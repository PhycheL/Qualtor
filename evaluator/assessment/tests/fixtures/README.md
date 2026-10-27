# 评分器单元测试的固定数据

| 文件 | 来源 |
|---|---|
| `mull_elements_cxx11_final.json` | 工具链验收轮次 `cxx11-final-20261023` 在 Clang 镜像中由 Mull 0.34.2 生成的 Elements 报告 |
| `gcov_gildedrose_cxx11_final.gcov.json.gz`、`gcov_gildedrose_cxx11_final.gcov` | 同一轮次在 GCC 镜像中由 gcov 14.2.0 生成的 JSON 与文本输出 |
| `gcov_tennis4_dtor_variants.gcov.json.gz`、`gcov_tennis4_dtor_variants.gcov` | 2026-10-27 题库标定 `bank-prepare-20261027-01-tennis-refactoring-4` 中参考测试第 1 轮的 gcov 14.2.0 JSON 与文本输出；第 26 行的虚析构函数有 D0、D2 两个符号，用于核对按行合并 |
| `gtest_1_12_1_list.json`、`gtest_1_12_1_run.json`、`gtest_1_12_1_run.stdout` | 2026-10-24 在宿主机用 GoogleTest 1.12.1（官方源码包，SHA-256 与 Dockerfile 一致）运行 `gtest_1_12_1_semantics.cc` 的实际输出，用于确认列表、跳过、禁用和失败的字段取值 |

这些文件只用于解析逻辑的单元测试，不是评分结果。
