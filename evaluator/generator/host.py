"""宿主机上的 pi 专用接线：配置、可见材料、容器生命周期和产物评分。"""
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time
import uuid
from urllib.parse import urlsplit

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent / "scorer"), str(HERE.parent / "common"), str(HERE.parent / "toolchains")]
from paths import AGENTS, COMMON, GENERATOR, REPO, SCORER
from audit import Audit
from common import (freeze_product, now, read_json, scorer_version, sha256_file, sha256_text, source_root,
                    validate_product, write_json)
import pipeline
from cost import extract, add_costs
from toolchains import GENERATOR_IMAGE

# Agent 可写目录都是限定大小的 tmpfs，写满时写入失败，不会占满宿主机磁盘；结束时由监督进程复制回 trial 记录。
AGENT_TMPFS = {"/workspace/tests": "64m", "/agent/state": "16m", "/agent/sessions": "256m"}


def deps_fingerprint(root, modules):
    """依赖目录的元数据指纹（路径、类型、大小、修改时间）。依赖文件多达数万个，逐个读内容太慢；
    任何安装、删除或修改都会改变大小或修改时间，从而被发现。"""
    parts = []
    for directory, dirs, files in os.walk(modules):
        dirs.sort()
        for name in sorted(dirs + files):
            path = Path(directory) / name
            info = path.lstat()
            kind = "l" if path.is_symlink() else ("d" if path.is_dir() else "f")
            parts.append(f"{path.relative_to(root)}\0{kind}\0{info.st_size}\0{info.st_mtime_ns}")
    return sha256_text("\n".join(parts))


def tree_hash(root, runtime=False):
    """源码按内容哈希。runtime=True 时再加上构建产物 dist/ 和依赖目录 node_modules/ 的元数据指纹，
    用来确认实际运行的 pi 与构建记录一致。"""
    root = Path(root)
    parts = []
    for directory, dirs, files in os.walk(root):
        if runtime and "node_modules" in dirs:
            modules = Path(directory) / "node_modules"
            parts.append(f"{modules.relative_to(root)}\0deps\0{deps_fingerprint(root, modules)}")
        dirs[:] = sorted(d for d in dirs if d not in (".git", "node_modules", "__pycache__", ".artifacts")
                         and (runtime or d != "dist"))
        for name in sorted(files):
            path = Path(directory) / name
            if name == ".qualtor-build.json" or path.suffix == ".pyc":
                continue
            parts.append(f"{path.relative_to(root)}\0{sha256_file(path)}")
    return sha256_text("\n".join(parts))


def git_snapshot():
    commit = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=REPO).decode().strip()
    diff = subprocess.check_output(["git", "diff", "HEAD", "--binary"], cwd=REPO)
    untracked = subprocess.check_output(["git", "ls-files", "--others", "--exclude-standard", "-z"], cwd=REPO)
    digest = hashlib.sha256(diff)
    for name in sorted(filter(None, untracked.decode().split("\0"))):
        path = REPO / name
        if path.is_file():
            digest.update(name.encode() + b"\0" + path.read_bytes())
    return {"commit": commit, "dirty": bool(diff or untracked), "uncommitted_sha256": digest.hexdigest()}


def read_dotenv(path):
    """读取单行字面值；不执行 shell、不插值，错误中不回显配置内容。"""
    try:
        lines = path.read_text(encoding="utf-8-sig").splitlines()
    except FileNotFoundError:
        raise ValueError("缺少仓库根目录 .env，请复制 .env.example 后填写 API 地址和密钥") from None
    except (OSError, UnicodeError):
        raise ValueError("无法读取仓库根目录 .env，请检查文件权限和 UTF-8 编码") from None
    values = {}
    for number, line in enumerate(lines, 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        match = re.fullmatch(r"(?:export\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)", line)
        if not match:
            raise ValueError(f".env 第 {number} 行格式错误，应为 KEY=VALUE")
        key, value = match.groups()
        if value.startswith(("'", '"')):
            end = value.find(value[0], 1)
            tail = value[end + 1:].strip() if end >= 0 else ""
            if end < 0 or (tail and not tail.startswith("#")):
                raise ValueError(f".env 第 {number} 行引号格式错误")
            value = value[1:end]
        else:
            value = "" if value.startswith("#") else re.split(r"\s+#", value, maxsplit=1)[0].rstrip()
        if "\0" in value or key in values:
            raise ValueError(f".env 第 {number} 行含空字符或重复字段")
        values[key] = value
    return values


def load_config(name):
    if not re.fullmatch(r"[a-zA-Z0-9_-]+", name):
        raise ValueError("配置名只能包含字母、数字、-、_")
    path = AGENTS / "configs" / name / "config.json"
    config = read_json(path)
    required = ("provider", "model", "thinking", "api", "base_url_env", "api_key_env")
    for key in required:
        if not isinstance(config.get(key), str) or not config[key].strip():
            raise ValueError(f"请填写 {path.relative_to(REPO)} 的 {key}")
    if set(config) - set(required) - {"reasoning", "context_window", "max_tokens", "cost_per_million", "compat", "thinking_level_map"}:
        raise ValueError("配置含未知字段；密钥和 API 地址仅从仓库根目录 .env 读取")
    if config["thinking"] not in ("off", "minimal", "low", "medium", "high", "xhigh", "max"):
        raise ValueError("thinking 必须是 pi 支持的思考级别")
    for key in ("base_url_env", "api_key_env"):
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", config[key]):
            raise ValueError(f"{key} 必须是环境变量名")
    values = read_dotenv(REPO / ".env")
    for key in ("base_url_env", "api_key_env"):
        if not values.get(config[key], "").strip():
            raise ValueError(f"请在仓库根目录 .env 中填写 {config[key]}")
    base = values[config["base_url_env"]]
    url = urlsplit(base)
    if url.scheme not in ("http", "https") or not url.hostname or url.username or url.password or url.query or url.fragment:
        raise ValueError("API 地址必须是 http(s) URL，且不包含凭证、查询参数或 fragment")
    # 只导出选中配置的两个字段，供 Docker 按名称取值；不加载 .env 中的其他宿主机设置。
    os.environ.update({config[key]: values[config[key]] for key in ("base_url_env", "api_key_env")})
    config["base_url"] = base
    config.setdefault("reasoning", False)
    config.setdefault("context_window", 131072)
    config.setdefault("max_tokens", 8192)
    config.setdefault("cost_per_million", None)
    return config, {"name": name, "sha256": sha256_file(path), "settings": config}


def public_task(task):
    budget = task["budget"].get("repair_rounds")
    if type(budget) is not int or budget < 0:
        raise ValueError("task.json 的 budget.repair_rounds 必须是非负整数")
    root = source_root(task)
    visible = task.get("visible", {}).get("files", [])
    if not visible:
        raise ValueError("任务必须明确 visible.files")
    for rel in visible:
        path = root / rel
        if Path(rel).is_absolute() or ".." in Path(rel).parts or not path.is_file() or path.is_symlink():
            raise ValueError(f"不合法的可见文件：{rel}")
        if not path.resolve().is_relative_to(root):
            raise ValueError(f"可见文件越过源码目录：{rel}")
    if not set(task["target_sources"]) <= set(visible):
        raise ValueError("被测源文件必须列入 visible.files")
    return {"id": task["id"], "title": task["title"], "target_sources": task["target_sources"],
            "include_dirs": task["include_dirs"], "visible_files": visible,
            "allowed_test_files": task["allowed_test_files"], "budget": {"repair_rounds": budget},
            "test_timeout_seconds": task["params"]["test_timeout_seconds"]}


def task_text(task):
    return f"""# 测试生成任务：{task['title']}

为现有 C++11 代码生成 GoogleTest 1.12.1 单元测试。断言以代码的实际行为为准。
通过 read、grep、find、ls 阅读源码，通过 write、edit 编写测试，通过 build_and_test 编译并运行。

- 被测文件：{', '.join('project/' + p for p in task['target_sources'])}
- 可见文件：{', '.join('project/' + p for p in task['visible_files'])}
- 允许修改：{', '.join(task['allowed_test_files'])}。只提交这些测试文件。
- 头文件目录：{', '.join('project/' + p for p in task['include_dirs'])}；构建时也包含 tests/。
- 修复预算：{task['budget']['repair_rounds']} 轮。第 1 次 build_and_test 冻结首次产物，不算修复；以后每次调用消耗 1 轮。
- 单测超时：{task['test_timeout_seconds']} 秒。build_and_test 返回编译错误或每个测试的通过/失败信息与剩余轮次。

先生成能检查行为的测试，主动编译验证；如编译失败或断言失败，根据结果修正并在预算内再次验证。
预算用尽后工具会拒绝再次编译。完成后结束对话，框架将自动冻结最终产物。
"""


class GenerationExecutor:
    def __init__(self, docker_executor):
        self.ex = docker_executor
        record = json.loads(self.ex._call("inspect-generator-image", self.ex.docker + ["image", "inspect", GENERATOR_IMAGE]))[0]
        self.image = {"tag": GENERATOR_IMAGE, "id": record["Id"], "platform": f"{record['Os']}/{record['Architecture']}"}
        if self.image["platform"] != self.ex.images["gcc"]["platform"]:
            raise ValueError("生成镜像和评分镜像架构必须一致")
        if not (AGENTS / "pi/packages/coding-agent/dist/cli.js").is_file():
            raise ValueError("pi 尚未在生成镜像中构建；先运行 toolchains.py --toolchain generator")
        stamp_path = AGENTS / "pi/.qualtor-build.json"
        if not stamp_path.is_file():
            raise ValueError("缺少 pi 构建记录；先运行 toolchains.py --toolchain generator")
        stamp = read_json(stamp_path)
        if (stamp.get("image_id") != self.image["id"] or stamp.get("source_sha256") != tree_hash(AGENTS / "pi")
                or stamp.get("runtime_sha256") != tree_hash(AGENTS / "pi", runtime=True)):
            raise ValueError("pi 或生成镜像已改变，需要重新运行 toolchains.py --toolchain generator")

    def generate(self, task, config, record, scenario=None, watchdog=900):
        record = Path(record)
        record.mkdir(parents=True, exist_ok=False)
        (record / "workspace/tests").mkdir(parents=True)
        (record / "pi-state").mkdir()
        (record / "logs/sessions").mkdir(parents=True)
        inputs = record / "input"
        inputs.mkdir()
        public = public_task(task)
        (record / "TASK.md").write_text(task_text(public))
        write_json(inputs / "runtime.json", {"task": public, "model": config, "scripted": scenario is not None,
                                               "watchdog_seconds": watchdog})
        if scenario is not None:
            write_json(inputs / "scenario.json", scenario)
        audit = Audit(record / "logs/container")
        name = "qg-" + uuid.uuid4().hex[:20]
        uid, gid = os.getuid() or 1000, os.getgid() or 1000
        # root 只负责可信监督服务；pi 与生成的 C++ 分别降权到不同 UID。
        command = self.ex.docker + ["create", "--name", name, "--platform", self.image["platform"],
            "--network", "bridge", "--cpus", "2", "--memory", "2g", "--pids-limit", "256",
            "--read-only", "--cap-drop", "ALL", "--security-opt", "no-new-privileges",
            "--tmpfs", "/tmp:rw,exec,nosuid,nodev,size=512m,mode=1777", "--tmpfs", "/control:rw,nosuid,nodev,size=1m",
            "--tmpfs", "/private:rw,nosuid,nodev,size=1m,mode=700",
            "--tmpfs", f"/agent:rw,nosuid,nodev,size=1m,mode=700,uid={uid},gid={gid}",
            "--tmpfs", "/snapshots:rw,nosuid,nodev,size=128m,mode=755",
            "--tmpfs", "/workspace:rw,nosuid,nodev,size=1m,mode=755", "--workdir", "/workspace",
            "-e", f"QUALTOR_AGENT_UID={uid}", "-e", f"QUALTOR_AGENT_GID={gid}",
            "-e", "PYTHONDONTWRITEBYTECODE=1"]
        for target, size in sorted(AGENT_TMPFS.items()):
            command += ["--tmpfs", f"{target}:rw,noexec,nosuid,nodev,size={size},mode=700,uid={uid},gid={gid}"]
        for cap in ("CHOWN", "DAC_OVERRIDE", "FOWNER", "KILL", "SETUID", "SETGID"):
            command += ["--cap-add", cap]
        if scenario is None:
            command += ["-e", config["api_key_env"]]  # Docker 从宿主机环境取值，argv/日志不包含密钥。
        mounts = {"/pi": (AGENTS / "pi", True), "/framework": (GENERATOR / "runtime", True),
                  "/helpers/audit.py": (COMMON / "audit.py", True),
                  "/helpers/gtest_results.py": (SCORER / "gtest_results.py", True),
                  "/cmake": (SCORER / "cmake", True), "/input": (inputs, True), "/private/record": (record, False),
                  "/workspace/TASK.md": (record / "TASK.md", True)}
        for rel in public["visible_files"]:
            mounts["/workspace/project/" + rel] = (source_root(task) / rel, True)
        for target, (source, readonly) in sorted(mounts.items()):
            command += ["--mount", f"type=bind,source={source},target={target}" + (",readonly" if readonly else "")]
        command += [self.image["id"], "python3", "/framework/launch.py"]
        self.ex._call("generation-create", command, audit=audit)
        started = time.time()
        # inspect 的选择字段不含 Config.Env，避免 Docker 把传入的密钥写进审计。
        inspect_format = '{"State":{{json .State}},"Mounts":{{json .Mounts}},"HostConfig":{{json .HostConfig}},"Image":{{json .Image}}}'
        try:
            before = json.loads(self.ex._call("generation-inspect", self.ex.docker + ["inspect", "--format", inspect_format, name], audit=audit))
            actual = {m["Destination"]: m for m in before["Mounts"]}
            if (set(actual) != set(mounts) or any(actual[t]["RW"] == ro for t, (_, ro) in mounts.items())
                    or not set(AGENT_TMPFS) <= set(before["HostConfig"].get("Tmpfs") or {})
                    or not before["HostConfig"]["ReadonlyRootfs"] or before["HostConfig"]["NetworkMode"] != "bridge"):
                raise ValueError("生成容器挂载或隔离配置不正确")
            write_json(record / "container.json", before)
            execution = audit.run("generation-start", self.ex.docker + ["start", "--attach", name], timeout=None)
            after = json.loads(self.ex._call("generation-exit", self.ex.docker + ["inspect", "--format", "{{json .State}}", name], audit=audit))
            write_json(record / "container-exit.json", after)
        finally:
            self.ex._call("generation-remove", self.ex.docker + ["rm", "--force", name], audit=audit)
        if not (record / "generation.json").is_file():
            for phase in ("first", "final"):
                if not (record / phase / "manifest.json").exists():
                    shutil.copytree(record / "workspace/tests", record / phase / "tests", dirs_exist_ok=True)
                    freeze_product(record / phase)
            write_json(record / "generation.json", {"status": "agent_error", "started_at": started,
                       "ended_at": time.time(), "first_at": None, "build_calls": 0, "repair_rounds": 0,
                       "container_exit_code": after.get("ExitCode"), "docker_exit_code": execution["returncode"]})
        return read_json(record / "generation.json")


def score_frozen(executor, task, product, out, meta, cost_path, calibration):
    out = Path(out)
    if out.exists():
        raise ValueError(f"评分目录已存在，拒绝覆盖：{out}")
    for attempt in range(3):
        result = pipeline.score_product(executor, task, product, out, meta,
                    Audit(out.parent / "logs" / f"{out.name}-{attempt + 1}"), cost_path, calibration=calibration)
        if result["status"] != "infra_error" or attempt == 2:
            return result
        retained = out.parent / "infra-retries" / f"{out.name}-{attempt + 1}"
        retained.parent.mkdir(exist_ok=True)
        out.rename(retained)


def trial(executor, generator, task, config, trial_dir, index, agent_version, calibration, scenario=None, watchdog=900):
    trial_dir = Path(trial_dir)
    trial_dir.mkdir(parents=True, exist_ok=False)
    failures = []
    for attempt in range(1, 4):
        record = trial_dir / "generation-attempts" / f"attempt-{attempt}"
        plan = scenario(attempt) if callable(scenario) else scenario
        generation = generator.generate(task, config, record, plan, watchdog)
        cost = extract(record, priced=config.get("cost_per_million") is not None or scenario is not None)
        write_json(record / "cost.json", cost)
        if generation["status"] != "agent_error":
            break
        failures.append({"record": str(record.relative_to(REPO)), "cost": cost["final"]})
    successful = generation["status"] != "agent_error"
    # 原始尝试原位保留，审计中的宿主机路径始终可追溯；trial 根提供可用尝试的副本。
    if successful:
        for path in list(record.iterdir()):
            if path.is_dir():
                shutil.copytree(path, trial_dir / path.name)
            else:
                shutil.copy2(path, trial_dir / path.name)
    current = trial_dir if successful else record
    prior = [f["cost"] for f in failures[:(None if successful else -1)]]
    cost = {**cost, "first": add_costs(cost["first"], prior), "final": add_costs(cost["final"], prior),
            "generation_attempts": attempt, "includes_retry_cost": True}
    write_json(trial_dir / "cost.json", cost)
    result = {"task": task["id"], "set": task["set"], "trial": index, **generation,
              "generation_attempts": attempt, "failed_generations": failures, "cost": cost, "scores": {}}
    if successful:
        for phase in ("first", "final"):
            problem = validate_product(current / phase, task)
            if problem:
                result.setdefault("product_problems", {})[phase] = problem
            cost_path = trial_dir / f"cost-{phase}.json"
            write_json(cost_path, cost[phase])
            scored = score_frozen(executor, task, current / phase, trial_dir / "score" / scorer_version() / phase,
                                 {"agent_version": agent_version, "trial": index, "phase": phase,
                                  "cost_path": str(cost_path.relative_to(REPO))}, cost_path, calibration)
            result["scores"][phase] = {"status": scored["status"], "invalid_reason": scored["invalid_reason"],
                                       "metrics": scored["metrics"]}
    write_json(trial_dir / "trial.json", result)
    return result
