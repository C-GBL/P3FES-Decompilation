// CRI AFS archive (DATA/SOUND/V*.AFS, 366 files). Little-endian.
//   "AFS\0", u32 count, count x {u32 offset, u32 size}, {u32 name_block_offset,
//   u32 name_block_size}; members 2048-aligned; name block (48 B/entry) at
//   align_up(last member end, 2048). Entry enumeration only (docs/FORMATS.md §7).
#pragma once

#include <string_view>
#include <vector>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

struct AfsTimestamp {
    u16 year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
};

struct AfsEntry {
    u32 offset = 0;
    u32 size = 0;
    std::string_view name;  // from the name block; empty if the block is missing
    AfsTimestamp timestamp;
    u32 name_record_tail = 0;  // u32 at name record +44; meaning not established
    Bytes data;
};

class AfsView {
public:
    static Result<AfsView> parse(Bytes buf);

    [[nodiscard]] const std::vector<AfsEntry>& entries() const { return entries_; }
    [[nodiscard]] u32 name_block_offset() const { return name_block_offset_; }
    [[nodiscard]] u32 name_block_size() const { return name_block_size_; }
    [[nodiscard]] bool has_names() const { return has_names_; }

private:
    std::vector<AfsEntry> entries_;
    u32 name_block_offset_ = 0;
    u32 name_block_size_ = 0;
    bool has_names_ = false;
};

bool is_afs(Bytes buf);

}  // namespace p3fes::formats
