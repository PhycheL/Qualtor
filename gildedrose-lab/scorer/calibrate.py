#!/usr/bin/env python3
"""评分器校准：对校准样本逐个评分两次，与期望比对，检查重复评分一致，写校准报告和校准状态。

用法（在装有 Docker 和两个工具链镜像的机器上，从项目根目录执行）：
    python3 gildedrose-lab/scorer/calibrate.py
    python3 gildedrose-lab/scorer/calibrate.py --samples CAL-01,CAL-07 --jobs 2
只校准部分样本时会写报告，但不会把校准状态记为通过。
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "scripts"))

from audit import Audit  # noqa: E402
from common import (ARTIFACTS, CALIBRATION, CALIBRATION_STATUS, LAB, RUNS, check_run_id, default_run_id,  # noqa: E402
                    hidden_path, load_baseline, load_task, now, read_json, samples_sha256, scorer_code_sha256,
                    scorer_version, sha256_file, task_sha256, write_json)
import judge  # noqa: E402
import pipeline  # noqa: E402

NEEDS = {"M1_e2e": "mull", "M1_valid": "mull", "C1": "coverage", "C2": "coverage", "C3": "coverage"}


def load_samples(task_id, selected=None):
    root = CALIBRATION / task_id
    samples = {}
    for path in sorted(p for p in root.iterdir() if p.is_dir() and (p / "expected.json").is_file()):
        if selected and path.name not in selected:
            continue
        samples[path.name] = {"dir": path, "expected": read_json(path / "expected.json")}
    if selected and set(selected) - set(samples):
        raise SystemExit(f"找不到样本：{sorted(set(selected) - set(samples))}")
    return samples


def check_reference_copy(task, sample):
    """样本里的参考测试副本必须与隐藏的参考强测试集逐字节相同。"""
    rel = sample["expected"].get("reference_copy")
    if not rel:
        return []
    reference = hidden_path(task, "reference_tests") / Path(rel).name
    copy = sample["dir"] / "final" / rel
    if not copy.is_file() or sha256_file(copy) != sha256_file(reference):
        return [f"{rel} 与参考强测试集不一致，需要重建样本"]
    return []


def check_hard(hard, result):
    """硬性期望：必须完全一致的判定。"""
    problems = []
    for key in ("status", "invalid_reason"):
        if key in hard and result.get(key) != hard[key]:
            problems.append(f"{key}: 期望 {hard[key]}，实际 {result.get(key)}（{result.get('infra_detail') or ''}）"[:400])
    tests = result.get("tests") or {}
    explicit = hard.get("tests", {})
    for name, status in explicit.items():
        if tests.get(name) != status:
            problems.append(f"测试 {name}: 期望 {status}，实际 {tests.get(name)}")
    default = hard.get("tests_default")
    if default:
        wrong = {n: s for n, s in tests.items() if n not in explicit and s != default}
        if wrong:
            problems.append(f"其余测试应为 {default}，实际有 {wrong}")
    variants = {v["id"]: v for v in result.get("variants") or []}
    for vid, outcome in (hard.get("variants") or {}).items():
        actual = variants.get(vid, {}).get("outcome")
        if actual != outcome:
            problems.append(f"替换版本 {vid}: 期望 {outcome}，实际 {actual}")
    for vid, names in (hard.get("variant_failed_tests") or {}).items():
        actual = sorted(variants.get(vid, {}).get("failed_tests") or [])
        if actual != sorted(names):
            problems.append(f"替换版本 {vid} 上失败的测试: 期望 {sorted(names)}，实际 {actual}")
    return problems


def _compare(op, value, other):
    if op == "<":
        return value < other
    if op == ">":
        return value > other
    if op == "<=":
        return value <= other
    if op == ">=":
        return value >= other
    if op == "==":
        return value == other
    raise ValueError(op)


def check_relations(sample_id, expected, metrics_by_sample, capabilities):
    """相对期望：指标的范围或样本之间的大小关系。返回 (problems, skipped)。"""
    problems, skipped = [], []
    for relation in expected.get("relations", []):
        metric = relation["metric"]
        if NEEDS.get(metric) and not capabilities.get(NEEDS[metric]):
            skipped.append(f"{metric} 需要 {NEEDS[metric]}")
            continue
        value = (metrics_by_sample.get(sample_id) or {}).get(metric)
        other = None
        if "ref" in relation:
            if relation["ref"] not in metrics_by_sample:
                skipped.append(f"{metric} 需要样本 {relation['ref']}")
                continue
            other = (metrics_by_sample[relation["ref"]] or {}).get(metric)
            if other is not None and "factor" in relation:
                other = other * relation["factor"]
        elif "value" in relation:
            other = relation["value"]
        if value is None or (other is None and relation["op"] != "between"):
            problems.append(f"{metric}: 指标缺失（本样本 {value}，对照 {other}）")
            continue
        op = relation["op"]
        if op == "between":
            low, high = relation["range"]
            ok = low <= value <= high
            shown = f"[{low}, {high}]"
        elif op == "abs_diff_le":
            ok = abs(value - other) <= relation["value"] if "ref" in relation else False
            shown = f"|差| ≤ {relation['value']}（对照 {other:.4f}）"
        else:
            ok = _compare(op, value, other)
            shown = f"{op} {other:.4f}" + (f"（{relation['ref']}）" if "ref" in relation else "")
        if not ok:
            problems.append(f"{metric} = {value:.4f}，期望 {shown}")
    return problems, skipped


def evaluate(task, samples, results, capabilities):
    """results: {sample_id: [round1_result, round2_result, ...]}。返回报告。"""
    metrics = {sid: (rounds[0].get("metrics") or {}) for sid, rounds in results.items()}
    report = {"samples": {}, "passed": True}
    for sid in sorted(results):
        rounds, sample = results[sid], samples[sid]
        entry = {"description": sample["expected"].get("description"), "problems": [], "skipped": [],
                 "status": rounds[0].get("status"), "invalid_reason": rounds[0].get("invalid_reason")}
        entry["problems"] += check_reference_copy(task, sample)
        expected_cost = read_json(sample["dir"] / "generation" / "cost.json")
        for index, result in enumerate(rounds, 1):
            entry["problems"] += [f"第 {index} 次：{p}" for p in check_hard(sample["expected"].get("hard", {}), result)]
            if (result.get("cost") != expected_cost
                    or (result.get("metrics") or {}).get("K1") != expected_cost):
                entry["problems"].append(f"第 {index} 次：成本记录或 K1 与输入 cost.json 不一致")
        views = [judge.stable_view(r) for r in rounds]
        if any(view != views[0] for view in views[1:]):
            entry["problems"].append("重复评分结果不一致（除耗时字段外）")
        problems, skipped = check_relations(sid, sample["expected"], metrics, capabilities)
        entry["problems"] += problems
        entry["skipped"] += skipped
        entry["metrics"] = {k: metrics[sid].get(k) for k in ("M1_e2e", "M1_valid", "C1", "C2", "C3", "S1", "S2_max",
                                                              "V3", "M2", "F1")}
        entry["passed"] = not entry["problems"]
        report["passed"] = report["passed"] and entry["passed"]
        report["samples"][sid] = entry
    return report


def markdown(report):
    lines = [f"# 校准报告 {report['run_id']}", "",
             f"- 评分器版本：{report['scorer_version']}（代码指纹 {report['scorer_code_sha256'][:12]}）",
             f"- 结论：**{'通过' if report['passed'] else '未通过'}**" + ("（部分样本，不计为正式校准）" if report["partial"] else ""),
             f"- 每个样本评分 {report['rounds']} 次；镜像：" + "、".join(f"{k} {v['id'][:19]}" for k, v in report["images"].items()),
             "", "| 样本 | 结论 | 状态 | M1 端到端 | C1 | S1 | 问题 |", "|---|---|---|---|---|---|---|"]
    fmt = lambda v: "—" if v is None else f"{v:.3f}"
    for sid, entry in report["samples"].items():
        m = entry["metrics"]
        status = entry["status"] + (f"（{entry['invalid_reason']}）" if entry["invalid_reason"] else "")
        problems = "；".join(entry["problems"]).replace("|", "/") or "—"
        lines.append(f"| {sid} | {'通过' if entry['passed'] else '未通过'} | {status} | {fmt(m['M1_e2e'])} | "
                     f"{fmt(m['C1'])} | {fmt(m['S1'])} | {problems} |")
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--task", default="gildedrose-update-quality")
    parser.add_argument("--run-id", default=default_run_id("calibration"))
    parser.add_argument("--rounds", type=int, default=2)
    parser.add_argument("--jobs", type=int, default=2)
    parser.add_argument("--samples", help="逗号分隔的样本 ID；省略表示全部样本")
    args = parser.parse_args()
    check_run_id(args.run_id)
    if args.rounds < 2:
        parser.error("至少评分 2 次，才能检查重复评分一致")
    from docker_runner import DockerExecutor
    run_dir, evidence = RUNS / args.run_id, ARTIFACTS / "scorer" / args.run_id
    if run_dir.exists() or evidence.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    evidence.mkdir(parents=True)
    task = load_task(args.task)
    if not load_baseline(task):
        raise SystemExit("题目缺少变异分母 hidden/mutation_baseline.json，先运行 prepare_task.py baseline")
    selected = [s.strip() for s in args.samples.split(",")] if args.samples else None
    samples = load_samples(task["id"], selected)
    executor = DockerExecutor(Audit(evidence / "host"), evidence, args.run_id)

    def score(job):
        sid, index = job
        out = run_dir / "calibration" / task["id"] / sid / f"round-{index}"
        sample = samples[sid]["dir"]
        print(f"评分 {sid} 第 {index} 次", flush=True)
        return job, pipeline.score_product(executor, task, sample / "final", out,
                                           {"calibration_sample": sid, "round": index},
                                           Audit(out.parent / f"round-{index}-host"), sample / "generation" / "cost.json",
                                           calibration={"status": "in_calibration"})

    jobs = [(sid, index) for index in range(1, args.rounds + 1) for sid in samples]
    results = {sid: [None] * args.rounds for sid in samples}
    with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
        for (sid, index), result in pool.map(score, jobs):
            results[sid][index - 1] = result
            print(f"  {sid} 第 {index} 次：{result['status']} {result.get('invalid_reason') or ''}", flush=True)
    report = evaluate(task, samples, results, executor.capabilities)
    report.update(run_id=args.run_id, task=task["id"], rounds=args.rounds, partial=bool(selected),
                  scorer_version=scorer_version(), scorer_code_sha256=scorer_code_sha256(),
                  samples_sha256=samples_sha256(), task_sha256=task_sha256(task), images=executor.images,
                  finished_at=now())
    write_json(run_dir / "calibration_report.json", report)
    (run_dir / "calibration_report.md").write_text(markdown(report))
    if not selected:
        write_json(CALIBRATION_STATUS, {"scorer_version": report["scorer_version"],
                                        "scorer_code_sha256": report["scorer_code_sha256"],
                                        "samples_sha256": report["samples_sha256"],
                                        "tasks": {task["id"]: task_sha256(task)},
                                        "images": {k: v["id"] for k, v in executor.images.items()},
                                        "run_id": args.run_id, "passed": report["passed"],
                                        "report": str((run_dir / "calibration_report.json").relative_to(LAB)),
                                        "finished_at": report["finished_at"]})
    print(markdown(report))
    print(f"报告：{run_dir / 'calibration_report.md'}")
    return 0 if report["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
