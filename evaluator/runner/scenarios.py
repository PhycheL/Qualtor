"""框架自测剧本；不作为模型质量或模型费用的证据。"""
GOOD = '''#include "GildedRose.h"
#include <gtest/gtest.h>
TEST(Generated, NormalItem) {
    std::vector<Item> items{Item("ordinary", 5, 10)};
    GildedRose rose(items);
    rose.updateQuality();
    EXPECT_EQ(4, items[0].sellIn);
    EXPECT_EQ(9, items[0].quality);
}
'''
WRONG = GOOD.replace("EXPECT_EQ(9,", "EXPECT_EQ(99,")


def write(content=GOOD, path="tests/generated.cc"):
    return {"tool": "write", "args": {"path": path, "content": content}}


BUILD = {"tool": "build_and_test", "args": {}}
FINISHED = [write(WRONG), BUILD, write(), BUILD]
SCENARIOS = {
    "finished": FINISHED,
    "budget_exhausted": [write(WRONG), BUILD, BUILD, BUILD, BUILD, BUILD],
    "never_built": [write()],
    "generation_stalled": [write(), {"stall": True}],
    "agent_error": lambda attempt: [{"error": True}] if attempt < 3 else FINISHED,
    "agent_error_persistent": [{"error": True}],
    "access_denied": [write("modified", "project/cpp/src/GildedRose.cc"),
                      write("modified", "/out/result.json"),
                      write("modified", "tests/forbidden.json"),
                      {"tool": "read", "args": {"path": "/pi/package.json"}},
                      {"tool": "read", "args": {"path": "../input/runtime.json"}},
                      write(), BUILD],
    "compile_repair": [write("this is not C++"), BUILD, write(), BUILD],
    "edit_repair": [write(WRONG), BUILD,
                    {"tool": "edit", "args": {"path": "tests/generated.cc", "edits": [
                        {"oldText": "EXPECT_EQ(99,", "newText": "EXPECT_EQ(9,"}]}}, BUILD],
    "process_isolation": [write(GOOD + '''
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unistd.h>
// 在容器内能访问到的位置搜索隐藏评分材料的文件名；pi 依赖与系统目录跳过，避免超过单测时限。
std::string hiddenMaterialFound() {
    FILE* pipe = popen("find / \\\\( -path /proc -o -path /sys -o -path /pi -o -path /usr \\\\) -prune -o "
                       "\\\\( -name mutation_baseline.json -o -name reference_tests.cc -o -name probe_tests.cc "
                       "-o -name generate_probe.cc -o -name calibration-status.json -o -name calibration_report.json \\\\) "
                       "-print 2>/dev/null", "r");
    std::string found;
    char buffer[512];
    while (pipe && fgets(buffer, sizeof buffer, pipe)) found += buffer;
    if (pipe) pclose(pipe);
    return found;
}
TEST(Isolation, RefereeAndSourceProtected) {
    EXPECT_EQ(65534, getuid());
    EXPECT_TRUE(std::ifstream("/project/cpp/src/GildedRose.cc").good());
    EXPECT_TRUE(std::ifstream("/product/tests/generated.cc").good());
    EXPECT_EQ(nullptr, std::getenv("QUALTOR_API_KEY"));
    EXPECT_FALSE(std::ofstream("/private/output/result.json").good());
    EXPECT_FALSE(std::ofstream("/private/output/logs/tamper.log").good());
    EXPECT_FALSE(std::ofstream("/product/tests/generated.cc").good());
    EXPECT_FALSE(std::ofstream("/project/cpp/src/GildedRose.cc").good());
    EXPECT_FALSE(std::ifstream("/agent/state/settings.json").good());
    EXPECT_EQ("", hiddenMaterialFound());
}
'''), BUILD],
}


def config():
    return {"provider": "qualtor-scripted", "model": "script", "thinking": "off", "cost_per_million": {}}
