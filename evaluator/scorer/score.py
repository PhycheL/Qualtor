#!/usr/bin/env python3
"""评分冻结产物；--rescore 在原 run 的 score/<当前版本>/ 下补评，绝不覆盖旧版本。

补评中断后可直接重跑同一命令：已有有效结果的产物跳过，未完成或基础设施错误的结果移入 incomplete/ 后重评。
评分器校准状态不是 passed 时拒绝评分；只做参考时加 --allow-uncalibrated，结果中会记录校准状态。
"""
import argparse
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent / "common")]
from audit import Audit
from runs import finish, new_manifest, write_manifest
from common import (REPO, RUNS, calibration_status, check_run_id, default_run_id, load_task, now,
                    read_json, scorer_code_sha256, scorer_version, sha256_file, validate_product, write_json)
import pipeline

INFRA_RETRIES = 2


def finished_result(out):
    """已有可用结果时返回它；没有 result.json 或结果为基础设施错误时返回 None。"""
    path = out / "result.json"
    if not path.is_file():
        return None
    try:
        result = read_json(path)
    except (ValueError, UnicodeError):
        return None  # 中断时可能留下空文件或半写 JSON，交给 set_aside 保留后重评。
    return result if isinstance(result, dict) and result.get("status") in ("scored", "invalid") else None


def set_aside(out):
    """未完成的评分目录移到 incomplete/ 下保留，不删除、不覆盖。"""
    holder = out.parent / "incomplete"
    holder.mkdir(exist_ok=True)
    index = 1
    while (holder / f"{out.name}-{index}").exists():
        index += 1
    out.rename(holder / f"{out.name}-{index}")


def score_with_retry(executor, task, product, out, meta, cost, calibration):
    for attempt in range(INFRA_RETRIES + 1):
        result = pipeline.score_product(executor, task, product, out, meta,
                                        Audit(out.parent / "logs" / f"{out.name}-{attempt + 1}"), cost,
                                        calibration=calibration)
        if result["status"] != "infra_error" or attempt == INFRA_RETRIES:
            return result
        set_aside(out)


def rescore_jobs(run, version):
    jobs = {}
    for path in sorted(run.rglob("result.json")):
        if {"infra-retries", "incomplete", "generation-attempts"} & set(path.parts):
            continue
        if path.parent.parent.name == version and path.parent.parent.parent.name == "score":
            continue  # 当前版本可能留下半写 JSON；只由 pending_jobs 判断能否复用。
        result = read_json(path)
        if result.get("mode") != "score" or not result.get("meta", {}).get("agent_version"):
            continue
        meta = result["meta"]
        key = (result["task"]["id"], meta.get("trial", 1), meta.get("phase", "final"))
        product = REPO / result["product"]["path"]
        manifest = product / "manifest.json"
        if not manifest.is_file() or sha256_file(manifest) != result["product"]["manifest_sha256"]:
            raise ValueError(f"冻结产物已改变：{product}")
        task = load_task(key[0])
        problem = validate_product(product, task)
        if problem:
            raise ValueError(f"冻结产物校验失败：{product}: {problem}")
        out = run / "trials" / key[0] / f"trial-{key[1]}" / "score" / version / key[2]
        if out == path.parent:
            continue  # 当前版本自己的结果，不是补评来源
        previous = jobs.get(key)
        if previous and previous[1] != product:
            raise ValueError(f"同一个 trial/phase 存在不同冻结产物：{key}")
        cost = REPO / meta["cost_path"] if meta.get("cost_path") else None
        jobs[key] = (task, product, cost, dict(meta, rescored_from=str(path.relative_to(REPO))), out)
    if not jobs:
        raise ValueError("run 中没有可补评的冻结产物（迁移的校准/标定记录不支持补评）")
    return list(jobs.values())


def pending_jobs(jobs, calibrations=None, images=None):
    """跳过已有可用结果的产物；未完成的旧目录移开后重评。"""
    pending, skipped = [], []
    code = scorer_code_sha256() if calibrations is not None else None
    for job in jobs:
        task, product, _, _, out = job
        done = finished_result(out)
        if done and calibrations is not None:
            # 参考结果、旧指纹结果必须重评；不能在校准通过后仍跳过旧的未校准结果。
            done = (done.get("scorer") == {"version": scorer_version(), "code_sha256": code,
                                          "calibration": calibrations[task["id"]]}
                    and done.get("task", {}).get("task_json_sha256") == task["_sha256"]
                    and done.get("product", {}).get("manifest_sha256") == sha256_file(product / "manifest.json")
                    and done.get("images") == images)
        if done:
            skipped.append(out)
            continue
        if out.exists():
            set_aside(out)
        pending.append(job)
    return pending, skipped


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--task")
    parser.add_argument("--product", type=Path)
    parser.add_argument("--cost", type=Path)
    parser.add_argument("--agent-version")
    parser.add_argument("--trial", type=int, default=1)
    parser.add_argument("--phase", choices=["first", "final"], default="final")
    parser.add_argument("--rescore")
    parser.add_argument("--run-id")
    parser.add_argument("--allow-uncalibrated", action="store_true",
                        help="校准状态不是 passed 时仍然评分，结果只作参考，不能用于正式比较")
    args = parser.parse_args()
    if args.rescore and (args.run_id or args.task or args.product):
        parser.error("--rescore 写入原 run，不能同时指定 --run-id、--task 或 --product")
    if not args.rescore and not (args.task and args.product):
        parser.error("需要 --task 和 --product，或者 --rescore")
    version = scorer_version()
    manifest, write = None, None
    try:
        if args.rescore:
            run_id = check_run_id(args.rescore)
            run = RUNS / run_id
            jobs = rescore_jobs(run, version)
            session = default_run_id("rescore")
            evidence = run / "score" / version / session / "evidence"
            evidence.mkdir(parents=True, exist_ok=False)
            record_path = evidence.parent / "rescore.json"
        else:
            run_id = check_run_id(args.run_id or default_run_id("eval"))
            run = RUNS / run_id
            run.mkdir(parents=True, exist_ok=False)
            evidence = run / "evidence"
            evidence.mkdir()
            task = load_task(args.task)
            out = run / "trials" / task["id"] / f"trial-{args.trial}" / "score" / version / args.phase
            meta = {"agent_version": args.agent_version, "trial": args.trial, "phase": args.phase,
                    "cost_path": pipeline._rel(args.cost.resolve(), REPO) if args.cost else None}
            jobs = [(task, args.product, args.cost, meta, out)]
            record_path = run / "run.json"
        manifest = new_manifest(run_id, "eval", operation="rescore" if args.rescore else "score",
                                scorer_version=version, jobs=len(jobs))
        write = (lambda m: write_json(record_path, m)) if args.rescore else (lambda m: write_manifest(run, m))
        write(manifest)
        from docker_runner import DockerExecutor
        executor = DockerExecutor(Audit(evidence / "host"), evidence, run_id)
        calibrations = {task["id"]: calibration_status(executor.images, task) for task, *_ in jobs}
        uncalibrated = {k: v["status"] for k, v in calibrations.items() if v["status"] != "passed"}
        if uncalibrated and not args.allow_uncalibrated:
            manifest.update(status="failed", error=f"校准状态不是 passed：{uncalibrated}", finished_at=now())
            write(manifest)
            raise ValueError(f"评分器校准状态不是 passed：{uncalibrated}；先运行 calibrate.py，"
                             "只做参考时加 --allow-uncalibrated")
        if uncalibrated:
            print(f"警告：校准状态为 {uncalibrated}，结果不能用于正式比较", file=sys.stderr)
        if args.rescore:
            jobs, skipped = pending_jobs(jobs, calibrations, executor.images)
            manifest.update(jobs=len(jobs), skipped=[str(out.relative_to(run)) for out in skipped])
            write(manifest)
            for out in skipped:
                print(f"已有结果，跳过：{out.relative_to(run)}")
        failed = False
        for task, product, cost, meta, out in jobs:
            result = score_with_retry(executor, task, product, out, meta, cost, calibrations[task["id"]])
            failed |= result["status"] == "infra_error"
            print(f"{out.relative_to(run)}: {result['status']} {result.get('invalid_reason') or ''}")
        manifest.update(status="incomplete" if failed else "completed", finished_at=now())
        write(manifest)
    except BaseException as error:
        if manifest is not None and write is not None:
            manifest.update(status="failed", error=f"{type(error).__name__}: {error}", finished_at=now())
            write(manifest)
        if isinstance(error, (ValueError, FileNotFoundError, FileExistsError, RuntimeError)):
            parser.exit(2, str(error) + "\n")
        raise
    print(f"结果目录：{run}")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
