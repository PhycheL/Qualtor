"""D017 的公开构建契约；独立产品与 assessment 各自持有实现，不跨产品导入。"""
from pathlib import Path
import re
import shlex

BUILD_FIELDS = {"support_sources", "defines", "compile_options", "c_standard"}
COMPILE_OPTIONS = {"-fno-strict-aliasing", "-fwrapv", "-fsigned-char", "-funsigned-char"}
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx"}
HEADER_SUFFIXES = {".h", ".hh", ".hpp", ".hxx", ".inl"}
DEFINE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*(?:=(?:[A-Za-z_][A-Za-z0-9_]*|[+-]?(?:0[xX][0-9A-Fa-f]+|[0-9]+(?:\.[0-9]+)?)(?:[uUlLfF]*)))?")
KEYWORDS = set("""alignas alignof and and_eq asm auto bitand bitor bool break case catch char char16_t
char32_t class compl const constexpr const_cast continue decltype default delete do double dynamic_cast
else enum explicit export extern false float for friend goto if inline int long mutable namespace new
noexcept not not_eq nullptr operator or or_eq private protected public register reinterpret_cast restrict
return short signed sizeof static static_assert static_cast struct switch template this thread_local throw
true try typedef typeid typename union unsigned using virtual void volatile wchar_t while xor xor_eq
_Alignas _Alignof _Atomic _Bool _Complex _Generic _Imaginary _Noreturn _Static_assert _Thread_local defined""".split())


def reserved_identifier(value):
    return value.startswith("__") or bool(re.match(r"_[A-Z]", value)) or value in KEYWORDS


def validate_targets(targets, headers, visible, root, support=()):
    """D018：评分对象只能是非空源文件列表或非空头文件列表。None 表示旧题未声明头文件。"""
    if not isinstance(targets, list) or not all(isinstance(p, str) and p for p in targets):
        raise ValueError("target_sources 必须是路径列表")
    if headers is not None and (not isinstance(headers, list) or not headers
                                or not all(isinstance(p, str) and p for p in headers)):
        raise ValueError("target_headers 必须是非空路径列表")
    if bool(targets) == bool(headers):
        raise ValueError("只支持纯源文件或纯头文件题；拒绝空目标和混合题")
    selected = targets + (headers or [])
    if len(selected) != len(set(selected)) or set(selected) & set(support):
        raise ValueError("被测文件不能重复，且须与 support_sources 互斥")
    if not set(selected) <= set(visible):
        raise ValueError("被测文件必须全部可见")
    for rel in headers or []:
        path = Path(rel)
        if (path.is_absolute() or ".." in path.parts or str(path) != rel or path.suffix not in HEADER_SUFFIXES
                or any(c in rel for c in '\0;,\\\n\r$<>"\'')):
            raise ValueError(f"不合法的被测头文件路径：{rel}")
        current = Path(root)
        for part in path.parts:
            current /= part
            if current.is_symlink():
                raise ValueError(f"被测头文件不能经过符号链接：{rel}")
        if not current.is_file():
            raise ValueError(f"被测头文件不存在：{rel}")


def validate_build(build, targets, visible, root):
    """校验后返回带缺省值的副本；不改题目，避免改变旧题指纹。"""
    if not isinstance(build, dict) or set(build) - BUILD_FIELDS:
        raise ValueError("build 只接受 support_sources、defines、compile_options、c_standard")
    result = {"support_sources": [], "defines": [], "compile_options": [], **build}
    for key in ("support_sources", "defines", "compile_options"):
        values = result[key]
        if not isinstance(values, list) or not all(isinstance(v, str) and v for v in values):
            raise ValueError(f"build.{key} 必须是字符串列表")
        if len(values) != len(set(values)):
            raise ValueError(f"build.{key} 不允许重复项")
    support = result["support_sources"]
    if set(targets) & set(support):
        raise ValueError("support_sources 与 target_sources 必须互斥")
    if not set(support) <= set(visible):
        raise ValueError("support_sources 必须全部可见")
    for rel in list(targets) + support:
        path = Path(rel)
        if (path.is_absolute() or ".." in path.parts or str(path) != rel
                or any(c in rel for c in '\0;,\\\n\r$<>"\'') or path.suffix not in SOURCE_SUFFIXES):
            raise ValueError(f"不合法的 C/C++ 源文件路径：{rel}")
        current = Path(root)
        for part in path.parts:
            current /= part
            if current.is_symlink():
                raise ValueError(f"源文件路径不能经过符号链接：{rel}")
        if not current.is_file():
            raise ValueError(f"源文件不存在：{rel}")
    names = []
    for define in result["defines"]:
        name = define.split("=", 1)[0]
        if not DEFINE.fullmatch(define) or any(reserved_identifier(v) for v in define.split("=", 1)):
            raise ValueError(f"不合法的编译宏：{define}")
        names.append(name)
    if len(names) != len(set(names)):
        raise ValueError("编译宏名称不能重复")
    options = set(result["compile_options"])
    if options - COMPILE_OPTIONS:
        raise ValueError("compile_options 包含白名单之外的选项")
    if {"-fsigned-char", "-funsigned-char"} <= options:
        raise ValueError("char 符号选项相互冲突")
    if "c_standard" in build and build["c_standard"] not in ("c99", "c11"):
        raise ValueError("build.c_standard 只能为 c99 或 c11")
    if any(Path(p).suffix == ".c" for p in list(targets) + support) and "c_standard" not in build:
        raise ValueError("含 C 源文件时必须声明 build.c_standard")
    return result


def cmake_build_args(build, support_sources, target_headers=None):
    """输入已在宿主机校验；按 argv 传递，禁止拼接 shell。"""
    args = ["-DQUALTOR_SUPPORT_SOURCES=" + ";".join(support_sources),
            "-DQUALTOR_DEFINES=" + ";".join(build.get("defines", [])),
            "-DQUALTOR_COMPILE_OPTIONS=" + ";".join(build.get("compile_options", []))]
    if "c_standard" in build:
        args.append("-DQUALTOR_C_STANDARD=" + build["c_standard"][1:])
    if target_headers:
        args.append("-DQUALTOR_TARGET_HEADERS=" + ";".join(target_headers))
    return args


def compile_command_problems(commands, targets, support, tests, build, mode="plain", target_headers=None):
    """核对真实编译命令：标准、宏、选项与每一类编译单元的插桩边界。"""
    expected = set(targets + support + tests)
    problems = []
    if {entry["file"] for entry in commands} != expected or len(commands) != len(expected):
        problems.append("编译单元清单不一致")
    for entry in commands:
        path = entry["file"]
        args = entry.get("arguments") or shlex.split(entry["command"])
        standard = build.get("c_standard") if Path(path).suffix == ".c" else "c++11"
        if [a for a in args if a.startswith("-std=")] != [f"-std={standard}"]:
            problems.append(f"语言标准不一致：{path}")
        guards = [a for a in args if a.endswith("/cxx11_guard.h")]
        if bool(guards) != (Path(path).suffix != ".c"):
            problems.append(f"C++11 断言头作用范围错误：{path}")
        for define in build.get("defines", []):
            if "-D" + define not in args:
                problems.append(f"缺少宏 {define}：{path}")
        for option in build.get("compile_options", []):
            if option not in args:
                problems.append(f"缺少选项 {option}：{path}")
        if ("--coverage" in args) != (mode == "coverage" and (bool(target_headers) or path in targets)):
            problems.append(f"覆盖插桩作用范围错误：{path}")
        if any(a.startswith("-fpass-plugin=") for a in args) != (mode == "mull" and path in targets):
            problems.append(f"Mull 插件作用范围错误：{path}")
    return problems
