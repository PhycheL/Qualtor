"""题库建设工具的公共函数：哈希、JSON 和题目包骨架。只用标准库，兼容 Python 3.9。

题目包格式见 docs/评测模块与校准样本设计.md 第 3 节，建设流程见 docs/题库构建方案.md。
"""
import hashlib
import json
from pathlib import Path
import re
import shutil

REPO = Path(__file__).resolve().parents[2]
BENCHMARK = REPO / "benchmark"

DEFAULT_PARAMS = {"stability_repeats": 10, "shuffle_seeds": [1, 2, 3], "test_timeout_seconds": 5,
                  "mull_minimum_timeout_ms": 3000, "reference_min_m1": 0.8}

HIDDEN = {"mutation_baseline": "hidden/mutation_baseline.json",
          "reference_tests": "hidden/reference_tests",
          "equivalence_probe": "hidden/equivalence_probe/tests"}

PROBE_MODES = {
    "generated": "探针由生成器在原代码上运行大量输入得到，并包含全部参考测试；探针也区分不出的变异列为等价候选。",
    "reference_copy": "探针即参考测试的副本：等价候选就是参考测试未杀死的变异，变异分母为参考测试可检出的变异，"
                      "人工复核时把不等价的变异移回分母。",
}


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def write_json(path, data):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def write_text(path, text):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def copy_file(src, dst):
    dst = Path(dst)
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(src, dst)


def identifier(text, limit=60):
    """把任意描述变成 GoogleTest 可用的标识符片段。"""
    word = re.sub(r"[^0-9A-Za-z]+", "_", text).strip("_")
    return (word[:limit].rstrip("_") or "case")


def camel(slug):
    return "".join(part[:1].upper() + part[1:] for part in re.split(r"[-_\s]+", slug) if part)


_CAPTURED = {}


def material_fingerprint(task_dir):
    """题目材料指纹：除变异分母外的全部文件。分母由 Docker 标定产生，不属于建题工具的输出。"""
    digest = hashlib.sha256()
    for path in sorted(p for p in Path(task_dir).rglob("*") if p.is_file() and p.name != "mutation_baseline.json"):
        digest.update(str(path.relative_to(task_dir)).encode() + b"\0" + path.read_bytes())
    return digest.hexdigest()


def reset_task_dir(task_id, force):
    """清空题目目录准备重建；已有的变异分母先记下，write_task 结束时若材料没变再放回。"""
    task_dir = BENCHMARK / task_id
    if task_dir.exists():
        if not force:
            raise SystemExit(f"{task_dir} 已存在；确认重建时加 --force")
        baseline = task_dir / HIDDEN["mutation_baseline"]
        if baseline.is_file():
            _CAPTURED[task_id] = (material_fingerprint(task_dir), baseline.read_bytes())
        shutil.rmtree(task_dir)
    (task_dir / "source").mkdir(parents=True)
    return task_dir


def restore_baseline(task_dir, task_id):
    captured = _CAPTURED.pop(task_id, None)
    if captured is None:
        return None
    fingerprint, data = captured
    if material_fingerprint(task_dir) == fingerprint:
        (task_dir / HIDDEN["mutation_baseline"]).write_bytes(data)
        return "保留原有变异分母（材料未变）"
    print(f"{task_id}：题目材料已变化，原有变异分母作废，需重新标定", flush=True)
    return "材料已变化，需重新标定"


def copy_reference_as_probe(task_dir, extra_files=()):
    """把参考测试复制进探针目录；生成型探针再追加 extra_files。"""
    ref = task_dir / HIDDEN["reference_tests"]
    probe = task_dir / HIDDEN["equivalence_probe"]
    probe.mkdir(parents=True, exist_ok=True)
    for path in sorted(ref.iterdir()):
        if path.is_file() and path.suffix in (".cc", ".h"):
            shutil.copyfile(path, probe / path.name)
    for path in extra_files:
        shutil.copyfile(path, probe / Path(path).name)


def write_task(task_dir, *, task_id, tier, tags, title, description, provenance, source_files, target_sources,
               include_dirs, visible_files, existing_tests, scoring_domain, probe_mode, generated_by, variants=()):
    """写 task.json 与 source/SOURCE.json。source_files 是相对 source/ 的全部入库文件。"""
    if probe_mode not in PROBE_MODES:
        raise ValueError(f"未知探针模式：{probe_mode}")
    root = task_dir / "source"
    missing = [rel for rel in source_files if not (root / rel).is_file()]
    if missing:
        raise ValueError(f"源码文件缺失：{missing}")
    if not set(target_sources) <= set(visible_files) <= set(source_files):
        raise ValueError("被测文件必须可见，可见文件必须入库")
    write_json(root / "SOURCE.json", {**provenance, "files": {rel: sha256_file(root / rel)
                                                             for rel in sorted(source_files)}})
    task = {
        "schema": 1,
        "id": task_id,
        "set": "dev",
        "tier": tier,
        "tags": list(tags),
        "title": title,
        "description": description,
        "source": {"repository": provenance["repository"], "commit": provenance["commit"],
                   "root": f"benchmark/{task_id}/source",
                   "files": {rel: sha256_file(root / rel) for rel in sorted(visible_files)}},
        "target_sources": list(target_sources),
        "include_dirs": list(include_dirs),
        "visible": {"files": list(visible_files), "notes": "可见材料只有被测源码、头文件和构建方式（C++11 + GoogleTest 1.12.1）。"},
        "allowed_test_files": ["tests/*.cc", "tests/*.h"],
        "existing_tests": existing_tests,
        "budget": {"tokens": None, "seconds": None, "repair_rounds": 3,
                   "note": "只限制修复轮次；token 与时间记录但不设上限（D005）"},
        "scoring_domain": scoring_domain,
        "params": dict(DEFAULT_PARAMS),
        "mull": {"mutators": ["cxx_all"]},
        "hidden": dict(HIDDEN),
        "preparation": {"probe_mode": probe_mode, "probe_note": PROBE_MODES[probe_mode],
                        "generated_by": generated_by, "review": "参考测试与探针为工具生成或机械转换，尚未人工审阅"},
        "variants": list(variants),
    }
    write_json(task_dir / "task.json", task)
    restore_baseline(task_dir, task_id)
    return task
