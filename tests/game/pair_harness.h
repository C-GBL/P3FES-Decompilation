// The pair harness of tests/game (test_replacements.cpp describes the gate): one guest machine with the
// ELF image in RAM, a fresh randomised context per call, and an Outcome capturing what a replaced
// function must reproduce from its recompiled body -- $v0, the callee-saved registers, the arena and the
// caller's live stack, the virtual cycles and the number of check points. The dead stack (below $sp)
// is captured too, for tests that want to compare the frame buffers a StackFrame keeps there, and is
// scrubbed after every run so both runs of a pair start from the same bytes.
//
// Hardware-observing pairs (opt-in, run_pair_hw / HwCheck at the end of this file): for functions that
// reach a hardware-touching callee kept recompiled behind guest::call (the DMA packet layer): the
// hardware register access log, scripted register reads, the scratchpad and caller-chosen guest ranges
// (the DMA buffer), and optionally every GPR in full. game/README.md "Pair tests that observe the
// hardware" documents it.
#pragma once

#include "fake_hooks.h"
#include "stand_in_entry.h"
#include "write_tracker.h"

#include "elf_image.h"
#include "p3fes/ee_memory.h"
#include "p3fes_recomp_rt.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

namespace p3fes::game_test {

constexpr u32 kGp = 0x007D2CF0u;     // crt0's $gp (RUNTIME_CONTRACT H-46)
constexpr u32 kSp = 0x01FFFF00u;     // inside the main-thread stack 0x1F60000-0x2000000
constexpr u32 kArena = 0x01800000u;  // scratch arena for arguments: free RAM far above .bss/heap start
constexpr u32 kArenaSize = 0x2000u;
constexpr u32 kDeadStack = 0x800u;   // bytes below $sp a recompiled body (and its callees) may spill into

inline u64 sx(u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }

// The offset of the first differing byte of two buffers of n bytes (n when they are equal): memcmp first, the byte
// walk only when they differ (pairs compare up to the whole 32 MiB of RAM; the walk alone was ~10 ms a pair).
inline std::size_t first_difference(const u8* a, const u8* b, std::size_t n) {
    if (std::memcmp(a, b, n) == 0) return n;
    std::size_t i = 0;
    while (i < n && a[i] == b[i]) ++i;
    return i;
}

inline const char* elf_path() {
    const char* p = std::getenv("P3FES_ELF");
    return p ? p : P3FES_ELF_DEFAULT;
}

using Fn = void (*)(EEContext&);
using Args = std::array<u64, 4>;

struct Machine {
    EEMemory mem;
    EEContext ctx;
    rt_test::TestHooks hooks;

    const char* load_elf(const char* path) {
        recomp::ElfImage elf;
        const recomp::ElfImage::LoadResult r = elf.load(path);
        if (r.error) return r.error;
        for (const recomp::ElfSegment& s : elf.segments()) {
            if (s.vaddr + s.memsz > EEMemory::kMainRamSize) return "segment outside main RAM";
            if (s.filesz == 0) continue;
            const u8* bytes = elf.bytes_at(s.vaddr, s.filesz);
            if (!bytes) return "segment bytes unavailable";
            std::memcpy(mem.main_ram() + s.vaddr, bytes, s.filesz);
        }
        return nullptr;
    }
    void fresh_context(const Args& a, std::mt19937& rng) {
        ctx = EEContext{};
        ctx.memory = &mem;
        for (unsigned r = 1; r < 32; ++r) {  // callee-saved registers carry random values the callee must keep
            ctx.gpr[r].u64[0] = (static_cast<u64>(rng()) << 32) | rng();
            ctx.gpr[r].u64[1] = rng();
        }
        ctx.gpr[GPR_ZERO].u64[0] = ctx.gpr[GPR_ZERO].u64[1] = 0;
        for (unsigned i = 0; i < 4; ++i) ctx.gpr[GPR_A0 + i].u64[0] = a[i];
        ctx.gpr[GPR_SP].u64[0] = sx(kSp);
        ctx.gpr[GPR_GP].u64[0] = sx(kGp);
        ctx.gpr[GPR_RA].u64[0] = sx(0x00100008u);
        ctx.cycles = 1000;
    }
    // Guest RAM helpers for arguments.
    u8* at(u32 va) { return mem.main_ram() + va; }
    void put(u32 va, const std::string& s) {
        std::memcpy(at(va), s.data(), s.size());
        at(va)[s.size()] = 0;
    }
    std::string str(u32 va, std::size_t max = 1024) const {
        const u8* p = mem.main_ram() + va;
        std::size_t n = 0;
        while (n < max && p[n] != 0) ++n;
        return std::string(reinterpret_cast<const char*>(p), n);
    }
    std::vector<u8> bytes(u32 va, u32 len) const { return std::vector<u8>(mem.main_ram() + va, mem.main_ram() + va + len); }
};

struct Outcome {
    u64 v0 = 0;
    u64 saved[12] = {};  // s0..s7, gp, sp, fp, ra
    u64 cycles = 0;
    int checks = 0;
    std::vector<u8> arena;
    std::vector<u8> live_stack;  // [sp, sp + 0x100): the caller's frame, must not change
    std::vector<u8> dead_stack;  // [sp - kDeadStack, sp): frames of the run, for tests that look at them
};

inline Outcome run(Machine& m, Fn fn, const Args& args, u32 seed) {
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    {
        const EntryBypass entry{fn};  // the function under test runs past its own stand-in (stand_in_entry.h)
        fn(m.ctx);
    }
    Outcome o;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.arena = m.bytes(kArena, kArenaSize);
    o.live_stack = m.bytes(kSp, 0x100);
    o.dead_stack = m.bytes(kSp - kDeadStack, kDeadStack);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);  // the next run starts from the same bytes
    return o;
}

inline void expect_same(const Outcome& hand, const Outcome& recomp, const char* what) {
    INFO(std::string(what));  // a const char* would print as a pointer (doctest)
    CHECK(hand.v0 == recomp.v0);
    for (int i = 0; i < 12; ++i) CHECK(hand.saved[i] == recomp.saved[i]);
    CHECK(hand.cycles == recomp.cycles);
    CHECK(hand.checks == recomp.checks);
    CHECK(hand.arena == recomp.arena);
    CHECK(hand.live_stack == recomp.live_stack);
}

// A guest region the function overwrites: snapshot before the first run, restored before the second,
// so both runs see the same input; after the pair the recomp run's output is in place.
struct Reset {
    u32 va;
    u32 len;
};

struct Pair {
    Outcome hand;
    Outcome recomp;
    bool faulted = false;  // both bodies stopped at the same fault (fault_of below): nothing else to compare
};

inline Pair run_pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
                     std::initializer_list<Reset> resets = {}) {
    std::vector<std::vector<u8>> before;
    for (const Reset& r : resets) before.push_back(m.bytes(r.va, r.len));
    Pair p;
    p.hand = run(m, hand, args, seed);
    std::size_t i = 0;
    for (const Reset& r : resets) std::memcpy(m.at(r.va), before[i++].data(), r.len);
    p.recomp = run(m, recomp, args, seed);
    expect_same(p.hand, p.recomp, what);
    return p;
}

// The frame bytes [sp - frame + from, sp - frame + from + len) of both runs, equal when a StackFrame
// put its buffers where the recompiled body put them.
inline bool same_frame_bytes(const Pair& p, u32 frame, u32 from, u32 len) {
    const std::size_t off = kDeadStack - frame + from;
    return std::equal(p.hand.dead_stack.begin() + off, p.hand.dead_stack.begin() + off + len, p.recomp.dead_stack.begin() + off);
}

// =====================================================================================================
// Hardware-observing pairs (opt-in; game/README.md "Pair tests that observe the hardware").
//
// A replaced function whose callees touch hardware registers (DMAC / VIF / GS: the DMA packet routines
// that stay recompiled behind guest::call) leaves more observable state than the Outcome above holds:
// the register accesses it caused, what it did with the values those reads returned, and guest memory
// outside the arena -- the scratchpad (0x70000000, 16 KiB) where the packets are built and the DMA buffer
// the fromSPR copies target. run_pair_hw() runs both bodies on the same scripted bus and compares all of
// it; run() / run_pair() and every existing test are unchanged.
// =====================================================================================================

// A guest range in main RAM (va + len <= 32 MiB) or in the scratchpad (0x70000000..0x70003FFF).
struct GuestRange {
    u32 va;
    u32 len;
};

// What a hardware-observing pair compares besides the Outcome, and the register values its bus serves.
struct HwCheck {
    std::map<u32, u64> regs;               // physical address -> value of reads (writes update it), set fresh for each run
    std::map<u32, std::vector<u64>> reads; // scripted reads: the k-th read of `pa` returns reads[pa][k], then `regs`
    std::vector<GuestRange> ranges;        // compared after both runs and restored before the second
    std::map<unsigned, u64> gpr_in;        // GPR low halves set after the randomised context (arguments 5..8 in $t0..$t3)
    bool compare_spr = true;               // the whole scratchpad (always restored before the second run)
    bool compare_bus = true;               // the access log (direction, width, address, value) and VU control writes
    u32 gpr_mask = 0;                      // GPRs compared in all 128 bits: bit r = register r
    bool compare_hilo = false;             // HI/LO of both pipes and SA
    // The whole register file (GPRs 1..31 in 128 bits, HI/LO, SA, FPRs, FCR31) and the cycle count at every
    // check point, compared in order. A check point may preempt the thread, and the kernel then saves the full
    // context at $sp - 0x280 in guest memory (KernelOptions::context_frames): the bytes a whole-program run
    // compares. Needed for any function whose scratch registers are live across its check points.
    bool compare_checkpoint_regs = false;
    bool compare_dead_stack = false;       // [sp - kDeadStack, sp): the frames and spills of the run
};
inline constexpr u32 kAllGprs = 0xFFFFFFFEu;  // every GPR but $zero

// The bus of a hardware-observing run: logs every access like rt_test::RecordingBus, serves reads from
// the script first, then the register map (writes update the map), then RecordingBus's address pattern.
class ScriptedBus final : public hle::HwBus {
public:
    using Access = rt_test::RecordingBus::Access;
    std::vector<Access> log;
    std::map<u32, u64> regs;
    std::map<u32, std::vector<u64>> reads;
    std::map<u32, std::size_t> next_read;
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
    void write8(u32 pa, u8 v) override { log.push_back({true, 8, pa, v, 0}); regs[pa] = v; }
    void write16(u32 pa, u16 v) override { log.push_back({true, 16, pa, v, 0}); regs[pa] = v; }
    void write32(u32 pa, u32 v) override { log.push_back({true, 32, pa, v, 0}); regs[pa] = v; }
    void write64(u32 pa, u64 v) override { log.push_back({true, 64, pa, v, 0}); regs[pa] = v; }
    void write128(u32 pa, const u128& v) override { log.push_back({true, 128, pa, v.u64[0], v.u64[1]}); regs[pa] = v.u64[0]; }
};

// The register file at one check point (HwCheck::compare_checkpoint_regs).
struct RegSnap {
    u64 cycles;
    std::array<u128, 32> gpr;
    u128 hi, lo;
    u32 sa, fcr31;
    std::array<u32, 32> fpr;
};

// The hooks of a hardware-observing run: rt_test::TestHooks' behaviour over a ScriptedBus.
class HwHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    int syscalls = 0;
    int checks = 0;
    int traps = 0;
    std::vector<std::pair<u32, u32>> vu_control;
    bool record_regs = false;
    std::vector<RegSnap> snaps;
    // A body that never returns (a loop the world keeps going) once grew `snaps` to 44 GB before the host ran out of
    // memory (test_events, 2026-10-22). Record the first kMaxSnaps register files, and stop the run with a fatal
    // event past kMaxChecks check points (its pc field is the $ra of the moment: the last call made from the loop).
    static constexpr std::size_t kMaxSnaps = 200000;
    static constexpr int kMaxChecks = 50000000;

    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        if (++checks > kMaxChecks) {
            static thread_local char what[64];
            const u32 ra = static_cast<u32>(ctx.gpr[GPR_RA].u64[0]);
            std::snprintf(what, sizeof what, "check-point budget ($ra 0x%08x)", ra);
            fatal(ctx, ra, what);
        }
        if (record_regs && snaps.size() < kMaxSnaps) {
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
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override { ++traps; }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { throw rt_test::FatalEvent{pc, what, &ctx}; }
    void vu_control_write(EEContext&, u32 reg, u32 value) override { vu_control.emplace_back(reg, value); }
};

// Host bytes of a GuestRange (nullptr when it is neither in main RAM nor in the scratchpad).
inline u8* guest_bytes(Machine& m, const GuestRange& r) {
    if (r.va < EEMemory::kMainRamSize && r.len <= EEMemory::kMainRamSize - r.va) return m.mem.main_ram() + r.va;
    if (r.va >= 0x70000000u && r.va - 0x70000000u + r.len <= 0x4000u) return m.mem.scratchpad() + (r.va - 0x70000000u);
    return nullptr;
}

struct HwOutcome {
    Outcome base;
    std::vector<ScriptedBus::Access> bus;
    std::vector<std::pair<u32, u32>> vu_control;
    int syscalls = 0;
    int traps = 0;
    std::vector<u8> spr;
    std::vector<std::vector<u8>> ranges;
    std::array<u128, 32> gpr{};
    u128 hi{}, lo{};
    u32 sa = 0;
    std::vector<RegSnap> snaps;
};

// One run on a fresh HwHooks (fresh log, `hw.regs` and `hw.reads` loaded), capturing the extra state.
// skip_range: a range run_pair_hw compares through a PairRange (its HwOutcome::ranges entry stays empty).
inline HwOutcome run_hw(Machine& m, Fn fn, const Args& args, u32 seed, const HwCheck& hw,
                        std::size_t skip_range = static_cast<std::size_t>(-1)) {
    HwHooks hooks;
    hooks.bus_.regs = hw.regs;
    hooks.bus_.reads = hw.reads;
    hooks.record_regs = hw.compare_checkpoint_regs;
    rt_test::HooksScope scope{&hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (const auto& [r, v] : hw.gpr_in) m.ctx.gpr[r].u64[0] = v;
    const u64 c0 = m.ctx.cycles;
    {
        const EntryBypass entry{fn};  // the function under test runs past its own stand-in (stand_in_entry.h)
        fn(m.ctx);
    }
    HwOutcome h;
    Outcome& o = h.base;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = hooks.checks;
    o.arena = m.bytes(kArena, kArenaSize);
    o.live_stack = m.bytes(kSp, 0x100);
    o.dead_stack = m.bytes(kSp - kDeadStack, kDeadStack);
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
    h.bus = std::move(hooks.bus_.log);
    h.vu_control = std::move(hooks.vu_control);
    h.syscalls = hooks.syscalls;
    h.traps = hooks.traps;
    h.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    for (std::size_t i = 0; i < hw.ranges.size(); ++i) {
        const u8* p = i == skip_range ? nullptr : guest_bytes(m, hw.ranges[i]);
        if (p) h.ranges.emplace_back(p, p + hw.ranges[i].len);
        else h.ranges.emplace_back();
    }
    for (unsigned r = 0; r < 32; ++r) h.gpr[r] = m.ctx.gpr[r];
    h.hi = m.ctx.hi;
    h.lo = m.ctx.lo;
    h.sa = m.ctx.sa;
    h.snaps = std::move(hooks.snaps);
    return h;
}

// Runs `body` and returns "" or the fatal event it raised (pc and message, without the host return address). Since the
// 2026-10-21 faithfulness audit the hand-written callees fault exactly where the original does, so a random world that
// holds an impossible id (a pointer the original loads through and faults on) makes BOTH bodies of a pair stop at the
// same instruction; pair tests compare the two faults (fault_of(hand) == fault_of(recomp)) and skip their value checks.
template <class Body>
std::string fault_of(Body&& body) {
    try {
        body();
        return {};
    } catch (const rt_test::FatalEvent& e) {
        std::string w = e.what;
        if (const std::size_t k = w.find("; host return address"); k != std::string::npos) w.erase(k);
        return std::to_string(e.pc) + ": " + w;
    }
}

// 0x-prefixed hex for doctest messages (INFO does not keep stream manipulators).
inline std::string hex64(u64 v) {
    char buf[24];
    std::snprintf(buf, sizeof buf, "0x%llx", static_cast<unsigned long long>(v));
    return buf;
}

inline bool same_u128(const u128& a, const u128& b) { return a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]; }

inline constexpr std::size_t kNoRange = static_cast<std::size_t>(-1);

inline void expect_same_hw(const HwOutcome& hand, const HwOutcome& recomp, const HwCheck& hw, const char* what,
                           std::size_t tracked = kNoRange, std::size_t tracked_first = 0) {
    expect_same(hand.base, recomp.base, what);
    INFO(std::string(what));  // a const char* would print as a pointer (doctest)
    // The callee-saved registers in all 128 bits (expect_same covers the low halves): SQ/LQ spills.
    const unsigned saved[8] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7};
    for (unsigned r : saved) CHECK(hand.gpr[r].u64[1] == recomp.gpr[r].u64[1]);
    CHECK(hand.syscalls == recomp.syscalls);
    CHECK(hand.traps == recomp.traps);
    if (hw.compare_bus) {
        CHECK(hand.bus.size() == recomp.bus.size());
        const std::size_t n = std::min(hand.bus.size(), recomp.bus.size());
        for (std::size_t i = 0; i < n; ++i) {
            const auto& a = hand.bus[i];
            const auto& b = recomp.bus[i];
            if (a.write != b.write || a.bits != b.bits || a.pa != b.pa || a.lo != b.lo || a.hi != b.hi) {
                INFO("bus access " << i << ": hand " << (a.write ? "W" : "R") << a.bits << " " << hex64(a.pa) << "=" << hex64(a.lo)
                                   << " recomp " << (b.write ? "W" : "R") << b.bits << " " << hex64(b.pa) << "="
                                   << hex64(b.lo));
                CHECK(false);
                break;
            }
        }
        CHECK(hand.vu_control == recomp.vu_control);
    }
    if (hw.compare_spr) {
        const std::size_t first = first_difference(hand.spr.data(), recomp.spr.data(), hand.spr.size());
        INFO("first differing scratchpad byte " << hex64(first));
        CHECK(first == hand.spr.size());
    }
    for (std::size_t i = 0; i < hw.ranges.size(); ++i) {
        const auto& a = hand.ranges[i];
        const auto& b = recomp.ranges[i];
        // (a range run_pair_hw compared through a PairRange: its result is passed in, the outcomes hold no copy)
        const std::size_t size = i == tracked ? hw.ranges[i].len : a.size();
        const std::size_t first = i == tracked ? tracked_first : first_difference(a.data(), b.data(), a.size());
        INFO("range " << hex64(hw.ranges[i].va) << ": first differing byte at +" << hex64(first));
        CHECK(first == size);
    }
    for (unsigned r = 0; r < 32; ++r) {
        if (!(hw.gpr_mask & (1u << r))) continue;
        INFO("GPR " << r << ": hand " << hex64(hand.gpr[r].u64[1]) << ":" << hex64(hand.gpr[r].u64[0]) << " recomp "
                    << hex64(recomp.gpr[r].u64[1]) << ":" << hex64(recomp.gpr[r].u64[0]));
        CHECK(same_u128(hand.gpr[r], recomp.gpr[r]));
    }
    if (hw.compare_hilo) {
        CHECK(same_u128(hand.hi, recomp.hi));
        CHECK(same_u128(hand.lo, recomp.lo));
        CHECK(hand.sa == recomp.sa);
    }
    if (hw.compare_dead_stack) {
        const auto& a = hand.base.dead_stack;
        const auto& b = recomp.base.dead_stack;
        const std::size_t first = first_difference(a.data(), b.data(), a.size());
        INFO("dead stack: first differing byte at sp - " << hex64(kDeadStack - first));
        CHECK(first == a.size());
    }
    if (hw.compare_checkpoint_regs) {
        CHECK(hand.snaps.size() == recomp.snaps.size());
        const std::size_t n = std::min(hand.snaps.size(), recomp.snaps.size());
        for (std::size_t i = 0; i < n; ++i) {
            const RegSnap& a = hand.snaps[i];
            const RegSnap& b = recomp.snaps[i];
            int bad = -1;  // 1..31 GPR, 32 HI, 33 LO, 34 SA/FCR31, 35 FPR, 36 cycles
            for (unsigned r = 1; r < 32 && bad < 0; ++r)
                if (!same_u128(a.gpr[r], b.gpr[r])) bad = static_cast<int>(r);
            if (bad < 0 && !same_u128(a.hi, b.hi)) bad = 32;
            if (bad < 0 && !same_u128(a.lo, b.lo)) bad = 33;
            if (bad < 0 && (a.sa != b.sa || a.fcr31 != b.fcr31)) bad = 34;
            if (bad < 0 && a.fpr != b.fpr) bad = 35;
            if (bad < 0 && a.cycles != b.cycles) bad = 36;
            if (bad >= 0) {
                const u128 x = bad < 32 ? a.gpr[bad] : bad == 32 ? a.hi : a.lo;
                const u128 y = bad < 32 ? b.gpr[bad] : bad == 32 ? b.hi : b.lo;
                INFO("check point " << i << " of " << n << " (cycles " << a.cycles << " / " << b.cycles
                                    << "): first differing register " << bad << ": hand " << hex64(x.u64[1]) << ":"
                                    << hex64(x.u64[0]) << " recomp " << hex64(y.u64[1]) << ":" << hex64(y.u64[0]));
                CHECK(false);
                break;
            }
        }
    }
}

struct HwPair {
    HwOutcome hand;
    HwOutcome recomp;
};

// The hardware-observing pair: the scratchpad, `hw.ranges` and `resets` are snapshot before the hand run
// and restored before the recompiled run (both start from the same bytes and the same scripted bus); after
// the pair the recompiled run's output is in place. The first range of 1 MiB or more (the whole RAM in
// test_render_rw2.cpp) goes through a PairRange (write_tracker.h): the same snapshot / restore / compare, but only
// the pages written are copied (five 32 MiB copies and a 32 MiB compare per pair were most of those tests' time).
inline constexpr u32 kTrackedRangeMin = 0x100000u;

// The BIOS window (EEMemory::bios(), 4 MiB, writable) is compared and restored like the RAM ranges, through a second
// PairRange: a store through a stray or sign-extended pointer lands there (0xFFFFxxxx folds to the physical 0x1FFFxxxx,
// inside 0x1FC00000-0x1FFFFFFF). Without it the first body's BIOS stores were still in place when the second body ran,
// so the second body read the first body's values (test_fx_types.cpp, 2026-10-29: sub_345DB0 creates from an effect
// whose block A is the relative offset 0xFFFFEAF0; sub_344EB0 stores 3 at block +140, then the recompiled run's memcpy
// copied that 3 into the instance). A pair that writes no BIOS page costs two VirtualProtect calls.

inline HwPair run_pair_hw(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw,
                          std::initializer_list<Reset> resets = {}) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    std::size_t tracked = kNoRange;
    for (std::size_t i = 0; i < hw.ranges.size() && tracked == kNoRange; ++i)
        if (hw.ranges[i].len >= kTrackedRangeMin && hw.ranges[i].va < EEMemory::kMainRamSize) tracked = i;
    std::vector<std::vector<u8>> ranges, before;
    for (std::size_t i = 0; i < hw.ranges.size(); ++i) {
        const u8* p = guest_bytes(m, hw.ranges[i]);
        REQUIRE(p != nullptr);
        if (i == tracked) ranges.emplace_back();
        else ranges.emplace_back(p, p + hw.ranges[i].len);
    }
    for (const Reset& r : resets) before.push_back(m.bytes(r.va, r.len));
    std::unique_ptr<PairRange> big;  // armed here, where the snapshot of the range is taken
    if (tracked != kNoRange) {
        u8* lo = guest_bytes(m, hw.ranges[tracked]);
        big = std::make_unique<PairRange>(lo, lo + hw.ranges[tracked].len);
    }
    PairRange bios(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
    HwPair p;
    p.hand = run_hw(m, hand, args, seed, hw, tracked);
    bios.between();
    if (big) big->between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    for (std::size_t i = 0; i < hw.ranges.size(); ++i)
        if (i != tracked) std::memcpy(guest_bytes(m, hw.ranges[i]), ranges[i].data(), ranges[i].size());
    std::size_t i = 0;
    for (const Reset& r : resets) std::memcpy(m.at(r.va), before[i++].data(), r.len);
    p.recomp = run_hw(m, recomp, args, seed, hw, tracked);
    {
        const std::size_t first = bios.first_difference();
        INFO(std::string(what));
        INFO("BIOS window: first differing byte at " << hex64(EEMemory::kBiosBase + first));
        CHECK(first == bios.size());
    }
    expect_same_hw(p.hand, p.recomp, hw, what, tracked, big ? big->first_difference() : 0);
    return p;
}

inline bool same_frame_bytes(const HwPair& p, u32 frame, u32 from, u32 len) {
    const std::size_t off = kDeadStack - frame + from;
    return std::equal(p.hand.base.dead_stack.begin() + off, p.hand.base.dead_stack.begin() + off + len,
                      p.recomp.base.dead_stack.begin() + off);
}

// Bus helpers for tests: the number of accesses to `pa` in a log, writes only when `writes`.
inline std::size_t count_access(const std::vector<ScriptedBus::Access>& log, u32 pa, bool writes) {
    std::size_t n = 0;
    for (const auto& a : log) n += (a.pa == pa && a.write == writes) ? 1u : 0u;
    return n;
}

}  // namespace p3fes::game_test
