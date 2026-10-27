# 题库建设工具

这里的脚本用于生成、检查和批量标定 `benchmark/` 下的题目，不属于评测模块，修改它们不会让校准失效。各工具的作用与流程见 [题库构建方案](../../docs/题库构建方案.md)第 6 节，验证与重建命令见 [题库验证说明](../../docs/题库验证说明.md)。

| 文件 | 作用 |
|---|---|
| `bankutil.py` | 公共函数：哈希、题目包骨架、写 `task.json` 与 `SOURCE.json` |
| `import_humaneval_x.py` | HumanEval-X C++ → `humaneval-x-cpp-NN`（含探针生成与 GCC 回放） |
| `import_exercism.py`、`catch_compat.h` | Exercism C++ → `exercism-<练习名>`（Catch2 测试转换为 GoogleTest） |
| `build_katas.py`、`kata_tests/`、`kata_generators/` | Emily Bache 的 kata → 15 道题；手写参考测试与探针生成器放在子目录 |
| `probe_prelude.h` | 探针生成器公共部分：随机输入、C++ 字面值、子进程隔离执行 |
| `host_check.py` | 宿主机检查：本机编译器跑参考测试、探针与替换版本，不含覆盖率与 Mull |
| `prepare_new_tasks.py` | Docker 机器上批量标定变异分母并汇总 |
| `mutant_report.py` | 为人工复核逐题列出等价候选、不稳定、探针超时与参考测试缺口 |

`kata_tests/` 与生成器源码中的测试是隐藏材料，只供出题使用，不能放进任何题目的可见文件。

重建题目时（`--force`），材料与原来完全相同的题会保留已有的 `mutation_baseline.json`；材料变化的题分母作废，需重新标定。
