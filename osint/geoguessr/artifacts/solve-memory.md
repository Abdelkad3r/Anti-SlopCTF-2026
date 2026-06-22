# Writeup Memory

## Final Vulnerability / Trick

- The challenge encrypted 10 Shamir shares behind per-location Argon2-derived
  AES keys. Any 9 correct geolocations were enough to recover the flag.

## Why It Works

- Each panorama corresponds to one real-world location. The client checks a
  guessed H3 resolution-8 cell by deriving an Argon2 key from the cell string
  and challenge name, then matching its SHA-256 against the published target.
- A correct key decrypts one padded share. Combining any 9 unpadded shares via
  the bundled GF(256) Shamir implementation yields the final AES key.

## Solve Path

1. Dumped the web assets, challenge metadata, panoramas, and crypto parameters
   into `/tmp/geoguessr_live`.
2. Reimplemented the H3/Argon2 checker in `tools/geoguessr_check.py` and the
   final share combiner/decryptor in `tools/geoguessr_solve.py`.
3. Solved 9 locations from panorama clues, verified each via H3 disk search,
   decrypted 9 shares, and recovered the flag.

## Key Commands

```bash
python3 tools/geoguessr_check.py left -41.4395 147.140833 -r 12 -j 8
python3 tools/geoguessr_check.py ferris-wheel 37.7867 20.8999 -r 45 -j 8
python3 tools/geoguessr_check.py truck 47.4515 105.0535 -r 35 -j 8
python3 tools/geoguessr_solve.py tools/geoguessr_hits.json
```

## Important Code / Payload

```text
Working key file: tools/geoguessr_hits.json
Recovered flag: slopped{h0w_d0_agent5_sl0p_nmpz?}
```

## Dead Ends

- Spent time on the 10th panorama candidates that were not needed once 9 valid
  shares had been recovered.
- Several early `left` and `ferris-wheel` city guesses were visually plausible
  but outside the correct H3 radius.

## Things Future-Me Should Not Forget

- `left` was St John's Anglican Church / Elizabeth & St John, Launceston.
- `ferris-wheel` was Zakynthos harbor.
- `truck` was on the Mongolia road near Ondorshireet.
- The challenge share ciphertexts were double-padded; the solver already strips
  that correctly.

## Flag

`slopped{h0w_d0_agent5_sl0p_nmpz?}`
