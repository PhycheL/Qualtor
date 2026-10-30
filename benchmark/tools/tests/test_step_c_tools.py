"""步骤 C 建题工具：导入经 Audit 记录外部命令、只校验重建，以及预生成配置头的幂等与只核对模式。

不需要 Docker：预生成的容器执行由测试替身完成；导入只校验用题库中已入库的上游字节构造临时上游。
"""
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parents[1]
sys.path.insert(0, str(TOOLS))
import bankutil  # noqa: E402
import import_step_c  # noqa: E402
import pregenerate  # noqa: E402


def tree_digest(root):
    return {str(p.relative_to(root)): p.read_bytes() for p in sorted(Path(root).rglob('*')) if p.is_file()}


def events(run_dir):
    path = Path(run_dir) / 'evidence/host/events.jsonl'
    return [json.loads(line) for line in path.read_text().splitlines()] if path.is_file() else []


class ImportVerifyTest(unittest.TestCase):
    def fake_upstream(self, root):
        """gzip-hpp 的 source/ 逐字节取自固定上游提交；据此构造与 fetch_step_c.py 相同布局的临时上游。"""
        task = json.loads((REPO / 'benchmark/gzip-hpp/task.json').read_text())
        upstream = root / 'upstream'
        source = REPO / 'benchmark/gzip-hpp/source'
        for path in source.rglob('*'):
            if path.is_file() and path.name != 'SOURCE.json':
                target = upstream / 'gzip-hpp' / path.relative_to(source)
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(path, target)
        bankutil.write_json(root / 'downloads/gzip-hpp-source.json',
                            {'status': 'downloaded', 'repository': task['source']['repository'],
                             'commit': task['source']['commit']})
        return upstream

    def test_verify_rebuilds_in_scratch_audits_commands_and_never_writes_bank(self):
        before = tree_digest(REPO / 'benchmark/gzip-hpp')
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            upstream = self.fake_upstream(root)
            with patch.object(import_step_c, 'RUNS', root / 'runs'):
                code = import_step_c.main(['--upstream', str(upstream), '--tasks', 'gzip-hpp',
                                           '--run-id', 'verify-test', '--verify'])
            run = root / 'runs/verify-test'
            self.assertEqual(code, 0)
            report = json.loads((run / 'verify.json').read_text())
            self.assertEqual(report, {'identical': True, 'tasks': {'gzip-hpp': []}})
            manifest = json.loads((run / 'run.json').read_text())
            self.assertEqual((manifest['mode'], manifest['status'], manifest['passed']),
                             ('step_c_import_verify', 'completed', True))
            # 手写变异的 git apply 全部经 Audit 记录（命令、退出码与输出日志）。
            ended = [e for e in events(run) if e['kind'] == 'command_end']
            self.assertTrue(ended)
            self.assertTrue(all(e['argv'][:2] == ['git', 'apply'] and e['returncode'] == 0
                                and Path(e['stdout_log']).is_file() for e in ended))
            self.assertEqual({e['stage'] for e in ended if '--check' not in e['argv']},
                             {f'git-apply-gzip-hpp-hw-0{i}' for i in range(1, 6)})
        self.assertEqual(tree_digest(REPO / 'benchmark/gzip-hpp'), before)
        self.assertIsNone(bankutil.COMMAND_AUDIT)
        self.assertEqual(bankutil.BENCHMARK, REPO / 'benchmark')

    def test_verify_reports_differences_and_fails(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            upstream = self.fake_upstream(root)
            changed = upstream / 'gzip-hpp/include/gzip/utils.hpp'
            changed.write_text(changed.read_text() + '\n')
            with patch.object(import_step_c, 'RUNS', root / 'runs'):
                code = import_step_c.main(['--upstream', str(upstream), '--tasks', 'gzip-hpp',
                                           '--run-id', 'verify-diff', '--verify'])
            self.assertEqual(code, 1)
            report = json.loads((root / 'runs/verify-diff/verify.json').read_text())
            self.assertFalse(report['identical'])
            self.assertIn('内容不同：source/include/gzip/utils.hpp', report['tasks']['gzip-hpp'])
            self.assertFalse(json.loads((root / 'runs/verify-diff/run.json').read_text())['passed'])

    def test_compare_ignores_baselines_and_volatile_generation_evidence(self):
        with tempfile.TemporaryDirectory() as temp:
            expected, actual = Path(temp) / 'expected', Path(temp) / 'actual'
            record = {'environment': {'name': 'env', 'recipe_sha256': 'r', 'images': {'gcc': {'id': 'old'}}},
                      'commands': [['cmake']], 'outputs': {'a.h': 'x'}, 'evidence_run': 'run-1'}
            for root, run, image in ((expected, 'run-1', 'old'), (actual, 'run-2', 'rebuilt')):
                bankutil.write_text(root / 'task.json', '{}\n')
                bankutil.write_text(root / 'hidden/mutation_baseline.json', run)
                data = json.loads(json.dumps(record))
                data.update(evidence_run=run)
                data['environment']['images']['gcc']['id'] = image
                bankutil.write_json(root / 'source/SOURCE.json', {'generated': [data]})
            self.assertEqual(import_step_c.compare_task(expected, actual), [])
            bankutil.write_text(actual / 'hidden/README.md', 'extra\n')
            bankutil.write_json(actual / 'source/SOURCE.json', {'generated': [{**record, 'commands': [['make']]}]})
            self.assertEqual(import_step_c.compare_task(expected, actual),
                             ['重建多出：hidden/README.md',
                              '内容不同：source/SOURCE.json（已忽略 generated 的 evidence_run 与镜像 ID）'])

    def test_force_and_verify_are_exclusive(self):
        with self.assertRaises(SystemExit):
            import_step_c.main(['--upstream', '/nonexistent', '--tasks', 'gzip-hpp', '--run-id', 'x',
                                '--verify', '--force'])


class FakeExecutor:
    """替代 DockerExecutor：只提供 pregenerate 用到的接口，不连接 Docker。"""
    images_seen = 0

    def __init__(self, audit, evidence, run_id):
        self.docker = ['docker']

    def image_for(self, task, toolchain):
        return {'id': 'sha256:env-gcc', 'platform': 'linux/arm64'}

    def environment(self, task):
        FakeExecutor.images_seen += 1
        return {'name': 'bank-20261021', 'recipe_sha256': 'recipe',
                'images': {'gcc': {'id': f'sha256:image-{FakeExecutor.images_seen}'}}}


class PregenerateTest(unittest.TestCase):
    spec = {'environment': 'bank-20261021', 'commands': [['cmake', '-S', '/input', '-B', '/work/build']],
            'tools': [['cmake', '--version']], 'outputs': {'build/config.h': 'include/config.h'}}

    def setUp(self):
        self.header = '#define FEATURE 1\n'

    def fake_run(self, audit, docker, image, argv, evidence, mounts):
        work = Path(mounts['/work'][0])
        (work / 'build').mkdir(parents=True)
        (work / 'build/config.h').write_text(self.header)
        (work / 'versions.json').write_text(json.dumps([{'command': ['cmake', '--version'],
                                                         'stdout': 'cmake version 3.31.6\n', 'stderr': ''}]))
        return ''

    def run_generate(self, root, name, write=True):
        with patch.object(pregenerate, 'DockerExecutor', FakeExecutor), \
                patch.object(pregenerate, 'isolated_run', side_effect=self.fake_run):
            run = root / 'runs' / name
            run.mkdir(parents=True)
            return pregenerate.generate(root / 'input', root / 'source', self.spec, run, write=write)

    def test_rerun_replaces_record_and_check_mode_never_writes(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            bankutil.write_text(root / 'input/CMakeLists.txt', 'project(x)\n')
            bankutil.write_json(root / 'source/SOURCE.json', {'repository': 'r', 'generated': [
                {'output_paths': {'build/other.h': 'include/other.h'}, 'outputs': {'include/other.h': 'o'}}]})
            self.run_generate(root, 'first')
            self.run_generate(root, 'second')
            provenance = json.loads((root / 'source/SOURCE.json').read_text())
            # 同一输出只保留最新一条；其他输出的记录不受影响。
            self.assertEqual([list(r['output_paths'].values()) for r in provenance['generated']],
                             [['include/other.h'], ['include/config.h']])
            self.assertEqual(provenance['generated'][-1]['evidence_run'], 'second')
            self.assertEqual((root / 'source/include/config.h').read_text(), self.header)
            before = tree_digest(root / 'source')
            record = self.run_generate(root, 'check-ok', write=False)
            self.assertEqual(record['outputs'], provenance['generated'][-1]['outputs'])
            self.assertTrue(json.loads((root / 'runs/check-ok/summary.json').read_text())['passed'])
            self.assertEqual(tree_digest(root / 'source'), before)
            # 入库配置头被改动：核对失败，仍不写入。
            (root / 'source/include/config.h').write_text('#define FEATURE 2\n')
            before = tree_digest(root / 'source')
            with self.assertRaisesRegex(ValueError, '入库配置头与重复生成结果不同'):
                self.run_generate(root, 'check-bad', write=False)
            self.assertEqual(tree_digest(root / 'source'), before)
            self.assertFalse(json.loads((root / 'runs/check-bad/summary.json').read_text())['passed'])
            # 写入模式同样拒绝悄悄改写已入库的不同配置头。
            with self.assertRaisesRegex(ValueError, '入库配置头与重复生成结果不同'):
                self.run_generate(root, 'write-bad')

    def test_check_mode_requires_a_single_matching_record(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            bankutil.write_text(root / 'input/CMakeLists.txt', 'project(x)\n')
            self.run_generate(root, 'first')
            metadata = root / 'source/SOURCE.json'
            provenance = json.loads(metadata.read_text())
            provenance['generated'].append(provenance['generated'][0])
            bankutil.write_json(metadata, provenance)
            with self.assertRaisesRegex(ValueError, '记录 2 条'):
                self.run_generate(root, 'duplicate', write=False)
            provenance['generated'] = provenance['generated'][:1]
            provenance['generated'][0]['commands'] = [['make']]
            bankutil.write_json(metadata, provenance)
            with self.assertRaisesRegex(ValueError, 'generated 记录与本次生成不一致'):
                self.run_generate(root, 'changed-command', write=False)


if __name__ == '__main__':
    unittest.main()
