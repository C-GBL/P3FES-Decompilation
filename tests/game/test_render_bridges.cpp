// Phase 5 pair tests for the render_bridges slice (game/src/render/bridges.cpp): the MatFX material bridges of the
// PS2 driver (bump, environment, bump + environment, dual, UV transform, dual + UV transform) and the partitioned
// skin's object set-up callback (docs/ANALYSIS/22_rendering.md section 3). Each hand-written function and the
// recompiled body it replaces run on identical guest machines built from random RenderWare records (the atomic, its
// frame and camera, geometry and mesh header, material and its MatFX extension with both effect slots, base and effect
// textures with rasters and their sky extensions and cache slots, effect frames for the bump / environment matrices,
// UV matrices or none, material pipeline private data and VU1 code array, resEntries and the reference ring, the GS
// shadows and camera words, skins / hierarchies / partitions) on pair_harness.h's scripted hardware bus, with the DMA
// packet layer's state (no packet / open VIF packet / open cnt / open GIF packet; a nearly full scratchpad half).
//
// Per pair (as test_render_mesh.cpp): EVERY general register in 128 bits, HI/LO, all FPU registers, ACC, FCR31 and
// the VU0 state at the return; the whole register file and the cycle count at EVERY check point (callees' entry
// check points included: what each call hands over); the bus access log; the scratchpad; the world region, the gp
// window, the RW / skin globals, the packet templates, the texture cache globals, the DMA buffer window and the
// whole stack window (live and dead: the frames hold the original spills and frame records); cycles, check points,
// syscalls, traps. FPRs, ACC and VU0 start random. Host-side rules restate what the packets must carry (the UV
// matrix rows, the GS register numbers of the second pass, the partition record of skinSplitObjectSetupCB).
#include "pair_harness.h"

#include "p3fes/game/bridges.h"
#include "p3fes/game/mesh.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
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
P3FES_DECL_PAIR(fn_matfxBridgeUvTransform_00472270)
P3FES_DECL_PAIR(fn_matfxBridgeBumpMap_0046c5b0)
P3FES_DECL_PAIR(fn_matfxBridgeDual_0046e170)
P3FES_DECL_PAIR(fn_matfxBridgeEnvMap_0046cd90)
P3FES_DECL_PAIR(fn_matfxBridgeDualUvTransform_00472970)
P3FES_DECL_PAIR(fn_matfxBridgeBumpEnvMap_0046d6f0)
P3FES_DECL_PAIR(fn_skinSplitObjectSetupCB_004718a0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace mesh = p3fes::game::mesh;
namespace br = p3fes::game::bridges;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout ------------------------------------------------------------------------------------------
constexpr u32 kGpBase = 0x007D2CF0u;
constexpr u32 gpv(s32 off) { return kGpBase + static_cast<u32>(off); }
constexpr u32 kWorld = 0x01900000u;  // the random RenderWare records of a case
constexpr u32 kWorldLen = 0x10000u;
constexpr u32 kGpWindow = gpv(-21000);  // the bump scale words sit at gp-20928 / gp-20924
constexpr u32 kGpWindowLen = 4300;
constexpr u32 kStackLo = kSp - kDeadStack;
constexpr u32 kStackLen = kDeadStack + 0x100;

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region> kBase = {{kWorld, kWorldLen}, {kGpWindow, kGpWindowLen}};

// --- guest RAM helpers -------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u64 r64(const Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.mem.main_ram() + va, 8);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
u64 rng64(std::mt19937& rng) {
    const u64 hi = rng();
    return (hi << 32) | rng();
}
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 10) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng();
    case 3: return rng() & 0x807FFFFFu;
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 4001) - 2000) / 97.0f);
    }
}
void fill_floats(Machine& m, u32 va, u32 count, std::mt19937& rng) {
    for (u32 i = 0; i < count; ++i) w32(m, va + 4 * i, rand_float(rng));
}
// Register-file seed of a pair from the case index (draws inside an argument list would be unsequenced).
u32 seed_of(u32 i) { return 0x9E3779B9u * (i + 1); }

// --- one run with the full machine state ---------------------------------------------------------------------
struct Snap {
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0;
    std::array<u32, 32> fpr{};
    u32 acc = 0, fcr31 = 0;
    std::vector<u32> vu0;
    u64 cycles = 0;
    int checks = 0, syscalls = 0, traps = 0;
    std::vector<RegSnap> snaps;
    std::vector<ScriptedBus::Access> bus;
    std::vector<u8> spr, stack;
    std::vector<std::vector<u8>> regions;
};

std::vector<u32> vu0_words(const VU0State& v) {
    std::vector<u32> out;
    for (const auto& r : v.vf) out.insert(out.end(), std::begin(r), std::end(r));
    for (u16 x : v.vi) out.push_back(x);
    out.insert(out.end(), std::begin(v.acc), std::end(v.acc));
    for (u32 x : {v.q, v.p, v.i, v.r, v.status, v.mac, v.clip, v.tpc, v.cmsar0}) out.push_back(x);
    return out;
}

// The scripted hardware of a case: register values and per-register read scripts.
struct Hw {
    std::map<u32, u64> regs;
    std::map<u32, std::vector<u64>> reads;
    std::map<unsigned, u64> gpr_in;  // set after the randomised context
};

Snap run_full(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Region>& regions, const Hw& hw) {
    HwHooks hooks;
    hooks.bus_.regs = hw.regs;
    hooks.bus_.reads = hw.reads;
    hooks.record_regs = true;
    rt_test::HooksScope scope{&hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (u32& f : m.ctx.fpr) f = rand_float(rng);
    m.ctx.acc = rand_float(rng);
    m.ctx.fcr31 = rng() & 0x0183F07Fu;
    m.ctx.hi.u64[0] = rng64(rng);
    m.ctx.hi.u64[1] = rng64(rng);
    m.ctx.lo.u64[0] = rng64(rng);
    m.ctx.lo.u64[1] = rng64(rng);
    for (unsigned r = 1; r < 32; ++r)
        for (u32& x : m.ctx.vu0.vf[r]) x = rand_float(rng);
    for (u32& x : m.ctx.vu0.acc) x = rand_float(rng);
    m.ctx.vu0.status = rng() & 0xFFFu;
    m.ctx.vu0.mac = rng() & 0xFFFFu;
    for (const auto& [r, v] : hw.gpr_in) m.ctx.gpr[r].u64[0] = v;
    const u64 c0 = m.ctx.cycles;
    fn(m.ctx);
    Snap s;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = m.ctx.gpr[r];
    s.hi = m.ctx.hi;
    s.lo = m.ctx.lo;
    s.sa = m.ctx.sa;
    std::copy(std::begin(m.ctx.fpr), std::end(m.ctx.fpr), s.fpr.begin());
    s.acc = m.ctx.acc;
    s.fcr31 = m.ctx.fcr31;
    s.vu0 = vu0_words(m.ctx.vu0);
    s.cycles = m.ctx.cycles - c0;
    s.checks = hooks.checks;
    s.syscalls = hooks.syscalls;
    s.traps = hooks.traps;
    s.snaps = std::move(hooks.snaps);
    s.bus = std::move(hooks.bus_.log);
    s.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    s.stack = m.bytes(kStackLo, kStackLen);
    for (const Region& r : regions) s.regions.push_back(m.bytes(r.va, r.len));
    std::memset(m.at(kStackLo), 0, kDeadStack);
    return s;
}

int g_pairs = 0;

std::size_t first_diff(const std::vector<u8>& a, const std::vector<u8>& b) {
    std::size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) ++i;
    return i;
}

// Runs hand and recomp from the same machine state (the scratchpad and every region restored in between) and
// requires identical results everywhere. After the pair the recompiled run's output is in place.
std::pair<Snap, Snap> pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                           const std::vector<Region>& extra = {}, const Hw& hw = {}) {
    std::vector<Region> regions = kBase;
    regions.insert(regions.end(), extra.begin(), extra.end());
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    std::vector<std::vector<u8>> before;
    for (const Region& r : regions) before.push_back(m.bytes(r.va, r.len));
    const std::string label = std::string(what) + " seed " + std::to_string(seed);
    INFO(label);
    Snap h;
    try {
        h = run_full(m, hand, args, seed, regions, hw);
    } catch (const rt_test::FatalEvent& e) {
        MESSAGE("the hand run of " << label << " stopped at pc " << hex64(e.pc) << " ra "
                                    << hex64(e.ctx ? e.ctx->gpr[GPR_RA].u64[0] : 0) << ": " << e.what);
        throw;
    }
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    Snap r = run_full(m, recomp, args, seed, regions, hw);
    ++g_pairs;
    for (unsigned i = 1; i < 32; ++i) {
        INFO("gpr " << i << " hand " << hex64(h.gpr[i].u64[1]) << ":" << hex64(h.gpr[i].u64[0]) << " recomp "
                    << hex64(r.gpr[i].u64[1]) << ":" << hex64(r.gpr[i].u64[0]));
        CHECK(same_u128(h.gpr[i], r.gpr[i]));
    }
    CHECK(same_u128(h.hi, r.hi));
    CHECK(same_u128(h.lo, r.lo));
    CHECK(h.sa == r.sa);
    for (unsigned i = 0; i < 32; ++i) {
        INFO("fpr " << i);
        CHECK(h.fpr[i] == r.fpr[i]);
    }
    CHECK(h.acc == r.acc);
    CHECK(h.fcr31 == r.fcr31);
    CHECK(h.vu0 == r.vu0);
    CHECK(h.cycles == r.cycles);
    CHECK(h.checks == r.checks);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.traps == r.traps);
    CHECK(h.snaps.size() == r.snaps.size());
    for (std::size_t i = 0; i < std::min(h.snaps.size(), r.snaps.size()); ++i) {
        const RegSnap& a = h.snaps[i];
        const RegSnap& b = r.snaps[i];
        int bad = -1;
        for (unsigned g = 1; g < 32 && bad < 0; ++g)
            if (!same_u128(a.gpr[g], b.gpr[g])) bad = static_cast<int>(g);
        if (bad < 0 && !same_u128(a.hi, b.hi)) bad = 32;
        if (bad < 0 && !same_u128(a.lo, b.lo)) bad = 33;
        if (bad < 0 && (a.sa != b.sa || a.fcr31 != b.fcr31)) bad = 34;
        if (bad < 0 && a.fpr != b.fpr) bad = 35;
        if (bad < 0 && a.cycles != b.cycles) bad = 36;
        if (bad >= 0) {
            const u128 x = bad < 32 ? a.gpr[bad] : bad == 32 ? a.hi : a.lo;
            const u128 y = bad < 32 ? b.gpr[bad] : bad == 32 ? b.hi : b.lo;
            INFO("check point " << i << " (cycles " << a.cycles << " / " << b.cycles << "): first differing register "
                                << bad << ": hand " << hex64(x.u64[1]) << ":" << hex64(x.u64[0]) << " recomp "
                                << hex64(y.u64[1]) << ":" << hex64(y.u64[0]));
            CHECK(false);
            break;
        }
    }
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto& a = h.bus[i];
        const auto& b = r.bus[i];
        if (a.write != b.write || a.bits != b.bits || a.pa != b.pa || a.lo != b.lo || a.hi != b.hi) {
            INFO("bus access " << i << ": hand " << hex64(a.pa) << "=" << hex64(a.lo) << " recomp " << hex64(b.pa) << "="
                               << hex64(b.lo));
            CHECK(false);
            break;
        }
    }
    {
        const std::size_t f = first_diff(h.spr, r.spr);
        INFO("first differing scratchpad byte " << hex64(f));
        CHECK(f == h.spr.size());
    }
    {
        const std::size_t f = first_diff(h.stack, r.stack);
        INFO("stack window: first differing byte at " << hex64(kStackLo + f));
        CHECK(f == h.stack.size());
    }
    for (std::size_t i = 0; i < regions.size(); ++i) {
        const std::size_t f = first_diff(h.regions[i], r.regions[i]);
        INFO("region " << hex64(regions[i].va) << ": first differing byte at " << hex64(regions[i].va + f));
        CHECK(f == h.regions[i].size());
    }
    return {std::move(h), std::move(r)};
}

u64 gpr_of(const Snap& s, unsigned r) { return s.gpr[r].u64[0]; }

// =========================================================================================================
// The worlds (as test_render_mesh.cpp builds them)
// =========================================================================================================
constexpr u32 kPipe = kWorld + 0x0000, kHeader = kWorld + 0x0100, kAtomic = kWorld + 0x0200, kGeometry = kWorld + 0x0300;
constexpr u32 kResArray = kWorld + 0x0400, kResEntry = kWorld + 0x0500, kAtomFrame = kWorld + 0x0600;
constexpr u32 kRoot = kWorld + 0x0700, kMatRef = kWorld + 0x0800, kObjMatrix = kWorld + 0x0840, kCamera = kWorld + 0x0900;
constexpr u32 kWorldRec = kWorld + 0x0C00, kLights = kWorld + 0x1000, kLightFrames = kWorld + 0x1400;
constexpr u32 kTies = kWorld + 0x1C00, kSectors = kWorld + 0x1D00, kLightTies = kWorld + 0x2000;
constexpr u32 kLightBlock = kWorld + 0x3000, kInvRec = kWorld + 0x4000;
constexpr u32 kEffectFrames = kWorld + 0x4400;  // two frames for the MatFX bump / environment matrices
constexpr u32 kRwGlobals = mesh::kRwGlobals;
constexpr u32 kFrustumOff = 0x40;
constexpr u32 kTplLo = 0x965800u, kTplHi = 0x965A40u;
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;
constexpr u32 kType = gpv(-17212), kFixup = gpv(-17208), kCntTag = gpv(-17204), kPktStart = gpv(-17196);
constexpr u32 kQWrite = gpv(-17192), kQLimit = gpv(-17188), kAlloc = gpv(-17184), kHalfEnd = gpv(-17180);
constexpr u32 kHalfSize = gpv(-17164), kHalf0 = gpv(-17160), kHalf1 = gpv(-17156), kGifTail = gpv(-17152);
constexpr u32 kDmaPtr = gpv(-17128), kSprBase = gpv(-17124);
constexpr u32 kD8Chcr = 0x1000D000u, kDStat = 0x1000E010u;
constexpr u32 kSkinGlobals = 0x0095DE00u;
constexpr u32 kEffectCache = 0x0095C400u;  // matfxEffectMatrix's cached inverse / product matrix at 0x95C460
constexpr u32 kTexCache = 0x0077F200u;
constexpr u32 kClutWords = 0x009649F0u;
constexpr u32 kRaster = kWorld + 0x9000, kRaster2 = kWorld + 0x9400, kSlots = kWorld + 0x9800;
constexpr u32 kTexture = kWorld + 0xB000, kTexture2 = kWorld + 0xB100, kMatPvt = kWorld + 0xC800, kCodeArray = kWorld + 0xC900;
constexpr u32 kMaterial = kWorld + 0xCA00, kRing = kWorld + 0xD000, kExt = kWorld + 0xC000, kUvMats = kWorld + 0xC200;
constexpr u32 kResEntries2 = kWorld + 0xD400;
constexpr u32 kLeafCb = 0x4A2BA0u, kNonLeafCb = 0x1F1C50u;
const std::vector<Region> kRegBridge = {{kTplLo, kTplHi - kTplLo}, {kWinLo, kWinLen},     {kTexCache, 0x40},
                                        {kClutWords, 0x180},       {kRwGlobals, 0x200},   {kSkinGlobals, 0x60},
                                        {kEffectCache, 0x100}};

u32 light_at(u32 i) { return kLights + 0x80 * i; }

void put_frame(Machine& m, u32 frame, std::mt19937& rng) {
    fill_floats(m, frame + 80, 16, rng);
    w32(m, frame + 80 + 12, chance(rng, 40) ? 3u : rng() & 0x20003u);
    w32(m, frame + 160, kRoot);
}

void put_light(Machine& m, u32 i, std::mt19937& rng) {
    const u32 l = light_at(i);
    fill_random(m, l, 0x80, rng);
    w8(m, l + 1, static_cast<u8>(chance(rng, 85) ? pick(rng, {1, 2, 0x80, 0x81, 0x82, 0}) : rng()));
    w8(m, l + 2, static_cast<u8>(chance(rng, 75) ? (rng() | 1u) : (rng() & ~1u)));
    fill_floats(m, l + 20, 6, rng);
    fill_floats(m, l + 40, 1, rng);
    const u32 frame = kLightFrames + 0xC0 * i;
    put_frame(m, frame, rng);
    w32(m, l + 4, chance(rng, 90) ? frame : 0);
}

void put_light_block(Machine& m, std::mt19937& rng) {
    fill_random(m, kLightBlock, 0x800, rng);
    w32(m, gpv(mesh::kGpLightPtr), kLightBlock + 16 * (rng() % 8));
    w32(m, gpv(mesh::kGpLightCount), chance(rng, 40) ? 0u : pick(rng, {1, 4, 6, 50, 121, 122, 123, 124, 125, 0xFFFFFFFFu}));
    fill_floats(m, kInvRec, 24, rng);
}

struct AtomWorld {
    u32 meshes = 1;
    bool morphing = false;
};
AtomWorld put_atomic_world(Machine& m, std::mt19937& rng) {
    AtomWorld a;
    fill_random(m, kWorld, 0x5000, rng);
    fill_random(m, kRwGlobals, 0x200, rng);
    fill_random(m, kEffectCache, 0x100, rng);
    put_light_block(m, rng);
    w32(m, kRoot, rng());
    w8(m, kRoot + 3, static_cast<u8>(rng() & ~3u));
    // camera: +4 frame, +32 view matrix, +128 near / +132 far, the frustum planes
    w32(m, kRwGlobals + 0, kCamera);
    fill_floats(m, kCamera + 32, 16, rng);
    fill_floats(m, kCamera + 128, 2, rng);
    w32(m, kCamera + 4, kEffectFrames + 0x180);
    put_frame(m, kEffectFrames + 0x180, rng);
    w32(m, gpv(mesh::kGpCamFrustum), kFrustumOff);
    for (u32 p = 0; p < 6; ++p) fill_floats(m, kCamera + kFrustumOff + 96 + 20 * p, 4, rng);
    m.at(gpv(mesh::kGpCamFlags))[0] = static_cast<u8>(rng());
    a.meshes = 1 + rng() % 4;
    a.morphing = chance(rng, 25);
    w32(m, kPipe + mesh::pd::kObject, kAtomic);
    w32(m, kAtomic + 4, kAtomFrame);
    put_frame(m, kAtomFrame, rng);
    w32(m, kAtomic + 24, kGeometry);
    w8(m, kAtomic + 0, static_cast<u8>(chance(rng, 20) ? 255 : rng() % 8));  // matfxEffectMatrix: 255 = no atomic frame
    w8(m, kAtomic + 3, static_cast<u8>(rng() & ~1u));
    w32(m, kAtomic + 76, rng() & ~2u);
    fill_floats(m, kAtomic + 44, 4, rng);
    fill_floats(m, kAtomic + 88, 2, rng);
    w32(m, kGeometry + 8, chance(rng, 80) ? (rng() & 0x00FF00FFu) : rng());
    w32(m, kGeometry + 24, a.morphing ? 2 + rng() % 2 : 1);
    w16(m, kGeometry + 12, chance(rng, 60) ? 0 : static_cast<u16>(rng()));
    w32(m, kGeometry + 84, kHeader);
    w32(m, kHeader, chance(rng, 80) ? pick(rng, {0, 1, 2, 4, 8, 0x10}) : rng());
    w16(m, kHeader + 4, static_cast<u16>(a.meshes));
    w32(m, kHeader + 12, 0);
    w32(m, kHeader + 24, kWorld + 0x4800);
    const u32 goff = 0x40 + 4 * (rng() % 4), aoff = 0x70 + 4 * (rng() % 4);
    w32(m, gpv(mesh::kGpGeomResEntries), goff);
    w32(m, gpv(mesh::kGpAtomResEntries), aoff);
    w32(m, kGeometry + goff, kResArray);
    w32(m, kAtomic + aoff, kResArray);
    w32(m, kResArray, a.meshes);
    w32(m, kResArray + 4, chance(rng, 30) ? 0 : kResEntry);
    w32(m, kMatRef, kObjMatrix);
    w32(m, kRwGlobals + 4, kWorldRec);
    w16(m, kRwGlobals + 10, static_cast<u16>(rng()));
    const u32 nworld = rng() % 4;
    u32 prev = kWorldRec + 60;
    for (u32 i = 0; i < 8; ++i) put_light(m, i, rng);
    for (u32 i = 0; i < nworld; ++i) {
        w32(m, prev, light_at(i) + 52);
        prev = light_at(i) + 52;
    }
    w32(m, prev, kWorldRec + 60);
    const u32 nties = rng() % 4;
    prev = kAtomic + 100;
    u32 lt = 0;
    for (u32 t = 0; t < nties; ++t) {
        const u32 tie = kTies + 0x10 * t, sector = kSectors + 0x80 * t;
        w32(m, prev, tie);
        prev = tie;
        w32(m, tie + 8, sector);
        const u32 nl = rng() % 4;
        u32 lprev = sector + 64;
        for (u32 k = 0; k < nl; ++k) {
            const u32 ltie = kLightTies + 0x10 * (lt++);
            w32(m, lprev, ltie);
            lprev = ltie;
            w32(m, ltie + 8, chance(rng, 10) ? 0 : light_at(rng() % 8));
        }
        w32(m, lprev, sector + 64);
    }
    w32(m, prev, kAtomic + 100);
    for (u32 i = 0; i < 8; ++i)
        if (chance(rng, 20)) w16(m, light_at(i) + 60, static_cast<u16>(r32(m, kRwGlobals + 8) >> 16) + 1);
    return a;
}

// A random RW DMA state (no packet / open VIF / open cnt / open GIF; the scratchpad half sometimes nearly full).
Hw put_dma(Machine& m, std::mt19937& rng) {
    fill_random(m, kWinLo, kWinLen, rng);
    w32(m, kHalfSize, 0x13F400u);
    w32(m, kHalf0, 0x9B0A00u);
    w32(m, kHalf1, 0xAEFE00u);
    w32(m, kHalfEnd, 0xAEFE00u);
    w32(m, kQWrite, 0x9B0A10u + 8u * (rng() % 12));
    w32(m, kQLimit, 0x9B0A78u);
    const bool hi = chance(rng, 50);
    const u32 spr_base = hi ? 0x70002000u : 0x70000000u;
    const u32 fill = chance(rng, 30) ? 16u * (rng() % 256) : 8192u - 16u * (1 + rng() % 64);
    w32(m, kSprBase, spr_base);
    const u32 dma = 0x9C0000u + 16u * (rng() % 1024);
    w32(m, kDmaPtr, dma);
    w32(m, kCntTag, 0);
    w32(m, kGifTail, chance(rng, 30) ? 0x9BA000u + 16u * (rng() % 64) : 0);
    switch (rng() % 7) {
    case 0:
        w32(m, kType, 0);
        w32(m, gpv(mesh::kGpSprWrite), chance(rng, 50) ? 0 : spr_base + fill);
        w32(m, kAlloc, dma + 16u * (rng() % 64));
        w32(m, kPktStart, 0);
        break;
    case 1:
    case 2:
    case 3:
        w32(m, kType, 0x1101u);
        w32(m, gpv(mesh::kGpSprWrite), spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
        break;
    case 4:
    case 5:
        w32(m, kType, 0x80001101u);
        w32(m, gpv(mesh::kGpSprWrite), spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
        w32(m, kCntTag, dma - 16u * (1 + rng() % 32));
        break;
    default:
        w32(m, kType, 0x102u);
        w32(m, gpv(mesh::kGpSprWrite), spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
        break;
    }
    w32(m, kFixup, chance(rng, 25) ? spr_base + 16u * (rng() % 64) : 0);
    fill_random(m, kTplLo, kTplHi - kTplLo, rng);
    Hw hw;
    hw.regs[kD8Chcr] = chance(rng, 50) ? 0x100u : 0u;
    const u32 polls = pick(rng, {0, 0, 1, 3});
    if (polls) {
        std::vector<u64> stat(polls, 0);
        stat.push_back(0x100u);
        hw.reads[kDStat] = stat;
    }
    return hw;
}

// A raster with its sky extension (offset shared by every raster of the case) and its cache slot.
void put_raster(Machine& m, std::mt19937& rng, u32 raster, u32 ext) {
    fill_random(m, raster, 0x200, rng);
    w32(m, raster + 0, chance(rng, 50) ? raster : rng());
    w32(m, raster + 4, chance(rng, 90) ? kWorld + 0xA000 : 0);
    w32(m, raster + 20, chance(rng, 70) ? rng() % 12 : rng());  // width log: < 9 for both -> last raster = -1
    w8(m, raster + 32, static_cast<u8>(chance(rng, 80) ? (rng() & 0x7Fu) : rng()));
    w8(m, raster + 35, static_cast<u8>(chance(rng, 70) ? pick(rng, {0, 1, 5, 6, 0x16, 0x21, 0x25}) : rng()));
    w32(m, raster + ext + 88, chance(rng, 75) ? kSlots + 12 * (rng() % 16) : 0);
    w32(m, raster + ext + 16, rng() % 0x4000);
    w8(m, raster + ext + 23, static_cast<u8>(chance(rng, 50) ? 0 : rng()));
}

void put_texture_cache(Machine& m, std::mt19937& rng) {
    fill_random(m, kSlots, 0x100, rng);
    fill_random(m, kTexCache, 0x40, rng);
    fill_random(m, kClutWords, 0x180, rng);
    const u32 ext = 0x40 + 4 * (rng() % 8);
    w32(m, gpv(mesh::kGpRasterExt), ext);
    put_raster(m, rng, kRaster, ext);
    put_raster(m, rng, kRaster2, ext);
    w32(m, kTexCache + 0x00, chance(rng, 80) ? 1u : 0u);
    w32(m, kTexCache + 0x14, kSlots);
    w32(m, kTexCache + 0x20, chance(rng, 50) ? kLeafCb : kNonLeafCb);
    w32(m, kTexCache + 0x24, chance(rng, 40) ? kRaster : rng());
    w32(m, kTexCache + 0x28, rng() % 2);
    w32(m, gpv(-16856), chance(rng, 50) ? 0 : rng());
    w32(m, gpv(-17016), rng());
    w64(m, gpv(mesh::kGpTex1), rng64(rng));
}

u32 texture_word(std::mt19937& rng) {
    return chance(rng, 70) ? (rng() & 0xFFFFu) | (pick(rng, {0, 1, 3}) << 8) | (pick(rng, {0, 1, 3}) << 12) : rng();
}

// The material side of a mesh (as test_render_mesh.cpp) plus the second texture.
void put_material_world(Machine& m, std::mt19937& rng, u32 meshes) {
    fill_random(m, kWorld + 0xB000, 0x3000, rng);
    put_texture_cache(m, rng);
    w32(m, kTexture, kRaster);
    w32(m, kTexture + 80, texture_word(rng));
    w32(m, kTexture2, kRaster2);
    w32(m, kTexture2 + 80, texture_word(rng));
    w32(m, kMatPvt + 20, rng() & 0x3FFu);
    w32(m, kMatPvt + 24, kCodeArray);
    for (u32 k = 0; k < 8; ++k) w32(m, kCodeArray + 4 * k, chance(rng, 80) ? 0x5CD000u + 0x100 * k : rng());
    w32(m, gpv(mesh::kGpResidentProgram), chance(rng, 40) ? 0x5CD000u + 0x100 * (rng() % 8) : rng());
    w32(m, kMaterial + 0, chance(rng, 75) ? kTexture : 0);
    w32(m, kMaterial + 4, chance(rng, 50) ? (rng() | 0xFF000000u) : rng());
    w32(m, kMaterial + 8, 0);
    fill_floats(m, kMaterial + 12, 3, rng);
    for (u32 i = 0; i < meshes; ++i) w32(m, kHeader + 16 + 12 * i + 8, kMaterial);
    for (u32 i = 0; i < 4; ++i) {
        const u32 r = kResEntries2 + 0x40 * i;
        w32(m, kResArray + 4 + 4 * i, r);
        w32(m, r + 24, rng() % 4);
        w32(m, r + 28, chance(rng, 40) ? 0 : rng() % 4);
        w32(m, r + 32, kWorld + 0xE000 + 0x100 * i);
    }
    w64(m, gpv(mesh::kGpRenderFlags), rng64(rng));
    w64(m, gpv(mesh::kGpTest), rng64(rng));
    w64(m, gpv(mesh::kGpClamp), rng64(rng));
    w64(m, gpv(br::kGpFogColour), rng64(rng));
    w64(m, gpv(br::kGpZbuf), rng64(rng));
    w64(m, gpv(br::kGpAlpha), rng64(rng));
    w32(m, gpv(mesh::kGpCullMode), chance(rng, 50) ? 0 : 1);
    w32(m, gpv(mesh::kGpFogEnabled), chance(rng, 50) ? 0 : 1);
    w32(m, gpv(mesh::kGpCamProjection), chance(rng, 50) ? 3 : rng() % 3);
    w32(m, gpv(mesh::kGpClipLo), rng());
    w32(m, gpv(mesh::kGpLastRaster), chance(rng, 30) ? kRaster : (chance(rng, 50) ? 0xFFFFFFFFu : 0));
    w32(m, gpv(-17260), kRing);
    const u16 size = static_cast<u16>(8 + rng() % 32);
    w16(m, gpv(-20292), size);
    for (u32 k = 0; k < 64; ++k) w32(m, kRing + 4 * k, kResEntries2 + 0x40 * (k % 4) + 24);
    w16(m, gpv(-17268), static_cast<u16>(rng() % (size - 2)));
    w16(m, gpv(-17264), static_cast<u16>(size - 1));
}

void put_mesh_pipe(Machine& m, std::mt19937& rng, u32 mesh_index) {
    w32(m, kPipe + mesh::pd::kMatPrivate, kMatPvt);
    w32(m, kPipe + mesh::pd::kMesh, kHeader + 16 + 12 * mesh_index);
    w32(m, kPipe + mesh::pd::kResEntrySlot, kResArray + 4 + 4 * mesh_index);
    w32(m, kPipe + mesh::pd::kSurfaceProps, kMaterial + 12);
    w32(m, kPipe + mesh::pd::kTexture, r32(m, kMaterial));
    w32(m, kPipe + mesh::pd::kMatColour, r32(m, kMaterial + 4));
    fill_floats(m, kPipe + mesh::pd::kMorphLerp, 1, rng);
    w8(m, kPipe + mesh::pd::kTransType, static_cast<u8>(rng() & 0x3Fu));
    w8(m, kPipe + mesh::pd::kPrimType, static_cast<u8>(chance(rng, 85) ? 1 + rng() % 4 : rng()));
}

// The MatFX material extension: both 64-byte slots filled for `effect` (bridges.h), the kind at +128.
// Slot words: +0 frame / texture / UV matrix, +4 texture / UV matrix, +8 / +12 / +16 floats, +40 ALPHA_2,
// +48 FOGCOL (0x01000000 = the driver's), +56 TEST_2 bits; the same at +64.. for slot 1.
void put_matfx(Machine& m, std::mt19937& rng, u32 effect) {
    fill_random(m, kExt, 0x90, rng);
    const u32 off = 0x20 + 4 * (rng() % 4);
    w32(m, gpv(br::kGpMatFxExt), off);
    w32(m, kMaterial + off, kExt);
    // the bump scale cache: sometimes the camera's far plane already (no recompute)
    w32(m, gpv(br::kGpCamFar), chance(rng, 30) ? r32(m, kCamera + 132) : rand_float(rng));
    w32(m, gpv(br::kGpCamDepthScale), rand_float(rng));
    w32(m, kExt + br::kExtEffect, effect);
    fill_floats(m, kUvMats, 32, rng);
    put_frame(m, kEffectFrames, rng);
    put_frame(m, kEffectFrames + 0xC0, rng);
    for (u32 slot = 0; slot < 2; ++slot) {
        const u32 s = kExt + 64 * slot;
        fill_floats(m, s + 8, 3, rng);
        w64(m, s + 40, rng64(rng));
        w64(m, s + 48, chance(rng, 40) ? 0x01000000ull : rng64(rng));
        w64(m, s + 56, rng64(rng));
    }
    switch (effect) {
    case 1:  // bump: +0 frame (0 = the camera's), +4 bump texture (0 = the material's)
        w32(m, kExt + 0, chance(rng, 20) ? 0 : kEffectFrames);
        w32(m, kExt + 4, chance(rng, 70) ? kTexture2 : 0);
        break;
    case 2:  // environment: +0 frame, +4 texture
        w32(m, kExt + 0, chance(rng, 20) ? 0 : kEffectFrames);
        w32(m, kExt + 4, chance(rng, 80) ? kTexture2 : 0);
        break;
    case 3:  // bump (slot 0) + environment (slot 1)
        w32(m, kExt + 0, chance(rng, 20) ? 0 : kEffectFrames);
        w32(m, kExt + 4, chance(rng, 70) ? kTexture2 : 0);
        w32(m, kExt + 64, chance(rng, 20) ? 0 : kEffectFrames + 0xC0);
        w32(m, kExt + 68, chance(rng, 80) ? kTexture2 : 0);
        break;
    case 4:  // dual: +0 texture
        w32(m, kExt + 0, chance(rng, 80) ? kTexture2 : 0);
        break;
    case 5:  // UV transform: +0 matrix
        w32(m, kExt + 0, chance(rng, 75) ? kUvMats : 0);
        break;
    case 6:  // UV transform (+0, +4 matrices) + dual (+64 texture)
        w32(m, kExt + 0, chance(rng, 75) ? kUvMats : 0);
        w32(m, kExt + 4, chance(rng, 75) ? kUvMats + 64 : 0);
        w32(m, kExt + 64, chance(rng, 80) ? kTexture2 : 0);
        break;
    default: break;
    }
}

struct BridgeCase {
    Hw hw;
    u32 mesh_index = 0;
};
BridgeCase put_bridge_world(Machine& m, std::mt19937& rng, u32 effect) {
    BridgeCase b;
    const AtomWorld a = put_atomic_world(m, rng);
    put_material_world(m, rng, a.meshes);
    put_matfx(m, rng, effect);
    b.mesh_index = rng() % a.meshes;
    put_mesh_pipe(m, rng, b.mesh_index);
    b.hw = put_dma(m, rng);
    return b;
}

}  // namespace

// =========================================================================================================
// Effect 5: UV transform
// =========================================================================================================

TEST_CASE("game(render_bridges): matfxBridgeUvTransform (UV transform) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x472270u};
    int identity = 0;
    for (u32 i = 0; i < 600; ++i) {
        BridgeCase b = put_bridge_world(m, rng, 5);
        identity += r32(m, kExt) == 0;
        const auto p = pair(m, PAIR(fn_matfxBridgeUvTransform_00472270), {sx(kPipe), 0, 0, 0}, seed_of(i), "matfxBridgeUvTransform", kRegBridge, b.hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
    CHECK(identity > 50);
}

// =========================================================================================================
// Effect 1: bump map
// =========================================================================================================

TEST_CASE("game(render_bridges): matfxBridgeBumpMap (bump map) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46C5B0u};
    int own_texture = 0, rescaled = 0;
    for (u32 i = 0; i < 600; ++i) {
        BridgeCase b = put_bridge_world(m, rng, 1);
        own_texture += r32(m, kExt + 4) == 0;
        rescaled += r32(m, gpv(br::kGpCamFar)) != r32(m, kCamera + 132);
        const auto p = pair(m, PAIR(fn_matfxBridgeBumpMap_0046c5b0), {sx(kPipe), 0, 0, 0}, seed_of(i), "matfxBridgeBumpMap", kRegBridge, b.hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
        // rule: the PipeData's texture is the bump texture, else the material's
        const u32 want = r32(m, kExt + 4) ? r32(m, kExt + 4) : r32(m, kMaterial);
        CHECK(r32(m, kPipe + mesh::pd::kTexture) == want);
    }
    CHECK(own_texture > 50);
    CHECK(rescaled > 50);
}

// =========================================================================================================
// Effect 4: dual texture
// =========================================================================================================

TEST_CASE("game(render_bridges): matfxBridgeDual (dual texture) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46E170u};
    int second = 0, base = 0;
    for (u32 i = 0; i < 600; ++i) {
        BridgeCase b = put_bridge_world(m, rng, 4);
        second += r32(m, kExt) != 0;
        base += r32(m, kMaterial) != 0;
        const auto p = pair(m, PAIR(fn_matfxBridgeDual_0046e170), {sx(kPipe), 0, 0, 0}, seed_of(i), "matfxBridgeDual", kRegBridge, b.hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
    CHECK(second > 300);
    CHECK(base > 300);
}

// =========================================================================================================
// Effect 2: environment map
// =========================================================================================================

TEST_CASE("game(render_bridges): matfxBridgeEnvMap (environment map) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46CD90u};
    int env = 0, camera_frame = 0;
    for (u32 i = 0; i < 600; ++i) {
        BridgeCase b = put_bridge_world(m, rng, 2);
        env += r32(m, kExt + 4) != 0;
        camera_frame += r32(m, kExt) == 0;
        const auto p = pair(m, PAIR(fn_matfxBridgeEnvMap_0046cd90), {sx(kPipe), 0, 0, 0}, seed_of(i), "matfxBridgeEnvMap", kRegBridge, b.hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
    CHECK(env > 300);
    CHECK(camera_frame > 50);
}

// =========================================================================================================
// Effect 6: dual texture + UV transform
// =========================================================================================================

TEST_CASE("game(render_bridges): matfxBridgeDualUvTransform (dual + UV transform) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x472970u};
    int identity = 0, both = 0;
    for (u32 i = 0; i < 600; ++i) {
        BridgeCase b = put_bridge_world(m, rng, 6);
        identity += r32(m, kExt) == 0 || r32(m, kExt + 4) == 0;
        both += r32(m, kExt) != 0 && r32(m, kExt + 4) != 0;
        const auto p = pair(m, PAIR(fn_matfxBridgeDualUvTransform_00472970), {sx(kPipe), 0, 0, 0}, seed_of(i), "matfxBridgeDualUvTransform", kRegBridge, b.hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
    CHECK(identity > 100);
    CHECK(both > 100);
}

// =========================================================================================================
// Effect 3: bump map + environment map
// =========================================================================================================

TEST_CASE("game(render_bridges): matfxBridgeBumpEnvMap (bump + environment map) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46D6F0u};
    int own_texture = 0, env = 0;
    for (u32 i = 0; i < 600; ++i) {
        BridgeCase b = put_bridge_world(m, rng, 3);
        w32(m, gpv(-20916), chance(rng, 30) ? r32(m, kCamera + 132) : rand_float(rng));  // its own camera cache
        w32(m, gpv(-20920), rand_float(rng));
        own_texture += r32(m, kExt + 4) == 0;
        env += r32(m, kExt + 68) != 0;
        const auto p = pair(m, PAIR(fn_matfxBridgeBumpEnvMap_0046d6f0), {sx(kPipe), 0, 0, 0}, seed_of(i), "matfxBridgeBumpEnvMap", kRegBridge, b.hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
    CHECK(own_texture > 50);
    CHECK(env > 300);
}

// =========================================================================================================
// The partitioned skin's object set-up callback
// =========================================================================================================
namespace {

constexpr u32 kPalette = kWorld + 0x6000;  // 64 bones x 64 bytes
constexpr u32 kHierarchy = kWorld + 0x5000, kNodeRecs = kWorld + 0x5100, kNodeMats = kWorld + 0x5400;
constexpr u32 kSkin = kWorld + 0x5800, kSkinMats = kWorld + 0x7000;
constexpr u32 kNodeFrames = kWorld + 0x8000;  // 16 frames x 0xC0
const std::vector<Region> kRegSkin = {{kTplLo, kTplHi - kTplLo}, {kWinLo, kWinLen}, {kRwGlobals, 0x200}, {kSkinGlobals, 0x60}};

// A skinned atomic (as test_render_mesh.cpp): the skin globals, a hierarchy (or none) with node frames, a skin with
// its matrices; `partitions`: the skin's partition word (+48) and record (+44).
u32 put_skin(Machine& m, std::mt19937& rng, bool hierarchy, bool partitions) {
    fill_random(m, kSkinGlobals, 0x60, rng);
    const u32 aoff = 0x08 + 4 * (rng() % 4), goff = 0x30 + 4 * (rng() % 4);
    w32(m, 0x95DE14u, aoff);
    w32(m, 0x95DE18u, goff);
    w32(m, 0x95DE1Cu, kPalette);
    w32(m, 0x95DE34u, chance(rng, 25) ? 0x4A2BA0u : 0);  // the lighting hook: sometimes a leaf of the emitted set
    // bone counts on both sides of the 8-per-iteration copy (_rpSkinMatrixUpdating needs at least one node)
    const u32 bones = 1 + rng() % 16;
    w32(m, kAtomic + aoff, hierarchy ? kHierarchy : 0);
    w32(m, kGeometry + goff, kSkin);
    fill_random(m, kSkin, 0x80, rng);
    w32(m, kSkin, bones);
    w32(m, kSkin + 12, kSkinMats);
    w32(m, kSkin + 48, partitions ? 1 + rng() % 4 : 0);
    fill_floats(m, kSkinMats, 16 * 16, rng);
    fill_floats(m, kNodeMats, 16 * 16, rng);
    fill_random(m, kPalette, 64 * 16, rng);
    w32(m, kHierarchy, chance(rng, 85) ? pick(rng, {0, 2, 0x4000, 0x4002, 0x1000}) : rng());
    w32(m, kHierarchy + 4, bones);
    w32(m, kHierarchy + 8, kNodeMats);
    w32(m, kHierarchy + 16, kNodeRecs);
    for (u32 i = 0; i < 16; ++i) {
        const u32 f = kNodeFrames + 0xC0 * (i % 16);
        put_frame(m, f, rng);
        w32(m, kNodeRecs + 16 * i + 12, f);
    }
    return bones;
}

}  // namespace

TEST_CASE("game(render_bridges): skinSplitObjectSetupCB (partitioned skin set-up) equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4718A0u};
    int split = 0, whole = 0, empty = 0, wide = 0;
    for (u32 i = 0; i < 800; ++i) {
        put_atomic_world(m, rng);
        const bool partitions = chance(rng, 40);
        const u32 bones = put_skin(m, rng, chance(rng, 85), partitions);
        if (chance(rng, 8)) {  // no meshes: returns 0 after the resEntry array
            w16(m, kHeader + 4, 0);
            w32(m, kResArray, 0);
        }
        const bool no_meshes = m.at(kHeader + 4)[0] == 0 && m.at(kHeader + 5)[0] == 0;
        w32(m, br::kSkinPartition, rng());
        Hw hw = put_dma(m, rng);
        const auto p = pair(m, PAIR(fn_skinSplitObjectSetupCB_004718a0), {sx(kPipe), sx(kMatRef), 0, 0}, seed_of(i), "skinSplitObjectSetupCB",
                            kRegSkin, hw);
        if (no_meshes) {
            ++empty;
            CHECK(gpr_of(p.first, GPR_V0) == 0);
            continue;
        }
        CHECK(gpr_of(p.first, GPR_V0) == 1);
        // rules: the partition record for a partitioned skin, else cleared after the whole upload
        if (partitions) {
            ++split;
            CHECK(r32(m, br::kSkinPartition) == kSkin + 44);
        } else {
            ++whole;
            wide += bones >= 9;
            CHECK(r32(m, br::kSkinPartition) == 0);
        }
    }
    MESSAGE("skinSplitObjectSetupCB: " << split << " partitioned, " << whole << " whole uploads (" << wide << " with 9+ bones), " << empty
                           << " without meshes");
    CHECK(split > 100);
    CHECK(whole > 100);
    CHECK(wide > 30);
}

// =========================================================================================================
// The draw observers
// =========================================================================================================
namespace {
struct ObsLog {
    int meshes = 0, effects[7] = {}, skins = 0, bad = 0, direct_checked = 0;
};
ObsLog g_obs;
Machine* g_obs_machine = nullptr;
void on_mesh(EEContext&, const mesh::MeshDraw& d) {
    ++g_obs.meshes;
    const u8 tt = d.trans_type;
    if (d.vu1_code_index != (((tt & 0x20) >> 5) | ((tt & 0x18) >> 2))) ++g_obs.bad;
    if (d.vu1_program != r32(*g_obs_machine, kCodeArray + 4u * d.vu1_code_index)) ++g_obs.bad;
    if (d.material != kMaterial) ++g_obs.bad;
}
void on_skin(EEContext&, const mesh::SkinPalette& s) {
    ++g_obs.skins;
    if (s.palette != kPalette) ++g_obs.bad;
}
void on_effect(EEContext&, const br::EffectDraw& e) {
    const u32 kind = static_cast<u32>(e.effect);
    if (kind >= 1 && kind <= 6) ++g_obs.effects[kind];
    if (e.pipe_data != kPipe || e.extra_qw == 0) ++g_obs.bad;
    // the effect block starts with a DMA cnt tag (id 1 in bits 28..30) whose quadword count fits the block
    const u8* p = e.extra_at >= 0x70000000u ? g_obs_machine->mem.scratchpad() + (e.extra_at - 0x70000000u)
                                            : g_obs_machine->mem.main_ram() + e.extra_at;
    u32 tag;
    std::memcpy(&tag, p, 4);
    if (((tag >> 28) & 7) != 1) ++g_obs.bad;
    if (e.effect == br::Effect::UvTransform) {
        // 22_rendering.md section 3.2 plus this slice: cnt 3, STCYCL 4,4 / UNPACK V4-32 x3 -> 0x3BC, rows 0, 1, 3 of
        // the UV matrix ({x, y} low half), the identity at sp+80 when the effect has none
        u32 w[4];
        std::memcpy(w, p, 16);
        if (w[0] != 0x10000003u || w[2] != 0x01000404u || w[3] != 0x6C0303BCu) ++g_obs.bad;
        const u32 uv = r32(*g_obs_machine, kExt);
        if (uv != 0) {
            const u32 rows[3] = {0, 16, 48};
            for (u32 k = 0; k < 3; ++k) {
                u64 q[2];
                std::memcpy(q, p + 16 * (k + 1), 16);
                if (q[0] != r64(*g_obs_machine, uv + rows[k]) || q[1] != 0) ++g_obs.bad;
            }
        }
    } else if (e.effect != br::Effect::BumpMap) {
        // the two-pass effects end their block with DIRECT 6: GIF tag NLOOP 5 (A+D) and ALPHA_2, CLAMP_2, TEST_2,
        // TEX1_2, ZBUF_2 (GS registers 0x43, 0x09, 0x48, 0x15, 0x4F)
        const u8* direct = p + 16 * (e.extra_qw - 6);
        u64 gif[2];
        std::memcpy(gif, direct, 16);
        if ((gif[0] & 0xFFFF) != 0x8005 || gif[1] != 0xE) ++g_obs.bad;
        const u64 regs[5] = {0x43, 0x09, 0x48, 0x15, 0x4F};
        for (u32 k = 0; k < 5; ++k) {
            u64 q[2];
            std::memcpy(q, direct + 16 * (k + 1), 16);
            if (q[1] != regs[k]) ++g_obs.bad;
        }
        ++g_obs.direct_checked;
    }
}
}  // namespace

TEST_CASE("game(render_bridges): the draw observers report each bridge without changing guest state") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x0B5E8u};
    const mesh::DrawObserver dobs{nullptr, &on_skin, &on_mesh};
    const br::EffectObserver eobs{&on_effect};
    g_obs_machine = &m;
    mesh::set_draw_observer(&dobs);
    br::set_effect_observer(&eobs);
    g_obs = {};
    struct Entry {
        u32 effect;
        Fn hand, recomp;
    };
    const Entry entries[] = {{1, PAIR(fn_matfxBridgeBumpMap_0046c5b0)}, {2, PAIR(fn_matfxBridgeEnvMap_0046cd90)}, {3, PAIR(fn_matfxBridgeBumpEnvMap_0046d6f0)},
                             {4, PAIR(fn_matfxBridgeDual_0046e170)}, {5, PAIR(fn_matfxBridgeUvTransform_00472270)}, {6, PAIR(fn_matfxBridgeDualUvTransform_00472970)}};
    for (u32 i = 0; i < 40; ++i) {
        for (const Entry& e : entries) {
            BridgeCase b = put_bridge_world(m, rng, e.effect);
            pair(m, e.hand, e.recomp, {sx(kPipe), 0, 0, 0}, seed_of(i), "bridge observed", kRegBridge, b.hw);
        }
        put_atomic_world(m, rng);
        put_skin(m, rng, true, false);
        Hw hw = put_dma(m, rng);
        pair(m, PAIR(fn_skinSplitObjectSetupCB_004718a0), {sx(kPipe), sx(kMatRef), 0, 0}, seed_of(i), "skinSplitObjectSetupCB observed", kRegSkin, hw);
    }
    mesh::set_draw_observer(nullptr);
    br::set_effect_observer(nullptr);
    MESSAGE("observers: " << g_obs.meshes << " mesh draws, " << g_obs.skins << " palettes");
    // only the hand runs report (each pair calls the hand body once; the recompiled bodies have no observer)
    CHECK(g_obs.meshes == 6 * 40);
    for (u32 k = 1; k <= 6; ++k) CHECK(g_obs.effects[k] == 40);
    CHECK(g_obs.skins > 0);
    CHECK(g_obs.direct_checked == 4 * 40);
    CHECK(g_obs.bad == 0);
}

TEST_CASE("game(render_bridges): pair count") { MESSAGE("render_bridges pairs: " << g_pairs); }

#endif  // P3FES_GAME_HAVE_GENERATED
