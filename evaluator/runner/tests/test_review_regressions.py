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

class TrialCancellationTest(unittest.TestCase):
    def test_running_trial_finishes_after_other_worker_fails(self):
        second_started = threading.Event()
        started = []

        def work(task, index):
            started.append(index)
            if index == 1:
                if not second_started.wait(2):
                    raise AssertionError("第二个 worker 未启动")
                raise OSError("docker failure")
            if index == 2:
                second_started.set()
                time.sleep(0.1)
            return {"task": task["id"], "trial": index, "status": "finished"}

        results, errors, cancelled = run.run_trials(work, [({"id": "t"}, i) for i in range(1, 6)], 2)
        self.assertEqual(sorted(started), [1, 2])
        self.assertEqual([r["trial"] for r in results], [2])
        self.assertEqual([e["trial"] for e in errors], [1])
        self.assertEqual(sorted(c["trial"] for c in cancelled), [3, 4, 5])

    def check_stops_before_observer_collects_failure(self, failure):
        started = []
        collect = run.as_completed

        def delayed_collect(futures):
            time.sleep(0.05)  # 主线程尚未收取结果时，worker 已有机会领取下一项。
            return collect(futures)

        def work(task, index):
            started.append(index)
            if index == 1:
                if isinstance(failure, Exception):
                    raise failure
                return dict(failure, task=task["id"], trial=index)
            return {"task": task["id"], "trial": index, "status": "finished"}

        with patch.object(run, "as_completed", delayed_collect):
            results, errors, cancelled = run.run_trials(work, [({"id": "t"}, i) for i in range(1, 6)], 1)
        self.assertEqual(started, [1])
        self.assertEqual([e["trial"] for e in errors], [1])
        self.assertEqual(sorted(c["trial"] for c in cancelled), [2, 3, 4, 5])
        self.assertEqual(len(results), 0 if isinstance(failure, Exception) else 1)

    def test_exception_stops_worker_before_next_trial(self):
        self.check_stops_before_observer_collects_failure(OSError("docker create failed"))

    def test_exhausted_infrastructure_results_stop_new_trials(self):
        for failure in ({"status": "agent_error", "scores": {}},
                        {"status": "finished", "scores": {"final": {"status": "infra_error"}}}):
            with self.subTest(failure=failure):
                self.check_stops_before_observer_collects_failure(failure)

class RescoreRecoveryTest(unittest.TestCase):
    def test_reference_or_old_fingerprint_results_are_rescored(self):
        for mismatch in ("calibration", "code_sha256", "task", "images", None):
            with self.subTest(mismatch=mismatch), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                task = load_task("gildedrose-update-quality")
                product, out = root / "product", root / "score/0.1.3/final"
                (product / "tests").mkdir(parents=True)
                (product / "tests/a.cc").write_text("// frozen fixture\n")
                freeze_product(product)
                calibration = {"status": "passed", "run_id": "calibration-current"}
                result = {"status": "scored", "scorer": {"version": score.scorer_version(),
                          "code_sha256": score.scorer_code_sha256(), "calibration": calibration},
                          "task": {"task_json_sha256": task["_sha256"]}, "images": {},
                          "product": {"manifest_sha256": sha256_file(product / "manifest.json")}}
                if mismatch == "calibration":
                    result["scorer"]["calibration"] = {"status": "stale"}
                elif mismatch == "code_sha256":
                    result["scorer"]["code_sha256"] = "old"
                elif mismatch == "task":
                    result["task"]["task_json_sha256"] = "old"
                elif mismatch == "images":
                    result["images"] = {"gcc": {"id": "old"}}
                write_json(out / "result.json", result)
                pending, skipped = score.pending_jobs([(task, product, None, {}, out)], {task["id"]: calibration}, {})
                self.assertEqual(len(pending), int(mismatch is not None))
                self.assertEqual(len(skipped), int(mismatch is None))

    def test_truncated_current_result_can_be_set_aside(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            task = load_task("gildedrose-update-quality")
            product = root / "final"
            (product / "tests").mkdir(parents=True)
            (product / "tests/a.cc").write_text("// frozen fixture\n")
            freeze_product(product)
            old = root / "trials" / task["id"] / "trial-1/score/0.1.2/final"
            current = old.parent.parent / "0.1.3/final"
            write_json(old / "result.json", {"mode": "score", "meta": {"agent_version": "fixture", "trial": 1, "phase": "final"},
                       "task": {"id": task["id"]}, "product": {"path": str(product),
                       "manifest_sha256": sha256_file(product / "manifest.json")}})
            current.mkdir(parents=True)
            (current / "result.json").write_text('{"status":')
            with patch.object(score, "REPO", root):
                pending, skipped = score.pending_jobs(score.rescore_jobs(root, "0.1.3"))
            self.assertEqual(len(pending), 1)
            self.assertEqual(skipped, [])
            self.assertEqual((current.parent / "incomplete/final-1/result.json").read_text(), '{"status":')

    def test_docker_failure_and_interruption_finish_rescore_record(self):
        for error in (RuntimeError("docker unavailable"), KeyboardInterrupt()):
            with self.subTest(error=type(error).__name__), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                job = ({"id": "t"}, root / "product", None, {}, root / "eval-x/trials/t/trial-1/score/0.1.3/final")
                with patch.object(score, "RUNS", root), patch.object(score, "rescore_jobs", return_value=[job]), \
                     patch("docker_runner.DockerExecutor", side_effect=error), \
                     patch.object(sys, "argv", ["score.py", "--rescore", "eval-x"]):
                    with self.assertRaises(BaseException):
                        score.main()
                record = json.loads(next((root / "eval-x/score" / score.scorer_version()).glob("*/rescore.json")).read_text())
                self.assertEqual(record["status"], "failed")
                self.assertIn("finished_at", record)

if __name__ == "__main__": unittest.main()
