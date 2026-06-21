# Parallax Cartridge

**Category:** Reverse
**Points:** 355
**Flag:** `slopped{quiet_tracks_hide_in_hash_padded_resume_tapes}`

## Handout

- [`parallax.zip`](./parallax.zip) - original challenge archive. SHA256 `929e3bfb9a3c5e8f3aef47ae7760b42e8c94ad95cf090004a718304708108a01`.
- [`starter.qar`](./starter.qar) - starter cartridge. SHA256 `745eaaf2e5ae12ddc4bfd14bd6ad041572a38ff9915d4c178142d288b12222bc`.
- [`parallax-cartridge`](./parallax-cartridge) - stripped static Go service binary. SHA256 `4cbddae4588ad2673d5475ff7d01cd4d0276b225eeacadc14f1f3b0f49292eef`.
- [`solve.py`](./solve.py) - reproduces the token forgery and cartridge switch.

## Solver

Run the exploit against the original remote:

```bash
python3 solve.py --host 178.105.199.41 --port 13347
```

The script can also stop before networking and write the mutated cartridge:

```bash
python3 solve.py --offline --write-mutated /tmp/parallax-quiet.qar
```

## Overview

Parallax Cartridge was a VM/state-continuation challenge. The server accepted two commands:

```text
BOOT <base64-qar>
STEP <base64-qar> <base64-token>
```

`BOOT` audited a cartridge and returned a resume token. `STEP` accepted a cartridge plus that token and continued execution. The intended split was clear from the challenge text: one lane was certified, another lane continued.

The bug was exactly there. The cartridge had a visible program that audit approved, but it also had a `quiet` record that could make the runner select a hidden dictionary bank for the final instruction. The second bug was in the resume token: it used a raw SHA-256 prefix MAC, so the token could be length-extended.

Combining both bugs let us boot the clean cartridge, forge a stronger resume token, then step a quiet-bank cartridge that executed the hidden answer opcode.

## Cartridge Layout

The starter file begins with `QAR5` and then length records:

```text
0x004 LREC dict  len=256 data=0x00f
0x10f LREC prog  len=5   data=0x11a
0x11f LREC mesh  len=32  data=0x12a
0x14a LREC quiet len=8   data=0x156
0x15e LREC note  len=20  data=0x169
0x17d QDIR ...
```

The `dict` record is a table of 64 four-byte VM cells. The visible `prog` record expands to:

```text
[0, 1, 2, 3, 4]
```

Cell `4` is harmless for audit. The hidden lane we needed was cell `36`, which is `4 + 32`. In the handout, setting bit 0 of byte 1 in the `quiet` data made the runner resolve the last visible index through that quiet bank:

```python
mutated[0x156 + 1] |= 1
```

After that mutation, the audited program was still effectively `[0, 1, 2, 3, 4]`, but the runner's real program was:

```text
[0, 1, 2, 3, 36]
```

The runner cookie was computed over those VM cells:

```python
runner_cookie = SHA256(b"parallax/runner-cookie/v5" + runner_program)[:4]
```

## Token Weakness

Reversing the Go binary showed state resume tokens ending with a 32-byte SHA-256 digest. The construction was a prefix MAC:

```text
SHA256(secret || token_body)
```

The server secret was 32 bytes, but the secret value was not needed. SHA-256 exposes a Merkle-Damgard length-extension property: knowing the final digest of `secret || token_body` lets us compute a valid digest for:

```text
secret || token_body || glue_padding || attacker_suffix
```

The appended suffix was a short decoded state tape:

```text
f0 01 01                # enable the debug/answer path
f0 06 <runner_cookie>   # install the hidden runner cookie
```

The state decoder accepted duplicate fields, and the later field values won. That made the forged token authorize the mutated runner state.

## Exploit Steps

1. Parse `starter.qar` and locate the `dict`, `prog`, and `quiet` records.
2. Mutate the `quiet` record by setting `quiet[1] |= 1`.
3. Decode the visible program indices from the packed `prog` record.
4. Replace the final visible index `4` with hidden-bank index `36`.
5. Build the hidden runner program from dictionary cells `[0, 1, 2, 3, 36]`.
6. Compute the 4-byte runner cookie with `SHA256("parallax/runner-cookie/v5" || runner_program)[:4]`.
7. Send `BOOT` with the original cartridge and save the returned token.
8. Length-extend the token MAC, appending the debug flag and hidden runner cookie fields.
9. Send `STEP` with the mutated cartridge and forged token.

The remote returned:

```text
OK FLAG slopped{quiet_tracks_hide_in_hash_padded_resume_tapes}
```

## Takeaways

The first lesson is that audit and execution must parse the same object in the same way. Here, audit certified the visible lane while execution could be shifted into a quiet bank. The second lesson is older but just as sharp: `SHA256(secret || message)` is not a safe MAC. Use HMAC or an AEAD construction for resumable state.
