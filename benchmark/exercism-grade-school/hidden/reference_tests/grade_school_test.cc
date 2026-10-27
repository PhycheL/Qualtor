// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "grade_school.h"

#include <map>
#include <string>
#include <vector>

namespace {

using namespace std;

TEST(GradeSchool, T001_roster_is_empty_when_no_student_is_added) {
    const grade_school::school school{};

    REQUIRE(school.roster().empty());
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(GradeSchool, T002_student_is_added_to_the_roster) {
    grade_school::school school;
    school.add("Aimee", 2);

    const map<int, vector<string>> expected{{2, {"Aimee"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T003_multiple_students_in_the_same_grade_are_added_to_the_roster) {
    grade_school::school school;
    school.add("Blair", 2);
    school.add("James", 2);
    school.add("Paul", 2);

    const map<int, vector<string>> expected{{2, {"Blair", "James", "Paul"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T004_student_not_added_to_same_grade_in_the_roster_more_than_once) {
    grade_school::school school;
    school.add("Blair", 2);
    school.add("James", 2);
    school.add("James", 2);
    school.add("Paul", 2);

    const map<int, vector<string>> expected{{2, {"Blair", "James", "Paul"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T005_students_in_multiple_grades_are_added_to_the_roster) {
    grade_school::school school;
    school.add("Chelsea", 3);
    school.add("Logan", 7);

    const map<int, vector<string>> expected{{3, {"Chelsea"}}, {7, {"Logan"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T006_student_not_added_to_multiple_grades_in_the_roster) {
    grade_school::school school;
    school.add("Blair", 2);
    school.add("James", 2);
    school.add("James", 3);
    school.add("Paul", 3);

    const map<int, vector<string>> expected{{2, {"Blair", "James"}},
                                            {3, {"Paul"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T007_students_are_sorted_by_grades_in_the_roster) {
    grade_school::school school;
    school.add("Jim", 3);
    school.add("Peter", 2);
    school.add("Anna", 1);

    const map<int, vector<string>> expected{
        {1, {"Anna"}}, {2, {"Peter"}}, {3, {"Jim"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T008_students_are_sorted_by_name_in_the_roster) {
    grade_school::school school;
    school.add("Peter", 2);
    school.add("Zoe", 2);
    school.add("Alex", 2);

    const map<int, vector<string>> expected{{2, {"Alex", "Peter", "Zoe"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T009_students_are_sorted_by_grades_and_then_by_name_in_the_roster) {
    grade_school::school school;
    school.add("Peter", 2);
    school.add("Anna", 1);
    school.add("Barb", 1);
    school.add("Zoe", 2);
    school.add("Alex", 2);
    school.add("Jim", 3);
    school.add("Charlie", 1);

    const map<int, vector<string>> expected{{1, {"Anna", "Barb", "Charlie"}},
                                            {2, {"Alex", "Peter", "Zoe"}},
                                            {3, {"Jim"}}};
    REQUIRE(expected == school.roster());
}

TEST(GradeSchool, T010_grade_is_empty_if_no_students_in_the_roster) {
    const grade_school::school school{};

    REQUIRE(school.grade(1).empty());
}

TEST(GradeSchool, T011_grade_is_empty_if_no_students_in_that_grade) {
    grade_school::school school;
    school.add("Peter", 2);
    school.add("Zoe", 2);
    school.add("Alex", 2);
    school.add("Jim", 3);

    const vector<string> expected{};
    REQUIRE(expected == school.grade(1));
}

TEST(GradeSchool, T012_student_not_added_to_same_grade_more_than_once) {
    grade_school::school school;
    school.add("Blair", 2);
    school.add("James", 2);
    school.add("James", 2);
    school.add("Paul", 2);

    const vector<string> expected{"Blair", "James", "Paul"};
    REQUIRE(expected == school.grade(2));
}

TEST(GradeSchool, T013_student_not_added_to_multiple_grades) {
    grade_school::school school;
    school.add("Blair", 2);
    school.add("James", 2);
    school.add("James", 3);
    school.add("Paul", 3);

    const vector<string> expected{"Blair", "James"};
    REQUIRE(expected == school.grade(2));
}

TEST(GradeSchool, T014_student_not_added_to_other_grade_for_multiple_grades) {
    grade_school::school school;
    school.add("Blair", 2);
    school.add("James", 2);
    school.add("James", 3);
    school.add("Paul", 3);

    const vector<string> expected{"Paul"};
    REQUIRE(expected == school.grade(3));
}

TEST(GradeSchool, T015_students_are_sorted_by_name_in_a_grade) {
    grade_school::school school;
    school.add("Franklin", 5);
    school.add("Bradley", 5);
    school.add("Jeff", 1);

    const vector<string> expected{"Bradley", "Franklin"};
    REQUIRE(expected == school.grade(5));
}

#endif

}  // namespace
