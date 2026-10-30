// Phase 5 pair tests for slice battle_ui3 (game/src/battle/battle_ui3.cpp): every body against its recompiled body
// (__recomp) on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register file and the
// cycle count at every check point and at the return / stop, all 32 MiB of RAM (a PairRange: the dead stack and every
// stray store), the scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both bodies meet the same
// deterministic stand-ins: the heap behind the RW slots 0x960178 / 0x96017C, printf, the H_Cdvd file layer, and two
// recorders for the function pointers these bodies call: the render-state slot 0x960090 and an object's method).
//
//   * random worlds (the p3fes_handgen skeleton's, with the stand-ins);
//   * module worlds: every $gp slot of game/include/p3fes/game/battle_ui3.h pointing at a work block (now and then 0:
//     the K_Assert paths), the blocks shaped as the accessors read them -- flag words, loaded masks, small counts and
//     indices, gc_res's pair / id / slot tables with colliding keys, bp_res's sprite sets (44-byte page records),
//     bpp_main's member records, brp_seq's entries, the command panel's rows, gBtl / gEncountTbl for the command check
//     --, every other word random; arguments of the kind each function takes;
//   * the replay snapshots b_5800 (the battle panel and the command menu live), battle_ref_6150 (the result screen),
//     climb_ref_17000 and dorm_replay_4900: the real module works behind the real slots;
//   * documented-rule checks on the host (the hand body alone): the card grid of sub_20CDA0, the ground's index list of
//     sub_239170, the gc_res / bp_res / bpp_main / brp_seq lookups against host models, the page maps of sub_22E850 /
//     sub_215830 / sub_264CA0, the fades of br_lvpnl.c and bp_select.c over frames, the command cursor, the work
//     sub_24A7F0 allocates and registers.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/battle_ui3.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace ui = p3fes::game::bui3;

#define P3FES_BUI3_FUNCS(X)                                                                                             \
    X(sub_209D00, 00209d00) X(sub_209DC0, 00209dc0) X(sub_209DD0, 00209dd0) X(sub_209E10, 00209e10)                    \
    X(sub_209E20, 00209e20) X(sub_209E60, 00209e60) X(sub_209E70, 00209e70) X(sub_209EA0, 00209ea0)                    \
    X(sub_20C590, 0020c590) X(sub_20C5F0, 0020c5f0) X(sub_20C7B0, 0020c7b0) X(sub_20CCC0, 0020ccc0)                    \
    X(sub_20CDA0, 0020cda0) X(sub_20D7D0, 0020d7d0) X(sub_20DFE0, 0020dfe0) X(sub_20E4C0, 0020e4c0)                    \
    X(sub_20E510, 0020e510) X(sub_20E590, 0020e590) X(sub_20E690, 0020e690) X(sub_20EC00, 0020ec00)                    \
    X(sub_20F720, 0020f720) X(sub_20FC40, 0020fc40) X(sub_20FC90, 0020fc90) X(sub_20FD80, 0020fd80)                    \
    X(sub_215A50, 00215a50) X(sub_219C90, 00219c90) X(sub_21A3A0, 0021a3a0) X(sub_21A410, 0021a410)                    \
    X(sub_21A480, 0021a480) X(sub_21A590, 0021a590) X(sub_21AC90, 0021ac90) X(sub_21AE30, 0021ae30)                    \
    X(sub_21AF30, 0021af30) X(sub_21AFE0, 0021afe0) X(sub_21B150, 0021b150) X(sub_21B1F0, 0021b1f0)                    \
    X(sub_21B2D0, 0021b2d0) X(sub_21B3A0, 0021b3a0) X(sub_21B420, 0021b420) X(sub_21B670, 0021b670)                    \
    X(sub_21BAB0, 0021bab0) X(sub_21BB00, 0021bb00) X(sub_21BB50, 0021bb50) X(sub_21C3F0, 0021c3f0)                    \
    X(sub_21C450, 0021c450) X(sub_21C550, 0021c550) X(nullsub_11, 0021c7e0) X(sub_21C860, 0021c860)                    \
    X(sub_21C8B0, 0021c8b0) X(sub_21C930, 0021c930) X(sub_2226F0, 002226f0) X(sub_2227B0, 002227b0)                    \
    X(sub_222870, 00222870) X(sub_222B90, 00222b90) X(sub_222D60, 00222d60) X(sub_222ED0, 00222ed0)                    \
    X(sub_2230E0, 002230e0) X(sub_224860, 00224860) X(sub_226320, 00226320) X(sub_22B4E0, 0022b4e0)                    \
    X(sub_22B580, 0022b580) X(sub_22C210, 0022c210) X(sub_22E850, 0022e850) X(sub_2337E0, 002337e0)                    \
    X(sub_233850, 00233850) X(sub_23D7A0, 0023d7a0) X(sub_23D7F0, 0023d7f0) X(sub_245E00, 00245e00)                    \
    X(sub_245E50, 00245e50) X(sub_249130, 00249130) X(sub_249600, 00249600) X(sub_249650, 00249650)                    \
    X(sub_249680, 00249680) X(sub_24A180, 0024a180) X(sub_24D110, 0024d110) X(sub_24DA00, 0024da00)                    \
    X(sub_2519D0, 002519d0) X(sub_251E10, 00251e10) X(sub_251E80, 00251e80) X(sub_253410, 00253410)                    \
    X(sub_25CDB0, 0025cdb0) X(sub_25CE30, 0025ce30) X(sub_25D760, 0025d760) X(sub_25D7B0, 0025d7b0)                    \
    X(sub_25D800, 0025d800) X(sub_25D850, 0025d850) X(sub_260900, 00260900) X(sub_260920, 00260920)                    \
    X(sub_260940, 00260940) X(sub_260970, 00260970) X(sub_2626E0, 002626e0) X(sub_264CA0, 00264ca0)                    \
    X(sub_264D80, 00264d80) X(sub_272330, 00272330) X(sub_2737A0, 002737a0) X(sub_273980, 00273980)                    \
    X(sub_273E10, 00273e10) X(sub_274D40, 00274d40) X(sub_274D90, 00274d90) X(sub_274E10, 00274e10)                    \
    X(sub_274E90, 00274e90) X(sub_275A70, 00275a70) X(sub_2760F0, 002760f0) X(sub_276870, 00276870)                    \
    X(sub_276910, 00276910) X(sub_276CC0, 00276cc0) X(sub_276D10, 00276d10) X(sub_279450, 00279450)                    \
    X(sub_2794C0, 002794c0) X(sub_279510, 00279510) X(sub_279580, 00279580) X(sub_2795F0, 002795f0)                    \
    X(sub_2796B0, 002796b0) X(sub_279700, 00279700) X(sub_279750, 00279750) X(sub_2797A0, 002797a0)                    \
    X(sub_2797F0, 002797f0) X(sub_279840, 00279840) X(sub_279890, 00279890) X(sub_2798F0, 002798f0)                    \
    X(sub_27B6C0, 0027b6c0) X(sub_27BB50, 0027bb50) X(sub_2C1CE0, 002c1ce0) X(sub_1F5810, 001f5810)                    \
    X(sub_209C00, 00209c00) X(sub_209F00, 00209f00) X(sub_20A800, 0020a800) X(sub_20CD50, 0020cd50)                    \
    X(sub_215830, 00215830) X(sub_222930, 00222930) X(sub_222A60, 00222a60) X(sub_222FA0, 00222fa0)                    \
    X(sub_224660, 00224660) X(sub_22BF60, 0022bf60) X(sub_22C0E0, 0022c0e0) X(sub_22E780, 0022e780)                    \
    X(sub_239170, 00239170) X(sub_24A7F0, 0024a7f0) X(sub_275A90, 00275a90) X(sub_275BC0, 00275bc0)                    \
    X(sub_27B610, 0027b610)

namespace p3fes::recomp_gen {
#define P3FES_BUI3_DECL(name, addr) \
    void fn_##name##_##addr(EEContext&); \
    void fn_##name##_##addr##__recomp(EEContext&);
P3FES_BUI3_FUNCS(P3FES_BUI3_DECL)
#undef P3FES_BUI3_DECL
void fn_sub_21CCA0_0021cca0(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3) -------------------------------------------------------
// w a fresh work block (the register functions)   m a card model / quad / grid block    M a party-panel member block
// r an RGBA pointer   i an index 0..7 (now and then larger)   k a kind 0..25   u a u16 id (now and then high bits)
// p a gc_res pair key   o an object (+388 entry table, +260 word table, +1536 / +1540 the draw method)
// c a font chain   C a command (sub_2C1CE0)   T a task (+60 work)   x anything
struct Kinds {
    const char* name;
    const char* kinds;
};
const Kinds kKinds[] = {
    {"sub_209EA0", "m"}, {"sub_209F00", "m"}, {"sub_20A800", "m"}, {"sub_20C590", "mu"}, {"sub_20C5F0", "mxx"},
    {"sub_20C7B0", "m"}, {"sub_20CCC0", "mr"}, {"sub_20CD50", "mm"}, {"sub_20CDA0", "m"}, {"sub_20D7D0", "w"},
    {"sub_215A50", "w"}, {"sub_219C90", "w"}, {"sub_239170", "w"}, {"sub_23D7A0", "w"}, {"sub_24D110", "w"},
    {"sub_24DA00", "w"}, {"sub_260970", "w"}, {"sub_2626E0", "w"}, {"sub_264D80", "w"}, {"sub_272330", "w"},
    {"sub_275A70", "w"}, {"sub_276910", "w"}, {"sub_276D10", "w"}, {"sub_27BB50", "w"}, {"sub_20E510", "i"},
    {"sub_20E590", "i"}, {"sub_20E690", "i"}, {"sub_20F720", "u"}, {"sub_215830", "k"}, {"sub_21A480", "pp"},
    {"sub_21A590", "u"}, {"sub_21AC90", "pp"}, {"sub_21AE30", "pp"}, {"sub_21AFE0", "u"}, {"sub_21B1F0", "u"},
    {"sub_21B3A0", "i"}, {"sub_21B420", "i"}, {"sub_21B670", "x"}, {"sub_21BB00", "x"}, {"sub_21C3F0", "i"},
    {"sub_21C450", "u"}, {"sub_21C550", "i"}, {"sub_21C8B0", "i"}, {"sub_2226F0", "i"}, {"sub_2227B0", "i"},
    {"sub_22E780", "Mk"}, {"sub_22E850", "k"}, {"sub_2337E0", "M"}, {"sub_233850", "M"}, {"sub_249650", "u"},
    {"sub_249680", "o"}, {"sub_24A180", "o"}, {"sub_25CDB0", "c"}, {"sub_25CE30", "c"}, {"sub_260900", "oi"},
    {"sub_260920", "oi"}, {"sub_260940", "oi"}, {"sub_264CA0", "k"}, {"sub_279450", "i"}, {"sub_2794C0", "x"},
    {"sub_279510", "ix"}, {"sub_279580", "ix"}, {"sub_2795F0", "ix"}, {"sub_279890", "xx"}, {"sub_2C1CE0", "C"},
    {"sub_1F5810", "T"},
};

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
    const char* kinds;
};
std::vector<Case> make_cases() {
    std::vector<Case> v;
#define P3FES_BUI3_CASE(name, addr) \
    v.push_back({#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp, ""});
    P3FES_BUI3_FUNCS(P3FES_BUI3_CASE)
#undef P3FES_BUI3_CASE
    for (Case& c : v)
        for (const Kinds& k : kKinds)
            if (std::strcmp(c.name, k.name) == 0) c.kinds = k.kinds;
    return v;
}
const std::vector<Case>& cases() {
    static const std::vector<Case> v = make_cases();
    return v;
}
const Case& case_of(const char* name) {
    for (const Case& c : cases())
        if (std::strcmp(c.name, name) == 0) return c;
    static const Case none{"", 0, nullptr, nullptr, ""};
    return none;
}

// --- guest memory helpers -------------------------------------------------------------------------------------------
u8* ram(Machine& m, u32 va) { return m.at(std::min<u32>(va & 0x1FFFFFFu, 0x2000000u - 8)); }
void st8(Machine& m, u32 va, u8 v) { *ram(m, va) = v; }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(ram(m, va), &v, 2); }
void st32(Machine& m, u32 va, u32 v) { std::memcpy(ram(m, va), &v, 4); }
void stf(Machine& m, u32 va, float v) { std::memcpy(ram(m, va), &v, 4); }
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, ram(m, va), 2);
    return v;
}
u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
float ldf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, ram(m, va), 4);
    return v;
}
u32 gp_slot(s32 off) { return static_cast<u32>(static_cast<s32>(kGp) + off); }
bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }

// --- the stand-ins ----------------------------------------------------------------------------------------------------
// The function pointers of the module world point at two addresses the test build does not emit, served by recorders
// (the same two battle_core2's packet worlds use): the render-state slot 0x960090 (RwRenderStateSet) and an object's
// draw method (sub_24A180's jalr through +1536 -> +72).
constexpr u32 kRecRenderState = 0x281F20u;  // recorder -> 0
constexpr u32 kRecMethod = 0x2813F0u;       // recorder -> 1
constexpr u32 kRenderStateSlot = 0x960090u;
constexpr u32 kRecMsgWin = 0x3A4360u;       // not emitted: the message window calls under msgWinRequestMessage
constexpr u32 kRecMsgWin2 = 0x3A30C0u;
void ui3_setup(StandInWorld& w) {
    install_standard(w);
    w.si.install_recorder(kRecRenderState, "render_state", 0, 3);
    w.si.install_recorder(kRecMethod, "method", 1, 3);
    w.si.install_recorder(kRecMsgWin, "msgwin_3A4360", 0, 3);  // under msgWinRequestMessage (sub_273E10)
    w.si.install_recorder(kRecMsgWin2, "msgwin_3A30C0", 0, 3);
}

StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}

// hgp::pair with a fresh stand-in world around each body and the two call logs compared; returns the recompiled run.
hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    ui3_setup(*wh);
    ui3_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    INFO("function " << std::string(what));
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

// One body alone (the rule checks), with its own stand-in world kept for inspection.
struct Solo {
    hgp::Run run;
    std::unique_ptr<StandInWorld> world;
};
Solo solo(Machine& m, Fn fn, const Args& args, u32 seed = 1) {
    Solo s;
    s.world = std::make_unique<StandInWorld>();
    ui3_setup(*s.world);
    g_si[0] = s.world.get();
    g_fn[0] = fn;
    s.run = hgp::run_one(m, &thunk0, args, seed, {});
    return s;
}
u32 v0_of(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
u32 run_v0(Machine& m, const char* name, const Args& a) {
    const Solo s = solo(m, case_of(name).hand, a);
    if (s.run.stopped)
        MESSAGE(std::string(name) << ": " << s.run.what << "; ra " << hex64(s.run.end.gpr[31].u64[0]) << " a0 "
                                  << hex64(s.run.end.gpr[4].u64[0]) << " v0 " << hex64(s.run.end.gpr[2].u64[0]) << " s0 "
                                  << hex64(s.run.end.gpr[16].u64[0]));
    CHECK_FALSE(s.run.stopped);
    return v0_of(s.run);
}

// The ELF's data around the $gp slots (0x7C0000..0x7E0000) and the RW slots page, as loaded: a module world starts from
// them, so what an earlier case's body stored into a slot outside the ones the world sets does not leak into the next.
constexpr u32 kGpData = 0x7C0000u, kGpDataSize = 0x20000u, kRwPage = 0x960000u, kRwPageSize = 0x1000u;
std::vector<u8> g_gp_data, g_rw_page;

std::unique_ptr<Machine> new_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    g_gp_data.assign(m->at(kGpData), m->at(kGpData) + kGpDataSize);
    g_rw_page.assign(m->at(kRwPage), m->at(kRwPage) + kRwPageSize);
    return m;
}

// --- the module world -------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x34000u;
constexpr u32 kBcm = kWorld + 0x0000u;      // bcm_panel.c work (29,204 bytes)
constexpr u32 kBpp = kWorld + 0x7800u;      // bpp_main.c work (23,124)
constexpr u32 kParam = kWorld + 0xD400u;    // brp_param.c work (15,208)
constexpr u32 kGcRes = kWorld + 0x11000u;   // gc_res.c work (10,000)
constexpr u32 kSets = kWorld + 0x13800u;    // 8 sprite sets of 16 bytes {+4 records, +8 page table}
constexpr u32 kRecords = kWorld + 0x14000u; // 100 page records of 44 bytes
constexpr u32 kPages = kWorld + 0x15200u;   // the page table (16 pointers) and its 16 page records of 32 bytes
constexpr u32 kBpRes = kWorld + 0x15800u;   // bp_res.c work
constexpr u32 kSmall = kWorld + 0x16000u;   // the small works, 4 KiB apart (kSmallSlots)
constexpr u32 kFresh = kWorld + 0x2A000u;   // argument blocks: fresh works, models, members (36 KiB)
constexpr u32 kFreshSize = 0x9000u;

// The small works: their slot, in order (block kSmall + 0x1000 * index).
const s32 kSmallSlots[] = {ui::kGpSflRoot, ui::kGpSflRes, ui::kGpSflPsel, ui::kGpBseMain, ui::kGpSflGround,
                           ui::kGpSflPanel, ui::kGpBpcMain, ui::kGpBpmMain, ui::kGpBpeMain, ui::kGpBrpBirth,
                           ui::kGpSflCamera, ui::kGpGcPose, ui::kGpBpTut, ui::kGpBpTuta, ui::kGpBpdMain,
                           ui::kGpBpRush, ui::kGpFullQuad, ui::kGpBrHero, ui::kGpBrLvpnl, ui::kGpBrpSeq};
constexpr u32 kSmallCount = sizeof(kSmallSlots) / sizeof(kSmallSlots[0]);  // 20 -> up to kSmall + 0x14000
u32 small_block(s32 slot) {
    for (u32 i = 0; i < kSmallCount; ++i)
        if (kSmallSlots[i] == slot) return kSmall + 0x1000u * i;
    return 0;
}
// Further slots the callees read, pointed at random blocks of the fresh area's tail.
constexpr s32 kGpPanelTask = -18956;  // 0x7CE2E4 the "battle panel" task (sub_1FE510)
constexpr s32 kGpBrRes = -18916;      // 0x7CE30C br_res.c (sub_233D70 / sub_234630)
constexpr s32 kGpBrpRes = -18876;     // 0x7CE334 brp_res.c (sub_24B8A0)
constexpr u32 kObj = kFresh + 0x6000u;      // the 'o' object
constexpr u32 kObjTbl = kFresh + 0x6600u;   // its 128-byte entries
constexpr u32 kObjMeth = kFresh + 0x6E00u;  // the method object (+72 = the recorder)
constexpr u32 kCmd = kFresh + 0x6E80u;      // sub_2C1CE0's command
constexpr u32 kUnit = kFresh + 0x6F00u;     // its btlUnit (+2604 the DatUnit pointer: a random world word)
constexpr u32 kTask = kFresh + 0x6F40u;     // sub_1F5810's task (+60 its work)
constexpr u32 kPanelWork = kFresh + 0x8100u; // the panel task's work (sub_1FE510)

void fill_sets(Machine& m, std::mt19937& rng) {
    for (u32 s = 0; s < 8; ++s) {
        st32(m, kSets + 16 * s + 4, kRecords + 44 * (rng() % 8));
        st32(m, kSets + 16 * s + 8, kPages);
    }
    for (u32 r = 0; r < 100; ++r) {
        const u32 a = kRecords + 44 * r;
        st32(m, a + 0, kSets + 16 * (rng() % 8));
        st32(m, a + 4, rng() % 4);                // flags (u / v swaps)
        st32(m, a + 8, rng() % 16);               // the page
        st32(m, a + 12, 8 + rng() % 120);         // w
        st32(m, a + 16, 8 + rng() % 60);          // h
        st32(m, a + 20, rng() % 256);
        st32(m, a + 24, rng() % 256);
        for (u32 k = 28; k < 44; ++k) st8(m, a + k, static_cast<u8>(rng()));
    }
    for (u32 p = 0; p < 16; ++p) {  // the page table: 16 pointers to page records (sizes at +12 / +16)
        const u32 pr = kPages + 0x40u + 32 * p;
        st32(m, kPages + 4 * p, pr);
        st32(m, pr + 12, 64u << (rng() % 3));
        st32(m, pr + 16, 64u << (rng() % 3));
    }
}
u32 a_set(std::mt19937& rng) { return kSets + 16 * (rng() % 8); }

// The well-formed module world (every other word random).
void module_world(Machine& m, std::mt19937& rng) {
    std::memcpy(m.at(kGpData), g_gp_data.data(), kGpDataSize);
    std::memcpy(m.at(kRwPage), g_rw_page.data(), kRwPageSize);
    hgp::random_world(m, kWorld, kWorldSize, rng);
    fill_sets(m, rng);
    auto slot = [&](s32 off, u32 block) { st32(m, gp_slot(off), chance(rng, 8) ? 0u : block); };
    slot(ui::kGpBcmPanel, kBcm);
    slot(ui::kGpBppMain, kBpp);
    slot(ui::kGpBrpParam, kParam);
    slot(ui::kGpGcRes, kGcRes);
    slot(ui::kGpBpRes, kBpRes);
    for (u32 i = 0; i < kSmallCount; ++i) slot(kSmallSlots[i], kSmall + 0x1000u * i);
    st32(m, gp_slot(ui::kGpBpSelect), kSmall + 0x13800u);   // inside the brp_seq block's tail
    st32(m, gp_slot(ui::kGpBrpPersona), kSmall + 0x13C00u);
    st32(m, gp_slot(ui::kGpSflPersona), kSmall + 0x13E00u);
    st32(m, gp_slot(kGpPanelTask), kFresh + 0x8000u);
    st32(m, gp_slot(kGpBrRes), kFresh + 0x8400u);
    for (u32 k = 0; k < 32; ++k) st32(m, kFresh + 0x8400u + 4 * k, a_set(rng));  // br_res.c's set table (+48 ..)
    st32(m, kFresh + 0x8000u + 60, kPanelWork);
    st32(m, gp_slot(kGpBrpRes), kFresh + 0x8800u);
    st32(m, 0x7CDFA4u, rng() % 2);  // the scenario mode of sub_17D800
    st32(m, kRenderStateSlot, kRecRenderState);
    // flag words: a few bits
    for (u32 b : {kBcm, kBpp, kParam, kGcRes, kBpRes}) st32(m, b, rng() & 0x1FF);
    for (u32 i = 0; i < kSmallCount; ++i) {
        st32(m, kSmall + 0x1000u * i, rng() & 0x1FF);
        st32(m, kSmall + 0x1000u * i + 4, rng() & 0x1FF);
    }
    // sfl_res: the loaded mask, the file tables
    const u32 sr = small_block(ui::kGpSflRes);
    st32(m, sr + ui::kWkLoaded, chance(rng, 80) ? 7u : rng() % 8);
    st32(m, small_block(ui::kGpSflRoot) + 8, rng() % 3);
    // bpp_main: 0..4 member records with small ids
    st32(m, kBpp + ui::kBppCount, rng() % 5);
    for (u32 r = 0; r < 4; ++r) st16(m, kBpp + ui::kBppRecords + ui::kBppRecordSize * r + ui::kBppRecId, static_cast<u16>(rng() % 8));
    // gc_res: the loaded mask, colliding pair keys and ids, slot flags
    st32(m, kGcRes + ui::kGrLoaded, chance(rng, 70) ? 15u : rng() % 16);
    for (u32 e = 0; e < 16; ++e) {
        const u32 p = kGcRes + ui::kGrPairSize * e;
        st32(m, p + ui::kPrFlags, rng() % 4);
        st32(m, p + ui::kPrKeyA, rng() % 4);
        st32(m, p + ui::kPrKeyB, rng() % 4);
        const u32 q = kGcRes + ui::kGrIdSize * e;
        st32(m, q + ui::kGiFlags, rng() % 4);
        st16(m, q + ui::kGiId, static_cast<u16>(rng() % 10));
    }
    for (u32 s = 0; s < 32; ++s) st32(m, kGcRes + ui::kGrSlots + ui::kGrSlotSize * s, chance(rng, 85) ? 1u : 0u);
    // bp_res: sets, ids
    st32(m, kBpRes + ui::kBrLoaded, chance(rng, 80) ? 0x101u : rng() & 0x1FF);
    for (u32 i = 0; i < 8; ++i) st32(m, kBpRes + ui::kBrSets + 4 * i, a_set(rng));
    st32(m, kBpRes + ui::kBrSetOne, a_set(rng));
    st32(m, kBpRes + ui::kBrIdCount, rng() % 7);
    for (u32 i = 0; i < 6; ++i) {
        st32(m, kBpRes + ui::kBrIds + 4 * i, rng() % 8);
        st32(m, kBpRes + ui::kBrIdSets + 4 * i, a_set(rng));
    }
    // bcm_panel: cursor, rows, the cursor quad, +29200
    st32(m, kBcm + ui::kBcmList, 1u << (rng() % 4));
    st32(m, kBcm + ui::kBcmCur, rng() % 8);
    st32(m, kBcm + ui::kBcmPrev, rng() % 8);
    st32(m, kBcm + ui::kBcmRowCount, rng() % 6);
    for (u32 r = 0; r < 6; ++r)
        for (u32 stride : {1296u, 1040u, 1056u, 784u}) st32(m, kBcm + ui::kBcmRows + stride * r + (rng() % 4) * 4, rng() % 3);
    st32(m, kBcm + ui::kBcmCursorPage, rng() % 8);
    st32(m, kBcm + ui::kBcmCursorOn, rng() % 2);
    st32(m, kBcm + 27912, rng() % 3);
    st32(m, kBcm + 27908, rng() % 120);  // the detail numbers (bpIfontDrawNumber: 2 / 3 digits)
    st32(m, kBcm + 27916, rng() % 1200);
    st32(m, kBcm + 29200, rng() % 4);
    // br_lvpnl, brp_seq, bp_select
    const u32 lv = small_block(ui::kGpBrLvpnl);
    st32(m, lv + ui::kLvFrame, static_cast<u32>(static_cast<s32>(rng() % 42) - 2));
    st32(m, lv + ui::kLvMode, rng() % 3);
    const u32 bs = small_block(ui::kGpBrpSeq);
    st32(m, bs + ui::kBsState, chance(rng, 70) ? 9u : rng() % 12);
    st32(m, bs + ui::kBsIndex, rng() % 10);
    st32(m, bs + ui::kBsCount, rng() % 10);
    const u32 sel = kSmall + 0x13800u;
    st32(m, sel + ui::kSelFrame, static_cast<u32>(static_cast<s32>(rng() % 27) - 2));
    stf(m, sel + ui::kSelX, static_cast<float>(rng() % 640));
    stf(m, sel + ui::kSelY, static_cast<float>(rng() % 448));
    // the object of the 'o' kind, the command of sub_2C1CE0, the task of sub_1F5810
    st32(m, kObj + 388, kObjTbl);
    for (u32 e = 0; e < 8; ++e) st32(m, kObjTbl + 128 * e + 20, rng() % 16);
    st32(m, kObj + 1536, kObjMeth);
    st32(m, kObj + 1540, rng() % 4);
    st32(m, kObjMeth + 72, kRecMethod);
    st32(m, kCmd + 48, kUnit);
    st16(m, kCmd + 24, static_cast<u16>(rng() & 0x1FF));
    st32(m, kTask + 60, small_block(ui::kGpBpTut));
    // gBtl's setup and the encounter table
    st32(m, gp_slot(ui::kGpBtl), kFresh + 0x8C00u);
    st32(m, kFresh + 0x8C00u + 3004, kFresh + 0x8E00u);
    st16(m, kFresh + 0x8E00u + 8, static_cast<u16>(rng() % 4));
    st32(m, gp_slot(ui::kGpEncountTbl), kFresh + 0x8E40u);
}

// An argument of a kind.
u64 arg_of(char k, std::mt19937& rng) {
    if (rng() % 100 < 4) return hgp::random_arg(rng, kWorld, kWorldSize);  // anything, now and then
    switch (k) {
    case 'w': return sx(kFresh + 0x10u * (rng() % 16));
    case 'm': return sx(kFresh + 0x40u * (rng() % 64));
    case 'M': return sx(kFresh + 0x100u * (rng() % 32));
    case 'r': return sx(kRecords + 4 * (rng() % 64));
    case 'i': return rng() % 10 == 0 ? rng() % 40 : rng() % 8;
    case 'k': return rng() % 26;
    case 'u': return rng() % 6 == 0 ? (static_cast<u64>(rng() % 4) << 16) | (rng() % 10) : rng() % 10;
    case 'p': return rng() % 5;
    case 'o': return sx(kObj);
    case 'c': return rng() % 6 == 0 ? 0 : sx(kRecords + 44 * (rng() % 64));
    case 'C': return sx(kCmd);
    case 'T': return sx(kTask);
    default: return hgp::random_arg(rng, kWorld, kWorldSize);
    }
}
Args args_for(const Case& c, std::mt19937& rng) {
    Args a{};
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 4; ++i) a[i] = i < n ? arg_of(c.kinds[i], rng) : hgp::random_arg(rng, kWorld, kWorldSize);
    return a;
}

u32 seeds_or(u32 def) {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    return env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : def;
}

}  // namespace

TEST_CASE("game(battle_ui3): every body equals its recompiled body on random worlds") {
    auto m = new_machine();
    if (!m) return;
    const u32 seeds = seeds_or(24);
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    for (const Case& c : cases()) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs over " << cases().size() << " functions, " << stops << " ended at a compared stop");
}

TEST_CASE("game(battle_ui3): every body equals its recompiled body on module worlds") {
    auto m = new_machine();
    if (!m) return;
    const u32 seeds = seeds_or(40);
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    std::string always;
    for (const Case& c : cases()) {
        if (only && std::string(only) != c.name) continue;
        m = new_machine();  // a fresh machine per function: a wild store of an earlier case does not carry over
        int st = 0;
        std::string why;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 104729u + c.addr};
            module_world(*m, rng);
            const Args a = args_for(c, rng);
            const hgp::Run r = pair(*m, c.hand, c.recomp, a, seed, c.name);
            if (r.stopped) {
                ++st;
                if (why.empty()) why = r.what + " at " + hex64(r.stop_pc);
            }
        }
        pairs += static_cast<int>(seeds);
        stops += st;
        if (st == static_cast<int>(seeds)) always += std::string(" ") + c.name + " (" + why + ")";
    }
    MESSAGE("module worlds: " << pairs << " pairs, " << stops << " ended at a compared stop; always stopped:"
                              << (always.empty() ? " none" : always));
}

TEST_CASE("game(battle_ui3): every body on the replay snapshots' real module works") {
    int used = 0, pairs = 0, stops = 0;
    for (const char* dir : {"b_5800", "battle_ref_6150", "climb_ref_17000", "dorm_replay_4900"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        ++used;
        auto m = new_machine();
        if (!m) return;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        write_rw_slots(*m);
        int live = 0;
        for (s32 off = -18964; off <= -18692; off += 4)
            if (ld32(*m, gp_slot(off))) ++live;
        MESSAGE(std::string(dir) << ": " << live << " of the module slots 0x7CE2DC..0x7CE3EC set");
        std::mt19937 rng{0xB013u};
        for (const Case& c : cases()) {
            for (int rep = 0; rep < 4; ++rep) {
                Args a{};
                const std::size_t n = std::strlen(c.kinds);
                for (unsigned i = 0; i < 4; ++i) {
                    const char k = i < n ? c.kinds[i] : 'i';
                    // pointer kinds: fresh blocks of the stand-in heap's arena (zero in every snapshot)
                    const bool ptr = std::strchr("wmMroCcT", k) != nullptr;
                    a[i] = ptr ? sx(kStandInHeap + 0x200000u + 0x1000u * (rng() % 16)) : arg_of(k, rng);
                }
                const hgp::Run r = pair(*m, c.hand, c.recomp, a, rep + 1, c.name);
                ++pairs;
                stops += r.stopped ? 1 : 0;
            }
        }
    }
    MESSAGE("snapshots: " << used << " used, " << pairs << " pairs, " << stops << " ended at a compared stop");
}

// --- documented rules -------------------------------------------------------------------------------------------------

TEST_CASE("game(battle_ui3): gc_model.c builds the 68-vertex card grid and the card quads") {
    auto m = new_machine();
    if (!m) return;
    const u32 g = kFresh;
    std::memset(ram(*m, g), 0xCD, 2600);
    run_v0(*m, "sub_20CDA0", {sx(g), 0, 0, 0});
    CHECK(ld32(*m, g) == 0);
    CHECK(ldf(*m, g + 2464) == 0.5f);
    CHECK(ldf(*m, g + 2468) == 0.375f);
    const float pitch = ldf(*m, 0x7CB028u), half = ldf(*m, 0x7CB008u);
    u32 v = 0;
    for (int row = 0; row < 9; ++row) {
        const int n = (row & 1) ? 7 : 8;
        for (int col = 0; col < n; ++col, ++v) {
            float x;
            if (row & 1) x = static_cast<float>(col);
            else if (col == 0) x = 0.0f;
            else if (col == n - 1) x = 6.0f;
            else x = static_cast<float>(col - 1) + 0.5f;
            const u32 a = g + 4 + ui::kGcvSize * v;
            INFO("row " << row << " col " << col);
            CHECK(ldf(*m, a + 0) == x - 3.0f);
            CHECK(ldf(*m, a + 4) == pitch * static_cast<float>(row) - half);
            CHECK(ldf(*m, a + 8) == 0.0f);
        }
    }
    CHECK(v == static_cast<u32>(ui::kGridVerts));
    CHECK(ld32(*m, g + 4 + ui::kGcvSize * 68) == 0xCDCDCDCDu);  // nothing past the 68th vertex
    // the model header and kind of the two builders; the grid setter's flag
    for (int kind = 0; kind < 2; ++kind) {
        const u32 mdl = kFresh + 0x2000u;
        std::memset(ram(*m, mdl), 0xAB, 1600);
        run_v0(*m, kind ? "sub_20A800" : "sub_209F00", {sx(mdl), 0, 0, 0});
        CHECK(ld32(*m, mdl + ui::kGcmKind) == static_cast<u32>(kind));
        CHECK(ld32(*m, mdl + ui::kGcmFlags) == 0);
        CHECK(ldf(*m, mdl + ui::kGcmScale) == 1.0f);
        CHECK(ld32(*m, mdl + ui::kGcmColour) == 0xFFFFFFFFu);
        CHECK(ld32(*m, mdl + ui::kGcmGrid) == 0);
        CHECK(ldf(*m, mdl + ui::kGcmQuad0) == 3.0f);  // sub_20C7B0's first vertex x
        CHECK(ld32(*m, mdl + ui::kGcmQuad0 + ui::kGcvRgba) == 0xFFFFFFFFu);
        run_v0(*m, "sub_20CD50", {sx(mdl), sx(g), 0, 0});
        CHECK(ld32(*m, mdl + ui::kGcmGrid) == g);
        CHECK((ld32(*m, mdl + ui::kGcmFlags) & 8u) == 8u);
    }
    // sub_20CCC0: the RGBA into the four vertices
    const u32 q = kFresh + 0x3000u, rgba = kFresh + 0x3400u;
    st32(*m, rgba, 0x11223344u);
    run_v0(*m, "sub_20CCC0", {sx(q), sx(rgba), 0, 0});
    for (u32 k = 0; k < 4; ++k) CHECK(ld32(*m, q + ui::kGcvRgba + ui::kGcvSize * k) == 0x11223344u);
}

TEST_CASE("game(battle_ui3): sub_239170 builds the shuffle ground's quad index list and registers the work") {
    auto m = new_machine();
    if (!m) return;
    st32(*m, gp_slot(ui::kGpSflGround), 0);
    const u32 w = kFresh;
    std::memset(ram(*m, w), 0x5A, 0x8E00);
    run_v0(*m, "sub_239170", {sx(w), 0, 0, 0});
    CHECK(ld32(*m, gp_slot(ui::kGpSflGround)) == w);
    CHECK(ld32(*m, w) == 0);
    CHECK(ld32(*m, w + 12) == 0);
    CHECK(ld32(*m, w + 34688 + 1540) == 0);  // sub_249680(work + 34688): its +1540
    CHECK(ld32(*m, w + 34688) == 0x5A5A5A5Au);
    int bad = 0;
    for (u32 r = 0; r < 8; ++r)
        for (u32 c = 0; c < 10; ++c) {
            const u16 v = static_cast<u16>(r * 11 + c);
            const u32 a = w + 33728 + 12 * (r * 10 + c);
            const u16 want[6] = {v, static_cast<u16>(v + 1), static_cast<u16>(v + 11), static_cast<u16>(v + 1),
                                 static_cast<u16>(v + 12), static_cast<u16>(v + 11)};
            for (u32 k = 0; k < 6; ++k) bad += ld16(*m, a + 2 * k) != want[k];
        }
    CHECK(bad == 0);
}

TEST_CASE("game(battle_ui3): the module lookups against host models") {
    auto m = new_machine();
    if (!m) return;
    int checks = 0;
    for (u32 seed = 1; seed <= 200; ++seed) {
        std::mt19937 rng{seed};
        module_world(*m, rng);
        for (s32 off : {ui::kGpGcRes, ui::kGpBpRes, ui::kGpBppMain, ui::kGpBrpSeq})
            st32(*m, gp_slot(off), off == ui::kGpGcRes ? kGcRes : off == ui::kGpBpRes ? kBpRes : off == ui::kGpBppMain ? kBpp : small_block(off));
        st32(*m, kGcRes + ui::kGrLoaded, 15);
        st32(*m, kBpRes + ui::kBrLoaded, 0x101);
        // gc_res: has-pair / has-id / free slots (live = bit 0)
        const u32 a = rng() % 5, b = rng() % 5;
        u32 hp = 0, hi = 0, fp = 16, fi = 16, fs = 32, pv = 0, iv = 0;
        const u16 id = static_cast<u16>(rng() % 10);
        for (u32 e = 0; e < 16; ++e) {
            const u32 p = kGcRes + ui::kGrPairSize * e, q = kGcRes + ui::kGrIdSize * e;
            if ((ld32(*m, p + ui::kPrFlags) & 1) && ld32(*m, p + ui::kPrKeyA) == a && ld32(*m, p + ui::kPrKeyB) == b) hp = 1;
            if ((ld32(*m, q + ui::kGiFlags) & 1) && ld16(*m, q + ui::kGiId) == id) hi = 1;
            if (fp == 16 && !(ld32(*m, p + ui::kPrFlags) & 1)) fp = e;
            if (fi == 16 && !(ld32(*m, q + ui::kGiFlags) & 1)) fi = e;
        }
        for (u32 s = 0; s < 32; ++s)
            if (fs == 32 && !(ld32(*m, kGcRes + ui::kGrSlots + ui::kGrSlotSize * s) & 1)) fs = s;
        u32 e = 0;  // the value lookups take the first key match, live or not
        while (e < 16 && !(ld32(*m, kGcRes + ui::kGrPairSize * e + ui::kPrKeyA) == a && ld32(*m, kGcRes + ui::kGrPairSize * e + ui::kPrKeyB) == b)) ++e;
        pv = ld32(*m, kGcRes + ui::kGrPairSize * e + ui::kPrValue);
        u32 f = 0;
        while (f < 16 && ld16(*m, kGcRes + ui::kGrIdSize * f + ui::kGiId) != id) ++f;
        iv = ld32(*m, kGcRes + ui::kGrIdSize * f + ui::kGiValue);
        CHECK(run_v0(*m, "sub_21AC90", {a, b, 0, 0}) == hp);
        CHECK(run_v0(*m, "sub_21AFE0", {id, 0, 0, 0}) == hi);
        CHECK(run_v0(*m, "sub_21AF30", {0, 0, 0, 0}) == fp);
        CHECK(run_v0(*m, "sub_21B150", {0, 0, 0, 0}) == fi);
        CHECK(run_v0(*m, "sub_21A480", {a, b, 0, 0}) == pv);
        CHECK(run_v0(*m, "sub_21A590", {id, 0, 0, 0}) == iv);
        if (fs < 32) CHECK(run_v0(*m, "sub_21B2D0", {0, 0, 0, 0}) == kGcRes + ui::kGrSlots + ui::kGrSlotSize * fs);
        // bp_res: the set of an id
        const u32 sid = rng() % 9;
        u32 want;
        if (sid == 1) {
            want = ld32(*m, kBpRes + ui::kBrSetOne);
        } else {
            const u32 n = ld32(*m, kBpRes + ui::kBrIdCount);
            u32 k = 0;
            while (k < n && ld32(*m, kBpRes + ui::kBrIds + 4 * k) != sid) ++k;
            want = ld32(*m, kBpRes + ui::kBrIdSets + 4 * k);
        }
        CHECK(run_v0(*m, "sub_21C450", {sid, 0, 0, 0}) == want);
        const u32 si = rng() % 5;
        CHECK(run_v0(*m, "sub_21C3F0", {si, 0, 0, 0}) == ld32(*m, kBpRes + ui::kBrSets + 4 * si));
        // bpp_main: the member with an id
        const u16 mid = static_cast<u16>(rng() % 8);
        u32 rec = 0;
        for (u32 r = 0; r < ld32(*m, kBpp + ui::kBppCount) && !rec; ++r)
            if (ld16(*m, kBpp + ui::kBppRecords + ui::kBppRecordSize * r + ui::kBppRecId) == mid) rec = kBpp + ui::kBppRecords + ui::kBppRecordSize * r;
        CHECK(run_v0(*m, "sub_20F720", {mid, 0, 0, 0}) == rec);
        // brp_seq: the entry accessors
        const u32 bs = small_block(ui::kGpBrpSeq);
        const s32 idx = static_cast<s32>(ld32(*m, bs + ui::kBsIndex)), cnt = static_cast<s32>(ld32(*m, bs + ui::kBsCount));
        CHECK(run_v0(*m, "sub_274D40", {0, 0, 0, 0}) == static_cast<u32>(idx < cnt));
        CHECK(run_v0(*m, "sub_274E90", {0, 0, 0, 0}) == static_cast<u32>(std::max(cnt - idx - 1, 0)));
        CHECK(run_v0(*m, "sub_274D90", {0, 0, 0, 0}) == ld16(*m, bs + ui::kBsEntries + 8 * idx));
        CHECK(run_v0(*m, "sub_274E10", {0, 0, 0, 0}) == ld32(*m, bs + ui::kBsEntries + 4 + 8 * idx));
        checks += 13;
    }
    MESSAGE("lookups: " << checks << " host-model checks");
}

TEST_CASE("game(battle_ui3): the page maps of sub_22E850, sub_264CA0 and sub_215830") {
    auto m = new_machine();
    if (!m) return;
    const u32 icon[6] = {0, 13, 12, 14, 15, 16};
    for (u32 k = 0; k < 8; ++k) CHECK(run_v0(*m, "sub_22E850", {k, 0, 0, 0}) == (k >= 1 && k <= 5 ? icon[k] : 0u));
    std::mt19937 rng{7};
    module_world(*m, rng);
    st32(*m, gp_slot(ui::kGpBpRes), kBpRes);
    const u32 set2 = ld32(*m, kBpRes + ui::kBrSets + 8);
    auto page = [&](u32 set, u32 i) { return set ? ld32(*m, set + 4) + 44 * i : 0u; };
    for (u32 k = 0; k < 26; ++k) {
        u32 want = 0;
        if (k >= 1 && k <= 12) want = page(set2, k + 9);
        else if (k >= 13 && k <= 22) want = page(set2, k - 13);
        else if (k == 23) want = page(set2, 59);
        INFO("kind " << k);
        CHECK(run_v0(*m, "sub_215830", {k, 0, 0, 0}) == want);
    }
    // sub_22E780: kinds 1..5 set flag 2 and the page into the quad; 0 clears it
    const u32 mem = kFresh;
    st32(*m, mem, 0);
    run_v0(*m, "sub_22E780", {sx(mem), 3, 0, 0});
    CHECK(ld32(*m, mem + 1320) == 3);
    CHECK((ld32(*m, mem) & 2u) == 2u);
    run_v0(*m, "sub_22E780", {sx(mem), 0, 0, 0});
    CHECK((ld32(*m, mem) & 2u) == 0u);
}

TEST_CASE("game(battle_ui3): the br_lvpnl.c and bp_select.c fades over frames") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{11};
    module_world(*m, rng);
    const u32 lv = small_block(ui::kGpBrLvpnl);
    st32(*m, gp_slot(ui::kGpBrLvpnl), lv);
    st32(*m, gp_slot(kGpBrRes), kFresh + 0x8400u);
    for (u32 mode = 0; mode < 2; ++mode) {
        st32(*m, lv + ui::kLvFlags, 3);  // shown, animating
        st32(*m, lv + ui::kLvFrame, 0);
        st32(*m, lv + ui::kLvMode, mode);
        const s32 end = mode ? 33 : 36;
        int frames = 0;
        while ((ld32(*m, lv + ui::kLvFlags) & 2u) && frames < 100) {
            run_v0(*m, "sub_275BC0", {0, 0, 0, 0});
            ++frames;
        }
        INFO("mode " << mode);
        CHECK(frames == end + 1);  // `end` steps up the counter, one more clears the bit
        CHECK(static_cast<s32>(ld32(*m, lv + ui::kLvFrame)) == end);
    }
    // bp_select: opening counts to 20 and stays; closing clears the active bit at 20; the alpha follows
    const u32 sel = kSmall + 0x13800u;
    st32(*m, gp_slot(ui::kGpBpSelect), sel);
    st32(*m, gp_slot(ui::kGpBpRes), kBpRes);
    st32(*m, kBpRes + ui::kBrSets + 8, a_set(rng));
    st32(*m, sel + ui::kSelFlags, 1);
    st32(*m, sel + ui::kSelFrame, 0);
    for (int f = 0; f < 25; ++f) run_v0(*m, "sub_27B610", {0, 0, 0, 0});
    CHECK(ld32(*m, sel + ui::kSelFrame) == 20u);
    CHECK((ld32(*m, sel + ui::kSelFlags) & 1u) == 1u);
    st32(*m, sel + ui::kSelFlags, 3);
    st32(*m, sel + ui::kSelFrame, 0);
    int closing = 0;
    while ((ld32(*m, sel + ui::kSelFlags) & 1u) && closing < 50) {
        run_v0(*m, "sub_27B610", {0, 0, 0, 0});
        ++closing;
    }
    CHECK(closing == 21);
}

TEST_CASE("game(battle_ui3): the command cursor and the work sub_24A7F0 creates") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{5};
    module_world(*m, rng);
    st32(*m, gp_slot(ui::kGpBcmPanel), kBcm);
    st32(*m, gp_slot(ui::kGpBpRes), kBpRes);
    st32(*m, kBcm + ui::kBcmCur, 2);
    run_v0(*m, "sub_2226F0", {5, 0, 0, 0});
    CHECK(ld32(*m, kBcm + ui::kBcmState) == 1u);
    CHECK(ld32(*m, kBcm + ui::kBcmCur) == 5u);
    CHECK(ld32(*m, kBcm + ui::kBcmPrev) == 2u);
    CHECK(ld32(*m, kBcm + ui::kBcmTimer) == 0u);
    run_v0(*m, "sub_222870", {0, 0, 0, 0});
    CHECK(ld32(*m, kBcm + ui::kBcmState) == 8u);
    CHECK(ld32(*m, kBcm + ui::kBcmCur) == 0u);
    CHECK(ld32(*m, kBcm + ui::kBcmPrev) == 5u);
    // sub_24A7F0: a 50,544-byte block from the RwMalloc stand-in, the four sub-works registered inside it
    for (s32 off : {ui::kGpGcRes, ui::kGpSflRes, ui::kGpSflGround}) st32(*m, gp_slot(off), 0);
    const Solo s = solo(*m, case_of("sub_24A7F0").hand, {0, 0, 0, 0});
    INFO("sub_24A7F0: " << s.run.what << " at " << hex64(s.run.stop_pc));
    CHECK_FALSE(s.run.stopped);
    const u32 blk = ld32(*m, gp_slot(ui::kGpBrpBirth));
    CHECK(s.world->heap.size_of(blk) >= 50544u);
    CHECK(ld32(*m, gp_slot(ui::kGpGcRes)) == blk + 4052);
    CHECK(ld32(*m, gp_slot(ui::kGpSflRes)) == blk + 14128);
    CHECK(ld32(*m, gp_slot(ui::kGpSflGround)) == blk + 14272);
    CHECK(ld32(*m, blk + 4) == 0u);
    CHECK(ld32(*m, blk + 8) == 0u);
}

#else

TEST_CASE("game(battle_ui3): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
