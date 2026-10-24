// 有界穷举探针生成器：在评分输入域内逐点运行被测代码，把实际结果写成一个 GoogleTest 表格测试。
// 用途：准备题目时判定“等价变异候选”（探针也区分不出的变异），不参与正式评分。
// 用法：c++ -std=c++11 -I<cpp/src> generate_probe.cc <cpp/src>/GildedRose.cc -o gen && ./gen > probe_tests.cc
#include "GildedRose.h"

#include <cstdio>
#include <string>
#include <vector>

namespace {

const char* const kNames[] = {"+5 Dexterity Vest", "Aged Brie", "Backstage passes to a TAFKAL80ETC concert",
                              "Sulfuras, Hand of Ragnaros", "Conjured Mana Cake", "Aged Brie ",
                              "Backstage passes", "Sulfuras"};
const int kNameCount = sizeof(kNames) / sizeof(kNames[0]);
const int kSulfuras = 3;

std::string quoted(const std::string& text) {
    std::string out = "\"";
    for (char c : text) {
        if (c == '"' || c == '\\') out += '\\';
        out += c;
    }
    return out + "\"";
}

}  // namespace

int main() {
    std::printf("// 生成文件，勿手工修改。由 generate_probe.cc 对原始 GildedRose.cc 逐点运行得到。\n");
    std::printf("// 输入域：sellIn -20..20；质量 0..50，Sulfuras 质量 80；另含多商品库存。\n");
    std::printf("#include \"GildedRose.h\"\n\n#include <gtest/gtest.h>\n\n#include <string>\n#include <vector>\n\n");
    std::printf("namespace {\n\nconst char* const kNames[] = {");
    for (int n = 0; n < kNameCount; ++n) std::printf("%s%s", n ? ", " : "", quoted(kNames[n]).c_str());
    std::printf("};\n\nstruct Case {\n    int name, sellIn, quality, expectedSellIn, expectedQuality;\n};\n\n");
    std::printf("const Case kCases[] = {\n");
    int cases = 0;
    for (int n = 0; n < kNameCount; ++n) {
        for (int sellIn = -20; sellIn <= 20; ++sellIn) {
            int low = n == kSulfuras ? 80 : 0, high = n == kSulfuras ? 80 : 50;
            for (int quality = low; quality <= high; ++quality) {
                std::vector<Item> items(1, Item(kNames[n], sellIn, quality));
                GildedRose app(items);
                app.updateQuality();
                std::printf("    {%d, %d, %d, %d, %d},\n", n, sellIn, quality, items[0].sellIn, items[0].quality);
                ++cases;
            }
        }
    }
    std::printf("};\n\n");
    const int sells[] = {-2, 0, 1, 5, 6, 10, 11};
    const int qualities[] = {0, 1, 49, 50};
    std::printf("struct Inventory {\n    int sellIn, quality;\n    int expected[%d][2];\n};\n\n", kNameCount);
    std::printf("const Inventory kInventories[] = {\n");
    for (int s : sells) {
        for (int q : qualities) {
            std::vector<Item> items;
            for (int n = 0; n < kNameCount; ++n) items.push_back(Item(kNames[n], s, n == kSulfuras ? 80 : q));
            GildedRose app(items);
            app.updateQuality();
            std::printf("    {%d, %d, {", s, q);
            for (int n = 0; n < kNameCount; ++n) std::printf("%s{%d, %d}", n ? ", " : "", items[n].sellIn, items[n].quality);
            std::printf("}},\n");
        }
    }
    std::printf("};\n\n}  // namespace\n\n");
    std::printf("TEST(EquivalenceProbe, SingleItemsAcrossDomain) {\n"
                "    int mismatches = 0;\n"
                "    for (const Case& c : kCases) {\n"
                "        std::vector<Item> items(1, Item(kNames[c.name], c.sellIn, c.quality));\n"
                "        GildedRose app(items);\n"
                "        app.updateQuality();\n"
                "        if (items.size() != 1u || items[0].name != kNames[c.name] || items[0].sellIn != c.expectedSellIn ||\n"
                "            items[0].quality != c.expectedQuality) {\n"
                "            if (++mismatches <= 5) {\n"
                "                ADD_FAILURE() << kNames[c.name] << \" sellIn=\" << c.sellIn << \" quality=\" << c.quality;\n"
                "            }\n"
                "        }\n"
                "    }\n"
                "    EXPECT_EQ(0, mismatches) << \"of %d cases\";\n"
                "}\n\n", cases);
    std::printf("TEST(EquivalenceProbe, MixedInventories) {\n"
                "    int mismatches = 0;\n"
                "    for (const Inventory& inv : kInventories) {\n"
                "        std::vector<Item> items;\n"
                "        for (int n = 0; n < %d; ++n) items.push_back(Item(kNames[n], inv.sellIn, n == %d ? 80 : inv.quality));\n"
                "        GildedRose app(items);\n"
                "        app.updateQuality();\n"
                "        if (items.size() != %du) {\n"
                "            ++mismatches;\n"
                "            continue;\n"
                "        }\n"
                "        for (int n = 0; n < %d; ++n) {\n"
                "            if (items[n].name != kNames[n] || items[n].sellIn != inv.expected[n][0] ||\n"
                "                items[n].quality != inv.expected[n][1]) {\n"
                "                if (++mismatches <= 5) ADD_FAILURE() << kNames[n] << \" in inventory sellIn=\" << inv.sellIn;\n"
                "            }\n"
                "        }\n"
                "    }\n"
                "    EXPECT_EQ(0, mismatches);\n"
                "}\n\n", kNameCount, kSulfuras, kNameCount, kNameCount);
    std::printf("TEST(EquivalenceProbe, EmptyInventory) {\n"
                "    std::vector<Item> items;\n"
                "    GildedRose app(items);\n"
                "    app.updateQuality();\n"
                "    EXPECT_TRUE(items.empty());\n"
                "}\n");
    return 0;
}
