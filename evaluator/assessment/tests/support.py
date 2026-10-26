"""单元测试共用：导入路径、固定数据位置、构造结果的辅助函数。"""
from pathlib import Path
import sys

TESTS = Path(__file__).resolve().parent
ASSESSMENT = TESTS.parent
FIXTURES = TESTS / "fixtures"
for path in (ASSESSMENT, ASSESSMENT.parent / "common", TESTS):
    if str(path) not in sys.path:
        sys.path.insert(0, str(path))


def scored_result(task="t1", agent="A", trial=1, m1=0.5, v2=1, s1=0.0, phase="final", status="scored",
                  seconds=10, calibrated=True, task_set="dev"):
    """构造一份汇总器使用的结果；只填汇总需要的字段。"""
    metrics = {"V1": 1, "V2": v2, "V3": 0.0, "S1": s1, "S2": {}, "M1_e2e": m1 if status == "scored" else 0.0,
               "M1_valid": m1 if status == "scored" else None, "M2": None, "M4": None, "F1": None,
               "C1": 0.9, "C2": 0.8, "C3": 1.0}
    return {"mode": "score", "status": status, "task": {"id": task, "set": task_set},
            "meta": {"agent_version": agent, "trial": trial, "phase": phase},
            "metrics": None if status == "infra_error" else metrics,
            "cost": {"tokens": {"input": 100, "output": 50}, "seconds": seconds, "model_calls": 1, "repair_rounds": 0},
            "scorer": {"version": "0.1.0", "code_sha256": "x",
                       "calibration": {"status": "passed" if calibrated else "missing"}},
            "_path": f"{agent}/{task}/{trial}"}
