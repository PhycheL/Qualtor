#!/usr/bin/env python3
"""步骤 C 的真实 pi 剧本验收；测试产物经公开产品 CLI 生成，再独立评测。"""
import argparse
import copy
import json
from pathlib import Path
import sys

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / 'evaluator/runner'), str(REPO / 'evaluator/assessment'), str(REPO / 'evaluator/common')]
from audit import Audit
from docker_runner import DockerExecutor
from runs import new_manifest, write_manifest, finish
import common
import host
import pipeline

HEADER = '''#pragma once
#include <QObject>
#include <QDate>
#include <zlib.h>
#include "nested/probe.pb.h"
#if FEATURE_NUMBER != 7
#error FEATURE_NUMBER missing
#endif
class Relay : public QObject {
  Q_OBJECT
 public:
  void send(int value) { emit changed(value); }
 signals:
  void changed(int value);
};
'''
BODY = '''int evaluate(int x) {
  StepProbe probe;
  probe.set_value(x);
  return zlibVersion()[0] == '1' && QDate(2024, 2, 29).isValid()
      ? (probe.value() > 0 ? FEATURE_NUMBER : 0) : -1;
}
'''
GOOD = '''#include <gtest/gtest.h>
#include "api.h"
TEST(Environment, LinkedAndGeneratedUnits) {
  EXPECT_EQ(7, evaluate(1));
  EXPECT_EQ(0, evaluate(0));
  EXPECT_EQ(0, evaluate(-1));
  StepProbe p, q;
  p.set_value(7);
  ASSERT_TRUE(q.ParseFromString(p.SerializeAsString()));
  EXPECT_EQ(7, q.value());
  Relay relay;
  int value = 0;
  QObject::connect(&relay, &Relay::changed, [&](int x) { value = x; });
  relay.send(17);
  EXPECT_EQ(17, value);
}
'''


def fixture(root, header_only):
    root.mkdir()
    source = root / 'source'
    source.mkdir()
    files = {'api.h': HEADER + ('inline ' + BODY if header_only else 'int evaluate(int);\n'),
             'nested/probe.proto': 'syntax = "proto3";\nmessage StepProbe { int32 value = 1; }\n'}
    if not header_only:
        files['target.cc'] = '#include "api.h"\n' + BODY
    for rel, text in files.items():
        (source / rel).parent.mkdir(parents=True, exist_ok=True)
        (source / rel).write_text(text)
    task = common.load_task('gildedrose-update-quality')
    task.update(id='step-c-' + ('header' if header_only else 'source'), title='步骤 C 环境及生成单元验收',
                target_sources=[] if header_only else ['target.cc'], include_dirs=['.'],
                visible={'files': list(files)}, variants=[], hidden={},
                source={'root': str(source.relative_to(REPO)),
                        'files': {r: common.sha256_file(source / r) for r in files}},
                build={'environment': 'bank-20261021', 'defines': ['FEATURE_NUMBER=7'],
                       'link_libraries': ['Qt5::Core', 'protobuf::libprotobuf', 'ZLIB::ZLIB'],
                       'codegen': [{'tool': 'moc'}, {'tool': 'protoc', 'inputs': ['nested/probe.proto'], 'import_dirs': ['.']}]})
    if header_only:
        task['target_headers'] = ['api.h']
    replacement = 'api.h' if header_only else 'target.cc'
    variant_file = root / 'hidden/variants/positive-zero' / replacement
    variant_file.parent.mkdir(parents=True)
    variant_file.write_text(files[replacement].replace('probe.value() > 0', 'probe.value() >= 0'))
    task['variants'] = [{'id': 'positive-zero', 'kind': 'handwritten', 'expect': 'fail',
                         'files': {replacement: common.sha256_file(variant_file)}}]
    task['_dir'] = root
    common.write_json(root / 'assessment-task.json', {k: v for k, v in task.items() if not k.startswith('_')})
    task['_sha256'] = common.sha256_file(root / 'assessment-task.json')
    common.validate_task(task)
    common.write_json(root / 'task.json', host.public_task(task))
    return task


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--run-id', required=True)
    args = parser.parse_args()
    common.check_run_id(args.run_id)
    root = common.RUNS / args.run_id
    root.mkdir(exist_ok=False)
    manifest = new_manifest(args.run_id, 'eval', mode='step_c_contract', framework_selftest=True)
    write_manifest(root, manifest)
    audit = Audit(root / 'evidence/host')
    checks, results = {}, {}
    try:
        executor = DockerExecutor(audit, root / 'evidence', args.run_id)
        for name, header_only in [('source', False), ('header', True)]:
            part = root / name
            task = fixture(part, header_only)
            plan = [{'tool': 'write', 'args': {'path': 'tests/generated.cc', 'content': 'invalid C++ source'}},
                    {'tool': 'build_and_test', 'args': {}},
                    {'tool': 'write', 'args': {'path': 'tests/generated.cc', 'content': GOOD}},
                    {'tool': 'build_and_test', 'args': {}}]
            common.write_json(part / 'scenario.json', plan)
            generated = audit.run('generate-' + name, [sys.executable, '-B', str(REPO / 'agents/run.py'),
                '--task', str(part / 'task.json'), '--scenario', str(part / 'scenario.json'),
                '--output', str(part / 'generation')], timeout=900)
            if generated['returncode']:
                raise RuntimeError(generated['stderr_log'])
            first = common.read_json(part / 'generation/attempts/attempt-1/result.json')
            final = common.read_json(part / 'generation/attempts/attempt-2/result.json')
            assessed = pipeline.assess_product(executor, task, part / 'generation/final', part / 'assessment',
                                               {}, audit, prep=True)
            results[name] = assessed
            expected = set(task.get('target_headers') or task['target_sources'])
            checks[name] = {
                'compile_failure_recorded': first['status'] == 'build_failed',
                'repair_passed': final['status'] == 'passed',
                'independent_assessment': assessed['status'] == 'scored',
                'same_gcc_image': common.read_json(part / 'generation/toolchain.json')['id'] == executor.image_for(task, 'gcc')['id'],
                'coverage_only_targets': set((assessed['counts'].get('coverage') or {}).get('files', {})) == expected,
                'variant_detected': [v['outcome'] for v in assessed.get('variants', [])] == ['detected'],
                'generated_units_checked': all(s['status'] == 'built' for k, s in assessed['steps'].items()
                                               if k.endswith('build')),
                'mutation_boundary': (assessed.get('not_applicable', {}).get('M1') == 'header_only' if header_only
                    else bool(assessed.get('raw_mutants')) and all('/target.cc:' in m['id'] for m in assessed['raw_mutants']))}
        passed = all(all(c.values()) for c in checks.values())
        summary = {'passed': passed, 'checks': checks,
                   'note': '真实 pi 的剧本验收，无模型调用；源码、生成单元、替换版本及纯头文件路径均隔离执行。'}
        common.write_json(root / 'summary.json', summary)
        finish(root, manifest, 'completed', passed=passed)
        print(json.dumps(summary, ensure_ascii=False))
        return 0 if passed else 1
    except BaseException as error:
        finish(root, manifest, 'failed', error=str(error))
        raise


if __name__ == '__main__':
    raise SystemExit(main())
