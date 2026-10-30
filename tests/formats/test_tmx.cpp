#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/tmx.h"

using namespace p3fes;
using namespace p3fes::formats;

TEST_CASE("TMX: CARD/PERSONA/I_PRC001.TMX is a 256x256 PSMT8 texture with one CT32 palette") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/CARD/PERSONA/I_PRC001.TMX");
    REQUIRE(is_tmx(test::span_of(buf)));
    auto r = TmxView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    const TmxHeader& h = r->header();
    CHECK(h.id == 2);
    CHECK(h.file_size == 0x10440);
    CHECK(h.file_size == buf.size());
    CHECK(h.palette_count == 1);
    CHECK(h.palette_psm == TmxPsm::CT32);
    CHECK(h.width == 256);
    CHECK(h.height == 256);
    CHECK(h.pixel_psm == TmxPsm::T8);
    CHECK(h.mip_count == 0);
    CHECK(h.wrap_mode == 0xFF00);
    CHECK(h.comment.empty());
    CHECK(r->palette_bytes_each() == 1024);
    CHECK(r->palette(0).size() == 1024);
    CHECK(r->palette(1).empty());
    CHECK(r->pixels().size() == 256 * 256);
    CHECK(kTmxHeaderSize + 1024 + r->pixels().size() == buf.size());

    std::vector<u8> rgba(r->rgba8_size());
    REQUIRE(r->to_rgba8(rgba) == FormatError::None);
    // Pixel 0 must equal the unswizzled palette entry of its index, alpha rescaled.
    u8 clut[1024];
    tmx_unswizzle_clut8(r->palette(0), std::span<u8>(clut, 1024));
    const u8 idx = static_cast<u8>(r->pixels()[0]);
    CHECK(rgba[0] == clut[idx * 4 + 0]);
    CHECK(rgba[1] == clut[idx * 4 + 1]);
    CHECK(rgba[2] == clut[idx * 4 + 2]);
    const u8 a = clut[idx * 4 + 3];
    CHECK(rgba[3] == (a >= 0x80 ? 0xFF : a * 2));
}

TEST_CASE("TMX: a PSMT4 texture inside a cut-in pack converts (first entry of C01_3101.CPK)") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/CUTIN/SHAPE/C01_3101.CPK");
    // Second PAK entry at 0x5340 + 256 = c01_301010.tmx (0x10080 bytes).
    Bytes tmx = test::span_of(buf).subspan(0x5340 + 256, 0x10080);
    REQUIRE(is_tmx(tmx));
    auto r = TmxView::parse(tmx);
    REQUIRE(r.ok());
    CHECK(r->header().file_size == 0x10080);
    std::vector<u8> rgba(r->rgba8_size());
    CHECK(r->to_rgba8(rgba) == FormatError::None);
}

TEST_CASE("TMX: CLUT unswizzle swaps blocks 1 and 2 of every 32 colours") {
    u8 in[1024], out[1024];
    for (int i = 0; i < 256; ++i) {
        in[i * 4] = static_cast<u8>(i);
        in[i * 4 + 1] = in[i * 4 + 2] = in[i * 4 + 3] = 0;
    }
    tmx_unswizzle_clut8(as_bytes(in, 1024), std::span<u8>(out, 1024));
    CHECK(out[0 * 4] == 0);
    CHECK(out[7 * 4] == 7);
    CHECK(out[8 * 4] == 16);   // block 1 <- block 2
    CHECK(out[15 * 4] == 23);
    CHECK(out[16 * 4] == 8);   // block 2 <- block 1
    CHECK(out[23 * 4] == 15);
    CHECK(out[24 * 4] == 24);
    CHECK(out[31 * 4] == 31);
    CHECK(out[32 * 4] == 32);
    CHECK(out[40 * 4] == 48);
    CHECK(out[255 * 4] == 255);
}

TEST_CASE("TMX: synthetic CT32 / CT16 / T4 conversion") {
    auto make = [](u16 w, u16 h, TmxPsm px, u8 npal, const std::vector<u8>& body) {
        std::vector<std::byte> b(kTmxHeaderSize + body.size(), std::byte{0});
        const u16 id = 2;
        const u32 size = static_cast<u32>(b.size());
        std::memcpy(b.data(), &id, 2);
        std::memcpy(b.data() + 4, &size, 4);
        std::memcpy(b.data() + 8, "TMX0", 4);
        b[0x10] = std::byte{npal};
        b[0x11] = std::byte{0};
        std::memcpy(b.data() + 0x12, &w, 2);
        std::memcpy(b.data() + 0x14, &h, 2);
        b[0x16] = static_cast<std::byte>(px);
        std::memcpy(b.data() + kTmxHeaderSize, body.data(), body.size());
        return b;
    };
    SUBCASE("CT32 2x1") {
        auto b = make(2, 1, TmxPsm::CT32, 0, {10, 20, 30, 0x80, 1, 2, 3, 0x40});
        auto r = TmxView::parse(test::span_of(b));
        REQUIRE(r.ok());
        std::vector<u8> out(8);
        REQUIRE(r->to_rgba8(out) == FormatError::None);
        CHECK(out == std::vector<u8>{10, 20, 30, 0xFF, 1, 2, 3, 0x80});
    }
    SUBCASE("CT16 1x1 white opaque") {
        auto b = make(1, 1, TmxPsm::CT16, 0, {0xFF, 0xFF});
        auto r = TmxView::parse(test::span_of(b));
        REQUIRE(r.ok());
        std::vector<u8> out(4);
        REQUIRE(r->to_rgba8(out) == FormatError::None);
        CHECK(out == std::vector<u8>{255, 255, 255, 255});
    }
    SUBCASE("T4 2x1: low nibble first") {
        std::vector<u8> body(16 * 4, 0);
        body[1 * 4] = 0x11;  // colour 1 = red-ish
        body[2 * 4 + 1] = 0x22;  // colour 2 = green-ish
        body[1 * 4 + 3] = body[2 * 4 + 3] = 0x80;
        body.push_back(0x21);  // pixel0 = 1, pixel1 = 2
        auto b = make(2, 1, TmxPsm::T4, 1, body);
        auto r = TmxView::parse(test::span_of(b));
        REQUIRE(r.ok());
        std::vector<u8> out(8);
        REQUIRE(r->to_rgba8(out) == FormatError::None);
        CHECK(out == std::vector<u8>{0x11, 0, 0, 0xFF, 0, 0x22, 0, 0xFF});
    }
    SUBCASE("output buffer too small") {
        auto b = make(2, 1, TmxPsm::CT32, 0, std::vector<u8>(8, 0));
        auto r = TmxView::parse(test::span_of(b));
        REQUIRE(r.ok());
        std::vector<u8> out(4);
        CHECK(r->to_rgba8(out) == FormatError::Truncated);
    }
    SUBCASE("negative: bad magic, truncated, overrun, indexed without palette") {
        auto b = make(2, 1, TmxPsm::CT32, 0, std::vector<u8>(8, 0));
        std::memcpy(b.data() + 8, "TMX1", 4);
        CHECK(TmxView::parse(test::span_of(b)).code() == FormatError::BadMagic);
        std::vector<std::byte> t(0x20, std::byte{0});
        CHECK(TmxView::parse(test::span_of(t)).code() == FormatError::Truncated);
        auto o = make(64, 64, TmxPsm::CT32, 0, std::vector<u8>(8, 0));
        CHECK(TmxView::parse(test::span_of(o)).code() == FormatError::Overrun);
        auto np = make(2, 1, TmxPsm::T8, 0, std::vector<u8>(2, 0));
        CHECK(TmxView::parse(test::span_of(np)).code() == FormatError::BadHeader);
    }
}
