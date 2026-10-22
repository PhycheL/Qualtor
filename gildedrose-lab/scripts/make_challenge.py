#!/usr/bin/env python3
"""只生成题目和 C++ 源码；此脚本不计算题目答案。"""
import hashlib
import json
from pathlib import Path
import random
import sys
from audit import Audit


def generate(root):
    root = Path(root)
    root.mkdir(parents=True, exist_ok=False)
    rng = random.Random(61720261021)
    code = ['#include <iostream>', '#include <string>', '',
            'int tree(int x, int y, int z, unsigned flags) {']
    node = 0
    def emit_tree(depth, indent):
        nonlocal node
        pad = '    ' * indent
        if depth == 0:
            a, b, c, d = [rng.randint(-7, 7) for _ in range(4)]
            code.append(f'{pad}return ({a})*x + ({b})*y + ({c})*z + ({d});')
            return
        node += 1
        k, m = rng.randint(-3, 3), rng.randint(1, 5)
        cond = rng.choice([f'(x + y) % 5 <= ({k})', f'x < y || z == ({k})',
                           f'((flags & {1 << m}u) != 0 && z >= ({k})) || x == -y',
                           f'((x - z) * (y + 1)) % 7 > ({k})',
                           f'x <= ({k}) && (y > z || (flags & {1 << m}u) == 0)'])
        code.append(f'{pad}if ({cond}) {{ // T{node:02d}')
        emit_tree(depth - 1, indent + 1)
        code.append(f'{pad}}} else {{')
        emit_tree(depth - 1, indent + 1)
        code.append(f'{pad}}}')
    emit_tree(5, 1)
    code.extend(['}', '', 'int deep(int x, int y, int z, unsigned flags) {', '    int score = x - y + 2*z;'])
    bits = [rng.randrange(2) for _ in range(20)]
    offsets = [rng.randint(-9, 9) for _ in range(20)]
    def emit_deep(level, indent):
        pad = '    ' * indent
        if level == 20:
            code.append(f'{pad}return score + 1000;')
            return
        code.append(f'{pad}if ((((flags >> {level}) & 1u) == {bits[level]}u) && (score % 5 != {level % 5} || x == 0)) {{ // D{level:02d}')
        code.append(f'{pad}    score = (score * 3 + ({offsets[level]})) % 97;')
        emit_deep(level + 1, indent + 1)
        code.append(f'{pad}}} else {{')
        code.append(f'{pad}    if ((score < 0 && y <= z) || (x + y) % 3 == 0) {{')
        code.append(f'{pad}        if (z % 2 != 0) {{')
        code.append(f'{pad}            return score + {level + 1}*x - z;')
        code.append(f'{pad}        }} else {{')
        code.append(f'{pad}            return score - {level + 1}*y + z;')
        code.append(f'{pad}        }}')
        code.append(f'{pad}    }} else {{')
        code.append(f'{pad}        return score + {level + 1}*y - z;')
        code.append(f'{pad}    }}')
        code.append(f'{pad}}}')
    emit_deep(0, 1)
    code.extend(['}', '', 'int main() {', '    std::string id, kind; int x,y,z; unsigned flags;',
                 '    while (std::cin >> id >> kind >> x >> y >> z >> flags) {',
                 '        int result = kind == "tree" ? tree(x,y,z,flags) : deep(x,y,z,flags);',
                 "        std::cout << id << ' ' << result << '\\n';", '    }',
                 '    return std::cin.eof() ? 0 : 2;', '}'])
    source = '\n'.join(code) + '\n'
    (root / 'labyrinth.cc').write_text(source)
    mask = sum(b << i for i,b in enumerate(bits))
    rows = []
    for values in [(-7,2,3,19), (5,-3,-2,42), (0,0,0,0), (9,4,-5,63), (-4,-6,1,32), (2,7,8,17),
                   (-1,1,-3,7), (3,-2,4,20), (-8,1,3,7), (1,-3,2,4), (1,-3,-1,4), (-1,-2,-4,0)]:
        rows.append({'id': f'T{len(rows)+1:02d}', 'kind':'tree', 'x':values[0], 'y':values[1], 'z':values[2], 'flags':values[3]})
    for i,(x,y,z,flags) in enumerate([(0,0,0,mask), (0,2,-1,mask), (0,0,1,mask^(1<<4)),
                                     (0,-3,2,mask^(1<<8)), (0,1,1,mask^(1<<12)),
                                     (0,0,-1,mask^(1<<19)), (-5,2,3,mask), (4,-3,-2,mask)]):
        rows.append({'id':f'D{i+1:02d}', 'kind':'deep', 'x':x,'y':y,'z':z,'flags':flags})
    (root/'questions.json').write_text(json.dumps(rows,indent=2)+'\n')
    rose_rows=[]
    names=['Elixir', 'Aged Brie', 'Backstage passes to a TAFKAL80ETC concert', 'Sulfuras, Hand of Ragnaros', 'Conjured Mana Cake', 'Aged Brie ']
    for i,(name_index,sell,quality,days) in enumerate([
        (0,1,3,2),(0,0,1,1),(0,-1,50,7),(0,11,50,12),
        (1,0,48,2),(1,1,47,2),(1,-3,49,1),(1,10,0,12),
        (2,11,47,2),(2,10,48,1),(2,6,40,2),(2,5,48,1),
        (2,0,50,1),(2,1,47,2),(2,12,0,8),(2,-2,0,3),
        (3,-3,80,100),(3,5,80,0),(4,0,6,2),(4,3,6,4),
        (5,0,4,2),(0,0,0,100),(1,1,0,3),(2,6,0,6)]):
        rose_rows.append({'id':f'R{i+1:02d}','name':names[name_index],'sell_in':sell,'quality':quality,'days':days})
    (root/'rose_questions.json').write_text(json.dumps(rose_rows,ensure_ascii=False,indent=2)+'\n')
    stats={'seed':61720261021,'if_count':source.count('if ('),'max_if_nesting':22,
           'tree_if_count':31,'deep_if_count':60,'logical_operators':source.count('&&')+source.count('||'),
           'cyclomatic_per_function_excluding_short_circuit':{'tree':32,'deep':61},
           'deep_gate_count':20,'source_lines':len(code),'source_sha256':hashlib.sha256(source.encode()).hexdigest(),
           'note':'上述 if 指标只计 tree/deep；另有 main 的输入循环与 ?: 分发。结构复杂度不等同全部路径已覆盖。'}
    (root/'complexity.json').write_text(json.dumps(stats,ensure_ascii=False,indent=2)+'\n')
    (root/'prompt.md').write_text('''# 当前对话模型盲测协议

先阅读 `labyrinth.cc`、`questions.json` 和上游 `GildedRose.cc`、`rose_questions.json`，仅通过模型推理给出输出。
在第一次运行这些输入或查看标准答案前，将答案保存为 `predictions.json` 并登记 SHA-256。
不允许调用代码执行器计算这些题目的答案；评分程序只能在答案文件冻结以后运行。
C++ 使用 GCC 12 / C++17；负整数除法向零截断，余数与被除数同号。
GildedRose 题目要求预测现有代码行为（包含尚未实现 Conjured 特性的现状）。
答案格式：`{"model":"当前对话模型","rose":[{"id":"R01","sell_in":-1,"quality":0}],"stress":[{"id":"T01","value":123}]}`。
评分使用精确匹配，缺失、重复或额外 ID 均算协议错误；不允许得分后改答案。
这是单次小样本、当前执行模型的自测。题目生成器与答题者处于同一会话，不能宣称独立测评或推广为所有大模型的能力。
''')
    Audit(root/'logs').event(kind='challenge_generated_without_oracle',files={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in root.iterdir() if p.is_file()})
    print(json.dumps(stats,ensure_ascii=False,indent=2))


if __name__=='__main__':
    generate(sys.argv[1])
