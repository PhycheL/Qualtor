"""评分判定：测试状态、产物状态、计数与指标。纯函数，容器内外共用。

判定顺序与公式见 docs/评分算法.md 第 3–4 节；这里的实现即为准。
"""

# 测试级状态
DISABLED = "disabled"
SKIPPED = "skipped"
CRASHED = "crashed"
TIMED_OUT = "timed_out"
FAILED_ON_TARGET = "failed_on_target"
PASSED = "passed"          # 步骤 3 通过，尚未做稳定性检查
FLAKY = "flaky"
VALID = "valid"
INVALID_TEST_STATUSES = (DISABLED, SKIPPED, CRASHED, TIMED_OUT, FAILED_ON_TARGET)

# 产物级状态
SCORED = "scored"
INVALID = "invalid"
INFRA_ERROR = "infra_error"

_OUTCOME_TO_STATUS = {"disabled": DISABLED, "skipped": SKIPPED, "crashed": CRASHED,
                      "timed_out": TIMED_OUT, "failed": FAILED_ON_TARGET, "passed": PASSED}


def full_run_usable(full_run):
    """整体运行正常结束且写出了 JSON：退出码只允许 0（全部通过）或 1（有断言失败）。"""
    return bool(full_run and full_run.get("json") and not full_run.get("timed_out")
                and full_run.get("returncode") in (0, 1))


def step3_statuses(discovered, full_run, isolation):
    """步骤 2–3：按 docs/评分算法.md 第 3 节的顺序给每个发现的测试定状态。

    返回 (statuses, problem)。problem 为 None 或产物级问题：protocol_mismatch、no_result。
    """
    names = [t["name"] for t in discovered]
    if full_run_usable(full_run):
        outcomes = full_run.get("outcomes") or {}
        if set(outcomes) != set(names):
            return {}, "protocol_mismatch"
        return {n: _OUTCOME_TO_STATUS[outcomes[n]["outcome"]] for n in names}, None
    statuses = {}
    for name in names:
        outcome = (isolation or {}).get(name, {}).get("outcome")
        if outcome not in _OUTCOME_TO_STATUS:
            outcome = "crashed"  # 单独重跑也没有拿到结果
        statuses[name] = _OUTCOME_TO_STATUS[outcome]
    if names and all(s in (CRASHED, TIMED_OUT) for s in statuses.values()):
        return statuses, "no_result"
    return statuses, None


def is_flaky(stability):
    """步骤 4：任意一次重复、乱序或单独运行的结果与步骤 3 的“通过”不同，即为不稳定。"""
    return (stability.get("repeat_failures", 0) > 0 or stability.get("shuffle_failures", 0) > 0
            or stability.get("isolation_outcome", "passed") != "passed")


def final_test_statuses(step3, stability):
    """合并步骤 3 和步骤 4：通过且稳定的为 valid，通过但不稳定的为 flaky。"""
    final = {}
    for name, status in step3.items():
        if status == PASSED:
            final[name] = FLAKY if is_flaky(stability.get(name, {})) else VALID
        else:
            final[name] = status
    return final


def artifact_status(product_problem=None, build=None, record=None, infra=None):
    """docs/评分算法.md 第 4.1 节：按顺序判定产物状态，返回 (status, reason)。"""
    if infra:
        return INFRA_ERROR, infra
    if product_problem:
        return INVALID, "artifact_rejected"
    if build is not None and build.get("status") != "built":
        return INVALID, "build_failed"
    if record is None:
        return INFRA_ERROR, "missing_run_record"
    discovery = record.get("discovery") or {}
    if not discovery.get("ok"):
        return INVALID, "no_result"
    if not discovery.get("tests"):
        return INVALID, "zero_tests"
    problem = record.get("step3_problem")
    if problem in ("protocol_mismatch", "no_result"):
        return INVALID, problem
    statuses = record.get("final_statuses") or {}
    if not any(s in (VALID, FLAKY) for s in statuses.values()):
        return INVALID, "no_valid_tests"
    if not any(s == VALID for s in statuses.values()):
        return INVALID, "all_flaky"
    return SCORED, None


def test_counts(record, repeats):
    """docs/评分算法.md 第 4.2 节中与测试有关的计数。"""
    statuses = (record or {}).get("final_statuses") or {}
    stability = (record or {}).get("stability") or {}
    flaky = sorted(n for n, s in statuses.items() if s == FLAKY)
    by_status = {}
    for status in statuses.values():
        by_status[status] = by_status.get(status, 0) + 1
    discovery = (record or {}).get("discovery") or {}
    return {
        "n_discovered": len(discovery.get("tests") or []) if discovery.get("ok") else None,
        "n_invalid": sum(by_status.get(s, 0) for s in INVALID_TEST_STATUSES),
        "n_passed_1_3": by_status.get(VALID, 0) + by_status.get(FLAKY, 0),
        "n_flaky": len(flaky),
        "n_valid": by_status.get(VALID, 0),
        "by_status": dict(sorted(by_status.items())),
        "flaky_failures": {n: stability.get(n, {}).get("repeat_failures", 0) for n in flaky},
        "repeats": repeats,
    }


def valid_tests(record):
    """稳定有效测试清单，保持发现顺序。"""
    statuses = (record or {}).get("final_statuses") or {}
    order = [t["name"] for t in ((record or {}).get("discovery") or {}).get("tests") or []]
    return [n for n in order if statuses.get(n) == VALID]


# ---- 步骤 6：变异 ----

MULL_STATUS = {"Killed": "killed", "Survived": "survived", "NoCoverage": "not_covered", "Timeout": "timeout"}


def mull_status(raw):
    return MULL_STATUS.get(raw, "other")


def evaluate_mutants(report_mutants, baseline, config_sha256):
    """与冻结的变异分母比对。返回 (problem, counts, per_mutant)。problem 非空时为基础设施错误。"""
    if not baseline:
        return "missing_mutation_baseline", None, None
    if baseline.get("mull", {}).get("config_sha256") != config_sha256:
        return "mull_config_changed", None, None
    expected = {m["id"] for m in baseline.get("mutants", [])}
    actual = {m["id"] for m in report_mutants}
    if expected != actual:
        missing, extra = sorted(expected - actual), sorted(actual - expected)
        return f"mutant_set_mismatch: missing={len(missing)} extra={len(extra)}", None, None
    excluded_equivalent = {m["id"] for m in baseline.get("equivalent", [])}
    excluded_unstable = {m["id"] for m in baseline.get("unstable", [])}
    counts = {"killed": 0, "survived": 0, "not_covered": 0, "timeout": 0, "other": 0}
    per_mutant = {}
    for mutant in sorted(report_mutants, key=lambda m: m["id"]):
        if mutant["id"] in excluded_equivalent:
            per_mutant[mutant["id"]] = "equivalent"
            continue
        if mutant["id"] in excluded_unstable:
            per_mutant[mutant["id"]] = "unstable"
            continue
        status = mull_status(mutant["status"])
        counts[status] += 1
        per_mutant[mutant["id"]] = status
    counts["total"] = sum(counts[k] for k in ("killed", "survived", "not_covered", "timeout", "other"))
    counts["excluded_equivalent"] = len(excluded_equivalent)
    counts["excluded_unstable"] = len(excluded_unstable)
    return None, counts, per_mutant


def m1(counts):
    """M1 = 杀死数 ÷ (分母 − 超时数)；其他状态计入分母但不计入分子，并单独报告。"""
    if not counts or "total" not in counts:
        return None  # 准备模式只有原始计数，没有冻结的分母
    denominator = counts["total"] - counts["timeout"]
    return counts["killed"] / denominator if denominator > 0 else None


# ---- 步骤 7：替换版本 ----

def variant_outcome(variant, build_ok, outcomes, valid):
    """docs/评测模块与校准样本设计.md 第 5.7 节。返回 (outcome, failed_tests, infra_problem)。"""
    if not build_ok:
        if variant["expect"] == "fail":
            return "build_failed", [], None
        return None, [], f"variant {variant['id']} expected to build"
    failed = [n for n in valid if (outcomes.get(n) or {}).get("outcome") in ("failed", "crashed", "timed_out")]
    if variant["expect"] == "fail":
        if any((outcomes.get(n) or {}).get("outcome") in ("failed", "crashed") for n in valid):
            return "detected", failed, None
        if failed:
            return "timeout", failed, None
        return "not_detected", [], None
    return ("false_alarm", failed, None) if failed else ("clean", [], None)


# ---- 指标 ----

def _ratio(numerator, denominator):
    return numerator / denominator if denominator else None


def metrics(result):
    """docs/评分算法.md 第 4.3 节：由一份产物的计数算指标；None 表示“不适用”。"""
    status, reason = result["status"], result.get("invalid_reason")
    counts = result.get("counts") or {}
    tests = counts.get("tests") or {}
    built = 1 if (result.get("build") or {}).get("status") == "built" else 0
    out = {"V1": built,
           "V2": 1 if status == SCORED or reason == "all_flaky" else 0,
           "V3": _ratio(tests.get("n_invalid", 0), tests.get("n_discovered")) if tests.get("n_discovered") is not None else None,
           "S1": _ratio(tests.get("n_flaky", 0), tests.get("n_passed_1_3")),
           "S2": {n: f / tests["repeats"] for n, f in (tests.get("flaky_failures") or {}).items()} if tests.get("repeats") else {},
           }
    out["S2_max"] = max(out["S2"].values()) if out["S2"] else None
    if status == SCORED:
        value = m1(counts.get("mutants"))
        out["M1_e2e"] = value
        out["M1_valid"] = value
    else:
        out["M1_e2e"] = 0.0
        out["M1_valid"] = None
    coverage = counts.get("coverage") if status == SCORED else None
    for key, field in (("C1", "lines"), ("C2", "branches"), ("C3", "functions")):
        total = (coverage or {}).get("total", {}).get(field)
        out[key] = _ratio(total["covered"], total["total"]) if total else None
    variants = [v for v in (result.get("variants") or []) if status == SCORED]
    handwritten = [v for v in variants if v["kind"] == "handwritten" and v["outcome"] != "build_failed"]
    real = [v for v in variants if v["kind"] == "real_bug" and v["outcome"] != "build_failed"]
    equivalent = [v for v in variants if v["kind"] == "equivalent"]
    out["M2"] = _ratio(sum(v["outcome"] == "detected" for v in handwritten), len(handwritten))
    out["M4"] = _ratio(sum(v["outcome"] == "detected" for v in real), len(real))
    if equivalent:
        alarmed = set()
        for v in equivalent:
            alarmed.update(v.get("failed_tests") or [])
        out["F1"] = _ratio(len(alarmed), tests.get("n_valid", 0))
    else:
        out["F1"] = None
    out["K1"] = result.get("cost")
    return out


# ---- 确定性比较 ----

def stable_view(result):
    """去掉耗时、路径、时间戳等易变字段，用于“同一产物评两次结果一致”的检查。"""
    view = {"status": result.get("status"), "invalid_reason": result.get("invalid_reason"),
            "build": (result.get("build") or {}).get("status"),
            "tests": result.get("tests"), "counts": result.get("counts"),
            "mutants": result.get("mutants"),
            "variants": [{k: v.get(k) for k in ("id", "kind", "expect", "outcome", "failed_tests")}
                         for v in result.get("variants") or []]}
    return view
