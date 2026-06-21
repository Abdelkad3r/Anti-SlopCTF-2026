# Audit Spiral

**Category:** Reverse  
**Points:** 500  
**Flag:** `slopped{quadratic_capsules_unlock_the_attestor}`

## Handout

- [`auditvm`](./auditvm) — Linux x86-64 PIE ELF (~27 KiB), stripped. The VM runner distributed for the challenge; the remote wraps it with a secp256k1 signing interface. SHA1 BuildID `2a77f8573617426c5a53ba63e20db266322f7b34`.


## Overview

Audit Spiral shipped as a Linux x86_64 VM runner, but the remote service wrapped that VM with a secp256k1 signing interface:

```text
load <capsulehex>
sign
target
admin <r> <s>
```

The obvious goal was to produce a valid admin signature. The non-obvious part was where the nonce weakness lived.

## First Observations

Capsule bytecode could emit a chosen 16-byte sample. If the output was shorter than 16 bytes, the signing command failed with a Python `ValueError`; with 16 or more bytes, the output was signed.

Initial attempts focused on direct nonce leakage, but the useful pattern emerged only after repeatedly signing the same fixed-output capsule.

## The Nonce Pattern

Using a capsule that emitted sixteen zero bytes, we collected many signatures over the same kind of sample. For each ECDSA signature:

```text
k = (z + r*d) / s mod n
```

The nonce was not random. It followed a quadratic polynomial in the signing index:

```text
k_i = c0 + c1*i + c2*i^2
```

Substituting the ECDSA equation gives a linear system over the secp256k1 group order in the unknowns:

```text
d, c0, c1, c2
```

Four signatures are enough in theory, and collecting more made the solve easier to verify.

## Key Recovery

Solving the linear system recovered the static private key:

```text
0xa8118ccf6054821700c20bf08bd0b4cbe9bc4e4c140a619d86c0536692f417f
```

This matched the service public key:

```text
beca28a00a6eaac538fc75af63b68e07aa530f7fe93d534eb15d1a5a4a38e6380ba57795d2dfe2f7c86ec2b2ecd5e3a09e69db0b5f8bfdc26d331331f3f4e251
```

## Final Signature

After recovering the private key, the rest of the challenge was straightforward:

1. Ask the service for a fresh target digest.
2. Sign it locally with the recovered key.
3. Submit the signature with `admin <r> <s>`.

The service accepted the signature and returned:

```text
slopped{quadratic_capsules_unlock_the_attestor}
```

The final-stage solver is included at:

```text
reverse/audit-spiral/solve.py
```

It uses the recovered private key, asks the live service for a fresh target
digest, signs that digest locally with a small pure-Python secp256k1
implementation, and submits the resulting admin signature.

## Takeaways

The challenge rewarded observing nonce behavior over time rather than only inspecting one signature. Once the VM output was fixed, the quadratic nonce progression became the exploitable structure.
