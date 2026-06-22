# Geoguessr

**Category:** OSINT
**Points:** 487
**Service:** `http://178.105.199.41:13337/`
**Flag:** `slopped{h0w_d0_agent5_sl0p_nmpz?}`

## Summary

Geoguessr looked like a pure location hunt, but the client-side code made it much more deterministic than a normal map guessing game. Each panorama protected one encrypted Shamir share. A guess did not need to hit the exact latitude and longitude; it only needed to land in the correct H3 resolution-8 cell.

The solve was:

1. Dump the client metadata from `/challs.json` and `/levels.json`.
2. Read the browser logic for how coordinates became a key.
3. Identify candidate locations from the panoramas.
4. Search nearby H3 cells until the Argon2-derived key matched the published hash.
5. Decrypt nine shares.
6. Recombine the shares and decrypt the final ciphertext.

The threshold was nine out of ten, so the last unsolved panorama was unnecessary once nine valid keys were recovered.

## Artifacts

The useful challenge metadata and solve files are included here:

```text
artifacts/challs.json
artifacts/levels.json
artifacts/geoguessr_hits.json
artifacts/solve-memory.md
solve.py
tools/geoguessr_check.py
tools/geoguessr_scan.py
tools/geoguessr_solve.py
requirements.txt
```

`challs.json` contains the per-panorama target hashes and encrypted shares. `levels.json` contains the global Argon2, H3, Shamir threshold, and final ciphertext parameters. `geoguessr_hits.json` is the set of nine verified Argon2 keys used for the final solve.

## Client Model

The panorama route loaded a challenge by slug, then accepted a clicked or manually entered coordinate. The important client-side sequence was:

```text
lat/lon
  -> H3 cell at resolution 8
  -> Argon2d(password=cell, salt=name.padEnd(8, "0"))
  -> sha256(raw_key_hex)
  -> compare against challs.json[name].sha256
```

The level parameters were:

```text
Argon2 time cost: 3
Argon2 memory:    8192
H3 resolution:    8
Threshold:        9 shares
```

If the hash matched, the raw 16-byte Argon2 output was used as an AES-CBC key to decrypt that challenge's share. The final flag was another AES-CBC ciphertext, with the key reconstructed from the Shamir shares.

## Location Workflow

Because the verifier worked at H3 cell granularity, we only needed enough OSINT confidence to search the right neighborhood. The helper script starts from a candidate coordinate, expands an H3 disk, derives the same Argon2 key the browser would derive, and stops when the published SHA-256 target matches.

Examples from the solve:

```bash
python3 tools/geoguessr_check.py left -41.4395 147.140833 -r 12 -j 8
python3 tools/geoguessr_check.py ferris-wheel 37.7867 20.8999 -r 45 -j 8
python3 tools/geoguessr_check.py truck 47.4515 105.0535 -r 35 -j 8
```

Useful anchors:

| Challenge | Location clue used |
| --- | --- |
| `left` | St John's Anglican Church near Elizabeth and St John, Launceston |
| `ferris-wheel` | Zakynthos harbor |
| `truck` | Road in Mongolia near Ondorshireet |

The final key file contains nine hits:

```text
cat
sanity
police
bus
bar
border
left
ferris-wheel
truck
```

## Share Recovery

The decrypted shares were double padded, so the solver strips PKCS-style padding twice: once after AES-CBC decryption and once again around the share payload.

The client-side Shamir implementation used GF(256) over the AES polynomial:

```text
polynomial = 0x11b
generator  = 3
```

Each decrypted share stores its Shamir x-coordinate as the final byte. The solver interpolates the first nine recovered shares at x=0 to recover the final AES key:

```text
bf957a556e1c5f6b5836688a1798d9b2
```

That key decrypts the final level ciphertext.

## Reproduction

Install the small Python dependencies:

```bash
python3 -m venv .venv
. .venv/bin/activate
pip install -r requirements.txt
```

Run the final combiner from this directory:

```bash
python3 solve.py
```

Expected output:

```text
cat          share=b28dd0313eebeed427ffd5b6f9c7ba45e4 x=228
ferris-wheel share=405b2051cf851dc4e34fcab4eb93e2451c x=28
police       share=53dc2393e51b46d95dbc532cee3583d97b x=123
sanity       share=2643491c421f3dcc51ea64c71c979fa7dd x=221
truck        share=c5ba99075102e8d72542b6a2b8e630310c x=12
left         share=98e5109faeb42149418077711e2908c050 x=80
bus          share=4f1c429c4db4a097e564fe353155521fba x=186
bar          share=17e3c0f28e2a49bcc3b046b6c3a5745a58 x=88
border       share=8ead5852e7b3b5685c1876082e048ac113 x=19
9 shares
slopped{h0w_d0_agent5_sl0p_nmpz?}
```

## Takeaway

The OSINT work solved the locations, but the client-side crypto made the result verifiable. Once the H3 and Argon2 check was understood, every candidate coordinate could be tested locally and the final flag recovery became a normal threshold-secret reconstruction problem.
