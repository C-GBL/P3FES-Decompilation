// Phase 5 pair tests for the render_core3 slice (game/src/render/core3.cpp): RenderWare's core and the PS2 driver below
// the draw path, third pass -- [rwcore] matrices / frames / the resource heap / cameras / rasters / images, [rt2d],
// [renderstate], [raster], [upload], [im3d], [rxheap] (docs/ANALYSIS/22_rendering.md). Each hand-written function and
// the recompiled body it replaces run on identical guest machines built from random structures (frame trees, heap
// chains, matrices, raster / image / texture records, Rt2d paths, pipelines), with the device and plugin function
// pointers aimed at callbacks of the emitted set: leaves (identity, `v0 = a1`, 1, 0) and a non-leaf that spills $ra
// below the $sp it receives.
//
// Stricter than the Outcome (as test_render_ptank.cpp): per pair this file compares EVERY general register in 128
// bits, HI/LO, all FPU registers, ACC, FCR31 and the whole VU0 state at the return, the whole register file (GPRs,
// HI/LO, SA, FPRs, FCR31) and the cycle count at EVERY check point, the bus access log, the scratchpad, the world
// region of the case, the RW globals window (0x95E000..0x962000), the gp window, low memory (the retail error paths
// that continue with a null pointer), the WHOLE stack window (live and dead: the hand versions write the original's
// spills), the virtual cycles, the check-point and syscall counts. FPRs, ACC, HI/LO and VU0 start random, so a
// register the original leaves alone must stay alone. Host-side checks restate documented behaviour (core3.h).
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/game/core3.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
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
P3FES_DECL_PAIR(fn_sub_4C2FB0_004c2fb0)
P3FES_DECL_PAIR(fn_sub_4C33D0_004c33d0)
P3FES_DECL_PAIR(fn_sub_4C35D0_004c35d0)
P3FES_DECL_PAIR(fn_sub_4C3760_004c3760)
P3FES_DECL_PAIR(fn_sub_4C6BE0_004c6be0)
P3FES_DECL_PAIR(fn_sub_4C6C60_004c6c60)
P3FES_DECL_PAIR(fn_sub_4C6D60_004c6d60)
P3FES_DECL_PAIR(fn_sub_4C6E60_004c6e60)
P3FES_DECL_PAIR(fn_sub_4C6F30_004c6f30)
P3FES_DECL_PAIR(fn_RwCameraEndUpdate_004c9d00)
P3FES_DECL_PAIR(fn_RwCameraBeginUpdate_004c9d10)
P3FES_DECL_PAIR(fn_RwCameraClear_004c9e90)
P3FES_DECL_PAIR(fn_RwCameraShowRaster_004c9ed0)
P3FES_DECL_PAIR(fn_sub_4CB2F0_004cb2f0)
P3FES_DECL_PAIR(fn_sub_4CB7F0_004cb7f0)
P3FES_DECL_PAIR(fn_sub_4CDC70_004cdc70)
P3FES_DECL_PAIR(fn_sub_4CDCE0_004cdce0)
P3FES_DECL_PAIR(fn_sub_4CDD50_004cdd50)
P3FES_DECL_PAIR(fn_sub_4CDE00_004cde00)
P3FES_DECL_PAIR(fn_RwRasterShowRaster_004cdfe0)
P3FES_DECL_PAIR(fn_sub_4CE050_004ce050)
P3FES_DECL_PAIR(fn_sub_4CE200_004ce200)
P3FES_DECL_PAIR(fn_sub_4CF3B0_004cf3b0)
P3FES_DECL_PAIR(fn_sub_4CF4C0_004cf4c0)
P3FES_DECL_PAIR(fn_sub_4D0FD0_004d0fd0)
P3FES_DECL_PAIR(fn_sub_4D13E0_004d13e0)
P3FES_DECL_PAIR(fn_sub_4C2330_004c2330)
P3FES_DECL_PAIR(fn_sub_4CE3A0_004ce3a0)
P3FES_DECL_PAIR(fn_sub_4CE9A0_004ce9a0)
P3FES_DECL_PAIR(fn_sub_4CEC10_004cec10)
P3FES_DECL_PAIR(fn_RxPipelineExecute_004f2e70)
P3FES_DECL_PAIR(fn_sub_4F3150_004f3150)
P3FES_DECL_PAIR(fn_sub_4F5D30_004f5d30)
P3FES_DECL_PAIR(fn_sub_4F62D0_004f62d0)
P3FES_DECL_PAIR(fn_sub_4F6890_004f6890)
P3FES_DECL_PAIR(fn_sub_4F1ED0_004f1ed0)
P3FES_DECL_PAIR(fn_sub_4F1FD0_004f1fd0)
P3FES_DECL_PAIR(fn_sub_4F2150_004f2150)
P3FES_DECL_PAIR(fn_sub_4D78B0_004d78b0)
P3FES_DECL_PAIR(fn_sub_4EEC20_004eec20)
P3FES_DECL_PAIR(fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020)
P3FES_DECL_PAIR(fn_sub_4EF770_004ef770)
P3FES_DECL_PAIR(fn_sub_4DD480_004dd480)
P3FES_DECL_PAIR(fn_sub_4DD700_004dd700)
P3FES_DECL_PAIR(fn_sub_4DDAA0_004ddaa0)
P3FES_DECL_PAIR(fn_sub_4DDD30_004ddd30)
P3FES_DECL_PAIR(fn_sub_4DECE0_004dece0)
P3FES_DECL_PAIR(fn_sub_4DEF10_004def10)
P3FES_DECL_PAIR(fn_sub_4DEFD0_004defd0)
P3FES_DECL_PAIR(fn_sub_4E2F10_004e2f10)
P3FES_DECL_PAIR(fn_sub_4E4A90_004e4a90)
P3FES_DECL_PAIR(fn_sub_4E4C20_004e4c20)
P3FES_DECL_PAIR(fn_sub_4A55B0_004a55b0)
P3FES_DECL_PAIR(fn_sub_4A9A70_004a9a70)
P3FES_DECL_PAIR(fn_sub_4AAB40_004aab40)
P3FES_DECL_PAIR(fn_sub_4AAC70_004aac70)
P3FES_DECL_PAIR(fn_sub_4AAD50_004aad50)
P3FES_DECL_PAIR(fn_sub_4AB0C0_004ab0c0)
P3FES_DECL_PAIR(fn_sub_4AB910_004ab910)
P3FES_DECL_PAIR(fn_sub_4ABA20_004aba20)
P3FES_DECL_PAIR(fn_sub_4AC020_004ac020)
P3FES_DECL_PAIR(fn_sub_4AC390_004ac390)
P3FES_DECL_PAIR(fn_sub_4AE690_004ae690)
P3FES_DECL_PAIR(fn_sub_4AB8C0_004ab8c0)
P3FES_DECL_PAIR(fn_sub_4AB6A0_004ab6a0)
P3FES_DECL_PAIR(fn_sub_4ABD50_004abd50)
P3FES_DECL_PAIR(fn_sub_4AAE60_004aae60)
P3FES_DECL_PAIR(fn_sub_4AA2C0_004aa2c0)
P3FES_DECL_PAIR(fn_sub_4AD750_004ad750)
P3FES_DECL_PAIR(fn_sub_4AE2F0_004ae2f0)
P3FES_DECL_PAIR(fn_sub_4A6600_004a6600)
P3FES_DECL_PAIR(fn_sub_4ACE70_004ace70)
P3FES_DECL_PAIR(fn_sub_4AF9D0_004af9d0)
P3FES_DECL_PAIR(fn_sub_4ADF30_004adf30)
P3FES_DECL_PAIR(fn_sub_4AE960_004ae960)
P3FES_DECL_PAIR(fn_sub_4AE940_004ae940)
P3FES_DECL_PAIR(fn_sub_4B5330_004b5330)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

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
constexpr u32 kWorld = 0x01900000u;  // the random records of a case
constexpr u32 kWorldLen = 0x20000u;
constexpr u32 kGpWindow = gpv(-20800);
constexpr u32 kGpWindowLen = 4000;
constexpr u32 kRwWindow = 0x0095E000u;  // the Rt2d globals, RwEngineInstance 0x960070 and the driver globals
constexpr u32 kRwWindowLen = 0x4000u;
constexpr u32 kLow = 0;  // retail error paths continue with a null matrix / record
constexpr u32 kLowLen = 0x400;
constexpr u32 kStackLo = kSp - kDeadStack;
constexpr u32 kStackLen = kDeadStack + 0x100;
constexpr u32 kEngine = 0x960070u;

// Callbacks of the emitted set (tests/game/CMakeLists.txt lists them).
constexpr u32 kIdentity = 0x489950u;  // `jr ra; move v0, a0`
constexpr u32 kSecond = 0x4B3710u;    // `jr ra; move v0, a1`
constexpr u32 kOne = 0x469A90u;       // `jr ra; li v0, 1`
constexpr u32 kZero = 0x4A35B0u;      // returns 0 (render_rw)
constexpr u32 kNonLeaf = 0x1F1C50u;   // spills $ra below its $sp, returns the word at gp-18968

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region> kBase = {{kWorld, kWorldLen}, {kGpWindow, kGpWindowLen}, {kRwWindow, kRwWindowLen}, {kLow, kLowLen}};

// --- guest RAM helpers -------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
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
u32 seed_of(int i, u32 salt) { return 0x9E3779B9u * static_cast<u32>(i + 1) ^ salt; }
// A 32-bit register value: mostly the value itself sign-extended, sometimes with garbage in the upper half (the
// functions compare whole registers where the original does).
u64 reg_of(u32 v, std::mt19937& rng, bool whole = false) {
    if (whole && chance(rng, 15)) return rng64(rng);
    return sx(v);
}
// A world pointer: word-aligned, inside the first `span` bytes of the world.
u32 wptr(std::mt19937& rng, u32 span = 0x8000u, u32 align = 16) { return kWorld + (rng() % (span / align)) * align; }
// Pointer soup: `words` words from `va`, a fraction of them pointers into [kWorld, kWorld + span), the rest random.
void soup(Machine& m, u32 va, u32 words, std::mt19937& rng, u32 span = 0x8000u) {
    for (u32 i = 0; i < words; ++i) {
        const u32 k = rng() % 10;
        w32(m, va + 4 * i, k < 4 ? wptr(rng, span, 4) : k < 6 ? rand_float(rng) : k < 8 ? rng() % 16 : rng());
    }
}
// The RW globals the core reads, in a fresh state for each case: zero, then the plugin offsets used here.
void reset_rw(Machine& m) { std::memset(m.at(kRwWindow), 0, kRwWindowLen); }

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

// The scripted hardware of a case and extra GPR inputs.
struct Hw {
    std::map<u32, u64> regs;
    std::map<u32, std::vector<u64>> reads;
    std::map<unsigned, u64> gpr_in;  // set after the randomised context ($t0.. for arguments 5..8)
};

class C3Hooks final : public RtHooks {
public:
    ScriptedBus bus_;
    int syscalls = 0;
    int checks = 0;
    int traps = 0;
    std::vector<RegSnap> snaps;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        RegSnap s;
        s.cycles = ctx.cycles;
        for (unsigned r = 0; r < 32; ++r) s.gpr[r] = ctx.gpr[r];
        s.hi = ctx.hi;
        s.lo = ctx.lo;
        s.sa = ctx.sa;
        s.fcr31 = ctx.fcr31;
        for (unsigned i = 0; i < 32; ++i) s.fpr[i] = ctx.fpr[i];
        snaps.push_back(s);
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { throw rt_test::FatalEvent{pc, what, &ctx}; }
};

Snap run_full(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Region>& regions, const Hw& hw) {
    C3Hooks hooks;
    hooks.bus_.regs = hw.regs;
    hooks.bus_.reads = hw.reads;
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

// Runs hand and recomp from the same machine state (the scratchpad and every region restored in between) and requires
// identical results everywhere. After the pair the recompiled run's output is in place.
std::pair<Snap, Snap> pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Hw& hw = {},
                           const std::vector<Region>& extra = {}) {
    // A region of 1 MiB or more (at most one: write_tracker.h tracks one range at a time) goes through a PairRange:
    // only the pages a body writes are copied and compared; the others are byte-copied as before.
    std::vector<Region> regions = kBase;
    const Region* big = nullptr;
    for (const Region& r : extra) {
        if (r.len >= (1u << 20)) {
            REQUIRE(big == nullptr);
            big = &r;
        } else {
            regions.push_back(r);
        }
    }
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    std::vector<std::vector<u8>> before;
    for (const Region& r : regions) before.push_back(m.bytes(r.va, r.len));
    const std::string label = std::string(what) + " seed " + std::to_string(seed);
    INFO(label);
    std::unique_ptr<PairRange> window;
    if (big) window = std::make_unique<PairRange>(m.at(big->va), m.at(big->va) + big->len);
    Snap h;
    try {
        h = run_full(m, hand, args, seed, regions, hw);
    } catch (const rt_test::FatalEvent& e) {
        MESSAGE("the hand run of " << label << " stopped at pc " << hex64(e.pc) << ": " << e.what);
        throw;
    }
    if (window) window->between();  // first: it keeps what the hand body left (the small regions overlap it)
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    Snap r = run_full(m, recomp, args, seed, regions, hw);
    ++g_pairs;
    if (window) {
        const std::size_t f = window->first_difference();
        INFO("window " << hex64(big->va) << ": first differing byte at " << hex64(big->va + f));
        CHECK(f == window->size());
    }
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

// Every pair of a test counts; a test reports its number.
struct Counter {
    const char* what;
    int start = g_pairs;
    explicit Counter(const char* w) : what(w) {}
    ~Counter() { MESSAGE(std::string(what) << ": " << (g_pairs - start) << " pairs"); }
};

}  // namespace


// =========================================================================================================
// [rwcore]
// =========================================================================================================
namespace {

// Every word a pointer into [kWorld, kWorld + span) (structures whose fields the code follows blindly).
void psoup(Machine& m, u32 va, u32 words, std::mt19937& rng, u32 span = 0x8000u) {
    for (u32 i = 0; i < words; ++i) w32(m, va + 4 * i, wptr(rng, span, 4));
}
u32 callback(std::mt19937& rng) { return pick(rng, {kIdentity, kSecond, kOne, kZero, kNonLeaf}); }
// A combine op: 0 / 1 / 2, sometimes a bad one or a whole register with garbage above bit 31.
u64 combine(std::mt19937& rng) {
    if (chance(rng, 8)) return rng64(rng);
    if (chance(rng, 8)) return pick(rng, {3, 7, 0xFFFFFFFFu});
    return rng() % 3;
}

// A frame tree in the world: frames of 0xC0 bytes from kWorld + 0x1000 (+3 flags, +4 parent, +16 modelling matrix,
// +80 LTM, +152 first child, +156 next sibling, +160 root). Returns the frames, root first.
std::vector<u32> put_frames(Machine& m, std::mt19937& rng, unsigned n) {
    std::vector<u32> f;
    const u32 base = kWorld + 0x1000;
    for (unsigned i = 0; i < n; ++i) {
        const u32 fr = base + 0xC0 * i;
        fill_floats(m, fr, 0xC0 / 4, rng);
        w8(m, fr + 3, static_cast<u8>(rng()));
        w32(m, fr + 152, 0);
        w32(m, fr + 156, 0);
        w32(m, fr + 160, base);
        f.push_back(fr);
        if (i == 0) {
            w32(m, fr + 4, 0);
            continue;
        }
        const u32 parent = f[rng() % i];
        w32(m, fr + 4, parent);
        // prepend to the parent's children
        w32(m, fr + 156, r32(m, parent + 152));
        w32(m, parent + 152, fr);
    }
    // the root's parent: never followed for the root itself (its LTM is a copy)
    return f;
}

// A resource heap: the heap record at kWorld (+4 the first-free hint), blocks with a 32-byte header {+0 heap, +4 next,
// +8 prev, +12 size, +16 used} from kWorld + 0x100. Returns the block headers.
std::vector<u32> put_heap(Machine& m, std::mt19937& rng, unsigned n) {
    soup(m, kWorld, 64, rng);
    std::vector<u32> b;
    u32 at = kWorld + 0x100;
    for (unsigned i = 0; i < n; ++i) {
        const u32 size = 32u * pick(rng, {0, 1, 1, 2, 3, 4, 6, 9, 16});
        soup(m, at, 8 + size / 4, rng);
        w32(m, at + 0, kWorld);
        w32(m, at + 8, i ? b.back() : 0);
        w32(m, at + 12, size);
        w32(m, at + 16, chance(rng, 50) ? 1u : chance(rng, 80) ? 0u : rng());
        if (i) w32(m, b.back() + 4, at);
        b.push_back(at);
        at += 32 + size;
    }
    w32(m, b.back() + 4, 0);
    const u32 k = rng() % 6;
    w32(m, kWorld + 4, k == 0 ? 0u : b[rng() % b.size()]);
    return b;
}

}  // namespace

TEST_CASE("game(render_core3): the matrix ops sub_4C33D0 / sub_4C35D0 / sub_4C3760 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("matrix ops");
    std::mt19937 rng{0x4C33D0u};
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_4C33D0", PAIR(fn_sub_4C33D0_004c33d0)}, {"sub_4C35D0", PAIR(fn_sub_4C35D0_004c35d0)},
                    {"sub_4C3760", PAIR(fn_sub_4C3760_004c3760)}, {"sub_4C2FB0", PAIR(fn_sub_4C2FB0_004c2fb0)}};
    for (const W& wr : ws) {
        for (int i = 0; i < 300; ++i) {
            fill_floats(m, kWorld, 0x200, rng);
            fill_random(m, kLow, kLowLen, rng);
            const u32 mat = kWorld + 0x100, v = kWorld + 0x40 + 4 * (rng() % 4);
            w32(m, mat + 12, rng());
            pair(m, wr.hand, wr.recomp, Args{sx(mat), sx(v), combine(rng), rng64(rng)}, seed_of(i, 0x4C33u), wr.name);
        }
    }
    // documented: post-concat scale multiplies column x of every row by scale.x; translate post-concat adds t to pos
    namespace fpu = ee::fpu;
    for (int i = 0; i < 40; ++i) {
        fill_floats(m, kWorld, 0x200, rng);
        const u32 mat = kWorld + 0x100, v = kWorld + 0x40;
        const u32 before = r32(m, mat + 48), sx0 = r32(m, v);
        pair(m, PAIR(fn_sub_4C33D0_004c33d0), Args{sx(mat), sx(v), 2, 0}, seed_of(i, 0x1u), "scale rule");
        CHECK(r32(m, mat + 48) == fpu::mul(before, sx0));
        const u32 p = r32(m, mat + 52), ty = r32(m, v + 4);
        pair(m, PAIR(fn_sub_4C35D0_004c35d0), Args{sx(mat), sx(v), 2, 0}, seed_of(i, 0x2u), "translate rule");
        CHECK(r32(m, mat + 52) == fpu::add(p, ty));
    }
}

TEST_CASE("game(render_core3): the resource heap sub_4C6D60 / sub_4C6E60 / sub_4C6F30 equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("resource heap");
    std::mt19937 rng{0x4C6F30u};
    for (int i = 0; i < 600; ++i) {
        put_heap(m, rng, 1 + rng() % 12);
        const u32 size = 32u * (rng() % 8) + (chance(rng, 30) ? rng() % 32 : 0u);
        pair(m, PAIR(fn_sub_4C6F30_004c6f30), Args{sx(kWorld), size, rng64(rng), rng64(rng)}, seed_of(i, 0x6F30u),
             "sub_4C6F30");
        const auto d = put_heap(m, rng, 1 + rng() % 12);
        const u32 blk1 = d[rng() % d.size()];
        pair(m, PAIR(fn_sub_4C6E60_004c6e60), Args{sx(blk1 + 32), rng64(rng)}, seed_of(i, 0x6E60u), "sub_4C6E60");
        const auto c = put_heap(m, rng, 1 + rng() % 12);
        const u32 blk2 = c[rng() % c.size()];
        pair(m, PAIR(fn_sub_4C6D60_004c6d60), Args{sx(blk2), 32u * (rng() % 4)}, seed_of(i, 0x6D60u), "sub_4C6D60");
    }
    // documented: an allocation returns header + 32 of a block marked used, at least `size` (rounded to 32) large
    for (int i = 0; i < 100; ++i) {
        put_heap(m, rng, 2 + rng() % 10);
        const u32 size = 32u * (rng() % 4);
        auto [h, r] = pair(m, PAIR(fn_sub_4C6F30_004c6f30), Args{sx(kWorld), size}, seed_of(i, 0x77u), "alloc rule");
        const u32 got = h.gpr[GPR_V0].u32[0];
        if (got) {
            CHECK(r32(m, got - 16) == 1);
            CHECK(r32(m, got - 20) >= size);
        }
    }
}

TEST_CASE("game(render_core3): the plugin calls sub_4C6BE0 / sub_4C6C60 / sub_4D13E0 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("plugin calls");
    std::mt19937 rng{0x4C6BE0u};
    for (int i = 0; i < 400; ++i) {
        reset_rw(m);
        soup(m, kWorld, 0x400, rng);
        const u32 off = 4u * (rng() % 64);
        w32(m, gpv(-17376), off);
        w32(m, gpv(-17312), off);
        w32(m, kEngine + off + 8, callback(rng));
        w32(m, kEngine + off + 16, callback(rng));
        w32(m, kEngine + off + 44, callback(rng));
        const Args a{reg_of(wptr(rng), rng, true), reg_of(wptr(rng), rng), rng64(rng), rng64(rng)};
        pair(m, PAIR(fn_sub_4C6BE0_004c6be0), a, seed_of(i, 0x6BE0u), "sub_4C6BE0");
        pair(m, PAIR(fn_sub_4C6C60_004c6c60), a, seed_of(i, 0x6C60u), "sub_4C6C60");
        pair(m, PAIR(fn_sub_4D13E0_004d13e0), a, seed_of(i, 0x13E0u), "sub_4D13E0");
    }
}

TEST_CASE("game(render_core3): the camera and raster entry points equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("camera / raster entry points");
    std::mt19937 rng{0x4C9D00u};
    for (int i = 0; i < 400; ++i) {
        reset_rw(m);
        psoup(m, kWorld, 0x400, rng);
        const u32 cam = kWorld + 0x9000;
        soup(m, cam, 32, rng);
        w32(m, cam + 24, callback(rng));
        w32(m, cam + 28, callback(rng));
        w32(m, cam + 96, wptr(rng));
        // the device's standard functions (0x9600B8 + 4 * index) and the resource lists of sub_4C4890
        for (u32 k = 0; k < 29; ++k) w32(m, 0x9600B8u + 4 * k, callback(rng));
        const u32 off = 0x100u + 4u * (rng() % 64);  // the lists outside the standard-function table
        w32(m, gpv(-17408), off);
        w32(m, kEngine + off + 32, wptr(rng));
        w32(m, kEngine + off + 36, wptr(rng));
        const Args a{sx(cam), rng64(rng), rng64(rng), rng64(rng)};
        pair(m, PAIR(fn_RwCameraBeginUpdate_004c9d10), a, seed_of(i, 0x9D10u), "RwCameraBeginUpdate");
        pair(m, PAIR(fn_RwCameraEndUpdate_004c9d00), a, seed_of(i, 0x9D00u), "RwCameraEndUpdate");
        pair(m, PAIR(fn_RwCameraClear_004c9e90), a, seed_of(i, 0x9E90u), "RwCameraClear");
        pair(m, PAIR(fn_RwCameraShowRaster_004c9ed0), a, seed_of(i, 0x9ED0u), "RwCameraShowRaster");
        const u32 ras = wptr(rng);
        const Args b{sx(ras), sx(wptr(rng)), sx(wptr(rng)), sx(wptr(rng))};
        Hw hw;
        hw.gpr_in[GPR_T0] = sx(wptr(rng));
        hw.gpr_in[GPR_T1] = sx(wptr(rng));
        pair(m, PAIR(fn_RwRasterShowRaster_004cdfe0), b, seed_of(i, 0xDFE0u), "RwRasterShowRaster");
        pair(m, PAIR(fn_sub_4CDC70_004cdc70), b, seed_of(i, 0xDC70u), "sub_4CDC70");
        pair(m, PAIR(fn_sub_4CDCE0_004cdce0), b, seed_of(i, 0xDCE0u), "sub_4CDCE0");
        pair(m, PAIR(fn_sub_4CDD50_004cdd50), b, seed_of(i, 0xDD50u), "sub_4CDD50", hw);
        pair(m, PAIR(fn_sub_4CDE00_004cde00), b, seed_of(i, 0xDE00u), "sub_4CDE00");
        // sub-raster: +33 bit 7 picks the path
        w8(m, ras + 33, static_cast<u8>(rng()));
        pair(m, PAIR(fn_sub_4CE050_004ce050), Args{sx(ras), b[1], b[2]}, seed_of(i, 0xE050u), "sub_4CE050");
        pair(m, PAIR(fn_sub_4CE200_004ce200), Args{reg_of(ras, rng, true), rng64(rng), rng64(rng)}, seed_of(i, 0xE200u),
             "sub_4CE200");
    }
}

TEST_CASE("game(render_core3): the frame hierarchy sub_4CB2F0 / sub_4CB7F0 / sub_4CF3B0 / sub_4CF4C0 equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("frame hierarchy");
    std::mt19937 rng{0x4CF4C0u};
    for (int i = 0; i < 400; ++i) {
        reset_rw(m);
        fill_floats(m, kWorld, 0x400, rng);
        const auto f = put_frames(m, rng, 1 + rng() % 10);
        w32(m, 0x96012Cu, chance(rng, 50) ? 0x96012Cu : f[rng() % f.size()] + 8);
        w32(m, 0x960130u, 0x96012Cu);
        const u32 fr = f[rng() % f.size()];
        pair(m, PAIR(fn_sub_4CF4C0_004cf4c0), Args{sx(f[0])}, seed_of(i, 0xF4C0u), "sub_4CF4C0");
        pair(m, PAIR(fn_sub_4CF3B0_004cf3b0), Args{sx(fr), rng() & 0xFFu, 0, 0}, seed_of(i, 0xF3B0u), "sub_4CF3B0");
        pair(m, PAIR(fn_sub_4CB2F0_004cb2f0), Args{sx(fr)}, seed_of(i, 0xB2F0u), "sub_4CB2F0");
        pair(m, PAIR(fn_sub_4CB7F0_004cb7f0), Args{sx(fr), sx(kWorld + 0x40), combine(rng)}, seed_of(i, 0xB7F0u),
             "sub_4CB7F0");
    }
    // documented: after sub_4CF4C0 a dirty root's LTM is its modelling matrix and the root's bits 0 / 2 are clear
    for (int i = 0; i < 40; ++i) {
        fill_floats(m, kWorld, 0x400, rng);
        const auto f = put_frames(m, rng, 1 + rng() % 4);
        w8(m, f[0] + 3, static_cast<u8>(rng() | 4));
        pair(m, PAIR(fn_sub_4CF4C0_004cf4c0), Args{sx(f[0])}, seed_of(i, 0x55u), "sync rule");
        CHECK(std::memcmp(m.at(f[0] + 16), m.at(f[0] + 80), 64) == 0);
        CHECK((*m.at(f[0] + 3) & 5) == 0);
    }
}

TEST_CASE("game(render_core3): RwTextureSetName sub_4D0FD0 equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("sub_4D0FD0");
    std::mt19937 rng{0x4D0FD0u};
    for (int i = 0; i < 500; ++i) {
        reset_rw(m);
        w32(m, 0x960140u, 0x524828u);  // strncpy
        w32(m, 0x960164u, 0x524388u);  // strlen
        fill_random(m, kWorld, 0x200, rng);
        const u32 len = pick(rng, {0, 1, 5, 30, 31, 32, 33, 40, 60});
        std::string name;
        for (u32 k = 0; k < len; ++k) name += static_cast<char>('A' + rng() % 26);
        m.put(kWorld + 0x100, name);
        pair(m, PAIR(fn_sub_4D0FD0_004d0fd0), Args{sx(kWorld + 0x20), sx(kWorld + 0x100)}, seed_of(i, 0xFD0u), "sub_4D0FD0");
        if (len < 32) CHECK(m.str(kWorld + 0x30) == name);
    }
}


TEST_CASE("game(render_core3): RwMatrixOrthoNormalize sub_4C2330 equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("sub_4C2330");
    std::mt19937 rng{0x4C2330u};
    for (int i = 0; i < 1500; ++i) {
        fill_floats(m, kWorld, 0x100, rng);
        const u32 src = kWorld + 0x100, dst = chance(rng, 20) ? src : kWorld + 0x200;
        fill_floats(m, src, 16, rng);
        // zero-length rows and (anti)parallel rows exercise every choice of the rebuilt row
        for (u32 row = 0; row < 3; ++row) {
            if (chance(rng, 15)) std::memset(m.at(src + 16 * row), 0, 12);
            if (chance(rng, 10)) std::memcpy(m.at(src + 16 * row), m.at(src + 16 * ((row + 1) % 3)), 12);
        }
        pair(m, PAIR(fn_sub_4C2330_004c2330), Args{sx(dst), sx(src), rng64(rng)}, seed_of(i, 0x2330u), "sub_4C2330");
    }
}

namespace {
// An RGBA8 image record at `rec` (+0 flags, +4 width, +8 height, +16 stride, +20 pixels) with random pixels.
void put_image(Machine& m, std::mt19937& rng, u32 rec, u32 pixels, u32 w, u32 h) {
    w32(m, rec + 0, rng());
    w32(m, rec + 4, w);
    w32(m, rec + 8, h);
    w32(m, rec + 12, 32);
    const u32 stride = 4 * w + 4 * (rng() % 3);
    w32(m, rec + 16, stride);
    w32(m, rec + 20, pixels);
    fill_random(m, pixels, stride * h + 16, rng);
}
}  // namespace

TEST_CASE("game(render_core3): the image resample sub_4CE3A0 / sub_4CE9A0 / sub_4CEC10 equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("image resample");
    std::mt19937 rng{0x4CEC10u};
    for (int i = 0; i < 800; ++i) {
        const u32 w = 1 + rng() % 12, h = 1 + rng() % 12;
        put_image(m, rng, kWorld, kWorld + 0x1000, w, h);
        fill_floats(m, kWorld + 0x100, 16, rng);
        // a span [x0, x1) inside the image, 16.16, x1 > x0
        const u32 x0 = rng() % (w << 16);
        const u32 x1 = x0 + 1 + rng() % ((w << 16) - x0);
        const u32 y0 = rng() % (h << 16);
        const u32 y1 = y0 + 1 + rng() % ((h << 16) - y0);
        Hw hw;
        hw.gpr_in[GPR_T0] = sx(kWorld + 0x100);
        pair(m, PAIR(fn_sub_4CE3A0_004ce3a0), Args{sx(kWorld), x0, x1, y0}, seed_of(i, 0xE3A0u), "sub_4CE3A0", hw);
        Hw hw2;
        hw2.gpr_in[GPR_T0] = y1;
        hw2.gpr_in[GPR_T1] = sx(kWorld + 0x100);
        pair(m, PAIR(fn_sub_4CE9A0_004ce9a0), Args{sx(kWorld), x0, x1, y0}, seed_of(i, 0xE9A0u), "sub_4CE9A0", hw2);
    }
    for (int i = 0; i < 150; ++i) {
        const u32 sw = 1 + rng() % 12, sh = 1 + rng() % 12, dw = 1 + rng() % 6, dh = 1 + rng() % 6;
        put_image(m, rng, kWorld, kWorld + 0x1000, dw, dh);
        put_image(m, rng, kWorld + 0x40, kWorld + 0x2000, sw, sh);
        pair(m, PAIR(fn_sub_4CEC10_004cec10), Args{sx(kWorld), sx(kWorld + 0x40)}, seed_of(i, 0xEC10u), "sub_4CEC10");
    }
    // documented: resampling to the same size keeps the pixels (each output pixel covers exactly one source pixel)
    for (int i = 0; i < 20; ++i) {
        const u32 sw = 1 + rng() % 4, sh = 1 + rng() % 4;
        put_image(m, rng, kWorld, kWorld + 0x1000, sw, sh);
        put_image(m, rng, kWorld + 0x40, kWorld + 0x2000, sw, sh);
        pair(m, PAIR(fn_sub_4CEC10_004cec10), Args{sx(kWorld), sx(kWorld + 0x40)}, seed_of(i, 0x99u), "same size");
        const u32 ds = r32(m, kWorld + 16), ss = r32(m, kWorld + 0x40 + 16);
        for (u32 y = 0; y < sh; ++y)
            CHECK(std::memcmp(m.at(kWorld + 0x1000 + ds * y), m.at(kWorld + 0x2000 + ss * y), 4 * sw) == 0);
    }
}


// =========================================================================================================
// [rxheap] [im3d]
// =========================================================================================================
namespace {

const std::vector<Region> kExecGlobals = {{0x965A00u, 0x100}};

// A pipeline at `pipe`: +8 the first node -> +0 its definition -> +4 the body (a callback of the emitted set), +16
// the state, +20 a list.
void put_pipeline(Machine& m, std::mt19937& rng, u32 pipe) {
    soup(m, pipe, 8, rng);
    const u32 node = pipe + 0x40, def = pipe + 0x60;
    w32(m, pipe + 8, node);
    w32(m, pipe + 16, rng() % 4);
    w32(m, node, def);
    w32(m, def + 4, pick(rng, {kIdentity, kSecond, kOne, kZero, kNonLeaf}));
}

// A pipeline to lock (sub_4F6890): +4 the list head node, nodes linked through +8, each {+0 its block, +4 the
// block's size}; the scratch array {+12 entries, +16 capacity, +20 count} of 8-byte records; +24 the "needs lock" flag.
void put_lockable(Machine& m, std::mt19937& rng, u32 p) {
    soup(m, p, 16, rng);
    const unsigned n = rng() % 4;
    u32 head = p + 0x100;
    w32(m, p + 4, head);
    u32 prev = head;
    for (unsigned k = 0; k <= n; ++k) {
        const u32 node = p + 0x100 + 0x20 * k;
        if (k) w32(m, prev + 8, node);
        w32(m, node + 0, p + 0x1000 + 0x200 * k);
        w32(m, node + 4, 64 + 16 * (rng() % 8));
        w32(m, node + 8, 0);
        prev = node;
    }
    w32(m, p + 12, p + 0x800);
    const u32 cap = rng() % 8, cnt = rng() % 8;
    w32(m, p + 16, cap);
    w32(m, p + 20, cnt);
    w32(m, p + 24, rng() % 2);
    fill_random(m, p + 0x800, 0x400, rng);
    fill_random(m, p + 0x1000, 0x1000, rng);
}

}  // namespace

TEST_CASE("game(render_core3): RxPipelineExecute and the pipeline lock equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("rxheap");
    std::mt19937 rng{0x4F2E70u};
    for (int i = 0; i < 600; ++i) {
        reset_rw(m);
        w32(m, 0x960180u, pick(rng, {kIdentity, kIdentity, kZero}));  // RwRealloc for sub_4F61C0: in place, or failing
        const u32 pipe = kWorld, cur = kWorld + 0x4000;
        put_pipeline(m, rng, pipe);
        put_lockable(m, rng, cur);
        w32(m, gpv(-16832), cur);
        pair(m, PAIR(fn_RxPipelineExecute_004f2e70), Args{sx(pipe), sx(wptr(rng)), rng() % 2 ? rng64(rng) : 0, 0},
             seed_of(i, 0x2E70u), "RxPipelineExecute", {}, kExecGlobals);
        put_lockable(m, rng, cur);
        pair(m, PAIR(fn_sub_4F6890_004f6890), Args{sx(cur)}, seed_of(i, 0x6890u), "sub_4F6890");
        put_lockable(m, rng, cur);
        const u32 node = r32(m, cur + 4);
        pair(m, PAIR(fn_sub_4F62D0_004f62d0), Args{sx(node), chance(rng, 50) ? 0 : sx(node + 0x20), sx(cur)},
             seed_of(i, 0x62D0u), "sub_4F62D0");
    }
    // the scratch allocator and the output link
    for (int i = 0; i < 600; ++i) {
        const u32 base = kWorld + 0x100 * (rng() % 16);
        w32(m, gpv(-16820), base);
        w32(m, gpv(-16824), base + pick(rng, {0, 4, 8, 16, 64, 0x400}));
        soup(m, kWorld + 0x2000, 16, rng);
        w32(m, kWorld + 0x2010, chance(rng, 50) ? 0 : rng());
        pair(m, PAIR(fn_sub_4F3150_004f3150), Args{pick(rng, {0, 1, 3, 4, 7, 8, 13, 100}), rng64(rng)}, seed_of(i, 0x3150u),
             "sub_4F3150");
        pair(m, PAIR(fn_sub_4F5D30_004f5d30), Args{sx(kWorld + 0x2000), rng64(rng), sx(kWorld + 0x2010)},
             seed_of(i, 0x5D30u), "sub_4F5D30");
    }
}

TEST_CASE("game(render_core3): the Im3D entry points sub_4F1ED0 / sub_4F1FD0 / sub_4F2150 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("im3d");
    std::mt19937 rng{0x4F1ED0u};
    for (int i = 0; i < 800; ++i) {
        reset_rw(m);
        const u32 off = 0x100u + 4u * (rng() % 32);
        w32(m, gpv(-16848), off);
        const u32 g = kEngine + off;
        // six pipelines: the transform (+0) and the five render ones (+4 .. +20)
        for (u32 k = 0; k < 6; ++k) {
            put_pipeline(m, rng, kWorld + 0x200 * k);
            w32(m, g + 4 * k, kWorld + 0x200 * k);
        }
        put_pipeline(m, rng, 0);  // a bad primitive type runs the pipeline at record +32 = 0 (retail: whatever is there)
        w16(m, g + 64, static_cast<u16>(rng()));
        w32(m, g + 68, chance(rng, 15) ? 0u : wptr(rng));
        w32(m, gpv(-16832), kWorld + 0x4000);
        put_lockable(m, rng, kWorld + 0x4000);
        w32(m, kWorld + 0x4018, 0);  // the current pipeline needs no lock
        const u64 type = chance(rng, 10) ? rng64(rng) : rng() % 7;
        const u64 count = chance(rng, 10) ? rng64(rng) : pick(rng, {0, 1, 2, 3, 4, 5, 6, 7, 99, 0x10000, 0x10001, 0x20000});
        pair(m, PAIR(fn_sub_4F1ED0_004f1ed0), Args{sx(wptr(rng)), count, sx(wptr(rng)), rng64(rng)}, seed_of(i, 0x1ED0u),
             "sub_4F1ED0", {}, kExecGlobals);
        pair(m, PAIR(fn_sub_4F1FD0_004f1fd0), Args{type, sx(wptr(rng)), count}, seed_of(i, 0x1FD0u), "sub_4F1FD0", {},
             kExecGlobals);
        pair(m, PAIR(fn_sub_4F2150_004f2150), Args{type}, seed_of(i, 0x2150u), "sub_4F2150", {}, kExecGlobals);
    }
}


// =========================================================================================================
// [renderstate] [upload]
// =========================================================================================================
namespace {

const std::vector<Region> kVuConsts = {{0x965800u, 0x300}};

// The synthetic RW DMA state of the packet layer (as test_render_rw2.cpp / test_render_im2d.cpp): the two DMA
// half-buffers with type-0 queue blocks, the scratchpad double buffer, an open GIF packet or none.
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;
constexpr u32 kType = gpv(-17212), kFixup = gpv(-17208), kCntTag = gpv(-17204), kPktStart = gpv(-17196);
constexpr u32 kQWrite = gpv(-17192), kQLimit = gpv(-17188), kAlloc = gpv(-17184), kHalfEnd = gpv(-17180);
constexpr u32 kHalfSize = gpv(-17164), kHalf0 = gpv(-17160), kHalf1 = gpv(-17156), kGifTail = gpv(-17152);
constexpr u32 kSprPtr = gpv(-17148), kDmaPtr = gpv(-17128), kSprBase = gpv(-17124);
constexpr u32 kD8Chcr = 0x1000D000u, kD9Chcr = 0x1000D400u, kDStat = 0x1000E010u;

// Installs a DMA world; returns the scripted hardware of the case (D8 busy for its first reads sometimes, D_STAT
// polls before the BC0F bit).
Hw dma_world(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i < 0x4000; ++i) m.mem.scratchpad()[i] = static_cast<u8>(rng());
    fill_random(m, kWinLo, kWinLen, rng);
    std::memset(m.at(0x9B0A00u), 0, 0x80);
    std::memset(m.at(0xAEFE00u), 0, 0x80);
    w32(m, kHalfSize, 0x13F400u);
    w32(m, kHalf0, 0x9B0A00u);
    w32(m, kHalf1, 0xAEFE00u);
    w32(m, kHalfEnd, 0xAEFE00u);
    w32(m, kQWrite, 0x9B0A10u + 8u * (rng() % 12));
    w32(m, kQLimit, 0x9B0A78u);
    const u32 spr_base = chance(rng, 50) ? 0x70002000u : 0x70000000u;
    w32(m, kSprBase, spr_base);
    const u32 dma = 0x9C0000u + 16u * (rng() % 1024);
    w32(m, kDmaPtr, dma);
    w32(m, kCntTag, 0);
    w32(m, kGifTail, chance(rng, 33) ? 0x9BA000u + 16u * (rng() % 64) : 0);
    const u32 fill = chance(rng, 33) ? 16u * (rng() % 300) : 8192u - 16u * (24 + rng() % 16);
    if (chance(rng, 30)) {  // no packet open
        w32(m, kType, 0);
        w32(m, kSprPtr, chance(rng, 50) ? 0 : spr_base + fill);
        w32(m, kAlloc, dma + 16u * (rng() % 64));
        w32(m, kPktStart, 0);
    } else {  // a GIF or VIF packet open
        w32(m, kType, chance(rng, 50) ? 0x102u : 0x1101u);
        w32(m, kSprPtr, spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
    }
    w32(m, kFixup, chance(rng, 25) ? spr_base + 16u * (rng() % 64) : 0);
    Hw hw;
    hw.regs[kD8Chcr] = 0;
    if (chance(rng, 50)) hw.reads[kD8Chcr] = {0x100u, 0x100u};
    hw.regs[kD9Chcr] = 0;
    const u32 polls = pick(rng, {0, 0, 1, 3});
    if (polls) {
        std::vector<u64> stat(polls, 0);
        stat.push_back(0x100u);
        hw.reads[kDStat] = stat;
    }
    return hw;
}

}  // namespace

TEST_CASE("game(render_core3): the render-state getter sub_4D78B0 equals its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("sub_4D78B0");
    std::mt19937 rng{0x4D78B0u};
    const s32 shadows64[] = {-17048, -17072, -20272, -17088, -17040, -17032, -17056};
    const s32 shadows32[] = {-20264, -20260, -16956, -16964, -16948, -16924};
    for (int i = 0; i < 3000; ++i) {
        for (s32 o : shadows64) {
            w32(m, gpv(o), rng());
            w32(m, gpv(o) + 4, chance(rng, 70) ? 0 : rng());
        }
        for (s32 o : shadows32) w32(m, gpv(o), chance(rng, 60) ? rng() % 7 : rng());
        // the blend shadows index the 6 x 6 ALPHA table unchecked: keep them in mapped memory (retail: 0..5)
        w32(m, gpv(-20264), rng() % 16);
        w32(m, gpv(-20260), rng() % 16);
        if (chance(rng, 20)) w32(m, gpv(-16948), 0xFFFFFFFFu);
        if (chance(rng, 40)) w32(m, gpv(-16924), pick(rng, {0x965610u, 0x965530u, 0x965450u}));
        if (chance(rng, 40)) w32(m, gpv(-17040), pick(rng, {0x160, 0xC0, 0x120, 0x80, 0x60, 0, 0x20}));
        // an ALPHA shadow that matches the blend table for the blend shadows (the jump tables)
        if (chance(rng, 60)) {
            const u32 src = rng() % 7, dst = rng() % 7;
            w32(m, gpv(-20264), src);
            w32(m, gpv(-20260), dst);
            const u64 word = sx(r32(m, 0x77EF80u + 24 * dst + 4 * src));
            const u64 fix = (src == 1 && dst == 1) ? (0x80ull << 32) : 0;
            const u64 alpha = word | fix;
            std::memcpy(m.at(gpv(-17032)), &alpha, 8);
        }
        const u64 state = chance(rng, 5) ? rng64(rng) : rng() % 32;
        pair(m, PAIR(fn_sub_4D78B0_004d78b0), Args{state, sx(kWorld + 0x40)}, seed_of(i, 0x78B0u), "sub_4D78B0");
    }
}

TEST_CASE("game(render_core3): the camera VU constants sub_4EEC20 and the upload chains equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("upload");
    std::mt19937 rng{0x4EEC20u};
    for (int i = 0; i < 600; ++i) {
        const u32 cam = kWorld, ras = kWorld + 0x200, parent = kWorld + 0x300;
        fill_floats(m, cam, 64, rng);
        w32(m, cam + 20, pick(rng, {1, 1, 0, 2}));
        w32(m, cam + 96, ras);
        soup(m, ras, 16, rng);
        w32(m, ras, parent);
        auto extent = [&] {
            if (chance(rng, 10)) return static_cast<u32>(rng());
            const u32 v = rng() % 1024;
            return chance(rng, 10) ? v - 2000u : v;  // sometimes negative (the rounding halves)
        };
        for (u32 k : {12u, 16u}) {
            w32(m, ras + k, extent());
            w32(m, parent + k, extent());
        }
        w16(m, ras + 28, static_cast<u16>(rng()));
        w16(m, ras + 30, static_cast<u16>(rng()));
        w32(m, gpv(-16860), rng() % 2);
        w32(m, gpv(-16864), rand_float(rng));
        w8(m, gpv(-16892), static_cast<u8>(rng()));
        pair(m, PAIR(fn_sub_4EEC20_004eec20), Args{sx(cam)}, seed_of(i, 0xEC20u), "sub_4EEC20", {}, kVuConsts);
    }
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        fill_random(m, 0x965A40u, 0x10, rng);
        const u32 bytes = chance(rng, 70) ? rng() % 0x4000 : 0x7FEE0u * (1 + rng() % 2) + pick(rng, {0, 16, 1, 0x100});
        pair(m, PAIR(fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020),
             Args{sx(kWorld + 4 * (rng() % 64)), sx(0x01000000u + 16 * (rng() % 4096)), bytes}, seed_of(i, 0xF020u),
             "skyFillInPkt", {}, kVuConsts);
    }
    for (int i = 0; i < 300; ++i) {
        Hw hw = dma_world(m, rng);
        fill_random(m, 0x965A40u, 0x40, rng);
        const u64 rows = pick(rng, {0, 1, 2, 5, 16, 33});
        hw.gpr_in[GPR_T0] = rng() % 16;                         // TBW
        hw.gpr_in[GPR_T1] = pick(rng, {4, 8, 16, 24, 32});      // bpp
        hw.gpr_in[GPR_T2] = pick(rng, {0, 2, 0x13, 0x14});      // PSM
        hw.gpr_in[GPR_T3] = 64u * (1 + rng() % 16);             // the row stride
        pair(m, PAIR(fn_sub_4EF770_004ef770), Args{1 + rng() % 512, rows, sx(0x01000000u + 16 * (rng() % 1024)), rng() % 0x4000},
             seed_of(i, 0xF770u), "sub_4EF770", hw, {{kWinLo, kWinLen}, {0xAE0000u, 0x10000u}, {0x965800u, 0x300}});
    }
}


// =========================================================================================================
// [raster]
// =========================================================================================================
namespace {

// The 4 KiB / 2 KiB frame buffers of the swizzles reach below the dead-stack window: compared (and restored) too.
const std::vector<Region> kDeepStack = {{kSp - 0x2000u, 0x2000u - kDeadStack}};

// A lock record at `rec` for the swizzles: +4 the pixels, +12 the row length, +16 the rows, +24 the stride.
void put_lock(Machine& m, std::mt19937& rng, u32 rec, u32 pixels, u32 width_unit) {
    soup(m, rec, 16, rng);
    const u32 w = chance(rng, 5) ? 0u : width_unit * (1 + rng() % 4);
    const u32 h = chance(rng, 5) ? pick(rng, {0, 0xFFFFFFFCu}) : 4u * (1 + rng() % 4);
    const u32 stride = 2 * w + 32 + 16 * (rng() % 3);
    w32(m, rec + 4, pixels);
    w32(m, rec + 12, w);
    w32(m, rec + 16, h);
    w32(m, rec + 24, stride);
    fill_random(m, pixels, (h > 64 ? 4 : h + 4) * stride + 64, rng);
}

}  // namespace

TEST_CASE("game(render_core3): the raster swizzles sub_4DD480 / sub_4DD700 / sub_4DDAA0 / sub_4DDD30 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("swizzles");
    std::mt19937 rng{0x4DD480u};
    struct W {
        const char* name;
        Fn hand, recomp;
        u32 unit;
    };
    const W ws[] = {{"sub_4DD480", PAIR(fn_sub_4DD480_004dd480), 16}, {"sub_4DDAA0", PAIR(fn_sub_4DDAA0_004ddaa0), 16},
                    {"sub_4DD700", PAIR(fn_sub_4DD700_004dd700), 32}, {"sub_4DDD30", PAIR(fn_sub_4DDD30_004ddd30), 32}};
    for (const W& wr : ws) {
        for (int i = 0; i < 60; ++i) {
            put_lock(m, rng, kWorld, kWorld + 0x1000, wr.unit);
            pair(m, wr.hand, wr.recomp, Args{sx(kWorld), rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 0xD480u), wr.name, {},
                 kDeepStack);
        }
    }
}

TEST_CASE("game(render_core3): the driver's raster unlock / palette lock / palette unlock equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("raster lock");
    std::mt19937 rng{0x4DECE0u};
    for (int i = 0; i < 500; ++i) {
        reset_rw(m);
        const u32 ras = kWorld, slot_off = 0x60, slot = ras + slot_off;
        soup(m, ras, 0x40, rng);
        w32(m, gpv(-16968), slot_off);
        // the lock buffer (a swizzle-sized record) and the saved copy
        w32(m, ras + 4, kWorld + 0x1000);
        w32(m, ras + 12, pick(rng, {16, 32, 64}));
        w32(m, ras + 16, pick(rng, {4, 8}));
        w32(m, ras + 20, pick(rng, {4, 8, 16, 32}));
        w32(m, ras + 24, pick(rng, {8, 160, 192}));
        fill_random(m, kWorld + 0x1000, 0x1000, rng);
        w8(m, ras + 32, static_cast<u8>(rng()));
        w8(m, ras + 33, static_cast<u8>(rng()));
        w8(m, ras + 34, static_cast<u8>(rng()));
        w8(m, ras + 35, static_cast<u8>(rng()));
        w32(m, ras + 36, kWorld + 0x800);
        w32(m, ras + 8, chance(rng, 20) ? 0u : kWorld + 0x900);
        w32(m, slot + 8, (pick(rng, {0x13, 0x14, 0x00, 0x13}) << 20) | (rng() & 0xC00FFFFFu));
        w8(m, slot + 54, static_cast<u8>(rng() & 0xFE));
        w32(m, slot + 88, chance(rng, 50) ? 0u : kWorld + 0xA00);
        w32(m, gpv(-17312), 0x100);
        w32(m, kEngine + 0x100 + 44, pick(rng, {kOne, kZero, kNonLeaf}));
        pair(m, PAIR(fn_sub_4DECE0_004dece0), Args{0, sx(ras), rng64(rng)}, seed_of(i, 0xECE0u), "sub_4DECE0", {}, kDeepStack);
        w32(m, slot + 88, 0);  // sub_4F1540 / sub_4F0C70 take their short paths
        pair(m, PAIR(fn_sub_4DEF10_004def10), Args{sx(kWorld + 0x40), sx(ras), rng() % 4}, seed_of(i, 0xEF10u), "sub_4DEF10");
        w32(m, slot + 88, chance(rng, 50) ? 0u : kWorld + 0xA00);
        pair(m, PAIR(fn_sub_4DEFD0_004defd0), Args{0, sx(ras)}, seed_of(i, 0xEFD0u), "sub_4DEFD0");
    }
}

TEST_CASE("game(render_core3): the frame-buffer binding sub_4E2F10 and the scissor clips equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("frame buffer / scissor");
    std::mt19937 rng{0x4E2F10u};
    const std::vector<Region> kFb = {{0x965600u, 0x300}};
    for (int i = 0; i < 1000; ++i) {
        soup(m, kWorld, 0x200, rng);
        fill_random(m, 0x965600u, 0x300, rng);
        w32(m, gpv(-16968), 0x40);
        w32(m, gpv(-17016), rng());
        for (s32 o : {-17024, -17020}) {
            const u32 r = chance(rng, 15) ? 0u : kWorld + 0x100 * (rng() % 4);
            w32(m, gpv(o), r);
            if (r) w32(m, r + 0x40 + 88, chance(rng, 50) ? 0u : kWorld + 0x600 + 16 * (rng() % 8));
        }
        pair(m, PAIR(fn_sub_4E2F10_004e2f10), Args{rng64(rng)}, seed_of(i, 0x2F10u), "sub_4E2F10", {}, kFb);
        // the scissor and two rectangles {x, y, w, h}
        auto coord = [&] { return static_cast<u32>(static_cast<s32>(rng() % 600) - 100); };
        for (u32 k = 0; k < 4; ++k) w32(m, 0x965840u + 4 * k, k < 2 ? coord() : rng() % 500);
        for (u32 r : {kWorld + 0x800u, kWorld + 0x810u})
            for (u32 k = 0; k < 4; ++k) w32(m, r + 4 * k, k < 2 ? coord() : static_cast<u32>(static_cast<s32>(rng() % 400) - 20));
        pair(m, PAIR(fn_sub_4E4A90_004e4a90), Args{sx(kWorld + 0x800), sx(kWorld + 0x810)}, seed_of(i, 0x4A90u), "sub_4E4A90",
             {}, kFb);
        for (u32 r : {kWorld + 0x800u, kWorld + 0x810u})
            for (u32 k = 0; k < 4; ++k) w32(m, r + 4 * k, k < 2 ? coord() : static_cast<u32>(static_cast<s32>(rng() % 400) - 20));
        pair(m, PAIR(fn_sub_4E4C20_004e4c20), Args{sx(kWorld + 0x800), sx(kWorld + 0x810)}, seed_of(i, 0x4C20u), "sub_4E4C20",
             {}, kFb);
    }
}


// =========================================================================================================
// [rt2d]
// =========================================================================================================
namespace {

constexpr u32 kCtmDepth = 0x95EE70u, kCtmTable = 0x95EDF0u, kCtmChanged = 0x95EF50u, kTolValid = 0x95EF64u;
constexpr u32 kTolerance = 0x95EF60u, kBudget = 0x95EF68u, kRtCamera = 0x95EF84u, kScratchPath = 0x95ED88u;

// An array record {+0 data, +4 count, +8 capacity, +12 stride} at `rec`.
void put_list(Machine& m, u32 rec, u32 data, u32 count, u32 cap, u32 stride) {
    w32(m, rec, data);
    w32(m, rec + 4, count);
    w32(m, rec + 8, cap);
    w32(m, rec + 12, stride);
}

// The Rt2d globals: a CTM stack of `depth` with matrices in the world (some slots empty), RwMatrixCreate served from
// the freelist pointer (0x960188 = identity: the freelist's block itself), the flags random.
void put_rt2d(Machine& m, std::mt19937& rng) {
    reset_rw(m);
    fill_floats(m, kWorld + 0x6000, 0x800, rng);  // matrices
    w32(m, kCtmDepth, pick(rng, {0, 1, 2, 5, 30, 31}));
    for (u32 k = 0; k < 32; ++k) w32(m, kCtmTable + 4 * k, chance(rng, 15) ? 0u : kWorld + 0x6000 + 64 * k);
    w32(m, gpv(-17432), 0x200);
    w32(m, kEngine + 0x200, kWorld + 0x7C00);  // the matrix freelist: its block becomes the new matrix
    w32(m, 0x960188u, kIdentity);
    w32(m, 0x960180u, kIdentity);  // RwRealloc in place
    w32(m, 0x96017Cu, kIdentity);  // RwFree
    w32(m, 0x96018Cu, pick(rng, {kSecond, kNonLeaf}));  // the freelist free
    w32(m, 0x96012Cu, 0x96012Cu);  // the dirty-frame list, empty
    w32(m, 0x960130u, 0x96012Cu);
    w32(m, gpv(-17376), 0x300);    // the vector module: RwV3dTransformVectors -> the identity callback
    w32(m, kEngine + 0x300 + 16, kIdentity);
    w32(m, kEngine + 0x300 + 8, kIdentity);
    w32(m, kCtmChanged, rng() % 2);
    w32(m, kTolValid, chance(rng, 80) ? 1u : 0u);
    w32(m, kTolerance, rand_float(rng));
    w32(m, kBudget, rng() % 5);
    fill_floats(m, 0x95EE74u, 3, rng);   // the view extent
    fill_floats(m, 0x95EF58u, 2, rng);   // the device scale / aspect
    fill_floats(m, 0x95EDB0u, 16, rng);  // the base matrix
    w32(m, 0x95EDBCu, rng());
}

// A camera at `cam` with a frame tree for the device matrix (sub_4AAE60): +4 the frame, +20 the projection.
void put_rt_camera(Machine& m, std::mt19937& rng) {
    const u32 cam = kWorld + 0x9000;
    soup(m, cam, 32, rng);
    w32(m, cam + 20, pick(rng, {1, 2}));
    // a one-frame hierarchy at kWorld + 0x9100 (not dirty: the LTM read directly)
    const u32 fr = kWorld + 0x9100;
    fill_floats(m, fr, 0xC0 / 4, rng);
    w8(m, fr + 3, static_cast<u8>(rng() & 0xF8));
    w32(m, fr + 4, 0);
    w32(m, fr + 152, 0);
    w32(m, fr + 156, 0);
    w32(m, fr + 160, fr);
    w32(m, cam + 4, fr);
    w32(m, kRtCamera, cam);
}

// A path record set: `n` 24-byte segments {type, x, y, nx, ny, length} at `data`, types mostly 1 / 2 with every curve
// followed by its two control points.
void put_segments(Machine& m, std::mt19937& rng, u32 data, u32 n) {
    fill_floats(m, data, 6 * n, rng);
    for (u32 k = 0; k < n; ++k) {
        u32 t = pick(rng, {1, 1, 1, 2, 3});
        if (t == 2 && k + 2 >= n) t = 1;
        w32(m, data + 24 * k, t);
        if (t == 2) {
            w32(m, data + 24 * (k + 1), 9);
            w32(m, data + 24 * (k + 2), 9);
            k += 2;
        }
    }
}

// A brush / font colour block: 88 bytes of floats at `b`.
void put_brush(Machine& m, std::mt19937& rng, u32 b) { fill_floats(m, b, 26, rng); }

// An Rt2d object of `type` at `obj` (0x100 bytes): +0 type, +8 flags, +16 its matrix, +80 the CTM'd matrix, +144 /
// +160 the colour multiplier / offset, +176 .. +192 the type's fields.
void put_object(Machine& m, std::mt19937& rng, u32 obj, u32 type) {
    fill_floats(m, obj, 64, rng);
    w32(m, obj, type);
    w32(m, obj + 8, (rng() & 0x0100000Fu) | (chance(rng, 80) ? 4u : 0u));
    w32(m, obj + 12, rng());
    w32(m, obj + 92, rng());
}

}  // namespace

TEST_CASE("game(render_core3): the Rt2d CTM stack, Bezier split, brush colours and font call equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("rt2d CTM / brush");
    std::mt19937 rng{0x4AAB40u};
    for (int i = 0; i < 800; ++i) {
        put_rt2d(m, rng);
        fill_floats(m, kWorld, 0x400, rng);
        const u32 mat = kWorld + 0x100;
        w32(m, mat + 12, rng());
        pair(m, PAIR(fn_sub_4AAB40_004aab40), Args{chance(rng, 30) ? 0 : sx(mat)}, seed_of(i, 0xAB40u), "sub_4AAB40");
        pair(m, PAIR(fn_sub_4AAC70_004aac70), Args{sx(mat)}, seed_of(i, 0xAC70u), "sub_4AAC70");
        pair(m, PAIR(fn_sub_4AAD50_004aad50), Args{}, seed_of(i, 0xAD50u), "sub_4AAD50");
        pair(m, PAIR(fn_sub_4AB0C0_004ab0c0), Args{}, seed_of(i, 0xB0C0u), "sub_4AB0C0");
        pair(m, PAIR(fn_sub_4AB910_004ab910), Args{sx(kWorld + 0x200), sx(kWorld + 0x300), sx(kWorld + 0x340)},
             seed_of(i, 0xB910u), "sub_4AB910");
        Hw hw;
        hw.gpr_in[GPR_T0] = sx(kWorld + 0x440);
        hw.gpr_in[GPR_T1] = sx(kWorld + 0x460);
        hw.gpr_in[GPR_T2] = sx(kWorld + 0x480);
        pair(m, PAIR(fn_sub_4A55B0_004a55b0), Args{sx(kWorld + 0x500), sx(kWorld + 0x400), sx(kWorld + 0x410), sx(kWorld + 0x420)},
             seed_of(i, 0x55B0u), "sub_4A55B0", hw);
        w32(m, kWorld + 0x600 + 312, pick(rng, {kIdentity, kNonLeaf, kOne}));
        pair(m, PAIR(fn_sub_4A9A70_004a9a70), Args{sx(kWorld + 0x600), rng64(rng)}, seed_of(i, 0x9A70u), "sub_4A9A70");
    }
    // documented: Rt2dCTMPop never goes below depth 0
    for (int i = 0; i < 10; ++i) {
        put_rt2d(m, rng);
        w32(m, kCtmDepth, 0);
        pair(m, PAIR(fn_sub_4AAD50_004aad50), Args{}, seed_of(i, 0x9u), "pop rule");
        CHECK(r32(m, kCtmDepth) == 0);
    }
}

TEST_CASE("game(render_core3): the Rt2d path functions equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("rt2d paths");
    std::mt19937 rng{0x4ABD50u};
    for (int i = 0; i < 500; ++i) {
        put_rt2d(m, rng);
        put_rt_camera(m, rng);
        // the source path: {+0 data or list, +4 count or -1, +8 closed}
        const u32 src = kWorld, src_list = kWorld + 0x20, src_data = kWorld + 0x100;
        const u32 n = 1 + rng() % 12;
        put_segments(m, rng, src_data, n);
        put_list(m, src_list, src_data, n, n, 24);
        const bool via_list = chance(rng, 50);
        w32(m, src, via_list ? src_list : src_data);
        w32(m, src + 4, via_list ? 0xFFFFFFFFu : n);
        w32(m, src + 8, rng() % 2);
        // the destination path: {+0 its list}, the list's first record already there (the "previous point")
        const u32 dst = kWorld + 0x40, dst_list = kWorld + 0x60, dst_data = kWorld + 0x1000;
        fill_floats(m, dst_data, 6 * 400, rng);
        const u32 have = 1 + rng() % 3;
        put_list(m, dst_list, dst_data + 24, have, 380, 24);
        w32(m, dst, dst_list);
        w32(m, dst + 24, dst);  // the flattened copy of `dst` is itself (sub_4AB6A0)
        w32(m, dst + 8, 0);
        pair(m, PAIR(fn_sub_4ABD50_004abd50), Args{sx(dst), sx(src)}, seed_of(i, 0xBD50u), "sub_4ABD50", {}, kExecGlobals);
        // a single curve flattened directly, with a budget
        fill_floats(m, kWorld + 0x80, 8, rng);
        pair(m, PAIR(fn_sub_4ABA20_004aba20), Args{sx(dst), sx(kWorld + 0x80), rng() % 5}, seed_of(i, 0xBA20u), "sub_4ABA20");
        pair(m, PAIR(fn_sub_4AB6A0_004ab6a0), Args{sx(dst)}, seed_of(i, 0xB6A0u), "sub_4AB6A0");
        fill_floats(m, kWorld + 0xC0, 4, rng);
        pair(m, PAIR(fn_sub_4AC020_004ac020), Args{sx(src), sx(kWorld + 0xC0)}, seed_of(i, 0xC020u), "sub_4AC020");
        pair(m, PAIR(fn_sub_4AA2C0_004aa2c0), Args{}, seed_of(i, 0xA2C0u), "sub_4AA2C0", {}, kExecGlobals);
    }
    // the path-node chain destroyers: nodes {+0 a list or 0, +4 -1 (a list record) or not, +20 the next node}
    for (int i = 0; i < 500; ++i) {
        put_rt2d(m, rng);
        const u32 nodes = kWorld + 0x2000;
        const u32 k = rng() % 10;
        for (u32 j = 0; j < 10; ++j) {
            const u32 nd = nodes + 0x40 * j;
            soup(m, nd, 16, rng);
            const u32 lst = nd + 0x20;
            put_list(m, lst, chance(rng, 70) ? kWorld + 0x3000 : 0u, rng() % 4, rng() % 4, 24);
            w32(m, nd, chance(rng, 20) ? 0u : lst);
            w32(m, nd + 4, chance(rng, 50) ? 0xFFFFFFFFu : 1u);
            w32(m, nd + 20, j + 1 < k ? nd + 0x40 : 0u);
        }
        w32(m, 0x95ED84u, kWorld + 0x3800);  // the node freelist
        pair(m, PAIR(fn_sub_4AC390_004ac390), Args{chance(rng, 10) ? 0 : sx(nodes)}, seed_of(i, 0xC390u), "sub_4AC390");
        // the scratch path reset
        const u32 sp_ = kWorld + 0x2800;
        soup(m, sp_, 16, rng);
        put_list(m, sp_ + 0x40, kWorld + 0x3000, 3, 8, 24);
        w32(m, sp_, sp_ + 0x40);
        w32(m, sp_ + 20, chance(rng, 50) ? 0u : nodes);
        w32(m, kScratchPath, sp_);
        pair(m, PAIR(fn_sub_4AB8C0_004ab8c0), Args{}, seed_of(i, 0xB8C0u), "sub_4AB8C0");
    }
}

TEST_CASE("game(render_core3): the Rt2d object renderers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("rt2d objects");
    std::mt19937 rng{0x4AE960u};
    for (int i = 0; i < 400; ++i) {
        put_rt2d(m, rng);
        put_rt_camera(m, rng);
        fill_floats(m, kWorld, 0x100, rng);  // colour multiplier / offset at kWorld, kWorld + 0x10
        // a string object
        const u32 str = kWorld + 0x200, font = kWorld + 0x400, fobj = kWorld + 0x480, fnt = kWorld + 0x4C0;
        put_object(m, rng, str, 4);
        put_brush(m, rng, font);
        w32(m, str + 176, kWorld + 0x700);
        w32(m, str + 180, font);
        w32(m, str + 192, fobj);
        w32(m, fobj + 4, fnt);
        w32(m, fnt + 312, pick(rng, {kIdentity, kNonLeaf}));
        pair(m, PAIR(fn_sub_4AD750_004ad750), Args{sx(str)}, seed_of(i, 0xD750u), "sub_4AD750");
        // a pick region
        const u32 pick_region = kWorld + 0x800;
        put_object(m, rng, pick_region, 3);
        pair(m, PAIR(fn_sub_4AE2F0_004ae2f0), Args{sx(pick_region)}, seed_of(i, 0xE2F0u), "sub_4AE2F0");
        // a shape drawn from path nodes {flags, path (0: the stroke / fill return at once), brush}
        const u32 shape = kWorld + 0xA00, nodes = kWorld + 0xC00, nlist = kWorld + 0xB00;
        put_object(m, rng, shape, 2);
        const u32 nn = rng() % 4;
        for (u32 k = 0; k < nn; ++k) {
            w32(m, nodes + 12 * k, rng());
            w32(m, nodes + 12 * k + 4, 0);
            w32(m, nodes + 12 * k + 8, kWorld + 0xD00 + 0x60 * k);
            put_brush(m, rng, kWorld + 0xD00 + 0x60 * k);
        }
        put_list(m, nlist, nodes, nn, nn, 12);
        w32(m, shape + 176, nlist);
        w32(m, shape + 184, 0);
        pair(m, PAIR(fn_sub_4AF9D0_004af9d0), Args{sx(shape), sx(kWorld), sx(kWorld + 0x10)}, seed_of(i, 0xF9D0u), "sub_4AF9D0",
             {}, kExecGlobals);
        // a shape on an atomic: material colours from the shape's bytes, the atomic's frame and render callback
        const u32 atomic = kWorld + 0x1000, geo = kWorld + 0x1100, mats = kWorld + 0x1200;
        soup(m, atomic, 32, rng);
        w32(m, atomic + 4, kWorld + 0x9100);
        w32(m, atomic + 72, pick(rng, {kIdentity, kNonLeaf}));
        const u32 nm = rng() % 4;
        w32(m, geo + 36, nm);
        w32(m, geo + 32, mats);
        for (u32 k = 0; k < 4; ++k) w32(m, mats + 4 * k, kWorld + 0x1300 + 16 * k);
        w32(m, kWorld + 0x1080 + 8, geo);
        w32(m, shape + 176, kWorld + 0x1080);
        w32(m, shape + 180, kWorld + 0x1400);
        fill_random(m, kWorld + 0x1400, 16, rng);
        w32(m, shape + 184, atomic);
        pair(m, PAIR(fn_sub_4AF9D0_004af9d0), Args{sx(shape), sx(kWorld), sx(kWorld + 0x10)}, seed_of(i, 0xF9D1u),
             "sub_4AF9D0 atomic", {}, kExecGlobals);
        // a scene of the above children {object, depth}
        const u32 scene = kWorld + 0x1800, kids = kWorld + 0x1A00, klist = kWorld + 0x1980;
        put_object(m, rng, scene, 1);
        put_object(m, rng, pick_region, 3);
        put_object(m, rng, str, 4);
        w32(m, str + 176, kWorld + 0x700);
        w32(m, str + 180, font);
        w32(m, str + 192, fobj);
        w32(m, shape + 184, 0);
        w32(m, shape + 176, nlist);
        const u32 objs[4] = {str, pick_region, shape, kWorld + 0x1E00};
        put_object(m, rng, kWorld + 0x1E00, pick(rng, {0, 7}));  // an empty / unknown object
        const u32 nk = rng() % 5;
        for (u32 k = 0; k < nk; ++k) {
            w32(m, kids + 8 * k, objs[rng() % 4]);
            w32(m, kids + 8 * k + 4, rng() % 100);
        }
        for (u32 o : objs) w32(m, o + 4, rng() % 100);  // the objects' depths
        put_list(m, klist, kids, nk, nk, 8);
        w32(m, scene + 180, nk);
        w32(m, scene + 184, klist);
        w32(m, scene + 188, rng() % 2);
        pair(m, PAIR(fn_sub_4AE960_004ae960), Args{sx(scene), sx(kWorld), sx(kWorld + 0x10)}, seed_of(i, 0xE960u), "sub_4AE960",
             {}, kExecGlobals);
        pair(m, PAIR(fn_sub_4ADF30_004adf30), Args{sx(objs[rng() % 4]), sx(kWorld), sx(kWorld + 0x10)}, seed_of(i, 0xDF30u),
             "sub_4ADF30", {}, kExecGlobals);
        pair(m, PAIR(fn_sub_4AE940_004ae940), Args{sx(scene)}, seed_of(i, 0xE940u), "sub_4AE940", {}, kExecGlobals);
        w32(m, kWorld + 0x1F00 + 36, chance(rng, 20) ? 0u : scene);
        pair(m, PAIR(fn_sub_4B5330_004b5330), Args{sx(kWorld + 0x1F00)}, seed_of(i, 0x5330u), "sub_4B5330", {}, kExecGlobals);
        pair(m, PAIR(fn_sub_4AE690_004ae690), Args{sx(scene)}, seed_of(i, 0xE690u), "sub_4AE690");
        pair(m, PAIR(fn_sub_4AAE60_004aae60), Args{}, seed_of(i, 0xAE60u), "sub_4AAE60");
        pair(m, PAIR(fn_sub_4A6600_004a6600), Args{0, sx(kWorld + 0xD00)}, seed_of(i, 0x6600u), "sub_4A6600");
        pair(m, PAIR(fn_sub_4ACE70_004ace70), Args{0, sx(kWorld + 0xD00)}, seed_of(i, 0xCE70u), "sub_4ACE70");
    }
    // documented: the scene sort orders the children by depth (ascending)
    for (int i = 0; i < 20; ++i) {
        put_rt2d(m, rng);
        const u32 scene = kWorld + 0x1800, kids = kWorld + 0x1A00, klist = kWorld + 0x1980;
        const u32 nk = 2 + rng() % 6;
        for (u32 k = 0; k < nk; ++k) {
            const u32 o = kWorld + 0x2000 + 0x10 * k;
            w32(m, o + 4, rng() % 50);
            w32(m, kids + 8 * k, o);
        }
        put_list(m, klist, kids, nk, nk, 8);
        w32(m, scene + 180, nk);
        w32(m, scene + 184, klist);
        pair(m, PAIR(fn_sub_4AE690_004ae690), Args{sx(scene)}, seed_of(i, 0x7u), "sort rule");
        for (u32 k = 1; k < nk; ++k) CHECK(static_cast<s32>(r32(m, kids + 8 * (k - 1) + 4)) <= static_cast<s32>(r32(m, kids + 8 * k + 4)));
    }
}


// =========================================================================================================
// Real game state: the battle (vblank 6150) and dorm (4900) reference snapshots
// =========================================================================================================
namespace {

std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

const std::vector<Region> kAllRam = {{0, EEMemory::kMainRamSize}};

}  // namespace

TEST_CASE("game(render_core3): the slice on the battle / dorm snapshots (render states, Rt2d device matrix, frame buffers, heap)") {
    Counter cnt("snapshots");
    for (const char* dir : {"battle_ref_6150", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: snapshot " << std::string(dir) << " not found");
            continue;
        }
        Machine m;
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        const std::string where(dir);
        INFO(where);
        std::mt19937 rng{0x5A5Au};
        // every render state of the live GS shadows
        for (u32 state = 0; state < 32; ++state)
            pair(m, PAIR(fn_sub_4D78B0_004d78b0), Args{state, sx(0x01FF0000u)}, seed_of(static_cast<int>(state), 0x51u),
                 "sub_4D78B0 snapshot", {}, kAllRam);
        // the Rt2d CTM / device matrix / tolerance on the live Rt2d state, the frame-buffer binding
        pair(m, PAIR(fn_sub_4AB0C0_004ab0c0), Args{}, seed_of(1, 0x52u), "sub_4AB0C0 snapshot", {}, kAllRam);
        const u32 cam = r32(m, 0x95EF84u);
        if (cam != 0 && cam < EEMemory::kMainRamSize) {
            pair(m, PAIR(fn_sub_4AAE60_004aae60), Args{}, seed_of(2, 0x52u), "sub_4AAE60 snapshot", {}, kAllRam);
            w32(m, 0x95EF64u, 0);
            pair(m, PAIR(fn_sub_4AA2C0_004aa2c0), Args{}, seed_of(3, 0x52u), "sub_4AA2C0 snapshot", {}, kAllRam);
            pair(m, PAIR(fn_sub_4CB2F0_004cb2f0), Args{sx(r32(m, cam + 4))}, seed_of(4, 0x52u), "sub_4CB2F0 snapshot", {}, kAllRam);
            pair(m, PAIR(fn_sub_4EEC20_004eec20), Args{sx(cam)}, seed_of(5, 0x52u), "sub_4EEC20 snapshot", {}, kAllRam);
        }
        pair(m, PAIR(fn_sub_4E2F10_004e2f10), Args{}, seed_of(6, 0x52u), "sub_4E2F10 snapshot", {}, kAllRam);
        // first-fit allocations and frees on the live resource heap (0x960070 + gp-17408, +12)
        const u32 heap = r32(m, kEngine + r32(m, gpv(-17408)) + 12);
        if (heap != 0 && heap < EEMemory::kMainRamSize) {
            for (int i = 0; i < 12; ++i) {
                const auto [h, r] = pair(m, PAIR(fn_sub_4C6F30_004c6f30), Args{sx(heap), 32u * (1 + rng() % 64)},
                                         seed_of(i, 0x53u), "sub_4C6F30 snapshot", {}, kAllRam);
                const u32 got = h.gpr[GPR_V0].u32[0];
                if (got && chance(rng, 50))
                    pair(m, PAIR(fn_sub_4C6E60_004c6e60), Args{sx(got)}, seed_of(i, 0x54u), "sub_4C6E60 snapshot", {}, kAllRam);
            }
        }
    }
}

#endif  // P3FES_GAME_HAVE_GENERATED
