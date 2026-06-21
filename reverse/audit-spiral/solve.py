#!/usr/bin/env python3
import hashlib
import re
import socket
import sys


HOST = "178.105.199.41"
PORT = 20023

# Recovered from the quadratic nonce relation described in the writeup.
PRIVATE_KEY = int(
    "a8118ccf6054821700c20bf08bd0b4cbe9bc4e4c140a619d86c0536692f417f", 16
)

# secp256k1 parameters.
P = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
N = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
GX = 0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798
GY = 0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8
G = (GX, GY)


def inv(x, mod):
    return pow(x, -1, mod)


def point_add(a, b):
    if a is None:
        return b
    if b is None:
        return a

    x1, y1 = a
    x2, y2 = b

    if x1 == x2 and (y1 + y2) % P == 0:
        return None

    if a == b:
        lam = (3 * x1 * x1) * inv(2 * y1 % P, P)
    else:
        lam = (y2 - y1) * inv((x2 - x1) % P, P)
    lam %= P

    x3 = (lam * lam - x1 - x2) % P
    y3 = (lam * (x1 - x3) - y1) % P
    return x3, y3


def scalar_mult(k, point=G):
    result = None
    addend = point
    while k:
        if k & 1:
            result = point_add(result, addend)
        addend = point_add(addend, addend)
        k >>= 1
    return result


def deterministic_k(digest):
    seed = PRIVATE_KEY.to_bytes(32, "big") + digest
    k = int.from_bytes(hashlib.sha256(seed).digest(), "big") % N
    return k or 1


def sign_digest(digest):
    z = int.from_bytes(digest, "big") % N
    k = deterministic_k(digest)

    while True:
        r = scalar_mult(k)[0] % N
        if r:
            s = (inv(k, N) * (z + r * PRIVATE_KEY)) % N
            if s:
                return r, s
        k = (k + 1) % N or 1


def recv_until(sock, marker=b"> "):
    data = b""
    while marker not in data:
        chunk = sock.recv(4096)
        if not chunk:
            break
        data += chunk
    return data.decode(errors="replace")


def solve(host=HOST, port=PORT):
    with socket.create_connection((host, port), timeout=8) as sock:
        sock.settimeout(8)
        banner = recv_until(sock)
        print(banner, end="")

        sock.sendall(b"target\n")
        target_response = recv_until(sock)
        print(target_response, end="")

        match = re.search(r"digest=([0-9a-fA-F]{64})", target_response)
        if not match:
            raise RuntimeError("could not find target digest")

        digest = bytes.fromhex(match.group(1))
        r, s = sign_digest(digest)

        command = f"admin {r:x} {s:x}\n".encode()
        sock.sendall(command)
        print(recv_until(sock), end="")


if __name__ == "__main__":
    if len(sys.argv) == 1:
        solve()
    elif len(sys.argv) == 2 and ":" in sys.argv[1]:
        h, p = sys.argv[1].rsplit(":", 1)
        solve(h, int(p))
    elif len(sys.argv) == 3:
        solve(sys.argv[1], int(sys.argv[2]))
    else:
        print(f"usage: {sys.argv[0]} [host:port]", file=sys.stderr)
        raise SystemExit(2)
