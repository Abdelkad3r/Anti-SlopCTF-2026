# Finality Cache

**Category:** Blockchain  
**Points:** 447  
**Flag:** `slopped{wrapped_lane_offsets_expose_seal_keys_then_sign_recursive_checkpoints}`

## Overview

Finality Cache presented a bridge-style receipt flow. A guardian binary verified a receipt VM commitment, reconstructed a signed claim, and allowed the relayer to attest and redeem.

The obvious target was the claim amount. The challenge was that simply editing the amount broke the VM commitment.

## Receipt Structure

The sample receipt contained:

- a committed amount in the header
- lane programs that reconstructed the claim
- a 32-byte VM commitment over the lane programs and metadata

Changing only the output amount caused:

```text
preview amount mismatch
```

Changing the lane bytes directly caused:

```text
ERR bad vm commitment
```

So the exploit needed to mutate both the claim data and the receipt commitment.

## Mutation

The target amount was `80000`.

The claim amount inside lane 0 was encoded as a varint. We changed:

```text
a0 9c 01    # 20000
```

to:

```text
80 f1 04    # 80000
```

The header committed amount was also patched to little-endian `80000`.

At that point the data was semantically correct, but the VM commitment still needed repair.

## Recomputing the Commitment

The guardian binary recomputed the 32-byte digest internally. Instead of fully reimplementing the commitment routine, we used the local guardian under `gdb` and stopped at the recomputation point around:

```text
0x401a7a
```

From there we dumped the recomputed digest and patched it back into the receipt at:

```text
0x3c..0x5b
```

Now the modified receipt passed both the VM commitment check and the amount consistency check.

## Solution Flow

The final reproduction path was:

1. Fetch the session sample receipt.
2. Patch the lane varint from `20000` to `80000`.
3. Patch the committed amount header to little-endian `80000`.
4. Recompute and patch the VM commitment.
5. Submit the repaired receipt to `attest`.
6. Redeem the high-value claim.

The service returned:

```text
slopped{wrapped_lane_offsets_expose_seal_keys_then_sign_recursive_checkpoints}
```

## Takeaways

The visible lane map looked fixed, but the trusted commitment was local and recomputable. Once the amount and digest were kept consistent, the relayer signed a redeemable high-value claim.
