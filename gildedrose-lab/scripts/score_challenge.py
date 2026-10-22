"""核验事前冻结的模型答案，C++ 实际输出作为标准答案。"""
import collections
import hashlib
import json
from pathlib import Path
import shutil
from audit import now
from coverage import collect
from verify import evaluate


def score_challenge(challenge, output, rose_binary, audit):
    output.mkdir(parents=True, exist_ok=False)
    freeze = json.loads((challenge / 'freeze.json').read_text())
    for name, digest in freeze['files'].items():
        if hashlib.sha256((challenge / name).read_bytes()).hexdigest() != digest:
            raise AssertionError(f'frozen challenge changed: {name}')
    audit.event(kind='llm_oracle_started', frozen_at=freeze['frozen_at'], frozen_hashes=freeze['files'])
    predictions = json.loads((challenge / 'predictions.json').read_text())
    rose_questions = json.loads((challenge / 'rose_questions.json').read_text())
    stress_questions = json.loads((challenge / 'questions.json').read_text())
    def valid_ids(questions, answers):
        ids = [r['id'] for r in answers]
        return len(ids) == len(set(ids)) and set(ids) == {q['id'] for q in questions}
    protocol_valid = valid_ids(rose_questions, predictions['rose']) and valid_ids(stress_questions, predictions['stress'])
    if not protocol_valid:
        raise ValueError('model answer IDs do not match questions exactly')
    rose_map = {r['id']:r for r in predictions['rose']}
    cases = [{**q, 'suite':'model_rose', 'expected':{'name':q['name'], 'sell_in':rose_map[q['id']]['sell_in'],
                                                 'quality':rose_map[q['id']]['quality']}} for q in rose_questions]
    rose = evaluate(rose_binary, cases, audit, 'llm-rose-oracle')
    if rose['returncode'] or not rose['protocol_valid']:
        raise RuntimeError('rose oracle execution failed')
    (output / 'rose_result.json').write_text(json.dumps(rose, ensure_ascii=False, indent=2)+'\n')
    project = output / 'generated'
    project.mkdir()
    shutil.copy2(challenge / 'labyrinth.cc', project)
    (project / 'CMakeLists.txt').write_text('''cmake_minimum_required(VERSION 3.13)
project(blind_reasoning LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g --coverage -fprofile-abs-path -fdiagnostics-format=json)
add_link_options(--coverage)
add_executable(labyrinth labyrinth.cc)
''')
    build = output / 'build'
    for stage, command in [('llm-cmake-generate',['cmake','-S',str(project),'-B',str(build),'-G','Ninja']),
                           ('llm-cmake-build',['cmake','--build',str(build),'--parallel','2'])]:
        result = audit.run(stage, command)
        if result['returncode'] or result['timed_out']:
            raise RuntimeError(f'{stage} failed')
    payload = ''.join(f"{q['id']} {q['kind']} {q['x']} {q['y']} {q['z']} {q['flags']}\n" for q in stress_questions)
    truth = audit.run('llm-stress-oracle', [str(build/'labyrinth')], input_text=payload)
    if truth['returncode'] or truth['timed_out']:
        raise RuntimeError('stress oracle execution failed')
    actual = []
    for line in truth['stdout'].splitlines():
        ident, value = line.split()
        actual.append({'id':ident,'value':int(value)})
    if not valid_ids(stress_questions, actual):
        raise ValueError('oracle output protocol invalid')
    actual_map = {r['id']:r['value'] for r in actual}
    answer_map = {r['id']:r['value'] for r in predictions['stress']}
    comparisons = [{'id':q['id'],'family':q['kind'],'predicted':answer_map[q['id']],
                    'actual':actual_map[q['id']],'correct':answer_map[q['id']]==actual_map[q['id']]} for q in stress_questions]
    coverage = collect(build, output / 'coverage', audit, source_name='labyrinth.cc')
    def score(correct, total):
        return {'correct':correct, 'total':total, 'accuracy_percent':round(100*correct/total,4)}
    families={family:score(sum(r['correct'] for r in comparisons if r['family']==family),
                          sum(r['family']==family for r in comparisons)) for family in ['tree','deep']}
    result={'completed_at':now(),'model':predictions['model'],'protocol_valid':protocol_valid,'freeze_verified':True,
            'freeze':freeze,'rose':score(rose['total']-rose['failed'],rose['total']),
            'stress':score(sum(r['correct'] for r in comparisons),len(comparisons)),
            'by_family':families,'stress_comparisons':comparisons,'coverage':coverage,
            'limitations':['单次小样本自测，题目生成器与答题者处于同一会话，非独立外部评测。',
                           '本次模型作答来自当前对话；重跑脚本只重放冻结答案，不会自动调用新模型。',
                           '结构深度和分支数不等同路径覆盖，不代表所有复杂业务代码。']}
    (output / 'scores.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n')
    audit.event(kind='llm_scored', rose=result['rose'],stress=result['stress'],by_family=families)
    print('模型盲测评分：'+json.dumps({k:result[k] for k in ['rose','stress','by_family']},ensure_ascii=False),flush=True)
    return result
