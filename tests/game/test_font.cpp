// Phase 5 pair tests for the font renderer leaves (game/src/ui/font.cpp): each hand-written function and
// the recompiled body it replaces run on identical guest machines (pair_harness.h: result, callee-saved
// registers, virtual cycles, check-point count, the arena; here also the font globals at 0x7CD4E0 /
// 0x7CE630 / 0x95ABE0, the flag words, guest address 0 for the NULL paths and the stack frame of
// frFontProcessTag). Real game data: every glyph of DATA/FONT/FONT0-3.FNT (beside the ELF) through both Huffman
// decoders, byte-compared with each other and with a host decoder written from the format description
// (docs/ANALYSIS/20_menu_ui.md section 5.3); FONT0's width table drives the metrics. Random inputs: text
// codes (ASCII, two-byte 80 80 .. 83 FF and beyond), line chains, slot lists, ring buffers, tag strings
// with every handler index of sFrTagTable.
#include "pair_harness.h"

#include "p3fes/game/font.h"
#include "p3fes/game/ui.h"

#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_fmGslGetGlyphBlocks_003b4770)
P3FES_DECL_PAIR(fn_fmGslDecodeGlyph_003b47b0)
P3FES_DECL_PAIR(fn_fmGslAllocEntry_003b4520)
P3FES_DECL_PAIR(fn_fmGslReleaseEntry_003b4580)
P3FES_DECL_PAIR(fn_rbAlloc_003b46b0)
P3FES_DECL_PAIR(fn_rbFree_003b46f0)
P3FES_DECL_PAIR(fn_frFontSetGlyphMetrics_003b01d0)
P3FES_DECL_PAIR(fn_frFontInitLineNode_003b05c0)
P3FES_DECL_PAIR(fn_frFontCreateGlyphNode_003b0620)
P3FES_DECL_PAIR(fn_frFontKerningAdjust_003b0840)
P3FES_DECL_PAIR(fn_frFontLineSetAlpha_003b0bb0)
P3FES_DECL_PAIR(fn_frFontNodeSetCode_003b0c20)
P3FES_DECL_PAIR(fn_frFontLineResetAlpha_003b0c70)
P3FES_DECL_PAIR(fn_frFontLineSetStyle_003b0ce0)
P3FES_DECL_PAIR(fn_frFontLineSetPos_003b0d70)
P3FES_DECL_PAIR(fn_frFontLineSetColourSet_003b0dd0)
P3FES_DECL_PAIR(fn_frFontLineSetRgba_003b0e20)
P3FES_DECL_PAIR(fn_frFontSetDefaultGlyphFlags_003b0e70)
P3FES_DECL_PAIR(fn_frFontClearDefaultGlyphFlags_003b0e90)
P3FES_DECL_PAIR(fn_frFontLineFadeStep_003b0ec0)
P3FES_DECL_PAIR(fn_frFontLineChainJoin_003b1920)
P3FES_DECL_PAIR(fn_frFontLineGetWidth_003b19d0)
P3FES_DECL_PAIR(fn_frFontGetStyleGlyphWidth_003b1a10)
P3FES_DECL_PAIR(fn_frFontGetStyleGlyphHeight_003b1a40)
P3FES_DECL_PAIR(fn_frFontResetLineSpacing_003b1a70)
P3FES_DECL_PAIR(fn_frFontSetLineSpacing_003b1a80)
P3FES_DECL_PAIR(fn_frFontChainCountLines_003b1a90)
P3FES_DECL_PAIR(fn_frFontChainGetRowWidth_003b1b00)
P3FES_DECL_PAIR(fn_frFontChainGetRowPos_003b1bc0)
P3FES_DECL_PAIR(fn_frFontChainMoveTo_003b1c40)
P3FES_DECL_PAIR(fn_frFontChainCentreAt_003b1c90)
P3FES_DECL_PAIR(fn_frFontLayoutNewRow_003b2400)
P3FES_DECL_PAIR(fn_frFontTestTagFlags_003b2a00)
P3FES_DECL_PAIR(fn_frFontSetTagSlot_003b2a10)
P3FES_DECL_PAIR(fn_frFontProcessTagEx_003b2a30)
P3FES_DECL_PAIR(fn_frFontProcessTag_003b2bf0)
P3FES_DECL_PAIR(fn_frFontTagGetParam0_003af360)
P3FES_DECL_PAIR(fn_frFontTagGetParam1_003af370)
P3FES_DECL_PAIR(fn_frFontTagGetParam2_003af380)
P3FES_DECL_PAIR(fn_frFontTagGetParam3_003af390)
P3FES_DECL_PAIR(fn_frFontTagSetParams01_003af3a0)
P3FES_DECL_PAIR(fn_frFontTagSetParams23_003af460)
P3FES_DECL_PAIR(fn_frFontTagWait_003af5a0)
P3FES_DECL_PAIR(fn_frFontTagWaitIfFlag389_003af660)
P3FES_DECL_PAIR(fn_frFontGetStyleSize_003b35c0)
P3FES_DECL_PAIR(fn_frFontRasterAgeSlots_003b3770)
P3FES_DECL_PAIR(fn_frFontRasterFind_003b3dd0)
P3FES_DECL_PAIR(fn_frFontRasterLookup_003b3e00)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game::font;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

constexpr u32 kFntVa = 0x01900000u;   // a .FNT image (read only; outside the arena)
constexpr u32 kSynthVa = 0x01940000u; // a synthetic .FNT with a random width table
constexpr u32 kFlagWord389 = 0x83A21Cu + 4u * (389u / 32u);

u32 rd32(const std::vector<u8>& f, u32 off) {
    u32 v;
    std::memcpy(&v, f.data() + off, 4);
    return v;
}
u16 rd16(const std::vector<u8>& f, u32 off) {
    u16 v;
    std::memcpy(&v, f.data() + off, 2);
    return v;
}
u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 load16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }

std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}
std::filesystem::path font_dir() { return std::filesystem::path(elf_path()).parent_path().parent_path() / "DATA" / "FONT"; }

// --- a pair run that also compares the font globals (and restores every compared region between runs) ---
struct Region {
    u32 va;
    u32 len;
};
const Region kCompared[] = {
    {kArena, kArenaSize}, {0, 0x80}, {0x7CD4E0u, 0x40}, {0x7CE630u, 0x40}, {0x95ABE0u, 0x2F0}, {0x83A21Cu, 0x2C0},
};

Pair pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    std::vector<std::vector<u8>> before, after_hand;
    for (const Region& r : kCompared) before.push_back(m.bytes(r.va, r.len));
    Pair p;
    p.hand = run(m, hand, args, seed);
    std::size_t i = 0;
    for (const Region& r : kCompared) {
        after_hand.push_back(m.bytes(r.va, r.len));
        std::memcpy(m.at(r.va), before[i++].data(), r.len);
    }
    p.recomp = run(m, recomp, args, seed);
    expect_same(p.hand, p.recomp, what);
    i = 0;
    for (const Region& r : kCompared) {
        INFO(what << ": region " << std::hex << r.va);
        CHECK(m.bytes(r.va, r.len) == after_hand[i++]);
    }
    return p;
}

// --- the .FNT layout as frAddFontStyle resolves it (docs/ANALYSIS/20_menu_ui.md section 5.3) -----------
struct FntLayout {
    u32 count = 0, size1 = 0, widths = 0, block2 = 0, slots = 0, huffman = 0;  // offsets into the file
};
FntLayout layout_of(const std::vector<u8>& f) {
    FntLayout l;
    l.count = rd16(f, kFntGlyphCount);
    u32 off = rd32(f, 0) + (static_cast<u32>(f[0x0A]) << 6);
    if (f[kFntHasWidths] != 0) {
        l.size1 = rd32(f, off);
        l.widths = off + 4;
        const u32 o2 = off + 4 + l.size1;
        l.block2 = o2 + 4;
        off = o2 + 4 + rd32(f, o2);
    }
    l.slots = off;
    l.huffman = off + l.count * 4;
    return l;
}
// The style record frAddFontStyle writes for a file at `va`.
void put_style(Machine& m, u32 style, u32 va, const std::vector<u8>& f) {
    const FntLayout l = layout_of(f);
    const u32 rec = kStyles + style * kStyleStride;
    store32(m, rec + 0, 0);
    store32(m, rec + kStyleFnt, va);
    store32(m, rec + kStyleWidthBytes, l.size1);
    store32(m, rec + 0x0C, f[kFntHasWidths] ? rd32(f, l.block2 - 4) : 0);
    store32(m, rec + kStyleWidthTable, f[kFntHasWidths] ? va + l.widths : 0);
    store32(m, rec + 0x14, f[kFntHasWidths] ? va + l.block2 : 0);
    store32(m, rec + 0x18, va + l.slots);
    store32(m, rec + kStyleHuffman, va + l.huffman);
}
std::vector<u8> synthetic_fnt(std::mt19937& rng, u32 count) {
    std::vector<u8> f(0x20 + 0x40 + 4 + 2 * count + 4 + 4 * count, 0);
    const u32 hdr = 0x20;
    std::memcpy(f.data(), &hdr, 4);
    f[8] = f[9] = f[10] = 1;
    const u16 c = static_cast<u16>(count), w = 32, h = 32, bpg = 0x200;
    std::memcpy(f.data() + 0x0E, &c, 2);
    std::memcpy(f.data() + 0x10, &w, 2);
    std::memcpy(f.data() + 0x12, &h, 2);
    std::memcpy(f.data() + 0x14, &bpg, 2);
    f[0x16] = 1;
    const u32 size1 = 2 * count;
    std::memcpy(f.data() + 0x60, &size1, 4);
    for (u32 i = 0; i < count; ++i) {
        const int left = static_cast<int>(rng() % 12) - 2, right = rng() % 8 == 0 ? 0 : static_cast<int>(rng() % 30) - 1;
        f[0x64 + 2 * i] = static_cast<u8>(left);
        f[0x64 + 2 * i + 1] = static_cast<u8>(right);
    }
    return f;
}

// Host Huffman decoder written from the format description: bit i of the glyph's range is bit (i & 15)
// of stream word i >> 4; node 0 is the root, a node is a leaf when its first child is 0 and its symbol
// is the byte at +4.
std::vector<u8> host_decode(const std::vector<u8>& f, const FntLayout& l, u32 glyph) {
    const u32 blk = l.huffman;
    const u32 dict = blk + rd32(f, blk + 0);
    const u32 offsets = dict + rd32(f, blk + 4);
    const u32 stream = offsets + rd32(f, blk + 24);
    const u32 a = rd32(f, offsets + 4 * glyph), b = rd32(f, offsets + 4 * glyph + 4);
    std::vector<u8> out;
    u32 node = 0;
    for (u32 bit = a; bit < b; ++bit) {
        const u32 v = (rd16(f, stream + 2 * (bit >> 4)) >> (bit & 15)) & 1u;
        const u32 child = rd16(f, dict + node * 6 + 2 + 2 * v);
        if (rd16(f, dict + child * 6 + 2) == 0) {
            out.push_back(f[dict + child * 6 + 4]);
            node = 0;
        } else {
            node = child;
        }
    }
    return out;
}

// The documented glyph index of a text code (20_menu_ui.md section 0 / 5.2).
u32 host_glyph_index(u32 code, u32 count) {
    u32 g;
    if (code < 0x80) {
        g = code == 0x20 ? kGlyphSpace : code - 0x20;
    } else {
        const u32 k = code - 0x8080u;
        g = ((k & 0xFF00u) >> 1) + (k & 0x7Fu);
    }
    return static_cast<s32>(g) < static_cast<s32>(count) ? g : kGlyphReplacement;
}

// --- line chains in the arena --------------------------------------------------------------------------
constexpr u32 kLines = kArena + 0x000;   // 10 line nodes of 0x44
constexpr u32 kGlyphs = kArena + 0x300;  // 96 glyph nodes of 0x2C (to 0x1380)
constexpr u32 kOut = kArena + 0x1F00;
constexpr u32 kLineSize = 0x44, kGlyphSize = 0x2C;

struct Chain {
    std::vector<u32> lines;
    std::vector<std::vector<u32>> glyphs;
};
Chain build_chain(Machine& m, std::mt19937& rng, u32 first_line, u32 nlines, u32 first_glyph) {
    Chain c;
    s32 y = static_cast<s32>(rng() % 400) - 100;
    u32 g = first_glyph;
    for (u32 i = 0; i < nlines; ++i) {
        const u32 l = kLines + (first_line + i) * kLineSize;
        fill_random(m, l, kLineSize, rng);
        c.lines.push_back(l);
        m.at(l + 3)[0] = static_cast<u8>(static_cast<s8>(static_cast<int>(rng() % 9) - 3));
        store32(m, l + 4, static_cast<u32>(static_cast<s32>(rng() % 9000) - 2000));
        store32(m, l + 8, static_cast<u32>(y));
        y += rng() % 2 ? static_cast<s32>(rng() % 60) : static_cast<s32>(100 + rng() % 200);
        store32(m, l + 12, rng() % 40);
        const u32 ng = rng() % 7;
        std::vector<u32> gs;
        for (u32 k = 0; k < ng; ++k) {
            const u32 gv = kGlyphs + (g++ % 96) * kGlyphSize;
            fill_random(m, gv, kGlyphSize, rng);
            store32(m, gv + 12, rng() % 4 ? rng() % 700 : static_cast<u32>(-static_cast<s32>(rng() % 50)));
            m.at(gv + 22)[0] = static_cast<u8>(rng() % 3);
            if (rng() % 4 == 0) store32(m, gv + 16, load32(m, gv + 16) & 0xFFFFFF00u);
            if (rng() % 4 == 0) store32(m, gv + 16, (load32(m, gv + 16) & 0xFFFFFF00u) | (rng() % 8));
            gs.push_back(gv);
        }
        for (std::size_t k = 0; k < gs.size(); ++k) store32(m, gs[k] + 40, k + 1 < gs.size() ? gs[k + 1] : 0);
        store32(m, l + 28, gs.empty() ? 0 : gs[0]);
        c.glyphs.push_back(gs);
    }
    for (u32 i = 0; i < nlines; ++i) {
        const u32 next = i + 1 < nlines ? c.lines[i + 1] : 0;
        store32(m, c.lines[i] + 36, next);
        store32(m, c.lines[i] + 40, next);
        store32(m, c.lines[i] + 44, c.lines[0]);
    }
    return c;
}
s32 host_line_width(const Machine& m, u32 l) {
    u32 sum = 0;
    for (u32 g = load32(m, l + 28); g != 0; g = load32(m, g + 40))
        sum += load32(m, g + 12) + static_cast<u32>(static_cast<s32>(static_cast<s8>(m.mem.main_ram()[l + 3])));
    return static_cast<s32>(sum);
}

}  // namespace

TEST_CASE("game(font): every glyph of FONT0-3.FNT decodes identically through both Huffman decoders and the host decoder") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    int files = 0;
    std::mt19937 rng{0xF0A7u};
    for (const char* name : {"FONT0.FNT", "FONT1.FNT", "FONT2.FNT", "FONT3.FNT"}) {
        const std::vector<u8> f = read_file(font_dir() / name);
        if (f.empty()) {
            MESSAGE("SKIP: " << (font_dir() / name).string() << " not found");
            continue;
        }
        ++files;
        INFO(name);
        std::memset(m.at(kFntVa), 0, 0x40000);
        std::memcpy(m.at(kFntVa), f.data(), f.size());
        const FntLayout l = layout_of(f);
        const u32 bytes_per_glyph = rd16(f, 0x14);
        const u32 regions = kArena + 0x10;
        const u32 dst = kArena + 0x100;
        // the region resolver first
        Pair p = pair(m, PAIR(fn_fmGslGetGlyphBlocks_003b4770), Args{kFntVa + l.huffman, regions}, rng(), "fmGslGetGlyphBlocks(real)");
        CHECK(load32(m, regions + 0) == kFntVa + l.huffman + rd32(f, l.huffman));
        CHECK(load32(m, regions + 4) == kFntVa + l.huffman + rd32(f, l.huffman) + rd32(f, l.huffman + 4));
        u32 total = 0;
        for (u32 g = 0; g < l.count; ++g) {
            fill_random(m, dst, 0x200, rng);
            p = pair(m, PAIR(fn_fmGslDecodeGlyph_003b47b0), Args{dst, g, kFntVa, regions}, rng(), "fmGslDecodeGlyph(real glyph)");
            CHECK(same_frame_bytes(p, 160, 152, 8));  // the two bit offsets memcpy'd into the frame
            const std::vector<u8> want = host_decode(f, l, g);
            CHECK(want.size() == bytes_per_glyph);
            CHECK(p.hand.v0 == want.size());
            CHECK(load32(m, kLastDecodedBytes) == want.size());
            CHECK(m.bytes(dst, static_cast<u32>(want.size())) == want);
            total += static_cast<u32>(want.size());
        }
        CHECK(total == rd32(f, l.huffman + 28));  // the block's "total decoded bytes" word
    }
    if (files == 0) MESSAGE("SKIP: no DATA/FONT/FONT*.FNT beside the ELF");
}

TEST_CASE("game(font): fmGslGetGlyphBlocks on random block headers") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{11u};
    for (int it = 0; it < 500; ++it) {
        fill_random(m, kArena, 0x100, rng);
        const u32 hdr = kArena + 0x20 + (rng() % 8) * 4;  // one rng() per statement: the same draws on every compiler
        const u32 seed = rng();
        pair(m, PAIR(fn_fmGslGetGlyphBlocks_003b4770), Args{hdr, kArena + 0x80}, seed, "fmGslGetGlyphBlocks");
    }
}

TEST_CASE("game(font): frFontSetGlyphMetrics on FONT0's width table and random tables, sizes and scales") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B01D0u};
    const std::vector<u8> real = read_file(font_dir() / "FONT0.FNT");
    if (!real.empty()) {
        std::memcpy(m.at(kFntVa), real.data(), real.size());
        put_style(m, 0, kFntVa, real);
    } else {
        MESSAGE("SKIP (part): FONT0.FNT not found; style 0 uses a synthetic table");
    }
    std::vector<u8> synth = synthetic_fnt(rng, 506);
    std::memcpy(m.at(kSynthVa), synth.data(), synth.size());
    for (u32 s = real.empty() ? 0 : 1; s < 9; ++s) put_style(m, s, kSynthVa, synth);
    m.at(kSynthVa + 0x400)[0] = 0;  // keep a byte for the no-width-table case below
    const u32 node = kArena + 0x40;
    for (int it = 0; it < 6000; ++it) {
        fill_random(m, node, kGlyphSize, rng);
        const u32 style = rng() % 9;
        m.at(node + 21)[0] = static_cast<u8>(style);
        if (rng() % 3) m.at(node + 23)[0] |= 1;
        for (u32 s = 0; s < 9; ++s) m.at(kStyleSizes + s)[0] = static_cast<u8>(pick(rng, {32, 32, 24, 28, 16, 40, 64, 127, 0x80, 0xF0}));
        store32(m, kScaleX, pick(rng, {0, 0, 128, 96, 160, 0xFFFFFF80u, 1, 0x7FFFFFFFu}));
        store32(m, kScaleY, pick(rng, {0, 128, 64, 200, 0xFFFFFFFFu}));
        if (it % 50 == 0) store32(m, kStyles + style * kStyleStride + kStyleFnt, kSynthVa + 0x400 - kFntHasWidths);  // has-widths byte 0
        u32 glyph = pick(rng, {1, 17, 453, 454, 455, 505, 506, 600}) ;
        if (rng() % 2) glyph = rng() % 520;
        if (rng() % 40 == 0) glyph = 0x80000000u | (rng() % 600);  // the pair index overflows the signed compare
        pair(m, PAIR(fn_frFontSetGlyphMetrics_003b01d0), Args{node, glyph}, rng(), "frFontSetGlyphMetrics");
        if (it % 50 == 0) put_style(m, style, style == 0 && !real.empty() ? kFntVa : kSynthVa, style == 0 && !real.empty() ? real : synth);
    }
    if (!real.empty()) {
        // documented rule on FONT0: 'A' (glyph 0x21), proportional, size 32, no scale -> advance = right - left + 2
        const FntLayout l = layout_of(real);
        fill_random(m, node, kGlyphSize, rng);
        m.at(node + 21)[0] = 0;
        m.at(node + 23)[0] = 1;
        m.at(kStyleSizes)[0] = 32;
        store32(m, kScaleX, 0);
        store32(m, kScaleY, 0);
        pair(m, PAIR(fn_frFontSetGlyphMetrics_003b01d0), Args{node, 0x21}, rng(), "metrics of 'A'");
        const s32 left = static_cast<s8>(real[l.widths + 2 * 0x21]), right = static_cast<s8>(real[l.widths + 2 * 0x21 + 1]);
        CHECK(static_cast<s32>(load32(m, node + 12)) == right - left + 2);
        CHECK(static_cast<s32>(load32(m, node + 4)) == -left * 16);
    }
}

TEST_CASE("game(font): frFontCreateGlyphNode maps ASCII and two-byte codes to the documented glyph index") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B0620u};
    const std::vector<u8> real = read_file(font_dir() / "FONT0.FNT");
    std::vector<u8> f = real.empty() ? synthetic_fnt(rng, 506) : real;
    std::memcpy(m.at(kFntVa), f.data(), f.size());
    std::vector<u8> small = synthetic_fnt(rng, 300);  // a style with fewer glyphs: more replacements
    std::memcpy(m.at(kSynthVa), small.data(), small.size());
    for (u32 s = 0; s < 9; ++s) put_style(m, s, s == 7 ? kSynthVa : kFntVa, s == 7 ? small : f);
    const u32 ring = kArena + 0x1F80, records = kArena + 0x800, mgr = kArena + 0x1F00, slots = kArena + 0x000, gs = kArena + 0x200;
    int hits = 0, replaced = 0, two_byte = 0;
    for (int it = 0; it < 4000; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        // ring of 0x34-byte records (the first word non-zero = available)
        const u32 nrec = it % 97 == 0 ? 0 : 1 + rng() % 4;
        for (u32 r = 0; r < nrec; ++r) {
            store32(m, records + r * 0x34, 1 + rng() % 5);
            store32(m, records + r * 0x34 + 4, r + 1 < nrec ? records + (r + 1) * 0x34 : 0);
        }
        store32(m, ring + 4, nrec ? records : kArena + 0x1FF0);
        if (!nrec) store32(m, kArena + 0x1FF0, 0);
        store32(m, kGlyphRing, ring);
        // the code and its documented glyph
        u32 code;
        switch (rng() % 5) {
        case 0: code = 0x20; break;
        case 1: code = 0x21 + rng() % 0x5E; break;
        case 2: code = 0x8080 + ((rng() % 4) << 8); code += rng() % 0x80; break;
        case 3: code = 0x8080 + ((rng() % 4) << 8) + 0x80; code += rng() % 0x80; break;
        default: code = pick(rng, {0x80, 0x7F, 0x8000, 0x8400, 0x8480, 0x9000, 0xFFFF, 0x0, 0x1F}); break;
        }
        const u32 style = rng() % 9, colour = rng() % 4, mode = rng() % 3;
        const u32 count = rd16(style == 7 ? small : f, kFntGlyphCount);
        const u32 glyph = host_glyph_index(code, count);
        // raster slots: a few decoys and the one that must hit (glyph, colour) with a GS entry
        const u32 nslots = 1 + rng() % 6, hit = rng() % nslots;
        for (u32 s = 0; s < nslots; ++s) {
            const u32 sv = slots + s * 32;
            store32(m, sv + 4, s == hit ? glyph : glyph + 1 + rng() % 3);
            store16(m, sv + 8, static_cast<u16>(s == hit ? colour : colour + (rng() % 2)));
            store32(m, sv + 16, gs + s * 16);
            store32(m, sv + 24, s + 1 < nslots ? sv + 32 : 0);
        }
        store32(m, mgr + 8, slots);
        store32(m, kRasterSlots, mgr);
        m.at(kDefaultGlyphFlags)[0] = static_cast<u8>(rng());
        store16(m, kDefaultGlyphFlags, static_cast<u16>(rng()));
        for (u32 s = 0; s < 9; ++s) m.at(kStyleSizes + s)[0] = static_cast<u8>(pick(rng, {32, 24, 16, 40}));
        store32(m, kScaleX, pick(rng, {0, 128, 96}));
        store32(m, kScaleY, pick(rng, {0, 128}));
        const Pair p = pair(m, PAIR(fn_frFontCreateGlyphNode_003b0620), Args{code, style, colour, mode}, rng(), "frFontCreateGlyphNode");
        const u32 node = static_cast<u32>(p.hand.v0);
        if (nrec) {
            CHECK(node == records + 8);
            CHECK(load16(m, node) == code);
            // frFontCacheGlyph's cache hit returns the GS-list entry (+0x10) of the slot holding the documented glyph
            CHECK(load32(m, node + 28) == gs + hit * 16);
            ++hits;
        } else {
            CHECK(node == 0);  // K_Abort returned; the node was written at address 0
        }
        replaced += glyph == kGlyphReplacement;
        two_byte += code >= 0x8080 && code < 0x8400;
    }
    CHECK(hits > 3500);
    CHECK(replaced > 100);
    CHECK(two_byte > 1000);
    // the rule's fixed points: 80 80 is glyph 0, 80 FF glyph 0x7F, 81 80 glyph 0x80, 'A' glyph 0x21
    CHECK(host_glyph_index(0x8080, 506) == 0);
    CHECK(host_glyph_index(0x80FF, 506) == 0x7F);
    CHECK(host_glyph_index(0x8180, 506) == 0x80);
    CHECK(host_glyph_index('A', 506) == 0x21);
    CHECK(host_glyph_index(' ', 506) == 0x1F7);
}

TEST_CASE("game(font): frFontKerningAdjust over the kerning pairs, styles and scales") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B0840u};
    const u32 a = kArena + 0x100, b = kArena + 0x200;
    int nonzero = 0;
    for (int it = 0; it < 6000; ++it) {
        fill_random(m, a, kGlyphSize, rng);
        fill_random(m, b, kGlyphSize, rng);
        store16(m, a, static_cast<u16>(rng() % 4 ? pick(rng, {'a', 'e', 'o', 'u', 0x80C1, 0x80C5, 0x80CF, 0x80D5}) : rng() % 0x8400));
        store16(m, b, static_cast<u16>(rng() % 4 ? pick(rng, {'T', 'Y', 0x80B4, 0x80B9}) : rng() % 0x8400));
        m.at(a + 21)[0] = static_cast<u8>(pick(rng, {0, 0, 1, 1, 2, 8}));
        store32(m, a + 36, rng() % 10 ? b : 0);
        store32(m, kScaleX, pick(rng, {0, 128, 96, 300, 0xFFFFFF00u, 0x7FFFFFFFu, 0x80000001u}));
        const Pair p = pair(m, PAIR(fn_frFontKerningAdjust_003b0840), Args{a}, rng(), "frFontKerningAdjust");
        nonzero += p.hand.v0 != 0;
    }
    CHECK(nonzero > 1000);
    // documented: 'a' before 'T' at scale off -> 3, 'o' before 'Y' -> 2
    store16(m, a, 'a');
    store16(m, b, 'T');
    m.at(a + 21)[0] = 0;
    store32(m, a + 36, b);
    store32(m, kScaleX, 0);
    CHECK(pair(m, PAIR(fn_frFontKerningAdjust_003b0840), Args{a}, 1, "a T").hand.v0 == 3);
    store16(m, a, 'o');
    store16(m, b, 'Y');
    CHECK(pair(m, PAIR(fn_frFontKerningAdjust_003b0840), Args{a}, 1, "o Y").hand.v0 == 2);
}

TEST_CASE("game(font): line-node setters, widths and row helpers on random line chains") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B19D0u};
    int faded = 0;
    for (int it = 0; it < 1500; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        fill_random(m, 0, 0x80, rng);
        const u32 n = 1 + rng() % 6;
        const Chain c = build_chain(m, rng, 0, n, 0);
        const Chain d = build_chain(m, rng, 6, 1 + rng() % 4, 50);
        const u32 line = c.lines[rng() % n];
        const u32 maybe_null = rng() % 25 == 0 ? 0 : line;
        const u32 s = rng();
        pair(m, PAIR(fn_frFontInitLineNode_003b05c0), Args{kLines + 9 * kLineSize}, s, "frFontInitLineNode");
        CHECK(load32(m, kLines + 9 * kLineSize + 44) == kLines + 9 * kLineSize);
        pair(m, PAIR(fn_frFontLineSetAlpha_003b0bb0), Args{maybe_null, rng() & 0xFF}, s, "frFontLineSetAlpha alpha");
        pair(m, PAIR(fn_frFontNodeSetCode_003b0c20), Args{rng() % 25 ? c.lines[0] : 0, rng() & 0xFFFF}, s, "frFontNodeSetCode code");
        pair(m, PAIR(fn_frFontLineResetAlpha_003b0c70), Args{maybe_null}, s, "frFontLineResetAlpha");
        pair(m, PAIR(fn_frFontLineSetStyle_003b0ce0), Args{maybe_null, rng() % 9}, s, "frFontLineSetStyle style");
        pair(m, PAIR(fn_frFontLineSetPos_003b0d70), Args{maybe_null, sx(rng()), sx(rng())}, s, "frFontLineSetPos pos");
        pair(m, PAIR(fn_frFontLineSetColourSet_003b0dd0), Args{maybe_null, rng() & 0xFF}, s, "frFontLineSetColourSet colour");
        pair(m, PAIR(fn_frFontLineSetRgba_003b0e20), Args{maybe_null, sx(rng())}, s, "frFontLineSetRgba rgba");
        Pair p = pair(m, PAIR(fn_frFontLineFadeStep_003b0ec0), Args{maybe_null}, s, "frFontLineFadeStep fade");
        faded += p.hand.v0 == 1;
        // widths: one line, and per row
        p = pair(m, PAIR(fn_frFontLineGetWidth_003b19d0), Args{line}, s, "frFontLineGetWidth line width");
        CHECK(p.hand.v0 == sx(static_cast<u32>(host_line_width(m, line))));
        const u32 anchor = rng() % 20 ? c.lines[rng() % n] : 0;
        p = pair(m, PAIR(fn_frFontChainCountLines_003b1a90), Args{anchor}, s, "frFontChainCountLines count");
        if (anchor) CHECK(p.hand.v0 == n);
        s32 row = static_cast<s32>(rng() % (n + 2));
        if (rng() % 10 == 0) row -= 3;
        pair(m, PAIR(fn_frFontChainGetRowWidth_003b1b00), Args{sx(static_cast<u32>(row)), anchor}, s, "frFontChainGetRowWidth row width");
        pair(m, PAIR(fn_frFontChainGetRowPos_003b1bc0), Args{kOut, sx(static_cast<u32>(row)), anchor}, s, "frFontChainGetRowPos row pos");
        if (anchor && row >= 0 && static_cast<u32>(row) < n) {
            CHECK(load32(m, kOut) == load32(m, c.lines[static_cast<u32>(row)] + 4));
            CHECK(load32(m, kOut + 4) == load32(m, c.lines[static_cast<u32>(row)] + 8));
        }
        const s32 x = static_cast<s32>(rng() % 10000) - 3000, y = static_cast<s32>(rng() % 3000) - 500;
        pair(m, PAIR(fn_frFontChainMoveTo_003b1c40), Args{sx(static_cast<u32>(x)), sx(static_cast<u32>(y)), anchor}, s, "frFontChainMoveTo move");
        if (anchor) {
            CHECK(load32(m, c.lines[0] + 4) == static_cast<u32>(x));
            CHECK(load32(m, c.lines[0] + 8) == static_cast<u32>(y));
        }
        pair(m, PAIR(fn_frFontChainCentreAt_003b1c90), Args{sx(static_cast<u32>(x)), sx(static_cast<u32>(y)), anchor}, s, "frFontChainCentreAt centre");
        const u32 ja = rng() % 15 ? c.lines[rng() % n] : 0, jb = rng() % 15 ? d.lines[0] : 0;
        p = pair(m, PAIR(fn_frFontLineChainJoin_003b1920), Args{ja, jb, sx(pick(rng, {0, 1, 1, 2, 0xFFFFFFFFu}))}, s, "frFontLineChainJoin join");
        CHECK(p.hand.v0 == (ja == 0 ? jb : jb == 0 ? ja : jb));
    }
    CHECK(faded > 200);
}

TEST_CASE("game(font): the small state accessors (default flags, spacing, sizes, tag params and flags)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B1A70u};
    for (int it = 0; it < 1500; ++it) {
        fill_random(m, 0x7CD4E0u, 0x40, rng);
        fill_random(m, 0x95ABE0u, 0x2F0, rng);
        fill_random(m, kArena, 0x100, rng);
        for (u32 s = 0; s < 9; ++s) store32(m, kStyles + s * kStyleStride + kStyleFnt, kArena + 0x10 * (rng() % 8));
        const u32 s = rng();
        const u64 bits = sx(rng() % 4 ? rng() & 0xFFFF : rng());
        Pair p = pair(m, PAIR(fn_frFontSetDefaultGlyphFlags_003b0e70), Args{bits}, s, "frFontSetDefaultGlyphFlags");
        p = pair(m, PAIR(fn_frFontClearDefaultGlyphFlags_003b0e90), Args{bits}, s, "frFontClearDefaultGlyphFlags");
        pair(m, PAIR(fn_frFontResetLineSpacing_003b1a70), Args{}, s, "frFontResetLineSpacing");
        CHECK(load32(m, kLineSpacing) == 25);
        pair(m, PAIR(fn_frFontSetLineSpacing_003b1a80), Args{sx(rng())}, s, "frFontSetLineSpacing");
        pair(m, PAIR(fn_frFontLayoutNewRow_003b2400), Args{kArena + 0x40}, s, "frFontLayoutNewRow");
        p = pair(m, PAIR(fn_frFontTestTagFlags_003b2a00), Args{sx(rng())}, s, "frFontTestTagFlags");
        pair(m, PAIR(fn_frFontSetTagSlot_003b2a10), Args{rng() % 32, sx(rng())}, s, "frFontSetTagSlot");
        p = pair(m, PAIR(fn_frFontGetStyleSize_003b35c0), Args{sx(rng() % 4 ? rng() % 9 : rng())}, s, "frFontGetStyleSize");
        // style & 0xFF picks the record: wide arguments keep a low byte below 9 (records 9.. hold no .FNT pointer)
        const auto style_arg = [&rng]() -> u64 {
            if (rng() % 4) return rng() % 9;
            const u32 high = rng() & ~0xFFu;
            return sx(high | (rng() % 9));
        };
        pair(m, PAIR(fn_frFontGetStyleGlyphWidth_003b1a10), Args{style_arg()}, s, "frFontGetStyleGlyphWidth");
        pair(m, PAIR(fn_frFontGetStyleGlyphHeight_003b1a40), Args{style_arg()}, s, "frFontGetStyleGlyphHeight");
        p = pair(m, PAIR(fn_frFontTagGetParam0_003af360), Args{}, s, "frFontTagGetParam0");
        CHECK(p.hand.v0 == sx(load32(m, kTagParams)));
        pair(m, PAIR(fn_frFontTagGetParam1_003af370), Args{}, s, "frFontTagGetParam1");
        pair(m, PAIR(fn_frFontTagGetParam2_003af380), Args{}, s, "frFontTagGetParam2");
        pair(m, PAIR(fn_frFontTagGetParam3_003af390), Args{}, s, "frFontTagGetParam3");
    }
}

TEST_CASE("game(font): rbAlloc / rbFree and the GS-list entries") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B46B0u};
    const u32 ring = kArena + 0x1F00, rec0 = kArena + 0x100;
    const u32 head = kArena + 0x1800, ent0 = kArena + 0x1000;
    for (int it = 0; it < 2000; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        const u32 n = rng() % 5;
        for (u32 r = 0; r < n; ++r) {
            store32(m, rec0 + r * 0x40, rng() % 4 ? 1 + rng() % 3 : 0);
            store32(m, rec0 + r * 0x40 + 4, r + 1 < n ? rec0 + (r + 1) * 0x40 : 0);
        }
        store32(m, ring + 4, n ? rec0 : kArena + 0x1FF0);
        store32(m, kArena + 0x1FF0, 0);
        const u32 s = rng();
        Pair p = pair(m, PAIR(fn_rbAlloc_003b46b0), Args{ring}, s, "rbAlloc");
        if (n && load32(m, rec0) == 0) CHECK(p.hand.v0 == 0);
        const u32 payload = rng() % 10 == 0 ? 0 : rec0 + (rng() % 5) * 0x40 + 8;
        if (payload && rng() % 2) store32(m, payload - 4, 0);
        pair(m, PAIR(fn_rbFree_003b46f0), Args{payload, ring}, s, "rbFree");
        // a circular GS list: container `head`, entries linked through +0x18 / +0x1C
        const u32 k = rng() % 5;
        std::vector<u32> e{head};
        for (u32 i = 0; i < k; ++i) e.push_back(ent0 + i * 0x40);
        for (std::size_t i = 0; i < e.size(); ++i) {
            store32(m, e[i] + 28, e[(i + 1) % e.size()]);
            store32(m, e[i] + 24, e[(i + e.size() - 1) % e.size()]);
        }
        if (rng() % 3 == 0) store32(m, e[(1) % e.size()], 0);
        store32(m, kGslList, head);
        pair(m, PAIR(fn_fmGslAllocEntry_003b4520), Args{}, s, "fmGslAllocEntry");
        const u32 rel = rng() % 15 == 0 ? 0 : ent0 + 0x200 + (rng() % 4) * 0x40;
        p = pair(m, PAIR(fn_fmGslReleaseEntry_003b4580), Args{rel}, s, "fmGslReleaseEntry");
        CHECK(p.hand.v0 == sx(load32(m, kGslFreeCount)));
    }
}

TEST_CASE("game(font): raster-slot lookup and ageing on random slot lists") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B3770u};
    const u32 mgr = kArena + 0x1F00, slot0 = kArena + 0x100;
    int moved = 0, found = 0;
    for (int it = 0; it < 3000; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        const u32 n = rng() % 9;
        for (u32 i = 0; i < n; ++i) {
            const u32 sv = slot0 + i * 0x40;
            store32(m, sv + 0, rng() % 4);
            store32(m, sv + 4, rng() % 6);
            store16(m, sv + 8, static_cast<u16>(rng() % 3));
            store16(m, sv + 10, static_cast<u16>(static_cast<s16>(static_cast<int>(rng() % 4) - 1)));
            store32(m, sv + 16, rng() % 3 ? 0 : kArena + 0x1000);
            store32(m, sv + 24, i + 1 < n ? sv + 0x40 : 0);
        }
        store32(m, mgr + 8, n ? slot0 : 0);
        store32(m, mgr + 12, n ? slot0 + (n - 1) * 0x40 : 0);
        const u32 fh = rng() % 2 ? kArena + 0x1800 : 0;
        store32(m, mgr + 16, fh);
        store32(m, mgr + 20, fh);
        store32(m, kRasterSlots, mgr);
        const u32 s = rng();
        const u32 g = rng() % 6, col = rng() % 3;
        Pair p = pair(m, PAIR(fn_frFontRasterLookup_003b3e00), Args{g, col}, s, "frFontRasterLookup");
        found += p.hand.v0 != 0;
        p = pair(m, PAIR(fn_frFontRasterFind_003b3dd0), Args{g, col}, s, "frFontRasterFind");
        const u32 before = load32(m, mgr + 20);
        pair(m, PAIR(fn_frFontRasterAgeSlots_003b3770), Args{}, s, "frFontRasterAgeSlots");
        moved += load32(m, mgr + 20) != before;
    }
    CHECK(found > 500);
    CHECK(moved > 500);
}

namespace {
// A random message text with every handler index as a tag code (leads F1..F8; the wait / parameter tags
// with the lead their parameters need), ASCII, newlines and two-byte glyphs.
std::vector<u8> random_text(std::mt19937& rng, bool with_end_codes) {
    std::vector<u8> t;
    const u32 n = 1 + rng() % 24;
    for (u32 i = 0; i < n; ++i) {
        switch (rng() % 6) {
        case 0: t.push_back(static_cast<u8>(0x20 + rng() % 0x5F)); break;
        case 1: t.push_back(10); break;
        case 2:
            t.push_back(static_cast<u8>(0x80 + rng() % 0x70));
            t.push_back(static_cast<u8>(0x80 + rng() % 0x70));
            break;
        default: {
            u32 index = rng() % 0x4C;
            u32 lead = 0xF1 + rng() % 8;
            if (rng() % 2) {
                index = pick(rng, {0x42, 0x43, 0x46, 0x47});
                lead = index < 0x44 ? 0xF3 : 0xF2;
            }
            const u32 code = (lead << 8) | index;
            if (!with_end_codes && (code == 0xF131 || code == 0xF110 || code == 0xF104)) {
                t.push_back('x');
                break;
            }
            t.push_back(static_cast<u8>(lead));
            t.push_back(static_cast<u8>(index));
            for (u32 w = 0; w + 1 < (lead & 0xF); ++w) {
                t.push_back(static_cast<u8>(1 + rng() % 0xEF));
                t.push_back(static_cast<u8>(1 + rng() % 0xEF));
            }
            break;
        }
        }
    }
    t.push_back(0);
    return t;
}
}  // namespace

TEST_CASE("game(font): frFontProcessTagEx / frFontProcessTag and the render-state tag handlers on random tag strings") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x3B2A30u};
    const u32 text = kArena + 0x400, scan = kArena + 0x100, win = kArena + 0x200;
    int waits = 0, dispatched = 0;
    for (int it = 0; it < 3000; ++it) {
        fill_random(m, kArena, kArenaSize, rng);
        const std::vector<u8> t = random_text(rng, rng() % 3 == 0);
        std::memcpy(m.at(text), t.data(), t.size());
        std::memset(m.at(text + static_cast<u32>(t.size())), 0, 64);  // a skip past the terminator lands on zeros
        if (rng() % 8 == 0) m.at(text + 1)[0] = 8;  // the "second byte 8" prefix skip
        store32(m, scan + 16, text);
        store32(m, scan + 20, win);
        store32(m, scan + 24, 0);
        store32(m, win + 52, rng() % 2);
        store32(m, kFlagWord389, rng() % 2 ? load32(m, kFlagWord389) | (1u << (389 % 32)) : load32(m, kFlagWord389) & ~(1u << (389 % 32)));
        const u32 tag = pick(rng, {0, 0xF342, 0xF343, 0xF246, 0xF247, 0xF246, 0xF5FF});
        const u32 s = rng();
        Pair p = pair(m, PAIR(fn_frFontProcessTagEx_003b2a30), Args{scan, tag}, s, "frFontProcessTagEx");
        CHECK(p.hand.v0 == 0);
        dispatched += tag != 0 && load32(m, win + 48) == tag;
        p = pair(m, PAIR(fn_frFontProcessTag_003b2bf0), Args{text, win, tag}, s, "frFontProcessTag");
        CHECK(same_frame_bytes(p, 48, 16, 32));
        // the handlers directly, on a parameter block at a random offset
        store32(m, scan + 24, rng() % 8);
        fill_random(m, text, 16, rng);
        if (rng() % 3 == 0) m.at(text + load32(m, scan + 24) + 1)[0] = 0xFF;
        if (rng() % 3 == 0) m.at(text + load32(m, scan + 24) + 3)[0] = 0xFF;
        const u64 code = sx(rng() % 2 ? 0xF246 : rng());
        pair(m, PAIR(fn_frFontTagSetParams01_003af3a0), Args{code, scan}, s, "frFontTagSetParams01");
        pair(m, PAIR(fn_frFontTagSetParams23_003af460), Args{code, scan}, s, "frFontTagSetParams23");
        pair(m, PAIR(fn_frFontTagWait_003af5a0), Args{code, scan}, s, "frFontTagWait");
        pair(m, PAIR(fn_frFontTagWaitIfFlag389_003af660), Args{code, scan}, s, "frFontTagWaitIfFlag389");
    }
    CHECK(dispatched > 300);
    // documented: "F2 46 p0 p1" waits (p0 - 1) | (p1 - 1) << 8 ticks and sets tag flag 0x80
    const u8 msg[] = {'H', 'i', 0xF2, 0x46, 0x0B, 0x01, '!', 0};
    std::memcpy(m.at(text), msg, sizeof msg);
    store32(m, win + 52, 0);
    store32(m, win + 60, 0x12345);
    pair(m, PAIR(fn_frFontProcessTag_003b2bf0), Args{text, win, 0xF246}, 1, "wait tag");
    CHECK(load32(m, win + 48) == 0xF246);
    CHECK(load32(m, win + 60) == 10);
    CHECK((load32(m, kTagFlags) & 0x80u) != 0);
    ++waits;
    CHECK(waits == 1);
}

#else

TEST_CASE("game(font): font replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game was configured without P3FES_RT_EXEC_ELF; nothing to compare");
}

#endif
