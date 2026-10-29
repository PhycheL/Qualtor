#include <gtest/gtest.h>
#include "pngchunk_int.hpp"
#include "image.hpp"
#include "error.hpp"
#include "poc.h"
#include <zlib.h>
#include <string>
#include <vector>

using Exiv2::Internal::PngChunk;
namespace {
Exiv2::DataBuf buffer(const std::string& s) {
  return Exiv2::DataBuf(reinterpret_cast<const Exiv2::byte*>(s.data()), s.size());
}
std::string stringOf(const Exiv2::DataBuf& b) {
  return b.size_ ? std::string(reinterpret_cast<const char*>(b.pData_), b.size_) : std::string();
}
std::string compressed(const std::string& s) {
  uLongf n = compressBound(s.size());
  std::vector<unsigned char> b(n);
  if (compress2(b.data(), &n, reinterpret_cast<const Bytef*>(s.data()), s.size(), Z_BEST_COMPRESSION) != Z_OK)
    throw std::runtime_error("zlib compression failed");
  return std::string(reinterpret_cast<const char*>(b.data()), n);
}
std::string text(const std::string& key, const std::string& value) { return key + '\0' + value; }
void decodeImage(Exiv2::Image* image, const std::string& value) {
  PngChunk::decodeTXTChunk(image, buffer(value), PngChunk::tEXt_Chunk);
}
TEST(PngChunk, HeaderAndKeys) {
  const unsigned char data[] = {0,0,1,2,0,0,3,4};
  int width = 0, height = 0;
  PngChunk::decodeIHDRChunk(Exiv2::DataBuf(data, 8), &width, &height);
  EXPECT_EQ(258, width); EXPECT_EQ(772, height);
  for (std::string key : {std::string(), std::string("x"), std::string(79, 'a')}) {
    EXPECT_EQ(key, stringOf(PngChunk::keyTXTChunk(buffer(text(key, "value")))));
    EXPECT_EQ(key, stringOf(PngChunk::keyTXTChunk(buffer(std::string(8, 'h') + text(key, "value")), true)));
  }
  EXPECT_THROW(PngChunk::keyTXTChunk(buffer("")), Exiv2::Error);
  EXPECT_THROW(PngChunk::keyTXTChunk(buffer("unterminated")), Exiv2::Error);
  EXPECT_THROW(PngChunk::keyTXTChunk(buffer("12345678"), true), Exiv2::Error);
  EXPECT_THROW(PngChunk::keyTXTChunk(buffer("12345678key"), true), Exiv2::Error);
}
TEST(PngChunk, PlainAndCompressedText) {
  for (std::string value : {std::string(), std::string("hi"), std::string("a\0b", 3), std::string(4000, 'x')}) {
    EXPECT_EQ(value, stringOf(PngChunk::decodeTXTChunk(buffer(text("Comment", value)), PngChunk::tEXt_Chunk)));
    EXPECT_EQ(value, stringOf(PngChunk::decodeTXTChunk(buffer(text("Comment", std::string(1, '\0') + compressed(value))), PngChunk::zTXt_Chunk)));
    for (int flag = 0; flag <= 1; ++flag) {
      std::string payload = std::string(1, char(flag)) + '\0' + "en" + '\0' + "translated" + '\0'
                            + (flag ? compressed(value) : value);
      EXPECT_EQ(value, stringOf(PngChunk::decodeTXTChunk(buffer(text("Description", payload)), PngChunk::iTXt_Chunk)));
    }
  }
  for (std::string payload : {std::string(), std::string(1, '\1'), std::string("\0bad", 4)})
    EXPECT_THROW(PngChunk::decodeTXTChunk(buffer(text("key", payload)), PngChunk::zTXt_Chunk), Exiv2::Error);
  for (std::string payload : {std::string(), std::string(2, '\0'), std::string("\2\0\0\0", 4),
                              std::string("\1\1\0\0", 4), std::string("\1\0\0\0bad", 7)})
    EXPECT_THROW(PngChunk::decodeTXTChunk(buffer(text("key", payload)), PngChunk::iTXt_Chunk), Exiv2::Error);
  EXPECT_THROW(PngChunk::decodeTXTChunk(buffer(text("key", "value")), static_cast<PngChunk::TxtChunkType>(3)), Exiv2::Error);
}
TEST(PngChunk, EncodedLengthCrcAndMetadata) {
  for (Exiv2::MetadataId type : {Exiv2::mdComment, Exiv2::mdXmp, Exiv2::mdExif, Exiv2::mdIptc}) {
    for (std::string value : {std::string("a"), std::string("hello UTF-8 \xc3\xa9"), std::string(80, '\xff')}) {
      std::string chunk = PngChunk::makeMetadataChunk(value, type);
      ASSERT_GE(chunk.size(), 12u);
      const Exiv2::byte* bytes = reinterpret_cast<const Exiv2::byte*>(chunk.data());
      const uint32_t size = Exiv2::getULong(bytes, Exiv2::bigEndian);
      ASSERT_EQ(chunk.size() - 12, size);
      const uLong crc = crc32(crc32(0L, Z_NULL, 0), reinterpret_cast<const Bytef*>(chunk.data() + 4), size + 4);
      EXPECT_EQ(crc, Exiv2::getULong(bytes + 8 + size, Exiv2::bigEndian));
      const bool ascii = type == Exiv2::mdExif || type == Exiv2::mdIptc;
      EXPECT_EQ(ascii ? "zTXt" : "iTXt", chunk.substr(4, 4));
      std::string decoded = stringOf(PngChunk::decodeTXTChunk(buffer(chunk.substr(8, size)),
                                    ascii ? PngChunk::zTXt_Chunk : PngChunk::iTXt_Chunk));
      if (!ascii) EXPECT_EQ(value, decoded);
      else {
        EXPECT_EQ('\n', decoded[0]);
        EXPECT_NE(std::string::npos, decoded.find(type == Exiv2::mdExif ? "exif" : "iptc"));
        EXPECT_EQ('\n', decoded.back());
      }
    }
  }
  EXPECT_EQ("", PngChunk::makeMetadataChunk("ignored", Exiv2::mdIccProfile));
}
TEST(PngChunk, ImageContentAndMalformedRawProfiles) {
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  ASSERT_TRUE(image.get());
  decodeImage(image.get(), text("Comment", "ignored"));
  EXPECT_EQ("", image->comment());
  decodeImage(image.get(), text("Description", "first"));
  EXPECT_EQ("first", image->comment());
  decodeImage(image.get(), text("Description", "second"));
  EXPECT_EQ("first", image->comment());
  decodeImage(image.get(), text("XML:com.adobe.xmp", "junk<x>text</x>"));
  EXPECT_EQ("<x>text</x>", image->xmpPacket());
  decodeImage(image.get(), text("Raw profile type xmp", "\nxmp\n       3\n3c783e\n"));
  EXPECT_EQ("<x>", image->xmpPacket());
  for (std::string raw : {std::string("\nxmp\n0\n"), std::string("\nxmp\n"),
                          std::string("\nxmp\n9223372036854775808\n00")})
    EXPECT_NO_THROW(decodeImage(image.get(), text("Raw profile type xmp", raw)));
  EXPECT_THROW(decodeImage(image.get(), text("Raw profile type xmp", "\nxmp\n10\n00")), Exiv2::Error);
}
TEST(PngChunk, UpstreamIssue845) {
  EXPECT_THROW({
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(issue845, sizeof(issue845));
    image->readMetadata();
  }, Exiv2::Error);
}
}
