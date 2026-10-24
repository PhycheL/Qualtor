"""覆盖成本口径、可见材料、补评和校准门槛；执行路径由 Docker 剧本验收覆盖。"""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from host import load_config, public_task
from cost import extract, add_costs
from common import load_task, write_json
from run import execute
import score
import aggregate


class CostTest(unittest.TestCase):
    def test_first_cutoff_and_complete_messages_only(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            write_json(root / "generation.json", {"started_at": 1, "first_at": 2.5, "ended_at": 5, "repair_rounds": 1})
            logs = root / "logs/sessions"
            logs.mkdir(parents=True)
            messages = [{"type": "message", "message": {"role": "assistant", "timestamp": timestamp,
                        "usage": {"input": 10, "output": 5, "cacheRead": 4, "cacheWrite": 2, "cost": {"total": .25}}}}
                        for timestamp in (2000, 3000, 4000)]
            messages.insert(1, {"type": "message_update", "message": messages[0]["message"]})
            (logs / "session.jsonl").write_text("\n".join(json.dumps(m) for m in messages))
            result = extract(root)
            self.assertEqual(result["first"]["model_calls"], 1)
            self.assertEqual(result["final"]["model_calls"], 3)
            self.assertEqual(result["first"]["tokens"]["cache_read"], 4)
            self.assertEqual(result["final"]["usd"], .75)
            self.assertEqual(result["first"]["repair_rounds"], 0)
            self.assertIsNone(extract(root, priced=False)["final"]["usd"])
            self.assertEqual(add_costs(result["first"], [result["final"]])["model_calls"], 4)


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

    def test_empty_config_fails_before_model_call(self):
        with self.assertRaisesRegex(ValueError, "provider"):
            load_config("default")

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
                score.rescore_jobs(Path(tmp), "0.1.2")


if __name__ == "__main__":
    unittest.main()
