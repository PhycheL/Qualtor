"""真实子进程验证中断回收，不调用模型或 Docker。"""
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import tempfile
import time
import unittest
from unittest.mock import patch

AGENTS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(AGENTS))
from common.processes import Cancellation
from generator import host
from generator.support import read_json, write_json


class AuditInterruptionTest(unittest.TestCase):
    def test_keyboard_interrupt_reaps_child_and_finishes_audit(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            marker = root / "child.pid"
            worker = root / "worker.py"
            worker.write_text(f"import os,time\nfrom pathlib import Path\nPath({str(marker)!r}).write_text(str(os.getpid()))\ntime.sleep(60)\n")
            entry = root / "entry.py"
            entry.write_text(f"import sys\nsys.path.insert(0, {str(AGENTS)!r})\nfrom common.audit import Audit\n"
                             f"Audit({str(root / 'audit')!r}).run('child', [sys.executable, {str(worker)!r}], timeout=None)\n")
            parent = subprocess.Popen([sys.executable, str(entry)], start_new_session=True,
                                      stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            child = None
            try:
                deadline = time.monotonic() + 5
                while not marker.exists() and time.monotonic() < deadline:
                    time.sleep(0.02)
                self.assertTrue(marker.exists())
                child = int(marker.read_text())
                os.kill(parent.pid, signal.SIGINT)
                parent.wait(timeout=10)
                with self.assertRaises(ProcessLookupError):
                    os.kill(child, 0)
                events = [json.loads(line) for line in (root / "audit/events.jsonl").read_text().splitlines()]
                self.assertEqual(events[-1]["kind"], "command_end")
                self.assertTrue(events[-1]["cancelled"])
            finally:
                for pid in (child, parent.pid):
                    if pid is not None:
                        try:
                            os.killpg(pid, signal.SIGKILL)
                        except ProcessLookupError:
                            pass
                parent.wait(timeout=5)


class FinalizationCancellationTest(unittest.TestCase):
    def check_cancellation(self, stage, statuses):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "result"
            cancel = Cancellation()
            calls = []
            def generate_attempt(_task, _model, record, *_args):
                calls.append(record)
                generation = {"status": statuses[len(calls) - 1], "started_at": 1, "first_at": 2,
                              "ended_at": 3, "repair_rounds": 0}
                write_json(record / "generation.json", generation)
                (record / "logs/sessions").mkdir(parents=True)
                message = {"type": "message", "message": {"role": "assistant", "timestamp": 1500,
                           "usage": {"input": 10, "cost": {"total": 0.25}}}}
                (record / "logs/sessions/session.jsonl").write_text(json.dumps(message) + "\n")
                for phase in ("first", "final"):
                    (record / phase).mkdir()
                    (record / phase / "test.cc").write_text("retained test\n")
                return generation
            def request_cancel():
                if len(calls) == len(statuses):
                    cancel.signum = signal.SIGINT
                    cancel.set()
            original_extract, original_copytree = host.extract, host.shutil.copytree
            def extract(*args, **kwargs):
                result = original_extract(*args, **kwargs)
                if stage == "extract":
                    request_cancel()
                return result
            def copytree(*args, **kwargs):
                result = original_copytree(*args, **kwargs)
                if stage == "copy":
                    request_cancel()
                return result
            with patch.object(host, "verify_pi", return_value={}), \
                 patch.object(host, "generate_attempt", side_effect=generate_attempt), \
                 patch.object(host, "extract", side_effect=extract), \
                 patch.object(host.shutil, "copytree", side_effect=copytree):
                result = host.generate({"id": "task"}, {}, output, cancel=cancel)
            self.assertEqual(len(calls), len(statuses), "取消后不能发起新的生成尝试")
            self.assertEqual(result, read_json(output / "result.json"))
            for delivered in (result, read_json(output / "generation.json")):
                self.assertEqual(delivered["status"], "cancelled")
                self.assertEqual(delivered["cancellation_signal"], signal.SIGINT)
            for phase in ("first", "final"):
                self.assertEqual(result["cost"][phase]["model_calls"], len(statuses))
                self.assertEqual((output / phase / "test.cc").read_text(), "retained test\n")

    def test_cancel_during_cost_extraction_preserves_result(self):
        self.check_cancellation("extract", ["finished"])

    def test_cancel_after_failed_attempt_does_not_retry_or_duplicate_cost(self):
        self.check_cancellation("extract", ["agent_error", "agent_error"])

    def test_cancel_during_evidence_copy_preserves_retry_cost(self):
        self.check_cancellation("copy", ["agent_error", "finished"])
