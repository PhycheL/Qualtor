#!/usr/bin/env python3
"""评分冻结产物；--rescore 在原 run 的 score/<当前版本>/ 下补评，绝不覆盖旧版本。"""
import argparse
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent / "common")]
from audit import Audit
from common import (REPO, RUNS, calibration_status, check_run_id, default_run_id, load_task, now,
                    read_json, scorer_version, sha256_file, validate_product, write_json)
import pipeline


def rescore_jobs(run, version):
    jobs = {}
    for path in sorted(run.rglob("result.json")):
        if "infra-retries" in path.parts or "generation-attempts" in path.parts:
            continue
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
        if out.exists():
            raise ValueError(f"当前评分器版本已评过，拒绝覆盖：{out}")
        previous = jobs.get(key)
        if previous and previous[1] != product:
            raise ValueError(f"同一个 trial/phase 存在不同冻结产物：{key}")
        cost = REPO / meta["cost_path"] if meta.get("cost_path") else None
        jobs[key] = (task, product, cost, dict(meta, rescored_from=str(path.relative_to(REPO))), out)
    if not jobs:
        raise ValueError("run 中没有可补评的冻结产物（迁移的校准/标定记录不支持补评）")
    return list(jobs.values())


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
    args = parser.parse_args()
    if args.rescore and (args.run_id or args.task or args.product):
        parser.error("--rescore 写入原 run，不能同时指定 --run-id、--task 或 --product")
    if not args.rescore and not (args.task and args.product):
        parser.error("需要 --task 和 --product，或者 --rescore")
    version = scorer_version()
    try:
        if args.rescore:
            run_id = check_run_id(args.rescore)
            run = RUNS / run_id
            jobs = rescore_jobs(run, version)
            evidence = run / "score" / version / "evidence"
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
        manifest = {"kind": "eval", "run_id": run_id, "operation": "rescore" if args.rescore else "score",
                    "scorer_version": version, "status": "running", "started_at": now()}
        write_json(record_path, manifest)
        from docker_runner import DockerExecutor
        executor = DockerExecutor(Audit(evidence / "host"), evidence, run_id)
        failed = False
        for task, product, cost, meta, out in jobs:
            calibration = calibration_status(executor.images, task)
            if calibration["status"] != "passed":
                print(f"警告：校准状态为 {calibration['status']}，结果不能用于正式比较", file=sys.stderr)
            result = pipeline.score_product(executor, task, product, out, meta,
                        Audit(out.parent / "logs" / out.name), cost, calibration=calibration)
            failed |= result["status"] == "infra_error"
            print(f"{out.relative_to(run)}: {result['status']} {result.get('invalid_reason') or ''}")
        manifest.update(status="incomplete" if failed else "completed", finished_at=now())
        write_json(record_path, manifest)
    except (ValueError, FileNotFoundError, FileExistsError) as error:
        parser.exit(2, str(error) + "\n")
    print(f"结果目录：{run}")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
