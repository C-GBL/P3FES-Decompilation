// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/src/ipu/tables.hpp (MIT), whose VLC tables were adapted
// from Play! (BSD-2-Clause, Copyright (c) 2006-2026 Jean-Philip Desjardins; notice reproduced verbatim in
// runtime/ipu/NOTICE); adapted for p3fes-port.
//
// The Annex B code tables of ISO/IEC 13818-2 as {code, length, value} data, and the decoders over them. What was
// taken: the table rows (kMbAddressIncrement ... kDctTable1, unchanged: the VDEC value convention `length << 16 |
// value` comes with them). Ours: the MPEG-2 vs MPEG-1 split of B.1 (stuffing only with MP1, der from the game's
// `_sceMpegMbAddressIncrement 0x4FD1F8`), the D-picture table, the EOB entries (B.14 '10', B.15 '0110'), the
// lookup construction with the NeedBits/Invalid distinction for partially available input, and the self-checks
// (tests/ipu/test_vlc.cpp: prefix-free, Kraft sums, hand-derived vectors from the standard's tables).
#include "p3fes/ipu/mpeg2.h"

#include <algorithm>
#include <array>
#include <vector>

namespace p3fes::ipu::mpeg2 {

namespace {

struct VlcRow {
    u16 code;
    u8 length;
    u32 value;  // length << 16 | value (upstream / Play! convention = the IPU's VDEC DATA word)
};

struct DctRow {
    u16 code;
    u8 length;
    u8 run;     // 255 = escape
    s16 level;
};

constexpr u8 kEscapeRun = 255;

// ---- ported rows (unchanged) -----------------------------------------------------------------------------
constexpr VlcRow kMbAddressIncrement[] = {
    {0x1, 1, 0x10001}, {0x3, 3, 0x30002}, {0x2, 3, 0x30003}, {0x3, 4, 0x40004}, {0x2, 4, 0x40005},
    {0x3, 5, 0x50006}, {0x2, 5, 0x50007}, {0x7, 7, 0x70008}, {0x6, 7, 0x70009}, {0xB, 8, 0x8000A},
    {0xA, 8, 0x8000B}, {0x9, 8, 0x8000C}, {0x8, 8, 0x8000D}, {0x7, 8, 0x8000E}, {0x6, 8, 0x8000F},
    {0x17, 10, 0xA0010}, {0x16, 10, 0xA0011}, {0x15, 10, 0xA0012}, {0x14, 10, 0xA0013}, {0x13, 10, 0xA0014},
    {0x12, 10, 0xA0015}, {0x23, 11, 0xB0016}, {0x22, 11, 0xB0017}, {0x21, 11, 0xB0018}, {0x20, 11, 0xB0019},
    {0x1F, 11, 0xB001A}, {0x1E, 11, 0xB001B}, {0x1D, 11, 0xB001C}, {0x1C, 11, 0xB001D}, {0x1B, 11, 0xB001E},
    {0x1A, 11, 0xB001F}, {0x19, 11, 0xB0020}, {0x18, 11, 0xB0021}, {0xF, 11, 0xB0022}, {0x8, 11, 0xB0023},
};

constexpr VlcRow kMbTypeI[] = {
    {0x1, 1, 0x10001}, {0x1, 2, 0x20011},
};

constexpr VlcRow kMbTypeP[] = {
    {0x1, 1, 0x1000A}, {0x1, 2, 0x20002}, {0x1, 3, 0x30008}, {0x3, 5, 0x50001}, {0x2, 5, 0x5001A},
    {0x1, 5, 0x50012}, {0x1, 6, 0x60011},
};

constexpr VlcRow kMbTypeB[] = {
    {0x2, 2, 0x2000C}, {0x3, 2, 0x2000E}, {0x2, 3, 0x30004}, {0x3, 3, 0x30006}, {0x2, 4, 0x40008},
    {0x3, 4, 0x4000A}, {0x3, 5, 0x50001}, {0x2, 5, 0x5001E}, {0x3, 6, 0x6001A}, {0x2, 6, 0x60016},
    {0x1, 6, 0x60011},
};

constexpr VlcRow kMotionCode[] = {
    {0x1, 1, 0x10000}, {0x2, 3, 0x30001}, {0x3, 3, 0x3FFFF}, {0x2, 4, 0x40002}, {0x3, 4, 0x4FFFE},
    {0x2, 5, 0x50003}, {0x3, 5, 0x5FFFD}, {0x6, 7, 0x70004}, {0x7, 7, 0x7FFFC}, {0xA, 8, 0x80005},
    {0xB, 8, 0x8FFFB}, {0x8, 8, 0x80006}, {0x9, 8, 0x8FFFA}, {0x6, 8, 0x80007}, {0x7, 8, 0x8FFF9},
    {0x16, 10, 0xA0008}, {0x17, 10, 0xAFFF8}, {0x14, 10, 0xA0009}, {0x15, 10, 0xAFFF7}, {0x12, 10, 0xA000A},
    {0x13, 10, 0xAFFF6}, {0x22, 11, 0xB000B}, {0x23, 11, 0xBFFF5}, {0x20, 11, 0xB000C}, {0x21, 11, 0xBFFF4},
    {0x1E, 11, 0xB000D}, {0x1F, 11, 0xBFFF3}, {0x1C, 11, 0xB000E}, {0x1D, 11, 0xBFFF2}, {0x1A, 11, 0xB000F},
    {0x1B, 11, 0xBFFF1}, {0x18, 11, 0xB0010}, {0x19, 11, 0xBFFF0},
};

constexpr VlcRow kDmVector[] = {
    {0x0, 1, 0x10000}, {0x2, 2, 0x20001}, {0x3, 2, 0x2FFFF},
};

constexpr VlcRow kDcSizeLuma[] = {
    {0x0, 2, 0x1}, {0x1, 2, 0x2}, {0x4, 3, 0x0}, {0x5, 3, 0x3}, {0x6, 3, 0x4}, {0xE, 4, 0x5}, {0x1E, 5, 0x6},
    {0x3E, 6, 0x7}, {0x7E, 7, 0x8}, {0xFE, 8, 0x9}, {0x1FE, 9, 0xA}, {0x1FF, 9, 0xB},
};

constexpr VlcRow kDcSizeChroma[] = {
    {0x0, 2, 0x0}, {0x1, 2, 0x1}, {0x2, 2, 0x2}, {0x6, 3, 0x3}, {0xE, 4, 0x4}, {0x1E, 5, 0x5}, {0x3E, 6, 0x6},
    {0x7E, 7, 0x7}, {0xFE, 8, 0x8}, {0x1FE, 9, 0x9}, {0x3FE, 10, 0xA}, {0x3FF, 10, 0xB},
};

constexpr VlcRow kCodedBlockPattern[] = {
    {0x7, 3, 0x3C}, {0xD, 4, 0x4}, {0xC, 4, 0x8}, {0xB, 4, 0x10}, {0xA, 4, 0x20}, {0x13, 5, 0xC}, {0x12, 5, 0x30},
    {0x11, 5, 0x14}, {0x10, 5, 0x28}, {0xF, 5, 0x1C}, {0xE, 5, 0x2C}, {0xD, 5, 0x34}, {0xC, 5, 0x38}, {0xB, 5, 0x1},
    {0xA, 5, 0x3D}, {0x9, 5, 0x2}, {0x8, 5, 0x3E}, {0xF, 6, 0x18}, {0xE, 6, 0x24}, {0xD, 6, 0x3}, {0xC, 6, 0x3F},
    {0x17, 7, 0x5}, {0x16, 7, 0x9}, {0x15, 7, 0x11}, {0x14, 7, 0x21}, {0x13, 7, 0x6}, {0x12, 7, 0xA},
    {0x11, 7, 0x12}, {0x10, 7, 0x22}, {0x1F, 8, 0x7}, {0x1E, 8, 0xB}, {0x1D, 8, 0x13}, {0x1C, 8, 0x23},
    {0x1B, 8, 0xD}, {0x1A, 8, 0x31}, {0x19, 8, 0x15}, {0x18, 8, 0x29}, {0x17, 8, 0xE}, {0x16, 8, 0x32},
    {0x15, 8, 0x16}, {0x14, 8, 0x2A}, {0x13, 8, 0xF}, {0x12, 8, 0x33}, {0x11, 8, 0x17}, {0x10, 8, 0x2B},
    {0xF, 8, 0x19}, {0xE, 8, 0x25}, {0xD, 8, 0x1A}, {0xC, 8, 0x26}, {0xB, 8, 0x1D}, {0xA, 8, 0x2D}, {0x9, 8, 0x35},
    {0x8, 8, 0x39}, {0x7, 8, 0x1E}, {0x6, 8, 0x2E}, {0x5, 8, 0x36}, {0x4, 8, 0x3A}, {0x7, 9, 0x1F}, {0x6, 9, 0x2F},
    {0x5, 9, 0x37}, {0x4, 9, 0x3B}, {0x3, 9, 0x1B}, {0x2, 9, 0x27}, {0x1, 9, 0x0},
};

constexpr DctRow kDctTable0[] = {
    {0x3, 2, 0, 1}, {0x3, 3, 1, 1}, {0x4, 4, 0, 2}, {0x5, 4, 2, 1}, {0x5, 5, 0, 3}, {0x7, 5, 3, 1}, {0x6, 5, 4, 1},
    {0x6, 6, 1, 2}, {0x7, 6, 5, 1}, {0x5, 6, 6, 1}, {0x4, 6, 7, 1}, {0x1, 6, 255, 0}, {0x6, 7, 0, 4},
    {0x4, 7, 2, 2}, {0x7, 7, 8, 1}, {0x5, 7, 9, 1}, {0x26, 8, 0, 5}, {0x21, 8, 0, 6}, {0x25, 8, 1, 3},
    {0x24, 8, 3, 2}, {0x27, 8, 10, 1}, {0x23, 8, 11, 1}, {0x22, 8, 12, 1}, {0x20, 8, 13, 1}, {0xA, 10, 0, 7},
    {0xC, 10, 1, 4}, {0xB, 10, 2, 3}, {0xF, 10, 4, 2}, {0x9, 10, 5, 2}, {0xE, 10, 14, 1}, {0xD, 10, 15, 1},
    {0x8, 10, 16, 1}, {0x1D, 12, 0, 8}, {0x18, 12, 0, 9}, {0x13, 12, 0, 10}, {0x10, 12, 0, 11}, {0x1B, 12, 1, 5},
    {0x14, 12, 2, 4}, {0x1C, 12, 3, 3}, {0x12, 12, 4, 3}, {0x1E, 12, 6, 2}, {0x15, 12, 7, 2}, {0x11, 12, 8, 2},
    {0x1F, 12, 17, 1}, {0x1A, 12, 18, 1}, {0x19, 12, 19, 1}, {0x17, 12, 20, 1}, {0x16, 12, 21, 1},
    {0x1A, 13, 0, 12}, {0x19, 13, 0, 13}, {0x18, 13, 0, 14}, {0x17, 13, 0, 15}, {0x16, 13, 1, 6}, {0x15, 13, 1, 7},
    {0x14, 13, 2, 5}, {0x13, 13, 3, 4}, {0x12, 13, 5, 3}, {0x11, 13, 9, 2}, {0x10, 13, 10, 2}, {0x1F, 13, 22, 1},
    {0x1E, 13, 23, 1}, {0x1D, 13, 24, 1}, {0x1C, 13, 25, 1}, {0x1B, 13, 26, 1}, {0x1F, 14, 0, 16},
    {0x1E, 14, 0, 17}, {0x1D, 14, 0, 18}, {0x1C, 14, 0, 19}, {0x1B, 14, 0, 20}, {0x1A, 14, 0, 21},
    {0x19, 14, 0, 22}, {0x18, 14, 0, 23}, {0x17, 14, 0, 24}, {0x16, 14, 0, 25}, {0x15, 14, 0, 26},
    {0x14, 14, 0, 27}, {0x13, 14, 0, 28}, {0x12, 14, 0, 29}, {0x11, 14, 0, 30}, {0x10, 14, 0, 31},
    {0x18, 15, 0, 32}, {0x17, 15, 0, 33}, {0x16, 15, 0, 34}, {0x15, 15, 0, 35}, {0x14, 15, 0, 36},
    {0x13, 15, 0, 37}, {0x12, 15, 0, 38}, {0x11, 15, 0, 39}, {0x10, 15, 0, 40}, {0x1F, 15, 1, 8}, {0x1E, 15, 1, 9},
    {0x1D, 15, 1, 10}, {0x1C, 15, 1, 11}, {0x1B, 15, 1, 12}, {0x1A, 15, 1, 13}, {0x19, 15, 1, 14},
    {0x13, 16, 1, 15}, {0x12, 16, 1, 16}, {0x11, 16, 1, 17}, {0x10, 16, 1, 18}, {0x14, 16, 6, 3}, {0x1A, 16, 11, 2},
    {0x19, 16, 12, 2}, {0x18, 16, 13, 2}, {0x17, 16, 14, 2}, {0x16, 16, 15, 2}, {0x15, 16, 16, 2},
    {0x1F, 16, 27, 1}, {0x1E, 16, 28, 1}, {0x1D, 16, 29, 1}, {0x1C, 16, 30, 1}, {0x1B, 16, 31, 1},
};

constexpr DctRow kDctTable1[] = {
    {0x2, 2, 0, 1}, {0x2, 3, 1, 1}, {0x6, 3, 0, 2}, {0x7, 4, 0, 3}, {0x5, 5, 2, 1}, {0x7, 5, 3, 1}, {0x6, 5, 1, 2},
    {0x1C, 5, 0, 4}, {0x1D, 5, 0, 5}, {0x6, 6, 4, 1}, {0x7, 6, 5, 1}, {0x5, 6, 0, 6}, {0x4, 6, 0, 7},
    {0x1, 6, 255, 0}, {0x79, 7, 1, 3}, {0x7A, 7, 10, 1}, {0x7, 7, 2, 2}, {0x5, 7, 8, 1}, {0x78, 7, 9, 1},
    {0x6, 7, 6, 1}, {0x4, 7, 7, 1}, {0x7B, 7, 0, 8}, {0x7C, 7, 0, 9}, {0x26, 8, 3, 2}, {0x21, 8, 11, 1},
    {0x25, 8, 12, 1}, {0x24, 8, 13, 1}, {0x27, 8, 1, 4}, {0xFC, 8, 2, 3}, {0xFD, 8, 4, 2}, {0xFA, 8, 0, 12},
    {0xFB, 8, 0, 13}, {0xFE, 8, 0, 14}, {0xFF, 8, 0, 15}, {0x23, 8, 0, 10}, {0x22, 8, 0, 11}, {0x20, 8, 1, 5},
    {0x4, 9, 5, 2}, {0x5, 9, 14, 1}, {0x7, 9, 15, 1}, {0xD, 10, 16, 1}, {0xC, 10, 2, 4}, {0x1C, 12, 3, 3},
    {0x12, 12, 4, 3}, {0x1E, 12, 6, 2}, {0x15, 12, 7, 2}, {0x11, 12, 8, 2}, {0x1F, 12, 17, 1}, {0x1A, 12, 18, 1},
    {0x19, 12, 19, 1}, {0x17, 12, 20, 1}, {0x16, 12, 21, 1}, {0x16, 13, 1, 6}, {0x15, 13, 1, 7}, {0x14, 13, 2, 5},
    {0x13, 13, 3, 4}, {0x12, 13, 5, 3}, {0x11, 13, 9, 2}, {0x10, 13, 10, 2}, {0x1F, 13, 22, 1}, {0x1E, 13, 23, 1},
    {0x1D, 13, 24, 1}, {0x1C, 13, 25, 1}, {0x1B, 13, 26, 1}, {0x1F, 14, 0, 16}, {0x1E, 14, 0, 17},
    {0x1D, 14, 0, 18}, {0x1C, 14, 0, 19}, {0x1B, 14, 0, 20}, {0x1A, 14, 0, 21}, {0x19, 14, 0, 22},
    {0x18, 14, 0, 23}, {0x17, 14, 0, 24}, {0x16, 14, 0, 25}, {0x15, 14, 0, 26}, {0x14, 14, 0, 27},
    {0x13, 14, 0, 28}, {0x12, 14, 0, 29}, {0x11, 14, 0, 30}, {0x10, 14, 0, 31}, {0x18, 15, 0, 32},
    {0x17, 15, 0, 33}, {0x16, 15, 0, 34}, {0x15, 15, 0, 35}, {0x14, 15, 0, 36}, {0x13, 15, 0, 37},
    {0x12, 15, 0, 38}, {0x11, 15, 0, 39}, {0x10, 15, 0, 40}, {0x1F, 15, 1, 8}, {0x1E, 15, 1, 9}, {0x1D, 15, 1, 10},
    {0x1C, 15, 1, 11}, {0x1B, 15, 1, 12}, {0x1A, 15, 1, 13}, {0x19, 15, 1, 14}, {0x13, 16, 1, 15},
    {0x12, 16, 1, 16}, {0x11, 16, 1, 17}, {0x10, 16, 1, 18}, {0x14, 16, 6, 3}, {0x1A, 16, 11, 2}, {0x19, 16, 12, 2},
    {0x18, 16, 13, 2}, {0x17, 16, 14, 2}, {0x16, 16, 15, 2}, {0x15, 16, 16, 2}, {0x1F, 16, 27, 1},
    {0x1E, 16, 28, 1}, {0x1D, 16, 29, 1}, {0x1C, 16, 30, 1}, {0x1B, 16, 31, 1},
};
// ---- end of ported rows ------------------------------------------------------------------------------------

// Ours: MPEG-1 D-picture macroblock_type ('1' = intra, ISO 11172-2 Table B.2d) and the end_of_block codes.
constexpr VlcRow kMbTypeD[] = {{0x1, 1, 0x10001}};
constexpr DctRow kEobTable0 = {0x2, 2, 0, 0};   // B.14 '10'
constexpr DctRow kEobTable1 = {0x6, 4, 0, 0};   // B.15 '0110'

// Lookup entry: 0 = no code with this prefix; else length (bits 0-7), value (bits 16-31, two's complement).
// `prefix` marks every proper and complete code prefix as a binary-heap trie (node (1 << L) + p for the L-bit
// prefix p), so that a short input is told apart as NeedBits (a code may still follow) or Invalid (none can).
struct Lut {
    unsigned bits = 0;
    std::vector<u32> e;
    std::vector<u8> prefix;
    void mark(u32 code, unsigned length) {
        if (prefix.empty()) prefix.assign(std::size_t{2} << bits, 0u);
        for (unsigned len = 0; len <= length; ++len) prefix[(std::size_t{1} << len) + (code >> (length - len))] = 1;
    }
};

template <std::size_t N>
Lut build(const VlcRow (&rows)[N], bool skip_stuffing = false) {
    Lut l;
    for (const VlcRow& r : rows) l.bits = std::max<unsigned>(l.bits, r.length);
    l.e.assign(std::size_t{1} << l.bits, 0u);
    for (const VlcRow& r : rows) {
        if (skip_stuffing && (r.value & 0xFFFFu) == static_cast<u32>(kMbaiStuffing)) continue;
        const unsigned shift = l.bits - r.length;
        const u32 entry = r.length | ((r.value & 0xFFFFu) << 16);
        for (u32 i = 0; i < (1u << shift); ++i) l.e[(static_cast<u32>(r.code) << shift) | i] = entry;
        l.mark(r.code, r.length);
    }
    return l;
}

// DCT entry: kind (bits 0-1: 0 none, 1 coef, 2 eob, 3 escape), length (8-15), run (16-23), level (24-31).
Lut build_dct(const DctRow* rows, std::size_t n, const DctRow& eob) {
    Lut l;
    for (std::size_t k = 0; k < n; ++k) l.bits = std::max<unsigned>(l.bits, rows[k].length);
    l.e.assign(std::size_t{1} << l.bits, 0u);
    auto put = [&](const DctRow& r, u32 kind) {
        const unsigned shift = l.bits - r.length;
        const u32 entry = kind | (u32{r.length} << 8) | (kind == 1 ? (u32{r.run} << 16) | (static_cast<u32>(r.level) << 24) : 0u);
        for (u32 i = 0; i < (1u << shift); ++i) l.e[(static_cast<u32>(r.code) << shift) | i] = entry;
        l.mark(r.code, r.length);
    };
    for (std::size_t k = 0; k < n; ++k) put(rows[k], rows[k].run == kEscapeRun ? 3u : 1u);
    put(eob, 2u);
    return l;
}

struct Tables {
    std::array<Lut, static_cast<std::size_t>(Vlc::Count)> vlc;
    Lut dct0, dct1;
    Tables() {
        vlc[static_cast<std::size_t>(Vlc::MbAddrInc)] = build(kMbAddressIncrement, true);
        vlc[static_cast<std::size_t>(Vlc::MbAddrIncMpeg1)] = build(kMbAddressIncrement);
        vlc[static_cast<std::size_t>(Vlc::MbTypeI)] = build(kMbTypeI);
        vlc[static_cast<std::size_t>(Vlc::MbTypeP)] = build(kMbTypeP);
        vlc[static_cast<std::size_t>(Vlc::MbTypeB)] = build(kMbTypeB);
        vlc[static_cast<std::size_t>(Vlc::MbTypeD)] = build(kMbTypeD);
        vlc[static_cast<std::size_t>(Vlc::MotionCode)] = build(kMotionCode);
        vlc[static_cast<std::size_t>(Vlc::DmVector)] = build(kDmVector);
        vlc[static_cast<std::size_t>(Vlc::DcSizeLuma)] = build(kDcSizeLuma);
        vlc[static_cast<std::size_t>(Vlc::DcSizeChroma)] = build(kDcSizeChroma);
        vlc[static_cast<std::size_t>(Vlc::Cbp)] = build(kCodedBlockPattern);
        dct0 = build_dct(kDctTable0, std::size(kDctTable0), kEobTable0);
        dct1 = build_dct(kDctTable1, std::size(kDctTable1), kEobTable1);
    }
};

const Tables& tables() {
    static const Tables t;
    return t;
}

// The lookup index for `bits` bits from an MSB-aligned window.
inline u32 index_of(u32 window, unsigned bits) { return bits ? window >> (32u - bits) : 0u; }

// No code matched the zero-padded window: with fewer than `bits` bits available, wait if the available bits are
// the prefix of some code.
inline Decode short_or_invalid(const Lut& l, u32 window, unsigned avail) {
    if (avail >= l.bits) return Decode::Invalid;
    return l.prefix[(std::size_t{1} << avail) + index_of(window, avail)] ? Decode::NeedBits : Decode::Invalid;
}

} // namespace

unsigned vlc_max_length(Vlc t) { return tables().vlc[static_cast<std::size_t>(t)].bits; }

Decode decode_vlc(Vlc t, u32 window, unsigned avail, unsigned& length, int& value) {
    const Lut& l = tables().vlc[static_cast<std::size_t>(t)];
    const u32 e = l.e[index_of(window, l.bits)];
    const unsigned len = e & 0xFFu;
    if (len == 0) return short_or_invalid(l, window, avail);
    if (len > avail) return Decode::NeedBits;
    length = len;
    value = static_cast<s16>(static_cast<u16>(e >> 16));
    return Decode::Ok;
}

Decode decode_dct(bool table_one, u32 window, unsigned avail, DctCode& out) {
    const Lut& l = table_one ? tables().dct1 : tables().dct0;
    const u32 e = l.e[index_of(window, l.bits)];
    const unsigned kind = e & 3u;
    const unsigned len = (e >> 8) & 0xFFu;
    if (kind == 0) return short_or_invalid(l, window, avail);
    if (len > avail) return Decode::NeedBits;
    out.kind = kind == 1 ? DctCode::Coef : kind == 2 ? DctCode::Eob : DctCode::Escape;
    out.length = static_cast<u8>(len);
    out.run = static_cast<u8>(e >> 16);
    out.level = static_cast<u8>(e >> 24);
    return Decode::Ok;
}

std::vector<VlcCodeInfo> vlc_codes(Vlc t) {
    std::vector<VlcCodeInfo> out;
    auto add = [&](const VlcRow* rows, std::size_t n, bool skip_stuffing) {
        for (std::size_t k = 0; k < n; ++k) {
            if (skip_stuffing && (rows[k].value & 0xFFFFu) == static_cast<u32>(kMbaiStuffing)) continue;
            out.push_back({rows[k].code, rows[k].length, static_cast<s16>(static_cast<u16>(rows[k].value)),
                           rows[k].value >> 16});
        }
    };
    switch (t) {
    case Vlc::MbAddrInc: add(kMbAddressIncrement, std::size(kMbAddressIncrement), true); break;
    case Vlc::MbAddrIncMpeg1: add(kMbAddressIncrement, std::size(kMbAddressIncrement), false); break;
    case Vlc::MbTypeI: add(kMbTypeI, std::size(kMbTypeI), false); break;
    case Vlc::MbTypeP: add(kMbTypeP, std::size(kMbTypeP), false); break;
    case Vlc::MbTypeB: add(kMbTypeB, std::size(kMbTypeB), false); break;
    case Vlc::MbTypeD: add(kMbTypeD, std::size(kMbTypeD), false); break;
    case Vlc::MotionCode: add(kMotionCode, std::size(kMotionCode), false); break;
    case Vlc::DmVector: add(kDmVector, std::size(kDmVector), false); break;
    case Vlc::DcSizeLuma: add(kDcSizeLuma, std::size(kDcSizeLuma), false); break;
    case Vlc::DcSizeChroma: add(kDcSizeChroma, std::size(kDcSizeChroma), false); break;
    case Vlc::Cbp: add(kCodedBlockPattern, std::size(kCodedBlockPattern), false); break;
    case Vlc::Count: break;
    }
    return out;
}

std::vector<DctCodeInfo> dct_codes(bool table_one) {
    std::vector<DctCodeInfo> out;
    const DctRow* rows = table_one ? kDctTable1 : kDctTable0;
    const std::size_t n = table_one ? std::size(kDctTable1) : std::size(kDctTable0);
    for (std::size_t k = 0; k < n; ++k)
        out.push_back({rows[k].code, rows[k].length, rows[k].run == kEscapeRun ? DctCode::Escape : DctCode::Coef,
                       rows[k].run == kEscapeRun ? u8{0} : rows[k].run, static_cast<u8>(rows[k].level)});
    const DctRow& eob = table_one ? kEobTable1 : kEobTable0;
    out.push_back({eob.code, eob.length, DctCode::Eob, 0, 0});
    return out;
}

} // namespace p3fes::ipu::mpeg2
