#include "functions.h"
#include <gtest/gtest.h>
#include <climits>

TEST(BoostFilter, TypesAndBoundaries) {
  EXPECT_EQ((std::vector<int>{INT_MIN, -1, 0, INT_MAX}),
            filter_integers({boost::any(), INT_MIN, true, -1, 0, 1.0,
                             std::string("3"), 'a', INT_MAX, 4L}));
  EXPECT_TRUE(filter_integers({false, 0.0, "text", 0L}).empty());
  EXPECT_EQ((std::vector<int>{1, 1, -2}), filter_integers({1, 1, -2}));
}

TEST(BoostCompare, FiniteValuesAndTypes) {
  const boost::any values[] = {std::string("-3,5"), -3, -1.25, 0,
                              std::string("1.25"), 2.5, std::string("3,75")};
  for (int i = 0; i < 7; ++i) for (int j = 0; j < 7; ++j) {
    boost::any actual = compare_one(values[i], values[j]);
    if (i == j) {
      EXPECT_EQ("None", boost::any_cast<std::string>(actual));
    } else {
      const boost::any& expected = values[i > j ? i : j];
      ASSERT_TRUE(expected.type() == actual.type());
      if (expected.type() == typeid(int)) EXPECT_EQ(boost::any_cast<int>(expected), boost::any_cast<int>(actual));
      if (expected.type() == typeid(double)) EXPECT_EQ(boost::any_cast<double>(expected), boost::any_cast<double>(actual));
      if (expected.type() == typeid(std::string)) EXPECT_EQ(boost::any_cast<std::string>(expected), boost::any_cast<std::string>(actual));
    }
  }
  EXPECT_EQ("None", boost::any_cast<std::string>(compare_one(0, std::string("0,0"))));
  EXPECT_EQ("None", boost::any_cast<std::string>(compare_one(std::string("2.5"), 2.5)));
}

TEST(BoostCompare, CommaAtBeginningAndAfterFortyTwoCharacters) {
  EXPECT_EQ(1, boost::any_cast<int>(compare_one(std::string(",5"), 1)));
  EXPECT_EQ(1, boost::any_cast<int>(compare_one(1, std::string(",5"))));
  const std::string value = std::string(50, '0') + ",5";
  EXPECT_EQ(value, boost::any_cast<std::string>(compare_one(value, .25)));
  EXPECT_EQ(value, boost::any_cast<std::string>(compare_one(.25, value)));
}
