// Phase 5 pair tests for slice ui3 (game/src/ui/ui3.cpp): every hand-written camp-menu / HUD function and the
// recompiled body it replaces run on identical guest machines -- a random UI world (kwln tasks on the kernel's list with
// their work records: the camp root, the main list, the flash control, the two side portraits, the setup and screen
// tasks, the HUD draw / slide works, the highlight record, a camera with its begin / end callbacks, the RW render-state
// device pointers, the gp-relative camp globals, the flag bits, the date, the pad words) and a random register file --
// and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * guest memory: the world, .data / .bss (the gp-relative globals, the pad words, the flags, the slot table), the
//     device pointers, low RAM, the stack around $sp (live frame, the frames and spills of the run below it), the arena.
// The test build emits the list's animation helpers (sub_11E380, sub_11D3A0, sub_11CC80, sub_11C550 and their sub_18BC10),
// the camera getter and RwCameraBegin/EndUpdate, so the close / reopen / selection paths and the HUD task's camera bracket
// run to the end; the screen creators, the sprite / HUD draws and printf are not emitted (compared stops). The camera
// callbacks and the render-state device pointers point at emitted functions with defined behaviour, one of them a
// non-leaf that spills the $ra it gets below the $sp it gets (sub_1F1C50: the frame / link discipline of the `jalr`).
// Documented rules (20_menu_ui.md sections 2-3, ui3.h) are checked on the host independently of both bodies; the
// side-portrait transitions are decoded on the host straight from the ELF's jump tables and case instructions.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/ui3.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <map>
#include <string>
#include <tuple>
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
P3FES_DECL_PAIR(fn_sub_119A20_00119a20)
P3FES_DECL_PAIR(fn_sub_119A60_00119a60)
P3FES_DECL_PAIR(fn_sub_119A80_00119a80)
P3FES_DECL_PAIR(fn_H_Camp_UpdateDrawTask_0011a050)
P3FES_DECL_PAIR(fn_H_Camp_UpdateRootDrawTask_0011b420)
P3FES_DECL_PAIR(fn_sub_11B9B0_0011b9b0)
P3FES_DECL_PAIR(fn_sub_11BA00_0011ba00)
P3FES_DECL_PAIR(fn_sub_11BA50_0011ba50)
P3FES_DECL_PAIR(fn_sub_11E370_0011e370)
P3FES_DECL_PAIR(fn_sub_121DE0_00121de0)
P3FES_DECL_PAIR(fn_sub_122710_00122710)
P3FES_DECL_PAIR(fn_sub_123640_00123640)
P3FES_DECL_PAIR(fn_sub_124E00_00124e00)
P3FES_DECL_PAIR(fn_sub_127AB0_00127ab0)
P3FES_DECL_PAIR(fn_sub_127AD0_00127ad0)
P3FES_DECL_PAIR(fn_sub_127AF0_00127af0)
P3FES_DECL_PAIR(fn_sub_127FF0_00127ff0)
P3FES_DECL_PAIR(fn_sub_128010_00128010)
P3FES_DECL_PAIR(fn_sub_128030_00128030)
P3FES_DECL_PAIR(fn_sub_128140_00128140)
P3FES_DECL_PAIR(fn_sub_133B40_00133b40)
P3FES_DECL_PAIR(fn_sub_133B70_00133b70)
P3FES_DECL_PAIR(fn_sub_136820_00136820)
P3FES_DECL_PAIR(fn_sub_138E80_00138e80)
P3FES_DECL_PAIR(fn_sub_13BCB0_0013bcb0)
P3FES_DECL_PAIR(fn_sub_166C00_00166c00)
P3FES_DECL_PAIR(fn_sub_166C30_00166c30)
P3FES_DECL_PAIR(fn_sub_166C50_00166c50)
P3FES_DECL_PAIR(fn_sub_167EF0_00167ef0)
P3FES_DECL_PAIR(fn_sub_167F10_00167f10)
P3FES_DECL_PAIR(fn_sub_167F30_00167f30)
P3FES_DECL_PAIR(fn_sub_1681D0_001681d0)
P3FES_DECL_PAIR(fn_sub_1685B0_001685b0)
P3FES_DECL_PAIR(fn_sub_1685D0_001685d0)
P3FES_DECL_PAIR(fn_sub_169420_00169420)
P3FES_DECL_PAIR(fn_H_DayPartsPos_UpdateTask_001832c0)
P3FES_DECL_PAIR(fn_H_DayPartsDraw_UpdateTask_00183410)
P3FES_DECL_PAIR(fn_H_DayPartsDraw_DrawHud_001842c0)
P3FES_DECL_PAIR(fn_sub_1848F0_001848f0)
P3FES_DECL_PAIR(fn_H_DayPartsDraw_SetDate_00184c80)
P3FES_DECL_PAIR(fn_sub_187EA0_00187ea0)
P3FES_DECL_PAIR(fn_sub_188420_00188420)
P3FES_DECL_PAIR(fn_sub_188640_00188640)
P3FES_DECL_PAIR(fn_sub_188660_00188660)
P3FES_DECL_PAIR(fn_sub_1885F0_001885f0)
P3FES_DECL_PAIR(fn_sub_188BE0_00188be0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace u3 = p3fes::game::ui3;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }
#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the UI world (free RAM above the arena) ------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kTasks = kWorld;                  // 12 kwln tasks, 0x80 apart (+28 state, +60 work, +64 list next)
constexpr u32 kNumTasks = 12;
constexpr u32 kWorks = kWorld + 0x1000u;        // their work records, 0x400 apart
constexpr u32 kHighlight = kWorld + 0x5000u;    // gp-19876: the list highlight record (sub_11D3A0 writes 7 x 68 bytes, +680, +800)
constexpr u32 kCamera = kWorld + 0x6000u;       // gp-19504: +24 begin-update callback, +28 end-update callback
constexpr u32 kSprHandle = kWorld + 0x6100u;    // the HUD's sprite file handle (s16 state at +0, 5 = loaded)
enum Role : u32 { kCampDraw, kRoot, kFlash, kPcKani, kPersonaKani, kSetup, kScreen0, kScreen1, kScreen2, kScreen3, kHudDraw, kHudPos };
constexpr u32 task_of(u32 role) { return kTasks + 0x80u * role; }
constexpr u32 work_of(u32 role) { return kWorks + 0x400u * role; }

constexpr u32 kGp = 0x7D2CF0u;
constexpr u32 gp(s32 off) { return kGp + static_cast<u32>(off); }
constexpr u32 kKwlnList0 = gp(-19596), kKwlnList1 = gp(-19572), kKwlnList2 = gp(-19584);
constexpr u32 kCameraSlot = gp(-19504);
constexpr u32 kScenario = gp(-19788);           // sub_17D800: 1 = The Answer
constexpr u32 kDays = 0x83679Cu, kTime = 0x83679Eu, kFlagWords = 0x83A21Cu;
constexpr u32 kRenderSet = 0x960090u, kRenderGet = 0x960094u;
// Emitted call targets with defined behaviour: sub_4B3710 (`jr ra; move v0, a1`), sub_188640 (returns 0, this slice),
// sub_1F1C50 (non-leaf: spills $ra below its $sp, returns gp-18968).
constexpr u32 kTargets[] = {0x4B3710u, 0x188640u, 0x1F1C50u};

struct Window {
    u32 va;
    u32 len;
};
const Window kWindows[] = {
    {kWorld, kWorldSize},              // the UI world
    {0x0u, 0x1000u},                   // low RAM: callees that follow a null pointer write there
    {0x7C0000u, 0x80000u},             // .data / .bss: gp-relative words, the pad words, the slot table, the date, the flags
    {0x950000u, 0x20000u},             // the RW device pointers
    {kSp - 0x1000u, 0x1100u},          // the stack: frames and spills of the run, and the caller's live frame
    {kArena, kArenaSize},
};

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
u16 load16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + va, 2);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void storef(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
float loadf(const Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.mem.main_ram() + va, 4);
    return f;
}
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
// A 32-bit value as a register argument, sometimes with garbage in the upper half (the bodies take whole registers).
u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 20) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }
u32 small(std::mt19937& rng, u32 n) { return chance(rng, 92) ? rng() % n : rng(); }
void set_flag(Machine& m, u32 id, bool on) {
    const u32 w = kFlagWords + 4 * (id / 32);
    store32(m, w, on ? (load32(m, w) | (1u << (id % 32))) : (load32(m, w) & ~(1u << (id % 32))));
}

void random_world(Machine& m, std::mt19937& rng) {
    for (u32 off = 0; off < kWorldSize; off += 4) store32(m, kWorld + off, rng());
    // the kwln tasks: work pointers, a state nibble 0..3 (rarely invalid -> GetState's printf), mostly on the list
    u32 prev = 0;
    store32(m, kKwlnList0, 0);
    store32(m, kKwlnList1, 0);
    store32(m, kKwlnList2, 0);
    for (u32 r = 0; r < kNumTasks; ++r) {
        const u32 t = task_of(r);
        store32(m, t + 60, work_of(r));
        store32(m, t + 28, (rng() & ~0xFu) | (chance(rng, 97) ? rng() % 4 : rng() % 16));
        store32(m, t + 64, 0);
        if (chance(rng, 90)) {
            if (prev == 0) store32(m, kKwlnList0, t);
            else store32(m, prev + 64, t);
            prev = t;
        }
    }
    // the camp globals
    store32(m, gp(-19884), small(rng, 7));
    store32(m, gp(-19880), chance(rng, 25) ? 0u : task_of(kSetup));
    store32(m, gp(-19876), kHighlight);
    store32(m, gp(-19872), task_of(kFlash));
    store32(m, gp(-19868), task_of(kPcKani));
    store32(m, gp(-19864), task_of(kPersonaKani));
    store32(m, gp(-19860), chance(rng, 30) ? 0u : task_of(kRoot));
    for (s32 off : {-19820, -19824, -19696, -19692})
        store32(m, gp(off), chance(rng, 15) ? 0u : task_of(kScreen0 + rng() % 4));
    store32(m, kScenario, pick(rng, {0u, 0u, 1u, rng()}));
    // camera and device pointers
    store32(m, kCameraSlot, kCamera);
    store32(m, kCamera + 24, chance(rng, 15) ? 0x188640u : kTargets[rng() % 3]);
    store32(m, kCamera + 28, kTargets[rng() % 3]);
    store32(m, kRenderSet, kTargets[rng() % 3]);
    store32(m, kRenderGet, kTargets[rng() % 3]);
    // flags, date, pad words
    for (u32 i = 0; i < 176; ++i) store32(m, kFlagWords + 4 * i, chance(rng, 50) ? 0u : rng());
    store16(m, kDays, static_cast<u16>(chance(rng, 95) ? rng() % 300 : rng()));
    m.at(kTime)[0] = static_cast<u8>(chance(rng, 95) ? rng() % 10 : rng());
    for (u32 off = 0; off < 0x10; off += 2) store16(m, 0x7E094Cu + off, static_cast<u16>(chance(rng, 50) ? 0u : rng()));
    if (chance(rng, 40)) store16(m, u3::kPadPressed, static_cast<u16>(pick(rng, {u3::kPadUp, u3::kPadDown})));
    if (chance(rng, 30)) store16(m, u3::kPadRepeat, static_cast<u16>(pick(rng, {u3::kPadUp, u3::kPadDown, 0u})));
    if (chance(rng, 30)) store16(m, u3::kPadHeld, static_cast<u16>(pick(rng, {u3::kPadUp, u3::kPadDown, 0u})));

    // the camp root's work
    u32 w = work_of(kCampDraw);
    store32(m, w + u3::kCampState, small(rng, 23));
    store32(m, w + u3::kCampEquipTask, task_of(kScreen0 + rng() % 4));
    store32(m, w + u3::kCampScreenTask, task_of(kScreen0 + rng() % 4));
    store32(m, w + u3::kCampFlash, task_of(kFlash));
    store32(m, w + u3::kCampReopen, pick(rng, {0u, 1u}));
    // the main list's work
    w = work_of(kRoot);
    store32(m, w + u3::kRootState, small(rng, 12));
    store32(m, w + u3::kRootFrames, chance(rng, 85) ? rng() % 26 : rng());
    store32(m, w + u3::kRootOpenMode, pick(rng, {0u, 1u, 1u, 0u, 2u}));
    store32(m, w + u3::kRootCursor, chance(rng, 95) ? rng() % 7 : rng());
    store32(m, w + u3::kRootFlash, task_of(kFlash));
    store32(m, w + u3::kRootInput, pick(rng, {0u, 1u, 1u, 1u}));
    // the flash control (sub_11E380 starts it only from state 0)
    w = work_of(kFlash);
    store32(m, w + 0, chance(rng, 70) ? 0u : rng() % 20);
    store32(m, w + 8, small(rng, 18));
    store32(m, w + 16, pick(rng, {0u, 1u}));
    // the side portraits and the other tasks
    for (u32 r : {kPcKani, kPersonaKani}) {
        store32(m, work_of(r) + u3::kKaniState, rng() % 16);
        store32(m, work_of(r) + u3::kKaniScreen, small(rng, 20));
    }
    store32(m, work_of(kSetup), rng() % 5);
    for (u32 r = kScreen0; r <= kScreen3; ++r) store32(m, work_of(r), small(rng, 10));
    // the HUD draw work
    w = work_of(kHudDraw);
    store32(m, w + u3::kHudState, small(rng, 10));
    store32(m, w + u3::kHudEnabled, pick(rng, {0u, 1u, 1u}));
    store32(m, w + u3::kHudVisible, pick(rng, {0u, 1u, 1u}));
    store32(m, w + u3::kHudMonth, 1 + rng() % 12);
    store32(m, w + u3::kHudDay, 1 + rng() % 31);
    store32(m, w + u3::kHudPart, rng() % 10);
    store32(m, w + u3::kHudFade, static_cast<u32>(static_cast<s32>(rng() % 81) - 10));
    store32(m, w + u3::kHudFrame, rng() % 400);
    store32(m, w + u3::kHudNewMonth, 1 + rng() % 12);
    store32(m, w + u3::kHudNewDay, 1 + rng() % 31);
    store32(m, w + u3::kHudNewPart, rng() % 10);
    store32(m, w + u3::kHudSprFile, kSprHandle);
    store32(m, w + u3::kHudChild, task_of(kScreen0 + rng() % 4));
    store16(m, kSprHandle, static_cast<u16>(pick(rng, {5u, 5u, 4u, rng() & 0xFFFFu})));
    // the HUD slide work
    w = work_of(kHudPos);
    store32(m, w + 4, chance(rng, 90) ? rng() % 12 : rng());
    storef(m, w + 8, static_cast<float>(rng() % 401));
    storef(m, w + 16, chance(rng, 50) ? 0.0f : 400.0f);
    storef(m, w + 24, static_cast<float>(rng() % 401));
    store32(m, w + 32, pick(rng, {0u, 1u}));
}

// --- the register file at a check point / the return / a stop ----------------------------------------------------
struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0, acc = 0;
    std::array<u32, 32> fpr{};
};
Snap snap(const EEContext& c) {
    Snap s;
    s.cycles = c.cycles;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = c.gpr[r];
    s.hi = c.hi;
    s.lo = c.lo;
    s.sa = c.sa;
    s.fcr31 = c.fcr31;
    s.acc = c.acc;
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = c.fpr[i];
    return s;
}
// The first difference (empty when equal).
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "gpr " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa || a.fcr31 != b.fcr31) return "sa/fcr31";
    if (a.acc != b.acc) return "acc";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds the hand
// version's frames, whose destructors run the epilogue).
class UiHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap at_stop;
    int syscalls = 0;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override { snaps.push_back(snap(ctx)); }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stopped = true;
        stop_pc = pc;
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
};

struct Run {
    bool stopped = false;
    u32 stop_pc = 0;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
    std::vector<std::vector<u8>> mem;
};

// Registers set after the random context besides $a0..$a3: $t0..$t3 (the dispatchers' kind / extra arguments).
using Extra = std::array<u64, 4>;

Run run_one(Machine& m, Fn fn, const Args& args, const Extra* t, u32 seed) {
    UiHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    if (t)
        for (unsigned i = 0; i < 4; ++i) m.ctx.gpr[GPR_T0 + i].u64[0] = (*t)[i];
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    Run r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.syscalls = h.syscalls;
    r.snaps = std::move(h.snaps);
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    for (const Window& w : kWindows) r.mem.push_back(m.bytes(w.va, w.len));
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;  // missing function -> count
};
std::map<std::string, Stats> g_stats;
const char* g_current = "";  // the pair running when a callee ends the process (named by the terminate handler)

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place. Returns the recompiled run.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Extra* t = nullptr) {
    std::vector<std::vector<u8>> before;
    for (const Window& w : kWindows) before.push_back(m.bytes(w.va, w.len));
    g_current = what;
    std::set_terminate([] {
        std::fprintf(stderr, "terminate in %s\n", g_current);
        std::abort();
    });
    Run h = run_one(m, hand, args, t, seed);
    for (std::size_t i = 0; i < std::size(kWindows); ++i) std::memcpy(m.at(kWindows[i].va), before[i].data(), kWindows[i].len);
    Run r = run_one(m, recomp, args, t, seed);
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
    }
    const std::string name(what);
    INFO(name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " seed=" << seed);
    REQUIRE(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = diff(h.end, r.end);
        const std::string where = r.stopped ? "at the stop: " : "at the return: ";
        INFO(where << d);
        CHECK(d.empty());
    }
    for (std::size_t i = 0; i < std::size(kWindows); ++i) {
        const auto& a = h.mem[i];
        const auto& b = r.mem[i];
        std::size_t first = 0;
        while (first < a.size() && a[first] == b[first]) ++first;
        INFO("memory window " << hex64(kWindows[i].va) << ": first differing byte at " << hex64(kWindows[i].va + first));
        CHECK(first == a.size());
    }
    return r;
}

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// --- the specs: each function with its argument generator --------------------------------------------------------
enum class Arg { none, camp, root, flash, kani_pc, kani_persona, screen, hud_draw, hud_pos, slot_get, slot_set, item, value, words, dispatch, hud_frame };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
};
#define SPEC(name, kind) {#name, PAIR(name), Arg::kind}
const Spec kSpecs[] = {
    SPEC(fn_sub_119A20_00119a20, none),
    SPEC(fn_sub_119A60_00119a60, slot_get),
    SPEC(fn_sub_119A80_00119a80, slot_set),
    SPEC(fn_H_Camp_UpdateDrawTask_0011a050, camp),
    SPEC(fn_H_Camp_UpdateRootDrawTask_0011b420, root),
    SPEC(fn_sub_11B9B0_0011b9b0, root),
    SPEC(fn_sub_11BA00_0011ba00, root),
    SPEC(fn_sub_11BA50_0011ba50, root),
    SPEC(fn_sub_11E370_0011e370, flash),
    SPEC(fn_sub_121DE0_00121de0, kani_pc),
    SPEC(fn_sub_122710_00122710, kani_persona),
    SPEC(fn_sub_123640_00123640, dispatch),
    SPEC(fn_sub_124E00_00124e00, dispatch),
    SPEC(fn_sub_127AB0_00127ab0, screen),
    SPEC(fn_sub_127AD0_00127ad0, screen),
    SPEC(fn_sub_127AF0_00127af0, screen),
    SPEC(fn_sub_127FF0_00127ff0, screen),
    SPEC(fn_sub_128010_00128010, screen),
    SPEC(fn_sub_128030_00128030, screen),
    SPEC(fn_sub_128140_00128140, dispatch),
    SPEC(fn_sub_133B40_00133b40, value),
    SPEC(fn_sub_133B70_00133b70, screen),
    SPEC(fn_sub_136820_00136820, dispatch),
    SPEC(fn_sub_138E80_00138e80, dispatch),
    SPEC(fn_sub_13BCB0_0013bcb0, item),
    SPEC(fn_sub_166C00_00166c00, screen),
    SPEC(fn_sub_166C30_00166c30, screen),
    SPEC(fn_sub_166C50_00166c50, screen),
    SPEC(fn_sub_167EF0_00167ef0, screen),
    SPEC(fn_sub_167F10_00167f10, screen),
    SPEC(fn_sub_167F30_00167f30, screen),
    SPEC(fn_sub_1681D0_001681d0, none),
    SPEC(fn_sub_1685B0_001685b0, screen),
    SPEC(fn_sub_1685D0_001685d0, screen),
    SPEC(fn_sub_169420_00169420, none),
    SPEC(fn_H_DayPartsPos_UpdateTask_001832c0, hud_pos),
    SPEC(fn_H_DayPartsDraw_UpdateTask_00183410, hud_draw),
    SPEC(fn_H_DayPartsDraw_DrawHud_001842c0, hud_frame),
    SPEC(fn_sub_1848F0_001848f0, hud_draw),
    SPEC(fn_H_DayPartsDraw_SetDate_00184c80, hud_draw),
    SPEC(fn_sub_187EA0_00187ea0, screen),
    SPEC(fn_sub_188420_00188420, words),
    SPEC(fn_sub_188640_00188640, none),
    SPEC(fn_sub_188660_00188660, none),
    SPEC(fn_sub_1885F0_001885f0, none),
    SPEC(fn_sub_188BE0_00188be0, none),
};
#undef SPEC

Args args_for(Arg kind, std::mt19937& rng, Extra& t) {
    for (u64& x : t) x = (static_cast<u64>(rng()) << 32) | rng();
    const auto task = [&](u32 role) { return wide(rng, chance(rng, 95) ? task_of(role) : task_of(rng() % kNumTasks)); };
    const u32 enabled = pick(rng, {0u, 1u, 1u, 1u, rng()});
    switch (kind) {
    case Arg::none: return Args{rng(), rng(), rng(), rng()};
    case Arg::camp: return Args{task(kCampDraw), rng(), rng(), rng()};
    case Arg::root: return Args{task(kRoot), rng(), rng(), rng()};
    case Arg::flash: return Args{task(kFlash), rng(), rng(), rng()};
    case Arg::kani_pc: return Args{task(kPcKani), wide(rng, small(rng, 20)), rng(), rng()};
    case Arg::kani_persona: return Args{task(kPersonaKani), wide(rng, small(rng, 20)), rng(), rng()};
    case Arg::screen: return Args{task(kScreen0 + rng() % 4), rng(), rng(), rng()};
    case Arg::hud_draw:  // always the HUD task: a wild month in +24 would make clndGetDaysSinceStartFromDate run 2^32 steps
        return Args{wide(rng, task_of(kHudDraw)), wide(rng, enabled), rng(), rng()};
    case Arg::hud_pos: return Args{task(kHudPos), rng(), rng(), rng()};
    case Arg::slot_get: return Args{wide(rng, static_cast<u32>(static_cast<s32>(rng() % 80) - 20)), rng(), rng(), rng()};
    case Arg::slot_set: return Args{wide(rng, static_cast<u32>(static_cast<s32>(rng() % 80) - 20)), (static_cast<u64>(rng()) << 32) | rng(), rng(), rng()};
    case Arg::item: return Args{wide(rng, rng() % 40), wide(rng, rng() % 10), rng(), rng()};
    case Arg::value: return Args{task(kScreen0 + rng() % 4), (static_cast<u64>(rng()) << 32) | rng(), rng(), rng()};
    case Arg::words: return Args{task(kScreen0 + rng() % 4), (static_cast<u64>(rng()) << 32) | rng(), rng(), rng()};
    case Arg::hud_frame:  // (task, month, day, part; $t0 fade, $t1 frame, $t2 &extra)
        t[0] = sx(static_cast<u32>(static_cast<s32>(rng() % 81) - 10));
        t[1] = sx(rng() % 360);
        t[2] = sx(work_of(kHudDraw) + u3::kHudExtra);
        return Args{task(kHudDraw), wide(rng, 1 + rng() % 12), wide(rng, 1 + rng() % 31), wide(rng, pick(rng, {8u, 8u, rng() % 10}))};
    case Arg::dispatch: {
        // the kind sits in $a3 (sub_123640 / 124E00), $a2 (sub_128140), $t1 (sub_136820) or $t2 (sub_138E80)
        const u32 k = chance(rng, 85) ? rng() % 5 : rng();
        t[1] = chance(rng, 50) ? sx(k) : t[1];
        t[2] = chance(rng, 50) ? sx(k) : t[2];
        return Args{rng(), rng(), wide(rng, chance(rng, 50) ? k : rng() % 5), wide(rng, chance(rng, 50) ? k : rng() % 3)};
    }
    }
    return {};
}

// --- host decode of the side-portrait switches straight from the ELF ---------------------------------------------
// A case is `li v1, s; sw v1, 0(v0)` (state s), the exit address (nothing), or `lw v1, 12(v0); sltiu at, v1, n;
// beqz at; nop; lui a0, 0x7B; addiu a0, a0, lo; ...` (a second switch on the current screen through that table).
int host_kani_state(const Machine& m, u32 outer_table, u32 exit_pc, u32 screen, u32 cur) {
    if (screen >= 17) return -1;
    u32 target = load32(m, outer_table + 4 * screen);
    for (int depth = 0; depth < 2; ++depth) {
        if (target == exit_pc) return -1;
        const u32 insn = load32(m, target);
        if ((insn & 0xFFFF0000u) == 0x24030000u) return static_cast<int>(static_cast<s16>(insn & 0xFFFFu));  // li v1, s
        if (insn != 0x8C43000Cu || depth == 1) return -2;                                                     // lw v1, 12(v0)
        const u32 bound = load32(m, target + 4) & 0xFFFFu;                                                    // sltiu at, v1, n
        const u32 hi = load32(m, target + 16) & 0xFFFFu, lo = load32(m, target + 20) & 0xFFFFu;
        const u32 table = (hi << 16) + static_cast<u32>(static_cast<s32>(static_cast<s16>(lo)));
        if (cur >= bound) return -1;
        target = load32(m, table + 4 * cur);
    }
    return -2;
}

}  // namespace

// printf (0x5225A8) is hand-written since finalB (game/src/fx/finalB.cpp): its forwarder runs the body -- vfprintf into
// the stdout FILE, which waits on the IOP without end -- where these pairs ended at it as at a function this build does
// not emit (an endless walk grew `snaps` until the host ran out of memory). The stop keeps the stop: both runs end at
// the call and are compared there (StandIns::install_stop). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas) si.install_stop(va, "stopped at, as when it was not emitted");
        scope = std::make_unique<StandInsScope>(si);
    }
};

TEST_CASE("game(ui3): every replaced function equals its recompiled body on random UI worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    std::mt19937 rng{0x0C3A1u};
    g_stats.clear();
    constexpr int kWorlds = 600;
    for (int it = 0; it < kWorlds; ++it) {
        random_world(m, rng);
        for (const Spec& s : kSpecs) {
            Extra t{};
            const Args a = args_for(s.arg, rng, t);
            pair(m, s.hand, s.recomp, a, rng(), s.name, &t);
        }
    }
    int pairs = 0, stops = 0, complete = 0;
    std::string always_stopped;
    for (const auto& [name, st] : g_stats) {
        pairs += st.pairs;
        stops += st.stops;
        if (st.stops < st.pairs) {
            ++complete;
        } else {
            always_stopped += " " + name + " (at";
            for (const auto& [pc, n] : st.stop_at) always_stopped += " " + hex64(pc);
            always_stopped += ")";
        }
    }
    MESSAGE("ui3: " << pairs << " pairs over " << std::size(kSpecs) << " functions, " << stops
                    << " ended at a compared missing-function stop; " << complete
                    << " functions also returned normally; always at a stop (a big callee first):" << always_stopped);
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(ui3): every state of the camp root and the list, every portrait transition, every HUD state") {
    // Exhaustive sweeps over the state words (each also with random surroundings), on top of the random worlds above.
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    std::mt19937 rng{0x5EE9u};
    int runs = 0;
    for (int rep = 0; rep < 12; ++rep) {
        for (u32 s = 0; s < 23; ++s) {
            random_world(m, rng);
            store32(m, work_of(kCampDraw) + u3::kCampState, s);
            pair(m, PAIR(fn_H_Camp_UpdateDrawTask_0011a050), Args{sx(task_of(kCampDraw)), 0, 0, 0}, rng(), "camp state");
            ++runs;
        }
        // state 3 by every selection (-3..7)
        for (s32 sel = -3; sel <= 7; ++sel) {
            random_world(m, rng);
            store32(m, work_of(kCampDraw) + u3::kCampState, 3);
            store32(m, gp(-19860), task_of(kRoot));
            store32(m, work_of(kRoot) + u3::kRootSelection, static_cast<u32>(sel));
            pair(m, PAIR(fn_H_Camp_UpdateDrawTask_0011a050), Args{sx(task_of(kCampDraw)), 0, 0, 0}, rng(), "camp selection");
            ++runs;
        }
        for (u32 s = 0; s < 12; ++s) {
            random_world(m, rng);
            store32(m, work_of(kRoot) + u3::kRootState, s);
            pair(m, PAIR(fn_H_Camp_UpdateRootDrawTask_0011b420), Args{sx(task_of(kRoot)), 0, 0, 0}, rng(), "root state");
            ++runs;
        }
        for (u32 s = 0; s < 10; ++s) {
            random_world(m, rng);
            store32(m, work_of(kHudDraw) + u3::kHudState, s);
            pair(m, PAIR(fn_H_DayPartsDraw_UpdateTask_00183410), Args{sx(task_of(kHudDraw)), 0, 0, 0}, rng(), "hud state");
            ++runs;
        }
    }
    for (u32 cur = 0; cur < 19; ++cur)
        for (u32 screen = 0; screen < 19; ++screen) {
            random_world(m, rng);
            store32(m, work_of(kPcKani) + u3::kKaniScreen, cur);
            store32(m, work_of(kPersonaKani) + u3::kKaniScreen, cur);
            pair(m, PAIR(fn_sub_121DE0_00121de0), Args{sx(task_of(kPcKani)), sx(screen), 0, 0}, rng(), "pc kani sweep");
            pair(m, PAIR(fn_sub_122710_00122710), Args{sx(task_of(kPersonaKani)), sx(screen), 0, 0}, rng(), "persona kani sweep");
            runs += 2;
        }
    MESSAGE("sweeps: " << runs << " pairs");
}

TEST_CASE("game(ui3): the camp menu, the list, the portraits and the HUD follow the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xCA3Bu};

    // 1. The side portraits: the transition of every (current screen, new screen) pair equals the host decode of the
    //    ELF's jump tables, +12 becomes the new screen, $v0 = 1.
    int kani = 0;
    for (u32 cur = 0; cur < 18; ++cur)
        for (u32 screen = 0; screen < 18; ++screen)
            for (const auto& [role, table, exit_pc, fn, fr] :
                 {std::tuple{kPcKani, u3::kPcKaniOuterTable, 0x121FDCu, &recomp_gen::fn_sub_121DE0_00121de0, &recomp_gen::fn_sub_121DE0_00121de0__recomp},
                  std::tuple{kPersonaKani, u3::kPersonaKaniOuterTable, 0x12292Cu, &recomp_gen::fn_sub_122710_00122710, &recomp_gen::fn_sub_122710_00122710__recomp}}) {
                random_world(m, rng);
                const u32 w = work_of(role);
                store32(m, w + u3::kKaniScreen, cur);
                const u32 old_state = load32(m, w + u3::kKaniState);
                const int want = host_kani_state(m, table, exit_pc, screen, cur);
                REQUIRE(want != -2);
                const Run r = pair(m, fn, fr, Args{sx(task_of(role)), sx(screen), 0, 0}, rng(), "kani rule");
                INFO("cur " << cur << " screen " << screen);
                CHECK(v0_of(r) == 1);
                CHECK(load32(m, w + u3::kKaniScreen) == screen);
                CHECK(load32(m, w + u3::kKaniState) == (want >= 0 ? static_cast<u32>(want) : old_state));
                ++kani;
            }

    // 2. The camp root's selection (state 3): Skill 19, Item 17, Persona 11, Equip 5, Status 9, S.Link 13, System 15,
    //    cancel 4; the selection is remembered in gp-19884 (cancel / none leave it).
    const std::map<s32, u32> kNext = {{0, 19}, {1, 17}, {2, 11}, {3, 5}, {4, 9}, {5, 13}, {6, 15}, {-2, 4}};
    int selections = 0;
    for (int it = 0; it < 400; ++it) {
        random_world(m, rng);
        const s32 sel = static_cast<s32>(rng() % 10) - 3;
        store32(m, work_of(kCampDraw) + u3::kCampState, 3);
        store32(m, gp(-19860), task_of(kRoot));
        store32(m, work_of(kRoot) + u3::kRootSelection, static_cast<u32>(sel));
        store32(m, work_of(kFlash), 0);
        const u32 cursor = load32(m, gp(-19884));
        const Run r = pair(m, PAIR(fn_H_Camp_UpdateDrawTask_0011a050), Args{sx(task_of(kCampDraw)), 0, 0, 0}, rng(), "selection rule");
        CHECK(v0_of(r) == 0);
        const auto it2 = kNext.find(sel);
        const u32 want = it2 == kNext.end() ? 3u : it2->second;
        INFO("selection " << sel);
        CHECK(load32(m, work_of(kCampDraw) + u3::kCampState) == want);
        CHECK(load32(m, gp(-19884)) == (sel >= 0 && sel <= 6 ? static_cast<u32>(sel) : cursor));
        if (sel == -2) CHECK(load32(m, work_of(kRoot) + u3::kRootState) == 7);  // the list closes (sub_11B9B0)
        ++selections;
    }

    // 3. The list's input state: cancel -> -2 / confirm -> the cursor, both state 10; a move goes one step with the
    //    wrap-around 6 <-> 0 (only while the held / repeat-held word has the bit) and skips S.Link (5) in The Answer.
    int moves = 0, wraps = 0;
    for (int it = 0; it < 3000; ++it) {
        random_world(m, rng);
        const u32 w = work_of(kRoot);
        store32(m, w + u3::kRootState, 6);
        const u32 cursor = rng() % 7;
        store32(m, w + u3::kRootCursor, cursor);
        const u16 buttons = static_cast<u16>(pick(rng, {0u, 0u, 0u, 0x20u, 0x40u}));
        store16(m, u3::kPadButtons, buttons);
        const u32 input = load32(m, w + u3::kRootInput);
        const bool answer = load32(m, kScenario) != 0;
        const bool down = ((load16(m, u3::kPadPressed) | load16(m, u3::kPadRepeat)) & u3::kPadDown) != 0;
        const bool up = ((load16(m, u3::kPadPressed) | load16(m, u3::kPadRepeat)) & u3::kPadUp) != 0;
        const u16 held = static_cast<u16>(load16(m, u3::kPadHeld) | load16(m, u3::kPadRepeatHeld));
        pair(m, PAIR(fn_H_Camp_UpdateRootDrawTask_0011b420), Args{sx(task_of(kRoot)), 0, 0, 0}, rng(), "input rule");
        const u32 now = load32(m, w + u3::kRootCursor);
        if (buttons & 0x20) {
            CHECK(load32(m, w + u3::kRootSelection) == 0xFFFFFFFEu);
            CHECK(load32(m, w + u3::kRootState) == 10);
        } else if (buttons & 0x40) {
            CHECK(load32(m, w + u3::kRootSelection) == cursor);
            CHECK(load32(m, w + u3::kRootState) == 10);
        } else if (input == 0) {
            CHECK(now == cursor);
        } else if (down) {
            u32 want = cursor;
            if (cursor != 6) want = (answer && cursor + 1 == 5) ? 6 : cursor + 1;
            else if (held & u3::kPadDown) want = 0, ++wraps;
            INFO("down from " << cursor);
            CHECK(now == want);
            ++moves;
        } else if (up) {
            u32 want = cursor;
            if (cursor != 0) want = (answer && cursor - 1 == 5) ? 4 : cursor - 1;
            else if (held & u3::kPadUp) want = 6, ++wraps;
            INFO("up from " << cursor);
            CHECK(now == want);
            ++moves;
        } else {
            CHECK(now == cursor);
        }
    }

    // 4. The HUD slide: shown + flag 0x141D or 0x1407 -> hidden, target 400, 10 frames (9 after this frame's step);
    //    hidden + both clear -> shown, target 0. The x lands on gp-19704.
    int slides = 0;
    for (int it = 0; it < 600; ++it) {
        random_world(m, rng);
        const u32 w = work_of(kHudPos);
        const bool shown = load32(m, w + 32) != 0;
        const bool f1 = chance(rng, 50), f2 = chance(rng, 50);
        set_flag(m, 0x141D, f1);
        set_flag(m, 0x1407, f2);
        pair(m, PAIR(fn_H_DayPartsPos_UpdateTask_001832c0), Args{sx(task_of(kHudPos)), 0, 0, 0}, rng(), "slide rule");
        if (shown && (f1 || f2)) {
            CHECK(load32(m, w + 32) == 0);
            CHECK(loadf(m, w + 16) == 400.0f);
            CHECK(load32(m, w + 4) == 9);
            ++slides;
        } else if (!shown && !f1 && !f2) {
            CHECK(load32(m, w + 32) == 1);
            CHECK(loadf(m, w + 16) == 0.0f);
            CHECK(load32(m, w + 4) == 9);
            ++slides;
        }
        CHECK(load32(m, gp(-19704)) == load32(m, w + 8));
    }

    // 5. The HUD date: disabled -> dirty + state 2; flag 335 -> the current date shown at once; an unchanged date and
    //    day part -> state 2, visible; H_DayPartsDraw_SetDate always shows the current date (state 2).
    int dates = 0;
    for (int it = 0; it < 600; ++it) {
        random_world(m, rng);
        const u32 w = work_of(kHudDraw);
        const u32 enabled = pick(rng, {0u, 1u});
        const Run r = pair(m, PAIR(fn_sub_1848F0_001848f0), Args{sx(task_of(kHudDraw)), enabled, 0, 0}, rng(), "date rule");
        CHECK(load32(m, w + u3::kHudEnabled) == enabled);
        if (enabled == 0) {
            CHECK(load32(m, w + u3::kHudDirty) == 1);
            CHECK(load32(m, w + u3::kHudState) == 2);
        }
        const Run r2 = pair(m, PAIR(fn_H_DayPartsDraw_SetDate_00184c80), Args{sx(task_of(kHudDraw)), enabled, 0, 0}, rng(), "setdate rule");
        CHECK(load32(m, w + u3::kHudState) == 2);
        CHECK(load32(m, w + u3::kHudPart) == m.at(kTime)[0]);
        (void)r;
        (void)r2;
        ++dates;
    }
    MESSAGE("rules: " << kani << " portrait transitions, " << selections << " selections, " << moves << " cursor moves ("
                      << wraps << " wraps), " << slides << " HUD slides, " << dates << " HUD dates");
    CHECK(moves > 300);
    CHECK(wraps > 10);
    CHECK(slides > 100);
}

#else
TEST_CASE("game(ui3): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
