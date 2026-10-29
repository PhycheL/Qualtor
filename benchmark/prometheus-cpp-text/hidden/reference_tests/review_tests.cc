#include <gtest/gtest.h>
#include "prometheus/gauge.h"
#include "prometheus/text_serializer.h"
#include <ctime>
#include <cmath>

TEST(Review, GaugeTimestampAndCollect) {
  prometheus::Gauge g(3.75);
  EXPECT_DOUBLE_EQ(3.75, g.Collect().gauge().value());
  const auto before = std::time(nullptr);
  g.SetToCurrentTime();
  const auto after = std::time(nullptr);
  EXPECT_GE(g.Value(), static_cast<double>(before));
  EXPECT_LE(g.Value(), static_cast<double>(after));
  g.Set(-0.0);
  g.Increment(0.0);
  EXPECT_FALSE(std::signbit(g.Value()));
  g.Set(-0.0);
  g.Decrement(-0.0);
  EXPECT_FALSE(std::signbit(g.Value()));
}

TEST(Review, LabelsWithoutEscapesKeepAllCharacters) {
  using namespace io::prometheus::client;
  MetricFamily f;
  f.set_name("g"); f.set_type(GAUGE);
  auto m = f.add_metric(); m->mutable_gauge()->set_value(1);
  auto label = m->add_label(); label->set_name("x"); label->set_value("plain");
  prometheus::TextSerializer s;
  EXPECT_EQ("# TYPE g gauge\ng{x=\"plain\"} 1.000000\n", s.Serialize({f}));
}
