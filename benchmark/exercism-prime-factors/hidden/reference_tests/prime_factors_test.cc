// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "prime_factors.h"

namespace {

TEST(PrimeFactors, T001_no_factors) {
    const std::vector<long long> expected{};

    const std::vector<long long> actual{prime_factors::of(1)};

    REQUIRE(expected == actual);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(PrimeFactors, T002_prime_number) {
    const std::vector<long long> expected{2};

    const std::vector<long long> actual{prime_factors::of(2)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T003_another_prime_number) {
    const std::vector<long long> expected{3};

    const std::vector<long long> actual{prime_factors::of(3)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T004_square_of_a_prime) {
    const std::vector<long long> expected{3, 3};

    const std::vector<long long> actual{prime_factors::of(9)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T005_product_of_first_prime) {
    const std::vector<long long> expected{2, 2};

    const std::vector<long long> actual{prime_factors::of(4)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T006_cube_of_a_prime) {
    const std::vector<long long> expected{2, 2, 2};

    const std::vector<long long> actual{prime_factors::of(8)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T007_product_of_second_prime) {
    const std::vector<long long> expected{3, 3, 3};

    const std::vector<long long> actual{prime_factors::of(27)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T008_product_of_third_prime) {
    const std::vector<long long> expected{5, 5, 5, 5};

    const std::vector<long long> actual{prime_factors::of(625)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T009_product_of_first_and_second_prime) {
    const std::vector<long long> expected{2, 3};

    const std::vector<long long> actual{prime_factors::of(6)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T010_product_of_primes_and_non_primes) {
    const std::vector<long long> expected{2, 2, 3};

    const std::vector<long long> actual{prime_factors::of(12)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T011_product_of_primes) {
    const std::vector<long long> expected{5, 17, 23, 461};

    const std::vector<long long> actual{prime_factors::of(901255)};

    REQUIRE(expected == actual);
}

TEST(PrimeFactors, T012_factors_include_a_large_prime) {
    const std::vector<long long> expected{11, 9539, 894119};

    const std::vector<long long> actual{prime_factors::of(93819012551)};

    REQUIRE(expected == actual);
}

#endif

}  // namespace
