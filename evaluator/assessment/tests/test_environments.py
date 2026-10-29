"""构建环境输入边界，以及冻结旧题的兼容性。"""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'evaluator/assessment'))
from build_contract import load_environment, validate_environment, environment_tag, environment_find_packages
from build_contract import validate_build, generated_units, cmake_build_args, compile_command_problems


class EnvironmentTests(unittest.TestCase):
    def setUp(self):
        self.directory = ROOT / 'agents/toolchains/environments'
        self.recipe, self.digest = load_environment('bank-20261021', self.directory)

    def test_recipe_is_data_and_rejects_unsupported_inputs(self):
        invalid = []
        for key, value in [('schema', 2), ('snapshot', 'latest'), ('name', '../escape'),
                           ('libraries', ['arbitrary::target']), ('generators', ['bash']),
                           ('cmake_prefix_path', ['/opt/x;execute_process()'])]:
            recipe = copy.deepcopy(self.recipe)
            recipe[key] = value
            invalid.append(recipe)
        for version in ['', '*', '>=1.2', '1.0;touch /tmp/x', None]:
            recipe = copy.deepcopy(self.recipe)
            recipe['packages']['libssl-dev'] = version
            invalid.append(recipe)
        recipe = copy.deepcopy(self.recipe)
        recipe['script'] = 'echo injected'
        invalid.append(recipe)
        for recipe in invalid:
            with self.subTest(recipe=recipe), self.assertRaises(ValueError):
                validate_environment(recipe)

    def test_custom_recipe_is_hashed_by_contents(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / 'custom.json'
            recipe = copy.deepcopy(self.recipe)
            recipe['name'] = 'custom'
            path.write_text(json.dumps(recipe))
            loaded, digest = load_environment(str(path), self.directory)
            self.assertEqual(loaded['name'], 'custom')
            self.assertIn(digest[:12], environment_tag(loaded, digest, 'gcc'))
            path.write_text(json.dumps(recipe, indent=2))
            self.assertNotEqual(digest, load_environment(str(path), self.directory)[1])

    def test_find_packages_is_limited_to_recipe(self):
        self.assertEqual(environment_find_packages(self.recipe, ['Qt5::Core']),
                         'find_package(Qt5 5.15 REQUIRED COMPONENTS Core)\n')
        with self.assertRaises(ValueError):
            environment_find_packages(self.recipe, ['arbitrary::target'])

    def test_contract_copies_are_identical(self):
        self.assertEqual((ROOT / 'agents/generator/build/contract.py').read_bytes(),
                         (ROOT / 'evaluator/assessment/build_contract.py').read_bytes())

    def test_task_contract_rejects_unsupported_libraries_generators_and_paths(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            for name in ('subject.cc', 'api.proto'):
                (root / name).write_text('')
            build = {'environment': 'bank-20261021', 'link_libraries': ['protobuf::libprotobuf'],
                     'codegen': [{'tool': 'protoc', 'inputs': ['api.proto'], 'import_dirs': ['.']}]}
            validate_build(build, ['subject.cc'], ['subject.cc', 'api.proto'], root)
            for change in ({'link_libraries': ['GTest::gtest']}, {'compile_options': ['-fsigned-char']},
                           {'compile_options': ['-funsigned-char']}, {'environment': '../bank-20261021'},
                           {'codegen': [{'tool': 'moc'}]}, {'codegen': [{'tool': 'uic'}]},
                           {'codegen': [{'tool': 'protoc', 'inputs': ['../api.proto'], 'import_dirs': ['.']}]},
                           {'codegen': [{'tool': 'protoc', 'inputs': ['api.proto'], 'import_dirs': ['/tmp']}]}):
                with self.subTest(change=change), self.assertRaises((ValueError, FileNotFoundError)):
                    validate_build({**build, **change}, ['subject.cc'], ['subject.cc', 'api.proto'], root)

    def test_generated_units_are_checked_without_mull_or_source_coverage(self):
        build = {'environment': 'bank-20261021', 'link_libraries': ['Qt5::Core', 'protobuf::libprotobuf'],
                 'codegen': [{'tool': 'moc'}, {'tool': 'protoc', 'inputs': ['api.proto'], 'import_dirs': ['.']}]}
        generated = generated_units(build, '/build')
        self.assertEqual(generated, ['/build/scored_tests_autogen/mocs_compilation.cpp', '/build/api.pb.cc'])
        commands = [{'file': path, 'arguments': ['c++', '-std=c++11', '-include', '/cmake/cxx11_guard.h',
                     '-DQT_CORE_LIB', '-DQT_NO_DEBUG'] + (['--coverage'] if path == '/repo/a.cc' else [])}
                    for path in ['/repo/a.cc', '/product/tests/t.cc', *generated]]
        def check(records, headers=None):
            return compile_command_problems(records, ['/repo/a.cc'], [], ['/product/tests/t.cc'], build,
                                            'coverage', headers, generated, self.recipe)
        self.assertEqual(check(commands), [])
        changed = copy.deepcopy(commands)
        changed[-1]['arguments'].append('--coverage')
        self.assertTrue(check(changed))
        changed[-1]['arguments'].append('-fpass-plugin=/usr/lib/mull-ir-frontend-19')
        self.assertTrue(check(changed))
        self.assertTrue(check(commands[:-1]))

    def test_protoc_keeps_import_relative_paths_and_rejects_collisions(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / 'proto/nested').mkdir(parents=True)
            (root / 'proto/nested/api.proto').write_text('')
            (root / 'other/nested').mkdir(parents=True)
            (root / 'other/nested/api.proto').write_text('')
            (root / 'a.cc').write_text('')
            build = {'environment': 'bank-20261021', 'link_libraries': ['protobuf::libprotobuf'],
                     'codegen': [{'tool': 'protoc', 'inputs': ['proto/nested/api.proto'], 'import_dirs': ['proto']}]}
            visible = ['a.cc', 'proto/nested/api.proto', 'other/nested/api.proto']
            validate_build(build, ['a.cc'], visible, root)
            self.assertEqual(generated_units(build, '/build'), ['/build/nested/api.pb.cc'])
            build['codegen'][0]['inputs'].append('other/nested/api.proto')
            build['codegen'][0]['import_dirs'].append('other')
            with self.assertRaises(ValueError):
                validate_build(build, ['a.cc'], visible, root)

    def test_mull_original_run_timeout_is_optional_and_separate(self):
        from container_steps import phase_mull
        from unittest.mock import Mock
        for timeout in (None, 30000):
            with self.subTest(timeout=timeout), tempfile.TemporaryDirectory() as temp:
                audit = Mock()
                audit.run.return_value = {'returncode': 0, 'timed_out': False,
                    'stdout': 'No mutants found', 'stdout_log': 'out'}
                job = {'out_dir': temp, 'work_dir': temp, 'binary': '/build/scored_tests',
                       'tests': ['S.A'], 'minimum_timeout_ms': 3000, 'allow_zero_mutants': True}
                if timeout:
                    job['test_timeout_ms'] = timeout
                self.assertEqual(phase_mull(job, audit)['status'], 'ok')
                command = audit.run.call_args_list[-1].args[1]
                self.assertIn('--minimum-timeout=3000', command)
                self.assertEqual([x for x in command if x.startswith('--timeout=')],
                                 [] if timeout is None else ['--timeout=30000'])

    def test_runtime_environment_change_invalidates_admission(self):
        import common
        from unittest.mock import patch
        task = common.load_task('gildedrose-update-quality')
        task['build'] = {'environment': 'bank-20261021'}
        with patch.object(common, 'admission_state', return_value={'status': 'admitted'}), \
                patch.object(common, 'load_baseline', return_value={'environment': {'image': 'old'}}):
            self.assertEqual(common.admission_status(task, lambda _: {'image': 'old'})['status'], 'admitted')
            self.assertEqual(common.admission_status(task, lambda _: {'image': 'new'})['status'], 'stale')

    def test_environment_recipe_changes_task_and_admission_fingerprints(self):
        import common
        from unittest.mock import patch
        task = common.load_task('gildedrose-update-quality')
        with patch.object(common, 'task_environment', return_value=(self.recipe, 'a')):
            first = common.task_sha256(task)
        with patch.object(common, 'task_environment', return_value=(self.recipe, 'b')):
            current = common.task_sha256(task)
            self.assertNotEqual(first, current)
            self.assertEqual(common.admission_state(task['id'], current,
                {task['id']: {'task_sha256': first}})['status'], 'stale')

    def test_calibration_checks_recipe_and_runtime_images(self):
        import common
        from unittest.mock import patch
        images = {name: {'id': name} for name in ('gcc', 'clang')}
        environment = {'name': self.recipe['name'], 'recipe_sha256': self.digest, 'images': images}
        record = {'scorer_version': common.assessment_version(), 'scorer_code_sha256': common.assessment_code_sha256(),
                  'samples_sha256': common.samples_sha256(), 'images': {k: v['id'] for k, v in images.items()},
                  'environments': {self.recipe['name']: environment}, 'tasks': {}, 'passed': True}
        with tempfile.TemporaryDirectory() as temp, patch.object(common, 'CALIBRATION_STATUS', Path(temp) / 'state.json'):
            common.write_json(common.CALIBRATION_STATUS, record)
            self.assertEqual(common.calibration_status(images, environment_resolver=lambda _: environment)['status'], 'passed')
            changed = {**environment, 'images': {'gcc': {'id': 'rebuilt'}, 'clang': images['clang']}}
            self.assertEqual(common.calibration_status(images, environment_resolver=lambda _: changed)['status'], 'stale')
            self.assertEqual(common.calibration_status(images)['status'], 'stale')
            with patch.object(common, 'task_environment', return_value=(self.recipe, 'new-recipe')):
                self.assertEqual(common.calibration_status(None)['status'], 'stale')

    def test_stale_environment_denominator_stops_before_any_build(self):
        import common
        import pipeline
        from audit import Audit
        from unittest.mock import Mock, patch
        task = common.load_task('gildedrose-update-quality')
        task['build'] = {'environment': self.recipe['name']}
        executor = Mock(mode='docker', images={}, capabilities={'coverage': True, 'mull': True})
        executor.environment.return_value = {'name': self.recipe['name'], 'images': {'gcc': 'new'}}
        with tempfile.TemporaryDirectory() as temp, patch.object(pipeline, 'load_baseline', return_value={'environment': {}}):
            result = pipeline.assess_product(executor, task, Path(temp) / 'product', Path(temp) / 'out', {}, Audit(Path(temp) / 'audit'))
            self.assertEqual(result['status'], 'infra_error')
            self.assertEqual(result['infra_detail'], 'mutation_baseline_environment_changed')
            executor.run_phase.assert_not_called()

    def test_legacy_task_goldens(self):
        from common import load_task, mull_config_text, sha256_text, task_sha256
        # 只加载提示词纯函数；评测生产代码不导入产品实现。
        # 产品 task 模块的依赖用现有 runner 公开投影后经单独 Python 进程测试，避免 common 同名污染。
        import subprocess
        fixture = json.loads((Path(__file__).parent / 'fixtures/step_c_legacy_a273de2.json').read_text())
        self.assertEqual(len(fixture['tasks']), 115)
        for name, expected in fixture['tasks'].items():
            task = load_task(name)
            self.assertEqual(task_sha256(task), expected['task_sha256'], name)
            self.assertEqual(sha256_text(mull_config_text(task)), expected['mull_config_sha256'], name)
        script = '''import hashlib,json,sys
from pathlib import Path
sys.path.insert(0, "agents")
from generator.task import task_text
fixture=json.loads(Path("evaluator/assessment/tests/fixtures/step_c_legacy_a273de2.json").read_text())
for name, expected in fixture["tasks"].items():
    task=json.loads((Path("benchmark")/name/"task.json").read_text())
    public={**task,"visible_files":task["visible"]["files"],"test_timeout_seconds":task["params"]["test_timeout_seconds"]}
    assert hashlib.sha256(task_text(public).encode()).hexdigest()==expected["task_md_sha256"],name
'''
        subprocess.run([sys.executable, '-B', '-c', script], cwd=ROOT, check=True, capture_output=True)


if __name__ == '__main__':
    unittest.main()
