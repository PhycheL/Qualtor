#!/usr/bin/env python3
"""只读检查 Markdown 文档中的相对链接与锚点：目标文件存在，指向 .md 的锚点与目标文件的标题一致。

锚点按 GitHub 规则生成：去掉标题中的 Markdown 标记，转小写，删除字母、数字、空格、连字符和下划线以外的字符
（中文保留），空格换成连字符；同名标题依次加 -1、-2。外部链接（http、https、mailto）不检查。
指向 runs/ 的链接按本机文件检查（runs/ 不入 Git，缺失时单独列出，不算错误，除非加 --strict-runs）。

用法：python3 -I -B benchmark/tools/check_doc_links.py [文件...]   # 默认检查 README、AGENTS、agents/README 与 docs/*.md
"""
import argparse
from pathlib import Path
import re
import sys
import unicodedata
from urllib.parse import unquote

REPO = Path(__file__).resolve().parents[2]
DEFAULT = ["README.md", "AGENTS.md", "agents/README.md", "benchmark/tools/README.md", *sorted(
    str(p.relative_to(REPO)) for p in (REPO / "docs").glob("*.md"))]
LINK = re.compile(r"(?<!!)\[(?:[^\]\\]|\\.)*\]\(([^()\s]+(?:\([^()\s]*\))?[^()\s]*)(?:\s+\"[^\"]*\")?\)")
FENCE = re.compile(r"^\s*(```|~~~)")


def slug(heading):
    text = re.sub(r"`([^`]*)`", r"\1", heading)
    text = re.sub(r"!?\[([^\]]*)\]\([^)]*\)", r"\1", text)
    text = re.sub(r"[*_~]{1,3}([^*_~]+)[*_~]{1,3}", r"\1", text)
    text = re.sub(r"<[^>]+>", "", text).strip().lower()
    kept = "".join(c for c in text if c in " -_" or unicodedata.category(c)[0] in "LN")
    return kept.replace(" ", "-")


def anchors(path, cache={}):
    if path not in cache:
        seen, result, fenced = {}, set(), False
        for line in path.read_text(encoding="utf-8").splitlines():
            if FENCE.match(line):
                fenced = not fenced
                continue
            match = None if fenced else re.match(r"^(#{1,6})\s+(.*?)\s*#*\s*$", line)
            if match:
                base = slug(match.group(2))
                count = seen.get(base, 0)
                seen[base] = count + 1
                result.add(base if count == 0 else f"{base}-{count}")
        cache[path] = result
    return cache[path]


def links(path):
    fenced = False
    for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        if FENCE.match(line):
            fenced = not fenced
            continue
        if fenced:
            continue
        stripped = re.sub(r"`[^`]*`", "", line)
        for match in LINK.finditer(stripped):
            yield number, match.group(1)


def check(files, strict_runs=False):
    problems, missing_runs, total = [], [], 0
    for rel in files:
        path = (REPO / rel).resolve()
        for number, target in links(path):
            if re.match(r"^[a-z][a-z0-9+.-]*:", target):
                continue
            total += 1
            location = f"{path.relative_to(REPO)}:{number}"
            file_part, _, anchor = target.partition("#")
            destination = (path.parent / unquote(file_part)).resolve() if file_part else path
            if not destination.exists():
                inside_runs = destination.is_relative_to(REPO / "runs")
                (missing_runs if inside_runs and not strict_runs else problems).append(f"{location}: 目标不存在 {target}")
                continue
            if anchor and destination.suffix == ".md" and unquote(anchor) not in anchors(destination):
                problems.append(f"{location}: 锚点不存在 {target}")
    return total, problems, missing_runs


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("files", nargs="*", default=DEFAULT)
    parser.add_argument("--strict-runs", action="store_true", help="runs/ 下的目标缺失也算错误")
    args = parser.parse_args()
    total, problems, missing_runs = check(args.files, args.strict_runs)
    for line in problems:
        print(line)
    for line in missing_runs:
        print("（本机缺少 runs 证据）" + line)
    print(f"检查 {len(args.files)} 个文件、{total} 个相对链接：错误 {len(problems)}，本机缺少的 runs 目标 {len(missing_runs)}")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
