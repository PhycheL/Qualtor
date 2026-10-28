"""核对命令不能把缺失的分母报告为成功。"""
import contextlib
import io
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import apply_review


class MissingBaselineTest(unittest.TestCase):
    def test_requested_task_without_baseline_fails_verification(self):
        with tempfile.TemporaryDirectory() as folder:
            bank = Path(folder)
            task_id = "exercism-binary"
            task = bank / task_id
            task.mkdir()
            original = TOOLS.parent / task_id / "task.json"
            (task / "task.json").write_bytes(original.read_bytes())
            with patch.object(apply_review.common, "BENCHMARK", bank), \
                    patch.object(sys, "argv", ["apply_review.py", "--tasks", task_id]), \
                    contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(apply_review.main(), 1)


if __name__ == "__main__":
    unittest.main()
