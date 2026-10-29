#!/usr/bin/env python3
"""容器内执行器：按阶段执行构建、测试运行和 Mull，写出原始记录 step.json。

阶段：
- build：用评测模块的 CMake 模板构建测试可执行文件（步骤 1，以及步骤 6、7 的构建）；
- run：发现、整体运行、单独重跑、稳定性和覆盖率（步骤 2–5）；variant 模式只运行给定的测试（步骤 7）；
- mull：用稳定有效测试运行 mull-runner（步骤 6）。

判定规则在 judge.py；本文件只负责执行与记录。宿主机会依据原始记录重新判定一遍。
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import sys
import traceback

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "common"))

from audit import Audit, now  # noqa: E402
import gtest_results  # noqa: E402
import judge  # noqa: E402
from build_contract import cmake_build_args, compile_command_problems  # noqa: E402

LIST_TIMEOUT = 60


def write_json(path, value):
    Path(path).write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n")


def set_timeout(job, count):
    """一次运行多个测试时的总超时：单测超时 × 测试数，限制在 20–600 秒。"""
    return min(max(job["test_timeout"] * max(count, 1), 20), 600)


# ---- 构建 ----

def phase_build(job, audit):
    build_dir = Path(job["build_dir"])
    command = [job.get("cmake", "cmake"), "-S", job["template_dir"], "-B", str(build_dir), "-G", "Ninja",
               f"-DQUALTOR_MODE={job['mode']}",
               "-DQUALTOR_TARGET_SOURCES=" + ";".join(job["target_sources"]),
               "-DQUALTOR_INCLUDE_DIRS=" + ";".join(job["include_dirs"]),
               "-DQUALTOR_TEST_SOURCES=" + ";".join(job["test_sources"])]
    command += cmake_build_args(job.get("build", {}), job.get("support_sources", []), job.get("target_headers"))
    for key, option in (("cc", "CMAKE_C_COMPILER"), ("cxx", "CMAKE_CXX_COMPILER"), ("make_program", "CMAKE_MAKE_PROGRAM"),
                        ("gtest_prefix", "CMAKE_PREFIX_PATH")):
        if job.get(key):
            command.append(f"-D{option}={job[key]}")
    configured = audit.run("cmake-configure", command, cwd=job["work_dir"], timeout=300)
    if configured["returncode"] or configured["timed_out"]:
        # 配置阶段不编译测试源文件，失败说明模板或工具链有问题。
        return {"status": "infra_error", "reason": "cmake_configure_failed", "log": configured["stderr_log"]}
    commands = json.loads((build_dir / "compile_commands.json").read_text())
    problems = compile_command_problems(commands, job["target_sources"], job.get("support_sources", []),
                                        job["test_sources"], job.get("build", {}), job["mode"], job.get("target_headers"))
    if problems:
        return {"status": "infra_error", "reason": "compile_commands_mismatch",
                "problems": problems}
    built = audit.run("cmake-build", [job.get("cmake", "cmake"), "--build", str(build_dir), "--parallel", "2"],
                      cwd=job["work_dir"], timeout=job.get("timeout", 900))
    binary = build_dir / "scored_tests"
    if built["returncode"] or built["timed_out"] or not binary.is_file():
        text = built["stdout"] + "\n" + built["stderr"]
        diagnostics = [line.strip()[:400] for line in text.splitlines()
                       if "error" in line.lower() or "undefined reference" in line or "multiple definition" in line
                       or "duplicate symbol" in line][:30]
        return {"status": "build_failed", "reason": "build_timeout" if built["timed_out"] else "compile_or_link_error",
                "diagnostics": diagnostics, "log": built["stdout_log"]}
    return {"status": "built", "binary": str(binary), "compile_units": len(commands)}


# ---- 测试运行 ----

class Runner:
    """在同一个工作目录里运行测试可执行文件，记录每次运行的结果。"""

    def __init__(self, job, audit):
        self.job, self.audit = job, audit
        self.binary = job["binary"]
        self.out = Path(job["out_dir"])
        self.work = Path(job["work_dir"])
        self.work.mkdir(parents=True, exist_ok=True)
        self.seq = 0
        coverage = job.get("coverage")
        if coverage:
            # 构建目录只读挂载：所有运行的 .gcda 先重定向到废弃目录，步骤 5 再用干净目录单独采集。
            os.environ["GCOV_PREFIX"] = str(self.out / "gcov-scratch")
            os.environ["GCOV_PREFIX_STRIP"] = "0"

    def _json_path(self, label):
        self.seq += 1
        directory = self.out / "results"
        directory.mkdir(parents=True, exist_ok=True)
        return directory / f"{self.seq:03d}-{label}.json"

    def invoke(self, label, args, timeout):
        path = self._json_path(label)
        result = self.audit.run(label, [self.binary, *args, f"--gtest_output=json:{path}"],
                                cwd=self.work, timeout=timeout)
        document = gtest_results.load_json(path)
        return {"label": label, "returncode": result["returncode"], "timed_out": result["timed_out"],
                "json": document is not None, "document": document, "stdout": result["stdout"],
                "stdout_log": result["stdout_log"]}

    def discover(self):
        path = self._json_path("discover")
        result = self.audit.run("discover", [self.binary, "--gtest_list_tests", f"--gtest_output=json:{path}"],
                                cwd=self.work, timeout=LIST_TIMEOUT)
        tests = gtest_results.parse_list(gtest_results.load_json(path))
        return {"ok": tests is not None and not result["timed_out"], "tests": tests or [],
                "returncode": result["returncode"], "timed_out": result["timed_out"]}

    def run_set(self, label, names, extra=()):
        """运行一组测试，返回每个测试的结果；拿不到 JSON 时从标准输出恢复，正在运行的测试记为崩溃或超时。"""
        run = self.invoke(label, ["--gtest_filter=" + gtest_results.gtest_filter(names), *extra],
                          set_timeout(self.job, len(names)))
        usable = run["json"] and not run["timed_out"] and run["returncode"] in (0, 1)
        outcomes = {}
        if usable:
            parsed = gtest_results.parse_run(run["document"]) or {}
            for name in names:
                outcomes[name] = parsed.get(name, {}).get("outcome", "missing")
        else:
            parsed = gtest_results.parse_stdout(run["stdout"])
            for name in names:
                if name in parsed["finished"]:
                    outcomes[name] = parsed["finished"][name]
                elif name == parsed["in_progress"]:
                    outcomes[name] = "timed_out" if run["timed_out"] else "crashed"
                else:
                    outcomes[name] = "not_run"
        return {"label": label, "usable": usable, "returncode": run["returncode"],
                "timed_out": run["timed_out"], "outcomes": outcomes}

    def isolate(self, name, index):
        run = self.invoke(f"isolate-{index:03d}", ["--gtest_filter=" + name], self.job["test_timeout"])
        if run["timed_out"]:
            return {"outcome": "timed_out", "returncode": run["returncode"]}
        if run["json"] and run["returncode"] in (0, 1):
            parsed = (gtest_results.parse_run(run["document"]) or {}).get(name)
            if parsed:
                return {"outcome": parsed["outcome"], "failures": parsed["failures"], "returncode": run["returncode"]}
        return {"outcome": "crashed", "returncode": run["returncode"]}


def summarize_full(run):
    parsed = gtest_results.parse_run(run["document"]) if run["json"] else None
    return {"returncode": run["returncode"], "timed_out": run["timed_out"], "json": run["json"],
            "outcomes": parsed, "stdout_log": run["stdout_log"]}


def phase_run(job, audit):
    runner = Runner(job, audit)
    if job.get("mode") == "variant":
        return run_variant(job, runner)
    record = {"discovery": runner.discover()}
    if not record["discovery"]["ok"] or not record["discovery"]["tests"]:
        return {"status": "ok", "record": record}
    names = [t["name"] for t in record["discovery"]["tests"]]
    full = runner.invoke("full", [], set_timeout(job, len(names)))
    record["full_run"] = summarize_full(full)
    record["isolation"] = {}
    if not judge.full_run_usable(record["full_run"]):
        for index, name in enumerate(names):
            record["isolation"][name] = runner.isolate(name, index)
    step3, problem = judge.step3_statuses(record["discovery"]["tests"], record["full_run"], record["isolation"])
    record["step3"], record["step3_problem"] = step3, problem
    passed = [n for n in names if step3.get(n) == judge.PASSED]
    record["stability"], record["stability_runs"] = (stability(job, runner, passed, record["isolation"])
                                                    if passed and not problem else ({}, []))
    record["final_statuses"] = judge.final_test_statuses(step3, record["stability"]) if not problem else step3
    valid = judge.valid_tests(record)
    coverage = job.get("coverage")
    if coverage and valid and not problem:
        record["coverage"] = collect_coverage(job, runner, valid, coverage, audit)
    return {"status": "ok", "record": record}


def stability(job, runner, passed, isolation):
    """步骤 4：重复 N 次、按种子乱序、逐个单独运行；只统计步骤 3 通过的测试。"""
    per_test = {n: {"repeat_failures": 0, "repeat_observed": 0, "shuffle_failures": 0, "shuffle_observed": 0}
                for n in passed}
    runs = []
    for index in range(job["repeats"]):
        runs.append(("repeat", runner.run_set(f"repeat-{index + 1:02d}", passed)))
    for seed in job["shuffle_seeds"]:
        runs.append(("shuffle", runner.run_set(f"shuffle-{seed}", passed,
                                               ["--gtest_shuffle", f"--gtest_random_seed={seed}"])))
    for kind, run in runs:
        for name, outcome in run["outcomes"].items():
            if outcome in ("not_run", "missing"):
                continue  # 前面的测试崩溃导致没有运行到，不计入
            per_test[name][f"{kind}_observed"] += 1
            if outcome != "passed":
                per_test[name][f"{kind}_failures"] += 1
    for index, name in enumerate(passed):
        isolated = isolation.get(name) or runner.isolate(name, 500 + index)
        per_test[name]["isolation_outcome"] = isolated["outcome"]
    summary = [{"kind": kind, "label": run["label"], "usable": run["usable"],
                "returncode": run["returncode"], "timed_out": run["timed_out"]} for kind, run in runs]
    return per_test, summary


def collect_coverage(job, runner, valid, coverage, audit):
    """步骤 5：用干净的 GCOV_PREFIX 目录只运行一次稳定有效测试，再按被测源文件采集。"""
    import coverage as gcov_tools
    prefix = Path(coverage["prefix_dir"])
    if prefix.exists():
        shutil.rmtree(prefix)
    prefix.mkdir(parents=True)
    os.environ["GCOV_PREFIX"] = str(prefix)
    run = runner.run_set("coverage-run", valid)
    os.environ["GCOV_PREFIX"] = str(runner.out / "gcov-scratch")
    if not run["usable"] or any(o != "passed" for o in run["outcomes"].values()):
        return {"status": "error", "reason": "coverage_run_not_clean", "outcomes": run["outcomes"]}
    try:
        data = gcov_tools.collect_targets(prefix, coverage["sources"], runner.out / "coverage", audit,
                                          gcov=coverage.get("gcov", "gcov"), headers=coverage.get("headers", False))
    except Exception as error:  # 覆盖率只是诊断指标，失败时单独标出，不影响其他步骤
        return {"status": "error", "reason": f"gcov_failed: {error}"}
    if (data["missing_sources"] and not coverage.get("headers")) or not data["parsers_agree"]:
        return {"status": "error", "reason": "coverage_incomplete", "data": data}
    return {"status": "ok", "data": data}


def run_variant(job, runner):
    """步骤 7 的运行部分：只运行给定的稳定有效测试，记录每个测试在替换版本上的结果。"""
    names = job["tests"]
    run = runner.run_set("variant", names)
    outcomes = {n: {"outcome": o} for n, o in run["outcomes"].items()}
    if not run["usable"]:
        # 进程整体异常时逐个单独重跑，准确定位失败的测试。
        for index, name in enumerate(names):
            outcomes[name] = runner.isolate(name, index)
    return {"status": "ok", "record": {"variant_outcomes": outcomes, "usable": run["usable"],
                                       "returncode": run["returncode"], "timed_out": run["timed_out"]}}


# ---- Mull ----

def phase_mull(job, audit):
    report_dir = Path(job["out_dir"]) / "mull"
    report_dir.mkdir(parents=True, exist_ok=True)
    multiarch = audit.run("library-directory", ["g++-14", "-print-multiarch"], cwd=job["work_dir"], timeout=60)
    if multiarch["returncode"]:
        return {"status": "infra_error", "reason": "multiarch_lookup_failed"}
    command = [job.get("mull_runner", "mull-runner-19"), "--allow-surviving", "--include-not-covered",
               f"--workers={job.get('workers', 2)}", f"--ld-search-path=/usr/lib/{multiarch['stdout'].strip()}",
               f"--minimum-timeout={job['minimum_timeout_ms']}", "--reporters=Elements",
               f"--report-dir={report_dir}", "--report-name=mutations", job["binary"],
               # mull-runner 用法为 [OPTIONS] <EXECUTABLE> [RUNNER_ARGS]...；参数原样传给测试程序。
               "--", "--gtest_filter=" + gtest_results.gtest_filter(job["tests"])]
    result = audit.run("mull-runner", command, cwd=job["work_dir"], timeout=job.get("timeout", 3600))
    if result["returncode"] or result["timed_out"]:
        return {"status": "infra_error", "reason": "mull_runner_failed", "returncode": result["returncode"],
                "timed_out": result["timed_out"], "log": result["stderr_log"]}
    reports = sorted(report_dir.glob("mutations*.json"))
    if job.get("allow_zero_mutants") and zero_mutants(result, reports):
        return {"status": "ok", "mutants": [], "not_applicable": "zero_mutants",
                "zero_mutants_evidence": {"returncode": result["returncode"], "stdout": result["stdout"],
                                          "stdout_log": result["stdout_log"], "reports": []}}
    if len(reports) != 1:
        return {"status": "infra_error", "reason": f"unexpected_mull_reports: {len(reports)}"}
    report = json.loads(reports[0].read_text())
    mutants, problem = parse_mull_report(report, job["sources"])
    if problem:
        return {"status": "infra_error", "reason": problem}
    return {"status": "ok", "mutants": mutants, "report": str(reports[0]), "config": report.get("config")}


def zero_mutants(result, reports):
    return (result["returncode"] == 0 and not result.get("timed_out")
            and "No mutants found" in result.get("stdout", "") and not reports)


def parse_mull_report(report, sources):
    """Mull Elements 报告 -> 变异清单。id 形如 cxx_sub_to_add:/repo/x.cc:51:47:51:48，包含算子与位置。"""
    mutants = []
    for path, record in (report.get("files") or {}).items():
        if path not in sources:
            return None, f"mutated_unexpected_file: {path}"
        for mutant in record.get("mutants", []):
            mutants.append({"id": mutant["id"], "mutator": mutant.get("mutatorName"), "file": path,
                            "status": mutant.get("status"), "location": mutant.get("location")})
    ids = [m["id"] for m in mutants]
    if len(ids) != len(set(ids)):
        return None, "duplicate_mutant_ids"
    return sorted(mutants, key=lambda m: m["id"]), None


PHASES = {"build": phase_build, "run": phase_run, "mull": phase_mull}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--job", type=Path, required=True)
    args = parser.parse_args()
    job = json.loads(args.job.read_text())
    out = Path(job["out_dir"])
    audit = Audit(out / "logs")
    started = now()
    try:
        Path(job["work_dir"]).mkdir(parents=True, exist_ok=True)
        step = PHASES[job["phase"]](job, audit)
    except Exception:
        step = {"status": "infra_error", "reason": "executor_exception", "traceback": traceback.format_exc()}
    step.update(phase=job["phase"], started_at=started, finished_at=now())
    write_json(out / "step.json", step)
    print(json.dumps({k: step.get(k) for k in ("phase", "status", "reason")}, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
