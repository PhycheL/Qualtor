"""评测调度、评分校准门禁和补评回归测试。"""
import json
import os
from pathlib import Path
import sys
import tempfile
import threading
import time
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import host
from host import public_task
import run
import run as run_module
import evaluate
import aggregate
import runs
from common import freeze_product, load_task, sha256_file, write_json
from run import execute

class BoundariesTest(unittest.TestCase):
    def test_task_only_exports_allowed_material(self):
        task = load_task("gildedrose-update-quality")
        visible = public_task(task)
        self.assertEqual(visible["budget"]["repair_rounds"], 3)
        self.assertNotIn("hidden", visible)
        self.assertNotIn("variants", visible)
        self.assertNotIn("scoring_domain", visible)
        self.assertNotIn("mutation", json.dumps(visible))

    def test_visible_escape_rejected(self):
        task = load_task("gildedrose-update-quality")
        task["visible"]["files"].append("../hidden/mutation_baseline.json")
        with self.assertRaises(ValueError):
            public_task(task)

    def test_stale_calibration_prevents_generator_start(self):
        with tempfile.TemporaryDirectory() as tmp, patch("run.RUNS", Path(tmp)), \
             patch("run.DockerExecutor") as docker, patch("run.GenerationExecutor") as generator, \
             patch("run.calibration_status", return_value={"status": "stale"}), \
             patch("run.tree_hash", return_value="hash"), patch("run.git_snapshot", return_value={}):
            docker.return_value.images = {}
            with self.assertRaisesRegex(ValueError, "passed"):
                execute({}, {"name": "test", "sha256": "x"}, [load_task("gildedrose-update-quality")], 1, 1, "stale")
            generator.assert_not_called()
            self.assertEqual(json.loads((Path(tmp) / "stale/run.json").read_text())["status"], "failed")

    def test_results_filter_version_and_retry_evidence(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            for version in ("0.1.1", "0.1.2"):
                result = {"mode": "score", "meta": {"agent_version": "pi"}, "scorer": {"version": version}}
                write_json(root / f"trial/score/{version}/final/result.json", result)
                write_json(root / f"trial/score/{version}/infra-retries/final-1/result.json", result)
            self.assertEqual(len(aggregate.load_results([root], "0.1.2")), 1)

    def test_no_rescore_inputs_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaisesRegex(ValueError, "没有可补评"):
                evaluate.rescore_jobs(Path(tmp), "0.1.2")

if __name__ == "__main__": unittest.main()
