#!/usr/bin/env python3
"""重建 D018 的 CAL-21–28；期望先固定，再运行完整 Docker 校准。"""
from pathlib import Path
import re
import shutil
import sys

HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(HERE.parent))
from common import freeze_product, hidden_path, load_task, write_json
from build_step_a_samples import COST

# 从已冻结的 25 行中，弱样本只执行以下 20 行；不是采用产物自己的可执行行数作分母。
CIRCULAR_WEAK_LINES=[11,12,24,25,26,27,28,32,33,34,35,36,40,41,42,43,52,53,54,55]
CIRCULAR_DENOMINATOR=[11,12,16,24,25,26,27,28,32,33,34,35,36,40,41,42,43,46,47,48,49,52,53,54,55]


def relation(metric,op,value):
    return {'metric':metric,'op':op,'value':value}


def na(reason,header=False):
    return [{'metric':k,'op':'na','reason':reason} for k in ('M1_e2e','M1_valid')]+(
            [{'metric':'C2','op':'na','reason':'header_only'}] if header else [])


def remove_test(text,suite,name):
    # 这里删的两个上游测试没有嵌套花括号；精确匹配并要求只匹配一次。
    pattern=rf'^TEST\({re.escape(suite)}, {re.escape(name)}\) \{{[^{{}}]*^\}}\n'
    out,count=re.subn(pattern,'',text,flags=re.M)
    if count!=1:raise ValueError(f'无法唯一定位 {suite}.{name}')
    return out


def sample(tid,sid,description,relations,variants=None,weak=None,code=None,failed=None):
    task=load_task(tid); folder=HERE/tid/sid; tests=folder/'final/tests'
    if tests.exists():shutil.rmtree(tests)
    tests.mkdir(parents=True)
    files=[]
    if code is None:
        for path in sorted(hidden_path(task,'reference_tests').iterdir()):
            if path.is_file() and path.suffix in ('.cc','.h'):
                shutil.copyfile(path,tests/path.name);files.append('tests/'+path.name)
    else:(tests/'tests.cc').write_text(code)
    if weak:
        path=tests/'load_node_test.cc';path.write_text(remove_test(path.read_text(),'NodeTest',weak))
    freeze_product(folder/'final',frozen_at='2026-10-29T00:00:00+00:00')
    write_json(folder/'generation/cost.json',COST)
    hard={'status':'scored','tests_default':'valid','variants':variants or {}}
    if failed is not None:hard['variant_failed_tests']=failed
    if sid=='CAL-24':hard.update(status='invalid',invalid_reason='no_valid_tests',tests_default='failed_on_target')
    expected={'sample':sid,'description':description,'hard':hard,'relations':relations,
              'reference_copies':files} if code is None and not weak else {
              'sample':sid,'description':description,'reference_copy':None,'hard':hard,'relations':relations}
    if sid=='CAL-23':
        expected['frozen_coverage_derivation']={'seed_run':'step-b-seed-circular-20261029-01',
            'denominator_lines':CIRCULAR_DENOMINATOR,'covered_lines':CIRCULAR_WEAK_LINES,
            'calculation':'20 / 25；clear 和 overwrite 的 5 行保留在分母内，但弱样本未实例化这两个成员。'}
    write_json(folder/'expected.json',expected)
    print(tid,sid)


def main():
    sample('yaml-cpp-document','CAL-21','去掉 tagged-null 的唯一检出用例；M4 应降为零',
           [relation('M4','==',0),{'metric':'M1_e2e','op':'<=','ref':'CAL-18'},relation('S1','==',0)],
           {'tagged-null':'not_detected'},weak='LoadNullWithStrTag',failed={'tagged-null':[]})
    header=na('header_only',True)
    sample('exercism-circular-buffer','CAL-22','参考测试；全部 API 的冻结行 25/25、函数 9/9',
           header+[relation('C1','==',1),relation('C3','==',1),relation('M2','==',1)])
    sample('exercism-circular-buffer','CAL-23','少实例化不缩小冻结分母；只调用构造、write、read',
           header+[relation('C1','==',20/25),{'metric':'C1','op':'<','ref':'CAL-22'},relation('M2','<',1)],
           code='#include <gtest/gtest.h>\n#include "circular_buffer.h"\nTEST(Sparse, OneRoundTrip) { circular_buffer::circular_buffer<int> b(2); b.write(7); EXPECT_EQ(7,b.read()); }\n')
    sample('exercism-circular-buffer','CAL-24','原代码上全部失败；M1 不适用仍为 null',
           header+[relation('V2','==',0)],code='#include <gtest/gtest.h>\n#include "circular_buffer.h"\nTEST(Invalid, AlwaysFails) { circular_buffer::circular_buffer<int> b(2); b.write(7); EXPECT_EQ(99,b.read()); }\n')
    sample('exercism-hello-world','CAL-25','Mull 零变异有原始证据，不属于基础设施失败',
           na('zero_mutants')+[relation('M2','==',1),relation('C1','>=',.8)])
    sample('yaml-cpp-node-impl','CAL-26','公共头文件的真实缺陷和手写变异均被检出',
           header+[relation('M4','==',1),relation('M2','==',1)],{'null-string':'detected'},
           failed={'null-string':['NodeTest.LoadTildeAsNull']})
    sample('yaml-cpp-node-impl','CAL-27','去掉 null-string 回归测试后真实缺陷未检出',
           header+[relation('M4','==',0),{'metric':'C1','op':'<=','ref':'CAL-26'}],
           {'null-string':'not_detected'},weak='LoadTildeAsNull',failed={'null-string':[]})
    sample('yaml-cpp-emitter-utils','CAL-28','替换依赖头 exp.h，与被测源文件的 Mull 并存',
           [relation('M1_e2e','>=',.8),relation('M4','==',1)],{'carriage-return':'detected'})

if __name__=='__main__':main()
