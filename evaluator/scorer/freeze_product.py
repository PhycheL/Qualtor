#!/usr/bin/env python3
"""冻结测试产物：为 <产物目录>（含 tests/）写 manifest.json，记录每个文件的 SHA-256。

冻结之后评分器只校验、不改写；修改测试文件后要重新冻结，并作为一份新的产物记录。
用法：python3 evaluator/scorer/freeze_product.py <产物目录> [--force]
"""
import argparse
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import freeze_product  # noqa: E402


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("product", type=Path)
    parser.add_argument("--force", action="store_true", help="覆盖已有的 manifest.json")
    args = parser.parse_args()
    if not (args.product / "tests").is_dir():
        parser.error("产物目录下必须有 tests/")
    if (args.product / "manifest.json").exists() and not args.force:
        parser.error("manifest.json 已存在；确认要重新冻结时加 --force")
    files = freeze_product(args.product)
    print(f"已冻结 {len(files)} 个文件：{args.product / 'manifest.json'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
