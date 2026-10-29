#!/usr/bin/env python3
"""下载步骤 C 候选题的固定提交；只读取上游文件，不执行上游脚本。"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import sys
import tarfile

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / 'evaluator/common'))
from audit import Audit
from runs import new_manifest, write_manifest, finish

CANDIDATES = {
    'CodeGeeX': ('zai-org/CodeGeeX', '2838420b7b4492cf3d16bce5320e26e65960c9e2'),
    'qt-aes': ('bricke/Qt-AES', 'fe02771d'),
    'orc': ('apache/orc', 'bf5f7434'),
    'gzip-hpp': ('mapbox/gzip-hpp', '7546b35a'),
    'qt-mustache': ('robertknight/qt-mustache', '79f65c08'),
    'prometheus-cpp': ('jupp0r/prometheus-cpp', 'a97127c9'),
    'libphonenumber': ('google/libphonenumber', 'b4e9b737'),
    'exiv2': ('Exiv2/exiv2', 'b35c43e7'),
    'libtiff': ('vadz/libtiff', 'd651abc097d91fac57f33b5f9447d0a9183f58e7'),
    'prometheus-client-model': ('prometheus/client_model', 'fa8ad6fec33561be4280a8f0514318c79d7f6cb6'),
}


def fetch(root, name):
    repo, rev = CANDIDATES[name]
    audit = Audit(root / 'evidence' / name)
    output = root / 'upstream' / name
    metadata = root / 'downloads' / (name + '.json')
    archive = root / 'downloads' / (name + '.tar.gz')
    record = {'repository': 'https://github.com/' + repo, 'requested_commit': rev}
    try:
        command = ['curl', '--fail', '--location', '--retry', '3', '--max-time', '180',
                   'https://api.github.com/repos/' + repo + '/commits/' + rev, '--output', str(metadata)]
        done = audit.run('resolve', command, timeout=900)
        if done['returncode']:
            raise RuntimeError(done['stderr_log'])
        commit = json.loads(metadata.read_text())['sha']
        if not commit.startswith(rev):
            raise ValueError('提交不匹配')
        record['commit'] = commit
        done = audit.run('download', ['curl', '--fail', '--location', '--retry', '3', '--max-time', '300',
                        f'https://codeload.github.com/{repo}/tar.gz/{commit}', '--output', str(archive)], timeout=1500)
        if done['returncode']:
            raise RuntimeError(done['stderr_log'])
        record['archive_sha256'] = hashlib.sha256(archive.read_bytes()).hexdigest()
        output.mkdir(parents=True)
        # 只接受普通文件与目录，拒绝归档路径逃逸；不用上游解包脚本。
        with tarfile.open(archive) as tar:
            for member in tar:
                parts = Path(member.name).parts[1:]
                if not parts:
                    continue
                if '..' in parts or Path(*parts).is_absolute():
                    raise ValueError('unsafe archive path')
                if member.isdir():
                    (output / Path(*parts)).mkdir(parents=True, exist_ok=True)
                elif member.isfile():
                    target = output / Path(*parts)
                    target.parent.mkdir(parents=True, exist_ok=True)
                    target.write_bytes(tar.extractfile(member).read())
        record['status'] = 'downloaded'
    except Exception as error:
        record.update(status='failed', error=str(error))
    (root / 'downloads' / (name + '-source.json')).write_text(json.dumps(record, indent=2) + '\n')
    print(name + ': ' + record['status'], flush=True)
    return name, record


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run-id', required=True)
    parser.add_argument('--names', nargs='+', choices=list(CANDIDATES), default=list(CANDIDATES))
    args = parser.parse_args()
    root = REPO / 'runs' / args.run_id
    root.mkdir(exist_ok=False)
    (root / 'downloads').mkdir()
    manifest = new_manifest(args.run_id, 'prepare', mode='step_c_sources', candidates=args.names)
    write_manifest(root, manifest)
    with ThreadPoolExecutor(max_workers=3) as pool:
        records = dict(pool.map(lambda name: fetch(root, name), args.names))
    (root / 'summary.json').write_text(json.dumps(records, indent=2) + '\n')
    passed = all(r['status'] == 'downloaded' for r in records.values())
    finish(root, manifest, 'completed', passed=passed)
    return 0 if passed else 1


if __name__ == '__main__':
    raise SystemExit(main())
