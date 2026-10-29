#!/usr/bin/env python3
"""在宿主机上检查题目包：用本机编译器跑参考强测试集、探针和替换版本，不含覆盖率与 Mull。

这是 Docker 准入前的辅助检查，不能代替 prepare_task.py baseline，结论也不能写成已准入。
检查内容与准备工具一致：两套测试都要构建成功、全部有效且稳定；替换版本上应失败的被检出、等价版本无误报。

需要环境变量（与 evaluator/assessment/tests/host_executor.py 相同）：
  QUALTOR_HOST_CMAKE、QUALTOR_HOST_NINJA、QUALTOR_HOST_GTEST（GoogleTest 1.12.1 安装前缀）、QUALTOR_HOST_CXX
用法（从项目根目录执行）：
  python3 benchmark/tools/host_check.py --tasks exercism-clock humaneval-x-cpp-01 --run-id bank-hostcheck-<编号>
  python3 benchmark/tools/host_check.py --unprepared --jobs 4      # 检查所有尚未标定变异分母的题目
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import sys
import traceback

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "evaluator/assessment"), str(REPO / "evaluator/assessment/tests"),
                str(REPO / "evaluator/common")]

from audit import Audit  # noqa: E402
from runs import finish, new_manifest, write_manifest  # noqa: E402
import common  # noqa: E402
import host_executor  # noqa: E402
import pipeline  # noqa: E402
import prepare_task  # noqa: E402


def check_task(task_id, run_dir):
    out = run_dir / "tasks" / task_id
    entry = {"task": task_id, "problems": [], "suites": {}}
    try:
        task = common.load_task(task_id)
        executor = host_executor.HostExecutor()
        results = {}
        for suite, key in (("reference", "reference_tests"), ("probe", "equivalence_probe")):
            if suite == "probe" and (common.mutation_not_applicable(task) or not common.hidden_path(task, key)):
                continue
            product = prepare_task.make_product(common.hidden_path(task, key), out / "products" / suite)
            result = pipeline.assess_product(executor, task, product, out / suite, {"host_check": suite},
                                             Audit(out / f"{suite}-host"), prep=True,
                                             calibration={"status": "not_required_for_host_check"})
            results[suite] = [result]
            tests = result.get("tests") or {}
            entry["suites"][suite] = {"status": result["status"], "invalid_reason": result.get("invalid_reason"),
                                      "infra_detail": result.get("infra_detail"), "tests": len(tests),
                                      "valid": sum(1 for s in tests.values() if s == "valid"),
                                      "variants": {v["id"]: v["outcome"] for v in result.get("variants") or []}}
            entry["problems"] += prepare_task.suite_problems(suite, result)
        entry["problems"] += prepare_task.admission(task, results)
    except Exception as error:  # 题目包本身的问题也要记下来，不能让一道题中断整批检查
        entry["problems"].append(f"检查异常：{error}")
        entry["traceback"] = traceback.format_exc()
    entry["passed"] = not entry["problems"]
    return entry


def unprepared_tasks():
    ids = []
    for path in sorted(common.BENCHMARK.glob("*/task.json")):
        task = common.load_task(path.parent.name)
        if common.load_baseline(task) is None:
            ids.append(task["id"])
    return ids


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--tasks", nargs="*", default=[])
    parser.add_argument("--unprepared", action="store_true", help="检查所有还没有 mutation_baseline.json 的题目")
    parser.add_argument("--jobs", type=int, default=2)
    parser.add_argument("--run-id", default=common.default_run_id("bank-hostcheck"))
    args = parser.parse_args()
    if not host_executor.available():
        parser.error("缺少 QUALTOR_HOST_CMAKE、QUALTOR_HOST_NINJA、QUALTOR_HOST_GTEST 环境变量")
    tasks = list(dict.fromkeys(args.tasks + (unprepared_tasks() if args.unprepared else [])))
    if not tasks:
        parser.error("没有要检查的题目")
    common.check_run_id(args.run_id)
    run_dir = common.RUNS / args.run_id
    if run_dir.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    manifest = new_manifest(args.run_id, "prepare", mode="host_check", tasks=tasks,
                            host_toolchain={k: os.environ.get(k) for k in
                                            ("QUALTOR_HOST_CXX", "QUALTOR_HOST_GTEST", "QUALTOR_HOST_CMAKE")})
    write_manifest(run_dir, manifest)
    try:
        with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
            entries = list(pool.map(lambda t: check_task(t, run_dir), tasks))
    except BaseException as error:
        finish(run_dir, manifest, "failed", error=str(error))
        raise
    passed = [e["task"] for e in entries if e["passed"]]
    summary = {"run_id": args.run_id, "passed": len(passed), "failed": len(entries) - len(passed), "tasks": entries}
    common.write_json(run_dir / "summary.json", summary)
    lines = ["| 题目 | 结论 | 参考测试（有效/总数） | 探针（有效/总数） | 替换版本 | 问题 |", "|---|---|---|---|---|---|"]
    for e in entries:
        ref, probe = e["suites"].get("reference", {}), e["suites"].get("probe", {})
        variants = ", ".join(f"{k}={v}" for k, v in sorted(ref.get("variants", {}).items())) or "—"
        problem = "；".join(e["problems"])[:300].replace("|", "/") or "—"
        lines.append(f"| {e['task']} | {'通过' if e['passed'] else '未通过'} | {ref.get('valid', 0)}/{ref.get('tests', 0)} "
                     f"| {probe.get('valid', 0)}/{probe.get('tests', 0)} | {variants} | {problem} |")
    (run_dir / "summary.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    finish(run_dir, manifest, "completed", passed=len(passed) == len(entries))
    print("\n".join(lines))
    print(f"汇总：{run_dir / 'summary.md'}")
    return 0 if len(passed) == len(entries) else 1


if __name__ == "__main__":
    raise SystemExit(main())
