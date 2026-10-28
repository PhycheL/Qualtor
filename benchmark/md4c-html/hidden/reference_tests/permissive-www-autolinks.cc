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
TEST(Md4c_permissive_www_autolinks, Case1) {
  EXPECT_EQ("<p><a href=\"http://www.commonmark.org\">www.commonmark.org</a></p>\n", render("www.commonmark.org\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case2) {
  EXPECT_EQ("<p>Visit <a href=\"http://www.commonmark.org/help\">www.commonmark.org/help</a> for more information.</p>\n", render("Visit www.commonmark.org/help for more information.\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case3) {
  EXPECT_EQ("<p>Visit <a href=\"http://www.commonmark.org\">www.commonmark.org</a>.</p>\n<p>Visit <a href=\"http://www.commonmark.org/a.b\">www.commonmark.org/a.b</a>.</p>\n", render("Visit www.commonmark.org.\n\nVisit www.commonmark.org/a.b.\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case4) {
  EXPECT_EQ("<p><a href=\"http://www.google.com/search?q=Markup+(business)\">www.google.com/search?q=Markup+(business)</a></p>\n<p>(<a href=\"http://www.google.com/search?q=Markup+(business)\">www.google.com/search?q=Markup+(business)</a>)</p>\n", render("www.google.com/search?q=Markup+(business)\n\n(www.google.com/search?q=Markup+(business))\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case5) {
  EXPECT_EQ("<p><a href=\"http://www.google.com/search?q=(business))+ok\">www.google.com/search?q=(business))+ok</a></p>\n", render("www.google.com/search?q=(business))+ok\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case6) {
  EXPECT_EQ("<p><a href=\"http://www.google.com/search?q=commonmark&amp;hl=en\">www.google.com/search?q=commonmark&amp;hl=en</a></p>\n<p><a href=\"http://www.google.com/search?q=commonmark\">www.google.com/search?q=commonmark</a>&amp;hl;</p>\n", render("www.google.com/search?q=commonmark&hl=en\n\nwww.google.com/search?q=commonmark&hl;\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case7) {
  EXPECT_EQ("<p><a href=\"http://www.commonmark.org/he\">www.commonmark.org/he</a>&lt;lp</p>\n", render("www.commonmark.org/he<lp\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case8) {
  EXPECT_EQ("<p>This is <a href=\"www.github.com/\">link</a>.</p>\n", render("This is [link](www.github.com/).\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
TEST(Md4c_permissive_www_autolinks, Case9) {
  EXPECT_EQ("<p>This is <a href=\"www.github.com/\">link</a>X</p>\n", render("This is [link](www.github.com/)X\n", MD_FLAG_PERMISSIVEWWWAUTOLINKS));
}
