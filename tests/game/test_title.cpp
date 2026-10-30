// Phase 5 pair tests for slice title (game/src/ui/title.cpp): every hand-written game-root / logo / title function and
// the recompiled body it replaces run on identical guest machines -- a random title world (the seven module works the
// $gp words point at: op root, game root, op_res, op_title, op_logo, op_menu, op_wait; kwln tasks on the kernel's
// lists for the children; a title image with its sprite entries and textures; the fade module's work; a camera; the
// RW free slot; the pad words, the flags, the scenario word; a grid and a visitor for sub_269A10) and a random
// register file -- and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, ACC, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * guest memory: the world, .data / .bss (the $gp words, the pads, the flags), the RW slots, low RAM, the stack
//     around $sp (live frame, the frames and spills of the run below it), the arena.
// The test build emits the small callees (the fade helpers, the sprite set-up helpers sub_21CCA0 / sub_21D3B0 /
// sub_21CD00 / sub_21EAC0 / sub_21EAE0 / sub_21EB80 / sub_21D8E0, the sound-state helpers, the counters), so the
// initialisers run to the end; the big draws, the task creators and the file loader are not emitted (compared stops).
// sub_269A10's visitor points at emitted functions with defined behaviour, one of them a non-leaf that spills the $ra
// it gets below the $sp it gets (sub_1F1C50: the frame / link discipline of the `jalr`).
// Real game data: the title snapshots (extracted/_ours/r3_title_sky3100 / 3315, the dorm route's title) and the dorm,
// battle and M1 snapshots, whole RAM compared. Documented rules (title.h, title.cpp) are checked on the host.
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/title.h"

#include <array>
#include <climits>
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
P3FES_DECL_PAIR(fn_sub_265030_00265030)
P3FES_DECL_PAIR(fn_sub_265B30_00265b30)
P3FES_DECL_PAIR(fn_sub_265BB0_00265bb0)
P3FES_DECL_PAIR(fn_opRoot_UpdateOpTask_00265dc0)
P3FES_DECL_PAIR(fn_opRoot_UpdateOpDrawTask_00265e30)
P3FES_DECL_PAIR(fn_sub_265F80_00265f80)
P3FES_DECL_PAIR(fn_sub_266060_00266060)
P3FES_DECL_PAIR(fn_sub_2660D0_002660d0)
P3FES_DECL_PAIR(fn_sub_266140_00266140)
P3FES_DECL_PAIR(fn_sub_2663C0_002663c0)
P3FES_DECL_PAIR(fn_sub_266430_00266430)
P3FES_DECL_PAIR(fn_gmRoot_UpdateGameRootTask_00266590)
P3FES_DECL_PAIR(fn_sub_266660_00266660)
P3FES_DECL_PAIR(fn_sub_266670_00266670)
P3FES_DECL_PAIR(fn_sub_266690_00266690)
P3FES_DECL_PAIR(fn_sub_266AE0_00266ae0)
P3FES_DECL_PAIR(fn_sub_266B30_00266b30)
P3FES_DECL_PAIR(fn_sub_266BF0_00266bf0)
P3FES_DECL_PAIR(fn_sub_266C50_00266c50)
P3FES_DECL_PAIR(fn_sub_266D70_00266d70)
P3FES_DECL_PAIR(fn_sub_266DC0_00266dc0)
P3FES_DECL_PAIR(fn_sub_266E50_00266e50)
P3FES_DECL_PAIR(fn_sub_2673A0_002673a0)
P3FES_DECL_PAIR(fn_sub_2673F0_002673f0)
P3FES_DECL_PAIR(fn_sub_2692D0_002692d0)
P3FES_DECL_PAIR(fn_sub_2694B0_002694b0)
P3FES_DECL_PAIR(fn_sub_269500_00269500)
P3FES_DECL_PAIR(fn_sub_269550_00269550)
P3FES_DECL_PAIR(fn_sub_2695B0_002695b0)
P3FES_DECL_PAIR(fn_sub_269640_00269640)
P3FES_DECL_PAIR(fn_sub_269A10_00269a10)
P3FES_DECL_PAIR(fn_sub_269C80_00269c80)
P3FES_DECL_PAIR(fn_sub_269CA0_00269ca0)
P3FES_DECL_PAIR(fn_sub_269CC0_00269cc0)
P3FES_DECL_PAIR(fn_sub_269D10_00269d10)
P3FES_DECL_PAIR(fn_sub_269D50_00269d50)
P3FES_DECL_PAIR(fn_sub_26A0F0_0026a0f0)
P3FES_DECL_PAIR(fn_sub_26A1E0_0026a1e0)
P3FES_DECL_PAIR(fn_opMenuSetWork_0026a230)
P3FES_DECL_PAIR(fn_sub_26A280_0026a280)
P3FES_DECL_PAIR(fn_sub_26D430_0026d430)
P3FES_DECL_PAIR(fn_sub_26DA10_0026da10)
P3FES_DECL_PAIR(fn_sub_26DA90_0026da90)
P3FES_DECL_PAIR(fn_sub_26DB30_0026db30)
P3FES_DECL_PAIR(fn_sub_26DBD0_0026dbd0)
P3FES_DECL_PAIR(fn_sub_26DC20_0026dc20)
P3FES_DECL_PAIR(fn_sub_26DC70_0026dc70)
P3FES_DECL_PAIR(fn_sub_26DCC0_0026dcc0)
P3FES_DECL_PAIR(fn_sub_26DD10_0026dd10)
P3FES_DECL_PAIR(fn_sub_26DD60_0026dd60)
P3FES_DECL_PAIR(fn_sub_26DDC0_0026ddc0)
P3FES_DECL_PAIR(fn_sub_26E780_0026e780)
P3FES_DECL_PAIR(fn_sub_26EBF0_0026ebf0)
P3FES_DECL_PAIR(fn_sub_26EC50_0026ec50)
P3FES_DECL_PAIR(fn_sub_26ECA0_0026eca0)
P3FES_DECL_PAIR(fn_sub_26ED40_0026ed40)
P3FES_DECL_PAIR(fn_sub_26EDB0_0026edb0)
P3FES_DECL_PAIR(fn_sub_26EDD0_0026edd0)
P3FES_DECL_PAIR(fn_sub_26EE30_0026ee30)
P3FES_DECL_PAIR(fn_sub_26EE80_0026ee80)
#undef P3FES_DECL_PAIR
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
    // A body walking a snapshot without end is cut at the same check point in both runs (stop pc 0xFFFFFFFF, as
    // handgen_pairs.h): every check point's register file is kept, so an endless walk grew `snaps` until the host
    // ran out of memory (the snapshot case's "bad allocation", 2026-10-29).
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

Run run_one(Machine& m, Fn fn, const Args& args, u32 seed, const std::vector<Window>& windows) {
    TitleHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();  // the caller's FPRs ($f20.. must survive)
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

u64 v0_of(const Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

// A stand-in that ends the run at the callee the way a function this build does not emit does (rt::missing_function):
// datInitNewGame (sub_195DE0, hand-written since finalA) rewrites the whole save data, far outside the windows the
// random-world cases restore between the two runs, so those cases keep stopping at it, as when it was not emitted
// (the snapshot case, restored whole, runs it for real). Installed for the scope of a case.
struct StopAt {
    StandIns si;
    std::unique_ptr<StandInsScope> scope;
    explicit StopAt(std::initializer_list<u32> vas) {
        for (u32 va : vas)
            si.install(va, "stop (as not emitted)", [va](EEContext&, StandIns&, StandInCall&) { rt::missing_function(va); });
        scope = std::make_unique<StandInsScope>(si);
    }
};

// --- the specs: each function with its argument generator --------------------------------------------------------
enum class Arg { none, work, index, item, mode, grid };
struct Spec {
    const char* name;
    Fn hand;
    Fn recomp;
    Arg arg;
};
#define SPEC(name, kind) {#name, PAIR(name), Arg::kind}
const Spec kSpecs[] = {
    SPEC(fn_sub_265030_00265030, none),  SPEC(fn_sub_265B30_00265b30, none),  SPEC(fn_sub_265BB0_00265bb0, none),
    SPEC(fn_opRoot_UpdateOpTask_00265dc0, none),  SPEC(fn_opRoot_UpdateOpDrawTask_00265e30, none),  SPEC(fn_sub_265F80_00265f80, none),
    SPEC(fn_sub_266060_00266060, none),  SPEC(fn_sub_2660D0_002660d0, none),  SPEC(fn_sub_266140_00266140, none),
    SPEC(fn_sub_2663C0_002663c0, none),  SPEC(fn_sub_266430_00266430, none),  SPEC(fn_gmRoot_UpdateGameRootTask_00266590, none),
    SPEC(fn_sub_266660_00266660, mode),  SPEC(fn_sub_266670_00266670, work),  SPEC(fn_sub_266690_00266690, none),
    SPEC(fn_sub_266AE0_00266ae0, none),  SPEC(fn_sub_266B30_00266b30, none),  SPEC(fn_sub_266BF0_00266bf0, index),
    SPEC(fn_sub_266C50_00266c50, index), SPEC(fn_sub_266D70_00266d70, none),  SPEC(fn_sub_266DC0_00266dc0, none),
    SPEC(fn_sub_266E50_00266e50, index), SPEC(fn_sub_2673A0_002673a0, work),  SPEC(fn_sub_2673F0_002673f0, none),
    SPEC(fn_sub_2692D0_002692d0, none),  SPEC(fn_sub_2694B0_002694b0, none),  SPEC(fn_sub_269500_00269500, none),
    SPEC(fn_sub_269550_00269550, none),  SPEC(fn_sub_2695B0_002695b0, none),  SPEC(fn_sub_269640_00269640, none),
    SPEC(fn_sub_269A10_00269a10, grid),  SPEC(fn_sub_269C80_00269c80, none),  SPEC(fn_sub_269CA0_00269ca0, none),
    SPEC(fn_sub_269CC0_00269cc0, work),  SPEC(fn_sub_269D10_00269d10, none),  SPEC(fn_sub_269D50_00269d50, none),
    SPEC(fn_sub_26A0F0_0026a0f0, none),  SPEC(fn_sub_26A1E0_0026a1e0, none),  SPEC(fn_opMenuSetWork_0026a230, work),
    SPEC(fn_sub_26A280_0026a280, none),  SPEC(fn_sub_26D430_0026d430, none),  SPEC(fn_sub_26DA10_0026da10, none),
    SPEC(fn_sub_26DA90_0026da90, item),  SPEC(fn_sub_26DB30_0026db30, item),  SPEC(fn_sub_26DBD0_0026dbd0, none),
    SPEC(fn_sub_26DC20_0026dc20, none),  SPEC(fn_sub_26DC70_0026dc70, none),  SPEC(fn_sub_26DCC0_0026dcc0, none),
    SPEC(fn_sub_26DD10_0026dd10, work),  SPEC(fn_sub_26DD60_0026dd60, none),  SPEC(fn_sub_26DDC0_0026ddc0, none),
    SPEC(fn_sub_26E780_0026e780, none),  SPEC(fn_sub_26EBF0_0026ebf0, none),  SPEC(fn_sub_26EC50_0026ec50, none),
    SPEC(fn_sub_26ECA0_0026eca0, none),  SPEC(fn_sub_26ED40_0026ed40, none),  SPEC(fn_sub_26EDB0_0026edb0, none),
    SPEC(fn_sub_26EDD0_0026edd0, none),  SPEC(fn_sub_26EE30_0026ee30, none),  SPEC(fn_sub_26EE80_0026ee80, none),
};
#undef SPEC

Args args_for(Arg kind, std::mt19937& rng) {
    const u64 r0 = (static_cast<u64>(rng()) << 32) | rng(), r1 = (static_cast<u64>(rng()) << 32) | rng();
    switch (kind) {
    case Arg::none: return Args{r0, r1, rng(), rng()};  // the task updates ignore their task argument
    case Arg::work: return Args{wide(rng, chance(rng, 95) ? kScratch : 0u), r1, rng(), rng()};
    case Arg::index: return Args{wide(rng, chance(rng, 90) ? rng() % 3 : static_cast<u32>(static_cast<s32>(rng() % 8) - 4)), r1, rng(), rng()};
    case Arg::item: return Args{wide(rng, chance(rng, 90) ? rng() % 4 : static_cast<u32>(static_cast<s32>(rng() % 8) - 4)), r1, rng(), rng()};
    case Arg::mode: return Args{r0, r1, rng(), rng()};
    case Arg::grid: return Args{wide(rng, kGrid), wide(rng, kVisitor), rng(), rng()};
    }
    return {};
}

void summary(const char* tag, std::size_t nspecs) {
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
    MESSAGE(tag << ": " << pairs << " pairs over " << nspecs << " functions, " << stops
                << " ended at a compared missing-function stop; " << complete
                << " functions also returned normally; always at a stop (a big callee first):" << always_stopped);
}

// (the test's own reader, kept apart from stand_ins.h's read_snapshot since that header came in with StopAt)
std::vector<u8> title_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    std::vector<u8> v(EEMemory::kMainRamSize);
    f.read(reinterpret_cast<char*>(v.data()), static_cast<std::streamsize>(v.size()));
    if (f.gcount() != static_cast<std::streamsize>(v.size())) return {};
    return v;
}

}  // namespace

TEST_CASE("game(title): every replaced function equals its recompiled body on random title worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    // datInitNewGame; printf and sub_1052B0, the debug-log ring formatter (hand-written since finalB: printf's body,
    // vfprintf into the stdout FILE, allocates the FILE's buffer and waits on the IOP, the formatter advances its ring,
    // both outside the restored windows, so the second run saw another world): stopped at, as when they were not emitted
    StopAt stop{0x195DE0u, 0x5225A8u, 0x1052B0u};
    std::mt19937 rng{0x717E1u};
    g_stats.clear();
    constexpr int kWorlds = 500;
    for (int it = 0; it < kWorlds; ++it) {
        random_world(m, rng);
        for (const Spec& s : kSpecs) {
            set_gp_words(m, rng);
            pair(m, s.hand, s.recomp, args_for(s.arg, rng), rng(), s.name);
        }
    }
    summary("title", std::size(kSpecs));
    CHECK(g_stats.size() == std::size(kSpecs));
}

TEST_CASE("game(title): every op root / game root / logo / wait state, every cursor, every grid layout") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x195DE0u, 0x5225A8u, 0x1052B0u};  // datInitNewGame, printf, sub_1052B0: stopped at, as when not emitted (above)
    std::mt19937 rng{0x5EE7u};
    int runs = 0;
    for (int rep = 0; rep < 25; ++rep) {
        for (u32 s = 0; s < 21; ++s) {  // the op root: every state (19, 20 out of the table)
            for (u32 cur = 0; cur < 5; ++cur) {
                random_world(m, rng);
                store32(m, gp(tt::kGpOpRoot), kOpRootW);
                store32(m, kOpRootW + tt::kOpFlags, (load32(m, kOpRootW) & ~1u) | 1u);
                store32(m, kOpRootW + tt::kOpState, s);
                store32(m, kOpRootW + tt::kOpCursor, cur == 4 ? static_cast<u32>(-1) : cur);
                pair(m, PAIR(fn_sub_265030_00265030), Args{rng(), 0, 0, 0}, rng(), "op state");
                ++runs;
            }
        }
        for (u32 s = 0; s < 4; ++s)
            for (u32 mode = 0; mode < 3; ++mode) {  // the game root
                random_world(m, rng);
                store32(m, gp(tt::kGpGmRoot), kGmW);
                store32(m, kGmW + tt::kGmFlags, load32(m, kGmW) | 1u);
                store32(m, kGmW + tt::kGmState, s);
                store32(m, kGmW + tt::kGmMode, mode);
                pair(m, PAIR(fn_sub_266140_00266140), Args{rng(), 0, 0, 0}, rng(), "gm state");
                pair(m, PAIR(fn_gmRoot_UpdateGameRootTask_00266590), Args{rng(), 0, 0, 0}, rng(), "gm task");
                runs += 2;
            }
        for (u32 logo = 0; logo < 3; ++logo)
            for (u32 st = 0; st < 4; ++st) {  // the logo fades
                random_world(m, rng);
                store32(m, gp(tt::kGpOpLogo), kLogoW);
                store32(m, kLogoW, load32(m, kLogoW) | 1u);
                store32(m, kLogoW + 4, logo);
                store32(m, kLogoW + 276, st);
                pair(m, PAIR(fn_sub_269D50_00269d50), Args{rng(), 0, 0, 0}, rng(), "logo state");
                ++runs;
            }
        for (u32 page = 0; page < 3; ++page) {  // the wait screen
            random_world(m, rng);
            store32(m, gp(tt::kGpOpWait), kWaitW);
            store32(m, kWaitW, load32(m, kWaitW) & ~1u);
            store32(m, kWaitW + 4, page);
            pair(m, PAIR(fn_sub_26DDC0_0026ddc0), Args{rng(), 0, 0, 0}, rng(), "wait page");
            ++runs;
        }
        for (u32 layout = 0; layout < 3; ++layout)
            for (u32 cols = 0; cols < 4; ++cols) {  // the grids
                random_world(m, rng);
                store32(m, kGrid + 8, cols);
                store32(m, kGrid + 12, rng() % 4);
                store32(m, kGrid + 24, layout);
                pair(m, PAIR(fn_sub_269A10_00269a10), Args{sx(kGrid), sx(kVisitor), 0, 0}, rng(), "grid");
                ++runs;
            }
    }
    MESSAGE("sweeps: " << runs << " pairs");
}

TEST_CASE("game(title): the modules follow the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StopAt stop{0x195DE0u};  // datInitNewGame: stopped at, as when it was not emitted
    std::mt19937 rng{0x7171u};

    // 1. set work: the slot gets the work and the work's flags are cleared (a busy slot only asserts); clear work: 0.
    int works = 0;
    for (int it = 0; it < 200; ++it) {
        random_world(m, rng);
        store32(m, kScratch, 0xFFFFFFFFu);
        pair(m, PAIR(fn_sub_269CC0_00269cc0), Args{sx(kScratch), 0, 0, 0}, rng(), "set work rule");
        CHECK(load32(m, kScratch) == 0);
        CHECK(load32(m, gp(tt::kGpOpLogo)) == kScratch);
        pair(m, PAIR(fn_sub_269D10_00269d10), Args{0, 0, 0, 0}, rng(), "clear work rule");
        CHECK(load32(m, gp(tt::kGpOpLogo)) == 0);
        ++works;
    }

    // 2. the menu cursors: the new item's state / timer = 0, the old item's timer = 0, the cursor = the item.
    int selects = 0;
    for (int it = 0; it < 300; ++it) {
        random_world(m, rng);
        store32(m, gp(tt::kGpOpMenu), kMenuW);
        const bool cont = chance(rng, 50);
        const u32 n = cont ? 2 : 4, cursor = cont ? 6736 : 2808, list = cont ? 6752 : 2816;
        const u32 old = rng() % n, item = rng() % n;
        store32(m, kMenuW + cursor, old);
        if (cont) pair(m, PAIR(fn_sub_26DB30_0026db30), Args{sx(item), 0, 0, 0}, rng(), "select rule");
        else pair(m, PAIR(fn_sub_26DA90_0026da90), Args{sx(item), 0, 0, 0}, rng(), "select rule");
        CHECK(load32(m, kMenuW + cursor) == item);
        CHECK(load32(m, kMenuW + list + 784 * item) == 0);
        CHECK(load32(m, kMenuW + list + 784 * item + 4) == 0);
        CHECK(load32(m, kMenuW + list + 784 * old + 4) == 0);
        ++selects;
    }

    // 3. the wait screen's counters wrap like C's % (the compiled division), the fade-in timer stops at 190 and clears
    //    bit 3, the page timer stops at 220 and clears bit 2.
    int counters = 0;
    for (int it = 0; it < 400; ++it) {
        random_world(m, rng);
        store32(m, gp(tt::kGpOpWait), kWaitW);
        const u32 w = kWaitW;
        store32(m, w, load32(m, w) | 1u);
        const u32 flags = load32(m, w);
        std::array<s32, 13> before{};
        for (u32 i = 0; i < 13; ++i) before[i] = static_cast<s32>(load32(m, w + 4 * i));
        pair(m, PAIR(fn_sub_26DDC0_0026ddc0), Args{0, 0, 0, 0}, rng(), "counter rule");
        const struct {
            u32 off;
            s32 mod;
        } wraps[] = {{12, 90}, {16, 50}, {20, 30}, {24, 690}, {28, 70}, {32, 690}, {36, 1024}, {44, 360}, {48, 1024}};
        for (const auto& c : wraps) {
            const s32 v = before[c.off / 4];
            const s32 next = static_cast<s32>(static_cast<u32>(v) + 1u);
            if (next == INT32_MIN) continue;  // INT_MIN % m: the EE result is defined, C's is not checked here
            INFO("counter +" << c.off << " from " << v);
            CHECK(static_cast<s32>(load32(m, w + c.off)) == next % c.mod);
        }
        if (flags & 8u) {
            if (before[10] < 190) CHECK(static_cast<s32>(load32(m, w + 40)) == before[10] + 1);
            else CHECK((load32(m, w) & 8u) == 0);
        }
        ++counters;
    }

    // 4. sub_269A10 visits (cols + 1) x (rows + 1) points (layout 0) or (rows + 1) rows of cols + 2 / cols + 1 points
    //    (layout 1, even rows longer); the last record on its frame holds the last index and x = y = 1.
    int grids = 0;
    for (int it = 0; it < 300; ++it) {
        random_world(m, rng);
        const u32 cols = 1 + rng() % 5, rows = 1 + rng() % 5, layout = rng() % 2;
        store32(m, kGrid + 8, cols);
        store32(m, kGrid + 12, rows);
        store32(m, kGrid + 24, layout);
        store32(m, kVisitor, 0x4B3710u);
        pair(m, PAIR(fn_sub_269A10_00269a10), Args{sx(kGrid), sx(kVisitor), 0, 0}, rng(), "grid rule");
        const u32 rec = kSp - 160 + 128;
        u32 last = 0;
        if (layout == 0) last = rows * (cols + 1) + cols;
        else
            for (u32 r = 0; r <= rows; ++r) last += (r % 2 == 0) ? cols + 2 : cols + 1;
        if (layout == 1) --last;
        CHECK(load32(m, rec) == kGrid);
        CHECK(load32(m, rec + 16) == last);
        CHECK(loadf(m, rec + 4) == 1.0f);
        CHECK(loadf(m, rec + 8) == 1.0f);
        ++grids;
    }

    // 5. the op root: state 14 with the +24 child gone -> 16; state 7 ends the op root once sub_108710 allows it
    //    (flags bit 0 cleared, or untouched); state 0 / 1 only advance.
    int states = 0;
    for (int it = 0; it < 300; ++it) {
        random_world(m, rng);
        store32(m, gp(tt::kGpOpRoot), kOpRootW);
        store32(m, kOpRootW, (load32(m, kOpRootW) & ~4u) | 1u);
        store32(m, kOpRootW + tt::kOpState, 14);
        pair(m, PAIR(fn_sub_265030_00265030), Args{0, 0, 0, 0}, rng(), "state 14 rule");
        CHECK(load32(m, kOpRootW + tt::kOpState) == 16);
        ++states;
    }
    MESSAGE("rules: " << works << " set / clear pairs, " << selects << " selections, " << counters << " counter updates, "
                      << grids << " grids, " << states << " op states");
}

TEST_CASE("game(title): the title, dorm, battle and M1 snapshots") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5A95u};
    g_stats.clear();
    int runs = 0, found = 0;
    for (const char* dir : {"r3_title_sky3100", "r3_title_sky3315", "dorm_replay_4900", "battle_ref_6150", "b_5800", "v_m1"}) {
        const std::vector<u8> snapshot = title_snapshot(dir);
        if (snapshot.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        ++found;
        std::memcpy(m.at(0), snapshot.data(), snapshot.size());
        const bool title = std::string(dir).rfind("r3_title", 0) == 0;
        MESSAGE(dir << ": op root " << hex64(load32(m, gp(tt::kGpOpRoot))) << " (state "
                    << (load32(m, gp(tt::kGpOpRoot)) ? load32(m, load32(m, gp(tt::kGpOpRoot)) + 4) : 0u) << "), game root "
                    << hex64(load32(m, gp(tt::kGpGmRoot))) << " (state "
                    << (load32(m, gp(tt::kGpGmRoot)) ? load32(m, load32(m, gp(tt::kGpGmRoot)) + 4) : 0u) << ")");
        for (const Spec& s : kSpecs) {
            const bool root = s.hand == &recomp_gen::fn_gmRoot_UpdateGameRootTask_00266590 || s.hand == &recomp_gen::fn_sub_266140_00266140;
            if (!title && !root) continue;
            if (s.arg == Arg::grid) continue;  // the snapshot has no grid: wild sizes would loop for ages
            Args a = args_for(s.arg, rng);
            if (s.arg == Arg::work || s.arg == Arg::grid) a = Args{sx(kScratch), sx(kScratch + 0x40), 0, 0};
            pair(m, s.hand, s.recomp, a, rng(), s.name, kWholeRam, &snapshot);
            ++runs;
        }
    }
    MESSAGE("snapshots: " << found << " found, " << runs << " whole-RAM pairs");
    if (found) summary("snapshots", std::size(kSpecs));
}

#else
TEST_CASE("game(title): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
