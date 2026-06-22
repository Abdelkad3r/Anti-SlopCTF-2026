#!/usr/bin/env python3
import base64
import json
import re
from pathlib import Path


ARTIFACTS = Path(__file__).resolve().parent / "artifacts"


def load_json(name):
    return json.loads((ARTIFACTS / name).read_text())


def main():
    profile = load_json("cryptoverse-cyber-profile.json")
    issue_comments = load_json("issue-292-comments.json")
    pull = load_json("pull-301.json")

    part1 = base64.b64decode(profile["company"]).decode()

    issue_body = "\n".join(comment.get("body", "") for comment in issue_comments)
    part2 = re.search(r"Flag part 2:\s*`([^`]+)`", issue_body).group(1)

    part3 = re.search(r"Flag part 3:\s*`([^`]+)`", pull["body"]).group(1)

    print(part1 + part2 + part3)


if __name__ == "__main__":
    main()
