#include <gtest/gtest.h>
#include "pngchunk_int.hpp"
#include "image.hpp"
#include "error.hpp"
#include "exif.hpp"
#include "iptc.hpp"
#include "jpgimage.hpp"
#include <zlib.h>
#include <iomanip>
#include <functional>
#include <sstream>
#include <vector>

using Exiv2::Internal::PngChunk;
namespace {
Exiv2::DataBuf buf(const std::string& s) {
  return Exiv2::DataBuf(reinterpret_cast<const Exiv2::byte*>(s.data()), s.size());
}
std::string bytes(const Exiv2::DataBuf& b) {
  return b.size_ ? std::string(reinterpret_cast<const char*>(b.pData_), b.size_) : std::string();
}
std::string rawProfile(const std::string& data, const std::string& kind) {
  std::ostringstream s;
  s << '\n' << kind << '\n' << std::setw(8) << data.size();
  const char digits[] = "0123456789abcdef";
  for (size_t i = 0; i < data.size(); ++i) {
    if (i % 36 == 0) s << '\n';
    unsigned char c = static_cast<unsigned char>(data[i]);
    s << digits[c / 16] << digits[c % 16];
  }
  return s.str() + '\n';
}
void textToImage(Exiv2::Image* image, const std::string& key, const std::string& raw) {
  PngChunk::decodeTXTChunk(image, buf(key + '\0' + raw), PngChunk::tEXt_Chunk);
}
std::string rawText(const std::string& chunk) {
  const uint32_t n = Exiv2::getULong(reinterpret_cast<const Exiv2::byte*>(chunk.data()), Exiv2::bigEndian);
  return bytes(PngChunk::decodeTXTChunk(buf(chunk.substr(8, n)),
    chunk.substr(4, 4) == "zTXt" ? PngChunk::zTXt_Chunk : PngChunk::iTXt_Chunk));
}
TEST(PngMetadata, ExactRawProfileEncoding) {
  std::string all;
  for (int i = 0; i <= 255; ++i) all.push_back(static_cast<char>(i));
  for (size_t n : {size_t(1), size_t(35), size_t(36), size_t(37), size_t(256)}) {
    const std::string value = all.substr(0, n);
    EXPECT_EQ(rawProfile(value, "exif"), rawText(PngChunk::makeMetadataChunk(value, Exiv2::mdExif)));
    EXPECT_EQ(rawProfile(value, "iptc"), rawText(PngChunk::makeMetadataChunk(value, Exiv2::mdIptc)));
  }
}
TEST(PngMetadata, ExifHeaderScanDecodeAndRetainExisting) {
  Exiv2::ExifData metadata;
  metadata["Exif.Image.Make"] = "Qualtor";
  Exiv2::Blob encoded;
  Exiv2::ExifParser::encode(encoded, Exiv2::littleEndian, metadata);
  ASSERT_FALSE(encoded.empty());
  std::string tiff(encoded.begin(), encoded.end());
  std::string exif = std::string("Exif\0\0", 6) + tiff;
  for (std::string key : {"Raw profile type exif", "Raw profile type APP1"}) {
    for (std::string prefix : {std::string(), std::string("junk")}) {
      Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
      textToImage(image.get(), key, rawProfile(prefix + exif, "exif"));
      EXPECT_EQ("Qualtor", image->exifData()["Exif.Image.Make"].toString());
      EXPECT_EQ(Exiv2::littleEndian, image->byteOrder());
      image->exifData()["Exif.Image.Make"] = "retained";
      textToImage(image.get(), key, rawProfile(exif, "exif"));
      EXPECT_EQ("retained", image->exifData()["Exif.Image.Make"].toString());
    }
  }
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  textToImage(image.get(), "Raw profile type exif", rawProfile("no exif header in this payload", "exif"));
  EXPECT_TRUE(image->exifData().empty());
  textToImage(image.get(), "Raw profile type exif", rawProfile("", "exif"));
  EXPECT_TRUE(image->exifData().empty());
}
TEST(PngMetadata, IptcRawAndPhotoshopResource) {
  for (std::string value : {std::string("even"), std::string("odd"), std::string(100, 'x')}) {
    Exiv2::IptcData iptc;
    iptc["Iptc.Application2.ObjectName"] = value;
    const std::string payload = bytes(Exiv2::IptcParser::encode(iptc));
    const Exiv2::byte empty = 0;
    const std::string irb = bytes(Exiv2::Photoshop::setIptcIrb(&empty, 0, iptc));
    ASSERT_FALSE(payload.empty()); ASSERT_FALSE(irb.empty());
    for (const std::string& packed : {payload, irb}) {
      Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
      textToImage(image.get(), "Raw profile type iptc", rawProfile(packed, "iptc"));
      EXPECT_EQ(value, image->iptcData()["Iptc.Application2.ObjectName"].toString());
      image->iptcData()["Iptc.Application2.ObjectName"] = "retained";
      textToImage(image.get(), "Raw profile type iptc", rawProfile(packed, "iptc"));
      EXPECT_EQ("retained", image->iptcData()["Iptc.Application2.ObjectName"].toString());
    }
  }
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  textToImage(image.get(), "Raw profile type iptc", rawProfile("", "iptc"));
  EXPECT_TRUE(image->iptcData().empty());
  textToImage(image.get(), "Raw profile type iptc", rawProfile("nonsense", "iptc"));
  EXPECT_TRUE(image->iptcData().empty());
}
TEST(PngMetadata, RawProfileWhitespaceAndHexBoundaries) {
  for (std::string raw : {std::string("\nxmp\n       3\n3c783e\n"),
                          std::string("\nxmp\n\n 3\n 3 c=7 8=3 e\n")}) {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
    textToImage(image.get(), "Raw profile type xmp", raw);
    EXPECT_EQ("<x>", image->xmpPacket());
  }
  for (std::string raw : {std::string(""), std::string("x"), std::string("no newline"), std::string("\nxmp\n"),
                          std::string("\nxmp\n0\n"), std::string("\nxmp\n3"), std::string("\nxmp\n3\n"),
                          std::string("\nxmp\n3\n00\0xxx", 13)}) {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
    EXPECT_NO_THROW(textToImage(image.get(), "Raw profile type xmp", raw));
    EXPECT_TRUE(image->xmpPacket().empty());
  }
  // An encoded length cannot exceed the remaining two hex digits per byte.
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  EXPECT_THROW(textToImage(image.get(), "Raw profile type xmp", "\nxmp\n4\n00"), Exiv2::Error);
  EXPECT_THROW(textToImage(image.get(), "Raw profile type xmp", "\nxmp\n3\nzzzzzzzz"), Exiv2::Error);
}
TEST(PngMetadata, XmpAndEmptyDescription) {
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  textToImage(image.get(), "Description", "");
  EXPECT_TRUE(image->comment().empty());
  for (std::string packet : {"<x>", "plain", "junk<x>"}) {
    textToImage(image.get(), "XML:com.adobe.xmp", packet);
    EXPECT_EQ(packet == "junk<x>" ? "<x>" : packet, image->xmpPacket());
    textToImage(image.get(), "Raw profile type xmp", rawProfile(packet, "xmp"));
    EXPECT_EQ(packet == "junk<x>" ? "<x>" : packet, image->xmpPacket());
  }
}
TEST(PngMetadata, ZlibExpansionLimit) {
  const std::string maximum(131072, 'z');
  EXPECT_EQ(maximum, rawText(PngChunk::makeMetadataChunk(maximum, Exiv2::mdComment)));
  EXPECT_THROW(rawText(PngChunk::makeMetadataChunk(std::string(131073, 'z'), Exiv2::mdComment)), Exiv2::Error);
  std::string random;
  uint32_t state = 1;
  for (unsigned i = 0; i < 140000; ++i) {
    state = state * 1664525u + 1013904223u;
    random.push_back(static_cast<char>(state >> 24));
  }
  EXPECT_EQ(random, rawText(PngChunk::makeMetadataChunk(random, Exiv2::mdComment)));
}

void errorCode(const std::function<void()>& run, int expected) {
  try { run(); FAIL() << "expected Exiv2::Error"; }
  catch (const Exiv2::Error& error) { EXPECT_EQ(expected, error.code()); }
}
TEST(PngMetadata, MinimalTextAndLanguageBounds) {
  for (std::string key : {std::string(), std::string("x"), std::string("long-key")}) {
    const std::string chunk = PngChunk::makeMetadataChunk("hello", Exiv2::mdComment);
    // Reuse only the compressed stream after Description + flag/method/lang/key.
    const std::string body = chunk.substr(8, chunk.size() - 12);
    const std::string stream = body.substr(std::string("Description").size() + 5);
    EXPECT_EQ("hello", bytes(PngChunk::decodeTXTChunk(buf(key + std::string(2, '\0') + stream), PngChunk::zTXt_Chunk)));
    errorCode([&] { PngChunk::decodeTXTChunk(buf(key + std::string(2, '\0')), PngChunk::zTXt_Chunk); },
              Exiv2::kerFailedToReadImageData);
    for (std::string language : {std::string(), std::string(40, 'e')}) {
      std::string payload = key + std::string(3, '\0') + language + '\0' + "translated" + '\0' + "value";
      EXPECT_EQ("value", bytes(PngChunk::decodeTXTChunk(buf(payload), PngChunk::iTXt_Chunk)));
    }
  }
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  const std::string shortRaw = std::string("\nxmp\n10\n00") + '\0' + "junk";
  errorCode([&] { textToImage(image.get(), "Raw profile type xmp", shortRaw); }, Exiv2::kerCorruptedMetadata);
  errorCode([&] { textToImage(image.get(), "Raw profile type xmp", "\nxmp\n9223372036854775807\n00"); },
            Exiv2::kerCorruptedMetadata);
}

std::string resource(unsigned id, const std::string& data) {
  std::string result("8BIM");
  result += static_cast<char>(id >> 8); result += static_cast<char>(id);
  result += std::string(2, '\0');
  for (int shift : {24, 16, 8, 0}) result += static_cast<char>(data.size() >> shift);
  result += data;
  if (data.size() % 2) result += '\0';
  return result;
}
TEST(PngMetadata, MultipleResourcesAndNonIptcData) {
  Exiv2::IptcData name, city, fake;
  name["Iptc.Application2.ObjectName"] = "good";
  city["Iptc.Application2.City"] = "A distant city";
  fake["Iptc.Application2.ObjectName"] = "fake";
  const std::string first = resource(0x0404, bytes(Exiv2::IptcParser::encode(name)));
  const std::string second = resource(0x0404, bytes(Exiv2::IptcParser::encode(city)));
  const std::string unrelated = resource(0x0400, bytes(Exiv2::IptcParser::encode(fake)));
  for (const std::string& packed : {first + second, unrelated + first + second}) {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
    textToImage(image.get(), "Raw profile type iptc", rawProfile(packed, "iptc"));
    EXPECT_EQ("good", image->iptcData()["Iptc.Application2.ObjectName"].toString());
    EXPECT_EQ("A distant city", image->iptcData()["Iptc.Application2.City"].toString());
    EXPECT_EQ(2, image->iptcData().count());
  }
}

std::vector<std::string> messages;
void capture(int, const char* message) { messages.push_back(message); }
struct Capture {
  Exiv2::LogMsg::Handler handler = Exiv2::LogMsg::handler();
  Exiv2::LogMsg::Level level = Exiv2::LogMsg::level();
  Capture() { messages.clear(); Exiv2::LogMsg::setHandler(capture); Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn); }
  ~Capture() { Exiv2::LogMsg::setHandler(handler); Exiv2::LogMsg::setLevel(level); }
};
TEST(PngMetadata, EmptyMetadataAndLogCallbacks) {
  Capture log;
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::create(Exiv2::ImageType::png);
  textToImage(image.get(), "Raw profile type exif", rawProfile("", "exif"));
  EXPECT_TRUE(messages.empty());
  textToImage(image.get(), "Raw profile type exif", rawProfile(std::string("Exif\0\0", 6), "exif"));
  ASSERT_EQ(1u, messages.size());
  EXPECT_EQ("Failed to decode Exif metadata.\n", messages[0]);
  image->xmpPacket() = "retained";
  textToImage(image.get(), "XML:com.adobe.xmp", "");
  EXPECT_EQ("retained", image->xmpPacket());
  textToImage(image.get(), "Raw profile type xmp", rawProfile("", "xmp"));
  EXPECT_EQ("retained", image->xmpPacket());
}
}
