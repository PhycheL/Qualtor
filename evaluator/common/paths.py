"""仓库路径唯一入口；从本文件定位，不依赖当前工作目录。"""
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
EVALUATOR = REPO / "evaluator"
COMMON = EVALUATOR / "common"
TOOLCHAINS = EVALUATOR / "toolchains"
SCORER = EVALUATOR / "scorer"
GENERATOR = EVALUATOR / "generator"
BENCHMARK = REPO / "benchmark"
AGENTS = REPO / "agents"
RUNS = REPO / "runs"
