#!/usr/bin/env python3
"""把 agents/ 单独复制到仓库外，通过公开 CLI 验证独立交付。"""
import argparse
import json
from pathlib import Path
import shutil
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "common"))
from paths import AGENTS, RUNS
from audit import Audit
from runs import new_manifest, write_manifest, finish


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run-id", required=True)
    parser.add_argument('--environment', help='验证带构建环境的独立安装、链接、生成与修复')
    args = parser.parse_args()
    if not args.run_id.replace("-", "").replace("_", "").isalnum():
        parser.error("run-id 只能包含字母、数字、-、_")
    run = RUNS / args.run_id
    run.mkdir(parents=True, exist_ok=False)
    manifest = new_manifest(args.run_id, "eval", operation="delivery-selftest", framework_selftest=True)
    write_manifest(run, manifest)
    audit = Audit(run / "evidence")
    external = Path(tempfile.mkdtemp(prefix="qualtor-delivery-", dir="/private/tmp" if sys.platform == "darwin" else "/tmp"))
    package = external / "product"
    def ignored(directory, names):
        return [n for n in names if n in (".git", "__pycache__", ".artifacts", "output")
                or (n == "npm" and Path(directory) == AGENTS / ".cache")
                or (n.startswith(".env") and n != ".env.example")]
    try:
        shutil.copytree(AGENTS, package, symlinks=True, ignore=ignored)
        project = external / "customer-source"
        project.mkdir()
        (project / "counter.h").write_text("int next_value(int value);\n")
        (project / "counter.cc").write_text('#include "counter.h"\nint next_value(int value) { return value + 1; }\n')
        task = {"id": "customer-counter", "title": "独立交付示例", "source_root": "customer-source",
                "visible_files": ["counter.h", "counter.cc"], "target_sources": ["counter.cc"], "include_dirs": ["."],
                "allowed_test_files": ["tests/*.cc"], "budget": {"repair_rounds": 3}, "test_timeout_seconds": 5}
        if args.environment:
            (project / 'counter.cc').write_text('#include "counter.h"\n#include <zlib.h>\n'
                'int next_value(int value) { return zlibVersion()[0] == \'1\' ? value + 1 : value - 1; }\n')
            task['build'] = {'environment': args.environment, 'link_libraries': ['ZLIB::ZLIB']}
            setup = audit.run('independent-environment-setup',
                [sys.executable, str(package / 'setup.py'), '--environment', args.environment,
                 '--output', str(external / 'environment-setup')], cwd=external, timeout=2400)
            shutil.copytree(external / 'environment-setup', run / 'environment-setup')
            if setup['returncode']:
                raise RuntimeError(f"独立环境安装失败，见 {setup['stderr_log']}")
        (external / "task.json").write_text(json.dumps(task))
        good = '#include "counter.h"\n#include <gtest/gtest.h>\nTEST(Counter, Next) { EXPECT_EQ(4, next_value(3)); }\n'
        wrong = good.replace("EXPECT_EQ(4", "EXPECT_EQ(99")
        plan = [{"tool": "write", "args": {"path": "tests/counter.cc", "content": wrong}},
                {"tool": "build_and_test", "args": {}},
                {"tool": "read", "args": {"path": "feedback/attempt-1/result.json"}},
                {"tool": "write", "args": {"path": "tests/counter.cc", "content": good}},
                {"tool": "build_and_test", "args": {}}]
        (external / "scenario.json").write_text(json.dumps(plan))
        command = [sys.executable, str(package / "run.py"), "--task", str(external / "task.json"),
                   "--scenario", str(external / "scenario.json"), "--output", str(external / "result")]
        execution = audit.run("independent-product", command, cwd=external, timeout=600)
        if execution["returncode"]:
            raise RuntimeError(f"独立交付执行失败，见 {execution['stderr_log']}")
        output = external / "result"
        result = json.loads((output / "result.json").read_text())
        first = json.loads((output / "attempts/attempt-1/result.json").read_text())
        final = json.loads((output / "attempts/attempt-2/result.json").read_text())
        events = [json.loads(line) for line in (output / "logs/pi.stdout.jsonl").read_text().splitlines()]
        feedback_reads = [e for e in events if e.get("type") == "tool_execution_end" and e.get("toolName") == "read"]
        containers = [json.loads(p.read_text()) for p in (output / "attempts").glob("*/container.json")]
        checks = {"outside_repository": not external.is_relative_to(AGENTS.parent),
                  "no_evaluator_benchmark_git": not any((package / n).exists() for n in ("evaluator", "benchmark", ".git")),
                  "no_credentials_copied": not (package / ".env").exists(),
                  "host_pi": result["runtime"] == "host-pi", "finished": result["status"] == "finished",
                  "automatic_repair": result["repair_rounds"] == 1 and first["status"] == "tests_failed" and final["status"] == "passed",
                  "feedback_readable": bool(feedback_reads) and all(not e.get("isError") for e in feedback_reads),
                  "docker_source_and_tests_readonly": all(not m["RW"] for c in containers for m in c["Mounts"] if m["Destination"] in ("/project", "/product")),
                  "docker_offline": all(c["HostConfig"]["NetworkMode"] == "none" for c in containers)}
        if args.environment:
            environment = result.get('toolchain', {}).get('environment') or {}
            checks['environment_recorded'] = (environment.get('name') == args.environment
                and environment.get('gcc_image_id') == result.get('toolchain', {}).get('id'))
        shutil.copytree(output, run / "product-result")
        shutil.copytree(project, run / "source")
        for name in ("task.json", "scenario.json"):
            shutil.copy2(external / name, run / name)
        summary = {"passed": all(checks.values()), "checks": checks, "external_directory": str(external)}
        (run / "summary.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2) + "\n")
        finish(run, manifest, "completed", passed=summary["passed"])
        print(json.dumps(summary, ensure_ascii=False))
        return 0 if summary["passed"] else 1
    except BaseException as error:
        finish(run, manifest, "failed", error=str(error), external_directory=str(external))
        raise


if __name__ == "__main__":
    raise SystemExit(main())
