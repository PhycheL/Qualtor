// 参考强测试集：Theatrical Players 账单 statement()。隐藏材料，不提供给被评测的生成 Agent。
// 断言以现有代码的实际运行结果为准（D001）：金额按分计算后除以 100，两位小数；金额和积分都带逗号千分位。
#include "statement.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

namespace {

nlohmann::json Plays() {
    return nlohmann::json::parse(R"({
        "hamlet": {"name": "Hamlet", "type": "tragedy"},
        "as-like": {"name": "As You Like It", "type": "comedy"},
        "othello": {"name": "Othello", "type": "tragedy"},
        "henry-v": {"name": "Henry V", "type": "history"}
    })");
}

nlohmann::json Invoice(const std::string& customer, const std::string& performances) {
    return nlohmann::json::parse("{\"customer\": \"" + customer + "\", \"performances\": " + performances + "}");
}

std::string One(const std::string& play, int audience) {
    return statement(Invoice("BigCo", "[{\"playID\": \"" + play + "\", \"audience\": " + std::to_string(audience) + "}]"),
                     Plays());
}

TEST(StatementTest, ExampleInvoice) {
    std::string expected =
        "Statement for BigCo\n"
        " Hamlet: $650.00 (55 seats)\n"
        " As You Like It: $580.00 (35 seats)\n"
        " Othello: $500.00 (40 seats)\n"
        "Amount owed is $1,730.00\n"
        "You earned 47 credits";
    EXPECT_EQ(expected, statement(Invoice("BigCo", R"([
        {"playID": "hamlet", "audience": 55},
        {"playID": "as-like", "audience": 35},
        {"playID": "othello", "audience": 40}])"), Plays()));
}

TEST(StatementTest, TragedyChargesExtraAboveThirtySeats) {
    EXPECT_EQ("Statement for BigCo\n Hamlet: $400.00 (30 seats)\nAmount owed is $400.00\nYou earned 0 credits",
              One("hamlet", 30));
    EXPECT_EQ("Statement for BigCo\n Hamlet: $410.00 (31 seats)\nAmount owed is $410.00\nYou earned 1 credits",
              One("hamlet", 31));
    EXPECT_EQ("Statement for BigCo\n Hamlet: $400.00 (0 seats)\nAmount owed is $400.00\nYou earned 0 credits",
              One("hamlet", 0));
}

TEST(StatementTest, ComedyChargesPerSeatAndExtraAboveTwentySeats) {
    EXPECT_EQ("Statement for BigCo\n As You Like It: $360.00 (20 seats)\nAmount owed is $360.00\nYou earned 4 credits",
              One("as-like", 20));
    EXPECT_EQ("Statement for BigCo\n As You Like It: $468.00 (21 seats)\nAmount owed is $468.00\nYou earned 4 credits",
              One("as-like", 21));
    EXPECT_EQ("Statement for BigCo\n As You Like It: $548.00 (31 seats)\nAmount owed is $548.00\nYou earned 7 credits",
              One("as-like", 31));
    EXPECT_EQ("Statement for BigCo\n As You Like It: $315.00 (5 seats)\nAmount owed is $315.00\nYou earned 1 credits",
              One("as-like", 5));
}

TEST(StatementTest, LargeAmountsUseThousandsSeparator) {
    EXPECT_EQ("Statement for BigCo\n Othello: $10,100.00 (1000 seats)\nAmount owed is $10,100.00\nYou earned 970 credits",
              One("othello", 1000));
    EXPECT_EQ("Statement for BigCo\n As You Like It: $16,300.00 (2000 seats)\nAmount owed is $16,300.00\nYou earned 2,370 credits",
              One("as-like", 2000));
}

TEST(StatementTest, EmptyInvoiceOwesNothing) {
    EXPECT_EQ("Statement for Acme\nAmount owed is $0.00\nYou earned 0 credits", statement(Invoice("Acme", "[]"), Plays()));
}

TEST(StatementTest, UnknownPlayTypeThrows) {
    EXPECT_THROW(One("henry-v", 53), std::domain_error);
    try {
        One("henry-v", 53);
        FAIL() << "应抛出 std::domain_error";
    } catch (const std::domain_error& error) {
        EXPECT_EQ(std::string("unknown type: history"), error.what());
    }
}

}  // namespace
