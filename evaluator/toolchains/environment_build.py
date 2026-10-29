"""D020 环境构建与隔离预检；产品持有独立副本，不跨产品导入。"""
import json
import os
from pathlib import Path
import uuid

from build_contract import environment_tag


def build_environment(audit, docker, recipe, digest, base_tag, context, output, mode,
                      platform=None, skip_build=False):
    output = Path(output)
    output.mkdir(parents=True, exist_ok=True)

    def call(stage, argv, timeout=180, env=None):
        result = audit.run(stage, argv, timeout=timeout, env=env)
        if result["returncode"] or result["timed_out"]:
            raise RuntimeError(f"构建环境 {stage} 失败，见 {result['stderr_log']}")
        return result["stdout"]

    base = json.loads(call(f"base-{mode}", docker + ["image", "inspect", base_tag]))[0]
    actual_platform = f"{base['Os']}/{base['Architecture']}"
    if actual_platform not in ("linux/arm64", "linux/amd64") or (platform and actual_platform != platform):
        raise ValueError("环境基础镜像架构不匹配")
    (output / "base-image.json").write_text(json.dumps(base, indent=2) + "\n")
    tag = environment_tag(recipe, digest, mode)
    if not skip_build:
        command = docker + ["build", "--force-rm", "--platform", actual_platform,
                           "--file", str(Path(context) / "Dockerfile.environment"),
                           "--build-arg", "BASE_IMAGE=" + base["Id"],
                           "--build-arg", "RECIPE_SHA256=" + digest,
                           "--build-arg", "PACKAGES=" + " ".join(k + "=" + v for k, v in recipe["packages"].items()),
                           "--tag", tag, str(context)]
        # Docker 28 的 BuildKit 把本地 sha256 ID 当作仓库名；legacy builder 支持按本地 ID 构建。
        # 显式选择该实现，保持 D020 的基础镜像 ID 锁定，不退回可变标签。
        call(f"environment-build-{mode}", command, 1800, dict(os.environ, DOCKER_BUILDKIT="0"))
    item = json.loads(call(f"environment-inspect-{mode}", docker + ["image", "inspect", tag]))[0]
    if item.get("Config", {}).get("Labels", {}).get("org.qualtor.environment.recipe-sha256") != digest:
        raise ValueError("构建环境镜像的配方哈希不一致")
    if f"{item['Os']}/{item['Architecture']}" != actual_platform:
        raise ValueError("构建环境镜像架构与基础镜像不一致")
    image = {"tag": tag, "id": item["Id"], "platform": actual_platform, "base_id": base["Id"]}
    (output / "image.json").write_text(json.dumps(item, indent=2) + "\n")
    packages = isolated_run(audit, docker, image, ["python3", "-c",
        'import json, pathlib, subprocess; print(json.dumps({"before": pathlib.Path("/opt/qualtor/environment-before.txt").read_text(), "after": subprocess.check_output(["dpkg-query", "-W", "-f=${binary:Package}\\t${Version}\\n"]).decode(), "sources": pathlib.Path("/etc/apt/sources.list.d/debian.sources").read_text()}))'],
        output / "packages")
    inventory = json.loads(packages)
    before = dict(line.split("\t", 1) for line in inventory["before"].splitlines())
    after = dict(line.split("\t", 1) for line in inventory["after"].splitlines())
    changed = {k: [v, after.get(k)] for k, v in before.items() if after.get(k) != v}
    if changed:
        raise ValueError(f"构建环境改变了基础包：{changed}")
    for name, version in recipe["packages"].items():
        installed = after.get(name, after.get(name + ":" + item["Architecture"]))
        if installed != version:
            raise ValueError(f"构建环境软件包版本不一致：{name}")
    uris = [line.split(":", 1)[1].strip() for line in inventory["sources"].splitlines() if line.startswith("URIs:")]
    if not uris or any(uri.rstrip("/") not in (
            f"http://snapshot.debian.org/archive/debian/{recipe['snapshot']}",
            f"http://snapshot.debian.org/archive/debian-security/{recipe['snapshot']}") for uri in uris):
        raise ValueError("环境软件源与固定快照不一致")
    (output / "packages-before.txt").write_text(inventory["before"])
    (output / "packages-after.txt").write_text(inventory["after"])
    (output / "packages-added.json").write_text(json.dumps({k: v for k, v in after.items() if k not in before}, indent=2) + "\n")
    return image


def isolated_run(audit, docker, image, argv, evidence, mounts=None, timeout=600, cancel=None):
    evidence = Path(evidence)
    evidence.mkdir(parents=True, exist_ok=True)
    mounts = mounts or {}
    name = "qenv-" + uuid.uuid4().hex[:16]
    command = docker + ["create", "--name", name, "--platform", image["platform"],
        "--network", "none", "--read-only", "--cpus", "2", "--memory", "2g", "--pids-limit", "256",
        "--user", f"{os.getuid()}:{os.getgid()}", "--cap-drop", "ALL", "--security-opt", "no-new-privileges",
        "--tmpfs", "/tmp:rw,exec,nosuid,nodev,size=512m,mode=1777", "-e", "PYTHONDONTWRITEBYTECODE=1"]
    for target, (source, readonly) in mounts.items():
        if "," in str(source):
            raise ValueError("环境挂载路径不能含逗号")
        command += ["--mount", f"type=bind,source={Path(source).resolve()},target={target}" + (",readonly" if readonly else "")]
    command += [image["id"], *argv]
    options = {} if cancel is None else {"cancel": cancel}
    try:
        created = audit.run("environment-create", command, **options)
        if created["returncode"] or created.get("cancelled"):
            raise RuntimeError(f"环境容器创建失败：{created['stderr_log']}")
        inspected = audit.run("environment-container-inspect", docker + ["inspect", name])
        actual = json.loads(inspected["stdout"])[0]
        (evidence / "container.json").write_text(json.dumps(actual, indent=2) + "\n")
        mounted = {m["Destination"]: m for m in actual["Mounts"]}
        if (actual["HostConfig"]["NetworkMode"] != "none" or not actual["HostConfig"]["ReadonlyRootfs"]
                or actual["Config"]["User"].split(":")[0] in ("", "0", "root")
                or set(mounted) != set(mounts)
                or any(mounted[t]["RW"] == ro for t, (_, ro) in mounts.items())):
            raise ValueError("环境容器隔离不匹配")
        result = audit.run("environment-run", docker + ["start", "--attach", name], timeout=timeout, **options)
        if result.get("cancelled"):
            raise RuntimeError("环境预检已取消")
        state = audit.run("environment-exit", docker + ["inspect", "--format", "{{json .State}}", name])
        (evidence / "exit.json").write_text(state["stdout"])
        if result["returncode"] or result["timed_out"] or json.loads(state["stdout"])["ExitCode"]:
            raise RuntimeError(f"环境容器执行失败：{result['stderr_log']}")
        return result["stdout"]
    finally:
        removed = audit.run("environment-remove", docker + ["rm", "--force", name], timeout=30)
        if removed["returncode"] and "No such container" not in removed["stderr"]:
            raise RuntimeError(f"环境容器清理失败：{removed['stderr_log']}")
