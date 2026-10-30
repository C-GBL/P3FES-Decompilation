// Phase 5 pair tests for the render_rw2 slice (game/src/render/rw_builders.cpp): RenderWare sky-driver builders that
// reach the DMA packet layer (docs/ANALYSIS/22_rendering.md sections 2.4, 3.2, 5, 7). Every pair runs on
// pair_harness.h's hardware-observing harness (run_pair_hw): result, callee-saved registers (128 bits), cycles, check
// points and the arena as always, plus the bus access log (D8 fromSPR, D_STAT, D_PCR, the DMAC handler's channel
// registers), the scratchpad, the RW sky-driver globals and the DMA buffer window, on scripted D8_CHCR / D_STAT reads;
// and, for every function, every GPR in 128 bits, HI/LO, the register file at every check point (callees' entry check
// points included, which is what checks the arguments and $ra each call hands over) and the dead stack. Functions
// whose recompiled callees reach far (the material bridges, the PDS 2D bridges, the raster copy) compare the whole
// of main RAM.
//
// Worlds: a synthetic RW DMA state shaped like the dorm / battle snapshots (no packet, an open VIF packet, one with an
// open cnt tag, an open GIF packet; the scratchpad half nearly full to force the fromSPR copy), random register files,
// random driver flags; real game data: the RW state of the battle and dorm snapshots (extracted/_ours/*/eeMemory.bin
// beside the ELF's tree; skipped when absent) for the per-frame functions (render states, camera end, show raster,
// the raster packets, the flip). Documented-rule checks: the A+D packets against host models (22_rendering.md 5.4,
// the GS register numbers), the resource-reference ring flush, the PTank constant UV layout.
#include "pair_harness.h"

#include "p3fes/game/rw_builders.h"

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
P3FES_DECL_PAIR(fn_sub_46FB70_0046fb70)
P3FES_DECL_PAIR(fn_sub_470780_00470780)
P3FES_DECL_PAIR(fn_sub_471210_00471210)
P3FES_DECL_PAIR(fn_sub_472130_00472130)
P3FES_DECL_PAIR(fn_sub_472170_00472170)
P3FES_DECL_PAIR(fn_sub_4721B0_004721b0)
P3FES_DECL_PAIR(fn_sub_4721F0_004721f0)
P3FES_DECL_PAIR(fn_sub_472230_00472230)
P3FES_DECL_PAIR(fn_sub_473340_00473340)
P3FES_DECL_PAIR(fn_sub_473380_00473380)
P3FES_DECL_PAIR(fn_HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc_004a26d0)
P3FES_DECL_PAIR(fn_sub_4D4280_004d4280)
P3FES_DECL_PAIR(fn__rwDMAWaitQueue_004d53f0)
P3FES_DECL_PAIR(fn__rwDMAReqFlip_004d5270)
P3FES_DECL_PAIR(fn_SkyRasterShowRaster_004d9460)
P3FES_DECL_PAIR(fn_sub_4D8E80_004d8e80)
P3FES_DECL_PAIR(fn_sub_4E4E40_004e4e40)
P3FES_DECL_PAIR(fn_sub_4E4180_004e4180)
P3FES_DECL_PAIR(fn_sub_4E4420_004e4420)
P3FES_DECL_PAIR(fn_sub_4E4560_004e4560)
P3FES_DECL_PAIR(fn_sub_4E46C0_004e46c0)
P3FES_DECL_PAIR(fn_RpSkyRenderStateSet_004d7f60)
P3FES_DECL_PAIR(fn_sub_478440_00478440)
P3FES_DECL_PAIR(fn_sub_479840_00479840)
P3FES_DECL_PAIR(fn_sub_485EF0_00485ef0)
P3FES_DECL_PAIR(fn_sub_485FF0_00485ff0)
P3FES_DECL_PAIR(fn_sub_4748C0_004748c0)
P3FES_DECL_PAIR(fn_sub_4733C0_004733c0)
P3FES_DECL_PAIR(fn_sub_4E4800_004e4800)
P3FES_DECL_PAIR(fn_sub_477470_00477470)
P3FES_DECL_PAIR(fn_sub_478100_00478100)
P3FES_DECL_PAIR(fn_sub_477810_00477810)
P3FES_DECL_PAIR(fn_sub_477C90_00477c90)
P3FES_DECL_PAIR(fn_sub_4EF540_004ef540)
P3FES_DECL_PAIR(fn_sub_46C330_0046c330)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace rwb = p3fes::game::rwb;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout ---------------------------------------------------------------------------------------------
constexpr u32 kGlobalsLo = 0x7CDDC0u, kGlobalsHi = 0x7CEB40u;  // $gp-20272 .. $gp-16868 and their neighbours
constexpr u32 kRwLo = 0x95DE00u, kRwHi = 0x965C00u;            // RW absolute globals (palette word, flip data, ...)
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;          // the DMA window the synthetic worlds use
constexpr u32 kObj = 0x01880000u;                              // objects of a case (rasters, cameras, rings)
constexpr u32 kObjLen = 0x10000u;

constexpr u32 gp(s32 off) { return kGp + static_cast<u32>(off); }
constexpr u32 kType = gp(-17212), kFixup = gp(-17208), kCntTag = gp(-17204), kPktStart = gp(-17196);
constexpr u32 kQWrite = gp(-17192), kQLimit = gp(-17188), kAlloc = gp(-17184), kHalfEnd = gp(-17180);
constexpr u32 kHalfSize = gp(-17164), kHalf0 = gp(-17160), kHalf1 = gp(-17156), kGifTail = gp(-17152);
constexpr u32 kSprPtr = gp(-17148), kDmaPtr = gp(-17128), kSprBase = gp(-17124);
constexpr u32 kD8Chcr = 0x1000D000u, kD9Chcr = 0x1000D400u, kDStat = 0x1000E010u;

u32 get32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u64 get64(const Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.mem.main_ram() + va, 8);
    return v;
}
void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void putf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
u64 rng64(std::mt19937& rng) {
    const u64 hi = rng();  // two statements: the operands of | are unsequenced
    return (hi << 32) | rng();
}
void fill_random(u8* p, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= len; i += 4) {
        const u32 v = rng();
        std::memcpy(p + i, &v, 4);
    }
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }
bool coin(std::mt19937& rng, u32 one_in = 2) { return rng() % one_in == 0; }
// The register-file seed of a pair, from the case index: a seed drawn from `rng` inside the argument list of
// run_pair_hw would be evaluated in a compiler-dependent order against the other draws there.
u32 seed_of(int i) { return 0x9E3779B9u * static_cast<u32>(i + 1); }

// --- the synthetic RW DMA state (as test_render_im2d.cpp) -------------------------------------------------------
enum class Packet { None, VifOpen, VifOpenCnt, GifOpen };

struct World {
    Packet packet = Packet::VifOpen;
    u32 spr_fill = 0;
    bool spr_hi = false;
    bool chcr_busy = false;
    u32 stat_polls = 0;
};

World random_world(std::mt19937& rng) {
    World w;
    w.packet = static_cast<Packet>(pick(rng, {0, 1, 1, 1, 2, 2, 3}));
    // often nearly full (the fromSPR copy), but with room for the closing tags the packet layer writes unchecked
    w.spr_fill = coin(rng, 3) ? 16u * (rng() % 496) : 8192u - 16u * (16 + rng() % 16);
    w.spr_hi = coin(rng);
    w.chcr_busy = coin(rng);
    w.stat_polls = pick(rng, {0, 0, 1, 3});
    return w;
}

void install(Machine& m, std::mt19937& rng, const World& w) {
    fill_random(m.mem.scratchpad(), 0x4000, rng);
    fill_random(m.at(kWinLo), kWinLen, rng);
    // The two halves' queue blocks hold type-0 entries (the DMA handler skips unknown types), so a swap that hands a
    // half to _rwDMAHandler drains it without touching a channel.
    std::memset(m.at(0x9B0A00u), 0, 0x80);
    std::memset(m.at(0xAEFE00u), 0, 0x80);
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
    put32(m, kGifTail, coin(rng, 3) ? 0x9BA000u + 16u * (rng() % 64) : 0);
    switch (w.packet) {
    case Packet::None:
        put32(m, kType, 0);
        put32(m, kSprPtr, coin(rng) ? 0 : spr_base + w.spr_fill);
        put32(m, kAlloc, dma + 16u * (rng() % 64));
        put32(m, kPktStart, 0);
        break;
    case Packet::VifOpen:
    case Packet::VifOpenCnt:
        put32(m, kType, w.packet == Packet::VifOpen ? 0x1101u : 0x80001101u);
        put32(m, kSprPtr, spr_base + w.spr_fill);
        put32(m, kAlloc, dma + w.spr_fill);
        put32(m, kPktStart, dma - 16u * (rng() % 64));
        if (w.packet == Packet::VifOpenCnt) put32(m, kCntTag, dma - 16u * (1 + rng() % 32));
        break;
    case Packet::GifOpen:
        put32(m, kType, 0x102u);
        put32(m, kSprPtr, spr_base + w.spr_fill);
        put32(m, kAlloc, dma + w.spr_fill);
        put32(m, kPktStart, dma - 16u * (rng() % 64));
        break;
    }
    put32(m, kFixup, coin(rng, 4) ? spr_base + 16u * (rng() % 64) : 0);
    std::memset(m.at(kObj), 0, kObjLen);
}

// What every pair compares: the globals, the RW absolute globals, the DMA window, plus `extra`; the whole register
// file at every check point, every GPR in 128 bits, HI/LO, the dead stack, the bus log and the scratchpad.
HwCheck check_for(const World& w, std::vector<GuestRange> extra = {}, std::map<unsigned, u64> gpr_in = {}) {
    HwCheck hw;
    // D8 (fromSPR) busy for its first two reads in a busy world, idle after; D9 (toSPR, the PTank streamers) idle.
    hw.regs[kD8Chcr] = 0;
    if (w.chcr_busy) hw.reads[kD8Chcr] = {0x100u, 0x100u};
    hw.regs[kD9Chcr] = 0;
    if (w.stat_polls) {
        std::vector<u64> stat(w.stat_polls, 0);
        stat.push_back(0x100u);
        hw.reads[kDStat] = stat;
    }
    hw.ranges = {{kGlobalsLo, kGlobalsHi - kGlobalsLo}, {kRwLo, kRwHi - kRwLo}, {kWinLo, kWinLen}, {kObj, kObjLen}};
    for (const GuestRange& r : extra) hw.ranges.push_back(r);
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.gpr_in = std::move(gpr_in);
    return hw;
}
// The whole of main RAM (functions whose recompiled callees reach far): restored before the second run, compared.
const GuestRange kAllRam{0, EEMemory::kMainRamSize};

std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

// The A+D quadword {data, register} at `va` of the scratchpad or RAM.
struct Ad {
    u64 data, reg;
};
Ad ad_at(Machine& m, u32 va) {
    Ad a;
    const u8* p = guest_bytes(m, {va & ~15u, 16});
    std::memcpy(&a.data, p, 8);
    std::memcpy(&a.reg, p + 8, 8);
    return a;
}

// ======================================================================================================

TEST_CASE("game(render_rw2): the PDS 2D bridge entries sub_46FB70 / sub_470780 / sub_471210 (pair tail calls)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46FB70u};
    struct Entry {
        const char* name;
        Fn hand, recomp;
    };
    const Entry entries[] = {{"sub_46FB70", PAIR(fn_sub_46FB70_0046fb70)},
                             {"sub_470780", PAIR(fn_sub_470780_00470780)},
                             {"sub_471210", PAIR(fn_sub_471210_00471210)}};
    for (const Entry& e : entries) {
        for (int i = 0; i < 40; ++i) {
            const World w = random_world(rng);
            install(m, rng, w);
            // pair = {out0, out1}: the bridges' vertex / colour outputs (the instance counts of the RW globals are
            // zero in the ELF image, so the bridges take their empty path).
            const u32 pair = kObj + 16u * (rng() % 64);
            put32(m, pair, kObj + 0x1000u + 16u * (rng() % 64));
            put32(m, pair + 4, kObj + 0x2000u + 16u * (rng() % 64));
            run_pair_hw(m, e.hand, e.recomp, Args{rng64(rng), pair, rng64(rng), rng64(rng)}, seed_of(i), e.name,
                        check_for(w, {kAllRam}));
        }
    }
}

// An RxPS2AllPipeData (RenderWare 3.x layout; RpMeshPS2AllBridgeCallBack reads exactly these fields): +0 object
// private data, +4 material private data {+20, +24 VU1 code array}, +12 mesh header, +28 spExtra, +40 transType,
// +41 primType, +44 mesh, +48 resEntry reference, +60 surface properties, +64 texture (none: the untextured path),
// +68 material colour.
u32 put_pipe_data(Machine& m, std::mt19937& rng) {
    const u32 pipe = kObj + 0x100u, mat = kObj + 0x300u, code = kObj + 0x340u, header = kObj + 0x500u;
    const u32 ref = kObj + 0x380u, res = kObj + 0x600u, surf = kObj + 0x3C0u;
    put32(m, pipe + 0, kObj + 0x200u);
    put32(m, pipe + 4, mat);
    put32(m, mat + 20, rng() % 16);
    put32(m, mat + 24, code);
    for (u32 k = 0; k < 8; ++k) put32(m, code + 4 * k, 0x5CD000u + 0x100u * (rng() % 8));
    put32(m, pipe + 12, header);
    putf(m, pipe + 28, static_cast<float>(rng() % 100) / 10.0f);
    m.at(pipe + 40)[0] = static_cast<u8>(rng() & 0x3Fu);
    m.at(pipe + 41)[0] = static_cast<u8>(pick(rng, {3, 4}));
    put32(m, pipe + 44, header + 16u + 12u * (rng() % 4));
    put32(m, pipe + 48, ref);
    put32(m, ref, res);
    put32(m, res + 0, rng() % 4);
    put32(m, res + 4, rng() % 2);
    put32(m, res + 32, 0x9D0000u + 16u * (rng() % 256));
    put32(m, pipe + 60, surf);
    for (u32 k = 0; k < 3; ++k) putf(m, surf + 4 * k, static_cast<float>(rng() % 100) / 99.0f);
    put32(m, pipe + 64, 0);
    put32(m, pipe + 68, rng());
    return pipe;
}

TEST_CASE("game(render_rw2): the skin bridge wrappers sub_472130 .. sub_473380") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x472130u};
    struct Entry {
        const char* name;
        Fn hand, recomp;
    };
    const Entry entries[] = {{"sub_472130", PAIR(fn_sub_472130_00472130)}, {"sub_472170", PAIR(fn_sub_472170_00472170)},
                             {"sub_4721B0", PAIR(fn_sub_4721B0_004721b0)}, {"sub_4721F0", PAIR(fn_sub_4721F0_004721f0)},
                             {"sub_472230", PAIR(fn_sub_472230_00472230)}, {"sub_473340", PAIR(fn_sub_473340_00473340)},
                             {"sub_473380", PAIR(fn_sub_473380_00473380)}};
    for (const Entry& e : entries) {
        int with_palette = 0;
        for (int i = 0; i < 24; ++i) {
            // (the bridges' packets can overrun what they asked _rwDMAOpenVIFPkt for: keep them inside the scratchpad)
            World w = random_world(rng);
            w.spr_hi = false;
            w.spr_fill %= 0x1000u;
            install(m, rng, w);
            const u32 pipe = put_pipe_data(m, rng);
            // The pending palette record: a bone count of 0..2 and its index bytes.
            const bool palette = coin(rng);
            put32(m, rwb::kSkinPalettePending, palette ? kObj + 0x800u : 0);
            put32(m, kObj + 0x800u, rng() % 3);
            put32(m, kObj + 0x810u, kObj + 0x900u);
            fill_random(m.at(kObj + 0x900u), 64, rng);
            with_palette += palette ? 1 : 0;
            run_pair_hw(m, e.hand, e.recomp, Args{pipe, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i), e.name,
                        check_for(w, {kAllRam}));
        }
        INFO(e.name);
        CHECK(with_palette > 3);
    }
}

TEST_CASE("game(render_rw2): the resEntry header 0x4A26D0 (HandleUnexpected__... in functions.json)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A26D0u};
    for (int i = 0; i < 200; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const u32 owner = kObj + 16u * (rng() % 32);
        put32(m, owner + 8, rng());
        const u32 out = kObj + 0x400u + 4u * (rng() % 32);
        u32 size = pick(rng, {0, 16, 64, 256});
        size += 16u * (rng() % 8);
        const u64 tag = rng64(rng);
        run_pair_hw(m, PAIR(fn_HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc_004a26d0),
                    Args{sx(owner), sx(out), sx(size), tag}, seed_of(i), "resEntry header", check_for(w));
    }
}

TEST_CASE("game(render_rw2): sub_4D4280 -- the resource-reference ring flush") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D4280u};
    int split = 0, fences = 0;
    for (int i = 0; i < 300; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const u32 slots = pick(rng, {1, 2, 4, 8, 16});
        const u32 ring = kObj + 0x100u;
        put16(m, gp(rwb::kGpPuRefSlots), static_cast<u16>(slots));
        put32(m, gp(rwb::kGpPuRefRing), ring);
        for (u32 k = 0; k < 16; ++k) {
            const u32 res = kObj + 0x1000u + 32u * k;
            put32(m, ring + 4 * k, res);
            put32(m, res, 0x9D0000u + 16u * (rng() % 4096));
            s32 count = static_cast<s32>(pick(rng, {0, 1, 3, 100, 0xFFFF, 0x10000, 0x1FFFE, 0x20000}));
            count += static_cast<s32>(rng() % 3);
            if (coin(rng, 10)) count = -static_cast<s32>(rng() % 100);
            put32(m, res + 4, static_cast<u32>(count));
            if (count > 0xFFFF) ++split;
        }
        const u32 read = rng() % slots, write = coin(rng, 4) ? read : rng() % slots;
        put16(m, gp(rwb::kGpPuRefRead), static_cast<u16>(read));
        put16(m, gp(rwb::kGpPuRefWrite), static_cast<u16>(write));
        run_pair_hw(m, PAIR(fn_sub_4D4280_004d4280), Args{rng64(rng), rng64(rng), 0, 0}, seed_of(i), "PU ref flush", check_for(w));
        // documented: both indices reset when anything was pending, every visited entry's count cleared
        if (read != write) {
            ++fences;
            CHECK(get32(m, gp(rwb::kGpPuRefRead)) == 0);
            CHECK(static_cast<u16>(get32(m, gp(rwb::kGpPuRefWrite))) == 0);
            CHECK(get32(m, get32(m, ring + 4 * read) + 4) == 0);
        }
    }
    CHECK(split > 100);
    CHECK(fences > 100);
}

TEST_CASE("game(render_rw2): _rwDMAWaitQueue and _rwDMAReqFlip") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D53F0u};
    for (int i = 0; i < 400; ++i) {
        // Idle worlds may swap halves (_rwDMAForceBufferSwap waits for the queue to drain and for the busy flags,
        // which only the DMA interrupts clear, so they have no open packet whose close would kick a channel); busy
        // worlds have an empty build half, so nothing swaps.
        const bool idle = coin(rng);
        const bool flip = i % 2 == 1;
        World w = random_world(rng);
        if (idle) w.packet = Packet::None;
        install(m, rng, w);
        m.at(gp(rwb::kGpQueuePending))[0] = static_cast<u8>((idle || !flip) && coin(rng) ? 1 : 0);
        m.at(gp(rwb::kGpDmaBusyA))[0] = static_cast<u8>(!idle && coin(rng) ? 1 : 0);
        m.at(gp(rwb::kGpDmaBusyB))[0] = static_cast<u8>(!idle && (m.at(gp(rwb::kGpDmaBusyA))[0] == 0 || coin(rng)) ? 1 : 0);
        m.at(gp(rwb::kGpHalfIndex))[0] = static_cast<u8>(rng() % 2);
        m.at(gp(rwb::kGpFlipCount))[0] = static_cast<u8>(rng());
        // The handler's queue: head..tail of type-67 entries (skipped by _rwDMAHandler), or empty.
        const u32 head = 0x9B0A10u + 8u * (rng() % 4);
        // (a flip that swaps first waits for the queue to be drained: empty then)
        const bool swaps_first = flip && m.at(gp(rwb::kGpQueuePending))[0] != 0;
        const u32 n = swaps_first || coin(rng) ? 0 : 1 + rng() % 3;
        for (u32 k = 0; k < n; ++k) {
            put32(m, head + 8 * k, 67);
            put32(m, head + 8 * k + 4, 0);
        }
        put32(m, gp(rwb::kGpQueueHead), head);
        put32(m, gp(rwb::kGpQueueTail), head + 8 * n);
        const u32 half_start = get32(m, kHalf0 + 4u * m.at(gp(rwb::kGpHalfIndex))[0]);
        if (!idle || coin(rng)) put32(m, kQWrite, half_start);
        else put32(m, kQWrite, half_start + 8u * (1 + rng() % 8));
        if (!flip) {
            run_pair_hw(m, PAIR(fn__rwDMAWaitQueue_004d53f0), Args{rng64(rng), rng64(rng), 0, 0}, seed_of(i), "_rwDMAWaitQueue",
                        check_for(w));
        } else {
            const u32 data = kObj + 16u * (rng() % 64);
            run_pair_hw(m, PAIR(fn__rwDMAReqFlip_004d5270), Args{sx(data), rng64(rng), 0, 0}, seed_of(i), "_rwDMAReqFlip",
                        check_for(w));
            CHECK(m.at(gp(rwb::kGpQueuePending))[0] == 1);
        }
    }
}

// A frame raster in the object area: type byte +32, private flags +35, width +12, height +16, depth +20, offsets
// +28 / +30.
u32 put_raster(Machine& m, std::mt19937& rng, u32 va, u32 type, u32 pflags) {
    put32(m, va + 12, pick(rng, {640, 512, 256}));
    put32(m, va + 16, pick(rng, {448, 224, 256}));
    put32(m, va + 20, pick(rng, {32, 24, 16, 8, 4}));
    put16(m, va + 28, static_cast<u16>(rng()));
    put16(m, va + 30, static_cast<u16>(rng()));
    m.at(va + 32)[0] = static_cast<u8>((rng() & 0xF8u) | type);
    m.at(va + 35)[0] = static_cast<u8>(pflags);
    return va;
}

// The driver state the raster packets read: frame counter, the two FRAME_1 values, the shadows, interlace flags.
void put_raster_state(Machine& m, std::mt19937& rng) {
    put32(m, gp(rwb::kGpFrameCount), rng());
    put64(m, 0x9649F0u, rng64(rng));
    put64(m, 0x964B60u, rng64(rng));
    for (s32 off : {rwb::kGpZbuf1, rwb::kGpFrame1, rwb::kGpTest1, rwb::kGpXyoffset, rwb::kGpPrimShadow, rwb::kGpAlpha1,
                    rwb::kGpPrimShadowSaved})
        put64(m, gp(off), rng64(rng));
    m.at(gp(rwb::kGpInterlace))[0] = static_cast<u8>(coin(rng) ? 1 : 0);
    m.at(gp(rwb::kGpFieldParity))[0] = static_cast<u8>(rng() % 2);
    m.at(gp(rwb::kGpFlipCount))[0] = static_cast<u8>(rng());
    m.at(gp(rwb::kGpDmaBusyA))[0] = static_cast<u8>(rng() % 2);
    put32(m, gp(rwb::kGpFrameRaster), put_raster(m, rng, kObj + 0x200u, pick(rng, {5, 1, 2}), 0));
}

TEST_CASE("game(render_rw2): the raster packets sub_4E4180 / sub_4E4420 / sub_4E4560 / sub_4E46C0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4E4180u};
    for (int i = 0; i < 600; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        put_raster_state(m, rng);
        const int kind = i % 4;
        if (kind == 0) {
            const u64 mode = coin(rng) ? 2 : (coin(rng) ? rng64(rng) : pick(rng, {0, 1, 3}));
            run_pair_hw(m, PAIR(fn_sub_4E4180_004e4180), Args{mode, rng64(rng), 0, 0}, seed_of(i), "sub_4E4180", check_for(w));
        } else if (kind == 1 || kind == 2) {
            // stack arguments 9 and 10 at the caller's $sp
            put32(m, kSp, rng());
            put32(m, kSp + 8, coin(rng) ? 0 : rng());
            std::map<unsigned, u64> regs{{GPR_T0, rng64(rng)}, {GPR_T1, rng64(rng)}, {GPR_T2, rng64(rng)}, {GPR_T3, rng64(rng)}};
            const Args a{rng64(rng), rng64(rng), rng64(rng), rng64(rng)};
            if (kind == 1)
                run_pair_hw(m, PAIR(fn_sub_4E4420_004e4420), a, seed_of(i), "sub_4E4420", check_for(w, {}, regs));
            else
                run_pair_hw(m, PAIR(fn_sub_4E4560_004e4560), a, seed_of(i), "sub_4E4560", check_for(w, {}, regs));
        } else {
            run_pair_hw(m, PAIR(fn_sub_4E46C0_004e46c0), Args{rng64(rng), rng64(rng), 0, 0}, seed_of(i), "sub_4E46C0", check_for(w));
        }
    }
}

TEST_CASE("game(render_rw2): sub_4E4180 / sub_4E46C0 -- the A+D registers (documented)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4E46C0u};
    for (int i = 0; i < 100; ++i) {
        World w = random_world(rng);
        w.packet = Packet::VifOpen;
        w.spr_fill = 0;
        install(m, rng, w);
        put_raster_state(m, rng);
        m.at(gp(rwb::kGpInterlace))[0] = 0;
        const u32 p = get32(m, kSprPtr);
        const u64 frame = get64(m, coin(rng) ? 0x9649F0u : 0x964B60u);
        (void)frame;
        const bool z_only = i % 2 == 1;
        run_pair_hw(m, PAIR(fn_sub_4E4180_004e4180), Args{z_only ? 0u : 2u, 0, 0, 0}, seed_of(i), "sub_4E4180", check_for(w));
        // the A+D packet right after the open: tag (6 registers), then FRAME/ZBUF in mode order, TEST, DTHE, ALPHA, XY
        const u32 q = p;  // no fromSPR copy for a 32-qw packet into an empty half
        const Ad tag = ad_at(m, q);
        CHECK(tag.data == 0x1000000000008006ull);
        CHECK(tag.reg == 14);
        CHECK(ad_at(m, q + 16).reg == (z_only ? rwb::kGsZbuf1 : rwb::kGsFrame1));
        CHECK(ad_at(m, q + 32).reg == (z_only ? rwb::kGsFrame1 : rwb::kGsZbuf1));
        CHECK(ad_at(m, q + 48).reg == rwb::kGsTest1);
        CHECK((ad_at(m, q + 48).data & 0x70001u) == 0x30000u);  // ZTE, ZTST always, ATE off
        CHECK(ad_at(m, q + 64).reg == rwb::kGsDthe);
        CHECK(ad_at(m, q + 80).reg == rwb::kGsAlpha1);
        CHECK(ad_at(m, q + 80).data == 0x44);
        CHECK(ad_at(m, q + 96).reg == rwb::kGsXyoffset1);
        CHECK(get32(m, kSprPtr) == p + 112);
    }
}

TEST_CASE("game(render_rw2): RpSkyRenderStateSet 0x4D7F60 -- every state, every register") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D7F60u};
    int packets = 0;
    for (int i = 0; i < 800; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        put64(m, gp(rwb::kGpTest1), rng64(rng));
        put64(m, gp(rwb::kGpAlpha1), rng64(rng));
        put32(m, gp(rwb::kGpDimxEnabled), coin(rng, 3) ? 0 : rng());
        u64 state = pick(rng, {1, 1, 2, 2, 3, 3, 4, 5, 5, 0, 6, 7});
        if (coin(rng, 20)) state |= rng64(rng) << 3;  // whole-register compares
        u64 value = rng64(rng);
        if (state == 1) {
            value = pick(rng, {0, 0x55555555u, 1, 2});
            if (coin(rng, 8)) value += rng64(rng) << 32;
        }
        if (state == 4 || state == 5) {
            const u32 cell = kObj + 4u * (rng() % 64);
            put32(m, cell, coin(rng) ? rng() % 10 : rng());
            value = cell;
        }
        const u32 before = get32(m, kSprPtr);
        const HwPair p = run_pair_hw(m, PAIR(fn_RpSkyRenderStateSet_004d7f60), Args{state, value, rng64(rng), rng64(rng)},
                                     seed_of(i), "RpSkyRenderStateSet", check_for(w));
        if ((state == 2 || state == 3) && static_cast<u32>(p.hand.base.v0) == 1) {
            ++packets;
            // documented: a one-register A+D packet (tag + ALPHA_1 / TEST_1) and the shadow updated
            if (get32(m, kSprPtr) == before + 32) {
                const Ad a = ad_at(m, before + 16);
                CHECK(a.reg == (state == 2 ? rwb::kGsAlpha1 : rwb::kGsTest1));
                CHECK(a.data == get64(m, gp(state == 2 ? rwb::kGpAlpha1 : rwb::kGpTest1)));
            }
        }
    }
    CHECK(packets > 100);
}

TEST_CASE("game(render_rw2): SkyRasterShowRaster, the camera end update sub_4D8E80, sub_4E4E40") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D9460u};
    for (int i = 0; i < 300; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        put_raster_state(m, rng);
        const int kind = i % 3;
        if (kind == 0) {
            put64(m, gp(rwb::kGpShowRasterPending), coin(rng) ? 0 : rng64(rng));
            for (u32 k = 0; k < 4; ++k) put32(m, rwb::kDeferredOps + 4 * k, coin(rng, 4) ? rng() : 0);
            m.at(gp(rwb::kGpQueuePending))[0] = 0;
            run_pair_hw(m, PAIR(fn_SkyRasterShowRaster_004d9460), Args{rng64(rng), rng64(rng), 0, 0}, seed_of(i),
                        "SkyRasterShowRaster", check_for(w, {kAllRam}));
        } else if (kind == 1) {
            const u32 camera = kObj + 0x400u;
            const u32 type = pick(rng, {5, 5, 1, 2});
            const u32 pflags = coin(rng, 4) ? 0x90u : rng() & 0x6Fu;
            const u32 raster = put_raster(m, rng, kObj + 0x600u, type, pflags);
            put32(m, camera + 96, raster);
            put32(m, gp(rwb::kGpTexFlushPending), coin(rng) ? 1 : 0);
            run_pair_hw(m, PAIR(fn_sub_4D8E80_004d8e80), Args{rng64(rng), sx(camera), 0, 0}, seed_of(i), "sub_4D8E80",
                        check_for(w, {kAllRam}));
        } else {
            if (coin(rng, 4)) put32(m, gp(rwb::kGpFrameRaster), 0);
            run_pair_hw(m, PAIR(fn_sub_4E4E40_004e4e40), Args{rng64(rng), rng64(rng), 0, 0}, seed_of(i), "sub_4E4E40",
                        check_for(w, {kAllRam}));
        }
    }
}

// A PTank atomic: node {+8 atomic, +44 -> {+4 count}}, the plugin data offset, the tank block {+36/+40.. callbacks,
// +156 pipe}, the pipe's record index at +228 and its 36-byte records at +320.
struct Tank {
    u32 node, params, atomic, block, pipe;
};
Tank put_tank(Machine& m, std::mt19937& rng) {
    Tank t{kObj + 0x100u, kObj + 0x180u, kObj + 0x200u, kObj + 0x400u, kObj + 0x800u};
    const u32 off = 16u * (rng() % 8);
    put32(m, gp(rwb::kGpPtankDataOffset), off);
    put32(m, t.atomic + off, t.block);
    put32(m, t.node + 8, t.atomic);
    put32(m, t.node + 44, kObj + 0x1C0u);
    put32(m, kObj + 0x1C0u + 4, rng() % 64);
    put32(m, t.block + 156, t.pipe);
    put32(m, t.pipe + 228, rng() % 4);
    for (u32 k = 0; k < 4; ++k) put32(m, t.params + 4 * k, kObj + 0x2000u + 0x100u * k);
    return t;
}

TEST_CASE("game(render_rw2): the PTank callback setters sub_478440 / sub_479840") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x478440u};
    for (int i = 0; i < 200; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const Tank t = put_tank(m, rng);
        if (i % 2 == 0)
            run_pair_hw(m, PAIR(fn_sub_478440_00478440), Args{t.node, t.params, 0, 0}, seed_of(i), "sub_478440", check_for(w, {kAllRam}));
        else
            run_pair_hw(m, PAIR(fn_sub_479840_00479840), Args{t.node, t.params, 0, 0}, seed_of(i), "sub_479840", check_for(w, {kAllRam}));
        // documented: the render callback is installed at block +36 afterwards
        CHECK(get32(m, t.block + 36) == (i % 2 == 0 ? 0x477150u : 0x479170u));
    }
}

TEST_CASE("game(render_rw2): the PTank constant UV fills sub_485EF0 / sub_485FF0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x485EF0u};
    int fast = 0, slow = 0;
    for (int i = 0; i < 400; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const bool four = i % 2 == 1;
        const u32 tank = kObj + 0x100u;
        for (u32 k = 0; k < 8; ++k) putf(m, tank + 144 + 4 * k, static_cast<float>(rng() % 1000) / 999.0f);
        const u32 stream = kObj + 0x80u;
        const u32 dst = kObj + 0x1000u + 16u * (rng() % 16);
        const u32 stride = coin(rng) ? (four ? 8u : 16u) : pick(rng, {8, 12, 16, 20, 24, 32});
        put32(m, stream, dst);
        put32(m, stream + 4, stride);
        u64 count = pick(rng, {0, 1, 2, 5, 17, 40});
        // negative: the signed compare skips the loop (the streamer takes any count as a byte size: element path only)
        if (stride != (four ? 8u : 16u) && coin(rng, 16)) count = rng64(rng) | (1ull << 63);
        if (stride == (four ? 8u : 16u)) ++fast; else ++slow;
        const Args a{stream, count, tank, rng64(rng)};
        if (four)
            run_pair_hw(m, PAIR(fn_sub_485FF0_00485ff0), a, seed_of(i), "sub_485FF0", check_for(w));
        else
            run_pair_hw(m, PAIR(fn_sub_485EF0_00485ef0), a, seed_of(i), "sub_485EF0", check_for(w));
        // documented: the slow path writes (u, v) pairs vertex by vertex
        if (stride != (four ? 8u : 16u) && count == 1) {
            const u32 uv0 = four ? 144 : 144, v0 = four ? 148 : 156;
            CHECK(get32(m, dst) == get32(m, tank + uv0));
            CHECK(get32(m, dst + 4) == get32(m, tank + v0));
        }
    }
    CHECK(fast > 50);
    CHECK(slow > 50);
}

TEST_CASE("game(render_rw2): the PTank texture sub_4748C0 and the camera block sub_4733C0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4748C0u};
    for (int i = 0; i < 200; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        if (i % 2 == 0) {
            const u32 atomic = kObj + 0x100u, block = kObj + 0x400u;
            put32(m, atomic + 76, block);
            put64(m, block + 200, rng64(rng));
            put64(m, gp(rwb::kGpTest1), rng64(rng));
            u64 material = 0;
            if (!coin(rng, 4)) {
                material = kObj + 0x200u;
                // a raster that is already resident in the texture cache is out of reach here: the material's raster
                // pointer is 0, so RpSkyTexCacheAccessRaster returns 0 at once (its own tests are the bridge slice's)
                put32(m, kObj + 0x200u, 0);
                m.at(kObj + 0x200u + 80)[0] = static_cast<u8>(rng());
            }
            run_pair_hw(m, PAIR(fn_sub_4748C0_004748c0), Args{atomic, material, 0, 0}, seed_of(i), "sub_4748C0", check_for(w, {kAllRam}));
        } else {
            const u32 a = kObj + 0x100u, b = kObj + 0x200u, frame = kObj + 0x300u;
            fill_random(m.at(a), 64, rng);
            fill_random(m.at(b), 64, rng);
            put32(m, b + 4, frame);
            // a frame whose LTM is clean: RwFrameGetLTM returns frame + its matrix offset without updating
            run_pair_hw(m, PAIR(fn_sub_4733C0_004733c0), Args{a, b, 0, 0}, seed_of(i), "sub_4733C0", check_for(w, {kAllRam}));
        }
    }
}

TEST_CASE("game(render_rw2): sub_4E4800 -- the raster clear (GS sprite fill, CPU fill of a locked raster)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4E4800u};
    int gs = 0, cpu = 0;
    for (int i = 0; i < 400; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        put_raster_state(m, rng);
        const u32 raster = get32(m, gp(rwb::kGpFrameRaster));
        const u32 type = pick(rng, {0, 0, 4, 4, 1, 2, 2, 3, 5});
        m.at(raster + 32)[0] = static_cast<u8>(type);
        m.at(raster + 35)[0] = static_cast<u8>(coin(rng) ? 0x01u : rng());
        // locked pixels: a 256-byte-stride buffer in the object area (or none)
        put32(m, raster + 4, coin(rng, 6) ? 0 : kObj + 0x4000u);
        put32(m, raster + 20, pick(rng, {32, 16, 24, 8}));
        put32(m, raster + 24, 256);
        const u32 rect = kObj + 0x100u;
        put32(m, rect + 0, rng() % 16);
        put32(m, rect + 4, rng() % 16);
        put32(m, rect + 8, pick(rng, {0, 1, 3, 16, 32}));
        put32(m, rect + 12, pick(rng, {0, 1, 2, 7, 16}));
        const u64 colour = coin(rng, 4) ? rng64(rng) : rng();
        const HwPair p = run_pair_hw(m, PAIR(fn_sub_4E4800_004e4800), Args{rng64(rng), rect, colour, rng64(rng)}, seed_of(i),
                                     "sub_4E4800", check_for(w));
        if (type == 1 || type == 2) {
            ++gs;
            CHECK(static_cast<u32>(p.hand.base.v0) == 1);
        } else if (type == 0 || type == 4) {
            ++cpu;
        }
    }
    CHECK(gs > 50);
    CHECK(cpu > 100);
}

TEST_CASE("game(render_rw2): sub_477470 -- the PTank 2D lock record") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x477470u};
    for (int i = 0; i < 300; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        const u32 lock = kObj + 0x100u, data = kObj + 0x200u, pipe = kObj + 0x800u;
        put32(m, data + 76, pipe);
        const u32 index = rng() % 4;
        put32(m, pipe + 228, index);
        fill_random(m.at(pipe + 320), 36 * 4, rng);
        fill_random(m.at(lock), 48, rng);
        u64 flags = 0;
        for (u64 bit : {0x2ull, 0x2000ull, 0x80ull, 0x80000ull, 0x4ull, 0x4000ull, 0x10000000ull})
            if (coin(rng, 3)) flags |= bit;
        if (coin(rng, 8)) flags |= rng64(rng) & ~0x10000000ull;
        const std::map<unsigned, u64> regs{{GPR_T0, flags}};
        run_pair_hw(m, PAIR(fn_sub_477470_00477470), Args{lock, rng64(rng), data, rng64(rng)}, seed_of(i), "sub_477470",
                    check_for(w, {kAllRam}, regs));
        // documented: +0 always 1; a component asked for gets its record word and stride
        CHECK(get32(m, lock) == 1);
        CHECK(get32(m, lock + 16) == get32(m, pipe + 36 * index + 320));
        CHECK(get32(m, lock + 20) == 16);
        if ((flags & 2) || (flags & 0x2000)) CHECK(get32(m, lock + 36) == 4);
    }
}

TEST_CASE("game(render_rw2): the PTank constant fills sub_478100 / sub_477810 / sub_477C90") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x478100u};
    struct Fill {
        const char* name;
        Fn hand, recomp;
        u32 size;
    };
    const Fill fills[] = {{"sub_478100", PAIR(fn_sub_478100_00478100), 8},
                          {"sub_477810", PAIR(fn_sub_477810_00477810), 4},
                          {"sub_477C90", PAIR(fn_sub_477C90_00477c90), 16}};
    for (const Fill& fl : fills) {
        int unrolled = 0;
        for (int i = 0; i < 250; ++i) {
            const World w = random_world(rng);
            install(m, rng, w);
            const u32 tank = kObj + 0x100u;
            fill_random(m.at(tank + 100), 64, rng);
            const u32 stride = coin(rng, 3) ? fl.size : pick(rng, {4, 8, 12, 16, 20, 24, 32, 48});
            // (the streamers store doublewords: their stream is quadword aligned)
            const u32 stream = kObj + 0x80u, dst = kObj + 0x1000u + (stride == fl.size ? 16u : 4u) * (rng() % 16);
            put32(m, stream, dst);
            put32(m, stream + 4, stride);
            u64 count = pick(rng, {0, 1, 2, 7, 8, 9, 10, 16, 17, 25, 40, 64, 100});
            // negative: nothing written (the streamers take any count as a byte size: only on the element path)
            if (stride != fl.size && coin(rng, 12)) count = rng64(rng) | (1ull << 63);
            if (stride != fl.size && static_cast<s64>(count) >= 9) ++unrolled;
            run_pair_hw(m, fl.hand, fl.recomp, Args{stream, count, tank, rng64(rng)}, seed_of(i), fl.name, check_for(w));
            // documented: element k of a slow fill holds the tank's value
            if (stride != fl.size && static_cast<s64>(count) > 0) {
                const u32 k = static_cast<u32>(count) - 1;
                const u32 src = fl.size == 8 ? tank + 112 : fl.size == 4 ? tank + 124 : tank + 144;
                CHECK(std::memcmp(m.at(dst + k * stride), m.at(src), fl.size) == 0);
            }
        }
        INFO(fl.name);
        CHECK(unrolled > 40);
    }
}

TEST_CASE("game(render_rw2): sub_4EF540 -- the image upload header (BITBLTBUF / TRXREG)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4EF540u};
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        if (w.packet == Packet::VifOpenCnt) w.packet = Packet::GifOpen;
        install(m, rng, w);
        fill_random(m.at(0x965A40u), 0x40, rng);
        const u64 width = coin(rng) ? rng() % 1024 : rng64(rng), height = rng() % 1024;
        const u64 dbp = rng64(rng), dbw = rng() % 16, psm = pick(rng, {0, 2, 0x13, 0x14, 0x1B});
        const u64 size = coin(rng) ? rng() % 0x40000 : rng64(rng);
        const u64 flag = coin(rng) ? 0 : rng64(rng) | 1;
        const std::map<unsigned, u64> regs{{GPR_T0, psm}, {GPR_T1, size}, {GPR_T2, flag}};
        const u32 before = get32(m, kSprPtr);
        run_pair_hw(m, PAIR(fn_sub_4EF540_004ef540), Args{width, height, dbp, dbw}, seed_of(i), "sub_4EF540", check_for(w, {}, regs));
        // documented: BITBLTBUF (0x50) and TRXREG (0x52) at +48 / +80 of the packet when it went in place
        if (get32(m, kSprPtr) == before + 112) {
            const Ad b = ad_at(m, before + 48), t = ad_at(m, before + 80);
            CHECK(b.reg == 0x50);
            CHECK(((b.data >> 32) & 0x3FFFu) == (dbp & 0x3FFFu));
            CHECK(((b.data >> 56) & 0x3Fu) == (psm & 0x3Fu));
            CHECK(t.reg == 0x52);
            CHECK(t.data == (((height & 0xFFFFFFFFu) << 32) | (width & 0xFFFFFFFFu)));
        }
    }
}

TEST_CASE("game(render_rw2): sub_46C330 -- the VU1 record upload") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46C330u};
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        // (a 40-record packet is 202 qw: room for it in the half)
        w.spr_fill %= 0x800u;
        install(m, rng, w);
        const u32 src = kObj + 0x100u;
        fill_random(m.at(src), 80 * 40, rng);
        const u64 n = pick(rng, {0, 1, 2, 7, 8, 9, 10, 16, 17, 24, 25, 33, 40});
        const u32 before = get32(m, kSprPtr);
        const HwPair p = run_pair_hw(m, PAIR(fn_sub_46C330_0046c330), Args{src, n, rng64(rng), rng64(rng)}, seed_of(i),
                                     "sub_46C330", check_for(w));
        CHECK(p.hand.base.v0 == src);
        // documented: the count quadword then the records verbatim
        if (get32(m, kSprPtr) == before + 32 + 80 * static_cast<u32>(n) && n != 0) {
            u32 count;
            std::memcpy(&count, guest_bytes(m, {before + 16, 4}), 4);
            CHECK(count == static_cast<u32>(n));
            CHECK(std::memcmp(guest_bytes(m, {before + 32, 80}), m.at(src), 80) == 0);
        }
    }
}

// --- real RW state: the per-frame functions on the snapshots' driver state ----------------------------------------
TEST_CASE("game(render_rw2): render states, raster packets, camera end and raster clear on the snapshots' RW state") {
    int ran = 0;
    for (const char* dir : {"battle_ref_6150", "dorm_replay_4900", "b_5800"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        INFO(dir);
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());  // the whole machine as the snapshot holds it
        std::mt19937 rng{0x5EED2u};
        fill_random(m.mem.scratchpad(), 0x4000, rng);
        const u32 alloc = get32(m, kAlloc);
        const u32 lo = (std::min(get32(m, kQWrite), alloc) & ~0xFFFu) - 0x1000u;
        const u32 camera = get32(m, gp(-19504));  // the kwln root camera
        const u32 raster = get32(m, gp(rwb::kGpFrameRaster));
        World w;
        for (int i = 0; i < 90; ++i) {
            w.chcr_busy = i % 5 == 0;
            w.stat_polls = i % 7 == 0 ? 2 : 0;
            HwCheck hw = check_for(w, {{lo, 0x60000u}, kAllRam});
            switch (i % 6) {
            case 0:  // ALPHA_1 as the draw layer sets it (src alpha / inv src alpha, fix 0x80)
                run_pair_hw(m, PAIR(fn_RpSkyRenderStateSet_004d7f60), Args{2, pick(rng, {0x44, 0x80000044u, 0x48}), 0, 0},
                            seed_of(i), "ALPHA", hw);
                break;
            case 1:  // TEST_1 alpha test on / off
                run_pair_hw(m, PAIR(fn_RpSkyRenderStateSet_004d7f60), Args{3, pick(rng, {0x5000Du, 0x50000u, 0x3001u}), 0, 0},
                            seed_of(i), "TEST", hw);
                break;
            case 2:  // DIMX
                run_pair_hw(m, PAIR(fn_RpSkyRenderStateSet_004d7f60), Args{1, pick(rng, {0, 0x55555555u, 1}), 0, 0}, seed_of(i),
                            "DIMX", hw);
                break;
            case 3:  // the Z-only clear environment and its restore
                run_pair_hw(m, PAIR(fn_sub_4E4180_004e4180), Args{pick(rng, {0, 2}), 0, 0, 0}, seed_of(i), "sub_4E4180", hw);
                run_pair_hw(m, PAIR(fn_sub_4E46C0_004e46c0), Args{}, seed_of(i), "sub_4E46C0", hw);
                break;
            case 4:
                if (camera != 0)
                    run_pair_hw(m, PAIR(fn_sub_4D8E80_004d8e80), Args{0, camera, 0, 0}, seed_of(i), "camera end", hw);
                break;
            default: {  // a small clear of the frame raster
                const u32 rect = kObj + 0x100u;
                put32(m, rect + 0, rng() % 64);
                put32(m, rect + 4, rng() % 64);
                put32(m, rect + 8, 1 + rng() % 64);
                put32(m, rect + 12, 1 + rng() % 64);
                if (raster != 0)
                    run_pair_hw(m, PAIR(fn_sub_4E4800_004e4800), Args{0, rect, rng(), 0}, seed_of(i), "raster clear", hw);
                break;
            }
            }
            ++ran;
        }
    }
    MESSAGE("snapshot pairs: " << ran);
}

}  // namespace

#else

TEST_CASE("game(render_rw2): replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game was configured without P3FES_RT_EXEC_ELF; nothing to compare");
}

#endif
