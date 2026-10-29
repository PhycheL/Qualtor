// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace {

// This problem requires you to install and use the boost date_time library.
// CMake will try to find and configure it for you if it is installed on your
// system.
// See <http://www.boost.org/doc/libs/1_74_0/doc/html/date_time.html> for
// documentation on boost::gregorian::date

TEST(Meetup, T001_monteenth_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 13};
    REQUIRE(expected == meetup.monteenth());
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Meetup, T002_monteenth_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 19};
    REQUIRE(expected == meetup.monteenth());
}

TEST(Meetup, T003_monteenth_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 16};
    REQUIRE(expected == meetup.monteenth());
}

TEST(Meetup, T004_tuesteenth_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 19};
    REQUIRE(expected == meetup.tuesteenth());
}

TEST(Meetup, T005_tuesteenth_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 16};
    REQUIRE(expected == meetup.tuesteenth());
}

TEST(Meetup, T006_tuesteenth_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 13};
    REQUIRE(expected == meetup.tuesteenth());
}

TEST(Meetup, T007_wednesteenth_of_January_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jan, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jan, 16};
    REQUIRE(expected == meetup.wednesteenth());
}

TEST(Meetup, T008_wednesteenth_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 13};
    REQUIRE(expected == meetup.wednesteenth());
}

TEST(Meetup, T009_wednesteenth_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 19};
    REQUIRE(expected == meetup.wednesteenth());
}

TEST(Meetup, T010_thursteenth_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 16};
    REQUIRE(expected == meetup.thursteenth());
}

TEST(Meetup, T011_thursteenth_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 13};
    REQUIRE(expected == meetup.thursteenth());
}

TEST(Meetup, T012_thursteenth_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 19};
    REQUIRE(expected == meetup.thursteenth());
}

TEST(Meetup, T013_friteenth_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 19};
    REQUIRE(expected == meetup.friteenth());
}

TEST(Meetup, T014_friteenth_of_Aug_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 16};
    REQUIRE(expected == meetup.friteenth());
}

TEST(Meetup, T015_friteenth_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 13};
    REQUIRE(expected == meetup.friteenth());
}

TEST(Meetup, T016_saturteenth_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 16};
    REQUIRE(expected == meetup.saturteenth());
}

TEST(Meetup, T017_saturteenth_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 19};
    REQUIRE(expected == meetup.saturteenth());
}

TEST(Meetup, T018_sunteenth_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 19};
    REQUIRE(expected == meetup.sunteenth());
}

TEST(Meetup, T019_sunteenth_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 16};
    REQUIRE(expected == meetup.sunteenth());
}

TEST(Meetup, T020_sunteenth_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 13};
    REQUIRE(expected == meetup.sunteenth());
}

TEST(Meetup, T021_first_Monday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 4};
    REQUIRE(expected == meetup.first_monday());
}

TEST(Meetup, T022_first_Monday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 1};
    REQUIRE(expected == meetup.first_monday());
}

TEST(Meetup, T023_first_Tuesday_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 7};
    REQUIRE(expected == meetup.first_tuesday());
}

TEST(Meetup, T024_first_Tuesday_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 4};
    REQUIRE(expected == meetup.first_tuesday());
}

TEST(Meetup, T025_first_Wednesday_of_July_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jul, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jul, 3};
    REQUIRE(expected == meetup.first_wednesday());
}

TEST(Meetup, T026_first_Wednesday_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 7};
    REQUIRE(expected == meetup.first_wednesday());
}

TEST(Meetup, T027_first_Thursday_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 5};
    REQUIRE(expected == meetup.first_thursday());
}

TEST(Meetup, T028_first_Thursday_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 3};
    REQUIRE(expected == meetup.first_thursday());
}

TEST(Meetup, T029_first_Friday_of_November_2013) {
    const meetup::scheduler meetup{boost::gregorian::Nov, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Nov, 1};
    REQUIRE(expected == meetup.first_friday());
}

TEST(Meetup, T030_first_Friday_of_December_2013) {
    const meetup::scheduler meetup{boost::gregorian::Dec, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Dec, 6};
    REQUIRE(expected == meetup.first_friday());
}

TEST(Meetup, T031_first_Saturday_of_January_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jan, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jan, 5};
    REQUIRE(expected == meetup.first_saturday());
}

TEST(Meetup, T032_first_Saturday_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 2};
    REQUIRE(expected == meetup.first_saturday());
}

TEST(Meetup, T033_first_Sunday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 3};
    REQUIRE(expected == meetup.first_sunday());
}

TEST(Meetup, T034_first_Sunday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 7};
    REQUIRE(expected == meetup.first_sunday());
}

TEST(Meetup, T035_second_Monday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 11};
    REQUIRE(expected == meetup.second_monday());
}

TEST(Meetup, T036_second_Monday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 8};
    REQUIRE(expected == meetup.second_monday());
}

TEST(Meetup, T037_second_Tuesday_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 14};
    REQUIRE(expected == meetup.second_tuesday());
}

TEST(Meetup, T038_second_Tuesday_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 11};
    REQUIRE(expected == meetup.second_tuesday());
}

TEST(Meetup, T039_second_Wednesday_of_July_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jul, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jul, 10};
    REQUIRE(expected == meetup.second_wednesday());
}

TEST(Meetup, T040_second_Wednesday_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 14};
    REQUIRE(expected == meetup.second_wednesday());
}

TEST(Meetup, T041_second_Thursday_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 12};
    REQUIRE(expected == meetup.second_thursday());
}

TEST(Meetup, T042_second_Thursday_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 10};
    REQUIRE(expected == meetup.second_thursday());
}

TEST(Meetup, T043_second_Friday_of_November_2013) {
    const meetup::scheduler meetup{boost::gregorian::Nov, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Nov, 8};
    REQUIRE(expected == meetup.second_friday());
}

TEST(Meetup, T044_second_Friday_of_December_2013) {
    const meetup::scheduler meetup{boost::gregorian::Dec, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Dec, 13};
    REQUIRE(expected == meetup.second_friday());
}

TEST(Meetup, T045_second_Saturday_of_January_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jan, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jan, 12};
    REQUIRE(expected == meetup.second_saturday());
}

TEST(Meetup, T046_second_Saturday_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 9};
    REQUIRE(expected == meetup.second_saturday());
}

TEST(Meetup, T047_second_Sunday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 10};
    REQUIRE(expected == meetup.second_sunday());
}

TEST(Meetup, T048_second_Sunday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 14};
    REQUIRE(expected == meetup.second_sunday());
}

TEST(Meetup, T049_third_Monday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 18};
    REQUIRE(expected == meetup.third_monday());
}

TEST(Meetup, T050_third_Monday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 15};
    REQUIRE(expected == meetup.third_monday());
}

TEST(Meetup, T051_third_Tuesday_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 21};
    REQUIRE(expected == meetup.third_tuesday());
}

TEST(Meetup, T052_third_Tuesday_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 18};
    REQUIRE(expected == meetup.third_tuesday());
}

TEST(Meetup, T053_third_Wednesday_of_July_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jul, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jul, 17};
    REQUIRE(expected == meetup.third_wednesday());
}

TEST(Meetup, T054_third_Wednesday_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 21};
    REQUIRE(expected == meetup.third_wednesday());
}

TEST(Meetup, T055_third_Thursday_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 19};
    REQUIRE(expected == meetup.third_thursday());
}

TEST(Meetup, T056_third_Thursday_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 17};
    REQUIRE(expected == meetup.third_thursday());
}

TEST(Meetup, T057_third_Friday_of_November_2013) {
    const meetup::scheduler meetup{boost::gregorian::Nov, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Nov, 15};
    REQUIRE(expected == meetup.third_friday());
}

TEST(Meetup, T058_third_Friday_of_December_2013) {
    const meetup::scheduler meetup{boost::gregorian::Dec, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Dec, 20};
    REQUIRE(expected == meetup.third_friday());
}

TEST(Meetup, T059_third_Saturday_of_January_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jan, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jan, 19};
    REQUIRE(expected == meetup.third_saturday());
}

TEST(Meetup, T060_third_Saturday_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 16};
    REQUIRE(expected == meetup.third_saturday());
}

TEST(Meetup, T061_third_Sunday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 17};
    REQUIRE(expected == meetup.third_sunday());
}

TEST(Meetup, T062_third_Sunday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 21};
    REQUIRE(expected == meetup.third_sunday());
}

TEST(Meetup, T063_fourth_Monday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 25};
    REQUIRE(expected == meetup.fourth_monday());
}

TEST(Meetup, T064_fourth_Monday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 22};
    REQUIRE(expected == meetup.fourth_monday());
}

TEST(Meetup, T065_fourth_Tuesday_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 28};
    REQUIRE(expected == meetup.fourth_tuesday());
}

TEST(Meetup, T066_fourth_Tuesday_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 25};
    REQUIRE(expected == meetup.fourth_tuesday());
}

TEST(Meetup, T067_fourth_Wednesday_of_July_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jul, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jul, 24};
    REQUIRE(expected == meetup.fourth_wednesday());
}

TEST(Meetup, T068_fourth_Wednesday_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 28};
    REQUIRE(expected == meetup.fourth_wednesday());
}

TEST(Meetup, T069_fourth_Thursday_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 26};
    REQUIRE(expected == meetup.fourth_thursday());
}

TEST(Meetup, T070_fourth_Thursday_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 24};
    REQUIRE(expected == meetup.fourth_thursday());
}

TEST(Meetup, T071_fourth_Friday_of_November_2013) {
    const meetup::scheduler meetup{boost::gregorian::Nov, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Nov, 22};
    REQUIRE(expected == meetup.fourth_friday());
}

TEST(Meetup, T072_fourth_Friday_of_December_2013) {
    const meetup::scheduler meetup{boost::gregorian::Dec, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Dec, 27};
    REQUIRE(expected == meetup.fourth_friday());
}

TEST(Meetup, T073_fourth_Saturday_of_January_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jan, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jan, 26};
    REQUIRE(expected == meetup.fourth_saturday());
}

TEST(Meetup, T074_fourth_Saturday_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 23};
    REQUIRE(expected == meetup.fourth_saturday());
}

TEST(Meetup, T075_fourth_Sunday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 24};
    REQUIRE(expected == meetup.fourth_sunday());
}

TEST(Meetup, T076_fourth_Sunday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 28};
    REQUIRE(expected == meetup.fourth_sunday());
}

TEST(Meetup, T077_last_Monday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 25};
    REQUIRE(expected == meetup.last_monday());
}

TEST(Meetup, T078_last_Monday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 29};
    REQUIRE(expected == meetup.last_monday());
}

TEST(Meetup, T079_last_Tuesday_of_May_2013) {
    const meetup::scheduler meetup{boost::gregorian::May, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::May, 28};
    REQUIRE(expected == meetup.last_tuesday());
}

TEST(Meetup, T080_last_Tuesday_of_June_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jun, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jun, 25};
    REQUIRE(expected == meetup.last_tuesday());
}

TEST(Meetup, T081_last_Wednesday_of_July_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jul, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jul, 31};
    REQUIRE(expected == meetup.last_wednesday());
}

TEST(Meetup, T082_last_Wednesday_of_August_2013) {
    const meetup::scheduler meetup{boost::gregorian::Aug, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Aug, 28};
    REQUIRE(expected == meetup.last_wednesday());
}

TEST(Meetup, T083_last_Thursday_of_September_2013) {
    const meetup::scheduler meetup{boost::gregorian::Sep, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Sep, 26};
    REQUIRE(expected == meetup.last_thursday());
}

TEST(Meetup, T084_last_Thursday_of_October_2013) {
    const meetup::scheduler meetup{boost::gregorian::Oct, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Oct, 31};
    REQUIRE(expected == meetup.last_thursday());
}

TEST(Meetup, T085_last_Friday_of_November_2013) {
    const meetup::scheduler meetup{boost::gregorian::Nov, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Nov, 29};
    REQUIRE(expected == meetup.last_friday());
}

TEST(Meetup, T086_last_Friday_of_December_2013) {
    const meetup::scheduler meetup{boost::gregorian::Dec, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Dec, 27};
    REQUIRE(expected == meetup.last_friday());
}

TEST(Meetup, T087_last_Saturday_of_January_2013) {
    const meetup::scheduler meetup{boost::gregorian::Jan, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Jan, 26};
    REQUIRE(expected == meetup.last_saturday());
}

TEST(Meetup, T088_last_Saturday_of_February_2013) {
    const meetup::scheduler meetup{boost::gregorian::Feb, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Feb, 23};
    REQUIRE(expected == meetup.last_saturday());
}

TEST(Meetup, T089_last_Sunday_of_March_2013) {
    const meetup::scheduler meetup{boost::gregorian::Mar, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Mar, 31};
    REQUIRE(expected == meetup.last_sunday());
}

TEST(Meetup, T090_last_Sunday_of_April_2013) {
    const meetup::scheduler meetup{boost::gregorian::Apr, 2013};

    const boost::gregorian::date expected{2013, boost::gregorian::Apr, 28};
    REQUIRE(expected == meetup.last_sunday());
}
#endif

}  // namespace
