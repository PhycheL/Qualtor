#!/usr/bin/env python3
"""步骤 A 的真实 pi 剧本验收：混合 C/C++、宏三类编译单元、失败修复及独立评测；不计为题目或模型成绩。"""
import argparse
import json
from pathlib import Path
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / 'evaluator/runner'),str(REPO / 'evaluator/assessment'),str(REPO / 'evaluator/common')]
from audit import Audit
from docker_runner import DockerExecutor
from runs import new_manifest,write_manifest,finish
import common,host,pipeline

HEADER = '''#ifdef __cplusplus
extern "C" {
#endif
int evaluate(int x);
int c_support(void);
int cpp_support(void);
#ifdef __cplusplus
}
#endif
'''
GUARD = '''#if FEATURE_NUMBER != 7
#error FEATURE_NUMBER must reach every compilation unit
#endif
'''
C_GUARD = '''#if __STDC_VERSION__ != 199901L
#error C99 required
#endif
'''
GOOD = GUARD + '''#include "api.h"
#include <gtest/gtest.h>
TEST(BuildContract, AllUnitsUseFeatureMacro) {
  EXPECT_EQ(FEATURE_NUMBER * 2 + 1, evaluate(1));
  EXPECT_EQ(FEATURE_NUMBER * 2, evaluate(0));
}
'''


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run-id',required=True)
    args=parser.parse_args();common.check_run_id(args.run_id)
    root=common.RUNS/args.run_id
    root.mkdir(exist_ok=False)
    manifest=new_manifest(args.run_id,'eval',mode='step_a_contract',framework_selftest=True)
    write_manifest(root,manifest)
    source=root/'source';source.mkdir()
    files={'api.h':HEADER,
           'target.c':GUARD+C_GUARD+'#include "api.h"\nint evaluate(int x) { return c_support()+cpp_support()+(x>0?1:0); }\n',
           'support.c':GUARD+C_GUARD+'#include "api.h"\nint c_support(void) { return FEATURE_NUMBER; }\n',
           'support.cc':GUARD+'#include "api.h"\nint cpp_support(void) { return FEATURE_NUMBER; }\n'}
    for rel,text in files.items():(source/rel).write_text(text)
    task=common.load_task('md4c-html')
    task.update(id='step-a-build-contract',title='步骤 A 构建契约验收夹具',target_sources=['target.c'],include_dirs=['.'],
                visible={'files':list(files)},variants=[],hidden={},
                source={'root':str(source.relative_to(REPO)),'files':{r:common.sha256_file(source/r) for r in files}},
                build={'support_sources':['support.c','support.cc'],'c_standard':'c99',
                       'defines':['FEATURE_NUMBER=7'],'compile_options':['-fno-strict-aliasing','-fwrapv']})
    task['_dir']=root
    common.write_json(root/'assessment-task.json',{k:v for k,v in task.items() if not k.startswith('_')})
    task['_sha256']=common.sha256_file(root/'assessment-task.json')
    common.write_json(root/'task.json',host.public_task(task))
    plan=[{'tool':'write','args':{'path':'tests/generated.cc','content':'invalid C++ source'}},
          {'tool':'build_and_test','args':{}},
          {'tool':'write','args':{'path':'tests/generated.cc','content':GOOD}},
          {'tool':'build_and_test','args':{}}]
    common.write_json(root/'scenario.json',plan)
    audit=Audit(root/'evidence/host')
    result=audit.run('generate',['python3',str(REPO/'agents/run.py'),'--task',str(root/'task.json'),
             '--scenario',str(root/'scenario.json'),'--output',str(root/'generation')],timeout=600)
    if result['returncode']:raise RuntimeError(result['stderr_log'])
    first=common.read_json(root/'generation/attempts/attempt-1/result.json')
    final=common.read_json(root/'generation/attempts/attempt-2/result.json')
    executor=DockerExecutor(audit,root/'evidence',args.run_id)
    assessed=pipeline.assess_product(executor,task,root/'generation/final',root/'assessment',{},audit,prep=True)
    coverage=assessed['counts'].get('coverage',{})
    checks={'compile_failure_recorded':first['status']=='build_failed','repair_passed':final['status']=='passed',
            'independent_assessment':assessed['status']=='scored',
            'c_mutants_present':bool(assessed.get('raw_mutants')),
            'only_target_mutated':all('/target.c:' in m['id'] for m in assessed.get('raw_mutants',[])),
            'positive_c_coverage':(assessed.get('metrics') or {}).get('C1',0)>0,
            'macro_compile_manifests_checked':all(s['status']=='built' for k,s in assessed['steps'].items() if k.endswith('build'))}
    summary={'passed':all(checks.values()),'checks':checks,'coverage':coverage,
             'note':'剧本框架验收，无真实模型调用；每次构建内置检查所有编译单元的标准、宏、选项和插桩边界。'}
    common.write_json(root/'summary.json',summary)
    finish(root,manifest,'completed',passed=summary['passed'])
    print(json.dumps(summary,ensure_ascii=False))
    return 0 if summary['passed'] else 1


if __name__=='__main__':
    raise SystemExit(main())
