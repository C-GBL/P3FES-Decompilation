// Pair tests for slice finalD (game/src/lib/finalD.cpp): the 21 functions with mid-body entries -- each of the 23 entry
// points is its own pair, `<name>_at_<pc8>` (through its forwarder fn_<name>_<addr8>_at_<pc8>) against the recompiled
// entry form at that address (fn_..._at_<pc8>__recomp), the function start against fn_<name>_<addr8>__recomp -- compared
// by tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the return /
// stop, all 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window and the bus log. Worlds: random worlds
// (every entry; the standard stand-ins -- heap, printf / sprintf, the H_Cdvd layer -- installed in both runs with
// equal call logs), and documented rules from the instructions on the leaf entries: the constant and field getters,
// the zeroing resets, the track map, the descrambler XOR pass, the CFT setter, the return stub.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/finalD.h"

#include <cstring>

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_vfprintf_00526238(EEContext&);  // generated body
void fn_vfprintf_00526238__recomp(EEContext&);  // recompiled
void fn_vfprintf_00526238_at_005262b0(EEContext&);  // generated body
void fn_vfprintf_00526238_at_005262b0__recomp(EEContext&);  // recompiled
void fn_sub_53EF40_0053ef40(EEContext&);  // generated body
void fn_sub_53EF40_0053ef40__recomp(EEContext&);  // recompiled
void fn_sub_53EF40_0053ef40_at_0053efc0(EEContext&);  // generated body
void fn_sub_53EF40_0053ef40_at_0053efc0__recomp(EEContext&);  // recompiled
void fn_sub_54E7D8_0054e7d8(EEContext&);  // generated body
void fn_sub_54E7D8_0054e7d8__recomp(EEContext&);  // recompiled
void fn_sub_54E7D8_0054e7d8_at_0054e7f0(EEContext&);  // generated body
void fn_sub_54E7D8_0054e7d8_at_0054e7f0__recomp(EEContext&);  // recompiled
void fn_sub_54E7D8_0054e7d8_at_0054e808(EEContext&);  // generated body
void fn_sub_54E7D8_0054e7d8_at_0054e808__recomp(EEContext&);  // recompiled
void fn_sub_554138_00554138(EEContext&);  // generated body
void fn_sub_554138_00554138__recomp(EEContext&);  // recompiled
void fn_sub_554138_00554138_at_005541a8(EEContext&);  // generated body
void fn_sub_554138_00554138_at_005541a8__recomp(EEContext&);  // recompiled
void fn_sub_56DE28_0056de28(EEContext&);  // generated body
void fn_sub_56DE28_0056de28__recomp(EEContext&);  // recompiled
void fn_sub_56DE28_0056de28_at_0056de50(EEContext&);  // generated body
void fn_sub_56DE28_0056de28_at_0056de50__recomp(EEContext&);  // recompiled
void fn_sub_56DE28_0056de28_at_0056de78(EEContext&);  // generated body
void fn_sub_56DE28_0056de28_at_0056de78__recomp(EEContext&);  // recompiled
void fn_sub_56F8F8_0056f8f8(EEContext&);  // generated body
void fn_sub_56F8F8_0056f8f8__recomp(EEContext&);  // recompiled
void fn_sub_56F8F8_0056f8f8_at_0056f978(EEContext&);  // generated body
void fn_sub_56F8F8_0056f8f8_at_0056f978__recomp(EEContext&);  // recompiled
void fn_sub_577BB8_00577bb8(EEContext&);  // generated body
void fn_sub_577BB8_00577bb8__recomp(EEContext&);  // recompiled
void fn_sub_577BB8_00577bb8_at_00577bd0(EEContext&);  // generated body
void fn_sub_577BB8_00577bb8_at_00577bd0__recomp(EEContext&);  // recompiled
void fn_sub_578D60_00578d60(EEContext&);  // generated body
void fn_sub_578D60_00578d60__recomp(EEContext&);  // recompiled
void fn_sub_578D60_00578d60_at_00578d80(EEContext&);  // generated body
void fn_sub_578D60_00578d60_at_00578d80__recomp(EEContext&);  // recompiled
void fn_sub_57C0C0_0057c0c0(EEContext&);  // generated body
void fn_sub_57C0C0_0057c0c0__recomp(EEContext&);  // recompiled
void fn_sub_57C0C0_0057c0c0_at_0057c138(EEContext&);  // generated body
void fn_sub_57C0C0_0057c0c0_at_0057c138__recomp(EEContext&);  // recompiled
void fn_sub_580A28_00580a28(EEContext&);  // generated body
void fn_sub_580A28_00580a28__recomp(EEContext&);  // recompiled
void fn_sub_580A28_00580a28_at_00580a48(EEContext&);  // generated body
void fn_sub_580A28_00580a28_at_00580a48__recomp(EEContext&);  // recompiled
void fn_sub_582838_00582838(EEContext&);  // generated body
void fn_sub_582838_00582838__recomp(EEContext&);  // recompiled
void fn_sub_582838_00582838_at_00582850(EEContext&);  // generated body
void fn_sub_582838_00582838_at_00582850__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_add_4_005866a8(EEContext&);  // generated body
void fn_R_LOCK_DEF_add_4_005866a8__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_add_4_005866a8_at_005866bc(EEContext&);  // generated body
void fn_R_LOCK_DEF_add_4_005866a8_at_005866bc__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_lock_new_5_00587f00(EEContext&);  // generated body
void fn_R_LOCK_DEF_lock_new_5_00587f00__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_lock_new_5_00587f00_at_00587f50(EEContext&);  // generated body
void fn_R_LOCK_DEF_lock_new_5_00587f00_at_00587f50__recomp(EEContext&);  // recompiled
void fn_sub_589018_00589018(EEContext&);  // generated body
void fn_sub_589018_00589018__recomp(EEContext&);  // recompiled
void fn_sub_589018_00589018_at_00589030(EEContext&);  // generated body
void fn_sub_589018_00589018_at_00589030__recomp(EEContext&);  // recompiled
void fn_sub_5890F0_005890f0(EEContext&);  // generated body
void fn_sub_5890F0_005890f0__recomp(EEContext&);  // recompiled
void fn_sub_5890F0_005890f0_at_00589108(EEContext&);  // generated body
void fn_sub_5890F0_005890f0_at_00589108__recomp(EEContext&);  // recompiled
void fn_sub_58B398_0058b398(EEContext&);  // generated body
void fn_sub_58B398_0058b398__recomp(EEContext&);  // recompiled
void fn_sub_58B398_0058b398_at_0058b3d8(EEContext&);  // generated body
void fn_sub_58B398_0058b398_at_0058b3d8__recomp(EEContext&);  // recompiled
void fn_sub_58E800_0058e800(EEContext&);  // generated body
void fn_sub_58E800_0058e800__recomp(EEContext&);  // recompiled
void fn_sub_58E800_0058e800_at_0058e888(EEContext&);  // generated body
void fn_sub_58E800_0058e800_at_0058e888__recomp(EEContext&);  // recompiled
void fn_sub_5923E0_005923e0(EEContext&);  // generated body
void fn_sub_5923E0_005923e0__recomp(EEContext&);  // recompiled
void fn_sub_5923E0_005923e0_at_00592488(EEContext&);  // generated body
void fn_sub_5923E0_005923e0_at_00592488__recomp(EEContext&);  // recompiled
void fn_sub_59B4F0_0059b4f0(EEContext&);  // generated body
void fn_sub_59B4F0_0059b4f0__recomp(EEContext&);  // recompiled
void fn_sub_59B4F0_0059b4f0_at_0059b588(EEContext&);  // generated body
void fn_sub_59B4F0_0059b4f0_at_0059b588__recomp(EEContext&);  // recompiled
void fn_sub_59BAF0_0059baf0(EEContext&);  // generated body
void fn_sub_59BAF0_0059baf0__recomp(EEContext&);  // recompiled
void fn_sub_59BAF0_0059baf0_at_0059bb10(EEContext&);  // generated body
void fn_sub_59BAF0_0059baf0_at_0059bb10__recomp(EEContext&);  // recompiled
void fn_sub_5A0C00_005a0c00(EEContext&);  // generated body
void fn_sub_5A0C00_005a0c00__recomp(EEContext&);  // recompiled
void fn_sub_5A0C00_005a0c00_at_005a0ca0(EEContext&);  // generated body
void fn_sub_5A0C00_005a0c00_at_005a0ca0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"vfprintf", 0x526238, &recomp_gen::fn_vfprintf_00526238, &recomp_gen::fn_vfprintf_00526238__recomp},
    {"vfprintf_at_005262b0", 0x5262B0, &recomp_gen::fn_vfprintf_00526238_at_005262b0, &recomp_gen::fn_vfprintf_00526238_at_005262b0__recomp},
    {"sub_53EF40", 0x53EF40, &recomp_gen::fn_sub_53EF40_0053ef40, &recomp_gen::fn_sub_53EF40_0053ef40__recomp},
    {"sub_53EF40_at_0053efc0", 0x53EFC0, &recomp_gen::fn_sub_53EF40_0053ef40_at_0053efc0, &recomp_gen::fn_sub_53EF40_0053ef40_at_0053efc0__recomp},
    {"sub_54E7D8", 0x54E7D8, &recomp_gen::fn_sub_54E7D8_0054e7d8, &recomp_gen::fn_sub_54E7D8_0054e7d8__recomp},
    {"sub_54E7D8_at_0054e7f0", 0x54E7F0, &recomp_gen::fn_sub_54E7D8_0054e7d8_at_0054e7f0, &recomp_gen::fn_sub_54E7D8_0054e7d8_at_0054e7f0__recomp},
    {"sub_54E7D8_at_0054e808", 0x54E808, &recomp_gen::fn_sub_54E7D8_0054e7d8_at_0054e808, &recomp_gen::fn_sub_54E7D8_0054e7d8_at_0054e808__recomp},
    {"sub_554138", 0x554138, &recomp_gen::fn_sub_554138_00554138, &recomp_gen::fn_sub_554138_00554138__recomp},
    {"sub_554138_at_005541a8", 0x5541A8, &recomp_gen::fn_sub_554138_00554138_at_005541a8, &recomp_gen::fn_sub_554138_00554138_at_005541a8__recomp},
    {"sub_56DE28", 0x56DE28, &recomp_gen::fn_sub_56DE28_0056de28, &recomp_gen::fn_sub_56DE28_0056de28__recomp},
    {"sub_56DE28_at_0056de50", 0x56DE50, &recomp_gen::fn_sub_56DE28_0056de28_at_0056de50, &recomp_gen::fn_sub_56DE28_0056de28_at_0056de50__recomp},
    {"sub_56DE28_at_0056de78", 0x56DE78, &recomp_gen::fn_sub_56DE28_0056de28_at_0056de78, &recomp_gen::fn_sub_56DE28_0056de28_at_0056de78__recomp},
    {"sub_56F8F8", 0x56F8F8, &recomp_gen::fn_sub_56F8F8_0056f8f8, &recomp_gen::fn_sub_56F8F8_0056f8f8__recomp},
    {"sub_56F8F8_at_0056f978", 0x56F978, &recomp_gen::fn_sub_56F8F8_0056f8f8_at_0056f978, &recomp_gen::fn_sub_56F8F8_0056f8f8_at_0056f978__recomp},
    {"sub_577BB8", 0x577BB8, &recomp_gen::fn_sub_577BB8_00577bb8, &recomp_gen::fn_sub_577BB8_00577bb8__recomp},
    {"sub_577BB8_at_00577bd0", 0x577BD0, &recomp_gen::fn_sub_577BB8_00577bb8_at_00577bd0, &recomp_gen::fn_sub_577BB8_00577bb8_at_00577bd0__recomp},
    {"sub_578D60", 0x578D60, &recomp_gen::fn_sub_578D60_00578d60, &recomp_gen::fn_sub_578D60_00578d60__recomp},
    {"sub_578D60_at_00578d80", 0x578D80, &recomp_gen::fn_sub_578D60_00578d60_at_00578d80, &recomp_gen::fn_sub_578D60_00578d60_at_00578d80__recomp},
    {"sub_57C0C0", 0x57C0C0, &recomp_gen::fn_sub_57C0C0_0057c0c0, &recomp_gen::fn_sub_57C0C0_0057c0c0__recomp},
    {"sub_57C0C0_at_0057c138", 0x57C138, &recomp_gen::fn_sub_57C0C0_0057c0c0_at_0057c138, &recomp_gen::fn_sub_57C0C0_0057c0c0_at_0057c138__recomp},
    {"sub_580A28", 0x580A28, &recomp_gen::fn_sub_580A28_00580a28, &recomp_gen::fn_sub_580A28_00580a28__recomp},
    {"sub_580A28_at_00580a48", 0x580A48, &recomp_gen::fn_sub_580A28_00580a28_at_00580a48, &recomp_gen::fn_sub_580A28_00580a28_at_00580a48__recomp},
    {"sub_582838", 0x582838, &recomp_gen::fn_sub_582838_00582838, &recomp_gen::fn_sub_582838_00582838__recomp},
    {"sub_582838_at_00582850", 0x582850, &recomp_gen::fn_sub_582838_00582838_at_00582850, &recomp_gen::fn_sub_582838_00582838_at_00582850__recomp},
    {"R_LOCK_DEF_add_4", 0x5866A8, &recomp_gen::fn_R_LOCK_DEF_add_4_005866a8, &recomp_gen::fn_R_LOCK_DEF_add_4_005866a8__recomp},
    {"R_LOCK_DEF_add_4_at_005866bc", 0x5866BC, &recomp_gen::fn_R_LOCK_DEF_add_4_005866a8_at_005866bc, &recomp_gen::fn_R_LOCK_DEF_add_4_005866a8_at_005866bc__recomp},
    {"R_LOCK_DEF_lock_new_5", 0x587F00, &recomp_gen::fn_R_LOCK_DEF_lock_new_5_00587f00, &recomp_gen::fn_R_LOCK_DEF_lock_new_5_00587f00__recomp},
    {"R_LOCK_DEF_lock_new_5_at_00587f50", 0x587F50, &recomp_gen::fn_R_LOCK_DEF_lock_new_5_00587f00_at_00587f50, &recomp_gen::fn_R_LOCK_DEF_lock_new_5_00587f00_at_00587f50__recomp},
    {"sub_589018", 0x589018, &recomp_gen::fn_sub_589018_00589018, &recomp_gen::fn_sub_589018_00589018__recomp},
    {"sub_589018_at_00589030", 0x589030, &recomp_gen::fn_sub_589018_00589018_at_00589030, &recomp_gen::fn_sub_589018_00589018_at_00589030__recomp},
    {"sub_5890F0", 0x5890F0, &recomp_gen::fn_sub_5890F0_005890f0, &recomp_gen::fn_sub_5890F0_005890f0__recomp},
    {"sub_5890F0_at_00589108", 0x589108, &recomp_gen::fn_sub_5890F0_005890f0_at_00589108, &recomp_gen::fn_sub_5890F0_005890f0_at_00589108__recomp},
    {"sub_58B398", 0x58B398, &recomp_gen::fn_sub_58B398_0058b398, &recomp_gen::fn_sub_58B398_0058b398__recomp},
    {"sub_58B398_at_0058b3d8", 0x58B3D8, &recomp_gen::fn_sub_58B398_0058b398_at_0058b3d8, &recomp_gen::fn_sub_58B398_0058b398_at_0058b3d8__recomp},
    {"sub_58E800", 0x58E800, &recomp_gen::fn_sub_58E800_0058e800, &recomp_gen::fn_sub_58E800_0058e800__recomp},
    {"sub_58E800_at_0058e888", 0x58E888, &recomp_gen::fn_sub_58E800_0058e800_at_0058e888, &recomp_gen::fn_sub_58E800_0058e800_at_0058e888__recomp},
    {"sub_5923E0", 0x5923E0, &recomp_gen::fn_sub_5923E0_005923e0, &recomp_gen::fn_sub_5923E0_005923e0__recomp},
    {"sub_5923E0_at_00592488", 0x592488, &recomp_gen::fn_sub_5923E0_005923e0_at_00592488, &recomp_gen::fn_sub_5923E0_005923e0_at_00592488__recomp},
    {"sub_59B4F0", 0x59B4F0, &recomp_gen::fn_sub_59B4F0_0059b4f0, &recomp_gen::fn_sub_59B4F0_0059b4f0__recomp},
    {"sub_59B4F0_at_0059b588", 0x59B588, &recomp_gen::fn_sub_59B4F0_0059b4f0_at_0059b588, &recomp_gen::fn_sub_59B4F0_0059b4f0_at_0059b588__recomp},
    {"sub_59BAF0", 0x59BAF0, &recomp_gen::fn_sub_59BAF0_0059baf0, &recomp_gen::fn_sub_59BAF0_0059baf0__recomp},
    {"sub_59BAF0_at_0059bb10", 0x59BB10, &recomp_gen::fn_sub_59BAF0_0059baf0_at_0059bb10, &recomp_gen::fn_sub_59BAF0_0059baf0_at_0059bb10__recomp},
    {"sub_5A0C00", 0x5A0C00, &recomp_gen::fn_sub_5A0C00_005a0c00, &recomp_gen::fn_sub_5A0C00_005a0c00__recomp},
    {"sub_5A0C00_at_005a0ca0", 0x5A0CA0, &recomp_gen::fn_sub_5A0C00_005a0c00_at_005a0ca0, &recomp_gen::fn_sub_5A0C00_005a0c00_at_005a0ca0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

// Pairs with the stand-ins: both bodies get a fresh standard set and the two call logs must be equal.
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
int g_pairs = 0;
int g_stops = 0;
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    install_standard(*wh);
    install_standard(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    ++g_pairs;
    g_stops += r.stopped ? 1 : 0;
    return r;
}

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

}  // namespace

TEST_CASE("game(finalD): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += spair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

TEST_CASE("game(finalD): the entry points' documented rules -- getters, resets, the track map, the XOR pass") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto run = [&](const char* name, const Args& a) {
        const Case& c = find_case(name);
        return spair(*m, c.hand, c.recomp, a, 1, c.name);
    };
    g_pairs = g_stops = 0;
    const u32 a = kWorld, b = kWorld + 0x4000;
    std::memset(m->at(kWorld), 0, kWorldSize);

    // sub_54E7D8: the start and the entry 0x54E808 return 96; the entry 0x54E7F0 reads word +496 behind the byte flag +421
    CHECK(v0_of(run("sub_54E7D8", Args{sx(a), 0, 0, 0})) == 96u);
    CHECK(v0_of(run("sub_54E7D8_at_0054e808", Args{sx(a), 0, 0, 0})) == 96u);
    w32(*m, a + 496, 0x1234);
    CHECK(v0_of(run("sub_54E7D8_at_0054e7f0", Args{sx(a), 0, 0, 0})) == 0u);
    *m->at(a + 421) = 1;
    CHECK(v0_of(run("sub_54E7D8_at_0054e7f0", Args{sx(a), 0, 0, 0})) == 0x1234u);

    // sub_577BB8 / sub_578D60: the resets zero three / five words of the block in $a0; the start of sub_578D60 resets the
    // MPV globals at 0x7B29E8
    for (u32 i = 0; i < 6; ++i) w32(*m, b + 4 * i, 0xA5A5A5A5u);
    run("sub_577BB8_at_00577bd0", Args{sx(b), 0, 0, 0});
    CHECK(r32(*m, b) == 0u);
    CHECK(r32(*m, b + 8) == 0u);
    CHECK(r32(*m, b + 12) == 0xA5A5A5A5u);
    for (u32 i = 0; i < 6; ++i) w32(*m, b + 4 * i, 0xA5A5A5A5u);
    run("sub_578D60_at_00578d80", Args{sx(b), 0, 0, 0});
    CHECK(r32(*m, b + 16) == 0u);
    CHECK(r32(*m, b + 20) == 0xA5A5A5A5u);
    for (u32 i = 0; i < 5; ++i) w32(*m, 0x7B29E8u + 4 * i, 0x5A5A5A5Au);
    run("sub_578D60", Args{0, 0, 0, 0});
    CHECK(r32(*m, 0x7B29E8u) == 0u);
    CHECK(r32(*m, 0x7B29F8u) == 0u);

    // sub_59BAF0 (ctx, stream, slot, track): ctx[8004 + 68*stream + 4*slot] = track, ctx[4956 + 116*track] = stream,
    // $v0 = 116*track; the start is the (ctx, stream, track) form with slot 2
    CHECK(v0_of(run("sub_59BAF0_at_0059bb10", Args{sx(a), 3, 1, 5})) == 116u * 5u);
    CHECK(r32(*m, a + 8004 + 68 * 3 + 4 * 1) == 5u);
    CHECK(r32(*m, a + 4956 + 116 * 5) == 3u);
    CHECK(v0_of(run("sub_59BAF0", Args{sx(a), 7, 9, 0})) == 116u * 9u);
    CHECK(r32(*m, a + 8004 + 68 * 7 + 4 * 2) == 9u);
    CHECK(r32(*m, a + 4956 + 116 * 9) == 7u);

    // sub_56DE28: the entry 0x56DE78 stores $a0 into dword_7B291C; the entry 0x56DE50 and R_LOCK_DEF_add_4's entry are
    // return stubs (nothing written)
    run("sub_56DE28_at_0056de78", Args{0xBEEF, 0, 0, 0});
    CHECK(r32(*m, 0x7B291Cu) == 0xBEEFu);
    run("sub_56DE28_at_0056de50", Args{sx(a), 0, 0, 0});
    run("R_LOCK_DEF_add_4_at_005866bc", Args{sx(a), 0, 0, 0});

    // sub_57C0C0's XOR pass (key, block): block[i] ^= key[5 + i] ^ block[32 + i] over 32 halfwords
    u16 key[40], blk[64];
    for (u32 i = 0; i < 40; ++i) key[i] = static_cast<u16>(0x1111u * (i + 1));
    for (u32 i = 0; i < 64; ++i) blk[i] = static_cast<u16>(0x0101u * i + 7);
    std::memcpy(m->at(a), key, sizeof key);
    std::memcpy(m->at(b), blk, sizeof blk);
    run("sub_57C0C0_at_0057c138", Args{sx(a), sx(b), 0, 0});
    for (u32 i = 0; i < 32; ++i) {
        u16 got = 0;
        std::memcpy(&got, m->at(b + 2 * i), 2);
        CHECK(got == static_cast<u16>(blk[i] ^ key[5 + i] ^ blk[32 + i]));
    }
    MESSAGE(g_pairs << " rule pairs, " << g_stops << " stopped early");
}

#else

TEST_CASE("game(finalD): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
