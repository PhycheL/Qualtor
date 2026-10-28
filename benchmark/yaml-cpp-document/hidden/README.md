# yaml-cpp 文档解析

源码与上游 GoogleTest 测试取自 `5a9ab177bad9665ac5eb8f5b12435052123b5b6f`，保留原许可证。测试扩展名 `.cpp` 改为 `.cc`，无断言改写；8 个上游已禁用的规格用例不注册。参考测试启用 GoogleTest throw_on_failure，防止变异死循环积累 StrictMock 失败报告耗尽容器内存；原程序不触发。
被测文件为 `src/singledocparser.cpp`，其余 `src/*.cpp` 仅作依赖编译，不参与覆盖与变异。

真实缺陷来源：BugsC++ `yaml_cpp/3`；[修复提交](https://github.com/jbeder/yaml-cpp/commit/5a9ab177bad9665ac5eb8f5b12435052123b5b6f)。
替换版本直接取修复父提交 `72fe73a1043bef4a4f9e7032132f2aa50865d97e` 的该 `.cpp`，没有套用合成补丁；业务 diff 只改此源文件，保存为 `fix.patch`。
回归用例 `NodeTest.LoadNullWithStrTag` 验证显式字符串标签下的 null 保持字符串。修复前行为不符合该断言，计入 M4。
参考测试与探针相同，未检出项必须逐项复核；参考测试尚未人工审阅。

复核补充测试：`step_a_boundaries.cc` 来自 `benchmark/tools/mutant_review/yaml-cpp-document/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
