// Phase 5 pair tests for slice band20b (game/src/battle/band20b_*.cpp, game/src/model/band20b_model.cpp,
// game/src/fx/band20b_fx.cpp): every body against its recompiled body (__recomp) on identical guest machines, compared by
// tests/game/handgen_pairs.h -- the whole register file and the cycle count at every check point and at the return /
// stop, all 32 MiB of RAM (a PairRange: the dead stack and every stray store), the scratchpad, the BIOS window and the
// bus log -- plus the stand-in call log (both bodies meet the same deterministic stand-ins: the heap behind the RW slots,
// printf, sprintf, the H_Cdvd file layer, recorders behind the RW device slots the draw functions call through).
//
//   * random worlds (the p3fes_handgen skeleton's world, with the stand-ins);
//   * module worlds: every $gp slot of band20.h / battle_cmd_menu.h pointing at a work block shaped as the bodies read
//     it -- band20's module world (test_band20.cpp) plus the bcm_main.c work (skills, items, target / tactic rows and
//     cursors), the persona select's entries, order and cursor block, the analysis panel, card models, models and
//     their motion slots, effect definitions / records / instances / particle systems -- now and then a slot 0 (the
//     K_Assert paths), every other word random, and arguments of the kind each function takes ($a0..$a3, $t0);
//   * the replay snapshots b_5800 / fx2_battle_5450 / battle_ref_6150 (battle panels and effects live), b20_climb_10850 /
//     b20_climb_11200 (Shuffle Time live) and climb_ref_17000: the real works behind the real slots;
//   * documented-rule checks on the host (the hand body alone): the persona select's arcana -> page map, its two centred
//     number layouts and the digit pages of the "%d" writers, the kept / released id lists and the entry append, the
//     class instance's creation, the two scale slots, a model's motion-file names, the card model's copies.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/band20.h"
#include "p3fes/game/band20b.h"
#include "p3fes/game/battle_cmd_menu.h"

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
namespace b = p3fes::game::b20;
namespace bb = p3fes::game::b20b;
namespace bm = p3fes::game::bcm;

#define P3FES_B20B_FUNCS(X)                                                                                            \
    X(sub_202830, 00202830) X(sub_203630, 00203630) X(sub_2057C0, 002057c0) X(sub_2063F0, 002063f0)                  \
    X(sub_208B30, 00208b30) X(sub_2094F0, 002094f0) X(sub_209940, 00209940) X(sub_209BA0, 00209ba0)                  \
    X(sub_209C40, 00209c40) X(sub_209CC0, 00209cc0) X(sub_20AB30, 0020ab30) X(nullsub_66, 0020ac80)                  \
    X(sub_20AC90, 0020ac90) X(sub_20C320, 0020c320) X(sub_20C7A0, 0020c7a0) X(sub_20CA90, 0020ca90)                  \
    X(sub_20CF20, 0020cf20) X(sub_20D670, 0020d670) X(sub_20D690, 0020d690) X(sub_20D6C0, 0020d6c0)                  \
    X(sub_20D710, 0020d710) X(sub_20D770, 0020d770) X(sub_20E710, 0020e710) X(sub_20E8F0, 0020e8f0)                  \
    X(sub_20E9B0, 0020e9b0) X(sub_20EA00, 0020ea00) X(sub_20EC50, 0020ec50) X(sub_20F7D0, 0020f7d0)                  \
    X(sub_20F8B0, 0020f8b0) X(sub_20FA80, 0020fa80) X(sub_20FB60, 0020fb60) X(sub_20FCE0, 0020fce0)                  \
    X(sub_20FD30, 0020fd30) X(sub_20FE30, 0020fe30) X(sub_210D60, 00210d60) X(sub_215A30, 00215a30)                  \
    X(sub_215A40, 00215a40) X(sub_215B00, 00215b00) X(sub_215FC0, 00215fc0) X(sub_2168A0, 002168a0)                  \
    X(sub_2168F0, 002168f0) X(sub_2170C0, 002170c0) X(sub_217350, 00217350) X(sub_217410, 00217410)                  \
    X(sub_2174D0, 002174d0) X(sub_217590, 00217590) X(sub_217610, 00217610) X(sub_217780, 00217780)                  \
    X(sub_2180B0, 002180b0) X(sub_218250, 00218250) X(sub_218310, 00218310) X(sub_218370, 00218370)                  \
    X(sub_218570, 00218570) X(sub_2187B0, 002187b0) X(sub_218810, 00218810) X(sub_218B20, 00218b20)                  \
    X(sub_219370, 00219370) X(sub_219970, 00219970) X(sub_219AB0, 00219ab0) X(sub_219B90, 00219b90)                  \
    X(sub_21AD40, 0021ad40) X(sub_21B080, 0021b080) X(sub_21B6F0, 0021b6f0) X(sub_21B740, 0021b740)                  \
    X(sub_21B7C0, 0021b7c0) X(sub_21B830, 0021b830) X(sub_21C720, 0021c720) X(sub_2254A0, 002254a0)                  \
    X(sub_227D10, 00227d10) X(sub_22C1D0, 0022c1d0) X(sub_233790, 00233790) X(sub_2337B0, 002337b0)                  \
    X(sub_239280, 00239280) X(sub_2392D0, 002392d0) X(sub_23C3A0, 0023c3a0) X(sub_23CA10, 0023ca10)                  \
    X(sub_23CD50, 0023cd50) X(sub_23CDA0, 0023cda0) X(sub_23D240, 0023d240) X(sub_23D2A0, 0023d2a0)                  \
    X(sub_23D650, 0023d650) X(sub_23F010, 0023f010) X(sub_23F1D0, 0023f1d0) X(sub_23F540, 0023f540)                  \
    X(sub_3151D0, 003151d0) X(sub_31C1D0, 0031c1d0) X(sub_31E4D0, 0031e4d0) X(sub_321360, 00321360)                  \
    X(sub_321B00, 00321b00) X(sub_321C50, 00321c50) X(sub_321CE0, 00321ce0) X(sub_321D40, 00321d40)                  \
    X(sub_321E50, 00321e50) X(sub_321EB0, 00321eb0) X(sub_324470, 00324470) X(sub_324680, 00324680)                  \
    X(sub_324870, 00324870) X(sub_3257A0, 003257a0) X(sub_326490, 00326490) X(sub_326510, 00326510)                  \
    X(sub_3268C0, 003268c0) X(sub_3269E0, 003269e0) X(sub_326F60, 00326f60) X(sub_327090, 00327090)                  \
    X(sub_327250, 00327250) X(sub_3275D0, 003275d0) X(sub_32AF30, 0032af30) X(sub_32BA30, 0032ba30)                  \
    X(sub_32C340, 0032c340) X(sub_32CE10, 0032ce10) X(sub_32D840, 0032d840) X(sub_32E1A0, 0032e1a0)                  \
    X(sub_32EAB0, 0032eab0) X(sub_32EB40, 0032eb40) X(sub_32F8B0, 0032f8b0) X(sub_32F910, 0032f910)

namespace p3fes::recomp_gen {
#define P3FES_B20B_DECL(name, addr) \
    void fn_##name##_##addr(EEContext&); \
    void fn_##name##_##addr##__recomp(EEContext&);
P3FES_B20B_FUNCS(P3FES_B20B_DECL)
#undef P3FES_B20B_DECL
void fn_sub_21D3B0_0021d3b0(EEContext&);  // battle_panel: the quad of a page (the digit rule's reference)
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3, $t0) --------------------------------------------------
// w a fresh block   q 2D quads   n a number   d a digit   x a float vector   i an index   u a u16 id   B the analysis panel
// k a kind 0 / 1   P a member panel   g a card model   G a lighting grid   A an arcana   R a persona-select row
// E a persona-select entry   l lit 0 / 1   O a model   S a motion slot pointer   K a model kind 1 / 2   L a layer 0..7
// M an effect mesh   D an effect definition   r an effect record   N a node tree   I a class instance   Y a particle system
// m a matrix   a anything
struct Kinds {
    u32 addr;
    const char* kinds;
};
const Kinds kKinds[] = {
    {0x209940u, "qnn"}, {0x209BA0u, "qd"},  {0x20AB30u, "g"},   {0x20AC90u, "g"},   {0x20C320u, "xw"},  {0x20C7A0u, "ga"},
    {0x20CA90u, "mg"},  {0x20CF20u, "Gg"},  {0x20D670u, "gw"},  {0x20D690u, "gx"},  {0x20D6C0u, "g"},   {0x20D710u, "g"},
    {0x20D770u, "g"},   {0x20E710u, "i"},   {0x20EA00u, "i"},   {0x20F7D0u, "u"},   {0x20F8B0u, "u"},   {0x20FA80u, "u"},
    {0x20FB60u, "u"},   {0x20FE30u, "Bki"}, {0x210D60u, "B"},   {0x215A30u, "B"},   {0x215A40u, "B"},   {0x217410u, "ww"},
    {0x2174D0u, "ww"},  {0x217590u, "u"},   {0x2180B0u, "A"},   {0x218250u, "qnn"}, {0x218310u, "qd"},  {0x218370u, "qnnx"},
    {0x218570u, "qnnx"}, {0x218810u, "REl"}, {0x218B20u, "RElx"}, {0x219370u, "REl"}, {0x21AD40u, "nn"},  {0x21B080u, "u"},
    {0x233790u, "P"},   {0x2337B0u, "P"},   {0x23C3A0u, "q"},   {0x3151D0u, "O"},   {0x31C1D0u, "O"},   {0x31E4D0u, "SKn"},
    {0x321360u, "L"},   {0x324470u, "M"},   {0x324680u, "D"},   {0x324870u, "r"},   {0x3257A0u, "N"},   {0x326490u, "n"},
    {0x326510u, "D"},   {0x3268C0u, "I"},   {0x3269E0u, "II"},  {0x326F60u, "ID"},  {0x327090u, "ID"},  {0x327250u, "I"},
    {0x3275D0u, "I"},   {0x32AF30u, "Y"},   {0x32BA30u, "Y"},   {0x32C340u, "Y"},   {0x32CE10u, "Y"},   {0x32D840u, "Y"},
    {0x32E1A0u, "Y"},   {0x32EAB0u, "Y"},   {0x32EB40u, "Y"},   {0x32F8B0u, "Y"},   {0x32F910u, "Y"},
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
#define P3FES_B20B_CASE(name, addr) \
    v.push_back({#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp, ""});
    P3FES_B20B_FUNCS(P3FES_B20B_CASE)
#undef P3FES_B20B_CASE
    for (Case& c : v)
        for (const Kinds& k : kKinds)
            if (c.addr == k.addr) c.kinds = k.kinds;
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
u8* ram(Machine& m, u32 va) { return m.at(std::min<u32>(va & 0x1FFFFFFu, 0x2000000u - 16)); }
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
bool chance(std::mt19937& rng, u32 pct) {
    const u32 r = rng() % 100;
    return r < pct;
}
float small_f(std::mt19937& rng) {
    const int n = static_cast<int>(rng() % 2001) - 1000;
    const int d = 1 + static_cast<int>(rng() % 50);
    return static_cast<float>(n) / static_cast<float>(d);
}
u32 below(std::mt19937& rng, u32 n) {
    const u32 r = rng();
    return n ? r % n : 0u;
}

// --- the stand-ins ----------------------------------------------------------------------------------------------------
// The RW device slots (RwRenderStateSet / Get, the Im2D render functions) are .bss zeros in the ELF and real Sky
// functions in a snapshot; the worlds point them at two functions this library does not emit, served by recorders.
constexpr u32 kRec0 = 0x281F20u;  // recorder -> 0
constexpr u32 kRec1 = 0x2813F0u;  // recorder -> 1
constexpr u32 kDeviceSlots[] = {0x960090u, 0x960094u, 0x96009Cu, 0x9600A0u, 0x9600A4u};
void set_device_slots(Machine& m) {
    for (u32 s : kDeviceSlots) st32(m, s, s == 0x960094u ? kRec1 : kRec0);
}
void b20b_setup(StandInWorld& w) {
    install_standard(w);
    w.si.install_recorder(kRec0, "rw_device_0", 0, 3);
    w.si.install_recorder(kRec1, "rw_device_1", 1, 3);
    w.si.install_recorder(0x4DB350u, "SkyRasterCreate", 1, 3);
    w.si.install_recorder(0x4DD2E0u, "sub_4DD2E0 (the raster destroy's device step)", 1, 3);
    // not emitted here: the effect node step (test_field3_units / test_field7_epl stand it in the same way) and the
    // message manager's request step under msgWinRequestMessage
    w.si.install_recorder(0x3252A0u, "sub_3252A0 (effect node step)", 0, 3);
    w.si.install_recorder(0x3A4360u, "sub_3A4360 (message request)", 0, 3);
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
hgp::Run pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw = {}) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b20b_setup(*wh);
    b20b_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    INFO("function " << std::string(what));
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

// One body alone (the rule checks), with its own stand-in world kept for inspection.
struct Solo {
    hgp::Run run;
    std::unique_ptr<StandInWorld> world;
};
Solo solo(Machine& m, const char* name, const Args& args, const HwCheck& hw = {}) {
    Solo s;
    s.world = std::make_unique<StandInWorld>();
    b20b_setup(*s.world);
    g_si[0] = s.world.get();
    g_fn[0] = case_of(name).hand;
    s.run = hgp::run_one(m, &thunk0, args, 1, hw);
    if (s.run.stopped) MESSAGE(std::string(name) << ": stopped: " << s.run.what << " at " << hex64(s.run.stop_pc));
    CHECK_FALSE(s.run.stopped);
    return s;
}
u32 v0_of(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
// One body alone with a float argument in $f12 (the randomised context's $f12 replaced).
float g_f12 = 0.0f;
void thunk_f12(EEContext& ctx) {
    std::memcpy(&ctx.fpr[12], &g_f12, 4);
    thunk0(ctx);
}
Solo solo_f12(Machine& m, const char* name, const Args& args, float f12) {
    Solo s;
    s.world = std::make_unique<StandInWorld>();
    b20b_setup(*s.world);
    g_si[0] = s.world.get();
    g_fn[0] = case_of(name).hand;
    g_f12 = f12;
    s.run = hgp::run_one(m, &thunk_f12, args, 1, {});
    CHECK_FALSE(s.run.stopped);
    return s;
}

// The ELF's data around the $gp area and the RW page, as loaded: every world starts from them.
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
constexpr u32 kWorldSize = 0x82000u;
constexpr u32 kBcm = kWorld + 0x0000u;       // bcm_panel.c work (29,208 bytes)
constexpr u32 kBpp = kWorld + 0x7400u;       // bpp_main.c work (23,140)
constexpr u32 kBsa = kWorld + 0xCF00u;       // the analysis panel (42,688)
constexpr u32 kSflGround = kWorld + 0x17600u;// sfl_ground.c work (36,232)
constexpr u32 kBi = kWorld + 0x20400u;       // bi_main.c work (62,720)
constexpr u32 kBaus = kWorld + 0x2F900u;     // baus_main.c work (10,580)
constexpr u32 kGcRes = kWorld + 0x37600u;    // gc_res.c work (9,996)
constexpr u32 kSflRes = kWorld + 0x3A000u;   // sfl_res.c work (132)
constexpr u32 kBse = kWorld + 0x3A100u;
constexpr u32 kBpRes = kWorld + 0x3A200u;    // bp_res.c work (108)
constexpr u32 kBrRes = kWorld + 0x3A300u;    // br_res.c work (80)
constexpr u32 kSflPanel = kWorld + 0x3A400u; // sfl_panel.c work (1,808)
constexpr u32 kBrPanel = kWorld + 0x3AC00u;  // br_panel.c work (9,840)
constexpr u32 kSets = kWorld + 0x3D000u;     // 8 sprite sets of 32 bytes
constexpr u32 kRecords = kWorld + 0x3D100u;  // 100 page records of 44 bytes
constexpr u32 kRasters = kWorld + 0x3E300u;  // 64 raster words
constexpr u32 kQuads = kWorld + 0x3E400u;    // 16 quads of 256 bytes
constexpr u32 kFloats = kWorld + 0x3F400u;   // 64 vec4s
constexpr u32 kFx = kWorld + 0x3F800u;       // effect nodes, records, instances, meshes, definitions (0x8800)
constexpr u32 kFresh = kWorld + 0x48000u;    // argument blocks (0x8000)
constexpr u32 kPsel = kWorld + 0x70000u;     // sfl_psel.c work (24,724)
constexpr u32 kBcmMain = kWorld + 0x76400u;  // bcm_main.c work (30,644)
constexpr u32 kCards = kWorld + 0x7DC00u;    // two card models of 0x800 bytes
constexpr u32 kGrid = kWorld + 0x7EC00u;     // a lighting grid (0x1000)
constexpr u32 kModels = kWorld + 0x7FC00u;   // two models of 0x400 bytes, then motion slots
constexpr u32 kSlots32 = kWorld + 0x80400u;  // 32-byte motion slots, slot words at +0x200

const s32 kSlots[] = {b::kGpBausMain, b::kGpSflRes, b::kGpBppMain, b::kGpSflPsel, b::kGpGcRes, b::kGpBseMain,
                      b::kGpBpRes, b::kGpBcmPanel, b::kGpBrRes, b::kGpBrPanel, b::kGpSflGround, b::kGpSflPanel,
                      b::kGpBiMain, bm::kGpWork};
const u32 kBlocks[] = {kBaus, kSflRes, kBpp, kPsel, kGcRes, kBse, kBpRes, kBcm, kBrRes, kBrPanel, kSflGround, kSflPanel,
                       kBi, kBcmMain};

// The sprite sets (header {self, pages, rasters, raster count, page count}) and their 44-byte page records.
void fill_sets(Machine& m, std::mt19937& rng) {
    for (u32 s = 0; s < 8; ++s) {
        const u32 a = kSets + 32 * s;
        st32(m, a + 0, a);
        const u32 rec = below(rng, 8);
        st32(m, a + 4, kRecords + 44 * rec);
        const u32 ras = below(rng, 32);
        st32(m, a + 8, kRasters + 4 * ras);
        const u32 nras = below(rng, 4);
        st32(m, a + 12, nras);
        st32(m, a + 16, 70);
    }
    for (u32 r = 0; r < 100; ++r) {
        const u32 a = kRecords + 44 * r;
        const u32 set = below(rng, 8);
        st32(m, a + 0, kSets + 32 * set);
        const u32 ras = below(rng, 4);
        st32(m, a + 4, ras);
        const u32 fl = below(rng, 4);
        st32(m, a + 8, fl);
        const u32 w = 4 + below(rng, 120);
        st32(m, a + 12, w);
        const u32 h = 4 + below(rng, 60);
        st32(m, a + 16, h);
        const u32 l = below(rng, 256);
        st32(m, a + 20, l);
        const u32 t = below(rng, 256);
        st32(m, a + 24, t);
        for (u32 k = 28; k < 44; ++k) {
            const u32 c = rng();
            st8(m, a + k, static_cast<u8>(c));
        }
    }
}
u32 a_set(std::mt19937& rng) { return kSets + 32 * below(rng, 8); }

// An effect node tree: a root and 1..3 children, each with an effect record of a small class (test_band20.cpp's).
void make_tree(Machine& m, u32 at, std::mt19937& rng) {
    const u32 n = 1 + below(rng, 3);
    for (u32 k = 0; k <= n; ++k) {
        const u32 node = at + 0x100u * k;
        for (u32 o = 0; o < 100; o += 4) {
            const float f = small_f(rng);
            stf(m, node + o, f);
        }
        const u32 col = rng();
        st32(m, node + 100, col);
        const bool md = chance(rng, 50);
        const u32 mode = rng() & 0x1FC;
        st32(m, node + 104, md ? mode : 0u);
        const float sb = small_f(rng);
        stf(m, node + 116, sb);
        const u32 start = below(rng, 4);
        st32(m, node + 128, start);
        const u32 frame = below(rng, 6);
        st32(m, node + 132, frame);
        st32(m, node + 140, k == 0 ? at + 0x100u : 0u);
        const u32 rec = at + 0x600u + 0x40u * k;
        st32(m, node + 144, rec);
        const u32 shared = below(rng, 2);
        st32(m, node + 152, shared);
        st32(m, node + 172, (k > 0 && k < n) ? node + 0x100u : 0u);
        const u32 cls = below(rng, 27);
        st16(m, rec + 4, static_cast<u16>(cls));
        const bool none = chance(rng, 30);
        const u32 inst = below(rng, 8);
        st32(m, rec + 8, none ? 0u : kFresh + 0x7000u + 0x100u * inst);
        st32(m, rec + 24, 0);
        st32(m, rec + 40, 0);
    }
}

// An empty H_Cdvd request list (sCdvdListHead +4): the file stand-in links its nodes from the stand-in heap there, and a
// node left by an earlier pair would meet a new node at the same heap address (a cycle the list walk never leaves).
void empty_request_list(Machine& m) { st32(m, 0x7E0380u + 4, 0); }

void module_world(Machine& m, std::mt19937& rng) {
    std::memcpy(m.at(kGpData), g_gp_data.data(), kGpDataSize);
    empty_request_list(m);
    std::memcpy(m.at(kRwPage), g_rw_page.data(), kRwPageSize);
    write_rw_slots(m);
    set_device_slots(m);
    hgp::random_world(m, kWorld, kWorldSize, rng);
    fill_sets(m, rng);
    for (std::size_t i = 0; i < std::size(kSlots); ++i) {
        const bool zero = chance(rng, 6);
        st32(m, gp_slot(kSlots[i]), zero ? 0u : kBlocks[i]);
    }
    const u32 answer = below(rng, 2);
    st32(m, 0x7CDFA4u, answer);  // the scenario mode of sub_17D800 (The Answer)
    for (u32 blk : kBlocks) {
        const u32 f0 = rng() & 0x3FFF;
        st32(m, blk + 0, f0);
        const u32 f1 = rng() & 0x1FF;
        st32(m, blk + 4, f1);
    }
    // sfl_res.c: requested / loaded bits, the sprite set
    const u32 ld = rng() & 0x1F;
    st32(m, kSflRes + b::kSrLoaded, ld);
    const u32 rq = rng() & 0x1F;
    st32(m, kSflRes + b::kSrRequested, rq);
    st32(m, kSflRes + b::kSrSprSet, a_set(rng));
    for (u32 i = 0; i < 6; ++i) st32(m, kSflRes + b::kSrEffect + 4 * i, kRecords + 44 * i);  // "rasters" with sizes
    for (u32 i = 0; i < 5; ++i) st32(m, kSflRes + b::kSrBase + 4 * i, kRecords + 44 * (10 + i));
    // bp_res.c: the sets
    for (u32 i = 0; i < 7; ++i) st32(m, kBpRes + b::kBrSets + 4 * i, a_set(rng));
    // bpp_main.c: 0..4 members with small ids
    const u32 nm = below(rng, 5);
    st32(m, kBpp + b::kBppCount, nm);
    for (u32 r = 0; r < 4; ++r) {
        const u32 mem = kBpp + b::kBppMembers + b::kBppMemberSize * r;
        const u32 mf = rng() & 7;
        st32(m, mem + b::kBmFlags, mf);
        const u32 id = below(rng, 8);
        st16(m, mem + b::kBmId, static_cast<u16>(id));
        const u32 pf = rng() & 0x3FF;
        st32(m, mem + b::kBmPanel + b::kBpnFlags, pf);
    }
    // bcm_panel.c: rows of the tactics list
    const u32 rows = 1 + below(rng, 6);
    st32(m, kBcm + bb::kBcpRowCount, rows);
    const u32 top = below(rng, rows);
    st32(m, kBcm + bb::kBcpRowTop, top);
    // bcm_main.c: skills, items, target and tactic rows, the cursors
    for (u32 k = 0; k < 9; ++k) {
        const u32 fl = below(rng, 4);
        st32(m, kBcmMain + bm::kSkills - 4 + 8 * k, fl);
        const u32 id = below(rng, 300);
        st16(m, kBcmMain + bm::kSkills + 8 * k, static_cast<u16>(id));
    }
    for (u32 k = 0; k < 20; ++k) {
        const u32 id = below(rng, 200);
        st16(m, kBcmMain + bm::kItems + 2 * k, static_cast<u16>(id));
    }
    const u32 ntg = 1 + below(rng, 5);
    st32(m, kBcmMain + bm::kTargetCount, ntg);
    for (u32 k = 0; k < 6; ++k) {
        const u32 row = kBcmMain + bm::kTargets + 24 * k;
        const u32 fl = below(rng, 4);
        st32(m, row + bm::kRowFlags, fl);
        const u32 kind = below(rng, 3);
        st32(m, row + bm::kRowKind, kind);
        const u32 pc = below(rng, 12);
        st16(m, row + bm::kRowPcId, static_cast<u16>(pc));
        const u32 tac = 1 + below(rng, 10);
        st32(m, row + bm::kRowTactic, tac);
    }
    const u32 tc = below(rng, ntg);
    st32(m, kBcmMain + bb::kBmTargetCursor, tc);
    const u32 sc = below(rng, 9);
    st32(m, kBcmMain + bb::kBmSkillCursor, sc);
    const u32 ic = below(rng, 20);
    st32(m, kBcmMain + bb::kBmItemCursor, ic);
    const u32 tlc = 1 + below(rng, 10);
    st32(m, kBcmMain + bm::kTacticLineCount, tlc);
    st32(m, kBcmMain + bm::kTacticLineCount + 4, tlc);
    for (u32 k = 0; k < 11; ++k) {
        const u32 t = 1 + below(rng, 10);
        st32(m, kBcmMain + 944 + 4 * k, t);
    }
    const u32 tr = below(rng, tlc);
    st32(m, kBcmMain + bb::kBmTacticRow, tr);
    // the persona select: entries, order, cursor block, states
    const u32 total = below(rng, 21);
    st32(m, kPsel + bb::kPsTotal, total);
    const u32 stock = below(rng, 13);
    st32(m, kPsel + bb::kPsStock, stock);
    const u32 shown = std::min<u32>(total, 8);
    st32(m, kPsel + b::kPsCount, shown);
    for (u32 k = 0; k < 20; ++k) {
        const u32 e = kPsel + bb::kPsEntries + 16 * k;
        const u32 fl = rng() & 7;
        st32(m, e + 0, fl);
        const u32 id = below(rng, 200);
        st16(m, e + 4, static_cast<u16>(id));
        const u32 arc = below(rng, 24);
        st32(m, e + 8, arc);
        const u32 lvl = 1 + below(rng, 99);
        st32(m, e + 12, lvl);
        const u32 ord = below(rng, std::max<u32>(total, 1));
        st32(m, kPsel + bb::kPsOrder + 4 * k, ord);
    }
    st32(m, kPsel + bb::kPsOrderCount, total);
    const u32 st = below(rng, 7);
    st32(m, kPsel + bb::kPsState, st);
    const u32 sst = below(rng, 5);
    st32(m, kPsel + bb::kPsSubState, sst);
    const u32 ptop = below(rng, std::max<u32>(total > 8 ? total - 8 : 1, 1));
    st32(m, kPsel + bb::kPsTop, ptop);
    st32(m, kPsel + bb::kPsShown, shown);
    const u32 cur = below(rng, std::max<u32>(total, 1));
    st32(m, kPsel + bb::kPsCursorRow, cur);
    st32(m, kPsel + bb::kPsCursorTotal, total);
    const u32 cap = below(rng, std::max<u32>(total, 1));
    st32(m, kPsel + bb::kPsCaptionEntry, cap);
    const u32 ff = below(rng, 7);
    st32(m, kPsel + bb::kPsFadeFrame, ff);
    const u32 fi = below(rng, 2);
    st32(m, kPsel + bb::kPsFadeIn, fi);
    const u32 cf = below(rng, 4);
    st32(m, kPsel + bb::kPsCaptionFrame, cf);
    const u32 ci = below(rng, 2);
    st32(m, kPsel + bb::kPsCaptionIn, ci);
    const u32 fa = below(rng, 11);
    stf(m, kPsel + bb::kPsAlpha, static_cast<float>(fa) / 10.0f);
    const u32 ans = below(rng, 2);
    st32(m, kPsel + bb::kPsAnswer, ans);
    // the analysis panel: flags, kind, fade
    const u32 bk = below(rng, 2);
    st32(m, kBsa + bb::kBsaKind, bk);
    const u32 bf = rng() & 0xFF;
    st32(m, kBsa + bb::kBsaFlags, bf);
    const u32 bsc = below(rng, 9);
    st32(m, kBsa + bb::kBsaSkillCount, bsc);
    const u32 bff = below(rng, 14);
    st32(m, kBsa + bb::kBsaFadeFrame, bff);
    const u32 bfm = below(rng, 3);
    st32(m, kBsa + bb::kBsaFadeMode, bfm);
    // sfl_ground.c / sfl_panel.c / bi_main.c
    const u32 sgm = below(rng, 6);
    st32(m, kSflGround + b::kSgMode, sgm);
    const u32 sgf = below(rng, 60);
    st32(m, kSflGround + b::kSgFrame, sgf);
    const u32 spm = below(rng, 3);
    st32(m, kSflPanel + b::kSpnMode, spm);
    for (u32 r = 0; r < 16; ++r) {
        const u32 rec = kBi + b::kBiRecordSize * r;
        const u32 fl = rng() & 0x1F;
        st32(m, rec, fl);
        const u32 kind = below(rng, 8);
        st32(m, rec + bb::kBiKind, kind);
        const u32 age = below(rng, 52);
        st32(m, rec + bb::kBiAge, age);
        const u32 id = below(rng, 8);
        st16(m, rec + bb::kBiUnitId, static_cast<u16>(id));
    }
    // card models
    for (u32 c = 0; c < 2; ++c) {
        const u32 g = kCards + 0x800u * c;
        const u32 fl = rng() & 0xF;
        st32(m, g + bb::kGmFlags, fl);
        const u32 kind = below(rng, 3);
        st32(m, g + bb::kGmKind, kind);
        for (u32 o = 16; o < 64; o += 4) {
            const float f = small_f(rng);
            stf(m, g + o, f);
        }
        const bool parent = chance(rng, 30);
        st32(m, g + bb::kGmParent, parent ? kFresh + 0x6000u : 0u);
        const u32 life = below(rng, 40) << 16;
        st32(m, g + bb::kGmLife, life);
        const u32 lm = below(rng, 2);
        st32(m, g + bb::kGmLifeMode, lm);
        st32(m, g + bb::kGmGrid, kGrid);
    }
    for (u32 o = 0; o < 0x1000; o += 4) {
        const float f = small_f(rng);
        stf(m, kGrid + o, f);
    }
    // models and motion slots
    for (u32 k = 0; k < 2; ++k) {
        const u32 md = kModels + 0x400u * k;
        const u32 kind = below(rng, 3);
        st16(m, md + bb::kMdlKind, static_cast<u16>(kind));
        const u32 ch = below(rng, 12);
        st16(m, md + bb::kMdlCharacter, static_cast<u16>(ch));
    }
    for (u32 k = 0; k < 4; ++k) {
        const u32 slot = kSlots32 + 32 * k;
        const u32 bits = below(rng, 4);
        st16(m, slot + 14, static_cast<u16>(bits));
        const bool used = chance(rng, 50);
        st32(m, kSlots32 + 0x200u + 4 * k, used ? slot : 0u);
    }
    // effect structures: trees, records, instances, meshes, definitions, particle systems
    make_tree(m, kFx + 0x0000u, rng);
    make_tree(m, kFx + 0x0800u, rng);
    for (u32 k = 0; k < 4; ++k) {  // records
        const u32 rec = kFx + 0x1000u + 0x40u * k;
        const u32 cls = below(rng, 27);
        st16(m, rec + 4, static_cast<u16>(cls));
        const bool none = chance(rng, 40);
        const u32 inst = below(rng, 8);
        st32(m, rec + 8, none ? 0u : kFresh + 0x7000u + 0x100u * inst);
    }
    for (u32 k = 0; k < 2; ++k) {  // class instances: kinds, a particle system, a few records
        const u32 in = kFx + 0x1500u + 0x100u * k;
        const u32 cnt = below(rng, 4);
        st32(m, in + b::kFiCount, cnt);
        const u32 kind = below(rng, 8);
        st16(m, in + bb::kFiKind, static_cast<u16>(kind));
        st8(m, in + b::kFiOwns, 0);
        for (u32 o = 52; o <= 80; o += 4) st32(m, in + o, 0);
        st32(m, in + b::kFiPsys, kFx + 0x1D00u);
        if (chance(rng, 50)) {
            st32(m, in + b::kFiNodes, kFx + 0x1700u);
            st32(m, in + b::kFiNodesMem, kFx + 0x1700u);
            for (u32 i = 0; i < 3; ++i) st32(m, kFx + 0x1700u + 4 * i, kFx + 0x1000u + 0x40u * i);
        }
    }
    {  // a particle system: count, flags, particles, live / base parameter blocks
        const u32 ps = kFx + 0x1D00u;
        const u32 cnt = below(rng, 5);
        st32(m, ps + 8, cnt);
        const u32 fl = below(rng, 2);
        st32(m, ps + 12, fl);
        st32(m, ps + 24, kFx + 0x1A00u);
        st32(m, ps + 32, kFx + 0x1E00u);
        st32(m, ps + 36, kFx + 0x1F00u);
        for (u32 o = 0; o < 0x200; o += 4) {
            const float f = small_f(rng);
            stf(m, kFx + 0x1E00u + o, f);
        }
        for (u32 p = 0; p < 4; ++p) {
            const u32 pa = kFx + 0x1A00u + 32 * p;
            for (u32 o = 0; o < 32; o += 4) {
                const float f = small_f(rng);
                stf(m, pa + o, f);
            }
            const bool live = chance(rng, 70);
            const u32 age = below(rng, 30);
            st32(m, pa + 16, live ? age : 0xFFFFFFFFu);
        }
    }
    for (u32 k = 0; k < 2; ++k) {  // effect definitions
        const u32 d = kFx + 0x2000u + 0x100u * k;
        const u32 cls = below(rng, 27);
        st16(m, d + bb::kFdClass, static_cast<u16>(cls));
        const u32 type = below(rng, 12);
        st16(m, d + bb::kFdType, static_cast<u16>(type));
        const u32 kind = below(rng, 8);
        st16(m, d + bb::kFdKind, static_cast<u16>(kind));
    }
    for (u32 o = 0; o < 0x400; o += 4) {
        const float f = small_f(rng);
        stf(m, kFloats + o, f);
    }
}

// An argument of a kind.
u64 arg_of(char k, std::mt19937& rng) {
    if (chance(rng, 3)) return hgp::random_arg(rng, kWorld, kWorldSize);  // anything, now and then
    switch (k) {
    case 'w': return sx(kFresh + 0x10u * below(rng, 16));
    case 'q': return sx(kQuads + 0x100u * below(rng, 4));
    case 'n': {
        const bool big = chance(rng, 10);
        const u32 r = rng();
        return big ? r : r % 1200;
    }
    case 'd': return below(rng, 10);
    case 'x': return sx(kFloats + 0x10u * below(rng, 32));
    case 'm': return sx(kFloats + 0x100u * below(rng, 2));
    case 'i': {
        const bool far = chance(rng, 10);
        const u32 r = rng();
        return far ? r % 40 : r % 8;
    }
    case 'u': return below(rng, 10);
    case 'B': return sx(kBsa);
    case 'k': return below(rng, 3);
    case 'P': return sx(kBpp + b::kBppMembers + b::kBppMemberSize * below(rng, 4) + b::kBmPanel);
    case 'g': return sx(kCards + 0x800u * below(rng, 2));
    case 'G': return sx(kGrid);
    case 'A': return below(rng, 24);
    case 'R': return sx(kPsel + bb::kPsRows + 2320 * below(rng, 8));
    case 'E': return sx(kPsel + bb::kPsEntries + 16 * below(rng, 20));
    case 'l': return below(rng, 2);
    case 'O': return sx(kModels + 0x400u * below(rng, 2));
    case 'S': return sx(kSlots32 + 0x200u + 4 * below(rng, 4));
    case 'K': return 1 + below(rng, 2);
    case 'L': return below(rng, 8);
    case 'M': return sx(kFx + 0x1200u);
    case 'D': return sx(kFx + 0x2000u + 0x100u * below(rng, 2));
    case 'r': return sx(kFx + 0x1000u + 0x40u * below(rng, 4));
    case 'N': return sx(kFx + 0x800u * below(rng, 2));
    case 'I': return sx(kFx + 0x1500u + 0x100u * below(rng, 2));
    case 'Y': return sx(kFx + 0x1D00u);
    default: return hgp::random_arg(rng, kWorld, kWorldSize);
    }
}
// The arguments of a case: $a0..$a3 in Args, $t0 (a fifth argument) through HwCheck::gpr_in.
void args_for(const Case& c, std::mt19937& rng, Args& a, HwCheck& hw) {
    const std::size_t n = std::strlen(c.kinds);
    for (unsigned i = 0; i < 4; ++i) {
        const u64 v = i < n ? arg_of(c.kinds[i], rng) : hgp::random_arg(rng, kWorld, kWorldSize);
        a[i] = v;
    }
    if (n > 4) {
        const u64 t0 = arg_of(c.kinds[4], rng);
        hw.gpr_in[GPR_T0] = t0;
    }
}

u32 seeds_or(u32 def) {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    return env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : def;
}

}  // namespace

TEST_CASE("game(band20b): every body equals its recompiled body on random worlds") {
    auto m = new_machine();
    if (!m) return;
    const u32 seeds = seeds_or(16);
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int pairs = 0, stops = 0;
    for (const Case& c : cases()) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, 0x10000u, rng);
            empty_request_list(*m);
            Args args{};
            for (unsigned i = 0; i < 4; ++i) {
                const u64 v = hgp::random_arg(rng, kWorld, 0x10000u);
                args[i] = v;
            }
            stops += pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs over " << cases().size() << " functions, " << stops << " ended at a compared stop");
}

TEST_CASE("game(band20b): every body equals its recompiled body on module worlds") {
    auto m = new_machine();
    if (!m) return;
    const u32 seeds = seeds_or(32);
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
            Args a{};
            HwCheck hw;
            args_for(c, rng, a, hw);
            const hgp::Run r = pair(*m, c.hand, c.recomp, a, seed, c.name, hw);
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

TEST_CASE("game(band20b): every body on the replay snapshots' real works") {
    int used = 0, pairs = 0, stops = 0;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    const char* pick = std::getenv("P3FES_B20B_SNAPSHOT");  // one snapshot by name (debugging)
    for (const char* dir : {"b_5800", "fx2_battle_5450", "battle_ref_6150", "b20_climb_10850", "b20_climb_11200",
                            "climb_ref_17000"}) {
        if (pick && std::string(pick) != dir) continue;
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        ++used;
        auto m = new_machine();
        if (!m) return;
        int live = 0;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        for (s32 off : kSlots) live += ld32(*m, gp_slot(off)) ? 1 : 0;
        MESSAGE(std::string(dir) << ": " << live << " of the 14 module slots set");
        std::mt19937 rng{0xB20Bu};
        for (const Case& c : cases()) {
            if (only && std::string(only) != c.name) continue;
            for (int rep = 0; rep < 3; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %d\n", dir, c.name, rep);
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                write_rw_slots(*m);
                set_device_slots(*m);
                // pointer kinds: blocks of random words built in the stand-in heap's tail (zero in every snapshot)
                std::mt19937 wr{static_cast<u32>(rep) * 31u + c.addr};
                hgp::random_world(*m, kStandInHeap + 0x200000u, 0x20000u, wr);
                Args a{};
                HwCheck hw;
                const std::size_t n = std::strlen(c.kinds);
                for (unsigned i = 0; i < 4; ++i) {
                    const char k = i < n ? c.kinds[i] : 'i';
                    const bool ptr = std::strchr("wqxmBPgGROSMDrNIYE", k) != nullptr;
                    const u32 blk = below(rng, 16);
                    const u64 v = ptr ? sx(kStandInHeap + 0x200000u + 0x1000u * blk) : arg_of(k, wr);
                    a[i] = v;
                }
                const hgp::Run r = pair(*m, c.hand, c.recomp, a, static_cast<u32>(rep) + 1, c.name, hw);
                ++pairs;
                stops += r.stopped ? 1 : 0;
            }
        }
    }
    MESSAGE("snapshots: " << used << " used, " << pairs << " pairs, " << stops << " ended at a compared stop");
}

// --- documented rules -------------------------------------------------------------------------------------------------

TEST_CASE("game(band20b): the persona select's arcana pages, digit pages and centred numbers") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{5};
    module_world(*m, rng);
    st32(*m, gp_slot(b::kGpSflRes), kSflRes);
    st32(*m, kSflRes + b::kSrLoaded, 0x10);  // the spr set is in
    const u32 set = ld32(*m, kSflRes + b::kSrSprSet);
    const u32 pages = ld32(*m, set + 4);
    // sub_2180B0(arcana): the page record of the spr set -- 1..12 -> 10..21, 13..22 -> 0..9
    for (u32 arcana = 1; arcana <= 22; ++arcana) {
        const u32 want = arcana <= 12 ? arcana + 9 : arcana - 13;
        INFO("arcana " << arcana);
        CHECK(v0_of(solo(*m, "sub_2180B0", {arcana, 0, 0, 0}).run) == pages + 44 * want);
    }
    int checks = 0;
    // the "%d" writers: the digit i from the right gets page base + digit (sub_209BA0 46, sub_218310 39)
    st32(*m, gp_slot(b::kGpBpRes), kBpRes);
    st32(*m, kBpRes + b::kBrLoaded, 1);
    const u32 raster = kFresh + 0x4000u;  // every raster word -> one raster record of 64 x 64 texels
    for (u32 o = 0; o < 0x100; o += 4) st32(*m, raster + o, 64);
    for (u32 i = 0; i < 64; ++i) st32(*m, kRasters + 4 * i, raster);
    for (u32 value : {0u, 7u, 42u, 305u}) {
        for (const char* fn : {"sub_209940", "sub_218250"}) {
            const u32 q = kQuads;
            std::memset(ram(*m, q), 0, 4 * 256);
            solo(*m, fn, {sx(q), 4, value, 0});
            const bool baus = fn[5] == '0';
            const u32 dset = baus ? ld32(*m, kBpRes + b::kBrSets + 4) : set;  // panel set 1 / the spr set
            const u32 base = baus ? 46u : 39u;
            u32 v = value, i = 0;
            do {
                INFO(fn << " value " << value << " digit " << i);
                // the quad equals the one sub_21D3B0 itself makes from page base + digit (a reference quad at kQuads + 8)
                const u32 page = ld32(*m, dset + 4) + 44 * (base + v % 10);
                const u32 ref = kQuads + 256 * 8;
                std::memset(ram(*m, ref), 0, 256);
                hgp::run_one(*m, &rg::fn_sub_21D3B0_0021d3b0, {sx(ref), sx(page), 0, 0}, 1, {});
                CHECK(std::memcmp(ram(*m, q + 256 * i), ram(*m, ref), 256) == 0);
                ++checks;
                v /= 10;
                ++i;
            } while (v);
        }
    }
    // sub_218370 / sub_218570: value's digits centred in an n-digit field, 27 / 19 px apart (halves rounded to zero)
    for (u32 value : {3u, 58u, 120u}) {
        for (const char* fn : {"sub_218370", "sub_218570"}) {
            const s32 step = fn[7] == '3' ? 27 : 19;  // sub_218370 27 px, sub_218570 19 px
            const u32 n = 3;
            const u32 q = kQuads, xy = kFloats;
            stf(*m, xy, 300.0f);
            stf(*m, xy + 4, 40.0f);
            solo(*m, fn, {sx(q), n, value, sx(xy)});
            const s32 len = value >= 100 ? 3 : value >= 10 ? 2 : 1;
            for (s32 i = 0; i < static_cast<s32>(n); ++i) {
                const float x = ldf(*m, q + 256 * static_cast<u32>(i));
                const float y = ldf(*m, q + 256 * static_cast<u32>(i) + 4);
                INFO(fn << " value " << value << " quad " << i);
                if (i < len) {
                    const float want = (static_cast<float>(step * static_cast<s32>(n) / 2) +
                                        (300.0f + static_cast<float>(step * (len - 1 - i)))) -
                                       static_cast<float>(step * len / 2);
                    CHECK(x == want);
                } else {
                    CHECK(x == 300.0f);
                    CHECK(ldf(*m, q + 256 * static_cast<u32>(i) + 64) == 300.0f);  // zero width
                }
                CHECK(y == 40.0f);
                ++checks;
            }
        }
    }
    MESSAGE("persona select layouts: " << checks << " quad checks");
}

TEST_CASE("game(band20b): the persona select's kept / released lists and the entry append") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{6};
    module_world(*m, rng);
    st32(*m, gp_slot(b::kGpSflPsel), kPsel);
    const u32 flags[] = {0, 1, 2, 3, 2, 6, 1, 2};
    st32(*m, kPsel + bb::kPsTotal, 8);
    for (u32 k = 0; k < 8; ++k) {
        st32(*m, kPsel + bb::kPsEntries + 16 * k, flags[k]);
        st16(*m, kPsel + bb::kPsEntries + 16 * k + 4, static_cast<u16>(100 + k));
    }
    const u32 ids = kFresh, cnt = kFresh + 0x100u;
    solo(*m, "sub_217410", {sx(ids), sx(cnt), 0, 0});  // bit 1 set, bit 0 clear: entries 2, 4, 5, 7
    CHECK(ld32(*m, cnt) == 4u);
    CHECK(ld16(*m, ids + 0) == 102u);
    CHECK(ld16(*m, ids + 2) == 104u);
    CHECK(ld16(*m, ids + 4) == 105u);
    CHECK(ld16(*m, ids + 6) == 107u);
    solo(*m, "sub_2174D0", {sx(ids), sx(cnt), 0, 0});  // bit 0 set, bit 1 clear: entries 1, 6
    CHECK(ld32(*m, cnt) == 2u);
    CHECK(ld16(*m, ids + 0) == 101u);
    CHECK(ld16(*m, ids + 2) == 106u);
    solo(*m, "sub_217590", {0x1234u, 0, 0, 0});  // the append: flags 2, the id, the count + 1
    CHECK(ld32(*m, kPsel + bb::kPsTotal) == 9u);
    CHECK(ld32(*m, kPsel + bb::kPsEntries + 16 * 8) == 2u);
    CHECK(ld16(*m, kPsel + bb::kPsEntries + 16 * 8 + 4) == 0x1234u);
    // the fades: sub_2187B0 in (direction 1), sub_219AB0 the caption out (direction 0)
    st32(*m, kPsel, 0);
    solo(*m, "sub_2187B0", {0, 0, 0, 0});
    CHECK(ld32(*m, kPsel + bb::kPsFadeFrame) == 0u);
    CHECK(ld32(*m, kPsel + bb::kPsFadeIn) == 1u);
    CHECK(ld32(*m, kPsel) == 4u);
    solo(*m, "sub_219AB0", {0, 0, 0, 0});
    CHECK(ld32(*m, kPsel + bb::kPsCaptionIn) == 0u);
    CHECK(ld32(*m, kPsel) == 0x14u);
    CHECK(v0_of(solo(*m, "sub_2168A0", {0, 0, 0, 0}).run) == 0u);
}

TEST_CASE("game(band20b): class instances, the two scale slots and the card model's copies") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{7};
    module_world(*m, rng);
    // sub_326490(n): a 96-byte RwMalloc block, zeroed, {n, -1, 1.0}
    for (u32 n : {0u, 5u, 300u}) {
        const Solo s = solo(*m, "sub_326490", {n, 0, 0, 0});
        const u32 inst = v0_of(s.run);
        CHECK(s.world->heap.size_of(inst) == 96u);
        CHECK(ld32(*m, inst + b::kFiCount) == n);
        CHECK(ld32(*m, inst + bb::kFiFrame) == 0xFFFFFFFFu);
        CHECK(ldf(*m, inst + bb::kFiScale) == 1.0f);
        for (u32 o = 12; o < 96; o += 4) CHECK(ld32(*m, inst + o) == 0u);
    }
    // the scale slots: live (+32) = base (+36) x s on their fields, nothing else written
    const u32 ps = kFx + 0x1D00u, live = kFx + 0x1E00u, base = kFx + 0x1F00u;
    struct Slot {
        const char* fn;
        std::vector<u32> fields;
    };
    const Slot slots[] = {{"sub_32EAB0", {100, 104, 116, 124, 132, 200, 216, 224, 228}}, {"sub_32F8B0", {100, 104, 116, 124, 132}}};
    for (const Slot& sl : slots) {
        for (u32 o = 0; o < 0x100; o += 4) stf(*m, live + o, -1.0f);
        for (u32 o = 0; o < 0x100; o += 4) stf(*m, base + o, static_cast<float>(o) / 8.0f);
        solo_f12(*m, sl.fn, {sx(ps), 0, 0, 0}, 1.5f);
        for (u32 o = 0; o < 0x100; o += 4) {
            const bool field = std::find(sl.fields.begin(), sl.fields.end(), o) != sl.fields.end();
            INFO(sl.fn << " +" << o);
            CHECK(ldf(*m, live + o) == (field ? static_cast<float>(o) / 8.0f * 1.5f : -1.0f));
        }
    }
    // gc_model.c: the position out, the quaternion in, the glow (kind 1 only asserts otherwise -- it stores anyway)
    const u32 g = kCards, out = kFresh;
    stf(*m, g + bb::kGmPos, 1.5f);
    stf(*m, g + bb::kGmPos + 4, -2.0f);
    stf(*m, g + bb::kGmPos + 8, 8.25f);
    solo(*m, "sub_20D670", {sx(g), sx(out), 0, 0});
    CHECK(ldf(*m, out) == 1.5f);
    CHECK(ldf(*m, out + 4) == -2.0f);
    CHECK(ldf(*m, out + 8) == 8.25f);
    for (u32 i = 0; i < 4; ++i) stf(*m, kFloats + 4 * i, 0.25f * static_cast<float>(i + 1));
    solo(*m, "sub_20D690", {sx(g), sx(kFloats), 0, 0});
    for (u32 i = 0; i < 4; ++i) CHECK(ldf(*m, g + bb::kGmRot + 4 * i) == 0.25f * static_cast<float>(i + 1));
    st32(*m, g + bb::kGmShow, 0);
    st32(*m, g + bb::kGmFlags, 0);
    st32(*m, g + bb::kGmKind, 0);
    solo(*m, "sub_20D710", {sx(g), 0, 0, 0});
    CHECK(ld32(*m, g + bb::kGmShow) == 2u);
    CHECK(ld32(*m, g + bb::kGmFlags) == 2u);
}

TEST_CASE("game(band20b): a model's motion-file request by kind, id, weapon and story flags") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{8};
    module_world(*m, rng);
    st32(*m, 0x7CDFA4u, 0);  // not The Answer
    struct Want {
        u32 kind, id;
        const char* path;  // the H_Cdvd request (the file stand-in's log), "" none
    };
    // an enemy: "model/enemy/em%03X.se"; the special enemies 226..231 / 278..280 request nothing; a character other than
    // the protagonist and id 9: "model/player/bc%03X.acx" or its "a" variant when the id's story flag is set
    const Want wants[] = {{2, 0x45, "model/enemy/em045.se"}, {2, 227, ""}, {2, 279, ""}, {2, 281, "model/enemy/em119.se"},
                          {1, 0, "model/player/bc000.acx"}};
    for (const Want& w : wants) {
        const u32 slotw = kSlots32 + 0x200u;
        st32(*m, slotw, 0);  // no slot yet: one is allocated
        empty_request_list(*m);
        const Solo s = solo(*m, "sub_31E4D0", {sx(slotw), w.kind, w.id, 0});
        std::string got;
        for (const StandInCall& c : s.world->si.log)
            if (c.va == kHCdvdRequestFn) got = c.text;
        INFO("kind " << w.kind << " id " << w.id << " got '" << got << "'");
        if (*w.path) {
            CHECK(got.find(FakeCd::build_path(w.path)) != std::string::npos);
            const u32 slot = ld32(*m, slotw);
            CHECK(s.world->heap.size_of(slot) == 32u);
            CHECK(ld16(*m, slot + 8) == w.kind);
            CHECK(ld16(*m, slot + 10) == w.id);
            CHECK((ld16(*m, slot + 14) & 2u) == 2u);
        } else {
            CHECK(got.empty());
            CHECK(ld32(*m, slotw) == 0u);
        }
    }
}

#else

TEST_CASE("game(band20b): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
