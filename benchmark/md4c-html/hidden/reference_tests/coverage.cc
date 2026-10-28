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
TEST(Md4c_coverage, Case1) {
  EXPECT_EQ("<gi att1=tok1 att2=tok2>\n", render("<gi att1=tok1 att2=tok2>\n", 0));
}
TEST(Md4c_coverage, Case2) {
  EXPECT_EQ("<p>foo <gi att1=tok1 att2=tok2> bar</p>\n", render("foo <gi att1=tok1 att2=tok2> bar\n", 0));
}
TEST(Md4c_coverage, Case3) {
  EXPECT_EQ("<p>foo <gi att1=tok1\natt2=tok2> bar</p>\n", render("foo <gi att1=tok1\natt2=tok2> bar\n", 0));
}
TEST(Md4c_coverage, Case4) {
  EXPECT_EQ("<p><img src=\"img.png\" alt=\"alt text with entity ©\" title=\"title\"></p>\n", render("![alt text with *entity* &copy;](img.png 'title')\n", 0));
}
TEST(Md4c_coverage, Case5) {
  EXPECT_EQ("<blockquote>\n<p><a href=\"/url\">foo bar</a></p>\n</blockquote>\n", render("> [foo\n> bar]: /url\n>\n> [foo bar]\n", 0));
}
TEST(Md4c_coverage, Case6) {
  EXPECT_EQ("<ul>\n<li><?\n\nx\n</li>\n</ul>\n", render("[x]:\nx\n- <?\n\n  x\n", 0));
}
TEST(Md4c_coverage, Case7) {
  EXPECT_EQ("<p>x <a href=\"/url\" title=\"foo – bar\">link</a> x</p>\n", render("x [link](/url \"foo &ndash; bar\") x\n", 0));
}
TEST(Md4c_coverage, Case8) {
  EXPECT_EQ("<p>a*<em><em>b</em> c</em></p>\n", render("a***b* c*\n", 0));
}
TEST(Md4c_coverage, Case9) {
  EXPECT_EQ("<p>*<em><em>b</em> c</em></p>\n", render("***b* c*\n", 0));
}
TEST(Md4c_coverage, Case10) {
  EXPECT_EQ("<p>a<em>b**c</em></p>\n", render("a*b**c*\n", 0));
}
TEST(Md4c_coverage, Case11) {
  EXPECT_EQ("<pre><code class=\"language-&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;\"></code></pre>\n", render("```&amp;&amp;&amp;&amp;&amp;&amp;&amp;&amp;\n", 0));
}
TEST(Md4c_coverage, Case12) {
  EXPECT_EQ("<p><em><em>x</em> <em>x</em></em>_</p>\n", render("__x_ _x___\n", 0));
}
TEST(Md4c_coverage, Case13) {
  EXPECT_EQ("", render("[\\\\]: x\n", 0));
}
TEST(Md4c_coverage, Case14) {
  EXPECT_EQ("<p><a href=\"url\" title=\"title\">x</a>x</p>\n", render("[x](url\n'title'\n)x\n", 0));
}
TEST(Md4c_coverage, Case15) {
  EXPECT_EQ("<p>`</p>\n", render("`\n", 0));
}
TEST(Md4c_coverage, Case16) {
  EXPECT_EQ("<pre><code>xx\n</code></pre>\n<ul>\n<li></li>\n</ul>\n", render("[f]:\n-\n    xx\n-\n", 0));
}
TEST(Md4c_coverage, Case17) {
  EXPECT_EQ("<p><a href=\"/url\">ẞ SS</a></p>\n", render("[SS ẞ]: /url\n[ẞ SS]\n", 0));
}
TEST(Md4c_coverage, Case18) {
  EXPECT_EQ("<p>foo</p>\n<blockquote>\n</blockquote>\n", render("foo\n>\n", 0));
}
TEST(Md4c_coverage, Case19) {
  EXPECT_EQ("<p>. foo</p>\n", render(". foo\n", 0));
}
TEST(Md4c_coverage, Case20) {
  EXPECT_EQ("<p>[a] <a href=\"/foo\">ab</a> [abc]</p>\n", render("[ab]: /foo\n[a] [ab] [abc]\n", 0));
}
TEST(Md4c_coverage, Case21) {
  EXPECT_EQ("<p><a href=\"/foo\">a   b</a></p>\n", render("[a b]: /foo\n[a   b]\n", 0));
}
TEST(Md4c_coverage, Case22) {
  EXPECT_EQ("<p><em>a <em><em>b c</em> d</em></em></p>\n", render("*a **b c* d**\n", 0));
}
TEST(Md4c_coverage, Case23) {
  EXPECT_EQ("<p><a href=\"mailto:foo@123456789012345678901234567890123456789012345678901234567890123.123456789012345678901234567890123456789012345678901234567890123\">foo@123456789012345678901234567890123456789012345678901234567890123.123456789012345678901234567890123456789012345678901234567890123</a></p>\n", render("<foo@123456789012345678901234567890123456789012345678901234567890123.123456789012345678901234567890123456789012345678901234567890123>\n", 0));
}
TEST(Md4c_coverage, Case24) {
  EXPECT_EQ("<p>&lt;foo@123456789012345678901234567890123456789012345678901234567890123x.123456789012345678901234567890123456789012345678901234567890123&gt;</p>\n", render("<foo@123456789012345678901234567890123456789012345678901234567890123x.123456789012345678901234567890123456789012345678901234567890123>\n", 0));
}
TEST(Md4c_coverage, Case25) {
  EXPECT_EQ("<p>*<strong>foo <em>bar baz</em></strong></p>\n", render("***foo *bar baz***\n", 0));
}
TEST(Md4c_coverage, Case26) {
  EXPECT_EQ("<pre><code>                x\n</code></pre>\n<pre><code>                 x\n</code></pre>\n", render("~~~\n                x\n~~~\n\n~~~\n                 x\n~~~\n", 0));
}
TEST(Md4c_coverage, Case27) {
  EXPECT_EQ("<p><a href=\"link_url\"><img src=\"img_url\" alt=\"alt\"></a></p>\n", render("[![alt][img]][link]\n\n[img]: img_url\n[link]: link_url\n", 0));
}
TEST(Md4c_coverage, Case28) {
  EXPECT_EQ("<p>[fooﬕ]</p>\n", render("[fooﬗ]: /url\n[fooﬕ]\n", 0));
}
TEST(Md4c_coverage, Case29) {
  EXPECT_EQ("<ul>\n<li><script>\n</li>\n<li>foo\nbar\n</script></li>\n</ul>\n", render("- <script>\n- foo\nbar\n</script>\n", 0));
}
TEST(Md4c_coverage, Case30) {
  EXPECT_EQ("<p>*foo *bar</p>\n", render("*foo *bar\n", 0));
}
TEST(Md4c_coverage, Case31) {
  EXPECT_EQ("<p>*foo¡*bar</p>\n", render("*foo¡*bar\n", 0));
}
TEST(Md4c_coverage, Case32) {
  EXPECT_EQ("<p><a href=\"/url\">Příliš žluťoučký kůň úpěl ďábelské ódy.</a></p>\n", render("[Příliš žluťoučký kůň úpěl ďábelské ódy.]\n\n[PŘÍLIŠ ŽLUŤOUČKÝ KŮŇ ÚPĚL ĎÁBELSKÉ ÓDY.]: /url\n", 0));
}
TEST(Md4c_coverage, Case33) {
  EXPECT_EQ("<p>á*Á (U+00E1, i.e. two byte UTF-8 sequence)\n *  (U+2000, i.e. three byte UTF-8 sequence)</p>\n", render("á*Á (U+00E1, i.e. two byte UTF-8 sequence)\n *  (U+2000, i.e. three byte UTF-8 sequence)\n", 0));
}
TEST(Md4c_coverage, Case34) {
  EXPECT_EQ("<p><a href=\"/url.with.escape\">link</a></p>\n", render("[link](</url\\.with\\.escape>)\n", 0));
}
TEST(Md4c_coverage, Case35) {
  EXPECT_EQ("<p><a href=\"/url\">foo bar</a></p>\n", render("[foo bar]\n\n[foo bar]: /url\n", 0));
}
TEST(Md4c_coverage, Case36) {
  EXPECT_EQ("<blockquote>\n<p><a href=\"/url\" title=\"foo\nbar\">link</a></p>\n</blockquote>\n", render("> [link](/url 'foo\n> bar')\n", 0));
}
TEST(Md4c_coverage, Case37) {
  EXPECT_EQ("<p><a href=\"/foo\">foo</a>\n<a href=\"/qnptgbh\">qnptgbh</a>\n<a href=\"/abgbrwcv\">abgbrwcv</a>\n<a href=\"/alqadfgn\">alqadfgn</a>\n[axgydtdu]</p>\n", render("[foo]: /foo\n[qnptgbh]: /qnptgbh\n[abgbrwcv]: /abgbrwcv\n[abgbrwcv]: /abgbrwcv2\n[abgbrwcv]: /abgbrwcv3\n[abgbrwcv]: /abgbrwcv4\n[alqadfgn]: /alqadfgn\n\n[foo]\n[qnptgbh]\n[abgbrwcv]\n[alqadfgn]\n[axgydtdu]\n", 0));
}
