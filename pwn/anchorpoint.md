# Anchorpoint

**Category:** Pwn  
**Points:** 448  
**Flag:** `slopped{shadow_quote_ghash_rootcapsule}`

## Overview

Anchorpoint combined a VM memory corruption bug with multiple cryptographic gates. The exploit had to progress through three layers:

1. Use a VM output overflow to corrupt service state.
2. Recover and use the quote signing key to pass the shadow gate.
3. Exploit repeated AES-GCM nonces to forge the root capsule.

The final flag was gated behind the rootcaps capsule path, not just the regular shadow path.

## State Corruption

The VM opcode `0x50` wrote response bytes past a 64-byte response buffer and into adjacent stack state. By carefully choosing output length and content, we could overwrite useful state fields:

- quote budget
- shadow lock and cookie
- capsule budget
- nonce-freeze flag
- seal-cookie bytes

This corruption gave enough room to request the signatures and ciphertexts needed for the crypto half of the solve.

## Recovering the Quote Key

The quote signatures used an ECDSA-like scheme with an affine nonce recurrence. Four quote signatures were enough to solve the recurrence and recover the quote private key.

The shadow verifier used a BIP340-style Schnorr check over a quote-chain-derived message. During exploitation, the chain had to be maintained as:

```text
sha256(chain || quote_payload)
```

With the recovered quote key, we could produce a valid shadow submission.

## Forging the Root Capsule

Passing shadow was not sufficient. A normal `capsule|epoch` submission still failed because the final bit required a `rootcaps|epoch|counter_byte` capsule.

The service allowed us to freeze the seal nonce. Under AES-GCM, nonce reuse is fatal. We requested two known 16-byte plaintext capsules under the same nonce and used their ciphertext and tag differences to recover the GHASH key material:

1. Recover `H^2` from known plaintext/ciphertext/tag differences.
2. Derive `H`.
3. Recover `E_K(J0)`.
4. Forge a valid tag for the rootcaps AAD and ciphertext.

## Solution Flow

The clean exploit order was:

1. Trigger the VM output overflow and corrupt the needed state fields.
2. Collect four quote signatures.
3. Recover the quote key from the nonce recurrence.
4. Freeze the seal nonce and collect two known-plaintext capsules.
5. Recover the GCM authentication material.
6. Submit the valid shadow proof.
7. Forge and submit the rootcaps capsule.
8. Request the flag.

The service returned:

```text
slopped{shadow_quote_ghash_rootcapsule}
```

## Takeaways

Anchorpoint was a good example of a pwn challenge where memory corruption was only the first step. The overflow enabled the cryptographic attack surface, and the final solve required both key recovery and AES-GCM nonce-reuse forgery.
