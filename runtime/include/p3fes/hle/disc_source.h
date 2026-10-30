// Disc sources for the sector-level CDVD HLE (ADR-0008 §1; RUNTIME_CONTRACT L-01).
//
// A DiscSource answers "give me 2048-byte user-data sectors at disc LSN n" for the
// user's own copy of the game. Two implementations:
//
//   IsoFileSource           the user's plain 2048-byte-sector ISO image (byte offset lsn*2048).
//                           Opening it verifies, through the ISO9660 PVD and root directory,
//                           that SYSTEM.CNF says BOOT2=cdrom0:\SLUS_216.21;1 and refuses any
//                           other disc. This is the path the shipped port uses when it asks
//                           for the player's copy (GOAL.md ground rules).
//   ExtractedVolumesSource  the developer's extracted/disc/ files (DATA/BTL/BGM.CVM, SLUS_216.21,
//                           SYSTEM.CNF) placed at their disc LSNs by the constant kDiscLayout
//                           table (docs/DISC_LAYOUT.md §7). Sectors not covered by the table
//                           (system area, PVD, directories, LIB31) read as zeros.
//
// Nothing here copies, caches or writes disc data anywhere; reads go straight from
// the user's files into the caller's buffer.
//
// Errors use formats::Result<T> (no exceptions cross this API). Code mapping:
//   Overrun      request outside [0, sector_count()) or destination too small
//   Truncated    host file missing, unreadable, or shorter than required
//   BadHeader    malformed ISO9660 / SYSTEM.CNF structure, or not a 2048-byte-sector image
//   BadMagic     not the expected disc (no PVD, no SYSTEM.CNF, BOOT2 mismatch, size mismatch)
//   Unsupported  valid request this source does not model (e.g. ISO9660 multi-extent files,
//                paths the extracted catalogue does not cover)
//   Corrupt      kDiscLayout disagrees with an ISO's directory (verify_disc_layout)
//
// Not thread-safe: one owner (the IOP/CDVD HLE) drives a source.
#pragma once

#include <array>
#include <cstddef>
#include <filesystem>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>

#include "p3fes/ee_types.h"
#include "p3fes/formats/result.h"

namespace p3fes::hle {

using formats::Error;
using formats::FormatError;
using formats::Result;

class HostFile;  // runtime/hle/host_file.h (private)

// SCECdSecS2048: the only data pattern the game requests (docs/ANALYSIS/11_file_io.md §3,
// srd_exec_dvd 0x558138 passes mode {0,0,0}).
inline constexpr u32 kSectorSize = 2048;

// SYSTEM.CNF of the one disc this port accepts (docs/INVENTORY.md "SYSTEM.CNF").
inline constexpr std::string_view kExpectedBoot2 = "cdrom0:\\SLUS_216.21;1";

// ---------------------------------------------------------------------------------------------
// Disc layout table (docs/DISC_LAYOUT.md §7, observed 2026-10-18 from the user's ISO root
// directory; PS2 disc LSN == image LBA). The root directory holds exactly these five files plus
// the directory LIB31 (kDiscRootDirectories); verify_disc_layout() re-checks all of it against
// an ISO whenever one is available.
// ---------------------------------------------------------------------------------------------
struct DiscLayoutEntry {
    std::string_view identifier;  // ISO9660 file identifier in the root directory
    std::string_view host_name;   // file name under extracted/disc/
    u32 lsn;                      // first disc LSN of the extent
    u32 size;                     // bytes
    std::array<u8, 7> recorded;   // ISO9660 recording date and time of the root record (DiscFile::recorded)

    constexpr u32 sectors() const { return (size + kSectorSize - 1) / kSectorSize; }
    constexpr u32 end_lsn() const { return lsn + sectors(); }
};

// Recording dates: the user's ISO root directory (obs 2026-10-19; verify_disc_layout checks them), e.g. BTL.CVM
// 2008-01-04 14:59:58 GMT+9 -- the sceCdlFILE date the PCSX2 first_flip state holds at 0x7A2890.
inline constexpr std::array<DiscLayoutEntry, 5> kDiscLayout = {{
    {"BTL.CVM;1", "BTL.CVM", 633u, 936'579'072u, {108, 1, 4, 14, 59, 58, 36}},
    {"BGM.CVM;1", "BGM.CVM", 457'947u, 258'899'968u, {106, 12, 12, 16, 31, 39, 36}},
    {"DATA.CVM;1", "DATA.CVM", 584'363u, 3'367'428'096u, {108, 1, 4, 14, 55, 42, 36}},
    {"SLUS_216.21;1", "SLUS_216.21", 2'228'615u, 9'096'860u, {108, 1, 4, 15, 15, 58, 36}},
    // DISC_LAYOUT §7 prints this row's hex as 0x2112E1; the decimal value (= 0x2212E1) is the one
    // the ISO directory records (verify_disc_layout checks it).
    {"SYSTEM.CNF;1", "SYSTEM.CNF", 2'233'057u, 51u, {107, 11, 16, 10, 22, 42, 36}},
}};

// Root-directory subdirectories, which the extracted catalogue does not cover.
inline constexpr std::array<std::string_view, 1> kDiscRootDirectories = {"LIB31"};

// Volume size in sectors: 4,594,302,976 B / 2048 (docs/INVENTORY.md "Disc image"); equals the
// outer PVD volume_space_size (checked by verify_disc_layout).
inline constexpr u32 kDiscSectors = 2'243'312u;

// ROFS reads a CVM's ISO9660 image 3 sectors into the container file: vol.lba_offset = 3, read
// from the CVMH header by cvmh_AnalyMainHdrCvm 0x56AE20 and added in dcfReqRdCda 0x56AA98
// (docs/ANALYSIS/11_file_io.md §2).
inline constexpr u32 kCvmHeaderSectors = 3;

consteval bool disc_layout_is_well_formed() {
    for (std::size_t i = 0; i < kDiscLayout.size(); ++i) {
        if (kDiscLayout[i].end_lsn() > kDiscSectors) return false;
        if (i > 0 && kDiscLayout[i - 1].end_lsn() > kDiscLayout[i].lsn) return false;  // sorted, disjoint
    }
    return true;
}
static_assert(disc_layout_is_well_formed(), "kDiscLayout must be sorted, disjoint and inside the disc");

// Looks up a container by host name ("DATA.CVM"); nullptr if not in the table.
constexpr const DiscLayoutEntry* find_disc_layout(std::string_view host_name) {
    for (const DiscLayoutEntry& e : kDiscLayout)
        if (e.host_name == host_name) return &e;
    return nullptr;
}

// Disc LSN of the sector holding in-CVM ISO LBA `iso_lba` (manifest.json "lba"):
// LSN(x.CVM) + 3 + iso_lba (DISC_LAYOUT §7; RUNTIME_CONTRACT L-01).
constexpr u32 cvm_file_lsn(const DiscLayoutEntry& cvm, u32 iso_lba) {
    return cvm.lsn + kCvmHeaderSectors + iso_lba;
}

// ---------------------------------------------------------------------------------------------
// Identity
// ---------------------------------------------------------------------------------------------

// Parsed SYSTEM.CNF ("KEY = VALUE" lines; whitespace around key and value ignored).
struct SystemCnf {
    std::string boot2;       // BOOT2 value, e.g. "cdrom0:\SLUS_216.21;1"
    std::string version;     // VER, empty if absent
    std::string video_mode;  // VMODE, empty if absent
};

// BadHeader on non-text bytes or lines without '='; BadMagic when BOOT2 is absent (not a PS2
// game disc). Does not check *which* game; see verify_system_cnf().
Result<SystemCnf> parse_system_cnf(std::span<const std::byte> text);

// BadMagic unless cnf.boot2 == kExpectedBoot2. The single owner of "is this the user's copy of
// Persona 3 FES (NTSC-U)": both sources call it.
Result<SystemCnf> verify_system_cnf(SystemCnf cnf);

enum class DiscSourceKind : u8 { IsoImage, ExtractedVolumes };

struct DiscIdentity {
    DiscSourceKind kind = DiscSourceKind::IsoImage;
    SystemCnf system_cnf;          // verified: system_cnf.boot2 == kExpectedBoot2
    u32 sectors = 0;               // == sector_count()
    std::filesystem::path origin;  // the ISO file, or the extracted/disc directory
};

// A file located on the disc (outer ISO9660 directory record).
struct DiscFile {
    u32 lsn = 0;             // extent start, disc LSN
    u32 size = 0;            // bytes
    std::string identifier;  // as recorded, e.g. "DATA.CVM;1"
    std::array<u8, 7> recorded{};  // ISO9660 recording date and time as recorded (directory record bytes 18-24)

    constexpr u32 sectors() const { return (size + kSectorSize - 1) / kSectorSize; }
};

// ---------------------------------------------------------------------------------------------
// DiscSource
// ---------------------------------------------------------------------------------------------
class DiscSource {
public:
    virtual ~DiscSource() = default;
    DiscSource(const DiscSource&) = delete;
    DiscSource& operator=(const DiscSource&) = delete;

    // Copies `count` user-data sectors starting at disc LSN `lsn` into the first count*2048
    // bytes of `dst`. Ok value: bytes written. Overrun if [lsn, lsn+count) leaves the disc or
    // `dst` is too small; Truncated on a host read failure (dst contents then unspecified).
    virtual Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) = 0;

    // Disc size in sectors (outer PVD volume_space_size).
    virtual u32 sector_count() const = 0;

    virtual const DiscIdentity& identity() const = 0;

    // Locates `path` (libcdvd form: "\DATA.CVM;1", "\LIB31\PADMAN.IRX;1"; '/' also accepted;
    // case-insensitive; a component without ";N" matches any version). Ok(nullopt) means the
    // disc's directory data says the file is absent; an error means it could not be determined.
    // Default: ISO9660 walk from the PVD at LSN 16 through read_sectors().
    virtual Result<std::optional<DiscFile>> find_file(std::string_view path);

protected:
    DiscSource() = default;

    // Shared argument check for read_sectors(): Overrun on range or destination size.
    Result<std::size_t> check_read(u32 lsn, u32 count, std::span<std::byte> dst) const;
};

// The user's own ISO image (plain 2048-byte sectors; not BIN/CUE 2352-byte raw dumps).
class IsoFileSource final : public DiscSource {
public:
    // Opens and verifies `image`. Truncated: cannot open / shorter than its PVD says.
    // BadHeader: size is not a multiple of 2048 or malformed ISO9660. BadMagic: no PVD, no
    // SYSTEM.CNF, or BOOT2 != kExpectedBoot2 (a different disc: the port refuses it).
    static Result<std::unique_ptr<IsoFileSource>> open(const std::filesystem::path& image);

    ~IsoFileSource() override;

    Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) override;
    u32 sector_count() const override { return identity_.sectors; }
    const DiscIdentity& identity() const override { return identity_; }

private:
    explicit IsoFileSource(std::unique_ptr<HostFile> file);

    std::unique_ptr<HostFile> file_;
    DiscIdentity identity_;
};

// extracted/disc/ served at the kDiscLayout LSNs.
class ExtractedVolumesSource final : public DiscSource {
public:
    // `disc_dir` must hold the five kDiscLayout files under their host names. Truncated: a file
    // is missing or unreadable. BadMagic: a file size differs from kDiscLayout (another disc
    // revision) or SYSTEM.CNF BOOT2 != kExpectedBoot2.
    static Result<std::unique_ptr<ExtractedVolumesSource>> open(const std::filesystem::path& disc_dir);

    ~ExtractedVolumesSource() override;

    // Sectors outside the five extents read as zeros; the tail of a file's last sector is zero.
    Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) override;
    u32 sector_count() const override { return kDiscSectors; }
    const DiscIdentity& identity() const override { return identity_; }

    // Answers from kDiscLayout (no ISO directory exists in this source). Root-level names that
    // are neither a table file nor LIB31 are absent (the root listing is complete); anything
    // under LIB31 is Unsupported (outside the catalogue, so unknown rather than absent).
    Result<std::optional<DiscFile>> find_file(std::string_view path) override;

private:
    ExtractedVolumesSource();

    std::array<std::unique_ptr<HostFile>, kDiscLayout.size()> files_;
    DiscIdentity identity_;
};

// Self-check of kDiscLayout / kDiscRootDirectories / kDiscSectors against a source with a real
// ISO9660 directory (an IsoFileSource): every root file must be a table entry with the same LSN
// and size, every table entry must be present, the only root subdirectories are
// kDiscRootDirectories, and the PVD volume size is kDiscSectors. Ok value: entries confirmed.
// Corrupt on any disagreement; ISO9660 errors pass through.
Result<std::size_t> verify_disc_layout(DiscSource& iso);

// Entry point for the shipped port's first-run prompt (GOAL.md: "ask for their copy of the
// game"): a regular file opens as IsoFileSource, a directory as ExtractedVolumesSource. The
// caller shows formats::error_name(err.code) + err.detail and asks again on failure.
Result<std::unique_ptr<DiscSource>> open_user_disc(const std::filesystem::path& path);

}  // namespace p3fes::hle
