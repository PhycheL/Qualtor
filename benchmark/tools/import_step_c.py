#!/usr/bin/env python3
"""从固定归档导入步骤 C 的库与代码生成题；源码不改写，配置头在 Docker 中预生成。

全部外部命令经 evaluator/common/audit.py 记录到 runs/<run-id>/evidence/host（D021-3）；预生成配置头的
Docker 命令记录在各自的 runs/<run-id>-<题目>-config/evidence。--verify 把题目重建到临时目录，
与 benchmark/<题目> 逐字节比较（两类冻结分母不是建题输出，不比较；SOURCE.json 中每次生成都会变化的
证据 run-id 与派生镜像 ID 不比较），不写入题库。
"""
import argparse
import base64
import json
from pathlib import Path
import re
import shutil
import sys
import tempfile
import zlib

import bankutil
from bankutil import (REPO, BASELINES, reset_task_dir, copy_file, write_text, write_json, handwritten_variants,
                      apply_patch_variant, sha256_file)
from import_step_a import finish_task, YAML_OPTIONS
from import_humaneval_x import scan_block_end

TOOLS = Path(__file__).resolve().parent
RUNS = REPO / 'runs'
ENVIRONMENT = 'bank-20261021'
TASKS = ['qt-aes', 'orc-bloom-filter', 'libphonenumber-lite', 'prometheus-cpp-text', 'qt-mustache', 'gzip-hpp',
         'libtiff-strip', 'exiv2-pngchunk']


def metadata(upstream, name):
    record = json.loads((upstream.parent / 'downloads' / (name + '-source.json')).read_text())
    if record['status'] != 'downloaded':
        raise ValueError('上游归档没有验证成功：' + name)
    return record


def source_files(directory, upstream, names):
    for name in names:
        copy_file(upstream / name, directory / 'source' / name)


def remove_function(text, signature):
    begin = text.index(signature)
    brace = text.index('{', begin)
    end = scan_block_end(text, brace)
    return text[:begin] + text[end + 1:]


def finish(directory, upstream, name, targets, support, includes, tier, libraries, codegen=None,
           origins=(), headers=None, build=None, provenance_extra=None, variants=()):
    record = metadata(upstream, name)
    finish_task(directory, record['repository'], record['commit'], targets, support, includes, tier,
                ['environment', *(['codegen'] if codegen else []), name], directory.name,
                '第三方依赖与公开构建配置；源码按固定上游提交入库，开发题。', origins,
                build={'environment': ENVIRONMENT, 'link_libraries': libraries,
                       **({'codegen': codegen} if codegen else {}), **(build or {})},
                target_headers=headers, variants=list(variants) + handwritten_variants(directory),
                generated_by='benchmark/tools/import_step_c.py', provenance_extra=provenance_extra)


QT_MACROS = '''#include <gtest/gtest.h>
#define QCOMPARE(actual, expected) ASSERT_EQ((expected), (actual))
#define QVERIFY(value) ASSERT_TRUE(value)
#define QVERIFY2(value, message) ASSERT_TRUE(value) << message
#define QFAIL(message) FAIL() << message
'''


def qt_aes(args):
    repo = args.upstream / 'qt-aes'
    directory = reset_task_dir('qt-aes', args.force)
    source_files(directory, repo, ['qaesencryption.cpp', 'qaesencryption.h', 'aes_ct_sbox.h', 'LICENSE', 'CMakeLists.txt'])
    text = (repo / 'unit_test/aestest.cpp').read_text()
    text = remove_function(text, 'void AesTest::GenerateKeyIterationCapExceeded()')
    text = remove_function(text, 'void AesTest::CFB256FileRoundTrip_data()')
    start = text.index('void AesTest::CFB256FileRoundTrip()')
    brace = text.index('{', start)
    end = scan_block_end(text, brace)
    original = text[brace + 1:end]
    body = original[original.index('    QAESEncryption encryption'):]
    replacement = ''
    resources = []
    for index, path in enumerate(sorted((repo / 'unit_test').glob('*.txt')), 1):
        data = path.read_bytes()
        encoded = base64.b64encode(len(data).to_bytes(4, 'big') + zlib.compress(data)).decode()
        encoded = '\n'.join('"' + encoded[i:i + 100] + '"' for i in range(0, len(encoded), 100))
        resources.append(f'const char* const aes_resource_{index} =\n{encoded};\n')
        replacement += (f'void AesTest::CFBFile{index}() {{\n'
                        f'    QByteArray input = qUncompress(QByteArray::fromBase64(aes_resource_{index}));\n'
                        f'    ASSERT_EQ({len(data)}, input.size());\n' + body + '}\n')
    text = text[:start] + replacement + text[end + 1:]
    members = (repo / 'unit_test/aestest.h').read_text().split('private:\n', 1)[1].split('};')[0]
    prelude = (QT_MACROS + '#include "qaesencryption.h"\n#include "resources.h"\n'
               + 'class AesTest : public ::testing::Test {\nprotected:\n  void SetUp() override;\n' + members + '};\n')
    text = text.replace('#include "aestest.h"', prelude)
    text = text.replace('void AesTest::initTestCase()', 'void AesTest::SetUp()')
    text = re.sub(r'void AesTest::(?!SetUp)(\w+)\(\)', r'TEST_F(AesTest, \1)', text)
    write_text(directory / 'hidden/reference_tests/upstream_tests.cc', text)
    write_text(directory / 'hidden/reference_tests/resources.h', '#pragma once\n' + '\n'.join(resources))
    write_text(directory / 'hidden/reference_tests/runner_options.cc',
               YAML_OPTIONS.replace('// StrictMock 的连续意外事件会积累失败报告；首个断言失败即抛出，避免变异运行耗尽容器内存。',
                                    '// 首个断言失败即抛出；保留全部测试与输入，避免已检出的变异继续执行大文件往返。'))
    write_text(directory / 'hidden/README.md', '''# Qt AES 隐藏材料

上游 QtTest 机械转换为 GoogleTest；QObject 测试夹具换为 Test，断言保持；每个用例独立初始化。
按执行计划不注册含 500000 次 PBKDF2 的 GenerateKeyIterationCapExceeded。
四个文件往返用例保留全部原始字节，以 Qt qUncompress 解开隐藏头中的压缩输入，不要求 rcc 或额外挂载。
与既有 YAML 题相同，首个断言失败即抛出并结束本次运行，避免已检出的变异继续做大文件往返。
AES-NI 和 constant-time S-box 的条件编译测试沿用上游宏，本题不启用这些可选特性。
''')
    finish(directory, args.upstream, 'qt-aes', ['qaesencryption.cpp'], [], ['.'], 'medium', ['Qt5::Core'],
           [{'tool': 'moc'}], origins=['unit_test/aestest.cpp', 'unit_test/aestest.h', 'unit_test/*.txt'])
    # The unchanged upstream file round-trips take 16.32 s in the instrumented
    # Clang binary (step-c-aes-diagnosis-20261029-01). Mull warms up the whole
    # suite, whereas the validity timeout applies to each individual test.
    task_path = directory / 'task.json'
    task = json.loads(task_path.read_text())
    task['params']['mull_test_timeout_ms'] = 30000
    write_json(task_path, task)
    with (directory / 'hidden/README.md').open('a') as stream:
        stream.write('\nMull 原始全套预热实测 16.32 秒，故本题显式设置 --timeout=30000；'
                     '独立用例有效性超时不变。证据：runs/step-c-aes-diagnosis-20261029-01。\n')


def orc(args):
    from pregenerate import generate
    from runs import new_manifest, write_manifest, finish as finish_run
    repo = args.upstream / 'orc'
    directory = reset_task_dir('orc-bloom-filter', args.force)
    inputs = args.run_dir / 'orc-config-input'
    inputs.mkdir()
    for name in ['c++/src/Adaptor.hh.in', 'c++/include/orc/orc-config.hh.in', 'cmake_modules/CheckSourceCompiles.cmake']:
        copy_file(repo / name, inputs / Path(name).name)
    checks = (repo / 'c++/src/CMakeLists.txt').read_text().split('configure_file (', 1)[0]
    write_text(inputs / 'upstream-checks.cmake', checks)
    write_text(inputs / 'CMakeLists.txt', '''cmake_minimum_required(VERSION 3.20)
project(orc_configuration LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX11_FLAGS "-std=c++11")
set(ORC_VERSION "1.8.10")
find_package(ZLIB REQUIRED)
add_library(orc_zlib ALIAS ZLIB::ZLIB)
include(CheckSourceCompiles.cmake)
include(upstream-checks.cmake)
configure_file(Adaptor.hh.in "${CMAKE_CURRENT_BINARY_DIR}/Adaptor.hh")
configure_file(orc-config.hh.in "${CMAKE_CURRENT_BINARY_DIR}/orc-config.hh")
''')
    run_id = args.run_dir.name + '-orc-config'
    out = RUNS / run_id
    out.mkdir()
    if bankutil.COMMAND_AUDIT is not None:
        bankutil.COMMAND_AUDIT.event(kind='pregenerate', task='orc-bloom-filter', evidence_run=run_id)
    manifest = new_manifest(run_id, 'prepare', mode='pregenerate', task='orc-bloom-filter')
    write_manifest(out, manifest)
    spec = {'environment': ENVIRONMENT,
            'commands': [['cmake', '-S', '/input', '-B', '/work/build', '-G', 'Ninja']],
            'tools': [['cmake', '--version'], ['g++-14', '--version']],
            'outputs': {'build/Adaptor.hh': 'c++/src/Adaptor.hh', 'build/orc-config.hh': 'c++/include/orc/orc-config.hh'}}
    try:
        generate(inputs, directory / 'source', spec, out)
        finish_run(out, manifest, 'completed', passed=True)
    except BaseException as error:
        finish_run(out, manifest, 'failed', error=str(error))
        raise
    names = ['c++/src/BloomFilter.cc', 'c++/src/BloomFilter.hh', 'c++/src/Murmur3.cc', 'c++/src/Murmur3.hh',
             'c++/src/wrap/orc-proto-wrapper.hh', 'c++/include/orc/BloomFilter.hh', 'proto/orc_proto.proto', 'LICENSE', 'NOTICE']
    source_files(directory, repo, names)
    text = (repo / 'c++/test/TestBloomFilter.cc').read_text()
    text = text.replace('#include "orc/OrcFile.hh"', '').replace('#include "wrap/gtest-wrapper.h"', '#include <gtest/gtest.h>')
    # The upstream friend test is the supported access point for private hash
    # arithmetic. Add a small, fully defined counterexample without changing
    # the business class or using a private/public macro.
    marker = 'TEST(TestBloomFilter, testBloomFilterBasicOperations) {'
    assert text.count(marker) == 1
    text = text.replace(marker, marker + '''
    {
      proto::BloomFilter encoded;
      encoded.set_numhashfunctions(2);
      encoded.set_utf8bitset(std::string(8, '\\0'));
      (*encoded.mutable_utf8bitset())[0] = 4; // Only the first hash bit (2).
      BloomFilterImpl defined(encoded);
      const int64_t hash = (int64_t(1) << 32) | 1; // combinedHash = 2, 3.
      EXPECT_FALSE(defined.testHash(hash));
      defined.addHash(hash);
      EXPECT_TRUE(defined.testHash(hash));
      EXPECT_TRUE(defined.mBitSet->get(2));
      EXPECT_TRUE(defined.mBitSet->get(3));
      EXPECT_FALSE(defined.mBitSet->get(4));
      // Both halves remain small: multiplication/addition and negation are
      // defined throughout. Check all output bits independently of testHash.
      for (int32_t high = -3; high <= 3; ++high) {
        for (int32_t low = -3; low <= 3; ++low) {
          const uint64_t bits = (uint64_t(static_cast<uint32_t>(high)) << 32)
                              | static_cast<uint32_t>(low);
          defined.reset();
          defined.addHash(static_cast<int64_t>(bits));
          int32_t first = low + high, second = low + 2 * high;
          if (first < 0) first = ~first;
          if (second < 0) second = ~second;
          for (unsigned pos = 0; pos < 64; ++pos)
            EXPECT_EQ(pos == static_cast<unsigned>(first) % 64
                      || pos == static_cast<unsigned>(second) % 64, defined.mBitSet->get(pos));
          EXPECT_TRUE(defined.testHash(static_cast<int64_t>(bits)));
        }
      }
    }
''')
    write_text(directory / 'hidden/reference_tests/upstream_tests.cc', text)
    write_text(directory / 'hidden/README.md', '''# ORC BloomFilter

源码与 .proto 原样入库；Adaptor.hh 和 orc-config.hh 由上游特性检测片段在锁定 GCC 环境中生成，
两轮字节一致；完整命令、工具版本及输入/输出哈希见 source/SOURCE.json.generated。
参考测试来自 TestBloomFilter.cc；将 GoogleTest 包装头替换为标准头并移除未使用的 OrcFile.hh，
在上游已声明的 friend 测试中补充小整数哈希反例，避免依靠 signed hash 溢出区分变异。
Murmur3.cc 仅作依赖单元；生成的 orc_proto.pb.cc 不参与覆盖率和变异。原代码的 signed hash 运算
及大端不可达分支须按 D015 逐项复核，不能仅凭参考测试未检出认定等价。
''')
    finish(directory, args.upstream, 'orc', ['c++/src/BloomFilter.cc'], ['c++/src/Murmur3.cc'],
           ['c++/src', 'c++/include'], 'medium', ['protobuf::libprotobuf'],
           [{'tool': 'protoc', 'inputs': ['proto/orc_proto.proto'], 'import_dirs': ['proto']}],
           origins=['c++/test/TestBloomFilter.cc'])


def phone(args):
    repo = args.upstream / 'libphonenumber'
    directory = reset_task_dir('libphonenumber-lite', args.force)
    source_files(directory, repo, ['cpp/src/phonenumbers/phonenumber.cc', 'cpp/src/phonenumbers/phonenumber.h', 'LICENSE'])
    for name in ['phonenumber', 'phonemetadata']:
        copy_file(repo / f'resources/{name}.proto', directory / f'source/proto/phonenumbers/{name}.proto')
    copy_file(TOOLS / 'step_c/libphonenumber-lite/reference_tests/comparison.cc', directory / 'hidden/reference_tests/comparison.cc')
    write_text(directory / 'hidden/README.md', '''# libphonenumber lite 比较

被测 phonenumber.cc 与头文件保持上游字节；两个 resources/*.proto 按 phonenumbers/ 路径放置以保持
原始源码的生成头 include。它们原有 LITE_RUNTIME 选项保持。隐藏测试逐字段核对 presence、value、
重复字段的顺序与数量；只链接 protobuf lite，不需要 ICU 或 RE2。
''')
    finish(directory, args.upstream, 'libphonenumber', ['cpp/src/phonenumbers/phonenumber.cc'], [], ['cpp/src'],
           'easy', ['protobuf::libprotobuf-lite'], [{'tool': 'protoc',
               'inputs': ['proto/phonenumbers/phonenumber.proto', 'proto/phonenumbers/phonemetadata.proto'], 'import_dirs': ['proto']}],
           origins=['Qualtor field-by-field comparisons'])


def prometheus(args):
    repo = args.upstream / 'prometheus-cpp'
    directory = reset_task_dir('prometheus-cpp-text', args.force)
    targets = ['lib/text_serializer.cc', 'lib/counter.cc', 'lib/gauge.cc', 'lib/histogram.cc']
    names = targets + ['LICENSE'] + [str(p.relative_to(repo)) for p in (repo / 'include/prometheus').glob('*.h')]
    source_files(directory, repo, names)
    model = args.extra_upstream / 'prometheus-client-model'
    copy_file(model / 'metrics.proto', directory / 'source/proto/metrics.proto')
    copy_file(model / 'LICENSE', directory / 'source/proto/LICENSE')
    for name in ['counter', 'gauge', 'histogram']:
        copy_file(repo / f'tests/{name}_test.cc', directory / f'hidden/reference_tests/{name}_test.cc')
    copy_file(TOOLS / 'step_c/prometheus-cpp-text/reference_tests/serialization.cc', directory / 'hidden/reference_tests/serialization.cc')
    write_text(directory / 'hidden/README.md', '''# prometheus-cpp 文本与指标

业务源码原样入库。metrics.proto 来自本提交固定的 prometheus/client_model 子模块
fa8ad6fec33561be4280a8f0514318c79d7f6cb6，保留该子模块许可证。
counter、gauge、histogram 使用原 GoogleTest；文本序列化的隐藏边界测试覆盖所有指标类型及标签转义。
不导入网络 exposer 或 civetweb；不需要额外网络或库。
''')
    finish(directory, args.upstream, 'prometheus-cpp', targets, [], ['include'], 'medium', ['protobuf::libprotobuf'],
           [{'tool': 'protoc', 'inputs': ['proto/metrics.proto'], 'import_dirs': ['proto']}],
           origins=['tests/counter_test.cc', 'tests/gauge_test.cc', 'tests/histogram_test.cc', 'Qualtor serialization boundaries'],
           provenance_extra={'additional_sources': [{
               'repository': metadata(args.extra_upstream, 'prometheus-client-model')['repository'],
               'commit': metadata(args.extra_upstream, 'prometheus-client-model')['commit'],
               'files': {'proto/metrics.proto': 'metrics.proto', 'proto/LICENSE': 'LICENSE'},
               'note': '主提交固定的 prometheus/client_model gitlink；原文件字节不改写。'}]})


def mustache(args):
    repo = args.upstream / 'qt-mustache'
    directory = reset_task_dir('qt-mustache', args.force)
    source_files(directory, repo, ['src/mustache.cpp', 'src/mustache.h', 'LICENSE'])
    text = (repo / 'tests/test_mustache.cpp').read_text()
    # data-driven QtTest is translated to one GTest per JSON entry below.
    for name in ('testConformance_data', 'testConformance', 'testPartialFile'):
        text = remove_function(text, 'void TestMustache::' + name + '()')
    text = text[:text.index('// Create a QCoreApplication')]
    text = text.replace('#include "test_mustache.h"', QT_MACROS + '#include "mustache.h"')
    text = re.sub(r'void TestMustache::(\w+)\(\)', r'TEST(Mustache, \1)', text)
    write_text(directory / 'hidden/reference_tests/upstream_tests.cc', text)
    cases = '#include <gtest/gtest.h>\n#include "mustache.h"\n#include <QJsonDocument>\n#include <QJsonObject>\n'
    for filename in sorted((repo / 'tests/specs').glob('*.json')):
        for index, case in enumerate(json.loads(filename.read_text())['tests'], 1):
            data = json.dumps(case, ensure_ascii=True, separators=(',', ':'))
            literal = json.dumps(data, ensure_ascii=True)
            cases += f'''TEST(MustacheSpec_{filename.stem}, Case{index}) {{
  const QJsonObject input = QJsonDocument::fromJson({literal}).object();
  QHash<QString, QString> partials;
  QJsonObject values = input["partials"].toObject();
  for (auto it = values.begin(); it != values.end(); ++it) partials[it.key()] = it.value().toString();
  Mustache::Renderer renderer;
  Mustache::PartialMap partialMap(partials);
  Mustache::QtVariantContext context(input["data"].toObject().toVariantMap(), &partialMap);
  EXPECT_EQ(input["expected"].toString(), renderer.render(input["template"].toString(), &context));
}}
'''
    write_text(directory / 'hidden/reference_tests/spec_tests.cc', cases)
    write_text(directory / 'hidden/README.md', '''# Qt Mustache

上游 QtTest 机械转换为 GoogleTest；全部内嵌 JSON 规格转换为独立用例；源码不改写。
testPartialFile 使用外部可写文件路径，独立改写为 QTemporaryDir 文件用例（补充文件见参考测试）。
本题不含 Q_OBJECT；仅链接 QtCore，与 moc 题作对照。
''')
    for path in (TOOLS / 'step_c/qt-mustache/reference_tests').glob('*'):
        copy_file(path, directory / 'hidden/reference_tests' / path.name)
    finish(directory, args.upstream, 'qt-mustache', ['src/mustache.cpp'], [], ['src'], 'medium', ['Qt5::Core'],
           origins=['tests/test_mustache.cpp', 'tests/specs/*.json'])


def gzip_task(args):
    repo = args.upstream / 'gzip-hpp'
    directory = reset_task_dir('gzip-hpp', args.force)
    names = [str(p.relative_to(repo)) for p in (repo / 'include/gzip').glob('*.hpp')] + ['LICENSE.md']
    source_files(directory, repo, names)
    copy_file(TOOLS / 'step_c/gzip-hpp/reference_tests/compression.cc', directory / 'hidden/reference_tests/compression.cc')
    write_text(directory / 'hidden/README.md', '''# gzip-hpp

所有 include/gzip/*.hpp 原样入库；参考测试覆盖上游往返、错误参数和大小限制场景，补充 gzip/zlib
文件头与边界。大文件限制用较小的显式上限验证同一路径，不分配上游约 500 MB 的解压输入。
5 个手写变异只改变输出格式、边界或结果长度，不以越界和崩溃检出；补丁来自工具目录。
''')
    finish(directory, args.upstream, 'gzip-hpp', [], [], ['include'], 'easy', ['ZLIB::ZLIB'],
           origins=['test/test_io.cpp', 'Qualtor bounded compression cases'],
           headers=['include/gzip/compress.hpp', 'include/gzip/decompress.hpp', 'include/gzip/utils.hpp'],
           build={'defines': ['DEBUG']})


def configured_source(args, directory, repo, outputs, options, clone=False):
    from pregenerate import generate
    from runs import new_manifest, write_manifest, finish as finish_run
    out = RUNS / (args.run_dir.name + '-' + directory.name + '-config')
    out.mkdir()
    if bankutil.COMMAND_AUDIT is not None:
        bankutil.COMMAND_AUDIT.event(kind='pregenerate', task=directory.name, evidence_run=out.name)
    manifest = new_manifest(out.name, 'prepare', mode='pregenerate', task=directory.name)
    write_manifest(out, manifest)
    commands = ([['python3', '-c', 'import shutil; shutil.copytree("/input", "/work/source")']]
                if clone else [])
    commands.append(['cmake', '-S', '/work/source' if clone else '/input', '-B', '/work/build', '-G', 'Ninja', *options])
    spec = {'environment': ENVIRONMENT, 'commands': commands,
            'tools': [['cmake', '--version'], ['gcc-14', '--version'], ['g++-14', '--version']], 'outputs': outputs}
    try:
        generate(repo, directory / 'source', spec, out)
        finish_run(out, manifest, 'completed', passed=True)
    except BaseException as error:
        finish_run(out, manifest, 'failed', error=str(error))
        raise
    return out


# BugsC++ meta.json 中各缺陷的上游修复提交（runs/step-a-20261028-01/upstream/bugscpp 固定提交）。
BUGSCPP_FIX = {('exiv2', 12): 'b35c43e7c2409978a0c45f35c2ec8c7f625469df',
               ('libtiff', 5): 'd651abc097d91fac57f33b5f9447d0a9183f58e7'}


def bug_variant(directory, project, index, args):
    patch = args.bugscpp / 'bugscpp/taxonomy' / project / 'patch' / (f'{index:04d}-buggy.patch')
    copy_file(patch, directory / 'hidden/buggy.patch')
    source = {'repository': 'https://github.com/Suresoft-GLaDOS/bugscpp', 'project': project,
              'commit': 'be5cc489cb2b3127ec3b73cb4adfdd290807f55b',
              'bug': index, 'patch_sha256': sha256_file(patch)}
    return apply_patch_variant(directory, patch, f'bugscpp-{index}', 'real_bug',
                               'BugsC++ 固定 buggy.patch 作用于修复提交；参考测试验证修复后的行为。', source)


def libtiff(args):
    upstream = args.extra_upstream
    repo = upstream / 'libtiff'
    directory = reset_task_dir('libtiff-strip', args.force)
    config = configured_source(args, directory, repo,
        {'build/libtiff/tif_config.h': 'libtiff/tif_config.h', 'build/libtiff/tiffconf.h': 'libtiff/tiffconf.h'},
        ['-Djpeg=OFF', '-Dold-jpeg=OFF', '-Djpeg12=OFF', '-Djbig=OFF', '-Dlzma=OFF', '-Dzlib=ON',
         '-Dcxx=OFF', '-DCMAKE_C_STANDARD=99', '-DCMAKE_C_STANDARD_REQUIRED=ON', '-DCMAKE_C_EXTENSIONS=OFF'])
    ninja = (config / 'round-1/build/build.ninja').read_text()
    sources = sorted(set(re.findall(r'^build libtiff/CMakeFiles/tiff.dir/.*? /input/(\S+\.c) ', ninja, re.M)))
    if 'libtiff/tif_strip.c' not in sources:
        raise ValueError('libtiff 上游配置没有预期的被测源文件')
    names = sources + ['COPYRIGHT'] + [str(p.relative_to(repo)) for p in (repo / 'libtiff').glob('*.h')]
    source_files(directory, repo, names)
    for path in (TOOLS / 'step_c/libtiff-strip/reference_tests').glob('*'):
        copy_file(path, directory / 'hidden/reference_tests' / path.name)
    variant = bug_variant(directory, 'libtiff', 5, args)
    write_text(directory / 'hidden/README.md', f'''# libtiff strip

被测 tif_strip.c 与依赖 C 单元保留固定上游字节，依赖列表取自上游 CMake 的 tiff 目标。
配置头由锁定 GCC 环境重复生成，关闭 jpeg/jbig/lzma，仅启用 zlib 等上游内置能力。
参考测试直接覆盖条带与扫描行计算；BugsC++ libtiff/5 的补丁去掉 td_nstrips 缓存分支，
以已缓存条带数与重新计算值不同的有定义结构状态复现。补丁原样保存为 buggy.patch。

真实缺陷版本 {variant['id']}：
- BugsC++ 仓库 {variant['source']['repository']} 的固定提交 {variant['source']['commit']}，缺陷 libtiff/5；
  BugsC++ 标注为 CVE-2016-9273（Heap-buffer-overflow in cpStrips），上游修复提交 {BUGSCPP_FIX['libtiff', 5]}。
- buggy.patch 的 sha256：{variant['patch_sha256']}。
- 回归用例：Strips.ComputeAndCount。
''')
    finish(directory, upstream, 'libtiff', ['libtiff/tif_strip.c'],
           [s for s in sources if s != 'libtiff/tif_strip.c'], ['libtiff'], 'hard', ['ZLIB::ZLIB'],
           origins=['Qualtor strip arithmetic and cached strip regression'], build={'c_standard': 'c99'}, variants=[variant])


def exiv2(args):
    repo = args.upstream / 'exiv2'
    directory = reset_task_dir('exiv2-pngchunk', args.force)
    config = configured_source(args, directory, repo,
        {'build/exv_conf.h': 'config/exv_conf.h', 'build/exiv2lib_export.h': 'config/exiv2lib_export.h'},
        ['-DEXIV2_ENABLE_XMP=OFF', '-DEXIV2_ENABLE_NLS=OFF', '-DEXIV2_BUILD_SAMPLES=OFF', '-DEXIV2_BUILD_EXIV2_COMMAND=OFF',
         '-DEXIV2_BUILD_UNIT_TESTS=OFF', '-DEXIV2_BUILD_PO=OFF', '-DEXIV2_BUILD_DOC=OFF',
         '-DCMAKE_CXX_STANDARD=11', '-DCMAKE_CXX_STANDARD_REQUIRED=ON', '-DCMAKE_CXX_EXTENSIONS=OFF'], clone=True)
    ninja = (config / 'round-1/build/build.ninja').read_text()
    sources = sorted(set(re.findall(r'^build src/CMakeFiles/exiv2lib(?:_int)?.dir/.*? /work/source/(\S+\.cpp) ', ninja, re.M)))
    if 'src/pngchunk_int.cpp' not in sources:
        raise ValueError('exiv2 上游配置没有预期的被测源文件')
    names = sources + ['COPYING']
    for folder in ('src', 'include/exiv2'):
        names += [str(p.relative_to(repo)) for p in (repo / folder).glob('*') if p.suffix in ('.h', '.hpp')]
    source_files(directory, repo, names)
    for path in (TOOLS / 'step_c/exiv2-pngchunk/reference_tests').glob('*'):
        copy_file(path, directory / 'hidden/reference_tests' / path.name)
    poc = repo / 'test/data/issue_845_poc.png'
    raw = poc.read_bytes()
    write_text(directory / 'hidden/reference_tests/poc.h', '#pragma once\nstatic const unsigned char issue845[] = {'
               + ','.join(str(b) for b in raw) + '};\n')
    variant = bug_variant(directory, 'exiv2', 12, args)
    write_text(directory / 'hidden/README.md', f'''# Exiv2 PNG chunk

源码及 GPL COPYING 原样入库；依赖源文件取自上游 exiv2lib/exiv2lib_int 目标，XMP 与 NLS 功能关闭。
配置头在锁定 GCC 环境重复生成，SOURCE.json 保存全部输入、命令、版本和输出哈希。
参考测试覆盖公开 PngChunk 操作与错误输入；上游 test/data/issue_845_poc.png 原字节内嵌隐藏 poc.h，
通过 ImageFactory 内存入口回放。BugsC++ exiv2/12 的固定补丁原样保存为 buggy.patch。

真实缺陷版本 {variant['id']}：
- BugsC++ 仓库 {variant['source']['repository']} 的固定提交 {variant['source']['commit']}，缺陷 exiv2/12
  （Out-of-bounds Read），上游修复提交 {BUGSCPP_FIX['exiv2', 12]}。
- buggy.patch 的 sha256：{variant['patch_sha256']}。补丁删去 readRawProfile 逐位解析长度及溢出检查，
  改为 atol(startOfLength)，并要求 0 <= length。
- 回归用例：只有 PngChunk.ImageContentAndMalformedRawProfiles。长度字段为 "-1" 时，修复版本不解析负号、
  得到长度 0 并返回空结果；缺陷版本 atol 得到 -1，enforce 抛出 Exiv2::Error，EXPECT_NO_THROW 失败。
  该输入在两个版本上都是有定义行为。长度 9223372036854775808 只用于覆盖修复版本的溢出检查；它在缺陷版本上
  依赖 atol 溢出（ISO C 未定义行为，glibc 返回 LONG_MAX），检出不依赖这一输入。
- PngChunk.UpstreamIssue845 在缺陷版本上同样通过，不能检出该缺陷（0.5.0 标定
  step-c-seed-20261029-13-exiv2-pngchunk 中，缺陷版本只有上一个用例失败）。
''')
    finish(directory, args.upstream, 'exiv2', ['src/pngchunk_int.cpp'],
           [s for s in sources if s != 'src/pngchunk_int.cpp'], ['src', 'include/exiv2', 'config'], 'hard', ['ZLIB::ZLIB'],
           origins=['tests/bugfixes/github/test_issue_845.py', 'test/data/issue_845_poc.png', 'Qualtor PNG chunk boundaries'],
           variants=[variant], build={'defines': ['exiv2lib_STATIC']})


def normalized_source_json(path):
    """SOURCE.json 中每次预生成都会变化的字段：证据 run-id 与派生镜像 ID（D021-1 不比较镜像 ID）。"""
    data = json.loads(Path(path).read_text())
    for record in data.get('generated', []):
        record.pop('evidence_run', None)
        environment = record.get('environment')
        if isinstance(environment, dict):
            record['environment'] = {'name': environment.get('name'), 'recipe_sha256': environment.get('recipe_sha256')}
    return data


def compare_task(expected, actual):
    """逐字节比较重建结果与题库；返回差异清单。冻结分母由 Docker 标定产生，不属于建题输出。"""
    def listing(root):
        return {str(p.relative_to(root)) for p in Path(root).rglob('*')
                if p.is_file() and not (p.parent.name == 'hidden' and p.name in BASELINES)}
    have, built = listing(expected), listing(actual)
    problems = [f'重建缺少：{rel}' for rel in sorted(have - built)]
    problems += [f'重建多出：{rel}' for rel in sorted(built - have)]
    for rel in sorted(have & built):
        if rel == 'source/SOURCE.json':
            if normalized_source_json(Path(expected) / rel) != normalized_source_json(Path(actual) / rel):
                problems.append(f'内容不同：{rel}（已忽略 generated 的 evidence_run 与镜像 ID）')
        elif (Path(expected) / rel).read_bytes() != (Path(actual) / rel).read_bytes():
            problems.append(f'内容不同：{rel}')
    return problems


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--upstream', type=Path, required=True)
    parser.add_argument('--extra-upstream', type=Path)
    parser.add_argument('--bugscpp', type=Path, default=REPO / 'runs/step-a-20261028-01/upstream/bugscpp')
    parser.add_argument('--tasks', nargs='+', choices=TASKS, required=True)
    parser.add_argument('--run-id', required=True)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--force', action='store_true')
    mode.add_argument('--verify', action='store_true', help='重建到临时目录并与 benchmark/<题目> 逐字节比较，不写入题库')
    args = parser.parse_args(argv)
    sys.path.insert(0, str(REPO / 'evaluator/common'))
    from audit import Audit
    from runs import new_manifest, write_manifest, finish as finish_run
    if not re.fullmatch(r'[a-zA-Z0-9][a-zA-Z0-9_-]{0,79}', args.run_id):
        parser.error('run-id 只能包含字母、数字、-、_')
    args.run_dir = RUNS / args.run_id
    args.run_dir.mkdir(parents=True, exist_ok=False)
    manifest = new_manifest(args.run_id, 'prepare', mode='step_c_import_verify' if args.verify else 'step_c_import',
                            tasks=args.tasks, argv=sys.argv if argv is None else ['import_step_c.py', *argv])
    write_manifest(args.run_dir, manifest)
    functions = {'qt-aes': qt_aes, 'orc-bloom-filter': orc, 'libphonenumber-lite': phone,
                 'prometheus-cpp-text': prometheus, 'qt-mustache': mustache, 'gzip-hpp': gzip_task,
                 'libtiff-strip': libtiff, 'exiv2-pngchunk': exiv2}
    audit = Audit(args.run_dir / 'evidence/host')
    previous = bankutil.COMMAND_AUDIT, bankutil.BENCHMARK
    scratch = None
    try:
        bankutil.COMMAND_AUDIT = audit
        if args.verify:
            # 只在临时题库中重建；reset_task_dir 与 write_task 都写到 bankutil.BENCHMARK 之下。
            scratch = Path(tempfile.mkdtemp(prefix='qualtor-verify-'))
            bankutil.BENCHMARK = scratch / 'benchmark'
            bankutil.BENCHMARK.mkdir()
        for task in args.tasks:
            audit.event(kind='import_task', task=task, verify=args.verify)
            functions[task](args)
            print(('重建 ' if args.verify else '生成 ') + task, flush=True)
        if args.verify:
            report = {task: compare_task(previous[1] / task, bankutil.BENCHMARK / task) for task in args.tasks}
            write_json(args.run_dir / 'verify.json', {'identical': not any(report.values()), 'tasks': report})
            for task, problems in report.items():
                print(f"{task}：{'逐字节一致' if not problems else '不一致'}", flush=True)
                for problem in problems:
                    print('  - ' + problem, flush=True)
            finish_run(args.run_dir, manifest, 'completed', passed=not any(report.values()))
            return 0 if not any(report.values()) else 1
        finish_run(args.run_dir, manifest, 'completed', passed=True)
        return 0
    except BaseException as error:
        audit.event(kind='run_error', error=str(error))
        finish_run(args.run_dir, manifest, 'failed', error=str(error))
        raise
    finally:
        bankutil.COMMAND_AUDIT, bankutil.BENCHMARK = previous
        if scratch is not None:
            shutil.rmtree(scratch, ignore_errors=True)


if __name__ == '__main__':
    raise SystemExit(main())
