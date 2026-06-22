#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path


BASE = Path(__file__).resolve().parent / "artifacts" / "lane_helper.wasm"
PATCHED = Path(__file__).resolve().parent / "artifacts" / "patched_helper.wasm"

PATCHES = {
    0x37: 0x22,
    0x38: 0x01,
    0x48: 0x00,
    0x49: 0x00,
    0x4B: 0x00,
    0x94: 0x02,
    0x95: 0x01,
    0x96: 0x01,
    0x97: 0x01,
}


def apply_patches(data: bytes) -> bytes:
    buf = bytearray(data)
    for offset, value in PATCHES.items():
        buf[offset] = value
    return bytes(buf)


def main() -> None:
    parser = argparse.ArgumentParser(description="Rebuild and verify the Canopy Cache patched helper WASM.")
    parser.add_argument("--base", type=Path, default=BASE)
    parser.add_argument("--patched", type=Path, default=PATCHED)
    parser.add_argument("-o", "--output", type=Path)
    args = parser.parse_args()

    rebuilt = apply_patches(args.base.read_bytes())
    expected = args.patched.read_bytes()

    print("patches:")
    for offset, value in PATCHES.items():
        print(f"  0x{offset:02x} -> 0x{value:02x}")

    if rebuilt == expected:
        print("OK: rebuilt helper matches artifacts/patched_helper.wasm")
    else:
        print("MISMATCH: rebuilt helper differs from artifacts/patched_helper.wasm")
        for i, (a, b) in enumerate(zip(rebuilt, expected)):
            if a != b:
                print(f"first diff @ 0x{i:x}: rebuilt=0x{a:02x} expected=0x{b:02x}")
                break
        raise SystemExit(1)

    if args.output:
        args.output.write_bytes(rebuilt)
        print(f"wrote {args.output}")


if __name__ == "__main__":
    main()
