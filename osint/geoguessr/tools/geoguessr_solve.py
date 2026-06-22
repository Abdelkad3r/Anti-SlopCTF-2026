#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

from Crypto.Cipher import AES

HERE = Path(__file__).resolve()
DEFAULT_ARTIFACTS = (
    HERE.parent / "artifacts"
    if (HERE.parent / "artifacts").exists()
    else HERE.parents[1] / "artifacts"
)


def unpad(data: bytes) -> bytes:
    if not data:
        return data
    pad = data[-1]
    if pad < 1 or pad > 16 or pad > len(data):
        return data
    if data[-pad:] != bytes([pad]) * pad:
        return data
    return data[:-pad]


def aes_decrypt_hex(key_hex: str, iv_hex: str, ct_hex: str) -> bytes:
    cipher = AES.new(bytes.fromhex(key_hex), AES.MODE_CBC, bytes.fromhex(iv_hex))
    return unpad(cipher.decrypt(bytes.fromhex(ct_hex)))


def gf_mul_poly(a: int, b: int, poly: int = 0x11B) -> int:
    out = 0
    while b:
        if b & 1:
            out ^= a
        a <<= 1
        if a & 0x100:
            a ^= poly
        b >>= 1
    return out & 0xFF


def build_gf_tables(poly: int = 0x11B, generator: int = 3):
    exp = [0] * 512
    log = [0] * 256
    x = 1
    for i in range(255):
        exp[i] = x
        log[x] = i
        x = gf_mul_poly(x, generator, poly)
    for i in range(255, 512):
        exp[i] = exp[i - 255]
    return log, exp


LOG, EXP = build_gf_tables()


def gf_add(a: int, b: int) -> int:
    return a ^ b


def gf_mul(a: int, b: int) -> int:
    if a == 0 or b == 0:
        return 0
    return EXP[(LOG[a] + LOG[b]) % 255]


def gf_div(a: int, b: int) -> int:
    if b == 0:
        raise ZeroDivisionError("GF divide by zero")
    if a == 0:
        return 0
    return EXP[(LOG[a] - LOG[b] + 255) % 255]


def interpolate(xs, ys, x=0):
    out = 0
    n = len(xs)
    for i in range(n):
        basis = 1
        for j in range(n):
            if i == j:
                continue
            basis = gf_mul(basis, gf_div(gf_add(x, xs[j]), gf_add(xs[i], xs[j])))
        out = gf_add(out, gf_mul(ys[i], basis))
    return out


def combine(shares):
    size = len(shares[0])
    if any(len(s) != size for s in shares):
        raise ValueError("share sizes differ")
    xs = [s[-1] for s in shares]
    if len(set(xs)) != len(xs):
        raise ValueError("duplicate share indexes")
    secret = bytearray(size - 1)
    for i in range(size - 1):
        secret[i] = interpolate(xs, [s[i] for s in shares], 0)
    return bytes(secret)


def decrypt_share(challs, name: str, key_hex: str) -> bytes:
    chall = next(c for c in challs if c["name"] == name)
    return unpad(aes_decrypt_hex(key_hex, chall["iv"], chall["ciphertext"]))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "hits",
        nargs="?",
        default=str(DEFAULT_ARTIFACTS / "geoguessr_hits.json"),
        help="JSON file mapping challenge name to Argon2 key hex",
    )
    parser.add_argument("--artifacts", type=Path, default=DEFAULT_ARTIFACTS)
    args = parser.parse_args()

    challs = json.load(open(args.artifacts / "challs.json"))["main"]
    level = json.load(open(args.artifacts / "levels.json"))["main"]
    hits = json.load(open(args.hits))
    shares = []
    for chall in challs:
        name = chall["name"]
        if name not in hits:
            continue
        share = decrypt_share(challs, name, hits[name])
        print(f"{name:12s} share={share.hex()} x={share[-1]}")
        shares.append(share)
    print(f"{len(shares)} shares")
    if len(shares) >= level["threshold"]:
        key = combine(shares[: level["threshold"]])
        flag = unpad(aes_decrypt_hex(key.hex(), level["iv"], level["ciphertext"]))
        print(flag.decode())


if __name__ == "__main__":
    main()
