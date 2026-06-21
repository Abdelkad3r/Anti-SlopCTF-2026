# SloppedRider

**Category:** Web  
**Flag:** `slopped{riding_0n_M3?}`

## Overview

SloppedRider was a Node.js Express app presenting a motorbike riding game where the terrain was drawn from stock price charts. Players rode the chart, accumulated a score, and submitted it via a signed ride ticket. The game's legitimate score cap was hard-capped at 5,000, while the target to unlock the flag was 676,767.

The path to the flag combined two bugs: an SSRF in the chart preview endpoint that reached an internal operations server, and an error response that echoed back the fetched body verbatim, leaking the HMAC key used to sign ride tickets. With the key in hand, forging a ticket with `cap: 676767` and submitting that score was trivial.

## The Scoring System

Each chart came with a `rideTicket`: a base64url-encoded JSON payload signed with HMAC-SHA256.

```json
{
  "v": 1,
  "kind": "ride",
  "symbol": "TSLA",
  "period": "5y",
  "cap": 4500,
  "iat": 1749123456
}
```

The score submission endpoint at `POST /api/score` verified the signature and enforced `score <= ticket.cap`. To get the flag, the submitted score had to be at least `TARGET_SCORE = 676767` — far beyond any cap a legitimate chart could produce.

The signing key, `SCORE_KEY`, was generated once at startup and never exposed through normal routes.

## SSRF in Chart Preview

The `POST /api/chart/preview` endpoint accepted an arbitrary URL, fetched it server-side with Node's built-in `http`/`https` module, and tried to parse the response as a chart JSON object:

```
{ prices: [positive numbers], symbol, period, ... }
```

Protocol was restricted to `http:` and `https:`, and the timeout was 2.5 seconds. No other SSRF mitigations existed.

Separately, the server started a second HTTP listener bound exclusively to `127.0.0.1:43219`. This internal ops server exposed a `/ops/config` route that returned the runtime configuration:

```json
{
  "service": "sloppedrider-ops",
  "scoreKey": "3b6bbb0ab2921dee71771f9b07a7974fc475f206fd9534f6bc15d73bfef94d94",
  "targetScore": 676767,
  "note": "score tickets are HMAC-SHA256 over the base64url JSON payload"
}
```

Feeding that internal URL to the preview endpoint was straightforward:

```
POST /api/chart/preview
{"url": "http://127.0.0.1:43219/ops/config"}
```

## The Error Response Leak

The ops config JSON had no `prices` array, so `normalizeChart()` rejected it. The endpoint returned an error, but included a `sample` field containing the first 600 bytes of the fetched body:

```json
{
  "error": "chart feed must include 8-256 positive prices",
  "sample": "{\"service\":\"sloppedrider-ops\",\"scoreKey\":\"3b6bbb0ab292...\",...}"
}
```

The `scoreKey` was now in plaintext in the error response.

## Ticket Forgery

With the key, we constructed a forged payload granting a cap of 676,767 and signed it:

```python
payload = {"v": 1, "kind": "preview", "symbol": "SLOP",
           "period": "1y", "cap": 676767, "iat": int(time.time())}
payload_b64 = base64url(json.dumps(payload).encode())
sig = hmac.new(score_key.encode(), payload_b64.encode(), sha256).digest()
ticket = payload_b64 + "." + base64url(sig)
```

Submitting this ticket with `score: 676767` to `POST /api/score` cleared the cap check and hit the target threshold.

## Solution Flow

1. `POST /api/chart/preview` with `url: "http://127.0.0.1:43219/ops/config"`.
2. Parse `scoreKey` from the `sample` field of the error response.
3. Build a ticket JSON with `cap: 676767`, base64url-encode it, sign with HMAC-SHA256.
4. `POST /api/score` with `score: 676767` and the forged ticket.
5. Receive the flag.

## Takeaways

The two bugs were individually minor and only dangerous in combination. SSRF to an internal port is a well-known risk, but it is only critical here because the error path reflected the raw fetch body back to the caller. Had the server discarded the body on normalisation failure — or had the ops server not existed at all — neither bug would have been sufficient alone.
