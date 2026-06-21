# Graceful Exit

**Category:** Pwn
**Points:** 490
**Remote:** `nc 178.105.199.41 20001`
**Flag:** `slopped{previewed_offsets_can_reseal_reports}`

## Summary

Graceful Exit used framed `GORF` packets and a capsule preview format. The solve needed two independent bugs:

1. A signed negative back-reference in the `VIEW` stream leaked data from before the preview buffer.
2. The `seal` path copied symbol bytes over a 0x80-byte plan object, letting us replace the report pointer and length.

Once the flag page pointer and length were leaked, the plan overwrite turned the normal `fetch` command into a flag read.

## Handout

The original handout is included in [artifacts/graceful.zip](artifacts/graceful.zip). The extracted files used during the solve are:

```text
artifacts/graceful_exit
artifacts/sample.gfc
```

The solver is included as [solve.py](solve.py).

## Packet Framing

Every request is a `GORF` frame:

```text
"GORF" || type:u16le || flags:u16le || length:u32le || crc:u32le || body
```

Before `hello`, the CRC seed is fixed:

```text
0x714a5c21
```

After `hello`, the response includes a nonce:

```text
nonce=<8 hex digits>
```

That nonce becomes the CRC seed for all later frames. Missing this detail causes otherwise valid frames to be rejected.

## Building GFC2 Capsules

The capsule file starts with a `GFC2` header and a section table. The exploit only needed minimal sections:

```text
LITR  literal data
CODE  bytecode entries
SYMS  symbol metadata
FIXS  fixup data
VIEW  preview stream
```

The helper in `solve.py` builds valid capsules and recomputes the two body/table checksums used by the loader.

## Leak Stage

The preview engine kept a seed block immediately before the preview output buffer. The `VIEW` stream accepted a signed back-copy offset, including negative values.

The leaking view stream was:

```text
0x11 || sleb(-0x20) || uleb(0x80) || 0x00
```

That asked the preview renderer to copy 0x80 bytes starting at `preview_buffer - 0x20`.

The first 32 bytes of the leak included:

```text
leak[0:8]    XOR seed
leak[8:16]   encoded flag page pointer
leak[24:28]  flag length
```

The flag pointer was decoded as:

```text
flag_ptr = leak_qword0 ^ leak_qword1 ^ 0x736565645f676f72
```

## Overwrite Stage

The second capsule used symbol bytes as a fake plan object. The vulnerable `seal` path copied that symbol name over the existing 0x80-byte plan allocation.

The controlled fields were:

```text
plan + 0x30  cookie
plan + 0x38  report_ptr
plan + 0x40  report_len
plan + 0x7c  finished flag
```

By setting `report_ptr` to the leaked flag page and `report_len` to the leaked length, the later `fetch` command returned the flag as a normal report.

## Reproduction

Run the exploit:

```bash
python3 solve.py 178.105.199.41 20001
```

The solver performs the full chain:

1. Send `hello` and parse the nonce.
2. Load the leak capsule.
3. Render preview and decode the flag pointer.
4. Load the fake-plan capsule.
5. Run `audit`.
6. Run `seal`.
7. Call `fetch` with the overwritten cookie.

The remote returned:

```text
slopped{previewed_offsets_can_reseal_reports}
```

## Takeaway

Neither bug was enough by itself. The negative preview offset gave an address disclosure, and the report-plan overwrite turned that disclosure into a controlled read through an intended output path.
