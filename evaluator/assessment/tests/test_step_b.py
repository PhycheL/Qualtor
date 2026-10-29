"""D018 的不适用口径、冻结分母和兼容边界。"""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

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
        class InspectingExecutor(ScriptedExecutor):
            def run_phase(inner, label, toolchain, mounts, *args):
                if label == 'v01-build':
                    copied = mounts['repo'][0]
                    self.assertEqual((copied/'a.h').read_text(), 'inline int value(){ return 2; }\n')
                    self.assertEqual((copied/'a.cpp').read_bytes(), (common.source_root(self.task)/'a.cpp').read_bytes())
                return super().run_phase(label, toolchain, mounts, *args)
        ex = InspectingExecutor(['S.A'])
        assessment = pipeline.ProductAssessment(ex, self.task, product.parent, self.root/'out', {}, Audit(self.root/'audit'))
        result = assessment._variant(1, self.variant, ['S.A'])
        call = ex.calls[0]
        copied, ro = call['mounts']['repo']
        self.assertTrue(ro)
        self.assertNotIn('variant', call['mounts'])
        self.assertEqual(call['job']['target_sources'], ['/repo/a.cpp'])
        self.assertEqual(call['job']['support_sources'], ['/repo/dep.cpp'])
        self.assertFalse(copied.exists())
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

    def test_source_and_variant_paths_cannot_traverse_or_use_symlinks(self):
        source = common.source_root(self.task)
        original = dict(self.task['source']['files'])
        for index, rel in enumerate(('../outside.h', '/tmp/outside.h', 'x/../../outside.h')):
            with self.subTest(path=rel):
                self.task['source']['files'] = {rel: original['a.h']}
                with self.assertRaisesRegex(common.TaskError, '不合法的源码路径'):
                    common.copy_variant_tree(self.task, self.variant, self.root/f'bad-{index}')
        self.task['source']['files'] = original
        for index, root in enumerate((source, common.variant_dir(self.task, self.variant))):
            path = root/'a.h'
            data = path.read_bytes()
            other = self.root/f'outside-{index}.h'
            other.write_bytes(data)
            path.unlink(); path.symlink_to(other)
            with self.assertRaisesRegex(common.TaskError, '符号链接'):
                common.copy_variant_tree(self.task, self.variant, self.root/f'link-{index}')
            path.unlink(); path.write_bytes(data)
        (source/'linked-dir').symlink_to(source, target_is_directory=True)
        self.task['source']['files'] = {'linked-dir/a.h': original['a.h']}
        with self.assertRaisesRegex(common.TaskError, '符号链接'):
            common.copy_variant_tree(self.task, self.variant, self.root/'dir-link')

    def test_source_copy_removed_on_copy_build_and_run_failure(self):
        import pipeline
        from audit import Audit
        from test_docker_wiring import ScriptedExecutor
        for failure in ('copy', 'v01-build', 'v01-run'):
            with self.subTest(failure=failure):
                class Failing(ScriptedExecutor):
                    def run_phase(inner, label, *args):
                        if label == failure: raise pipeline.Infra('fixture failure')
                        return super().run_phase(label, *args)
                if failure == 'copy': self.variant['files']['a.h'] = '0'*64
                else: self.variant['files']['a.h'] = common.sha256_file(common.variant_dir(self.task,self.variant)/'a.h')
                out = self.root/failure
                assessment = pipeline.ProductAssessment(Failing(['S.A']), self.task, self.root/'product', out, {}, Audit(self.root/'audit'))
                with self.assertRaises((pipeline.Infra, common.TaskError)):
                    assessment._variant(1, self.variant, ['S.A'])
                self.assertFalse((out/'v01-source').exists())

class HeaderCoverageTest(unittest.TestCase):
    def test_instantiations_and_translation_units_share_source_positions(self):
        import gzip
        import json
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/'data.gz'
            doc={'format_version':'2','files':[{'file':'/repo/./api.h',
                 'lines':[{'line_number':10,'count':0},{'line_number':10,'count':2},{'line_number':11,'count':0}],
                 'functions':[{'name':'f<int>','start_line':10,'start_column':2,'execution_count':0},
                              {'name':'f<double>','start_line':10,'start_column':2,'execution_count':2}]}]}
            with gzip.open(path,'wt') as stream: json.dump(doc,stream)
            a=coverage.parse_json_sources(path,{'/repo/api.h'},headers=True)['/repo/api.h']
            b={'line_counts':{'10':1,'11':3,'20':0},'function_counts':{'10:2':1,'20:3':0}}
            merged=coverage.merge_header_stats([a,b])
            self.assertEqual(merged['line_counts'],{'10':3,'11':3,'20':0})
            self.assertEqual(merged['function']['total'],2)
            frozen=coverage.freeze_headers({'api.h':merged},{'api.h':'digest'})
            sparse=coverage.frozen_header_coverage({'api.h':a},frozen)
            self.assertEqual(sparse['total']['lines'],{'covered':1,'total':3})
            self.assertEqual(sparse['total']['functions'],{'covered':1,'total':2})
            a['line_counts']['999']=10
            extra=coverage.frozen_header_coverage({'api.h':a},frozen)
            self.assertEqual(extra['total'],sparse['total'])
            self.assertEqual(extra['files']['api.h']['outside_frozen_lines'],1)
            self.assertEqual(coverage.frozen_header_coverage({},frozen)['total']['lines'],{'covered':0,'total':3})
            with self.assertRaises(ValueError): coverage.freeze_headers({}, {'missing.h':'hash'})

    def test_header_contract_and_all_unit_instrumentation(self):
        import build_contract as c
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp)
            for rel in ('a.h','a.cc','dep.cc'): (root/rel).write_text('')
            c.validate_targets([],['a.h'],['a.h'],root)
            for targets,headers in [([],None),([],[]),(['a.cc'],['a.h']),([],['a.cc']),([],['../a.h']),([],['a.h','a.h'])]:
                with self.assertRaises(ValueError): c.validate_targets(targets,headers,['a.h','a.cc'],root)
            (root/'link.h').symlink_to(root/'a.h')
            with self.assertRaises(ValueError): c.validate_targets([],['link.h'],['link.h'],root)
            commands=[{'file':p,'arguments':['-std=c++11','-include','/cmake/cxx11_guard.h','--coverage']} for p in ('/repo/dep.cc','/product/t.cc')]
            self.assertEqual(c.compile_command_problems(commands,[],['/repo/dep.cc'],['/product/t.cc'],{},'coverage',['/repo/a.h']),[])
            commands[0]['arguments'].remove('--coverage')
            self.assertTrue(c.compile_command_problems(commands,[],['/repo/dep.cc'],['/product/t.cc'],{},'coverage',['/repo/a.h']))

    def test_legacy_fingerprints_and_mull_configs_match_frozen_08204ac(self):
        fixture=common.read_json(Path(__file__).parent/'fixtures/step_b_legacy.json')
        self.assertEqual(len(fixture['tasks']),103)
        for task_id, expected in fixture['tasks'].items():
            task=common.load_task(task_id)
            with self.subTest(task=task_id):
                self.assertEqual(common.task_sha256(task),expected['task_sha256'])
                self.assertEqual(common.sha256_text(common.mull_config_text(task)),expected['mull_config'])


class ApplicabilityTest(unittest.TestCase):
    def test_na_tasks_skip_clang_and_mull_but_run_variants(self):
        from audit import Audit
        from test_docker_wiring import ScriptedExecutor, REFERENCE_PRODUCT
        import pipeline
        for reason in ('header_only', 'zero_mutants'):
            with self.subTest(reason=reason), tempfile.TemporaryDirectory() as tmp:
                task = common.load_task('gildedrose-update-quality')
                ex = ScriptedExecutor(['S.A'])
                with patch.object(pipeline, 'mutation_not_applicable', return_value=reason):
                    result = pipeline.assess_product(ex, task, REFERENCE_PRODUCT, Path(tmp)/'out', {}, Audit(Path(tmp)/'audit'))
                self.assertEqual(result['status'], 'scored', result.get('infra_detail'))
                self.assertTrue(result['variants'])
                self.assertTrue(all(c['toolchain'] == 'gcc' for c in ex.calls))
                self.assertIsNone(result['metrics']['M1_e2e'])
                self.assertIsNone(result['metrics']['M1_valid'])

    def test_zero_mutants_not_allowed_at_scoring(self):
        from container_steps import phase_mull
        from unittest.mock import Mock
        with tempfile.TemporaryDirectory() as tmp:
            audit = Mock()
            audit.run.return_value = {'returncode':0, 'timed_out':False, 'stdout':'No mutants found', 'stdout_log':'out'}
            job = {'out_dir':tmp, 'work_dir':tmp, 'binary':'/build/scored_tests', 'tests':['S.A'],
                   'minimum_timeout_ms':100, 'allow_zero_mutants':False}
            self.assertEqual(phase_mull(job,audit), {'status':'infra_error','reason':'unexpected_mull_reports: 0'})

    def test_zero_mutants_requires_all_three_conditions(self):
        from container_steps import zero_mutants
        good={'returncode':0,'stdout':'[info] No mutants found','timed_out':False}
        self.assertTrue(zero_mutants(good,[]))
        for record,reports in [({**good,'returncode':1},[]),({**good,'stdout':''},[]),(good,['report.json']),({**good,'timed_out':True},[])]:
            self.assertFalse(zero_mutants(record,reports))

    def test_invalid_header_product_has_no_end_to_end_m1(self):
        import judge
        from audit import Audit
        from test_docker_wiring import ScriptedExecutor
        import pipeline
        with tempfile.TemporaryDirectory() as tmp:
            task=common.load_task('gildedrose-update-quality')
            task.update(target_sources=[],target_headers=['cpp/src/GildedRose.h'])
            result=pipeline.assess_product(ScriptedExecutor([]),task,Path(tmp)/'missing',Path(tmp)/'out',{},Audit(Path(tmp)/'audit'))
            self.assertEqual(result['status'],'invalid')
            self.assertIsNone(result['metrics']['M1_e2e'])
            self.assertEqual(result['not_applicable'],{'M1':'header_only','C2':'header_only'})
            self.assertEqual(result['metrics']['V2'],0)
            result['not_applicable']={'M1':'zero_mutants'}
            self.assertIsNone(judge.metrics(result)['M1_e2e'])

    def test_summary_counts_and_comparison_exclude_na(self):
        import aggregate
        results=[]
        for agent in ('A','B'):
            for task in ('source','header','missing'):
                results.append({'task':{'id':task,'set':'dev'},'meta':{'agent_version':agent,'trial':1,'phase':'final'},
                                'status':'infra_error' if task=='missing' else 'scored',
                                'not_applicable':{'M1':'header_only'} if task=='header' else {},
                                'metrics':{'M1_e2e':1 if task=='source' else None}})
        summary=aggregate.summarize(results,'dev','final')['A']['overall']['M1_e2e']
        self.assertEqual(summary,{'mean':1,'tasks':1,'not_applicable_tasks':1,'missing_tasks':1})
        comparison=aggregate.compare(results,'A','B',0.1,{},replicates=20)
        self.assertEqual(comparison['tasks'],['source'])
        self.assertEqual(comparison['excluded_not_applicable'],{'count':1,'tasks':['header']})
