// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
// Include the header file with the definitions of the functions you create.
#include "hello_world.h"

namespace {

// Include the test framework.

// Declares a single test.
TEST(HelloWorld, T001_test_hello) {
    // Check if your function returns "Hello, World!".
    REQUIRE(hello_world::hello() == "Hello, World!");
}

}  // namespace
