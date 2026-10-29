"""D018 的头文件/零变异准入门槛，使用已冻结的真实题目材料。"""
import copy
from pathlib import Path
import sys
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import admit


class NotApplicableAdmissionTest(unittest.TestCase):
    def test_header_and_zero_mutants_pass_without_m1(self):
        for tid, reason in (('exercism-circular-buffer','header_only'),('exercism-hello-world','zero_mutants')):
            with self.subTest(task=tid):
                problems, info = admit.check(tid)
                self.assertEqual(problems, [])
                self.assertEqual(info['not_applicable'], reason)
                self.assertIsNone(info['reference_m1'])

    def test_missing_coverage_unstable_reference_and_bad_variants_rejected(self):
        task = admit.common.load_task('exercism-circular-buffer')
        original = admit.common.load_baseline(task)
        changes = [lambda b:b['reference'].update(valid_stable=False),
                   lambda b:b['reference'].update(c1=None),
                   lambda b:b['reference'].update(c1=0.1),
                   lambda b:b['reference'].update(variants=[]),
                   lambda b:b['reference']['variants'][0].update(outcome='build_failed'),
                   lambda b:b['reference']['variants'][0].update(outcome='not_detected'),
                   lambda b:b.update(review_needed=[{'id':'pending'}])]
        for change in changes:
            baseline = copy.deepcopy(original); change(baseline)
            with patch.object(admit.common,'load_baseline',return_value=baseline):
                self.assertTrue(admit.check(task['id'])[0])
        with patch.object(admit.common,'load_coverage_baseline',return_value=None):
            self.assertTrue(admit.check(task['id'])[0])
        task['variants'] = task['variants'][:2]
        with patch.object(admit.common,'load_task',return_value=task):
            self.assertIn('手写变异数量不足或未全部检出',admit.check(task['id'])[0])

    def test_zero_mutants_requires_two_successful_no_report_records(self):
        task = admit.common.load_task('exercism-hello-world')
        original = admit.common.load_baseline(task)
        for evidence in ([], [{'returncode':0,'stdout':'No mutants found','reports':[]}],
                         [{'returncode':1,'stdout':'No mutants found','reports':[]}]*2,
                         [{'returncode':0,'stdout':'','reports':[]}]*2,
                         [{'returncode':0,'stdout':'No mutants found','reports':['report.json']}]*2):
            baseline = copy.deepcopy(original); baseline['zero_mutants_evidence'] = evidence
            with patch.object(admit.common,'load_baseline',return_value=baseline):
                self.assertIn('没有重复验证的零变异原始证据',admit.check(task['id'])[0])
