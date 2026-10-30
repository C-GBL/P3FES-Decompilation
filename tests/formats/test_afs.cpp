#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/adx.h"
#include "p3fes/formats/afs.h"

using namespace p3fes;
using namespace p3fes::formats;

TEST_CASE("AFS: SOUND/V185002.AFS (32 KiB) holds one ADX with a 48-byte name record") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/SOUND/V185002.AFS");
    REQUIRE(is_afs(test::span_of(buf)));
    auto r = AfsView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    REQUIRE(r->entries().size() == 1);
    const AfsEntry& e = r->entries()[0];
    CHECK(e.offset == 0x800);
    CHECK(e.size == 0x69C4);
    CHECK(e.data.size() == 0x69C4);
    CHECK(r->has_names());
    CHECK(r->name_block_offset() == 0x7800);
    CHECK(r->name_block_size() == 0x30);
    // Name block sits at the 2048-aligned end of the last member.
    CHECK(r->name_block_offset() == align_up(e.offset + e.size, 2048));
    CHECK(e.name == "000_000000_00_");
    CHECK(e.timestamp.year == 2006);
    CHECK(e.timestamp.month == 1);
    CHECK(e.timestamp.day == 18);
    CHECK(e.timestamp.hour == 15);
    CHECK(e.timestamp.minute == 12);
    CHECK(e.timestamp.second == 12);
    CHECK(e.name_record_tail == 1);

    // The member is a 24 kHz mono v4 ADX.
    REQUIRE(is_adx(e.data));
    auto adx = parse_adx(e.data);
    REQUIRE(adx.ok());
    CHECK(adx->header.channels == 1);
    CHECK(adx->header.sample_rate == 24000);
    CHECK(adx->body_fits);
}

TEST_CASE("AFS: every member of a larger voice archive is 2048-aligned ADX") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/SOUND/V452001.AFS");
    auto r = AfsView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->entries().size() > 1);
    for (const AfsEntry& e : r->entries()) {
        CHECK(e.offset % 2048 == 0);
        CHECK(is_adx(e.data));
        CHECK_FALSE(e.name.empty());
    }
}

TEST_CASE("AFS: synthetic and negative cases") {
    auto build = [](u32 count, bool with_names) {
        std::vector<std::byte> b(2048, std::byte{0});
        std::memcpy(b.data(), "AFS\0", 4);
        std::memcpy(b.data() + 4, &count, 4);
        u32 off = 2048;
        for (u32 i = 0; i < count; ++i) {
            const u32 size = 100 + i;
            std::memcpy(b.data() + 8 + 8 * i, &off, 4);
            std::memcpy(b.data() + 12 + 8 * i, &size, 4);
            off += 2048;
        }
        const u32 name_off = with_names ? off : 0, name_size = with_names ? 48 * count : 0;
        std::memcpy(b.data() + 8 + 8 * count, &name_off, 4);
        std::memcpy(b.data() + 12 + 8 * count, &name_size, 4);
        b.resize(off + (with_names ? 2048 : 0), std::byte{0});
        if (with_names) {
            for (u32 i = 0; i < count; ++i) {
                const char* nm = "member";
                std::memcpy(b.data() + name_off + 48 * i, nm, 6);
            }
        }
        return b;
    };
    SUBCASE("two members with names") {
        auto b = build(2, true);
        auto r = AfsView::parse(test::span_of(b));
        REQUIRE(r.ok());
        REQUIRE(r->entries().size() == 2);
        CHECK(r->entries()[1].offset == 4096);
        CHECK(r->entries()[1].size == 101);
        CHECK(r->entries()[1].name == "member");
        CHECK(r->has_names());
    }
    SUBCASE("no name block") {
        auto b = build(1, false);
        auto r = AfsView::parse(test::span_of(b));
        REQUIRE(r.ok());
        CHECK_FALSE(r->has_names());
        CHECK(r->entries()[0].name.empty());
    }
    SUBCASE("bad magic") {
        auto b = build(1, true);
        b[3] = std::byte{'X'};
        CHECK(AfsView::parse(test::span_of(b)).code() == FormatError::BadMagic);
        CHECK_FALSE(is_afs(test::span_of(b)));
    }
    SUBCASE("entry overruns") {
        auto b = build(1, true);
        const u32 huge = 0x7FFFFFFF;
        std::memcpy(b.data() + 12, &huge, 4);
        CHECK(AfsView::parse(test::span_of(b)).code() == FormatError::Overrun);
    }
    SUBCASE("truncated table") {
        std::vector<std::byte> b(12, std::byte{0});
        std::memcpy(b.data(), "AFS\0", 4);
        const u32 count = 1000;
        std::memcpy(b.data() + 4, &count, 4);
        CHECK(AfsView::parse(test::span_of(b)).code() == FormatError::Truncated);
    }
}
