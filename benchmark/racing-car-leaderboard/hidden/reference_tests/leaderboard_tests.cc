// 参考强测试集：Racing-Car LeaderBoard（车手、比赛积分与排行榜）。隐藏材料，不提供给被评测的生成 Agent。
// 断言以现有代码的实际运行结果为准（D001）：比赛按值保存 Driver，自动驾驶车会被切片，显示名就是算法版本号。
#include "Driver.h"
#include "LeaderBoard.h"
#include "Race.h"
#include "SelfDrivingCar.h"

#include <gtest/gtest.h>

#include <list>
#include <map>
#include <string>

namespace {

const Driver kNico("Nico Rosberg", "DE");
const Driver kLewis("Lewis Hamilton", "UK");
const Driver kSebastian("Sebastian Vettel", "DE");

std::list<Driver> Order(const Driver& a, const Driver& b, const Driver& c) {
    std::list<Driver> drivers;
    drivers.push_back(a);
    drivers.push_back(b);
    drivers.push_back(c);
    return drivers;
}

TEST(DriverTest, KeepsNameAndCountry) {
    EXPECT_EQ("Nico Rosberg", kNico.getName());
    EXPECT_EQ("DE", kNico.getCountry());
}

TEST(DriverTest, EqualWhenNameAndCountryMatch) {
    EXPECT_TRUE(kNico == kNico);
    EXPECT_TRUE(kNico == Driver("Nico Rosberg", "DE"));
    EXPECT_FALSE(kNico == Driver("Nico Rosberg", "FI"));
    EXPECT_FALSE(kNico == Driver("Nico Hulkenberg", "DE"));
}

TEST(SelfDrivingCarTest, UsesAlgorithmVersionAsNameAndCompanyAsCountry) {
    SelfDrivingCar car("1.2", "Acme");
    EXPECT_EQ("1.2", car.getAlgorithmVersion());
    EXPECT_EQ("1.2", car.getName());
    EXPECT_EQ("Acme", car.getCountry());
    car.setAlgorithmVersion("1.3");
    EXPECT_EQ("1.3", car.getAlgorithmVersion());
    EXPECT_EQ("1.2", car.getName());
}

TEST(RaceTest, PositionsPointsAndResults) {
    Race race("Australian Grand Prix", Order(kNico, kLewis, kSebastian));
    EXPECT_EQ("Australian Grand Prix", race.toString());
    EXPECT_EQ(0, race.position(kNico));
    EXPECT_EQ(1, race.position(kLewis));
    EXPECT_EQ(2, race.position(kSebastian));
    EXPECT_EQ(3, race.position(Driver("Max Verstappen", "NL")));
    EXPECT_EQ(25, race.getPoints(kNico));
    EXPECT_EQ(18, race.getPoints(kLewis));
    EXPECT_EQ(15, race.getPoints(kSebastian));
    std::list<Driver> results = race.getResults();
    ASSERT_EQ(3u, results.size());
    EXPECT_TRUE(results.front() == kNico);
    EXPECT_TRUE(results.back() == kSebastian);
    EXPECT_EQ("Lewis Hamilton", race.getDriverName(kLewis));
}

TEST(RaceTest, SelfDrivingCarIsStoredAsPlainDriver) {
    SelfDrivingCar car("1.2", "Acme");
    Race race("Malaysian Grand Prix", Order(car, kNico, kLewis));
    EXPECT_EQ(0, race.position(car));
    EXPECT_EQ(25, race.getPoints(car));
    EXPECT_EQ("1.2", race.getDriverName(car));
}

TEST(LeaderboardTest, SumsPointsPerDriverName) {
    std::list<Race> races;
    races.push_back(Race("Race 1", Order(kNico, kLewis, kSebastian)));
    races.push_back(Race("Race 2", Order(kSebastian, kLewis, kNico)));
    races.push_back(Race("Race 3", Order(kLewis, kNico, kSebastian)));
    Leaderboard leaderboard(races);
    std::map<std::string, int> results = leaderboard.driverResults();
    ASSERT_EQ(3u, results.size());
    EXPECT_EQ(25 + 15 + 18, results["Nico Rosberg"]);
    EXPECT_EQ(18 + 18 + 25, results["Lewis Hamilton"]);
    EXPECT_EQ(15 + 25 + 15, results["Sebastian Vettel"]);
}

TEST(LeaderboardTest, RanksByPointsDescending) {
    std::list<Race> races;
    races.push_back(Race("Race 1", Order(kNico, kLewis, kSebastian)));
    races.push_back(Race("Race 2", Order(kSebastian, kLewis, kNico)));
    races.push_back(Race("Race 3", Order(kLewis, kNico, kSebastian)));
    std::list<std::string> rankings = Leaderboard(races).driverRankings();
    std::list<std::string> expected;
    expected.push_back("Lewis Hamilton");
    expected.push_back("Nico Rosberg");
    expected.push_back("Sebastian Vettel");
    EXPECT_EQ(expected, rankings);
}

TEST(LeaderboardTest, TiesKeepAlphabeticalOrder) {
    Driver alice("Alice", "SE");
    Driver bob("Bob", "NO");
    Driver carol("Carol", "DK");
    std::list<Race> races;
    races.push_back(Race("Race 1", Order(bob, alice, carol)));
    races.push_back(Race("Race 2", Order(alice, bob, carol)));
    std::list<std::string> rankings = Leaderboard(races).driverRankings();
    std::list<std::string> expected;
    expected.push_back("Alice");
    expected.push_back("Bob");
    expected.push_back("Carol");
    EXPECT_EQ(expected, rankings);
    EXPECT_EQ(43, Leaderboard(races).driverResults()["Bob"]);
    EXPECT_EQ(30, Leaderboard(races).driverResults()["Carol"]);
}

TEST(LeaderboardTest, EmptyLeaderboardHasNoResults) {
    Leaderboard leaderboard((std::list<Race>()));
    EXPECT_TRUE(leaderboard.driverResults().empty());
    EXPECT_TRUE(leaderboard.driverRankings().empty());
}

}  // namespace
