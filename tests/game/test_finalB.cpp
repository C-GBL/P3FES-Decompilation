// Pair tests of slice finalB (game/src/fx/finalB.cpp): the 15 functions of the final wave, every body against its
// recompiled body on
//   * random worlds (the p3fes_handgen sweep, with bounded byte counts for the scratchpad streamers, a kind / mode for
//     the panel mover, a real format for the printf family and live globals for the releases);
//   * the stand-in worlds (heap, printf, the file layer; callees this build does not emit recorded): the documented
//     rules of the debug-log ring, the fclBankManager request log, the tween stepper, the CRI handle setter, the
//     death-scene trigger, the battle-panel resource release, the message-tag scene call, the fusion list creator and
//     the animation slot update;
//   * the shop snapshot's root panel for every kind / mode of the panel mover;
//   * the streamers with their DMAC channels idle (every CHCR read sees STR clear): the syscall, the channel
//     programming on the bus log, the staged scratchpad and the memcpy tail.
// Compared by tests/game/handgen_pairs.h (hgp::pair) and stand_ins.h (run_pair_si): the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log.
#include "sweep1_util.h"

#include "p3fes/game/finalB.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
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
using namespace p3fes::game_test::s1t;
namespace fb = p3fes::game::finalB;

namespace p3fes::recomp_gen {
void fn_sub_1052B0_001052b0(EEContext&);  // generated body
void fn_sub_1052B0_001052b0__recomp(EEContext&);  // recompiled
void fn_sub_343B60_00343b60(EEContext&);  // generated body
void fn_sub_343B60_00343b60__recomp(EEContext&);  // recompiled
void fn_sub_3B93C0_003b93c0(EEContext&);  // generated body
void fn_sub_3B93C0_003b93c0__recomp(EEContext&);  // recompiled
void fn_sub_3CF160_003cf160(EEContext&);  // generated body
void fn_sub_3CF160_003cf160__recomp(EEContext&);  // recompiled
void fn_sub_3E0C20_003e0c20(EEContext&);  // generated body
void fn_sub_3E0C20_003e0c20__recomp(EEContext&);  // recompiled
void fn_printf_005225a8(EEContext&);  // generated body
void fn_printf_005225a8__recomp(EEContext&);  // recompiled
void fn_atan2l_4_0054d100(EEContext&);  // generated body
void fn_atan2l_4_0054d100__recomp(EEContext&);  // recompiled
void fn_sub_54D220_0054d220(EEContext&);  // generated body
void fn_sub_54D220_0054d220__recomp(EEContext&);  // recompiled
void fn_sub_18B700_0018b700(EEContext&);  // generated body
void fn_sub_18B700_0018b700__recomp(EEContext&);  // recompiled
void fn_sub_21BB60_0021bb60(EEContext&);  // generated body
void fn_sub_21BB60_0021bb60__recomp(EEContext&);  // recompiled
void fn_sub_2DCE90_002dce90(EEContext&);  // generated body
void fn_sub_2DCE90_002dce90__recomp(EEContext&);  // recompiled
void fn_sub_313490_00313490(EEContext&);  // generated body
void fn_sub_313490_00313490__recomp(EEContext&);  // recompiled
void fn_sub_476140_00476140(EEContext&);  // generated body
void fn_sub_476140_00476140__recomp(EEContext&);  // recompiled
void fn_sub_476720_00476720(EEContext&);  // generated body
void fn_sub_476720_00476720__recomp(EEContext&);  // recompiled
void fn_sub_476C20_00476c20(EEContext&);  // generated body
void fn_sub_476C20_00476c20__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_1052B0", 0x1052B0, &recomp_gen::fn_sub_1052B0_001052b0, &recomp_gen::fn_sub_1052B0_001052b0__recomp},
    {"sub_343B60", 0x343B60, &recomp_gen::fn_sub_343B60_00343b60, &recomp_gen::fn_sub_343B60_00343b60__recomp},
    {"sub_3B93C0", 0x3B93C0, &recomp_gen::fn_sub_3B93C0_003b93c0, &recomp_gen::fn_sub_3B93C0_003b93c0__recomp},
    {"sub_3CF160", 0x3CF160, &recomp_gen::fn_sub_3CF160_003cf160, &recomp_gen::fn_sub_3CF160_003cf160__recomp},
    {"sub_3E0C20", 0x3E0C20, &recomp_gen::fn_sub_3E0C20_003e0c20, &recomp_gen::fn_sub_3E0C20_003e0c20__recomp},
    {"printf", 0x5225A8, &recomp_gen::fn_printf_005225a8, &recomp_gen::fn_printf_005225a8__recomp},
    {"atan2l_4", 0x54D100, &recomp_gen::fn_atan2l_4_0054d100, &recomp_gen::fn_atan2l_4_0054d100__recomp},
    {"sub_54D220", 0x54D220, &recomp_gen::fn_sub_54D220_0054d220, &recomp_gen::fn_sub_54D220_0054d220__recomp},
    {"sub_18B700", 0x18B700, &recomp_gen::fn_sub_18B700_0018b700, &recomp_gen::fn_sub_18B700_0018b700__recomp},
    {"sub_21BB60", 0x21BB60, &recomp_gen::fn_sub_21BB60_0021bb60, &recomp_gen::fn_sub_21BB60_0021bb60__recomp},
    {"sub_2DCE90", 0x2DCE90, &recomp_gen::fn_sub_2DCE90_002dce90, &recomp_gen::fn_sub_2DCE90_002dce90__recomp},
    {"sub_313490", 0x313490, &recomp_gen::fn_sub_313490_00313490, &recomp_gen::fn_sub_313490_00313490__recomp},
    {"sub_476140", 0x476140, &recomp_gen::fn_sub_476140_00476140, &recomp_gen::fn_sub_476140_00476140__recomp},
    {"sub_476720", 0x476720, &recomp_gen::fn_sub_476720_00476720, &recomp_gen::fn_sub_476720_00476720__recomp},
    {"sub_476C20", 0x476C20, &recomp_gen::fn_sub_476C20_00476c20, &recomp_gen::fn_sub_476C20_00476c20__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
constexpr u32 kFmt = kWorld + 0x8000u, kStr = kWorld + 0x8100u, kRec = kWorld + 0x9000u, kWork = kWorld + 0xA000u;
constexpr u32 kBtl = kWorld + 0xB000u, kSlot = kWorld + 0xC000u, kTable = kWorld + 0xC100u;
constexpr u32 kGlobalLogCount = 0x7CDEC4u, kGlobalBpRes = 0x7CE304u, kGlobalBtl = 0x7CE3ECu;
constexpr u32 kFakeRes = 0x01234560u;

// The first `n` arguments of a recorded call ($a0..$a3, $t0..$t3 in order; the registers past the callee's arguments
// hold whatever the randomised context had).
std::vector<u64> first_args(const StandInCall& c, std::size_t n) { return std::vector<u64>(c.args.begin(), c.args.begin() + static_cast<std::ptrdiff_t>(n)); }

// The streamers' DMAC channels idle: every CHCR read sees STR (bit 8) clear, so the wait loops end at once and no
// transfer happens (both runs see the same device); the other registers hold what the bodies write.
HwCheck idle_channels() {
    HwCheck hw;
    hw.reads[fb::kD8Chcr].assign(1u << 14, 0);
    hw.reads[fb::kD9Chcr].assign(1u << 14, 0);
    hw.regs = {{fb::kD8Chcr, 0}, {fb::kD9Chcr, 0}};
    return hw;
}

// The arguments of one random pair: bounded byte counts for the streamers, a kind / mode for the panel mover, a real
// format for the printf family, live globals for the release and the trigger, the retail RW slots for the creator.
Args sweep_args(Machine& m, const Case& c, std::mt19937& rng, HwCheck& hw) {
    Args a{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
           hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
    const u32 bytes = rng() % 0x3000u;
    const u32 dst = kWorld + (rng() % 0x4000u) * 4u, src = kWorld + 0x4000u + (rng() % 0x3000u) * 4u;
    switch (c.addr) {
    case 0x476140u: hw = idle_channels(); a = {dst, bytes, rng(), 0}; break;
    case 0x476720u: hw = idle_channels(); a = {dst, bytes, src, 0}; break;
    case 0x476C20u: hw = idle_channels(); a = {dst, src, bytes, 0}; break;
    case 0x3E0C20u: a = {kWork, rng() % 19u, rng() % 3u, 0}; break;
    case 0x5225A8u:
    case 0x1052B0u:
        wstr(m, kFmt, "%d %x %s %c\n");
        wstr(m, kStr, "finalB");
        a = {kFmt, rng(), rng(), kStr};
        w8(m, kGlobalLogCount, static_cast<u8>(rng() % 16u));
        break;
    case 0x21BB60u: w32(m, kGlobalBpRes, kWork); write_rw_slots(m); break;
    case 0x2DCE90u: w32(m, kGlobalBtl, kBtl); break;
    case 0x343B60u: write_rw_slots(m); break;
    default: break;
    }
    return a;
}

}  // namespace

TEST_CASE("game(finalB): every body equals its recompiled body on random worlds") {
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
            HwCheck hw;
            const Args args = sweep_args(*m, c, rng, hw);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name, hw).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// The debug-log ring (sub_1052B0): the line is formatted through vsprintf into a zeroed 256-byte buffer and appended at
// the count's slot; a full ring (15 lines) first drops its oldest line (the others move down one slot) so the new line
// lands in slot 14. The result is the line's address in the ring.
TEST_CASE("game(finalB): the debug-log ring formatter") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    for (const u32 count : {0u, 1u, 7u, 14u, 15u}) {
        SiPair sp = run_case(m, base, kCases, "sub_1052B0", {kFmt, 7, 0xBEEF, kStr}, 100 + count, [&](Machine& mm) {
            wstr(mm, kFmt, "n=%d x=%x s=%s");
            wstr(mm, kStr, "abc");
            w8(mm, kGlobalLogCount, static_cast<u8>(count));
            for (u32 i = 0; i < 15; ++i) {
                std::memset(mm.at(fb::kLogRing + fb::kLogLine * i), 0, fb::kLogLine);
                wstr(mm, fb::kLogRing + fb::kLogLine * i, "old" + std::to_string(i));
            }
        });
        INFO("count " << count);
        const u32 slot = count == 15 ? 14 : count;
        CHECK(gstr(m, fb::kLogRing + fb::kLogLine * slot) == "n=7 x=beef s=abc");
        CHECK(r8(m, kGlobalLogCount) == (count == 15 ? 15u : count + 1));
        CHECK(static_cast<u32>(v0_of(sp.hw)) == fb::kLogRing + fb::kLogLine * slot);
        if (count == 15) {
            for (u32 i = 0; i < 14; ++i) CHECK(gstr(m, fb::kLogRing + fb::kLogLine * i) == "old" + std::to_string(i + 1));
        } else {
            for (u32 i = 0; i < count; ++i) CHECK(gstr(m, fb::kLogRing + fb::kLogLine * i) == "old" + std::to_string(i));
            if (count + 1 < 15) CHECK(gstr(m, fb::kLogRing + fb::kLogLine * (count + 1)) == "old" + std::to_string(count + 1));
        }
        // the rest of the line is the zeroed buffer's
        for (u32 i = 20; i < fb::kLogLine; ++i) CHECK(r8(m, fb::kLogRing + fb::kLogLine * slot + i) == 0u);
    }
}

// The fclBankManager request logger (sub_3CF160): "[fclBankManager.c:102]" then "%x:%d:%d:%d\n" of the packed id
// (id, id >> 16, byte 1, byte 0) through printf and the debug-log ring, then sub_3CF960(id, arg) != 0.
TEST_CASE("game(finalB): the fclBankManager request logger") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    for (const u64 ret : {0ull, 0x1234ull}) {
        SiPair sp = run_case(m, base, kCases, "sub_3CF160", {0x00120304u, 5, 0, 0}, 200 + static_cast<u32>(ret),
                             [&](Machine& mm) { w8(mm, kGlobalLogCount, 3); }, ret, {}, {0x3CF960u});
        INFO("sub_3CF960 -> " << ret);
        const std::vector<StandInCall> p = calls(sp, kPrintf);
        REQUIRE(p.size() == 2u);
        CHECK(p[0].text == "[fclBankManager.c:102]");
        CHECK(p[1].text == "120304:18:3:4\n");
        const std::vector<StandInCall> q = calls(sp, 0x3CF960u);
        REQUIRE(q.size() == 1u);
        CHECK(q[0].args[0] == 0x120304u);
        CHECK(q[0].args[1] == 5u);
        CHECK(v0_of(sp.hw) == (ret ? 1 : 0));
        CHECK(gstr(m, fb::kLogRing + fb::kLogLine * 3) == "120304:18:3:4\n");  // the ring got the same line
        CHECK(r8(m, kGlobalLogCount) == 4u);
    }
}

// The tween stepper (sub_18B700): an inactive record returns 0; the frame steps by one while below the limit; while
// it is below the last frame the step returns 0; at the last frame kind 0 runs sub_18BB20, kind 1 sub_18BB80 (their
// result returned) and any other kind returns 0.
TEST_CASE("game(finalB): the tween stepper, the CRI handle setter, the death-scene trigger") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    struct T {
        u32 active, kind, frame, last, limit;
        u32 want_frame;
        s64 want_v0;
        u32 callee;  // 0: none
    };
    const T cases[] = {
        {0, 0, 3, 10, 20, 3, 0, 0},         // inactive: untouched
        {1, 2, 3, 10, 20, 4, 0, 0},         // stepped, below the last frame
        {1, 2, 9, 10, 20, 10, 0, 0},        // reaches the last frame: kind 2 returns 0
        {1, 0, 9, 10, 20, 10, 0x77, 0x18BB20u},
        {1, 1, 9, 10, 20, 10, 0x77, 0x18BB80u},
        {1, 0, 20, 10, 20, 20, 0x77, 0x18BB20u},  // at the limit: not stepped, past the last frame
        {1, 1, 10, 10, 10, 10, 0x77, 0x18BB80u},
    };
    u32 seed = 300;
    for (const T& t : cases) {
        SiPair sp = run_case(m, base, kCases, "sub_18B700", {kRec, 0, 0, 0}, seed++, [&](Machine& mm) {
            std::memset(mm.at(kRec), 0, 0x44);
            w32(mm, kRec + fb::tween::kActive, t.active);
            w32(mm, kRec + fb::tween::kKind, t.kind);
            w32(mm, kRec + fb::tween::kFrame, t.frame);
            w32(mm, kRec + fb::tween::kLast, t.last);
            w32(mm, kRec + fb::tween::kLimit, t.limit);
        }, 0x77, {}, {0x18BB20u, 0x18BB80u});
        INFO("active " << t.active << " kind " << t.kind << " frame " << t.frame);
        CHECK(r32(m, kRec + fb::tween::kFrame) == t.want_frame);
        CHECK(v0_of(sp.hw) == t.want_v0);
        CHECK(calls(sp, 0x18BB20u).size() == (t.callee == 0x18BB20u ? 1u : 0u));
        CHECK(calls(sp, 0x18BB80u).size() == (t.callee == 0x18BB80u ? 1u : 0u));
        if (t.callee) CHECK(calls(sp, t.callee)[0].args[0] == kRec);
    }
    // the CRI handle setter: *(handle + 168) = value, nothing else of the handle
    SiPair sp = run_case(m, base, kCases, "sub_54D220", {kRec, 0x5555AAAAu, 0, 0}, seed++, [&](Machine& mm) { std::memset(mm.at(kRec), 0x11, 0x100); });
    CHECK(r32(m, kRec + fb::kCriHandleSlot168) == 0x5555AAAAu);
    CHECK(r32(m, kRec + 164) == 0x11111111u);
    CHECK(r32(m, kRec + 172) == 0x11111111u);
    // the death-scene trigger: gBtl flag 0x40 at +12 calls sub_108F70 once, otherwise nothing
    for (const u32 flags : {0x40u, 0x0u, 0xFFFFFFBFu}) {
        sp = run_case(m, base, kCases, "sub_2DCE90", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
            w32(mm, kGlobalBtl, kBtl);
            w32(mm, kBtl + 12, flags);
        }, 0, {}, {0x108F70u});
        CHECK(calls(sp, 0x108F70u).size() == ((flags & 0x40u) ? 1u : 0u));
    }
}

// The battle-panel resource release (sub_21BB60): a null work asserts (sub_19D3F0("bp_res.c", 89)); flag bit 0 releases
// the seven rasters at +16 (sub_21CC20) and frees the six blocks at +84 through the RwFree slot; bit 7 nullsub_11,
// bit 8 sub_21C930, bits 4..6 release the rasters at +56 / +60 / +64; the work pointer is cleared.
TEST_CASE("game(finalB): the battle-panel resource release") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const std::vector<u32> stand = {0x21CC20u, 0x21C930u, 0x19D3F0u};
    u32 seed = 400;
    for (const u32 flags : {0x1F1u, 0x1u, 0x70u, 0x180u, 0x0u}) {
        SiPair sp = run_case(m, base, kCases, "sub_21BB60", {0, 0, 0, 0}, seed++, [&](Machine& mm) {
            w32(mm, kGlobalBpRes, kWork);
            std::memset(mm.at(kWork), 0, 0x100);
            w32(mm, kWork + fb::bpres::kFlags, flags);
            for (u32 i = 0; i < 7; ++i) w32(mm, kWork + fb::bpres::kRasters + 4 * i, 0x2000 + i);
            w32(mm, kWork + fb::bpres::kRaster4, 0x3004);
            w32(mm, kWork + fb::bpres::kRaster5, 0x3005);
            w32(mm, kWork + fb::bpres::kRaster6, 0x3006);
            for (u32 i = 0; i < 6; ++i) w32(mm, kWork + fb::bpres::kBlocks + 4 * i, 0x4000 + 16 * i);
        }, 0, {}, stand);
        INFO("flags " << flags);
        CHECK(r32(m, kGlobalBpRes) == 0u);
        const std::vector<StandInCall> rel = calls(sp, 0x21CC20u);
        std::vector<u32> want;
        if (flags & 1u)
            for (u32 i = 0; i < 7; ++i) want.push_back(0x2000 + i);
        if (flags & 0x10u) want.push_back(0x3004);
        if (flags & 0x20u) want.push_back(0x3005);
        if (flags & 0x40u) want.push_back(0x3006);
        REQUIRE(rel.size() == want.size());
        for (std::size_t i = 0; i < want.size(); ++i) CHECK(static_cast<u32>(rel[i].args[0]) == want[i]);
        const std::vector<StandInCall> freed = calls(sp, kRwSlotFns[1]);
        REQUIRE(freed.size() == ((flags & 1u) ? 6u : 0u));
        for (std::size_t i = 0; i < freed.size(); ++i) CHECK(static_cast<u32>(freed[i].args[0]) == 0x4000 + 16 * i);
        CHECK(calls(sp, 0x21C930u).size() == ((flags & 0x100u) ? 1u : 0u));
        CHECK(calls(sp, 0x19D3F0u).empty());
    }
    // no work: the assertion, then the (null) work's flags are read from address 4 and the pointer stays cleared
    SiPair sp = run_case(m, base, kCases, "sub_21BB60", {0, 0, 0, 0}, seed++, [&](Machine& mm) { w32(mm, kGlobalBpRes, 0); w32(mm, 4, 0); }, 0, {}, stand);
    const std::vector<StandInCall> as = calls(sp, 0x19D3F0u);
    REQUIRE(as.size() == 1u);
    CHECK(gstr(m, static_cast<u32>(as[0].args[0])) == "bp_res.c");
    CHECK(as[0].args[1] == 89u);
    CHECK(calls(sp, 0x21CC20u).empty());
    CHECK(r32(m, kGlobalBpRes) == 0u);
}

// The message-tag scene call (sub_3B93C0): the scene resource of id (a0 & 0x3FF) | 0xC00 (sub_3B5D10); with a3 == -1
// one sub_3B8FF0(res, 0, a1, a2, 1, 0); otherwise sub_3B8FF0(res, 0, a1, a2, 0, 0) and, after a second look-up,
// sub_3B9260(res, 0, a3, t0, 1, 0). A missing resource skips its call.
TEST_CASE("game(finalB): the message-tag scene call and the fusion list creator") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const std::vector<u32> stand = {0x3B5D10u, 0x3B8FF0u, 0x3B9260u};
    u32 seed = 500;
    {
        SiPair sp = run_case(m, base, kCases, "sub_3B93C0", {0x8001u, 11, 22, 0xFFFFu}, seed++, {}, kFakeRes, {{GPR_T0, 33}}, stand);
        std::vector<StandInCall> look = calls(sp, 0x3B5D10u);
        REQUIRE(look.size() == 1u);
        CHECK(look[0].args[0] == 0xC01u);
        std::vector<StandInCall> c = calls(sp, 0x3B8FF0u);
        REQUIRE(c.size() == 1u);
        CHECK(first_args(c[0], 6) == std::vector<u64>{kFakeRes, 0, 11, 22, 1, 0});
        CHECK(calls(sp, 0x3B9260u).empty());
        CHECK(static_cast<u32>(v0_of(sp.hw)) == kFakeRes);
        sp = run_case(m, base, kCases, "sub_3B93C0", {0x8001u, 11, 22, 5}, seed++, {}, kFakeRes, {{GPR_T0, 33}}, stand);
        look = calls(sp, 0x3B5D10u);
        REQUIRE(look.size() == 2u);
        CHECK(look[1].args[0] == 0xC01u);
        c = calls(sp, 0x3B8FF0u);
        REQUIRE(c.size() == 1u);
        CHECK(first_args(c[0], 6) == std::vector<u64>{kFakeRes, 0, 11, 22, 0, 0});
        c = calls(sp, 0x3B9260u);
        REQUIRE(c.size() == 1u);
        CHECK(first_args(c[0], 6) == std::vector<u64>{kFakeRes, 0, 5, 33, 1, 0});
        // no resource: nothing applied
        sp = run_case(m, base, kCases, "sub_3B93C0", {0x3FFu, 1, 2, 3}, seed++, {}, 0, {{GPR_T0, 4}}, stand);
        CHECK(calls(sp, 0x3B5D10u).size() == 2u);
        CHECK(calls(sp, 0x3B8FF0u).empty());
        CHECK(calls(sp, 0x3B9260u).empty());
    }
    // The fusion list creator (sub_343B60): a block of 48 * count + 12 bytes from RwMalloc (hint 0x40000) whose +0 is
    // its entries (+12) and +8 itself; the work's rows (+140) are raised to at least 3; +4 = sub_323FB0(count, rows,
    // 0x69BCF0, 4, 76); a raster argument goes to sub_324510(obj, raster), none to sub_3243F0(obj, sub_3210A0(20));
    // then sub_343860(block, work). The block is the result. sub_323FB0 and sub_3210A0 (the fx_layers slice) run for
    // real on the stand-in heap (their entries are not served by the recorders); the other three are recorded.
    const std::vector<u32> stand2 = {0x3243F0u, 0x324510u, 0x343860u};
    for (const u32 raster : {0u, 0x99u}) {
        for (const u32 rows : {1u, 3u, 9u}) {
            SiPair sp = run_case(m, base, kCases, "sub_343B60", {kWork, raster, 0, 0}, seed++, [&](Machine& mm) {
                std::memset(mm.at(kWork), 0, 0x100);
                w32(mm, kWork + 56, 5);
                w32(mm, kWork + 140, rows);
            }, 0x04321000u, {}, stand2);
            INFO("raster " << raster << " rows " << rows);
            std::string trace;
            for (const StandInCall& c : sp.recomp->si.log)
                trace += hex64(c.va) + "(" + hex64(c.args[0]) + "," + hex64(c.args[1]) + ")->" + hex64(c.v0) + " ";
            INFO("calls: " << trace);
            const u32 blk = static_cast<u32>(v0_of(sp.hw));
            REQUIRE(blk != 0u);
            CHECK(sp.recomp->heap.size_of(blk) >= 48u * 5u + 12u);
            // the block's RwMalloc: 48 * count + 12 bytes with hint 0x40000, and it is the result
            std::size_t allocs = 0;
            for (const StandInCall& a : calls(sp, kRwSlotFns[0])) {
                INFO("RwMalloc " << a.args[0] << " hint " << hex64(a.args[1]) << " -> " << hex64(a.v0));
                if (a.args[0] == 48u * 5u + 12u && a.args[1] == 0x40000u) {
                    ++allocs;
                    CHECK(static_cast<u32>(a.v0) == blk);
                }
            }
            CHECK(allocs == 1u);
            CHECK(r32(m, blk) == blk + 12u);
            CHECK(r32(m, blk + 8) == blk);
            const u32 obj = r32(m, blk + 4);  // sub_323FB0's object, built on the stand-in heap
            CHECK(obj != 0u);
            CHECK(sp.recomp->heap.size_of(obj) > 0u);
            CHECK(r32(m, kWork + 140) == (rows < 3 ? 3u : rows));
            CHECK(calls(sp, 0x324510u).size() == (raster ? 1u : 0u));
            CHECK(calls(sp, 0x3243F0u).size() == (raster ? 0u : 1u));
            if (raster) {
                CHECK(calls(sp, 0x324510u)[0].args[0] == obj);
                CHECK(calls(sp, 0x324510u)[0].args[1] == raster);
            } else {
                CHECK(calls(sp, 0x3243F0u)[0].args[0] == obj);
            }
            std::vector<StandInCall> c = calls(sp, 0x343860u);
            REQUIRE(c.size() == 1u);
            CHECK(c[0].args[0] == blk);
            CHECK(c[0].args[1] == kWork);
        }
    }
}

// The animation slot update (sub_313490): an idle slot (node < 0) returns the other slot; kind 1 only updates the
// hierarchy (sub_466EF0 on the slot's +32) and returns the other slot; otherwise, when speed = frame delta * rate is
// positive or flags bit 1 / 2 is set, a finished blend (>= 1.0) advances the time by the speed and an unfinished one
// advances the blend by 1 / steps, then bit 2 is cleared; without a node table the slot is the result.
TEST_CASE("game(finalB): the animation slot update") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    struct S {
        s16 node;
        u8 kind;
        u16 flags;
        f32 dt, rate, time, blend;
        u16 steps;
        f32 want_time, want_blend;
        u16 want_flags;
        bool other;  // the result is $a1
        u32 callee;
    };
    const S cases[] = {
        {-1, 0, 6, 0.5f, 2.0f, 3.0f, 1.5f, 4, 3.0f, 1.5f, 6, true, 0},
        {0, 1, 6, 0.5f, 2.0f, 3.0f, 1.5f, 4, 3.0f, 1.5f, 6, true, 0x466EF0u},
        {0, 0, 6, 0.5f, 2.0f, 3.0f, 1.5f, 4, 4.0f, 1.5f, 2, false, 0},
        {2, 0, 0, 0.5f, 2.0f, 3.0f, 0.25f, 4, 3.0f, 0.5f, 0, false, 0},
        {2, 0, 0, 0.0f, 1.0f, 3.0f, 0.25f, 4, 3.0f, 0.25f, 0, false, 0},   // no speed, no flag: untouched
        {2, 0, 2, 0.0f, 1.0f, 3.0f, 1.0f, 4, 3.0f, 1.0f, 2, false, 0},     // bit 1 forces the step: time += 0
        {2, 0, 4, -1.0f, 1.0f, 3.0f, 0.5f, 2, 3.0f, 1.0f, 0, false, 0},    // bit 2 forces one step and is cleared
    };
    u32 seed = 600;
    for (const S& s : cases) {
        SiPair sp = run_case(m, base, kCases, "sub_313490", {kSlot, 0x55, 0, 0}, seed++, [&](Machine& mm) {
            std::memset(mm.at(kSlot), 0, 0x50);
            w16(mm, kSlot + fb::aslot::kFlags, s.flags);
            w8(mm, kSlot + fb::aslot::kKind, s.kind);
            w16(mm, kSlot + fb::aslot::kNode, static_cast<u16>(s.node));
            wf32(mm, kSlot + fb::aslot::kRate, s.rate);
            wf32(mm, kSlot + fb::aslot::kTime, s.time);
            w16(mm, kSlot + fb::aslot::kBlendSteps, s.steps);
            wf32(mm, kSlot + fb::aslot::kBlend, s.blend);
            w32(mm, kSlot + fb::aslot::kClump, kTable);
            w32(mm, kTable + 32, 0x7777);
            wf32(mm, fb::aslot::kFrameDelta, s.dt);
        }, 0, {}, {0x466EF0u});
        INFO("node " << s.node << " kind " << int(s.kind) << " flags " << s.flags << " dt " << s.dt);
        CHECK(static_cast<u32>(v0_of(sp.hw)) == (s.other ? 0x55u : kSlot));
        CHECK(rf32(m, kSlot + fb::aslot::kTime) == s.want_time);
        CHECK(rf32(m, kSlot + fb::aslot::kBlend) == s.want_blend);
        CHECK(r16(m, kSlot + fb::aslot::kFlags) == s.want_flags);
        CHECK(calls(sp, 0x466EF0u).size() == (s.callee ? 1u : 0u));
        if (s.callee) CHECK(calls(sp, 0x466EF0u)[0].args[0] == kTable);  // kind 1 passes the slot's +32 itself
    }
}

// The scratchpad streamers with idle channels: one _sceFlushCache syscall each; the word fill stages its quadwords in
// the scratchpad (0x70000000) and programs channel 8 (fromSPR: SADR 0, MADR the destination, QWC the quadwords, CHCR
// STR); the copy programs channel 9 (toSPR from the source) then channel 8, and copies the tail (bytes % 16) itself.
TEST_CASE("game(finalB): the scratchpad streamers on idle channels") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{0xF1A1Bu};
    auto writes = [](const hgp::Run& r, u32 pa) {
        std::vector<u64> v;
        for (const auto& a : r.bus)
            if (a.write && a.pa == pa) v.push_back(a.lo);
        return v;
    };
    u32 seed = 700;
    const u32 dst = kWorld + 0x1000u, src = kWorld + 0x5000u;
    for (const u32 bytes : {16u, 64u, 100u, 4096u, 16384u, 20000u}) {
        INFO("bytes " << bytes);
        hgp::random_world(*m, kWorld, kWorldSize, rng);
        hgp::Run r = hgp::pair(*m, kCases[12].hand, kCases[12].recomp, {dst, bytes, 0xA5A5A5A5u, 0}, seed++, "sub_476140", idle_channels());
        if (!r.stopped) {
            CHECK(r.syscalls == 1);
            const std::vector<u64> madr = writes(r, fb::kD8Madr), qwc = writes(r, fb::kD8Qwc), chcr = writes(r, fb::kD8Chcr);
            REQUIRE(!madr.empty());
            CHECK(madr[0] == dst);
            u32 total = 0;
            for (u64 q : qwc) total += static_cast<u32>(q);
            CHECK(total == bytes / 16);
            CHECK(chcr.size() == qwc.size());
            for (u64 c : chcr) CHECK((c & 0x100u) != 0);
            const u32 staged = std::min(bytes / 16, fb::kChunkQw) * 16;
            for (u32 i = 0; i < staged; i += 4) {
                u32 w;
                std::memcpy(&w, r.spr.data() + i, 4);
                CHECK(w == 0xA5A5A5A5u);
            }
        }
        hgp::random_world(*m, kWorld, kWorldSize, rng);
        r = hgp::pair(*m, kCases[14].hand, kCases[14].recomp, {dst, src, bytes, 0}, seed++, "sub_476C20", idle_channels());
        if (!r.stopped) {
            CHECK(r.syscalls == 1);
            const std::vector<u64> to = writes(r, fb::kD9Madr), from = writes(r, fb::kD8Madr);
            REQUIRE(!to.empty());
            REQUIRE(!from.empty());
            CHECK(to[0] == src);
            CHECK(from[0] == dst);
            u32 total = 0;
            for (u64 q : writes(r, fb::kD9Qwc)) total += static_cast<u32>(q);
            CHECK(total == bytes / 16);
            const u32 head = bytes & ~15u;  // the tail bytes are copied by memcpy; the head waits for the (idle) DMA
            for (u32 i = head; i < bytes; ++i) CHECK(r8(*m, dst + i) == r8(*m, src + i));
        }
    }
    // the quadword-pattern fill stages the 16-byte pattern
    hgp::random_world(*m, kWorld, kWorldSize, rng);
    for (u32 i = 0; i < 16; ++i) w8(*m, src + i, static_cast<u8>(0xC0 + i));
    const hgp::Run r = hgp::pair(*m, kCases[13].hand, kCases[13].recomp, {dst, 256, src, 0}, seed++, "sub_476720", idle_channels());
    if (!r.stopped) {
        CHECK(r.syscalls == 1);
        CHECK(writes(r, fb::kD8Madr).size() == 1u);
        CHECK(writes(r, fb::kD8Madr)[0] == dst);
        CHECK(writes(r, fb::kD8Qwc)[0] == 16u);
        for (u32 i = 0; i < 256; ++i) CHECK(r.spr[i] == static_cast<u8>(0xC0 + (i % 16)));
    }
}

// The facility panel mover (sub_3E0C20) on the shop snapshot's root panel: every kind (0..17 and one past the table)
// in every mode, the hand-written callees (nmList, fclElemSetParams, the node look-up) running for real.
TEST_CASE("game(finalB): the facility panel mover on the shop snapshot") {
    std::vector<u8> base;
    auto mp = real_machine("shop_ref_4100", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no shop_ref_4100 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 panel = r32(m, 0x7CDEE4u);
    if (panel == 0u) {
        MESSAGE("SKIP: no facility panel in the snapshot");
        return;
    }
    u32 seed = 800, pairs = 0;
    for (u32 kind = 0; kind <= 18; ++kind) {
        for (u32 mode = 0; mode <= 2; ++mode) {
            run_case(m, base, kCases, "sub_3E0C20", {panel, kind, mode, 0}, seed++);
            ++pairs;
        }
    }
    CHECK(pairs == 57u);
}

#else

TEST_CASE("game(finalB): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
