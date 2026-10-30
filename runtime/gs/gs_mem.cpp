// GS local memory addressing. Block and column tables are the GS User's Manual's page/block/column layouts; the
// PSMT8/PSMT4 column formula follows the arrangement in ps2-web-recomp @ c0f476e runtime/src/gs/gs.cpp
// (build_tables, MIT) and is checked in tests/gs against the manual's literal column tables.
#include "p3fes/gs/gs_mem.h"

namespace p3fes::gs {

namespace {

// Block order inside a page (GS User's Manual). 32-bit formats and PSMT8 share one table (8 x 4 blocks), 16-bit
// formats and PSMT4 the other (4 x 8 blocks). Z formats use the colour table with the block number XOR 24.
constexpr u8 kBlock32[4][8] = {
    {0, 1, 4, 5, 16, 17, 20, 21},
    {2, 3, 6, 7, 18, 19, 22, 23},
    {8, 9, 12, 13, 24, 25, 28, 29},
    {10, 11, 14, 15, 26, 27, 30, 31},
};
constexpr u8 kBlock16[8][4] = {
    {0, 2, 8, 10}, {1, 3, 9, 11}, {4, 6, 12, 14}, {5, 7, 13, 15},
    {16, 18, 24, 26}, {17, 19, 25, 27}, {20, 22, 28, 30}, {21, 23, 29, 31},
};
constexpr u8 kBlock16S[8][4] = {
    {0, 2, 16, 18}, {1, 3, 17, 19}, {8, 10, 24, 26}, {9, 11, 25, 27},
    {4, 6, 20, 22}, {5, 7, 21, 23}, {12, 14, 28, 30}, {13, 15, 29, 31},
};
constexpr u32 kZBlockXor = 24u;

// Word order inside one 32-bit column (8 x 2 pixels, 16 words), and the swapped order PSMT8/PSMT4 use on alternate
// half-columns.
constexpr u8 kColumnWord[2][2][8] = {
    {{0, 1, 4, 5, 8, 9, 12, 13}, {2, 3, 6, 7, 10, 11, 14, 15}},
    {{8, 9, 12, 13, 0, 1, 4, 5}, {10, 11, 14, 15, 2, 3, 6, 7}},
};
// Halfword order inside one 16-bit column (16 x 2 pixels, 32 halfwords).
constexpr u8 kColumn16[2][16] = {
    {0, 2, 8, 10, 16, 18, 24, 26, 1, 3, 9, 11, 17, 19, 25, 27},
    {4, 6, 12, 14, 20, 22, 28, 30, 5, 7, 13, 15, 21, 23, 29, 31},
};

SwizzleTables build() {
    SwizzleTables t{};
    for (u32 y = 0; y < 32; ++y) {
        for (u32 x = 0; x < 64; ++x) {
            const u32 block = kBlock32[y >> 3][x >> 3];
            const u32 inner = ((y >> 1) & 3u) * 64u + kColumnWord[0][y & 1u][x & 7u] * 4u;
            t.ct32[y][x] = static_cast<u16>(block * 256u + inner);
            t.z32[y][x] = static_cast<u16>((block ^ kZBlockXor) * 256u + inner);
        }
    }
    for (u32 y = 0; y < 64; ++y) {
        for (u32 x = 0; x < 64; ++x) {
            const u32 inner = ((y >> 1) & 3u) * 64u + kColumn16[y & 1u][x & 15u] * 2u;
            const u32 b16 = kBlock16[y >> 3][x >> 4];
            const u32 b16s = kBlock16S[y >> 3][x >> 4];
            t.ct16[y][x] = static_cast<u16>(b16 * 256u + inner);
            t.ct16s[y][x] = static_cast<u16>(b16s * 256u + inner);
            t.z16[y][x] = static_cast<u16>((b16 ^ kZBlockXor) * 256u + inner);
            t.z16s[y][x] = static_cast<u16>((b16s ^ kZBlockXor) * 256u + inner);
        }
    }
    for (u32 y = 0; y < 64; ++y) {
        for (u32 x = 0; x < 128; ++x) {
            const u32 block = kBlock32[y >> 4][x >> 4];
            const u32 column = (y >> 2) & 3u;
            const u32 cx = x & 15u, cy = y & 3u;
            const u32 table = ((cy >> 1) & 1u) ^ (column & 1u);
            const u32 word = kColumnWord[table][cy & 1u][cx & 7u];
            const u32 byte = ((cx >> 3) & 1u) * 2u + ((cy >> 1) & 1u);
            t.t8[y][x] = static_cast<u16>(block * 256u + column * 64u + word * 4u + byte);
        }
    }
    for (u32 y = 0; y < 128; ++y) {
        for (u32 x = 0; x < 128; ++x) {
            const u32 block = kBlock16[y >> 4][x >> 5];
            const u32 column = (y >> 2) & 3u;
            const u32 cx = x & 31u, cy = y & 3u;
            const u32 table = ((cy >> 1) & 1u) ^ (column & 1u);
            const u32 word = kColumnWord[table][cy & 1u][cx & 7u];
            const u32 nibble = ((cx >> 3) & 3u) * 2u + ((cy >> 1) & 1u);
            t.t4[y][x] = static_cast<u16>((block * 256u + column * 64u + word * 4u) * 2u + nibble);
        }
    }
    return t;
}

const SwizzleTables kTables = build();

inline u32 page_base(u32 bp, u32 page) noexcept { return (bp + page * kBlocksPerPage) * kBlockBytes; }

} // namespace

const SwizzleTables& swizzle_tables() noexcept { return kTables; }

bool psm_valid(u32 psm) noexcept {
    switch (psm) {
    case 0x00: case 0x01: case 0x02: case 0x0A: case 0x13: case 0x14: case 0x1B: case 0x24: case 0x2C:
    case 0x30: case 0x31: case 0x32: case 0x3A:
        return true;
    default:
        return false;
    }
}

u32 psm_bits(u32 psm) noexcept {
    switch (psm) {
    case 0x01: case 0x31: return 24;
    case 0x02: case 0x0A: case 0x32: case 0x3A: return 16;
    case 0x13: case 0x1B: return 8;
    case 0x14: case 0x24: case 0x2C: return 4;
    default: return 32;
    }
}

u32 psm_transfer_bits(u32 psm) noexcept { return psm_bits(psm); }

const char* psm_name(u32 psm) noexcept {
    switch (psm) {
    case 0x00: return "PSMCT32";
    case 0x01: return "PSMCT24";
    case 0x02: return "PSMCT16";
    case 0x0A: return "PSMCT16S";
    case 0x13: return "PSMT8";
    case 0x14: return "PSMT4";
    case 0x1B: return "PSMT8H";
    case 0x24: return "PSMT4HL";
    case 0x2C: return "PSMT4HH";
    case 0x30: return "PSMZ32";
    case 0x31: return "PSMZ24";
    case 0x32: return "PSMZ16";
    case 0x3A: return "PSMZ16S";
    default: return "PSM?";
    }
}

GsMemory::GsMemory() : bytes_(new u8[kVramBytes]) { clear(); }

u32 GsMemory::addr32(u32 bp, u32 bw, u32 x, u32 y, bool z) noexcept {
    x &= 2047u;
    y &= 2047u;
    const u32 page = (y >> 5) * bw + (x >> 6);
    const u32 off = z ? kTables.z32[y & 31u][x & 63u] : kTables.ct32[y & 31u][x & 63u];
    return (page_base(bp, page) + off) & kVramMask;
}

u32 GsMemory::addr16(u32 bp, u32 bw, u32 x, u32 y, unsigned layout) noexcept {
    x &= 2047u;
    y &= 2047u;
    const u32 page = (y >> 6) * bw + (x >> 6);
    u32 off;
    switch (layout) {
    case 1: off = kTables.ct16s[y & 63u][x & 63u]; break;
    case 2: off = kTables.z16[y & 63u][x & 63u]; break;
    case 3: off = kTables.z16s[y & 63u][x & 63u]; break;
    default: off = kTables.ct16[y & 63u][x & 63u]; break;
    }
    return (page_base(bp, page) + off) & kVramMask;
}

u32 GsMemory::addr8(u32 bp, u32 bw, u32 x, u32 y) noexcept {
    x &= 2047u;
    y &= 2047u;
    const u32 page = (y >> 6) * (bw >> 1) + (x >> 7);
    return (page_base(bp, page) + kTables.t8[y & 63u][x & 127u]) & kVramMask;
}

u32 GsMemory::addr4(u32 bp, u32 bw, u32 x, u32 y) noexcept {
    x &= 2047u;
    y &= 2047u;
    const u32 page = (y >> 7) * (bw >> 1) + (x >> 7);
    return (page_base(bp, page) * 2u + kTables.t4[y & 127u][x & 127u]) & (kVramBytes * 2u - 1u);
}

u32 GsMemory::read(u32 psm, u32 bp, u32 bw, u32 x, u32 y) const noexcept {
    const u8* m = bytes_.get();
    u16 h;
    switch (psm) {
    case 0x01: return read_u32(addr32(bp, bw, x, y)) & 0xFFFFFFu;
    case 0x30: return read_u32(addr32(bp, bw, x, y, true));
    case 0x31: return read_u32(addr32(bp, bw, x, y, true)) & 0xFFFFFFu;
    case 0x02: std::memcpy(&h, m + addr16(bp, bw, x, y, 0), 2); return h;
    case 0x0A: std::memcpy(&h, m + addr16(bp, bw, x, y, 1), 2); return h;
    case 0x32: std::memcpy(&h, m + addr16(bp, bw, x, y, 2), 2); return h;
    case 0x3A: std::memcpy(&h, m + addr16(bp, bw, x, y, 3), 2); return h;
    case 0x13: return m[addr8(bp, bw, x, y)];
    case 0x14: {
        const u32 n = addr4(bp, bw, x, y);
        return (m[n >> 1] >> ((n & 1u) * 4u)) & 0xFu;
    }
    case 0x1B: return read_u32(addr32(bp, bw, x, y)) >> 24;
    case 0x24: return (read_u32(addr32(bp, bw, x, y)) >> 24) & 0xFu;
    case 0x2C: return read_u32(addr32(bp, bw, x, y)) >> 28;
    default: return read_u32(addr32(bp, bw, x, y));
    }
}

void GsMemory::write(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 value) noexcept {
    u8* m = bytes_.get();
    const auto put16 = [m](u32 a, u32 v) {
        const u16 h = static_cast<u16>(v);
        std::memcpy(m + a, &h, 2);
    };
    const auto merge32 = [this](u32 a, u32 keep_mask, u32 v) { write_u32(a, (read_u32(a) & keep_mask) | (v & ~keep_mask)); };
    switch (psm) {
    case 0x01: merge32(addr32(bp, bw, x, y), 0xFF000000u, value); break;
    case 0x30: write_u32(addr32(bp, bw, x, y, true), value); break;
    case 0x31: merge32(addr32(bp, bw, x, y, true), 0xFF000000u, value); break;
    case 0x02: put16(addr16(bp, bw, x, y, 0), value); break;
    case 0x0A: put16(addr16(bp, bw, x, y, 1), value); break;
    case 0x32: put16(addr16(bp, bw, x, y, 2), value); break;
    case 0x3A: put16(addr16(bp, bw, x, y, 3), value); break;
    case 0x13: m[addr8(bp, bw, x, y)] = static_cast<u8>(value); break;
    case 0x14: {
        const u32 n = addr4(bp, bw, x, y);
        u8& b = m[n >> 1];
        b = (n & 1u) ? static_cast<u8>((b & 0x0Fu) | ((value & 0xFu) << 4)) : static_cast<u8>((b & 0xF0u) | (value & 0xFu));
        break;
    }
    case 0x1B: merge32(addr32(bp, bw, x, y), 0x00FFFFFFu, value << 24); break;
    case 0x24: merge32(addr32(bp, bw, x, y), 0xF0FFFFFFu, (value & 0xFu) << 24); break;
    case 0x2C: merge32(addr32(bp, bw, x, y), 0x0FFFFFFFu, (value & 0xFu) << 28); break;
    default: write_u32(addr32(bp, bw, x, y), value); break;
    }
}

} // namespace p3fes::gs
