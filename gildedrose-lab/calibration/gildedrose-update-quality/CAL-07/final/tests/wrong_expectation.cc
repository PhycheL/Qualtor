// 校准样本 CAL-07：断言值故意写错（实际为 19）。
#include "GildedRose.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

Item updateOnce(const std::string& name, int sellIn, int quality) {
    std::vector<Item> items(1, Item(name, sellIn, quality));
    GildedRose app(items);
    app.updateQuality();
    return items[0];
}

}  // namespace

TEST(CalibrationWrongExpectation, ExpectedValueIsWrong) {
    EXPECT_EQ(18, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}
