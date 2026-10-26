#!/usr/bin/env python3
"""评测公开入口：选题、多次调用生成产品、独立评分和汇总。"""
from pathlib import Path
import runpy

if __name__ == "__main__":
    runpy.run_path(str(Path(__file__).resolve().parent / "runner/run.py"), run_name="__main__")
