#include "p3fes/formats/bf.h"

#include <cstring>

namespace p3fes::formats {

namespace {
constexpr std::string_view kOpcodeNames[kBfOpcodeCount] = {
    "PUSHI", "PUSHF", "PUSHIX", "PUSHIF", "PUSHREG", "POPIX", "POPFX", "PROC", "COMM", "END",
    "JUMP", "CALL", "RUN", "GOTO", "ADD", "SUB", "MUL", "DIV", "MINUS", "NOT", "OR", "AND",
    "EQ", "NEQ", "S", "L", "SE", "LE", "IF", "PUSHIS", "PUSHLIX", "PUSHLFX", "POPLIX", "POPLFX",
    "PUSHSTR",
};
inline constexpr std::size_t kBfHeaderSize = 0x20;
inline constexpr std::size_t kBfSectionDescSize = 0x10;
inline constexpr std::size_t kBfLabelSize = 0x20;
}  // namespace

std::string_view bf_opcode_name(u16 opcode) {
    return opcode < kBfOpcodeCount ? kOpcodeNames[opcode] : std::string_view{"op_??"};
}

bool is_bf(Bytes buf) {
    return buf.size() >= kBfHeaderSize && std::memcmp(buf.data() + 8, "FLW0", 4) == 0;
}

Result<BfView> BfView::parse(Bytes buf) {
    if (buf.size() < kBfHeaderSize) return {FormatError::Truncated, "header (0x20 bytes)"};
    Reader r(buf);
    BfView v;
    const u32 w0 = r.u32le();
    v.string_section_offset_ = r.u32le();
    if (!r.match("FLW0")) return {FormatError::BadMagic, "FLW0"};
    const u32 w0c = r.u32le();
    const u32 nsec = r.u32le();
    v.word14_ = r.u32le();
    const u32 w18 = r.u32le();
    const u32 w1c = r.u32le();
    if (w0 != 0 || w0c != 0 || w18 != 0 || w1c != 0) return {FormatError::BadHeader, "reserved words"};
    if (nsec == 0 || nsec > 64) return {FormatError::BadHeader, "section count"};
    if (!in_bounds(buf, kBfHeaderSize, static_cast<std::size_t>(nsec) * kBfSectionDescSize))
        return {FormatError::Truncated, "section table"};

    v.buf_ = buf;
    v.sections_.reserve(nsec);
    for (u32 i = 0; i < nsec; ++i) {
        BfSection s;
        s.type = r.u32le();
        s.element_size = r.u32le();
        s.element_count = r.u32le();
        s.offset = r.u32le();
        const u64 bytes = s.byte_size();
        if (s.offset > buf.size() || bytes > buf.size() - s.offset) return {FormatError::Overrun, "section"};
        v.sections_.push_back(s);
    }
    // Observed on all 40 files: types 0..4 in order, contiguous, element sizes
    // 32/32/4/1/1, and the header size word equals the string section offset.
    for (const BfSection& s : v.sections_) {
        if ((s.type == 0 || s.type == 1) && s.element_size != kBfLabelSize)
            return {FormatError::Unsupported, "label size"};
        if (s.type == 2 && s.element_size != 4) return {FormatError::Unsupported, "instruction size"};
    }
    return v;
}

Bytes BfView::section_bytes(u32 type) const {
    for (const BfSection& s : sections_) {
        if (s.type == type) return subspan_or_empty(buf_, s.offset, static_cast<std::size_t>(s.byte_size()));
    }
    return {};
}

std::vector<BfLabel> BfView::labels(u32 type) const {
    std::vector<BfLabel> out;
    for (const BfSection& s : sections_) {
        if (s.type != type || s.element_size != kBfLabelSize) continue;
        out.reserve(s.element_count);
        for (u32 i = 0; i < s.element_count; ++i) {
            const std::size_t at = s.offset + static_cast<std::size_t>(i) * kBfLabelSize;
            BfLabel l;
            l.name = cstr_field(buf_.subspan(at, 24));
            l.instruction_index = ld_u32le(buf_, at + 24);
            l.reserved = ld_u32le(buf_, at + 28);
            out.push_back(l);
        }
    }
    return out;
}

u32 BfView::instruction_word_count() const {
    for (const BfSection& s : sections_)
        if (s.type == 2) return s.element_count;
    return 0;
}

FormatError BfView::decode_instructions(std::vector<BfInstruction>& out) const {
    Bytes code = section_bytes(2);
    const u32 words = static_cast<u32>(code.size() / 4);
    out.reserve(words);
    for (u32 i = 0; i < words;) {
        BfInstruction ins;
        ins.index = i;
        ins.opcode = ld_u16le(code, static_cast<std::size_t>(i) * 4);
        ins.operand = ld_u16le(code, static_cast<std::size_t>(i) * 4 + 2);
        ++i;
        if (bf_opcode_has_value(ins.opcode)) {
            if (i >= words) {
                out.push_back(ins);
                return FormatError::Corrupt;
            }
            ins.value = ld_u32le(code, static_cast<std::size_t>(i) * 4);
            ins.has_value = true;
            ++i;
        }
        out.push_back(ins);
    }
    return FormatError::None;
}

}  // namespace p3fes::formats
