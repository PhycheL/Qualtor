// 参考强测试集：Racing-Car TirePressureMonitoring 的 Alarm。隐藏材料，不提供给被评测的生成 Agent。
// Sensor.cpp 不参与构建（链接替身题）：上游传感器读数是 srand(time(0)) 的随机数，测试用下面的替身提供读数。
#include "Alarm.h"
#include "Sensor.h"

#include <gtest/gtest.h>

#include <deque>

namespace {
std::deque<double> g_readings;
}  // namespace

Sensor::Sensor() {}

double Sensor::popNextPressurePsiValue() {
    double value = g_readings.front();
    g_readings.pop_front();
    return value;
}

namespace {

class AlarmTest : public ::testing::Test {
protected:
    void SetUp() override { g_readings.clear(); }

    bool AlarmAfter(double reading) {
        g_readings.push_back(reading);
        Alarm alarm;
        alarm.check();
        return alarm.isAlarmOn();
    }
};

TEST_F(AlarmTest, IsOffBeforeAnyCheck) {
    Alarm alarm;
    EXPECT_FALSE(alarm.isAlarmOn());
}

TEST_F(AlarmTest, PressureWithinLimitsKeepsAlarmOff) {
    EXPECT_FALSE(AlarmAfter(17.0));
    EXPECT_FALSE(AlarmAfter(19.5));
    EXPECT_FALSE(AlarmAfter(21.0));
}

TEST_F(AlarmTest, LowPressureTurnsAlarmOn) {
    EXPECT_TRUE(AlarmAfter(16.99));
    EXPECT_TRUE(AlarmAfter(0.0));
}

TEST_F(AlarmTest, HighPressureTurnsAlarmOn) {
    EXPECT_TRUE(AlarmAfter(21.01));
    EXPECT_TRUE(AlarmAfter(100.0));
}

TEST_F(AlarmTest, AlarmStaysOnOnceTriggered) {
    g_readings.push_back(16.0);
    g_readings.push_back(19.0);
    Alarm alarm;
    alarm.check();
    alarm.check();
    EXPECT_TRUE(alarm.isAlarmOn());
}

TEST_F(AlarmTest, NormalReadingsDoNotTriggerLater) {
    g_readings.push_back(18.0);
    g_readings.push_back(20.0);
    g_readings.push_back(22.0);
    Alarm alarm;
    alarm.check();
    EXPECT_FALSE(alarm.isAlarmOn());
    alarm.check();
    EXPECT_FALSE(alarm.isAlarmOn());
    alarm.check();
    EXPECT_TRUE(alarm.isAlarmOn());
}

TEST_F(AlarmTest, EachCheckConsumesOneReading) {
    g_readings.push_back(18.0);
    g_readings.push_back(18.0);
    g_readings.push_back(18.0);
    Alarm alarm;
    alarm.check();
    alarm.check();
    EXPECT_EQ(1u, g_readings.size());
}

}  // namespace
