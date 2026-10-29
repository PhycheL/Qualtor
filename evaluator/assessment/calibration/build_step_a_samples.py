#!/usr/bin/env python3
"""重建步骤 A 的多文件、C 和宏配置校准样本；生成后需完整 Docker 校准。"""
from pathlib import Path
import shutil
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
from common import freeze_product, hidden_path, load_task, write_json

CASES = {
    "yaml-cpp-document": ("CAL-18", "只替换 .cpp 的真实缺陷；依赖源文件不覆盖、不变异", {"tagged-null": "detected"}),
    "md4c-html": ("CAL-19", "C99 被测源文件有覆盖、有变异，C 依赖源文件仅参与链接", {}),
    "tinyexpr-configured": ("CAL-20", "C11 数学解析库与 C++11 测试均采用公开功能宏", {}),
}
COST = {"tokens": {"input": 0, "output": 0}, "seconds": 0, "model_calls": 0, "repair_rounds": 0,
        "note": "校准样本没有生成过程，成本为固定的假数据"}
# 0.3.0 ARM64 原始结果：runs/step-a-calibration-20261028-03，两轮完全一致。
EXACT = {
    "CAL-18": {"C1": 256 / 264, "C2": 0.6584766584766585, "C3": 1.0},
    "CAL-19": {"C1": 258 / 263, "C2": 0.9073170731707317, "C3": 0.9545454545454546},
    "CAL-20": {"C1": 370 / 383, "C2": 0.8806818181818182, "C3": 1.0},
}


def main():
    for tid, (sid, description, variants) in CASES.items():
        task = load_task(tid)
        sample = HERE / tid / sid
        tests = sample / "final/tests"
        if tests.exists():
            shutil.rmtree(tests)
        tests.mkdir(parents=True)
        files = sorted(p for p in hidden_path(task, "reference_tests").iterdir()
                       if p.is_file() and p.suffix in (".cc", ".h"))
        for p in files:
            shutil.copyfile(p, tests / p.name)
        freeze_product(sample / "final", frozen_at="2026-10-28T00:00:00+00:00")
        write_json(sample / "generation/cost.json", COST)
        write_json(sample / "expected.json", {
            "description": description,
            "reference_copies": ["tests/" + p.name for p in files],
            "hard": {"status": "scored", "tests_default": "valid", "variants": variants,
                     **({"variant_failed_tests": {"tagged-null": ["NodeTest.LoadNullWithStrTag"]}} if variants else {})},
            "relations": [{"metric": key, "op": "==", "value": value}
                          for key, value in {"M1_e2e": 1, **EXACT[sid], "S1": 0, "V3": 0}.items()]
                         + ([{"metric": "M4", "op": "==", "value": 1}] if variants else []),
            "build_evidence": "每次配置检查 compile_commands.json：标准、宏、选项一致；覆盖/Mull 仅作用于 target_sources。",
        })
        print(tid, sid, len(files))


if __name__ == "__main__":
    main()
