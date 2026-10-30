// The physical PS2 memory card behind DBCMAN/MC2_S1: an 8 MiB NAND image of 16,384 raw pages of 528 bytes
// (512 data + 16 spare, the spare starting with the page's 12 ECC bytes), erased in blocks of 16 pages.
//
// Sources: Ross Ridge, "PlayStation 2 Memory Card File System" (§physical layout: page/spare/erase-block
// sizes; erased flash reads all ones); ps2sdk @ 329e2bb mcman-internal.h (AFL-2.0, field names only).
// Observed: the standard card spec the game expects -- 512 / 16 / 16,384 -- in _sceMcCoreInit 0x51AE68 and
// _sceMcCoreCreateSocket 0x51C218, and in the PCSX2 atlus_logo state (0x985510: 0x200, 0x10, 0x4000);
// the PCSX2 card image (tools/third_party/pcsx2/memcards/Mcd001.ps2) is 8,650,752 bytes, all 0xFF.
//
// Device rules (what MC2_S1's SIO2 page commands can do, MC2_S1.IRX .text 0xCF8 read / 0x108C program /
// 0xB00 erase): reads and programs start at byte 0 of a raw page and cover up to 528 bytes; a program can
// only clear bits (NAND: stored &= written) -- MC2_S1 always erases a block before programming it, so the
// AND only matters for a sequence the real card would also corrupt; an erase sets the 16 pages of one
// block to 0xFF. Not thread-safe.
#pragma once

#include <cstddef>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include "p3fes/ee_types.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::hle::memcard {

inline constexpr u32 kPageSize = 512;
inline constexpr u32 kSpareSize = 16;
inline constexpr u32 kRawPageSize = kPageSize + kSpareSize;  // 528
inline constexpr u32 kPagesPerBlock = 16;
inline constexpr u32 kPages = 16384;
inline constexpr u32 kBlocks = kPages / kPagesPerBlock;  // 1024
inline constexpr std::size_t kImageSize = std::size_t{kPages} * kRawPageSize;  // 8,650,752
inline constexpr u8 kErasedByte = 0xFF;

struct CardStats {
    u64 page_reads = 0;
    u64 page_programs = 0;
    u64 block_erases = 0;
    u64 program_conflicts = 0;  // programs that asked for a 0 bit to become 1 (the stored bit stays 0)
    u64 rejected = 0;           // out-of-range page / oversized transfer
    u64 flushes = 0;
};

class Card;

// Where a card's changes go (source.h implements the copy-on-write file). Called by Card::flush with
// every page modified since the last successful flush, in ascending order.
class CardBacking {
public:
    virtual ~CardBacking() = default;
    virtual bool store(const Card& card, std::span<const u32> dirty_pages, std::string& error) = 0;
    virtual std::string describe() const = 0;
};

class Card {
public:
    // Every page erased (0xFF): an unformatted card, like the PCSX2 Mcd001.ps2 the oracle runs with.
    static std::shared_ptr<Card> blank(std::string name = "blank");
    // A raw image of exactly kImageSize bytes; nullptr otherwise.
    static std::shared_ptr<Card> from_image(std::vector<u8> image, std::string name);

    // ---- device operations ---------------------------------------------------------------------------
    // Bytes [0, out.size()) of raw page `page`. false: page out of range or out.size() > 528.
    bool read(u32 page, std::span<u8> out) const;
    // Programs bytes [0, in.size()) of raw page `page` with the NAND rule (stored &= in).
    bool program(u32 page, std::span<const u8> in);
    // Erases the block containing `page` (all 16 x 528 bytes -> 0xFF).
    bool erase_block(u32 page);

    // ---- inspection ------------------------------------------------------------------------------------
    std::span<const u8> image() const { return image_; }
    std::span<const u8> raw_page(u32 page) const;  // empty if out of range
    const std::string& name() const { return name_; }
    const CardStats& stats() const { return stats_; }
    bool dirty() const { return !dirty_.empty(); }

    // ---- persistence -------------------------------------------------------------------------------------
    void set_backing(std::unique_ptr<CardBacking> b) { backing_ = std::move(b); }
    const CardBacking* backing() const { return backing_.get(); }
    // Hands the dirty pages to the backing (no-op without one or when clean). false + `error` on failure;
    // the pages stay dirty and the next flush retries.
    bool flush(std::string* error = nullptr);
    // Machine state (p3fes/state_io.h): the image, the pages not yet flushed, the stats. The backing stays the
    // loading process's (its copy-on-write file).
    void state(StateIo& io);

    explicit Card(std::vector<u8> image, std::string name);

private:
    std::vector<u8> image_;
    std::string name_;
    std::vector<u32> dirty_;           // sorted, unique
    std::vector<u8> dirty_mark_;       // one byte per page
    std::unique_ptr<CardBacking> backing_;
    mutable CardStats stats_;

    void mark(u32 page);
};

}  // namespace p3fes::hle::memcard
