// ExtractedVolumesSource: extracted/disc/ files placed at their kDiscLayout LSNs
// (docs/DISC_LAYOUT.md §7). Uncovered sectors read as zeros.
#include <algorithm>
#include <cstring>
#include <vector>

#include "host_file.h"
#include "iso9660.h"
#include "p3fes/hle/disc_source.h"
#include "p3fes/prof.h"

namespace p3fes::hle {

namespace {

constexpr std::size_t kSystemCnfIndex = 4;
static_assert(kDiscLayout[kSystemCnfIndex].host_name == "SYSTEM.CNF");

bool is_root_directory(std::string_view component) {
    for (std::string_view d : kDiscRootDirectories)
        if (iso9660::component_matches(d, component)) return true;
    return false;
}

}  // namespace

ExtractedVolumesSource::ExtractedVolumesSource() = default;
ExtractedVolumesSource::~ExtractedVolumesSource() = default;

Result<std::unique_ptr<ExtractedVolumesSource>> ExtractedVolumesSource::open(const std::filesystem::path& disc_dir) {
    std::unique_ptr<ExtractedVolumesSource> src(new ExtractedVolumesSource());
    for (std::size_t i = 0; i < kDiscLayout.size(); ++i) {
        auto f = HostFile::open(disc_dir / std::filesystem::path(kDiscLayout[i].host_name));
        if (!f) return Error{FormatError::Truncated, "an extracted/disc file of kDiscLayout is missing or unreadable"};
        if (f.value()->size() != kDiscLayout[i].size)
            return Error{FormatError::BadMagic, "an extracted/disc file size differs from kDiscLayout (another disc revision?)"};
        src->files_[i] = std::move(f).value();
    }
    std::vector<std::byte> cnf_bytes(kDiscLayout[kSystemCnfIndex].size);
    auto rd = src->files_[kSystemCnfIndex]->read_at(0, cnf_bytes);
    if (!rd) return rd.error();
    auto cnf = parse_system_cnf(cnf_bytes);
    if (!cnf) return cnf.error();
    auto verified = verify_system_cnf(std::move(cnf).value());
    if (!verified) return verified.error();

    src->identity_.kind = DiscSourceKind::ExtractedVolumes;
    src->identity_.system_cnf = std::move(verified).value();
    src->identity_.sectors = kDiscSectors;
    src->identity_.origin = disc_dir;
    return src;
}

Result<std::size_t> ExtractedVolumesSource::read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) {
    const prof::Scope prof_zone(prof::Zone::Cdvd);
    auto bytes = check_read(lsn, count, dst);
    if (!bytes) return bytes.error();
    const u32 end = lsn + count;  // <= kDiscSectors by check_read
    u32 cur = lsn;
    std::byte* out = dst.data();
    while (cur < end) {
        // The table is sorted and disjoint: find the extent containing `cur`, or the next one.
        std::size_t i = 0;
        while (i < kDiscLayout.size() && kDiscLayout[i].end_lsn() <= cur) ++i;
        if (i == kDiscLayout.size() || cur < kDiscLayout[i].lsn) {
            const u32 gap_end = (i == kDiscLayout.size()) ? end : std::min(end, kDiscLayout[i].lsn);
            const std::size_t n = static_cast<std::size_t>(gap_end - cur) * kSectorSize;
            std::memset(out, 0, n);
            out += n;
            cur = gap_end;
            continue;
        }
        const DiscLayoutEntry& e = kDiscLayout[i];
        const u32 seg_end = std::min(end, e.end_lsn());
        const u64 file_off = static_cast<u64>(cur - e.lsn) * kSectorSize;
        const std::size_t seg_bytes = static_cast<std::size_t>(seg_end - cur) * kSectorSize;
        const std::size_t data_bytes = static_cast<std::size_t>(std::min<u64>(seg_bytes, e.size - file_off));
        auto rd = files_[i]->read_at(file_off, std::span<std::byte>{out, data_bytes});
        if (!rd) return rd.error();
        std::memset(out + data_bytes, 0, seg_bytes - data_bytes);  // tail of the last sector
        out += seg_bytes;
        cur = seg_end;
    }
    return bytes.value();
}

Result<std::optional<DiscFile>> ExtractedVolumesSource::find_file(std::string_view path) {
    const std::vector<std::string_view> parts = iso9660::split_path(path);
    if (parts.empty()) return Error{FormatError::Unsupported, "empty search path"};
    if (parts.size() == 1) {
        for (const DiscLayoutEntry& e : kDiscLayout)
            if (iso9660::component_matches(e.identifier, parts[0]))
                return std::optional<DiscFile>{DiscFile{e.lsn, e.size, std::string(e.identifier), e.recorded}};
        if (is_root_directory(parts[0]))
            return Error{FormatError::Unsupported, "LIB31 is outside the extracted catalogue (use the ISO source)"};
        return std::optional<DiscFile>{};  // the root listing is complete (kDiscLayout + LIB31)
    }
    if (is_root_directory(parts[0]))
        return Error{FormatError::Unsupported, "paths under LIB31 are outside the extracted catalogue (use the ISO source)"};
    return std::optional<DiscFile>{};  // no other root directory exists
}

}  // namespace p3fes::hle
