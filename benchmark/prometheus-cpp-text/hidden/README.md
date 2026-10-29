# prometheus-cpp 文本与指标

业务源码原样入库。metrics.proto 来自本提交固定的 prometheus/client_model 子模块
fa8ad6fec33561be4280a8f0514318c79d7f6cb6，保留该子模块许可证。
counter、gauge、histogram 使用原 GoogleTest；文本序列化的隐藏边界测试覆盖所有指标类型及标签转义。
不导入网络 exposer 或 civetweb；不需要额外网络或库。

复核补充测试：`review_tests.cc` 来自 `benchmark/tools/mutant_review/prometheus-cpp-text/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
