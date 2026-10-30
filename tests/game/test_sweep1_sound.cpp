// Pair tests of slice sweep1, group sound (game/src/sweep/sweep1_sound.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the dorm snapshot: the h_sndcom slot rules (idle = state 1; the two bank requests touch only an idle slot), the
//     SE-bank request steps and request, the ADX channel start / stop with the CRI ADXT thunks recorded (the in-memory
//     play sets the record and calls the channel start), the H_SfdPlay task creator's work.
#include "sweep1_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_108740_00108740(EEContext&);  // generated body
void fn_sub_108740_00108740__recomp(EEContext&);  // recompiled
void fn_sub_108E80_00108e80(EEContext&);  // generated body
void fn_sub_108E80_00108e80__recomp(EEContext&);  // recompiled
void fn_sub_109070_00109070(EEContext&);  // generated body
void fn_sub_109070_00109070__recomp(EEContext&);  // recompiled
void fn_sub_109CA0_00109ca0(EEContext&);  // generated body
void fn_sub_109CA0_00109ca0__recomp(EEContext&);  // recompiled
void fn_sub_109E30_00109e30(EEContext&);  // generated body
void fn_sub_109E30_00109e30__recomp(EEContext&);  // recompiled
void fn_sub_10A2E0_0010a2e0(EEContext&);  // generated body
void fn_sub_10A2E0_0010a2e0__recomp(EEContext&);  // recompiled
void fn_sub_10A5A0_0010a5a0(EEContext&);  // generated body
void fn_sub_10A5A0_0010a5a0__recomp(EEContext&);  // recompiled
void fn_sub_10BB00_0010bb00(EEContext&);  // generated body
void fn_sub_10BB00_0010bb00__recomp(EEContext&);  // recompiled
void fn_sub_10BCE0_0010bce0(EEContext&);  // generated body
void fn_sub_10BCE0_0010bce0__recomp(EEContext&);  // recompiled
void fn_sub_10BE60_0010be60(EEContext&);  // generated body
void fn_sub_10BE60_0010be60__recomp(EEContext&);  // recompiled
void fn_sub_10D6F0_0010d6f0(EEContext&);  // generated body
void fn_sub_10D6F0_0010d6f0__recomp(EEContext&);  // recompiled
void fn_sub_10D7B0_0010d7b0(EEContext&);  // generated body
void fn_sub_10D7B0_0010d7b0__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_IsChannelPlaying_0010d910(EEContext&);  // generated body
void fn_H_Sndcom_IsChannelPlaying_0010d910__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_108740", 0x108740, &recomp_gen::fn_sub_108740_00108740, &recomp_gen::fn_sub_108740_00108740__recomp},
    {"sub_108E80", 0x108E80, &recomp_gen::fn_sub_108E80_00108e80, &recomp_gen::fn_sub_108E80_00108e80__recomp},
    {"sub_109070", 0x109070, &recomp_gen::fn_sub_109070_00109070, &recomp_gen::fn_sub_109070_00109070__recomp},
    {"sub_109CA0", 0x109CA0, &recomp_gen::fn_sub_109CA0_00109ca0, &recomp_gen::fn_sub_109CA0_00109ca0__recomp},
    {"sub_109E30", 0x109E30, &recomp_gen::fn_sub_109E30_00109e30, &recomp_gen::fn_sub_109E30_00109e30__recomp},
    {"sub_10A2E0", 0x10A2E0, &recomp_gen::fn_sub_10A2E0_0010a2e0, &recomp_gen::fn_sub_10A2E0_0010a2e0__recomp},
    {"sub_10A5A0", 0x10A5A0, &recomp_gen::fn_sub_10A5A0_0010a5a0, &recomp_gen::fn_sub_10A5A0_0010a5a0__recomp},
    {"sub_10BB00", 0x10BB00, &recomp_gen::fn_sub_10BB00_0010bb00, &recomp_gen::fn_sub_10BB00_0010bb00__recomp},
    {"sub_10BCE0", 0x10BCE0, &recomp_gen::fn_sub_10BCE0_0010bce0, &recomp_gen::fn_sub_10BCE0_0010bce0__recomp},
    {"sub_10BE60", 0x10BE60, &recomp_gen::fn_sub_10BE60_0010be60, &recomp_gen::fn_sub_10BE60_0010be60__recomp},
    {"sub_10D6F0", 0x10D6F0, &recomp_gen::fn_sub_10D6F0_0010d6f0, &recomp_gen::fn_sub_10D6F0_0010d6f0__recomp},
    {"sub_10D7B0", 0x10D7B0, &recomp_gen::fn_sub_10D7B0_0010d7b0, &recomp_gen::fn_sub_10D7B0_0010d7b0__recomp},
    {"H_Sndcom_IsChannelPlaying", 0x10D910, &recomp_gen::fn_H_Sndcom_IsChannelPlaying_0010d910, &recomp_gen::fn_H_Sndcom_IsChannelPlaying_0010d910__recomp},
};

}  // namespace

TEST_CASE("game(sweep1 sound): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep1 cases (real data and documented rules) ---

namespace {

constexpr u32 kChannels = 0x7E4430u;  // 16 ADX channel records, 308 bytes (font2.h snd)
constexpr u32 kChSize = 308;
constexpr u32 kSeReq = 0x7E5770u;     // six 40-byte SE-bank requests
constexpr u32 kSlots = 0x833710u;     // h_sndcom slots, 68 bytes
constexpr u32 kReq = kScratch + 0x200;

}  // namespace

// The h_sndcom slot rules on the dorm snapshot: "is idle" is state == 1 for every slot; the two bank requests only
// touch an idle slot (bank id +8, state 2 by id or 8 from buffers with the three sources and sizes).
TEST_CASE("game(sweep1 sound): h_sndcom slot requests and the idle test (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    for (u32 slot = 0; slot < 8; ++slot) {
        for (const u16 state : {0, 1, 2, 8}) {
            SiPair sp = run_case(m, base, kCases, "H_Sndcom_IsChannelPlaying", {slot, 0, 0, 0}, 1 + slot,
                                 [&](Machine& mm) { w16(mm, kSlots + 68 * slot, state); });
            CHECK(v0_of(sp.hw) == (state == 1 ? 1 : 0));
        }
    }
    for (const u16 state : {1, 3}) {
        // by id: bound slots are unbound first (a recorder stands in for H_Sndcom_UnbindSfx)
        SiPair sp = run_case(m, base, kCases, "sub_10D6F0", {2, 77, 0, 0}, 10, [&](Machine& mm) {
            w16(mm, kSlots + 68 * 2, state);
            w32(mm, kSlots + 68 * 2 + 24, 1);
        });
        CHECK(r16(m, kSlots + 68 * 2) == (state == 1 ? 2u : 3u));
        if (state == 1) CHECK(r16(m, kSlots + 68 * 2 + 8) == 77u);
        // from buffers: eight register arguments
        sp = run_case(m, base, kCases, "sub_10D7B0", {3, 55, 0x1000, 0x10}, 11, [&](Machine& mm) {
            w16(mm, kSlots + 68 * 3, state);
            w32(mm, kSlots + 68 * 3 + 24, 0);
        }, 0, {{8u, 0x2000}, {9u, 0x20}, {10u, 0x3000}, {11u, 0x30}});
        if (state == 1) {
            CHECK(r16(m, kSlots + 68 * 3) == 8u);
            CHECK(r16(m, kSlots + 68 * 3 + 8) == 55u);
            CHECK(r32(m, kSlots + 68 * 3 + 52) == 0x1000u);
            CHECK(r32(m, kSlots + 68 * 3 + 56) == 0x2000u);
            CHECK(r32(m, kSlots + 68 * 3 + 60) == 0x3000u);
            CHECK(r32(m, kSlots + 68 * 3 + 32) == 0x10u);
            CHECK(r32(m, kSlots + 68 * 3 + 40) == 0x20u);
            CHECK(r32(m, kSlots + 68 * 3 + 48) == 0x30u);
        } else {
            CHECK(r16(m, kSlots + 68 * 3) == 3u);
        }
    }
}

// The SE-bank request step and request: 0 -> 1, 2 -> 3 through a slot request, 3 -> 1 with bound once the slot is
// idle; the request record of kwlnRootCreateTask.
TEST_CASE("game(sweep1 sound): the SE-bank request step and request") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    namespace sb = game::sw1::sebank;
    struct Step { u16 state; u16 explicit_; u16 slot_state; u16 want; u32 want_bound; };
    for (const Step s : {Step{0, 0, 1, 1, 9}, Step{2, 0, 1, 3, 9}, Step{2, 1, 1, 3, 9}, Step{3, 0, 1, 1, 1},
                         Step{3, 0, 2, 3, 9}, Step{1, 0, 1, 1, 9}}) {
        SiPair sp = run_case(m, base, kCases, "sub_108E80", {kReq, 0, 0, 0}, 1 + s.state, [&](Machine& mm) {
            std::memset(mm.at(kReq), 0, 40);
            w16(mm, kReq + sb::kState, s.state);
            w16(mm, kReq + sb::kBank, 12);
            w16(mm, kReq + sb::kSlot, 4);
            w32(mm, kReq + sb::kBound, 9);
            w16(mm, kReq + sb::kExplicit, s.explicit_);
            w16(mm, kSlots + 68 * 4, s.slot_state);
        });
        INFO("state " << s.state << " explicit " << s.explicit_ << " slot " << s.slot_state);
        CHECK(r16(m, kReq + sb::kState) == s.want);
        CHECK(r32(m, kReq + sb::kBound) == s.want_bound);
        if (s.state == 2) CHECK(r16(m, kSlots + 68 * 4) == (s.explicit_ ? 8u : 2u));
    }
    // the request: record `slot` gets state 2 / bank / slot (whatever sub_109DF0 answers on the snapshot)
    SiPair sp = run_case(m, base, kCases, "sub_109CA0", {1, 33, 0, 0}, 20, [&](Machine& mm) {
        std::memset(mm.at(kSeReq + 40), 0, 40);
    });
    CHECK(v0_of(sp.hw) == 1);
    CHECK(r16(m, kSeReq + 40 + 2) == 33u);
    CHECK(r16(m, kSeReq + 40 + 4) == 1u);
    CHECK(r16(m, kSeReq + 40) == 2u);
}

// The ADX channel helpers with the CRI ADXT thunks stood in by recorders: the in-memory play sets the channel record
// (active, id, data address, start type 5) and calls the channel start; stop / fade-stop clear it.
TEST_CASE("game(sweep1 sound): ADX channel start / stop with the CRI thunks recorded") {
    // the CRI stop thunk atan2l_4 and the handle setter sub_54D220 (hand-written since finalB) recorded from the start
    const std::vector<u32> kCriStops = {0x54D100u, 0x54D220u};
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    for (const u32 ch : {2u, 3u, 4u}) {
        SiPair sp = run_case(m, base, kCases, "sub_10A2E0", {0x01900000u, ch, 321, 0}, 1 + ch, {}, 0, {},
                                 {0x109180u});  // the channel start: hand-written since sweep5, recorded as before
        const u32 rec = kChannels + kChSize * ch;
        CHECK(v0_of(sp.hw) == 1);
        CHECK(r32(m, rec + 0) == 1u);
        CHECK(r16(m, rec + 8) == 321u);
        CHECK(r16(m, rec + 12) == 0u);  // started is set by the channel start (still recompiled: stood in here)
        CHECK(r16(m, rec + game::sw1::sndch::kStartType) == 5u);
        CHECK(r32(m, rec + 0x11C) == 0x01900000u);
        // then the channel start sub_109180(ch) (test_script4 stands it in; recompiled, a recorder here)
        const std::vector<StandInCall> starts = calls(sp, 0x109180u);
        REQUIRE(starts.size() == 1u);
        CHECK(static_cast<u32>(starts[0].args[0]) == ch);
        // stop: the CRI stop, inactive, id -1
        std::vector<u8> playing(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        // (the CRI stop thunk atan2l_4 0x54D100 and the handle setter sub_54D220, hand-written since finalB, are
        // recorded: run for real the thunk reaches the CRI stop's IOP wait)
        sp = run_case(m, playing, kCases, "sub_109070", {ch, 0, 0, 0}, 10 + ch, {}, 0, {}, kCriStops);
        CHECK(v0_of(sp.hw) == 1);
        CHECK(r32(m, rec + 0) == 0u);
        CHECK(r16(m, rec + 8) == 0xFFFFu);
        CHECK(calls(sp, 0x54D100u).size() == 1u);
        sp = run_case(m, playing, kCases, "sub_109E30", {ch, 0, 0, 0}, 20 + ch, {}, 0, {}, kCriStops);
        CHECK(r32(m, rec + 0) == 0u);
        CHECK(calls(sp, 0x54D220u).size() == 1u);
        // an inactive channel: nothing
        sp = run_case(m, base, kCases, "sub_109070", {ch, 0, 0, 0}, 30 + ch, [&](Machine& mm) { w32(mm, rec, 0); }, 0, {}, kCriStops);
        CHECK(calls(sp, 0x54D100u).empty());
    }
}

// The movie task creators on the stand-in heap and kwln kernel: the 544-byte work, its movie id and flags.
TEST_CASE("game(sweep1 sound): the H_SfdPlay task creators") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    namespace sfd = game::sw1::sfd;
    SiPair sp = run_case(m, base, kCases, "sub_10BCE0", {0, 42, 0, 0}, 1);
    const u32 task = static_cast<u32>(v0_of(sp.hw));
    if (task != 0u) {
        const u32 work = r32(m, task + 60);
        CHECK(r32(m, work + sfd::kOwned) == 1u);
        CHECK(r16(m, work + sfd::kMovieId) == 42u);
        CHECK(r32(m, work + sfd::kRestore) == 0u);
    }
}

// --- end of the sweep1 cases ---

#else

TEST_CASE("game(sweep1 sound): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
