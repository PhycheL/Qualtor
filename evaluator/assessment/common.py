"""评测模块宿主机侧的公共函数：路径、哈希、题目包与产物校验、Mull 配置、校准状态。"""
import datetime as dt
import fnmatch
import hashlib
import json
from pathlib import Path
import re
import shutil
from build_contract import validate_build

HEADER_SUFFIXES = {".h", ".hh", ".hpp", ".hxx", ".inl"}

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "common"))
from paths import REPO, ASSESSMENT, COMMON, BENCHMARK, RUNS

CALIBRATION = ASSESSMENT / "calibration"
CALIBRATION_STATUS = ASSESSMENT / "calibration-status.json"
# 已准入题目清单（R-08）：正式比较只用登记过、且指纹与登记时一致的题目。由 benchmark/tools/admit.py 写入。
ADMISSION = BENCHMARK / "admission.json"

# 评测模块的行为由这些文件决定（assessment/ 下的代码、构建模板、版本号，以及共用脚本）；任何一个变化都要重新校准。
SHARED_FILES = ["audit.py", "coverage.py", "paths.py", "runs.py"]


def code_files():
    files = sorted(ASSESSMENT.glob("*.py")) + sorted((ASSESSMENT / "cmake").glob("*")) + [ASSESSMENT / "VERSION"]
    return [str(p.relative_to(ASSESSMENT)) for p in files if p.is_file()]


def now():
    return dt.datetime.now(dt.timezone.utc).isoformat()


def read_json(path):
    return json.loads(Path(path).read_text())


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2, sort_keys=False) + "\n")


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def sha256_text(text):
    return hashlib.sha256(text.encode()).hexdigest()


def assessment_version():
    return (ASSESSMENT / "VERSION").read_text().strip()


def assessment_code_sha256():
    """评测模块代码指纹：版本号相同但代码变了，校准结果也视为过期。"""
    lines = [f"{name}\0{sha256_file(ASSESSMENT / name)}" for name in code_files()]
    lines += [f"common/{name}\0{sha256_file(COMMON / name)}" for name in SHARED_FILES]
    return sha256_text("\n".join(lines))


def samples_sha256():
    """全部校准样本（含期望结果）的指纹：样本变化后，旧的校准结果失效。"""
    files = sorted(p for p in CALIBRATION.rglob("*") if p.is_file() and "__pycache__" not in p.parts)
    return sha256_text("\n".join(f"{p.relative_to(CALIBRATION)}\0{sha256_file(p)}" for p in files))


RUN_ID = re.compile(r"[a-zA-Z0-9][a-zA-Z0-9_-]{0,79}")


def check_run_id(run_id):
    if not RUN_ID.fullmatch(run_id):
        raise ValueError("run-id 只能包含字母、数字、-、_，以字母或数字开头且最多 80 字符")
    return run_id


def default_run_id(prefix):
    return f"{prefix}-" + dt.datetime.now(dt.timezone.utc).strftime("%Y%m%d-%H%M%S")


# ---- 题目包 ----

class TaskError(ValueError):
    pass


def load_task(task):
    """读取并校验题目包；task 可以是题目 ID 或目录路径。"""
    task_dir = Path(task)
    if not task_dir.is_dir():
        task_dir = BENCHMARK / str(task)
    path = task_dir / "task.json"
    if not path.is_file():
        raise TaskError(f"找不到题目包：{task}")
    data = read_json(path)
    data["_dir"] = task_dir.resolve()
    data["_sha256"] = sha256_file(path)
    validate_task(data)
    return data


def source_root(task):
    return (REPO / task["source"]["root"]).resolve()


def validate_task(task):
    for key in ("schema", "id", "set", "source", "target_sources", "include_dirs", "allowed_test_files",
                "params", "mull", "variants"):
        if key not in task:
            raise TaskError(f"task.json 缺少 {key}")
    if task["schema"] != 1 or task["set"] not in ("dev", "acceptance"):
        raise TaskError("task.json 的 schema 或 set 不正确")
    root = source_root(task)
    try:
        build = validate_build(task.get("build", {}), task["target_sources"],
                               task.get("visible", {}).get("files", []), root)
    except ValueError as error:
        raise TaskError(str(error)) from error
    for rel, digest in task["source"]["files"].items():
        path = root / rel
        if not path.is_file() or sha256_file(path) != digest:
            raise TaskError(f"被测源码缺失或哈希不一致：{rel}")
    for rel in task["target_sources"] + task["include_dirs"]:
        if not (root / rel).exists():
            raise TaskError(f"路径不存在：{rel}")
    for rel in task["target_sources"] + build["support_sources"]:
        if rel not in task["source"]["files"]:
            raise TaskError(f"被测源文件未登记哈希：{rel}")
    ids = set()
    for variant in task["variants"]:
        if variant["id"] in ids or not re.fullmatch(r"[a-z0-9-]+", variant["id"]):
            raise TaskError(f"替换版本 ID 重复或不合法：{variant['id']}")
        ids.add(variant["id"])
        if variant["kind"] not in ("real_bug", "equivalent", "handwritten") or variant["expect"] not in ("fail", "pass"):
            raise TaskError(f"替换版本类型或期望不正确：{variant['id']}")
        for rel, digest in variant["files"].items():
            visible = task.get("visible", {}).get("files", [])
            allowed = set(task["target_sources"]) | set(task.get("target_headers", []))
            allowed |= {p for p in visible if Path(p).suffix in HEADER_SUFFIXES}
            if rel in build["support_sources"] or rel not in visible or rel not in allowed:
                raise TaskError(f"替换版本 {variant['id']} 只能替换可见的被测源文件或头文件，不能替换依赖源文件：{rel}")
            if rel not in task["source"]["files"]:
                raise TaskError(f"替换文件未登记源码哈希：{rel}")
            path = variant_dir(task, variant) / rel
            if not path.is_file() or sha256_file(path) != digest:
                raise TaskError(f"替换版本文件缺失或哈希不一致：{variant['id']} {rel}")


def variant_dir(task, variant):
    return task["_dir"] / "hidden" / "variants" / variant["id"]


def checked_file(root, rel, digest):
    """复制前验证路径和内容；禁止通过目录别名或符号链接越出已登记源码树。"""
    path = Path(rel)
    if path.is_absolute() or ".." in path.parts or str(path) != rel:
        raise TaskError(f"不合法的源码路径：{rel}")
    current = Path(root)
    for part in path.parts:
        current /= part
        if current.is_symlink():
            raise TaskError(f"源码路径不能经过符号链接：{rel}")
    if not current.is_file() or sha256_file(current) != digest:
        raise TaskError(f"源码缺失或哈希不一致：{rel}")
    return current


def copy_variant_tree(task, variant, destination):
    """按登记清单复制整棵树并原位替换，使同目录引号包含也指向替换版本。"""
    destination = Path(destination)
    destination.mkdir(parents=True, exist_ok=False)
    hashes = dict(task["source"]["files"])
    for rel, digest in hashes.items():
        source = checked_file(source_root(task), rel, digest)
        target = destination / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, target)
        if sha256_file(target) != digest:
            raise TaskError(f"源码复制后哈希不一致：{rel}")
    for rel, digest in variant["files"].items():
        source = checked_file(variant_dir(task, variant), rel, digest)
        if rel not in hashes:
            raise TaskError(f"替换文件未登记：{rel}")
        shutil.copyfile(source, destination / rel)
        if sha256_file(destination / rel) != digest:
            raise TaskError(f"替换复制后哈希不一致：{rel}")
        hashes[rel] = digest
    return sha256_text("\n".join(f"{rel}\0{hashes[rel]}" for rel in sorted(hashes)))


def hidden_path(task, key):
    value = task.get("hidden", {}).get(key)
    return (task["_dir"] / value) if value else None


def load_baseline(task):
    path = hidden_path(task, "mutation_baseline")
    return read_json(path) if path and path.is_file() else None


def task_sha256(task):
    """题目指纹：task.json 与全部隐藏材料；变异分母只取实质内容，不含复核状态等元数据。"""
    hidden = task["_dir"] / "hidden"
    baseline_path = hidden_path(task, "mutation_baseline")
    parts = [f"task.json\0{task['_sha256']}"]
    for path in sorted(p for p in hidden.rglob("*") if p.is_file()):
        if baseline_path and path == baseline_path:
            continue
        parts.append(f"{path.relative_to(task['_dir'])}\0{sha256_file(path)}")
    baseline = load_baseline(task)
    if baseline:
        essence = {"mull": baseline.get("mull", {}).get("config_sha256"),
                   "mutants": sorted(m["id"] for m in baseline.get("mutants", [])),
                   "equivalent": sorted(m["id"] for m in baseline.get("equivalent", [])),
                   "unstable": sorted(m["id"] for m in baseline.get("unstable", []))}
        parts.append("baseline\0" + sha256_text(json.dumps(essence, sort_keys=True)))
    return sha256_text("\n".join(parts))


def mull_config_text(task, container_root="/repo"):
    """根据 task.json 生成实际使用的 Mull 配置；includePaths 只包含被测源文件。"""
    # 配置按全文冻结哈希，保留旧注释以兼容已有变异分母；模块改名不改变配置。
    lines = ["# 由评分器根据 task.json 生成；修改算子要升级变异分母。", "mutators:"]
    lines += [f"  - {name}" for name in task["mull"]["mutators"]]
    if task["mull"].get("ignore_mutators"):
        lines.append("ignoreMutators:")
        lines += [f"  - {name}" for name in task["mull"]["ignore_mutators"]]
    lines.append("includePaths:")
    lines += [f"  - '{re.escape(container_root + '/' + rel)}$'" for rel in task["target_sources"]]
    return "\n".join(lines) + "\n"


# ---- 产物 ----

def product_files(product):
    product = Path(product)
    return sorted(str(p.relative_to(product)) for p in product.rglob("*")
                  if p.is_file() and p.name != "manifest.json")


def validate_product(product, task):
    """核对冻结产物：清单、哈希、允许的文件、没有符号链接。返回问题描述，没有问题时返回 None。"""
    product = Path(product)
    manifest_path = product / "manifest.json"
    if not manifest_path.is_file():
        return "缺少 manifest.json"
    if any(p.is_symlink() for p in product.rglob("*")):
        return "产物中不允许符号链接"
    try:
        manifest = read_json(manifest_path)
        listed = manifest["files"]
    except (ValueError, KeyError, TypeError):
        return "manifest.json 格式不正确"
    actual = product_files(product)
    if sorted(listed) != actual:
        return f"manifest 与实际文件不一致：清单 {sorted(listed)}，实际 {actual}"
    for rel in actual:
        if not any(fnmatch.fnmatchcase(rel, pattern) for pattern in task["allowed_test_files"]):
            return f"不允许的文件：{rel}"
        if sha256_file(product / rel) != listed[rel]:
            return f"哈希不一致：{rel}"
    return None


def product_test_sources(product):
    return [rel for rel in product_files(product) if rel.endswith((".cc", ".cpp", ".cxx"))]


def freeze_product(product, frozen_at=None):
    """为产物目录写 manifest.json（冻结）。只用于准备产物，评分时只校验、不改写。"""
    product = Path(product)
    files = {rel: sha256_file(product / rel) for rel in product_files(product)}
    write_json(product / "manifest.json", {"files": files, "frozen_at": frozen_at or now()})
    return files


# ---- 校准状态 ----

def calibration_status(images, task=None):
    """返回当前评测模块代码、样本、镜像和全部校准题目对应的校准状态：passed、failed、stale 或 missing。

    task 只用来复用已加载的题目对象；无论查询哪道题，都核对校准记录中的每一道校准题。
    """
    if not CALIBRATION_STATUS.is_file():
        return {"status": "missing"}
    record = read_json(CALIBRATION_STATUS)
    # 校准结论依赖全部校准题的材料：任何一道校准题变化，所有题目的正式评测都不能再复用这次校准。
    for task_id, digest in sorted((record.get("tasks") or {}).items()):
        try:
            current = task if task is not None and task["id"] == task_id else load_task(task_id)
            changed = task_sha256(current) != digest
        except TaskError:
            changed = True
        if changed:
            return {"status": "stale", "run_id": record.get("run_id"), "reason": f"校准题目 {task_id} 的材料已变化"}
    current = {"scorer_version": assessment_version(), "scorer_code_sha256": assessment_code_sha256(),
               "samples_sha256": samples_sha256(),
               "images": {k: v["id"] for k, v in images.items()} if images else None}
    stale = (record.get("scorer_version") != current["scorer_version"]
             or record.get("scorer_code_sha256") != current["scorer_code_sha256"]
             or record.get("samples_sha256") != current["samples_sha256"]
             or (current["images"] is not None and record.get("images") != current["images"]))
    if stale:
        return {"status": "stale", "run_id": record.get("run_id")}
    return {"status": "passed" if record.get("passed") else "failed", "run_id": record.get("run_id"),
            "report": record.get("report")}


# ---- 准入（R-08） ----

def load_admission():
    """已准入题目清单：{题目 ID: 登记记录}；文件不存在时为空。"""
    return read_json(ADMISSION).get("tasks", {}) if ADMISSION.is_file() else {}


def admission_state(task_id, task_sha, admitted=None):
    """按登记时的题目指纹判断准入状态：admitted、stale（登记后材料或分母变化）或 not_admitted。"""
    record = (load_admission() if admitted is None else admitted).get(task_id)
    if record is None:
        return {"status": "not_admitted"}
    if task_sha is None or record.get("task_sha256") != task_sha:
        return {"status": "stale", "admitted_at": record.get("admitted_at"),
                "reason": "题目材料或变异分母在准入后发生变化（或结果未记录题目指纹），需重新准入"}
    return {"status": "admitted", "admitted_at": record.get("admitted_at"), "by": record.get("by")}


def admission_status(task):
    return admission_state(task["id"], task_sha256(task))
