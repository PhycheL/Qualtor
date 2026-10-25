// 等价版本差分检查：与某一份 GildedRose.cc 一起编译，按固定输入网格连续更新 3 天，输出结果数量和哈希。
// 原代码与 eq-02 的输出必须完全相同。sellIn 为 INT_MIN 时原代码有符号溢出（未定义行为），不在比较范围内。
// 用法见 benchmark/gildedrose-update-quality/hidden/variants/README.md。
#include "GildedRose.h"

#include <climits>
#include <cstdio>
#include <string>
#include <vector>

namespace {

unsigned long long hashValue = 1469598103934665603ULL;
unsigned long long count = 0;

void mix(long long value)
{
    for (int i = 0; i < 8; ++i)
    {
        hashValue ^= static_cast<unsigned long long>((value >> (i * 8)) & 0xff);
        hashValue *= 1099511628211ULL;
    }
}

std::vector<int> range(int low, int high, const std::vector<int>& extra)
{
    std::vector<int> values(extra);
    for (int value = low; value <= high; ++value)
    {
        values.push_back(value);
    }
    return values;
}

}  // namespace

int main()
{
    const char* names[] = {"Aged Brie", "Backstage passes to a TAFKAL80ETC concert", "Sulfuras, Hand of Ragnaros",
                           "+5 Dexterity Vest", "Conjured Mana Cake", "", "Aged brie", "Sulfuras"};
    std::vector<int> extremeSellIn;
    extremeSellIn.push_back(INT_MIN + 1);
    extremeSellIn.push_back(INT_MIN + 2);
    extremeSellIn.push_back(INT_MIN + 3);
    extremeSellIn.push_back(-100000);
    extremeSellIn.push_back(100000);
    extremeSellIn.push_back(INT_MAX - 1);
    extremeSellIn.push_back(INT_MAX);
    std::vector<int> extremeQuality;
    extremeQuality.push_back(INT_MIN);
    extremeQuality.push_back(INT_MIN + 1);
    extremeQuality.push_back(-100000);
    extremeQuality.push_back(100000);
    extremeQuality.push_back(INT_MAX - 1);
    extremeQuality.push_back(INT_MAX);
    const std::vector<int> sellIns = range(-80, 80, extremeSellIn);
    const std::vector<int> qualities = range(-80, 130, extremeQuality);
    for (unsigned n = 0; n < sizeof(names) / sizeof(names[0]); ++n)
    {
        for (unsigned s = 0; s < sellIns.size(); ++s)
        {
            for (unsigned q = 0; q < qualities.size(); ++q)
            {
                std::vector<Item> items(1, Item(names[n], sellIns[s], qualities[q]));
                GildedRose rose(items);
                for (int day = 0; day < 3 && items[0].sellIn != INT_MIN; ++day)
                {
                    rose.updateQuality();
                    mix(n);
                    mix(s);
                    mix(q);
                    mix(day);
                    mix(items[0].sellIn);
                    mix(items[0].quality);
                    ++count;
                }
            }
        }
    }
    std::printf("%llu %016llx\n", count, hashValue);
    return 0;
}
