// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "robot_name.h"
#include <cctype>
#include <string>
#include <unordered_set>

namespace {

using namespace std;

namespace {
// Helper function to check the robot name matches the instructions.
//
// 2 uppercase letters followed by 3 digits.
static bool validate_name(const string& name) {
    if (name.length() != 5) return false;
    return isupper(name[0]) && isupper(name[1]) && isdigit(name[2]) &&
           isdigit(name[3]) && isdigit(name[4]);
}
}  // namespace

TEST(RobotName, T001_has_a_name) {
    const robot_name::robot robot;

    REQUIRE(validate_name(robot.name()));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(RobotName, T002_name_is_the_same_each_time) {
    const robot_name::robot robot;

    REQUIRE(robot.name() == robot.name());
}

TEST(RobotName, T003_different_robots_have_different_names) {
    const robot_name::robot robot_one;
    const robot_name::robot robot_two;

    REQUIRE(robot_one.name() != robot_two.name());
}

TEST(RobotName, T004_is_able_to_reset_name) {
    robot_name::robot robot;
    const auto original_name = robot.name();

    robot.reset();

    REQUIRE(original_name != robot.name());
}

TEST(RobotName, T005_exhausting_digits_yields_different_names) {
    robot_name::robot robot;
    unordered_set<string> names;
    names.insert(robot.name());

    for (int i = 0; i < 1000; ++i) {
        robot.reset();
        REQUIRE(names.count(robot.name()) == 0);
        REQUIRE(validate_name(robot.name()));
        names.insert(robot.name());
    }
}
#endif

}  // namespace
