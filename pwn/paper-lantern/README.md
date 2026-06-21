# Paper Lantern

**Category:** Pwn
**Remote:** `nc 178.105.199.41 20000`
**Flag:** `slopped{faulted_crt_seams_burn_open}`

## Summary

Paper Lantern looked like a capsule VM challenge, but the real target was the CRT-RSA-FDH signer behind the capsule audit system. The signer refused to sign unsafe capsules directly, but the runtime trusted any capsule whose RSA-FDH signature verified.

The solve was:

1. Understand the capsule audit format.
2. Trigger a CRT signing fault for a safe capsule.
3. Factor the RSA modulus with the Bellcore attack.
4. Forge a valid signature for an unsafe `0x7f` record.
5. Run the signed unsafe capsule to print the flag.

## Handout

The original handout is included in [artifacts/paper-lantern.zip](artifacts/paper-lantern.zip). The extracted handout files are kept under the original `dist/` layout:

```text
artifacts/dist/capsule.py
artifacts/dist/paper_lantern
artifacts/dist/public_params.json
```

The final forge solver is included as [solve.py](solve.py).

## Protocol

The handout included `capsule.py`, which defined the frame types and record helpers. The important frame types were:

```text
FT_HELLO       0x10
FT_ACK_STRICT 0x12
FT_NEWCAP      0x20
FT_APPEND      0x21
FT_SIGN        0x22
FT_COMMENT     0x23
FT_RUN         0x24
```

Strict mode had to be enabled before useful capsule operations:

```python
client.send(FT_HELLO, b"\x01")
client.send(FT_ACK_STRICT)
```

The hidden flag record was opcode `0x7f`. `SIGN` rejected capsules containing this opcode, but `RUN` only checked whether the provided signature was valid for the capsule audit.

## Hash And Signature Model

The public parameters declared:

```json
{
  "scheme": "crt-rsa-fdh",
  "e": 65537,
  "signature_size": 64
}
```

The FDH message representative was:

```text
d = SHA256(audit)
m = SHA256("paper-lantern/v4:msg" + d) ||
    SHA256("paper-lantern/v4:aux" + d)
m = m mod n
```

So a valid signature was any `s` satisfying:

```text
s^e mod n == m
```

## Triggering The Fault

The comment/replay path could overflow into the signer fault controls. The working trigger started with:

```text
comment_literal(64 zero bytes)
comment_braid_fill(17, 0)
```

Then suffix XOR operations set the logical fault fields:

```text
enable   = 1
branch   = 0
amount   = 1
align    = 5
checksum = 107
```

Using this against a normal safe capsule produced a faulty CRT-RSA signature. The safe audit used during the solve was:

```text
T\x02hiH
```

## Factoring The Modulus

For a faulty CRT signature, one prime verifies correctly and the other does not. The Bellcore relation recovers a factor:

```text
g = gcd(sig^e - H(m), n)
```

The recovered factors were:

```text
p = 82757585072455028579685401889888615758895788003223315567334952176806753515189
q = 71296171568667776680278779905104901035842966603378173362597119862250613420693
```

After that, the private exponent was:

```text
d = e^-1 mod lcm(p-1, q-1)
```

## Forging The Unsafe Capsule

The unsafe capsule audit marker for a single `0x7f` record is:

```text
b"F"
```

The solver signs that audit locally, appends:

```python
rec_raw(0x7f) + rec_halt()
```

and sends the forged signature to `FT_RUN`.

## Reproduction

Run:

```bash
python3 solve.py 178.105.199.41 20000
```

The expected output is:

```text
slopped{faulted_crt_seams_burn_open}
```

## Takeaway

The unsafe opcode filter was placed on the signing path, not on the execution path. Once a single faulty CRT signature factored the public modulus, the attacker could sign the forbidden audit directly and make the runtime accept it.
