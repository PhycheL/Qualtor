#!/usr/bin/env python3
"""D020 在隔离容器中用 C++11 验证已安装库、生成器、ABI 和分析边界。"""
import argparse
import gzip
import json
import os
from pathlib import Path
import shlex
import sys
import traceback

sys.path.insert(0, '/common')
from audit import Audit, now


def check(mode, recipe, output, summary):
    audit = Audit(output / 'smoke-logs')
    smoke = Path(__file__).resolve().parent / 'environment_smoke'
    build = output / 'smoke-build'
    source = output / 'smoke-input'
    source.mkdir()
    config = source / 'mull.yml'
    config.write_text("mutators:\n  - cxx_all\nincludePaths:\n  - '" + str(smoke / 'subject.cc') + "$'\n")
    env = dict(os.environ, MULL_CONFIG=str(config))

    def call(stage, argv, cwd=output, timeout=180):
        result = audit.run(stage, argv, cwd=cwd, timeout=timeout, env=env)
        if result['returncode'] or result['timed_out']:
            raise RuntimeError(f"{stage} failed; see {result['stderr_log']}")
        if 'Could not find dynamic library' in result['stdout'] + result['stderr']:
            raise RuntimeError('Mull could not find a dynamic library')
        return result['stdout']

    libraries = recipe['libraries']
    packages = {'Boost::headers': ('Boost', 'HAVE_BOOST'), 'OpenSSL::Crypto': ('OpenSSL', 'HAVE_OPENSSL'),
                'ZLIB::ZLIB': ('ZLIB', 'HAVE_ZLIB'), 'protobuf::libprotobuf': ('Protobuf', 'HAVE_PROTOBUF'),
                'protobuf::libprotobuf-lite': ('Protobuf', None), 'Qt5::Core': ('Qt5', 'HAVE_QT')}
    selected = {packages[lib][0] for lib in libraries}
    defines = sorted({packages[lib][1] for lib in libraries if packages[lib][1]})
    # 只有配方声明了生成器才运行相应测试；库目标仍通过 find_package 核查。
    if 'moc' not in recipe['generators'] and 'HAVE_QT' in defines:
        defines.remove('HAVE_QT')
    if 'protoc' not in recipe['generators'] and 'HAVE_PROTOBUF' in defines:
        defines.remove('HAVE_PROTOBUF')
    if recipe['name'] == 'bank-20261021':
        defines += ['BANK_VERSION']
    find = '\n'.join('find_package(Qt5 5.15 REQUIRED COMPONENTS Core)' if p == 'Qt5'
                     else f'find_package({p} REQUIRED)' for p in sorted(selected))
    text = f'''cmake_minimum_required(VERSION 3.20)
project(environment_check LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(GTest 1.12.1 EXACT CONFIG REQUIRED)
{find}
add_executable(env_tests "{smoke}/subject.cc" "{smoke}/tests.cc")
target_compile_options(env_tests PRIVATE -O0 -g -include "{smoke}/cxx11_guard.h")
target_compile_definitions(env_tests PRIVATE {' '.join(defines)})
target_link_libraries(env_tests PRIVATE GTest::gtest_main {' '.join(libraries)})
target_include_directories(env_tests PRIVATE "${{CMAKE_CURRENT_BINARY_DIR}}" "{smoke}")
enable_testing()
include(GoogleTest)
gtest_discover_tests(env_tests DISCOVERY_MODE PRE_TEST)
'''
    if 'HAVE_QT' in defines:
        text += f'target_sources(env_tests PRIVATE "{smoke}/relay.h")\nset_target_properties(env_tests PROPERTIES AUTOMOC ON)\n'
    if 'HAVE_PROTOBUF' in defines:
        # 与两套构建模板相同：固定的 add_custom_command 调用导入目标 protobuf::protoc，输出只写构建目录。
        text += f'''add_custom_command(OUTPUT "${{CMAKE_CURRENT_BINARY_DIR}}/probe.pb.cc" "${{CMAKE_CURRENT_BINARY_DIR}}/probe.pb.h"
  COMMAND protobuf::protoc "--cpp_out=${{CMAKE_CURRENT_BINARY_DIR}}" "-I{smoke}" "{smoke}/probe.proto"
  DEPENDS "{smoke}/probe.proto" protobuf::protoc VERBATIM)
target_sources(env_tests PRIVATE "${{CMAKE_CURRENT_BINARY_DIR}}/probe.pb.cc" "${{CMAKE_CURRENT_BINARY_DIR}}/probe.pb.h")
'''
        version = call('protoc-version', ['protoc', '--version']).strip()
        if recipe['name'] == 'bank-20261021' and version != 'libprotoc 3.21.12':
            raise ValueError('protoc version mismatch')
        summary['protoc'] = version
    if mode == 'gcc':
        text += f'set_source_files_properties("{smoke}/subject.cc" PROPERTIES COMPILE_OPTIONS "--coverage;-fprofile-abs-path")\ntarget_link_options(env_tests PRIVATE --coverage)\n'
    else:
        text += f'set_source_files_properties("{smoke}/subject.cc" PROPERTIES COMPILE_OPTIONS "-fpass-plugin=/usr/lib/mull-ir-frontend-19;-grecord-command-line")\n'
    (source / 'CMakeLists.txt').write_text(text)
    compiler = 'g++-14' if mode == 'gcc' else 'clang++-19'
    summary['compiler'] = call('compiler-version', [compiler, '--version'])
    assert ('14.2.0' if mode == 'gcc' else '19.1.7') in summary['compiler']
    call('cmake-configure', ['cmake', '-S', str(source), '-B', str(build), '-G', 'Ninja',
         '-DCMAKE_BUILD_TYPE=Release', '-DCMAKE_CXX_COMPILER=' + compiler,
         '-DCMAKE_PREFIX_PATH=' + ';'.join(['/opt/googletest', *recipe['cmake_prefix_path']])])
    call('cmake-build', ['cmake', '--build', str(build), '--parallel', '2'], timeout=600)
    commands = json.loads((build / 'compile_commands.json').read_text())
    expected = {str(smoke / 'subject.cc'), str(smoke / 'tests.cc')}
    if 'HAVE_QT' in defines:
        expected.add(str(build / 'env_tests_autogen/mocs_compilation.cpp'))
    if 'HAVE_PROTOBUF' in defines:
        expected.add(str(build / 'probe.pb.cc'))
    assert {c['file'] for c in commands} == expected and len(commands) == len(expected)
    for c in commands:
        args = shlex.split(c['command'])
        assert [a for a in args if a.startswith('-std=')] == ['-std=c++11']
        assert str(smoke / 'cxx11_guard.h') in args
        target = c['file'] == str(smoke / 'subject.cc')
        assert ('--coverage' in args) == (mode == 'gcc' and target)
        assert any(a.startswith('-fpass-plugin=') for a in args) == (mode == 'clang' and target)
    summary['compile_units'] = sorted(expected)
    libraries_found = {p.resolve() for p in Path('/usr').rglob('libstdc++.so.6')}
    assert len(libraries_found) == 1, libraries_found
    summary['libstdcxx'] = list(map(str, libraries_found))
    binary = build / 'env_tests'
    ldd = call('ldd', ['ldd', str(binary)])
    assert 'not found' not in ldd
    (output / 'ldd.txt').write_text(ldd)
    if 'HAVE_PROTOBUF' in defines and mode == 'clang':
        symbols = call('protobuf-abi', ['llvm-nm-19', '--dynamic', '--demangle', '/usr/lib/' +
                       call('multiarch-abi', ['g++-14', '-print-multiarch']).strip() + '/libprotobuf.so'])
        assert 'google::protobuf::Message::DebugString[abi:cxx11]' in symbols
    discovered = json.loads(call('ctest-discover', ['ctest', '--test-dir', str(build), '--show-only=json-v1']))
    prefix = output / 'gcov-prefix'
    env['GCOV_PREFIX'] = str(prefix)
    env['GCOV_PREFIX_STRIP'] = '0'
    results = output / 'gtest-results.json'
    call('gtest-run', [str(binary), '--gtest_output=json:' + str(results)])
    report = json.loads(results.read_text())
    tests = [t for s in report['testsuites'] for t in s['testsuite']]
    expected_count = 1 + sum(d.startswith('HAVE_') for d in defines)
    assert len(discovered['tests']) == len(tests) == expected_count
    assert all(t['status'] == 'RUN' and t['result'] == 'COMPLETED' and not t.get('failures') for t in tests)
    summary['tests'] = {'discovered': expected_count, 'executed': len(tests), 'passed': len(tests)}
    if mode == 'gcc':
        reports = output / 'coverage'
        reports.mkdir()
        # 断言针对未过滤的原始数据：只有被测单元插桩，测试、moc 与 protoc 生成单元都不能产生覆盖数据。
        gcda = sorted(prefix.rglob('*.gcda'))
        assert len(gcda) == 1 and gcda[0].name == 'subject.cc.gcda', gcda
        raw = {}
        for data in gcda:
            notes = Path('/' + str(data.relative_to(prefix))).with_suffix('.gcno')
            data.with_suffix('.gcno').write_bytes(notes.read_bytes())
            call('gcov', ['gcov-14', '-j', '-b', '-c', '-p', str(data)], cwd=reports)
        for path in reports.glob('*.gcov.json.gz'):
            for entry in json.loads(gzip.decompress(path.read_bytes()))['files']:
                if entry.get('lines') or entry.get('functions'):
                    raw.setdefault(entry['file'], []).append(entry)
        assert set(raw) == {str(smoke / 'subject.cc')}, sorted(raw)
        files = {name: entries[0] for name, entries in raw.items()}
        assert any(line['count'] > 0 for file in files.values() for line in file['lines'])
        (output / 'coverage.json').write_text(json.dumps(files, indent=2) + '\n')
        summary['coverage_files'] = list(files)
    else:
        multiarch = call('library-directory', ['g++-14', '-print-multiarch']).strip()
        call('mull', ['mull-runner-19', '--allow-surviving', '--include-not-covered', '--workers=2',
             '--ld-search-path=/usr/lib/' + multiarch, '--reporters=Elements', '--report-dir=' + str(output),
             '--report-name=mutations', str(binary)])
        mutations = json.loads((output / 'mutations.json').read_text())
        assert set(mutations['files']) == {str(smoke / 'subject.cc')}
        mutants = [m for f in mutations['files'].values() for m in f['mutants']]
        assert any(m['status'] == 'Killed' for m in mutants)
        summary['mutations'] = {'total': len(mutants), 'killed': sum(m['status'] == 'Killed' for m in mutants)}


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--toolchain', choices=['gcc', 'clang'], required=True)
    p.add_argument('--recipe', type=Path, required=True)
    p.add_argument('--output', type=Path, required=True)
    args = p.parse_args()
    summary = {'status': 'running', 'started_at': now(), 'toolchain': args.toolchain}
    try:
        check(args.toolchain, json.loads(args.recipe.read_text()), args.output, summary)
        summary['status'] = 'passed'
    except Exception as error:
        summary.update(status='failed', error=str(error))
        traceback.print_exc()
    summary['finished_at'] = now()
    (args.output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary))
    return 0 if summary['status'] == 'passed' else 1


if __name__ == '__main__':
    raise SystemExit(main())
