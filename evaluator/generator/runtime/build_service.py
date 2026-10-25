"""容器内可信编译服务。预算与快照由 root 持有，编译/测试使用独立的无特权用户。"""
import fnmatch
import hashlib
import json
import os
from pathlib import Path
import shutil
import signal
import socketserver
import threading
import time

from audit import Audit, now
import gtest_results

RECORD = Path("/private/record")
WORKSPACE = Path("/workspace")
TEST_UID = 65534
FEEDBACK_LIMIT = 8000


def kill_uid(uid, proc=Path("/proc")):
    """结束指定 UID 的全部进程。生成的测试可能留下脱离进程组的后台进程，每次运行后统一清理。"""
    killed = []
    for entry in proc.iterdir():
        if not entry.name.isdigit():
            continue
        try:
            if entry.stat().st_uid != uid:
                continue
            os.kill(int(entry.name), signal.SIGKILL)
            killed.append(int(entry.name))
        except (FileNotFoundError, ProcessLookupError, PermissionError):
            continue
    return killed


def feedback_text(outcomes, details, limit=FEEDBACK_LIMIT):
    """先给出每个测试的通过/失败汇总，再附失败详情；截断只发生在详情部分。"""
    failed = [name for name, outcome in outcomes.items() if outcome["outcome"] != "passed"]
    head = f"测试结果：共 {len(outcomes)} 个，通过 {len(outcomes) - len(failed)} 个，未通过 {len(failed)} 个。\n"
    if failed:
        head += "未通过的测试（其余全部通过）：\n" + "".join(f"- {name}: {outcomes[name]['outcome']}\n" for name in failed)
    else:
        head += "全部通过。\n"
    body = "".join(f"\n--- {name}: {outcomes[name]['outcome']}\n{details[name]}" for name in failed)
    text = head + ("\n失败详情：" + body if body else "")
    if len(text) > limit:
        marker = "\n……（输出过长，已截断）"
        text = text[:max(0, limit - len(marker))] + marker
    return text


def write_json(path, value):
    Path(path).write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n")


def freeze(source, destination):
    """复制普通测试文件后立即冻结；绝不跟随链接、FIFO 或设备文件。"""
    source, destination = Path(source), Path(destination)
    (destination / "tests").mkdir(parents=True, exist_ok=False)
    files = {}
    for path in sorted(source.rglob("*")):
        if path.is_symlink() or (not path.is_dir() and not path.is_file()):
            raise ValueError(f"非法产物文件：{path.name}")
        if not path.is_file():
            continue
        rel = Path("tests") / path.relative_to(source)
        target = destination / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        content = path.read_bytes()
        target.write_bytes(content)
        target.chmod(0o444)
        files[str(rel)] = hashlib.sha256(content).hexdigest()
    write_json(destination / "manifest.json", {"files": files, "frozen_at": now()})
    return files


class BuildService:
    def __init__(self, task):
        self.task = task
        self.calls = 0
        self.first_at = None
        # 看门狗只在没有编译任务时计时；编译与测试由各自的阶段超时约束。
        self.busy = False
        self.last_activity = time.monotonic()
        self.lock = threading.Lock()
        self.audit = Audit(RECORD / "logs/orchestrator")
        self.env = {"PATH": os.environ["PATH"], "HOME": "/tmp/test-home", "CMAKE_PREFIX_PATH": "/opt/googletest",
                    "CC": "gcc-14", "CXX": "g++-14"}
        Path("/tmp/test-home").mkdir()
        os.chown("/tmp/test-home", TEST_UID, TEST_UID)

    def request(self, data):
        with self.lock:
            if data.get("op") == "denied":
                self.audit.event(kind="access_denied", **{k: v for k, v in data.items() if k != "op"})
                return {"ok": True}
            if data.get("op") != "build":
                return {"text": "未知操作", "details": {"error": True}}
            limit = self.task["budget"]["repair_rounds"]
            if self.calls >= limit + 1:
                self.audit.event(kind="budget_denied", calls=self.calls, request=data)
                return {"text": "修复预算已用完。请结束任务；不能继续编译验证。剩余修复轮次：0。",
                        "details": {"budget_exhausted": True, "remaining_repair_rounds": 0}}
            self.busy = True
            try:
                return self._build_call(data, limit)
            finally:
                self.busy = False
                self.last_activity = time.monotonic()

    def _build_call(self, data, limit):
        self.calls += 1
        attempt = RECORD / "attempts" / f"attempt-{self.calls}"
        attempt.mkdir(parents=True)
        started = time.time()
        self.audit.event(kind="build_start", call=self.calls, request=data, timestamp=started)
        files = freeze(WORKSPACE / "tests", attempt / "product")
        if self.calls == 1:
            self.first_at = started
            shutil.copytree(attempt / "product", RECORD / "first")
        write_json(RECORD / "build-state.json", {"calls": self.calls, "first_at": self.first_at,
                                                 "repair_rounds": max(0, self.calls - 1)})
        audit = Audit(attempt / "logs")
        result = self.build(attempt, files, audit)
        remaining = limit - max(0, self.calls - 1)
        result["remaining_repair_rounds"] = remaining
        result["call"] = self.calls
        write_json(attempt / "result.json", result)
        self.audit.event(kind="build_end", call=self.calls, status=result["status"], remaining=remaining)
        # 完整原始输出写审计日志；测试结果反馈已把通过/失败汇总放在最前，这里统一截到 8000 字符。
        feedback = result.pop("feedback")[:FEEDBACK_LIMIT]
        return {"text": feedback + f"\n剩余修复轮次：{remaining}（首次编译不计修复）。", "details": result}

    def build(self, attempt, files, audit):
        sources = [str(attempt / "product" / rel) for rel in files if rel.endswith((".cc", ".cpp", ".cxx"))]
        if any(not any(fnmatch.fnmatchcase(rel, pattern) for pattern in self.task["allowed_test_files"]) for rel in files):
            return {"status": "artifact_rejected", "feedback": "存在不允许提交的文件。"}
        if not sources:
            return {"status": "zero_tests", "feedback": "没有测试源文件；请在 tests/ 内编写 GoogleTest 测试。"}
        work = Path("/tmp") / f"build-{self.calls}"
        work.mkdir()
        os.chown(work, TEST_UID, TEST_UID)
        # 编译只读快照在 Linux 原生 tmpfs 上；裁判记录目录保持 root 私有。
        snapshot = Path("/snapshots") / f"attempt-{self.calls}"
        shutil.copytree(attempt / "product", snapshot)
        sources = [str(snapshot / rel) for rel in files if rel.endswith((".cc", ".cpp", ".cxx"))]
        command = ["cmake", "-S", "/cmake", "-B", str(work / "build"), "-G", "Ninja", "-DQUALTOR_MODE=plain",
                   "-DQUALTOR_TARGET_SOURCES=" + ";".join("/workspace/project/" + s for s in self.task["target_sources"]),
                   "-DQUALTOR_INCLUDE_DIRS=" + ";".join(["/workspace/project/" + s for s in self.task["include_dirs"]]
                                                          + [str(snapshot / "tests")]),
                   "-DQUALTOR_TEST_SOURCES=" + ";".join(sources)]
        def run(label, args, timeout):
            env = dict(self.env, TMPDIR=str(work), HOME=str(work))
            try:
                return audit.run(label, args, cwd=work, timeout=timeout, env=env, user=TEST_UID, group=TEST_UID)
            finally:
                leftover = kill_uid(TEST_UID)
                if leftover:
                    audit.event(kind="leftover_processes_killed", stage=label, pids=leftover)
        configured = run("configure", command, 300)
        if configured["returncode"]:
            return {"status": "build_failed", "feedback": configured["stdout"] + configured["stderr"]}
        built = run("compile", ["cmake", "--build", str(work / "build"), "--parallel", "2"], 900)
        if built["returncode"]:
            return {"status": "build_failed", "feedback": built["stdout"] + built["stderr"]}
        binary = str(work / "build/scored_tests")
        listed = run("discover", [binary, "--gtest_list_tests", f"--gtest_output=json:{work}/list.json"],
                     self.task["test_timeout_seconds"])
        tests = gtest_results.parse_list(gtest_results.load_json(work / "list.json"))
        if listed["returncode"] or not tests:
            return {"status": "zero_tests" if tests == [] else "no_result", "feedback": "没有发现可执行测试。\n" + listed["stdout"] + listed["stderr"]}
        outcomes, details = {}, {}
        # 每个测试仅执行一遍，按发现顺序逐个启动；单测超时精确采用 task 参数。
        for index, test in enumerate(tests):
            report = work / f"test-{index}.json"
            executed = run(f"test-{index}", [binary, "--gtest_filter=" + test["name"], f"--gtest_output=json:{report}"],
                           self.task["test_timeout_seconds"])
            parsed = gtest_results.parse_run(gtest_results.load_json(report)) or {}
            outcome = parsed.get(test["name"], {"outcome": "timed_out" if executed["timed_out"] else "crashed"})
            if executed["returncode"] not in (0, 1):
                outcome = {"outcome": "timed_out" if executed["timed_out"] else "crashed"}
            outcomes[test["name"]] = outcome
            details[test["name"]] = executed["stdout"] + executed["stderr"]
        for path in work.glob("*.json"):
            shutil.copy2(path, attempt / path.name)
        shutil.copy2(work / "build/compile_commands.json", attempt / "compile_commands.json")
        passed = bool(outcomes) and all(v["outcome"] == "passed" for v in outcomes.values())
        return {"status": "passed" if passed else "tests_failed", "tests": outcomes,
                "feedback": feedback_text(outcomes, details)}


def serve(service):
    class Handler(socketserver.StreamRequestHandler):
        def handle(self):
            try:
                result = service.request(json.loads(self.rfile.readline()))
            except Exception as error:
                service.audit.event(kind="build_error", error=str(error))
                result = {"text": f"编译服务故障：{error}", "details": {"infra_error": True}}
            self.wfile.write((json.dumps(result, ensure_ascii=False) + "\n").encode())
    server = socketserver.ThreadingUnixStreamServer("/control/build.sock", Handler)
    os.chmod("/control/build.sock", 0o660)
    os.chown("/control/build.sock", 0, int(os.environ["QUALTOR_AGENT_GID"]))
    threading.Thread(target=server.serve_forever, daemon=True).start()
    return server
