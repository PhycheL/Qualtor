#include <gtest/gtest.h>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <limits>
#include <vector>
extern "C" {
#include "tiffiop.h"
}

namespace {
int diagnosticCount = 0;
void countError(const char*, const char*, va_list) { ++diagnosticCount; }
struct Memory {
  std::vector<unsigned char> bytes;
  toff_t pos = 0;
  static tmsize_t read(thandle_t h, void* dst, tmsize_t n) {
    Memory& m = *static_cast<Memory*>(h);
    if (n < 0 || m.pos >= m.bytes.size()) return 0;
    n = std::min<tmsize_t>(n, m.bytes.size() - m.pos);
    std::memcpy(dst, m.bytes.data() + m.pos, n); m.pos += n; return n;
  }
  static tmsize_t write(thandle_t h, void* src, tmsize_t n) {
    Memory& m = *static_cast<Memory*>(h);
    if (n < 0 || m.pos + n > 1048576) return 0;
    m.bytes.resize(std::max<size_t>(m.bytes.size(), m.pos + n));
    std::memcpy(m.bytes.data() + m.pos, src, n); m.pos += n; return n;
  }
  static toff_t seek(thandle_t h, toff_t off, int mode) {
    Memory& m = *static_cast<Memory*>(h);
    m.pos = (mode == SEEK_SET ? 0 : mode == SEEK_CUR ? m.pos : m.bytes.size()) + off;
    return m.pos;
  }
  static int close(thandle_t) { return 0; }
  static toff_t size(thandle_t h) { return static_cast<Memory*>(h)->bytes.size(); }
  static int map(thandle_t, void**, toff_t*) { return 0; }
  static void unmap(thandle_t, void*, toff_t) {}
};
class Strips : public ::testing::Test {
 protected:
  Memory memory;
  TIFF* tif = nullptr;
  TIFFErrorHandler oldHandler = nullptr;
  void SetUp() override {
    oldHandler = TIFFSetErrorHandler(countError);
    diagnosticCount = 0;
    tif = TIFFClientOpen("memory", "w", &memory, Memory::read, Memory::write,
                         Memory::seek, Memory::close, Memory::size, Memory::map, Memory::unmap);
    ASSERT_NE(nullptr, tif);
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 11u);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 9u);
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 4u);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  }
  void TearDown() override {
    if (tif) TIFFClose(tif);
    TIFFSetErrorHandler(oldHandler);
  }
};
TEST_F(Strips, ComputeAndCount) {
  EXPECT_EQ(3u, TIFFNumberOfStrips(tif));
  for (uint32 row : {0u, 3u, 4u, 8u, 12u})
    EXPECT_EQ(row / 4, TIFFComputeStrip(tif, row, 0));
  tif->tif_dir.td_stripsperimage = 3;
  tif->tif_dir.td_planarconfig = PLANARCONFIG_SEPARATE;
  EXPECT_EQ(9u, TIFFNumberOfStrips(tif));
  EXPECT_EQ(8u, TIFFComputeStrip(tif, 8, 2));
  const int before = diagnosticCount;
  EXPECT_EQ(0u, TIFFComputeStrip(tif, 8, 3));
  EXPECT_EQ(0u, TIFFComputeStrip(tif, 8, 4));
  EXPECT_EQ(before + 2, diagnosticCount);
  tif->tif_dir.td_rowsperstrip = static_cast<uint32>(-1);
  EXPECT_EQ(3u, TIFFNumberOfStrips(tif));
  tif->tif_dir.td_nstrips = 7;  // ChopUpSingleUncompressedStrip may change this cache.
  EXPECT_EQ(7u, TIFFNumberOfStrips(tif));
  tif->tif_dir.td_nstrips = 0;
}
TEST_F(Strips, SizesAndDefaultRows) {
  EXPECT_EQ(33u, TIFFScanlineSize64(tif));
  EXPECT_EQ(33, TIFFScanlineSize(tif));
  EXPECT_EQ(132u, TIFFStripSize64(tif));
  EXPECT_EQ(132, TIFFStripSize(tif));
  EXPECT_EQ(297u, TIFFVStripSize64(tif, static_cast<uint32>(-1)));
  EXPECT_EQ(66, TIFFVStripSize(tif, 2));
  EXPECT_EQ(0u, TIFFVStripSize64(tif, 0));
  EXPECT_EQ(33u, TIFFRasterScanlineSize64(tif));
  EXPECT_EQ(33, TIFFRasterScanlineSize(tif));
  EXPECT_EQ(8192u / 33, TIFFDefaultStripSize(tif, 0));
  EXPECT_EQ(17u, TIFFDefaultStripSize(tif, 17));
  EXPECT_EQ(1u, TIFFDefaultStripSize(tif, 1));
  EXPECT_EQ(8192u / 33, TIFFDefaultStripSize(tif, static_cast<uint32>(-1)));
  tif->tif_dir.td_rowsperstrip = 12;
  EXPECT_EQ(297u, TIFFStripSize64(tif));
  tif->tif_dir.td_planarconfig = PLANARCONFIG_SEPARATE;
  tif->tif_dir.td_bitspersample = 1;
  EXPECT_EQ(2u, TIFFScanlineSize64(tif));
  EXPECT_EQ(6u, TIFFRasterScanlineSize64(tif));
  tif->tif_dir.td_planarconfig = PLANARCONFIG_CONTIG;
  EXPECT_EQ(5u, TIFFScanlineSize64(tif));
  EXPECT_EQ(5u, TIFFRasterScanlineSize64(tif));
  tif->tif_dir.td_imagewidth = 0;
  const int before = diagnosticCount;
  EXPECT_EQ(0u, TIFFScanlineSize64(tif));
  EXPECT_EQ(8192u, TIFFDefaultStripSize(tif, 0));
  EXPECT_EQ(before + 2, diagnosticCount);
  tif->tif_dir.td_imagewidth = 100000;
  tif->tif_dir.td_bitspersample = 8;
  EXPECT_EQ(1u, TIFFDefaultStripSize(tif, 0));
}
TEST_F(Strips, YcbcrAndInvalidSampling) {
  tif->tif_dir.td_photometric = PHOTOMETRIC_YCBCR;
  for (uint16 h : {1, 2, 4}) for (uint16 v : {1, 2, 4}) {
    tif->tif_dir.td_ycbcrsubsampling[0] = h;
    tif->tif_dir.td_ycbcrsubsampling[1] = v;
    const uint64 row = ((11u + h - 1) / h) * (h * v + 2);
    EXPECT_EQ(row / v, TIFFScanlineSize64(tif));
    EXPECT_EQ(row * ((9u + v - 1) / v), TIFFVStripSize64(tif, 9));
  }
  for (uint16 bad : {0, 3, 5}) {
    const int before = diagnosticCount;
    tif->tif_dir.td_ycbcrsubsampling[0] = bad;
    EXPECT_EQ(0u, TIFFScanlineSize64(tif));
    EXPECT_EQ(0u, TIFFVStripSize64(tif, 2));
    tif->tif_dir.td_ycbcrsubsampling[0] = 2;
    tif->tif_dir.td_ycbcrsubsampling[1] = bad;
    EXPECT_EQ(0u, TIFFScanlineSize64(tif));
    EXPECT_EQ(0u, TIFFVStripSize64(tif, 2));
    EXPECT_EQ(before + 4, diagnosticCount);
  }
  tif->tif_dir.td_samplesperpixel = 1;
  const int before = diagnosticCount;
  EXPECT_EQ(0u, TIFFVStripSize64(tif, 2));
  EXPECT_EQ(before + 1, diagnosticCount);
}
TEST_F(Strips, RawByteCounts) {
  uint64 counts[] = {1, 42, 0, std::numeric_limits<uint64>::max()};
  tif->tif_dir.td_stripbytecount = counts;
  EXPECT_EQ(1u, TIFFRawStripSize64(tif, 0));
  EXPECT_EQ(1, TIFFRawStripSize(tif, 0));
  EXPECT_EQ(42, TIFFRawStripSize(tif, 1));
  const int before = diagnosticCount;
  EXPECT_EQ(std::numeric_limits<uint64>::max(), TIFFRawStripSize64(tif, 2));
  EXPECT_EQ(-1, TIFFRawStripSize(tif, 2));
  EXPECT_EQ(-1, TIFFRawStripSize(tif, 3));
  EXPECT_EQ(before + 2, diagnosticCount);
  tif->tif_dir.td_stripbytecount = nullptr;
}
}
