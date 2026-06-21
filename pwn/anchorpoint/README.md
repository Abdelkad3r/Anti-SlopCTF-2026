# Anchorpoint

**Category:** Pwn
**Points:** 448
**Remote:** `nc 178.105.199.41 20002`
**Flag:** `slopped{shadow_quote_ghash_rootcapsule}`

## Summary

Anchorpoint was a multi-stage pwn and crypto challenge. The first bug was a VM output overflow, but the overflow did not directly reach the flag. It only unlocked the conditions needed to attack two later verification layers: a quote/shadow signing path and an AES-GCM sealed capsule path.

The final exploit chain was:

1. Abuse opcode `0x50` to write past a 64-byte VM response buffer.
2. Corrupt adjacent service state so quote requests, shadow submission, capsule sealing, and nonce freezing were available.
3. Collect four ECDSA-like quote signatures.
4. Recover the quote private key from the affine nonce recurrence.
5. Forge the shadow proof.
6. Reuse sealed capsule nonces to recover GHASH material.
7. Forge the required `rootcaps|...` AES-GCM capsule.
8. Request the flag.

## Handout

The original handout is included in [artifacts/anchorpoint.zip](artifacts/anchorpoint.zip). The extracted files used during analysis are also included:

```text
artifacts/anchorpoint
artifacts/sample.apvm
```

The binary is a stripped 64-bit Linux ELF. The sample APVM file is a tiny program that is useful for confirming the VM framing and output behavior.

## Protocol And VM

The service speaks a small AP packet format:

```text
"AP" || type:u8 || length:u16le || checksum:u8 || payload
```

The checksum is not cryptographic. It mixes the packet type, payload length, and payload bytes with a rotate-left operation. After the initial info packet, the service gives enough VM seed material to encode new bytecode for the current connection.

The useful VM program shape was simple:

```text
0x10 <byte>  # load literal byte
0x50         # append/output byte
...
0x70         # halt
```

The bug was in the append/output path. Opcode `0x50` wrote output bytes into a 64-byte response buffer, but did not stop at 64 bytes. Bytes after the response landed in adjacent state fields.

The exploit used that overflow to set:

```text
response[64] = quote budget
response[67] = shadow unlock byte
```

In the full solve, additional nearby fields were used to raise capsule budget and freeze the seal nonce for the GCM stage.

## Quote Key Recovery

The quote endpoint returned payloads ending in a 64-byte ECDSA-like signature:

```text
quote_payload || r:32 || s:32
```

The signing nonce followed an affine recurrence:

```text
k[i+1] = a*k[i] + b
```

For an ECDSA-style signature,

```text
k[i] = (e[i] + r[i] * d) / s[i] mod n
```

where `d` is the private key. Substituting the affine relation across four signatures gives a quadratic equation in `d`:

```text
(k2 - k1)^2 = (k3 - k2) * (k1 - k0)
```

Solving that equation modulo the secp256k1 order recovered the quote private key. The candidate was verified by checking that `d*G` matched the x-only public key from the service info packet.

## Shadow Proof

The shadow verifier was BIP340-style. The message was derived from the quote chain, the epoch, a counter, and a crumb:

```text
chain[0] = 32 zero bytes
chain[i+1] = sha256(chain[i] || quote_payload[i])
crumb = tagged_hash("Anchorpoint/shadow-crumb", epoch || counter || chain)
msg = tagged_hash("Anchorpoint/shadow-msg", epoch || counter || chain || crumb)
```

With the recovered quote key, we could sign this message and submit:

```text
a7 34 || counter || crumb || schnorr_signature
```

That passed the shadow gate, but it still did not return the flag. A regular capsule submission produced:

```text
root capsule required
```

and a normal post-shadow capsule failed with:

```text
root aad
```

Those errors were the clue that the final path required a different AAD, not just a valid regular capsule.

## Root Capsule Forgery

The normal capsule AAD was:

```text
capsule|epoch
```

The final capsule had to use:

```text
rootcaps|epoch|counter_byte
```

The VM overflow made it possible to freeze the seal nonce. With two one-block capsules sealed under the same nonce and same AAD, and with known plaintexts, AES-GCM breaks in the usual way.

For one-block messages with identical nonce and AAD:

```text
tag0 xor tag1 = (ciphertext0 xor ciphertext1) * H^2
```

So the exploit recovers:

```text
H^2 = (tag0 xor tag1) / (ciphertext0 xor ciphertext1)
H = sqrt(H^2)
E_K(J0) = tag0 xor GHASH(H, aad0, ciphertext0)
```

After that, a valid tag can be created for the `rootcaps|...` AAD and the chosen root ciphertext. Submitting the shadow proof and forged root capsule in the same connection sets both gates.

## Reproduction

The reference exploit is included as [exploit.py](exploit.py). It preserves the AP framing, VM encoder, quote-key recovery, shadow-signature construction, and GHASH forgery helpers from the solve.

Run the first stage:

```bash
python3 exploit.py 178.105.199.41 20002
```

That recovers the quote key and builds the shadow packet. The event-time final script also derived the 16-byte root target during the root capsule stage and passed it into the GCM forge. The repository script exposes that final input explicitly:

```bash
python3 exploit.py 178.105.199.41 20002 --root-plain-hex <16-byte-root-target-hex>
```

During the solve, the successful run submitted the forged root capsule and returned:

```text
slopped{shadow_quote_ghash_rootcapsule}
```

## Takeaway

The memory corruption bug was only the entry point. The actual flag required respecting the service's cryptographic state machine: recover the quote key, satisfy shadow, then forge a GCM-authenticated root capsule with the exact root AAD.
