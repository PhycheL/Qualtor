#include <gtest/gtest.h>
#include <string>
#include <vector>
extern int environment_subject(int);
TEST(Environment, Subject) {
  EXPECT_EQ(1, environment_subject(2));
  EXPECT_EQ(6, environment_subject(4));
}
#ifdef HAVE_BOOST
#include <boost/any.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/version.hpp>
TEST(Environment, Boost) {
  boost::any value = std::string("cxx11");
  EXPECT_EQ("cxx11", boost::any_cast<std::string>(value));
  boost::gregorian::date date(2024, 2, 28);
  EXPECT_EQ(boost::gregorian::date(2024, 3, 1), date + boost::gregorian::days(2));
  EXPECT_EQ(date, boost::gregorian::from_simple_string("2024-02-28"));
#ifdef BANK_VERSION
  EXPECT_EQ(108300, BOOST_VERSION);
#endif
}
#endif
#ifdef HAVE_OPENSSL
#include <openssl/md5.h>
#include <openssl/crypto.h>
TEST(Environment, OpenSSL) {
  unsigned char digest[MD5_DIGEST_LENGTH];
  const std::string input = "Hello world";
  MD5(reinterpret_cast<const unsigned char*>(input.data()), input.size(), digest);
  const char* hex = "0123456789abcdef";
  std::string actual;
  for (unsigned i = 0; i < sizeof digest; ++i) {
    actual += hex[digest[i] >> 4]; actual += hex[digest[i] & 15];
  }
  EXPECT_EQ("3e25960a79dbc69b674cd4ec67a72c62", actual);
  EXPECT_EQ(OPENSSL_VERSION_NUMBER, OpenSSL_version_num());
}
#endif
#ifdef HAVE_ZLIB
#include <zlib.h>
TEST(Environment, Zlib) {
  const std::string input(10000, 'z');
  std::vector<unsigned char> compressed(compressBound(input.size()));
  uLongf length = compressed.size();
  ASSERT_EQ(Z_OK, compress(compressed.data(), &length,
                          reinterpret_cast<const Bytef*>(input.data()), input.size()));
  std::vector<unsigned char> restored(input.size());
  uLongf restored_length = restored.size();
  ASSERT_EQ(Z_OK, uncompress(restored.data(), &restored_length, compressed.data(), length));
  EXPECT_EQ(input, std::string(restored.begin(), restored.end()));
  EXPECT_STREQ(ZLIB_VERSION, zlibVersion());
#ifdef BANK_VERSION
  EXPECT_STREQ("1.3.1", zlibVersion());
#endif
}
#endif
#ifdef HAVE_PROTOBUF
#include "probe.pb.h"
#include <google/protobuf/arena.h>
TEST(Environment, Protobuf) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  google::protobuf::Arena arena;
  qualtor::Probe* message = google::protobuf::Arena::CreateMessage<qualtor::Probe>(&arena);
  (*message->mutable_children())["key"].set_name("value");
  message->set_label("round-trip");
  message->mutable_nested()->set_name("nested");
  qualtor::Probe parsed;
  ASSERT_TRUE(parsed.ParseFromString(message->SerializeAsString()));
  EXPECT_EQ("value", parsed.children().at("key").name());
  EXPECT_EQ("nested", parsed.nested().name());
  EXPECT_EQ(qualtor::Probe::kLabel, parsed.choice_case());
  const google::protobuf::FieldDescriptor* field = parsed.GetDescriptor()->FindFieldByName("label");
  ASSERT_NE(nullptr, field);
  EXPECT_EQ("round-trip", parsed.GetReflection()->GetString(parsed, field));
  EXPECT_FALSE(parsed.DebugString().empty()); // Links protobuf's std::string ABI symbol.
}
#endif
#ifdef HAVE_QT
#include "relay.h"
#include <QDate>
#include <QRegularExpression>
TEST(Environment, Qt) {
  Relay relay;
  int observed = 0;
  QObject::connect(&relay, &Relay::changed, [&](int value) { observed = value; });
  relay.send(42);
  EXPECT_EQ(42, observed);
  EXPECT_EQ(QDate(2024, 3, 1), QDate(2024, 2, 28).addDays(2));
  EXPECT_TRUE(QRegularExpression("^[a-z]+$").match("qualtor").hasMatch());
  EXPECT_STREQ(QT_VERSION_STR, qVersion());
#ifdef BANK_VERSION
  EXPECT_STREQ("5.15.15", qVersion());
#endif
}
#endif
