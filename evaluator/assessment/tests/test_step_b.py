"""D018 的不适用口径、冻结分母和兼容边界。"""
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import calibrate
import common
sys.path.insert(0, str(common.COMMON))
# coverage 名称可能被其他测试预加载为第三方包。
import importlib.util
spec = importlib.util.spec_from_file_location('step_b_coverage', common.COMMON / 'coverage.py')
coverage = importlib.util.module_from_spec(spec)
spec.loader.exec_module(coverage)


class StepBFixesTest(unittest.TestCase):
    def test_no_gcda_creates_output_and_reports_missing(self):
        with tempfile.TemporaryDirectory() as tmp:
            out = Path(tmp) / 'new' / 'coverage'
            result = coverage.collect_targets(Path(tmp) / 'empty', ['/repo/a.cc'], out, None)
            self.assertEqual(result['missing_sources'], ['/repo/a.cc'])
            self.assertTrue((out / 'coverage.json').is_file())

    def test_na_requires_null_and_exact_reason_not_missing_metric(self):
        expected = {'relations': [{'metric': 'M1_e2e', 'op': 'na', 'reason': 'header_only'}]}
        check = lambda metrics, reasons: calibrate.check_relations('CAL', expected, {'CAL': metrics}, {}, {'CAL': reasons})
        self.assertEqual(check({'M1_e2e': None}, {'M1': 'header_only'}), ([], []))
        for metrics, reasons in [({}, {'M1':'header_only'}), ({'M1_e2e':0}, {'M1':'header_only'}),
                                 ({'M1_e2e':None}, {}), ({'M1_e2e':None}, {'M1':'zero_mutants'})]:
            self.assertTrue(check(metrics, reasons)[0])
        self.assertTrue(calibrate.check_relations('CAL', {'relations':[{'metric':'M4','op':'==','value':0}]},
                                                  {'CAL':{'M4':None}}, {})[0])

    def test_report_shows_m4_v2_and_na_reason(self):
        report = {'run_id':'fixture', 'scorer_version':'0.4.0', 'scorer_code_sha256':'abc', 'passed':True,
                  'partial':False, 'rounds':2, 'images':{}, 'tasks':{'t':{'samples':['CAL']}},
                  'samples':{'CAL':{'task':'t', 'status':'scored', 'invalid_reason':None, 'passed':True,
                                   'problems':[], 'not_applicable':{'M1':'header_only'},
                                   'metrics':{'M1_e2e':None, 'M4':1, 'V2':1, 'C1':0.8, 'S1':0}}}}
        table = calibrate.markdown(report)
        self.assertIn('| M4 | V2 |', table)
        self.assertIn('| — | 1.000 | 1.000 | 0.800 | 0.000 | M1: header_only |', table)
