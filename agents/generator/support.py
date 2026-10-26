"""产品内部的路径、文件和版本工具；不依赖仓库根或 Git。"""
import hashlib
import json
import os
from pathlib import Path
import platform
import subprocess

AGENTS = Path(__file__).resolve().parents[1]


def read_json(path):
    return json.loads(Path(path).read_text())


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n")


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def sha256_text(text):
    return hashlib.sha256(text.encode()).hexdigest()


def tree_hash(root, runtime=False):
    """可复制的内容指纹；排除凭证、缓存、运行产物和安装依赖。"""
    root = Path(root)
    parts = []
    for directory, dirs, files in os.walk(root):
        dirs[:] = sorted(d for d in dirs if d not in (".git", "node_modules", "__pycache__", ".artifacts", ".cache", "output")
                         and (runtime or d != "dist"))
        for name in sorted(files):
            path = Path(directory) / name
            if name == ".qualtor-build.json" or name.startswith(".env") or path.suffix == ".pyc":
                continue
            parts.append(f"{path.relative_to(root)}\0{sha256_file(path)}")
    return sha256_text("\n".join(parts))


def dependency_hash(root):
    """原生依赖按内容记录，复制交付目录不会因为 mtime 改变而失效。"""
    root = Path(root)
    parts = []
    for directory, dirs, files in os.walk(root):
        dirs[:] = sorted(d for d in dirs if d not in (".git", ".artifacts")
                         and (d != "dist" or "node_modules" in Path(directory).parts))
        base = Path(directory)
        if "node_modules" not in base.parts:
            continue
        for name in sorted(dirs + files):
            path = base / name
            if path.is_symlink():
                parts.append(f"{path.relative_to(root)}\0link\0{os.readlink(path)}")
            elif path.is_file():
                parts.append(f"{path.relative_to(root)}\0{sha256_file(path)}")
    return sha256_text("\n".join(parts))


def host_platform():
    return {"system": platform.system(), "machine": platform.machine(),
            "node": subprocess.check_output(["node", "--version"], text=True).strip()}


def verify_pi():
    try:
        stamp = read_json(AGENTS / "pi/.qualtor-build.json")
    except FileNotFoundError:
        raise ValueError("pi 尚未在当前宿主机安装；请执行 setup.py --pi-only") from None
    if (stamp.get("host") != host_platform() or stamp.get("source_sha256") != tree_hash(AGENTS / "pi")
            or stamp.get("runtime_sha256") != tree_hash(AGENTS / "pi", runtime=True)
            or stamp.get("dependencies_sha256") != dependency_hash(AGENTS / "pi")):
        raise ValueError("pi 运行环境或依赖已改变；请在当前宿主机重新执行 agents/setup.py --pi-only")
    if not (AGENTS / "pi/packages/coding-agent/dist/cli.js").is_file():
        raise ValueError("pi 未构建；请执行 agents/setup.py --pi-only")
    for name, tool in stamp.get("search_tools", {}).items():
        if sha256_file(AGENTS / ".cache/tools/bin" / name) != tool["sha256"]:
            raise ValueError("搜索工具已改变；请重新执行 agents/setup.py --pi-only")
    return stamp
