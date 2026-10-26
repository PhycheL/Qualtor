// 校准样本 CAL-03：所有测试都被禁用。
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

TEST(CalibrationDisabled, DISABLED_First) {
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

TEST(DISABLED_CalibrationDisabledSuite, Second) {
    EXPECT_EQ(1, updateOnce("Aged Brie", 2, 0).quality);
}
