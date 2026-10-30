// Phase 5 pair tests for the field layer's second pass (game/src/field/field_lo.cpp, slice field_lo): each
// hand-written function and the recompiled body it replaces run on identical guest machines on randomised inputs.
// Compared: pair_harness's Outcome ($v0, the callee-saved registers, the arena, the caller's live stack, the cycles,
// the check-point count), the WHOLE register file at every check point and at the return (GPRs in 128 bits, HI/LO,
// SA, FPRs, ACC, FCR31 and the cycle count: a preemption at a check point saves the whole register file to the guest
// stack, wave 7), the dead stack (the frames and spills of both runs) and the guest ranges these functions write
// (low memory, the gp-relative globals, sField). Randomised FPRs / ACC / FCR31 / HI / LO go in, so a register the hand
// version forgets to write shows. Non-leaf callees run through their generated entry points in both runs; the
// documented rules (field_lo.h, docs/ANALYSIS/26_field.md) are checked on the host, independently of both bodies.
#include "pair_harness.h"

#include "p3fes/game/field_lo.h"

#include <cstring>
#include <functional>
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
P3FES_DECL_PAIR(fn_sub_1AD870_001ad870)
P3FES_DECL_PAIR(fn_sub_1AD890_001ad890)
P3FES_DECL_PAIR(fn_K_FldFrame_CtlGetSphereCollisRadius_001ad8b0)
P3FES_DECL_PAIR(fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0)
P3FES_DECL_PAIR(fn_K_FldFrame_CtlGetXGrid_001ad910)
P3FES_DECL_PAIR(fn_K_FldFrame_CtlGetZGrid_001ad920)
P3FES_DECL_PAIR(fn_sub_1AD930_001ad930)
P3FES_DECL_PAIR(fn_sub_1AE470_001ae470)
P3FES_DECL_PAIR(fn_sub_1A02C0_001a02c0)
P3FES_DECL_PAIR(fn_sub_1A01C0_001a01c0)
P3FES_DECL_PAIR(fn_sub_1A0310_001a0310)
P3FES_DECL_PAIR(fn_sub_1A0410_001a0410)
P3FES_DECL_PAIR(fn_sub_1A0420_001a0420)
P3FES_DECL_PAIR(fn_sub_1A0150_001a0150)
P3FES_DECL_PAIR(fn_sub_1A0040_001a0040)
P3FES_DECL_PAIR(fn_sub_1A0DC0_001a0dc0)
P3FES_DECL_PAIR(fn_sub_19FD40_0019fd40)
P3FES_DECL_PAIR(fn_sub_19FD70_0019fd70)
P3FES_DECL_PAIR(fn_sub_19FDA0_0019fda0)
P3FES_DECL_PAIR(fn_sub_1A09D0_001a09d0)
P3FES_DECL_PAIR(fn_sub_1A0A10_001a0a10)
P3FES_DECL_PAIR(fn_sub_1A0A50_001a0a50)
P3FES_DECL_PAIR(fn_sub_1A48E0_001a48e0)
P3FES_DECL_PAIR(fn_sub_1A48F0_001a48f0)
P3FES_DECL_PAIR(fn_sub_1A4920_001a4920)
P3FES_DECL_PAIR(fn_sub_1A4930_001a4930)
P3FES_DECL_PAIR(fn_sub_1BAB40_001bab40)
P3FES_DECL_PAIR(fn_sub_1BAB50_001bab50)
P3FES_DECL_PAIR(fn_K_FldDungeon_RequestShutdown_001bff00)
P3FES_DECL_PAIR(fn_K_FldDungeon_GetScrMemory_001bffe0)
P3FES_DECL_PAIR(fn_sub_1B0910_001b0910)
P3FES_DECL_PAIR(fn_K_Seq_CheckField_001b78a0)
P3FES_DECL_PAIR(fn_sub_1B79F0_001b79f0)
P3FES_DECL_PAIR(fn_sub_1B7AC0_001b7ac0)
P3FES_DECL_PAIR(fn_sub_1A9180_001a9180)
P3FES_DECL_PAIR(fn_sub_1A9390_001a9390)
P3FES_DECL_PAIR(fn_sub_1A93D0_001a93d0)
P3FES_DECL_PAIR(fn_sub_1BB090_001bb090)
P3FES_DECL_PAIR(fn_sub_1B0220_001b0220)
P3FES_DECL_PAIR(fn_sub_1B0240_001b0240)
P3FES_DECL_PAIR(fn_sub_1B0260_001b0260)
P3FES_DECL_PAIR(fn_sub_1AFF70_001aff70)
P3FES_DECL_PAIR(fn_sub_1B0020_001b0020)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;
using namespace p3fes::game::fldlo;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- guest layout of the tests ---------------------------------------------------------------------------------------
constexpr u32 kField = 0x869F60u;                  // sField
constexpr u32 kSceneSlot = kGp - 22448;            // gp-0x57B0: -> scene record
constexpr u32 kDungeonSlot = kGp - 19080;          // gp-0x4A88
constexpr u32 kCounterSlot = kGp - 19092;          // gp-0x4A94
constexpr u32 kPackSlot = kGp - 19348;             // gp-0x4B94
constexpr u32 kKwlnStarting = kGp - 0x4C8C, kKwlnEnding = kGp - 0x4C80, kKwlnRunning = kGp - 0x4C74;
static_assert(kSceneSlot == 0x7CD540u && kDungeonSlot == 0x7CE268u);

constexpr u32 kTask = kArena + 0x000;   // a kwln task (0x68 bytes): +60 the work
constexpr u32 kTask2 = kArena + 0x080;  // a second task (a collision controller's)
constexpr u32 kWork = kArena + 0x100;   // its work (up to 0x600 bytes: the think queue)
constexpr u32 kWork2 = kArena + 0x700;  // the second work
constexpr u32 kScene = kArena + 0x800;  // the scene record
constexpr u32 kMgr = kArena + 0x880;    // the resource manager: 22 list heads
constexpr u32 kRes0 = kArena + 0x900;   // resources, 0x100 apart (8)
constexpr u32 kVec = kArena + 0x1100;   // a f32[3]
constexpr u32 kBlock = kArena + 0x1200; // a block descriptor (24-byte rows)

// The guest ranges compared after both runs (and restored before the second): low memory (a NULL resource writes
// address 40), the gp-relative globals, sField, the arena, the stack around $sp.
const std::vector<GuestRange> kRanges = {
    {0x0, 0x1000}, {0x7CC000u, 0x4000}, {kField, 0x2000}, {kArena, kArenaSize}, {kSp - kDeadStack, kDeadStack + 0x100}};

void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u32 get32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}

using Prepare = std::function<void(EEContext&)>;

// The whole register file.
struct Regs {
    std::array<u128, 32> gpr;
    u128 hi, lo;
    u32 sa, fcr31, acc;
    std::array<u32, 32> fpr;
};
Regs grab(const EEContext& c) {
    Regs r;
    for (unsigned i = 0; i < 32; ++i) {
        r.gpr[i] = c.gpr[i];
        r.fpr[i] = c.fpr[i];
    }
    r.hi = c.hi;
    r.lo = c.lo;
    r.sa = c.sa;
    r.fcr31 = c.fcr31;
    r.acc = c.acc;
    return r;
}

struct Run {
    Outcome o;
    std::vector<RegSnap> snaps;  // every check point, plus one at the return
    Regs regs;
    std::vector<std::vector<u8>> mem;
};

// One run: a randomised context (GPRs as pair_harness, plus FPRs, ACC, FCR31, HI/LO), `prepare` for the register
// arguments, the function, then a check point of our own so the register file at the return is recorded too.
Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const Prepare& prepare) {
    HwHooks hooks;
    hooks.record_regs = true;
    rt_test::HooksScope scope{&hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng() & 0xBF7FFFFFu;
    m.ctx.acc = rng() & 0xBF7FFFFFu;
    m.ctx.fcr31 = rng() & 0x00800000u;
    m.ctx.hi.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    m.ctx.lo.u64[0] = (static_cast<u64>(rng()) << 32) | rng();
    if (prepare) prepare(m.ctx);
    const u64 c0 = m.ctx.cycles;
    fn(m.ctx);
    Run r;
    r.o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned saved[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) r.o.saved[i] = m.ctx.gpr[saved[i]].u64[0];
    r.o.cycles = m.ctx.cycles - c0;
    r.o.checks = hooks.checks;
    r.o.arena = m.bytes(kArena, kArenaSize);
    r.o.live_stack = m.bytes(kSp, 0x100);
    r.regs = grab(m.ctx);
    rt::check_events(m.ctx);  // the return's register file as a final snapshot
    r.snaps = std::move(hooks.snaps);
    for (const GuestRange& g : kRanges) r.mem.push_back(m.bytes(g.va, g.len));
    return r;
}

bool same(const u128& a, const u128& b) { return a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]; }

// The first difference between two register files, or "" ("" also compares the cycle counts of snapshots).
std::string diff_regs(const std::array<u128, 32>& ga, const std::array<u128, 32>& gb, const u128& ha, const u128& hb,
                      const u128& la, const u128& lb, u32 saa, u32 sab, u32 fa, u32 fb, const std::array<u32, 32>& pa,
                      const std::array<u32, 32>& pb) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same(ga[r], gb[r]))
            return "GPR " + std::to_string(r) + " hand " + hex64(ga[r].u64[1]) + ":" + hex64(ga[r].u64[0]) + " recomp " +
                   hex64(gb[r].u64[1]) + ":" + hex64(gb[r].u64[0]);
    if (!same(ha, hb)) return "HI";
    if (!same(la, lb)) return "LO";
    if (saa != sab) return "SA";
    if (fa != fb) return "FCR31 hand " + hex64(fa) + " recomp " + hex64(fb);
    for (unsigned i = 0; i < 32; ++i)
        if (pa[i] != pb[i]) return "FPR " + std::to_string(i) + " hand " + hex64(pa[i]) + " recomp " + hex64(pb[i]);
    return "";
}

int g_pairs = 0;

// The pair: snapshot the ranges, run the hand version, restore, run the recompiled body, compare everything. The
// recompiled run's output stays in place.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const std::string& what, const Prepare& prepare = {}) {
    std::vector<std::vector<u8>> before;
    for (const GuestRange& g : kRanges) before.push_back(m.bytes(g.va, g.len));
    const Run h = run_one(m, hand, args, seed, prepare);
    for (std::size_t i = 0; i < kRanges.size(); ++i) std::memcpy(m.at(kRanges[i].va), before[i].data(), kRanges[i].len);
    Run r = run_one(m, recomp, args, seed, prepare);
    ++g_pairs;
    INFO(what);
    expect_same(h.o, r.o, what.c_str());
    CHECK(h.snaps.size() == r.snaps.size());
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const RegSnap& a = h.snaps[i];
        const RegSnap& b = r.snaps[i];
        std::string d = diff_regs(a.gpr, b.gpr, a.hi, b.hi, a.lo, b.lo, a.sa, b.sa, a.fcr31, b.fcr31, a.fpr, b.fpr);
        if (d.empty() && a.cycles != b.cycles) d = "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    const std::string d = diff_regs(h.regs.gpr, r.regs.gpr, h.regs.hi, r.regs.hi, h.regs.lo, r.regs.lo, h.regs.sa, r.regs.sa,
                                    h.regs.fcr31, r.regs.fcr31, h.regs.fpr, r.regs.fpr);
    INFO("at the return: " << d);
    CHECK(d.empty());
    CHECK(h.regs.acc == r.regs.acc);
    for (std::size_t i = 0; i < kRanges.size(); ++i) {
        const std::size_t first = first_difference(h.mem[i].data(), r.mem[i].data(), h.mem[i].size());
        INFO("range " << hex64(kRanges[i].va) << ": first differing byte at +" << hex64(first));
        CHECK(first == h.mem[i].size());
    }
    return r;
}

Prepare f12(u32 bits) {
    return [bits](EEContext& c) { c.fpr[12] = bits; };
}
u64 rnd64(std::mt19937& rng) { return (static_cast<u64>(rng()) << 32) | rng(); }
// A random 64-bit register value that sometimes holds exactly `v` (and sometimes `v` with upper bits set).
u64 near(std::mt19937& rng, u64 v) {
    switch (rng() % 4) {
        case 0: return v;
        case 1: return v | (static_cast<u64>(rng() | 1u) << 32);
        case 2: return rng() % 4;
        default: return rnd64(rng);
    }
}

void fill(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
void set_task(Machine& m, u32 task, u32 work) { put32(m, task + kTaskWork, work); }

// The scene: record at kScene with (major, minor), the manager kMgr (or none), resources by type in lists.
void set_scene(Machine& m, s32 major, s32 minor, bool with_mgr) {
    put32(m, kSceneSlot, kScene);
    put32(m, kScene + kSceneMajor, static_cast<u32>(major));
    put32(m, kScene + kSceneMinor, static_cast<u32>(minor));
    put32(m, kScene + kSceneMgr, with_mgr ? kMgr : 0);
    std::memset(m.at(kMgr), 0, 22 * 4);
}
// Resource i (u16 id) linked at the head of its type's list.
void add_res(Machine& m, unsigned i, u16 id, u32 flags) {
    const u32 res = kRes0 + 0x100 * i;
    const u32 type = (id >> 10) & 0x3F;
    put16(m, res, id);
    put32(m, res + kResFlags, flags);
    put32(m, res + kResNext, get32(m, kMgr + 4 * type));
    put32(m, kMgr + 4 * type, res);
}

}  // namespace

// =====================================================================================================================

TEST_CASE("field_lo: collision controller accessors (sub_1AD870..sub_1AE470) match their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1AD870u};
    for (u32 i = 0; i < 300; ++i) {
        fill(m, kWork, 64, rng);
        set_task(m, kTask, kWork);
        const Args a{kTask, rnd64(rng), 0, 0};
        pair(m, PAIR(fn_sub_1AD870_001ad870), a, i, "sub_1AD870 " + std::to_string(i));
        pair(m, PAIR(fn_sub_1AD890_001ad890), a, i, "sub_1AD890 " + std::to_string(i));
        pair(m, PAIR(fn_K_FldFrame_CtlGetSphereCollisRadius_001ad8b0), a, i, "K_FldFrame_CtlGetSphereCollisRadius " + std::to_string(i));
        pair(m, PAIR(fn_K_FldFrame_CtlGetXGrid_001ad910), a, i, "K_FldFrame_CtlGetXGrid " + std::to_string(i));
        pair(m, PAIR(fn_K_FldFrame_CtlGetZGrid_001ad920), a, i, "K_FldFrame_CtlGetZGrid " + std::to_string(i));
        pair(m, PAIR(fn_sub_1AD930_001ad930), a, i, "sub_1AD930 " + std::to_string(i));
        pair(m, PAIR(fn_sub_1AE470_001ae470), a, i, "sub_1AE470 " + std::to_string(i));
        const u32 radii[] = {0u, 0x80000000u, fbits(12.5f), 0x00000001u /* denormal */, rng() & 0xBF7FFFFFu};
        pair(m, PAIR(fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0), a, i, "K_FldFrame_CtlSetSphereCollisRadius " + std::to_string(i), f12(radii[i % 5]));
    }
    // Documented rules: bit 28 follows a zero radius; set / clear are or / and-not.
    put32(m, kWork + kCtlFlags, 0x40000000u);
    pair(m, PAIR(fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0), Args{kTask, 0, 0, 0}, 1, "radius 0", f12(0));
    CHECK(get32(m, kWork + kCtlFlags) == 0x50000000u);
    pair(m, PAIR(fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0), Args{kTask, 0, 0, 0}, 1, "radius 3", f12(fbits(3.0f)));
    CHECK(get32(m, kWork + kCtlFlags) == 0x40000000u);
    CHECK(get32(m, kWork + kCtlRadius) == fbits(3.0f));
    pair(m, PAIR(fn_sub_1AD870_001ad870), Args{kTask, 0x8000000Fu, 0, 0}, 2, "set");
    CHECK(get32(m, kWork + kCtlFlags) == 0xC000000Fu);
    pair(m, PAIR(fn_sub_1AD890_001ad890), Args{kTask, 0x40000001u, 0, 0}, 3, "clear");
    CHECK(get32(m, kWork + kCtlFlags) == 0x8000000Eu);
}

TEST_CASE("field_lo: scene-id predicates (sub_1A02C0 / sub_1A01C0 / sub_1A0310) match on every major and key minors") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const s32 minors[] = {0, 1, 2, 3, 51, 52, 53, 7, -1};
    for (s32 major = -2; major <= 100; ++major) {
        for (s32 minor : minors) {
            set_scene(m, major, minor, true);
            const std::string w = std::to_string(major) + "/" + std::to_string(minor);
            const u32 seed = static_cast<u32>(major * 31 + minor);
            const Run fixed = pair(m, PAIR(fn_sub_1A02C0_001a02c0), Args{}, seed, "sub_1A02C0 " + w);
            const Run tart = pair(m, PAIR(fn_sub_1A01C0_001a01c0), Args{}, seed, "sub_1A01C0 " + w);
            const Run spec = pair(m, PAIR(fn_sub_1A0310_001a0310), Args{}, seed, "sub_1A0310 " + w);
            // Documented rules (26_field.md 3.2), independent of both bodies.
            const bool is_fixed = (major >= 51 && major <= 58) || (major >= 71 && major <= 78);
            const bool is_random = ((major >= 21 && major <= 28) || (major >= 41 && major <= 48)) && minor == 0;
            const bool is_tart = is_fixed || is_random || (major >= 30 && major <= 38);
            const bool is_spec = (major == 8 && minor == 3) || (major == 32 && minor == 2) ||
                                 (major == 26 && minor >= 51 && minor <= 53) || (major == 37 && minor == 1) ||
                                 (major == 35 && minor == 1) || major == 4 || major == 5;
            INFO(w);
            CHECK(fixed.o.v0 == (is_fixed ? 1u : 0u));
            CHECK(tart.o.v0 == (is_tart ? 1u : 0u));
            CHECK(spec.o.v0 == (is_spec ? 1u : 0u));
        }
    }
    std::mt19937 rng{0x1A0410u};
    for (u32 i = 0; i < 50; ++i) {
        set_scene(m, 1, 1, true);
        const Args a{rnd64(rng), 0, 0, 0};
        pair(m, PAIR(fn_sub_1A0410_001a0410), a, i, "sub_1A0410");
        CHECK(get32(m, kScene + kSceneWord24) == static_cast<u32>(a[0]));
        pair(m, PAIR(fn_sub_1A0420_001a0420), a, i, "sub_1A0420");
        CHECK(get32(m, kScene + kSceneWord28) == static_cast<u32>(a[0]));
    }
}

TEST_CASE("field_lo: scene-resource flag helpers and list heads match their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1A0150u};
    for (u32 i = 0; i < 400; ++i) {
        const bool with_mgr = (i % 7) != 0;
        set_scene(m, 21, 0, with_mgr);
        // Up to 8 resources: blocks (type 12), type 10, type 4.
        const unsigned n = rng() % 9;
        u16 ids[8] = {};
        for (unsigned k = 0; k < n; ++k) {
            static const u16 kTypes[] = {0x3000, 0x2800, 0x1000};
            ids[k] = static_cast<u16>(kTypes[rng() % 3] + (rng() % 64));
            add_res(m, k, ids[k], rng());
            fill(m, kRes0 + 0x100 * k + 252, 4, rng);
        }
        const u64 on = near(rng, 1);
        const u16 id = (n && rng() % 4) ? ids[rng() % n] : static_cast<u16>(0x3000 + rng() % 64);
        const std::string w = " #" + std::to_string(i);
        pair(m, PAIR(fn_sub_1A0150_001a0150), Args{id, on, 0, 0}, i, "sub_1A0150" + w);
        if (with_mgr) pair(m, PAIR(fn_sub_1A0DC0_001a0dc0), Args{id, on, 0, 0}, i, "sub_1A0DC0" + w);
        else pair(m, PAIR(fn_sub_1A0DC0_001a0dc0), Args{id, on, 0, 0}, i, "sub_1A0DC0 no manager" + w);
        put32(m, kField + kFieldBlocksHidden, rng());
        pair(m, PAIR(fn_sub_1A0040_001a0040), Args{near(rng, 1), near(rng, 1), 0, 0}, i, "sub_1A0040" + w);
        pair(m, PAIR(fn_sub_19FD40_0019fd40), Args{}, i, "sub_19FD40" + w);
        pair(m, PAIR(fn_sub_19FD70_0019fd70), Args{}, i, "sub_19FD70" + w);
        pair(m, PAIR(fn_sub_19FDA0_0019fda0), Args{}, i, "sub_19FDA0" + w);
        pair(m, PAIR(fn_sub_1A09D0_001a09d0), Args{}, i, "sub_1A09D0" + w);
        pair(m, PAIR(fn_sub_1A0A10_001a0a10), Args{}, i, "sub_1A0A10" + w);
        pair(m, PAIR(fn_sub_1A0A50_001a0a50), Args{}, i, "sub_1A0A50" + w);
    }
    // Documented rules: bit 1 of +40 follows `on == 1`; sub_1A0040 writes sField +52 = 0 / 1 per block.
    set_scene(m, 21, 0, true);
    add_res(m, 0, 0x3005, 0x10);
    add_res(m, 1, 0x3006, 0x12);
    add_res(m, 2, 0x2801, 0x0);
    pair(m, PAIR(fn_sub_1A0150_001a0150), Args{0x3005, 1, 0, 0}, 7, "set 0x3005");
    CHECK(get32(m, kRes0 + kResFlags) == 0x12u);
    pair(m, PAIR(fn_sub_1A0DC0_001a0dc0), Args{0x3006, 0, 0, 0}, 8, "clear 0x3006");
    CHECK(get32(m, kRes0 + 0x100 + kResFlags) == 0x10u);
    pair(m, PAIR(fn_sub_1A0040_001a0040), Args{1, 1, 0, 0}, 9, "all on");
    CHECK(get32(m, kRes0 + kResFlags) == 0x12u);
    CHECK(get32(m, kRes0 + 0x100 + kResFlags) == 0x12u);
    CHECK(get32(m, kRes0 + 0x200 + kResFlags) == 0x2u);
    CHECK(get32(m, kField + kFieldBlocksHidden) == 0u);
    pair(m, PAIR(fn_sub_1A0040_001a0040), Args{0, 0, 0, 0}, 10, "blocks off");
    CHECK(get32(m, kRes0 + kResFlags) == 0x10u);
    CHECK(get32(m, kRes0 + 0x200 + kResFlags) == 0x2u);  // type 10 untouched without the second argument
    CHECK(get32(m, kField + kFieldBlocksHidden) == 1u);
    const Run head = pair(m, PAIR(fn_sub_19FD70_0019fd70), Args{}, 11, "block head + 272");
    CHECK(static_cast<u32>(head.o.v0) == kRes0 + 0x100 + 272);  // the last added block is the head
    const Run none = pair(m, PAIR(fn_sub_1A09D0_001a09d0), Args{}, 12, "no type 4");
    CHECK(none.o.v0 == 0u);
}

TEST_CASE("field_lo: camera cylinder, field root, dungeon and pack accessors match their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1A48E0u};
    for (u32 i = 0; i < 200; ++i) {
        fill(m, kWork, 64, rng);
        fill(m, kVec, 12, rng);
        set_task(m, kTask, kWork);
        const std::string w = " #" + std::to_string(i);
        pair(m, PAIR(fn_sub_1A48E0_001a48e0), Args{kTask, rnd64(rng), 0, 0}, i, "sub_1A48E0" + w);
        pair(m, PAIR(fn_sub_1A48F0_001a48f0), Args{kTask, kVec, 0, 0}, i, "sub_1A48F0" + w);
        pair(m, PAIR(fn_sub_1A4920_001a4920), Args{kTask, 0, 0, 0}, i, "sub_1A4920" + w, f12(rng()));
        pair(m, PAIR(fn_sub_1A4930_001a4930), Args{kTask, 0, 0, 0}, i, "sub_1A4930" + w, f12(rng()));
        pair(m, PAIR(fn_sub_1BAB40_001bab40), Args{kTask, 0, 0, 0}, i, "sub_1BAB40" + w);
        pair(m, PAIR(fn_sub_1BAB50_001bab50), Args{kTask, 0, 0, 0}, i, "sub_1BAB50" + w);
        put32(m, kDungeonSlot, (i % 3) ? kTask : 0);
        pair(m, PAIR(fn_K_FldDungeon_RequestShutdown_001bff00), Args{}, i, "K_FldDungeon_RequestShutdown" + w);
        pair(m, PAIR(fn_K_FldDungeon_GetScrMemory_001bffe0), Args{}, i, "K_FldDungeon_GetScrMemory" + w);
        put32(m, kPackSlot, rng());
        pair(m, PAIR(fn_sub_1B0910_001b0910), Args{}, i, "sub_1B0910" + w);
    }
    put32(m, kDungeonSlot, kTask);
    put32(m, kWork + kDngShutdown, 0);
    pair(m, PAIR(fn_K_FldDungeon_RequestShutdown_001bff00), Args{}, 1, "shutdown");
    CHECK(get32(m, kWork + kDngShutdown) == 1u);
    put32(m, kWork + kDngScrMemory, 0x12345678u);
    CHECK(pair(m, PAIR(fn_K_FldDungeon_GetScrMemory_001bffe0), Args{}, 2, "script memory").o.v0 == 0x12345678u);
    put32(m, kDungeonSlot, 0);
    CHECK(pair(m, PAIR(fn_K_FldDungeon_GetScrMemory_001bffe0), Args{}, 3, "no dungeon").o.v0 == 0u);
}

TEST_CASE("field_lo: sequence checks (K_Seq_CheckField / sub_1B79F0 / sub_1B7AC0) match their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1B78A0u};
    for (u32 i = 0; i < 120; ++i) {
        // The kwln lists: the running list holds kTask2 -> (kTask or nothing).
        const bool alive = (i % 2) == 0;
        put32(m, kKwlnStarting, 0);
        put32(m, kKwlnEnding, (i % 5 == 0) ? kTask2 : 0);
        put32(m, kKwlnRunning, kTask2);
        put32(m, kTask2 + 0x40, alive ? kTask : 0);
        put32(m, kTask + 0x40, 0);
        put32(m, kField, (i % 7 == 3) ? 0 : kTask);
        put32(m, kDungeonSlot, (i % 7 == 3) ? 0 : kTask);
        const std::string w = " #" + std::to_string(i);
        const u32 root_before = get32(m, kField);
        const Run a = pair(m, PAIR(fn_K_Seq_CheckField_001b78a0), Args{}, i, "K_Seq_CheckField" + w);
        const bool exists = alive && root_before != 0;
        CHECK(a.o.v0 == (exists ? 0u : 1u));
        CHECK(get32(m, kField) == (exists ? root_before : 0u));
        put32(m, kField, root_before);
        pair(m, PAIR(fn_sub_1B79F0_001b79f0), Args{}, i, "sub_1B79F0" + w);
        const u32 dng_before = get32(m, kDungeonSlot);
        const Run d = pair(m, PAIR(fn_sub_1B7AC0_001b7ac0), Args{}, i, "sub_1B7AC0" + w);
        const bool dexists = alive && dng_before != 0;
        CHECK(d.o.v0 == (dexists ? 0u : 1u));
        CHECK(get32(m, kDungeonSlot) == (dexists ? dng_before : 0u));
    }
}

TEST_CASE("field_lo: EPL handle accessors (sub_1A9180 / sub_1A9390 / sub_1A93D0) match their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1A9180u};
    for (u32 i = 0; i < 300; ++i) {
        fill(m, kWork, 128, rng);
        for (u32 k = 0; k < 8; ++k)
            if (rng() % 2) put32(m, kWork + kEplHandles + 4 * k, 0);
        put32(m, kWork + kEplState, static_cast<u32>(static_cast<s32>(rng() % 5) - 2));
        set_task(m, kTask, kWork);
        const u64 task = (i % 4 == 0) ? 0 : (i % 4 == 1) ? (kTask | (static_cast<u64>(rng() | 1u) << 32)) : kTask;
        const u64 idx = (i % 5 == 0) ? static_cast<u64>(-1) : (i % 11 == 0) ? (static_cast<u64>(-1) << 40) | 2 : rng() % 8;
        const std::string w = " #" + std::to_string(i);
        const Run r = pair(m, PAIR(fn_sub_1A9180_001a9180), Args{task, 0, 0, 0}, i, "sub_1A9180" + w);
        const s32 state = static_cast<s32>(get32(m, kWork + kEplState));
        CHECK(r.o.v0 == ((task == 0 || state >= 1) ? 1u : 0u));
        pair(m, PAIR(fn_sub_1A9390_001a9390), Args{kTask, idx, rnd64(rng), 0}, i, "sub_1A9390" + w);
        pair(m, PAIR(fn_sub_1A93D0_001a93d0), Args{kTask, idx, 0, 0}, i, "sub_1A93D0" + w);
    }
}

TEST_CASE("field_lo: the floor grid cell marker sub_1BB090 matches its recompiled body") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1BB090u};
    for (u32 i = 0; i < 250; ++i) {
        std::memset(m.at(kField), 0, 0x2000);
        // A few taken cells (K_Assert 292 paths) in random places.
        for (u32 k = rng() % 4; k > 0; --k) m.at(kField + kGridBase + kGridRow * (rng() % 16) + kGridCell * (rng() % 16))[0] = 1;
        const u32 w = 1 + rng() % 4, d = 1 + rng() % 4;
        fill(m, kBlock, kBlockRowStride * 5, rng);
        m.at(kBlock)[1] = static_cast<u8>(w);
        m.at(kBlock)[2] = static_cast<u8>(d);
        put32(m, kCounterSlot, rng());
        // Mostly inside the grid; sometimes past its edge (K_Assert 262 / 263, which continue); high bits masked.
        u64 x = (i % 9 == 0) ? 16 - (rng() % 2) : rng() % (17 - w);
        u64 z = (i % 10 == 0) ? 16 - (rng() % 2) : rng() % (17 - d);
        if (i % 6 == 0) x |= static_cast<u64>(rng()) << 16;
        if (i % 7 == 0) z |= static_cast<u64>(rng()) << 16;
        const u32 tag = rng();
        pair(m, PAIR(fn_sub_1BB090_001bb090), Args{kBlock, x, z, tag}, i, "sub_1BB090 #" + std::to_string(i));
    }
    // Documented rule: a 2 x 1 block at (3, 5) on an empty grid.
    std::memset(m.at(kField), 0, 0x2000);
    std::memset(m.at(kBlock), 0, kBlockRowStride * 2);
    m.at(kBlock)[0] = 0xF0;
    m.at(kBlock)[1] = 2;
    m.at(kBlock)[2] = 1;
    m.at(kBlock)[3] = 9;
    m.at(kBlock)[kBlockCellByte] = 0x11;
    m.at(kBlock)[kBlockCellByte + kBlockCellStride] = 0x22;
    put32(m, kCounterSlot, 0x105);
    pair(m, PAIR(fn_sub_1BB090_001bb090), Args{kBlock, 3, 5, 0x4477}, 1, "2x1 at (3, 5)");
    const u8* c0 = m.at(kField + kGridBase + kGridRow * 5 + kGridCell * 3);
    const u8* c1 = c0 + kGridCell;
    CHECK(c0[0] == 1);
    CHECK(c0[1] == 1);  // the origin
    CHECK(c1[1] == 0);
    CHECK(c0[2] == 0xF0);
    CHECK(c0[6] == 0x77);
    CHECK(c0[7] == 2);
    CHECK(c0[8] == 1);
    CHECK(c0[9] == 0x05);
    CHECK(c0[10] == 9);
    CHECK(c0[11] == 0x11);
    CHECK(c1[0] == 1);
    CHECK(c1[11] == 0x22);
    CHECK(get32(m, kCounterSlot) == 0x106u);
}

TEST_CASE("field_lo: the enemy-think queue (sub_1B0220..sub_1B0260, sub_1AFF70, sub_1B0020) matches its recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x1AFF70u};
    constexpr u32 kUnit = kArena + 0x1400;
    for (u32 i = 0; i < 300; ++i) {
        fill(m, kWork, 0x600, rng);
        fill(m, kWork2, 64, rng);
        set_task(m, kTask, kWork);
        set_task(m, kTask2, kWork2);
        put32(m, kWork + kThinkUnit, kUnit);
        put32(m, kUnit + kUnitCollisionTask, kTask2);
        const s32 count = static_cast<s32>(rng() % 51) - 2;
        put32(m, kWork + kThinkCount, static_cast<u32>(count));
        if (count > 0 && count <= 47) put32(m, kWork + kThinkQueue + kThinkEntrySize * (count - 1), rng() % 3);
        fill(m, kVec, 12, rng);
        const std::string w = " #" + std::to_string(i);
        pair(m, PAIR(fn_sub_1B0220_001b0220), Args{kTask, 0, 0, 0}, i, "sub_1B0220" + w);
        pair(m, PAIR(fn_sub_1B0240_001b0240), Args{kTask, rnd64(rng), 0, 0}, i, "sub_1B0240" + w);
        pair(m, PAIR(fn_sub_1B0260_001b0260), Args{kTask, near(rng, 1), 0, 0}, i, "sub_1B0260" + w);
        put32(m, kWork + kThinkCount, static_cast<u32>(count));
        const u32 value = (i % 3 == 0) ? rng() : rng() % 200;
        const Run p = pair(m, PAIR(fn_sub_1AFF70_001aff70), Args{kTask, value, 0, 0}, i, "sub_1AFF70" + w);
        const bool last_is_wait = count > 0 && count <= 47 && get32(m, kWork + kThinkQueue + kThinkEntrySize * (count - 1)) == 1;
        const bool pushed = count < 47 && !last_is_wait;
        CHECK(p.o.v0 == (pushed ? 1u : 0u));
        if (pushed && value < 200) {  // exact in a single
            CHECK(get32(m, kWork + kThinkCount) == static_cast<u32>(count + 1));
            float f;
            std::memcpy(&f, m.at(kWork + kThinkQueue + kThinkEntrySize * count + 16), 4);
            CHECK(f == static_cast<float>(static_cast<s32>(value)));
        }
        put32(m, kWork + kThinkCount, static_cast<u32>(count));
        const Run q = pair(m, PAIR(fn_sub_1B0020_001b0020), Args{kTask, kVec, rnd64(rng), 0}, i, "sub_1B0020" + w);
        CHECK(q.o.v0 == (count < 47 ? 1u : 0u));
    }
    // Documented rule: mode 1 freezes the unit's controller (bit 27), any other mode unfreezes it.
    put32(m, kWork2 + kCtlFlags, 0x1u);
    pair(m, PAIR(fn_sub_1B0260_001b0260), Args{kTask, 1, 0, 0}, 1, "freeze");
    CHECK(get32(m, kWork2 + kCtlFlags) == 0x08000001u);
    CHECK(get32(m, kWork + kThinkMode) == 1u);
    pair(m, PAIR(fn_sub_1B0260_001b0260), Args{kTask, 3, 0, 0}, 2, "unfreeze");
    CHECK(get32(m, kWork2 + kCtlFlags) == 0x1u);
    MESSAGE("field_lo: " << g_pairs << " pairs compared");
}

#endif  // P3FES_GAME_HAVE_GENERATED
