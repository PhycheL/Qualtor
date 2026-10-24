// 校准样本 CAL-11：确定性地模拟时好时坏。
// 评分器在同一个工作目录里按固定顺序运行测试，所以每次评分的失败次数相同。
#include <fstream>

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

TEST(CalibrationFlaky, FailsOnEveryOtherRun) {
    int count = 0;
    {
        std::ifstream in("qualtor_calibration_counter.txt");
        if (in) {
            in >> count;
        }
    }
    ++count;
    {
        std::ofstream out("qualtor_calibration_counter.txt");
        out << count;
    }
    EXPECT_NE(0, count % 2) << "run " << count;
}
