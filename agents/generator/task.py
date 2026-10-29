"""公开任务的严格输入边界和给生成 Agent 的说明。"""
import math
from pathlib import Path
from generator.support import read_json
from generator.build.contract import validate_build, validate_targets


def load_task(path):
    path = Path(path).resolve()
    task = read_json(path)
    required = {"id", "title", "source_root", "target_sources", "include_dirs", "visible_files",
                "allowed_test_files", "budget", "test_timeout_seconds"}
    if not isinstance(task, dict) or not required <= set(task) or set(task) - required - {"build", "target_headers"}:
        raise ValueError("公开任务字段不完整或含未知字段；不能传入隐藏评分材料")
    for key in ("id", "title", "source_root"):
        if not isinstance(task[key], str) or not task[key].strip():
            raise ValueError(f"公开任务 {key} 必须是非空字符串")
    root = (path.parent / task["source_root"]).resolve()
    if not root.is_dir():
        raise ValueError("source_root 必须是存在的目录")
    for key in ("target_sources", "include_dirs", "visible_files", "allowed_test_files"):
        values = task[key]
        if not isinstance(values, list) or not all(isinstance(v, str) and v for v in values):
            raise ValueError(f"{key} 必须是路径列表")
        if key not in ("include_dirs", "target_sources") and not values:
            raise ValueError(f"{key} 不能为空")
        for value in values:
            rel = Path(value)
            if rel.is_absolute() or ".." in rel.parts or any(c in value for c in ("\0", ";", ",", "\\", "\n", "\r")):
                raise ValueError(f"{key} 含不合法的相对路径")
            if key == "allowed_test_files" and (not value.startswith("tests/") or any(c in value for c in "?[]")):
                raise ValueError("allowed_test_files 仅支持 tests/ 下含 * 的模式")
    for rel in task["visible_files"]:
        current = root
        for part in Path(rel).parts:
            current /= part
            if current.is_symlink():
                raise ValueError("可见文件不能经过符号链接")
        if not current.is_file():
            raise ValueError(f"可见文件不存在：{rel}")
    if not set(task["target_sources"]) <= set(task["visible_files"]):
        raise ValueError("target_sources 必须是 visible_files 的子集")
    build = validate_build(task.get("build", {}), task["target_sources"], task["visible_files"], root)
    validate_targets(task["target_sources"], task.get("target_headers"), task["visible_files"], root, build["support_sources"])
    budget = task["budget"]
    if not isinstance(budget, dict) or set(budget) != {"repair_rounds"} or type(budget["repair_rounds"]) is not int or budget["repair_rounds"] < 0:
        raise ValueError("budget 只接受非负整数 repair_rounds")
    timeout = task["test_timeout_seconds"]
    if type(timeout) not in (int, float) or not math.isfinite(timeout) or timeout <= 0:
        raise ValueError("test_timeout_seconds 必须是有限正数")
    task["source_root"] = str(root)
    return task


def task_text(task):
    build = task.get("build", {})
    target_line = "被测文件：" + ', '.join('project/' + p for p in task['target_sources'])
    if task.get("target_headers"):
        target_line = "被测头文件：" + ', '.join('project/' + p for p in task['target_headers'])
        target_line += "\n- 被测代码全部位于被测头文件中。"
    configuration = ""
    if build:
        configuration = (f"- 依赖源文件（参与编译链接）：{', '.join('project/' + p for p in build.get('support_sources', [])) or '无'}\n"
                         f"- 全部编译单元的宏：{', '.join(build.get('defines', [])) or '无'}；"
                         f"编译选项：{', '.join(build.get('compile_options', [])) or '无'}。\n"
                         f"- C 源文件标准：{build.get('c_standard', '无 C 源文件')}；测试仍使用 C++11 / GoogleTest。\n")
    return f"""# 测试生成任务：{task['title']}

为现有 C/C++ 代码生成 C++11 / GoogleTest 1.12.1 单元测试。断言以代码的实际行为为准。
通过 read、grep、find、ls 阅读源码，通过 write、edit 编写测试，通过 build_and_test 编译并运行。

- {target_line}
- 可见文件：{', '.join('project/' + p for p in task['visible_files'])}
- 允许修改：{', '.join(task['allowed_test_files'])}。只提交这些测试文件。
- 头文件目录：{', '.join('project/' + p for p in task['include_dirs'])}；构建时也包含 tests/。
{configuration}- 测试快照：build_and_test 在编译前保存本轮测试快照，第 1 次快照同时作为首次产物保留；你可以根据反馈继续修改测试。
- 修复预算：{task['budget']['repair_rounds']} 轮。第 1 次 build_and_test 不算修复；以后每次调用消耗 1 轮。
- 单测超时：{task['test_timeout_seconds']} 秒。build_and_test 返回编译错误或测试结果、剩余轮次，以及 feedback/ 中完整日志的位置，可使用 read 继续查看。

先生成能检查行为的测试，主动编译验证；如编译失败或断言失败，根据结果修正并在预算内再次验证。
预算用尽后工具会拒绝再次编译。完成后结束对话，框架将自动保存最终测试快照。
"""


