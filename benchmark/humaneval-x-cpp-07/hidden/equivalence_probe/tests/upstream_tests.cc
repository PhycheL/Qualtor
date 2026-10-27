// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_07.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_049 {


TEST(HumanEvalX, CPP_049) {

    HE_ASSERT(modp(3, 5) == 3);
    HE_ASSERT(modp(1101, 101) == 2);
    HE_ASSERT(modp(0, 101) == 1);
    HE_ASSERT(modp(3, 11) == 8);
    HE_ASSERT(modp(100, 101) == 1);
    HE_ASSERT(modp(30, 5) == 4);
    HE_ASSERT(modp(31, 5) == 3);
}

}  // namespace he_cpp_049

namespace he_cpp_050 {


TEST(HumanEvalX, CPP_050) {

    
    for (int i=0;i<100;i++)
    {
        int l=10+rand()%11;
        string str="";
        for (int j=0;j<l;j++)
        {
            char chr=97+rand()%26;
            str+=chr;
        }

        string encoded_str = encode_shift(str);
        HE_ASSERT(decode_shift(encoded_str) == str);
    }
}

}  // namespace he_cpp_050

namespace he_cpp_051 {


TEST(HumanEvalX, CPP_051) {

    HE_ASSERT(remove_vowels("") == "");
    HE_ASSERT(remove_vowels("abcdef\nghijklm") == "bcdf\nghjklm");
    HE_ASSERT(remove_vowels("fedcba") == "fdcb");
    HE_ASSERT(remove_vowels("eeeee") == "");
    HE_ASSERT(remove_vowels("acBAA") == "cB");
    HE_ASSERT(remove_vowels("EcBOO") == "cB");
    HE_ASSERT(remove_vowels("ybcd") == "ybcd");
}

}  // namespace he_cpp_051

namespace he_cpp_052 {


TEST(HumanEvalX, CPP_052) {

    HE_ASSERT(below_threshold({1, 2, 4, 10}, 100));
    HE_ASSERT(not(below_threshold({1, 20, 4, 10}, 5)));
    HE_ASSERT(below_threshold({1, 20, 4, 10}, 21));
    HE_ASSERT(below_threshold({1, 20, 4, 10}, 22));
    HE_ASSERT(below_threshold({1, 8, 4, 10}, 11));
    HE_ASSERT(not(below_threshold({1, 8, 4, 10}, 10)));
}

}  // namespace he_cpp_052

namespace he_cpp_053 {


TEST(HumanEvalX, CPP_053) {

    HE_ASSERT(add(0, 1) == 1);
    HE_ASSERT(add(1, 0) == 1);
    HE_ASSERT(add(2, 3) == 5);
    HE_ASSERT(add(5, 7) == 12);
    HE_ASSERT(add(7, 5) == 12);
    for (int i=0;i<100;i+=1)
    {
        int x=rand()%1000;
        int y=rand()%1000;
        HE_ASSERT(add(x, y) == x + y);
    }
}

}  // namespace he_cpp_053

namespace he_cpp_054 {


TEST(HumanEvalX, CPP_054) {

    HE_ASSERT(same_chars("eabcdzzzz", "dddzzzzzzzddeddabc") == true);
    HE_ASSERT(same_chars("abcd", "dddddddabc") == true);
    HE_ASSERT(same_chars("dddddddabc", "abcd") == true);
    HE_ASSERT(same_chars("eabcd", "dddddddabc") == false);
    HE_ASSERT(same_chars("abcd", "dddddddabcf") == false);
    HE_ASSERT(same_chars("eabcdzzzz", "dddzzzzzzzddddabc") == false);
    HE_ASSERT(same_chars("aabb", "aaccc") == false);
}

}  // namespace he_cpp_054

namespace he_cpp_055 {


TEST(HumanEvalX, CPP_055) {

    HE_ASSERT(fib(10) == 55);
    HE_ASSERT(fib(1) == 1);
    HE_ASSERT(fib(8) == 21);
    HE_ASSERT(fib(11) == 89);
    HE_ASSERT(fib(12) == 144);
}

}  // namespace he_cpp_055

namespace he_cpp_056 {


TEST(HumanEvalX, CPP_056) {

    HE_ASSERT(correct_bracketing("<>"));
    HE_ASSERT(correct_bracketing("<<><>>"));
    HE_ASSERT(correct_bracketing("<><><<><>><>"));
    HE_ASSERT(correct_bracketing("<><><<<><><>><>><<><><<>>>"));
    HE_ASSERT(not (correct_bracketing("<<<><>>>>")));
    HE_ASSERT(not (correct_bracketing("><<>")));
    HE_ASSERT(not (correct_bracketing("<")));
    HE_ASSERT(not (correct_bracketing("<<<<")));
    HE_ASSERT(not (correct_bracketing(">")));
    HE_ASSERT(not (correct_bracketing("<<>")));
    HE_ASSERT(not (correct_bracketing("<><><<><>><>><<>")));
    HE_ASSERT(not (correct_bracketing("<><><<><>><>>><>")));
}

}  // namespace he_cpp_056
