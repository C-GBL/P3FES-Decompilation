// Phase 5 pair tests for slice battle_cmd_menu (game/src/battle/battle_cmd_menu.cpp): every hand-written bcm_main.c
// function and the recompiled body it replaces run on identical guest machines and must leave the same
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31) and cycle count at EVERY check point, in
//     order (a check point may preempt the thread; the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same everything);
//   * whole main RAM (a BaseRange over the 32 MiB, PairRange's exact protocol: only the pages written are copied and
//     compared, and restoring the world copies back only the pages written since) and scratchpad.
//
// Worlds.
//   * The battle snapshot (extracted/_ours/b_5800/eeMemory.bin beside the ELF's tree; the command menu is open there:
//     bcm work 0x1883C20, the battle root, the font system, the item / persona / skill tables of a real save). Its
//     work record holds uninitialised heap fill in the lists no builder has filled yet; the world sanitises those
//     counts (sanitize()), then each pair starts from the restored snapshot, randomises the record's scalar fields
//     (flags, operation bits, debug switches, cursors, list kinds, row kinds / tactics / units, counts within their
//     arrays, the skill / item / persona ids from the save's own lists) and may first run builders (their recompiled
//     bodies) so that the releasers and the drawing queries see real font lines. The font callees run for real
//     (frFontBuildGlyphList and its closure are emitted), so the builders and releasers run to the end.
//   * A synthetic world (the ELF image, a random work record at kWorld with every font-line pointer 0): runs every
//     function whether or not the snapshot is present.
// Documented rules (battle_cmd_menu.h) are checked on the host independently of both bodies.
#include "pair_harness.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle_cmd_menu.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
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
P3FES_DECL_PAIR(fn_sub_201AF0_00201af0)
P3FES_DECL_PAIR(fn_sub_2053C0_002053c0)
P3FES_DECL_PAIR(fn_sub_2054C0_002054c0)
P3FES_DECL_PAIR(fn_sub_205500_00205500)
P3FES_DECL_PAIR(fn_sub_205550_00205550)
P3FES_DECL_PAIR(fn_sub_2055A0_002055a0)
P3FES_DECL_PAIR(fn_sub_2055F0_002055f0)
P3FES_DECL_PAIR(fn_sub_205650_00205650)
P3FES_DECL_PAIR(fn_sub_2056A0_002056a0)
P3FES_DECL_PAIR(fn_sub_205700_00205700)
P3FES_DECL_PAIR(fn_sub_205760_00205760)
P3FES_DECL_PAIR(fn_sub_2079C0_002079c0)
P3FES_DECL_PAIR(fn_sub_207A10_00207a10)
P3FES_DECL_PAIR(fn_sub_207A60_00207a60)
P3FES_DECL_PAIR(fn_sub_207AB0_00207ab0)
P3FES_DECL_PAIR(fn_sub_207B00_00207b00)
P3FES_DECL_PAIR(fn_sub_207B50_00207b50)
P3FES_DECL_PAIR(fn_sub_207BA0_00207ba0)
P3FES_DECL_PAIR(fn_sub_207BF0_00207bf0)
P3FES_DECL_PAIR(fn_sub_207C40_00207c40)
P3FES_DECL_PAIR(fn_sub_207C90_00207c90)
P3FES_DECL_PAIR(fn_sub_207CE0_00207ce0)
P3FES_DECL_PAIR(fn_sub_207D30_00207d30)
P3FES_DECL_PAIR(fn_sub_207D80_00207d80)
P3FES_DECL_PAIR(fn_sub_207DD0_00207dd0)
P3FES_DECL_PAIR(fn_sub_207F70_00207f70)
P3FES_DECL_PAIR(fn_sub_207FC0_00207fc0)
P3FES_DECL_PAIR(fn_sub_2085E0_002085e0)
P3FES_DECL_PAIR(fn_sub_208630_00208630)
P3FES_DECL_PAIR(fn_sub_208680_00208680)
P3FES_DECL_PAIR(fn_sub_2086D0_002086d0)
P3FES_DECL_PAIR(fn_sub_207930_00207930)
P3FES_DECL_PAIR(fn_sub_207960_00207960)
P3FES_DECL_PAIR(fn_sub_208010_00208010)
P3FES_DECL_PAIR(fn_sub_208050_00208050)
P3FES_DECL_PAIR(fn_sub_208130_00208130)
P3FES_DECL_PAIR(fn_sub_2082C0_002082c0)
P3FES_DECL_PAIR(fn_sub_208360_00208360)
P3FES_DECL_PAIR(fn_sub_2083D0_002083d0)
P3FES_DECL_PAIR(fn_sub_208570_00208570)
P3FES_DECL_PAIR(fn_sub_208720_00208720)
P3FES_DECL_PAIR(fn_sub_208790_00208790)
P3FES_DECL_PAIR(fn_sub_208860_00208860)
P3FES_DECL_PAIR(fn_sub_1FFC60_001ffc60)
P3FES_DECL_PAIR(fn_sub_201730_00201730)
P3FES_DECL_PAIR(fn_sub_201780_00201780)
P3FES_DECL_PAIR(fn_sub_201EF0_00201ef0)
P3FES_DECL_PAIR(fn_sub_2024B0_002024b0)
P3FES_DECL_PAIR(fn_sub_202BC0_00202bc0)
P3FES_DECL_PAIR(fn_sub_202C90_00202c90)
P3FES_DECL_PAIR(fn_sub_203030_00203030)
P3FES_DECL_PAIR(fn_sub_203360_00203360)
P3FES_DECL_PAIR(fn_sub_203760_00203760)
P3FES_DECL_PAIR(fn_sub_203990_00203990)
P3FES_DECL_PAIR(fn_sub_203B70_00203b70)
P3FES_DECL_PAIR(fn_sub_203DE0_00203de0)
P3FES_DECL_PAIR(fn_sub_204000_00204000)
P3FES_DECL_PAIR(fn_sub_204760_00204760)
P3FES_DECL_PAIR(fn_sub_204AF0_00204af0)
P3FES_DECL_PAIR(fn_sub_204BE0_00204be0)
P3FES_DECL_PAIR(fn_sub_205000_00205000)
P3FES_DECL_PAIR(fn_sub_205410_00205410)
P3FES_DECL_PAIR(fn_sub_206310_00206310)
P3FES_DECL_PAIR(fn_sub_206EB0_00206eb0)
P3FES_DECL_PAIR(fn_sub_201880_00201880)
P3FES_DECL_PAIR(fn_sub_201AD0_00201ad0)
P3FES_DECL_PAIR(fn_sub_202A10_00202a10)
P3FES_DECL_PAIR(fn_sub_203410_00203410)
P3FES_DECL_PAIR(fn_sub_206170_00206170)
P3FES_DECL_PAIR(fn_sub_206E40_00206e40)
P3FES_DECL_PAIR(fn_sub_207010_00207010)
P3FES_DECL_PAIR(fn_sub_207E20_00207e20)
P3FES_DECL_PAIR(fn_sub_207F10_00207f10)
P3FES_DECL_PAIR(fn_sub_2025E0_002025e0)
P3FES_DECL_PAIR(fn_sub_2031C0_002031c0)
P3FES_DECL_PAIR(fn_sub_203C30_00203c30)
P3FES_DECL_PAIR(fn_sub_204CC0_00204cc0)
P3FES_DECL_PAIR(fn_sub_205D60_00205d60)
P3FES_DECL_PAIR(fn_sub_2060B0_002060b0)
P3FES_DECL_PAIR(fn_sub_206F70_00206f70)
P3FES_DECL_PAIR(fn_sub_207340_00207340)
P3FES_DECL_PAIR(fn_sub_2078A0_002078a0)
P3FES_DECL_PAIR(fn_sub_208460_00208460)
P3FES_DECL_PAIR(fn_sub_2016B0_002016b0)
P3FES_DECL_PAIR(fn_sub_201A50_00201a50)
P3FES_DECL_PAIR(fn_sub_201B50_00201b50)
P3FES_DECL_PAIR(fn_sub_201C30_00201c30)
P3FES_DECL_PAIR(fn_sub_201D10_00201d10)
P3FES_DECL_PAIR(fn_sub_201E00_00201e00)
P3FES_DECL_PAIR(fn_sub_202010_00202010)
P3FES_DECL_PAIR(fn_sub_202D70_00202d70)
P3FES_DECL_PAIR(fn_sub_203850_00203850)
P3FES_DECL_PAIR(fn_sub_204480_00204480)
P3FES_DECL_PAIR(fn_sub_2065A0_002065a0)
P3FES_DECL_PAIR(fn_sub_206740_00206740)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace bc = p3fes::game::bcm;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }
#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

constexpr u32 kGpAddr = 0x7D2CF0u;
constexpr u32 gp(s32 off) { return kGpAddr + static_cast<u32>(off); }
constexpr u32 kWorld = 0x01810000u;      // the synthetic world's work record (0x7800 bytes)
constexpr u32 kWorldBattle = 0x01818000u; // the synthetic battle root
constexpr u32 kWorldRec = 0x01818800u;    // the colour record of sub_208570
constexpr u32 kRasterCallback = 0x009600F4u;  // the RW device's raster-create callback slot
constexpr bool kStubRasterCallback = false;

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
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }
// A 32-bit value as a register argument, sometimes with garbage in the upper half (the bodies take whole registers).
u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 20) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }

std::vector<u8> bcm_snapshot(const char* dir) {  // (the test's own reader, apart from stand_ins.h's read_snapshot)
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}
const std::vector<u8>& snapshot_b5800() {
    static const std::vector<u8> s = bcm_snapshot("b_5800");
    return s;
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

class BcmHooks final : public RtHooks {
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
    // The register files of the first kMaxSnaps check points are kept (a long callee loop would exhaust memory); all
    // are counted. (A hook may not throw here: guest::backedge is noexcept.)
    static constexpr std::size_t kMaxSnaps = 8192;
    std::size_t checks = 0;
    void check_events(EEContext& ctx) override {
        ++checks;
        if (snaps.size() < kMaxSnaps) snaps.push_back(snap(ctx));
    }
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
    std::size_t checks = 0;
    std::vector<Snap> snaps;
    Snap end;
};

const char* g_current = "";  // the pair running (named when a callee ends the process)

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed) {
    BcmHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    } catch (const std::exception& e) {
        std::fprintf(stderr, "run_one: %s: exception %s\n", g_current, e.what());
        throw;
    }
    Run r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.syscalls = h.syscalls;
    r.checks = h.checks;
    r.snaps = std::move(h.snaps);
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;
};
std::map<std::string, Stats> g_stats;

// The live world's RAM (World::init): its base image and the pair protocol on one tracker (write_tracker.h BaseRange:
// restoring the world copies back only the pages written since, not 32 MiB per pair).
BaseRange* g_ram = nullptr;

// Both bodies from the same guest state; afterwards the recompiled run's memory is in place.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    g_current = what;
    std::set_terminate([] {
        std::fprintf(stderr, "terminate in %s\n", g_current);
        std::abort();
    });
    if (g_ram == nullptr) FAIL("pair() outside a World (no BaseRange)");
    BaseRange& ram = *g_ram;
    const std::vector<u8> spr0(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    Run h = run_one(m, hand, args, seed);
    const std::vector<u8> spr_h(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    std::memcpy(m.mem.scratchpad(), spr0.data(), spr0.size());
    ram.between();
    Run r = run_one(m, recomp, args, seed);
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
    }
    INFO(std::string(what) << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " seed=" << seed);
    REQUIRE(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.checks == r.checks);
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
        INFO(std::string(r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first) << " hand " << unsigned(ram.first_body_byte(first))
                                                  << " recomp " << unsigned(m.mem.main_ram()[first]));
        CHECK(false);
    }
    CHECK(std::memcmp(spr_h.data(), m.mem.scratchpad(), spr_h.size()) == 0);
    return r;
}

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// --- the worlds -----------------------------------------------------------------------------------------------------
// Capacities of the record's arrays (battle_cmd_menu.h): counts stay inside them.
struct World {
    Machine m;
    bool snapshot = false;
    std::unique_ptr<BaseRange> base;  // main RAM of the world before each pair (after m: destroyed first)
    u32 work = 0;
    ~World() {
        if (base && g_ram == base.get()) g_ram = nullptr;
    }

    // Builds the base: the snapshot (sanitised) or the synthetic world. False when the ELF is missing.
    bool init(bool use_snapshot) {
        if (m.load_elf(elf_path())) return false;
        const std::vector<u8>& s = snapshot_b5800();
        snapshot = use_snapshot && !s.empty();
        if (snapshot) {
            std::memcpy(m.mem.main_ram(), s.data(), s.size());
            work = load32(m, gp(bc::kGpWork));
            if (work == 0) snapshot = false;
        }
        if (snapshot) {
            sanitize();
            // A glyph-cache miss creates a raster through the RW device's raster callback (0x9600F4 -> sub_4DE0A0: GS
            // image reads, DMA): point it at an emitted stub with defined behaviour (sub_4B3710: `jr ra; move v0, a1`),
            // so the font layer runs on past it in both bodies.
            if (kStubRasterCallback && load32(m, kRasterCallback) == 0x4DE0A0u) store32(m, kRasterCallback, 0x4B3710u);
        } else {
            work = kWorld;
            std::mt19937 rng{0xBC3u};
            for (u32 off = 0; off < 0x7800u; off += 4) store32(m, kWorld + off, rng());
            for (u32 off = 0; off < 0x800u; off += 4) store32(m, kWorldBattle + off, rng());
            store32(m, kWorldBattle + 336, 0);  // no units
            store32(m, gp(bc::kGpWork), kWorld);
            store32(m, gp(bc::kGpBattle), kWorldBattle);
            sanitize();
            clear_lines();
        }
        base = std::make_unique<BaseRange>(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        g_ram = base.get();
        return true;
    }
    void restore() { base->restore(); }
    u32 w(s32 off) const { return load32(m, work + static_cast<u32>(off)); }
    void set(s32 off, u32 v) { store32(m, work + static_cast<u32>(off), v); }

    // The counts of the lists no builder filled yet hold heap fill (0x80000000 / 0x55555555 ...): make them empty, and
    // the cursors small.
    void sanitize() {
        for (s32 off : {bc::kItemLineCount, bc::kItemCount, bc::kPersonaLineCount, bc::kPersonaCount, bc::kTacticLineCount,
                        bc::kAnalyzeLineCount})
            set(off, 0);
        if (w(bc::kSkillCount) > 4) set(bc::kSkillCount, 0);
        if (w(bc::kTargetCount) > 6) set(bc::kTargetCount, 0);
        set(bc::kTargetLineCount, 0);
        for (s32 off = 30280; off < 30608; off += 4) set(off, 0);
        // line pointers no list owns (the skill lines and the skill title of the open skill window are real)
        for (s32 off = bc::kSkillLines + 4 * static_cast<s32>(w(bc::kSkillCount)); off < bc::kSkillTitle; off += 4) set(off, 0);
        for (s32 off = bc::kItemLines; off < bc::kItems; off += 4) set(off, 0);
        for (s32 off = bc::kPersonaLines; off < bc::kPersonaLineCount; off += 4) set(off, 0);
        for (s32 off = bc::kTargetLines; off < bc::kTargetCount; off += 4) set(off, 0);
        for (s32 off = bc::kTacticLines; off < bc::kTacticLineCount; off += 4) set(off, 0);
        for (s32 off = bc::kAnalyzeLines; off < bc::kAnalyzeLineCount; off += 4) set(off, 0);
        set(bc::kItemTitle, 0);
        set(bc::kTitleLine, 0);
        set(bc::kTitleLine2, 0);
    }
    // The synthetic world has no font lines: every line pointer 0.
    void clear_lines() {
        for (s32 off = bc::kSkillLines; off < bc::kItems; off += 4) set(off, 0);
        for (s32 off = bc::kPersonaLines; off < bc::kTargets; off += 4) set(off, 0);
        for (s32 off = bc::kTargetLines; off < bc::kTargetCount; off += 4) set(off, 0);
        for (s32 off = bc::kTacticLines; off < bc::kPanel; off += 4) set(off, 0);
        set(bc::kItemTitle, 0);
        set(bc::kSkillTitle, 0);
        set(bc::kHelpLine, 0);
    }

    // Scalar fields of the record at random (pointers and font lines stay as the base has them).
    void mutate(std::mt19937& rng) {
        u32 flags = w(bc::kFlags);
        constexpr u32 kBuiltBits = 0x1Eu | 0x1000u | 0x2000u | 0x800000u;  // a list's lines exist
        for (unsigned b = 0; b < 32; ++b)
            if (chance(rng, (kBuiltBits >> b) & 1u ? 5 : 20)) flags ^= 1u << b;
        set(bc::kFlags, flags);
        // the item list: ids from the battle items 4000..4222 (sometimes any)
        if (chance(rng, 60)) {
            const u32 n = rng() % 10;
            set(bc::kItemCount, n);
            for (u32 i = 0; i < n; ++i)
                store16(m, work + static_cast<u32>(bc::kItems) + 2 * i, static_cast<u16>(4000 + rng() % 223));
        }
        set(bc::kFlags2, chance(rng, 50) ? w(bc::kFlags2) : rng());
        set(bc::kOperation, chance(rng, 30) ? w(bc::kOperation) : rng() & 0xFF);
        set(bc::kListKind, pick(rng, {0u, 0u, 1u, 2u, 3u, rng()}));
        set(bc::kMode, pick(rng, {0u, 1u, 2u, 2u, 3u}));
        set(bc::kWord36, rng());
        set(bc::kDebug, chance(rng, 40) ? 0u : rng() & 0x7F);
        set(30308, rng() % 4);
        set(30360, rng() % 8);
        set(30412, rng() % 8);
        set(30404, rng() % 4);
        set(30456, rng() % 4);
        set(30464, rng() % 8);
        set(30292, rng() % 6);
        if (chance(rng, 50)) set(bc::kTargetCount, rng() % 7);
        for (u32 i = 0; i < 6; ++i) {
            const s32 row = bc::kTargets + 24 * static_cast<s32>(i);
            if (chance(rng, 50)) set(row + bc::kRowKind, pick(rng, {0u, 1u, 1u, 2u, 3u}));
            if (chance(rng, 30)) set(row + bc::kRowFlags, rng() & 3);
            if (chance(rng, 30)) set(row + bc::kRowTactic, pick(rng, {1u, 2u, 7u, 7u, 10u, rng() % 12}));
            if (chance(rng, 30)) store16(m, work + static_cast<u32>(row + bc::kRowPcId), static_cast<u16>(1 + rng() % 10));
        }
    }
};

// --- the specs ------------------------------------------------------------------------------------------------------
enum class Arg { none, item, skill, pc, record, value, work };
// A prelude runs recompiled builders first (results kept), so releasers and refreshers see real font lines and rows.
enum class Pre { none, skills, items, personas, rows, row_lines, any };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
    Pre pre;
};
#define SPEC(name, kind) {#name, PAIR(name), Arg::kind, Pre::none}
#define SPECP(name, kind, pre) {#name, PAIR(name), Arg::kind, Pre::pre}
const Spec kSpecs[] = {
    SPEC(fn_sub_201AF0_00201af0, none),
    SPEC(fn_sub_2053C0_002053c0, none),
    SPEC(fn_sub_2054C0_002054c0, none),
    SPEC(fn_sub_205500_00205500, none),
    SPEC(fn_sub_205550_00205550, none),
    SPEC(fn_sub_2055A0_002055a0, none),
    SPEC(fn_sub_2055F0_002055f0, skill),
    SPEC(fn_sub_205650_00205650, item),
    SPEC(fn_sub_2056A0_002056a0, none),
    SPEC(fn_sub_205700_00205700, none),
    SPEC(fn_sub_205760_00205760, none),
    SPEC(fn_sub_2079C0_002079c0, none),
    SPEC(fn_sub_207A10_00207a10, none),
    SPEC(fn_sub_207A60_00207a60, none),
    SPEC(fn_sub_207AB0_00207ab0, none),
    SPEC(fn_sub_207B00_00207b00, none),
    SPEC(fn_sub_207B50_00207b50, none),
    SPEC(fn_sub_207BA0_00207ba0, none),
    SPEC(fn_sub_207BF0_00207bf0, none),
    SPEC(fn_sub_207C40_00207c40, none),
    SPEC(fn_sub_207C90_00207c90, none),
    SPEC(fn_sub_207CE0_00207ce0, none),
    SPEC(fn_sub_207D30_00207d30, none),
    SPEC(fn_sub_207D80_00207d80, none),
    SPEC(fn_sub_207DD0_00207dd0, none),
    SPEC(fn_sub_207F70_00207f70, none),
    SPEC(fn_sub_207FC0_00207fc0, none),
    SPEC(fn_sub_2085E0_002085e0, none),
    SPEC(fn_sub_208630_00208630, none),
    SPEC(fn_sub_208680_00208680, none),
    SPEC(fn_sub_2086D0_002086d0, none),
    SPEC(fn_sub_207930_00207930, item),
    SPEC(fn_sub_207960_00207960, item),
    SPEC(fn_sub_208010_00208010, none),
    SPEC(fn_sub_208050_00208050, none),
    SPEC(fn_sub_208130_00208130, none),
    SPEC(fn_sub_2082C0_002082c0, value),
    SPEC(fn_sub_208360_00208360, none),
    SPEC(fn_sub_2083D0_002083d0, none),
    SPEC(fn_sub_208570_00208570, record),
    SPEC(fn_sub_208720_00208720, none),
    SPECP(fn_sub_208790_00208790, none, rows),
    SPEC(fn_sub_208860_00208860, pc),
    SPEC(fn_sub_2024B0_002024b0, none),
    SPECP(fn_sub_202BC0_00202bc0, none, skills),
    SPEC(fn_sub_203030_00203030, none),
    SPECP(fn_sub_203360_00203360, none, items),
    SPEC(fn_sub_203760_00203760, none),
    SPEC(fn_sub_203990_00203990, none),
    SPECP(fn_sub_203B70_00203b70, none, personas),
    SPECP(fn_sub_203DE0_00203de0, none, personas),
    SPEC(fn_sub_204000_00204000, none),
    SPECP(fn_sub_204760_00204760, none, rows),
    SPECP(fn_sub_204BE0_00204be0, none, row_lines),
    SPECP(fn_sub_205000_00205000, none, row_lines),
    SPEC(fn_sub_206310_00206310, none),
    SPEC(fn_sub_206EB0_00206eb0, none),
    SPEC(fn_sub_201EF0_00201ef0, none),
    SPEC(fn_sub_202C90_00202c90, none),
    SPECP(fn_sub_204AF0_00204af0, none, rows),
    SPEC(fn_sub_205410_00205410, none),
    SPECP(fn_sub_1FFC60_001ffc60, none, any),
    SPEC(fn_sub_201730_00201730, work),
    SPECP(fn_sub_201780_00201780, none, any),
    SPEC(fn_sub_201880_00201880, none),
    SPEC(fn_sub_201AD0_00201ad0, none),
    SPECP(fn_sub_202A10_00202a10, none, skills),
    SPECP(fn_sub_203410_00203410, none, items),
    SPEC(fn_sub_206170_00206170, none),
    SPEC(fn_sub_206E40_00206e40, none),
    SPEC(fn_sub_207010_00207010, none),
    SPEC(fn_sub_207E20_00207e20, none),
    SPEC(fn_sub_207F10_00207f10, none),
    SPECP(fn_sub_2025E0_002025e0, none, skills),
    SPECP(fn_sub_2031C0_002031c0, none, items),
    SPECP(fn_sub_203C30_00203c30, none, personas),
    SPECP(fn_sub_204CC0_00204cc0, none, row_lines),
    SPECP(fn_sub_205D60_00205d60, none, row_lines),
    SPEC(fn_sub_2060B0_002060b0, none),
    SPEC(fn_sub_206F70_00206f70, none),
    SPEC(fn_sub_207340_00207340, none),
    SPEC(fn_sub_2078A0_002078a0, none),
    SPEC(fn_sub_208460_00208460, none),
    SPEC(fn_sub_2016B0_002016b0, none),
    SPEC(fn_sub_201A50_00201a50, none),
    SPECP(fn_sub_201B50_00201b50, none, any),
    SPECP(fn_sub_201C30_00201c30, none, any),
    SPECP(fn_sub_201D10_00201d10, none, any),
    SPECP(fn_sub_201E00_00201e00, none, any),
    SPEC(fn_sub_202010_00202010, none),
    SPEC(fn_sub_202D70_00202d70, none),
    SPEC(fn_sub_203850_00203850, none),
    SPECP(fn_sub_204480_00204480, none, rows),
    SPECP(fn_sub_2065A0_002065a0, none, row_lines),
    SPEC(fn_sub_206740_00206740, none),
};
#undef SPEC
#undef SPECP

Args args_for(Arg kind, std::mt19937& rng, const World& w) {
    switch (kind) {
    case Arg::none: return Args{(static_cast<u64>(rng()) << 32) | rng(), rng(), rng(), rng()};
    case Arg::item: return Args{wide(rng, chance(rng, 85) ? rng() % 0x1000 : rng()), rng(), rng(), rng()};
    case Arg::skill: return Args{wide(rng, pick(rng, {rng() % 464, rng() % 0x200, 463u, 464u, rng()})), rng(), rng(), rng()};
    case Arg::pc: return Args{wide(rng, chance(rng, 85) ? rng() % 12 : rng()), rng(), rng(), rng()};
    case Arg::record: return Args{wide(rng, kWorldRec + 4 * (rng() % 8)), rng(), rng(), rng()};
    case Arg::value: return Args{(static_cast<u64>(rng()) << 32) | rng(), rng(), rng(), rng()};
    case Arg::work: return Args{wide(rng, w.work), rng(), rng(), rng()};
    }
    return {};
}

// Runs a recompiled body for its effect (a prelude step): the machine keeps what it leaves.
void run_recomp(Machine& m, Fn fn, u32 seed) { (void)run_one(m, fn, Args{}, seed); }

void prelude(World& w, Pre pre, std::mt19937& rng) {
    g_current = "prelude";
    Machine& m = w.m;
    const u32 seed = rng();
    switch (pre) {
    case Pre::none: break;
    case Pre::skills: run_recomp(m, &recomp_gen::fn_sub_2024B0_002024b0__recomp, seed); break;
    case Pre::items: run_recomp(m, &recomp_gen::fn_sub_203030_00203030__recomp, seed); break;
    case Pre::personas: run_recomp(m, &recomp_gen::fn_sub_203990_00203990__recomp, seed); break;
    case Pre::rows:
        w.set(bc::kFlags, w.w(bc::kFlags) & ~0x10u);
        run_recomp(m, &recomp_gen::fn_sub_204000_00204000__recomp, seed);
        break;
    case Pre::row_lines:
        w.set(bc::kFlags, w.w(bc::kFlags) & ~0x10u);
        run_recomp(m, &recomp_gen::fn_sub_204000_00204000__recomp, seed);
        run_recomp(m, &recomp_gen::fn_sub_204760_00204760__recomp, seed + 1);
        w.set(30456, rng() % 3);
        w.set(30464, rng() % 6);
        break;
    case Pre::any:
        if (chance(rng, 50)) run_recomp(m, &recomp_gen::fn_sub_2024B0_002024b0__recomp, seed);
        if (chance(rng, 50)) run_recomp(m, &recomp_gen::fn_sub_203030_00203030__recomp, seed + 1);
        if (chance(rng, 50)) run_recomp(m, &recomp_gen::fn_sub_203990_00203990__recomp, seed + 2);
        if (chance(rng, 50)) {
            w.set(bc::kFlags, w.w(bc::kFlags) & ~0x10u);
            run_recomp(m, &recomp_gen::fn_sub_204000_00204000__recomp, seed + 3);
            run_recomp(m, &recomp_gen::fn_sub_204760_00204760__recomp, seed + 4);
        }
        break;
    }
    // persona cursor fields within the list
    if (pre == Pre::personas) {
        const u32 n = w.w(bc::kPersonaCount);
        w.set(30404, n ? rng() % n : 0);
        w.set(30412, n ? rng() % (n + 1) : 0);
    }
}

void run_specs(World& w, std::mt19937& rng, int per_spec) {
    for (const Spec& s : kSpecs) {
        for (int i = 0; i < per_spec; ++i) {
            w.restore();
            const bool null_work = chance(rng, 4);
            w.mutate(rng);
            store32(w.m, gp(bc::kGpWork), w.work);
            prelude(w, s.pre, rng);
            if (null_work) store32(w.m, gp(bc::kGpWork), 0);  // the "work != NULL" assertions
            pair(w.m, s.hand, s.recomp, args_for(s.arg, rng, w), rng(), s.name);
        }
    }
}

void report(const char* what) {
    int pairs = 0, stops = 0;
    std::string always;
    for (const auto& [name, st] : g_stats) {
        pairs += st.pairs;
        stops += st.stops;
        if (st.stops * 2 > st.pairs) {
            always += " " + name.substr(3, 10) + " " + std::to_string(st.stops) + "/" + std::to_string(st.pairs) + " (at";
            for (const auto& [pc, n] : st.stop_at) always += " " + hex64(pc);
            always += ")";
        }
    }
    MESSAGE(std::string(what) << ": " << pairs << " pairs, " << stops << " at a compared missing-function stop; mostly stopped:" << always);
}

// ====================================================================================================================

// printf (0x5225A8) is hand-written since finalB (game/src/fx/finalB.cpp): its forwarder runs the body -- vfprintf into
// the stdout FILE, which waits on the IOP without end (the pair never returns) -- where these pairs ended at it as at
// a function this build does not emit. The stop keeps the stop: both runs end at the call and are compared there
// (StandIns::install_stop). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas) si.install_stop(va, "stopped at, as when it was not emitted");
        scope = std::make_unique<StandInsScope>(si);
    }
};

TEST_CASE("game(battle_cmd_menu): every function against its recompiled body on the synthetic world") {
    World w;
    if (!w.init(false)) {
        MESSAGE("SKIP: cannot load the ELF (set P3FES_ELF)");
        return;
    }
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    g_stats.clear();
    std::mt19937 rng{0xBC31u};
    run_specs(w, rng, 60);
    report("synthetic world");
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(battle_cmd_menu): every function against its recompiled body on the battle snapshot") {
    World w;
    if (!w.init(true)) {
        MESSAGE("SKIP: cannot load the ELF (set P3FES_ELF)");
        return;
    }
    if (!w.snapshot) {
        MESSAGE("SKIP: extracted/_ours/b_5800/eeMemory.bin not found beside the ELF's tree");
        return;
    }
    StopAt stop{0x5225A8u};  // printf: stopped at, as when it was not emitted
    g_stats.clear();
    std::mt19937 rng{0xBC32u};
    run_specs(w, rng, 40);
    report("battle snapshot");
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(battle_cmd_menu): the documented rules") {
    World w;
    if (!w.init(true)) {
        MESSAGE("SKIP: cannot load the ELF (set P3FES_ELF)");
        return;
    }
    std::mt19937 rng{0xBC33u};
    // 1. The debug switches set / clear exactly their bit of +30624; the flag setters exactly theirs of +0.
    const struct {
        Fn hand, recomp;
        s32 off;
        u32 set, clear;
    } kBits[] = {
        {PAIR(fn_sub_2079C0_002079c0), bc::kDebug, 0x1, 0}, {PAIR(fn_sub_207A10_00207a10), bc::kDebug, 0x2, 0},
        {PAIR(fn_sub_207A60_00207a60), bc::kDebug, 0x4, 0}, {PAIR(fn_sub_207AB0_00207ab0), bc::kDebug, 0x8, 0},
        {PAIR(fn_sub_207B00_00207b00), bc::kDebug, 0x10, 0}, {PAIR(fn_sub_207B50_00207b50), bc::kDebug, 0x20, 0},
        {PAIR(fn_sub_207BA0_00207ba0), bc::kDebug, 0x40, 0}, {PAIR(fn_sub_207BF0_00207bf0), bc::kDebug, 0, 0x1},
        {PAIR(fn_sub_207C40_00207c40), bc::kDebug, 0, 0x2}, {PAIR(fn_sub_207C90_00207c90), bc::kDebug, 0, 0x4},
        {PAIR(fn_sub_207CE0_00207ce0), bc::kDebug, 0, 0x8}, {PAIR(fn_sub_207D30_00207d30), bc::kDebug, 0, 0x10},
        {PAIR(fn_sub_207D80_00207d80), bc::kDebug, 0, 0x20}, {PAIR(fn_sub_207DD0_00207dd0), bc::kDebug, 0, 0x40},
        {PAIR(fn_sub_2085E0_002085e0), bc::kFlags, 0x8000000, 0}, {PAIR(fn_sub_208630_00208630), bc::kFlags, 0, 0x8000000},
        {PAIR(fn_sub_208680_00208680), bc::kFlags, 0x10000000, 0}, {PAIR(fn_sub_2086D0_002086d0), bc::kFlags, 0, 0x10000000},
    };
    int bits = 0;
    for (int it = 0; it < 40; ++it)
        for (const auto& b : kBits) {
            w.restore();
            w.mutate(rng);
            store32(w.m, gp(bc::kGpWork), w.work);
            const u32 before = w.w(b.off);
            pair(w.m, b.hand, b.recomp, Args{}, rng(), "bit rule");
            CHECK(w.w(b.off) == ((before | b.set) & ~b.clear));
            ++bits;
        }
    // 2. The selected skill / item / persona: the row under the cursor.
    int sel = 0;
    for (int it = 0; it < 100; ++it) {
        w.restore();
        w.mutate(rng);
        store32(w.m, gp(bc::kGpWork), w.work);
        const u32 s = w.w(30308), i = w.w(30360), p = w.w(30412);
        CHECK(v0_of(pair(w.m, PAIR(fn_sub_205500_00205500), Args{}, rng(), "skill rule")) == load16(w.m, w.work + 44 + 8 * s));
        CHECK(v0_of(pair(w.m, PAIR(fn_sub_205550_00205550), Args{}, rng(), "item rule")) == load16(w.m, w.work + 156 + 2 * i));
        CHECK(v0_of(pair(w.m, PAIR(fn_sub_2055A0_002055a0), Args{}, rng(), "persona rule")) == load16(w.m, w.work + 616 + 8 * p));
        ++sel;
    }
    // 3. sub_2055F0: ids >= 464 -> 0, else bit 1 of byte 1 of the 44-byte row of the table at $gp-18680.
    int skills = 0;
    for (u32 id = 0; id < 470; ++id) {
        w.restore();
        const u32 table = load32(w.m, gp(bc::kGpSkillTable));
        const Run r = pair(w.m, PAIR(fn_sub_2055F0_002055f0), Args{sx(id), 0, 0, 0}, rng(), "skill table rule");
        const u32 want = id >= 464 ? 0u : (w.m.at(table + 44 * id + 1)[0] >> 1) & 1u;
        CHECK(v0_of(r) == want);
        ++skills;
    }
    // 4. sub_208570: rec+0 |= 4, the RGB bytes of the 8 words at +20 cleared, the alphas 0 / 5.
    for (int it = 0; it < 50; ++it) {
        w.restore();
        for (u32 off = 0; off < 64; off += 4) store32(w.m, kWorldRec + off, rng());
        const u32 flags = load32(w.m, kWorldRec);
        pair(w.m, PAIR(fn_sub_208570_00208570), Args{sx(kWorldRec), 0, 0, 0}, rng(), "colour rule");
        CHECK(load32(w.m, kWorldRec) == (flags | 4u));
        for (u32 k = 0; k < 8; ++k) CHECK((load32(w.m, kWorldRec + 20 + 4 * k) & 0xFFFFFFu) == 0u);
        const u8* p = w.m.at(kWorldRec);
        CHECK((p[23] == 0 && p[27] == 0 && p[39] == 0 && p[43] == 0));
        CHECK((p[31] == 5 && p[35] == 5 && p[47] == 5 && p[51] == 5));
    }
    MESSAGE("rules: " << bits << " bit setters, " << sel << " selections, " << skills << " skill ids");
}

TEST_CASE("game(battle_cmd_menu): the navigator comments -- every member, first time and again") {
    // sub_208860 picks the "again" line when sub_2DDC10(id) -- the flag 0x697BD8[id] (datGetFlag) -- is set; both
    // states for every id, and every jump-table case (ids 0..10, and beyond the table).
    World w;
    if (!w.init(true)) {
        MESSAGE("SKIP: cannot load the ELF (set P3FES_ELF)");
        return;
    }
    std::mt19937 rng{0xBC34u};
    constexpr u32 kFlagWords = 0x83A21Cu;  // datGetFlag's bit array
    int runs = 0;
    for (int rep = 0; rep < 3; ++rep)
        for (u32 pc = 0; pc < 13; ++pc)
            for (int said = 0; said < 2; ++said) {
                w.restore();
                // ids 9 and 10 have no flag in the retail table (-1: never "again"); give them one on the last rep so
                // the "again" blocks of their cases run too
                if (rep == 2) {
                    store32(w.m, 0x697BD8u + 4 * 9, 0xB0u);
                    store32(w.m, 0x697BD8u + 4 * 10, 0xB1u);
                }
                const u32 flag = pc < 12 ? load32(w.m, 0x697BD8u + 4 * pc) : 0xFFFFFFFFu;
                if (pc >= 2 && pc < 12 && flag != 0xFFFFFFFFu && flag < 0x1600) {
                    const u32 word = kFlagWords + 4 * (flag / 32);
                    const u32 bit = 1u << (flag % 32);
                    store32(w.m, word, said ? (load32(w.m, word) | bit) : (load32(w.m, word) & ~bit));
                }
                // the member's bad status (sub_16C970: party record 0x834010 + 868 (id - 2), word +16) clear, so the
                // comment is made (any of 0x80371 suppresses it)
                if (pc >= 2 && pc < 12 && rep != 1) store32(w.m, 0x834020u + 868u * (pc - 2), 0);
                pair(w.m, PAIR(fn_sub_208860_00208860), Args{wide(rng, pc), 0, 0, 0}, rng(), "navigator sweep");
                ++runs;
            }
    MESSAGE("navigator sweep: " << runs << " pairs");
}

TEST_CASE("game(battle_cmd_menu): summary") { report("all"); }

}  // namespace

#else
TEST_CASE("game(battle_cmd_menu): no recompiled code in this build") {
    MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF");
}
#endif
