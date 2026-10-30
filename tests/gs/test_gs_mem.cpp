// GS local memory: swizzle tables against the GS User's Manual's literal tables, page/block geometry, aliasing
// between formats, and image transfers (BITBLTBUF/TRXPOS/TRXREG/TRXDIR + IMAGE/HWREG) in both directions for every
// PSM the game uses (docs/ANALYSIS/14 §5).
#include "gs_test_util.h"

#include <random>
#include <set>

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;

namespace {

// GS User's Manual column tables (one block; values are word / halfword / byte / nibble indices inside the block).
constexpr u8 kLit32[8][8] = {
    {0, 1, 4, 5, 8, 9, 12, 13},     {2, 3, 6, 7, 10, 11, 14, 15},   {16, 17, 20, 21, 24, 25, 28, 29},
    {18, 19, 22, 23, 26, 27, 30, 31}, {32, 33, 36, 37, 40, 41, 44, 45}, {34, 35, 38, 39, 42, 43, 46, 47},
    {48, 49, 52, 53, 56, 57, 60, 61}, {50, 51, 54, 55, 58, 59, 62, 63},
};
constexpr u8 kLit16[2][16] = {
    {0, 2, 8, 10, 16, 18, 24, 26, 1, 3, 9, 11, 17, 19, 25, 27},
    {4, 6, 12, 14, 20, 22, 28, 30, 5, 7, 13, 15, 21, 23, 29, 31},
};
constexpr u8 kLit8[8][16] = { // columns 0 and 1; columns 2 and 3 are the same + 128
    {0, 4, 16, 20, 32, 36, 48, 52, 2, 6, 18, 22, 34, 38, 50, 54},
    {8, 12, 24, 28, 40, 44, 56, 60, 10, 14, 26, 30, 42, 46, 58, 62},
    {33, 37, 49, 53, 1, 5, 17, 21, 35, 39, 51, 55, 3, 7, 19, 23},
    {41, 45, 57, 61, 9, 13, 25, 29, 43, 47, 59, 63, 11, 15, 27, 31},
    {96, 100, 112, 116, 64, 68, 80, 84, 98, 102, 114, 118, 66, 70, 82, 86},
    {104, 108, 120, 124, 72, 76, 88, 92, 106, 110, 122, 126, 74, 78, 90, 94},
    {65, 69, 81, 85, 97, 101, 113, 117, 67, 71, 83, 87, 99, 103, 115, 119},
    {73, 77, 89, 93, 105, 109, 121, 125, 75, 79, 91, 95, 107, 111, 123, 127},
};
constexpr u16 kLit4[8][32] = { // columns 0 and 1; columns 2 and 3 are the same + 256
    {0, 8, 32, 40, 64, 72, 96, 104, 2, 10, 34, 42, 66, 74, 98, 106, 4, 12, 36, 44, 68, 76, 100, 108, 6, 14, 38, 46, 70, 78, 102, 110},
    {16, 24, 48, 56, 80, 88, 112, 120, 18, 26, 50, 58, 82, 90, 114, 122, 20, 28, 52, 60, 84, 92, 116, 124, 22, 30, 54, 62, 86, 94, 118, 126},
    {65, 73, 97, 105, 1, 9, 33, 41, 67, 75, 99, 107, 3, 11, 35, 43, 69, 77, 101, 109, 5, 13, 37, 45, 71, 79, 103, 111, 7, 15, 39, 47},
    {81, 89, 113, 121, 17, 25, 49, 57, 83, 91, 115, 123, 19, 27, 51, 59, 85, 93, 117, 125, 21, 29, 53, 61, 87, 95, 119, 127, 23, 31, 55, 63},
    {192, 200, 224, 232, 128, 136, 160, 168, 194, 202, 226, 234, 130, 138, 162, 170, 196, 204, 228, 236, 132, 140, 164, 172, 198, 206, 230, 238, 134, 142, 166, 174},
    {208, 216, 240, 248, 144, 152, 176, 184, 210, 218, 242, 250, 146, 154, 178, 186, 212, 220, 244, 252, 148, 156, 180, 188, 214, 222, 246, 254, 150, 158, 182, 190},
    {129, 137, 161, 169, 193, 201, 225, 233, 131, 139, 163, 171, 195, 203, 227, 235, 133, 141, 165, 173, 197, 205, 229, 237, 135, 143, 167, 175, 199, 207, 231, 239},
    {145, 153, 177, 185, 209, 217, 241, 249, 147, 155, 179, 187, 211, 219, 243, 251, 149, 157, 181, 189, 213, 221, 245, 253, 151, 159, 183, 191, 215, 223, 247, 255},
};

constexpr u32 kAllPsm[] = {0x00, 0x01, 0x02, 0x0A, 0x13, 0x14, 0x1B, 0x24, 0x2C, 0x30, 0x31, 0x32, 0x3A};

u32 value_mask(u32 psm) { return psm_bits(psm) >= 32 ? 0xFFFFFFFFu : (1u << psm_bits(psm)) - 1u; }

// Pack pixel values the way host <-> local transfers carry them (little-endian bit stream, psm_bits per pixel).
std::vector<u8> pack(const std::vector<u32>& px, u32 bpp) {
    std::vector<u8> out((px.size() * bpp + 7) / 8, 0);
    std::size_t bit = 0;
    for (u32 v : px) {
        for (u32 b = 0; b < bpp; ++b, ++bit)
            if ((v >> b) & 1u) out[bit / 8] = static_cast<u8>(out[bit / 8] | (1u << (bit % 8)));
    }
    return out;
}

void upload(Fixture& f, u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 w, u32 h, const std::vector<u8>& bytes) {
    GifBuilder b;
    b.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, bp, bw, psm)},
          {reg::TRXPOS, gs_trxpos(0, 0, x, y)},
          {reg::TRXREG, gs_trxreg(w, h)},
          {reg::TRXDIR, 0}});
    b.image(bytes.data(), bytes.size());
    f.send(b);
}

std::vector<u8> download(Fixture& f, u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 w, u32 h, std::size_t bytes) {
    GifBuilder b;
    b.ad({{reg::BITBLTBUF, gs_bitbltbuf(bp, bw, psm, 0, 0, 0)},
          {reg::TRXPOS, gs_trxpos(x, y, 0, 0)},
          {reg::TRXREG, gs_trxreg(w, h)},
          {reg::TRXDIR, 1}});
    f.send(b);
    std::vector<u128> q((bytes + 15) / 16);
    f.core().read_image(q);
    std::vector<u8> out(bytes);
    std::memcpy(out.data(), q.data(), bytes);
    return out;
}

} // namespace

TEST_CASE("swizzle: column tables match the GS manual's literal tables (hand: GS User's Manual)") {
    const SwizzleTables& t = swizzle_tables();
    for (u32 y = 0; y < 8; ++y)
        for (u32 x = 0; x < 8; ++x) CHECK(t.ct32[y][x] == kLit32[y][x] * 4u);
    for (u32 y = 0; y < 8; ++y)
        for (u32 x = 0; x < 16; ++x) CHECK(t.ct16[y][x] == ((y >> 1) * 32u + kLit16[y & 1u][x]) * 2u);
    for (u32 y = 0; y < 16; ++y)
        for (u32 x = 0; x < 16; ++x) CHECK(t.t8[y][x] == kLit8[y & 7u][x] + (y >= 8 ? 128u : 0u));
    for (u32 y = 0; y < 16; ++y)
        for (u32 x = 0; x < 32; ++x) CHECK(t.t4[y][x] == kLit4[y & 7u][x] + (y >= 8 ? 256u : 0u));
}

TEST_CASE("swizzle: block order inside a page, Z formats at block XOR 24 (hand: GS User's Manual)") {
    const SwizzleTables& t = swizzle_tables();
    // PSMCT32 blocks: first row 0 1 4 5 16 17 20 21, first column 0 2 8 10.
    const u32 row0[8] = {0, 1, 4, 5, 16, 17, 20, 21};
    for (u32 bx = 0; bx < 8; ++bx) CHECK(t.ct32[0][bx * 8] / 256u == row0[bx]);
    const u32 col0[4] = {0, 2, 8, 10};
    for (u32 by = 0; by < 4; ++by) CHECK(t.ct32[by * 8][0] / 256u == col0[by]);
    // PSMCT16 vs PSMCT16S differ in block order only.
    CHECK(t.ct16[0][32] / 256u == 8u);
    CHECK(t.ct16s[0][32] / 256u == 16u);
    CHECK(t.ct16[16][0] / 256u == 4u);
    CHECK(t.ct16s[16][0] / 256u == 8u);
    // Z32/Z16/Z16S: the same pixel lands 24 blocks away (XOR).
    CHECK(t.z32[0][0] == 24u * 256u);
    CHECK(t.z32[24][56] / 256u == (31u ^ 24u));
    CHECK(t.z16[0][0] == 24u * 256u);
    CHECK(t.z16s[0][0] == 24u * 256u);
    CHECK(t.z16s[8][0] / 256u == (1u ^ 24u));
    CHECK(GsMemory::addr32(0, 1, 0, 0, true) == 6144u);
    CHECK(GsMemory::addr16(0, 1, 0, 0, 3) == 6144u);
}

TEST_CASE("swizzle: every format maps one page onto all of its 8 KiB exactly once (hand: GS User's Manual)") {
    const SwizzleTables& t = swizzle_tables();
    const auto check_perm = [](auto& table, u32 step, u32 limit) {
        std::vector<u8> seen(limit, 0);
        for (const auto& row : table)
            for (u16 v : row) {
                REQUIRE(v % step == 0);
                REQUIRE(v < limit);
                ++seen[v];
            }
        u32 bad = 0;
        for (u32 i = 0; i < limit; i += step) bad += seen[i] != 1;
        CHECK(bad == 0);
    };
    check_perm(t.ct32, 4, 8192);
    check_perm(t.z32, 4, 8192);
    check_perm(t.ct16, 2, 8192);
    check_perm(t.ct16s, 2, 8192);
    check_perm(t.z16, 2, 8192);
    check_perm(t.z16s, 2, 8192);
    check_perm(t.t8, 1, 8192);
    check_perm(t.t4, 1, 16384);
}

TEST_CASE("swizzle: a PSMT8 block / column is the PSMCT32 block / column with the same number (hand: GS User's Manual)") {
    const SwizzleTables& t = swizzle_tables();
    for (u32 by = 0; by < 4; ++by) {
        for (u32 bx = 0; bx < 8; ++bx) {
            std::set<u32> b8, b32;
            for (u32 y = 0; y < 16; ++y)
                for (u32 x = 0; x < 16; ++x) b8.insert(t.t8[by * 16 + y][bx * 16 + x]);
            for (u32 y = 0; y < 8; ++y)
                for (u32 x = 0; x < 8; ++x)
                    for (u32 k = 0; k < 4; ++k) b32.insert(t.ct32[by * 8 + y][bx * 8 + x] + k);
            CHECK(b8 == b32);
            // Column c of the PSMT8 block (4 rows of 16 px) = bytes c*64 .. c*64+63 of that block.
            const u32 base = t.ct32[by * 8][bx * 8] & ~255u;
            for (u32 c = 0; c < 4; ++c) {
                u32 lo = ~0u, hi = 0;
                for (u32 y = c * 4; y < c * 4 + 4; ++y)
                    for (u32 x = 0; x < 16; ++x) {
                        lo = std::min<u32>(lo, t.t8[by * 16 + y][bx * 16 + x]);
                        hi = std::max<u32>(hi, t.t8[by * 16 + y][bx * 16 + x]);
                    }
                CHECK(lo == base + c * 64u);
                CHECK(hi == base + c * 64u + 63u);
            }
        }
    }
    // PSMT4 blocks (32x16) are the PSMCT16 blocks (16x8) with the same number.
    for (u32 by = 0; by < 8; ++by) {
        for (u32 bx = 0; bx < 4; ++bx) {
            std::set<u32> b4, b16;
            for (u32 y = 0; y < 16; ++y)
                for (u32 x = 0; x < 32; ++x) b4.insert(t.t4[by * 16 + y][bx * 32 + x] / 2u);
            for (u32 y = 0; y < 8; ++y)
                for (u32 x = 0; x < 16; ++x)
                    for (u32 k = 0; k < 2; ++k) b16.insert(t.ct16[by * 8 + y][bx * 16 + x] + k);
            CHECK(b4 == b16);
        }
    }
}

TEST_CASE("swizzle: page layout, buffer width, mid-page base pointer and 4 MiB wrap (hand: GS User's Manual)") {
    // PSMCT32, BW 10 (640 px, the game's frame buffer): pages are 64x32, 10 per row.
    CHECK(GsMemory::addr32(0, 10, 64, 0) == 8192u);
    CHECK(GsMemory::addr32(0, 10, 0, 32) == 10u * 8192u);
    CHECK(GsMemory::addr32(0, 10, 639, 447) / 8192u == 13u * 10u + 9u);
    // The game's second frame buffer FBP 140 = block 4480: pixel (0,0) at 0x118000 (docs/ANALYSIS/10 §2.9).
    CHECK(GsMemory::addr32(140 * 32, 10, 0, 0) == 0x118000u);
    // Z at ZBP 280 PSMZ16S: page 280 is 0x230000; pixel (0,0) is in block 24 of it.
    CHECK(GsMemory::addr16(280 * 32, 10, 0, 0, 3) == 0x230000u + 24u * 256u);
    // PSMCT16: 64x64 pages, BW pages per row.
    CHECK(GsMemory::addr16(0, 10, 0, 64, 0) == 10u * 8192u);
    // PSMT8: 128x64 pages, BW/2 per row.
    CHECK(GsMemory::addr8(0, 10, 128, 0) == 8192u);
    CHECK(GsMemory::addr8(0, 10, 0, 64) == 5u * 8192u);
    // PSMT4: 128x128 pages, BW/2 per row (nibble addresses).
    CHECK(GsMemory::addr4(0, 10, 128, 0) == 2u * 8192u);
    CHECK(GsMemory::addr4(0, 10, 0, 128) == 2u * 5u * 8192u);
    // A base pointer in the middle of a page adds block numbers, not page numbers.
    CHECK(GsMemory::addr32(1, 1, 0, 0) == 256u);
    CHECK(GsMemory::addr32(1, 1, 8, 0) == 2u * 256u);
    CHECK(GsMemory::addr32(30, 1, 16, 0) == ((30u + 4u) * 256u));
    // Block numbers wrap at 16384 (4 MiB).
    CHECK(GsMemory::addr32(16383, 1, 8, 0) == 0u);
    CHECK(GsMemory::addr32(0, 1, 0, 2048 + 3) == GsMemory::addr32(0, 1, 0, 3));
}

TEST_CASE("memory: raw read/write per format; T8H/T4HL/T4HH and CT24/Z24 share PSMCT32 words (hand: GS User's Manual)") {
    GsMemory m;
    std::mt19937 rng(1234);
    for (u32 psm : kAllPsm) {
        CAPTURE(psm_name(psm));
        m.clear();
        std::vector<u32> vals(70 * 40);
        for (u32& v : vals) v = rng() & value_mask(psm);
        for (u32 y = 0; y < 40; ++y)
            for (u32 x = 0; x < 70; ++x) m.write(psm, 0x100, 4, x + 50, y + 20, vals[y * 70 + x]);
        u32 bad = 0;
        for (u32 y = 0; y < 40; ++y)
            for (u32 x = 0; x < 70; ++x) bad += m.read(psm, 0x100, 4, x + 50, y + 20) != vals[y * 70 + x];
        CHECK(bad == 0);
    }
    m.clear();
    m.write(0x00, 0, 1, 3, 5, 0x11223344u);
    CHECK(m.read(0x1B, 0, 1, 3, 5) == 0x11u);
    CHECK(m.read(0x24, 0, 1, 3, 5) == 0x1u);
    CHECK(m.read(0x2C, 0, 1, 3, 5) == 0x1u);
    m.write(0x2C, 0, 1, 3, 5, 0xA);
    CHECK(m.read(0x00, 0, 1, 3, 5) == 0xA1223344u);
    m.write(0x24, 0, 1, 3, 5, 0x7);
    CHECK(m.read(0x00, 0, 1, 3, 5) == 0xA7223344u);
    m.write(0x1B, 0, 1, 3, 5, 0x5C);
    CHECK(m.read(0x00, 0, 1, 3, 5) == 0x5C223344u);
    m.write(0x01, 0, 1, 3, 5, 0xFFAABBCCu);
    CHECK(m.read(0x00, 0, 1, 3, 5) == 0x5CAABBCCu);
    m.write(0x31, 0, 1, 3, 5, 0xFF010203u);
    CHECK((m.read(0x30, 0, 1, 3, 5) & 0xFFFFFFu) == 0x010203u);
}

TEST_CASE("transfer: host -> local -> host round trip for every PSM, crossing page boundaries (hand: GS User's Manual)") {
    std::mt19937 rng(99);
    for (u32 psm : kAllPsm) {
        CAPTURE(psm_name(psm));
        Fixture f;
        const u32 w = 75, h = 70, x0 = 60, y0 = 30, bp = 0x400, bw = 4;
        std::vector<u32> vals(static_cast<std::size_t>(w) * h);
        for (u32& v : vals) v = rng() & value_mask(psm);
        const std::vector<u8> bytes = pack(vals, psm_bits(psm));
        upload(f, psm, bp, bw, x0, y0, w, h, bytes);
        CHECK(f.core().stats().image_qwords_in == (bytes.size() + 15) / 16);
        u32 bad = 0;
        for (u32 y = 0; y < h; ++y)
            for (u32 x = 0; x < w; ++x) bad += f.mem().read(psm, bp, bw, x0 + x, y0 + y) != vals[y * w + x];
        CHECK(bad == 0);
        const std::vector<u8> back = download(f, psm, bp, bw, x0, y0, w, h, bytes.size());
        CHECK(back == bytes);
        CHECK_FALSE(f.core().local_to_host_active());
    }
}

TEST_CASE("transfer: HWREG writes feed the host -> local transfer like IMAGE data (hand: GS User's Manual)") {
    Fixture f;
    GifBuilder b;
    b.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0, 1, 0x00)},
          {reg::TRXPOS, gs_trxpos(0, 0, 2, 3)},
          {reg::TRXREG, gs_trxreg(4, 1)},
          {reg::TRXDIR, 0},
          {reg::HWREG, 0x2222222211111111ull},
          {reg::HWREG, 0x4444444433333333ull}});
    f.send(b);
    CHECK(f.mem().read(0x00, 0, 1, 2, 3) == 0x11111111u);
    CHECK(f.mem().read(0x00, 0, 1, 5, 3) == 0x44444444u);
    CHECK_FALSE(f.core().host_to_local_active());
}

TEST_CASE("transfer: data written as PSMCT32 reads back as PSMT8 per the manual's tables (hand: GS User's Manual)") {
    // 8x8 PSMCT32 pixels whose bytes are 0..255 in raster order fill exactly block 0; reading the same block as a
    // 16x16 PSMT8 image (BW 2) must return, for each pixel, the byte at its PSMT8 offset. Expected values come from
    // the literal tables, not from the implementation's formulas.
    Fixture f;
    std::vector<u8> bytes(256);
    for (u32 i = 0; i < 256; ++i) bytes[i] = static_cast<u8>(i);
    upload(f, 0x00, 0, 2, 0, 0, 8, 8, bytes);
    // Byte offset inside the block -> CT32 pixel (word index -> raster index via kLit32) -> value.
    u32 raster_of_word[64];
    for (u32 y = 0; y < 8; ++y)
        for (u32 x = 0; x < 8; ++x) raster_of_word[kLit32[y][x]] = y * 8 + x;
    u32 bad = 0;
    for (u32 y = 0; y < 16; ++y)
        for (u32 x = 0; x < 16; ++x) {
            const u32 off = kLit8[y & 7u][x] + (y >= 8 ? 128u : 0u);
            const u32 expect = raster_of_word[off / 4] * 4 + off % 4;
            bad += f.mem().read(0x13, 0, 2, x, y) != expect;
        }
    CHECK(bad == 0);
    // Spot values: T8 (0,2) is byte 33 = word 8 byte 1; word 8 is CT32 pixel (4,0) -> 4*4+1.
    CHECK(f.mem().read(0x13, 0, 2, 0, 2) == 17u);
    // The PSMT8 download of that block reproduces the same bytes in PSMT8 raster order.
    const std::vector<u8> t8 = download(f, 0x13, 0, 2, 0, 0, 16, 16, 256);
    CHECK(t8[2 * 16 + 0] == 17u);
}

TEST_CASE("transfer: local -> local copy honours TRXPOS.DIR for overlapping rectangles (hand: GS User's Manual)") {
    Fixture f;
    for (u32 x = 0; x < 8; ++x) f.mem().write(0x00, 0, 1, x, 0, 100 + x);
    // Copy [0,6) -> [2,8) on the same row. DIR 2/3 (right to left) must not smear the source.
    GifBuilder b;
    b.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 1, 0x00, 0, 1, 0x00)},
          {reg::TRXPOS, gs_trxpos(0, 0, 2, 0, 2)},
          {reg::TRXREG, gs_trxreg(6, 1)},
          {reg::TRXDIR, 2}});
    f.send(b);
    for (u32 x = 2; x < 8; ++x) CHECK(f.mem().read(0x00, 0, 1, x, 0) == 100 + x - 2);
    // The same copy left to right (DIR 0) propagates the first two pixels.
    for (u32 x = 0; x < 8; ++x) f.mem().write(0x00, 0, 1, x, 0, 100 + x);
    GifBuilder c;
    c.ad({{reg::TRXPOS, gs_trxpos(0, 0, 2, 0, 0)}, {reg::TRXDIR, 2}});
    f.send(c);
    CHECK(f.mem().read(0x00, 0, 1, 7, 0) == 101u);
    CHECK(f.core().stats().local_copies == 2u);
}
