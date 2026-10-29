"""D019 的诊断归因、单指标失败及校准契约。"""
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import common
import container_steps
import calibrate
import judge
import pipeline
from audit import Audit
from test_docker_wiring import ScriptedExecutor, REFERENCE_PRODUCT

ERROR = '/product/tests/t.cc:748:51: error: hex escape sequence out of range'


class ClangFailureTest(unittest.TestCase):
    def test_all_errors_must_point_to_frozen_tests(self):
        classify = lambda text: container_steps.test_compile_errors(text, {'/product/tests/t.cc'})
        self.assertEqual(classify(ERROR)[0]['line'], 748)
        self.assertTrue(classify(ERROR+'\n1 error generated.\nninja: build stopped: subcommand failed.'))
        for line in ('/repo/a.h:2:1: error: bad', '/product/tests/unknown.h:2:1: error: bad',
                     '/product/tests/../../repo/a.h:2:1: error: bad', 'ld: error: bad',
                     "undefined reference to `f`", 'clang++: error: unable to execute command: Killed',
                     'PLEASE submit a bug report', 'Segmentation fault'):
            with self.subTest(line=line):
                self.assertEqual(classify(ERROR+'\n'+line), [])
        self.assertEqual(classify('ninja: build stopped: subcommand failed.'), [])
        # 超出旧诊断摘要的第 30 行也必须参与归因。
        self.assertEqual(classify((ERROR+'\n')*31+'/repo/a.h:2:1: error: bad'), [])

    def score(self, tmp, product_origin=True, prep=False):
        class FailingClang(ScriptedExecutor):
            def run_phase(inner, label, *args):
                if label == 'clang-build':
                    return {'status':'build_failed','reason':'compile_or_link_error',
                            'failure_origin':'product_tests' if product_origin else None,
                            'errors':container_steps.test_compile_errors(ERROR, {'/product/tests/t.cc'})}
                return super().run_phase(label,*args)
        ex = FailingClang(['S.A'], failing_on={'v02-run':['S.A']})
        result = pipeline.assess_product(ex, common.load_task('gildedrose-update-quality'), REFERENCE_PRODUCT,
                                        Path(tmp)/'out', {}, Audit(Path(tmp)/'audit'), prep=prep)
        return result, ex

    def test_product_error_keeps_gcc_coverage_and_variants(self):
        with tempfile.TemporaryDirectory() as tmp:
            result, ex = self.score(tmp)
        self.assertEqual(result['status'], 'scored', result.get('infra_detail'))
        self.assertEqual(result['metrics']['M1_e2e'], 0)
        self.assertIsNone(result['metrics']['M1_valid'])
        self.assertEqual(result['metrics']['V2'], 1)
        self.assertEqual(result['metrics']['C1'], 1)
        self.assertEqual(result['metrics']['M2'], 1)
        self.assertNotIn('M1', result.get('not_applicable', {}))
        self.assertNotIn('mull', [c['label'] for c in ex.calls])
        self.assertEqual(result['metric_failures']['M1']['reason'], 'clang_test_compile_failed')
        self.assertIn('metric_failures', judge.stable_view(result))

    def test_unknown_origin_and_reference_preparation_still_fail(self):
        for origin, prep in ((False,False),(True,True)):
            with self.subTest(origin=origin,prep=prep), tempfile.TemporaryDirectory() as tmp:
                result, ex = self.score(tmp, origin, prep)
                self.assertEqual(result['status'], 'infra_error')
                self.assertIn('clang_build_failed', result['infra_detail'])
                self.assertFalse(result['variants'])

    def test_calibration_requires_null_field_and_failure_reason(self):
        expected = {'metrics':{'M1_valid':None},'metric_failures':{'M1':'clang_test_compile_failed'}}
        self.assertTrue(calibrate.check_hard(expected, {}))
        result = {'metrics':{'M1_valid':None},'metric_failures':{'M1':{'reason':'clang_test_compile_failed','errors':[{}]}}}
        self.assertEqual(calibrate.check_hard(expected,result), [])
