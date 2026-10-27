// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "collatz_conjecture.h"
#include <stdexcept>

namespace {

TEST(CollatzConjecture, T001_zero_steps_for_one) { REQUIRE(0 == collatz_conjecture::steps(1)); }

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(CollatzConjecture, T002_divide_if_even) { REQUIRE(4 == collatz_conjecture::steps(16)); }

TEST(CollatzConjecture, T003_even_and_odd_steps) { REQUIRE(9 == collatz_conjecture::steps(12)); }

TEST(CollatzConjecture, T004_large_number_of_even_and_odd_steps) {
    REQUIRE(152 == collatz_conjecture::steps(1000000));
}

TEST(CollatzConjecture, T005_zero_is_an_error) {
    REQUIRE_THROWS_AS(collatz_conjecture::steps(0), std::domain_error);
}

TEST(CollatzConjecture, T006_negative_value_is_an_error) {
    REQUIRE_THROWS_AS(collatz_conjecture::steps(-15), std::domain_error);
}
#endif

}  // namespace
