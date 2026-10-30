#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/pak.h"
#include "p3fes/formats/rmd.h"
#include "p3fes/formats/tmx.h"

using namespace p3fes;
using namespace p3fes::formats;

namespace {

// Builds a synthetic PAK: entries padded to 64 bytes, zero terminator header.
std::vector<std::byte> make_pak(const std::vector<std::pair<std::string, std::vector<std::byte>>>& files,
                                bool terminator = true) {
    std::vector<std::byte> out;
    for (const auto& [name, data] : files) {
        std::vector<std::byte> hdr(kPakHeaderSize, std::byte{0});
        std::memcpy(hdr.data(), name.data(), name.size());
        const u32 size = static_cast<u32>(data.size());
        std::memcpy(hdr.data() + kPakNameSize, &size, 4);
        out.insert(out.end(), hdr.begin(), hdr.end());
        out.insert(out.end(), data.begin(), data.end());
        out.resize(align_up(out.size(), kPakEntryAlign), std::byte{0});
    }
    if (terminator) out.resize(out.size() + kPakHeaderSize, std::byte{0});
    return out;
}

}  // namespace

TEST_CASE("PAK: real BUSTUP pack (BUST_DUMMY.BIN) has one TMX entry and a zero terminator") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/BUSTUP/BUST_DUMMY.BIN");
    auto r = PakView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    REQUIRE(r->entries().size() == 1);
    const PakEntry& e = r->entries()[0];
    CHECK(e.name == "bust_dummy.tmx");
    CHECK(e.data.size() == 0x40440);
    CHECK(is_tmx(e.data));
    CHECK_FALSE(r->eof_terminated());
    // Payload ends at 0x40540, which is 64-aligned, so the terminator sits there
    // and the file is exactly terminator-inclusive.
    CHECK(r->terminator_offset() == 0x40540);
    CHECK(r->terminator_offset() + kPakHeaderSize == buf.size());
    CHECK(r->find("BUST_DUMMY.TMX") == &e);
    CHECK(r->find("BUST_DUMMY.TMX", /*case_insensitive=*/false) == nullptr);
    CHECK_FALSE(is_nested_pak(e));
}

TEST_CASE("PAK: BTL/MODEL/PACK/BC003.PAC has a 16-byte-unaligned RMD followed by junk padding") {
    P3FES_REQUIRE_FIXTURE(buf, "BTL/MODEL/PACK/BC003.PAC");
    auto r = PakView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    REQUIRE(r->entries().size() >= 2);
    CHECK(r->entries()[0].name == "bc003.RMD");
    CHECK(r->entries()[0].data.size() == 0x7983B);  // ends at 0x7993B: 5 junk bytes before 0x79940
    CHECK(r->entries()[1].header_offset == 0x79940);
    CHECK(r->entries()[1].name == "bc003.acx");
    CHECK(looks_like_rmd(r->entries()[0].data));
    CHECK(r->terminator_offset() + kPakHeaderSize == buf.size());
}

TEST_CASE("PAK: terminator-only pack (I_B_0315A.BIN, 256 zero bytes) parses with zero entries") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/BUSTUP/I_B_0315A.BIN");
    REQUIRE(buf.size() == 256);
    CHECK(looks_like_pak(test::span_of(buf)));
    auto r = PakView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->entries().empty());
    CHECK(r->terminator_offset() == 0);
}

TEST_CASE("PAK: cut-in C01_3101.CPK has no terminator and ends at the aligned payload end") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/CUTIN/SHAPE/C01_3101.CPK");
    auto r = PakView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->eof_terminated());
    REQUIRE(r->entries().size() == 2);
    CHECK(r->entries()[1].name == "c01_301010.tmx");
    CHECK(r->entries()[1].header_offset == 0x5340);
    CHECK(r->terminator_offset() == buf.size());
}

TEST_CASE("PAK: nested packs (CUTIN .CPK inside a BTL .SE/.PAC) are detected") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/CAMP/CAMP_FR07.PAK");
    auto r = PakView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    REQUIRE(r->entries().size() == 3);
    // Entry 2 follows 16 bytes of leftover name junk ("________W1") at 0x2EF30.
    CHECK(r->entries()[2].header_offset == 0x2EF40);
    CHECK(r->entries()[2].name == "chara/i_camp_hum_blue_07.tmx");
    for (const PakEntry& e : r->entries()) CHECK_FALSE(is_nested_pak(e));
}

TEST_CASE("PAK: synthetic round trip, lookup and nested detection") {
    std::vector<std::byte> inner_data(100, std::byte{0xAB});
    auto inner = make_pak({{"inner.bin", inner_data}});
    auto outer = make_pak({{"a.txt", {std::byte{'h'}, std::byte{'i'}}}, {"sub/pack.pak", inner}});
    auto r = PakView::parse(test::span_of(outer));
    REQUIRE(r.ok());
    REQUIRE(r->entries().size() == 2);
    CHECK(r->entries()[0].name == "a.txt");
    CHECK(r->entries()[0].data.size() == 2);
    CHECK(r->entries()[1].header_offset == 320);  // 256 + 2 -> align 64 = 320
    CHECK(is_nested_pak(r->entries()[1]));
    CHECK_FALSE(is_nested_pak(r->entries()[0]));
    CHECK(r->find("SUB/PACK.PAK") != nullptr);
    CHECK(r->find("missing") == nullptr);
    CHECK_FALSE(r->eof_terminated());

    auto eof = make_pak({{"a.bin", std::vector<std::byte>(64, std::byte{1})}}, /*terminator=*/false);
    auto r2 = PakView::parse(test::span_of(eof));
    REQUIRE(r2.ok());
    CHECK(r2->eof_terminated());
}

TEST_CASE("PAK: sniff rejects tables whose first bytes happen to be ASCII") {
    // Shapes observed on disc: BTL/SKILL/*.BED ("BED400\0" + u32 0x28...), a
    // FIELD/MAP table ("3\0\1\0" + zeros), CUTIN .CIN ("CIN\0"), IOPRP300.IMG ("RESET").
    std::vector<std::byte> bed(9840, std::byte{0});
    std::memcpy(bed.data(), "BED400", 6);
    bed[8] = std::byte{0x28};
    CHECK_FALSE(looks_like_pak(test::span_of(bed)));
    std::vector<std::byte> map(4608, std::byte{0});
    map[0] = std::byte{'3'};
    map[2] = std::byte{1};
    CHECK_FALSE(looks_like_pak(test::span_of(map)));
    std::vector<std::byte> cin(14208, std::byte{0});
    std::memcpy(cin.data(), "CIN", 3);
    cin[4] = std::byte{1};
    CHECK_FALSE(looks_like_pak(test::span_of(cin)));
    // A real-shaped single-entry pack with an extension and a terminator passes.
    auto ok = make_pak({{"x.tmx", std::vector<std::byte>(40, std::byte{1})}});
    CHECK(looks_like_pak(test::span_of(ok)));
    // ...but the same pack with a dot-less name does not (sniff only; parse still accepts it).
    auto nodot = make_pak({{"xtmx", std::vector<std::byte>(40, std::byte{1})}});
    CHECK_FALSE(looks_like_pak(test::span_of(nodot)));
    CHECK(PakView::parse(test::span_of(nodot)).ok());
}

TEST_CASE("PAK: negative cases") {
    SUBCASE("too short") {
        std::vector<std::byte> b(100, std::byte{'a'});
        auto r = PakView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
    SUBCASE("size overruns the buffer") {
        auto b = make_pak({{"x.bin", std::vector<std::byte>(10, std::byte{1})}});
        const u32 huge = 0x7FFFFFFF;
        std::memcpy(b.data() + kPakNameSize, &huge, 4);
        auto r = PakView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::BadMagic);  // first entry: cannot even identify as PAK
        CHECK_FALSE(looks_like_pak(test::span_of(b)));
    }
    SUBCASE("non-printable name") {
        auto b = make_pak({{"ok.bin", std::vector<std::byte>(10, std::byte{1})}});
        b[0] = std::byte{0x01};
        auto r = PakView::parse(test::span_of(b));
        CHECK_FALSE(r.ok());
    }
    SUBCASE("missing terminator and truncated final header") {
        auto b = make_pak({{"ok.bin", std::vector<std::byte>(10, std::byte{1})}});
        b.resize(b.size() - 100);  // chop into the terminator header
        auto r = PakView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
}
