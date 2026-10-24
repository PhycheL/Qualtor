#!/usr/bin/env python3
"""真实 Docker + pi + 本地剧本 provider 的确定性验收；不调用真实模型。"""
import argparse
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from host import GenerationExecutor, trial
from paths import RUNS, REPO, TOOLCHAINS
from audit import Audit
from common import (calibration_status, check_run_id, default_run_id, load_task, read_json, sha256_file,
                    sha256_text, write_json, now)
from docker_runner import DockerExecutor
from cost import extract
from scenarios import SCENARIOS, BUILD, config, write


def run_case(name, run, executor, generator, generation_only=False):
    task = load_task("gildedrose-update-quality")
    plan = [write((TOOLCHAINS / "smoke/rose_tests.cc").read_text()), BUILD] if name == "smoke" else SCENARIOS[name]
    directory = run / name
    if generation_only:
        record = generator.generate(task, config(), directory, plan if not callable(plan) else plan(1),
                                    watchdog=8 if name == "generation_stalled" else 900)
        write_json(directory / "cost.json", extract(directory))
        result = record
    else:
        calibration = calibration_status(executor.images, task)
        if calibration["status"] != "passed":
            raise ValueError(f"完整自测要求评分器已校准：{calibration}")
        result = trial(executor, generator, task, config(), directory, 1, "framework-scripted", calibration,
                       scenario=plan, watchdog=8 if name == "generation_stalled" else 900)
    expected = name if name in ("budget_exhausted", "never_built", "generation_stalled") else "finished"
    if name == "agent_error_persistent" or (generation_only and name == "agent_error"):
        expected = "agent_error"
    checks = {"status": result["status"] == expected}
    if name == "budget_exhausted":
        checks["budget_calls"] = result["build_calls"] == 4
        checks["budget_rejection"] = "budget_denied" in (directory / "logs/orchestrator/events.jsonl").read_text()
    if name == "never_built":
        checks["identical_products"] = read_json(directory / "first/manifest.json")["files"] == read_json(directory / "final/manifest.json")["files"]
    if name in ("finished", "compile_repair"):
        checks["different_products"] = read_json(directory / "first/manifest.json")["files"] != read_json(directory / "final/manifest.json")["files"]
        checks["one_repair"] = result["repair_rounds"] == 1
        checks["final_build_passed"] = read_json(directory / "attempts/attempt-2/result.json")["status"] == "passed"
        if not generation_only:
            checks["first_invalid_final_scored"] = (result["scores"]["first"]["status"] == "invalid"
                                                       and result["scores"]["final"]["status"] == "scored")
    if name == "agent_error" and not generation_only:
        checks["fresh_retries"] = result["generation_attempts"] == 3 and len(result["failed_generations"]) == 2
    if name == "agent_error_persistent" and not generation_only:
        checks["retry_limit"] = result["generation_attempts"] == 3 and not result["scores"]
    if name == "access_denied":
        events = directory / "logs/orchestrator/events.jsonl"
        checks["denials"] = events.exists() and events.read_text().count('"kind": "access_denied"') == 5
    if name == "smoke":
        built = read_json(directory / "attempts/attempt-1/result.json") if (directory / "attempts/attempt-1/result.json").is_file() else {}
        checks["nine_tests"] = built.get("status") == "passed" and len(built.get("tests", {})) == 9
    if name == "process_isolation":
        built = read_json(directory / "attempts/attempt-1/result.json")
        checks["protection_assertions_passed"] = built["status"] == "passed" and len(built["tests"]) == 2
    if not generation_only and expected != "agent_error":
        checks["both_scored"] = len(result["scores"]) == 2 and all(s["status"] != "infra_error" for s in result["scores"].values())
    entry = {"case": name, "passed": all(checks.values()), "checks": checks, "generation": result}
    write_json(run / f"{name}-checks.json", entry)
    return entry


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cases", nargs="+", default=["smoke", *SCENARIOS])
    parser.add_argument("--generation-only", action="store_true", help="只验收生成，不作独立隐藏评分")
    parser.add_argument("--closed-loop", action="store_true", help="用剧本模型驱动正式 run 编排器，验收多 trial 与汇总")
    parser.add_argument("--trials", type=int, default=5)
    parser.add_argument("--jobs", type=int, default=1)
    parser.add_argument("--run-id", default=default_run_id("eval-selftest"))
    args = parser.parse_args()
    if args.closed_loop:
        if args.trials < 1 or args.jobs < 1 or args.generation_only:
            parser.error("closed-loop 要求正整数 trials/jobs，且不能跳过评分")
        from run import execute
        import json
        model = config()
        run, summary = execute(model, {"name": "framework-scripted", "sha256": sha256_text(json.dumps(model)), "settings": model},
                               [load_task("gildedrose-update-quality")], args.trials, args.jobs, args.run_id,
                               scenario=SCENARIOS["finished"])
        checks = {"completed": summary["status"] == "completed", "trial_count": len(summary["trials"]) == args.trials,
                  "first_invalid_final_scored": all(t["scores"].get("first", {}).get("status") == "invalid"
                       and t["scores"].get("final", {}).get("status") == "scored" for t in summary["trials"])}
        write_json(run / "checks.json", {"passed": all(checks.values()), "checks": checks})
        print(f"闭环自测：{checks}；{run / 'summary.json'}")
        return 0 if all(checks.values()) else 1
    check_run_id(args.run_id)
    run = RUNS / args.run_id
    run.mkdir(parents=True, exist_ok=False)
    manifest = {"kind": "eval", "framework_selftest": True, "started_at": now(), "status": "running"}
    write_json(run / "run.json", manifest)
    executor = DockerExecutor(Audit(run / "evidence/host"), run / "evidence", args.run_id)
    generator = GenerationExecutor(executor)
    results = []
    for name in args.cases:
        print(f"自测 {name}", flush=True)
        entry = run_case(name, run, executor, generator, args.generation_only)
        results.append(entry)
        print(f"  {'通过' if entry['passed'] else '失败'}：{entry['checks']}", flush=True)
    passed = all(r["passed"] for r in results)
    manifest.update(status="passed" if passed else "failed", finished_at=now())
    write_json(run / "run.json", manifest)
    write_json(run / "summary.json", {**manifest, "cases": results})
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())
