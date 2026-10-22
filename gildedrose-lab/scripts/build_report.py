#!/usr/bin/env python3
"""从原始结果生成中文交付报告与命令索引，不修改实验数据。"""
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import shlex
import sys
from urllib.parse import quote

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'deliverables'
DOCS = ROOT.parent / 'docs'
RUN = ROOT / 'runs' / (ROOT / 'artifacts/latest-run.txt').read_text().strip()
EVIDENCE = ROOT / 'artifacts' / RUN.name


def read(path):
    return json.loads(Path(path).read_text())


def link(path, label=None):
    path = Path(path)
    rel = os.path.relpath(path, DOCS)
    return f'[{label or path.name}]({quote(rel, safe="/")})'


def table(headers, rows):
    def clean(value):
        return str(value).replace('|','\\|').replace('\n',' ')
    return '\n'.join(['| '+' | '.join(headers)+' |', '| '+' | '.join('---' for _ in headers)+' |'] +
                     ['| '+' | '.join(clean(v) for v in row)+' |' for row in rows])


def resolve_recorded(path):
    if not path:
        return None
    if path.startswith('/work/'):
        return ROOT / 'runs' / path[len('/work/'):]
    if path.startswith('/lab/'):
        return ROOT / path[len('/lab/'):]
    p = Path(path)
    if p.is_absolute():
        return p
    if path.startswith('gildedrose-lab/'):
        return ROOT.parent / p
    return ROOT / p


def stamp(value):
    parsed = dt.datetime.fromisoformat(value)
    return parsed.astimezone(dt.timezone(dt.timedelta(hours=8))).strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]


def main():
    OUT.mkdir(exist_ok=True)
    DOCS.mkdir(exist_ok=True)
    summary = read(RUN/'summary.json')
    mutations = read(RUN/'mutation_results.json')
    scores = read(RUN/'llm/scores.json')
    cases = read(RUN/'cases.json')
    complexity = read(ROOT/'benchmark/complexity.json')
    freeze = read(ROOT/'benchmark/freeze.json')
    image = read(EVIDENCE/'image-inspect.json')[0]
    container = read(EVIDENCE/'container-inspect-before.json')[0]
    source_scope = read(RUN/'source_scope.json')
    source_manifest = read(ROOT/'external/source_manifest.json')
    duration = (dt.datetime.fromisoformat(summary['completed_at'])-dt.datetime.fromisoformat(summary['started_at'])).total_seconds()
    unique_cases = len({(c['name'],c['sell_in'],c['quality'],c['days']) for c in cases})
    first_host = min(r['started_at'] for f in (ROOT/'artifacts/host').glob('*.json')
                     if isinstance((r:=read(f)),dict) and 'started_at' in r)
    result_rows = [
        ['源码获取',summary['commit'],link(ROOT/'external/GildedRose-Refactoring-Kata/cpp','宿主机 cpp 目录')],
        ['上游测试范围','仅 cpp/；未编译其他语言目录',link(RUN/'source_scope.json','实际编译文件清单')],
        ['源码引入方式','只读 bind mount；构建上下文只有 docker/ 文件',link(EVIDENCE/'container-inspect-before.json','挂载证据')],
        ['Python → CMake → CTest','完成生成、编译及3项 CTest（其中合同测试内部执行13,965例）',link(RUN/'baseline/test_result.json')],
        ['基线测试','13,965 / 13,965 通过',link(RUN/'cases.json','全部输入与 oracle')],
        ['GildedRose.cc 行覆盖','29 / 29 = 100%',link(RUN/'baseline/coverage/text/GildedRose.cc.gcov')],
        ['GildedRose.cc 分支覆盖','38 / 38 = 100%；文本与 JSON 完全一致',link(RUN/'baseline/coverage/coverage.json')],
        ['行为 Bug 检出','20 / 20 = 100%',link(RUN/'mutation_results.json')],
        ['编译错误捕获','5 / 5 = 100%；均含源码位置与 GCC 消息',link(RUN/'mutants/E01/result.json','编译诊断示例')],
        ['链接错误捕获','1 / 1 = 100%',link(RUN/'mutants/E06/result.json')],
        ['等价改动对照','2 / 2 正常通过，观察到0次误报',link(RUN/'mutants/C01/result.json','对照证据')],
        ['模型预测现有 GildedRose 行为','24 / 24 正确',link(RUN/'llm/rose_result.json')],
        ['模型预测合成复杂分支','20 / 20 正确',link(RUN/'llm/scores.json')],
        ['已知上游需求缺口','Conjured 独立探针2例均与新需求不符，单列记录',link(RUN/'known_spec_gap.json')],
        ['最终退出状态',f"流水线 {summary['status']}；Docker 容器退出0；约 {duration:.2f} 秒",link(RUN/'summary.json')],
    ]
    environment_rows=[['宿主机','macOS / ARM64；宿主机 Python 3.13.3'],['Docker','客户端与 Engine 28.0.4；Docker Desktop 4.40.0'],
        ['容器','Debian 12 bookworm / Linux ARM64'],['容器工具','Python 3.11.2；CMake 3.25.1；GCC/gcov 12.2.0；Ninja 1.11.1'],
        ['镜像标签','qualtor-gildedrose-toolchain:bookworm'],['实测镜像 ID',image['Id']],
        ['基础镜像','debian:bookworm-slim@sha256:7ff6ba31527b9e336162fa061746c366c4b2032f4d2cff2078bea43f78efe3f8'],
        ['运行限制','2 CPU、2 GiB 内存、256 PID；禁网、只读根文件系统、无附加 capabilities'],
        ['自动日志起点（北京时间）',stamp(first_host)],['成功容器运行（北京时间）',stamp(summary['started_at'])+' 至 '+stamp(summary['completed_at'])]]
    suite_rows = [[name, count, f"{summary['suite_detection'][name]}/20",f"{summary['suite_detection'][name]/20*100:.0f}%"] for name,count in summary['case_suites'].items()]
    mutation_rows=[]
    for r in mutations:
        mutation_rows.append([r['id'],r['description'],{'behavior':'行为','compile':'编译','link':'链接','equivalent_control':'等价对照'}[r['kind']],
                              r['status'],r.get('failed_cases','—'),link(RUN/'mutants'/r['id']/'result.json','结果')])
    error_rows=[]
    for r in mutations:
        if r['kind'] in ('compile','link'):
            d=r['diagnostics'][0]
            line=d.get('line') or d.get('locations',[{}])[0].get('caret',{}).get('line')
            error_rows.append([r['id'],r['description'],r['build_returncode'],line,d['message']])
    baseline_source=f'https://github.com/emilybache/GildedRose-Refactoring-Kata/blob/{summary["commit"]}/cpp/src/GildedRose.cc'
    paragraphs=[
        '# GildedRose Docker 自动化与复杂分支推理实验报告',
        f'本报告已按后续要求更新为仅保留上游 `cpp/` 文件夹，当前成功轮次为 `{RUN.name}`。上一轮及本轮的完整测试闭环都实际运行在 Docker 中；Python、CMake、GCC、CTest、gcov 和变异检测均在容器内执行。源码位于宿主机，通过只读目录挂载引入镜像外的文件。其他语言目录已经从工作目录和交付 ZIP 中移除。',
        '**13,965 是对同一份 C++ 实现生成的输入组合记录数，不是源码文件数，也不是跨语言测试总数。** 上游业务目标是 `cpp/src/GildedRose.cc` 的 `GildedRose::updateQuality()`；`.cc` 是上游采用的 C++ 文件扩展名，按你的要求保留整个 `cpp/` 文件夹，没有更改扩展名。本轮删去其他语言目录后，C++ 输入矩阵没有变化，所以数量仍为13,965。Python 文件是运行闭环所必需的调度和解析脚本。',
        '容器内已完成“生成 → 编译 → 测试 → 解析覆盖率 → 独立注入 Bug → 统计检出率”，并重放事前冻结的当前对话模型答案进行评分。下表为本次复跑实测结果，原始证据均可直接打开。',
        table(['验证项','实测结果','证据'],result_rows),
        '100% 行/分支覆盖率对应的是上游 `cpp/src/GildedRose.cc`；100% 变异检出率对应事前固定的20个行为变异；模型100%正确率对应本次44道具体问题。这三个分母不同，均不表示软件没有任何 Bug，也不表示模型能够正确处理所有复杂条件程序。',
        '最初从 [GitHub 上游仓库](https://github.com/emilybache/GildedRose-Refactoring-Kata/tree/main) 的 main 分支浅克隆，再固定实际提交。本轮将工作树收敛为仅检出 `cpp/`；被测 [C++ 源码]('+baseline_source+') 未修改，初始与最终 SHA-256 均为 `'+summary['source_sha256']+'`，本机稀疏工作树运行前后 `git status --porcelain` 均为空。Python 负责调度和解析，不是本次 gcov 的被测语言。',
        f"保留的上游 `cpp/` 共 {len(source_manifest['files'])} 个文件，包括 C++ 源码、头文件、CMake 配置与说明。源码快照逐文件哈希见 "+link(ROOT/'external/source_manifest.json')+'。本机保留隐藏 `.git` 用于提交溯源；交付 ZIP 排除所有 `.git` 对象，以免携带其他语言的历史内容。上游许可证与需求说明另存于 '+link(DOCS/'upstream/license.txt','许可证')+' 和 '+link(DOCS/'upstream/GildedRoseRequirements.md','需求说明')+'。',
        '以下是本轮 `compile_commands.json` 中的全部基线编译输入；前两轮也只编译同样的上游 C++ 文件。变异实验只修改 `GildedRose.cc` 的独立副本，额外模型压力题也是 C++，没有执行其他上游语言实现。',
        table(['实际编译文件','角色'],[[f, '生成的 C++ 输入输出探针' if '/generated/' in f else '上游业务实现' if '/src/' in f else '上游 C++ 文本测试'] for f in source_scope['compiled_files']]),
        table(['环境项目','记录值'],environment_rows),
        '基础镜像以 digest 固定，工具链包的实际版本另有 dpkg 清单。APT 软件仓库没有固定到历史快照，因此未来重新构建可能获得补丁更新，不能承诺未来镜像逐字节相同；当前已构建镜像可直接用 `--skip-build` 复用。',
        '容器挂载关系如下。源码和脚本都在镜像外，构建、覆盖文件、变异副本及日志也持久化到宿主机。',
        table(['宿主机目录（相对实验目录）','容器目录','属性'],[[m['Source'].replace(str(ROOT)+'/',''),m['Destination'],'只读' if not m['RW'] else '可写'] for m in container['Mounts'] if m['Type']=='bind']),
        '''```mermaid
flowchart LR
  A[宿主机上游仓库] -->|只读 bind mount| B[容器内 Python]
  S[宿主机脚本与模板] -->|只读 bind mount| B
  B --> C[CMake 生成和编译]
  C --> D[CTest 与 13965 个用例]
  D --> E[gcov 文本与 JSON 核对]
  E --> F[28 个独立变异]
  F --> G[冻结模型答案评分]
  G --> H[宿主机产物和日志]
```''',
        '这一实现遵循 [Docker bind mounts](https://docs.docker.com/engine/storage/bind-mounts/) 的宿主目录挂载方式。Dockerfile 没有复制项目的指令，构建命令的上下文明确指定为 `gildedrose-lab/docker`，`.dockerignore` 仅允许 Dockerfile 和过滤规则。镜像历史、创建容器时的 Mounts 信息以及“不挂载时 /repo 和 /lab 均不存在”的实际探针一并保留，见 '+link(EVIDENCE/'image-history.txt')+'。',
        'Python 使用参数数组调用子进程，不通过 shell 拼接业务命令。每条命令记录开始/结束时间、工作目录、退出码、超时、stdout、stderr；执行探针时另存 stdin。超时会终止该子进程组。CMake 采用源码外构建：先 `cmake -S ... -B ... -G Ninja`，再 `cmake --build ... --parallel 2`，最后运行 CTest。这些命令用法对应 [CMake CLI 文档](https://cmake.org/cmake/help/latest/manual/cmake.1.html)。',
        '基线包装项目复用上游 CMake 的 GildedRoseLib 和文本测试，关闭四个会下载 GoogleTest/Catch2 的选项，再加入空库存测试与生成的合同测试。上游单元测试里存在故意写成 `EXPECT_EQ("fixme", ...)` 的占位断言，所以本报告不声称原仓库默认所有测试已通过。CTest 的3项为本实验空库存测试、13,965例合同测试和上游文本测试；文本测试的成功退出本身不等同于业务断言。',
        '测试 oracle 使用独立的分段规则描述普通商品、Aged Brie、Backstage passes 和 Sulfuras 的每天变化，未照抄原始嵌套 if-else。Conjured 在“现有行为”基线中按普通商品处理，另设“新需求”探针。测试还包含名称尾随空格，以核对代码使用精确字符串匹配。',
        table(['测试组','用例记录数','单独检出的行为变异','该组检出率'],suite_rows),
        '数量构成为：冒烟5条；边界组 `(5个非Sulfuras名称 × 7个质量值 + Sulfuras的1个质量值) × 8个销售日 × 5个运行天数 = 1,440`；有界穷举组 `(5 × 51 + 1) × 15个销售日 × 3个运行天数 = 11,520`；固定随机组1,000条。合计 `5 + 1,440 + 11,520 + 1,000 = 13,965`。每条输入包含商品名、sellIn、quality 和运行天数，分别断言这份 C++ 实现的输出。',
        f'四组共有13,965条用例记录，互异输入组合为 {unique_cases:,} 个；组间有重复，报告没有把记录数当作独立样本数。边界组围绕销售日 -3、-1、0、1、5、6、10、11 与质量0、1、2、47、48、49、50，分别执行0、1、2、5、10天。Sulfuras 使用合法质量80。有界穷举覆盖销售日 -2至12、质量0至50以及1/2/5天；固定随机组 seed 为20261021，覆盖更宽销售日与0至60天。',
        '测试生成规则与变异清单在运行前落盘并记录 SHA-256。本次只靠5个冒烟用例能检出7/20；边界组和有界穷举组都检出20/20；固定随机组检出19/20，遗漏 M18（门票接近质量上限时的条件错误）。这说明边界输入对这组缺陷有实际贡献。测试用例详情见 '+link(RUN/'cases.json')+'，全部变异详表见 [变异明细](变异明细.md)。',
        '覆盖编译使用 `-O0 -g --coverage -fprofile-abs-path`，先执行基线，再保存 `.gcda/.gcno` 原始快照。Python 分别调用 `gcov -b -c` 和 `gcov -b -c -j`，解析 `.gcov` 与 `.gcov.json.gz`，只统计匹配目标源码文件的数据，并核对可执行行数、命中行数、分支数与命中分支数。选项和 JSON 格式参考 [GCC gcov 文档](https://gcc.gnu.org/onlinedocs/gcc/Invoking-Gcov.html)；本次实测版本为 GCC 12.2.0 / JSON format 1。',
        '目标文件有29个 gcov 可执行行、38条分支边，全部命中。这里的“行”不是源文件物理行数，分支覆盖不是路径覆盖或 MC/DC。标准库、测试探针和合成压力程序没有混入该100%业务覆盖指标；本次该源码没有额外 throw 分支，原始分支与剔除 throw 后的计数相同。原始覆盖快照在 '+link(RUN/'baseline/coverage/raw','coverage/raw/')+'，后续探针运行不会改写它。',
        '每个 Bug 都从同一份原始源码独立生成，保存补丁和前后哈希，使用独立构建目录。行为变异只有在编译成功、探针返回成功、输出协议有效而断言不匹配时才记为 killed；构建失败、超时或输出损坏不会被误算成行为 Bug 检出。行为检出率为 `20 / 20 = 100%`。两个等价变异（循环后置递增改前置递增、自身相减改零）均 survived，作为无行为变化的对照；两个样本的零误报不应外推成总体零误报率。',
        '编译错误使用 GCC JSON 诊断提取消息和文件/行/列。因为 Ninja 可能把编译器输出放到构建 stdout，解析器同时检查 stdout 与 stderr。链接错误通过独立的 undefined reference 分类捕获。六个负向构建均返回1，均捕获到了预期阶段的诊断，且测试脚本继续处理后续变异。',
        table(['编号','注入错误','构建返回码','源码行','捕获消息'],error_rows),
        '上游需求缺口单独测得：`Conjured Mana Cake` 在 sellIn=3、quality=6 时一天后实际 quality=5，新需求应为4；在 sellIn=0、quality=6 时实际为4，新需求应为2。此结果说明当前原始实现尚未支持新功能，既不混入本实验行为变异分母，也没有通过修改上游代码隐藏它。',
        '大模型部分按你的选择使用当前对话模型。题目生成器只写源码和问题，不计算答案；模型只读题目与源码后作答。最终题目含24个原仓库多日边界问题，以及12个条件树问题、8个深层状态更新问题。冻结前补充了4个负余数入口问题，未执行的初版也已保留。',
        f"答案于北京时间 {stamp(freeze['frozen_at'])} 冻结，SHA-256 为 `{freeze['files']['predictions.json']}`。评分前逐个核对题目、源码、协议和预测文件哈希；此后才调用 C++ 可执行程序取得答案。题目 ID 不允许缺失、重复或多出。原始答案见 "+link(ROOT/'benchmark/predictions.json')+'，冻结记录见 '+link(ROOT/'benchmark/freeze.json')+'，逐题输入/预测/实际值见 [模型盲测逐题结果](模型盲测逐题结果.md)。',
        table(['模型测试对象','题数','正确','准确率'],[['原仓库行为',24,24,'100%'],['合成条件树',12,12,'100%'],['合成深层状态更新',8,8,'100%'],['合计',44,44,'100%']]),
        f"合成源码有 {complexity['source_lines']} 个物理行、91个 if、115个逻辑 &&/|| 运算符，最大 if 嵌套22层。tree 函数有31个 if，deep 函数有60个 if 和20级连续门控；不计短路运算的逐函数圈复杂度为32和61。D01、D02 走完20级门控，D06 在最深层走入两级回退条件。涉及负数取模、短路条件、位掩码、嵌套返回和逐级更新状态。合成代码是额外压力题，不冒充上游仓库原有代码。",
        '这20个合成输入对应的实际覆盖率只有 **97/214 行 = 45.33%，149/442 分支 = 33.71%**；剔除 throw 分支后为149/430 = 34.65%。合成器还可能产生相关或不可达条件。因此本次结果只能支持“模型答对了这些给定输入”，不能支持“所有深层分支均已验证”。题目作者和答题者处于同一会话，且 GildedRose 是公开 kata，这是一轮有限自测，不是独立第三方模型评测；没有多模型、多采样或独立随机种子对照，运行时也没有可核验的精确模型快照。',
        '本次全过程包含真实失败及修复：Docker 沙箱套接字受限；默认凭据助手阻塞；独立 Docker 配置初次未发现 Buildx；APT 单个软件包下载 HTTP 500；首轮容器执行时日志事件 kind 参数冲突。收敛为 cpp/ 后第一次使用 --skip-build 时镜像标签不存在，随后按原 Dockerfile 成功重建并复跑；日志不足以判断标签此前为何消失。所有失败日志均保留。原因、修复与对应日志见 '+link(DOCS/'实现与修复记录.md')+f'。本报告采用最新成功轮次 `{RUN.name}`，容器退出0，源码未变，实验容器已删除，工具链镜像保留供复用。',
        '复现时在 Qualtor 根目录执行以下命令。首条包含镜像构建；镜像已存在时第二条可直接运行。默认使用新的时间戳目录，不覆盖历史运行。',
        '```bash\npython3 gildedrose-lab/run.py\n# 使用已构建的工具链\npython3 gildedrose-lab/run.py --skip-build\n```',
        '重跑会生成测试与变异、运行全部构建/覆盖/检出流程，并重放已冻结的44份模型预测。**它不会自动产生新的模型回答，也不会发起模型 API 请求。** 要测新的模型，应建立独立题目和答案目录，重新执行“先提交答案、冻结、再评分”的协议。本次 Python 无第三方依赖；Docker 首次构建需要访问公开镜像和 Debian 软件仓库，实验容器禁网。',
        '从 ZIP 解压后也使用相同入口。附件包含上游 cpp/ 快照及固定提交、逐文件哈希；入口支持无 `.git` 的快照模式，先校验目录范围和全部源码哈希，再运行容器。任何源码被更改、缺失或增加，都会在编译前拒绝执行。',
        '全量过程附件包含：上游 cpp/ 源码快照、最终脚本/模板、命令时间线、每条实验命令的 stdout/stderr/stdin、失败尝试、生成用例、28个变异源码与补丁、编译产物、gcov 原始与解析文件、容器/镜像元数据、模型题目/预测/冻结哈希/逐题评分以及 SHA-256 文件清单。历史 C++ 实验日志也保留，以满足全程记录要求；其原始克隆输出可提及其他语言，但不再附带那些语言的源码。Docker 镜像本体不装入过程 ZIP，仍保留在本机 Docker 中。附件入口为 [全量执行过程](全量执行过程.md)。',
        '日志范围说明：实验下载、镜像构建、容器运行、CMake/CTest/gcov、Bug 注入和模型评分命令均有自动原始日志；日志工具建立前的环境检查以整理记录和工具结果保存，见 '+link(DOCS/'过程记录.md')+'。无关进程标题已从一次进程检查输出中清除，避免把其他应用的参数带入附件。文件哈希清单用于检查附件内容完整性。'
    ]
    (DOCS/'执行报告.md').write_text('\n\n'.join(paragraphs)+'\n')
    details=['# 全部变异明细',table(['编号','变异内容','类别','结果','失败用例数','原始结果'],mutation_rows),
             '每项行为变异的第一个反例仅用于解释；检测使用全部预先生成用例。所有失败明细保存在各自 test_result.json。']
    for r in mutations:
        if r.get('first_counterexample'):
            counter=r['first_counterexample']
            details.extend([f"**{r['id']}：{r['description']}**。输入 `{json.dumps(counter['input'],ensure_ascii=False)}`；期望 `{json.dumps(counter['expected'],ensure_ascii=False)}`；实际 `{json.dumps(counter['actual'],ensure_ascii=False)}`。",
                            link(RUN/'mutants'/r['id']/'mutation.diff','源码补丁')+' · '+link(RUN/'mutants'/r['id']/'test_result.json','全部反例')])
    (DOCS/'变异明细.md').write_text('\n\n'.join(details)+'\n')
    rose_actual={}
    rose_result=read(RUN/'llm/rose_result.json')
    for line in resolve_recorded(rose_result['stdout_log']).read_text().splitlines():
        ident,sell,quality,name=shlex.split(line)
        rose_actual[ident]=(int(sell),int(quality))
    predictions=read(ROOT/'benchmark/predictions.json')
    rose_prediction={r['id']:(r['sell_in'],r['quality']) for r in predictions['rose']}
    rose_rows=[[q['id'],repr(q['name']),f"{q['sell_in']}, {q['quality']}, {q['days']}",str(rose_prediction[q['id']]),str(rose_actual[q['id']]),'正确' if rose_prediction[q['id']]==rose_actual[q['id']] else '错误'] for q in read(ROOT/'benchmark/rose_questions.json')]
    stress_map={r['id']:r for r in scores['stress_comparisons']}
    stress_rows=[[q['id'],q['kind'],f"{q['x']}, {q['y']}, {q['z']}, {q['flags']}",stress_map[q['id']]['predicted'],stress_map[q['id']]['actual'],'正确' if stress_map[q['id']]['correct'] else '错误'] for q in read(ROOT/'benchmark/questions.json')]
    (DOCS/'模型盲测逐题结果.md').write_text('\n\n'.join(['# 模型盲测逐题结果','预测文件在运行标准答案前冻结，评分后未修改。以下只是输出与评分，不包含模型内部推理。',
        table(['ID','商品','输入 sellIn,quality,days','预测 (sellIn,quality)','实际 (sellIn,quality)','结果'],rose_rows),
        table(['ID','函数','输入 x,y,z,flags','预测输出','实际输出','结果'],stress_rows),
        '精确哈希、评分时刻、原始执行输出及覆盖信息见 '+link(RUN/'llm/scores.json')+'。'])+'\n')
    events=[]
    event_files=[ROOT/'artifacts/host/events.jsonl']+list((ROOT/'runs').glob('*/logs/events.jsonl'))
    for f in event_files:
        for line in f.read_text().splitlines():
            event=json.loads(line)
            if event.get('kind')=='command_end':
                event['event_file']=str(f)
                events.append(event)
    events.sort(key=lambda r:r['started_at'])
    process=['# 全量执行过程索引',f'本索引包含 {len(events)} 条已结束的实验和环境命令。时间为北京时间 UTC+8；原始 JSON 使用 UTC。先前环境检查见 '+link(DOCS/'过程记录.md')+'，实现变更见 '+link(DOCS/'实现与修复记录.md')+'。',
             '日志没有截断；页面只索引输出文件，全部原始内容在 ZIP 内。注入编译错误的非零退出码属于预期实验结果；首轮 Docker 下载与实现失败也如实保留。']
    for i,event in enumerate(events,1):
        paths=[]
        for key,label in [('stdout_log','stdout'),('stderr_log','stderr'),('stdin_log','stdin')]:
            path=resolve_recorded(event.get(key))
            if path and path.exists(): paths.append(link(path,label))
        process.extend([f"{i}. **{stamp(event['started_at'])} · {event['stage']}**。退出码 `{event['returncode']}`；耗时 `{event['duration_seconds']}` 秒；超时 `{event['timed_out']}`。",
                        '```text\ncwd: '+event['cwd']+'\n'+shlex.join(event['argv'])+'\n```',' · '.join(paths)])
    (DOCS/'全量执行过程.md').write_text('\n\n'.join(process)+'\n')
    provenance={'generated_at':dt.datetime.now(dt.timezone.utc).isoformat(),'run_id':RUN.name,'repository_revision':summary['commit'],
                'upstream_scope':'cpp/','upstream_snapshot_files':len(source_manifest['files']),
                'source_sha256':summary['source_sha256'],'cases_sha256':summary['cases_sha256'],
                'image_id':image['Id'],'predictions_sha256':freeze['files']['predictions.json'],'indexed_commands':len(events),
                'unique_case_inputs':unique_cases,'pipeline_duration_seconds':duration}
    (OUT/'provenance.json').write_text(json.dumps(provenance,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps(provenance,ensure_ascii=False,indent=2))


if __name__=='__main__':
    main()
