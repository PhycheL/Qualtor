# yaml-cpp-emitter-utils 隐藏材料

业务源码逐字节取自 yaml-cpp `a6db7e32ac506d536596d31bdb2b365de1cf35a2`；独立快照，保留原始许可证与构建配置。
被测文件 `src/emitterutils.cpp`，其余 src/*.cpp 作依赖；头文件题的覆盖率构建给全部单元插桩，统计只限被测头文件。
参考测试为上游 GoogleTest；扩展名改为 .cc，去除上游已禁用的测试，沿用步骤 A 的 throw_on_failure 设置。
真实缺陷来自 BugsC++ yaml_cpp/9 的 buggy.patch；提交、patch 哈希和回归用例记录在 upstream_evidence.json。
预期回归用例：EmitterTest.UserType2。实际检出名单以 Docker 标定为准。
手写变异来自 benchmark/tools/handwritten_variants/yaml-cpp-emitter-utils/；均需编译成功并由断言失败检出。
参考测试未经过人工审阅。准备阶段冻结 coverage_baseline.json；未进入分母的 API 说明见 coverage_notes.md（若有）。

复核补充测试：`step_b_boundaries.cc` 来自 `benchmark/tools/mutant_review/yaml-cpp-emitter-utils/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
