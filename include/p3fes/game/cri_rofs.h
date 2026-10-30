// CRI ROFS (the CVM file system) directory helpers, hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/11_file_io.md §1; names are the IDA names in symbols/p3fes.sym).
//
// The `#DirLst#` tables the ELF embeds (149 of them, one per directory of the three CVMs) carry a
// one-byte lookup hash per entry, consulted by the sequential search (`rfdir_nameSequentialSearch`):
//   search_id = ((218 + sum of rfdir_toUpperFname(c) over the name) >> 2) & 0xFF
// verified equal on all 12,016 entries (ida/logs/file_io_tables.txt). CVM volumes use the binary
// search, so in this game the hash is computed but only the sequential path compares it.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// 0x56BC78. One character of a file name for hashing/comparison: ASCII lowercase becomes uppercase,
// '.' becomes 0 (so "NAME" and "NAME." hash alike), everything else is returned unchanged.
char rfdir_toUpperFname(EEContext& ctx, char c);

// 0x56BC10. The lookup hash of a NUL-terminated name (see above). An empty name hashes to 54.
u8 rfdir_getSearchID(EEContext& ctx, const char* name);

// 0x569848 (tge-pr4's name, verified in topic 11 and promoted on the IDA master 2026-10-20 through
// symbols/deltas/rofs_toupper.sym; sub_569848 before that). Uppercases an ASCII string in guest
// memory in place (a-z only, every byte up to and including the NUL); a null pointer is ignored. Called
// by the CVM binary search for every file open, with the query name.
void RFMAI_ToUpperStr(EEContext& ctx, u32 str_va);

// --- directory tables (docs/ANALYSIS/11 §1 "Record definitions"), as laid out in guest RAM ---------
struct RofsDirLstHdr {      // 24 bytes; followed by `count` RofsDirLstEnt
    u32 count;              // entries, "." and ".." included
    u32 count2;             // equals count in every table of the ELF
    u32 dir_lba;
    char marker[8];         // "#DirLst#"
    u32 zero;
};
struct RofsDirLstEnt {      // 48 bytes
    u32 size_lo;            // low half of the 64-bit file size
    u32 size_hi;
    u32 lba;
    u8 flags;               // bit 1: directory
    u8 search_id;           // rfdir_getSearchID(name)
    char name[34];          // NUL-terminated, uppercase, ";1" stripped; extension-less files carry a trailing '.'
};
struct RofsVolume {         // 52 bytes (array at g_rofs_work+40); only the fields the searches read are named
    s32 img_hn;
    s32 lba_offset;         // 3 for the three CVMs, 0 for a volume read through ISO directory records
    s32 root_lba;
    s32 root_size;
    u32 dir;                // RofsDirLstHdr* set by ROFS_SetDir
    u8 rest[32];
};
static_assert(sizeof(RofsDirLstHdr) == 24 && sizeof(RofsDirLstEnt) == 48 && sizeof(RofsVolume) == 52);
constexpr u32 kRofsDirEntFlagDir = 2;
constexpr u32 kRofsDirEntryOffset = sizeof(RofsDirLstHdr);  // table + 24 + 48 * i
// Guest address of entry `i` (0-based) of the table at `dir_va`.
inline u32 rofs_dir_entry(u32 dir_va, u32 i) noexcept { return dir_va + kRofsDirEntryOffset + i * sizeof(RofsDirLstEnt); }

// 0x56C2E0. 1 if the NUL-terminated name in guest RAM contains a '.', else 0 (an empty name has none).
void rfdir_isContainPeriod(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x56BAC8. File-name equality for the sequential search: the two names (guest RAM) are compared
// character by character through rfdir_toUpper (ASCII case-insensitive) until `a` ends -- at its NUL
// or at a single '.' right before it -- and `b` must end the same way there, so "NAME", "name" and
// "NAME." are all equal. (Not symmetric at the edge: ".." equals "." but "." does not equal "..",
// because b's '.' is compared as an ordinary character while a still has one.) 1 when equal, else 0.
void rfdirStrcmpFileName(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x56C320. The CVM lookup (docs/ANALYSIS/11 §1 step 4): "." -> 1, ".." -> 2; otherwise the query is
// uppercased (into a 512-byte frame buffer) and a copy gets a '.' appended when it contains none, then
// a binary search over entries [2, count] compares directory entries (flags & 2) against the raw
// uppercase query and file entries against the dotted one with strcmp (case-sensitive, exact length).
// Returns the 1-based entry index, 0 when not found or `name_va` is null. The uppercased copy is left
// in the two frame buffers, as the original left it on its stack.
s32 rfdir_nameBinarySearch(EEContext& ctx, u32 name_va, u32 dir_va);

// 0x56C4B0. The lookup for volumes without an LBA offset: "." -> 1, ".." -> 2; otherwise the first
// entry whose search_id equals rfdir_getSearchID(name) and whose name matches -- rfdirStrcmpDirName
// for directories, rfdirStrcmpFileName for files -- 1-based; 0 when none or `name_va` is null.
s32 rfdir_nameSequentialSearch(EEContext& ctx, u32 name_va, u32 dir_va);

// 0x56C5B0. Entry point of RFMAI_OpenG: the binary search when the volume has an LBA offset (every CVM),
// else the sequential one; 0 for a null volume.
void RFDIR_SearchName(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
