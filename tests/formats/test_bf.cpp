#include <doctest.h>

#include <cstring>

#include "fixtures.h"
#include "p3fes/formats/bf.h"
#include "p3fes/formats/bmd.h"

using namespace p3fes;
using namespace p3fes::formats;

TEST_CASE("BF: DUNGEONAT00.BF (519 bytes) has one procedure, three words and an embedded MSG1") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/FIELD/SCRIPT/DUNGEONAT00.BF");
    REQUIRE(is_bf(test::span_of(buf)));
    auto r = BfView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    REQUIRE(r->sections().size() == 5);
    for (u32 i = 0; i < 5; ++i) CHECK(r->sections()[i].type == i);
    CHECK(r->string_section_offset() == 0x117);
    CHECK(r->sections()[4].offset == 0x117);
    CHECK(r->sections()[4].byte_size() == 0xF0);
    CHECK(r->sections()[4].offset + r->sections()[4].byte_size() == buf.size());
    CHECK(r->header_word_14() == 0);

    auto procs = r->procedures();
    REQUIRE(procs.size() == 1);
    CHECK(procs[0].name == "dng_init_00");
    CHECK(procs[0].instruction_index == 0);
    CHECK(procs[0].reserved == 0);
    CHECK(r->jump_labels().empty());

    std::vector<BfInstruction> ins;
    CHECK(r->decode_instructions(ins) == FormatError::None);
    REQUIRE(ins.size() == 3);
    CHECK(ins[0].opcode == static_cast<u16>(BfOpcode::PROC));
    CHECK(ins[0].operand == 0);
    CHECK(ins[1].opcode == static_cast<u16>(BfOpcode::END));
    CHECK(ins[2].opcode == static_cast<u16>(BfOpcode::END));
    CHECK(bf_opcode_name(ins[0].opcode) == "PROC");

    // Section 3 is a complete MSG1 file: one selection message "YESNO_SEL".
    Bytes msg = r->message_data();
    REQUIRE(msg.size() == 0x7B);
    REQUIRE(is_bmd(msg));
    auto bmd = BmdView::parse(msg);
    REQUIRE(bmd.ok());
    REQUIRE(bmd->messages().size() == 1);
    CHECK(bmd->messages()[0].type == BmdMessageType::Selection);
    CHECK(bmd->messages()[0].name == "YESNO_SEL");
    REQUIRE(bmd->messages()[0].lines.size() == 2);
    CHECK(bmd_line_to_text(bmd->messages()[0].lines[0]) == "{F2 08 FF FF}{F1 3F}Yes");
    CHECK(bmd_line_to_text(bmd->messages()[0].lines[1]) == "{F2 08 FF FF}{F1 3F}No");
}

TEST_CASE("BF: LMAP.BF section table, label targets and instruction stream are consistent") {
    P3FES_REQUIRE_FIXTURE(buf, "DATA/FIELD/SCRIPT/LMAP.BF");
    auto r = BfView::parse(test::span_of(buf));
    REQUIRE(r.ok());
    CHECK(r->procedures().size() == 7);
    CHECK(r->jump_labels().size() == 10);
    CHECK(r->instruction_word_count() == 449);
    CHECK(r->message_data().size() == 130);
    CHECK(r->string_table().size() == 240);
    CHECK(r->string_section_offset() == 2582);

    std::vector<BfInstruction> ins;
    REQUIRE(r->decode_instructions(ins) == FormatError::None);
    // Every procedure label points at a PROC whose operand is the label index;
    // every jump label points inside the stream.
    std::size_t words = 0;
    for (const BfInstruction& i : ins) {
        words += i.has_value ? 2 : 1;
        CHECK(i.opcode < kBfOpcodeCount);
    }
    CHECK(words == 449);
    auto at_word = [&](u32 w) -> const BfInstruction* {
        for (const BfInstruction& i : ins)
            if (i.index == w) return &i;
        return nullptr;
    };
    u32 k = 0;
    for (const BfLabel& p : r->procedures()) {
        const BfInstruction* i = at_word(p.instruction_index);
        REQUIRE(i != nullptr);
        CHECK(i->opcode == static_cast<u16>(BfOpcode::PROC));
        CHECK(i->operand == k++);
    }
    for (const BfLabel& j : r->jump_labels()) CHECK(j.instruction_index < 449);
    CHECK(is_bmd(r->message_data()));
}

TEST_CASE("BF: negative cases") {
    SUBCASE("bad magic") {
        std::vector<std::byte> b(0x70, std::byte{0});
        std::memcpy(b.data() + 8, "FLW1", 4);
        auto r = BfView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::BadMagic);
        CHECK_FALSE(is_bf(test::span_of(b)));
    }
    SUBCASE("truncated header") {
        std::vector<std::byte> b(0x10, std::byte{0});
        std::memcpy(b.data() + 8, "FLW0", 4);
        auto r = BfView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
    SUBCASE("section table runs past the buffer") {
        std::vector<std::byte> b(0x20, std::byte{0});
        std::memcpy(b.data() + 8, "FLW0", 4);
        const u32 five = 5;
        std::memcpy(b.data() + 0x10, &five, 4);
        auto r = BfView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Truncated);
    }
    SUBCASE("section offset overruns") {
        std::vector<std::byte> b(0x70, std::byte{0});
        std::memcpy(b.data() + 8, "FLW0", 4);
        const u32 one = 1, size = 32, count = 1000, off = 0x30;
        std::memcpy(b.data() + 0x10, &one, 4);
        std::memcpy(b.data() + 0x20, &one, 4);  // type (unused)
        std::memcpy(b.data() + 0x24, &size, 4);
        std::memcpy(b.data() + 0x28, &count, 4);
        std::memcpy(b.data() + 0x2C, &off, 4);
        auto r = BfView::parse(test::span_of(b));
        REQUIRE_FALSE(r.ok());
        CHECK(r.code() == FormatError::Overrun);
    }
    SUBCASE("PUSHI missing its value word is reported as Corrupt") {
        // Header + one instruction section of a single PUSHI word.
        std::vector<std::byte> b(0x20 + 0x10 + 4, std::byte{0});
        std::memcpy(b.data() + 8, "FLW0", 4);
        const u32 one = 1, two = 2, four = 4, off = 0x30;
        std::memcpy(b.data() + 0x10, &one, 4);
        std::memcpy(b.data() + 0x20, &two, 4);
        std::memcpy(b.data() + 0x24, &four, 4);
        std::memcpy(b.data() + 0x28, &one, 4);
        std::memcpy(b.data() + 0x2C, &off, 4);
        auto r = BfView::parse(test::span_of(b));
        REQUIRE(r.ok());
        std::vector<BfInstruction> ins;
        CHECK(r->decode_instructions(ins) == FormatError::Corrupt);
        CHECK(ins.size() == 1);
    }
}
