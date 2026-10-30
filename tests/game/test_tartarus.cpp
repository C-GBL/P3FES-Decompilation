// Phase 5 pair tests for the Tartarus field band (game/src/field/tartarus_*.cpp): each hand-written function and the
// recompiled body it replaces run on identical guest machines, and EVERYTHING observable is compared:
//   * the whole register file (GPRs in 128 bits, HI/LO, SA, the FPRs, ACC, FCR31) and the cycle count at every check
//     point -- the function's own and those of the callees it reaches (a check point may preempt the thread, and the
//     kernel then stores the register file in guest memory) -- and at the return or stop;
//   * all 32 MiB of guest RAM (a PairRange, tests/game/write_tracker.h: only the pages written are copied) and the
//     scratchpad: the frames and spills on the dead stack, the work records, the units, the globals;
//   * the bus log length, syscall and trap counts.
// Callees that are kept recompiled but not emitted in this test build end the run through rt::missing_function: the
// hooks snapshot the register file at that call before the stop unwinds (memory stays as it was), so both bodies must
// reach the same callee with the same state. Inputs: randomised synthetic records in the test arena, plus the real
// Tartarus state of the battle route's snapshots (extracted/_ours/b_6700 and b_5800 beside the ELF's tree: the live
// "ene think proc" / "y_smap draw proc" / "y_staire_disp_proc" tasks and their works), with fields varied at random.
// The documented rules (game/include/p3fes/game/tartarus.h) are checked on the host, independently of both bodies.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/tartarus.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iterator>
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
P3FES_DECL_PAIR(fn_sub_429E80_00429e80)
P3FES_DECL_PAIR(fn_sub_429E90_00429e90)
P3FES_DECL_PAIR(fn_sub_429EF0_00429ef0)
P3FES_DECL_PAIR(fn_sub_429FE0_00429fe0)
P3FES_DECL_PAIR(fn_sub_42A230_0042a230)
P3FES_DECL_PAIR(fn_sub_42A310_0042a310)
P3FES_DECL_PAIR(fn_sub_42A0D0_0042a0d0)
P3FES_DECL_PAIR(fn_sub_42A180_0042a180)
P3FES_DECL_PAIR(fn_sub_42A3F0_0042a3f0)
P3FES_DECL_PAIR(fn_sub_42A4A0_0042a4a0)
P3FES_DECL_PAIR(fn_sub_42BA30_0042ba30)
P3FES_DECL_PAIR(fn_sub_430220_00430220)
P3FES_DECL_PAIR(fn_sub_430270_00430270)
P3FES_DECL_PAIR(fn_sub_4302A0_004302a0)
P3FES_DECL_PAIR(fn_sub_4311F0_004311f0)
P3FES_DECL_PAIR(fn_sub_42ADB0_0042adb0)
P3FES_DECL_PAIR(fn_sub_42B050_0042b050)
P3FES_DECL_PAIR(fn_sub_42B540_0042b540)
P3FES_DECL_PAIR(fn_sub_42FD80_0042fd80)
P3FES_DECL_PAIR(fn_Y_SMap_UpdateStaireDispTask_00430060)
P3FES_DECL_PAIR(fn_sub_430630_00430630)
P3FES_DECL_PAIR(fn_sub_430780_00430780)
P3FES_DECL_PAIR(fn_sub_430A40_00430a40)
P3FES_DECL_PAIR(fn_sub_42A550_0042a550)
P3FES_DECL_PAIR(fn_sub_42BA50_0042ba50)
P3FES_DECL_PAIR(fn_sub_42BC10_0042bc10)
P3FES_DECL_PAIR(fn_sub_42BD80_0042bd80)
P3FES_DECL_PAIR(fn_sub_42BFD0_0042bfd0)
P3FES_DECL_PAIR(fn_sub_42C0A0_0042c0a0)
P3FES_DECL_PAIR(fn_sub_42CD80_0042cd80)
P3FES_DECL_PAIR(fn_sub_42CFC0_0042cfc0)
P3FES_DECL_PAIR(fn_sub_42DD90_0042dd90)
P3FES_DECL_PAIR(fn_sub_42EA60_0042ea60)
P3FES_DECL_PAIR(fn_sub_42F440_0042f440)
P3FES_DECL_PAIR(fn_Y_SMap_UpdateSmapMaskDrawTask_00430bb0)
P3FES_DECL_PAIR(fn_Y_TimeLimit_UpdateTimeLimitDrawTask_0045a020)
P3FES_DECL_PAIR(fn_sub_447F90_00447f90)
P3FES_DECL_PAIR(fn_sub_449C90_00449c90)
P3FES_DECL_PAIR(fn_sub_449D10_00449d10)
P3FES_DECL_PAIR(fn_sub_44A240_0044a240)
P3FES_DECL_PAIR(fn_sub_44A330_0044a330)
P3FES_DECL_PAIR(fn_sub_44A630_0044a630)
P3FES_DECL_PAIR(fn_sub_448060_00448060)
P3FES_DECL_PAIR(fn_sub_448CF0_00448cf0)
P3FES_DECL_PAIR(fn_sub_449D60_00449d60)
P3FES_DECL_PAIR(fn_sub_449FE0_00449fe0)
P3FES_DECL_PAIR(fn_sub_44A110_0044a110)
P3FES_DECL_PAIR(fn_sub_44A420_0044a420)
P3FES_DECL_PAIR(fn_sub_44A790_0044a790)
P3FES_DECL_PAIR(fn_sub_44E530_0044e530)
P3FES_DECL_PAIR(fn_sub_44F060_0044f060)
P3FES_DECL_PAIR(fn_sub_44F120_0044f120)
P3FES_DECL_PAIR(fn_sub_44F170_0044f170)
P3FES_DECL_PAIR(fn_sub_44F1C0_0044f1c0)
P3FES_DECL_PAIR(fn_sub_44F270_0044f270)
P3FES_DECL_PAIR(fn_sub_4532D0_004532d0)
P3FES_DECL_PAIR(fn_sub_4533E0_004533e0)
P3FES_DECL_PAIR(fn_sub_453460_00453460)
P3FES_DECL_PAIR(fn_sub_453470_00453470)
P3FES_DECL_PAIR(fn_sub_453480_00453480)
P3FES_DECL_PAIR(fn_sub_453490_00453490)
P3FES_DECL_PAIR(fn_sub_4514A0_004514a0)
P3FES_DECL_PAIR(fn_sub_452010_00452010)
P3FES_DECL_PAIR(fn_sub_452F70_00452f70)
P3FES_DECL_PAIR(fn_sub_44DFC0_0044dfc0)
P3FES_DECL_PAIR(fn_sub_44E560_0044e560)
P3FES_DECL_PAIR(fn_sub_44F300_0044f300)
P3FES_DECL_PAIR(fn_sub_44FAB0_0044fab0)
P3FES_DECL_PAIR(fn_sub_44FFB0_0044ffb0)
P3FES_DECL_PAIR(fn_sub_4534B0_004534b0)
P3FES_DECL_PAIR(fn_sub_453ED0_00453ed0)
P3FES_DECL_PAIR(fn_sub_44B7D0_0044b7d0)
P3FES_DECL_PAIR(fn_sub_44D600_0044d600)
P3FES_DECL_PAIR(fn_sub_4501B0_004501b0)
P3FES_DECL_PAIR(fn_sub_450B30_00450b30)
P3FES_DECL_PAIR(fn_sub_44AF60_0044af60)
P3FES_DECL_PAIR(fn_sub_451D70_00451d70)
P3FES_DECL_PAIR(fn_sub_4523C0_004523c0)
P3FES_DECL_PAIR(fn_sub_452A70_00452a70)
P3FES_DECL_PAIR(fn_sub_454110_00454110)
P3FES_DECL_PAIR(fn_sub_44BEB0_0044beb0)
P3FES_DECL_PAIR(fn_Y_Stratum_UpdateEneThinkTask_0044aaf0)
P3FES_DECL_PAIR(fn_sub_453D90_00453d90)
P3FES_DECL_PAIR(fn_Y_Stratum_UpdateEneDeadEffectTask_004541f0)
P3FES_DECL_PAIR(fn_sub_4543C0_004543c0)
P3FES_DECL_PAIR(fn_sub_454400_00454400)
P3FES_DECL_PAIR(fn_sub_454520_00454520)
P3FES_DECL_PAIR(fn_sub_454620_00454620)
P3FES_DECL_PAIR(fn_sub_454A70_00454a70)
P3FES_DECL_PAIR(fn_sub_454D00_00454d00)
P3FES_DECL_PAIR(fn_sub_455B50_00455b50)
P3FES_DECL_PAIR(fn_sub_455CF0_00455cf0)
P3FES_DECL_PAIR(fn_sub_4561D0_004561d0)
P3FES_DECL_PAIR(fn_sub_4561F0_004561f0)
P3FES_DECL_PAIR(fn_sub_4563B0_004563b0)
P3FES_DECL_PAIR(fn_sub_4563C0_004563c0)
P3FES_DECL_PAIR(fn_sub_4563D0_004563d0)
P3FES_DECL_PAIR(fn_sub_456400_00456400)
P3FES_DECL_PAIR(fn_sub_456410_00456410)
P3FES_DECL_PAIR(fn_sub_456450_00456450)
P3FES_DECL_PAIR(fn_sub_456490_00456490)
P3FES_DECL_PAIR(fn_sub_4564E0_004564e0)
P3FES_DECL_PAIR(fn_sub_456530_00456530)
P3FES_DECL_PAIR(fn_sub_456580_00456580)
P3FES_DECL_PAIR(fn_sub_4565D0_004565d0)
P3FES_DECL_PAIR(fn_sub_456620_00456620)
P3FES_DECL_PAIR(fn_sub_457340_00457340)
P3FES_DECL_PAIR(fn_sub_457390_00457390)
P3FES_DECL_PAIR(fn_sub_4573D0_004573d0)
P3FES_DECL_PAIR(fn_sub_457410_00457410)
P3FES_DECL_PAIR(fn_sub_457470_00457470)
P3FES_DECL_PAIR(fn_sub_454F50_00454f50)
P3FES_DECL_PAIR(fn_sub_456EA0_00456ea0)
P3FES_DECL_PAIR(fn_sub_456670_00456670)
P3FES_DECL_PAIR(fn_sub_456A90_00456a90)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace tart = p3fes::game::tart;

#define LOAD_ELF_OR_SKIP(m)                                                                                 \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the whole register file -----------------------------------------------------------------------------------------
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
// "" when equal, else the first difference.
std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "GPR " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) +
                   " recomp " + hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "HI";
    if (!same_u128(a.lo, b.lo)) return "LO";
    if (a.sa != b.sa) return "SA";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "FPR " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.fcr31 != b.fcr31) return "FCR31: hand " + hex64(a.fcr31) + " recomp " + hex64(b.fcr31);
    if (a.acc != b.acc) return "ACC";
    if (a.cycles != b.cycles) return "cycles: hand " + std::to_string(a.cycles) + " recomp " + std::to_string(b.cycles);
    return "";
}

// Hooks: a register snapshot at every check point; rt::missing_function (a callee not emitted in this build) snapshots
// the register file at the call before it unwinds.
class FullHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    std::vector<Snap> snaps;
    int syscalls = 0, traps = 0;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap at_stop{};

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override { snaps.push_back(snap(ctx)); }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override {
        stopped = true;
        stop_pc = pc;
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
    void vu_control_write(EEContext&, u32, u32) override {}
};

struct Run {
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    Snap end{};
    std::size_t bus = 0;
    int syscalls = 0, traps = 0;
    std::vector<u8> spr;
    u64 v0() const { return end.gpr[GPR_V0].u64[0]; }
    u32 f0() const { return end.fpr[0]; }
};

// Run-time setup after the randomised context: float arguments, extra argument registers.
using Prep = std::function<void(EEContext&)>;

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const Prep& prep) {
    FullHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng() & 0xBF7FFFFFu;
    m.ctx.acc = rng() & 0xBF7FFFFFu;
    m.ctx.fcr31 = rng() & 0x00800000u;
    for (int i = 0; i < 2; ++i) {
        m.ctx.hi.u64[i] = (static_cast<u64>(rng()) << 32) | rng();
        m.ctx.lo.u64[i] = (static_cast<u64>(rng()) << 32) | rng();
    }
    if (prep) prep(m.ctx);
    Run r;
    try {
        fn(m.ctx);
        r.end = snap(m.ctx);
    } catch (const rt_test::FatalEvent&) {
        r.stopped = true;
        r.stop_pc = h.stop_pc;
        r.end = h.at_stop;
    }
    r.snaps = std::move(h.snaps);
    r.bus = h.bus_.log.size();
    r.syscalls = h.syscalls;
    r.traps = h.traps;
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    return r;
}

struct PairOut {
    Run hand, recomp;
};

int g_pairs = 0;
int g_stops = 0;

// One pair on the machine's current memory; afterwards the recompiled run's memory is in place.
PairOut pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const std::string& what, const Prep& prep = {}) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    PairOut p;
    p.hand = run_one(m, hand, args, seed, prep);
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    p.recomp = run_one(m, recomp, args, seed, prep);
    ++g_pairs;
    g_stops += p.recomp.stopped ? 1 : 0;
    INFO(what);
    CHECK(p.hand.stopped == p.recomp.stopped);
    CHECK(p.hand.stop_pc == p.recomp.stop_pc);
    CHECK(p.hand.snaps.size() == p.recomp.snaps.size());
    const std::size_t n = std::min(p.hand.snaps.size(), p.recomp.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        const std::string d = diff(p.hand.snaps[i], p.recomp.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << " of " << n << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = diff(p.hand.end, p.recomp.end);
        INFO("at the return / stop: " << d);
        CHECK(d.empty());
    }
    {
        const std::size_t first = ram.first_difference();
        INFO("RAM: first differing byte at " << hex64(first));
        CHECK(first == ram.size());
    }
    CHECK(p.hand.spr == p.recomp.spr);
    CHECK(p.hand.bus == p.recomp.bus);
    CHECK(p.hand.syscalls == p.recomp.syscalls);
    CHECK(p.hand.traps == p.recomp.traps);
    return p;
}

// --- fixtures ------------------------------------------------------------------------------------------------------
constexpr u32 gpva(s32 off) { return kGp + static_cast<u32>(off); }

constexpr u32 kTask = 0x01800000u;   // a kwln task record (+60 = the work)
constexpr u32 kWork = 0x01800400u;   // its work (0x1000 bytes)
constexpr u32 kObjs = 0x01804000u;   // objects, 0x200 bytes apart (up to 0x01810000)
constexpr u32 kBuf = 0x01812000u;    // argument buffers

void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void put8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void putf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
u32 get32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
float getf(const Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.mem.main_ram() + va, 4);
    return f;
}
void fill(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
void zero(Machine& m, u32 va, u32 len) { std::memset(m.at(va), 0, len); }
u32 obj(int i) { return kObjs + 0x200u * static_cast<u32>(i); }
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
float bitsf(u32 v) {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

// A task record with a random work.
void make_task(Machine& m, std::mt19937& rng, u32 task = kTask, u32 work = kWork) {
    zero(m, task, 0x68);
    put32(m, task + 60, work);
    fill(m, work, 0x1000, rng);
}
// 64-bit argument registers: sign-extended words, or a value with stray upper bits (the whole-register tests).
u64 arg64(std::mt19937& rng, u32 low) { return rng() % 4 == 0 ? (static_cast<u64>(rng()) << 32) | low : sx(low); }
// A finite float of moderate size (sometimes 0 / negative / large).
float rfloat(std::mt19937& rng) {
    switch (rng() % 5) {
    case 0: return 0.0f;
    case 1: return static_cast<float>(rng() % 256);
    case 2: return -static_cast<float>(rng() % 1000) / 7.0f;
    default: return static_cast<float>(static_cast<s32>(rng() % 200000) - 100000) / 64.0f;
    }
}
// A world coordinate inside the 16 x 16 grid of 800-unit cells (sometimes just outside).
float rcoord(std::mt19937& rng) { return static_cast<float>(static_cast<s32>(rng() % 14000) - 600) + static_cast<float>(rng() % 64) / 64.0f; }
Prep fargs(std::initializer_list<std::pair<unsigned, float>> regs) {
    std::vector<std::pair<unsigned, float>> v(regs);
    return [v](EEContext& c) {
        for (auto [r, f] : v) c.fpr[r] = fbits(f);
    };
}

// --- the battle route's snapshots ---------------------------------------------------------------------------------------
std::vector<u8> tart_snapshot(const char* dir) {  // (the test's own reader, apart from stand_ins.h's read_snapshot)
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}
// Loads a snapshot's RAM over the machine (false: absent, the test skips that part).
bool load_snapshot(Machine& m, const char* dir) {
    const std::vector<u8> v = tart_snapshot(dir);
    if (v.empty()) {
        MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
        return false;
    }
    std::memcpy(m.mem.main_ram(), v.data(), v.size());
    return true;
}
// The kwln tasks (0x68-byte records) whose update callback (+0x34) is `update`, by a scan of RAM for records with a
// printable name whose byte sum matches +0x18 and a work pointer (+0x3C) in RAM.
std::vector<u32> tasks_with_update(const Machine& m, u32 update) {
    std::vector<u32> out;
    const u8* ram = m.mem.main_ram();
    for (u32 va = 0x100000u; va + 0x68 < EEMemory::kMainRamSize; va += 4) {
        if (get32(m, va + 0x34) != update) continue;
        const u32 work = get32(m, va + 0x3C);
        if (work == 0 || work >= EEMemory::kMainRamSize) continue;
        s32 sum = 0;
        int n = 0;
        while (n < 24 && ram[va + n] >= 0x20 && ram[va + n] < 0x7F) sum += static_cast<s8>(ram[va + n++]);
        if (n < 3 || ram[va + n] != 0 || static_cast<s32>(get32(m, va + 0x18)) != sum) continue;
        out.push_back(va);
    }
    return out;
}

// ======================================================================================================================
// The mini-map's leaves
// ======================================================================================================================

TEST_CASE("game(tartarus): the mini-map / stair icon setters equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A001u};
    for (int i = 0; i < 48; ++i) {
        make_task(m, rng);
        const u64 v = arg64(rng, rng() % 3 == 0 ? rng() % 3 : rng());
        pair(m, PAIR(fn_sub_429E80_00429e80), Args{sx(kTask), v, 0, 0}, rng(), "sub_429E80");
        pair(m, PAIR(fn_sub_4302A0_004302a0), Args{sx(kTask), 0, 0, 0}, rng(), "sub_4302A0");
        const u64 xy = (static_cast<u64>(fbits(rfloat(rng))) << 32) | fbits(rfloat(rng));
        const PairOut p = pair(m, PAIR(fn_sub_430220_00430220), Args{sx(kTask), xy, 0, 0}, rng(), "sub_430220");
        // the documented rule: (s16) x, (s16) y, shown = 1
        CHECK(static_cast<s16>(get32(m, kWork) & 0xFFFF) == static_cast<s16>(static_cast<s32>(bitsf(static_cast<u32>(xy)))));
        CHECK(m.at(kWork)[tart::kStairShown] == 1);
        (void)p;
        pair(m, PAIR(fn_sub_430270_00430270), Args{sx(kBuf), sx(kTask), 0, 0}, rng(), "sub_430270");
        CHECK(std::memcmp(m.at(kBuf), m.at(kWork + tart::kStairRect), 16) == 0);
        // the lock flag: 1 and other values
        put8(m, gpva(tart::kGpSmapLock), static_cast<u8>(i % 3 == 0 ? 1 : rng()));
        const PairOut q = pair(m, PAIR(fn_sub_42BA30_0042ba30), Args{}, rng(), "sub_42BA30");
        CHECK(q.hand.v0() == (static_cast<s8>(*m.at(gpva(tart::kGpSmapLock))) == 1 ? 1u : 0u));
        // cell -> world: (x, z) unsigned, negative halves included
        const u64 x = i % 4 == 0 ? (static_cast<u64>(rng()) << 32 | 0x80000000u | rng()) : rng() % 16;
        const u64 z = i % 5 == 0 ? sx(0x80000000u | rng()) : rng() % 16;
        pair(m, PAIR(fn_sub_4311F0_004311f0), Args{sx(kBuf), x, z, 0}, rng(), "sub_4311F0");
        if (x < 16 && z < 16) {
            CHECK(getf(m, kBuf) == 800.0f * static_cast<float>(x));
            CHECK(get32(m, kBuf + 4) == 0u);
            CHECK(getf(m, kBuf + 8) == 800.0f * static_cast<float>(z));
        }
    }
}

// The cell-offset functions on positions and units: synthetic positions, then the snapshot's units.
TEST_CASE("game(tartarus): the mini-map cell offsets equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A002u};
    struct Pos {
        Fn hand, recomp;
        const char* name;
        bool z;
    };
    const Pos pos[] = {{PAIR(fn_sub_42A0D0_0042a0d0), "sub_42A0D0", false},
                       {PAIR(fn_sub_42A180_0042a180), "sub_42A180", true},
                       {PAIR(fn_sub_42A3F0_0042a3f0), "sub_42A3F0", false},
                       {PAIR(fn_sub_42A4A0_0042a4a0), "sub_42A4A0", true}};
    for (int i = 0; i < 40; ++i) {
        const float p[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
        std::memcpy(m.at(kBuf), p, 12);
        const float size = i % 3 == 0 ? 63.0f : static_cast<float>(rng() % 200) / 4.0f;
        for (const Pos& f : pos) pair(m, f.hand, f.recomp, Args{sx(kBuf), 0, 0, 0}, rng(), f.name, fargs({{12, size}}));
    }
    struct Unit {
        Fn hand, recomp;
        const char* name;
        int count;
    };
    const Unit units[] = {{PAIR(fn_sub_429EF0_00429ef0), "sub_429EF0", 4},
                          {PAIR(fn_sub_429FE0_00429fe0), "sub_429FE0", 4},
                          {PAIR(fn_sub_42A230_0042a230), "sub_42A230", 24},
                          {PAIR(fn_sub_42A310_0042a310), "sub_42A310", 24}};
    for (const char* dir : {"b_6700", "b_5800"}) {
        if (!load_snapshot(m, dir)) continue;
        for (const Unit& u : units)
            for (int i = 0; i < u.count; ++i) {
                const u32 unit = (u.count == 4 ? tart::kFldUnitsPc : tart::kFldUnitsEc) + tart::kFldUnitSize * i;
                if (get32(m, unit + tart::kUnitUsed) == 0 || get32(m, unit + tart::kUnitSceneRes) == 0) continue;
                pair(m, u.hand, u.recomp, Args{arg64(rng, static_cast<u32>(i)), 0, 0, 0}, rng(), std::string(u.name) + " " + dir,
                     fargs({{12, i % 2 ? 63.0f : 17.5f}}));
            }
        // the frozen centre from the player's controller
        make_task(m, rng);
        pair(m, PAIR(fn_sub_429E90_00429e90), Args{sx(kTask), arg64(rng, rng() % 2), 0, 0}, rng(), std::string("sub_429E90 ") + dir);
    }
}

// The map's drawing helpers on the live "y_smap draw proc" task of b_6700 (its work, the floor layout, the units): the
// centre frozen or not, units switched off at random so the loops run past the skipped ones, the layer count varied.
// sprCreateHandle allocates through the RW heap hook and is not emitted here: a drawn mark ends the run there.
TEST_CASE("game(tartarus): the mini-map drawing helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A003u};
    if (load_snapshot(m, "b_6700")) {
        const std::vector<u32> smap = tasks_with_update(m, 0x4281F0u);
        REQUIRE(!smap.empty());
        const u32 task = smap[0];
        const u32 work = get32(m, task + tart::kTaskWork);
        const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        for (int i = 0; i < 24; ++i) {
            std::memcpy(m.mem.main_ram(), base.data(), base.size());
            if (i % 2) put8(m, work + tart::kSmapFrozen, 1);
            if (i % 3 == 1) put8(m, work + 2858, static_cast<u8>(rng() % 4));
            if (i % 4 == 2) putf(m, work + tart::kSmapFrozenPos, rcoord(rng));
            pair(m, PAIR(fn_sub_42ADB0_0042adb0), Args{sx(task), 0, 0, 0}, rng(), "sub_42ADB0");
            // the marks: some or all units off
            for (int u = 0; u < 28; ++u) {
                const u32 unit = (u < 24 ? tart::kFldUnitsEc + tart::kFldUnitSize * u : tart::kFldUnitsPc + tart::kFldUnitSize * (u - 24));
                if (i >= 8 || rng() % 3 == 0) put32(m, unit + (rng() % 2 ? tart::kUnitUsed : tart::kUnitSceneRes), 0);
            }
            pair(m, PAIR(fn_sub_42B050_0042b050), Args{sx(task), 0, 0, 0}, rng(), "sub_42B050");
            pair(m, PAIR(fn_sub_42B540_0042b540), Args{sx(task), 0, 0, 0}, rng(), "sub_42B540");
        }
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        // the stair finder on the live grid, then on grids with stair cells / open sides at random
        for (int i = 0; i < 16; ++i) {
            if (i > 0) {
                for (int c = 0; c < 256; ++c) {
                    const u32 cell = 0x869F60u + 72 + 16 * c;
                    put8(m, cell + 2, static_cast<u8>(rng() % 6 == 0 ? 8 : rng() % 10));
                    put8(m, cell + 1, static_cast<u8>(rng() % 2));
                    put8(m, cell + 11, static_cast<u8>(i < 6 ? 0 : rng()));
                }
            }
            pair(m, PAIR(fn_sub_42FD80_0042fd80), Args{sx(kBuf), sx(task), 0, 0}, rng(), "sub_42FD80");
        }
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        // the stair icon (live task), the frame handles, the pulse
        for (const u32 st : tasks_with_update(m, 0x430060u)) {
            put8(m, get32(m, st + tart::kTaskWork) + tart::kStairShown, 0);
            pair(m, PAIR(fn_Y_SMap_UpdateStaireDispTask_00430060), Args{sx(st), 0, 0, 0}, rng(), "Y_SMap_UpdateStaireDispTask hidden");
            put8(m, get32(m, st + tart::kTaskWork) + tart::kStairShown, 1);
            pair(m, PAIR(fn_Y_SMap_UpdateStaireDispTask_00430060), Args{sx(st), 0, 0, 0}, rng(), "Y_SMap_UpdateStaireDispTask shown");
        }
        pair(m, PAIR(fn_sub_430630_00430630), Args{sx(task), 0, 0, 0}, rng(), "sub_430630");
        for (int i = 0; i < 6; ++i) {
            const u64 off = (static_cast<u64>(fbits(rfloat(rng))) << 32) | fbits(rfloat(rng));
            pair(m, PAIR(fn_sub_430780_00430780), Args{off, sx(rng() % 640), sx(rng() % 448), sx(rng() % 4000)}, rng(),
                 "sub_430780");
        }
    }
    // the sparkle seeds: a synthetic field root work (sField +24 -> a task)
    Machine n;
    LOAD_ELF_OR_SKIP(n);
    for (int i = 0; i < 24; ++i) {
        make_task(n, rng);
        put32(n, 0x869F60u + 24, kTask);
        pair(n, PAIR(fn_sub_430A40_00430a40), Args{arg64(rng, rng() % 6), 0, 0, 0}, rng(), "sub_430A40");
    }
}

// The set-up / seen-grid functions on b_6700's live map work and units: the seen grid, the two flags gp-0x4628 /
// gp-0x462C and the grid's room bytes varied; the task creators they reach (heap) end the runs there.
TEST_CASE("game(tartarus): the mini-map set-up and seen-grid functions equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A004u};
    if (!load_snapshot(m, "b_6700")) return;
    const std::vector<u32> smap = tasks_with_update(m, 0x4281F0u);
    REQUIRE(!smap.empty());
    const u32 task = smap[0];
    const u32 work = get32(m, task + tart::kTaskWork);
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    for (int i = 0; i < 64; ++i) {
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        if (i % 2) fill(m, 0x95C100u, 0x40, rng);
        for (int c = 0; c < 256; ++c)
            if (rng() % 4 == 0) put8(m, 0x95C110u + c, static_cast<u8>(rng() % 3));
        put8(m, gpva(-17960), static_cast<u8>(rng() % 3 == 0));
        put8(m, gpva(-17964), static_cast<u8>(rng() % 3 == 0));
        if (i % 4 == 3) {
            put8(m, work + 2824, static_cast<u8>(rng() % 16));
            put8(m, work + 2825, static_cast<u8>(rng() % 16));
            put8(m, work + 2827, static_cast<u8>(rng() % 16));
            put8(m, work + 2828, static_cast<u8>(rng() % 16));
        }
        if (i % 3 == 2)
            for (int c = 0; c < 256; ++c) put8(m, 0x869F60u + 72 + 16 * c + 11, static_cast<u8>(rng()));
        const u64 pc = arg64(rng, static_cast<u32>(i % 5 == 0 ? 0 : rng() % 4));
        const u64 x = arg64(rng, rng() % 16), z = arg64(rng, rng() % 16);
        pair(m, PAIR(fn_sub_42A550_0042a550), Args{sx(task), pc, x, z}, rng(), "sub_42A550");
    }
    for (int i = 0; i < 12; ++i) {
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        if (i % 3 == 1) put8(m, work + 2858, static_cast<u8>(rng() % 3));
        if (i % 2) put32(m, 0x8717E8u, 0);
        if (i % 4 == 2) put32(m, 0x8717F4u, 0);
        pair(m, PAIR(fn_sub_42BA50_0042ba50), Args{sx(task), 0, 0, 0}, rng(), "sub_42BA50");
        pair(m, PAIR(fn_sub_42BC10_0042bc10), Args{sx(task), 0, 0, 0}, rng(), "sub_42BC10");
        pair(m, PAIR(fn_sub_42BFD0_0042bfd0), Args{sx(task), 0, 0, 0}, rng(), "sub_42BFD0");
        // room cells: none, or a few (+0 / +1 == 1) of kinds below / above 5
        for (int c = 0; c < 256; ++c) {
            const u32 cell = 0x869F60u + 72 + 16 * c;
            const bool room = i > 0 && rng() % 64 == 0;
            put8(m, cell + 0, room ? 1 : static_cast<u8>(rng() % 2 ? 0 : 2));
            put8(m, cell + 1, room ? 1 : static_cast<u8>(rng() % 2));
            put8(m, cell + 2, static_cast<u8>(rng() % 9));
        }
        pair(m, PAIR(fn_sub_42BD80_0042bd80), Args{sx(task), 0, 0, 0}, rng(), "sub_42BD80");
    }
}

// The grid cell a field unit's collision controller is in (controller work +44 / +48, K_FldFrame_CtlGetXGrid / ZGrid).
std::pair<s32, s32> unit_cell(const Machine& m, u32 unit) {
    const u32 res = get32(m, unit + tart::kUnitSceneRes);
    if (res == 0 || res >= EEMemory::kMainRamSize) return {-1, -1};
    const u32 ctl = get32(m, res + tart::kResController);
    if (ctl == 0 || ctl >= EEMemory::kMainRamSize) return {-1, -1};
    const u32 w = get32(m, ctl + tart::kTaskWork);
    if (w == 0 || w >= EEMemory::kMainRamSize) return {-1, -1};
    return {static_cast<s32>(get32(m, w + 44)), static_cast<s32>(get32(m, w + 48))};
}

// The per-cell mark drawers on b_6700 (the live map work, units, objects): each unit / object on its own cell (and a
// wrong cell), the centre frozen or not, the seen grid and the status words varied. A drawn mark ends at
// sprCreateHandle (heap); the placement and the skip paths before it are compared.
TEST_CASE("game(tartarus): the mini-map mark drawers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A005u};
    if (!load_snapshot(m, "b_6700")) return;
    const std::vector<u32> smap = tasks_with_update(m, 0x4281F0u);
    REQUIRE(!smap.empty());
    const u32 task = smap[0];
    const u32 work = get32(m, task + tart::kTaskWork);
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto vary = [&](int i) {
        std::memcpy(m.mem.main_ram(), base.data(), base.size());
        put8(m, work + tart::kSmapFrozen, static_cast<u8>(i % 2));
        if (i % 3 == 2) put8(m, work + 2857, static_cast<u8>(4 + rng() % 24));
        for (int c = 0; c < 256; ++c)
            if (rng() % 3 == 0) put8(m, 0x95C110u + c, static_cast<u8>(rng() % 2));
    };
    for (int i = 0; i < 16; ++i) {
        vary(i);
        for (int pc = 0; pc < 4; ++pc) {
            auto [x, z] = unit_cell(m, tart::kFldUnitsPc + tart::kFldUnitSize * pc);
            if (i % 4 == 3) x += 1;
            const u64 ox = sx(static_cast<u32>(static_cast<s32>(rng() % 5) - 2));
            const u64 oz = sx(static_cast<u32>(static_cast<s32>(rng() % 5) - 2));
            const Prep prep = [ox, oz](EEContext& c) {
                c.gpr[8].u64[0] = ox;
                c.gpr[9].u64[0] = oz;
            };
            pair(m, PAIR(fn_sub_42C0A0_0042c0a0), Args{sx(task), arg64(rng, pc), sx(x), sx(z)}, rng(), "sub_42C0A0", prep);
        }
        for (int e = 0; e < 24; e += 1 + static_cast<int>(rng() % 4)) {
            auto [x, z] = unit_cell(m, tart::kFldUnitsEc + tart::kFldUnitSize * e);
            if (x < 0) continue;
            const u64 oz = sx(static_cast<u32>(static_cast<s32>(rng() % 3) - 1));
            const Prep prep = [oz](EEContext& c) { c.gpr[8].u64[0] = oz; };
            pair(m, PAIR(fn_sub_42CFC0_0042cfc0), Args{sx(task), sx(x), sx(z), sx(rng() % 3)}, rng(), "sub_42CFC0", prep);
        }
        // the objects / chests / exit on their cells
        for (int k = 0; k < 8; ++k) {
            const u32 rec = 0x86BE00u + 16 * k;
            if (i % 4 == 1) put32(m, rec, rng() % 6);
            const s32 x = static_cast<s32>((getf(m, rec + 4) + 400.0f) / 800.0f);
            const s32 z = static_cast<s32>((getf(m, rec + 12) + 400.0f) / 800.0f);
            pair(m, PAIR(fn_sub_42DD90_0042dd90), Args{sx(task), sx(x), sx(z), sx(rng() % 3)}, rng(), "sub_42DD90");
        }
        for (int k = 0; k < 32; k += 1 + static_cast<int>(rng() % 6)) {
            const u32 rec = 0x86BE80u + 312 * k;
            if (i % 4 == 2) put32(m, rec, rng() % 2);
            const s32 x = static_cast<s32>((getf(m, rec + 268) + 400.0f) / 800.0f);
            const s32 z = static_cast<s32>((getf(m, rec + 276) + 400.0f) / 800.0f);
            pair(m, PAIR(fn_sub_42EA60_0042ea60), Args{sx(task), sx(x), sx(z), sx(rng() % 3)}, rng(), "sub_42EA60");
        }
        put32(m, 0x86E580u, i % 3 ? 1u : 0u);
        const s32 ex = static_cast<s32>((getf(m, 0x86E684u) + 400.0f) / 800.0f);
        const s32 ez = static_cast<s32>((getf(m, 0x86E68Cu) + 400.0f) / 800.0f);
        pair(m, PAIR(fn_sub_42F440_0042f440), Args{sx(task), sx(ex), sx(ez + (i % 5 == 4)), sx(rng() % 3)}, rng(),
             "sub_42F440");
        // the sparkles of flagged members
        for (int k = 0; k < 3; ++k) put8(m, work + 2360 + k, static_cast<u8>(rng() % 2));
        for (int k = 0; k < 15; ++k) {
            put8(m, work + 2279 + k, static_cast<u8>(rng() % 3));
            put8(m, work + 2264 + k, static_cast<u8>(18 + rng() % 4));
        }
        pair(m, PAIR(fn_sub_42CD80_0042cd80), Args{sx(task), 0, 0, 0}, rng(), "sub_42CD80");
    }
    // the mask task (live) in its states, the time-limit states on a synthetic work
    std::memcpy(m.mem.main_ram(), base.data(), base.size());
    for (const u32 mt : tasks_with_update(m, 0x430BB0u)) {
        const u32 mw = get32(m, mt + tart::kTaskWork);
        for (int s = 0; s < 4; ++s) {
            put8(m, mw, static_cast<u8>(s));
            put8(m, mw + 125, static_cast<u8>(s % 2));
            pair(m, PAIR(fn_Y_SMap_UpdateSmapMaskDrawTask_00430bb0), Args{sx(mt), 0, 0, 0}, rng(), "Y_SMap_UpdateSmapMaskDrawTask");
        }
    }
    for (int i = 0; i < 40; ++i) {
        make_task(m, rng);
        put8(m, kWork + 93, static_cast<u8>(i % 9 == 0));
        put8(m, kWork + 4, static_cast<u8>(i % 9));
        put8(m, kWork + 5, static_cast<u8>(rng() % 2));
        put16(m, kWork + 6, static_cast<u16>(rng() % 12));
        put16(m, kWork + 68, static_cast<u16>(rng() % 12));
        put32(m, kWork, get32(m, gpva(tart::kGpSmapSprite)));
        pair(m, PAIR(fn_Y_TimeLimit_UpdateTimeLimitDrawTask_0045a020), Args{sx(kTask), 0, 0, 0}, rng(), "Y_TimeLimit_UpdateTimeLimitDrawTask");
    }
}

// ======================================================================================================================
// The stratum title's helpers (synthetic: the stratum parts work, the stratum record at *(gp-0x4604))
// ======================================================================================================================

constexpr u32 kRecord = 0x01814000u;  // the stratum record (0x200 bytes)
constexpr u32 kVerts = 0x01816000u;   // an Im2D vertex array

// A stratum parts work whose pointer slots all name dummy handles in kObjs, and a record of n entries {s8 block,
// s16 floor}, the current block / floor one of them (or not).
void make_stratum(Machine& m, std::mt19937& rng, int n, bool current_listed) {
    make_task(m, rng);
    for (u32 off = 0; off < 0x1000; off += 4) put32(m, kWork + off, obj(static_cast<int>(rng() % 48)));
    fill(m, kObjs, 0xC000, rng);
    zero(m, kRecord, 0x200);
    put32(m, gpva(tart::kGpStratum), kRecord);
    for (int i = 0; i < n; ++i) {
        put8(m, kRecord + 4 + 4 * i, static_cast<u8>(1 + rng() % 6));
        put16(m, kRecord + 6 + 4 * i, static_cast<u16>(rng() % 260));
    }
    put8(m, kRecord + 160, static_cast<u8>(n));
    const int cur = n ? static_cast<int>(rng() % n) : 0;
    put16(m, kRecord + 162, current_listed && n ? static_cast<u16>(get32(m, kRecord + 6 + 4 * cur) & 0xFFFF) : 0xFFFF);
    put8(m, kRecord + 164, current_listed && n ? *m.at(kRecord + 4 + 4 * cur) : 0xFF);
    for (int b = 0; b < 8; ++b) {
        put16(m, kRecord + 124 + 6 * b, static_cast<u16>(rng() % 20));
        put8(m, kRecord + 166 + b, static_cast<u8>(rng() % 3));
    }
    put8(m, kWork + 2366, static_cast<u8>(n ? rng() % n : 0));
    put8(m, kWork + 2367, static_cast<u8>(n));
    put8(m, kWork + 2368, static_cast<u8>(n + (rng() % 2 ? 0 : rng() % 4)));
    put8(m, kWork + 2369, 0);
    put8(m, kWork + 595, static_cast<u8>(rng() % 8));
    put8(m, kWork + 1179, static_cast<u8>(rng() % 7));
    put8(m, kWork + 1180, static_cast<u8>(rng() % 200));
    for (int k = 0; k < 4; ++k) put16(m, kWork + 2388 + 2 * k, static_cast<u16>(rng() % 26));
    put16(m, kWork + 238, static_cast<u16>(rng() % 12));
    put16(m, kWork + 244, static_cast<u16>(rng() % 12));
}

TEST_CASE("game(tartarus): the stratum title's helpers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A006u};
    for (int it = 0; it < 48; ++it) {
        const int n = 1 + static_cast<int>(rng() % 12);
        make_stratum(m, rng, n, it % 4 != 3);
        const u64 i = arg64(rng, static_cast<u32>(rng() % n));
        pair(m, PAIR(fn_sub_447F90_00447f90), Args{sx(kBuf), sx(kTask), i, 0}, rng(), "sub_447F90");
        if (it % 3 == 0) {  // an entry from the title table
            const u32 t = get32(m, 0x6B4650u + 4 * (rng() % 30));
            put32(m, kRecord + 4 + 4 * static_cast<u32>(i & 0xFF), t);
        }
        const PairOut q = pair(m, PAIR(fn_sub_449C90_00449c90), Args{sx(kTask), i, 0, 0}, rng(), "sub_449C90");
        {  // the documented rule: the first matching record of the 30 at 0x6B4650, -1 when none
            const u32 e = get32(m, kRecord + 4 + 4 * static_cast<u32>(i & 0xFF));
            s64 want = -1;
            for (int k = 0; k < 30 && want < 0; ++k) {
                const u32 t = get32(m, 0x6B4650u + 4 * k);
                if (static_cast<s8>(t & 0xFF) == static_cast<s8>(e & 0xFF) && static_cast<s16>(t >> 16) == static_cast<s16>(e >> 16))
                    want = k;
            }
            CHECK(static_cast<s64>(q.hand.v0()) == want);
        }
        pair(m, PAIR(fn_sub_449D10_00449d10), Args{sx(kTask), 0, 0, 0}, rng(), "sub_449D10");
        pair(m, PAIR(fn_sub_44A630_0044a630), Args{sx(kTask), 0, 0, 0}, rng(), "sub_44A630");
        const Prep f = fargs({{13, rfloat(rng)}, {15, 3.0f}, {21, static_cast<float>(rng() % 256)}, {23, rfloat(rng)}});
        pair(m, PAIR(fn_sub_44A240_0044a240), Args{sx(kTask), arg64(rng, rng() % 60), 0, 0}, rng(), "sub_44A240", f);
        pair(m, PAIR(fn_sub_44A330_0044a330), Args{sx(kTask), arg64(rng, rng() % 60), 0, 0}, rng(), "sub_44A330", f);
        const u64 xy = (static_cast<u64>(fbits(rfloat(rng))) << 32) | fbits(rfloat(rng));
        const u64 floor = rng() % 3 == 0 ? (get32(m, kRecord + 162) & 0xFFFF) : rng() % 300;
        const u64 block = rng() % 3 == 0 ? *m.at(kRecord + 164) : rng() % 7;
        const u64 active = rng() % 2, alpha = rng() % 256;
        const u64 entry = rng() % 2 ? *m.at(kWork + 2366) : rng() % 8;
        const Prep p5 = [active, alpha](EEContext& c) {
            c.gpr[9].u64[0] = active;
            c.gpr[10].u64[0] = alpha;
        };
        pair(m, PAIR(fn_sub_448060_00448060), Args{sx(kTask), entry, xy, block}, rng(), "sub_448060",
             [floor, p5](EEContext& c) { c.gpr[8].u64[0] = floor; p5(c); });
        pair(m, PAIR(fn_sub_448CF0_00448cf0), Args{sx(kTask), entry, xy, block}, rng(), "sub_448CF0",
             [floor, p5](EEContext& c) { c.gpr[8].u64[0] = floor; p5(c); });
        // the cursor walk ends on an entry of the current floor: entry 0 (always reached after a wrap), or a random one
        // of the list when the walk can reach it (fewer than 7 entries: plain wrap)
        if (it % 2 || *m.at(kWork + 2368) >= 7) put16(m, kRecord + 162, static_cast<u16>(get32(m, kRecord + 6) & 0xFFFF));
        pair(m, PAIR(fn_sub_449D60_00449d60), Args{sx(kTask), 0, 0, 0}, rng(), "sub_449D60");
        const Prep slide = fargs({{12, rfloat(rng)}, {13, rfloat(rng)}, {14, rfloat(rng)}, {15, rfloat(rng)}});
        pair(m, PAIR(fn_sub_449FE0_00449fe0), Args{sx(kTask), sx(rng() % 3 ? rng() % 16 : 0), 0, 0}, rng(), "sub_449FE0", slide);
        pair(m, PAIR(fn_sub_44A110_0044a110), Args{sx(kTask), sx(rng() % 3 ? rng() % 16 : 0), 0, 0}, rng(), "sub_44A110", slide);
        pair(m, PAIR(fn_sub_44A420_0044a420), Args{sx(kTask), sx(rng() % 8), sx(rng() % 24), 0}, rng(), "sub_44A420");
        // the wobble vertex: rec {**verts, f32 x, f32 y, -> {+1152 s32 phase}, index}
        put32(m, kBuf, kBuf + 0x40);
        put32(m, kBuf + 0x40, kVerts);
        putf(m, kBuf + 4, static_cast<float>(rng() % 1000) / 1000.0f);
        putf(m, kBuf + 8, static_cast<float>(rng() % 1000) / 1000.0f);
        put32(m, kBuf + 12, obj(1));
        put32(m, obj(1) + 1152, rng() % 360);
        put32(m, kBuf + 16, rng() % 32);
        pair(m, PAIR(fn_sub_44A790_0044a790), Args{sx(kBuf), 0, 0, 0}, rng(), "sub_44A790");
    }
}

// ======================================================================================================================
// The shadows' think code
// ======================================================================================================================

// Every used shadow index of the snapshot in memory.
std::vector<int> used_shadows(const Machine& m) {
    std::vector<int> out;
    for (int i = 0; i < 24; ++i) {
        const u32 u = tart::kFldUnitsEc + tart::kFldUnitSize * i;
        if (get32(m, u + tart::kUnitUsed) && get32(m, u + tart::kUnitSceneRes)) out.push_back(i);
    }
    return out;
}

TEST_CASE("game(tartarus): the think leaves equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A007u};
    for (int i = 0; i < 64; ++i) {
        const float p[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
        const float q[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
        std::memcpy(m.at(kBuf), p, 12);
        std::memcpy(m.at(kBuf + 16), q, 12);
        const PairOut x = pair(m, PAIR(fn_sub_44F120_0044f120), Args{sx(kBuf), 0, 0, 0}, rng(), "sub_44F120");
        CHECK(static_cast<s32>(x.hand.v0()) == static_cast<s32>((p[0] + 400.0f) / 800.0f));
        const PairOut z = pair(m, PAIR(fn_sub_44F170_0044f170), Args{sx(kBuf), 0, 0, 0}, rng(), "sub_44F170");
        CHECK(static_cast<s32>(z.hand.v0()) == static_cast<s32>((p[2] + 400.0f) / 800.0f));
        const float d = static_cast<float>(rng() % 9000);
        pair(m, PAIR(fn_sub_44F1C0_0044f1c0), Args{sx(kBuf), sx(kBuf + 16), 0, 0}, rng(), "sub_44F1C0", fargs({{12, d}}));
        pair(m, PAIR(fn_sub_44F270_0044f270), Args{sx(kBuf), sx(kBuf + 16), 0, 0}, rng(), "sub_44F270");
        make_task(m, rng);
        fill(m, obj(0), 0x200, rng);
        put32(m, obj(0) + 364, kTask);
        pair(m, PAIR(fn_sub_44E530_0044e530), Args{sx(obj(0)), arg64(rng, rng() % 9), 0, 0}, rng(), "sub_44E530");
        pair(m, PAIR(fn_sub_453490_00453490), Args{sx(kTask), 0, 0, 0}, rng(), "sub_453490");
        put32(m, gpva(-17916), rng());
        pair(m, PAIR(fn_sub_453460_00453460), Args{}, rng(), "sub_453460");
        pair(m, PAIR(fn_sub_453470_00453470), Args{arg64(rng, rng()), 0, 0, 0}, rng(), "sub_453470");
        pair(m, PAIR(fn_sub_453480_00453480), Args{}, rng(), "sub_453480");
    }
    for (const char* dir : {"b_6700", "b_5800"}) {
        if (!load_snapshot(m, dir)) continue;
        const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        const std::vector<u32> thinks = tasks_with_update(m, 0x44AAF0u);
        for (int i = 0; i < 12; ++i) {
            std::memcpy(m.mem.main_ram(), base.data(), base.size());
            if (i % 3 == 2)
                for (int c = 0; c < 256; ++c) put8(m, 0x869F60u + 72 + 16 * c + 11, static_cast<u8>(rng()));
            pair(m, PAIR(fn_sub_4532D0_004532d0), Args{arg64(rng, rng() % 2), 0, 0, 0}, rng(), std::string("sub_4532D0 ") + dir);
            pair(m, PAIR(fn_sub_4533E0_004533e0), Args{arg64(rng, rng() % 3), 0, 0, 0}, rng(), std::string("sub_4533E0 ") + dir);
            for (const u32 t : thinks) {
                const float p[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
                std::memcpy(m.at(kBuf), p, 12);
                pair(m, PAIR(fn_sub_44F060_0044f060), Args{sx(t), sx(kBuf), 0, 0}, rng(), "sub_44F060",
                     fargs({{12, static_cast<float>(rng() % 8000)}}));
                pair(m, PAIR(fn_sub_452F70_00452f70), Args{sx(kBuf + 64), sx(t), 0, 0}, rng(), "sub_452F70");
            }
            for (const int e : used_shadows(m))
                pair(m, PAIR(fn_sub_4514A0_004514a0), Args{arg64(rng, static_cast<u32>(e)), 0, 0, 0}, rng(), "sub_4514A0");
            const float p[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
            std::memcpy(m.at(kBuf), p, 12);
            pair(m, PAIR(fn_sub_452010_00452010), Args{sx(kBuf), 0, 0, 0}, rng(), std::string("sub_452010 ") + dir);
        }
    }
}

// The think tasks of a snapshot with their works varied: state / step bytes, the target member, the flags.
struct ThinkWorld {
    std::vector<u8> base;
    std::vector<u32> tasks;
};
bool think_world(Machine& m, const char* dir, ThinkWorld& w) {
    if (!load_snapshot(m, dir)) return false;
    w.base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    w.tasks = tasks_with_update(m, 0x44AAF0u);
    return !w.tasks.empty();
}
void vary_think(Machine& m, std::mt19937& rng, u32 task, int i) {
    const u32 w = get32(m, task + tart::kTaskWork);
    if (i % 2) put8(m, w + 65, static_cast<u8>(rng() % 2));
    if (i % 3 == 1) put8(m, w + 24, static_cast<u8>(rng() % 4));
    if (i % 4 == 2) put8(m, w + 5, static_cast<u8>(rng() % 4));
    if (i % 5 == 3) put8(m, gpva(-17972), static_cast<u8>(rng() % 2));
    if (i % 6 == 4) {
        const u32 unit = tart::kFldUnitsEc + tart::kFldUnitSize * static_cast<s8>(*m.at(w + 1));
        put32(m, unit + 396, rng() % 5);
    }
    if (i % 7 == 5) put32(m, w + 12, 0);
}

TEST_CASE("game(tartarus): the think checks and the contact state equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A008u};
    for (const char* dir : {"b_6700", "b_5800"}) {
        ThinkWorld w;
        if (!think_world(m, dir, w)) continue;
        for (int i = 0; i < 24; ++i) {
            for (const u32 t : w.tasks) {
                std::memcpy(m.mem.main_ram(), w.base.data(), w.base.size());
                vary_think(m, rng, t, i);
                const std::string tag = std::string(" ") + dir;
                pair(m, PAIR(fn_sub_44DFC0_0044dfc0), Args{sx(t), 0, 0, 0}, rng(), "sub_44DFC0" + tag);
                pair(m, PAIR(fn_sub_44E560_0044e560), Args{sx(t), 0, 0, 0}, rng(), "sub_44E560" + tag);
                pair(m, PAIR(fn_sub_44FAB0_0044fab0), Args{sx(t), 0, 0, 0}, rng(), "sub_44FAB0" + tag);
                pair(m, PAIR(fn_sub_44FFB0_0044ffb0), Args{sx(t), 0, 0, 0}, rng(), "sub_44FFB0" + tag);
                const u32 wk = get32(m, t + tart::kTaskWork);
                const u64 ec = static_cast<u64>(static_cast<s64>(static_cast<s8>(*m.at(wk + 1))));
                pair(m, PAIR(fn_sub_44F300_0044f300), Args{ec, 0, 0, 0}, rng(), "sub_44F300" + tag);
                // the path expansion: random own / target cells, some records filled
                put8(m, wk + 120, static_cast<u8>(i % 8 == 0 ? 0 : rng() % 16));
                put8(m, wk + 121, static_cast<u8>(i % 8 == 0 ? 0 : rng() % 16));
                put8(m, wk + 139, static_cast<u8>(rng() % 16));
                put8(m, wk + 140, static_cast<u8>(rng() % 16));
                for (int c = 0; c < 256; ++c)
                    if (rng() % 4 == 0) put32(m, wk + 152 + 8 * c, 0); else if (rng() % 8 == 0) put32(m, wk + 152 + 8 * c, rng());
                put32(m, wk + 148, rng() % 8);
                pair(m, PAIR(fn_sub_4534B0_004534b0), Args{ec, 0, 0, 0}, rng(), "sub_4534B0" + tag);
            }
        }
    }
}

// printf (0x5225A8) is hand-written since finalB (game/src/fx/finalB.cpp): its forwarder runs the body -- vfprintf into
// the stdout FILE, which waits on the IOP without end -- where the think-state pairs ended at it as at a function this
// build does not emit (an endless walk grew `snaps` until the host ran out of memory). The stop keeps the stop: both
// runs end at the call and are compared there (StandIns::install_stop). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas) si.install_stop(va, "stopped at, as when it was not emitted");
        scope = std::make_unique<StandInsScope>(si);
    }
};

// The think states on the snapshots' live think tasks: every state / sub-state value, the targets and counters varied.
TEST_CASE("game(tartarus): the think states equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    std::mt19937 rng{0x7A55A009u};
    for (const char* dir : {"b_6700", "b_5800"}) {
        ThinkWorld w;
        if (!think_world(m, dir, w)) continue;
        for (int i = 0; i < 26; ++i) {
            for (const u32 t : w.tasks) {
                std::memcpy(m.mem.main_ram(), w.base.data(), w.base.size());
                vary_think(m, rng, t, i);
                const u32 wk = get32(m, t + tart::kTaskWork);
                const u64 ec = static_cast<u64>(static_cast<s64>(static_cast<s8>(*m.at(wk + 1))));
                put8(m, wk + 3, static_cast<u8>(i));
                put8(m, wk + 4, static_cast<u8>(i % 10));
                put8(m, wk + 7, static_cast<u8>(rng() % 3));
                put8(m, wk + 8, static_cast<u8>(rng() % 3));
                put32(m, wk + 148, rng() % 4);
                put8(m, wk + 139, static_cast<u8>(i % 4 == 0 ? 0 : rng() % 16));
                put8(m, wk + 140, static_cast<u8>(i % 4 == 0 ? 0 : rng() % 16));
                const std::string tag = std::string(" ") + dir + " sub-state " + std::to_string(i);
                for (int st = 3; st <= 6; ++st) {  // (each pair leaves the recompiled run's memory: the next starts from it)
                        put8(m, wk + 2, static_cast<u8>(st));
                    put8(m, wk + 64, static_cast<u8>(i % 9 == 8));
                    pair(m, PAIR(fn_Y_Stratum_UpdateEneThinkTask_0044aaf0), Args{sx(t), 0, 0, 0}, rng(), "Y_Stratum_UpdateEneThinkTask" + tag);
                        put8(m, wk + 2, static_cast<u8>(st));
                    pair(m, PAIR(fn_sub_454110_00454110), Args{sx(t), 0, 0, 0}, rng(), "sub_454110" + tag);
                }
                pair(m, PAIR(fn_sub_44AF60_0044af60), Args{sx(t), 0, 0, 0}, rng(), "sub_44AF60" + tag);
                pair(m, PAIR(fn_sub_44BEB0_0044beb0), Args{sx(t), 0, 0, 0}, rng(), "sub_44BEB0" + tag);
                pair(m, PAIR(fn_sub_44B7D0_0044b7d0), Args{sx(t), 0, 0, 0}, rng(), "sub_44B7D0" + tag);
                pair(m, PAIR(fn_sub_44D600_0044d600), Args{sx(t), 0, 0, 0}, rng(), "sub_44D600" + tag);
                pair(m, PAIR(fn_sub_4501B0_004501b0), Args{ec, 0, 0, 0}, rng(), "sub_4501B0" + tag);
                pair(m, PAIR(fn_sub_450B30_00450b30), Args{ec, 0, 0, 0}, rng(), "sub_450B30" + tag);
                pair(m, PAIR(fn_sub_451D70_00451d70), Args{sx(t), 0, 0, 0}, rng(), "sub_451D70" + tag);
                pair(m, PAIR(fn_sub_4523C0_004523c0), Args{sx(t), ec, 0, 0}, rng(), "sub_4523C0" + tag);
                pair(m, PAIR(fn_sub_452A70_00452a70), Args{ec, sx(rng() % 4), 0, 0}, rng(), "sub_452A70" + tag);
                const float p[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
                std::memcpy(m.at(kBuf), p, 12);
                const u64 tx = rng() % 16, tz = i % 5 == 0 ? *m.at(wk + 93) : rng() % 16;
                const u64 x = i % 5 == 0 ? tx : rng() % 16;
                const Prep pp = [tx, tz](EEContext& c) {
                    c.gpr[8].u64[0] = tx;
                    c.gpr[9].u64[0] = tz;
                };
                pair(m, PAIR(fn_sub_453ED0_00453ed0), Args{ec, x, i % 5 == 0 ? tz : rng() % 16, sx(kBuf)}, rng(),
                     "sub_453ED0" + tag, pp);
            }
        }
    }
}

// ======================================================================================================================
// The movement helpers, status bytes, symbol marker, party switches / skills and the Kyoto NPC helpers
// ======================================================================================================================

TEST_CASE("game(tartarus): the movement helpers and the status bytes equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7A55A00Au};
    for (const char* dir : {"b_6700", "b_5800"}) {
        ThinkWorld w;
        if (!think_world(m, dir, w)) continue;
        for (int i = 0; i < 16; ++i) {
            for (const u32 t : w.tasks) {
                std::memcpy(m.mem.main_ram(), w.base.data(), w.base.size());
                vary_think(m, rng, t, i);
                const u32 wk = get32(m, t + tart::kTaskWork);
                const u64 ec = static_cast<u64>(static_cast<s64>(static_cast<s8>(*m.at(wk + 1))));
                const std::string tag = std::string(" ") + dir;
                const float p[3] = {rcoord(rng), rfloat(rng), rcoord(rng)};
                std::memcpy(m.at(kBuf), p, 12);
                pair(m, PAIR(fn_sub_4543C0_004543c0), Args{ec, arg64(rng, rng() % 7), 0, 0}, rng(), "sub_4543C0" + tag);
                pair(m, PAIR(fn_sub_454400_00454400), Args{sx(kBuf), ec, 0, 0}, rng(), "sub_454400" + tag);
                pair(m, PAIR(fn_sub_454520_00454520), Args{sx(kBuf), ec, 0, 0}, rng(), "sub_454520" + tag);
                pair(m, PAIR(fn_sub_454620_00454620), Args{ec, 0, 0, 0}, rng(), "sub_454620" + tag);
                pair(m, PAIR(fn_sub_454A70_00454a70), Args{ec, sx(kBuf), 0, 0}, rng(), "sub_454A70" + tag);
                pair(m, PAIR(fn_sub_454D00_00454d00), Args{sx(kBuf), 0, 0, 0}, rng(), "sub_454D00" + tag);
                pair(m, PAIR(fn_sub_454F50_00454f50), Args{ec, sx(rng() % 4), 0, 0}, rng(), "sub_454F50" + tag);
                // a path: records chained from the target back to the start (or broken, the 100-round cap)
                const int sx0 = static_cast<int>(rng() % 16), sz0 = static_cast<int>(rng() % 16);
                int cx = sx0, cz = sz0;
                put8(m, wk + 141, static_cast<u8>(sx0));
                put8(m, wk + 142, static_cast<u8>(sz0));
                const int len = 1 + static_cast<int>(rng() % 12);
                for (int k = 0; k < len; ++k) {
                    const int nx = std::min(15, cx + static_cast<int>(rng() % 2)), nz = std::min(15, cz + 1);
                    const u32 rec = wk + 152 + 8 * static_cast<u32>(nx + 16 * nz);
                    put16(m, rec + 0, static_cast<u16>(nx));
                    put16(m, rec + 2, static_cast<u16>(nz));
                    put16(m, rec + 4, static_cast<u16>(cx));
                    put16(m, rec + 6, static_cast<u16>(i % 5 == 4 ? (cz + 7) & 15 : cz));
                    cx = nx;
                    cz = nz;
                }
                put8(m, wk + 139, static_cast<u8>(cx));
                put8(m, wk + 140, static_cast<u8>(cz));
                pair(m, PAIR(fn_sub_453D90_00453d90), Args{ec, 0, 0, 0}, rng(), "sub_453D90" + tag);
            }
            pair(m, PAIR(fn_sub_455B50_00455b50), Args{}, rng(), std::string("sub_455B50 ") + dir);
            pair(m, PAIR(fn_sub_455CF0_00455cf0), Args{}, rng(), std::string("sub_455CF0 ") + dir);
        }
        // the symbol-direction marker (live task)
        for (const u32 st : tasks_with_update(m, 0x455E00u)) {
            for (int i = 0; i < 8; ++i) {
                const Prep f = fargs({{12, rfloat(rng)}, {13, rfloat(rng)}});
                pair(m, PAIR(fn_sub_4561D0_004561d0), Args{sx(st), 0, 0, 0}, rng(), "sub_4561D0", f);
                pair(m, PAIR(fn_sub_4563B0_004563b0), Args{sx(st), 0, 0, 0}, rng(), "sub_4563B0", f);
                pair(m, PAIR(fn_sub_4561F0_004561f0), Args{sx(st), 0, 0, 0}, rng(), "sub_4561F0");
            }
        }
    }
    // synthetic: the dead effect, the marker setters, the party switches and skill state, the NPC slots
    Machine n;
    LOAD_ELF_OR_SKIP(n);
    for (int i = 0; i < 40; ++i) {
        make_task(n, rng);
        put8(n, kWork, static_cast<u8>(i % 3));
        pair(n, PAIR(fn_Y_Stratum_UpdateEneDeadEffectTask_004541f0), Args{sx(kTask), 0, 0, 0}, rng(), "Y_Stratum_UpdateEneDeadEffectTask");
        pair(n, PAIR(fn_sub_4563C0_004563c0), Args{sx(kTask), arg64(rng, rng()), 0, 0}, rng(), "sub_4563C0");
        pair(n, PAIR(fn_sub_4563D0_004563d0), Args{sx(kTask), (static_cast<u64>(rng()) << 32) | rng(), 0, 0}, rng(), "sub_4563D0");
        pair(n, PAIR(fn_sub_456400_00456400), Args{sx(kTask), arg64(rng, rng()), 0, 0}, rng(), "sub_456400");
        const int pc = static_cast<int>(rng() % 4);
        put32(n, tart::kFldUnitsPc + tart::kFldUnitSize * pc + 364, kTask);
        struct M {
            Fn h, r;
            const char* name;
        };
        const M modes[] = {{PAIR(fn_sub_456410_00456410), "sub_456410"}, {PAIR(fn_sub_456450_00456450), "sub_456450"},
                           {PAIR(fn_sub_456490_00456490), "sub_456490"}, {PAIR(fn_sub_4564E0_004564e0), "sub_4564E0"},
                           {PAIR(fn_sub_456530_00456530), "sub_456530"}, {PAIR(fn_sub_456580_00456580), "sub_456580"},
                           {PAIR(fn_sub_4565D0_004565d0), "sub_4565D0"}, {PAIR(fn_sub_456620_00456620), "sub_456620"}};
        for (int k = 0; k < 8; ++k) {
            const PairOut q = pair(n, modes[k].h, modes[k].r, Args{arg64(rng, static_cast<u32>(pc)), 0, 0, 0}, rng(), modes[k].name);
            CHECK(*n.at(kWork + 4704) == k);  // the documented rule: one mode per function
            (void)q;
        }
        pair(n, PAIR(fn_sub_457340_00457340), Args{sx(pc), arg64(rng, rng() % 5), arg64(rng, rng() % 4), 0}, rng(), "sub_457340");
        pair(n, PAIR(fn_sub_457390_00457390), Args{sx(pc), 0, 0, 0}, rng(), "sub_457390");
        pair(n, PAIR(fn_sub_4573D0_004573d0), Args{sx(pc), 0, 0, 0}, rng(), "sub_4573D0");
        for (int s = 0; s < 4; ++s) {
            put32(n, 0x86E6A0u + 448 * s + 72, rng() % 3 ? rng() : 0);
            put32(n, 0x86E6A0u + 448 * s + 84, rng() % 2 ? obj(s) : 0);
            put32(n, 0x86E6A0u + 448 * s + 80, obj(8 + s));
        }
        const PairOut fr = pair(n, PAIR(fn_sub_457410_00457410), Args{}, rng(), "sub_457410");
        {
            u32 want = 0;
            for (int s = 0; s < 4 && !want; ++s)
                if (get32(n, 0x86E6A0u + 448 * s + 72) == 0) want = 0x86E6A0u + 448 * s;
            CHECK(static_cast<u32>(fr.hand.v0()) == want);
        }
        pair(n, PAIR(fn_sub_457470_00457470), Args{sx(rng() % 4), 0, 0, 0}, rng(), "sub_457470");
        // the party skill use: timers at 49 / 50, aim points
        put8(n, kWork + 4667, static_cast<u8>(47 + rng() % 4));
        put16(n, kWork + 4646, static_cast<u16>(rng() % 4));
        put8(n, kWork + 4665, static_cast<u8>(rng() % 5));
        pair(n, PAIR(fn_sub_456670_00456670), Args{0, sx(pc), 0, 0}, rng(), "sub_456670");
        pair(n, PAIR(fn_sub_456A90_00456a90), Args{0, sx(pc), sx(rng() % 4), 0}, rng(), "sub_456A90");
        pair(n, PAIR(fn_sub_456EA0_00456ea0), Args{0, sx(pc), sx(rng() % 4), 0}, rng(), "sub_456EA0");
    }
}

// Last in the file: the pair / stop totals of the cases above (printed; checked only for being non-zero).
TEST_CASE("game(tartarus): pair totals") {
    MESSAGE("tartarus pairs: " << g_pairs << ", ended at a missing-function stop: " << g_stops);
    CHECK(g_pairs >= 0);
}

}  // namespace

#endif  // P3FES_GAME_HAVE_GENERATED
