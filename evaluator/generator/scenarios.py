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
                      write("modified", "/record/build-state.json"),
                      write("modified", "tests/forbidden.json"),
                      {"tool": "read", "args": {"path": "/pi/package.json"}},
                      {"tool": "read", "args": {"path": "../input/runtime.json"}},
                      write(), BUILD],
    "compile_repair": [write("this is not C++"), BUILD, write(), BUILD],
    "process_isolation": [write(GOOD + '''
#include <fstream>
#include <unistd.h>
TEST(Isolation, RefereeAndSourceProtected) {
    EXPECT_EQ(65534, getuid());
    EXPECT_FALSE(std::ofstream("/private/record/build-state.json").good());
    EXPECT_FALSE(std::ofstream("/private/record/first/tests/generated.cc").good());
    EXPECT_FALSE(std::ofstream("/snapshots/attempt-1/tests/generated.cc").good());
    EXPECT_FALSE(std::ofstream("/workspace/project/cpp/src/GildedRose.cc").good());
    EXPECT_FALSE(std::ifstream("/agent/state/settings.json").good());
    EXPECT_FALSE(std::ifstream("/scorer/calibration-status.json").good());
    EXPECT_FALSE(std::ifstream("/lab/tasks/gildedrose-update-quality/hidden/mutation_baseline.json").good());
}
'''), BUILD],
}


def config():
    return {"provider": "qualtor-scripted", "model": "script", "thinking": "off", "cost_per_million": {}}
