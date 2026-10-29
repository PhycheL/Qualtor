"""一次编译快照的容器入口。源码和测试只读；编译与测试使用独立 UID。"""
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

if __package__:
    from common.audit import Audit, now
    from . import gtest_results
    from .contract import cmake_build_args, compile_command_problems
else:
    from audit import Audit, now
    import gtest_results
    from contract import cmake_build_args, compile_command_problems

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
    body = "\n失败详情：" + body if body else ""
    if len(head) + len(body) > limit:
        marker = "\n……（输出过长，已截断）"
        body = body[:max(0, limit - len(head) - len(marker))] + marker
    return head + body


class ContainerBuild:
    def __init__(self, task):
        self.task = task
        self.env = {"PATH": os.environ["PATH"], "CMAKE_PREFIX_PATH": "/opt/googletest", "CC": "gcc-14", "CXX": "g++-14"}

    def build(self, attempt, files, audit):
        sources = [str(attempt / "product" / rel) for rel in files if rel.endswith((".cc", ".cpp", ".cxx"))]
        if any(not any(fnmatch.fnmatchcase(rel, pattern) for pattern in self.task["allowed_test_files"]) for rel in files):
            return {"status": "artifact_rejected", "feedback": "存在不允许提交的文件。"}
        if not sources:
            return {"status": "zero_tests", "feedback": "没有测试源文件；请在 tests/ 内编写 GoogleTest 测试。"}
        work = Path("/tmp/build")
        work.mkdir()
        os.chown(work, TEST_UID, TEST_UID)
        snapshot = Path("/product")
        sources = [str(snapshot / rel) for rel in files if rel.endswith((".cc", ".cpp", ".cxx"))]
        command = ["cmake", "-S", "/cmake", "-B", str(work / "build"), "-G", "Ninja",
                   "-DQUALTOR_TARGET_SOURCES=" + ";".join("/project/" + s for s in self.task["target_sources"]),
                   "-DQUALTOR_INCLUDE_DIRS=" + ";".join(["/project/" + s for s in self.task["include_dirs"]]
                                                          + [str(snapshot / "tests")]),
                   "-DQUALTOR_TEST_SOURCES=" + ";".join(sources)]
        build = self.task.get("build", {})
        targets = ["/project/" + s for s in self.task["target_sources"]]
        support = ["/project/" + s for s in build.get("support_sources", [])]
        headers = ["/project/" + s for s in self.task.get("target_headers", [])]
        command += cmake_build_args(build, support, headers)
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
        shutil.copy2(work / "build/compile_commands.json", attempt / "compile_commands.json")
        commands = json.loads((attempt / "compile_commands.json").read_text())
        problems = compile_command_problems(commands, targets, support, sources, build, target_headers=headers)
        if problems:
            raise RuntimeError("compile_commands_mismatch: " + "; ".join(problems))
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
        passed = bool(outcomes) and all(v["outcome"] == "passed" for v in outcomes.values())
        return {"status": "passed" if passed else "tests_failed", "tests": outcomes,
                "feedback": feedback_text(outcomes, details)}


if __name__ == "__main__":
    task = json.loads(Path("/input/task.json").read_text())
    files = json.loads(Path("/product/manifest.json").read_text())["files"]
    result = ContainerBuild(task).build(Path("/private/output"), files, Audit(Path("/private/output/logs")))
    Path("/private/output/result.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n")
