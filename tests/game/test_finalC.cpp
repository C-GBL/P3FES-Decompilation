// Pair tests for slice finalC (skeleton written by p3fes_handgen; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// Every body against its recompiled body on random worlds, compared by tests/game/handgen_pairs.h: the whole register
// file and cycle count at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS
// window and the bus log. Then the documented rules of each function on real structures: the kernel syscall numbers,
// the serial and INTC registers, the libc stdio request packet and its RPC, the pad RPC buffer, dvCi's cache-file
// table and the IPU / scratchpad DMA kicks, with the kernel semaphores, the IOP RPCs, the cache sync, the CD sync and
// the dvCi output stood in (recorders whose call logs both bodies must match).
#include "libs1_util.h"

#include "p3fes/game/finalC.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::libs1;

namespace p3fes::recomp_gen {
void fn__sce_GetGsDxDyOffset_004f9158(EEContext&);  // generated body
void fn__sce_GetGsDxDyOffset_004f9158__recomp(EEContext&);  // recompiled
void fn__sendDataToIPU_005000b0(EEContext&);  // generated body
void fn__sendDataToIPU_005000b0__recomp(EEContext&);  // recompiled
void fn__cpr8_00501178(EEContext&);  // generated body
void fn__cpr8_00501178__recomp(EEContext&);  // recompiled
void fn__sceSetVTLBRefillHandler_00502e10(EEContext&);  // generated body
void fn__sceSetVTLBRefillHandler_00502e10__recomp(EEContext&);  // recompiled
void fn__sceSetVCommonHandler_00502e20(EEContext&);  // generated body
void fn__sceSetVCommonHandler_00502e20__recomp(EEContext&);  // recompiled
void fn_kputchar_00504bc0(EEContext&);  // generated body
void fn_kputchar_00504bc0__recomp(EEContext&);  // recompiled
void fn_sceRead_00508cb8(EEContext&);  // generated body
void fn_sceRead_00508cb8__recomp(EEContext&);  // recompiled
void fn_sceWrite_00508f28(EEContext&);  // generated body
void fn_sceWrite_00508f28__recomp(EEContext&);  // recompiled
void fn_sceIoctl_005091e8(EEContext&);  // generated body
void fn_sceIoctl_005091e8__recomp(EEContext&);  // recompiled
void fn_sceSync_0050a888(EEContext&);  // generated body
void fn_sceSync_0050a888__recomp(EEContext&);  // recompiled
void fn_sceLseek64_0050acd8(EEContext&);  // generated body
void fn_sceLseek64_0050acd8__recomp(EEContext&);  // recompiled
void fn__sce_SetTLBEntry_0050cd60(EEContext&);  // generated body
void fn__sce_SetTLBEntry_0050cd60__recomp(EEContext&);  // recompiled
void fn_Exit_0050da58(EEContext&);  // generated body
void fn_Exit_0050da58__recomp(EEContext&);  // recompiled
void fn_scePadSetButtonInfo_005122c0(EEContext&);  // generated body
void fn_scePadSetButtonInfo_005122c0__recomp(EEContext&);  // recompiled
void fn_dvci_search_fstate_0055aea0(EEContext&);  // generated body
void fn_dvci_search_fstate_0055aea0__recomp(EEContext&);  // recompiled
void fn_sub_77FFA0_0077ffa0(EEContext&);  // generated body
void fn_sub_77FFA0_0077ffa0__recomp(EEContext&);  // recompiled
void fn_sub_7CC670_007cc670(EEContext&);  // generated body
void fn_sub_7CC670_007cc670__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"_sce_GetGsDxDyOffset", 0x4F9158, &recomp_gen::fn__sce_GetGsDxDyOffset_004f9158, &recomp_gen::fn__sce_GetGsDxDyOffset_004f9158__recomp},
    {"_sendDataToIPU", 0x5000B0, &recomp_gen::fn__sendDataToIPU_005000b0, &recomp_gen::fn__sendDataToIPU_005000b0__recomp},
    {"_cpr8", 0x501178, &recomp_gen::fn__cpr8_00501178, &recomp_gen::fn__cpr8_00501178__recomp},
    {"_sceSetVTLBRefillHandler", 0x502E10, &recomp_gen::fn__sceSetVTLBRefillHandler_00502e10, &recomp_gen::fn__sceSetVTLBRefillHandler_00502e10__recomp},
    {"_sceSetVCommonHandler", 0x502E20, &recomp_gen::fn__sceSetVCommonHandler_00502e20, &recomp_gen::fn__sceSetVCommonHandler_00502e20__recomp},
    {"kputchar", 0x504BC0, &recomp_gen::fn_kputchar_00504bc0, &recomp_gen::fn_kputchar_00504bc0__recomp},
    {"sceRead", 0x508CB8, &recomp_gen::fn_sceRead_00508cb8, &recomp_gen::fn_sceRead_00508cb8__recomp},
    {"sceWrite", 0x508F28, &recomp_gen::fn_sceWrite_00508f28, &recomp_gen::fn_sceWrite_00508f28__recomp},
    {"sceIoctl", 0x5091E8, &recomp_gen::fn_sceIoctl_005091e8, &recomp_gen::fn_sceIoctl_005091e8__recomp},
    {"sceSync", 0x50A888, &recomp_gen::fn_sceSync_0050a888, &recomp_gen::fn_sceSync_0050a888__recomp},
    {"sceLseek64", 0x50ACD8, &recomp_gen::fn_sceLseek64_0050acd8, &recomp_gen::fn_sceLseek64_0050acd8__recomp},
    {"_sce_SetTLBEntry", 0x50CD60, &recomp_gen::fn__sce_SetTLBEntry_0050cd60, &recomp_gen::fn__sce_SetTLBEntry_0050cd60__recomp},
    {"Exit", 0x50DA58, &recomp_gen::fn_Exit_0050da58, &recomp_gen::fn_Exit_0050da58__recomp},
    {"scePadSetButtonInfo", 0x5122C0, &recomp_gen::fn_scePadSetButtonInfo_005122c0, &recomp_gen::fn_scePadSetButtonInfo_005122c0__recomp},
    {"dvci_search_fstate", 0x55AEA0, &recomp_gen::fn_dvci_search_fstate_0055aea0, &recomp_gen::fn_dvci_search_fstate_0055aea0__recomp},
    {"sub_77FFA0", 0x77FFA0, &recomp_gen::fn_sub_77FFA0_0077ffa0, &recomp_gen::fn_sub_77FFA0_0077ffa0__recomp},
    {"sub_7CC670", 0x7CC670, &recomp_gen::fn_sub_7CC670_007cc670, &recomp_gen::fn_sub_7CC670_007cc670__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (the random sweep, and the buffers of the rule checks).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

// --- the libc stdio layer (sceRead / sceWrite / sceIoctl / sceSync / sceLseek64) ------------------------------------
constexpr u32 kFsInitDone = 0x77F53Cu;  // sceFsInit has run
constexpr u32 kSemaSlots = 0x77F4B8u;   // 32 semaphore ids of the non-blocking requests in flight (-1 = free)
constexpr u32 kSlotLock = 0x77F54Cu;    // the semaphore guarding them
constexpr u32 kIobLock = 0x77F548u;     // the iob table's semaphore (get_iob)
constexpr u32 kIob = 0x969A00u;         // 32 iobs of 16 bytes: +0 the IOP fd, +4 the flags
constexpr u32 kPacket = 0x968500u;      // the request packet: +0 sema, +4 the result slot, +8 = 4, +0xC the IOP fd ...
constexpr u32 kReply = 0x969140u;       // the 4-byte RPC reply
constexpr u32 kFsClient = 0x969C00u;    // the file service's RPC client
constexpr u32 kFsWaitS = 0x508048u, kFsSigSema = 0x508078u, kCreateSema = 0x503160u, kDeleteSema = 0x503170u;
constexpr u32 kWaitSema = 0x5031A0u, kSignalSema = 0x503180u, kSyncBuf = 0x5067F8u, kFsInit = 0x508170u;
constexpr u32 kFsCallRpc = 0x507AD8u;
constexpr u64 kSemaId = 7;

struct Io {
    s32 rpc = 0;         // what sceFsSifCallRpc answers
    u32 reply = 1;       // the 4-byte reply it leaves (0 = the request was not taken: -11)
    u64 result = 42;     // what it stores into the result slot (the IOP's byte count / position)
};
Setup stdio_world(Io o = {}) {
    return [o](StandInWorld& w) {
        w.si.install_recorder(kFsWaitS, "_sceFsWaitS", 0);
        w.si.install_recorder(kFsSigSema, "_sceFsSigSema", 0);
        w.si.install_recorder(kCreateSema, "_sceCreateSema", kSemaId);
        w.si.install_recorder(kDeleteSema, "_sceDeleteSema", 0);
        w.si.install_recorder(kWaitSema, "_sceWaitSema", 0);
        w.si.install_recorder(kSignalSema, "_sceSignalSema", 0);
        w.si.install_recorder(kSyncBuf, "sub_5067F8", 0);
        w.si.install_recorder(kFsInit, "sceFsInit", 0);
        w.si.install(kFsCallRpc, "sceFsSifCallRpc", [o](EEContext& ctx, StandIns&, StandInCall& c) {
            // (client, command, mode, packet, size, reply, 4, end fn, end arg): the IOP answers into the reply word
            // and the result slot the packet names at +4.
            const u32 packet = static_cast<u32>(c.args[3]), reply = static_cast<u32>(c.args[5]);
            ctx.memory->write<u32>(reply, o.reply);
            ctx.memory->write<u64>(gu32(ctx, packet + 4), o.result);
            c.v0 = sx(static_cast<u32>(o.rpc));
        });
    };
}
HwCheck stdio_ranges() {
    HwCheck hw;
    hw.ranges = {{kPacket, 0x440u}, {kReply, 16u}, {kIob, 0x200u}, {kSemaSlots, 0x94u}, {kWorld, 0x1000u}};
    return hw;
}
void stdio_state(Machine& m, u32 fd, u32 iop_fd, u32 flags, bool init_done = true) {
    w32(m, kFsInitDone, init_done ? 1u : 0u);
    wzero(m, kIob, 0x200);
    w32(m, kIob + 16 * fd, iop_fd);
    w32(m, kIob + 16 * fd + 4, flags);
    for (u32 i = 0; i < 32; ++i) w32(m, kSemaSlots + 4 * i, 0xFFFFFFFFu);
    w32(m, kSlotLock, 0x55);
    w32(m, kIobLock, 0x66);
    wzero(m, kPacket, 0x440);
    w32(m, kReply, 0);
}
std::vector<StandInCall> calls(u32 va) {
    std::vector<StandInCall> out;
    for (const StandInCall& c : last_log().log)
        if (c.va == va) out.push_back(c);
    return out;
}
std::vector<std::pair<u32, u32>> hw_writes(const hgp::Run& r, u32 lo, u32 hi) {
    std::vector<std::pair<u32, u32>> out;
    for (const auto& a : r.bus)
        if (a.write && a.pa >= lo && a.pa < hi) out.emplace_back(static_cast<u32>(a.pa), static_cast<u32>(a.lo));
    return out;
}
const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }
u64 v1_of(const hgp::Run& r) { return r.end.gpr[GPR_V1].u64[0]; }

}  // namespace

TEST_CASE("game(finalC): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, kSeeds, {});
}

TEST_CASE("game(finalC): syscall wrappers, Exit, kputchar, the alarm payload body and the data-band break word") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    // The kernel syscall wrappers: one syscall with its number in $v1 (the harness answers 0x600DF00D in $v0).
    for (const auto& [name, num] : {std::pair<const char*, u32>{"_sce_GetGsDxDyOffset", 128}, {"_sceSetVTLBRefillHandler", 13},
                                    {"_sceSetVCommonHandler", 14}, {"_sce_SetTLBEntry", 86}}) {
        const hgp::Run r = pair(*m, C(name), Args{1, 2, 3, 4}, 1, name);
        INFO(name);
        CHECK_FALSE(r.stopped);
        CHECK(r.syscalls == 1);
        CHECK(v1_of(r) == sx(num));
        CHECK(v0_of(r) == 0x600DF00Du);
    }
    // Exit: the exit hook (sub_50D998, stood in) sees the status, then syscall 4 (Exit) gets it back in $a0.
    {
        const hgp::Run r = pair(*m, C("Exit"), Args{3, 0, 0, 0}, 1, "Exit", [](StandInWorld& w) {
            w.si.install_recorder(0x50D998u, "sub_50D998", 0);
        });
        CHECK_FALSE(r.stopped);
        CHECK(r.syscalls == 1);
        CHECK(v1_of(r) == 4u);
        CHECK(r.end.gpr[4].u64[0] == 3u);
        const auto hook = calls(0x50D998u);
        REQUIRE(hook.size() == 1u);
        CHECK(hook[0].args[0] == 3u);
    }
    // kputchar: spins while SIO_ISR bit 15 (TX FIFO full) is set, then the byte goes to SIO_TXFIFO; $v0 = the byte.
    {
        HwCheck hw;
        hw.reads[0x1000F130u] = {0x8000u, 0x8000u, 0u};
        const hgp::Run r = pair(*m, C("kputchar"), Args{0x41, 0, 0, 0}, 1, "kputchar", {}, hw);
        CHECK_FALSE(r.stopped);
        CHECK(count_access(r.bus, 0x1000F130u, false) == 3u);
        const auto w = hw_writes(r, 0x1000F000u, 0x10010000u);
        REQUIRE(w.size() == 1u);
        CHECK(w[0] == std::pair<u32, u32>{0x1000F180u, 0x41u});
        CHECK(v0_of(r) == 0x41u);
    }
    // sub_77FFA0 (the alarm kernel payload's body): INTC_STAT bit 2 acknowledged, spun on until set, acknowledged
    // again, then the payload's seven table entries at 0x8007474C.. called in the order +0x4760, +0x4764 (1, 2, 1),
    // +0x474C (0xDFFD), +0x4750, +0x475C (127), +0x4754, +0x4758; $v0 = the last one's result. The table points at
    // the payload blob's own 8-byte stubs (symbols/ functions: an indirect call needs one), each stood in by a
    // recorder.
    {
        const u32 stubs[7] = {0x77F598u, 0x77F5F8u, 0x77F65Cu, 0x77F67Cu, 0x77F6B4u, 0x77F704u, 0x77FF10u};
        for (u32 k = 0; k < 7; ++k) w32(*m, 0x7474Cu + 4 * k, stubs[k]);
        HwCheck hw;
        hw.reads[0x1000F000u] = {0u, 0u, 4u};
        const auto table = [stubs](StandInWorld& w) {
            for (u32 k = 0; k < 7; ++k) w.si.install_recorder(stubs[k], "payload entry " + std::to_string(k), 0x100u + k);
        };
        const hgp::Run r = pair(*m, C("sub_77FFA0"), Args{0, 0, 0, 0}, 1, "sub_77FFA0", table, hw);
        CHECK_FALSE(r.stopped);
        int acks = 0;
        for (const auto& a : r.bus)
            if (a.write && a.pa == 0x1000F000u && (a.lo & 0xFFFFFFFFu) == 4u) ++acks;
        CHECK(acks == 2);
        CHECK(count_access(r.bus, 0x1000F000u, false) == 3u);
        const auto& log = last_log().log;
        REQUIRE(log.size() == 7u);
        const u32 order[7] = {5, 6, 0, 1, 4, 2, 3};
        for (std::size_t i = 0; i < 7; ++i) CHECK(log[i].va == stubs[order[i]]);
        CHECK(log[1].args[0] == 1u);
        CHECK(log[1].args[1] == 2u);
        CHECK(log[1].args[2] == 1u);
        CHECK(log[2].args[0] == 0xDFFDu);
        CHECK(log[4].args[0] == 127u);
        CHECK(v0_of(r) == 0x103u);
    }
    // sub_7CC670: one `break` word in the data band: both bodies stop there (the stop is reported at the word after
    // the break).
    {
        const hgp::Run r = pair(*m, C("sub_7CC670"), Args{0, 0, 0, 0}, 1, "sub_7CC670");
        CHECK(r.stopped);
        CHECK(r.stop_pc == 0x7CC674u);
        CHECK(r.syscalls == 0);
    }
}

TEST_CASE("game(finalC): the libc stdio IOP file RPCs: iob checks, the request packet, the semaphores and the results") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 buf = kWorld + 0x100;
    // sceRead, blocking: packet = (sema, &result, 4, IOP fd, buf, size, -, iob index); the buffer and the packet are
    // written back (sub_5067F8), RPC command 2 with 32 bytes, the lock released, the semaphore waited and deleted,
    // $v0 = the IOP's byte count.
    {
        stdio_state(*m, 3, 0x11, 1);
        const hgp::Run r = pair(*m, C("sceRead"), Args{3, buf, 0x100, 0}, 1, "sceRead blocking", stdio_world(), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 42);
        CHECK(r32(*m, kPacket) == kSemaId);
        CHECK(r32(*m, kPacket + 4) != 0u);
        CHECK(r32(*m, kPacket + 8) == 4u);
        CHECK(r32(*m, kPacket + 0xC) == 0x11u);
        CHECK(r32(*m, kPacket + 0x10) == buf);
        CHECK(r32(*m, kPacket + 0x14) == 0x100u);
        CHECK(r32(*m, kPacket + 0x1C) == 3u);
        const auto wait = calls(kFsWaitS), sync = calls(kSyncBuf), rpc = calls(kFsCallRpc), waited = calls(kWaitSema);
        REQUIRE(wait.size() == 1u);
        CHECK(wait[0].args[0] == 2u);
        REQUIRE(sync.size() == 2u);
        CHECK(sync[0].args[0] == buf);
        CHECK(sync[0].args[1] == 0x100u);
        CHECK(sync[1].args[0] == kPacket);
        CHECK(sync[1].args[1] == 32u);
        REQUIRE(rpc.size() == 1u);
        CHECK(rpc[0].args[0] == kFsClient);
        CHECK(rpc[0].args[1] == 2u);
        CHECK(rpc[0].args[3] == kPacket);
        CHECK(rpc[0].args[4] == 32u);
        CHECK(rpc[0].args[5] == kReply);
        REQUIRE(waited.size() == 2u);  // the iob lock (get_iob), then the request's semaphore
        CHECK(waited[0].args[0] == 0x66u);
        CHECK(waited[1].args[0] == kSemaId);
        REQUIRE(calls(kDeleteSema).size() == 1u);
        CHECK(calls(kFsSigSema).size() == 1u);
        CHECK(r32(*m, kSemaSlots) == 0xFFFFFFFFu);
    }
    // Non-blocking iob (flag 0x8000): the semaphore goes into the first free slot under the slot lock, the packet
    // carries its negative, nothing is waited and $v0 = 0. The second slot when the first is taken.
    for (int taken = 0; taken < 2; ++taken) {
        stdio_state(*m, 3, 0x11, 0x8001);
        if (taken) w32(*m, kSemaSlots, 5);
        const hgp::Run r = pair(*m, C("sceRead"), Args{3, buf, 0x100, 0}, 2 + static_cast<u32>(taken), "sceRead non-blocking",
                                stdio_world(), stdio_ranges());
        INFO("slot taken " << taken);
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 0);
        CHECK(r32(*m, kSemaSlots + 4 * static_cast<u32>(taken)) == kSemaId);
        CHECK(r32(*m, kPacket) == static_cast<u32>(-static_cast<s32>(kSemaId)));
        const auto waited = calls(kWaitSema), signalled = calls(kSignalSema);
        REQUIRE(waited.size() == 2u);  // the iob lock, then the slot lock: never the request's semaphore
        CHECK(waited[1].args[0] == 0x55u);
        REQUIRE(signalled.size() == 2u);
        CHECK(signalled[1].args[0] == 0x55u);
        CHECK(calls(kDeleteSema).size() == 1u);
    }
    // Flag 0x20000000: the buffer is not written back, the packet still is.
    {
        stdio_state(*m, 3, 0x11, 0x20000001u);
        const hgp::Run r = pair(*m, C("sceRead"), Args{3, buf, 0x100, 0}, 4, "sceRead no sync", stdio_world(), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 42);
        const auto sync = calls(kSyncBuf);
        REQUIRE(sync.size() == 1u);
        CHECK(sync[0].args[0] == kPacket);
    }
    // -9: a descriptor past the 32 iobs, an iob without flags, or before sceFsInit (the lock released, no RPC).
    {
        const struct { const char* what; u32 fd; u32 flags; bool init; } bad[] = {{"fd 40", 40, 1, true}, {"no flags", 3, 0, true}, {"no init", 3, 1, false}};
        u32 seed = 5;
        for (const auto& b : bad) {
            stdio_state(*m, b.fd < 32 ? b.fd : 3, 0x11, b.flags, b.init);
            const hgp::Run r = pair(*m, C("sceRead"), Args{b.fd, buf, 0x100, 0}, seed++, std::string("sceRead ") + b.what, stdio_world(), stdio_ranges());
            INFO(b.what);
            CHECK_FALSE(r.stopped);
            CHECK(v0s(r) == -9);
            CHECK(calls(kFsCallRpc).empty());
            CHECK(calls(kFsSigSema).size() == 1u);
        }
    }
    // -11: a failed call (the semaphore deleted, the lock released) or an empty reply.
    {
        stdio_state(*m, 3, 0x11, 1);
        const hgp::Run r = pair(*m, C("sceRead"), Args{3, buf, 0x100, 0}, 8, "sceRead rpc fails", stdio_world({-1, 1, 42}), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == -11);
        CHECK(calls(kDeleteSema).size() == 1u);
        CHECK(calls(kFsSigSema).size() == 1u);
        CHECK(calls(kWaitSema).size() == 1u);  // the iob lock only
        stdio_state(*m, 3, 0x11, 1);
        const hgp::Run r2 = pair(*m, C("sceRead"), Args{3, buf, 0x100, 0}, 9, "sceRead empty reply", stdio_world({0, 0, 42}), stdio_ranges());
        CHECK_FALSE(r2.stopped);
        CHECK(v0s(r2) == -11);
        CHECK(calls(kDeleteSema).size() == 1u);
    }
    // sceWrite: command 3, a 48-byte packet (+0x2C the iob index), the buffer written back but not the packet; the
    // bytes before the first 16-byte boundary of the buffer (+0x18 their count, at most the size) are copied into the
    // packet at +0x1C through the uncached window.
    {
        stdio_state(*m, 5, 0x22, 1);
        const hgp::Run r = pair(*m, C("sceWrite"), Args{5, buf, 0x80, 0}, 10, "sceWrite aligned", stdio_world({0, 1, 0x80}), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 0x80);
        CHECK(r32(*m, kPacket + 0xC) == 0x22u);
        CHECK(r32(*m, kPacket + 0x10) == buf);
        CHECK(r32(*m, kPacket + 0x14) == 0x80u);
        CHECK(r32(*m, kPacket + 0x18) == 0u);
        CHECK(r32(*m, kPacket + 0x2C) == 5u);
        const auto rpc = calls(kFsCallRpc);
        REQUIRE(rpc.size() == 1u);
        CHECK(rpc[0].args[1] == 3u);
        CHECK(rpc[0].args[4] == 48u);
        const auto sync = calls(kSyncBuf);
        REQUIRE(sync.size() == 1u);
        CHECK(sync[0].args[0] == buf);
        CHECK(sync[0].args[1] == 0x80u);
        for (const auto& [size, head] : {std::pair<u32, u32>{0x80, 13}, {4, 4}}) {
            stdio_state(*m, 5, 0x22, 1);
            for (u32 i = 0; i < 32; ++i) w8(*m, buf + i, static_cast<u8>(0xA0 + i));
            const hgp::Run ru = pair(*m, C("sceWrite"), Args{5, buf + 3, size, 0}, 20 + size, "sceWrite unaligned", stdio_world({0, 1, size}), stdio_ranges());
            INFO("size " << size);
            CHECK_FALSE(ru.stopped);
            CHECK(v0s(ru) == static_cast<s32>(size));
            CHECK(r32(*m, kPacket + 0x10) == buf + 3);
            CHECK(r32(*m, kPacket + 0x18) == head);
            CHECK(std::memcmp(m->at(kPacket + 0x1C), m->at(buf + 3), head) == 0);
            CHECK(r8(*m, kPacket + 0x1C + head) == 0);
        }
        stdio_state(*m, 5, 0x22, 0);
        const hgp::Run r2 = pair(*m, C("sceWrite"), Args{5, buf, 0x80, 0}, 11, "sceWrite no flags", stdio_world(), stdio_ranges());
        CHECK_FALSE(r2.stopped);
        CHECK(v0s(r2) == -9);
    }
    // sceIoctl: command 5, the request at +0x10 and the 1024-byte argument copied to +0x14 with its length 1024 at
    // +0x41C (0 for a null argument, whose bytes stay), the whole 1056-byte packet written back and sent.
    {
        std::vector<u8> arg(1024);
        for (std::size_t i = 0; i < arg.size(); ++i) arg[i] = static_cast<u8>(i * 7 + 1);
        stdio_state(*m, 2, 0x33, 1);
        std::memcpy(m->at(buf), arg.data(), arg.size());
        const hgp::Run r = pair(*m, C("sceIoctl"), Args{2, 0x1234, buf, 0}, 12, "sceIoctl", stdio_world({0, 1, 9}), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 9);
        CHECK(r32(*m, kPacket + 0xC) == 0x33u);
        CHECK(r32(*m, kPacket + 0x10) == 0x1234u);
        CHECK(std::memcmp(m->at(kPacket + 0x14), arg.data(), arg.size()) == 0);
        CHECK(r32(*m, kPacket + 0x41C) == 1024u);
        const auto rpc = calls(kFsCallRpc), sync = calls(kSyncBuf);
        REQUIRE(rpc.size() == 1u);
        CHECK(rpc[0].args[1] == 5u);
        CHECK(rpc[0].args[4] == 1056u);
        REQUIRE(sync.size() == 1u);
        CHECK(sync[0].args[0] == kPacket);
        CHECK(sync[0].args[1] == 1056u);
        stdio_state(*m, 2, 0x33, 1);
        std::memset(m->at(kPacket + 0x14), 0xEE, 1024);
        const hgp::Run r2 = pair(*m, C("sceIoctl"), Args{2, 0x1234, 0, 0}, 13, "sceIoctl null argument", stdio_world({0, 1, 9}), stdio_ranges());
        CHECK_FALSE(r2.stopped);
        CHECK(v0s(r2) == 9);
        CHECK(r32(*m, kPacket + 0x41C) == 0u);
        const std::vector<u8> kept(1024, 0xEE);
        CHECK(std::memcmp(m->at(kPacket + 0x14), kept.data(), kept.size()) == 0);
    }
    // sceSync: sceFsInit when it has not run, the device name copied to +0x14 (its 1024th byte cleared when it fills
    // the field), the mode at +0x10, command 19 with 1044 bytes.
    {
        stdio_state(*m, 0, 0, 0, false);
        wstr(*m, buf, "cdrom0:");
        const hgp::Run r = pair(*m, C("sceSync"), Args{buf, 2, 0, 0}, 14, "sceSync", stdio_world({0, 1, 0}), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 0);
        CHECK(calls(kFsInit).size() == 1u);
        CHECK(gstr(*m, kPacket + 0x14) == "cdrom0:");
        CHECK(r32(*m, kPacket + 0x10) == 2u);
        const auto rpc = calls(kFsCallRpc);
        REQUIRE(rpc.size() == 1u);
        CHECK(rpc[0].args[1] == 19u);
        CHECK(rpc[0].args[4] == 1044u);
        CHECK(calls(kWaitSema).size() == 1u);
        CHECK(calls(kDeleteSema).size() == 1u);
        stdio_state(*m, 0, 0, 0, true);
        std::memset(m->at(buf), 'n', 1100);
        const hgp::Run r2 = pair(*m, C("sceSync"), Args{buf, 0, 0, 0}, 15, "sceSync long name", stdio_world({0, 1, 0}), stdio_ranges());
        CHECK_FALSE(r2.stopped);
        CHECK(calls(kFsInit).empty());
        CHECK(r8(*m, kPacket + 0x14 + 1022) == 'n');
        CHECK(r8(*m, kPacket + 0x14 + 1023) == 0);
        stdio_state(*m, 0, 0, 0, true);
        wstr(*m, buf, "host:");
        const hgp::Run r3 = pair(*m, C("sceSync"), Args{buf, 0, 0, 0}, 16, "sceSync empty reply", stdio_world({0, 0, 0}), stdio_ranges());
        CHECK_FALSE(r3.stopped);
        CHECK(v0s(r3) == -11);
    }
    // sceLseek64: the 64-bit offset at +0x10, the whence at +0x18, the iob index at +0x1C, command 22 with 32 bytes,
    // the 8-byte result in $v0.
    {
        stdio_state(*m, 7, 0x44, 1);
        const hgp::Run r = pair(*m, C("sceLseek64"), Args{7, 0x0000000100000010ull, 2, 0}, 17, "sceLseek64",
                                stdio_world({0, 1, 0x0000000123456789ull}), stdio_ranges());
        CHECK_FALSE(r.stopped);
        CHECK(v0_of(r) == 0x0000000123456789ull);
        CHECK(r64(*m, kPacket + 0x10) == 0x0000000100000010ull);
        CHECK(r32(*m, kPacket + 0x18) == 2u);
        CHECK(r32(*m, kPacket + 0x1C) == 7u);
        CHECK(r32(*m, kPacket + 0xC) == 0x44u);
        const auto rpc = calls(kFsCallRpc);
        REQUIRE(rpc.size() == 1u);
        CHECK(rpc[0].args[1] == 22u);
        CHECK(rpc[0].args[4] == 32u);
        stdio_state(*m, 7, 0x44, 1);
        const hgp::Run r2 = pair(*m, C("sceLseek64"), Args{7, 0, 0, 0}, 18, "sceLseek64 rpc fails", stdio_world({-1, 1, 0}), stdio_ranges());
        CHECK_FALSE(r2.stopped);
        CHECK(v0s(r2) == -11);
    }
}

TEST_CASE("game(finalC): scePadSetButtonInfo, dvci_search_fstate, the IPU tag list and the scratchpad copy") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    // scePadSetButtonInfo: the request (10, port, slot, mode) in the pad RPC buffer, 128 bytes each way on the pad
    // client; a reply of 1 also sets the request state 2; $v0 = the reply, 0 when the call fails.
    {
        constexpr u32 kPadBuf = 0x96DF00u, kPadClient = 0x96DCC0u, kCallRpc = 0x507230u, kSetReqState = 0x511B08u;
        const struct { const char* what; s32 rpc; u32 reply; s32 v0; std::size_t states; } cases[] = {
            {"reply 1", 0, 1, 1, 1}, {"reply 0", 0, 0, 0, 0}, {"reply 5", 0, 5, 5, 0}, {"rpc fails", -1, 1, 0, 0}};
        u32 seed = 1;
        for (const auto& c : cases) {
            wzero(*m, kPadBuf, 0x80);
            w32(*m, kPadBuf + 0x10, c.reply);
            HwCheck hw;
            hw.ranges = {{kPadBuf, 0x80u}};
            const hgp::Run r = pair(*m, C("scePadSetButtonInfo"), Args{1, 0, 7, 0}, seed++, std::string("scePadSetButtonInfo ") + c.what,
                                    [c](StandInWorld& w) {
                                        w.si.install_recorder(kCallRpc, "sceSifCallRpc", sx(static_cast<u32>(c.rpc)));
                                        w.si.install_recorder(kSetReqState, "scePadSetReqState", 0);
                                    }, hw);
            INFO(c.what);
            CHECK_FALSE(r.stopped);
            CHECK(v0s(r) == c.v0);
            CHECK(r32(*m, kPadBuf) == 10u);
            CHECK(r32(*m, kPadBuf + 4) == 1u);
            CHECK(r32(*m, kPadBuf + 8) == 0u);
            CHECK(r32(*m, kPadBuf + 0xC) == 7u);
            const auto rpc = calls(kCallRpc), states = calls(kSetReqState);
            REQUIRE(rpc.size() == 1u);
            CHECK(rpc[0].args[0] == kPadClient);
            CHECK(rpc[0].args[1] == 1u);
            CHECK(rpc[0].args[3] == kPadBuf);
            CHECK(rpc[0].args[4] == 128u);
            CHECK(rpc[0].args[5] == kPadBuf);
            CHECK(rpc[0].args[6] == 128u);
            REQUIRE(states.size() == c.states);
            if (!states.empty()) {
                CHECK(states[0].args[0] == 1u);
                CHECK(states[0].args[1] == 0u);
                CHECK(states[0].args[2] == 2u);
            }
        }
    }
    // dvci_search_fstate: the table's names (after 8 * 0x7A2A68 pair bytes, 0x7A2A6C + 1 bytes each) searched one by
    // one (converted, sceCdSync(1) spun on, the trace marks), a hit stores (sector, size) into the entry and prints
    // "found", a miss counts and prints "Not found"; the total, the warning with misses, $v0 = the hits.
    {
        constexpr u32 kConv = 0x55A9B0u, kMark = 0x558988u, kCdSync = 0x510148u, kSearch = 0x559DD8u, kPrint = 0x5416E8u, kWarn = 0x541760u;
        constexpr u32 kCount = 0x7A2A68u, kNameLen = 0x7A2A6Cu, kConvName = 0x7A2B88u;
        const u32 table = kWorld, names = table + 24;
        w32(*m, kCount, 3);
        w32(*m, kNameLen, 15);
        wzero(*m, table, 24 + 3 * 16);
        wstr(*m, names, "A.BIN");
        wstr(*m, names + 32, "Z.BIN");
        const Setup dvci = [](StandInWorld& w) {
            w.si.install_recorder(kConv, "dvci_conv_fname", 0);
            w.si.install_recorder(kMark, "mark", 0);
            w.si.install_recorder(kPrint, "dvci printf", 0);
            w.si.install_recorder(kWarn, "dvci warning", 0);
            auto syncs = std::make_shared<int>(0), searches = std::make_shared<int>(0);
            w.si.install(kCdSync, "sceCdSync", [syncs](EEContext&, StandIns&, StandInCall& c) { c.v0 = ++*syncs == 1 ? 1u : 0u; });
            w.si.install(kSearch, "dvCiCdSearchFile", [searches](EEContext& ctx, StandIns&, StandInCall& c) {
                const int k = ++*searches;
                ctx.memory->write<u32>(static_cast<u32>(c.args[0]), 0x1000u + static_cast<u32>(k));
                ctx.memory->write<u32>(static_cast<u32>(c.args[0]) + 4, 0x2000u + static_cast<u32>(k));
                c.v0 = k == 1 ? 1u : 0u;
            });
        };
        HwCheck hw;
        hw.ranges = {{kWorld, 0x1000u}, {kConvName, 0x100u}};
        const hgp::Run r = pair(*m, C("dvci_search_fstate"), Args{table, 3, 0, 0}, 1, "dvci_search_fstate", dvci, hw);
        CHECK_FALSE(r.stopped);
        CHECK(v0s(r) == 1);
        CHECK(r32(*m, table) == 0x1001u);
        CHECK(r32(*m, table + 4) == 0x2001u);
        CHECK(r32(*m, table + 8) == 0u);
        CHECK(r32(*m, table + 16) == 0u);
        const auto conv = calls(kConv), sync = calls(kCdSync), search = calls(kSearch), print = calls(kPrint), warn = calls(kWarn), marks = calls(kMark);
        REQUIRE(conv.size() == 2u);
        CHECK(conv[0].args[0] == names);
        CHECK(conv[0].args[1] == kConvName);
        CHECK(conv[1].args[0] == names + 32);
        CHECK(sync.size() == 3u);  // 1 then 0 for the first name, 0 for the second
        REQUIRE(search.size() == 2u);
        CHECK(search[0].args[1] == kConvName);
        REQUIRE(print.size() == 3u);
        CHECK(print[0].args[1] == names);
        CHECK(print[1].args[1] == names + 32);
        CHECK(print[2].args[1] == 1u);
        REQUIRE(warn.size() == 1u);
        CHECK(warn[0].args[1] == 10u);
        REQUIRE(marks.size() == 8u);
        const u32 expected[8] = {37888, 37889, 38144, 38145, 37888, 37889, 38144, 38146};
        for (std::size_t i = 0; i < 8; ++i) CHECK(marks[i].args[0] == expected[i]);
        // no entries: the total alone, no warning
        const hgp::Run r0 = pair(*m, C("dvci_search_fstate"), Args{table, 0, 0, 0}, 2, "dvci_search_fstate empty", dvci, hw);
        CHECK_FALSE(r0.stopped);
        CHECK(v0s(r0) == 0);
        CHECK(calls(kPrint).size() == 1u);
        CHECK(calls(kWarn).empty());
        CHECK(calls(kConv).empty());
    }
    // _sendDataToIPU: the tag list at ($a0 + 4495) & ~15: pieces of at most 0xFFF40 bytes, qwc = (len + 15) >> 4, id 3
    // (ref) while more follows else 0 (refe), the source address; FlushCache (one syscall), then D4_TADR = the list,
    // D4_QWC = 0, D4_CHCR = 0x105.
    {
        const u32 work = kWorld, src = kWorld + 0x2000, tags = (work + 4495u) & ~15u;
        const u32 len = 0xFFF40u + 0x124u;
        wzero(*m, tags, 64);
        const hgp::Run r = pair(*m, C("_sendDataToIPU"), Args{work, src, len, 0}, 1, "_sendDataToIPU two pieces");
        CHECK_FALSE(r.stopped);
        CHECK(r.syscalls == 1);
        CHECK(r32(*m, tags) == (0xFFF4u | 0x30000000u));
        CHECK(r32(*m, tags + 4) == src);
        CHECK(r32(*m, tags + 16) == 0x13u);
        CHECK(r32(*m, tags + 20) == src + 0xFFF40u);
        const auto w = hw_writes(r, 0x1000B400u, 0x1000B500u);
        REQUIRE(w.size() == 3u);
        CHECK(w[0] == std::pair<u32, u32>{0x1000B430u, tags});
        CHECK(w[1] == std::pair<u32, u32>{0x1000B420u, 0u});
        CHECK(w[2] == std::pair<u32, u32>{0x1000B400u, 0x105u});
        // one short piece: a single refe tag of 2 qwords
        wzero(*m, tags, 64);
        const hgp::Run r1 = pair(*m, C("_sendDataToIPU"), Args{work, src, 17, 0}, 2, "_sendDataToIPU one piece");
        CHECK_FALSE(r1.stopped);
        CHECK(r32(*m, tags) == 2u);
        CHECK(r32(*m, tags + 4) == src);
        CHECK(r32(*m, tags + 16) == 0u);
        // nothing: no tag, the kick still goes out
        wzero(*m, tags, 64);
        const hgp::Run r2 = pair(*m, C("_sendDataToIPU"), Args{work, src, 0, 0}, 3, "_sendDataToIPU nothing");
        CHECK_FALSE(r2.stopped);
        CHECK(r32(*m, tags) == 0u);
        CHECK(hw_writes(r2, 0x1000B400u, 0x1000B500u).size() == 3u);
    }
    // _cpr8, a frame picture (+388 == 3, +244 == 0) of 2 blocks on a 2-macroblock-wide image: stride 768, 48 qwords a
    // block; each block flushes the scratchpad to the destination (D9: SADR 0, MADR, QWC, CHCR 0x101) then loads the
    // next source chunk (D8: SADR 0, MADR, QWC, CHCR 0x100), the sources stepping by the field stride (= 768 here) and
    // the destinations by 768. The polls (D9_CHCR / D8_CHCR STR, D8_QWC) read zeros.
    {
        const u32 state = kWorld, image = kWorld + 0x100, src = kWorld + 0x4000, dst = kWorld + 0x8000;
        wzero(*m, state, 0x200);
        wzero(*m, image, 0x40);
        w32(*m, state + 236, src);
        w32(*m, state + 388, 3);
        w32(*m, image, dst);
        w32(*m, image + 12, 2);
        w32(*m, image + 16, 2);
        HwCheck hw;
        hw.reads[0x1000D400u] = std::vector<u64>(64, 0);
        hw.reads[0x1000D000u] = std::vector<u64>(64, 0);
        hw.reads[0x1000D020u] = std::vector<u64>(64, 0);
        const hgp::Run r = pair(*m, C("_cpr8"), Args{state, image, 0, 0}, 1, "_cpr8 frame", {}, hw);
        CHECK_FALSE(r.stopped);
        const auto w = hw_writes(r, 0x1000D000u, 0x1000D500u);
        REQUIRE(w.size() == 16u);
        for (u32 k = 0; k < 2; ++k) {
            const std::pair<u32, u32> block[8] = {{0x1000D480u, 0u}, {0x1000D410u, dst + 768 * k}, {0x1000D420u, 48u}, {0x1000D400u, 0x101u},
                                                  {0x1000D080u, 0u}, {0x1000D010u, src + 768 * k}, {0x1000D020u, 48u}, {0x1000D000u, 0x100u}};
            for (u32 i = 0; i < 8; ++i) {
                INFO("block " << k << " write " << i);
                CHECK(w[8 * k + i] == block[i]);
            }
        }
        CHECK(count_access(r.bus, 0x1000D400u, false) == 2u);
        CHECK(count_access(r.bus, 0x1000D000u, false) == 2u);
        CHECK(count_access(r.bus, 0x1000D020u, false) == 2u);
    }
}

#else

TEST_CASE("game(finalC): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
