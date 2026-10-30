#!/usr/bin/env python3
"""从题库数据生成文档引用的题库事实（只读，不写任何文件）。

数据来源：benchmark/*/task.json、source/SOURCE.json、hidden/mutation_baseline.json、
hidden/coverage_baseline.json、benchmark/admission.json、agents/toolchains/environments/*.json、
evaluator/assessment/calibration-status.json、calibration_report.json、calibration/*/CAL-*/expected.json；
“新题”指不在 evaluator/assessment/tests/fixtures/step_c_legacy_a273de2.json（a273de2 时的 115 题）中的题。
M1 适用的新题，参考 C1 取自分母标定运行 runs/<created_by_run>/prep/reference-*/result.json（仅本地证据，
缺失时输出 null）；纯头文件题取分母 reference.c1。

用法：python3 -I -B benchmark/tools/bank_facts.py [--format json|markdown]
"""
import argparse
from collections import Counter
import json
import os
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
BENCHMARK = REPO / "benchmark"
ASSESSMENT = REPO / "evaluator/assessment"
LEGACY = ASSESSMENT / "tests/fixtures/step_c_legacy_a273de2.json"
CODEGEN_TOOLS = ("moc", "protoc")


def read(path):
    return json.loads(Path(path).read_text(encoding="utf-8"))


def optional(path):
    return read(path) if Path(path).is_file() else None


def reference_c1(task, baseline):
    """纯头文件/零变异题取分母中的 reference.c1；其余取标定运行的参考测试结果（每轮一个值）。"""
    if not baseline:
        return None, None
    if (baseline.get("reference") or {}).get("c1") is not None:
        return [baseline["reference"]["c1"]], "hidden/mutation_baseline.json reference.c1"
    run = baseline.get("created_by_run")
    values = []
    prep = REPO / "runs" / str(run) / "prep"
    names = sorted(n for n in os.listdir(prep) if n.startswith("reference-")) if prep.is_dir() else []
    for path in (prep / n / "result.json" for n in names):
        if not path.is_file():
            continue
        metrics = read(path).get("metrics") or {}
        values.append(metrics.get("C1"))
    return (values or None), (f"runs/{run}/prep/reference-*/result.json metrics.C1" if values else None)


def collect():
    legacy = set(read(LEGACY)["tasks"])
    admission = read(BENCHMARK / "admission.json")["tasks"]
    tasks = {}
    for path in sorted(BENCHMARK / name / "task.json" for name in os.listdir(BENCHMARK)):
        if not path.is_file():
            continue
        task = read(path)
        task["_dir"] = path.parent
        tasks[task["id"]] = task
    tiers = Counter(task.get("tier", "easy") for task in tasks.values())
    untiered = sorted(t for t, task in tasks.items() if "tier" not in task)

    libraries, boost, codegen, generated, defines, support = {}, [], {t: [] for t in CODEGEN_TOOLS}, [], [], []
    header_only, zero_mutants, real_bug, equivalent, environments = [], [], [], [], Counter()
    for tid, task in tasks.items():
        build = task.get("build", {})
        if build.get("environment"):
            environments[build["environment"]] += 1
        for target in build.get("link_libraries", []):
            libraries.setdefault(target, []).append(tid)
        if "Boost::headers" in build.get("link_libraries", []):
            boost.append(tid)
        for entry in build.get("codegen", []):
            codegen[entry["tool"]].append(tid)
        source = optional(task["_dir"] / "source/SOURCE.json") or {}
        if source.get("generated"):
            generated.append(tid)
        if build.get("defines"):
            defines.append(tid)
        if build.get("support_sources"):
            support.append(tid)
        if task.get("target_headers"):
            header_only.append(tid)
        baseline = optional(task["_dir"] / task.get("hidden", {}).get("mutation_baseline", "hidden/none"))
        if (baseline or {}).get("mutation", {}).get("reason") == "zero_mutants":
            zero_mutants.append(tid)
        kinds = {v["kind"] for v in task.get("variants", [])}
        if "real_bug" in kinds:
            real_bug.append(tid)
        if "equivalent" in kinds:
            equivalent.append(tid)
    # “链接第三方库”按导入目标统计；Boost::headers 只用头文件，单独计数。protobuf 与 protobuf-lite 合并为 protobuf。
    families = {"OpenSSL::Crypto": "OpenSSL", "ZLIB::ZLIB": "zlib", "protobuf::libprotobuf": "protobuf",
                "protobuf::libprotobuf-lite": "protobuf", "Qt5::Core": "Qt"}
    linked = {}
    for target, ids in libraries.items():
        if target in families:
            linked.setdefault(families[target], set()).update(ids)
    linking_tasks = sorted(set().union(*linked.values())) if linked else []

    new = {}
    for tid in sorted(set(tasks) - legacy):
        task = tasks[tid]
        baseline = optional(task["_dir"] / task["hidden"]["mutation_baseline"]) or {}
        reference = baseline.get("reference", {})
        c1, c1_source = reference_c1(task, baseline)
        new[tid] = {
            "tier": task.get("tier", "easy"), "environment": task.get("build", {}).get("environment"),
            "link_libraries": task.get("build", {}).get("link_libraries", []),
            "codegen": [e["tool"] for e in task.get("build", {}).get("codegen", [])],
            "pregenerated_headers": sorted(t for r in (optional(task["_dir"] / "source/SOURCE.json") or {}).get("generated", [])
                                           for t in r.get("output_paths", {}).values()),
            "target_headers": bool(task.get("target_headers")),
            "variants": Counter(v["kind"] for v in task.get("variants", [])),
            "mutation_applicable": baseline.get("mutation", {}).get("applicable", True),
            "not_applicable_reason": baseline.get("mutation", {}).get("reason"),
            "mutants_reported": len(baseline.get("mutants", [])),
            "equivalent": len(baseline.get("equivalent", [])),
            "unstable": len(baseline.get("unstable", [])),
            "denominator": reference.get("total"), "reference_killed": reference.get("killed"),
            "reference_timeout": reference.get("timeout"), "probe_timeout_review": len(baseline.get("review_needed", [])),
            "reference_m1": reference.get("m1"), "reference_c1": c1, "reference_c1_source": c1_source,
            "params_mull_test_timeout_ms": task["params"].get("mull_test_timeout_ms"),
            "admitted_by": (admission.get(tid) or {}).get("by"),
        }

    status = optional(ASSESSMENT / "calibration-status.json") or {}
    report = optional(ASSESSMENT / "calibration_report.json") or {}
    calibration = {}
    calibration_root = ASSESSMENT / "calibration"
    candidates = [calibration_root / task_dir / sample / "expected.json"
                  for task_dir in os.listdir(calibration_root) if (calibration_root / task_dir).is_dir()
                  for sample in os.listdir(calibration_root / task_dir) if sample.startswith("CAL-")]
    for expected_path in sorted(p for p in candidates if p.is_file()):
        sid = expected_path.parent.name
        number = int(sid.split("-")[1])
        if not 30 <= number <= 35:
            continue
        expected = read(expected_path)
        measured = (report.get("samples") or {}).get(sid, {})
        calibration[sid] = {
            "task": expected_path.parent.parent.name, "description": expected.get("description"),
            "expected": {"hard": expected.get("hard"), "relations": expected.get("relations"),
                         "environment": "environment" in expected, "build_boundary": expected.get("build_boundary", False)},
            "measured": {"status": measured.get("status"), "passed": measured.get("passed"),
                         "metrics": measured.get("metrics"), "not_applicable": measured.get("not_applicable")},
        }
    recipes = {}
    for path in sorted((REPO / "agents/toolchains/environments").glob("*.json")):
        recipe = read(path)
        recipes[recipe["name"]] = {"packages": recipe["packages"], "libraries": recipe["libraries"],
                                   "generators": recipe["generators"], "snapshot": recipe["snapshot"]}
    signers = Counter(record.get("by") for record in admission.values())
    return {
        "total_tasks": len(tasks), "legacy_tasks": len(legacy & set(tasks)), "new_tasks": len(new),
        "tiers": dict(sorted(tiers.items())), "tier_note": "没有 tier 字段的题计为 easy", "untiered_tasks": untiered,
        "capabilities": {
            "linking_tasks": {"count": len(linking_tasks), "tasks": linking_tasks,
                              "by_library": {k: sorted(v) for k, v in sorted(linked.items())}},
            "boost_header_tasks": sorted(boost),
            "codegen_tasks": {"count": len({t for ids in codegen.values() for t in ids}),
                              "by_tool": {k: sorted(v) for k, v in codegen.items()}},
            "pregenerated_header_tasks": sorted(generated),
            "define_tasks": sorted(defines), "support_source_tasks": sorted(support),
            "header_only_tasks": sorted(header_only), "zero_mutant_tasks": sorted(zero_mutants),
            "real_bug_tasks": sorted(real_bug), "equivalent_version_tasks": sorted(equivalent),
            "environment_tasks": dict(environments),
        },
        "new_tasks_detail": {k: {**v, "variants": dict(v["variants"])} for k, v in new.items()},
        "calibration": {"run_id": status.get("run_id"), "scorer_version": status.get("scorer_version"),
                        "passed": status.get("passed"), "rounds": report.get("rounds"),
                        "tasks": sorted((status.get("tasks") or {})), "samples": calibration},
        "recipes": recipes,
        "admission": {"signers": dict(signers),
                      "new_task_signers": dict(Counter(v["admitted_by"] for v in new.values()))},
    }


def fmt(value):
    if value is None:
        return "—"
    if isinstance(value, float):
        return f"{value:.4f}".rstrip("0").rstrip(".")
    if isinstance(value, list):
        return " / ".join(fmt(v) for v in value)
    return str(value)


def relation(item):
    if item["op"] == "na":
        return f"{item['metric']} 不适用（{item.get('reason')}）"
    return f"{item['metric']} {item['op']} {item['ref'] if 'ref' in item else fmt(item.get('value'))}"


def markdown(facts):
    caps = facts["capabilities"]
    lines = [f"# 题库事实（{facts['total_tasks']} 题；a273de2 旧题 {facts['legacy_tasks']}，新题 {facts['new_tasks']}）", "",
             "层级（" + facts["tier_note"] + "）：" + "、".join(f"{k} {v}" for k, v in facts["tiers"].items()), "",
             f"- 链接第三方库（不含 Boost::headers）：{caps['linking_tasks']['count']} 道；"
             + "，".join(f"{k} {len(v)}" for k, v in caps["linking_tasks"]["by_library"].items()),
             f"- Boost 头文件题：{len(caps['boost_header_tasks'])} 道（{', '.join(caps['boost_header_tasks'])}）",
             f"- 代码生成：{caps['codegen_tasks']['count']} 道；"
             + "，".join(f"{k} {len(v)}" for k, v in caps["codegen_tasks"]["by_tool"].items()),
             f"- 预生成配置头题：{len(caps['pregenerated_header_tasks'])} 道（{', '.join(caps['pregenerated_header_tasks'])}）"]
    for key, label in (("define_tasks", "宏题"), ("support_source_tasks", "依赖源文件题"), ("header_only_tasks", "纯头文件题"),
                       ("zero_mutant_tasks", "零变异题"), ("real_bug_tasks", "真实缺陷题"),
                       ("equivalent_version_tasks", "等价版本题")):
        lines.append(f"- {label}：{len(caps[key])} 道")
    lines += ["", "| 新题 | 层级 | 库 | 生成器 | 变异报告 | 等价 | 不稳定 | 分母 | 参考检出 | 参考超时 | 参考 M1 | 参考 C1 | 签署人 |",
              "|---|---|---|---|---|---|---|---|---|---|---|---|---|"]
    for tid, info in facts["new_tasks_detail"].items():
        denominator = info["denominator"] if info["mutation_applicable"] else f"不适用（{info['not_applicable_reason']}）"
        lines.append(f"| {tid} | {info['tier']} | {', '.join(info['link_libraries'])} | {', '.join(info['codegen']) or '—'} | "
                     f"{info['mutants_reported']} | {info['equivalent']} | {info['unstable']} | {denominator} | "
                     f"{fmt(info['reference_killed'])} | {fmt(info['reference_timeout'])} | {fmt(info['reference_m1'])} | "
                     f"{fmt(info['reference_c1'])} | {info['admitted_by']} |")
    lines += ["", f"校准 {facts['calibration']['run_id']}（{facts['calibration']['scorer_version']}，"
              f"passed={facts['calibration']['passed']}，{facts['calibration']['rounds']} 轮）",
              "", "| 样本 | 题目 | 期望 | 实测 M1_e2e | M1_valid | C1 | C2 | M2 | 不适用 |", "|---|---|---|---|---|---|---|---|---|"]
    for sid, sample in facts["calibration"]["samples"].items():
        expected = sample["expected"]
        text = "；".join([", ".join(f"{k}={v}" for k, v in (expected["hard"] or {}).items())]
                        + [relation(r) for r in expected["relations"] or []]
                        + (["环境一致"] if expected["environment"] else []) + (["构建边界"] if expected["build_boundary"] else []))
        metrics = sample["measured"]["metrics"] or {}
        lines.append(f"| {sid} | {sample['task']} | {text} | {fmt(metrics.get('M1_e2e'))} | {fmt(metrics.get('M1_valid'))} | "
                     f"{fmt(metrics.get('C1'))} | {fmt(metrics.get('C2'))} | {fmt(metrics.get('M2'))} | "
                     f"{fmt(json.dumps(sample['measured']['not_applicable'], ensure_ascii=False))} |")
    for name, recipe in facts["recipes"].items():
        lines += ["", f"配方 {name}（快照 {recipe['snapshot']}）：" + "、".join(f"`{k}={v}`" for k, v in recipe["packages"].items()),
                  "导入目标：" + "、".join(recipe["libraries"]) + "；生成器：" + "、".join(recipe["generators"])]
    lines += ["", "准入签署人：" + "；".join(f"{k} {v} 道" for k, v in facts["admission"]["signers"].items())]
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--format", choices=["json", "markdown"], default="markdown")
    args = parser.parse_args()
    facts = collect()
    print(json.dumps(facts, ensure_ascii=False, indent=2) if args.format == "json" else markdown(facts), end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
