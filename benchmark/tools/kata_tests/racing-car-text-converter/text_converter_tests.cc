// 参考强测试集：Racing-Car TextConverter（文本转 HTML、按 PAGE_BREAK 分页）。隐藏材料，不提供给被评测的生成 Agent。
// 测试在当前工作目录写入各自独立的输入文件；断言以现有代码的实际运行结果为准（D001），包括单引号转成 &quot;。
#include "HtmlPagesConverter.h"
#include "HtmlTextConverter.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <string>

namespace {

std::string WriteFile(const std::string& name, const std::string& content) {
    std::ofstream out(name.c_str(), std::ios::binary);
    out << content;
    return name;
}

TEST(HtmlTextConverterTest, KeepsFilename) {
    EXPECT_EQ("some/path/input.txt", HtmlTextConverter("some/path/input.txt").getFilename());
}

TEST(HtmlTextConverterTest, EscapesEachLineAndAddsLineBreaks) {
    std::string file = WriteFile("qualtor_text_escape.txt", "a<b>c\n'quoted' & \"double\"\nplain");
    EXPECT_EQ("a&lt;b&gt;c<br />&quot;quoted&quot; &amp; &quot;double&quot;<br />plain<br />",
              HtmlTextConverter(file).convertToHtml());
}

TEST(HtmlTextConverterTest, EmptyAndMissingFilesGiveEmptyHtml) {
    EXPECT_EQ("", HtmlTextConverter(WriteFile("qualtor_text_empty.txt", "")).convertToHtml());
    std::remove("qualtor_text_missing.txt");
    EXPECT_EQ("", HtmlTextConverter("qualtor_text_missing.txt").convertToHtml());
}

TEST(HtmlTextConverterTest, BlankLinesStillProduceLineBreaks) {
    std::string file = WriteFile("qualtor_text_blank.txt", "first\n\nthird\n");
    EXPECT_EQ("first<br /><br />third<br />", HtmlTextConverter(file).convertToHtml());
}

TEST(HtmlPagesConverterTest, KeepsFilename) {
    std::string file = WriteFile("qualtor_pages_name.txt", "x\n");
    EXPECT_EQ(file, HtmlPagesConverter(file).getFilename());
}

TEST(HtmlPagesConverterTest, SinglePageWithoutBreak) {
    std::string file = WriteFile("qualtor_pages_single.txt", "one & two\nthree\n");
    EXPECT_EQ("one &amp; two<br />three<br />", HtmlPagesConverter(file).getHtmlPage(0));
}

TEST(HtmlPagesConverterTest, SplitsPagesAtPageBreakLines) {
    std::string file = WriteFile("qualtor_pages_split.txt",
                                 "page one\nstill one\nPAGE_BREAK\n<page two>\nPAGE_BREAK\nthree\n");
    HtmlPagesConverter converter(file);
    EXPECT_EQ("page one<br />still one<br />", converter.getHtmlPage(0));
    EXPECT_EQ("&lt;page two&gt;<br />", converter.getHtmlPage(1));
    EXPECT_EQ("three<br />", converter.getHtmlPage(2));
}

TEST(HtmlPagesConverterTest, BreakMarkerInsideLineAlsoEndsPage) {
    std::string file = WriteFile("qualtor_pages_inline.txt", "alpha\nxx PAGE_BREAK yy\nbeta");
    HtmlPagesConverter converter(file);
    EXPECT_EQ("alpha<br />", converter.getHtmlPage(0));
    EXPECT_EQ("beta<br />", converter.getHtmlPage(1));
}

TEST(HtmlPagesConverterTest, ConsecutiveBreaksGiveEmptyPage) {
    std::string file = WriteFile("qualtor_pages_empty.txt", "a\nPAGE_BREAK\nPAGE_BREAK\nb\n");
    HtmlPagesConverter converter(file);
    EXPECT_EQ("a<br />", converter.getHtmlPage(0));
    EXPECT_EQ("", converter.getHtmlPage(1));
    EXPECT_EQ("b<br />", converter.getHtmlPage(2));
}

}  // namespace
