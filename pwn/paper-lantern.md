# Paper Lantern

**Category:** Pwn  
**Flag:** `slopped{faulted_crt_seams_burn_open}`

## Overview

Paper Lantern looked like a capsule VM challenge, but the real target was the RSA signing implementation behind it. The service signed safe capsule audits with CRT-RSA-FDH and refused to sign unsafe records directly.

The goal was to obtain a valid signature for an unsafe `0x7f` record that `RUN` would execute.

## Signing Model

The verifier hashed an audit as:

```text
d = SHA256(audit)
H(m) = SHA256("paper-lantern/v4:msg" + d) ||
       SHA256("paper-lantern/v4:aux" + d)
```

The result was reduced modulo `n`, and signatures were checked as RSA-FDH values.

The `SIGN` command rejected unsafe opcode `0x7f`, but `RUN` trusted any capsule with a valid RSA-FDH signature. That meant we needed to forge a valid signature for a capsule containing `0x7f`.

## The Fault

The service used CRT-RSA for signing. If we could trigger a signing fault, the classic Bellcore attack applies:

```text
gcd(sig^e - H(m), n)
```

When a CRT signature is wrong modulo one prime but correct modulo the other, that gcd reveals a nontrivial factor of `n`.

The fault was enabled through a replay/comment overflow. The useful trigger was:

```text
literal(64 zero bytes) + braid_fill(17, 0)
```

Then suffix XORs set the logical fields:

```text
enable = 1
branch = 0
amount = 1
align = 5
checksum = 107
```

This caused the signer to produce a faulty signature for a normal safe capsule.

## Factoring and Forging

The recovered factors were:

```text
p = 82757585072455028579685401889888615758895788003223315567334952176806753515189
q = 71296171568667776680278779905104901035842966603378173362597119862250613420693
```

With `p` and `q`, we computed the private exponent and forged a signature for the unsafe audit containing the record stream:

```text
7f
```

The forged audit marker used during the solve was:

```text
b"F"
```

## Solution

The final flow was:

1. Get a safe signature for `T\x02hiH`.
2. Trigger the CRT fault.
3. Factor `n` with `gcd(sig^e - H(m), n)`.
4. Forge a signature for the unsafe `0x7f` record.
5. Run the capsule.

The service executed the hidden record and returned:

```text
slopped{faulted_crt_seams_burn_open}
```

## Takeaways

The unsafe opcode filter was not enough because the runtime trusted signatures. A single faulty CRT-RSA signature was enough to factor the modulus and sign arbitrary capsule audits.
