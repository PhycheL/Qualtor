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

class VariantTreeTest(unittest.TestCase):
    def setUp(self):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.root = Path(tmp.name)
        source = self.root / 'source'
        source.mkdir()
        for name, text in {'a.cpp':'#include "a.h"\nint f(){ return value(); }\n',
                           'a.h':'inline int value(){ return 1; }\n', 'dep.cpp':'int dep(){ return 0; }\n'}.items():
            (source / name).write_text(text)
        self.task = common.load_task('gildedrose-update-quality')
        self.task.update(_dir=self.root, source={'root':str(source), 'files':{p.name:common.sha256_file(p) for p in source.iterdir()}},
                         target_sources=['a.cpp'], include_dirs=['.'], visible={'files':['a.cpp','a.h','dep.cpp']},
                         build={'support_sources':['dep.cpp']}, variants=[])
        v = self.root / 'hidden/variants/header/a.h'
        v.parent.mkdir(parents=True)
        v.write_text('inline int value(){ return 2; }\n')
        self.variant = {'id':'header','kind':'handwritten','expect':'fail','files':{'a.h':common.sha256_file(v)}}
        self.task['variants'] = [self.variant]

    def test_quoted_include_uses_in_place_copy_and_same_compile_unit_list(self):
        import pipeline
        from audit import Audit
        from test_docker_wiring import ScriptedExecutor
        common.validate_task(self.task)
        product = self.root / 'product/tests'
        product.mkdir(parents=True)
        (product / 't.cc').write_text('// test\n')
        ex = ScriptedExecutor(['S.A'])
        assessment = pipeline.ProductAssessment(ex, self.task, product.parent, self.root/'out', {}, Audit(self.root/'audit'))
        result = assessment._variant(1, self.variant, ['S.A'])
        call = ex.calls[0]
        copied, ro = call['mounts']['repo']
        self.assertTrue(ro)
        self.assertNotIn('variant', call['mounts'])
        self.assertEqual(call['job']['target_sources'], ['/repo/a.cpp'])
        self.assertEqual(call['job']['support_sources'], ['/repo/dep.cpp'])
        self.assertEqual((copied/'a.h').read_text(),'inline int value(){ return 2; }\n')
        self.assertEqual((copied/'a.cpp').read_bytes(),(common.source_root(self.task)/'a.cpp').read_bytes())
        self.assertEqual(len(result['source_tree_sha256']),64)
        from host_executor import HostExecutor
        assessment.ex=HostExecutor()
        self.assertEqual(assessment.target_paths(copied), [str(copied/'a.cpp')])
        self.assertEqual((common.source_root(self.task)/'a.h').read_text(),'inline int value(){ return 1; }\n')

    def test_support_source_and_invisible_header_rejected(self):
        for rel in ['dep.cpp','hidden.h']:
            self.variant['files']={rel:'0'*64}
            with self.assertRaisesRegex(common.TaskError, '只能替换'):
                common.validate_task(self.task)

    def test_hash_mismatch_rejected_before_compilation(self):
        self.variant['files']['a.h']='0'*64
        with self.assertRaisesRegex(common.TaskError,'哈希不一致'):
            common.copy_variant_tree(self.task,self.variant,self.root/'copy')
        self.task['source']['files']['a.cpp']='0'*64
        with self.assertRaisesRegex(common.TaskError,'哈希不一致'):
            common.copy_variant_tree(self.task,self.variant,self.root/'copy2')
