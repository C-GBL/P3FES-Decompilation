#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/adx.h"

using namespace p3fes;
using namespace p3fes::formats;

TEST_CASE("ADX: BGM/0501.ADX is 48 kHz stereo v4 with no loop block and an end marker") {
    P3FES_REQUIRE_FIXTURE(buf, "BGM/0501.ADX");
    REQUIRE(is_adx(test::span_of(buf)));
    auto r = parse_adx(test::span_of(buf));
    REQUIRE(r.ok());
    const AdxHeader& h = r->header;
    CHECK(h.copyright_offset == 0x24);
    CHECK(h.data_offset() == 0x28);
    CHECK(h.encoding == 3);
    CHECK(h.block_size == 18);
    CHECK(h.sample_bit_depth == 4);
    CHECK(h.channels == 2);
    CHECK(h.sample_rate == 48000);
    CHECK(h.sample_count == 0x15783);
    CHECK(h.highpass_cutoff == 500);
    CHECK(h.version == 4);
    CHECK(h.flags == 0);
    CHECK_FALSE(h.loop.has_value());
    CHECK(h.frame_count() == 2749);
    CHECK(h.expected_body_bytes() == 2749ull * 18 * 2);
    CHECK(r->copyright_ok);
    CHECK(r->body_fits);
    CHECK(r->end_marker);
    // header + body + one 18-byte end block == file size
    CHECK(h.data_offset() + h.expected_body_bytes() + 18 == buf.size());
}

TEST_CASE("ADX: SOUND2/EVENT/EVE_149.ADX carries a v4 loop block whose byte offsets match the framing") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/SOUND2/EVENT/EVE_149.ADX");
    auto r = parse_adx(test::span_of(buf));
    REQUIRE(r.ok());
    const AdxHeader& h = r->header;
    CHECK(h.version == 4);
    CHECK(h.channels == 2);
    CHECK(h.sample_rate == 24000);
    CHECK(h.data_offset() == 0x80);
    REQUIRE(h.loop.has_value());
    CHECK(h.loop->alignment_samples == 1);
    CHECK(h.loop->enabled == 1);
    CHECK(h.loop->begin_sample == 154624);
    CHECK(h.loop->begin_byte == 174080);
    CHECK(h.loop->end_sample == 298496);
    CHECK(h.loop->end_byte == 335936);  // 0x52040
    // begin_byte == data_offset + (begin_sample / 32) * block_size * channels
    CHECK(h.loop->begin_byte == h.data_offset() + (h.loop->begin_sample / 32) * 18u * 2u);
    CHECK(h.loop->end_byte <= buf.size());
}

TEST_CASE("ADX: SOUND/VOICE/V000.ADX is a v3 mono header") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/SOUND/VOICE/V000.ADX");
    auto r = parse_adx(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->header.version == 3);
    CHECK(r->header.channels == 1);
    CHECK(r->header.sample_rate == 24000);
    CHECK(r->header.copyright_offset == 0x20);
    CHECK_FALSE(r->header.loop.has_value());
    CHECK(r->copyright_ok);
    CHECK(r->body_fits);
}

TEST_CASE("ADX: negative cases") {
    SUBCASE("bad magic") {
        std::vector<std::byte> b(0x30, std::byte{0});
        auto r = parse_adx(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::BadMagic);
        CHECK_FALSE(is_adx(test::span_of(b)));
    }
    SUBCASE("truncated") {
        std::vector<std::byte> b(0x10, std::byte{0});
        b[0] = std::byte{0x80};
        auto r = parse_adx(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
    SUBCASE("copyright offset past the end") {
        std::vector<std::byte> b(0x20, std::byte{0});
        b[0] = std::byte{0x80};
        b[2] = std::byte{0x7F};
        b[3] = std::byte{0xFF};
        b[4] = std::byte{3};
        b[5] = std::byte{18};
        b[6] = std::byte{4};
        b[7] = std::byte{1};
        b[0x12] = std::byte{4};
        auto r = parse_adx(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Overrun);
    }
    SUBCASE("unknown version") {
        std::vector<std::byte> b(0x30, std::byte{0});
        b[0] = std::byte{0x80};
        b[3] = std::byte{0x24};
        b[4] = std::byte{3};
        b[5] = std::byte{18};
        b[6] = std::byte{4};
        b[7] = std::byte{1};
        b[0x12] = std::byte{9};
        auto r = parse_adx(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Unsupported);
    }
}
