#!/usr/bin/env python3
import argparse
import concurrent.futures
import hashlib
import json
import time
from pathlib import Path

import h3
from argon2.low_level import Type, hash_secret_raw

DEFAULT_ARTIFACTS = Path(__file__).resolve().parents[1] / "artifacts"


def latlng_to_cell(lat, lon, res):
    if hasattr(h3, "latlng_to_cell"):
        return h3.latlng_to_cell(lat, lon, res)
    return h3.geo_to_h3(lat, lon, res)


def cell_to_latlng(cell):
    if hasattr(h3, "cell_to_latlng"):
        return h3.cell_to_latlng(cell)
    return h3.h3_to_geo(cell)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("name")
    parser.add_argument("lat_min", type=float)
    parser.add_argument("lat_max", type=float)
    parser.add_argument("lon_min", type=float)
    parser.add_argument("lon_max", type=float)
    parser.add_argument("--step", type=float, default=0.0025)
    parser.add_argument("--workers", type=int, default=8)
    parser.add_argument("--artifacts", type=Path, default=DEFAULT_ARTIFACTS)
    args = parser.parse_args()

    challs = json.load(open(args.artifacts / "challs.json"))["main"]
    levels = json.load(open(args.artifacts / "levels.json"))["main"]
    target = next(c for c in challs if c["name"] == args.name)["sha256"]
    salt = args.name.ljust(8, "0").encode()
    res = levels["resolution"]

    cells = set()
    lat = args.lat_min
    while lat <= args.lat_max:
        lon = args.lon_min
        while lon <= args.lon_max:
            cells.add(latlng_to_cell(lat, lon, res))
            lon += args.step
        lat += args.step
    cells = sorted(cells)
    print(f"cells {len(cells)}", flush=True)

    def check(cell):
        raw = hash_secret_raw(
            cell.encode(),
            salt,
            time_cost=levels["t"],
            memory_cost=levels["mem"],
            parallelism=1,
            hash_len=16,
            type=Type.D,
            version=0x13,
        )
        hx = raw.hex()
        if hashlib.sha256(hx.encode()).hexdigest() == target:
            return cell, hx
        return None

    start = time.time()
    checked = 0
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.workers) as pool:
        futures = {pool.submit(check, cell): cell for cell in cells}
        for fut in concurrent.futures.as_completed(futures):
            checked += 1
            result = fut.result()
            if result:
                cell, hx = result
                center = cell_to_latlng(cell)
                print(f"FOUND {args.name} {cell} {center[0]} {center[1]} {hx}", flush=True)
                return
            if checked % 500 == 0:
                elapsed = time.time() - start
                print(f"checked {checked}/{len(cells)} elapsed {elapsed:.1f}s", flush=True)
    print(f"not found elapsed {time.time() - start:.1f}s")


if __name__ == "__main__":
    main()
