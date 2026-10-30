// Phase 5 pair tests for the fx_epl slice (game/src/fx/fx_epl.cpp): the EPL effect-object API -- the four object
// kinds of the function rows at 0x69C368 and the effect-node wrappers (fx_epl.h). Each hand-written function and the
// recompiled body it replaces run on identical guest machines built from random structures (objects, models with a
// frame list, effect nodes with child lists, particle systems with their records, atomics / geometries / materials,
// textures), with the callbacks the bodies reach through tables (the particle-system kind row 0 of 0x69C510, the
// node kind row 0 of 0x69BE20, the RW render-state slot 0x960090) aimed at callbacks of the emitted set: a leaf
// (`li v0, 1`) and a non-leaf that spills $ra below the $sp it receives.
//
// Compared per pair: EVERY general register in 128 bits, HI/LO, SA, all FPU registers, ACC, FCR31 and the whole VU0
// state at the return (or at the missing-function stop), the whole register file (GPRs, HI/LO, SA, FPRs, FCR31) and
// the cycle count at EVERY check point, the bus access log, the scratchpad, the WHOLE 32 MiB of RAM (through a
// PairRange: the stack window live and dead included -- the hand versions write the original's spills), the virtual
// cycles, the check-point and syscall counts and the stop address. FPRs, ACC, HI/LO and VU0 start random, so a
// register the original leaves alone must stay alone.
//
// Callees the slice leaves recompiled and the tests do not emit (the model create / destroy / animation, the node
// create / draw / destroy trees, the RW stream / clump calls, the particle drawing sub_34EAE0, the debug gizmos) end a
// run at a missing-function stop: both bodies must reach it in the same state. Real data: the effect nodes of the
// battle_ref_6150 / b_5800 / dorm_replay_4900 snapshots (skipped when absent). Host-side checks restate documented
// behaviour (fx_epl.h).
#include "pair_harness.h"
#include "write_tracker.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/game/fx_epl.h"

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
P3FES_DECL_PAIR(fn_sub_34C250_0034c250)
P3FES_DECL_PAIR(fn_sub_34C320_0034c320)
P3FES_DECL_PAIR(fn_sub_34C350_0034c350)
P3FES_DECL_PAIR(fn_sub_34C390_0034c390)
P3FES_DECL_PAIR(fn_sub_34C5A0_0034c5a0)
P3FES_DECL_PAIR(fn_sub_34C5D0_0034c5d0)
P3FES_DECL_PAIR(fn_sub_34C630_0034c630)
P3FES_DECL_PAIR(fn_sub_34C640_0034c640)
P3FES_DECL_PAIR(fn_sub_34C650_0034c650)
P3FES_DECL_PAIR(fn_sub_34C660_0034c660)
P3FES_DECL_PAIR(fn_sub_34C940_0034c940)
P3FES_DECL_PAIR(fn_sub_34CB60_0034cb60)
P3FES_DECL_PAIR(fn_sub_34CC00_0034cc00)
P3FES_DECL_PAIR(fn_sub_34CF30_0034cf30)
P3FES_DECL_PAIR(fn_sub_34D050_0034d050)
P3FES_DECL_PAIR(fn_sub_34D090_0034d090)
P3FES_DECL_PAIR(fn_sub_34D0A0_0034d0a0)
P3FES_DECL_PAIR(fn_sub_34D0B0_0034d0b0)
P3FES_DECL_PAIR(fn_sub_34D0C0_0034d0c0)
P3FES_DECL_PAIR(fn_sub_34D0D0_0034d0d0)
P3FES_DECL_PAIR(fn_sub_34D130_0034d130)
P3FES_DECL_PAIR(fn_sub_34D150_0034d150)
P3FES_DECL_PAIR(fn_sub_34D3A0_0034d3a0)
P3FES_DECL_PAIR(fn_sub_34D810_0034d810)
P3FES_DECL_PAIR(fn_sub_34D990_0034d990)
P3FES_DECL_PAIR(fn_sub_34DB00_0034db00)
P3FES_DECL_PAIR(fn_sub_34DB30_0034db30)
P3FES_DECL_PAIR(fn_sub_34E390_0034e390)
P3FES_DECL_PAIR(fn_sub_34E3D0_0034e3d0)
P3FES_DECL_PAIR(fn_sub_34E420_0034e420)
P3FES_DECL_PAIR(fn_sub_34E450_0034e450)
P3FES_DECL_PAIR(fn_sub_34E480_0034e480)
P3FES_DECL_PAIR(fn_sub_34E490_0034e490)
P3FES_DECL_PAIR(fn_sub_34E7C0_0034e7c0)
P3FES_DECL_PAIR(fn_sub_34E800_0034e800)
P3FES_DECL_PAIR(fn_sub_34E910_0034e910)
P3FES_DECL_PAIR(fn_sub_34E940_0034e940)
P3FES_DECL_PAIR(fn_sub_34F6B0_0034f6b0)
P3FES_DECL_PAIR(fn_sub_34F910_0034f910)
P3FES_DECL_PAIR(fn_sub_34FB40_0034fb40)
P3FES_DECL_PAIR(fn_sub_34FB70_0034fb70)
P3FES_DECL_PAIR(fn_sub_34FBA0_0034fba0)
P3FES_DECL_PAIR(fn_sub_34FBE0_0034fbe0)
P3FES_DECL_PAIR(fn_sub_34FC30_0034fc30)
P3FES_DECL_PAIR(fn_sub_34FC60_0034fc60)
P3FES_DECL_PAIR(fn_sub_34FC90_0034fc90)
P3FES_DECL_PAIR(fn_sub_34FCA0_0034fca0)
P3FES_DECL_PAIR(fn_sub_34FCD0_0034fcd0)
P3FES_DECL_PAIR(fn_sub_34FCF0_0034fcf0)
P3FES_DECL_PAIR(fn_sub_34FD10_0034fd10)
P3FES_DECL_PAIR(fn_sub_34FD30_0034fd30)
P3FES_DECL_PAIR(fn_sub_34FD50_0034fd50)
P3FES_DECL_PAIR(fn_sub_34FD70_0034fd70)
P3FES_DECL_PAIR(fn_sub_34FDB0_0034fdb0)
P3FES_DECL_PAIR(fn_sub_34FDF0_0034fdf0)
P3FES_DECL_PAIR(fn_sub_34FE30_0034fe30)
P3FES_DECL_PAIR(fn_sub_34FE80_0034fe80)
P3FES_DECL_PAIR(fn_sub_34FF70_0034ff70)
P3FES_DECL_PAIR(fn_sub_34FF90_0034ff90)
P3FES_DECL_PAIR(fn_sub_34FFC0_0034ffc0)
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
constexpr u32 kWorldLen = 0x10000u;
constexpr u32 kObj = kWorld + 0x100;       // the EPL object (a0)
constexpr u32 kObj2 = kWorld + 0x400;      // a second object (copy sources)
constexpr u32 kModel = kWorld + 0x1000;    // a character model (0x400 bytes)
constexpr u32 kModel2 = kWorld + 0x1800;
constexpr u32 kNodePtrs = kWorld + 0x2000; // kind 2's node pointer array
constexpr u32 kNodes = kWorld + 0x2100;    // effect nodes, 0xC0 bytes each
constexpr u32 kDescs = kWorld + 0x3000;    // node descriptors (44 bytes, kind at +4, data at +8)
// (node children live 4 KiB above their parent's slot: kWorld + 0x3100 .. 0x3900)
constexpr u32 kSystem = kWorld + 0x8800;   // a particle system (+0 kind, +8 count, +12 flags, +16 age, +24 records, +32 xform)
constexpr u32 kSysXform = kWorld + 0x8880; // its position (+0) and rotation (+16); +84 the layer (as the owner record)
constexpr u32 kSysRecs = kWorld + 0x9000;  // 32-byte system records
constexpr u32 kObjRecs = kWorld + 0xA000;  // 24 / 28-byte object records
constexpr u32 kFrameList = kWorld + 0xB000;  // model +1008: u16 count, +4 entries (80 bytes: matrix, +64 id, +68 key)
constexpr u32 kEntries = kWorld + 0xB100;
constexpr u32 kHier = kWorld + 0xB800;     // model +220: +4 the frame
constexpr u32 kFrame = kWorld + 0xB900;    // an RwFrame (+80 LTM, +160 root)
constexpr u32 kRoot = kWorld + 0xBA00;     // its root (+3 flags: bit 0 clear = synced)
constexpr u32 kVec = kWorld + 0xC000;      // vector / matrix arguments
constexpr u32 kAtomic = kWorld + 0xC400;   // an atomic (+24 geometry)
constexpr u32 kGeometry = kWorld + 0xC500; // +8 flags, +32 material pointers, +36 count
constexpr u32 kMatPtrs = kWorld + 0xC600;
constexpr u32 kMaterials = kWorld + 0xC700;
constexpr u32 kTexture = kWorld + 0xCC00;  // an RwTexture (+84 reference count)
constexpr u32 kRasterSlot = kWorld + 0xCD00;
constexpr u32 kRaster = kWorld + 0xCE00;
constexpr u32 kFrameKeyOff = 0x40;         // gp[-17856]: the offset sub_466720 reads a frame's key at
constexpr u32 kPsysTable = 0x0069C510u;    // particle-system kind rows (16 bytes: +0 step, +4 scale)
constexpr u32 kNodeTable = 0x0069BE20u;    // effect-node kind rows (52 bytes; +28 .. +48 the setters)
constexpr u32 kRenderStateSet = 0x00960090u;
constexpr u32 kSlot21 = 0x00957A74u;       // sub_3210A0(21): the manager's resource slot 21
constexpr u32 kLayerSel = gpv(-25288);     // the selected draw layer (u16)

// Callbacks of the emitted set (tests/game/CMakeLists.txt lists them).
constexpr u32 kOne = 0x469A90u;      // `jr ra; li v0, 1`
constexpr u32 kNonLeaf = 0x1F1C50u;  // spills $ra below its $sp, returns the word at gp-18968

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
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
u64 rng64(std::mt19937& rng) {
    const u64 hi = rng();
    return (hi << 32) | rng();
}
u32 rand_float(std::mt19937& rng) {
    switch (rng() % 12) {
    case 0: return 0;
    case 1: return 0x80000000u;
    case 2: return rng();
    case 3: return rng() & 0x807FFFFFu;
    default: return std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 4001) - 2000) / 97.0f);
    }
}
u32 fbits(float f) { return std::bit_cast<u32>(f); }
void fill_floats(Machine& m, u32 va, u32 count, std::mt19937& rng) {
    for (u32 i = 0; i < count; ++i) w32(m, va + 4 * i, rand_float(rng));
}
u32 seed_of(int i, u32 salt) { return 0x9E3779B9u * static_cast<u32>(i + 1) ^ salt; }
// A small int: mostly 0..range-1, sometimes an edge (negative, large).
u32 small(std::mt19937& rng, u32 range) {
    if (chance(rng, 6)) return pick(rng, {0xFFFFFFFFu, 0x80000000u, 0x7FFFFFFFu, 0x10000u});
    return rng() % range;
}
// The world: floats, small ints and pointers into it (structures the code follows blindly stay inside).
void soup(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i < kWorldLen / 4; ++i) {
        const u32 k = rng() % 10;
        const u32 v = k < 3 ? kWorld + (rng() % (kWorldLen / 16)) * 16 : k < 7 ? rand_float(rng) : k < 9 ? rng() % 16 : rng();
        w32(m, kWorld + 4 * i, v);
    }
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
};

std::vector<u32> vu0_words(const VU0State& v) {
    std::vector<u32> out;
    for (const auto& r : v.vf) out.insert(out.end(), std::begin(r), std::end(r));
    for (u16 x : v.vi) out.push_back(x);
    out.insert(out.end(), std::begin(v.acc), std::end(v.acc));
    for (u32 x : {v.q, v.p, v.i, v.r, v.status, v.mac, v.clip, v.tpc, v.cmsar0}) out.push_back(x);
    return out;
}

Snap snap_of(const EEContext& ctx) {
    Snap s;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = ctx.gpr[r];
    s.hi = ctx.hi;
    s.lo = ctx.lo;
    s.sa = ctx.sa;
    std::copy(std::begin(ctx.fpr), std::end(ctx.fpr), s.fpr.begin());
    s.acc = ctx.acc;
    s.fcr31 = ctx.fcr31;
    s.vu0 = vu0_words(ctx.vu0);
    s.cycles = ctx.cycles;
    return s;
}

// The first difference of two snapshots ("" when equal).
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "gpr " + std::to_string(r) + " hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa) return "sa";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + " hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.acc != b.acc) return "acc";
    if (a.fcr31 != b.fcr31) return "fcr31";
    if (a.vu0 != b.vu0) {
        std::size_t i = 0;
        while (i < a.vu0.size() && a.vu0[i] == b.vu0[i]) ++i;
        return "vu0 word " + std::to_string(i);
    }
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

class EplHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    int syscalls = 0;
    int traps = 0;
    std::vector<Snap> snaps;
    std::size_t checks = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap at_stop;

    // A random world can loop (a node list that leads back to itself); with every check point recorded, one such run
    // once grew to 23 GB and the test died of bad_alloc under the gate's parallel load. Record the first kMaxSnaps
    // check points, count the rest, and stop both runs at the same check point once the budget is spent.
    static constexpr std::size_t kMaxSnaps = 20000;
    static constexpr std::size_t kMaxChecks = 2000000;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        if (snaps.size() < kMaxSnaps) snaps.push_back(snap_of(ctx));
        if (++checks > kMaxChecks) fatal(ctx, 0xB0D6E7u, "check-point budget");
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stopped = true;
        stop_pc = pc;
        at_stop = snap_of(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
};

struct Run {
    bool stopped = false;
    u32 stop_pc = 0;
    int syscalls = 0, traps = 0;
    std::size_t checks = 0;
    std::vector<Snap> snaps;
    Snap end;
    std::vector<ScriptedBus::Access> bus;
    std::vector<u8> spr;
};

// Extra register inputs set after the randomised context ($f12.. for the float arguments, $vf10 for sub_34D3A0).
struct In {
    std::vector<std::pair<unsigned, u32>> fpr;
    bool vf10 = false;
    std::array<u32, 4> vf10_value{};
};

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const In& in) {
    EplHooks hooks;
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
    m.ctx.vu0.q = rand_float(rng);
    for (const auto& [f, v] : in.fpr) m.ctx.fpr[f] = v;
    if (in.vf10)
        for (unsigned k = 0; k < 4; ++k) m.ctx.vu0.vf[10][k] = in.vf10_value[k];
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    Run r;
    r.stopped = hooks.stopped;
    r.stop_pc = hooks.stop_pc;
    r.syscalls = hooks.syscalls;
    r.traps = hooks.traps;
    r.checks = hooks.checks;
    r.snaps = std::move(hooks.snaps);
    r.end = hooks.stopped ? hooks.at_stop : snap_of(m.ctx);
    r.bus = std::move(hooks.bus_.log);
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    int complete = 0;
    std::map<u32, int> stop_at;  // missing function -> count
};
std::map<std::string, Stats> g_stats;
int g_pairs = 0;

// Both bodies from the same machine (the whole RAM through a PairRange, the scratchpad restored in between); requires
// identical results everywhere. After the pair the recompiled run's output is in place. Returns the recompiled run.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const In& in = {}) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    const std::string label = std::string(what) + " seed " + std::to_string(seed) + " a0=" + hex64(args[0]) + " a1=" + hex64(args[1]);
    INFO(label);
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    Run h = run_one(m, hand, args, seed, in);
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    Run r = run_one(m, recomp, args, seed, in);
    ++g_pairs;
    Stats& st = g_stats[what];
    ++st.pairs;
    (r.stopped ? st.stops : st.complete) += 1;
    if (r.stopped) ++st.stop_at[r.stop_pc];
    REQUIRE(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.traps == r.traps);
    CHECK(h.checks == r.checks);
    CHECK(h.snaps.size() == r.snaps.size());
    for (std::size_t i = 0; i < std::min(h.snaps.size(), r.snaps.size()); ++i) {
        const std::string d = diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << h.snaps.size() << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = diff(h.end, r.end);
        INFO((r.stopped ? "at the stop " + hex64(r.stop_pc) + ": " : std::string("at the return: ")) << d);
        CHECK(d.empty());
    }
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto& a = h.bus[i];
        const auto& b = r.bus[i];
        if (a.write != b.write || a.bits != b.bits || a.pa != b.pa || a.lo != b.lo || a.hi != b.hi) {
            INFO("bus access " << i << ": hand " << hex64(a.pa) << "=" << hex64(a.lo) << " recomp " << hex64(b.pa) << "=" << hex64(b.lo));
            CHECK(false);
            break;
        }
    }
    {
        const std::size_t f = first_difference(h.spr.data(), r.spr.data(), h.spr.size());
        INFO("first differing scratchpad byte " << hex64(f));
        CHECK(f == h.spr.size());
    }
    {
        const std::size_t f = ram.first_difference();
        INFO("RAM: first differing byte at " << hex64(f) << " (hand left " << hex64(ram.first_body_byte(f < ram.size() ? f : 0)) << ")");
        CHECK(f == ram.size());
    }
    return r;
}

// Every pair of a test counts; a test reports its numbers (pairs, how many ended at a stop).
struct Counter {
    const char* what;
    int start = g_pairs;
    explicit Counter(const char* w) : what(w) {}
    ~Counter() { MESSAGE(std::string(what) << ": " << (g_pairs - start) << " pairs"); }
};
void report(std::initializer_list<const char*> names) {
    for (const char* n : names) {
        const Stats& s = g_stats[n];
        std::string where;
        for (const auto& [pc, k] : s.stop_at) where += " " + hex64(pc) + " x" + std::to_string(k);
        MESSAGE(std::string(n) << ": " << s.pairs << " pairs, " << s.complete << " to the return, " << s.stops
                               << " at a missing-function stop" << where);
    }
}

// --- the world builders --------------------------------------------------------------------------------------
// The table rows the bodies dispatch through, aimed at emitted callbacks (once per test case; the same for both runs).
void patch_tables(Machine& m, std::mt19937& rng) {
    w32(m, kPsysTable + 0, pick(rng, {kNonLeaf, kOne}));  // step
    w32(m, kPsysTable + 4, pick(rng, {kOne, kNonLeaf}));  // scale
    for (u32 off = 28; off <= 48; off += 4) w32(m, kNodeTable + off, pick(rng, {kOne, kNonLeaf, 0u}));
    w32(m, kRenderStateSet, pick(rng, {kNonLeaf, kOne}));
    w32(m, gpv(-17856), kFrameKeyOff);
}

// A model at `model` (0x400 bytes of soup): flags +216 (0x1000 mostly clear: the frame update / draw return at
// once), the frame list +1008 (frames `ids` present), the hierarchy +220.
void put_model(Machine& m, u32 model, std::mt19937& rng, const std::vector<u32>& ids) {
    u16 flags = static_cast<u16>(rng());
    if (!chance(rng, 8)) flags &= static_cast<u16>(~0x1000u);
    w16(m, model + 216, flags);
    w32(m, model + 280, chance(rng, 50) ? 0u : rng());
    w32(m, model + 860, chance(rng, 50) ? 0u : rng());
    w32(m, model + 1008, kFrameList);
    w32(m, model + 220, kHier);
    // the frame list: one entry per id, matrices of floats, all sharing the frame key (no hierarchy search)
    w16(m, kFrameList, static_cast<u16>(ids.size()));
    w32(m, kFrameList + 4, kEntries);
    const u32 key = rng();
    for (std::size_t i = 0; i < ids.size(); ++i) {
        const u32 e = kEntries + 80 * static_cast<u32>(i);
        fill_floats(m, e, 16, rng);
        w32(m, e + 64, ids[i]);
        w32(m, e + 68, key);
    }
    w32(m, kHier + 4, kFrame);
    w32(m, kFrame + kFrameKeyOff, key);
    fill_floats(m, kFrame + 80, 16, rng);
    w32(m, kFrame + 160, kRoot);
    w8(m, kRoot + 3, static_cast<u8>(rng() & ~1u));
}

// An effect node at `node` (0xC0 bytes): vectors, floats and flags; a child list of `children` nodes of kind 0 (the
// patched row) or none.
void put_node(Machine& m, u32 node, std::mt19937& rng, unsigned children) {
    fill_floats(m, node, 0xC0 / 4, rng);
    w32(m, node + 104, rng());
    w32(m, node + 132, rng());
    w32(m, node + 140, 0);
    w32(m, node + 144, kDescs);
    w32(m, node + 172, 0);
    u32 prev = 0;
    for (unsigned c = 0; c < children; ++c) {
        const u32 ch = node + 0x1000 + 0xC0 * c;  // children live 4 KiB above their parent's slot
        fill_floats(m, ch, 0xC0 / 4, rng);
        w32(m, ch + 104, rng());
        w32(m, ch + 132, rng());
        w32(m, ch + 140, 0);
        const u32 d = kDescs + 48 * (c + 1);
        w32(m, d, 210);
        w16(m, d + 4, 0);  // kind 0: the patched row
        w32(m, d + 8, kWorld + (rng() % 0x100) * 16);
        w32(m, ch + 144, d);
        w32(m, ch + 172, 0);
        if (prev) w32(m, prev + 172, ch);
        else w32(m, node + 140, ch);
        prev = ch;
    }
}

// A particle system: kind 0 (the patched row), `count` records whose +16 (age) is random in {-2 .. 2}.
void put_system(Machine& m, std::mt19937& rng, u32 count) {
    w16(m, kSystem, 0);
    w32(m, kSystem + 8, count);
    w32(m, kSystem + 12, rng());
    w32(m, kSystem + 16, pick(rng, {0, 1, 2, 7, 0xFFFFFFFFu}));
    w32(m, kSystem + 24, kSysRecs);
    w32(m, kSystem + 32, kSysXform);
    for (u32 i = 0; i < 16; ++i) {
        fill_floats(m, kSysRecs + 32 * i, 4, rng);
        w32(m, kSysRecs + 32 * i + 16, static_cast<u32>(static_cast<s32>(rng() % 5) - 2));
    }
    fill_floats(m, kSysXform, 8, rng);
}

// The object fields every kind reads, over the soup.
void put_object(Machine& m, u32 obj, std::mt19937& rng) {
    fill_floats(m, obj, 0x50, rng);
    w32(m, obj + 140, small(rng, 12));  // kind 1 lifetime
    w32(m, obj + 152, small(rng, 14));  // kind 1 age
    w32(m, obj + 148, kModel);
    w16(m, obj + 84, static_cast<u16>(rng() % 7));
    w8(m, obj + 144, static_cast<u8>(chance(rng, 50) ? 0 : rng()));
}

u32 layer_sel(std::mt19937& rng) { return pick(rng, {0, 1, 2, 3, rng() & 0xFFFFu}); }

}  // namespace

// =========================================================================================================
// Kind 1: the model object
// =========================================================================================================
TEST_CASE("game(fx_epl): kind 1, the model object, equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("kind 1");
    std::mt19937 rng{0x34C250u};
    patch_tables(m, rng);
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_34C250", PAIR(fn_sub_34C250_0034c250)}, {"sub_34C320", PAIR(fn_sub_34C320_0034c320)},
                    {"sub_34C350", PAIR(fn_sub_34C350_0034c350)}, {"sub_34C390", PAIR(fn_sub_34C390_0034c390)},
                    {"sub_34C5A0", PAIR(fn_sub_34C5A0_0034c5a0)}, {"sub_34C5D0", PAIR(fn_sub_34C5D0_0034c5d0)},
                    {"sub_34C630", PAIR(fn_sub_34C630_0034c630)}, {"sub_34C640", PAIR(fn_sub_34C640_0034c640)},
                    {"sub_34C650", PAIR(fn_sub_34C650_0034c650)}, {"sub_34C660", PAIR(fn_sub_34C660_0034c660)}};
    for (const W& wr : ws) {
        for (int i = 0; i < 160; ++i) {
            soup(m, rng);
            put_object(m, kObj, rng);
            put_object(m, kObj2, rng);
            put_model(m, kModel, rng, {0, 1, 2});
            put_model(m, kModel2, rng, {0});
            w32(m, kObj2 + 148, kModel2);
            if (chance(rng, 70)) w32(m, kObj + 148, chance(rng, 50) ? 0u : kModel);
            w16(m, kLayerSel, static_cast<u16>(layer_sel(rng)));
            // a1: the copy source, a value (the colour setter), or a vector (an unmapped pointer would fault in the
            // original: retail never passes one)
            const std::string name = wr.name;
            const u32 a1 = name == "sub_34C250" ? kObj2 : name == "sub_34C650" ? static_cast<u32>(rng()) : kVec;
            fill_floats(m, kVec, 16, rng);
            In in;
            in.fpr.push_back({12, rand_float(rng)});
            pair(m, wr.hand, wr.recomp, Args{sx(kObj), sx(a1), rng64(rng), rng64(rng)}, seed_of(i, 0x3421u), wr.name, in);
        }
    }
    for (const W& wr : ws) report({wr.name});

    // documented: the step advances +36 to 1.0 and the age by one unless a lifetime is set and already exceeded
    for (int i = 0; i < 64; ++i) {
        soup(m, rng);
        const u32 life = static_cast<u32>(i % 8), age = static_cast<u32>(i / 8);
        w32(m, kObj + 140, life);
        w32(m, kObj + 152, age);
        w32(m, kObj + 36, 0);
        pair(m, PAIR(fn_sub_34C350_0034c350), Args{sx(kObj), 0, 0, 0}, seed_of(i, 0x350u), "step rule");
        const bool expired = life < age && life != 0;
        CHECK(r32(m, kObj + 152) == (expired ? age : age + 1));
        CHECK(r32(m, kObj + 36) == (expired ? 0u : fbits(1.0f)));
    }
    // documented: the draw request queues the object at the head of layer +84 of the selected layer set (+156 link)
    for (int i = 0; i < 16; ++i) {
        soup(m, rng);
        const u32 sel = static_cast<u32>(i % 3), layer = static_cast<u32>(i % 5);
        w16(m, kLayerSel, static_cast<u16>(sel));
        w16(m, kObj + 84, static_cast<u16>(layer));
        const u32 head = 0x957320u + 28 * sel + 4 * layer;
        const u32 old = r32(m, head);
        pair(m, PAIR(fn_sub_34C5A0_0034c5a0), Args{sx(kObj), 0, 0, 0}, seed_of(i, 0x5A0u), "queue rule");
        CHECK(r32(m, head) == kObj);
        CHECK(r32(m, kObj + 156) == old);
    }
}

// =========================================================================================================
// Kind 2: the node-carrying model
// =========================================================================================================
TEST_CASE("game(fx_epl): kind 2, the node-carrying model, equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("kind 2");
    std::mt19937 rng{0x34CC00u};
    patch_tables(m, rng);
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_34CC00", PAIR(fn_sub_34CC00_0034cc00)}, {"sub_34CF30", PAIR(fn_sub_34CF30_0034cf30)},
                    {"sub_34D050", PAIR(fn_sub_34D050_0034d050)}, {"sub_34CB60", PAIR(fn_sub_34CB60_0034cb60)},
                    {"sub_34C940", PAIR(fn_sub_34C940_0034c940)}, {"sub_34D090", PAIR(fn_sub_34D090_0034d090)},
                    {"sub_34D0A0", PAIR(fn_sub_34D0A0_0034d0a0)}, {"sub_34D0B0", PAIR(fn_sub_34D0B0_0034d0b0)},
                    {"sub_34D0C0", PAIR(fn_sub_34D0C0_0034d0c0)}};
    for (const W& wr : ws) {
        for (int i = 0; i < 240; ++i) {
            soup(m, rng);
            put_object(m, kObj, rng);
            const u32 frames = small(rng, 6) & 7u;
            w32(m, kObj + 40, frames);
            w32(m, kObj + 44, small(rng, 10));   // age
            w32(m, kObj + 144, small(rng, 10));  // lifetime
            w32(m, kObj + 152, kNodePtrs);
            w32(m, kObj + 156, chance(rng, 70) ? rng() % 3 : 0u);
            w32(m, kObj + 160, kModel);
            for (u32 f = 0; f < 8; ++f) {
                const u32 node = kNodes + 0xC0 * f;
                put_node(m, node, rng, chance(rng, 25) ? 1 + rng() % 2 : 0);
                w32(m, kNodePtrs + 4 * f, node);
            }
            std::vector<u32> ids;
            for (u32 f = 0; f < 8; ++f)
                if (chance(rng, 30)) ids.push_back(f);
            put_model(m, kModel, rng, ids);
            fill_floats(m, kVec, 16, rng);
            In in;
            in.fpr.push_back({12, rand_float(rng)});
            pair(m, wr.hand, wr.recomp, Args{sx(kObj), sx(kVec), rng64(rng), rng64(rng)}, seed_of(i, 0x34CCu), wr.name, in);
        }
    }
    for (const W& wr : ws) report({wr.name});
    // documented: the step grows the age (+44) by one whatever else happens before a stop-free return
    int checked = 0;
    for (int i = 0; i < 120 && checked < 20; ++i) {
        soup(m, rng);
        put_object(m, kObj, rng);
        w32(m, kObj + 44, 5);
        w32(m, kObj + 144, 3);  // expired: nothing but the age step
        w32(m, kObj + 160, kModel);
        const Run r = pair(m, PAIR(fn_sub_34CC00_0034cc00), Args{sx(kObj), 0, 0, 0}, seed_of(i, 0xCC0u), "age rule");
        if (r.stopped) continue;
        CHECK(r32(m, kObj + 44) == 6u);
        ++checked;
    }
    CHECK(checked > 0);
}

// =========================================================================================================
// Kind 3: the clump particle system
// =========================================================================================================
TEST_CASE("game(fx_epl): kind 3, the clump particle system, equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("kind 3");
    std::mt19937 rng{0x34DB30u};
    patch_tables(m, rng);
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_34DB30", PAIR(fn_sub_34DB30_0034db30)}, {"sub_34E3D0", PAIR(fn_sub_34E3D0_0034e3d0)},
                    {"sub_34D150", PAIR(fn_sub_34D150_0034d150)}, {"sub_34E390", PAIR(fn_sub_34E390_0034e390)},
                    {"sub_34DB00", PAIR(fn_sub_34DB00_0034db00)}, {"sub_34E420", PAIR(fn_sub_34E420_0034e420)},
                    {"sub_34E450", PAIR(fn_sub_34E450_0034e450)}, {"sub_34E480", PAIR(fn_sub_34E480_0034e480)},
                    {"sub_34E490", PAIR(fn_sub_34E490_0034e490)}, {"sub_34D810", PAIR(fn_sub_34D810_0034d810)},
                    {"sub_34D990", PAIR(fn_sub_34D990_0034d990)}, {"sub_34D0D0", PAIR(fn_sub_34D0D0_0034d0d0)},
                    {"sub_34D130", PAIR(fn_sub_34D130_0034d130)}};
    for (const W& wr : ws) {
        const std::string name = wr.name;
        for (int i = 0; i < 200; ++i) {
            soup(m, rng);
            put_object(m, kObj, rng);
            put_object(m, kObj2, rng);
            put_system(m, rng, small(rng, 12) & 15u);
            w32(m, kObj + 88, chance(rng, 90) ? kSystem : 0u);
            w32(m, kObj + 92, kObjRecs);
            w16(m, kObj + 12, static_cast<u16>(chance(rng, 80) ? 3 : rng()));
            w16(m, kObj2 + 12, static_cast<u16>(chance(rng, 60) ? 3 : rng()));
            w32(m, kObj + 84, chance(rng, 50) ? 0u : kModel);
            // the emitter parameters of sub_34D150
            w8(m, kObj + 16, static_cast<u8>(chance(rng, 50) ? 0 : rng()));
            if (chance(rng, 15)) {
                w32(m, kObj + 20, 0);
                w32(m, kObj + 24, 0);
                w32(m, kObj + 28, chance(rng, 50) ? 0u : 0x80000000u);
            }
            w32(m, kObj + 52, pick(rng, {0, 1, 2, 2, 3, rng()}));
            fill_floats(m, kObjRecs, 0x100, rng);
            // an owner record for the layer queue: system +32 -> +84 the layer
            w16(m, kSysXform + 84, static_cast<u16>(rng() % 7));
            w16(m, kLayerSel, static_cast<u16>(layer_sel(rng)));
            // atomics: geometry with `n` materials
            const u32 nmat = small(rng, 6) & 7u;
            w32(m, kAtomic + 24, kGeometry);
            w32(m, kGeometry + 32, kMatPtrs);
            w32(m, kGeometry + 36, nmat);
            for (u32 k = 0; k < 8; ++k) w32(m, kMatPtrs + 4 * k, kMaterials + 32 * k);
            fill_floats(m, kVec, 16, rng);
            u64 a0 = sx(kObj), a1 = sx(kVec);
            if (name == "sub_34D150") a1 = sx(kObjRecs + 24 * (rng() % 12));
            if (name == "sub_34D810") a1 = sx(kObj2);
            if (name == "sub_34D0D0" || name == "sub_34D130") a0 = sx(kAtomic);
            In in;
            in.fpr.push_back({12, rand_float(rng)});
            pair(m, wr.hand, wr.recomp, Args{a0, a1, rng64(rng), rng64(rng)}, seed_of(i, 0x34DBu), wr.name, in);
        }
    }
    for (const W& wr : ws) report({wr.name});

    // sub_34D3A0: the colour of a record at a time, $vf10 in and out
    for (int i = 0; i < 1500; ++i) {
        soup(m, rng);
        w32(m, kObj + 56, pick(rng, {0, 1, 5, 6, 7, 12, 30, 60, 61, 0xFFFFFFFAu, rng() % 400}));
        for (u32 k = 0; k < 6; ++k) w32(m, kObj + 60 + 4 * k, rng());
        const u32 rec = kObjRecs + 24 * (rng() % 8);
        w8(m, rec + 20, static_cast<u8>(pick(rng, {0, 1, 2, 3, 4, 5, 0xFF, rng() % 6})));
        In in;
        in.vf10 = true;
        for (u32& x : in.vf10_value) x = rand_float(rng);
        const u32 t = pick(rng, {0, 1, 5, 6, 59, 60, 61, 0xFFFFFFFFu, rng() % 1000, rng()});
        pair(m, PAIR(fn_sub_34D3A0_0034d3a0), Args{sx(kObj), sx(rec), sx(t), rng64(rng)}, seed_of(i, 0x3A0u), "sub_34D3A0", in);
    }
    report({"sub_34D3A0"});

    // documented: the atomic callbacks set every material colour / the modulate flag and return the atomic
    for (int i = 0; i < 16; ++i) {
        soup(m, rng);
        const u32 n = static_cast<u32>(i % 5);
        w32(m, kAtomic + 24, kGeometry);
        w32(m, kGeometry + 32, kMatPtrs);
        w32(m, kGeometry + 36, n);
        for (u32 k = 0; k < 8; ++k) w32(m, kMatPtrs + 4 * k, kMaterials + 32 * k);
        w32(m, kVec, 0x11223344u + static_cast<u32>(i));
        const Run r = pair(m, PAIR(fn_sub_34D0D0_0034d0d0), Args{sx(kAtomic), sx(kVec), 0, 0}, seed_of(i, 0xD0Du), "colour rule");
        CHECK(r.end.gpr[GPR_V0].u64[0] == sx(kAtomic));
        for (u32 k = 0; k < n; ++k) CHECK(r32(m, kMaterials + 32 * k + 4) == 0x11223344u + static_cast<u32>(i));
        const u32 flags = r32(m, kGeometry + 8);
        pair(m, PAIR(fn_sub_34D130_0034d130), Args{sx(kAtomic), 0, 0, 0}, seed_of(i, 0x130u), "modulate rule");
        CHECK(r32(m, kGeometry + 8) == (flags | 0x40u));
    }
    // documented: a zero key length gives $vf10 x (key[phase] lanes x gp[-32232]); with phase 0 and time 0 the
    // result is the same for any positive key length (t = 0, key 0)
    for (int i = 0; i < 8; ++i) {
        soup(m, rng);
        for (u32 k = 0; k < 6; ++k) w32(m, kObj + 60 + 4 * k, rng());
        w8(m, kObjRecs + 20, 0);
        In in;
        in.vf10 = true;
        in.vf10_value = {fbits(1.0f), fbits(2.0f), fbits(0.5f), fbits(1.0f)};
        w32(m, kObj + 56, 0);
        const Run a = pair(m, PAIR(fn_sub_34D3A0_0034d3a0), Args{sx(kObj), sx(kObjRecs), 0, 0}, seed_of(i, 0x1u), "colour key rule", in);
        w32(m, kObj + 56, 6 * static_cast<u32>(i + 1));
        const Run b = pair(m, PAIR(fn_sub_34D3A0_0034d3a0), Args{sx(kObj), sx(kObjRecs), 0, 0}, seed_of(i, 0x1u), "colour key rule", in);
        CHECK(std::vector<u32>(a.end.vu0.begin() + 40, a.end.vu0.begin() + 44) ==
              std::vector<u32>(b.end.vu0.begin() + 40, b.end.vu0.begin() + 44));
    }
}

// =========================================================================================================
// Kind 4: the textured particle system
// =========================================================================================================
TEST_CASE("game(fx_epl): kind 4, the textured particle system, equals its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("kind 4");
    std::mt19937 rng{0x34F6B0u};
    patch_tables(m, rng);
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_34F6B0", PAIR(fn_sub_34F6B0_0034f6b0)}, {"sub_34FBE0", PAIR(fn_sub_34FBE0_0034fbe0)},
                    {"sub_34E940", PAIR(fn_sub_34E940_0034e940)}, {"sub_34F910", PAIR(fn_sub_34F910_0034f910)},
                    {"sub_34FB40", PAIR(fn_sub_34FB40_0034fb40)}, {"sub_34FB70", PAIR(fn_sub_34FB70_0034fb70)},
                    {"sub_34FBA0", PAIR(fn_sub_34FBA0_0034fba0)}, {"sub_34E910", PAIR(fn_sub_34E910_0034e910)},
                    {"sub_34FC30", PAIR(fn_sub_34FC30_0034fc30)}, {"sub_34FC60", PAIR(fn_sub_34FC60_0034fc60)},
                    {"sub_34FC90", PAIR(fn_sub_34FC90_0034fc90)}, {"sub_34FCA0", PAIR(fn_sub_34FCA0_0034fca0)},
                    {"sub_34E800", PAIR(fn_sub_34E800_0034e800)}, {"sub_34E7C0", PAIR(fn_sub_34E7C0_0034e7c0)}};
    for (const W& wr : ws) {
        const std::string name = wr.name;
        for (int i = 0; i < 200; ++i) {
            soup(m, rng);
            put_object(m, kObj, rng);
            put_object(m, kObj2, rng);
            put_system(m, rng, small(rng, 12) & 15u);
            // draws: all particles dead (the loops run to the end) or some alive (a stop in sub_34EAE0)
            if (chance(rng, 60))
                for (u32 k = 0; k < 16; ++k) w32(m, kSysRecs + 32 * k + 16, static_cast<u32>(-1 - static_cast<s32>(rng() % 3)));
            w32(m, kObj + 92, chance(rng, 90) ? kSystem : 0u);
            w32(m, kObj + 100, kObjRecs);
            w32(m, kObj + 96, kTexture);
            w32(m, kObj2 + 96, kTexture);
            w32(m, kTexture + 84, small(rng, 5));
            fill_floats(m, kObjRecs, 0x200, rng);
            w16(m, kSysXform + 84, static_cast<u16>(rng() % 7));
            w16(m, kLayerSel, static_cast<u16>(layer_sel(rng)));
            w32(m, kSlot21, kRasterSlot);
            w32(m, kRasterSlot, kRaster);
            w32(m, kRaster + 12, pick(rng, {64, 128, 256, rng()}));
            w32(m, kRaster + 16, pick(rng, {32, 64, 256, rng()}));
            fill_floats(m, kVec, 16, rng);
            u64 a1 = sx(kVec);
            if (name == "sub_34E940") a1 = sx(kObjRecs + 28 * (rng() % 12));
            if (name == "sub_34F910") a1 = pick(rng, {0, 1, 1, 0x101, rng()});
            if (name == "sub_34E800") a1 = sx(kObj2);
            In in;
            in.fpr.push_back({12, rand_float(rng)});
            pair(m, wr.hand, wr.recomp, Args{sx(kObj), a1, rng64(rng), rng64(rng)}, seed_of(i, 0x34F6u), wr.name, in);
        }
    }
    for (const W& wr : ws) report({wr.name});

    // documented: the copy slot shares the texture and adds one reference
    for (int i = 0; i < 8; ++i) {
        soup(m, rng);
        w32(m, kObj2 + 96, kTexture);
        w32(m, kTexture + 84, static_cast<u32>(i));
        pair(m, PAIR(fn_sub_34E800_0034e800), Args{sx(kObj), sx(kObj2), 0, 0}, seed_of(i, 0x800u), "texture rule");
        CHECK(r32(m, kObj + 96) == kTexture);
        CHECK(r32(m, kTexture + 84) == static_cast<u32>(i + 1));
    }
    // documented: the step scrolls +84 / +88 by +28 / +32 (one add each) when the system has particles
    for (int i = 0; i < 8; ++i) {
        soup(m, rng);
        put_object(m, kObj, rng);
        put_system(m, rng, 1);
        w32(m, kSystem + 16, 5);
        w32(m, kSysRecs + 16, 1);  // alive, not new: no emission
        w32(m, kObj + 92, kSystem);
        w32(m, kObj + 100, kObjRecs);
        w32(m, kObj + 28, fbits(0.25f));
        w32(m, kObj + 84, fbits(1.0f));
        const Run r = pair(m, PAIR(fn_sub_34F6B0_0034f6b0), Args{sx(kObj), 0, 0, 0}, seed_of(i, 0x6B0u), "scroll rule");
        if (!r.stopped) CHECK(r32(m, kObj + 84) == fbits(1.25f));
    }
}

// =========================================================================================================
// [nodes] the effect-node wrappers
// =========================================================================================================
namespace {
struct NodeW {
    const char* name;
    Fn hand, recomp;
};
const NodeW kNodeWrappers[] = {
    {"sub_34FCD0", PAIR(fn_sub_34FCD0_0034fcd0)}, {"sub_34FCF0", PAIR(fn_sub_34FCF0_0034fcf0)},
    {"sub_34FD10", PAIR(fn_sub_34FD10_0034fd10)}, {"sub_34FD30", PAIR(fn_sub_34FD30_0034fd30)},
    {"sub_34FD50", PAIR(fn_sub_34FD50_0034fd50)}, {"sub_34FD70", PAIR(fn_sub_34FD70_0034fd70)},
    {"sub_34FDB0", PAIR(fn_sub_34FDB0_0034fdb0)}, {"sub_34FDF0", PAIR(fn_sub_34FDF0_0034fdf0)},
    {"sub_34FE30", PAIR(fn_sub_34FE30_0034fe30)}, {"sub_34FE80", PAIR(fn_sub_34FE80_0034fe80)},
    {"sub_34FF70", PAIR(fn_sub_34FF70_0034ff70)}, {"sub_34FF90", PAIR(fn_sub_34FF90_0034ff90)},
    {"sub_34FFC0", PAIR(fn_sub_34FFC0_0034ffc0)}};
}  // namespace

TEST_CASE("game(fx_epl): the effect-node wrappers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    Counter cnt("nodes");
    std::mt19937 rng{0x34FD10u};
    patch_tables(m, rng);
    for (const NodeW& wr : kNodeWrappers) {
        for (int i = 0; i < 200; ++i) {
            soup(m, rng);
            put_node(m, kNodes, rng, chance(rng, 40) ? 1 + rng() % 3 : 0);
            fill_floats(m, kVec, 32, rng);
            w32(m, kVec + 64, rng());
            In in;
            for (unsigned f = 12; f <= 14; ++f) in.fpr.push_back({f, rand_float(rng)});
            const u64 a1 = std::string(wr.name) == "sub_34FD70" || std::string(wr.name) == "sub_34FDB0" ? rng() % 8 : sx(kVec);
            pair(m, wr.hand, wr.recomp, Args{sx(kNodes), a1, rng64(rng), rng64(rng)}, seed_of(i, 0x34FDu), wr.name, in);
        }
    }
    for (const NodeW& wr : kNodeWrappers) report({wr.name});
    // documented: the position wrapper passes the vec3 with w = 0 (sub_325C10 stores it at +64)
    for (int i = 0; i < 8; ++i) {
        soup(m, rng);
        put_node(m, kNodes, rng, 0);
        fill_floats(m, kVec, 4, rng);
        pair(m, PAIR(fn_sub_34FDF0_0034fdf0), Args{sx(kNodes), sx(kVec), 0, 0}, seed_of(i, 0xDF0u), "position rule");
        for (u32 k = 0; k < 3; ++k) CHECK(r32(m, kNodes + 64 + 4 * k) == r32(m, kVec + 4 * k));
        CHECK(r32(m, kNodes + 76) == 0u);
    }
    // documented: the colour wrapper stores the word at *a1 in the node (+100)
    for (int i = 0; i < 8; ++i) {
        soup(m, rng);
        put_node(m, kNodes, rng, 0);
        w32(m, kVec, 0xA0B0C0D0u + static_cast<u32>(i));
        pair(m, PAIR(fn_sub_34FF90_0034ff90), Args{sx(kNodes), sx(kVec), 0, 0}, seed_of(i, 0xF90u), "colour word rule");
        CHECK(r32(m, kNodes + 100) == 0xA0B0C0D0u + static_cast<u32>(i));
    }
}

// The effect nodes of real snapshots: the nodes (descriptor word 210 at +144's target) and their roots (a child list
// +140 pointing at one, not a node's own +172 seen through a 32-byte shift), driven through every node wrapper.
TEST_CASE("game(fx_epl): the node wrappers on the effect nodes of the replay snapshots") {
    namespace fs = std::filesystem;
    const fs::path base = fs::path(P3FES_ELF_DEFAULT).parent_path().parent_path() / "_ours";
    const char* names[] = {"battle_ref_6150", "b_5800", "dorm_replay_4900"};
    int ran = 0;
    for (const char* n : names) {
        const fs::path snap = base / n / "eeMemory.bin";
        std::ifstream f(snap, std::ios::binary);
        if (!f) {
            MESSAGE("SKIP: no snapshot " << snap.string());
            continue;
        }
        Machine m;
        f.read(reinterpret_cast<char*>(m.mem.main_ram()), EEMemory::kMainRamSize);
        if (!f) {
            MESSAGE("SKIP: short snapshot " << snap.string());
            continue;
        }
        Counter cnt(n);
        auto ok = [](u32 a) { return a >= 0x100000u && a < 0x2000000u - 0x100u; };
        std::vector<u32> nodes;
        for (u32 p = 0x400000u; p < 0x2000000u - 0x100u; p += 16) {
            const u32 d = r32(m, p + 144);
            if (!ok(d) || (d & 3u) || r32(m, d) != 210 || r16(m, d + 4) >= 64) continue;
            const u32 c = r32(m, p + 140), nx = r32(m, p + 172);
            if ((c && !ok(c)) || (nx && !ok(nx))) continue;
            nodes.push_back(p);
        }
        std::vector<u32> roots;
        for (u32 p = 0x400000u; p < 0x2000000u - 0x100u; p += 16) {
            const u32 c = r32(m, p + 140);
            if (!std::binary_search(nodes.begin(), nodes.end(), c)) continue;
            if (std::binary_search(nodes.begin(), nodes.end(), p - 32)) continue;  // a node's +172 seen at +140
            roots.push_back(p);
        }
        MESSAGE(std::string(n) << ": " << nodes.size() << " effect nodes, " << roots.size() << " roots");
        std::mt19937 rng{0xE91u};
        std::vector<u32> targets = roots;
        for (std::size_t k = 0; k < nodes.size() && k < 24; ++k) targets.push_back(nodes[k]);
        const u32 vec = 0x01FF0000u;  // in the main thread's stack window, far below the tests' $sp (kSp)
        int i = 0;
        for (u32 node : targets) {
            for (const NodeW& wr : kNodeWrappers) {
                const std::string name = wr.name;
                if (name == "sub_34FCD0" || name == "sub_34FCF0" || name == "sub_34FD50") continue;  // allocators
                fill_floats(m, vec, 32, rng);
                In in;
                for (unsigned fr = 12; fr <= 14; ++fr) in.fpr.push_back({fr, rand_float(rng)});
                const u64 a1 = name == "sub_34FD70" || name == "sub_34FDB0" ? rng() % 8 : sx(vec);
                pair(m, wr.hand, wr.recomp, Args{sx(node), a1, 0, 0}, seed_of(i++, 0x5A9u), wr.name, in);
                ++ran;
            }
        }
    }
    MESSAGE("snapshot node pairs: " << ran);
}

#endif  // P3FES_GAME_HAVE_GENERATED
