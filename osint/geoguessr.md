# Geoguessr

**Category:** OSINT  
**Points:** 487  
**Flag:** `slopped{h0w_d0_agent5_sl0p_nmpz?}`

## Overview

The challenge presented a quick game of ten Geoguessr-style maps. At first glance it looked like a pure OSINT location hunt, but the web client revealed that each solved location unlocked part of a cryptographic secret.

Each panorama corresponded to an encrypted Shamir share. The client did not require exact coordinates. Instead, it accepted the correct H3 resolution-8 cell for each challenge.

## Client-Side Discovery

After dumping the web assets, the important logic was:

1. Convert a guessed latitude/longitude into an H3 cell.
2. Derive an Argon2 key from the H3 cell string and the challenge name.
3. Hash the raw key and compare it to a published target.
4. If the key matched, decrypt an AES-CBC encrypted share.
5. Combine enough shares with the included GF(256) Shamir implementation.

The threshold was 9 of 10 shares, so we did not need to fully solve every panorama. Nine correct H3 cells were enough to recover the final AES key and decrypt the flag.

## Location Solving

The practical workflow was to identify strong visual anchors, test candidate coordinates, and search nearby H3 cells until the derived key matched the published target.

Some of the useful anchors were:

- `left`: St John's Anglican Church / Elizabeth and St John, Launceston.
- `ferris-wheel`: Zakynthos harbor.
- `truck`: a road in Mongolia near Ondorshireet.

For each likely location, we used a checker script to search nearby H3 cells and confirm whether the derived key matched the challenge metadata.

Example commands from the solve:

```bash
python3 tools/geoguessr_check.py left -41.4395 147.140833 -r 12 -j 8
python3 tools/geoguessr_check.py ferris-wheel 37.7867 20.8999 -r 45 -j 8
python3 tools/geoguessr_check.py truck 47.4515 105.0535 -r 35 -j 8
```

Once enough locations were verified, the final solver combined the shares:

```bash
python3 tools/geoguessr_solve.py tools/geoguessr_hits.json
```

## Solution

The recovered shares reconstructed the final AES key, which decrypted the flag:

```text
slopped{h0w_d0_agent5_sl0p_nmpz?}
```

## Takeaways

This was not just a visual geolocation challenge. The real trick was realizing that the client-side crypto turned each location into a verifiable key. That meant a candidate only needed to land in the correct H3 cell, which made the OSINT portion much more forgiving once the verification code was understood.
