#!/usr/bin/env python3
"""对步骤 C 的特定 UB 候选取证；仅修改副本，不写题目或评分分母。"""
import argparse
import json
from pathlib import Path
import shutil
import sys

REPO = Path(__file__).resolve().parents[3]
sys.path[:0] = [str(REPO / 'evaluator/assessment'), str(REPO / 'evaluator/common'),
                str(REPO / 'evaluator/toolchains')]
import common
from audit import Audit
from runs import new_manifest, write_manifest, finish
from docker_runner import DockerExecutor
from environment_build import isolated_run

RUNNER = r'''
import json, os, sys
from pathlib import Path
sys.path.insert(0, '/common')
from audit import Audit
audit = Audit(Path('/out/commands'))
spec = json.loads(Path('/out/spec.json').read_text())
flags = ['-std=c++11', '-O0', '-g', '-fPIC', '-fsanitize=address,undefined,pointer-subtract,pointer-compare',
         '-fno-sanitize-recover=all', '-D_GLIBCXX_ASSERTIONS', '-DQT_FORCE_ASSERTS', '-fno-omit-frame-pointer']
libs = []
if spec['task'] == 'qt-mustache':
    arch = audit.run('compiler-multiarch', ['g++-14', '-dumpmachine'])
    assert arch['returncode'] == 0
    multiarch = arch['stdout'].strip()
    qt = Path('/usr/include') / multiarch / 'qt5'
    assert (qt / 'QtCore/qstring.h').is_file()
    libs = ['-DQT_CORE_LIB', '-I' + str(qt), '-I' + str(qt / 'QtCore'), '-lQt5Core']
    for name in ('qstring.h', 'qstringview.h', 'qarraydata.h', 'qvector.h', 'qglobal.h'):
        path = qt / 'QtCore' / name
        if path.is_file():
            Path('/out', name).write_bytes(path.read_bytes())
results = []
for case in spec['cases']:
    folder = Path('/out') / case['name']
    command = ['g++-14', *flags, *['-I/repo/' + x for x in spec['includes']],
               str(folder / 'source.cc'), '/out/' + case['driver'], '-o', str(folder / 'probe'), *libs]
    built = audit.run(case['name'] + '-build', command, timeout=120)
    row = dict(case, build_returncode=built['returncode'])
    if built['returncode'] == 0:
        executed = audit.run(case['name'] + '-run', [str(folder / 'probe')], timeout=30,
            env=dict(os.environ, ASAN_OPTIONS='detect_leaks=0:detect_invalid_pointer_pairs=2'))
        row.update(returncode=executed['returncode'], timed_out=executed['timed_out'],
                   stdout=executed['stdout'], stderr=executed['stderr'],
                   diagnostic=any(s in executed['stderr'] for s in ('AddressSanitizer', 'runtime error:', 'ASSERT', 'Assertion')))
    results.append(row)
    Path('/out/results.json').write_text(json.dumps(results, indent=2) + '\n')
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--task', choices=['humaneval-x-cpp-boost', 'qt-mustache'], required=True)
    parser.add_argument('--run-id', required=True)
    args = parser.parse_args()
    common.check_run_id(args.run_id)
    out = REPO / 'runs' / args.run_id
    out.mkdir(exist_ok=False)
    task = common.load_task(args.task)
    root = common.source_root(task)
    manifest = new_manifest(args.run_id, 'prepare', mode='step_c_sanitizer', task=args.task)
    write_manifest(out, manifest)
    cases = []
    def case(name, source, driver, mid=None, note=None):
        folder = out / name
        folder.mkdir()
        (folder / 'source.cc').write_text(source)
        cases.append({'name': name, 'driver': driver, 'id': mid, 'note': note})
    if args.task == 'humaneval-x-cpp-boost':
        text = (root / 'src/cpp_137.cc').read_text()
        (out / 'driver.cc').write_text('#include <boost/any.hpp>\n#include <string>\n#include <iostream>\n'
            'boost::any compare_one(boost::any,boost::any);\nint main() {\n'
            'std::cout << boost::any_cast<int>(compare_one(std::string("2.5"),3)) << "\\n";\n'
            'std::cout << boost::any_cast<int>(compare_one(3,std::string("2.5"))) << "\\n"; }\n')
        case('original', text, 'driver.cc')
        for line in (25, 40):
            lines = text.splitlines(True)
            lines[line - 1] = lines[line - 1].replace('find(s.begin(),s.end(),',
                'find(s.begin(),std::string::iterator(reinterpret_cast<char*>(42)),')
            assert lines[line - 1] != text.splitlines(True)[line - 1]
            case('range-' + str(line), ''.join(lines), 'driver.cc',
                 f'cxx_replace_scalar_call:/repo/src/cpp_137.cc:{line}:30:{line}:33',
                 '固定 Mull IR 将 end() 返回的 i64 换成 42；源码副本用相同无效指针表示。')
    else:
        text = (root / 'src/mustache.cpp').read_text()
        (out / 'driver.cc').write_text('#include "mustache.h"\n#include <iostream>\n'
            'QString escapeHtml(const QString&);\nint main() {\n'
            'std::cout << escapeHtml("").toStdString() << "ok\\n";\n'
            'Mustache::QtVariantContext c(QVariantHash{}); c.pop();\n'
            'std::cout << c.stringValue(".").toStdString() << "\\n"; }\n')
        (out / 'standalone.cc').write_text('#include "mustache.h"\n#include <iostream>\nint main() {\n'
            'Mustache::QtVariantContext c(QVariantHash{}); Mustache::Renderer r;\n'
            'std::cout << r.render("{{!c}}", &c).toStdString() << "ok\\n"; }\n')
        (out / 'raw.cc').write_text('#include "mustache.h"\n#include <iostream>\nint main() {\n'
            'Mustache::QtVariantContext c(QVariantHash{{"x", "<&>"}}); Mustache::Renderer r;\n'
            'std::cout << r.render("{{{x}}}a", &c).toStdString() << "\\n"; }\n')
        case('original', text, 'driver.cc')
        case('escape-end', text.replace('i < escaped.length()', 'i <= escaped.length()'), 'driver.cc',
             'cxx_lt_to_le:/repo/src/mustache.cpp:34:18:34:19')
        case('empty-context', text.replace('!m_contextStack.isEmpty()', '!false'), 'driver.cc',
             'cxx_replace_scalar_call:/repo/src/mustache.cpp:125:36:125:43',
             '固定 Mull IR 的 bool 返回值 i1 截断 42 为 false。')
        case('standalone-original', text, 'standalone.cc', note='检查原始末尾独占标签路径的 QStringView 前置条件。')
        case('standalone-mutant', text.replace('end <= content.size()', 'end < content.size()'), 'standalone.cc',
             'cxx_le_to_lt:/repo/src/mustache.cpp:568:13:568:15')
        case('raw-original', text, 'raw.cc')
        case('raw-enum', text.replace('tag.escapeMode = Tag::Raw;', 'tag.escapeMode = static_cast<Tag::EscapeMode>(42);'),
             'raw.cc', 'cxx_assign_const:/repo/src/mustache.cpp:448:19:448:20')
    common.write_json(out / 'spec.json', {'task': args.task, 'cases': cases, 'includes': task['include_dirs']})
    (out / 'runner.py').write_text(RUNNER)
    audit = Audit(out / 'host')
    try:
        executor = DockerExecutor(audit, out / 'evidence', args.run_id)
        manifest['environment'] = executor.environment(task)
        write_manifest(out, manifest)
        isolated_run(audit, executor.docker, executor.image_for(task, 'gcc'), ['python3', '/out/runner.py'],
            out / 'container', mounts={'/out': (out, False), '/repo': (root, True),
                                      '/common': (REPO / 'evaluator/common', True)}, timeout=900)
        rows = common.read_json(out / 'results.json')
        original = rows[0]
        passed = (all(r['build_returncode'] == 0 for r in rows)
                  and original.get('returncode') == 0 and not original.get('diagnostic'))
        common.write_json(out / 'summary.json', {'passed': passed, 'results': rows,
            'scope': '源码副本 sanitizer/库前置条件诊断，不是正式评分；结合真实 Mull IR 逐项复核。'})
        finish(out, manifest, 'completed', passed=passed)
        print(json.dumps({'passed': passed, 'results': [{k:r.get(k) for k in ('name','returncode','diagnostic')} for r in rows]}))
        return 0 if passed else 1
    except BaseException as error:
        finish(out, manifest, 'failed', error=str(error))
        raise


if __name__ == '__main__':
    raise SystemExit(main())
