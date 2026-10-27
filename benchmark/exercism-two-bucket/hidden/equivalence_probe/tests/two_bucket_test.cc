// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "two_bucket.h"

namespace {

CATCH_REGISTER_ENUM(two_bucket::bucket_id, two_bucket::bucket_id::one,
                    two_bucket::bucket_id::two)

TEST(TwoBucket, T001_Measure_using_bucket_one_of_size_3_and_bucket_two_of_size_5) {
    auto bucket1_capacity = 3;
    auto bucket2_capacity = 5;
    auto goal_volume = 1;
    auto start_bucket = two_bucket::bucket_id::one;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 4);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::one);
    CHECK(actual.other_bucket_volume == 5);
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(TwoBucket, T002_Measure_using_bucket_one_of_size_3_and_bucket_two_of_size_5) {
    auto bucket1_capacity = 3;
    auto bucket2_capacity = 5;
    auto goal_volume = 1;
    auto start_bucket = two_bucket::bucket_id::two;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 8);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::two);
    CHECK(actual.other_bucket_volume == 3);
}

TEST(TwoBucket, T003_Measure_using_bucket_one_of_size_7_and_bucket_two_of_size_11) {
    auto bucket1_capacity = 7;
    auto bucket2_capacity = 11;
    auto goal_volume = 2;
    auto start_bucket = two_bucket::bucket_id::one;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 14);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::one);
    CHECK(actual.other_bucket_volume == 11);
}

TEST(TwoBucket, T004_Measure_using_bucket_one_of_size_7_and_bucket_two_of_size_11) {
    auto bucket1_capacity = 7;
    auto bucket2_capacity = 11;
    auto goal_volume = 2;
    auto start_bucket = two_bucket::bucket_id::two;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 18);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::two);
    CHECK(actual.other_bucket_volume == 7);
}

TEST(TwoBucket, T005_Measure_one_step_using_bucket_one_of_size_1_and_bucket_two_o) {
    auto bucket1_capacity = 1;
    auto bucket2_capacity = 3;
    auto goal_volume = 3;
    auto start_bucket = two_bucket::bucket_id::two;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 1);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::two);
    CHECK(actual.other_bucket_volume == 0);
}

TEST(TwoBucket, T006_Measure_using_bucket_one_of_size_2_and_bucket_two_of_size_3) {
    auto bucket1_capacity = 2;
    auto bucket2_capacity = 3;
    auto goal_volume = 3;
    auto start_bucket = two_bucket::bucket_id::one;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 2);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::two);
    CHECK(actual.other_bucket_volume == 2);
}

TEST(TwoBucket, T007_Not_possible_to_reach_the_goal) {
    auto bucket1_capacity = 6;
    auto bucket2_capacity = 15;
    auto goal_volume = 5;
    auto start_bucket = two_bucket::bucket_id::one;

    REQUIRE_THROWS(two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                       goal_volume, start_bucket));
}

TEST(TwoBucket, T008_With_the_same_buckets_but_a_different_goal_then_it_is_possib) {
    auto bucket1_capacity = 6;
    auto bucket2_capacity = 15;
    auto goal_volume = 9;
    auto start_bucket = two_bucket::bucket_id::one;

    auto actual = two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                      goal_volume, start_bucket);

    CHECK(actual.num_moves == 10);
    CHECK(actual.goal_bucket == two_bucket::bucket_id::two);
    CHECK(actual.other_bucket_volume == 0);
}

TEST(TwoBucket, T009_Goal_larger_than_both_buckets_is_impossible) {
    auto bucket1_capacity = 5;
    auto bucket2_capacity = 7;
    auto goal_volume = 8;
    auto start_bucket = two_bucket::bucket_id::one;

    REQUIRE_THROWS(two_bucket::measure(bucket1_capacity, bucket2_capacity,
                                       goal_volume, start_bucket));
}

#endif  // EXERCISM_RUN_ALL_TESTS

}  // namespace
