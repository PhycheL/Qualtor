#!/usr/bin/env python3
"""把 Exercism C++ 练习转换为题目包：参考解作被测代码，上游 Catch2 测试机械转换为 GoogleTest 参考测试。

每个练习生成一道题 benchmark/exercism-<slug>/：
- source/src/：.meta/example.* 按练习规定的文件名（如 clock.h、clock.cpp）放置；source/LICENSE 为上游许可证；
- hidden/reference_tests/：转换后的测试与 catch_compat.h；
- hidden/equivalence_probe/tests/：参考测试副本（探针模式 reference_copy，见 bankutil.PROBE_MODES）。

跳过：依赖尚未接入的 Boost、参考解或测试不能按 C++11 编译。下载的上游仓库只作为数据读取，不在其中执行任何脚本。
用法（从项目根目录执行）：
  python3 benchmark/tools/import_exercism.py --source <解压后的 exercism/cpp 根目录> --commit <提交号> [--slugs clock luhn] [--force]
"""
import argparse
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
EXCLUDED = {
    "list-ops": "参考解使用 C++17 的 [[maybe_unused]]，不能原样按 C++11 接入",
}
CATCH_BLOCK = re.compile(r'^[ \t]*#[ \t]*ifdef[ \t]+EXERCISM_TEST_SUITE[^\n]*\n(?:[^\n]*\n){0,3}?[ \t]*#[ \t]*endif[^\n]*\n', re.M)
CATCH_LINE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*[<"](?:catch2/catch\.hpp|test/catch\.hpp)[>"][^\n]*\n', re.M)
STRINGS = r'(?:"(?:[^"\\\n]|\\.)*"\s*)+'
TEST_CASE = re.compile(r'TEST_CASE\s*\(\s*(' + STRINGS + r')(?:,\s*' + STRINGS + r')?\)')


def convert_test(text, suite):
    """Catch2 测试 → GoogleTest：替换头文件，TEST_CASE 改为 TEST，主体放进匿名命名空间避免全局名冲突。"""
    text = text.replace("\\\n", "")  # 先按 C++ 翻译阶段 2 拼接反斜杠续行，上游有跨行的字符串
    text = re.sub(r"^[ \t]*//[ \t]*clang-format[ \t]+(?:off|on)[ \t]*\n", "", text, flags=re.M)
    replaced, count = CATCH_BLOCK.subn("", text)
    if count == 0:
        replaced, count = CATCH_LINE.subn("", text)
    if count == 0:
        raise ValueError("找不到 Catch2 头文件引用")
    names = set()

    def rename(match):
        description = "".join(re.findall(r'"((?:[^"\\\n]|\\.)*)"', match.group(1)))
        base = f"T{len(names) + 1:03d}_{bankutil.identifier(description)}"
        names.add(base)
        return f"TEST({suite}, {base})"

    body = TEST_CASE.sub(rename, replaced)
    if not names:
        raise ValueError("没有 TEST_CASE")
    lines = body.splitlines(keepends=True)
    last_include = max((i for i, line in enumerate(lines) if re.match(r"\s*#\s*include\b", line)), default=-1)
    head, rest = "".join(lines[:last_include + 1]), "".join(lines[last_include + 1:])
    return ("// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。\n"
            "#define EXERCISM_RUN_ALL_TESTS 1\n#include <gtest/gtest.h>\n#include \"catch_compat.h\"\n"
            + head + "\nnamespace {\n" + rest.rstrip() + "\n\n}  // namespace\n"), len(names)


def has_function_body(code):
    """.cpp 里是否有函数实现；只有 include、命名空间和注释的空壳视为代码全在头文件里。"""
    stripped = re.sub(r"//[^\n]*|/\*.*?\*/", "", code, flags=re.S)
    return re.search(r"\)\s*(?:const\s*)?(?:noexcept\s*)?\{", stripped) is not None


def compiles(cxx, files, include_dirs, extra=()):
    for path in files:
        command = [cxx, "-std=c++11", "-fsyntax-only", *extra] + [f"-I{d}" for d in include_dirs] + [str(path)]
        if subprocess.run(command, capture_output=True).returncode != 0:
            return False
    return True


def import_exercise(exercise, args, gtest_include):
    slug = exercise.name
    if slug in EXCLUDED:
        return None, EXCLUDED[slug]
    environment = getattr(args, 'environment', None) if slug == 'meetup' else None
    if slug == 'meetup' and not environment:
        return None, 'meetup 需要 --environment bank-20261021'
    meta = json.loads((exercise / ".meta" / "config.json").read_text(encoding="utf-8"))
    files = meta.get("files", {})
    solution, tests, examples = files.get("solution", []), files.get("test", []), files.get("example", [])
    if len(tests) != 1:
        return None, "测试文件不止一个（需人工处理）"
    by_ext = {Path(s).suffix: Path(s).name for s in solution}
    mapping = {by_ext[Path(e).suffix]: f"exercises/practice/{slug}/{e}" for e in examples if Path(e).suffix in by_ext}
    cpp_files = [name for name in mapping if name.endswith(".cpp")]
    # 模板练习的 solution 可能列出 .cpp 桩，但上游参考实现只提供头文件。
    missing_solution = set(Path(s).name for s in solution) - set(mapping)
    header_example = bool(mapping) and all(Path(n).suffix in ('.h', '.hpp', '.hh', '.hxx', '.inl') for n in mapping)
    if not mapping or (missing_solution and not (header_example and all(n.endswith('.cpp') for n in missing_solution))):
        return None, "参考解文件与练习规定的文件名对不上"
    with tempfile.TemporaryDirectory(prefix="exercism-import-") as tmp:
        tmp = Path(tmp)
        for name, rel in mapping.items():
            shutil.copyfile(args.source / rel, tmp / name)
        header_only = not any(has_function_body((tmp / n).read_text(encoding="utf-8")) for n in cpp_files)
        headers = sorted(n for n in mapping if n.endswith((".h", ".hh", ".hpp", ".hxx", ".inl"))) if header_only else None
        units = [tmp / n for n in cpp_files]
        if header_only:
            check = tmp / "header_check.cc"
            check.write_text(''.join(f'#include "{n}"\n' for n in headers))
            units = [check]
        if not getattr(args, 'defer_build', False) and not compiles(args.cxx, units, [tmp], extra=("-pedantic-errors",) if header_only else ()):
            return None, "参考解不能按 C++11 编译"
        loc = sum(len((tmp / n).read_text(encoding="utf-8").splitlines()) for n in mapping)
        suite = bankutil.camel(slug)
        converted, cases = convert_test((exercise / tests[0]).read_text(encoding="utf-8"), suite)
        test_name = Path(tests[0]).stem + ".cc"
        (tmp / test_name).write_text(converted, encoding="utf-8")
        shutil.copyfile(TOOLS / "catch_compat.h", tmp / "catch_compat.h")
        if not getattr(args, 'defer_build', False) and gtest_include and not compiles(args.cxx, [tmp / test_name], [tmp, gtest_include]):
            return None, "转换后的测试不能按 C++11 编译（需人工转换）"
        task_id = f"exercism-{slug}"
        task_dir = bankutil.reset_task_dir(task_id, args.force)
        for name in mapping:
            bankutil.copy_file(tmp / name, task_dir / "source" / "src" / name)
        bankutil.copy_file(args.source / "LICENSE", task_dir / "source" / "LICENSE")
        ref = task_dir / bankutil.HIDDEN["reference_tests"]
        bankutil.copy_file(tmp / test_name, ref / test_name)
        bankutil.copy_file(TOOLS / "catch_compat.h", ref / "catch_compat.h")
    extra = TOOLS / ("step_c" if environment else "step_b") / task_id
    if extra.is_dir():
        for path in sorted(extra.rglob("*")):
            if path.is_file():
                bankutil.copy_file(path, task_dir / "hidden" / path.relative_to(extra))
    bankutil.copy_reference_as_probe(task_dir)
    snake = Path((headers or cpp_files)[0]).stem
    visible = sorted(f"src/{name}" for name in mapping)
    note = bankutil.review_note(task_id)
    bankutil.write_text(task_dir / "hidden" / "README.md", (
        f"# {task_id} 隐藏材料\n\n"
        f"- 被测代码：Exercism C++ 练习 `{slug}` 的参考解（`.meta/example.*`），提交 `{args.commit}`。\n"
        f"- 参考测试：上游 `{tests[0]}` 由 `benchmark/tools/import_exercism.py` 机械转换为 GoogleTest，共 {cases} 个用例；"
        "`catch_compat.h` 把 Catch2 断言映射为 GoogleTest。\n"
        + (f"- {note}\n" if note else "")
        + f"- 探针：参考测试副本（{bankutil.PROBE_MODES['reference_copy']}）\n"
        "- 重建：重新运行导入脚本并加 `--force`；修改参考测试后要重新标定变异分母。\n"))
    variants = bankutil.handwritten_variants(task_dir)
    if header_only:
        with (task_dir / "hidden/README.md").open("a") as stream:
            stream.write("\n纯头文件题；参考测试及准备阶段实例化文件确定 coverage_baseline.json。未实例化成员说明见 coverage_notes.md。"
                         "手写变异来源为 benchmark/tools/handwritten_variants/，检出在 Docker 中核验。\n")
    bankutil.write_task(
        task_dir, task_id=task_id, tier="easy" if loc < 100 else "medium", tags=["exercism", "upstream_tests"],
        title=f"{snake} 模块单元测试",
        description=f"Exercism C++ 练习 {slug} 的参考解作为被测代码；上游 Catch2 测试机械转换为 GoogleTest 作参考测试。公开代码，开发题。",
        provenance={"repository": "https://github.com/exercism/cpp", "commit": args.commit, "license": "MIT",
                    "upstream_paths": dict(sorted({f"src/{k}": v for k, v in mapping.items()}.items())),
                    "upstream_tests": f"exercises/practice/{slug}/{tests[0]}"},
        source_files=visible + ["LICENSE"], target_sources=[] if header_only else sorted(f"src/{n}" for n in cpp_files),
        include_dirs=["src"], visible_files=visible,
        existing_tests={"available": True, "note": "上游 Catch2 测试已转换为 GoogleTest 参考测试，对 Agent 不可见。"},
        scoring_domain="上游测试覆盖的输入；未单独界定评分输入域，探针即参考测试。",
        probe_mode="reference_copy", generated_by="benchmark/tools/import_exercism.py", variants=variants,
        target_headers=[f"src/{n}" for n in headers] if header_only else None,
        build={'environment': environment, 'link_libraries': ['Boost::headers']} if environment else None)
    return task_id, f"{cases} 个上游用例，{loc} 行"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--commit", required=True)
    parser.add_argument("--slugs", nargs="*")
    parser.add_argument("--cxx", default=os.environ.get("QUALTOR_HOST_CXX", "c++"))
    parser.add_argument("--force", action="store_true")
    parser.add_argument('--environment', help='meetup 使用的构建环境')
    parser.add_argument('--defer-build', action='store_true', help='只导入材料；编译有效性留给后续 Docker 标定，不调用宿主机编译器')
    args = parser.parse_args()
    gtest = os.environ.get("QUALTOR_HOST_GTEST")
    gtest_include = str(Path(gtest) / "include") if gtest else None
    practice = args.source / "exercises" / "practice"
    chosen = [practice / s for s in args.slugs] if args.slugs else sorted(p for p in practice.iterdir() if p.is_dir())
    imported, skipped = [], {}
    for exercise in chosen:
        task_id, note = import_exercise(exercise, args, gtest_include)
        if task_id:
            imported.append(task_id)
            print(f"生成 {task_id}：{note}")
        else:
            skipped[exercise.name] = note
    for slug, reason in sorted(skipped.items()):
        print(f"跳过 {slug}：{reason}")
    print(f"共生成 {len(imported)} 道题，跳过 {len(skipped)} 个练习")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
