# Finality Cache

**Category:** Blockchain
**Points:** 447
**Remote:** `nc 178.105.199.41 13357`
**Flag:** `slopped{wrapped_lane_offsets_expose_seal_keys_then_sign_recursive_checkpoints}`

## Summary

Finality Cache was a bridge-style receipt challenge. The remote service opened a session, handed out a receipt, let a local guardian binary attest the receipt, and then redeemed the signed claim through the vault logic.

The obvious target was the claim amount. The obstacle was that the receipt was internally committed: editing only the amount broke either the previewed claim consistency check or the guardian's VM commitment.

The successful exploit kept all three views of the receipt aligned:

1. Patch the claim amount reconstructed by the receipt VM.
2. Patch the committed amount in the receipt header.
3. Recompute and patch the 32-byte VM commitment.
4. Submit the repaired receipt for attestation.
5. Redeem the signed high-value claim.

## Artifacts

The original handout and extracted files are included:

```text
artifacts/cache.zip
artifacts/dist/BridgeVault.sol
artifacts/dist/guardian
artifacts/dist/sample.receipt
patch_receipt.py
```

`BridgeVault.sol` shows the claim verification and redemption behavior. `guardian` is the stripped local verifier used to recompute and sign a session receipt. `sample.receipt` is the bundled example receipt from the handout.

## Receipt Layout

The sample receipt starts with the `FCRA` magic and stores several fixed header fields before the lane program data. Two offsets mattered during the solve:

```text
0x20..0x27  committed amount, little-endian uint64
0x3c..0x5b  VM commitment digest
```

In the bundled sample receipt:

```text
offset 0x20: 204e000000000000 = 20000
offset 0x3c: ed51118dbc7e4487988c793bc154352c6596cd6a5616ccea2f5fba9ba9055787
```

Changing only the header amount was not enough. The guardian previewed the claim produced by the receipt VM and rejected inconsistent receipts with:

```text
preview amount mismatch
```

Changing only the lane data was also not enough, because the VM commitment no longer matched:

```text
ERR bad vm commitment
```

## Amount Mutation

The target amount was `80000`.

The committed header amount was patched from:

```text
20 4e 00 00 00 00 00 00  # 20000
```

to:

```text
80 38 01 00 00 00 00 00  # 80000
```

In the event-time session receipt, the lane program also exposed the claim amount as the varint:

```text
a0 9c 01  # 20000
```

That was changed to:

```text
80 f1 04  # 80000
```

The included `patch_receipt.py` performs the header patch, searches for the lane varint, and accepts an explicit `--lane-offset` for session receipts where the value is found during analysis.

## Commitment Repair

After the semantic amount changes, the 32-byte VM commitment had to be recomputed. The fastest reliable route during the solve was to let the local `guardian` do the hard part.

The guardian recomputed the digest internally before comparing it against the receipt header. Running it under `gdb` and breaking around the recomputation point near `0x401a7a` exposed the new digest. That digest was then patched back into:

```text
receipt[0x3c:0x5c]
```

The helper supports that final insertion:

```bash
python3 patch_receipt.py \
  --input session.receipt \
  --output repaired.receipt \
  --lane-offset 0x... \
  --digest-hex <32-byte-recomputed-digest>
```

Without `--digest-hex`, the script writes the amount-mutated receipt and prints a reminder that the guardian commitment still needs to be repaired.

## Reproduction

The event-time solve flow was:

```text
1. Fetch the remote session receipt.
2. Patch the lane amount varint from 20000 to 80000.
3. Patch the committed amount at offset 0x20 to little-endian 80000.
4. Run the local guardian under gdb and dump the recomputed VM commitment.
5. Patch the digest at offset 0x3c.
6. Submit the repaired receipt to attest.
7. Redeem the signed claim.
```

The successful redemption returned:

```text
slopped{wrapped_lane_offsets_expose_seal_keys_then_sign_recursive_checkpoints}
```

## Takeaway

The lane map looked fixed, but the trusted commitment was local and recomputable. Once the receipt VM output, committed amount, and digest were all kept consistent, the relayer signed a claim for the higher amount.
