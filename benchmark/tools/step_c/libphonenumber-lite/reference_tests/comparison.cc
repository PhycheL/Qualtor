#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include "phonenumbers/phonenumber.h"
#include "phonenumbers/phonenumber.pb.h"
#include "phonenumbers/phonemetadata.pb.h"

using namespace i18n::phonenumbers;

TEST(PhoneEquality, EachFieldPresenceValueAndSymmetry) {
  const std::vector<std::function<void(PhoneNumber&)> > setters = {
    [](PhoneNumber& p) { p.set_country_code(0); },
    [](PhoneNumber& p) { p.set_country_code(86); },
    [](PhoneNumber& p) { p.set_national_number(0); },
    [](PhoneNumber& p) { p.set_national_number(123456789012345ULL); },
    [](PhoneNumber& p) { p.set_extension(""); },
    [](PhoneNumber& p) { p.set_extension("001"); },
    [](PhoneNumber& p) { p.set_italian_leading_zero(false); },
    [](PhoneNumber& p) { p.set_italian_leading_zero(true); },
    [](PhoneNumber& p) { p.set_number_of_leading_zeros(1); },
    [](PhoneNumber& p) { p.set_number_of_leading_zeros(3); },
    [](PhoneNumber& p) { p.set_raw_input(""); },
    [](PhoneNumber& p) { p.set_raw_input("+1 555"); },
    [](PhoneNumber& p) { p.set_country_code_source(PhoneNumber::UNSPECIFIED); },
    [](PhoneNumber& p) { p.set_country_code_source(PhoneNumber::FROM_DEFAULT_COUNTRY); },
    [](PhoneNumber& p) { p.set_preferred_domestic_carrier_code(""); },
    [](PhoneNumber& p) { p.set_preferred_domestic_carrier_code("001"); }
  };
  PhoneNumber empty;
  EXPECT_TRUE(ExactlySameAs(empty, empty));
  for (const auto& set : setters) {
    PhoneNumber a, b;
    set(a);
    EXPECT_FALSE(ExactlySameAs(a, b));
    EXPECT_FALSE(ExactlySameAs(b, a));
    set(b);
    EXPECT_TRUE(ExactlySameAs(a, b));
    EXPECT_TRUE(ExactlySameAs(b, a));
  }
  for (std::size_t i = 0; i < setters.size(); i += 2) {
    PhoneNumber a, b;
    setters[i](a);
    setters[i + 1](b);
    EXPECT_FALSE(ExactlySameAs(a, b));
    EXPECT_FALSE(ExactlySameAs(b, a));
  }
}

TEST(PhoneDescriptionEquality, OptionalAndRepeatedFields) {
  PhoneNumberDesc empty;
  EXPECT_TRUE(ExactlySameAs(empty, empty));
  const std::vector<std::function<void(PhoneNumberDesc&)> > setters = {
    [](PhoneNumberDesc& p) { p.set_national_number_pattern(""); },
    [](PhoneNumberDesc& p) { p.set_national_number_pattern("[0-9]+"); },
    [](PhoneNumberDesc& p) { p.set_example_number(""); },
    [](PhoneNumberDesc& p) { p.set_example_number("123456"); },
    [](PhoneNumberDesc& p) { p.add_possible_length(0); },
    [](PhoneNumberDesc& p) { p.add_possible_length(7); },
    [](PhoneNumberDesc& p) { p.add_possible_length_local_only(0); },
    [](PhoneNumberDesc& p) { p.add_possible_length_local_only(6); }
  };
  for (const auto& set : setters) {
    PhoneNumberDesc a, b;
    set(a);
    EXPECT_FALSE(ExactlySameAs(a, b));
    EXPECT_FALSE(ExactlySameAs(b, a));
    set(b);
    EXPECT_TRUE(ExactlySameAs(a, b));
  }
  for (std::size_t i = 0; i < setters.size(); i += 2) {
    PhoneNumberDesc a, b;
    setters[i](a);
    setters[i + 1](b);
    EXPECT_FALSE(ExactlySameAs(a, b));
  }
  PhoneNumberDesc a, b;
  for (int n : {3, 7, 9}) { a.add_possible_length(n); b.add_possible_length(n); }
  for (int n : {2, 6}) { a.add_possible_length_local_only(n); b.add_possible_length_local_only(n); }
  EXPECT_TRUE(ExactlySameAs(a, b));
  b.set_possible_length(2, 8);
  EXPECT_FALSE(ExactlySameAs(a, b));
  b.set_possible_length(2, 9);
  b.set_possible_length_local_only(1, 5);
  EXPECT_FALSE(ExactlySameAs(a, b));
}
