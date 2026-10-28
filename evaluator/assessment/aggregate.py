#!/usr/bin/env python3
"""汇总与比较：按 docs/评分算法.md 第 5–6 节，把各次运行的 result.json 汇总到题目和题库，并比较两个版本。

用法：
    python3 evaluator/assessment/aggregate.py summarize --runs <run-id> [<run-id> ...]
    python3 evaluator/assessment/aggregate.py compare --runs <run-id> ... --baseline A --candidate B \\
        --delta 0.05 --tolerance V2=0.05 --tolerance S1=0.05 --tolerance K1.seconds=60
汇总器只读结果文件中的计数和指标，不重新执行任何测试。
"""
import argparse
import json
from pathlib import Path
import random
import statistics
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from common import RUNS, admission_state, load_admission, now, read_json, write_json  # noqa: E402

RATIO_METRICS = ["V1", "V2", "V3", "S1", "M1_e2e", "M1_valid", "M2", "M4", "F1", "C1", "C2", "C3"]
COST_FIELDS = ["tokens_input", "tokens_output", "tokens_cache_read", "tokens_cache_write", "seconds", "model_calls", "repair_rounds", "usd"]
HIGHER_IS_BETTER = {"V1", "V2", "M1_e2e", "M1_valid", "M2", "M4", "C1", "C2", "C3"}


# ---- 读取 ----

def load_results(runs, version=None):
    """读取运行目录下全部 result.json，只保留带 agent_version 的正式评分结果（排除校准与准备）。"""
    results = []
    for run in runs:
        root = Path(run) if Path(run).is_dir() else RUNS / run
        if not root.is_dir():
            raise SystemExit(f"找不到运行目录：{run}")
        for path in sorted(root.rglob("result.json")):
            # 被重评替换的结果（infra-retries、incomplete）和失败的生成尝试不参与汇总。
            if {"infra-retries", "incomplete", "generation-attempts"} & set(path.parts):
                continue
            result = read_json(path)
            if version is not None and result.get("scorer", {}).get("version") != version:
                continue
            if result.get("mode") == "score" and (result.get("meta") or {}).get("agent_version"):
                result["_path"] = str(path)
                results.append(result)
    return results


def cost_values(cost):
    """把成本记录展开成可汇总的数值字段；缺失为 None。"""
    cost = cost or {}
    tokens = cost.get("tokens") or {}
    return {"tokens_input": tokens.get("input"), "tokens_output": tokens.get("output"),
            "tokens_cache_read": tokens.get("cache_read"), "tokens_cache_write": tokens.get("cache_write"),
            "seconds": cost.get("seconds"), "model_calls": cost.get("model_calls"),
            "repair_rounds": cost.get("repair_rounds"), "usd": cost.get("usd")}


def metric_value(result, name):
    """一份产物上的指标值；infra_error 的产物不参与任何计算。"""
    if result["status"] == "infra_error":
        return None
    if name.startswith("K1."):
        return cost_values(result.get("cost")).get(name[3:])
    return (result.get("metrics") or {}).get(name)


def index(results, set_name=None, phase=None):
    """{agent_version: {task_id: {trial: result}}}，并检查重复。"""
    table, duplicates = {}, []
    for result in results:
        meta = result["meta"]
        if set_name and result["task"]["set"] != set_name:
            continue
        if phase and meta.get("phase", "final") != phase:
            continue
        slot = table.setdefault(meta["agent_version"], {}).setdefault(result["task"]["id"], {})
        key = meta.get("trial")
        if key in slot:
            duplicates.append(f"{meta['agent_version']} {result['task']['id']} trial {key}")
        slot[key] = result
    if duplicates:
        raise SystemExit("存在重复的运行结果：" + "；".join(duplicates))
    return table


# ---- 第 5 节：汇总 ----

def mean(values):
    values = [v for v in values if v is not None]
    return sum(values) / len(values) if values else None


def summarize_task(trials):
    results = list(trials.values())
    usable = [r for r in results if r["status"] != "infra_error"]
    out = {"trials": len(results), "infra_missing": len(results) - len(usable),
           "statuses": {s: sum(r["status"] == s for r in results) for s in sorted({r["status"] for r in results})}}
    for name in RATIO_METRICS:
        out[name] = mean(metric_value(r, name) for r in usable)
    s2 = [v for r in usable for v in ((r.get("metrics") or {}).get("S2") or {}).values()]
    out["S2_median"] = statistics.median(s2) if s2 else None
    for field in COST_FIELDS:
        values = [metric_value(r, "K1." + field) for r in usable]
        values = [v for v in values if v is not None]
        out["K1." + field] = {"mean": mean(values), "median": statistics.median(values) if values else None}
    return out


def summarize(results, set_name, phase):
    table = index(results, set_name, phase)
    summary = {}
    for agent, tasks in sorted(table.items()):
        per_task = {task: summarize_task(trials) for task, trials in sorted(tasks.items())}
        overall = {}
        for name in RATIO_METRICS + ["S2_median"]:
            values = [t[name] for t in per_task.values() if t[name] is not None]
            overall[name] = {"mean": mean(values), "tasks": len(values)}
        summary[agent] = {"tasks": per_task, "overall": overall}
    return summary


# ---- 第 6 节：比较 ----

def percentile(sorted_values, q):
    if not sorted_values:
        return None
    position = (len(sorted_values) - 1) * q
    low = int(position)
    high = min(low + 1, len(sorted_values) - 1)
    return sorted_values[low] + (sorted_values[high] - sorted_values[low]) * (position - low)


def paired_bootstrap(per_task, replicates, seed):
    """per_task: [(A 的取值列表, B 的取值列表)]。返回 (Δ, L, U)：两层配对 bootstrap 的 95% 区间。"""
    if not per_task:
        return None, None, None
    delta = mean(mean(b) - mean(a) for a, b in per_task)
    rng = random.Random(seed)
    n = len(per_task)
    draws = []
    for _ in range(replicates):
        total = 0.0
        for _ in range(n):
            a, b = per_task[rng.randrange(n)]
            total += (sum(rng.choice(b) for _ in b) / len(b)) - (sum(rng.choice(a) for _ in a) / len(a))
        draws.append(total / n)
    draws.sort()
    return delta, percentile(draws, 0.025), percentile(draws, 0.975)


def paired_values(table, baseline, candidate, metric):
    pairs, tasks = [], []
    for task in sorted(set(table.get(baseline, {})) & set(table.get(candidate, {}))):
        a = [metric_value(r, metric) for r in table[baseline][task].values()]
        b = [metric_value(r, metric) for r in table[candidate][task].values()]
        a, b = [v for v in a if v is not None], [v for v in b if v is not None]
        if a and b:
            pairs.append((a, b))
            tasks.append(task)
    return pairs, tasks


def compare(results, baseline, candidate, delta_min, tolerances, set_name="dev", phase="final",
            replicates=10000, seed=20261024, primary="M1_e2e"):
    table = index(results, set_name, phase)
    pairs, tasks = paired_values(table, baseline, candidate, primary)
    delta, low, high = paired_bootstrap(pairs, replicates, seed)
    guards = {}
    for metric, epsilon in sorted(tolerances.items()):
        g_pairs, g_tasks = paired_values(table, baseline, candidate, metric)
        g_delta, g_low, g_high = paired_bootstrap(g_pairs, replicates, seed)
        higher_better = metric in HIGHER_IS_BETTER
        worse = None if g_delta is None else (-g_delta if higher_better else g_delta)
        guards[metric] = {"delta": g_delta, "ci": [g_low, g_high], "worse": worse, "tolerance": epsilon,
                          "passes": worse is not None and worse <= epsilon, "tasks": len(g_tasks)}
    decision = decide(delta, low, high, delta_min, guards)
    return {"baseline": baseline, "candidate": candidate, "set": set_name, "phase": phase, "primary": primary,
            "tasks": tasks, "n_tasks": len(tasks), "delta": delta, "ci": [low, high], "delta_min": delta_min,
            "guards": guards, "decision": decision,
            "note": "题数不足 10，结论仅供参考" if len(tasks) < 10 else None,
            "bootstrap": {"replicates": replicates, "seed": seed}, "computed_at": now()}


def decide(delta, low, high, delta_min, guards):
    """docs/评分算法.md 第 6.4 节，依次判断，命中即停。"""
    if delta is None:
        return "无法区分"
    if delta >= delta_min and low > 0:
        failing = [m for m, g in guards.items() if not g["passes"]]
        return "主指标提升但有代价：" + "、".join(failing) if failing else "更好"
    if delta <= -delta_min and high < 0:
        return "更差"
    return "无法区分"


def calibration_problems(results):
    states = {(r["scorer"]["version"], r["scorer"]["code_sha256"]) for r in results}
    problems = []
    if len(states) > 1:
        problems.append(f"结果来自不同版本的评测模块：{sorted(states)}；先用同一版本补评")
    uncalibrated = sorted({r["_path"] for r in results if r["scorer"].get("calibration", {}).get("status") != "passed"})
    if uncalibrated:
        problems.append(f"{len(uncalibrated)} 份结果的评测模块校准状态不是 passed")
    return problems


def admission_problems(results, admitted=None):
    """R-08：正式比较只用已准入题目的结果，且结果评分时的题目指纹须与准入登记一致。"""
    admitted = load_admission() if admitted is None else admitted
    states = {}
    for r in results:
        task = r.get("task") or {}
        state = admission_state(task.get("id"), task.get("sha256"), admitted)["status"]
        if state != "admitted":
            states.setdefault(state, set()).add(task.get("id"))
    labels = {"not_admitted": "未准入", "stale": "准入后材料已变化或结果未记录题目指纹"}
    return [f"{labels[state]}的题目：{', '.join(sorted(map(str, ids)))}" for state, ids in sorted(states.items())]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("summarize", "compare"):
        p = sub.add_parser(name)
        p.add_argument("--runs", nargs="+", required=True)
        p.add_argument("--set", choices=["dev", "acceptance"], default="dev")
        p.add_argument("--phase", choices=["first", "final"], default="final")
        p.add_argument("--assessment-version", "--scorer-version", dest="assessment_version",
                       help="只汇总指定评测模块版本；--scorer-version 是兼容旧命令的别名")
        p.add_argument("--out", type=Path)
        p.add_argument("--allow-uncalibrated", action="store_true")
        p.add_argument("--allow-unadmitted", action="store_true", help="包含未准入题目的结果，只作参考")
        if name == "compare":
            p.add_argument("--baseline", required=True)
            p.add_argument("--candidate", required=True)
            p.add_argument("--delta", type=float, required=True, help="最小有意义差异 δ")
            p.add_argument("--tolerance", action="append", default=[], help="守护指标容忍值，例如 V2=0.05")
            p.add_argument("--bootstrap", type=int, default=10000)
            p.add_argument("--seed", type=int, default=20261024)
    args = parser.parse_args()
    results = load_results(args.runs, args.assessment_version)
    problems = calibration_problems(results)
    if problems and not args.allow_uncalibrated:
        raise SystemExit("；".join(problems) + "（确认只做参考时加 --allow-uncalibrated）")
    unadmitted = admission_problems(results)
    if unadmitted and not args.allow_unadmitted:
        raise SystemExit("；".join(unadmitted) + "（正式比较只用已准入题目；确认只做参考时加 --allow-unadmitted）")
    problems += unadmitted
    if args.command == "summarize":
        output = {"set": args.set, "phase": args.phase, "summary": summarize(results, args.set, args.phase),
                  "warnings": problems}
    else:
        tolerances = {}
        for item in args.tolerance:
            key, _, value = item.partition("=")
            tolerances[key] = float(value)
        output = compare(results, args.baseline, args.candidate, args.delta, tolerances, args.set, args.phase,
                         args.bootstrap, args.seed)
        output["warnings"] = problems
    text = json.dumps(output, ensure_ascii=False, indent=2)
    if args.out:
        write_json(args.out, output)
    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
