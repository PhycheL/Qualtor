# yatzy-refactoring 隐藏材料

- 被测代码：emilybache/Yatzy-Refactoring-Kata 提交 `8a2ad924e5154a36423e72c2573cfe3129cf4fd8`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- 参考测试：`sample_gtest.cpp` 为上游 15 个用例；`characterization_tests.cc` 为每 97 种组合取 1 种的全部计分结果。
- 探针：`probe_tests.cc` 穷举全部 7776 种组合，由 `equivalence_probe/generate_probe.cc` 生成。
- 探针：探针由生成器在原代码上运行大量输入得到，并包含全部参考测试；探针也区分不出的变异列为等价候选。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
