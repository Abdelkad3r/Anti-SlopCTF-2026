#!/usr/bin/env python3
"""
Exploit for Reverse/Parallax Cartridge.

The BOOT token is authenticated as SHA256(secret || body), not HMAC.  We do not
know the 32-byte secret, but the digest can be length-extended.  The forged tape
appends duplicate decoded fields that turn on the debug/answer path and install
the runner cookie for the hidden quiet-bank program.
"""

import argparse
import base64
import hashlib
import re
import socket
import struct
from pathlib import Path


DEFAULT_HOST = "178.105.199.41"
DEFAULT_PORT = 13347
SECRET_LEN = 32
QUIET_BANK_DELTA = 32
RUNNER_COOKIE_LABEL = b"parallax/runner-cookie/v5"

SHA256_K = [
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
    0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
    0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
    0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
    0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
    0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
    0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
    0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
    0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
]


def b64encode(data):
    return base64.b64encode(data)


def b64decode(text):
    if isinstance(text, str):
        text = text.encode()
    text += b"=" * (-len(text) % 4)
    return base64.b64decode(text)


def rotr32(x, n):
    return ((x >> n) | (x << (32 - n))) & 0xFFFFFFFF


def sha256_compress(chunk, state):
    words = list(struct.unpack(">16I", chunk))
    for i in range(16, 64):
        s0 = rotr32(words[i - 15], 7) ^ rotr32(words[i - 15], 18) ^ (words[i - 15] >> 3)
        s1 = rotr32(words[i - 2], 17) ^ rotr32(words[i - 2], 19) ^ (words[i - 2] >> 10)
        words.append((words[i - 16] + s0 + words[i - 7] + s1) & 0xFFFFFFFF)

    a, b, c, d, e, f, g, h = state
    for i in range(64):
        big_s1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25)
        ch = (e & f) ^ ((~e) & g)
        t1 = (h + big_s1 + ch + SHA256_K[i] + words[i]) & 0xFFFFFFFF
        big_s0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22)
        maj = (a & b) ^ (a & c) ^ (b & c)
        t2 = (big_s0 + maj) & 0xFFFFFFFF
        h, g, f, e, d, c, b, a = g, f, e, (d + t1) & 0xFFFFFFFF, c, b, a, (t1 + t2) & 0xFFFFFFFF

    return [(x + y) & 0xFFFFFFFF for x, y in zip(state, [a, b, c, d, e, f, g, h])]


def sha256_padding(message_len):
    return b"\x80" + b"\x00" * (((56 - (message_len + 1) % 64) % 64)) + struct.pack(">Q", message_len * 8)


def sha256_length_extend(digest, original_len, suffix):
    state = list(struct.unpack(">8I", digest))
    glue = sha256_padding(original_len)
    total_len = original_len + len(glue) + len(suffix)
    extension = suffix + sha256_padding(total_len)
    for offset in range(0, len(extension), 64):
        state = sha256_compress(extension[offset:offset + 64], state)
    return struct.pack(">8I", *state), glue


def parse_qar_records(qar):
    if not qar.startswith(b"QAR5"):
        raise ValueError("not a QAR5 cartridge")

    records = {}
    offset = 4
    while offset < len(qar):
        tag = qar[offset:offset + 4]
        if tag == b"LREC":
            name_len = qar[offset + 4]
            data_len = int.from_bytes(qar[offset + 5:offset + 7], "little")
            name_start = offset + 7
            data_start = name_start + name_len
            name = qar[name_start:data_start].decode("ascii")
            records[name] = (data_start, data_len)
            offset = data_start + data_len
            continue
        if tag == b"QDIR":
            break
        raise ValueError(f"unknown QAR record at 0x{offset:x}: {tag!r}")

    return records


def ungray(value):
    out = value
    while value:
        value >>= 1
        out ^= value
    return out


def unpack_indices(blob):
    count = blob[0]
    packed = int.from_bytes(blob[1:], "little")
    indices = []
    for i in range(count):
        indices.append(ungray((packed >> (5 * i)) & 0x1F))
    return indices


def make_quiet_bank_cartridge(original):
    records = parse_qar_records(original)
    dict_off, dict_len = records["dict"]
    prog_off, prog_len = records["prog"]
    quiet_off, quiet_len = records["quiet"]

    if dict_len % 4:
        raise ValueError("dict record is not made of 4-byte cells")
    if quiet_len < 2:
        raise ValueError("quiet record is too short")

    visible_indices = unpack_indices(original[prog_off:prog_off + prog_len])
    runner_indices = visible_indices[:-1] + [visible_indices[-1] + QUIET_BANK_DELTA]
    max_index = dict_len // 4
    if runner_indices[-1] >= max_index:
        raise ValueError("hidden quiet-bank index is outside the dict")

    mutated = bytearray(original)
    mutated[quiet_off + 1] |= 1

    dictionary = mutated[dict_off:dict_off + dict_len]
    runner_program = b"".join(dictionary[i * 4:(i + 1) * 4] for i in runner_indices)
    runner_cookie = hashlib.sha256(RUNNER_COOKIE_LABEL + runner_program).digest()[:4]
    return bytes(mutated), visible_indices, runner_indices, runner_program, runner_cookie


def forge_resume_token(token_b64, runner_cookie):
    raw = b64decode(token_b64)
    if len(raw) < 33:
        raise ValueError("token is too short")

    body, digest = raw[:-32], raw[-32:]

    # Decoded tape fields. Later duplicates win in the Go state decoder.
    # f0 01 01: set field 1 to true/debug.
    # f0 06 xx: set field 6 to the hidden-runner cookie.
    suffix = b"\xf0\x01\x01" + b"\xf0\x06" + runner_cookie
    new_digest, glue = sha256_length_extend(digest, SECRET_LEN + len(body), suffix)
    return body + glue + suffix + new_digest, suffix, glue


def recv_some(sock, timeout=1.0):
    old_timeout = sock.gettimeout()
    chunks = []
    try:
        sock.settimeout(timeout)
        while True:
            try:
                chunk = sock.recv(4096)
            except socket.timeout:
                break
            if not chunk:
                break
            chunks.append(chunk)
            if len(chunk) < 4096:
                break
    finally:
        sock.settimeout(old_timeout)
    return b"".join(chunks).decode(errors="replace")


def extract_token(response):
    match = re.search(r"TOKEN\s+([A-Za-z0-9+/=]+)", response)
    if not match:
        raise ValueError(f"could not find token in response: {response!r}")
    return match.group(1)


def exploit(host, port, original, mutated, runner_cookie, forged_token=None):
    with socket.create_connection((host, port), timeout=10) as sock:
        sock.settimeout(2.0)
        banner = recv_some(sock)
        print(banner, end="" if banner.endswith("\n") else "\n")

        sock.sendall(b"BOOT " + b64encode(original) + b"\n")
        boot_response = recv_some(sock)
        print("BOOT:", boot_response.strip())

        if forged_token is None:
            token = extract_token(boot_response)
            forged_token, _suffix, _glue = forge_resume_token(token, runner_cookie)

        sock.sendall(b"STEP " + b64encode(mutated) + b" " + b64encode(forged_token) + b"\n")
        step_response = recv_some(sock)
        print("STEP:", step_response.strip())
        return step_response


def main():
    parser = argparse.ArgumentParser(description="Exploit Anti-Slop CTF Parallax Cartridge")
    parser.add_argument("--host", default=DEFAULT_HOST)
    parser.add_argument("--port", type=int, default=DEFAULT_PORT)
    parser.add_argument("--qar", type=Path, default=Path(__file__).with_name("starter.qar"))
    parser.add_argument("--token", help="forge this BOOT token offline instead of connecting")
    parser.add_argument("--write-mutated", type=Path, help="write the quiet-bank cartridge to this path")
    parser.add_argument("--offline", action="store_true", help="only print derived values")
    args = parser.parse_args()

    original = args.qar.read_bytes()
    mutated, visible, runner, runner_program, runner_cookie = make_quiet_bank_cartridge(original)
    print(f"[+] visible program indices: {visible}")
    print(f"[+] runner program indices:  {runner}")
    print(f"[+] runner program bytes:    {runner_program.hex()}")
    print(f"[+] runner cookie:           {runner_cookie.hex()}")

    if args.write_mutated:
        args.write_mutated.write_bytes(mutated)
        print(f"[+] wrote mutated cartridge to {args.write_mutated}")

    if args.token:
        forged, suffix, glue = forge_resume_token(args.token, runner_cookie)
        print(f"[+] extension suffix: {suffix.hex()}")
        print(f"[+] SHA-256 glue:     {glue.hex()}")
        print(f"[+] forged token:     {b64encode(forged).decode()}")
        return

    if args.offline:
        return

    response = exploit(args.host, args.port, original, mutated, runner_cookie)
    flag = re.search(r"slopped\{[^}]+\}", response)
    if flag:
        print(f"[+] flag: {flag.group(0)}")


if __name__ == "__main__":
    main()
