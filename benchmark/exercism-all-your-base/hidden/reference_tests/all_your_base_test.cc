// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "all_your_base.h"

namespace {

using namespace std;

// all-your-base exercise test case data version 2.3.0

TEST(AllYourBase, T001_single_bit_one_to_decimal) {
    vector<unsigned int> in_digits{1};
    vector<unsigned int> expected{1};
    vector<unsigned int> out_digits = all_your_base::convert(2, in_digits, 10);

    REQUIRE(expected == out_digits);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(AllYourBase, T002_binary_to_single_decimal) {
    vector<unsigned int> in_digits{1, 0, 1};
    vector<unsigned int> expected{5};
    vector<unsigned int> out_digits = all_your_base::convert(2, in_digits, 10);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T003_single_decimal_to_binary) {
    vector<unsigned int> in_digits{5};
    vector<unsigned int> expected{1, 0, 1};
    vector<unsigned int> out_digits = all_your_base::convert(10, in_digits, 2);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T004_binary_to_multiple_decimal) {
    vector<unsigned int> in_digits{1, 0, 1, 0, 1, 0};
    vector<unsigned int> expected{4, 2};
    vector<unsigned int> out_digits = all_your_base::convert(2, in_digits, 10);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T005_decimal_to_binary) {
    vector<unsigned int> in_digits{4, 2};
    vector<unsigned int> expected{1, 0, 1, 0, 1, 0};
    vector<unsigned int> out_digits = all_your_base::convert(10, in_digits, 2);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T006_trinary_to_hexadecimal) {
    vector<unsigned int> in_digits{1, 1, 2, 0};
    vector<unsigned int> expected{2, 10};
    vector<unsigned int> out_digits = all_your_base::convert(3, in_digits, 16);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T007_hexadecimal_to_trinary) {
    vector<unsigned int> in_digits{2, 10};
    vector<unsigned int> expected{1, 1, 2, 0};
    vector<unsigned int> out_digits = all_your_base::convert(16, in_digits, 3);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T008_fifteen_bit_integer) {
    vector<unsigned int> in_digits{3, 46, 60};
    vector<unsigned int> expected{6, 10, 45};
    vector<unsigned int> out_digits = all_your_base::convert(97, in_digits, 73);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T009_empty_list) {
    vector<unsigned int> in_digits{};
    vector<unsigned int> expected{};
    vector<unsigned int> out_digits = all_your_base::convert(2, in_digits, 10);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T010_single_zero) {
    vector<unsigned int> in_digits{0};
    vector<unsigned int> expected{};
    vector<unsigned int> out_digits = all_your_base::convert(10, in_digits, 2);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T011_multiple_zeros) {
    vector<unsigned int> in_digits{0, 0, 0};
    vector<unsigned int> expected{};
    vector<unsigned int> out_digits = all_your_base::convert(10, in_digits, 2);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T012_leading_zeros) {
    vector<unsigned int> in_digits{0, 6, 0};
    vector<unsigned int> expected{4, 2};
    vector<unsigned int> out_digits = all_your_base::convert(7, in_digits, 10);

    REQUIRE(expected == out_digits);
}

TEST(AllYourBase, T013_first_base_is_one) {
    vector<unsigned int> in_digits{};

    REQUIRE_THROWS_AS(all_your_base::convert(1, in_digits, 10),
                      std::invalid_argument);
}

TEST(AllYourBase, T014_first_base_is_zero) {
    vector<unsigned int> in_digits{};

    REQUIRE_THROWS_AS(all_your_base::convert(0, in_digits, 10),
                      std::invalid_argument);
}

TEST(AllYourBase, T015_invalid_positive_digit) {
    vector<unsigned int> in_digits{1, 2, 1, 0, 1, 0};

    REQUIRE_THROWS_AS(all_your_base::convert(2, in_digits, 10),
                      std::invalid_argument);
}

TEST(AllYourBase, T016_second_base_is_one) {
    vector<unsigned int> in_digits{1, 0, 1, 0, 1, 0};

    REQUIRE_THROWS_AS(all_your_base::convert(2, in_digits, 1),
                      std::invalid_argument);
}

TEST(AllYourBase, T017_second_base_is_zero) {
    vector<unsigned int> in_digits{7};

    REQUIRE_THROWS_AS(all_your_base::convert(10, in_digits, 0),
                      std::invalid_argument);
}

#endif

}  // namespace
