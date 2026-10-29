"""产品生成入口：公开任务、空工作区、宿主机 pi、错误重试和成本。"""
import os
from pathlib import Path
import shutil
import sys
import time

from common.audit import Audit
from generator.build.artifacts import freeze
from generator.cost import extract, add_costs
from generator.support import AGENTS, read_json, write_json, sha256_file, verify_pi
from generator.task import task_text


def generate_attempt(task, model, record, scenario, watchdog, cancel=None):
    record = Path(record)
    record.mkdir(parents=True, exist_ok=False)
    workspace = record / "workspace"
    (workspace / "tests").mkdir(parents=True)
    (workspace / "project").mkdir()
    (record / "logs").mkdir()
    source_hashes = {}
    for rel in task["visible_files"]:
        source, target = Path(task["source_root"]) / rel, workspace / "project" / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, target)
        target.chmod(0o444)
        source_hashes[rel] = sha256_file(target)
    write_json(record / "source-manifest.json", {"files": source_hashes})
    (workspace / "TASK.md").write_text(task_text(task))
    (workspace / "TASK.md").chmod(0o444)
    write_json(record / "input/runtime.json", {"task": task, "model": model, "scripted": scenario is not None,
                                                "watchdog_seconds": watchdog})
    if scenario is not None:
        write_json(record / "input/scenario.json", scenario)
    started = time.time()
    # 单次尝试独立进程。pi 只继承选中密钥，Docker 不接收它；日志由监督进程脱敏。
    audit = Audit(record / "logs/host")
    result = audit.run("launch-pi", [sys.executable, str(AGENTS / "generator/runtime/launch.py"), str(record)],
                       timeout=None, cancel=cancel, cancel_grace=60)
    if not (record / "generation.json").is_file():
        state = read_json(record / "build-state.json") if (record / "build-state.json").is_file() else {}
        for phase in ("first", "final"):
            if not (record / phase).exists():
                freeze(workspace / "tests", record / phase)
        write_json(record / "generation.json", {"status": "cancelled" if result["cancelled"] else "agent_error", "started_at": started,
                   "ended_at": time.time(), "first_at": state.get("first_at"), "build_calls": state.get("calls", 0),
                   "repair_rounds": state.get("repair_rounds", 0), "supervisor_exit_code": result["returncode"]})
    if cancel is not None and cancel.is_set():
        generation = read_json(record / "generation.json")
        generation.update(status="cancelled", cancellation_signal=cancel.signum)
        write_json(record / "generation.json", generation)
    for rel, digest in source_hashes.items():
        if sha256_file(workspace / "project" / rel) != digest or sha256_file(Path(task["source_root"]) / rel) != digest:
            raise ValueError("运行期间可见源码改变，本次产物不能用于比较")
    return read_json(record / "generation.json")


def generate(task, model, output, scenario=None, watchdog=900, attempts=3, cancel=None):
    stamp = verify_pi()
    output = Path(output).resolve()
    output.mkdir(parents=True, exist_ok=False)
    write_json(output / "runtime.json", {"mode": "host-pi", "product_pid": os.getpid(), "pi": stamp})
    if task.get('build', {}).get('environment'):
        from generator.build.docker import DockerCompiler
        # 在生成重试循环与模型启动之前失败，避免把缺包误报给模型或重复生成。
        started = time.time()
        try:
            DockerCompiler(output / 'environment-preflight', cancel, task=task)
        except (ValueError, OSError, RuntimeError):
            if cancel is None or not cancel.is_set():
                raise
            empty = output / 'workspace/tests'
            empty.mkdir(parents=True)
            for phase in ('first', 'final'):
                freeze(empty, output / phase)
            generation = {'status': 'cancelled', 'cancellation_signal': cancel.signum,
                          'started_at': started, 'ended_at': time.time(), 'first_at': None,
                          'build_calls': 0, 'repair_rounds': 0}
            write_json(output / 'generation.json', generation)
            cost = extract(output, priced=model.get('cost_per_million') is not None or scenario is not None)
            cost.update(generation_attempts=0, includes_retry_cost=True)
            write_json(output / 'cost.json', cost)
            result = {'schema': 1, 'task': task['id'], **generation, 'generation_attempts': 0,
                      'failed_generations': [], 'cost': cost, 'runtime': 'host-pi', 'toolchain': None}
            write_json(output / 'result.json', result)
            return result
    failures = []
    for attempt in range(1, attempts + 1):
        record = output / "generation-attempts" / f"attempt-{attempt}"
        # 自测可为每次错误重试指定独立剧本；真实模型使用相同公开任务。
        plan = scenario[attempt - 1] if scenario and isinstance(scenario[0], list) else scenario
        generation = generate_attempt(task, model, record, plan, watchdog, cancel)
        cost = extract(record, priced=model.get("cost_per_million") is not None or scenario is not None)
        write_json(record / "cost.json", cost)
        if generation["status"] == "agent_error":
            failures.append({"record": str(record.relative_to(output)), "cost": cost["final"]})
        if generation["status"] != "agent_error" or (cancel is not None and cancel.is_set()):
            break
    # 包含首次/最终产物、日志、attempts 的交付结果固定在根目录；原始尝试保持原位可审计。
    for path in record.iterdir():
        if path.is_dir():
            shutil.copytree(path, output / path.name)
        else:
            shutil.copy2(path, output / path.name)
    # 最后一次已经包含在 cost 中；即使收尾被取消，也不能重复累计其费用。
    prior = [f["cost"] for f in failures if f["record"] != str(record.relative_to(output))]
    cost = {**cost, "first": add_costs(cost["first"], prior), "final": add_costs(cost["final"], prior),
            "generation_attempts": attempt, "includes_retry_cost": True}
    write_json(output / "cost.json", cost)
    # 成本提取和证据复制可能较慢，须在交付结果落盘前再次接收取消。
    # 原始 attempt 保留监督进程结束时的状态，根目录记录整个产品调用的状态。
    if cancel is not None and cancel.is_set():
        generation = {**generation, "status": "cancelled", "cancellation_signal": cancel.signum}
    write_json(output / "generation.json", generation)
    result = {"schema": 1, "task": task["id"], **generation, "generation_attempts": attempt,
              "failed_generations": failures, "cost": cost, "runtime": "host-pi",
              "toolchain": read_json(output / "toolchain.json") if (output / "toolchain.json").exists() else None}
    write_json(output / "result.json", result)
    return result
