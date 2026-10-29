#include <gtest/gtest.h>
#include "utf8.h"
#include <string>
#include <vector>
TEST(Utf8Errors, CheckedInvalidInputs) {
  std::string out;
  EXPECT_THROW(utf8::append(0x110000,std::back_inserter(out)),utf8::invalid_code_point);
  EXPECT_THROW(utf8::append(0xd800,std::back_inserter(out)),utf8::invalid_code_point);
  std::u16string wide;
  EXPECT_THROW(utf8::append16(0x110000,std::back_inserter(wide)),utf8::invalid_code_point);
  for (const std::string s : {std::string("\xff",1),std::string("\xc0\xaf",2),std::string("\xed\xa0\x80",3)}) {
    auto it=s.begin(); EXPECT_ANY_THROW(utf8::next(it,s.end()));
    EXPECT_FALSE(utf8::is_valid(s.begin(),s.end()));
  }
  std::string truncated("\xe2\x82",2); auto it=truncated.begin();
  EXPECT_THROW(utf8::next(it,truncated.end()),utf8::not_enough_room);
  EXPECT_EQ(std::string("\xef\xbf\xbd",3),utf8::replace_invalid(std::string("\xff",1)));
  std::u16string bad(1,0xd800); auto p=bad.begin();
  EXPECT_THROW(utf8::next16(p,bad.end()),utf8::not_enough_room);
  EXPECT_THROW(utf8::utf16to8(bad.begin(),bad.end(),std::back_inserter(out)),utf8::invalid_utf16);
  bad.push_back('A'); EXPECT_THROW(utf8::utf16to8(bad.begin(),bad.end(),std::back_inserter(out)),utf8::invalid_utf16);
  bad.assign(1,0xdc00); EXPECT_THROW(utf8::utf16to8(bad.begin(),bad.end(),std::back_inserter(out)),utf8::invalid_utf16);
}
TEST(Utf8Errors, ExceptionPayloads) {
  utf8::invalid_code_point cp(0x110000); EXPECT_EQ(0x110000u,cp.code_point()); EXPECT_STREQ("Invalid code point",cp.what());
  utf8::invalid_utf8 octet(static_cast<unsigned char>(0xff)); EXPECT_EQ(0xffu,octet.utf8_octet()); EXPECT_STREQ("Invalid UTF-8",octet.what());
  utf8::invalid_utf16 word(0xd800); EXPECT_EQ(0xd800u,word.utf16_word()); EXPECT_STREQ("Invalid UTF-16",word.what());
  utf8::not_enough_room room; EXPECT_STREQ("Not enough space",room.what());
}
