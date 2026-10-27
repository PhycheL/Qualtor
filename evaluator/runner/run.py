#!/usr/bin/env python3
"""一条命令运行 pi 生成、修复、冻结、首次/最终评分及按集合汇总。"""
import argparse
from collections import Counter
from concurrent.futures import CancelledError, ThreadPoolExecutor, as_completed
from pathlib import Path
import sys
import threading

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from host import GenerationExecutor, git_snapshot, load_config, public_task, tree_hash, trial
from cost import add_costs
from product_process import Cancellation
from paths import AGENTS, BENCHMARK, GENERATOR, RUNS, REPO
from audit import Audit
from runs import finish, new_manifest, write_manifest
from common import (calibration_status, check_run_id, default_run_id, load_baseline, load_task, now,
                    assessment_code_sha256, assessment_version, sha256_file, task_sha256, validate_task, write_json)
from docker_runner import DockerExecutor
import aggregate


def select_tasks(names, task_set):
    selected, skipped = {}, set()
    for name in names:
        whole = name == "all" or Path(name).resolve() == BENCHMARK
        if whole:
            choices = [p.parent for p in BENCHMARK.glob("*/task.json")]
        else:
            choices = [p for p in name.split(",") if p]
        for choice in choices:
            task = load_task(choice)
            if task_set is not None and task["set"] != task_set:
                continue
            # 未标定变异分母的题目评分必然是基础设施错误：点名时在生成前报错，批量选择时跳过。
            if load_baseline(task) is None:
                if not whole:
                    raise ValueError(f"题目 {task['id']} 尚未标定变异分母，先运行 prepare_task.py baseline --write")
                skipped.add(task["id"])
                continue
            public_task(task)
            selected[task["id"]] = task
    if skipped:
        print("跳过尚未标定变异分母的题目：" + ", ".join(sorted(skipped)), file=sys.stderr)
    if not selected:
        raise ValueError("没有符合筛选条件的题目")
    return list(selected.values())


def infrastructure_failure(result):
    if result.get("status") == "cancelled":
        return "生成已由用户取消"
    if result.get("status") == "agent_error":
        return "生成基础设施错误，已耗尽重试"
    phases = [phase for phase, score in result.get("scores", {}).items() if score["status"] == "infra_error"]
    return f"评分基础设施错误，已耗尽重试：{', '.join(phases)}" if phases else None


def run_trials(work, jobs_list, jobs, cancel=None):
    """并行执行 trial。异常或基础设施重试耗尽即取消未开始项；正在运行的等其结束（D012）。"""
    results, errors, cancelled = [], [], []
    stopped = threading.Event()

    def guarded_work(task, index):
        # 在 worker 内关闸；不能等主线程读到异常后再取消，worker 此时可能已开始下一项。
        if stopped.is_set() or (cancel is not None and cancel.is_set()):
            raise CancelledError()
        try:
            result = work(task, index)
            if infrastructure_failure(result):
                stopped.set()
            return result
        except Exception:
            stopped.set()
            raise

    with ThreadPoolExecutor(max_workers=jobs) as pool:
        futures = {pool.submit(guarded_work, task, index): (task["id"], index) for task, index in jobs_list}
        for future in as_completed(futures):
            label = futures[future]
            if future.cancelled():
                cancelled.append({"task": label[0], "trial": label[1]})
                continue
            try:
                result = future.result()
                results.append(result)
                failure = infrastructure_failure(result)
                if failure:
                    errors.append({"task": label[0], "trial": label[1], "error": failure})
            except CancelledError:
                cancelled.append({"task": label[0], "trial": label[1]})
            except Exception as error:
                errors.append({"task": label[0], "trial": label[1], "error": f"{type(error).__name__}: {error}"})
            if stopped.is_set():
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
                "generator_sha256": tree_hash(GENERATOR), "agent_product_sha256": tree_hash(AGENTS),
                "scorer_version": assessment_version(),
                "scorer_code_sha256": assessment_code_sha256()})
    write_manifest(run, manifest)
    try:
        executor = DockerExecutor(audit, run / "evidence", run_id)
        states = {t["id"]: calibration_status(executor.images, t) for t in tasks}
        manifest["calibration"] = states
        if any(s["status"] != "passed" for s in states.values()):
            raise ValueError(f"评测模块校准必须为 passed，当前：{states}；请先运行 calibrate.py")
        generator = GenerationExecutor(executor)
        manifest.update(images=executor.images, generation_runtime="host-pi")
        write_manifest(run, manifest)
        agent_version = config_snapshot["name"] + "@" + manifest["qualtor"]["commit"][:12] + "-" + config_snapshot["sha256"][:12]
        def work(task, index):
            print(f"生成与评分 {task['id']} trial-{index}", flush=True)
            result = trial(executor, generator, task, config, run / "trials" / task["id"] / f"trial-{index}",
                           index, agent_version, states[task["id"]], scenario, watchdog)
            print(f"  {task['id']} trial-{index}: {result['status']} "
                  + ", ".join(f"{p}={s['status']}" for p, s in result["scores"].items()), flush=True)
            return result
        with Cancellation() as cancellation:
            generator.cancel = cancellation
            results, errors, cancelled = run_trials(work, [(task, index) for task in tasks for index in range(1, count + 1)], jobs, cancellation)
            if cancellation.is_set():
                manifest["cancellation_signal"] = cancellation.signum
                errors.append({"error": "用户取消评测", "signal": cancellation.signum})
        if errors:
            # 基础设施异常：未开始的 trial 已取消，避免继续消耗模型费用；已完成的结果原样保留。
            summary = {"run_id": run_id, "status": "failed", "scorer_version": assessment_version(),
                       "framework_selftest": scenario is not None, "errors": errors, "cancelled_trials": cancelled,
                       "trial_statuses": dict(Counter(r["status"] for r in results)),
                       "trials": sorted(results, key=lambda r: (r["task"], r["trial"]))}
            write_json(run / "summary.json", summary)
            if cancellation.is_set():
                raise RuntimeError(f"评测已取消；保留 {len(results)} 个已启动 trial 的结果，取消 {len(cancelled)} 个未开始 trial")
            raise RuntimeError(f"{len(errors)} 个 trial 出现基础设施异常，已取消 {len(cancelled)} 个未开始的 trial：{errors[0]['error']}")
        for task in tasks:
            validate_task(task)
        if (tree_hash(GENERATOR) != manifest["generator_sha256"]
                or tree_hash(AGENTS) != manifest["agent_product_sha256"]
                or assessment_code_sha256() != manifest["scorer_code_sha256"]
                or tree_hash(AGENTS / "pi", runtime=True) != manifest["pi_runtime_sha256"]):
            raise ValueError("运行期间框架或 pi 文件发生变化，本轮不用于正式比较")
        scores = aggregate.load_results([run], version=assessment_version())
        summary = {"run_id": run_id, "scorer_version": assessment_version(), "framework_selftest": scenario is not None,
                   "trial_statuses": dict(Counter(r["status"] for r in results)), "trials": sorted(results, key=lambda r: (r["task"], r["trial"])),
                   "sets": {task_set: {phase: aggregate.summarize(scores, task_set, phase) for phase in ("first", "final")}
                            for task_set in sorted({t["set"] for t in tasks})}}
        summary["all_generation_cost"] = add_costs(
            {"tokens": {"input": 0, "output": 0, "cache_read": 0, "cache_write": 0},
             "seconds": 0, "model_calls": 0, "repair_rounds": 0, "usd": 0},
            [r["cost"]["final"] for r in results])
        # D012：基础设施故障已在上面终止，此处仅处理完整执行的 run。
        summary["status"] = "completed"
        write_json(run / "summary.json", summary)
    except BaseException as error:
        audit.event(kind="run_error", error=str(error))
        finish(run, manifest, "failed", error=str(error))
        raise
    finish(run, manifest, "completed")
    return run, summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", default="default")
    parser.add_argument("--env-file", help="显式指定产品连接配置；默认 agents/.env")
    parser.add_argument("--tasks", nargs="+", default=["gildedrose-update-quality"])
    parser.add_argument("--set", choices=["dev", "acceptance"])
    parser.add_argument("--trials", type=int, default=5)
    parser.add_argument("--jobs", type=int, default=1)
    parser.add_argument("--run-id", default=default_run_id("eval"))
    args = parser.parse_args()
    if args.trials < 1 or args.jobs < 1:
        parser.error("--trials 和 --jobs 必须至少为 1")
    try:
        config, snapshot = load_config(args.config, args.env_file)
        tasks = select_tasks(args.tasks, args.set)
        run, summary = execute(config, snapshot, tasks, args.trials, args.jobs, args.run_id)
    except (ValueError, FileNotFoundError, FileExistsError, RuntimeError) as error:
        parser.exit(2, str(error) + "\n")
    print(f"{summary['status']}；结果：{run / 'summary.json'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
