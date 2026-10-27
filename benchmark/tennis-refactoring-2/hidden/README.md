# tennis-refactoring-2 隐藏材料

- 被测代码：emilybache/Tennis-Refactoring-Kata 提交 `a8ecc946929084eb4fe187ce2fcf3716dcb88f96`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- `src/tennis.h` 由 Qualtor 添加，只声明上游已有的 `tennis_score`。
- 参考测试：`upstream_tennis_tests.cc` 为上游 33 个用例；`characterization_tests.cc` 为生成器记录的前 12 个组合。
- 探针：探针由生成器在原代码上运行大量输入得到，并包含全部参考测试；探针也区分不出的变异列为等价候选。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
