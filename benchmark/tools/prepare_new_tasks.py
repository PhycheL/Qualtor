#!/usr/bin/env python3
"""在 Docker 机器上批量标定新题的变异分母，并汇总结果。

对每道题调用 evaluator/assessment/prepare_task.py baseline（每道题一个独立 run），读取各自的 prepare_report.json
与分母草稿，汇总变异数、等价候选、不稳定变异，以及参考测试的两种检出率：
- reference_m1：准备工具的口径，分母已剔除探针也区分不出的等价候选；
- reference_raw_m1：不剔除等价候选的原始检出率，killed ÷ (全部变异 − 超时)。探针模式为 reference_copy 的题，
  reference_m1 必然为 1，应看这个原始值判断参考测试强弱。

写入前应用变异复核结论（benchmark/tools/mutant_review/<题目 ID>/confirmed.json）：真实 Mull 反例已检出、却仍被探针
判为等价候选的变异移回分母；只在未定义行为下不同的变异列为不稳定（D015）。随后重算 reference_m1，修订后的草稿
另存为 mutation_baseline.reviewed.json；
重算后低于阈值的题不写入。题目包由本脚本写入，prepare_task.py 只负责标定。

用法（从项目根目录执行，需要 Docker 与两套工具链镜像）：
  python3 benchmark/tools/prepare_new_tasks.py --write                 # 所有还没有 mutation_baseline.json 的题
  python3 benchmark/tools/prepare_new_tasks.py --tasks exercism-clock --write --jobs 2
  python3 benchmark/tools/prepare_new_tasks.py --tasks humaneval-x-cpp-17 --write --force   # 材料变化后重新标定
不加 --write 时只标定、不写入题目包；已有分母的题要覆盖时加 --force。
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import shutil
import subprocess
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(Path(__file__).resolve().parent), str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]

import bankutil  # noqa: E402
import common  # noqa: E402
from audit import Audit
from runs import finish, new_manifest, write_manifest  # noqa: E402


def unprepared_tasks():
    return [p.parent.name for p in sorted(common.BENCHMARK.glob("*/task.json"))
            if common.load_baseline(common.load_task(p.parent.name)) is None]


def prepare(task_id, args):
    run_id = f"{args.run_id}-{task_id}"[:80]
    task = common.load_task(task_id)
    target = common.hidden_path(task, "mutation_baseline")
    entry = {"task": task_id, "run_id": run_id, "probe_mode": (task.get("preparation") or {}).get("probe_mode"),
             "written": False}
    if args.write and target.exists() and not args.force:
        entry.update(passed=False, problems=["变异分母已存在；确认要重新标定时加 --force"])
        print(f"{task_id}：已有分母，跳过", flush=True)
        return entry
    command = [sys.executable, str(REPO / "evaluator/assessment/prepare_task.py"), "baseline", "--task", task_id,
               "--run-id", run_id]
    done = Audit(common.RUNS / args.run_id / "commands" / task_id).run("prepare-task", command, cwd=REPO, timeout=14400)
    run_dir = common.RUNS / run_id
    if run_dir.exists():
        (run_dir / "batch-stdout.log").write_text(done["stdout"], encoding="utf-8")
    entry["exit_code"] = done["returncode"]
    report_path, draft_path = run_dir / "prepare_report.json", run_dir / "mutation_baseline.json"
    if report_path.is_file():
        report = json.loads(report_path.read_text(encoding="utf-8"))
        entry.update(passed=report.get("passed"), problems=report.get("problems", []), mutants=report.get("mutants"),
                     equivalent_candidates=report.get("equivalent_candidates"), unstable=report.get("unstable"),
                     review_needed=report.get("review_needed"),
                     reference_m1=(report.get("reference") or {}).get("m1"))
    else:
        entry.update(passed=False, problems=[done["stderr"][-1500:] or "没有生成 prepare_report.json"])
    final, moved = None, []
    if draft_path.is_file():
        draft = json.loads(draft_path.read_text(encoding="utf-8"))
        if 'environment' in draft:
            entry['environment'] = draft['environment']
        if draft.get("mutation", {}).get("applicable") is False:
            entry.update(not_applicable=draft["mutation"]["reason"], reference_c1=draft["reference"].get("c1"),
                         handwritten=draft["reference"].get("handwritten"),
                         handwritten_detected=draft["reference"].get("handwritten_detected"))
        statuses = [m["reference_status"][0] for m in draft["mutants"]]
        timeouts = statuses.count("timeout")
        entry["reference_raw_m1"] = statuses.count("killed") / (len(statuses) - timeouts) if len(statuses) > timeouts else None
        final, moved, problems = bankutil.apply_confirmed(draft, task_id)
        entry["confirmed_moved"] = len(moved)
        if problems:
            entry["passed"] = False
            entry["problems"] = entry["problems"] + problems
        elif moved:
            common.write_json(run_dir / "mutation_baseline.reviewed.json", final)
            reference = final["reference"]
            entry.update(equivalent_candidates=len(final["equivalent"]), unstable=len(final["unstable"]),
                         reference_m1=reference["m1"])
            if not reference["passes"]:
                entry["passed"] = False
                entry["problems"] = entry["problems"] + [
                    f"落实 {len(moved)} 项复核结论后，参考强测试集 M1 = {reference['m1']}，"
                    f"低于阈值 {reference['threshold']}；需要补强"]
    if args.write and entry.get("passed"):
        if moved:
            common.write_json(target, final)
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(draft_path, target)
        if task.get("target_headers"):
            shutil.copyfile(run_dir / "coverage_baseline.json", common.hidden_path(task, "coverage_baseline"))
        entry["written"] = True
    print(f"{task_id}：{'通过' if entry.get('passed') else '未通过'}，变异 {entry.get('mutants')}，"
          f"等价候选 {entry.get('equivalent_candidates')}，复核修订 {len(moved)}，参考 M1 {entry.get('reference_m1')}，"
          f"原始检出率 {entry.get('reference_raw_m1')}", flush=True)
    return entry


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--tasks", nargs="*", default=[])
    parser.add_argument("--write", action="store_true", help="全部检查通过时写入题目的 mutation_baseline.json")
    parser.add_argument("--force", action="store_true", help="覆盖已有的 mutation_baseline.json（题目材料变化后重新标定）")
    parser.add_argument("--jobs", type=int, default=1)
    parser.add_argument("--run-id", default=common.default_run_id("bank-prepare"))
    args = parser.parse_args()
    tasks = args.tasks or unprepared_tasks()
    if not tasks:
        parser.error("没有需要标定的题目")
    common.check_run_id(args.run_id)
    run_dir = common.RUNS / args.run_id
    if run_dir.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    manifest = new_manifest(args.run_id, "prepare", mode="bank_batch", tasks=tasks, write=args.write, force=args.force)
    write_manifest(run_dir, manifest)
    try:
        with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
            entries = list(pool.map(lambda t: prepare(t, args), tasks))
    except BaseException as error:
        finish(run_dir, manifest, "failed", error=str(error))
        raise
    common.write_json(run_dir / "summary.json", {"run_id": args.run_id, "tasks": entries})
    lines = ["| 题目 | 结论 | 探针模式 | 变异 | 等价候选 | 不稳定 | 复核修订 | 参考 M1 | 原始检出率 | 已写入 | 问题 |",
             "|---|---|---|---|---|---|---|---|---|---|---|"]
    fmt = lambda v: "—" if v is None else (f"{v:.3f}" if isinstance(v, float) else str(v))
    for e in entries:
        problem = "；".join(e.get("problems") or [])[:200].replace("|", "/").replace("\n", " ") or "—"
        lines.append(f"| {e['task']} | {'通过' if e.get('passed') else '未通过'} | {e.get('probe_mode')} | {fmt(e.get('mutants'))} "
                     f"| {fmt(e.get('equivalent_candidates'))} | {fmt(e.get('unstable'))} | {fmt(e.get('confirmed_moved'))} "
                     f"| {fmt(e.get('reference_m1'))} | {fmt(e.get('reference_raw_m1'))} | {'是' if e.get('written') else '否'} "
                     f"| {problem} |")
    (run_dir / "summary.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    passed = all(e.get("passed") for e in entries)
    finish(run_dir, manifest, "completed", passed=passed)
    print(f"汇总：{run_dir / 'summary.md'}")
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())
