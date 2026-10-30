// Atlus message file ("MSG1" at +8; 11 .BMD files plus the type-3 section of
// every .BF). Little-endian. All stored pointers are relative to +0x20.
//
//   +00 u32 7   +04 u32 file size   +08 "MSG1"   +0C u32 0
//   +10 u32 relocation table offset   +14 u32 relocation table size
//   +18 u32 message count   +1C u32 0x00020000
//   +20 count x {u32 type (0 dialogue, 1 selection), u32 ptr}
//   then {u32 speaker-name table ptr, u32 speaker count, u32 0, u32 0}
//   dialogue : char name[24], u16 line count, u16 speaker id (0xFFFF none),
//              u32 line ptr[count], u32 text size, text
//   selection: char name[24], u16 0, u16 option count, u32 ?, u32 ptr[count],
//              u32 text size, text
//   speaker table: u32 ptr[count] -> NUL-terminated names
//   relocation table (last): byte-coded deltas between pointer fields.
// Text: ASCII bytes, 0x0A newline, two-byte glyphs 0x80-0xEF xx, control codes
// 0xF1-0xFF with total length 2*(low nibble) (docs/FORMATS.md §3).
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

enum class BmdMessageType : u32 { Dialogue = 0, Selection = 1 };

struct BmdMessage {
    std::string_view name;
    BmdMessageType type = BmdMessageType::Dialogue;
    u16 speaker_id = 0xFFFF;      // dialogue only; index into speaker_names()
    u32 selection_word = 0;        // selection only; the u32 after the counts (meaning unknown)
    std::vector<Bytes> lines;      // raw encoded text per line/option
    std::size_t offset = 0;        // absolute offset of the message record
};

enum class BmdTokenKind : u8 {
    Ascii,     // one byte 0x20..0x7E (also 0x00..0x1F other than 0x0A, reported as Ascii with raw byte)
    NewLine,   // 0x0A
    Glyph,     // two bytes: 0x80..0xEF then any byte; glyph_index set
    Control,   // 0xF1..0xFF func params...; func set
    Invalid,   // truncated code at end of line
};

struct BmdToken {
    BmdTokenKind kind = BmdTokenKind::Ascii;
    Bytes raw;              // the exact bytes of the token
    u16 glyph_index = 0;    // Glyph: (b1 - 0x81) * 0x80 + b2 + 0x20 (PersonaEditor convention; < 0x80 is ASCII in the wide font)
    u8 control_func = 0;    // Control: second byte
};

// Splits one encoded line into tokens. Always consumes the whole span.
std::vector<BmdToken> bmd_tokenize(Bytes line);
// Renders a line as readable text: ASCII as-is, '\n' for 0x0A, control codes
// as {F2 08 FF FF}, glyphs as the ASCII letter when glyph_index < 0x80 else
// {G:xxxx}. Lossless for ASCII/newline; codes are preserved verbatim.
std::string bmd_line_to_text(Bytes line);

class BmdView {
public:
    static Result<BmdView> parse(Bytes buf);

    [[nodiscard]] const std::vector<BmdMessage>& messages() const { return messages_; }
    [[nodiscard]] const std::vector<std::string_view>& speaker_names() const { return speakers_; }
    [[nodiscard]] u32 relocation_offset() const { return reloc_offset_; }
    [[nodiscard]] u32 relocation_size() const { return reloc_size_; }
    [[nodiscard]] u32 file_size() const { return file_size_; }
    // Decodes the relocation table into absolute offsets of pointer fields.
    [[nodiscard]] std::vector<u32> relocations() const;

private:
    Bytes buf_;
    std::vector<BmdMessage> messages_;
    std::vector<std::string_view> speakers_;
    u32 reloc_offset_ = 0;
    u32 reloc_size_ = 0;
    u32 file_size_ = 0;
};

bool is_bmd(Bytes buf);

}  // namespace p3fes::formats
