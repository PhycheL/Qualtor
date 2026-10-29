#!/usr/bin/env python3
"""从已下载的固定提交创建步骤 A 的公开库题目；不联网、不改上游源码。

python3 benchmark/tools/import_step_a.py --upstream runs/step-a-20261028-01/upstream
输入为 yaml-cpp、md4c、tinyexpr 的 Git checkout；已有题目拒绝覆盖。
"""
import argparse
import json
from pathlib import Path
import re
import subprocess

from bankutil import (BENCHMARK, copy_file, copy_reference_as_probe, sha256_file, write_json, review_note,
                      write_task, write_text)

YAML_FIX = "5a9ab177bad9665ac5eb8f5b12435052123b5b6f"
MD4C_COMMIT = "c3340b480e5232711858108be07460a9836c8ab5"


def yaml_test_text(text):
    # 上游显式禁用的规格用例不注册进参考测试，保留清单与来源；不是删除运行失败用例。
    return re.sub(r'^TEST(?:_F)?\([^\n]+, DISABLED_[^\n]+\) \{.*?^\}\n', '', text, flags=re.M | re.S)


YAML_OPTIONS = '''// StrictMock 的连续意外事件会积累失败报告；首个断言失败即抛出，避免变异运行耗尽容器内存。
#include <gtest/gtest.h>
namespace {
class ReferenceOptions : public ::testing::Environment {
 public:
  void SetUp() override { ::testing::GTEST_FLAG(throw_on_failure) = true; }
};
::testing::Environment* const options = ::testing::AddGlobalTestEnvironment(new ReferenceOptions);
}
'''


def git(repo, *args):
    return subprocess.check_output(["git", "-C", str(repo), *args])


def create(task_id):
    directory = BENCHMARK / task_id
    directory.mkdir(exist_ok=False)
    (directory / "source").mkdir()
    (directory / "hidden/reference_tests").mkdir(parents=True)
    return directory


def finish_task(directory, repository, commit, targets, support, includes, tier, tags, title, description,
                origins, build=None, variants=(), target_headers=None, generated_by="benchmark/tools/import_step_a.py"):
    root = directory / "source"
    files = [str(p.relative_to(root)) for p in sorted(root.rglob("*")) if p.is_file()]
    visible = [p for p in files if Path(p).suffix in (".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inl")]
    config = {"support_sources": support, **(build or {})}
    copy_reference_as_probe(directory)
    note = review_note(directory.name)
    if note:
        with (directory / "hidden/README.md").open("a") as stream:
            stream.write("\n" + note + "\n")
    write_task(directory, task_id=directory.name, tier=tier, tags=tags, title=title, description=description,
               provenance={"repository": repository, "commit": commit, "reference_tests": origins,
                           "added_by_qualtor": [], "note": "source/ 文件逐字节取自上述提交；隐藏测试的转换见 hidden/README.md。"},
               source_files=files, target_sources=targets, include_dirs=includes, visible_files=visible,
               existing_tests={"available": False, "note": "上游测试作为隐藏参考材料，未投影给生成 Agent。"},
               scoring_domain="隐藏参考测试覆盖的输入；断言以固定源码实际行为为准；不以此收窄等价性判定。",
               probe_mode="reference_copy", generated_by=generated_by,
               variants=variants, build=config, target_headers=target_headers)


def parent_replacements(directory, repo, commit, variant_id):
    """只替换本题 source/ 已保存且修复实际涉及的文件，支持源文件和公共/内部头文件。"""
    parent = git(repo, "rev-parse", commit + "^").decode().strip()
    changed = git(repo, "diff", "--name-only", parent, commit).decode().splitlines()
    relatives = [p for p in changed if (directory / "source" / p).is_file()]
    for rel in relatives:
        path = directory / "hidden/variants" / variant_id / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(git(repo, "show", f"{parent}:{rel}"))
    patch = git(repo, "diff", parent, commit, "--", *relatives)
    (directory / "hidden/fix.patch").write_bytes(patch)
    return parent, {rel:sha256_file(directory / "hidden/variants" / variant_id / rel) for rel in relatives}


def yaml_task(upstream):
    repo = upstream / "yaml-cpp"
    directory = create("yaml-cpp-document")
    files = git(repo, "ls-tree", "-r", "--name-only", YAML_FIX).decode().splitlines()
    for rel in files:
        if rel.startswith(("src/", "include/")) or rel in ("LICENSE", "CMakeLists.txt", "README.md"):
            path = directory / "source" / rel
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(git(repo, "show", f"{YAML_FIX}:{rel}"))
    tests = ["test/integration/load_node_test.cpp", "test/integration/handler_test.cpp",
             "test/integration/handler_spec_test.cpp", "test/integration/error_messages_test.cpp",
             "test/integration/node_spec_test.cpp", "test/parser_test.cpp"]
    headers = [p for p in files if p.startswith("test/") and "/gtest-" not in p and p.endswith(".h")]
    for rel in tests + headers:
        name = Path(rel).name.replace(".cpp", ".cc")
        write_text(directory / "hidden/reference_tests" / name,
                   yaml_test_text(git(repo, "show", f"{YAML_FIX}:{rel}").decode()))
    write_text(directory / "hidden/reference_tests/reference_options.cc", YAML_OPTIONS)
    parent, replacements = parent_replacements(directory, repo, YAML_FIX, "tagged-null")
    rel = "src/singledocparser.cpp"
    write_text(directory / "hidden/README.md", f"""# yaml-cpp 文档解析

源码与上游 GoogleTest 测试取自 `{YAML_FIX}`，保留原许可证。测试扩展名 `.cpp` 改为 `.cc`，无断言改写；8 个上游已禁用的规格用例不注册。参考测试启用 GoogleTest throw_on_failure，防止变异死循环积累 StrictMock 失败报告耗尽容器内存；原程序不触发。
被测文件为 `src/singledocparser.cpp`，其余 `src/*.cpp` 仅作依赖编译，不参与覆盖与变异。

真实缺陷来源：BugsC++ `yaml_cpp/3`；[修复提交](https://github.com/jbeder/yaml-cpp/commit/{YAML_FIX})。
替换版本直接取修复父提交 `{parent}` 的该 `.cpp`，没有套用合成补丁；业务 diff 只改此源文件，保存为 `fix.patch`。
回归用例 `NodeTest.LoadNullWithStrTag` 验证显式字符串标签下的 null 保持字符串。修复前行为不符合该断言，计入 M4。
参考测试与探针相同，未检出项必须逐项复核；参考测试尚未人工审阅。
""")
    support = sorted(str(p.relative_to(directory / "source")) for p in (directory / "source/src").glob("*.cpp")
                     if p.name != "singledocparser.cpp")
    finish_task(directory, "https://github.com/jbeder/yaml-cpp", YAML_FIX, [rel], support, ["include", "src"],
                "hard", ["real-bug", "support-sources", "stateful", "multi-file"], "YAML 文档解析",
                "真实库的单文档事件解析模块；真实缺陷修复只涉及被测源文件。", tests + headers,
                build={"compile_options": ["-fno-strict-aliasing"]},
                variants=[{"id": "tagged-null", "kind": "real_bug", "expect": "fail",
                           "files": replacements,
                           "source": {"repository": "https://github.com/jbeder/yaml-cpp", "commit": parent,
                                      "fix_commit": YAML_FIX, "dataset": "BugsC++ yaml_cpp/3"}}])


def markdown_examples(text):
    state, inputs, outputs = 0, [], []
    for line in text.splitlines(keepends=True):
        stripped = line.strip()
        if re.fullmatch(r"`{32} example(?: [a-z]+)?", stripped):
            state, inputs, outputs = 1, [], []
        elif state == 2 and stripped == "`" * 32:
            yield "".join(inputs).replace("→", "\t"), "".join(outputs).replace("→", "\t")
            state = 0
        elif state == 1 and stripped == ".":
            state = 2
        elif state == 1:
            inputs.append(line)
        elif state == 2:
            outputs.append(line)


def cpp_string(text):
    # JSON 非 ASCII 保持 UTF-8；控制字符只出现 C++ 可用的标准转义。
    return json.dumps(text, ensure_ascii=False).replace("\\u0000", "\\0")


def md4c_task(upstream):
    repo = upstream / "md4c"
    assert git(repo, "rev-parse", "HEAD").decode().strip() == MD4C_COMMIT
    directory = create("md4c-html")
    for rel in ("LICENSE.md", "CMakeLists.txt", "src/md4c-html.c", "src/md4c.c", "src/entity.c",
                "src/md4c.h", "src/md4c-html.h", "src/entity.h"):
        copy_file(repo / rel, directory / "source" / rel)
    flags = {"spec": "0", "coverage": "0", "tables": "MD_FLAG_TABLES",
             "strikethrough": "MD_FLAG_STRIKETHROUGH", "tasklists": "MD_FLAG_TASKLISTS",
             "wiki-links": "MD_FLAG_WIKILINKS", "latex-math": "MD_FLAG_LATEXMATHSPANS",
             "underline": "MD_FLAG_UNDERLINE", "permissive-url-autolinks": "MD_FLAG_PERMISSIVEURLAUTOLINKS",
             "permissive-email-autolinks": "MD_FLAG_PERMISSIVEEMAILAUTOLINKS",
             "permissive-www-autolinks": "MD_FLAG_PERMISSIVEWWWAUTOLINKS"}
    prelude = '''// 上游 Markdown 输入和预期 HTML 转为 C++11 GoogleTest，转换工具 import_step_a.py。
#include <gtest/gtest.h>
#include <string>
#include "md4c-html.h"
static void append_html(const char* s, MD_SIZE n, void* p) { static_cast<std::string*>(p)->append(s,n); }
static std::string render(const std::string& input, unsigned flags, unsigned renderer=0) {
  std::string output;
  EXPECT_EQ(0, md_html(input.data(), input.size(), append_html, &output, flags, renderer));
  return output;
}
'''
    count = 0
    capture = json.loads((Path(__file__).parent / "step_a/md4c_actual.json").read_text())
    assert capture["source_commit"] == MD4C_COMMIT
    for name, option in flags.items():
        text = prelude
        for i, (markdown, html) in enumerate(markdown_examples((repo / f"test/{name}.txt").read_text())):
            html = capture["outputs"][f"Md4c_{name.replace('-', '_')}.Case{i+1}"]
            text += (f"TEST(Md4c_{name.replace('-', '_')}, Case{i+1}) {{\n"
                     f"  EXPECT_EQ({cpp_string(html)}, render({cpp_string(markdown)}, {option}));\n}}\n")
            count += 1
        write_text(directory / f"hidden/reference_tests/{name}.cc", text)
    copy_file(repo / "test/LICENSE", directory / "hidden/TEST_LICENSE")
    write_text(directory / "hidden/README.md", f"""# md4c HTML 渲染

源码取 release-0.4.8 `{MD4C_COMMIT}`，原文件未改。被测 `src/md4c-html.c`；解析器与实体表为依赖源文件。
参考测试由 11 份上游 `test/*.txt` 转为 {count} 个 GoogleTest 用例，保留全部输入及各扩展开关，测试许可证见 `TEST_LICENSE`。
上游比较归一化 HTML；本题按 D001 使用固定 GCC 原程序的逐字节输出，记录在 `benchmark/tools/step_a/md4c_actual.json`。全部 770 个输入保留，128 项输出格式差异证据见 `runs/step-a-md4c-capture-20261028-01/`。
探针为参考测试副本；测试未人工审阅，等价候选逐项复核。
""")
    finish_task(directory, "https://github.com/mity/md4c", MD4C_COMMIT, ["src/md4c-html.c"],
                ["src/md4c.c", "src/entity.c"], ["src"], "medium", ["c", "support-sources", "multi-file"],
                "Markdown HTML 渲染", "C99 HTML 渲染模块；Markdown 解析器只作为编译依赖。",
                [f"test/{name}.txt" for name in flags], build={"c_standard": "c99"})


def tinyexpr_task(upstream):
    repo = upstream / "tinyexpr"
    commit = git(repo, "rev-parse", "HEAD").decode().strip()
    directory = create("tinyexpr-configured")
    for rel in ("tinyexpr.c", "tinyexpr.h", "LICENSE", "Makefile", "README.md"):
        copy_file(repo / rel, directory / "source" / rel)
    text = (repo / "smoke.c").read_text()
    main = text.index("int main(")
    test_names = re.findall(r'lrun\("[^\"]+", (test_\w+)\)', text[main:])
    text = text[:main].replace('#include "minctest.h"', '''// Qualtor adaptation: minctest assertions -> GoogleTest; original inputs retained.
#include <gtest/gtest.h>
#define lok(x) ASSERT_TRUE(x)
#define lequal(a,b) EXPECT_EQ(a,b)
#define lfequal(a,b) EXPECT_NEAR(a,b,0.001)
#if !defined(TE_POW_FROM_RIGHT) || !defined(TE_NAT_LOG)
#error This task requires both public feature macros in tests and library.
#endif''')
    # C 的函数指针/void* 隐式转换在 C++11 测试中必须显式书写。
    text = re.sub(r'(\{"\w+", )(\w+)(, TE_(?:FUNCTION|CLOSURE)\d)', r'\1reinterpret_cast<const void*>(\2)\3', text)
    text = text.replace('double *c = context;', 'double *c = static_cast<double*>(context);')
    text = re.sub(r'(?<!\w)malloc\(([^;]+)\)', r'static_cast<char*>(malloc(\1))', text)
    text = text.replace('lfails', '::testing::UnitTest::GetInstance()->current_test_info()->result()->total_part_count()')
    text = re.sub(r'(\{"[^\"]+",\s*)([0-9]{16,})(\})', r'\1static_cast<double>(\2)\3', text)
    for name in test_names:
        if name != "test_locale":  # 宿主机 locale 安装状态不属于题目输入，固定容器只用 C locale。
            text += f"TEST(TinyExpr, {name[5:]}) {{ {name}(); }}\n"
    write_text(directory / "hidden/reference_tests/reference_tests.cc", text)
    write_text(directory / "hidden/README.md", f"""# TinyExpr 宏配置

源码取 `{commit}`，未改原始业务代码。C11 编译启用 `TE_POW_FROM_RIGHT` 和 `TE_NAT_LOG`，宏同时传给 C++11 测试。
`smoke.c` 的 minctest 断言转换为 GoogleTest；浮点容差沿用 0.001。仅为 C++ 编译显式转换函数指针、void*、malloc 结果及大整数到 double 的聚合初始化，移除原 main；lfails 映射到当前 GoogleTest 的断言结果数量。
locale 测试依赖外部 locale 安装状态，未注册；其余上游测试输入保留。测试与源码许可证均保留原文。
探针为参考测试副本；参考测试未人工审阅；等价候选逐项复核。
""")
    finish_task(directory, "https://github.com/codeplea/tinyexpr", commit, ["tinyexpr.c"], [], ["."],
                "medium", ["c", "compile-defines", "parser"], "数学表达式编译与求值",
                "带变量、闭包和可配置幂结合方向及对数语义的 C 表达式模块。", ["smoke.c", "minctest.h"],
                build={"c_standard": "c11", "defines": ["TE_POW_FROM_RIGHT", "TE_NAT_LOG"],
                       "compile_options": ["-fno-strict-aliasing"]})


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--upstream", type=Path, required=True)
    args = parser.parse_args()
    yaml_task(args.upstream)
    md4c_task(args.upstream)
    tinyexpr_task(args.upstream)
