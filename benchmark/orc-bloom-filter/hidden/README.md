# ORC BloomFilter

源码与 .proto 原样入库；Adaptor.hh 和 orc-config.hh 由上游特性检测片段在锁定 GCC 环境中生成，
两轮字节一致；完整命令、工具版本及输入/输出哈希见 source/SOURCE.json.generated。
参考测试来自 TestBloomFilter.cc；将 GoogleTest 包装头替换为标准头并移除未使用的 OrcFile.hh，
在上游已声明的 friend 测试中补充小整数哈希反例，避免依靠 signed hash 溢出区分变异。
Murmur3.cc 仅作依赖单元；生成的 orc_proto.pb.cc 不参与覆盖率和变异。原代码的 signed hash 运算
及大端不可达分支须按 D015 逐项复核，不能仅凭参考测试未检出认定等价。

复核补充测试：`review_tests.cc` 来自 `benchmark/tools/mutant_review/orc-bloom-filter/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
