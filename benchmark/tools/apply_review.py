#!/usr/bin/env python3
"""把变异复核结论落到已有分母上，或核对分母是否都已落实。

benchmark/tools/mutant_review/<题目 ID>/confirmed.json 列出复核结论：真实 Mull 反例已检出的变异移回分母；
只在未定义行为下与原代码不同的变异列为不稳定，不计入分母（D015）。
重新标定时 prepare_new_tasks.py 会自动应用；本脚本用于材料没有变化、不需要重新标定的题，以及核对现有分母。
修订后参考强测试集 M1 低于阈值的题不写入，需要先补强参考测试再重新标定。

用法（任意机器，从项目根目录执行；只读写 JSON，不需要 Docker）：
  python3 benchmark/tools/apply_review.py                                  # 核对所有带 confirmed.json 的题
  python3 benchmark/tools/apply_review.py --tasks exercism-zebra-puzzle --write
不加 --write 时只核对：缺少分母、仍有结论未落实、修订后低于阈值或 ID 对不上时，退出码为 1。
"""
import argparse
from pathlib import Path
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(Path(__file__).resolve().parent), str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]

import bankutil  # noqa: E402
import common  # noqa: E402


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--tasks", nargs="*", default=[])
    parser.add_argument("--write", action="store_true", help="把修订后的分母写入题目包")
    args = parser.parse_args()
    tasks = args.tasks or sorted(p.name for p in bankutil.MUTANT_REVIEW.iterdir() if (p / "confirmed.json").is_file())
    failed = False
    fmt = lambda v: "—" if v is None else f"{v:.4f}"
    for task_id in tasks:
        task = common.load_task(task_id)
        baseline = common.load_baseline(task)
        if baseline is None:
            failed = True
            print(f"{task_id}：没有分母（待标定），核对未通过")
            continue
        if common.mutation_not_applicable(task, baseline):
            print(f"{task_id}：M1 不适用，跳过 Mull 复核；手写变异由 admit.py 核对")
            continue
        confirmed = bankutil.load_confirmed(task_id)
        result, moved, problems = bankutil.apply_confirmed(baseline, task_id)
        before, after = baseline["reference"], result["reference"]
        print(f"{task_id}：复核结论 {len(confirmed)}，待落实 {len(moved)}，"
              f"参考 M1 {fmt(before['m1'])} → {fmt(after['m1'])}（阈值 {after['threshold']}）")
        if problems:
            failed = True
            print("  问题：" + "；".join(problems))
        elif not after["passes"]:
            failed = True
            print("  修订后低于阈值：需补强参考测试并重新标定，未写入")
        elif moved and args.write:
            common.write_json(common.hidden_path(task, "mutation_baseline"), result)
            print("  已写入")
        elif moved:
            failed = True
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
