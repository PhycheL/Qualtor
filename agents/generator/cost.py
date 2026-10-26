#!/usr/bin/env python3
"""从 pi 原始会话重新提取成本；只计完整 assistant 消息，避免累加 JSONL 流式增量。"""
import argparse
import json
from pathlib import Path

VERSION = "1.0.0"


def extract(record, priced=True):
    record = Path(record)
    generation = json.loads((record / "generation.json").read_text())
    messages = []
    for path in sorted((record / "logs/sessions").rglob("*.jsonl")):
        for line in path.read_text().splitlines():
            try:
                entry = json.loads(line)
            except ValueError:
                continue
            message = entry.get("message") or {}
            if entry.get("type") == "message" and message.get("role") == "assistant":
                messages.append(message)
    # pi 在写会话前崩溃时，用完整 message_end 事件恢复；不与会话重复相加。
    if not messages and (record / "logs/pi.stdout.jsonl").exists():
        for line in (record / "logs/pi.stdout.jsonl").read_text().splitlines():
            try:
                entry = json.loads(line)
            except ValueError:
                continue
            message = entry.get("message") or {}
            if entry.get("type") == "message_end" and message.get("role") == "assistant":
                messages.append(message)
    def total(cutoff, repairs):
        selected = [m for m in messages if (m.get("timestamp", 0) + m.get("durationMs", 0)) / 1000 <= cutoff]
        return {"extractor_version": VERSION,
                "tokens": {out: sum((m.get("usage") or {}).get(key, 0) for m in selected)
                           for out, key in (("input", "input"), ("output", "output"),
                                            ("cache_read", "cacheRead"), ("cache_write", "cacheWrite"))},
                "model_calls": len(selected), "repair_rounds": repairs,
                "seconds": max(0, cutoff - generation["started_at"]),
                "usd": sum((m.get("usage") or {}).get("cost", {}).get("total", 0) for m in selected) if priced else None}
    return {"extractor_version": VERSION,
            "first": total(generation.get("first_at") or generation["ended_at"], 0),
            "final": total(generation["ended_at"], generation["repair_rounds"])}


def add_costs(current, previous):
    result = dict(current, tokens=dict(current["tokens"]))
    for cost in previous:
        for key, value in cost["tokens"].items():
            result["tokens"][key] = result["tokens"].get(key, 0) + value
        for key in ("model_calls", "repair_rounds", "seconds"):
            result[key] += cost[key]
        result["usd"] = result["usd"] + cost["usd"] if result["usd"] is not None and cost["usd"] is not None else None
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("record", type=Path)
    parser.add_argument("--unpriced", action="store_true")
    args = parser.parse_args()
    print(json.dumps(extract(args.record, not args.unpriced), ensure_ascii=False, indent=2))
