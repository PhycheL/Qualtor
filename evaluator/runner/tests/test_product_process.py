"""评测通过公开进程接口取消产品，不导入产品私有实现。"""
import json
import os
from pathlib import Path
import signal
import sys
import tempfile
import threading
import time
import unittest
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import host
import run
from product_process import run_product
from audit import Audit


class ProductCancellationTest(unittest.TestCase):
    def test_cancel_reaps_product_and_records_exit(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            marker = root / "pid"
            script = root / "product.py"
            script.write_text(f"import os,time\nfrom pathlib import Path\nPath({str(marker)!r}).write_text(str(os.getpid()))\ntime.sleep(60)\n")
            cancellation = threading.Event()
            def cancel_when_started():
                deadline = time.monotonic() + 5
                while not marker.exists() and time.monotonic() < deadline:
                    time.sleep(0.02)
                cancellation.set()
            thread = threading.Thread(target=cancel_when_started)
            thread.start()
            result = run_product(Audit(root / "audit"), [sys.executable, str(script)], cancellation)
            thread.join()
            self.assertTrue(result["cancelled"])
            self.assertEqual(result["returncode"], -signal.SIGTERM)
            with self.assertRaises(ProcessLookupError):
                os.kill(int(marker.read_text()), 0)
            self.assertTrue(Path(result["stdout_log"]).exists())

    def test_cancelled_generation_is_not_scored(self):
        with tempfile.TemporaryDirectory() as directory, patch.object(host, "score_frozen") as score:
            generator = Mock()
            generator.cancel = None
            generator.generate.return_value = {"status": "cancelled", "cost": {}}
            result = host.trial(None, generator, {"id": "task", "set": "dev"}, {}, Path(directory) / "trial",
                                1, "agent", {})
            score.assert_not_called()
            self.assertEqual(result["scores"], {})
            self.assertIsNotNone(run.infrastructure_failure(result))

    def test_cancel_after_finished_product_does_not_start_scoring(self):
        with tempfile.TemporaryDirectory() as directory, patch.object(host, "score_frozen") as score:
            cancellation = threading.Event()
            generation = {"status": "finished", "cost": {}}
            def finish_product(*_args):
                cancellation.set()
                return generation
            generator = Mock(cancel=cancellation)
            generator.generate.side_effect = finish_product
            result = host.trial(None, generator, {"id": "task", "set": "dev"}, {}, Path(directory) / "trial",
                                1, "agent", {})
            score.assert_not_called()
            self.assertEqual(result["status"], "cancelled")
            self.assertEqual(result["scores"], {})
            self.assertEqual(generation["status"], "finished")  # 不改产品已交付的独立结果

    def test_cancel_before_dispatch_does_not_start_trials(self):
        cancellation = threading.Event()
        cancellation.set()
        work = Mock()
        results, errors, cancelled = run.run_trials(work, [({"id": "task"}, i) for i in range(3)], 2, cancellation)
        work.assert_not_called()
        self.assertEqual((results, errors), ([], []))
        self.assertEqual(len(cancelled), 3)
