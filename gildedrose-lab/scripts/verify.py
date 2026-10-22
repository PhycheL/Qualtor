#!/usr/bin/env python3
import argparse
import collections
import json
from pathlib import Path
import shlex
import sys
from audit import Audit


def evaluate(binary, cases, audit, stage):
    payload = "".join(f'{c["id"]} {json.dumps(c["name"])} {c["sell_in"]} {c["quality"]} {c["days"]}\n' for c in cases)
    process = audit.run(stage, [str(binary)], input_text=payload, timeout=120)
    actual, parse_errors = {}, []
    for line in process["stdout"].splitlines():
        try:
            ident, sell, quality, name = shlex.split(line)
            if ident in actual:
                raise ValueError("duplicate id")
            actual[ident] = {"name": name, "sell_in": int(sell), "quality": int(quality)}
        except ValueError as error:
            parse_errors.append({"line": line, "error": str(error)})
    mismatches = [{"id": c["id"], "suite": c["suite"], "input": {k:c[k] for k in ["name","sell_in","quality","days"]},
                   "expected": c["expected"], "actual": actual.get(c["id"])}
                  for c in cases if actual.get(c["id"]) != c["expected"]]
    suite_totals = dict(collections.Counter(c["suite"] for c in cases))
    suite_failed = dict(collections.Counter(c["suite"] for c in mismatches))
    valid_protocol = (not parse_errors and set(actual) == {c["id"] for c in cases})
    return {"passed": process["returncode"] == 0 and valid_protocol and not mismatches,
            "returncode": process["returncode"], "timed_out": process["timed_out"],
            "total": len(cases), "failed": len(mismatches), "protocol_valid": valid_protocol,
            "suite_totals": suite_totals, "suite_failed": suite_failed,
            "mismatches": mismatches, "parse_errors": parse_errors,
            "stdout_log": process["stdout_log"], "stderr_log": process["stderr_log"]}


if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("--binary", type=Path, required=True)
    p.add_argument("--cases", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--log-dir", type=Path, required=True)
    args = p.parse_args()
    result = evaluate(args.binary, json.loads(args.cases.read_text()), Audit(args.log_dir), "contract-binary")
    args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n")
    print(json.dumps({k:v for k,v in result.items() if k not in ["mismatches","parse_errors"]}, ensure_ascii=False))
    sys.exit(0 if result["passed"] else 1)
