#include "p3fes/formats/pak.h"

#include <cctype>

namespace p3fes::formats {

namespace {

// A valid non-terminator header: printable NUL-terminated name and a payload
// that fits in the remaining buffer.
bool header_valid(Bytes buf, std::size_t off, std::string_view& name, u32& size) {
    if (!in_bounds(buf, off, kPakHeaderSize)) return false;
    name = cstr_field(buf.subspan(off, kPakNameSize));
    if (name.empty() || name.size() == kPakNameSize || !is_printable_ascii(name)) return false;
    size = ld_u32le(buf, off + kPakNameSize);
    return in_bounds(buf, off + kPakHeaderSize, size);
}

bool is_terminator(Bytes buf, std::size_t off) {
    return in_bounds(buf, off, kPakHeaderSize) && ld_u8(buf, off) == 0 &&
           ld_u32le(buf, off + kPakNameSize) == 0;
}

bool iequals(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i)
        if (std::tolower(static_cast<unsigned char>(a[i])) != std::tolower(static_cast<unsigned char>(b[i])))
            return false;
    return true;
}

}  // namespace

bool looks_like_pak(Bytes buf) {
    std::string_view name;
    u32 size = 0;
    if (header_valid(buf, 0, name, size)) {
        // Every entry name on disc has an extension; tables that happen to start
        // with short ASCII ("3\0", "BED400\0", "CIN\0", "RESET\0") do not.
        if (name.find('.') == std::string_view::npos) return false;
        // Second-header rule: after the first payload (64-aligned) there must be
        // another valid header, a terminator, or exactly EOF.
        const std::size_t next = align_up(kPakHeaderSize + size, kPakEntryAlign);
        if (next == buf.size()) return true;
        std::string_view n2;
        u32 s2 = 0;
        return is_terminator(buf, next) || header_valid(buf, next, n2, s2);
    }
    // Terminator-only PAK (six BUSTUP .BINs are exactly 256 zero bytes).
    if (buf.size() == kPakHeaderSize) {
        for (std::byte b : buf)
            if (b != std::byte{0}) return false;
        return true;
    }
    return false;
}

bool is_nested_pak(const PakEntry& e) {
    std::string_view name;
    u32 size = 0;
    return header_valid(e.data, 0, name, size);
}

Result<PakView> PakView::parse(Bytes buf) {
    PakView v;
    v.buf_ = buf;
    if (buf.size() < kPakHeaderSize) return {FormatError::Truncated, "first header"};

    std::size_t off = 0;
    for (;;) {
        if (off == buf.size() && !v.entries_.empty()) {
            v.eof_terminated_ = true;
            v.terminator_offset_ = off;
            break;
        }
        if (!in_bounds(buf, off, kPakHeaderSize)) {
            return {FormatError::Truncated, v.entries_.empty() ? "first header" : "terminator"};
        }
        if (ld_u8(buf, off) == 0) {
            if (!is_terminator(buf, off)) return {FormatError::BadHeader, "terminator size != 0"};
            v.terminator_offset_ = off;
            break;
        }
        std::string_view name;
        u32 size = 0;
        if (!header_valid(buf, off, name, size)) {
            if (v.entries_.empty()) return {FormatError::BadMagic, "entry name"};
            return in_bounds(buf, off + kPakHeaderSize, ld_u32le(buf, off + kPakNameSize))
                       ? Result<PakView>{FormatError::BadHeader, "entry name"}
                       : Result<PakView>{FormatError::Overrun, "entry size"};
        }
        PakEntry e;
        e.name = name;
        e.header_offset = off;
        e.data = buf.subspan(off + kPakHeaderSize, size);
        v.entries_.push_back(e);
        off = align_up(off + kPakHeaderSize + size, kPakEntryAlign);
        if (off > buf.size()) {
            // Payload ended inside the final alignment pad: the file is shorter
            // than the padded size. Not observed on disc; report as truncated.
            return {FormatError::Truncated, "alignment pad"};
        }
    }
    return v;
}

const PakEntry* PakView::find(std::string_view name, bool case_insensitive) const {
    for (const PakEntry& e : entries_) {
        if (case_insensitive ? iequals(e.name, name) : e.name == name) return &e;
    }
    return nullptr;
}

}  // namespace p3fes::formats
