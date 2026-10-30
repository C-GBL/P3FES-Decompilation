// IsoFileSource: the user's plain 2048-byte-sector ISO (disc LSN n at byte offset n*2048).
#include "host_file.h"
#include "iso9660.h"
#include "p3fes/hle/disc_source.h"
#include "p3fes/prof.h"

namespace p3fes::hle {

namespace {
// Resource bound for SYSTEM.CNF (this disc's is 51 B).
constexpr u32 kMaxSystemCnfBytes = 64u * 1024u;
}  // namespace

IsoFileSource::IsoFileSource(std::unique_ptr<HostFile> file) : file_(std::move(file)) {}
IsoFileSource::~IsoFileSource() = default;

Result<std::unique_ptr<IsoFileSource>> IsoFileSource::open(const std::filesystem::path& image) {
    auto file = HostFile::open(image);
    if (!file) return file.error();
    const u64 bytes = file.value()->size();
    if (bytes % kSectorSize != 0)
        return Error{FormatError::BadHeader,
                     "image size is not a multiple of 2048 (raw 2352-byte BIN/CUE dumps are not supported; use a plain ISO)"};
    if (bytes / kSectorSize > 0xFFFFFFFFull) return Error{FormatError::BadHeader, "image larger than 2^32 sectors"};

    std::unique_ptr<IsoFileSource> src(new IsoFileSource(std::move(file).value()));
    src->identity_.kind = DiscSourceKind::IsoImage;
    src->identity_.origin = image;
    src->identity_.sectors = static_cast<u32>(bytes / kSectorSize);  // provisional until the PVD is read

    auto vol = iso9660::read_volume(*src);
    if (!vol) return vol.error();
    if (vol->volume_sectors == 0) return Error{FormatError::BadHeader, "ISO9660 volume_space_size is 0"};
    if (vol->volume_sectors > src->identity_.sectors)
        return Error{FormatError::Truncated, "image is shorter than its PVD volume_space_size"};
    src->identity_.sectors = vol->volume_sectors;

    auto cnf_rec = iso9660::find(*src, vol.value(), "SYSTEM.CNF;1");
    if (!cnf_rec) return cnf_rec.error();
    if (!cnf_rec->has_value())
        return Error{FormatError::BadMagic, "no SYSTEM.CNF in the root directory (not a PS2 game disc)"};
    auto cnf_bytes = iso9660::read_file(*src, *cnf_rec.value(), kMaxSystemCnfBytes);
    if (!cnf_bytes) return cnf_bytes.error();
    auto cnf = parse_system_cnf(cnf_bytes.value());
    if (!cnf) return cnf.error();
    auto verified = verify_system_cnf(std::move(cnf).value());
    if (!verified) return verified.error();
    src->identity_.system_cnf = std::move(verified).value();
    return src;
}

Result<std::size_t> IsoFileSource::read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) {
    const prof::Scope prof_zone(prof::Zone::Cdvd);
    auto bytes = check_read(lsn, count, dst);
    if (!bytes) return bytes.error();
    return file_->read_at(static_cast<u64>(lsn) * kSectorSize, dst.first(bytes.value()));
}

}  // namespace p3fes::hle
