"""评测接线：投影公开任务，通过产品 CLI 生成，再独立评分。"""
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
from concurrent.futures import CancelledError
from urllib.parse import urlsplit

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent / "assessment"), str(HERE.parent / "common"), str(HERE.parent / "toolchains")]
from paths import AGENTS, COMMON, GENERATOR, REPO, ASSESSMENT
from audit import Audit
from common import (freeze_product, now, read_json, assessment_version, sha256_file, sha256_text, source_root,
                    validate_product, write_json)
import pipeline
from cost import add_costs
from product_process import run_product


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
        dirs[:] = sorted(d for d in dirs if d not in (".git", "node_modules", "__pycache__", ".artifacts", ".cache", "output")
                         and (runtime or d != "dist"))
        for name in sorted(files):
            path = Path(directory) / name
            if name == ".qualtor-build.json" or name.startswith(".env") or path.suffix == ".pyc":
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
    if not set(task["target_sources"] + task.get("build", {}).get("support_sources", [])) <= set(visible):
        raise ValueError("被测和依赖源文件必须列入 visible.files")
    public = {"id": task["id"], "title": task["title"], "target_sources": task["target_sources"],
            "include_dirs": task["include_dirs"], "visible_files": visible,
            "allowed_test_files": task["allowed_test_files"], "budget": {"repair_rounds": budget},
            "test_timeout_seconds": task["params"]["test_timeout_seconds"], "source_root": str(root)}
    if "build" in task:
        public["build"] = task["build"]
    return public


def score_frozen(executor, task, product, out, meta, cost_path, calibration):
    out = Path(out)
    if out.exists():
        raise ValueError(f"评分目录已存在，拒绝覆盖：{out}")
    for attempt in range(3):
        result = pipeline.assess_product(executor, task, product, out, meta,
                    Audit(out.parent / "logs" / f"{out.name}-{attempt + 1}"), cost_path, calibration=calibration)
        if result["status"] != "infra_error" or attempt == 2:
            return result
        retained = out.parent / "infra-retries" / f"{out.name}-{attempt + 1}"
        retained.parent.mkdir(exist_ok=True)
        out.rename(retained)


def load_config(name, env_file=None):
    command = [sys.executable, str(AGENTS / "run.py"), "--describe", "--config", name]
    if env_file:
        command += ["--env-file", str(Path(env_file).resolve())]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode:
        raise ValueError(result.stderr.strip() or "产品配置检查失败")
    description = json.loads(result.stdout)
    if description.get("schema") != 1:
        raise ValueError("不支持的产品接口版本")
    config = dict(description["config"]["settings"], _name=name, _env_file=env_file)
    return config, dict(description["config"], product=description)


class GenerationExecutor:
    """只依赖产品 CLI 契约，不导入其工作区、预算或 pi 私有实现。"""
    def __init__(self, docker_executor, cancel=None):
        self.ex = docker_executor
        self.image = docker_executor.images["gcc"]
        self.cancel = cancel

    def generate(self, task, config, record, scenario=None, watchdog=900, attempts=3):
        record = Path(record)
        request = record.parent / (record.name + "-request")
        request.mkdir(parents=True, exist_ok=False)
        write_json(request / "task.json", public_task(task))
        command = [sys.executable, str(AGENTS / "run.py"), "--task", str(request / "task.json"),
                   "--output", str(record), "--config", config.get("_name", "default"),
                   "--watchdog", str(watchdog), "--attempts", str(attempts)]
        if config.get("_env_file"):
            command += ["--env-file", str(Path(config["_env_file"]).resolve())]
        if scenario is not None:
            plan = [scenario(i) for i in range(1, attempts + 1)] if callable(scenario) else scenario
            write_json(request / "scenario.json", plan)
            command += ["--scenario", str(request / "scenario.json")]
        execution = run_product(Audit(request / "logs"), command, self.cancel)
        if not (record / "result.json").is_file():
            if self.cancel is not None and self.cancel.is_set():
                raise CancelledError()
            raise RuntimeError(f"产品未产生结果，见 {execution['stderr_log']}")
        result = read_json(record / "result.json")
        if result.get("schema") != 1:
            raise ValueError("不支持的产品结果版本")
        if result.get("toolchain") and result["toolchain"]["id"] != self.image["id"]:
            raise ValueError("产品编译和评分 GCC 镜像不同，本轮不用于比较")
        if execution["returncode"] and result["status"] not in ("agent_error", "cancelled"):
            raise RuntimeError("产品入口异常退出")
        return result


def trial(executor, generator, task, config, trial_dir, index, agent_version, calibration, scenario=None, watchdog=900):
    trial_dir = Path(trial_dir)
    generation = generator.generate(task, config, trial_dir, scenario, watchdog)
    result = {**generation, "set": task["set"], "trial": index, "scores": {}}
    # 产品可能已正常结束，但调度在读取结果时收到取消；此时不再启动评分。
    if generator.cancel is not None and generator.cancel.is_set():
        result.update(status="cancelled", cancellation_signal=getattr(generator.cancel, "signum", None))
    if result["status"] not in ("agent_error", "cancelled"):
        for phase in ("first", "final"):
            problem = validate_product(trial_dir / phase, task)
            if problem:
                result.setdefault("product_problems", {})[phase] = problem
            cost_path = trial_dir / f"cost-{phase}.json"
            write_json(cost_path, generation["cost"][phase])
            scored = score_frozen(executor, task, trial_dir / phase, trial_dir / "score" / assessment_version() / phase,
                                 {"agent_version": agent_version, "trial": index, "phase": phase,
                                  "cost_path": str(cost_path.relative_to(REPO))}, cost_path, calibration)
            result["scores"][phase] = {"status": scored["status"], "invalid_reason": scored["invalid_reason"],
                                       "metrics": scored["metrics"]}
    write_json(trial_dir / "trial.json", result)
    return result


