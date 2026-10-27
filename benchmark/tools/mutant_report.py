#!/usr/bin/env python3
"""为人工复核生成变异清单：逐题列出等价候选、待复核与不稳定变异，以及参考测试没杀死但探针杀死的变异。

每条列出源码位置、算子、原始行与变异后的写法（能直接替换的运算符直接给出新行，其余给出说明），
以及参考测试、探针各轮的状态，最后留一列给复核人填写结论。只读取题目包里已写入的 mutation_baseline.json，
不修改任何题目材料。

用法（从项目根目录执行）：
  python3 benchmark/tools/mutant_report.py --tasks exercism-clock humaneval-x-cpp-11 --run-id bank-review-<编号>
  python3 benchmark/tools/mutant_report.py --all --run-id bank-review-<编号>
"""
import argparse
import json
from pathlib import Path
import re
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]

import common  # noqa: E402
from runs import finish, new_manifest, write_manifest  # noqa: E402

# 算子 -> (原运算符, 变异后的运算符)
SWAP = {
    "cxx_add_to_sub": ("+", "-"), "cxx_sub_to_add": ("-", "+"), "cxx_mul_to_div": ("*", "/"),
    "cxx_div_to_mul": ("/", "*"), "cxx_rem_to_div": ("%", "/"),
    "cxx_lt_to_le": ("<", "<="), "cxx_le_to_lt": ("<=", "<"), "cxx_gt_to_ge": (">", ">="), "cxx_ge_to_gt": (">=", ">"),
    "cxx_eq_to_ne": ("==", "!="), "cxx_ne_to_eq": ("!=", "=="), "cxx_le_to_gt": ("<=", ">"), "cxx_lt_to_ge": ("<", ">="),
    "cxx_ge_to_lt": (">=", "<"), "cxx_gt_to_le": (">", "<="),
    "cxx_and_to_or": ("&", "|"), "cxx_or_to_and": ("|", "&"), "cxx_xor_to_or": ("^", "|"),
    "cxx_lshift_to_rshift": ("<<", ">>"), "cxx_rshift_to_lshift": (">>", "<<"),
    "cxx_add_assign_to_sub_assign": ("+=", "-="), "cxx_sub_assign_to_add_assign": ("-=", "+="),
    "cxx_mul_assign_to_div_assign": ("*=", "/="), "cxx_div_assign_to_mul_assign": ("/=", "*="),
    "cxx_rem_assign_to_div_assign": ("%=", "/="), "cxx_and_assign_to_or_assign": ("&=", "|="),
    "cxx_or_assign_to_and_assign": ("|=", "&="), "cxx_xor_assign_to_or_assign": ("^=", "|="),
    "cxx_lshift_assign_to_rshift_assign": ("<<=", ">>="), "cxx_rshift_assign_to_lshift_assign": (">>=", "<<="),
    "cxx_pre_inc_to_pre_dec": ("++", "--"), "cxx_post_inc_to_post_dec": ("++", "--"),
    "cxx_pre_dec_to_pre_inc": ("--", "++"), "cxx_post_dec_to_post_inc": ("--", "++"),
}
DESCRIBE = {
    "cxx_remove_void_call": "删除这次 void 函数调用", "cxx_replace_scalar_call": "把这次函数调用的结果替换为 42",
    "cxx_assign_const": "把这次赋值的右侧替换为 42", "cxx_init_const": "把这个初始值替换为 42",
    "cxx_minus_to_noop": "去掉一元负号", "cxx_bitwise_not_to_noop": "去掉按位取反", "cxx_remove_negation": "去掉逻辑非",
}
LOCATION = re.compile(r"^(?P<mutator>[^:]+):(?P<path>.+):(?P<l1>\d+):(?P<c1>\d+):(?P<l2>\d+):(?P<c2>\d+)$")


def render(task_root, mutant_id):
    """返回 (相对路径:行, 原始行, 变异后的写法)。"""
    m = LOCATION.match(mutant_id)
    if not m:
        return mutant_id, "", "无法解析位置"
    rel = m.group("path").split("/repo/", 1)[-1]
    line_no, c1, l2, c2 = int(m.group("l1")), int(m.group("c1")), int(m.group("l2")), int(m.group("c2"))
    path = task_root / rel
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines() if path.is_file() else []
    original = lines[line_no - 1] if 0 < line_no <= len(lines) else ""
    where = f"{rel}:{line_no}:{c1}"
    mutator = m.group("mutator")
    if l2 == line_no and original:
        segment = original[c1 - 1:c2 - 1]
        swap = SWAP.get(mutator)
        if swap and segment.strip() == swap[0]:
            return where, original.strip(), (original[:c1 - 1] + segment.replace(swap[0], swap[1]) + original[c2 - 1:]).strip()
        if swap and swap[0] in segment:
            return where, original.strip(), f"`{segment}` 中的 `{swap[0]}` 改为 `{swap[1]}`"
        if mutator in DESCRIBE:
            return where, original.strip(), f"{DESCRIBE[mutator]}：`{segment}`"
    return where, original.strip(), DESCRIBE.get(mutator, mutator)


def cell(text):
    return str(text).replace("|", "\\|").replace("\n", " ")


def task_report(task_id):
    task = common.load_task(task_id)
    baseline = common.load_baseline(task)
    if baseline is None:
        return None, f"# {task_id}\n\n还没有 mutation_baseline.json，跳过。\n"
    root = common.source_root(task)
    mutants = {m["id"]: m for m in baseline["mutants"]}
    sections = [
        ("等价候选（已从分母剔除）", [e["id"] for e in baseline.get("equivalent", [])]),
        ("不稳定变异（已从分母剔除）", [e["id"] for e in baseline.get("unstable", [])]),
        ("探针超时等待复核（保留在分母中）", [e["id"] for e in baseline.get("review_needed", [])]),
    ]
    excluded = {i for _, ids in sections for i in ids}
    gaps = [i for i, m in mutants.items() if i not in excluded and m["reference_status"][0] != "killed"
            and m["probe_status"][0] == "killed"]
    sections.append(("参考测试没杀死、探针杀死的变异（参考测试缺口，保留在分母中）", gaps))
    statuses = [m["reference_status"][0] for m in mutants.values()]
    timeouts = statuses.count("timeout")
    raw = statuses.count("killed") / (len(statuses) - timeouts) if len(statuses) > timeouts else None
    probe_mode = (task.get("preparation") or {}).get("probe_mode", "bounded_probe")
    out = [f"# {task_id} 变异复核清单", "",
           f"- 探针模式：`{probe_mode}`；变异 {len(mutants)} 个；参考测试原始检出率 "
           f"{'—' if raw is None else f'{raw:.3f}'}；分母口径 M1 {baseline['reference'].get('m1')}。",
           f"- 复核状态：`{baseline['review']['status']}`。复核方法见 docs/评测运行说明.md 第 3 节："
           "确认等价的保留在 `equivalent`，不等价的从 `equivalent` 删除（移回分母），并补参考测试。",
           "- 下表的变异后写法仅为源码位置示意，结论以实际 Mull IR 为准：同一位置可能对应多个调用，"
           "同一 ID 也可能对应多个内部变异，实际删除的可能是临时对象的析构。",
           "- 常量 42 对 bool 的效果须核对 IR 位宽及后续读取；例如 i8 存储后截成 i1 可得到 false，"
           "不能把它解释为标准 C++ 的 bool = 42。固定随机种子仍可能在长调用序列上区分变异。",
           "- 按 D011 检查原代码全部有定义的输入；题面限制、探针未覆盖、当前机器未崩溃均不能单独证明等价。", ""]
    counts = {}
    for title, ids in sections:
        counts[title] = len(ids)
        out += [f"## {title}：{len(ids)} 个", ""]
        if not ids:
            continue
        out += ["| 位置 | 算子 | 原始代码 | 变异后（源码示意） | 参考测试 | 探针 | 复核结论 |", "|---|---|---|---|---|---|---|"]
        for mutant_id in sorted(ids, key=lambda i: (LOCATION.match(i).group("path") if LOCATION.match(i) else i,
                                                    int(LOCATION.match(i).group("l1")) if LOCATION.match(i) else 0)):
            m = mutants.get(mutant_id, {})
            where, original, mutated = render(root, mutant_id)
            out.append(f"| {cell(where)} | {cell(m.get('mutator', ''))} | `{cell(original)}` | {cell(mutated)} "
                       f"| {cell('/'.join(m.get('reference_status', [])))} | {cell('/'.join(m.get('probe_status', [])))} |  |")
        out.append("")
    return {"task": task_id, "probe_mode": probe_mode, "mutants": len(mutants), "reference_raw_m1": raw,
            "counts": counts}, "\n".join(out)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--tasks", nargs="*", default=[])
    parser.add_argument("--all", action="store_true", help="所有已写入分母的题")
    parser.add_argument("--run-id", default=common.default_run_id("bank-review"))
    args = parser.parse_args()
    tasks = list(args.tasks)
    if args.all:
        tasks += [p.parent.name for p in sorted(common.BENCHMARK.glob("*/task.json"))
                  if common.load_baseline(common.load_task(p.parent.name)) is not None]
    tasks = list(dict.fromkeys(tasks))
    if not tasks:
        parser.error("没有要生成清单的题目")
    common.check_run_id(args.run_id)
    run_dir = common.RUNS / args.run_id
    if run_dir.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    manifest = new_manifest(args.run_id, "prepare", mode="mutant_review", tasks=tasks)
    write_manifest(run_dir, manifest)
    index = ["| 题目 | 探针模式 | 变异 | 原始检出率 | 等价候选 | 不稳定 | 探针超时 | 参考测试缺口 |", "|---|---|---|---|---|---|---|---|"]
    entries = []
    for task_id in tasks:
        entry, text = task_report(task_id)
        (run_dir / f"{task_id}.md").write_text(text, encoding="utf-8")
        if entry:
            entries.append(entry)
            c = list(entry["counts"].values())
            raw = "—" if entry["reference_raw_m1"] is None else f"{entry['reference_raw_m1']:.3f}"
            index.append(f"| [{task_id}]({task_id}.md) | {entry['probe_mode']} | {entry['mutants']} | {raw} "
                         f"| {c[0]} | {c[1]} | {c[2]} | {c[3]} |")
    (run_dir / "index.md").write_text("# 变异复核清单\n\n" + "\n".join(index) + "\n", encoding="utf-8")
    common.write_json(run_dir / "summary.json", {"run_id": args.run_id, "tasks": entries})
    finish(run_dir, manifest, "completed")
    print(f"清单：{run_dir / 'index.md'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
