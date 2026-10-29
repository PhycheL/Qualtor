#!/usr/bin/env python3
"""在锁定 GCC 环境中生成入库配置头，并核对重复生成的逐字节一致性。

spec JSON 是维护者的出题输入，不进入公开 build 契约。输入树只读挂载，命令只能在
禁网容器的 /work 构建目录中写入；生成后的头文件与命令、工具和全部输入哈希一同登记。
"""
import argparse
import json
from pathlib import Path
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / 'evaluator/assessment'), str(REPO / 'evaluator/common'),
               str(REPO / 'evaluator/toolchains')]
from audit import Audit
from docker_runner import DockerExecutor
from environment_build import isolated_run
from runs import new_manifest, write_manifest, finish
from common import check_run_id, sha256_file, write_json


def relative_header(value):
    path = Path(value)
    if path.is_absolute() or '..' in path.parts or path.suffix not in ('.h', '.hh', '.hpp', '.hxx'):
        raise ValueError('输出必须是相对路径的配置头文件')
    return path


def generate(input_root, source_root, spec, run_dir):
    input_root, source_root, run_dir = map(lambda p: Path(p).resolve(), (input_root, source_root, run_dir))
    if set(spec) != {'environment', 'commands', 'tools', 'outputs'}:
        raise ValueError('生成规格必须包含 environment、commands、tools、outputs')
    for key in ('commands', 'tools'):
        if not isinstance(spec[key], list) or not spec[key] or any(
                not isinstance(c, list) or not c or not all(isinstance(a, str) for a in c) for c in spec[key]):
            raise ValueError('命令和工具版本检查必须为非空 argv 数组')
    if not isinstance(spec['outputs'], dict) or not spec['outputs']:
        raise ValueError('需要声明生成的配置头')
    for output, target in spec['outputs'].items():
        relative_header(output)
        relative_header(target)
    inputs = {}
    for path in sorted(input_root.rglob('*')):
        if '.git' in path.relative_to(input_root).parts:
            continue
        if path.is_symlink():
            raise ValueError('预生成输入不能含符号链接')
        if path.is_file():
            inputs[str(path.relative_to(input_root))] = sha256_file(path)
    audit = Audit(run_dir / 'evidence')
    executor = DockerExecutor(audit, run_dir / 'evidence', run_dir.name)
    task = {'build': {'environment': spec['environment']}}
    image = executor.image_for(task, 'gcc')
    control = run_dir / 'control'
    control.mkdir()
    write_json(control / 'spec.json', spec)
    program = '''import json,os,sys
sys.path.insert(0,'/common')
from audit import Audit
spec=json.load(open('/control/spec.json'))
os.chdir('/work')
audit=Audit('/work/audit')
versions=[]
for index,command in enumerate(spec['tools']):
    result=audit.run('version-'+str(index),command,timeout=60)
    if result['returncode']: raise RuntimeError(result['stderr_log'])
    versions.append({'command':command,'stdout':result['stdout'],'stderr':result['stderr']})
for index,command in enumerate(spec['commands']):
    result=audit.run('generate-'+str(index),command,timeout=900)
    if result['returncode']: raise RuntimeError(result['stderr_log'])
json.dump(versions,open('/work/versions.json','w'),indent=2)
'''
    hashes = []
    for iteration in (1, 2):
        work = run_dir / f'round-{iteration}'
        work.mkdir()
        isolated_run(audit, executor.docker, image, ['python3', '-c', program],
                     run_dir / f'container-{iteration}',
                     {'/input': (input_root, True), '/control': (control, True),
                      '/common': (REPO / 'evaluator/common', True), '/work': (work, False)})
        current = {}
        for output, target in spec['outputs'].items():
            path = work / output
            if path.is_symlink() or not path.is_file() or not path.resolve().is_relative_to(work):
                raise ValueError('生成输出不存在或越过构建目录：' + output)
            current[target] = sha256_file(path)
        hashes.append(current)
    if hashes[0] != hashes[1]:
        raise ValueError('两轮预生成配置头不一致')
    for output, target in spec['outputs'].items():
        path = source_root / target
        if path.exists() and sha256_file(path) != hashes[0][target]:
            raise ValueError('入库配置头与重复生成结果不同：' + target)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes((run_dir / 'round-1' / output).read_bytes())
    record = {'environment': executor.environment(task), 'commands': spec['commands'],
              'tools': json.loads((run_dir / 'round-1/versions.json').read_text()),
              'inputs': inputs, 'outputs': hashes[0], 'output_paths': spec['outputs'],
              'reproduced': True, 'evidence_run': run_dir.name}
    metadata = source_root / 'SOURCE.json'
    provenance = json.loads(metadata.read_text()) if metadata.is_file() else {}
    provenance.setdefault('generated', []).append(record)
    provenance.setdefault('files', {}).update(hashes[0])
    write_json(metadata, provenance)
    write_json(run_dir / 'summary.json', record)
    return record


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input', type=Path, required=True)
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--spec', type=Path, required=True)
    parser.add_argument('--run-id', required=True)
    args = parser.parse_args()
    check_run_id(args.run_id)
    root = REPO / 'runs' / args.run_id
    root.mkdir(exist_ok=False)
    manifest = new_manifest(args.run_id, 'prepare', mode='pregenerate')
    write_manifest(root, manifest)
    try:
        generate(args.input, args.source, json.loads(args.spec.read_text()), root)
        finish(root, manifest, 'completed', passed=True)
    except BaseException as error:
        finish(root, manifest, 'failed', error=str(error))
        raise


if __name__ == '__main__':
    main()
