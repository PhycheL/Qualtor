#!/usr/bin/env python3
"""生成过程附件；逐文件 SHA-256、ZIP CRC 与归档内清单双重验证。"""
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import stat
import zipfile
from audit import Audit
import build_report
import verify_delivery

ROOT=Path(__file__).resolve().parents[1]
PROJECT=ROOT.parent
OUT=ROOT/'deliverables'


def content(path):
    return os.readlink(path).encode() if path.is_symlink() else path.read_bytes()


def archive_name(path):
    relative=path.relative_to(PROJECT)
    if '..' in relative.parts:
        raise ValueError('Archive path must stay within the project: '+str(path))
    return relative.as_posix()


def main():
    build_report.main()
    verify_delivery.main()
    archive=OUT/'全量执行过程.zip'
    receipt=OUT/'archive_verification.json'
    checksum=OUT/'全量执行过程.zip.sha256'
    manifest=OUT/'SHA256SUMS.txt'
    excluded={archive,receipt,checksum,manifest}
    def include(path):
        return path not in excluded and '.git' not in Path(archive_name(path)).parts and '__pycache__' not in path.parts and path.name!='.DS_Store' and path.suffix!='.pyc'
    metadata={'snapshot_at':dt.datetime.now(dt.timezone.utc).isoformat(),
              'command':'python3 gildedrose-lab/scripts/package_delivery.py',
              'scope':'上游源码仅含 cpp/，保留所有 C++ 实验和失败记录、docs/ 文档及根目录 README.md、AGENTS.md；排除其他语言、Git 对象、缓存、归档自身及归档完成后生成的校验回执。源码提交和逐文件哈希由 gildedrose-lab/external/source_manifest.json 追溯。',
              'image_included':False,'image_note':'Docker 镜像保留在本机 Docker 中；归档只包含重建定义与镜像元数据。'}
    (OUT/'packaging_snapshot.json').write_text(json.dumps(metadata,ensure_ascii=False,indent=2)+'\n')
    Audit(ROOT/'artifacts/host').event(kind='packaging_snapshot_ready',**metadata)
    candidates=list(ROOT.rglob('*'))+list((PROJECT/'docs').rglob('*'))+[PROJECT/'README.md',PROJECT/'AGENTS.md']
    files=sorted(p for p in candidates if (p.is_file() or p.is_symlink()) and include(p))
    hashes={archive_name(p):hashlib.sha256(content(p)).hexdigest() for p in files}
    manifest.write_text(''.join(f'{digest}  {name}\n' for name,digest in hashes.items()))
    with zipfile.ZipFile(archive,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=6) as bundle:
        for path in files+[manifest]:
            name=archive_name(path)
            if path.is_symlink():
                info=zipfile.ZipInfo(name)
                info.create_system=3
                info.external_attr=(stat.S_IFLNK|0o777)<<16
                bundle.writestr(info,content(path))
            else:
                bundle.write(path,name)
    with zipfile.ZipFile(archive) as bundle:
        bad=bundle.testzip()
        if bad:
            raise AssertionError('ZIP CRC failed: '+bad)
        for name,expected in hashes.items():
            actual=hashlib.sha256(bundle.read(name)).hexdigest()
            if actual!=expected:
                raise AssertionError('archive content hash mismatch: '+name)
        upstream_prefix='gildedrose-lab/external/GildedRose-Refactoring-Kata/'
        upstream_files=[n[len(upstream_prefix):] for n in bundle.namelist() if n.startswith(upstream_prefix)]
        if len(upstream_files)!=20 or any(not n.startswith('cpp/') for n in upstream_files):
            raise AssertionError('Archive must contain only the 20 upstream cpp/ files')
        if any('.git' in Path(n).parts for n in bundle.namelist()):
            raise AssertionError('Archive includes Git metadata or other-language objects')
        entries=len(bundle.infolist())
    digest=hashlib.sha256(archive.read_bytes()).hexdigest()
    checksum.write_text(digest+'  '+archive.name+'\n')
    result={'completed_at':dt.datetime.now(dt.timezone.utc).isoformat(),'archive':str(archive),'bytes':archive.stat().st_size,
            'entries':entries,'file_hashes_verified':len(hashes),'crc_verified':True,'sha256':digest,
            'upstream_scope':'cpp/','upstream_files':len(upstream_files),'git_metadata_excluded':True,
            'manifest_note':'SHA256SUMS.txt 的路径相对项目根目录，与 ZIP 条目名一致；不包含自身或外部归档回执，避免自引用。'}
    receipt.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps(result,ensure_ascii=False,indent=2))


if __name__=='__main__':
    main()
