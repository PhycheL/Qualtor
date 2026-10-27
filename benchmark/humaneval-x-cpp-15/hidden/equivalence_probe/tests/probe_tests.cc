// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_15.h"

#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {

template <class T>
void ExpectNearScalar(T actual, T expected, double tolerance) {
    EXPECT_NEAR(actual, expected, tolerance * (1 + std::fabs(static_cast<double>(expected))));
}

template <class T>
void ExpectNearVec(const std::vector<T>& actual, const std::vector<T>& expected, double tolerance) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) ExpectNearScalar(actual[i], expected[i], tolerance);
}

}  // namespace

TEST(Probe, odd_count_01) {
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 3n the str3ng 3 of the 3nput.")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("2Z"), std::string("3"), std::string("the number of oBdd elements 2n the str2ng 2 of the UnGut."), std::string("0sgDOkx"), std::string("the number of odd elements 3n the str3ng 3 of the 3nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("111111"), std::string("the number of odd elemnts 4n the str4ng 4 og the 4nput.")})), (std::vector<std::string >{std::string("the number of odd elements 6n the str6ng 6 of the 6nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("11111111"), std::string("GYaan8gJ"), std::string("1234567"), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("31p4"), std::string("fgVqcb5Dovjs"), std::string("Gdlt"), std::string("the3 number of odd elements 2yn the str2ng 2 of the 2nput.")})), (std::vector<std::string >{std::string("the number of odd elements 8n the str8ng 8 of the 8nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("3"), std::string("11111111")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("1234567"), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("1"), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("E")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("137"), std::string("314"), std::string("t")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1npuat."), std::string("314"), std::string("the number o odd elements 2n the str8ng 8 oGf the 8nput."), std::string("314"), std::string("3")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("wfKnNf"), std::string("the number of odd elemeot31n the str1ng 1 of the 1nput."), std::string("31"), std::string("11111111")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 5n the str5ng 5 of the 5nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("314"), std::string("the number of oddY elements 2n the str2ng 2 of the 2nput."), std::string("DkB06W9iV6"), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("Cls1s Nwlye"), std::string("qV"), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("mwLvtFTJ0"), std::string("the number of odd elements 1n the str1ng v of t he 1nput."), std::string("the number of od elements 8n the str8g 8 of the 8nput."), std::string("the number of odd elements3n the strrng 3 of the 3nput.")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("1111111"), std::string("uLdQbimmgHF"), std::string("SKE6V2q"), std::string("thue number of odd elements 8n the str8ng 8 of the8nput."), std::string("43")})), (std::vector<std::string >{std::string("the number of odd elements 7n the str7ng 7 of the 7nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput."), std::string("137")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("20")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("314")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("3")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("he number of odd elements Bn th str3ng 3 of the 3nput."), std::string("1n37"), std::string("89O3prgM2N a"), std::string("71"), std::string("mdfTk"), std::string("Gtno"), std::string("nibPwP"), std::string("eQ9sdQI  yk")})), (std::vector<std::string >{std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("tXe number of odd elements 8n the str8nga8 of thge 8nput."), std::string("137"), std::string("314")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 3n the sr3ng3 of the 3nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n thBe str1ng 1 of the 1n.ut."), std::string("lp6g"), std::string("rwMw"), std::string("be.Op")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("th.e number of odd elements 4n the str4ng 4 of t1e 4nput."), std::string("the number of odd eleme4nts 8n the str8ng 8 of the 8npRt."), std::string("11111111"), std::string("314"), std::string("kh rMbDtA"), std::string("the number of odzd elements 8n xhe str8ng 8 of he 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
}

TEST(Probe, odd_count_02) {
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("314"), std::string("the number of odd elements 2n the st2ng 2 of 3he 2npSt."), std::string("3"), std::string("314")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("tYmv5")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("11111111")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("137"), std::string("11s11111"), std::string("11111111")})), (std::vector<std::string >{std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 7n the str7ng 7 of the 7nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("137"), std::string("9fAbNSN"), std::string("the number of odd elements 3n tP e str3ng 3 of the 3nput."), std::string("3")})), (std::vector<std::string >{std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("oFr3")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("t14")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("137"), std::string("314"), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number ofZodd eNlements 4n the str4ng 4 of the 4npuv.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("tXrfyI8"), std::string("ejDUR"), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("DSM9"), std::string("0V0Q3"), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("zhNanXz"), std::string("the number of odd elements 1n the str1ng 1 of tfhe 1npt."), std::string("11S111111"), std::string("P234m67"), std::string("31"), std::string("Vq"), std::string("the number of odd elements 3n the strOng 3 of the 3nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("odu2ItAPv"), std::string("M1234567"), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 8n the str8ng 8 ofN the 8nput."), std::string(""), std::string("271"), std::string("dX"), std::string("tle number of odd elemnts 3n the str3ng 3 of the 3nput."), std::string("7."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string(""), std::string("wwiyRr44H"), std::string("")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("137"), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("137"), std::string("the number of odd elements 3n the str3ng 3 of the 3nput.")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("3"), std::string("11111111"), std::string("NhVxiBI")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 5n the str2g 2 of the 2nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("8SuEd"), std::string("11111111")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("KTp"), std::string("1111111"), std::string("X"), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("kMhAV8OgCMdc"), std::string("c3"), std::string("LCiKw3")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 7n the str7ng 7 of the 7nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("111117L1"), std::string("osBxG"), std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string(""), std::string("OjZW200rF1X"), std::string("271")})), (std::vector<std::string >{std::string("the number of odd elements 7n the str7ng 7 of the 7nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("Bo75")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
}

TEST(Probe, minSubArraySum_01) {
    EXPECT_EQ((minSubArraySum(std::vector<long long >{10LL, 11LL, 13LL, 3LL, 4LL})), (3LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL, 2LL, -10LL})), (-11LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{190LL, 533LL, -5LL, 15LL, 25LL, 17LL, 34LL})), (-5LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-32LL, 1LL, 3LL})), (-32LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{20LL})), (20LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{7LL})), (7LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-6LL, -5LL, 29LL, -990LL})), (-990LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{489LL, -1LL})), (-1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{469LL, 4LL, 21LL})), (4LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{846LL, 2LL, -8LL, 274LL, 235LL})), (-8LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-835LL, 543LL, 2LL, 30LL})), (-835LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-573LL})), (-573LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{2LL, 3LL, 1LL, 4LL, 2LL, 4LL})), (1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-9999999999999999LL, -465LL})), (-10000000000000464LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-104LL, -779LL})), (-883LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL, -3LL, 10LL, -5LL})), (-6LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{0LL, -739LL, 29LL, 26LL, 0LL})), (-739LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL, -3LL})), (-6LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{4LL, -9999999999999997LL, -7LL, 3LL, -14LL, -12LL, 26LL})), (-10000000000000027LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{610LL})), (610LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{10LL, -2LL, -3LL, 2LL, -10LL})), (-13LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-9999999999999999LL})), (-9999999999999999LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{2LL, 3LL, 4LL, 1LL, 2LL, 4LL, -3LL})), (-3LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{0LL, 10LL, 20LL, 1000000LL})), (0LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL, -3LL, 2LL, -10LL})), (-14LL));
}

TEST(Probe, minSubArraySum_02) {
    EXPECT_EQ((minSubArraySum(std::vector<long long >{9LL})), (9LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{20LL, 31LL, -9999999999999999LL, 4LL, 2LL})), (-9999999999999999LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL})), (-3LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{82LL, 1000000LL})), (82LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{10LL, -1LL, 13LL, 8LL, 3LL, 4LL})), (-1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{10LL, 11LL, 13LL, 8LL, 3LL, 4LL})), (3LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{10LL, 11LL, 13LL, 8LL, 3LL, 4LL, 0LL})), (0LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, 1LL})), (-1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{0LL, 11LL})), (0LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{10LL, 11LL, 13LL, -1LL, 3LL, 4LL})), (-1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{100LL, -33LL, 32LL, -1LL, 0LL, -2LL})), (-33LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{22LL})), (22LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL, -3LL, 2LL, -10LL, 27LL})), (-14LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-571LL, 0LL, 6LL, 1000000LL, 11LL, -1LL})), (-571LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{495LL, 189LL, 30LL})), (30LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, -2LL, -3LL, 2LL, -10LL, 17LL})), (-14LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{22LL, -3LL, -5LL})), (-8LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{100LL, -33LL, 32LL, -1LL, 0LL, -2LL, 644LL})), (-33LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{27LL, -1LL, 0LL, -617LL, -2LL, 0LL, -6LL})), (-626LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{999998LL, 0LL, 10LL, 32LL, 14LL, 19LL})), (0LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{19LL, 11LL, -5LL, 5LL, 11LL})), (-5LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{3LL, 157LL, 28LL})), (3LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{1LL})), (1LL));
}

TEST(Probe, max_fill_01) {
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{-7, 375, 7, 366}, std::vector<int >{3, 1, 10, 3}, std::vector<int >{534, 3, 24, -498}}, 14)), (60));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{4, 2, 10, 5}, std::vector<int >{24, 18}}, 2)), (32));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 10)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, -5)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 1, 1}}, 13)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0, 0}, std::vector<int >{1}, std::vector<int >{1, 1}, std::vector<int >{}}, 20)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{4, 0}}, 6)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{10, 1, 4}, std::vector<int >{6, 29, 26}, std::vector<int >{-10, 5, -899}}, -710)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 22)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{4, -564}, std::vector<int >{3, 1}, std::vector<int >{}}, -6)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{8, 6, 352, 5}, std::vector<int >{11}}, 20)), (20));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0, 1, 0}, std::vector<int >{1, 1, 0, 1}}, 3)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 0}, std::vector<int >{0, 1}, std::vector<int >{0, 1}, std::vector<int >{1, 0}}, 11)), (4));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{10, 8, 0}, std::vector<int >{16, 7, 18}}, 18)), (4));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{}}, 6)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{-990, 2, 5, -2}, std::vector<int >{}, std::vector<int >{6, 4, 985, 204}, std::vector<int >{352, 7, 1, 15}}, -674)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{26, 9}, std::vector<int >{3, -260}, std::vector<int >{23, 8}, std::vector<int >{11, -955}}, -895)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 1, 0}, std::vector<int >{0}, std::vector<int >{0, 0, 0, 0}, std::vector<int >{1, 0, 1}}, 12)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{11}, std::vector<int >{292}, std::vector<int >{5}, std::vector<int >{-3}}, 15)), (22));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{4}, std::vector<int >{6}}, -6)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{}}, 14)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{}, std::vector<int >{1, 1, 1, 0}}, 25)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0, 0, 0}, std::vector<int >{1, 1, 0, 1}, std::vector<int >{}, std::vector<int >{0, 1, 1, 0}}, 5)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 120)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{-10, 7}}, 5)), (0));
}

TEST(Probe, max_fill_02) {
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{20, 0, 3}, std::vector<int >{30, -932, 3}}, 17)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{-6, 7, 509, 29}, std::vector<int >{1, -3, 11, 454}, std::vector<int >{18, 6, 10, 7}, std::vector<int >{2, 3, 10, 2}}, 11)), (98));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 1, 1}, std::vector<int >{0}, std::vector<int >{0, 0, 0}, std::vector<int >{0, 1, 1}}, 2)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{5, -790, 0}, std::vector<int >{28, 0, 1}, std::vector<int >{22, 5, 24}, std::vector<int >{275, -621, 699}}, 16)), (29));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 0, 1}, std::vector<int >{0, 0, 1}, std::vector<int >{1, 1, 0, 1}}, 6)), (3));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 1, 0}, std::vector<int >{0}, std::vector<int >{1, 1, 0, 0}}, 21)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{-8, 5, 6, 99999}, std::vector<int >{3, 0, 12, -10}, std::vector<int >{8, 2, 13, 2}, std::vector<int >{-9, 27, 5, 100}}, 8)), (12522));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{10}, std::vector<int >{6}}, 4)), (5));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 1, 1, 0}, std::vector<int >{0, 0, 0}, std::vector<int >{1, 1, 1, 0}}, 14)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0}, std::vector<int >{0, 0}}, 5)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 1}}, -977)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 1}}, -10)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0}}, 11)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{9, -4}, std::vector<int >{8, 6}}, 2)), (10));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 1, 0, 0}}, 23)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0}, std::vector<int >{0}, std::vector<int >{0}, std::vector<int >{1}}, -145)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1, 14}, std::vector<int >{0, -495}, std::vector<int >{2, 11}, std::vector<int >{19, 21}}, 7)), (11));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 100)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{19, 3, 4}}, 3)), (9));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{}, std::vector<int >{}, std::vector<int >{29, -505, -9}}, 0)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{9, -9, 618}, std::vector<int >{20}}, 8)), (81));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0}, std::vector<int >{0, 0, 1, 1}, std::vector<int >{0}}, -1)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0, 0, 0}, std::vector<int >{}, std::vector<int >{0}}, 7)), (0));
}

TEST(Probe, sort_array_01) {
    EXPECT_EQ((sort_array(std::vector<int >{0, 1, 2, 3, 4})), (std::vector<int >{0, 1, 2, 4, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 5, 1, 3, 4})), (std::vector<int >{1, 2, 4, 3, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 2, 3, 4, 5})), (std::vector<int >{1, 2, 4, 3, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{-370, 760, 1, 173})), (std::vector<int >{1, -370, 173, 760}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 2, 4, 3, 5})), (std::vector<int >{1, 2, 4, 3, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 1, 2, 4, 3})), (std::vector<int >{0, 1, 2, 4, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{32, 3, 5, 6, 12, 44})), (std::vector<int >{32, 3, 5, 6, 12, 44}));
    EXPECT_EQ((sort_array(std::vector<int >{7, -4, -4, -591, 12})), (std::vector<int >{-4, -4, 12, 7, -591}));
    EXPECT_EQ((sort_array(std::vector<int >{3, 0, 2, 1, 4})), (std::vector<int >{0, 1, 2, 4, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{12, -4})), (std::vector<int >{-4, 12}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 0, 2, 3})), (std::vector<int >{0, 1, 2, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{-6, -5, -2, -3, -4})), (std::vector<int >{-4, -2, -6, -5, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{-919, 32})), (std::vector<int >{32, -919}));
    EXPECT_EQ((sort_array(std::vector<int >{13, 6, -9, 13, 146, 14, 1, 100})), (std::vector<int >{1, -9, 6, 13, 13, 14, 100, 146}));
    EXPECT_EQ((sort_array(std::vector<int >{-1})), (std::vector<int >{-1}));
    EXPECT_EQ((sort_array(std::vector<int >{0, -1, 4, 346, 370, -9})), (std::vector<int >{0, -1, 4, -9, 346, 370}));
    EXPECT_EQ((sort_array(std::vector<int >{-2, 1, 235})), (std::vector<int >{-2, 1, 235}));
    EXPECT_EQ((sort_array(std::vector<int >{-4, -2, -6, -5, -3})), (std::vector<int >{-4, -2, -6, -5, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 7, 77, 10})), (std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 10, 7, 77}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 5, 2, 3, 4, 22})), (std::vector<int >{1, 2, 4, 3, 5, 22}));
    EXPECT_EQ((sort_array(std::vector<int >{-670, -3, 3, 6})), (std::vector<int >{-3, 3, 6, -670}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 5, 77, 4, 5, 3, 5, 10, 2, 3, 4})), (std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 10, 77}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 5, 77, 4, 5, 3, 5, 7, 2, 3, 4, -1})), (std::vector<int >{-1, 2, 2, 4, 4, 3, 3, 5, 5, 5, 7, 77}));
    EXPECT_EQ((sort_array(std::vector<int >{3, 6, 44, 12, 32, 5})), (std::vector<int >{32, 3, 5, 6, 12, 44}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 4, 8, 16, 32, 751})), (std::vector<int >{2, 4, 8, 16, 32, 751}));
}

TEST(Probe, sort_array_02) {
    EXPECT_EQ((sort_array(std::vector<int >{-5, -179, -6, 802})), (std::vector<int >{-6, -5, 802, -179}));
    EXPECT_EQ((sort_array(std::vector<int >{23, -77, 0, 43, -2, 456, 25, 44})), (std::vector<int >{0, -2, 25, 44, -77, 23, 43, 456}));
    EXPECT_EQ((sort_array(std::vector<int >{-4})), (std::vector<int >{-4}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 4, 8, 16, 32})), (std::vector<int >{2, 4, 8, 16, 32}));
    EXPECT_EQ((sort_array(std::vector<int >{-2, -3, -4, -5, -6, -5})), (std::vector<int >{-4, -2, -6, -5, -5, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{5, 1, 99999, -1, -3, -5, 1000, 4})), (std::vector<int >{-1, 1, 4, -5, -3, 5, 1000, 99999}));
    EXPECT_EQ((sort_array(std::vector<int >{5, 2, 3, 4})), (std::vector<int >{2, 4, 3, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{5, 1, 2, 3, 4})), (std::vector<int >{1, 2, 4, 3, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{-3, -5, -4, -4, -1})), (std::vector<int >{-4, -4, -1, -5, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{44, 895, 6, -8, -5, 0})), (std::vector<int >{0, -8, -5, 6, 44, 895}));
    EXPECT_EQ((sort_array(std::vector<int >{-6, -6, 96, 99999, 812, -857})), (std::vector<int >{-6, -6, 96, 812, -857, 99999}));
    EXPECT_EQ((sort_array(std::vector<int >{-5, 4, 190})), (std::vector<int >{4, -5, 190}));
    EXPECT_EQ((sort_array(std::vector<int >{-9, 0, 2})), (std::vector<int >{0, 2, -9}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 443, -6, -9, -1, 3})), (std::vector<int >{-1, 2, -9, -6, 3, 443}));
    EXPECT_EQ((sort_array(std::vector<int >{34, -846})), (std::vector<int >{34, -846}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 5, 2, -427, 4})), (std::vector<int >{1, 2, 4, 5, -427}));
    EXPECT_EQ((sort_array(std::vector<int >{-1, 1})), (std::vector<int >{-1, 1}));
    EXPECT_EQ((sort_array(std::vector<int >{32, 3, 5, 6, 12, 44, 3})), (std::vector<int >{32, 3, 3, 5, 6, 12, 44}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 14, -1, -5, -7, 7})), (std::vector<int >{0, -1, -5, -7, 7, 14}));
    EXPECT_EQ((sort_array(std::vector<int >{-320})), (std::vector<int >{-320}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 0, 2, 3, 4, 455})), (std::vector<int >{0, 1, 2, 4, 3, 455}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 0, 2, 3, 3})), (std::vector<int >{0, 1, 2, 3, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{-835, 24, 5, -628, 1, 8})), (std::vector<int >{1, 8, 5, 24, -835, -628}));
}

TEST(Probe, select_words_01) {
    EXPECT_EQ((select_words(std::string(""), 12)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("D1W15tic"), 3)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("x2by"), 9)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Ppa1"), 27)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("c"), 6)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("ftDFppRvUTHf"), 3)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("2s14"), 27)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("f"), 9)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("ac"), -1)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("OVHGTSAJyF"), 2)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("EygnJpvwou"), 0)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Hello worNd"), 4)), (std::vector<std::string >{std::string("worNd")}));
    EXPECT_EQ((select_words(std::string("UL21O5"), 880)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Mary ha9d a littlRe lamb"), 4)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("n7cle"), 7)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("a b  d e f"), 2)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string(""), 2)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("wjP4z2ie"), 19)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Mary had a little lamb"), 6)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Hello world"), 0)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("lamb"), 0)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("N"), 1)), (std::vector<std::string >{std::string("N")}));
    EXPECT_EQ((select_words(std::string("Ucle"), 100)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("jN8s9u"), 3)), (std::vector<std::string >{std::string("jN8s9u")}));
    EXPECT_EQ((select_words(std::string("a  c de f"), 2)), (std::vector<std::string >{}));
}

TEST(Probe, select_words_02) {
    EXPECT_EQ((select_words(std::string("M"), 287)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("d"), 1)), (std::vector<std::string >{std::string("d")}));
    EXPECT_EQ((select_words(std::string("f"), 100)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Hello wo5ld"), 6)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string(""), 5)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("d0QZJ"), 0)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("4m9DnL"), 741)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("a bVc G e f"), 15)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("rqw7hQb"), 599)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("f"), 259)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("2QtjIoLkXlV"), 15)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("QrmOVk"), -959)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("8q"), 6)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("b"), 20)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("vTyb1W"), -777)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("a b c d ef"), 9)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Hello world"), -3)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Mary had a little lamb"), 0)), (std::vector<std::string >{std::string("a")}));
    EXPECT_EQ((select_words(std::string("Uncle"), 24)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("d 7mKxlPmy"), 15)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("c"), 3)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("7"), 0)), (std::vector<std::string >{std::string("7")}));
    EXPECT_EQ((select_words(std::string("Z"), 3)), (std::vector<std::string >{}));
}

TEST(Probe, get_closest_vowel_01) {
    EXPECT_EQ((get_closest_vowel(std::string("FV65"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("cvMd7 7"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("LG3f"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("Zv2GD6m0f"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string(""))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("FUL"))), (std::string("U")));
    EXPECT_EQ((get_closest_vowel(std::string("TquicAk"))), (std::string("A")));
    EXPECT_EQ((get_closest_vowel(std::string("F L"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("Wesj"))), (std::string("e")));
    EXPECT_EQ((get_closest_vowel(std::string("ZY9ol 9"))), (std::string("o")));
    EXPECT_EQ((get_closest_vowel(std::string("amrd"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("lGNobYNFmRHN"))), (std::string("o")));
    EXPECT_EQ((get_closest_vowel(std::string("tWzli"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("27cr9"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("it7"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("ftQl2l"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("4r5"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("yogurt"))), (std::string("u")));
    EXPECT_EQ((get_closest_vowel(std::string("N4Uwipz14Asm"))), (std::string("A")));
    EXPECT_EQ((get_closest_vowel(std::string("ptmst"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("dn"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("aIs"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("bad"))), (std::string("a")));
    EXPECT_EQ((get_closest_vowel(std::string("1lu0zyXUVJV"))), (std::string("U")));
    EXPECT_EQ((get_closest_vowel(std::string("fsll"))), (std::string("")));
}

TEST(Probe, get_closest_vowel_02) {
    EXPECT_EQ((get_closest_vowel(std::string("XpKIaF"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("3W"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("quic"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("alK"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("8sfw0u1"))), (std::string("u")));
    EXPECT_EQ((get_closest_vowel(std::string("NrkUGr"))), (std::string("U")));
    EXPECT_EQ((get_closest_vowel(std::string("E"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("PAbKoFve"))), (std::string("o")));
    EXPECT_EQ((get_closest_vowel(std::string("full"))), (std::string("u")));
    EXPECT_EQ((get_closest_vowel(std::string("k"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("Above"))), (std::string("o")));
    EXPECT_EQ((get_closest_vowel(std::string("fuJll"))), (std::string("u")));
    EXPECT_EQ((get_closest_vowel(std::string("vP4OVu"))), (std::string("O")));
    EXPECT_EQ((get_closest_vowel(std::string("eAs"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("QR"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("yort"))), (std::string("o")));
    EXPECT_EQ((get_closest_vowel(std::string(" jxlyean"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("yobrur"))), (std::string("u")));
    EXPECT_EQ((get_closest_vowel(std::string(" RPa Y"))), (std::string("a")));
    EXPECT_EQ((get_closest_vowel(std::string("Asia"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("anime"))), (std::string("i")));
    EXPECT_EQ((get_closest_vowel(std::string("easy"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("most"))), (std::string("o")));
}

TEST(Probe, match_parens_01) {
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()d)())"), std::string("())())"), std::string("((m3)("), std::string("No"), std::string(")"), std::string("((())"), std::string(")("), std::string("4jAFoiWF5Aw")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")(()"), std::string("(()(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()"), std::string("())")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("m6iHRHedg3W"), std::string("0"), std::string(")())"), std::string("()))()"), std::string("())"), std::string("(()())(("), std::string("3x5GOLMBg54"), std::string("V")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("2YpNIE1"), std::string(")(()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("("), std::string("7PuF0Sj6Zx"), std::string(""), std::string("WIJDK"), std::string("(2())"), std::string("No")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("Bm53SeY"), std::string("Zq7lp"), std::string(")())"), std::string("(())i)"), std::string("QN(X(("), std::string(""), std::string("N"), std::string("WF17JPN")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(((("), std::string("YHF")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(())))"), std::string("(()())((")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")("), std::string(")(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")(()"), std::string("(()()(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()("), std::string(")")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("ZuVPOgdW4cAy"), std::string("()))()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("((G)1("), std::string("aEz"), std::string("p"), std::string("fqwYqhy)0u"), std::string("())")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")"), std::string(")"), std::string("(())()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")"), std::string("(")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(((("), std::string(")(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")(()"), std::string("g sv(qFabr0")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(())))"), std::string("(()())(("), std::string(")(")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")"), std::string(")")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("((())"), std::string("((((")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("S2"), std::string("Zho4bb5IqC("), std::string(")1S"), std::string(")d))"), std::string("(()(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("7IFyQQwRu"), std::string("i A1p31ia"), std::string("((()"), std::string("(())()"), std::string("xx47ZOB")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(((("), std::string("((())")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("e"), std::string("())")})), (std::string("No")));
}

TEST(Probe, match_parens_02) {
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(())))"), std::string("(()())(("), std::string("()T))")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")l())"), std::string(")T((d"), std::string(""), std::string(")())"), std::string(")"), std::string("())())"), std::string("(()()(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("M)("), std::string("fi)))"), std::string("scLIw24"), std::string("((r())"), std::string("p((V("), std::string("ITUZwP8nHRt")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(KM"), std::string("))"), std::string(")"), std::string(")(()"), std::string("(()())(("), std::string("((M)))"), std::string("())"), std::string("()))()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()("), std::string("()))()")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()("), std::string(")(()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()(())"), std::string("())())"), std::string("QC())()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(X(b)))A"), std::string("VHErF5cnJC)"), std::string("No"), std::string("(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()("), std::string(")"), std::string(")(K)")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")"), std::string("("), std::string("4ypLX")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()())(("), std::string("(())))")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("y0Vg"), std::string("(()())((")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("o"), std::string(")("), std::string(")("), std::string("(At)()"), std::string("yk8M8v"), std::string("(U"), std::string("(())()"), std::string("2tCM)Bd839")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()("), std::string(""), std::string("(())()"), std::string("9)"), std::string("(()())(("), std::string("(4)")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(((("), std::string("((())"), std::string("6I")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")(P))"), std::string("tiGPO487oD"), std::string("()5()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()"), std::string("h()Q()(("), std::string("i("), std::string(")"), std::string("9FR33yss"), std::string("")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")())"), std::string("(()()(")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(())))"), std::string("a(A"), std::string("VL8kgDjI"), std::string("(()()("), std::string("(()())((")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")"), std::string("()(")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")(()"), std::string("(()("), std::string("f")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("()())"), std::string(")"), std::string("WVrZRfgKU8aB"), std::string(")(()"), std::string("GTTPRD7jSnl"), std::string("X(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()())(("), std::string("Kn9"), std::string("((())")})), (std::string("No")));
}
