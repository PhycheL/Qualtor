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
TEST(Md4c_tables, Case1) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("| Column 1 | Column 2 |\n|----------|----------|\n| foo      | bar      |\n| baz      | qux      |\n| quux     | quuz     |\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case2) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 | Column 2 |\n---------|--------- |\nfoo      | bar      |\nbaz      | qux      |\nquux     | quuz     |\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case3) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("| Column 1 | Column 2\n|----------|---------\n| foo      | bar\n| baz      | qux\n| quux     | quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case4) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 | Column 2\n---------|---------\nfoo      | bar\nbaz      | qux\nquux     | quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case5) {
  EXPECT_EQ("<h2>Column 1</h2>\n<p>foo\nbaz\nquux</p>\n", render("Column 1\n--------\nfoo\nbaz\nquux\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case6) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 |Column 2\n---|---\nfoo | bar\nbaz| qux\nquux|quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case7) {
  EXPECT_EQ("<p>Lorem ipsum dolor sit amet.\n| Column 1 | Column 2\n| ---------|---------\n| foo      | bar\n| baz      | qux\n| quux     | quuz</p>\n", render("Lorem ipsum dolor sit amet.\n| Column 1 | Column 2\n| ---------|---------\n| foo      | bar\n| baz      | qux\n| quux     | quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case8) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n<tr>\n<td>Lorem ipsum dolor sit amet.</td>\n<td></td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 | Column 2\n---------|---------\nfoo      | bar\nbaz      | qux\nquux     | quuz\nLorem ipsum dolor sit amet.\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case9) {
  EXPECT_EQ("<p>| Column 1 | Column 2\n| ---------|--\n| foo      | bar\n| baz      | qux\n| quux     | quuz</p>\n", render("| Column 1 | Column 2\n| ---------|--\n| foo      | bar\n| baz      | qux\n| quux     | quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case10) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th align=\"left\">Column 2</th>\n<th align=\"center\">Column 3</th>\n<th align=\"right\">Column 4</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>default</td>\n<td align=\"left\">left</td>\n<td align=\"center\">center</td>\n<td align=\"right\">right</td>\n</tr>\n</tbody>\n</table>\n", render("| Column 1 | Column 2 | Column 3 | Column 4 |\n|----------|:---------|:--------:|---------:|\n| default  | left     | center   | right    |\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case11) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>foo</td>\n<td>bar</td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux | xyzzy</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 | Column 2\n---------|---------\nfoo      | bar\nbaz      | qux \\| xyzzy\nquux     | quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case12) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td><em>foo</em></td>\n<td>bar</td>\n</tr>\n<tr>\n<td><strong>baz</strong></td>\n<td><a href=\"/url\">qux</a></td>\n</tr>\n<tr>\n<td>quux</td>\n<td><a href=\"/url2\">quuz</a></td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 | Column 2\n---------|---------\n*foo*    | bar\n**baz**  | [qux]\nquux     | [quuz](/url2)\n\n[qux]: /url\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case13) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>Column 1</th>\n<th>Column 2</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td><code>foo     | bar</code></td>\n<td></td>\n</tr>\n<tr>\n<td>baz</td>\n<td>qux</td>\n</tr>\n<tr>\n<td>quux</td>\n<td>quuz</td>\n</tr>\n</tbody>\n</table>\n", render("Column 1 | Column 2\n---------|---------\n`foo     | bar`\nbaz      | qux\nquux     | quuz\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case14) {
  EXPECT_EQ("<ul>\n<li>x|x\n---|---</li>\n</ul>\n", render("* x|x\n---|---\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case15) {
  EXPECT_EQ("<ul>\n<li><table>\n<thead>\n<tr>\n<th>x</th>\n<th>x</th>\n</tr>\n</thead>\n</table>\n</li>\n</ul>\n<p>x|x</p>\n", render("* x|x\n  ---|---\nx|x\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case16) {
  EXPECT_EQ("<p>] http://x.x <em>x</em></p>\n<table>\n<thead>\n<tr>\n<th>x</th>\n<th>x</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>x</td>\n<td></td>\n</tr>\n</tbody>\n</table>\n", render("] http://x.x *x*\n\n|x|x|\n|---|---|\n|x|\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case17) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>A</th>\n<th>B</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td><a href=\"url\">x</a></td>\n<td></td>\n</tr>\n</tbody>\n</table>\n", render("A | B\n--- | ---\n[x](url)\n", MD_FLAG_TABLES));
}
TEST(Md4c_tables, Case18) {
  EXPECT_EQ("<table>\n<thead>\n<tr>\n<th>abc</th>\n<th>def</th>\n</tr>\n</thead>\n</table>\n", render("| abc | def |\n| --- | --- |\n", MD_FLAG_TABLES));
}
