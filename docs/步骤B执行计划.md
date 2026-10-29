# 步骤 B 执行计划：头文件与模板（R-06、R-07）

> **计划，未实施（2026-10-29）。** 基点为 `08204ac`：评测模块 0.3.0，第 03 轮校准 passed，103 题准入有效，工作区干净。本文供执行方逐步实施，完成后交开发 Agent 按第 9 节验收。实施结果写入[题库验证说明](题库验证说明.md)新增的第 15 节和[研发日志](研发日志.md)，本文不追记执行结果。
>
> 依据：[题库构建方案](题库构建方案.md)第 2、7 节，[评测规格](评测规格.md)第 7 节，[决策记录](决策记录.md) D015–D017，以及 2026-10-29 对代码影响面、替换版本构建和候选材料的只读调研。

## 0. 目标与完成标准

评测模块和独立产品要支持三类新题目：

- 被测代码全部在头文件中（R-06）；
- 被测代码在当前变异算子下没有变异（零变异口径）；
- 替换版本需要替换头文件（R-07）。

本步骤要建成覆盖这三类的新题，处理步骤 A 审查遗留的 4 项，把评测模块升到 0.4.0，并在 Linux ARM64 Docker 完成校准、标定、准入和正式路径验收。

全部满足以下条件，步骤 B 才算完成：

1. 0.4.0 完整校准 passed，全部样本各两次（含 CAL-21–28）。
2. 第 4 节的新题全部签署准入；未纳入的题按第 4.3 节记录原因。
3. 旧 103 题不受影响，以下各项全部成立：
   - `task.json` 和 `hidden/` 都没有改动；
   - 题目指纹和准入不变，不需要重签；
   - `mull_config_text()` 输出逐字节不变；
   - 产品生成的 TASK.md 逐字节不变。
4. 旧冻结产物在 0.4.0 下补评，除版本、指纹字段外指标与 0.3.0 完全一致。
5. 用干净提交跑 `evaluator/run.py` 正式路径，用真实模型对第 6 节列出的 5 道题各生成 1 次，全部 scored，并且 M1 不适用的口径正确。
6. D018 写入决策记录，第 8 节列出的文档全部同步；每条实验命令都有 Audit 记录。

## 1. 范围

**本步骤要做：**

- R-06：在 `task.json` 增加可选的 `target_headers`。头文件覆盖率用冻结分母统计。无被测源文件或零变异时，M1 记为不适用。
- R-07：替换版本可以替换可见头文件，构建时复制一份源码树，在副本里原位替换。
- 步骤 A 遗留的 4 项：
  - 保留宏名校验；
  - 校准报告展示 M4；
  - 增加 CAL-21 弱反向样本；
  - 收紧 CAL-18–20 的阈值。
- 顺带修复 `evaluator/common/coverage.py`：没有任何 `.gcda` 时，写文件前没有先建目录。
- 新题见第 4 节，校准样本见第 5 节，评测模块版本升为 0.4.0。

**本步骤不做：**

| 事项 | 归属 |
|---|---|
| R-01、R-04；meetup（依赖 Boost.Date_Time） | 步骤 C |
| list-ops：参考解用了 `[[maybe_unused]]`，属于 C++17，不能原样使用 | 维持排除 |
| Q-03 人工审阅、AMD64、验收集、基线噪声 | 后续工作 |
| 历史产物全量补评 | 只做第 7 节的回归补评 |
| 镜像改动 | `08204ac` 已改为按完整名称解析，本步骤不再改 |
| 比较规则中主指标的定义 | 不改；只规定 M1 不适用的题怎样退出 M1 配对，见 D018-3 |
| 同时有被测源文件和被测头文件的混合题 | 本步骤拒绝，留作后续工作，避免没有校准的语义进入正式评测 |

## 2. 开工前的决定（D018 草案）

执行第一步把本节原样写入决策记录。措辞可以调整，决定的内容不能改。

**D018-1 字段**
- `task.json` 新增顶层可选字段 `target_headers`。它决定评分范围，与 `target_sources` 同类，不放进 `build`。
- 列表中的路径须满足：
  - 是可见文件；
  - 位于源码根目录内，不经过符号链接；
  - 后缀限 `.h`、`.hh`、`.hpp`、`.hxx`、`.inl`；
  - 与 `target_sources`、`build.support_sources` 互斥。
- 一道题只能是两种形态之一：
  - `target_sources` 非空且没有 `target_headers`，即旧语义；
  - `target_sources` 为空且 `target_headers` 非空，即纯头文件题。
- 校验函数放在共享契约里，两份契约文件保持逐字节相同。
- 产品公开任务在 9 个必填字段之外，可选字段从 `build` 扩为 `build`、`target_headers`。runner 只在题目有该字段时投影它。

**D018-2 头文件覆盖率**
- 插桩范围：有 `target_headers` 的题，覆盖率构建要给全部编译单元插桩（测试、依赖源文件和被测源文件），原因有两个：
  - 头文件里的代码在测试单元中实例化；
  - 内联函数和模板实例是 COMDAT。链接器如果保留了未插桩单元里的那份副本，计数会丢失，覆盖率就会取决于链接顺序。
- 统计范围：只统计被测头文件，依赖文件自身的行仍不计入。Mull 插件仍只加在被测源文件上。
- 冻结分母：
  - 行按行号跨编译单元合并；
  - 函数按 `(start_line, start_column)` 合并各实例，任一实例执行过即算覆盖；
  - 分母来自参考测试的覆盖率运行，写入 `hidden/coverage_baseline.json`；
  - 必要时可加只在准备阶段编译的显式实例化文件，放在 `hidden/coverage_instantiation/*.cc`，评分时不编译；
  - 产物的 C1 和 C3 只在冻结集合上计算。冻结集合之外的行不计入，只记数量供诊断；
  - 每个被测头文件至少要有一行冻结代码。
- C2：头文件分支在各实例之间没有稳定的对应关系，纯头文件题的 C2 记为不适用（⊥）。
- 题目指纹：`coverage_baseline.json` 与 `mutation_baseline.json` 一样只取实质内容（各头文件的哈希、冻结行和冻结函数），时间、run-id 等元数据不进指纹。重建题目时与 `mutation_baseline.json` 一样保留。
- 没有 `target_headers` 的题，覆盖率语义、插桩范围和编译命令全部保持不变。

**D018-3 M1 适用性**
- 两种情况下 M1 不适用，原因记为：
  - `header_only`：`target_sources` 为空；
  - `zero_mutants`：准备阶段 Mull 输出 “No mutants found”，且没有报告，证据保存 stdout。
- 题目的状态由冻结分母 `mutation_baseline.json` 记录：`"mutation": {"applicable": false, "reason": ...}`，`mutants` 为空。分母的实质内容只在存在这个键时才加入它，旧题的指纹计算结果不变。
- 结果的表示：
  - M1 不适用的题，无论产物状态如何（包括 invalid），`M1_e2e` 和 `M1_valid` 都为 ⊥；
  - 结果中记 `not_applicable: {"M1": 原因}`，纯头文件题另记 `"C2": "header_only"`；
  - 评分时不运行 Mull。
- 汇总与比较：
  - 汇总照常跳过 ⊥，但把“不适用”和“缺失”分别计数；
  - 比较时，M1 不适用的题不进入 M1 配对集合，在结论中写明排除了多少题；
  - 主指标的定义和守护指标规则都不变。
- 适用 M1 的题，如果评分时 Mull 没有出报告，仍按 `infra_error` 处理。

**D018-4 不适用 M1 的题，用手写变异衡量缺陷检出**
- 数量：每题至少 5 个手写变异。被测代码有效行数不超过 30 的小题（leap、two-fer、hello-world、reverse-string）至少 3 个。
- 每个变异的要求：
  - `kind: handwritten`，`expect: fail`；
  - 只改一处语义，模拟常见缺陷，例如边界、比较、遗漏分支、错误常量、状态没有更新；
  - 能和参考测试一起编译，由测试失败检出，不能靠编译失败检出；
  - 差异必须出现在有定义的行为上，只在未定义行为下不同的变异不能用（D015）。
- 存放：源文件是 `benchmark/tools/handwritten_variants/<题目 ID>/` 下的 patch 和说明，由导入脚本生成到 `hidden/variants/`，保证重建时逐字节一致。
- 这类题的缺陷检出看 M2；有真实缺陷时另看 M4。产物无效的情况由 V2 反映，不新增指标。

**D018-5 准入**
- M1 适用的题：准入条件不变。
- M1 不适用的题，需要同时满足：
  - 参考测试有效且稳定；
  - 纯头文件题已有 `coverage_baseline.json`；
  - 参考测试的 C1 达到 `reference_min_c1`。纯头文件题按冻结分母计算，零变异题按普通行覆盖计算；
  - 手写变异数量达标，并且全部被参考测试检出；
  - 真实缺陷版本全部被检出，等价版本全部通过；
  - 没有标为 pending 的结论。
- `reference_min_c1` 的缺省值为 0.8，只在 M1 不适用时读取，不写进旧题的 `task.json`。
- 没有变异分母可用的题，探针不是必需的。

**D018-6 R-07 替换头文件**
- 可替换的文件：
  - 被测源文件、被测头文件和可见头文件；
  - 依赖源文件仍不能替换（D017），不可见的文件也不能替换。
- 构建方式：
  - 宿主机按 `source.files` 复制整棵源码树，逐个校验 sha256；
  - 在副本中原位写入替换文件，再以原路径只读挂入容器；
  - 所有替换版本，包括已有的 hw-01、eq-02、tagged-null，都走这一条路径。
- 不采用“覆盖目录放在 -I 最前面”的做法。同目录用引号包含的头文件会先在包含它的文件所在目录查找，已核实 103 题中有 97 题是这种写法。

**D018-7 步骤 A 遗留项**
- 保留宏名：两份契约同时拒绝以下宏名，标识符形式的宏值也按同样规则限制：
  - 以 `__` 开头的名字；
  - 匹配 `_[A-Z]*` 的名字；
  - C99/C11/C++11 关键字和替代记号；
  - `defined`。
- 校准报告：指标列表和 Markdown 加入 M4、V2，并展示不适用的原因。
- 新增 CAL-21 弱反向样本。
- CAL-18–20 的覆盖率和 M1 期望固定为 0.3.0 实测值，作为本步骤覆盖率重构的回归断言（第 5.2 节）。

**D018-8 版本与兼容**
- 评测模块升为 0.4.0：M1 口径、覆盖率和替换版本构建都有变化。
- 旧题遵守第 0 节第 3 条。
- 产品只在 `target_headers` 存在时增加提示词行，旧题的 TASK.md 逐字节不变。产品目录指纹仍会随提交变化，研发日志要写明旧题的生成行为没有变化。

## 3. 实施顺序

每个阶段结束时，四组单元测试都要通过：

```bash
python3 -B -m unittest discover -s evaluator/assessment/tests -p "test_*.py"
python3 -B -m unittest discover -s evaluator/runner/tests -p "test_*.py"
python3 -B -m unittest discover -s benchmark/tools/tests -p "test_*.py"
python3 -B -m unittest discover -s agents/tests -p "test_*.py"
```

建议每个阶段单独提交，便于审查和回退。下表的行号以 `08204ac` 为准，实施时以函数名为准。

### B0 文档先行与金标准（只改文档和测试夹具）

1. **写入 D018**：把第 2 节写进决策记录，单独提交，和步骤 A 的 `d050890` 做法一样。
2. **订正题库构建方案**：
   - 第 1.4、5.1、5.2 节：meetup 移到步骤 C；“6 个代码全在头文件里”改为“5 个可接入加 meetup”；list-ops 归入 C++17。
   - 第 2 节：R-06、R-07 两行标为进行中。
3. **用 `08204ac` 的代码生成两份金标准，存为测试夹具**：
   - 103 道旧题经 `public_task()` 投影、再由产品 `task_text()` 生成的 TASK.md 的 sha256；
   - `mull_config_text()` 的 sha256。

   这两份夹具在 B4 中用作回归断言，必须在修改产品之前生成。

### B1 遗留小项与基础修复

| 改动 | 位置 | 测试 |
|---|---|---|
| 保留宏名和宏值（D018-7） | `evaluator/assessment/build_contract.py` 与 `agents/generator/build/contract.py` 的宏校验处（约第 40–47 行），两份同步修改 | 在 `test_build_contract.py` 增加拒绝用例：`__GNUC__`、`_GLIBCXX_DEBUG`、`private`、`defined`、`X=__LINE__`、`X=int`。另确认 `TE_POW_FROM_RIGHT`、`TE_NAT_LOG` 仍能通过，两份文件哈希相同的断言保持 |
| 展示 M4、V2 和不适用原因 | `calibrate.py` 的指标列表（约第 170 行）和 Markdown 表 | 报告快照测试 |
| 支持断言 ⊥ | `calibrate.py` 的 `check_relations` 增加 `{"metric": ..., "op": "na", "reason": ...}`，要求值为 null 且原因一致；原有的“指标缺失”判定不变 | 正例与反例 |
| 没有 `.gcda` 时先建目录 | `evaluator/common/coverage.py` 约第 203 行 | 用无数据的目录复现，原来抛 FileNotFoundError，修复后不再抛 |
| 文档 | 产品 README 写明保留宏规则 | — |

### B2 R-07：复制源码树构建替换版本

1. 修改 `common.validate_task` 中替换版本的校验（约第 136–138 行），可替换范围按 D018-6；替换依赖源文件或不可见文件时给出明确错误。
2. 修改 `pipeline.py` 的替换版本构建（约第 223–244 行）：
   - 宿主机建临时目录，按 `source.files` 复制文件并校验哈希；
   - 写入替换文件并校验 `variants[].files` 中的哈希；
   - 以原 repo 路径只读挂载，去掉单独的 `/variant` 挂载；
   - 结果中记录副本的树哈希；
   - `HostExecutor.at()` 按副本根目录换算路径。
3. 同步修改 `test_docker_wiring.py` 中与替换版本挂载相关的断言（约第 164、175–178 行）。
4. 新增单元测试：
   - 用一道微型题构造 `a.cpp` 以 `#include "a.h"` 包含同目录头文件，替换版本只换 `a.h`，断言副本中的文件、挂载规格和编译单元清单正确；
   - 替换依赖源文件时被拒绝；
   - 哈希不符时被拒绝。
5. 旧替换版本的判定不变，由第 7 节的校准和回归补评在 Docker 中验证。

### B3 R-06 评测侧

**契约（两份同步修改）**
- `validate_build` 或新增的函数校验 `target_headers`，规则见 D018-1。
- `compile_command_problems`：有被测头文件的覆盖率构建中，要求全部编译单元都带 `--coverage`；Mull 插件仍只允许出现在被测源文件上。
- `cmake_build_args` 传入被测头文件。

**CMake 模板**
- 文件：`evaluator/assessment/cmake/CMakeLists.txt`。
- 被测源文件为空、但传入了被测头文件时，不再报 `FATAL_ERROR`（约第 14–18 行）。
- 覆盖率模式下，有被测头文件时给全部编译单元插桩（约第 39 行）。
- 其余情况的生成结果不变。

**覆盖率采集**
- 文件：`evaluator/common/coverage.py`。
- 被测头文件的数据跨 `.gcda` 合并，取代第 181–182 行抛 ValueError 的分支；合并规则按 D018-2。
- 路径先用 `realpath` 规范化。
- 文本解析与 JSON 解析的一致性检查改为逐个 `.gcda` 进行。

**准备阶段**
- 文件：`prepare_task.py`。
- 纯头文件题：
  - 不运行 Mull，写入 `mutation.applicable=false`；
  - 由参考测试和可选的实例化文件生成 `coverage_baseline.json`；
  - 探针改为可选；
  - 修复缺少 `mull_config_sha256` 时的 KeyError（约第 99 行）。
- 零变异判定：只在准备阶段，按 mull-runner 退出码 0、stdout 含 “No mutants found”、没有报告三个条件同时成立判定，并保存原始 stdout。
- 判断是否通过：M1 不适用的题按 D018-5 判定。

**评分**
- `pipeline.py`：M1 不适用时跳过 Mull；`_coverage` 对被测头文件使用冻结集合；结果写入 `not_applicable`。
- `judge.py` 的 `metrics`：M1 不适用时两项都为 None，不再对 invalid 记 0。
- `common.task_sha256`：`coverage_baseline` 只取实质内容；`mutation` 键只在存在时加入。

**汇总**
- 文件：`aggregate.py`。
- 按题和跨题汇总时，分别报告 M1 不适用的题数和缺失题数。
- `compare` 输出 `excluded_not_applicable`。

**版本**：`VERSION` 改为 0.4.0。

**单元测试**
- 行和函数跨编译单元合并：用夹具或构造的 gcov JSON，含同一模板的两种实例；
- 实例化较少的产物，C1 不高于冻结分母下的参考值；
- 冻结集合之外的行不计入；
- 零变异判定的三个条件，缺任一条件都不判为零变异；
- M1 不适用时，invalid 产物的 `M1_e2e` 为 None；
- 旧题分母的实质内容和题目指纹不变：取若干旧题，与 B0 的金标准比对；
- 汇总计数和比较时的排除计数。

### B4 产品与 runner

**产品：`agents/generator/task.py`**
- 接受可选的 `target_headers`。`target_sources` 只有在 `target_headers` 非空时才允许为空（约第 25–26 行）。
- `task_text` 只在存在被测头文件时修改提示词：
  - 在“被测文件”一行改写为“被测头文件：…”；
  - 被测源文件为空时，写明“被测代码全部位于被测头文件中”。
- 其他题的 TASK.md 必须逐字节不变。

**产品构建**
- `agents/generator/build/container_build.py` 和 `agents/toolchains/cmake/CMakeLists.txt` 支持被测源文件为空。
- 产品只做普通构建，不涉及覆盖率。

**产品 README**：说明 `target_headers` 的用途、取值限制和纯头文件题的提示词。

**runner**
- `evaluator/runner/host.py` 的 `public_task`：只在存在 `target_headers` 时投影它；放宽对被测源文件非空的检查。
- `evaluator/runner/scenarios.py`：泄露检查清单加入 `coverage_baseline.json`、`coverage_instantiation`。

**测试**
- 产品接受纯头文件题的公开任务；
- 混合题和后缀不合法的头文件被拒绝；
- 103 道旧题的 TASK.md 与 B0 金标准逐字节相同；
- runner 投影纯头文件题后，产品能加载。

### B5 建题工具

**`bankutil.py`**
- `write_task` 支持 `target_headers`；
- 重建题目时保留 `coverage_baseline.json`；
- 新增函数，把手写变异的 patch 生成到 `hidden/variants/`；
- 不给旧题补任何新键。

**准入与复核工具**
- `admit.py`：按 D018-5 核对 M1 不适用的题，报告中增加冻结 C1、手写变异的数量和检出数。
- `prepare_new_tasks.py`、`mutant_report.py`、`apply_review.py`、`host_check.py`：遇到 M1 不适用的题时跳过变异部分，不报错。

**`import_exercism.py`**
- 解除 hello-world、reverse-string 的排除。
- 纯头文件练习：把 `example.h` 作为被测头文件，C++11 检查改为编译一个包含该头文件的编译单元。
- 把 meetup 的排除原因改为“依赖 Boost（R-01）”，把 list-ops 的排除原因改为“C++17”。

**新增 `import_step_b.py`**
- 导入第 4 节的非 Exercism 题。
- 去掉 `import_step_a.py` 中的三处硬编码：
  - 被替换文件路径；
  - fix.patch 的路径范围；
  - 可见文件后缀。

  泛化后，`import_step_a.py` 对 3 道旧题的重建仍要逐字节一致。

**手写变异**：在 `benchmark/tools/handwritten_variants/<题目 ID>/` 下编写，要求按 D018-4。

### B6 题目与校准样本

1. 按第 4 节导入新题。宿主机先用 g++-14 直接编译检查；本机的 `host_check.py` 因缺少 CMake 不可用，不作要求。
2. 新增 `evaluator/assessment/calibration/build_step_b_samples.py`，生成 CAL-21–28，规格见第 5 节。
3. 修改 `build_step_a_samples.py` 中 CAL-18–20 的阈值，见第 5.2 节。

## 4. 新题

### 4.1 题目清单

上游提交和 C++11 结论来自宿主机检查（Homebrew GCC 14 与 Apple clang，`-std=c++11 -pedantic-errors`），没有在 Docker 中运行过；变异数、覆盖率和缺陷能否复现都要以 Docker 标定为准。

| 优先级 | 题目 ID（建议） | 来源与提交 | 被测 | 替换版本 | 验证的能力 | 层级 |
|---|---|---|---|---|---|---|
| 必选 | `exercism-circular-buffer` | Exercism `7315f0f`，example.h（类模板，有效行 47） | 头文件 | 手写 ≥ 5 | R-06 纯头文件、冻结分母；CAL-22–24 | 入门 |
| 必选 | `exercism-hello-world` | 同上 | `hello_world.cpp`（零变异） | 手写 ≥ 3 | 零变异口径；CAL-25 | 入门 |
| 必选 | `yaml-cpp-node-impl` | BugsC++ yaml_cpp/4，修复提交 `33315286` | 头文件 `include/yaml-cpp/node/impl.h`；`src/*.cpp` 作依赖源文件 | 真实缺陷（替换 impl.h）+ 手写 ≥ 5 | R-07 替换公共头文件、R-06 加依赖源文件、M4；CAL-26/27 | 困难 |
| 必选 | `yaml-cpp-emitter-utils` | BugsC++ yaml_cpp/9，修复提交 `a6db7e32` | `src/emitterutils.cpp`（M1 适用） | 真实缺陷（替换不被测的 `src/exp.h`，该头文件被 6 个编译单元包含） | R-07 替换非被测头文件，与 M1 并存；CAL-28 | 困难 |
| 应选 | `exercism-binary-search-tree`、`exercism-linked-list` | Exercism `7315f0f` | 头文件（类模板；linked-list 的 `.cpp` 是空壳，不列入被测） | 手写 ≥ 5 | R-06 | 入门 |
| 应选 | `exercism-leap`、`exercism-two-fer` | 同上 | 头文件（inline 函数） | 手写 ≥ 3 | R-06 小题 | 入门 |
| 应选 | `exercism-reverse-string` | 同上 | `.cpp`（零变异） | 手写 ≥ 3 | 零变异 | 入门 |
| 应选 | `utfcpp-checked` | utfcpp v4.0.6 `b26a5f71` | `utf8/core.h`、`checked.h`、`unchecked.h`；`cpp11.h` 作可见依赖 | 手写 ≥ 5 | R-06 模板模块 | 中等 |
| 应选 | `nlohmann-json-to-chars` | nlohmann/json v3.11.3 `9cca280a` | `detail/conversions/to_chars.hpp`（1118 行，函数模板） | 手写 ≥ 5 | R-06 模板模块 | 困难 |
| 应选 | `cpp-peglib-parser` | BugsC++ cpp_peglib/5，修复提交 `2d276c8c` | 单头文件 `peglib.h` | 真实缺陷（替换 peglib.h）+ 手写 ≥ 5 | R-06 与 R-07 叠加的大头文件 | 困难 |

完成必选 4 题加应选 8 题后，题库共 115 题：入门 101、中等 9、困难 5，以实际导入为准。

### 4.2 出题注意

**通用要求**
- 源码按上游原样入库，不修改业务代码。真实缺陷版本由 BugsC++ 的 buggy.patch 作用在修复提交上得到，在 `hidden/README.md` 和上游证据中记录：
  - BugsC++ 的提交号；
  - patch 的哈希；
  - 回归用例名。
- 新的 yaml-cpp 快照是独立题目，不复用 `yaml-cpp-document`。
- 参考测试从上游测试机械转换：Exercism 用现有的 Catch2 转换，cpp-peglib 用 `catch_compat.h`，utfcpp 只需替换 include。
- 纯头文件题的冻结分母应包含公开 API 的全部模板成员；参考测试实例化不到的部分，用 `hidden/coverage_instantiation/` 补齐。没有进入分母的函数，在 `hidden/README.md` 中逐个写明原因。

**逐题要求**
- **nlohmann-json-to-chars**：上游测试如果依赖整库 `json.hpp`，可见文件随之扩大，但被测仍只有 `to_chars.hpp`。
- **cpp-peglib-parser**：在 C++11 下，peglib 用 `peg::any` 代替 `std::any`，必须在 Docker 中确认缺陷能复现，再纳入。

### 4.3 替换与淘汰规则

- 题目因自身质量达不到准入时，先补强参考测试、补手写变异或实例化文件；仍不行就按备选替换，并在验证说明中写明原因。原因包括：
  - Docker 中不能按 C++11 编译；
  - 缺陷不能确定性复现；
  - 冻结 C1 低于 0.8。
- 备选：
  - cpp-peglib：缺陷 /4（`be470f93`）、/10（`b92da07b`）；
  - 模板模块：rapidjson `internal/regex.h`（master `24b5e7a8`）、fmt 10.2.1 的 `args.h`。
  - rapidjson 测试自定义了 `RAPIDJSON_ASSERT`，函数式宏不能用 `build.defines` 表达，只作备选。
- 必选的 4 道不能替换。其中任何一道不能准入，就说明能力实现有问题，要先修实现。

## 5. 校准样本

### 5.1 新增样本（样本 ID 全局唯一，CAL-17 已并入其他样本，不再使用）

| 样本 | 题目 | 内容 | 期望（hard 和 relations） |
|---|---|---|---|
| CAL-21 | yaml-cpp-document | 参考测试去掉 `NodeTest.LoadNullWithStrTag`（`load_node_test.cc` 第 273–277 行），`reference_copy` 为 null | 全部 valid；`tagged-null` 为 not_detected；`variant_failed_tests == []`；M4 == 0；M1_e2e ≤ CAL-18；S1 == 0 |
| CAL-22 | exercism-circular-buffer | 参考测试原样复制 | scored；全部 valid；M1_e2e 和 M1_valid 断言为 `na`、原因 header_only；C2 断言为 `na`；C1、C3 等于冻结分母上的参考值；M2 == 1 |
| CAL-23 | exercism-circular-buffer | 只调用部分成员函数的测试，少实例化 | 全部 valid；C1 < CAL-22，并等于预先算好的精确值（分母取冻结集合，少实例化的部分不能抬高覆盖率）；M2 < 1；M1 断言为 `na` |
| CAL-24 | exercism-circular-buffer | 测试在被测代码上全部失败 | invalid；M1_e2e 断言为 `na`（不能是 0）；V2 == 0 |
| CAL-25 | exercism-hello-world | 参考测试原样复制 | scored，不能是 infra_error；M1 断言为 `na`、原因 zero_mutants；M2 == 1；C1 ≥ 0.8 |
| CAL-26 | yaml-cpp-node-impl | 参考测试原样复制 | scored；真实缺陷版本 detected，`variant_failed_tests` 为预先确定的回归用例；M4 == 1；M2 == 1；M1 断言为 `na` |
| CAL-27 | yaml-cpp-node-impl | 去掉检出真实缺陷的测试 | 真实缺陷版本 not_detected；M4 == 0；C1 ≤ CAL-26 |
| CAL-28 | yaml-cpp-emitter-utils | 参考测试原样复制 | scored；M1_e2e ≥ 0.8；替换 `exp.h` 的真实缺陷版本 detected；M4 == 1 |

### 5.2 收紧 CAL-18–20

取值来源：`runs/step-a-calibration-20261028-03`，两轮实测值完全相同。

| 样本 | 改为 |
|---|---|
| CAL-18 | M1_e2e == 1；C1 == 256/264；C2、C3 等于实测值；S1 == 0；V3 == 0；M4 == 1；`variant_failed_tests == [NodeTest.LoadNullWithStrTag]` |
| CAL-19 | M1_e2e == 1；C1 == 258/263；C2、C3 等于实测值；S1 == 0；V3 == 0 |
| CAL-20 | M1_e2e == 1；C1 == 370/383；C2、C3 等于实测值；S1 == 0；V3 == 0 |

这些相等断言用来证明，覆盖率重构没有改变旧题型的计算结果。之后如果需要调整，要写明理由、升版本并重新校准。

CAL-01–16 不改，作为 GildedRose 和旧替换版本 hw-01、eq-02 的回归断言。

## 6. Docker 执行顺序（Linux ARM64）

**通用规则**
- 每条命令都经 Audit 执行，保存命令、时间、退出码、stdout 和 stderr（步骤 A 曾漏记 4 个 run 的命令审计）。
- run-id 用 `step-b-<用途>-YYYYMMDD-NN`。失败保留，重试换新的 run-id。
- 正式 runner 必须在已提交的干净工作区上运行。

| 序号 | 步骤 | 命令或要点 | 通过标准 |
|---|---|---|---|
| 1 | 预检 | `docker image inspect docker.io/library/qualtor-gcc:14.2.0-gtest1.12.1-cxx11` 和 `docker.io/library/qualtor-clang:19.1.7-mull0.34.2-gtest1.12.1-cxx11` 的 ID | 分别等于 `bd01e6e4…`、`013ac35a…` |
| 2 | 校准题的种子分母 | `python3 -B evaluator/assessment/prepare_task.py baseline --task <题目> --write`，对 circular-buffer、hello-world、yaml-cpp-node-impl、yaml-cpp-emitter-utils 各执行一次 | 解开校准依赖；正式分母的实质内容要与之一致 |
| 3 | 完整校准 | `python3 -B evaluator/assessment/calibrate.py --jobs 2 --run-id step-b-calibration-YYYYMMDD-01` | 全部样本各两次 passed；状态版本为 0.4.0 |
| 4 | 正式标定 | `python3 -B benchmark/tools/prepare_new_tasks.py --tasks <新题…> --write --jobs 2 --run-id step-b-formal-YYYYMMDD-01` | 全部写入；M1 不适用的题有 `coverage_baseline.json`，或零变异证据 |
| 5 | 复核 | `mutant_report.py`，只有 yaml-cpp-emitter-utils 有等价候选；逐题核对手写变异和真实缺陷的检出 | 没有 pending |
| 6 | 签署 | `python3 -B benchmark/tools/admit.py --tasks <新题…> --by <复核人> --write` | 新题 admitted；旧 103 题仍 admitted，不需要重签 |
| 7 | 回归补评 | `python3 -B evaluator/assessment/evaluate.py --rescore step-a-runner-20261028-02`，结果写入原 run 的 `score/0.4.0/` | 6 份结果除版本、指纹字段外，指标、状态、变异和替换版本判定与 `score/0.3.0/` 完全一致 |
| 8 | 提交 | 提交实现与新题 | `git status` 干净 |
| 9 | 正式 runner | `python3 -B evaluator/run.py --config default --tasks exercism-circular-buffer exercism-hello-world yaml-cpp-node-impl yaml-cpp-emitter-utils <utfcpp-checked 或 nlohmann-json-to-chars> --trials 1 --run-id step-b-runner-YYYYMMDD-01` | completed；5 题都 finished，10 份结果都 scored；M1 不适用的题 `M1_e2e` 为 null 且原因正确；M4 和 M2 有值 |
| 10 | 收尾核对 | 编写 `final_checks.py`，生成 `final-checks.json` 和 `summary.md` | 第 9 节各项都有机器核对结果 |

## 7. 回归与兼容性检查

**本机即可完成（不需要 Docker）**
- 四组单元测试；
- 用 `admit.py` 核对，不加 `--write`；
- 用 `apply_review.py` 核对；
- `calibration_status` 重算为 passed；
- 两份契约文件哈希相同；
- 旧 103 题：`git diff 08204ac -- benchmark/<旧题>/` 为空，题目指纹与 `admission.json` 的登记一致，`mull_config_text` 和 TASK.md 都与 B0 金标准一致。

**需要 Docker**
- CAL-01–16、CAL-18–20 在 0.4.0 下仍然通过；
- 第 6 节第 7 步的补评结果与 0.3.0 一致；
- `import_step_a.py` 泛化后，对 3 道旧题的重建逐字节一致，执行时保留审计。

## 8. 文档同步

| 文档 | 内容 |
|---|---|
| [决策记录](决策记录.md) | D018；文件开头的现行口径说明加入 D018 |
| [评分算法](评分算法.md) | 第 4.3 节：M1 不适用记 ⊥（含 invalid）；被测头文件的 C1 和 C3 用冻结分母，C2 为 ⊥。第 5 节：“不适用”与“缺失”分别计数。第 6.1 节：M1 配对排除不适用的题 |
| [评测规格](评测规格.md) | 指标口径；第 6 节的实现状态；第 7 节删除已完成的遗留项，加入混合题等后续工作 |
| [评测模块与校准样本设计](评测模块与校准样本设计.md) | 题目包新增 `target_headers`、`coverage_baseline.json`、`coverage_instantiation/` 和手写变异来源；样本表加入 CAL-21–28，更新 CAL-18–20 |
| [题库构建方案](题库构建方案.md) | R-06、R-07 的状态；第 1.3、1.4 节的题数；第 5 节的新题与候选；第 7 节步骤 B 的状态；第 8 节 Q-01；附录 A 的模板 |
| [题库验证说明](题库验证说明.md) | 新增第 15 节，记录执行顺序、结果、证据表和未验证范围 |
| [评测运行说明](评测运行说明.md) | 新命令和行为：零变异、M1 不适用、回归补评 |
| [产品 README](../agents/README.md)、[接口与运行边界](接口与运行边界.md) | 公开任务字段、保留宏、纯头文件题的提示词 |
| [研发日志](研发日志.md) | 本轮过程、失败记录，以及“旧题生成行为不变”的说明 |
| [文档索引](README.md) | 更新相关行；本计划完成后标注为历史计划 |

## 9. 交付与验收

**交付时请提供：**
- 提交范围：先是 D018 的独立提交，然后是各阶段的提交；
- 本轮全部 run-id 清单；
- `summary.md`：每条结论都对应证据路径，失败与重试保留；
- `final-checks.json`；
- 未纳入题目的清单及原因。

**我会逐项验收：**

1. **代码审查**
   - D018 的每一条都有对应实现，没有超出范围的改动；
   - 两份契约逐字节相同；
   - 旧题的代码路径行为不变（覆盖率插桩范围、编译命令、Mull 配置）；
   - 评测侧没有导入产品的私有实现。
2. **本机复算**：第 7 节中本机能做的全部项目；另外独立复算：
   - 新题冻结分母的实质内容与题目指纹；
   - 手写变异的数量和要求；
   - 隐藏材料没有出现在可见文件中。
3. **校准证据**：全部样本两轮结果都是 0.4.0；代码指纹、样本指纹和题目指纹与校准状态一致；CAL-22–27 的 `na` 断言和 CAL-23 的冻结分母判定，都能在原始 `result.json` 中找到。
4. **标定与准入**：新题的分母、`coverage_baseline.json`、零变异证据、替换版本检出记录；`admission.json` 中旧题的记录不变。
5. **回归补评**：`score/0.4.0` 与 `score/0.3.0` 逐字段比对，结果一致。
6. **正式 runner**：
   - 启动审计的参数，以及运行时工作区是否干净；
   - 公开任务的投影（`target_headers` 存在、隐藏材料没有进入）；
   - 10 份结果的不适用口径；
   - 密钥扫描。
7. **文档**：第 8 节全部同步，链接有效；已实现、已验证、待实现区分清楚；不把 AI 复核写成人工审阅。

## 10. 风险与预案

| 风险 | 预案 |
|---|---|
| 函数键 `(start_line, start_column)` 在宏展开或 lambda 中冲突 | 冲突时改用 `(start_line, start_column, demangled base name)`，加单元测试，写进 D018 的实现说明 |
| 冻结分母依赖参考测试的实例化，漏掉部分模板 | 用实例化文件补齐；没进入分母的函数在 `hidden/README.md` 中逐个说明。补不齐的模块改用备选 |
| 给全部编译单元插桩后，覆盖率构建变慢，或依赖源文件较多的题内存不足 | 覆盖率阶段用 `--jobs 1` 重试；仍然失败就记录，并缩小依赖源文件的范围（只保留链接需要的文件） |
| 零变异判定把 Mull 故障误判为零变异 | 只在准备阶段判定，三个条件缺一不可，并保存原始输出；评分阶段对有变异的题维持 `infra_error` |
| cpp-peglib 的缺陷在 C++11 的 `peg::any` 路径下不能复现 | 换用 /4 或 /10；都不行就记录原因，作为后续候选 |
| Exercism 上游缓存（`/tmp/qualtor-dl-exercism`）被清理 | 按导入脚本重新下载 `7315f0f`，核对哈希后再导入 |
| 覆盖率重构意外改变旧题型的结果 | CAL-18–20 的精确断言和回归补评会暴露这个问题。必须找到原因并修复，不能为了通过而改阈值 |
