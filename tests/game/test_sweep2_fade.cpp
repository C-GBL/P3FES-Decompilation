// Pair tests of slice sweep2, group fade (game/src/sweep/sweep2_fade.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the battle snapshot b_5800 (its gBtl and real units): kind 7's unit marks under the selector, kind 1's phase-0
//     colour and light position, kind 5's colour-scale envelope (phases 0 / 1 / 2, the saved start value), kind 12's
//     screen fade request / reset (h_fade.c's record), kinds 8 / 9 / 11 outside their window.
#include "sweep2_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s2t;

namespace p3fes::recomp_gen {
void fn_sub_352F70_00352f70(EEContext&);  // generated body
void fn_sub_352F70_00352f70__recomp(EEContext&);  // recompiled
void fn_sub_3556D0_003556d0(EEContext&);  // generated body
void fn_sub_3556D0_003556d0__recomp(EEContext&);  // recompiled
void fn_sub_3569E0_003569e0(EEContext&);  // generated body
void fn_sub_3569E0_003569e0__recomp(EEContext&);  // recompiled
void fn_sub_356C70_00356c70(EEContext&);  // generated body
void fn_sub_356C70_00356c70__recomp(EEContext&);  // recompiled
void fn_sub_3571C0_003571c0(EEContext&);  // generated body
void fn_sub_3571C0_003571c0__recomp(EEContext&);  // recompiled
void fn_sub_357550_00357550(EEContext&);  // generated body
void fn_sub_357550_00357550__recomp(EEContext&);  // recompiled
void fn_sub_357710_00357710(EEContext&);  // generated body
void fn_sub_357710_00357710__recomp(EEContext&);  // recompiled
void fn_sub_357730_00357730(EEContext&);  // generated body
void fn_sub_357730_00357730__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_352F70", 0x352F70, &recomp_gen::fn_sub_352F70_00352f70, &recomp_gen::fn_sub_352F70_00352f70__recomp},
    {"sub_3556D0", 0x3556D0, &recomp_gen::fn_sub_3556D0_003556d0, &recomp_gen::fn_sub_3556D0_003556d0__recomp},
    {"sub_3569E0", 0x3569E0, &recomp_gen::fn_sub_3569E0_003569e0, &recomp_gen::fn_sub_3569E0_003569e0__recomp},
    {"sub_356C70", 0x356C70, &recomp_gen::fn_sub_356C70_00356c70, &recomp_gen::fn_sub_356C70_00356c70__recomp},
    {"sub_3571C0", 0x3571C0, &recomp_gen::fn_sub_3571C0_003571c0, &recomp_gen::fn_sub_3571C0_003571c0__recomp},
    {"sub_357550", 0x357550, &recomp_gen::fn_sub_357550_00357550, &recomp_gen::fn_sub_357550_00357550__recomp},
    {"sub_357710", 0x357710, &recomp_gen::fn_sub_357710_00357710, &recomp_gen::fn_sub_357710_00357710__recomp},
    {"sub_357730", 0x357730, &recomp_gen::fn_sub_357730_00357730, &recomp_gen::fn_sub_357730_00357730__recomp},
};

}  // namespace

TEST_CASE("game(sweep2 fade): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep2 cases (real data and documented rules) ---

namespace {

constexpr u32 kInst = kScratch;            // a hand-built class-31 instance (script4_fx.h FxC31Inst)
constexpr u32 kParams = kScratch + 0x100;  // its parameters
constexpr u32 kState = kScratch + 0x200;   // its state (a model holder with no model, or kind 5's saved colour)
constexpr u32 kListed = 0x957BD8u;         // fxUnitSelected's listed units (up to the first null)
constexpr u32 kActorA = 0x957BD0u, kActorB = 0x957BD4u;
constexpr u32 kInv255 = 0x7CAE4Cu;         // f32 1/255
constexpr u32 kFadeRecord = 0x7CDE90u;     // h_fade.c's record (sub_103C30 / sub_103CB0)

// The battle units of the snapshot: gBtl's four lists in order.
std::vector<u32> battle_units(Machine& m) {
    std::vector<u32> out;
    const u32 btl = r32(m, s2t::kGBtlSlot);
    if (btl == 0) return out;
    for (u32 i = 0; i < 4; ++i)
        for (u32 u = r32(m, btl + game::sw2::kBtlUnitLists + 8 * i); u != 0 && out.size() < 32; u = r32(m, u + game::sw2::kUnitNext))
            out.push_back(u);
    return out;
}

// The instance at frame `frame` with the parameters at kParams and the state at kState; the selector (params bytes
// 0..3 {mode A, mode B, list mask, all}) picks `listed[i]` when mask bit i is set.
void put_instance(Machine& m, u32 frame, const std::vector<u32>& listed, u8 mask, u8 all) {
    std::memset(m.at(kInst), 0, 0x40);
    std::memset(m.at(kParams), 0, 0x80);
    std::memset(m.at(kState), 0, 0x20);
    wf32(m, kInst + 0, 1.5f);
    wf32(m, kInst + 4, -2.0f);
    wf32(m, kInst + 8, 3.25f);
    wf32(m, kInst + 32, 1.0f);
    w32(m, kInst + game::sw2::kC31Frame, frame);
    w32(m, kInst + game::sw2::kC31State, kState);
    w32(m, kInst + game::sw2::kC31Params, kParams);
    w32(m, kActorA, 0);
    w32(m, kActorB, 0);
    for (u32 i = 0; i < 4; ++i) w32(m, kListed + 4 * i, i < listed.size() ? listed[i] : 0u);
    w8(m, kParams + 2, mask);
    w8(m, kParams + 3, all);
}

}  // namespace

// Kind 7's update (sub_3569E0) on the battle snapshot's units: the selector picks the first listed unit only (mask 1)
// or every unit (all); a picked unit whose status record is not dead gets flag +2508 bit 3; the others are untouched.
TEST_CASE("game(sweep2 fade): kind 7 marks the selected units") {
    std::vector<u8> base;
    auto mp = snap_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or battle snapshot");
        return;
    }
    Machine& m = *mp;
    const std::vector<u32> units = battle_units(m);
    REQUIRE(units.size() >= 2);
    for (const u8 all : {u8{0}, u8{1}}) {
        const SiPair sp = run_case_w(m, base, kCases, "sub_3569E0", {kInst, 0, 0, 0}, 700 + all,
                                     [&](Machine& mm) { put_instance(mm, 3, {units[0], units[1]}, 1, all); });
        INFO("all " << int(all));
        for (std::size_t i = 0; i < units.size(); ++i) {
            const u16 before = static_cast<u16>(base[units[i] + game::sw2::kUnitFlags] | (base[units[i] + game::sw2::kUnitFlags + 1] << 8));
            const u16 now = r16(m, units[i] + game::sw2::kUnitFlags);
            const bool picked = all != 0 || i == 0;
            if (!picked)
                CHECK(now == before);
            else
                CHECK((now == before || now == (before | 8u)));  // | 8 unless its status record says dead
            if (picked && r32(m, units[i] + game::sw2::kUnitStatus) == 0) CHECK(now == (before | 8u));
        }
        CHECK(calls(sp, 0x282D40u).empty());  // the motion only at frame 0
    }
}

// Kind 1's update (sub_352F70) at frame 0 with duration 0 (phase 0) and no model: every picked unit's colour +112..+124
// = the parameters' RGBA (+20) x 1/255 and its light position +84..+92 = the instance position; the rest untouched.
TEST_CASE("game(sweep2 fade): kind 1 phase 0 sets the picked units' colour") {
    std::vector<u8> base;
    auto mp = snap_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or battle snapshot");
        return;
    }
    Machine& m = *mp;
    const std::vector<u32> units = battle_units(m);
    REQUIRE(units.size() >= 2);
    const u8 rgba[4] = {0x10, 0x80, 0xFF, 0x40};
    run_case_w(m, base, kCases, "sub_352F70", {kInst, 0, 0, 0}, 710, [&](Machine& mm) {
        put_instance(mm, 0, {units[0]}, 1, 0);
        for (u32 k = 0; k < 4; ++k) w8(mm, kParams + 20 + k, rgba[k]);
    });
    const f32 inv = rf32(m, kInv255);
    for (u32 k = 0; k < 4; ++k) CHECK(rf32(m, units[0] + 112 + 4 * k) == static_cast<f32>(rgba[k]) * inv);
    CHECK(rf32(m, units[0] + 84) == 1.5f);
    CHECK(rf32(m, units[0] + 88) == -2.0f);
    CHECK(rf32(m, units[0] + 92) == 3.25f);
    CHECK(std::memcmp(m.at(units[1] + 84), base.data() + units[1] + 84, 44) == 0);
}

// Kind 5's update (sub_3556D0): the scene colour scale gBtl +548 follows the fade envelope of script4_fx.h -- phase 0
// sets the target at frame 0; phase 1 reaches the target exactly at frame = fade-in (at once when fade-in is 0; it
// saves the current value at frame 0); phase 2's last frame (frame = duration) leaves the scene's own colour 0x7CCA38..0x7CCA3A; alpha is 1.
TEST_CASE("game(sweep2 fade): kind 5 colour-scale envelope") {
    std::vector<u8> base;
    auto mp = snap_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or battle snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 btl = r32(m, s2t::kGBtlSlot);
    REQUIRE(btl != 0u);
    const u32 vec = btl + 548;
    const f32 inv = rf32(m, kInv255);
    const u8 rgba[4] = {0x40, 0xC0, 0x20, 0xFF};
    struct Step {
        u32 duration, fade_in, fade_out, frame;
        int expect;  // 0 the target, 1 the scene's own colour
    };
    const Step steps[] = {{0, 0, 0, 0, 0}, {20, 10, 5, 10, 0}, {20, 10, 5, 20, 1}, {20, 0, 5, 0, 0}};
    u32 seed = 720;
    for (const Step& st : steps) {
        run_case_w(m, base, kCases, "sub_3556D0", {kInst, 0, 0, 0}, ++seed, [&](Machine& mm) {
            put_instance(mm, st.frame, {}, 0, 0);
            w32(mm, kParams + 0, st.duration);
            w16(mm, kParams + 4, static_cast<u16>(st.fade_in));
            w16(mm, kParams + 6, static_cast<u16>(st.fade_out));
            for (u32 k = 0; k < 4; ++k) w8(mm, kParams + 8 + k, rgba[k]);
        });
        INFO("duration " << st.duration << " frame " << st.frame);
        for (u32 k = 0; k < 3; ++k) {
            const u8 byte = st.expect == 0 ? rgba[k] : base[0x7CCA38u + k];
            CHECK(rf32(m, vec + 4 * k) == doctest::Approx(static_cast<f32>(byte) * inv).epsilon(1e-6));
        }
        CHECK(rf32(m, vec + 12) == 1.0f);
    }
    // phase 1 at frame 0 saves the scale it starts from into the state
    run_case_w(m, base, kCases, "sub_3556D0", {kInst, 0, 0, 0}, 730, [&](Machine& mm) {
        put_instance(mm, 0, {}, 0, 0);
        w32(mm, kParams + 0, 20);
        w16(mm, kParams + 4, 10);
    });
    CHECK(std::memcmp(m.at(kState), base.data() + vec, 16) == 0);
}

// Kind 12 (h_fade.c): the update requests the screen fade at frame 0 only, with the parameters' four halves, when
// option flag 387 is set (its result, sub_103C30's datGetFlag(387), is the update's $v0); the destroy resets the record.
TEST_CASE("game(sweep2 fade): kind 12 screen fade request and reset") {
    std::vector<u8> base;
    auto mp = snap_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or battle snapshot");
        return;
    }
    Machine& m = *mp;
    for (const u32 frame : {0u, 4u}) {
        const SiPair sp = run_case_w(m, base, kCases, "sub_357730", {kInst, 0, 0, 0}, 740 + frame, [&](Machine& mm) {
            put_instance(mm, frame, {}, 0, 0);
            w16(mm, kParams + 0, 0x11);
            w16(mm, kParams + 4, 0x22);
            w16(mm, kParams + 8, 0x33);
            w16(mm, kParams + 12, 0x44);
        });
        INFO("frame " << frame);
        const bool requested = frame == 0 && v0_of(sp.hw) == 1;
        if (requested) {
            CHECK(r16(m, kFadeRecord + 0) == 2u);
            CHECK(r16(m, kFadeRecord + 0x18) == 0x11u);  // 0x7CDEA8 <- params +0
            CHECK(r16(m, kFadeRecord + 0x04) == 0x22u);  // 0x7CDE94 <- params +4
            CHECK(r16(m, kFadeRecord + 0x10) == 0x33u);  // 0x7CDEA0 <- params +8
            CHECK(r16(m, kFadeRecord + 0x0C) == 0x44u);  // 0x7CDE9C <- params +12
            CHECK(r16(m, kFadeRecord + 0x08) == 0u);
            CHECK(r16(m, kFadeRecord + 0x14) == 0u);
        } else {
            CHECK(std::memcmp(m.at(kFadeRecord), base.data() + kFadeRecord, 0x1A) == 0);
        }
    }
    run_case_w(m, base, kCases, "sub_357710", {kState, 0, 0, 0}, 750, [&](Machine& mm) {
        for (u32 i = 0; i < 0x1A; i += 2) w16(mm, kFadeRecord + i, static_cast<u16>(0x100 + i));
        w16(mm, 0x7E09DEu, 5);
        w16(mm, 0x7E09E0u, 6);
    });
    CHECK(r16(m, kFadeRecord) == 1u);
    for (const u32 off : {0x04u, 0x08u, 0x0Cu, 0x10u, 0x14u, 0x18u}) CHECK(r16(m, kFadeRecord + off) == 0u);
    CHECK(r16(m, 0x7E09DEu) == 0u);
    CHECK(r16(m, 0x7E09E0u) == 0u);
}

// Outside their duration the model kinds 8 / 9 do nothing, and kind 11 does nothing after frame 0: no call, no unit
// touched. At frame 0 kind 11 sets the camera shot by params +0 (pairs only: the camera is hand-written code).
TEST_CASE("game(sweep2 fade): kinds 8 / 9 / 11 outside their window") {
    std::vector<u8> base;
    auto mp = snap_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or battle snapshot");
        return;
    }
    Machine& m = *mp;
    const std::vector<u32> units = battle_units(m);
    struct K {
        const char* fn;
        u32 dur_off;
    };
    u32 seed = 760;
    for (const K k : {K{"sub_356C70", 4}, K{"sub_3571C0", 44}}) {
        const SiPair sp = run_case_w(m, base, kCases, k.fn, {kInst, 0, 0, 0}, ++seed, [&](Machine& mm) {
            put_instance(mm, 9, units, 0, 1);
            w32(mm, kParams + k.dur_off, 8);  // frame 9 > duration 8
        });
        INFO(k.fn);
        CHECK(sp.recomp->si.log.empty());
        for (u32 u : units) CHECK(std::memcmp(m.at(u), base.data() + u, 2640) == 0);
    }
    for (const u32 shot : {0u, 1u, 2u}) {
        for (const u32 frame : {0u, 1u}) {
            const SiPair sp = run_case_w(m, base, kCases, "sub_357550", {kInst, 0, 0, 0}, ++seed, [&](Machine& mm) {
                put_instance(mm, frame, {}, 0, 0);
                w32(mm, kParams + 0, shot);
            });
            if (frame != 0) {
                CHECK(sp.recomp->si.log.empty());
                for (u32 u : units) CHECK(std::memcmp(m.at(u), base.data() + u, 2640) == 0);
            }
        }
    }
}

// --- end of the sweep2 cases ---

#else

TEST_CASE("game(sweep2 fade): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
