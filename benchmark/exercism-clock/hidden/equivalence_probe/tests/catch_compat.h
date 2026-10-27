// Catch2 断言到 GoogleTest 的最小兼容层，随转换后的 Exercism 参考测试一起放在隐藏目录。
// 只覆盖 Exercism C++ 测试实际用到的写法；TEST_CASE 由 benchmark/tools/import_exercism.py 改写为 TEST。
// Catch2 的 REQUIRE 失败即中止本测试，这里统一映射为 EXPECT_*：失败照样判为测试失败，杀死变异的效果相同。
#pragma once

#include <gtest/gtest.h>

#include <cmath>

#define REQUIRE(...) EXPECT_TRUE((__VA_ARGS__))
#define CHECK(...) EXPECT_TRUE((__VA_ARGS__))
#define REQUIRE_FALSE(...) EXPECT_FALSE((__VA_ARGS__))
#define CHECK_FALSE(...) EXPECT_FALSE((__VA_ARGS__))
#define REQUIRE_THROWS_AS(expr, type) EXPECT_THROW((void)(expr), type)
#define CHECK_THROWS_AS(expr, type) EXPECT_THROW((void)(expr), type)
#define REQUIRE_THROWS(...) EXPECT_ANY_THROW((void)(__VA_ARGS__))
#define CHECK_THROWS(...) EXPECT_ANY_THROW((void)(__VA_ARGS__))
#define REQUIRE_NOTHROW(...) EXPECT_NO_THROW((void)(__VA_ARGS__))
#define CHECK_NOTHROW(...) EXPECT_NO_THROW((void)(__VA_ARGS__))
#define INFO(...) ((void)0)
#define SECTION(...) if (true)
#define CATCH_REGISTER_ENUM(...)

namespace Catch {
namespace Matchers {
struct WithinAbsMatcher {
    double target;
    double margin;
};
inline WithinAbsMatcher WithinAbs(double target, double margin) {
    WithinAbsMatcher matcher = {target, margin};
    return matcher;
}
}  // namespace Matchers
}  // namespace Catch

inline bool catch_compat_match(double value, const Catch::Matchers::WithinAbsMatcher& matcher) {
    return std::fabs(value - matcher.target) <= matcher.margin;
}

#define REQUIRE_THAT(arg, matcher) EXPECT_TRUE(catch_compat_match((arg), (matcher)))
#define CHECK_THAT(arg, matcher) EXPECT_TRUE(catch_compat_match((arg), (matcher)))
