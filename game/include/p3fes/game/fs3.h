// Phase 5 slice fs3: the rest of the pure file-layer functions (docs/ANALYSIS/11_file_io.md §1, §4), hand-decompiled
// from SLUS_216.21 -- the CRI ROFS name handling (rofs_dir.c / rofs_mai.c: volume-name split, volume table, ISO
// directory record -> #DirLst# entry, the case-insensitive comparers) and the BTL/VOL routing of a request path
// (h_cdvd.c: H_Cdvd_BuildVolumePaths). H_Cdvd_Request / H_Cdvd_Destroy stay recompiled (heap hooks, the debug
// printf ring, ADXF's close). Names are the IDA names in symbols/functions.json; proposed names for the sub_* ones
// are in comments here.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// --- CRI ROFS globals (docs/ANALYSIS/11 §1) ---------------------------------------------------------------------
constexpr u32 kRofsWorkPtr = 0x7B2700u;   // holds the address of the ROFS work area (g_rofs_work)
// Fields of the work area the functions below read (offsets observed in rfmai_getVolume / rfmai_getDirBufAdr /
// sub_568368).
constexpr u32 kRofsWorkMaxVolumes = 8;    // s32: volume slots (3 in this game, ROFS_Init's cfg)
constexpr u32 kRofsWorkMaxDirEnts = 12;   // s32: #DirLst# entries per directory buffer (836)
constexpr u32 kRofsWorkVolumes = 40;      // RofsVolume[max_volumes], 52 bytes each; directory buffers follow
constexpr u32 kRofsWorkDefVolume = 44;    // RofsVolume* of the default volume (ADXF_SetDefDev("VOL")), 0 when none
constexpr u32 kRofsVolumeName = 22;       // char[9]: the volume name inside a RofsVolume
constexpr u32 kRofsVolumeSize = 52;
constexpr u32 kRofsDevName = 0x7C72A0u;   // "ROFS": the device name rfmai_getVolume maps to the default volume
constexpr u32 kRofsCd001 = 0x7C7298u;     // "CD001": the ISO9660 standard identifier rfmai_checkMedia compares

// 0x56B980. ASCII toupper of a byte (sign-extended as `lb` left it); the result is sign-extended as well.
void rfdir_toUpper(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x56B9A8. Case-insensitive comparison of at most `n` characters of two guest strings: 1 when equal over those
// characters (or `n` <= 0), 0 otherwise; when `a` ends first the result is whether `b` ends at the same place.
void rfdirStrncmpi(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x56BA48. Directory-name equality for the sequential search: case-insensitive, exact length. 1 / 0.
void rfdirStrcmpDirName(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x56BBA0. Characters of `str` before the first one that occurs in `delims` (both NUL-terminated guest strings).
void rfdir_getTokenSize(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x56BCB0. One ISO9660 directory record (`rec`, read through RFMAI_CopyStructCdDr into its static struct) ->
// one 48-byte #DirLst# entry at `out`: zeroed, size_lo = data length, lba = extent, flags = file flags, the name
// (files: identifier minus its ";1"; directories: whole, with the "\0" / "\1" identifiers becoming "." / ".."),
// search_id = rfdir_getSearchID(name). Returns the record length, -1 when it is shorter than 34, 0 for a null
// argument.
void rfdir_getOneDirEnt(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x566F30. 1 when the five bytes at `pvd` + 1 are "CD001" (an ISO9660 volume descriptor), else 0.
void rfmai_checkMedia(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x566F78. Splits "VOL:NAME" into the volume (uppercased, through RFMAI_ToUpperStr) and the file name; a path
// without ':' keeps its name and gets the default volume's name (sub_568368). The path is scanned through a
// 512-byte frame buffer (at most 512 characters per part; a path of 513+ characters is refused). Each part must
// fit its buffer with its NUL (`vol_cap`, `name_cap`). Returns 1 on success, 0 on a null / non-positive argument,
// a too-long path or part, or no default volume.
void rfmai_divideFname(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x567188. The directory buffer of volume slot `idx`: work.volumes + 52 * max_volumes + idx * (24 + 48 *
// max_dir_ents); 0 when idx < 0 or idx > max_volumes. Leaves the product in HI/LO as the original's `mult` did.
void rfmai_getDirBufAdr(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x5671F0. The RofsVolume whose name equals `name` (strcmp over the max_volumes slots); a null name with
// `use_default` == 1, or the device name "ROFS", is the default volume's name. 0 when not found.
void rfmai_getVolume(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x568368 (proposed rfmai_getDefVolName). The default volume's name (its RofsVolume + 22), 0 when none is set.
void sub_568368_regs(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x569BD0 (proposed RFMAI_CnvU32plusU32toS64, docs/ANALYSIS/11 §1 step 5). (hi << 32) | lo as one 64-bit value.
void sub_569BD0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x569BE8 (proposed RFMAI_CnvS64toU32plusU32). Stores the high word of `v` at `hi_va` and the low word at `lo_va`;
// returns the high word sign-extended (the original's $v0).
void sub_569BE8(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- H_Cdvd volume routing (docs/ANALYSIS/11 §1 step 1, §4) ------------------------------------------------------
constexpr u32 kHCdvdBtlDirNames = 0x5CDD80u; // g_tbl_rofsDirNames_BTL: dir strings routed to "BTL:", "" ends it
constexpr u32 kHCdvdBtlDirScan = 200;        // entries H_Cdvd_BuildVolumePaths looks at, at most
constexpr u32 kHCdvdVolPtr2 = 0x7CB1BCu;     // holds the address of "VOL:" ($gp-31540, a second copy of 0x7CB1B8)
constexpr u32 kHCdvdBtlPtr = 0x7CB1C8u;      // holds the address of "BTL:" ($gp-31528)

// 0x101240. `dir` = path up to and including its last '\'; `vol_file` = "VOL:" + the rest, or "BTL:" + the rest
// when the directory (normalized, without its 4-character volume prefix) is one of g_tbl_rofsDirNames_BTL. Returns
// 0. (Like H_Cdvd_SplitPath, a path without '\' leaves the reversal buffer unterminated: it stays on the guest
// stack for that.)
s32 H_Cdvd_BuildVolumePaths(EEContext& ctx, u32 path_va, u32 vol_file_va, u32 dir_va);

}  // namespace p3fes::game
