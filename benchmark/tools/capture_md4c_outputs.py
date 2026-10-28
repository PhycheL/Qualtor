#!/usr/bin/env python3
"""在固定 GCC Docker 记录 md4c 全部上游输入的原始 HTML 输出（D001），不做语义归一化。"""
import argparse
import json
from pathlib import Path
import re
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "evaluator/assessment"), str(REPO / "evaluator/common")]
from audit import Audit
import common
from docker_runner import DockerExecutor
import pipeline
from runs import new_manifest, write_manifest, finish


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run-id", required=True)
    args = parser.parse_args()
    common.check_run_id(args.run_id)
    root = common.RUNS / args.run_id
    if root.exists():
        parser.error("run-id 已存在")
    manifest = new_manifest(args.run_id, "prepare", mode="md4c_characterization")
    write_manifest(root, manifest)
    task = common.load_task("md4c-html")
    product = root / "product"
    (product / "tests").mkdir(parents=True)
    provenance = common.read_json(common.source_root(task) / "SOURCE.json")
    upstream_names = {Path(name).stem + ".cc" for name in provenance["reference_tests"]}
    for source in common.hidden_path(task, "reference_tests").glob("*.cc"):
        if source.name not in upstream_names:
            continue
        text = re.sub(r'  EXPECT_EQ\((.*), render\((.*)\)\);',
                      r'  const auto actual = render(\2);\n  RecordProperty("actual", actual);\n  EXPECT_EQ(\1, actual);',
                      source.read_text())
        (product / "tests" / source.name).write_text(text)
    common.freeze_product(product)
    audit = Audit(root / "evidence/host")
    executor = DockerExecutor(audit, root / "evidence", args.run_id)
    executor.capabilities = {"coverage": True, "mull": False}
    result = pipeline.assess_product(executor, task, product, root / "capture", {}, audit, prep=True)
    full = next((root / "capture/gcc-run/results").glob("*-full.json"))
    output = json.loads(full.read_text())
    actual = {}
    for suite in output["testsuites"]:
        for test in suite["testsuite"]:
            actual[suite["name"] + "." + test["name"]] = test["actual"]
    assert len(actual) == 770
    common.write_json(root / "actual.json", {"source_commit": task["source"]["commit"], "evidence": str(full.relative_to(REPO)),
                                             "outputs": actual})
    finish(root, manifest, "completed", passed=True, captured=len(actual),
           original_expectation_failures=sum(s != "valid" for s in result["tests"].values()))
    print(root / "actual.json")


if __name__ == "__main__":
    main()
