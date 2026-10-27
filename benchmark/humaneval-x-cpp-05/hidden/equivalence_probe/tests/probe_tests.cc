// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_05.h"

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

TEST(Probe, sort_third_01) {
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, -623})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, -623}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 5, 9, 8, 1})), (std::vector<int >{2, 6, 3, 4, 5, 9, 8, 1}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 8, 9, 5, 1})), (std::vector<int >{1, 6, 3, 2, 9, 5, 8}));
    EXPECT_EQ((sort_third(std::vector<int >{-3, 5, 3, -1, 123})), (std::vector<int >{-3, 5, 3, -1, 123}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 3, 4, 8, 9, 2})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 3, 4, 8, 9, 2, 1})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 8, -12, 4, 23, 2, 3, -10, 12, 11})), (std::vector<int >{3, 8, -12, 4, 23, 2, 5, -10, 12, 11}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1}));
    EXPECT_EQ((sort_third(std::vector<int >{-5, 313, -3, 19, 12})), (std::vector<int >{-5, 313, -3, 19, 12}));
    EXPECT_EQ((sort_third(std::vector<int >{23})), (std::vector<int >{23}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10})), (std::vector<int >{1, 3, -5, 2, -3, 3, 5, 0, 123, 9, -10}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 4, 3, 6, 8, 9, 2})), (std::vector<int >{2, 4, 3, 5, 8, 9, 6}));
    EXPECT_EQ((sort_third(std::vector<int >{22, -7})), (std::vector<int >{22, -7}));
    EXPECT_EQ((sort_third(std::vector<int >{4, 1, 12345, 199, -11})), (std::vector<int >{4, 1, 12345, 199, -11}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10, 5})), (std::vector<int >{1, 3, -5, 2, -3, 3, 5, 0, 123, 9, -10, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{-10, 6, 6, 1, -6})), (std::vector<int >{-10, 6, 6, 1, -6}));
    EXPECT_EQ((sort_third(std::vector<int >{12, 4})), (std::vector<int >{12, 4}));
    EXPECT_EQ((sort_third(std::vector<int >{3, 6, 5, 4, 8, 9, 2})), (std::vector<int >{2, 6, 5, 3, 8, 9, 4}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 9, 4, 3, 2})), (std::vector<int >{4, 6, 9, 5, 3, 2}));
    EXPECT_EQ((sort_third(std::vector<int >{-13, 300, 0, 16, 20, 12})), (std::vector<int >{-13, 300, 0, 16, 20, 12}));
    EXPECT_EQ((sort_third(std::vector<int >{0, 11, -557, 9, 1, 29, -10, 7})), (std::vector<int >{-10, 11, -557, 0, 1, 29, 9, 7}));
    EXPECT_EQ((sort_third(std::vector<int >{8, 123, -9, 6, 1, 3})), (std::vector<int >{6, 123, -9, 8, 1, 3}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 9, 3, 4, 6, 8, 2})), (std::vector<int >{2, 9, 3, 4, 6, 8, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 3, 4, 6, 9, 2})), (std::vector<int >{5, 3, 4, 6, 9, 2}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, 3})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, 3}));
}

TEST(Probe, sort_third_02) {
    EXPECT_EQ((sort_third(std::vector<int >{5, 8, 3, 4, 6, 9, 2, -1})), (std::vector<int >{2, 8, 3, 4, 6, 9, 5, -1}));
    EXPECT_EQ((sort_third(std::vector<int >{26, 4, 2, -3})), (std::vector<int >{-3, 4, 2, 26}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 8, -12, 4, 23, 2, 3, 11, 12, -777})), (std::vector<int >{-777, 8, -12, 3, 23, 2, 4, 11, 12, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 9, 4, 8, 3, 2})), (std::vector<int >{2, 6, 9, 4, 8, 3, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{-10, 4, -489, 10})), (std::vector<int >{-10, 4, -489, 10}));
    EXPECT_EQ((sort_third(std::vector<int >{-6, 8, 14, -8, 895, 801, 2})), (std::vector<int >{-8, 8, 14, -6, 895, 801, 2}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, 5})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 8, 3, 4, 6, 9, 5})), (std::vector<int >{2, 8, 3, 4, 6, 9, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{3})), (std::vector<int >{3}));
    EXPECT_EQ((sort_third(std::vector<int >{-12, 8})), (std::vector<int >{-12, 8}));
    EXPECT_EQ((sort_third(std::vector<int >{30})), (std::vector<int >{30}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 11, 15, 15, 11})), (std::vector<int >{2, 6, 11, 15, 15, 11}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 8, 3, 4, 6, 9, 2, 5})), (std::vector<int >{2, 8, 3, 4, 6, 9, 5, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{3, -5, 2, -3, 3, 9, 0, 123, 1, -10})), (std::vector<int >{-10, -5, 2, -3, 3, 9, 0, 123, 1, 3}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 8, 30, 4, 6, 9, 2})), (std::vector<int >{2, 8, 30, 4, 6, 9, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 3, 4, 8, 9, 2, 1, 8})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 1, 8}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 2, -12, 4, 23, 2, 3, 11, 12, -10})), (std::vector<int >{-10, 2, -12, 3, 23, 2, 4, 11, 12, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{8, -451, 123, 832, 135, 0})), (std::vector<int >{8, -451, 123, 832, 135, 0}));
    EXPECT_EQ((sort_third(std::vector<int >{748, 26, 874, -9, 4, 19})), (std::vector<int >{-9, 26, 874, 748, 4, 19}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 9, 4, 2, 3, 2})), (std::vector<int >{2, 6, 9, 4, 2, 3, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 3, 4, 6, 9, 2})), (std::vector<int >{2, 6, 3, 4, 6, 9, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{5, -5, 2, -3, 3, 9, 0, 123, 1, -10})), (std::vector<int >{-10, -5, 2, -3, 3, 9, 0, 123, 1, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{11, 2, -10, -10, 4})), (std::vector<int >{-10, 2, -10, 11, 4}));
}

TEST(Probe, unique_01) {
    EXPECT_EQ((unique(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 9, 0, 123})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{190, 533, -5, 125, 25, 17, 11})), (std::vector<int >{-5, 11, 17, 25, 125, 190, 533}));
    EXPECT_EQ((unique(std::vector<int >{124, 125, 9})), (std::vector<int >{9, 124, 125}));
    EXPECT_EQ((unique(std::vector<int >{3})), (std::vector<int >{3}));
    EXPECT_EQ((unique(std::vector<int >{0, 3, 5, 9, 123})), (std::vector<int >{0, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{3, -5, 29, -990})), (std::vector<int >{-990, -5, 3, 29}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 489, 123})), (std::vector<int >{0, 2, 3, 5, 123, 489}));
    EXPECT_EQ((unique(std::vector<int >{469, 4, 21})), (std::vector<int >{4, 21, 469}));
    EXPECT_EQ((unique(std::vector<int >{846, 2, 5, 274, 235})), (std::vector<int >{2, 5, 235, 274, 846}));
    EXPECT_EQ((unique(std::vector<int >{-835, 543, 123, 30})), (std::vector<int >{-835, 30, 123, 543}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, -573, 9, 0, 123})), (std::vector<int >{-573, 0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 9, 2, 3, 3, 5, 0, 123})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 9, 123, -465})), (std::vector<int >{-465, 0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{-104, -779})), (std::vector<int >{-779, -104}));
    EXPECT_EQ((unique(std::vector<int >{123, -739, 29, 26, 0})), (std::vector<int >{-739, 0, 26, 29, 123}));
    EXPECT_EQ((unique(std::vector<int >{4, 7, -7, 3, 123, 11, 26})), (std::vector<int >{-7, 3, 4, 7, 11, 26, 123}));
    EXPECT_EQ((unique(std::vector<int >{610})), (std::vector<int >{610}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123, -3})), (std::vector<int >{-3, 0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 9, 123})), (std::vector<int >{2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{20, -1, 123, 2, 2})), (std::vector<int >{-1, 2, 20, 123}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 9})), (std::vector<int >{0, 2, 3, 5, 9}));
    EXPECT_EQ((unique(std::vector<int >{82, 2})), (std::vector<int >{2, 82}));
    EXPECT_EQ((unique(std::vector<int >{0, 7, 3, 5, 9, 123})), (std::vector<int >{0, 3, 5, 7, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 9, 123, 0})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
}

TEST(Probe, unique_02) {
    EXPECT_EQ((unique(std::vector<int >{0, 3, 2, 5, 9, 123})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{9, 11})), (std::vector<int >{9, 11}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, -1, 9, 123})), (std::vector<int >{-1, 0, 2, 3, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{0, 22, 3, 5, 9, 123})), (std::vector<int >{0, 3, 5, 9, 22, 123}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123, 27})), (std::vector<int >{0, 2, 3, 5, 9, 27, 123}));
    EXPECT_EQ((unique(std::vector<int >{-571, 0, 4, 9, 11, -1})), (std::vector<int >{-571, -1, 0, 4, 9, 11}));
    EXPECT_EQ((unique(std::vector<int >{495, 189, 1})), (std::vector<int >{1, 189, 495}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123, 17})), (std::vector<int >{0, 2, 3, 5, 9, 17, 123}));
    EXPECT_EQ((unique(std::vector<int >{22, 9, -5})), (std::vector<int >{-5, 9, 22}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123, 644})), (std::vector<int >{0, 2, 3, 5, 9, 123, 644}));
    EXPECT_EQ((unique(std::vector<int >{27, -1, 0, -617, -2, 123, 123})), (std::vector<int >{-617, -2, -1, 0, 27, 123}));
    EXPECT_EQ((unique(std::vector<int >{1, 5, 9, 5, 14, 19})), (std::vector<int >{1, 5, 9, 14, 19}));
    EXPECT_EQ((unique(std::vector<int >{19, 2, 5, 5, 9})), (std::vector<int >{2, 5, 9, 19}));
    EXPECT_EQ((unique(std::vector<int >{3, 157, 28})), (std::vector<int >{3, 28, 157}));
    EXPECT_EQ((unique(std::vector<int >{-5})), (std::vector<int >{-5}));
    EXPECT_EQ((unique(std::vector<int >{12, 3, 5, 2, 3, 3, 9, 0, 123})), (std::vector<int >{0, 2, 3, 5, 9, 12, 123}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 123, 2, 3, 3, 9, 0, 5})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0})), (std::vector<int >{0, 2, 3, 5, 9}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 9, 123, -3})), (std::vector<int >{-3, 0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{9, 2, 123, 3, 3, 0})), (std::vector<int >{0, 2, 3, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{1000, 21, 959, 7, 2, 123, 0, 21})), (std::vector<int >{0, 2, 7, 21, 123, 959, 1000}));
    EXPECT_EQ((unique(std::vector<int >{5, 7, 497})), (std::vector<int >{5, 7, 497}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 125, 0, 123})), (std::vector<int >{0, 2, 3, 5, 123, 125}));
}

TEST(Probe, max_element_01) {
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 123.0f, 1.0f, -10.0f, -3.55999994f}), 123.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 3.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 3.0f, -11.1999998f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{10.1999998f}), 10.1999998f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-14.3999996f, 9.99999975e-05f, 9.99999975e-05f, 1.39999998f}), 1.39999998f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 2.0999999f}), 2.0999999f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{18.7999992f, 0.0f}), 18.7999992f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 123.0f, 1.0f, -10.0f}), 123.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{2.0f, 3.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 9.99999975e-05f, 1.0f, -10.0f}), 9.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 3.0f, 9.99999975e-05f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 3.0f, -2.50999999f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-12.6000004f}), -12.6000004f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{9.99999975e-05f, 9.99999975e-05f, -3.0f, 0.100000001f}), 0.100000001f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, -10.0f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{16.1000004f, 0.0f, 17.7000008f, -5.0f, -1.29999995f}), 17.7000008f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, 15.6000004f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, -10.0f, -8.98999977f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{9.99999975e-05f, -5.0f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f}), 9.99999975e-05f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 3.0f, 4.5f}), 4.5f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{3.20000005f}), 3.20000005f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.20009995f, -0.899900019f, 17.8999996f, 1.70009995f}), 17.8999996f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 9.0f, 3.0f, 0.0f, 123.0f, 1.0f, -10.0f}), 123.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{9.99999975e-05f, 2.0f, 3.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{9.99999975e-05f, -1.46000004f, 6.0f}), 6.0f, 1e-5);
}

TEST(Probe, max_element_02) {
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, -10.0f, 9.0f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, -10.0f, 9.99999975e-05f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 3.0f, -1.79990005f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 1.0f, -10.0f}), 9.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{2.0f, 1.0f, 3.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, -12.5f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, -10.0f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.19999981f, 9.38000011f, -16.2999992f, -0.299899995f}), 9.38000011f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-14.6999998f, 9.99999975e-05f}), 9.99999975e-05f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{9.99999975e-05f, -2.0f, -18.7999992f, -12.8999996f, -3.80999994f, -7.9000001f, 9.99999975e-05f}), 9.99999975e-05f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-11.6999998f, 9.99999975e-05f, -14.1000004f, 10.3000002f}), 10.3000002f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 9.99999975e-05f, 3.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, -14.8999996f, -9.0f, -13.8999996f, -0.699899971f, 1.10010004f, 9.99999975e-05f, 1.20009995f}), 1.20009995f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-18.3999996f, 1.21000004f, 3.8599999f, -5.0f, 14.6999998f}), 14.6999998f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.90009999f, 2.0f}), 2.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 9.99999975e-05f}), 2.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 3.0f, 2.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{2.93000007f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f}), 2.93000007f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{6.46000004f, 4.30000019f, -14.6999998f, 0.400099993f, 9.99999975e-05f, -3.28999996f, 0.300000012f}), 6.46000004f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 124.0f, 1.0f, -10.0f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-16.7000008f, -1.09990001f, 0.100100003f, 9.99999975e-05f, -5.0f}), 0.100100003f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-14.1999998f, 0.0f, -6.80000019f, 0.0f, -3.0999999f, 0.300000012f}), 0.300000012f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, -10.0f, 1.0f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, -10.0f, 1.0f, 123.0f}), 123.0f, 1e-5);
}

TEST(Probe, fizz_buzz_01) {
    EXPECT_EQ((fizz_buzz(26)), (0));
    EXPECT_EQ((fizz_buzz(0)), (0));
    EXPECT_EQ((fizz_buzz(100)), (3));
    EXPECT_EQ((fizz_buzz(-579)), (0));
    EXPECT_EQ((fizz_buzz(-9)), (0));
    EXPECT_EQ((fizz_buzz(-959)), (0));
    EXPECT_EQ((fizz_buzz(78)), (2));
    EXPECT_EQ((fizz_buzz(-921)), (0));
    EXPECT_EQ((fizz_buzz(100002)), (8026));
    EXPECT_EQ((fizz_buzz(98)), (3));
    EXPECT_EQ((fizz_buzz(-5)), (0));
    EXPECT_EQ((fizz_buzz(2)), (0));
    EXPECT_EQ((fizz_buzz(-878)), (0));
    EXPECT_EQ((fizz_buzz(-406)), (0));
    EXPECT_EQ((fizz_buzz(3)), (0));
    EXPECT_EQ((fizz_buzz(173)), (4));
    EXPECT_EQ((fizz_buzz(-255)), (0));
    EXPECT_EQ((fizz_buzz(-591)), (0));
    EXPECT_EQ((fizz_buzz(190)), (6));
    EXPECT_EQ((fizz_buzz(-778)), (0));
    EXPECT_EQ((fizz_buzz(9998)), (639));
    EXPECT_EQ((fizz_buzz(-1)), (0));
    EXPECT_EQ((fizz_buzz(614)), (18));
    EXPECT_EQ((fizz_buzz(-2)), (0));
    EXPECT_EQ((fizz_buzz(25)), (0));
}

TEST(Probe, fizz_buzz_02) {
    EXPECT_EQ((fizz_buzz(639)), (20));
    EXPECT_EQ((fizz_buzz(-6)), (0));
    EXPECT_EQ((fizz_buzz(-244)), (0));
    EXPECT_EQ((fizz_buzz(7)), (0));
    EXPECT_EQ((fizz_buzz(22)), (0));
    EXPECT_EQ((fizz_buzz(10)), (0));
    EXPECT_EQ((fizz_buzz(-3)), (0));
    EXPECT_EQ((fizz_buzz(80)), (3));
    EXPECT_EQ((fizz_buzz(623)), (18));
    EXPECT_EQ((fizz_buzz(905)), (44));
    EXPECT_EQ((fizz_buzz(76)), (0));
    EXPECT_EQ((fizz_buzz(346)), (10));
    EXPECT_EQ((fizz_buzz(370)), (10));
    EXPECT_EQ((fizz_buzz(14)), (0));
    EXPECT_EQ((fizz_buzz(235)), (6));
    EXPECT_EQ((fizz_buzz(24)), (0));
    EXPECT_EQ((fizz_buzz(5)), (0));
    EXPECT_EQ((fizz_buzz(11)), (0));
    EXPECT_EQ((fizz_buzz(79)), (3));
    EXPECT_EQ((fizz_buzz(13)), (0));
    EXPECT_EQ((fizz_buzz(200)), (6));
    EXPECT_EQ((fizz_buzz(231)), (6));
    EXPECT_EQ((fizz_buzz(100000)), (8026));
}

TEST(Probe, sort_even_01) {
    ExpectNearVec(sort_even(std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, -2.31999993f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, -2.31999993f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, 18.2000008f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, 18.2000008f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{3.0f, 6.0f, 5.0f, 4.0f}), std::vector<float >{3.0f, 6.0f, 5.0f, 4.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{1.0f, 2.0f, 3.0f}), std::vector<float >{1.0f, 2.0f, 3.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{123.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, -10.0f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 8.0f, -12.0f, 4.0f, 23.0f, 2.0f, 3.0f, 11.0f, 12.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 12.0f, 11.0f, 23.0f, -10.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{11.0f, 8.0f, -12.0f, 4.0f, 23.0f, 2.0f, 3.0f, 5.0f, 12.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 11.0f, 2.0f, 12.0f, 5.0f, 23.0f, -10.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-5.0f, -5.0f, 9.99999975e-05f}), std::vector<float >{-5.0f, -5.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 6.0f, 3.0f, 4.0f, 0.409999996f}), std::vector<float >{0.409999996f, 6.0f, 3.0f, 4.0f, 5.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 123.0f, 1.0f, -10.0f, -14.1000004f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, -14.1000004f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.99999975e-05f, 9.99999975e-05f, -1.79990005f, 9.99999975e-05f}), std::vector<float >{-1.79990005f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 123.0f, 1.0f, -10.0f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 8.0f, -12.0f, 8.69999981f, 23.0f, 2.0f, 3.0f, 11.0f, 12.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, 3.0f, 8.69999981f, 5.0f, 2.0f, 12.0f, 11.0f, 23.0f, -10.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 12.0f, 11.0f, 23.0f, -10.0f, -6.5999999f}), std::vector<float >{-12.0f, 8.0f, -6.5999999f, 4.0f, 3.0f, 2.0f, 5.0f, 11.0f, 12.0f, -10.0f, 23.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 9.80000019f, 123.0f, 1.0f, -10.0f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 9.80000019f, 9.0f, 1.0f, 123.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-8.30000019f, -1.79990005f, 9.99999975e-05f, 1.80009997f, -4.5999999f, 4.0f, 9.99999975e-05f}), std::vector<float >{-8.30000019f, -1.79990005f, -4.5999999f, 1.80009997f, 9.99999975e-05f, 4.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{3.0f, 6.0f, 5.0f, 4.0f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 6.0f, 3.0f, 4.0f, 5.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{13.5f, 0.0f, -13.5f, 12.8000002f, 1.67999995f, 17.2999992f}), std::vector<float >{-13.5f, 0.0f, 1.67999995f, 12.8000002f, 13.5f, 17.2999992f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-7.9000001f, -1.89999998f, 9.99999975e-05f}), std::vector<float >{-7.9000001f, -1.89999998f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{1.30009997f, 12.0f, -0.349999994f}), std::vector<float >{-0.349999994f, 12.0f, 1.30009997f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{4.0f, -14.8999996f, -15.3000002f, 23.0f, 6.0f, 4.5999999f, 8.69999981f}), std::vector<float >{-15.3000002f, -14.8999996f, 4.0f, 23.0f, 6.0f, 4.5999999f, 8.69999981f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-15.3999996f, 5.59000015f, -0.300000012f, -1.0f, 1.89999998f, -1.49989998f, 1.90009999f}), std::vector<float >{-15.3999996f, 5.59000015f, -0.300000012f, -1.0f, 1.89999998f, -1.49989998f, 1.90009999f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{2.0f, 3.0f}), std::vector<float >{2.0f, 3.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 9.99999975e-05f, 3.0f, 4.0f}), std::vector<float >{3.0f, 9.99999975e-05f, 5.0f, 4.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 8.0f, -12.0f, 4.0f, 23.0f, 2.0f, 3.0f, -10.0f, 12.0f, 11.0f}), std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 12.0f, -10.0f, 23.0f, 11.0f}, 1e-5);
}

TEST(Probe, sort_even_02) {
    ExpectNearVec(sort_even(std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, -1.49989998f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f, -1.49989998f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-2.0999999f, -1.70000005f, 1.60010004f, -6.5f, 9.99999975e-05f, 0.500100017f, 17.7000008f}), std::vector<float >{-2.0999999f, -1.70000005f, 9.99999975e-05f, -6.5f, 1.60010004f, 0.500100017f, 17.7000008f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{2.0f, 1.0f, 3.0f}), std::vector<float >{2.0f, 1.0f, 3.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 3.0f, -5.0f, 9.0f, -3.0f, 3.0f, 2.0f, 0.0f, 123.0f, 1.0f, -10.0f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 9.0f, -3.0f, 3.0f, 2.0f, 0.0f, 5.0f, 1.0f, 123.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{3.0f, 4.0f, 5.0f, 6.0f}), std::vector<float >{3.0f, 4.0f, 5.0f, 6.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-12.0f, 8.0f, 4.0f, 5.0f, 2.0f, 12.0f, 11.0f, 23.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, -10.0f, 5.0f, 2.0f, 12.0f, 4.0f, 23.0f, 11.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.99999975e-05f, 123.0f}), std::vector<float >{9.99999975e-05f, 123.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.99999975e-05f, 2.0f, 4.19999981f, 6.69999981f, -1.39999998f, 18.3999996f, 9.99999975e-05f}), std::vector<float >{-1.39999998f, 2.0f, 9.99999975e-05f, 6.69999981f, 9.99999975e-05f, 18.3999996f, 4.19999981f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 11.0f, 23.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, -10.0f, 4.0f, 3.0f, 2.0f, 5.0f, 23.0f, 11.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 12.0f, 11.0f, 23.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, -10.0f, 4.0f, 3.0f, 12.0f, 5.0f, 23.0f, 11.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.39999962f, 9.99999975e-05f, -6.9000001f}), std::vector<float >{-6.9000001f, 9.99999975e-05f, 9.39999962f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-5.19999981f, 5.0f, 1.29999995f, -15.0f, 9.99999975e-05f, -4.5999999f, -5.0f, 7.69000006f}), std::vector<float >{-5.19999981f, 5.0f, -5.0f, -15.0f, 9.99999975e-05f, -4.5999999f, 1.29999995f, 7.69000006f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 0.0f, 123.0f, 1.0f, -10.0f}), std::vector<float >{-5.0f, 3.0f, -3.0f, 2.0f, 0.0f, 3.0f, 1.0f, 123.0f, 5.0f, -10.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 1.70009995f, -17.8999996f, 2.71000004f}), std::vector<float >{-17.8999996f, 9.99999975e-05f, 9.99999975e-05f, 1.70009995f, 9.99999975e-05f, 2.71000004f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-0.200000003f}), std::vector<float >{-0.200000003f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{1.0f, 2.0f}), std::vector<float >{1.0f, 2.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 8.0f, -12.0f, 4.0f, 23.0f, 12.0f, 3.0f, 11.0f, 2.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, 2.0f, 4.0f, 3.0f, 12.0f, 5.0f, 11.0f, 23.0f, -10.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-0.199900001f, 12.0f, 1.64999998f, -3.0f, -10.0f, 5.30000019f, 9.99999975e-05f}), std::vector<float >{-10.0f, 12.0f, -0.199900001f, -3.0f, 9.99999975e-05f, 5.30000019f, 1.64999998f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 8.0f, -12.0f, 23.0f, 2.0f, 3.0f, 11.0f, 12.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, -10.0f, 23.0f, 2.0f, 3.0f, 5.0f, 12.0f, 11.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.99999975e-05f, 6.0f, 5.0f, 4.0f}), std::vector<float >{9.99999975e-05f, 6.0f, 5.0f, 4.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{14.1000004f}), std::vector<float >{14.1000004f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{1.0f, 2.0f, 3.0f, 9.99999975e-05f}), std::vector<float >{1.0f, 2.0f, 3.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{123.0f, 9.99999975e-05f, 9.99999975e-05f, -1.09990001f, 0.0f}), std::vector<float >{0.0f, 9.99999975e-05f, 9.99999975e-05f, -1.09990001f, 123.0f}, 1e-5);
}

TEST(Probe, encode_cyclic_01) {
    EXPECT_EQ((encode_cyclic(std::string(" Co37WWcUj"))), (std::string("Co 7W3cUWj")));
    EXPECT_EQ((encode_cyclic(std::string("ZY9ol 9"))), (std::string("Y9Zl o9")));
    EXPECT_EQ((encode_cyclic(std::string("amrd"))), (std::string("mrad")));
    EXPECT_EQ((encode_cyclic(std::string("lGNobYNFmRHN"))), (std::string("GNlbYoFmNHNR")));
    EXPECT_EQ((encode_cyclic(std::string("s"))), (std::string("s")));
    EXPECT_EQ((encode_cyclic(std::string("t"))), (std::string("t")));
    EXPECT_EQ((encode_cyclic(std::string("u4F"))), (std::string("4Fu")));
    EXPECT_EQ((encode_cyclic(std::string("14AsmaYVPt "))), (std::string("4A1masVPYt ")));
    EXPECT_EQ((encode_cyclic(std::string("pT "))), (std::string("T p")));
    EXPECT_EQ((encode_cyclic(std::string("jd"))), (std::string("jd")));
    EXPECT_EQ((encode_cyclic(std::string("XcbGws7OrzLI"))), (std::string("cbXwsGOr7LIz")));
    EXPECT_EQ((encode_cyclic(std::string("O"))), (std::string("O")));
    EXPECT_EQ((encode_cyclic(std::string("1lu0zyXUVJV"))), (std::string("lu1zy0UVXJV")));
    EXPECT_EQ((encode_cyclic(std::string("hXpKIaF"))), (std::string("XphIaKF")));
    EXPECT_EQ((encode_cyclic(std::string("3W"))), (std::string("3W")));
    EXPECT_EQ((encode_cyclic(std::string("k"))), (std::string("k")));
    EXPECT_EQ((encode_cyclic(std::string("upwKo"))), (std::string("pwuKo")));
    EXPECT_EQ((encode_cyclic(std::string("8sfw0u1"))), (std::string("sf80uw1")));
    EXPECT_EQ((encode_cyclic(std::string("NrkUGr"))), (std::string("rkNGrU")));
    EXPECT_EQ((encode_cyclic(std::string("E"))), (std::string("E")));
    EXPECT_EQ((encode_cyclic(std::string("8aF"))), (std::string("aF8")));
    EXPECT_EQ((encode_cyclic(std::string("MGY"))), (std::string("GYM")));
    EXPECT_EQ((encode_cyclic(std::string("J"))), (std::string("J")));
    EXPECT_EQ((encode_cyclic(std::string("D"))), (std::string("D")));
    EXPECT_EQ((encode_cyclic(std::string("wtZqlTu"))), (std::string("tZwlTqu")));
}

TEST(Probe, encode_cyclic_02) {
    EXPECT_EQ((encode_cyclic(std::string("vP4OVu"))), (std::string("P4vVuO")));
    EXPECT_EQ((encode_cyclic(std::string("r"))), (std::string("r")));
    EXPECT_EQ((encode_cyclic(std::string("fQR2"))), (std::string("QRf2")));
    EXPECT_EQ((encode_cyclic(std::string("9P"))), (std::string("9P")));
    EXPECT_EQ((encode_cyclic(std::string("l"))), (std::string("l")));
    EXPECT_EQ((encode_cyclic(std::string("anExYkrfoh"))), (std::string("nEaYkxforh")));
    EXPECT_EQ((encode_cyclic(std::string(" "))), (std::string(" ")));
    EXPECT_EQ((encode_cyclic(std::string("a YRK5"))), (std::string(" YaK5R")));
    EXPECT_EQ((encode_cyclic(std::string("XR"))), (std::string("XR")));
    EXPECT_EQ((encode_cyclic(std::string("a6PNNdekNUl"))), (std::string("6PaNdNkNeUl")));
    EXPECT_EQ((encode_cyclic(std::string("72"))), (std::string("72")));
    EXPECT_EQ((encode_cyclic(std::string("3"))), (std::string("3")));
    EXPECT_EQ((encode_cyclic(std::string("S8"))), (std::string("S8")));
    EXPECT_EQ((encode_cyclic(std::string("0oVFuL1wMW0M"))), (std::string("oV0uLFwM10MW")));
    EXPECT_EQ((encode_cyclic(std::string("N"))), (std::string("N")));
    EXPECT_EQ((encode_cyclic(std::string("j"))), (std::string("j")));
    EXPECT_EQ((encode_cyclic(std::string("jj"))), (std::string("jj")));
    EXPECT_EQ((encode_cyclic(std::string("I"))), (std::string("I")));
    EXPECT_EQ((encode_cyclic(std::string("9h"))), (std::string("9h")));
    EXPECT_EQ((encode_cyclic(std::string("U"))), (std::string("U")));
    EXPECT_EQ((encode_cyclic(std::string("C"))), (std::string("C")));
    EXPECT_EQ((encode_cyclic(std::string("P"))), (std::string("P")));
    EXPECT_EQ((encode_cyclic(std::string("EDm3P0k"))), (std::string("DmEP03k")));
}

TEST(Probe, decode_cyclic_01) {
    EXPECT_EQ((decode_cyclic(std::string("DK"))), (std::string("DK")));
    EXPECT_EQ((decode_cyclic(std::string("4pw"))), (std::string("w4p")));
    EXPECT_EQ((decode_cyclic(std::string("pgN"))), (std::string("Npg")));
    EXPECT_EQ((decode_cyclic(std::string("w2"))), (std::string("w2")));
    EXPECT_EQ((decode_cyclic(std::string("l"))), (std::string("l")));
    EXPECT_EQ((decode_cyclic(std::string("kjbluk3f"))), (std::string("bkjklu3f")));
    EXPECT_EQ((decode_cyclic(std::string("WA"))), (std::string("WA")));
    EXPECT_EQ((decode_cyclic(std::string("roS"))), (std::string("Sro")));
    EXPECT_EQ((decode_cyclic(std::string("g"))), (std::string("g")));
    EXPECT_EQ((decode_cyclic(std::string("t"))), (std::string("t")));
    EXPECT_EQ((decode_cyclic(std::string("xQtiyY760GC"))), (std::string("txQYiy076GC")));
    EXPECT_EQ((decode_cyclic(std::string("le"))), (std::string("le")));
    EXPECT_EQ((decode_cyclic(std::string("jVA"))), (std::string("AjV")));
    EXPECT_EQ((decode_cyclic(std::string("z"))), (std::string("z")));
    EXPECT_EQ((decode_cyclic(std::string("4jEgVaQOxkL"))), (std::string("E4jagVxQOkL")));
    EXPECT_EQ((decode_cyclic(std::string("dJ"))), (std::string("dJ")));
    EXPECT_EQ((decode_cyclic(std::string("hpgczCm"))), (std::string("ghpCczm")));
    EXPECT_EQ((decode_cyclic(std::string("O"))), (std::string("O")));
    EXPECT_EQ((decode_cyclic(std::string("yctThqIvR"))), (std::string("tycqThRIv")));
    EXPECT_EQ((decode_cyclic(std::string("q9gj5BAHX3gw"))), (std::string("gq9Bj5XAHw3g")));
    EXPECT_EQ((decode_cyclic(std::string("F"))), (std::string("F")));
    EXPECT_EQ((decode_cyclic(std::string("k"))), (std::string("k")));
    EXPECT_EQ((decode_cyclic(std::string("n4zzl"))), (std::string("zn4zl")));
    EXPECT_EQ((decode_cyclic(std::string("6"))), (std::string("6")));
    EXPECT_EQ((decode_cyclic(std::string("3"))), (std::string("3")));
}

TEST(Probe, decode_cyclic_02) {
    EXPECT_EQ((decode_cyclic(std::string("ABnyE"))), (std::string("nAByE")));
    EXPECT_EQ((decode_cyclic(std::string("zF"))), (std::string("zF")));
    EXPECT_EQ((decode_cyclic(std::string("rz"))), (std::string("rz")));
    EXPECT_EQ((decode_cyclic(std::string("NAaU"))), (std::string("aNAU")));
    EXPECT_EQ((decode_cyclic(std::string("nUVvv4zAe"))), (std::string("VnU4vvezA")));
    EXPECT_EQ((decode_cyclic(std::string("B"))), (std::string("B")));
    EXPECT_EQ((decode_cyclic(std::string("c"))), (std::string("c")));
    EXPECT_EQ((decode_cyclic(std::string("2Ff"))), (std::string("f2F")));
    EXPECT_EQ((decode_cyclic(std::string("o"))), (std::string("o")));
    EXPECT_EQ((decode_cyclic(std::string("xH5KNlz3M0lI"))), (std::string("5xHlKNMz3I0l")));
    EXPECT_EQ((decode_cyclic(std::string("9L9bxo09o0"))), (std::string("99Lobxo090")));
    EXPECT_EQ((decode_cyclic(std::string("p"))), (std::string("p")));
    EXPECT_EQ((decode_cyclic(std::string("tvrQkC2iPFm"))), (std::string("rtvCQkP2iFm")));
    EXPECT_EQ((decode_cyclic(std::string("UggI5Q"))), (std::string("gUgQI5")));
    EXPECT_EQ((decode_cyclic(std::string("8L"))), (std::string("8L")));
    EXPECT_EQ((decode_cyclic(std::string("qmaz9AvxLlaV"))), (std::string("aqmAz9LvxVla")));
    EXPECT_EQ((decode_cyclic(std::string("u"))), (std::string("u")));
    EXPECT_EQ((decode_cyclic(std::string("1eJC "))), (std::string("J1eC ")));
    EXPECT_EQ((decode_cyclic(std::string("GrZZYlw0fB T"))), (std::string("ZGrlZYfw0TB ")));
    EXPECT_EQ((decode_cyclic(std::string("9rnLPcA4Tqax"))), (std::string("n9rcLPTA4xqa")));
    EXPECT_EQ((decode_cyclic(std::string("Q"))), (std::string("Q")));
    EXPECT_EQ((decode_cyclic(std::string("ORQlrqX"))), (std::string("QORqlrX")));
    EXPECT_EQ((decode_cyclic(std::string("w"))), (std::string("w")));
}

TEST(Probe, triples_sum_to_zero_01) {
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, -2, 1})), (true));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{7, -4, 13, 16, 1000, 11, 28, 4})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{850, 102, -1, 7})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{100, 3, 5, -100, 30})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, 0, -9})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 2, 5, 7, 99})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, -1})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 2, 7, 3})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, 0, 11})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, 0, 98})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 26})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{100, 3, 5, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{5, 3, 1, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-8, -100, -935, 8, 7, -100, 4, 15})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, -2, -5})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-1, 14, 7, 1, 23, 20, 2})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, 0, 17})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-654, -8, 7})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{3, 9, 6, -614, 7, 26, 18, 6})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{100, 3, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{5, 694, -1, 2, 5, 25, 1})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{2, 4, -5, 3, 9, 7})), (true));
}

TEST(Probe, triples_sum_to_zero_02) {
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{5, -5, 14, 2, -1, 15})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 5, 3, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{584, 30, 18, -100, 10})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{100, -5, -7, 331, 20, 99999, 2, -2})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-1, 9})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, -2, 1})), (true));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-183, 2, 5, 7})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-8, 564, -10, -2, -1})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 2, 3, 7})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{11, 5, -2})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{2, 24, 9})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{100, 3, 14, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{2, 4, 3, 9, 7})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 0, 5, 3})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 5, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{12345, 11, 154, 26, 0})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{5, -5, 4, -1, 101, 264})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-19, -806})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{2, -2, 15, -63, -100, 15, -4})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{5, 0, 99999})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{99999, 102, 5, 13, 2})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{25, 439, 1, -64, -6, 5, -1})), (true));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, -1, 11})), (false));
}
