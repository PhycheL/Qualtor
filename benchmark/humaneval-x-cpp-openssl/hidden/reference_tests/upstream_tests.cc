#include "functions.h"
#include <gtest/gtest.h>
#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))
namespace he_cpp_162 {


TEST(HumanEvalX, CPP_162) {

    HE_ASSERT(string_to_md5("Hello world") == "3e25960a79dbc69b674cd4ec67a72c62");
    HE_ASSERT(string_to_md5("") == "None");
    HE_ASSERT(string_to_md5("A B C") == "0ef78513b0cb8cef12743f5aeb35f888");
    HE_ASSERT(string_to_md5("password") == "5f4dcc3b5aa765d61d8327deb882cf99");
}

}  // namespace he_cpp_162
