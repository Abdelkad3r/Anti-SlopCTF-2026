#!/usr/bin/env python3
import json
import socket
import struct
from pathlib import Path

FT_HELLO = 0x10
FT_NOP = 0x11
FT_ACK_STRICT = 0x12
FT_INFO = 0x13
FT_NEWCAP = 0x20
FT_APPEND = 0x21
FT_SIGN = 0x22
FT_COMMENT = 0x23
FT_RUN = 0x24

RT_OK = 0x80
RT_ERR = 0x81
RT_MODE = 0x82
RT_SIG = 0x83
RT_OUT = 0x84
RT_INFO = 0x85

REC_TEXT = 0x01
REC_ECHO = 0x02
REC_HALT = 0x03
REC_TRACE = 0x05


def rec_text(data: bytes) -> bytes:
    if len(data) > 48:
        raise ValueError("text record too large")
    return bytes([REC_TEXT, len(data)]) + data


def rec_echo() -> bytes:
    return bytes([REC_ECHO])


def rec_halt() -> bytes:
    return bytes([REC_HALT])


def rec_trace(offset: int, size: int) -> bytes:
    if not 0 <= offset <= 0xFF:
        raise ValueError("offset must fit in one byte")
    if not 0 <= size <= 0xFF:
        raise ValueError("size must fit in one byte")
    return bytes([REC_TRACE, offset, size])


def rec_raw(kind: int, payload: bytes = b"") -> bytes:
    if not 0 <= kind <= 0xFF:
        raise ValueError("record kind must fit in one byte")
    return bytes([kind]) + payload


def comment_literal(data: bytes) -> bytes:
    if not 1 <= len(data) <= 64:
        raise ValueError("literal span must be between 1 and 64 bytes")
    return bytes([len(data) - 1]) + data


def comment_repeat(byte: int, count: int) -> bytes:
    if not 0 <= byte <= 0xFF:
        raise ValueError("repeat byte must fit in one byte")
    if not 3 <= count <= 66:
        raise ValueError("repeat span must be between 3 and 66 bytes")
    return bytes([0x40 | (count - 3), byte])


def comment_backref(distance: int, count: int) -> bytes:
    if not 1 <= distance <= 0xFF:
        raise ValueError("backref distance must fit in one byte")
    if not 3 <= count <= 66:
        raise ValueError("backref span must be between 3 and 66 bytes")
    return bytes([0x80 | (count - 3), distance])


def comment_xor(count: int, mask: int) -> bytes:
    if not 1 <= count <= 32:
        raise ValueError("xor span must be between 1 and 32 bytes")
    if not 0 <= mask <= 0xFF:
        raise ValueError("xor mask must fit in one byte")
    return bytes([0xC0 | (count - 1), mask])


def comment_braid_fill(count: int, value: int) -> bytes:
    if not 17 <= count <= 32:
        raise ValueError("braid span must be between 17 and 32 bytes")
    if not 0 <= value <= 0xFF:
        raise ValueError("fill byte must fit in one byte")
    return bytes([0xE0 | (count - 17), value])


def comment_patch(idx: int, value: int) -> bytes:
    if not 0 <= idx <= 7:
        raise ValueError("patch slot must be between 0 and 7")
    if not 0 <= value <= 0xFF:
        raise ValueError("patch value must fit in one byte")
    return b"\xFF" + bytes([idx, value])


class Client:
    def __init__(self, host: str, port: int):
        self.sock = socket.create_connection((host, port))
        self.seq = 0
        self.banner = self.recv()

    def strict_handshake(self) -> None:
        self.send(FT_HELLO, b"\x01")
        self.recv()
        self.send(FT_ACK_STRICT)
        self.recv()

    def send(self, ftype: int, payload: bytes = b"") -> None:
        self.sock.sendall(struct.pack("<BBH", ftype, self.seq, len(payload)) + payload)
        self.seq = (self.seq + 1) & 0xFF

    def recv(self):
        hdr = self._read(4)
        ftype, seq, length = struct.unpack("<BBH", hdr)
        payload = self._read(length)
        return ftype, seq, payload

    def _read(self, n: int) -> bytes:
        out = b""
        while len(out) < n:
            chunk = self.sock.recv(n - len(out))
            if not chunk:
                raise EOFError("connection closed")
            out += chunk
        return out


def load_public_params() -> dict:
    path = Path(__file__).with_name("public_params.json")
    return json.loads(path.read_text())


if __name__ == "__main__":
    print(json.dumps(load_public_params(), indent=2))
