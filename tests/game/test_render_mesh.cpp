// Phase 5 pair tests for the render_mesh slice (game/src/render/mesh.cpp): RenderWare's PS2All mesh seam
// (docs/ANALYSIS/22_rendering.md sections 3 and 8.2). Each hand-written function and the recompiled body it
// replaces run on identical guest machines built from random RenderWare records (atomics, geometries, mesh
// headers, materials, textures and rasters with their sky extensions, lights, world-sector ties, skins and
// hierarchies, PS2All node / material pipeline private data, resEntries, the RW sky-driver gp words, the
// packet templates and the DMA state of the packet layer) on pair_harness.h's scripted hardware bus.
//
// Stricter than the Outcome: per pair this file compares EVERY general register in 128 bits, HI/LO, all FPU
// registers, ACC, FCR31 and the whole VU0 state at the return, the whole register file (GPRs, HI/LO, SA, FPRs,
// FCR31) and the cycle count at EVERY check point (a check point may preempt the thread and the kernel saves
// the register file in guest memory), the bus access log (the DMA packet layer's D8 / D_STAT / D_PCR accesses,
// the DI/EI status reads), the scratchpad, the world region, the RW globals / templates / texture cache / light
// block / skin globals, the DMA buffer window, the WHOLE stack window (live and dead: the hand versions write
// the original's spills and frame records), the virtual cycles and the check-point count. FPRs, ACC and the
// VU0 registers start random, so a register or lane the original leaves alone must stay alone. Callbacks are
// functions of the emitted set reached through the dispatch table, including non-leaf ones that spill $ra below
// the $sp they get. Host-side checks restate documented rules (22_rendering.md section 3.2: the VU1 code index,
// the prim / transType table, the A+D register pairs, the palette layout).
#include "pair_harness.h"

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
P3FES_DECL_PAIR(fn_sub_49CA50_0049ca50)
P3FES_DECL_PAIR(fn_sub_49CAB0_0049cab0)
P3FES_DECL_PAIR(fn_sub_49CBD0_0049cbd0)
P3FES_DECL_PAIR(fn_sub_4F1E20_004f1e20)
P3FES_DECL_PAIR(fn_sub_4F1E40_004f1e40)
P3FES_DECL_PAIR(fn_RpAtomicPS2AllPrimTypeTransTypeSetupFunc_004a05d0)
P3FES_DECL_PAIR(fn_sub_4A0480_004a0480)
P3FES_DECL_PAIR(fn_sub_49FF10_0049ff10)
P3FES_DECL_PAIR(fn_sub_4A0430_004a0430)
P3FES_DECL_PAIR(fn_sub_4A06C0_004a06c0)
P3FES_DECL_PAIR(fn_sub_4A09D0_004a09d0)
P3FES_DECL_PAIR(fn__rpSkinMatrixUpdating_0046b510)
P3FES_DECL_PAIR(fn_sub_46B8E0_0046b8e0)
P3FES_DECL_PAIR(fn_sub_46EB90_0046eb90)
P3FES_DECL_PAIR(fn_openVU1SetupPktNew_004ec2b0)
P3FES_DECL_PAIR(fn_sub_4F0F30_004f0f30)
P3FES_DECL_PAIR(fn_RpSkyTexCacheAccessRaster_004f1020)
P3FES_DECL_PAIR(fn_RpMeshPS2AllBridgeCallBack_004a0e00)
P3FES_DECL_PAIR(fn_sub_46EA80_0046ea80)
P3FES_DECL_PAIR(fn_PS2AllNodeBody_0049f5d0)
P3FES_DECL_PAIR(fn_AtomicDefaultRenderCallBack_00490860)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace mesh = p3fes::game::mesh;

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
constexpr u32 kGpWindow = gpv(-20800);
constexpr u32 kGpWindowLen = 4000;
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
u64 rng64(std::mt19937& rng) { return (static_cast<u64>(rng()) << 32) | rng(); }
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
// A world address: 16-byte aligned record slot k of size `size` in [kWorld + base, ...).
u32 slot(u32 base, u32 k, u32 size) { return kWorld + base + k * size; }

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
    std::map<unsigned, u32> fpr_in;
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
    for (const auto& [f, v] : hw.fpr_in) m.ctx.fpr[f] = v;
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
        MESSAGE("the hand run of " << label << " stopped at pc " << hex64(e.pc) << " ra " << hex64(e.ctx ? e.ctx->gpr[GPR_RA].u64[0] : 0)
                                    << ": " << e.what);
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

// The packet write pointer: mostly in the scratchpad half, sometimes main RAM.
u32 rand_write_ptr(std::mt19937& rng) {
    return chance(rng, 80) ? 0x70000000u + 16u * (rng() % 0x380) : slot(0xE000, rng() % 64, 16);
}

}  // namespace

// =========================================================================================================
// Leaves
// =========================================================================================================

TEST_CASE("game(render_mesh): the filter / colour / surface / raster TEX leaves equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x49CA50u};
    for (u32 i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        w64(m, gpv(mesh::kGpTex1), rng64(rng));
        const u64 mode = chance(rng, 80) ? rng() % 9 : rng64(rng);
        pair(m, PAIR(fn_sub_49CA50_0049ca50), {mode, 0, 0, 0}, i, "sub_49CA50");

        const u32 wp = rand_write_ptr(rng);
        w32(m, gpv(mesh::kGpSprWrite), wp);
        const u32 rgba = slot(0x100, rng() % 16, 4);
        Hw hw;
        hw.fpr_in[12] = pick(rng, {0x3B808081u, 0x3B011B50u, rand_float(rng)});
        pair(m, PAIR(fn_sub_49CAB0_0049cab0), {sx(rgba), 0, 0, 0}, i, "sub_49CAB0", {}, hw);
        w32(m, gpv(mesh::kGpSprWrite), wp);
        const u32 surf = slot(0x200, rng() % 16, 12);
        fill_floats(m, surf, 3, rng);
        pair(m, PAIR(fn_sub_49CBD0_0049cbd0), {sx(surf), 0, 0, 0}, i, "sub_49CBD0", {}, hw);

        const u32 ext = 4 * (rng() % 32);
        w32(m, gpv(mesh::kGpRasterExt), ext);
        const u32 raster = slot(0x400, rng() % 8, 0x100);
        const u32 out0 = slot(0x800, rng() % 8, 8), out1 = slot(0x900, rng() % 8, 8);
        pair(m, PAIR(fn_sub_4F1E20_004f1e20), {sx(raster), sx(out0), sx(out1), 0}, i, "sub_4F1E20");
        pair(m, PAIR(fn_sub_4F1E40_004f1e40), {sx(raster), sx(out0), chance(rng, 85) ? rng() % 9 : rng64(rng), 0}, i,
             "sub_4F1E40");
    }
    // rules: the filter table (22_rendering.md section 3.2: TEX1 MMAG/MMIN from the filter mode).
    const u32 bits[9] = {0, 0, 0x60, 0x80, 0x120, 0xC0, 0x160, 0, 0};
    for (u32 mode = 0; mode < 9; ++mode) {
        w64(m, gpv(mesh::kGpTex1), ~0ull);
        pair(m, PAIR(fn_sub_49CA50_0049ca50), {mode, 0, 0, 0}, mode, "sub_49CA50 rule");
        CHECK(r64(m, gpv(mesh::kGpTex1)) == ((~0ull & ~0x1E0ull) | bits[mode]));
    }
}

TEST_CASE("game(render_mesh): RpAtomicPS2AllPrimTypeTransTypeSetupFunc and the instance test equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A05D0u};
    const u32 pdata = slot(0x0, 0, 0x60);
    for (u32 i = 0; i < 600; ++i) {
        fill_random(m, kWorld, 0x2000, rng);
        const u32 header = slot(0x100, 0, 0x20);
        w32(m, pdata + mesh::pd::kMeshHeader, header);
        w32(m, header, chance(rng, 80) ? pick(rng, {0, 1, 2, 4, 8, 0x10, 0x100, 0x200}) : rng());
        m.at(gpv(mesh::kGpCamFlags))[0] = static_cast<u8>(rng());
        const u64 inside = chance(rng, 80) ? rng() % 3 : rng64(rng);
        pair(m, PAIR(fn_RpAtomicPS2AllPrimTypeTransTypeSetupFunc_004a05d0), {sx(pdata), inside, 0, 0}, i, "RpAtomicPS2AllPrimTypeTransTypeSetupFunc");

        // the instance test: atomic, geometry, resEntry array and resEntry
        const u32 atomic = slot(0x200, 0, 0x80), geometry = slot(0x300, 0, 0x60), arr = slot(0x400, 0, 0x10);
        const u32 res = slot(0x500, 0, 0x40);
        w32(m, atomic + 24, geometry);
        w32(m, geometry + 8, chance(rng, 85) ? rng() & 0xFFu : rng());
        w8(m, geometry + 24, static_cast<u8>(rng() % 4));
        w16(m, geometry + 12, chance(rng, 50) ? 0 : static_cast<u16>(rng()));
        w32(m, pdata + mesh::pd::kResEntries, arr);
        w32(m, arr + 4, chance(rng, 20) ? 0 : res);
        const u32 ident = (r32(m, geometry + 8) & 0x9F) << 16 | u32{m.at(geometry + 24)[0]} << 24 | (r32(m, header + 4) >> 16);
        const u32 res_ident = chance(rng, 40) ? ident : (chance(rng, 50) ? (ident ^ 0x1u) : rng());
        w32(m, res + 40, res_ident);
        w32(m, atomic + 76, chance(rng, 50) ? 1 : rng());
        const s16 sm = static_cast<s16>(rng() % 3), em = static_cast<s16>(rng() % 3);
        w16(m, atomic + 76 + 4, static_cast<u16>(sm));
        w16(m, atomic + 76 + 6, static_cast<u16>(em));
        w32(m, res + 24 + 36, chance(rng, 50) ? static_cast<u32>(static_cast<s32>(sm)) : rng() % 3);
        w32(m, res + 24 + 40, chance(rng, 50) ? static_cast<u32>(static_cast<s32>(em)) : rng() % 3);
        pair(m, PAIR(fn_sub_4A0480_004a0480), {sx(atomic), sx(pdata), 0, 0}, i, "sub_4A0480");
    }
    // rules: the prim / transType table (22_rendering.md section 3.2).
    struct Row {
        u32 flags;
        u8 prim, tt;
    };
    const Row rows[] = {{1, 4, 0}, {0, 3, 4}, {2, 3, 4}, {0x10, 4, 0}, {8, 2, 0x10}, {4, 1, 0x14}};
    for (const Row& row : rows) {
        const u32 header = slot(0x100, 0, 0x20);
        w32(m, pdata + mesh::pd::kMeshHeader, header);
        w32(m, header, row.flags);
        m.at(gpv(mesh::kGpCamFlags))[0] = 0x08;  // parallel projection
        pair(m, PAIR(fn_RpAtomicPS2AllPrimTypeTransTypeSetupFunc_004a05d0), {sx(pdata), 2, 0, 0}, row.flags, "RpAtomicPS2AllPrimTypeTransTypeSetupFunc rule");
        CHECK(m.at(pdata + mesh::pd::kPrimType)[0] == row.prim);
        CHECK(m.at(pdata + mesh::pd::kTransType)[0] == (row.tt | 0x08));
        pair(m, PAIR(fn_RpAtomicPS2AllPrimTypeTransTypeSetupFunc_004a05d0), {sx(pdata), 1, 0, 0}, row.flags, "RpAtomicPS2AllPrimTypeTransTypeSetupFunc rule clip");
        CHECK(m.at(pdata + mesh::pd::kTransType)[0] == (row.tt | 0x0A));
    }
}

// =========================================================================================================
// Lights and the stock atomic set-up
// =========================================================================================================
namespace {

// World record placement (kWorld + offset).
constexpr u32 kPipe = kWorld + 0x0000, kHeader = kWorld + 0x0100, kAtomic = kWorld + 0x0200, kGeometry = kWorld + 0x0300;
constexpr u32 kResArray = kWorld + 0x0400, kResEntry = kWorld + 0x0500, kAtomFrame = kWorld + 0x0600;
constexpr u32 kRoot = kWorld + 0x0700, kMatRef = kWorld + 0x0800, kObjMatrix = kWorld + 0x0840, kCamera = kWorld + 0x0900;
constexpr u32 kWorldRec = kWorld + 0x0C00, kLights = kWorld + 0x1000, kLightFrames = kWorld + 0x1400;
constexpr u32 kTies = kWorld + 0x1C00, kSectors = kWorld + 0x1D00, kLightTies = kWorld + 0x2000;
constexpr u32 kLightBlock = kWorld + 0x3000, kInvRec = kWorld + 0x4000;
constexpr u32 kRwGlobals = mesh::kRwGlobals;
constexpr u32 kFrustumOff = 0x40;  // gp-16972: the camera's frustum planes at camera + 0x40 + 96
const std::vector<Region> kRegRw = {{kRwGlobals, 0x200}};

u32 light_at(u32 i) { return kLights + 0x80 * i; }

// A frame whose LTM (+80) is clean (root +3 bits 0..1 clear: RwFrameGetLTM returns it without a sync).
void put_frame(Machine& m, u32 frame, std::mt19937& rng) {
    fill_floats(m, frame + 80, 16, rng);
    w32(m, frame + 80 + 12, chance(rng, 40) ? 3u : rng() & 0x20003u);
    w32(m, frame + 160, kRoot);
}

// A light of a random type with a frame (or none).
void put_light(Machine& m, u32 i, std::mt19937& rng) {
    const u32 l = light_at(i);
    fill_random(m, l, 0x80, rng);
    w8(m, l + 1, static_cast<u8>(chance(rng, 85) ? pick(rng, {1, 2, 0x80, 0x81, 0x82, 0}) : rng()));
    w8(m, l + 2, static_cast<u8>(chance(rng, 75) ? (rng() | 1u) : (rng() & ~1u)));
    fill_floats(m, l + 20, 6, rng);  // radius, colour, ...
    fill_floats(m, l + 40, 1, rng);
    const u32 frame = kLightFrames + 0xC0 * i;
    put_frame(m, frame, rng);
    w32(m, l + 4, chance(rng, 90) ? frame : 0);
}

// The light block state: pointer into the world, a count (0 = first light) and the header record.
void put_light_block(Machine& m, std::mt19937& rng) {
    fill_random(m, kLightBlock, 0x800, rng);
    w32(m, gpv(mesh::kGpLightPtr), kLightBlock + 16 * (rng() % 8));
    w32(m, gpv(mesh::kGpLightCount), chance(rng, 40) ? 0u : pick(rng, {1, 4, 6, 50, 121, 122, 123, 124, 125, 0xFFFFFFFFu}));
    fill_floats(m, kInvRec, 24, rng);
}

// The common world of the atomic set-up and lights: camera, frustum, world lights, sector ties, geometry,
// mesh header, resEntry array (one slot per mesh: no reallocation), matrix reference.
struct AtomWorld {
    u32 meshes = 1;
    bool morphing = false;
};
AtomWorld put_atomic_world(Machine& m, std::mt19937& rng) {
    AtomWorld a;
    fill_random(m, kWorld, 0x5000, rng);
    fill_random(m, kRwGlobals, 0x200, rng);
    put_light_block(m, rng);
    w32(m, kRoot, rng());
    w8(m, kRoot + 3, static_cast<u8>(rng() & ~3u));
    // camera: +32 view matrix, frustum planes
    w32(m, kRwGlobals + 0, kCamera);
    fill_floats(m, kCamera + 32, 16, rng);
    w32(m, gpv(mesh::kGpCamFrustum), kFrustumOff);
    for (u32 p = 0; p < 6; ++p) {
        const u32 pl = kCamera + kFrustumOff + 96 + 20 * p;
        fill_floats(m, pl, 4, rng);
    }
    m.at(gpv(mesh::kGpCamFlags))[0] = static_cast<u8>(rng());
    // atomic, geometry, mesh header
    a.meshes = 1 + rng() % 4;
    a.morphing = chance(rng, 25);
    w32(m, kPipe + mesh::pd::kObject, kAtomic);
    w32(m, kAtomic + 4, kAtomFrame);
    put_frame(m, kAtomFrame, rng);
    w32(m, kAtomic + 24, kGeometry);
    w8(m, kAtomic + 3, static_cast<u8>(rng() & ~1u));  // world sphere valid (no recompute)
    w32(m, kAtomic + 76, rng() & ~2u);                   // interpolator: no resync
    fill_floats(m, kAtomic + 44, 4, rng);                // the world sphere
    fill_floats(m, kAtomic + 88, 2, rng);
    w32(m, kGeometry + 8, chance(rng, 80) ? (rng() & 0x00FF00FFu) : rng());
    w32(m, kGeometry + 24, a.morphing ? 2 + rng() % 2 : 1);
    w16(m, kGeometry + 12, chance(rng, 60) ? 0 : static_cast<u16>(rng()));
    w32(m, kGeometry + 84, kHeader);
    w32(m, kHeader, chance(rng, 80) ? pick(rng, {0, 1, 2, 4, 8, 0x10}) : rng());
    w16(m, kHeader + 4, static_cast<u16>(a.meshes));
    w32(m, kHeader + 12, 0);
    // the first mesh's material (header + 16 + 8): sub_4A06C0 stores material + 12 at its record's +0
    w32(m, kHeader + 24, kWorld + 0x4800);
    // resEntry arrays (geometry / atomic plugin offsets), one slot per mesh
    const u32 goff = 0x40 + 4 * (rng() % 4), aoff = 0x70 + 4 * (rng() % 4);
    w32(m, gpv(mesh::kGpGeomResEntries), goff);
    w32(m, gpv(mesh::kGpAtomResEntries), aoff);
    w32(m, kGeometry + goff, kResArray);
    w32(m, kAtomic + aoff, kResArray);
    w32(m, kResArray, a.meshes);
    w32(m, kResArray + 4, chance(rng, 30) ? 0 : kResEntry);
    // matrix reference
    w32(m, kMatRef, kObjMatrix);
    // world lights (circular list at world +60 through light +52) and the light stamp
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
    // sector ties: atomic +100 -> tie (+0 next, +8 sector); sector +64 -> light tie (+0 next, +8 light)
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
    // light stamps: some lights already stamped this frame
    for (u32 i = 0; i < 8; ++i)
        if (chance(rng, 20)) w16(m, light_at(i) + 60, static_cast<u16>(r32(m, kRwGlobals + 8) >> 16) + 1);
    return a;
}

}  // namespace

TEST_CASE("game(render_mesh): the light block writers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x49FF10u};
    for (u32 i = 0; i < 800; ++i) {
        fill_random(m, kWorld, 0x5000, rng);
        w32(m, kRoot, rng());
        w8(m, kRoot + 3, static_cast<u8>(rng() & ~3u));
        put_light_block(m, rng);
        put_light(m, 0, rng);
        Hw hw;
        hw.fpr_in[12] = rand_float(rng);
        hw.fpr_in[13] = rand_float(rng);
        const u32 inv = chance(rng, 20) ? 0 : kInvRec;
        pair(m, PAIR(fn_sub_49FF10_0049ff10), {sx(light_at(0)), sx(inv), 0, 0}, i, "sub_49FF10", {}, hw);
        put_light_block(m, rng);
        pair(m, PAIR(fn_sub_4A0430_004a0430), {sx(light_at(0)), sx(kInvRec), 0, 0}, i, "sub_4A0430");
    }
    // rule: a point light after the header -> colour qw {r, g, b, 0x80}, then {pos, radius}; count 4 + 2.
    fill_random(m, kWorld, 0x5000, rng);
    w8(m, kRoot + 3, 0);
    put_light_block(m, rng);
    w32(m, gpv(mesh::kGpLightPtr), kLightBlock);
    w32(m, gpv(mesh::kGpLightCount), 0);
    put_light(m, 0, rng);
    w8(m, light_at(0) + 1, 0x80);
    w32(m, light_at(0) + 4, kLightFrames);
    pair(m, PAIR(fn_sub_49FF10_0049ff10), {sx(light_at(0)), 0, 0, 0}, 1, "sub_49FF10 rule");
    CHECK(r32(m, gpv(mesh::kGpLightCount)) == 6);
    CHECK(r32(m, gpv(mesh::kGpLightPtr)) == kLightBlock + 6 * 16);
    CHECK(r32(m, kLightBlock + 64 + 0) == r32(m, light_at(0) + 24));
    CHECK(r32(m, kLightBlock + 64 + 12) == 0x80);
    CHECK(r32(m, kLightBlock + 80 + 0) == r32(m, kLightFrames + 80 + 48));
    CHECK(r32(m, kLightBlock + 80 + 12) == r32(m, light_at(0) + 20));
}

TEST_CASE("game(render_mesh): the atomic lights and the stock atomic set-up equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A09D0u};
    for (u32 i = 0; i < 500; ++i) {
        put_atomic_world(m, rng);
        pair(m, PAIR(fn_sub_4A06C0_004a06c0), {sx(kPipe), 0, 0, 0}, i, "sub_4A06C0", kRegRw);
        put_atomic_world(m, rng);
        pair(m, PAIR(fn_sub_4A09D0_004a09d0), {sx(kPipe), sx(kMatRef), 0, 0}, i, "sub_4A09D0", kRegRw);
    }
}

// =========================================================================================================
// The DMA packet layer's state (as test_render_im2d.cpp builds it) and the skin
// =========================================================================================================
namespace {

constexpr u32 kTplLo = 0x965800u, kTplHi = 0x965A40u;
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;  // the DMA buffer window the worlds use
constexpr u32 kType = gpv(-17212), kFixup = gpv(-17208), kCntTag = gpv(-17204), kPktStart = gpv(-17196);
constexpr u32 kQWrite = gpv(-17192), kQLimit = gpv(-17188), kAlloc = gpv(-17184), kHalfEnd = gpv(-17180);
constexpr u32 kHalfSize = gpv(-17164), kHalf0 = gpv(-17160), kHalf1 = gpv(-17156), kGifTail = gpv(-17152);
constexpr u32 kDmaPtr = gpv(-17128), kSprBase = gpv(-17124);
constexpr u32 kD8Chcr = 0x1000D000u, kDStat = 0x1000E010u;
constexpr u32 kSkinGlobals = 0x0095DE00u;
const std::vector<Region> kRegDma = {{kTplLo, kTplHi - kTplLo}, {kWinLo, kWinLen}, {kRwGlobals, 0x200}, {kSkinGlobals, 0x60}};

// A random RW DMA state: no packet / an open VIF packet / one with an open cnt tag / an open GIF packet; the
// scratchpad half sometimes nearly full (the fromSPR copy); D8 busy or idle, D_STAT polls. Returns the bus.
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

constexpr u32 kPalette = kWorld + 0x6000;     // 64 bones x 64 bytes
constexpr u32 kHierarchy = kWorld + 0x5000, kNodeRecs = kWorld + 0x5100, kNodeMats = kWorld + 0x5400;
constexpr u32 kSkin = kWorld + 0x5800, kSkinMats = kWorld + 0x7000;
constexpr u32 kNodeFrames = kWorld + 0x8000;  // 16 frames x 0xC0
constexpr u32 kPartition = kWorld + 0x5A00, kSlotMap = kWorld + 0x5B00, kMeshTable = kWorld + 0x5C00, kRanges = kWorld + 0x5D00;

// A skinned atomic: the skin globals, a hierarchy (or none) with node frames, a skin with its matrices.
u32 put_skin(Machine& m, std::mt19937& rng, bool hierarchy) {
    fill_random(m, kSkinGlobals, 0x60, rng);
    const u32 aoff = 0x08 + 4 * (rng() % 4), goff = 0x30 + 4 * (rng() % 4);  // free atomic / geometry words
    w32(m, 0x95DE14u, aoff);
    w32(m, 0x95DE18u, goff);
    w32(m, 0x95DE1Cu, kPalette);
    w32(m, 0x95DE34u, chance(rng, 25) ? 0x4A2BA0u : 0);  // the lighting hook: sometimes a leaf of the emitted set
    const u32 bones = 1 + rng() % 16;
    w32(m, kAtomic + aoff, hierarchy ? kHierarchy : 0);
    w32(m, kGeometry + goff, kSkin);
    w32(m, kSkin, bones);
    w32(m, kSkin + 12, kSkinMats);
    fill_floats(m, kSkinMats, 16 * 16, rng);
    fill_floats(m, kNodeMats, 16 * 16, rng);
    w32(m, kHierarchy, chance(rng, 85) ? pick(rng, {0, 2, 0x4000, 0x4002, 0x1000}) : rng());
    w32(m, kHierarchy + 4, bones);
    w32(m, kHierarchy + 8, kNodeMats);
    w32(m, kHierarchy + 16, kNodeRecs);
    for (u32 i = 0; i < 16; ++i) {
        const u32 f = kNodeFrames + 0xC0 * i;
        put_frame(m, f, rng);
        w32(m, kNodeRecs + 16 * i + 12, f);
    }
    return bones;
}

}  // namespace

TEST_CASE("game(render_mesh): _rpSkinMatrixUpdating _rpSkinMatrixUpdating equals its recompiled body (VU0 palette)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46B510u};
    for (u32 i = 0; i < 400; ++i) {
        put_atomic_world(m, rng);
        fill_random(m, kPalette, 0x1000, rng);
        put_skin(m, rng, chance(rng, 80));
        pair(m, PAIR(fn__rpSkinMatrixUpdating_0046b510), {sx(kAtomic), sx(kSkin), 0, 0}, i, "_rpSkinMatrixUpdating", {{kSkinGlobals, 0x60}});
    }
    // rule: no hierarchy -> identity matrices with flags | 0x20003
    put_atomic_world(m, rng);
    const u32 bones = put_skin(m, rng, false);
    pair(m, PAIR(fn__rpSkinMatrixUpdating_0046b510), {sx(kAtomic), sx(kSkin), 0, 0}, 1, "_rpSkinMatrixUpdating rule", {{kSkinGlobals, 0x60}});
    for (u32 b = 0; b < bones; ++b) {
        const u32 p = kPalette + 64 * b;
        CHECK(r32(m, p + 0) == 0x3F800000u);
        CHECK(r32(m, p + 20) == 0x3F800000u);
        CHECK(r32(m, p + 40) == 0x3F800000u);
        CHECK(r32(m, p + 4) == 0);
        CHECK((r32(m, p + 12) & 0x20003u) == 0x20003u);
    }
}

TEST_CASE("game(render_mesh): the skin palette uploads sub_46B8E0 / sub_46EB90 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46EB90u};
    for (u32 i = 0; i < 400; ++i) {
        // partitioned upload of one mesh
        const AtomWorld a = put_atomic_world(m, rng);
        put_skin(m, rng, true);
        fill_floats(m, kPalette, 16 * 64, rng);
        w32(m, 0x95DE38u, kPartition);
        const u32 per = 1 + rng() % 12;
        w32(m, kPartition, per);
        w32(m, kPartition + 12, kSlotMap);
        w32(m, kPartition + 16, kMeshTable);
        w32(m, kPartition + 20, kRanges);
        for (u32 k = 0; k < 64; ++k) w8(m, kSlotMap + k, static_cast<u8>(rng() % per));
        for (u32 k = 0; k < 8; ++k) {
            w8(m, kMeshTable + 2 * k, static_cast<u8>(rng() % 4));
            w8(m, kMeshTable + 2 * k + 1, static_cast<u8>(rng() % 3));
            w8(m, kRanges + 2 * k, static_cast<u8>(rng() % 32));
            w8(m, kRanges + 2 * k + 1, static_cast<u8>(rng() % 5));
        }
        const u32 mesh = kHeader + 16 + 12 * (rng() % a.meshes);
        w32(m, kPipe + mesh::pd::kMesh, mesh);
        w32(m, kPipe + mesh::pd::kMeshHeader, kHeader);
        Hw hw = put_dma(m, rng);
        pair(m, PAIR(fn_sub_46B8E0_0046b8e0), {sx(kPipe), 0, 0, 0}, i, "sub_46B8E0", kRegDma, hw);

        // the skinned atomic's set-up
        put_atomic_world(m, rng);
        put_skin(m, rng, chance(rng, 85));
        if (chance(rng, 10)) {  // no meshes: returns 0 after the resEntry array
            w16(m, kHeader + 4, 0);
            w32(m, kResArray, 0);
        }
        hw = put_dma(m, rng);
        pair(m, PAIR(fn_sub_46EB90_0046eb90), {sx(kPipe), sx(kMatRef), 0, 0}, i, "sub_46EB90", kRegDma, hw);
    }
}

// =========================================================================================================
// openVU1SetupPktNew and the texture cache entry
// =========================================================================================================
namespace {

constexpr u32 kTexCache = 0x0077F200u;
constexpr u32 kClutWords = 0x009649F0u;
const std::vector<Region> kRegTex = {{kTplLo, kTplHi - kTplLo}, {kWinLo, kWinLen}, {kTexCache, 0x40}, {kClutWords, 0x180}};
constexpr u32 kRaster = kWorld + 0x9000, kSlots = kWorld + 0x9800;
// Callbacks of the emitted set: a leaf (sub_4A2BA0, returns 1) and a non-leaf that spills $ra (sub_1F1C50).
constexpr u32 kLeafCb = 0x4A2BA0u, kNonLeafCb = 0x1F1C50u;

// A raster with its sky extension, the cache globals and the GS shadow words the access reads.
void put_raster(Machine& m, std::mt19937& rng) {
    fill_random(m, kRaster, 0x200, rng);
    fill_random(m, kSlots, 0x100, rng);
    fill_random(m, kTexCache, 0x40, rng);
    fill_random(m, kClutWords, 0x180, rng);
    const u32 ext = 0x40 + 4 * (rng() % 8);
    w32(m, gpv(mesh::kGpRasterExt), ext);
    w32(m, kRaster + 0, chance(rng, 50) ? kRaster : rng());
    w32(m, kRaster + 4, chance(rng, 90) ? kWorld + 0xA000 : 0);
    w8(m, kRaster + 32, static_cast<u8>(chance(rng, 80) ? (rng() & 0x7Fu) : rng()));
    w32(m, kRaster + ext + 88, chance(rng, 75) ? kSlots + 12 * (rng() % 16) : 0);
    w32(m, kRaster + ext + 16, rng() % 0x4000);
    w8(m, kRaster + ext + 23, static_cast<u8>(chance(rng, 50) ? 0 : rng()));
    w32(m, kTexCache + 0x00, chance(rng, 80) ? 1u : 0u);
    w32(m, kTexCache + 0x14, kSlots);
    w32(m, kTexCache + 0x20, chance(rng, 50) ? kLeafCb : kNonLeafCb);
    w32(m, kTexCache + 0x24, chance(rng, 40) ? kRaster : rng());
    w32(m, kTexCache + 0x28, rng() % 2);
    w32(m, gpv(mesh::kGpLastRaster), chance(rng, 30) ? 0xFFFFFFFFu : rng());
    w32(m, gpv(-16856), chance(rng, 50) ? 0 : rng());
    w32(m, gpv(-17016), rng());
    w64(m, gpv(mesh::kGpTex1), rng64(rng));
}

}  // namespace

TEST_CASE("game(render_mesh): openVU1SetupPktNew openVU1SetupPktNew equals its recompiled body (object packet)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4EC2B0u};
    for (u32 i = 0; i < 500; ++i) {
        fill_random(m, kWorld, 0x5000, rng);
        Hw hw = put_dma(m, rng);
        const u32 matrix = chance(rng, 85) ? kWorld + 0x100 + 16 * (rng() % 8) : 0;
        const u32 lights = kWorld + 0x1000 + 16 * (rng() % 8);
        const u32 nq = chance(rng, 80) ? rng() % 24 : rng() % 125;
        const auto p = pair(m, PAIR(fn_openVU1SetupPktNew_004ec2b0), {sx(matrix), sx(lights), nq, 0}, i, "openVU1SetupPktNew", kRegDma, hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
}

TEST_CASE("game(render_mesh): the texture cache entry sub_4F0F30 / RpSkyTexCacheAccessRaster RpSkyTexCacheAccessRaster equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4F1020u};
    for (u32 i = 0; i < 800; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        put_raster(m, rng);
        Hw hw = put_dma(m, rng);
        pair(m, PAIR(fn_sub_4F0F30_004f0f30), {sx(kRaster), 0, 0, 0}, i, "sub_4F0F30", kRegTex, hw);
        put_raster(m, rng);
        hw = put_dma(m, rng);
        const u64 mode = chance(rng, 70) ? 0 : (chance(rng, 80) ? 1 : rng64(rng));
        pair(m, PAIR(fn_RpSkyTexCacheAccessRaster_004f1020), {sx(kRaster), mode, 0, 0}, i, "RpSkyTexCacheAccessRaster", kRegTex, hw);
    }
}

// =========================================================================================================
// The material bridge, the dispatcher, the object node and the atomic render callback
// =========================================================================================================
namespace {

constexpr u32 kTexture = kWorld + 0xB000, kMatPvt = kWorld + 0xC800, kCodeArray = kWorld + 0xC900;
constexpr u32 kMaterial = kWorld + 0xCA00, kRing = kWorld + 0xD000;
constexpr u32 kResEntries2 = kWorld + 0xD400;  // more resEntries (one per mesh)
constexpr u32 kBridgeFn = 0x4A0E00u;
constexpr u32 kLeafOne = 0x4A2BA0u, kLeafZero = 0x4A35B0u;  // callbacks of the emitted set returning 1 / 0
const std::vector<Region> kRegBridge = {{kTplLo, kTplHi - kTplLo}, {kWinLo, kWinLen}, {kTexCache, 0x40}, {kClutWords, 0x180},
                                        {kRwGlobals, 0x200}, {kSkinGlobals, 0x60}};

// The material side of a mesh: material pipeline private data (code array, VIF offset), the material and its
// texture / raster, the resEntries, the GS shadows and camera words the bridge reads, the reference ring.
void put_material_world(Machine& m, std::mt19937& rng, u32 meshes) {
    put_raster(m, rng);
    fill_random(m, kWorld + 0xB000, 0x3000, rng);
    w32(m, kTexture, kRaster);
    w32(m, kTexture + 80, chance(rng, 70) ? (rng() & 0xFFFFu) | (pick(rng, {0, 1, 3}) << 8) | (pick(rng, {0, 1, 3}) << 12) : rng());
    w32(m, kMatPvt + 20, rng() & 0x3FFu);
    w32(m, kMatPvt + 24, kCodeArray);
    for (u32 k = 0; k < 8; ++k) w32(m, kCodeArray + 4 * k, chance(rng, 80) ? 0x5CD000u + 0x100 * k : rng());
    w32(m, gpv(mesh::kGpResidentProgram), chance(rng, 40) ? 0x5CD000u + 0x100 * (rng() % 8) : rng());
    // material: texture, colour, pipeline, surface properties
    w32(m, kMaterial + 0, chance(rng, 75) ? kTexture : 0);
    w32(m, kMaterial + 4, chance(rng, 50) ? (rng() | 0xFF000000u) : rng());
    w32(m, kMaterial + 8, 0);
    fill_floats(m, kMaterial + 12, 3, rng);
    for (u32 i = 0; i < meshes; ++i) w32(m, kHeader + 16 + 12 * i + 8, kMaterial);
    // resEntries: one per mesh slot
    for (u32 i = 0; i < 4; ++i) {
        const u32 r = kResEntries2 + 0x40 * i;
        w32(m, kResArray + 4 + 4 * i, r);
        w32(m, r + 24, rng() % 4);
        w32(m, r + 28, chance(rng, 40) ? 0 : rng() % 4);
        w32(m, r + 32, kWorld + 0xE000 + 0x100 * i);
    }
    // GS shadows, render flags, camera words
    w64(m, gpv(mesh::kGpRenderFlags), rng64(rng));
    w64(m, gpv(mesh::kGpTest), rng64(rng));
    w64(m, gpv(mesh::kGpClamp), rng64(rng));
    w32(m, gpv(mesh::kGpCullMode), chance(rng, 50) ? 0 : 1);
    w32(m, gpv(mesh::kGpFogEnabled), chance(rng, 50) ? 0 : 1);
    w32(m, gpv(mesh::kGpCamProjection), chance(rng, 50) ? 3 : rng() % 3);
    w32(m, gpv(mesh::kGpClipLo), rng());
    w32(m, gpv(mesh::kGpLastRaster), chance(rng, 30) ? kRaster : (chance(rng, 50) ? 0xFFFFFFFFu : 0));
    // the packet layer's reference ring (_rwDMAAddPURef)
    w32(m, gpv(-17260), kRing);
    const u16 size = static_cast<u16>(8 + rng() % 32);
    w16(m, gpv(-20292), size);
    // entries are resEntry use counts (resEntry + 24), as _rwDMAAddPURef stores them and the packet layer's
    // reference flush (sub_4D4280, from _rwDMAClosePkt) walks them; the write index never meets the flush index
    for (u32 k = 0; k < 64; ++k) w32(m, kRing + 4 * k, kResEntries2 + 0x40 * (k % 4) + 24);
    w16(m, gpv(-17268), static_cast<u16>(rng() % (size - 2)));
    w16(m, gpv(-17264), static_cast<u16>(size - 1));
}

// One mesh's PipeData as PS2AllNodeBody fills it.
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

}  // namespace

TEST_CASE("game(render_mesh): RpMeshPS2AllBridgeCallBack equals its recompiled body (material packet, DI/EI, refs)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A0E00u};
    int textured = 0, programs = 0, firsts = 0;
    for (u32 i = 0; i < 800; ++i) {
        const AtomWorld a = put_atomic_world(m, rng);
        put_material_world(m, rng, a.meshes);
        const u32 mi = rng() % a.meshes;
        put_mesh_pipe(m, rng, mi);
        Hw hw = put_dma(m, rng);
        const u32 resident = r32(m, gpv(mesh::kGpResidentProgram));
        const u32 res = r32(m, kResArray + 4 + 4 * mi);
        const u32 uses = r32(m, res + 28);
        const auto p = pair(m, PAIR(fn_RpMeshPS2AllBridgeCallBack_004a0e00), {sx(kPipe), 0, 0, 0}, i, "RpMeshPS2AllBridgeCallBack",
                            kRegBridge, hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
        // rules (22_rendering.md section 3.2): the VU1 code index from transType, the program call when not resident
        const u8 tt = m.at(kPipe + mesh::pd::kTransType)[0];
        const u8 index = static_cast<u8>(((tt & 0x20) >> 5) | ((tt & 0x18) >> 2));
        CHECK(m.at(kPipe + mesh::pd::kVu1CodeIndex)[0] == index);
        CHECK(r32(m, gpv(mesh::kGpResidentProgram)) == r32(m, kCodeArray + 4 * index));
        programs += resident != r32(m, kCodeArray + 4 * index);
        textured += r32(m, kPipe + mesh::pd::kTexture) != 0;
        firsts += uses == 0;
        CHECK((r32(m, res + 28) == uses + 1 || r32(m, res + 28) == 1));  // 1 after a reference flush in the packet layer
    }
    MESSAGE("bridge: " << textured << " textured, " << programs << " program uploads, " << firsts << " first uses");
}

TEST_CASE("game(render_mesh): the skin bridge dispatcher sub_46EA80 equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46EA80u};
    for (u32 i = 0; i < 300; ++i) {
        const AtomWorld a = put_atomic_world(m, rng);
        put_material_world(m, rng, a.meshes);
        put_mesh_pipe(m, rng, rng() % a.meshes);
        // the material extension: none, or an effect 0..3 (bridge table 0x6B4EE4)
        const u32 off = 0x20 + 4 * (rng() % 4);
        w32(m, gpv(mesh::kGpSkinGeomExt), off);
        w32(m, kMaterial + off, chance(rng, 30) ? 0 : kWorld + 0xC000);
        w32(m, kWorld + 0xC000 + 128, rng() % 4);
        // the bridge table 0x6B4EE4 (the PDS skin bridges in the game): the stock bridge, a leaf, a non-leaf
        for (u32 k = 0; k < 4; ++k) w32(m, 0x6B4EE4u + 4 * k, pick(rng, {kBridgeFn, kBridgeFn, kLeafOne, kNonLeafCb}));
        Hw hw = put_dma(m, rng);
        std::vector<Region> regions = kRegBridge;
        regions.push_back({0x6B4EE0u, 0x20});
        pair(m, PAIR(fn_sub_46EA80_0046ea80), {sx(kPipe), 0, 0, 0}, i, "sub_46EA80", regions, hw);
        CHECK(r32(m, kMatPvt + 24) == kCodeArray);  // restored
    }
}

namespace {

constexpr u32 kNode = kWorld + 0xF000, kNodePvt = kWorld + 0xF100, kParams = kWorld + 0xF200, kDefLights = kWorld + 0xF300;
constexpr u32 kPipeline = kWorld + 0xF400, kPipeNode = kWorld + 0xF480, kResList = kWorld + 0xF500;

// The object node world on top of the atomic / material worlds: node private data (callbacks, the default light
// block, its VU1 address, the node material pipeline), a material pipeline (pipeline +8 -> node +20 -> the
// PS2AllMat private data), the global default pipeline, the resource list head, the atomic's resEntries linked.
void put_node_world(Machine& m, std::mt19937& rng, const AtomWorld& a, bool stock_setup) {
    fill_random(m, kNode, 0x700, rng);
    w32(m, kNode + 20, kNodePvt);
    w32(m, kNodePvt + 16, stock_setup ? 0x4A09D0u : pick(rng, {kLeafOne, kLeafOne, kLeafZero}));
    w32(m, kNodePvt + 20, pick(rng, {0, kLeafOne, kNonLeafCb}));
    w32(m, kNodePvt + 24, chance(rng, 30) ? kPipeline : 0);
    w32(m, kNodePvt + 28, rng() & 0x3FFu);
    w32(m, kNodePvt + 36, kDefLights);
    w32(m, kParams, kAtomic);
    w32(m, kPipeline + 8, kPipeNode);
    w32(m, kPipeNode + 20, kMatPvt);
    w32(m, kMatPvt + 0, chance(rng, 70) ? 0 : kLeafOne);         // instance test callback
    w32(m, kMatPvt + 12, chance(rng, 60) ? kBridgeFn : kLeafOne);  // the bridge
    w32(m, kMatPvt + 16, pick(rng, {0, kLeafOne, kNonLeafCb}));    // post-mesh
    w32(m, kMaterial + 8, chance(rng, 50) ? kPipeline : 0);
    // the global default material pipeline (PS2All module globals +68) and the default atomic pipeline (+60)
    const u32 modoff = 0x80 + 4 * (rng() % 8);
    w32(m, gpv(mesh::kGpRwGlobalsOffset), modoff);
    w32(m, kRwGlobals + modoff + 68, kPipeline);
    // the resource list: RW globals + gp-17408 -> +36 = the list head (a node {next, prev})
    const u32 resoff = 0x100 + 4 * (rng() % 8);
    w32(m, gpv(mesh::kGpResList), resoff);
    w32(m, kRwGlobals + resoff + 36, kResList);
    w32(m, kResList, kResList + 0x40);
    w32(m, kResList + 4, kResList);
    w32(m, kResList + 0x40, kResList);
    w32(m, kResList + 0x44, kResList);
    for (u32 i = 0; i < 4; ++i) {  // each resEntry linked between two cells (next, prev at +0 / +4)
        const u32 r = kResEntries2 + 0x40 * i;
        w32(m, r + 0, chance(rng, 80) ? kResList + 0x80 + 0x10 * i : 0);
        w32(m, r + 4, kResList + 0xC0 + 0x10 * i);
    }
    // the geometry is native (no instance test) or instance-stable: identifiers equal, no locks, no morph change
    if (chance(rng, 50)) {
        w32(m, kGeometry + 8, r32(m, kGeometry + 8) | 0x01000000u);
    } else {
        w32(m, kGeometry + 8, r32(m, kGeometry + 8) & ~0x01000000u);
        const u32 ident = (r32(m, kGeometry + 8) & 0x9F) << 16 | u32{m.at(kGeometry + 24)[0]} << 24 | (r32(m, kHeader + 4) >> 16);
        w32(m, kResEntry + 40, ident);
        w32(m, kResArray + 4, kResEntry);
        w16(m, kGeometry + 12, 0);
        w32(m, kAtomic + 76, r32(m, kAtomic + 76) & ~3u);
        w32(m, kResEntry + 0, chance(rng, 80) ? kResList + 0x80 : 0);
        w32(m, kResEntry + 4, kResList + 0xC0);
        w32(m, kResEntry + 24, rng() % 4);
        w32(m, kResEntry + 28, rng() % 3);
        w32(m, kResEntry + 32, kWorld + 0xE000);
    }
    w32(m, gpv(mesh::kGpLightCount), 0);
    (void)a;
}

}  // namespace

TEST_CASE("game(render_mesh): PS2AllNodeBody PS2AllNodeBody equals its recompiled body (stock atomic, bridge, callbacks)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x49F5D0u};
    for (u32 i = 0; i < 500; ++i) {
        const AtomWorld a = put_atomic_world(m, rng);
        put_material_world(m, rng, a.meshes);
        put_node_world(m, rng, a, chance(rng, 75));
        Hw hw = put_dma(m, rng);
        const auto p = pair(m, PAIR(fn_PS2AllNodeBody_0049f5d0), {sx(kNode), sx(kParams), 0, 0}, i, "PS2AllNodeBody", kRegBridge, hw);
        CHECK(gpr_of(p.first, GPR_V0) == 1);
    }
}

namespace {
// The draw observer (mesh.h): host records of what was serialised. Both runs of a pair call it (the recompiled
// node reaches the hand bridge through the dispatch table), and the pair still compares equal: no guest effect.
struct DrawLog {
    int objects = 0, skins = 0, meshes = 0, textured = 0, bad = 0;
};
DrawLog g_log;
Machine* g_obs_machine = nullptr;
void on_object(EEContext&, const mesh::ObjectSetup& o) {
    ++g_log.objects;
    if (o.lights != 0x95DFC0u && o.light_qw != 2) ++g_log.bad;  // the block header (or the node default, 2 qw)
}
void on_skin(EEContext&, const mesh::SkinPalette&) { ++g_log.skins; }
void on_mesh(EEContext&, const mesh::MeshDraw& d) {
    ++g_log.meshes;
    g_log.textured += d.texture != 0;
    const u8 tt = d.trans_type;
    // 22_rendering.md section 3.2: the code index and the program it names; PRIM in the GIF tag
    if (d.vu1_code_index != (((tt & 0x20) >> 5) | ((tt & 0x18) >> 2))) ++g_log.bad;
    if (d.vu1_program != r32(*g_obs_machine, kCodeArray + 4u * d.vu1_code_index)) ++g_log.bad;
    if (((d.gif_tag_lo >> 47) & 0x7FF) != ((r64(*g_obs_machine, gpv(mesh::kGpRenderFlags)) | d.prim_type) & 0x7FF)) ++g_log.bad;
    if (d.material != kMaterial || d.res_data != r32(*g_obs_machine, d.res_entry + 32)) ++g_log.bad;
}
}  // namespace

TEST_CASE("game(render_mesh): the draw observer reports each object and mesh draw without changing guest state") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x0B5E7u};
    const mesh::DrawObserver obs{&on_object, &on_skin, &on_mesh};
    g_obs_machine = &m;
    mesh::set_draw_observer(&obs);
    g_log = {};
    for (u32 i = 0; i < 200; ++i) {
        const AtomWorld a = put_atomic_world(m, rng);
        put_material_world(m, rng, a.meshes);
        put_node_world(m, rng, a, true);
        w32(m, kNodePvt + 16, 0x4A09D0u);
        w32(m, kMatPvt + 12, kBridgeFn);
        Hw hw = put_dma(m, rng);
        pair(m, PAIR(fn_PS2AllNodeBody_0049f5d0), {sx(kNode), sx(kParams), 0, 0}, i, "PS2AllNodeBody observed", kRegBridge, hw);
    }
    mesh::set_draw_observer(nullptr);
    MESSAGE("observer: " << g_log.objects << " objects, " << g_log.meshes << " mesh draws (" << g_log.textured << " textured)");
    CHECK(g_log.objects == 2 * 200);
    CHECK(g_log.meshes > 0);
    CHECK(g_log.bad == 0);
}

TEST_CASE("game(render_mesh): AtomicDefaultRenderCallBack AtomicDefaultRenderCallBack equals its recompiled body (RxPipelineExecute)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x490860u};
    for (u32 i = 0; i < 300; ++i) {
        const AtomWorld a = put_atomic_world(m, rng);
        put_material_world(m, rng, a.meshes);
        put_node_world(m, rng, a, true);
        // a pipeline whose first node is the PS2All object node: pipeline {.., +8 nodes} -> node {+0 definition
        // (+4 body), ..., +20 private}; RxPipelineExecute calls the body with (node, &data at 0x965A90); the heap
        // (gp-16832) needs no reset (+24 = 0)
        const u32 pipe = kWorld + 0xF600, def = kWorld + 0xF680, heap = kWorld + 0xF6C0;
        fill_random(m, pipe, 0x100, rng);
        w32(m, pipe + 8, kNode);
        w32(m, kNode + 0, def);
        w32(m, def + 4, 0x49F5D0u);
        w32(m, gpv(-16832), heap);
        w32(m, heap + 24, 0);
        w32(m, kAtomic + 108, chance(rng, 70) ? pipe : 0);
        const u32 modoff = r32(m, gpv(mesh::kGpRwGlobalsOffset));
        w32(m, kRwGlobals + modoff + 60, pipe);
        Hw hw = put_dma(m, rng);
        std::vector<Region> regions = kRegBridge;
        regions.push_back({0x965A40u, 0x80});  // RxPipelineExecute's execution context
        pair(m, PAIR(fn_AtomicDefaultRenderCallBack_00490860), {sx(kAtomic), 0, 0, 0}, i, "AtomicDefaultRenderCallBack", regions, hw);
    }
}

TEST_CASE("game(render_mesh): pair count") { MESSAGE("render_mesh pairs: " << g_pairs); }

#endif  // P3FES_GAME_HAVE_GENERATED
