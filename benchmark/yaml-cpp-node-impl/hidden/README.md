# yaml-cpp-node-impl 隐藏材料

业务源码逐字节取自 yaml-cpp `33315286abb27c04a5fc5322b828153f6aaf70eb`；独立快照，保留原始许可证与构建配置。
被测文件 `include/yaml-cpp/node/impl.h`，其余 src/*.cpp 作依赖。覆盖率构建给全部单元插桩，统计只限被测头文件；准备阶段冻结 coverage_baseline.json。
参考测试为上游 GoogleTest；扩展名改为 .cc，去除上游已禁用的测试，沿用步骤 A 的 throw_on_failure 设置。
真实缺陷来自 BugsC++ yaml_cpp/4 的 buggy.patch；提交、patch 哈希和回归用例记录在 upstream_evidence.json。
预期回归用例：NodeTest.LoadTildeAsNull。实际检出名单以 Docker 标定为准。
手写变异来自 benchmark/tools/handwritten_variants/yaml-cpp-node-impl/；均需编译成功并由断言失败检出。
参考测试未经过人工审阅。冻结范围说明见 coverage_notes.md。
