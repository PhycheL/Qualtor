"""校验只含 cpp/ 的上游快照；交付 ZIP 无需携带其他语言的 Git 对象。"""
import hashlib
import json
from pathlib import Path


def cpp_files(repo):
    repo = Path(repo)
    return {str(p.relative_to(repo)): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in sorted((repo / 'cpp').rglob('*')) if p.is_file()}


def verify_snapshot(repo, manifest_path, revision):
    repo = Path(repo)
    manifest = json.loads(Path(manifest_path).read_text())
    if manifest['commit'] != revision or manifest['scope'] != ['cpp']:
        raise ValueError('Source snapshot revision/scope does not match')
    if {p.name for p in repo.iterdir()} - {'cpp', 'SOURCE.json', 'GildedRoseRequirements.md', 'license.txt'}:
        raise ValueError('Upstream working tree contains files outside cpp/')
    actual = cpp_files(repo)
    if not actual or actual != manifest['files']:
        raise ValueError('C++ source snapshot files or hashes changed')
    return manifest
