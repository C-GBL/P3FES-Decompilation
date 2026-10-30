// The game's CD layer (H_Cdvd_*, docs/ANALYSIS/11_file_io.md §2), hand-decompiled from SLUS_216.21:
// the pure path helpers, the in-memory file cache (sCdvdCache) and the name-first PAK indexing. Names
// are the IDA names in symbols/p3fes.sym.
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

constexpr u32 kHCdvdVolPrefix = 0x7CB1A8u;     // "VOL:\" (the literal at $gp-31560)
constexpr u32 kHCdvdVolPrefixPtr = 0x7CB1B8u;  // holds the address of "VOL:" (0x7CB1B0; $gp-31544)
constexpr u32 kHCdvdPathMax = 255;             // characters copied by H_Cdvd_BuildPathUppercase at most

// sCdvdCache 0x7D6F80: 256 slots registered by H_Cdvd_AddFile for the entries of every loaded PAK
// (name = UPPER(dir + name) with '/' -> '\'); also the backing of the RenderWare "pak:" device.
struct HCdvdCacheEntry {  // 148 bytes
    s32 used;
    u32 owner;
    char name[128];
    u32 data;  // guest address of the file bytes
    u32 size;
    u32 zero;
};
static_assert(sizeof(HCdvdCacheEntry) == 148);
constexpr u32 kHCdvdCache = 0x7D6F80u;
constexpr u32 kHCdvdCacheSlots = 256;

// H_Cdvd request node: `state` at +12, 4 once the whole file is in memory (H_Cdvd_Update).
constexpr u32 kHCdvdNodeState = 12;
constexpr u32 kHCdvdStateLoaded = 4;

// The request node (868 bytes; H_Cdvd_Request allocates it through the heap hook and links it behind
// sCdvdListHead 0x7E0380, H_Cdvd_Update pumps the list): two links, then the file record that
// H_Cdvd_Update hands to H_Cdvd_AddFile as `node + 8`. Offsets from the generated bodies of
// H_Cdvd_Request, H_Cdvd_Update, H_Cdvd_AddFile and H_Cdvd_ArchiveGetFile; the `unknown_*` runs are
// bytes those bodies never name.
struct HCdvdFile {  // 860 bytes at node + 8
    u32 zero;            // +0   (node +8)   cleared by H_Cdvd_Request
    u32 state;           // +4   (node +12)  kHCdvdStateLoaded once the file is in memory
    char path[256];      // +8   (node +16)  "VOL:\..." as H_Cdvd_BuildPathUppercase builds it (the dedup key)
    u32 data;            // +264 (node +272) 64-byte-aligned buffer with the file bytes (archive: + 256 zero bytes)
    u32 raw;             // +268 (node +276) the heap allocation behind `data`
    u8 unknown_272[12];
    u32 size;            // +284 (node +292) bytes of the file
    u8 unknown_288[40];
    u32 is_archive;      // +328 (node +336) the `isArchive` argument of H_Cdvd_Request
    u32 handle;          // +332 (node +340) the ADXF handle while the read is in flight
    char vol_file[256];  // +336 (node +344) "VOL:NAME" / "BTL:NAME" (H_Cdvd_BuildVolumePaths)
    char dir[256];       // +592 (node +600) the directory part of the path
    s16 entry_count;     // +848 (node +856) slots H_Cdvd_AddFile registered (1 for a plain file)
    s16 refcount;        // +850 (node +858) one per H_Cdvd_Request of the same path
    u8 unknown_852[8];
};
static_assert(sizeof(HCdvdFile) == 860);
static_assert(offsetof(HCdvdFile, data) == 264 && offsetof(HCdvdFile, size) == 284 &&
              offsetof(HCdvdFile, is_archive) == 328 && offsetof(HCdvdFile, entry_count) == 848);

struct HCdvdRequest {  // 868 bytes
    u32 prev;        // +0 the node before it (sCdvdListHead for the first)
    u32 next;        // +4 the node after it, 0 at the tail
    HCdvdFile file;  // +8
};
static_assert(sizeof(HCdvdRequest) == 868);
static_assert(offsetof(HCdvdRequest, file) + offsetof(HCdvdFile, state) == kHCdvdNodeState);
constexpr u32 kHCdvdListHead = 0x7E0380u;

// A name-first PAK entry (docs/ANALYSIS/11_file_io.md §2, runtime/formats/pak.h): the 252-byte
// NUL-padded name and the little-endian size, the data at +256, the next entry at +256 + align64(size);
// an entry whose name starts with NUL ends the archive (H_Cdvd_Update appends 256 zero bytes for that).
struct HCdvdPakEntry {
    char name[252];
    u32 size;
};
static_assert(sizeof(HCdvdPakEntry) == 256);
constexpr u32 kHCdvdPakAlign = 64;
constexpr u32 kHCdvdCacheNameMax = 255;  // characters the uppercase pass over a built name visits at most

// 0x101010. out = "VOL:\" + path with '/' -> '\' and a-z uppercased, at most 255 characters of `path`
// (a longer path is cut there and left without a terminator, as the original does).
void H_Cdvd_BuildPathUppercase(EEContext& ctx, u32 path_va, u32 out_va);

// 0x101100. Splits a built path at its last '\': `vol_file` = "VOL:" + the part after it,
// `dir` = the part up to and including it. (Without any '\' the original reads stale stack bytes past
// its unterminated reversal buffer; the hand version keeps that buffer on the guest stack for that.)
void H_Cdvd_SplitPath(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x1013F0. Copies `src` to `dst` resolving ".\" / "./" (dropped) and "..\" / "../" (the previous
// component is dropped, when there is a separator before it); stops at the NUL or after 253 input
// characters (then without a terminator).
void H_Cdvd_NormalizePath(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x1016B0. 1 when the node's state is 4 (loaded), else 0.
void H_Cdvd_IsFileLoaded(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x1021C0. Looks `path` up in sCdvdCache by its built and normalized name against each used slot's
// normalized name (strcmp): returns the data address and stores the size through `size_out`, or
// returns 0 (nothing stored). The value 1 as path is a sentinel that returns 0 at once.
void H_Cdvd_CacheFindFile(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the cache table (hcdvd_cache.cpp) ------------------------------------------------------------

// 0x102650. Takes the first unused slot of sCdvdCache for `owner`: used = 1, the 128 bytes at `name`
// copied as they are (a longer name is cut without a terminator), data, size, zero. Returns the slot
// index, -1 when all 256 slots are used (the original then does nothing). The original's $v0 is
// memcpy's result or, when full, the caller's own.
void H_Cdvd_CacheAdd(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x102030. The same body as H_Cdvd_CacheAdd compiled a second time: the registration H_Cdvd_AddFile
// uses, with the file record (node + 8) as owner.
void H_Cdvd_AddFileCacheEntry(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x102870. Clears `used` of every slot whose owner is `owner` (H_Cdvd_Destroy, and the UI loaders
// for the PAKs they registered with H_Cdvd_CacheAddArchive).
void H_Cdvd_CacheRemove(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- name-first PAKs (hcdvd_pak.cpp) --------------------------------------------------------------

// 0x101E30, `file` = node + 8 (H_Cdvd_Update calls it once the read is complete). A plain file takes one
// slot under file.path with file.entry_count = 1. An archive: the directory of file.path (everything up
// to and including the last '\', found by a backward scan from each NUL of the 256-byte path) + each
// entry's name, a-z uppercased and '/' -> '\', one slot per entry with owner = the file record and
// data = the entry bytes; file.entry_count counts the entries.
void H_Cdvd_AddFile(EEContext& ctx, u32 file_va);

// 0x102720. Registers every entry of the PAK at `pak` under UPPER("VOL:\" + dir + name) with owner =
// pak (H_Cdvd_CacheRemove(pak) takes them out again): the UI loaders use it for PAKs they read
// themselves (sub_115F00, sub_1167F0, sub_117540).
void H_Cdvd_CacheAddArchive(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x102100. Entry `index` of the node's archive: walks `index` headers (no terminator check), returns
// the data address and stores the entry size through `size_out`.
void H_Cdvd_ArchiveGetFile(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x1022E0. The header address of entry `index` of the node's archive, 0 when the archive ends at or
// before it.
void H_Cdvd_GetArchiveFileBuffer(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
