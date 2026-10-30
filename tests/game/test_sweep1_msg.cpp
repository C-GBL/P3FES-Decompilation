// Pair tests of slice sweep1, group msg (game/src/sweep/sweep1_msg.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the dorm snapshot's message slots through a script task: the MSG COMM handlers' busy-byte protocol;
//   * hand-built tag contexts: the BMD tag argument decoding of the scene / call tags and the voice path.
#include "sweep1_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_3A0220_003a0220(EEContext&);  // generated body
void fn_sub_3A0220_003a0220__recomp(EEContext&);  // recompiled
void fn_sub_3A05B0_003a05b0(EEContext&);  // generated body
void fn_sub_3A05B0_003a05b0__recomp(EEContext&);  // recompiled
void fn_sub_3A0960_003a0960(EEContext&);  // generated body
void fn_sub_3A0960_003a0960__recomp(EEContext&);  // recompiled
void fn_sub_3A0E90_003a0e90(EEContext&);  // generated body
void fn_sub_3A0E90_003a0e90__recomp(EEContext&);  // recompiled
void fn_sub_3A1F30_003a1f30(EEContext&);  // generated body
void fn_sub_3A1F30_003a1f30__recomp(EEContext&);  // recompiled
void fn_scrCommand_MSG_003a2150(EEContext&);  // generated body
void fn_scrCommand_MSG_003a2150__recomp(EEContext&);  // recompiled
void fn_sub_3A2260_003a2260(EEContext&);  // generated body
void fn_sub_3A2260_003a2260__recomp(EEContext&);  // recompiled
void fn_sub_3A2440_003a2440(EEContext&);  // generated body
void fn_sub_3A2440_003a2440__recomp(EEContext&);  // recompiled
void fn_itfMesMngCreateHandle_003a2ef0(EEContext&);  // generated body
void fn_itfMesMngCreateHandle_003a2ef0__recomp(EEContext&);  // recompiled
void fn_sub_3A7120_003a7120(EEContext&);  // generated body
void fn_sub_3A7120_003a7120__recomp(EEContext&);  // recompiled
void fn_sub_3A7490_003a7490(EEContext&);  // generated body
void fn_sub_3A7490_003a7490__recomp(EEContext&);  // recompiled
void fn_sub_3A7A40_003a7a40(EEContext&);  // generated body
void fn_sub_3A7A40_003a7a40__recomp(EEContext&);  // recompiled
void fn_sub_3AA720_003aa720(EEContext&);  // generated body
void fn_sub_3AA720_003aa720__recomp(EEContext&);  // recompiled
void fn_sub_3AAAE0_003aaae0(EEContext&);  // generated body
void fn_sub_3AAAE0_003aaae0__recomp(EEContext&);  // recompiled
void fn_sub_3AB320_003ab320(EEContext&);  // generated body
void fn_sub_3AB320_003ab320__recomp(EEContext&);  // recompiled
void fn_sub_3ABB10_003abb10(EEContext&);  // generated body
void fn_sub_3ABB10_003abb10__recomp(EEContext&);  // recompiled
void fn_sub_3ACBC0_003acbc0(EEContext&);  // generated body
void fn_sub_3ACBC0_003acbc0__recomp(EEContext&);  // recompiled
void fn_sub_3ACE60_003ace60(EEContext&);  // generated body
void fn_sub_3ACE60_003ace60__recomp(EEContext&);  // recompiled
void fn_sub_3ADB80_003adb80(EEContext&);  // generated body
void fn_sub_3ADB80_003adb80__recomp(EEContext&);  // recompiled
void fn_sub_3ADD40_003add40(EEContext&);  // generated body
void fn_sub_3ADD40_003add40__recomp(EEContext&);  // recompiled
void fn_sub_3AEA50_003aea50(EEContext&);  // generated body
void fn_sub_3AEA50_003aea50__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_3A0220", 0x3A0220, &recomp_gen::fn_sub_3A0220_003a0220, &recomp_gen::fn_sub_3A0220_003a0220__recomp},
    {"sub_3A05B0", 0x3A05B0, &recomp_gen::fn_sub_3A05B0_003a05b0, &recomp_gen::fn_sub_3A05B0_003a05b0__recomp},
    {"sub_3A0960", 0x3A0960, &recomp_gen::fn_sub_3A0960_003a0960, &recomp_gen::fn_sub_3A0960_003a0960__recomp},
    {"sub_3A0E90", 0x3A0E90, &recomp_gen::fn_sub_3A0E90_003a0e90, &recomp_gen::fn_sub_3A0E90_003a0e90__recomp},
    {"sub_3A1F30", 0x3A1F30, &recomp_gen::fn_sub_3A1F30_003a1f30, &recomp_gen::fn_sub_3A1F30_003a1f30__recomp},
    {"scrCommand_MSG", 0x3A2150, &recomp_gen::fn_scrCommand_MSG_003a2150, &recomp_gen::fn_scrCommand_MSG_003a2150__recomp},
    {"sub_3A2260", 0x3A2260, &recomp_gen::fn_sub_3A2260_003a2260, &recomp_gen::fn_sub_3A2260_003a2260__recomp},
    {"sub_3A2440", 0x3A2440, &recomp_gen::fn_sub_3A2440_003a2440, &recomp_gen::fn_sub_3A2440_003a2440__recomp},
    {"itfMesMngCreateHandle", 0x3A2EF0, &recomp_gen::fn_itfMesMngCreateHandle_003a2ef0, &recomp_gen::fn_itfMesMngCreateHandle_003a2ef0__recomp},
    {"sub_3A7120", 0x3A7120, &recomp_gen::fn_sub_3A7120_003a7120, &recomp_gen::fn_sub_3A7120_003a7120__recomp},
    {"sub_3A7490", 0x3A7490, &recomp_gen::fn_sub_3A7490_003a7490, &recomp_gen::fn_sub_3A7490_003a7490__recomp},
    {"sub_3A7A40", 0x3A7A40, &recomp_gen::fn_sub_3A7A40_003a7a40, &recomp_gen::fn_sub_3A7A40_003a7a40__recomp},
    {"sub_3AA720", 0x3AA720, &recomp_gen::fn_sub_3AA720_003aa720, &recomp_gen::fn_sub_3AA720_003aa720__recomp},
    {"sub_3AAAE0", 0x3AAAE0, &recomp_gen::fn_sub_3AAAE0_003aaae0, &recomp_gen::fn_sub_3AAAE0_003aaae0__recomp},
    {"sub_3AB320", 0x3AB320, &recomp_gen::fn_sub_3AB320_003ab320, &recomp_gen::fn_sub_3AB320_003ab320__recomp},
    {"sub_3ABB10", 0x3ABB10, &recomp_gen::fn_sub_3ABB10_003abb10, &recomp_gen::fn_sub_3ABB10_003abb10__recomp},
    {"sub_3ACBC0", 0x3ACBC0, &recomp_gen::fn_sub_3ACBC0_003acbc0, &recomp_gen::fn_sub_3ACBC0_003acbc0__recomp},
    {"sub_3ACE60", 0x3ACE60, &recomp_gen::fn_sub_3ACE60_003ace60, &recomp_gen::fn_sub_3ACE60_003ace60__recomp},
    {"sub_3ADB80", 0x3ADB80, &recomp_gen::fn_sub_3ADB80_003adb80, &recomp_gen::fn_sub_3ADB80_003adb80__recomp},
    {"sub_3ADD40", 0x3ADD40, &recomp_gen::fn_sub_3ADD40_003add40, &recomp_gen::fn_sub_3ADD40_003add40__recomp},
    {"sub_3AEA50", 0x3AEA50, &recomp_gen::fn_sub_3AEA50_003aea50, &recomp_gen::fn_sub_3AEA50_003aea50__recomp},
};

}  // namespace

TEST_CASE("game(sweep1 msg): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep1 cases (real data and documented rules) ---

namespace {

constexpr u32 kSlotHandles = 0x959EECu;  // the message manager's slots: the current handle of slot h at + 52 h (msg2.h)
constexpr u32 kTag = kScratch + 0x400;   // a tag context: +16 the argument base, +24 the offset
constexpr u32 kTagArgs = kScratch + 0x500;

// The BMD tag argument encoding: argument k is the bytes {lo + 1, hi + 1}, hi byte 255 meaning 0.
void put_tag_args(Machine& m, const std::vector<u16>& args) {
    std::memset(m.at(kTag), 0, 32);
    w32(m, kTag + 16, kTagArgs);
    w32(m, kTag + 24, 0);
    for (std::size_t k = 0; k < args.size(); ++k) {
        const u8 lo = static_cast<u8>(args[k] & 0xFF), hi = static_cast<u8>(args[k] >> 8);
        w8(m, kTagArgs + static_cast<u32>(2 * k), static_cast<u8>(lo + 1));
        w8(m, kTagArgs + static_cast<u32>(2 * k + 1), hi == 0 ? 255 : static_cast<u8>(hi + 1));
    }
}

}  // namespace

// COMM 0 (MSG) and its two siblings on the dorm snapshot's message slots, through a script task: no slot -> done; a
// shown message (busy +52 > 0) keeps the script waiting; a finished one (busy < 0) is cleared and done; an idle handle
// gets the request.
TEST_CASE("game(sweep1 msg): the MSG COMM handlers' busy-byte protocol (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    namespace mes = game::sw1::mes;
    u32 slot = 0xFFFFFFFFu, handle = 0;
    for (u32 h = 0; h < 16; ++h)
        if (r32(m, kSlotHandles + 52 * h) != 0) {
            slot = h;
            handle = r32(m, kSlotHandles + 52 * h);
            break;
        }
    if (slot == 0xFFFFFFFFu) {
        MESSAGE("SKIP: no message slot with a handle in the snapshot");
        return;
    }
    for (const char* fn : {"scrCommand_MSG", "sub_3A2440"}) {
        INFO(fn);
        for (const u8 busy : {u8{1}, u8{0xFF}, u8{0xFE}}) {
            SiPair sp = run_case(m, base, kCases, fn, {0, 0, 0, 0}, 1 + busy, [&](Machine& mm) {
                set_comm_args(mm, {57});
                w32(mm, kScrTask + game::scr::kMessageId, slot);
                w8(mm, handle + mes::kBusy, busy);
            });
            if (busy == 1) {
                CHECK(v0_of(sp.hw) == 0);
                CHECK(r8(m, handle + mes::kBusy) == 1u);
            } else {
                CHECK(v0_of(sp.hw) == 1);
                CHECK(r8(m, handle + mes::kBusy) == 0u);
            }
        }
        // no slot: done at once
        SiPair sp = run_case(m, base, kCases, fn, {0, 0, 0, 0}, 9, [&](Machine& mm) {
            set_comm_args(mm, {57});
            w32(mm, kScrTask + game::scr::kMessageId, 0xFFFFFFFFu);
        });
        CHECK(v0_of(sp.hw) == 1);
        // idle: the request (whatever it answers, the pair decides; a stood-in request logs the message id 57)
        sp = run_case(m, base, kCases, fn, {0, 0, 0, 0}, 10, [&](Machine& mm) {
            set_comm_args(mm, {57});
            w32(mm, kScrTask + game::scr::kMessageId, slot);
            w8(mm, handle + mes::kBusy, 0);
        });
        for (const StandInCall& c : calls(sp, 0x3A30C0u)) {
            CHECK(static_cast<u32>(c.args[0]) == slot);
            CHECK(static_cast<u32>(c.args[1]) == 57u);
        }
    }
}

// The tag handlers decode their arguments as documented: the scene calls receive arg2 | arg0 << 16 | arg1 << 8 (with
// 0x300 / 0x200 by arg3 for sub_3ADB80) and sub_3B93C0 the five arguments in $a0..$t0.
TEST_CASE("game(sweep1 msg): the message tag handlers decode their arguments") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const std::vector<std::vector<u16>> sets = {{1, 2, 3, 0, 0}, {0x12, 0x34, 0x56, 7, 9}, {200, 0, 17, 0, 1}};
    u32 seed = 1;
    for (const std::vector<u16>& a : sets) {
        // the scene calls (sub_3CF160, hand-written since finalB) and sub_3B93C0 are recorded from the start
        SiPair sp = run_case(m, base, kCases, "sub_3ADD40", {0, kTag, 0, 0}, seed++, [&](Machine& mm) { put_tag_args(mm, a); }, 0, {}, {0x3CF160u});
        std::vector<StandInCall> c = calls(sp, 0x3CF160u);
        REQUIRE(c.size() == 1u);
        const u32 want = static_cast<u32>(a[2]) | (static_cast<u32>(a[0]) << 16) | (static_cast<u32>(a[1]) << 8);
        CHECK(static_cast<u32>(c[0].args[0]) == want);
        CHECK(c[0].args[1] == 0u);
        sp = run_case(m, base, kCases, "sub_3ADB80", {0, kTag, 0, 0}, seed++, [&](Machine& mm) { put_tag_args(mm, a); }, 0, {}, {0x3CF160u});
        c = calls(sp, 0x3CF160u);
        REQUIRE(c.size() == 1u);
        CHECK(static_cast<u32>(c[0].args[0]) == want);
        CHECK(static_cast<u32>(c[0].args[1]) == (a[3] == 0 ? 0x300u : 0x200u));
        sp = run_case(m, base, kCases, "sub_3AEA50", {0, kTag, 0, 0}, seed++, [&](Machine& mm) { put_tag_args(mm, a); }, 0, {}, {0x3B93C0u});
        c = calls(sp, 0x3B93C0u);
        REQUIRE(c.size() == 1u);
        for (int k = 0; k < 5; ++k) CHECK(static_cast<u16>(c[0].args[static_cast<std::size_t>(k)]) == a[static_cast<std::size_t>(k)]);
    }
}

// The voice tag: with flag 388 the path "sound/voice_e%03d_%03d/%03d_%03d%05d.adx" (major <= 400) or the "_%04d" form
// with minor / 20 in the directory (401..500) goes to channel 2; without the flag nothing.
TEST_CASE("game(sweep1 msg): the voice tag builds the voice path") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    for (const std::vector<u16>& a : std::vector<std::vector<u16>>{{100, 5, 12}, {399, 1, 7}, {450, 41, 3}}) {
        SiPair sp = run_case(m, base, kCases, "sub_3ACBC0", {0, kTag, 0, 0}, seed++, [&](Machine& mm) { put_tag_args(mm, a); },
                             0, {}, {0x10A370u});  // the voice play: hand-written since sweep5, recorded as before
        const std::vector<StandInCall> fmt = calls(sp, kSprintf);  // the path as the sprintf stand-in formatted it
        for (const StandInCall& c : calls(sp, 0x10A370u)) {
            char want[96];
            if (a[0] <= 400) std::snprintf(want, sizeof want, "sound/voice_e%03d_%03d/%03d_%03d%05d.adx", a[0], a[1], a[0], a[1], a[2]);
            else std::snprintf(want, sizeof want, "sound/voice_e%03d_%03d/%03d_%03d_%04d.adx", a[0], a[1] / 20, a[0], a[1], a[2]);
            CHECK(c.args[0] == 2u);
            REQUIRE(fmt.size() == 1u);
            CHECK(fmt[0].text == want);
            CHECK(c.args[1] == fmt[0].args[0]);
        }
    }
}

// --- end of the sweep1 cases ---

#else

TEST_CASE("game(sweep1 msg): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
