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
TEST(Md4c_spec, Case1) {
  EXPECT_EQ("<pre><code>foo\tbaz\t\tbim\n</code></pre>\n", render("\tfoo\tbaz\t\tbim\n", 0));
}
TEST(Md4c_spec, Case2) {
  EXPECT_EQ("<pre><code>foo\tbaz\t\tbim\n</code></pre>\n", render("  \tfoo\tbaz\t\tbim\n", 0));
}
TEST(Md4c_spec, Case3) {
  EXPECT_EQ("<pre><code>a\ta\nὐ\ta\n</code></pre>\n", render("    a\ta\n    ὐ\ta\n", 0));
}
TEST(Md4c_spec, Case4) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<p>bar</p>\n</li>\n</ul>\n", render("  - foo\n\n\tbar\n", 0));
}
TEST(Md4c_spec, Case5) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<pre><code>  bar\n</code></pre>\n</li>\n</ul>\n", render("- foo\n\n\t\tbar\n", 0));
}
TEST(Md4c_spec, Case6) {
  EXPECT_EQ("<blockquote>\n<pre><code>  foo\n</code></pre>\n</blockquote>\n", render(">\t\tfoo\n", 0));
}
TEST(Md4c_spec, Case7) {
  EXPECT_EQ("<ul>\n<li><pre><code>  foo\n</code></pre>\n</li>\n</ul>\n", render("-\t\tfoo\n", 0));
}
TEST(Md4c_spec, Case8) {
  EXPECT_EQ("<pre><code>foo\nbar\n</code></pre>\n", render("    foo\n\tbar\n", 0));
}
TEST(Md4c_spec, Case9) {
  EXPECT_EQ("<ul>\n<li>foo<ul>\n<li>bar<ul>\n<li>baz</li>\n</ul>\n</li>\n</ul>\n</li>\n</ul>\n", render(" - foo\n   - bar\n\t - baz\n", 0));
}
TEST(Md4c_spec, Case10) {
  EXPECT_EQ("<h1>\tFoo</h1>\n", render("#\tFoo\n", 0));
}
TEST(Md4c_spec, Case11) {
  EXPECT_EQ("<hr>\n", render("*\t*\t*\t\n", 0));
}
TEST(Md4c_spec, Case12) {
  EXPECT_EQ("<ul>\n<li>`one</li>\n<li>two`</li>\n</ul>\n", render("- `one\n- two`\n", 0));
}
TEST(Md4c_spec, Case13) {
  EXPECT_EQ("<hr>\n<hr>\n<hr>\n", render("***\n---\n___\n", 0));
}
TEST(Md4c_spec, Case14) {
  EXPECT_EQ("<p>+++</p>\n", render("+++\n", 0));
}
TEST(Md4c_spec, Case15) {
  EXPECT_EQ("<p>===</p>\n", render("===\n", 0));
}
TEST(Md4c_spec, Case16) {
  EXPECT_EQ("<p>--\n**\n__</p>\n", render("--\n**\n__\n", 0));
}
TEST(Md4c_spec, Case17) {
  EXPECT_EQ("<hr>\n<hr>\n<hr>\n", render(" ***\n  ***\n   ***\n", 0));
}
TEST(Md4c_spec, Case18) {
  EXPECT_EQ("<pre><code>***\n</code></pre>\n", render("    ***\n", 0));
}
TEST(Md4c_spec, Case19) {
  EXPECT_EQ("<p>Foo\n***</p>\n", render("Foo\n    ***\n", 0));
}
TEST(Md4c_spec, Case20) {
  EXPECT_EQ("<hr>\n", render("_____________________________________\n", 0));
}
TEST(Md4c_spec, Case21) {
  EXPECT_EQ("<hr>\n", render(" - - -\n", 0));
}
TEST(Md4c_spec, Case22) {
  EXPECT_EQ("<hr>\n", render(" **  * ** * ** * **\n", 0));
}
TEST(Md4c_spec, Case23) {
  EXPECT_EQ("<hr>\n", render("-     -      -      -\n", 0));
}
TEST(Md4c_spec, Case24) {
  EXPECT_EQ("<hr>\n", render("- - - -    \n", 0));
}
TEST(Md4c_spec, Case25) {
  EXPECT_EQ("<p>_ _ _ _ a</p>\n<p>a------</p>\n<p>---a---</p>\n", render("_ _ _ _ a\n\na------\n\n---a---\n", 0));
}
TEST(Md4c_spec, Case26) {
  EXPECT_EQ("<p><em>-</em></p>\n", render(" *-*\n", 0));
}
TEST(Md4c_spec, Case27) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n</ul>\n<hr>\n<ul>\n<li>bar</li>\n</ul>\n", render("- foo\n***\n- bar\n", 0));
}
TEST(Md4c_spec, Case28) {
  EXPECT_EQ("<p>Foo</p>\n<hr>\n<p>bar</p>\n", render("Foo\n***\nbar\n", 0));
}
TEST(Md4c_spec, Case29) {
  EXPECT_EQ("<h2>Foo</h2>\n<p>bar</p>\n", render("Foo\n---\nbar\n", 0));
}
TEST(Md4c_spec, Case30) {
  EXPECT_EQ("<ul>\n<li>Foo</li>\n</ul>\n<hr>\n<ul>\n<li>Bar</li>\n</ul>\n", render("* Foo\n* * *\n* Bar\n", 0));
}
TEST(Md4c_spec, Case31) {
  EXPECT_EQ("<ul>\n<li>Foo</li>\n<li><hr>\n</li>\n</ul>\n", render("- Foo\n- * * *\n", 0));
}
TEST(Md4c_spec, Case32) {
  EXPECT_EQ("<h1>foo</h1>\n<h2>foo</h2>\n<h3>foo</h3>\n<h4>foo</h4>\n<h5>foo</h5>\n<h6>foo</h6>\n", render("# foo\n## foo\n### foo\n#### foo\n##### foo\n###### foo\n", 0));
}
TEST(Md4c_spec, Case33) {
  EXPECT_EQ("<p>####### foo</p>\n", render("####### foo\n", 0));
}
TEST(Md4c_spec, Case34) {
  EXPECT_EQ("<p>#5 bolt</p>\n<p>#hashtag</p>\n", render("#5 bolt\n\n#hashtag\n", 0));
}
TEST(Md4c_spec, Case35) {
  EXPECT_EQ("<p>## foo</p>\n", render("\\## foo\n", 0));
}
TEST(Md4c_spec, Case36) {
  EXPECT_EQ("<h1>foo <em>bar</em> *baz*</h1>\n", render("# foo *bar* \\*baz\\*\n", 0));
}
TEST(Md4c_spec, Case37) {
  EXPECT_EQ("<h1>foo</h1>\n", render("#                  foo                     \n", 0));
}
TEST(Md4c_spec, Case38) {
  EXPECT_EQ("<h3>foo</h3>\n<h2>foo</h2>\n<h1>foo</h1>\n", render(" ### foo\n  ## foo\n   # foo\n", 0));
}
TEST(Md4c_spec, Case39) {
  EXPECT_EQ("<pre><code># foo\n</code></pre>\n", render("    # foo\n", 0));
}
TEST(Md4c_spec, Case40) {
  EXPECT_EQ("<p>foo\n# bar</p>\n", render("foo\n    # bar\n", 0));
}
TEST(Md4c_spec, Case41) {
  EXPECT_EQ("<h2>foo</h2>\n<h3>bar</h3>\n", render("## foo ##\n  ###   bar    ###\n", 0));
}
TEST(Md4c_spec, Case42) {
  EXPECT_EQ("<h1>foo</h1>\n<h5>foo</h5>\n", render("# foo ##################################\n##### foo ##\n", 0));
}
TEST(Md4c_spec, Case43) {
  EXPECT_EQ("<h3>foo</h3>\n", render("### foo ###     \n", 0));
}
TEST(Md4c_spec, Case44) {
  EXPECT_EQ("<h3>foo ### b</h3>\n", render("### foo ### b\n", 0));
}
TEST(Md4c_spec, Case45) {
  EXPECT_EQ("<h1>foo#</h1>\n", render("# foo#\n", 0));
}
TEST(Md4c_spec, Case46) {
  EXPECT_EQ("<h3>foo ###</h3>\n<h2>foo ###</h2>\n<h1>foo #</h1>\n", render("### foo \\###\n## foo #\\##\n# foo \\#\n", 0));
}
TEST(Md4c_spec, Case47) {
  EXPECT_EQ("<hr>\n<h2>foo</h2>\n<hr>\n", render("****\n## foo\n****\n", 0));
}
TEST(Md4c_spec, Case48) {
  EXPECT_EQ("<p>Foo bar</p>\n<h1>baz</h1>\n<p>Bar foo</p>\n", render("Foo bar\n# baz\nBar foo\n", 0));
}
TEST(Md4c_spec, Case49) {
  EXPECT_EQ("<h2></h2>\n<h1></h1>\n<h3></h3>\n", render("## \n#\n### ###\n", 0));
}
TEST(Md4c_spec, Case50) {
  EXPECT_EQ("<h1>Foo <em>bar</em></h1>\n<h2>Foo <em>bar</em></h2>\n", render("Foo *bar*\n=========\n\nFoo *bar*\n---------\n", 0));
}
TEST(Md4c_spec, Case51) {
  EXPECT_EQ("<h1>Foo <em>bar\nbaz</em></h1>\n", render("Foo *bar\nbaz*\n====\n", 0));
}
TEST(Md4c_spec, Case52) {
  EXPECT_EQ("<h1>Foo <em>bar\nbaz</em>\t</h1>\n", render("  Foo *bar\nbaz*\t\n====\n", 0));
}
TEST(Md4c_spec, Case53) {
  EXPECT_EQ("<h2>Foo</h2>\n<h1>Foo</h1>\n", render("Foo\n-------------------------\n\nFoo\n=\n", 0));
}
TEST(Md4c_spec, Case54) {
  EXPECT_EQ("<h2>Foo</h2>\n<h2>Foo</h2>\n<h1>Foo</h1>\n", render("   Foo\n---\n\n  Foo\n-----\n\n  Foo\n  ===\n", 0));
}
TEST(Md4c_spec, Case55) {
  EXPECT_EQ("<pre><code>Foo\n---\n\nFoo\n</code></pre>\n<hr>\n", render("    Foo\n    ---\n\n    Foo\n---\n", 0));
}
TEST(Md4c_spec, Case56) {
  EXPECT_EQ("<h2>Foo</h2>\n", render("Foo\n   ----      \n", 0));
}
TEST(Md4c_spec, Case57) {
  EXPECT_EQ("<p>Foo\n---</p>\n", render("Foo\n    ---\n", 0));
}
TEST(Md4c_spec, Case58) {
  EXPECT_EQ("<p>Foo\n= =</p>\n<p>Foo</p>\n<hr>\n", render("Foo\n= =\n\nFoo\n--- -\n", 0));
}
TEST(Md4c_spec, Case59) {
  EXPECT_EQ("<h2>Foo</h2>\n", render("Foo  \n-----\n", 0));
}
TEST(Md4c_spec, Case60) {
  EXPECT_EQ("<h2>Foo\\</h2>\n", render("Foo\\\n----\n", 0));
}
TEST(Md4c_spec, Case61) {
  EXPECT_EQ("<h2>`Foo</h2>\n<p>`</p>\n<h2>&lt;a title=&quot;a lot</h2>\n<p>of dashes&quot;/&gt;</p>\n", render("`Foo\n----\n`\n\n<a title=\"a lot\n---\nof dashes\"/>\n", 0));
}
TEST(Md4c_spec, Case62) {
  EXPECT_EQ("<blockquote>\n<p>Foo</p>\n</blockquote>\n<hr>\n", render("> Foo\n---\n", 0));
}
TEST(Md4c_spec, Case63) {
  EXPECT_EQ("<blockquote>\n<p>foo\nbar\n===</p>\n</blockquote>\n", render("> foo\nbar\n===\n", 0));
}
TEST(Md4c_spec, Case64) {
  EXPECT_EQ("<ul>\n<li>Foo</li>\n</ul>\n<hr>\n", render("- Foo\n---\n", 0));
}
TEST(Md4c_spec, Case65) {
  EXPECT_EQ("<h2>Foo\nBar</h2>\n", render("Foo\nBar\n---\n", 0));
}
TEST(Md4c_spec, Case66) {
  EXPECT_EQ("<hr>\n<h2>Foo</h2>\n<h2>Bar</h2>\n<p>Baz</p>\n", render("---\nFoo\n---\nBar\n---\nBaz\n", 0));
}
TEST(Md4c_spec, Case67) {
  EXPECT_EQ("<p>====</p>\n", render("\n====\n", 0));
}
TEST(Md4c_spec, Case68) {
  EXPECT_EQ("<hr>\n<hr>\n", render("---\n---\n", 0));
}
TEST(Md4c_spec, Case69) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n</ul>\n<hr>\n", render("- foo\n-----\n", 0));
}
TEST(Md4c_spec, Case70) {
  EXPECT_EQ("<pre><code>foo\n</code></pre>\n<hr>\n", render("    foo\n---\n", 0));
}
TEST(Md4c_spec, Case71) {
  EXPECT_EQ("<blockquote>\n<p>foo</p>\n</blockquote>\n<hr>\n", render("> foo\n-----\n", 0));
}
TEST(Md4c_spec, Case72) {
  EXPECT_EQ("<h2>&gt; foo</h2>\n", render("\\> foo\n------\n", 0));
}
TEST(Md4c_spec, Case73) {
  EXPECT_EQ("<p>Foo</p>\n<h2>bar</h2>\n<p>baz</p>\n", render("Foo\n\nbar\n---\nbaz\n", 0));
}
TEST(Md4c_spec, Case74) {
  EXPECT_EQ("<p>Foo\nbar</p>\n<hr>\n<p>baz</p>\n", render("Foo\nbar\n\n---\n\nbaz\n", 0));
}
TEST(Md4c_spec, Case75) {
  EXPECT_EQ("<p>Foo\nbar</p>\n<hr>\n<p>baz</p>\n", render("Foo\nbar\n* * *\nbaz\n", 0));
}
TEST(Md4c_spec, Case76) {
  EXPECT_EQ("<p>Foo\nbar\n---\nbaz</p>\n", render("Foo\nbar\n\\---\nbaz\n", 0));
}
TEST(Md4c_spec, Case77) {
  EXPECT_EQ("<pre><code>a simple\n  indented code block\n</code></pre>\n", render("    a simple\n      indented code block\n", 0));
}
TEST(Md4c_spec, Case78) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<p>bar</p>\n</li>\n</ul>\n", render("  - foo\n\n    bar\n", 0));
}
TEST(Md4c_spec, Case79) {
  EXPECT_EQ("<ol>\n<li><p>foo</p>\n<ul>\n<li>bar</li>\n</ul>\n</li>\n</ol>\n", render("1.  foo\n\n    - bar\n", 0));
}
TEST(Md4c_spec, Case80) {
  EXPECT_EQ("<pre><code>&lt;a/&gt;\n*hi*\n\n- one\n</code></pre>\n", render("    <a/>\n    *hi*\n\n    - one\n", 0));
}
TEST(Md4c_spec, Case81) {
  EXPECT_EQ("<pre><code>chunk1\n\nchunk2\n\n\n\nchunk3\n</code></pre>\n", render("    chunk1\n\n    chunk2\n  \n \n \n    chunk3\n", 0));
}
TEST(Md4c_spec, Case82) {
  EXPECT_EQ("<pre><code>chunk1\n  \n  chunk2\n</code></pre>\n", render("    chunk1\n      \n      chunk2\n", 0));
}
TEST(Md4c_spec, Case83) {
  EXPECT_EQ("<p>Foo\nbar</p>\n", render("Foo\n    bar\n\n", 0));
}
TEST(Md4c_spec, Case84) {
  EXPECT_EQ("<pre><code>foo\n</code></pre>\n<p>bar</p>\n", render("    foo\nbar\n", 0));
}
TEST(Md4c_spec, Case85) {
  EXPECT_EQ("<h1>Heading</h1>\n<pre><code>foo\n</code></pre>\n<h2>Heading</h2>\n<pre><code>foo\n</code></pre>\n<hr>\n", render("# Heading\n    foo\nHeading\n------\n    foo\n----\n", 0));
}
TEST(Md4c_spec, Case86) {
  EXPECT_EQ("<pre><code>    foo\nbar\n</code></pre>\n", render("        foo\n    bar\n", 0));
}
TEST(Md4c_spec, Case87) {
  EXPECT_EQ("<pre><code>foo\n</code></pre>\n", render("\n    \n    foo\n    \n\n", 0));
}
TEST(Md4c_spec, Case88) {
  EXPECT_EQ("<pre><code>foo  \n</code></pre>\n", render("    foo  \n", 0));
}
TEST(Md4c_spec, Case89) {
  EXPECT_EQ("<pre><code>&lt;\n &gt;\n</code></pre>\n", render("```\n<\n >\n```\n", 0));
}
TEST(Md4c_spec, Case90) {
  EXPECT_EQ("<pre><code>&lt;\n &gt;\n</code></pre>\n", render("~~~\n<\n >\n~~~\n", 0));
}
TEST(Md4c_spec, Case91) {
  EXPECT_EQ("<p><code>foo</code></p>\n", render("``\nfoo\n``\n", 0));
}
TEST(Md4c_spec, Case92) {
  EXPECT_EQ("<pre><code>aaa\n~~~\n</code></pre>\n", render("```\naaa\n~~~\n```\n", 0));
}
TEST(Md4c_spec, Case93) {
  EXPECT_EQ("<pre><code>aaa\n```\n</code></pre>\n", render("~~~\naaa\n```\n~~~\n", 0));
}
TEST(Md4c_spec, Case94) {
  EXPECT_EQ("<pre><code>aaa\n```\n</code></pre>\n", render("````\naaa\n```\n``````\n", 0));
}
TEST(Md4c_spec, Case95) {
  EXPECT_EQ("<pre><code>aaa\n~~~\n</code></pre>\n", render("~~~~\naaa\n~~~\n~~~~\n", 0));
}
TEST(Md4c_spec, Case96) {
  EXPECT_EQ("<pre><code></code></pre>\n", render("```\n", 0));
}
TEST(Md4c_spec, Case97) {
  EXPECT_EQ("<pre><code>\n```\naaa\n</code></pre>\n", render("`````\n\n```\naaa\n", 0));
}
TEST(Md4c_spec, Case98) {
  EXPECT_EQ("<blockquote>\n<pre><code>aaa\n</code></pre>\n</blockquote>\n<p>bbb</p>\n", render("> ```\n> aaa\n\nbbb\n", 0));
}
TEST(Md4c_spec, Case99) {
  EXPECT_EQ("<pre><code>\n  \n</code></pre>\n", render("```\n\n  \n```\n", 0));
}
TEST(Md4c_spec, Case100) {
  EXPECT_EQ("<pre><code></code></pre>\n", render("```\n```\n", 0));
}
TEST(Md4c_spec, Case101) {
  EXPECT_EQ("<pre><code>aaa\naaa\n</code></pre>\n", render(" ```\n aaa\naaa\n```\n", 0));
}
TEST(Md4c_spec, Case102) {
  EXPECT_EQ("<pre><code>aaa\naaa\naaa\n</code></pre>\n", render("  ```\naaa\n  aaa\naaa\n  ```\n", 0));
}
TEST(Md4c_spec, Case103) {
  EXPECT_EQ("<pre><code>aaa\n aaa\naaa\n</code></pre>\n", render("   ```\n   aaa\n    aaa\n  aaa\n   ```\n", 0));
}
TEST(Md4c_spec, Case104) {
  EXPECT_EQ("<pre><code>```\naaa\n```\n</code></pre>\n", render("    ```\n    aaa\n    ```\n", 0));
}
TEST(Md4c_spec, Case105) {
  EXPECT_EQ("<pre><code>aaa\n</code></pre>\n", render("```\naaa\n  ```\n", 0));
}
TEST(Md4c_spec, Case106) {
  EXPECT_EQ("<pre><code>aaa\n</code></pre>\n", render("   ```\naaa\n  ```\n", 0));
}
TEST(Md4c_spec, Case107) {
  EXPECT_EQ("<pre><code>aaa\n    ```\n</code></pre>\n", render("```\naaa\n    ```\n", 0));
}
TEST(Md4c_spec, Case108) {
  EXPECT_EQ("<p><code> </code>\naaa</p>\n", render("``` ```\naaa\n", 0));
}
TEST(Md4c_spec, Case109) {
  EXPECT_EQ("<pre><code>aaa\n~~~ ~~\n</code></pre>\n", render("~~~~~~\naaa\n~~~ ~~\n", 0));
}
TEST(Md4c_spec, Case110) {
  EXPECT_EQ("<p>foo</p>\n<pre><code>bar\n</code></pre>\n<p>baz</p>\n", render("foo\n```\nbar\n```\nbaz\n", 0));
}
TEST(Md4c_spec, Case111) {
  EXPECT_EQ("<h2>foo</h2>\n<pre><code>bar\n</code></pre>\n<h1>baz</h1>\n", render("foo\n---\n~~~\nbar\n~~~\n# baz\n", 0));
}
TEST(Md4c_spec, Case112) {
  EXPECT_EQ("<pre><code class=\"language-ruby\">def foo(x)\n  return 3\nend\n</code></pre>\n", render("```ruby\ndef foo(x)\n  return 3\nend\n```\n", 0));
}
TEST(Md4c_spec, Case113) {
  EXPECT_EQ("<pre><code class=\"language-ruby\">def foo(x)\n  return 3\nend\n</code></pre>\n", render("~~~~    ruby startline=3 $%@#$\ndef foo(x)\n  return 3\nend\n~~~~~~~\n", 0));
}
TEST(Md4c_spec, Case114) {
  EXPECT_EQ("<pre><code class=\"language-;\"></code></pre>\n", render("````;\n````\n", 0));
}
TEST(Md4c_spec, Case115) {
  EXPECT_EQ("<p><code>aa</code>\nfoo</p>\n", render("``` aa ```\nfoo\n", 0));
}
TEST(Md4c_spec, Case116) {
  EXPECT_EQ("<pre><code class=\"language-aa\">foo\n</code></pre>\n", render("~~~ aa ``` ~~~\nfoo\n~~~\n", 0));
}
TEST(Md4c_spec, Case117) {
  EXPECT_EQ("<pre><code>``` aaa\n</code></pre>\n", render("```\n``` aaa\n```\n", 0));
}
TEST(Md4c_spec, Case118) {
  EXPECT_EQ("<table><tr><td>\n<pre>\n**Hello**,\n<p><em>world</em>.\n</pre></p>\n</td></tr></table>\n", render("<table><tr><td>\n<pre>\n**Hello**,\n\n_world_.\n</pre>\n</td></tr></table>\n", 0));
}
TEST(Md4c_spec, Case119) {
  EXPECT_EQ("<table>\n  <tr>\n    <td>\n           hi\n    </td>\n  </tr>\n</table>\n<p>okay.</p>\n", render("<table>\n  <tr>\n    <td>\n           hi\n    </td>\n  </tr>\n</table>\n\nokay.\n", 0));
}
TEST(Md4c_spec, Case120) {
  EXPECT_EQ(" <div>\n  *hello*\n         <foo><a>\n", render(" <div>\n  *hello*\n         <foo><a>\n", 0));
}
TEST(Md4c_spec, Case121) {
  EXPECT_EQ("</div>\n*foo*\n", render("</div>\n*foo*\n", 0));
}
TEST(Md4c_spec, Case122) {
  EXPECT_EQ("<DIV CLASS=\"foo\">\n<p><em>Markdown</em></p>\n</DIV>\n", render("<DIV CLASS=\"foo\">\n\n*Markdown*\n\n</DIV>\n", 0));
}
TEST(Md4c_spec, Case123) {
  EXPECT_EQ("<div id=\"foo\"\n  class=\"bar\">\n</div>\n", render("<div id=\"foo\"\n  class=\"bar\">\n</div>\n", 0));
}
TEST(Md4c_spec, Case124) {
  EXPECT_EQ("<div id=\"foo\" class=\"bar\n  baz\">\n</div>\n", render("<div id=\"foo\" class=\"bar\n  baz\">\n</div>\n", 0));
}
TEST(Md4c_spec, Case125) {
  EXPECT_EQ("<div>\n*foo*\n<p><em>bar</em></p>\n", render("<div>\n*foo*\n\n*bar*\n", 0));
}
TEST(Md4c_spec, Case126) {
  EXPECT_EQ("<div id=\"foo\"\n*hi*\n", render("<div id=\"foo\"\n*hi*\n", 0));
}
TEST(Md4c_spec, Case127) {
  EXPECT_EQ("<div class\nfoo\n", render("<div class\nfoo\n", 0));
}
TEST(Md4c_spec, Case128) {
  EXPECT_EQ("<div *?~&&&-<---\n*foo*\n", render("<div *???-&&&-<---\n*foo*\n", 0));
}
TEST(Md4c_spec, Case129) {
  EXPECT_EQ("<div><a href=\"bar\">*foo*</a></div>\n", render("<div><a href=\"bar\">*foo*</a></div>\n", 0));
}
TEST(Md4c_spec, Case130) {
  EXPECT_EQ("<table><tr><td>\nfoo\n</td></tr></table>\n", render("<table><tr><td>\nfoo\n</td></tr></table>\n", 0));
}
TEST(Md4c_spec, Case131) {
  EXPECT_EQ("<div></div>\n``` c\nint x = 33;\n```\n", render("<div></div>\n``` c\nint x = 33;\n```\n", 0));
}
TEST(Md4c_spec, Case132) {
  EXPECT_EQ("<a href=\"foo\">\n*bar*\n</a>\n", render("<a href=\"foo\">\n*bar*\n</a>\n", 0));
}
TEST(Md4c_spec, Case133) {
  EXPECT_EQ("<Warning>\n*bar*\n</Warning>\n", render("<Warning>\n*bar*\n</Warning>\n", 0));
}
TEST(Md4c_spec, Case134) {
  EXPECT_EQ("<i class=\"foo\">\n*bar*\n</i>\n", render("<i class=\"foo\">\n*bar*\n</i>\n", 0));
}
TEST(Md4c_spec, Case135) {
  EXPECT_EQ("</ins>\n*bar*\n", render("</ins>\n*bar*\n", 0));
}
TEST(Md4c_spec, Case136) {
  EXPECT_EQ("<del>\n*foo*\n</del>\n", render("<del>\n*foo*\n</del>\n", 0));
}
TEST(Md4c_spec, Case137) {
  EXPECT_EQ("<del>\n<p><em>foo</em></p>\n</del>\n", render("<del>\n\n*foo*\n\n</del>\n", 0));
}
TEST(Md4c_spec, Case138) {
  EXPECT_EQ("<p><del><em>foo</em></del></p>\n", render("<del>*foo*</del>\n", 0));
}
TEST(Md4c_spec, Case139) {
  EXPECT_EQ("<pre language=\"haskell\"><code>\nimport Text.HTML.TagSoup\n\nmain :: IO ()\nmain = print $ parseTags tags\n</code></pre>\n<p>okay</p>\n", render("<pre language=\"haskell\"><code>\nimport Text.HTML.TagSoup\n\nmain :: IO ()\nmain = print $ parseTags tags\n</code></pre>\nokay\n", 0));
}
TEST(Md4c_spec, Case140) {
  EXPECT_EQ("<script type=\"text/javascript\">\n// JavaScript example\n\ndocument.getElementById(\"demo\").innerHTML = \"Hello JavaScript!\";\n</script>\n<p>okay</p>\n", render("<script type=\"text/javascript\">\n// JavaScript example\n\ndocument.getElementById(\"demo\").innerHTML = \"Hello JavaScript!\";\n</script>\nokay\n", 0));
}
TEST(Md4c_spec, Case141) {
  EXPECT_EQ("<style\n  type=\"text/css\">\nh1 {color:red;}\n\np {color:blue;}\n</style>\n<p>okay</p>\n", render("<style\n  type=\"text/css\">\nh1 {color:red;}\n\np {color:blue;}\n</style>\nokay\n", 0));
}
TEST(Md4c_spec, Case142) {
  EXPECT_EQ("<style\n  type=\"text/css\">\n\nfoo\n", render("<style\n  type=\"text/css\">\n\nfoo\n", 0));
}
TEST(Md4c_spec, Case143) {
  EXPECT_EQ("<blockquote>\n<div>\nfoo\n</blockquote>\n<p>bar</p>\n", render("> <div>\n> foo\n\nbar\n", 0));
}
TEST(Md4c_spec, Case144) {
  EXPECT_EQ("<ul>\n<li><div>\n</li>\n<li>foo</li>\n</ul>\n", render("- <div>\n- foo\n", 0));
}
TEST(Md4c_spec, Case145) {
  EXPECT_EQ("<style>p{color:red;}</style>\n<p><em>foo</em></p>\n", render("<style>p{color:red;}</style>\n*foo*\n", 0));
}
TEST(Md4c_spec, Case146) {
  EXPECT_EQ("<!-- foo -->*bar*\n<p><em>baz</em></p>\n", render("<!-- foo -->*bar*\n*baz*\n", 0));
}
TEST(Md4c_spec, Case147) {
  EXPECT_EQ("<script>\nfoo\n</script>1. *bar*\n", render("<script>\nfoo\n</script>1. *bar*\n", 0));
}
TEST(Md4c_spec, Case148) {
  EXPECT_EQ("<!-- Foo\n\nbar\n   baz -->\n<p>okay</p>\n", render("<!-- Foo\n\nbar\n   baz -->\nokay\n", 0));
}
TEST(Md4c_spec, Case149) {
  EXPECT_EQ("<?php\n\n  echo '>';\n\n?>\n<p>okay</p>\n", render("<?php\n\n  echo '>';\n\n?>\nokay\n", 0));
}
TEST(Md4c_spec, Case150) {
  EXPECT_EQ("<!DOCTYPE html>\n", render("<!DOCTYPE html>\n", 0));
}
TEST(Md4c_spec, Case151) {
  EXPECT_EQ("<![CDATA[\nfunction matchwo(a,b)\n{\n  if (a < b && a < 0) then {\n    return 1;\n\n  } else {\n\n    return 0;\n  }\n}\n]]>\n<p>okay</p>\n", render("<![CDATA[\nfunction matchwo(a,b)\n{\n  if (a < b && a < 0) then {\n    return 1;\n\n  } else {\n\n    return 0;\n  }\n}\n]]>\nokay\n", 0));
}
TEST(Md4c_spec, Case152) {
  EXPECT_EQ("  <!-- foo -->\n<pre><code>&lt;!-- foo --&gt;\n</code></pre>\n", render("  <!-- foo -->\n\n    <!-- foo -->\n", 0));
}
TEST(Md4c_spec, Case153) {
  EXPECT_EQ("  <div>\n<pre><code>&lt;div&gt;\n</code></pre>\n", render("  <div>\n\n    <div>\n", 0));
}
TEST(Md4c_spec, Case154) {
  EXPECT_EQ("<p>Foo</p>\n<div>\nbar\n</div>\n", render("Foo\n<div>\nbar\n</div>\n", 0));
}
TEST(Md4c_spec, Case155) {
  EXPECT_EQ("<div>\nbar\n</div>\n*foo*\n", render("<div>\nbar\n</div>\n*foo*\n", 0));
}
TEST(Md4c_spec, Case156) {
  EXPECT_EQ("<p>Foo\n<a href=\"bar\">\nbaz</p>\n", render("Foo\n<a href=\"bar\">\nbaz\n", 0));
}
TEST(Md4c_spec, Case157) {
  EXPECT_EQ("<div>\n<p><em>Emphasized</em> text.</p>\n</div>\n", render("<div>\n\n*Emphasized* text.\n\n</div>\n", 0));
}
TEST(Md4c_spec, Case158) {
  EXPECT_EQ("<div>\n*Emphasized* text.\n</div>\n", render("<div>\n*Emphasized* text.\n</div>\n", 0));
}
TEST(Md4c_spec, Case159) {
  EXPECT_EQ("<table>\n<tr>\n<td>\nHi\n</td>\n</tr>\n</table>\n", render("<table>\n\n<tr>\n\n<td>\nHi\n</td>\n\n</tr>\n\n</table>\n", 0));
}
TEST(Md4c_spec, Case160) {
  EXPECT_EQ("<table>\n  <tr>\n<pre><code>&lt;td&gt;\n  Hi\n&lt;/td&gt;\n</code></pre>\n  </tr>\n</table>\n", render("<table>\n\n  <tr>\n\n    <td>\n      Hi\n    </td>\n\n  </tr>\n\n</table>\n", 0));
}
TEST(Md4c_spec, Case161) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">foo</a></p>\n", render("[foo]: /url \"title\"\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case162) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"the title\">foo</a></p>\n", render("   [foo]: \n      /url  \n           'the title'  \n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case163) {
  EXPECT_EQ("<p><a href=\"my_(url)\" title=\"title (with parens)\">Foo*bar]</a></p>\n", render("[Foo*bar\\]]:my_(url) 'title (with parens)'\n\n[Foo*bar\\]]\n", 0));
}
TEST(Md4c_spec, Case164) {
  EXPECT_EQ("<p><a href=\"my%20url\" title=\"title\">Foo bar</a></p>\n", render("[Foo bar]:\n<my url>\n'title'\n\n[Foo bar]\n", 0));
}
TEST(Md4c_spec, Case165) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"\ntitle\nline1\nline2\n\">foo</a></p>\n", render("[foo]: /url '\ntitle\nline1\nline2\n'\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case166) {
  EXPECT_EQ("<p>[foo]: /url 'title</p>\n<p>with blank line'</p>\n<p>[foo]</p>\n", render("[foo]: /url 'title\n\nwith blank line'\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case167) {
  EXPECT_EQ("<p><a href=\"/url\">foo</a></p>\n", render("[foo]:\n/url\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case168) {
  EXPECT_EQ("<p>[foo]:</p>\n<p>[foo]</p>\n", render("[foo]:\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case169) {
  EXPECT_EQ("<p><a href=\"\">foo</a></p>\n", render("[foo]: <>\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case170) {
  EXPECT_EQ("<p>[foo]: <bar>(baz)</p>\n<p>[foo]</p>\n", render("[foo]: <bar>(baz)\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case171) {
  EXPECT_EQ("<p><a href=\"/url%5Cbar*baz\" title=\"foo&quot;bar\\baz\">foo</a></p>\n", render("[foo]: /url\\bar\\*baz \"foo\\\"bar\\baz\"\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case172) {
  EXPECT_EQ("<p><a href=\"url\">foo</a></p>\n", render("[foo]\n\n[foo]: url\n", 0));
}
TEST(Md4c_spec, Case173) {
  EXPECT_EQ("<p><a href=\"first\">foo</a></p>\n", render("[foo]\n\n[foo]: first\n[foo]: second\n", 0));
}
TEST(Md4c_spec, Case174) {
  EXPECT_EQ("<p><a href=\"/url\">Foo</a></p>\n", render("[FOO]: /url\n\n[Foo]\n", 0));
}
TEST(Md4c_spec, Case175) {
  EXPECT_EQ("<p><a href=\"/%CF%86%CE%BF%CF%85\">αγω</a></p>\n", render("[ΑΓΩ]: /φου\n\n[αγω]\n", 0));
}
TEST(Md4c_spec, Case176) {
  EXPECT_EQ("", render("[foo]: /url\n", 0));
}
TEST(Md4c_spec, Case177) {
  EXPECT_EQ("<p>bar</p>\n", render("[\nfoo\n]: /url\nbar\n", 0));
}
TEST(Md4c_spec, Case178) {
  EXPECT_EQ("<p>[foo]: /url &quot;title&quot; ok</p>\n", render("[foo]: /url \"title\" ok\n", 0));
}
TEST(Md4c_spec, Case179) {
  EXPECT_EQ("<p>&quot;title&quot; ok</p>\n", render("[foo]: /url\n\"title\" ok\n", 0));
}
TEST(Md4c_spec, Case180) {
  EXPECT_EQ("<pre><code>[foo]: /url &quot;title&quot;\n</code></pre>\n<p>[foo]</p>\n", render("    [foo]: /url \"title\"\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case181) {
  EXPECT_EQ("<pre><code>[foo]: /url\n</code></pre>\n<p>[foo]</p>\n", render("```\n[foo]: /url\n```\n\n[foo]\n", 0));
}
TEST(Md4c_spec, Case182) {
  EXPECT_EQ("<p>Foo\n[bar]: /baz</p>\n<p>[bar]</p>\n", render("Foo\n[bar]: /baz\n\n[bar]\n", 0));
}
TEST(Md4c_spec, Case183) {
  EXPECT_EQ("<h1><a href=\"/url\">Foo</a></h1>\n<blockquote>\n<p>bar</p>\n</blockquote>\n", render("# [Foo]\n[foo]: /url\n> bar\n", 0));
}
TEST(Md4c_spec, Case184) {
  EXPECT_EQ("<h1>bar</h1>\n<p><a href=\"/url\">foo</a></p>\n", render("[foo]: /url\nbar\n===\n[foo]\n", 0));
}
TEST(Md4c_spec, Case185) {
  EXPECT_EQ("<p>===\n<a href=\"/url\">foo</a></p>\n", render("[foo]: /url\n===\n[foo]\n", 0));
}
TEST(Md4c_spec, Case186) {
  EXPECT_EQ("<p><a href=\"/foo-url\" title=\"foo\">foo</a>,\n<a href=\"/bar-url\" title=\"bar\">bar</a>,\n<a href=\"/baz-url\">baz</a></p>\n", render("[foo]: /foo-url \"foo\"\n[bar]: /bar-url\n  \"bar\"\n[baz]: /baz-url\n\n[foo],\n[bar],\n[baz]\n", 0));
}
TEST(Md4c_spec, Case187) {
  EXPECT_EQ("<p><a href=\"/url\">foo</a></p>\n<blockquote>\n</blockquote>\n", render("[foo]\n\n> [foo]: /url\n", 0));
}
TEST(Md4c_spec, Case188) {
  EXPECT_EQ("", render("[foo]: /url\n", 0));
}
TEST(Md4c_spec, Case189) {
  EXPECT_EQ("<p>aaa</p>\n<p>bbb</p>\n", render("aaa\n\nbbb\n", 0));
}
TEST(Md4c_spec, Case190) {
  EXPECT_EQ("<p>aaa\nbbb</p>\n<p>ccc\nddd</p>\n", render("aaa\nbbb\n\nccc\nddd\n", 0));
}
TEST(Md4c_spec, Case191) {
  EXPECT_EQ("<p>aaa</p>\n<p>bbb</p>\n", render("aaa\n\n\nbbb\n", 0));
}
TEST(Md4c_spec, Case192) {
  EXPECT_EQ("<p>aaa\nbbb</p>\n", render("  aaa\n bbb\n", 0));
}
TEST(Md4c_spec, Case193) {
  EXPECT_EQ("<p>aaa\nbbb\nccc</p>\n", render("aaa\n             bbb\n                                       ccc\n", 0));
}
TEST(Md4c_spec, Case194) {
  EXPECT_EQ("<p>aaa\nbbb</p>\n", render("   aaa\nbbb\n", 0));
}
TEST(Md4c_spec, Case195) {
  EXPECT_EQ("<pre><code>aaa\n</code></pre>\n<p>bbb</p>\n", render("    aaa\nbbb\n", 0));
}
TEST(Md4c_spec, Case196) {
  EXPECT_EQ("<p>aaa<br>\nbbb</p>\n", render("aaa     \nbbb     \n", 0));
}
TEST(Md4c_spec, Case197) {
  EXPECT_EQ("<p>aaa</p>\n<h1>aaa</h1>\n", render("  \n\naaa\n  \n\n# aaa\n\n  \n", 0));
}
TEST(Md4c_spec, Case198) {
  EXPECT_EQ("<blockquote>\n<h1>Foo</h1>\n<p>bar\nbaz</p>\n</blockquote>\n", render("> # Foo\n> bar\n> baz\n", 0));
}
TEST(Md4c_spec, Case199) {
  EXPECT_EQ("<blockquote>\n<h1>Foo</h1>\n<p>bar\nbaz</p>\n</blockquote>\n", render("># Foo\n>bar\n> baz\n", 0));
}
TEST(Md4c_spec, Case200) {
  EXPECT_EQ("<blockquote>\n<h1>Foo</h1>\n<p>bar\nbaz</p>\n</blockquote>\n", render("   > # Foo\n   > bar\n > baz\n", 0));
}
TEST(Md4c_spec, Case201) {
  EXPECT_EQ("<pre><code>&gt; # Foo\n&gt; bar\n&gt; baz\n</code></pre>\n", render("    > # Foo\n    > bar\n    > baz\n", 0));
}
TEST(Md4c_spec, Case202) {
  EXPECT_EQ("<blockquote>\n<h1>Foo</h1>\n<p>bar\nbaz</p>\n</blockquote>\n", render("> # Foo\n> bar\nbaz\n", 0));
}
TEST(Md4c_spec, Case203) {
  EXPECT_EQ("<blockquote>\n<p>bar\nbaz\nfoo</p>\n</blockquote>\n", render("> bar\nbaz\n> foo\n", 0));
}
TEST(Md4c_spec, Case204) {
  EXPECT_EQ("<blockquote>\n<p>foo</p>\n</blockquote>\n<hr>\n", render("> foo\n---\n", 0));
}
TEST(Md4c_spec, Case205) {
  EXPECT_EQ("<blockquote>\n<ul>\n<li>foo</li>\n</ul>\n</blockquote>\n<ul>\n<li>bar</li>\n</ul>\n", render("> - foo\n- bar\n", 0));
}
TEST(Md4c_spec, Case206) {
  EXPECT_EQ("<blockquote>\n<pre><code>foo\n</code></pre>\n</blockquote>\n<pre><code>bar\n</code></pre>\n", render(">     foo\n    bar\n", 0));
}
TEST(Md4c_spec, Case207) {
  EXPECT_EQ("<blockquote>\n<pre><code></code></pre>\n</blockquote>\n<p>foo</p>\n<pre><code></code></pre>\n", render("> ```\nfoo\n```\n", 0));
}
TEST(Md4c_spec, Case208) {
  EXPECT_EQ("<blockquote>\n<p>foo\n- bar</p>\n</blockquote>\n", render("> foo\n    - bar\n", 0));
}
TEST(Md4c_spec, Case209) {
  EXPECT_EQ("<blockquote>\n</blockquote>\n", render(">\n", 0));
}
TEST(Md4c_spec, Case210) {
  EXPECT_EQ("<blockquote>\n</blockquote>\n", render(">\n>  \n> \n", 0));
}
TEST(Md4c_spec, Case211) {
  EXPECT_EQ("<blockquote>\n<p>foo</p>\n</blockquote>\n", render(">\n> foo\n>  \n", 0));
}
TEST(Md4c_spec, Case212) {
  EXPECT_EQ("<blockquote>\n<p>foo</p>\n</blockquote>\n<blockquote>\n<p>bar</p>\n</blockquote>\n", render("> foo\n\n> bar\n", 0));
}
TEST(Md4c_spec, Case213) {
  EXPECT_EQ("<blockquote>\n<p>foo\nbar</p>\n</blockquote>\n", render("> foo\n> bar\n", 0));
}
TEST(Md4c_spec, Case214) {
  EXPECT_EQ("<blockquote>\n<p>foo</p>\n<p>bar</p>\n</blockquote>\n", render("> foo\n>\n> bar\n", 0));
}
TEST(Md4c_spec, Case215) {
  EXPECT_EQ("<p>foo</p>\n<blockquote>\n<p>bar</p>\n</blockquote>\n", render("foo\n> bar\n", 0));
}
TEST(Md4c_spec, Case216) {
  EXPECT_EQ("<blockquote>\n<p>aaa</p>\n</blockquote>\n<hr>\n<blockquote>\n<p>bbb</p>\n</blockquote>\n", render("> aaa\n***\n> bbb\n", 0));
}
TEST(Md4c_spec, Case217) {
  EXPECT_EQ("<blockquote>\n<p>bar\nbaz</p>\n</blockquote>\n", render("> bar\nbaz\n", 0));
}
TEST(Md4c_spec, Case218) {
  EXPECT_EQ("<blockquote>\n<p>bar</p>\n</blockquote>\n<p>baz</p>\n", render("> bar\n\nbaz\n", 0));
}
TEST(Md4c_spec, Case219) {
  EXPECT_EQ("<blockquote>\n<p>bar</p>\n</blockquote>\n<p>baz</p>\n", render("> bar\n>\nbaz\n", 0));
}
TEST(Md4c_spec, Case220) {
  EXPECT_EQ("<blockquote>\n<blockquote>\n<blockquote>\n<p>foo\nbar</p>\n</blockquote>\n</blockquote>\n</blockquote>\n", render("> > > foo\nbar\n", 0));
}
TEST(Md4c_spec, Case221) {
  EXPECT_EQ("<blockquote>\n<blockquote>\n<blockquote>\n<p>foo\nbar\nbaz</p>\n</blockquote>\n</blockquote>\n</blockquote>\n", render(">>> foo\n> bar\n>>baz\n", 0));
}
TEST(Md4c_spec, Case222) {
  EXPECT_EQ("<blockquote>\n<pre><code>code\n</code></pre>\n</blockquote>\n<blockquote>\n<p>not code</p>\n</blockquote>\n", render(">     code\n\n>    not code\n", 0));
}
TEST(Md4c_spec, Case223) {
  EXPECT_EQ("<p>A paragraph\nwith two lines.</p>\n<pre><code>indented code\n</code></pre>\n<blockquote>\n<p>A block quote.</p>\n</blockquote>\n", render("A paragraph\nwith two lines.\n\n    indented code\n\n> A block quote.\n", 0));
}
TEST(Md4c_spec, Case224) {
  EXPECT_EQ("<ol>\n<li><p>A paragraph\nwith two lines.</p>\n<pre><code>indented code\n</code></pre>\n<blockquote>\n<p>A block quote.</p>\n</blockquote>\n</li>\n</ol>\n", render("1.  A paragraph\n    with two lines.\n\n        indented code\n\n    > A block quote.\n", 0));
}
TEST(Md4c_spec, Case225) {
  EXPECT_EQ("<ul>\n<li>one</li>\n</ul>\n<p>two</p>\n", render("- one\n\n two\n", 0));
}
TEST(Md4c_spec, Case226) {
  EXPECT_EQ("<ul>\n<li><p>one</p>\n<p>two</p>\n</li>\n</ul>\n", render("- one\n\n  two\n", 0));
}
TEST(Md4c_spec, Case227) {
  EXPECT_EQ("<ul>\n<li>one</li>\n</ul>\n<pre><code> two\n</code></pre>\n", render(" -    one\n\n     two\n", 0));
}
TEST(Md4c_spec, Case228) {
  EXPECT_EQ("<ul>\n<li><p>one</p>\n<p>two</p>\n</li>\n</ul>\n", render(" -    one\n\n      two\n", 0));
}
TEST(Md4c_spec, Case229) {
  EXPECT_EQ("<blockquote>\n<blockquote>\n<ol>\n<li><p>one</p>\n<p>two</p>\n</li>\n</ol>\n</blockquote>\n</blockquote>\n", render("   > > 1.  one\n>>\n>>     two\n", 0));
}
TEST(Md4c_spec, Case230) {
  EXPECT_EQ("<blockquote>\n<blockquote>\n<ul>\n<li>one</li>\n</ul>\n<p>two</p>\n</blockquote>\n</blockquote>\n", render(">>- one\n>>\n  >  > two\n", 0));
}
TEST(Md4c_spec, Case231) {
  EXPECT_EQ("<p>-one</p>\n<p>2.two</p>\n", render("-one\n\n2.two\n", 0));
}
TEST(Md4c_spec, Case232) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<p>bar</p>\n</li>\n</ul>\n", render("- foo\n\n\n  bar\n", 0));
}
TEST(Md4c_spec, Case233) {
  EXPECT_EQ("<ol>\n<li><p>foo</p>\n<pre><code>bar\n</code></pre>\n<p>baz</p>\n<blockquote>\n<p>bam</p>\n</blockquote>\n</li>\n</ol>\n", render("1.  foo\n\n    ```\n    bar\n    ```\n\n    baz\n\n    > bam\n", 0));
}
TEST(Md4c_spec, Case234) {
  EXPECT_EQ("<ul>\n<li><p>Foo</p>\n<pre><code>bar\n\n\nbaz\n</code></pre>\n</li>\n</ul>\n", render("- Foo\n\n      bar\n\n\n      baz\n", 0));
}
TEST(Md4c_spec, Case235) {
  EXPECT_EQ("<ol start=\"123456789\">\n<li>ok</li>\n</ol>\n", render("123456789. ok\n", 0));
}
TEST(Md4c_spec, Case236) {
  EXPECT_EQ("<p>1234567890. not ok</p>\n", render("1234567890. not ok\n", 0));
}
TEST(Md4c_spec, Case237) {
  EXPECT_EQ("<ol start=\"0\">\n<li>ok</li>\n</ol>\n", render("0. ok\n", 0));
}
TEST(Md4c_spec, Case238) {
  EXPECT_EQ("<ol start=\"3\">\n<li>ok</li>\n</ol>\n", render("003. ok\n", 0));
}
TEST(Md4c_spec, Case239) {
  EXPECT_EQ("<p>-1. not ok</p>\n", render("-1. not ok\n", 0));
}
TEST(Md4c_spec, Case240) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<pre><code>bar\n</code></pre>\n</li>\n</ul>\n", render("- foo\n\n      bar\n", 0));
}
TEST(Md4c_spec, Case241) {
  EXPECT_EQ("<ol start=\"10\">\n<li><p>foo</p>\n<pre><code>bar\n</code></pre>\n</li>\n</ol>\n", render("  10.  foo\n\n           bar\n", 0));
}
TEST(Md4c_spec, Case242) {
  EXPECT_EQ("<pre><code>indented code\n</code></pre>\n<p>paragraph</p>\n<pre><code>more code\n</code></pre>\n", render("    indented code\n\nparagraph\n\n    more code\n", 0));
}
TEST(Md4c_spec, Case243) {
  EXPECT_EQ("<ol>\n<li><pre><code>indented code\n</code></pre>\n<p>paragraph</p>\n<pre><code>more code\n</code></pre>\n</li>\n</ol>\n", render("1.     indented code\n\n   paragraph\n\n       more code\n", 0));
}
TEST(Md4c_spec, Case244) {
  EXPECT_EQ("<ol>\n<li><pre><code> indented code\n</code></pre>\n<p>paragraph</p>\n<pre><code>more code\n</code></pre>\n</li>\n</ol>\n", render("1.      indented code\n\n   paragraph\n\n       more code\n", 0));
}
TEST(Md4c_spec, Case245) {
  EXPECT_EQ("<p>foo</p>\n<p>bar</p>\n", render("   foo\n\nbar\n", 0));
}
TEST(Md4c_spec, Case246) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n</ul>\n<p>bar</p>\n", render("-    foo\n\n  bar\n", 0));
}
TEST(Md4c_spec, Case247) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<p>bar</p>\n</li>\n</ul>\n", render("-  foo\n\n   bar\n", 0));
}
TEST(Md4c_spec, Case248) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n<li><pre><code>bar\n</code></pre>\n</li>\n<li><pre><code>baz\n</code></pre>\n</li>\n</ul>\n", render("-\n  foo\n-\n  ```\n  bar\n  ```\n-\n      baz\n", 0));
}
TEST(Md4c_spec, Case249) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n</ul>\n", render("-   \n  foo\n", 0));
}
TEST(Md4c_spec, Case250) {
  EXPECT_EQ("<ul>\n<li></li>\n</ul>\n<p>foo</p>\n", render("-\n\n  foo\n", 0));
}
TEST(Md4c_spec, Case251) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n<li></li>\n<li>bar</li>\n</ul>\n", render("- foo\n-\n- bar\n", 0));
}
TEST(Md4c_spec, Case252) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n<li></li>\n<li>bar</li>\n</ul>\n", render("- foo\n-   \n- bar\n", 0));
}
TEST(Md4c_spec, Case253) {
  EXPECT_EQ("<ol>\n<li>foo</li>\n<li></li>\n<li>bar</li>\n</ol>\n", render("1. foo\n2.\n3. bar\n", 0));
}
TEST(Md4c_spec, Case254) {
  EXPECT_EQ("<ul>\n<li></li>\n</ul>\n", render("*\n", 0));
}
TEST(Md4c_spec, Case255) {
  EXPECT_EQ("<p>foo\n*</p>\n<p>foo\n1.</p>\n", render("foo\n*\n\nfoo\n1.\n", 0));
}
TEST(Md4c_spec, Case256) {
  EXPECT_EQ("<ol>\n<li><p>A paragraph\nwith two lines.</p>\n<pre><code>indented code\n</code></pre>\n<blockquote>\n<p>A block quote.</p>\n</blockquote>\n</li>\n</ol>\n", render(" 1.  A paragraph\n     with two lines.\n\n         indented code\n\n     > A block quote.\n", 0));
}
TEST(Md4c_spec, Case257) {
  EXPECT_EQ("<ol>\n<li><p>A paragraph\nwith two lines.</p>\n<pre><code>indented code\n</code></pre>\n<blockquote>\n<p>A block quote.</p>\n</blockquote>\n</li>\n</ol>\n", render("  1.  A paragraph\n      with two lines.\n\n          indented code\n\n      > A block quote.\n", 0));
}
TEST(Md4c_spec, Case258) {
  EXPECT_EQ("<ol>\n<li><p>A paragraph\nwith two lines.</p>\n<pre><code>indented code\n</code></pre>\n<blockquote>\n<p>A block quote.</p>\n</blockquote>\n</li>\n</ol>\n", render("   1.  A paragraph\n       with two lines.\n\n           indented code\n\n       > A block quote.\n", 0));
}
TEST(Md4c_spec, Case259) {
  EXPECT_EQ("<pre><code>1.  A paragraph\n    with two lines.\n\n        indented code\n\n    &gt; A block quote.\n</code></pre>\n", render("    1.  A paragraph\n        with two lines.\n\n            indented code\n\n        > A block quote.\n", 0));
}
TEST(Md4c_spec, Case260) {
  EXPECT_EQ("<ol>\n<li><p>A paragraph\nwith two lines.</p>\n<pre><code>indented code\n</code></pre>\n<blockquote>\n<p>A block quote.</p>\n</blockquote>\n</li>\n</ol>\n", render("  1.  A paragraph\nwith two lines.\n\n          indented code\n\n      > A block quote.\n", 0));
}
TEST(Md4c_spec, Case261) {
  EXPECT_EQ("<ol>\n<li>A paragraph\nwith two lines.</li>\n</ol>\n", render("  1.  A paragraph\n    with two lines.\n", 0));
}
TEST(Md4c_spec, Case262) {
  EXPECT_EQ("<blockquote>\n<ol>\n<li><blockquote>\n<p>Blockquote\ncontinued here.</p>\n</blockquote>\n</li>\n</ol>\n</blockquote>\n", render("> 1. > Blockquote\ncontinued here.\n", 0));
}
TEST(Md4c_spec, Case263) {
  EXPECT_EQ("<blockquote>\n<ol>\n<li><blockquote>\n<p>Blockquote\ncontinued here.</p>\n</blockquote>\n</li>\n</ol>\n</blockquote>\n", render("> 1. > Blockquote\n> continued here.\n", 0));
}
TEST(Md4c_spec, Case264) {
  EXPECT_EQ("<ul>\n<li>foo<ul>\n<li>bar<ul>\n<li>baz<ul>\n<li>boo</li>\n</ul>\n</li>\n</ul>\n</li>\n</ul>\n</li>\n</ul>\n", render("- foo\n  - bar\n    - baz\n      - boo\n", 0));
}
TEST(Md4c_spec, Case265) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n<li>bar</li>\n<li>baz</li>\n<li>boo</li>\n</ul>\n", render("- foo\n - bar\n  - baz\n   - boo\n", 0));
}
TEST(Md4c_spec, Case266) {
  EXPECT_EQ("<ol start=\"10\">\n<li>foo<ul>\n<li>bar</li>\n</ul>\n</li>\n</ol>\n", render("10) foo\n    - bar\n", 0));
}
TEST(Md4c_spec, Case267) {
  EXPECT_EQ("<ol start=\"10\">\n<li>foo</li>\n</ol>\n<ul>\n<li>bar</li>\n</ul>\n", render("10) foo\n   - bar\n", 0));
}
TEST(Md4c_spec, Case268) {
  EXPECT_EQ("<ul>\n<li><ul>\n<li>foo</li>\n</ul>\n</li>\n</ul>\n", render("- - foo\n", 0));
}
TEST(Md4c_spec, Case269) {
  EXPECT_EQ("<ol>\n<li><ul>\n<li><ol start=\"2\">\n<li>foo</li>\n</ol>\n</li>\n</ul>\n</li>\n</ol>\n", render("1. - 2. foo\n", 0));
}
TEST(Md4c_spec, Case270) {
  EXPECT_EQ("<ul>\n<li><h1>Foo</h1>\n</li>\n<li><h2>Bar</h2>\nbaz</li>\n</ul>\n", render("- # Foo\n- Bar\n  ---\n  baz\n", 0));
}
TEST(Md4c_spec, Case271) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n<li>bar</li>\n</ul>\n<ul>\n<li>baz</li>\n</ul>\n", render("- foo\n- bar\n+ baz\n", 0));
}
TEST(Md4c_spec, Case272) {
  EXPECT_EQ("<ol>\n<li>foo</li>\n<li>bar</li>\n</ol>\n<ol start=\"3\">\n<li>baz</li>\n</ol>\n", render("1. foo\n2. bar\n3) baz\n", 0));
}
TEST(Md4c_spec, Case273) {
  EXPECT_EQ("<p>Foo</p>\n<ul>\n<li>bar</li>\n<li>baz</li>\n</ul>\n", render("Foo\n- bar\n- baz\n", 0));
}
TEST(Md4c_spec, Case274) {
  EXPECT_EQ("<p>The number of windows in my house is\n14.  The number of doors is 6.</p>\n", render("The number of windows in my house is\n14.  The number of doors is 6.\n", 0));
}
TEST(Md4c_spec, Case275) {
  EXPECT_EQ("<p>The number of windows in my house is</p>\n<ol>\n<li>The number of doors is 6.</li>\n</ol>\n", render("The number of windows in my house is\n1.  The number of doors is 6.\n", 0));
}
TEST(Md4c_spec, Case276) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n</li>\n<li><p>bar</p>\n</li>\n<li><p>baz</p>\n</li>\n</ul>\n", render("- foo\n\n- bar\n\n\n- baz\n", 0));
}
TEST(Md4c_spec, Case277) {
  EXPECT_EQ("<ul>\n<li>foo<ul>\n<li>bar<ul>\n<li><p>baz</p>\n<p>bim</p>\n</li>\n</ul>\n</li>\n</ul>\n</li>\n</ul>\n", render("- foo\n  - bar\n    - baz\n\n\n      bim\n", 0));
}
TEST(Md4c_spec, Case278) {
  EXPECT_EQ("<ul>\n<li>foo</li>\n<li>bar</li>\n</ul>\n<!-- -->\n<ul>\n<li>baz</li>\n<li>bim</li>\n</ul>\n", render("- foo\n- bar\n\n<!-- -->\n\n- baz\n- bim\n", 0));
}
TEST(Md4c_spec, Case279) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<p>notcode</p>\n</li>\n<li><p>foo</p>\n</li>\n</ul>\n<!-- -->\n<pre><code>code\n</code></pre>\n", render("-   foo\n\n    notcode\n\n-   foo\n\n<!-- -->\n\n    code\n", 0));
}
TEST(Md4c_spec, Case280) {
  EXPECT_EQ("<ul>\n<li>a</li>\n<li>b</li>\n<li>c</li>\n<li>d</li>\n<li>e</li>\n<li>f</li>\n<li>g</li>\n</ul>\n", render("- a\n - b\n  - c\n   - d\n  - e\n - f\n- g\n", 0));
}
TEST(Md4c_spec, Case281) {
  EXPECT_EQ("<ol>\n<li><p>a</p>\n</li>\n<li><p>b</p>\n</li>\n<li><p>c</p>\n</li>\n</ol>\n", render("1. a\n\n  2. b\n\n   3. c\n", 0));
}
TEST(Md4c_spec, Case282) {
  EXPECT_EQ("<ul>\n<li>a</li>\n<li>b</li>\n<li>c</li>\n<li>d\n- e</li>\n</ul>\n", render("- a\n - b\n  - c\n   - d\n    - e\n", 0));
}
TEST(Md4c_spec, Case283) {
  EXPECT_EQ("<ol>\n<li><p>a</p>\n</li>\n<li><p>b</p>\n</li>\n</ol>\n<pre><code>3. c\n</code></pre>\n", render("1. a\n\n  2. b\n\n    3. c\n", 0));
}
TEST(Md4c_spec, Case284) {
  EXPECT_EQ("<ul>\n<li><p>a</p>\n</li>\n<li><p>b</p>\n</li>\n<li><p>c</p>\n</li>\n</ul>\n", render("- a\n- b\n\n- c\n", 0));
}
TEST(Md4c_spec, Case285) {
  EXPECT_EQ("<ul>\n<li><p>a</p>\n</li>\n<li></li>\n<li><p>c</p>\n</li>\n</ul>\n", render("* a\n*\n\n* c\n", 0));
}
TEST(Md4c_spec, Case286) {
  EXPECT_EQ("<ul>\n<li><p>a</p>\n</li>\n<li><p>b</p>\n<p>c</p>\n</li>\n<li><p>d</p>\n</li>\n</ul>\n", render("- a\n- b\n\n  c\n- d\n", 0));
}
TEST(Md4c_spec, Case287) {
  EXPECT_EQ("<ul>\n<li><p>a</p>\n</li>\n<li><p>b</p>\n</li>\n<li><p>d</p>\n</li>\n</ul>\n", render("- a\n- b\n\n  [ref]: /url\n- d\n", 0));
}
TEST(Md4c_spec, Case288) {
  EXPECT_EQ("<ul>\n<li>a</li>\n<li><pre><code>b\n\n\n</code></pre>\n</li>\n<li>c</li>\n</ul>\n", render("- a\n- ```\n  b\n\n\n  ```\n- c\n", 0));
}
TEST(Md4c_spec, Case289) {
  EXPECT_EQ("<ul>\n<li>a<ul>\n<li><p>b</p>\n<p>c</p>\n</li>\n</ul>\n</li>\n<li>d</li>\n</ul>\n", render("- a\n  - b\n\n    c\n- d\n", 0));
}
TEST(Md4c_spec, Case290) {
  EXPECT_EQ("<ul>\n<li>a<blockquote>\n<p>b</p>\n</blockquote>\n</li>\n<li>c</li>\n</ul>\n", render("* a\n  > b\n  >\n* c\n", 0));
}
TEST(Md4c_spec, Case291) {
  EXPECT_EQ("<ul>\n<li>a<blockquote>\n<p>b</p>\n</blockquote>\n<pre><code>c\n</code></pre>\n</li>\n<li>d</li>\n</ul>\n", render("- a\n  > b\n  ```\n  c\n  ```\n- d\n", 0));
}
TEST(Md4c_spec, Case292) {
  EXPECT_EQ("<ul>\n<li>a</li>\n</ul>\n", render("- a\n", 0));
}
TEST(Md4c_spec, Case293) {
  EXPECT_EQ("<ul>\n<li>a<ul>\n<li>b</li>\n</ul>\n</li>\n</ul>\n", render("- a\n  - b\n", 0));
}
TEST(Md4c_spec, Case294) {
  EXPECT_EQ("<ol>\n<li><pre><code>foo\n</code></pre>\n<p>bar</p>\n</li>\n</ol>\n", render("1. ```\n   foo\n   ```\n\n   bar\n", 0));
}
TEST(Md4c_spec, Case295) {
  EXPECT_EQ("<ul>\n<li><p>foo</p>\n<ul>\n<li>bar</li>\n</ul>\n<p>baz</p>\n</li>\n</ul>\n", render("* foo\n  * bar\n\n  baz\n", 0));
}
TEST(Md4c_spec, Case296) {
  EXPECT_EQ("<ul>\n<li><p>a</p>\n<ul>\n<li>b</li>\n<li>c</li>\n</ul>\n</li>\n<li><p>d</p>\n<ul>\n<li>e</li>\n<li>f</li>\n</ul>\n</li>\n</ul>\n", render("- a\n  - b\n  - c\n\n- d\n  - e\n  - f\n", 0));
}
TEST(Md4c_spec, Case297) {
  EXPECT_EQ("<p><code>hi</code>lo`</p>\n", render("`hi`lo`\n", 0));
}
TEST(Md4c_spec, Case298) {
  EXPECT_EQ("<p>!&quot;#$%&amp;'()*+,-./:;&lt;=&gt;?@[\\]^_`{|}~</p>\n", render("\\!\\\"\\#\\$\\%\\&\\'\\(\\)\\*\\+\\,\\-\\.\\/\\:\\;\\<\\=\\>\\?\\@\\[\\\\\\]\\^\\_\\`\\{\\|\\}\\~\n", 0));
}
TEST(Md4c_spec, Case299) {
  EXPECT_EQ("<p>\\\t\\A\\a\\ \\3\\φ\\«</p>\n", render("\\\t\\A\\a\\ \\3\\φ\\«\n", 0));
}
TEST(Md4c_spec, Case300) {
  EXPECT_EQ("<p>*not emphasized*\n&lt;br/&gt; not a tag\n[not a link](/foo)\n`not code`\n1. not a list\n* not a list\n# not a heading\n[foo]: /url &quot;not a reference&quot;\n&amp;ouml; not a character entity</p>\n", render("\\*not emphasized*\n\\<br/> not a tag\n\\[not a link](/foo)\n\\`not code`\n1\\. not a list\n\\* not a list\n\\# not a heading\n\\[foo]: /url \"not a reference\"\n\\&ouml; not a character entity\n", 0));
}
TEST(Md4c_spec, Case301) {
  EXPECT_EQ("<p>\\<em>emphasis</em></p>\n", render("\\\\*emphasis*\n", 0));
}
TEST(Md4c_spec, Case302) {
  EXPECT_EQ("<p>foo<br>\nbar</p>\n", render("foo\\\nbar\n", 0));
}
TEST(Md4c_spec, Case303) {
  EXPECT_EQ("<p><code>\\[\\`</code></p>\n", render("`` \\[\\` ``\n", 0));
}
TEST(Md4c_spec, Case304) {
  EXPECT_EQ("<pre><code>\\[\\]\n</code></pre>\n", render("    \\[\\]\n", 0));
}
TEST(Md4c_spec, Case305) {
  EXPECT_EQ("<pre><code>\\[\\]\n</code></pre>\n", render("~~~\n\\[\\]\n~~~\n", 0));
}
TEST(Md4c_spec, Case306) {
  EXPECT_EQ("<p><a href=\"http://example.com?find=%5C*\">http://example.com?find=\\*</a></p>\n", render("<http://example.com?find=\\*>\n", 0));
}
TEST(Md4c_spec, Case307) {
  EXPECT_EQ("<a href=\"/bar\\/)\">\n", render("<a href=\"/bar\\/)\">\n", 0));
}
TEST(Md4c_spec, Case308) {
  EXPECT_EQ("<p><a href=\"/bar*\" title=\"ti*tle\">foo</a></p>\n", render("[foo](/bar\\* \"ti\\*tle\")\n", 0));
}
TEST(Md4c_spec, Case309) {
  EXPECT_EQ("<p><a href=\"/bar*\" title=\"ti*tle\">foo</a></p>\n", render("[foo]\n\n[foo]: /bar\\* \"ti\\*tle\"\n", 0));
}
TEST(Md4c_spec, Case310) {
  EXPECT_EQ("<pre><code class=\"language-foo+bar\">foo\n</code></pre>\n", render("``` foo\\+bar\nfoo\n```\n", 0));
}
TEST(Md4c_spec, Case311) {
  EXPECT_EQ("<p>  &amp; © Æ Ď\n¾ ℋ ⅆ\n∲ ≧̸</p>\n", render("&nbsp; &amp; &copy; &AElig; &Dcaron;\n&frac34; &HilbertSpace; &DifferentialD;\n&ClockwiseContourIntegral; &ngE;\n", 0));
}
TEST(Md4c_spec, Case312) {
  EXPECT_EQ("<p># Ӓ Ϡ �</p>\n", render("&#35; &#1234; &#992; &#0;\n", 0));
}
TEST(Md4c_spec, Case313) {
  EXPECT_EQ("<p>&quot; ആ ಫ</p>\n", render("&#X22; &#XD06; &#xcab;\n", 0));
}
TEST(Md4c_spec, Case314) {
  EXPECT_EQ("<p>&amp;nbsp &amp;x; &amp;#; &amp;#x;\n&amp;#87654321;\n&amp;#abcdef0;\n&amp;ThisIsNotDefined; &amp;hi?;</p>\n", render("&nbsp &x; &#; &#x;\n&#87654321;\n&#abcdef0;\n&ThisIsNotDefined; &hi?;\n", 0));
}
TEST(Md4c_spec, Case315) {
  EXPECT_EQ("<p>&amp;copy</p>\n", render("&copy\n", 0));
}
TEST(Md4c_spec, Case316) {
  EXPECT_EQ("<p>&amp;MadeUpEntity;</p>\n", render("&MadeUpEntity;\n", 0));
}
TEST(Md4c_spec, Case317) {
  EXPECT_EQ("<a href=\"&ouml;&ouml;.html\">\n", render("<a href=\"&ouml;&ouml;.html\">\n", 0));
}
TEST(Md4c_spec, Case318) {
  EXPECT_EQ("<p><a href=\"/f%C3%B6%C3%B6\" title=\"föö\">foo</a></p>\n", render("[foo](/f&ouml;&ouml; \"f&ouml;&ouml;\")\n", 0));
}
TEST(Md4c_spec, Case319) {
  EXPECT_EQ("<p><a href=\"/f%C3%B6%C3%B6\" title=\"föö\">foo</a></p>\n", render("[foo]\n\n[foo]: /f&ouml;&ouml; \"f&ouml;&ouml;\"\n", 0));
}
TEST(Md4c_spec, Case320) {
  EXPECT_EQ("<pre><code class=\"language-föö\">foo\n</code></pre>\n", render("``` f&ouml;&ouml;\nfoo\n```\n", 0));
}
TEST(Md4c_spec, Case321) {
  EXPECT_EQ("<p><code>f&amp;ouml;&amp;ouml;</code></p>\n", render("`f&ouml;&ouml;`\n", 0));
}
TEST(Md4c_spec, Case322) {
  EXPECT_EQ("<pre><code>f&amp;ouml;f&amp;ouml;\n</code></pre>\n", render("    f&ouml;f&ouml;\n", 0));
}
TEST(Md4c_spec, Case323) {
  EXPECT_EQ("<p>*foo*\n<em>foo</em></p>\n", render("&#42;foo&#42;\n*foo*\n", 0));
}
TEST(Md4c_spec, Case324) {
  EXPECT_EQ("<p>* foo</p>\n<ul>\n<li>foo</li>\n</ul>\n", render("&#42; foo\n\n* foo\n", 0));
}
TEST(Md4c_spec, Case325) {
  EXPECT_EQ("<p>foo\n\nbar</p>\n", render("foo&#10;&#10;bar\n", 0));
}
TEST(Md4c_spec, Case326) {
  EXPECT_EQ("<p>\tfoo</p>\n", render("&#9;foo\n", 0));
}
TEST(Md4c_spec, Case327) {
  EXPECT_EQ("<p>[a](url &quot;tit&quot;)</p>\n", render("[a](url &quot;tit&quot;)\n", 0));
}
TEST(Md4c_spec, Case328) {
  EXPECT_EQ("<p><code>foo</code></p>\n", render("`foo`\n", 0));
}
TEST(Md4c_spec, Case329) {
  EXPECT_EQ("<p><code>foo ` bar</code></p>\n", render("`` foo ` bar ``\n", 0));
}
TEST(Md4c_spec, Case330) {
  EXPECT_EQ("<p><code>``</code></p>\n", render("` `` `\n", 0));
}
TEST(Md4c_spec, Case331) {
  EXPECT_EQ("<p><code> `` </code></p>\n", render("`  ``  `\n", 0));
}
TEST(Md4c_spec, Case332) {
  EXPECT_EQ("<p><code> a</code></p>\n", render("` a`\n", 0));
}
TEST(Md4c_spec, Case333) {
  EXPECT_EQ("<p><code> b </code></p>\n", render("` b `\n", 0));
}
TEST(Md4c_spec, Case334) {
  EXPECT_EQ("<p><code> </code>\n<code>  </code></p>\n", render("` `\n`  `\n", 0));
}
TEST(Md4c_spec, Case335) {
  EXPECT_EQ("<p><code>foo bar   baz</code></p>\n", render("``\nfoo\nbar  \nbaz\n``\n", 0));
}
TEST(Md4c_spec, Case336) {
  EXPECT_EQ("<p><code>foo </code></p>\n", render("``\nfoo \n``\n", 0));
}
TEST(Md4c_spec, Case337) {
  EXPECT_EQ("<p><code>foo   bar  baz</code></p>\n", render("`foo   bar \nbaz`\n", 0));
}
TEST(Md4c_spec, Case338) {
  EXPECT_EQ("<p><code>foo\\</code>bar`</p>\n", render("`foo\\`bar`\n", 0));
}
TEST(Md4c_spec, Case339) {
  EXPECT_EQ("<p><code>foo`bar</code></p>\n", render("``foo`bar``\n", 0));
}
TEST(Md4c_spec, Case340) {
  EXPECT_EQ("<p><code>foo `` bar</code></p>\n", render("` foo `` bar `\n", 0));
}
TEST(Md4c_spec, Case341) {
  EXPECT_EQ("<p>*foo<code>*</code></p>\n", render("*foo`*`\n", 0));
}
TEST(Md4c_spec, Case342) {
  EXPECT_EQ("<p>[not a <code>link](/foo</code>)</p>\n", render("[not a `link](/foo`)\n", 0));
}
TEST(Md4c_spec, Case343) {
  EXPECT_EQ("<p><code>&lt;a href=&quot;</code>&quot;&gt;`</p>\n", render("`<a href=\"`\">`\n", 0));
}
TEST(Md4c_spec, Case344) {
  EXPECT_EQ("<p><a href=\"`\">`</p>\n", render("<a href=\"`\">`\n", 0));
}
TEST(Md4c_spec, Case345) {
  EXPECT_EQ("<p><code>&lt;http://foo.bar.</code>baz&gt;`</p>\n", render("`<http://foo.bar.`baz>`\n", 0));
}
TEST(Md4c_spec, Case346) {
  EXPECT_EQ("<p><a href=\"http://foo.bar.%60baz\">http://foo.bar.`baz</a>`</p>\n", render("<http://foo.bar.`baz>`\n", 0));
}
TEST(Md4c_spec, Case347) {
  EXPECT_EQ("<p>```foo``</p>\n", render("```foo``\n", 0));
}
TEST(Md4c_spec, Case348) {
  EXPECT_EQ("<p>`foo</p>\n", render("`foo\n", 0));
}
TEST(Md4c_spec, Case349) {
  EXPECT_EQ("<p>`foo<code>bar</code></p>\n", render("`foo``bar``\n", 0));
}
TEST(Md4c_spec, Case350) {
  EXPECT_EQ("<p><em>foo bar</em></p>\n", render("*foo bar*\n", 0));
}
TEST(Md4c_spec, Case351) {
  EXPECT_EQ("<p>a * foo bar*</p>\n", render("a * foo bar*\n", 0));
}
TEST(Md4c_spec, Case352) {
  EXPECT_EQ("<p>a*&quot;foo&quot;*</p>\n", render("a*\"foo\"*\n", 0));
}
TEST(Md4c_spec, Case353) {
  EXPECT_EQ("<p>* a *</p>\n", render("* a *\n", 0));
}
TEST(Md4c_spec, Case354) {
  EXPECT_EQ("<p>foo<em>bar</em></p>\n", render("foo*bar*\n", 0));
}
TEST(Md4c_spec, Case355) {
  EXPECT_EQ("<p>5<em>6</em>78</p>\n", render("5*6*78\n", 0));
}
TEST(Md4c_spec, Case356) {
  EXPECT_EQ("<p><em>foo bar</em></p>\n", render("_foo bar_\n", 0));
}
TEST(Md4c_spec, Case357) {
  EXPECT_EQ("<p>_ foo bar_</p>\n", render("_ foo bar_\n", 0));
}
TEST(Md4c_spec, Case358) {
  EXPECT_EQ("<p>a_&quot;foo&quot;_</p>\n", render("a_\"foo\"_\n", 0));
}
TEST(Md4c_spec, Case359) {
  EXPECT_EQ("<p>foo_bar_</p>\n", render("foo_bar_\n", 0));
}
TEST(Md4c_spec, Case360) {
  EXPECT_EQ("<p>5_6_78</p>\n", render("5_6_78\n", 0));
}
TEST(Md4c_spec, Case361) {
  EXPECT_EQ("<p>пристаням_стремятся_</p>\n", render("пристаням_стремятся_\n", 0));
}
TEST(Md4c_spec, Case362) {
  EXPECT_EQ("<p>aa_&quot;bb&quot;_cc</p>\n", render("aa_\"bb\"_cc\n", 0));
}
TEST(Md4c_spec, Case363) {
  EXPECT_EQ("<p>foo-<em>(bar)</em></p>\n", render("foo-_(bar)_\n", 0));
}
TEST(Md4c_spec, Case364) {
  EXPECT_EQ("<p>_foo*</p>\n", render("_foo*\n", 0));
}
TEST(Md4c_spec, Case365) {
  EXPECT_EQ("<p>*foo bar *</p>\n", render("*foo bar *\n", 0));
}
TEST(Md4c_spec, Case366) {
  EXPECT_EQ("<p>*foo bar\n*</p>\n", render("*foo bar\n*\n", 0));
}
TEST(Md4c_spec, Case367) {
  EXPECT_EQ("<p>*(*foo)</p>\n", render("*(*foo)\n", 0));
}
TEST(Md4c_spec, Case368) {
  EXPECT_EQ("<p><em>(<em>foo</em>)</em></p>\n", render("*(*foo*)*\n", 0));
}
TEST(Md4c_spec, Case369) {
  EXPECT_EQ("<p><em>foo</em>bar</p>\n", render("*foo*bar\n", 0));
}
TEST(Md4c_spec, Case370) {
  EXPECT_EQ("<p>_foo bar _</p>\n", render("_foo bar _\n", 0));
}
TEST(Md4c_spec, Case371) {
  EXPECT_EQ("<p>_(_foo)</p>\n", render("_(_foo)\n", 0));
}
TEST(Md4c_spec, Case372) {
  EXPECT_EQ("<p><em>(<em>foo</em>)</em></p>\n", render("_(_foo_)_\n", 0));
}
TEST(Md4c_spec, Case373) {
  EXPECT_EQ("<p>_foo_bar</p>\n", render("_foo_bar\n", 0));
}
TEST(Md4c_spec, Case374) {
  EXPECT_EQ("<p>_пристаням_стремятся</p>\n", render("_пристаням_стремятся\n", 0));
}
TEST(Md4c_spec, Case375) {
  EXPECT_EQ("<p><em>foo_bar_baz</em></p>\n", render("_foo_bar_baz_\n", 0));
}
TEST(Md4c_spec, Case376) {
  EXPECT_EQ("<p><em>(bar)</em>.</p>\n", render("_(bar)_.\n", 0));
}
TEST(Md4c_spec, Case377) {
  EXPECT_EQ("<p><strong>foo bar</strong></p>\n", render("**foo bar**\n", 0));
}
TEST(Md4c_spec, Case378) {
  EXPECT_EQ("<p>** foo bar**</p>\n", render("** foo bar**\n", 0));
}
TEST(Md4c_spec, Case379) {
  EXPECT_EQ("<p>a**&quot;foo&quot;**</p>\n", render("a**\"foo\"**\n", 0));
}
TEST(Md4c_spec, Case380) {
  EXPECT_EQ("<p>foo<strong>bar</strong></p>\n", render("foo**bar**\n", 0));
}
TEST(Md4c_spec, Case381) {
  EXPECT_EQ("<p><strong>foo bar</strong></p>\n", render("__foo bar__\n", 0));
}
TEST(Md4c_spec, Case382) {
  EXPECT_EQ("<p>__ foo bar__</p>\n", render("__ foo bar__\n", 0));
}
TEST(Md4c_spec, Case383) {
  EXPECT_EQ("<p>__\nfoo bar__</p>\n", render("__\nfoo bar__\n", 0));
}
TEST(Md4c_spec, Case384) {
  EXPECT_EQ("<p>a__&quot;foo&quot;__</p>\n", render("a__\"foo\"__\n", 0));
}
TEST(Md4c_spec, Case385) {
  EXPECT_EQ("<p>foo__bar__</p>\n", render("foo__bar__\n", 0));
}
TEST(Md4c_spec, Case386) {
  EXPECT_EQ("<p>5__6__78</p>\n", render("5__6__78\n", 0));
}
TEST(Md4c_spec, Case387) {
  EXPECT_EQ("<p>пристаням__стремятся__</p>\n", render("пристаням__стремятся__\n", 0));
}
TEST(Md4c_spec, Case388) {
  EXPECT_EQ("<p><strong>foo, <strong>bar</strong>, baz</strong></p>\n", render("__foo, __bar__, baz__\n", 0));
}
TEST(Md4c_spec, Case389) {
  EXPECT_EQ("<p>foo-<strong>(bar)</strong></p>\n", render("foo-__(bar)__\n", 0));
}
TEST(Md4c_spec, Case390) {
  EXPECT_EQ("<p>**foo bar **</p>\n", render("**foo bar **\n", 0));
}
TEST(Md4c_spec, Case391) {
  EXPECT_EQ("<p>**(**foo)</p>\n", render("**(**foo)\n", 0));
}
TEST(Md4c_spec, Case392) {
  EXPECT_EQ("<p><em>(<strong>foo</strong>)</em></p>\n", render("*(**foo**)*\n", 0));
}
TEST(Md4c_spec, Case393) {
  EXPECT_EQ("<p><strong>Gomphocarpus (<em>Gomphocarpus physocarpus</em>, syn.\n<em>Asclepias physocarpa</em>)</strong></p>\n", render("**Gomphocarpus (*Gomphocarpus physocarpus*, syn.\n*Asclepias physocarpa*)**\n", 0));
}
TEST(Md4c_spec, Case394) {
  EXPECT_EQ("<p><strong>foo &quot;<em>bar</em>&quot; foo</strong></p>\n", render("**foo \"*bar*\" foo**\n", 0));
}
TEST(Md4c_spec, Case395) {
  EXPECT_EQ("<p><strong>foo</strong>bar</p>\n", render("**foo**bar\n", 0));
}
TEST(Md4c_spec, Case396) {
  EXPECT_EQ("<p>__foo bar __</p>\n", render("__foo bar __\n", 0));
}
TEST(Md4c_spec, Case397) {
  EXPECT_EQ("<p>__(__foo)</p>\n", render("__(__foo)\n", 0));
}
TEST(Md4c_spec, Case398) {
  EXPECT_EQ("<p><em>(<strong>foo</strong>)</em></p>\n", render("_(__foo__)_\n", 0));
}
TEST(Md4c_spec, Case399) {
  EXPECT_EQ("<p>__foo__bar</p>\n", render("__foo__bar\n", 0));
}
TEST(Md4c_spec, Case400) {
  EXPECT_EQ("<p>__пристаням__стремятся</p>\n", render("__пристаням__стремятся\n", 0));
}
TEST(Md4c_spec, Case401) {
  EXPECT_EQ("<p><strong>foo__bar__baz</strong></p>\n", render("__foo__bar__baz__\n", 0));
}
TEST(Md4c_spec, Case402) {
  EXPECT_EQ("<p><strong>(bar)</strong>.</p>\n", render("__(bar)__.\n", 0));
}
TEST(Md4c_spec, Case403) {
  EXPECT_EQ("<p><em>foo <a href=\"/url\">bar</a></em></p>\n", render("*foo [bar](/url)*\n", 0));
}
TEST(Md4c_spec, Case404) {
  EXPECT_EQ("<p><em>foo\nbar</em></p>\n", render("*foo\nbar*\n", 0));
}
TEST(Md4c_spec, Case405) {
  EXPECT_EQ("<p><em>foo <strong>bar</strong> baz</em></p>\n", render("_foo __bar__ baz_\n", 0));
}
TEST(Md4c_spec, Case406) {
  EXPECT_EQ("<p><em>foo <em>bar</em> baz</em></p>\n", render("_foo _bar_ baz_\n", 0));
}
TEST(Md4c_spec, Case407) {
  EXPECT_EQ("<p><em><em>foo</em> bar</em></p>\n", render("__foo_ bar_\n", 0));
}
TEST(Md4c_spec, Case408) {
  EXPECT_EQ("<p><em>foo <em>bar</em></em></p>\n", render("*foo *bar**\n", 0));
}
TEST(Md4c_spec, Case409) {
  EXPECT_EQ("<p><em>foo <strong>bar</strong> baz</em></p>\n", render("*foo **bar** baz*\n", 0));
}
TEST(Md4c_spec, Case410) {
  EXPECT_EQ("<p><em>foo<strong>bar</strong>baz</em></p>\n", render("*foo**bar**baz*\n", 0));
}
TEST(Md4c_spec, Case411) {
  EXPECT_EQ("<p><em>foo**bar</em></p>\n", render("*foo**bar*\n", 0));
}
TEST(Md4c_spec, Case412) {
  EXPECT_EQ("<p><em><strong>foo</strong> bar</em></p>\n", render("***foo** bar*\n", 0));
}
TEST(Md4c_spec, Case413) {
  EXPECT_EQ("<p><em>foo <strong>bar</strong></em></p>\n", render("*foo **bar***\n", 0));
}
TEST(Md4c_spec, Case414) {
  EXPECT_EQ("<p><em>foo<strong>bar</strong></em></p>\n", render("*foo**bar***\n", 0));
}
TEST(Md4c_spec, Case415) {
  EXPECT_EQ("<p>foo<em><strong>bar</strong></em>baz</p>\n", render("foo***bar***baz\n", 0));
}
TEST(Md4c_spec, Case416) {
  EXPECT_EQ("<p>foo<strong><strong><strong>bar</strong></strong></strong>***baz</p>\n", render("foo******bar*********baz\n", 0));
}
TEST(Md4c_spec, Case417) {
  EXPECT_EQ("<p><em>foo <strong>bar <em>baz</em> bim</strong> bop</em></p>\n", render("*foo **bar *baz* bim** bop*\n", 0));
}
TEST(Md4c_spec, Case418) {
  EXPECT_EQ("<p><em>foo <a href=\"/url\"><em>bar</em></a></em></p>\n", render("*foo [*bar*](/url)*\n", 0));
}
TEST(Md4c_spec, Case419) {
  EXPECT_EQ("<p>** is not an empty emphasis</p>\n", render("** is not an empty emphasis\n", 0));
}
TEST(Md4c_spec, Case420) {
  EXPECT_EQ("<p>**** is not an empty strong emphasis</p>\n", render("**** is not an empty strong emphasis\n", 0));
}
TEST(Md4c_spec, Case421) {
  EXPECT_EQ("<p><strong>foo <a href=\"/url\">bar</a></strong></p>\n", render("**foo [bar](/url)**\n", 0));
}
TEST(Md4c_spec, Case422) {
  EXPECT_EQ("<p><strong>foo\nbar</strong></p>\n", render("**foo\nbar**\n", 0));
}
TEST(Md4c_spec, Case423) {
  EXPECT_EQ("<p><strong>foo <em>bar</em> baz</strong></p>\n", render("__foo _bar_ baz__\n", 0));
}
TEST(Md4c_spec, Case424) {
  EXPECT_EQ("<p><strong>foo <strong>bar</strong> baz</strong></p>\n", render("__foo __bar__ baz__\n", 0));
}
TEST(Md4c_spec, Case425) {
  EXPECT_EQ("<p><strong><strong>foo</strong> bar</strong></p>\n", render("____foo__ bar__\n", 0));
}
TEST(Md4c_spec, Case426) {
  EXPECT_EQ("<p><strong>foo <strong>bar</strong></strong></p>\n", render("**foo **bar****\n", 0));
}
TEST(Md4c_spec, Case427) {
  EXPECT_EQ("<p><strong>foo <em>bar</em> baz</strong></p>\n", render("**foo *bar* baz**\n", 0));
}
TEST(Md4c_spec, Case428) {
  EXPECT_EQ("<p><strong>foo<em>bar</em>baz</strong></p>\n", render("**foo*bar*baz**\n", 0));
}
TEST(Md4c_spec, Case429) {
  EXPECT_EQ("<p><strong><em>foo</em> bar</strong></p>\n", render("***foo* bar**\n", 0));
}
TEST(Md4c_spec, Case430) {
  EXPECT_EQ("<p><strong>foo <em>bar</em></strong></p>\n", render("**foo *bar***\n", 0));
}
TEST(Md4c_spec, Case431) {
  EXPECT_EQ("<p><strong>foo <em>bar <strong>baz</strong>\nbim</em> bop</strong></p>\n", render("**foo *bar **baz**\nbim* bop**\n", 0));
}
TEST(Md4c_spec, Case432) {
  EXPECT_EQ("<p><strong>foo <a href=\"/url\"><em>bar</em></a></strong></p>\n", render("**foo [*bar*](/url)**\n", 0));
}
TEST(Md4c_spec, Case433) {
  EXPECT_EQ("<p>__ is not an empty emphasis</p>\n", render("__ is not an empty emphasis\n", 0));
}
TEST(Md4c_spec, Case434) {
  EXPECT_EQ("<p>____ is not an empty strong emphasis</p>\n", render("____ is not an empty strong emphasis\n", 0));
}
TEST(Md4c_spec, Case435) {
  EXPECT_EQ("<p>foo ***</p>\n", render("foo ***\n", 0));
}
TEST(Md4c_spec, Case436) {
  EXPECT_EQ("<p>foo <em>*</em></p>\n", render("foo *\\**\n", 0));
}
TEST(Md4c_spec, Case437) {
  EXPECT_EQ("<p>foo <em>_</em></p>\n", render("foo *_*\n", 0));
}
TEST(Md4c_spec, Case438) {
  EXPECT_EQ("<p>foo *****</p>\n", render("foo *****\n", 0));
}
TEST(Md4c_spec, Case439) {
  EXPECT_EQ("<p>foo <strong>*</strong></p>\n", render("foo **\\***\n", 0));
}
TEST(Md4c_spec, Case440) {
  EXPECT_EQ("<p>foo <strong>_</strong></p>\n", render("foo **_**\n", 0));
}
TEST(Md4c_spec, Case441) {
  EXPECT_EQ("<p>*<em>foo</em></p>\n", render("**foo*\n", 0));
}
TEST(Md4c_spec, Case442) {
  EXPECT_EQ("<p><em>foo</em>*</p>\n", render("*foo**\n", 0));
}
TEST(Md4c_spec, Case443) {
  EXPECT_EQ("<p>*<strong>foo</strong></p>\n", render("***foo**\n", 0));
}
TEST(Md4c_spec, Case444) {
  EXPECT_EQ("<p>***<em>foo</em></p>\n", render("****foo*\n", 0));
}
TEST(Md4c_spec, Case445) {
  EXPECT_EQ("<p><strong>foo</strong>*</p>\n", render("**foo***\n", 0));
}
TEST(Md4c_spec, Case446) {
  EXPECT_EQ("<p><em>foo</em>***</p>\n", render("*foo****\n", 0));
}
TEST(Md4c_spec, Case447) {
  EXPECT_EQ("<p>foo ___</p>\n", render("foo ___\n", 0));
}
TEST(Md4c_spec, Case448) {
  EXPECT_EQ("<p>foo <em>_</em></p>\n", render("foo _\\__\n", 0));
}
TEST(Md4c_spec, Case449) {
  EXPECT_EQ("<p>foo <em>*</em></p>\n", render("foo _*_\n", 0));
}
TEST(Md4c_spec, Case450) {
  EXPECT_EQ("<p>foo _____</p>\n", render("foo _____\n", 0));
}
TEST(Md4c_spec, Case451) {
  EXPECT_EQ("<p>foo <strong>_</strong></p>\n", render("foo __\\___\n", 0));
}
TEST(Md4c_spec, Case452) {
  EXPECT_EQ("<p>foo <strong>*</strong></p>\n", render("foo __*__\n", 0));
}
TEST(Md4c_spec, Case453) {
  EXPECT_EQ("<p>_<em>foo</em></p>\n", render("__foo_\n", 0));
}
TEST(Md4c_spec, Case454) {
  EXPECT_EQ("<p><em>foo</em>_</p>\n", render("_foo__\n", 0));
}
TEST(Md4c_spec, Case455) {
  EXPECT_EQ("<p>_<strong>foo</strong></p>\n", render("___foo__\n", 0));
}
TEST(Md4c_spec, Case456) {
  EXPECT_EQ("<p>___<em>foo</em></p>\n", render("____foo_\n", 0));
}
TEST(Md4c_spec, Case457) {
  EXPECT_EQ("<p><strong>foo</strong>_</p>\n", render("__foo___\n", 0));
}
TEST(Md4c_spec, Case458) {
  EXPECT_EQ("<p><em>foo</em>___</p>\n", render("_foo____\n", 0));
}
TEST(Md4c_spec, Case459) {
  EXPECT_EQ("<p><strong>foo</strong></p>\n", render("**foo**\n", 0));
}
TEST(Md4c_spec, Case460) {
  EXPECT_EQ("<p><em><em>foo</em></em></p>\n", render("*_foo_*\n", 0));
}
TEST(Md4c_spec, Case461) {
  EXPECT_EQ("<p><strong>foo</strong></p>\n", render("__foo__\n", 0));
}
TEST(Md4c_spec, Case462) {
  EXPECT_EQ("<p><em><em>foo</em></em></p>\n", render("_*foo*_\n", 0));
}
TEST(Md4c_spec, Case463) {
  EXPECT_EQ("<p><strong><strong>foo</strong></strong></p>\n", render("****foo****\n", 0));
}
TEST(Md4c_spec, Case464) {
  EXPECT_EQ("<p><strong><strong>foo</strong></strong></p>\n", render("____foo____\n", 0));
}
TEST(Md4c_spec, Case465) {
  EXPECT_EQ("<p><strong><strong><strong>foo</strong></strong></strong></p>\n", render("******foo******\n", 0));
}
TEST(Md4c_spec, Case466) {
  EXPECT_EQ("<p><em><strong>foo</strong></em></p>\n", render("***foo***\n", 0));
}
TEST(Md4c_spec, Case467) {
  EXPECT_EQ("<p><em><strong><strong>foo</strong></strong></em></p>\n", render("_____foo_____\n", 0));
}
TEST(Md4c_spec, Case468) {
  EXPECT_EQ("<p><em>foo _bar</em> baz_</p>\n", render("*foo _bar* baz_\n", 0));
}
TEST(Md4c_spec, Case469) {
  EXPECT_EQ("<p><em>foo <strong>bar *baz bim</strong> bam</em></p>\n", render("*foo __bar *baz bim__ bam*\n", 0));
}
TEST(Md4c_spec, Case470) {
  EXPECT_EQ("<p>**foo <strong>bar baz</strong></p>\n", render("**foo **bar baz**\n", 0));
}
TEST(Md4c_spec, Case471) {
  EXPECT_EQ("<p>*foo <em>bar baz</em></p>\n", render("*foo *bar baz*\n", 0));
}
TEST(Md4c_spec, Case472) {
  EXPECT_EQ("<p>*<a href=\"/url\">bar*</a></p>\n", render("*[bar*](/url)\n", 0));
}
TEST(Md4c_spec, Case473) {
  EXPECT_EQ("<p>_foo <a href=\"/url\">bar_</a></p>\n", render("_foo [bar_](/url)\n", 0));
}
TEST(Md4c_spec, Case474) {
  EXPECT_EQ("<p>*<img src=\"foo\" title=\"*\"/></p>\n", render("*<img src=\"foo\" title=\"*\"/>\n", 0));
}
TEST(Md4c_spec, Case475) {
  EXPECT_EQ("<p>**<a href=\"**\"></p>\n", render("**<a href=\"**\">\n", 0));
}
TEST(Md4c_spec, Case476) {
  EXPECT_EQ("<p>__<a href=\"__\"></p>\n", render("__<a href=\"__\">\n", 0));
}
TEST(Md4c_spec, Case477) {
  EXPECT_EQ("<p><em>a <code>*</code></em></p>\n", render("*a `*`*\n", 0));
}
TEST(Md4c_spec, Case478) {
  EXPECT_EQ("<p><em>a <code>_</code></em></p>\n", render("_a `_`_\n", 0));
}
TEST(Md4c_spec, Case479) {
  EXPECT_EQ("<p>**a<a href=\"http://foo.bar/?q=**\">http://foo.bar/?q=**</a></p>\n", render("**a<http://foo.bar/?q=**>\n", 0));
}
TEST(Md4c_spec, Case480) {
  EXPECT_EQ("<p>__a<a href=\"http://foo.bar/?q=__\">http://foo.bar/?q=__</a></p>\n", render("__a<http://foo.bar/?q=__>\n", 0));
}
TEST(Md4c_spec, Case481) {
  EXPECT_EQ("<p><a href=\"/uri\" title=\"title\">link</a></p>\n", render("[link](/uri \"title\")\n", 0));
}
TEST(Md4c_spec, Case482) {
  EXPECT_EQ("<p><a href=\"/uri\">link</a></p>\n", render("[link](/uri)\n", 0));
}
TEST(Md4c_spec, Case483) {
  EXPECT_EQ("<p><a href=\"\">link</a></p>\n", render("[link]()\n", 0));
}
TEST(Md4c_spec, Case484) {
  EXPECT_EQ("<p><a href=\"\">link</a></p>\n", render("[link](<>)\n", 0));
}
TEST(Md4c_spec, Case485) {
  EXPECT_EQ("<p>[link](/my uri)</p>\n", render("[link](/my uri)\n", 0));
}
TEST(Md4c_spec, Case486) {
  EXPECT_EQ("<p><a href=\"/my%20uri\">link</a></p>\n", render("[link](</my uri>)\n", 0));
}
TEST(Md4c_spec, Case487) {
  EXPECT_EQ("<p>[link](foo\nbar)</p>\n", render("[link](foo\nbar)\n", 0));
}
TEST(Md4c_spec, Case488) {
  EXPECT_EQ("<p>[link](<foo\nbar>)</p>\n", render("[link](<foo\nbar>)\n", 0));
}
TEST(Md4c_spec, Case489) {
  EXPECT_EQ("<p><a href=\"b)c\">a</a></p>\n", render("[a](<b)c>)\n", 0));
}
TEST(Md4c_spec, Case490) {
  EXPECT_EQ("<p>[link](&lt;foo&gt;)</p>\n", render("[link](<foo\\>)\n", 0));
}
TEST(Md4c_spec, Case491) {
  EXPECT_EQ("<p>[a](&lt;b)c\n[a](&lt;b)c&gt;\n[a](<b>c)</p>\n", render("[a](<b)c\n[a](<b)c>\n[a](<b>c)\n", 0));
}
TEST(Md4c_spec, Case492) {
  EXPECT_EQ("<p><a href=\"(foo)\">link</a></p>\n", render("[link](\\(foo\\))\n", 0));
}
TEST(Md4c_spec, Case493) {
  EXPECT_EQ("<p><a href=\"foo(and(bar))\">link</a></p>\n", render("[link](foo(and(bar)))\n", 0));
}
TEST(Md4c_spec, Case494) {
  EXPECT_EQ("<p><a href=\"foo(and(bar)\">link</a></p>\n", render("[link](foo\\(and\\(bar\\))\n", 0));
}
TEST(Md4c_spec, Case495) {
  EXPECT_EQ("<p><a href=\"foo(and(bar)\">link</a></p>\n", render("[link](<foo(and(bar)>)\n", 0));
}
TEST(Md4c_spec, Case496) {
  EXPECT_EQ("<p><a href=\"foo):\">link</a></p>\n", render("[link](foo\\)\\:)\n", 0));
}
TEST(Md4c_spec, Case497) {
  EXPECT_EQ("<p><a href=\"#fragment\">link</a></p>\n<p><a href=\"http://example.com#fragment\">link</a></p>\n<p><a href=\"http://example.com?foo=3#frag\">link</a></p>\n", render("[link](#fragment)\n\n[link](http://example.com#fragment)\n\n[link](http://example.com?foo=3#frag)\n", 0));
}
TEST(Md4c_spec, Case498) {
  EXPECT_EQ("<p><a href=\"foo%5Cbar\">link</a></p>\n", render("[link](foo\\bar)\n", 0));
}
TEST(Md4c_spec, Case499) {
  EXPECT_EQ("<p><a href=\"foo%20b%C3%A4\">link</a></p>\n", render("[link](foo%20b&auml;)\n", 0));
}
TEST(Md4c_spec, Case500) {
  EXPECT_EQ("<p><a href=\"%22title%22\">link</a></p>\n", render("[link](\"title\")\n", 0));
}
TEST(Md4c_spec, Case501) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">link</a>\n<a href=\"/url\" title=\"title\">link</a>\n<a href=\"/url\" title=\"title\">link</a></p>\n", render("[link](/url \"title\")\n[link](/url 'title')\n[link](/url (title))\n", 0));
}
TEST(Md4c_spec, Case502) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title &quot;&quot;\">link</a></p>\n", render("[link](/url \"title \\\"&quot;\")\n", 0));
}
TEST(Md4c_spec, Case503) {
  EXPECT_EQ("<p><a href=\"/url%C2%A0%22title%22\">link</a></p>\n", render("[link](/url \"title\")\n", 0));
}
TEST(Md4c_spec, Case504) {
  EXPECT_EQ("<p>[link](/url &quot;title &quot;and&quot; title&quot;)</p>\n", render("[link](/url \"title \"and\" title\")\n", 0));
}
TEST(Md4c_spec, Case505) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title &quot;and&quot; title\">link</a></p>\n", render("[link](/url 'title \"and\" title')\n", 0));
}
TEST(Md4c_spec, Case506) {
  EXPECT_EQ("<p><a href=\"/uri\" title=\"title\">link</a></p>\n", render("[link](   /uri\n  \"title\"  )\n", 0));
}
TEST(Md4c_spec, Case507) {
  EXPECT_EQ("<p>[link] (/uri)</p>\n", render("[link] (/uri)\n", 0));
}
TEST(Md4c_spec, Case508) {
  EXPECT_EQ("<p><a href=\"/uri\">link [foo [bar]]</a></p>\n", render("[link [foo [bar]]](/uri)\n", 0));
}
TEST(Md4c_spec, Case509) {
  EXPECT_EQ("<p>[link] bar](/uri)</p>\n", render("[link] bar](/uri)\n", 0));
}
TEST(Md4c_spec, Case510) {
  EXPECT_EQ("<p>[link <a href=\"/uri\">bar</a></p>\n", render("[link [bar](/uri)\n", 0));
}
TEST(Md4c_spec, Case511) {
  EXPECT_EQ("<p><a href=\"/uri\">link [bar</a></p>\n", render("[link \\[bar](/uri)\n", 0));
}
TEST(Md4c_spec, Case512) {
  EXPECT_EQ("<p><a href=\"/uri\">link <em>foo <strong>bar</strong> <code>#</code></em></a></p>\n", render("[link *foo **bar** `#`*](/uri)\n", 0));
}
TEST(Md4c_spec, Case513) {
  EXPECT_EQ("<p><a href=\"/uri\"><img src=\"moon.jpg\" alt=\"moon\"></a></p>\n", render("[![moon](moon.jpg)](/uri)\n", 0));
}
TEST(Md4c_spec, Case514) {
  EXPECT_EQ("<p>[foo <a href=\"/uri\">bar</a>](/uri)</p>\n", render("[foo [bar](/uri)](/uri)\n", 0));
}
TEST(Md4c_spec, Case515) {
  EXPECT_EQ("<p>[foo <em>[bar <a href=\"/uri\">baz</a>](/uri)</em>](/uri)</p>\n", render("[foo *[bar [baz](/uri)](/uri)*](/uri)\n", 0));
}
TEST(Md4c_spec, Case516) {
  EXPECT_EQ("<p><img src=\"uri3\" alt=\"[foo](uri2)\"></p>\n", render("![[[foo](uri1)](uri2)](uri3)\n", 0));
}
TEST(Md4c_spec, Case517) {
  EXPECT_EQ("<p>*<a href=\"/uri\">foo*</a></p>\n", render("*[foo*](/uri)\n", 0));
}
TEST(Md4c_spec, Case518) {
  EXPECT_EQ("<p><a href=\"baz*\">foo *bar</a></p>\n", render("[foo *bar](baz*)\n", 0));
}
TEST(Md4c_spec, Case519) {
  EXPECT_EQ("<p><em>foo [bar</em> baz]</p>\n", render("*foo [bar* baz]\n", 0));
}
TEST(Md4c_spec, Case520) {
  EXPECT_EQ("<p>[foo <bar attr=\"](baz)\"></p>\n", render("[foo <bar attr=\"](baz)\">\n", 0));
}
TEST(Md4c_spec, Case521) {
  EXPECT_EQ("<p>[foo<code>](/uri)</code></p>\n", render("[foo`](/uri)`\n", 0));
}
TEST(Md4c_spec, Case522) {
  EXPECT_EQ("<p>[foo<a href=\"http://example.com/?search=%5D(uri)\">http://example.com/?search=](uri)</a></p>\n", render("[foo<http://example.com/?search=](uri)>\n", 0));
}
TEST(Md4c_spec, Case523) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">foo</a></p>\n", render("[foo][bar]\n\n[bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case524) {
  EXPECT_EQ("<p><a href=\"/uri\">link [foo [bar]]</a></p>\n", render("[link [foo [bar]]][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case525) {
  EXPECT_EQ("<p><a href=\"/uri\">link [bar</a></p>\n", render("[link \\[bar][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case526) {
  EXPECT_EQ("<p><a href=\"/uri\">link <em>foo <strong>bar</strong> <code>#</code></em></a></p>\n", render("[link *foo **bar** `#`*][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case527) {
  EXPECT_EQ("<p><a href=\"/uri\"><img src=\"moon.jpg\" alt=\"moon\"></a></p>\n", render("[![moon](moon.jpg)][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case528) {
  EXPECT_EQ("<p>[foo <a href=\"/uri\">bar</a>]<a href=\"/uri\">ref</a></p>\n", render("[foo [bar](/uri)][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case529) {
  EXPECT_EQ("<p>[foo <em>bar <a href=\"/uri\">baz</a></em>]<a href=\"/uri\">ref</a></p>\n", render("[foo *bar [baz][ref]*][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case530) {
  EXPECT_EQ("<p>*<a href=\"/uri\">foo*</a></p>\n", render("*[foo*][ref]\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case531) {
  EXPECT_EQ("<p><a href=\"/uri\">foo *bar</a>*</p>\n", render("[foo *bar][ref]*\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case532) {
  EXPECT_EQ("<p>[foo <bar attr=\"][ref]\"></p>\n", render("[foo <bar attr=\"][ref]\">\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case533) {
  EXPECT_EQ("<p>[foo<code>][ref]</code></p>\n", render("[foo`][ref]`\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case534) {
  EXPECT_EQ("<p>[foo<a href=\"http://example.com/?search=%5D%5Bref%5D\">http://example.com/?search=][ref]</a></p>\n", render("[foo<http://example.com/?search=][ref]>\n\n[ref]: /uri\n", 0));
}
TEST(Md4c_spec, Case535) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">foo</a></p>\n", render("[foo][BaR]\n\n[bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case536) {
  EXPECT_EQ("<p><a href=\"/url\">ẞ</a></p>\n", render("[ẞ]\n\n[SS]: /url\n", 0));
}
TEST(Md4c_spec, Case537) {
  EXPECT_EQ("<p><a href=\"/url\">Baz</a></p>\n", render("[Foo\n  bar]: /url\n\n[Baz][Foo bar]\n", 0));
}
TEST(Md4c_spec, Case538) {
  EXPECT_EQ("<p>[foo] <a href=\"/url\" title=\"title\">bar</a></p>\n", render("[foo] [bar]\n\n[bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case539) {
  EXPECT_EQ("<p>[foo]\n<a href=\"/url\" title=\"title\">bar</a></p>\n", render("[foo]\n[bar]\n\n[bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case540) {
  EXPECT_EQ("<p><a href=\"/url1\">bar</a></p>\n", render("[foo]: /url1\n\n[foo]: /url2\n\n[bar][foo]\n", 0));
}
TEST(Md4c_spec, Case541) {
  EXPECT_EQ("<p>[bar][foo!]</p>\n", render("[bar][foo\\!]\n\n[foo!]: /url\n", 0));
}
TEST(Md4c_spec, Case542) {
  EXPECT_EQ("<p>[foo][ref[]</p>\n<p>[ref[]: /uri</p>\n", render("[foo][ref[]\n\n[ref[]: /uri\n", 0));
}
TEST(Md4c_spec, Case543) {
  EXPECT_EQ("<p>[foo][ref[bar]]</p>\n<p>[ref[bar]]: /uri</p>\n", render("[foo][ref[bar]]\n\n[ref[bar]]: /uri\n", 0));
}
TEST(Md4c_spec, Case544) {
  EXPECT_EQ("<p>[[[foo]]]</p>\n<p>[[[foo]]]: /url</p>\n", render("[[[foo]]]\n\n[[[foo]]]: /url\n", 0));
}
TEST(Md4c_spec, Case545) {
  EXPECT_EQ("<p><a href=\"/uri\">foo</a></p>\n", render("[foo][ref\\[]\n\n[ref\\[]: /uri\n", 0));
}
TEST(Md4c_spec, Case546) {
  EXPECT_EQ("<p><a href=\"/uri\">bar\\</a></p>\n", render("[bar\\\\]: /uri\n\n[bar\\\\]\n", 0));
}
TEST(Md4c_spec, Case547) {
  EXPECT_EQ("<p>[]</p>\n<p>[]: /uri</p>\n", render("[]\n\n[]: /uri\n", 0));
}
TEST(Md4c_spec, Case548) {
  EXPECT_EQ("<p>[\n]</p>\n<p>[\n]: /uri</p>\n", render("[\n ]\n\n[\n ]: /uri\n", 0));
}
TEST(Md4c_spec, Case549) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">foo</a></p>\n", render("[foo][]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case550) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\"><em>foo</em> bar</a></p>\n", render("[*foo* bar][]\n\n[*foo* bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case551) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">Foo</a></p>\n", render("[Foo][]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case552) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">foo</a>\n[]</p>\n", render("[foo] \n[]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case553) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">foo</a></p>\n", render("[foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case554) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\"><em>foo</em> bar</a></p>\n", render("[*foo* bar]\n\n[*foo* bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case555) {
  EXPECT_EQ("<p>[<a href=\"/url\" title=\"title\"><em>foo</em> bar</a>]</p>\n", render("[[*foo* bar]]\n\n[*foo* bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case556) {
  EXPECT_EQ("<p>[[bar <a href=\"/url\">foo</a></p>\n", render("[[bar [foo]\n\n[foo]: /url\n", 0));
}
TEST(Md4c_spec, Case557) {
  EXPECT_EQ("<p><a href=\"/url\" title=\"title\">Foo</a></p>\n", render("[Foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case558) {
  EXPECT_EQ("<p><a href=\"/url\">foo</a> bar</p>\n", render("[foo] bar\n\n[foo]: /url\n", 0));
}
TEST(Md4c_spec, Case559) {
  EXPECT_EQ("<p>[foo]</p>\n", render("\\[foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case560) {
  EXPECT_EQ("<p>*<a href=\"/url\">foo*</a></p>\n", render("[foo*]: /url\n\n*[foo*]\n", 0));
}
TEST(Md4c_spec, Case561) {
  EXPECT_EQ("<p><a href=\"/url2\">foo</a></p>\n", render("[foo][bar]\n\n[foo]: /url1\n[bar]: /url2\n", 0));
}
TEST(Md4c_spec, Case562) {
  EXPECT_EQ("<p><a href=\"/url1\">foo</a></p>\n", render("[foo][]\n\n[foo]: /url1\n", 0));
}
TEST(Md4c_spec, Case563) {
  EXPECT_EQ("<p><a href=\"\">foo</a></p>\n", render("[foo]()\n\n[foo]: /url1\n", 0));
}
TEST(Md4c_spec, Case564) {
  EXPECT_EQ("<p><a href=\"/url1\">foo</a>(not a link)</p>\n", render("[foo](not a link)\n\n[foo]: /url1\n", 0));
}
TEST(Md4c_spec, Case565) {
  EXPECT_EQ("<p>[foo]<a href=\"/url\">bar</a></p>\n", render("[foo][bar][baz]\n\n[baz]: /url\n", 0));
}
TEST(Md4c_spec, Case566) {
  EXPECT_EQ("<p><a href=\"/url2\">foo</a><a href=\"/url1\">baz</a></p>\n", render("[foo][bar][baz]\n\n[baz]: /url1\n[bar]: /url2\n", 0));
}
TEST(Md4c_spec, Case567) {
  EXPECT_EQ("<p>[foo]<a href=\"/url1\">bar</a></p>\n", render("[foo][bar][baz]\n\n[baz]: /url1\n[foo]: /url2\n", 0));
}
TEST(Md4c_spec, Case568) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo\" title=\"title\"></p>\n", render("![foo](/url \"title\")\n", 0));
}
TEST(Md4c_spec, Case569) {
  EXPECT_EQ("<p><img src=\"train.jpg\" alt=\"foo bar\" title=\"train &amp; tracks\"></p>\n", render("![foo *bar*]\n\n[foo *bar*]: train.jpg \"train & tracks\"\n", 0));
}
TEST(Md4c_spec, Case570) {
  EXPECT_EQ("<p><img src=\"/url2\" alt=\"foo bar\"></p>\n", render("![foo ![bar](/url)](/url2)\n", 0));
}
TEST(Md4c_spec, Case571) {
  EXPECT_EQ("<p><img src=\"/url2\" alt=\"foo bar\"></p>\n", render("![foo [bar](/url)](/url2)\n", 0));
}
TEST(Md4c_spec, Case572) {
  EXPECT_EQ("<p><img src=\"train.jpg\" alt=\"foo bar\" title=\"train &amp; tracks\"></p>\n", render("![foo *bar*][]\n\n[foo *bar*]: train.jpg \"train & tracks\"\n", 0));
}
TEST(Md4c_spec, Case573) {
  EXPECT_EQ("<p><img src=\"train.jpg\" alt=\"foo bar\" title=\"train &amp; tracks\"></p>\n", render("![foo *bar*][foobar]\n\n[FOOBAR]: train.jpg \"train & tracks\"\n", 0));
}
TEST(Md4c_spec, Case574) {
  EXPECT_EQ("<p><img src=\"train.jpg\" alt=\"foo\"></p>\n", render("![foo](train.jpg)\n", 0));
}
TEST(Md4c_spec, Case575) {
  EXPECT_EQ("<p>My <img src=\"/path/to/train.jpg\" alt=\"foo bar\" title=\"title\"></p>\n", render("My ![foo bar](/path/to/train.jpg  \"title\"   )\n", 0));
}
TEST(Md4c_spec, Case576) {
  EXPECT_EQ("<p><img src=\"url\" alt=\"foo\"></p>\n", render("![foo](<url>)\n", 0));
}
TEST(Md4c_spec, Case577) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"\"></p>\n", render("![](/url)\n", 0));
}
TEST(Md4c_spec, Case578) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo\"></p>\n", render("![foo][bar]\n\n[bar]: /url\n", 0));
}
TEST(Md4c_spec, Case579) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo\"></p>\n", render("![foo][bar]\n\n[BAR]: /url\n", 0));
}
TEST(Md4c_spec, Case580) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo\" title=\"title\"></p>\n", render("![foo][]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case581) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo bar\" title=\"title\"></p>\n", render("![*foo* bar][]\n\n[*foo* bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case582) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"Foo\" title=\"title\"></p>\n", render("![Foo][]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case583) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo\" title=\"title\">\n[]</p>\n", render("![foo] \n[]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case584) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo\" title=\"title\"></p>\n", render("![foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case585) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"foo bar\" title=\"title\"></p>\n", render("![*foo* bar]\n\n[*foo* bar]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case586) {
  EXPECT_EQ("<p>![[foo]]</p>\n<p>[[foo]]: /url &quot;title&quot;</p>\n", render("![[foo]]\n\n[[foo]]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case587) {
  EXPECT_EQ("<p><img src=\"/url\" alt=\"Foo\" title=\"title\"></p>\n", render("![Foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case588) {
  EXPECT_EQ("<p>![foo]</p>\n", render("!\\[foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case589) {
  EXPECT_EQ("<p>!<a href=\"/url\" title=\"title\">foo</a></p>\n", render("\\![foo]\n\n[foo]: /url \"title\"\n", 0));
}
TEST(Md4c_spec, Case590) {
  EXPECT_EQ("<p><a href=\"http://foo.bar.baz\">http://foo.bar.baz</a></p>\n", render("<http://foo.bar.baz>\n", 0));
}
TEST(Md4c_spec, Case591) {
  EXPECT_EQ("<p><a href=\"http://foo.bar.baz/test?q=hello&amp;id=22&amp;boolean\">http://foo.bar.baz/test?q=hello&amp;id=22&amp;boolean</a></p>\n", render("<http://foo.bar.baz/test?q=hello&id=22&boolean>\n", 0));
}
TEST(Md4c_spec, Case592) {
  EXPECT_EQ("<p><a href=\"irc://foo.bar:2233/baz\">irc://foo.bar:2233/baz</a></p>\n", render("<irc://foo.bar:2233/baz>\n", 0));
}
TEST(Md4c_spec, Case593) {
  EXPECT_EQ("<p><a href=\"MAILTO:FOO@BAR.BAZ\">MAILTO:FOO@BAR.BAZ</a></p>\n", render("<MAILTO:FOO@BAR.BAZ>\n", 0));
}
TEST(Md4c_spec, Case594) {
  EXPECT_EQ("<p><a href=\"a+b+c:d\">a+b+c:d</a></p>\n", render("<a+b+c:d>\n", 0));
}
TEST(Md4c_spec, Case595) {
  EXPECT_EQ("<p><a href=\"made-up-scheme://foo,bar\">made-up-scheme://foo,bar</a></p>\n", render("<made-up-scheme://foo,bar>\n", 0));
}
TEST(Md4c_spec, Case596) {
  EXPECT_EQ("<p><a href=\"http://../\">http://../</a></p>\n", render("<http://../>\n", 0));
}
TEST(Md4c_spec, Case597) {
  EXPECT_EQ("<p><a href=\"localhost:5001/foo\">localhost:5001/foo</a></p>\n", render("<localhost:5001/foo>\n", 0));
}
TEST(Md4c_spec, Case598) {
  EXPECT_EQ("<p>&lt;http://foo.bar/baz bim&gt;</p>\n", render("<http://foo.bar/baz bim>\n", 0));
}
TEST(Md4c_spec, Case599) {
  EXPECT_EQ("<p><a href=\"http://example.com/%5C%5B%5C\">http://example.com/\\[\\</a></p>\n", render("<http://example.com/\\[\\>\n", 0));
}
TEST(Md4c_spec, Case600) {
  EXPECT_EQ("<p><a href=\"mailto:foo@bar.example.com\">foo@bar.example.com</a></p>\n", render("<foo@bar.example.com>\n", 0));
}
TEST(Md4c_spec, Case601) {
  EXPECT_EQ("<p><a href=\"mailto:foo+special@Bar.baz-bar0.com\">foo+special@Bar.baz-bar0.com</a></p>\n", render("<foo+special@Bar.baz-bar0.com>\n", 0));
}
TEST(Md4c_spec, Case602) {
  EXPECT_EQ("<p>&lt;foo+@bar.example.com&gt;</p>\n", render("<foo\\+@bar.example.com>\n", 0));
}
TEST(Md4c_spec, Case603) {
  EXPECT_EQ("<p>&lt;&gt;</p>\n", render("<>\n", 0));
}
TEST(Md4c_spec, Case604) {
  EXPECT_EQ("<p>&lt; http://foo.bar &gt;</p>\n", render("< http://foo.bar >\n", 0));
}
TEST(Md4c_spec, Case605) {
  EXPECT_EQ("<p>&lt;m:abc&gt;</p>\n", render("<m:abc>\n", 0));
}
TEST(Md4c_spec, Case606) {
  EXPECT_EQ("<p>&lt;foo.bar.baz&gt;</p>\n", render("<foo.bar.baz>\n", 0));
}
TEST(Md4c_spec, Case607) {
  EXPECT_EQ("<p>http://example.com</p>\n", render("http://example.com\n", 0));
}
TEST(Md4c_spec, Case608) {
  EXPECT_EQ("<p>foo@bar.example.com</p>\n", render("foo@bar.example.com\n", 0));
}
TEST(Md4c_spec, Case609) {
  EXPECT_EQ("<p><a><bab><c2c></p>\n", render("<a><bab><c2c>\n", 0));
}
TEST(Md4c_spec, Case610) {
  EXPECT_EQ("<p><a/><b2/></p>\n", render("<a/><b2/>\n", 0));
}
TEST(Md4c_spec, Case611) {
  EXPECT_EQ("<p><a  /><b2\ndata=\"foo\" ></p>\n", render("<a  /><b2\ndata=\"foo\" >\n", 0));
}
TEST(Md4c_spec, Case612) {
  EXPECT_EQ("<p><a foo=\"bar\" bam = 'baz <em>\"</em>'\n_boolean zoop:33=zoop:33 /></p>\n", render("<a foo=\"bar\" bam = 'baz <em>\"</em>'\n_boolean zoop:33=zoop:33 />\n", 0));
}
TEST(Md4c_spec, Case613) {
  EXPECT_EQ("<p>Foo <responsive-image src=\"foo.jpg\" /></p>\n", render("Foo <responsive-image src=\"foo.jpg\" />\n", 0));
}
TEST(Md4c_spec, Case614) {
  EXPECT_EQ("<p>&lt;33&gt; &lt;__&gt;</p>\n", render("<33> <__>\n", 0));
}
TEST(Md4c_spec, Case615) {
  EXPECT_EQ("<p>&lt;a h*#ref=&quot;hi&quot;&gt;</p>\n", render("<a h*#ref=\"hi\">\n", 0));
}
TEST(Md4c_spec, Case616) {
  EXPECT_EQ("<p>&lt;a href=&quot;hi'&gt; &lt;a href=hi'&gt;</p>\n", render("<a href=\"hi'> <a href=hi'>\n", 0));
}
TEST(Md4c_spec, Case617) {
  EXPECT_EQ("<p>&lt; a&gt;&lt;\nfoo&gt;&lt;bar/ &gt;\n&lt;foo bar=baz\nbim!bop /&gt;</p>\n", render("< a><\nfoo><bar/ >\n<foo bar=baz\nbim!bop />\n", 0));
}
TEST(Md4c_spec, Case618) {
  EXPECT_EQ("<p>&lt;a href='bar'title=title&gt;</p>\n", render("<a href='bar'title=title>\n", 0));
}
TEST(Md4c_spec, Case619) {
  EXPECT_EQ("<p></a></foo ></p>\n", render("</a></foo >\n", 0));
}
TEST(Md4c_spec, Case620) {
  EXPECT_EQ("<p>&lt;/a href=&quot;foo&quot;&gt;</p>\n", render("</a href=\"foo\">\n", 0));
}
TEST(Md4c_spec, Case621) {
  EXPECT_EQ("<p>foo <!-- this is a\ncomment - with hyphen --></p>\n", render("foo <!-- this is a\ncomment - with hyphen -->\n", 0));
}
TEST(Md4c_spec, Case622) {
  EXPECT_EQ("<p>foo &lt;!-- not a comment -- two hyphens --&gt;</p>\n", render("foo <!-- not a comment -- two hyphens -->\n", 0));
}
TEST(Md4c_spec, Case623) {
  EXPECT_EQ("<p>foo &lt;!--&gt; foo --&gt;</p>\n<p>foo &lt;!-- foo---&gt;</p>\n", render("foo <!--> foo -->\n\nfoo <!-- foo--->\n", 0));
}
TEST(Md4c_spec, Case624) {
  EXPECT_EQ("<p>foo <?php echo $a; ?></p>\n", render("foo <?php echo $a; ?>\n", 0));
}
TEST(Md4c_spec, Case625) {
  EXPECT_EQ("<p>foo <!ELEMENT br EMPTY></p>\n", render("foo <!ELEMENT br EMPTY>\n", 0));
}
TEST(Md4c_spec, Case626) {
  EXPECT_EQ("<p>foo <![CDATA[>&<]]></p>\n", render("foo <![CDATA[>&<]]>\n", 0));
}
TEST(Md4c_spec, Case627) {
  EXPECT_EQ("<p>foo <a href=\"&ouml;\"></p>\n", render("foo <a href=\"&ouml;\">\n", 0));
}
TEST(Md4c_spec, Case628) {
  EXPECT_EQ("<p>foo <a href=\"\\*\"></p>\n", render("foo <a href=\"\\*\">\n", 0));
}
TEST(Md4c_spec, Case629) {
  EXPECT_EQ("<p>&lt;a href=&quot;&quot;&quot;&gt;</p>\n", render("<a href=\"\\\"\">\n", 0));
}
TEST(Md4c_spec, Case630) {
  EXPECT_EQ("<p>foo<br>\nbaz</p>\n", render("foo  \nbaz\n", 0));
}
TEST(Md4c_spec, Case631) {
  EXPECT_EQ("<p>foo<br>\nbaz</p>\n", render("foo\\\nbaz\n", 0));
}
TEST(Md4c_spec, Case632) {
  EXPECT_EQ("<p>foo<br>\nbaz</p>\n", render("foo       \nbaz\n", 0));
}
TEST(Md4c_spec, Case633) {
  EXPECT_EQ("<p>foo<br>\nbar</p>\n", render("foo  \n     bar\n", 0));
}
TEST(Md4c_spec, Case634) {
  EXPECT_EQ("<p>foo<br>\nbar</p>\n", render("foo\\\n     bar\n", 0));
}
TEST(Md4c_spec, Case635) {
  EXPECT_EQ("<p><em>foo<br>\nbar</em></p>\n", render("*foo  \nbar*\n", 0));
}
TEST(Md4c_spec, Case636) {
  EXPECT_EQ("<p><em>foo<br>\nbar</em></p>\n", render("*foo\\\nbar*\n", 0));
}
TEST(Md4c_spec, Case637) {
  EXPECT_EQ("<p><code>code  span</code></p>\n", render("`code \nspan`\n", 0));
}
TEST(Md4c_spec, Case638) {
  EXPECT_EQ("<p><code>code\\ span</code></p>\n", render("`code\\\nspan`\n", 0));
}
TEST(Md4c_spec, Case639) {
  EXPECT_EQ("<p><a href=\"foo  \nbar\"></p>\n", render("<a href=\"foo  \nbar\">\n", 0));
}
TEST(Md4c_spec, Case640) {
  EXPECT_EQ("<p><a href=\"foo\\\nbar\"></p>\n", render("<a href=\"foo\\\nbar\">\n", 0));
}
TEST(Md4c_spec, Case641) {
  EXPECT_EQ("<p>foo\\</p>\n", render("foo\\\n", 0));
}
TEST(Md4c_spec, Case642) {
  EXPECT_EQ("<p>foo</p>\n", render("foo  \n", 0));
}
TEST(Md4c_spec, Case643) {
  EXPECT_EQ("<h3>foo\\</h3>\n", render("### foo\\\n", 0));
}
TEST(Md4c_spec, Case644) {
  EXPECT_EQ("<h3>foo</h3>\n", render("### foo  \n", 0));
}
TEST(Md4c_spec, Case645) {
  EXPECT_EQ("<p>foo\nbaz</p>\n", render("foo\nbaz\n", 0));
}
TEST(Md4c_spec, Case646) {
  EXPECT_EQ("<p>foo\nbaz</p>\n", render("foo \n baz\n", 0));
}
TEST(Md4c_spec, Case647) {
  EXPECT_EQ("<p>hello $.;'there</p>\n", render("hello $.;'there\n", 0));
}
TEST(Md4c_spec, Case648) {
  EXPECT_EQ("<p>Foo χρῆν</p>\n", render("Foo χρῆν\n", 0));
}
TEST(Md4c_spec, Case649) {
  EXPECT_EQ("<p>Multiple     spaces</p>\n", render("Multiple     spaces\n", 0));
}
