# Observers Are All You Need

**Category:** OSINT
**Points:** 443
**Flag:** `slopped{OPH_is_a_rec0nstructi0n_pr0gram_f0r_funD4mentaL_phys1cs}`

## Summary

The challenge prompt gave a philosophical quote, told us to focus on artifacts produced in May 2026, and said the flag was split into three parts. The title was the real steering wheel: "Observers Are All You Need" pointed toward Observer Patch Holography, usually shortened to OPH.

The solve was not to infer a flag from prose. That produced plausible but wrong guesses. The correct path was to follow the May 2026 GitHub artifact trail around `FloatingPragma/observer-patch-holography` and the account `cryptoverse-cyber`.

## Artifacts

The evidence snapshots and reproduction helper are included here:

```text
artifacts/cryptoverse-cyber-profile.json
artifacts/issue-292-comments.json
artifacts/pull-301.json
artifacts/notes.md
artifacts/solve-memory.md
solve.py
```

The three JSON files were fetched from GitHub's API during writeup preparation. They preserve the exact profile metadata, issue comment, and pull request body used to reconstruct the flag.

## Pivot

The prompt's May 2026 hint mattered. A broad web search for the quote and nearby language led to the OPH project, but the repository text only explained the theme. It did not by itself give the exact flag.

The better search target was GitHub activity around:

```text
FloatingPragma/observer-patch-holography
cryptoverse-cyber
May 2026
```

That account appeared on the relevant repository activity and carried all three flag fragments.

## Fragment 1

The first fragment was hidden in the GitHub profile metadata for `cryptoverse-cyber`. The API response included:

```json
{
  "login": "cryptoverse-cyber",
  "company": "c2xvcHBlZHtPUEhfaXNfYV8=",
  "updated_at": "2026-05-31T02:18:26Z"
}
```

Decoding the `company` value as base64 gives:

```text
slopped{OPH_is_a_
```

The timestamp also matches the challenge note to focus on May 2026 artifacts.

## Fragment 2

The second fragment was in a comment on issue `#292` in `FloatingPragma/observer-patch-holography`.

The artifact snapshot shows:

```text
user: cryptoverse-cyber
created_at: 2026-05-24T03:17:04Z
url: https://github.com/FloatingPragma/observer-patch-holography/issues/292#issuecomment-4527254522
```

The comment body contained:

```text
rec0nstructi0n_pr0gram_f0r_
```

## Fragment 3

The third fragment was in pull request `#301`, also by `cryptoverse-cyber`.

The artifact snapshot shows:

```text
created_at: 2026-05-24T03:14:48Z
updated_at: 2026-05-24T03:15:15Z
url: https://github.com/FloatingPragma/observer-patch-holography/pull/301
```

The PR body ended with:

```text
funD4mentaL_phys1cs}
```

## Reproduction

The included solver reads the saved GitHub API artifacts, decodes the profile metadata, extracts the two markdown fragments, and prints the assembled flag:

```bash
python3 solve.py
```

Expected output:

```text
slopped{OPH_is_a_rec0nstructi0n_pr0gram_f0r_funD4mentaL_phys1cs}
```

The same check can be done manually:

```bash
jq -r '.company' artifacts/cryptoverse-cyber-profile.json | base64 -d
jq -r '.[].body' artifacts/issue-292-comments.json
jq -r '.body' artifacts/pull-301.json
```

## Takeaway

The challenge punished guessing from theme alone. The exact answer came from treating "May 2026 artifacts" literally and following the public GitHub trail: profile metadata for part 1, an issue comment for part 2, and a pull request body for part 3.
