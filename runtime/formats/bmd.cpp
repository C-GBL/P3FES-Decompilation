#include "p3fes/formats/bmd.h"

#include <cstring>

namespace p3fes::formats {

namespace {
inline constexpr std::size_t kBmdHeaderSize = 0x20;
inline constexpr u32 kBmdPointerBase = 0x20;
inline constexpr std::size_t kBmdNameSize = 24;
inline constexpr u32 kBmdVersion = 0x00020000;

constexpr char kHex[] = "0123456789ABCDEF";
void append_hex_byte(std::string& s, u8 b) {
    s.push_back(kHex[b >> 4]);
    s.push_back(kHex[b & 0xF]);
}
}  // namespace

bool is_bmd(Bytes buf) {
    return buf.size() >= kBmdHeaderSize && ld_u32le(buf, 0) == 7 &&
           std::memcmp(buf.data() + 8, "MSG1", 4) == 0;
}

std::vector<BmdToken> bmd_tokenize(Bytes line) {
    std::vector<BmdToken> out;
    std::size_t i = 0;
    while (i < line.size()) {
        const u8 c = ld_u8(line, i);
        BmdToken t;
        if (c >= 0xF0) {
            // Control code: total length 2 * low nibble (F1 = 2 bytes ... FF = 30).
            const std::size_t len = 2u * (c & 0xF);
            if (len == 0 || i + len > line.size()) {
                t.kind = BmdTokenKind::Invalid;
                t.raw = line.subspan(i);
                out.push_back(t);
                break;
            }
            t.kind = BmdTokenKind::Control;
            t.raw = line.subspan(i, len);
            t.control_func = ld_u8(line, i + 1);
            i += len;
        } else if (c >= 0x80) {
            if (i + 2 > line.size()) {
                t.kind = BmdTokenKind::Invalid;
                t.raw = line.subspan(i);
                out.push_back(t);
                break;
            }
            t.kind = BmdTokenKind::Glyph;
            t.raw = line.subspan(i, 2);
            const int idx = (static_cast<int>(c) - 0x81) * 0x80 + ld_u8(line, i + 1) + 0x20;
            t.glyph_index = static_cast<u16>(idx < 0 ? 0 : idx);
            i += 2;
        } else {
            t.kind = c == 0x0A ? BmdTokenKind::NewLine : BmdTokenKind::Ascii;
            t.raw = line.subspan(i, 1);
            i += 1;
        }
        out.push_back(t);
    }
    return out;
}

std::string bmd_line_to_text(Bytes line) {
    std::string s;
    s.reserve(line.size());
    for (const BmdToken& t : bmd_tokenize(line)) {
        switch (t.kind) {
        case BmdTokenKind::Ascii: {
            const u8 c = ld_u8(t.raw, 0);
            if (c >= 0x20 && c <= 0x7E) {
                s.push_back(static_cast<char>(c));
            } else {
                s += "{";
                append_hex_byte(s, c);
                s += "}";
            }
            break;
        }
        case BmdTokenKind::NewLine:
            s.push_back('\n');
            break;
        case BmdTokenKind::Glyph:
            if (t.glyph_index >= 0x20 && t.glyph_index < 0x80) {
                s.push_back(static_cast<char>(t.glyph_index));
            } else {
                s += "{G:";
                append_hex_byte(s, static_cast<u8>(t.glyph_index >> 8));
                append_hex_byte(s, static_cast<u8>(t.glyph_index & 0xFF));
                s += "}";
            }
            break;
        case BmdTokenKind::Control:
        case BmdTokenKind::Invalid:
            s += t.kind == BmdTokenKind::Invalid ? "{!" : "{";
            for (std::size_t i = 0; i < t.raw.size(); ++i) {
                if (i) s.push_back(' ');
                append_hex_byte(s, ld_u8(t.raw, i));
            }
            s += "}";
            break;
        }
    }
    return s;
}

Result<BmdView> BmdView::parse(Bytes buf) {
    if (buf.size() < kBmdHeaderSize) return {FormatError::Truncated, "header (0x20 bytes)"};
    Reader r(buf);
    BmdView v;
    const u32 type = r.u32le();
    v.file_size_ = r.u32le();
    if (!r.match("MSG1")) return {FormatError::BadMagic, "MSG1"};
    const u32 zero = r.u32le();
    v.reloc_offset_ = r.u32le();
    v.reloc_size_ = r.u32le();
    const u32 count = r.u32le();
    const u32 version = r.u32le();
    if (type != 7 || zero != 0) return {FormatError::BadHeader, "type/zero"};
    if (version != kBmdVersion) return {FormatError::Unsupported, "version != 0x00020000"};
    if (v.file_size_ > buf.size()) return {FormatError::Overrun, "file size"};
    if (v.reloc_offset_ > buf.size() || v.reloc_size_ > buf.size() - v.reloc_offset_)
        return {FormatError::Overrun, "relocation table"};
    if (!in_bounds(buf, kBmdHeaderSize, static_cast<std::size_t>(count) * 8 + 16))
        return {FormatError::Truncated, "message table"};
    v.buf_ = buf;

    // Speaker-name table descriptor follows the message table.
    const std::size_t spk_desc = kBmdHeaderSize + static_cast<std::size_t>(count) * 8;
    const u32 spk_ptr = ld_u32le(buf, spk_desc);
    const u32 spk_count = ld_u32le(buf, spk_desc + 4);
    if (spk_count) {
        const std::size_t tbl = static_cast<std::size_t>(spk_ptr) + kBmdPointerBase;
        if (!in_bounds(buf, tbl, static_cast<std::size_t>(spk_count) * 4))
            return {FormatError::Overrun, "speaker table"};
        v.speakers_.reserve(spk_count);
        for (u32 i = 0; i < spk_count; ++i) {
            const std::size_t at = static_cast<std::size_t>(ld_u32le(buf, tbl + i * 4)) + kBmdPointerBase;
            if (at >= buf.size()) return {FormatError::Overrun, "speaker name"};
            v.speakers_.push_back(cstr_field(buf.subspan(at)));
        }
    }

    v.messages_.reserve(count);
    for (u32 i = 0; i < count; ++i) {
        const std::size_t ent = kBmdHeaderSize + static_cast<std::size_t>(i) * 8;
        BmdMessage m;
        const u32 mtype = ld_u32le(buf, ent);
        m.offset = static_cast<std::size_t>(ld_u32le(buf, ent + 4)) + kBmdPointerBase;
        if (mtype > 1) return {FormatError::Unsupported, "message type"};
        m.type = static_cast<BmdMessageType>(mtype);
        Reader mr(buf, 0);
        mr.seek(m.offset);
        m.name = cstr_field(mr.bytes(kBmdNameSize));
        u32 n = 0;
        if (m.type == BmdMessageType::Dialogue) {
            n = mr.u16le();
            m.speaker_id = mr.u16le();
        } else {
            const u16 z = mr.u16le();
            n = mr.u16le();
            m.selection_word = mr.u32le();
            if (!mr.failed() && z != 0) return {FormatError::BadHeader, "selection reserved u16"};
        }
        if (mr.failed()) return {FormatError::Truncated, "message record"};
        if (n) {
            const std::size_t ptrs = mr.pos();
            mr.skip(static_cast<std::size_t>(n) * 4);
            const u32 text_size = mr.u32le();
            if (mr.failed()) return {FormatError::Truncated, "line pointers"};
            const std::size_t text_start = mr.pos();
            if (!in_bounds(buf, text_start, text_size)) return {FormatError::Overrun, "text size"};
            const std::size_t text_end = text_start + text_size;
            m.lines.reserve(n);
            for (u32 k = 0; k < n; ++k) {
                const std::size_t a = static_cast<std::size_t>(ld_u32le(buf, ptrs + k * 4)) + kBmdPointerBase;
                const std::size_t b = k + 1 < n
                                          ? static_cast<std::size_t>(ld_u32le(buf, ptrs + (k + 1) * 4)) + kBmdPointerBase
                                          : text_end;
                if (a < text_start || b > text_end || a > b) return {FormatError::Overrun, "line pointer"};
                Bytes line = buf.subspan(a, b - a);
                // Strip trailing NULs: selection options are NUL-terminated and
                // the text block is zero-padded to 4 bytes after the last line.
                std::size_t len = line.size();
                while (len > 0 && line[len - 1] == std::byte{0}) --len;
                m.lines.push_back(line.first(len));
            }
        }
        v.messages_.push_back(std::move(m));
    }
    return v;
}

std::vector<u32> BmdView::relocations() const {
    std::vector<u32> out;
    u32 pos = kBmdPointerBase;
    std::size_t i = reloc_offset_;
    const std::size_t end = reloc_offset_ + reloc_size_;
    while (i < end) {
        const u8 v = ld_u8(buf_, i);
        if ((v & 1) == 0) {               // even byte: next pointer 2*v bytes ahead
            pos += 2u * v;
            out.push_back(pos);
            i += 1;
        } else if ((v & 7) == 7) {        // run of (v>>3)+2 consecutive words
            for (u32 k = 0; k < (static_cast<u32>(v) >> 3) + 2; ++k) {
                pos += 4;
                out.push_back(pos);
            }
            i += 1;
        } else if ((v & 3) == 1 && i + 1 < end) {  // two-byte delta: (v16 >> 2) words
            const u16 v16 = ld_u16le(buf_, i);
            pos += (static_cast<u32>(v16) >> 2) * 4;
            out.push_back(pos);
            i += 2;
        } else if ((v & 7) == 3 && i + 2 < end) {  // three-byte delta: (v24 >> 3) words
            const u32 v24 = ld_u8(buf_, i) | (ld_u8(buf_, i + 1) << 8) | (ld_u8(buf_, i + 2) << 16);
            pos += (v24 >> 3) * 4;
            out.push_back(pos);
            i += 3;
        } else {
            break;  // malformed; return what was decoded
        }
    }
    return out;
}

}  // namespace p3fes::formats
