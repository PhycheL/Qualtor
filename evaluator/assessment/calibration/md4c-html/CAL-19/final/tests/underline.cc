// 上游 Markdown 输入和预期 HTML 转为 C++11 GoogleTest，转换工具 import_step_a.py。
#include <gtest/gtest.h>
#include <string>
#include "md4c-html.h"
static void append_html(const char* s, MD_SIZE n, void* p) { static_cast<std::string*>(p)->append(s,n); }
static std::string render(const std::string& input, unsigned flags, unsigned renderer=0) {
  std::string output;
  EXPECT_EQ(0, md_html(input.data(), input.size(), append_html, &output, flags, renderer));
  return output;
}
TEST(Md4c_underline, Case1) {
  EXPECT_EQ("<p><u>foo</u></p>\n", render("_foo_\n", MD_FLAG_UNDERLINE));
}
TEST(Md4c_underline, Case2) {
  EXPECT_EQ("<p><u><u><u>foo</u></u></u></p>\n", render("___foo___\n", MD_FLAG_UNDERLINE));
}
TEST(Md4c_underline, Case3) {
  EXPECT_EQ("<p>foo_bar_baz</p>\n", render("foo_bar_baz\n", MD_FLAG_UNDERLINE));
}
TEST(Md4c_underline, Case4) {
  EXPECT_EQ("<p>_foo _bar</p>\n", render("_foo _bar\n", MD_FLAG_UNDERLINE));
}
