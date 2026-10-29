#include <gtest/gtest.h>
#include <limits>
#include "prometheus/text_serializer.h"

using namespace io::prometheus::client;
using prometheus::TextSerializer;

static std::string text(const MetricFamily& family) {
  TextSerializer serializer;
  return serializer.Serialize({family});
}

TEST(TextMetrics, EmptyHelpAndTimestamps) {
  TextSerializer serializer;
  EXPECT_EQ("", serializer.Serialize({}));
  MetricFamily f;
  f.set_name("requests");
  f.set_type(COUNTER);
  EXPECT_EQ("# TYPE requests counter\n", text(f));
  f.set_help("number of requests");
  Metric* m = f.add_metric();
  m->mutable_counter()->set_value(12.5);
  m->set_timestamp_ms(12345);
  EXPECT_EQ("# HELP requests number of requests\n# TYPE requests counter\nrequests 12.500000 12345\n", text(f));
  m->set_timestamp_ms(-1);
  EXPECT_NE(std::string::npos, text(f).find("12.500000 -1\n"));
}

TEST(TextMetrics, LabelsEscapesAndSpecialNumbers) {
  MetricFamily f;
  f.set_name("g");
  f.set_type(GAUGE);
  Metric* m = f.add_metric();
  auto* label = m->add_label();
  label->set_name("x"); label->set_value("a\\b\"c\nd");
  label = m->add_label(); label->set_name("y"); label->set_value("plain");
  m->mutable_gauge()->set_value(-1.25);
  EXPECT_EQ("# TYPE g gauge\ng{x=\"a\\\\b\\\"c\\\nd\",y=\"plain\"} -1.250000\n", text(f));
  m->clear_label();
  m->mutable_gauge()->set_value(std::numeric_limits<double>::infinity());
  EXPECT_EQ("# TYPE g gauge\ng +Inf\n", text(f));
  m->mutable_gauge()->set_value(-std::numeric_limits<double>::infinity());
  EXPECT_EQ("# TYPE g gauge\ng -Inf\n", text(f));
  m->mutable_gauge()->set_value(std::numeric_limits<double>::quiet_NaN());
  EXPECT_EQ("# TYPE g gauge\ng Nan\n", text(f));
}

TEST(TextMetrics, SummaryAndUntyped) {
  MetricFamily f;
  f.set_name("s"); f.set_type(SUMMARY);
  Metric* m = f.add_metric();
  auto* s = m->mutable_summary(); s->set_sample_count(3); s->set_sample_sum(7.25);
  auto* q = s->add_quantile(); q->set_quantile(.5); q->set_value(2.0);
  q = s->add_quantile(); q->set_quantile(.9); q->set_value(4.0);
  EXPECT_EQ("# TYPE s summary\ns_count 3\ns_sum 7.250000\ns_quantile{quantile=\"0.500000\"} 2.000000\ns_quantile{quantile=\"0.900000\"} 4.000000\n", text(f));
  f.set_type(UNTYPED); m->mutable_untyped()->set_value(3.5);
  EXPECT_EQ("# TYPE s untyped\ns 3.500000\n", text(f));
}

TEST(TextMetrics, HistogramExplicitAndImplicitInfinity) {
  MetricFamily f;
  f.set_name("h"); f.set_type(HISTOGRAM);
  Metric* m = f.add_metric();
  auto* h = m->mutable_histogram(); h->set_sample_count(3); h->set_sample_sum(6.5);
  auto* b = h->add_bucket(); b->set_upper_bound(2); b->set_cumulative_count(1);
  const std::string expected = "# TYPE h histogram\nh_count 3\nh_sum 6.500000\nh_bucket{le=\"2.000000\"} 1\nh_bucket{le=\"+Inf\"} 3\n";
  EXPECT_EQ(expected, text(f));
  b = h->add_bucket(); b->set_upper_bound(std::numeric_limits<double>::infinity()); b->set_cumulative_count(3);
  EXPECT_EQ(expected, text(f));
  h->clear_bucket();
  EXPECT_EQ("# TYPE h histogram\nh_count 3\nh_sum 6.500000\nh_bucket{le=\"+Inf\"} 3\n", text(f));
}
