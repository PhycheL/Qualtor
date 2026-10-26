"""宿主机持有编译预算和冻结快照，通过本地 socket 向 pi 提供编译反馈。"""
import json
import os
from pathlib import Path
import shutil
import socketserver
import threading
import time

from common.audit import Audit
from generator.build.artifacts import freeze
from generator.build.docker import DockerCompiler
from generator.support import write_json

FEEDBACK_LIMIT = 8000


class BuildService:
    def __init__(self, task, record, cancel=None):
        self.task, self.record = task, Path(record)
        self.workspace = self.record / "workspace"
        self.calls, self.first_at = 0, None
        self.busy, self.last_activity = False, time.monotonic()
        self.lock = threading.Lock()
        self.audit = Audit(self.record / "logs/orchestrator")
        self.cancel = cancel
        self.compiler = DockerCompiler(self.record, cancel)

    def request(self, data):
        with self.lock:
            if self.cancel is not None and self.cancel.is_set():
                return {"text": "生成已取消。", "details": {"cancelled": True}}
            if data.get("op") == "denied":
                self.audit.event(kind="access_denied", **{k: v for k, v in data.items() if k != "op"})
                return {"ok": True}
            if data.get("op") == "model_request":
                self.audit.event(kind="model_request", **{k: data.get(k) for k in ("model", "reasoning_effort", "thinking_type")})
                return {"ok": True}
            if data.get("op") != "build":
                return {"text": "未知操作", "details": {"error": True}}
            limit = self.task["budget"]["repair_rounds"]
            if self.calls >= limit + 1:
                self.audit.event(kind="budget_denied", calls=self.calls, request=data)
                return {"text": "修复预算已用完。请结束任务；剩余修复轮次：0。",
                        "details": {"budget_exhausted": True, "remaining_repair_rounds": 0}}
            self.busy = True
            try:
                return self.build(data, limit)
            finally:
                self.busy, self.last_activity = False, time.monotonic()

    def build(self, data, limit):
        self.calls += 1
        attempt = self.record / "attempts" / f"attempt-{self.calls}"
        attempt.mkdir(parents=True)
        started = time.time()
        self.audit.event(kind="build_start", call=self.calls, request=data, timestamp=started)
        freeze(self.workspace / "tests", attempt / "product")
        if self.calls == 1:
            self.first_at = started
            shutil.copytree(attempt / "product", self.record / "first")
        write_json(self.record / "build-state.json", {"calls": self.calls, "first_at": self.first_at,
                                                     "repair_rounds": max(0, self.calls - 1)})
        result = self.compiler.build(attempt, self.task)
        remaining = limit - max(0, self.calls - 1)
        result.update(remaining_repair_rounds=remaining, call=self.calls)
        write_json(attempt / "result.json", result)
        self.audit.event(kind="build_end", call=self.calls, status=result["status"], remaining=remaining)
        # 反馈投影只含本轮编译诊断；工具只能读取，所有写入仍限于 tests/。
        feedback_dir = self.workspace / "feedback" / f"attempt-{self.calls}"
        shutil.copytree(attempt / "output", feedback_dir)
        for path in feedback_dir.rglob("*"):
            if path.is_file():
                path.chmod(0o444)
        feedback = result["feedback"] if "tests" in result else result["feedback"][:FEEDBACK_LIMIT]
        relative = str(feedback_dir.relative_to(self.workspace))
        return {"text": feedback + f"\n完整编译、执行日志和报告：{relative}/。\n剩余修复轮次：{remaining}（首次编译不计修复）。",
                "details": {k: v for k, v in result.items() if k != "feedback"} | {"feedback_path": relative}}


def serve(service, socket_path):
    class Handler(socketserver.StreamRequestHandler):
        def handle(self):
            try:
                result = service.request(json.loads(self.rfile.readline(65536)))
            except Exception as error:
                service.audit.event(kind="build_error", error=str(error))
                result = {"text": f"编译服务故障：{error}", "details": {"infra_error": True}}
            try:
                self.wfile.write((json.dumps(result, ensure_ascii=False) + "\n").encode())
            except (BrokenPipeError, ConnectionResetError):
                pass  # 取消时 pi 可能先退出；编译结果与清理记录已经落盘。
    server = socketserver.ThreadingUnixStreamServer(str(socket_path), Handler)
    os.chmod(socket_path, 0o600)
    threading.Thread(target=server.serve_forever, daemon=True).start()
    return server
