// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "largest_series_product.h"

namespace {

TEST(LargestSeriesProduct, T001_finds_the_largest_product_if_span_equals_length) {
    REQUIRE(largest_series_product::largest_product("29", 2) == 18);
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(LargestSeriesProduct, T002_can_find_the_largest_product_of_2_with_numbers_in_order) {
    REQUIRE(largest_series_product::largest_product("0123456789", 2) == 72);
}

TEST(LargestSeriesProduct, T003_can_find_the_largest_product_of_2) {
    REQUIRE(largest_series_product::largest_product("576802143", 2) == 48);
}

TEST(LargestSeriesProduct, T004_can_find_the_largest_product_of_3_with_numbers_in_order) {
    REQUIRE(largest_series_product::largest_product("0123456789", 3) == 504);
}

TEST(LargestSeriesProduct, T005_can_find_the_largest_product_of_3) {
    REQUIRE(largest_series_product::largest_product("1027839564", 3) == 270);
}

TEST(LargestSeriesProduct, T006_can_find_the_largest_product_of_5_with_numbers_in_order) {
    REQUIRE(largest_series_product::largest_product("0123456789", 5) == 15120);
}

TEST(LargestSeriesProduct, T007_can_get_the_largest_product_of_a_big_number) {
    REQUIRE(largest_series_product::largest_product(
                "73167176531330624919225119674426574742355349194934", 6) ==
            23520);
}

TEST(LargestSeriesProduct, T008_reports_zero_if_the_only_digits_are_zero) {
    REQUIRE(largest_series_product::largest_product("0000", 2) == 0);
}

TEST(LargestSeriesProduct, T009_reports_zero_if_all_spans_include_zero) {
    REQUIRE(largest_series_product::largest_product("99099", 3) == 0);
}

TEST(LargestSeriesProduct, T010_rejects_span_longer_than_string_length) {
    REQUIRE_THROWS_AS(largest_series_product::largest_product("123", 4),
                      std::domain_error);
}

TEST(LargestSeriesProduct, T011_rejects_empty_string_and_nonzero_span) {
    REQUIRE_THROWS_AS(largest_series_product::largest_product("", 1),
                      std::domain_error);
}

TEST(LargestSeriesProduct, T012_rejects_invalid_character_in_digits) {
    REQUIRE_THROWS_AS(largest_series_product::largest_product("1234a5", 2),
                      std::domain_error);
}

TEST(LargestSeriesProduct, T013_rejects_negative_span) {
    REQUIRE_THROWS_AS(largest_series_product::largest_product("12345", -1),
                      std::domain_error);
}
#endif

}  // namespace
