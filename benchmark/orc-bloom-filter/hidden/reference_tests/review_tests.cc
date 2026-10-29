#include <gtest/gtest.h>
#include "BloomFilter.hh"
#include <cstring>

namespace orc {
int32_t optimalNumOfHashFunctions(uint64_t, uint64_t);
int32_t optimalNumOfBits(uint64_t, double);
}

TEST(Review, BitSetMergeAndSizeErrors) {
  orc::BitSet a(128), b(128), c(192);
  a.set(0); b.set(1); b.set(64); b.set(127);
  a.merge(b);
  for (unsigned i = 0; i < 128; ++i)
    EXPECT_EQ(i == 0 || i == 1 || i == 64 || i == 127, a.get(i));
  try { a.merge(c); FAIL(); }
  catch (const std::logic_error& e) {
    EXPECT_STREQ("BitSet must be of equal length (2 != 3)", e.what());
  }
  orc::BitSet empty(0);
  EXPECT_NO_THROW(empty.merge(empty));
}

TEST(Review, OptimalSizesAndConstructorChecks) {
  EXPECT_EQ(1, orc::optimalNumOfHashFunctions(100, 1));
  EXPECT_EQ(7, orc::optimalNumOfHashFunctions(10, 100));
  EXPECT_EQ(69, orc::optimalNumOfHashFunctions(1, 100));
  orc::BloomFilterImpl f(10, .01);
  EXPECT_EQ(128u, f.getBitSize());
  EXPECT_EQ(9, f.getNumHashFunctions());
  EXPECT_THROW(orc::BloomFilterImpl(0, .05), std::logic_error);
  EXPECT_THROW(orc::BloomFilterImpl(1, 0), std::logic_error);
  EXPECT_THROW(orc::BloomFilterImpl(1, 1), std::logic_error);
  EXPECT_THROW(orc::BloomFilterImpl(1, -.1), std::logic_error);
  EXPECT_THROW(orc::BloomFilterImpl(1, 1.1), std::logic_error);
}

static orc::proto::BloomFilter encoded(unsigned hashes, std::initializer_list<uint64_t> words) {
  orc::proto::BloomFilter p;
  p.set_numhashfunctions(hashes);
  std::string bytes;
  for (uint64_t word : words)
    for (unsigned shift = 0; shift < 64; shift += 8)
      bytes.push_back(static_cast<char>(word >> shift));
  p.set_utf8bitset(bytes);
  return p;
}

TEST(Review, MergeSerializedBitsWithoutSignedHashArithmetic) {
  orc::BloomFilterImpl a(encoded(2, {1, 0})), b(encoded(2, {2, uint64_t(1) << 63}));
  a.merge(b);
  orc::proto::BloomFilter actual;
  orc::BloomFilterUTF8Utils::serialize(a, actual);
  EXPECT_EQ(encoded(2, {3, uint64_t(1) << 63}).SerializeAsString(), actual.SerializeAsString());
  EXPECT_THROW(a.merge(orc::BloomFilterImpl(encoded(3, {1, 0}))), std::logic_error);
  EXPECT_THROW(a.merge(orc::BloomFilterImpl(encoded(2, {1}))), std::logic_error);
  auto bad = encoded(1, {0});
  bad.set_utf8bitset("abc");
  EXPECT_THROW(orc::BloomFilterImpl{bad}, std::logic_error);
}
