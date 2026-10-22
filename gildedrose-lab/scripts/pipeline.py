#!/usr/bin/env python3
"""容器内完整实验：生成 -> CMake -> CTest -> gcov -> 独立变异。"""
import argparse
import collections
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import sys
import traceback
from audit import Audit, now
from cases import generate, expected, make_case
from coverage import collect
from mutations import catalogue, manifest
from verify import evaluate
from score_challenge import score_challenge
from source_snapshot import verify_snapshot


def write_json(path, data):
    Path(path).write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n")


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def must(result):
    if result["returncode"] or result["timed_out"]:
        raise RuntimeError(f'{result["stage"]} failed: {result["returncode"]}; {result["stderr_log"]}')
    return result


def diagnostics(result):
    found = []
    for line in (result["stdout"] + "\n" + result["stderr"]).splitlines():
        try:
            entries = json.loads(line)
        except (ValueError, TypeError):
            entries = None
        if isinstance(entries, list):
            for entry in entries:
                if isinstance(entry, dict) and entry.get("kind") in ("error", "fatal error"):
                    found.append({"phase": "compile", **entry})
        if "undefined reference to" in line:
            location = re.search(r"(.+?):(\d+):", line)
            found.append({"phase": "link", "kind": "error", "message": line,
                          "file": location.group(1) if location else None,
                          "line": int(location.group(2)) if location else None})
    return found


def run(args):
    work = args.output.resolve()
    work.mkdir(parents=True, exist_ok=False)
    audit = Audit(work / "logs")
    audit.event(kind="pipeline_start", upstream=str(args.repo), argv=sys.argv)
    summary = {"started_at": now(), "status": "running"}
    write_json(work / "summary.json", summary)
    for name, cmd in [("python", ["python3", "--version"]), ("cmake", ["cmake", "--version"]),
                      ("gcc", ["g++", "--version"]), ("gcov", ["gcov", "--version"]), ("kernel", ["uname", "-a"])]:
        must(audit.run("version-" + name, cmd))
    source = args.repo / "cpp/src/GildedRose.cc"
    original = source.read_text()
    initial_sha = sha(source)
    snapshot_path = Path('/lab/external/source_manifest.json')
    snapshot = json.loads(snapshot_path.read_text())
    if (args.repo / '.git').is_dir():
        commit = must(audit.run("repo-commit", ["git", "-c", f"safe.directory={args.repo}", "-C", str(args.repo), "rev-parse", "HEAD"]))["stdout"].strip()
    else:
        commit = snapshot['commit']
    verify_snapshot(args.repo, snapshot_path, commit)
    cases = generate()
    print(f"生成 {len(cases)} 个固定测试用例", flush=True)
    write_json(work / "cases.json", cases)
    write_json(work / "mutation_manifest.json", manifest())
    audit.event(kind="fixtures_frozen", cases_sha256=sha(work / "cases.json"),
                mutation_manifest_sha256=sha(work / "mutation_manifest.json"), total=len(cases))
    project = work / "generated"
    shutil.copytree("/lab/templates", project)
    build = work / "baseline/build"
    test_output = work / "baseline/test_result.json"
    def configure(label, build_dir, override=None):
        command = ["cmake", "-S", str(project), "-B", str(build_dir), "-G", "Ninja",
                   f"-DUPSTREAM_CPP={args.repo}/cpp", f"-DCASES_FILE={work}/cases.json",
                   f"-DRESULT_FILE={test_output}", f"-DAUDIT_DIR={work}/logs"]
        if override:
            command.append(f"-DSOURCE_OVERRIDE={override}")
        return audit.run(label + "-generate", command)
    must(configure("baseline", build))
    compile_commands = json.loads((build / 'compile_commands.json').read_text())
    compiled_files = [r['file'] for r in compile_commands]
    upstream_files = [f for f in compiled_files if Path(f).is_relative_to(args.repo)]
    if not upstream_files or any(not Path(f).is_relative_to(args.repo / 'cpp') for f in upstream_files):
        raise AssertionError('Compilation includes upstream files outside cpp/')
    if any(Path(f).suffix not in ('.cc', '.cpp', '.cxx', '.c++') for f in compiled_files):
        raise AssertionError('Compilation includes a non-C++ translation unit')
    source_scope = {'upstream_scope': 'cpp/', 'business_source': str(source),
                    'compiled_files': compiled_files, 'upstream_compiled_files': upstream_files,
                    'other_upstream_languages_compiled': False, 'case_count': len(cases),
                    'case_count_meaning': '同一份 C++ 实现的输入组合记录数，不是文件数或语言数'}
    write_json(work / 'source_scope.json', source_scope)
    audit.event(kind='compilation_scope_verified', **source_scope)
    must(audit.run("baseline-build", ["cmake", "--build", str(build), "--parallel", "2"]))
    must(audit.run("baseline-ctest", ["ctest", "--test-dir", str(build), "--output-on-failure", "-V"]))
    baseline = json.loads(test_output.read_text())
    if not baseline["passed"]:
        raise AssertionError("baseline contract failed")
    coverage = collect(build, work / "baseline/coverage", audit)
    print(f"基线通过；覆盖率：{coverage['text']['line']}，分支：{coverage['text']['branch_all']}", flush=True)
    spec_cases = [make_case("conjured_fresh", "known_spec_gap", "Conjured Mana Cake", 3, 6, 1),
                  make_case("conjured_expired", "known_spec_gap", "Conjured Mana Cake", 0, 6, 1)]
    for case in spec_cases:
        case["expected"] = expected(case["name"], case["sell_in"], case["quality"], case["days"], True)
    gap = evaluate(build / "rose_probe", spec_cases, audit, "known-conjured-spec-gap")
    write_json(work / "known_spec_gap.json", gap)
    results = []
    for mutation in catalogue():
        location = work / "mutants" / mutation.id
        override = location / "source"
        override.mkdir(parents=True)
        modified = mutation.apply(original)
        (override / "GildedRose.cc").write_text(modified)
        shutil.copy2(source.with_name("GildedRose.h"), override)
        (location / "mutation.diff").write_text("".join(difflib.unified_diff(original.splitlines(True), modified.splitlines(True),
                                                                    fromfile="upstream/GildedRose.cc", tofile=mutation.id + "/GildedRose.cc")))
        row = {"id": mutation.id, "kind": mutation.kind, "description": mutation.description,
               "original_sha256": initial_sha, "mutant_sha256": sha(override / "GildedRose.cc")}
        mutant_build = location / "build"
        configured = configure(mutation.id, mutant_build, override)
        if configured["returncode"]:
            row.update(status="infrastructure_error", step="cmake_generate")
        else:
            compiled = audit.run(mutation.id + "-build", ["cmake", "--build", str(mutant_build), "--parallel", "2"])
            row["build_returncode"] = compiled["returncode"]
            row["diagnostics"] = diagnostics(compiled)
            if mutation.kind in ("compile", "link"):
                valid = (compiled["returncode"] != 0 and not compiled["timed_out"] and
                         any(d["phase"] == mutation.kind for d in row["diagnostics"]))
                row["status"] = "caught" if valid else "not_caught"
            elif compiled["returncode"] or compiled["timed_out"]:
                row["status"] = "unexpected_build_failure"
            else:
                checked = evaluate(mutant_build / "rose_probe", cases, audit, mutation.id + "-test")
                write_json(location / "test_result.json", checked)
                row.update(failed_cases=checked["failed"], suite_failed=checked["suite_failed"],
                           first_counterexample=next(iter(checked["mismatches"]), None))
                row["status"] = ("infrastructure_error" if checked["returncode"] or not checked["protocol_valid"]
                                 else "killed" if checked["failed"] else "survived")
        write_json(location / "result.json", row)
        results.append(row)
        write_json(work / "mutation_results.json", results)
        audit.event(kind="mutation_result", result=row)
        print(f'{mutation.id} {mutation.kind}: {row["status"]}', flush=True)
    behavior = [r for r in results if r["kind"] == "behavior"]
    negative = [r for r in results if r["kind"] in ("compile", "link")]
    controls = [r for r in results if r["kind"] == "equivalent_control"]
    llm = score_challenge(Path('/lab/benchmark'), work / 'llm', build / 'rose_probe', audit)
    counts = dict(collections.Counter(c["suite"] for c in cases))
    verify_snapshot(args.repo, snapshot_path, commit)
    summary.update(completed_at=now(), commit=commit, source_sha256=initial_sha, upstream_scope='cpp/',
                   source_unchanged=(initial_sha == sha(source)), cases=len(cases), case_suites=counts,
                   cases_sha256=sha(work / "cases.json"), baseline_passed=baseline["passed"], coverage=coverage,
                   behavior_mutants={"detected": sum(r["status"] == "killed" for r in behavior), "total": len(behavior)},
                   suite_detection={suite: sum(r.get("suite_failed", {}).get(suite, 0) > 0 for r in behavior) for suite in counts},
                   build_error_capture={"detected": sum(r["status"] == "caught" for r in negative), "total": len(negative)},
                   equivalent_controls={"survived": sum(r["status"] == "survived" for r in controls), "total": len(controls)},
                   known_spec_gap={"failed": gap["failed"], "total": gap["total"]},
                   llm={key:llm[key] for key in ['protocol_valid','freeze_verified','rose','stress','by_family']})
    valid = (summary["source_unchanged"] and baseline["passed"] and coverage["parsers_agree"] and
             all(r["status"] == "killed" for r in behavior) and all(r["status"] == "caught" for r in negative) and
             all(r["status"] == "survived" for r in controls) and llm['protocol_valid'] and llm['freeze_verified'])
    summary["status"] = "passed" if valid else "failed"
    write_json(work / "summary.json", summary)
    audit.event(kind="pipeline_end", summary=summary)
    print(json.dumps(summary, ensure_ascii=False, indent=2))
    return 0 if valid else 1


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, default=Path("/repo"))
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    try:
        sys.exit(run(args))
    except Exception:
        if args.output.is_dir():
            error = traceback.format_exc()
            Audit(args.output / "logs").event(kind="pipeline_exception", traceback=error)
            summary_path = args.output / 'summary.json'
            summary = json.loads(summary_path.read_text()) if summary_path.exists() else {}
            summary.update(status='failed', error=error, completed_at=now())
            write_json(summary_path, summary)
        raise
