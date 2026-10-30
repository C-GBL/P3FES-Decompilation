// libmc2's cluster cache, socket helpers and blocking API (0x5130E8-0x51C330): the per-port write-cluster cache
// (libs1::mc2::kClustCache: a run of up to 16 consecutive clusters of one erase block), the superblock page reads /
// writes, the bad-block checks, the core layer's small socket helpers, and the blocking sceMc2* calls (the async request
// followed by sceMc2Sync2, both still recompiled: they wait on kernel semaphores).
//
// Register ABI (arguments in $a0.., the result in $v0); one role line per function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs1::mc2 {
constexpr u32 kClustCache = 0x97CCC0u;  // per port 16400 bytes: first, last, erase block, count, 16 x 1024-byte clusters
constexpr s32 kClustCacheStride = 16400;
constexpr u32 kSysPage = 0x984D00u;     // the page buffer of the superblock reads / writes
constexpr u32 kCoreSockets = 0x985508u; // the core layer: 2 sockets x 36 bytes (+0 used, +4 DBC id, +8 page length, ...)
constexpr s32 kCoreStride = 36;
}  // namespace libs1::mc2


// Close a card socket (refused while a request runs).
void sceMc2DeleteSocket(EEContext& ctx);  // 0x5133F8 (register ABI: arguments in $a0.., the result in $v0)
// Wait for the running request (sceMc2Sync2 mode 0).
void sceMc2Sync(EEContext& ctx);  // 0x514928 (register ABI: arguments in $a0.., the result in $v0)
// Blocking card information: the async request, then a wait for its result.
void sceMc2GetInfo(EEContext& ctx);  // 0x514950 (register ABI: arguments in $a0.., the result in $v0)
// Blocking format.
void sceMc2Format(EEContext& ctx);  // 0x514990 (register ABI: arguments in $a0.., the result in $v0)
// Blocking unformat.
void sceMc2Unformat(EEContext& ctx);  // 0x5149D0 (register ABI: arguments in $a0.., the result in $v0)
// Blocking file read.
void sceMc2ReadFile(EEContext& ctx);  // 0x514A10 (register ABI: arguments in $a0.., the result in $v0)
// Blocking file write.
void sceMc2WriteFile(EEContext& ctx);  // 0x514A50 (register ABI: arguments in $a0.., the result in $v0)
// Blocking fast file read.
void sceMc2ReadFastFile(EEContext& ctx);  // 0x514A90 (register ABI: arguments in $a0.., the result in $v0)
// Blocking fast file write.
void sceMc2WriteFastFile(EEContext& ctx);  // 0x514AD0 (register ABI: arguments in $a0.., the result in $v0)
// Blocking create.
void sceMc2CreateFile(EEContext& ctx);  // 0x514B10 (register ABI: arguments in $a0.., the result in $v0)
// Blocking delete.
void sceMc2Delete(EEContext& ctx);  // 0x514B50 (register ABI: arguments in $a0.., the result in $v0)
// Blocking rename.
void sceMc2Rename(EEContext& ctx);  // 0x514B90 (register ABI: arguments in $a0.., the result in $v0)
// Blocking make-directory.
void sceMc2Mkdir(EEContext& ctx);  // 0x514BD0 (register ABI: arguments in $a0.., the result in $v0)
// Blocking change-directory.
void sceMc2Chdir(EEContext& ctx);  // 0x514C10 (register ABI: arguments in $a0.., the result in $v0)
// Blocking directory listing.
void sceMc2GetDir(EEContext& ctx);  // 0x514C50 (register ABI: arguments in $a0.., the result in $v0)
// Blocking attribute change.
void sceMc2Chmod(EEContext& ctx);  // 0x514C90 (register ABI: arguments in $a0.., the result in $v0)
// Blocking file look-up.
void sceMc2SearchFile(EEContext& ctx);  // 0x514CD0 (register ABI: arguments in $a0.., the result in $v0)
// Blocking free-entry query.
void sceMc2GetEntSpace(EEContext& ctx);  // 0x514D10 (register ABI: arguments in $a0.., the result in $v0)
// Empty both ports' write-cluster caches (first cluster -1, count 0).
void _sceMcpInit(EEContext& ctx);  // 0x51A140 (register ABI: arguments in $a0.., the result in $v0)
// The card geometry from the core layer (_sceMcCoreGetCardSpec).
void _sceMcpGetCardSpec(EEContext& ctx);  // 0x51A180 (register ABI: arguments in $a0.., the result in $v0)
// Whether the card was changed (_sceMcCoreCheckNewCard).
void _sceMcpCheckNewCard(EEContext& ctx);  // 0x51A1A0 (register ABI: arguments in $a0.., the result in $v0)
// Authenticate the card (_sceMcCoreAuthentication).
void _sceMcpAuthentication(EEContext& ctx);  // 0x51A1C0 (register ABI: arguments in $a0.., the result in $v0)
// Read page 0 (the superblock) into 0x984D00 and copy its first 388 bytes to the port's superblock copy.
void _sceMcpReadSysInfo(EEContext& ctx);  // 0x51A1E0 (register ABI: arguments in $a0.., the result in $v0)
// Write the port's superblock copy to page 0 (padded with 0xFF).
void _sceMcpWriteSysInfo(EEContext& ctx);  // 0x51A2F8 (register ABI: arguments in $a0.., the result in $v0)
// Read N card clusters (clusters x pages per cluster) through _sceMcCoreReadPage.
void _sceMcpReadClust(EEContext& ctx);  // 0x51A418 (register ABI: arguments in $a0.., the result in $v0)
// Write N card clusters through _sceMcCoreWritePage.
void _sceMcpWriteClust(EEContext& ctx);  // 0x51A458 (register ABI: arguments in $a0.., the result in $v0)
// Write the cached run of user clusters back and empty the cache.
void _sceMcpFlushCache(EEContext& ctx);  // 0x51A498 (register ABI: arguments in $a0.., the result in $v0)
// Queue one user cluster in the write cache: starts a run, appends a consecutive cluster of the same erase block (up
// to 16), or flushes and starts over.
void _sceMcpWriteUserClustOnCache(EEContext& ctx);  // 0x51A508 (register ABI: arguments in $a0.., the result in $v0)
// Read one user cluster (allocation offset added): from the write cache when it holds it, else from the card.
void _sceMcpReadUserClustOnCache(EEContext& ctx);  // 0x51A8A0 (register ABI: arguments in $a0.., the result in $v0)
// Read one user cluster (through the write cache).
void _sceMcpReadUserClust(EEContext& ctx);  // 0x51A9E0 (register ABI: arguments in $a0.., the result in $v0)
// Read user clusters straight from the card (_sceMcCoreReadPageFast).
void _sceMcpReadUserClustFast(EEContext& ctx);  // 0x51AA00 (register ABI: arguments in $a0.., the result in $v0)
// Write user clusters straight to the card (_sceMcCoreWritePageFast).
void _sceMcpWriteUserClustFast(EEContext& ctx);  // 0x51AA48 (register ABI: arguments in $a0.., the result in $v0)
// Write N consecutive user clusters through the write cache; 0 on the first failure.
void _sceMcpWriteUserClust(EEContext& ctx);  // 0x51AA90 (register ABI: arguments in $a0.., the result in $v0)
// Whether a block is in the superblock's bad-block list (32 entries).
void _sceMcpIsSpeckOutBlock(EEContext& ctx);  // 0x51AB08 (register ABI: arguments in $a0.., the result in $v0)
// Whether a cluster lies in a bad block.
void _sceMcpIsSpeckOutClust(EEContext& ctx);  // 0x51AB50 (register ABI: arguments in $a0.., the result in $v0)
// Build the bad-block list for a format: reads the first pages of every block and lists (up to 16) blocks whose data
// is not all 0xFF.
void _sceMcpMakeSpecoutBlock(EEContext& ctx);  // 0x51AB98 (register ABI: arguments in $a0.., the result in $v0)
// Set a socket's write-back blocks (the backup blocks of the superblock).
void _sceMcCoreSetWriteBackHole(EEContext& ctx);  // 0x51AF70 (register ABI: arguments in $a0.., the result in $v0)
// Copy a 16-byte card geometry record into the socket's entry (+8).
void _sceMcCoreSetCardSpec(EEContext& ctx);  // 0x51AF98 (register ABI: arguments in $a0.., the result in $v0)
// Read pages with the socket's ECC setting (_sceMcCoreReadPage2).
void _sceMcCoreReadPage(EEContext& ctx);  // 0x51B8D0 (register ABI: arguments in $a0.., the result in $v0)
// 1 for a socket number below 2 whose entry is in use.
void _sceMcCoreCheckSocket(EEContext& ctx);  // 0x51C250 (register ABI: arguments in $a0.., the result in $v0)
// The libmc2 socket (0 / 1) that holds a DBC socket id; -1 when none does.
void _sceMcCoreChangeSocketTypeDbc2Mc(EEContext& ctx);  // 0x51C2E8 (register ABI: arguments in $a0.., the result in $v0)
// The DBC socket id of a libmc2 socket; -1 when unused.
void _sceMcCoreChangeSocketTypeMc2Dbc(EEContext& ctx);  // 0x51C330 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
