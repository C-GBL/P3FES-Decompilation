// Pair tests of the boot slice's scene band (game/src/boot/boot_scene.cpp, boot_scene.h). Every body against its
// recompiled body on random worlds (the p3fes_handgen skeleton, tests/game/handgen_pairs.h: the whole register file and
// cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus
// log), then the scene colour scale and the scene-draw passes with their documented rules (stand-in world).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/boot_scene.h"

#include <cstring>
#include <map>
#include <vector>

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
void fn_sub_199C60_00199c60(EEContext&);  // generated body
void fn_sub_199C60_00199c60__recomp(EEContext&);  // recompiled
void fn_sub_199CF0_00199cf0(EEContext&);  // generated body
void fn_sub_199CF0_00199cf0__recomp(EEContext&);  // recompiled
void fn_sub_19AB30_0019ab30(EEContext&);  // generated body
void fn_sub_19AB30_0019ab30__recomp(EEContext&);  // recompiled
void fn_sub_19B2B0_0019b2b0(EEContext&);  // generated body
void fn_sub_19B2B0_0019b2b0__recomp(EEContext&);  // recompiled
void fn_sub_19BEB0_0019beb0(EEContext&);  // generated body
void fn_sub_19BEB0_0019beb0__recomp(EEContext&);  // recompiled
void fn_sub_19C320_0019c320(EEContext&);  // generated body
void fn_sub_19C320_0019c320__recomp(EEContext&);  // recompiled
void fn_sub_19C4B0_0019c4b0(EEContext&);  // generated body
void fn_sub_19C4B0_0019c4b0__recomp(EEContext&);  // recompiled
void fn_sub_19D270_0019d270(EEContext&);  // generated body
void fn_sub_19D270_0019d270__recomp(EEContext&);  // recompiled
void fn_sub_19D2A0_0019d2a0(EEContext&);  // generated body
void fn_sub_19D2A0_0019d2a0__recomp(EEContext&);  // recompiled
void fn_K_SceneDraw_UpdateDrwOpcFldTask_0019d410(EEContext&);  // generated body
void fn_K_SceneDraw_UpdateDrwOpcFldTask_0019d410__recomp(EEContext&);  // recompiled
void fn_sub_19D4A0_0019d4a0(EEContext&);  // generated body
void fn_sub_19D4A0_0019d4a0__recomp(EEContext&);  // recompiled
void fn_sub_19DE40_0019de40(EEContext&);  // generated body
void fn_sub_19DE40_0019de40__recomp(EEContext&);  // recompiled
void fn_sub_19E1B0_0019e1b0(EEContext&);  // generated body
void fn_sub_19E1B0_0019e1b0__recomp(EEContext&);  // recompiled
void fn_sub_19E1F0_0019e1f0(EEContext&);  // generated body
void fn_sub_19E1F0_0019e1f0__recomp(EEContext&);  // recompiled
void fn_sub_19E330_0019e330(EEContext&);  // generated body
void fn_sub_19E330_0019e330__recomp(EEContext&);  // recompiled
void fn_sub_19EE40_0019ee40(EEContext&);  // generated body
void fn_sub_19EE40_0019ee40__recomp(EEContext&);  // recompiled
void fn_K_SceneDraw_CreateTasks_0019f730(EEContext&);  // generated body
void fn_K_SceneDraw_CreateTasks_0019f730__recomp(EEContext&);  // recompiled
void fn_sub_19F8F0_0019f8f0(EEContext&);  // generated body
void fn_sub_19F8F0_0019f8f0__recomp(EEContext&);  // recompiled
void fn_sub_19FDD0_0019fdd0(EEContext&);  // generated body
void fn_sub_19FDD0_0019fdd0__recomp(EEContext&);  // recompiled
void fn_sub_19FE20_0019fe20(EEContext&);  // generated body
void fn_sub_19FE20_0019fe20__recomp(EEContext&);  // recompiled
void fn_sub_19FE70_0019fe70(EEContext&);  // generated body
void fn_sub_19FE70_0019fe70__recomp(EEContext&);  // recompiled
void fn_sub_19FEC0_0019fec0(EEContext&);  // generated body
void fn_sub_19FEC0_0019fec0__recomp(EEContext&);  // recompiled
void fn_sub_19FF10_0019ff10(EEContext&);  // generated body
void fn_sub_19FF10_0019ff10__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_199C60", 0x199C60, &recomp_gen::fn_sub_199C60_00199c60, &recomp_gen::fn_sub_199C60_00199c60__recomp},
    {"sub_199CF0", 0x199CF0, &recomp_gen::fn_sub_199CF0_00199cf0, &recomp_gen::fn_sub_199CF0_00199cf0__recomp},
    {"sub_19AB30", 0x19AB30, &recomp_gen::fn_sub_19AB30_0019ab30, &recomp_gen::fn_sub_19AB30_0019ab30__recomp},
    {"sub_19B2B0", 0x19B2B0, &recomp_gen::fn_sub_19B2B0_0019b2b0, &recomp_gen::fn_sub_19B2B0_0019b2b0__recomp},
    {"sub_19BEB0", 0x19BEB0, &recomp_gen::fn_sub_19BEB0_0019beb0, &recomp_gen::fn_sub_19BEB0_0019beb0__recomp},
    {"sub_19C320", 0x19C320, &recomp_gen::fn_sub_19C320_0019c320, &recomp_gen::fn_sub_19C320_0019c320__recomp},
    {"sub_19C4B0", 0x19C4B0, &recomp_gen::fn_sub_19C4B0_0019c4b0, &recomp_gen::fn_sub_19C4B0_0019c4b0__recomp},
    {"sub_19D270", 0x19D270, &recomp_gen::fn_sub_19D270_0019d270, &recomp_gen::fn_sub_19D270_0019d270__recomp},
    {"sub_19D2A0", 0x19D2A0, &recomp_gen::fn_sub_19D2A0_0019d2a0, &recomp_gen::fn_sub_19D2A0_0019d2a0__recomp},
    {"K_SceneDraw_UpdateDrwOpcFldTask", 0x19D410, &recomp_gen::fn_K_SceneDraw_UpdateDrwOpcFldTask_0019d410, &recomp_gen::fn_K_SceneDraw_UpdateDrwOpcFldTask_0019d410__recomp},
    {"sub_19D4A0", 0x19D4A0, &recomp_gen::fn_sub_19D4A0_0019d4a0, &recomp_gen::fn_sub_19D4A0_0019d4a0__recomp},
    {"sub_19DE40", 0x19DE40, &recomp_gen::fn_sub_19DE40_0019de40, &recomp_gen::fn_sub_19DE40_0019de40__recomp},
    {"sub_19E1B0", 0x19E1B0, &recomp_gen::fn_sub_19E1B0_0019e1b0, &recomp_gen::fn_sub_19E1B0_0019e1b0__recomp},
    {"sub_19E1F0", 0x19E1F0, &recomp_gen::fn_sub_19E1F0_0019e1f0, &recomp_gen::fn_sub_19E1F0_0019e1f0__recomp},
    {"sub_19E330", 0x19E330, &recomp_gen::fn_sub_19E330_0019e330, &recomp_gen::fn_sub_19E330_0019e330__recomp},
    {"sub_19EE40", 0x19EE40, &recomp_gen::fn_sub_19EE40_0019ee40, &recomp_gen::fn_sub_19EE40_0019ee40__recomp},
    {"K_SceneDraw_CreateTasks", 0x19F730, &recomp_gen::fn_K_SceneDraw_CreateTasks_0019f730, &recomp_gen::fn_K_SceneDraw_CreateTasks_0019f730__recomp},
    {"sub_19F8F0", 0x19F8F0, &recomp_gen::fn_sub_19F8F0_0019f8f0, &recomp_gen::fn_sub_19F8F0_0019f8f0__recomp},
    {"sub_19FDD0", 0x19FDD0, &recomp_gen::fn_sub_19FDD0_0019fdd0, &recomp_gen::fn_sub_19FDD0_0019fdd0__recomp},
    {"sub_19FE20", 0x19FE20, &recomp_gen::fn_sub_19FE20_0019fe20, &recomp_gen::fn_sub_19FE20_0019fe20__recomp},
    {"sub_19FE70", 0x19FE70, &recomp_gen::fn_sub_19FE70_0019fe70, &recomp_gen::fn_sub_19FE70_0019fe70__recomp},
    {"sub_19FEC0", 0x19FEC0, &recomp_gen::fn_sub_19FEC0_0019fec0, &recomp_gen::fn_sub_19FEC0_0019fec0__recomp},
    {"sub_19FF10", 0x19FF10, &recomp_gen::fn_sub_19FF10_0019ff10, &recomp_gen::fn_sub_19FF10_0019ff10__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(boot_scene): every body equals its recompiled body on random worlds") {
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
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}





// =====================================================================================================================
// Meaningful pairs: the scene colour scale (sub_19F8F0) on the stand-in world (the field-source list sub_3B5D50 stood
// in), with the documented rule checked on the host: the clear colour = the base clear colour (0x7CE124) scaled by
// the RGBA factors, each channel cut at 255; and the scene-draw control's children (K_SceneDraw_CreateTasks) with
// their priorities.
// =====================================================================================================================

namespace {

namespace rgs = p3fes::recomp_gen;

HwCheck scene_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}
void put_f(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }

}  // namespace

TEST_CASE("game(boot_scene): the scene colour scale scales and clamps the clear colour") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    const u32 scale = 0x01B90000u;
    std::mt19937 rng{0x5CE7E};
    const WorldSetup setup = [](StandInWorld& w) {
        install_standard(w);
        w.si.install_recorder(0x3B5D50u, "sub_3B5D50 (field sources: none)", 0);
    };
    int pairs = 0;
    for (int i = 0; i < 64; ++i) {
        u8 base[4];
        for (u8& b : base) b = static_cast<u8>(rng());
        std::memcpy(m->at(0x7CE124u), base, 4);
        float f[4];
        for (float& x : f) x = (rng() % 9 == 0) ? 0.0f : static_cast<float>(rng() % 3000) / 1000.0f;
        for (int k = 0; k < 4; ++k) put_f(*m, scale + 4u * static_cast<u32>(k), f[k]);
        run_pair_si(*m, &rgs::fn_sub_19F8F0_0019f8f0, &rgs::fn_sub_19F8F0_0019f8f0__recomp, {sx(scale), 0, 0, 0},
                    700 + static_cast<u32>(i), "sub_19F8F0", scene_check(), setup);
        ++pairs;
        for (int k = 0; k < 4; ++k) {
            const s32 v = static_cast<s32>(static_cast<float>(base[k]) * f[k]);
            const u32 want = static_cast<u32>(v) >= 0x100u ? 0xFFu : static_cast<u32>(v);
            CHECK(m->at(0x7CE128u)[k] == want);
        }
    }
    MESSAGE("colour scale: " << pairs << " pairs");
}

TEST_CASE("game(boot_scene): the scene-draw control creates its passes with the documented priorities") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    const u32 parent = 0x01B80000u;
    std::memset(m->at(parent), 0, 0x200);
    std::memset(m->at(0x7CE064u), 0, 0x7CE088u - 0x7CE064u);
    const SiPair p = run_pair_si(*m, &rgs::fn_K_SceneDraw_CreateTasks_0019f730, &rgs::fn_K_SceneDraw_CreateTasks_0019f730__recomp,
                                 {sx(parent), 0, 0, 0}, 801, "K_SceneDraw_CreateTasks", scene_check());
    const u32 ctl = static_cast<u32>(p.hw.recomp.base.v0);
    REQUIRE(ctl != 0);
    CHECK(m->str(ctl, 24) == "scene draw CTL");
    std::map<std::string, u32> prio;
    std::vector<u32> todo;
    u32 c;
    std::memcpy(&c, m->at(ctl + 0x50), 4);
    todo.push_back(c);
    while (!todo.empty()) {
        const u32 t = todo.back();
        todo.pop_back();
        if (!t) continue;
        u32 pr, sib;
        std::memcpy(&pr, m->at(t + 0x20), 4);
        std::memcpy(&sib, m->at(t + 0x54), 4);
        prio[m->str(t, 24)] = pr;
        todo.push_back(sib);
    }
    const std::pair<const char*, u32> documented[] = {
        {"shadow map camera", 2068}, {"draw opac field", 2070}, {"draw opac field object", 2071},
        {"draw character model", 2084}, {"draw trans field obj preChar", 2095}, {"draw persona model", 4168},
        {"draw trans field object", 4172}, {"draw trans field", 4173}, {"draw trans field(sort)", 4183},
        {"draw trans NPC(sort)", 4183},
    };
    for (const auto& [name, pr] : documented) {
        const std::string key = std::string(name).substr(0, 23);
        INFO(key);
        REQUIRE(prio.count(key) == 1);
        CHECK(prio[key] == pr);
    }
    CHECK(prio.size() == 10);
}

#else

TEST_CASE("game(boot_scene): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
