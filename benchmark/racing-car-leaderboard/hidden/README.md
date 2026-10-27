# racing-car-leaderboard 隐藏材料

- 被测代码：emilybache/Racing-Car-Katas 提交 `6584af9b6d9bd3d8105b8c8ad4fc544d3c09fed6`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- 参考测试：`kata_tests/racing-car-leaderboard/` 下手写，断言为原代码的实际运行结果。
- 比赛按值保存 Driver，自动驾驶车被切片，显示名为算法版本号；参考测试按这一实际行为断言。
- 探针：探针即参考测试的副本：等价候选就是参考测试未杀死的变异，变异分母为参考测试可检出的变异，人工复核时把不等价的变异移回分母。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
