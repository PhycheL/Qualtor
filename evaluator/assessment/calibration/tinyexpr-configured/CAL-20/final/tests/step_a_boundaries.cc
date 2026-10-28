#include <gtest/gtest.h>
#include <cmath>
#include <cstdio>
#include <string>
#include "tinyexpr.h"
namespace {
double value(const char* input) { int e=99; double v=te_interp(input,&e); EXPECT_EQ(0,e) << input; return v; }
std::string pointer(const void* p) { char text[64]; std::snprintf(text,sizeof(text),"%p",p); return text; }
}
TEST(TinyExprBoundary, IntegerLimitsAndOverflow) {
  EXPECT_EQ(1,value("ncr(4294967295,0)"));
  EXPECT_EQ(1,value("ncr(4294967295,4294967295)"));
  EXPECT_EQ(100,value("ncr(100,99)"));
  EXPECT_EQ(100,value("ncr(100,1)"));
  EXPECT_TRUE(std::isinf(value("ncr(68,34)")));
  EXPECT_TRUE(std::isinf(value("fac(21)")));
}
TEST(TinyExprBoundary, DecimalRoundingAtExactPowerLimit) {
  // C/C++ correctly rounded literal, compared exactly rather than upstream's 0.001 tolerance.
  EXPECT_EQ(7e-22,value("7e-22"));
  EXPECT_EQ(3e-22,value("3e-22"));
}
TEST(TinyExprBoundary, TrailingFunctionSeparator) {
  int error=0;
  te_expr* t=te_compile("pow(1,2,)",nullptr,0,&error);
  EXPECT_EQ(nullptr,t);
  EXPECT_EQ(8,error);
  te_free(t);
}
TEST(TinyExprBoundary, DepthAndLongFlatInput) {
  for (int depth : {469,470,511}) {
    const std::string expr=std::string(depth,'(')+"1"+std::string(depth,')');
    EXPECT_EQ(1,value(expr.c_str())) << depth;
  }
  int error=0;
  const std::string too_deep=std::string(512,'(')+"1"+std::string(512,')');
  te_expr* t=te_compile(too_deep.c_str(),nullptr,0,&error);
  EXPECT_EQ(nullptr,t); EXPECT_EQ(-1,error); te_free(t);
  std::string flat="1"; for(int i=0;i<300;++i) flat+="+1";
  EXPECT_EQ(301,value(flat.c_str()));
}
TEST(TinyExprBoundary, PublicTreePrinter) {
  double x=3;
  te_variable vars[]={{"x",&x,TE_VARIABLE,nullptr}};
  int error=0;
  te_expr* tree=te_compile("x+2",vars,1,&error);
  ASSERT_NE(nullptr,tree); ASSERT_EQ(0,error);
  const std::string expected="f2 "+pointer(tree->parameters[0])+" "+pointer(tree->parameters[1])+"\n bound "+pointer(&x)+"\n 2.000000\n";
  testing::internal::CaptureStdout(); te_print(tree);
  EXPECT_EQ(expected,testing::internal::GetCapturedStdout());
  te_free(tree);
}
TEST(TinyExprBoundary, RejectedTokensAfterKnownFunction) {
  for (const char* text : {".","1+=(2,3)","1+&(2,3)","1+|(2,3)"}) {
    int error=0;
    te_expr* t=te_compile(text,nullptr,0,&error);
    EXPECT_EQ(nullptr,t) << text;
    if (std::string(text)==".") EXPECT_EQ(1,error);
    te_free(t);
  }
  double unused=0;
  const te_variable invalid[]={{"bad",&unused,24,nullptr}};
  int error=0;
  te_expr* t=te_compile("1+bad(2,3)",invalid,1,&error);
  EXPECT_EQ(nullptr,t); EXPECT_GT(error,0); te_free(t);
  EXPECT_EQ(5e-22,value("5e-22"));
}
TEST(TinyExprBoundary, LongFractionOffsetsExponentSaturation) {
  // Fixed Clang/Mull IR counterexample: 100,000,000 fractional places cancel
  // the parser's exponent saturation; both original and mutant stay within 2 GiB.
  std::string input="0.";
  input.append(99999999,'0');
  input += "1e1000000000";
  EXPECT_EQ(1,value(input.c_str()));
}
