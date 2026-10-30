// Pair tests of slice sweep2, group fcl (game/src/sweep/sweep2_fcl.cpp): the body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the shop snapshot's real element set: the compendium element animator's groups (the ids each starts, no delay,
//     element 1 only for the compendium kind, the root panel move of group 15, unknown groups).
#include "sweep2_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s2t;

namespace p3fes::recomp_gen {
void fn_sub_4072D0_004072d0(EEContext&);  // generated body
void fn_sub_4072D0_004072d0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_4072D0", 0x4072D0, &recomp_gen::fn_sub_4072D0_004072d0, &recomp_gen::fn_sub_4072D0_004072d0__recomp},
};

}  // namespace

TEST_CASE("game(sweep2 fcl): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep2 cases (real data and documented rules) ---

namespace {

constexpr u32 kList = kScratch;            // a hand-made compendium list: +36 -> the work
constexpr u32 kWork = kScratch + 0x100;    // the shop work: +68 -> the screen record
constexpr u32 kScreen = kScratch + 0x200;  // +4 the list kind, +28 / +32 the element sets

// The shop snapshot's element set (fclShop.c's work +152) and its elements by id.
u32 shop_set(Machine& m) {
    const u32 seq = r32(m, game::shop::kShopSeqGlobal);
    if (seq == 0) return 0;
    const u32 work = r32(m, r32(m, seq + game::shop::kListObjPayload) + 12);
    return work ? r32(m, work + game::shop::kShopElements) : 0u;
}
u32 find_elem(Machine& m, u32 set, u32 id) {
    const u32 list = r32(m, set);
    u32 n = r32(m, list + game::shop::kListHead);
    for (int k = 0; n != 0 && k < 256; ++k, n = r32(m, n + game::shop::kNodeNext)) {
        const u32 e = r32(m, n + game::shop::kNodePayload);
        if (e != 0 && r32(m, e + game::shop::kElemId) == id) return e;
    }
    return 0;
}

}  // namespace

// sub_4072D0 [fclShopBook_AnimElements] on the shop snapshot's real element set (as both sets of a hand-made
// compendium screen): each group starts its elements (found or appended, started: state 1) with a template record
// stamped with the id; going out (dir 1) every element starts at once (delay +44 = 0), coming in (dir 0) the template
// staggers some of them by steps of 5 frames; group 14 adds element 1 only for the compendium kind (-8); group 15 also
// moves the root panel (sub_3E0C20(.., 2, 0 in / 2 out)); an unknown group touches nothing.
TEST_CASE("game(sweep2 fcl): the compendium element animator by group") {
    std::vector<u8> base;
    auto mp = snap_machine("shop_ref_4100", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or shop snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 set = shop_set(m);
    REQUIRE(set != 0u);
    struct G {
        u32 group;
        std::vector<u32> ids;
    };
    const G groups[] = {{13, {13}}, {12, {12}}, {11, {11}}, {16, {9, 10, 6}}, {15, {8, 4, 5, 6, 7, 3}}, {14, {0, 1}}};
    // the root-panel move sub_3E0C20 (hand-written since finalB) is recorded: the hooked forwarder serves the recorder
    const WorldSetup record_panel = [](StandInWorld& w) { w.si.install_recorder(0x3E0C20u, "sub_3E0C20 (panel move)", 0); };
    u32 seed = 900;
    for (const G& g : groups) {
        for (const u32 dir : {0u, 1u}) {
            for (const s32 kind : {-8, -9}) {
                if (g.group != 14 && kind == -9) continue;
                const SiPair sp = run_case_w(m, base, kCases, "sub_4072D0", {kList, g.group, dir, 0}, ++seed, [&](Machine& mm) {
                    std::memset(mm.at(kList), 0, 0x300);
                    w32(mm, kList + game::sw2::kBookListWork, kWork);
                    w32(mm, kWork + game::sw2::kBookScreen, kScreen);
                    w32(mm, kScreen + 4, static_cast<u32>(kind));
                    w32(mm, kScreen + game::sw2::kBookSetA, set);
                    w32(mm, kScreen + game::sw2::kBookSetB, set);
                }, record_panel);
                INFO("group " << g.group << " dir " << dir << " kind " << kind);
                for (u32 id : g.ids) {
                    const u32 e = find_elem(m, set, id);
                    if (g.group == 14 && id == 1 && kind != -8) {
                        // element 1 only for the compendium list (a registration list leaves it as it was)
                        continue;
                    }
                    REQUIRE(e != 0u);
                    CHECK(r32(m, e + game::shop::kElemState) == 1u);
                    const s16 delay = rs16(m, e + game::shop::kElemDelay);
                    if (dir == 1)
                        CHECK(delay == 0);
                    else
                        CHECK((delay >= 0 && delay <= 30 && delay % 5 == 0));
                }
                const std::vector<StandInCall> panel = calls(sp, 0x3E0C20u);
                if (g.group == 15) {
                    REQUIRE(panel.size() == 1u);
                    CHECK(panel[0].args[1] == 2u);
                    CHECK(panel[0].args[2] == (dir ? 2u : 0u));
                } else {
                    CHECK(panel.empty());
                }
            }
        }
    }
    // an unknown group: no element started, no call
    for (const u32 group : {0u, 3u, 17u}) {
        const SiPair sp = run_case_w(m, base, kCases, "sub_4072D0", {kList, group, 0, 0}, ++seed, [&](Machine& mm) {
            std::memset(mm.at(kList), 0, 0x300);
            w32(mm, kList + game::sw2::kBookListWork, kWork);
            w32(mm, kWork + game::sw2::kBookScreen, kScreen);
            w32(mm, kScreen + game::sw2::kBookSetA, set);
            w32(mm, kScreen + game::sw2::kBookSetB, set);
        }, record_panel);
        CHECK(sp.recomp->si.log.empty());
    }
}

// --- end of the sweep2 cases ---

#else

TEST_CASE("game(sweep2 fcl): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
