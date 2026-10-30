// Phase 5 pair tests for the render_im2d slice (game/src/render/render_im2d.cpp): RenderWare's Im2D
// submission path (docs/ANALYSIS/22_rendering.md sections 6, 8.1). The first pairs on the hardware boundary:
// every function but closeAndDispatchVU1Packet reaches _rwDMAOpenVIFPkt (recompiled: D8 fromSPR, D_STAT,
// D_PCR, the BC0F wait), so every pair runs on pair_harness.h's hardware-observing harness (run_pair_hw):
// result, callee-saved registers (128 bits), cycles, check points and the arena as always, plus the bus
// access log, the scratchpad, the RW sky driver globals, the packet templates and the DMA buffer window,
// on scripted D8_CHCR (idle / busy) and D_STAT (BC0F polls) reads; and, for all 18, every GPR in 128 bits and HI/LO,
// the register file at every check point and the dead stack (register fidelity: render_im2d.h, Frame).
//
// Worlds: a synthetic RW DMA state shaped like the dorm / battle snapshots (no packet, an open VIF packet,
// one with an open cnt tag, an open GIF packet; the scratchpad half nearly full to force the fromSPR copy;
// both scratchpad halves), random or real packet templates, fog bit, TME bit, resident program, packet
// limits 0 / 1 / 16 / 17 / 39. Real game data: the RW state of the battle and dorm snapshots
// (extracted/_ours/*/eeMemory.bin beside the ELF's tree; skipped when absent) driving a UI frame of
// game-shaped Im2D calls (sprite and glyph quads as tri-strips of four vertices, a fade, lines).
// Documented-rule checks: the packet layout of 22_rendering.md section 6 against a host model (head, batch
// headers, vertex order with the strip's alternating winding and the fan's hub, trailers, tail).
#include "pair_harness.h"

#include "p3fes/game/render_im2d.h"

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
P3FES_DECL_PAIR(fn_closeAndDispatchVU1Packet_004ec4c0)
P3FES_DECL_PAIR(fn_open2DVU1Pkt_004ec100)
P3FES_DECL_PAIR(fn_addCopyVU1Line_004ec8a0)
P3FES_DECL_PAIR(fn_addCopyVU1Triangle_004ecac0)
P3FES_DECL_PAIR(fn_addCopyVU1PrimLineList_004ecd40)
P3FES_DECL_PAIR(fn_addCopyVU1PrimPolyLine_004ecfd0)
P3FES_DECL_PAIR(fn_addCopyVU1PrimTriList_004ed260)
P3FES_DECL_PAIR(fn_addCopyVU1PrimTriStrip_004ed570)
P3FES_DECL_PAIR(fn_addCopyVU1PrimTriFan_004ed890)
P3FES_DECL_PAIR(fn_addCopyVU1IndPrimLineList_004edc20)
P3FES_DECL_PAIR(fn_addCopyVU1IndPrimPolyLine_004eded0)
P3FES_DECL_PAIR(fn_addCopyVU1IndPrimTriList_004ee180)
P3FES_DECL_PAIR(fn_addCopyVU1IndPrimTriStrip_004ee4b0)
P3FES_DECL_PAIR(fn_addCopyVU1IndPrimTriFan_004ee810)
P3FES_DECL_PAIR(fn_SkyIm2DRenderLine_004eca60)
P3FES_DECL_PAIR(fn_SkyIm2DRenderTriangle_004ecce0)
P3FES_DECL_PAIR(fn_SkyIm2DRenderPrimitive_004edba0)
P3FES_DECL_PAIR(fn_SkyIm2DRenderIndexedPrimitive_004eeb50)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace im2d = p3fes::game::im2d;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout ------------------------------------------------------------------------------------
constexpr u32 kVerts = 0x01900000u;  // vertex arrays (read only)
constexpr u32 kMaxVerts = 160;
constexpr u32 kIndices = 0x01910000u;  // u16 index arrays
constexpr u32 kGp = im2d::kGp;
constexpr u32 kGlobalsLo = 0x7CDDC0u, kGlobalsHi = 0x7CEB40u;  // $gp-20272 .. $gp-16868 and their neighbours
constexpr u32 kTplLo = 0x965850u, kTplHi = 0x965A40u;
constexpr u32 kDmaLo = 0x9B0200u, kDmaLen = 0x280000u;  // the DMA buffer (_rwDMADmaOpen, both snapshots)
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;   // the window the synthetic worlds use

constexpr u32 kType = kGp - 17212u, kFixup = kGp - 17208u, kCntTag = kGp - 17204u, kPktStart = kGp - 17196u;
constexpr u32 kQWrite = kGp - 17192u, kQLimit = kGp - 17188u, kAlloc = kGp - 17184u, kHalfEnd = kGp - 17180u;
constexpr u32 kHalfSize = kGp - 17164u, kHalf0 = kGp - 17160u, kHalf1 = kGp - 17156u, kGifTail = kGp - 17152u;
constexpr u32 kDmaPtr = kGp - 17128u, kSprBase = kGp - 17124u;
constexpr u32 kD8Chcr = 0x1000D000u, kDStat = 0x1000E010u, kDPcr = 0x1000E020u, kD8Madr = 0x1000D010u;
constexpr u32 kPrograms[4] = {0x5CD820u, 0x5CD980u, 0x5CD3B0u, 0x5CD5B0u};  // 038 039 036 037

// The templates 0x965850..0x965A2F as the dorm snapshot holds them (22_rendering.md section 6 decodes them).
const char* const kRealTemplates =
    "00000010000000170000000000000000" "0a000010000000000000000000000000" "01000010000000000000000000000000"
    "01000010000000000000000000000000" "01000060000000000000000000000000" "0100000000c02e301204000000000000"
    "00000011000000110000001100000000" "010000100000000004040001d403016c" "00000000000000000000000000000000"
    "00000011000000150000000000000000" "00000011000000000000000000000000" "00000000000000000000000000000000"
    "00feff440001003aff1f4bc30020cb45" "00feff440001003affff833f0000c842" "0080a24334a6493bff1f4bc30020cb45"
    "000065437a178f3bffff833f0000c842" "0000c8420000c8420000c8420000c842" "0020cb450020cb450020cb450020cb45"
    "f2a2bd3e75847b3e329082bd0020cb45" "000020440000e043ce14cb4a00000000" "0000000000000000604e7ec400000000"
    "00000045000000450000000000000000" "00000003e10100020000000000000000" "00000000000000000000001100000000"
    "00000010000000000000000000000000" "4901803f4901803f4901803f1283003f" "1283003f1283003f1283003f1283003f"
    "030000100000000000000000f903036c" "0d0000100000000000000000f0030d6c" "0000d8440000e4440000000000000000";

u32 get32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u64 rng64(std::mt19937& rng) { return (static_cast<u64>(rng()) << 32) | rng(); }
void fill_random(u8* p, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= len; i += 4) {
        const u32 v = rng();
        std::memcpy(p + i, &v, 4);
    }
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }

// --- worlds ----------------------------------------------------------------------------------------------
enum class Packet { None, VifOpen, VifOpenCnt, GifOpen };

struct World {
    Packet packet = Packet::VifOpen;
    u32 spr_fill = 0;  // bytes already in the scratchpad half
    bool spr_hi = false;
    u32 limit_lines = 39, limit_tris = 39;
    bool fog = false, tme = false;
    u32 resident = 0x5CD980u;
    bool chcr_busy = false;
    u32 stat_polls = 0;  // D_STAT reads without bit 8 before the BC0F wait ends
    bool real_templates = false;
};

World random_world(std::mt19937& rng) {
    World w;
    w.packet = static_cast<Packet>(pick(rng, {0, 1, 1, 1, 2, 2, 3}));
    w.spr_fill = rng() % 3 == 0 ? 16u * (rng() % 512) : 8192u - 16u * (1 + rng() % 64);  // often nearly full
    w.spr_hi = rng() % 2 == 0;
    w.limit_lines = pick(rng, {39, 39, 39, 16, 17, 1, 0, 5});
    w.limit_tris = pick(rng, {39, 39, 39, 16, 17, 1, 0, 5});
    w.fog = rng() % 2 == 0;
    w.tme = rng() % 2 == 0;
    w.resident = rng() % 5 == 0 ? (rng() & 0x01FFFFF0u) : kPrograms[rng() % 4];
    w.chcr_busy = rng() % 2 == 0;
    w.stat_polls = pick(rng, {0, 0, 1, 3});
    w.real_templates = rng() % 4 == 0;
    return w;
}

void put_real_templates(Machine& m) {
    const std::string hex = kRealTemplates;
    for (std::size_t i = 0; i + 1 < hex.size(); i += 2) m.at(kTplLo)[i / 2] = static_cast<u8>(std::stoul(hex.substr(i, 2), nullptr, 16));
}

// The synthetic RW state of one case (pointers inside [kWinLo, kWinLo + kWinLen)).
void install(Machine& m, std::mt19937& rng, const World& w) {
    fill_random(m.mem.scratchpad(), 0x4000, rng);
    fill_random(m.at(kTplLo), kTplHi - kTplLo, rng);
    if (w.real_templates) put_real_templates(m);
    fill_random(m.at(kWinLo), kWinLen, rng);
    put32(m, kHalfSize, 0x13F400u);
    put32(m, kHalf0, 0x9B0A00u);
    put32(m, kHalf1, 0xAEFE00u);
    put32(m, kHalfEnd, 0xAEFE00u);
    put32(m, kQWrite, 0x9B0A10u + 8u * (rng() % 12));
    put32(m, kQLimit, 0x9B0A78u);
    const u32 spr_base = w.spr_hi ? 0x70002000u : 0x70000000u;
    put32(m, kSprBase, spr_base);
    const u32 dma = 0x9C0000u + 16u * (rng() % 1024);
    put32(m, kDmaPtr, dma);
    put32(m, kCntTag, 0);
    put32(m, kGifTail, rng() % 3 == 0 ? 0x9BA000u + 16u * (rng() % 64) : 0);
    switch (w.packet) {
    case Packet::None:
        put32(m, kType, 0);
        put32(m, im2d::kSprWritePtr, rng() % 2 ? 0 : spr_base + w.spr_fill);
        put32(m, kAlloc, dma + 16u * (rng() % 64));
        put32(m, kPktStart, 0);
        break;
    case Packet::VifOpen:
    case Packet::VifOpenCnt:
        put32(m, kType, w.packet == Packet::VifOpen ? 0x1101u : 0x80001101u);
        put32(m, im2d::kSprWritePtr, spr_base + w.spr_fill);
        put32(m, kAlloc, dma + w.spr_fill);
        put32(m, kPktStart, dma - 16u * (rng() % 64));
        if (w.packet == Packet::VifOpenCnt) put32(m, kCntTag, dma - 16u * (1 + rng() % 32));
        break;
    case Packet::GifOpen:
        put32(m, kType, 0x102u);
        put32(m, im2d::kSprWritePtr, spr_base + w.spr_fill);
        put32(m, kAlloc, dma + w.spr_fill);
        put32(m, kPktStart, dma - 16u * (rng() % 64));
        break;
    }
    put32(m, kFixup, rng() % 4 == 0 ? spr_base + 16u * (rng() % 64) : 0);
    m.at(im2d::kIm2DFlags)[0] = static_cast<u8>((rng() & 0xFEu) | (w.fog ? 1u : 0u));
    put32(m, im2d::kResidentProgram, w.resident);
    put32(m, im2d::kMaxLinesPerPacket, w.limit_lines);
    put32(m, im2d::kMaxTrisPerPacket, w.limit_tris);
    put64(m, im2d::kRenderFlags, (rng64(rng) & ~0x10ull) | (w.tme ? 0x10u : 0u));
    fill_random(m.at(kVerts), kMaxVerts * 64u, rng);
}

// Random u16 indices below `nverts`.
void put_indices(Machine& m, std::mt19937& rng, u32 count, u32 nverts) {
    for (u32 i = 0; i < count + 4; ++i) put16(m, kIndices + 2u * i, static_cast<u16>(rng() % nverts));
}

HwCheck check_for(const World& w, u32 gpr_mask, std::map<unsigned, u64> gpr_in = {}, u32 dma_lo = kWinLo, u32 dma_len = kWinLen) {
    HwCheck hw;
    hw.regs[kD8Chcr] = w.chcr_busy ? 0x100u : 0u;
    if (w.stat_polls) {
        std::vector<u64> stat(w.stat_polls, 0);
        stat.push_back(0x100u);
        hw.reads[kDStat] = stat;
    }
    hw.ranges = {{kGlobalsLo, kGlobalsHi - kGlobalsLo}, {kTplLo, kTplHi - kTplLo}, {dma_lo, dma_len}};
    // Register fidelity everywhere (render_im2d.h, Frame): the requested mask is a floor, every pair compares
    // all GPRs, HI/LO, the register file at every check point and the frames and spills below $sp.
    hw.gpr_mask = gpr_mask | kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in = std::move(gpr_in);
    return hw;
}

constexpr u32 kV0 = 1u << GPR_V0;

// The ra slot of _rwDMAOpenVIFPkt's frame (48 bytes, $ra at +32) below open2DVU1Pkt's (48) below `frames`:
// equal in both runs and the link of the jal in open2DVU1Pkt -- the $sp and $ra hand-over of every level.
void check_callee_frame(const HwPair& p, u32 frames, bool opened) {
    CHECK(same_frame_bytes(p, frames + 96, 32, 8));
    if (opened) {
        u64 ra;
        std::memcpy(&ra, p.hand.base.dead_stack.data() + (kDeadStack - (frames + 96) + 32), 8);
        CHECK(ra == sx(0x4EC144u));
    }
}

// The number of primitives a builder draws for `n` (22_rendering.md section 6 / the instructions).
u64 prims_of(int kind, u64 n) {
    switch (kind) {
    case 0: return static_cast<u32>(n) >> 1;                   // line list
    case 1: return sx(static_cast<u32>(n) - 1);                // polyline
    case 2: return static_cast<u32>(n) / 3u;                   // triangle list
    default: return n < 3 ? 0 : sx(static_cast<u32>(n) - 2);  // strip, fan
    }
}

// Counts that cross the 16-primitive batch and the packet limit, and the small edge cases.
u64 pick_count(std::mt19937& rng, int kind) {
    u64 n = rng() % 3 == 0 ? pick(rng, {0, 1, 2, 3, 4, 5, 6, 16, 17, 18, 19, 33, 34, 35, 40, 41, 42, 78, 79, 80, 81, 117, 118, 120})
                           : rng() % 121;
    if (kind == 1 && n == 0) n = 1;  // a polyline of 0 vertices is 0xFFFFFFFF lines: never called so
    // the whole-register `n < 3` (with low words 0 / 1 the count would wrap to ~2^64: never called so)
    if (kind >= 3 && n >= 2 && rng() % 16 == 0) n |= static_cast<u64>(rng() | 1u) << 32;
    return n;
}

// --- the snapshot RW state ---------------------------------------------------------------------------
std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

// ======================================================================================================

TEST_CASE("game(render_im2d): closeAndDispatchVU1Packet closeAndDispatchVU1Packet -- the 64-byte tail, every register") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4EC4C0u};
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        install(m, rng, w);
        const u32 p = 0x70000000u + 16u * (rng() % 1020) + (i % 7 == 0 ? 4u * (rng() % 4) : 0u);  // a few unaligned
        put32(m, im2d::kSprWritePtr, p);
        HwCheck hw = check_for(w, kAllGprs);
        hw.compare_hilo = true;
        run_pair_hw(m, PAIR(fn_closeAndDispatchVU1Packet_004ec4c0), Args{}, rng(), "closeAndDispatchVU1Packet", hw);
        // documented: cnt1 + FLUSH, cnt1 + FLUSH from the templates, write pointer + 64
        u8 expect[64];
        std::memcpy(expect, m.at(im2d::kTplCnt1A), 16);
        const u64 flush[2] = {0x11000000u, 0};
        std::memcpy(expect + 16, flush, 16);
        std::memcpy(expect + 32, m.at(im2d::kTplCnt1B), 16);
        std::memcpy(expect + 48, m.at(im2d::kTplFlush), 16);
        CHECK(std::memcmp(m.mem.scratchpad() + ((p & ~15u) - 0x70000000u), expect, 64) == 0);
        CHECK(get32(m, im2d::kSprWritePtr) == p + 64);
    }
}

TEST_CASE("game(render_im2d): open2DVU1Pkt open2DVU1Pkt -- packet head, program call, DMA packet layer, every register") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4EC100u};
    int calls = 0, resident = 0, kicks = 0, busy_waits = 0;
    for (int i = 0; i < 800; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const bool tri = rng() % 2 == 0;
        const u32 n = rng() % 8 == 0 ? rng() % 60 : rng() % 40;
        u64 gs_prim = tri ? 5 : 1;
        if (rng() % 8 == 0) gs_prim |= rng64(rng) & ~0x7FFull;  // only the low 32 bits count (zero-extended)
        u64 program = rng() % 3 == 0 ? sx(w.resident) : sx(kPrograms[rng() % 4]);
        if (rng() % 16 == 0) program = rng64(rng);  // whole-register compare
        const u32 before = get32(m, im2d::kResidentProgram);
        HwCheck hw = check_for(w, kAllGprs, {{GPR_T0, program}, {GPR_T1, rng64(rng)}});
        hw.compare_hilo = true;
        const HwPair p = run_pair_hw(m, PAIR(fn_open2DVU1Pkt_004ec100), Args{3, tri ? 12u : 8u, n, gs_prim}, rng(), "open2DVU1Pkt", hw);
        CHECK(static_cast<u32>(p.hand.base.v0) == 1);
        // documented: the program is `call`ed and becomes resident unless it already was
        if (sx(before) == program) {
            ++resident;
            CHECK(get32(m, im2d::kResidentProgram) == before);
        } else {
            ++calls;
            CHECK(get32(m, im2d::kResidentProgram) == static_cast<u32>(program));
        }
        // documented: PRIM = (render flags | gs_prim) & 0x7FF in bits 15..25 of the GIF tag's second word
        u64 flags;
        std::memcpy(&flags, m.at(im2d::kRenderFlags), 8);
        CHECK(((get32(m, im2d::kTplGifTag + 4) >> 15) & 0x7FFu) == ((static_cast<u32>(flags) | static_cast<u32>(gs_prim)) & 0x7FFu));
        const std::size_t k = count_access(p.hand.bus, kD8Madr, true);
        kicks += k ? 1 : 0;
        busy_waits += count_access(p.hand.bus, kDPcr, true) ? 1 : 0;
    }
    MESSAGE("open2DVU1Pkt: " << calls << " program calls, " << resident << " resident, " << kicks << " runs with a fromSPR copy, "
                             << busy_waits << " with the D8 busy wait");
    CHECK(calls > 100);
    CHECK(resident > 100);
    CHECK(kicks > 50);
    CHECK(busy_waits > 20);
}

TEST_CASE("game(render_im2d): addCopyVU1Line / addCopyVU1Triangle addCopyVU1Line / addCopyVU1Triangle") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4EC8A0u};
    for (int i = 0; i < 400; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const bool tri = i % 2 == 1;
        const u32 desc = rng() % 2 ? im2d::kDescriptorFog : im2d::kDescriptorNoFog;
        const u32 va = kVerts + 64u * (rng() % kMaxVerts), vb = kVerts + 64u * (rng() % kMaxVerts),
                  vc = kVerts + 64u * (rng() % kMaxVerts);
        const u64 open_arg = rng() % 2 ? 0 : rng64(rng);
        if (!tri) {
            HwCheck hw = check_for(w, kV0);
            const HwPair p = run_pair_hw(m, PAIR(fn_addCopyVU1Line_004ec8a0), Args{desc, open_arg, va, vb}, rng(), "addCopyVU1Line", hw);
            check_callee_frame(p, 64, true);
        } else {
            HwCheck hw = check_for(w, kV0, {{GPR_T0, sx(vc)}});
            const HwPair p = run_pair_hw(m, PAIR(fn_addCopyVU1Triangle_004ecac0), Args{desc, open_arg, va, vb}, rng(), "addCopyVU1Triangle", hw);
            check_callee_frame(p, 80, true);
        }
    }
}

struct Builder {
    const char* name;
    Fn hand, recomp;
    int kind;  // 0 line list, 1 polyline, 2 tri list, 3 strip, 4 fan
    u32 frame;
};

TEST_CASE("game(render_im2d): the prim-array builders addCopyVU1Prim* addCopyVU1PrimLineList .. addCopyVU1PrimTriFan") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const Builder builders[] = {
        {"addCopyVU1PrimLineList", PAIR(fn_addCopyVU1PrimLineList_004ecd40), 0, 112}, {"addCopyVU1PrimPolyLine", PAIR(fn_addCopyVU1PrimPolyLine_004ecfd0), 1, 112},
        {"addCopyVU1PrimTriList", PAIR(fn_addCopyVU1PrimTriList_004ed260), 2, 112},  {"addCopyVU1PrimTriStrip", PAIR(fn_addCopyVU1PrimTriStrip_004ed570), 3, 128},
        {"addCopyVU1PrimTriFan", PAIR(fn_addCopyVU1PrimTriFan_004ed890), 4, 128},
    };
    std::mt19937 rng{0x4ECD40u};
    for (const Builder& b : builders) {
        int multi_packet = 0;
        for (int i = 0; i < 300; ++i) {
            const World w = random_world(rng);
            install(m, rng, w);
            const u64 n = pick_count(rng, b.kind);
            const u32 desc = rng() % 2 ? im2d::kDescriptorFog : im2d::kDescriptorNoFog;
            const u64 open_arg = rng() % 2 ? 0 : rng64(rng);
            const HwPair p = run_pair_hw(m, b.hand, b.recomp, Args{desc, open_arg, kVerts, n}, rng(), b.name, check_for(w, kV0));
            const u64 prims = prims_of(b.kind, n);
            check_callee_frame(p, b.frame, prims != 0);
            const u32 limit = b.kind <= 1 ? w.limit_lines : w.limit_tris;
            if (limit != 0 && prims > limit) ++multi_packet;
        }
        INFO(b.name);
        CHECK(multi_packet > 20);
    }
}

TEST_CASE("game(render_im2d): the indexed builders addCopyVU1IndPrim* addCopyVU1IndPrimLineList .. addCopyVU1IndPrimTriFan") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const Builder builders[] = {
        {"addCopyVU1IndPrimLineList", PAIR(fn_addCopyVU1IndPrimLineList_004edc20), 0, 128},
        {"addCopyVU1IndPrimPolyLine", PAIR(fn_addCopyVU1IndPrimPolyLine_004eded0), 1, 128},
        {"addCopyVU1IndPrimTriList", PAIR(fn_addCopyVU1IndPrimTriList_004ee180), 2, 128},
        {"addCopyVU1IndPrimTriStrip", PAIR(fn_addCopyVU1IndPrimTriStrip_004ee4b0), 3, 144},
        {"addCopyVU1IndPrimTriFan", PAIR(fn_addCopyVU1IndPrimTriFan_004ee810), 4, 144},
    };
    std::mt19937 rng{0x4EDC20u};
    for (const Builder& b : builders) {
        for (int i = 0; i < 300; ++i) {
            const World w = random_world(rng);
            install(m, rng, w);
            const u64 n = pick_count(rng, b.kind);
            put_indices(m, rng, static_cast<u32>(n) + 4, 1 + rng() % kMaxVerts);
            const u32 desc = rng() % 2 ? im2d::kDescriptorFog : im2d::kDescriptorNoFog;
            const u64 open_arg = rng() % 2 ? 0 : rng64(rng);
            const HwPair p = run_pair_hw(m, b.hand, b.recomp, Args{desc, open_arg, kVerts, kIndices}, rng(), b.name,
                                         check_for(w, kV0, {{GPR_T0, n}}));
            check_callee_frame(p, b.frame, prims_of(b.kind, n) != 0);
        }
    }
}

TEST_CASE("game(render_im2d): the device entry points SkyIm2DRender{Line,Triangle,Primitive,IndexedPrimitive}") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4EDBA0u};
    int early = 0;
    for (int i = 0; i < 1200; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        switch (i % 4) {
        case 0: {  // SkyIm2DRenderLine(verts, numVerts, i0, i1)
            const HwPair p = run_pair_hw(m, PAIR(fn_SkyIm2DRenderLine_004eca60), Args{kVerts, rng64(rng), rng() % kMaxVerts, rng() % kMaxVerts},
                                         rng(), "SkyIm2DRenderLine", check_for(w, kV0));
            CHECK(static_cast<u32>(p.hand.base.v0) == 1);
            check_callee_frame(p, 16 + 64, true);
            break;
        }
        case 1: {  // SkyIm2DRenderTriangle(verts, numVerts, i0, i1, i2)
            const HwPair p = run_pair_hw(m, PAIR(fn_SkyIm2DRenderTriangle_004ecce0), Args{kVerts, rng64(rng), rng() % kMaxVerts, rng() % kMaxVerts},
                                         rng(), "SkyIm2DRenderTriangle", check_for(w, kV0, {{GPR_T0, rng() % kMaxVerts}}));
            CHECK(static_cast<u32>(p.hand.base.v0) == 1);
            check_callee_frame(p, 16 + 80, true);
            break;
        }
        default: {  // SkyIm2DRender(Indexed)Primitive(prim, verts, n [, indices, numIndices])
            const bool indexed = i % 4 == 3;
            u64 prim = rng() % 4 == 0 ? pick(rng, {0, 6, 7, 0xFFFFFFFFu}) : 1 + rng() % 5;
            if (rng() % 16 == 0) prim = rng64(rng);  // signed / unsigned 64-bit range tests
            if (rng() % 16 == 0) prim = 0xFFFFFFFF00000003ull;
            const bool call = static_cast<s64>(prim) > 0 && prim < 6;
            const int kind = call ? static_cast<int>(prim) - 1 : 0;
            const u64 n = pick_count(rng, kind);
            if (indexed) put_indices(m, rng, static_cast<u32>(n) + 4, 1 + rng() % kMaxVerts);
            HwCheck hw = check_for(w, call ? kV0 : kAllGprs, indexed ? std::map<unsigned, u64>{{GPR_T0, n}} : std::map<unsigned, u64>{});
            const HwPair p = indexed ? run_pair_hw(m, PAIR(fn_SkyIm2DRenderIndexedPrimitive_004eeb50), Args{prim, kVerts, rng64(rng), kIndices}, rng(),
                                                   "SkyIm2DRenderIndexedPrimitive", hw)
                                     : run_pair_hw(m, PAIR(fn_SkyIm2DRenderPrimitive_004edba0), Args{prim, kVerts, n, rng64(rng)}, rng(),
                                                   "SkyIm2DRenderPrimitive", hw);
            CHECK(static_cast<u32>(p.hand.base.v0) == 1);
            early += call ? 0 : 1;
            break;
        }
        }
    }
    CHECK(early > 30);
}

// --- documented packet layout (22_rendering.md section 6) against a host model ---------------------------
struct Q {
    u64 lo, hi;
};
Q q_at(Machine& m, u32 va) {
    Q q;
    if (va >= 0x70000000u) {
        std::memcpy(&q, m.mem.scratchpad() + (va - 0x70000000u), 16);
    } else {
        std::memcpy(&q, m.mem.main_ram() + va, 16);
    }
    return q;
}

// Builds the expected quadwords of one packet (head without the program call, batches, tail) for the
// primitive vertex addresses `prims` and compares them with the scratchpad from `p0`.
void check_packet(Machine& m, u32 p0, bool with_call, u32 prim_qw, const std::vector<std::array<u32, 3>>& prims, u32 verts_per) {
    u32 p = p0 + 8u * 16u + (with_call ? 16u : 0u);
    std::size_t done = 0, batch = 0;
    while (done < prims.size()) {
        const u32 n = static_cast<u32>(std::min<std::size_t>(16, prims.size() - done));
        INFO("batch " << batch << " (" << n << " primitives)");
        const Q h0 = q_at(m, p), h1 = q_at(m, p + 16);
        CHECK(h0.lo == (0x10000000ull | (prim_qw * n + 2)));
        CHECK(h0.hi == (0x0100040404000000ull | n));
        CHECK(h1.lo == 0xC000C00020000000ull);
        CHECK(h1.hi == static_cast<u64>(0x7C008000u | ((prim_qw * n) << 16)) << 32);
        p += 32;
        for (u32 k = 0; k < n; ++k) {
            for (u32 v = 0; v < verts_per; ++v) {
                const u32 src = prims[done + k][v];
                CHECK(std::memcmp(m.mem.scratchpad() + (p - 0x70000000u), m.mem.main_ram() + src, 64) == 0);
                p += 64;
            }
        }
        const Q t = q_at(m, p);
        const Q want = q_at(m, batch == 0 ? im2d::kTplFirstBatchEnd : im2d::kTplNextBatchEnd);
        CHECK((t.lo == want.lo && t.hi == want.hi));
        p += 16;
        done += n;
        ++batch;
    }
    const Q c0 = q_at(m, p), c1 = q_at(m, p + 16), want0 = q_at(m, im2d::kTplCnt1A);
    CHECK((c0.lo == want0.lo && c0.hi == want0.hi));
    CHECK((c1.lo == 0x11000000u && c1.hi == 0));
    CHECK(get32(m, im2d::kSprWritePtr) == p + 64);
}

TEST_CASE("game(render_im2d): the packet layout of 22_rendering.md section 6 (strip winding, fan hub, batches, tail)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x22D6u};
    for (int i = 0; i < 120; ++i) {
        World w;  // an open VIF packet with room: the packet starts at the write pointer, no fromSPR copy
        w.packet = Packet::VifOpen;
        w.spr_fill = 16u * (rng() % 4);
        w.spr_hi = rng() % 2 == 0;
        w.limit_lines = w.limit_tris = 39;
        w.resident = rng() % 2 ? kPrograms[1] : kPrograms[0];
        install(m, rng, w);
        const u32 p0 = get32(m, im2d::kSprWritePtr);
        const int which = i % 6;
        const u64 n = 1 + rng() % 41;
        const u32 desc = im2d::kDescriptorNoFog;  // programs 038 (lines) / 039 (triangles)
        put_indices(m, rng, static_cast<u32>(n) + 4, kMaxVerts);
        auto idx = [&](u32 k) { return static_cast<u32>(m.at(kIndices)[2 * k] | (m.at(kIndices)[2 * k + 1] << 8)); };
        auto vtx = [&](u32 k) { return kVerts + 64u * k; };
        std::vector<std::array<u32, 3>> prims;
        u32 prim_qw = 12, per = 3, program = kPrograms[1];
        switch (which) {
        case 0:  // strip: (i, i+1, i+2) for even i, (i, i+2, i+1) for odd i
            for (u32 t = 0; t + 2 < n && t < 39; ++t) prims.push_back(t % 2 == 0 ? std::array<u32, 3>{vtx(t), vtx(t + 1), vtx(t + 2)}
                                                                                 : std::array<u32, 3>{vtx(t), vtx(t + 2), vtx(t + 1)});
            if (n < 3 || n - 2 > 39) continue;
            run_pair_hw(m, PAIR(fn_addCopyVU1PrimTriStrip_004ed570), Args{desc, 0, kVerts, n}, rng(), "strip layout", check_for(w, kV0));
            break;
        case 1:  // fan: (0, i+1, i+2)
            for (u32 t = 0; t + 2 < n; ++t) prims.push_back({vtx(0), vtx(t + 1), vtx(t + 2)});
            if (n < 3 || n - 2 > 39) continue;
            run_pair_hw(m, PAIR(fn_addCopyVU1PrimTriFan_004ed890), Args{desc, 0, kVerts, n}, rng(), "fan layout", check_for(w, kV0));
            break;
        case 2:  // triangle list
            for (u32 t = 0; 3 * t + 2 < n; ++t) prims.push_back({vtx(3 * t), vtx(3 * t + 1), vtx(3 * t + 2)});
            if (prims.empty()) continue;
            run_pair_hw(m, PAIR(fn_addCopyVU1PrimTriList_004ed260), Args{desc, 0, kVerts, n}, rng(), "list layout", check_for(w, kV0));
            break;
        case 3:  // indexed strip through the index array
            for (u32 t = 0; t + 2 < n; ++t) prims.push_back(t % 2 == 0 ? std::array<u32, 3>{vtx(idx(t)), vtx(idx(t + 1)), vtx(idx(t + 2))}
                                                                       : std::array<u32, 3>{vtx(idx(t)), vtx(idx(t + 2)), vtx(idx(t + 1))});
            if (n < 3 || n - 2 > 39) continue;
            run_pair_hw(m, PAIR(fn_addCopyVU1IndPrimTriStrip_004ee4b0), Args{desc, 0, kVerts, kIndices}, rng(), "indexed strip layout",
                        check_for(w, kV0, {{GPR_T0, n}}));
            break;
        case 4:  // indexed fan: hub = index 0
            for (u32 t = 0; t + 2 < n; ++t) prims.push_back({vtx(idx(0)), vtx(idx(t + 1)), vtx(idx(t + 2))});
            if (n < 3 || n - 2 > 39) continue;
            run_pair_hw(m, PAIR(fn_addCopyVU1IndPrimTriFan_004ee810), Args{desc, 0, kVerts, kIndices}, rng(), "indexed fan layout",
                        check_for(w, kV0, {{GPR_T0, n}}));
            break;
        default:  // line list (program 038)
            prim_qw = 8;
            per = 2;
            program = kPrograms[0];
            for (u32 t = 0; 2 * t + 1 < n; ++t) prims.push_back({vtx(2 * t), vtx(2 * t + 1), 0});
            if (prims.empty()) continue;
            run_pair_hw(m, PAIR(fn_addCopyVU1PrimLineList_004ecd40), Args{desc, 0, kVerts, n}, rng(), "line list layout", check_for(w, kV0));
            break;
        }
        INFO("case " << which << " n " << n);
        check_packet(m, p0, w.resident != program, prim_qw, prims, per);
    }
}

// --- real RW state: a UI frame of game-shaped Im2D calls on the snapshots' driver state -------------------
// A quad as sprDrawSprite / frFontRasterDrawGlyph / H_Cursor_UpdateDrawTask build it (20_menu_ui.md section
// 5.4, 4.2): four vertices (x, y), (x + w, y), (x, y + h), (x + w, y + h), z, 1/z, UVs, the colour as floats,
// drawn as RwIm2DRenderPrimitive(4 = tri-strip, verts, 4).
void put_quad(Machine& m, u32 va, float x, float y, float w, float h, float z, u32 rgba) {
    for (u32 k = 0; k < 4; ++k) {
        im2d::RwIm2DVertex v{};
        v.x = x + ((k & 1) ? w : 0.0f);
        v.y = y + ((k & 2) ? h : 0.0f);
        v.z = z;
        v.recip_z = 1.0f / 160.0f;
        v.u = (k & 1) ? 1.0f : 0.0f;
        v.v = (k & 2) ? 1.0f : 0.0f;
        v.r = static_cast<float>(rgba & 0xFF);
        v.g = static_cast<float>((rgba >> 8) & 0xFF);
        v.b = static_cast<float>((rgba >> 16) & 0xFF);
        v.a = static_cast<float>(rgba >> 24);
        std::memcpy(m.at(va + 64u * k), &v, 64);
    }
}

TEST_CASE("game(render_im2d): a UI frame of Im2D calls on the battle and dorm snapshots' RW state") {
    for (const char* dir : {"battle_ref_6150", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        INFO(dir);
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.at(kGlobalsLo), snap.data() + kGlobalsLo, kGlobalsHi - kGlobalsLo);
        std::memcpy(m.at(kTplLo), snap.data() + kTplLo, kTplHi - kTplLo);
        std::memcpy(m.at(kDmaLo), snap.data() + kDmaLo, kDmaLen);
        std::mt19937 rng{0x5EEDu};
        fill_random(m.mem.scratchpad(), 0x4000, rng);
        World w;  // only the bus script matters here; the RW state is the snapshot's
        w.chcr_busy = false;
        const u32 alloc = get32(m, kAlloc);
        const u32 lo = (std::min(get32(m, kQWrite), alloc) & ~0xFFFu) - 0x1000u;
        int calls = 0;
        for (int i = 0; i < 160; ++i) {
            w.chcr_busy = i % 5 == 0;
            w.stat_polls = i % 7 == 0 ? 2 : 0;
            HwCheck hw = check_for(w, kV0, {}, lo, 0x60000u);
            const u32 kind = i % 8;
            if (kind < 5) {  // a sprite or glyph quad
                put_quad(m, kVerts, 16.0f * (i % 40), 12.0f * (i % 30), 16.0f, 24.0f, 1.0f + i, 0x80FFFFFFu - i);
                run_pair_hw(m, PAIR(fn_SkyIm2DRenderPrimitive_004edba0), Args{4, kVerts, 4, 0}, rng(), "sprite quad", hw);
            } else if (kind == 5) {  // a glyph run: several quads as one indexed triangle list
                const u32 glyphs = 1 + i % 12;
                for (u32 g = 0; g < glyphs; ++g) {
                    put_quad(m, kVerts + 256u * g, 8.0f * g, 200.0f, 8.0f, 16.0f, 2.0f, 0xFF404040u);
                    const u16 tri[6] = {static_cast<u16>(4 * g), static_cast<u16>(4 * g + 1), static_cast<u16>(4 * g + 2),
                                        static_cast<u16>(4 * g + 1), static_cast<u16>(4 * g + 3), static_cast<u16>(4 * g + 2)};
                    std::memcpy(m.at(kIndices + 12u * g), tri, 12);
                }
                hw.gpr_in = {{GPR_T0, 6u * glyphs}};
                run_pair_hw(m, PAIR(fn_SkyIm2DRenderIndexedPrimitive_004eeb50), Args{3, kVerts, 4u * glyphs, kIndices}, rng(), "glyph run", hw);
            } else if (kind == 6) {  // a full-screen fade: two triangles as a list
                put_quad(m, kVerts, 0.0f, 0.0f, 640.0f, 448.0f, 0.5f, 0x40000000u);
                std::memcpy(m.at(kVerts + 256u), m.at(kVerts + 64u), 64);
                std::memcpy(m.at(kVerts + 320u), m.at(kVerts + 128u), 64);
                run_pair_hw(m, PAIR(fn_SkyIm2DRenderPrimitive_004edba0), Args{3, kVerts, 6, 0}, rng(), "fade", hw);
            } else {  // a window frame: a polyline of five points
                put_quad(m, kVerts, 40.0f, 40.0f, 200.0f, 80.0f, 3.0f, 0xFFFFFFFFu);
                std::memcpy(m.at(kVerts + 256u), m.at(kVerts), 64);
                run_pair_hw(m, PAIR(fn_SkyIm2DRenderPrimitive_004edba0), Args{2, kVerts, 5, 0}, rng(), "window frame", hw);
            }
            ++calls;
        }
        CHECK(calls == 160);
        CHECK(get32(m, kType) == 0x1101u);  // the frame's Im2D calls leave the VIF packet open
    }
}

}  // namespace

#else

TEST_CASE("game(render_im2d): Im2D replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game was configured without P3FES_RT_EXEC_ELF; nothing to compare");
}

#endif
