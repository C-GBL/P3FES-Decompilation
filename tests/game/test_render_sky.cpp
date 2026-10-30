// Phase 5 pair tests for the render_sky slice (game/src/render/sky.cpp): the RenderWare sky driver's core (the
// render-state funnel, the camera begin / clear, the texture cache, the mip-map chain) and the PDS 2D / Im3D bridges
// (docs/ANALYSIS/22_rendering.md sections 2.4, 3.2, 5.3, 5.4). Every pair runs on pair_harness.h's hardware-observing
// harness (run_pair_hw): result, callee-saved registers (128 bits), cycles, check points and the arena, plus the bus
// access log, the scratchpad, the RW sky-driver globals, the RW absolute globals, the DMA window and the case's
// objects (or all of main RAM), on scripted D8_CHCR / D_STAT reads; every GPR in 128 bits, HI/LO, the register file
// at every check point (the callees' entry check points included: the arguments and $ra of every call) and the dead
// stack.
//
// Worlds: the synthetic RW DMA state of test_render_rw2.cpp (no packet, an open VIF packet, one with an open cnt tag,
// an open GIF packet; the scratchpad half nearly full to force the fromSPR copy), random register files, random driver
// shadows; synthetic rasters / cameras / cache slots / PipeData; and the real driver state of the battle and dorm
// snapshots (extracted/_ours/*/eeMemory.bin beside the ELF's tree; skipped when absent): every render state on the
// real shadows and rasters, the camera begin / clear on the kwln root camera, the cache placement on the cache's own
// rasters. Documented-rule checks: the A+D packets of the render states (register numbers, the shadows they send).
#include "pair_harness.h"

#include "p3fes/game/sky.h"

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
P3FES_DECL_PAIR(fn__rwSkySetRenderState_004d6b90)
P3FES_DECL_PAIR(fn_SkyCameraBeginUpdate_004d84c0)
P3FES_DECL_PAIR(fn_sub_4D8F40_004d8f40)
P3FES_DECL_PAIR(fn_sub_4E3640_004e3640)
P3FES_DECL_PAIR(fn_sub_4F0C70_004f0c70)
P3FES_DECL_PAIR(fn_sub_4F1B30_004f1b30)
P3FES_DECL_PAIR(fn_sub_4F1780_004f1780)
P3FES_DECL_PAIR(fn_sub_46FDD0_0046fdd0)
P3FES_DECL_PAIR(fn_RpPDS_G3_2DFont_PS2AllBridgeCallBack_004709e0)
P3FES_DECL_PAIR(fn_sub_471470_00471470)
P3FES_DECL_PAIR(fn_sub_4A2790_004a2790)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace sky = p3fes::game::sky;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout ---------------------------------------------------------------------------------------------
constexpr u32 kGlobalsLo = 0x7CDDC0u, kGlobalsHi = 0x7CEB40u;  // $gp-20272 .. $gp-16868 and their neighbours
constexpr u32 kRwLo = 0x95DE00u, kRwHi = 0x965C00u;            // RW absolute globals
constexpr u32 kCacheLo = 0x77EF00u, kCacheLen = 0x400u;        // the texture cache words 0x77F200.. and the ALPHA table
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;          // the DMA window the synthetic worlds use
constexpr u32 kObj = 0x01880000u;                              // objects of a case (rasters, cameras, slots)
constexpr u32 kObjLen = 0x20000u;

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
// Plausible floats (no NaN / denormal clutter): +-[0.01, 1000).
float rfloat(std::mt19937& rng) {
    const float f = static_cast<float>(rng() % 100000) / 100.0f + 0.01f;
    return (rng() & 1) ? -f : f;
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }
bool coin(std::mt19937& rng, u32 one_in = 2) { return rng() % one_in == 0; }
u32 seed_of(int i) { return 0x9E3779B9u * static_cast<u32>(i + 1); }

// --- the synthetic RW DMA state (as test_render_rw2.cpp) --------------------------------------------------------
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
    w.spr_fill = coin(rng, 3) ? 16u * (rng() % 496) : 8192u - 16u * (16 + rng() % 16);
    w.spr_hi = coin(rng);
    w.chcr_busy = coin(rng);
    w.stat_polls = pick(rng, {0, 0, 1, 3});
    return w;
}

void install(Machine& m, std::mt19937& rng, const World& w) {
    fill_random(m.mem.scratchpad(), 0x4000, rng);
    fill_random(m.at(kWinLo), kWinLen, rng);
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
    // _rwDMAWaitQueue (render_rw2, tested there) returns at once without a pending swap
    m.at(gp(-17252))[0] = 0;
}

// What every pair compares: the globals, the RW absolute globals, the texture cache words, the DMA window, the
// objects, plus `extra`; the whole register file at every check point, every GPR, HI/LO, the dead stack, the bus log
// and the scratchpad.
HwCheck check_for(const World& w, std::vector<GuestRange> extra = {}) {
    HwCheck hw;
    hw.regs[kD8Chcr] = 0;
    if (w.chcr_busy) hw.reads[kD8Chcr] = {0x100u, 0x100u};
    hw.regs[kD9Chcr] = 0;
    if (w.stat_polls) {
        std::vector<u64> stat(w.stat_polls, 0);
        stat.push_back(0x100u);
        hw.reads[kDStat] = stat;
    }
    hw.ranges = {{kGlobalsLo, kGlobalsHi - kGlobalsLo}, {kRwLo, kRwHi - kRwLo}, {kCacheLo, kCacheLen},
                 {kWinLo, kWinLen}, {kObj, kObjLen}};
    for (const GuestRange& r : extra) hw.ranges.push_back(r);
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}
const GuestRange kAllRam{0, EEMemory::kMainRamSize};

std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

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

// The driver shadows and flags the funnel and the camera read.
void put_shadows(Machine& m, std::mt19937& rng) {
    for (s32 off : {sky::kGpRenderFlags, sky::kGpZbuf1, sky::kGpFrame1, sky::kGpTest1, sky::kGpXyoffset, sky::kGpFogCol,
                    sky::kGpClamp1, sky::kGpTex1, sky::kGpAlpha1, sky::kGpXyBaseX, sky::kGpXyBaseY})
        put64(m, gp(off), rng64(rng));
    put32(m, gp(sky::kGpSrcBlend), rng() % 6);
    put32(m, gp(sky::kGpDestBlend), rng() % 6);
    put32(m, gp(sky::kGpVertexAlpha), coin(rng) ? 0 : 1);
    put32(m, gp(sky::kGpRasterAlpha), coin(rng) ? 0 : 1);
    put32(m, gp(sky::kGpRasterExt), 0x34u);
    put32(m, gp(sky::kGpFrameCount), rng());
    put64(m, sky::kFrame1A, rng64(rng));
    put64(m, sky::kFrame1B, rng64(rng));
    m.at(gp(sky::kGpCamFlags))[0] = static_cast<u8>(rng());
    m.at(gp(sky::kGpInterlace))[0] = static_cast<u8>(coin(rng) ? 1 : 0);
    m.at(gp(sky::kGpFieldParity))[0] = static_cast<u8>(rng() % 2);
    m.at(gp(sky::kGpFlipCount))[0] = static_cast<u8>(rng());
    m.at(gp(sky::kGpDmaBusyA))[0] = static_cast<u8>(rng() % 2);
    put32(m, sky::kTexCacheActive, 0);  // no texture cache unless a case sets one up
}

// A raster in the object area with its sky extension at +0x34 (the snapshots' plugin offset): type +32, flags +33,
// format +35, size +12 / +16 / +20, offsets +28 / +30.
u32 put_raster(Machine& m, std::mt19937& rng, u32 va, u32 type) {
    put32(m, va + 0, va);  // its own parent
    put32(m, va + 4, 0);
    put32(m, va + 8, kObj + 0x10000u);  // pixels
    put32(m, va + 12, pick(rng, {640, 512, 256, 128, 64, 32}));
    put32(m, va + 16, pick(rng, {448, 256, 128, 64, 32}));
    put32(m, va + 20, pick(rng, {32, 24, 16, 8, 4}));
    put16(m, va + 28, static_cast<u16>(coin(rng) ? 0 : rng() % 64));
    put16(m, va + 30, static_cast<u16>(coin(rng) ? 0 : rng() % 64));
    m.at(va + 32)[0] = static_cast<u8>(type);
    m.at(va + 33)[0] = static_cast<u8>(rng());
    m.at(va + 35)[0] = static_cast<u8>(rng());
    fill_random(m.at(va + 0x34), 96, rng);  // the extension
    return va;
}

// ======================================================================================================

TEST_CASE("game(render_sky): _rwSkySetRenderState -- every state, every refused value, the whole compare chain") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D6B90u};
    int packets = 0, ok = 0;
    for (int i = 0; i < 1400; ++i) {
        const World w = random_world(rng);
        install(m, rng, w);
        put_shadows(m, rng);
        u64 state = pick(rng, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 20, 21, 29, 30, 0, 31});
        if (coin(rng, 25)) state |= rng64(rng) << 5;  // whole-register compares
        u64 value;
        switch (state) {
        case 1:  // no raster (texture cache off: the raster path is the snapshots' case)
            value = 0;
            break;
        case 2: case 3: case 4: case 7: case 16: case 20: value = rng() % 6; break;
        case 9: case 10: case 11: case 29: value = rng() % 11; break;
        case 30: value = coin(rng) ? rng() % 256 : rng(); break;
        default: value = coin(rng) ? rng() % 3 : rng64(rng); break;
        }
        if (coin(rng, 30)) value |= rng64(rng) << 32;
        const u32 before = get32(m, kSprPtr);
        const HwPair p = run_pair_hw(m, PAIR(fn__rwSkySetRenderState_004d6b90), Args{state, value, rng64(rng), rng64(rng)},
                                     seed_of(i), "_rwSkySetRenderState", check_for(w));
        ok += static_cast<u32>(p.hand.base.v0) == 1 ? 1 : 0;
        // documented: a one-register A+D packet of the matching shadow
        static constexpr struct {
            u64 state;
            s32 shadow;
            u64 reg;
        } kOne[] = {{2, sky::kGpClamp1, 8},  {3, sky::kGpClamp1, 8}, {4, sky::kGpClamp1, 8},   {6, sky::kGpTest1, 71},
                    {9, sky::kGpTex1, 20},   {10, sky::kGpAlpha1, 66}, {11, sky::kGpAlpha1, 66}, {15, sky::kGpFogCol, 61},
                    {29, sky::kGpTest1, 71}, {30, sky::kGpTest1, 71}};
        for (const auto& k : kOne) {
            if (k.state == state && static_cast<u32>(p.hand.base.v0) == 1 && get32(m, kSprPtr) == before + 32) {
                ++packets;
                const Ad a = ad_at(m, before + 16);
                CHECK(a.reg == k.reg);
                CHECK(a.data == get64(m, gp(k.shadow)));
            }
        }
    }
    CHECK(ok > 400);
    CHECK(packets > 60);
}

TEST_CASE("game(render_sky): sub_4F1B30 -- the deferred cache-raster TEX0 / TEX1 / MIPTBP packet") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4F1B30u};
    for (int i = 0; i < 400; ++i) {
        World w = random_world(rng);
        w.spr_fill %= 0x1000u;
        install(m, rng, w);
        put_shadows(m, rng);
        const u32 raster = put_raster(m, rng, kObj + 0x100u, pick(rng, {2, 2, 4, 5, 1}));
        put32(m, sky::kTexCacheCurrent, coin(rng, 6) ? 0 : raster);
        put32(m, sky::kTexCacheMode, coin(rng) ? 0 : 1);
        put32(m, sky::kTexCacheActive, coin(rng) ? 0 : 1);
        run_pair_hw(m, PAIR(fn_sub_4F1B30_004f1b30), Args{rng64(rng), rng64(rng), 0, 0}, seed_of(i), "sub_4F1B30", check_for(w));
    }
}

// A camera: +96 the frame raster, the frustum block at camera + $gp-16972, the view window and frame rows at
// +148..+184 / +292..+384, the 8 doublewords at +32 copied to 0x965330.
u32 put_camera(Machine& m, std::mt19937& rng, u32 type) {
    const u32 cam = kObj + 0x1000u, raster = kObj + 0x2000u;
    for (u32 off = 0; off < 0x200; off += 4) putf(m, cam + off, rfloat(rng));
    put32(m, cam + 20, pick(rng, {1, 2}));  // projection
    put_raster(m, rng, raster, type);
    put32(m, cam + 96, raster);
    put32(m, gp(sky::kGpCamFrustum), 0x200u);
    // the maximum raster: usually large enough
    const u32 max = kObj + 0x3000u;
    put32(m, gp(sky::kGpMaxRaster), max);
    put32(m, max, coin(rng, 8) ? 100 : 1024);
    put32(m, max + 4, coin(rng, 8) ? 100 : 1024);
    put32(m, gp(sky::kGpCamBegun), coin(rng) ? 0 : 1);
    put32(m, gp(sky::kGpRasterUpload), coin(rng, 3) ? 1 : 0);
    put32(m, sky::kTexCacheCurrent, 0);
    return cam;
}

TEST_CASE("game(render_sky): SkyCameraBeginUpdate -- the draw environment, the VU1 constants and the frustum") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D84C0u};
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        w.spr_fill %= 0x1000u;
        install(m, rng, w);
        put_shadows(m, rng);
        const u32 cam = put_camera(m, rng, pick(rng, {5, 5, 2, 1, 4}));
        // a camera texture: resident (ext +23) or not
        m.at(kObj + 0x2000u + 0x34u + 23)[0] = static_cast<u8>(coin(rng, 4) ? 0 : 1);
        run_pair_hw(m, PAIR(fn_SkyCameraBeginUpdate_004d84c0), Args{rng64(rng), cam, rng64(rng), 0}, seed_of(i),
                    "SkyCameraBeginUpdate", check_for(w, {kAllRam}));
    }
}

TEST_CASE("game(render_sky): sub_4D8F40 -- the camera clear (colour / Z strips)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D8F40u};
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        w.spr_fill %= 0x400u;
        w.spr_hi = false;
        install(m, rng, w);
        put_shadows(m, rng);
        const u32 cam = put_camera(m, rng, pick(rng, {5, 2, 1}));
        const u32 raster = kObj + 0x2000u;
        // keep the strip count small enough for one packet in the scratchpad
        put32(m, raster + 12, pick(rng, {0, 1, 31, 32, 33, 64, 100, 200}));
        put32(m, raster + 16, pick(rng, {1, 32, 448}));
        m.at(raster + 0x34u + 23)[0] = static_cast<u8>(coin(rng, 4) ? 0 : 1);
        const u32 colour = kObj + 0x3100u;
        put32(m, colour, rng());
        const u64 flags = coin(rng, 10) ? rng64(rng) : rng() % 4;
        run_pair_hw(m, PAIR(fn_sub_4D8F40_004d8f40), Args{cam, colour, flags, rng64(rng)}, seed_of(i), "sub_4D8F40",
                    check_for(w, {kAllRam}));
    }
}

TEST_CASE("game(render_sky): sub_4E3640 -- the mip-map chain") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4E3640u};
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        w.spr_fill %= 0x400u;
        w.spr_hi = false;
        install(m, rng, w);
        put_shadows(m, rng);
        const u32 raster = put_raster(m, rng, kObj + 0x100u, 4);
        // levels (ext +22 >> 2) 0..6; widths up to 256 (the extra columns of wide levels)
        const u32 levels = coin(rng, 6) ? 0 : 1 + rng() % 6;
        m.at(raster + 0x34u + 22)[0] = static_cast<u8>((levels << 2) | (rng() & 3));
        put32(m, raster + 12, pick(rng, {8, 16, 32, 64, 65, 128, 256}));
        put32(m, raster + 16, pick(rng, {8, 16, 32, 64, 128, 256}));
        // the PSM in TEX0 bits 20..25 of ext +8: 0 / 1 / 0x0A / others
        const u32 psm = pick(rng, {0, 1, 0x0A, 0x13, 0x14, 2});
        put32(m, raster + 0x34u + 8, (get32(m, raster + 0x34u + 8) & ~(0x3Fu << 20)) | (psm << 20));
        run_pair_hw(m, PAIR(fn_sub_4E3640_004e3640), Args{raster, rng64(rng), 0, 0}, seed_of(i), "sub_4E3640", check_for(w));
    }
}

TEST_CASE("game(render_sky): sub_4F0C70 -- the texture-cache PATH3 upload") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4F0C70u};
    int queued = 0;
    for (int i = 0; i < 300; ++i) {
        World w = random_world(rng);
        w.spr_fill %= 0x1000u;
        install(m, rng, w);
        put_shadows(m, rng);
        // the GIF chain tail (sub_4D6250 moves it)
        put32(m, kGifTail, 0x9BA000u + 16u * (rng() % 64));
        const u32 raster = put_raster(m, rng, kObj + 0x100u, pick(rng, {4, 4, 2}));
        const u32 ext = raster + 0x34u;
        const u32 slots = kObj + 0x800u;
        put32(m, sky::kTexCacheSlots, slots);
        for (u32 k = 0; k < 8; ++k) {
            put32(m, slots + 12 * k, k == 3 ? raster : 0);
            put32(m, slots + 12 * k + 4, 0xAF000u + 0x800u * k);
            put32(m, slots + 12 * k + 8, 0x800u);
        }
        put32(m, ext + 88, coin(rng, 6) ? 0 : slots + 36);
        m.at(raster + 33)[0] = static_cast<u8>(coin(rng, 5) ? 0 : 0x40);
        m.at(ext + 54)[0] = static_cast<u8>(coin(rng, 5) ? 0 : 1);
        // the upload packet: {count, ..., 64-byte headers at +16}; header +52 -> the 80-byte block
        const u32 pkt = kObj + 0x1000u, block = kObj + 0x1800u;
        put32(m, raster + 36, pkt);
        const u32 count = 1 + rng() % 3;
        put32(m, pkt, count);
        fill_random(m.at(pkt + 16), 64 * count, rng);
        put32(m, pkt + 16 + 64 * (count - 1) + 52, block);
        fill_random(m.at(block), 80, rng);
        put32(m, ext + 44, 80u + pick(rng, {0, 16, 32, 48, 64, 128, 256, 1024}));
        put32(m, sky::kTexCacheCurrent, coin(rng) ? raster : 0);
        put32(m, sky::kTexCacheMode, coin(rng) ? 0 : 1);
        put32(m, sky::kTexCacheHit0, 3);
        put32(m, sky::kTexCacheHit1, coin(rng) ? 3 : 1);
        const HwPair p = run_pair_hw(m, PAIR(fn_sub_4F0C70_004f0c70), Args{raster, rng64(rng), 0, 0}, seed_of(i),
                                     "sub_4F0C70", check_for(w, {kAllRam}));
        queued += static_cast<u32>(p.hand.base.v0) == 1 ? 1 : 0;
    }
    CHECK(queued > 80);
}

TEST_CASE("game(render_sky): sub_4F1780 -- the texture-cache placement (release / keep / place / evict)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4F1780u};
    int placed = 0;
    for (int i = 0; i < 400; ++i) {
        World w = random_world(rng);
        w.spr_fill %= 0x1000u;
        install(m, rng, w);
        put_shadows(m, rng);
        const u32 nslots = pick(rng, {8, 12, 16});
        put32(m, gp(sky::kGpTexCacheSlots), nslots);
        const u32 slots = kObj + 0x800u;
        put32(m, sky::kTexCacheActive, coin(rng, 8) ? 0 : 1);
        put32(m, sky::kTexCacheSlots, slots);
        put32(m, sky::kTexCacheBase, 0xAF000u);
        put32(m, sky::kTexCacheSize, 0x51000u);
        // a few other rasters in the slots
        for (u32 k = 0; k < nslots; ++k) {
            const u32 other = coin(rng, 3) ? put_raster(m, rng, kObj + 0x4000u + 0x100u * k, 4) : 0;
            if (other) put32(m, other + 0x34u + 88, slots + 12 * k);
            put32(m, slots + 12 * k, other);
            put32(m, slots + 12 * k + 4, 0xAF000u + 0x2000u * k);
            put32(m, slots + 12 * k + 8, 0x2000u);
        }
        const u32 next = pick(rng, {0, 3, 6, 7, 8, nslots - 1, nslots});
        put32(m, sky::kTexCacheNext, next);
        // the eviction hand walks from its end to itself, wrapping at the next-free index: both below it (as the
        // game keeps them; anything else walks off the slot array)
        const bool hand = next > 0 && coin(rng, 3);
        put32(m, sky::kTexCacheHand, hand ? rng() % next : 0xFFFFFFFFu);
        put32(m, sky::kTexCacheHandEnd, hand ? rng() % next : 0xFFFFFFFFu);
        // the raster: resident in slot 7 or not; "locked" (type bit 7) or without pixels, so the upload allocator
        // sub_4EFA00 is not reached (its packets need a real raster: the snapshots' case)
        const u32 raster = put_raster(m, rng, kObj + 0x100u, 4);
        const u32 ext = raster + 0x34u;
        const bool resident = coin(rng);
        m.at(ext + 23)[0] = static_cast<u8>(resident ? 1 : 0);
        put32(m, ext + 88, resident ? slots + 12 * 7 : 0);
        if (resident) put32(m, slots + 12 * 7, raster);
        put32(m, ext + 48, pick(rng, {0x800, 0x2000, 0x4000, 0x100000}));
        const bool locked = coin(rng);
        m.at(raster + 32)[0] = static_cast<u8>(4 | (locked ? 0x80 : 0));
        put32(m, raster + 4, locked && coin(rng) ? kObj + 0x10000u : 0);
        put32(m, sky::kTexCacheCurrent, coin(rng) ? raster : 0);
        const u32 mode = coin(rng) ? 0 : (coin(rng) ? 1 : rng());
        const HwPair p = run_pair_hw(m, PAIR(fn_sub_4F1780_004f1780), Args{raster, mode, rng64(rng), 0}, seed_of(i),
                                     "sub_4F1780", check_for(w, {kAllRam}));
        placed += static_cast<u32>(p.hand.base.v0) == 1 ? 1 : 0;
    }
    CHECK(placed > 100);
}

// An RxPS2AllPipeData (as test_render_rw2.cpp): +4 material private {+20 VIF offset, +24 VU1 code array}, +28 spExtra,
// +40 transType, +41 primType, +48 resEntry reference, +60 surface properties, +68 material colour.
u32 put_pipe_data(Machine& m, std::mt19937& rng) {
    const u32 pipe = kObj + 0x100u, mat = kObj + 0x300u, code = kObj + 0x340u;
    const u32 ref = kObj + 0x380u, res = kObj + 0x600u, surf = kObj + 0x3C0u;
    put32(m, pipe + 4, mat);
    put32(m, mat + 20, rng() % 16);
    put32(m, mat + 24, code);
    for (u32 k = 0; k < 8; ++k) put32(m, code + 4 * k, 0x5CD000u + 0x100u * (rng() % 8));
    putf(m, pipe + 28, static_cast<float>(rng() % 100) / 10.0f);
    m.at(pipe + 40)[0] = static_cast<u8>(rng() & 0x3Fu);
    m.at(pipe + 41)[0] = static_cast<u8>(pick(rng, {3, 4, 1, 2}));
    put32(m, pipe + 48, ref);
    put32(m, ref, res);
    put32(m, res + 24, rng() % 4);  // reference count, uses this frame
    put32(m, res + 28, rng() % 2);
    put32(m, res + 32, 0x9D0000u + 16u * (rng() % 256));
    put32(m, pipe + 60, surf);
    for (u32 k = 0; k < 3; ++k) putf(m, surf + 4 * k, static_cast<float>(rng() % 100) / 99.0f);
    put32(m, pipe + 68, rng());
    return pipe;
}

TEST_CASE("game(render_sky): the PDS 2D bridges and the Im3D bridge") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46FDD0u};
    struct Entry {
        const char* name;
        Fn hand, recomp;
    };
    const Entry entries[] = {{"sub_46FDD0", PAIR(fn_sub_46FDD0_0046fdd0)},
                             {"RpPDS_G3_2DFont_PS2AllBridgeCallBack", PAIR(fn_RpPDS_G3_2DFont_PS2AllBridgeCallBack_004709e0)},
                             {"sub_471470", PAIR(fn_sub_471470_00471470)},
                             {"sub_4A2790", PAIR(fn_sub_4A2790_004a2790)}};
    for (const Entry& e : entries) {
        int resident = 0;
        for (int i = 0; i < 150; ++i) {
            World w = random_world(rng);
            w.spr_hi = false;
            w.spr_fill %= 0x1000u;
            install(m, rng, w);
            put_shadows(m, rng);
            const u32 pipe = put_pipe_data(m, rng);
            const u32 cam = kObj + 0x2000u;
            put32(m, sky::kPdsCamera, cam);
            put32(m, cam + 20, pick(rng, {1, 1, 2}));
            put32(m, gp(sky::kGpCullMode), coin(rng) ? 0 : 1);
            put32(m, gp(sky::kGpFogEnabled), coin(rng) ? 0 : 1);
            put32(m, gp(sky::kGpCamProjection), pick(rng, {1, 2, 3}));
            put32(m, gp(sky::kGpClipLo), rng());
            put32(m, gp(sky::kGpResidentProgram), coin(rng) ? get32(m, kObj + 0x340u) : 0);
            const u32 refs = get32(m, kObj + 0x600u + 24);
            resident += get32(m, gp(sky::kGpResidentProgram)) != 0 ? 1 : 0;
            run_pair_hw(m, e.hand, e.recomp, Args{pipe, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i), e.name,
                        check_for(w, {kAllRam}));
            // documented: the resEntry's use word is set to 1 and then counted (2: _rwDMAAddPURef never runs from
            // these bridges), its reference count incremented
            CHECK(get32(m, kObj + 0x600u + 28) == 2);
            CHECK(get32(m, kObj + 0x600u + 24) == refs + 1);
        }
        INFO(e.name);
        CHECK(resident > 30);
    }
}

// --- real driver state ------------------------------------------------------------------------------------------
TEST_CASE("game(render_sky): the funnel, the camera begin / clear and the texture cache on the snapshots' state") {
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
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        std::mt19937 rng{0x5EED3u};
        fill_random(m.mem.scratchpad(), 0x4000, rng);
        m.at(gp(-17252))[0] = 0;  // no pending swap: _rwDMAWaitQueue returns at once (render_rw2 tests it)
        const u32 alloc = get32(m, kAlloc);
        const u32 lo = (std::min(get32(m, kQWrite), alloc) & ~0xFFFu) - 0x1000u;
        const u32 camera = get32(m, gp(sky::kGpCamera));
        const u32 slots = get32(m, sky::kTexCacheSlots);
        const u32 nslots = get32(m, gp(sky::kGpTexCacheSlots));
        std::vector<u32> rasters;
        for (u32 k = 0; k < nslots && slots != 0; ++k)
            if (const u32 r = get32(m, slots + 12 * k)) rasters.push_back(r);
        World w;
        for (int i = 0; i < 160; ++i) {
            w.chcr_busy = i % 5 == 0;
            w.stat_polls = i % 7 == 0 ? 2 : 0;
            HwCheck hw = check_for(w, {{lo, 0x60000u}, kAllRam});
            switch (i % 8) {
            case 0:  // the texture raster: a resident one, another one, none
            {
                u32 r = 0;
                if (!rasters.empty() && !coin(rng, 4)) r = rasters[rng() % rasters.size()];
                else if (coin(rng)) r = get32(m, gp(sky::kGpRaster));
                run_pair_hw(m, PAIR(fn__rwSkySetRenderState_004d6b90), Args{1, r, 0, 0}, seed_of(i), "raster", hw);
                break;
            }
            case 1:
            case 2:  // the other states as the game sets them
            {
                const u64 state = pick(rng, {2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 20, 29, 30});
                const u64 value = state == 15 ? rng() : state == 30 ? rng() % 256 : rng() % 9;
                run_pair_hw(m, PAIR(fn__rwSkySetRenderState_004d6b90), Args{state, value, 0, 0}, seed_of(i), "state", hw);
                break;
            }
            case 3:
                if (camera != 0)
                    run_pair_hw(m, PAIR(fn_SkyCameraBeginUpdate_004d84c0), Args{0, camera, 0, 0}, seed_of(i), "camera begin", hw);
                break;
            case 4:
                if (camera != 0) {
                    const u32 colour = kObj + 0x100u;
                    put32(m, colour, rng());
                    run_pair_hw(m, PAIR(fn_sub_4D8F40_004d8f40), Args{camera, colour, rng() % 4, 0}, seed_of(i), "camera clear", hw);
                }
                break;
            case 5:
                run_pair_hw(m, PAIR(fn_sub_4F1B30_004f1b30), Args{}, seed_of(i), "sub_4F1B30", hw);
                break;
            case 6:  // keep a resident raster (mode 1) / release it (mode 0) / place a released one
                if (!rasters.empty()) {
                    const u32 r = rasters[rng() % rasters.size()];
                    run_pair_hw(m, PAIR(fn_sub_4F1780_004f1780), Args{r, rng() % 2, 0, 0}, seed_of(i), "sub_4F1780", hw);
                }
                break;
            default:  // the mip-map chain of a cached raster
                if (!rasters.empty()) {
                    const u32 r = rasters[rng() % rasters.size()];
                    run_pair_hw(m, PAIR(fn_sub_4E3640_004e3640), Args{r, 0, 0, 0}, seed_of(i), "sub_4E3640", hw);
                }
                break;
            }
            ++ran;
        }
    }
    MESSAGE("snapshot pairs: " << ran);
}

}  // namespace

#else

TEST_CASE("game(render_sky): replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game was configured without P3FES_RT_EXEC_ELF; nothing to compare");
}

#endif
