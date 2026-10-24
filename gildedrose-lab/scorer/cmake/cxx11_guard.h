#pragma once
// 评分构建强制使用 ISO C++11；由评分器通过 -include 注入每个编译单元。
static_assert(__cplusplus == 201103L, "Qualtor scoring builds must use ISO C++11");
