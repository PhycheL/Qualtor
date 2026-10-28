"""题库建设工具的公共函数：哈希、JSON、题目包骨架，以及变异复核结论的应用。只用标准库，兼容 Python 3.9。

题目包格式见 docs/评测模块与校准样本设计.md 第 3 节，建设流程见 docs/题库构建方案.md。
"""
import copy
import hashlib
import json
from pathlib import Path
import re
import shutil

REPO = Path(__file__).resolve().parents[2]
BENCHMARK = REPO / "benchmark"
MUTANT_REVIEW = Path(__file__).resolve().parent / "mutant_review"

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


def review_test_files(task_id):
    """复核补充测试：mutant_review/<题目 ID>/ 下的 .cc/.h，是变异复核中用来区分等价候选的反例。"""
    folder = MUTANT_REVIEW / task_id
    return sorted(p for p in folder.iterdir() if p.suffix in (".cc", ".h")) if folder.is_dir() else []


def review_note(task_id):
    """隐藏材料 README 中说明复核补充测试的一句话；没有补充测试时返回 None。"""
    names = [p.name for p in review_test_files(task_id)]
    if not names:
        return None
    return (f"复核补充测试：{'、'.join(f'`{n}`' for n in names)} 来自 `benchmark/tools/mutant_review/{task_id}/`，"
            "是变异复核中区分等价候选的反例，已并入参考测试与探针。")


def copy_reference_as_probe(task_dir, extra_files=()):
    """先把复核补充测试并入参考测试，再把参考测试复制进探针目录；生成型探针再追加 extra_files。"""
    ref = task_dir / HIDDEN["reference_tests"]
    for path in review_test_files(task_dir.name):
        if (ref / path.name).exists():
            raise ValueError(f"复核补充测试与已有参考测试同名：{path.name}")
        shutil.copyfile(path, ref / path.name)
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


NON_EQUIVALENT = "non_equivalent_verified"  # 真实 Mull 反例检出：计入分母
UNDEFINED_ONLY = "undefined_only"  # 只在未定义行为下与原代码不同（D015）：列为不稳定，不计入分母


def load_confirmed(task_id):
    """mutant_review/<题目 ID>/confirmed.json 中的复核结论；没有时返回空列表。"""
    path = MUTANT_REVIEW / task_id / "confirmed.json"
    return json.loads(path.read_text(encoding="utf-8"))["mutants"] if path.is_file() else []


def load_equivalent(task_id):
    """mutant_review/<题目 ID>/equivalent.json 中已有等价依据的候选：{变异 ID: 结论}。"""
    path = MUTANT_REVIEW / task_id / "equivalent.json"
    data = json.loads(path.read_text(encoding="utf-8"))["mutants"] if path.is_file() else []
    return {m["id"]: m for m in data}


def review_gaps(baseline, task_id):
    """准入前要补的复核：(没有结论的等价候选 ID, 结论标记了 pending、仍待补证据的 ID)。"""
    concluded = load_equivalent(task_id)
    open_ids = [m["id"] for m in baseline["equivalent"] if m["id"] not in concluded]
    pending = [m["id"] for m in baseline["equivalent"] if concluded.get(m["id"], {}).get("pending")]
    pending += [m["id"] for m in load_confirmed(task_id) if m.get("pending")]
    return open_ids, pending


def apply_confirmed(baseline, task_id):
    """把 confirmed.json 的复核结论落到分母上，并按 prepare_task.py 的口径重算参考强测试集的 M1。

    - non_equivalent_verified：探针区分不出、但真实 Mull 反例已证明不等价的变异，从等价候选移回分母；
    - undefined_only：只在未定义行为下才与原代码不同的变异（D015），从等价候选或分母移入不稳定，不计入分母。
    返回 (分母, 本次改动的 ID, 问题)；有问题时分母不变，没有改动时返回原对象。
    """
    confirmed = load_confirmed(task_id)
    ids = {m["id"] for m in baseline["mutants"]}
    missing = sorted(m["id"] for m in confirmed if m["id"] not in ids)
    unknown = sorted(m["id"] for m in confirmed if m["verdict"] not in (NON_EQUIVALENT, UNDEFINED_ONLY))
    if missing:
        return baseline, [], [f"复核结论的变异不在本次变异集合中，需人工核对：{missing}"]
    if unknown:
        return baseline, [], [f"复核结论的判定无法识别：{unknown}"]
    equivalent = {m["id"] for m in baseline["equivalent"]}
    unstable = {m["id"] for m in baseline["unstable"]}
    restore = [m for m in confirmed if m["verdict"] == NON_EQUIVALENT and m["id"] in equivalent]
    undefined = [m for m in confirmed if m["verdict"] == UNDEFINED_ONLY and m["id"] not in unstable]
    if not restore and not undefined:
        return baseline, [], []
    result = copy.deepcopy(baseline)
    changed = {m["id"] for m in restore} | {m["id"] for m in undefined}
    statuses = {m["id"]: m for m in result["mutants"]}
    result["equivalent"] = [m for m in result["equivalent"] if m["id"] not in changed]
    kept = [m for m in result.get("confirmed_non_equivalent", []) if m["id"] not in changed]
    result["confirmed_non_equivalent"] = kept + [
        {"id": m["id"], "verdict": m["verdict"], "evidence": m["evidence"],
         "reason": "探针未区分，复核已确认不等价，保留在分母中"} for m in sorted(restore, key=lambda m: m["id"])]
    if not result["confirmed_non_equivalent"]:
        del result["confirmed_non_equivalent"]
    result["unstable"] = result["unstable"] + [
        {"id": m["id"], "reference_status": statuses[m["id"]]["reference_status"],
         "probe_status": statuses[m["id"]]["probe_status"], "verdict": m["verdict"], "evidence": m["evidence"],
         "reason": "复核确认只在未定义行为下与原代码不同，结果取决于二进制与执行条件（D015），从分母中剔除"}
        for m in sorted(undefined, key=lambda m: m["id"])]
    excluded = {m["id"] for m in result["equivalent"]} | {m["id"] for m in result["unstable"]}
    counts = {"killed": 0, "timeout": 0, "total": 0}
    for mutant in result["mutants"]:
        if mutant["id"] in excluded:
            continue
        counts["total"] += 1
        status = mutant["reference_status"][0]
        if status in ("killed", "timeout"):
            counts[status] += 1
    denominator = counts["total"] - counts["timeout"]
    m1 = counts["killed"] / denominator if denominator else None
    threshold = result["reference"]["threshold"]
    result["reference"] = {**counts, "m1": m1, "threshold": threshold, "passes": m1 is not None and m1 >= threshold}
    return result, sorted(changed), []
