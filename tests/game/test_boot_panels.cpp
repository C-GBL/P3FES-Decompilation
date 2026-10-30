// Pair tests of the boot slice's panel band (game/src/boot/boot_panels.cpp, boot_panels.h). Every body against its
// recompiled body on random worlds (the p3fes_handgen skeleton, tests/game/handgen_pairs.h: the whole register file and
// cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus
// log), then a tween record over its whole life and the member-panel mode switch with their documented rules.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/boot_panels.h"

#include <algorithm>
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
void fn_sub_18A3F0_0018a3f0(EEContext&);  // generated body
void fn_sub_18A3F0_0018a3f0__recomp(EEContext&);  // recompiled
void fn_sub_18A9C0_0018a9c0(EEContext&);  // generated body
void fn_sub_18A9C0_0018a9c0__recomp(EEContext&);  // recompiled
void fn_sub_18A9F0_0018a9f0(EEContext&);  // generated body
void fn_sub_18A9F0_0018a9f0__recomp(EEContext&);  // recompiled
void fn_sub_18B270_0018b270(EEContext&);  // generated body
void fn_sub_18B270_0018b270__recomp(EEContext&);  // recompiled
void fn_sub_18B360_0018b360(EEContext&);  // generated body
void fn_sub_18B360_0018b360__recomp(EEContext&);  // recompiled
void fn_sub_18B380_0018b380(EEContext&);  // generated body
void fn_sub_18B380_0018b380__recomp(EEContext&);  // recompiled
void fn_sub_18B5F0_0018b5f0(EEContext&);  // generated body
void fn_sub_18B5F0_0018b5f0__recomp(EEContext&);  // recompiled
void fn_sub_18B620_0018b620(EEContext&);  // generated body
void fn_sub_18B620_0018b620__recomp(EEContext&);  // recompiled
void fn_sub_18B7B0_0018b7b0(EEContext&);  // generated body
void fn_sub_18B7B0_0018b7b0__recomp(EEContext&);  // recompiled
void fn_sub_18BA60_0018ba60(EEContext&);  // generated body
void fn_sub_18BA60_0018ba60__recomp(EEContext&);  // recompiled
void fn_sub_18BB20_0018bb20(EEContext&);  // generated body
void fn_sub_18BB20_0018bb20__recomp(EEContext&);  // recompiled
void fn_sub_18BB80_0018bb80(EEContext&);  // generated body
void fn_sub_18BB80_0018bb80__recomp(EEContext&);  // recompiled
void fn_sub_18BC80_0018bc80(EEContext&);  // generated body
void fn_sub_18BC80_0018bc80__recomp(EEContext&);  // recompiled
void fn_sub_18BD90_0018bd90(EEContext&);  // generated body
void fn_sub_18BD90_0018bd90__recomp(EEContext&);  // recompiled
void fn_sub_18BEE0_0018bee0(EEContext&);  // generated body
void fn_sub_18BEE0_0018bee0__recomp(EEContext&);  // recompiled
void fn_sub_18BFA0_0018bfa0(EEContext&);  // generated body
void fn_sub_18BFA0_0018bfa0__recomp(EEContext&);  // recompiled
void fn_sub_18BFF0_0018bff0(EEContext&);  // generated body
void fn_sub_18BFF0_0018bff0__recomp(EEContext&);  // recompiled
void fn_sub_18C0A0_0018c0a0(EEContext&);  // generated body
void fn_sub_18C0A0_0018c0a0__recomp(EEContext&);  // recompiled
void fn_sub_18C0C0_0018c0c0(EEContext&);  // generated body
void fn_sub_18C0C0_0018c0c0__recomp(EEContext&);  // recompiled
void fn_sub_18C150_0018c150(EEContext&);  // generated body
void fn_sub_18C150_0018c150__recomp(EEContext&);  // recompiled
void fn_sub_18C780_0018c780(EEContext&);  // generated body
void fn_sub_18C780_0018c780__recomp(EEContext&);  // recompiled
void fn_sub_18CE50_0018ce50(EEContext&);  // generated body
void fn_sub_18CE50_0018ce50__recomp(EEContext&);  // recompiled
void fn_sub_18D320_0018d320(EEContext&);  // generated body
void fn_sub_18D320_0018d320__recomp(EEContext&);  // recompiled
void fn_sub_18DB20_0018db20(EEContext&);  // generated body
void fn_sub_18DB20_0018db20__recomp(EEContext&);  // recompiled
void fn_sub_18DDE0_0018dde0(EEContext&);  // generated body
void fn_sub_18DDE0_0018dde0__recomp(EEContext&);  // recompiled
void fn_sub_18DE60_0018de60(EEContext&);  // generated body
void fn_sub_18DE60_0018de60__recomp(EEContext&);  // recompiled
void fn_sub_18E330_0018e330(EEContext&);  // generated body
void fn_sub_18E330_0018e330__recomp(EEContext&);  // recompiled
void fn_sub_18E390_0018e390(EEContext&);  // generated body
void fn_sub_18E390_0018e390__recomp(EEContext&);  // recompiled
void fn_sub_18E490_0018e490(EEContext&);  // generated body
void fn_sub_18E490_0018e490__recomp(EEContext&);  // recompiled
void fn_sub_18E4A0_0018e4a0(EEContext&);  // generated body
void fn_sub_18E4A0_0018e4a0__recomp(EEContext&);  // recompiled
void fn_sub_18E540_0018e540(EEContext&);  // generated body
void fn_sub_18E540_0018e540__recomp(EEContext&);  // recompiled
void fn_sub_18E5C0_0018e5c0(EEContext&);  // generated body
void fn_sub_18E5C0_0018e5c0__recomp(EEContext&);  // recompiled
void fn_sub_18E7A0_0018e7a0(EEContext&);  // generated body
void fn_sub_18E7A0_0018e7a0__recomp(EEContext&);  // recompiled
void fn_sub_18E820_0018e820(EEContext&);  // generated body
void fn_sub_18E820_0018e820__recomp(EEContext&);  // recompiled
void fn_sub_18E8E0_0018e8e0(EEContext&);  // generated body
void fn_sub_18E8E0_0018e8e0__recomp(EEContext&);  // recompiled
void fn_sub_18EB30_0018eb30(EEContext&);  // generated body
void fn_sub_18EB30_0018eb30__recomp(EEContext&);  // recompiled
void fn_sub_18EB40_0018eb40(EEContext&);  // generated body
void fn_sub_18EB40_0018eb40__recomp(EEContext&);  // recompiled
void fn_sub_18EF60_0018ef60(EEContext&);  // generated body
void fn_sub_18EF60_0018ef60__recomp(EEContext&);  // recompiled
void fn_sub_18EFB0_0018efb0(EEContext&);  // generated body
void fn_sub_18EFB0_0018efb0__recomp(EEContext&);  // recompiled
void fn_sub_18F060_0018f060(EEContext&);  // generated body
void fn_sub_18F060_0018f060__recomp(EEContext&);  // recompiled
void fn_sub_18F080_0018f080(EEContext&);  // generated body
void fn_sub_18F080_0018f080__recomp(EEContext&);  // recompiled
void fn_sub_18F0A0_0018f0a0(EEContext&);  // generated body
void fn_sub_18F0A0_0018f0a0__recomp(EEContext&);  // recompiled
void fn_sub_18F0B0_0018f0b0(EEContext&);  // generated body
void fn_sub_18F0B0_0018f0b0__recomp(EEContext&);  // recompiled
void fn_sub_18F0C0_0018f0c0(EEContext&);  // generated body
void fn_sub_18F0C0_0018f0c0__recomp(EEContext&);  // recompiled
void fn_sub_18F0E0_0018f0e0(EEContext&);  // generated body
void fn_sub_18F0E0_0018f0e0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_18A3F0", 0x18A3F0, &recomp_gen::fn_sub_18A3F0_0018a3f0, &recomp_gen::fn_sub_18A3F0_0018a3f0__recomp},
    {"sub_18A9C0", 0x18A9C0, &recomp_gen::fn_sub_18A9C0_0018a9c0, &recomp_gen::fn_sub_18A9C0_0018a9c0__recomp},
    {"sub_18A9F0", 0x18A9F0, &recomp_gen::fn_sub_18A9F0_0018a9f0, &recomp_gen::fn_sub_18A9F0_0018a9f0__recomp},
    {"sub_18B270", 0x18B270, &recomp_gen::fn_sub_18B270_0018b270, &recomp_gen::fn_sub_18B270_0018b270__recomp},
    {"sub_18B360", 0x18B360, &recomp_gen::fn_sub_18B360_0018b360, &recomp_gen::fn_sub_18B360_0018b360__recomp},
    {"sub_18B380", 0x18B380, &recomp_gen::fn_sub_18B380_0018b380, &recomp_gen::fn_sub_18B380_0018b380__recomp},
    {"sub_18B5F0", 0x18B5F0, &recomp_gen::fn_sub_18B5F0_0018b5f0, &recomp_gen::fn_sub_18B5F0_0018b5f0__recomp},
    {"sub_18B620", 0x18B620, &recomp_gen::fn_sub_18B620_0018b620, &recomp_gen::fn_sub_18B620_0018b620__recomp},
    {"sub_18B7B0", 0x18B7B0, &recomp_gen::fn_sub_18B7B0_0018b7b0, &recomp_gen::fn_sub_18B7B0_0018b7b0__recomp},
    {"sub_18BA60", 0x18BA60, &recomp_gen::fn_sub_18BA60_0018ba60, &recomp_gen::fn_sub_18BA60_0018ba60__recomp},
    {"sub_18BB20", 0x18BB20, &recomp_gen::fn_sub_18BB20_0018bb20, &recomp_gen::fn_sub_18BB20_0018bb20__recomp},
    {"sub_18BB80", 0x18BB80, &recomp_gen::fn_sub_18BB80_0018bb80, &recomp_gen::fn_sub_18BB80_0018bb80__recomp},
    {"sub_18BC80", 0x18BC80, &recomp_gen::fn_sub_18BC80_0018bc80, &recomp_gen::fn_sub_18BC80_0018bc80__recomp},
    {"sub_18BD90", 0x18BD90, &recomp_gen::fn_sub_18BD90_0018bd90, &recomp_gen::fn_sub_18BD90_0018bd90__recomp},
    {"sub_18BEE0", 0x18BEE0, &recomp_gen::fn_sub_18BEE0_0018bee0, &recomp_gen::fn_sub_18BEE0_0018bee0__recomp},
    {"sub_18BFA0", 0x18BFA0, &recomp_gen::fn_sub_18BFA0_0018bfa0, &recomp_gen::fn_sub_18BFA0_0018bfa0__recomp},
    {"sub_18BFF0", 0x18BFF0, &recomp_gen::fn_sub_18BFF0_0018bff0, &recomp_gen::fn_sub_18BFF0_0018bff0__recomp},
    {"sub_18C0A0", 0x18C0A0, &recomp_gen::fn_sub_18C0A0_0018c0a0, &recomp_gen::fn_sub_18C0A0_0018c0a0__recomp},
    {"sub_18C0C0", 0x18C0C0, &recomp_gen::fn_sub_18C0C0_0018c0c0, &recomp_gen::fn_sub_18C0C0_0018c0c0__recomp},
    {"sub_18C150", 0x18C150, &recomp_gen::fn_sub_18C150_0018c150, &recomp_gen::fn_sub_18C150_0018c150__recomp},
    {"sub_18C780", 0x18C780, &recomp_gen::fn_sub_18C780_0018c780, &recomp_gen::fn_sub_18C780_0018c780__recomp},
    {"sub_18CE50", 0x18CE50, &recomp_gen::fn_sub_18CE50_0018ce50, &recomp_gen::fn_sub_18CE50_0018ce50__recomp},
    {"sub_18D320", 0x18D320, &recomp_gen::fn_sub_18D320_0018d320, &recomp_gen::fn_sub_18D320_0018d320__recomp},
    {"sub_18DB20", 0x18DB20, &recomp_gen::fn_sub_18DB20_0018db20, &recomp_gen::fn_sub_18DB20_0018db20__recomp},
    {"sub_18DDE0", 0x18DDE0, &recomp_gen::fn_sub_18DDE0_0018dde0, &recomp_gen::fn_sub_18DDE0_0018dde0__recomp},
    {"sub_18DE60", 0x18DE60, &recomp_gen::fn_sub_18DE60_0018de60, &recomp_gen::fn_sub_18DE60_0018de60__recomp},
    {"sub_18E330", 0x18E330, &recomp_gen::fn_sub_18E330_0018e330, &recomp_gen::fn_sub_18E330_0018e330__recomp},
    {"sub_18E390", 0x18E390, &recomp_gen::fn_sub_18E390_0018e390, &recomp_gen::fn_sub_18E390_0018e390__recomp},
    {"sub_18E490", 0x18E490, &recomp_gen::fn_sub_18E490_0018e490, &recomp_gen::fn_sub_18E490_0018e490__recomp},
    {"sub_18E4A0", 0x18E4A0, &recomp_gen::fn_sub_18E4A0_0018e4a0, &recomp_gen::fn_sub_18E4A0_0018e4a0__recomp},
    {"sub_18E540", 0x18E540, &recomp_gen::fn_sub_18E540_0018e540, &recomp_gen::fn_sub_18E540_0018e540__recomp},
    {"sub_18E5C0", 0x18E5C0, &recomp_gen::fn_sub_18E5C0_0018e5c0, &recomp_gen::fn_sub_18E5C0_0018e5c0__recomp},
    {"sub_18E7A0", 0x18E7A0, &recomp_gen::fn_sub_18E7A0_0018e7a0, &recomp_gen::fn_sub_18E7A0_0018e7a0__recomp},
    {"sub_18E820", 0x18E820, &recomp_gen::fn_sub_18E820_0018e820, &recomp_gen::fn_sub_18E820_0018e820__recomp},
    {"sub_18E8E0", 0x18E8E0, &recomp_gen::fn_sub_18E8E0_0018e8e0, &recomp_gen::fn_sub_18E8E0_0018e8e0__recomp},
    {"sub_18EB30", 0x18EB30, &recomp_gen::fn_sub_18EB30_0018eb30, &recomp_gen::fn_sub_18EB30_0018eb30__recomp},
    {"sub_18EB40", 0x18EB40, &recomp_gen::fn_sub_18EB40_0018eb40, &recomp_gen::fn_sub_18EB40_0018eb40__recomp},
    {"sub_18EF60", 0x18EF60, &recomp_gen::fn_sub_18EF60_0018ef60, &recomp_gen::fn_sub_18EF60_0018ef60__recomp},
    {"sub_18EFB0", 0x18EFB0, &recomp_gen::fn_sub_18EFB0_0018efb0, &recomp_gen::fn_sub_18EFB0_0018efb0__recomp},
    {"sub_18F060", 0x18F060, &recomp_gen::fn_sub_18F060_0018f060, &recomp_gen::fn_sub_18F060_0018f060__recomp},
    {"sub_18F080", 0x18F080, &recomp_gen::fn_sub_18F080_0018f080, &recomp_gen::fn_sub_18F080_0018f080__recomp},
    {"sub_18F0A0", 0x18F0A0, &recomp_gen::fn_sub_18F0A0_0018f0a0, &recomp_gen::fn_sub_18F0A0_0018f0a0__recomp},
    {"sub_18F0B0", 0x18F0B0, &recomp_gen::fn_sub_18F0B0_0018f0b0, &recomp_gen::fn_sub_18F0B0_0018f0b0__recomp},
    {"sub_18F0C0", 0x18F0C0, &recomp_gen::fn_sub_18F0C0_0018f0c0, &recomp_gen::fn_sub_18F0C0_0018f0c0__recomp},
    {"sub_18F0E0", 0x18F0E0, &recomp_gen::fn_sub_18F0E0_0018f0e0, &recomp_gen::fn_sub_18F0E0_0018f0e0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(boot_panels): every body equals its recompiled body on random worlds") {
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
// Meaningful pairs: a tween record (boot_panels.h) evaluated over its whole life frame by frame through sub_18BB20 (each frame
// a pair: whole RAM, the register file at every check point, the dead stack), the machine carrying the recompiled
// run's state into the next frame; on the host the documented curves -- linear motion from + (to - from) t / n, the
// fade-in alpha 255 t / n, the fade-out 255 - 255 t / n, `to` at the last frame -- and the member-panel
// mode switch of sub_18DDE0.
// =====================================================================================================================

namespace {

namespace rgp = p3fes::recomp_gen;

u32 l32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
float lf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void st32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void stf(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }

constexpr u32 kRenderStateFixture = 0x51DF58u;  // a recorder for the RW render-state slot (sceSkSsSESQ_Control: never emitted)
constexpr u32 kTween = 0x01B90000u;

}  // namespace

TEST_CASE("game(boot_panels): a tween record runs its documented motion and fade over its frames") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    struct Shape {
        u32 motion, fade, first, last;
    };
    const Shape shapes[] = {{1, 2, 0, 10}, {1, 1, 3, 12}, {0, 0, 0, 5}, {1, 2, 5, 5}};
    int pairs = 0, drawn = 0;
    for (const Shape& sh : shapes) {
        std::memset(m->at(kTween), 0, 68);
        st32(*m, kTween + 4, 1);   // active
        st32(*m, kTween + 8, 0);   // kind: plain
        st32(*m, kTween + 12, sh.motion);
        st32(*m, kTween + 16, sh.fade);
        st32(*m, kTween + 28, sh.first);
        st32(*m, kTween + 32, sh.last);
        const float fx = 100.0f, fy = 50.0f, tx = 400.0f, ty = 250.0f;
        stf(*m, kTween + 40, fx);
        stf(*m, kTween + 44, fy);
        stf(*m, kTween + 48, tx);
        stf(*m, kTween + 52, ty);
        for (u32 frame = sh.first; frame <= sh.last; ++frame) {
            st32(*m, kTween + 24, frame);  // the stepper's frame count (sub_18B700 is hand-written since finalB; test_ui6 stands it in)
            hgp::pair(*m, &rgp::fn_sub_18BB20_0018bb20, &rgp::fn_sub_18BB20_0018bb20__recomp, {sx(kTween), 0, 0, 0},
                      500 + frame, "sub_18BB20 (tween frame)");
            ++pairs;
            ++drawn;
            const s32 t = static_cast<s32>(frame - sh.first), n = static_cast<s32>(sh.last - sh.first);
            const u32 alpha = l32(*m, kTween + 64);
            if (sh.fade == 2) CHECK(alpha == (n ? static_cast<u32>(255 * t / n) : 255u));
            if (sh.fade == 1) CHECK(alpha == (n ? static_cast<u32>(255 - 255 * t / n) : 0u));
            if (sh.fade == 0) CHECK(alpha == 0u);
            const float x = lf(*m, kTween + 56), y = lf(*m, kTween + 60);
            if (sh.motion == 0 || t == n) {
                CHECK(x == tx);
                CHECK(y == ty);
            } else {
                CHECK(x == doctest::Approx(fx + (tx - fx) * static_cast<float>(t) / static_cast<float>(n)).epsilon(1e-5));
                CHECK(y == doctest::Approx(fy + (ty - fy) * static_cast<float>(t) / static_cast<float>(n)).epsilon(1e-5));
            }
        }
    }
    MESSAGE("tween frames: " << pairs << " pairs, " << drawn << " drawn frames checked");
}

TEST_CASE("game(boot_panels): the member panel's mode switch keeps the mode to come back to") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 task = 0x01B90100u, work = 0x01B90200u;
    // kind -> mode: 0 -> 0, 1 -> 3 (the mark comes in), 2 -> 1, 3 -> 2 (the flash, the old mode saved in +16)
    const u32 mode_of[4] = {0, 3, 1, 2};
    int pairs = 0;
    for (u32 kind = 0; kind < 5; ++kind) {
        for (u32 before = 0; before < 5; ++before) {
            std::memset(m->at(task), 0, 0x68);
            std::memset(m->at(work), 0, 116);
            st32(*m, task + 60, work);
            st32(*m, work + 12, before);
            st32(*m, work + 16, 0xAAu);
            st32(*m, work + 24, 17);
            hgp::pair(*m, &rgp::fn_sub_18DDE0_0018dde0, &rgp::fn_sub_18DDE0_0018dde0__recomp, {sx(task), kind, 0, 0},
                      600 + kind * 8 + before, "sub_18DDE0");
            ++pairs;
            CHECK(l32(*m, work + 12) == (kind < 4 ? mode_of[kind] : before));
            CHECK(l32(*m, work + 16) == (kind == 3 ? before : 0xAAu));
            CHECK(l32(*m, work + 24) == 0u);  // the mode timer restarts
        }
    }
    MESSAGE("member mode switch: " << pairs << " pairs");
}

TEST_CASE("game(boot_panels): the cut-ins pick their files by spell and by unit") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    const u32 task = 0x01B90100u, work = 0x01B90200u;
    int pairs = 0;
    // the fusion-spell cut-in, step 0: index = spell - 0x110 for 0x110..0x121 (other spells keep the index), the
    // archive "battle/cutin/per_mix%02d.bin" requested, step 1, keep running (0)
    for (u32 spell = 0x10E; spell <= 0x123; ++spell) {
        std::memset(m->at(0x7E0380u), 0, 16 + 256);
        std::memset(m->at(task), 0, 0x68);
        std::memset(m->at(work), 0, 2676);
        st32(*m, task + 60, work);
        st32(*m, work + 4, spell);
        st32(*m, work + 8, 7);
        const SiPair p = run_pair_si(*m, &rgp::fn_sub_18A9F0_0018a9f0, &rgp::fn_sub_18A9F0_0018a9f0__recomp,
                                     {sx(task), 0, 0, 0}, 900 + spell, "sub_18A9F0 step 0", hw,
                                     [](StandInWorld& w) {
                                         install_standard(w);
                                         w.cd.load = false;
                                     });
        ++pairs;
        const u32 index = (spell >= 0x110 && spell <= 0x121) ? spell - 0x110 : 7;
        CHECK(l32(*m, work + 8) == index);
        CHECK(l32(*m, work) == 1);
        CHECK(static_cast<u32>(p.hw.recomp.base.v0) == 0);
        const StandIns& si = p.recomp->si;
        REQUIRE(si.calls_to(kHCdvdRequestFn) == 1);
        char name[64];
        std::snprintf(name, sizeof name, "battle/cutin/per_mix%02u.bin", index);
        for (const StandInCall& c : si.log)
            if (c.va == kHCdvdRequestFn) {
                CHECK(c.text == FakeCd::build_path(name));
                CHECK(c.args[1] == 1);  // an archive
                CHECK(static_cast<u32>(c.v0) == l32(*m, work + 64));
            }
    }
    // the battle member cut-in, steps 0 and 1: step 0 names the unit's movie (sprintf into the frame: the stand-in logs
    // the text), step 1 makes the animation task (sub_111150, hand-written by font2: it runs) and stores it at +8
    const char* movie_of[12] = {"4b00", "4b00", "4b00", "4b01", "4b02", "4b03", "4b00", "4b04", "4b05", nullptr, "4b07", "4b00"};
    for (u32 scenario = 0; scenario < 2; ++scenario) {
        for (u32 unit = 0; unit < 12; ++unit) {
            st32(*m, kGp - 19788u, scenario);
            std::memset(m->at(task), 0, 0x68);
            std::memset(m->at(work), 0, 976);
            st32(*m, task + 60, work);
            st32(*m, work + 4, unit);
            // the RwRenderStateSet slot (0x960090, filled by RenderWare at boot) aimed at a recorder: both bodies call it.
            // The recorder sits at a sound-driver entry no test build emits and no slice replaces (sceSkSsSESQ_Control,
            // IOP side); it used to sit at sub_104D10, the debug printer, which slice unblock replaced.
            st32(*m, 0x960090u, kRenderStateFixture);
            const WorldSetup setup = [](StandInWorld& w) {
                install_standard(w);
                w.si.install_recorder(kRenderStateFixture, "RwRenderStateSet (slot 0x960090)", 1);
            };
            const SiPair s0 = run_pair_si(*m, &rgp::fn_sub_18EB40_0018eb40, &rgp::fn_sub_18EB40_0018eb40__recomp,
                                          {sx(task), 0, 0, 0}, 1000 + unit, "sub_18EB40 step 0", hw, setup);
            ++pairs;
            CHECK(l32(*m, work) == 1);
            CHECK(static_cast<u32>(s0.hw.recomp.base.v0) == 0);
            const StandIns& si0 = s0.recomp->si;
            CHECK(si0.calls_to(kRenderStateFixture) == 7);  // render states 6..12 every frame
            REQUIRE(si0.calls_to(kSprintf) == 1);
            const std::string want = std::string("battle/cutin/c41_") + (unit == 9 ? (scenario ? "4b08" : "4b06") : movie_of[unit]) + ".cpk";
            for (const StandInCall& c : si0.log)
                if (c.va == kSprintf) CHECK(c.text == want);
            const SiPair s1 = run_pair_si(*m, &rgp::fn_sub_18EB40_0018eb40, &rgp::fn_sub_18EB40_0018eb40__recomp,
                                          {sx(task), 0, 0, 0}, 1100 + unit, "sub_18EB40 step 1", hw, setup);
            ++pairs;
            CHECK(l32(*m, work) == 2);
            CHECK(l32(*m, work + 8) != 0u);
            CHECK(static_cast<u32>(s1.hw.recomp.base.v0) == 0);
        }
    }
    MESSAGE("cut-in file picks: " << pairs << " pairs");
}

#else

TEST_CASE("game(boot_panels): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
