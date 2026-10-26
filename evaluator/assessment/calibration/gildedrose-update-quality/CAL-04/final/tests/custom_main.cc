// 校准样本 CAL-04：自带 main 直接返回 0。
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

TEST(CalibrationCustomMain, NeverRuns) {
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

int main() {
    return 0;
}
