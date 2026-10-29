#!/usr/bin/env python3
"""公开 CLI 的环境失败路径：缺镜像、缺包均在模型调用前退出。

缺包镜像是专用故障夹具，只修改镜像标签元数据，不安装或移除主环境的包；结束时删除。
临时配方使用本轮唯一名称，清理前核对字节，避免覆盖用户材料。
"""
import copy
import json
import os
from pathlib import Path
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / 'evaluator/assessment'), str(REPO / 'evaluator/common')]
from audit import Audit
from build_contract import environment_tag, load_environment
from common import check_run_id, write_json
from docker_runner import DockerExecutor
from runs import new_manifest, write_manifest, finish


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run-id', required=True)
    args = parser.parse_args()
    check_run_id(args.run_id)
    root = REPO / 'runs' / args.run_id
    root.mkdir(exist_ok=False)
    manifest = new_manifest(args.run_id, 'eval', mode='environment_failures', framework_selftest=True)
    write_manifest(root, manifest)
    audit = Audit(root / 'evidence')
    temporary, images, checks = [], [], {}
    executor = DockerExecutor(audit, root / 'evidence', args.run_id)
    directory = REPO / 'agents/toolchains/environments'
    original, _ = load_environment('bank-20261021', directory)
    (root / 'source').mkdir()
    (root / 'source/a.cc').write_text('int value() { return 1; }\n')
    write_json(root / 'scenario.json', [{'tool': 'write', 'args': {'path': 'tests/a.cc', 'content': 'must not execute'}}])
    try:
        for index, case in enumerate(('missing-image', 'missing-package')):
            part = root / case
            part.mkdir()
            recipe = copy.deepcopy(original)
            recipe.update(name='verify-' + root.name[-11:] + '-' + case,
                          packages={'libqualtor-missing-dev': '1.0'}, libraries=[], generators=[],
                          imported_compile_definitions={}, imported_compile_options={})
            path = directory / (recipe['name'] + '.json')
            if path.exists():
                raise ValueError('故障夹具配方已存在：' + str(path))
            write_json(path, recipe)
            temporary.append((path, path.read_bytes()))
            write_json(part / 'recipe.json', recipe)
            _, digest = load_environment(recipe['name'], directory)
            tag = environment_tag(recipe, digest, 'gcc')
            if case == 'missing-package':
                context = part / 'context'
                context.mkdir()
                (context / 'Dockerfile').write_text('FROM ' + executor.images['gcc']['id'] + '\n'
                    + 'LABEL org.qualtor.environment.recipe-sha256="' + digest + '"\n')
                images.append(tag)
                built = audit.run('build-fault-fixture', executor.docker + ['build', '--network', 'none',
                    '--tag', tag, str(context)], env=dict(os.environ, DOCKER_BUILDKIT='0'), timeout=120)
                if built['returncode']:
                    raise RuntimeError(built['stderr_log'])
            task = {'id': case, 'title': '环境失败路径', 'source_root': str(root / 'source'),
                    'target_sources': ['a.cc'], 'include_dirs': ['.'], 'visible_files': ['a.cc'],
                    'allowed_test_files': ['tests/*.cc'], 'budget': {'repair_rounds': 3},
                    'test_timeout_seconds': 5, 'build': {'environment': recipe['name']}}
            write_json(part / 'task.json', task)
            result = audit.run(case, [sys.executable, '-B', str(REPO / 'agents/run.py'),
                '--task', str(part / 'task.json'), '--output', str(part / 'output'),
                '--scenario', str(root / 'scenario.json')], timeout=180)
            logs = '\n'.join(p.read_text(errors='replace') for p in (part / 'output').rglob('*.stderr.log'))
            checks[case] = {'exit_2': result['returncode'] == 2,
                            'no_generation_attempt': not (part / 'output/generation-attempts').exists(),
                            'specific_evidence': ('No such image' in logs if case == 'missing-image'
                                                  else 'libqualtor-missing-dev' in logs)}
        passed = all(all(values.values()) for values in checks.values())
        write_json(root / 'summary.json', {'passed': passed, 'checks': checks})
        finish(root, manifest, 'completed', passed=passed)
        print(json.dumps(checks, ensure_ascii=False))
        return 0 if passed else 1
    except BaseException as error:
        finish(root, manifest, 'failed', error=str(error))
        raise
    finally:
        for tag in images:
            result = audit.run('remove-fault-fixture', executor.docker + ['image', 'rm', tag])
            if result['returncode']:
                raise RuntimeError('故障夹具镜像清理失败：' + result['stderr_log'])
        for path, contents in temporary:
            if path.read_bytes() != contents:
                raise ValueError('临时配方被修改，保留供核对：' + str(path))
            path.unlink()


if __name__ == '__main__':
    raise SystemExit(main())
