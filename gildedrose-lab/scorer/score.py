#!/usr/bin/env python3
"""评分入口：给一份冻结的测试产物打分，或用当前评分器补评一次历史运行。

用法（在装有 Docker 和两个工具链镜像的机器上，从项目根目录执行）：
    python3 gildedrose-lab/scorer/score.py --task gildedrose-update-quality --product <产物目录> \\
        --cost <cost.json> --agent-version <版本> --trial 1 --phase final
    python3 gildedrose-lab/scorer/score.py --rescore <旧 run-id>
产物目录包含 manifest.json 和 tests/；用 freeze_product.py 冻结。结果写到 runs/<run-id>/。
"""
import argparse
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "scripts"))

from audit import Audit  # noqa: E402
from common import (ARTIFACTS, LAB, RUNS, calibration_status, check_run_id, default_run_id, load_task,  # noqa: E402
                    read_json, sha256_file)
import pipeline  # noqa: E402


def label_for(meta):
    return f"{meta.get('agent_version') or 'unknown'}-trial-{meta.get('trial') or 0}-{meta.get('phase') or 'final'}"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--task")
    parser.add_argument("--product", type=Path)
    parser.add_argument("--cost", type=Path)
    parser.add_argument("--agent-version")
    parser.add_argument("--trial", type=int)
    parser.add_argument("--phase", choices=["first", "final"], default="final")
    parser.add_argument("--rescore", help="补评一个历史运行目录里的全部产物")
    parser.add_argument("--run-id", default=default_run_id("score"))
    args = parser.parse_args()
    check_run_id(args.run_id)
    if not args.rescore and not (args.task and args.product):
        parser.error("需要 --task 和 --product，或者 --rescore")
    from docker_runner import DockerExecutor
    run_dir, evidence = RUNS / args.run_id, ARTIFACTS / "scorer" / args.run_id
    if run_dir.exists() or evidence.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    evidence.mkdir(parents=True)
    executor = DockerExecutor(Audit(evidence / "host"), evidence, args.run_id)
    jobs = []
    if args.rescore:
        old = RUNS / args.rescore
        for path in sorted(old.rglob("result.json")):
            result = read_json(path)
            product = LAB / result["product"]["path"]
            manifest = product / "manifest.json"
            if not manifest.is_file() or sha256_file(manifest) != result["product"]["manifest_sha256"]:
                print(f"跳过 {path}：产物已不存在或已改变", file=sys.stderr)
                continue
            cost = result["meta"].get("cost_path")
            jobs.append((result["task"]["id"], product, LAB / cost if cost else None,
                         dict(result["meta"], rescored_from=str(path.relative_to(LAB))),
                         path.parent.relative_to(old)))
    else:
        meta = {"agent_version": args.agent_version, "trial": args.trial, "phase": args.phase,
                "cost_path": pipeline._rel(args.cost.resolve(), LAB) if args.cost else None}
        task = load_task(args.task)
        jobs.append((task["id"], args.product, args.cost, meta, Path("tasks") / task["id"] / label_for(meta)))
    status = 0
    for task_id, product, cost, meta, rel in jobs:
        task = load_task(task_id)
        calibration = calibration_status(executor.images, task)
        if calibration["status"] != "passed":
            print(f"警告：评分器校准状态为 {calibration['status']}，结果不能用于正式比较", file=sys.stderr)
        out = run_dir / rel
        result = pipeline.score_product(executor, task, product, out, meta, Audit(out.parent / (out.name + "-host")),
                                        cost, calibration=calibration)
        print(f"{rel}: {result['status']} {result.get('invalid_reason') or ''} {result.get('infra_detail') or ''}")
        status |= result["status"] == "infra_error"
    print(f"结果目录：{run_dir}")
    return 1 if status else 0


if __name__ == "__main__":
    raise SystemExit(main())
