#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "md4c-html.h"
namespace {
void append(const char* s, MD_SIZE n, void* p) { static_cast<std::string*>(p)->append(s,n); }
std::string html(const std::string& text, unsigned options=0) {
  std::string out;
  EXPECT_EQ(0, md_html(text.data(), text.size(), append, &out, 0, options));
  return out;
}
void chunks(const char* s, MD_SIZE n, void* p) { static_cast<std::vector<std::string>*>(p)->push_back(std::string(s,n)); }
}
TEST(Md4cBoundary, UnicodeAndHexLimits) {
  EXPECT_EQ(std::string("<p>\x7f \xdf\xbf \xef\xbf\xbf \xf0\x90\x80\x80 \xf0\xa3\x91\x96 \xf4\x8f\xbf\xbf \xef\xbf\xbd</p>\n"),
            html("&#127; &#2047; &#65535; &#65536; &#144470; &#1114111; &#1114112;"));
  EXPECT_EQ(std::string("<p>I \xc2\xaa</p>\n"), html("&#x49; &#xAA;"));
}
TEST(Md4cBoundary, NullCharactersInTextAndAttributes) {
  EXPECT_EQ("<p>a\xef\xbf\xbd" "b</p>\n", html(std::string("a\0b",3)));
  EXPECT_EQ("<p>[x](a\xef\xbf\xbd" "b)</p>\n", html(std::string("[x](a\0b)",8)));
}
TEST(Md4cBoundary, RendererOptions) {
  const std::string bom("\xef\xbb\xbf",3);
  EXPECT_EQ("", html(bom,MD_HTML_FLAG_SKIP_UTF8_BOM));
  EXPECT_EQ("<p>x</p>\n", html(bom+"x",MD_HTML_FLAG_SKIP_UTF8_BOM));
  EXPECT_EQ("<p>abc</p>\n", html("abc",MD_HTML_FLAG_SKIP_UTF8_BOM));
  EXPECT_EQ("<p>"+bom+"x</p>\n", html(bom+"x"));
  EXPECT_EQ("<p>&amp; &#65;</p>\n", html("&amp; &#65;",MD_HTML_FLAG_VERBATIM_ENTITIES));
  EXPECT_EQ("<hr />\n",html("---\n",MD_HTML_FLAG_XHTML));
}
TEST(Md4cBoundary, CallbackDoesNotEmitEmptyEscapedChunks) {
  for (const std::string input : {std::string("<&"),std::string("[x](<&>)")}) {
    std::vector<std::string> out;
    ASSERT_EQ(0,md_html(input.data(),input.size(),chunks,&out,0,0));
    ASSERT_FALSE(out.empty());
    for (const auto& part : out) EXPECT_FALSE(part.empty()) << input;
  }
}

TEST(Md4cBoundary, NullCharacterInTitle) {
  EXPECT_EQ("<p><a href=\"a\" title=\"b\xef\xbf\xbd" "c\">x</a></p>\n",html(std::string("[x](a \"b\0c\")",12)));
}
