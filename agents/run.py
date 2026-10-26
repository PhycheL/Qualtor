#!/usr/bin/env python3
"""生成产品公开入口：宿主机运行 pi，Docker 编译测试，输出冻结产物和生成成本。"""
import argparse
import json
import math
from pathlib import Path
import sys
from common.processes import Cancellation

from generator.config import load_config
from generator.host import generate
from generator.support import AGENTS, read_json, tree_hash, verify_pi
from generator.task import load_task


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--task", type=Path, help="公开任务 JSON，source_root 相对于此文件")
    parser.add_argument("--output", type=Path, help="本次新建输出目录，已存在时拒绝覆盖")
    parser.add_argument("--config", default="default")
    parser.add_argument("--env-file", type=Path, help="默认使用产品目录的 .env")
    parser.add_argument("--watchdog", type=float, default=900)
    parser.add_argument("--attempts", type=int, default=3, help="生成基础设施错误的总尝试次数（1 至 3）")
    parser.add_argument("--scenario", type=Path, help="仅框架验收：通过真实 pi 执行本地剧本，无模型调用")
    parser.add_argument("--describe", action="store_true", help="输出接口版本、产品和 pi 指纹及无凭证的配置快照")
    args = parser.parse_args()
    if not math.isfinite(args.watchdog) or args.watchdog <= 0 or args.attempts not in range(1, 4):
        parser.error("watchdog 必须为正数，attempts 必须为 1 至 3")
    try:
        scenario = read_json(args.scenario) if args.scenario else None
        if scenario is not None:
            model = {"provider": "qualtor-scripted", "model": "script", "thinking": "off", "cost_per_million": {}}
            snapshot = {"name": "framework-scripted"}
        else:
            model, snapshot = load_config(args.config, args.env_file)
        if args.describe:
            print(json.dumps({"schema": 1, "product_sha256": tree_hash(AGENTS),
                              "pi": verify_pi(), "config": snapshot}, ensure_ascii=False))
            return 0
        if args.task is None or args.output is None:
            parser.error("生成必须指定 --task 和 --output")
        with Cancellation() as cancel:
            result = generate(load_task(args.task), model, args.output, scenario, args.watchdog, args.attempts, cancel)
        print(json.dumps({"status": result["status"], "result": str(args.output.resolve() / "result.json")}, ensure_ascii=False))
        if result["status"] == "cancelled":
            return 128 + (result.get("cancellation_signal") or 15)
        return 1 if result["status"] == "agent_error" else 0
    except (ValueError, OSError, RuntimeError) as error:
        parser.exit(2, str(error) + "\n")


if __name__ == "__main__":
    raise SystemExit(main())
