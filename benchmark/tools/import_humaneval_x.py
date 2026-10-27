#!/usr/bin/env python3
"""把 HumanEval-X C++ 转换为题目包：按题号每约 8 道打包成一题，共 20 题（benchmark/humaneval-x-cpp-NN/）。

每道题：
- source/src/：每道 HumanEval 题一个源文件（prompt + canonical_solution，保留上游自己的 #include），
  公共头文件声明全部函数（含题面里的辅助函数）并带题面注释；
- hidden/reference_tests/：upstream_tests.cc（上游 test 字段机械转换）+ characterization_tests.cc（生成器记录的
  每个函数前 12 个输入的实际结果）；
- hidden/equivalence_probe/：生成器源码与 probe_prelude.h；tests/ 下是参考测试副本 + probe_tests.cc（其余输入）。

生成器在原代码上执行随机输入：输入取自上游测试、题面里的字面值及其扰动，每个输入在子进程中执行，
用 ASan、UBSan 与 libc++ 断言过滤触发未定义行为、崩溃、超时或超过 20 毫秒的输入；带 ASan 与不带 ASan
的两种构建、不同的栈与堆填充共跑 4 遍，只保留每遍都正常结束且结果相同的输入。之后用 GCC 14 + libstdc++ 回放，删去结果与 libc++ 不一致的断言。
CPP/22、CPP/137（Boost）和 CPP/162（OpenSSL）需要第三方库，等 R-01 完成后另行出题。

用法（从项目根目录执行；需要 Apple clang 或其他支持 ASan/UBSan 的 clang，以及 GCC 14 与其 GoogleTest）：
  python3 benchmark/tools/import_humaneval_x.py --data <humaneval_cpp.jsonl.gz> --commit <CodeGeeX 提交号> \\
      --license <CodeGeeX 的 LICENSE 文件> --gcc g++-14 --gcc-gtest <GoogleTest 安装前缀> [--force] [--jobs 4]
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import gzip
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import bankutil  # noqa: E402

TOOLS = Path(__file__).resolve().parent
EXCLUDED = {22: "需要 Boost（boost::any）", 137: "需要 Boost（boost::any）", 162: "需要 OpenSSL（MD5）"}
BUNDLES, PROBE_LIMIT, REFERENCE_CASES, CHUNK = 20, 60, 12, 25
SEED = 20261027
KEYWORDS = {"if", "for", "while", "switch", "return", "else", "do", "case", "sizeof", "main"}
SIG = re.compile(r"^(?P<ret>[A-Za-z_][\w:<>,\t \*&]*?)[ \t]*\b(?P<name>[A-Za-z_]\w*)[ \t]*\((?P<params>[^()]*)\)\s*\{", re.M)
STRING = r'"(?:[^"\\\n]|\\.)*"'
NUMBER = r"-?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?"

GEN = {"int": "gen_int", "long long": "gen_ll", "float": "gen_float", "double": "gen_double", "string": "gen_string",
       "vector<int>": "gen_vec_int", "vector<long long>": "gen_vec_ll", "vector<float>": "gen_vec_float",
       "vector<double>": "gen_vec_double", "vector<string>": "gen_vec_string",
       "vector<vector<int>>": "gen_vec_vec_int", "map<string,string>": "gen_map_ss"}
CTYPE = {"int": "int", "long long": "long long", "float": "float", "double": "double", "string": "std::string",
         "vector<int>": "std::vector<int>", "vector<long long>": "std::vector<long long>",
         "vector<float>": "std::vector<float>", "vector<double>": "std::vector<double>",
         "vector<string>": "std::vector<std::string>", "vector<vector<int>>": "std::vector<std::vector<int> >",
         "map<string,string>": "std::map<std::string, std::string>"}
KIND = {"int": "int", "long long": "ll", "bool": "bool", "float": "float", "double": "double", "string": "string",
        "vector<int>": "vec_int", "vector<long long>": "vec_ll", "vector<float>": "vec_float",
        "vector<double>": "vec_double", "vector<string>": "vec_string", "vector<vector<int>>": "vec_vec_int",
        "map<char,int>": "map_char_int"}


def norm(type_text):
    t = re.sub(r"\bstd::", "", type_text)
    t = re.sub(r"\bconst\b|&", " ", t)
    t = re.sub(r"\s+", " ", t).strip()
    return re.sub(r"\s*([<>,])\s*", r"\1", t)


def strip_comments(code):
    return re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", code, flags=re.S))


def functions(code):
    """顶格定义的函数：(返回类型, 函数名, [(参数类型, 参数名)], 原始签名)。先去掉注释，题面示例里也有函数调用。"""
    found = []
    for m in SIG.finditer(strip_comments(code)):
        ret, name = m.group("ret").strip(), m.group("name")
        if name in KEYWORDS or ret.split()[-1] in KEYWORDS:
            continue
        params = []
        for part in [p.strip() for p in re.split(r",(?![^<]*>)", m.group("params")) if p.strip()]:
            pm = re.match(r"^(.*?[\s>\*&])(\w+)$", part)
            params.append((norm(pm.group(1)) if pm else norm(part), pm.group(2) if pm else ""))
        found.append({"ret": norm(ret), "name": name, "params": params,
                      "signature": f"{ret} {name}({m.group('params').strip()})"})
    return found


def split_declaration(declaration):
    includes, code = [], []
    for line in declaration.splitlines():
        if re.match(r"\s*#\s*include\b", line):
            includes.append(line.strip())
        elif not re.match(r"\s*using\s+namespace\s+std\s*;", line):
            code.append(line)
    return includes, "\n".join(code) + "\n"


def scan_block_end(text, open_index):
    """从 open_index 处的 { 开始找匹配的 }，跳过字符串、字符字面值和注释。"""
    depth, i = 0, open_index
    while i < len(text):
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < len(text) and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j + 1
            continue
        if text.startswith("//", i):
            i = text.find("\n", i)
            i = len(text) if i < 0 else i
            continue
        if text.startswith("/*", i):
            i = text.find("*/", i) + 2
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    raise ValueError("main 的大括号不匹配")


def convert_upstream(problem):
    test = problem["test"]
    includes = [line.strip() for line in test.splitlines() if re.match(r"\s*#\s*include\b", line)]
    body = re.sub(r"^[ \t]*#[ \t]*(?:include|undef)[^\n]*\n", "", test, flags=re.M)
    main = re.search(r"\bint\s+main\s*\(\s*\)\s*\{", body)
    end = scan_block_end(body, main.end() - 1)
    helpers, main_body = body[:main.start()], body[main.end():end]
    main_body = re.sub(r"\breturn\s+0\s*;", "return;", main_body)
    helpers, main_body = (re.sub(r"\bassert\s*\(", "HE_ASSERT(", text) for text in (helpers, main_body))
    pid = int(problem["task_id"].split("/")[1])
    block = (f"namespace he_cpp_{pid:03d} {{\n{helpers.strip()}\n\nTEST(HumanEvalX, CPP_{pid:03d}) {{\n"
             f"{main_body.rstrip()}\n}}\n\n}}  // namespace he_cpp_{pid:03d}\n")
    return includes, block


def literal_seeds(problem):
    text = problem["prompt"] + "\n" + problem["test"] + "\n" + problem.get("example_test", "")
    strings = list(dict.fromkeys(s for s in re.findall(STRING, text) if len(s) <= 120))[:60]
    numbers = list(dict.fromkeys(re.findall(r"(?<![\w.])" + NUMBER + r"(?![\w.])", text)))
    ints = [n for n in numbers if re.fullmatch(r"-?\d+", n) and abs(int(n)) < 9 * 10 ** 18][:80]
    reals = [n for n in numbers if not re.fullmatch(r"-?\d+", n)][:80]
    ivecs, fvecs, svecs = [], [], []
    token = re.compile(r"\s*(" + STRING + "|" + NUMBER + r")\s*(?:,|$)")
    for group in re.findall(r"\{([^{}]*)\}", text):
        items, pos = [], 0
        while pos < len(group):
            m = token.match(group, pos)
            if not m:
                items = None
                break
            items.append(m.group(1))
            pos = m.end()
        if items is None:
            continue
        if not items:
            ivecs.append([]), svecs.append([]), fvecs.append([])
        elif all(i.startswith('"') for i in items):
            svecs.append(items)
        elif all(not i.startswith('"') for i in items):
            (ivecs if all(re.fullmatch(r"-?\d+", i) and abs(int(i)) < 9 * 10 ** 18 for i in items) else fvecs).append(items)
    dedup = lambda groups: [list(g) for g in dict.fromkeys(tuple(g) for g in groups)][:40]
    return strings, ints, reals, dedup(ivecs), dedup(fvecs), dedup(svecs)


def seeds_function(pid, problem):
    strings, ints, reals, ivecs, fvecs, svecs = literal_seeds(problem)
    lines = [f"static const probe::Seeds& seeds_{pid}() {{", "    static probe::Seeds sd;", "    static bool ready = false;",
             "    if (!ready) {", "        ready = true;"]
    lines += [f"        sd.ints.push_back({v}LL);" for v in ints]
    lines += [f"        sd.reals.push_back({v});" for v in reals]
    lines += [f"        sd.strs.push_back({v});" for v in strings]
    lines += [f"        sd.ivecs.push_back(std::vector<long long>{{{', '.join(i + 'LL' for i in g)}}});" for g in ivecs]
    lines += [f"        sd.fvecs.push_back(std::vector<double>{{{', '.join(g)}}});" for g in fvecs]
    lines += [f"        sd.svecs.push_back(std::vector<std::string>{{{', '.join(g)}}});" for g in svecs]
    return "\n".join(lines + ["    }", "    return sd;", "}"]) + "\n"


def probe_function(index, pid, fn):
    lines = [f"// CPP/{pid} {fn['signature']}",
             f"static void probe_{index}(unsigned long long seed, int limit, FILE* out) {{",
             f"    probe::Rng rng(seed * 1000003ULL + {index}ULL);", f"    const probe::Seeds& sd = seeds_{pid}();",
             "    std::set<std::string> seen;", "    int kept = 0;",
             "    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {"]
    for i, (ptype, _) in enumerate(fn["params"]):
        lines.append(f"        {CTYPE[ptype]} a{i} = probe::{GEN[ptype]}(rng, sd);")
    args = ", ".join(f"a{i}" for i in range(len(fn["params"])))
    shown = ' + ", " + '.join(f"probe::lit(a{i})" for i in range(len(fn["params"])))
    lines.append(f'        std::string call = std::string("{fn["name"]}(")' + (f" + {shown}" if shown else "") + ' + ")";')
    lines += ["        if (!seen.insert(call).second) continue;", "        std::string result;",
              f"        if (!probe::run_case([&]() {{ return probe::lit({fn['name']}({args})); }}, result)) continue;",
              f'        probe::emit(out, "{fn["name"]}", "{KIND[fn["ret"]]}", call, result);', "        ++kept;", "    }", "}"]
    return "\n".join(lines) + "\n"


def assertion(kind, call, expected):
    if kind == "float":
        return f"ExpectNearScalar({call}, {expected}, 1e-5);"
    if kind == "double":
        return f"ExpectNearScalar({call}, {expected}, 1e-9);"
    if kind in ("vec_float", "vec_double"):
        return f"ExpectNearVec({call}, {expected}, {'1e-5' if kind == 'vec_float' else '1e-9'});"
    return f"EXPECT_EQ(({call}), ({expected}));"  # 括号保护花括号与模板实参里的逗号


CASE_HEADER = """// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 {seed}）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "{header}"

#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {{

template <class T>
void ExpectNearScalar(T actual, T expected, double tolerance) {{
    EXPECT_NEAR(actual, expected, tolerance * (1 + std::fabs(static_cast<double>(expected))));
}}

template <class T>
void ExpectNearVec(const std::vector<T>& actual, const std::vector<T>& expected, double tolerance) {{
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) ExpectNearScalar(actual[i], expected[i], tolerance);
}}

}}  // namespace
"""


def write_cases(path, header, suite, cases):
    """写断言文件，返回 {行号: 用例}，用于 GCC 回放后按行删除不一致的断言。"""
    lines = CASE_HEADER.format(seed=SEED, header=header).splitlines()
    by_function, at_line = {}, {}
    for case in cases:
        by_function.setdefault(case[0], []).append(case)
    for name, items in by_function.items():
        for k in range(0, len(items), CHUNK):
            lines += ["", f"TEST({suite}, {name}_{k // CHUNK + 1:02d}) {{"]
            for case in items[k:k + CHUNK]:
                lines.append("    " + assertion(case[1], case[2], case[3]))
                at_line[len(lines)] = case
            lines.append("}")
    bankutil.write_text(path, "\n".join(lines) + "\n")
    return at_line


def run(command, **kwargs):
    return subprocess.run(command, capture_output=True, text=True, **kwargs)


# 每个输入要在两种构建、多种内存填充下都正常结束且结果完全相同才保留：
# ASan 构建能抓越界与释放后使用；不带 ASan 的构建栈布局不同，读未初始化变量的输入会得到不同的垃圾值而被淘汰。
PASSES = (("asan", "0", "0"), ("asan", "255", "171"), ("plain", "0", None), ("plain", "1", None))


def generate_cases(task_dir, gen_dir, sources, args, tmp):
    common = ["-std=c++11", "-O0", "-g", "-fno-sanitize-recover=all", "-fno-omit-frame-pointer",
              "-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE"]
    builds = {"asan": common + ["-fsanitize=address,undefined"], "plain": common + ["-fsanitize=undefined"]}
    for name, flags in builds.items():
        built = run([args.clang, *flags, f"-I{task_dir / 'source/src'}", f"-I{gen_dir}",
                     str(gen_dir / "generate_probe.cc"), *map(str, sources), "-o", str(tmp / f"gen-{name}")])
        if built.returncode != 0:
            raise RuntimeError("探针生成器编译失败：\n" + built.stderr[-3000:])
    passes = []
    for build, dirt, fill in PASSES:
        out = tmp / f"cases-{build}-{dirt}.tsv"
        env = dict(os.environ, QUALTOR_PROBE_DIRT=dirt)
        if fill is not None:
            env["ASAN_OPTIONS"] = f"detect_leaks=0:malloc_fill_byte={fill}:max_malloc_fill_size=1048576"
        done = run([str(tmp / f"gen-{build}"), str(SEED), str(PROBE_LIMIT), str(out)], env=env, timeout=3600)
        if done.returncode != 0:
            raise RuntimeError("探针生成器运行失败：\n" + done.stderr[-3000:])
        rows, seen = [], set()
        for line in out.read_text().splitlines():
            row = tuple(line.split("\t"))
            if len(row) == 4 and row[:3] not in seen:  # 同一调用只保留第一次结果
                seen.add(row[:3])
                rows.append(row)
        passes.append(rows)
    others = [set(rows) for rows in passes[1:]]
    return [case for case in passes[0] if all(case in rows for rows in others)]


def gcc_replay(task_dir, sources, test_files, args, tmp):
    """用 GCC 14 + libstdc++ 编译运行全部测试，返回 {文件名: [失败行号]}。"""
    binary = tmp / "replay"
    gtest = Path(args.gcc_gtest)
    built = run([args.gcc, "-std=c++11", "-O0", f"-I{task_dir / 'source/src'}", f"-I{gtest / 'include'}",
                 *map(str, test_files), *map(str, sources), f"-L{gtest / 'lib'}", "-lgtest", "-lgtest_main",
                 "-pthread", "-o", str(binary)])
    if built.returncode != 0:
        raise RuntimeError("GCC 回放编译失败：\n" + built.stderr[-3000:])
    done = run([str(binary)], timeout=600, cwd=tmp)
    failures = {}
    for name, line in re.findall(r"([\w.]+\.cc):(\d+): Failure", done.stdout):
        failures.setdefault(name, set()).add(int(line))
    if done.returncode not in (0, 1) or (done.returncode == 1 and not failures):
        raise RuntimeError("GCC 回放异常结束：\n" + done.stdout[-3000:])
    return failures


def build_bundle(number, problems, args):
    task_id = f"humaneval-x-cpp-{number:02d}"
    header_name = f"humaneval_x_cpp_{number:02d}.h"
    guard = header_name.replace(".", "_").upper()
    task_dir = bankutil.reset_task_dir(task_id, args.force)
    src = task_dir / "source" / "src"
    ids = [int(p["task_id"].split("/")[1]) for p in problems]
    header = [f"// HumanEval-X C++ 函数集 {number:02d}：{', '.join(p['task_id'] for p in problems)}。",
              "// 由 benchmark/tools/import_humaneval_x.py 从上游 prompt 与 canonical_solution 生成。",
              f"#ifndef {guard}", f"#define {guard}", "", "#include <map>", "#include <string>", "#include <vector>", "",
              "using namespace std;", ""]
    sources, fns, upstream_includes, upstream_blocks, gen_parts = [], [], [], [], []
    for problem, pid in zip(problems, ids):
        includes, code = split_declaration(problem["prompt"])
        full = code + problem["canonical_solution"]
        found = functions(full)
        doc = re.search(r"/\*.*?\*/", problem["prompt"], re.S)
        header.append(f"// {problem['task_id']}")
        if doc:
            header.append(doc.group(0).strip())
        header += [f"{fn['signature']};" for fn in found] + [""]
        path = src / f"cpp_{pid:03d}.cc"
        bankutil.write_text(path, f"// HumanEval-X {problem['task_id']}（prompt + canonical_solution）\n"
                                  f'#include "{header_name}"\n' + "\n".join(includes) + "\n\n" + full.strip() + "\n")
        sources.append(path)
        test_includes, block = convert_upstream(problem)
        upstream_includes += test_includes
        upstream_blocks.append(block)
        gen_parts.append(seeds_function(pid, problem))
        for fn in found:
            if fn["ret"] in KIND and all(p in GEN for p, _ in fn["params"]):
                fns.append((pid, fn))
            else:
                print(f"  {task_id}：{fn['name']} 的类型不受生成器支持，只由参考测试覆盖")
    header += [f"#endif  // {guard}", ""]
    bankutil.write_text(src / header_name, "\n".join(header))
    shutil.copyfile(args.license, task_dir / "source" / "LICENSE")
    ref = task_dir / bankutil.HIDDEN["reference_tests"]
    includes = sorted(set(i for i in upstream_includes if "assert.h" not in i))
    bankutil.write_text(ref / "upstream_tests.cc", (
        "// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。\n"
        f'#include "{header_name}"\n\n#include <gtest/gtest.h>\n' + "".join(i + "\n" for i in includes)
        + "\n#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))\n\n" + "\n".join(upstream_blocks)))
    gen_dir = task_dir / "hidden" / "equivalence_probe"
    gen_dir.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(TOOLS / "probe_prelude.h", gen_dir / "probe_prelude.h")
    calls = [f"    probe_{i}(seed, limit, out);" for i in range(len(fns))]
    bankutil.write_text(gen_dir / "generate_probe.cc", (
        "// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出\n"
        "// “函数\\t结果类型\\t调用表达式\\t结果字面值”。构建与运行方式见同目录上级的 README.md。\n"
        f'#include "{header_name}"\n#include "probe_prelude.h"\n\n' + "\n".join(gen_parts) + "\n"
        + "\n".join(probe_function(i, pid, fn) for i, (pid, fn) in enumerate(fns))
        + "\nint main(int argc, char** argv) {\n    if (argc != 4) return 2;\n"
          "    unsigned long long seed = strtoull(argv[1], 0, 10);\n    int limit = atoi(argv[2]);\n"
          "    FILE* out = fopen(argv[3], \"w\");\n    if (!out) return 2;\n" + "\n".join(calls)
        + "\n    fclose(out);\n    return 0;\n}\n"))
    problems_found = []
    with tempfile.TemporaryDirectory(prefix=f"{task_id}-") as tmp:
        tmp = Path(tmp)
        cases = generate_cases(task_dir, gen_dir, sources, args, tmp)
        for attempt in range(4):
            first, rest, seen = [], [], {}
            for case in cases:
                seen[case[0]] = seen.get(case[0], 0) + 1
                (first if seen[case[0]] <= REFERENCE_CASES else rest).append(case)
            ref_lines = write_cases(ref / "characterization_tests.cc", header_name, "Characterization", first)
            probe_lines = write_cases(tmp / "probe_tests.cc", header_name, "Probe", rest)
            failures = gcc_replay(task_dir, sources, [ref / "upstream_tests.cc", ref / "characterization_tests.cc",
                                                      tmp / "probe_tests.cc"], args, tmp)
            if failures.get("upstream_tests.cc"):
                problems_found.append(f"上游测试在 GCC 下失败（行 {sorted(failures['upstream_tests.cc'])}），需人工处理")
            bad = {ref_lines[n] for n in failures.get("characterization_tests.cc", ()) if n in ref_lines}
            bad |= {probe_lines[n] for n in failures.get("probe_tests.cc", ()) if n in probe_lines}
            if not bad:
                break
            cases = [c for c in cases if c not in bad]
            print(f"  {task_id}：GCC 回放删去 {len(bad)} 个与 libc++ 结果不一致的断言")
        else:
            problems_found.append("GCC 回放多次后仍有不一致的断言")
        bankutil.copy_reference_as_probe(task_dir, [tmp / "probe_tests.cc"])
    per_function = {}
    for case in cases:
        per_function[case[0]] = per_function.get(case[0], 0) + 1
    visible = sorted([f"src/{header_name}"] + [f"src/{p.name}" for p in sources])
    bankutil.write_text(task_dir / "hidden" / "README.md", (
        f"# {task_id} 隐藏材料\n\n"
        f"- 被测代码：HumanEval-X C++ 的 {len(problems)} 道题（{', '.join(p['task_id'] for p in problems)}），"
        "每题一个源文件，内容为上游 prompt + canonical_solution。\n"
        "- 参考测试：`upstream_tests.cc` 由上游 test 字段机械转换；`characterization_tests.cc` 为生成器记录的每个函数前 "
        f"{REFERENCE_CASES} 个输入的实际结果。\n"
        f"- 探针（{bankutil.PROBE_MODES['generated']}）：`tests/` 下为参考测试副本与 `probe_tests.cc`；"
        f"各函数保留的输入数：{json.dumps(per_function, ensure_ascii=False)}。\n"
        "- 生成器：`equivalence_probe/generate_probe.cc` 与 `probe_prelude.h`。输入取自上游测试与题面中的字面值及其扰动；"
        "每个输入在子进程中执行，用 ASan、UBSan 与 libc++ 断言过滤未定义行为、崩溃、超时和超过 20 毫秒的输入；"
        "带 ASan 与不带 ASan 两种构建、不同栈与堆填充共跑 4 遍，只保留每遍都正常结束且结果相同的输入"
        "（读未初始化变量的输入在不同栈布局下结果不同而被淘汰）；再用 GCC 14 + libstdc++ 回放，删去结果不一致的断言。\n"
        "- 重建：重新运行 `benchmark/tools/import_humaneval_x.py --force`；修改后要重新标定变异分母。\n"))
    bankutil.write_task(
        task_dir, task_id=task_id, tier="easy", tags=["humaneval-x", "pure_functions", "multi_file"],
        title=f"C++ 函数集 {number:02d} 单元测试",
        description=(f"HumanEval-X C++ 的 {len(problems)} 道题合为一题，每题一个源文件；上游 assert 测试转换为 GoogleTest，"
                     "另由生成器记录原代码在大量输入上的实际结果。公开数据，开发题。"),
        provenance={"repository": "https://github.com/zai-org/CodeGeeX", "commit": args.commit, "license": "Apache-2.0",
                    "dataset": "codegeex/benchmark/humaneval-x/cpp/data/humaneval_cpp.jsonl.gz",
                    "dataset_sha256": hashlib.sha256(Path(args.data).read_bytes()).hexdigest(),
                    "problems": [p["task_id"] for p in problems]},
        source_files=visible + ["LICENSE"], target_sources=[f"src/{p.name}" for p in sources], include_dirs=["src"],
        visible_files=visible,
        existing_tests={"available": True, "note": "HumanEval-X 自带的 assert 测试已转换为 GoogleTest 参考测试，对 Agent 不可见。"},
        scoring_domain=("生成器从上游测试与题面字面值出发随机生成的输入（含扰动），已过滤触发未定义行为、崩溃、超时或依赖未初始化内存的输入；"
                        "上游测试的输入照原样保留。参考测试与探针只在这些输入上保证与被测代码一致。"),
        probe_mode="generated", generated_by="benchmark/tools/import_humaneval_x.py")
    return task_id, sum(per_function.values()), problems_found


def plan_bundles(rows):
    ids = sorted(int(r["task_id"].split("/")[1]) for r in rows)
    pending = [i for i in ids if i not in EXCLUDED]
    by_id = {int(r["task_id"].split("/")[1]): r for r in rows}
    names = {i: {fn["name"] for fn in functions(split_declaration(by_id[i]["prompt"])[1] + by_id[i]["canonical_solution"])}
             for i in pending}
    size = len(pending) // BUNDLES
    bundles = []
    while pending:
        bundle, used = [], set()
        for pid in list(pending):
            if len(bundle) == size and len(bundles) < BUNDLES - 1:
                break
            if names[pid] & used:
                continue
            bundle.append(pid)
            used |= names[pid]
            pending.remove(pid)
        bundles.append(bundle)
    return [[by_id[i] for i in b] for b in bundles]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--data", required=True)
    parser.add_argument("--commit", required=True)
    parser.add_argument("--license", required=True)
    parser.add_argument("--clang", default="c++")
    parser.add_argument("--gcc", default="g++-14")
    parser.add_argument("--gcc-gtest", required=True)
    parser.add_argument("--only", type=int, nargs="*", help="只生成指定编号的题，如 --only 1 2")
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()
    opener = gzip.open if args.data.endswith(".gz") else open
    with opener(args.data, "rt", encoding="utf-8") as handle:
        rows = [json.loads(line) for line in handle if line.strip()]
    bundles = plan_bundles(rows)
    jobs = [(n, b) for n, b in enumerate(bundles, 1) if not args.only or n in args.only]

    def work(item):
        number, problems = item
        try:
            return build_bundle(number, problems, args)
        except Exception as error:
            return f"humaneval-x-cpp-{number:02d}", 0, [f"生成失败：{error}"]

    with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as pool:
        results = list(pool.map(work, jobs))
    for task_id, count, problems in results:
        print(f"{task_id}：{count} 个生成用例" + ("；" + "；".join(problems) if problems else ""))
    for pid, reason in sorted(EXCLUDED.items()):
        print(f"未纳入 CPP/{pid}：{reason}，等 R-01 完成后另行出题")
    return 1 if any(problems for _, _, problems in results) else 0


if __name__ == "__main__":
    raise SystemExit(main())
