# theatrical-players-statement 隐藏材料

- 被测代码：emilybache/Theatrical-Players-Refactoring-Kata 提交 `d76f8d4968f1bceff2a0bac17ba27759894bebf4`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- 参考测试：`kata_tests/theatrical-players-statement/` 下手写，断言为原代码的实际运行结果。
- `third_party/json.hpp` 是 header-only 第三方库，随源码入库并对 Agent 可见；不链接任何库。
- 探针：探针即参考测试的副本：等价候选就是参考测试未杀死的变异，变异分母为参考测试可检出的变异，人工复核时把不等价的变异移回分母。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
