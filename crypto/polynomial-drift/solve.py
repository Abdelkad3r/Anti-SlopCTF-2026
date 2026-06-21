#!/usr/bin/env python3
"""
Polynomial Drift solver.

The service signs capsule commits with ECDSA/secp256k1. The capsule below makes
the low 24 bits of each nonce visible as:

    k & 0xffffff == (4 << 16) | (3 << 8) | preview

Collect enough commit signatures, solve the resulting hidden-number problem
with fpylll/CVP, then sign the final grant digest and submit it via auth.
"""

import argparse
import hashlib
import json
import re
import socket
import time

try:
    from fpylll import CVP, LLL, IntegerMatrix
except ImportError as exc:
    raise SystemExit("missing dependency: pip install fpylll cysignals") from exc


HOST = "178.105.199.41"
PORT = 20006
TARGET_PUB = "02cc74bc2c7013648ff52090c12ed29cf95ce79ab49506d6c16957cc04e660e488"

N = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
P = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
GX = 55066263022277343669578718895168534326250603453777594175500187360389116729240
GY = 32670510020758816978083085130507043184471273380659243275938904335757337482424

NONCE_LOW_BITS = 24
NONCE_LOW_BASE = (4 << 16) | (3 << 8)
CAPSULE_HEX = "504446540209008a0000000010163e474c709aa5f8"


def inv(x, mod):
    return pow(x % mod, -1, mod)


def ec_add(p1, p2):
    if p1 is None:
        return p2
    if p2 is None:
        return p1

    x1, y1 = p1
    x2, y2 = p2
    if x1 == x2 and (y1 + y2) % P == 0:
        return None

    if p1 == p2:
        lam = (3 * x1 * x1) * inv(2 * y1, P) % P
    else:
        lam = (y2 - y1) * inv(x2 - x1, P) % P

    x3 = (lam * lam - x1 - x2) % P
    y3 = (lam * (x1 - x3) - y1) % P
    return x3, y3


def ec_mul(k, point=(GX, GY)):
    result = None
    k %= N
    while k:
        if k & 1:
            result = ec_add(result, point)
        point = ec_add(point, point)
        k >>= 1
    return result


def compressed_pubkey(d):
    x, y = ec_mul(d)
    return ("03" if y & 1 else "02") + x.to_bytes(32, "big").hex()


def ecdsa_sign_digest(d, digest, low_s=True):
    z = int.from_bytes(digest, "big")
    counter = 0
    while True:
        seed = b"polydrift-auth|" + d.to_bytes(32, "big") + digest + counter.to_bytes(4, "big")
        k = int.from_bytes(hashlib.sha256(seed).digest(), "big") % N
        counter += 1
        if not k:
            continue

        r = ec_mul(k)[0] % N
        if not r:
            continue

        s = inv(k, N) * (z + r * d) % N
        if not s:
            continue
        if low_s and s > N // 2:
            s = N - s
        return r.to_bytes(32, "big") + s.to_bytes(32, "big")


def rol8(x, n):
    n &= 7
    return ((x << n) | (x >> (8 - n))) & 0xff if n else x & 0xff


def build_capsule(values=(1, 2, 3, 4), a=0, b=0, c=0):
    code = []
    for value in values:
        code += [0x10, value & 0xff]
    code += [0x40]

    code = bytes(code)
    checksum = (a + sum(code)) & 0xffff
    shift = (c ^ b) & 0xff
    encoded = bytearray()
    for i, plain in enumerate(code):
        mask = (rol8((23 * i) & 0xff, c) + b) & 0xff
        encoded.append(rol8((plain ^ mask) & 0xff, shift))

    return (
        b"PDFT"
        + bytes([2])
        + len(code).to_bytes(2, "little")
        + checksum.to_bytes(2, "little")
        + bytes([a, b, c])
        + bytes(encoded)
    )


def read_available(sock, wait=0.08, timeout=1.0):
    old_timeout = sock.gettimeout()
    chunks = []
    try:
        sock.settimeout(timeout)
        try:
            first = sock.recv(8192)
        except socket.timeout:
            return ""
        if not first:
            return ""
        chunks.append(first)

        sock.settimeout(wait)
        while True:
            try:
                chunk = sock.recv(8192)
            except socket.timeout:
                break
            if not chunk:
                break
            chunks.append(chunk)
    finally:
        sock.settimeout(old_timeout)

    return b"".join(chunks).decode(errors="replace")


def send_command(sock, line):
    sock.sendall(line.encode() + b"\n")
    return read_available(sock)


def collect_rows(host, port, count, capsule_hex):
    rows = []
    with socket.create_connection((host, port), timeout=10) as sock:
        sock.settimeout(1.0)
        banner = read_available(sock, timeout=2.0)
        print(banner, end="" if banner.endswith("\n") else "\n")

        for i in range(count):
            output = ""
            output += send_command(sock, f"load {capsule_hex}")
            output += send_command(sock, "dryrun")
            output += send_command(sock, "commit")

            match = re.search(
                r"ok epoch=(\d+) preview=([0-9a-fA-F]+) "
                r"digest=([0-9a-fA-F]{64}) sig=([0-9a-fA-F]{128})",
                output,
            )
            if not match:
                print(f"[!] row {i}: parse failed")
                print(output.strip())
                continue

            row = {
                "i": i,
                "epoch": int(match.group(1)),
                "preview": match.group(2).lower(),
                "digest": match.group(3).lower(),
                "sig": match.group(4).lower(),
                "raw": output,
            }
            rows.append(row)
            print(f"[+] row {i:02d}: preview={row['preview']} digest={row['digest'][:16]}...")

        try:
            send_command(sock, "quit")
        except OSError:
            pass

    return rows


def load_rows(path):
    data = json.load(open(path))
    if isinstance(data, dict):
        return data.get("rows", [])
    return data


def parse_row(row):
    digest = row.get("digest")
    if digest is None:
        match = re.search(r"digest=([0-9a-fA-F]{64})", row.get("raw", "") + row.get("line", ""))
        digest = match.group(1) if match else None
    if digest is None:
        raise ValueError("row is missing digest")

    sig = row.get("sig")
    if sig is None:
        match = re.search(r"sig=([0-9a-fA-F]{128})", row.get("raw", "") + row.get("line", ""))
        sig = match.group(1) if match else None
    if sig is None:
        raise ValueError("row is missing signature")

    preview = row.get("preview") or row.get("commit_preview")
    if preview is None:
        match = re.search(r"preview=([0-9a-fA-F]+)", row.get("raw", "") + row.get("line", ""))
        preview = match.group(1) if match else None
    if preview is None:
        raise ValueError("row is missing preview")

    z = int(digest, 16)
    r = int(sig[:64], 16)
    s = int(sig[64:], 16)
    known_low = NONCE_LOW_BASE | int(preview, 16)
    return z, r, s, known_low


def recover_key(rows, expected_pub=TARGET_PUB):
    b = 1 << NONCE_LOW_BITS
    threshold = N // b
    inv_b = inv(b, N)

    for sample_count in range(8, len(rows) + 1):
        samples = []
        for row in rows[:sample_count]:
            z, r, s, known_low = parse_row(row)
            s_inv = inv(s, N)
            a = (r * s_inv) % N
            c = (z * s_inv - known_low) % N
            samples.append(((a * inv_b) % N, (c * inv_b) % N))

        dim = len(samples)
        modulus = N * b
        matrix = IntegerMatrix(dim + 1, dim + 1)
        for i in range(dim):
            matrix[i, i] = modulus
        for i, (a, _c) in enumerate(samples):
            matrix[dim, i] = (a * b) % modulus
        matrix[dim, dim] = 1

        target = [(((-c + threshold // 2) % N) * b) for (_a, c) in samples] + [0]
        LLL.reduction(matrix)
        closest = CVP.closest_vector(matrix, target)
        candidate = int(closest[dim]) % N
        pub = compressed_pubkey(candidate)

        ok = 0
        for a, c in samples:
            if (a * candidate + c) % N <= threshold:
                ok += 1

        print(f"[*] samples={sample_count:02d} ok={ok:02d}/{dim:02d} candidate={candidate:#x}")
        if pub == expected_pub:
            print(f"[+] recovered key matches {expected_pub}")
            return candidate

    raise RuntimeError("failed to recover a key matching the expected public key")


def auth(host, port, d):
    with socket.create_connection((host, port), timeout=10) as sock:
        sock.settimeout(2.0)
        banner = read_available(sock, timeout=2.0)
        print(banner, end="" if banner.endswith("\n") else "\n")

        match = re.search(r"sid=(\d+)", banner)
        if not match:
            raise RuntimeError("could not parse sid from banner")

        sid = int(match.group(1))
        digest = hashlib.sha256(b"POLYPHASE|grant|" + sid.to_bytes(8, "big")).digest()
        sig = ecdsa_sign_digest(d, digest)
        print(f"[+] auth sid={sid} sig={sig.hex()}")
        sock.sendall(b"auth " + sig.hex().encode() + b"\n")
        return read_available(sock, timeout=2.0)


def int_arg(value):
    return int(value, 0)


def main():
    parser = argparse.ArgumentParser(description="Solve Anti-Slop CTF Polynomial Drift")
    parser.add_argument("--host", default=HOST)
    parser.add_argument("--port", default=PORT, type=int)
    parser.add_argument("--count", default=12, type=int)
    parser.add_argument("--capsule", default=CAPSULE_HEX)
    parser.add_argument("--capture", help="write collected rows to this JSON file")
    parser.add_argument("--use-capture", help="recover from a previously collected JSON file")
    parser.add_argument("--private-key", type=int_arg, help="skip recovery and use this scalar")
    parser.add_argument("--expected-pub", default=TARGET_PUB)
    parser.add_argument("--collect-only", action="store_true")
    parser.add_argument("--no-auth", action="store_true")
    args = parser.parse_args()

    generated = build_capsule().hex()
    if args.capsule == CAPSULE_HEX and generated != CAPSULE_HEX:
        raise RuntimeError("capsule builder sanity check failed")

    if args.private_key is not None:
        d = args.private_key % N
    else:
        rows = load_rows(args.use_capture) if args.use_capture else collect_rows(
            args.host, args.port, args.count, args.capsule
        )

        if args.capture:
            with open(args.capture, "w") as f:
                json.dump({"rows": rows}, f, indent=2)
            print(f"[+] saved {len(rows)} rows to {args.capture}")

        if args.collect_only:
            return
        if len(rows) < 8:
            raise RuntimeError("need more signatures for the lattice recovery")

        d = recover_key(rows, args.expected_pub)

    print(f"[+] private key = {d:#x}")
    if not args.no_auth:
        print(auth(args.host, args.port, d))


if __name__ == "__main__":
    main()
