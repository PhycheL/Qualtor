"""run.json 的统一格式（D010）：所有执行都是 run，用 kind 区分类型，用 status 表示执行到了哪一步。

- kind：toolchain、prepare、calibration、eval 四类之一；
- status：running（进行中）、completed（执行完毕）、incomplete（执行完毕但有缺失结果）、failed（中途出错）；
- passed：验收类执行（工具链验收、分母标定、校准、框架自测）的结论，与 status 分开记录。
"""
import json
from pathlib import Path

from audit import now

SCHEMA = 1
KINDS = ("toolchain", "prepare", "calibration", "eval")
STATUSES = ("running", "completed", "incomplete", "failed")


def new_manifest(run_id, kind, **fields):
    manifest = {"schema": SCHEMA, "run_id": run_id, "kind": kind, "status": "running", "started_at": now(), **fields}
    check_manifest(manifest)
    return manifest


def check_manifest(manifest):
    for key in ("schema", "run_id", "kind", "status", "started_at"):
        if key not in manifest:
            raise ValueError(f"run.json 缺少字段 {key}")
    if manifest["kind"] not in KINDS:
        raise ValueError(f"run.json 的 kind 必须是 {KINDS} 之一：{manifest['kind']}")
    if manifest["status"] not in STATUSES:
        raise ValueError(f"run.json 的 status 必须是 {STATUSES} 之一：{manifest['status']}")
    if "passed" in manifest and not isinstance(manifest["passed"], bool):
        raise ValueError("run.json 的 passed 必须是布尔值")


def write_manifest(run_dir, manifest):
    check_manifest(manifest)
    path = Path(run_dir) / "run.json"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n")
    return path


def finish(run_dir, manifest, status, **fields):
    manifest.update(status=status, finished_at=now(), **fields)
    return write_manifest(run_dir, manifest)
