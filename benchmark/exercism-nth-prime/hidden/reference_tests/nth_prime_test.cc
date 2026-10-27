// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "nth_prime.h"
#include <stdexcept>

namespace {

TEST(NthPrime, T001_first) { REQUIRE(2 == nth_prime::nth(1)); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(NthPrime, T002_second) { REQUIRE(3 == nth_prime::nth(2)); }

TEST(NthPrime, T003_sixth) { REQUIRE(13 == nth_prime::nth(6)); }

TEST(NthPrime, T004_big_prime) { REQUIRE(104743 == nth_prime::nth(10001)); }

TEST(NthPrime, T005_weird_case) {
    REQUIRE_THROWS_AS(nth_prime::nth(0), std::domain_error);
}
#endif

}  // namespace
