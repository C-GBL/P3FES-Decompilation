// Atlus name-first PAK container (.PAC/.BIN/.FPC/.CPK/.SE/.PAK, ~3,100 files).
//
// Layout observed on the NTSC-U disc (docs/FORMATS.md §1):
//   entry: char name[252] (NUL-terminated, printable ASCII, junk allowed after
//          the NUL) + u32 LE size, then `size` payload bytes.
//   The next entry header starts at align_up(payload_end, 64); the pad bytes
//   are usually zero but may be leftover junk.
//   Terminator: an entry whose name[0] == 0 (size 0; the remaining name bytes
//   may be junk). Five cut-in .CPK files have no terminator and end exactly at
//   the aligned payload end — accepted and reported via `eof_terminated`.
#pragma once

#include <string_view>
#include <vector>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

struct PakEntry {
    std::string_view name;  // view into the buffer, no copy
    Bytes data;
    std::size_t header_offset = 0;  // offset of the 256-byte entry header
};

inline constexpr std::size_t kPakNameSize = 252;
inline constexpr std::size_t kPakHeaderSize = 256;
inline constexpr std::size_t kPakEntryAlign = 64;

class PakView {
public:
    static Result<PakView> parse(Bytes buf);

    [[nodiscard]] const std::vector<PakEntry>& entries() const { return entries_; }
    [[nodiscard]] const PakEntry* find(std::string_view name, bool case_insensitive = true) const;

    // True when the walk reached EOF at an aligned payload end without seeing
    // an empty-name terminator header.
    [[nodiscard]] bool eof_terminated() const { return eof_terminated_; }
    // Offset of the terminator header, or buffer size when eof_terminated().
    [[nodiscard]] std::size_t terminator_offset() const { return terminator_offset_; }
    [[nodiscard]] Bytes buffer() const { return buf_; }

private:
    Bytes buf_;
    std::vector<PakEntry> entries_;
    bool eof_terminated_ = false;
    std::size_t terminator_offset_ = 0;
};

// Cheap header sniff: a first entry with a printable NUL-terminated name whose
// payload fits in the buffer, or a 256-byte all-zero terminator-only PAK.
bool looks_like_pak(Bytes buf);

// True when an entry's payload itself starts with a valid PAK entry header.
bool is_nested_pak(const PakEntry& e);

}  // namespace p3fes::formats
