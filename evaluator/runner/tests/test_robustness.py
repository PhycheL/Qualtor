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
import score
import aggregate
import runs
from common import freeze_product, load_task, sha256_file, write_json
from run import execute

class RunTrialsTest(unittest.TestCase):
    def test_first_error_cancels_trials_not_yet_started(self):
        started = []

        def work(task, index):
            started.append(index)
            if index == 1:
                raise OSError("docker create failed")
            return {"task": task["id"], "trial": index, "status": "finished"}

        jobs = [({"id": "t"}, index) for index in range(1, 6)]
        results, errors, cancelled = run_module.run_trials(work, jobs, 1)
        self.assertEqual(started, [1])
        self.assertEqual(results, [])
        self.assertEqual(errors[0]["trial"], 1)
        self.assertIn("docker create failed", errors[0]["error"])
        self.assertEqual(sorted(c["trial"] for c in cancelled), [2, 3, 4, 5])

    def test_all_trials_run_without_errors(self):
        results, errors, cancelled = run_module.run_trials(
            lambda task, index: {"task": task["id"], "trial": index}, [({"id": "t"}, i) for i in range(1, 4)], 2)
        self.assertEqual(sorted(r["trial"] for r in results), [1, 2, 3])
        self.assertEqual((errors, cancelled), ([], []))

class RescoreResumeTest(unittest.TestCase):
    def test_finished_results_skipped_and_incomplete_set_aside(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            done, infra, partial, fresh = (root / f"trial-{i}/score/0.1.3/final" for i in range(1, 5))
            write_json(done / "result.json", {"status": "scored"})
            write_json(infra / "result.json", {"status": "infra_error"})
            (partial / "gcc-build").mkdir(parents=True)
            jobs = [("task", "product", None, {}, out) for out in (done, infra, partial, fresh)]
            pending, skipped = score.pending_jobs(jobs)
            self.assertEqual(skipped, [done])
            self.assertEqual([job[4] for job in pending], [infra, partial, fresh])
            self.assertFalse(infra.exists())
            self.assertTrue((infra.parent / "incomplete/final-1/result.json").is_file())
            self.assertTrue((partial.parent / "incomplete/final-1/gcc-build").is_dir())
            # 汇总不读取被移开的结果
            result = {"mode": "score", "meta": {"agent_version": "pi"}, "scorer": {"version": "0.1.3"},
                      "status": "scored"}
            write_json(infra.parent / "incomplete/final-1/result.json", result)
            self.assertEqual(aggregate.load_results([root], "0.1.3"), [])

    def test_rescore_refuses_uncalibrated_scorer(self):
        with tempfile.TemporaryDirectory() as tmp:
            run = Path(tmp) / "eval-x"
            out = run / "trials/t/trial-1/score/0.1.3/final"
            job = ({"id": "t"}, Path(tmp) / "product", None, {}, out)
            with patch.object(score, "RUNS", Path(tmp)), patch.object(score, "rescore_jobs", return_value=[job]), \
                 patch.object(score, "calibration_status", return_value={"status": "stale"}), \
                 patch("docker_runner.DockerExecutor") as docker, \
                 patch.object(score.pipeline, "score_product") as scored, \
                 patch.object(sys, "argv", ["score.py", "--rescore", "eval-x"]):
                docker.return_value.images = {}
                with self.assertRaises(SystemExit) as caught:
                    score.main()
            self.assertEqual(caught.exception.code, 2)
            scored.assert_not_called()
            record = json.loads(next((run / "score" / score.scorer_version()).glob("*/rescore.json")).read_text())
            self.assertEqual(record["status"], "failed")

class RunManifestTest(unittest.TestCase):
    def test_manifest_fields_and_vocabulary(self):
        with tempfile.TemporaryDirectory() as tmp:
            manifest = runs.new_manifest("eval-1", "eval", operation="generate")
            self.assertEqual((manifest["schema"], manifest["run_id"], manifest["status"]), (1, "eval-1", "running"))
            runs.finish(Path(tmp), manifest, "completed", passed=True)
            written = json.loads((Path(tmp) / "run.json").read_text())
            self.assertEqual((written["status"], written["passed"]), ("completed", True))
            self.assertIn("finished_at", written)
        with self.assertRaisesRegex(ValueError, "kind"):
            runs.new_manifest("x", "validation")
        with self.assertRaisesRegex(ValueError, "status"):
            runs.check_manifest(dict(runs.new_manifest("x", "eval"), status="passed"))
        with self.assertRaisesRegex(ValueError, "passed"):
            runs.check_manifest(dict(runs.new_manifest("x", "eval"), passed="yes"))

if __name__ == "__main__": unittest.main()
