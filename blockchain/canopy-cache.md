# Canopy Cache

**Category:** Blockchain  
**Points:** 490  
**Flag:** `slopped{packbits_lookup_routes_rethread_the_owner_lane}`

## Overview

Canopy Cache mixed a WASM-like helper module, encrypted service messages, and a route table hidden behind witness validation. The goal was to make the `audit` path invoke a route that we controlled while preserving the capability mask required for blessing.

## High-Level Strategy

The supplied mesh module was patched so that `audit` invoked route `1`. We then needed route `1` to point at a valid preview lane.

The catch was in the witness layer:

- The `bind` decoder rejected image offsets above `0x0f`.
- The later route patcher needed an offset above `0x17`.

So a direct bind with the desired offset failed validation.

## Session Encryption

The `warm`, `quote`, and `attest` payloads were encrypted with a session-derived LCG XOR stream. The `status` hint leaked enough state to recover the session stream, allowing us to prepare valid encrypted payloads for the later steps.

## PackBits Overflow

The breakthrough was the `expand` opcode. It validated the compressed input length, but the PackBits-style decompressed output could grow past the intended area and overwrite the bind table.

The exploit used this sequence:

1. Add four RLE fragments to the arena.
2. Create a valid bind using a small offset that passed validation.
3. Trigger layer expansion so the RLE output rewrote the bind entry after validation.

The rewritten bind entry became:

```text
[route=1, quote=0, image_off=0x18, flags=0]
```

The warm image at offset `0x18` contained the desired route bytes:

```text
02 01 01 01
```

This preserved `cap_mask = 0x01`, so the slot was still blessable.

## Solution Flow

The final order was:

1. Upload the patched helper module.
2. Warm the image with route bytes at offset `0x18`.
3. Sync the session.
4. Quote and attest using the recovered encrypted payload format.
5. Bless the slot.
6. Activate it.
7. Invoke `audit`.
8. Request the flag.

The service returned:

```text
slopped{packbits_lookup_routes_rethread_the_owner_lane}
```

## Takeaways

This challenge was about getting data past one validator and then changing it before the consumer used it. The PackBits expansion created exactly that gap: validate a harmless bind, then expand into the bind table and retarget the route.
