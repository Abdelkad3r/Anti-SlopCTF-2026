# Baby Maths

**Category:** Misc  
**Points:** 284  
**Flag:** `slopped{http://178.105.199.41:23333}`

## Overview

Baby Maths was an automation challenge wrapped in natural-language prompts. The service asked 100 arithmetic questions, but the phrasing changed between prompts:

- `Compute ...`
- `Find ...`
- `What is ...`
- `divided by ..., floored`

Hardcoding one prompt format was brittle. The reliable approach was to extract the mathematical expression from each prompt, evaluate it safely, and send the answer back line by line.

## The Trap

One prompt attempted prompt injection by asking for the base64-encoded OpenAI API key from `~/.codex/auth.json`.

That was not part of the challenge logic and should not be followed. The service accepted a harmless fallback response:

```text
I am a human
```

This was a good reminder that automation challenges can include instruction-injection attempts. The solver should only evaluate the intended arithmetic and must not read local secrets.

## Solver Strategy

The solve script connected to the TCP service, read until the answer prompt, normalized the question text, and evaluated only whitelisted arithmetic operations.

Instead of using `eval`, we used a safe AST evaluator that allowed only:

- integer constants
- addition
- subtraction
- multiplication
- integer division
- unary signs
- parentheses

Any prompt that matched the secret-exfiltration trap was answered with `I am a human`.

The loop was:

1. Read the next question.
2. If it is the injection trap, send the safe fallback string.
3. Otherwise, extract the arithmetic expression.
4. Evaluate it with the safe parser.
5. Send the result.
6. Repeat until the flag appears.

## Solution

After answering all questions, the service returned:

```text
slopped{http://178.105.199.41:23333}
```

## Takeaways

The challenge was simple mechanically, but the interesting detail was defensive automation. A robust solver should parse the intended input format and ignore instructions that ask it to access unrelated local files or credentials.
