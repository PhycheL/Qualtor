#!/usr/bin/env python3
"""冻结 CAL-30–35 的期望；样本建立在种子分母之后、完整校准之前。"""
from pathlib import Path
import shutil
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
from common import freeze_product, hidden_path, load_task, load_baseline, write_json
from build_step_a_samples import COST

CASES = {
    'CAL-30': ('humaneval-x-cpp-openssl', '链接 OpenSSL；环境配方与双镜像一致'),
    'CAL-31': ('humaneval-x-cpp-openssl', '只测试空输入；保留真实的强弱关系'),
    'CAL-32': ('qt-aes', 'moc 生成单元不计覆盖和变异'),
    'CAL-33': ('orc-bloom-filter', 'protoc 生成单元不计覆盖和变异'),
    'CAL-34': ('humaneval-x-cpp-boost', '第三方环境头文件'),
    'CAL-35': ('exercism-meetup', '环境加纯头文件：M1 不适用、冻结覆盖及手写检出'),
}


def main():
    mapping = {}
    for sid, (tid, description) in CASES.items():
        task = load_task(tid)
        baseline = load_baseline(task)
        if not baseline or 'environment' not in baseline:
            raise ValueError(tid + ' 缺少环境种子分母')
        folder = HERE / tid / sid
        if folder.exists():
            raise ValueError('期望已冻结，不自动覆盖：' + str(folder))
        tests = folder / 'final/tests'
        tests.mkdir(parents=True)
        copies = []
        if sid == 'CAL-31':
            (tests / 'empty.cc').write_text('#include <gtest/gtest.h>\n#include "functions.h"\n'
                'TEST(WeakOpenSSL, EmptyInput) { EXPECT_EQ("None", string_to_md5("")); }\n')
        else:
            for path in sorted(hidden_path(task, 'reference_tests').iterdir()):
                if path.is_file() and path.suffix in ('.cc', '.h'):
                    shutil.copyfile(path, tests / path.name)
                    copies.append('tests/' + path.name)
        freeze_product(folder / 'final')
        write_json(folder / 'generation/cost.json', COST)
        relations = [{'metric': 'M1_e2e', 'op': '>=', 'value': .8}]
        if sid == 'CAL-31':
            relations = [{'metric': 'M1_e2e', 'op': '<', 'ref': 'CAL-30'}]
        if sid == 'CAL-35':
            relations = [{'metric': metric, 'op': 'na', 'reason': 'header_only'}
                         for metric in ('M1_e2e', 'M1_valid')]
            relations += [{'metric': 'C1', 'op': '==', 'value': baseline['reference']['c1']},
                          {'metric': 'M2', 'op': '==', 'value': 1}]
        expected = {'sample': sid, 'original_ids': [sid], 'description': description,
                    'hard': {'status': 'scored', 'tests_default': 'valid'}, 'relations': relations,
                    'environment': baseline['environment'], 'build_boundary': sid in ('CAL-32', 'CAL-33'),
                    **({'reference_copies': copies} if copies else {'reference_copy': None})}
        write_json(folder / 'expected.json', expected)
        mapping[sid] = {'retained': sid, 'task': tid, 'purpose': description,
                        'assertions': ['hard', 'relations', 'environment'] + (['build_boundary'] if expected['build_boundary'] else [])}
        print(tid, sid)
    write_json(HERE / 'step_c_mapping.json', {'mapping': mapping,
        'note': '本轮六项独立保留；若后续替补导致合并，必须保留双方全部适用断言并更新关系引用。'})


if __name__ == '__main__':
    main()
