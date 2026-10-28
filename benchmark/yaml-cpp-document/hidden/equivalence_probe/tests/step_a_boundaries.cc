#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
TEST(YamlBoundary, TruncatedFlowDocuments) {
  for (const char* text : {"[", "[1", "[1,", "{", "{a", "{a:", "[a: ", "[a: b", "{a: b"}) {
    EXPECT_THROW(YAML::Load(text),YAML::ParserException) << text;
  }
}
TEST(YamlBoundary, UnknownAndEmptyAnchor) {
  EXPECT_THROW(YAML::Load("*missing"),YAML::ParserException);
  EXPECT_THROW(YAML::Load("& "),YAML::ParserException);
}
#include "scanner.h"
#include "singledocparser.h"
#include "directives.h"
#include "mock_event_handler.h"
#include <sstream>
TEST(YamlBoundary, ScannerConsumedByCallback) {
  // SingleDocParser accepts a caller-owned Scanner. Consume remaining tokens
  // during the scalar callback; original HandleDocument reports ParserException.
  for (const char* text : {"- a", "a: b"}) {
    std::istringstream input(text);
    YAML::Scanner scanner(input);
    YAML::Directives directives;
    YAML::SingleDocParser parser(scanner,directives);
    testing::NiceMock<YAML::MockEventHandler> handler;
    ON_CALL(handler,OnScalar(testing::_,testing::_,testing::_,testing::_)).WillByDefault(
      testing::Invoke([&](const YAML::Mark&,const std::string&,YAML::anchor_t,const std::string&) {
        while(!scanner.empty()) scanner.pop();
      }));
    EXPECT_THROW(parser.HandleDocument(handler),YAML::ParserException);
  }
}
#include "token.h"
TEST(YamlBoundary, CallerSuppliedEmptyAnchorToken) {
  std::istringstream input("&a x");
  YAML::Scanner scanner(input);
  ASSERT_EQ(YAML::Token::ANCHOR,scanner.peek().type);
  // Scanner exposes a mutable token reference; empty anchor is handled by
  // RegisterAnchor's explicit NullAnchor branch without undefined behavior.
  scanner.peek().value.clear();
  YAML::Directives directives;
  YAML::SingleDocParser parser(scanner,directives);
  testing::NiceMock<YAML::MockEventHandler> handler;
  EXPECT_CALL(handler,OnScalar(testing::_,testing::_,YAML::NullAnchor,"x")).Times(1);
  EXPECT_NO_THROW(parser.HandleDocument(handler));
}
