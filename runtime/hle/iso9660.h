// Minimal ISO9660 reader over a DiscSource: PVD, directory records, path search.
// Private to runtime/hle; the single owner of ISO9660 interpretation for the disc sources,
// the CDVD search-file service and the kDiscLayout self-check.
//
// Scope (observed on the user's disc, DISC_LAYOUT §2/§7): one PVD, 2048-byte logical blocks,
// Level-1 style identifiers, no extended attributes, no interleave, no multi-extent files.
// Anything outside that scope is reported as Unsupported rather than guessed.
#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "p3fes/hle/disc_source.h"

namespace p3fes::hle::iso9660 {

inline constexpr u32 kPvdLsn = 16;
// Resource bound for one directory extent (the outer disc's largest directory is 1,288 B; CVM
// roots are <= 10,240 B).
inline constexpr u32 kMaxDirectoryBytes = 1u << 20;

struct Record {
    std::string identifier;  // raw, e.g. "DATA.CVM;1"; a single 0x00 / 0x01 byte for "." / ".."
    u32 lsn = 0;
    u32 size = 0;
    u8 flags = 0;  // bit 1 = directory
    std::size_t dir_offset = 0;  // byte offset of this record inside its directory extent (read_directory; 0 otherwise)
    std::array<u8, 7> recorded{};  // recording date and time (record bytes 18-24: years since 1900, month, day,
                                   // hour, minute, second, GMT offset in 15-minute units)

    bool is_directory() const { return (flags & 0x02) != 0; }
    bool is_self_or_parent() const {
        return identifier.size() == 1 && (identifier[0] == 0 || identifier[0] == 1);
    }
};

struct Volume {
    u32 volume_sectors = 0;  // PVD volume_space_size
    Record root;             // root directory record from the PVD
};

// BadMagic if no primary volume descriptor precedes the terminator; BadHeader if its logical
// block size is not 2048 or the root record is malformed.
Result<Volume> read_volume(DiscSource& disc);

// Records of a directory extent, excluding "." and "..".
Result<std::vector<Record>> read_directory(DiscSource& disc, const Volume& vol, const Record& dir);

// True if `query` (one path component) names the record: ASCII case-insensitive; a query
// without ";" ignores the record's ";N" version suffix.
bool component_matches(std::string_view record_identifier, std::string_view query);

// Splits on '\' and '/', dropping empty components (so "\A\B;1" -> {"A", "B;1"}).
std::vector<std::string_view> split_path(std::string_view path);

// Walks `path` from the root. Ok(nullopt) if a component is absent or an intermediate component
// is a file.
Result<std::optional<Record>> find(DiscSource& disc, const Volume& vol, std::string_view path);

// Reads a whole file (Unsupported if larger than max_bytes).
Result<std::vector<std::byte>> read_file(DiscSource& disc, const Record& file, u32 max_bytes);

}  // namespace p3fes::hle::iso9660
