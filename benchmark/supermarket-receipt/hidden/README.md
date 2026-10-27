# supermarket-receipt 隐藏材料

- 被测代码：emilybache/SupermarketReceipt-Refactoring-Kata 提交 `c72d68abd77a417f84193b72a3b8d14177336066`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- 参考测试：`kata_tests/supermarket-receipt/` 下手写，断言为原代码的实际运行结果。
- `ReceiptPrinter` 的逻辑写在头文件里，当前流水线不会对它做变异（R-06），测试照常覆盖。
- 探针：探针即参考测试的副本：等价候选就是参考测试未杀死的变异，变异分母为参考测试可检出的变异，人工复核时把不等价的变异移回分母。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
