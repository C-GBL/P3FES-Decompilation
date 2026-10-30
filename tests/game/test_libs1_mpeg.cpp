// Pair tests of slice libs1, libmpeg's handle layer (game/src/lib/libs1_mpeg.cpp): every body against its recompiled
// body through tests/game/libs1_util.h (tests/game/handgen_pairs.h's whole-machine comparison on a fresh stand-in world
// per body, call logs equal). The callees no test build emits are served by recorders: the IPU feed _sendDataToIPU,
// _clearOnce, _sceMpegError / _sceMpegError1, the converters _sceMpegCscStoreRefImage / _cpr8 and _sceMpegFlush;
// _getpic (cri2, hand-written) runs and stops at its first check (a buffer off the 64-byte grid). scePrintf is emitted
// in the test build (another slice's callee), so _ErrMessage is paired only in the random sweep.
// Inputs: decoder states built field by field (cri2::mpeg's layout), every accessor read back on the host, the setters'
// stores, the callback table through a stand-in callback, the allocator arithmetic, the field-pair display hand-off.
//@INCLUDES
#include "p3fes/game/cri2.h"
//@END
#include "libs1_util.h"

#include "p3fes/game/libs1_mpeg.h"

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
void fn_sceMpegDelete_00500ad0(EEContext&);  // generated body
void fn_sceMpegDelete_00500ad0__recomp(EEContext&);  // recompiled
void fn_sceMpegAddBs_00500ad8(EEContext&);  // generated body
void fn_sceMpegAddBs_00500ad8__recomp(EEContext&);  // recompiled
void fn_sceMpegGetPicture_00500b18(EEContext&);  // generated body
void fn_sceMpegGetPicture_00500b18__recomp(EEContext&);  // recompiled
void fn_sceMpegGetPictureRAW8_00500b60(EEContext&);  // generated body
void fn_sceMpegGetPictureRAW8_00500b60__recomp(EEContext&);  // recompiled
void fn_sceMpegGetPictureAbort_00500ba8(EEContext&);  // generated body
void fn_sceMpegGetPictureAbort_00500ba8__recomp(EEContext&);  // recompiled
void fn_sceMpegIsEnd_00500c38(EEContext&);  // generated body
void fn_sceMpegIsEnd_00500c38__recomp(EEContext&);  // recompiled
void fn_sceMpegIsRefBuffEmpty_00500c48(EEContext&);  // generated body
void fn_sceMpegIsRefBuffEmpty_00500c48__recomp(EEContext&);  // recompiled
void fn_sceMpegSetDecodeMode_00500c58(EEContext&);  // generated body
void fn_sceMpegSetDecodeMode_00500c58__recomp(EEContext&);  // recompiled
void fn_sceMpegGetDecodeMode_00500c70(EEContext&);  // generated body
void fn_sceMpegGetDecodeMode_00500c70__recomp(EEContext&);  // recompiled
void fn_sceMpegAddCallback_00500c90(EEContext&);  // generated body
void fn_sceMpegAddCallback_00500c90__recomp(EEContext&);  // recompiled
void fn_sceMpegSetBuffType_00500cc8(EEContext&);  // generated body
void fn_sceMpegSetBuffType_00500cc8__recomp(EEContext&);  // recompiled
void fn_sceMpegGetBuffType_00500d00(EEContext&);  // generated body
void fn_sceMpegGetBuffType_00500d00__recomp(EEContext&);  // recompiled
void fn__sceMpegDispatchMpegCallback_00500d10(EEContext&);  // generated body
void fn__sceMpegDispatchMpegCallback_00500d10__recomp(EEContext&);  // recompiled
void fn__sceMpegDispatchMpegCbNodata_00500d88(EEContext&);  // generated body
void fn__sceMpegDispatchMpegCbNodata_00500d88__recomp(EEContext&);  // recompiled
void fn_sceMpegClearRefBuff_00500e48(EEContext&);  // generated body
void fn_sceMpegClearRefBuff_00500e48__recomp(EEContext&);  // recompiled
void fn_sceMpegGetPictureRAW8xy_00500ea0(EEContext&);  // generated body
void fn_sceMpegGetPictureRAW8xy_00500ea0__recomp(EEContext&);  // recompiled
void fn_sceMpegSetDefaultPtsGap_00500ef0(EEContext&);  // generated body
void fn_sceMpegSetDefaultPtsGap_00500ef0__recomp(EEContext&);  // recompiled
void fn_sceMpegResetDefaultPtsGap_00500f08(EEContext&);  // generated body
void fn_sceMpegResetDefaultPtsGap_00500f08__recomp(EEContext&);  // recompiled
void fn_sceMpegSetImageBuff_00500f20(EEContext&);  // generated body
void fn_sceMpegSetImageBuff_00500f20__recomp(EEContext&);  // recompiled
void fn_sceMpegDispWidth_00500f30(EEContext&);  // generated body
void fn_sceMpegDispWidth_00500f30__recomp(EEContext&);  // recompiled
void fn_sceMpegDispHeight_00500f40(EEContext&);  // generated body
void fn_sceMpegDispHeight_00500f40__recomp(EEContext&);  // recompiled
void fn_sceMpegDispCenterOffX_00500f50(EEContext&);  // generated body
void fn_sceMpegDispCenterOffX_00500f50__recomp(EEContext&);  // recompiled
void fn_sceMpegDispCenterOffY_00500f60(EEContext&);  // generated body
void fn_sceMpegDispCenterOffY_00500f60__recomp(EEContext&);  // recompiled
void fn__sceMpegSetBrokenLink_00500f70(EEContext&);  // generated body
void fn__sceMpegSetBrokenLink_00500f70__recomp(EEContext&);  // recompiled
void fn__sceMpegSetPtm_00500f80(EEContext&);  // generated body
void fn__sceMpegSetPtm_00500f80__recomp(EEContext&);  // recompiled
void fn__sceMpegAlalcInit_00501068(EEContext&);  // generated body
void fn__sceMpegAlalcInit_00501068__recomp(EEContext&);  // recompiled
void fn__sceMpegAlalcSetDynamic_00501080(EEContext&);  // generated body
void fn__sceMpegAlalcSetDynamic_00501080__recomp(EEContext&);  // recompiled
void fn__sceMpegAlalcReset_00501110(EEContext&);  // generated body
void fn__sceMpegAlalcReset_00501110__recomp(EEContext&);  // recompiled
void fn__dispRefImageField_005016c8(EEContext&);  // generated body
void fn__dispRefImageField_005016c8__recomp(EEContext&);  // recompiled
void fn__ErrMessage_005024f0(EEContext&);  // generated body
void fn__ErrMessage_005024f0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using p3fes::game_test::libs1::Case;

const Case kCases[] = {
    {"sceMpegDelete", 0x500AD0, &recomp_gen::fn_sceMpegDelete_00500ad0, &recomp_gen::fn_sceMpegDelete_00500ad0__recomp},
    {"sceMpegAddBs", 0x500AD8, &recomp_gen::fn_sceMpegAddBs_00500ad8, &recomp_gen::fn_sceMpegAddBs_00500ad8__recomp},
    {"sceMpegGetPicture", 0x500B18, &recomp_gen::fn_sceMpegGetPicture_00500b18, &recomp_gen::fn_sceMpegGetPicture_00500b18__recomp},
    {"sceMpegGetPictureRAW8", 0x500B60, &recomp_gen::fn_sceMpegGetPictureRAW8_00500b60, &recomp_gen::fn_sceMpegGetPictureRAW8_00500b60__recomp},
    {"sceMpegGetPictureAbort", 0x500BA8, &recomp_gen::fn_sceMpegGetPictureAbort_00500ba8, &recomp_gen::fn_sceMpegGetPictureAbort_00500ba8__recomp},
    {"sceMpegIsEnd", 0x500C38, &recomp_gen::fn_sceMpegIsEnd_00500c38, &recomp_gen::fn_sceMpegIsEnd_00500c38__recomp},
    {"sceMpegIsRefBuffEmpty", 0x500C48, &recomp_gen::fn_sceMpegIsRefBuffEmpty_00500c48, &recomp_gen::fn_sceMpegIsRefBuffEmpty_00500c48__recomp},
    {"sceMpegSetDecodeMode", 0x500C58, &recomp_gen::fn_sceMpegSetDecodeMode_00500c58, &recomp_gen::fn_sceMpegSetDecodeMode_00500c58__recomp},
    {"sceMpegGetDecodeMode", 0x500C70, &recomp_gen::fn_sceMpegGetDecodeMode_00500c70, &recomp_gen::fn_sceMpegGetDecodeMode_00500c70__recomp},
    {"sceMpegAddCallback", 0x500C90, &recomp_gen::fn_sceMpegAddCallback_00500c90, &recomp_gen::fn_sceMpegAddCallback_00500c90__recomp},
    {"sceMpegSetBuffType", 0x500CC8, &recomp_gen::fn_sceMpegSetBuffType_00500cc8, &recomp_gen::fn_sceMpegSetBuffType_00500cc8__recomp},
    {"sceMpegGetBuffType", 0x500D00, &recomp_gen::fn_sceMpegGetBuffType_00500d00, &recomp_gen::fn_sceMpegGetBuffType_00500d00__recomp},
    {"_sceMpegDispatchMpegCallback", 0x500D10, &recomp_gen::fn__sceMpegDispatchMpegCallback_00500d10, &recomp_gen::fn__sceMpegDispatchMpegCallback_00500d10__recomp},
    {"_sceMpegDispatchMpegCbNodata", 0x500D88, &recomp_gen::fn__sceMpegDispatchMpegCbNodata_00500d88, &recomp_gen::fn__sceMpegDispatchMpegCbNodata_00500d88__recomp},
    {"sceMpegClearRefBuff", 0x500E48, &recomp_gen::fn_sceMpegClearRefBuff_00500e48, &recomp_gen::fn_sceMpegClearRefBuff_00500e48__recomp},
    {"sceMpegGetPictureRAW8xy", 0x500EA0, &recomp_gen::fn_sceMpegGetPictureRAW8xy_00500ea0, &recomp_gen::fn_sceMpegGetPictureRAW8xy_00500ea0__recomp},
    {"sceMpegSetDefaultPtsGap", 0x500EF0, &recomp_gen::fn_sceMpegSetDefaultPtsGap_00500ef0, &recomp_gen::fn_sceMpegSetDefaultPtsGap_00500ef0__recomp},
    {"sceMpegResetDefaultPtsGap", 0x500F08, &recomp_gen::fn_sceMpegResetDefaultPtsGap_00500f08, &recomp_gen::fn_sceMpegResetDefaultPtsGap_00500f08__recomp},
    {"sceMpegSetImageBuff", 0x500F20, &recomp_gen::fn_sceMpegSetImageBuff_00500f20, &recomp_gen::fn_sceMpegSetImageBuff_00500f20__recomp},
    {"sceMpegDispWidth", 0x500F30, &recomp_gen::fn_sceMpegDispWidth_00500f30, &recomp_gen::fn_sceMpegDispWidth_00500f30__recomp},
    {"sceMpegDispHeight", 0x500F40, &recomp_gen::fn_sceMpegDispHeight_00500f40, &recomp_gen::fn_sceMpegDispHeight_00500f40__recomp},
    {"sceMpegDispCenterOffX", 0x500F50, &recomp_gen::fn_sceMpegDispCenterOffX_00500f50, &recomp_gen::fn_sceMpegDispCenterOffX_00500f50__recomp},
    {"sceMpegDispCenterOffY", 0x500F60, &recomp_gen::fn_sceMpegDispCenterOffY_00500f60, &recomp_gen::fn_sceMpegDispCenterOffY_00500f60__recomp},
    {"_sceMpegSetBrokenLink", 0x500F70, &recomp_gen::fn__sceMpegSetBrokenLink_00500f70, &recomp_gen::fn__sceMpegSetBrokenLink_00500f70__recomp},
    {"_sceMpegSetPtm", 0x500F80, &recomp_gen::fn__sceMpegSetPtm_00500f80, &recomp_gen::fn__sceMpegSetPtm_00500f80__recomp},
    {"_sceMpegAlalcInit", 0x501068, &recomp_gen::fn__sceMpegAlalcInit_00501068, &recomp_gen::fn__sceMpegAlalcInit_00501068__recomp},
    {"_sceMpegAlalcSetDynamic", 0x501080, &recomp_gen::fn__sceMpegAlalcSetDynamic_00501080, &recomp_gen::fn__sceMpegAlalcSetDynamic_00501080__recomp},
    {"_sceMpegAlalcReset", 0x501110, &recomp_gen::fn__sceMpegAlalcReset_00501110, &recomp_gen::fn__sceMpegAlalcReset_00501110__recomp},
    {"_dispRefImageField", 0x5016C8, &recomp_gen::fn__dispRefImageField_005016c8, &recomp_gen::fn__dispRefImageField_005016c8__recomp},
    {"_ErrMessage", 0x5024F0, &recomp_gen::fn__ErrMessage_005024f0, &recomp_gen::fn__ErrMessage_005024f0__recomp},
};

using namespace p3fes::game_test::libs1;
namespace mp = p3fes::game::cri2::mpeg;
namespace lm = p3fes::game::libs1::mpeg;

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kHandle = 0x01830000u;  // a sceMpeg handle: +64 -> the state
constexpr u32 kState = 0x01831000u;   // the decoder state (0x880 bytes and more)
constexpr u32 kInfo = 0x01834000u;    // the output-info record of _dispRefImageField
constexpr u32 kField0 = 0x01835000u, kField1 = 0x01835100u;  // two field descriptors
constexpr u32 kImage = 0x01836000u;
constexpr u32 kCbFn = 0x501DF8u;  // a callback address served by a stand-in (no test build emits it)

const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }

void recorders(StandInWorld& w) {
    w.si.install_recorder(0x5000B0u, "_sendDataToIPU", 0);
    w.si.install_recorder(0x4FFDA8u, "_clearOnce", 0);
    w.si.install(0x502668u, "_sceMpegError", [](EEContext& ctx, StandIns&, StandInCall& c) {
        c.text = std::string(reinterpret_cast<const char*>(gptr(ctx, static_cast<u32>(c.args[1]))));
    });
    w.si.install_recorder(0x5026C0u, "_sceMpegError1", 0);
    w.si.install_recorder(kCbFn, "_sceMpegCscStoreRefImage", 0x77);
    w.si.install_recorder(0x501178u, "_cpr8", 0x66);
    w.si.install_recorder(0x501AE8u, "_sceMpegFlush", 0);
}

void fresh_state(Machine& m, u32 seed) {
    std::mt19937 rng{seed};
    for (u32 i = 0; i < 0x900; i += 4) w32(m, kState + i, rng() % 3 == 0 ? rng() : rng() % 64);
    w32(m, kHandle + mp::kInner, kState);
    w32(m, kState + mp::kAbort, 0);
    w32(m, kState + mp::kImageBuf, kImage);   // 64-byte aligned
}

}  // namespace

TEST_CASE("game(libs1_mpeg): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, 32, recorders);
}

TEST_CASE("game(libs1_mpeg): accessors and setters on built decoder states") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (u32 seed = 1; seed <= 12; ++seed) {
        fresh_state(*m, seed);
        const std::string tag = " seed " + std::to_string(seed);
        CHECK(v0s(pair(*m, C("sceMpegIsEnd"), {kHandle}, seed, "IsEnd" + tag, recorders)) == static_cast<s32>(r32(*m, kState + mp::kEnd)));
        const bool empty = r32(*m, kState + mp::kFrameNo) == 0;
        CHECK(v0_of(pair(*m, C("sceMpegIsRefBuffEmpty"), {kHandle}, seed, "IsRefBuffEmpty" + tag, recorders)) == (empty ? 1u : 0u));
        CHECK(v0s(pair(*m, C("sceMpegGetBuffType"), {kHandle}, seed, "GetBuffType" + tag, recorders)) == static_cast<s32>(r32(*m, kState + mp::kBufType)));
        CHECK(v0s(pair(*m, C("sceMpegDispWidth"), {kHandle}, seed, "DispWidth" + tag, recorders)) == static_cast<s32>(r32(*m, kState + lm::kDispWidth)));
        CHECK(v0s(pair(*m, C("sceMpegDispHeight"), {kHandle}, seed, "DispHeight" + tag, recorders)) == static_cast<s32>(r32(*m, kState + lm::kDispHeight)));
        // both centre accessors return the address of the centre record (state + 200)
        CHECK(v0_of(pair(*m, C("sceMpegDispCenterOffX"), {kHandle}, seed, "CenterX" + tag, recorders)) == kState + 200);
        CHECK(v0_of(pair(*m, C("sceMpegDispCenterOffY"), {kHandle}, seed, "CenterY" + tag, recorders)) == kState + 200);
        CHECK(v0_of(pair(*m, C("sceMpegDelete"), {kHandle}, seed, "Delete" + tag, recorders)) == 1);

        // decode modes: set, then read back through three out-words
        pair(*m, C("sceMpegSetDecodeMode"), {kHandle, 7 + seed, 11, 13}, seed, "SetDecodeMode" + tag, recorders);
        CHECK(r32(*m, kState + mp::kSkipI) == 7 + seed);
        CHECK(r32(*m, kState + mp::kSkipP) == 11);
        CHECK(r32(*m, kState + mp::kSkipB) == 13);
        const auto gd = pair(*m, C("sceMpegGetDecodeMode"), {kHandle, kWorld, kWorld + 4, kWorld + 8}, seed, "GetDecodeMode" + tag, recorders);
        CHECK(r32(*m, kWorld) == 7 + seed);
        CHECK(r32(*m, kWorld + 4) == 11);
        CHECK(r32(*m, kWorld + 8) == 13);
        CHECK(v0s(gd) == 13);

        pair(*m, C("sceMpegSetDefaultPtsGap"), {kHandle, 0x123456789ull * seed}, seed, "SetDefaultPtsGap" + tag, recorders);
        CHECK(r64(*m, kState + lm::kPtsGap) == 0x123456789ull * seed);
        CHECK(r32(*m, kState + lm::kPtsGapSet) == 1);
        pair(*m, C("sceMpegResetDefaultPtsGap"), {kHandle}, seed, "ResetDefaultPtsGap" + tag, recorders);
        CHECK(r64(*m, kState + lm::kPtsGap) == 0);
        CHECK(r32(*m, kState + lm::kPtsGapSet) == 0);
        pair(*m, C("_sceMpegSetPtm"), {kHandle, 90000ull * seed}, seed, "SetPtm" + tag, recorders);
        CHECK(r64(*m, kState + lm::kPtm) == 90000ull * seed);
        CHECK(r32(*m, kState + lm::kPtmSet) == 1);
        const u32 old = r32(*m, kState + mp::kBrokenLinkPend);
        CHECK(v0_of(pair(*m, C("_sceMpegSetBrokenLink"), {kHandle, seed & 1}, seed, "SetBrokenLink" + tag, recorders)) == sx(old));
        CHECK(r32(*m, kState + mp::kBrokenLinkPend) == (seed & 1));
        pair(*m, C("sceMpegSetImageBuff"), {kHandle, kImage + 64 * seed}, seed, "SetImageBuff" + tag, recorders);
        CHECK(r32(*m, kState + mp::kImageBuf) == kImage + 64 * seed);
        pair(*m, C("sceMpegGetPictureAbort"), {kHandle}, seed, "GetPictureAbort" + tag, recorders);
        CHECK(r32(*m, kState + mp::kAbort) == 1);

        // buffer type: 0 / 1 accepted (and _clearOnce called), anything else -1
        for (u64 t : {0ull, 1ull, 2ull, 0xFFFFFFFFFFFFFFFFull}) {
            const auto r = pair(*m, C("sceMpegSetBuffType"), {kHandle, t}, seed, "SetBuffType" + tag, recorders);
            if (t < 2) {
                CHECK(v0s(r) == 1);
                CHECK(r32(*m, kState + mp::kBufType) == t);
                CHECK(last_log().calls_to(0x4FFDA8u) == 1);
            } else {
                CHECK(v0s(r) == -1);
                CHECK(last_log().calls_to(0x4FFDA8u) == 0);
            }
        }
        // the reference descriptors' "complete" words
        for (u32 i = 0; i < 6; ++i) w32(*m, kState + 456 + 16 * (i % 3) + 4 * (i / 3), kWorld + 0x100 * (i + 1));
        for (u32 i = 0; i < 6; ++i) w32(*m, kWorld + 0x100 * (i + 1) + mp::kRefDone, 1);
        w32(*m, kState + 488 + 4, 0);  // one empty slot is skipped
        pair(*m, C("sceMpegClearRefBuff"), {kHandle}, seed, "ClearRefBuff" + tag, recorders);
        for (u32 i = 0; i < 6; ++i) CHECK(r32(*m, kWorld + 0x100 * (i + 1) + mp::kRefDone) == (i == 5 ? 1u : 0u));
    }
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_mpeg): GetPicture variants, AddBs, the callback table, the allocator") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (u32 seed = 1; seed <= 8; ++seed) {
        fresh_state(*m, seed);
        const std::string tag = " seed " + std::to_string(seed);
        const u32 img = kImage + 0x40 * seed;
        // The three variants store the output set-up, then _getpic runs; a buffer off the 64-byte grid makes its first
        // check report through _sceMpegError1 and return -1 (the abort-flag exit would print through scePrintf, which
        // the test build emits). RGB32: format 1, uncached image buffer, size, offsets 0.
        auto r = pair(*m, C("sceMpegGetPicture"), {kHandle, img + 4, 0x1000u * seed}, seed, "GetPicture" + tag, recorders);
        CHECK(v0s(r) == -1);
        CHECK(last_log().calls_to(0x5026C0u) == 1);
        CHECK(r32(*m, kState + lm::kOutCsc) == 1);
        CHECK(r32(*m, kState + mp::kImageBuf) == ((img + 4) | 0x20000000u));
        CHECK(r32(*m, kState + lm::kOutSize) == 0x1000u * seed);
        CHECK(r32(*m, kState + lm::kOutX) == 0);
        CHECK(r32(*m, kState + lm::kOutY) == 0);
        r = pair(*m, C("sceMpegGetPictureRAW8"), {kHandle, img + 8, 0x800u * seed}, seed, "GetPictureRAW8" + tag, recorders);
        CHECK(v0s(r) == -1);
        CHECK(r32(*m, kState + lm::kOutCsc) == 0);
        CHECK(r64(*m, kState + mp::kImageBuf) == static_cast<u64>((img + 8) | 0x20000000u));  // a doubleword store: +240 cleared
        CHECK(r32(*m, kState + lm::kOutSize) == 0x800u * seed);
        r = pair(*m, C("sceMpegGetPictureRAW8xy"), {kHandle, img + 16, 20 + seed, 15}, seed, "GetPictureRAW8xy" + tag, recorders);
        CHECK(v0s(r) == -1);
        CHECK(r32(*m, kState + lm::kOutX) == 16 * (20 + seed));
        CHECK(r32(*m, kState + lm::kOutY) == 16 * 15);
        CHECK(r32(*m, kState + lm::kOutSize) == (20 + seed) * 15);

        // AddBs: (size + 19) / 16 quadwords, rounded towards zero
        for (s64 size : {0ll, 1ll, 13ll, 16ll, 100ll, -19ll, -20ll, -36ll}) {
            r = pair(*m, C("sceMpegAddBs"), {kHandle, kWorld, static_cast<u64>(size)}, seed, "AddBs " + std::to_string(size), recorders);
            CHECK(v0s(r) == 1);
            const StandInCall& call = last_log().log.back();
            CHECK(call.va == 0x5000B0u);
            CHECK(static_cast<u32>(call.args[0]) == kState);
            const s64 q = (size + 19) / 16;  // C division truncates towards zero, as the sra after the bias
            CHECK(static_cast<s32>(call.args[2]) == static_cast<s32>(16 * q));
        }

        // the callback table: install returns the old function; dispatch calls it with (handle, record, data)
        w32(*m, kState + lm::kCbTable + 12 * 2, 0x1234u);
        r = pair(*m, C("sceMpegAddCallback"), {kHandle, 2, kCbFn, 0xABCD0000u + seed}, seed, "AddCallback" + tag, recorders);
        CHECK(v0_of(r) == 0x1234u);
        CHECK(r32(*m, kState + lm::kCbTable + 24) == kCbFn);
        CHECK(r32(*m, kState + lm::kCbTable + 28) == 0xABCD0000u + seed);
        w32(*m, kWorld + 0x40, 2);  // a record of type 2
        r = pair(*m, C("_sceMpegDispatchMpegCallback"), {kHandle, kWorld + 0x40}, seed, "Dispatch" + tag, recorders);
        CHECK(v0_of(r) == 0x77);
        REQUIRE(last_log().calls_to(kCbFn) == 1);
        CHECK(static_cast<u32>(last_log().log.back().args[0]) == kHandle);
        CHECK(static_cast<u32>(last_log().log.back().args[1]) == kWorld + 0x40);
        CHECK(static_cast<u32>(last_log().log.back().args[2]) == 0xABCD0000u + seed);
        w32(*m, kState + lm::kCbTable + 24, 0);  // empty slot: 0, no call
        r = pair(*m, C("_sceMpegDispatchMpegCallback"), {kHandle, kWorld + 0x40}, seed, "Dispatch empty" + tag, recorders);
        CHECK(v0_of(r) == 0);
        CHECK(last_log().log.empty());
        r = pair(*m, C("_sceMpegDispatchMpegCallback"), {0, kWorld + 0x40}, seed, "Dispatch null" + tag, recorders);
        CHECK(v0_of(r) == 0);
        // NODATA: the type-1 slot with a stack record {1}
        w32(*m, kState + lm::kCbNodata, kCbFn);
        w32(*m, kState + lm::kCbTable + 12 + 4, 0x5150u);
        r = pair(*m, C("_sceMpegDispatchMpegCbNodata"), {kHandle}, seed, "Nodata" + tag, recorders);
        CHECK(v0_of(r) == 1);
        CHECK(last_log().calls_to(kCbFn) == 1);
        CHECK(static_cast<u32>(last_log().log.back().args[2]) == 0x5150u);
        w32(*m, kState + lm::kCbNodata, 0);
        r = pair(*m, C("_sceMpegDispatchMpegCbNodata"), {kHandle}, seed, "Nodata empty" + tag, recorders);
        CHECK(v0_of(r) == 1);
        CHECK(last_log().log.empty());

        // the allocator: init, mark, bytes left
        pair(*m, C("_sceMpegAlalcInit"), {kWorld + 0x80, 0x100000u * seed, 0x4000u}, seed, "AlalcInit" + tag, recorders);
        CHECK(r32(*m, kWorld + 0x80 + lm::alalc::kBase) == 0x100000u * seed);
        CHECK(r32(*m, kWorld + 0x80 + lm::alalc::kSize) == 0x4000u);
        CHECK(r32(*m, kWorld + 0x80 + lm::alalc::kCursor) == 0x100000u * seed);
        CHECK(r32(*m, kWorld + 0x80 + lm::alalc::kMark) == 0x100000u * seed);
        w32(*m, kWorld + 0x80 + lm::alalc::kCursor, 0x100000u * seed + 0x1230);
        pair(*m, C("_sceMpegAlalcSetDynamic"), {kWorld + 0x80}, seed, "AlalcSetDynamic" + tag, recorders);
        CHECK(r32(*m, kWorld + 0x80 + lm::alalc::kMark) == 0x100000u * seed + 0x1230);
        CHECK(v0s(pair(*m, C("_sceMpegAlalcReset"), {kWorld + 0x80}, seed, "AlalcReset" + tag, recorders)) == 0x4000 - 0x1230);
    }
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_mpeg): the field-pair display hand-off") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    int n = 0;
    for (u32 seed = 1; seed <= 24; ++seed) {
        std::mt19937 rng{seed};
        fresh_state(*m, seed);
        wzero(*m, kInfo, 0x100);
        w32(*m, kState + 2152, kInfo);
        w32(*m, kState + 388, rng() % 2 ? 2 : 3);       // picture structure: 2 = bottom field first
        w32(*m, kState + lm::kPtsGapSet, rng() % 2);
        w64(*m, kState + lm::kPtsGap, 3003);
        w32(*m, kState + 152, rng() % 2 ? 1000 : static_cast<u32>(-1));
        w32(*m, kState + 156, rng() % 4);
        w32(*m, kState + 160, rng() % 3);
        w32(*m, kState + lm::kPtmSet, rng() % 3);
        w64(*m, kState + lm::kPtm, rng() % 2 ? 777 : ~0ull);
        w32(*m, kState + lm::kOutCsc, rng() % 2);
        const u32 w = 16 * (1 + rng() % 40), h = 16 * (1 + rng() % 30);
        for (u32 f : {kField0, kField1}) {
            for (u32 i = 0; i < 0x80; i += 4) w32(*m, f + i, rng() % 16);
            w64(*m, f + 24, rng() % 2 ? static_cast<u64>(rng()) : ~0ull);  // PTS (negative = none)
            w64(*m, f + 32, rng());
            w32(*m, f + 40, rng() % 4 ? 1 : 0);                            // complete
        }
        w32(*m, kField0 + 4, w);
        w32(*m, kField0 + 8, h);
        w32(*m, kField0 + 12, w / 16);
        w32(*m, kField0 + 16, h / 32);
        // the caller's buffer: big enough or not, in pixels (RAW8xy) or in bytes (size)
        const bool xy = rng() % 2;
        const bool fits = rng() % 3 != 0;
        w32(*m, kState + lm::kOutY, xy ? (fits ? h : h - 16) : 0);
        w32(*m, kState + lm::kOutX, xy ? (fits ? w + 16 : w - 16) : 0);
        w32(*m, kState + lm::kOutSize, fits ? (w / 16) * (h / 32) : (w / 16) * (h / 32) - 1);
        const auto r = pair(*m, C("_dispRefImageField"), {kState, kField0, kField1}, seed, "dispRefImageField seed " + std::to_string(seed), recorders);
        const StandIns& log = last_log();
        if (!fits) {
            CHECK(log.calls_to(0x502668u) == 1);
            if (log.calls_to(0x502668u) == 1) {
                const std::string& t = log.log.back().text;
                CHECK(t.find("Too small buffer") == 0);
                CHECK(t.find(std::to_string(w) + "x" + std::to_string(h) + " picture") != std::string::npos);
            }
        } else {
            CHECK(log.calls_to(0x502668u) == 0);
            const bool both = r32(*m, kField0 + 40) == 1 && r32(*m, kField1 + 40) == 1;
            CHECK(log.calls_to(kCbFn) + log.calls_to(0x501178u) == (both ? 1u : 0u));
            if (both) CHECK(r32(*m, kField0 + 16) == h / 32);  // doubled for the conversion and halved back
            const u32 first = r32(*m, kState + 388) == 2 ? kField0 : kField1;  // the field whose size is shown
            CHECK(r32(*m, kState + lm::kDispWidth) == r32(*m, first + 92));
            CHECK(r32(*m, kState + lm::kDispHeight) == r32(*m, first + 96));
        }
        CHECK(!r.stopped);
        ++n;
    }
    MESSAGE(n << " hand-offs; pairs " << counts().pairs << ", stopped " << counts().stops);
}

#else

TEST_CASE("game(libs1_mpeg): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
