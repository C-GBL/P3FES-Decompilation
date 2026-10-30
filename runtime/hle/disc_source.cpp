// DiscSource base behaviour, SYSTEM.CNF identity, the kDiscLayout self-check and the first-run
// entry point. The two concrete sources live in iso_file_source.cpp / extracted_volumes_source.cpp.
#include "p3fes/hle/disc_source.h"

#include <system_error>

#include "iso9660.h"

namespace p3fes::hle {

namespace {

std::string_view trim(std::string_view s) {
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t')) s.remove_prefix(1);
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r')) s.remove_suffix(1);
    return s;
}

}  // namespace

// ---- SYSTEM.CNF ---------------------------------------------------------------------------

Result<SystemCnf> parse_system_cnf(std::span<const std::byte> text) {
    std::string_view all{reinterpret_cast<const char*>(text.data()), text.size()};
    if (const std::size_t nul = all.find('\0'); nul != std::string_view::npos) all = all.substr(0, nul);
    for (const char c : all) {
        const auto u = static_cast<unsigned char>(c);
        if ((u < 0x20 && c != '\r' && c != '\n' && c != '\t') || u > 0x7E)
            return Error{FormatError::BadHeader, "SYSTEM.CNF contains non-text bytes"};
    }
    SystemCnf cnf;
    bool have_boot2 = false;
    std::size_t pos = 0;
    while (pos < all.size()) {
        std::size_t eol = all.find('\n', pos);
        if (eol == std::string_view::npos) eol = all.size();
        const std::string_view line = trim(all.substr(pos, eol - pos));
        pos = eol + 1;
        if (line.empty()) continue;
        const std::size_t eq = line.find('=');
        if (eq == std::string_view::npos) return Error{FormatError::BadHeader, "SYSTEM.CNF line without '='"};
        const std::string_view key = trim(line.substr(0, eq));
        const std::string_view value = trim(line.substr(eq + 1));
        if (key == "BOOT2") {
            cnf.boot2.assign(value);
            have_boot2 = true;
        } else if (key == "VER") {
            cnf.version.assign(value);
        } else if (key == "VMODE") {
            cnf.video_mode.assign(value);
        }
    }
    if (!have_boot2) return Error{FormatError::BadMagic, "SYSTEM.CNF has no BOOT2 line (not a PS2 game disc)"};
    return cnf;
}

Result<SystemCnf> verify_system_cnf(SystemCnf cnf) {
    if (cnf.boot2 != kExpectedBoot2)
        return Error{FormatError::BadMagic,
                     "SYSTEM.CNF BOOT2 is not cdrom0:\\SLUS_216.21;1 (not Persona 3 FES NTSC-U; the port needs that disc)"};
    return cnf;
}

// ---- DiscSource -----------------------------------------------------------------------------

Result<std::size_t> DiscSource::check_read(u32 lsn, u32 count, std::span<std::byte> dst) const {
    if (static_cast<u64>(lsn) + count > sector_count())
        return Error{FormatError::Overrun, "sector range outside the disc"};
    const std::size_t bytes = static_cast<std::size_t>(count) * kSectorSize;
    if (dst.size() < bytes) return Error{FormatError::Overrun, "destination smaller than count*2048 bytes"};
    return bytes;
}

Result<std::optional<DiscFile>> DiscSource::find_file(std::string_view path) {
    auto vol = iso9660::read_volume(*this);
    if (!vol) return vol.error();
    auto rec = iso9660::find(*this, vol.value(), path);
    if (!rec) return rec.error();
    if (!rec->has_value()) return std::optional<DiscFile>{};
    const iso9660::Record& r = *rec.value();
    return std::optional<DiscFile>{DiscFile{r.lsn, r.size, r.identifier, r.recorded}};
}

// ---- kDiscLayout self-check -----------------------------------------------------------------

Result<std::size_t> verify_disc_layout(DiscSource& iso) {
    auto vol = iso9660::read_volume(iso);
    if (!vol) return vol.error();
    if (vol->volume_sectors != kDiscSectors)
        return Error{FormatError::Corrupt, "PVD volume_space_size differs from kDiscSectors"};
    auto root = iso9660::read_directory(iso, vol.value(), vol->root);
    if (!root) return root.error();

    std::array<bool, kDiscLayout.size()> seen{};
    for (const iso9660::Record& r : root.value()) {
        if (r.is_directory()) {
            bool known = false;
            for (std::string_view d : kDiscRootDirectories) known = known || iso9660::component_matches(r.identifier, d);
            if (!known) return Error{FormatError::Corrupt, "ISO root holds a directory not in kDiscRootDirectories"};
            continue;
        }
        std::size_t idx = kDiscLayout.size();
        for (std::size_t i = 0; i < kDiscLayout.size(); ++i)
            if (iso9660::component_matches(r.identifier, kDiscLayout[i].identifier)) idx = i;
        if (idx == kDiscLayout.size()) return Error{FormatError::Corrupt, "ISO root holds a file missing from kDiscLayout"};
        if (seen[idx]) return Error{FormatError::Corrupt, "ISO root lists a kDiscLayout file twice"};
        if (r.lsn != kDiscLayout[idx].lsn) return Error{FormatError::Corrupt, "kDiscLayout LSN differs from the ISO directory"};
        if (r.size != kDiscLayout[idx].size) return Error{FormatError::Corrupt, "kDiscLayout size differs from the ISO directory"};
        if (r.recorded != kDiscLayout[idx].recorded)
            return Error{FormatError::Corrupt, "kDiscLayout recording date differs from the ISO directory"};
        seen[idx] = true;
    }
    for (const bool s : seen)
        if (!s) return Error{FormatError::Corrupt, "kDiscLayout entry absent from the ISO root directory"};
    return kDiscLayout.size();
}

// ---- first-run entry point ------------------------------------------------------------------

Result<std::unique_ptr<DiscSource>> open_user_disc(const std::filesystem::path& path) {
    std::error_code ec;
    if (std::filesystem::is_directory(path, ec)) {
        auto src = ExtractedVolumesSource::open(path);
        if (!src) return src.error();
        return std::unique_ptr<DiscSource>(std::move(src).value());
    }
    if (std::filesystem::is_regular_file(path, ec)) {
        auto src = IsoFileSource::open(path);
        if (!src) return src.error();
        return std::unique_ptr<DiscSource>(std::move(src).value());
    }
    return Error{FormatError::Truncated, "path is neither a disc image file nor an extracted/disc directory"};
}

}  // namespace p3fes::hle
