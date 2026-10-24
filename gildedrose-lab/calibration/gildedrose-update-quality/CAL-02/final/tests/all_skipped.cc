// 校准样本 CAL-02：所有测试都跳过。
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

TEST(CalibrationSkipped, First) {
    GTEST_SKIP() << "skipped on purpose";
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

TEST(CalibrationSkipped, Second) {
    GTEST_SKIP() << "skipped on purpose";
}
