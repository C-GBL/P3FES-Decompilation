// Pair tests of slice libs1, libpad's readers (game/src/lib/libs1_pad.cpp), through tests/game/libs1_util.h. The DMA
// frame reader scePadGetDmaStr (interrupt masking and a cache sync in its body: never emitted) is served by a stand-in
// with the retail rule -- the newer of the area's two 128-byte frames by the counter at +88 / +216, copied into the
// caller's buffer, its address returned -- and scePadSetButtonInfo (SIF RPC) by a recorder. Inputs: the dorm replay
// snapshot's port table and DMA area (the pad the routes drive), then built frames over every mode / state byte the
// readers test, each result checked against a host decoder of the frame.
#include "libs1_util.h"

#include "p3fes/game/libs1_pad.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <map>
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

namespace p3fes::recomp_gen {
void fn_scePadGetFrameCount_00511988(EEContext&);  // generated body
void fn_scePadGetFrameCount_00511988__recomp(EEContext&);  // recompiled
void fn_scePadRead_005119e0(EEContext&);  // generated body
void fn_scePadRead_005119e0__recomp(EEContext&);  // recompiled
void fn_scePadGetState_00511a58(EEContext&);  // generated body
void fn_scePadGetState_00511a58__recomp(EEContext&);  // recompiled
void fn_scePadStateIntToStr_00511ad0(EEContext&);  // generated body
void fn_scePadStateIntToStr_00511ad0__recomp(EEContext&);  // recompiled
void fn_scePadGetReqState_00511bc0(EEContext&);  // generated body
void fn_scePadGetReqState_00511bc0__recomp(EEContext&);  // recompiled
void fn_scePadReqIntToStr_00511c18(EEContext&);  // generated body
void fn_scePadReqIntToStr_00511c18__recomp(EEContext&);  // recompiled
void fn_scePadInfoAct_00511c50(EEContext&);  // generated body
void fn_scePadInfoAct_00511c50__recomp(EEContext&);  // recompiled
void fn_scePadInfoComb_00511d68(EEContext&);  // generated body
void fn_scePadInfoComb_00511d68__recomp(EEContext&);  // recompiled
void fn_scePadInfoMode_00511e80(EEContext&);  // generated body
void fn_scePadInfoMode_00511e80__recomp(EEContext&);  // recompiled
void fn_scePadGetButtonMask_00512210(EEContext&);  // generated body
void fn_scePadGetButtonMask_00512210__recomp(EEContext&);  // recompiled
void fn_scePadInfoPressMode_00512370(EEContext&);  // generated body
void fn_scePadInfoPressMode_00512370__recomp(EEContext&);  // recompiled
void fn_scePadEnterPressMode_005123f0(EEContext&);  // generated body
void fn_scePadEnterPressMode_005123f0__recomp(EEContext&);  // recompiled
void fn_scePadExitPressMode_00512448(EEContext&);  // generated body
void fn_scePadExitPressMode_00512448__recomp(EEContext&);  // recompiled
void fn_scePadSetFlushRate_00512838(EEContext&);  // generated body
void fn_scePadSetFlushRate_00512838__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using p3fes::game_test::libs1::Case;

const Case kCases[] = {
    {"scePadGetFrameCount", 0x511988, &recomp_gen::fn_scePadGetFrameCount_00511988, &recomp_gen::fn_scePadGetFrameCount_00511988__recomp},
    {"scePadRead", 0x5119E0, &recomp_gen::fn_scePadRead_005119e0, &recomp_gen::fn_scePadRead_005119e0__recomp},
    {"scePadGetState", 0x511A58, &recomp_gen::fn_scePadGetState_00511a58, &recomp_gen::fn_scePadGetState_00511a58__recomp},
    {"scePadStateIntToStr", 0x511AD0, &recomp_gen::fn_scePadStateIntToStr_00511ad0, &recomp_gen::fn_scePadStateIntToStr_00511ad0__recomp},
    {"scePadGetReqState", 0x511BC0, &recomp_gen::fn_scePadGetReqState_00511bc0, &recomp_gen::fn_scePadGetReqState_00511bc0__recomp},
    {"scePadReqIntToStr", 0x511C18, &recomp_gen::fn_scePadReqIntToStr_00511c18, &recomp_gen::fn_scePadReqIntToStr_00511c18__recomp},
    {"scePadInfoAct", 0x511C50, &recomp_gen::fn_scePadInfoAct_00511c50, &recomp_gen::fn_scePadInfoAct_00511c50__recomp},
    {"scePadInfoComb", 0x511D68, &recomp_gen::fn_scePadInfoComb_00511d68, &recomp_gen::fn_scePadInfoComb_00511d68__recomp},
    {"scePadInfoMode", 0x511E80, &recomp_gen::fn_scePadInfoMode_00511e80, &recomp_gen::fn_scePadInfoMode_00511e80__recomp},
    {"scePadGetButtonMask", 0x512210, &recomp_gen::fn_scePadGetButtonMask_00512210, &recomp_gen::fn_scePadGetButtonMask_00512210__recomp},
    {"scePadInfoPressMode", 0x512370, &recomp_gen::fn_scePadInfoPressMode_00512370, &recomp_gen::fn_scePadInfoPressMode_00512370__recomp},
    {"scePadEnterPressMode", 0x5123F0, &recomp_gen::fn_scePadEnterPressMode_005123f0, &recomp_gen::fn_scePadEnterPressMode_005123f0__recomp},
    {"scePadExitPressMode", 0x512448, &recomp_gen::fn_scePadExitPressMode_00512448, &recomp_gen::fn_scePadExitPressMode_00512448__recomp},
    {"scePadSetFlushRate", 0x512838, &recomp_gen::fn_scePadSetFlushRate_00512838, &recomp_gen::fn_scePadSetFlushRate_00512838__recomp},
};

using namespace p3fes::game_test::libs1;
namespace lp = p3fes::game::libs1::pad;

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kGetDmaStr = 0x511830u, kSetButtonInfo = 0x5122C0u;
constexpr u32 kArea = 0x01830000u;  // a DMA area for built frames (port 1, slot 0)
constexpr u32 kOut = 0x01832000u;

const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }

void stand_ins(StandInWorld& w) {
    w.si.install(kGetDmaStr, "scePadGetDmaStr", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 port = static_cast<u32>(c.args[0]), slot = static_cast<u32>(c.args[1]), buf = static_cast<u32>(c.args[2]);
        const u32 area = gu32(ctx, lp::kPortTable + lp::kPortStride * port + lp::kSlotStride * slot);
        const s32 c0 = static_cast<s32>(gu32(ctx, area + 88)), c1 = static_cast<s32>(gu32(ctx, area + 216));
        const u32 frame = area + (c0 < c1 ? 128u : 0u);
        if (buf) std::memcpy(gptr(ctx, buf), gptr(ctx, frame), 128);
        c.v0 = sx(frame);
    });
    w.si.install_recorder(kSetButtonInfo, "scePadSetButtonInfo", 1);
}

// The frame the readers see (the newer one), as bytes.
std::vector<u8> frame_of(const Machine& m, u32 port, u32 slot) {
    const u32 area = r32(m, lp::kPortTable + lp::kPortStride * port + lp::kSlotStride * slot);
    const u32 f = area + (static_cast<s32>(r32(m, area + 88)) < static_cast<s32>(r32(m, area + 216)) ? 128u : 0u);
    std::vector<u8> v(128);
    for (u32 i = 0; i < 128; ++i) v[i] = r8(m, f + i);
    return v;
}
bool is_open(const Machine& m, u32 port, u32 slot) { return r32(m, lp::kPortTable + lp::kPortStride * port + lp::kSlotStride * slot + lp::kOpen) != 0; }

// Host decoders (from the instructions)
s64 model_state(const Machine& m, u32 p, u32 s) {
    if (!is_open(m, p, s)) return 99;
    const auto f = frame_of(m, p, s);
    if (f[lp::kState] == 6 && f[lp::kReqState] == 2) return 5;
    return f[lp::kState];
}
s64 model_act(const Machine& m, u32 p, u32 s, s64 act, s64 what) {
    if (!is_open(m, p, s)) return 0;
    const auto f = frame_of(m, p, s);
    if (f[lp::kExtMode] != 1 || f[lp::kMode] < 2) return 0;
    if (act >= f[lp::kActCount]) return 0;
    if (act == -1) return f[lp::kActCount];
    if (act < 0) return 0;  // (unreachable: below -1 is "less than the count" but indexes before the table)
    if (what >= 1 && what <= 4) return f[lp::kActTable + 4 * act + (what - 1)];
    return 0;
}
s64 model_comb(const Machine& m, u32 p, u32 s, s64 idx, s64 what) {
    if (!is_open(m, p, s)) return 0;
    const auto f = frame_of(m, p, s);
    if (f[lp::kExtMode] != 1 || f[lp::kMode] < 2) return 0;
    if (idx == -1) return f[lp::kCombCount];
    if (idx >= f[lp::kCombCount]) return 0;
    const s64 k = what == -1 ? 0 : what == 0 ? 1 : what == 1 ? 2 : what == 2 ? 3 : -1;
    return k < 0 ? 0 : f[lp::kCombTable + 4 * idx + k];
}
s64 model_mode(const Machine& m, u32 p, u32 s, s64 term, s64 index) {
    if (!is_open(m, p, s)) return 0;
    const auto f = frame_of(m, p, s);
    if (f[lp::kExtMode] != 1 || f[lp::kReqState] == 2) return 0;
    const bool no_table = f[lp::kMode] == 1;
    auto entry = [&](s64 i) { return static_cast<s64>(f[lp::kModeTable + 2 * i] | f[lp::kModeTable + 2 * i + 1] << 8); };
    switch (term) {
    case 1: return f[lp::kModeCur] == 0xF3 ? 0 : f[lp::kModeCur] >> 4;
    case 2: return no_table ? 0 : entry(f[lp::kModeIndex]);
    case 3: return no_table ? 0 : f[lp::kModeIndex];
    case 4:
        if (no_table) return 0;
        if (index == -1) return f[lp::kModeCount];
        if (index >= f[lp::kModeCount]) return 0;
        return entry(index);
    default: return 0;
    }
}

}  // namespace

TEST_CASE("game(libs1_pad): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, 32, stand_ins);
}

TEST_CASE("game(libs1_pad): the readers on the dorm snapshot's pad and on built frames") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = read_snapshot("dorm_replay_4900");
    if (snap.empty()) {
        MESSAGE("SKIP: dorm_replay_4900 not found");
        return;
    }
    copy_from_snapshot(*m, snap, lp::kPortTable, 0x100);
    const u32 area0 = r32(*m, lp::kPortTable);
    copy_from_snapshot(*m, snap, area0, 0x100);
    REQUIRE(is_open(*m, 0, 0));
    u32 seed = 1;
    // the live pad: what H_Pad_UpdateWorkPad reads every frame
    {
        const auto f = frame_of(*m, 0, 0);
        const auto r = pair(*m, C("scePadRead"), {0, 0, kOut}, seed++, "Read (dorm)", stand_ins);
        CHECK(v0_of(r) == (f[lp::kDataLen] | f[lp::kDataLen + 1] << 8 | f[lp::kDataLen + 2] << 16 | static_cast<u32>(f[lp::kDataLen + 3]) << 24));
        for (u32 i = 0; i < v0_of(r) && i < 32; ++i) CHECK(r8(*m, kOut + i) == f[i]);
        CHECK(v0s(pair(*m, C("scePadGetState"), {0, 0}, seed++, "GetState (dorm)", stand_ins)) == model_state(*m, 0, 0));
        CHECK(v0s(pair(*m, C("scePadGetReqState"), {0, 0}, seed++, "GetReqState (dorm)", stand_ins)) == f[lp::kReqState]);
        CHECK(v0s(pair(*m, C("scePadGetFrameCount"), {0, 0}, seed++, "GetFrameCount (dorm)", stand_ins)) ==
              static_cast<s32>(f[88] | f[89] << 8 | f[90] << 16 | static_cast<u32>(f[91]) << 24));
        for (s64 a : {-1ll, 0ll, 1ll, 2ll})
            for (s64 w : {1ll, 2ll, 3ll, 4ll, 5ll})
                CHECK(v0s(pair(*m, C("scePadInfoAct"), {0, 0, static_cast<u64>(a), static_cast<u64>(w)}, seed++, "InfoAct (dorm)", stand_ins)) == model_act(*m, 0, 0, a, w));
        for (s64 t : {1ll, 2ll, 3ll, 4ll})
            for (s64 i : {-1ll, 0ll, 1ll, 2ll})
                CHECK(v0s(pair(*m, C("scePadInfoMode"), {0, 0, static_cast<u64>(t), static_cast<u64>(i)}, seed++, "InfoMode (dorm)", stand_ins)) == model_mode(*m, 0, 0, t, i));
        MESSAGE("dorm pad: state " << int(f[lp::kState]) << ", request " << int(f[lp::kReqState]) << ", mode " << int(f[lp::kModeCur])
                                   << ", extended " << int(f[lp::kExtMode]) << ", " << v0_of(r) << " data bytes");
    }
    // built frames on port 1 slot 0 (closed first: every reader's "not open" answer)
    w32(*m, lp::kPortTable + lp::kPortStride, kArea);
    w32(*m, lp::kPortTable + lp::kPortStride + lp::kOpen, 0);
    CHECK(v0s(pair(*m, C("scePadGetState"), {1, 0}, seed++, "GetState closed", stand_ins)) == 99);
    CHECK(v0s(pair(*m, C("scePadRead"), {1, 0, kOut}, seed++, "Read closed", stand_ins)) == 0);
    CHECK(v0s(pair(*m, C("scePadEnterPressMode"), {1, 0}, seed++, "EnterPressMode closed", stand_ins)) == 0);
    CHECK(last_log().calls_to(kSetButtonInfo) == 0);
    w32(*m, lp::kPortTable + lp::kPortStride + lp::kOpen, 1);
    std::mt19937 rng{77};
    for (int round = 0; round < 64; ++round) {
        for (u32 i = 0; i < 256; ++i) w8(*m, kArea + i, static_cast<u8>(rng()));
        w32(*m, kArea + 88, rng() % 1000);
        w32(*m, kArea + 216, rng() % 1000);
        for (u32 base : {0u, 128u}) {
            w32(*m, kArea + base + lp::kDataLen, rng() % 33);
            w8(*m, kArea + base + lp::kExtMode, rng() % 3 ? 1 : static_cast<u8>(rng()));
            w8(*m, kArea + base + lp::kMode, static_cast<u8>(rng() % 4));
            w8(*m, kArea + base + lp::kState, static_cast<u8>(rng() % 3 ? 6 : rng() % 8));
            w8(*m, kArea + base + lp::kReqState, static_cast<u8>(rng() % 4));
            w8(*m, kArea + base + lp::kActCount, static_cast<u8>(rng() % 4));
            w8(*m, kArea + base + lp::kCombCount, static_cast<u8>(rng() % 4));
            w8(*m, kArea + base + lp::kModeCount, static_cast<u8>(rng() % 4));
            w8(*m, kArea + base + lp::kModeIndex, static_cast<u8>(rng() % 4));
            w8(*m, kArea + base + lp::kModeCur, static_cast<u8>(rng() % 5 == 0 ? 0xF3 : rng()));
        }
        const std::string tag = " round " + std::to_string(round);
        const auto f = frame_of(*m, 1, 0);
        CHECK(v0s(pair(*m, C("scePadGetState"), {1, 0}, seed++, "GetState" + tag, stand_ins)) == model_state(*m, 1, 0));
        const auto rr = pair(*m, C("scePadRead"), {1, 0, kOut}, seed++, "Read" + tag, stand_ins);
        CHECK(v0_of(rr) == f[lp::kDataLen]);
        for (u32 i = 0; i < f[lp::kDataLen]; ++i) CHECK(r8(*m, kOut + i) == f[i]);
        const s64 a = static_cast<s64>(rng() % 5) - 1, w = rng() % 6, t = rng() % 6, i = static_cast<s64>(rng() % 5) - 1;
        CHECK(v0s(pair(*m, C("scePadInfoAct"), {1, 0, static_cast<u64>(a), static_cast<u64>(w)}, seed++, "InfoAct" + tag, stand_ins)) == model_act(*m, 1, 0, a, w));
        CHECK(v0s(pair(*m, C("scePadInfoComb"), {1, 0, static_cast<u64>(a), static_cast<u64>(w) - 1}, seed++, "InfoComb" + tag, stand_ins)) ==
              model_comb(*m, 1, 0, a, w - 1));
        CHECK(v0s(pair(*m, C("scePadInfoMode"), {1, 0, static_cast<u64>(t), static_cast<u64>(i)}, seed++, "InfoMode" + tag, stand_ins)) == model_mode(*m, 1, 0, t, i));
        const bool ext = f[lp::kExtMode] == 1 && f[lp::kMode] >= 2;
        const u32 mask = f[121] | f[122] << 8 | f[123] << 16 | static_cast<u32>(f[124]) << 24;
        CHECK(v0_of(pair(*m, C("scePadGetButtonMask"), {1, 0}, seed++, "GetButtonMask" + tag, stand_ins)) ==
              (ext && f[lp::kPressCaps] >= 2 ? sx(mask) : 0));
        CHECK(v0_of(pair(*m, C("scePadInfoPressMode"), {1, 0}, seed++, "InfoPressMode" + tag, stand_ins)) == (ext && (f[lp::kPressCaps] & 2) ? 1u : 0u));
        CHECK(v0s(pair(*m, C("scePadGetReqState"), {1, 0}, seed++, "GetReqState" + tag, stand_ins)) == f[lp::kReqState]);
    }
    // pressure mode on / off: scePadSetButtonInfo with the 12-button mask or 0
    pair(*m, C("scePadEnterPressMode"), {1, 0}, seed++, "EnterPressMode", stand_ins);
    REQUIRE(last_log().calls_to(kSetButtonInfo) == 1);
    CHECK(last_log().log.back().args[2] == 0xFFF);
    pair(*m, C("scePadExitPressMode"), {1, 0}, seed++, "ExitPressMode", stand_ins);
    REQUIRE(last_log().calls_to(kSetButtonInfo) == 1);
    CHECK(last_log().log.back().args[2] == 0);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_pad): state names and the flush rate") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (u64 s = 0; s < 10; ++s) {
        wstr(*m, kOut, "XXXXXXXXXXXXXXXXXXXXXXXX");
        pair(*m, C("scePadStateIntToStr"), {s, kOut}, static_cast<u32>(s + 1), "StateIntToStr " + std::to_string(s), stand_ins);
        const std::string want = s < 8 ? gstr(*m, r32(*m, lp::kStateNames + 4 * static_cast<u32>(s))) : std::string();
        CHECK(gstr(*m, kOut) == want);
        wstr(*m, kOut, "XXXXXXXXXXXXXXXXXXXXXXXX");
        pair(*m, C("scePadReqIntToStr"), {s, kOut}, static_cast<u32>(s + 1), "ReqIntToStr " + std::to_string(s), stand_ins);
        CHECK(gstr(*m, kOut) == (s < 4 ? gstr(*m, r32(*m, lp::kReqNames + 4 * static_cast<u32>(s))) : std::string()));
    }
    MESSAGE("state names: " << gstr(*m, r32(*m, lp::kStateNames)) << " .. " << gstr(*m, r32(*m, lp::kStateNames + 28)));
    // accepted: 0 and 16675..66675 (an unsigned range check after the bias)
    for (s64 v : {0ll, 1ll, 16674ll, 16675ll, 40000ll, 66675ll, 66676ll, -1ll, 0x100000000ll + 16675}) {
        w32(*m, lp::kFlushRate, 0xDEAD);
        const auto r = pair(*m, C("scePadSetFlushRate"), {static_cast<u64>(v)}, 1, "SetFlushRate " + std::to_string(v), stand_ins);
        const s64 lo = static_cast<s32>(static_cast<u32>(v));  // the instructions use the word
        const bool ok = v == 0 || static_cast<u64>(lo - 16675) <= 0xC348u;  // the range test is on the word
        CHECK(v0_of(r) == (ok ? 1u : 0u));
        CHECK(r32(*m, lp::kFlushRate) == (ok ? static_cast<u32>(v) : 0xDEADu));
    }
}

#else

TEST_CASE("game(libs1_pad): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
