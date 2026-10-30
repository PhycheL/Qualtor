#!/usr/bin/env python3
"""评测模块校准：对校准样本逐个评分两次，与期望比对，检查重复评分一致，写校准报告和校准状态。

样本按题目放在 calibration/<题目 ID>/ 下；默认校准所有带样本的题目，并在校准状态中记录每道题的指纹（R-08）。

用法（在装有 Docker 和两个工具链镜像的机器上，从项目根目录执行）：
    python3 evaluator/assessment/calibrate.py
    python3 evaluator/assessment/calibrate.py --task gildedrose-update-quality --samples CAL-01,CAL-07 --jobs 2
只校准部分题目或部分样本时会写报告，但不会更新校准状态。
"""
import argparse
import shutil
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent / "common"))

from audit import Audit  # noqa: E402
from common import (CALIBRATION, CALIBRATION_STATUS, REPO, RUNS, check_run_id, default_run_id,  # noqa: E402
                    hidden_path, load_baseline, load_task, now, read_json, samples_sha256, assessment_code_sha256,
                    assessment_version, environment_identity, sha256_file, task_sha256, write_json)
import judge  # noqa: E402
from runs import finish, new_manifest, write_manifest  # noqa: E402
import pipeline  # noqa: E402
from build_contract import generated_units, task_environment

NEEDS = {"M1_e2e": "mull", "M1_valid": "mull", "C1": "coverage", "C2": "coverage", "C3": "coverage"}


def calibration_tasks():
    """带校准样本的题目 ID：calibration/<题目 ID>/ 下至少有一个含 expected.json 的样本目录。"""
    return sorted(p.name for p in CALIBRATION.iterdir()
                  if p.is_dir() and any((s / "expected.json").is_file() for s in p.iterdir() if s.is_dir()))


def load_samples(task_id, selected=None):
    root = CALIBRATION / task_id
    samples = {}
    for path in sorted(p for p in root.iterdir() if p.is_dir() and (p / "expected.json").is_file()):
        if selected and path.name not in selected:
            continue
        samples[path.name] = {"dir": path, "expected": read_json(path / "expected.json")}
    return samples


def check_reference_copy(task, sample):
    """样本里的参考测试副本必须与隐藏的参考强测试集逐字节相同。"""
    expected = sample["expected"]
    relatives = expected.get("reference_copies", [])
    problems = []
    reference_root = hidden_path(task, "reference_tests")
    if "reference_copies" in expected:
        actual = {"tests/" + p.name for p in reference_root.iterdir()
                  if p.is_file() and p.suffix in (".cc", ".h")}
        if set(relatives) != actual:
            problems.append("reference_copies 与参考强测试集文件清单不一致，需要重建样本")
    if expected.get("reference_copy"):
        relatives = list(relatives) + [expected["reference_copy"]]
    for rel in relatives:
        reference = reference_root / Path(rel).name
        copy = sample["dir"] / "final" / rel
        if not reference.is_file() or not copy.is_file() or sha256_file(copy) != sha256_file(reference):
            problems.append(f"{rel} 与参考强测试集不一致，需要重建样本")
    return problems


def check_hard(hard, result):
    """硬性期望：必须完全一致的判定。"""
    problems = []
    for key in ("status", "invalid_reason"):
        if key in hard and result.get(key) != hard[key]:
            problems.append(f"{key}: 期望 {hard[key]}，实际 {result.get(key)}（{result.get('infra_detail') or ''}）"[:400])
    for metric, reason in hard.get("metric_failures", {}).items():
        actual = result.get("metric_failures", {}).get(metric, {})
        if actual.get("reason") != reason or not actual.get("errors"):
            problems.append(f"{metric} 失败原因: 期望 {reason} 及错误位置，实际 {actual}")
    for metric, value in hard.get("metrics", {}).items():
        metrics = result.get("metrics") or {}
        if metric not in metrics or metrics[metric] != value:
            problems.append(f"{metric}: 期望 {value}，实际 {metrics.get(metric)}")
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


def check_environment_boundary(task, expected, result):
    """从结果与原始构建证据核对环境和生成单元；没有期望的新字段时保持旧样本语义。"""
    problems = []
    if 'environment' in expected:
        environment = expected['environment']
        # D021-1：冻结期望只比较环境名与配方哈希；镜像 ID 由本轮校准环境记录核对（run_calibration）。
        actual = result.get('environment') or {}
        if environment_identity(actual) != environment_identity(environment) or set(actual.get('images') or {}) != {'gcc', 'clang'}:
            problems.append('环境记录与冻结期望不一致')
        selected = task_environment(task.get('build', {}))
        if not selected or selected[1] != environment.get('recipe_sha256'):
            problems.append('环境配方与冻结期望不一致')
    if expected.get('build_boundary'):
        targets = set(task.get('target_headers') or task['target_sources'])
        coverage = (result.get('counts', {}).get('coverage') or {}).get('files', {})
        if set(coverage) != targets:
            problems.append('覆盖率文件集合不是声明的被测文件')
        mutants = result.get('mutants') or {}
        if task['target_sources'] and not mutants:
            problems.append('缺少变异记录')
        if any(not any('/repo/' + target + ':' in mid for target in targets) for mid in mutants):
            problems.append('变异记录包含被测文件之外的单元')
        predicted = generated_units(task.get('build', {}), '/build')
        for label, step in result.get('steps', {}).items():
            if not label.endswith('-build'):
                continue
            path = REPO / step['dir'] / 'step.json'
            if not path.is_file() or read_json(path).get('generated_units') != predicted:
                problems.append(label + ' 的生成单元与声明不一致')
    return problems


def check_relations(sample_id, expected, metrics_by_sample, capabilities, not_applicable=None):
    """相对期望：指标的范围或样本之间的大小关系。返回 (problems, skipped)。"""
    problems, skipped = [], []
    for relation in expected.get("relations", []):
        metric = relation["metric"]
        if relation["op"] == "na":
            own = metrics_by_sample.get(sample_id) or {}
            reason_key = "M1" if metric in ("M1_e2e", "M1_valid") else metric
            reason = (not_applicable or {}).get(sample_id, {}).get(reason_key)
            if metric not in own or own[metric] is not None or not reason or reason != relation.get("reason"):
                problems.append(f"{metric}: 期望不适用 {relation.get('reason')}，实际 {own.get(metric)} / {reason}")
            continue
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
            entry['problems'] += [f'第 {index} 次：{p}' for p in check_environment_boundary(task, sample['expected'], result)]
            if (result.get("cost") != expected_cost
                    or (result.get("metrics") or {}).get("K1") != expected_cost):
                entry["problems"].append(f"第 {index} 次：成本记录或 K1 与输入 cost.json 不一致")
        views = [judge.stable_view(r) for r in rounds]
        if any(view != views[0] for view in views[1:]):
            entry["problems"].append("重复评分结果不一致（除耗时字段外）")
        na = {name: rs[0].get("not_applicable", {}) for name, rs in results.items()}
        problems, skipped = check_relations(sid, sample["expected"], metrics, capabilities, na)
        entry["problems"] += problems
        entry["skipped"] += skipped
        entry["metrics"] = {k: metrics[sid].get(k) for k in ("M1_e2e", "M1_valid", "C1", "C2", "C3", "S1", "S2_max",
                                                              "V2", "V3", "M2", "M4", "F1")}
        entry["not_applicable"] = rounds[0].get("not_applicable", {})
        entry["metric_failures"] = rounds[0].get("metric_failures", {})
        entry["passed"] = not entry["problems"]
        report["passed"] = report["passed"] and entry["passed"]
        report["samples"][sid] = entry
    return report


def markdown(report):
    lines = [f"# 校准报告 {report['run_id']}", "",
             f"- 评测模块版本：{report['scorer_version']}（代码指纹 {report['scorer_code_sha256'][:12]}）",
             f"- 结论：**{'通过' if report['passed'] else '未通过'}**" + ("（部分题目或样本，不计为正式校准）" if report["partial"] else ""),
             f"- 题目：" + "、".join(f"{tid}（{len(info['samples'])} 个样本）" for tid, info in report["tasks"].items()),
             f"- 每个样本评分 {report['rounds']} 次；镜像：" + "、".join(f"{k} {v['id'][:19]}" for k, v in report["images"].items()),
             "", "| 题目 | 样本 | 结论 | 状态 | M1 端到端 | M4 | V2 | C1 | S1 | 不适用或单项失败原因 | 问题 |", "|---|---|---|---|---|---|---|---|---|---|---|"]
    fmt = lambda v: "—" if v is None else f"{v:.3f}"
    for sid, entry in report["samples"].items():
        m = entry["metrics"]
        status = entry["status"] + (f"（{entry['invalid_reason']}）" if entry["invalid_reason"] else "")
        problems = "；".join(entry["problems"]).replace("|", "/") or "—"
        reasons = [k + ': ' + v for k, v in entry.get('not_applicable', {}).items()]
        reasons += [k + ' 失败: ' + v['reason'] for k, v in entry.get('metric_failures', {}).items()]
        lines.append(f"| {entry['task']} | {sid} | {'通过' if entry['passed'] else '未通过'} | {status} | {fmt(m['M1_e2e'])} | "
                     f"{fmt(m.get('M4'))} | {fmt(m.get('V2'))} | {fmt(m['C1'])} | {fmt(m['S1'])} | "
                     f"{', '.join(reasons) or '—'} | {problems} |")
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--task", action="append", help="只校准指定题目（可重复）；省略表示所有带样本的题目")
    parser.add_argument("--run-id", default=default_run_id("calibration"))
    parser.add_argument("--rounds", type=int, default=2)
    parser.add_argument("--jobs", type=int, default=2)
    parser.add_argument("--samples", help="逗号分隔的样本 ID；省略表示全部样本")
    args = parser.parse_args()
    check_run_id(args.run_id)
    if args.rounds < 2:
        parser.error("至少评分 2 次，才能检查重复评分一致")
    run_dir, evidence = RUNS / args.run_id, RUNS / args.run_id / "evidence"
    if run_dir.exists() or evidence.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    evidence.mkdir(parents=True)
    manifest = new_manifest(args.run_id, "calibration", tasks=args.task or calibration_tasks(),
                            partial=bool(args.task or args.samples))
    write_manifest(run_dir, manifest)
    try:
        code, passed = run_calibration(args, run_dir, evidence)
    except BaseException as error:
        finish(run_dir, manifest, "failed", error=str(error))
        raise
    finish(run_dir, manifest, "completed", passed=passed)
    return code


def plan(task_ids, selected):
    """读取各题的样本；样本 ID 在所有题目中唯一，汇总报告按样本 ID 列出。"""
    tasks, samples = {}, {}
    for task_id in task_ids:
        if not (CALIBRATION / task_id).is_dir():
            raise SystemExit(f"题目 {task_id} 没有校准样本目录 calibration/{task_id}/")
        task = load_task(task_id)
        if not load_baseline(task):
            raise SystemExit(f"题目 {task_id} 缺少变异分母 hidden/mutation_baseline.json，先运行 prepare_task.py baseline")
        tasks[task_id] = task
        for sid, sample in load_samples(task_id, selected).items():
            if sid in samples:
                raise SystemExit(f"样本 ID 重复：{sid}（{samples[sid]['task']}、{task_id}）")
            samples[sid] = {**sample, "task": task_id}
    if selected and set(selected) - set(samples):
        raise SystemExit(f"找不到样本：{sorted(set(selected) - set(samples))}")
    if not samples:
        raise SystemExit("没有可校准的样本")
    return tasks, samples


def run_calibration(args, run_dir, evidence):
    from docker_runner import DockerExecutor
    all_tasks = calibration_tasks()
    selected = [s.strip() for s in args.samples.split(",")] if args.samples else None
    tasks, samples = plan(args.task or all_tasks, selected)
    partial = bool(selected) or set(tasks) != set(all_tasks)
    executor = DockerExecutor(Audit(evidence / "host"), evidence, args.run_id)

    def score(job):
        sid, index = job
        task = tasks[samples[sid]["task"]]
        out = run_dir / "calibration" / task["id"] / sid / f"round-{index}"
        sample = samples[sid]["dir"]
        print(f"评分 {task['id']} {sid} 第 {index} 次", flush=True)
        return job, pipeline.assess_product(executor, task, sample / "final", out,
                                           {"calibration_sample": sid, "round": index},
                                           Audit(out.parent / f"round-{index}-host"), sample / "generation" / "cost.json",
                                           calibration={"status": "in_calibration"})

    jobs = [(sid, index) for index in range(1, args.rounds + 1) for sid in samples]
    results = {sid: [None] * args.rounds for sid in samples}
    with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
        for (sid, index), result in pool.map(score, jobs):
            results[sid][index - 1] = result
            print(f"  {sid} 第 {index} 次：{result['status']} {result.get('invalid_reason') or ''}", flush=True)
    report = {"samples": {}, "tasks": {}, "passed": True}
    for task_id, task in tasks.items():
        own = {sid: s for sid, s in samples.items() if s["task"] == task_id}
        part = evaluate(task, own, {sid: results[sid] for sid in own}, executor.capabilities)
        for sid, entry in part["samples"].items():
            report["samples"][sid] = {"task": task_id, **entry}
        report["tasks"][task_id] = {"task_sha256": task_sha256(task), "passed": part["passed"], "samples": sorted(own)}
        report["passed"] = report["passed"] and part["passed"]
    report.update(run_id=args.run_id, rounds=args.rounds, partial=partial,
                  scorer_version=assessment_version(), scorer_code_sha256=assessment_code_sha256(),
                  samples_sha256=samples_sha256(), images=executor.images, finished_at=now())
    environments = {task['build']['environment']: executor.environment(task) for task in tasks.values()
                    if task.get('build', {}).get('environment')}
    if environments:
        report['environments'] = environments
        for sid, rounds in results.items():
            name = tasks[samples[sid]['task']].get('build', {}).get('environment')
            if name and any(result.get('environment') != environments[name] for result in rounds):
                report['samples'][sid]['problems'].append('环境记录与本轮校准环境不一致')
                report['samples'][sid]['passed'] = report['passed'] = False
    write_json(run_dir / "calibration_report.json", report)
    (run_dir / "calibration_report.md").write_text(markdown(report))
    if not partial:
        for name in ("calibration_report.json", "calibration_report.md"):
            shutil.copy2(run_dir / name, CALIBRATION_STATUS.parent / name)
        write_json(CALIBRATION_STATUS, {"scorer_version": report["scorer_version"],
                                        "scorer_code_sha256": report["scorer_code_sha256"],
                                        "samples_sha256": report["samples_sha256"],
                                        "tasks": {tid: info["task_sha256"] for tid, info in report["tasks"].items()},
                                        "images": {k: v["id"] for k, v in executor.images.items()},
                                        **({'environments': environments} if environments else {}),
                                        "run_id": args.run_id, "passed": report["passed"],
                                        "report": str((CALIBRATION_STATUS.parent / "calibration_report.json").relative_to(REPO)),
                                        "finished_at": report["finished_at"]})
    print(markdown(report))
    print(f"报告：{run_dir / 'calibration_report.md'}")
    return (0 if report["passed"] else 1), bool(report["passed"])


if __name__ == "__main__":
    raise SystemExit(main())
