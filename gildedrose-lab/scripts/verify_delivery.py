#!/usr/bin/env python3
"""验证实际实验结果与交付证据一致性；不重新执行已通过的测试集。"""
import datetime as dt
import hashlib
import json
from pathlib import Path
import re
from urllib.parse import unquote
import shutil
import tempfile
from source_snapshot import verify_snapshot

ROOT=Path(__file__).resolve().parents[1]
DOCS=ROOT.parent/'docs'
RUN=ROOT/'runs'/(ROOT/'artifacts/latest-run.txt').read_text().strip()
EVIDENCE=ROOT/'artifacts'/RUN.name


def read(path):
    return json.loads(Path(path).read_text())


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def main():
    checks=[]
    def check(name, condition):
        if not condition:
            raise AssertionError(name)
        checks.append(name)
    summary=read(RUN/'summary.json')
    check('完整流水线成功',summary['status']=='passed')
    repo=ROOT/'external/GildedRose-Refactoring-Kata'
    manifest=verify_snapshot(repo, ROOT/'external/source_manifest.json', summary['commit'])
    check('上游工作树仅有cpp且20个文件哈希一致',len(manifest['files'])==20 and {p.name for p in repo.iterdir()} <= {'cpp','.git'})
    with tempfile.TemporaryDirectory(prefix='gildedrose-cpp-snapshot-') as temporary:
        snapshot=Path(temporary)/'source'
        shutil.copytree(repo/'cpp', snapshot/'cpp')
        check('无Git的附件源码快照通过校验',verify_snapshot(snapshot, ROOT/'external/source_manifest.json', summary['commit'])==manifest)
        target=snapshot/'cpp/src/GildedRose.cc'
        target.write_bytes(target.read_bytes()+b'\n// altered snapshot\n')
        try:
            verify_snapshot(snapshot, ROOT/'external/source_manifest.json', summary['commit'])
        except ValueError:
            check('无Git快照检测到源码修改并拒绝执行',True)
        else:
            check('无Git快照检测到源码修改并拒绝执行',False)
    scope=read(RUN/'source_scope.json')
    expected_upstream={'/repo/cpp/src/GildedRose.cc','/repo/cpp/test/cpp_texttest/GildedRoseTextTests.cc'}
    check('最新编译范围仅为cpp',scope['upstream_scope']=='cpp/' and not scope['other_upstream_languages_compiled'] and set(scope['upstream_compiled_files'])==expected_upstream)
    for historical in [ROOT/'runs/acceptance-20261021', ROOT/'runs/verified-20261021', RUN]:
        commands=read(historical/'baseline/build/compile_commands.json')
        files=[record['file'] for record in commands]
        check(historical.name+'实际编译未涉及其他上游语言',set(f for f in files if f.startswith('/repo/'))==expected_upstream and all(Path(f).suffix in {'.cc','.cpp','.cxx','.c++'} for f in files))
    check('基线13965例且零失败',read(RUN/'baseline/test_result.json')['failed']==0 and summary['cases']==13965)
    check('基线目标源码哈希保持一致',sha(ROOT/'external/GildedRose-Refactoring-Kata/cpp/src/GildedRose.cc')==summary['source_sha256'])
    check('测试数据哈希未变化',sha(RUN/'cases.json')==summary['cases_sha256'])
    rows=read(RUN/'mutation_results.json')
    check('28项变异记录完整且ID唯一',len(rows)==28 and len({r['id'] for r in rows})==28)
    check('20个行为变异均经断言检出',sum(r['kind']=='behavior' and r['status']=='killed' and r['build_returncode']==0 for r in rows)==20)
    check('5个编译错误均有GCC文件行列',sum(r['kind']=='compile' and r['status']=='caught' and any(d.get('locations') for d in r['diagnostics']) for r in rows)==5)
    check('1个链接错误单独捕获',sum(r['kind']=='link' and r['status']=='caught' for r in rows)==1)
    check('2个等价对照均未误报',sum(r['kind']=='equivalent_control' and r['status']=='survived' for r in rows)==2)
    check('每个变异都有补丁和独立源码',all((RUN/'mutants'/r['id']/'mutation.diff').is_file() and sha(RUN/'mutants'/r['id']/'source/GildedRose.cc')==r['mutant_sha256'] for r in rows))
    for where in ['baseline','llm']:
        coverage=read(RUN/where/'coverage/coverage.json')
        check(where+'覆盖率双格式一致',coverage['parsers_agree'])
        check(where+'原始gcov快照完整',len(list((RUN/where/'coverage/raw').glob('*.gcda')))==1 and len(list((RUN/where/'coverage/raw').glob('*.gcno')))==1)
    check('原始业务覆盖计数29/29与38/38',summary['coverage']['text']['line']=={'covered':29,'total':29,'percent':100.0} and summary['coverage']['text']['branch_all']=={'covered':38,'total':38,'percent':100.0})
    freeze=read(ROOT/'benchmark/freeze.json')
    check('所有冻结文件哈希未变',all(sha(ROOT/'benchmark'/name)==value for name,value in freeze['files'].items()))
    events=[json.loads(line) for line in (RUN/'logs/events.jsonl').read_text().splitlines()]
    oracle=next(e for e in events if e['kind']=='llm_oracle_started')
    check('模型答案冻结早于运行评分',dt.datetime.fromisoformat(freeze['frozen_at'])<dt.datetime.fromisoformat(oracle['time']))
    for earlier in [ROOT/'runs/acceptance-20261021', ROOT/'runs/verified-20261021', RUN]:
        records=[json.loads(line) for line in (earlier/'logs/events.jsonl').read_text().splitlines()]
        check(earlier.name+'任何基线执行均晚于预测冻结',all(dt.datetime.fromisoformat(e['started_at'])>dt.datetime.fromisoformat(freeze['frozen_at']) for e in records if e.get('stage')=='contract-binary'))
    scores=read(RUN/'llm/scores.json')
    check('模型44题评分一致',scores['rose']['correct']==24 and scores['stress']['correct']==20 and scores['protocol_valid'])
    source=(ROOT/'benchmark/labyrinth.cc').read_text()
    if_lines=[line for line in source.splitlines() if line.lstrip().startswith('if (')]
    max_depth=max((len(line)-len(line.lstrip()))//4 for line in if_lines)
    check('合成源码91个if且最深22层',len(if_lines)==91 and max_depth==22)
    # D06 命中最深的回退内层 if，D01/D02 命中深链最终返回。
    gcov=(RUN/'llm/coverage/text/labyrinth.cc.gcov').read_text()
    check('最深回退条件实际执行',bool(re.search(r'\n\s*[1-9][0-9]*:\s*177:.*if \(z % 2 != 0\)',gcov)))
    check('20级门控最终返回实际执行',bool(re.search(r'\n\s*[1-9][0-9]*:\s*174:.*return score \+ 1000',gcov)))
    before=read(EVIDENCE/'container-inspect-before.json')[0]
    after=read(EVIDENCE/'container-inspect-after.json')[0]
    mounts={m['Destination']:m for m in before['Mounts']}
    check('源码和脚本只读挂载',all(mounts[n]['Type']=='bind' and not mounts[n]['RW'] for n in ['/repo','/lab']))
    check('产物写入宿主机挂载',mounts['/work']['Type']=='bind' and mounts['/work']['RW'])
    check('容器禁网并使用只读根文件系统',before['HostConfig']['NetworkMode']=='none' and before['HostConfig']['ReadonlyRootfs'])
    check('容器实际退出0',after['State']['ExitCode']==0 and not after['State']['Running'])
    check('完整流水线入口在容器内为Python',before['Path']=='python3' and before['Args']==['/lab/scripts/pipeline.py','--output','/work/'+RUN.name])
    dockerfile=(ROOT/'docker/Dockerfile').read_text()
    check('Dockerfile不复制项目代码',not re.search(r'^\s*(COPY|ADD)\b',dockerfile,re.MULTILINE|re.IGNORECASE))
    check('四份报告已集中到docs',all((DOCS/name).is_file() for name in ['执行报告.md','全量执行过程.md','变异明细.md','模型盲测逐题结果.md']))
    broken=[]
    for markdown in list(DOCS.rglob('*.md'))+[ROOT.parent/'README.md',ROOT.parent/'AGENTS.md']:
        for target in re.findall(r'\]\(([^)]+)\)',markdown.read_text()):
            if '://' in target or target.startswith('#'):
                continue
            if not (markdown.parent/unquote(target)).exists():
                broken.append((markdown.name,target))
    check('报告内所有本地证据链接可解析',not broken)
    patterns=[re.compile(rb'ctx7sk-[A-Za-z0-9_-]{20,}'),re.compile(rb'sk-(?:proj-|ant-)[A-Za-z0-9_-]{20,}'),
              re.compile(rb'AKIA[A-Z0-9]{16}'),re.compile(rb'Bearer\s+[A-Za-z0-9._-]{30,}')]
    secret_files=[]
    for folder in [ROOT/name for name in ['artifacts','notes','benchmark','deliverables']]+[DOCS]:
        for f in folder.rglob('*'):
            if f.is_file() and f.suffix in ['.json','.jsonl','.log','.md','.txt']:
                blob=f.read_bytes()
                if any(p.search(blob) for p in patterns):
                    secret_files.append(str(f.relative_to(ROOT.parent)))
    check('日志附件未发现所扫描的常见凭据模式',not secret_files)
    result={'verified_at':dt.datetime.now(dt.timezone.utc).isoformat(),'passed':True,'checks':checks,
            'note':'这是证据一致性与链接核验；凭据模式扫描不是对任意秘密的完备证明。'}
    (ROOT/'deliverables/verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps(result,ensure_ascii=False,indent=2))


if __name__=='__main__':
    main()
