#!/usr/bin/env python3
"""把 Emily Bache 的 C++ kata 转换为题目包（Tennis ×6、Yatzy、Parrot、SupermarketReceipt、Theatrical Players、
Racing-Car ×5）。

参考测试来源：
- Tennis、Yatzy：上游 GoogleTest 测试（只把函数声明换成头文件引用）+ 生成器记录的实际结果；
- Parrot：上游测试改写为 C++11（kata_tests/parrot-refactoring/）+ 生成器记录的实际结果；
- 其余：kata_tests/<题目 ID>/ 下手写的参考测试，探针为参考测试副本。
Tennis 与 Parrot 的探针按 import_humaneval_x.py 的方式生成（子进程隔离、消毒器过滤、两遍比对、GCC 回放）；
Yatzy 穷举 7776 种骰子组合生成表格探针。TirePressureMonitoring 不编译 Sensor.cpp，测试须自行提供 Sensor 的链接替身。

用法（从项目根目录执行）：
  python3 benchmark/tools/build_katas.py --repos <仓库清单.json> --gcc g++-14 --gcc-gtest <GoogleTest 前缀> [--force]
仓库清单格式：{"Tennis-Refactoring-Kata": {"path": "<解压目录>", "commit": "<提交号>"}, ...}，六个仓库都要有。
"""
import argparse
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import bankutil  # noqa: E402
import import_humaneval_x as gen  # noqa: E402

TOOLS = Path(__file__).resolve().parent
TESTS = TOOLS / "kata_tests"
GENERATORS = TOOLS / "kata_generators"
REFERENCE_DOMAIN = "参考测试覆盖的输入；未单独界定评分输入域，探针即参考测试。"


def create(args, task_id, repo_name, files, *, targets, include_dirs, visible, tier, tags, title, description,
           existing_tests, scoring_domain, probe_mode, notes, added=None):
    root, commit = Path(args.repos[repo_name]["path"]), args.repos[repo_name]["commit"]
    task_dir = bankutil.reset_task_dir(task_id, args.force)
    for dst, src in files.items():
        bankutil.copy_file(root / src, task_dir / "source" / dst)
    for dst, text in (added or {}).items():
        bankutil.write_text(task_dir / "source" / dst, text)
    bankutil.copy_file(root / "license.txt", task_dir / "source" / "LICENSE")
    provenance = {"repository": f"https://github.com/emilybache/{repo_name}", "commit": commit, "license": "MIT",
                  "upstream_paths": dict(sorted(files.items())), "added_by_qualtor": sorted(added or {})}
    meta = dict(task_id=task_id, tier=tier, tags=tags, title=title, description=description, provenance=provenance,
                source_files=sorted(set(files) | set(added or {}) | {"LICENSE"}), target_sources=targets,
                include_dirs=include_dirs, visible_files=sorted(visible), existing_tests=existing_tests,
                scoring_domain=scoring_domain, probe_mode=probe_mode, generated_by="benchmark/tools/build_katas.py")
    readme = [f"# {task_id} 隐藏材料", "", f"- 被测代码：emilybache/{repo_name} 提交 `{commit}`；"
              f"文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。"]
    readme += [f"- {line}" for line in notes]
    note = bankutil.review_note(task_id)
    if note:
        readme.append(f"- {note}")
    readme.append(f"- 探针：{bankutil.PROBE_MODES[probe_mode]}")
    readme.append("- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。")
    return task_dir, meta, readme


def finish(task_dir, meta, readme):
    bankutil.write_text(task_dir / "hidden" / "README.md", "\n".join(readme) + "\n")
    bankutil.write_task(task_dir, **meta)
    return meta["task_id"]


def copy_tests(task_dir, task_id):
    ref = task_dir / bankutil.HIDDEN["reference_tests"]
    for path in sorted((TESTS / task_id).glob("*.cc")):
        bankutil.copy_file(path, ref / path.name)


def generated_probe(task_dir, sources, generator, header, args):
    """Tennis/Parrot：运行探针生成器，前若干个结果进参考测试，其余进探针；GCC 回放删去不一致的断言。"""
    gen_dir = task_dir / "hidden" / "equivalence_probe"
    gen_dir.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(GENERATORS / generator, gen_dir / "generate_probe.cc")
    shutil.copyfile(TOOLS / "probe_prelude.h", gen_dir / "probe_prelude.h")
    ref = task_dir / bankutil.HIDDEN["reference_tests"]
    problems = []
    with tempfile.TemporaryDirectory(prefix=f"{task_dir.name}-") as tmp:
        tmp = Path(tmp)
        cases = gen.generate_cases(task_dir, gen_dir, sources, args, tmp)
        for _ in range(4):
            first, rest, seen = [], [], {}
            for case in cases:
                seen[case[0]] = seen.get(case[0], 0) + 1
                (first if seen[case[0]] <= gen.REFERENCE_CASES else rest).append(case)
            ref_lines = gen.write_cases(ref / "characterization_tests.cc", header, "Characterization", first)
            probe_lines = gen.write_cases(tmp / "probe_tests.cc", header, "Probe", rest)
            tests = sorted(ref.glob("*.cc")) + [tmp / "probe_tests.cc"]
            failures = gen.gcc_replay(task_dir, sources, tests, args, tmp)
            upstream = {k: v for k, v in failures.items() if k not in ("characterization_tests.cc", "probe_tests.cc")}
            if upstream:
                problems.append(f"上游或手写参考测试在 GCC 下失败：{upstream}")
            bad = {ref_lines[n] for n in failures.get("characterization_tests.cc", ()) if n in ref_lines}
            bad |= {probe_lines[n] for n in failures.get("probe_tests.cc", ()) if n in probe_lines}
            if not bad:
                break
            cases = [c for c in cases if c not in bad]
        bankutil.copy_reference_as_probe(task_dir, [tmp / "probe_tests.cc"])
    return len(cases), problems


def build_tennis(args):
    root = Path(args.repos["Tennis-Refactoring-Kata"]["path"])
    upstream = (root / "cpp/gtest_all.cpp").read_text(encoding="utf-8")
    declaration = "const std::string tennis_score(int p1Score, int p2Score);"
    if declaration not in upstream:
        raise SystemExit("上游 Tennis 测试的函数声明已变化")
    built = []
    for n in (1, 2, 3, 4, 6, 7):
        code = (root / f"cpp/tennis{n}.cc").read_text(encoding="utf-8")
        ret = re.search(r"^((?:const\s+)?std::string)\s+tennis_score\s*\(", code, re.M).group(1)
        header = ("// 由 Qualtor 添加：上游 tennis{0}.cc 没有头文件，这里按其定义声明 tennis_score，供测试包含。\n"
                  "#ifndef TENNIS_H\n#define TENNIS_H\n\n#include <string>\n\n{1} tennis_score(int p1Score, int p2Score);\n\n"
                  "#endif  // TENNIS_H\n").format(n, ret)
        task_id = f"tennis-refactoring-{n}"
        task_dir, meta, readme = create(
            args, task_id, "Tennis-Refactoring-Kata", {f"src/tennis{n}.cc": f"cpp/tennis{n}.cc"},
            added={"src/tennis.h": header}, targets=[f"src/tennis{n}.cc"], include_dirs=["src"],
            visible=[f"src/tennis{n}.cc", "src/tennis.h"], tier="easy", tags=["kata", "upstream_tests"],
            title=f"网球计分 tennis{n} 单元测试",
            description=f"Tennis Refactoring Kata 的第 {n} 种实现；上游 GoogleTest 测试与生成器记录的实际结果作参考测试。公开代码，开发题。",
            existing_tests={"available": True, "note": "上游 cpp/gtest_all.cpp 已作参考测试（只把函数声明换成 tennis.h），对 Agent 不可见。"},
            scoring_domain="两名选手 0–15 分的全部组合，排除触发未定义行为、崩溃或超时的组合。", probe_mode="generated",
            notes=["`src/tennis.h` 由 Qualtor 添加，只声明上游已有的 `tennis_score`。",
                   "参考测试：`upstream_tennis_tests.cc` 为上游 33 个用例；`characterization_tests.cc` 为生成器记录的前 12 个组合。"])
        ref = task_dir / bankutil.HIDDEN["reference_tests"]
        bankutil.write_text(ref / "upstream_tennis_tests.cc",
                            "// 上游 cpp/gtest_all.cpp，只把 tennis_score 的声明换成 tennis.h；隐藏材料。\n"
                            + upstream.replace(declaration, '#include "tennis.h"'))
        count, problems = generated_probe(task_dir, [task_dir / f"source/src/tennis{n}.cc"], "tennis_probe.cc", "tennis.h", args)
        built.append((finish(task_dir, meta, readme), count, problems))
    return built


def build_yatzy(args):
    root = Path(args.repos["Yatzy-Refactoring-Kata"]["path"])
    task_dir, meta, readme = create(
        args, "yatzy-refactoring", "Yatzy-Refactoring-Kata",
        {"src/yatzy1.cpp": "cpp/src/yatzy1.cpp", "src/yatzy1.hpp": "cpp/src/yatzy1.hpp"},
        targets=["src/yatzy1.cpp"], include_dirs=["src"], visible=["src/yatzy1.cpp", "src/yatzy1.hpp"], tier="easy",
        tags=["kata", "upstream_tests"], title="Yatzy 计分单元测试",
        description="Yatzy Refactoring Kata 的 yatzy1 实现；上游 GoogleTest 测试与穷举记录的实际结果作参考测试。公开代码，开发题。",
        existing_tests={"available": True, "note": "上游 cpp/test-gtest/sample_gtest.cpp 已原样作参考测试，对 Agent 不可见。"},
        scoring_domain="5 个骰子各为 1–6 的全部 7776 种组合。", probe_mode="generated",
        notes=["参考测试：`sample_gtest.cpp` 为上游 15 个用例；`characterization_tests.cc` 为每 97 种组合取 1 种的全部计分结果。",
               "探针：`probe_tests.cc` 穷举全部 7776 种组合，由 `equivalence_probe/generate_probe.cc` 生成。"])
    ref = task_dir / bankutil.HIDDEN["reference_tests"]
    bankutil.copy_file(root / "cpp/test-gtest/sample_gtest.cpp", ref / "sample_gtest.cpp")
    gen_dir = task_dir / "hidden" / "equivalence_probe"
    bankutil.copy_file(GENERATORS / "yatzy_probe.cc", gen_dir / "generate_probe.cc")
    with tempfile.TemporaryDirectory(prefix="yatzy-") as tmp:
        binary = Path(tmp) / "gen"
        built = subprocess.run([args.gcc, "-std=c++11", "-O0", f"-I{task_dir / 'source/src'}", str(gen_dir / "generate_probe.cc"),
                                str(task_dir / "source/src/yatzy1.cpp"), "-o", str(binary)], capture_output=True, text=True)
        if built.returncode != 0:
            raise RuntimeError(built.stderr[-2000:])
        for mode, path in (("sample", ref / "characterization_tests.cc"), ("probe", Path(tmp) / "probe_tests.cc")):
            subprocess.run([str(binary), mode, str(path)], check=True)
        bankutil.copy_reference_as_probe(task_dir, [Path(tmp) / "probe_tests.cc"])
    return [(finish(task_dir, meta, readme), 7776, [])]


def build_parrot(args):
    task_dir, meta, readme = create(
        args, "parrot-refactoring", "Parrot-Refactoring-Kata",
        {"src/Parrot.cpp": "cpp/src/Parrot.cpp", "src/Parrot.h": "cpp/src/Parrot.h"},
        targets=["src/Parrot.cpp"], include_dirs=["src"], visible=["src/Parrot.cpp", "src/Parrot.h"], tier="easy",
        tags=["kata", "upstream_tests"], title="Parrot 速度与叫声单元测试",
        description="Parrot Refactoring Kata；上游测试改写为 C++11，加生成器记录的实际结果作参考测试。公开代码，开发题。",
        existing_tests={"available": True, "note": "上游 test-gtest 用了 C++14 的 make_unique，已改写为 C++11 作参考测试，对 Agent 不可见。"},
        scoring_domain="三种鹦鹉 × 椰子 0–5 × 电压 {0, 0.5, 1, 1.5, 2, 2.5, 3, 4} × 是否被钉住。", probe_mode="generated",
        notes=["参考测试：`parrot_tests.cc` 改写自上游；`characterization_tests.cc` 为生成器记录的前 12 个输入。"])
    copy_tests(task_dir, "parrot-refactoring")
    count, problems = generated_probe(task_dir, [task_dir / "source/src/Parrot.cpp"], "parrot_probe.cc", "Parrot.h", args)
    return [(finish(task_dir, meta, readme), count, problems)]


def build_handwritten(args, task_id, repo_name, files, targets, include_dirs, visible, tier, tags, title, description,
                      existing_tests, notes):
    task_dir, meta, readme = create(
        args, task_id, repo_name, files, targets=targets, include_dirs=include_dirs, visible=visible, tier=tier, tags=tags,
        title=title, description=description, existing_tests=existing_tests, scoring_domain=REFERENCE_DOMAIN,
        probe_mode="reference_copy", notes=["参考测试：`kata_tests/" + task_id + "/` 下手写，断言为原代码的实际运行结果。"] + notes)
    copy_tests(task_dir, task_id)
    bankutil.copy_reference_as_probe(task_dir)
    return finish(task_dir, meta, readme)


def build_others(args):
    root = Path(args.repos["SupermarketReceipt-Refactoring-Kata"]["path"])
    names = sorted(p.name for p in (root / "cpp/src").iterdir() if p.suffix in (".cpp", ".h") and not p.stem == "sample")
    built = [build_handwritten(
        args, "supermarket-receipt", "SupermarketReceipt-Refactoring-Kata", {f"src/{n}": f"cpp/src/{n}" for n in names},
        [f"src/{n}" for n in names if n.endswith(".cpp")], ["src"], [f"src/{n}" for n in names], "medium",
        ["kata", "multi_file"], "超市小票与优惠单元测试",
        "SupermarketReceipt Refactoring Kata：商品目录、购物车、四种优惠与小票打印。公开代码，开发题。",
        {"available": False, "note": "上游 GoogleTest 只有一个依赖 ApprovalTests 的样例，未采用。"},
        ["`ReceiptPrinter` 的逻辑写在头文件里，当前流水线不会对它做变异（R-06），测试照常覆盖。"])]
    built.append(build_handwritten(
        args, "theatrical-players-statement", "Theatrical-Players-Refactoring-Kata",
        {"src/statement.cpp": "cpp/statement.cpp", "src/statement.h": "cpp/statement.h", "third_party/json.hpp": "cpp/third_party/json.hpp"},
        ["src/statement.cpp"], ["src", "third_party"], ["src/statement.cpp", "src/statement.h", "third_party/json.hpp"],
        "medium", ["kata", "third_party_header"], "剧团账单 statement 单元测试",
        "Theatrical Players Refactoring Kata：按剧目类型与观众人数计算账单金额与积分，依赖随仓库提供的 nlohmann/json 3.11.3。公开代码，开发题。",
        {"available": False, "note": "上游测试依赖 ApprovalTests，未采用。"},
        ["`third_party/json.hpp` 是 header-only 第三方库，随源码入库并对 Agent 可见；不链接任何库。"]))
    racing = Path(args.repos["Racing-Car-Katas"]["path"])
    specs = [
        ("racing-car-leaderboard", "LeaderBoard", ["Driver", "LeaderBoard", "Race", "SelfDrivingCar"], [], "easy",
         ["kata", "multi_file"], "车手排行榜单元测试", "车手、比赛积分与排行榜。",
         ["比赛按值保存 Driver，自动驾驶车被切片，显示名为算法版本号；参考测试按这一实际行为断言。"]),
        ("racing-car-telemetry", "TelemetrySystem", ["TelemetryClient", "TelemetryDiagnosticControls"], [], "easy",
         ["kata", "randomness"], "遥测客户端单元测试", "模拟调制解调器连接与诊断报文。",
         ["连接结果与随机报文取决于标准库的分布实现，参考测试只断言与实现无关的部分。"]),
        ("racing-car-text-converter", "TextConverter", ["HtmlPagesConverter", "HtmlTextConverter"], ["StringEscapeUtils.h"],
         "easy", ["kata", "file_io"], "文本转 HTML 单元测试", "读取文本文件转为 HTML，按 PAGE_BREAK 分页。",
         ["测试在当前工作目录写入各自的输入文件。`StringEscapeUtils` 写在头文件里，当前不做变异（R-06）。"]),
        ("racing-car-turn-ticket", "TurnTicketDispenser", ["TicketDispenser", "TurnNumberSequence", "TurnTicket"], [],
         "easy", ["kata", "global_state"], "排队取号单元测试", "取号机与全局递增的号码序列。",
         ["号码来自静态全局计数器，参考测试只断言相对增量。"]),
    ]
    for task_id, folder, units, extra_headers, tier, tags, title, what, notes in specs:
        files = {}
        for unit in units:
            files[f"{folder}/source/{unit}.cpp"] = f"Cpp/{folder}/source/{unit}.cpp"
            files[f"{folder}/include/{unit}.h"] = f"Cpp/{folder}/include/{unit}.h"
        for header in extra_headers:
            files[f"{folder}/include/{header}"] = f"Cpp/{folder}/include/{header}"
        built.append(build_handwritten(
            args, task_id, "Racing-Car-Katas", files, sorted(k for k in files if k.endswith(".cpp")),
            [f"{folder}/include"], sorted(files), tier, tags, title, f"Racing-Car-Katas 的 {folder}：{what}公开代码，开发题。",
            {"available": False, "note": "上游测试只有占位断言，未采用。"}, notes))
    files = {"TirePressureMonitoring/source/Alarm.cpp": "Cpp/TirePressureMonitoring/source/Alarm.cpp",
             "TirePressureMonitoring/source/Sensor.cpp": "Cpp/TirePressureMonitoring/source/Sensor.cpp",
             "TirePressureMonitoring/include/Alarm.h": "Cpp/TirePressureMonitoring/include/Alarm.h",
             "TirePressureMonitoring/include/Sensor.h": "Cpp/TirePressureMonitoring/include/Sensor.h"}
    built.append(build_handwritten(
        args, "racing-car-tire-pressure", "Racing-Car-Katas", files, ["TirePressureMonitoring/source/Alarm.cpp"],
        ["TirePressureMonitoring/include"],
        ["TirePressureMonitoring/source/Alarm.cpp", "TirePressureMonitoring/include/Alarm.h", "TirePressureMonitoring/include/Sensor.h"],
        "medium", ["kata", "link_seam"], "胎压报警单元测试",
        "Racing-Car-Katas 的 TirePressureMonitoring：只编译 Alarm.cpp，Sensor 需要测试提供链接替身。公开代码，开发题。",
        {"available": False, "note": "上游测试只有占位断言，未采用。"},
        ["`Sensor.cpp` 只作来源记录，不可见、不编译；测试必须自行定义 `Sensor::Sensor()` 与 `Sensor::popNextPressurePsiValue()`。"]))
    return [(task_id, 0, []) for task_id in built]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--repos", required=True, help="仓库清单 JSON")
    parser.add_argument("--clang", default="c++")
    parser.add_argument("--gcc", default="g++-14")
    parser.add_argument("--gcc-gtest", required=True)
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()
    args.repos = json.loads(Path(args.repos).read_text(encoding="utf-8"))
    results = build_tennis(args) + build_yatzy(args) + build_parrot(args) + build_others(args)
    for task_id, count, problems in results:
        print(f"{task_id}：" + (f"{count} 个生成用例" if count else "手写参考测试") + ("；" + "；".join(problems) if problems else ""))
    return 1 if any(problems for _, _, problems in results) else 0


if __name__ == "__main__":
    raise SystemExit(main())
