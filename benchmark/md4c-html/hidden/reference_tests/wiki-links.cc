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
TEST(Md4c_wiki_links, Case1) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">foo</x-wikilink></p>\n", render("[[foo]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case2) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">bar</x-wikilink></p>\n", render("[[foo|bar]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case3) {
  EXPECT_EQ("<p>[[]]</p>\n", render("[[]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case4) {
  EXPECT_EQ("<p>[[|foo]]</p>\n", render("[[|foo]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case5) {
  EXPECT_EQ("<p>[[foo\nbar]]</p>\n", render("[[foo\nbar]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case6) {
  EXPECT_EQ("<p>[[foo\nbar|baz]]</p>\n", render("[[foo\nbar|baz]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case7) {
  EXPECT_EQ("<p><x-wikilink data-target=\"*foo*\">*foo*</x-wikilink></p>\n", render("[[*foo*]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case8) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\"><img src=\"bar.jpg\" alt=\"bar\"></x-wikilink></p>\n", render("[[foo|![bar](bar.jpg)]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case9) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">bar|baz</x-wikilink></p>\n", render("[[foo|bar|baz]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case10) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo|bar\">baz</x-wikilink></p>\n", render("[[foo\\|bar|baz]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case11) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\"><em>bar</em></x-wikilink></p>\n", render("[[foo|*bar*]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case12) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">foo</x-wikilink></p>\n", render("[[foo|]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case13) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">foo\nbar\nbaz</x-wikilink></p>\n", render("[[foo|foo\nbar\nbaz]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case14) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">foo</x-wikilink>(foo.jpg)</p>\n", render("[[foo]](foo.jpg)\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case15) {
  EXPECT_EQ("<p><x-wikilink data-target=\"foo\">foo</x-wikilink></p>\n", render("[foo]: /url\n\n[[foo]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case16) {
  EXPECT_EQ("<p>| A                | B   |\n|------------------|-----|\n| <x-wikilink data-target=\"foo\"><em>bar</em></x-wikilink>    | baz |</p>\n", render("| A                | B   |\n|------------------|-----|\n| [[foo|*bar*]]    | baz |\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case17) {
  EXPECT_EQ("<p><img src=\"foo.jpg\" alt=\"[foo]\"></p>\n", render("![[foo]](foo.jpg)\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case18) {
  EXPECT_EQ("<p>[<a href=\"/url\">foo</a></p>\n", render("[[foo]\n\n[foo]: /url\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case19) {
  EXPECT_EQ("<p>[<a href=\"/url\">foo</a>]</p>\n", render("\\[[foo]]\n\n[foo]: /url\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case20) {
  EXPECT_EQ("<p>[[foo<x-wikilink data-target=\"bar\">bar</x-wikilink>]]</p>\n", render("[[foo[[bar]]]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case21) {
  EXPECT_EQ("<p>[[12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901]]\n[[12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901|foo]]</p>\n", render("[[12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901]]\n[[12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901|foo]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case22) {
  EXPECT_EQ("<p><x-wikilink data-target=\"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\">1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890</x-wikilink>\n<x-wikilink data-target=\"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\">foo</x-wikilink></p>\n", render("[[1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890]]\n[[1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890|foo]]\n", MD_FLAG_WIKILINKS));
}
TEST(Md4c_wiki_links, Case23) {
  EXPECT_EQ("<blockquote>\n<p><x-wikilink data-target=\"12345678901234567890123456789012345678901234567890\">1234567890\n1234567890\n1234567890\n1234567890\n123456789</x-wikilink></p>\n</blockquote>\n", render("> [[12345678901234567890123456789012345678901234567890|1234567890\n> 1234567890\n> 1234567890\n> 1234567890\n> 123456789]]\n", MD_FLAG_WIKILINKS));
}
