#!/usr/bin/env python3
import hashlib
import json
import math
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).with_name("artifacts") / "dist"))
from capsule import Client, FT_ACK_STRICT, FT_APPEND, FT_HELLO, FT_NEWCAP, FT_RUN, rec_halt, rec_raw


HOST = sys.argv[1] if len(sys.argv) > 1 else "178.105.199.41"
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 20000

P = 82757585072455028579685401889888615758895788003223315567334952176806753515189
Q = 71296171568667776680278779905104901035842966603378173362597119862250613420693


def load_params():
    path = Path(__file__).with_name("artifacts") / "dist" / "public_params.json"
    return json.loads(path.read_text())


def fdh(audit: bytes, n: int) -> int:
    digest = hashlib.sha256(audit).digest()
    block = hashlib.sha256(b"paper-lantern/v4:msg" + digest).digest()
    block += hashlib.sha256(b"paper-lantern/v4:aux" + digest).digest()
    return int.from_bytes(block, "big") % n or 1


def sign(audit: bytes) -> bytes:
    params = load_params()
    n = int(params["n"], 16)
    e = int(params["e"])
    size = int(params["signature_size"])

    assert P * Q == n
    d = pow(e, -1, math.lcm(P - 1, Q - 1))
    m = fdh(audit, n)
    sig = pow(m, d, n)
    assert pow(sig, e, n) == m
    return sig.to_bytes(size, "big")


def recv_text(client):
    ftype, _seq, payload = client.recv()
    return ftype, payload


def main():
    sig = sign(b"F")
    records = rec_raw(0x7F) + rec_halt()

    client = Client(HOST, PORT)
    client.send(FT_HELLO, b"\x01")
    recv_text(client)
    client.send(FT_ACK_STRICT)
    recv_text(client)
    client.send(FT_NEWCAP)
    recv_text(client)
    client.send(FT_APPEND, records)
    recv_text(client)
    client.send(FT_RUN, sig)
    _ftype, payload = recv_text(client)
    print(payload.decode(errors="replace"), end="")


if __name__ == "__main__":
    main()
