#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <gzip/compress.hpp>
#include <gzip/decompress.hpp>
#include <gzip/utils.hpp>

TEST(Gzip, RoundTripAndFormat) {
  for (std::size_t size : {0, 1, 2, 100, 4096}) {
    std::string input;
    for (std::size_t i = 0; i < size; ++i) input.push_back(static_cast<char>(i % 256));
    for (int level = -1; level <= 9; ++level) {
      const std::string encoded = gzip::compress(input.data(), input.size(), level);
      ASSERT_GT(encoded.size(), 2u);
      EXPECT_EQ(0x1f, static_cast<unsigned char>(encoded[0]));
      EXPECT_EQ(0x8b, static_cast<unsigned char>(encoded[1]));
      EXPECT_TRUE(gzip::is_compressed(encoded.data(), encoded.size()));
      EXPECT_EQ(input, gzip::decompress(encoded.data(), encoded.size()));
    }
  }
}

TEST(Gzip, HeaderDetectionBoundaries) {
  EXPECT_FALSE(gzip::is_compressed("", 0));
  EXPECT_FALSE(gzip::is_compressed("x", 1));
  EXPECT_FALSE(gzip::is_compressed("\x1f\x8b", 2));
  EXPECT_TRUE(gzip::is_compressed("\x1f\x8b\0", 3));
  EXPECT_FALSE(gzip::is_compressed("\x1f\x8c\0", 3));
  EXPECT_FALSE(gzip::is_compressed("\x1e\x8b\0", 3));
  for (unsigned char byte : {0x9c, 0x01, 0xda, 0x5e}) {
    const char header[] = {'x', static_cast<char>(byte), 0};
    EXPECT_TRUE(gzip::is_compressed(header, 3));
  }
  EXPECT_FALSE(gzip::is_compressed("\x78\x02\0", 3));
}

TEST(Gzip, BoundedErrors) {
  std::string output;
  gzip::Compressor limited(Z_DEFAULT_COMPRESSION, 3);
  EXPECT_NO_THROW(limited.compress(output, "abc", 3));
  EXPECT_THROW(limited.compress(output, "abcd", 4), std::runtime_error);
  EXPECT_THROW(gzip::compress("abc", 3, 99), std::runtime_error);
  EXPECT_THROW(gzip::compress("abc", std::uint64_t(std::numeric_limits<unsigned int>::max()) + 1), std::runtime_error);
  EXPECT_THROW(gzip::decompress("abc", std::uint64_t(std::numeric_limits<unsigned int>::max())), std::runtime_error);
  EXPECT_THROW(gzip::decompress("not compressed", 14), std::runtime_error);
  const std::string encoded = gzip::compress(std::string(10000, 'a').data(), 10000);
  gzip::Decompressor small(100);
  EXPECT_THROW(small.decompress(output, encoded.data(), encoded.size()), std::runtime_error);
  EXPECT_THROW(small.decompress(output, encoded.data(), 101), std::runtime_error);
}
