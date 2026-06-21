# Graceful Exit

**Category:** Pwn  
**Points:** 490  
**Flag:** `slopped{previewed_offsets_can_reseal_reports}`

## Overview

Graceful Exit used framed `GORF` messages and a capsule preview system. The exploit combined an information leak from a signed negative back-reference with an overwrite in the report sealing path.

The final primitive was turning `fetch` into an arbitrary read from the in-memory flag page.

## Preview Leak

After `hello`, the service printed a nonce. That nonce became the request CRC seed for later frames.

The preview VM kept a small seed block on the stack before the preview buffer. The `VIEW` stream accepted a signed negative back-reference, which allowed reads from before the start of the preview buffer.

Using a back-reference around:

```text
preview_buffer - 0x20
```

we could leak the seed block. The leak contained:

- an XOR seed
- an encoded flag page pointer
- the plan cookie
- the flag length

The flag pointer was decoded with:

```text
flag_ptr = leak_qword0 ^ leak_qword1 ^ 0x736565645f676f72
```

## Plan Overwrite

The second bug was in `seal`. It copied a symbol name directly over the 0x80-byte plan object. By making the symbol name exactly the right size, we could overwrite:

- `plan.cookie`
- `plan.report_ptr`
- `plan.report_len`
- `plan.finished`

That turned the later `fetch` command into a read from an attacker-controlled pointer.

## Exploit Flow

The reliable order was:

1. Send `hello` and capture the CRC seed.
2. Load a preview-leak capsule.
3. Use the negative back-reference to leak the seed block.
4. Decode the flag pointer and length.
5. Load a second capsule with a fake plan object encoded as symbol bytes.
6. Run `audit`.
7. Run `seal` to overwrite the plan.
8. Call `fetch` with the overwritten cookie.

Because `plan.report_ptr` now pointed to the flag page and `plan.report_len` matched the leaked flag length, `fetch` returned:

```text
slopped{previewed_offsets_can_reseal_reports}
```

## Takeaways

The challenge was a clean two-stage exploit: first leak the hidden pointer, then reuse a separate overwrite to redirect a legitimate output path. Neither bug alone was enough; together they formed a controlled flag read.
