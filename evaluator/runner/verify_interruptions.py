#!/usr/bin/env python3
"""用真实 pi、本地剧本和 Docker 验证用户中断；不调用模型 API。"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import signal
import sys
import threading
import time

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from host import public_task
from product_process import run_product
from scenarios import GOOD, BUILD, write
from audit import Audit
from common import check_run_id, default_run_id, load_task, read_json, write_json
from paths import AGENTS, REPO, RUNS
from runs import finish, new_manifest, write_manifest


def wait_for(predicate, seconds=60):
    deadline = time.monotonic() + seconds
    while time.monotonic() < deadline:
        try:
            result = predicate()
            if result:
                return result
        except (FileNotFoundError, json.JSONDecodeError):
            pass
        time.sleep(0.05)
    raise TimeoutError("没有到达预期中断位置")


def events(path):
    return [json.loads(line) for line in path.read_text().splitlines() if line]


def pi_started(output):
    return next((e for e in events(output / "generation-attempts/attempt-1/logs/orchestrator/events.jsonl")
                 if e["kind"] == "pi_start"), None)


def no_process(pid):
    try:
        os.kill(pid, 0)
        return False
    except ProcessLookupError:
        return True


def check_product(output, pids, audit):
    result = read_json(output / "result.json")
    checks = {"cancelled": result["status"] == "cancelled", "no_retry": result["generation_attempts"] == 1,
              "cost_retained": result["cost"]["final"]["model_calls"] >= 1,
              "processes_reaped": all(no_process(pid) for pid in pids)}
    for phase in ("first", "final"):
        manifest = read_json(output / phase / "manifest.json")
        checks[phase + "_frozen"] = bool(manifest["files"]) and all(
            hashlib.sha256((output / phase / rel).read_bytes()).hexdigest() == digest
            for rel, digest in manifest["files"].items())
    for file in (output / "generation-attempts").glob("*/attempts/*/container.json"):
        container = read_json(file)
        inspected = audit.run("check-container-removed", ["docker", "inspect", container["Id"]])
        checks["removed_" + container["Name"].lstrip("/")] = inspected["returncode"] != 0 and "No such" in inspected["stderr"]
    return checks


def product_case(root, label, signum, during_build, audit):
    request, output = root / label / "request", root / label / "product"
    task = public_task(load_task("gildedrose-update-quality"))
    task["test_timeout_seconds"] = 60
    content = GOOD + ('\n#include <unistd.h>\nTEST(Interrupt, Long) { sleep(30); EXPECT_EQ(1, 1); }\n' if during_build else '')
    plan = [write(content), BUILD] if during_build else [write(content), {"stall": True}]
    write_json(request / "task.json", task)
    write_json(request / "scenario.json", plan)
    fallback = threading.Event()
    observation = {}
    def interrupt():
        try:
            runtime = wait_for(lambda: read_json(output / "runtime.json"))
            pi = wait_for(lambda: pi_started(output))
            if during_build:
                log = output / "generation-attempts/attempt-1/attempts/attempt-1/output/logs/events.jsonl"
                wait_for(lambda: any(e.get("kind") == "command_start" and e.get("stage") == "test-1" for e in events(log)))
            else:
                log = output / "generation-attempts/attempt-1/logs/pi.stdout.jsonl"
                wait_for(lambda: any(e.get("type") == "tool_execution_end" for e in events(log)))
            observation.update(product_pid=runtime["product_pid"], pi_pid=pi["pid"], supervisor_pid=pi["supervisor_pid"])
            audit.event(kind="inject_signal", case=label, signal=signum, **observation)
            os.kill(runtime["product_pid"], signum)
        except Exception as error:
            observation["error"] = str(error)
            fallback.set()
    thread = threading.Thread(target=interrupt)
    thread.start()
    execution = run_product(Audit(request / "audit"), [sys.executable, str(AGENTS / "run.py"),
        "--task", str(request / "task.json"), "--output", str(output), "--scenario", str(request / "scenario.json"),
        "--watchdog", "90"], fallback)
    thread.join()
    if "error" in observation:
        raise RuntimeError(observation["error"])
    checks = check_product(output, list(observation.values()), audit)
    checks["signal_exit_code"] = execution["returncode"] == 128 + signum
    checks["build_stage_reached"] = read_json(output / "result.json")["build_calls"] == (1 if during_build else 0)
    return {"case": label, "passed": all(checks.values()), "checks": checks}


def batch_case(root, audit):
    batch_id = root.name + "-batch"
    batch = RUNS / batch_id
    entry = root / "evidence/batch.py"
    pid_file = root / "evidence/batch.pid"
    entry.parent.mkdir(parents=True, exist_ok=True)
    entry.write_text(f'''import os, sys
from pathlib import Path
sys.path.insert(0, {str(HERE)!r})
from run import execute
from scenarios import config, write
from common import load_task, sha256_text
import json
Path({str(pid_file)!r}).write_text(str(os.getpid()))
model = config()
execute(model, {{"name":"framework-scripted", "sha256":sha256_text(json.dumps(model)), "settings":model}},
        [load_task("gildedrose-update-quality")], 5, 2, {batch_id!r}, scenario=[write(), {{"stall":True}}])
''')
    fallback = threading.Event()
    observation = {}
    def interrupt():
        try:
            products = [batch / "trials/gildedrose-update-quality" / f"trial-{i}" for i in (1, 2)]
            pids = []
            for output in products:
                runtime = wait_for(lambda: read_json(output / "runtime.json"))
                pi = wait_for(lambda: pi_started(output))
                log = output / "generation-attempts/attempt-1/logs/pi.stdout.jsonl"
                wait_for(lambda: any(e.get("type") == "tool_execution_end" for e in events(log)))
                pids.append([runtime["product_pid"], pi["pid"], pi["supervisor_pid"]])
            observation["pids"] = pids
            pid = int(pid_file.read_text())
            audit.event(kind="inject_signal", case="batch", pid=pid, signal=signal.SIGINT)
            os.kill(pid, signal.SIGINT)
        except Exception as error:
            observation["error"] = str(error)
            fallback.set()
    thread = threading.Thread(target=interrupt)
    thread.start()
    execution = run_product(Audit(root / "evidence/batch"), [sys.executable, str(entry)], fallback)
    thread.join()
    if "error" in observation:
        raise RuntimeError(observation["error"])
    summary = read_json(batch / "summary.json")
    checks = {"failed": summary["status"] == read_json(batch / "run.json")["status"] == "failed",
              "nonzero_exit": execution["returncode"] != 0, "queued_cancelled": len(summary["cancelled_trials"]) == 3,
              "active_cancelled": len(summary["trials"]) == 2 and all(t["status"] == "cancelled" and not t["scores"] for t in summary["trials"])}
    for i, pids in enumerate(observation["pids"], 1):
        for name, passed in check_product(batch / "trials/gildedrose-update-quality" / f"trial-{i}", pids, audit).items():
            checks[f"trial-{i}_{name}"] = passed
    return {"case": "batch", "run": batch_id, "passed": all(checks.values()), "checks": checks}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run-id", default=default_run_id("eval-interruptions"))
    args = parser.parse_args()
    check_run_id(args.run_id)
    root = RUNS / args.run_id
    root.mkdir(parents=True, exist_ok=False)
    manifest = new_manifest(args.run_id, "eval", operation="interruptions", framework_selftest=True)
    write_manifest(root, manifest)
    audit = Audit(root / "evidence/host")
    cases = []
    try:
        for label, signum, building in (("sigint-model-wait", signal.SIGINT, False), ("sigterm-docker", signal.SIGTERM, True)):
            print(label, flush=True)
            cases.append(product_case(root, label, signum, building, audit))
        print("batch-cancellation", flush=True)
        cases.append(batch_case(root, audit))
        passed = all(c["passed"] for c in cases)
        finish(root, manifest, "completed", passed=passed)
    except BaseException as error:
        finish(root, manifest, "failed", error=str(error))
        raise
    finally:
        write_json(root / "summary.json", {**manifest, "cases": cases})
    print(json.dumps({"passed": passed, "cases": cases}, ensure_ascii=False), flush=True)
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())
