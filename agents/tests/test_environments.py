"""环境错误在模型调用前结束；取消保持产品退出契约。"""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from generator import host


class PreflightTests(unittest.TestCase):
    def test_environment_failure_is_not_a_generation_retry(self):
        with tempfile.TemporaryDirectory() as temp, patch.object(host, 'verify_pi', return_value={}), \
                patch('generator.build.docker.DockerCompiler', side_effect=RuntimeError('missing package')), \
                patch.object(host, 'generate_attempt') as attempt:
            with self.assertRaisesRegex(RuntimeError, 'missing package'):
                host.generate({'id': 'test', 'build': {'environment': 'bank-20261021'}}, {}, Path(temp) / 'out')
            attempt.assert_not_called()

    def test_preflight_cancellation_saves_zero_model_calls_and_empty_snapshots(self):
        cancel = Mock(signum=15)
        cancel.is_set.return_value = True
        with tempfile.TemporaryDirectory() as temp, patch.object(host, 'verify_pi', return_value={}), \
                patch('generator.build.docker.DockerCompiler', side_effect=RuntimeError('cancelled')), \
                patch.object(host, 'generate_attempt') as attempt:
            out = Path(temp) / 'out'
            result = host.generate({'id': 'test', 'build': {'environment': 'bank-20261021'}}, {}, out, cancel=cancel)
            self.assertEqual((result['status'], result['cancellation_signal'], result['generation_attempts']),
                             ('cancelled', 15, 0))
            self.assertEqual(result['cost']['final']['model_calls'], 0)
            for phase in ('first', 'final'):
                self.assertTrue((out / phase / 'manifest.json').is_file())
            self.assertEqual(json.loads((out / 'result.json').read_text())['status'], 'cancelled')
            attempt.assert_not_called()
