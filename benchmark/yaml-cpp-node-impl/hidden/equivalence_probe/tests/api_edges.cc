#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
TEST(NodeApi, ExplicitTagAndDefaultDefinition) {
  YAML::Node empty; EXPECT_TRUE(empty.IsDefined()); EXPECT_TRUE(empty.IsNull());
  YAML::Node scalar("value"); scalar.SetTag("!custom");
  EXPECT_EQ("!custom",scalar.Tag()); EXPECT_EQ("value",scalar.as<std::string>());
  scalar.SetTag("!other"); EXPECT_EQ("!other",scalar.Tag());
}
