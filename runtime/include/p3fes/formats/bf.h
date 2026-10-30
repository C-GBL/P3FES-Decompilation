// Atlus flow script container ("FLW0" at +8; DATA/FIELD/SCRIPT/*.BF and
// DATA/SCRIPT/EVENT/*.BF, 40 top-level files). Little-endian.
//
//   +00 u32 0   +04 u32 string-section offset (== offset of section 4)
//   +08 "FLW0"  +0C u32 0   +10 u32 section count (5)   +14 u32 ? (0 in all 40)
//   +18 u32 0   +1C u32 0
//   +20 count x {u32 type, u32 element size, u32 element count, u32 offset}
//   sections are contiguous and in type order 0..4:
//     0 procedure labels (32 B: char name[24], u32 instruction index, u32 0)
//     1 jump labels      (32 B, same layout)
//     2 instructions     (4 B words: u16 opcode, u16 operand; PUSHI/PUSHF take
//                         one extra 32-bit value word)
//     3 message data     (1 B units: an embedded MSG1/BMD file)
//     4 string table     (1 B units)
// This decodes the instruction stream to records; it is not a VM
// (docs/FORMATS.md §2).
#pragma once

#include <string_view>
#include <vector>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

// Descriptive names (community convention); semantics are Phase 2/5 work.
enum class BfOpcode : u16 {
    PUSHI = 0, PUSHF = 1, PUSHIX = 2, PUSHIF = 3, PUSHREG = 4, POPIX = 5, POPFX = 6, PROC = 7,
    COMM = 8, END = 9, JUMP = 10, CALL = 11, RUN = 12, GOTO = 13, ADD = 14, SUB = 15, MUL = 16,
    DIV = 17, MINUS = 18, NOT = 19, OR = 20, AND = 21, EQ = 22, NEQ = 23, S = 24, L = 25,
    SE = 26, LE = 27, IF = 28, PUSHIS = 29, PUSHLIX = 30, PUSHLFX = 31, POPLIX = 32, POPLFX = 33,
    PUSHSTR = 34,
};
inline constexpr u16 kBfOpcodeCount = 35;
std::string_view bf_opcode_name(u16 opcode);  // "op_NN" for unknown values
constexpr bool bf_opcode_has_value(u16 op) { return op == 0 || op == 1; }

struct BfSection {
    u32 type = 0;
    u32 element_size = 0;
    u32 element_count = 0;
    u32 offset = 0;
    [[nodiscard]] u64 byte_size() const { return static_cast<u64>(element_size) * element_count; }
};

struct BfLabel {
    std::string_view name;
    u32 instruction_index = 0;
    u32 reserved = 0;  // observed 0
};

struct BfInstruction {
    u32 index = 0;      // word index into the instruction section
    u16 opcode = 0;
    u16 operand = 0;
    u32 value = 0;      // PUSHI: s32 immediate, PUSHF: f32 bits
    bool has_value = false;
};

class BfView {
public:
    static Result<BfView> parse(Bytes buf);

    [[nodiscard]] u32 string_section_offset() const { return string_section_offset_; }
    [[nodiscard]] u32 header_word_14() const { return word14_; }
    [[nodiscard]] const std::vector<BfSection>& sections() const { return sections_; }
    [[nodiscard]] Bytes section_bytes(u32 type) const;

    [[nodiscard]] std::vector<BfLabel> procedures() const { return labels(0); }
    [[nodiscard]] std::vector<BfLabel> jump_labels() const { return labels(1); }
    [[nodiscard]] u32 instruction_word_count() const;
    // Decodes every instruction. Returns Corrupt if a PUSHI/PUSHF value word
    // runs past the section; the records decoded so far are kept in `out`.
    [[nodiscard]] FormatError decode_instructions(std::vector<BfInstruction>& out) const;
    [[nodiscard]] Bytes message_data() const { return section_bytes(3); }  // MSG1 for BmdView
    [[nodiscard]] Bytes string_table() const { return section_bytes(4); }

private:
    std::vector<BfLabel> labels(u32 type) const;

    Bytes buf_;
    std::vector<BfSection> sections_;
    u32 string_section_offset_ = 0;
    u32 word14_ = 0;
};

bool is_bf(Bytes buf);

}  // namespace p3fes::formats
