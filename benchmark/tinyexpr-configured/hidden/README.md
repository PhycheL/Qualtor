# TinyExpr 宏配置

源码取 `ba2e32bbcc2d1e644a7e132d24c2f542821cabe0`，未改原始业务代码。C11 编译启用 `TE_POW_FROM_RIGHT` 和 `TE_NAT_LOG`，宏同时传给 C++11 测试。
`smoke.c` 的 minctest 断言转换为 GoogleTest；浮点容差沿用 0.001。仅为 C++ 编译显式转换函数指针、void*、malloc 结果及大整数到 double 的聚合初始化，移除原 main；lfails 映射到当前 GoogleTest 的断言结果数量。
locale 测试依赖外部 locale 安装状态，未注册；其余上游测试输入保留。测试与源码许可证均保留原文。
探针为参考测试副本；参考测试未人工审阅；等价候选逐项复核。

复核补充测试：`step_a_boundaries.cc` 来自 `benchmark/tools/mutant_review/tinyexpr-configured/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
