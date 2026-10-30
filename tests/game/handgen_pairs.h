// The pair runner of the p3fes_handgen test skeletons (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): a hand body
// and its recompiled body run from the same guest machine and must leave the same
//   * whole register file -- GPRs 1..31 in 128 bits, HI/LO, SA, FCR31, ACC, the FPRs, the VU0 macro registers -- and
//     cycle count at EVERY check point, in order (a check point may preempt the thread, and the kernel then saves the
//     whole register file at $sp - 0x280: the bytes a whole-program run compares; brief, wave 7);
//   * whole register file and cycle count at the return, or at the stop when the run ends early (a callee that is not
//     emitted in this build, an address fault, a runaway walk cut at the same check point): same pc, same message;
//   * the whole 32 MiB of main RAM (a PairRange: only written pages are copied), the scratchpad and the BIOS window;
//   * the hardware bus log and the syscall count (pair_harness.h's ScriptedBus: HwCheck::regs / reads script it).
// It is run_pair_hw / HwCheck's comparison widened to runs that stop (tests/game/test_battle_fx.cpp's runner, shared).
// The random register file: fresh_context's GPRs (pair_harness.h), $t0..$t3 world words (arguments 5..8), random
// singles in the FPRs and VU0, FCR31's C bit.
#pragma once

#include "pair_harness.h"
#include "write_tracker.h"

#include <array>
#if defined(_MSC_VER)
#include <excpt.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

namespace p3fes::game_test::hgp {

struct Snap {
    u64 cycles = 0;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0, fcr31 = 0, acc = 0;
    std::array<u32, 32> fpr{};
    VU0State vu0{};
};

inline Snap snap(const EEContext& c) {
    Snap s;
    s.cycles = c.cycles;
    for (unsigned r = 0; r < 32; ++r) s.gpr[r] = c.gpr[r];
    s.hi = c.hi;
    s.lo = c.lo;
    s.sa = c.sa;
    s.fcr31 = c.fcr31;
    s.acc = c.acc;
    for (unsigned i = 0; i < 32; ++i) s.fpr[i] = c.fpr[i];
    s.vu0 = c.vu0;
    return s;
}

// The first difference of two snapshots ("" when equal).
inline std::string diff(const Snap& a, const Snap& b) {
    for (unsigned r = 1; r < 32; ++r)
        if (!same_u128(a.gpr[r], b.gpr[r]))
            return "gpr " + std::to_string(r) + ": hand " + hex64(a.gpr[r].u64[1]) + ":" + hex64(a.gpr[r].u64[0]) + " recomp " +
                   hex64(b.gpr[r].u64[1]) + ":" + hex64(b.gpr[r].u64[0]);
    if (!same_u128(a.hi, b.hi)) return "hi";
    if (!same_u128(a.lo, b.lo)) return "lo";
    if (a.sa != b.sa) return "sa";
    if (a.fcr31 != b.fcr31) return "fcr31: hand " + hex64(a.fcr31) + " recomp " + hex64(b.fcr31);
    if (a.acc != b.acc) return "acc";
    const VU0State &x = a.vu0, &y = b.vu0;  // field by field (the struct has padding)
    if (std::memcmp(x.vf, y.vf, sizeof x.vf) != 0) return "vu0 vf";
    if (std::memcmp(x.vi, y.vi, sizeof x.vi) != 0) return "vu0 vi";
    if (std::memcmp(x.acc, y.acc, sizeof x.acc) != 0) return "vu0 acc";
    if (x.q != y.q || x.p != y.p || x.i != y.i || x.r != y.r) return "vu0 q/p/i/r";
    if (x.status != y.status || x.mac != y.mac || x.clip != y.clip) return "vu0 flags";
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) return "fpr " + std::to_string(i) + ": hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]);
    if (a.cycles != b.cycles) return "cycles " + std::to_string(a.cycles) + " / " + std::to_string(b.cycles);
    return {};
}

// The hooks of one run: every check point's register file, the stop (fatal event) with its register file, the bus.
class Hooks final : public RtHooks {
public:
    ScriptedBus bus_;
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    Snap at_stop;
    int syscalls = 0;
    std::vector<std::pair<u32, u32>> vu_control;
    // A body walking random data without end is cut at the same check point in both runs (stop pc 0xFFFFFFFF).
    std::size_t max_checks = 20000;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        snaps.push_back(snap(ctx));
        if (snaps.size() >= max_checks) {
            stopped = true;
            stop_pc = 0xFFFFFFFFu;
            what = "runaway";
            at_stop = snaps.back();
            throw rt_test::FatalEvent{stop_pc, "runaway", &ctx};
        }
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* w) override {
        stopped = true;
        stop_pc = pc;
        what = w;
        // the fault message names the host return address (inside the hand or the recompiled body): not compared
        if (const std::size_t k = what.find("; host return address"); k != std::string::npos) what.erase(k);
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, w, &ctx};
    }
    void vu_control_write(EEContext&, u32 reg, u32 value) override { vu_control.emplace_back(reg, value); }
};

struct Run {
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
    std::vector<u8> spr;
    std::vector<ScriptedBus::Access> bus;
    std::vector<std::pair<u32, u32>> vu_control;
};

// The call, with a host access violation caught as a stop: some hand-written callees of a whole-program build
// (p3fes_handgen_deep) read guest memory through host pointers without the runtime's mapping checks, so a random world
// can fault the host in both bodies alike. (C++ exceptions -- the fatal-event stops -- pass through.) The write faults of
// a WriteTracker are handled by its vectored handler before this filter sees anything.
inline bool call_guarded(Fn fn, EEContext& ctx) {
#if defined(_MSC_VER)
    __try {
        fn(ctx);
    } __except (_exception_code() == 0xC0000005u /* EXCEPTION_ACCESS_VIOLATION */ ? 1 /* EXECUTE_HANDLER */ : 0) {
        return false;
    }
#else
    fn(ctx);
#endif
    return true;
}

inline float small_float(std::mt19937& rng) {
    return static_cast<float>(static_cast<int>(rng() % 2001) - 1000) / static_cast<float>(1 + rng() % 64);
}

// One run from the seed's register file (both runs of a pair draw the same values).
inline Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const HwCheck& hw) {
    Hooks h;
    h.bus_.regs = hw.regs;
    h.bus_.reads = hw.reads;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 4; ++i) m.ctx.gpr[GPR_T0 + i].u64[0] = rng() % 4 == 0 ? (static_cast<u64>(rng()) << 32) | rng() : rng() % 64;
    for (unsigned i = 0; i < 32; ++i) {
        const float f = small_float(rng);
        u32 bits;
        std::memcpy(&bits, &f, 4);
        m.ctx.fpr[i] = rng() % 10 == 0 ? static_cast<u32>(rng()) : bits;
    }
    m.ctx.fcr31 = rng() & 0x00800000u;
    for (unsigned r = 1; r < 32; ++r)
        for (u32& x : m.ctx.vu0.vf[r]) {
            const float f = small_float(rng);
            std::memcpy(&x, &f, 4);
        }
    for (u32& x : m.ctx.vu0.acc) x = rng() & 0x7F7FFFFFu;
    for (const auto& [r, v] : hw.gpr_in) m.ctx.gpr[r].u64[0] = v;
    bool host_fault = false;
    try {
        const EntryBypass entry{fn};  // the function under test runs past its own stand-in (stand_in_entry.h)
        host_fault = !call_guarded(fn, m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    if (host_fault && !h.stopped) {
        h.stopped = true;
        h.stop_pc = 0xFFFFFFFEu;
        h.what = "host access violation";
        h.at_stop = snap(m.ctx);
    }
    Run r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.what = h.what;
    r.syscalls = h.syscalls;
    r.snaps = std::move(h.snaps);
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    r.bus = std::move(h.bus_.log);
    r.vu_control = std::move(h.vu_control);
    return r;
}

inline bool bios_clean(Machine& m) {
    static const std::vector<u8> zeros(EEMemory::kBiosSize, 0);
    return std::memcmp(m.mem.bios(), zeros.data(), EEMemory::kBiosSize) == 0;
}

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place. Returns the recompiled run
// (its end state: $v0 in end.gpr[GPR_V0]; stopped / stop_pc / what for an early stop).
inline Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw = {}) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    if (std::getenv("P3FES_HG_RECOMP_FIRST")) std::swap(hand, recomp);  // debugging: which body crashes the host
    if (trace) std::fprintf(stderr, "  hand\n");
    Run h = run_one(m, hand, args, seed, hw);
    if (trace) std::fprintf(stderr, "  recomp\n");
    std::vector<u8> bios_h;  // a stray store through a random pointer may land in the (writable, zero) BIOS window
    if (!bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    Run r = run_one(m, recomp, args, seed, hw);
    const bool bios_r = !bios_clean(m);
    INFO(what << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " a3=" << hex64(args[3])
              << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string())
              << (h.stopped ? " (hand stopped: " + h.what + " at " + hex64(h.stop_pc) + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r && !bios_h.empty()) CHECK(std::memcmp(bios_h.data(), m.mem.bios(), EEMemory::kBiosSize) == 0);
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);  // (the check points below say where the runs part)
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
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
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                                  << unsigned(m.mem.main_ram()[first]));
        CHECK(false);
    }
    {
        const std::size_t first = first_difference(h.spr.data(), r.spr.data(), h.spr.size());
        INFO("scratchpad: first differing byte at " << hex64(first));
        CHECK(first == h.spr.size());
    }
    CHECK(h.bus.size() == r.bus.size());
    const std::size_t nb = std::min(h.bus.size(), r.bus.size());
    for (std::size_t i = 0; i < nb; ++i) {
        const auto& a = h.bus[i];
        const auto& b = r.bus[i];
        if (a.write != b.write || a.bits != b.bits || a.pa != b.pa || a.lo != b.lo || a.hi != b.hi) {
            INFO("bus access " << i << " differs: hand " << hex64(a.pa) << " recomp " << hex64(b.pa));
            CHECK(false);
            break;
        }
    }
    CHECK(h.vu_control == r.vu_control);
    return r;
}

// --- random worlds ---------------------------------------------------------------------------------------------------

// Words that are mostly zero or small, now and then a pointer back into [lo, lo + len) (4-aligned) or a wide value:
// a field the code takes for a pointer lands in the world or makes both bodies fault at the same instruction.
inline u32 world_word(std::mt19937& rng, u32 lo, u32 len) {
    const u32 k = rng() % 16;
    if (k < 6) return 0;
    if (k < 10) return rng() % 32;
    if (k < 14) return lo + ((rng() % len) & ~3u);
    if (k < 15) return rng() & 0xFFFFu;
    return rng();
}
inline void random_world(Machine& m, u32 lo, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= len; i += 4) {
        const u32 v = world_word(rng, lo, len);
        std::memcpy(m.at(lo + i), &v, 4);
    }
}
// An argument: a pointer into the world (half the time), a small value, zero or a wide value (sign-extended).
inline u64 random_arg(std::mt19937& rng, u32 lo, u32 len) {
    const u32 k = rng() % 8;
    if (k < 4) return sx(lo + ((rng() % len) & ~15u));
    if (k < 6) return rng() % 16;
    if (k < 7) return 0;
    return sx(rng());
}

}  // namespace p3fes::game_test::hgp
