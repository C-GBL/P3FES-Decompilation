// Phase 5 pair tests for slice big_draws (game/src/ui/big_draws.cpp): the title screen's three per-frame draws and the
// date / time HUD's three digit helpers against their recompiled bodies on identical guest machines, which must leave
// the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * guest memory: the title world, .data / .bss, the RW slots, low RAM, the stack around $sp (the live frame, the
//     frames and spills of the run below it), the arena; whole RAM on the snapshots.
// The title world is test_title.cpp's (the seven module works, a title image with its sprite entries and textures, the
// camera, the pads), with the title / menu / wait sprites built by the hand-written initialisers (opTitle_Init
// sub_2692D0, opMenu_Init sub_26D430, opWait_Init sub_26E780) and then every animation word the draws read randomised
// around its thresholds. The sprite set-up helpers the draws call (sub_21CCA0 / sub_21D8E0 / sub_21D950 / sub_21D890 /
// sub_21EAE0), RpRandom, sinf / cosf and the op_res / grid helpers are emitted, so the title draws run to the end.
// The HUD helpers call sprDrawSpriteBasic / sub_115BC0 / sub_115AD0, which allocate through the RW heap slots and are
// not emitted: one case stands them in with recorders (stand_ins.h: each call's arguments, $ra and entry check point
// logged and compared) so the whole bodies run on valid dates (whole RAM, run_pair_si); another runs wild arguments
// up to the first sprite call or the same fault in both bodies.
// Real game data: the title snapshots (extracted/_ours/r3_title_sky3100 / 3315: the op root live) and the dorm, battle
// and M1 snapshots, whole RAM compared. Documented rules (big_draws.cpp) are checked on the host.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/big_draws.h"
#include "p3fes/game/title.h"

#include <array>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
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
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_sub_183840_00183840)
P3FES_DECL_PAIR(fn_sub_183BE0_00183be0)
P3FES_DECL_PAIR(fn_sub_183F60_00183f60)
P3FES_DECL_PAIR(fn_sub_267430_00267430)
P3FES_DECL_PAIR(fn_sub_26A2C0_0026a2c0)
P3FES_DECL_PAIR(fn_sub_26EED0_0026eed0)
#undef P3FES_DECL_PAIR
void fn_sub_2692D0_002692d0(EEContext&);  // opTitle_Init (title slice)
void fn_sub_26D430_0026d430(EEContext&);  // opMenu_Init
void fn_sub_26E780_0026e780(EEContext&);  // opWait_Init
}  // namespace p3fes::recomp_gen

namespace {

namespace tt = p3fes::game::title;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }
#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the title world (free RAM above the arena) ---------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kOpRootW = kWorld + 0x0000u;   // 17712 bytes
constexpr u32 kGmW = kWorld + 0x4800u;
constexpr u32 kResW = kWorld + 0x4900u;
constexpr u32 kTitleW = kWorld + 0x4A00u;    // 4160 bytes
constexpr u32 kLogoW = kWorld + 0x5B00u;
constexpr u32 kMenuW = kWorld + 0x5D00u;     // 7280 bytes
constexpr u32 kWaitW = kWorld + 0x7980u;     // 4472 bytes
constexpr u32 kTasks = kWorld + 0x9000u;     // 12 kwln tasks, 0x80 apart (+28 state, +60 work, +64 list next)
constexpr u32 kNumTasks = 12;
constexpr u32 kTaskWorks = kWorld + 0x9800u; // their work records, 0x40 apart
constexpr u32 kImage = kWorld + 0xA000u;     // the title image: +4 the sprite entries
constexpr u32 kEntries = kWorld + 0xA100u;   // 40 entries of 44 bytes (+0 header, +8 index, +12.. sizes / offsets, +28.. rgba)
constexpr u32 kImgHdr = kWorld + 0xA900u;    // +8 the texture table
constexpr u32 kTexTab = kWorld + 0xA980u;    // 4 texture pointers
constexpr u32 kTexRec = kWorld + 0xAA00u;    // 4 textures of 0x40 bytes (+12 width, +16 height)
constexpr u32 kFadeW = kWorld + 0xAC00u;     // the fade module's work (gp-18740)
constexpr u32 kCamera = kWorld + 0xAD00u;    // gp-19504: +128 the scale the sprite set-ups divide by
constexpr u32 kGrid = kWorld + 0xAE00u;      // sub_269A10: +8 cols, +12 rows, +24 layout
constexpr u32 kVisitor = kWorld + 0xAE40u;   // +0 the function, +4 a word
constexpr u32 kScratch = kWorld + 0xB000u;   // the set-work functions' work argument
constexpr u32 task_of(u32 i) { return kTasks + 0x80u * i; }

constexpr u32 gp(s32 off) { return tt::gp_addr(off); }
constexpr u32 kKwlnList0 = gp(-19596), kKwlnList1 = gp(-19572), kKwlnList2 = gp(-19584);
constexpr u32 kCameraSlot = gp(-19504);
constexpr u32 kScenario = gp(-19788);
constexpr u32 kFadeSlot = gp(-18740);
constexpr u32 kFlagWords = 0x83A21Cu;
constexpr u32 kRwFreeSlot = 0x96017Cu;
// Emitted call targets with defined behaviour: sub_4B3710 (`jr ra; move v0, a1`), sub_188640 (returns 0, ui3),
// sub_1F1C50 (non-leaf: spills $ra below its $sp, returns gp-18968).
constexpr u32 kTargets[] = {0x4B3710u, 0x188640u, 0x1F1C50u};

struct Window {
    u32 va;
    u32 len;
};
const std::vector<Window> kWindows = {
    {kWorld, kWorldSize},              // the title world
    {0x0u, 0x10000u},                  // low RAM: an accessor or callee following a null work pointer writes there
    {0x7C0000u, 0x80000u},             // .data / .bss: the $gp words, the pads, the flags
    {0x950000u, 0x20000u},             // the RW slots
    {kSp - 0x1000u, 0x1100u},          // the stack: frames and spills of the run, and the caller's live frame
    {kArena, kArenaSize},
};
const std::vector<Window> kWholeRam = {};  // snapshot pairs: pair() compares the whole RAM through a PairRange

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
float loadf(const Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.mem.main_ram() + va, 4);
    return f;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void store16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void storef(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
// A 32-bit value as a register argument, sometimes with garbage in the upper half (the bodies take whole registers).
u64 wide(std::mt19937& rng, u32 v) { return chance(rng, 20) ? (static_cast<u64>(rng()) << 32) | v : sx(v); }
u32 pick(std::mt19937& rng, std::initializer_list<u32> v) { return *(v.begin() + rng() % v.size()); }
u32 small(std::mt19937& rng, u32 n) { return chance(rng, 92) ? rng() % n : rng(); }
u32 near(std::mt19937& rng, s32 v) { return static_cast<u32>(v + static_cast<s32>(rng() % 5) - 2); }
u32 task(std::mt19937& rng) { return task_of(rng() % kNumTasks); }
void set_flag(Machine& m, u32 id, bool on) {
    const u32 w = kFlagWords + 4 * (id / 32);
    store32(m, w, on ? (load32(m, w) | (1u << (id % 32))) : (load32(m, w) & ~(1u << (id % 32))));
}
u32 flags_word(std::mt19937& rng) {  // mostly alive (bit 0), the other module bits random
    return (rng() & 0x3Eu) | (chance(rng, 85) ? 1u : 0u) | (chance(rng, 10) ? rng() & ~0x3Fu : 0u);
}

// The seven module work words (8 % null: the accessors' K_Assert paths). Set again before every function of a world:
// the set-work functions point them at their argument and the clear-work functions null them.
void set_gp_words(Machine& m, std::mt19937& rng) {
    const auto work = [&](u32 w) { return chance(rng, 8) ? 0u : w; };
    store32(m, gp(tt::kGpOpRoot), work(kOpRootW));
    store32(m, gp(tt::kGpGmRoot), work(kGmW));
    store32(m, gp(tt::kGpOpRes), work(kResW));
    store32(m, gp(tt::kGpOpTitle), work(kTitleW));
    store32(m, gp(tt::kGpOpLogo), work(kLogoW));
    store32(m, gp(tt::kGpOpMenu), work(kMenuW));
    store32(m, gp(tt::kGpOpWait), work(kWaitW));
}

void random_world(Machine& m, std::mt19937& rng) {
    for (u32 off = 0; off < kWorldSize; off += 4) store32(m, kWorld + off, rng());
    // the kwln tasks: a state nibble 0..3 (rarely invalid -> GetState's printf), mostly on the list
    u32 prev = 0;
    store32(m, kKwlnList0, 0);
    store32(m, kKwlnList1, 0);
    store32(m, kKwlnList2, 0);
    for (u32 r = 0; r < kNumTasks; ++r) {
        const u32 t = task_of(r);
        store32(m, t + 60, kTaskWorks + 0x40u * r);
        store32(m, t + 28, (rng() & ~0xFu) | (chance(rng, 97) ? rng() % 4 : rng() % 16));
        store32(m, t + 64, 0);
        if (chance(rng, 70)) {
            if (prev == 0) store32(m, kKwlnList0, t);
            else store32(m, prev + 64, t);
            prev = t;
        }
    }
    // the $gp words
    set_gp_words(m, rng);
    store32(m, gp(tt::kGpTitleMode), pick(rng, {0u, 1u, rng()}));
    m.at(gp(tt::kGpOpToggle))[0] = static_cast<u8>(pick(rng, {0u, 1u, rng() & 0xFFu}));
    store32(m, gp(tt::kGpMovieSeen), pick(rng, {0u, 1u}));
    store32(m, gp(tt::kGpMcResultA), pick(rng, {0u, 0u, 1u, rng()}));
    store32(m, gp(tt::kGpMcResultB), pick(rng, {0u, 1u}));
    store32(m, kFadeSlot, chance(rng, 5) ? 0u : kFadeW);
    store32(m, kFadeW, rng() & 0xFFu);
    store32(m, kCameraSlot, kCamera);
    storef(m, kCamera + 128, chance(rng, 80) ? 1.0f : static_cast<float>(1 + rng() % 4) * 0.5f);
    store32(m, kRwFreeSlot, kTargets[rng() % 3]);
    store32(m, kScenario, pick(rng, {0u, 0u, 1u, rng()}));
    for (u32 i = 0; i < 176; ++i) store32(m, kFlagWords + 4 * i, chance(rng, 50) ? 0u : rng());
    set_flag(m, tt::kGmFlagReturnToTitle, chance(rng, 50));
    set_flag(m, tt::kGmFlagNoCount, chance(rng, 50));
    // the pads: Cross 0x40, up 0x1000, down 0x4000, the 0x9FF "any" mask, the 0x600 shoulder pair the idle test ignores
    for (u32 off = 0; off < 0x10; off += 2) store16(m, tt::kPadButtons + off, static_cast<u16>(chance(rng, 60) ? 0u : rng()));
    for (u32 pad : {tt::kPadButtons, tt::kPadHeld, tt::kPadPressed, tt::kPadPressed2, tt::kPadRepeat})
        if (chance(rng, 50)) store16(m, pad, static_cast<u16>(pick(rng, {0u, 0x40u, 0x1000u, 0x4000u, 0x600u, 0x8u, 0x5040u})));

    // the image: entries -> header -> texture table -> textures
    store32(m, kImage + 4, kEntries);
    for (u32 i = 0; i < 40; ++i) {
        const u32 e = kEntries + 44 * i;
        store32(m, e + 0, kImgHdr);
        store32(m, e + 8, rng() % 4);
        for (u32 k = 12; k < 28; k += 4) store32(m, e + k, rng() % 512);
    }
    store32(m, kImgHdr + 8, kTexTab);
    for (u32 i = 0; i < 4; ++i) {
        store32(m, kTexTab + 4 * i, kTexRec + 0x40u * i);
        store32(m, kTexRec + 0x40u * i + 12, pick(rng, {64u, 128u, 256u, 512u, 0u}));
        store32(m, kTexRec + 0x40u * i + 16, pick(rng, {64u, 128u, 256u, 448u, 0u}));
    }

    // the op root
    u32 w = kOpRootW;
    store32(m, w + tt::kOpFlags, flags_word(rng));
    store32(m, w + tt::kOpState, chance(rng, 92) ? rng() % 19 : pick(rng, {19u, 20u, rng()}));
    store32(m, w + tt::kOpParent, task(rng));
    for (s32 off : {tt::kOpChild16, tt::kOpChild20, tt::kOpChild24, tt::kOpChild28, tt::kOpMovieTask})
        store32(m, w + off, chance(rng, 10) ? 0u : task(rng));
    store32(m, w + tt::kOpCursor, chance(rng, 90) ? rng() % 4 : static_cast<u32>(static_cast<s32>(rng() % 8) - 3));
    store32(m, w + tt::kOpIdle, chance(rng, 40) ? near(rng, 449) : small(rng, 450));
    store32(m, w + tt::kOpReturnState, pick(rng, {8u, 9u, 17u, 8u, 9u, 17u, rng() % 20}));
    // the game root
    w = kGmW;
    store32(m, w + tt::kGmFlags, flags_word(rng));
    store32(m, w + tt::kGmState, chance(rng, 92) ? rng() % 3 : pick(rng, {3u, rng()}));
    store32(m, w + tt::kGmParent, task(rng));
    for (s32 off : {tt::kGmOpTask, tt::kGmGameTask, tt::kGmWaitTask}) store32(m, w + off, chance(rng, 10) ? 0u : task(rng));
    store32(m, w + tt::kGmMode, pick(rng, {0u, 1u, 0u, 1u, 2u, rng()}));
    // op_res: textures, image
    w = kResW;
    store32(m, w + 0, flags_word(rng));
    store32(m, w + 4, rng() & 7u);
    for (u32 i = 0; i < 14; ++i) store32(m, w + 12 + 4 * i, kTexRec + 0x40u * (rng() % 4));
    store32(m, w + 68, kImage);
    store32(m, w + 72, kImage);
    store32(m, w + 76, kTexRec + 0x40u * (rng() % 4));
    store32(m, w + 80, kTexRec + 0x40u * (rng() % 4));
    // op_title, op_logo
    store32(m, kTitleW + 0, flags_word(rng));
    store32(m, kTitleW + 8, pick(rng, {0u, 1u, rng()}));
    store32(m, kLogoW + 0, flags_word(rng));
    store32(m, kLogoW + 4, pick(rng, {0u, 1u, 0u, 1u, 2u, rng()}));
    store32(m, kLogoW + 272, chance(rng, 50) ? near(rng, 74) : rng() % 100);
    store32(m, kLogoW + 276, pick(rng, {0u, 1u, 2u, 0u, 1u, 2u, 3u, rng()}));
    // op_menu
    store32(m, kMenuW + 0, flags_word(rng));
    store32(m, kMenuW + 2808, chance(rng, 90) ? rng() % 4 : rng() % 16);
    store32(m, kMenuW + 6736, chance(rng, 90) ? rng() % 2 : rng() % 16);
    // op_wait: counters near their wrap points, sometimes negative or huge
    w = kWaitW;
    store32(m, w + 0, flags_word(rng));
    store32(m, w + 4, pick(rng, {0u, 1u, 0u, 1u, 2u, rng()}));
    store32(m, w + 8, chance(rng, 50) ? near(rng, 219) : rng() % 300);
    const s32 wraps[] = {90, 50, 30, 690, 70, 690, 1024, 0, 360, 1024};
    for (u32 i = 0; i < 10; ++i) {
        const u32 off = 12 + 4 * i;
        if (off == 40) {
            store32(m, w + 40, chance(rng, 50) ? near(rng, 189) : rng() % 300);
            continue;
        }
        const u32 v = chance(rng, 60) ? near(rng, wraps[i] - 1)
                      : chance(rng, 50) ? static_cast<u32>(-static_cast<s32>(rng() % 3000))
                                        : rng();
        store32(m, w + off, v);
    }
    // sub_269A10
    store32(m, kGrid + 8, chance(rng, 90) ? rng() % 6 : static_cast<u32>(-static_cast<s32>(rng() % 3)));
    store32(m, kGrid + 12, chance(rng, 90) ? rng() % 6 : static_cast<u32>(-static_cast<s32>(rng() % 3)));
    store32(m, kGrid + 24, pick(rng, {0u, 1u, 0u, 1u, 2u, rng()}));
    store32(m, kVisitor + 0, kTargets[rng() % 3]);
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

// Hooks that record the register file at every check point and at a fatal stop (before the throw unwinds the hand
// version's frames, whose destructors run the epilogue).
class TitleHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    std::vector<Snap> snaps;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
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
        this->what = what ? what : "";
        at_stop = snap(ctx);
        throw rt_test::FatalEvent{pc, what, &ctx};
    }
};

struct Run {
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    int syscalls = 0;
    std::vector<Snap> snaps;
    Snap end;
    std::vector<std::vector<u8>> mem;
};

// GPR / FPR values a pair sets after the randomised context (the HUD helpers' $t0, $f12, $f13).
std::map<unsigned, u64> g_gpr_in;
std::map<unsigned, u32> g_fpr_in;

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Window>& windows) {
    TitleHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();  // the caller's FPRs ($f20.. must survive)
    for (const auto& [r, v] : g_gpr_in) m.ctx.gpr[r].u64[0] = v;
    for (const auto& [f, v] : g_fpr_in) m.ctx.fpr[f] = v;
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    Run r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.what = h.what;
    r.syscalls = h.syscalls;
    r.snaps = std::move(h.snaps);
    r.end = h.stopped ? h.at_stop : snap(m.ctx);
    for (const Window& w : windows) r.mem.push_back(m.bytes(w.va, w.len));
    return r;
}

struct Stats {
    int pairs = 0;
    int stops = 0;
    std::map<u32, int> stop_at;  // missing function -> count
    std::map<std::string, int> why;  // the stop's message -> count
};
std::map<std::string, Stats> g_stats;
const char* g_current = "";

// Both bodies from the same guest state (`base` restores the whole RAM when given, else the windows are saved and
// restored); afterwards the recompiled run's memory is in place. Returns the recompiled run; `hand_out` gets the other.
Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what,
         const std::vector<Window>& windows = kWindows, const std::vector<u8>* base = nullptr, Run* hand_out = nullptr) {
    std::vector<std::vector<u8>> before;
    std::unique_ptr<PairRange> ram;  // snapshot pairs: the whole RAM through a PairRange (only written pages copied)
    const std::vector<Window> none;
    const std::vector<Window>& win = base ? none : windows;
    if (base) {
        std::memcpy(m.at(0), base->data(), base->size());
        ram = std::make_unique<PairRange>(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    } else {
        // Low RAM is what an accessor reads through a null work pointer: keep every word there a world address, so a
        // pointer read from it stays mapped (the recompiled loads stop at an unmapped address, guest::load reads 0).
        for (u32 off = 0; off < 0x10000u; off += 4) store32(m, off, kWorld + 0x100u);
        for (const Window& w : windows) before.push_back(m.bytes(w.va, w.len));
    }
    g_current = what;
    std::set_terminate([] {
        std::fprintf(stderr, "terminate in %s\n", g_current);
        std::abort();
    });
    Run h = run_one(m, hand, args, seed, win);
    if (ram) ram->between();
    else
        for (std::size_t i = 0; i < windows.size(); ++i) std::memcpy(m.at(windows[i].va), before[i].data(), windows[i].len);
    Run r = run_one(m, recomp, args, seed, win);
    if (ram) {
        const std::size_t first = ram->first_difference();
        INFO(what << ": whole RAM: first differing byte at " << hex64(first));
        CHECK(first == ram->size());
        ram.reset();
    }
    Stats& st = g_stats[what];
    ++st.pairs;
    if (r.stopped) {
        ++st.stops;
        ++st.stop_at[r.stop_pc];
        ++st.why[r.what];
    }
    const std::string name(what);
    INFO(name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " seed=" << seed << " stop: hand '" << h.what
              << "' recomp '" << r.what << "'");
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
    for (std::size_t i = 0; i < win.size(); ++i) {
        const auto& a = h.mem[i];
        const auto& b = r.mem[i];
        if (std::memcmp(a.data(), b.data(), a.size()) == 0) continue;
        std::size_t first = 0;
        while (first < a.size() && a[first] == b[first]) ++first;
        INFO("memory window " << hex64(windows[i].va) << ": first differing byte at " << hex64(windows[i].va + first));
        CHECK(false);
    }
    if (hand_out) *hand_out = std::move(h);
    return r;
}


// --- big_draws: the specs, the animation words, the HUD arguments ------------------------------------------------
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
};
#define SPEC(name) {#name, PAIR(name)}
const Spec kTitleSpecs[] = {SPEC(fn_sub_267430_00267430), SPEC(fn_sub_26A2C0_0026a2c0), SPEC(fn_sub_26EED0_0026eed0)};
const Spec kHudSpecs[] = {SPEC(fn_sub_183840_00183840), SPEC(fn_sub_183BE0_00183be0), SPEC(fn_sub_183F60_00183f60)};
#undef SPEC

// The wait screen's two fade grids and their vertex arrays (the free end of the title world: 140 points of 64 bytes each
// for the largest grid, 13 x 10 staggered).
constexpr u32 kFadeObj = kWorld + 0xB100u;
constexpr u32 kFadeVerts = kWorld + 0xB400u;
constexpr u32 kFadeVertsSize = 0x2300u;
static_assert(kFadeVerts + 2 * kFadeVertsSize <= kWorld + kWorldSize);

// One plain run of a (hand-written) function on the machine, outside a pair: the initialisers that build the sprites.
void run_plain(Machine& m, Fn fn) {
    TitleHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{0x1u};
    m.fresh_context(Args{0, 0, 0, 0}, rng);
    try {
        fn(m.ctx);
    } catch (const rt_test::FatalEvent&) {
    }
    std::memset(m.at(kSp - kDeadStack), 0, kDeadStack);
}

// A timer around the thresholds the draws compare it with (negative and far values included).
u32 timer(std::mt19937& rng, std::initializer_list<s32> marks) {
    if (chance(rng, 8)) return rng();
    if (chance(rng, 8)) return static_cast<u32>(-static_cast<s32>(rng() % 50));
    if (chance(rng, 60)) return static_cast<u32>(*(marks.begin() + rng() % marks.size()) + static_cast<s32>(rng() % 7) - 3);
    return rng() % 700;
}

// The title world with the sprites built and the animation words of the three title modules randomised.
void title_world(Machine& m, std::mt19937& rng) {
    random_world(m, rng);
    store32(m, gp(tt::kGpOpRes), kResW);
    store32(m, gp(tt::kGpOpTitle), kTitleW);
    store32(m, gp(tt::kGpOpMenu), kMenuW);
    store32(m, gp(tt::kGpOpWait), kWaitW);
    run_plain(m, &recomp_gen::fn_sub_2692D0_002692d0);
    run_plain(m, &recomp_gen::fn_sub_26D430_0026d430);
    run_plain(m, &recomp_gen::fn_sub_26E780_0026e780);
    const std::initializer_list<s32> marks = {0, 10, 12, 32, 70, 95, 100, 120, 130, 144, 145, 160, 165, 180, 200, 220, 512};
    // op_title: flags (bit 0 alive, bit 2 showing), the fade timer, the page (0 logo, 1 menu)
    store32(m, kTitleW + 0, flags_word(rng) | (chance(rng, 80) ? 4u : 0u));
    store32(m, kTitleW + 4, timer(rng, marks));
    store32(m, kTitleW + 8, pick(rng, {0u, 1u, 0u, 1u, 2u, rng()}));
    // op_menu: flags, the menu timer, the cursors, the items' states and timers
    store32(m, kMenuW + 0, flags_word(rng) | (chance(rng, 50) ? 4u : 0u) | (chance(rng, 50) ? 0x20u : 0u));
    store32(m, kMenuW + 2332, timer(rng, marks));
    store32(m, kMenuW + 2808, chance(rng, 90) ? rng() % 4 : rng() % 16);
    store32(m, kMenuW + 6736, chance(rng, 90) ? rng() % 2 : rng() % 16);
    for (u32 i = 0; i < 4; ++i) {
        store32(m, kMenuW + 2816 + 784 * i, chance(rng, 90) ? rng() % 12 : rng());
        store32(m, kMenuW + 2820 + 784 * i, timer(rng, marks));
    }
    for (u32 i = 0; i < 2; ++i) {
        store32(m, kMenuW + 6752 + 784 * i, chance(rng, 90) ? rng() % 12 : rng());
        store32(m, kMenuW + 6756 + 784 * i, timer(rng, marks));
    }
    // op_wait: flags, the page, the page timer, the animation counters
    store32(m, kWaitW + 0, flags_word(rng) | (chance(rng, 70) ? 4u : 0u) | (chance(rng, 50) ? 8u : 0u));
    store32(m, kWaitW + 4, pick(rng, {0u, 1u, 0u, 1u, 2u, rng()}));
    store32(m, kWaitW + 8, timer(rng, {0, 10, 20, 30, 40, 60, 100, 160, 190, 200, 219, 220}));
    const s32 wraps[] = {90, 50, 30, 690, 70, 690, 1024, 190, 360, 1024};
    for (u32 i = 0; i < 10; ++i) store32(m, kWaitW + 12 + 4 * i, chance(rng, 85) ? rng() % static_cast<u32>(wraps[i]) : rng());
    // The two fade grids +4464 / +4468 (sub_269690(1, 12, 9) objects: heap-built, so opWait_Init stops at their creation
    // in the test build): +0 -> a word holding the vertex array (64-byte vertices the visitors sub_271230 / sub_2716D0
    // write), +8 columns, +12 rows, +24 the layout sub_269A10 walks.
    for (u32 k = 0; k < 2; ++k) {
        const u32 obj = kFadeObj + 0x40u * k, verts = kFadeVerts + kFadeVertsSize * k;
        store32(m, kWaitW + 4464 + 4 * k, obj);
        store32(m, obj + 0, obj + 0x30u);
        store32(m, obj + 0x30u, verts);
        store32(m, obj + 8, chance(rng, 70) ? 12u : rng() % 13);
        store32(m, obj + 12, chance(rng, 70) ? 9u : rng() % 10);
        store32(m, obj + 24, chance(rng, 90) ? rng() % 2 : rng() % 4);
    }
}

// The HUD helpers' arguments: $a0 the HUD sprite file (any pointer: not read before the first sprite call), $a1 the
// colour / alpha byte, $a2 / $a3 month / day, $t0 the day part (sub_183F60), $f12 / $f13 the HUD offset.
Args hud_args(std::mt19937& rng) {
    // (the month loop of clndGetDaysSinceStartFromDate ends only for 1.. as a sign-extended word: 0 or a register with
    // garbage in the upper half would walk ~2^32 months in both bodies)
    const u32 month = chance(rng, 90) ? 1 + rng() % 12 : 13 + rng() % 3;
    const u32 day = chance(rng, 90) ? 1 + rng() % 31 : rng() % 40;
    g_gpr_in[GPR_T0] = chance(rng, 90) ? rng() % 9 : wide(rng, rng());
    float x = chance(rng, 50) ? 0.0f : static_cast<float>(static_cast<int>(rng() % 400) - 200);
    u32 xb;
    std::memcpy(&xb, &x, 4);
    g_fpr_in[12] = xb;
    g_fpr_in[13] = chance(rng, 80) ? 0u : rng();
    return Args{wide(rng, kWorld + 0x100u), wide(rng, rng() & 0xFFu), sx(month), wide(rng, day)};
}

void summary2(const char* tag, std::size_t nspecs) {
    int pairs = 0, stops = 0, complete = 0;
    std::string per;
    for (const auto& [name, st] : g_stats) {
        pairs += st.pairs;
        stops += st.stops;
        if (st.stops < st.pairs) ++complete;
        per += " " + name + " " + std::to_string(st.pairs) + " pairs";
        if (st.stops) {
            per += " (stops at";
            for (const auto& [pc, k] : st.stop_at) per += " " + hex64(pc) + " x" + std::to_string(k);
            int shown = 0;
            for (const auto& [w, k] : st.why) {
                if (++shown > 2) break;
                per += " '" + w.substr(0, w.find(';')) + "' x" + std::to_string(k);
            }
            if (st.why.size() > 2) per += " +" + std::to_string(st.why.size() - 2) + " other messages";
            per += ")";
        }
        per += ";";
    }
    const std::string t(tag);
    MESSAGE(t << ": " << pairs << " pairs over " << nspecs << " functions, " << stops
              << " ended at a compared missing-function stop, " << complete << " functions also returned normally:" << per);
}

}  // namespace

TEST_CASE("game(big_draws): the title draws equal their recompiled bodies on random title worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0xB16D7u};
    g_stats.clear();
    constexpr int kWorlds = 400;
    for (int it = 0; it < kWorlds; ++it) {
        title_world(m, rng);
        for (const Spec& s : kTitleSpecs) {
            if (chance(rng, 4)) set_gp_words(m, rng);  // sometimes a null work: the K_Assert path continues
            pair(m, s.hand, s.recomp, Args{rng(), rng(), rng(), rng()}, rng(), s.name);
        }
    }
    summary2("title draws", std::size(kTitleSpecs));
    CHECK(g_stats.size() == std::size(kTitleSpecs));
}

// The HUD helpers on wild arguments too (garbage upper halves, out-of-range days / months, parts >= 9): without
// stand-ins, so the runs end at the first sprite call or at the same fault in both bodies (compared there).
TEST_CASE("game(big_draws): the HUD helpers on wild arguments, up to the first sprite call") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x4D0Du};
    g_stats.clear();
    for (int it = 0; it < 1000; ++it) {
        if (it % 50 == 0) random_world(m, rng);
        for (const Spec& s : kHudSpecs) pair(m, s.hand, s.recomp, hud_args(rng), rng(), s.name);
    }
    g_gpr_in.clear();
    g_fpr_in.clear();
    summary2("HUD helpers", std::size(kHudSpecs));
}

namespace {
// The alpha byte a draw handed sub_21D950: vertex 0's alpha float (+44 of the sprite's strip) is (float)byte.
int alpha_of(const Machine& m, u32 sprite) { return static_cast<int>(loadf(m, sprite + 44)); }
// (u8)(255 * a) as the host computes it; the EE FPU rounds differently in the last place, so rules allow +-1.
int host_alpha(float a) { return static_cast<int>(static_cast<unsigned>(255.0f * a)) & 0xFF; }
float ramp(s32 t, s32 from, s32 len) {  // 0 before `from`, (t - from) / len, 1 from `from + len` on
    return t < from ? 0.0f : t < from + len ? static_cast<float>(t - from) / static_cast<float>(len) : 1.0f;
}
}  // namespace

TEST_CASE("game(big_draws): the draws follow the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x7E1Eu};
    g_stats.clear();

    // 1. op_title, page 0 (the logo fading in): the fade timer +4 counts to 200 while showing (bit 2), then bit 2 is
    //    cleared; the logo sprite (+16, image entry 14) sits at (188, 144) with alpha ramp(t, 70, 30) of the new timer.
    int titles = 0;
    for (int it = 0; it < 300; ++it) {
        title_world(m, rng);
        const s32 t = static_cast<s32>(rng() % 240) - 5;
        const bool showing = chance(rng, 80);
        store32(m, kTitleW + 0, (load32(m, kTitleW) & ~4u) | 1u | (showing ? 4u : 0u));
        store32(m, kTitleW + 4, static_cast<u32>(t));
        store32(m, kTitleW + 8, 0);
        pair(m, PAIR(fn_sub_267430_00267430), Args{0, 0, 0, 0}, rng(), "title rule");
        const s32 t1 = showing && t < 200 ? t + 1 : t;
        CHECK(static_cast<s32>(load32(m, kTitleW + 4)) == t1);
        CHECK(((load32(m, kTitleW) & 4u) != 0) == (showing && t < 200));
        CHECK(loadf(m, kTitleW + 16 + 0) == 188.0f);
        CHECK(loadf(m, kTitleW + 16 + 4) == 144.0f);
        const int want = host_alpha(ramp(t1, 70, 30));
        INFO("title timer " << t1 << " alpha " << alpha_of(m, kTitleW + 16) << " host " << want);
        CHECK(std::abs(alpha_of(m, kTitleW + 16) - want) <= 1);
        ++titles;
    }

    // 2. opMenuUpdate: the background counters wrap (+2320 % 1300, +2324 % 500, +2328 / +2788 / +2792 / +2796 / +2800
    //    % 150, +2784 % 80), +2804 counts to 40 and then clears flags bit 3; while bit 2 the menu timer +2332 counts to
    //    80 and then clears bit 2; the backdrop (+16) gets alpha ramp(timer, 0, 70).
    int menus = 0;
    for (int it = 0; it < 300; ++it) {
        title_world(m, rng);
        const struct {
            u32 off, mod;
        } wraps[] = {{2320, 1300}, {2324, 500}, {2328, 150}, {2788, 150}, {2784, 80}, {2792, 150}, {2800, 150}, {2796, 150}};
        for (const auto& w : wraps) store32(m, kMenuW + w.off, rng() % w.mod);
        const u32 c2804 = rng() % 45, t = rng() % 90;
        const bool showing = chance(rng, 70);
        store32(m, kMenuW + 2804, c2804);
        store32(m, kMenuW + 2332, t);
        store32(m, kMenuW, (load32(m, kMenuW) & ~0x0Du) | 1u | 8u | (showing ? 4u : 0u));
        std::array<u32, 8> before{};
        for (std::size_t i = 0; i < 8; ++i) before[i] = load32(m, kMenuW + wraps[i].off);
        pair(m, PAIR(fn_sub_26A2C0_0026a2c0), Args{0, 0, 0, 0}, rng(), "menu rule");
        for (std::size_t i = 0; i < 8; ++i) {
            INFO("counter +" << wraps[i].off);
            CHECK(load32(m, kMenuW + wraps[i].off) == (before[i] + 1) % wraps[i].mod);
        }
        CHECK(load32(m, kMenuW + 2804) == (c2804 < 40 ? c2804 + 1 : c2804));
        CHECK(((load32(m, kMenuW) & 8u) != 0) == (c2804 < 40));
        const u32 t1 = showing && t < 80 ? t + 1 : t;
        CHECK(load32(m, kMenuW + 2332) == t1);
        CHECK(((load32(m, kMenuW) & 4u) != 0) == (showing && t < 80));
        const int want = host_alpha(ramp(static_cast<s32>(t1), 0, 70));
        INFO("menu timer " << t1);
        CHECK(std::abs(alpha_of(m, kMenuW + 16) - want) <= 1);
        ++menus;
    }

    // 3. op_wait, page 0: the backdrop sprite (+64) fades in with ramp(timer, 0, 100) (the draw does not move the timer);
    //    page 1: it fades out with 1 - ramp(timer, 0, 40).
    int waits = 0;
    for (int it = 0; it < 300; ++it) {
        title_world(m, rng);
        const u32 page = rng() % 2;
        const s32 t = static_cast<s32>(rng() % 130) - 5;
        store32(m, kWaitW + 4, page);
        store32(m, kWaitW + 8, static_cast<u32>(t));
        pair(m, PAIR(fn_sub_26EED0_0026eed0), Args{0, 0, 0, 0}, rng(), "wait rule");
        CHECK(static_cast<s32>(load32(m, kWaitW + 8)) == t);
        const float a = page == 0 ? ramp(t, 0, 100) : 1.0f - ramp(t, 0, 40);
        INFO("wait page " << page << " timer " << t);
        CHECK(std::abs(alpha_of(m, kWaitW + 64) - host_alpha(a)) <= 1);
        ++waits;
    }

    // 4. The HUD helpers up to their first sprite call (the hand run's registers at the stop): sub_183840 draws the moon
    //    disc (sprite 46) unless the phase tbl_clndMoonPhase[days] ($s2 = days) is 29, when its first sprite is the
    //    phase-29 icon 18; sub_183BE0 starts with '1' (sprite 36, x 515) for months 10..12, else the month's units digit
    //    35 + month % 10 (x 532), tinted (0, 14, 2), alpha max(alpha, 40); sub_183F60 draws the part's name by the jump
    //    table 0x7B66D0 (or 54, the holiday name, for parts 2..5).
    int huds = 0;
    static constexpr u32 kPartSprite[9] = {53, 47, 48, 49, 50, 51, 52, 53, 55};
    for (int it = 0; it < 600; ++it) {
        if (it % 50 == 0) random_world(m, rng);
        Args a = hud_args(rng);
        Run hand;
        pair(m, PAIR(fn_sub_183840_00183840), a, rng(), "hud moon rule", kWindows, nullptr, &hand);
        if (hand.stopped && hand.stop_pc == 0x1159F0u) {
            const u64 phase = hand.end.gpr[GPR_S0].u64[0];  // the lbu of tbl_clndMoonPhase[days]
            INFO("phase " << phase);
            CHECK(phase < 256);
            CHECK(hand.end.gpr[GPR_A2].u64[0] == (phase == 29 ? 18u : 46u));
        }
        a = hud_args(rng);
        pair(m, PAIR(fn_sub_183BE0_00183be0), a, rng(), "hud date rule", kWindows, nullptr, &hand);
        if (hand.stopped && hand.stop_pc == 0x115BC0u) {
            const u32 mo = static_cast<u32>(a[2]);
            INFO("month " << mo);
            CHECK(hand.end.gpr[GPR_A2].u64[0] == (mo >= 10 ? 36u : 35u + mo % 10));
            CHECK(hand.end.gpr[GPR_T1].u64[0] == 14u);
            const s64 al = static_cast<s64>(a[1]);  // `slti at, a1, 40` on the whole register
            CHECK(hand.end.gpr[GPR_A3].u64[0] == (static_cast<u64>(al < 40 ? 40 : al) & 0xFFu));
        }
        a = hud_args(rng);
        const u64 part = g_gpr_in[GPR_T0];
        pair(m, PAIR(fn_sub_183F60_00183f60), a, rng(), "hud part rule", kWindows, nullptr, &hand);
        if (hand.stopped && hand.stop_pc == 0x1159F0u) {
            const u64 s = hand.end.gpr[GPR_A2].u64[0];
            INFO("part " << part << " sprite " << s);
            if (s == 54) CHECK((part >= 2 && part <= 5));
            else CHECK((part < 9 && s == kPartSprite[part]));
        }
        ++huds;
    }
    g_gpr_in.clear();
    g_fpr_in.clear();
    MESSAGE("rules: " << titles << " title, " << menus << " menu, " << waits << " wait pairs, " << huds
                      << " HUD triples");
}

// The HUD helpers past their sprite calls: sprDrawSpriteBasic / sub_115BC0 / sub_115AD0 stood in by recorders (each
// call's $ra, $a0..$a3 / $t0..$t3 and its entry check point are logged and compared), so every path of the three
// bodies runs: the moon phases, the glow counter gp-19708, the phase labels, every weekday and tint, every day part.
// Whole RAM, the whole register file at every check point and at the return, the dead stack, HI/LO.
TEST_CASE("game(big_draws): the HUD helpers run whole with the sprite calls stood in") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5EEDu};
    const WorldSetup setup = [](StandInWorld& w) {
        w.si.install_recorder(0x1159F0u, "sprDrawSpriteBasic", 0x1C00010u);
        w.si.install_recorder(0x115BC0u, "sub_115BC0", 0x1C00020u);
        w.si.install_recorder(0x115AD0u, "sub_115AD0", 0x1C00030u);
    };
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    int pairs = 0;
    std::size_t calls = 0;
    std::map<u64, int> moon_icons, weekday_glyphs, part_names;
    for (int it = 0; it < 1500; ++it) {
        if (it % 100 == 0) random_world(m, rng);
        store32(m, gp(game::big_draws::kGpHudBlink), chance(rng, 90) ? rng() % 42 : rng());  // the glow counter (0..40)
        const Spec& s = kHudSpecs[it % 3];
        Args a = hud_args(rng);
        a[2] = sx(1 + rng() % 12);  // valid dates only: a wild day would fault in both bodies, and a fatal stop
        a[3] = sx(1 + rng() % 31);  // propagates out of run_pair_si
        hw.gpr_in.clear();
        hw.gpr_in[GPR_T0] = g_gpr_in[GPR_T0];  // the day part of sub_183F60
        SiPair p = run_pair_si(m, s.hand, s.recomp, a, rng(), s.name, hw, setup);
        for (const StandInCall& c : p.hand->si.log) {
            if (c.ra == 0x183A10u) ++moon_icons[c.args[2]];      // the phase icon (jal 0x183A08)
            if (c.ra == 0x183F20u) ++weekday_glyphs[c.args[2]];  // the weekday glyph (jal 0x183F18)
            if (it % 3 == 2) ++part_names[c.args[2]];            // sub_183F60's one call
        }
        calls += p.hand->si.log.size();
        ++pairs;
    }
    g_gpr_in.clear();
    g_fpr_in.clear();
    MESSAGE("HUD stand-in pairs: " << pairs << ", " << calls << " sprite calls; " << moon_icons.size()
                                   << " distinct moon icons, " << weekday_glyphs.size() << " weekday glyphs, "
                                   << part_names.size() << " day-part names");
    CHECK(moon_icons.size() >= 16);  // the icons 3..18
    CHECK(weekday_glyphs.size() >= 7);
    CHECK(part_names.size() >= 8);
}

TEST_CASE("game(big_draws): the title, dorm, battle and M1 snapshots") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5A96u};
    g_stats.clear();
    int runs = 0, found = 0;
    for (const char* dir : {"r3_title_sky3100", "r3_title_sky3315", "dorm_replay_4900", "battle_ref_6150", "b_5800", "v_m1"}) {
        const std::vector<u8> snapshot = read_snapshot(dir);
        if (snapshot.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        ++found;
        std::memcpy(m.at(0), snapshot.data(), snapshot.size());
        const bool title = std::string(dir).rfind("r3_title", 0) == 0;
        MESSAGE(dir << ": op_title " << hex64(load32(m, gp(tt::kGpOpTitle))) << ", op_menu "
                    << hex64(load32(m, gp(tt::kGpOpMenu))) << ", op_wait " << hex64(load32(m, gp(tt::kGpOpWait))));
        for (int rep = 0; rep < (title ? 3 : 1); ++rep) {
            for (const Spec& s : kTitleSpecs) {
                if (!title) continue;
                pair(m, s.hand, s.recomp, Args{0, 0, 0, 0}, rng(), s.name, kWholeRam, &snapshot);
                ++runs;
            }
        }
        for (int rep = 0; rep < 4; ++rep)
            for (const Spec& s : kHudSpecs) {
                pair(m, s.hand, s.recomp, hud_args(rng), rng(), s.name, kWholeRam, &snapshot);
                ++runs;
            }
        g_gpr_in.clear();
        g_fpr_in.clear();
    }
    MESSAGE("snapshots: " << found << " found, " << runs << " whole-RAM pairs");
    if (found) summary2("snapshots", std::size(kTitleSpecs) + std::size(kHudSpecs));
}

#else
TEST_CASE("game(big_draws): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
