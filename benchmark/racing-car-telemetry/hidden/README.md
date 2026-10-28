# racing-car-telemetry 隐藏材料

- 被测代码：emilybache/Racing-Car-Katas 提交 `6584af9b6d9bd3d8105b8c8ad4fc544d3c09fed6`；文件对应关系见 `source/SOURCE.json` 的 `upstream_paths`。
- 参考测试：`kata_tests/racing-car-telemetry/` 下手写，断言为原代码的实际运行结果。
- 连接结果与随机报文取决于标准库的分布实现，参考测试只断言与实现无关的部分。
- 复核补充测试：`review_tests.cc` 来自 `benchmark/tools/mutant_review/racing-car-telemetry/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
- 探针：探针即参考测试的副本：等价候选就是参考测试未杀死的变异，变异分母为参考测试可检出的变异，人工复核时把不等价的变异移回分母。
- 重建：重新运行 `benchmark/tools/build_katas.py --force`；修改参考测试后要重新标定变异分母。
