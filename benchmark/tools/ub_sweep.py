#!/usr/bin/env python3
"""在固定 Linux 工具链上用 sanitizer 复核变异的源码副本，区分等价与“只在未定义行为下不同”（D015）。

对每个变异 ID，在被测源码副本上做对应的源码改动（比较/算术运算符、自增自减、把标量调用换成 42、把初值换成 42），
与驱动程序一起用固定 GCC 镜像中的 g++-14 -fsanitize=address,undefined -D_GLIBCXX_ASSERTIONS 编译运行，
与原代码的输出比较：输出相同且没有报告记为 same_output，报告未定义行为记为 undefined_behavior。
源码改动是对 Mull IR 变异的近似：运算符按变异 ID 的列范围逐字核对，无法用源码表达的变异记为 not_expressible。

用法（从项目根目录执行；默认在 Docker 中运行，证据写入 runs/<run-id>/）：
  python3 benchmark/tools/ub_sweep.py --task exercism-zebra-puzzle \\
      --driver benchmark/tools/ub_drivers/exercism-zebra-puzzle.cc --pending --run-id bank-ub-<编号> [--resolve]
--pending 选出 mutant_review 中标记了待 ub_sweep 复核的结论；--ids 可直接指定变异。
--resolve：结果与记录的结论一致（equivalent ↔ same_output，undefined_only ↔ undefined_behavior）时，清除 pending 并写入证据；
不一致的保留 pending，由复核人处理。--local <编译器> 只用于在本机检查脚本，结果不能作为固定工具链证据。
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(Path(__file__).resolve().parent), str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]

import bankutil  # noqa: E402

OPS = {"cxx_add_to_sub": ("+", "-"), "cxx_sub_to_add": ("-", "+"), "cxx_mul_to_div": ("*", "/"),
       "cxx_add_assign_to_sub_assign": ("+=", "-="),
       "cxx_eq_to_ne": ("==", "!="), "cxx_ne_to_eq": ("!=", "=="), "cxx_gt_to_ge": (">", ">="),
       "cxx_gt_to_le": (">", "<="), "cxx_ge_to_gt": (">=", ">"), "cxx_ge_to_lt": (">=", "<"),
       "cxx_lt_to_ge": ("<", ">="), "cxx_lt_to_le": ("<", "<="), "cxx_le_to_lt": ("<=", "<"), "cxx_le_to_gt": ("<=", ">"),
       "cxx_post_inc_to_post_dec": ("++", "--"), "cxx_pre_inc_to_pre_dec": ("++", "--")}
MARK = "ub_sweep.py"
RUNNER = r'''
import json, os, re, subprocess, sys
from pathlib import Path
spec = json.loads(Path("/out/spec.json").read_text())
cxx = os.environ.get("UB_SWEEP_CXX", "g++-14")
flags = ["-std=c++11", "-O0", "-g", "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
         "-fno-omit-frame-pointer", "-D_GLIBCXX_ASSERTIONS"] + ["-I" + d for d in spec["include_dirs"]]
ub = re.compile(r"AddressSanitizer|runtime error:|UndefinedBehaviorSanitizer|Assertion .* failed|libc\+\+ Hardening")
results = []
for v in spec["variants"]:
    work = Path(spec["out"]) / v["name"]
    sources = [str(work / Path(s).name) if s == v.get("mutated") else str(Path(spec["repo"]) / s) for s in spec["sources"]]
    exe = str(work / "a.out")
    build = subprocess.run([cxx] + flags + sources + [spec["driver"], "-o", exe], capture_output=True, text=True)
    r = {"name": v["name"], "id": v.get("id"), "compile_returncode": build.returncode, "compile_stderr": build.stderr[-1500:]}
    if build.returncode == 0:
        try:
            run = subprocess.run([exe], capture_output=True, text=True, timeout=60,
                                 env=dict(os.environ, ASAN_OPTIONS="detect_leaks=0"))
            r.update(returncode=run.returncode, stdout=run.stdout, stderr_head=run.stderr.strip().splitlines()[:4],
                     undefined=bool(ub.search(run.stderr)))
        except subprocess.TimeoutExpired:
            r["timed_out"] = True
    results.append(r)
    Path(spec["out"], "results.json").write_text(json.dumps(results, indent=1) + "\n")
'''


def mutate(text, mid):
    """在源码文本上做变异 ID 对应的改动；返回 (新文本, 改动后的行)。"""
    op, _, l1, c1, l2, c2 = mid.split(":")
    lines = text.split("\n")
    line, a, b = lines[int(l1) - 1], int(c1) - 1, int(c2) - 1
    if l1 != l2:
        raise ValueError("跨行的变异无法用源码表达")
    if op in OPS:
        old, new = OPS[op]
        if line[a:b] != old:
            raise ValueError(f"列范围内是 {line[a:b]!r}，不是 {old!r}")
        line = line[:a] + new + line[b:]
    elif op == "cxx_replace_scalar_call":
        start = a - 1
        if line[start] != "." or line[b:b + 1] != "(":
            raise ValueError("只支持 对象.方法(...) 形式的调用")
        while start > 0 and (line[start - 1].isalnum() or line[start - 1] == "_"):
            start -= 1
        depth, end = 0, b
        while True:
            depth += {"(": 1, ")": -1}.get(line[end], 0)
            end += 1
            if depth == 0:
                break
        line = line[:start] + "42" + line[end:]
    elif op == "cxx_init_const":
        eq = line.index("=", b)
        stop = min(i for i in (line.find(";", eq), line.find(",", eq)) if i >= 0)
        line = line[:eq + 1] + " 42" + line[stop:]
    else:
        raise ValueError(f"未支持的算子 {op}")
    lines[int(l1) - 1] = line
    return "\n".join(lines), line.strip()


def pending_ids(task_id):
    ids = [m["id"] for m in bankutil.load_equivalent(task_id).values() if MARK in (m.get("pending") or "")]
    ids += [m["id"] for m in bankutil.load_confirmed(task_id) if MARK in (m.get("pending") or "")]
    return sorted(set(ids))


def main():
    import common
    from audit import Audit
    from runs import finish, new_manifest, write_manifest
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--task", required=True)
    parser.add_argument("--driver", required=True, type=Path)
    parser.add_argument("--ids", nargs="*", default=[])
    parser.add_argument("--pending", action="store_true", help="复核 mutant_review 中标记待 ub_sweep 复核的结论")
    parser.add_argument("--resolve", action="store_true", help="结果与记录一致时清除 pending 并写入证据")
    parser.add_argument("--local", metavar="CXX", help="在本机用指定编译器运行（只检查脚本，不是固定工具链证据）")
    parser.add_argument("--run-id", required=True)
    args = parser.parse_args()
    task = common.load_task(args.task)
    ids = list(dict.fromkeys(args.ids + (pending_ids(task["id"]) if args.pending else [])))
    if not ids:
        parser.error("没有要复核的变异")
    if args.resolve and args.local:
        parser.error("--local 的结果不是固定工具链证据，不能用于 --resolve")
    common.check_run_id(args.run_id)
    run_dir = common.RUNS / args.run_id
    if run_dir.exists():
        parser.error("run-id 已使用；请使用新目录保留历史证据")
    image = common.read_json(common.CALIBRATION_STATUS)["images"]["gcc"]
    manifest = new_manifest(args.run_id, "prepare", mode="ub_sweep", task=task["id"], ids=ids,
                            image=None if args.local else image, local_compiler=args.local)
    write_manifest(run_dir, manifest)
    root = common.source_root(task)
    variants, skipped = [{"name": "original"}], []
    for i, mid in enumerate(ids):
        rel = mid.split(":")[1].removeprefix("/repo/")
        try:
            text, edited = mutate((root / rel).read_text(), mid)
        except (ValueError, IndexError) as error:
            skipped.append({"id": mid, "outcome": "not_expressible", "detail": str(error)})
            continue
        (run_dir / f"m{i:02d}").mkdir()
        (run_dir / f"m{i:02d}" / Path(rel).name).write_text(text)
        variants.append({"name": f"m{i:02d}", "id": mid, "mutated": rel, "edited_line": edited})
    (run_dir / "original").mkdir()
    shutil.copyfile(args.driver, run_dir / "driver.cc")
    (run_dir / "runner.py").write_text(RUNNER)
    local = bool(args.local)
    spec = {"variants": variants, "sources": task["target_sources"],
            "repo": str(root) if local else "/repo", "out": str(run_dir) if local else "/out",
            "driver": str(run_dir / "driver.cc") if local else "/out/driver.cc",
            "include_dirs": [str(root / d) if local else f"/repo/{d}" for d in task["include_dirs"]]}
    (run_dir / "spec.json").write_text(json.dumps(spec, ensure_ascii=False, indent=1) + "\n")
    audit = Audit(run_dir / "evidence")
    if local:
        runner = run_dir / "runner.py"
        runner.write_text(RUNNER.replace('Path("/out/spec.json")', f'Path({str(run_dir / "spec.json")!r})'))
        result = audit.run("sweep-local", [sys.executable, "-B", str(runner)], timeout=3600,
                           env=dict(os.environ, UB_SWEEP_CXX=args.local))
    else:
        result = audit.run("sweep", ["docker", "run", "--rm", "--network", "none", "--read-only", "--cpus", "1",
                                     "--memory", "2g", "--pids-limit", "128", "--cap-drop", "ALL",
                                     "--security-opt", "no-new-privileges", "--user", f"{os.getuid()}:{os.getgid()}",
                                     "--tmpfs", "/tmp:rw,nosuid,nodev,size=256m,mode=1777",
                                     "--mount", f"type=bind,source={root},target=/repo,readonly",
                                     "--mount", f"type=bind,source={run_dir},target=/out",
                                     image, "python3", "/out/runner.py"], timeout=3600)
    if result["returncode"] != 0 or not (run_dir / "results.json").is_file():
        finish(run_dir, manifest, "failed", error="扫描执行失败")
        raise SystemExit(f"扫描执行失败，见 {result['stderr_log']}")
    raw = {r["name"]: r for r in json.loads((run_dir / "results.json").read_text())}
    reference = raw.get("original", {})
    if reference.get("returncode") != 0 or reference.get("undefined"):
        finish(run_dir, manifest, "failed", error="原代码在 sanitizer 下没有正常结束")
        raise SystemExit("原代码在 sanitizer 下没有正常结束，扫描结论无效")
    report = list(skipped)
    for v in variants[1:]:
        r = raw[v["name"]]
        if r["compile_returncode"] != 0:
            outcome = "build_failed"
        elif r.get("timed_out"):
            outcome = "timeout"
        elif r["undefined"]:
            outcome = "undefined_behavior"
        elif r["returncode"] == 0:
            outcome = "same_output" if r["stdout"] == reference["stdout"] else "different_output"
        else:
            outcome = f"exit_{r['returncode']}"
        report.append({"id": v["id"], "outcome": outcome, "edited_line": v["edited_line"],
                       "stderr_head": r.get("stderr_head", [])})
    resolved = resolve(task["id"], report, args.run_id) if args.resolve else []
    (run_dir / "ub-sweep.json").write_text(json.dumps({"original_stdout": reference["stdout"], "results": report,
                                                       "resolved": resolved}, ensure_ascii=False, indent=1) + "\n")
    counts = {}
    for r in report:
        counts[r["outcome"]] = counts.get(r["outcome"], 0) + 1
    lines = [f"# {task['id']} 源码副本 sanitizer 复核", "",
             f"{'本机 ' + args.local + '（只检查脚本）' if local else '固定 GCC 镜像 ' + image[:19]}；"
             "参数 `-std=c++11 -O0 -g -fsanitize=address,undefined -fno-sanitize-recover=all -D_GLIBCXX_ASSERTIONS`。", "",
             f"结果：{json.dumps(counts, ensure_ascii=False)}；清除 pending {len(resolved)} 项。", "",
             "| 变异 ID | 结果 | 改动后的行 |", "|---|---|---|"]
    lines += [f"| `{r['id']}` | {r['outcome']} | `{r.get('edited_line', r.get('detail', ''))[:80]}` |" for r in report]
    (run_dir / "ub-sweep.md").write_text("\n".join(lines) + "\n")
    print("\n".join(lines[:5]))
    finish(run_dir, manifest, "completed", passed=True)
    return 0


def resolve(task_id, report, run_id):
    """结果与记录的结论一致时清除 pending，并把本次运行加入证据。"""
    outcome = {r["id"]: r["outcome"] for r in report}
    evidence = [f"runs/{run_id}/ub-sweep.md", f"runs/{run_id}/ub-sweep.json"]
    resolved = []
    for name, expected in (("equivalent.json", "same_output"), ("confirmed.json", "undefined_behavior")):
        path = bankutil.MUTANT_REVIEW / task_id / name
        if not path.is_file():
            continue
        data = json.loads(path.read_text(encoding="utf-8"))
        for m in data["mutants"]:
            if MARK in (m.get("pending") or "") and outcome.get(m["id"]) == expected:
                if name == "confirmed.json" and m["verdict"] != "undefined_only":
                    continue
                m.pop("pending")
                m["evidence"] = m["evidence"] + evidence
                resolved.append(m["id"])
        path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    return resolved


if __name__ == "__main__":
    raise SystemExit(main())
