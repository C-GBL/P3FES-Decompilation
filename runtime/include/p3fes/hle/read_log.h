// The read log of the modernize pass (docs/MODERNIZE_PLAN.md §3, stage 0): every disc read the game makes through
// cdvdfsv, one text line each, with what layer 1 (native files) needs to redo the read by path instead of by LSN.
//
//   <vblank> lsn=<LSN> n=<sectors> bytes=<sectors*2048> dst=<guest buf, hex> path=<file> off=<byte offset in file>
//            fsize=<file bytes> hash=<FNV-1a 64 of the delivered bytes, hex | -> [err=<libcdvd error>]
//
// `path` comes from the disc's own directories (DiscPathIndex): "DATA.CVM:\FIELD\X.PAC" for a CVM member (the
// CVM's inner ISO9660 image, CRI's container: CVMH header sectors, then the image), "SLUS_216.21",
// "LIB31\SDRDRV.IRX" or "DATA.CVM" for an outer file (a CVM itself when the read is not inside one member: its
// header, its directories, or a span across members), "-" when no file holds the whole read (then `off` is the
// disc byte offset). A read may run past `fsize` into the last sector's padding: `bytes` is always whole sectors.
// `hash` covers all `bytes`. Nothing here touches guest memory; the host (runtime/app, --read-log) formats lines
// from IopConfig::cd_read_sink events.
#pragma once

#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "p3fes/ee_types.h"
#include "p3fes/hle/disc_source.h"

namespace p3fes::hle {

inline constexpr u64 kFnv1a64Basis = 0xCBF29CE484222325ull;
u64 fnv1a64(std::span<const std::byte> bytes, u64 h = kFnv1a64Basis);

// Where a sector range lives, by path.
struct ResolvedRead {
    std::string path = "-";
    u64 offset = 0;     // bytes from the start of `path` to the read's first sector (disc offset for "-")
    u64 file_size = 0;  // bytes of `path` (0 for "-")
};

// LSN -> file map of a DiscSource, built once from its ISO9660 directories (the ISO, a mods overlay) or, for the
// extracted volumes (no outer directories), from kDiscLayout; every CVM's inner image is walked. Not thread-safe.
class DiscPathIndex {
public:
    static DiscPathIndex build(DiscSource& disc);

    // The smallest file holding all of [lsn, lsn + sectors): a CVM member, else an outer file, else "-".
    ResolvedRead resolve(u32 lsn, u32 sectors) const;

    std::size_t outer_files() const { return outer_.size(); }
    std::size_t members() const { return members_.size(); }

    // Every indexed file, outer files first, each list in LSN order: its path (as `resolve` names it), first LSN,
    // sector count and size in bytes. Layer 1's native files service builds its by-path table from this.
    template <typename Fn>
    void for_each_file(Fn&& fn) const {
        for (const Span& s : outer_) fn(s.path, s.lsn, s.sectors, s.size, true);
        for (const Span& s : members_) fn(s.path, s.lsn, s.sectors, s.size, false);
    }

private:
    struct Span {
        u32 lsn = 0, sectors = 0;
        u64 size = 0;
        std::string path;
    };
    std::vector<Span> outer_, members_;  // each sorted by lsn, disjoint within itself
    static const Span* find(const std::vector<Span>& v, u32 lsn, u32 sectors);
};

struct ReadLogRecord {
    u64 vblank = 0;
    u32 lsn = 0, sectors = 0, dst = 0;
    int error = 0;
    ResolvedRead file;
    u64 hash = 0;  // fnv1a64 of the delivered bytes (unused when error != 0)
};

inline constexpr std::string_view kReadLogHeader =
    "# p3fes read log v1: vblank lsn= n= bytes= dst= path= off= fsize= hash= [err=] (docs/MODERNIZE_PLAN.md section 3)";

// One line, without the newline.
std::string format_read_log_line(const ReadLogRecord& r);

}  // namespace p3fes::hle
