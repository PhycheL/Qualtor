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
TEST(Md4c_latex_math, Case1) {
  EXPECT_EQ("<p><x-equation>a+b=c</x-equation> Hello, world!</p>\n", render("$a+b=c$ Hello, world!\n", MD_FLAG_LATEXMATHSPANS));
}
TEST(Md4c_latex_math, Case2) {
  EXPECT_EQ("<p>This is a display equation: <x-equation type=\"display\">\\int_a^b x dx</x-equation>.</p>\n", render("This is a display equation: $$\\int_a^b x dx$$.\n", MD_FLAG_LATEXMATHSPANS));
}
TEST(Md4c_latex_math, Case3) {
  EXPECT_EQ("<p><x-equation type=\"display\">\\int_a^b f(x) dx </x-equation></p>\n", render("$$\n\\int_a^b\nf(x) dx\n$$\n", MD_FLAG_LATEXMATHSPANS));
}
