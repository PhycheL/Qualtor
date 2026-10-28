#!/usr/bin/env python3
"""题目准入（R-08）：核对准入条件，由复核人签署分母并登记到 benchmark/admission.json。

准入条件（docs/题库构建方案.md 第 4 节）：
1. 题目包能加载、源码哈希一致，可见文件都在源码目录内；有变异分母，参考强测试集达到阈值；
2. mutant_review/<题目 ID>/confirmed.json 的复核结论都已落实到分母；
3. 分母中每个等价候选都在 mutant_review/<题目 ID>/equivalent.json 中有等价结论，且结论没有标记 pending（待补证据）。
不稳定、探针超时和参考测试缺口不阻止准入，数量写进登记记录。编译、确定性运行与参考强度
由 Docker 标定（prepare_new_tasks.py）保证，本脚本只核对其结果，不重新执行测试。

用法（任意机器，从项目根目录执行；只读写 JSON，不需要 Docker）：
  python3 benchmark/tools/admit.py                                    # 列出全部题目的核对结果
  python3 benchmark/tools/admit.py --tasks <题目 ID>... --by <复核人> --write
  python3 benchmark/tools/admit.py --ready --by <复核人> --write        # 签署并准入全部可签署的题
写入时把分母的 review 改为 reviewed（填 by、at、note），并登记题目指纹。之后题目材料或分母变化，
指纹不再一致，准入自动失效（runner 与汇总按 stale 处理），需要重新签署。review 字段不计入指纹。
"""
import argparse
import datetime as dt
from pathlib import Path
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(Path(__file__).resolve().parent), str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]

import bankutil  # noqa: E402
import common  # noqa: E402

NOTE = "已准入题目清单（R-08）：正式比较只用这里登记、且当前题目指纹与登记时一致的题目。由 benchmark/tools/admit.py 写入。"


def check(task_id):
    """返回 (问题清单, 摘要)。问题为空表示可以签署。"""
    try:
        task = common.load_task(task_id)
    except common.TaskError as error:
        return [f"题目包无效：{error}"], {}
    root = common.source_root(task)
    problems = []
    for rel in task.get("visible", {}).get("files", []):
        path = (root / rel).resolve()
        if not path.is_file() or not path.is_relative_to(root):
            problems.append(f"可见文件不在源码目录内：{rel}")
    baseline = common.load_baseline(task)
    if baseline is None:
        return problems + ["没有变异分母，先在 Docker 中标定"], {}
    statuses = [m["reference_status"][0] for m in baseline["mutants"]]
    timeouts = statuses.count("timeout")
    info = {"mutants": len(baseline["mutants"]), "equivalent": len(baseline["equivalent"]),
            "unstable": len(baseline["unstable"]), "review_needed": len(baseline.get("review_needed", [])),
            "confirmed_non_equivalent": len(baseline.get("confirmed_non_equivalent", [])),
            "reference_m1": baseline["reference"]["m1"],
            "reference_raw_m1": statuses.count("killed") / (len(statuses) - timeouts) if len(statuses) > timeouts else None,
            "review": baseline["review"]["status"]}
    if not baseline["reference"]["passes"]:
        problems.append(f"参考强测试集 M1 = {baseline['reference']['m1']}，低于阈值")
    _, pending, review_problems = bankutil.apply_confirmed(baseline, task_id)
    problems += review_problems
    if pending:
        problems.append(f"{len(pending)} 项复核结论尚未落实到分母（apply_review.py --write）")
    open_ids, pending = bankutil.review_gaps(baseline, task_id)
    for ids, label in ((open_ids, "个等价候选没有等价结论"), (pending, "项结论标记为待补证据")):
        if ids:
            problems.append(f"{len(ids)} {label}：" + "、".join(i.split("/src/")[-1] for i in ids[:5])
                            + ("……" if len(ids) > 5 else ""))
    return problems, info


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--tasks", nargs="*", default=[])
    parser.add_argument("--ready", action="store_true", help="只处理核对通过、可以签署的题")
    parser.add_argument("--by", help="复核人；--write 时必填")
    parser.add_argument("--note", default="", help="签署说明，写入分母 review.note 与准入记录")
    parser.add_argument("--write", action="store_true", help="签署分母并登记准入")
    args = parser.parse_args()
    if args.write and not (args.by or "").strip():
        parser.error("--write 需要 --by <复核人>")
    tasks = args.tasks or sorted(p.parent.name for p in common.BENCHMARK.glob("*/task.json"))
    admitted = common.load_admission()
    results = {task_id: check(task_id) for task_id in tasks}
    states = {task_id: common.admission_state(task_id, common.task_sha256(common.load_task(task_id)), admitted)["status"]
              if info else "not_admitted" for task_id, (_, info) in results.items()}
    ready = [t for t, (problems, _) in results.items() if not problems]
    chosen = ready if args.ready else tasks
    fmt = lambda v: "—" if v is None else f"{v:.3f}"
    for task_id in chosen:
        problems, info = results[task_id]
        print(f"{task_id}：{'可签署' if not problems else '未就绪'}；准入状态 {states[task_id]}"
              + (f"；变异 {info['mutants']}，等价候选 {info['equivalent']}，不稳定 {info['unstable']}，"
                 f"参考 M1 {fmt(info['reference_m1'])}，原始检出率 {fmt(info['reference_raw_m1'])}" if info else ""))
        for problem in problems:
            print(f"  - {problem}")
    print(f"共 {len(tasks)} 道：可签署 {len(ready)}，未就绪 {len(tasks) - len(ready)}；"
          f"已准入且指纹一致 {sum(1 for t in tasks if states[t] == 'admitted')}")
    if not args.write:
        return 0 if all(not results[t][0] for t in chosen) else 1
    blocked = [t for t in chosen if results[t][0]]
    if blocked:
        parser.error("以下题目未就绪，不能签署：" + "、".join(blocked))
    today = dt.date.today().isoformat()
    record = common.read_json(common.ADMISSION) if common.ADMISSION.is_file() else {"schema": 1, "note": NOTE, "tasks": {}}
    for task_id in chosen:
        task = common.load_task(task_id)
        baseline = common.load_baseline(task)
        info = results[task_id][1]
        note = args.note or (f"按 benchmark/tools/mutant_review/{task_id}/ 的复核结论签署：等价候选 {info['equivalent']} 项均有结论，"
                             f"不稳定 {info['unstable']} 项按规则剔除，探针超时 {info['review_needed']} 项保留在分母中。")
        baseline["review"] = {"status": "reviewed", "by": args.by, "at": today, "note": note}
        common.write_json(common.hidden_path(task, "mutation_baseline"), baseline)
        record["tasks"][task_id] = {"task_sha256": common.task_sha256(task), "admitted_at": common.now(), "by": args.by,
                                    "note": note, "reference": baseline["reference"],
                                    "reference_raw_m1": info["reference_raw_m1"],
                                    "counts": {k: info[k] for k in ("mutants", "equivalent", "unstable", "review_needed",
                                                                     "confirmed_non_equivalent")}}
        print(f"已签署并准入：{task_id}")
    record["tasks"] = dict(sorted(record["tasks"].items()))
    common.write_json(common.ADMISSION, record)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
