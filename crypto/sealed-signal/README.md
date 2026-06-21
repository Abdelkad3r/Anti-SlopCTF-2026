# Sealed Signal

**Category:** Cryptography
**Points:** 459
**Flag:** `slopped{cbc_mac_capsule_splice_last_claim_wins}`

## Summary

Sealed Signal was a WebSocket cryptography challenge built around a custom relay
protocol. The UI let a user open an eight-character room, seal a resume capsule,
resume from that capsule, and ask for the flag. It also exposed a second feature:
signing a "cache blob" into a cache capsule.

The vulnerability was that both capsule families used compatible CBC-MAC state.
The cache capsule signer prepended a fixed 16-byte header before the user blob,
then returned the MAC. That let us use it as a chosen-message CBC-MAC oracle and
splice together a valid MAC for a forbidden resume capsule:

```text
kind=resume&role=root&scope=flag&room=flagroom&cache=flagroom&pad=...
```

The important twist was that `role=admin&scope=flag` was not enough. It resumed
successfully, but the flag endpoint still replied `admins only`. The winning
role was `root`, with `scope=flag`.

## Folder Contents

- [`relay-client.js`](relay-client.js): browser protocol client from the service
- [`sample-session.r1t`](sample-session.r1t): captured relay traffic
- [`exploit.py`](exploit.py): clean end-to-end solver
- [`artifacts.md`](artifacts.md): artifact notes and hashes

## 1. Recon the Web Client

The landing page described the challenge mechanics:

```text
Boutique relay tickets still use the low-latency room cache, but ops now also
signs reconnect cache capsules for telemetry. The browser keeps your room
casing, the backbone still folds labels case-insensitively, and flagroom remains
admin-only.
```

The client loaded `/app.js`. Saving that file as `relay-client.js` gave us the
full wire protocol.

The WebSocket endpoint is:

```text
ws://178.105.199.41:20013/ws
```

The page exposed these user actions:

- `HELLO`: connect with a nickname
- `OPEN`: open a draft for an eight-byte room
- `SEAL`: seal the latest draft and receive a resume token plus resume capsule
- `RESUME`: resume from token plus capsule
- `FLAGREQ`: ask for the flag
- `CAPSULE`: ask the cache signer to sign a cache blob

## 2. Reverse the Relay Frame Format

The frame format is simple once `/app.js` is read:

```text
R1 || nibble_swap(op || xid_le16 || varint(payload_len) || payload || crc16_le)
```

Each payload is a sequence of tagged fields:

```text
tag || varint(length) || value
```

Important tags:

| Name | Tag |
| --- | --- |
| `ROOM` | `0x04` |
| `DRAFT` | `0x05` |
| `TOKEN` | `0x06` |
| `ROLE` | `0x07` |
| `SCOPE` | `0x08` |
| `FLAG` | `0x0a` |
| `BLOB` | `0x0d` |
| `CAPSULE` | `0x0e` |

Important opcodes:

| Name | Opcode |
| --- | --- |
| `HELLO` / `HELLO_ACK` | `0x10` / `0x11` |
| `OPEN` / `OPENED` | `0x20` / `0x21` |
| `SEAL` / `SEALED` | `0x30` / `0x31` |
| `RESUME` / `RESUMED` | `0x40` / `0x41` |
| `FLAGREQ` / `FLAG` | `0x50` / `0x51` |
| `CAPSULE` / `CAPPED` | `0x60` / `0x61` |
| `ERROR` | `0x7f` |

After `HELLO_ACK`, the server provides a one-byte dialect. All later opcodes are
XORed with that dialect byte on the wire. The frame bytes after `R1` are also
nibble-swapped, and the CRC is CRC16-CCITT over the unswapped body.

The included solver implements this framing directly.

## 3. Observe a Normal Resume Capsule

Opening and sealing `flagroom` as a normal user gives a valid token and capsule.
The resume capsule plaintext is visible because it is not encrypted; the last 16
bytes are the MAC.

A normal sealed capsule has the shape:

```text
kind=resume&role=user&scope=chat&room=flagroom&cache=flagroom&pad=...
<16-byte MAC>
```

Resuming it works, but `FLAGREQ` does not return the flag because the role and
scope are not privileged.

## 4. Inspect the Cache Capsule Signer

The UI also signs arbitrary cache blobs. The browser sends opcode `CAPSULE` with
tag `BLOB`, and the response contains a `CAPSULE` field.

For an attacker-chosen `blob`, the returned cache capsule starts with:

```text
CACHE::SIGNME::! || blob || mac
```

`CACHE::SIGNME::!` is exactly 16 bytes. Asking the cache signer to sign an empty
blob returns the CBC-MAC state after this fixed header:

```python
H = sign_cache_blob(b"")
```

This state is the bridge between the cache-signing oracle and resume-capsule
MACs.

## 5. Why the Signer Filter Is Not Enough

The cache signer rejects obvious forbidden blobs containing `scope=flag`. A
direct request for a root flag resume plaintext is therefore blocked.

The target resume plaintext is five 16-byte blocks:

```text
P0 = b"kind=resume&role"
P1 = b"=root&scope=fla"
P2 = b"g&room=flagroom&"
P3 = b"cache=flagroom&p"
P4 = b"ad=AAAAAAAAAAAAA"
```

The forbidden substring `scope=flag` appears across block boundaries, so the
filter can be avoided by signing different-looking intermediate blocks that
produce the same CBC-MAC chaining states.

## 6. CBC-MAC Splice

Let `E` be the AES block operation used inside CBC-MAC and let `H` be the state
after the fixed cache header:

```text
H = MAC("CACHE::SIGNME::!")
```

A cache signing query for blob block `B0` starts from state `H`:

```text
state_1 = E(H xor B0)
```

We want the resume MAC state after target block `P0` from a zero IV:

```text
target_state_1 = E(P0)
```

Choose:

```text
B0 = P0 xor H
```

Then:

```text
E(H xor B0) = E(H xor P0 xor H) = E(P0)
```

So the first cache-signing query:

```text
(P0 xor H) || P1
```

returns the same chaining state as a real resume MAC after `P0 || P1`. Call that
returned tag `T1`.

To continue from `P2`, make a second cache-signing query whose first block
cancels the cache header again:

```text
X = T1 xor P2 xor H
```

The signer processes:

```text
H xor X = H xor T1 xor P2 xor H = T1 xor P2
```

which is exactly the next CBC-MAC input for the target resume message. Therefore
the second query:

```text
X || P3 || P4
```

returns the valid MAC for:

```text
P0 || P1 || P2 || P3 || P4
```

Neither cache-signing query contains the literal forbidden substring
`scope=flag`, but the forged resume plaintext does.

## 7. Build the Winning Capsule

The final plaintext is:

```text
kind=resume&role=root&scope=flag&room=flagroom&cache=flagroom&pad=AAAAAAAAAAAAA
```

It is exactly 80 bytes, or five AES blocks. The forged capsule is:

```text
target_plaintext || forged_mac
```

Use the legitimate token from sealing `flagroom`, but replace the legitimate
capsule with the forged one:

```text
RESUME(token, forged_capsule)
FLAGREQ()
```

The server accepts the resume state:

```text
role=root scope=flag room=flagroom
```

Then `FLAGREQ` returns:

```text
slopped{cbc_mac_capsule_splice_last_claim_wins}
```

## Reproduction

Install the WebSocket dependency if needed:

```bash
python3 -m pip install websockets
```

Run the solver from this folder:

```bash
cd crypto/sealed-signal
python3 exploit.py http://178.105.199.41:20013
```

Expected output:

```text
resumed: root flag flagroom
slopped{cbc_mac_capsule_splice_last_claim_wins}
```

## Takeaways

CBC-MAC is only safe for fixed-domain messages when the domain separation is
real. Here, the cache capsule and resume capsule MACs were close enough that a
chosen-message oracle in one domain could manufacture a valid tag in the other.
The fixed cache header did not save the design because it was one full block and
could be algebraically cancelled with `P0 xor H`.
