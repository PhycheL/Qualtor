#!/usr/bin/env python3
"""独立安装宿主机 pi 依赖并构建 GCC 镜像；无需 evaluator、benchmark 或 Git。"""
import argparse
import datetime as dt
import os
from pathlib import Path
import sys

from common.audit import Audit
from generator.build.docker import docker_command
from generator.support import AGENTS, dependency_hash, host_platform, read_json, tree_hash, write_json


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    scope = parser.add_mutually_exclusive_group()
    scope.add_argument("--pi-only", action="store_true")
    scope.add_argument("--gcc-only", action="store_true")
    scope.add_argument("--environment", help="构建指定环境的 GCC 镜像（名称或配方路径），不重建基础镜像")
    parser.add_argument("--platform", choices=["linux/arm64", "linux/amd64"])
    parser.add_argument("--output", type=Path, default=AGENTS / "output" / dt.datetime.now(dt.timezone.utc).strftime("setup-%Y%m%d-%H%M%S"))
    args = parser.parse_args()
    args.output = args.output.resolve()
    args.output.mkdir(parents=True, exist_ok=False)
    audit = Audit(args.output / "evidence/host")
    summary = {"status": "running", "host": host_platform()}
    manifest = {"schema": 1, "run_id": args.output.name, "kind": "toolchain", "operation": "product-setup",
                "status": "running", "started_at": dt.datetime.now(dt.timezone.utc).isoformat()}
    write_json(args.output / "run.json", manifest)
    write_json(args.output / "summary.json", summary)
    def call(stage, command, cwd=AGENTS, env=None):
        result = audit.run(stage, command, cwd=cwd, timeout=1800, echo=True, env=env)
        if result["returncode"] or result["timed_out"]:
            raise RuntimeError(f"{stage} 失败；见 {result['stderr_log']}")
    try:
        if not args.gcc_only and not args.environment:
            if tuple(map(int, summary["host"]["node"].lstrip("v").split(".")[:2])) < (23, 6):
                raise ValueError("产品需要 Node >= 23.6（原生 TypeScript 支持），推荐 Node 24 或更新版本")
            env = dict(os.environ, HUSKY="0", npm_config_cache=str(AGENTS / ".cache/npm"))
            call("npm-ci-host", ["npm", "ci", "--ignore-scripts"], AGENTS / "pi", env)
            call("build-pi-host", ["node", str(AGENTS / "build_pi.mjs")], env=env)
            env.update(PI_CODING_AGENT_DIR=str(AGENTS / ".cache/tools"), PI_OFFLINE="0")
            call("install-search-tools", ["node", str(AGENTS / "setup_tools.mjs")], env=env)
            stamp = {"host": summary["host"], "source_sha256": tree_hash(AGENTS / "pi"),
                     "runtime_sha256": tree_hash(AGENTS / "pi", runtime=True),
                     "dependencies_sha256": dependency_hash(AGENTS / "pi"),
                     "search_tools": read_json(AGENTS / ".cache/tools/bin/manifest.json")}
            write_json(AGENTS / "pi/.qualtor-build.json", stamp)
            summary["pi"] = stamp
        if args.environment:
            from generator.build.contract import load_environment
            from generator.build.environment import build_environment, isolated_run
            recipe, digest = load_environment(args.environment, AGENTS / "toolchains/environments")
            destination = AGENTS / 'toolchains/environments' / (recipe['name'] + '.json')
            if Path(args.environment).suffix == '.json' and destination.exists():
                existing, existing_digest = load_environment(str(destination), destination.parent)
                if existing_digest != digest:
                    raise ValueError('环境名称已被另一配方使用；请为用户配方使用新的名称')
            docker = docker_command(audit, args.output / "evidence")
            tag = read_json(AGENTS / "toolchains/images.json")["gcc"]
            image = build_environment(audit, docker, recipe, digest, tag, AGENTS / "toolchains/docker",
                                      args.output / "gcc", "gcc", args.platform)
            write_json(args.output / "recipe.json", recipe)
            isolated_run(audit, docker, image,
                ["python3", "/toolchains/check_environment.py", "--toolchain", "gcc",
                 "--recipe", "/recipe.json", "--output", "/work"], args.output / "gcc/smoke-container",
                {"/toolchains": (AGENTS / "toolchains", True), "/common": (AGENTS / "common", True),
                 "/recipe.json": (args.output / "recipe.json", True), "/work": (args.output / "gcc", False)})
            summary["environment"] = {"name": recipe["name"], "recipe_sha256": digest, "image": image}
            if Path(args.environment).suffix == '.json' and not destination.exists():
                destination.parent.mkdir(parents=True, exist_ok=True)
                destination.write_bytes(Path(args.environment).read_bytes())
        elif not args.pi_only:
            docker = docker_command(audit, args.output / "evidence")
            tag = read_json(AGENTS / "toolchains/images.json")["gcc"]
            command = docker + ["build", "--progress", "plain", "--file", str(AGENTS / "toolchains/docker/Dockerfile.gcc"),
                               "--target", "gcc", "--tag", tag]
            if args.platform:
                command += ["--platform", args.platform]
            call("build-gcc", command + [str(AGENTS / "toolchains/docker")])
            call("inspect-gcc", docker + ["image", "inspect", tag])
            summary["gcc"] = tag
        summary["status"] = "completed"
    except BaseException as error:
        summary.update(status="failed", error=str(error))
        raise
    finally:
        write_json(args.output / "summary.json", summary)
        manifest.update(status=summary["status"], passed=summary["status"] == "completed",
                        finished_at=dt.datetime.now(dt.timezone.utc).isoformat())
        if "error" in summary:
            manifest["error"] = summary["error"]
        write_json(args.output / "run.json", manifest)
    print(f"安装完成；证据：{args.output}")


if __name__ == "__main__":
    main()
