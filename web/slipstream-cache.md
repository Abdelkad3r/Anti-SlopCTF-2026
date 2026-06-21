# Slipstream Cache

**Category:** Web / Cryptography
**Flag:** `slopped{split_parsers_make_signed_packages_liable}`

## Overview

Slipstream Cache presented a small package registry for `SPK1` bundles. The page
allowed uploading a package, inspecting the registry response, and triggering an
install run. The public sample package was the real handout: it contained enough
structure to recover the parser boundary, the signing model, and the internal
maintenance route used to retrieve the flag.

The important hint was:

```text
Stop guessing paths. Reverse the package format first; signedlen matters.
```

That turned the challenge from route guessing into a split-parser problem. The
registry verifier and install runtime did not agree on which bytes of the
manifest were security-relevant.

## Reversing the Package

The downloaded sample starts with an `SPK1` header followed by a `CRT1`
certificate, a small manifest, and an RSA signature block.

The useful fixed offsets in the sample were:

| Offset | Meaning |
| --- | --- |
| `0x000` | `SPK1` magic |
| `0x006` | start of `CRT1` certificate body |
| `0x0a` | certificate role/class byte |
| `0x121` | `signed_len` |
| `0x123` | `manifest_len` |
| `0x125` | manifest start |

Uploading the unmodified sample produced the verifier transcript:

```text
vendor=sample-vendor
role=public
kid=13889c7a
signed_len=19 manifest_len=32
name=lantern
cmd=static
signature=2a647c486013d259e0d91de6e27aa692
```

The manifest itself was TLV-like:

```text
01 0007 "lantern"
02 0006 "static"
04 000a "cache-warm"
```

Only the first 19 bytes were signed. Those bytes covered the `name` and `cmd`
fields, but the manifest length told the runtime to keep parsing beyond that.
That gap was the first vulnerability.

## Manifest Confusion

The original signed prefix and package signature could be preserved while
increasing `manifest_len` and appending extra TLVs after the signed region.

Appending a second command TLV changed install-time behavior even though the
registry still displayed the signed view as:

```json
{
  "name": "lantern",
  "cmd": "static"
}
```

Most guessed commands returned:

```text
unsupported runtime command
```

but `cmd=fetch` produced a different error:

```text
runtime url must stay on loopback
```

That identified an internal fetch primitive. The URL field was TLV tag `03`, so
the forged manifest became:

```text
<original manifest>
02 0005 "fetch"
03 001c "http://127.0.0.1:20024/..."
```

Using that package, the installer fetched loopback-only routes and returned the
response in its install log.

## Internal Discovery

Fetching `/internal/` over loopback revealed the maintenance interface:

```text
maintenance routes:
- /internal/blind-sign?role=operator&blinded=<hex>
- /internal/flag?cert=<b64>&sig=<b64>
```

The public route blocked direct access, so the forged `fetch` package was needed
for every call into this interface.

The blind-sign endpoint returned a CA public key and a raw RSA signature over the
provided blinded integer. Testing the bundled certificate showed the certificate
signature format:

```text
cert_sig^e mod n == SHA256(cert_body)
```

There was no PKCS#1 padding on the certificate signature. That made a standard
blind RSA signing attack enough to mint a modified certificate.

## Operator Certificate

The `CRT1` certificate body begins:

```text
43 52 54 31 01 0d 73 61 6d 70 6c 65 ...
CRT1       ^^
```

The byte after `CRT1` is the role/class byte. The sample used value `1`, which
parsed as `public`. Changing it to other values caused uploads to fail with:

```text
only public vendor packages may be uploaded
```

That error was useful: it confirmed the modified certificates still verified and
parsed, but the upload endpoint rejected non-public roles. The internal flag
route was the correct consumer for those certificates.

The operator role was value `2`. The final certificate forgery was:

1. Copy the sample `CRT1` certificate body.
2. Change the role byte from `1` to `2`.
3. Compute `SHA256(modified_cert_body)`.
4. Blind that integer with a random RSA factor.
5. Ask `/internal/blind-sign?role=operator&blinded=<hex>` to sign it.
6. Unblind the returned signature.
7. Send the full signed certificate to `/internal/flag`.

The flag route expected the certificate parameter to contain the full certificate
body plus its two-byte signature length and CA signature:

```text
cert = base64(cert_body || 0x0080 || ca_signature)
sig  = base64(ca_signature)
```

The response was:

```text
slopped{split_parsers_make_signed_packages_liable}
```

## Reproduction

The bundled artifacts include:

- [`sample.spk`](../artifacts/slipstream-cache/sample.spk), the downloaded
  sample package
- [`exploit.py`](../artifacts/slipstream-cache/exploit.py), a standalone solver
  using only Python's standard library

Run:

```bash
python3 artifacts/slipstream-cache/exploit.py http://178.105.199.41:20024
```

The script rebuilds the forged fetch package, discovers the internal routes,
uses the blind signer to mint the operator certificate, and prints the recovered
flag.

## Takeaways

The bug was not a weak signature by itself; it was a disagreement between two
parsers. The verifier honored `signed_len`, while the runtime honored the larger
`manifest_len`. Once unsigned TLVs could influence install behavior, the
loopback-only maintenance API became reachable. The raw RSA certificate signing
then made the operator certificate forgery mechanical.
