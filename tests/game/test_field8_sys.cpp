// Pair tests of slice field8, group sys (game/src/sweep/field8_sys.cpp): every body against its recompiled body
//   * on random worlds (the p3fes_handgen sweep, each random draw its own statement);
//   * with the IOP-facing libraries stood in (stand_ins.h; field8_util.h), the documented rules: the hdd RtFS
//     callbacks' path / mode / position / seek rules, H_Memcard_Check's result rules and the sequencers mode by mode,
//     the init functions' records, h_sndcom's SE voices, the sound pump's channel rules on the dorm snapshot, the
//     resource manager's pump / init / suspend / resume and its worker thread over the ten request kinds,
//     the VBlank gate installer and the assert stubs.
#include "field8_util.h"

#include <cstring>
#include <memory>
#include <string>
#include <vector>
#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_H_Cdvd_RtFsHdd_Fopen_00102900(EEContext&);  // generated body
void fn_H_Cdvd_RtFsHdd_Fopen_00102900__recomp(EEContext&);  // recompiled
void fn_sub_102A70_00102a70(EEContext&);  // generated body
void fn_sub_102A70_00102a70__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_RtFsHdd_FRead_00102ad0(EEContext&);  // generated body
void fn_H_Cdvd_RtFsHdd_FRead_00102ad0__recomp(EEContext&);  // recompiled
void fn_sub_102B60_00102b60(EEContext&);  // generated body
void fn_sub_102B60_00102b60__recomp(EEContext&);  // recompiled
void fn_sub_102BF0_00102bf0(EEContext&);  // generated body
void fn_sub_102BF0_00102bf0__recomp(EEContext&);  // recompiled
void fn_sub_102D10_00102d10(EEContext&);  // generated body
void fn_sub_102D10_00102d10__recomp(EEContext&);  // recompiled
void fn_H_Pad_Init_00103000(EEContext&);  // generated body
void fn_H_Pad_Init_00103000__recomp(EEContext&);  // recompiled
void fn_sub_108BC0_00108bc0(EEContext&);  // generated body
void fn_sub_108BC0_00108bc0__recomp(EEContext&);  // recompiled
void fn_sub_10BF70_0010bf70(EEContext&);  // generated body
void fn_sub_10BF70_0010bf70__recomp(EEContext&);  // recompiled
void fn_H_ResrcMan_MaybeResumeThread_0010bff0(EEContext&);  // generated body
void fn_H_ResrcMan_MaybeResumeThread_0010bff0__recomp(EEContext&);  // recompiled
void fn_H_ResrcMan_Init_0010c050(EEContext&);  // generated body
void fn_H_ResrcMan_Init_0010c050__recomp(EEContext&);  // recompiled
void fn_H_ResrcMan_Update_0010c5f0(EEContext&);  // generated body
void fn_H_ResrcMan_Update_0010c5f0__recomp(EEContext&);  // recompiled
void fn_H_Resman_ThreadProc_0010c7d0(EEContext&);  // generated body
void fn_H_Resman_ThreadProc_0010c7d0__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_Init_0010cac0(EEContext&);  // generated body
void fn_H_Sndcom_Init_0010cac0__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_StopVoice_0010da70(EEContext&);  // generated body
void fn_H_Sndcom_StopVoice_0010da70__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_PlayVoice_0010db60(EEContext&);  // generated body
void fn_H_Sndcom_PlayVoice_0010db60__recomp(EEContext&);  // recompiled
void fn_H_Memcard_Init_0018f100(EEContext&);  // generated body
void fn_H_Memcard_Init_0018f100__recomp(EEContext&);  // recompiled
void fn_H_Memcard_Check_0018f190(EEContext&);  // generated body
void fn_H_Memcard_Check_0018f190__recomp(EEContext&);  // recompiled
void fn_H_Memcard_UpdateSeqMode_0018f2c0(EEContext&);  // generated body
void fn_H_Memcard_UpdateSeqMode_0018f2c0__recomp(EEContext&);  // recompiled
void fn_sub_190590_00190590(EEContext&);  // generated body
void fn_sub_190590_00190590__recomp(EEContext&);  // recompiled
void fn_sub_190720_00190720(EEContext&);  // generated body
void fn_sub_190720_00190720__recomp(EEContext&);  // recompiled
void fn_sub_190CD0_00190cd0(EEContext&);  // generated body
void fn_sub_190CD0_00190cd0__recomp(EEContext&);  // recompiled
void fn_sub_191660_00191660(EEContext&);  // generated body
void fn_sub_191660_00191660__recomp(EEContext&);  // recompiled
void fn_kwlnInstallVsyncFieldGate_0019d360(EEContext&);  // generated body
void fn_kwlnInstallVsyncFieldGate_0019d360__recomp(EEContext&);  // recompiled
void fn_sub_19D3F0_0019d3f0(EEContext&);  // generated body
void fn_sub_19D3F0_0019d3f0__recomp(EEContext&);  // recompiled
void fn_sub_19D400_0019d400(EEContext&);  // generated body
void fn_sub_19D400_0019d400__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game_test::f8t;

const Case kCases[] = {
    {"H_Cdvd_RtFsHdd_Fopen", 0x102900, &recomp_gen::fn_H_Cdvd_RtFsHdd_Fopen_00102900, &recomp_gen::fn_H_Cdvd_RtFsHdd_Fopen_00102900__recomp},
    {"sub_102A70", 0x102A70, &recomp_gen::fn_sub_102A70_00102a70, &recomp_gen::fn_sub_102A70_00102a70__recomp},
    {"H_Cdvd_RtFsHdd_FRead", 0x102AD0, &recomp_gen::fn_H_Cdvd_RtFsHdd_FRead_00102ad0, &recomp_gen::fn_H_Cdvd_RtFsHdd_FRead_00102ad0__recomp},
    {"sub_102B60", 0x102B60, &recomp_gen::fn_sub_102B60_00102b60, &recomp_gen::fn_sub_102B60_00102b60__recomp},
    {"sub_102BF0", 0x102BF0, &recomp_gen::fn_sub_102BF0_00102bf0, &recomp_gen::fn_sub_102BF0_00102bf0__recomp},
    {"sub_102D10", 0x102D10, &recomp_gen::fn_sub_102D10_00102d10, &recomp_gen::fn_sub_102D10_00102d10__recomp},
    {"H_Pad_Init", 0x103000, &recomp_gen::fn_H_Pad_Init_00103000, &recomp_gen::fn_H_Pad_Init_00103000__recomp},
    {"sub_108BC0", 0x108BC0, &recomp_gen::fn_sub_108BC0_00108bc0, &recomp_gen::fn_sub_108BC0_00108bc0__recomp},
    {"sub_10BF70", 0x10BF70, &recomp_gen::fn_sub_10BF70_0010bf70, &recomp_gen::fn_sub_10BF70_0010bf70__recomp},
    {"H_ResrcMan_MaybeResumeThread", 0x10BFF0, &recomp_gen::fn_H_ResrcMan_MaybeResumeThread_0010bff0, &recomp_gen::fn_H_ResrcMan_MaybeResumeThread_0010bff0__recomp},
    {"H_ResrcMan_Init", 0x10C050, &recomp_gen::fn_H_ResrcMan_Init_0010c050, &recomp_gen::fn_H_ResrcMan_Init_0010c050__recomp},
    {"H_ResrcMan_Update", 0x10C5F0, &recomp_gen::fn_H_ResrcMan_Update_0010c5f0, &recomp_gen::fn_H_ResrcMan_Update_0010c5f0__recomp},
    {"H_Resman_ThreadProc", 0x10C7D0, &recomp_gen::fn_H_Resman_ThreadProc_0010c7d0, &recomp_gen::fn_H_Resman_ThreadProc_0010c7d0__recomp},
    {"H_Sndcom_Init", 0x10CAC0, &recomp_gen::fn_H_Sndcom_Init_0010cac0, &recomp_gen::fn_H_Sndcom_Init_0010cac0__recomp},
    {"H_Sndcom_StopVoice", 0x10DA70, &recomp_gen::fn_H_Sndcom_StopVoice_0010da70, &recomp_gen::fn_H_Sndcom_StopVoice_0010da70__recomp},
    {"H_Sndcom_PlayVoice", 0x10DB60, &recomp_gen::fn_H_Sndcom_PlayVoice_0010db60, &recomp_gen::fn_H_Sndcom_PlayVoice_0010db60__recomp},
    {"H_Memcard_Init", 0x18F100, &recomp_gen::fn_H_Memcard_Init_0018f100, &recomp_gen::fn_H_Memcard_Init_0018f100__recomp},
    {"H_Memcard_Check", 0x18F190, &recomp_gen::fn_H_Memcard_Check_0018f190, &recomp_gen::fn_H_Memcard_Check_0018f190__recomp},
    {"H_Memcard_UpdateSeqMode", 0x18F2C0, &recomp_gen::fn_H_Memcard_UpdateSeqMode_0018f2c0, &recomp_gen::fn_H_Memcard_UpdateSeqMode_0018f2c0__recomp},
    {"sub_190590", 0x190590, &recomp_gen::fn_sub_190590_00190590, &recomp_gen::fn_sub_190590_00190590__recomp},
    {"sub_190720", 0x190720, &recomp_gen::fn_sub_190720_00190720, &recomp_gen::fn_sub_190720_00190720__recomp},
    {"sub_190CD0", 0x190CD0, &recomp_gen::fn_sub_190CD0_00190cd0, &recomp_gen::fn_sub_190CD0_00190cd0__recomp},
    {"sub_191660", 0x191660, &recomp_gen::fn_sub_191660_00191660, &recomp_gen::fn_sub_191660_00191660__recomp},
    {"kwlnInstallVsyncFieldGate", 0x19D360, &recomp_gen::fn_kwlnInstallVsyncFieldGate_0019d360, &recomp_gen::fn_kwlnInstallVsyncFieldGate_0019d360__recomp},
    {"sub_19D3F0", 0x19D3F0, &recomp_gen::fn_sub_19D3F0_0019d3f0, &recomp_gen::fn_sub_19D3F0_0019d3f0__recomp},
    {"sub_19D400", 0x19D400, &recomp_gen::fn_sub_19D400_0019d400, &recomp_gen::fn_sub_19D400_0019d400__recomp},
};

constexpr u32 kSceOpen = 0x508670u, kSceLseek = 0x508A78u, kSceRead = 0x508CB8u, kSceWrite = 0x508F28u,
              kSceClose = 0x508900u, kSceSync = 0x50A888u;
constexpr u32 kMcCheck = 0x514900u, kMcGetInfo = 0x5136F8u, kMcSearch = 0x5137B8u, kMcFormat = 0x513598u,
              kMcMkdir = 0x5140F8u, kMcCreate = 0x513DE8u, kMcWrite = 0x513CC8u, kMcRead = 0x513968u;
constexpr u32 kMcSeq = 0x7CE03Cu, kMcCancelWord = 0x7CE01Cu, kMcSlotWord = 0x7CE034u, kMcOrigWord = 0x7CE00Cu,
              kMcInfo = 0x846EA0u, kMcPath = 0x846DA0u;
constexpr u32 kCreateThread = 0x502F60u, kStartThread = 0x5042A0u, kReferStatus = 0x503060u, kSuspend = 0x5030D0u,
              kResume = 0x5030F0u, kSleep = 0x503080u, kWakeup = 0x503090u;
constexpr u32 kAddIntc = 0x502E40u, kEnableIntc = 0x503CA8u, kRemoveIntc = 0x502E60u;
constexpr u32 kSesqStatus = 0x51E028u, kSesqControl = 0x51DF58u, kSpuAlloc = 0x51D6F8u;
constexpr u32 kPadPortOpen = 0x511590u;
constexpr u32 kStarted = 0x7CDF24u, kThreadId = 0x7CDF28u, kControl = 0x7CDF30u, kReqList = 0x7E5860u,
              kReqRecords = 0x7E5A40u;
constexpr u32 kSlots = 0x833710u, kVoices = 0x833650u;

// The worker thread never returns: both bodies run inside a catch of F8Stop (thrown by the test's SleepThread).
void thread_hand(EEContext& ctx) {
    try {
        recomp_gen::fn_H_Resman_ThreadProc_0010c7d0(ctx);
    } catch (const F8Stop&) {
    }
}
void thread_recomp(EEContext& ctx) {
    try {
        recomp_gen::fn_H_Resman_ThreadProc_0010c7d0__recomp(ctx);
    } catch (const F8Stop&) {
    }
}

}  // namespace

TEST_CASE("game(field8 sys): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}

// --- the "hdd:" RtFS device -------------------------------------------------------------------------------------------
// The callbacks on a 144-byte file object with the pfs0 calls stood in: sceOpen answers `open_ret` (and logs the path),
// sceLseek answers the size for SEEK_END and the offset otherwise, sceRead / sceWrite answer `io_ret`. The rules: the
// path is "pfs0:" + name + 4; the RtFS mode bits map to the sceOpen flags (1 -> 1, 2 -> 2, both -> 3, 4 -> 0x200,
// write without 8 -> 0x400) with mode 0777; open answers 2 for no name, 3 when sceOpen fails, else 1 with the size and
// position 0; read / write add the count to the 64-bit position (read sets state 3), an error answers 0 and moves
// nothing; seek's whence 3 / 2 / 1 move back / forward / to the offset, clamped at 0, any other whence gives -1 without
// a seek, and the result quadword is the position's; exists opens and closes; close marks state 1.
TEST_CASE("game(field8 sys): the hdd RtFS callbacks over pfs0 (open modes, read / write / seek rules, exists, close)") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    namespace hdd = game::f8::hdd;
    constexpr u32 kFile = kScratch, kName = kScratch + 0x200, kResult = kScratch + 0x300, kBuf = kScratch + 0x400;
    s64 open_ret = 7, io_ret = 64;
    const s64 kSize = 0x12345;
    const auto pfs = [&](StandInWorld& w) {
        w.si.install(kSceOpen, "sceOpen", [&](EEContext& ctx, StandIns&, StandInCall& c) {
            c.text = guest_str(ctx, c.args[0]);
            c.v0 = static_cast<u64>(open_ret);
        });
        w.si.install(kSceLseek, "sceLseek", [&](EEContext&, StandIns&, StandInCall& c) {
            c.v0 = (c.args[2] & 0xFFFFFFFFu) == 2 ? static_cast<u64>(kSize) : c.args[1];
        });
        w.si.install(kSceRead, "sceRead", [&](EEContext&, StandIns&, StandInCall& c) { c.v0 = static_cast<u64>(io_ret); });
        w.si.install(kSceWrite, "sceWrite", [&](EEContext&, StandIns&, StandInCall& c) { c.v0 = static_cast<u64>(io_ret); });
        w.si.install_recorder(kSceClose, "sceClose", 0);
        w.si.install_recorder(kSceSync, "sceSync", 0);
    };
    const auto fresh = [&](Machine& mm) {
        std::memset(mm.at(kFile), 0xCD, 144);
        wstr(mm, kName, "hdd:SAVE/P3.DAT");
    };
    u32 seed = 1;
    int opens = 0;
    for (u32 mode = 0; mode < 16; ++mode) {
        for (const s64 ret : {s64{7}, s64{-5}}) {
            open_ret = ret;
            SiPair sp = run_f8(m, base, kCases, "H_Cdvd_RtFsHdd_Fopen", {kScratch + 0x800, kFile, kName, mode}, seed++, fresh, pfs);
            ++opens;
            const auto o = log_of(sp, kSceOpen);
            REQUIRE(o.size() == 1);
            CHECK(o[0].text == "pfs0:SAVE/P3.DAT");
            u32 flags = 0;
            if ((mode & 3) == 3) {
                flags = 3;
            } else {
                if (mode & 1) flags = 1;
                if (mode & 2) flags |= 2;
            }
            if (mode & 4) flags |= 0x200;
            if ((mode & 2) && !(mode & 8)) flags |= 0x400;
            CHECK((o[0].args[1] & 0xFFFFFFFFu) == flags);
            CHECK((o[0].args[2] & 0xFFFFFFFFu) == 511u);
            CHECK(r32(m, kFile + hdd::kOpened) == 0u);
            CHECK(rs32(m, kFile + hdd::kFd) == static_cast<s32>(ret));
            if (ret >= 0) {
                CHECK(v0_of(sp.hw) == 1);
                CHECK(s64_at(m, kFile + hdd::kSize) == kSize);
                CHECK(s64_at(m, kFile + hdd::kPos) == 0);
                CHECK(r32(m, kFile + hdd::kIsOpen) == 1u);
                CHECK(count_of(sp, kSceLseek) == 2u);
            } else {
                CHECK(v0_of(sp.hw) == 3);
                CHECK(r32(m, kFile + hdd::kIsOpen) == 0xCDCDCDCDu);
                CHECK(count_of(sp, kSceLseek) == 0u);
            }
        }
    }
    // no name: 2, nothing opened (the path is built from the null name first: strcat of address 4)
    SiPair sp = run_f8(m, base, kCases, "H_Cdvd_RtFsHdd_Fopen", {0, kFile, 0, 1}, seed++, fresh, pfs);
    CHECK(v0_of(sp.hw) == 2);
    CHECK(count_of(sp, kSceOpen) == 0u);
    // an open file object
    const auto opened = [&](s64 pos) {
        return [&, pos](Machine& mm) {
            fresh(mm);
            w32(mm, kFile + hdd::kFd, 9);
            w64(mm, kFile + hdd::kPos, pos);
            w32(mm, kFile + hdd::kState, 2);
        };
    };
    for (const s64 ret : {s64{64}, s64{0}, s64{-1}}) {
        io_ret = ret;
        sp = run_f8(m, base, kCases, "H_Cdvd_RtFsHdd_FRead", {kFile, kBuf, 100, 0}, seed++, opened(1000), pfs);
        CHECK(v0_of(sp.hw) == (ret >= 0 ? ret : 0));
        CHECK(s64_at(m, kFile + hdd::kPos) == 1000 + (ret >= 0 ? ret : 0));
        CHECK(r32(m, kFile + hdd::kState) == (ret >= 0 ? 3u : 2u));
        REQUIRE(count_of(sp, kSceRead) == 1u);
        CHECK((log_of(sp, kSceRead)[0].args[0] & 0xFFFFFFFFu) == 9u);
        sp = run_f8(m, base, kCases, "sub_102B60", {kFile, kBuf, 100, 0}, seed++, opened(1000), pfs);
        CHECK(v0_of(sp.hw) == (ret >= 0 ? ret : 0));
        CHECK(s64_at(m, kFile + hdd::kPos) == 1000 + (ret >= 0 ? ret : 0));
        CHECK(r32(m, kFile + hdd::kState) == 2u);
    }
    for (u32 whence = 0; whence < 5; ++whence) {
        for (const s32 off : {0, 300, 5000, -2000}) {
            sp = run_f8(m, base, kCases, "sub_102BF0", {kResult, kFile, static_cast<u64>(static_cast<s64>(off)), whence}, seed++,
                        opened(1000), pfs);
            s64 want = -1;
            if (whence == 3) want = 1000 - off;
            if (whence == 2) want = 1000 + off;
            if (whence == 1) want = off;
            if (whence >= 1 && whence <= 3 && want < 0) want = 0;
            CHECK(s64_at(m, kFile + hdd::kPos) == want);
            CHECK(s64_at(m, kResult) == want);
            CHECK(std::memcmp(m.at(kResult), m.at(kFile + hdd::kPos), 16) == 0);
            CHECK(count_of(sp, kSceLseek) == (whence >= 1 && whence <= 3 ? 1u : 0u));
        }
    }
    for (const s64 ret : {s64{3}, s64{-2}}) {
        open_ret = ret;
        sp = run_f8(m, base, kCases, "sub_102D10", {kScratch + 0x800, kName, 0, 0}, seed++, fresh, pfs);
        CHECK(v0_of(sp.hw) == (ret >= 0 ? 1 : 0));
        CHECK(count_of(sp, kSceClose) == (ret >= 0 ? 1u : 0u));
        CHECK(log_of(sp, kSceOpen).at(0).text == "pfs0:SAVE/P3.DAT");
        CHECK((log_of(sp, kSceOpen).at(0).args[1] & 0xFFFFFFFFu) == 1u);
    }
    sp = run_f8(m, base, kCases, "sub_102A70", {kFile, 0, 0, 0}, seed++, opened(5), pfs);
    CHECK(r32(m, kFile + hdd::kState) == 1u);
    REQUIRE(count_of(sp, kSceClose) == 1u);
    CHECK((log_of(sp, kSceClose)[0].args[0] & 0xFFFFFFFFu) == 9u);
    CHECK(count_of(sp, kSceSync) == 1u);
    MESSAGE("hdd callbacks: " << opens << " opens, " << seed << " pairs");
}

// --- H_Memcard ---------------------------------------------------------------------------------------------------
// sceMc2CheckAsync stood in: it writes {cmd, result} through its first two arguments and answers `ret`.
struct McCheck {
    s64 ret = 1;
    u32 cmd = 0;
    s32 res = 0;
};
std::function<void(StandInWorld&)> mc_world(const McCheck& k) {
    return [k](StandInWorld& w) {
        w.si.install(kMcCheck, "sceMc2CheckAsync", [k](EEContext& ctx, StandIns&, StandInCall& c) {
            ctx.memory->write<u32>(static_cast<u32>(c.args[0]), k.cmd);
            ctx.memory->write<u32>(static_cast<u32>(c.args[1]), static_cast<u32>(k.res));
            c.v0 = static_cast<u64>(k.ret);
        });
        for (const u32 va : {kMcGetInfo, kMcSearch, kMcFormat, kMcMkdir, kMcCreate, kMcWrite, kMcRead})
            w.si.install_recorder(va, "sceMc2 request", 0);
    };
}

// H_Memcard_Check's rule: finished (1) -> ok = 1 when the result is 0 (commands 5 / 6: when it is not negative; there a
// negative one clears ok, elsewhere ok is left alone), a negative result keeps its low 16 bits; 0 / -1 / anything else
// come back as they are.
TEST_CASE("game(field8 sys): H_Memcard_Check's result rules") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kCmd = kScratch, kRes = kScratch + 4, kOk = kScratch + 8;
    u32 seed = 1;
    int n = 0;
    for (const s64 ret : {s64{1}, s64{0}, s64{-1}, s64{7}}) {
        for (const u32 cmd : {1u, 5u, 6u, 9u}) {
            for (const s32 res : {0, 3, -0x7FFE, -1}) {
                const McCheck k{ret, cmd, res};
                SiPair sp = run_f8(m, base, kCases, "H_Memcard_Check", {kCmd, kRes, kOk, 0}, seed++,
                                   [](Machine& mm) { w32(mm, kOk, 0x55u); }, mc_world(k));
                ++n;
                CHECK(v0_of(sp.hw) == ret);
                if (ret != 1) {
                    CHECK(r32(m, kOk) == 0x55u);
                    continue;
                }
                const bool long_cmd = cmd == 5 || cmd == 6;
                if (long_cmd) CHECK(r32(m, kOk) == (res >= 0 ? 1u : 0u));
                else CHECK(r32(m, kOk) == (res == 0 ? 1u : 0x55u));
                CHECK(r32(m, kRes) == (res < 0 ? (static_cast<u32>(res) & 0xFFFFu) : static_cast<u32>(res)));
            }
        }
    }
    MESSAGE("H_Memcard_Check: " << n << " pairs");
}

// The sequencers step by step on the ELF image: every mode of the save sequencer (0..13), the load sequencer and the
// slot scan / area check over their modes, with the check answering "busy", "idle" or "finished" with the libmc2 errors
// they switch on. Documented steps checked: save mode 0 issues GetInfo and goes to 1; mode 1 on a formatted PS2 card
// searches "/BASLUS-21621Save<slot>/BASLUS-21621Save<slot>" (the original P3 data's folder when the request word +46 is
// set) and goes to 2, an unformatted card goes to 3 answering 2; modes 4 / 5 / 9, once the card is idle, format (-> 5) /
// go to 6 / go to 6; the card check
// clears the cancel word and re-issues GetInfo, and maps a non-PS2 card to -1 and an unformatted one to -2.
TEST_CASE("game(field8 sys): the H_Memcard sequencers mode by mode") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const McCheck checks[] = {{0, 0, 0}, {-1, 0, 0}, {1, 1, 0}, {1, 1, 47}, {1, 1, 2}, {1, 1, 19}, {1, 1, -0x6FFF}, {1, 5, 0}};
    u32 seed = 1;
    int n = 0;
    const char* seqs[] = {"H_Memcard_UpdateSeqMode", "sub_190720", "sub_190CD0", "sub_191660", "sub_190590"};
    for (const char* fn : seqs) {
        for (u32 mode = 0; mode < 15; ++mode) {
            for (const McCheck& k : checks) {
                for (const u32 formatted : {0u, 1u}) {
                    if (formatted == 0 && mode != 1) continue;
                    SiPair sp = run_f8(m, base, kCases, fn, {0, 0, 0, 0}, seed++, [&](Machine& mm) {
                        w32(mm, kMcSeq, mode);
                        w32(mm, kMcSlotWord, 3);
                        w32(mm, kMcOrigWord, mode == 1 && formatted ? 1u : 0u);
                        w32(mm, kMcCancelWord, mode & 1);
                        w32(mm, kMcInfo, 2);
                        w32(mm, kMcInfo + 4, mode == 1 ? formatted : 1u);
                    }, mc_world(k));
                    ++n;
                    if (std::string(fn) != "H_Memcard_UpdateSeqMode") continue;
                    if (mode == 0 && k.ret == -1) {
                        CHECK(count_of(sp, kMcGetInfo) == 1u);
                        CHECK(r32(m, kMcSeq) == 1u);
                        CHECK(v0_of(sp.hw) == 0);
                    }
                    if (mode == 1 && k.ret == 1 && k.cmd == 1 && k.res == 0) {
                        if (formatted) {
                            CHECK(r32(m, kMcSeq) == 2u);
                            REQUIRE(count_of(sp, kMcSearch) == 1u);
                            CHECK(m.str(kMcPath, 64) == "/BASLUS-21569Save3/BASLUS-21569Save3");  // the +46 word is set
                        } else {
                            CHECK(r32(m, kMcSeq) == 3u);
                            CHECK(v0_of(sp.hw) == 2);
                        }
                    }
                    if (mode == 4 && k.ret == -1) {
                        CHECK(count_of(sp, kMcFormat) == 1u);
                        CHECK(r32(m, kMcSeq) == 5u);
                    }
                    if ((mode == 5 || mode == 9) && k.ret == -1) CHECK(r32(m, kMcSeq) == 6u);
                }
            }
        }
    }
    // the card check's cancel path and its card-type answers
    for (const u32 type : {2u, 1u}) {
        for (const u32 formatted : {1u, 0u}) {
            SiPair sp = run_f8(m, base, kCases, "sub_190590", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
                w32(mm, kMcCancelWord, 0);
                w32(mm, kMcInfo, type);
                w32(mm, kMcInfo + 4, formatted);
            }, mc_world({1, 1, 0}));
            ++n;
            CHECK(count_of(sp, kMcGetInfo) == 1u);
            CHECK(v0_of(sp.hw) == (type != 2 ? -1 : formatted ? 0 : -2));
        }
    }
    SiPair sp = run_f8(m, base, kCases, "sub_190590", {0, 0, 0, 0}, seed++, [&](Machine& mm) { w32(mm, kMcCancelWord, 1); },
                       mc_world({-1, 0, 0}));
    CHECK(r32(m, kMcCancelWord) == 0u);
    CHECK(count_of(sp, kMcGetInfo) == 1u);
    MESSAGE("H_Memcard sequencers: " << n << " pairs");
}

// H_Memcard_Init: the socket parameters {2, 2, 0} and the socket handle the library answers.
TEST_CASE("game(field8 sys): H_Memcard_Init, H_Pad_Init and H_Sndcom_Init set up their records") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    // (sceMc2CreateSocket is hand-written since finalA: stood in explicitly, as the absent recorder served it before)
    SiPair sp = run_f8(m, base, kCases, "H_Memcard_Init", {0, 0, 0, 0}, 1, {},
                       [](StandInWorld& w) { w.si.install_recorder(0x513368u, "sceMc2CreateSocket", 0x4242); }, 0x4242);
    CHECK(r32(m, 0x7CE024u) == 0x4242u);
    CHECK(r32(m, 0x846EB0u) == 2u);
    CHECK(r32(m, 0x846EB4u) == 2u);
    CHECK(r32(m, 0x846EB8u) == 0u);
    // pads: both 54-byte state records get their port, +4 = 3, the rest of the words cleared; both ports opened
    // (scePadInit / scePadPortOpen are hand-written since finalA: stood in explicitly, as the absent recorders served
    // them before)
    sp = run_f8(m, base, kCases, "H_Pad_Init", {0, 0, 0, 0}, 2, [](Machine& mm) {
        std::memset(mm.at(0x7E0940u), 0xEE, 0x7E0A1Cu - 0x7E0940u);
    }, [](StandInWorld& w) {
        w.si.install_recorder(0x511138u, "scePadInit", 0);
        w.si.install_recorder(kPadPortOpen, "scePadPortOpen", 0);
    });
    for (u32 port = 0; port < 2; ++port) {
        const u32 rec = 0x7E09B0u + 54u * port;
        CHECK(r16(m, rec + 8) == port);
        CHECK(r16(m, rec + 4) == 3u);
        CHECK(r16(m, rec + 0) == 0u);
        CHECK(r16(m, rec + 2) == 0u);
        CHECK(r16(m, rec + 10) == 0u);
    }
    for (u32 va = 0x7E0940u; va < 0x7E09ACu; ++va) CHECK(r8(m, va) == 0u);  // the two previous-frame copies
    const auto opens = log_of(sp, kPadPortOpen);
    REQUIRE(opens.size() == 2u);
    CHECK(static_cast<u32>(opens[0].args[2]) == 0x7E0840u);
    CHECK(static_cast<u32>(opens[1].args[0]) == 1u);
    CHECK(static_cast<u32>(opens[1].args[2]) == 0x7E0740u);
    // h_sndcom: six slots {state 0, +4 0, bound 0, own index}, the SPU2 RAM blocks 614,400 / 716,800 / 4 x 102,400
    sp = run_f8(m, base, kCases, "H_Sndcom_Init", {0, 0, 0, 0}, 3, [](Machine& mm) { std::memset(mm.at(kSlots), 0xEE, 68 * 6); },
                [](StandInWorld& w) {
                    w.si.install(kSpuAlloc, "sceSpu2MemAllocate", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0] + 0x100; });
                });
    const auto allocs = log_of(sp, kSpuAlloc);
    REQUIRE(allocs.size() == 6u);
    const u32 sizes[6] = {614400, 716800, 102400, 102400, 102400, 102400};
    for (u32 i = 0; i < 6; ++i) {
        const u32 slot = kSlots + 68u * i;
        CHECK(static_cast<u32>(allocs[i].args[0]) == sizes[i]);
        CHECK(r16(m, slot) == 0u);
        CHECK(r32(m, slot + 4) == 0u);
        CHECK(r32(m, slot + 24) == 0u);
        CHECK(r16(m, slot + 10) == i);
        CHECK(r32(m, slot + 36) == sizes[i] + 0x100u);
    }
    CHECK(r32(m, 0x833698u) == 0u);
}

// --- the SE voices -----------------------------------------------------------------------------------------------
// H_Sndcom_PlayVoice / StopVoice over the slot states: only an idle (1), bound slot plays or stops; a voice still
// playing is stopped first (Status + Control 2 with its handle); a new voice records its slot and the handle the
// driver answers (Control 0, 10, sequence, a3).
TEST_CASE("game(field8 sys): the SE voices of h_sndcom") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const auto driver = [](StandInWorld& w) {
        w.si.install_recorder(kSesqStatus, "SESQ_Status", 0);
        w.si.install_recorder(kSesqControl, "SESQ_Control", 0x77);
    };
    u32 seed = 1;
    for (const u16 state : {u16{1}, u16{2}}) {
        for (const u32 bound : {1u, 0u}) {
            for (const u32 active : {0u, 1u}) {
                const auto world = [&](Machine& mm) {
                    const u32 slot = kSlots + 68u * 2;
                    w16(mm, slot, state);
                    w32(mm, slot + 24, bound);
                    w32(mm, slot + 16, 0x31);
                    w32(mm, kVoices + 12u * 5, active);
                    w32(mm, kVoices + 12u * 5 + 8, 0x99);
                };
                SiPair sp = run_f8(m, base, kCases, "H_Sndcom_PlayVoice", {2, 5, 40, 3}, seed++, world, driver);
                const bool live = state == 1 && bound;
                const auto ctl = log_of(sp, kSesqControl);
                CHECK(ctl.size() == (live ? (active ? 2u : 1u) : 0u));
                if (live) {
                    CHECK((ctl.back().args[0] & 0xFFFFFFFFu) == 0x31u);
                    CHECK((ctl.back().args[1] & 0xFFFFFFFFu) == 0u);
                    CHECK((ctl.back().args[3] & 0xFFFFFFFFu) == 40u);
                    CHECK(r32(m, kVoices + 12u * 5) == 1u);
                    CHECK(r16(m, kVoices + 12u * 5 + 4) == 2u);
                    CHECK(r32(m, kVoices + 12u * 5 + 8) == 0x77u);
                    if (active) CHECK((ctl.front().args[3] & 0xFFFFFFFFu) == 0x99u);
                }
                sp = run_f8(m, base, kCases, "H_Sndcom_StopVoice", {2, 5, 0, 0}, seed++, world, driver);
                CHECK(count_of(sp, kSesqControl) == (live && active ? 1u : 0u));
                CHECK(count_of(sp, kSesqStatus) == (live && active ? 1u : 0u));
                CHECK(r32(m, kVoices + 12u * 5) == (live ? 0u : active));
            }
        }
    }
}

// --- the per-frame sound pump ------------------------------------------------------------------------------------
// sub_108BC0 on the dorm snapshot's channel records, the ADXT status stood in: status 3 (finished) leaves every active
// channel inactive; another status starts the pending plays of channels 2..5 (+12 == 3 -> the channel start, == 2 ->
// the restart thunk) and marks them started (+12 = 1).
TEST_CASE("game(field8 sys): the sound pump's channel rules (dorm snapshot)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kCh = 0x7E4430u, kChSize = 308;
    u32 seed = 1;
    for (const u64 status : {3ull, 0ull, 1ull}) {
        for (const u16 pending : {u16{3}, u16{2}, u16{0}}) {
            SiPair sp = run_f8(m, base, kCases, "sub_108BC0", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
                for (u32 ch = 2; ch < 6; ++ch) {
                    w32(mm, kCh + kChSize * ch, ch & 1);
                    w16(mm, kCh + kChSize * ch + 12, pending);
                }
            }, [status](StandInWorld& w) { w.si.install_recorder(0x54D148u, "ADXT status", status); });
            for (u32 ch = 2; ch < 6; ++ch) {
                const u32 rec = kCh + kChSize * ch;
                if (!(ch & 1)) {
                    CHECK(r32(m, rec) == 0u);
                    CHECK(r16(m, rec + 12) == pending);
                } else if (status == 3) {
                    CHECK(r32(m, rec) == 0u);
                } else {
                    CHECK(r32(m, rec) == 1u);
                    CHECK(r16(m, rec + 12) == (pending == 3 || pending == 2 ? 1u : 0u));
                }
            }
        }
    }
}

// --- the resource-manager thread ---------------------------------------------------------------------------------
// The per-frame pump on built request lists: finished requests are skipped; a new request with a file name gets its
// H_Cdvd request (the fake file layer's node) and state 1; one without a file is handed over at once; a loading one is
// handed over once its node is loaded (and only then); a request with the thread counts its frames. Handing over: the
// control block {go 1, request}, state 2, the worker woken (its thread id).
TEST_CASE("game(field8 sys): the resource manager's pump, init, suspend / resume and worker thread") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    namespace rm = game::f8::resman;
    constexpr u32 kA = kScratch, kB = kScratch + 0x200, kNodeVa = kScratch + 0x800, kData = kScratch + 0x1000;
    const auto request = [](Machine& mm, u32 r, u32 next, u32 state, const char* name) {
        std::memset(mm.at(r), 0, 476);
        w32(mm, r + rm::kNext, next);
        w32(mm, r + rm::kState, state);
        if (name) wstr(mm, r + rm::kFileName, name);
    };
    u32 seed = 1;
    // head: a finished request, then the request under test
    for (u32 state = 0; state < 4; ++state) {
        for (const bool named : {true, false}) {
            for (const bool loaded : {true, false}) {
                SiPair sp = run_f8(m, base, kCases, "H_ResrcMan_Update", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
                    w32(mm, kReqList, kA);
                    w32(mm, kThreadId, 42);
                    std::memset(mm.at(kControl), 0, 8);
                    request(mm, kA, kB, 3, nullptr);
                    request(mm, kB, 0, state, named ? "field/pack/F004_001.PAC" : nullptr);
                    w16(mm, kB + rm::kFramesWaited, 5);
                    if (state == 1) {
                        make_loaded_node(mm, kNodeVa, kData, {1, 2, 3, 4});
                        if (!loaded) w32(mm, kNodeVa + 12, 1);
                        w32(mm, kB + rm::kNode, kNodeVa);
                    }
                }, [](StandInWorld& w) { w.si.install_recorder(kWakeup, "_sceWakeupThread", 0); });  // hand-written since finalA
                const bool handed = (state == 0 && !named) || (state == 1 && loaded);
                if (state == 0 && named) {
                    CHECK(r32(m, kB + rm::kState) == 1u);
                    CHECK(sp.recomp->cd.nodes.size() == 1u);
                    CHECK(r32(m, kB + rm::kNode) != 0u);
                }
                if (state == 2) CHECK(r16(m, kB + rm::kFramesWaited) == 6u);
                if (state == 3) CHECK(count_of(sp, kWakeup) == 0u);
                CHECK(count_of(sp, kWakeup) == (handed ? 1u : 0u));
                if (handed) {
                    CHECK((log_of(sp, kWakeup)[0].args[0] & 0xFFFFFFFFu) == 42u);
                    CHECK(r16(m, kControl) == 1u);
                    CHECK(r32(m, kControl + 4) == kB);
                    CHECK(r32(m, kB + rm::kState) == 2u);
                }
                if (state == 1 && !loaded) CHECK(r32(m, kB + rm::kState) == 1u);
            }
        }
    }
    // init: the 256 records' first words, the worker's list, the thread {entry, stack, size, $gp, priority}
    SiPair sp = run_f8(m, base, kCases, "H_ResrcMan_Init", {0, 0, 0, 0}, seed++, [](Machine& mm) {
        std::memset(mm.at(kReqRecords), 0xEE, 476 * 256);
        std::memset(mm.at(kReqList), 0xEE, 8);
        std::memset(mm.at(kControl), 0xEE, 8);
    }, [](StandInWorld& w) {
        // the thread parameters live in the caller's frame: read them at the call
        w.si.install(kCreateThread, "CreateThread", [](EEContext& ctx, StandIns&, StandInCall& c) {
            std::string words;
            for (u32 i = 1; i < 6; ++i) words += std::to_string(ctx.memory->read<u32>(static_cast<u32>(c.args[0]) + 4 * i)) + " ";
            c.text = words;
            c.v0 = 0x2A;
        });
        // (StartThread is hand-written since finalA: stood in explicitly, as the absent recorder served it before)
        w.si.install_recorder(kStartThread, "StartThread", 0);
    });
    for (u32 i = 0; i < 256; ++i) CHECK(r32(m, kReqRecords + 476u * i) == 0u);
    CHECK(r32(m, kReqList) == 0u);
    CHECK(r32(m, kReqList + 4) == 0u);
    CHECK(r16(m, kControl) == 0u);
    CHECK(r32(m, kThreadId) == 0x2Au);
    CHECK(r32(m, kStarted) == 1u);
    const auto created = log_of(sp, kCreateThread);
    REQUIRE(created.size() == 1u);
    // {entry H_Resman_ThreadProc, stack 0x803640, 0x20000 bytes, $gp 0x7D2CF0, priority 28}
    CHECK(created[0].text == std::to_string(0x10C7D0u) + " " + std::to_string(0x803640u) + " " + std::to_string(0x20000u) + " " +
                                 std::to_string(0x7D2CF0u) + " 28 ");
    REQUIRE(count_of(sp, kStartThread) == 1u);
    CHECK(static_cast<u32>(log_of(sp, kStartThread)[0].args[1]) == kControl);
    // suspend / resume: only once the worker exists; a sleeping (8) or dormant (12) worker is not suspended
    for (const u32 started : {0u, 1u}) {
        for (const u32 status : {16u, 8u, 12u, 2u}) {
            sp = run_f8(m, base, kCases, "sub_10BF70", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
                w32(mm, kStarted, started);
                w32(mm, kThreadId, 7);
            }, [status](StandInWorld& w) {
                w.si.install(kReferStatus, "ReferThreadStatus", [status](EEContext& ctx, StandIns&, StandInCall& c) {
                    ctx.memory->write<u32>(static_cast<u32>(c.args[1]), status);
                    c.v0 = 0;
                });
                // (_sceSuspendThread is hand-written since finalA: stood in explicitly, as the absent recorder was)
                w.si.install_recorder(kSuspend, "_sceSuspendThread", 0);
            });
            CHECK(count_of(sp, kSuspend) == (started && status != 8 && status != 12 ? 1u : 0u));
        }
        sp = run_f8(m, base, kCases, "H_ResrcMan_MaybeResumeThread", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
            w32(mm, kStarted, started);
            w32(mm, kThreadId, 7);
        }, [](StandInWorld& w) { w.si.install_recorder(kResume, "_sceResumeThread", 0); });  // hand-written since finalA
        CHECK(count_of(sp, kResume) == started);
    }
    // the worker: woken with a request of each kind chained to a second (new, no file) one; both are served by their
    // kind's loader, their nodes destroyed, marked done (3), and the worker goes back to sleep (go = 0), where the
    // second sleep ends the run.
    int served = 0;
    // (on the dorm snapshot: RenderWare is up there, so the hand-written RenderWare callees the loaders reach run on
    // its real globals instead of the ELF image's null function slots)
    std::vector<u8> dbase;
    auto dmp = real_machine("dorm_replay_4900", dbase);
    if (!dmp) {
        MESSAGE("SKIP (the worker): no dorm_replay_4900 snapshot");
        return;
    }
    Machine& dm = *dmp;
    // (kinds 3, 4, 5, 7, 8 and kind 2 with +456 run hand-written RenderWare stream readers that need real streams; the
    // kinds served here reach the texture-path setter sub_4CC5C0 and the stream readers sub_490050 / sub_4920A0 --
    // hand-written since render_rw9, run on the snapshot's RenderWare with the request's empty name / data -- or loaders
    // this build does not emit, recorded; 10 is past the table)
    const u32 kinds[] = {0, 1, 2, 6, 9, 10};
    for (const u32 kind : kinds) {
        const auto world = [&](Machine& mm) {
            std::memset(mm.at(kControl), 0, 8);
            request(mm, kA, kB, 2, nullptr);
            request(mm, kB, 0, 0, nullptr);
            w32(mm, kA + rm::kKind, kind);
            w32(mm, kB + rm::kKind, kind == 10 ? 6u : kinds[(kind + 1) % 5]);
            make_loaded_node(mm, kNodeVa, kData, {9, 9});
            w32(mm, kA + rm::kNode, kNodeVa);
        };
        sp = run_f8(dm, dbase, &thread_hand, &thread_recomp, {kControl, 0, 0, 0}, seed++, "H_Resman_ThreadProc", world,
                    [&](StandInWorld& w) {
                        auto sleeps = std::make_shared<int>(0);
                        Machine* mm = &dm;
                        w.si.install(kSleep, "SleepThread (the test's waker)", [sleeps, mm](EEContext&, StandIns&, StandInCall& c) {
                            c.v0 = 0;
                            if (++*sleeps == 1) {
                                w16(*mm, kControl, 1);
                                w32(*mm, kControl + 4, kA);
                                return;
                            }
                            throw F8Stop{};
                        });
                    }, 0x5150);
        ++served;
        CHECK(r16(dm, kControl) == 0u);
        CHECK(r32(dm, kA + rm::kState) == 3u);
        CHECK(r32(dm, kB + rm::kState) == 3u);
        CHECK(r32(dm, kA + rm::kNode) == 0u);
        CHECK(r32(dm, kControl + 4) == kB);
        REQUIRE(count_of(sp, kHCdvdDestroyFn) == 1u);  // only the first request had a node
        CHECK(static_cast<u32>(log_of(sp, kHCdvdDestroyFn)[0].args[0]) == kNodeVa);
        CHECK(sp.recomp->si.calls_to(kSleep) == 1u);  // the second (throwing) call is not logged
    }
    MESSAGE("resource manager: " << seed << " pairs, the worker over " << served << " kinds");
}

// --- the VBlank gate, the assert stubs ---------------------------------------------------------------------------
TEST_CASE("game(field8 sys): the VBlank gate installer and the K_Assert / K_Abort stubs") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    // the gate: AddIntcHandler(2, kwlnVsyncFieldGate, 0) fails -> 0; EnableIntc fails -> handler removed, id -1, 0
    for (const s64 id : {s64{-1}, s64{3}}) {
        for (const s64 en : {s64{-1}, s64{1}}) {
            SiPair sp = run_f8(m, base, kCases, "kwlnInstallVsyncFieldGate", {0, 0, 0, 0}, seed++, {}, [&](StandInWorld& w) {
                w.si.install_recorder(kAddIntc, "AddIntcHandler", static_cast<u64>(id));
                w.si.install_recorder(kEnableIntc, "EnableIntc", static_cast<u64>(en));
                w.si.install_recorder(kRemoveIntc, "RemoveIntcHandler", 0);
            });
            const auto add = log_of(sp, kAddIntc);
            REQUIRE(add.size() == 1u);
            CHECK((add[0].args[0] & 0xFFFFFFFFu) == 2u);
            CHECK((add[0].args[1] & 0xFFFFFFFFu) == 0x19D320u);
            const bool ok = id >= 0 && en >= 0;
            CHECK(v0_of(sp.hw) == (ok ? 1 : 0));
            CHECK(rs32(m, 0x7CC148u) == (ok ? 3 : -1));
            CHECK(count_of(sp, kEnableIntc) == (id >= 0 ? 1u : 0u));
            CHECK(count_of(sp, kRemoveIntc) == (id >= 0 && en < 0 ? 1u : 0u));
        }
    }
    // the stubs return at once: nothing written, two cycles
    for (const char* fn : {"sub_19D3F0", "sub_19D400"}) {
        SiPair sp = run_f8(m, base, kCases, fn, {0x5D0000, 123, 0, 0}, seed++, {});
        CHECK(sp.hw.recomp.base.cycles == 2u);
        CHECK(sp.hw.recomp.base.checks == 1);
    }
}

#else

TEST_CASE("game(field8 sys): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
