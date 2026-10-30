#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/bmd.h"

using namespace p3fes;
using namespace p3fes::formats;

TEST_CASE("BMD: DATTUTORIAL.BMD (110 bytes) decodes header, one message and the relocation table") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/HELP/DATTUTORIAL.BMD");
    REQUIRE(is_bmd(test::span_of(buf)));
    auto r = BmdView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->file_size() == 0x6E);
    CHECK(r->relocation_offset() == 0x6C);
    CHECK(r->relocation_size() == 2);
    CHECK(r->speaker_names().empty());
    REQUIRE(r->messages().size() == 1);
    const BmdMessage& m = r->messages()[0];
    CHECK(m.type == BmdMessageType::Dialogue);
    CHECK(m.name == "tutorial_000");
    CHECK(m.speaker_id == 0xFFFF);
    CHECK(m.offset == 0x38);
    REQUIRE(m.lines.size() == 1);
    // f2 08 ff ff f1 3f "Tutorial" 0a (trailing zero fill trimmed)
    CHECK(m.lines[0].size() == 15);
    CHECK(bmd_line_to_text(m.lines[0]) == "{F2 08 FF FF}{F1 3F}Tutorial\n");

    auto toks = bmd_tokenize(m.lines[0]);
    REQUIRE(toks.size() == 11);
    CHECK(toks[0].kind == BmdTokenKind::Control);
    CHECK(toks[0].control_func == 0x08);
    CHECK(toks[0].raw.size() == 4);
    CHECK(toks[1].kind == BmdTokenKind::Control);
    CHECK(toks[1].raw.size() == 2);
    CHECK(toks[2].kind == BmdTokenKind::Ascii);
    CHECK(toks[10].kind == BmdTokenKind::NewLine);

    // Relocation table "07 16": run of 2 words (0x24, 0x28), then +44 -> 0x54.
    auto rel = r->relocations();
    REQUIRE(rel.size() == 3);
    CHECK(rel[0] == 0x24);
    CHECK(rel[1] == 0x28);
    CHECK(rel[2] == 0x54);
}

TEST_CASE("BMD: DATQUESTHELP.BMD has 200 dialogue messages and one pointer per entry and line") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/HELP/DATQUESTHELP.BMD");
    auto r = BmdView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->file_size() == buf.size());
    REQUIRE(r->messages().size() == 200);
    CHECK(r->messages()[0].name == "quest_000");
    CHECK(r->speaker_names().empty());
    std::size_t lines = 0;
    for (const BmdMessage& m : r->messages()) {
        CHECK(m.type == BmdMessageType::Dialogue);
        lines += m.lines.size();
        for (Bytes l : m.lines) {
            for (const BmdToken& t : bmd_tokenize(l)) CHECK(t.kind != BmdTokenKind::Invalid);
        }
    }
    CHECK(lines == 200);
    // 200 entry pointers + 1 speaker-table pointer + 200 line pointers.
    CHECK(r->relocations().size() == 401);
    CHECK(r->relocation_offset() + r->relocation_size() == buf.size());
}

TEST_CASE("BMD: MSG_QUEST.BMD carries a speaker-name table") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/FACILITY/MSG_QUEST.BMD");
    auto r = BmdView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    REQUIRE(r->speaker_names().size() == 1);
    CHECK_FALSE(r->speaker_names()[0].empty());
    CHECK(r->messages().size() == 200);
    CHECK(r->relocations().size() == 402);
}

TEST_CASE("BMD: glyph index follows the PersonaEditor convention") {
    // 80 B2 = wide 'R' (community observation): (0x80-0x81)*0x80 + 0xB2 + 0x20 = 0x52.
    const std::byte line[] = {std::byte{0x80}, std::byte{0xB2}, std::byte{0x81}, std::byte{0x80}, std::byte{0xF1}};
    auto toks = bmd_tokenize(Bytes{line, 5});
    REQUIRE(toks.size() == 3);
    CHECK(toks[0].kind == BmdTokenKind::Glyph);
    CHECK(toks[0].glyph_index == 0x52);
    CHECK(toks[1].glyph_index == 0xA0);
    CHECK(toks[2].kind == BmdTokenKind::Invalid);  // F1 needs 2 bytes
    CHECK(bmd_line_to_text(Bytes{line, 5}) == "R{G:00A0}{!F1}");
}

TEST_CASE("BMD: negative cases") {
    SUBCASE("bad magic") {
        std::vector<std::byte> b(0x40, std::byte{0});
        b[0] = std::byte{7};
        std::memcpy(b.data() + 8, "MSG0", 4);
        auto r = BmdView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::BadMagic);
    }
    SUBCASE("truncated") {
        std::vector<std::byte> b(0x10, std::byte{0});
        auto r = BmdView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
    SUBCASE("message table overruns") {
        std::vector<std::byte> b(0x30, std::byte{0});
        b[0] = std::byte{7};
        std::memcpy(b.data() + 8, "MSG1", 4);
        const u32 size = 0x30, count = 1000, ver = 0x20000;
        std::memcpy(b.data() + 4, &size, 4);
        std::memcpy(b.data() + 0x18, &count, 4);
        std::memcpy(b.data() + 0x1C, &ver, 4);
        auto r = BmdView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
    SUBCASE("unsupported version word") {
        std::vector<std::byte> b(0x40, std::byte{0});
        b[0] = std::byte{7};
        std::memcpy(b.data() + 8, "MSG1", 4);
        const u32 size = 0x40, ver = 0x10000;
        std::memcpy(b.data() + 4, &size, 4);
        std::memcpy(b.data() + 0x1C, &ver, 4);
        auto r = BmdView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Unsupported);
    }
}
