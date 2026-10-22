#!/usr/bin/env python3
"""一条命令复现实验；仓库、脚本、构建输出全部使用宿主机 bind mounts。"""
import argparse
import datetime as dt
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "scripts"))
from audit import Audit
from source_snapshot import cpp_files, verify_snapshot

IMAGE = "qualtor-gildedrose-toolchain:bookworm"
REVISION = "d6407909c73b2ba61bfa7568af0d9bdce1902fd5"
REPOSITORY = "https://github.com/emilybache/GildedRose-Refactoring-Kata.git"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--skip-build", action="store_true")
    parser.add_argument("--run-id", default=dt.datetime.now(dt.timezone.utc).strftime("run-%Y%m%dT%H%M%SZ"))
    args = parser.parse_args()
    if not args.run_id.replace("-", "").replace("_", "").isalnum():
        parser.error("run-id may contain only letters, digits, - and _")
    audit = Audit(ROOT / "artifacts/host")
    def call(stage, command, timeout=180, echo=True):
        result = audit.run(stage, command, cwd=ROOT, timeout=timeout, echo=echo)
        if result["returncode"] or result["timed_out"]:
            raise RuntimeError(f"{stage} failed; see {result['stderr_log']}")
        return result
    repo = ROOT / "external/GildedRose-Refactoring-Kata"
    snapshot_path = ROOT / 'external/source_manifest.json'
    new_checkout = not repo.exists()
    if not repo.exists():
        repo.parent.mkdir(parents=True, exist_ok=True)
        call("clone-pinned-main", ["git", "clone", "--depth", "1", "--filter=blob:none", "--no-checkout", "--branch", "main", REPOSITORY, str(repo)], 300)
        head = call("clone-head", ["git", "-C", str(repo), "rev-parse", "HEAD"])["stdout"].strip()
        if head != REVISION:
            call("fetch-pinned-revision", ["git", "-C", str(repo), "fetch", "--depth", "1", "origin", REVISION], 300)
            call("checkout-pinned-revision", ["git", "-C", str(repo), "checkout", "--detach", REVISION])
    has_git = (repo / '.git').is_dir()
    if has_git:
        head = call("verify-revision", ["git", "-C", str(repo), "rev-parse", "HEAD"])["stdout"].strip()
        if head != REVISION:
            raise RuntimeError("Existing checkout differs from pinned revision; preserving it.")
        if not new_checkout:
            dirty = call("verify-clean-checkout", ["git", "-C", str(repo), "status", "--porcelain"])["stdout"].strip()
            if dirty:
                raise RuntimeError("Upstream checkout contains local changes; refusing to remove files.")
        # 兼容本机 Git 2.23：不依赖较新版本的 git sparse-checkout 子命令。
        call('enable-cpp-only-checkout', ['git', '-C', str(repo), 'config', 'core.sparseCheckout', 'true'])
        patterns = repo / '.git/info/sparse-checkout'
        patterns.parent.mkdir(parents=True, exist_ok=True)
        patterns.write_text('/cpp/\n')
        call('checkout-only-cpp', ['git', '-C', str(repo), 'read-tree', '-mu', 'HEAD'])
        snapshot = {'repository': REPOSITORY, 'commit': REVISION, 'scope': ['cpp'], 'files': cpp_files(repo)}
        snapshot_path.write_text(json.dumps(snapshot, ensure_ascii=False, indent=2) + '\n')
    verify_snapshot(repo, snapshot_path, REVISION)
    audit.event(kind='source_scope_verified', scope=['cpp'], git_metadata_present=has_git,
                snapshot_manifest=str(snapshot_path), source_files=len(cpp_files(repo)))
    context = call("docker-endpoint", ["docker", "context", "inspect", "--format", "{{.Endpoints.docker.Host}}"], echo=False)["stdout"].strip()
    client = ROOT / "artifacts/docker-client"
    client.mkdir(parents=True, exist_ok=True)
    config = {"auths": {}, "cliPluginsExtraDirs": [str(Path.home() / ".docker/cli-plugins")]}
    (client / "config.json").write_text(json.dumps(config, indent=2) + "\n")
    docker = ["docker", "--config", str(client), "--host", context]
    call("docker-version", docker + ["version"])
    if not args.skip_build:
        call("build-toolchain", docker + ["build", "--progress", "plain", "--tag", IMAGE, str(ROOT / "docker")], 1800)
    image = call("image-inspect", docker + ["image", "inspect", IMAGE], echo=False)
    evidence = ROOT / "artifacts" / args.run_id
    evidence.mkdir(parents=True, exist_ok=False)
    (evidence / "image-inspect.json").write_text(image["stdout"])
    history = call("image-history", docker + ["history", "--no-trunc", IMAGE], echo=False)
    (evidence / "image-history.txt").write_text(history["stdout"])
    call("image-has-no-project", docker + ["run", "--rm", "--network", "none", IMAGE, "python3", "-c",
         "from pathlib import Path; assert not Path('/repo').exists(); assert not Path('/lab').exists(); print('No repository or lab paths exist without mounts')"])
    runs = ROOT / "runs"
    runs.mkdir(exist_ok=True)
    name = "qualtor-" + args.run_id.lower()
    command = docker + ["create", "--name", name, "--network", "none", "--cpus", "2", "--memory", "2g",
          "--pids-limit", "256", "--cap-drop", "ALL", "--security-opt", "no-new-privileges", "--read-only",
          "--tmpfs", "/tmp:rw,nosuid,nodev,size=128m,mode=1777", "--user", f"{os.getuid()}:{os.getgid()}",
          "-e", "PYTHONDONTWRITEBYTECODE=1", "--mount", f"type=bind,source={repo},target=/repo,readonly",
          "--mount", f"type=bind,source={ROOT},target=/lab,readonly",
          "--mount", f"type=bind,source={runs},target=/work",
          IMAGE, "python3", "/lab/scripts/pipeline.py", "--output", "/work/" + args.run_id]
    call("container-create", command)
    inspected = call("container-inspect-before", docker + ["inspect", name], echo=False)
    (evidence / "container-inspect-before.json").write_text(inspected["stdout"])
    record = json.loads(inspected["stdout"])[0]
    mounts = {m["Destination"]:m for m in record["Mounts"]}
    assert mounts["/repo"]["Type"] == "bind" and not mounts["/repo"]["RW"]
    assert mounts["/lab"]["Type"] == "bind" and not mounts["/lab"]["RW"]
    assert mounts["/work"]["Type"] == "bind" and mounts["/work"]["RW"]
    execution = audit.run("container-pipeline", docker + ["start", "--attach", name], cwd=ROOT, timeout=1800, echo=True)
    final = call("container-inspect-after", docker + ["inspect", name], echo=False)
    (evidence / "container-inspect-after.json").write_text(final["stdout"])
    state = json.loads(final["stdout"])[0]["State"]
    if state["Running"]:
        call("stop-timed-out-task-container", docker + ["stop", "--time", "10", name])
    call("container-remove", docker + ["rm", name])
    if has_git:
        clean = call("verify-upstream-after", ["git", "-C", str(repo), "status", "--porcelain"])
        if clean['stdout'].strip():
            raise RuntimeError('Upstream changed during experiment')
    verify_snapshot(repo, snapshot_path, REVISION)
    audit.event(kind="host_run_finished", run_id=args.run_id, container_exit_code=state["ExitCode"],
                host_returncode=execution["returncode"], output=str(runs / args.run_id))
    if state["ExitCode"] or execution["returncode"] or execution["timed_out"]:
        return 1
    (ROOT / "artifacts/latest-run.txt").write_text(args.run_id + "\n")
    print(f"结果目录：{runs / args.run_id}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
