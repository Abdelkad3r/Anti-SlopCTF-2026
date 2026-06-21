# Slipstream Cache Artifacts

This web challenge folder contains the public sample package used for the solve
and a standalone reproduction script.

## Files

- [`sample.spk`](sample.spk)
  Public sample package downloaded from `/public/sample`.

- [`exploit.py`](exploit.py)
  Rebuilds the signed-length confusion package, uses the loopback fetch
  primitive to reach the maintenance routes, blinds an operator certificate
  digest, unblinds the CA signature, and retrieves the flag.

## Hashes

```text
cccff729431bb2aa3e4b047a51464d54dc5c4ade603acd655c109bc98fc139fc  sample.spk
```
