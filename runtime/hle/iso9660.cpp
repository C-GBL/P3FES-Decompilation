#include "iso9660.h"

#include <cstring>

#include "p3fes/formats/bytes.h"

namespace p3fes::hle::iso9660 {

using formats::Bytes;
using formats::ld_u16le;
using formats::ld_u32le;
using formats::ld_u8;

namespace {

constexpr std::size_t kRecordFixed = 33;  // bytes before the identifier

char ascii_upper(char c) { return (c >= 'a' && c <= 'z') ? static_cast<char>(c - 'a' + 'A') : c; }

bool iequals(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i)
        if (ascii_upper(a[i]) != ascii_upper(b[i])) return false;
    return true;
}

// Parses one directory record (its length byte is non-zero and it lies inside one sector).
// `vol` == nullptr skips the extent bounds check (used for the PVD's own root record).
Result<Record> parse_record(Bytes rec, const Volume* vol) {
    if (rec.size() < kRecordFixed)
        return Error{FormatError::BadHeader, "ISO9660 directory record shorter than 33 bytes"};
    const std::size_t name_len = ld_u8(rec, 32);
    if (kRecordFixed + name_len > rec.size())
        return Error{FormatError::BadHeader, "ISO9660 directory record identifier overruns the record"};
    if (name_len == 0) return Error{FormatError::BadHeader, "ISO9660 directory record has an empty identifier"};
    if (ld_u8(rec, 1) != 0)
        return Error{FormatError::Unsupported, "ISO9660 extended attribute records are not modelled"};
    if (ld_u8(rec, 26) != 0 || ld_u8(rec, 27) != 0)
        return Error{FormatError::Unsupported, "ISO9660 interleaved files are not modelled"};
    Record r;
    r.lsn = ld_u32le(rec, 2);
    r.size = ld_u32le(rec, 10);
    r.flags = ld_u8(rec, 25);
    for (std::size_t i = 0; i < r.recorded.size(); ++i) r.recorded[i] = ld_u8(rec, 18 + i);
    if ((r.flags & 0x80) != 0) return Error{FormatError::Unsupported, "ISO9660 multi-extent files are not modelled"};
    r.identifier.assign(reinterpret_cast<const char*>(rec.data()) + kRecordFixed, name_len);
    if (vol != nullptr && r.size != 0) {
        const u64 end = static_cast<u64>(r.lsn) + (static_cast<u64>(r.size) + kSectorSize - 1) / kSectorSize;
        if (end > vol->volume_sectors) return Error{FormatError::BadHeader, "ISO9660 extent lies outside the volume"};
    }
    return r;
}

}  // namespace

Result<Volume> read_volume(DiscSource& disc) {
    std::vector<std::byte> sector(kSectorSize);
    // The descriptor set starts at LSN 16 and ends with a type-255 terminator; bound the scan.
    for (u32 lsn = kPvdLsn; lsn < kPvdLsn + 32 && lsn < disc.sector_count(); ++lsn) {
        auto rd = disc.read_sectors(lsn, 1, sector);
        if (!rd) return rd.error();
        const Bytes s{sector.data(), sector.size()};
        if (std::memcmp(sector.data() + 1, "CD001", 5) != 0 || ld_u8(s, 6) != 1)
            return Error{FormatError::BadMagic, "no ISO9660 volume descriptor at LSN 16 (not a 2048-byte-sector ISO image)"};
        const u8 type = ld_u8(s, 0);
        if (type == 255) break;
        if (type != 1) continue;
        if (ld_u16le(s, 128) != kSectorSize) return Error{FormatError::BadHeader, "ISO9660 logical block size is not 2048"};
        if (ld_u8(s, 156) != 34) return Error{FormatError::BadHeader, "ISO9660 PVD root directory record length is not 34"};
        Volume vol;
        vol.volume_sectors = ld_u32le(s, 80);
        auto root = parse_record(s.subspan(156, 34), nullptr);
        if (!root) return root.error();
        vol.root = std::move(root.value());
        if (!vol.root.is_directory()) return Error{FormatError::BadHeader, "ISO9660 PVD root record is not a directory"};
        return vol;
    }
    return Error{FormatError::BadMagic, "no ISO9660 primary volume descriptor"};
}

Result<std::vector<Record>> read_directory(DiscSource& disc, const Volume& vol, const Record& dir) {
    if (!dir.is_directory()) return Error{FormatError::BadHeader, "ISO9660 record is not a directory"};
    if (dir.size > kMaxDirectoryBytes) return Error{FormatError::Unsupported, "ISO9660 directory larger than 1 MiB"};
    const u32 nsec = (dir.size + kSectorSize - 1) / kSectorSize;
    if (static_cast<u64>(dir.lsn) + nsec > vol.volume_sectors)
        return Error{FormatError::BadHeader, "ISO9660 directory extent lies outside the volume"};
    std::vector<std::byte> buf(static_cast<std::size_t>(nsec) * kSectorSize);
    if (nsec != 0) {
        auto rd = disc.read_sectors(dir.lsn, nsec, buf);
        if (!rd) return rd.error();
    }
    std::vector<Record> out;
    const Bytes all{buf.data(), dir.size};
    std::size_t off = 0;
    while (off < all.size()) {
        const std::size_t sector_end = (off / kSectorSize + 1) * kSectorSize;
        const std::size_t len = ld_u8(all, off);
        if (len == 0) {  // records never span sectors; the rest of this sector is padding
            off = sector_end;
            continue;
        }
        if (off + len > sector_end || off + len > all.size())
            return Error{FormatError::BadHeader, "ISO9660 directory record crosses a sector boundary"};
        auto rec = parse_record(all.subspan(off, len), &vol);
        if (!rec) return rec.error();
        rec->dir_offset = off;
        if (!rec->is_self_or_parent()) out.push_back(std::move(rec.value()));
        off += len;
    }
    return out;
}

bool component_matches(std::string_view record_identifier, std::string_view query) {
    if (query.find(';') == std::string_view::npos) {
        const std::size_t semi = record_identifier.find(';');
        if (semi != std::string_view::npos) record_identifier = record_identifier.substr(0, semi);
    }
    return iequals(record_identifier, query);
}

std::vector<std::string_view> split_path(std::string_view path) {
    std::vector<std::string_view> parts;
    std::size_t i = 0;
    while (i < path.size()) {
        std::size_t j = i;
        while (j < path.size() && path[j] != '\\' && path[j] != '/') ++j;
        if (j > i) parts.push_back(path.substr(i, j - i));
        i = j + 1;
    }
    return parts;
}

Result<std::optional<Record>> find(DiscSource& disc, const Volume& vol, std::string_view path) {
    const std::vector<std::string_view> parts = split_path(path);
    if (parts.empty()) return Error{FormatError::Unsupported, "empty search path"};
    Record dir = vol.root;
    for (std::size_t i = 0;; ++i) {
        auto entries = read_directory(disc, vol, dir);
        if (!entries) return entries.error();
        const Record* hit = nullptr;
        for (const Record& r : entries.value()) {
            if (component_matches(r.identifier, parts[i])) {
                hit = &r;
                break;
            }
        }
        if (hit == nullptr) return std::optional<Record>{};
        if (i + 1 == parts.size()) return std::optional<Record>{*hit};
        if (!hit->is_directory()) return std::optional<Record>{};
        dir = *hit;
    }
}

Result<std::vector<std::byte>> read_file(DiscSource& disc, const Record& file, u32 max_bytes) {
    if (file.is_directory()) return Error{FormatError::BadHeader, "ISO9660 record is a directory, not a file"};
    if (file.size > max_bytes) return Error{FormatError::Unsupported, "file larger than the caller's bound"};
    const u32 nsec = (file.size + kSectorSize - 1) / kSectorSize;
    std::vector<std::byte> buf(static_cast<std::size_t>(nsec) * kSectorSize);
    if (nsec != 0) {
        auto rd = disc.read_sectors(file.lsn, nsec, buf);
        if (!rd) return rd.error();
    }
    buf.resize(file.size);
    return buf;
}

}  // namespace p3fes::hle::iso9660
