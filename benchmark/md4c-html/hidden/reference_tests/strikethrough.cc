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
TEST(Md4c_strikethrough, Case1) {
  EXPECT_EQ("<p><del>Hi</del> Hello, world!</p>\n", render("~Hi~ Hello, world!\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case2) {
  EXPECT_EQ("<p>This ~text~~ is curious.</p>\n", render("This ~text~~ is curious.\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case3) {
  EXPECT_EQ("<p>foo ~~~bar~~~</p>\n", render("foo ~~~bar~~~\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case4) {
  EXPECT_EQ("<p>~foo ~bar</p>\n", render("~foo ~bar\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case5) {
  EXPECT_EQ("<p>This ~~has a</p>\n<p>new paragraph~~.</p>\n", render("This ~~has a\n\nnew paragraph~~.\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case6) {
  EXPECT_EQ("<p><del><code>foo</code></del></p>\n", render("~`foo`~\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case7) {
  EXPECT_EQ("<p><del><em>foo</em></del></p>\n", render("~*foo*~\n", MD_FLAG_STRIKETHROUGH));
}
TEST(Md4c_strikethrough, Case8) {
  EXPECT_EQ("<p><em><del>foo</del></em></p>\n", render("*~foo~*\n", MD_FLAG_STRIKETHROUGH));
}
