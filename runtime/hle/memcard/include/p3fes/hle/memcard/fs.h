// The PS2 memory-card file system on top of Card: superblock, FAT (through the indirect FAT clusters),
// directory entries, a formatter and a read-only view.
//
// Sources: Ross Ridge, "PlayStation 2 Memory Card File System" (superblock fields, 2-page clusters,
// indirect FAT, FAT entry encoding 0x80000000|next / 0xFFFFFFFF end / 0x7FFFFFFF free, 512-byte directory
// entries, root "." / ".."); ps2sdk @ 329e2bb (AFL-2.0) mcman-internal.h MCDevInfo and libmc-common.h
// McFsEntry / sceMcFileAttr* for the field names and offsets. The formatter's values follow what the game's
// own libmc2 formatter writes (obs, _sceMcFatFormat 0x516118): magic "Sony PS2 Memory Card Format" +
// " 1.2.0.0" (0x51625C/0x516294), page 512 / 2 pages per cluster / 16 per block / 0xFF00 (0x5162B4-0x5162E0),
// card type 2, flags 0x2B (0x5162F8/0x5162FC), cluster size 1024 and 256 FAT entries per cluster at +340/+344,
// backup blocks = the last two good blocks (0x516354-0x51638C), the IFC list at +80, the FAT clusters right
// after the indirect FAT cluster, alloc_end = backup_block2 * 8 - alloc_offset (0x516648), "." mode 0x8427
// length 2 (0x516788). Every page is programmed as 512 data + 12 ECC bytes (MC2_S1 programs page+ECC; the
// last 4 spare bytes stay erased). Not verified against a card the game itself formatted (no such image here).
#pragma once

#include <array>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "p3fes/ee_types.h"
#include "p3fes/hle/memcard/card.h"

namespace p3fes::hle::memcard {

inline constexpr char kSuperblockMagic[] = "Sony PS2 Memory Card Format ";  // 28 bytes incl. the space
inline constexpr u32 kPagesPerCluster = 2;
inline constexpr u32 kClusterSize = kPageSize * kPagesPerCluster;  // 1024
inline constexpr u32 kClusters = kPages / kPagesPerCluster;          // 8192
inline constexpr u32 kFatPerCluster = kClusterSize / 4;              // 256
inline constexpr u32 kDirEntrySize = 512;

inline constexpr u32 kFatFree = 0x7FFFFFFFu;
inline constexpr u32 kFatEnd = 0xFFFFFFFFu;
inline constexpr u32 kFatAllocated = 0x80000000u;

// sceMcFileAttr* (ps2sdk libmc-common.h).
namespace mode {
inline constexpr u16 kRead = 0x0001, kWrite = 0x0002, kExec = 0x0004, kProtected = 0x0008;
inline constexpr u16 kFile = 0x0010, kDir = 0x0020, kClosed = 0x0080, k0400 = 0x0400;
inline constexpr u16 kPs1 = 0x1000, kHidden = 0x2000, kExists = 0x8000;
}  // namespace mode

// sceMcStDateTime: binary fields (not BCD).
struct DateTime {
    u8 sec = 0, min = 0, hour = 0, day = 1, month = 1;
    u16 year = 2026;
};

struct Superblock {
    std::string magic;    // 28 bytes
    std::string version;  // 12-byte field, NUL-trimmed ("1.2.0.0")
    u16 page_len = 0, pages_per_cluster = 0, pages_per_block = 0, unused = 0;
    u32 clusters_per_card = 0, alloc_offset = 0, alloc_end = 0, rootdir_cluster = 0;
    u32 backup_block1 = 0, backup_block2 = 0;
    std::array<u32, 32> ifc_list{};
    std::array<s32, 32> bad_block_list{};
    u8 card_type = 0, card_flags = 0;
};

// Superblock from page 0's data. nullopt + `why` if the magic or geometry does not describe the
// standard 8 MiB card this model implements (an unformatted card has no magic).
std::optional<Superblock> parse_superblock(std::span<const u8> page0, std::string* why = nullptr);

struct DirEntry {
    u16 mode = 0;
    u32 length = 0;  // files: bytes; directories: entries
    DateTime created, modified;
    u32 cluster = 0;    // first cluster, relative to alloc_offset
    u32 dir_entry = 0;  // "." of a directory: its index in the parent
    u32 attr = 0;
    std::string name;
};
DirEntry parse_dir_entry(std::span<const u8> b);  // b: >= 512 bytes
void encode_dir_entry(const DirEntry& e, std::span<u8> b);

// Writes an empty file system to `card` (erasing every block first). `now` stamps the root entries.
void format(Card& card, const DateTime& now = {});

// Programs one cluster (2 pages of data, each with its 12 ECC bytes) the way MC2_S1 does: the target block
// must be erased. Used by the formatter and the tests.
void program_cluster(Card& card, u32 abs_cluster, std::span<const u8> data /*1024*/);

// Read-only view of a formatted card.
class FsView {
public:
    explicit FsView(const Card& card);
    bool ok() const { return sb_.has_value(); }
    const std::string& error() const { return error_; }
    const Superblock& superblock() const { return *sb_; }

    // Cluster data (1024 bytes) at an absolute cluster number; ECC-checked (a mismatch is counted).
    std::vector<u8> read_cluster(u32 abs_cluster) const;
    // FAT entry of a cluster relative to alloc_offset (through ifc_list); nullopt if out of range.
    std::optional<u32> fat(u32 rel_cluster) const;
    // Relative clusters of a chain starting at `first` (stops at the end marker, a free entry or a loop).
    std::vector<u32> chain(u32 first) const;
    // `count` entries of the directory whose first cluster is `first`.
    std::vector<DirEntry> read_dir(u32 first, u32 count) const;
    std::vector<DirEntry> root() const;
    u32 free_clusters() const;
    u32 ecc_errors() const { return ecc_errors_; }

private:
    const Card& card_;
    std::optional<Superblock> sb_;
    std::string error_;
    mutable u32 ecc_errors_ = 0;
};

}  // namespace p3fes::hle::memcard
