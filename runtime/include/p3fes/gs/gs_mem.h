// GS local memory (4 MiB) and the pixel-address swizzle of every storage format the game uses (contract H-34;
// docs/ANALYSIS/14 §5: PSMCT32/24/16/16S, PSMT8/8H, PSMT4/4HL/4HH, PSMZ32/24/16/16S).
//
// Address model (GS User's Manual "Local Memory" chapter): memory is pages of 8 KiB, a page is 32 blocks of 256 B,
// a block is 4 columns of 64 B. A format fixes the page size in pixels (32-bit 64x32, 16-bit 64x64, 8-bit 128x64,
// 4-bit 128x128), the order of the 32 blocks inside a page (the block tables), and the order of the pixels inside a
// block's columns (the column tables). A buffer starts at block BP and is BW*64 pixels wide; pages of a buffer are
// laid out row-major, BW pages per row for 32/16-bit formats and BW/2 for 8/4-bit formats. The block number is
// `BP + page * 32 + block_table[...]` modulo 16384 (4 MiB), so a buffer may start mid-page.
//
// Aliasing follows from the shared geometry: a PSMT8 block (16x16 px) and a PSMCT32 block (8x8 px) at the same
// block number are the same 256 bytes, and so are their columns; PSMT8H/PSMT4HL/PSMT4HH live in the top byte /
// nibbles of PSMCT32 words; PSMZ* use the colour tables with the block number XOR 24 (so a Z buffer and a frame
// buffer at the same BP do not collide block-for-block). This is how CLUTs and 8-bit textures uploaded as 32-bit
// data work.
#pragma once

#include "p3fes/gs/gs_types.h"

#include <array>
#include <cstring>
#include <memory>

namespace p3fes::gs {

class GsMemory {
public:
    GsMemory();
    GsMemory(const GsMemory&) = delete;
    GsMemory& operator=(const GsMemory&) = delete;

    u8* data() noexcept { return bytes_.get(); }
    const u8* data() const noexcept { return bytes_.get(); }
    void clear() noexcept { std::memset(bytes_.get(), 0, kVramBytes); }

    // Byte address of pixel (x, y) of the buffer {bp, bw} in a 32-bit-word format (CT32/CT24/T8H/T4HL/T4HH use
    // `z = false`, Z32/Z24 `z = true`). x, y are taken modulo 2048 like the GS's 11-bit coordinates.
    static u32 addr32(u32 bp, u32 bw, u32 x, u32 y, bool z = false) noexcept;
    // Byte address of a 16-bit pixel: `layout` 0 = CT16, 1 = CT16S, 2 = Z16, 3 = Z16S.
    static u32 addr16(u32 bp, u32 bw, u32 x, u32 y, unsigned layout) noexcept;
    static u32 addr8(u32 bp, u32 bw, u32 x, u32 y) noexcept;
    // Nibble address (byte address * 2 + 1 for the high nibble) of a PSMT4 pixel.
    static u32 addr4(u32 bp, u32 bw, u32 x, u32 y) noexcept;

    // Raw pixel value in the format's own width (CT24/Z24: 24 bits, T8H: 8, T4*: 4, 16-bit formats: 16). Undefined
    // PSM values are treated as CT32.
    u32 read(u32 psm, u32 bp, u32 bw, u32 x, u32 y) const noexcept;
    // Write the low `psm_bits` bits of `value`; CT24/Z24/T8H/T4HL/T4HH preserve the rest of the 32-bit word.
    void write(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 value) noexcept;

    u32 read_u32(u32 byte_addr) const noexcept {
        u32 v;
        std::memcpy(&v, bytes_.get() + (byte_addr & kVramMask & ~3u), 4);
        return v;
    }
    void write_u32(u32 byte_addr, u32 v) noexcept { std::memcpy(bytes_.get() + (byte_addr & kVramMask & ~3u), &v, 4); }

private:
    std::unique_ptr<u8[]> bytes_;
};

// The in-page tables, exposed for tests (byte offsets inside one 8 KiB page; nibble offsets for PSMT4).
struct SwizzleTables {
    std::array<std::array<u16, 64>, 32> ct32;   // [y][x], 64x32 page
    std::array<std::array<u16, 64>, 32> z32;
    std::array<std::array<u16, 64>, 64> ct16;   // [y][x], 64x64 page
    std::array<std::array<u16, 64>, 64> ct16s;
    std::array<std::array<u16, 64>, 64> z16;
    std::array<std::array<u16, 64>, 64> z16s;
    std::array<std::array<u16, 128>, 64> t8;    // [y][x], 128x64 page
    std::array<std::array<u16, 128>, 128> t4;   // [y][x], 128x128 page, nibble offsets
};
const SwizzleTables& swizzle_tables() noexcept;

} // namespace p3fes::gs
