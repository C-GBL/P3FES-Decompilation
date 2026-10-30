// Phase 5 pair tests for the render_world slice (game/src/render/world.cpp): RenderWare's world -- sectors, atomics,
// clump render, geometry locks and the mesh-build helpers, the PS2All instancing and the MatFX / skin / PDS set-up
// (docs/ANALYSIS/22_rendering.md sections 2.2, 2.3, 3.1, 7.3). Each hand-written function and the recompiled body it
// replaces run on identical guest machines built from random worlds (sector lists, BSP trees, light lists, atomics,
// meshes, Im3D records, instance records) and from the real RW state of the battle and dorm snapshots
// (extracted/_ours/*/eeMemory.bin beside the ELF's tree; skipped when absent).
//
// Stricter than the Outcome (as test_render_ptank.cpp): per pair this file compares EVERY general register in 128
// bits, HI/LO, all FPU registers, ACC, FCR31 and the whole VU0 state at the return, the whole register file (GPRs,
// HI/LO, SA, FPRs, FCR31) and the cycle count at EVERY check point, the bus access log, the scratchpad, the world
// region of the case, the RW globals / driver windows, the WHOLE stack window (live and dead: the hand versions write
// the original's spills), the virtual cycles, the check-point and syscall counts. FPRs, ACC, HI/LO and VU0 start
// random, so a register the original leaves alone must stay alone. Callbacks reached through `jalr` are pointed at
// small recompiled stand-ins, including a non-leaf one that spills the $ra it gets below its $sp (sub_1F1C50, returns
// *(gp-18968)); a callee kept out of the emitted set is a missing-function stop, and the pair is then compared at the
// stop (the same function, the same register file and memory). Host-side checks restate documented rules.
#include "pair_harness.h"

#include "p3fes/game/world.h"

#include <algorithm>
#include <array>
#include <bit>
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
P3FES_DECL_PAIR(fn_worldSectorRenderDispatch_00499230)
P3FES_DECL_PAIR(fn_worldSetSectorRenderCallBack_0049a3d0)
P3FES_DECL_PAIR(fn_RpWorldRender_0049a250)
P3FES_DECL_PAIR(fn__rpSectorDefaultRenderCallBack_00499b90)
P3FES_DECL_PAIR(fn_worldForAllLights_00499c20)
P3FES_DECL_PAIR(fn_worldSectorForAllLights_00499ca0)
P3FES_DECL_PAIR(fn_worldForAllSectors_0049a870)
P3FES_DECL_PAIR(fn_worldSectorGetWorld_0049a170)
P3FES_DECL_PAIR(fn_WorldSectorRender_00499320)
P3FES_DECL_PAIR(fn_sub_499140_00499140)
P3FES_DECL_PAIR(fn_atomicGetWorldBoundingSphere_004912b0)
P3FES_DECL_PAIR(fn_RpClumpRender_00491630)
P3FES_DECL_PAIR(fn_geometryLock_00493370)
P3FES_DECL_PAIR(fn_sub_498E30_00498e30)
P3FES_DECL_PAIR(fn_meshHeaderForAllMeshes_00495f10)
P3FES_DECL_PAIR(fn_triStripTriangleEdge_00496e80)
P3FES_DECL_PAIR(fn_meshSortCompare_004965a0)
P3FES_DECL_PAIR(fn_triStripTakeTriangle_00496f60)
P3FES_DECL_PAIR(fn_matfxSetSectorPipeline_00469d00)
P3FES_DECL_PAIR(fn_matfxSetAtomicPipeline_00469d60)
P3FES_DECL_PAIR(fn_sub_469DC0_00469dc0)
P3FES_DECL_PAIR(fn_RpPDS_G3d_Skin_PS2AllInstanceCallBack_0046eb10)
P3FES_DECL_PAIR(fn_RpMeshPS2AllInstanceCallBack_004a0dc0)
P3FES_DECL_PAIR(fn_sub_4A2780_004a2780)
P3FES_DECL_PAIR(fn_ps2AllSectorLightCB_004a3f20)
P3FES_DECL_PAIR(fn_sub_49C7A0_0049c7a0)
P3FES_DECL_PAIR(fn_ps2AllIm3DObjectSetup_004a2560)
P3FES_DECL_PAIR(fn_pds2DObjectSetupA_0046fb80)
P3FES_DECL_PAIR(fn_pds2DObjectSetupB_00470790)
P3FES_DECL_PAIR(fn_pds2DObjectSetupC_00471220)
P3FES_DECL_PAIR(fn_ps2AllSectorObjectSetup_004a4060)
P3FES_DECL_PAIR(fn_matfxEffectMatrix_0046b060)
P3FES_DECL_PAIR(fn_sub_46BAB0_0046bab0)
P3FES_DECL_PAIR(fn_sub_46BD00_0046bd00)
P3FES_DECL_PAIR(fn_skinInstanceWeights_0046b1b0)
P3FES_DECL_PAIR(fn_sub_4687E0_004687e0)
P3FES_DECL_PAIR(fn_triStripExtend_00497130)
P3FES_DECL_PAIR(fn_PS2AllNodeInstance_0049faa0)
P3FES_DECL_PAIR(fn_sub_4A35C0_004a35c0)
P3FES_DECL_PAIR(fn_ps2AllIm3DInstance_004a2bb0)
P3FES_DECL_PAIR(fn_ps2AllMatClusterLayout_0049cc70)
P3FES_DECL_PAIR(fn_ps2AllInstanceSizes_0049d4d0)
P3FES_DECL_PAIR(fn_ps2AllInstanceDmaChain_0049dc70)
P3FES_DECL_PAIR(fn_ps2AllSectorInstance_004a42f0)
P3FES_DECL_PAIR(fn_ps2AllAtomicInstance_004a1430)
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
namespace gw = p3fes::game::world;

// --- guest layout ------------------------------------------------------------------------------------------
constexpr u32 kGpBase = 0x007D2CF0u;
constexpr u32 gpv(s32 off) { return kGpBase + static_cast<u32>(off); }
constexpr u32 kWorld = 0x01900000u;  // the random records of a case
constexpr u32 kWorldLen = 0x20000u;
constexpr u32 kGpWindow = gpv(-20800);
constexpr u32 kGpWindowLen = 4400;
constexpr u32 kRwWindow = 0x0095D000u;  // the skin / PS2All globals, the light block, the RW globals and plugins
constexpr u32 kRwWindowLen = 0x9000u;
constexpr u32 kStackLo = kSp - kDeadStack;
constexpr u32 kStackLen = kDeadStack + 0x100;
constexpr u32 kD8Chcr = 0x1000D000u, kD9Chcr = 0x1000D400u;
constexpr u32 kRwGlobals = 0x00960070u;
constexpr u32 kCurCamera = kRwGlobals, kCurWorld = kRwGlobals + 4, kFrameStamp = 0x00960078u;

// Stand-ins reached through `jalr` (recompiled or replaced elsewhere, in the emitted set).
constexpr u32 kLeafOne = 0x4A2BA0u;     // returns 1
constexpr u32 kNonLeaf = 0x1F1C50u;     // spills $ra in a 16-byte frame, returns *(gp-18968)
constexpr u32 kRetA1 = 0x4B3710u;       // `jr ra; move v0, a1`
constexpr s32 kGpStubResult = -18968;

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region> kBase = {{kWorld, kWorldLen}, {kGpWindow, kGpWindowLen}, {kRwWindow, kRwWindowLen}};

// --- guest RAM helpers -------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { m.at(va)[0] = v; }
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
// A circular RW list head at `head` with the links `links` (each link {next, prev}).
void link_list(Machine& m, u32 head, const std::vector<u32>& links) {
    u32 prev = head;
    for (u32 l : links) {
        w32(m, prev, l);
        w32(m, l + 4, prev);
        prev = l;
    }
    w32(m, prev, head);
    w32(m, head + 4, prev);
}

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
    bool stopped = false;
    u32 stop_pc = 0;
    std::string why;
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

// The scripted hardware of a case: register values and per-register read scripts, extra GPR inputs.
struct Hw {
    std::map<u32, u64> regs{{kD8Chcr, 0}, {kD9Chcr, 0}};  // the scratchpad channels idle
    std::map<u32, std::vector<u64>> reads;
    std::map<unsigned, u64> gpr_in;  // set after the randomised context
};

// The bus of a run: pair_harness.h's ScriptedBus behaviour plus a fake DMAC for the scratchpad channels (as
// test_render_ptank.cpp): a CHCR write with STR moves QWC quadwords at once (D9 toSPR, D8 fromSPR), then clears STR
// and QWC and sets the channel's D_STAT bit, so the DMA packet layer's waits end; both runs see the same device.
constexpr u32 kDStat = 0x1000E010u;
class DmacBus final : public hle::HwBus {
public:
    using Access = rt_test::RecordingBus::Access;
    std::vector<Access> log;
    std::map<u32, u64> regs;
    std::map<u32, std::vector<u64>> reads;
    std::map<u32, std::size_t> next_read;
    EEMemory* mem = nullptr;
    hle::Timebase tb;

    u64 value(u32 pa) {
        auto s = reads.find(pa);
        if (s != reads.end()) {
            std::size_t& k = next_read[pa];
            if (k < s->second.size()) return s->second[k++];
        }
        auto it = regs.find(pa);
        return it != regs.end() ? it->second : rt_test::RecordingBus::pattern(pa);
    }
    void store(u32 pa, u64 v) {
        if (pa == kDStat) {
            const u64 old = regs.count(pa) ? regs[pa] : 0;
            regs[pa] = (old & ~(v & 0xFFFFu)) ^ (v & 0xFFFF0000u);
            return;
        }
        regs[pa] = v;
        if ((pa == kD8Chcr || pa == kD9Chcr) && (v & 0x100u)) transfer(pa);
    }
    void transfer(u32 chcr) {
        const u32 qwc = static_cast<u32>(regs[chcr + 0x20]) & 0xFFFFu;
        const u32 madr = static_cast<u32>(regs[chcr + 0x10]);
        const u32 sadr = static_cast<u32>(regs[chcr + 0x80]) & 0x3FF0u;
        for (u32 q = 0; q < qwc; ++q) {
            const u32 ma = (madr & 0x01FFFFF0u) + 16 * q;
            u8* ram = mem->main_ram() + (ma % EEMemory::kMainRamSize);
            u8* spr = mem->scratchpad() + ((sadr + 16 * q) & 0x3FF0u);
            if (chcr == kD9Chcr)
                std::memcpy(spr, ram, 16);
            else
                std::memcpy(ram, spr, 16);
        }
        regs[chcr] &= ~0x100ull;
        regs[chcr + 0x20] = 0;
        regs[kDStat] = (regs.count(kDStat) ? regs[kDStat] : 0) | (chcr == kD9Chcr ? 0x200u : 0x100u);
    }

    void map(u32, u32, hle::HwDevice*) override {}
    void set_dma_handler(unsigned, hle::DmaChannelHandler*) override {}
    void raise_intc(unsigned) override {}
    void dma_complete(unsigned) override {}
    const hle::Timebase& time() const override { return tb; }

    u8 read8(u32 pa) override { log.push_back({false, 8, pa, 0, 0}); return static_cast<u8>(value(pa)); }
    u16 read16(u32 pa) override { log.push_back({false, 16, pa, 0, 0}); return static_cast<u16>(value(pa)); }
    u32 read32(u32 pa) override { log.push_back({false, 32, pa, 0, 0}); return static_cast<u32>(value(pa)); }
    u64 read64(u32 pa) override { log.push_back({false, 64, pa, 0, 0}); return value(pa); }
    u128 read128(u32 pa) override {
        log.push_back({false, 128, pa, 0, 0});
        u128 r;
        r.u64[0] = value(pa);
        r.u64[1] = ~r.u64[0];
        return r;
    }
    void write8(u32 pa, u8 v) override { log.push_back({true, 8, pa, v, 0}); store(pa, v); }
    void write16(u32 pa, u16 v) override { log.push_back({true, 16, pa, v, 0}); store(pa, v); }
    void write32(u32 pa, u32 v) override { log.push_back({true, 32, pa, v, 0}); store(pa, v); }
    void write64(u32 pa, u64 v) override { log.push_back({true, 64, pa, v, 0}); store(pa, v); }
    void write128(u32 pa, const u128& v) override { log.push_back({true, 128, pa, v.u64[0], v.u64[1]}); store(pa, v.u64[0]); }
};

RegSnap reg_snap(const EEContext& ctx) {
    RegSnap s;
    s.cycles = ctx.cycles;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = ctx.gpr[r];
    s.hi = ctx.hi;
    s.lo = ctx.lo;
    s.sa = ctx.sa;
    s.fcr31 = ctx.fcr31;
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = ctx.fpr[i];
    return s;
}

// The hooks of a run: HwHooks' behaviour over the DmacBus; a fatal event (a missing function of the emitted set, a
// misaligned access) records where it stopped and ends the run.
class WHooks final : public RtHooks {
public:
    DmacBus bus_;
    int syscalls = 0;
    int checks = 0;
    int traps = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    std::vector<RegSnap> snaps;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        snaps.push_back(reg_snap(ctx));
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stopped = true;
        stop_pc = pc;
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
};

Snap run_full(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Region>& regions, const Hw& hw) {
    WHooks hooks;
    hooks.bus_.regs = hw.regs;
    hooks.bus_.reads = hw.reads;
    hooks.bus_.mem = &m.mem;
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
    std::string why;
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent& e) {
        why = e.what.substr(0, 48);
    }
    Snap s;
    s.why = why;
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
    s.stopped = hooks.stopped;
    s.stop_pc = hooks.stop_pc;
    s.snaps = std::move(hooks.snaps);
    s.bus = std::move(hooks.bus_.log);
    s.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    s.stack = m.bytes(kStackLo, kStackLen);
    for (const Region& r : regions) s.regions.push_back(m.bytes(r.va, r.len));
    std::memset(m.at(kStackLo), 0, kDeadStack);
    return s;
}

int g_pairs = 0;
int g_stops = 0;
std::map<std::string, int> g_stop_kinds;  // the stops of the recompiled runs, by function / reason

std::size_t first_diff(const std::vector<u8>& a, const std::vector<u8>& b) {
    std::size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) ++i;
    return i;
}

u64 gpr_of(const Snap& s, unsigned r) { return s.gpr[r].u64[0]; }

// Runs hand and recomp from the same machine state (the scratchpad and every region restored in between) and
// requires identical results everywhere. After the pair the recompiled run's output is in place.
std::pair<Snap, Snap> pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Hw& hw = {},
                           const std::vector<Region>& extra = {}) {
    std::vector<Region> regions = kBase;
    regions.insert(regions.end(), extra.begin(), extra.end());
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    std::vector<std::vector<u8>> before;
    for (const Region& r : regions) before.push_back(m.bytes(r.va, r.len));
    const std::string label = std::string(what) + " seed " + std::to_string(seed);
    INFO(label);
    Snap h = run_full(m, hand, args, seed, regions, hw);
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    Snap r = run_full(m, recomp, args, seed, regions, hw);
    ++g_pairs;
    g_stops += r.stopped ? 1 : 0;
    if (r.stopped) ++g_stop_kinds[std::string(what) + ": " + r.why];
    INFO("stops: hand " << h.stopped << " at " << hex64(h.stop_pc) << ", recomp " << r.stopped << " at " << hex64(r.stop_pc));
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    if (h.stopped != r.stopped || h.cycles != r.cycles) {
        MESSAGE("first mismatch of " << label << ": hand cycles " << h.cycles << " checks " << h.checks << ", recomp cycles "
                                     << r.cycles << " checks " << r.checks);
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

// The snapshot's main RAM (extracted/_ours/<dir>/eeMemory.bin beside the ELF's tree), empty when absent.
std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

// A stand-in callback: the leaf returning 1, the non-leaf returning *(gp-18968) (set to `result`), or the leaf
// returning its $a1.
u32 put_callback(Machine& m, std::mt19937& rng, bool may_stop) {
    const u32 cb = pick(rng, {kLeafOne, kNonLeaf, kNonLeaf, kRetA1});
    w32(m, gpv(kGpStubResult), may_stop && chance(rng, 25) ? 0u : 1u + rng() % 1000);
    return cb;
}

}  // namespace

// =========================================================================================================
// World sectors
// =========================================================================================================

TEST_CASE("game(render_world): the sector callbacks, the default sector render and RpWorldRender's set-up") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x499230u};
    const u32 world = kWorld + 0x100, sector = kWorld + 0x400, pipe = kWorld + 0x800, node = kWorld + 0x880,
              def = kWorld + 0x8C0, heap = kWorld + 0x900;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        w32(m, kCurWorld, world);
        w32(m, world + 104, put_callback(m, rng, true));
        // worldSectorRenderDispatch: a tail jump to the world's callback (the sector in $a0)
        pair(m, PAIR(fn_worldSectorRenderDispatch_00499230), Args{sector, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1), "worldSectorRenderDispatch");
        // worldSetSectorRenderCallBack: the callback or the default
        const u32 cb = chance(rng, 40) ? 0u : rng();
        pair(m, PAIR(fn_worldSetSectorRenderCallBack_0049a3d0), Args{world, cb, rng64(rng), rng64(rng)}, seed_of(i, 2), "worldSetSectorRenderCallBack");
        CHECK(r32(m, world + 104) == (cb != 0 ? cb : 0x499B90u));
        // _rpSectorDefaultRenderCallBack: a pipeline whose first node's body is a stand-in (RxPipelineExecute calls it
        // with (node, &data)); the heap (gp-16832) needs no reset (+24 = 0)
        w32(m, pipe + 8, node);
        w32(m, node + 0, def);
        w32(m, def + 4, put_callback(m, rng, true));
        w32(m, gpv(-16832), heap);
        w32(m, heap + 24, 0);
        w16(m, sector + 132, static_cast<u16>(pick(rng, {0, 1, 7, 0x8000, 0xFFFF})));
        w32(m, sector + 124, chance(rng, 50) ? pipe : 0u);
        w32(m, world + 108, chance(rng, 50) ? pipe : 0u);
        const u32 modoff = 4u * (rng() % 64);
        w32(m, gpv(gw::kGpPs2AllModule), modoff);
        w32(m, kRwGlobals + modoff + 64, pipe);
        pair(m, PAIR(fn__rpSectorDefaultRenderCallBack_00499b90), Args{sector, rng64(rng), rng64(rng), rng64(rng)},
             seed_of(i, 3), "_rpSectorDefaultRenderCallBack", {}, {{0x965A40u, 0x80}});
    }
}

TEST_CASE("game(render_world): the light walks worldForAllLights / worldSectorForAllLights and the BSP walk worldForAllSectors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x499C20u};
    const u32 world = kWorld + 0x100, sector = kWorld + 0x300;
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x4000, rng);
        w32(m, kCurWorld, world);
        // world lights: list at world +60, link at light +52
        std::vector<u32> links;
        const u32 n = pick(rng, {0, 1, 2, 3, 5, 8});
        for (u32 k = 0; k < n; ++k) links.push_back(kWorld + 0x1000 + 0x80 * k + 52);
        link_list(m, world + 60, links);
        const u32 cb = put_callback(m, rng, true);
        pair(m, PAIR(fn_worldForAllLights_00499c20), Args{cb, chance(rng, 20) ? 0u : rng(), rng64(rng), rng64(rng)}, seed_of(i, 1),
             "worldForAllLights");
        // sector lights: list at sector +64 of {next, prev, light}, a light may be 0
        std::vector<u32> ties;
        for (u32 k = 0; k < n; ++k) {
            const u32 t = kWorld + 0x2000 + 0x20 * k;
            ties.push_back(t);
            w32(m, t + 8, chance(rng, 20) ? 0u : kWorld + 0x1000 + 0x80 * k);
        }
        link_list(m, sector + 64, ties);
        const u32 cb2 = put_callback(m, rng, true);
        pair(m, PAIR(fn_worldSectorForAllLights_00499ca0), Args{sector, cb2, chance(rng, 20) ? 0u : rng(), rng64(rng)}, seed_of(i, 2),
             "worldSectorForAllLights");
        // a BSP tree: plane nodes {type >= 0, .., +8 left, +12 right}, sectors {type < 0}
        u32 next = kWorld + 0x3000;
        auto make = [&](auto& self, int depth) -> u32 {
            const u32 at = next;
            next += 0x20;
            if (depth == 0 || chance(rng, 30)) {
                w32(m, at, 0x80000000u | rng());
                return at;
            }
            w32(m, at, rng() & 0x7FFFFFFFu);
            const u32 l = self(self, depth - 1);
            const u32 r = self(self, depth - 1);
            w32(m, at + 8, l);
            w32(m, at + 12, r);
            return at;
        };
        w32(m, world + 28, make(make, static_cast<int>(rng() % 6)));
        const u32 cb3 = put_callback(m, rng, true);
        pair(m, PAIR(fn_worldForAllSectors_0049a870), Args{world, cb3, chance(rng, 20) ? 0u : rng(), rng64(rng)}, seed_of(i, 3),
             "worldForAllSectors");
    }
}

TEST_CASE("game(render_world): worldSectorGetWorld finds the world of a sector (address test or BSP search)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x49A170u};
    int found = 0;
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x6000, rng);
        const u32 modoff = 0x200u + 4u * (rng() % 16);
        w32(m, gpv(gw::kGpWorldModule), modoff);
        const u32 head = kRwGlobals + modoff + 4;
        // worlds: chunk {world, block size, link at +8}; world +3 bit 0: sectors inside the block
        std::vector<u32> links;
        std::vector<u32> sectors;
        const u32 n = pick(rng, {0, 1, 2, 3, 4});
        for (u32 k = 0; k < n; ++k) {
            const u32 chunk = kWorld + 0x100 + 0x40 * k, wld = kWorld + 0x1000 + 0x1000 * k;
            w32(m, chunk, wld);
            w32(m, chunk + 4, 0x400 + 0x100 * (rng() % 8));
            links.push_back(chunk + 8);
            const bool inside = chance(rng, 50);
            w8(m, wld + 3, static_cast<u8>((rng() & 0xFE) | (inside ? 1 : 0)));
            // a small BSP: root plane with two sectors
            const u32 root = wld + 0x100, s0 = wld + 0x200, s1 = wld + 0x300;
            w32(m, wld + 28, root);
            w32(m, root, rng() & 0x7FFFFFFFu);
            w32(m, root + 8, s0);
            w32(m, root + 12, s1);
            w32(m, s0, 0x80000000u | rng());
            w32(m, s1, 0x80000000u | rng());
            sectors.push_back(s0);
            sectors.push_back(s1);
        }
        link_list(m, head, links);
        u32 target = chance(rng, 80) && !sectors.empty() ? sectors[rng() % sectors.size()] : kWorld + 0x8000u;
        if (chance(rng, 10)) target = kWorld + 0x1000;  // the world's own address
        const auto p = pair(m, PAIR(fn_worldSectorGetWorld_0049a170), Args{target, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1),
                            "worldSectorGetWorld", {}, {{kRwGlobals + 0x200, 0x100}});
        found += gpr_of(p.first, GPR_V0) != 0;
    }
    CHECK(found > 100);
}

TEST_CASE("game(render_world): the MatFX pipe setters and the PS2All / skin instance dispatch (stops at the instancers)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x469D00u};
    for (int i = 0; i < 200; ++i) {
        fill_random(m, kWorld, 0x2000, rng);
        // matfxSetAtomicPipeline: atomic +24 geometry, flag 0x80 at +8
        const u32 atomic = kWorld + 0x100, geometry = kWorld + 0x200;
        w32(m, atomic + 24, geometry);
        w32(m, geometry + 8, rng() & (chance(rng, 50) ? 0xFFFFFFFFu : ~0x80u));
        pair(m, PAIR(fn_matfxSetAtomicPipeline_00469d60), Args{atomic, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1), "matfxSetAtomicPipeline");
        // matfxSetSectorPipeline: the sector's world through worldSectorGetWorld (one world holding the sector in its block)
        const u32 modoff = 0x200u;
        w32(m, gpv(gw::kGpWorldModule), modoff);
        const u32 chunk = kWorld + 0x400, wld = kWorld + 0x800, sector = kWorld + 0x900;
        w32(m, chunk, wld);
        w32(m, chunk + 4, 0x400);
        link_list(m, kRwGlobals + modoff + 4, {chunk + 8});
        w8(m, wld + 3, 1);
        w32(m, wld + 8, rng() & (chance(rng, 50) ? 0xFFFFFFFFu : ~0x80u));
        pair(m, PAIR(fn_matfxSetSectorPipeline_00469d00), Args{sector, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 2), "matfxSetSectorPipeline",
             {}, {{kRwGlobals + 0x200, 0x100}});
        // RpMeshPS2AllInstanceCallBack: the object type byte 0xFF (sector) or not; the instancers stop (not emitted)
        const u32 pd = kWorld + 0x1000, obj = kWorld + 0x1100;
        w32(m, pd + 8, obj);
        w8(m, obj, static_cast<u8>(chance(rng, 50) ? 0xFF : rng()));
        pair(m, PAIR(fn_RpMeshPS2AllInstanceCallBack_004a0dc0), Args{pd, rng(), rng64(rng), rng64(rng)}, seed_of(i, 3),
             "RpMeshPS2AllInstanceCallBack");
        // the skin instance callback: native geometries (flag 0x01000000) return 1, others stop at ps2AllAtomicInstance
        w32(m, obj + 24, geometry);
        w32(m, geometry + 8, chance(rng, 50) ? 0x01000000u | rng() : rng() & ~0x01000000u);
        const u32 inst = kWorld + 0x1200;
        pair(m, PAIR(fn_RpPDS_G3d_Skin_PS2AllInstanceCallBack_0046eb10), Args{pd, inst, rng64(rng), rng64(rng)}, seed_of(i, 4),
             "RpPDS_G3d_Skin_PS2AllInstanceCallBack");
        // the tail calls (stop at their targets)
        pair(m, PAIR(fn_sub_469DC0_00469dc0), Args{rng(), rng(), rng64(rng), rng64(rng)}, seed_of(i, 5), "sub_469DC0");
        pair(m, PAIR(fn_sub_4A2780_004a2780), Args{rng(), rng(), rng64(rng), rng64(rng)}, seed_of(i, 6), "sub_4A2780");
    }
}

namespace {
// A frame whose LTM (+80, 16 floats, type bits at +92) is clean: its root (+160) has no dirty bits (+3).
constexpr u32 kRoot = kWorld + 0x1F000;
void put_frame(Machine& m, u32 frame, std::mt19937& rng) {
    fill_floats(m, frame + 80, 16, rng);
    w32(m, frame + 80 + 12, chance(rng, 40) ? 3u : rng() & 0x20003u);
    w32(m, frame + 160, kRoot);
    w32(m, kRoot, rng());
    w8(m, kRoot + 3, static_cast<u8>(rng() & ~3u));
}
// The current camera (RW globals +0) with its frame (+4) and view matrix (+32), and the frustum planes the sector
// test reads (camera + gp-16972 + 96: 6 planes of 20 bytes, the corner-index bytes at +16..+18 in 0..1).
constexpr u32 kCamera = kWorld + 0x1E000, kCamFrame = kWorld + 0x1E800;
void put_camera(Machine& m, std::mt19937& rng) {
    fill_floats(m, kCamera, 0x200 / 4, rng);
    put_frame(m, kCamFrame, rng);
    w32(m, kCamera + 4, kCamFrame);
    w32(m, kCurCamera, kCamera);
    const u32 off = 4u * (rng() % 32);
    w32(m, gpv(-16972), off);
    for (u32 p = 0; p < 6; ++p)
        for (u32 k = 0; k < 3; ++k) w8(m, kCamera + off + 96 + 20 * p + 16 + k, static_cast<u8>(rng() % 2));
}
const std::vector<Region> kMeshData = {{0x0077DE00u, 0x200}};  // the Im3D / PDS 2D mesh header 0x77DEC0
}  // namespace

TEST_CASE("game(render_world): the Im3D, PDS 2D and world sector object set-ups") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A2560u};
    const u32 pd = kWorld + 0x100, rec = kWorld + 0x200, xform = kWorld + 0x300, hdr = kWorld + 0x400, ref = kWorld + 0x180,
              out = kWorld + 0x700;
    struct S {
        const char* name;
        Fn hand, recomp;
    };
    const S setups[] = {{"ps2AllIm3DObjectSetup", PAIR(fn_ps2AllIm3DObjectSetup_004a2560)}, {"pds2DObjectSetupA", PAIR(fn_pds2DObjectSetupA_0046fb80)},
                        {"pds2DObjectSetupB", PAIR(fn_pds2DObjectSetupB_00470790)}, {"pds2DObjectSetupC", PAIR(fn_pds2DObjectSetupC_00471220)}};
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x2000, rng);
        put_camera(m, rng);
        // the Im3D record: +0 flags (4: frustum result 2), +4 transform or 0, +36 mode, +40 / +44 the counts
        w32(m, rec, rng() & (chance(rng, 50) ? 0xFFFFFFFFu : ~4u));
        w32(m, rec + 4, chance(rng, 50) ? 0u : xform);
        fill_floats(m, xform, 16, rng);
        w8(m, rec + 36, static_cast<u8>(rng() % 8));
        w32(m, rec + 40, chance(rng, 40) ? 0u : rng() % 100);
        w32(m, pd + 8, rec);
        w32(m, ref, out);
        w32(m, gpv(gw::kGpMeshModule), 4u * (rng() % 32));
        // the primitive flags of the mesh header the set-up reads back (pd +12; sub_4A24A0 points it at 0x77DEC0)
        w32(m, 0x77DEC0u, pick(rng, {1, 0, 2, 0x10, 8, 0x20, 3, 0x12, rng()}));
        // sub_4AAE60 (the PDS 2D set-ups): its cached path (0x95EF50 != 0): the RW camera record 0x95EF84 (+4 frame)
        w32(m, 0x95EF50u, 1);
        w32(m, 0x95EF84u, kCamera);
        const S& s = setups[i % 4];
        pair(m, s.hand, s.recomp, Args{pd, ref, rng64(rng), rng64(rng)}, seed_of(i, 1), s.name, {}, kMeshData);
        // documented: prim 4 for a strip (flag bit 0) / 3 for a list (flags 0 or 2) / 2 for a polyline (8)
        const u32 f = r32(m, 0x77DEC0u);
        const u8 prim = m.at(pd + 41)[0];
        if (f & 1) CHECK(prim == 4);
        else if ((f & 0xFF) == 0 || (f & 2)) CHECK(prim == 3);
        else if (f & 0x10) CHECK(prim == 4);
        else if (f & 8) CHECK(prim == 2);
        else CHECK(prim == 1);
    }
    // ps2AllSectorObjectSetup: a world sector (+120 mesh header, resEntry array at the plugin offset), the current world's flags
    // (native 0x01000000, lit 0x20, modulate 0x40), world / sector lights through ps2AllSectorLightCB (light +2 bit 1:
    // sub_49FF10 into the light block)
    const u32 sector = kWorld + 0x800, world = kWorld + 0x900, res = kWorld + 0xA00, entry = kWorld + 0xB00,
              lights = kWorld + 0x1000, block = kWorld + 0x3000;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x4000, rng);
        put_camera(m, rng);
        w32(m, pd + 8, sector);
        w32(m, sector + 120, hdr);
        w16(m, hdr + 4, static_cast<u16>(1 + rng() % 4));
        w32(m, hdr, pick(rng, {1, 0, 2, 0x10, 8, rng()}));
        const u32 off = 4u * (rng() % 16);
        w32(m, gpv(gw::kGpSectorResEntries), off);
        w32(m, sector + off, chance(rng, 85) ? res : 0u);
        w32(m, res, chance(rng, 80) ? r16(m, hdr + 4) : 7u);  // a count mismatch reallocates (sub_49E5A0)
        w32(m, res + 4, chance(rng, 20) ? 0u : entry);
        w32(m, entry + 40, chance(rng, 50) ? r32(m, pd + 24) : rng());
        w32(m, kCurWorld, world);
        w32(m, world + 8, rng() & (chance(rng, 30) ? 0xFFFFFFFFu : ~0x01000000u));
        w32(m, 0x960178u, kNonLeaf);  // RwMalloc: the non-leaf stand-in returning a buffer; RwFree: a leaf
        w32(m, 0x96017Cu, kLeafOne);
        w32(m, gpv(kGpStubResult), kWorld + 0x6000);
        // lights: the world's (+60) and the sector's ties (+64); bit 1 of +2 is rare (the light block is set up)
        std::vector<u32> links, ties;
        const u32 n = rng() % 4;
        for (u32 k = 0; k < n; ++k) {
            const u32 l = lights + 0x100 * k;
            w8(m, l + 1, static_cast<u8>(pick(rng, {1, 2, 0x80, 0x81, 0x82})));
            w8(m, l + 2, static_cast<u8>(chance(rng, 25) ? (rng() | 2u) : (rng() & ~2u)));
            fill_floats(m, l + 20, 8, rng);
            put_frame(m, l + 0x40, rng);
            w32(m, l + 4, l + 0x40);
            links.push_back(l + 52);
            const u32 t = kWorld + 0x2000 + 0x10 * k;
            w32(m, t + 8, l);
            ties.push_back(t);
        }
        link_list(m, world + 60, links);
        link_list(m, sector + 64, ties);
        w32(m, gpv(-17516), block + 16 * (rng() % 4));
        w32(m, gpv(-17520), pick(rng, {0, 1, 4, 123, 124}));
        pair(m, PAIR(fn_ps2AllSectorObjectSetup_004a4060), Args{pd, ref, rng64(rng), rng64(rng)}, seed_of(i, 2), "ps2AllSectorObjectSetup");
    }
}

TEST_CASE("game(render_world): the MatFX effect matrix, the skin weights and the MatFX raster combine") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46B060u};
    const u32 frame = kWorld + 0x100, obj = kWorld + 0x300, rec = kWorld + 0x380, recframe = kWorld + 0x400,
              out = kWorld + 0x600;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        put_camera(m, rng);
        put_frame(m, frame, rng);
        put_frame(m, recframe, rng);
        w32(m, obj + 8, rec);
        w8(m, rec, static_cast<u8>(chance(rng, 30) ? 0xFF : rng()));
        w32(m, rec + 4, recframe);
        // the cache key: hit, or one of the three parts different
        const u32 f = chance(rng, 20) ? 0u : frame;
        w32(m, gpv(gw::kGpFxCacheRecord), chance(rng, 60) ? rec : rng());
        w32(m, gpv(gw::kGpFxCacheFrame), chance(rng, 70) ? (f ? f : kCamFrame) : rng());
        const u64 stamp = r16(m, kFrameStamp);
        const u64 key = chance(rng, 70) ? stamp : rng64(rng);
        std::memcpy(m.at(gpv(gw::kGpFxCacheStamp)), &key, 8);
        w32(m, gw::kFxMatrix + 12, chance(rng, 40) ? 3u : rng());
        pair(m, PAIR(fn_matfxEffectMatrix_0046b060), Args{f, out, obj, rng64(rng)}, seed_of(i, 1), "matfxEffectMatrix");
        CHECK(std::memcmp(m.at(out), m.at(gw::kFxMatrix), 64) == 0);  // documented: the 16 words copied out
    }
    // skinInstanceWeights: mesh {indices, count}, skin +24 weights, destination
    const u32 mesh = kWorld + 0x100, skin = kWorld + 0x200, idx = kWorld + 0x1000, wts = kWorld + 0x2000, dst = kWorld + 0x8000;
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x10000, rng);
        const u32 n = pick(rng, {0, 1, 2, 7, 8, 9, 10, 16, 17, 25, 33, 100});
        for (u32 k = 0; k < n; ++k) w16(m, idx + 2 * k, static_cast<u16>(rng() % 256));
        w32(m, mesh, idx);
        w32(m, mesh + 4, chance(rng, 5) ? 0x80000000u | rng() : n);
        w32(m, skin + 24, wts);
        pair(m, PAIR(fn_skinInstanceWeights_0046b1b0), Args{mesh, skin, dst, rng64(rng)}, seed_of(i, 2), "skinInstanceWeights");
        if (static_cast<s32>(r32(m, mesh + 4)) > 0)  // documented: record k = weights[indices[k]]
            for (u32 k = 0; k < n; ++k) CHECK(std::memcmp(m.at(dst + 16 * k), m.at(wts + 16 * r16(m, idx + 2 * k)), 16) == 0);
    }
    // sub_4687E0: the raster combine; its RwImage callees stay out of the emitted set (a stop at the first one)
    for (int i = 0; i < 50; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        const u32 tex = kWorld + 0x100, tex2 = kWorld + 0x200, ras = kWorld + 0x300;
        w32(m, tex, ras);
        w32(m, tex2, ras);
        pair(m, PAIR(fn_sub_4687E0_004687e0), Args{chance(rng, 50) ? tex2 : 0u, tex, rng64(rng), rng64(rng)}, seed_of(i, 3),
             "sub_4687E0");
    }
}

TEST_CASE("game(render_world): the Rt2d path draws sub_46BAB0 / sub_46BD00 (a chain of paths, both pipelines)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x46BAB0u};
    const u32 brush = kWorld + 0x100, tex = kWorld + 0x200, pipe = kWorld + 0x800, node = kWorld + 0x880,
              def = kWorld + 0x8C0, heap = kWorld + 0x900, verts = kWorld + 0x4000;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x8000, rng);
        // a chain of 1..3 paths: +0 the vertices, +4 their count, +8 data (0 skips in sub_46BD00), +12 non-zero when
        // flattened, +16 inset, +20 next
        const u32 n = 1 + rng() % 3;
        for (u32 k = 0; k < n; ++k) {
            const u32 p = kWorld + 0x1000 + 0x100 * k;
            w32(m, p + 8, chance(rng, 15) ? 0u : p + 0x40);
            w32(m, p + 12, 1 + rng());
            w32(m, p, verts + 0x800 * k);
            w32(m, p + 4, pick(rng, {1, 2, 3, 4, 10, 40, 41, 79, 80, 81, 120}));
            fill_floats(m, verts + 0x800 * k, 0x800 / 4, rng);
            fill_floats(m, p + 16, 1, rng);
            w32(m, p + 20, k + 1 < n ? p + 0x100 : 0u);
        }
        w32(m, brush + 104, chance(rng, 30) ? 0u : tex);
        w32(m, 0x960090u, put_callback(m, rng, false));  // the device's render state setter (RW globals +144)
        // the two pipelines (0x95F040 / 0x95F050) with a stand-in body; the packet record (sub_4F2710: RW globals +
        // gp-16848 + 64)
        w32(m, pipe + 8, node);
        w32(m, node + 0, def);
        w32(m, def + 4, put_callback(m, rng, true));
        w32(m, gpv(-16832), heap);
        w32(m, heap + 24, 0);
        w32(m, 0x95F040u, pipe);
        w32(m, 0x95F050u, pipe);
        w32(m, gpv(-16848), 0x400u + 16u * (rng() % 8));
        if (i % 2 == 0)
            pair(m, PAIR(fn_sub_46BAB0_0046bab0), Args{kWorld + 0x1000, brush, rng64(rng), rng64(rng)}, seed_of(i, 1), "sub_46BAB0");
        else
            pair(m, PAIR(fn_sub_46BD00_0046bd00), Args{kWorld + 0x1000, brush, rng64(rng), rng64(rng)}, seed_of(i, 2), "sub_46BD00");
    }
}

TEST_CASE("game(render_world): the tri-strip helpers triStripTriangleEdge / triStripTakeTriangle / triStripExtend and the mesh sort compare") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x497130u};
    // a random triangle soup with adjacency: triangles (64 bytes: +4/+8/+12 edges, +16/+20 bucket links, +24 used,
    // +28 marked, +32 bucket byte), edges (16 bytes: u16 vertices at +0/+2, triangles at +4/+8), 256 bucket heads
    const u32 tris = kWorld + 0x1000, edges = kWorld + 0x3000, buckets = kWorld + 0x4000, strip = kWorld + 0x100,
              idx = kWorld + 0x5000;
    int taken = 0;
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x6000, rng);
        const u32 nt = 1 + rng() % 24, ne = 1 + rng() % 40;
        auto tri = [&](u32 k) { return tris + 64 * k; };
        auto edge = [&](u32 k) { return edges + 16 * k; };
        for (u32 k = 0; k < ne; ++k) {
            w16(m, edge(k), static_cast<u16>(rng() % 6));
            w16(m, edge(k) + 2, static_cast<u16>(rng() % 6));
            w32(m, edge(k) + 4, chance(rng, 10) ? 0u : tri(rng() % nt));
            w32(m, edge(k) + 8, chance(rng, 25) ? 0u : tri(rng() % nt));
        }
        for (u32 k = 0; k < nt; ++k) {
            for (u32 e = 0; e < 3; ++e) w32(m, tri(k) + 4 + 4 * e, edge(rng() % ne));
            w32(m, tri(k) + 16, chance(rng, 40) ? 0u : tri(rng() % nt));
            w32(m, tri(k) + 20, chance(rng, 40) ? 0u : tri(rng() % nt));
            w32(m, tri(k) + 24, chance(rng, 70) ? 0u : 1u);
            w32(m, tri(k) + 28, chance(rng, 70) ? 0u : 1u);
            w8(m, tri(k) + 32, static_cast<u8>(rng() % 4));
        }
        for (u32 b = 0; b < 256; ++b) w32(m, buckets + 4 * b, chance(rng, 50) ? 0u : tri(rng() % nt));
        const u32 mode = pick(rng, {0, 2, 3, 4, 5, 7});
        switch (i % 3) {
        case 0:
            pair(m, PAIR(fn_triStripTriangleEdge_00496e80), Args{tri(rng() % nt), rng() % 6, rng() % 6 | (rng() << 16), rng64(rng)},
                 seed_of(i, 1), "triStripTriangleEdge");
            break;
        case 1:
            pair(m, PAIR(fn_triStripTakeTriangle_00496f60), Args{tri(rng() % nt), buckets, mode, rng64(rng)}, seed_of(i, 2), "triStripTakeTriangle");
            break;
        default: {
            // the strip so far: count >= 1 vertices at idx (room for every triangle)
            const u32 count = 1 + rng() % 3;
            for (u32 k = 0; k < count; ++k) w16(m, idx + 2 * k, static_cast<u16>(rng() % 6));
            w32(m, strip, idx);
            w32(m, strip + 4, count);
            Hw hw;
            hw.gpr_in[GPR_T0] = mode;
            const auto p = pair(m, PAIR(fn_triStripExtend_00497130), Args{strip, chance(rng, 5) ? 0u : edge(rng() % ne), buckets, rng64(rng)},
                                seed_of(i, 3), "triStripExtend", hw);
            taken += static_cast<int>(gpr_of(p.first, GPR_V0));
            break;
        }
        }
    }
    CHECK(taken > 100);
    // meshSortCompare: two records ({.., +8 material}), materials with textures / rasters / colour alpha and the u16 keys
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        const u32 ra = kWorld + 0x100, rb = kWorld + 0x140, pa = kWorld + 0x180, pb = kWorld + 0x184;
        const u32 mats[2] = {kWorld + 0x200, kWorld + 0x300};
        for (u32 k = 0; k < 2; ++k) {
            const u32 mat = mats[k], tex = mat + 0x40, ras = mat + 0x80;
            w32(m, mat, chance(rng, 20) ? 0u : tex);
            w32(m, tex, ras);
            w8(m, ras + 35, static_cast<u8>(pick(rng, {0, 1, 3, 5, 2, 0x15, 0x11, rng()})));
            w8(m, mat + 7, static_cast<u8>(chance(rng, 60) ? 255 : rng()));
            for (u32 o : {12u, 14u, 16u, 18u}) w16(m, mat + o, static_cast<u16>(rng() % 4));
        }
        w32(m, ra + 8, chance(rng, 5) ? 0u : mats[0]);
        w32(m, rb + 8, chance(rng, 10) ? r32(m, ra + 8) : mats[1]);
        w32(m, pa, ra);
        w32(m, pb, rb);
        pair(m, PAIR(fn_meshSortCompare_004965a0), Args{pa, pb, rng64(rng), rng64(rng)}, seed_of(i, 4), "meshSortCompare");
    }
}

TEST_CASE("game(render_world): PS2AllNodeInstance (the gather / callback path on random records) and sub_4A35C0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x49FAA0u};
    const u32 pd = kWorld + 0x100, mat = kWorld + 0x200, slot = kWorld + 0x400, res = kWorld + 0x1000, hdr = kWorld + 0x500,
              mesh = kWorld + 0x540;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x4000, rng);
        w32(m, pd + 4, mat);
        w32(m, pd + 12, hdr);
        w32(m, pd + 44, mesh);
        w32(m, pd + 48, slot);
        w32(m, slot, res);
        w32(m, pd + 52, rng() & ~0xCu);  // no re-instance (the snapshot test drives that path on real meshes)
        w32(m, res + 8, 0x200);  // the size SyncDCache covers
        w32(m, res + 32, kWorld + 0x2000);
        w8(m, mat + 181, static_cast<u8>(pick(rng, {0, 1, 3, 8, 9, 10, 17})));
        w32(m, mat + 8, put_callback(m, rng, false));  // the instance callback
        pair(m, PAIR(fn_PS2AllNodeInstance_0049faa0), Args{pd, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1),
             "PS2AllNodeInstance");
    }
    // sub_4A35C0: object (+32 the slot array), pipeline (+8 flags, +12 name), slot 0..11; strcmp through the RW globals
    // (+344); a missing slot array is created by sub_4F3EC0 through RwMalloc (the non-leaf stand-in returning a buffer)
    const u32 obj = kWorld + 0x100, pipe = kWorld + 0x200, arr = kWorld + 0x300, name = kWorld + 0x400, buf = kWorld + 0x800;
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        w32(m, 0x960158u, 0x524128u);  // strcmp
        w32(m, 0x960178u, kNonLeaf);   // RwMalloc / RwFree
        w32(m, 0x96017Cu, kLeafOne);
        w32(m, gpv(kGpStubResult), chance(rng, 10) ? 0u : buf);
        w32(m, obj + 32, chance(rng, 40) ? 0u : arr);
        w32(m, pipe + 8, rng() & (chance(rng, 50) ? 0xFFFFFFFFu : 0x7FFFFFFFu));
        const char* names[] = {"PS2", "PS3", "", "PS2X"};
        const char* nm = names[chance(rng, 70) ? 0 : 1 + rng() % 3];
        m.put(name, nm);
        w32(m, pipe + 12, name);
        const u32 s = pick(rng, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        pair(m, PAIR(fn_sub_4A35C0_004a35c0), Args{chance(rng, 5) ? 0u : obj, chance(rng, 5) ? 0u : pipe, s, rng64(rng)},
             seed_of(i, 2), "sub_4A35C0");
    }
}

TEST_CASE("game(render_world): the Im3D instance ps2AllIm3DInstance (three streams, strips / lists / fans, clusters)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A2BB0u};
    const u32 pd = kWorld + 0x100, rec = kWorld + 0x200, slot = kWorld + 0x280, res = kWorld + 0x300, hdr = kWorld + 0x600,
              mesh = kWorld + 0x640, verts = kWorld + 0x1000, idx = kWorld + 0x3000, data = kWorld + 0x4000;
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x10000, rng);
        const u32 n = pick(rng, {0, 1, 2, 3, 4, 5, 8, 20, 47, 48, 49, 100});
        w32(m, pd + 8, rec);
        w32(m, pd + 12, hdr);
        w32(m, pd + 44, mesh);
        w32(m, pd + 48, slot);
        w32(m, pd + 52, rng());
        w32(m, slot, res);
        w32(m, hdr, pick(rng, {0, 1, 2, 8, 0x100, 0x101, 0x102, 0x108, rng()}));
        w32(m, mesh, idx);
        for (u32 k = 0; k < 128; ++k) w16(m, idx + 2 * k, static_cast<u16>(rng() % 64));
        w32(m, rec, rng());
        w32(m, rec + 12, verts);
        fill_floats(m, verts, 64 * 9, rng);
        // the resEntry header (+24): +8 data, +24 per-cluster vertex count, +36 count; per stream +144 count / +152
        // offset / +160 stride / +164 back-step (and +192.., +240..)
        const u32 h = res + 24;
        w32(m, res + 36, n);
        w32(m, h + 8, data);
        const u32 per = pick(rng, {3, 4, 6, 12, 24, 48});
        w32(m, h + 24, per);
        for (u32 st = 0; st < 3; ++st) {
            const u32 b = h + 144 + 48 * st;
            w32(m, b, per);
            w32(m, b + 8, rng() % 16);
            w16(m, b + 16, static_cast<u16>(rng() % 32));
            w16(m, b + 20, static_cast<u16>(rng() % 8));
        }
        pair(m, PAIR(fn_ps2AllIm3DInstance_004a2bb0), Args{pd, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1), "ps2AllIm3DInstance");
    }
}

namespace {
// The real atomics of a snapshot: RpAtomic (type 1, render callback AtomicDefaultRenderCallBack at +72) whose geometry
// (+24) has a mesh header (+84: u16 count at +4, first offset +12, 12-byte meshes from +16).
struct RealMesh {
    u32 atomic, geometry, header, mesh, mat_private;
};
bool okp(u32 p) { return p != 0 && p % 4 == 0 && p >= 0x100000u && p < 0x2000000u; }
// A live atomic: its frame (+4) belongs to a hierarchy whose root (+160) is its own root (freed atomics keep stale
// frames).
bool live_atomic(const Machine& m, u32 a) {
    const u32 f = r32(m, a + 4);
    if (!okp(f)) return false;
    const u32 root = r32(m, f + 160);
    return okp(root) && r32(m, root + 160) == root;
}
std::vector<RealMesh> real_meshes(const Machine& m) {
    std::vector<RealMesh> out;
    const u32 modoff = r32(m, gpv(gw::kGpPs2AllModule));
    const u32 def_pipe = r32(m, kRwGlobals + modoff + 68);  // the global default material pipeline
    for (u32 a = 0x100000; a < 0x1F00000; a += 4) {
        if (r32(m, a + 72) != 0x490860u || m.mem.main_ram()[a] != 1) continue;
        const u32 g = r32(m, a + 24);
        if (!okp(g)) continue;
        const u32 hdr = r32(m, g + 84);
        if (!okp(hdr)) continue;
        const u32 n = r16(m, hdr + 4), first = r32(m, hdr + 12);
        for (u32 i = 0; i < n && i < 64; ++i) {
            const u32 mesh = hdr + 16 + first + 12 * i, mat = r32(m, mesh + 8);
            if (!okp(mat)) continue;
            const u32 pipe = r32(m, mat + 8) ? r32(m, mat + 8) : def_pipe;
            if (!okp(pipe) || !okp(r32(m, pipe + 8))) continue;
            const u32 mp = r32(m, r32(m, pipe + 8) + 20);
            if (!okp(mp)) continue;
            const u32 cb = r32(m, mp + 8);
            if (cb != 0x4A0DC0u && cb != 0x46EB10u) continue;
            out.push_back({a, g, hdr, mesh, mp});
        }
    }
    return out;
}
}  // namespace

TEST_CASE("game(render_world): the PS2All instancing on the snapshots' real atomics (PS2AllNodeInstance, ps2AllInstanceSizes, "
          "ps2AllInstanceDmaChain, ps2AllAtomicInstance, the skin instance and weights, ps2AllMatClusterLayout)") {
    int ran = 0;
    for (const char* dir : {"battle_ref_6150", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        INFO(std::string(dir));
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        std::memset(m.at(kStackLo), 0, kDeadStack);  // every run starts from a scrubbed dead stack (run_full)
        std::mt19937 rng{0x4A1430u};
        const std::vector<RealMesh> meshes = real_meshes(m);
        MESSAGE(std::string(dir) << ": " << meshes.size() << " real meshes with a PS2All / skin material pipeline");
        CHECK(!meshes.empty());
        // free RAM of the snapshots (zero): the resEntry (its own slot: the allocator stand-in returns the slot), the
        // PipeData, the stream records of ps2AllInstanceSizes and its outputs
        const u32 res = 0x01B00000u, pd = 0x01B80000u, recs = 0x01B80100u, outs = 0x01B80400u, inst = 0x01B80480u;
        const std::vector<Region> regs = {{res, 0x40000}, {pd, 0x1000}};
        for (std::size_t k = 0; k < meshes.size(); ++k) {
            const RealMesh& r = meshes[k];
            std::memset(m.at(res), 0, 0x40000);
            std::memset(m.at(pd), 0, 0x1000);
            w32(m, res + 8, 0x30000);              // the size SyncDCache covers
            w32(m, r.mat_private + 4, kRetA1);     // the resEntry allocator: returns the slot (in place of sub_4A0CE0)
            w32(m, pd + 4, r.mat_private);
            w32(m, pd + 8, r.atomic);
            w32(m, pd + 12, r.header);
            w32(m, pd + 24, rng());
            w32(m, pd + 44, r.mesh);
            w32(m, pd + 48, res);
            w32(m, pd + 52, 0xC);                   // re-instance
            std::vector<Region> with_mat = regs;
            with_mat.push_back({r.mat_private, 0x300});
            const auto p = pair(m, PAIR(fn_PS2AllNodeInstance_0049faa0), Args{pd, rng64(rng), rng64(rng), rng64(rng)},
                                seed_of(static_cast<int>(k), 1), "PS2AllNodeInstance (real)", {}, with_mat);
            CHECK(gpr_of(p.first, GPR_V0) == 1);
            // the instance callbacks and the instancer directly, on the resEntry just built
            const bool skin = r32(m, r.mat_private + 8) == 0x46EB10u;
            w32(m, inst, r32(m, res + 24 + 48));  // the first stream's address (resEntry +48)
            pair(m, PAIR(fn_ps2AllAtomicInstance_004a1430), Args{pd, inst, rng64(rng), rng64(rng)}, seed_of(static_cast<int>(k), 2),
                 "ps2AllAtomicInstance (real)", {}, regs);
            if (skin)
                pair(m, PAIR(fn_RpPDS_G3d_Skin_PS2AllInstanceCallBack_0046eb10), Args{pd, inst, rng64(rng), rng64(rng)},
                     seed_of(static_cast<int>(k), 3), "skin instance (real)", {}, regs);
            else
                pair(m, PAIR(fn_RpMeshPS2AllInstanceCallBack_004a0dc0), Args{pd, inst, rng64(rng), rng64(rng)},
                     seed_of(static_cast<int>(k), 3), "RpMeshPS2AllInstanceCallBack (real)", {}, regs);
            // the sizes and the DMA chain directly
            Hw hw;
            hw.gpr_in[GPR_T0] = outs + 4;
            hw.gpr_in[GPR_T1] = outs + 8;
            const u32 count = r32(m, r.mesh + 4);
            pair(m, PAIR(fn_ps2AllInstanceSizes_0049d4d0), Args{pd, count, recs, outs}, seed_of(static_cast<int>(k), 4),
                 "ps2AllInstanceSizes (real)", hw, regs);
            pair(m, PAIR(fn_ps2AllInstanceDmaChain_0049dc70), Args{pd, rng64(rng), rng64(rng), rng64(rng)}, seed_of(static_cast<int>(k), 5),
                 "ps2AllInstanceDmaChain (real)", {}, regs);
            pair(m, PAIR(fn_ps2AllMatClusterLayout_0049cc70), Args{r.mat_private, rng64(rng), rng64(rng), rng64(rng)},
                 seed_of(static_cast<int>(k), 6), "ps2AllMatClusterLayout (real)", {}, with_mat);
            // the skin weights of a skinned geometry (skin globals +4: the geometry extension offset)
            const u32 skin_ext = r32(m, r.geometry + r32(m, 0x95DE18u));
            if (skin && okp(skin_ext) && okp(r32(m, skin_ext + 24)))
                pair(m, PAIR(fn_skinInstanceWeights_0046b1b0), Args{r.mesh, skin_ext, res + 0x20000, rng64(rng)},
                     seed_of(static_cast<int>(k), 7), "skinInstanceWeights (real)", {}, regs);
            ++ran;
        }
    }
    MESSAGE("real instancing cases: " << ran);
}

TEST_CASE("game(render_world): bounding spheres, clump render and the geometry lock on the snapshots' real objects") {
    int atoms = 0, clumps = 0;
    for (const char* dir : {"battle_ref_6150", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        INFO(std::string(dir));
        Machine m;
        LOAD_ELF_OR_SKIP(m);
        std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
        std::memset(m.at(kStackLo), 0, kDeadStack);
        std::mt19937 rng{0x4912B0u};
        std::vector<u32> atomics, clumplist;
        for (u32 a = 0x100000; a < 0x1F00000; a += 4) {
            const u8 type = m.mem.main_ram()[a];
            if (type == 1 && r32(m, a + 72) == 0x490860u && live_atomic(m, a) && okp(r32(m, a + 24))) atomics.push_back(a);
            if (type == 2 && okp(r32(m, a + 8))) {  // a clump: its atomic list (+8, link at atomic +64) is circular
                u32 l = r32(m, a + 8);
                int n = 0;
                bool good = true;
                while (l != a + 8 && n < 64) {
                    if (!okp(l) || m.mem.main_ram()[l - 64] != 1 || r32(m, l - 64 + 72) != 0x490860u || !live_atomic(m, l - 64)) {
                        good = false;
                        break;
                    }
                    l = r32(m, l);
                    ++n;
                }
                if (good && n > 0 && n < 64) clumplist.push_back(a);
            }
        }
        MESSAGE(std::string(dir) << ": " << atomics.size() << " atomics, " << clumplist.size() << " clumps");
        const std::vector<Region> wide = {{0x00900000u, 0x00100000u}, {0x00F00000u, 0x00700000u}};
        for (std::size_t k = 0; k < atomics.size(); ++k) {
            const u32 a = atomics[k];
            if (chance(rng, 30)) m.at(a + 3)[0] |= 1;  // the atomic's own dirty bit
            pair(m, PAIR(fn_atomicGetWorldBoundingSphere_004912b0), Args{a, rng64(rng), rng64(rng), rng64(rng)}, seed_of(static_cast<int>(k), 1),
                 "atomicGetWorldBoundingSphere (real)", {}, wide);
            ++atoms;
        }
        for (std::size_t k = 0; k < clumplist.size(); ++k) {
            const u32 c = clumplist[k];
            // the atomics' render callbacks: stand-ins (one may fail: the clump returns 0); render flags as they are
            for (u32 l = r32(m, c + 8); l != c + 8; l = r32(m, l)) w32(m, l - 64 + 72, put_callback(m, rng, true));
            pair(m, PAIR(fn_RpClumpRender_00491630), Args{c, rng64(rng), rng64(rng), rng64(rng)}, seed_of(static_cast<int>(k), 2),
                 "RpClumpRender (real)", {}, wide);
            ++clumps;
        }
        // the geometry lock on real geometries (the polygon lock destroys the mesh header: sub_495C80, recompiled)
        for (std::size_t k = 0; k < atomics.size() && k < 20; ++k) {
            const u32 g = r32(m, atomics[k] + 24);
            pair(m, PAIR(fn_geometryLock_00493370), Args{g, pick(rng, {0, 2, 4, 0x1F00, 0xFFFE}), rng64(rng), rng64(rng)},
                 seed_of(static_cast<int>(k), 3), "geometryLock (real)", {}, wide);
        }
    }
    MESSAGE("real atomics " << atoms << ", clumps " << clumps);
}

TEST_CASE("game(render_world): the world sector instance ps2AllSectorInstance and the cluster layout on synthetic sectors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4A42F0u};
    const u32 pd = kWorld + 0x100, mat = kWorld + 0x200, sector = kWorld + 0x600, hdr = kWorld + 0x700,
              mesh = kWorld + 0x740, world = kWorld + 0x780, idx = kWorld + 0x1000, res = kWorld + 0x2000,
              streams = kWorld + 0x8000;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x20000, rng);
        const u32 n = pick(rng, {0, 1, 2, 3, 5, 8, 23, 24, 25, 60});
        w32(m, kCurWorld, world);
        w32(m, world + 8, rng());
        w32(m, pd + 4, mat);
        w32(m, pd + 8, sector);
        w32(m, pd + 12, hdr);
        w32(m, pd + 44, mesh);
        w32(m, pd + 48, kWorld + 0x1F0);
        w32(m, kWorld + 0x1F0, res);
        w32(m, pd + 52, rng());
        w32(m, hdr, pick(rng, {0, 1, 2, 8, 0x100, 0x101, 0x102, rng()}));
        w32(m, mesh, idx);
        for (u32 k = 0; k < 256; ++k) w16(m, idx + 2 * k, static_cast<u16>(rng() % 64));
        for (u32 k = 0; k < 12; ++k) w32(m, mat + 32 + 8 * k, rng());
        // the sector's streams: +8 positions, +12 normals, +16 / +20 UVs, +48 colours (64 vertices each)
        for (u32 s : {8u, 12u, 16u, 20u, 48u}) w32(m, sector + s, streams + 0x400 * (s / 4));
        fill_floats(m, streams, 0x2000 / 4, rng);
        // the resEntry header (+24): +8 data, +24 per-cluster vertices, +36 count; per stream at +144 + 24 k: count,
        // offset, u16 stride / back-step (as ps2AllIm3DInstance's test)
        const u32 h = res + 24;
        w32(m, res + 36, n);
        w32(m, h + 8, kWorld + 0x10000);
        const u32 per = pick(rng, {3, 4, 6, 12, 24, 48});
        w32(m, h + 24, per);
        for (u32 st = 0; st < 6; ++st) {
            const u32 b = h + 144 + 24 * st;
            w32(m, b, per);
            w32(m, b + 8, rng() % 16);
            w16(m, b + 16, static_cast<u16>(rng() % 16));
            w16(m, b + 20, static_cast<u16>(rng() % 8));
        }
        pair(m, PAIR(fn_ps2AllSectorInstance_004a42f0), Args{pd, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1), "ps2AllSectorInstance");
    }
    // ps2AllAtomicInstance on synthetic atomics: one or two morph targets (the interpolation record's start / end at atomic +80 /
    // +82), every stream (the second target's positions and normals at +396.. / +420..), geometry flags
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x20000, rng);
        const u32 atom = kWorld + 0x800, geom = kWorld + 0x900, targets = kWorld + 0xA00;
        const u32 n = pick(rng, {0, 1, 2, 3, 5, 8, 23, 24, 25, 60});
        w32(m, pd + 4, mat);
        w32(m, pd + 8, atom);
        w32(m, pd + 12, hdr);
        w32(m, pd + 44, mesh);
        w32(m, pd + 48, kWorld + 0x1F0);
        w32(m, kWorld + 0x1F0, res);
        w32(m, pd + 52, rng());
        w32(m, hdr, pick(rng, {0, 1, 2, 8, 0x100, 0x101, 0x102, rng()}));
        w32(m, mesh, idx);
        for (u32 k = 0; k < 256; ++k) w16(m, idx + 2 * k, static_cast<u16>(rng() % 64));
        for (u32 k = 0; k < 12; ++k) w32(m, mat + 32 + 8 * k, rng());
        w32(m, atom + 24, geom);
        const u32 morphs = pick(rng, {1, 1, 2});
        w32(m, geom + 24, morphs);
        w32(m, geom + 8, rng());
        w32(m, geom + 92, targets);
        w16(m, atom + 80, static_cast<u16>(rng() % morphs));
        w16(m, atom + 82, static_cast<u16>(rng() % morphs));
        for (u32 t = 0; t < 2; ++t) {
            w32(m, targets + 28 * t + 20, streams + 0x800 * t);
            w32(m, targets + 28 * t + 24, streams + 0x1000 + 0x400 * t);
        }
        for (u32 s : {48u, 52u, 56u}) w32(m, geom + s, streams + 0x2000 + 0x400 * (s / 4 - 12));
        fill_floats(m, streams, 0x3000 / 4, rng);
        const u32 h = res + 24;
        w32(m, res + 36, n);
        w32(m, h + 8, kWorld + 0x10000);
        const u32 per = pick(rng, {3, 4, 6, 12, 24, 48});
        w32(m, h + 24, per);
        for (u32 st = 0; st < 12; ++st) {
            const u32 b = h + 144 + 24 * st;
            w32(m, b, per);
            w32(m, b + 4, per);
            w32(m, b + 8, rng() % 16);
            w32(m, b + 12, rng() % 16);
            w16(m, b + 16, static_cast<u16>(rng() % 16));
            w16(m, b + 18, static_cast<u16>(rng() % 16));
            w16(m, b + 20, static_cast<u16>(rng() % 8));
        }
        pair(m, PAIR(fn_ps2AllAtomicInstance_004a1430), Args{pd, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 5), "ps2AllAtomicInstance (synthetic)");
        if (morphs == 1) CHECK(r32(m, h + 36) == r16(m, atom + 80));  // documented: the start target in the resEntry
    }
    // ps2AllInstanceSizes / ps2AllInstanceDmaChain on synthetic layouts: every stream type (12 stream flags with bit 0, in or out of the
    // cluster, the UNPACK formats), strips / lists, double buffering, morph targets, a few clusters
    const u32 fmts[] = {0x68000000u, 0x6C000000u, 0x6D000000u, 0x64000000u, 0x65000000u, 0x6E000000u, 0x60000000u, 0x6A000000u};
    for (int i = 0; i < 600; ++i) {
        fill_random(m, kWorld, 0x20000, rng);
        const u32 slot = kWorld + 0x1F0, rese = kWorld + 0x1000, data = kWorld + 0x4000, recs = kWorld + 0x3000,
                  outs = kWorld + 0x3800;
        w32(m, pd + 4, mat);
        w32(m, pd + 12, hdr);
        w32(m, pd + 48, slot);
        w32(m, slot, rese);
        w32(m, pd + 36, chance(rng, 20) ? 1u : 0u);
        w32(m, hdr, pick(rng, {0, 1, 2, 8, 0x100, 0x101}));
        for (u32 k = 0; k < 12; ++k) {
            const u32 f = fmts[rng() % 8] | (chance(rng, 85) ? 1u : 0u) | (chance(rng, 60) ? 0x2000u : 0u) | (rng() & 0x4010u);
            w32(m, mat + 32 + 8 * k, f);
            w32(m, mat + 36 + 8 * k, 1 + rng() % 16);
        }
        w8(m, mat + 180, static_cast<u8>(chance(rng, 30) ? 1 : 0));
        w8(m, mat + 181, static_cast<u8>(rng() % 12));
        w8(m, mat + 182, static_cast<u8>(rng() % 12));
        w8(m, mat + 185, static_cast<u8>(rng() % 3));
        w8(m, mat + 497, static_cast<u8>(rng() % 3));
        for (u32 rec : {184u, 496u}) {
            w8(m, mat + rec, static_cast<u8>(pick(rng, {1, 2, 3, 4})));
            w8(m, mat + rec + 1, static_cast<u8>(rng() % 3));
            w32(m, mat + rec + 8, 6 + rng() % 40);
            w32(m, mat + rec + 12, 1 + rng() % 4);
            w32(m, mat + rec + 16, 6 + rng() % 40);
            w32(m, mat + rec + 20, 1 + rng() % 4);
        }
        Hw hw;
        hw.gpr_in[GPR_T0] = outs + 4;
        hw.gpr_in[GPR_T1] = outs + 8;
        pair(m, PAIR(fn_ps2AllInstanceSizes_0049d4d0), Args{pd, rng() % 200, recs, outs}, seed_of(i, 3), "ps2AllInstanceSizes", hw);
        // the resEntry for ps2AllInstanceDmaChain: +32 the data, +52 clusters, +36 vertices, +56 clusters per block; the header (+24):
        // +24 per-cluster vertices, +8 data, +28 clusters, per stream +152 / +156 offsets and +166 the unpack address
        const u32 clusters = 1 + rng() % 5, per = 3 + rng() % 30;
        w32(m, rese + 32, data);
        w32(m, rese + 52, clusters);
        w32(m, rese + 36, per * clusters - rng() % 3);
        w32(m, rese + 56, 1 + rng() % 3);
        w32(m, rese + 24 + 24, per);
        w32(m, rese + 24 + 8, data + 0x4000);
        w32(m, rese + 24 + 28, clusters);
        for (u32 k = 0; k < 12; ++k) {
            w32(m, rese + 24 + 152 + 24 * k, rng() % 64);
            w32(m, rese + 24 + 156 + 24 * k, rng() % 64);
        }
        pair(m, PAIR(fn_ps2AllInstanceDmaChain_0049dc70), Args{pd, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 4), "ps2AllInstanceDmaChain");
    }
    // ps2AllMatClusterLayout on random pipeline records (the flags, the stream flags, the VU1 buffer sizes)
    for (int i = 0; i < 400; ++i) {
        fill_random(m, kWorld, 0x1000, rng);
        w32(m, mat + 176, pick(rng, {0, 1, 4, 8, 0xC, 0x10, rng()}));
        for (u32 k = 0; k < 10; ++k) w32(m, mat + 32 + 8 * k, rng() & (chance(rng, 50) ? 0xFFFFFFFFu : 0xFFFFDFFFu));
        w8(m, mat + 182, static_cast<u8>(rng() % 11));
        w8(m, mat + 181, static_cast<u8>(rng() % 11));
        for (u32 rec : {184u, 496u}) w32(m, mat + rec + 4, 64 + rng() % 1000);
        pair(m, PAIR(fn_ps2AllMatClusterLayout_0049cc70), Args{mat, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 2), "ps2AllMatClusterLayout");
    }
}

TEST_CASE("game(render_world): RpWorldRender and WorldSectorRender (visible sectors, their atomics, the frame stamp)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x499320u};
    const u32 world = kWorld + 0x100, list = kWorld + 0x200;
    int rendered = 0;
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x10000, rng);
        put_camera(m, rng);
        w32(m, kCurWorld, world);
        w32(m, world + 104, put_callback(m, rng, true));  // the world's sector render callback
        // the engine's point-transform table (RW globals + gp-17376, +8: sub_4E3EC0, as the snapshots hold it)
        w32(m, gpv(-17376), 0x134);
        w32(m, kRwGlobals + 0x134 + 8, 0x4E3EC0u);
        // the camera's visible sector list (camera + gp-17544: {+0 array, +8 count})
        const u32 off = 4u * (rng() % 16);
        w32(m, gpv(-17544), off);
        const u32 nsec = rng() % 4;
        w32(m, kCamera + off, list);
        w32(m, kCamera + off + 8, nsec);
        w16(m, kFrameStamp, static_cast<u16>(rng() % 4));
        for (u32 s = 0; s < nsec; ++s) {
            const u32 sector = kWorld + 0x1000 + 0x800 * s;
            w32(m, list + 4 * s, sector);
            // the atomics tied to the sector (+56: {next, prev, atomic})
            std::vector<u32> ties;
            const u32 na = rng() % 4;
            for (u32 k = 0; k < na; ++k) {
                const u32 tie = sector + 0x100 + 0x10 * k, atom = sector + 0x200 + 0x100 * k, frame = kWorld + 0x8000 + 0x100 * (4 * s + k);
                w32(m, tie + 8, atom);
                ties.push_back(tie);
                w8(m, atom + 2, static_cast<u8>(chance(rng, 80) ? (rng() | 4u) : (rng() & ~4u)));
                w8(m, atom + 3, static_cast<u8>(rng() & 1u));
                w16(m, atom + 96, static_cast<u16>(rng() % 4));
                w32(m, atom + 76, rng() & ~2u);
                put_frame(m, frame, rng);
                w32(m, atom + 4, frame);
                fill_floats(m, atom + 28, 4, rng);
                w32(m, atom + 72, put_callback(m, rng, false));
            }
            link_list(m, sector + 56, ties);
        }
        if (i % 2 == 0) {
            pair(m, PAIR(fn_RpWorldRender_0049a250), Args{world, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 1), "RpWorldRender");
        } else if (nsec > 0) {
            pair(m, PAIR(fn_WorldSectorRender_00499320), Args{r32(m, list), rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 2),
                 "WorldSectorRender");
            ++rendered;
        }
    }
    CHECK(rendered > 50);
}

TEST_CASE("game(render_world): the geometry unlock / mesh-build helpers, the light callback and the Im3D render test") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x499140u};
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x2000, rng);
        const u32 geom = kWorld + 0x100;
        // sub_499140: the build callback at 0x77DDA0 (data 0x77DDA4) when $a1 bit 0; sub_495C20 frees through the RW
        // globals (RwFree +380, the free-list free +396: stand-ins)
        w32(m, 0x77DDA0u, put_callback(m, rng, true));
        w32(m, 0x77DDA4u, rng());
        w32(m, 0x96017Cu, kLeafOne);
        w32(m, 0x96018Cu, kLeafOne);
        w32(m, geom + 4, chance(rng, 30) ? 0u : kWorld + 0x400);
        w32(m, geom + 8, chance(rng, 50) ? 0u : kWorld + 0x500);
        pair(m, PAIR(fn_sub_499140_00499140), Args{chance(rng, 5) ? 0u : geom, rng() | 1u, rng64(rng), rng64(rng)}, seed_of(i, 1),
             "sub_499140", {}, {{0x0077DD00u, 0x100}});
        // sub_498E30: the tail call into the mesh build (outside the emitted set: a stop with its arguments)
        pair(m, PAIR(fn_sub_498E30_00498e30), Args{geom, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 2), "sub_498E30");
        // meshHeaderForAllMeshes: the meshes after a header (count u16 +4, first offset +12), the callback until 0
        const u32 hdr = kWorld + 0x800;
        w16(m, hdr + 4, static_cast<u16>(pick(rng, {0, 1, 2, 5, 9})));
        w32(m, hdr + 12, 4u * (rng() % 8));
        pair(m, PAIR(fn_meshHeaderForAllMeshes_00495f10), Args{hdr, put_callback(m, rng, true), rng(), rng64(rng)}, seed_of(i, 3),
             "meshHeaderForAllMeshes");
        // ps2AllSectorLightCB: a world-flagged light into the light block (sub_49FF10 with scale 1.0)
        const u32 light = kWorld + 0x1000, block = kWorld + 0x1800;
        w8(m, light + 1, static_cast<u8>(pick(rng, {1, 2, 0x80, 0x81, 0x82})));
        w8(m, light + 2, static_cast<u8>(rng()));
        fill_floats(m, light + 20, 8, rng);
        put_frame(m, light + 0x80, rng);
        w32(m, light + 4, light + 0x80);
        w32(m, gpv(-17516), block + 16 * (rng() % 4));
        w32(m, gpv(-17520), pick(rng, {0, 1, 4, 123, 124}));
        pair(m, PAIR(fn_ps2AllSectorLightCB_004a3f20), Args{light, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 4), "ps2AllSectorLightCB");
        // sub_49C7A0: (_, record ref): the record's vertex count (u16 +0), +4 -> +24, render state 1 unless +12 bit 0
        const u32 rec = kWorld + 0x1C00, ref = kWorld + 0x1C80;
        w32(m, ref, rec);
        w16(m, rec, static_cast<u16>(pick(rng, {0, 1, 7, 0x8000})));
        w32(m, 0x960090u, put_callback(m, rng, false));
        pair(m, PAIR(fn_sub_49C7A0_0049c7a0), Args{rng(), ref, rng64(rng), rng64(rng)}, seed_of(i, 5), "sub_49C7A0");
    }
}

TEST_CASE("game(render_world): pair count") {
    MESSAGE("render_world pairs: " << g_pairs << " (" << g_stops << " ended at a stop)");
    for (const auto& [k, n] : g_stop_kinds) MESSAGE("  stop " << k << " x" << n);
}

#else

TEST_CASE("game(render_world): replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game was configured without P3FES_RT_EXEC_ELF; nothing to compare");
}

#endif
