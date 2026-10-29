#!/usr/bin/env python3
"""从固定上游提交导入步骤 B 的模板库与头文件缺陷题；业务文件原样保存。"""
import argparse
from pathlib import Path
import re

import bankutil as b
from import_exercism import convert_test
from import_step_a import git, finish_task, yaml_test_text, YAML_OPTIONS

TOOLS=Path(__file__).resolve().parent
COMMITS={'utfcpp':'b26a5f718f4f370af1852a0d5c6ae8fa031ba7d0',
         'json':'9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03',
         'cpp-peglib':'2d276c8cd9a64800587172b40b8cb74e273a4f88'}
YAML={'yaml-cpp-node-impl':('33315286abb27c04a5fc5322b828153f6aaf70eb',4,'include/yaml-cpp/node/impl.h','null-string'),
      'yaml-cpp-emitter-utils':('a6db7e32ac506d536596d31bdb2b365de1cf35a2',9,'src/emitterutils.cpp','carriage-return')}


def create(task_id,force):
    directory=b.reset_task_dir(task_id,force)
    (directory/'hidden/reference_tests').mkdir(parents=True)
    return directory


def snapshot(directory,repo,commit,choose):
    names=git(repo,'ls-tree','-r','--name-only',commit).decode().splitlines()
    for rel in names:
        if choose(rel):
            path=directory/'source'/rel
            path.parent.mkdir(parents=True,exist_ok=True)
            path.write_bytes(git(repo,'show',f'{commit}:{rel}'))
    return names


def extra_material(directory):
    folder=TOOLS/'step_b'/directory.name
    if folder.is_dir():
        for path in sorted(folder.rglob('*')):
            if path.is_file():b.copy_file(path,directory/'hidden'/path.relative_to(folder))


def bug_variant(directory,repo,bugscpp,project,number,commit,variant_id,regression):
    patch=bugscpp/f'bugscpp/taxonomy/{project}/patch/{number:04d}-buggy.patch'
    b.copy_file(patch,directory/'hidden/buggy.patch')
    source={'dataset':f'BugsC++ {project}/{number}',
            'dataset_commit':git(bugscpp,'rev-parse','HEAD').decode().strip(),
            'fix_commit':commit,'patch_sha256':b.sha256_file(patch),'regression_tests':regression}
    variant=b.apply_patch_variant(directory,patch,variant_id,'real_bug','上游缺陷修复的反向补丁',source)
    # 修复方向的 diff 仅用于阅读；被替换业务文件来自上游数据集 buggy.patch。
    import difflib
    fix=''
    for rel in variant['files']:
        buggy=(directory/'hidden/variants'/variant_id/rel).read_text().splitlines(True)
        fixed=(directory/'source'/rel).read_text().splitlines(True)
        fix+=''.join(difflib.unified_diff(buggy,fixed,fromfile='a/'+rel,tofile='b/'+rel))
    b.write_text(directory/'hidden/fix.patch',fix)
    b.write_json(directory/'hidden/upstream_evidence.json',source)
    return variant


def yaml_task(task_id,args):
    commit,number,target,vid=YAML[task_id]
    repo=args.yaml_source
    directory=create(task_id,args.force)
    names=snapshot(directory,repo,commit,lambda p:p.startswith(('src/','include/')) or p in ('LICENSE','CMakeLists.txt','README.md'))
    tests=([p for p in names if p.startswith('test/') and '/gtest-' not in p and p.endswith('.cpp') and p!='test/main.cpp']
           if number==4 else ['test/integration/emitter_test.cpp','test/integration/gen_emitter_test.cpp',
                             'test/integration/encoding_test.cpp','test/ostream_wrapper_test.cpp','test/regex_test.cpp'])
    headers=[p for p in names if p.startswith('test/') and '/gtest-' not in p and p.endswith('.h')]
    for rel in tests+headers:
        b.write_text(directory/'hidden/reference_tests'/Path(rel).name.replace('.cpp','.cc'),
                     yaml_test_text(git(repo,'show',f'{commit}:{rel}').decode()))
    b.write_text(directory/'hidden/reference_tests/reference_options.cc',YAML_OPTIONS)
    regression=['NodeTest.LoadTildeAsNull'] if number==4 else ['EmitterTest.UserType2']
    variant=bug_variant(directory,repo,args.bugscpp,'yaml_cpp',number,commit,vid,regression)
    extra_material(directory)
    variants=[variant]+b.handwritten_variants(directory)
    b.write_text(directory/'hidden/README.md',f'''# {task_id} 隐藏材料

业务源码逐字节取自 yaml-cpp `{commit}`；独立快照，保留原始许可证与构建配置。
被测文件 `{target}`，其余 src/*.cpp 作依赖；头文件题的覆盖率构建给全部单元插桩，统计只限被测头文件。
参考测试为上游 GoogleTest；扩展名改为 .cc，去除上游已禁用的测试，沿用步骤 A 的 throw_on_failure 设置。
真实缺陷来自 BugsC++ yaml_cpp/{number} 的 buggy.patch；提交、patch 哈希和回归用例记录在 upstream_evidence.json。
预期回归用例：{', '.join(regression)}。实际检出名单以 Docker 标定为准。
手写变异来自 benchmark/tools/handwritten_variants/{task_id}/；均需编译成功并由断言失败检出。
参考测试未经过人工审阅。准备阶段冻结 coverage_baseline.json；未进入分母的 API 说明见 coverage_notes.md（若有）。
''')
    support=sorted(p for p in names if p.startswith('src/') and p.endswith('.cpp') and p!=target)
    finish_task(directory,'https://github.com/jbeder/yaml-cpp',commit,[] if number==4 else [target],support,
                ['include','src'],'hard',['real-bug','header-variant','support-sources'],
                'YAML 节点访问' if number==4 else 'YAML 输出格式处理','公开 YAML 库的模块单元测试。',tests+headers,
                variants=variants,build={'compile_options':['-fno-strict-aliasing']},
                target_headers=[target] if number==4 else None,generated_by='benchmark/tools/import_step_b.py')
    return directory


def library_task(task_id,args):
    name={'utfcpp-checked':'utfcpp','nlohmann-json-to-chars':'json','cpp-peglib-parser':'cpp-peglib'}[task_id]
    repo=args.upstream/name
    commit=COMMITS[name]
    directory=create(task_id,args.force)
    variants=[]
    if name=='utfcpp':
        snapshot(directory,repo,commit,lambda p:p.startswith('source/') or p in ('LICENSE','CMakeLists.txt'))
        targets=['source/utf8/'+p for p in ('core.h','checked.h','unchecked.h')]
        tests=['tests/apitests.cpp','tests/test_cpp11.cpp']
        for rel in tests:
            text=git(repo,'show',f'{commit}:{rel}').decode().replace('#include "../extern/ftest/ftest.h"','#include <gtest/gtest.h>')
            b.write_text(directory/'hidden/reference_tests'/Path(rel).name.replace('.cpp','.cc'),text)
        for rel in ['tests/test_checked_api.h','tests/test_checked_iterator.h','tests/test_unchecked_api.h','tests/test_unchecked_iterator.h']:
            b.write_text(directory/'hidden/reference_tests'/Path(rel).name,git(repo,'show',f'{commit}:{rel}').decode())
        repository='https://github.com/nemtrif/utfcpp';includes=['source'];tier='medium'
    elif name=='json':
        snapshot(directory,repo,commit,lambda p:p.startswith('include/') or p in ('LICENSE.MIT','CMakeLists.txt'))
        targets=['include/nlohmann/detail/conversions/to_chars.hpp']
        tests=['tests/src/unit-to_chars.cpp']
        raw=git(repo,'show',f'{commit}:{tests[0]}').decode().replace('#include "doctest_compatibility.h"','#include "catch2/catch.hpp"')
        text,_=convert_test(raw,'ToChars')
        b.write_text(directory/'hidden/reference_tests/to_chars.cc','#define CAPTURE(...) ((void)0);\n'+text)
        b.copy_file(TOOLS/'catch_compat.h',directory/'hidden/reference_tests/catch_compat.h')
        repository='https://github.com/nlohmann/json';includes=['include'];tier='hard'
    else:
        snapshot(directory,repo,commit,lambda p:p in ('peglib.h','LICENSE','CMakeLists.txt'))
        targets=['peglib.h'];tests=['test/test.cc']
        raw=git(repo,'show',f'{commit}:test/test.cc').decode('utf-8-sig').replace('#define CATCH_CONFIG_MAIN','').replace('#include "catch.hh"','#include "catch2/catch.hpp"')
        text,_=convert_test(raw,'PegParser')
        # 上游语法调试测试复制全局 Grammar，Definition 的复制构造会改写共享
        # Holder::outer_。保留测试内容，并在副本析构后恢复指针，支持乱序运行。
        text=text.replace('#include <peglib.h>', '#include <peglib.h>\n#include "grammar_scope.h"')
        text=text.replace('    auto g = ParserGenerator::grammar();',
                          '    GlobalGrammarScope restore;\n    auto g = ParserGenerator::grammar();')
        text=text.replace('    Grammar g = make_peg_grammar();',
                          '    GlobalGrammarScope restore;\n    Grammar g = make_peg_grammar();')
        b.write_text(directory/'hidden/reference_tests/parser.cc',text)
        b.copy_file(TOOLS/'catch_compat.h',directory/'hidden/reference_tests/catch_compat.h')
        variants=[bug_variant(directory,repo,args.bugscpp,'cpp_peglib',5,commit,'left-recursion',
                              ['PegParser.T051_Left_recursive_with_a_ZOM_content_rule'])]
        repository='https://github.com/yhirose/cpp-peglib';includes=['.'];tier='hard'
    extra_material(directory)
    variants+=b.handwritten_variants(directory)
    b.write_text(directory/'hidden/README.md',f'''# {task_id} 隐藏材料

来源：{repository}，提交 `{commit}`。source/ 中业务文件未改动，保留许可证。
被测头文件：{', '.join(targets)}。其余头文件只作可见依赖，不进入覆盖率分母。
参考测试从 {', '.join(tests)} 机械转换：utfcpp 只替换 ftest include；其他库沿用 Catch 断言兼容层，TEST_CASE 改为 GoogleTest，SECTION 独立作用域按顺序执行，CAPTURE 仅去除诊断输出。
手写变异源文件与说明：benchmark/tools/handwritten_variants/{task_id}/；参考测试尚未人工审阅。
冻结范围及未实例化成员见 coverage_notes.md（若有）；缺陷、覆盖率和变异检出结论以 Docker 标定为准。
''')
    finish_task(directory,repository,commit,[],[],includes,tier,['templates','header-only'],
                {'utfcpp':'UTF 编码转换','json':'浮点数文本转换','cpp-peglib':'PEG 语法解析'}[name],
                '公开 C++11 库的模板与内联模块。',tests,variants=variants,target_headers=targets,
                generated_by='benchmark/tools/import_step_b.py')
    return directory


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--upstream',type=Path,required=True)
    parser.add_argument('--yaml-source',type=Path,required=True)
    parser.add_argument('--bugscpp',type=Path,required=True)
    parser.add_argument('--tasks',nargs='+',default=list(YAML)+['utfcpp-checked','nlohmann-json-to-chars','cpp-peglib-parser'])
    parser.add_argument('--force',action='store_true')
    args=parser.parse_args()
    for task_id in args.tasks:
        directory=yaml_task(task_id,args) if task_id in YAML else library_task(task_id,args)
        print('已导入',directory)

if __name__=='__main__':main()
