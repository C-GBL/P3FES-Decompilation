#include "p3fes/formats/afs.h"

#include <cstring>

namespace p3fes::formats {

namespace {
inline constexpr std::size_t kNameRecordSize = 48;
inline constexpr std::size_t kNameFieldSize = 32;
}  // namespace

bool is_afs(Bytes buf) {
    return buf.size() >= 8 && std::memcmp(buf.data(), "AFS\0", 4) == 0;
}

Result<AfsView> AfsView::parse(Bytes buf) {
    Reader r(buf);
    // Note the explicit length: a bare "AFS\0" literal would build a 3-char view.
    if (!r.match(std::string_view{"AFS\0", 4}))
        return {r.failed() ? FormatError::Truncated : FormatError::BadMagic, "AFS\\0"};
    const u32 count = r.u32le();
    if (r.failed()) return {FormatError::Truncated, "count"};
    if (!in_bounds(buf, 8, static_cast<std::size_t>(count) * 8 + 8))
        return {FormatError::Truncated, "entry table"};

    AfsView v;
    v.entries_.reserve(count);
    for (u32 i = 0; i < count; ++i) {
        AfsEntry e;
        e.offset = r.u32le();
        e.size = r.u32le();
        if (!in_bounds(buf, e.offset, e.size)) return {FormatError::Overrun, "entry offset/size"};
        e.data = buf.subspan(e.offset, e.size);
        v.entries_.push_back(e);
    }
    // The name-block descriptor follows the entry table (at 8 + 8*count). Other
    // CRI tools also accept it at 0x7F8; every file on this disc uses the former.
    v.name_block_offset_ = r.u32le();
    v.name_block_size_ = r.u32le();
    if (r.failed()) return {FormatError::Truncated, "name block descriptor"};

    if (v.name_block_offset_ != 0 && v.name_block_size_ != 0) {
        if (!in_bounds(buf, v.name_block_offset_, v.name_block_size_))
            return {FormatError::Overrun, "name block"};
        if (v.name_block_size_ >= kNameRecordSize * static_cast<std::size_t>(count)) {
            v.has_names_ = true;
            for (u32 i = 0; i < count; ++i) {
                const std::size_t rec = v.name_block_offset_ + kNameRecordSize * i;
                AfsEntry& e = v.entries_[i];
                e.name = cstr_field(buf.subspan(rec, kNameFieldSize));
                e.timestamp.year = ld_u16le(buf, rec + 32);
                e.timestamp.month = ld_u16le(buf, rec + 34);
                e.timestamp.day = ld_u16le(buf, rec + 36);
                e.timestamp.hour = ld_u16le(buf, rec + 38);
                e.timestamp.minute = ld_u16le(buf, rec + 40);
                e.timestamp.second = ld_u16le(buf, rec + 42);
                e.name_record_tail = ld_u32le(buf, rec + 44);
            }
        }
    }
    return v;
}

}  // namespace p3fes::formats
