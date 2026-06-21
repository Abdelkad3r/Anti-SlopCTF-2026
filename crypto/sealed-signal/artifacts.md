# Sealed Signal Artifacts

This directory contains the local artifacts used for the solve.

## Files

- [`relay-client.js`](relay-client.js)
  Browser-side protocol implementation recovered from `/app.js`. It documents
  the `R1` frame format, tag IDs, opcode IDs, dialect XOR, nibble swap, varint
  encoding, and CRC16 check.

- [`sample-session.r1t`](sample-session.r1t)
  Captured binary relay traffic used while reversing the frame format.

- [`exploit.py`](exploit.py)
  Clean end-to-end solver. It implements the relay protocol, asks the cache
  capsule signer for two carefully chosen MACs, forges a root resume capsule,
  and requests the flag.

## Hashes

```text
019af172af00cb7ef50e875290fafe83d6d7d21a85ae45a743487ddab4b0f973  relay-client.js
02ad3ef0395d6f13eb02e63804a23c5f6334405d41a6e2cc0c062aba4594b70c  sample-session.r1t
```
