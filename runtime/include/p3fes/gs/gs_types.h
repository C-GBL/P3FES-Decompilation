// Graphics Synthesizer constants shared by the GS core, GIF, VIF1 and the CRTC output (Phase 3, runtime/gs/README.md).
//
// Every value here is a definition from the GS User's Manual (pixel storage formats, general-purpose register
// addresses, privileged register offsets); the game-side usage census is docs/ANALYSIS/14 §4 and
// docs/RUNTIME_CONTRACT.md §5.4.
#pragma once

#include "p3fes/ee_types.h"

#include <cstddef>
#include <vector>

namespace p3fes::gs {

inline constexpr u32 kVramBytes = 4u * 1024u * 1024u; // GS local memory
inline constexpr u32 kVramMask = kVramBytes - 1u;
inline constexpr u32 kBlockBytes = 256u;              // BP / TBP / CBP unit (64 words)
inline constexpr u32 kPageBytes = 8192u;              // FBP / ZBP unit (2048 words = 32 blocks)
inline constexpr u32 kBlocksPerPage = 32u;

// Pixel storage modes (6-bit PSM field of TEX0 / FRAME / BITBLTBUF; ZBUF stores the low nibble).
enum class Psm : u8 {
    CT32 = 0x00,
    CT24 = 0x01,
    CT16 = 0x02,
    CT16S = 0x0A,
    T8 = 0x13,
    T4 = 0x14,
    T8H = 0x1B,
    T4HL = 0x24,
    T4HH = 0x2C,
    Z32 = 0x30,
    Z24 = 0x31,
    Z16 = 0x32,
    Z16S = 0x3A,
};

inline constexpr u32 psm_u32(Psm p) noexcept { return static_cast<u32>(p); }

// True for the 13 formats above; every other 6-bit value is undefined (the core treats it as CT32 and counts it).
bool psm_valid(u32 psm) noexcept;
// Bits per pixel as stored in local memory (24 for CT24/Z24: one 32-bit word whose top byte is untouched).
u32 psm_bits(u32 psm) noexcept;
// Bits per pixel in host <-> local image transfers (24-bit formats are packed 3 bytes per pixel).
u32 psm_transfer_bits(u32 psm) noexcept;
const char* psm_name(u32 psm) noexcept;

// General-purpose registers (A+D address byte / REGLIST descriptor space; GS User's Manual §7).
namespace reg {
inline constexpr u8 PRIM = 0x00, RGBAQ = 0x01, ST = 0x02, UV = 0x03, XYZF2 = 0x04, XYZ2 = 0x05, TEX0_1 = 0x06,
                    TEX0_2 = 0x07, CLAMP_1 = 0x08, CLAMP_2 = 0x09, FOG = 0x0A, XYZF3 = 0x0C, XYZ3 = 0x0D,
                    TEX1_1 = 0x14, TEX1_2 = 0x15, TEX2_1 = 0x16, TEX2_2 = 0x17, XYOFFSET_1 = 0x18,
                    XYOFFSET_2 = 0x19, PRMODECONT = 0x1A, PRMODE = 0x1B, TEXCLUT = 0x1C, SCANMSK = 0x22,
                    MIPTBP1_1 = 0x34, MIPTBP1_2 = 0x35, MIPTBP2_1 = 0x36, MIPTBP2_2 = 0x37, TEXA = 0x3B,
                    FOGCOL = 0x3D, TEXFLUSH = 0x3F, SCISSOR_1 = 0x40, SCISSOR_2 = 0x41, ALPHA_1 = 0x42,
                    ALPHA_2 = 0x43, DIMX = 0x44, DTHE = 0x45, COLCLAMP = 0x46, TEST_1 = 0x47, TEST_2 = 0x48,
                    PABE = 0x49, FBA_1 = 0x4A, FBA_2 = 0x4B, FRAME_1 = 0x4C, FRAME_2 = 0x4D, ZBUF_1 = 0x4E,
                    ZBUF_2 = 0x4F, BITBLTBUF = 0x50, TRXPOS = 0x51, TRXREG = 0x52, TRXDIR = 0x53, HWREG = 0x54,
                    SIGNAL = 0x60, FINISH = 0x61, LABEL = 0x62, NOP = 0x7F;
// PACKED-mode register descriptors that are not plain register ids.
inline constexpr u8 PACKED_AD = 0x0E, PACKED_NOP = 0x0F;
} // namespace reg

// Privileged registers: offsets from 0x12000000 (64-bit; GS User's Manual §8).
namespace priv {
inline constexpr u32 PMODE = 0x0000, SMODE1 = 0x0010, SMODE2 = 0x0020, SRFSH = 0x0030, SYNCH1 = 0x0040,
                     SYNCH2 = 0x0050, SYNCV = 0x0060, DISPFB1 = 0x0070, DISPLAY1 = 0x0080, DISPFB2 = 0x0090,
                     DISPLAY2 = 0x00A0, EXTBUF = 0x00B0, EXTDATA = 0x00C0, EXTWRITE = 0x00D0, BGCOLOR = 0x00E0,
                     CSR = 0x1000, IMR = 0x1010, BUSDIR = 0x1040, SIGLBLID = 0x1080;
} // namespace priv

// Bit-field helper: `bits(v, lo, n)` = n bits of v starting at bit lo.
inline constexpr u32 bits(u64 v, unsigned lo, unsigned n) noexcept {
    return static_cast<u32>((v >> lo) & ((n >= 64 ? ~0ull : (1ull << n) - 1ull)));
}

// One composed CRTC frame (or any RGBA image): row-major, 0xAABBGGRR per pixel (R in the low byte).
struct Frame {
    u32 width = 0;
    u32 height = 0;
    std::vector<u32> rgba;

    bool empty() const noexcept { return width == 0 || height == 0; }
    u32 at(u32 x, u32 y) const noexcept { return rgba[static_cast<std::size_t>(y) * width + x]; }
};

inline constexpr u32 rgba(u32 r, u32 g, u32 b, u32 a = 0xFF) noexcept {
    return (r & 0xFFu) | ((g & 0xFFu) << 8) | ((b & 0xFFu) << 16) | ((a & 0xFFu) << 24);
}

} // namespace p3fes::gs
