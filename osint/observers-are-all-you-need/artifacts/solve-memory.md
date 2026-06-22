# Writeup Memory

## Final Vulnerability / Trick

- The flag was split across public May 2026 artifacts connected to
  `FloatingPragma/observer-patch-holography` and the `cryptoverse-cyber`
  GitHub account.
- Part 1 was hidden as base64 in the GitHub profile `company` field, while
  parts 2 and 3 were explicit flag fragments in an issue comment and PR body.

## Why It Works

- The challenge prompt quote and title point to Observer Patch Holography.
- The May 2026 hint narrows the search to public artifacts from that period.
- The same account, `cryptoverse-cyber`, planted all three parts:
  profile metadata, issue `#292`, and PR `#301`.

## Solve Path

1. Identified the target project as `FloatingPragma/observer-patch-holography`.
2. Searched May 2026 GitHub artifacts and found part 2 in issue `#292`.
3. Found part 3 in PR `#301`.
4. Checked `cryptoverse-cyber` globally and decoded the base64 profile
   `company` value `c2xvcHBlZHtPUEhfaXNfYV8=` to recover part 1.
5. Assembled the chunks in order.

## Key Commands

```bash
curl -fsSL -H 'Accept: application/vnd.github+json' \
  https://api.github.com/users/cryptoverse-cyber | jq -r '.company'

python3 - <<'PY'
import base64
s = 'c2xvcHBlZHtPUEhfaXNfYV8='
print(base64.b64decode(s).decode())
PY
```

## Important Code / Payload

```text
Part 1: slopped{OPH_is_a_
Part 2: rec0nstructi0n_pr0gram_f0r_
Part 3: funD4mentaL_phys1cs}
```

## Dead Ends

- The no-prefix assembly was wrong.
- The LinkedIn-style `our reconstruction program...` prefix was wrong.
- The long `Observer Patch Holography is a...` prose-derived prefix was wrong.
- Repo phrase matching was useful for confidence, but the first part had to be
  recovered from the GitHub profile metadata.

## Things Future-Me Should Not Forget

- Do not write up part 1 as an inference. It was directly encoded in
  `cryptoverse-cyber`'s profile.
- GitHub API returned `company: c2xvcHBlZHtPUEhfaXNfYV8=` and
  `updated_at: 2026-05-31T02:18:26Z`, matching the May 2026 artifact hint.

## Flag

`slopped{OPH_is_a_rec0nstructi0n_pr0gram_f0r_funD4mentaL_phys1cs}`
