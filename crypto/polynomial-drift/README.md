# Polynomial Drift

**Category:** Cryptography  
**Points:** 443  
**Flag:** `slopped{polyphase_masks_force_a_hidden_number_pivot}`

## Handout

- [`polydrift`](./polydrift) — Linux x86-64 PIE ELF (~473 KiB), stripped. The Rust TCP service binary distributed for the challenge. SHA1 BuildID `26738268efd95276473e549b78d75bc385bfa3b8`.


## Overview

Polynomial Drift exposed a Rust TCP service built around a small capsule VM. A valid capsule could be committed repeatedly, and each commit produced an ECDSA signature over secp256k1.

The challenge was not to break ECDSA directly. The bug was that the VM output influenced visible low bits of the nonce. That turned repeated signatures into a hidden-number-problem instance.

## The Useful Capsule

We used a minimal valid capsule:

```text
504446540209008a0000000010163e474c709aa5f8
```

For bytecode pushing `(1, 2, 3, 4)`, the nonce leaked through the preview value:

```text
k & 0xffffff == (4 << 16) | (3 << 8) | preview
```

So each signature gave us the low 24 bits of the nonce.

## Turning Signatures Into HNP

ECDSA gives:

```text
s = k^-1 * (z + r*d) mod n
```

Rearranging:

```text
k = z/s + (r/s)*d mod n
```

Because the low 24 bits of `k` were known, we wrote:

```text
k = K + 2^24 * t
```

where `K` is the known low-bit portion. For each signature:

```text
(r/s)*d + (z/s - K) == 2^24 * t mod n
```

With enough signatures, this becomes a lattice/CVP problem. We collected more than 11 signatures and solved for the private key with `fpylll`.

The recovered main private key was:

```text
0xb94052b8ca127bc32e757e49dc37abcc55d0333186ef7e4dd96973439e8da570
```

It matched the remote public key:

```text
02cc74bc2c7013648ff52090c12ed29cf95ce79ab49506d6c16957cc04e660e488
```

## Getting the Flag

The `diag` key was a decoy. The final authorization used the main signing key recovered from the commit signatures.

The final message to sign was:

```python
SHA256(b"POLYPHASE|grant|" + sid.to_bytes(8, "big"))
```

After signing it locally, we sent the raw `r || s` signature with:

```text
auth <signature hex>
```

The service accepted the signature and returned:

```text
slopped{polyphase_masks_force_a_hidden_number_pivot}
```

## Takeaways

The important pivot was to stop treating the diagnostic key as the target and instead attack the main commit signatures. A small nonce leak over many signatures is enough to recover an ECDSA private key.
