# 题库建设工具

这里的脚本用于生成、检查和批量标定 `benchmark/` 下的题目，不属于评测模块，修改它们不会让校准失效。各工具的作用与流程见 [题库构建方案](../../docs/题库构建方案.md)第 6 节，验证与重建命令见 [题库验证说明](../../docs/题库验证说明.md)。

| 文件 | 作用 |
|---|---|
| `bankutil.py` | 公共函数：哈希、题目包骨架、写 `task.json` 与 `SOURCE.json`，并入复核补充测试、移回已确认的不等价变异 |
| `import_humaneval_x.py` | HumanEval-X C++ → `humaneval-x-cpp-NN`（含探针生成与 GCC 回放） |
| `import_exercism.py`、`catch_compat.h` | Exercism C++ → `exercism-<练习名>`（Catch2 测试转换为 GoogleTest） |
| `build_katas.py`、`kata_tests/`、`kata_generators/` | Emily Bache 的 kata → 15 道题；手写参考测试与探针生成器放在子目录 |
| `import_step_a.py`、`step_a/` | 从固定上游提交导入 yaml-cpp、md4c、TinyExpr；保存测试转换与 md4c 实际输出 |
| `capture_md4c_outputs.py` | 在固定 GCC Docker 捕获上游 770 个输入的实际 HTML，按 D001 冻结逐字节断言 |
| `verify_step_a_build.py` | 混合 C/C++ 构建、三类单元宏/选项、失败后修复和 support 排除的 Docker 剧本验收 |
| `fetch_step_c.py`、`import_step_c.py`、`step_c/` | 步骤 C：下载并校验固定上游归档；导入 Qt、protobuf、zlib 与 BugsC++ 题。外部命令经 `evaluator/common/audit.py` 记录到 `runs/<run-id>/evidence/host`（D021-3）；`--verify` 把题目重建到临时目录并与 `benchmark/<题目>` 逐字节比较，不写入题库 |
| `pregenerate.py` | 在环境 GCC 镜像中两轮生成预生成配置头并登记 `SOURCE.json` 的 `generated`；重跑时替换同一输出的旧记录，`--check` 只核对、不写入 |
| `bank_facts.py` | 只读：从 `task.json`、分母、准入、配方与校准记录生成题库事实（层级、能力题数、新题分母、CAL-30–35、签署人），供文档引用；`python3 -I -B benchmark/tools/bank_facts.py [--format json]` |
| `probe_prelude.h` | 探针生成器公共部分：随机输入、C++ 字面值、子进程隔离执行 |
| `host_check.py` | 宿主机检查：本机编译器跑参考测试、探针与替换版本，不含覆盖率与 Mull |
| `prepare_new_tasks.py` | Docker 机器上批量标定变异分母并汇总；写入前落实 `mutant_review/` 的复核结论 |
| `mutant_report.py` | 为人工复核逐题列出等价候选、不稳定、探针超时、参考测试缺口，以及已移回分母的确认项 |
| `mutant_review/` | 变异复核结论：`review_tests.cc` 为复核补充测试，建题时并入参考测试与探针；`confirmed.json` 为影响分母的结论；`equivalent.json` 为等价候选的结论（见该目录的 README） |
| `apply_review.py` | 把 `confirmed.json` 的结论落到已有分母上，或核对是否都已落实；只读写 JSON，不需要 Docker |
| `admit.py` | 准入（R-08，D016）：核对准入条件，由复核人签署分母并登记到 `benchmark/admission.json`；只读写 JSON |
| `mutant_ir.py` | 在固定 Clang/Mull 镜像中导出带变异的 IR，列出各变异生效副本删改的调用；`analyze` 可离线分析已导出的 IR |
| `ub_sweep.py`、`ub_drivers/` | 在固定 GCC 镜像中用 libstdc++ 断言加 ASan/UBSan 复核变异的源码副本；`ub_drivers/` 放各题的驱动程序 |
| `tests/` | 题库工具的单元测试 |

命令审计（D021-3）：`import_step_c.py`、`pregenerate.py`、`fetch_step_c.py`、`prepare_new_tasks.py` 经 `evaluator/common/audit.py` 执行外部命令。`bankutil.run_command` 只在设置了 `bankutil.COMMAND_AUDIT` 时经 Audit，否则直接调用 `subprocess`。`import_step_a.py`、`import_step_b.py`、`import_exercism.py`、`import_humaneval_x.py`、`build_katas.py` 尚未接入，仍直接调用 `subprocess`；由它们生成的题没有审计下的重建证据。

`apply_review.py` 遇到缺失分母也返回失败（退出码 1），不能把未标定的题当作核对通过。对应回归检查：`python3 -B -m unittest discover -s benchmark/tools/tests -p 'test_*.py'`。

`kata_tests/`、`mutant_review/` 与生成器源码中的测试是隐藏材料，只供出题使用，不能放进任何题目的可见文件。

重建题目时（`--force`），材料与原来完全相同的题会保留已有的 `mutation_baseline.json`；材料变化的题分母作废，需重新标定。

复核结论可以带 `pending` 字段，表示还缺证据，`admit.py` 视为未就绪。`mutant_ir.py` 和 `ub_sweep.py` 的 `--resolve` 只在固定工具链的结果与结论一致时清除 pending，并追加证据路径。

此前 0.2.1 的 2026-10-28 Docker 取证：三项 IR 各只删一次析构、无新增调用；第 09/11 组实际删除空 `std::__new_allocator<int>` 析构，已更正原 vector 析构说明。Zebra 为 33 项输出相同、19 项 UB。55 项 pending 已清除并追加证据，100 道题已由 Codex（AI 复核，Linux ARM64）签署；总报告 `runs/eval-bank-021-20261028-01/summary.md`，历史结果见题库验证说明第 13 节；步骤 A 当前结果见第 14 节。


步骤 A 的导入与验证顺序（D017）：

1. 在独立工作区重建，保留原题目和 runs。`import_step_a.py` 拒绝覆盖已存在的三个目标目录。`--upstream` 目录下放 `yaml-cpp/`、`md4c/`、`tinyexpr/` Git checkout；前两者由脚本固定提交，TinyExpr checkout 固定为 `ba2e32bbcc2d1e644a7e132d24c2f542821cabe0`。许可证与源码原文一并导入。
2. 执行 `python3 benchmark/tools/import_step_a.py --upstream <上游目录>`。`step_a/md4c_actual.json` 是固定 GCC 对上游 770 输入的实际结果，附提交号与原始证据；改变源码或选项时先用 `capture_md4c_outputs.py --run-id <新编号>` 重新捕获，并审核差异，不直接沿用旧输出。
3. 用 `prepare_new_tasks.py --tasks yaml-cpp-document md4c-html tinyexpr-configured --run-id <种子编号> --write` 建立种子分母，补反例、等价和 D015 证据。`mutant_review/<task>/step_a_boundaries.cc` 等补充测试由 bankutil 自动并入参考和探针，反例驱动放子目录以免被自动编入参考。
4. 运行 `python3 evaluator/assessment/calibration/build_step_a_samples.py` 生成 CAL-18–20 的完整参考副本，再按[评测运行说明](../../docs/评测运行说明.md)完整校准。运行 `verify_step_a_build.py --run-id <新编号>` 验证三类单元与失败后修复。
5. 使用新 run-id 正式标定（已有分母加 `--force`），再执行 mutant_report、apply_review 核对和 admit 签署。任何新校准题材料或分母实质内容变化都需重新完整校准；仅 review 元数据变化不影响指纹。

2026-10-28 的重建检查 `runs/step-a-import-replay-20261028-02/summary.json`：三题全部非分母文件逐字节一致。0.3.0 完整校准、19 题正式标定、103 题准入及真实生成证据见[题库验证说明](../../docs/题库验证说明.md)第 14 节。
