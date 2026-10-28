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
TEST(Md4c_permissive_url_autolinks, Case1) {
  EXPECT_EQ("<p>Homepage: <a href=\"https://github.com/mity/md4c\">https://github.com/mity/md4c</a></p>\n", render("Homepage: <https://github.com/mity/md4c>\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case2) {
  EXPECT_EQ("<p>Homepage: <a href=\"https://github.com/mity/md4c\">https://github.com/mity/md4c</a></p>\n", render("Homepage: https://github.com/mity/md4c\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case3) {
  EXPECT_EQ("<p>ssh://root@example.com</p>\n", render("ssh://root@example.com\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case4) {
  EXPECT_EQ("<p>Have you ever visited <a href=\"http://www.zombo.com\">http://www.zombo.com</a>?</p>\n", render("Have you ever visited http://www.zombo.com?\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case5) {
  EXPECT_EQ("<p><a href=\"http://www.bing.com/search?q=md4c\">http://www.bing.com/search?q=md4c</a></p>\n", render("http://www.bing.com/search?q=md4c\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case6) {
  EXPECT_EQ("<p><a href=\"http://commonmark.org\">http://commonmark.org</a></p>\n<p>(Visit <a href=\"https://encrypted.google.com/search?q=Markup+(business)\">https://encrypted.google.com/search?q=Markup+(business)</a>)</p>\n<p>Anonymous FTP is available at <a href=\"ftp://foo.bar.baz\">ftp://foo.bar.baz</a>.</p>\n", render("http://commonmark.org\n\n(Visit https://encrypted.google.com/search?q=Markup+(business))\n\nAnonymous FTP is available at ftp://foo.bar.baz.\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case7) {
  EXPECT_EQ("<p>This is <a href=\"http://github.com/\">link</a>.</p>\n", render("This is [link](http://github.com/).\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case8) {
  EXPECT_EQ("<p>This is <a href=\"http://github.com/\">link</a>X</p>\n", render("This is [link](http://github.com/)X\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case9) {
  EXPECT_EQ("<p><em>(<a href=\"http://example.com\">http://example.com</a>)</em></p>\n", render("*(http://example.com)*\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
TEST(Md4c_permissive_url_autolinks, Case10) {
  EXPECT_EQ("<p><a href=\"http://example.com\">http://example.com</a></p>\n", render("[http://example.com](http://example.com)\n", MD_FLAG_PERMISSIVEURLAUTOLINKS));
}
