#!/usr/bin/env python3
"""容器内验收固定版本工具链；结果只证明工具可用，不代表模型测试评分。"""
import argparse
from collections import Counter
import json
import os
from pathlib import Path
import shlex
import traceback

from audit import Audit, now
from coverage import collect


def write_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n")


def check(mode, output, summary):
    audit = Audit(output / "logs")

    def call(stage, command, cwd=output):
        result = audit.run(stage, command, cwd=cwd, timeout=180)
        if result["returncode"] or result["timed_out"]:
            raise RuntimeError(f"{stage} failed; see {result['stderr_log']}")
        return result["stdout"]

    if os.environ.get("QUALTOR_TOOLCHAIN") != mode:
        raise RuntimeError("镜像类型与选择的工具链不一致")
    versions = {
        "gcc": call("gcc-version", ["g++-14", "-dumpfullversion"]).strip(),
        "gcov": call("gcov-version", ["gcov-14", "--version"]),
        "cmake": call("cmake-version", ["cmake", "--version"]),
        "packages": call("installed-packages", ["dpkg-query", "-W"]),
    }
    if versions["gcc"] != "14.2.0" or "14.2.0" not in versions["gcov"]:
        raise RuntimeError("GCC/gcov 版本不匹配")
    if mode == "clang":
        versions["clang"] = call("clang-version", ["clang++-19", "--version"])
        versions["llvm"] = call("llvm-version", ["llvm-config-19", "--version"]).strip()
        versions["mull"] = call("mull-version", ["mull-runner-19", "--version"])
        if ("clang version 19.1.7" not in versions["clang"] or versions["llvm"] != "19.1.7"
                or "mull-runner 0.34.2" not in versions["mull"] or "LLVM: 19.1.7" not in versions["mull"]):
            raise RuntimeError("Clang/LLVM/Mull 版本不匹配")
    write_json(output / "versions.json", versions)

    build = output / "build"
    compiler = "g++-14" if mode == "gcc" else "clang++-19"
    call("cmake-configure", ["cmake", "-S", "/smoke", "-B", str(build), "-G", "Ninja",
         f"-DCMAKE_CXX_COMPILER={compiler}", f"-DQUALTOR_MODE={mode}", "-DUPSTREAM_CPP=/repo/cpp"])
    call("cmake-build", ["cmake", "--build", str(build), "--parallel", "2"])
    commands = json.loads((build / "compile_commands.json").read_text())
    if len(commands) != 2 or any("-std=c++11" not in shlex.split(c["command"]) for c in commands):
        raise RuntimeError("业务源码和测试必须均以 -std=c++11 编译")
    summary["cxx_standard"] = 11
    summary["googletest"] = "1.12.1"  # CMake find_package 已强制 EXACT。

    binary = build / "rose_tests"
    listed = call("gtest-list", [str(binary), "--gtest_list_tests"])
    (output / "gtest-list.txt").write_text(listed)
    ctest = json.loads(call("ctest-discover", ["ctest", "--test-dir", str(build), "--show-only=json-v1"]))
    discovered = [test["name"] for test in ctest["tests"]]
    if len(discovered) != 9 or len(set(discovered)) != 9:
        raise RuntimeError(f"应发现 9 个独立测试，实际为 {discovered}")
    call("ctest-run", ["ctest", "--test-dir", str(build), "--no-tests=error", "--output-on-failure"])
    # 清除 CTest 运行数据，只统计下方一次 GoogleTest JSON 验收运行的覆盖率。
    for path in build.rglob("*.gcda"):
        path.unlink()
    results = output / "gtest-results.json"
    call("gtest-run", [str(binary), f"--gtest_output=json:{results}"])
    data = json.loads(results.read_text())
    tests = [test for suite in data["testsuites"] for test in suite["testsuite"]]
    executed = {f"{suite['name']}.{test['name']}" for suite in data["testsuites"] for test in suite["testsuite"]}
    if (data["tests"] != 9 or len(tests) != 9 or set(discovered) != executed
            or data["failures"] or data["disabled"] or data["errors"]
            or any(t.get("status") != "RUN" or t.get("result") != "COMPLETED" or t.get("failures") for t in tests)):
        raise RuntimeError("测试发现数、执行数或执行结果不符合预期")
    summary["tests"] = {"discovered": len(discovered), "executed": len(tests), "passed": len(tests)}

    if mode == "gcc":
        coverage = collect(build, output / "coverage", audit)
        if (coverage["json"]["source"] != "/repo/cpp/src/GildedRose.cc"
                or coverage["json"]["gcc_version"] != "14.2.0"
                or coverage["json"]["line"]["covered"] == 0):
            raise RuntimeError("覆盖率缺失或统计范围不正确")
        summary["coverage"] = coverage
    else:
        multiarch = call("library-directory", ["g++-14", "-print-multiarch"]).strip()
        # 幸存变异是测试结果；--allow-surviving 避免将其误报为工具故障。
        call("mull-run", ["mull-runner-19", "--allow-surviving", "--include-not-covered", "--workers=2",
             f"--ld-search-path=/usr/lib/{multiarch}",
             "--reporters=Elements",
             f"--report-dir={output}", "--report-name=mutations", str(binary)])
        reports = list(output.glob("mutations*.json"))
        if len(reports) != 1:
            raise RuntimeError(f"Mull 报告数量不正确：{reports}")
        report = json.loads(reports[0].read_text())
        mutants = []
        for path, record in report["files"].items():
            if path != "/repo/cpp/src/GildedRose.cc":
                raise RuntimeError(f"Mull 错误地变异了其他文件：{path}")
            mutants.extend(record["mutants"])
        counts = Counter(m["status"] for m in mutants)
        if not mutants or counts["Killed"] == 0:
            raise RuntimeError("Mull 必须实际生成变异，且至少检出一个行为改变")
        if set(counts) - {"Killed", "Survived", "NoCoverage"}:
            raise RuntimeError(f"Mull 出现超时或异常状态：{dict(counts)}")
        summary["mutations"] = {"total": len(mutants), "statuses": dict(counts), "report": str(reports[0])}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolchain", choices=["gcc", "clang"], required=True)
    parser.add_argument("--output", type=Path, default=Path("/work"))
    args = parser.parse_args()
    summary = {"status": "running", "started_at": now(), "toolchain": args.toolchain}
    try:
        check(args.toolchain, args.output, summary)
        summary["status"] = "passed"
    except Exception as error:
        summary.update(status="failed", error=str(error))
        traceback.print_exc()
    summary["finished_at"] = now()
    write_json(args.output / "summary.json", summary)
    print(json.dumps(summary, ensure_ascii=False, indent=2))
    return 0 if summary["status"] == "passed" else 1


if __name__ == "__main__":
    raise SystemExit(main())
