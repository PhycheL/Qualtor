"""D017 的公开构建契约；独立产品与 assessment 各自持有实现，不跨产品导入。"""
from pathlib import Path
import hashlib
import json
import re
import shlex

BUILD_FIELDS = {"support_sources", "defines", "compile_options", "c_standard", "environment", "link_libraries", "codegen"}
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

# D020：配方是数据；库/生成器只使用这里已有的 CMake 接线，不接受任意脚本。
ENVIRONMENT_SNAPSHOT = "20261021T000000Z"
ENVIRONMENT_NAME = re.compile(r"[a-z][a-z0-9-]{0,63}")
LIBRARY_PACKAGES = {"Boost::headers": "Boost", "OpenSSL::Crypto": "OpenSSL",
                    "ZLIB::ZLIB": "ZLIB", "protobuf::libprotobuf": "Protobuf",
                    "protobuf::libprotobuf-lite": "Protobuf", "Qt5::Core": "Qt5"}
GENERATOR_LIBRARIES = {"moc": {"Qt5::Core"},
                       "protoc": {"protobuf::libprotobuf", "protobuf::libprotobuf-lite"}}


def validate_environment(recipe):
    fields = {"schema", "name", "snapshot", "packages", "libraries", "generators",
              "cmake_prefix_path", "imported_compile_definitions", "imported_compile_options"}
    if not isinstance(recipe, dict) or set(recipe) != fields or type(recipe["schema"]) is not int or recipe["schema"] != 1:
        raise ValueError("构建环境配方字段不完整或包含未知字段")
    if not isinstance(recipe["name"], str) or not ENVIRONMENT_NAME.fullmatch(recipe["name"]):
        raise ValueError("构建环境名称不合法")
    if recipe["snapshot"] != ENVIRONMENT_SNAPSHOT:
        raise ValueError("构建环境必须使用基础镜像的同一 Debian 快照")
    packages = recipe["packages"]
    if not isinstance(packages, dict) or not packages:
        raise ValueError("构建环境必须声明精确版本的软件包")
    for name, version in packages.items():
        if (not re.fullmatch(r"[a-z0-9][a-z0-9+.-]+", name)
                or not isinstance(version, str) or not re.fullmatch(r"[0-9][A-Za-z0-9.+:~\-]*", version)):
            raise ValueError("软件包必须具有合法名称和精确版本，不能含通配符或命令")
    for key, allowed in (("libraries", LIBRARY_PACKAGES), ("generators", GENERATOR_LIBRARIES)):
        values = recipe[key]
        if (not isinstance(values, list) or not all(isinstance(v, str) and v in allowed for v in values)
                or len(values) != len(set(values))):
            raise ValueError(f"构建环境 {key} 包含未知或重复项")
    for tool in recipe["generators"]:
        if not GENERATOR_LIBRARIES[tool] & set(recipe["libraries"]):
            raise ValueError(f"生成器 {tool} 缺少对应的库目标")
    prefixes = recipe["cmake_prefix_path"]
    if (not isinstance(prefixes, list) or any(not isinstance(p, str)
            or not re.fullmatch(r"/(?:usr|opt)/[A-Za-z0-9_./+-]+", p)
            or ".." in Path(p).parts for p in prefixes)):
        raise ValueError("CMake 前缀只能指向环境内的 /usr 或 /opt 目录")
    for key, allowed in (("imported_compile_definitions", {"QT_CORE_LIB", "QT_NO_DEBUG"}),
                         ("imported_compile_options", {"-fPIC"})):
        data = recipe[key]
        if not isinstance(data, dict) or set(data) - set(recipe["libraries"]):
            raise ValueError(f"{key} 必须按已声明的库目标登记")
        for target, values in data.items():
            if (target != "Qt5::Core" or not isinstance(values, list)
                    or not all(isinstance(v, str) and v in allowed for v in values)
                    or len(values) != len(set(values))):
                raise ValueError(f"{key} 包含白名单之外的导入选项")
    return recipe


def load_environment(name_or_path, directory):
    path = Path(name_or_path)
    if path.suffix != ".json":
        if not isinstance(name_or_path, str) or not ENVIRONMENT_NAME.fullmatch(name_or_path):
            raise ValueError("构建环境名称不合法")
        path = Path(directory) / (name_or_path + ".json")
    recipe = validate_environment(json.loads(path.read_text()))
    if Path(name_or_path).suffix != ".json" and recipe["name"] != name_or_path:
        raise ValueError("构建环境名称与配方不一致")
    return recipe, hashlib.sha256(path.read_bytes()).hexdigest()


def environment_tag(recipe, digest, toolchain):
    if toolchain not in ("gcc", "clang"):
        raise ValueError("环境只支持 GCC 或 Clang")
    return f"docker.io/library/qualtor-env-{recipe['name']}-{toolchain}:{digest[:12]}"


def environment_find_packages(recipe, libraries=None):
    libraries = recipe["libraries"] if libraries is None else libraries
    if set(libraries) - set(recipe["libraries"]):
        raise ValueError("链接库不在构建环境配方中")
    packages = sorted({LIBRARY_PACKAGES[v] for v in libraries})
    return "\n".join("find_package(Qt5 5.15 REQUIRED COMPONENTS Core)" if p == "Qt5"
                     else f"find_package({p} REQUIRED)" for p in packages) + "\n"


def environment_directory():
    """只定位配方数据；独立产品和评测分别使用自己的契约实现。"""
    for parent in Path(__file__).resolve().parents:
        for candidate in (parent / "toolchains/environments", parent / "agents/toolchains/environments"):
            if candidate.is_dir():
                return candidate
    raise ValueError("构建环境配方目录不存在")


def task_environment(build):
    if "environment" not in build:
        return None
    name = build["environment"]
    if not isinstance(name, str) or not ENVIRONMENT_NAME.fullmatch(name):
        raise ValueError("build.environment 必须是环境名称")
    return load_environment(name, environment_directory())


def validate_codegen(build, visible, root, recipe):
    libraries = build.get("link_libraries", [])
    if (not isinstance(libraries, list) or not all(isinstance(v, str) for v in libraries)
            or len(libraries) != len(set(libraries)) or set(libraries) - set(recipe["libraries"])):
        raise ValueError("build.link_libraries 必须是配方声明的互异导入目标")
    entries = build.get("codegen", [])
    if not isinstance(entries, list):
        raise ValueError("build.codegen 必须为列表")
    tools = set()
    for entry in entries:
        if not isinstance(entry, dict) or entry.get("tool") not in recipe["generators"]:
            raise ValueError("build.codegen 使用了环境未声明的生成器")
        tool = entry["tool"]
        if tool in tools or not GENERATOR_LIBRARIES[tool] & set(libraries):
            raise ValueError("生成器不能重复，且必须链接对应库")
        tools.add(tool)
        if tool == "moc":
            if set(entry) != {"tool"}:
                raise ValueError("moc 只接受 tool 字段")
            continue
        if set(entry) != {"tool", "inputs", "import_dirs"}:
            raise ValueError("protoc 必须声明 inputs 和 import_dirs")
        inputs, dirs = entry["inputs"], entry["import_dirs"]
        if (not isinstance(inputs, list) or not inputs or not isinstance(dirs, list)
                or not all(isinstance(p, str) and p for p in inputs + dirs)):
            raise ValueError("protoc 输入与目录必须是路径列表，输入不能为空")
        outputs = [proto_relative(p, dirs) for p in inputs]
        if not set(inputs) <= set(visible) or len(set(outputs)) != len(inputs):
            raise ValueError("protoc 输入必须全部可见，输出文件名不能冲突")
        for rel in inputs + dirs:
            path = Path(rel)
            if (path.is_absolute() or '..' in path.parts or str(path) != rel
                    or any(c in rel for c in '\0;,\\\n\r$<>"\'')):
                raise ValueError("protoc 路径必须是安全相对路径")
            current = Path(root)
            for part in path.parts:
                current /= part
                if current.is_symlink():
                    raise ValueError("protoc 路径不能经过符号链接")
            if rel in inputs and (path.suffix != '.proto' or not current.is_file()):
                raise ValueError("protoc 输入必须是存在的 .proto 文件")
            if rel in dirs and not current.is_dir():
                raise ValueError("protoc import_dirs 必须存在")


def proto_relative(path, import_dirs):
    """protoc 使用首个包含输入的 -I 根；保留其下路径，支持上游的子目录 include。"""
    for directory in import_dirs:
        try:
            return str(Path(path).relative_to(directory).with_suffix('.pb.cc'))
        except ValueError:
            continue
    raise ValueError('protoc 输入必须位于某个 import_dirs 目录内')


def generated_units(build, build_dir):
    generated = []
    for entry in build.get("codegen", []):
        if entry["tool"] == "moc":
            generated.append(str(Path(build_dir) / "scored_tests_autogen/mocs_compilation.cpp"))
        else:
            generated += [str(Path(build_dir) / proto_relative(p, entry['import_dirs'])) for p in entry["inputs"]]
    return generated


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
        raise ValueError("build 包含未知字段")
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
    environment = task_environment(build)
    if environment:
        if options & {"-fsigned-char", "-funsigned-char"}:
            raise ValueError("有环境的题不能改变预编译库的 char 符号约定")
        validate_codegen(build, visible, root, environment[0])
    elif "link_libraries" in build or "codegen" in build:
        raise ValueError("链接库和代码生成必须同时声明 build.environment")
    return result


def cmake_build_args(build, support_sources, target_headers=None, recipe=None, source_root=None, moc_headers=None):
    """输入已在宿主机校验；按 argv 传递，禁止拼接 shell。"""
    args = ["-DQUALTOR_SUPPORT_SOURCES=" + ";".join(support_sources),
            "-DQUALTOR_DEFINES=" + ";".join(build.get("defines", [])),
            "-DQUALTOR_COMPILE_OPTIONS=" + ";".join(build.get("compile_options", []))]
    if "c_standard" in build:
        args.append("-DQUALTOR_C_STANDARD=" + build["c_standard"][1:])
    if target_headers:
        args.append("-DQUALTOR_TARGET_HEADERS=" + ";".join(target_headers))
    if "environment" in build:
        if recipe is None or source_root is None:
            raise ValueError("环境构建需要配方和只读源码根目录")
        libraries = build.get("link_libraries", [])
        environment_find_packages(recipe, libraries)
        args += ["-DQUALTOR_LIBRARIES=" + ";".join(libraries),
                 "-DQUALTOR_PACKAGES=" + ";".join(sorted({LIBRARY_PACKAGES[v] for v in libraries})),
                 "-DCMAKE_PREFIX_PATH=" + ";".join(["/opt/googletest", *recipe["cmake_prefix_path"]])]
        for entry in build.get("codegen", []):
            if entry["tool"] == "moc":
                args += ["-DQUALTOR_AUTOMOC=ON", "-DQUALTOR_MOC_HEADERS=" + ";".join(moc_headers or [])]
            else:
                args += ["-DQUALTOR_PROTO_FILES=" + ";".join(str(Path(source_root) / p) for p in entry["inputs"]),
                         "-DQUALTOR_PROTO_IMPORT_DIRS=" + ";".join(str(Path(source_root) / p) for p in entry["import_dirs"]),
                         "-DQUALTOR_PROTO_OUTPUTS=" + ";".join(proto_relative(p, entry['import_dirs']) for p in entry['inputs'])]
    return args


def compile_command_problems(commands, targets, support, tests, build, mode="plain", target_headers=None,
                             generated=None, recipe=None):
    """核对真实编译命令：标准、宏、选项与每一类编译单元的插桩边界。"""
    expected = set(targets + support + tests + (generated or []))
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
        if recipe:
            imported = set()
            for target in build.get("link_libraries", []):
                imported.update(recipe["imported_compile_definitions"].get(target, []))
            for define in imported:
                if "-D" + define not in args:
                    problems.append(f"缺少配方导入宏 {define}：{path}")
            if any(a.startswith('-DQT_') and a[2:] not in imported | set(build.get('defines', [])) for a in args):
                problems.append(f"未知的 Qt 导入宏：{path}")
            if "-fPIC" in args and not any("-fPIC" in recipe['imported_compile_options'].get(t, [])
                                            for t in build.get('link_libraries', [])):
                problems.append(f"配方未声明 -fPIC：{path}")
            system_dirs = [args[i + 1] for i, value in enumerate(args[:-1]) if value == '-isystem']
            system_dirs += [a[len('-isystem'):] for a in args if a.startswith('-isystem') and a != '-isystem']
            for directory in system_dirs:
                base = directory in ('/opt/googletest/include', '/usr/include')
                qt = ('Qt5::Core' in build.get('link_libraries', []) and re.fullmatch(
                    r'/usr/(?:include/(?:aarch64|x86_64)-linux-gnu/qt5(?:/QtCore)?|lib/(?:aarch64|x86_64)-linux-gnu/qt5/mkspecs/linux-g\+\+)', directory))
                if not base and not qt:
                    problems.append(f"库目标带入未登记的系统头文件目录：{directory}：{path}")
        if ("--coverage" in args) != (mode == "coverage" and (bool(target_headers) or path in targets)):
            problems.append(f"覆盖插桩作用范围错误：{path}")
        if any(a.startswith("-fpass-plugin=") for a in args) != (mode == "mull" and path in targets):
            problems.append(f"Mull 插件作用范围错误：{path}")
    return problems
