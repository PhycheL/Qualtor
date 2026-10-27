// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "triangle.h"
#include <stdexcept>

namespace {

/*
Problem spec commentary:

    Pursuant to discussion in #202, we have decided NOT to test triangles
    where all side lengths are positive but a + b = c. e.g:
    (2, 4, 2, Isosceles), (1, 3, 4, Scalene).
    It's true that the triangle inequality admits such triangles.These
    triangles have zero area, however.
    They're degenerate triangles with all three vertices collinear.
    (In contrast, we will test (0, 0, 0, Illegal), as it is a point)
    The tests assert properties of the triangle are true or false.
    See: https://github.com/exercism/problem-specifications/issues/379 for
    disscussion of this approach How you handle invalid triangles is up to you.
    These tests suggest a triangle is returned, but all of its properties are
false. But you could also have the creation of an invalid triangle return an
error or exception. Choose what is idiomatic for your language."

The CPP track has chosen to throw a domain error for invalid triangles.

Tests, that check if an equilateral is also scalene (etc.) do not work with
the chosen implementation, they are therefore not implemented for this track.

*/

// improves error messages with triangle flavor enum text instead of integers:
CATCH_REGISTER_ENUM(triangle::flavor, triangle::flavor::equilateral,
                    triangle::flavor::isosceles, triangle::flavor::scalene)

TEST(Triangle, T001_equilateral_triangle_all_sides_are_equal) {
    REQUIRE(triangle::flavor::equilateral == triangle::kind(2, 2, 2));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(Triangle, T002_equilateral_triangle_any_side_is_unequal) {
    REQUIRE_FALSE(triangle::flavor::equilateral == triangle::kind(2, 3, 2));
}

TEST(Triangle, T003_equilateral_triangle_no_sides_are_equal) {
    REQUIRE_FALSE(triangle::flavor::equilateral == triangle::kind(5, 4, 6));
}

TEST(Triangle, T004_equilateral_triangle_sides_may_be_floats) {
    REQUIRE(triangle::flavor::equilateral == triangle::kind(0.5, 0.5, 0.5));
}

TEST(Triangle, T005_isosceles_triangle_last_two_sides_are_equal) {
    REQUIRE(triangle::flavor::isosceles == triangle::kind(3, 4, 4));
}

TEST(Triangle, T006_isosceles_triangle_first_two_sides_are_equal) {
    REQUIRE(triangle::flavor::isosceles == triangle::kind(4, 4, 3));
}

TEST(Triangle, T007_isosceles_triangle_first_and_last_sides_are_equal) {
    REQUIRE(triangle::flavor::isosceles == triangle::kind(4, 3, 4));
}

TEST(Triangle, T008_isosceles_triangle_no_sides_are_equal) {
    REQUIRE_FALSE(triangle::flavor::isosceles == triangle::kind(2, 3, 4));
}

TEST(Triangle, T009_isosceles_triangle_first_triangle_inequality_violation) {
    REQUIRE_THROWS_AS(triangle::kind(1, 1, 3), std::domain_error);
}

TEST(Triangle, T010_isosceles_triangle_second_triangle_inequality_violation) {
    REQUIRE_THROWS_AS(triangle::kind(1, 3, 1), std::domain_error);
}

TEST(Triangle, T011_isosceles_triangle_third_triangle_inequality_violation) {
    REQUIRE_THROWS_AS(triangle::kind(3, 1, 1), std::domain_error);
}

TEST(Triangle, T012_isosceles_triangle_sides_may_be_floats) {
    REQUIRE(triangle::flavor::isosceles == triangle::kind(0.5, 0.4, 0.5));
}

TEST(Triangle, T013_scalene_triangle_no_sides_are_equal) {
    REQUIRE(triangle::flavor::scalene == triangle::kind(5, 4, 6));
}

TEST(Triangle, T014_scalene_triangle_may_not_violate_triangle_inequality) {
    REQUIRE_THROWS_AS(triangle::kind(7, 3, 2), std::domain_error);
}

TEST(Triangle, T015_scalene_triangle_sides_may_be_floats) {
    REQUIRE(triangle::flavor::scalene == triangle::kind(0.4, 0.6, 0.3));
}

TEST(Triangle, T016_all_zero_sides_is_not_a_triangle) {
    REQUIRE_THROWS_AS(triangle::kind(0, 0, 0), std::domain_error);
}

// Tests that are not in the problem spec
// kept for legacy and specific cpp functionality

TEST(Triangle, T017_triangles_with_negative_sides_are_illegal) {
    REQUIRE_THROWS_AS(triangle::kind(3, 4, -5), std::domain_error);
}

TEST(Triangle, T018_double_and_integer_arguments) {
    REQUIRE(triangle::flavor::scalene == triangle::kind(5.5, 4, 2));
}

#endif

}  // namespace
