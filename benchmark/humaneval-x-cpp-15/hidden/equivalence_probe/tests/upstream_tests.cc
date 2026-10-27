// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_15.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_113 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_113) {

    HE_ASSERT(issame(odd_count({"1234567"}) , {"the number of odd elements 4n the str4ng 4 of the 4nput."}));
    HE_ASSERT(issame(odd_count({"3","11111111"}) , {"the number of odd elements 1n the str1ng 1 of the 1nput.", "the number of odd elements 8n the str8ng 8 of the 8nput."}));
    HE_ASSERT(issame(odd_count({"271", "137", "314"}) , {
        "the number of odd elements 2n the str2ng 2 of the 2nput.",
        "the number of odd elements 3n the str3ng 3 of the 3nput.",
        "the number of odd elements 2n the str2ng 2 of the 2nput."
    }));
}

}  // namespace he_cpp_113

namespace he_cpp_114 {


TEST(HumanEvalX, CPP_114) {

    HE_ASSERT(minSubArraySum({2, 3, 4, 1, 2, 4}) == 1);
    HE_ASSERT(minSubArraySum({-1, -2, -3}) == -6);
    HE_ASSERT(minSubArraySum({-1, -2, -3, 2, -10}) == -14);
    HE_ASSERT(minSubArraySum({-9999999999999999}) == -9999999999999999);
    HE_ASSERT(minSubArraySum({0, 10, 20, 1000000}) == 0);
    HE_ASSERT(minSubArraySum({-1, -2, -3, 10, -5}) == -6);
    HE_ASSERT(minSubArraySum({100, -1, -2, -3, 10, -5}) == -6);
    HE_ASSERT(minSubArraySum({10, 11, 13, 8, 3, 4}) == 3);
    HE_ASSERT(minSubArraySum({100, -33, 32, -1, 0, -2}) == -33);
    HE_ASSERT(minSubArraySum({-10}) == -10);
    HE_ASSERT(minSubArraySum({7}) == 7);
    HE_ASSERT(minSubArraySum({1, -1}) == -1);
}

}  // namespace he_cpp_114

namespace he_cpp_115 {


TEST(HumanEvalX, CPP_115) {

    HE_ASSERT(max_fill({{0,0,1,0}, {0,1,0,0}, {1,1,1,1}}, 1) == 6);
    HE_ASSERT(max_fill({{0,0,1,1}, {0,0,0,0}, {1,1,1,1}, {0,1,1,1}}, 2) == 5);
    HE_ASSERT(max_fill({{0,0,0}, {0,0,0}}, 5) == 0);
    HE_ASSERT(max_fill({{1,1,1,1}, {1,1,1,1}}, 2) == 4);
    HE_ASSERT(max_fill({{1,1,1,1}, {1,1,1,1}}, 9) == 2);
}

}  // namespace he_cpp_115

namespace he_cpp_116 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_116) {

    HE_ASSERT(issame(sort_array({1,5,2,3,4}) , {1, 2, 4, 3, 5}));
    HE_ASSERT(issame(sort_array({-2,-3,-4,-5,-6}) , {-4, -2, -6, -5, -3}));
    HE_ASSERT(issame(sort_array({1,0,2,3,4}) , {0, 1, 2, 4, 3}));
    HE_ASSERT(issame(sort_array({}) , {}));
    HE_ASSERT(issame(sort_array({2,5,77,4,5,3,5,7,2,3,4}) , {2, 2, 4, 4, 3, 3, 5, 5, 5, 7, 77}));
    HE_ASSERT(issame(sort_array({3,6,44,12,32,5}) , {32, 3, 5, 6, 12, 44}));
    HE_ASSERT(issame(sort_array({2,4,8,16,32}) , {2, 4, 8, 16, 32}));
    HE_ASSERT(issame(sort_array({2,4,8,16,32}) , {2, 4, 8, 16, 32}));
}

}  // namespace he_cpp_116

namespace he_cpp_117 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_117) {

    HE_ASSERT(issame(select_words("Mary had a little lamb", 4) , {"little"}   ));
    HE_ASSERT(issame(select_words("Mary had a little lamb", 3) , {"Mary", "lamb"} ));
    HE_ASSERT(issame(select_words("simple white space", 2) , {}     ));
    HE_ASSERT(issame(select_words("Hello world", 4) , {"world"}  ));
    HE_ASSERT(issame(select_words("Uncle sam", 3) , {"Uncle"}));
    HE_ASSERT(issame(select_words("", 4) , {}));
    HE_ASSERT(issame(select_words("a b c d e f", 1) , {"b", "c", "d", "f"}));
}

}  // namespace he_cpp_117

namespace he_cpp_118 {


TEST(HumanEvalX, CPP_118) {

    HE_ASSERT(get_closest_vowel("yogurt") == "u");
    HE_ASSERT(get_closest_vowel("full") == "u");
    HE_ASSERT(get_closest_vowel("easy") == "");
    HE_ASSERT(get_closest_vowel("eAsy") == "");
    HE_ASSERT(get_closest_vowel("ali") == "");
    HE_ASSERT(get_closest_vowel("bad") == "a");
    HE_ASSERT(get_closest_vowel("most") =="o");
    HE_ASSERT(get_closest_vowel("ab") == "");
    HE_ASSERT(get_closest_vowel("ba") == "");
    HE_ASSERT(get_closest_vowel("quick") == "");
    HE_ASSERT(get_closest_vowel("anime") == "i");
    HE_ASSERT(get_closest_vowel("Asia") == "");
    HE_ASSERT(get_closest_vowel("Above") == "o");
}

}  // namespace he_cpp_118

namespace he_cpp_119 {


TEST(HumanEvalX, CPP_119) {

    HE_ASSERT(match_parens({"()(", ")"}) == "Yes");
    HE_ASSERT(match_parens({")", ")"}) == "No");
    HE_ASSERT(match_parens({"(()(())", "())())"}) == "No");
    HE_ASSERT(match_parens({")())", "(()()("}) == "Yes");
    HE_ASSERT(match_parens({"(())))", "(()())(("}) == "Yes");
    HE_ASSERT(match_parens({"()", "())"}) == "No");
    HE_ASSERT(match_parens({"(()(", "()))()"}) == "Yes");
    HE_ASSERT(match_parens({"((((", "((())"}) == "No");
    HE_ASSERT(match_parens({")(()", "(()("}) == "No");
    HE_ASSERT(match_parens({")(", ")("}) == "No");
    HE_ASSERT(match_parens({"(", ")"}) == "Yes");
    HE_ASSERT(match_parens({")", "("}) == "Yes" );
}

}  // namespace he_cpp_119

namespace he_cpp_120 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_120) {

    HE_ASSERT(issame(maximum({-3, -4, 5}, 3) , {-4, -3, 5}));
    HE_ASSERT(issame(maximum({4, -4, 4}, 2) , {4, 4}));
    HE_ASSERT(issame(maximum({-3, 2, 1, 2, -1, -2, 1}, 1) , {2}));
    HE_ASSERT(issame(maximum({123, -123, 20, 0 , 1, 2, -3}, 3) , {2, 20, 123}));
    HE_ASSERT(issame(maximum({-123, 20, 0 , 1, 2, -3}, 4) , {0, 1, 2, 20}));
    HE_ASSERT(issame(maximum({5, 15, 0, 3, -13, -8, 0}, 7) , {-13, -8, 0, 0, 3, 5, 15}));
    HE_ASSERT(issame(maximum({-1, 0, 2, 5, 3, -10}, 2) , {3, 5}));
    HE_ASSERT(issame(maximum({1, 0, 5, -7}, 1) , {5}));
    HE_ASSERT(issame(maximum({4, -4}, 2) , {-4, 4}));
    HE_ASSERT(issame(maximum({-10, 10}, 2) , {-10, 10}));
    HE_ASSERT(issame(maximum({1, 2, 3, -23, 243, -400, 0}, 0) , {}));
}

}  // namespace he_cpp_120
