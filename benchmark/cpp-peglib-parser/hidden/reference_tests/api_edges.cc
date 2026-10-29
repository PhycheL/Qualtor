#include <gtest/gtest.h>
#include "peglib.h"
TEST(PegApi, SearchPosition) {
  peg::parser parser("S <- 'abc'"); ASSERT_TRUE(static_cast<bool>(parser));
  size_t pos=99,len=99; ASSERT_TRUE(parser.search("xxabc",pos,len));
  EXPECT_EQ(2u,pos); EXPECT_EQ(3u,len);
}
TEST(PegApi, RuleNames) {
  peg::parser parser("S <- A A <- 'abc'"); ASSERT_TRUE(static_cast<bool>(parser));
  auto names=parser.get_rule_names();
  EXPECT_NE(names.end(),std::find(names.begin(),names.end(),"S"));
  EXPECT_NE(names.end(),std::find(names.begin(),names.end(),"A"));
}
TEST(PegApi, TraceAndErrorLocation) {
  peg::parser parser("S <- 'abc'"); ASSERT_TRUE(static_cast<bool>(parser));
  size_t calls=0,line=0;
  parser.enable_trace([&](const char*,const char*,size_t,const peg::SemanticValues&,const peg::Context&,const peg::any&){++calls;});
  EXPECT_TRUE(parser.parse("abc")); EXPECT_GT(calls,0u);
  parser.log=[&](size_t l,size_t,const std::string&){line=l;};
  EXPECT_FALSE(parser.parse("xbc")); EXPECT_EQ(1u,line);
}
TEST(PegApi, GrammarErrorLocation) {
  peg::parser parser;
  size_t line=0;
  parser.log=[&](size_t l,size_t,const std::string&){line=l;};
  EXPECT_FALSE(parser.load_grammar("S <- ["));
  EXPECT_EQ(1u,line);
}
