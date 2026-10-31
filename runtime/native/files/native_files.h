// Modernize layer 1 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the host's native files service.
//
// NativeFiles answers the game's CD wrappers by path (p3fes/native/files_service.h). Its table is the disc's own
// directories: every outer file and every CVM member, the same walk and the same path strings as the read log
// (hle::DiscPathIndex). A disc file is a byte range of the host file (the user's ISO, or extracted/disc's CVMs placed
// by kDiscLayout); reads copy from it directly through the DiscSource's host reader. Nothing here goes through the
// IOP, cdvdfsv, SIF or the emulated CDVD.
//
// Mods (ADR-0016) in native mode are a lookup by path: an override replaces the file's bytes and size with the mod
// file's (read from the host file at each read, zero-padded), at the disc file's own LSN -- no relocated extents,
// and the game's ROFS tables are not patched. A container read (dvCi: an ADX / Sofdec stream) over a replaced
// member serves the mod file's bytes inside that member's disc extent: CRI ROFS still clamps a stream to the size in
// the ELF's #DirLst# table, so a streamed replacement longer than the disc file is cut there (README §7 "what is
// left").
//
// Not thread-safe: one owner (the host thread that runs guest code).
#pragma once

#include <cstddef>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "p3fes/hle/disc_source.h"
#include "p3fes/hle/mods_overlay.h"
#include "p3fes/native/files_service.h"

namespace p3fes::native::files {

// One read the service served, for the read log (GameHost formats it like a cdvdfsv read: lsn = the file's LSN +
// offset / 2048, sectors = bytes / 2048 rounded up; the path then comes from the same DiscPathIndex).
struct NativeRead {
    u32 lsn = 0;
    u32 sectors = 0;
    u32 guest_dst = 0;
    std::span<const std::byte> data;
};

// The by-path key: upper case, '\' separators, no leading '\', and per component no ";N" and no trailing '.'.
std::string path_key(std::string_view path);

class NativeFiles final : public FileService {
public:
    // Indexes `disc` (which must outlive this object). Unsupported if the disc has no CVM member at all.
    static hle::Result<std::unique_ptr<NativeFiles>> open(hle::DiscSource& disc);
    ~NativeFiles() override;

    std::optional<FileRef> find(std::string_view path) override;
    std::optional<OuterFile> search(std::string_view cd_path) override;
    std::optional<FileRef> outer_at(u32 lsn) override;
    bool read(const FileRef& f, u64 offset, std::span<std::byte> dst, u32 guest_dst) override;

    // Mods by path: replaces the current set (call again after a mods reload). Overrides whose disc path is not a
    // file of this disc are skipped. Returns the number applied.
    std::size_t set_overrides(const std::vector<hle::ModOverride>& overrides);
    void set_read_observer(std::function<void(const NativeRead&)> f) { observer_ = std::move(f); }
    // Called with the path of every find() / search() that found nothing (the game retries those every frame).
    void set_miss_observer(std::function<void(std::string_view)> f) { miss_ = std::move(f); }

    std::size_t outer_files() const { return outer_count_; }
    std::size_t members() const { return entries_.size() - outer_count_; }
    // Every file: path (the read log's form), disc LSN, size on the disc. In index order (outer files first).
    template <typename Fn>
    void for_each_file(Fn&& fn) const {
        for (const Entry& e : entries_) fn(e.path, e.lsn, e.disc_size);
    }

private:
    struct Entry {
        std::string path;        // "DATA.CVM:\FIELD\X.PAC" / "DATA.CVM"
        u32 lsn = 0;             // first disc LSN
        u32 sectors = 0;         // disc extent
        u64 disc_size = 0;       // bytes on the disc
        bool outer = false;
        u32 container = 0;       // a member: the id of its CVM (0 for outer files)
        std::filesystem::path host;  // a replaced file: the mod file (empty = the disc's bytes)
        u64 host_size = 0;
    };

    explicit NativeFiles(hle::DiscSource& disc) : disc_(disc) {}
    const Entry* entry(u32 id) const { return (id && id <= entries_.size()) ? &entries_[id - 1] : nullptr; }
    FileRef ref(u32 id) const;
    bool read_disc(u64 byte_offset, std::span<std::byte> dst);
    bool read_host(const Entry& e, u64 offset, std::span<std::byte> dst);

    hle::DiscSource& disc_;
    std::vector<Entry> entries_;                   // id = index + 1
    std::size_t outer_count_ = 0;
    std::unordered_map<std::string, u32> by_key_;  // path_key -> id
    std::map<u32, u32> outer_by_lsn_;              // first LSN -> id
    std::map<u32, std::vector<u32>> replaced_in_;  // container id -> replaced member ids
    std::vector<std::byte> bounce_;                // partial sectors
    std::function<void(const NativeRead&)> observer_;
    std::function<void(std::string_view)> miss_;
};

}  // namespace p3fes::native::files
