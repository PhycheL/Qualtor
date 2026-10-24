"""解析 GoogleTest 1.12.1 的列表 JSON、运行 JSON 和标准输出。纯函数，容器内外通用。

字段含义已在 GoogleTest 1.12.1 上实测：
- 列表 JSON（--gtest_list_tests --gtest_output=json）包含禁用的测试；
- 运行 JSON 中通过为 status=RUN/result=COMPLETED，失败另带 failures，
  跳过为 RUN/SKIPPED，禁用（测试名或套件名带 DISABLED_ 前缀）为 NOTRUN/SUPPRESSED。
"""
import json
from pathlib import Path
import re

# 每个测试的结束行带 "(N ms)"；运行结束后的汇总段会重复打印同名行但不带耗时，不能计入。
_MARKER = re.compile(r"^\[\s*(RUN|OK|FAILED|SKIPPED)\s*\] (\S+)(?: \(\d+ ms\))?\s*$")
_TIMED = re.compile(r" \(\d+ ms\)\s*$")


def load_json(path):
    """读取 JSON；文件不存在或损坏时返回 None，由调用方判定为“没有结果”。"""
    path = Path(path)
    if not path.is_file():
        return None
    try:
        return json.loads(path.read_text(errors="replace"))
    except ValueError:
        return None


def parse_list(document):
    """列表 JSON -> [{name, suite, test, file, line}]，保持 GoogleTest 的登记顺序。"""
    if not isinstance(document, dict) or not isinstance(document.get("testsuites"), list):
        return None
    tests = []
    for suite in document["testsuites"]:
        for case in suite.get("testsuite", []):
            tests.append({"name": f"{suite['name']}.{case['name']}", "suite": suite["name"],
                          "test": case["name"], "file": case.get("file"), "line": case.get("line")})
    return tests


def parse_run(document):
    """运行 JSON -> {完整测试名: 结果}；结果取值 passed、failed、skipped、disabled。"""
    if not isinstance(document, dict) or not isinstance(document.get("testsuites"), list):
        return None
    outcomes = {}
    for suite in document["testsuites"]:
        for case in suite.get("testsuite", []):
            name = f"{suite['name']}.{case['name']}"
            failures = [f.get("failure", "")[:500] for f in case.get("failures", []) or []]
            if case.get("status") != "RUN":
                outcome = "disabled"
            elif case.get("result") == "SKIPPED":
                outcome = "skipped"
            elif failures:
                outcome = "failed"
            elif case.get("result") == "COMPLETED":
                outcome = "passed"
            else:
                # 其他取值（例如 SUPPRESSED 但 status=RUN）不应出现，按失败处理并保留原值供排查。
                outcome = "failed"
                failures = failures or [f"unexpected result {case.get('result')!r}"]
            outcomes[name] = {"outcome": outcome, "failures": failures[:3]}
    return outcomes


def parse_stdout(text):
    """在拿不到 JSON 时，从标准输出恢复已结束测试的结果，并找出崩溃或超时时正在运行的测试。"""
    finished, running = {}, None
    for line in (text or "").splitlines():
        match = _MARKER.match(line)
        if not match:
            continue
        kind, name = match.group(1), match.group(2)
        if kind == "RUN":
            running = name
            continue
        if not _TIMED.search(line):
            continue  # 汇总段的重复行
        finished[name] = {"OK": "passed", "FAILED": "failed", "SKIPPED": "skipped"}[kind]
        if running == name:
            running = None
    return {"finished": finished, "in_progress": running}


def gtest_filter(names):
    """把测试名清单写成 --gtest_filter 的正向过滤串。"""
    return ":".join(names)
