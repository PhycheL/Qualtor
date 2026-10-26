#!/usr/bin/env python3
"""宿主机 pi 监督进程：事件记录、看门狗和结束时保存测试快照；C++ 由独立 Docker 服务执行。"""
import json
import os
from pathlib import Path
import signal
import shutil
import subprocess
import sys
import threading
import time
import traceback
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from common.audit import Audit, now
from common.processes import Cancellation, stop_process
from generator.build.service import BuildService, serve
from generator.build.artifacts import freeze
from generator.support import AGENTS, read_json, write_json


def copy_regular(source, destination):
    """只复制普通文件和目录，不跟随链接、不复制特殊文件。"""
    source, destination = Path(source), Path(destination)
    destination.mkdir(parents=True, exist_ok=True)
    for path in sorted(source.rglob("*")):
        if path.is_symlink() or not (path.is_dir() or path.is_file()):
            continue
        target = destination / path.relative_to(source)
        if path.is_dir():
            target.mkdir(parents=True, exist_ok=True)
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(path, target)


def stalled_for(now_monotonic, last_event, service):
    """距最近一次进展的秒数。编译与测试进行中不计时，它们由各自的阶段超时约束。"""
    if service.busy:
        return 0.0
    return now_monotonic - max(last_event, service.last_activity)


def supervise(RECORD, cancel):
    config = read_json(RECORD / "input/runtime.json")
    RECORD.chmod(0o700)
    state_dir, session_dir = RECORD / "pi-state", RECORD / "logs/sessions"
    workspace = RECORD / "workspace"
    for path in (state_dir, session_dir, RECORD / "attempts"):
        path.mkdir(parents=True, exist_ok=True)
    write_json(state_dir / "settings.json", {"retry": {"enabled": False}, "quietStartup": True,
               "enableInstallTelemetry": False, "enableAnalytics": False})
    audit = Audit(RECORD / "logs/orchestrator")
    env = {k: os.environ[k] for k in ("PATH", "LANG", "LC_ALL") if k in os.environ}
    env.update(HOME=str(state_dir), PI_CODING_AGENT_DIR=str(state_dir),
               PI_OFFLINE="1", PI_TELEMETRY="0", NO_COLOR="1",
               QUALTOR_WORKSPACE=str(workspace),
               QUALTOR_RUNTIME_CONFIG=str(RECORD / "input/runtime.json"),
               QUALTOR_SCENARIO=str(RECORD / "input/scenario.json"),
               XDG_CONFIG_HOME=str(state_dir / "xdg"))
    env["PATH"] = str(AGENTS / ".cache/tools/bin") + os.pathsep + env.get("PATH", "")
    secret_name = config["model"].get("api_key_env")
    secret = os.environ.get(secret_name, "") if secret_name else ""
    if secret_name:
        env[secret_name] = secret
    def redact(text):
        return text.replace(secret, "[REDACTED]") if secret else text
    command = ["node", str(AGENTS / "pi/packages/coding-agent/dist/cli.js"), "--mode", "json", "-nc", "-ne", "-ns", "-np",
               "--no-themes", "--no-mcp", "--offline", "--session-dir", str(session_dir),
               "--tools", "read,write,edit,grep,find,ls,build_and_test", "-e", str(AGENTS / "generator/runtime/extension.ts")]
    if config["scripted"]:
        command += ["-e", str(AGENTS / "generator/runtime/scripted.ts")]
    command += ["--provider", config["model"]["provider"], "--model", config["model"]["model"],
                "--thinking", config["model"]["thinking"], "阅读 TASK.md，完成其中的测试生成任务。"]
    started = time.time()
    last_event = [time.monotonic()]
    state = {"settled": False, "model_error": False, "tool_infra_error": False}
    def drain(pipe, name, output, events=False):
        with (RECORD / "logs" / name).open("w") as log:
            for line in iter(pipe.readline, ""):
                clean = redact(line)
                log.write(clean)
                log.flush()
                if events:
                    try:
                        event = json.loads(line)
                    except ValueError:
                        continue
                    # build_and_test 运行期间的进度心跳不代表 Agent 有进展，不刷新看门狗。
                    if event.get("type") != "tool_execution_update":
                        last_event[0] = time.monotonic()
                    if event.get("type") == "agent_settled":
                        state["settled"] = True
                    message = event.get("message") or {}
                    if event.get("type") == "message_end" and message.get("stopReason") in ("error", "aborted"):
                        state["model_error"] = True
                    if event.get("type") == "tool_execution_end" and (event.get("result") or {}).get("details", {}).get("infra_error"):
                        state["tool_infra_error"] = True
    process, service, server, control = None, None, None, None
    threads = []
    stalled, requested, failure = False, False, None
    try:
        service = BuildService(config["task"], RECORD, cancel)
        # macOS 的 Unix socket 路径长度有限，不能使用深层 trial 路径。
        control = tempfile.TemporaryDirectory(prefix="qualtor-", dir="/tmp")
        socket_path = Path(control.name) / "build.sock"
        env["QUALTOR_BUILD_SOCKET"] = str(socket_path)
        server = serve(service, socket_path)
        if not cancel.is_set():
            process = subprocess.Popen(command, cwd=workspace, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                       stdin=subprocess.DEVNULL, text=True, errors="replace", start_new_session=True)
            audit.event(kind="pi_start", argv=command, timestamp=started, pid=process.pid, supervisor_pid=os.getpid())
            threads = [threading.Thread(target=drain, args=(process.stdout, "pi.stdout.jsonl", sys.stdout, True), daemon=True),
                       threading.Thread(target=drain, args=(process.stderr, "pi.stderr.log", sys.stderr), daemon=True)]
            for thread in threads:
                thread.start()
            while process.poll() is None and not cancel.is_set():
                if stalled_for(time.monotonic(), last_event[0], service) >= config["watchdog_seconds"]:
                    stalled = True
                    audit.event(kind="watchdog", seconds=config["watchdog_seconds"])
                    break
                time.sleep(0.1)
    except Exception as error:
        failure = redact(str(error))
        audit.event(kind="supervisor_error", error=failure)
    finally:
        requested = cancel.is_set()
        # 同时通知编译线程退出，避免等到阶段超时；它的 finally 负责删除 Docker 容器。
        cancel.set()
        try:
            if process is not None:
                stop_process(process, grace=3)
            for thread in threads:
                thread.join(timeout=5)
            if server is not None:
                server.shutdown()
                server.server_close()
        finally:
            if control is not None:
                control.cleanup()
    calls = service.calls if service else 0
    if requested or cancel.signum is not None:
        status = "cancelled"
    elif stalled:
        status = "generation_stalled"
    elif failure or process is None or process.returncode or state["model_error"] or state["tool_infra_error"] or not state["settled"]:
        status = "agent_error"
    elif not calls:
        status = "never_built"
    elif calls >= config["task"]["budget"]["repair_rounds"] + 1:
        status = "budget_exhausted"
    else:
        status = "finished"
    freeze(workspace / "tests", RECORD / "final")
    if not (RECORD / "first").exists():
        freeze(workspace / "tests", RECORD / "first")
    result = {"status": status, "started_at": started, "ended_at": time.time(),
              "first_at": service.first_at if service else None,
              "build_calls": calls, "repair_rounds": max(0, calls - 1),
              "pi_exit_code": process.returncode if process else None,
              "cancellation_signal": cancel.signum if status == "cancelled" else None, **state}
    if failure:
        result["error"] = failure
    write_json(RECORD / "generation.json", result)
    audit.event(kind="pi_end", **result)
    # pi 会话有时含模型服务错误原文；保留结构，只替换实际凭证。
    for path in session_dir.rglob("*.jsonl"):
        if secret and path.is_file() and not path.is_symlink():
            path.write_text(redact(path.read_text()))
    for path in [RECORD / "logs/sessions", *(RECORD / "logs/sessions").rglob("*")]:
        path.chmod(0o755 if path.is_dir() else 0o644)
    return 128 + (cancel.signum or signal.SIGTERM) if status == "cancelled" else 0


def main():
    with Cancellation() as cancel:
        return supervise(Path(sys.argv[1]).resolve(), cancel)


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception:
        # 启动异常由产品入口记为 agent_error，保留原始记录后在新工作区重试。
        traceback.print_exc()
        raise SystemExit(1)
