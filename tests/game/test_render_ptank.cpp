// Phase 5 pair tests for the render_ptank slice (game/src/render/ptank.cpp): RenderWare's particle tanks -- the sprite
// writers, the tank callbacks and the draw path (docs/ANALYSIS/22_rendering.md sections 2.4, 4, 7). Each hand-written
// function and the recompiled body it replaces run on identical guest machines built from random tank blocks, camera
// vectors, particle arrays, lock records and vertex streams.
//
// Stricter than the Outcome (as test_render_mesh.cpp): per pair this file compares EVERY general register in 128
// bits, HI/LO, all FPU registers, ACC, FCR31 and the whole VU0 state at the return, the whole register file (GPRs,
// HI/LO, SA, FPRs, FCR31) and the cycle count at EVERY check point, the bus access log (the scratchpad streamers'
// D8 / D9 / D_STAT accesses, the DMA packet layer), the scratchpad, the world region of the case, the RW globals
// window, the WHOLE stack window (live and dead: the hand versions write the original's spills, including the
// compiler's own spill slots of the big writers), the virtual cycles, the check-point and syscall counts. FPRs, ACC,
// HI/LO and VU0 start random, so a register the original leaves alone must stay alone. The streams sometimes overlap
// their sources (the per-component load / store order is then observable). Host-side checks restate the documented
// layouts (ptank.h: the corner order of a quad, the UV rectangle's vertex pairs, the packed colours).
//
// The scratchpad streamers (sub_476C20 copy, sub_476140 / sub_476720 fills) are hand-written since finalB (slice
// finalB, game/src/fx/finalB.cpp; paired in tests/game/test_finalB.cpp): here their D9 / D8 channels are served idle
// (CHCR 0), the bus performs no transfer (both runs see the same), and their _sceFlushCache syscall is counted.
#include "pair_harness.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/game/ptank.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
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
P3FES_DECL_PAIR(fn_sub_486980_00486980)
P3FES_DECL_PAIR(fn_sub_486AE0_00486ae0)
P3FES_DECL_PAIR(fn_sub_486EC0_00486ec0)
P3FES_DECL_PAIR(fn_sub_487520_00487520)
P3FES_DECL_PAIR(fn_sub_487990_00487990)
P3FES_DECL_PAIR(fn_sub_487AC0_00487ac0)
P3FES_DECL_PAIR(fn_sub_488260_00488260)
P3FES_DECL_PAIR(fn_sub_4882F0_004882f0)
P3FES_DECL_PAIR(fn_sub_488390_00488390)
P3FES_DECL_PAIR(fn_sub_488410_00488410)
P3FES_DECL_PAIR(fn_sub_487E80_00487e80)
P3FES_DECL_PAIR(fn_sub_487EF0_00487ef0)
P3FES_DECL_PAIR(fn_sub_4880B0_004880b0)
P3FES_DECL_PAIR(fn_sub_4884A0_004884a0)
P3FES_DECL_PAIR(fn_sub_488B80_00488b80)
P3FES_DECL_PAIR(fn_sub_486100_00486100)
P3FES_DECL_PAIR(fn_sub_485070_00485070)
P3FES_DECL_PAIR(fn_sub_485E20_00485e20)
P3FES_DECL_PAIR(fn_sub_486C80_00486c80)
P3FES_DECL_PAIR(fn_sub_487030_00487030)
P3FES_DECL_PAIR(fn_sub_487280_00487280)
P3FES_DECL_PAIR(fn_sub_4876F0_004876f0)
P3FES_DECL_PAIR(fn_sub_487BF0_00487bf0)
P3FES_DECL_PAIR(fn_sub_477610_00477610)
P3FES_DECL_PAIR(fn_sub_477A20_00477a20)
P3FES_DECL_PAIR(fn_sub_477EB0_00477eb0)
P3FES_DECL_PAIR(fn_sub_478280_00478280)
P3FES_DECL_PAIR(fn_sub_485110_00485110)
P3FES_DECL_PAIR(fn_sub_485440_00485440)
P3FES_DECL_PAIR(fn_sub_477150_00477150)
P3FES_DECL_PAIR(fn_sub_479170_00479170)
P3FES_DECL_PAIR(fn_sub_479590_00479590)
P3FES_DECL_PAIR(fn_sub_488550_00488550)
P3FES_DECL_PAIR(fn_sub_4866C0_004866c0)
P3FES_DECL_PAIR(fn_sub_47BF80_0047bf80)
P3FES_DECL_PAIR(fn_sub_478520_00478520)
P3FES_DECL_PAIR(fn_sub_479900_00479900)
P3FES_DECL_PAIR(fn_sub_47B280_0047b280)
P3FES_DECL_PAIR(fn_sub_47B750_0047b750)
P3FES_DECL_PAIR(fn_sub_4861B0_004861b0)
P3FES_DECL_PAIR(fn_sub_474160_00474160)
P3FES_DECL_PAIR(fn_sub_488B90_00488b90)
P3FES_DECL_PAIR(fn_sub_474A80_00474a80)
P3FES_DECL_PAIR(fn_sub_4749A0_004749a0)
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
constexpr u32 kStackLo = kSp - kDeadStack;
constexpr u32 kStackLen = kDeadStack + 0x100;
constexpr u32 kD8Chcr = 0x1000D000u, kD9Chcr = 0x1000D400u;

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region> kBase = {{kWorld, kWorldLen}, {kGpWindow, kGpWindowLen}};

// --- guest RAM helpers -------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
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

// The scripted hardware of a case: register values and per-register read scripts, extra GPR inputs.
struct Hw {
    std::map<u32, u64> regs{{kD8Chcr, 0}, {kD9Chcr, 0}};  // the streamers' channels idle
    std::map<u32, std::vector<u64>> reads;
    std::map<unsigned, u64> gpr_in;  // set after the randomised context (the 5th argument in $t0)
};

// The bus of a run: pair_harness.h's ScriptedBus behaviour (log every access, serve the read scripts, then the register
// map, then RecordingBus's pattern) plus a fake DMAC for the two scratchpad channels the PTank streamers use: a CHCR
// write with STR (bit 8) moves QWC quadwords at once -- D9 toSPR from MADR to the scratchpad at SADR, D8 fromSPR from
// the scratchpad at SADR to MADR -- then clears STR and QWC and sets the channel's D_STAT bit (a D_STAT write clears
// the bits written, toggles the mask bits). So a streamer's wait loops end and its data really moves; both runs of a
// pair see the same device.
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
    int transfers = 0;

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
        ++transfers;
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

// The hooks of a run: HwHooks' behaviour over the DmacBus.
class PtHooks final : public RtHooks {
public:
    DmacBus bus_;
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

int g_dma_transfers = 0;

Snap run_full(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Region>& regions, const Hw& hw) {
    PtHooks hooks;
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
    g_dma_transfers += hooks.bus_.transfers;
    s.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    s.stack = m.bytes(kStackLo, kStackLen);
    for (const Region& r : regions) s.regions.push_back(m.bytes(r.va, r.len));
    std::memset(m.at(kStackLo), 0, kDeadStack);
    return s;
}

int g_pairs = 0;
int g_faulted_pairs = 0;  // both runs stopped at the same fault

std::size_t first_diff(const std::vector<u8>& a, const std::vector<u8>& b) {
    std::size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) ++i;
    return i;
}

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
    Snap h, r;
    const std::string fh = fault_of([&] { h = run_full(m, hand, args, seed, regions, hw); });
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    for (std::size_t i = 0; i < regions.size(); ++i) std::memcpy(m.at(regions[i].va), before[i].data(), regions[i].len);
    const std::string fr = fault_of([&] { r = run_full(m, recomp, args, seed, regions, hw); });
    if (!fh.empty() || !fr.empty()) {
        // A random pointer the original itself faults on (the register-faithful callees fault where it does, since
        // the 2026-10-21 audit): both runs must stop at the same instruction.
        INFO("hand: " << fh << "; recomp: " << fr);
        CHECK(fh == fr);
        std::memset(m.at(kStackLo), 0, kDeadStack);
        ++g_faulted_pairs;
        return {h, r};
    }
    ++g_pairs;
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

// --- a random tank -------------------------------------------------------------------------------------------
// Layout of a case: the stream record at +0x40, camera right / up at +0x80 / +0x90, the tank block at +0x100 (0x100
// bytes of random floats, then its array pointers), the particle arrays from +0x1000, the vertex stream from +0x10000.
constexpr u32 kStream = kWorld + 0x40, kRight = kWorld + 0x80, kUp = kWorld + 0x90, kTank = kWorld + 0x100;
constexpr u32 kArrays = kWorld + 0x1000, kVerts = kWorld + 0x10000;

// A count: mostly small, sometimes 8..17 (the unrolled loops), 0, or negative as a whole register.
u64 rand_count(std::mt19937& rng) {
    if (chance(rng, 6)) return rng64(rng) | (1ull << 63);
    if (chance(rng, 6)) return 0;
    return pick(rng, {1, 1, 2, 3, 4, 5, 7, 8, 9, 10, 16, 17, 25, 40});
}

// Fills the tank block, its per-particle arrays {pointer, stride} at +4 .. +72, and the stream. `elem` is the
// vertex element size the writer stores (the vertex stride is >= it, or equal to it). Returns the vertex stride.
u32 put_tank(Machine& m, std::mt19937& rng, u32 elem, bool may_alias = true) {
    fill_random(m, kWorld, 0x1000, rng);
    fill_floats(m, kTank, 64, rng);
    fill_floats(m, kRight, 4, rng);
    fill_floats(m, kUp, 4, rng);
    fill_floats(m, kArrays, 0xC000 / 4, rng);
    // arrays: +4 positions, +12 matrices, +20 second component, +28 sizes, +36 colours, +44 vertex colours, +52
    // rotations, +60 UV rectangles, +68 UV quads; strides >= the element size (sometimes 0: every particle the same)
    const u32 elems[9] = {12, 64, 12, 8, 4, 16, 4, 16, 32};
    for (u32 k = 0; k < 9; ++k) {
        const u32 base = kArrays + 0x1400u * k + 4u * (rng() % 4);
        const u32 stride = chance(rng, 8) ? 0u : elems[k] + 4u * pick(rng, {0, 0, 0, 1, 2, 4});
        w32(m, kTank + 4 + 8 * k, base);
        w32(m, kTank + 8 + 8 * k, stride);
    }
    const u32 stride = chance(rng, 30) ? elem : elem + 4u * pick(rng, {1, 2, 3, 5, 8});
    u32 dst = kVerts + 4u * (rng() % 64);
    if (may_alias && chance(rng, 8)) dst = r32(m, kTank + 4 + 8 * (rng() % 9));  // the stream overlaps a source
    w32(m, kStream, dst);
    w32(m, kStream + 4, stride);
    return stride;
}

}  // namespace

// =========================================================================================================
// 3-D sprite writers
// =========================================================================================================

TEST_CASE("game(render_ptank): the 3-D position writers sub_486980 .. sub_487AC0 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x486980u};
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_486980", PAIR(fn_sub_486980_00486980)}, {"sub_486AE0", PAIR(fn_sub_486AE0_00486ae0)},
                    {"sub_486EC0", PAIR(fn_sub_486EC0_00486ec0)}, {"sub_487520", PAIR(fn_sub_487520_00487520)},
                    {"sub_487990", PAIR(fn_sub_487990_00487990)}, {"sub_487AC0", PAIR(fn_sub_487AC0_00487ac0)},
                    {"sub_486C80", PAIR(fn_sub_486C80_00486c80)}, {"sub_487030", PAIR(fn_sub_487030_00487030)},
                    {"sub_487280", PAIR(fn_sub_487280_00487280)}, {"sub_4876F0", PAIR(fn_sub_4876F0_004876f0)}};
    for (const W& wr : ws) {
        for (int i = 0; i < 250; ++i) {
            put_tank(m, rng, 12);
            const u64 count = rand_count(rng);
            Hw hw;
            hw.gpr_in[GPR_T0] = kTank;
            const auto [h, r] = pair(m, wr.hand, wr.recomp, Args{kStream, kRight, kUp, count}, seed_of(i, 0x4869u), wr.name, hw);
            (void)h;
            (void)r;
        }
    }
    // documented (ptank.h): v0 = p - r - u with r = right * w/2, u = up * h/2 (sub_486980, one particle)
    namespace fpu = ee::fpu;
    for (int i = 0; i < 50; ++i) {
        put_tank(m, rng, 12, false);
        Hw hw;
        hw.gpr_in[GPR_T0] = kTank;
        pair(m, PAIR(fn_sub_486980_00486980), Args{kStream, kRight, kUp, 1}, seed_of(i, 0x1111u), "sub_486980 rule", hw);
        const u32 p = r32(m, kTank + 4), dst = r32(m, kStream);
        const u32 hw2 = fpu::mul(0x3F000000u, r32(m, kTank + 112)), hh = fpu::mul(0x3F000000u, r32(m, kTank + 116));
        const u32 rx = fpu::mul(r32(m, kRight), hw2), ux = fpu::mul(r32(m, kUp), hh);
        const u32 corner = fpu::sub(rx ^ fpu::kSign, ux);
        CHECK(r32(m, dst) == fpu::add(r32(m, p), corner));
    }
    MESSAGE("3-D position pairs: " << g_pairs);
}

TEST_CASE("game(render_ptank): the UV / colour / second-component writers equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x488260u};
    struct W {
        const char* name;
        Fn hand, recomp;
        u32 elem;
    };
    const W ws[] = {{"sub_488260", PAIR(fn_sub_488260_00488260), 8},  {"sub_4882F0", PAIR(fn_sub_4882F0_004882f0), 8},
                    {"sub_488390", PAIR(fn_sub_488390_00488390), 8},  {"sub_488410", PAIR(fn_sub_488410_00488410), 8},
                    {"sub_487E80", PAIR(fn_sub_487E80_00487e80), 4},  {"sub_487EF0", PAIR(fn_sub_487EF0_00487ef0), 4},
                    {"sub_4880B0", PAIR(fn_sub_4880B0_004880b0), 4},  {"sub_4884A0", PAIR(fn_sub_4884A0_004884a0), 12},
                    {"sub_486100", PAIR(fn_sub_486100_00486100), 12}, {"sub_487BF0", PAIR(fn_sub_487BF0_00487bf0), 4}};
    for (const W& wr : ws) {
        for (int i = 0; i < 250; ++i) {
            put_tank(m, rng, wr.elem);
            const u64 count = rand_count(rng);
            pair(m, wr.hand, wr.recomp, Args{kStream, count, kTank, rng64(rng)}, seed_of(i, 0x4882u), wr.name);
        }
    }
    // documented: the UV rectangle's vertex pairs (u0, v1), (u1, v1), (u1, v0), (u0, v0) (sub_488390, one particle)
    for (int i = 0; i < 20; ++i) {
        const u32 stride = put_tank(m, rng, 8, false);
        pair(m, PAIR(fn_sub_488390_00488390), Args{kStream, 1, kTank, 0}, seed_of(i, 0x2222u), "sub_488390 rule");
        const u32 dst = r32(m, kStream);
        const u32 u0 = r32(m, kTank + 144), v0 = r32(m, kTank + 148), u1 = r32(m, kTank + 152), v1 = r32(m, kTank + 156);
        const u32 want[8] = {u0, v1, u1, v1, u1, v0, u0, v0};
        for (u32 k = 0; k < 4; ++k) {
            CHECK(r32(m, dst + k * stride) == want[2 * k]);
            CHECK(r32(m, dst + k * stride + 4) == want[2 * k + 1]);
        }
    }
    // documented: the constant colour in every vertex, the constant vertex colours by vertex (sub_4880B0 / sub_487EF0)
    for (int i = 0; i < 40; ++i) {
        const u32 stride = put_tank(m, rng, 4, false);
        const u32 n = pick(rng, {1, 3, 9, 17});
        const bool by_vertex = i % 2 == 1;
        if (by_vertex)
            pair(m, PAIR(fn_sub_487EF0_00487ef0), Args{kStream, n, kTank, 0}, seed_of(i, 0x3334u), "sub_487EF0 rule");
        else
            pair(m, PAIR(fn_sub_4880B0_004880b0), Args{kStream, n, kTank, 0}, seed_of(i, 0x3333u), "sub_4880B0 rule");
        const u32 dst = r32(m, kStream);
        for (u32 k = 0; k < 4 * n; ++k)
            CHECK(r32(m, dst + k * stride) == r32(m, kTank + (by_vertex ? 128 + 4 * (k % 4) : 124)));
    }
}

TEST_CASE("game(render_ptank): the 2-D streamer writers sub_485070 / sub_485E20 and the instance end sub_488B80") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x485070u};
    int fast = 0;
    for (int i = 0; i < 400; ++i) {
        const bool colours = i % 2 == 0;
        const u32 stride = put_tank(m, rng, colours ? 4 : 8);
        // the fast path: the source stride equals four vertices (a streamer copy of count * stride * 4 bytes, the
        // stream quadword aligned)
        if (chance(rng, 40)) {
            w32(m, kTank + (colours ? 48 : 72), 4 * stride);
            w32(m, kStream, kVerts + 16u * (rng() % 16));
            ++fast;
        }
        u64 count = rand_count(rng);
        if (static_cast<s64>(count) < 0 || count > 64) count = rng() % 8;  // the streamer takes the count as a size
        if (colours)
            pair(m, PAIR(fn_sub_485070_00485070), Args{kStream, count, kTank, rng64(rng)}, seed_of(i, 0x4850u), "sub_485070");
        else
            pair(m, PAIR(fn_sub_485E20_00485e20), Args{kStream, count, kTank, rng64(rng)}, seed_of(i, 0x485Eu), "sub_485E20");
    }
    CHECK(fast > 100);
    CHECK(g_dma_transfers > 100);  // the fake DMAC moved the streamers' data
    // sub_488B80: the lock's resource entry (+24); an entry already released (+84 != 0) returns at once in sub_4933D0
    for (int i = 0; i < 50; ++i) {
        fill_random(m, kWorld, 0x400, rng);
        const u32 lock = kWorld + 0x100, entry = kWorld + 0x200;
        w32(m, lock + 24, entry);
        w32(m, entry + 84, 1 + rng() % 100);
        pair(m, PAIR(fn_sub_488B80_00488b80), Args{rng(), lock, rng64(rng), rng64(rng)}, seed_of(i, 0x488Bu), "sub_488B80");
    }
}

TEST_CASE("game(render_ptank): the 2-D attribute writers sub_477610 .. sub_485440 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x477610u};
    struct W {
        const char* name;
        Fn hand, recomp;
        u32 elem, src_off;  // element size, tank offset of the {pointer, stride} pair (0: the fill writers)
        bool count_in_a3;
    };
    const W ws[] = {{"sub_477610", PAIR(fn_sub_477610_00477610), 12, 4, true},
                    {"sub_477A20", PAIR(fn_sub_477A20_00477a20), 4, 36, false},
                    {"sub_477EB0", PAIR(fn_sub_477EB0_00477eb0), 16, 60, false},
                    {"sub_478280", PAIR(fn_sub_478280_00478280), 8, 28, false},
                    {"sub_485110", PAIR(fn_sub_485110_00485110), 4, 0, false},
                    {"sub_485440", PAIR(fn_sub_485440_00485440), 4, 0, false}};
    for (const W& wr : ws) {
        int fast = 0, unrolled = 0;
        for (int i = 0; i < 300; ++i) {
            const u32 stride = put_tank(m, rng, wr.elem);
            u64 count = rand_count(rng);
            // the fast path: a source laid out as the stream (copy), or a packed stream (fill); quadword aligned
            const bool fill = wr.src_off == 0;
            if (!fill && chance(rng, 30)) w32(m, kTank + wr.src_off + 4, stride);
            if (fill ? stride == 4 : r32(m, kTank + wr.src_off + 4) == stride) {
                w32(m, kStream, kVerts + 16u * (rng() % 16));
                if (static_cast<s64>(count) < 0) count = rng() % 8;  // the streamers take the count as a size
                ++fast;
            } else if (static_cast<s64>(count) >= 9) {
                ++unrolled;
            }
            Hw hw;
            if (wr.count_in_a3) {
                hw.gpr_in[GPR_T0] = kTank;
                pair(m, wr.hand, wr.recomp, Args{kStream, rng64(rng), rng64(rng), count}, seed_of(i, 0x4776u), wr.name, hw);
            } else {
                pair(m, wr.hand, wr.recomp, Args{kStream, count, kTank, rng64(rng)}, seed_of(i, 0x4776u), wr.name, hw);
            }
        }
        INFO(wr.name);
        CHECK(fast > 30);
        CHECK(unrolled > 30);
    }
}

// --- the lock callbacks' world ---------------------------------------------------------------------------------
// lock record +0x40, atomic +0x200 (+24 the geometry +0x300, + the plugin offset gp-17792 -> the tank block or the
// count record), the tank block / data at +0x100 (+76 the pipeline record +0x800), the camera +0x600 with its frame
// +0x680 (a clean LTM at +80), the geometry's resEntry array +0x380 (or none: sub_49E5A0 allocates through the RW
// allocator, pointed at the identity stub sub_489950), the RW DMA state of the packet layer (sub_4D5E90 flushes the
// open scratchpad half through the fake DMAC).
constexpr u32 kLock = kWorld + 0x40, kAtomic = kWorld + 0x200, kGeometry = kWorld + 0x300, kResArray = kWorld + 0x380;
constexpr u32 kPipe = kWorld + 0x800, kCamera = kWorld + 0x600, kFrame = kWorld + 0x680;
constexpr u32 kRwCamera = 0x960070u, kRwMalloc = 0x960178u, kRwFree = 0x96017Cu, kIdentityStub = 0x489950u;

void put_rw_dma(Machine& m, std::mt19937& rng) {
    const u32 base = chance(rng, 50) ? 0x70000000u : 0x70002000u;
    w32(m, gpv(-17124), base);
    w32(m, gpv(-17148), chance(rng, 30) ? 0u : base + 16u * (rng() % 8));
    w32(m, gpv(-17128), kWorld + 0x18000u + 16u * (rng() % 16));
    w32(m, gpv(-17208), chance(rng, 70) ? 0u : base + 16u * (rng() % 4));
    fill_random(m, kWorld + 0x18000u, 0x1000, rng);
}

void put_lock_world(Machine& m, std::mt19937& rng) {
    fill_random(m, kWorld, 0x1000, rng);
    fill_floats(m, kTank, 64, rng);
    w32(m, kTank + 76, kPipe);
    w32(m, kTank + 88, pick(rng, {0, 0x8000, 0x20000, 0x28000, rng()}));
    w32(m, kTank + 92, rng() % 12);  // sub_474A80's blend table indices
    w32(m, kTank + 96, rng() % 12);
    // the pipeline record: the buffer ring and 36-byte buffer records
    fill_random(m, kPipe, 0x400, rng);
    w32(m, kPipe + 224, pick(rng, {1, 1, 0, 2}));
    w32(m, kPipe + 228, rng() % 4);
    w32(m, kPipe + 232, pick(rng, {0, 1, 2, 3}));
    for (u32 k = 0; k < 4; ++k) w32(m, kPipe + 312 + 4 * k, chance(rng, 30) ? 0u : kWorld + 0xC00u + 32u * k);
    // the atomic, its geometry and the geometry's resEntry array
    w32(m, kAtomic + 24, kGeometry);
    const u32 off = 16u * (rng() % 4);
    w32(m, gpv(-17504), off);
    w32(m, kGeometry + off, chance(rng, 10) ? 0u : kResArray);
    w32(m, kResArray, chance(rng, 85) ? 1u : 0u);
    w32(m, kResArray + 4, chance(rng, 15) ? 0u : kWorld + 0xD00u);
    w32(m, kRwMalloc, kIdentityStub);
    w32(m, kRwFree, kIdentityStub);
    // the current camera and its frame (a clean LTM)
    w32(m, kRwCamera, kCamera);
    w32(m, kCamera + 4, kFrame);
    std::memset(m.at(kFrame), 0, 0x80);
    w32(m, kFrame + 160, kFrame);
    fill_floats(m, kFrame + 80, 16, rng);
    m.at(kFrame + 3)[0] = 0;
    // the plugin offset to the tank block
    const u32 poff = 16u * (rng() % 4);
    w32(m, gpv(-17792), poff);
    w32(m, kAtomic + poff, kTank);
    put_rw_dma(m, rng);
}

u64 rand_lock_flags(std::mt19937& rng) {
    u64 f = 0;
    for (u64 bit : {0x2ull, 0x2000ull, 0x80ull, 0x80000ull, 0x4ull, 0x4000ull, 0x10ull, 0x40ull, 0x100ull, 0x40000ull,
                    0x100000ull, 0x10000000ull, 0x800000ull})
        if (chance(rng, 30)) f |= bit;
    if (chance(rng, 10)) f |= rng64(rng);
    return f;
}

TEST_CASE("game(render_ptank): the lock callbacks sub_477150 / sub_479170 / sub_479590 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x477150u};
    struct W {
        const char* name;
        Fn hand, recomp;
    };
    const W ws[] = {{"sub_477150", PAIR(fn_sub_477150_00477150)}, {"sub_479170", PAIR(fn_sub_479170_00479170)},
                    {"sub_479590", PAIR(fn_sub_479590_00479590)}};
    for (const W& wr : ws) {
        for (int i = 0; i < 300; ++i) {
            put_lock_world(m, rng);
            Hw hw;
            hw.gpr_in[GPR_T0] = rand_lock_flags(rng);
            pair(m, wr.hand, wr.recomp, Args{kLock, kAtomic, kTank, rng64(rng)}, seed_of(i, 0x4771u), wr.name, hw,
                 {{0, 0x100}});
        }
    }
    // documented: the 3-D lock always asks for the 16-byte component of record +320 (+0 = 1, stride 16)
    for (int i = 0; i < 20; ++i) {
        put_lock_world(m, rng);
        Hw hw;
        hw.gpr_in[GPR_T0] = rand_lock_flags(rng) & ~0x10000000ull;
        pair(m, PAIR(fn_sub_479590_00479590), Args{kLock, kAtomic, kTank, 0}, seed_of(i, 0x9590u), "sub_479590 rule", hw);
        const u32 index = r32(m, kPipe + 228);
        CHECK(r32(m, kLock) == 1);
        CHECK(r32(m, kLock + 16) == r32(m, kPipe + 36 * index + 320));
        CHECK(r32(m, kLock + 20) == 16);
    }
}

TEST_CASE("game(render_ptank): the 3-D instance begin sub_488550 and the format set-up sub_4866C0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x488550u};
    for (int i = 0; i < 400; ++i) {
        put_lock_world(m, rng);
        // the geometry: lock flags +12, morph target +92 (+20 normals, +24), +48 colours, +52 UVs; the tank's count
        // record behind the plugin offset; the first new vertex in $a3
        const u32 target = kWorld + 0x500u, normals = kWorld + 0x8000u;
        w32(m, kGeometry + 92, target);
        w32(m, target + 20, normals);
        fill_random(m, normals, 64 * 48, rng);
        const u32 poff = r32(m, gpv(-17792));
        const u32 count_rec = kWorld + 0x5C0u;
        w32(m, kAtomic + poff, count_rec);
        const u32 count = pick(rng, {0, 1, 5, 9, 16, 30, 64});
        w32(m, count_rec, count);
        // (a negative first vertex would make the original fill through a wild pointer: not a game input)
        const u64 first = pick(rng, {0, 0, 1, 3, 8, 20, 70});
        Hw hw;
        hw.gpr_in[GPR_T0] = rand_lock_flags(rng);
        pair(m, PAIR(fn_sub_488550_00488550), Args{kLock, kAtomic, kTank, first}, seed_of(i, 0x4885u), "sub_488550", hw,
             {{0, 0x100}});
    }
    // sub_4866C0: every format / attribute flag combination
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x400, rng);
        const u32 poff = 16u * (rng() % 4);
        w32(m, gpv(-17792), poff);
        w32(m, kAtomic + poff, kTank);
        u32 fmt = 0, attr = 0;
        for (u32 bit : {0x8u, 0x8000u, 0x20u, 0x4u, 0x1000000u})
            if (chance(rng, 40)) fmt |= bit;
        for (u32 bit : {0x80u, 0x100u, 0x80000u, 0x100000u, 0x2u, 0x40u, 0x40000u, 0x10u})
            if (chance(rng, 30)) attr |= bit;
        // one flag word (+168) holds the format and the attribute bits
        if (chance(rng, 10)) attr |= rng() & ~0x100802Cu;
        w32(m, kTank + 168, fmt | attr);
        pair(m, PAIR(fn_sub_4866C0_004866c0), Args{kAtomic, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 0x4866u),
             "sub_4866C0");
        // documented (ptank.h): +36 the instance begin, +56 the instance end, +40 a position writer
        CHECK(r32(m, kTank + 36) == 0x488550u);
        CHECK(r32(m, kTank + 56) == 0x488B80u);
        const u32 pos = r32(m, kTank + 40);
        const bool pivot = (fmt & 0x1000000u) != 0;
        if (fmt & 0x8) CHECK(pos == (pivot ? 0x487AC0u : 0x487990u));
        else if (fmt & 0x8000) CHECK(pos == (pivot ? 0x486AE0u : 0x486980u));
        else if ((fmt & 0x24) == 0x24) CHECK(pos == (pivot ? 0x4876F0u : 0x487030u));
    }
}

// --- the DMA packet layer's state (as test_render_mesh.cpp builds it) ---------------------------------------------
constexpr u32 kTplLo = 0x965800u, kTplHi = 0x965A40u;
constexpr u32 kWinLo = 0x9B0200u, kWinLen = 0x30000u;  // the DMA buffer window
constexpr u32 kType = gpv(-17212), kFixup = gpv(-17208), kCntTag = gpv(-17204), kPktStart = gpv(-17196);
constexpr u32 kQWrite = gpv(-17192), kQLimit = gpv(-17188), kAlloc = gpv(-17184), kHalfEnd = gpv(-17180);
constexpr u32 kHalfSize = gpv(-17164), kHalf0 = gpv(-17160), kHalf1 = gpv(-17156), kGifTail = gpv(-17152);
constexpr u32 kDmaPtr = gpv(-17128), kSprBase = gpv(-17124), kSprWrite = gpv(-17148);
const std::vector<Region> kRegPacket = {{kTplLo, kTplHi - kTplLo}, {kWinLo, kWinLen}, {0x960000u, 0x200}, {0x77F200u, 0x40},
                                        {0x9649F0u, 0x180}, {0x965A40u, 0x80}, {0x95C4A0u, 48 * 80}, {0, 0x100}};

// A random RW DMA state: no packet / an open VIF packet / one with an open cnt tag / an open GIF packet; the
// scratchpad half sometimes nearly full (the fromSPR copy, moved by the fake DMAC).
void put_packet_dma(Machine& m, std::mt19937& rng) {
    fill_random(m, kWinLo, kWinLen, rng);
    std::memset(m.at(0x9B0A00u), 0, 0x80);  // the two halves' queue blocks: type-0 entries
    std::memset(m.at(0xAEFE00u), 0, 0x80);
    w32(m, kHalfSize, 0x13F400u);
    w32(m, kHalf0, 0x9B0A00u);
    w32(m, kHalf1, 0xAEFE00u);
    w32(m, kHalfEnd, 0xAEFE00u);
    w32(m, kQWrite, 0x9B0A10u + 8u * (rng() % 12));
    w32(m, kQLimit, 0x9B0A78u);
    const u32 spr_base = chance(rng, 50) ? 0x70002000u : 0x70000000u;
    const u32 fill = chance(rng, 30) ? 16u * (rng() % 256) : 8192u - 16u * (24 + rng() % 40);
    w32(m, kSprBase, spr_base);
    const u32 dma = 0x9C0000u + 16u * (rng() % 1024);
    w32(m, kDmaPtr, dma);
    w32(m, kCntTag, 0);
    w32(m, kGifTail, chance(rng, 30) ? 0x9BA000u + 16u * (rng() % 64) : 0);
    switch (rng() % 7) {
    case 0:
        w32(m, kType, 0);
        w32(m, kSprWrite, chance(rng, 50) ? 0 : spr_base + fill);
        w32(m, kAlloc, dma + 16u * (rng() % 64));
        w32(m, kPktStart, 0);
        break;
    case 1:
    case 2:
    case 3:
        w32(m, kType, 0x1101u);
        w32(m, kSprWrite, spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
        break;
    case 4:
    case 5:
        w32(m, kType, 0x80001101u);
        w32(m, kSprWrite, spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
        w32(m, kCntTag, dma - 16u * (1 + rng() % 32));
        break;
    default:
        w32(m, kType, 0x102u);
        w32(m, kSprWrite, spr_base + fill);
        w32(m, kAlloc, dma + fill);
        w32(m, kPktStart, dma - 16u * (rng() % 64));
        break;
    }
    w32(m, kFixup, chance(rng, 25) ? spr_base + 16u * (rng() % 64) : 0);
    fill_random(m, kTplLo, kTplHi - kTplLo, rng);
}

// The packet layer's reference ring (_rwDMAAddPURef): entries are use counts the flush walks; the write index never
// meets the flush index.
void put_ref_ring(Machine& m, std::mt19937& rng, u32 entry) {
    const u32 ring = kWorld + 0x2C00u;
    w32(m, gpv(-17260), ring);
    const u16 size = static_cast<u16>(8 + rng() % 32);
    std::memcpy(m.at(gpv(-20292)), &size, 2);
    for (u32 k = 0; k < 64; ++k) w32(m, ring + 4 * k, entry);
    const u16 write = static_cast<u16>(rng() % (size - 2)), read = static_cast<u16>(size - 1);
    std::memcpy(m.at(gpv(-17268)), &write, 2);
    std::memcpy(m.at(gpv(-17264)), &read, 2);
}

// The bridge's world: PS2All pipe data +0x40, the material pipeline's private data +0x2000 (VU1 code array +0x2400,
// batch size +504), the mesh header +0x2600, the resEntry slot +0x2700 -> resEntry +0x2800 (its DMA block +0x3000),
// a texture +0x2900 (raster 0: not resident) or none, the tank block (count +4, the pipeline record +0x2A00 at +156,
// alpha +180), the camera with its raster, the GS shadows and the reference ring.
constexpr u32 kPipeData = kWorld + 0x40, kMatPvt = kWorld + 0x2000, kCodeArray = kWorld + 0x2400;
constexpr u32 kMeshHeader = kWorld + 0x2600, kSlot = kWorld + 0x2700, kResEntry = kWorld + 0x2800;
constexpr u32 kTexture = kWorld + 0x2900, kPipeRec = kWorld + 0x2A00, kCamRaster = kWorld + 0x6A0;

void put_bridge_world(Machine& m, std::mt19937& rng, bool three_d) {
    fill_random(m, kWorld, 0x4000, rng);
    put_packet_dma(m, rng);
    w32(m, kPipeData + 4, kMatPvt);
    w32(m, kPipeData + 8, kAtomic);
    w32(m, kPipeData + 12, kMeshHeader);
    m.at(kPipeData + 40)[0] = static_cast<u8>(rng());
    w32(m, kPipeData + 48, kSlot);
    w32(m, kPipeData + 64, chance(rng, 60) ? 0u : kTexture);
    w32(m, kTexture, 0);
    w32(m, kMatPvt + 20, rng() & 0x3FFu);
    w32(m, kMatPvt + 24, kCodeArray);
    for (u32 k = 0; k < 4; ++k) w32(m, kCodeArray + 4 * k, chance(rng, 80) ? 0x5CD000u + 0x100 * k : rng());
    w32(m, gpv(-16888), chance(rng, 40) ? 0x5CD000u + 0x100 * (rng() % 4) : rng());
    const u32 batch = pick(rng, {1, 4, 16, 48, 80});
    w32(m, kMatPvt + 504, batch);
    // the tank block
    const u32 poff = 16u * (rng() % 4);
    w32(m, gpv(-17792), poff);
    w32(m, kAtomic + poff, kTank);
    w32(m, kTank + 156, kPipeRec);
    w32(m, kTank + 180, pick(rng, {0, 1, 1, 2}));
    w32(m, kPipeRec + 220, pick(rng, {1, 1, 0}));
    u32 count = pick(rng, {0, 1, 5, 16, 47, 100});
    // the resEntry: fresh (its cluster counts match) or stale (re-instanced by ps2AllInstanceDmaChain: an empty tank, whose
    // re-instance writes only its DMA block's two header words)
    w32(m, kSlot, kResEntry);
    w32(m, kResEntry + 24, rng() % 4);
    w32(m, kResEntry + 28, chance(rng, 40) ? 0 : rng() % 4);
    w32(m, kResEntry + 32, kWorld + 0x3000u);
    const bool stale = chance(rng, 25);
    if (stale) count = 0;
    w32(m, kTank + 4, count);
    const u32 verts = three_d ? 4 * count : count;
    w32(m, kResEntry + 36, stale ? verts + 1 + rng() % 4 : verts);
    w32(m, kResEntry + 52, stale ? 0 : (verts + batch - 1) / batch);
    // the camera
    w32(m, kRwCamera, kCamera);
    w32(m, kCamera + 96, kCamRaster);
    w32(m, kCamRaster + 12, pick(rng, {640, 512, 320}));
    w32(m, kCamRaster + 16, pick(rng, {448, 256, 224}));
    fill_floats(m, kCamera + 112, 2, rng);
    put_ref_ring(m, rng, kResEntry + 24);
}

TEST_CASE("game(render_ptank): the material bridges sub_478520 / sub_479900 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x478520u};
    int opened = 0;
    for (int i = 0; i < 600; ++i) {
        const bool three_d = i % 2 == 1;
        put_bridge_world(m, rng, three_d);
        const auto [h, r] = three_d ? pair(m, PAIR(fn_sub_479900_00479900), Args{kPipeData, rng64(rng), rng64(rng), rng64(rng)},
                                           seed_of(i, 0x4799u), "sub_479900", {}, kRegPacket)
                                    : pair(m, PAIR(fn_sub_478520_00478520), Args{kPipeData, rng64(rng), rng64(rng), rng64(rng)},
                                           seed_of(i, 0x4785u), "sub_478520", {}, kRegPacket);
        if (h.gpr[GPR_V0].u64[0] == 1) ++opened;
        (void)r;
    }
    CHECK(opened > 200);
}

TEST_CASE("game(render_ptank): the streamed format set-up sub_47BF80") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x47BF80u};
    for (int i = 0; i < 300; ++i) {
        fill_random(m, kWorld, 0x400, rng);
        const u32 poff = 16u * (rng() % 4);
        w32(m, gpv(-17792), poff);
        w32(m, kAtomic + poff, kTank);
        u32 flags = 0;
        for (u32 bit : {0x8u, 0x8000u, 0x20u, 0x4u, 0x1000000u, 0x80u, 0x100u, 0x80000u, 0x100000u, 0x2u, 0x40u, 0x40000u, 0x10u})
            if (chance(rng, 35)) flags |= bit;
        if (chance(rng, 10)) flags |= rng();
        w32(m, kTank + 168, flags);
        pair(m, PAIR(fn_sub_47BF80_0047bf80), Args{kAtomic, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 0x47BFu), "sub_47BF80");
        // documented (ptank.h): the same callback slots as sub_4866C0, with the streamed writers
        CHECK(r32(m, kTank + 36) == 0x488550u);
        CHECK(r32(m, kTank + 56) == 0x488B80u);
        if ((flags & 0x10) != 0) CHECK(r32(m, kTank + 52) == 0x486100u);
    }
}

// The object-per-matrix world: the atomic's bounding sphere (+28) and pipeline (+108: a one-node pipeline whose body is
// the identity stub, so RxPipelineExecute runs through), the engine's point transform (the device table at 0x960070 +
// gp-17376, +8 -> 0x4E3EC0, the routine the game installs), a camera with view (+148) and clip (+gp-16972 + 96)
// planes, the matrices (+0x4000), colours (+0x6000) and the vector (+0x6800), the DMA packet layer (sub_46C330).
constexpr u32 kMatrices = kWorld + 0x4000, kColours = kWorld + 0x6000, kVector = kWorld + 0x6800;
constexpr u32 kObjCamera = kWorld + 0x7400;

void put_matrix_world(Machine& m, std::mt19937& rng) {
    fill_random(m, kWorld, 0x8000, rng);
    put_packet_dma(m, rng);
    // the sphere: centre in [-20, 20], radius in (0, 30]
    for (u32 k = 0; k < 3; ++k)
        w32(m, kAtomic + 28 + 4 * k, std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 4001) - 2000) / 100.0f));
    w32(m, kAtomic + 40, std::bit_cast<u32>(static_cast<float>(1 + rng() % 3000) / 100.0f));
    const u32 pipe = kWorld + 0x7000, node = kWorld + 0x7080, def = kWorld + 0x70C0, heap = kWorld + 0x7100;
    w32(m, kAtomic + 108, pipe);
    w32(m, pipe + 8, node);
    w32(m, node, def);
    w32(m, def + 4, kIdentityStub);
    w32(m, gpv(-16832), heap);
    w32(m, heap + 24, 0);
    const u32 dev = kWorld + 0x7200;
    w32(m, gpv(-17376), dev - 0x960070u);
    w32(m, dev + 8, 0x4E3EC0u);
    // the camera's planes: axis normals (sometimes skewed), distances around the spheres
    w32(m, kRwCamera, kObjCamera);
    const u32 clip_off = 0x100;
    w32(m, gpv(-16972), clip_off);
    for (u32 base : {kObjCamera + 148, kObjCamera + clip_off + 96}) {
        for (u32 p = 0; p < 6; ++p) {
            float n[3] = {0, 0, 0};
            n[p / 2] = (p & 1) ? -1.0f : 1.0f;
            if (chance(rng, 20)) n[(p / 2 + 1) % 3] = static_cast<float>(static_cast<s32>(rng() % 200) - 100) / 100.0f;
            for (u32 k = 0; k < 3; ++k) w32(m, base + 20 * p + 4 * k, std::bit_cast<u32>(n[k]));
            w32(m, base + 20 * p + 12, std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 8001) - 2000) / 100.0f));
        }
    }
    // matrices: random floats, the flags word (+12) orthonormal (3) or not
    fill_floats(m, kMatrices, 64 * 16, rng);
    for (u32 i = 0; i < 64; ++i) {
        w32(m, kMatrices + 64 * i + 12, pick(rng, {3, 3, 0, 1, 2}) | (rng() & ~3u & 0xFF00u));
        for (u32 k = 0; k < 3; ++k)  // positions near the frusta
            w32(m, kMatrices + 64 * i + 48 + 4 * k,
                std::bit_cast<u32>(static_cast<float>(static_cast<s32>(rng() % 6001) - 3000) / 100.0f));
    }
    fill_floats(m, kVector, 3, rng);
}

TEST_CASE("game(render_ptank): the object-per-matrix draws sub_47B280 / sub_47B750 equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x47B280u};
    int drawn = 0, batches = 0;
    for (int i = 0; i < 300; ++i) {
        put_matrix_world(m, rng);
        const u64 count = pick(rng, {0, 1, 2, 5, 20, 47, 48, 49, 60});
        const std::vector<u8> records = m.bytes(0x95C4A0u, 48 * 80);
        const u32 ctx_word = r32(m, 0x965A80u);  // RxPipelineExecute's context words (cleared by each run)
        w32(m, 0x965A80u, 0xDEADBEEFu);
        (void)ctx_word;
        if (i % 2 == 0)
            pair(m, PAIR(fn_sub_47B280_0047b280), Args{kAtomic, kMatrices, count, kColours}, seed_of(i, 0x47B2u), "sub_47B280",
                 {}, kRegPacket);
        else
            pair(m, PAIR(fn_sub_47B750_0047b750), Args{kAtomic, kMatrices, count, kVector}, seed_of(i, 0x47B7u), "sub_47B750",
                 {}, kRegPacket);
        if (m.bytes(0x95C4A0u, 48 * 80) != records) ++drawn;  // a visible matrix reached the records
        if (r32(m, 0x965A80u) != 0xDEADBEEFu) ++batches;       // RxPipelineExecute ran
    }
    MESSAGE("object-per-matrix pairs with records: " << drawn << ", with a pipeline run: " << batches);
    CHECK(drawn > 60);
    CHECK(batches > 60);
}

constexpr u32 kOneStub = 0x469A90u;  // `jr ra; li v0, 1`

TEST_CASE("game(render_ptank): the instance runner sub_4861B0 drives the 3-D lock and writers (real call chain)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4861B0u};
    int written = 0;
    for (int i = 0; i < 400; ++i) {
        put_lock_world(m, rng);
        // the tank's callbacks: the 3-D lock (or the identity stub, or none) as instance begin, real writers, the
        // instance end (non-leaf: its tail call sub_4933D0 spills $ra / $s0 below the $sp it gets; the geometry's
        // +84 is set, so it returns at once)
        w32(m, kTank + 36, pick(rng, {0x479590u, 0x479590u, kIdentityStub, 0}));
        w32(m, kTank + 40, pick(rng, {0x486980u, 0x487990u, 0x486C80u, 0}));
        w32(m, kTank + 44, pick(rng, {0x488390u, 0x488260u, 0}));
        w32(m, kTank + 48, pick(rng, {0x4880B0u, 0x487E80u, 0}));
        w32(m, kTank + 52, pick(rng, {0x4884A0u, 0}));
        w32(m, kTank + 56, pick(rng, {0x488B80u, 0}));
        w32(m, kGeometry + 84, 1 + rng() % 8);
        w32(m, kTank, rng() % 12);  // the tank's own count (flags 0x1E8000)
        // the pipeline records' component pointers: vertex streams in the world
        for (u32 k = 0; k < 4; ++k) {
            w32(m, kPipe + 36 * k + 320, kWorld + 0x10000u + 0x800u * k);
            w32(m, kPipe + 36 * k + 340, kWorld + 0x12000u + 0x400u * k);
            w32(m, kPipe + 36 * k + 352, kWorld + 0x13000u + 0x400u * k);
        }
        const u64 count = pick(rng, {0, 1, 3, 8, 12});
        const u64 flags = chance(rng, 30) ? 0x8000u : rand_lock_flags(rng) & ~0x10000000ull;
        const std::vector<u8> before = m.bytes(kWorld + 0x10000u, 0x4000);
        pair(m, PAIR(fn_sub_4861B0_004861b0), Args{kAtomic, kTank, count, flags}, seed_of(i, 0x4861u), "sub_4861B0", {},
             {{0, 0x100}});
        if (m.bytes(kWorld + 0x10000u, 0x4000) != before) ++written;
    }
    MESSAGE("sub_4861B0 pairs whose writers wrote vertices: " << written);
    CHECK(written > 50);
}

TEST_CASE("game(render_ptank): the render callbacks sub_474160 / sub_488B90 and the GS words sub_474A80 / sub_4749A0") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x474160u};
    for (int i = 0; i < 300; ++i) {
        put_lock_world(m, rng);
        // RwRenderStateGet / Set: stand-ins; the tank's callbacks: stubs, the format set-up, the blend-state render
        // (non-leaf, nesting another callback)
        w32(m, 0x960094u, pick(rng, {kIdentityStub, kOneStub}));
        w32(m, 0x960090u, pick(rng, {kIdentityStub, kOneStub}));
        w32(m, kTank + 4, pick(rng, {0, 1, 5}) | (chance(rng, 5) ? 0x80000000u : 0));
        w32(m, kTank + 28, pick(rng, {0, kIdentityStub}));
        w32(m, kTank + 32, pick(rng, {0, kIdentityStub, kOneStub}));
        w32(m, kTank + 16, pick(rng, {kIdentityStub, 0x4866C0u, 0x488B90u}));
        w32(m, kTank + 80 + 100, pick(rng, {0, 1}));
        w32(m, kTank + 100, pick(rng, {0, 1}));
        if (i % 2 == 0)
            pair(m, PAIR(fn_sub_474160_00474160), Args{kAtomic, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 0x4741u),
                 "sub_474160");
        else
            pair(m, PAIR(fn_sub_488B90_00488b90), Args{kAtomic, kTank, rng64(rng), rng64(rng)}, seed_of(i, 0x488Bu), "sub_488B90");
    }
    // sub_474A80: every blend pair, in range and out of range; sub_4749A0: every address-mode pair, with or without a
    // texture
    for (int i = 0; i < 400; ++i) {
        put_lock_world(m, rng);
        w32(m, kTank + 92, rng() % 11);
        w32(m, kTank + 96, rng() % 11);
        if (i % 2 == 0) {
            pair(m, PAIR(fn_sub_474A80_00474a80), Args{kTank, rng64(rng), rng64(rng), rng64(rng)}, seed_of(i, 0x474Au), "sub_474A80");
        } else {
            const u32 tex = kWorld + 0xE00u;
            w32(m, tex + 80, (rng() & ~0xFF00u) | ((rng() % 6) << 8) | ((rng() % 6) << 12));
            pair(m, PAIR(fn_sub_4749A0_004749a0), Args{kTank, chance(rng, 15) ? 0u : tex, rng64(rng), rng64(rng)},
                 seed_of(i, 0x4749u), "sub_4749A0");
        }
    }
}

TEST_CASE("game(render_ptank): pair count") { MESSAGE("render_ptank pairs so far: " << g_pairs); }

#else
TEST_CASE("game(render_ptank): replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: P3FES_GAME_HAVE_GENERATED=0");
}
#endif
