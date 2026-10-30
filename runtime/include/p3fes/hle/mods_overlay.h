// Mods overlay (ADR-0016): a virtual disc in which whole disc files are replaced by host files from one or more
// mods folders, without touching the user's ISO. Off unless asked for: p3fes / the editor's GameHost build one
// only for an explicit `--mods DIR` (HostConfig::mods); without it the DiscSource is the plain IsoFileSource /
// ExtractedVolumesSource exactly as before.
//
// Mods folders. A mod mirrors the disc's paths, the CVM containers by their base name as in extracted/:
//     <mod>\DATA\FIELD\F005_001.PAC   replaces DATA.CVM's \FIELD\F005_001.PAC
//     <mod>\BTL\BATTLE\...            BTL.CVM members;  <mod>\BGM\...  BGM.CVM members
//     <mod>\LIB31\X.IRX               an outer-disc file (ISO sources only)
// Names match case-insensitively, as the ISO9660 layer matches them (iso9660::component_matches), and a disc
// file can only be replaced, not added (the game's ROFS tables are fixed in the ELF). Refused: SYSTEM.CNF, the
// boot ELF, a whole *.CVM, paths that escape the mod root ("..", absolute, drive / stream names, reparse points
// and symlinks anywhere under the root) and files above ModsOptions::max_file_bytes.
// A `--mods DIR` is one mod when DIR holds a mod.json or an entry named like a disc root entry (DATA, BTL, BGM,
// LIB31, ...); otherwise every subfolder of DIR is a mod, in mod.json "load_order" order (default 0, then folder
// name). Several --mods: later ones win per file; within a folder, later in load order wins.
// mod.json (optional): {"name": "...", "description": "...", "load_order": N}; malformed -> logged, defaults used.
//
// Where the guest learns a file's LBA and size, and what the overlay does about each (ADR-0016 §2):
//   1. sceCdSearchFile for \DATA.CVM;1 / \BGM.CVM;1 / \BTL.CVM;1 (dvCiOpen, three times at boot; cdvdfsv ->
//      find_file): every CVM is *relocated* into a window of its own after the real image (kModsFirstWindow +
//      i * kModsWindowSectors) and reported with the CVM's maximum reachable size, kModsCvmWindowSectors * 2048
//      (dvCiOpen: size_sct = (size + 2047) >> 11, dvCiSeek clamps to it, so a CVM can only reach 2^21 - 1
//      sectors past its start: BTL.CVM at LSN 633 cannot reach past the real image, hence relocation). The outer
//      ISO9660 root records of the CVMs are patched to the same LSN / size, the outer PVD volume size to
//      sector_count(). The CVM header sectors' size fields (CVMH +0x1C, ZONE +0x04 / +0x30, read by
//      cvmh_AnalyMainHdrCvm 0x56AE20) and the inner PVD volume size are moved by the same amount.
//   2. The CRI ROFS "#DirLst#" tables compiled into the ELF (docs/ANALYSIS/11_file_io.md §1: 149 tables, entry
//      {size_lo, size_hi, lba, flags, search_id, name[34]}): the only place the game reads a CVM member's lba
//      and size (ROFS runs in "external directory records" mode and never reads the CVMs' directories). The ELF
//      is loaded from a host file, not from disc sectors, so these are patched in guest RAM:
//      patch_rofs_tables(), right after the ELF is loaded and after every reload().
//   3. The CVMs' inner ISO9660 directory records (patched in the virtual sectors; read by this port's own tools
//      and tests, not by the game) and outer directory records of replaced outer files (find_file / cdvdfsv).
//   Path tables hold directories only (unchanged). AFS / PAK / BIN member tables are inside files, so they are
//   covered by whole-file replacement. H_Cdvd's request list and PAK member cache hold loaded *data*, not LBAs.
// Every replaced file gets a new extent at the end of its window: reads there come from the mod file (its last
// sector zero-padded), reads of the patched sectors from the patched copies, every other sector from the base.
//
// Reload (reload(), GameHost::reload_mods): re-scans the folders. Unchanged files (same host path, size and
// write time) keep their extent; changed or new ones get a new extent after the window's last; extents are never
// reused or freed during a session, so a ROFS handle the guest opened earlier (it copied lba and size at open,
// RFHN_CreateHnG) still reads the bytes of the file it opened: files up to ModsOptions::snapshot_max_file_bytes
// are copied into memory at scan time and an old extent serves that copy; larger files are read from the host
// file at each read (the overlay never keeps a mod file open), so an old extent of a large file sees the file as
// it is now, cut / zero-padded to the size it was scanned with. A change on disk is served only after a reload
// (except through that large-file path). The RAM tables are rewritten at once, so the next ROFS open sees
// the new lba / size (and a file whose override was removed gets the disc's values back). Files H_Cdvd already
// loaded (whole-file heap buffers; PAK members in sCdvdCache) stay as loaded until the game destroys and
// requests them again, e.g. on a scene change; streams in flight finish on their old extent. CVM relocation and
// the reported CVM sizes never change after open (dvCi caches them at boot).
//
// Not thread-safe (one owner, like every DiscSource); reload() and patch_rofs_tables() run between guest slices.
#pragma once

#include <cstddef>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "p3fes/hle/disc_source.h"

namespace p3fes::hle {

// First relocation window: above any real PS2 DVD-5 image (2,295,104 sectors max; this disc 2,243,312).
inline constexpr u32 kModsFirstWindow = 0x0040'0000u;
// Spacing of the windows (one per CVM, then one for outer files).
inline constexpr u32 kModsWindowSectors = 0x0040'0000u;
// Largest CVM the guest can address: dvCiOpen size_sct = (size + 2047) >> 11 on a u32 size.
inline constexpr u32 kModsCvmWindowSectors = 0x001F'FFFFu;  // 2^21 - 1 sectors = 0xFFFFF800 bytes
// Default cap on one mod file (1 GiB; the largest disc file inside a CVM is ~350 MB of movie).
inline constexpr u64 kModsMaxFileBytes = u64{1} << 30;

struct ModsOptions {
    std::vector<std::filesystem::path> dirs;     // --mods DIR, in command-line order (later wins per file); may be empty
    bool enabled = true;                         // false: the overlay is built (CVMs relocated) but serves no file
    u64 max_file_bytes = kModsMaxFileBytes;
    u32 cvm_window_sectors = kModsCvmWindowSectors;  // tests shrink it to exercise "window full"
    // Files up to this size are copied into memory at scan time, so an extent keeps exactly the bytes it was scanned
    // with; larger ones are read from the host file at each read (opened per read: the overlay never holds a mod
    // file open, so the editor can always save or replace it). Superseded copies are dropped oldest first beyond
    // snapshot_total_bytes (those extents then read the current file too).
    u64 snapshot_max_file_bytes = u64{32} << 20;
    u64 snapshot_total_bytes = u64{512} << 20;
    std::function<void(std::string_view)> log;   // one line per message; empty = silent
};

// One mod folder, in load order.
struct ModInfo {
    std::filesystem::path root;
    std::string name;          // mod.json "name", else the folder name
    std::string description;   // mod.json "description"
    long long load_order = 0;  // mod.json "load_order"
    bool has_manifest = false;
};

// One disc file served from a mod file (the winning one).
struct ModOverride {
    std::string disc_path;            // normalised, e.g. "DATA\FIELD\F005_001.PAC" (upper case, no ";1")
    std::filesystem::path host_path;
    std::string mod_name;
    u32 lsn = 0;                      // virtual-disc extent start
    u32 size = 0;                     // bytes, the mod file's size at scan time
    u32 lba = 0;                      // in-CVM ISO LBA (what the guest's ROFS table gets); == lsn for outer files
    u32 original_lsn = 0;             // the disc's extent (disc LSN)
    u32 original_size = 0;
    u32 generation = 0;               // the scan that allocated the extent (0 = open)
    u32 rofs_entries = 0;             // ROFS table entries pointing at it (patch_rofs_tables; CVM members only)
};

struct ModsScan {
    u32 generation = 0;
    std::vector<ModInfo> mods;
    std::vector<ModOverride> overrides;  // sorted by disc_path
    std::vector<std::string> rejected;   // one line per refused file / folder, with the reason
};

// mod.json. BadHeader on malformed JSON or a top level that is not an object. Unknown keys are ignored.
Result<ModInfo> parse_mod_json(std::string_view text);

// A path relative to a mod root ('\' or '/') -> the normalised disc path "A\B\C" (upper case). Unsupported, with
// the reason, for an empty / absolute / drive-relative path, "." / ".." components, empty components, or ':',
// ';', '*', '?', '"', '<', '>', '|' or control characters in a component.
Result<std::string> normalise_mod_path(std::string_view relative);

class ModsOverlay final : public DiscSource {
public:
    // Scans the folders and builds the virtual disc over `base` (which it owns). `options.dirs` may be empty (an
    // overlay for folders added later, set_dirs + reload). Unsupported: `base` is larger than kModsFirstWindow; a
    // folder that does not exist is an error (BadHeader), a refused file is not (logged, in scan().rejected).
    static Result<std::unique_ptr<ModsOverlay>> open(std::unique_ptr<DiscSource> base, ModsOptions options);
    ~ModsOverlay() override;

    Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) override;
    u32 sector_count() const override { return identity_.sectors; }
    const DiscIdentity& identity() const override { return identity_; }  // the base's, with sectors = virtual
    // The CVMs: relocated LSN and window size; replaced outer files: their extent; anything else: the base's.
    Result<std::optional<DiscFile>> find_file(std::string_view path) override;

    // Re-scans the folders (see the file comment). Ok value: overrides now applied. The caller re-applies
    // patch_rofs_tables() afterwards (GameHost::reload_mods does both).
    Result<std::size_t> reload();

    // Writes the current overrides into the game's ROFS "#DirLst#" tables in guest RAM. `image` is the guest RAM
    // holding the ELF's loaded bytes, starting at guest address `image_va`. The first call scans it for the
    // tables (it must be the freshly loaded ELF) and remembers their original entries; later calls patch the
    // same addresses, restoring entries whose override went away. Ok value: entries written.
    Result<std::size_t> patch_rofs_tables(std::span<std::byte> image, u32 image_va);
    std::size_t rofs_table_count() const;

    const ModsScan& scan() const { return scan_; }
    DiscSource& base() { return *base_; }

    // Editor controls; each takes effect at the next reload() (the caller reloads, GameHost does it for you).
    // Disabled: no folder is scanned and no file is replaced (the CVMs stay relocated, see "Reload").
    void set_enabled(bool on) { opt_.enabled = on; }
    bool enabled() const { return opt_.enabled; }
    void set_dirs(std::vector<std::filesystem::path> dirs) { opt_.dirs = std::move(dirs); }
    const std::vector<std::filesystem::path>& dirs() const { return opt_.dirs; }

    // Disc files the guest has read since the last reload() (or clear_reads()): normalised disc paths ("DATA\FIELD\
    // F005_001.PAC", "LIB31\SDRDRV.IRX"), whether or not they are replaced, sorted. A read is a sector read through
    // this source (sceCdRead from the game, module loads by the IOP HLE); this is how a host tells "the guest has
    // this file loaded: it needs a scene reload to see a change". Directory / header sectors are not files.
    const std::vector<std::string>& files_read() const { return reads_list_; }
    bool was_read(std::string_view disc_path) const { return reads_.count(std::string(disc_path)) != 0; }
    void clear_reads();
    // Set by reload(): the disc files whose served bytes this reload changed (new, changed or no longer replaced)
    // and that the guest had read at any time this session. The guest may hold the old bytes (H_Cdvd keeps loaded
    // files until the scene drops them): the "needs a scene reload" list. Conservative: a file read long ago and
    // since dropped is listed too.
    const std::vector<std::string>& stale_after_reload() const { return stale_; }
    // Called once per file, at its first read since the last reload / clear_reads (on the reading thread: the host
    // thread, inside a guest slice -- the observer must not touch the overlay).
    void set_read_observer(std::function<void(const std::string&)> f) { read_observer_ = std::move(f); }
    // Virtual LSN of a CVM's relocated image (host name "DATA.CVM"); nullopt if no such CVM.
    std::optional<u32> cvm_lsn(std::string_view host_name) const;
    // 16 hex digits over the applied overrides (path, extent, size, host write time): machine states record it.
    std::string fingerprint() const;

private:
    struct Cvm;
    struct Extent;
    struct Region;
    struct Table;
    struct Pending;

    ModsOverlay(std::unique_ptr<DiscSource> base, ModsOptions options);
    Result<std::size_t> init_layout();
    Result<std::size_t> rescan();
    void log(std::string_view s) const;
    Result<std::vector<std::byte>*> patch_sector(u32 vlsn);
    Result<std::size_t> read_unpatched(u32 lsn, u32 count, std::span<std::byte> dst);
    void rebuild_regions();

    std::unique_ptr<DiscSource> base_;
    ModsOptions opt_;
    DiscIdentity identity_;
    std::vector<Cvm> cvms_;
    bool base_has_iso_ = false;
    u32 outer_window_ = 0, outer_cursor_ = 0;
    std::vector<std::shared_ptr<Extent>> extents_;       // every extent ever allocated (never freed)
    std::map<std::string, std::shared_ptr<Extent>> live_;  // disc_path -> the extent currently served
    std::vector<Region> regions_;                         // sorted by start
    std::map<u32, std::vector<std::byte>> patched_;       // virtual LSN -> 2048 patched bytes
    struct FileSpan {
        u32 start = 0, count = 0;
        std::string path;
    };
    std::vector<FileSpan> files_;   // every disc file at its virtual LSN (CVM members in their windows), sorted
    std::set<std::string> reads_, reads_ever_;
    std::vector<std::string> reads_list_, stale_;
    std::function<void(const std::string&)> read_observer_;
    void note_read(u32 lsn, u32 count);
    void note_file(const std::string& path);
    std::vector<Table> tables_;
    bool tables_scanned_ = false;
    u32 image_va_ = 0;
    std::size_t image_size_ = 0;
    u32 scans_ = 0;
    ModsScan scan_;
};

}  // namespace p3fes::hle
