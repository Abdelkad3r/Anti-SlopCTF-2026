# Canopy Cache

**Category:** Blockchain
**Points:** 490
**Remote:** `nc 178.105.199.41 31347`
**Flag:** `slopped{packbits_lookup_routes_rethread_the_owner_lane}`

## Summary

Canopy Cache mixed a small WASM-like helper module, encrypted service messages, and a route table protected by witness validation. The goal was to make the `audit` path invoke a route we controlled while keeping the capability mask required for blessing.

The final exploit combined three pieces:

1. Patch the helper module so `audit` calls route `1`.
2. Place useful route bytes in the warmed image at offset `0x18`.
3. Abuse PackBits expansion to rewrite a validated bind entry after the witness decoder accepted it.

That produced a blessable preview lane whose route pointer led to the desired audit path.

## Artifacts

The original handout, extracted files, analysis notes, and patched helper are included:

```text
artifacts/canopy.zip
artifacts/dist/canopyd
artifacts/dist/blessed_proxy.wasm
artifacts/dist/legacy_vault.sol
artifacts/lane_helper.wasm
artifacts/patched_helper.wasm
artifacts/analysis/canopyd.decomp.c
verify_patch.py
```

`canopyd.decomp.c` is the Ghidra decompile used during the solve. `lane_helper.wasm` is the helper module we patched, and `patched_helper.wasm` is the exact module used for the final exploit.

## Service Model

The binary exposed a command interface:

```text
upload <slot> <hex_wasm>
inspect <slot>
warm <slot> <hex_profile>
sync <slot>
quote <slot> <hex_receipt>
attest <slot> <hex_witness>
bless <slot>
activate <slot> <sealhex>
invoke <export_name>
flag
```

The interesting status fields were:

```text
session_hint
cap_mask
cache_warmed
cache_synced
quote_root
attest_root
attest_signers
```

`warm`, `quote`, and `attest` were not plain payload paths. They used a session-derived LCG XOR stream. The `status` hint leaked enough state to derive the stream and prepare valid encrypted payloads.

## Helper Patch

The supplied helper needed to make `audit` reach route `1`. The patched helper is small enough that the patch can be represented as direct byte edits:

```text
0x37 -> 0x22
0x38 -> 0x01
0x48 -> 0x00
0x49 -> 0x00
0x4b -> 0x00
0x94 -> 0x02
0x95 -> 0x01
0x96 -> 0x01
0x97 -> 0x01
```

The repository includes a verifier:

```bash
python3 verify_patch.py
```

Expected output:

```text
OK: rebuilt helper matches artifacts/patched_helper.wasm
```

## Validation Gap

The direct plan was to bind route `1` to a preview lane at image offset `0x18`, where the warmed image contained:

```text
02 01 01 01
```

The problem was that two consumers disagreed about valid offsets:

```text
bind decoder: rejects image offsets above 0x0f
route patcher: needs an offset above 0x17
```

A direct bind to `0x18` therefore failed validation.

The bypass was the `expand` opcode. It validated the compressed input length, but the PackBits-style decompressed output could run past the intended area and overwrite the bind table after validation.

The witness sequence was:

```text
1. Add four RLE fragments to the arena.
2. Create a valid bind using a small image offset.
3. Trigger layer expansion.
4. Let decompressed bytes rewrite the bind entry.
```

The rewritten bind entry became:

```text
[route=1, quote=0, image_off=0x18, flags=0]
```

That preserved:

```text
cap_mask = 0x01
```

so the slot was still blessable.

## Reproduction

The final command sequence was:

```text
1. upload the patched helper module
2. warm the image with route bytes at offset 0x18
3. sync the slot
4. quote using the recovered encrypted receipt format
5. attest with the PackBits-overflow witness
6. bless the slot
7. activate it
8. invoke audit
9. request flag
```

The service returned:

```text
slopped{packbits_lookup_routes_rethread_the_owner_lane}
```

## Takeaway

Canopy Cache was a classic validate-then-mutated-state problem. The bind entry passed validation with a harmless offset, then PackBits expansion rewrote the already-accepted data into the route the later consumer actually used.
