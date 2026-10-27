# parrot-refactoring 隐藏材料

- 被测代码：emilybache/Parrot-Refactoring-Kata 提交 `28fe97beb296acd28fe5febdccca34def62e8616`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- 参考测试：`parrot_tests.cc` 改写自上游；`characterization_tests.cc` 为生成器记录的前 12 个输入。
- 探针：探针由生成器在原代码上运行大量输入得到，并包含全部参考测试；探针也区分不出的变异列为等价候选。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
