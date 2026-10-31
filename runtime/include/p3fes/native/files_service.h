// Modernize pass, layer 1: disc and files (docs/MODERNIZE_PLAN.md §3, ADR-0017; runtime/hle/README.md §7).
//
// The seam between the game's own CD wrappers and the host. With `--native files` the host installs a FileService
// (runtime/native/files/native_files.h) in `g_service`; the game's wrappers then read host files by path and
// complete at once instead of going through CRI's SRD / libcdvd / SIF / cdvdfsv / the emulated CDVD:
//   H_Cdvd_Update 0x100980   (the game's loader)  a queued whole-file load is read by path and is loaded (state 4)
//                                                 in the same pump; every queued request completes in one call
//   dvCiCdSearchFile 0x559DD8 (CRI's CD device)   sceCdSearchFile for the CVM containers ("\DATA.CVM;1")
//   dvCiReqRd 0x55A490        (CRI's CD device)   a container read (ROFS mount sectors, ADX / Sofdec stream chunks):
//                                                 the handle is complete when the call returns
// With `g_service == nullptr` (the default, `--native` without `files`) every one of them runs its faithful body
// unchanged. The game library depends on headers only, so this is an interface plus an inline pointer.
#pragma once

#include <array>
#include <cstddef>
#include <optional>
#include <span>
#include <string>
#include <string_view>

#include "p3fes/ee_types.h"

namespace p3fes::native::files {

// A file found by path.
struct FileRef {
    u32 id = 0;    // the service's handle for read() (never 0 for a found file)
    u64 size = 0;  // bytes (a replaced file: the mod file's size)
    u32 lsn = 0;   // disc LSN of its first sector on the user's disc (the read log's key; a replaced file keeps the
                   // disc file's LSN: no relocation in native mode)
};

// What sceCdSearchFile answers for an outer disc file (cdvdfsv's sceCdlFILE).
struct OuterFile {
    FileRef file;
    std::string identifier;        // as recorded, e.g. "DATA.CVM;1"
    std::array<u8, 7> recorded{};  // ISO9660 recording date and time (directory record bytes 18-24)
};

class FileService {
public:
    virtual ~FileService() = default;

    // "DATA.CVM:\FIELD\X.PAC" (a CVM member, the read log's form) or "DATA.CVM", "LIB31\X.IRX" (outer files).
    // Case-insensitive; '/' or '\'; a leading '\', ";N" versions and a trailing '.' are optional.
    virtual std::optional<FileRef> find(std::string_view path) = 0;

    // libcdvd's form, "\DATA.CVM;1": an outer file with its directory record.
    virtual std::optional<OuterFile> search(std::string_view cd_path) = 0;

    // The outer file whose extent starts at disc LSN `lsn` (a dvCi handle keeps only that, at +32).
    virtual std::optional<FileRef> outer_at(u32 lsn) = 0;

    // Copies dst.size() bytes from byte `offset` of `f`. Past the end of a disc file the bytes are the disc's own
    // (the rest of its last sector: what a sector read delivers); past the end of a replaced file, zeros. A container
    // read over a replaced member serves the mod file's bytes in that member's extent. `guest_dst` is the guest
    // address the bytes go to (for the read log only). false: a host read error (dst is then unspecified).
    virtual bool read(const FileRef& f, u64 offset, std::span<std::byte> dst, u32 guest_dst) = 0;
};

// Installed by the host (GameHost) while `--native files` is on; nullptr = the faithful path.
inline FileService* g_service = nullptr;
inline FileService* service() noexcept { return g_service; }

}  // namespace p3fes::native::files
