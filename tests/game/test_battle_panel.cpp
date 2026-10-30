// Phase 5 pair tests for slice battle_panel (game/src/battle/battle_panel.cpp): the 106 functions of pb_main.c /
// bp_root.c / bp_misc.c and the 2D sprite helpers against their recompiled bodies.
//
// Every pair runs the hand-written function and the __recomp body from the same guest state (the whole 32 MiB of main
// RAM is restored between them through a PairRange, write_tracker.h, and compared after both; the scratchpad too) and
// a random register file (GPRs in 128 bits, FPRs), and requires the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same $ra / $sp / arguments / everything), and the same stop;
//   * all of main RAM (the frames and spills below $sp included) and the scratchpad.
// The panel world: the "battle panel" task ($gp - 18956) with its work block (the mode word from the bits the panel
// functions test, +12 / +16, the tutorial id +0x33310), gBtl ($gp - 18692) with +12 flags and its four unit lists
// (+336 + 8k; units with +156 flags, +164 id, +168 slot, +2604 DatUnit, +2612 next), the main camera ($gp - 19504:
// +128 / +132), stand-in tasks for the callees' task slots ($gp - 18952 / -18924 / -18900 / -18892 / -18888), a sprite
// set (records of 44 bytes, page records with sizes, colour bytes) and the argument blocks (entry lists, a command
// record, a request record, float rects). The test build emits the small callees (tests/game/CMakeLists.txt: the
// persona list readers sub_17B500 / sub_17B5B0 / sub_17B660 / sub_17BE10 / sub_17C070 / sub_170710, the command
// menu's state readers, the dialog slot helpers, the battle check sub_289030); deeper callees are compared at their
// stop. Real game data: the same pairs on the battle snapshot b_5800 (extracted/_ours, where "battle panel" is live).
// Documented-rule checks (battle_panel.cpp's comments) on the host.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/battle_panel.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
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
#define P3FES_DECL_PAIR(name, addr8)      \
    void fn_##name##_##addr8(EEContext&); \
    void fn_##name##_##addr8##__recomp(EEContext&);
P3FES_BATTLE_PANEL_FUNCS(P3FES_DECL_PAIR)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

struct Func {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};
#define P3FES_F(name, addr8) Func{#name, 0x##addr8, &recomp_gen::fn_##name##_##addr8, &recomp_gen::fn_##name##_##addr8##__recomp},
const Func kFuncs[] = {P3FES_BATTLE_PANEL_FUNCS(P3FES_F)};
#undef P3FES_F

const Func& by_addr(u32 addr) {
    for (const Func& f : kFuncs)
        if (f.addr == addr) return f;
    FAIL("no function at " << hex64(addr));
    return kFuncs[0];
}

// --- guest helpers ---------------------------------------------------------------------------------------------
void st8(Machine& m, u32 va, u32 v) { m.at(va)[0] = static_cast<u8>(v); }
void st16(Machine& m, u32 va, u32 v) { const u16 x = static_cast<u16>(v); std::memcpy(m.at(va), &x, 2); }
void st32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void stf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
u32 ld32(const Machine& m, u32 va) { u32 v; std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4); return v; }
u16 ld16(const Machine& m, u32 va) { u16 v; std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 2); return v; }
float ldf(const Machine& m, u32 va) { float v; std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4); return v; }
u32 fbits(float f) { u32 v; std::memcpy(&v, &f, 4); return v; }

constexpr u32 kPanelTaskSlot = game::bpanel::kPanelTaskPtr;  // $gp - 18956
constexpr u32 kGBtlSlot = game::bpanel::kGBtlPtr;            // $gp - 18692
constexpr u32 kCameraSlot = 0x7CE0C0u;                       // $gp - 19504 (kwlnGetMainCamera sub_198590)
constexpr u32 kSkillSlot = 0x7CE3F8u;                        // $gp - 18680 (the table sub_17C070 reads)
constexpr u32 kCalleeTaskSlots[] = {0x7CE2E8u, 0x7CE304u, 0x7CE31Cu, 0x7CE324u, 0x7CE328u};  // $gp - 18952 ...

// --- the register file at a check point / the return / a stop ----------------------------------------------------
struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0;
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
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = c.fpr[i];
    return s;
}
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "gpr " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa || a.fcr31 != b.fcr31) return "sa/fcr31";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds), with a
// cycle budget (a callee walking a list the random world closed into a loop stops at the same check point in both).
constexpr u64 kBudget = 20'000'000;
constexpr std::size_t kMaxSnaps = 20'000;
class PanelHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    std::vector<Snap> snaps;
    std::size_t checks = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    Snap at_stop;
    int syscalls = 0;
    u64 limit = 0;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        if (snaps.size() < kMaxSnaps) snaps.push_back(snap(ctx));
        if (ctx.cycles > limit) fatal(ctx, 0xB0D6E7u, "cycle budget");
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* w) override {
        stopped = true;
        stop_pc = pc;
        what = w;
        what = what.substr(0, what.find("; host"));  // (the host return address differs between the bodies)
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, w, &ctx};
    }
};

struct Run {
    std::size_t checks = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
};

struct Regs {  // what a pair sets after the randomised context
    Args a{};
    bool set_f12 = false;
    u32 f12 = 0;
};

Run run_one(Machine& m, Fn fn, const Regs& in, u32 seed) {
    PanelHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(in.a, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();
    if (in.set_f12) m.ctx.fpr[12] = in.f12;
    h.limit = m.ctx.cycles + kBudget;
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    Run r;
    r.checks = h.checks;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.what = h.what;
    r.syscalls = h.syscalls;
    r.snaps = std::move(h.snaps);
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;
};

// --- the tester: the world, the arguments, a pair ------------------------------------------------------------------
struct Tester {
    std::unique_ptr<Machine> mp = std::make_unique<Machine>();
    Machine& m = *mp;
    std::mt19937 rng;
    std::map<std::string, Stats> stats;
    int pairs = 0;
    bool real = false;  // the world is a snapshot

    // The objects (synthetic world, or the snapshot's own where it has them).
    u32 work = 0x01400000u;      // panel work (0x34000)
    u32 task = 0x01440000u;      // the panel task
    u32 gbtl = 0x01440400u;      // gBtl (0xC00)
    std::vector<u32> units;      // btlUnits
    std::vector<u32> datunits;   // their DatUnits
    // argument blocks / the sprite world / the camera / the callee stand-ins (moved below the stack for snapshots)
    u32 misc = 0x0144C000u;
    u32 set = 0x0144A000u;       // sprite set: +4 the records, +8 the page table
    u32 sprites = 0x0144A100u;   // 16 records x 44
    u32 pagetbl = 0x0144A400u;   // 4 page pointers
    u32 pages = 0x0144A500u;     // 4 page records x 32
    u32 strip = 0x0144B000u;     // the 4-vertex strip
    u32 camera = 0x0144B200u;
    u32 fake = 0x0144D000u;      // stand-in tasks (5 x 0x100) and their work (5 x 0x400 at +0x800)
    u32 skill = 0x01450000u;     // the table behind $gp - 18680 (0x5000)
    u32 bcm = 0x01458000u;       // the command menu's work (0x7800)

    explicit Tester(u32 seed) : rng(seed) {}

    u32 r(u32 n) { return static_cast<u32>(rng() % n); }
    bool chance(u32 pct) { return r(100) < pct; }
    template <typename T, std::size_t N> u32 pick(const T (&v)[N]) { return static_cast<u32>(v[r(static_cast<u32>(N))]); }
    u64 value(u32 v) { return chance(25) ? ((static_cast<u64>(rng()) << 32) | v) : sx(v); }
    float rfloat() {
        if (chance(5)) {
            const u32 bits = static_cast<u32>(rng());
            float f;
            std::memcpy(&f, &bits, 4);
            return f;
        }
        return static_cast<float>(static_cast<s32>(r(4000)) - 2000) / static_cast<float>(1 + r(8));
    }

    const char* load() { return m.load_elf(elf_path()); }

    // The synthetic panel world on top of the loaded ELF.
    void new_world() {
        real = false;
        // panel task + work
        for (u32 va = work; va < work + 0x34000u; va += 4) st32(m, va, chance(60) ? 0 : static_cast<u32>(rng()));
        static constexpr u32 kBits[] = {0x4, 0x8, 0x10, 0x20, 0x100, 0x200, 0x400, 0x1000, 0x2000, 0x4000, 0x8000,
                                        0x10000, 0x20000, 0x40000};
        u32 mode = 0;
        for (u32 b : kBits)
            if (chance(30)) mode |= b;
        if (chance(10)) mode = static_cast<u32>(rng());
        st32(m, work + 0, mode);
        st32(m, work + 12, chance(80) ? r(3) : static_cast<u32>(rng()));
        st32(m, work + 16, static_cast<u32>(rng()));
        st32(m, work + 0x33310u, chance(50) ? r(40) : static_cast<u32>(rng()));
        for (u32 va = task; va < task + 0x100u; va += 4) st32(m, va, static_cast<u32>(rng()));
        st32(m, task + 60, work);
        st32(m, kPanelTaskSlot, task);
        // gBtl and the unit lists
        for (u32 va = gbtl; va < gbtl + 0xC00u; va += 4) st32(m, va, chance(50) ? 0 : static_cast<u32>(rng()));
        static constexpr u32 kFlags12[] = {0, 0x80, 0x800, 0x880};
        st32(m, gbtl + 12, (static_cast<u32>(rng()) & ~0x880u) | pick(kFlags12));
        units.clear();
        datunits.clear();
        const u32 n = 12;
        for (u32 k = 0; k < n; ++k) {
            const u32 u = 0x01441000u + 0xA40u * k, d = 0x01449000u + 0x40u * k;
            units.push_back(u);
            datunits.push_back(d);
            for (u32 va = u; va < u + 0xA40u; va += 4) st32(m, va, chance(70) ? 0 : static_cast<u32>(rng()));
            for (u32 va = d; va < d + 0x40u; va += 4) st32(m, va, static_cast<u32>(rng()));
            st32(m, u + 156, (static_cast<u32>(rng()) & ~8u) | (chance(65) ? 8u : 0u));
            st16(m, u + 164, chance(80) ? 1 + r(12) : static_cast<u32>(rng()));
            st32(m, u + 168, chance(85) ? r(8) : static_cast<u32>(rng()));
            st32(m, u + 2604, d);
            st16(m, d + 0, rng());
            st16(m, d + 2, chance(80) ? 1 + r(12) : static_cast<u32>(rng()));
            st8(m, d + 6, r(100));
        }
        std::vector<u32> order(n);
        for (u32 i = 0; i < n; ++i) order[i] = i;
        std::shuffle(order.begin(), order.end(), rng);
        u32 next = 0;
        for (u32 list = 0; list < 4; ++list) {
            const u32 len = list == 3 && next < n ? n - next : std::min(n - next, r(6));
            u32 prev = gbtl + 336 + 8 * list;
            for (u32 i = 0; i < len; ++i) {
                st32(m, prev, units[order[next]]);
                prev = units[order[next]] + 2612;
                ++next;
            }
            st32(m, prev, 0);
        }
        if (chance(3)) st32(m, kGBtlSlot, 0);
        else st32(m, kGBtlSlot, gbtl);
        common_objects();
    }

    // The objects both worlds get (in the snapshot they go below the stack, where the snapshot keeps nothing live).
    void common_objects() {
        // camera
        stf(m, camera + 128, chance(5) ? 0.0f : 0.1f + static_cast<float>(r(1000)));
        stf(m, camera + 132, 1000.0f + static_cast<float>(r(100000)));
        st32(m, kCameraSlot, camera);
        // callee stand-in tasks
        for (u32 i = 0; i < std::size(kCalleeTaskSlots); ++i) {
            const u32 t = fake + 0x100u * i, w = fake + 0x800u + 0x400u * i;
            for (u32 va = t; va < t + 0x100u; va += 4) st32(m, va, static_cast<u32>(rng()) & 0xFFFFu);
            for (u32 va = w; va < w + 0x400u; va += 4) st32(m, va, chance(50) ? 0 : static_cast<u32>(rng()) & 0xFFFFFu);
            st32(m, t + 60, w);
            if (!real || chance(30)) st32(m, kCalleeTaskSlots[i], chance(10) ? 0 : t);
        }
        // the command menu's work ($gp - 18952 is the work itself): +0 flags (0x2000000 / 0x4000000 read by sub_207F70 /
        // sub_207FC0), +36 the state sub_2054C0 returns, +30360 the index sub_205500 / sub_205550 / sub_2055A0 use
        if (!real || chance(30)) {
            for (u32 va = bcm; va < bcm + 0x7800u; va += 4) st32(m, va, static_cast<u32>(rng()) & 0xFFu);
            st32(m, bcm + 0, (static_cast<u32>(rng()) & ~0x6000000u) | (chance(15) ? 0x2000000u : 0u) | (chance(15) ? 0x4000000u : 0u));
            st32(m, bcm + 36, chance(90) ? r(8) : static_cast<u32>(rng()));
            st32(m, bcm + 30360, r(8));
            st32(m, kCalleeTaskSlots[0], chance(5) ? 0 : bcm);
        }
        if (!real) {
            for (u32 va = skill; va < skill + 0x5000u; va += 4) st32(m, va, static_cast<u32>(rng()));
            st32(m, kSkillSlot, skill);
        }
        // the sprite world
        st32(m, set + 4, sprites);
        st32(m, set + 8, pagetbl);
        for (u32 p = 0; p < 4; ++p) {
            const u32 pg = pages + 32 * p;
            st32(m, pagetbl + 4 * p, pg);
            st32(m, pg + 12, chance(5) ? 0 : 1u << (4 + r(6)));
            st32(m, pg + 16, chance(5) ? 0 : 1u << (4 + r(6)));
        }
        for (u32 k = 0; k < 16; ++k) {
            const u32 s = sprites + 44 * k;
            st32(m, s + 0, set);
            st32(m, s + 4, chance(80) ? r(4) : static_cast<u32>(rng()));
            st32(m, s + 8, r(4));
            st32(m, s + 12, r(512));
            st32(m, s + 16, r(512));
            st32(m, s + 20, r(512));
            st32(m, s + 24, r(512));
            for (u32 b = 28; b < 44; ++b) st8(m, s + b, chance(20) ? 0xFF : rng());
        }
        for (u32 va = strip; va < strip + 0x120u; va += 4) st32(m, va, static_cast<u32>(rng()));
        // argument blocks
        for (u32 va = misc; va < misc + 0x1000u; va += 4) st32(m, va, static_cast<u32>(rng()));
        for (u32 i = 0; i < 16; ++i) st16(m, misc + 2 * i, chance(70) ? r(64) : rng());           // u16 entry ids
        for (u32 i = 0; i < 16; ++i) st32(m, misc + 0x40 + 4 * i, chance(70) ? r(64) : static_cast<u32>(rng()));  // s32 ids
        st32(m, misc + 0x200 + 8, static_cast<u32>(rng()) & 0x7Fu);                               // request flags
        st16(m, misc + 0x200 + 16, chance(70) ? r(8) : rng());
        st32(m, misc + 0x200 + 20, r(4));
        for (u32 i = 0; i < 24; ++i) stf(m, misc + 0x400 + 4 * i, rfloat());                     // float rects
        for (u32 i = 0; i < 16; ++i) st8(m, misc + 0x500 + i, chance(20) ? 0xFF - r(2) : rng());  // colour bytes
        st8(m, misc + 0x600 + 6, r(100));                                                         // sub_1FC870's record
    }

    // The battle snapshot b_5800 as the world (false when absent): the panel task / gBtl / units are the game's own.
    bool snapshot_world(const std::vector<u8>& ram) {
        std::memcpy(m.mem.main_ram(), ram.data(), EEMemory::kMainRamSize);
        real = true;
        task = ld32(m, kPanelTaskSlot);
        gbtl = ld32(m, kGBtlSlot);
        if (task == 0 || gbtl == 0) return false;
        work = ld32(m, task + 60);
        units.clear();
        datunits.clear();
        for (u32 list = 0; list < 4; ++list)
            for (u32 u = ld32(m, gbtl + 336 + 8 * list), n = 0; u != 0 && n < 16; u = ld32(m, u + 2612), ++n) {
                units.push_back(u);
                if (const u32 d = ld32(m, u + 2604)) datunits.push_back(d);
            }
        if (datunits.empty()) datunits.push_back(units.empty() ? gbtl : units[0]);
        if (units.empty()) units.push_back(gbtl);
        // the synthetic blocks below the stack (0x1F60000.., unused at this frame)
        misc = 0x01F61000u;
        set = 0x01F62000u;
        sprites = 0x01F62100u;
        pagetbl = 0x01F62400u;
        pages = 0x01F62500u;
        strip = 0x01F63000u;
        camera = ld32(m, kCameraSlot) != 0 ? ld32(m, kCameraSlot) : 0x01F63200u;
        fake = 0x01F64000u;
        bcm = 0x01F68000u;
        const u32 cam = camera;
        common_objects();
        if (cam != 0x01F63200u) {  // keep the game's camera (common_objects wrote over its +128 / +132: put them back)
            std::memcpy(m.at(cam + 128), ram.data() + cam + 128, 8);
            st32(m, kCameraSlot, cam);
        }
        return true;
    }

    u32 any_unit() { return units[r(static_cast<u32>(units.size()))]; }
    u32 any_dat() { return datunits[r(static_cast<u32>(datunits.size()))]; }

    Regs regs_for(u32 addr) {
        Regs x;
        x.a = {value(static_cast<u32>(rng())), value(static_cast<u32>(rng())), value(r(8)), value(r(8))};
        switch (addr) {
        case 0x1FC720: x.a[0] = sx(any_dat()); break;
        case 0x1FC870: x.a = {sx(any_dat()), sx(chance(70) ? misc + 0x600 : any_dat()), 0, 0}; break;
        case 0x1FCCC0: x.a = {sx(any_dat()), sx(any_dat()), value(chance(70) ? r(64) : static_cast<u32>(rng())), 0}; break;
        case 0x1FCE20: x.a = {sx(any_dat()), sx(misc), sx(chance(10) ? 0 : chance(30) ? 1 : 2 + r(6)), 0}; break;
        case 0x1FD350: x.a = {sx(any_dat()), sx(misc + 0x40), sx(chance(10) ? 0 : chance(30) ? 1 : 2 + r(6)), 0}; break;
        case 0x1FD890: case 0x1FDAC0: x.a[0] = sx(task); break;
        case 0x1FDF10: x.a[0] = sx(misc + 0x100); break;
        case 0x1FE510: case 0x1FE580: case 0x1FEBF0: x.a[0] = value(static_cast<u32>(rng())); break;
        case 0x1FE650: x.a[0] = sx(misc + 0x200); break;
        case 0x1FE810: {
            static constexpr u32 kItems[] = {0xFFFFFFFFu, 335, 324, 0, 1, 336, 323};
            x.a[0] = chance(80) ? sx(pick(kItems)) : value(static_cast<u32>(rng()));
            break;
        }
        case 0x1FEF90: case 0x1FF160: x.a[0] = value(chance(85) ? r(11) : r(20)); break;
        case 0x1FF430: x.a[0] = value(chance(80) ? r(8) : static_cast<u32>(rng())); break;
        case 0x1FF500: x.a[0] = chance(80) ? sx(1 + r(12)) : value(r(0x10000)); break;
        case 0x1FF630: x.a[0] = chance(85) ? sx(r(6)) : value(static_cast<u32>(rng())); break;
        case 0x1FF7F0: x.a[0] = chance(80) ? sx(1 + r(12)) : value(r(0x10000)); break;
        case 0x21CCA0: x.a = {chance(15) ? 0 : sx(set), value(r(16)), 0, 0}; break;
        case 0x21CCE0: x.a[0] = sx(sprites + 44 * r(16)); break;
        case 0x21CD00: case 0x21CEC0: x.a = {sx(sprites + 44 * r(16)), sx(misc + 0x300), value(chance(85) ? r(8) : r(12)), 0}; break;
        case 0x21D3B0: x.a = {sx(strip), sx(sprites + 44 * r(16)), 0, 0}; break;
        case 0x21E380: x.a = {sx(strip), sx(sprites + 44 * r(16)), value(chance(85) ? r(8) : r(12)), 0}; break;
        case 0x21D890: case 0x21D8E0: case 0x21EAE0: case 0x21EB80: x.a = {sx(strip), sx(misc + 0x400 + 4 * r(8)), 0, 0}; break;
        case 0x21D950: case 0x21DD60: x.a = {sx(strip), sx(misc + 0x500), 0, 0}; break;
        case 0x21E170: x.a = {sx(strip), sx(misc + 0x400), sx(misc + 0x420), sx(misc + 0x440)}; break;
        case 0x21EA00: x.a[0] = value(chance(70) ? r(0x10000) : static_cast<u32>(rng())); break;
        case 0x21EAC0:
            x.a[0] = sx(strip);
            x.set_f12 = true;
            x.f12 = fbits(rfloat());
            break;
        default: break;
        }
        return x;
    }

    // One pair: both bodies from the same state; afterwards the recompiled run's memory is in place.
    Run pair(const Func& f, const Regs& in, const char* tag = nullptr) {
        ++pairs;
        const u32 seed = static_cast<u32>(rng());
        const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
        Run h, c;
        std::size_t first = 0, bfirst = 0;
        std::vector<u8> spr_hand;
        {
            PairRange big(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
            // the BIOS window: a random world's wild pointers reach it through the kseg mirrors (0xFFCBxxxx -> 0x1FCBxxxx;
            // sub_17B860, hand-written since sweep5c, writes there): restored for the second body and compared
            PairRange bios(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
            h = run_one(m, f.hand, in, seed);
            big.between();
            bios.between();
            spr_hand.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
            std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
            c = run_one(m, f.recomp, in, seed);
            first = big.first_difference();
            bfirst = bios.first_difference();
        }
        Stats& st = stats[f.name];
        ++st.pairs;
        if (c.stopped) {
            ++st.stops;
            ++st.stop_at[c.stop_pc];
        }
        INFO(std::string(f.name) << (tag ? std::string(" ") + tag : std::string()) << " a0=" << hex64(in.a[0]) << " a1="
                                 << hex64(in.a[1]) << " a2=" << hex64(in.a[2]) << " seed=" << seed);
        INFO("main RAM: first differing byte at " << hex64(first));
        CHECK(first == EEMemory::kMainRamSize);
        INFO("BIOS window: first differing byte at " << hex64(EEMemory::kBiosBase + bfirst));
        CHECK(bfirst == EEMemory::kBiosSize);
        const std::size_t sfirst = first_difference(spr_hand.data(), m.mem.scratchpad(), 0x4000);
        INFO("scratchpad: first differing byte at " << hex64(sfirst));
        CHECK(sfirst == 0x4000u);
        REQUIRE(h.stopped == c.stopped);
        CHECK(h.stop_pc == c.stop_pc);
        CHECK(h.what == c.what);
        CHECK(h.checks == c.checks);
        CHECK(h.syscalls == c.syscalls);
        const std::size_t n = std::min(h.snaps.size(), c.snaps.size());
        for (std::size_t i = 0; i < n; ++i) {
            const std::string d = diff(h.snaps[i], c.snaps[i]);
            if (!d.empty()) {
                INFO("check point " << i << " of " << n << ": " << d);
                CHECK(false);
                break;
            }
        }
        const std::string d = diff(h.end, c.end);
        INFO((c.stopped ? "at the stop " + hex64(c.stop_pc) + ": " : std::string("at the return: ")) << d);
        CHECK(d.empty());
        return c;
    }

    std::string summary() const {
        int p = 0, s = 0;
        for (const auto& [name, st] : stats) {
            p += st.pairs;
            s += st.stops;
        }
        return std::to_string(p) + " pairs, " + std::to_string(p - s) + " returned, " + std::to_string(s) + " at a compared stop";
    }
};

#define P3FES_BP_LOAD(t)                                                                                \
    Tester t(0xB9A7u);                                                                                  \
    if (const char* err = t.load()) {                                                                   \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)); \
        return;                                                                                         \
    }

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
s32 a_of(const Run& r, unsigned reg) { return static_cast<s32>(r.end.gpr[reg].u32[0]); }

}  // namespace

TEST_CASE("game(battle_panel): every function equals its recompiled body on random panel worlds") {
    P3FES_BP_LOAD(t)
#ifdef NDEBUG
    constexpr int kPairsPerFunc = 150;
#else
    constexpr int kPairsPerFunc = 50;
#endif
    std::string returned_never;
    for (const Func& f : kFuncs) {
        for (int i = 0; i < kPairsPerFunc; ++i) {
            if (i % 3 == 0) t.new_world();
            t.pair(f, t.regs_for(f.addr));
        }
        const Stats& st = t.stats[f.name];
        if (st.stops == st.pairs) {
            returned_never += std::string(" ") + f.name;
            for (const auto& [pc, k] : st.stop_at) returned_never += "@" + hex64(pc);
        }
    }
    MESSAGE("synthetic worlds: " << t.summary() << "; functions that always reach a callee not emitted here:" << returned_never);
}

TEST_CASE("game(battle_panel): the pairs on the battle snapshot b_5800 (the panel tasks are live there)") {
    P3FES_BP_LOAD(t)
    const std::filesystem::path path =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / "b_5800" / "eeMemory.bin";
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        MESSAGE("SKIP: extracted/_ours/b_5800/eeMemory.bin not found beside the ELF's tree");
        return;
    }
    std::vector<u8> ram((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    REQUIRE(ram.size() == EEMemory::kMainRamSize);
    REQUIRE(t.snapshot_world(ram));
    MESSAGE("b_5800: panel task " << hex64(t.task) << ", work " << hex64(t.work) << " (mode " << hex64(ld32(t.m, t.work))
                                  << "), gBtl " << hex64(t.gbtl) << ", " << t.units.size() << " units");
    for (const Func& f : kFuncs)
        for (int i = 0; i < 12; ++i) {
            if (i % 4 == 0) REQUIRE(t.snapshot_world(ram));
            t.pair(f, t.regs_for(f.addr), "b_5800");
        }
    // The unit-list searches over every unit of the snapshot.
    for (u32 u : t.units) {
        REQUIRE(t.snapshot_world(ram));
        t.pair(by_addr(0x1FF430), Regs{{sx(ld32(t.m, u + 168)), 0, 0, 0}}, "slot");
        t.pair(by_addr(0x1FF500), Regs{{sx(ld16(t.m, u + 164)), 0, 0, 0}}, "id");
        if (const u32 d = ld32(t.m, u + 2604)) t.pair(by_addr(0x1FF7F0), Regs{{sx(ld16(t.m, d + 2)), 0, 0, 0}}, "dat id");
    }
    MESSAGE("b_5800: " << t.summary());
}

TEST_CASE("game(battle_panel): documented rules (battle_panel.cpp)") {
    P3FES_BP_LOAD(t)
    Machine& m = t.m;
    auto fresh = [&] {
        t.new_world();
        st32(m, kGBtlSlot, t.gbtl);
    };
    // Lay out list 0 (gBtl +336) with the given units / on-field flags / ids / slots; the other lists empty.
    auto party = [&](std::initializer_list<std::array<u32, 3>> rows) {  // {on field, id, slot}
        u32 prev = t.gbtl + 336, k = 0;
        for (const auto& row : rows) {
            const u32 u = t.units[k++];
            st32(m, u + 156, row[0] ? 0x8u : 0x0u);
            st16(m, u + 164, row[1]);
            st32(m, u + 168, row[2]);
            st32(m, prev, u);
            prev = u + 2612;
        }
        st32(m, prev, 0);
        for (u32 l = 1; l < 4; ++l) st32(m, t.gbtl + 336 + 8 * l, 0);
    };
    // sub_1FF5B0: the units on the field; sub_1FF630: the id of the a0-th of them counted from the end.
    fresh();
    party({{1, 5, 0}, {0, 6, 1}, {1, 7, 2}, {1, 8, 3}});
    CHECK(v0_of(t.pair(by_addr(0x1FF5B0), Regs{})) == 3);
    fresh();
    party({{1, 5, 0}, {0, 6, 1}, {1, 7, 2}, {1, 8, 3}});
    CHECK(v0_of(t.pair(by_addr(0x1FF630), Regs{{0, 0, 0, 0}})) == 8);
    fresh();
    party({{1, 5, 0}, {0, 6, 1}, {1, 7, 2}, {1, 8, 3}});
    CHECK(v0_of(t.pair(by_addr(0x1FF630), Regs{{2, 0, 0, 0}})) == 5);
    // sub_1FF500: the unit with the id, skipping the one off the field; sub_1FF430: by slot.
    fresh();
    party({{0, 9, 4}, {1, 9, 5}});
    CHECK(v0_of(t.pair(by_addr(0x1FF500), Regs{{9, 0, 0, 0}})) == sx(t.units[1]));
    fresh();
    party({{0, 9, 4}, {1, 9, 5}});
    CHECK(v0_of(t.pair(by_addr(0x1FF430), Regs{{5, 0, 0, 0}})) == sx(t.units[1]));
    fresh();
    party({{0, 9, 4}, {1, 9, 5}});
    CHECK(v0_of(t.pair(by_addr(0x1FF430), Regs{{4, 0, 0, 0}})) == 0);  // off the field: not found (K_Assert, 0)
    // sub_1FF7F0: a unit on the field whose DatUnit id is a0.
    fresh();
    party({{1, 1, 0}});
    st16(m, ld32(m, t.units[0] + 2604) + 2, 77);
    CHECK(v0_of(t.pair(by_addr(0x1FF7F0), Regs{{77, 0, 0, 0}})) == 1);
    fresh();
    party({{0, 1, 0}});
    st16(m, ld32(m, t.units[0] + 2604) + 2, 77);
    CHECK(v0_of(t.pair(by_addr(0x1FF7F0), Regs{{77, 0, 0, 0}})) == 0);
    // The mode word: sub_1FE630 / sub_1FEB30 test 0x400 / 0x1000; sub_1FE510 sets 0x200 and +12; sub_1FDDF0.
    fresh();
    st32(m, t.work, 0x1404u);
    CHECK(v0_of(t.pair(by_addr(0x1FE630), Regs{})) == 0x400);
    CHECK(v0_of(t.pair(by_addr(0x1FEB30), Regs{})) == 0x1000);
    t.pair(by_addr(0x1FE510), Regs{{0x55, 0, 0, 0}});
    CHECK(ld32(m, t.work) == 0x1604u);
    CHECK(ld32(m, t.work + 12) == 0x55u);
    CHECK(v0_of(t.pair(by_addr(0x1FDDF0), Regs{})) == 1);  // 0x200 -> 1
    st32(m, t.work, 0x000Cu);
    CHECK(v0_of(t.pair(by_addr(0x1FDDF0), Regs{})) == 8);
    st32(m, t.work, 0x0004u);
    CHECK(v0_of(t.pair(by_addr(0x1FDDF0), Regs{})) == 0);
    // sub_1FDF10: the fixed command (0x200) with work +12 == 1 -> kind 4, flag 2, +10 = 324; 0x2000 -> kind 10.
    fresh();
    st32(m, t.work, 0x204u);
    st32(m, t.work + 12, 1);
    t.pair(by_addr(0x1FDF10), Regs{{sx(t.misc + 0x100), 0, 0, 0}});
    CHECK(ld32(m, t.misc + 0x100) == 2u);
    CHECK(ld32(m, t.misc + 0x104) == 4u);
    CHECK(ld16(m, t.misc + 0x10A) == 324u);
    st32(m, t.work, 0x2004u);
    st32(m, t.work + 16, 0xABCD);
    t.pair(by_addr(0x1FDF10), Regs{{sx(t.misc + 0x100), 0, 0, 0}});
    CHECK(ld32(m, t.misc + 0x104) == 10u);
    CHECK(ld32(m, t.misc + 0x110) == 0xABCDu);
    // sub_1FDF10 through the command menu's state: state 2 -> kind 3, +8 = sub_205550(); state 3 -> K_Assert (kind
    // stays 0); state 6 -> kind 7.
    {
        fresh();
        const u32 bcm = ld32(m, kCalleeTaskSlots[0]);
        REQUIRE(bcm != 0);
        st32(m, t.work, 0x4u);
        st32(m, bcm, 0);
        st32(m, bcm + 30360, 2);
        st16(m, bcm + 156 + 4, 0x1234);
        const std::pair<u32, u32> cases[] = {{2, 3}, {3, 0}, {6, 7}, {0, 1}, {4, 5}};
        for (const auto& [state, kind] : cases) {
            st32(m, bcm + 36, state);
            st32(m, t.misc + 0x104, 0);
            st16(m, t.misc + 0x108, 0);
            t.pair(by_addr(0x1FDF10), Regs{{sx(t.misc + 0x100), 0, 0, 0}});
            CHECK(ld32(m, t.misc + 0x104) == kind);
            if (state == 2) CHECK(ld16(m, t.misc + 0x108) == 0x1234u);
        }
    }
    // sub_1FEF90 / sub_1FF160: the message triple handed to sub_25BE60 (not emitted: compared at the stop, a0..a2).
    {
        // sub_25BE60 is hand-written since sweep5b: stood in as the stop it was when this build did not emit it
        StandIns si;
        si.install_stop(0x25BE60u, "sub_25BE60 (stop)");
        StandInsScope stand_ins{si};
        fresh();
        const Run r = t.pair(by_addr(0x1FEF90), Regs{{5, 0, 0, 0}});  // case 5 of the table 0x7B7250
        REQUIRE(r.stopped);
        CHECK(r.stop_pc == 0x25BE60u);
        CHECK(a_of(r, GPR_A0) == 237);
        CHECK(a_of(r, GPR_A1) == 238);
        CHECK(a_of(r, GPR_A2) == 239);
        const Run q = t.pair(by_addr(0x1FF160), Regs{{2, 0, 0, 0}});  // case 2 of 0x7B7280 (0, 1, 6: K_Assert)
        CHECK(a_of(q, GPR_A0) == 255);
        CHECK(a_of(q, GPR_A2) == 257);
    }
    // sub_21CCA0: set->records + 44 * a1, 0 for no set.
    fresh();
    CHECK(v0_of(t.pair(by_addr(0x21CCA0), Regs{{sx(t.set), 3, 0, 0}})) == sx(t.sprites + 44 * 3));
    CHECK(v0_of(t.pair(by_addr(0x21CCA0), Regs{{0, 3, 0, 0}})) == 0);
    // sub_21CD00: uv = texel rect / page size, unflipped.
    {
        fresh();
        const u32 s = t.sprites;
        st32(m, s + 4, 0);
        st32(m, s + 8, 1);
        st32(m, s + 12, 32);
        st32(m, s + 16, 16);
        st32(m, s + 20, 64);
        st32(m, s + 24, 8);
        const u32 pg = ld32(m, t.pagetbl + 4);
        st32(m, pg + 12, 128);
        st32(m, pg + 16, 64);
        t.pair(by_addr(0x21CD00), Regs{{sx(s), sx(t.misc + 0x300), 0, 0}});
        CHECK(ldf(m, t.misc + 0x300) == 0.5f);    // u0 = 64 / 128
        CHECK(ldf(m, t.misc + 0x308) == 0.75f);   // u1 = 96 / 128
        CHECK(ldf(m, t.misc + 0x304) == 0.125f);  // v0 = 8 / 64
        CHECK(ldf(m, t.misc + 0x30C) == 0.375f);  // v1 = 24 / 64
        st32(m, s + 4, 1);                        // u flipped
        t.pair(by_addr(0x21CD00), Regs{{sx(s), sx(t.misc + 0x300), 0, 0}});
        CHECK(ldf(m, t.misc + 0x300) == 0.75f);
        CHECK(ldf(m, t.misc + 0x308) == 0.5f);
    }
    // sub_21D8E0: the rect as the strip's corners.
    {
        fresh();
        const float rect[4] = {10.0f, 20.0f, 30.0f, 40.0f};
        for (u32 i = 0; i < 4; ++i) stf(m, t.misc + 0x400 + 4 * i, rect[i]);
        t.pair(by_addr(0x21D8E0), Regs{{sx(t.strip), sx(t.misc + 0x400), 0, 0}});
        CHECK(ldf(m, t.strip + 64) == 40.0f);
        CHECK(ldf(m, t.strip + 132) == 60.0f);
        CHECK(ldf(m, t.strip + 192) == 10.0f);
    }
    MESSAGE("rule pairs: " << t.summary());
}

#endif  // P3FES_GAME_HAVE_GENERATED
