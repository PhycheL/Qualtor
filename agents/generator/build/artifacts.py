"""冻结普通文件及内容哈希。"""
import hashlib
from pathlib import Path
from common.audit import now
from generator.support import write_json

def freeze(source, destination):
    """复制普通测试文件后立即冻结；绝不跟随链接、FIFO 或设备文件。"""
    source, destination = Path(source), Path(destination)
    (destination / "tests").mkdir(parents=True, exist_ok=False)
    files = {}
    for path in sorted(source.rglob("*")):
        if path.is_symlink() or (not path.is_dir() and not path.is_file()):
            raise ValueError(f"非法产物文件：{path.name}")
        if not path.is_file():
            continue
        rel = Path("tests") / path.relative_to(source)
        target = destination / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        content = path.read_bytes()
        target.write_bytes(content)
        target.chmod(0o444)
        files[str(rel)] = hashlib.sha256(content).hexdigest()
    write_json(destination / "manifest.json", {"files": files, "frozen_at": now()})
    return files


