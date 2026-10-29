#!/usr/bin/env python3
"""题目准备：标定变异分母，并做准入检查。

用法（在装有 Docker 和两个工具链镜像的机器上，从项目根目录执行）：
    python3 evaluator/assessment/prepare_task.py baseline --task gildedrose-update-quality
    python3 evaluator/assessment/prepare_task.py baseline --task gildedrose-update-quality --write

做法：用参考强测试集和有界穷举探针各评分 --repeats 次（准备模式：记录 Mull 原始结果，不比对分母）。
- 各次结果不一致、或参考测试检出而探针（包含全部参考测试）未检出的变异列为“不稳定”，从分母中剔除；
- 探针也区分不出（幸存或未覆盖）的变异列为“等价变异候选”，从分母中剔除，复核状态为 pending；
- 用剩余分母计算参考强测试集的 M1，并检查替换版本：应失败的被检出、等价版本无误报。
草稿写到运行目录；加 --write 才写入题目的 hidden/mutation_baseline.json。人工复核后把 review.status 改为 reviewed。
"""
import argparse
from pathlib import Path
import shutil
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "common"))

from audit import Audit  # noqa: E402
from runs import finish, new_manifest, write_manifest  # noqa: E402
from common import (REPO, RUNS, check_run_id, default_run_id, freeze_product, hidden_path,  # noqa: E402
                    load_task, mull_config_text, now, assessment_code_sha256, assessment_version, write_json)
from coverage import freeze_headers, frozen_header_coverage, merge_header_stats
import judge  # noqa: E402
import pipeline  # noqa: E402


def make_product(source_dir, product, instantiation=None):
    (product / "tests").mkdir(parents=True)
    for path in sorted(Path(source_dir).iterdir()):
        if path.is_file() and path.suffix in (".cc", ".h"):
            shutil.copy2(path, product / "tests" / path.name)
    if instantiation and instantiation.is_dir():
        for path in sorted(instantiation.glob("*.cc")):
            target = product / "tests" / ("coverage_instantiation_" + path.name)
            if target.exists():
                raise ValueError(f"实例化文件与参考测试重名：{target}")
            shutil.copy2(path, target)
    freeze_product(product)
    return product


def suite_problems(name, result):
    problems = []
    if result["status"] != judge.SCORED:
        problems.append(f"{name}: 状态 {result['status']} {result.get('invalid_reason') or ''} {result.get('infra_detail') or ''}")
    bad = {t: s for t, s in (result.get("tests") or {}).items() if s != judge.VALID}
    if bad:
        problems.append(f"{name}: 存在无效或不稳定的测试 {bad}")
    return problems


def build_baseline(task, runs, config_text, images, run_id):
    """runs: {"reference": [result, ...], "probe": [result, ...]}。"""
    reasons = {(r.get("not_applicable") or {}).get("M1") for rs in runs.values() for r in rs}
    if reasons != {None}:
        if len(reasons) != 1 or None in reasons:
            raise ValueError("各次运行的 M1 适用性不一致")
        reason = reasons.pop()
        refs = runs["reference"]
        c1s = [r["metrics"]["C1"] for r in refs]
        threshold = task["params"].get("reference_min_c1", 0.8)
        variants = refs[0].get("variants", [])
        handwritten = [v for v in variants if v["kind"] == "handwritten" and v["expect"] == "fail"]
        return {"task": task["id"], "created_at": now(), "created_by_run": run_id,
                "scorer_version": assessment_version(), "scorer_code_sha256": assessment_code_sha256(),
                "images": {k:v["id"] for k,v in images.items()},
                "mutation": {"applicable": False, "reason": reason},
                "mutants": [], "equivalent": [], "unstable": [], "review_needed": [],
                "review": {"status":"pending", "by":None, "at":None, "note":"核对参考覆盖率与替换版本检出"},
                "zero_mutants_evidence": [r["zero_mutants_evidence"] for r in refs] if reason == "zero_mutants" else [],
                "reference": {"m1":None, "c1":min(c1s) if all(c is not None for c in c1s) else None,
                              "threshold":threshold, "valid_stable": all(not suite_problems('reference', r) for r in refs),
                              "handwritten":len(handwritten),
                              "handwritten_detected":sum(v["outcome"] == "detected" for v in handwritten),
                              "variants": [{k:v[k] for k in ('id','kind','expect','outcome','failed_tests')} for v in variants],
                              "passes": all(c is not None and c >= threshold for c in c1s)}}
    ids = None
    statuses = {"reference": {}, "probe": {}}
    meta = {}
    for suite, results in runs.items():
        for result in results:
            raw = {m["id"]: m for m in result.get("raw_mutants") or []}
            if ids is None:
                ids = set(raw)
            elif set(raw) != ids:
                raise SystemExit("各次 Mull 运行生成的变异集合不一致，不能标定分母")
            for mid, mutant in raw.items():
                statuses[suite].setdefault(mid, []).append(judge.mull_status(mutant["status"]))
                meta[mid] = {"mutator": mutant["mutator"], "location": mutant["location"]}
    mutants, equivalent, unstable, review = [], [], [], []
    for mid in sorted(ids or []):
        ref, probe = statuses["reference"][mid], statuses["probe"][mid]
        mutants.append({"id": mid, **meta[mid], "reference_status": ref, "probe_status": probe})
        if len(set(ref)) > 1 or len(set(probe)) > 1:
            unstable.append({"id": mid, "reference_status": ref, "probe_status": probe,
                             "reason": "多次运行结果不一致（可能是未定义行为导致的偶然崩溃），从分母中剔除"})
        elif ref[0] == "killed" and probe[0] in ("survived", "not_covered"):
            # 探针包含全部参考测试：参考测试检出而探针没有，说明结果取决于二进制，多为未定义行为（D015）。
            unstable.append({"id": mid, "reference_status": ref, "probe_status": probe,
                             "reason": "参考测试检出而探针未检出，结果取决于二进制（多为未定义行为），从分母中剔除"})
        elif probe[0] in ("survived", "not_covered"):
            equivalent.append({"id": mid, "method": "bounded_probe",
                               "reason": "在有界穷举探针下未被区分：可能是等价变异，也可能是引入了未表现出来的未定义行为；需人工复核"})
        elif probe[0] in ("timeout", "other"):
            review.append({"id": mid, "reason": f"探针结果为 {probe[0]}，保留在分母中，请人工确认"})
    excluded = {m["id"] for m in equivalent} | {m["id"] for m in unstable}
    counts = {"killed": 0, "timeout": 0, "total": 0}
    for mid in sorted(ids or []):
        if mid in excluded:
            continue
        counts["total"] += 1
        status = statuses["reference"][mid][0]
        if status == "killed":
            counts["killed"] += 1
        elif status == "timeout":
            counts["timeout"] += 1
    denominator = counts["total"] - counts["timeout"]
    reference_m1 = counts["killed"] / denominator if denominator else None
    threshold = task["params"]["reference_min_m1"]
    return {
        "task": task["id"], "created_at": now(), "created_by_run": run_id,
        "scorer_version": assessment_version(), "scorer_code_sha256": assessment_code_sha256(),
        "images": {k: v["id"] for k, v in images.items()},
        "mull": {"config_sha256": runs["reference"][0].get("mull_config_sha256"), "config": config_text},
        "mutants": mutants, "equivalent": equivalent, "unstable": unstable, "review_needed": review,
        "review": {"status": "pending", "by": None, "at": None,
                   "note": "等价变异候选由有界穷举探针自动给出；人工逐个复核后，把 status 改为 reviewed 并填写 by、at"},
        "reference": {**counts, "m1": reference_m1, "threshold": threshold,
                      "passes": reference_m1 is not None and reference_m1 >= threshold},
    }


def admission(task, runs):
    """替换版本准入：参考强测试集应检出“应失败”的版本、在等价版本上无误报；探针同样检查。"""
    problems = []
    for suite, results in runs.items():
        for result in results:
            actual = {v["id"] for v in result.get("variants") or []}
            if actual != {v["id"] for v in task["variants"]}:
                problems.append(f"{suite} 替换版本结果不完整")
            for variant in result.get("variants") or []:
                expected = "detected" if variant["expect"] == "fail" else "clean"
                if variant["outcome"] != expected:
                    problems.append(f"{suite} 在 {variant['id']} 上为 {variant['outcome']}，应为 {expected}")
    if any((r.get("not_applicable") or {}).get("M1") for r in runs["reference"]):
        count = sum(v["kind"] == "handwritten" and v["expect"] == "fail" for v in task["variants"])
        minimum = handwritten_minimum(task)
        if count < minimum:
            problems.append(f"M1 不适用的题需要至少 {minimum} 个手写变异，实际 {count}")
    return sorted(set(problems))


def handwritten_minimum(task):
    small = {"exercism-leap", "exercism-two-fer", "exercism-hello-world", "exercism-reverse-string"}
    if task["id"] in small:
        from common import source_root
        paths = task["target_sources"] + task.get("target_headers", [])
        lines = [line.strip() for rel in paths for line in (source_root(task) / rel).read_text().splitlines()]
        effective = [line for line in lines if line and not line.startswith(("//", "/*", "*", "#"))]
        if len(effective) <= 30:
            return 3
    return 5


def coverage_baseline(task, references, run_id):
    files = {}
    for rel in task["target_headers"]:
        records = [(r.get("counts", {}).get("coverage") or {}).get("files", {}).get(rel, {}) for r in references]
        files[rel] = merge_header_stats(records)
    frozen = freeze_headers(files, {rel:task["source"]["files"][rel] for rel in task["target_headers"]})
    frozen.update(created_at=now(), created_by_run=run_id)
    for result in references:
        # 准入的参考 C1 也按刚冻结的集合计算。
        raw = result["counts"]["coverage"]
        counts = frozen_header_coverage(raw["files"], frozen)
        for metric, field in (("C1", "lines"), ("C3", "functions")):
            c = counts["total"][field]
            result["metrics"][metric] = c["covered"] / c["total"] if c["total"] else None
    return frozen


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    baseline = sub.add_parser("baseline", help="标定变异分母并做准入检查")
    baseline.add_argument("--task", default="gildedrose-update-quality")
    baseline.add_argument("--run-id", default=default_run_id("prepare"))
    baseline.add_argument("--repeats", type=int, default=2)
    baseline.add_argument("--write", action="store_true", help="写入题目的 hidden/mutation_baseline.json")
    baseline.add_argument("--force", action="store_true", help="允许覆盖已有的变异分母")
    args = parser.parse_args()
    check_run_id(args.run_id)
    run_dir, evidence = RUNS / args.run_id, RUNS / args.run_id / "evidence"
    if run_dir.exists() or evidence.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    evidence.mkdir(parents=True)
    manifest = new_manifest(args.run_id, "prepare", task=args.task)
    write_manifest(run_dir, manifest)
    try:
        code, passed = run_prepare(args, run_dir, evidence, parser)
    except BaseException as error:
        finish(run_dir, manifest, "failed", error=str(error))
        raise
    finish(run_dir, manifest, "completed", passed=passed)
    return code


def run_prepare(args, run_dir, evidence, parser):
    from docker_runner import DockerExecutor
    task = load_task(args.task)
    target = hidden_path(task, "mutation_baseline")
    if args.write and target.exists() and not args.force:
        parser.error(f"{target} 已存在；确认要重新标定时加 --force")
    executor = DockerExecutor(Audit(evidence / "host"), evidence, args.run_id)
    products = {"reference": make_product(hidden_path(task, "reference_tests"), run_dir / "products" / "reference",
                                         hidden_path(task, "coverage_instantiation"))}
    probe = hidden_path(task, "equivalence_probe")
    if probe and probe.is_dir() and not task.get("target_headers"):
        products["probe"] = make_product(probe, run_dir / "products" / "probe")
    runs, problems = {"reference": []}, []
    for index in range(1, args.repeats + 1):
        for suite, product in products.items():
            if suite == "probe" and runs["reference"][-1].get("not_applicable", {}).get("M1"):
                continue
            print(f"准备模式评分：{suite} 第 {index} 次", flush=True)
            out = run_dir / "prep" / f"{suite}-{index}"
            result = pipeline.assess_product(executor, task, product, out, {"prep_suite": suite, "round": index},
                                            Audit(out.parent / f"{suite}-{index}-host"), prep=True,
                                            calibration={"status": "not_required_for_prep"})
            runs.setdefault(suite, []).append(result)
            problems += suite_problems(f"{suite} 第 {index} 次", result)
    if problems:
        write_json(run_dir / "prepare_report.json", {"passed": False, "problems": problems})
        print("\n".join(problems))
        return 1, False
    frozen = coverage_baseline(task, runs["reference"], args.run_id) if task.get("target_headers") else None
    if frozen:
        write_json(run_dir / "coverage_baseline.json", frozen)
    if not runs["reference"][0].get("not_applicable", {}).get("M1") and not runs.get("probe"):
        raise ValueError("M1 适用的题必须提供等价探针")
    config_text = mull_config_text(task)
    draft = build_baseline(task, runs, config_text, executor.images, args.run_id)
    problems += admission(task, runs)
    if not draft["reference"]["passes"]:
        metric = "c1" if "mutation" in draft else "m1"
        problems.append(f"参考强测试集 {metric} = {draft['reference'][metric]}，低于阈值 {draft['reference']['threshold']}；需要补强")
    write_json(run_dir / "mutation_baseline.json", draft)
    report = {"passed": not problems, "problems": problems, "reference": draft["reference"],
              "mutants": len(draft["mutants"]), "equivalent_candidates": len(draft["equivalent"]),
              "unstable": len(draft["unstable"]), "review_needed": len(draft["review_needed"]),
              "draft": str((run_dir / "mutation_baseline.json").relative_to(REPO))}
    write_json(run_dir / "prepare_report.json", report)
    print(f"变异 {report['mutants']} 个；等价候选 {report['equivalent_candidates']}；不稳定 {report['unstable']}；"
          f"需复核 {report['review_needed']}；参考强测试集 M1 = {draft['reference']['m1']}")
    for problem in problems:
        print("问题：" + problem)
    if args.write and not problems:
        write_json(target, draft)
        if frozen:
            write_json(hidden_path(task, "coverage_baseline"), frozen)
        print(f"已写入 {target}；请人工复核等价变异候选后，把 review.status 改为 reviewed")
    elif args.write:
        print("存在问题，未写入题目包")
    print(f"草稿：{run_dir / 'mutation_baseline.json'}")
    return (0 if not problems else 1), not problems


if __name__ == "__main__":
    raise SystemExit(main())
