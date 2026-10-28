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
TEST(Md4c_tasklists, Case1) {
  EXPECT_EQ("<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>foo</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>bar</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>baz</li>\n</ul>\n", render(" * [x] foo\n * [X] bar\n * [ ] baz\n", MD_FLAG_TASKLISTS));
}
TEST(Md4c_tasklists, Case2) {
  EXPECT_EQ("<ol>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>foo</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>bar</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>baz</li>\n</ol>\n", render(" 1. [x] foo\n 2. [X] bar\n 3. [ ] baz\n", MD_FLAG_TASKLISTS));
}
TEST(Md4c_tasklists, Case3) {
  EXPECT_EQ("<ul>\n<li>xxx:<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>foo</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>bar</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>baz</li>\n</ul>\n</li>\n<li>yyy:<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>qux</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>quux</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>quuz</li>\n</ul>\n</li>\n</ul>\n", render(" * xxx:\n   * [x] foo\n   * [x] bar\n   * [ ] baz\n * yyy:\n   * [ ] qux\n   * [x] quux\n   * [ ] quuz\n", MD_FLAG_TASKLISTS));
}
TEST(Md4c_tasklists, Case4) {
  EXPECT_EQ("<ol>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>xxx:<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>foo</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>bar</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>baz</li>\n</ul>\n</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>yyy:<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>qux</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>quux</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>quuz</li>\n</ul>\n</li>\n</ol>\n", render(" 1. [x] xxx:\n    * [x] foo\n    * [x] bar\n    * [ ] baz\n 2. [ ] yyy:\n    * [ ] qux\n    * [x] quux\n    * [ ] quuz\n", MD_FLAG_TASKLISTS));
}
TEST(Md4c_tasklists, Case5) {
  EXPECT_EQ("<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled checked>xxx:<ul>\n<li>foo</li>\n<li>bar</li>\n<li>baz</li>\n</ul>\n</li>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>yyy:<ul>\n<li>qux</li>\n<li>quux</li>\n<li>quuz</li>\n</ul>\n</li>\n</ul>\n", render(" * [x] xxx:\n   * foo\n   * bar\n   * baz\n * [ ] yyy:\n   * qux\n   * quux\n   * quuz\n", MD_FLAG_TASKLISTS));
}
