#!/usr/bin/env python3
"""查看 Mull 变异在固定 Clang/Mull 工具链 IR 中实际改了什么，作为复核证据。

Mull 的 IR 前端把每个变异编译成一个以变异 ID 命名的函数副本（同一 ID 有多个内部变异时副本名加 .N 后缀），
原函数改为分发函数：按 getenv(变异 ID) 依次检查，命中第一个就调用该副本，否则调用 mull_<原名>_original。
因此同一 ID 的多个副本中只有最先被检查到的会生效。本工具找出每个 ID 生效的副本，并列出它与原始函数相比
删去和增加的调用（例如“删除调用”实际删掉的是哪个析构函数）。

用法（从项目根目录执行）：
  # Docker 机器：用校准状态中记录的 Clang 镜像导出 IR 并分析，证据写入 runs/<run-id>/
  python3 benchmark/tools/mutant_ir.py emit --task exercism-series \\
      --ids 'cxx_remove_void_call:/repo/src/series.cpp:32:9:32:69' --run-id bank-ir-<编号> [--resolve]
  # --pending：选出 mutant_review 中标记了待 mutant_ir 核对的结论；--resolve：生效副本只删去析构调用、
  # 没有新增调用时，清除该结论的 pending 并写入证据（只适用于“删除调用”的等价结论）
  # 任意机器：分析已导出的 IR 文件
  python3 benchmark/tools/mutant_ir.py analyze --ll <文件.ll> --ids '<变异 ID>' ...
编译参数与评分时的 Mull 构建一致：-std=c++11 -O0 -g -include cxx11_guard.h -grecord-command-line
-fpass-plugin=/usr/lib/mull-ir-frontend-19，Mull 配置由 task.json 生成。
"""
import argparse
import collections
import json
import os
from pathlib import Path
import re
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]

NAME = r'("(?:[^"\\]|\\.)*"|[\w.$-]+)'
DEFINE = re.compile(r"^define\b.*?@" + NAME + r"\(")
STRING = re.compile(r'^@([\w.$-]+) = .*?constant \[\d+ x i8\] c"((?:[^"\\]|\\.)*)"')
LABEL = re.compile(r"^([\w.$-]+):")
GETENV = re.compile(r"call ptr @getenv\(ptr @([\w.$-]+)\)")
BRANCH = re.compile(r"br i1 %[\w.$-]+, label %([\w.$-]+), label %([\w.$-]+)")
STORE = re.compile(r"store ptr @" + NAME + r", ptr")
CALL = re.compile(r"\b(?:call|invoke)\b[^@]*?@" + NAME + r"\(")


def unquote(name):
    return name[1:-1] if name.startswith('"') else name


def decode(text):
    return re.sub(r"\\([0-9A-Fa-f]{2})", lambda m: chr(int(m.group(1), 16)), text).rstrip("\0")


def parse(path):
    """返回 ({函数名: 函数体行}, {字符串常量名: 文本})。"""
    functions, strings, current = {}, {}, None
    for line in Path(path).read_text(errors="replace").splitlines():
        if current is None:
            m = DEFINE.match(line)
            if m:
                current = unquote(m.group(1))
                functions[current] = []
                continue
            m = STRING.match(line)
            if m:
                strings[m.group(1)] = decode(m.group(2))
        elif line == "}":
            current = None
        else:
            functions[current].append(line)
    return functions, strings


def blocks(body):
    """把函数体拆成 {块标签: 行}；入口块的标签记为 entry。"""
    result, label = {"entry": []}, "entry"
    for line in body:
        m = LABEL.match(line)
        if m:
            label = m.group(1)
            result[label] = []
        else:
            result[label].append(line)
    return result


def dispatch_order(body, strings):
    """分发函数中各副本的检查顺序：[(变异 ID, 副本名)]，排在前面的先被检查。"""
    parts, checks = blocks(body), {}
    for label, lines in parts.items():
        text = "\n".join(lines)
        env, branch = GETENV.search(text), BRANCH.search(text)
        if env and branch:
            store = STORE.search("\n".join(parts.get(branch.group(1), [])))
            if store:
                checks[label] = (strings.get(env.group(1)), unquote(store.group(1)), branch.group(2))
    targets = {false for _, _, false in checks.values()}
    heads = [label for label in checks if label not in targets]
    order, seen = [], set()
    for head in heads:
        label = head
        while label in checks and label not in seen:
            seen.add(label)
            mutant_id, clone, label = checks[label]
            order.append((mutant_id, clone))
    return order


def calls(lines):
    return collections.Counter(n for n in (unquote(m.group(1)) for line in lines for m in CALL.finditer(line))
                               if not n.startswith("llvm."))


def analyze(path, ids):
    functions, strings = parse(path)
    found = {}
    for name, body in functions.items():
        if name.startswith("mull_") or ":" in name:
            continue
        for position, (mutant_id, clone) in enumerate(dispatch_order(body, strings)):
            found.setdefault(mutant_id, []).append((name, position, clone))
    report = []
    for mutant_id in ids:
        entries = sorted(found.get(mutant_id, []), key=lambda e: e[1])
        if not entries:
            report.append({"id": mutant_id, "problem": "IR 中没有找到该变异的分发检查"})
            continue
        dispatcher, _, active = entries[0]
        original = functions.get(f"mull_{dispatcher}_original")
        if original is None or active not in functions:
            report.append({"id": mutant_id, "dispatcher": dispatcher, "active": active,
                           "problem": "找不到原始函数或生效副本"})
            continue
        before, after = calls(original), calls(functions[active])
        report.append({"id": mutant_id, "dispatcher": dispatcher, "copies": [e[2] for e in entries], "active": active,
                       "removed_calls": dict(before - after), "added_calls": dict(after - before), "ir": str(path)})
    return report


def demangle(names):
    import shutil
    import subprocess
    tool = shutil.which("c++filt") or shutil.which("llvm-cxxfilt")
    if not tool or not names:
        return {}
    out = subprocess.run([tool], input="\n".join(names), capture_output=True, text=True).stdout.splitlines()
    return dict(zip(names, out)) if len(out) == len(names) else {}


def emit(args):
    import common
    from audit import Audit
    from runs import finish, new_manifest, write_manifest
    common.check_run_id(args.run_id)
    run_dir = common.RUNS / args.run_id
    if run_dir.exists():
        raise SystemExit("run-id 已使用；请使用新目录保留历史证据")
    task = common.load_task(args.task)
    if args.pending:
        import bankutil
        args.ids = list(dict.fromkeys(args.ids + sorted(m["id"] for m in bankutil.load_equivalent(task["id"]).values()
                                                         if "mutant_ir.py" in (m.get("pending") or ""))))
    if not args.ids:
        raise SystemExit("没有要核对的变异")
    image = common.read_json(common.CALIBRATION_STATUS)["images"]["clang"]
    manifest = new_manifest(args.run_id, "prepare", mode="mutant_ir", task=task["id"], ids=args.ids, image=image)
    write_manifest(run_dir, manifest)
    (run_dir / "mull.yml").write_text(common.mull_config_text(task))
    audit = Audit(run_dir / "evidence")
    sources = sorted({i.split(":")[1].removeprefix("/repo/") for i in args.ids})
    report = []
    for source in sources:
        out = run_dir / (Path(source).name + ".ll")
        command = ["docker", "run", "--rm", "--network", "none", "--read-only", "--cpus", "1", "--memory", "1g",
                   "--pids-limit", "256", "--cap-drop", "ALL", "--security-opt", "no-new-privileges",
                   "--user", f"{os.getuid()}:{os.getgid()}", "--tmpfs", "/tmp:rw,nosuid,nodev,size=256m,mode=1777",
                   "--mount", f"type=bind,source={common.source_root(task)},target=/repo,readonly",
                   "--mount", f"type=bind,source={common.ASSESSMENT / 'cmake'},target=/assessment,readonly",
                   "--mount", f"type=bind,source={run_dir},target=/out", "-e", "MULL_CONFIG=/out/mull.yml", image,
                   "clang++-19", "-std=c++11", "-O0", "-g", "-include", "/assessment/cxx11_guard.h",
                   "-grecord-command-line", "-fpass-plugin=/usr/lib/mull-ir-frontend-19", "-S", "-emit-llvm",
                   *[f"-I/repo/{d}" for d in task["include_dirs"]], f"/repo/{source}", "-o", f"/out/{out.name}"]
        result = audit.run(f"emit-{Path(source).name}", command, timeout=300)
        if result["returncode"] != 0:
            finish(run_dir, manifest, "failed", error=f"导出 {source} 的 IR 失败")
            raise SystemExit(f"导出 {source} 的 IR 失败，见 {result['stderr_log']}")
        report += analyze(out, [i for i in args.ids if f"/repo/{source}:" in i])
    resolved = resolve(task["id"], report, args.run_id) if args.resolve else []
    write_report(run_dir, report, resolved)
    finish(run_dir, manifest, "completed", passed=all("problem" not in r for r in report))
    return 0 if all("problem" not in r for r in report) else 1


DESTRUCTOR = re.compile(r"D[012]Ev$")


def relative(path):
    try:
        return str(Path(path).resolve().relative_to(REPO))
    except ValueError:
        return str(path)


def resolve(task_id, report, run_id):
    """“删除调用”的等价结论：生效副本只删去析构调用、没有新增调用时清除 pending，并把本次 IR 加入证据。"""
    import bankutil
    ok = {r["id"]: r for r in report if "problem" not in r and r["removed_calls"] and not r["added_calls"]
          and all(DESTRUCTOR.search(name) for name in r["removed_calls"])}
    path = bankutil.MUTANT_REVIEW / task_id / "equivalent.json"
    if not path.is_file():
        return []
    data = json.loads(path.read_text(encoding="utf-8"))
    resolved = []
    for m in data["mutants"]:
        if m["id"] in ok and "mutant_ir.py" in (m.get("pending") or ""):
            m.pop("pending")
            m["evidence"] = m["evidence"] + [f"runs/{run_id}/mutant-ir.md", f"runs/{run_id}/mutant-ir.json",
                                             relative(ok[m["id"]]["ir"])]
            resolved.append(m["id"])
    path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    return resolved


def write_report(run_dir, report, resolved=()):
    names = sorted({n for r in report for k in ("removed_calls", "added_calls") for n in r.get(k, {})})
    readable = demangle(names)
    for r in report:
        for key in ("removed_calls", "added_calls"):
            if key in r:
                r[key + "_demangled"] = {readable.get(n, n): c for n, c in r[key].items()}
    (Path(run_dir) / "mutant-ir.json").write_text(json.dumps({"results": report, "resolved": list(resolved)},
                                                             ensure_ascii=False, indent=1) + "\n")
    lines = ["# 变异的实际 IR 改动", "", "| 变异 ID | 生效副本 | 删去的调用 | 增加的调用 |", "|---|---|---|---|"]
    for r in report:
        fmt = lambda d: "；".join(f"{k} ×{v}" for k, v in d.items()) or "—"
        lines.append(f"| `{r['id']}` | {r.get('active', '—')} | "
                     f"{r.get('problem') or fmt(r.get('removed_calls_demangled', {}))} | {fmt(r.get('added_calls_demangled', {}))} |")
    (Path(run_dir) / "mutant-ir.md").write_text("\n".join(lines) + "\n")
    print("\n".join(lines))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    e = sub.add_parser("emit", help="在固定 Clang/Mull 镜像中导出 IR 并分析（需要 Docker）")
    e.add_argument("--task", required=True)
    e.add_argument("--ids", nargs="*", default=[])
    e.add_argument("--pending", action="store_true", help="核对 mutant_review 中标记待 mutant_ir 核对的结论")
    e.add_argument("--resolve", action="store_true", help="只删去析构调用时清除 pending 并写入证据")
    e.add_argument("--run-id", required=True)
    a = sub.add_parser("analyze", help="分析已导出的 IR 文件")
    a.add_argument("--ll", required=True, type=Path)
    a.add_argument("--ids", nargs="+", required=True)
    args = parser.parse_args()
    if args.command == "emit":
        return emit(args)
    report = analyze(args.ll, args.ids)
    print(json.dumps(report, ensure_ascii=False, indent=1))
    return 0 if all("problem" not in r for r in report) else 1


if __name__ == "__main__":
    raise SystemExit(main())
