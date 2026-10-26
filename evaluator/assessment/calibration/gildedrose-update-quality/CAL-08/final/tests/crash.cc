// 校准样本 CAL-08：空指针解引用，进程崩溃。
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

TEST(CalibrationCrash, NullDereference) {
    int* volatile pointer = 0;
    *pointer = 42;
}
