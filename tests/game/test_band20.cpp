// Phase 5 pair tests for slice band20 (game/src/battle/band20_*.cpp, game/src/fx/band20_fx.cpp): every body against its
// recompiled body (__recomp) on identical guest machines, compared by tests/game/handgen_pairs.h -- the whole register
// file and the cycle count at every check point and at the return / stop, all 32 MiB of RAM (a PairRange: the dead
// stack and every stray store), the scratchpad, the BIOS window and the bus log -- plus the stand-in call log (both
// bodies meet the same deterministic stand-ins: the heap behind the RW slots 0x960178 / 0x96017C, printf, sprintf, the
// H_Cdvd file layer, and recorders behind the RW device slots the draw functions call through).
//
//   * random worlds (the p3fes_handgen skeleton's world, with the stand-ins);
//   * module worlds: every $gp slot of band20.h pointing at a work block shaped as the bodies read it (flag and loaded
//     words with a few bits, counts and indices in range, sprite sets / page records, party-panel members, the command
//     panel's states, effect node trees with children and effect records, class instances, particle systems, colour
//     tracks, image and file headers) -- now and then a slot 0 (the K_Assert paths) --, every other word random, and
//     arguments of the kind each function takes ($a0..$a3, $t0);
//   * the replay snapshots: b_5800 / fx2_battle_5450 (the battle panels live: baus, bpp, bse, bp_res, bcm, bi),
//     battle_ref_6150 (the result screen: br_res, br_panel) and b20_climb_10850 / b20_climb_11200 (Shuffle Time live,
//     made for this slice from the climb in reference mode): the real works behind the real slots;
//   * documented-rule checks on the host (the hand body alone): the bp_ifont / bpp_panel / baus digit layouts, the card
//     x of gc_model.c, the card grid's index list, the ailment icon map, the card side map, the colour track's alpha
//     envelope, the sprite set built from i_change_per01.spr, the panel archive
//     through request -> file service -> update on the file stand-in, the Shuffle Time effect archive's request.
#include "handgen_pairs.h"
#include "stand_ins.h"
#include "write_tracker.h"

#include "p3fes/game/band20.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
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

#define P3FES_B20_FUNCS(X) \
    X(sub_208AD0, 00208ad0) X(sub_208B20, 00208b20) X(sub_208F60, 00208f60) X(sub_209540, 00209540)                  \
    X(sub_209A00, 00209a00) X(sub_209C80, 00209c80) X(sub_209D40, 00209d40) X(sub_209E80, 00209e80)                  \
    X(sub_209E90, 00209e90) X(sub_20C660, 0020c660) X(sub_20C8D0, 0020c8d0) X(sub_20CC80, 0020cc80)                  \
    X(sub_20D630, 0020d630) X(sub_20D820, 0020d820) X(sub_20E030, 0020e030) X(sub_20E200, 0020e200)                  \
    X(sub_20E380, 0020e380) X(sub_20E3D0, 0020e3d0) X(sub_20E610, 0020e610) X(sub_20E790, 0020e790)                  \
    X(sub_20E800, 0020e800) X(sub_20EA80, 0020ea80) X(sub_20EB40, 0020eb40) X(sub_20ECC0, 0020ecc0)                  \
    X(sub_20ED50, 0020ed50) X(sub_20ED70, 0020ed70) X(sub_20EDC0, 0020edc0) X(sub_20EDF0, 0020edf0)                  \
    X(sub_20F260, 0020f260) X(sub_20F3B0, 0020f3b0) X(sub_20F680, 0020f680) X(sub_20F9A0, 0020f9a0)                  \
    X(sub_20FDD0, 0020fdd0) X(sub_20FE20, 0020fe20) X(sub_210D90, 00210d90) X(sub_213E80, 00213e80)                  \
    X(sub_215770, 00215770) X(sub_215AA0, 00215aa0) X(sub_216800, 00216800) X(sub_2172C0, 002172c0)                  \
    X(sub_219B00, 00219b00) X(sub_219D90, 00219d90) X(sub_21A120, 0021a120) X(sub_21A1B0, 0021a1b0)                  \
    X(sub_21A840, 0021a840) X(sub_21B4A0, 0021b4a0) X(sub_21B650, 0021b650) X(sub_21B660, 0021b660)                  \
    X(sub_21B920, 0021b920) X(sub_21B940, 0021b940) X(sub_21BCB0, 0021bcb0) X(sub_21C5D0, 0021c5d0)                  \
    X(sub_21C640, 0021c640) X(sub_21C6B0, 0021c6b0) X(sub_21C790, 0021c790) X(sub_21C9F0, 0021c9f0)                  \
    X(sub_21CC20, 0021cc20) X(sub_21EC40, 0021ec40) X(sub_21F0C0, 0021f0c0) X(sub_21F140, 0021f140)                  \
    X(sub_21F150, 0021f150) X(sub_21F3C0, 0021f3c0) X(sub_21F410, 0021f410) X(sub_221B60, 00221b60)                  \
    X(sub_223290, 00223290) X(sub_224150, 00224150) X(sub_224940, 00224940) X(sub_225040, 00225040)                  \
    X(sub_2255F0, 002255f0) X(sub_225670, 00225670) X(sub_2257F0, 002257f0) X(sub_226040, 00226040)                  \
    X(sub_2265D0, 002265d0) X(sub_227800, 00227800) X(sub_227F30, 00227f30) X(sub_2289B0, 002289b0)                  \
    X(sub_228E40, 00228e40) X(sub_229B40, 00229b40) X(sub_22A2B0, 0022a2b0) X(sub_22AE80, 0022ae80)                  \
    X(sub_22B530, 0022b530) X(sub_22B630, 0022b630) X(sub_22BCF0, 0022bcf0) X(sub_22C0A0, 0022c0a0)                  \
    X(sub_22C2D0, 0022c2d0) X(sub_22C720, 0022c720) X(sub_22C850, 0022c850) X(sub_22C8A0, 0022c8a0)                  \
    X(sub_22DF10, 0022df10) X(sub_22E900, 0022e900) X(sub_22E9A0, 0022e9a0) X(sub_22EA40, 0022ea40)                  \
    X(sub_22EB30, 0022eb30) X(sub_22ECB0, 0022ecb0) X(sub_22F1C0, 0022f1c0) X(sub_22F3B0, 0022f3b0)                  \
    X(sub_22FA80, 0022fa80) X(sub_232EA0, 00232ea0) X(sub_233C00, 00233c00) X(sub_234070, 00234070)                  \
    X(sub_2350F0, 002350f0) X(sub_235F30, 00235f30) X(sub_235FF0, 00235ff0) X(sub_236390, 00236390)                  \
    X(sub_238A50, 00238a50) X(sub_238BF0, 00238bf0) X(sub_238DC0, 00238dc0) X(sub_23B990, 0023b990)                  \
    X(sub_23C350, 0023c350) X(sub_23C520, 0023c520) X(sub_23C850, 0023c850) X(sub_23D0E0, 0023d0e0)                  \
    X(sub_23D130, 0023d130) X(sub_23D1F0, 0023d1f0) X(sub_23D7B0, 0023d7b0) X(sub_23D870, 0023d870)                  \
    X(sub_23D8F0, 0023d8f0) X(sub_23DAC0, 0023dac0) X(sub_23E970, 0023e970) X(sub_23EE50, 0023ee50)                  \
    X(sub_23F390, 0023f390) X(sub_23F3E0, 0023f3e0) X(sub_23F430, 0023f430) X(sub_23F480, 0023f480)                  \
    X(sub_23F500, 0023f500) X(sub_324310, 00324310) X(sub_3243F0, 003243f0) X(sub_324510, 00324510)                  \
    X(sub_324740, 00324740) X(sub_3247D0, 003247d0) X(sub_324820, 00324820) X(sub_325500, 00325500)                  \
    X(sub_3257E0, 003257e0) X(sub_325B80, 00325b80) X(sub_325C10, 00325c10) X(sub_325D60, 00325d60)                  \
    X(sub_325E40, 00325e40) X(sub_326030, 00326030) X(sub_326280, 00326280) X(sub_3263B0, 003263b0)                  \
    X(sub_326740, 00326740) X(sub_326C70, 00326c70) X(sub_326CF0, 00326cf0) X(sub_326DB0, 00326db0)                  \
    X(sub_326E50, 00326e50) X(sub_326F00, 00326f00) X(sub_3271C0, 003271c0) X(sub_3282E0, 003282e0)                  \
    X(sub_329800, 00329800) X(sub_3299B0, 003299b0) X(sub_329D60, 00329d60) X(sub_329ED0, 00329ed0)                  \
    X(sub_32A120, 0032a120) X(sub_32B990, 0032b990) X(sub_32C2B0, 0032c2b0) X(sub_32CD70, 0032cd70)                  \
    X(sub_32D7C0, 0032d7c0) X(sub_32E110, 0032e110)

namespace p3fes::recomp_gen {
#define P3FES_B20_DECL(name, addr) \
    void fn_##name##_##addr(EEContext&); \
    void fn_##name##_##addr##__recomp(EEContext&);
P3FES_B20_FUNCS(P3FES_B20_DECL)
#undef P3FES_B20_DECL
void fn_H_Cdvd_Update_00100980(EEContext&);  // not emitted: served by the stand-ins' file layer
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

// --- the functions and the kinds of their arguments ($a0..$a3, $t0) --------------------------------------------------
// w a fresh work block   q 2D quads   Q an Im2D quad   p a page record   n a number   x / v float vectors   i an index
// c a card count 1..7   u a u16 id   b ailment bits   y a digit style 0 / 1   f a sprite-font index   h an s16 side word
// e the analysis panel   P a member panel   m a card model   r an RGBA   S a sprite file   s a sprite set   G an image
// F a 3-entry image file   K the 10-entry card file   M an effect mesh   R an effect record   N an effect node tree
// I a class instance   J a particle-drawing instance   T a colour track   Y a particle system (scale slots)
// k a mesh kind   a anything
struct Kinds {
    u32 addr;
    const char* kinds;
};
const Kinds kKinds[] = {
    {0x208AD0u, "w"}, {0x209A00u, "qnnx"}, {0x209D40u, "h"}, {0x20C660u, "ic"}, {0x20CC80u, "mr"},
    {0x20D630u, "mx"}, {0x20E610u, "i"}, {0x20E800u, "F"}, {0x20ED50u, "w"}, {0x20F9A0u, "u"},
    {0x20FE20u, "w"}, {0x210D90u, "e"}, {0x213E80u, "e"}, {0x215770u, "e"}, {0x21B4A0u, "K"},
    {0x21B650u, "w"}, {0x21B920u, "w"}, {0x21C790u, "a"}, {0x21C9F0u, "S"}, {0x21CC20u, "s"},
    {0x21EC40u, "G"}, {0x21F0C0u, "w"}, {0x21F150u, "i"}, {0x22C720u, "Pu"}, {0x22C850u, "P"},
    {0x22C8A0u, "P"}, {0x22DF10u, "P"}, {0x22E900u, "Pn"}, {0x22E9A0u, "Pn"}, {0x22EA40u, "qn"},
    {0x22EB30u, "qnx"}, {0x22ECB0u, "Qp"}, {0x22F1C0u, "Pb"}, {0x22F3B0u, "P"}, {0x22FA80u, "P"},
    {0x232EA0u, "P"}, {0x235F30u, "qnn"}, {0x235FF0u, "qnnyx"}, {0x238A50u, "qnnfx"}, {0x238BF0u, "qnnfx"},
    {0x238DC0u, "qnnfx"}, {0x23C520u, "qxxx"}, {0x23C850u, "qr"}, {0x23F480u, "w"}, {0x324310u, "M"},
    {0x3243F0u, "Ma"}, {0x324510u, "Ma"}, {0x324740u, "R"}, {0x3247D0u, "R"}, {0x324820u, "R"},
    {0x325500u, "Nv"}, {0x3257E0u, "N"}, {0x325B80u, "N"}, {0x325C10u, "Nv"}, {0x325D60u, "Nv"},
    {0x325E40u, "N"}, {0x326030u, "Nn"}, {0x326280u, "Nv"}, {0x3263B0u, "Nv"}, {0x326740u, "I"},
    {0x326C70u, "Iii"}, {0x326CF0u, "Iik"}, {0x326DB0u, "Ii"}, {0x326E50u, "Ia"}, {0x326F00u, "Ia"},
    {0x3271C0u, "Ia"}, {0x3282E0u, "J"}, {0x329800u, "vv"}, {0x3299B0u, "v"}, {0x329D60u, "vv"},
    {0x329ED0u, "v"}, {0x32A120u, "Tvnn"}, {0x32B990u, "Y"}, {0x32C2B0u, "Y"}, {0x32CD70u, "Y"},
    {0x32D7C0u, "Y"}, {0x32E110u, "Y"},
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
#define P3FES_B20_CASE(name, addr) \
    v.push_back({#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp, ""});
    P3FES_B20_FUNCS(P3FES_B20_CASE)
#undef P3FES_B20_CASE
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
bool chance(std::mt19937& rng, u32 pct) { return rng() % 100 < pct; }
float small_f(std::mt19937& rng) {
    const int n = static_cast<int>(rng() % 2001) - 1000;
    const int d = 1 + static_cast<int>(rng() % 50);
    return static_cast<float>(n) / static_cast<float>(d);
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
// Heap blocks an earlier world left in guest memory, kept out of a later pair's heaps (set around such pairs).
std::vector<std::pair<u32, u32>> g_reserve;
void b20_setup(StandInWorld& w) {
    install_standard(w);
    w.si.install_recorder(kRec0, "rw_device_0", 0, 3);
    w.si.install_recorder(kRec1, "rw_device_1", 1, 3);
    // the device steps under the RW raster functions bp_tex.c calls (not emitted): SkyRasterCreate 0x4DB350 and the
    // destroy's 0x4DD2E0 (docs/ANALYSIS/14_vu1_gs_census.md), recorders -> 1, so creation and release run to their end
    w.si.install_recorder(0x4DB350u, "SkyRasterCreate", 1, 3);
    w.si.install_recorder(0x4DD2E0u, "sub_4DD2E0 (the raster destroy's device step)", 1, 3);
    for (const auto& [p, n] : g_reserve) w.heap.reserve(p, n);
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
    b20_setup(*wh);
    b20_setup(*wr);
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
Solo solo(Machine& m, Fn fn, const Args& args, const HwCheck& hw = {}, StandInWorld* keep = nullptr) {
    Solo s;
    if (!keep) {
        s.world = std::make_unique<StandInWorld>();
        b20_setup(*s.world);
        keep = s.world.get();
    }
    g_si[0] = keep;
    g_fn[0] = fn;
    s.run = hgp::run_one(m, &thunk0, args, 1, hw);
    return s;
}
u32 v0_of(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
float f0_of(const hgp::Run& r) {
    float f;
    std::memcpy(&f, &r.end.fpr[0], 4);
    return f;
}
hgp::Run run_ok(Machine& m, const char* name, const Args& a, const HwCheck& hw = {}, StandInWorld* keep = nullptr) {
    const Solo s = solo(m, case_of(name).hand, a, hw, keep);
    if (s.run.stopped) MESSAGE(std::string(name) << ": stopped: " << s.run.what << " at " << hex64(s.run.stop_pc));
    CHECK_FALSE(s.run.stopped);
    return s.run;
}

// --- long runs (savedata's pair_long): the raster builders copy texels with a check point per row, past the pair
// harness's 20,000-check-point cap on a real file. Every check point's register file and cycles go into a hash (both
// runs must give the same hash and count); the end state, the whole RAM and the scratchpad are compared as hgp::pair does.
constexpr u64 kMaxChecks = 8'000'000;
class LongHooks final : public RtHooks {
public:
    ScriptedBus bus_;
    u64 checks = 0, hash = 1469598103934665603ull;
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    hgp::Snap at_stop;
    int syscalls = 0;
    void mix(const void* p, std::size_t n) {
        const u8* bb = static_cast<const u8*>(p);
        for (std::size_t i = 0; i < n; ++i) hash = (hash ^ bb[i]) * 1099511628211ull;
    }
    void mix_snap(const hgp::Snap& s) {
        mix(&s.cycles, 8);
        for (const u128& g : s.gpr) mix(&g, 16);
        mix(&s.hi, 16);
        mix(&s.lo, 16);
        mix(&s.fcr31, 4);
        mix(s.fpr.data(), 4 * 32);
        mix(s.vu0.vf, sizeof s.vu0.vf);
    }
    void syscall(EEContext& ctx, u32) override {
        ++syscalls;
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
    void check_events(EEContext& ctx) override {
        ++checks;
        mix_snap(hgp::snap(ctx));
        if (checks >= kMaxChecks) {
            stopped = true;
            stop_pc = 0xFFFFFFFFu;
            what = "runaway";
            at_stop = hgp::snap(ctx);
            throw rt_test::FatalEvent{stop_pc, "runaway", &ctx};
        }
    }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* w) override {
        stopped = true;
        stop_pc = pc;
        what = w;
        if (const std::size_t k = what.find("; host return address"); k != std::string::npos) what.erase(k);
        at_stop = hgp::snap(ctx);
        throw rt_test::FatalEvent{pc, w, &ctx};
    }
    void vu_control_write(EEContext&, u32, u32) override {}
};
struct LongRun {
    bool stopped = false;
    u32 stop_pc = 0;
    std::string what;
    u64 checks = 0, hash = 0;
    hgp::Snap end;
    std::vector<u8> spr;
    std::size_t bus = 0;
};
LongRun run_long(Machine& m, Fn fn, const Args& args, u32 seed) {
    LongHooks h;
    rt_test::HooksScope scope{&h};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    try {
        if (!hgp::call_guarded(fn, m.ctx) && !h.stopped) {
            h.stopped = true;
            h.stop_pc = 0xFFFFFFFEu;
            h.what = "host access violation";
            h.at_stop = hgp::snap(m.ctx);
        }
    } catch (const rt_test::FatalEvent&) {
    }
    LongRun r;
    r.stopped = h.stopped;
    r.stop_pc = h.stop_pc;
    r.what = h.what;
    r.checks = h.checks;
    r.hash = h.hash;
    r.end = h.stopped ? h.at_stop : hgp::snap(m.ctx);
    r.spr.assign(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    r.bus = h.bus_.log.size();
    return r;
}
u32 v0_of_long(const LongRun& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
// One body alone, long (the rule checks on real files), in the given stand-in world.
LongRun solo_long(Machine& m, Fn fn, const char* name, const Args& a, StandInWorld& w) {
    g_si[0] = &w;
    g_fn[0] = fn;
    const LongRun r = run_long(m, &thunk0, a, 1);
    if (r.stopped) MESSAGE(std::string(name) << ": stopped: " << r.what << " at " << hex64(r.stop_pc));
    CHECK_FALSE(r.stopped);
    return r;
}
// The pair, long: fresh identical stand-in worlds, both call logs compared.
LongRun pair_long(Machine& m, Fn hand, Fn recomp, const char* name, const Args& args, u32 seed) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    b20_setup(*wh);
    b20_setup(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    PairRange ram(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    const LongRun h = run_long(m, &thunk0, args, seed);
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    const LongRun r = run_long(m, &thunk1, args, seed);
    INFO(name << " (long) seed " << seed << (r.stopped ? " (recomp stopped: " + r.what + ")" : std::string()));
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.checks == r.checks);
    CHECK(h.hash == r.hash);
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first));
        CHECK(false);
    }
    CHECK(first_difference(h.spr.data(), r.spr.data(), h.spr.size()) == h.spr.size());
    CHECK(h.bus == r.bus);
    expect_same_log(wh->si, wr->si, name);
    return r;
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
constexpr u32 kWorldSize = 0x70000u;
constexpr u32 kBcm = kWorld + 0x0000u;       // bcm_panel.c work (29,208 bytes)
constexpr u32 kBpp = kWorld + 0x7400u;       // bpp_main.c work (23,140)
constexpr u32 kBsa = kWorld + 0xCF00u;       // the analysis panel (42,688)
constexpr u32 kSflGround = kWorld + 0x17600u;// sfl_ground.c work (36,232)
constexpr u32 kBi = kWorld + 0x20400u;       // bi_main.c work (62,720)
constexpr u32 kBaus = kWorld + 0x2F900u;     // baus_main.c work (10,580)
constexpr u32 kPsel = kWorld + 0x32300u;     // sfl_psel.c work (21,204)
constexpr u32 kGcRes = kWorld + 0x37600u;    // gc_res.c work (9,996)
constexpr u32 kSflRes = kWorld + 0x3A000u;   // sfl_res.c work (132)
constexpr u32 kBse = kWorld + 0x3A100u;
constexpr u32 kBpRes = kWorld + 0x3A200u;    // bp_res.c work (108)
constexpr u32 kBrRes = kWorld + 0x3A300u;    // br_res.c work (80)
constexpr u32 kSflPanel = kWorld + 0x3A400u; // sfl_panel.c work (528)
constexpr u32 kBrPanel = kWorld + 0x3A800u;  // br_panel.c work (9,840)
constexpr u32 kSets = kWorld + 0x3D000u;     // 8 sprite sets of 32 bytes
constexpr u32 kRecords = kWorld + 0x3D100u;  // 100 page records of 44 bytes
constexpr u32 kRasters = kWorld + 0x3E300u;  // 64 raster words
constexpr u32 kQuads = kWorld + 0x3E400u;    // 16 quads of 256 bytes
constexpr u32 kFloats = kWorld + 0x3F400u;   // 64 vec4s
constexpr u32 kFx = kWorld + 0x3F800u;       // effect nodes, records, instances, meshes (0x8800)
constexpr u32 kFresh = kWorld + 0x48000u;    // argument blocks (0x8000)
constexpr u32 kFiles = kWorld + 0x50000u;    // images and files (0x20000)

const s32 kSlots[] = {b::kGpBausMain, b::kGpSflRes, b::kGpBppMain, b::kGpSflPsel, b::kGpGcRes, b::kGpBseMain,
                      b::kGpBpRes, b::kGpBcmPanel, b::kGpBrRes, b::kGpBrPanel, b::kGpSflGround, b::kGpSflPanel,
                      b::kGpBiMain};
const u32 kBlocks[] = {kBaus, kSflRes, kBpp, kPsel, kGcRes, kBse, kBpRes, kBcm, kBrRes, kBrPanel, kSflGround, kSflPanel, kBi};

// The sprite sets (header {self, pages, rasters, raster count, page count}) and their 44-byte page records.
void fill_sets(Machine& m, std::mt19937& rng) {
    for (u32 s = 0; s < 8; ++s) {
        const u32 a = kSets + 32 * s;
        st32(m, a + 0, a);
        st32(m, a + 4, kRecords + 44 * (rng() % 8));
        st32(m, a + 8, kRasters + 4 * (rng() % 32));
        st32(m, a + 12, rng() % 4);
        st32(m, a + 16, 70);
    }
    for (u32 r = 0; r < 100; ++r) {
        const u32 a = kRecords + 44 * r;
        st32(m, a + 0, kSets + 32 * (rng() % 8));
        st32(m, a + 4, rng() % 4);
        st32(m, a + 8, rng() % 4);
        st32(m, a + 12, 4 + rng() % 120);
        st32(m, a + 16, 4 + rng() % 60);
        st32(m, a + 20, rng() % 256);
        st32(m, a + 24, rng() % 256);
        for (u32 k = 28; k < 44; ++k) st8(m, a + k, static_cast<u8>(rng()));
    }
}
u32 a_set(std::mt19937& rng) { return kSets + 32 * (rng() % 8); }

// An image as sub_21EC40 reads it: +16 palette rows, +18 / +20 width / height, +22 the format, texels from +64.
const u8 kFormats[] = {0, 1, 2, 10, 19, 27, 20, 36, 44};
u32 make_image(Machine& m, u32 at, std::mt19937& rng) {
    std::memset(ram(m, at), 0, 64);
    st8(m, at + 16, static_cast<u8>(1 + rng() % 2));
    st16(m, at + 18, static_cast<u16>(8u << (rng() % 2)));
    st16(m, at + 20, static_cast<u16>(4u << (rng() % 2)));
    st8(m, at + 22, chance(rng, 95) ? kFormats[rng() % 9] : static_cast<u8>(rng()));
    for (u32 k = 64; k < 64 + 0x800; k += 4) st32(m, at + k, rng());
    return at;
}
// A file of image entries (8 bytes each from +8: an offset at +0), a u16 count at +4.
u32 make_file(Machine& m, u32 at, u32 entries, std::mt19937& rng) {
    std::memset(ram(m, at), 0, 8 + 8 * entries);
    st16(m, at + 4, static_cast<u16>(chance(rng, 90) ? entries : rng() % 12));
    for (u32 e = 0; e < entries; ++e) {
        const u32 img = make_image(m, at + 0x100u + 0x900u * (e % 4), rng);
        st32(m, at + 8 + 8 * e, img - at);
    }
    return at;
}

// An effect node tree: a root and 1..3 children, each with an effect record of a small class.
u32 make_tree(Machine& m, u32 at, std::mt19937& rng) {
    const u32 n = 1 + rng() % 3;
    for (u32 k = 0; k <= n; ++k) {
        const u32 node = at + 0x100u * k;
        for (u32 o = 0; o < 96; o += 4) stf(m, node + o, small_f(rng));
        stf(m, node + 96, small_f(rng));
        st32(m, node + 100, rng());
        st32(m, node + 104, chance(rng, 50) ? (rng() & 0x1FC) : 0u);
        stf(m, node + 116, small_f(rng));
        st32(m, node + 128, rng() % 4);
        st32(m, node + 132, rng() % 6);
        st32(m, node + 140, k == 0 ? at + 0x100u : 0u);
        const u32 rec = at + 0x600u + 0x40u * k;
        st32(m, node + 144, rec);
        st32(m, node + 152, rng() % 2);
        st32(m, node + 172, (k > 0 && k < n) ? node + 0x100u : 0u);
        st16(m, rec + 4, static_cast<u16>(rng() % 27));
        st32(m, rec + 8, chance(rng, 30) ? 0u : kFresh + 0x7000u + 0x100u * (rng() % 8));
        st32(m, rec + 24, 0);
        st32(m, rec + 40, 0);
    }
    return at;
}

void module_world(Machine& m, std::mt19937& rng) {
    std::memcpy(m.at(kGpData), g_gp_data.data(), kGpDataSize);
    std::memcpy(m.at(kRwPage), g_rw_page.data(), kRwPageSize);
    write_rw_slots(m);
    set_device_slots(m);
    hgp::random_world(m, kWorld, kWorldSize, rng);
    fill_sets(m, rng);
    for (std::size_t i = 0; i < std::size(kSlots); ++i) st32(m, gp_slot(kSlots[i]), chance(rng, 6) ? 0u : kBlocks[i]);
    st32(m, 0x7CDFA4u, rng() % 2);  // the scenario mode of sub_17D800 (The Answer)
    for (u32 blk : kBlocks) {
        st32(m, blk + 0, rng() & 0x1FF);
        st32(m, blk + 4, rng() & 0x1FF);
    }
    // baus_main.c: 0..4 entries
    st32(m, kBaus + b::kBausCount, rng() % 5);
    for (u32 e = 0; e < 4; ++e) {
        const u32 a = kBaus + b::kBausEntries + b::kBausEntrySize * e;
        st32(m, a + 0, rng() % 2);
        st32(m, a + 4, rng() % 8);
        st32(m, a + 8, rng() % 100);
        st32(m, a + 12, 1 + rng() % 100);
        st32(m, a + 528, chance(rng, 20) ? 0xFFFFFFFFu : rng() % 3);
        st32(m, a + 532, chance(rng, 20) ? 0xFFFFFFFFu : rng() % 3);
        st32(m, a + 536, rng() % 3);
    }
    // sfl_res.c: requested / loaded bits, nodes, the sprite set
    st32(m, kSflRes + b::kSrLoaded, rng() & 0x1F);
    st32(m, kSflRes + b::kSrRequested, rng() & 0x1F);
    st32(m, kSflRes + b::kSrSprSet, a_set(rng));
    // bpp_main.c: 0..4 members with small ids, the target, the slide
    st32(m, kBpp + b::kBppCount, rng() % 5);
    st32(m, kBpp + b::kBppSlide, rng() % 12);
    st32(m, kBpp + b::kBppSlideMax, rng() % 12);
    for (u32 r = 0; r < 4; ++r) {
        const u32 mem = kBpp + b::kBppMembers + b::kBppMemberSize * r;
        st32(m, mem + b::kBmFlags, rng() & 7);
        st16(m, mem + b::kBmId, static_cast<u16>(rng() % 8));
        const u32 pn = mem + b::kBmPanel;
        st32(m, pn + b::kBpnFlags, rng() & 0x3FF);
        st16(m, pn + b::kBpnId, static_cast<u16>(rng() % 8));
        st32(m, pn + b::kBpnIcon, rng() % 12);
        for (u32 o : {b::kBpnOpenFrame, b::kBpnFlashFrame, b::kBpnFadeFrame}) st32(m, pn + static_cast<u32>(o), rng() % 24);
        stf(m, pn + b::kBpnX, small_f(rng));
        stf(m, pn + b::kBpnY, small_f(rng));
        stf(m, pn + b::kBpnScale, small_f(rng));
        st32(m, pn + b::kBpnHp, rng() % 1000);
        st32(m, pn + b::kBpnSp, rng() % 1000);
    }
    // sfl_psel.c: entries
    st32(m, kPsel + b::kPsCount, rng() % 4);
    // gc_res.c: loaded mask, slots, pair and id records
    st32(m, kGcRes + b::kGrLoaded, rng() & 15);
    for (u32 s = 0; s < 32; ++s) {
        const u32 a = kGcRes + b::kGrSlots + b::kGcSlotSize * s;
        st32(m, a + 0, chance(rng, 15) ? 1u : 0u);
        st32(m, a + 4, rng() % 3);
        st32(m, a + 272, rng() % 3);
        st32(m, a + 276, rng() % 16);
    }
    // bp_res.c: the sets
    for (u32 i = 0; i < 7; ++i) st32(m, kBpRes + b::kBrSets + 4 * i, a_set(rng));
    for (u32 i = 0; i < 3; ++i) st32(m, kBpRes + b::kBrIdSets + 4 * i, a_set(rng));
    st32(m, kBpRes + b::kBrIdCount, rng() % 4);
    // bcm_panel.c: the states and timers, the rows
    st32(m, kBcm + b::kBcmList, 1u << (rng() % 4));
    st32(m, kBcm + b::kBcmState, rng() % 9);
    st32(m, kBcm + b::kBcmCur, rng() % 7);
    st32(m, kBcm + b::kBcmPrev, chance(rng, 20) ? 0xFFFFFFFFu : rng() % 7);
    st32(m, kBcm + b::kBcmSub, rng() % 5);
    st32(m, kBcm + b::kBcmSubPrev, rng() % 5);
    st32(m, kBcm + b::kBcmSubStep, rng() % 5);
    st32(m, kBcm + b::kBcmSubSel, rng() % 3);
    for (u32 o : {b::kBcmTimer, b::kBcmSubTimer, b::kBcmMenuTimer}) st32(m, kBcm + static_cast<u32>(o), rng() % 8);
    st32(m, kBcm + b::kBcmRowTotal, rng() % 10);
    st32(m, kBcm + b::kBcmRowTop, rng() % 5);
    st32(m, kBcm + b::kBcmRowShown, rng() % 6);
    st32(m, kBcm + b::kBcmCursorPage, rng() % 8);
    st32(m, kBcm + b::kBcmCursorOn, rng() % 2);
    st32(m, kBcm + 29200, rng() % 4);
    stf(m, kBcm + b::kBcmFade, static_cast<float>(rng() % 11) / 10.0f);
    st32(m, kBcm + 24688, rng() % 6);  // the rows in use
    // br_panel.c: the fade
    st32(m, kBrPanel + 9832, rng() % 14);
    st32(m, kBrPanel + 9836, rng() % 3);
    // sfl_ground.c / sfl_panel.c
    st32(m, kSflGround + b::kSgMode, rng() % 3);
    st32(m, kSflGround + b::kSgFrame, rng() % 60);
    st32(m, kSflPanel + b::kSpnMode, rng() % 3);
    st32(m, kSflPanel + b::kSpnFrame, rng() % 60);
    st32(m, kSflPanel + b::kSpnCount, rng() % 7);
    // the analysis panel's fade
    st32(m, kBsa + 4, rng() & 0x7F);
    st32(m, kBsa + 42672, rng() % 14);
    st32(m, kBsa + 42676, rng() % 3);
    st32(m, kBsa + 52, rng() % 4);
    // effect structures: trees, records, instances, meshes, psys, tracks
    make_tree(m, kFx + 0x0000u, rng);
    make_tree(m, kFx + 0x0800u, rng);
    for (u32 k = 0; k < 4; ++k) {  // records
        const u32 rec = kFx + 0x1000u + 0x40u * k;
        st16(m, rec + 4, static_cast<u16>(rng() % 27));
        st32(m, rec + 8, chance(rng, 40) ? 0u : kFresh + 0x7000u + 0x100u * (rng() % 8));
        st32(m, rec + 24, 0);
        st32(m, rec + 40, 0);
    }
    for (u32 k = 0; k < 2; ++k) {  // meshes: no RW objects, 0..3 materials
        const u32 mesh = kFx + 0x1200u + 0x80u * k;
        st32(m, mesh + 12, 0);
        st32(m, mesh + 16, 0);
        st16(m, mesh + 28, static_cast<u16>(rng() % 4));
        st32(m, mesh + 40, kFx + 0x1400u);
        for (u32 i = 0; i < 4; ++i) st32(m, kFx + 0x1400u + 4 * i, kFresh + 0x7800u + 0x40u * i);
    }
    for (u32 k = 0; k < 2; ++k) {  // class instances: no parts or a few records
        const u32 in = kFx + 0x1500u + 0x100u * k;
        st32(m, in + 0, rng() % 3);
        st8(m, in + 14, 0);
        for (u32 o = 52; o <= 80; o += 4) st32(m, in + o, 0);
        if (chance(rng, 50)) {
            st32(m, in + 52, kFx + 0x1700u);
            st32(m, in + 56, kFx + 0x1700u);
            for (u32 i = 0; i < 3; ++i) st32(m, kFx + 0x1700u + 4 * i, kFx + 0x1000u + 0x40u * i);
        }
    }
    {  // a particle-drawing instance: kind 7 or not, a particle system with 0..4 particles
        const u32 in = kFx + 0x1800u, ps = kFx + 0x1900u, parts = kFx + 0x1A00u;
        st32(m, in + 4, rng());
        st16(m, in + 12, static_cast<u16>(chance(rng, 70) ? 7 : rng() % 10));
        st32(m, in + 76, ps);
        st32(m, ps + 8, rng() % 5);
        st32(m, ps + 12, rng() % 2);
        st32(m, ps + 24, parts);
        for (u32 p = 0; p < 4; ++p) {
            for (u32 o = 0; o < 32; o += 4) stf(m, parts + 32 * p + o, small_f(rng));
            st32(m, parts + 32 * p + 16, chance(rng, 70) ? rng() % 30 : 0xFFFFFFFFu);
            st32(m, parts + 32 * p + 20, rng());
        }
    }
    for (u32 k = 0; k < 2; ++k) {  // colour tracks
        const u32 t = kFx + 0x1C00u + 0x40u * k;
        st8(m, t, static_cast<u8>(rng() % 3));
        for (u32 o = 4; o < 28; o += 4) st32(m, t + o, rng());
        stf(m, t + 16, static_cast<float>(rng() % 101) / 100.0f);
        stf(m, t + 24, static_cast<float>(rng() % 101) / 100.0f);
    }
    {  // particle systems for the scale slots: live / base parameter blocks
        const u32 ps = kFx + 0x1D00u;
        st32(m, ps + 32, kFx + 0x1E00u);
        st32(m, ps + 36, kFx + 0x1F00u);
        for (u32 o = 0; o < 0x100; o += 4) stf(m, kFx + 0x1F00u + o, small_f(rng));
    }
    for (u32 o = 0; o < 0x400; o += 4) stf(m, kFloats + o, small_f(rng));  // vectors / matrices
    // images and files
    make_image(m, kFiles, rng);
    make_file(m, kFiles + 0x4000u, 3, rng);
    make_file(m, kFiles + 0x8000u, 10, rng);
}

// An argument of a kind.
u64 arg_of(char k, std::mt19937& rng) {
    if (rng() % 100 < 3) return hgp::random_arg(rng, kWorld, kWorldSize);  // anything, now and then
    switch (k) {
    case 'w': return sx(kFresh + 0x10u * (rng() % 16));
    case 'q': return sx(kQuads + 0x100u * (rng() % 4));
    case 'Q': return sx(kQuads + 0x100u * (rng() % 8));
    case 'p': return sx(kRecords + 44 * (rng() % 64));
    case 'n': return chance(rng, 10) ? rng() : rng() % 1200;
    case 'x': case 'v': return sx(kFloats + 0x10u * (rng() % 32));
    case 'i': return chance(rng, 10) ? rng() % 40 : rng() % 8;
    case 'c': return 1 + rng() % 7;
    case 'u': return rng() % 10;
    case 'b': return chance(rng, 70) ? (1u << (rng() % 21)) : rng();
    case 'y': return rng() % 3;
    case 'f': return rng() % 4;
    case 'h': return sx(kFloats + 0x200u + 4 * (rng() % 8));
    case 'e': return sx(kBsa);
    case 'P': return sx(chance(rng, 80) ? kBpp + b::kBppMembers + b::kBppMemberSize * (rng() % 4) + b::kBmPanel : kFresh + 0x100u * (rng() % 16));
    case 'm': return sx(kFresh + 0x40u * (rng() % 32));
    case 'r': return sx(kRecords + 4 * (rng() % 64));
    case 'S': return sx(kFiles + 0x10000u);
    case 's': return sx(a_set(rng));
    case 'G': return sx(kFiles);
    case 'F': return sx(kFiles + 0x4000u);
    case 'K': return sx(kFiles + 0x8000u);
    case 'M': return sx(kFx + 0x1200u + 0x80u * (rng() % 2));
    case 'R': return sx(kFx + 0x1000u + 0x40u * (rng() % 4));
    case 'N': return sx(kFx + 0x800u * (rng() % 2));
    case 'I': return sx(kFx + 0x1500u + 0x100u * (rng() % 2));
    case 'J': return sx(kFx + 0x1800u);
    case 'T': return sx(kFx + 0x1C00u + 0x40u * (rng() % 2));
    case 'Y': return sx(kFx + 0x1D00u);
    case 'k': return rng() % 9;
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

std::vector<u8> read_host_file(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

}  // namespace

TEST_CASE("game(band20): every body equals its recompiled body on random worlds") {
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
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (unsigned i = 0; i < 4; ++i) {
                const u64 v = hgp::random_arg(rng, kWorld, kWorldSize);
                args[i] = v;
            }
            stops += pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs over " << cases().size() << " functions, " << stops << " ended at a compared stop");
}

TEST_CASE("game(band20): every body equals its recompiled body on module worlds") {
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

TEST_CASE("game(band20): every body on the replay snapshots' real module works") {
    int used = 0, pairs = 0, stops = 0;
    for (const char* dir : {"b_5800", "fx2_battle_5450", "battle_ref_6150", "b20_climb_10850", "b20_climb_11200"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        ++used;
        auto m = new_machine();
        if (!m) return;
        int live = 0;
        {
            std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
            for (s32 off : kSlots) live += ld32(*m, gp_slot(off)) ? 1 : 0;
        }
        MESSAGE(std::string(dir) << ": " << live << " of the band's 13 module slots set");
        std::mt19937 rng{0xB020u};
        for (const Case& c : cases()) {
            for (int rep = 0; rep < 3; ++rep) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                write_rw_slots(*m);
                set_device_slots(*m);
                // pointer kinds: blocks of a module world built in the stand-in heap's tail (zero in every snapshot)
                std::mt19937 wr{static_cast<u32>(rep) * 31u + c.addr};
                Args a{};
                HwCheck hw;
                const std::size_t n = std::strlen(c.kinds);
                for (unsigned i = 0; i < 4; ++i) {
                    const char k = i < n ? c.kinds[i] : 'i';
                    const bool ptr = std::strchr("wqQpxvhePmrSsGFKMRNIJTY", k) != nullptr;
                    const u64 v = ptr ? sx(kStandInHeap + 0x200000u + 0x1000u * (rng() % 16)) : arg_of(k, wr);
                    a[i] = v;
                }
                if (n > 4) hw.gpr_in[GPR_T0] = sx(kStandInHeap + 0x2F0000u);
                const hgp::Run r = pair(*m, c.hand, c.recomp, a, static_cast<u32>(rep) + 1, c.name, hw);
                ++pairs;
                stops += r.stopped ? 1 : 0;
            }
        }
    }
    MESSAGE("snapshots: " << used << " used, " << pairs << " pairs, " << stops << " ended at a compared stop");
}

// --- documented rules -------------------------------------------------------------------------------------------------

TEST_CASE("game(band20): the digit layouts of bp_ifont.c, bpp_panel.c and baus_main.c") {
    // bpp_panel.c sub_22EB30: right-aligned three digits, 16 px apart, unused quads zero-sized at the origin
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{3};
    module_world(*m, rng);
    st32(*m, gp_slot(b::kGpBpRes), kBpRes);
    int checks = 0;
    for (u32 value : {0u, 7u, 42u, 305u, 999u}) {
        const u32 q = kQuads, xy = kFloats;
        stf(*m, xy, 100.0f);
        stf(*m, xy + 4, 50.0f);
        run_ok(*m, "sub_22EB30", {sx(q), value, sx(xy), 0});
        const u32 digits = value >= 100 ? 3 : value >= 10 ? 2 : 1;
        const u32 set3 = ld32(*m, kBpRes + b::kBrSets + 12);
        for (u32 i = 0; i < 3; ++i) {
            // the quad's rectangle: vertex 0 x / y (sub_21D8E0 writes x, y, w, h into the four vertices)
            const float x = ldf(*m, q + 256 * i + 0), y = ldf(*m, q + 256 * i + 4);
            INFO("value " << value << " quad " << i);
            if (i < digits) {
                CHECK(x == 100.0f + 16.0f * static_cast<float>(2 - i));
                CHECK(y == 50.0f);
                // the width is the digit's page width (panel set 3, page = the digit, last digit first)
                const u32 d = (value / (i == 0 ? 1 : i == 1 ? 10 : 100)) % 10;
                const u32 page = ld32(*m, set3 + 4) + 44 * d;
                CHECK(ldf(*m, q + 256 * i + 64) - x == static_cast<float>(static_cast<s32>(ld32(*m, page + 12))));
            } else {
                CHECK(x == 100.0f);
                CHECK(ldf(*m, q + 256 * i + 64) == 100.0f);  // zero width
            }
            checks += 3;
        }
    }
    // bp_ifont.c on b_5800's real sprite fonts: left / right / centred x of each digit
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: b_5800 not found (bp_ifont checks)");
        return;
    }
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(*m);
    set_device_slots(*m);
    const u32 q = kStandInHeap + 0x200000u, xy = kStandInHeap + 0x201000u;
    for (u32 value : {5u, 61u, 480u, 1234u}) {
        for (const char* fn : {"sub_238A50", "sub_238BF0", "sub_238DC0"}) {
            const u32 n = 5;
            stf(*m, xy, 200.0f);
            stf(*m, xy + 4, 80.0f);
            HwCheck hw;
            hw.gpr_in[GPR_T0] = sx(xy);
            run_ok(*m, fn, {sx(q), n, value, 0}, hw);
            const u32 digits = value >= 1000 ? 4 : value >= 100 ? 3 : value >= 10 ? 2 : 1;
            for (u32 i = 0; i < digits; ++i) {
                const u32 pos = digits - 1 - i;  // the quad of digit i (from the right) sits at string position pos
                float want = 200.0f + 15.0f * static_cast<float>(pos);
                if (fn[7] == 'B') want += 15.0f * static_cast<float>(n - digits);
                if (fn[7] == 'D') want = (static_cast<float>((15 * n) / 2) + want) - static_cast<float>((15 * digits) / 2);
                INFO(fn << " value " << value << " digit " << i);
                CHECK(ldf(*m, q + 256 * i) == want);
                CHECK(ldf(*m, q + 256 * i + 4) == 80.0f);
                ++checks;
            }
        }
    }
    MESSAGE("digit layouts: " << checks << " checks");
}

TEST_CASE("game(band20): gc_model.c's card x and grid index list, sfl_data.c's side map, the ailment icon map") {
    auto m = new_machine();
    if (!m) return;
    // sub_20C660(i, n): the card's screen x
    for (u32 n = 1; n <= 7; ++n)
        for (u32 i = 0; i < n; ++i) {
            const hgp::Run r = run_ok(*m, "sub_20C660", {i, n, 0, 0});
            float want = 0.0f;
            if (n >= 3 && n <= 5) want = static_cast<float>(i + 1) * (640.0f / static_cast<float>(n + 1));
            else if (n == 6) want = 500.0f * static_cast<float>(i) / 5.0f + 70.0f;
            else if (n == 2) want = 200.0f * static_cast<float>(i) / 1.0f + 220.0f;
            INFO("i " << i << " n " << n);
            CHECK(std::fabs(f0_of(r) - want) <= std::fabs(want) * 1e-6f);  // within an ulp: the R5900 FPU truncates
        }
    // sub_20C8D0: 8 rows x 6 quads (two triangles each) and the row ends, alternating diagonals, 0x875A90
    std::memset(ram(*m, 0x875A90u), 0xEE, 0x400);
    run_ok(*m, "sub_20C8D0", {0, 0, 0, 0});
    std::vector<u16> want;
    u16 v = 0;
    for (int row = 0; row < 8; ++row) {
        for (int q = 0; q < 6; ++q) {
            if (row & 1) {
                want.insert(want.end(), {v, static_cast<u16>(v + 8), static_cast<u16>(v + 7), v, static_cast<u16>(v + 1), static_cast<u16>(v + 8)});
            } else {
                want.insert(want.end(), {v, static_cast<u16>(v + 1), static_cast<u16>(v + 8), static_cast<u16>(v + 1), static_cast<u16>(v + 9), static_cast<u16>(v + 8)});
            }
            ++v;
        }
        if (row & 1) {
            want.insert(want.end(), {v, static_cast<u16>(v + 8), static_cast<u16>(v + 7)});
            ++v;
        } else {
            want.insert(want.end(), {v, static_cast<u16>(v + 1), static_cast<u16>(v + 8)});
            v = static_cast<u16>(v + 2);
        }
    }
    int bad = 0;
    for (std::size_t k = 0; k < want.size(); ++k) bad += ld16(*m, 0x875A90u + 2 * static_cast<u32>(k)) != want[k];
    INFO("grid indices: " << want.size());
    CHECK(want.size() == 312u);  // the body's own K_Assert (line 1303): 312 indices
    CHECK(*std::max_element(want.begin(), want.end()) < 68);  // and every one a vertex of the 68 (line 1301)
    CHECK(bad == 0);
    CHECK(ld16(*m, 0x875A90u + 2 * 312) == 0xEEEEu);  // nothing past the list
    // sub_209D40: -1 -> 2, 0 -> 0, 1 -> 1, else -1
    const u32 w = kFresh;
    for (s16 side : {static_cast<s16>(-1), static_cast<s16>(0), static_cast<s16>(1), static_cast<s16>(2), static_cast<s16>(-7)}) {
        st16(*m, w, static_cast<u16>(side));
        const u32 got = v0_of(run_ok(*m, "sub_209D40", {sx(w), 0, 0, 0}));
        const u32 exp = side == -1 ? 2u : side == 0 ? 0u : side == 1 ? 1u : 0xFFFFFFFFu;
        INFO("side " << side);
        CHECK(got == exp);
    }
    // sub_22F1C0: one ailment bit -> the icon; anything else clears the icon flag
    std::mt19937 rng{9};
    module_world(*m, rng);
    const u32 pn = kFresh + 0x1000u;
    struct Map { u32 bits; s32 icon; };
    const Map maps[] = {{0x80000u, 8}, {0x200u, 10}, {0x80u, 7}, {0x40u, 6}, {0x20u, 5}, {0x10u, 4}, {8u, 3}, {4u, 2}, {2u, 1}, {1u, 0},
                        {3u, -1}, {0x100u, -1}, {0u, -1}, {0x400u, -1}};
    for (const Map& mp : maps) {
        st32(*m, pn + b::kBpnFlags, 5);
        st32(*m, pn + b::kBpnIcon, 77);
        const Solo s = solo(*m, case_of("sub_22F1C0").hand, {sx(pn), mp.bits, 0, 0});
        INFO("bits " << hex64(mp.bits));
        if (mp.icon >= 0) {
            CHECK((ld32(*m, pn + b::kBpnFlags) & 4u) == 4u);
            CHECK(static_cast<s32>(ld32(*m, pn + b::kBpnIcon)) == mp.icon);
        } else {
            CHECK((ld32(*m, pn + b::kBpnFlags) & 4u) == 0u);
            CHECK(ld32(*m, pn + b::kBpnIcon) == 77u);
        }
    }
}

TEST_CASE("game(band20): the colour track's alpha envelope") {
    auto m = new_machine();
    if (!m) return;
    std::mt19937 rng{21};
    int checks = 0;
    // sub_32A120(track, alpha*, t, length): RGB interpolated between the keys, alpha from *alpha
    for (int n = 0; n < 300; ++n) {
        const u32 t = kFx, al = kFx + 0x80u;
        const u32 kind = rng() % 3;
        const u32 c1 = rng() & 0xFFFFFFu, c2 = rng() & 0xFFFFFFu, c3 = rng() & 0xFFFFFFu;
        const float m1 = static_cast<float>(1 + rng() % 99) / 100.0f;
        const float m2 = m1 + (1.0f - m1) * static_cast<float>(rng() % 100) / 100.0f;
        st8(*m, t, static_cast<u8>(kind));
        st32(*m, t + 4, c1);
        st32(*m, t + 8, kind == 1 ? c3 : kind == 2 ? c3 : c1);
        st32(*m, t + 12, c2);
        stf(*m, t + 16, m1);
        st32(*m, t + 20, c2);
        stf(*m, t + 24, m2);
        // the alpha envelope: {alpha, -, fade-in end, fade-out start} (fractions of the length)
        const u32 alpha = rng() % 256;
        const float fin = static_cast<float>(rng() % 50) / 100.0f;
        const float fout = 0.5f + static_cast<float>(rng() % 50) / 100.0f;
        st32(*m, al, alpha);
        stf(*m, al + 8, fin);
        stf(*m, al + 12, fout);
        const u32 len = rng() % 60;
        const u32 tt = len ? rng() % (len + 1) : 0;
        const u32 got = v0_of(run_ok(*m, "sub_32A120", {sx(t), sx(al), tt, len}));
        INFO("kind " << kind << " t " << tt << " len " << len << " in " << fin << " out " << fout);
        if (len == 0) {
            CHECK(got == ((c1 & 0xFFFFFFu) | (alpha << 24)));  // the first key, the envelope's alpha
        } else {
            const s32 in_end = static_cast<s32>(fin * static_cast<float>(len));
            const s32 out_start = static_cast<s32>(fout * static_cast<float>(len));
            const s32 ti = static_cast<s32>(tt), li = static_cast<s32>(len);
            float k = 1.0f;
            if (ti < in_end) k = static_cast<float>(ti) / static_cast<float>(in_end);
            else if (out_start < ti) k = static_cast<float>(li - ti) / static_cast<float>(li - out_start);
            const s32 want = static_cast<s32>(static_cast<float>(alpha) * k);
            const s32 a = static_cast<s32>(got >> 24);
            if (k == 1.0f) CHECK(a == static_cast<s32>(alpha));
            else CHECK(std::abs(a - want) <= 1);  // the R5900 FPU truncates its products: one step either way
        }
        ++checks;
    }
    MESSAGE("maths: " << checks << " checks");
}

TEST_CASE("game(band20): bp_tex.c builds the sprite set of i_change_per01.spr") {
    const std::vector<u8> spr = read_host_file(extracted_root() + "/BTL/BATTLE/SHUFFLE/I_CHANGE_PER01.SPR");
    if (spr.empty()) {
        MESSAGE("SKIP: extracted/BTL/BATTLE/SHUFFLE/I_CHANGE_PER01.SPR not found");
        return;
    }
    // On b_5800: the RenderWare engine the raster functions (sub_21EC40 -> RwRasterCreate ..) need is up there; the
    // file goes into the stand-in arena's tail (zero in every snapshot), the set into the stand-in heap.
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: b_5800 not found");
        return;
    }
    auto m = new_machine();
    if (!m) return;
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(*m);
    set_device_slots(*m);
    const u32 file = kStandInHeap + 0x200000u;
    std::memcpy(ram(*m, file), spr.data(), spr.size());
    auto rd16 = [&](u32 o) { return static_cast<u32>(spr[o] | (spr[o + 1] << 8)); };
    auto rd32 = [&](u32 o) { return static_cast<u32>(spr[o] | (spr[o + 1] << 8) | (spr[o + 2] << 16) | (static_cast<u32>(spr[o + 3]) << 24)); };
    const u32 rasters = rd16(20), pages = rd16(22), ptab = rd32(28);
    // the pair on the real file first (long: one check point per texel row), then the hand body alone for the rules
    pair_long(*m, case_of("sub_21C9F0").hand, case_of("sub_21C9F0").recomp, "sub_21C9F0 i_change_per01.spr", {sx(file), 0, 0, 0}, 1);
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(*m);
    set_device_slots(*m);
    std::memcpy(ram(*m, file), spr.data(), spr.size());
    StandInWorld w;
    b20_setup(w);
    const LongRun r = solo_long(*m, case_of("sub_21C9F0").hand, "sub_21C9F0", {sx(file), 0, 0, 0}, w);
    const u32 set = static_cast<u32>(r.end.gpr[GPR_V0].u64[0]);
    MESSAGE("i_change_per01.spr: " << pages << " pages, " << rasters << " rasters, " << r.checks << " check points");
    CHECK(w.heap.size_of(set) >= 20 + 44 * pages + 4 * rasters);
    CHECK(ld32(*m, set + b::kSsPages) == set + 20);
    CHECK(ld32(*m, set + b::kSsRasters) == set + 20 + 44 * pages);
    CHECK(ld32(*m, set + b::kSsRasterCount) == rasters);
    CHECK(ld32(*m, set + b::kSsPageCount) == pages);
    int bad = 0;
    for (u32 p = 0; p < pages; ++p) {
        const u32 src = rd32(ptab + 8 * p + 4);  // the page's record in the file
        const u32 rec = set + 20 + 44 * p;
        bad += ld32(*m, rec + b::kSpSet) != set;
        bad += ld32(*m, rec + b::kSpFlags) != rd32(src + 20);
        bad += ld32(*m, rec + b::kSpRaster) != rd32(src + 24);
        bad += ld32(*m, rec + b::kSpW) != rd32(src + 92) - rd32(src + 84);
        bad += ld32(*m, rec + b::kSpH) != rd32(src + 96) - rd32(src + 88);
        bad += ld32(*m, rec + b::kSpLeft) != rd32(src + 84);
        bad += ld32(*m, rec + b::kSpTop) != rd32(src + 88);
        for (u32 k = 0; k < 4; ++k) {
            const u32 c = rd32(src + 100 + 4 * k);
            const u8 want[4] = {static_cast<u8>((255u * (c >> 24)) >> 7), static_cast<u8>((255u * ((c >> 16) & 0xFF)) >> 7),
                                static_cast<u8>((255u * ((c >> 8) & 0xFF)) >> 7), static_cast<u8>((255u * (c & 0xFF)) >> 7)};
            for (u32 j = 0; j < 4; ++j) bad += *ram(*m, rec + 28 + 4 * k + j) != want[j];
        }
    }
    for (u32 i = 0; i < rasters; ++i) bad += ld32(*m, set + 20 + 44 * pages + 4 * i) == 0;  // a raster for each image
    CHECK(bad == 0);
    // the destroy frees the set's block (the RwFree stand-in) after its rasters
    const std::size_t live = w.heap.live().size();
    solo_long(*m, case_of("sub_21CC20").hand, "sub_21CC20", {sx(set), 0, 0, 0}, w);
    CHECK(w.heap.size_of(set) == 0u);
    CHECK(w.heap.live().size() < live);
}

TEST_CASE("game(band20): the panel archive and the Shuffle Time effect archive through request and update") {
    if (read_host_file(extracted_root() + "/BTL/SND_BENC/PANEL/BP_ALL.BIN").empty()) {
        MESSAGE("SKIP: extracted/BTL/SND_BENC/PANEL/BP_ALL.BIN not found");
        return;
    }
    // On b_5800 (the RenderWare engine is up for the rasters), with this test's works in the stand-in arena's tail.
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: b_5800 not found");
        return;
    }
    auto m = new_machine();
    if (!m) return;
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(*m);
    set_device_slots(*m);
    st32(*m, 0x7CDFA4u, 0);      // not The Answer: bp_all.bin
    st32(*m, 0x7E0380u + 4, 0);  // an empty H_Cdvd request list: the file stand-in serves only this test's requests
    const u32 wBpRes = kStandInHeap + 0x2E0000u, wSflRes = kStandInHeap + 0x2E1000u;
    auto pump = [&](StandInWorld& w) {  // the frame's file service: the retail cdvd task's H_Cdvd_Update
        solo_long(*m, &rg::fn_H_Cdvd_Update_00100980, "H_Cdvd_Update", {0, 0, 0, 0}, w);
    };
    // bp_res.c: register, request, update (the file stand-in loads in one H_Cdvd_Update), the block accessors
    {
        StandInWorld w;
        b20_setup(w);
        st32(*m, gp_slot(b::kGpBpRes), 0);
        std::memset(ram(*m, wBpRes), 0xA5, 0x100);
        solo_long(*m, case_of("sub_21B920").hand, "sub_21B920", {sx(wBpRes), 0, 0, 0}, w);
        CHECK(ld32(*m, gp_slot(b::kGpBpRes)) == wBpRes);
        CHECK(ld32(*m, wBpRes + b::kBrFlags) == 0u);
        CHECK(ld32(*m, wBpRes + b::kBrLoaded) == 0u);
        solo_long(*m, case_of("sub_21B940").hand, "sub_21B940", {0, 0, 0, 0}, w);
        CHECK((ld32(*m, wBpRes + b::kBrFlags) & 1u) == 1u);
        const u32 node = ld32(*m, wBpRes + b::kBrNode);
        CHECK(node != 0);
        // the update before the file is in leaves everything; then the file service runs once
        solo_long(*m, case_of("sub_21BCB0").hand, "sub_21BCB0", {0, 0, 0, 0}, w);
        CHECK((ld32(*m, wBpRes + b::kBrLoaded) & 1u) == 0u);
        pump(w);
        CHECK(w.cd.missing.empty());
        const LongRun up = solo_long(*m, case_of("sub_21BCB0").hand, "sub_21BCB0", {0, 0, 0, 0}, w);
        MESSAGE("bp_all.bin: the update took " << up.checks << " check points");
        CHECK((ld32(*m, wBpRes + b::kBrLoaded) & 1u) == 1u);
        int sets = 0;
        for (u32 i = 0; i < 7; ++i) sets += ld32(*m, wBpRes + b::kBrSets + 4 * i) ? 1 : 0;
        CHECK(sets == 7);
        for (u32 off : {84u, 88u, 92u, 96u, 100u}) CHECK(w.heap.size_of(ld32(*m, wBpRes + off)) > 0u);
        // the block accessors
        CHECK(static_cast<u32>(solo_long(*m, case_of("sub_21C5D0").hand, "sub_21C5D0", {0, 0, 0, 0}, w).end.gpr[GPR_V0].u64[0]) == ld32(*m, wBpRes + 88));
        CHECK(static_cast<u32>(solo_long(*m, case_of("sub_21C640").hand, "sub_21C640", {0, 0, 0, 0}, w).end.gpr[GPR_V0].u64[0]) == ld32(*m, wBpRes + 84));
        CHECK(static_cast<u32>(solo_long(*m, case_of("sub_21C6B0").hand, "sub_21C6B0", {0, 0, 0, 0}, w).end.gpr[GPR_V0].u64[0]) == ld32(*m, wBpRes + 92));
        // (the release, sub_21BB60, is hand-written since finalB (tests/game/test_finalB.cpp pairs it on this world);
        // test_field6_result records it where it counts the RwFree calls of the panel teardown)
    }
    // sfl_res.c: request (AGS_)sfl_effect.bin, update, check the rasters' places, the release
    if (!read_host_file(extracted_root() + "/BTL/BATTLE/SHUFFLE/SFL_EFFECT.BIN").empty()) {
        StandInWorld w;
        b20_setup(w);
        std::memset(ram(*m, wSflRes), 0, 0x100);
        st32(*m, gp_slot(b::kGpSflRes), wSflRes);
        solo_long(*m, case_of("sub_20E3D0").hand, "sub_20E3D0", {0, 0, 0, 0}, w);
        CHECK(ld32(*m, wSflRes + b::kSrRequested) == 4u);
        CHECK(ld32(*m, wSflRes + b::kSrEffectNode) != 0u);
        CHECK(v0_of_long(solo_long(*m, case_of("sub_20E380").hand, "sub_20E380", {0, 0, 0, 0}, w)) == 0u);
        pump(w);
        CHECK(w.cd.missing.empty());
        // The update then builds the six rasters through RwRasterCreate -> SkyRasterCreate (0x4DB350), which this
        // library does not emit: its recorder is enough for bp_all.bin's images above, not for this archive's (the
        // caller goes on with a register the device step leaves set); the pair below compares both bodies on it.
        CHECK(ld32(*m, wSflRes + b::kSrLoaded) == 0u);
    }
    // and the update as a pair on the loaded archive (long): request + service again, then both bodies
    {
        StandInWorld w;
        b20_setup(w);
        std::memset(ram(*m, wSflRes), 0, 0x100);
        st32(*m, gp_slot(b::kGpSflRes), wSflRes);
        solo_long(*m, case_of("sub_20E3D0").hand, "sub_20E3D0", {0, 0, 0, 0}, w);
        pump(w);
        // the pair's own stand-in worlds keep this world's heap blocks (the loaded archive) reserved
        g_reserve.assign(w.heap.live().begin(), w.heap.live().end());
        pair_long(*m, case_of("sub_20D820").hand, case_of("sub_20D820").recomp, "sub_20D820 sfl_effect.bin", {0, 0, 0, 0}, 2);
        g_reserve.clear();
    }
}

TEST_CASE("game(band20): the party panel builds its member records and slides by the documented rules") {
    auto m = new_machine();
    if (!m) return;
    const std::vector<u8> snap = read_snapshot("b_5800");
    if (snap.empty()) {
        MESSAGE("SKIP: b_5800 not found");
        return;
    }
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    write_rw_slots(*m);
    set_device_slots(*m);
    const u32 bpp = ld32(*m, gp_slot(b::kGpBppMain));
    REQUIRE(bpp != 0);
    const u32 n = ld32(*m, bpp + b::kBppCount);
    MESSAGE("b_5800: bpp_main.c at " << hex64(bpp) << ", " << n << " members, flags " << hex64(ld32(*m, bpp)));
    CHECK(n >= 1);
    CHECK(n <= 4);
    // the live records: party ids and slide length 2 (n - 1) + 6
    CHECK(static_cast<s32>(ld32(*m, bpp + b::kBppSlideMax)) == static_cast<s32>(2 * (n - 1) + 6));
    for (u32 r = 0; r < n; ++r) {
        const u32 pn = bpp + b::kBppMembers + b::kBppMemberSize * r + b::kBmPanel;
        CHECK((ld32(*m, pn + b::kBpnFlags) & 1u) == 1u);  // open
        CHECK(ld16(*m, pn + b::kBpnId) == ld16(*m, bpp + b::kBppMembers + b::kBppMemberSize * r + b::kBmId));
    }
    // rebuild (sub_20F680 closes, sub_20F3B0 builds): the same members, slide rescaled, values -1 for the refresh
    const u32 slide = ld32(*m, bpp + b::kBppSlide), smax = ld32(*m, bpp + b::kBppSlideMax);
    run_ok(*m, "sub_20F680", {0, 0, 0, 0});
    CHECK(ld32(*m, bpp + b::kBppCount) == 0u);
    CHECK((ld32(*m, bpp) & 2u) == 0u);
    run_ok(*m, "sub_20F3B0", {0, 0, 0, 0});
    CHECK(ld32(*m, bpp + b::kBppCount) == n);
    CHECK((ld32(*m, bpp) & 2u) == 2u);
    CHECK(ld32(*m, bpp + b::kBppSlide) == (smax ? slide * (2 * (n - 1) + 6) / smax : 0u));
    for (u32 r = 0; r < n; ++r) {
        const u32 mem = bpp + b::kBppMembers + b::kBppMemberSize * r;
        for (u32 o : {16u, 20u, 24u, 28u}) CHECK(ld32(*m, mem + o) == 0xFFFFFFFFu);
        CHECK(ldf(*m, mem + b::kBmPanel + b::kBpnX) == 476.0f);
    }
    // one update refreshes every value (they were -1) while the panel runs (flag bit 7), and the draw hook runs
    st32(*m, bpp, ld32(*m, bpp) | 0x80u);
    run_ok(*m, "sub_20EDF0", {0, 0, 0, 0});
    for (u32 r = 0; r < n; ++r) {
        const u32 mem = bpp + b::kBppMembers + b::kBppMemberSize * r;
        CHECK(ld32(*m, mem + b::kBmHp) != 0xFFFFFFFFu);
        CHECK(ld32(*m, mem + b::kBmHp) == ld32(*m, mem + b::kBmPanel + b::kBpnHp));  // the panel's digits follow
        CHECK(ld32(*m, mem + b::kBmSp) == ld32(*m, mem + b::kBmPanel + b::kBpnSp));
    }
    run_ok(*m, "sub_20F260", {0, 0, 0, 0});
}

#else

TEST_CASE("game(band20): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
