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
TEST(Md4c_permissive_email_autolinks, Case1) {
  EXPECT_EQ("<p>E-mail: <a href=\"mailto:john.doe@gmail.com\">mailto:john.doe@gmail.com</a></p>\n", render("E-mail: <mailto:john.doe@gmail.com>\n", MD_FLAG_PERMISSIVEEMAILAUTOLINKS));
}
TEST(Md4c_permissive_email_autolinks, Case2) {
  EXPECT_EQ("<p>E-mail: <a href=\"mailto:john.doe@gmail.com\">john.doe@gmail.com</a></p>\n", render("E-mail: john.doe@gmail.com\n", MD_FLAG_PERMISSIVEEMAILAUTOLINKS));
}
TEST(Md4c_permissive_email_autolinks, Case3) {
  EXPECT_EQ("<p>hello@mail+xyz.example isn't valid, but <a href=\"mailto:hello+xyz@mail.example\">hello+xyz@mail.example</a> is.</p>\n", render("hello@mail+xyz.example isn't valid, but hello+xyz@mail.example is.\n", MD_FLAG_PERMISSIVEEMAILAUTOLINKS));
}
TEST(Md4c_permissive_email_autolinks, Case4) {
  EXPECT_EQ("<p><a href=\"mailto:a.b-c_d@a.b\">a.b-c_d@a.b</a></p>\n<p><a href=\"mailto:a.b-c_d@a.b\">a.b-c_d@a.b</a>.</p>\n<p>a.b-c_d@a.b-</p>\n<p>a.b-c_d@a.b_</p>\n", render("a.b-c_d@a.b\n\na.b-c_d@a.b.\n\na.b-c_d@a.b-\n\na.b-c_d@a.b_\n", MD_FLAG_PERMISSIVEEMAILAUTOLINKS));
}
