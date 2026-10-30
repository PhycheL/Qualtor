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


class DockerCompilerEnvironmentTests(unittest.TestCase):
    """DockerCompiler 的环境选择与预检；docker 命令由测试替身应答，不需要 Docker。"""

    def responder(self, digest, label=None):
        from generator.support import AGENTS, read_json
        base_tag = read_json(AGENTS / 'toolchains/images.json')['gcc']

        def response(stage, command, **kwargs):
            result = {'returncode': 0, 'timed_out': False, 'cancelled': False, 'stdout': '', 'stderr': '',
                      'stderr_log': stage + '.stderr.log'}
            if command[:3] == ['docker', 'context', 'inspect']:
                result['stdout'] = 'unix:///fake.sock\n'
            elif command[-1] == base_tag:
                result['stdout'] = json.dumps([{'Id': 'sha256:base', 'Os': 'linux', 'Architecture': 'arm64',
                                                'RootFS': {'Layers': ['l1']}}])
            elif 'qualtor-env-bank-20261021-gcc' in command[-1]:
                result['stdout'] = json.dumps([{'Id': 'sha256:env-gcc', 'Os': 'linux', 'Architecture': 'arm64',
                    'RootFS': {'Layers': ['l1', 'l2']},
                    'Config': {'Labels': {'org.qualtor.environment.recipe-sha256': label or digest}}}])
            else:
                result.update(returncode=1, stderr='unexpected ' + ' '.join(command))
            return result
        return response

    def test_preflight_failure_is_explicit_and_toolchain_records_environment(self):
        from generator.build import docker as build_docker
        from generator.build.contract import task_environment
        task = {'build': {'environment': 'bank-20261021', 'link_libraries': ['ZLIB::ZLIB']}}
        recipe, digest = task_environment(task['build'])
        audit = Mock()
        audit.run.side_effect = self.responder(digest)
        with tempfile.TemporaryDirectory() as temp, patch.object(build_docker, 'Audit', return_value=audit), \
                patch.object(build_docker, 'isolated_run',
                             side_effect=RuntimeError('环境容器执行失败：Environment package mismatch: zlib1g-dev')) as run:
            record = Path(temp) / 'preflight'
            with self.assertRaisesRegex(RuntimeError, 'Environment package mismatch'):
                build_docker.DockerCompiler(record, task=task)
            run.assert_called_once()
            toolchain = json.loads((record / 'toolchain.json').read_text())
            self.assertEqual(toolchain['id'], 'sha256:env-gcc')
            self.assertEqual(toolchain['environment'], {'name': recipe['name'], 'recipe_sha256': digest,
                                                        'gcc_image_id': 'sha256:env-gcc'})
            # 预检的 CMake 输入只含配方声明的包与目标。
            cmake = (record / 'evidence/environment-input/CMakeLists.txt').read_text()
            for target in recipe['libraries']:
                self.assertIn(f'if(NOT TARGET {target})', cmake)

    def test_environment_image_must_match_recipe_label(self):
        from generator.build import docker as build_docker
        from generator.build.contract import task_environment
        task = {'build': {'environment': 'bank-20261021'}}
        _, digest = task_environment(task['build'])
        audit = Mock()
        audit.run.side_effect = self.responder(digest, label='other')
        with tempfile.TemporaryDirectory() as temp, patch.object(build_docker, 'Audit', return_value=audit), \
                patch.object(build_docker, 'isolated_run') as run:
            with self.assertRaisesRegex(ValueError, '配方'):
                build_docker.DockerCompiler(Path(temp) / 'preflight', task=task)
            run.assert_not_called()

    def test_product_cli_exits_with_explicit_error_before_generation(self):
        import run as product_run
        with tempfile.TemporaryDirectory() as temp:
            source = Path(temp) / 'src'
            source.mkdir()
            (source / 'a.cc').write_text('int f() { return 1; }\n')
            task = {'id': 't', 'title': 't', 'source_root': 'src', 'target_sources': ['a.cc'], 'include_dirs': ['.'],
                    'visible_files': ['a.cc'], 'allowed_test_files': ['tests/*.cc'], 'budget': {'repair_rounds': 1},
                    'test_timeout_seconds': 5, 'build': {'environment': 'bank-20261021', 'link_libraries': ['ZLIB::ZLIB']}}
            (Path(temp) / 'task.json').write_text(json.dumps(task))
            argv = ['run.py', '--task', str(Path(temp) / 'task.json'), '--output', str(Path(temp) / 'out'),
                    '--scenario', str(Path(temp) / 'scenario.json')]
            (Path(temp) / 'scenario.json').write_text('[]')
            with patch.object(sys, 'argv', argv), patch.object(host, 'verify_pi', return_value={}), \
                    patch('generator.build.docker.DockerCompiler', side_effect=RuntimeError('构建环境不可用：镜像不存在')), \
                    patch.object(host, 'generate_attempt') as attempt, patch('sys.stderr') as stderr:
                with self.assertRaises(SystemExit) as raised:
                    product_run.main()
            self.assertEqual(raised.exception.code, 2)
            self.assertIn('构建环境不可用', ''.join(c.args[0] for c in stderr.write.call_args_list))
            attempt.assert_not_called()
            self.assertFalse((Path(temp) / 'out/result.json').exists())


class TaskTextTests(unittest.TestCase):
    def test_environment_tasks_add_exactly_two_lines(self):
        from generator.task import task_text
        base = {'id': 't', 'title': 't', 'target_sources': ['a.cc'], 'include_dirs': ['.'], 'visible_files': ['a.cc'],
                'allowed_test_files': ['tests/*.cc'], 'budget': {'repair_rounds': 3}, 'test_timeout_seconds': 5,
                'build': {'defines': ['X=1']}}
        environment = {**base, 'build': {**base['build'], 'environment': 'bank-20261021',
                                         'link_libraries': ['Qt5::Core', 'protobuf::libprotobuf'],
                                         'codegen': [{'tool': 'moc'}, {'tool': 'protoc', 'inputs': ['a.proto'],
                                                                      'import_dirs': ['.']}]}}
        before, after = task_text(base).splitlines(), task_text(environment).splitlines()
        added = [line for line in after if line not in before]
        self.assertEqual(added, ['- 可用的库目标：Qt5::Core, protobuf::libprotobuf。', '- 构建生成器：moc, protoc。'])
        self.assertEqual([line for line in after if line not in added], before)
        plain = {k: v for k, v in base.items() if k != 'build'}
        self.assertNotIn('可用的库目标', task_text(plain))
        self.assertNotIn('构建生成器', task_text(plain))
