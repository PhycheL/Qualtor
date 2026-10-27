# exercism-rail-fence-cipher 隐藏材料

- 被测代码：Exercism C++ 练习 `rail-fence-cipher` 的参考解（`.meta/example.*`），提交 `7315f0f38a47a6b4d3fe5a44a04b96c2a1805124`。
- 参考测试：上游 `rail_fence_cipher_test.cpp` 由 `benchmark/tools/import_exercism.py` 机械转换为 GoogleTest，共 6 个用例；`catch_compat.h` 把 Catch2 断言映射为 GoogleTest。
- 探针：参考测试副本（探针即参考测试的副本：等价候选就是参考测试未杀死的变异，变异分母为参考测试可检出的变异，人工复核时把不等价的变异移回分母。）
- 重建：重新运行导入脚本并加 `--force`；修改参考测试后要重新标定变异分母。
