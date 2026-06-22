#!/usr/bin/env python3
import argparse
import hashlib
import json
import multiprocessing as mp
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


def worker(args):
    name, cell, level, target = args
    raw = hash_secret_raw(
        cell.encode(),
        name.ljust(8, "0").encode(),
        time_cost=level["t"],
        memory_cost=level["mem"],
        parallelism=1,
        hash_len=16,
        type=Type.D,
        version=0x13,
    )
    ok = hashlib.sha256(raw.hex().encode()).hexdigest() == TARGETS[name]
    return ok, cell, raw.hex()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("name")
    parser.add_argument("lat", type=float)
    parser.add_argument("lon", type=float)
    parser.add_argument("-r", "--radius", type=int, default=25)
    parser.add_argument("-j", "--jobs", type=int, default=8)
    parser.add_argument("--artifacts", type=Path, default=DEFAULT_ARTIFACTS)
    args = parser.parse_args()

    challs = json.load(open(args.artifacts / "challs.json"))["main"]
    level = json.load(open(args.artifacts / "levels.json"))["main"]
    targets = {c["name"]: c["sha256"] for c in challs}
    if args.name not in targets:
        raise SystemExit(f"unknown challenge name: {args.name}")

    center = latlng_to_cell(args.lat, args.lon, level["resolution"])
    cells = list(h3.grid_disk(center, args.radius))
    print(args.name, center, len(cells), flush=True)
    start = time.time()
    with mp.Pool(args.jobs) as pool:
        for ok, cell, key in pool.imap_unordered(
            worker,
            [(args.name, cell, level, targets[args.name]) for cell in cells],
            chunksize=4,
        ):
            if ok:
                print("HIT", cell, cell_to_latlng(cell), key, time.time() - start)
                pool.terminate()
                return
    print("no", time.time() - start)


if __name__ == "__main__":
    main()
