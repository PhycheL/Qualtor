#!/usr/bin/env python3
"""构建并验收两套固定版本的 C++11 Docker 工具链。"""
import argparse
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT.parent / "common"))
from paths import REPO, COMMON, RUNS, BENCHMARK, AGENTS
from audit import Audit, now
from runs import finish, new_manifest, write_manifest
from source_snapshot import verify_snapshot

IMAGES = {
    "gcc": json.loads((AGENTS / "toolchains/images.json").read_text())["gcc"],
    "clang": "docker.io/library/qualtor-clang:19.1.7-mull0.34.2-gtest1.12.1-cxx11",
}
BUILD_IMAGES = IMAGES


def write_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n")


def execute(args, evidence, summary):
    audit = Audit(evidence / "host")

    def call(stage, command, timeout=180, echo=False):
        result = audit.run(stage, command, cwd=ROOT, timeout=timeout, echo=echo)
        if result["returncode"] or result["timed_out"]:
            raise RuntimeError(f"{stage} failed; see {result['stderr_log']}")
        return result["stdout"]

    endpoint = call("docker-endpoint", ["docker", "context", "inspect", "--format", "{{.Endpoints.docker.Host}}"])
    client = evidence / "docker-client"
    client.mkdir()
    write_json(client / "config.json", {"auths": {}, "cliPluginsExtraDirs": [str(Path.home() / ".docker/cli-plugins")]})
    docker = ["docker", "--config", str(client), "--host", endpoint.strip()]
    call("docker-version", docker + ["version"])
    modes = list(BUILD_IMAGES) if args.toolchain == "all" else [args.toolchain]
    inputs = [ROOT / "toolchains.py", ROOT / "docker/Dockerfile.toolchains", ROOT / "docker/.dockerignore",
              ROOT / "check_toolchain.py", COMMON / "audit.py", COMMON / "coverage.py",
              COMMON / "source_snapshot.py", AGENTS / "toolchains/images.json",
              AGENTS / "toolchains/docker/Dockerfile.gcc", *sorted((ROOT / "smoke").glob("*"))]
    write_json(evidence / "inputs.json", {str(p.relative_to(REPO)): hashlib.sha256(p.read_bytes()).hexdigest()
                                        for p in inputs if p.is_file()})
    repo = BENCHMARK / "gildedrose-update-quality/source"
    snapshot_path = repo / "SOURCE.json"
    if not args.build_only:
        # 不重新生成清单或更新上游；缺少源码时按实验说明准备固定快照。
        snapshot = json.loads(snapshot_path.read_text())
        verify_snapshot(repo, snapshot_path, snapshot["commit"])
        write_json(evidence / "source_manifest.json", snapshot)
    run = RUNS / args.run_id
    if not args.build_only:
        run.mkdir(parents=True, exist_ok=True)
    for mode in modes:
        tag = BUILD_IMAGES[mode]
        if not args.skip_build:
            print(f"构建 {mode}：{tag}", flush=True)
            context = AGENTS / "toolchains/docker" if mode == "gcc" else ROOT / "docker"
            dockerfile = context / ("Dockerfile.gcc" if mode == "gcc" else "Dockerfile.toolchains")
            build = docker + ["build", "--progress", "plain", "--file", str(dockerfile),
                              "--target", mode, "--tag", tag]
            if args.platform:
                build += ["--platform", args.platform]
            call(f"build-{mode}", build + [str(context)], timeout=1800, echo=True)
        record = json.loads(call(f"inspect-{mode}-image", docker + ["image", "inspect", tag]))[0]
        image_id = record["Id"]
        actual_platform = f"{record['Os']}/{record['Architecture']}"
        if actual_platform not in ("linux/arm64", "linux/amd64"):
            raise RuntimeError(f"不支持的镜像平台：{actual_platform}")
        if args.platform and actual_platform != args.platform:
            raise RuntimeError(f"镜像平台 {actual_platform} 与指定平台 {args.platform} 不一致")
        write_json(evidence / f"{mode}-image.json", record)
        (evidence / f"{mode}-history.txt").write_text(call(f"history-{mode}", docker + ["history", "--no-trunc", image_id]))
        summary["images"][mode] = {"tag": tag, "id": image_id, "platform": actual_platform}
        if args.build_only:
            continue
        output = run / mode
        output.mkdir()
        name = f"qualtor-{args.run_id.lower()}-{mode}"
        command = docker + ["create", "--name", name, "--platform", actual_platform,
                  "--network", "none", "--cpus", "2", "--memory", "2g", "--pids-limit", "256",
                  "--cap-drop", "ALL", "--security-opt", "no-new-privileges", "--read-only",
                  "--tmpfs", "/tmp:rw,nosuid,nodev,size=128m,mode=1777", "--user", f"{os.getuid()}:{os.getgid()}",
                  "-e", "PYTHONDONTWRITEBYTECODE=1", "-e", "MULL_CONFIG=/smoke/mull.yml",
                  "--mount", f"type=bind,source={repo},target=/repo,readonly",
                  "--mount", f"type=bind,source={COMMON},target=/common,readonly",
                  "--mount", f"type=bind,source={ROOT / 'smoke'},target=/smoke,readonly",
                  "--mount", f"type=bind,source={ROOT},target=/toolchains,readonly",
                  "--mount", f"type=bind,source={output},target=/work",
                  image_id, "python3", "/toolchains/check_toolchain.py", "--toolchain", mode]
        call(f"create-{mode}", command)
        try:
            before = json.loads(call(f"inspect-{mode}-before", docker + ["inspect", name]))[0]
            write_json(evidence / f"{mode}-container-before.json", before)
            mounts = {m["Destination"]: m for m in before["Mounts"]}
            if (before["HostConfig"]["NetworkMode"] != "none" or not before["HostConfig"]["ReadonlyRootfs"]
                    or any(mounts[p]["RW"] for p in ("/repo", "/common", "/smoke")) or not mounts["/work"]["RW"]):
                raise RuntimeError("容器隔离配置不正确")
            print(f"验收 {mode}（{actual_platform}，C++11）", flush=True)
            execution = audit.run(f"check-{mode}", docker + ["start", "--attach", name], cwd=ROOT, timeout=600, echo=True)
            after = json.loads(call(f"inspect-{mode}-after", docker + ["inspect", name]))[0]
            write_json(evidence / f"{mode}-container-after.json", after)
            if (execution["returncode"] or execution["timed_out"] or after["State"]["Running"]
                    or after["State"]["ExitCode"]):
                raise RuntimeError(f"{mode} 容器验收失败，见 {output} 和 {evidence / 'host'}")
            result = json.loads((output / "summary.json").read_text())
            if result["status"] != "passed":
                raise RuntimeError(f"{mode} 验收未通过")
            summary["checks"][mode] = result
        finally:
            # 超时也只清理本次创建的容器，原始日志和输出目录始终保留。
            state = call(f"state-{mode}", docker + ["inspect", "--format", "{{.State.Running}}", name]).strip()
            if state == "true":
                call(f"stop-{mode}", docker + ["stop", "--time", "5", name])
            call(f"remove-{mode}", docker + ["rm", name])
            verify_snapshot(repo, snapshot_path, snapshot["commit"])
    summary["status"] = "built" if args.build_only else "passed"
    if not args.build_only:
        write_json(run / "summary.json", summary)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolchain", choices=["all", "gcc", "clang"], default="all")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--skip-build", action="store_true", help="使用本机已构建的固定版本镜像")
    group.add_argument("--build-only", action="store_true", help="只构建镜像，不运行验收")
    parser.add_argument("--platform", choices=["linux/arm64", "linux/amd64"], help="默认使用 Docker 当前平台")
    parser.add_argument("--run-id", default=dt.datetime.now(dt.timezone.utc).strftime("toolchain-%Y%m%d-%H%M%S"))
    args = parser.parse_args()
    if not re.fullmatch(r"[a-zA-Z0-9][a-zA-Z0-9_-]{0,79}", args.run_id):
        parser.error("run-id 只能包含字母、数字、-、_，以字母或数字开头且最多 80 字符")
    evidence = RUNS / args.run_id / "evidence"
    if evidence.exists() or (RUNS / args.run_id).exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    evidence.mkdir(parents=True, exist_ok=False)
    run = RUNS / args.run_id
    manifest = new_manifest(args.run_id, "toolchain", toolchain=args.toolchain, build_only=args.build_only)
    write_manifest(run, manifest)
    summary = {"kind": "toolchain", "status": "running", "started_at": now(), "run_id": args.run_id, "images": {}, "checks": {}}
    crashed = False
    interruption = None
    try:
        execute(args, evidence, summary)
    except BaseException as error:
        crashed = True
        if not isinstance(error, Exception):
            interruption = error
        summary.update(status="failed", error=str(error))
        print(f"失败：{error}", file=sys.stderr)
    summary["finished_at"] = now()
    write_json(evidence / "summary.json", summary)
    write_json(run / "summary.json", summary)
    # summary.json 保留验收结论 passed/failed/built；run.json 只用统一状态，结论写在 passed 字段。
    finish(run, manifest, "failed" if crashed else "completed", passed=summary["status"] in ("passed", "built"),
           result=summary["status"], **({"error": summary["error"]} if crashed else {}))
    print(f"状态：{summary['status']}；证据：{evidence}")
    if interruption is not None:
        raise interruption
    return 0 if summary["status"] in ("passed", "built") else 1


if __name__ == "__main__":
    raise SystemExit(main())
