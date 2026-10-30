// libmc2's FAT layer (0x5153A0-0x51A078): the PS2 memory card file system on the EE (public format: the
// superblock, the indirect FAT, 1,024-byte clusters, 512-byte directory entries). Per port it keeps a copy of the
// superblock (libs1::mc2::kSuperblock), a FAT / indirect-FAT cluster cache and the current directory
// (libs1::mc2::kFatState); clusters go through the write-cluster cache of libs1_mc2.cpp and pages through the core
// layer (_sceMcCore*, still recompiled: the DBC driver on the IOP). The file operations run in libmc2's basic_thread.
//
// Register ABI (arguments in $a0.., the result in $v0); one role line per function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs1::mc2 {
// per port: the superblock copy (public card format) and the library's words after it
constexpr u32 kSuperblock = 0x7827E0u;
constexpr s32 kSuperblockStride = 388;
constexpr s32 kMagic = 0, kVersion = 28, kPageLen = 40, kPagesPerCluster = 42, kPagesPerBlock = 44, kClusters = 48;
constexpr s32 kAllocOffset = 52, kAllocEnd = 56, kRootCluster = 60, kBackup1 = 64, kBackup2 = 68, kIfcList = 80;
constexpr s32 kBadBlocks = 208, kUsableClusters = 368;
// per port: the FAT state (550 words)
constexpr u32 kFatState = 0x97B788u;
constexpr s32 kFatStateStride = 2200;
constexpr s32 kIndirectCache = 0, kFatCache = 1024, kFatCacheClust = 2048, kIndirectCacheIdx = 2052, kCurDir = 2056;
constexpr s32 kNewCard = 2184, kFormatted = 2188, kFreeSearch = 2192, kFatDirty = 2196;
constexpr u32 kEntryBuf = 0x97C8C0u;  // one cluster: two 512-byte directory entries
// a directory entry (512 bytes)
constexpr s32 kEntMode = 0, kEntLength = 4, kEntCreated = 8, kEntCluster = 16, kEntDirEntry = 20, kEntModified = 24;
constexpr s32 kEntAttr = 32, kEntName = 64;
constexpr u16 kModeRead = 0x1, kModeFile = 0x10, kModeDir = 0x20, kModeHidden = 0x2000, kModeExists = 0x8000;
// result codes
constexpr u32 kFound = 0x81010011u, kNoEntry = 0x81010002u, kIoError = 0x8101006Fu, kBadName = 0x81010016u;
constexpr u32 kFull = 0x8101001Cu, kChainEnd = 0x81010059u, kBrokenChain = 0x81019002u, kNotConnected = 0x81010013u;
constexpr u32 kUnformatted = 0x8101002Fu, kCardChanged = 0x81019003u;
}  // namespace libs1::mc2


// Reset the FAT state of both ports: no cached FAT / indirect cluster (-1), not dirty, free search from 0, the new-
// card flag set (so the next GetInfo re-reads the card), the current directory "/".
void _sceMcFatInit(EEContext& ctx);  // 0x5153A0 (register ABI: arguments in $a0.., the result in $v0)
// Reset one port's FAT state as _sceMcFatInit does for both.
void _sceMcFatInit2(EEContext& ctx);  // 0x515400 (register ABI: arguments in $a0.., the result in $v0)
// The card cluster holding the FAT entry of a cluster: reads the indirect-FAT cluster (ifc_list[n / 65536]) into the
// port's indirect cache when it is not cached, then returns its word for (n / 256) % 256; *err = 0x8101006F on a read
// failure, 0x81019001 for an unused (negative) word.
void _sceMcFatGetFatClustNum(EEContext& ctx);  // 0x515468 (register ABI: arguments in $a0.., the result in $v0)
// Write the cached FAT cluster back when it is dirty (_sceMcpWriteClust); clears the dirty flag; 0 on a write
// failure, else 1.
void _sceMcFatFlushFatCache(EEContext& ctx);  // 0x515588 (register ABI: arguments in $a0.., the result in $v0)
// The FAT entry of a cluster: finds its FAT cluster, swaps it into the FAT cache (flushing the old one first) and
// returns entry n % 256; *err as _sceMcFatGetFatClustNum.
void _sceMcFatReadFatData(EEContext& ctx);  // 0x515618 (register ABI: arguments in $a0.., the result in $v0)
// The FAT entry of a cluster, with *err = 0x81019002 for an unformatted entry (0x7FFFFFFF).
void _sceMcFatGetNextClust(EEContext& ctx);  // 0x515730 (register ABI: arguments in $a0.., the result in $v0)
// The next cluster of a chain: the entry without its in-use bit; -1 with *err = 0x81010059 at the chain's end.
void _sceMcFatGetNextClustSelf(EEContext& ctx);  // 0x515778 (register ABI: arguments in $a0.., the result in $v0)
// Store a FAT entry: swaps its FAT cluster into the cache and marks it dirty; 1, or 0 with *err set.
void _sceMcFatWriteFatData(EEContext& ctx);  // 0x5157E0 (register ABI: arguments in $a0.., the result in $v0)
// Find a free cluster (in-use bit clear) from the port's search start; restarts once from 0 when it reaches the
// usable-cluster count; *err = 0x8101001C when the card is full.
void _sceMcFatGetFreeClust(EEContext& ctx);  // 0x515910 (register ABI: arguments in $a0.., the result in $v0)
// Count the free clusters from the search start to the usable-cluster count (superblock +368).
void _sceMcFatGetFreeClustSize(EEContext& ctx);  // 0x515A40 (register ABI: arguments in $a0.., the result in $v0)
// Read directory entry N of a directory cluster chain: follows the chain two entries per cluster, reads the cluster
// into the entry buffer 0x97C8C0 and copies the 512-byte entry out (its name's 32nd byte cleared); 0x81010002 past
// the end, 0x8101006F on a read failure.
void _GetEntryByPos(EEContext& ctx);  // 0x515B18 (register ABI: arguments in $a0.., the result in $v0)
// The length of a cluster chain in clusters (0 for an empty chain -1); 0x81019002 for a broken chain (an entry
// without its in-use bit).
void _fat_chain_trace(EEContext& ctx);  // 0x515C98 (register ABI: arguments in $a0.., the result in $v0)
// Give the core layer the card geometry from the superblock: page length, pages per block, pages per card (clusters x
// 1024 / page length), ECC on.
void _reset_problem_patch(EEContext& ctx);  // 0x515D28 (register ABI: arguments in $a0.., the result in $v0)
// Card information (type 2, formatted flag, free clusters): on a new card re-reads the superblock (magic "Sony PS2
// Memory Card Format", version >= 1.1), sets the core geometry and write-back hole, counts the usable clusters,
// checks the root's "." and ".." entries; 0x81019003 once after a card change.
void _sceMcFatGetInfo(EEContext& ctx);  // 0x515D80 (register ABI: arguments in $a0.., the result in $v0)
// Erase every block of the card and reset the port's FAT state.
void _sceMcFatUnFormat(EEContext& ctx);  // 0x516A48 (register ABI: arguments in $a0.., the result in $v0)
// The checks before every file operation: card connected and not changed, formatted, authenticated; then the core
// write-back; 0 or the error code.
void _ConfInsert(EEContext& ctx);  // 0x516B48 (register ABI: arguments in $a0.., the result in $v0)
// Build the absolute path of a name (_make_path) and check its characters and component lengths; 0x81010016 /
// 0x8101005B on a bad name.
void _CheckFileDescript(EEContext& ctx);  // 0x516BE8 (register ABI: arguments in $a0.., the result in $v0)
// Find a name in a directory chain (checks the "." / ".." entries of its first cluster), copying the 512-byte entry
// out and its index; 0x81010002 when absent.
void _SearchEntry(EEContext& ctx);  // 0x516C48 (register ABI: arguments in $a0.., the result in $v0)
// Walk an absolute path component by component from the root; returns 0x81010011 with the entry (and its parent /
// index) when found, 0x81010002 with the parent when the last component is missing.
void _SearchFile(EEContext& ctx);  // 0x516EC0 (register ABI: arguments in $a0.., the result in $v0)
// Write directory entry N of a directory chain (read-modify-write of its cluster through the cluster cache).
void _SetEntryByPos(EEContext& ctx);  // 0x517310 (register ABI: arguments in $a0.., the result in $v0)
// Count the free entries of a directory chain (for the space checks of create).
void _GetFreeEntrySize(EEContext& ctx);  // 0x5174B8 (register ABI: arguments in $a0.., the result in $v0)
// Create a directory entry in a parent: takes a free slot (or appends a cluster to the parent chain), writes the
// entry, and for a directory its first cluster with "." and "..".
void _CreateEntry(EEContext& ctx);  // 0x5175E8 (register ABI: arguments in $a0.., the result in $v0)
// Update the parent directory's entry after a change (its length / modification time).
void _ParentDirUpdate(EEContext& ctx);  // 0x517AB8 (register ABI: arguments in $a0.., the result in $v0)
// Look a path up and return its {created, modified, length, mode, name} record.
void _sceMcFatSearchFile(EEContext& ctx);  // 0x517BE8 (register ABI: arguments in $a0.., the result in $v0)
// Create a file or directory: checks the name, the parent, free clusters and entries, allocates the first cluster,
// writes the entry with the card clock, updates the parent, flushes the caches.
void _sceMcFatCreateFile(EEContext& ctx);  // 0x517CD8 (register ABI: arguments in $a0.., the result in $v0)
// Read from a file at an offset: walks the chain cluster by cluster through the entry buffer; returns the bytes read.
void _sceMcFatReadFile(EEContext& ctx);  // 0x518268 (register ABI: arguments in $a0.., the result in $v0)
// Read from a file with whole clusters straight into the caller's buffer (_sceMcpReadUserClustFast) where the offset
// allows; returns the bytes read.
void _sceMcFatReadFastFile(EEContext& ctx);  // 0x518470 (register ABI: arguments in $a0.., the result in $v0)
// Write to a file at an offset: extends the chain as needed, writes through the cluster cache, updates the entry and
// the parent.
void _sceMcFatWriteFile(EEContext& ctx);  // 0x5187C0 (register ABI: arguments in $a0.., the result in $v0)
// The next cluster of a chain, allocating and linking a free one at the chain's end.
void _sceMcFatGetNextClustAlloc(EEContext& ctx);  // 0x518DA0 (register ABI: arguments in $a0.., the result in $v0)
// Write to a file with whole clusters straight from the caller's buffer where possible.
void _sceMcFatWriteFastFile(EEContext& ctx);  // 0x518E70 (register ABI: arguments in $a0.., the result in $v0)
// Delete a file or an empty directory: frees its chain in the FAT and clears its entry.
void _sceMcFatDeleteFile(EEContext& ctx);  // 0x5194F8 (register ABI: arguments in $a0.., the result in $v0)
// Change the port's current directory (checked to exist and be a directory).
void _sceMcFatChDir(EEContext& ctx);  // 0x519728 (register ABI: arguments in $a0.., the result in $v0)
// List the entries of a directory matching a wild-card name into the caller's table (continuing from an index).
void _sceMcFatGetDir(EEContext& ctx);  // 0x519850 (register ABI: arguments in $a0.., the result in $v0)
// Set a file's attributes / times from a record.
void _sceMcFatSetAttr(EEContext& ctx);  // 0x519D70 (register ABI: arguments in $a0.., the result in $v0)
// Rename an entry within its directory.
void _sceMcFatRename(EEContext& ctx);  // 0x519EF8 (register ABI: arguments in $a0.., the result in $v0)
// The free entries of a directory.
void _sceMcFatGetEntSpace(EEContext& ctx);  // 0x51A078 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
