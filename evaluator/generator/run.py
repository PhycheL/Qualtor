#!/usr/bin/env python3
"""一条命令运行 pi 生成、修复、冻结、首次/最终评分及按集合汇总。"""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from host import GenerationExecutor, git_snapshot, load_config, public_task, tree_hash, trial
from cost import add_costs
from paths import AGENTS, BENCHMARK, GENERATOR, RUNS, REPO
from audit import Audit
from runs import finish, new_manifest, write_manifest
from common import (calibration_status, check_run_id, default_run_id, load_task, now, scorer_code_sha256,
                    scorer_version, sha256_file, task_sha256, validate_task, write_json)
from docker_runner import DockerExecutor
import aggregate


def select_tasks(names, task_set):
    selected = {}
    for name in names:
        if name == "all" or Path(name).resolve() == BENCHMARK:
            choices = [p.parent for p in BENCHMARK.glob("*/task.json")]
        else:
            choices = [p for p in name.split(",") if p]
        for choice in choices:
            task = load_task(choice)
            if task_set is None or task["set"] == task_set:
                public_task(task)
                selected[task["id"]] = task
    if not selected:
        raise ValueError("没有符合筛选条件的题目")
    return list(selected.values())


def run_trials(work, jobs_list, jobs):
    """并行执行 trial。任一 trial 抛出异常后，取消所有尚未开始的 trial；正在运行的等其结束。"""
    results, errors, cancelled = [], [], []
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        futures = {pool.submit(work, task, index): (task["id"], index) for task, index in jobs_list}
        for future in as_completed(futures):
            label = futures[future]
            if future.cancelled():
                cancelled.append({"task": label[0], "trial": label[1]})
                continue
            try:
                results.append(future.result())
            except Exception as error:
                errors.append({"task": label[0], "trial": label[1], "error": f"{type(error).__name__}: {error}"})
                for other in futures:
                    other.cancel()
    return results, errors, cancelled


def execute(config, config_snapshot, tasks, count, jobs, run_id, scenario=None, watchdog=900):
    check_run_id(run_id)
    run = RUNS / run_id
    run.mkdir(parents=True, exist_ok=False)
    audit = Audit(run / "evidence/host")
    manifest = new_manifest(run_id, "eval", **{
                "operation": "generate", "framework_selftest": scenario is not None, "config": config_snapshot,
                "qualtor": git_snapshot(), "trials_per_task": count, "jobs": jobs,
                "tasks": {t["id"]: {"set": t["set"], "sha256": task_sha256(t), "source": t["source"],
                                     "budget": t["budget"]} for t in tasks},
                "pi_sha256": tree_hash(AGENTS / "pi"), "pi_runtime_sha256": tree_hash(AGENTS / "pi", runtime=True),
                "generator_sha256": tree_hash(GENERATOR), "scorer_version": scorer_version(),
                "scorer_code_sha256": scorer_code_sha256()})
    write_manifest(run, manifest)
    try:
        executor = DockerExecutor(audit, run / "evidence", run_id)
        states = {t["id"]: calibration_status(executor.images, t) for t in tasks}
        manifest["calibration"] = states
        if any(s["status"] != "passed" for s in states.values()):
            raise ValueError(f"评分器校准必须为 passed，当前：{states}；请先运行 calibrate.py")
        generator = GenerationExecutor(executor)
        manifest.update(images={**executor.images, "generator": generator.image})
        write_manifest(run, manifest)
        agent_version = config_snapshot["name"] + "@" + manifest["qualtor"]["commit"][:12] + "-" + config_snapshot["sha256"][:12]
        def work(task, index):
            print(f"生成与评分 {task['id']} trial-{index}", flush=True)
            result = trial(executor, generator, task, config, run / "trials" / task["id"] / f"trial-{index}",
                           index, agent_version, states[task["id"]], scenario, watchdog)
            print(f"  {task['id']} trial-{index}: {result['status']} "
                  + ", ".join(f"{p}={s['status']}" for p, s in result["scores"].items()), flush=True)
            return result
        results, errors, cancelled = run_trials(work, [(task, index) for task in tasks for index in range(1, count + 1)], jobs)
        if errors:
            # 基础设施异常：未开始的 trial 已取消，避免继续消耗模型费用；已完成的结果原样保留。
            summary = {"run_id": run_id, "status": "failed", "scorer_version": scorer_version(),
                       "framework_selftest": scenario is not None, "errors": errors, "cancelled_trials": cancelled,
                       "trial_statuses": dict(Counter(r["status"] for r in results)),
                       "trials": sorted(results, key=lambda r: (r["task"], r["trial"]))}
            write_json(run / "summary.json", summary)
            raise RuntimeError(f"{len(errors)} 个 trial 出现基础设施异常，已取消 {len(cancelled)} 个未开始的 trial：{errors[0]['error']}")
        for task in tasks:
            validate_task(task)
        if (tree_hash(GENERATOR) != manifest["generator_sha256"]
                or scorer_code_sha256() != manifest["scorer_code_sha256"]
                or tree_hash(AGENTS / "pi", runtime=True) != manifest["pi_runtime_sha256"]):
            raise ValueError("运行期间框架或 pi 文件发生变化，本轮不用于正式比较")
        scores = aggregate.load_results([run], version=scorer_version())
        summary = {"run_id": run_id, "scorer_version": scorer_version(), "framework_selftest": scenario is not None,
                   "trial_statuses": dict(Counter(r["status"] for r in results)), "trials": sorted(results, key=lambda r: (r["task"], r["trial"])),
                   "sets": {task_set: {phase: aggregate.summarize(scores, task_set, phase) for phase in ("first", "final")}
                            for task_set in sorted({t["set"] for t in tasks})}}
        summary["all_generation_cost"] = add_costs(
            {"tokens": {"input": 0, "output": 0, "cache_read": 0, "cache_write": 0},
             "seconds": 0, "model_calls": 0, "repair_rounds": 0, "usd": 0},
            [r["cost"]["final"] for r in results])
        missing = [r for r in results if r["status"] == "agent_error" or any(s["status"] == "infra_error" for s in r["scores"].values())]
        manifest["status"] = "incomplete" if missing else "completed"
        summary["status"] = manifest["status"]
        write_json(run / "summary.json", summary)
    except BaseException as error:
        audit.event(kind="run_error", error=str(error))
        finish(run, manifest, "failed", error=str(error))
        raise
    finish(run, manifest, manifest["status"])
    return run, summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", default="default")
    parser.add_argument("--tasks", nargs="+", default=["gildedrose-update-quality"])
    parser.add_argument("--set", choices=["dev", "acceptance"])
    parser.add_argument("--trials", type=int, default=5)
    parser.add_argument("--jobs", type=int, default=1)
    parser.add_argument("--run-id", default=default_run_id("eval"))
    args = parser.parse_args()
    if args.trials < 1 or args.jobs < 1:
        parser.error("--trials 和 --jobs 必须至少为 1")
    try:
        config, snapshot = load_config(args.config)
        tasks = select_tasks(args.tasks, args.set)
        run, summary = execute(config, snapshot, tasks, args.trials, args.jobs, args.run_id)
    except (ValueError, FileNotFoundError, FileExistsError, RuntimeError) as error:
        parser.exit(2, str(error) + "\n")
    print(f"{summary['status']}；结果：{run / 'summary.json'}")
    return 0 if summary["status"] == "completed" else 1


if __name__ == "__main__":
    raise SystemExit(main())
