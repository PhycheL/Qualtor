#!/usr/bin/env python3
"""生成容器入口：监督 pi、保存事件、检测无响应并冻结产物。"""
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

sys.path.insert(0, "/helpers")
from audit import Audit, now
from build_service import BuildService, RECORD, freeze, serve, write_json


def copy_regular(source, destination):
    """把 tmpfs 中的内容复制回宿主机记录目录；只复制普通文件和目录，不跟随链接、不复制特殊文件。"""
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


def main():
    config = json.loads(Path("/input/runtime.json").read_text())
    uid, gid = int(os.environ["QUALTOR_AGENT_UID"]), int(os.environ["QUALTOR_AGENT_GID"])
    RECORD.chmod(0o700)
    state_dir, session_dir = Path("/agent/state"), Path("/agent/sessions")
    for name in ("logs", "attempts"):
        (RECORD / name).mkdir(exist_ok=True)
    for path in (state_dir, session_dir, Path("/workspace/tests")):
        path.mkdir(parents=True, exist_ok=True)
        os.chown(path, uid, gid)
        path.chmod(0o700 if path.name != "tests" else 0o755)
    # 禁止继承用户机器的扩展、skill、会话和自动重试配置。
    settings = state_dir / "settings.json"
    write_json(settings, {"retry": {"enabled": False}, "quietStartup": True,
                          "enableInstallTelemetry": False, "enableAnalytics": False})
    os.chown(settings, uid, gid)
    Path("/control").mkdir(exist_ok=True)
    os.chown("/control", 0, gid)
    os.chmod("/control", 0o710)
    service = BuildService(config["task"])
    server = serve(service)
    audit = Audit(RECORD / "logs/orchestrator")
    env = {k: os.environ[k] for k in ("PATH", "LANG", "LC_ALL") if k in os.environ}
    env.update(HOME=str(state_dir), PI_CODING_AGENT_DIR=str(state_dir),
               PI_OFFLINE="1", PI_TELEMETRY="0", NO_COLOR="1")
    secret_name = config["model"].get("api_key_env")
    secret = os.environ.get(secret_name, "") if secret_name else ""
    if secret_name:
        env[secret_name] = secret
    def redact(text):
        return text.replace(secret, "[REDACTED]") if secret else text
    command = ["node", "/pi/packages/coding-agent/dist/cli.js", "--mode", "json", "-nc", "-ne", "-ns", "-np",
               "--no-themes", "--no-mcp", "--offline", "--session-dir", str(session_dir),
               "--tools", "read,write,edit,grep,find,ls,build_and_test", "-e", "/framework/extension.ts"]
    if config["scripted"]:
        command += ["-e", "/framework/scripted.ts"]
    command += ["--provider", config["model"]["provider"], "--model", config["model"]["model"],
                "--thinking", config["model"]["thinking"], "阅读 TASK.md，完成其中的测试生成任务。"]
    started = time.time()
    audit.event(kind="pi_start", argv=command, timestamp=started)
    process = subprocess.Popen(command, cwd="/workspace", env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                               stdin=subprocess.DEVNULL, text=True, errors="replace", user=uid, group=gid,
                               extra_groups=[], start_new_session=True)
    last_event = [time.monotonic()]
    state = {"settled": False, "model_error": False, "tool_infra_error": False}
    def drain(pipe, name, output, events=False):
        with (RECORD / "logs" / name).open("w") as log:
            for line in iter(pipe.readline, ""):
                clean = redact(line)
                log.write(clean)
                log.flush()
                output.write(clean)
                output.flush()
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
    threads = [threading.Thread(target=drain, args=(process.stdout, "pi.stdout.jsonl", sys.stdout, True)),
               threading.Thread(target=drain, args=(process.stderr, "pi.stderr.log", sys.stderr))]
    for thread in threads:
        thread.start()
    stalled = False
    while process.poll() is None:
        if stalled_for(time.monotonic(), last_event[0], service) >= config["watchdog_seconds"]:
            stalled = True
            audit.event(kind="watchdog", seconds=config["watchdog_seconds"])
            os.killpg(process.pid, signal.SIGKILL)
            break
        time.sleep(0.1)
    process.wait()
    for thread in threads:
        thread.join(timeout=5)
    server.shutdown()
    # 等正在执行的 build 收尾。其进程有独立阶段超时，预算/首次快照不会被中断重写。
    with service.lock:
        if stalled:
            status = "generation_stalled"
        elif process.returncode or state["model_error"] or state["tool_infra_error"] or not state["settled"]:
            status = "agent_error"
        elif not service.calls:
            status = "never_built"
        elif service.calls >= config["task"]["budget"]["repair_rounds"] + 1:
            status = "budget_exhausted"
        else:
            status = "finished"
        freeze(Path("/workspace/tests"), RECORD / "final")
        if not (RECORD / "first").exists():
            freeze(Path("/workspace/tests"), RECORD / "first")
        result = {"status": status, "started_at": started, "ended_at": time.time(), "first_at": service.first_at,
                  "build_calls": service.calls, "repair_rounds": max(0, service.calls - 1),
                  "pi_exit_code": process.returncode, **state}
        write_json(RECORD / "generation.json", result)
        audit.event(kind="pi_end", **result)
    # pi 会话有时含模型服务错误原文；保留结构，只替换实际凭证。
    for path in session_dir.rglob("*.jsonl"):
        if secret and path.is_file() and not path.is_symlink():
            path.write_text(redact(path.read_text()))
    # Agent 可写目录是 tmpfs，结束后复制回 trial 记录供审计与成本抽取。
    copy_regular(session_dir, RECORD / "logs/sessions")
    copy_regular(state_dir, RECORD / "pi-state")
    copy_regular(Path("/workspace/tests"), RECORD / "workspace/tests")
    for path in [RECORD / "logs/sessions", *(RECORD / "logs/sessions").rglob("*")]:
        path.chmod(0o755 if path.is_dir() else 0o644)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception:
        # 未启动完成的容器由宿主机记为 agent_error，并保留 stderr 与全新重跑记录。
        traceback.print_exc()
        raise SystemExit(1)
