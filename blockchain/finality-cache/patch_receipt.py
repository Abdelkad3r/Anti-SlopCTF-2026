#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path


DEFAULT_IN = Path(__file__).resolve().parent / "artifacts" / "dist" / "sample.receipt"
DEFAULT_OUT = Path("patched.receipt")

AMOUNT_OFFSET = 0x20
COMMITMENT_OFFSET = 0x3C
COMMITMENT_LEN = 32
OLD_AMOUNT = 20000
NEW_AMOUNT = 80000
OLD_AMOUNT_VARINT = bytes.fromhex("a09c01")
NEW_AMOUNT_VARINT = bytes.fromhex("80f104")


def patch_once(buf: bytearray, needle: bytes, replacement: bytes, label: str) -> int:
    idx = bytes(buf).find(needle)
    if idx < 0:
        raise ValueError(f"could not find {label} bytes {needle.hex()}")
    buf[idx : idx + len(needle)] = replacement
    return idx


def parse_digest(hex_value: str) -> bytes:
    digest = bytes.fromhex(hex_value)
    if len(digest) != COMMITMENT_LEN:
        raise ValueError("digest must be exactly 32 bytes")
    return digest


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Patch a Finality Cache receipt amount and optionally insert a recomputed VM commitment."
    )
    parser.add_argument("-i", "--input", type=Path, default=DEFAULT_IN)
    parser.add_argument("-o", "--output", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--amount", type=int, default=NEW_AMOUNT)
    parser.add_argument("--digest-hex", help="32-byte recomputed guardian VM commitment")
    parser.add_argument(
        "--lane-offset",
        type=lambda value: int(value, 0),
        help="explicit lane amount varint offset, if the old varint is not plainly searchable",
    )
    args = parser.parse_args()

    data = bytearray(args.input.read_bytes())
    old_header = int.from_bytes(data[AMOUNT_OFFSET : AMOUNT_OFFSET + 8], "little")
    print(f"header amount @ 0x{AMOUNT_OFFSET:x}: {old_header}")
    data[AMOUNT_OFFSET : AMOUNT_OFFSET + 8] = args.amount.to_bytes(8, "little")
    print(f"patched header amount -> {args.amount}")

    if args.lane_offset is not None:
        off = args.lane_offset
        before = bytes(data[off : off + len(OLD_AMOUNT_VARINT)])
        data[off : off + len(OLD_AMOUNT_VARINT)] = NEW_AMOUNT_VARINT
        print(f"patched lane varint @ 0x{off:x}: {before.hex()} -> {NEW_AMOUNT_VARINT.hex()}")
    else:
        try:
            off = patch_once(data, OLD_AMOUNT_VARINT, NEW_AMOUNT_VARINT, "old lane amount varint")
            print(f"patched lane varint @ 0x{off:x}: {OLD_AMOUNT_VARINT.hex()} -> {NEW_AMOUNT_VARINT.hex()}")
        except ValueError as exc:
            print(f"note: {exc}")
            print("      the event-time remote receipt exposed the lane varint plainly;")
            print("      this bundled sample keeps that value inside the lane encoding.")
            print("      rerun with --lane-offset when working on a session receipt.")

    if args.digest_hex:
        digest = parse_digest(args.digest_hex)
        old_digest = bytes(data[COMMITMENT_OFFSET : COMMITMENT_OFFSET + COMMITMENT_LEN])
        data[COMMITMENT_OFFSET : COMMITMENT_OFFSET + COMMITMENT_LEN] = digest
        print(f"patched digest @ 0x{COMMITMENT_OFFSET:x}: {old_digest.hex()} -> {digest.hex()}")
    else:
        print("note: no --digest-hex supplied; receipt still needs the recomputed guardian commitment.")

    args.output.write_bytes(data)
    print(f"wrote {args.output}")


if __name__ == "__main__":
    main()
