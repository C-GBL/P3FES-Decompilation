#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/rmd.h"

using namespace p3fes;
using namespace p3fes::formats;

TEST_CASE("RMD: WEAPON/WP017.RMD chunk tree (Atlus tag, Atlus setup, TexDictionary, Clump...)") {
    P3FES_REQUIRE_FIXTURE(buf, "BTL/MODEL/WEAPON/WP017.RMD");
    REQUIRE(looks_like_rmd(test::span_of(buf)));
    auto r = parse_rmd(test::span_of(buf));
    REQUIRE(r.ok());
    const RwStream& s = r.value();
    REQUIRE(s.chunks.size() >= 4);
    CHECK(s.chunks[0].type == rw::kAtlusSceneTag);
    CHECK(s.chunks[0].size == 2);
    CHECK(s.chunks[0].library_id == rw::kAtlusLibraryId);
    CHECK(s.chunks[0].depth == 0);
    CHECK(s.chunks[1].offset == 0x0E);  // directly after the 2-byte payload, unaligned
    CHECK(s.chunks[1].type == 0xF0F000E0u);
    CHECK(s.chunks[1].size == 0x484);
    // 0x0E + 12 + 0x484 = 0x49E; two zero pad bytes precede the TexDictionary at 0x4A0.
    CHECK(s.padding_bytes >= 2);
    bool found_texdict = false;
    for (const RwChunk& c : s.chunks) {
        if (c.type == rw::kTexDictionary && c.depth == 0) {
            found_texdict = true;
            CHECK(c.offset == 0x4A0);
            CHECK(c.library_id == rw::kP3LibraryId);
        }
        CHECK(c.end() <= buf.size());
        if (c.parent != 0xFFFFFFFFu) {
            const RwChunk& p = s.chunks[c.parent];
            CHECK(c.offset >= p.payload_offset());
            CHECK(c.end() <= p.end());
            CHECK(c.depth == p.depth + 1);
        }
    }
    CHECK(found_texdict);
    CHECK(s.count(rw::kClump) == 1);
    CHECK(s.count(rw::kTextureNative) >= 1);
    CHECK(s.count(rw::kFrameList) >= 1);
    CHECK(s.count(rw::kGeometry) >= 1);
    CHECK(s.count(rw::kAtomic) >= 1);
    CHECK(s.consumed == buf.size());
    CHECK_FALSE(s.trailing_bytes);
}

TEST_CASE("RMD: libraryID decodes to RenderWare 3.7.0.2") {
    CHECK(rw::version(rw::kP3LibraryId) == 0x37002);
    CHECK(rw::build(rw::kP3LibraryId) == 0x37);
    CHECK(rw::version(0x1C02002Du) == 0x37002);
    CHECK(rw::type_name(rw::kClump) == "Clump");
    CHECK(rw::type_name(0xF0F00004u) == "AtlusChunk");
    CHECK(rw::is_atlus(0xF0F00005u));
    CHECK_FALSE(rw::is_atlus(rw::kClump));
}

TEST_CASE("RMD: synthetic stream and negative cases") {
    auto put = [](std::vector<std::byte>& b, u32 type, u32 size, u32 lib) {
        std::byte h[12];
        std::memcpy(h, &type, 4);
        std::memcpy(h + 4, &size, 4);
        std::memcpy(h + 8, &lib, 4);
        b.insert(b.end(), h, h + 12);
    };
    SUBCASE("clump containing a struct and a frame list containing a struct") {
        std::vector<std::byte> b;
        put(b, rw::kClump, 12 + 4 + 12 + 12 + 4, rw::kP3LibraryId);
        put(b, rw::kStruct, 4, rw::kP3LibraryId);
        b.resize(b.size() + 4, std::byte{0});
        put(b, rw::kFrameList, 12 + 4, rw::kP3LibraryId);
        put(b, rw::kStruct, 4, rw::kP3LibraryId);
        b.resize(b.size() + 4, std::byte{0});
        auto r = parse_rmd(test::span_of(b));
        REQUIRE(r.ok());
        REQUIRE(r->chunks.size() == 4);
        CHECK(r->chunks[0].depth == 0);
        CHECK(r->chunks[1].depth == 1);
        CHECK(r->chunks[2].depth == 1);
        CHECK(r->chunks[3].depth == 2);
        CHECK(r->chunks[3].parent == 2);
        CHECK(r->consumed == b.size());
    }
    SUBCASE("a container whose payload is not a chunk sequence stays a leaf") {
        std::vector<std::byte> b;
        put(b, rw::kClump, 16, rw::kP3LibraryId);
        b.resize(b.size() + 16, std::byte{0x77});
        auto r = parse_rmd(test::span_of(b));
        REQUIRE(r.ok());
        CHECK(r->chunks.size() == 1);
    }
    SUBCASE("too short / bad library id / size overrun") {
        std::vector<std::byte> s(8, std::byte{0});
        CHECK(parse_rmd(test::span_of(s)).code() == FormatError::Truncated);
        // The libraryID plausibility check accepts anything decoding to RW 3.x
        // (0x12345678 does, as 3.4.8.x); 0xFFFFFFFF decodes outside that range.
        std::vector<std::byte> b;
        put(b, rw::kClump, 0, 0xFFFFFFFFu);
        CHECK(parse_rmd(test::span_of(b)).code() == FormatError::BadMagic);
        CHECK_FALSE(looks_like_rmd(test::span_of(b)));
        std::vector<std::byte> o;
        put(o, rw::kClump, 1000, rw::kP3LibraryId);
        CHECK(parse_rmd(test::span_of(o)).code() == FormatError::Overrun);
    }
    SUBCASE("corrupt later header truncates the walk and flags trailing bytes") {
        std::vector<std::byte> b;
        put(b, rw::kStruct, 4, rw::kP3LibraryId);
        b.resize(b.size() + 4, std::byte{0});
        b.resize(b.size() + 12, std::byte{0xFF});
        auto r = parse_rmd(test::span_of(b));
        REQUIRE(r.ok());
        CHECK(r->chunks.size() == 1);
        CHECK(r->trailing_bytes);
        CHECK(r->consumed == 16);
    }
}
