// AI 补充：公开 Utils API 的字符边界、非法 UTF-8 的实际处理和输出状态。
#include <gtest/gtest.h>
#include "emitterutils.h"
#include <string>
#include <vector>
using namespace YAML;
namespace {
std::string output(const ostream_wrapper& out) { return std::string(out.str(),out.pos()); }
std::string utf8(unsigned cp) {
  if(cp<0x80) return std::string(1,static_cast<char>(cp));
  if(cp<0x800) return std::string{static_cast<char>(0xc0|(cp>>6)),static_cast<char>(0x80|(cp&63))};
  if(cp<0x10000) return std::string{static_cast<char>(0xe0|(cp>>12)),static_cast<char>(0x80|((cp>>6)&63)),static_cast<char>(0x80|(cp&63))};
  return std::string{static_cast<char>(0xf0|(cp>>18)),static_cast<char>(0x80|((cp>>12)&63)),static_cast<char>(0x80|((cp>>6)&63)),static_cast<char>(0x80|(cp&63))};
}
TEST(EmitterBoundaries, AnchorUnicode) {
  for(unsigned cp : {0x85u,0xa0u,0x7ffu,0xd7ffu,0xe000u,0xfdcfu,0xfdf0u,0xfffdu,0x10000u,0x40000u,0x10fffdu}) {
    SCOPED_TRACE(cp); ostream_wrapper out;
    EXPECT_TRUE(Utils::WriteAnchor(out,utf8(cp)));
    EXPECT_EQ("&"+utf8(cp),output(out));
  }
  for(char c : {' ', '~', '\x7f'}) { ostream_wrapper out; EXPECT_FALSE(Utils::WriteAnchor(out,std::string(1,c))); }
}
TEST(EmitterBoundaries, DecoderInvalidAndLimits) {
  const std::vector<std::string> invalid={std::string("\x80",1),std::string("\xc2",1),utf8(0x110000),utf8(0xd800),utf8(0xdfff),utf8(0xfffe),utf8(0xffff),utf8(0xfdd0),utf8(0xfdef)};
  for(const auto& s:invalid) {
    ostream_wrapper out; EXPECT_TRUE(Utils::WriteSingleQuotedString(out,s));
    EXPECT_EQ("'"+utf8(0xfffd)+"'",output(out));
  }
  for(unsigned cp : {0u,0x7fu,0x7ffu,0x40000u,0x10fffdu}) {
    ostream_wrapper out; EXPECT_TRUE(Utils::WriteSingleQuotedString(out,utf8(cp)));
    EXPECT_EQ("'"+utf8(cp)+"'",output(out));
  }
  ostream_wrapper trailing; EXPECT_TRUE(Utils::WriteSingleQuotedString(trailing,std::string("\xc2" "A",2)));
  EXPECT_EQ("'"+utf8(0xfffd)+"A'",output(trailing));
}
TEST(EmitterBoundaries, StringFormatFlags) {
  EXPECT_EQ(StringFormat::Plain,Utils::ComputeStringFormat("?x",Auto,FlowType::Block,false));
  EXPECT_EQ(StringFormat::DoubleQuoted,Utils::ComputeStringFormat("?x",Auto,FlowType::Flow,false));
  for(auto mode : {Auto,SingleQuoted,Literal}) {
    EXPECT_EQ(StringFormat::DoubleQuoted,Utils::ComputeStringFormat(std::string("\x80",1),mode,FlowType::Block,true));
    EXPECT_NE(StringFormat::DoubleQuoted,Utils::ComputeStringFormat("ABC",mode,FlowType::Block,true));
  }
  EXPECT_EQ(StringFormat::DoubleQuoted,Utils::ComputeStringFormat("abc ",Auto,FlowType::Block,false));
}
TEST(EmitterBoundaries, QuotesAtUnicodeBoundaries) {
  struct Case {unsigned cp; const char* expected;};
  for(auto c : {Case{0x80,"\"\\x80\""},Case{0xa0,"\"\\xa0\""},Case{0xff,"\"\\u00ff\""},Case{0x7e,"\"~\""}}) {
    ostream_wrapper out; EXPECT_TRUE(Utils::WriteDoubleQuotedString(out,utf8(c.cp),StringEscaping::NonAscii));
    EXPECT_EQ(c.expected,output(out));
  }
  for(char c : {'a','z','A','Z'}) { ostream_wrapper out; EXPECT_TRUE(Utils::WriteChar(out,c,StringEscaping::None)); EXPECT_EQ(std::string(1,c),output(out)); }
  ostream_wrapper tilde; EXPECT_TRUE(Utils::WriteChar(tilde,'~',StringEscaping::None)); EXPECT_EQ("\"~\"",output(tilde));
  for(unsigned cp : {0x80u,0xa0u}) {
    ostream_wrapper raw,json;
    EXPECT_TRUE(Utils::WriteDoubleQuotedString(raw,utf8(cp),StringEscaping::None));
    EXPECT_TRUE(Utils::WriteDoubleQuotedString(json,utf8(cp),StringEscaping::JSON));
    EXPECT_EQ(cp==0x80u ? "\"\\x80\"" : "\"\\xa0\"",output(raw));
    EXPECT_EQ(cp==0x80u ? "\"\\u0080\"" : "\"\\u00a0\"",output(json));
  }
}
TEST(EmitterBoundaries, CommentAfterNewline) {
  ostream_wrapper out; EXPECT_TRUE(Utils::WriteComment(out,"line\nnext",1));
  EXPECT_TRUE(out.comment()); EXPECT_EQ("# line\n# next",output(out));
}
} // namespace
