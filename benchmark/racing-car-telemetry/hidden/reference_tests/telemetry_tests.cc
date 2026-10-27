// 参考强测试集：Racing-Car TelemetrySystem。隐藏材料，不提供给被评测的生成 Agent。
// 连接是否成功和随机报文取决于固定种子的 mt19937 与标准库的分布实现，这里只断言与实现无关的部分：
// 参数检查、诊断报文、随机报文的长度与字符范围，以及多次连接后终会上线。
#include "TelemetryClient.h"
#include "TelemetryDiagnosticControls.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

namespace {

const char kDiagnosticReport[] =
    "LAST TX rate................ 100 MBPS\r\n"
    "HIGHEST TX rate............. 100 MBPS\r\n"
    "LAST RX rate................ 100 MBPS\r\n"
    "HIGHEST RX rate............. 100 MBPS\r\n"
    "BIT RATE.................... 100000000\r\n"
    "WORD LEN.................... 16\r\n"
    "WORD/FRAME.................. 511\r\n"
    "BITS/FRAME.................. 8192\r\n"
    "MODULATION TYPE............. PCM/FM\r\n"
    "TX Digital Los.............. 0.75\r\n"
    "RX Digital Los.............. 0.10\r\n"
    "BEP Test.................... -5\r\n"
    "Local Rtrn Count............ 00\r\n"
    "Remote Rtrn Count........... 00";

TEST(TelemetryClientTest, StartsOffline) {
    TelemetryClient client;
    EXPECT_FALSE(client.getOnlineStatus());
    EXPECT_EQ("AT#UD", TelemetryClient::DIAGNOSTIC_MESSAGE);
}

TEST(TelemetryClientTest, RejectsEmptyConnectionStringAndMessage) {
    TelemetryClient client;
    EXPECT_THROW(client.connect(""), std::invalid_argument);
    EXPECT_FALSE(client.getOnlineStatus());
    EXPECT_THROW(client.send(""), std::invalid_argument);
}

TEST(TelemetryClientTest, EventuallyConnectsAndCanDisconnect) {
    TelemetryClient client;
    for (int attempt = 0; attempt < 20 && !client.getOnlineStatus(); ++attempt) client.connect("*111#");
    EXPECT_TRUE(client.getOnlineStatus());
    client.disconnect();
    EXPECT_FALSE(client.getOnlineStatus());
}

TEST(TelemetryClientTest, DiagnosticMessageIsAnsweredOnce) {
    TelemetryClient client;
    client.send(TelemetryClient::DIAGNOSTIC_MESSAGE);
    EXPECT_EQ(kDiagnosticReport, client.receive());
    std::string next = client.receive();
    EXPECT_NE(kDiagnosticReport, next);
    EXPECT_GE(next.size(), 61u);
    EXPECT_LE(next.size(), 110u);
}

TEST(TelemetryClientTest, OrdinaryMessageGetsRandomReply) {
    TelemetryClient client;
    client.send("hello");
    for (int i = 0; i < 20; ++i) {
        std::string reply = client.receive();
        ASSERT_GE(reply.size(), 61u);
        ASSERT_LE(reply.size(), 110u);
        for (size_t j = 0; j < reply.size(); ++j) {
            EXPECT_GE(reply[j], 86);
            EXPECT_LE(reply[j], 125);
        }
    }
}

TEST(TelemetryDiagnosticControlsTest, DiagnosticInfoCanBeSet) {
    TelemetryDiagnosticControls controls;
    EXPECT_EQ("", controls.getDiagnosticInfo());
    controls.setDiagnosticInfo("previous");
    EXPECT_EQ("previous", controls.getDiagnosticInfo());
}

TEST(TelemetryDiagnosticControlsTest, CheckTransmissionStoresDiagnosticReport) {
    TelemetryDiagnosticControls controls;
    controls.setDiagnosticInfo("previous");
    controls.checkTransmission();
    EXPECT_EQ(kDiagnosticReport, controls.getDiagnosticInfo());
    controls.checkTransmission();
    EXPECT_EQ(kDiagnosticReport, controls.getDiagnosticInfo());
}

}  // namespace
