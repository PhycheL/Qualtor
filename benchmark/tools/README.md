# 题库建设工具

这里的脚本用于生成、检查和批量标定 `benchmark/` 下的题目，不属于评测模块，修改它们不会让校准失效。各工具的作用与流程见 [题库构建方案](../../docs/题库构建方案.md)第 6 节，验证与重建命令见 [题库验证说明](../../docs/题库验证说明.md)。

| 文件 | 作用 |
|---|---|
| `bankutil.py` | 公共函数：哈希、题目包骨架、写 `task.json` 与 `SOURCE.json`，并入复核补充测试、移回已确认的不等价变异 |
| `import_humaneval_x.py` | HumanEval-X C++ → `humaneval-x-cpp-NN`（含探针生成与 GCC 回放） |
| `import_exercism.py`、`catch_compat.h` | Exercism C++ → `exercism-<练习名>`（Catch2 测试转换为 GoogleTest） |
| `build_katas.py`、`kata_tests/`、`kata_generators/` | Emily Bache 的 kata → 15 道题；手写参考测试与探针生成器放在子目录 |
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

`apply_review.py` 遇到缺失分母也返回失败（退出码 1），不能把未标定的题当作核对通过。对应回归检查：`python3 -B -m unittest discover -s benchmark/tools/tests -p 'test_*.py'`。

`kata_tests/`、`mutant_review/` 与生成器源码中的测试是隐藏材料，只供出题使用，不能放进任何题目的可见文件。

重建题目时（`--force`），材料与原来完全相同的题会保留已有的 `mutation_baseline.json`；材料变化的题分母作废，需重新标定。

复核结论可以带 `pending` 字段，表示还缺证据，`admit.py` 视为未就绪。`mutant_ir.py` 和 `ub_sweep.py` 的 `--resolve` 只在固定工具链的结果与结论一致时清除 pending，并追加证据路径。

2026-10-28 Docker 取证已完成：三项 IR 各只删一次析构、无新增调用；第 09/11 组实际删除空 `std::__new_allocator<int>` 析构，已更正原 vector 析构说明。Zebra 为 33 项输出相同、19 项 UB。55 项 pending 已清除并追加证据，100 道题已由 Codex（AI 复核，Linux ARM64）签署；总报告 `runs/eval-bank-021-20261028-01/summary.md`，当前结果见题库验证说明第 13 节。
