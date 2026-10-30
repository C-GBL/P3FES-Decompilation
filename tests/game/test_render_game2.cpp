// Phase 5 pair tests for the game-side draw layer, second pass (game/src/render/render_game2.cpp): every function
// against its recompiled body on identical guest machines built from random worlds.
//
// Per pair this file compares
//   * the WHOLE main RAM after the run (dead stack included: the hand versions write the original prologue spills and
//     keep their vertex arrays at the original frame offsets) and the whole scratchpad (the RenderWare packets),
//   * the hardware register log (every DMAC access of the still-recompiled _rwDMAOpenVIFPkt / flushes, in order),
//   * every register at the end (all 128-bit GPRs, the FPRs, ACC, FCR31, HI/LO both pipes, SA), the cycles,
//   * and the register file at every check point (rt::check_events: every callee entry and every back-edge, in
//     order): all GPRs in 128 bits, the FPRs, HI/LO, ACC, FCR31 and the cycle count -- so every call is made with the
//     same arguments, the same $ra, the same caller-saved registers and the same stack, as the kernel would save them
//     on a preemption.
// A callee outside the test build stops both runs with a missing-function fatal event; the pair then compares the
// state at the stop (the same callee reached in the same state), which is how the deep RenderWare trees below some
// passes are bounded.
//
// RenderWare's device pointers (RwRenderStateSet/Get, the Im2D pointers, the camera's begin/end, the clear device
// call) point at small recompiled stand-ins: sub_1F1C50 (a non-leaf that spills the $ra it gets below its $sp and
// returns the word at gp-18968), sub_321120 (stores $a0 at gp-25288) and sub_1A8910 (stores 0 at $a0).
// RpSkyRenderStateSet / Get and the DMA packet layer run their real bodies on a synthetic RenderWare DMA state.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/hcdvd.h"
#include "p3fes/game/render_game2.h"
#include "p3fes/rt_hooks.h"

#include <cstring>
#include <optional>
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
P3FES_DECL_PAIR(fn_sub_3294D0_003294d0)
P3FES_DECL_PAIR(fn_sub_329550_00329550)
P3FES_DECL_PAIR(fn_sub_3295C0_003295c0)
P3FES_DECL_PAIR(fn_sub_329630_00329630)
P3FES_DECL_PAIR(fn_sub_34ADA0_0034ada0)
P3FES_DECL_PAIR(fn_sub_34A800_0034a800)
P3FES_DECL_PAIR(fn_sub_349A30_00349a30)
P3FES_DECL_PAIR(fn_sub_348DA0_00348da0)
P3FES_DECL_PAIR(fn_sub_34B010_0034b010)
P3FES_DECL_PAIR(fn_sub_349D30_00349d30)
P3FES_DECL_PAIR(fn_kwlnRootUpdate2DDrawBeginTask_001989e0)
P3FES_DECL_PAIR(fn_sub_1A4C10_001a4c10)
P3FES_DECL_PAIR(fn_sub_1AE290_001ae290)
P3FES_DECL_PAIR(fn_sub_3962C0_003962c0)
P3FES_DECL_PAIR(fn_sub_1A50F0_001a50f0)
P3FES_DECL_PAIR(fn_sub_1A7B50_001a7b50)
P3FES_DECL_PAIR(fn_sub_1A7FC0_001a7fc0)
P3FES_DECL_PAIR(fn_sub_1A8140_001a8140)
P3FES_DECL_PAIR(fn_sub_1A8B10_001a8b10)
P3FES_DECL_PAIR(fn_sub_315C20_00315c20)
P3FES_DECL_PAIR(fn_sub_359110_00359110)
P3FES_DECL_PAIR(fn_sub_359560_00359560)
P3FES_DECL_PAIR(fn_sub_359B40_00359b40)
P3FES_DECL_PAIR(fn_sub_359E50_00359e50)
P3FES_DECL_PAIR(fn_sub_19D530_0019d530)
P3FES_DECL_PAIR(fn_sub_19DB10_0019db10)
P3FES_DECL_PAIR(fn_sub_19DE80_0019de80)
P3FES_DECL_PAIR(fn_sub_19F470_0019f470)
P3FES_DECL_PAIR(fn_K_SceneDraw_UpdateDrwOpcFldObjTask_0019d780)
P3FES_DECL_PAIR(fn_sub_188250_00188250)
P3FES_DECL_PAIR(fn_sub_41BAF0_0041baf0)
P3FES_DECL_PAIR(fn_sub_317A20_00317a20)
P3FES_DECL_PAIR(fn_K_FldSrc_DrawFieldOpaque_001b3e50)
P3FES_DECL_PAIR(fn_K_FldSrc_DrawFieldTrans_001b4720)
P3FES_DECL_PAIR(fn_sub_358460_00358460)
P3FES_DECL_PAIR(fn_sub_29E4B0_0029e4b0)
P3FES_DECL_PAIR(fn_sub_2891E0_002891e0)
P3FES_DECL_PAIR(fn_sub_19EF80_0019ef80)
P3FES_DECL_PAIR(fn_frFontDraw_003b1360)
P3FES_DECL_PAIR(fn_sub_113A30_00113a30)
P3FES_DECL_PAIR(fn_sub_113D80_00113d80)
P3FES_DECL_PAIR(fn_sub_1140D0_001140d0)
P3FES_DECL_PAIR(fn_sub_114AF0_00114af0)
P3FES_DECL_PAIR(fn_sub_3B4B40_003b4b40)
P3FES_DECL_PAIR(fn_sub_139DC0_00139dc0)
P3FES_DECL_PAIR(fn_sub_2720C0_002720c0)
P3FES_DECL_PAIR(fn_sub_2532B0_002532b0)
P3FES_DECL_PAIR(fn_sub_22C5A0_0022c5a0)
P3FES_DECL_PAIR(fn_sub_27B880_0027b880)
P3FES_DECL_PAIR(fn_sub_23C8C0_0023c8c0)
P3FES_DECL_PAIR(fn_sub_411EE0_00411ee0)
P3FES_DECL_PAIR(fn_sub_25BBF0_0025bbf0)
P3FES_DECL_PAIR(fn_sub_2520F0_002520f0)
P3FES_DECL_PAIR(fn_sub_351290_00351290)
P3FES_DECL_PAIR(fn_sub_351510_00351510)
P3FES_DECL_PAIR(fn_sub_351940_00351940)
P3FES_DECL_PAIR(fn_sub_351A10_00351a10)
P3FES_DECL_PAIR(fn_sub_41BF80_0041bf80)
P3FES_DECL_PAIR(fn_sub_20D500_0020d500)
// the second half (render_game2_hg.cpp)
P3FES_DECL_PAIR(fn_sub_1059B0_001059b0)
P3FES_DECL_PAIR(fn_sub_107B20_00107b20)
P3FES_DECL_PAIR(fn_sub_2496E0_002496e0)
P3FES_DECL_PAIR(fn_sub_111610_00111610)
P3FES_DECL_PAIR(fn_sub_1071F0_001071f0)
P3FES_DECL_PAIR(fn_sub_114450_00114450)
P3FES_DECL_PAIR(fn_sub_114E70_00114e70)
P3FES_DECL_PAIR(fn_sub_115350_00115350)
P3FES_DECL_PAIR(fn_sub_1127D0_001127d0)
P3FES_DECL_PAIR(fn_sub_124FD0_00124fd0)
P3FES_DECL_PAIR(fn_sub_2095A0_002095a0)
P3FES_DECL_PAIR(fn_sub_19BCF0_0019bcf0)
P3FES_DECL_PAIR(fn_sub_199D90_00199d90)
P3FES_DECL_PAIR(fn_sub_19A420_0019a420)
P3FES_DECL_PAIR(fn_sub_19AB80_0019ab80)
P3FES_DECL_PAIR(fn_sub_249C10_00249c10)
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

constexpr u32 kGpBase = 0x007D2CF0u;
constexpr u32 gpv(s32 off) { return kGpBase + static_cast<u32>(off); }

// Stand-ins for RenderWare's device calls (recompiled functions reached through the dispatch table).
constexpr u32 kStubNonLeaf = 0x1F1C50u;  // spills $ra in a 16-byte frame, returns *(gp-18968)
constexpr u32 kStubStoreA0 = 0x321120u;  // *(s16*)(gp-25288) = $a0
constexpr u32 kStubZeroAt = 0x1A8910u;   // *(u32*)$a0 = 0
constexpr s32 kGpStubResult = -18968;

// Arena layout (kArena = 0x01800000, 8 KiB).
constexpr u32 kCamera = kArena;            // RwCamera: +0x18 begin, +0x1C end, +0x80 near plane
constexpr u32 kTask = kArena + 0x100;      // a kwln task record (+0x3C = work, +0x4C = a second record)
constexpr u32 kWork = kArena + 0x200;      // task work records
constexpr u32 kObj = kArena + 0x600;       // effect objects (+36 params, +40 record)
constexpr u32 kParams = kArena + 0x800;    // effect params
constexpr u32 kRec = kArena + 0xC00;       // misc records
constexpr u32 kBig = kArena + 0x1000;      // a large work record (dds3 debug objects: +1660 .. +1680)

// The RenderWare DMA state (22_rendering.md section 5.1; render_im2d's synthetic worlds).
constexpr u32 kType = kGpBase - 17212u, kFixup = kGpBase - 17208u, kCntTag = kGpBase - 17204u, kPktStart = kGpBase - 17196u;
constexpr u32 kQWrite = kGpBase - 17192u, kQLimit = kGpBase - 17188u, kAlloc = kGpBase - 17184u, kHalfEnd = kGpBase - 17180u;
constexpr u32 kHalfSize = kGpBase - 17164u, kHalf0 = kGpBase - 17160u, kHalf1 = kGpBase - 17156u, kGifTail = kGpBase - 17152u;
constexpr u32 kSprWritePtr = kGpBase - 17148u, kDmaPtr = kGpBase - 17128u, kSprBase = kGpBase - 17124u;
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;
constexpr u32 kD8Chcr = 0x1000D000u, kDStat = 0x1000E010u;

// --- the check-point spy over a logging bus ----------------------------------------------------------------------
struct Snap {
    u128 gpr[32];
    u32 fpr[32];
    u128 hi, lo;
    u64 cycles;
    u32 acc, fcr31, sa;
};

Snap snap_of(const EEContext& ctx) {
    Snap s;
    std::memcpy(s.gpr, ctx.gpr, sizeof s.gpr);
    std::memcpy(s.fpr, ctx.fpr, sizeof s.fpr);
    s.hi = ctx.hi;
    s.lo = ctx.lo;
    s.cycles = ctx.cycles;
    s.acc = ctx.acc;
    s.fcr31 = ctx.fcr31;
    s.sa = ctx.sa;
    return s;
}

class Spy final : public RtHooks {
public:
    ScriptedBus bus_;
    std::vector<Snap> log;
    int syscalls = 0;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        // a runaway world (a list that loops) ends both runs at the same check point instead of exhausting memory
        if (log.size() >= 200000) throw rt_test::FatalEvent{0, "check-point budget", &ctx};
        log.push_back(snap_of(ctx));
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { throw rt_test::FatalEvent{pc, what, &ctx}; }
    void vu_control_write(EEContext&, u32, u32) override {}
};

bool same128(const u128& a, const u128& b) { return a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]; }

std::map<std::string, int> g_stops;  // why runs stopped (missing callee / lookup miss), for the coverage messages
std::string stops_summary() {
    std::string out;
    for (const auto& [k, v] : g_stops) out += k + " x" + std::to_string(v) + "; ";
    g_stops.clear();
    return out;
}

struct Run {
    Snap end;
    std::vector<Snap> log;
    std::vector<ScriptedBus::Access> bus;
    std::vector<u8> spr;
    bool fatal = false;
    u32 fatal_pc = 0;
    std::string fatal_what;
    std::shared_ptr<StandInWorld> si;  // the run's stand-ins (heap, printf / sprintf, H_Cdvd, recorders), if any
};

using Fprs = std::vector<std::pair<unsigned, u32>>;
using Gprs = std::vector<std::pair<unsigned, u64>>;

// The world a pair starts from: the RAM and scratchpad images and the bus registers.
struct World {
    Machine& m;
    std::vector<u8> base;
    std::vector<u8> spr;
    std::map<u32, u64> regs;
    explicit World(Machine& mm) : m(mm) {}
    void snapshot() {
        base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    }
    void restore_spr() { std::memcpy(m.mem.scratchpad(), spr.data(), spr.size()); }
};

std::string hex(u64 v);

Run run_once(World& w, Fn fn, const Args& args, u32 seed, const Fprs& fprs, const Gprs& gprs,
             const WorldSetup* setup = nullptr) {
    Machine& m = w.m;
    Spy spy;
    spy.bus_.regs = w.regs;
    rt_test::HooksScope scope{&spy};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();
    m.ctx.hi.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    m.ctx.lo.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    m.ctx.acc = rng();
    for (const auto& [r, v] : fprs) m.ctx.fpr[r] = v;
    for (const auto& [r, v] : gprs) m.ctx.gpr[r].u64[0] = v;
    Run r;
    // stand-ins: a fresh set per run, built by the same setup for both runs of a pair (stand_ins.h)
    std::shared_ptr<StandInWorld> siw;
    std::optional<StandInsScope> installed;
    if (setup) {
        siw = std::make_shared<StandInWorld>();
        (*setup)(*siw);
        installed.emplace(siw->si);
    }
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent& e) {
        r.fatal = true;
        r.fatal_pc = e.pc;
        r.fatal_what = e.what;
        ++g_stops[std::string(e.what).substr(0, 60) + " (ra " + hex(m.ctx.gpr[31].u32[0]) + ")"];
    }
    installed.reset();
    r.si = std::move(siw);
    r.end = snap_of(m.ctx);
    r.log = std::move(spy.log);
    r.bus = std::move(spy.bus_.log);
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    return r;
}

std::string hex(u64 v) {
    char b[24];
    std::snprintf(b, sizeof b, "0x%llx", static_cast<unsigned long long>(v));
    return b;
}

// The first register a snapshot pair differs in (-1: none): 0..31 GPR, 32 HI, 33 LO, 34 FCR31 / ACC / SA, 35+f FPR f,
// 70 cycles.
int first_diff(const Snap& x, const Snap& y) {
    for (unsigned g = 0; g < 32; ++g)
        if (!same128(x.gpr[g], y.gpr[g])) return static_cast<int>(g);
    if (!same128(x.hi, y.hi)) return 32;
    if (!same128(x.lo, y.lo)) return 33;
    if (x.fcr31 != y.fcr31 || x.acc != y.acc || x.sa != y.sa) return 34;
    for (unsigned f = 0; f < 32; ++f)
        if (x.fpr[f] != y.fpr[f]) return 35 + static_cast<int>(f);
    if (x.cycles != y.cycles) return 70;
    return -1;
}
std::string describe(const Snap& x, const Snap& y, int d) {
    if (d < 32) return "gpr " + std::to_string(d) + " hand " + hex(x.gpr[d].u64[1]) + ":" + hex(x.gpr[d].u64[0]) + " recomp " +
                       hex(y.gpr[d].u64[1]) + ":" + hex(y.gpr[d].u64[0]);
    if (d == 32 || d == 33) return d == 32 ? "hi" : "lo";
    if (d == 34) return "fcr31/acc/sa";
    if (d < 70) return "fpr " + std::to_string(d - 35) + " hand " + hex(x.fpr[d - 35]) + " recomp " + hex(y.fpr[d - 35]);
    return "cycles hand " + std::to_string(x.cycles) + " recomp " + std::to_string(y.cycles);
}

// Runs hand and recomp from the world and compares everything (header comment); with a stand-in setup, both runs get
// a fresh set built by it and the call logs, the heaps' live blocks and the file layers' nodes must be equal too.
// Returns the recomp run (its stand-ins' log in `si`).
Run pair_run(World& w, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const WorldSetup* setup,
             const Fprs& fprs = {}, const Gprs& gprs = {}) {
    INFO(std::string(what) << " seed " << seed);
    Machine& m = w.m;
    std::memcpy(m.mem.main_ram(), w.base.data(), w.base.size());
    w.restore_spr();
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    const Run h = run_once(w, hand, args, seed, fprs, gprs, setup);
    ram.between();
    w.restore_spr();
    Run r = run_once(w, recomp, args, seed, fprs, gprs, setup);
    INFO("fatal: hand '" << h.fatal_what << "' recomp '" << r.fatal_what << "'");
    if (setup) {
        expect_same_log(h.si->si, r.si->si, what);
        CHECK(h.si->heap.live() == r.si->heap.live());
        CHECK(h.si->heap.bad_frees == r.si->heap.bad_frees);
        CHECK(h.si->cd.nodes == r.si->cd.nodes);
    }
    CHECK(h.fatal == r.fatal);
    CHECK(h.fatal_pc == r.fatal_pc);
    const u8* b = m.mem.main_ram();
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("first differing byte at " << hex(first) << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                        << unsigned(b[first]));
        CHECK(false);
    }
    {
        const std::size_t first = first_difference(h.spr.data(), r.spr.data(), h.spr.size());
        INFO("first differing scratchpad byte " << hex(first));
        CHECK(first == h.spr.size());
    }
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto& x = h.bus[i];
        const auto& y = r.bus[i];
        if (x.write != y.write || x.bits != y.bits || x.pa != y.pa || x.lo != y.lo || x.hi != y.hi) {
            INFO("bus access " << i << " differs: " << hex(x.pa) << " / " << hex(y.pa));
            CHECK(false);
            break;
        }
    }
    {
        const int d = first_diff(h.end, r.end);
        INFO("at the end: " << (d < 0 ? std::string("-") : describe(h.end, r.end, d)));
        CHECK(d < 0);
    }
    if (h.log.size() != r.log.size()) {
        const auto& longer = h.log.size() > r.log.size() ? h.log : r.log;
        const std::size_t at = std::min(h.log.size(), r.log.size());
        INFO("the longer run (" << (h.log.size() > r.log.size() ? "hand" : "recomp") << ") continues with ra "
                                << hex(longer[at].gpr[31].u64[0]) << " cycles " << longer[at].cycles << "; the shorter ends at cycles "
                                << (at ? (h.log.size() > r.log.size() ? r.end.cycles : h.end.cycles) : 0) << " fatal pcs "
                                << hex(h.fatal_pc) << " / " << hex(r.fatal_pc));
        CHECK(false);
    }
    for (std::size_t k = 0; k < std::min(h.log.size(), r.log.size()); ++k) {
        const int d = first_diff(h.log[k], r.log[k]);
        if (d >= 0) {
            INFO("check point " << k << " of " << h.log.size() << " (pc ra " << hex(h.log[k].gpr[31].u64[0]) << " / "
                                 << hex(r.log[k].gpr[31].u64[0]) << "): " << describe(h.log[k], r.log[k], d));
            CHECK(false);
            break;
        }
    }
    return r;
}

// The plain pair (no stand-ins). Returns the recomp run's fatal flag.
bool pair(World& w, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Fprs& fprs = {},
          const Gprs& gprs = {}) {
    return pair_run(w, hand, recomp, args, seed, what, nullptr, fprs, gprs).fatal;
}

void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u32 f32bits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }
void fill_floats(Machine& m, u32 va, u32 n, std::mt19937& rng, float lo, float hi) {
    for (u32 i = 0; i < n; ++i) w32(m, va + 4 * i, f32bits(frand(rng, lo, hi)));
}
u32 stub(std::mt19937& rng) { return pick(rng, {kStubNonLeaf, kStubNonLeaf, kStubStoreA0}); }

// The RenderWare DMA state: an open VIF packet with some bytes already in the scratchpad half, RW's GS shadows.
void dma_world(World& w, std::mt19937& rng) {
    Machine& m = w.m;
    for (u32 i = 0; i < 0x4000; ++i) m.mem.scratchpad()[i] = static_cast<u8>(rng());
    fill_random(m, kWinLo, 0x2000, rng);
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
    w32(m, kGifTail, 0);
    const u32 fill = chance(rng, 70) ? 16u * (rng() % 500) : 8192u - 16u * (1 + rng() % 8);
    w32(m, kType, chance(rng, 80) ? 0x1101u : 0x80001101u);
    w32(m, kSprWritePtr, spr_base + fill);
    w32(m, kAlloc, dma + fill);
    w32(m, kPktStart, dma - 16u * (rng() % 64));
    w32(m, kFixup, 0);
    for (s32 off = -17100; off < -16860; off += 4) w32(m, gpv(off), rng());  // the GS shadows and flags
    w.regs.clear();
    w.regs[kD8Chcr] = chance(rng, 50) ? 0x100u : 0u;
    w.regs[kDStat] = 0x100u;
}

// The RenderWare side every draw function sees: the main camera, the device pointers, the stand-ins' state.
void common_world(World& w, std::mt19937& rng, bool begin_ok) {
    Machine& m = w.m;
    std::memset(m.at(kArena), 0, kArenaSize);
    std::memset(m.at(kSp - 0x2000), 0, 0x2000);
    w32(m, gpv(-19504), kCamera);
    w32(m, kCamera + 0x18, stub(rng));
    w32(m, kCamera + 0x1C, chance(rng, 25) ? kStubZeroAt : stub(rng));
    w32(m, kCamera + 0x80, f32bits(frand(rng, 0.05f, 20.0f)));
    w32(m, gpv(kGpStubResult), begin_ok ? kCamera : 0);
    w32(m, game::rg2::kPfnRenderStateSet, stub(rng));
    w32(m, game::rg2::kPfnRenderStateGet, stub(rng));
    w32(m, game::rg2::kPfnIm2DRenderTriangle, stub(rng));
    w32(m, game::rg2::kPfnIm2DRenderPrimitive, stub(rng));
    w32(m, game::rg2::kPfnIm2DRenderIndexedPrimitive, stub(rng));
    w32(m, 0x96010Cu, stub(rng));  // the camera clear device call of RwCameraClear
    w32(m, 0x960088u, f32bits(frand(rng, -100.0f, 70000.0f)));  // near screen z
    dma_world(w, rng);
}

// --- the model's atomic lists (render_game2.cpp [cull]) ---------------------------------------------------------
// Atomics (+3 dirty bits clear, +4 a clean frame, +24 geometry, +44 the cached world sphere, +72 the render callback =
// a stand-in), geometries (+32 materials, +36 count), materials (+4 RGBA, the RpUserData plugin at +16 holding a
// "per3modelMatColor" entry so sub_1B5A30 / sub_1A6400 find it), the frustum camera at 0x960070 (+148 six planes of
// 20 bytes) and 44-byte nodes in the lists of a model record.
constexpr u32 kNodes = kArena + 0x1000, kAtomics = kArena + 0x1200, kGeoms = kArena + 0x1500, kMats = kArena + 0x1600;
constexpr u32 kUserData = kArena + 0x1700, kFrame = kArena + 0x1E00, kFrustumCam = kArena + 0x1800, kQueue = kArena + 0x1B40;
constexpr u32 kXlQueue = 0x8668F0u;  // the translucent queue sub_1A8920 appends to (count + 44-byte nodes)

void cull_world(World& w, std::mt19937& rng) {
    Machine& m = w.m;
    w32(m, 0x960070u, kFrustumCam);
    for (u32 p = 0; p < 6; ++p) {  // planes: a normal, the distance (and the 4-byte tail the stride skips)
        const u32 a = kFrustumCam + 148 + 20 * p;
        w32(m, a + 0, f32bits(frand(rng, -1.0f, 1.0f)));
        w32(m, a + 4, f32bits(frand(rng, -1.0f, 1.0f)));
        w32(m, a + 8, f32bits(frand(rng, -1.0f, 1.0f)));
        w32(m, a + 12, f32bits(frand(rng, -0.5f, 2.5f)));
    }
    w32(m, kFrame + 160, kFrame);  // the root of a clean hierarchy
    m.at(kFrame + 3)[0] = 0;
    w32(m, gpv(-17680), 16);  // the RpUserData plugin offset in a material
    for (u32 g = 0; g < 2; ++g) {
        const u32 geo = kGeoms + 0x40 * g;
        const u32 nmat = g == 0 ? 0u : 1 + rng() % 3;
        w32(m, geo + 32, geo + 0x30);  // the material pointer array
        w32(m, geo + 36, nmat);
        for (u32 k = 0; k < nmat; ++k) {
            const u32 mat = kMats + 0x20 * (k + 3 * g);
            w32(m, geo + 0x30 + 4 * k, mat);
            w32(m, mat + 4, chance(rng, 50) ? (rng() | 0xFF000000u) : rng());  // alpha 255 or not
            w32(m, mat + 16, 1);  // one user-data entry
            w32(m, mat + 20, kUserData);
        }
    }
    w32(m, kUserData + 0, 0x678F90u);  // "per3modelMatColor"
    w32(m, kUserData + 4, 1);
    w32(m, kUserData + 8, 1);
    w32(m, kUserData + 12, kUserData + 0x20);
    w32(m, kUserData + 0x20, rng());  // the colour word
    for (u32 a = 0; a < 8; ++a) {
        const u32 at = kAtomics + 0x60 * a;
        m.at(at + 3)[0] = 0;
        w32(m, at + 4, kFrame);
        w32(m, at + 24, chance(rng, 85) ? kGeoms + 0x40 * (rng() % 2) : 0u);
        w32(m, at + 44, f32bits(frand(rng, -2.0f, 2.0f)));
        w32(m, at + 48, f32bits(frand(rng, -2.0f, 2.0f)));
        w32(m, at + 52, f32bits(frand(rng, -2.0f, 2.0f)));
        w32(m, at + 56, f32bits(frand(rng, 0.0f, 1.5f)));
        w32(m, at + 72, stub(rng));
        w32(m, at + 76, 0);
    }
    w32(m, kXlQueue, rng() % 4);
    for (s32 off : {-27404, -27400, -27396, -27392, -27388, -27384, -27380, -27376, -27372, -19352})
        w32(m, gpv(off), pick(rng, {1u, 1u, 0u, 2u}));
}

// A random 44-byte node on one of the 8 atomics.
void put_node(Machine& m, std::mt19937& rng, u32 node, u32 next) {
    w32(m, node + 0, kAtomics + 0x60 * (rng() % 8));
    w32(m, node + 4, pick(rng, {0u, 1u, 1u, 2u}));
    w32(m, node + 8, pick(rng, {0u, 1u, 1u, 2u}));
    fill_floats(m, node + 12, 3, rng, 0.0f, 2.0f);
    w32(m, node + 24, chance(rng, 25) ? f32bits(chance(rng, 50) ? 1.0f : 0.0f) : f32bits(frand(rng, -0.2f, 1.2f)));
    w32(m, node + 28, pick(rng, {0u, 2u, 3u, 4u, 2u}));
    w32(m, node + 40, next);
}

// The model lists record at `lists`: each list offset gets a chain of 0..3 nodes (10 nodes of 48 bytes at most).
void put_lists(Machine& m, std::mt19937& rng, u32 lists) {
    u32 n = 0;
    for (u32 off : {8u, 12u, 16u, 20u, 24u, 28u, 32u, 36u, 40u}) {
        u32 head = 0;
        const u32 len = rng() % 4;
        for (u32 k = 0; k < len && n < 10; ++k, ++n) {
            const u32 node = kNodes + 48 * n;
            put_node(m, rng, node, head);
            head = node;
        }
        w32(m, lists + off, head);
    }
}

}  // namespace

TEST_CASE("render_game2: the game's raw VIF packets (FRAME_1 mask, CLAMP_1) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns fns[] = {
        {PAIR(fn_sub_3294D0_003294d0), "sub_3294D0 FRAME_1 masked"},
        {PAIR(fn_sub_329550_00329550), "sub_329550 FRAME_1 restored"},
        {PAIR(fn_sub_3295C0_003295c0), "sub_3295C0 CLAMP_1 = a0"},
        {PAIR(fn_sub_329630_00329630), "sub_329630 CLAMP_1 restored"},
    };
    std::mt19937 rng{0x3294D0u};
    for (const Fns& f : fns) {
        for (int i = 0; i < 40; ++i) {
            common_world(w, rng, true);
            w.snapshot();
            const u64 a0 = (static_cast<u64>(rng()) << 32) | rng();
            pair(w, f.hand, f.recomp, {a0, 0, 0, 0}, 100 + i, f.name);
        }
    }
}

TEST_CASE("render_game2: the full-screen effect callbacks of the 0x348000 band match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
        bool two_args;
    };
    const Fns fns[] = {
        {PAIR(fn_sub_34ADA0_0034ada0), "sub_34ADA0", false}, {PAIR(fn_sub_34A800_0034a800), "sub_34A800", false},
        {PAIR(fn_sub_349A30_00349a30), "sub_349A30", false}, {PAIR(fn_sub_348DA0_00348da0), "sub_348DA0", true},
        {PAIR(fn_sub_34B010_0034b010), "sub_34B010", false}, {PAIR(fn_sub_349D30_00349d30), "sub_349D30", false},
    };
    std::mt19937 rng{0x348DA0u};
    for (const Fns& f : fns) {
        for (int i = 0; i < 40; ++i) {
            common_world(w, rng, true);
            // The object, its params (+36: the vertex builders' blocks at +192 .. as screen-space floats and colour
            // bytes, the gating bytes +195 / +199 / +207) and its record (+40 -> +8 -> the raster word).
            w32(m, kObj + 36, kParams);
            w32(m, kObj + 40, kRec);
            w32(m, kRec + 8, kRec + 0x40);
            w32(m, kRec + 0x40, rng());
            w32(m, 0x957BA8u, rng());
            fill_floats(m, kParams, 0x100, rng, -50.0f, 700.0f);
            for (u32 k : {0u, 4u, 12u}) w32(m, kParams + 192 + k, rng());  // colour bytes
            for (u32 off : {195u, 199u, 207u}) m.at(kParams + off)[0] = static_cast<u8>(chance(rng, 25) ? 0 : rng());
            // sub_348340's culling window (+24 .. +36 of its block): inside or outside the 640 x 448 screen
            const u32 blk = f.two_args ? kParams + 4 : kParams + 192 + 4;
            if (chance(rng, 70)) {
                w32(m, blk + 24, f32bits(frand(rng, 0.0f, 640.0f)));
                w32(m, blk + 28, f32bits(frand(rng, 0.0f, 448.0f)));
                w32(m, blk + 32, f32bits(frand(rng, 0.0f, 640.0f)));
                w32(m, blk + 36, f32bits(frand(rng, 0.0f, 448.0f)));
            }
            w.snapshot();
            if (f.two_args)
                pair(w, f.hand, f.recomp, {sx(kParams), sx(kRec + 0x40), 0, 0}, 200 + i, f.name);
            else
                pair(w, f.hand, f.recomp, {sx(kObj), 0, 0, 0}, 200 + i, f.name);
        }
    }
}

TEST_CASE("render_game2: the 2D pass and the debug-shape passes match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x1989E0u};
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, i % 4 != 0);
        w32(m, gpv(-19888), 0);  // the sprite file list and the sprite queue: empty
        w32(m, gpv(-19892), 0);
        w.snapshot();
        pair(w, PAIR(fn_kwlnRootUpdate2DDrawBeginTask_001989e0), {sx(kTask), 0, 0, 0}, 300 + i, "kwlnRootUpdate2DDrawBeginTask");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, i % 4 != 0);
        w32(m, kTask + 60, kWork);
        fill_floats(m, kWork, 32, rng, -100.0f, 100.0f);
        w.snapshot();
        pair(w, PAIR(fn_sub_1A4C10_001a4c10), {sx(kTask), 0, 0, 0}, 400 + i, "sub_1A4C10");
    }
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, i % 4 != 0);
        w32(m, kTask + 60, kWork);
        w32(m, kWork, chance(rng, 75) ? rng() | 1u : 0u);
        w32(m, kTask + 76, kRec);
        w32(m, kRec + 60, kRec + 0x80);
        w32(m, kRec + 0x80 + 32, f32bits(frand(rng, 0.0f, 50.0f)));
        w32(m, kRec + 0x80 + 16, 0);  // no frame: the position stays zero (sub_318B60's model world is not built here)
        w32(m, gpv(-27352), f32bits(frand(rng, 0.0f, 200.0f)));
        w.snapshot();
        pair(w, PAIR(fn_sub_1AE290_001ae290), {sx(kTask), 0, 0, 0}, 500 + i, "sub_1AE290");
    }
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, i % 4 != 0);
        w32(m, kTask + 76, chance(rng, 85) ? kRec : 0u);  // the dds3 process (+60 its work)
        w32(m, kRec + 60, chance(rng, 90) ? kBig : 0u);
        w32(m, kBig + 1648, 0);  // dbgDrawRect off
        w32(m, kBig + 1660, pick(rng, {0u, 1u, 2u}));
        w32(m, kBig + 1664, pick(rng, {0u, 1u, 2u}));
        w.snapshot();
        pair(w, PAIR(fn_sub_3962C0_003962c0), {sx(kTask), 0, 0, 0}, 600 + i, "sub_3962C0");
    }
}

TEST_CASE("render_game2: the model's atomic lists (opaque, opaque-only, translucent, the sorted queue) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns fns[] = {
        {PAIR(fn_sub_1A7B50_001a7b50), "sub_1A7B50 opaque passes"},
        {PAIR(fn_sub_1A7FC0_001a7fc0), "sub_1A7FC0 opaque-only pass"},
        {PAIR(fn_sub_1A8140_001a8140), "sub_1A8140 translucent passes"},
    };
    std::mt19937 rng{0x1A7B50u};
    int stopped = 0, total = 0;
    for (const Fns& f : fns) {
        for (int i = 0; i < 80; ++i) {
            common_world(w, rng, true);
            cull_world(w, rng);
            const u32 lists = chance(rng, 95) ? kRec : 0u;
            put_lists(m, rng, kRec);
            w.snapshot();
            stopped += pair(w, f.hand, f.recomp, {sx(lists), pick(rng, {0u, 1u, 1u, 2u}), 0, 0}, 700 + i, f.name);
            ++total;
        }
    }
    for (int i = 0; i < 80; ++i) {
        common_world(w, rng, true);
        cull_world(w, rng);
        const u32 count = rng() % 5;
        w32(m, kQueue, count);
        for (u32 k = 0; k < count; ++k) put_node(m, rng, kQueue + 4 + 44 * k, 0);
        w.snapshot();
        stopped += pair(w, PAIR(fn_sub_1A8B10_001a8b10), {sx(kQueue), 0, 0, 0}, 800 + i, "sub_1A8B10 sorted queue");
        ++total;
    }
    MESSAGE("cull pairs: " << total << ", stopped at a missing callee: " << stopped << " (" << stops_summary() << ")");
    CHECK(stopped < total / 4);
}

TEST_CASE("render_game2: the model passes (sub_315C20) and the single-atomic task (sub_1A50F0) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x315C20u};
    int stopped = 0;
    for (int i = 0; i < 80; ++i) {
        common_world(w, rng, true);
        cull_world(w, rng);
        // The model: +216 flags (0x200 whole, 0x400 faded, 0x800 own states), +211 alpha, +220 clump, +224 lists,
        // +228 / +232 its own states. Whole / faded models reach sub_1A88E0 / sub_3164C0 (not in this build: the
        // pair stops there in the same state).
        const u32 model = kArena + 0x1A00;  // (kBig overlaps the nodes)
        const u16 flags = static_cast<u16>((rng() & 0xA00u) | (chance(rng, 12) ? 0x400u : 0u));
        std::memcpy(m.at(model + 216), &flags, 2);
        m.at(model + 211)[0] = static_cast<u8>(rng());
        // The clump (+220): two atomics linked through +64 into the clump's ring at +8 (RpClumpForAllAtomics), their
        // render flag (+2 bit 2) random; the debug cylinder of sub_1A8820 off (gp-19356).
        constexpr u32 kClump = kArena + 0x1C40;
        const u32 at0 = kAtomics + 0x60 * (rng() % 4), at1 = kAtomics + 0x60 * (4 + rng() % 4);
        w32(m, kClump + 8, chance(rng, 90) ? at0 + 64 : kClump + 8);
        w32(m, at0 + 64, at1 + 64);
        w32(m, at1 + 64, kClump + 8);
        m.at(at0 + 2)[0] = static_cast<u8>(rng());
        m.at(at1 + 2)[0] = static_cast<u8>(rng());
        w32(m, gpv(-19356), 0);
        w32(m, model + 220, kClump);
        w32(m, model + 224, chance(rng, 85) ? kRec : 0u);
        w32(m, model + 228, rng() % 128);
        w32(m, model + 232, rng());
        put_lists(m, rng, kRec);
        w.snapshot();
        stopped += pair(w, PAIR(fn_sub_315C20_00315c20), {sx(model), 0, 0, 0}, 900 + i, "sub_315C20");
    }
    MESSAGE("sub_315C20 pairs stopped at a missing callee: " << stopped << " (" << stops_summary() << ")");
    CHECK(stopped < 20);
    for (int i = 0; i < 50; ++i) {
        common_world(w, rng, i % 4 != 0);
        cull_world(w, rng);
        w32(m, kTask + 60, kWork);
        w32(m, kWork + 0, chance(rng, 85) ? 1u : 0u);
        w32(m, kWork + 4, chance(rng, 60) ? kArena + 0x1B00 : 0u);  // the model (its root LTM: sub_318B60 returns it)
        fill_floats(m, kArena + 0x1B00, 16, rng, -2.0f, 2.0f);
        w32(m, kWork + 8, kRec + 0x40);
        w32(m, kRec + 0x40 + 20, kAtomics + 0x60 * (rng() % 8));
        w.snapshot();
        pair(w, PAIR(fn_sub_1A50F0_001a50f0), {sx(kTask), 0, 0, 0}, 1000 + i, "sub_1A50F0");
    }
}

// The debug shapes' RenderWare side: the vector module's device table (0x960070 + gp-17376: +8 the point transform =
// a stand-in), the Im3D block (0x960070 + gp-16848: +0 the transform pipeline, whose single node's body is a
// stand-in) and an idle RxHeap (gp-16832, +24 = 0); the main camera's near / far (+128 / +132) and view matrix
// (+32); the Im2D near / far screen z. RwIm3DRenderLine (sub_4F22B0, outside this build) stops the runs that draw a
// line, in the same state.
constexpr u32 kVecDev = kArena + 0x1F00, kIm3D = kArena + 0x1C80, kPipe = kArena + 0x1F40, kHeap = kArena + 0x1F80;
void shapes_world(World& w, std::mt19937& rng) {
    Machine& m = w.m;
    cull_world(w, rng);
    w32(m, gpv(-17376), kVecDev - 0x960070u);
    w32(m, kVecDev + 8, stub(rng));
    w32(m, kVecDev + 12, stub(rng));
    w32(m, gpv(-16848), kIm3D - 0x960070u);
    w32(m, kIm3D + 0, kPipe);
    w32(m, kPipe + 8, kPipe + 0x20);  // node array
    w32(m, kPipe + 0x20, kPipe + 0x30);  // node 0 -> definition
    w32(m, kPipe + 0x34, kStubNonLeaf);  // definition +4 = the body
    w32(m, gpv(-16832), kHeap);
    w32(m, kHeap + 24, 0);
    w32(m, kCamera + 128, f32bits(frand(rng, 0.05f, 2.0f)));
    w32(m, kCamera + 132, f32bits(frand(rng, 100.0f, 5000.0f)));
    fill_floats(m, kCamera + 32, 16, rng, -1.0f, 1.0f);
    w32(m, 0x960088u, f32bits(frand(rng, 1.0f, 100.0f)));
    w32(m, 0x96008Cu, f32bits(frand(rng, 60000.0f, 70000.0f)));
    fill_floats(m, kWork, 64, rng, -2.0f, 2.0f);  // centres, matrices
    w32(m, kWork + 0x100, rng());                  // the RwRGBA
}

TEST_CASE("render_game2: the debug shapes (lines, axes, circle, sphere, cylinder) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x359110u};
    int stopped = 0, total = 0;
    for (int i = 0; i < 30; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        w.snapshot();
        stopped += pair(w, PAIR(fn_sub_359110_00359110), {sx(kWork), sx(kWork + 16), sx(kWork + 0x100), rng() % 2}, 1100 + i,
                        "sub_359110 line");
        ++total;
    }
    int circles = 0;
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        w.snapshot();
        circles += !pair(w, PAIR(fn_sub_359560_00359560), {sx(kWork), sx(kWork + 0x100), chance(rng, 50) ? sx(kWork + 0x40) : 0u, rng() % 2},
                         1300 + i, "sub_359560 circle", {{12, f32bits(frand(rng, 0.0f, 3.0f))}});
    }
    for (int i = 0; i < 30; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        w.snapshot();
        circles += !pair(w, PAIR(fn_sub_359B40_00359b40), {sx(kWork), sx(kWork + 0x100), rng() % 2, 0}, 1400 + i, "sub_359B40 sphere",
                         {{12, f32bits(frand(rng, 0.0f, 3.0f))}});
    }
    for (int i = 0; i < 30; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        w.snapshot();
        stopped += pair(w, PAIR(fn_sub_359E50_00359e50), {sx(kWork), sx(kWork + 0x100), rng() % 2, 0}, 1500 + i,
                        "sub_359E50 cylinder", {{12, f32bits(frand(rng, 0.0f, 3.0f))}, {13, f32bits(frand(rng, 0.0f, 4.0f))}});
        ++total;
    }
    MESSAGE("shape pairs with lines: " << total << ", stopped in RwIm3DRenderLine: " << stopped << "; circles / spheres run whole: "
                                       << circles << " (" << stops_summary() << ")");
    CHECK(circles == 90);
}

// The field side of the passes (render_game2.cpp [field]), outside the arena (the pairs compare and restore the whole
// RAM): the scene (gp-22448: +0 the floor, +8 the resource manager: one list head per kind), field resources of 0x200
// bytes (+40 flags, +248 next, +260 / +280 models whose +224 lists feed the predicates, +284 .. +412 the per-resource
// lights), kwlnRoot's three lights (gp-19528 / -19524 / -19520: +1 type, +4 a clean frame, +24 colour, +44 an empty
// sector ring) and the field world (gp-19536[gp-19492]: +52 / +60 light lists). The model draw sub_317A20 and the
// translucent field pass are outside this build: runs that reach them stop there in the same state.
constexpr u32 kScene = 0x01900000u, kRes = 0x01910000u, kLights = 0x01902000u, kFrames = 0x01902400u, kWorld = 0x01902800u;
void field_world(World& w, std::mt19937& rng, unsigned draw_percent) {
    Machine& m = w.m;
    std::memset(m.at(kScene), 0, 0x3000);
    std::memset(m.at(kRes), 0, 0x200 * 44);
    w32(m, gpv(-22448), kScene);
    w32(m, kScene + 0, pick(rng, {12u, 199u, 200u, 260u}));
    w32(m, kScene + 8, kScene + 0x100);  // the manager (past the scene's own words: +24 / +28 are read)
    for (u32 kind = 0; kind < 22; ++kind) {
        u32 head = 0;
        const u32 len = rng() % 3;
        for (u32 k = 0; k < len; ++k) {
            const u32 res = kRes + 0x200 * (kind * 2 + k);  // each kind's own resources
            u32 flags = rng() & ~0x2u & ~0x10000u;
            if (chance(rng, draw_percent)) flags |= 2u;
            if (chance(rng, 10)) flags |= 0x10000u;
            w32(m, res + 40, flags);
            w32(m, res + 248, head);
            w32(m, res + 260, res + 0x1C0);
            w32(m, res + 280, res + 0x1C0);
            w32(m, res + 300, chance(rng, 50) ? res + 0x1C0 : 0u);
            w32(m, res + 352, res);
            fill_floats(m, res + 284, 32, rng, 0.0f, 1.0f);
            const u32 lists = res + 0x1D0;  // the model's lists record: empty, or non-empty (+0 / +16 / +32)
            w32(m, res + 0x1C0 + 224, chance(rng, 80) ? lists : 0u);
            for (u32 off : {0u, 12u, 16u, 20u, 32u, 36u, 40u}) w32(m, lists + off, chance(rng, 40) ? rng() | 1u : 0u);
            head = res;
        }
        w32(m, kScene + 0x100 + 4 * kind, head);
    }
    for (u32 l = 0; l < 3; ++l) {
        const u32 light = kLights + 0x80 * l, frame = kFrames + 0xC0 * l;
        m.at(light + 1)[0] = static_cast<u8>(rng() % 128);
        w32(m, light + 4, frame);
        fill_floats(m, light + 24, 4, rng, 0.0f, 1.0f);
        w32(m, light + 44, light + 44);
        w32(m, light + 52, light + 52);  // the world link
        w32(m, light + 56, light + 52);
        w32(m, frame + 160, frame);
        fill_floats(m, frame + 16, 16, rng, -1.0f, 1.0f);
        w32(m, gpv(-19528 + 4 * static_cast<s32>(l)), light);
    }
    w32(m, gpv(-17532), 0x60);  // the light's world-plugin offset (a word past the fields above)
    w32(m, gpv(-19492), 0);
    w32(m, gpv(-19536), kWorld);
    w32(m, kWorld + 52, kWorld + 52);
    w32(m, kWorld + 56, kWorld + 52);
    w32(m, kWorld + 60, kWorld + 60);
    w32(m, kWorld + 64, kWorld + 60);
    w32(m, gpv(-19484), pick(rng, {0u, 1u, 1u}));
    w32(m, 0x8668F0u, rng() % 3);  // the sorted translucent queue
    for (u32 k = 0; k < 3; ++k) put_node(m, rng, 0x8668F4u + 44 * k, 0);
}

TEST_CASE("render_game2: the field model passes match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
        unsigned draw_percent;
    };
    const Fns fns[] = {
        {PAIR(fn_sub_19D530_0019d530), "sub_19D530 sorted translucent queue", 50},
        {PAIR(fn_sub_19DB10_0019db10), "sub_19DB10 opaque NPCs", 50},
        {PAIR(fn_sub_19DE80_0019de80), "sub_19DE80 translucent NPCs", 50},
        {PAIR(fn_sub_19F470_0019f470), "sub_19F470 persona model", 15},
        {PAIR(fn_K_SceneDraw_UpdateDrwOpcFldObjTask_0019d780), "K_SceneDraw_UpdateDrwOpcFldObjTask", 15},
    };
    std::mt19937 rng{0x19D530u};
    for (const Fns& f : fns) {
        int whole = 0;
        for (int i = 0; i < 40; ++i) {
            common_world(w, rng, i % 5 != 0);
            cull_world(w, rng);
            field_world(w, rng, f.draw_percent);
            w.snapshot();
            whole += !pair(w, f.hand, f.recomp, {sx(kTask), 0, 0, 0}, 1600 + i, f.name);
        }
        MESSAGE(std::string(f.name) << ": " << whole << " of 40 pairs ran whole (" << stops_summary() << ")");
        CHECK(whole >= 8);
    }
}

TEST_CASE("render_game2: the calendar task and the event 3-D pass match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x188250u};
    int whole = 0;
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, i % 5 != 0);
        w32(m, kTask + 60, kWork);
        w32(m, kWork + 0, pick(rng, {1u, 1u, 2u, 3u, 0xFFFFFFFFu}));
        w32(m, kWork + 16, rng() % 4);  // the sprite file handle (sprFileIsReady)
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_188250_00188250), {sx(kTask), 0, 0, 0}, 1700 + i, "sub_188250");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, i % 5 != 0);
        // The camera's view window (+104 / +108) and frame (+4, clean); the task's object list (+60 -> +0 -> +12, next
        // +16, record +20: s16 flags, s8 kind).
        w32(m, kCamera + 104, f32bits(frand(rng, 0.2f, 2.0f)));
        w32(m, kCamera + 108, f32bits(frand(rng, 0.2f, 2.0f)));
        w32(m, kCamera + 4, chance(rng, 50) ? kRec + 0x100 : 0u);
        w32(m, kRec + 0x100 + 160, kRec + 0x100);
        w32(m, kTask + 60, kWork);
        w32(m, kWork, kWork + 0x20);
        u32 head = 0;
        for (u32 k = 0; k < rng() % 4; ++k) {
            const u32 obj = kRec + 0x20 * k, rec = kRec + 0x80 + 0x10 * k;
            w32(m, obj + 16, head);
            w32(m, obj + 20, rec);
            const u16 flags = static_cast<u16>(rng() & 0xFFEEu | (chance(rng, 60) ? 0x11u : 0u));
            std::memcpy(m.at(rec), &flags, 2);
            m.at(rec + 2)[0] = static_cast<u8>(pick(rng, {0u, 1u, 4u, 5u, 2u, 3u, 6u}));
            head = obj;
        }
        w32(m, kWork + 0x20 + 12, head);
        w.snapshot();
        // the camera far-plane setter sub_1A4580 is not in the test build (test_battle_camera_6 stands it in): a
        // recorder here too, so the pass runs on past it
        const WorldSetup far_plane = [](StandInWorld& s) { s.si.install_recorder(0x1A4580u, "sub_1A4580 (far plane)", 0); };
        whole += !pair_run(w, PAIR(fn_sub_41BAF0_0041baf0), {sx(kTask), 0, 0, 0}, 1800 + i, "sub_41BAF0", &far_plane).fatal;
    }
    MESSAGE("calendar / event pass pairs run whole: " << whole << " of 80 (" << stops_summary() << ")");
    CHECK(whole >= 30);
}

// A model record for sub_317A20 (outside the arena): flags +216, colour +208, the clump +220 (the cull worlds' two
// atomics through +64), the lists +224, the material animation +860 off; the shadow +1012, the attachments +284 and
// the children +948 mostly off (their callees are outside this build: a run that reaches one stops there).
constexpr u32 kModel = 0x01904000u;
void model_world(World& w, std::mt19937& rng) {
    Machine& m = w.m;
    std::memset(m.at(kModel), 0, 0x420);
    u16 flags = static_cast<u16>(rng());
    if (chance(rng, 90)) flags |= 0x1000;
    if (chance(rng, 85)) flags |= 0x4;
    if (chance(rng, 75)) flags &= static_cast<u16>(~0x2u);
    if (chance(rng, 70)) flags &= static_cast<u16>(~0x8001u);
    if (chance(rng, 60)) flags &= static_cast<u16>(~0x20u);
    std::memcpy(m.at(kModel + 216), &flags, 2);
    w32(m, kModel + 208, rng());
    std::memcpy(m.at(kModel + 212), &flags, 2);
    constexpr u32 kClump = kArena + 0x1C40;
    const u32 at0 = kAtomics + 0x60 * (rng() % 4), at1 = kAtomics + 0x60 * (4 + rng() % 4);
    w32(m, kClump + 8, at0 + 64);
    w32(m, at0 + 64, at1 + 64);
    w32(m, at1 + 64, kClump + 8);
    m.at(at0 + 2)[0] = static_cast<u8>(rng());
    m.at(at1 + 2)[0] = static_cast<u8>(rng());
    w32(m, gpv(-19356), 0);
    w32(m, kModel + 220, kClump);
    w32(m, kModel + 224, chance(rng, 85) ? kRec : 0u);
    w32(m, kModel + 228, rng() % 128);
    w32(m, kModel + 232, rng());
    fill_floats(m, kModel + 128, 3, rng, -10.0f, 10.0f);
    if (chance(rng, 10)) w32(m, kModel + 1012, kModel + 0x400);
    if (chance(rng, 10)) w32(m, kModel + 284 + 156 * (rng() % 4), kModel + 0x3C0);
    put_lists(m, rng, kRec);
}

TEST_CASE("render_game2: the model draw (sub_317A20) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x317A20u};
    int whole = 0;
    for (int i = 0; i < 120; ++i) {
        common_world(w, rng, true);
        cull_world(w, rng);
        model_world(w, rng);
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_317A20_00317a20), {sx(kModel), 0, 0, 0}, 1900 + i, "sub_317A20");
    }
    MESSAGE("model draw pairs run whole: " << whole << " of 120 (" << stops_summary() << ")");
    CHECK(whole >= 60);
}

TEST_CASE("render_game2: the field world passes (K_FldSrc_DrawFieldOpaque / Trans) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns fns[] = {
        {PAIR(fn_K_FldSrc_DrawFieldOpaque_001b3e50), "K_FldSrc_DrawFieldOpaque"},
        {PAIR(fn_K_FldSrc_DrawFieldTrans_001b4720), "K_FldSrc_DrawFieldTrans"},
    };
    std::mt19937 rng{0x1B3E50u};
    for (const Fns& f : fns) {
        int whole = 0;
        for (int i = 0; i < 60; ++i) {
            common_world(w, rng, i % 6 != 0);
            cull_world(w, rng);
            field_world(w, rng, 30);
            model_world(w, rng);  // its clump serves the res's clumps
            // The field resource: flags (bit 0 world mode: RpWorldRender is outside this build), the worlds / lists
            // +8 / +12 / +16, the extra parts +20 (count) / +152 (lists) / +24 (clumps).
            const u32 res = kScene + 0x3800;  // (past the lights, frames and world)
            u32 flags = rng() & 0xC0000000u;
            if (chance(rng, 25)) flags |= 1u;
            w32(m, res + 0, flags);
            for (u32 off : {8u, 12u, 16u}) w32(m, res + off, chance(rng, 80) ? (off == 12 && !(flags & 1u) ? kRec : kArena + 0x1C40) : 0u);
            if (flags & 1u)
                for (u32 off : {8u, 12u, 16u}) w32(m, res + off, kScene + 0x3900 + off * 8);  // worlds (+12 the camera slot)
            const u32 parts = rng() % 3;
            w32(m, res + 20, parts);
            for (u32 k = 0; k < parts; ++k) {
                w32(m, res + 152 + 4 * k, chance(rng, 50) ? kRec : 0u);
                w32(m, res + 24 + 4 * k, kArena + 0x1C40);
            }
            w32(m, gpv(-17544), 0x40);  // the camera's world plugin offset
            w.snapshot();
            whole += !pair(w, f.hand, f.recomp, {sx(kCamera), sx(res), 0, 0}, 2100 + i, f.name);
        }
        MESSAGE(std::string(f.name) << ": " << whole << " of 60 pairs ran whole (" << stops_summary() << ")");
        CHECK(whole >= 30);
    }
}


TEST_CASE("render_game2: the battle front pass, the full-screen quads and the NPC sort match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x2891E0u};
    int whole = 0;
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        w32(m, kWork, rng());
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_358460_00358460), {sx(kWork), rng() % 2, 0, 0}, 2200 + i, "sub_358460");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, true);
        // the battle work: +564 .. +576 the flash RGBA as floats (alpha <= 0: nothing drawn)
        w32(m, gpv(-18692), kBig);
        fill_floats(m, kBig + 564, 3, rng, 0.0f, 1.0f);
        w32(m, kBig + 576, f32bits(chance(rng, 25) ? -0.5f : frand(rng, 0.0f, 1.0f)));
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_29E4B0_0029e4b0), {0, 0, 0, 0}, 2300 + i, "sub_29E4B0");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, true);
        cull_world(w, rng);
        field_world(w, rng, 30);
        model_world(w, rng);
        // the battle work's unit lists (+340 / +348): units (+156 flags, +2546 model id, +2608 next, +296 the model,
        // +400 / +416 its light colour / matrix) in RAM past the field world
        constexpr u32 kUnits = 0x01905000u;
        w32(m, gpv(-18692), kBig);
        for (u32 side = 0; side < 2; ++side) {
            u32 head = 0;
            for (u32 k = 0; k < rng() % 3; ++k) {
                const u32 u = kUnits + 0xC00 * (side * 2 + k);
                w32(m, u + 156, chance(rng, 70) ? rng() | 0x800u : 0u);
                const u16 id = static_cast<u16>(1 + rng() % 21);
                std::memcpy(m.at(u + 2546), &id, 2);
                w32(m, u + 2608, head);
                w32(m, u + 296, kModel);
                fill_floats(m, u + 400, 32, rng, -1.0f, 1.0f);
                head = u;
            }
            w32(m, kBig + 340 + 8 * side, head);
        }
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_2891E0_002891e0), {0, 0, 0, 0}, 2400 + i, "sub_2891E0");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, i % 5 != 0);
        cull_world(w, rng);
        field_world(w, rng, 50);
        model_world(w, rng);
        for (u32 k = 0; k < 44; ++k) {  // every resource's model: the model world's, its effects mostly off
            w32(m, kRes + 0x200 * k + 296, kModel);
            for (u32 e = 0; e < 3; ++e) w32(m, kRes + 0x200 * k + 256 + 4 * e, chance(rng, 20) ? kRes + 0x200 * k + 0x100 : 0u);
        }
        w32(m, kScene + 28, pick(rng, {0u, 1u, 1u}));
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_19EF80_0019ef80), {sx(kTask), 0, 0, 0}, 2500 + i, "sub_19EF80");
    }
    MESSAGE("battle / NPC sort pairs run whole: " << whole << " of 160 (" << stops_summary() << ")");
    CHECK(whole >= 100);
}

TEST_CASE("render_game2: the text draw (frFontDraw) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x3B1360u};
    int whole = 0;
    for (int i = 0; i < 80; ++i) {
        common_world(w, rng, true);
        // text +44 -> lines (0x60 bytes: +0 / +2 bytes, +3 s8 spacing, +4 / +8 pen, +20 z, +24 width, +28 glyphs, +40
        // next, +48 end tag, +60 wait counter, +64 continuation); glyphs (0x40: +2 count, +4 / +8 offsets, +12 width,
        // +16 alpha (and the rgba word), +20 code, +24 / +25 size, +28 -> the font node of frFontRasterDrawGlyph, +40
        // next) whose node's slot holds the glyph's code (a cached glyph).
        const u32 text = kWork, lines = kArena + 0x1000, glyphs = kArena + 0x1400, node = kArena + 0x1A00, slot = kArena + 0x1A40;
        w32(m, text + 44, chance(rng, 95) ? lines : 0u);
        const u32 nlines = 1 + rng() % 3;
        for (u32 l = 0; l < nlines; ++l) {
            const u32 line = lines + 0x60 * l;
            fill_random(m, line, 0x60, rng);
            m.at(line + 3)[0] = static_cast<u8>(rng() % 5);
            w32(m, line + 4, rng() % 8000);
            w32(m, line + 8, rng() % 3000);
            w32(m, line + 20, f32bits(frand(rng, 0.0f, 50.0f)));
            w32(m, line + 24, rng() % 600);
            w32(m, line + 40, l + 1 < nlines ? line + 0x60 : 0u);
            w32(m, line + 48, pick(rng, {0xF247u, 0xF246u, 0xF215u, 0xF214u, 0x41u}));
            w32(m, line + 60, pick(rng, {0u, 1u, 5u, 0xFFFFFFFFu}));
            w32(m, line + 64, chance(rng, 80) ? 0u : 1u);
            u32 ghead = 0;
            for (u32 g = 0; g < rng() % 4; ++g) {
                const u32 gl = glyphs + 0x40 * (l * 4 + g);
                fill_random(m, gl, 0x40, rng);
                w32(m, gl + 4, rng() % 200);
                w32(m, gl + 8, rng() % 200);
                w32(m, gl + 12, rng() % 40);
                m.at(gl + 16)[0] = static_cast<u8>(pick(rng, {0u, 255u, 128u}));
                m.at(gl + 24)[0] = static_cast<u8>(rng() % 40);
                m.at(gl + 25)[0] = static_cast<u8>(rng() % 40);
                w32(m, gl + 28, node);
                w32(m, gl + 40, ghead);
                ghead = gl;
            }
            w32(m, line + 28, ghead);
        }
        w32(m, node + 12, slot);
        // frFontRasterDrawGlyph compares the slot's code with the glyph's (+20 byte): make them equal for most glyphs
        for (u32 g = 0; g < 12; ++g) m.at(glyphs + 0x40 * g + 20)[0] = 0x41;
        const u16 code = 0x41;
        std::memcpy(m.at(slot + 8), &code, 2);
        w16(m, gpv(-22512), static_cast<u16>(chance(rng, 30) ? 0x40u : 0u));
        w32(m, gpv(-18108), pick(rng, {0u, 0u, 2u}));
        w.snapshot();
        whole += !pair(w, PAIR(fn_frFontDraw_003b1360), {sx(text), sx(pick(rng, {0u, 1u, 0x100u, 0xFFu})), 0, 0}, 2600 + i,
                       "frFontDraw");
    }
    MESSAGE("frFontDraw pairs run whole: " << whole << " of 80 (" << stops_summary() << ")");
    CHECK(whole >= 40);
}

TEST_CASE("render_game2: the menu rectangles and the small panels match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns rects[] = {
        {PAIR(fn_sub_113A30_00113a30), "sub_113A30"}, {PAIR(fn_sub_113D80_00113d80), "sub_113D80"},
        {PAIR(fn_sub_1140D0_001140d0), "sub_1140D0"}, {PAIR(fn_sub_114AF0_00114af0), "sub_114AF0"},
    };
    std::mt19937 rng{0x113A30u};
    for (const Fns& f : rects) {
        for (int i = 0; i < 30; ++i) {
            common_world(w, rng, true);
            w32(m, kWork, rng());
            w.snapshot();
            pair(w, f.hand, f.recomp, {sx(rng()), rng() % 640, rng() % 448, sx(kWork)}, 2700 + i, f.name,
                 {{12, f32bits(frand(rng, -5.0f, 50.0f))}, {13, f32bits(frand(rng, 0.0f, 640.0f))}, {14, f32bits(frand(rng, 0.0f, 448.0f))}});
        }
    }
    for (int i = 0; i < 30; ++i) {
        common_world(w, rng, true);
        for (u32 k = 0; k < 8; ++k) {
            w32(m, kWork + 8 * k, rng() % 10240);
            w32(m, kWork + 8 * k + 4, rng() % 3584);
            for (u32 c = 0; c < 4; ++c) w32(m, kRec + 16 * k + 4 * c, rng() % 256);
        }
        for (u32 k = 0; k < 4; ++k) {
            m.at(kTask + k)[0] = static_cast<u8>(rng() % 8);
            m.at(kTask + 8 + k)[0] = static_cast<u8>(rng() % 8);
        }
        w.snapshot();
        pair(w, PAIR(fn_sub_3B4B40_003b4b40), {sx(kWork), sx(kRec), sx(kTask), sx(kTask + 8)}, 2800 + i, "sub_3B4B40");
    }
    for (int i = 0; i < 20; ++i) {
        common_world(w, rng, true);
        w.snapshot();
        pair(w, PAIR(fn_sub_139DC0_00139dc0), {0, 0, 0, 0}, 2900 + i, "sub_139DC0", {{12, f32bits(frand(rng, -5.0f, 50.0f))}});
    }
}

TEST_CASE("render_game2: the battle / result panels match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
        s32 slot;  // the work's gp slot (0: the work is passed in $a0 / $a1)
    };
    const Fns fns[] = {
        {PAIR(fn_sub_2720C0_002720c0), "sub_2720C0", -18740}, {PAIR(fn_sub_2532B0_002532b0), "sub_2532B0", -18848},
        {PAIR(fn_sub_22C5A0_0022c5a0), "sub_22C5A0", -18920}, {PAIR(fn_sub_27B880_0027b880), "sub_27B880", -18700},
        {PAIR(fn_sub_25BBF0_0025bbf0), "sub_25BBF0", -18828}, {PAIR(fn_sub_2520F0_002520f0), "sub_2520F0", -18852},
        {PAIR(fn_sub_23C8C0_0023c8c0), "sub_23C8C0", 0},       {PAIR(fn_sub_411EE0_00411ee0), "sub_411EE0", 0},
    };
    std::mt19937 rng{0x2720C0u};
    int whole = 0, total = 0;
    constexpr u32 kPanel = 0x01906000u;  // the panel work (28 KiB: the quads up to +27648 + 64)
    for (const Fns& f : fns) {
        for (int i = 0; i < 30; ++i) {
            common_world(w, rng, true);
            std::memset(m.at(kPanel), 0, 0x7000);
            for (u32 off = 0; off < 0x7000; off += 4) w32(m, kPanel + off, f32bits(frand(rng, 0.0f, 600.0f)));
            w32(m, kPanel, rng());               // the flags
            w32(m, kPanel + 8, rng() % 3);       // a variant
            w32(m, kPanel + 2896, rng() % 4);    // a count
            w32(m, kPanel + 12, kPanel + 0x100);  // 411EE0's slots
            for (u32 k = 0; k < 5; ++k) {
                const u32 s = kPanel + 0x100 + 20 * k;
                const u16 glyph = static_cast<u16>(chance(rng, 50) ? 0 : 1 + rng() % 200);
                std::memcpy(m.at(s + 12), &glyph, 2);
            }
            if (f.slot) w32(m, gpv(f.slot), chance(rng, 92) ? kPanel : 0u);
            w.snapshot();
            whole += !pair(w, f.hand, f.recomp, {sx(kPanel), sx(kPanel), 0, 0}, 3000 + i, f.name);
            ++total;
        }
    }
    MESSAGE("panel pairs run whole: " << whole << " of " << total << " (" << stops_summary() << ")");
    CHECK(whole >= total / 3);
}

TEST_CASE("render_game2: the screen-capture fade task and the event line objects match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x351A10u};
    int whole = 0;
    // the capture work: +0 state, +2 duration, +4 frame, +8 raster, +12 the capture camera (here the main camera
    // record: begin / end stand-ins, +96 / +100 rasters, +132 far plane)
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, i % 4 != 0);
        shapes_world(w, rng);
        w32(m, kTask + 60, kWork);
        m.at(kWork)[0] = static_cast<u8>(pick(rng, {0u, 1u, 2u, 3u, 3u, 4u, 7u}));
        const u16 dur = static_cast<u16>(1 + rng() % 30), frame = static_cast<u16>(rng() % 31);
        std::memcpy(m.at(kWork + 2), &dur, 2);
        std::memcpy(m.at(kWork + 4), &frame, 2);
        w32(m, kWork + 8, chance(rng, 50) ? kRec : 0u);
        w32(m, kWork + 12, chance(rng, 80) ? kCamera : 0u);
        w32(m, kCamera + 96, kRec + 0x40);
        w32(m, kCamera + 100, 0);
        w32(m, kCamera + 4, 0);
        w32(m, kCamera + 132, f32bits(frand(rng, 100.0f, 5000.0f)));
        w32(m, gpv(-17024), kRec + 0x80);  // the frame-buffer raster (sub_4E3630): +12 / +16 its size
        w32(m, kRec + 0x80 + 12, pick(rng, {640u, 512u}));
        w32(m, kRec + 0x80 + 16, pick(rng, {448u, 224u}));
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_351A10_00351a10), {sx(kTask), 0, 0, 0}, 3300 + i, "sub_351A10");
    }
    for (int i = 0; i < 30; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        w32(m, kWork + 12, kCamera);
        w32(m, gpv(-17024), kRec + 0x80);
        w32(m, kRec + 0x80 + 12, pick(rng, {640u, 512u}));
        w32(m, kRec + 0x80 + 16, pick(rng, {448u, 224u}));
        w32(m, kCamera + 132, f32bits(frand(rng, 100.0f, 5000.0f)));
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_351290_00351290), {sx(kWork), 0, 0, 0}, 3400 + i, "sub_351290");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, true);
        shapes_world(w, rng);
        // obj: +0 flags, +4 vertices, +8 count, +12 -> raster, +16 the matrix
        w32(m, kObj + 0, rng());
        w32(m, kObj + 4, kRec);
        const u16 n = static_cast<u16>(rng() % 8);
        std::memcpy(m.at(kObj + 8), &n, 2);
        w32(m, kObj + 12, kObj + 0x40);
        w32(m, kObj + 0x40, rng());
        w32(m, kObj + 16, kParams);
        fill_floats(m, kParams, 16, rng, -2.0f, 2.0f);
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_41BF80_0041bf80), {sx(kObj), 0, 0, 0}, 3500 + i, "sub_41BF80");
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_20D500_0020d500), {sx(kObj), sx(kParams), 0, 0}, 3600 + i, "sub_20D500");
    }
    MESSAGE("capture / line object pairs run whole: " << whole << " of 170 (" << stops_summary() << ")");
    CHECK(whole >= 20);
}


// --- real game data: the battle snapshot b_5800 and the field snapshot b_3500 (extracted/_ours beside the ELF's tree)
// The snapshot's RAM is the world (the battle work, the units and their models, the field resources, the lights, the
// atomic lists are the game's own); RenderWare's device pointers and the main camera's begin / end are pointed at
// the stand-ins (the real driver is outside this build), so the pairs run through the culling and the passes until
// the first atomic render callback (AtomicDefaultRenderCallBack, outside this build: a compared stop).
namespace {
// (read_snapshot: stand_ins.h -- extracted/_ours/<dir>/eeMemory.bin, empty when absent)
u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void snapshot_world(World& w, const std::vector<u8>& ram, std::mt19937& rng) {
    Machine& m = w.m;
    std::memcpy(m.mem.main_ram(), ram.data(), ram.size());
    for (u32 i = 0; i < 0x4000; ++i) m.mem.scratchpad()[i] = static_cast<u8>(rng());
    for (u32 pfn = 0x960090u; pfn <= 0x9600A4u; pfn += 4) w32(m, pfn, stub(rng));
    w32(m, 0x96010Cu, stub(rng));
    const u32 cam = ld32(m, gpv(-19504));
    w32(m, cam + 0x18, kStubNonLeaf);
    w32(m, cam + 0x1C, stub(rng));
    w32(m, gpv(kGpStubResult), cam);  // BeginUpdate succeeds
    w.regs.clear();
    w.regs[kD8Chcr] = 0;
    w.regs[kDStat] = 0x100u;
}
}  // namespace

TEST_CASE("render_game2: the passes on the battle (b_5800) and field (b_3500) snapshots match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    const std::vector<u8> battle = read_snapshot("b_5800");
    const std::vector<u8> field = read_snapshot("b_3500");
    if (battle.empty() || field.empty()) {
        MESSAGE("SKIP: extracted/_ours/b_5800 or b_3500/eeMemory.bin not found beside the ELF's tree");
        return;
    }
    World w(m);
    std::mt19937 rng{5800u};
    int whole = 0, total = 0;
    // battle: the front pass, the flash, and the model draw of the field resources' models
    for (int i = 0; i < 6; ++i) {
        snapshot_world(w, battle, rng);
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_2891E0_002891e0), {0, 0, 0, 0}, 3700 + i, "b_5800 sub_2891E0");
        whole += !pair(w, PAIR(fn_sub_29E4B0_0029e4b0), {0, 0, 0, 0}, 3710 + i, "b_5800 sub_29E4B0");
        total += 2;
    }
    {
        snapshot_world(w, battle, rng);
        w.snapshot();
        // The models the front pass reaches: a unit's model id (+2546) names a field resource (sub_3B54C0 over the
        // resource manager *(scene + 8), gp-22448), and the resource's +296 is its model. Every resource of the
        // manager's lists (heads at +4k, linked by +248) with a model is one pair.
        const u32 scene = ld32(m, gpv(-22448));
        const u32 mgr = scene ? ld32(m, scene + 8) : 0;
        int models = 0;
        for (u32 k = 0; mgr && k < 16; ++k)
            for (u32 r = ld32(m, mgr + 4 * k); r != 0 && models < 12; r = ld32(m, r + 248)) {
                const u32 model = ld32(m, r + 296);
                if (model == 0 || model >= EEMemory::kMainRamSize) continue;
                ++models;
                whole += !pair(w, PAIR(fn_sub_317A20_00317a20), {sx(model), 0, 0, 0}, 3720 + models, "b_5800 sub_317A20");
                const u32 lists = ld32(m, model + 224);
                if (lists) {
                    whole += !pair(w, PAIR(fn_sub_1A7B50_001a7b50), {sx(lists), 1, 0, 0}, 3740 + models, "b_5800 sub_1A7B50");
                    whole += !pair(w, PAIR(fn_sub_1A8140_001a8140), {sx(lists), 0, 0, 0}, 3760 + models, "b_5800 sub_1A8140");
                    total += 2;
                }
                ++total;
            }
        MESSAGE("b_5800: " << models << " resource models");
        CHECK(models > 0);
    }
    // field: the field object pass, the NPC passes, the persona and translucent-NPC passes, the sorted queue, and the
    // world passes of each field resource of list 12 with flag 2
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns passes[] = {
        {PAIR(fn_K_SceneDraw_UpdateDrwOpcFldObjTask_0019d780), "b_3500 K_SceneDraw_UpdateDrwOpcFldObjTask"},
        {PAIR(fn_sub_19DB10_0019db10), "b_3500 sub_19DB10"},  {PAIR(fn_sub_19DE80_0019de80), "b_3500 sub_19DE80"},
        {PAIR(fn_sub_19F470_0019f470), "b_3500 sub_19F470"},  {PAIR(fn_sub_19EF80_0019ef80), "b_3500 sub_19EF80"},
        {PAIR(fn_sub_19D530_0019d530), "b_3500 sub_19D530"},
    };
    for (const Fns& f : passes) {
        for (int i = 0; i < 3; ++i) {
            snapshot_world(w, field, rng);
            w.snapshot();
            whole += !pair(w, f.hand, f.recomp, {0, 0, 0, 0}, 3800 + i, f.name);
            ++total;
        }
    }
    {
        snapshot_world(w, field, rng);
        w.snapshot();
        const u32 scene = ld32(m, gpv(-22448));
        const u32 mgr = ld32(m, scene + 8);
        const u32 cam = ld32(m, gpv(-19504));
        int res_n = 0;
        for (u32 r = mgr ? ld32(m, mgr + 4 * 12) : 0; r != 0 && res_n < 8; r = ld32(m, r + 248)) {
            const u32 res = ld32(m, r + 352);
            if (!res) continue;
            ++res_n;
            whole += !pair(w, PAIR(fn_K_FldSrc_DrawFieldOpaque_001b3e50), {sx(cam), sx(res), 0, 0}, 3900 + res_n, "b_3500 K_FldSrc_DrawFieldOpaque");
            whole += !pair(w, PAIR(fn_K_FldSrc_DrawFieldTrans_001b4720), {sx(cam), sx(res), 0, 0}, 3920 + res_n, "b_3500 K_FldSrc_DrawFieldTrans");
            total += 2;
        }
        MESSAGE("b_3500: " << res_n << " field resources of list 12");
    }
    MESSAGE("snapshot pairs: " << total << ", run whole " << whole << " (" << stops_summary() << ")");
    CHECK(total > 20);
}

TEST_CASE("render_game2: documented rules (the tables the passes read from the ELF)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    // The screen quads' index table 0x69CB80: two triangles of a 4-vertex quad.
    u16 idx[6];
    std::memcpy(idx, m.at(0x69CB80u), sizeof idx);
    for (u16 i : idx) CHECK(i < 4);
    // The debug shapes' state table 0x69CE60: six {state, value} pairs of RenderWare render states (1 .. 20).
    for (u32 k = 0; k < 6; ++k) {
        const u32 st = ld32(m, 0x69CE60u + 8 * k);
        CHECK(st >= 1);
        CHECK(st <= 20);
    }
    // The material colour user-data name both lookups use.
    CHECK(m.str(0x678F90u) == "per3modelMatColor");
    CHECK(m.str(0x678C60u) == "per3modelMatColor");
    // The Im2D device slots the panels call: 0x96009C RwIm2DRenderTriangle, 0x9600A0 Primitive, 0x9600A4 Indexed.
    CHECK(game::rg2::kPfnIm2DRenderTriangle == 0x96009Cu);
    CHECK(game::rg2::kPfnIm2DRenderPrimitive == 0x9600A0u);
    CHECK(game::rg2::kPfnIm2DRenderIndexedPrimitive == 0x9600A4u);
}

// =====================================================================================================================
// The second half (game/src/render/render_game2_hg.cpp, p3fes_handgen bodies). Same comparison as above (whole RAM,
// scratchpad, bus log, the register file at every check point and at the end); the heap / printf / sprintf / file
// users run with the test stand-ins (stand_ins.h) in both runs, whose call logs, heaps and file nodes must match too.
// Callees outside the test build that a path needs are recorders (they log the call and return a chosen $v0), so the
// pairs run past them; the rest stop both runs at the same missing-function event.
// =====================================================================================================================
namespace {

constexpr u32 kW2 = 0x01A00000u;  // the worlds below (free RAM between the field worlds and the stand-in heap)
constexpr u32 kW2Size = 0x20000u;

u64 pack2(float x, float y) { return static_cast<u64>(f32bits(x)) | (static_cast<u64>(f32bits(y)) << 32); }
void wf(Machine& m, u32 va, float f) { w32(m, va, f32bits(f)); }
u32 r32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}

// The vector module's device functions as RenderWare installs them (the climb snapshot: *(gp-17376) = 0x134, the
// plugin block at 0x960070 + 0x134): +8 the points transform sub_4E3EC0, +12 the vectors transform sub_4E3F20
// (RwV3dTransformPoints / Vectors call through these).
void v3d_device(Machine& m) {
    w32(m, gpv(-17376), 0x134);
    w32(m, 0x960070u + 0x134 + 8, 0x4E3EC0u);
    w32(m, 0x960070u + 0x134 + 12, 0x4E3F20u);
}

// A clean file layer: no requests in flight, an empty sCdvdCache.
void clear_cdvd_for_tests(Machine& m) {
    std::memset(m.at(game::kHCdvdListHead), 0, 16 + 256);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * game::kHCdvdCacheSlots);
}

// A recorder for each callee in `vas` (returning `v0`), plus the standard set (heap, printf / sprintf, H_Cdvd).
WorldSetup standard_plus(std::vector<std::pair<u32, u64>> recorders) {
    return [recorders](StandInWorld& s) {
        install_standard(s);
        for (const auto& [va, v0] : recorders) s.si.install_recorder(va, "recorder", v0);
    };
}

// A synthetic sprite file (the layout sub_1127D0 reads; ui2.h SprHandle / kSprFileSprites): the raster table at +260
// (8 slots, some empty), the 128-byte sprite records through +388.
constexpr u32 kSprFile = kW2 + 0x1000, kSprRecs = kW2 + 0x2000, kSprRasters = kW2 + 0x3000, kSprHandle = kW2 + 0x800;

void sprite_file(Machine& m, std::mt19937& rng) {
    std::memset(m.at(kSprFile), 0, 0x3000);
    w32(m, kSprFile + 388, kSprRecs);
    for (u32 k = 0; k < 8; ++k) {
        const u32 ras = kSprRasters + 0x20 * k;
        w32(m, ras + 12, 16 + rng() % 497);  // width, height (ints)
        w32(m, ras + 16, 16 + rng() % 497);
        w32(m, kSprFile + 260 + 4 * k, chance(rng, 85) ? ras : 0u);
    }
    for (u32 s = 0; s < 4; ++s) {
        const u32 rec = kSprRecs + 128 * s;
        w32(m, rec + 20, rng() % 8);                         // raster slot
        w32(m, rec + 24, rng() & 0xBu);                      // 1 / 2 flips, 8 untextured
        w32(m, rec + 44, rng() & 3u);                        // 1 / 2 the two blend variants
        const u32 ext = rng() % 6;                           // at most one edge strip (+52 .. +64), or none
        for (u32 e = 0; e < 4; ++e) w32(m, rec + 52 + 4 * e, ext == e ? 1 + rng() % 40 : 0u);
        w32(m, rec + 68, rng() % 64);                        // draw offset
        w32(m, rec + 72, rng() % 64);
        const u32 u0 = rng() % 200, v0 = rng() % 200;
        w32(m, rec + 84, u0);
        w32(m, rec + 88, v0);
        w32(m, rec + 92, u0 + 1 + rng() % 200);
        w32(m, rec + 96, v0 + 1 + rng() % 200);
        for (u32 c = 0; c < 4; ++c) w32(m, rec + 100 + 4 * c, rng());  // vertex colours (alpha in the top byte)
        w16(m, rec + 116, chance(rng, 30) ? static_cast<u16>(rng() % 300) : 0);  // size overrides
        w16(m, rec + 118, chance(rng, 30) ? static_cast<u16>(rng() % 300) : 0);
    }
}

// A sprite handle on the synthetic file (rotation 0: no RwMatrix work, see the snapshot test for the rotated path).
void sprite_handle(Machine& m, std::mt19937& rng, u32 h, float rotation) {
    std::memset(m.at(h), 0, 0x34);
    w32(m, h + 8, kSprFile);
    w32(m, h + 12, rng() % 4);
    wf(m, h + 16, frand(rng, -64.0f, 640.0f));
    wf(m, h + 20, frand(rng, -64.0f, 448.0f));
    m.at(h + 24)[0] = chance(rng, 50) ? 0 : static_cast<u8>(rng());  // alpha subtracted
    m.at(h + 25)[0] = chance(rng, 50) ? 0 : static_cast<u8>(rng());  // fade
    w16(m, h + 28, chance(rng, 20) ? static_cast<u16>(rng() % 50) : 0);
    w16(m, h + 30, chance(rng, 20) ? static_cast<u16>(rng() % 50) : 0);
    wf(m, h + 32, rotation);
    w16(m, h + 36, static_cast<u16>(rng() % 64));
    w16(m, h + 38, static_cast<u16>(rng() % 64));
    w16(m, h + 40, chance(rng, 50) ? 0 : static_cast<u16>(1024 + rng() % 8192));  // 4.12 scale, 0 = 1.0
    w16(m, h + 42, chance(rng, 50) ? 0 : static_cast<u16>(1024 + rng() % 8192));
    wf(m, h + 44, frand(rng, 0.0f, 50.0f));
    for (u32 c = 0; c < 3; ++c) m.at(h + 48 + c)[0] = static_cast<u8>(rng());
}

}  // namespace

TEST_CASE("render_game2: the menu panels (sub_114450, sub_114E70, sub_115350) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x114450u};
    int whole = 0, total = 0;
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, true);
        std::memset(m.at(kW2), 0, 0x100);
        w32(m, kW2 + 12, 1 + rng() % 512);  // the raster: width, height
        w32(m, kW2 + 16, 1 + rng() % 512);
        w32(m, kW2 + 0x40, kW2);  // the slot holding it ($t0 points here)
        w.snapshot();
        const Fprs f = {{12, f32bits(frand(rng, -10.0f, 100.0f))}, {13, f32bits(frand(rng, -50.0f, 640.0f))},
                        {14, f32bits(frand(rng, -50.0f, 448.0f))}, {15, f32bits(frand(rng, 0.0f, 256.0f))},
                        {16, f32bits(frand(rng, 0.0f, 256.0f))}};
        // sub_114450(colour, edge alpha, -, height; $t0 = &raster; $f12 depth, $f13 x, $f14 y)
        whole += !pair(w, PAIR(fn_sub_114450_00114450), {rng(), rng() & 0xFFu, rng(), rng() % 480}, 4100 + i, "sub_114450", f,
                       {{8, kW2 + 0x40}});
        // sub_114E70(flip 0 / 1 / 2, colour, width, height; $t0 = &raster; $f12 .. $f16 x, y, depth, u, v)
        whole += !pair(w, PAIR(fn_sub_114E70_00114e70), {rng() % 4, rng(), 1 + rng() % 640, 1 + rng() % 480}, 4200 + i,
                       "sub_114E70", f, {{8, kW2 + 0x40}});
        // sub_115350(colour, four (x, y) pairs in $a1 .. $t0, alphas in $t1 .. $t3; $f12 depth)
        const auto xy = [&] { return pack2(frand(rng, -50.0f, 640.0f), frand(rng, -50.0f, 448.0f)); };
        whole += !pair(w, PAIR(fn_sub_115350_00115350), {rng(), xy(), xy(), xy()}, 4300 + i, "sub_115350", f,
                       {{8, xy()}, {9, rng() % 256}, {10, rng() % 256}, {11, rng() % 256}});
        total += 3;
    }
    MESSAGE("menu panel pairs: " << total << ", run whole " << whole << " (" << stops_summary() << ")");
    CHECK(whole == total);  // the device calls are stand-ins: every pair runs to the end
}

TEST_CASE("render_game2: the sprite draw (sub_1127D0) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x1127D0u};
    int whole = 0, total = 0;
    for (int i = 0; i < 160; ++i) {
        common_world(w, rng, true);
        sprite_file(m, rng);
        sprite_handle(m, rng, kSprHandle, 0.0f);
        w.snapshot();
        whole += !pair(w, PAIR(fn_sub_1127D0_001127d0), {kSprHandle, rng() & 1u, rng(), rng()}, 5100 + i, "sub_1127D0");
        ++total;
    }
    MESSAGE("sprite pairs (synthetic, no rotation): " << total << ", run whole " << whole << " (" << stops_summary() << ")");
    CHECK(whole == total);

    // The game's own sprite handles (the climb snapshot: the list at 0x7CDF3C, four handles on one file), as they are
    // and rotated (RwMatrixCreate / Rotate / Destroy on the real RenderWare state, the free list on the stand-in heap).
    const std::vector<u8> climb = read_snapshot("climb_ref_17000");
    if (climb.empty()) {
        MESSAGE("SKIP: extracted/_ours/climb_ref_17000 not found");
        return;
    }
    write_rw_slots(m);
    int real = 0;
    for (int i = 0; i < 24; ++i) {
        snapshot_world(w, climb, rng);
        write_rw_slots(m);
        std::vector<u32> handles;
        for (u32 h = ld32(m, 0x7CDF3Cu); h != 0 && handles.size() < 8; h = ld32(m, h)) handles.push_back(h);
        REQUIRE(!handles.empty());
        const u32 h = handles[static_cast<std::size_t>(i) % handles.size()];
        if (i >= 8) wf(m, h + 32, i < 16 ? frand(rng, -720.0f, 720.0f) : (chance(rng, 50) ? 190.0f : -200.0f));
        w.snapshot();
        const WorldSetup si = install_standard;
        const Run r = pair_run(w, PAIR(fn_sub_1127D0_001127d0), {h, rng() & 1u, 0, 0}, 5300 + i, "climb sub_1127D0", &si);
        real += !r.fatal;
    }
    MESSAGE("sprite pairs on the climb's handles: 24, run whole " << real << " (" << stops_summary() << ")");
}

TEST_CASE("render_game2: the numbered sprite label (sub_124FD0) matches its recompiled body on the stand-ins") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x124FD0u};
    int whole = 0, total = 0, drawn = 0;
    for (int i = 0; i < 80; ++i) {
        common_world(w, rng, true);
        sprite_file(m, rng);
        w32(m, 0x833B90u, kSprFile);  // the label sprites' file
        std::memset(m.at(kW2 + 0x900), 0, 16);
        w16(m, kW2 + 0x902, static_cast<u16>(rng() % 300));  // the record: +2 the id sub_173220 names
        w32(m, 0x7CDF68u, rng() % 25);                         // the pulse counter (gp-19848)
        w.snapshot();
        const u64 shown = chance(rng, 75) ? 1 : 0;  // sub_176600: is it to be drawn
        // sprCreateHandle and its release sub_115980 run (hand-written since slice unblock): a handle is the 52-byte
        // block sprCreateHandle takes through the RW calloc slot (the stand-in heap), freed again through the free slot.
        // sub_3B32D0 (text) and sub_176600 are replaced and run too: their recorders here never served them, and since
        // the hooked forwarders (2026-10-29) they would, so they are gone (the pairs run as they always did).
        const WorldSetup si = [](StandInWorld& s) {
            install_standard(s);
            s.si.install_recorder(0x1159F0u, "sprDrawSpriteBasic", 0);
        };
        const Run r = pair_run(w, PAIR(fn_sub_124FD0_00124fd0), {pack2(frand(rng, 0.0f, 400.0f), frand(rng, 0.0f, 300.0f)),
                               kW2 + 0x900, chance(rng, 50) ? 0u : rng() % 4, 0}, 5500 + i, "sub_124FD0", &si,
                               {{12, f32bits(frand(rng, 0.0f, 50.0f))}});
        whole += !r.fatal;
        ++total;
        if (r.si) {
            // documented: the label text is sprintf'd first (the format at 0x7CB66C), and the sprites are created
            // only when sub_176600 says so and the state byte is 0
            REQUIRE(!r.si->si.log.empty());
            CHECK(r.si->si.log[0].va == kSprintf);
            // a sprite handle made = sprCreateHandle's RwCalloc(1, 52, 0x40000) (it runs: no stand-in to count), its file
            // the label sprites' file
            u32 handles = 0;
            for (const StandInCall& c : r.si->si.log)
                if (c.va == kRwSlotFns[3] && c.args[1] == 52u && c.args[2] == 0x40000u) {
                    ++handles;
                    CHECK(r32(m, static_cast<u32>(c.v0) + 8) == kSprFile);
                }
            if (handles != 0) {
                CHECK(shown == 1);
                ++drawn;
            }
        }
    }
    MESSAGE("label pairs: " << total << ", run whole " << whole << ", " << drawn << " with the sprites (" << stops_summary() << ")");
    CHECK(whole == total);
}

TEST_CASE("render_game2: the bust-up portrait task (sub_1059B0) matches its recompiled body on the stand-ins") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x1059B0u};
    constexpr u32 kRecB = kW2 + 0x4000, kNode = kW2 + 0x6000, kPak = kW2 + 0x7000, kRas = kW2 + 0x5000;
    int whole = 0, total = 0, named = 0;
    for (int i = 0; i < 160; ++i) {
        common_world(w, rng, true);
        std::memset(m.at(kRecB), 0, 0x700);
        const u32 state = pick(rng, {1u, 1u, 2u, 2u, 3u, 4u, 4u, 4u, 5u});
        w16(m, kRecB + 0, static_cast<u16>(state));
        w16(m, kRecB + 4, static_cast<u16>(pick(rng, {9u, 15u, 10u, 39u, 30u, 42u, 48u, 12u, 5u, 8u, 6u, 13u, 27u, 3u, 20u})));
        w16(m, kRecB + 10, static_cast<u16>(rng() % 8));
        wf(m, kRecB + 12, frand(rng, -100.0f, 400.0f));
        wf(m, kRecB + 16, frand(rng, -100.0f, 300.0f));
        for (u32 k = 0; k < 4; ++k) {
            w32(m, kRas + 0x10 * k, rng());       // the RwRaster the layer's texture holds at +0
            w32(m, kRecB + 20 + 4 * k, kRas + 0x10 * k);
        }
        for (u32 c = 0; c < 4; ++c) m.at(kRecB + 1312 + c)[0] = c == 3 && chance(rng, 70) ? 255 : static_cast<u8>(rng());
        wf(m, kRecB + 1316, frand(rng, 0.0f, 20.0f));
        w32(m, kRecB + 1320, kNode);
        wf(m, kRecB + 1324, frand(rng, 0.25f, 1.5f));
        wf(m, kRecB + 1328, frand(rng, 0.25f, 1.5f));
        w32(m, kRecB + 1352, rng());
        w32(m, kRecB + 1356, rng() % 4);       // layers loaded so far
        w32(m, kRecB + 1360, rng() & 1u);      // eyes
        w32(m, kRecB + 1364, rng() & 1u);      // mouth
        w32(m, kRecB + 1368, rng() & 1u);      // blink phase on
        w32(m, kRecB + 1372, 1 + rng() % 3);   // frames left in the phase
        w32(m, kRecB + 1376, rng() % 7);       // the phase (6 is out of the table)
        w32(m, kRecB + 1380, rng() & 1u);
        // the list file: a loaded (state 4) or loading node over a name-first PAK of 0 .. 4 entries
        std::memset(m.at(kNode), 0, 868);
        w32(m, kNode + 12, chance(rng, 75) ? 4u : 1u);
        w32(m, kNode + 272, kPak);
        std::memset(m.at(kPak), 0, 0x800);
        const u32 entries = rng() % 5;
        for (u32 e = 0; e < entries; ++e) {
            const std::string name = "bu" + std::to_string(rng() % 100) + "_" + std::to_string(e) + ".tmx";
            std::memcpy(m.at(kPak + 320 * e), name.c_str(), name.size() + 1);
            w32(m, kPak + 320 * e + 252, 64);
        }
        w32(m, gpv(-19788), rng() & 1u);  // The Answer (sub_17D800)
        w.snapshot();
        const u32 done = rng() & 1u;  // sub_10C3A0: the texture is ready
        const WorldSetup si = [&m, done](StandInWorld& s) {
            install_standard(s);
            s.si.install_recorder(0x10C1A0u, "sub_10C1A0 (texture request)", 0x1A0F000u);
            s.si.install(0x10C3A0u, "sub_10C3A0 (texture poll)", [&m, done](EEContext&, StandIns&, StandInCall& c) {
                w32(m, static_cast<u32>(c.args[1]), done);
                c.v0 = kW2 + 0x5800;
            });
        };
        const Run r = pair_run(w, PAIR(fn_sub_1059B0_001059b0), {kRecB, 0, 0, 0}, 5700 + i, "sub_1059B0", &si);
        whole += !r.fatal;
        ++total;
        // documented (state 1, list loaded, entry present): the texture path is "bustup/" + the entry's name
        if (r.si)
            for (const StandInCall& c : r.si->si.log)
                if (c.va == kSprintf && c.text.rfind("bustup/", 0) == 0) {
                    CHECK(c.text.find(".tmx") != std::string::npos);
                    ++named;
                }
    }
    MESSAGE("bust-up pairs: " << total << ", run whole " << whole << ", " << named << " texture paths (" << stops_summary() << ")");
    CHECK(whole == total);
}

TEST_CASE("render_game2: the camp fade layers (sub_107B20, sub_1071F0) match their recompiled bodies on the stand-ins") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x107B20u};
    constexpr u32 kFade = 0x7CDE90u;  // the fade record (h_fade.c): +108 state, +112 / +116 duration / frame, ...
    int whole = 0, total = 0;
    for (int i = 0; i < 120; ++i) {
        common_world(w, rng, true);
        clear_cdvd_for_tests(m);
        w16(m, kFade + 108, static_cast<u16>(rng() % 9));
        w16(m, kFade + 112, static_cast<u16>(1 + rng() % 60));
        w16(m, kFade + 116, static_cast<u16>(rng() % 60));
        w16(m, kFade + 92, static_cast<u16>(rng() % 110));
        w16(m, kFade + 120, static_cast<u16>(rng() % 6));  // the fade kind (0 / 1 / 2 / 4 name a file)
        w32(m, kFade + 72, 0);
        w32(m, kFade + 76, 0);
        w32(m, kFade + 80, 0);  // no effect yet: H_Cdvd_CacheFindFile is asked (nothing cached)
        w32(m, kFade + 84, chance(rng, 50) ? kW2 + 0x9000 : 0u);
        w32(m, kFade + 88, rng());
        w.snapshot();
        const u64 ready = rng() & 1u;
        const WorldSetup si = [&m, ready](StandInWorld& s) {
            install_standard(s);
            s.si.install_recorder(0x10C1A0u, "sub_10C1A0 (texture request)", 0x1A0F000u);
            s.si.install(0x10C3A0u, "sub_10C3A0 (texture poll)", [&m, ready](EEContext&, StandIns&, StandInCall& c) {
                w32(m, static_cast<u32>(c.args[1]), static_cast<u32>(ready));
                c.v0 = kW2 + 0x9000;
            });
            s.si.install_recorder(0x4D0F00u, "sub_4D0F00 (texture destroy)", 1);
            s.si.install_recorder(0x111DD0u, "sub_111DD0 (anm task)", 0);
            s.si.install_recorder(0x111F20u, "sub_111F20", 0);
            s.si.install_recorder(0x111EC0u, "sub_111EC0 (anm ready)", ready);
            s.si.install_recorder(0x111EE0u, "sub_111EE0", 0);
            s.si.install_recorder(0x111CB0u, "sub_111CB0 (anm done)", ready ^ 1u);
            s.si.install_recorder(0x111F00u, "sub_111F00", 0);
        };
        whole += !pair_run(w, PAIR(fn_sub_107B20_00107b20), {rng(), rng(), 0, 0}, 5900 + i, "sub_107B20", &si).fatal;
        whole += !pair_run(w, PAIR(fn_sub_1071F0_001071f0), {rng(), rng(), 0, 0}, 6000 + i, "sub_1071F0", &si).fatal;
        total += 2;
    }
    MESSAGE("camp fade pairs: " << total << ", run whole " << whole << " (" << stops_summary() << ")");
}

TEST_CASE("render_game2: the MAESTRO stream task (sub_111610) matches its recompiled body on the stand-ins") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x111610u};
    constexpr u32 kWorkM = kW2 + 0x8000;
    int whole = 0, total = 0, printed = 0;
    for (int i = 0; i < 120; ++i) {
        common_world(w, rng, true);
        clear_cdvd_for_tests(m);
        std::memset(m.at(kWorkM), 0, 0x200);
        w32(m, kTask + 60, kWorkM);
        w32(m, kWorkM + 0, pick(rng, {0u, 0u, 1u, 2u, 3u, 4u, 4u, 5u}));  // the state
        w32(m, kWorkM + 4, 0);
        w32(m, kWorkM + 8, kW2 + 0x8400);
        w32(m, kWorkM + 12, kW2 + 0x8500);
        w32(m, kW2 + 0x8500 + 8, kW2 + 0x8600);
        wf(m, kWorkM + 20, frand(rng, 0.0f, 100.0f));
        const char* path = "maestro/test.dat";
        std::memcpy(m.at(kWorkM + 24), path, std::strlen(path) + 1);
        for (u32 k = 280; k <= 292; k += 4) w32(m, kWorkM + k, rng() & 1u);
        wf(m, kWorkM + 296, frand(rng, 0.0f, 1.0f));
        w32(m, kWorkM + 300, rng() & 1u);  // through the file layer
        w.snapshot();
        const u64 stream = chance(rng, 70) ? kW2 + 0x8400 : 0u, chunk = rng() & 1u;
        std::vector<std::pair<u32, u64>> rec = {{0x4C9D70u, 0}, {0x4AA390u, 0}, {0x4AA3D0u, 0}, {0x4A9F20u, 0}, {0x4AA410u, 0},
                                                {0x4C58A0u, stream}, {0x4B45B0u, kW2 + 0x8500}, {0x4C5780u, 0}, {0x4A9D80u, 0},
                                                {0x4B4D60u, kW2 + 0x8700}, {0x4AE070u, 0}, {0x4AE0C0u, 0}, {0x4AEF60u, 0},
                                                {0x4A9BF0u, 0}, {0x4B1A70u, 0}, {0x4B1A60u, 0}, {0x4B5000u, 0}, {0x4B4C70u, 0},
                                                {0x4B3CC0u, 0}, {0x4AE110u, 0}, {0x4AAA60u, 0}, {0x4AE060u, 0}, {0x111C50u, 0}};
        (void)chunk;
        const WorldSetup si = standard_plus(rec);
        const Run r = pair_run(w, PAIR(fn_sub_111610_00111610), {kTask, 0, 0, 0}, 6200 + i, "sub_111610", &si);
        whole += !r.fatal;
        ++total;
        if (r.si) printed += static_cast<int>(r.si->si.calls_to(kPrintf));
    }
    MESSAGE("MAESTRO pairs: " << total << ", run whole " << whole << ", " << printed << " error prints (" << stops_summary() << ")");
}

TEST_CASE("render_game2: the battle-panel sprite group (sub_2095A0) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x2095A0u};
    constexpr u32 kPanel = kW2 + 0xA000;
    int whole = 0, total = 0;
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, true);
        std::memset(m.at(kPanel), 0, 0x3000);
        w32(m, 0x7CE2ECu, chance(rng, 95) ? kPanel : 0u);
        w32(m, kPanel + 0, rng() & 1u);
        w32(m, kPanel + 10576, rng() % 3);
        for (u32 e = 0; e < 2; ++e) {
            const u32 ent = kPanel + 1056 * e;
            w32(m, ent + 16, rng() & 1u);
            w32(m, ent + 552, rng() % 3);
            for (u32 j = 0; j < 2; ++j) w32(m, ent + 544 + 4 * j, pick(rng, {0u, 1u, 0xFFFFFFFFu}));
            fill_floats(m, ent + 32, 64 * 3, rng, 0.0f, 400.0f);
        }
        w.snapshot();
        const WorldSetup si = standard_plus({{0x209C00u, kW2 + 0xD000}});
        whole += !pair_run(w, PAIR(fn_sub_2095A0_002095a0), {rng(), rng(), 0, 0}, 6400 + i, "sub_2095A0", &si).fatal;
        ++total;
    }
    MESSAGE("battle-panel group pairs: " << total << ", run whole " << whole << " (" << stops_summary() << ")");
}

TEST_CASE("render_game2: the light projector (sub_19AB80, sub_199D90, sub_19A420, sub_19BCF0) matches its recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x19AB80u};
    constexpr u32 kProj = kW2 + 0x10000;                     // the projector record (vertex buffer, +21600 ..)
    constexpr u32 kTri = kW2 + 0x16000, kVerts = kTri + 0x100, kCtx = kW2 + 0x17000, kLtmFrame = kW2 + 0x17100;
    int whole = 0, total = 0, queued = 0;
    for (int i = 0; i < 120; ++i) {
        common_world(w, rng, true);
        field_world(w, rng, 50);
        v3d_device(m);
        std::memset(m.at(kProj + 21600), 0, 0x80);
        w32(m, kProj + 21600, pick(rng, {0u, 3u, 300u, 594u, 597u, 598u, 600u}));  // vertices queued (a flush at >= 598)
        fill_floats(m, kProj + 21616, 3, rng, -1.0f, 1.0f);                  // the projection direction
        fill_floats(m, kProj + 21632, 16, rng, -0.05f, 0.05f);               // the projection matrix: a small scale
        fill_floats(m, kProj + 21632 + 48, 3, rng, 0.3f, 0.7f);              // and an offset into the texture
        m.at(kProj + 21696)[0] = static_cast<u8>(rng());
        w32(m, kProj + 21700, rng() & 1u);                                     // fade by distance
        fill_floats(m, kTri, 3, rng, -1.0f, 1.0f);                             // the face normal
        for (u32 v = 0; v < 3; ++v) {
            w32(m, kTri + 28 + 4 * v, kVerts + 16 * v);
            fill_floats(m, kVerts + 16 * v, 3, rng, -10.0f, 10.0f);
        }
        std::memset(m.at(kLtmFrame), 0, 0x100);
        w32(m, kLtmFrame + 160, kLtmFrame);
        fill_floats(m, kLtmFrame + 0x50, 16, rng, -1.0f, 1.0f);
        w32(m, kCtx + 4, kProj);
        w32(m, kCtx + 8, kCtx + 0x40);
        w32(m, kCtx + 0x44, kLtmFrame);
        w.snapshot();
        const u32 before = r32(m, kProj + 21600);
        whole += !pair(w, PAIR(fn_sub_199D90_00199d90), {rng(), rng(), kTri, kProj}, 6600 + i, "sub_199D90");
        if (r32(m, kProj + 21600) == before + 3) ++queued;  // the triangle was queued (no flush)
        whole += !pair(w, PAIR(fn_sub_19A420_0019a420), {rng(), kTri, kCtx, rng()}, 6700 + i, "sub_19A420");
        // sub_19AB80(light, raster, mode, arg; $t0 flag, $t1 projector; $f12 alpha (< 0: the other blend), $f13 range)
        const u32 light = kW2 + 0x17200;
        w32(m, light + 4, kLtmFrame);
        w.snapshot();
        const WorldSetup si = standard_plus({{0x464020u, 0}});
        whole += !pair_run(w, PAIR(fn_sub_19AB80_0019ab80), {light, rng(), rng() % 3, rng()}, 6800 + i, "sub_19AB80", &si,
                           {{12, f32bits(frand(rng, -1.0f, 1.0f))}, {13, f32bits(frand(rng, 0.5f, 50.0f))}},
                           {{8, rng() & 1u}, {9, kProj}})
                      .fatal;
        total += 3;
    }
    // sub_19BCF0: the projector task's destroy (RW objects released through recorders, the work block freed)
    for (int i = 0; i < 40; ++i) {
        common_world(w, rng, true);
        write_rw_slots(m);
        constexpr u32 kWorkP = kStandInHeap;  // the first block the setup allocates
        std::memset(m.at(kWorkP), 0, 0x60);
        std::memset(m.at(kW2 + 0x18000), 0, 0x500);  // the frame, raster and camera records below (zeroed)
        w32(m, kTask + 60, kWorkP);
        w16(m, kWorkP + 10, static_cast<u16>(rng() & 1u));
        w32(m, kWorkP + 60, kW2 + 0x18000);
        w32(m, kWorkP + 64, kW2 + 0x18100);
        w32(m, kWorkP + 68, chance(rng, 70) ? kW2 + 0x18200 : 0u);
        w32(m, kW2 + 0x18200 + 4, chance(rng, 50) ? kW2 + 0x18300 : 0u);
        w32(m, kW2 + 0x18200 + 96, rng() & 1u);
        w32(m, kW2 + 0x18200 + 100, chance(rng, 50) ? kW2 + 0x18400 : 0u);
        w32(m, kWorkP + 72, 0);
        w32(m, kWorkP + 76, 0);
        w32(m, gpv(-19492), 0);
        w.snapshot();
        const WorldSetup si = [](StandInWorld& s) {
            install_standard(s);
            s.heap.alloc(0x60);
            for (u32 va : {0x4D1840u, 0x4CAF80u, 0x4CA030u, 0x4D0BE0u, 0x494CC0u, 0x491A80u}) s.si.install_recorder(va, "RW", 1);
        };
        whole += !pair_run(w, PAIR(fn_sub_19BCF0_0019bcf0), {kTask, 0, 0, 0}, 6900 + i, "sub_19BCF0", &si).fatal;
        ++total;
    }
    MESSAGE("projector pairs: " << total << ", run whole " << whole << ", " << queued << " triangles queued by sub_199D90 (" << stops_summary() << ")");
}

TEST_CASE("render_game2: Shuffle Time's particle tank (sub_2496E0, sub_249C10) matches its recompiled bodies on the stand-ins") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x2496E0u};
    constexpr u32 kWorkS = kW2 + 0x18000, kAtomic = kW2 + 0x19000, kData = kW2 + 0x19400, kBuf = kW2 + 0x1A000;
    constexpr u32 kFrameS = kW2 + 0x19800;
    int whole = 0, total = 0, prints = 0;
    for (int i = 0; i < 60; ++i) {
        common_world(w, rng, true);
        write_rw_slots(m);
        v3d_device(m);
        std::memset(m.at(kWorkS), 0, 0x620);
        std::memset(m.at(kAtomic), 0, 0x1000);
        fill_floats(m, kWorkS, 128 * 3, rng, -150.0f, 150.0f);  // the particles
        w32(m, kWorkS + 1540, rng() & 1u);
        w32(m, kWorkS + 1536, kAtomic);
        w32(m, 0x7CE770u, 0x40);  // the PTank plugin offset (gp-17792): atomic + 0x40 -> its data
        w32(m, kAtomic + 0x40, kData);
        w32(m, kData + 0, 128);
        w32(m, kAtomic + 24, kAtomic + 0x100);  // geometry -> +32 -> the material list
        w32(m, kAtomic + 0x100 + 32, kAtomic + 0x200);
        w32(m, kAtomic + 0x200, kAtomic + 0x300);
        w32(m, kAtomic + 4, kFrameS);  // the atomic's frame
        std::memset(m.at(kFrameS), 0, 0x100);
        w32(m, kFrameS + 160, kFrameS);
        fill_floats(m, kFrameS + 0x50, 16, rng, -1.0f, 1.0f);
        w32(m, kCamera + 4, kFrameS);  // the camera's frame
        w.snapshot();
        const WorldSetup si = [&m](StandInWorld& s) {
            install_standard(s);
            s.si.install_recorder(0x474210u, "RpPTankAtomicCreate", kAtomic);
            s.si.install_recorder(0x4CAF10u, "RwFrameCreate", kFrameS);
            s.si.install_recorder(0x492D10u, "RpAtomicSetFrame", 0);
            s.si.install_recorder(0x494D50u, "material texture", 0);
            s.si.install_recorder(0x4747F0u, "PTank unlock", 0);
            s.si.install_recorder(0x4CB750u, "RwFrameTranslate", 0);
            // the lock: {pointer, stride} of the colour (2) or position (1) stream into kBuf
            s.si.install(0x474640u, "PTank lock", [&m](EEContext&, StandIns&, StandInCall& c) {
                const u32 out = static_cast<u32>(c.args[1]);
                w32(m, out, c.args[2] == 2 ? kBuf : kBuf + 0x800);
                w32(m, out + 4, c.args[2] == 2 ? 4u : 12u);
                c.v0 = out;
            });
        };
        const Run a = pair_run(w, PAIR(fn_sub_2496E0_002496e0), {kWorkS, 0, 0, 0}, 7100 + i, "sub_2496E0", &si);
        whole += !a.fatal;
        if (a.si) prints += static_cast<int>(a.si->si.calls_to(kPrintf));
        whole += !pair_run(w, PAIR(fn_sub_249C10_00249c10), {kWorkS, 0, 0, 0}, 7200 + i, "sub_249C10", &si).fatal;
        total += 2;
    }
    MESSAGE("particle pairs: " << total << ", run whole " << whole << ", " << prints << " \"sfl_eff: max\" prints ("
                               << stops_summary() << ")");
}

TEST_CASE("render_game2: documented rules of the second half (strings and tables the bodies read from the ELF)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    // sub_1059B0: the portrait paths and its source file name (K_Assert-style argument of sub_10C1A0)
    CHECK(m.str(0x5D3C50u) == "test/char/i_bust%02d_%1d");
    CHECK(m.str(0x5D3C70u) == "test/char/i_bust29_%1d");
    CHECK(m.str(0x5D3C88u) == "bustup/%s");
    CHECK(m.str(0x5D3C98u) == "h_chrdsp.c");
    // its blink / mouth phase table 0x7B5180: six case addresses inside the function (3, 100, 2, 2, 2, 80 frames)
    for (u32 k = 0; k < 6; ++k) {
        const u32 target = r32(m, 0x7B5180u + 4 * k);
        CHECK(target >= 0x1059B0u);
        CHECK(target < 0x1059B0u + 3448u);
    }
    // sub_107B20 / sub_1071F0: the camp fade files
    CHECK(m.str(0x5D3FB0u) == "camp/camp/I_25.EPL");
    CHECK(m.str(0x5D3FD0u) == "camp/camp/i_time25_01.tmx");
    CHECK(m.str(0x5D3FF0u) == "h_fade.c");
    CHECK(m.str(0x5D3EB0u) == "camp/fade/if_lr_0a.anm");
    CHECK(m.str(0x5D3F90u) == "camp/fade/if_move_4b.anm");
    // sub_111610: its two error messages
    CHECK(m.str(0x5D6B80u) == "STREAM OPEN ERROR MAESTRO \n");
    CHECK(m.str(0x5D6BA0u) == "FIND CHUMK ERROR MAESTRO \n");
    // sub_2496E0: the particle count message; sub_2095A0: its source file
    CHECK(m.str(0x68E8B0u) == "sfl_eff: max %d\n");
    CHECK(m.str(0x6850A8u) == "baus_main.c");
}

#endif  // P3FES_GAME_HAVE_GENERATED
