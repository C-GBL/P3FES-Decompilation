// PS2 memory-card file system: superblock parse, directory entries, formatter, read-only view (fs.h).
#include "p3fes/hle/memcard/fs.h"

#include <algorithm>
#include <cstring>

#include "p3fes/hle/memcard/ecc.h"

namespace p3fes::hle::memcard {
namespace {

u16 ld16(std::span<const u8> b, std::size_t o) { return static_cast<u16>(b[o] | (b[o + 1] << 8)); }
u32 ld32(std::span<const u8> b, std::size_t o) {
    return static_cast<u32>(b[o]) | (static_cast<u32>(b[o + 1]) << 8) | (static_cast<u32>(b[o + 2]) << 16) |
           (static_cast<u32>(b[o + 3]) << 24);
}
std::string c_string(std::span<const u8> b, std::size_t o, std::size_t max) {
    const auto first = b.begin() + static_cast<std::ptrdiff_t>(o);
    const auto last = first + static_cast<std::ptrdiff_t>(std::min(max, b.size() - o));
    return std::string(first, std::find(first, last, u8{0}));
}
void st16(std::span<u8> b, std::size_t o, u16 v) {
    b[o] = static_cast<u8>(v);
    b[o + 1] = static_cast<u8>(v >> 8);
}
void st32(std::span<u8> b, std::size_t o, u32 v) {
    for (int i = 0; i < 4; ++i) b[o + i] = static_cast<u8>(v >> (8 * i));
}

DateTime ld_time(std::span<const u8> b, std::size_t o) {
    DateTime t;
    t.sec = b[o + 1];
    t.min = b[o + 2];
    t.hour = b[o + 3];
    t.day = b[o + 4];
    t.month = b[o + 5];
    t.year = ld16(b, o + 6);
    return t;
}
void st_time(std::span<u8> b, std::size_t o, const DateTime& t) {
    b[o + 0] = 0;
    b[o + 1] = t.sec;
    b[o + 2] = t.min;
    b[o + 3] = t.hour;
    b[o + 4] = t.day;
    b[o + 5] = t.month;
    st16(b, o + 6, t.year);
}

// Standard 8 MiB layout (Ross Ridge; the values the game's _sceMcFatFormat derives for a card without bad
// blocks, see fs.h): superblock in cluster 0, the indirect FAT cluster 8 (first cluster of block 1), 32 FAT
// clusters 9..40, allocatable clusters from 41, backup blocks 1023 / 1022 at the end.
constexpr u32 kIfcCluster = (kPagesPerBlock * kPageSize + kClusterSize - 1) / kClusterSize;  // 8
constexpr u32 kFatClusters = (kClusters * 4 - 1) / kClusterSize + 1;                         // 32
constexpr u32 kAllocOffset = kIfcCluster + 1 + kFatClusters;                                 // 41
constexpr u32 kBackupBlock1 = kBlocks - 1;                                                   // 1023
constexpr u32 kBackupBlock2 = kBlocks - 2;                                                   // 1022
constexpr u32 kAllocEnd = kBackupBlock2 * (kPagesPerBlock / kPagesPerCluster) - kAllocOffset;  // 8135
static_assert(kIfcCluster == 8 && kFatClusters == 32 && kAllocOffset == 41 && kAllocEnd == 8135);

std::array<u8, kPageSize> superblock_page() {
    std::array<u8, kPageSize> p;
    p.fill(0xFF);  // _sceMcpWriteSysInfo 0x51A2F8 starts from a 0xFF page; untouched bytes keep it
    std::span<u8> b(p);
    std::fill(p.begin(), p.begin() + 40, u8{0});
    const char text[] = "Sony PS2 Memory Card Format 1.2.0.0";
    std::memcpy(p.data(), text, sizeof text - 1);
    st16(b, 40, kPageSize);
    st16(b, 42, kPagesPerCluster);
    st16(b, 44, kPagesPerBlock);
    st16(b, 46, 0xFF00);
    st32(b, 48, kClusters);
    st32(b, 52, kAllocOffset);
    st32(b, 56, kAllocEnd);
    st32(b, 60, 0);  // root directory: first allocatable cluster
    st32(b, 64, kBackupBlock1);
    st32(b, 68, kBackupBlock2);
    st32(b, 72, 0);
    st32(b, 76, 0);
    for (u32 i = 0; i < 32; ++i) st32(b, 80 + 4 * i, i == 0 ? kIfcCluster : 0u);  // ifc_list (memset 0 at 0x516430)
    for (u32 i = 0; i < 32; ++i) st32(b, 208 + 4 * i, 0xFFFFFFFFu);                 // bad_block_list: none
    b[336] = 2;     // card type: PS2
    b[337] = 0x2B;  // card flags as libmc2 writes them (0x5162FC)
    // libmc2's in-memory extension of the superblock, written to the card with it (0x5162EC-0x516348,
    // 0x516668): cluster size, FAT entries per cluster, clusters per block, three zero words, the next-free
    // search hint (set when the formatter's good-cluster count reaches clusters_per_card / 1000 * 1000 + 1;
    // der: 8001 on a card without bad clusters) and four -1 words.
    st32(b, 340, kClusterSize);
    st32(b, 344, kFatPerCluster);
    st32(b, 348, kPagesPerBlock / kPagesPerCluster);
    st32(b, 356, 0);
    st32(b, 360, 0);
    st32(b, 364, 0);
    st32(b, 368, (kClusters / 1000) * 1000 + 1);
    for (u32 o : {372u, 376u, 380u, 384u}) st32(b, o, 0xFFFFFFFFu);
    return p;
}

void program_page_with_ecc(Card& card, u32 page, std::span<const u8> data /*512*/) {
    std::array<u8, kPageSize + 12> buf{};
    std::memcpy(buf.data(), data.data(), kPageSize);
    ecc_compute(std::span<const u8>(buf.data(), kPageSize), std::span<u8>(buf.data() + kPageSize, 12));
    card.program(page, buf);
}

}  // namespace

std::optional<Superblock> parse_superblock(std::span<const u8> b, std::string* why) {
    auto fail = [&](const char* w) -> std::optional<Superblock> {
        if (why) *why = w;
        return std::nullopt;
    };
    if (b.size() < 340) return fail("superblock page shorter than 340 bytes");
    Superblock s;
    s.magic.assign(reinterpret_cast<const char*>(b.data()), 28);
    if (s.magic != kSuperblockMagic) return fail("no 'Sony PS2 Memory Card Format ' magic (unformatted card)");
    s.version = c_string(b, 28, 12);
    s.page_len = ld16(b, 40);
    s.pages_per_cluster = ld16(b, 42);
    s.pages_per_block = ld16(b, 44);
    s.unused = ld16(b, 46);
    s.clusters_per_card = ld32(b, 48);
    s.alloc_offset = ld32(b, 52);
    s.alloc_end = ld32(b, 56);
    s.rootdir_cluster = ld32(b, 60);
    s.backup_block1 = ld32(b, 64);
    s.backup_block2 = ld32(b, 68);
    for (u32 i = 0; i < 32; ++i) {
        s.ifc_list[i] = ld32(b, 80 + 4 * i);
        s.bad_block_list[i] = static_cast<s32>(ld32(b, 208 + 4 * i));
    }
    s.card_type = b[336];
    s.card_flags = b[337];
    if (s.page_len != kPageSize || s.pages_per_cluster != kPagesPerCluster || s.pages_per_block != kPagesPerBlock ||
        s.clusters_per_card != kClusters)
        return fail("geometry other than 512-byte pages / 2 per cluster / 16 per block / 8192 clusters");
    if (s.alloc_offset >= kClusters || s.alloc_end > kClusters - s.alloc_offset)
        return fail("allocatable area outside the card");
    return s;
}

DirEntry parse_dir_entry(std::span<const u8> b) {
    DirEntry e;
    e.mode = ld16(b, 0);
    e.length = ld32(b, 4);
    e.created = ld_time(b, 8);
    e.cluster = ld32(b, 16);
    e.dir_entry = ld32(b, 20);
    e.modified = ld_time(b, 24);
    e.attr = ld32(b, 32);
    e.name = c_string(b, 64, 32);
    return e;
}

void encode_dir_entry(const DirEntry& e, std::span<u8> b) {
    std::fill(b.begin(), b.begin() + kDirEntrySize, u8{0});
    st16(b, 0, e.mode);
    st32(b, 4, e.length);
    st_time(b, 8, e.created);
    st32(b, 16, e.cluster);
    st32(b, 20, e.dir_entry);
    st_time(b, 24, e.modified);
    st32(b, 32, e.attr);
    std::memcpy(b.data() + 64, e.name.data(), std::min<std::size_t>(e.name.size(), 31));
}

void program_cluster(Card& card, u32 abs_cluster, std::span<const u8> data) {
    for (u32 i = 0; i < kPagesPerCluster; ++i)
        program_page_with_ecc(card, abs_cluster * kPagesPerCluster + i, data.subspan(i * kPageSize, kPageSize));
}

void format(Card& card, const DateTime& now) {
    for (u32 blk = 0; blk < kBlocks; ++blk) card.erase_block(blk * kPagesPerBlock);
    program_page_with_ecc(card, 0, superblock_page());

    std::vector<u8> c(kClusterSize);
    // Indirect FAT cluster: the absolute FAT cluster numbers, the rest -1 (0x5164B0).
    for (u32 i = 0; i < kFatPerCluster; ++i) st32(c, 4 * i, i < kFatClusters ? kIfcCluster + 1 + i : 0xFFFFFFFFu);
    program_cluster(card, kIfcCluster, c);
    // FAT: allocatable clusters free, the root directory's cluster allocated + end of chain, entries past
    // alloc_end left at -1 (the formatter writes -1 clusters first, 0x5165C8, then the free marks).
    for (u32 f = 0; f < kFatClusters; ++f) {
        for (u32 i = 0; i < kFatPerCluster; ++i) {
            const u32 rel = f * kFatPerCluster + i;
            u32 v = rel < kAllocEnd ? kFatFree : 0xFFFFFFFFu;
            if (rel == 0) v = kFatEnd;
            st32(c, 4 * i, v);
        }
        program_cluster(card, kIfcCluster + 1 + f, c);
    }
    // Root directory: "." and "..".
    DirEntry dot;
    dot.mode = mode::kExists | mode::k0400 | mode::kDir | mode::kExec | mode::kWrite | mode::kRead;  // 0x8427
    dot.length = 2;
    dot.created = dot.modified = now;
    dot.name = ".";
    DirEntry dotdot = dot;
    dotdot.mode = 0xA426;  // the value libmc2's formatter writes (0x51687C): exists, hidden, 0x400, dir, w, x
    dotdot.length = 0;
    dotdot.name = "..";
    std::fill(c.begin(), c.end(), u8{0});
    encode_dir_entry(dot, std::span<u8>(c).first(kDirEntrySize));
    encode_dir_entry(dotdot, std::span<u8>(c).subspan(kDirEntrySize, kDirEntrySize));
    program_cluster(card, kAllocOffset, c);
}

FsView::FsView(const Card& card) : card_(card) {
    std::array<u8, kPageSize> p0{};
    card_.read(0, p0);
    sb_ = parse_superblock(p0, &error_);
}

std::vector<u8> FsView::read_cluster(u32 abs_cluster) const {
    std::vector<u8> out(kClusterSize, 0);
    for (u32 i = 0; i < kPagesPerCluster; ++i) {
        std::array<u8, kPageSize + 12> raw{};
        if (!card_.read(abs_cluster * kPagesPerCluster + i, raw)) {
            ++ecc_errors_;
            continue;
        }
        std::span<u8> data(raw.data(), kPageSize);
        if (ecc_check(data, std::span<const u8>(raw.data() + kPageSize, 12)) == EccCheck::Uncorrectable) ++ecc_errors_;
        std::memcpy(out.data() + i * kPageSize, data.data(), kPageSize);
    }
    return out;
}

std::optional<u32> FsView::fat(u32 rel) const {
    if (!ok() || rel >= kClusters) return std::nullopt;
    const u32 fat_index = rel / kFatPerCluster;
    const u32 ifc_index = fat_index / kFatPerCluster;
    if (ifc_index >= 32) return std::nullopt;
    const auto ifc = read_cluster(sb_->ifc_list[ifc_index]);
    const u32 fat_cluster = ld32(ifc, 4 * (fat_index % kFatPerCluster));
    if (fat_cluster >= kClusters) return std::nullopt;
    const auto f = read_cluster(fat_cluster);
    return ld32(f, 4 * (rel % kFatPerCluster));
}

std::vector<u32> FsView::chain(u32 first) const {
    std::vector<u32> out;
    u32 c = first;
    while (out.size() < kClusters) {
        out.push_back(c);
        const auto e = fat(c);
        if (!e || *e == kFatEnd || (*e & kFatAllocated) == 0) break;
        c = *e & 0x7FFFFFFFu;
        if (std::find(out.begin(), out.end(), c) != out.end()) break;
    }
    return out;
}

std::vector<DirEntry> FsView::read_dir(u32 first, u32 count) const {
    std::vector<DirEntry> out;
    if (!ok()) return out;
    for (u32 rel : chain(first)) {
        const auto c = read_cluster(sb_->alloc_offset + rel);
        for (u32 i = 0; i < kClusterSize / kDirEntrySize && out.size() < count; ++i)
            out.push_back(parse_dir_entry(std::span<const u8>(c).subspan(i * kDirEntrySize, kDirEntrySize)));
        if (out.size() >= count) break;
    }
    return out;
}

std::vector<DirEntry> FsView::root() const {
    if (!ok()) return {};
    const auto first = read_dir(sb_->rootdir_cluster, 1);
    if (first.empty()) return {};
    return read_dir(sb_->rootdir_cluster, std::max<u32>(first[0].length, 1));
}

u32 FsView::free_clusters() const {
    if (!ok()) return 0;
    u32 n = 0;
    for (u32 f = 0; f * kFatPerCluster < sb_->alloc_end; ++f) {
        const u32 ifc_index = f / kFatPerCluster;
        const auto ifc = read_cluster(sb_->ifc_list[ifc_index]);
        const auto c = read_cluster(ld32(ifc, 4 * (f % kFatPerCluster)));
        for (u32 i = 0; i < kFatPerCluster && f * kFatPerCluster + i < sb_->alloc_end; ++i)
            if ((ld32(c, 4 * i) & kFatAllocated) == 0) ++n;
    }
    return n;
}

}  // namespace p3fes::hle::memcard
