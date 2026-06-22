#!/usr/bin/env python3
from __future__ import annotations

import argparse
import ast
import operator
import re
import socket
from dataclasses import dataclass


DEFAULT_HOST = "178.105.199.41"
DEFAULT_PORT = 22222
SAFE_FALLBACK = "I am a human"


class ParseError(ValueError):
    pass


OPS = {
    ast.Add: operator.add,
    ast.Sub: operator.sub,
    ast.Mult: operator.mul,
    ast.FloorDiv: operator.floordiv,
    ast.Div: operator.floordiv,
}

UNARY_OPS = {
    ast.UAdd: operator.pos,
    ast.USub: operator.neg,
}


@dataclass
class Question:
    raw: str
    prompt: str
    expression: str | None
    answer: str


def safe_eval(expr: str) -> int:
    tree = ast.parse(expr, mode="eval")

    def visit(node: ast.AST) -> int:
        if isinstance(node, ast.Expression):
            return visit(node.body)
        if isinstance(node, ast.Constant) and isinstance(node.value, int):
            return node.value
        if isinstance(node, ast.BinOp) and type(node.op) in OPS:
            right = visit(node.right)
            if isinstance(node.op, (ast.Div, ast.FloorDiv)) and right == 0:
                raise ZeroDivisionError("division by zero")
            return OPS[type(node.op)](visit(node.left), right)
        if isinstance(node, ast.UnaryOp) and type(node.op) in UNARY_OPS:
            return UNARY_OPS[type(node.op)](visit(node.operand))
        raise ParseError(f"unsupported expression node: {ast.dump(node)}")

    return visit(tree)


def interesting_lines(text: str) -> list[str]:
    lines = []
    for line in text.replace("\r", "").splitlines():
        line = line.strip()
        if not line or line == ">":
            continue
        if line.startswith("Baby Maths"):
            continue
        if line.startswith("100 questions"):
            continue
        if line.startswith("Answer carefully"):
            continue
        if re.fullmatch(r"Question\s+\d+/\d+", line):
            continue
        lines.append(line)
    return lines


def contains_injection(text: str) -> bool:
    lowered = text.lower()
    needles = [
        "auth.json",
        "openai api key",
        "api key",
        "base64-encoded",
        "base64 encoded",
    ]
    return any(needle in lowered for needle in needles)


def normalize_expression(prompt: str) -> str:
    expr = prompt.strip()
    expr = re.sub(r"^(please\s+)?(compute|calculate|evaluate|find)\s+", "", expr, flags=re.I)
    expr = re.sub(r"^what\s+is\s+", "", expr, flags=re.I)
    expr = re.sub(r"^tell\s+me\s+", "", expr, flags=re.I)
    expr = expr.strip(" .?!")

    replacements = [
        (r"\bdivided\s+by\b", "//"),
        (r",?\s*floored\b", ""),
        (r"\bmultiplied\s+by\b", "*"),
        (r"\btimes\b", "*"),
        (r"\bplus\b", "+"),
        (r"\bminus\b", "-"),
    ]
    for pattern, replacement in replacements:
        expr = re.sub(pattern, replacement, expr, flags=re.I)

    expr = expr.replace("×", "*").replace("÷", "//")
    expr = re.sub(r"[^0-9+\-*/() \t]", " ", expr)
    expr = re.sub(r"\s+", " ", expr).strip()
    if not expr:
        raise ParseError(f"could not extract expression from: {prompt!r}")
    return expr


def answer_block(text: str) -> Question:
    lines = interesting_lines(text)
    prompt = lines[-1] if lines else text.strip()
    if contains_injection(text):
        return Question(text, prompt, None, SAFE_FALLBACK)
    expr = normalize_expression(prompt)
    return Question(text, prompt, expr, str(safe_eval(expr)))


def recv_until_prompt(sock: socket.socket) -> bytes:
    data = bytearray()
    while True:
        chunk = sock.recv(4096)
        if not chunk:
            break
        data.extend(chunk)
        if data.endswith(b"> ") or b"Bye." in data or b"slopped{" in data:
            break
    return bytes(data)


def solve(host: str, port: int, verbose: bool = False) -> str:
    with socket.create_connection((host, port), timeout=10) as sock:
        sock.settimeout(10)
        transcript = []
        while True:
            block = recv_until_prompt(sock).decode("utf-8", "replace")
            if not block:
                break
            transcript.append(block)
            if "slopped{" in block:
                return block
            if "Bye." in block or "Wrong answer" in block:
                raise RuntimeError(block)
            question = answer_block(block)
            if verbose:
                if question.expression is None:
                    print(f"{question.prompt} -> {question.answer}")
                else:
                    print(f"{question.prompt} -> {question.expression} = {question.answer}")
            sock.sendall(question.answer.encode() + b"\n")
        return "".join(transcript)


def main() -> None:
    parser = argparse.ArgumentParser(description="Solve Anti-Slop CTF Baby Maths.")
    parser.add_argument("host", nargs="?", default=DEFAULT_HOST)
    parser.add_argument("port", nargs="?", type=int, default=DEFAULT_PORT)
    parser.add_argument("-v", "--verbose", action="store_true")
    args = parser.parse_args()
    print(solve(args.host, args.port, args.verbose), end="")


if __name__ == "__main__":
    main()
