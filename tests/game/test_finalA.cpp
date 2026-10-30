// Pair tests of slice finalA (game/src/field/finalA.cpp): the last functions other tests held recompiled -- the BGM
// channel start, datInitNewGame, the model fade task, the floor-effect stop, the two collision push-outs, the shadow
// unit creation, the unit model release, gmRoot_CreateGameRootTask, RwTextureRead, the kernel thread wrappers,
// kputs, scePadInit / scePadPortOpen, sceMc2CreateSocket and the frFontEx string draw. Every body against its
// recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the packet's replay snapshots (dorm_replay_4900, b_5800, climb_ref_17000, fusion_ref_6300, shop_ref_4100) with
//     arguments of each function's kind (args_of): live kwln tasks and field units of the snapshot, the RpWorld,
//     spawn records, guest strings, 64-byte aligned pad buffers, socket parameters; the SIF / interrupt wrappers
//     stood in (they would spin on the IOP), every other callee this build does not emit recorded;
//   * documented rules on the host: the BGM channel record, the floor-effect slot release, the sceMc2 error codes,
//     scePadPortOpen's alignment / already-open / success paths, StartThread's context set-up, the unit model
//     release, the frFontEx layout (position, colour, alignment, width).
// Compared by tests/game/handgen_pairs.h (hgp::pair) and stand_ins.h (run_pair_si): the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log.
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function, one function, a trace line per pair.
#include "handgen_pairs.h"
#include "sweep2_util.h"

#include "p3fes/game/finalA.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
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
using namespace p3fes::game_test::s1t;
namespace fa = p3fes::game::finalA;

namespace p3fes::recomp_gen {
void fn_sub_10A410_0010a410(EEContext&);  // generated body
void fn_sub_10A410_0010a410__recomp(EEContext&);  // recompiled
void fn_sub_195DE0_00195de0(EEContext&);  // generated body
void fn_sub_195DE0_00195de0__recomp(EEContext&);  // recompiled
void fn_sub_1A60D0_001a60d0(EEContext&);  // generated body
void fn_sub_1A60D0_001a60d0__recomp(EEContext&);  // recompiled
void fn_sub_1A9400_001a9400(EEContext&);  // generated body
void fn_sub_1A9400_001a9400__recomp(EEContext&);  // recompiled
void fn_sub_1AB390_001ab390(EEContext&);  // generated body
void fn_sub_1AB390_001ab390__recomp(EEContext&);  // recompiled
void fn_sub_1ABD20_001abd20(EEContext&);  // generated body
void fn_sub_1ABD20_001abd20__recomp(EEContext&);  // recompiled
void fn_sub_1CF940_001cf940(EEContext&);  // generated body
void fn_sub_1CF940_001cf940__recomp(EEContext&);  // recompiled
void fn_sub_1D1640_001d1640(EEContext&);  // generated body
void fn_sub_1D1640_001d1640__recomp(EEContext&);  // recompiled
void fn_gmRoot_CreateGameRootTask_002664c0(EEContext&);  // generated body
void fn_gmRoot_CreateGameRootTask_002664c0__recomp(EEContext&);  // recompiled
void fn_sub_4D1260_004d1260(EEContext&);  // generated body
void fn_sub_4D1260_004d1260__recomp(EEContext&);  // recompiled
void fn__sceWakeupThread_00503090(EEContext&);  // generated body
void fn__sceWakeupThread_00503090__recomp(EEContext&);  // recompiled
void fn__sceSuspendThread_005030d0(EEContext&);  // generated body
void fn__sceSuspendThread_005030d0__recomp(EEContext&);  // recompiled
void fn__sceResumeThread_005030f0(EEContext&);  // generated body
void fn__sceResumeThread_005030f0__recomp(EEContext&);  // recompiled
void fn_StartThread_005042a0(EEContext&);  // generated body
void fn_StartThread_005042a0__recomp(EEContext&);  // recompiled
void fn_kputs_00504650(EEContext&);  // generated body
void fn_kputs_00504650__recomp(EEContext&);  // recompiled
void fn_scePadInit_00511138(EEContext&);  // generated body
void fn_scePadInit_00511138__recomp(EEContext&);  // recompiled
void fn_scePadPortOpen_00511590(EEContext&);  // generated body
void fn_scePadPortOpen_00511590__recomp(EEContext&);  // recompiled
void fn_sceMc2CreateSocket_00513368(EEContext&);  // generated body
void fn_sceMc2CreateSocket_00513368__recomp(EEContext&);  // recompiled
void fn_sub_3B2CB0_003b2cb0(EEContext&);  // generated body
void fn_sub_3B2CB0_003b2cb0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_10A410", 0x10A410, &recomp_gen::fn_sub_10A410_0010a410, &recomp_gen::fn_sub_10A410_0010a410__recomp},
    {"sub_195DE0", 0x195DE0, &recomp_gen::fn_sub_195DE0_00195de0, &recomp_gen::fn_sub_195DE0_00195de0__recomp},
    {"sub_1A60D0", 0x1A60D0, &recomp_gen::fn_sub_1A60D0_001a60d0, &recomp_gen::fn_sub_1A60D0_001a60d0__recomp},
    {"sub_1A9400", 0x1A9400, &recomp_gen::fn_sub_1A9400_001a9400, &recomp_gen::fn_sub_1A9400_001a9400__recomp},
    {"sub_1AB390", 0x1AB390, &recomp_gen::fn_sub_1AB390_001ab390, &recomp_gen::fn_sub_1AB390_001ab390__recomp},
    {"sub_1ABD20", 0x1ABD20, &recomp_gen::fn_sub_1ABD20_001abd20, &recomp_gen::fn_sub_1ABD20_001abd20__recomp},
    {"sub_1CF940", 0x1CF940, &recomp_gen::fn_sub_1CF940_001cf940, &recomp_gen::fn_sub_1CF940_001cf940__recomp},
    {"sub_1D1640", 0x1D1640, &recomp_gen::fn_sub_1D1640_001d1640, &recomp_gen::fn_sub_1D1640_001d1640__recomp},
    {"gmRoot_CreateGameRootTask", 0x2664C0, &recomp_gen::fn_gmRoot_CreateGameRootTask_002664c0, &recomp_gen::fn_gmRoot_CreateGameRootTask_002664c0__recomp},
    {"sub_4D1260", 0x4D1260, &recomp_gen::fn_sub_4D1260_004d1260, &recomp_gen::fn_sub_4D1260_004d1260__recomp},
    {"_sceWakeupThread", 0x503090, &recomp_gen::fn__sceWakeupThread_00503090, &recomp_gen::fn__sceWakeupThread_00503090__recomp},
    {"_sceSuspendThread", 0x5030D0, &recomp_gen::fn__sceSuspendThread_005030d0, &recomp_gen::fn__sceSuspendThread_005030d0__recomp},
    {"_sceResumeThread", 0x5030F0, &recomp_gen::fn__sceResumeThread_005030f0, &recomp_gen::fn__sceResumeThread_005030f0__recomp},
    {"StartThread", 0x5042A0, &recomp_gen::fn_StartThread_005042a0, &recomp_gen::fn_StartThread_005042a0__recomp},
    {"kputs", 0x504650, &recomp_gen::fn_kputs_00504650, &recomp_gen::fn_kputs_00504650__recomp},
    {"scePadInit", 0x511138, &recomp_gen::fn_scePadInit_00511138, &recomp_gen::fn_scePadInit_00511138__recomp},
    {"scePadPortOpen", 0x511590, &recomp_gen::fn_scePadPortOpen_00511590, &recomp_gen::fn_scePadPortOpen_00511590__recomp},
    {"sceMc2CreateSocket", 0x513368, &recomp_gen::fn_sceMc2CreateSocket_00513368, &recomp_gen::fn_sceMc2CreateSocket_00513368__recomp},
    {"sub_3B2CB0", 0x3B2CB0, &recomp_gen::fn_sub_3B2CB0_003b2cb0, &recomp_gen::fn_sub_3B2CB0_003b2cb0__recomp},
};

// The random sweep's world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;

// The scratch layout (field4_util.h kScratch 0x01BC0000: free in the ELF's memory and in every snapshot).
constexpr u32 kStr = kScratch;               // guest strings
constexpr u32 kVec = kScratch + 0x100u;      // vec3s / a placement matrix
constexpr u32 kTask = kScratch + 0x400u;     // a kwln task (0x68 bytes), its work at kTaskWork
constexpr u32 kTaskWork = kScratch + 0x500u; // the task's work (0x100 bytes)
constexpr u32 kUnit = kScratch + 0x800u;     // a field unit (448 bytes)
constexpr u32 kSpawn = kScratch + 0xA00u;    // a spawn record (272 bytes)
constexpr u32 kBuf = kScratch + 0x1000u;     // a 64-byte aligned pad buffer (two 128-byte halves)
constexpr u32 kParam = kScratch + 0x1200u;   // sceMc2 socket parameters
constexpr u32 kFont = kScratch + 0x1400u;    // a font record (zeroed) for the frFontEx draw
constexpr u32 kChain = kScratch + 0x1800u;   // a line chain the frFontBuildGlyphList stand-in hands out
constexpr u32 kGlyph = kChain + 0x100u;      // its five glyph nodes of 48 bytes
constexpr u32 kStatus = kScratch + 0x1C00u;  // a thread stack for StartThread (0x1000 bytes)
constexpr u32 kStackSize = 0x1000u;

// SIF / interrupt / RPC wrappers the bodies reach: stood in (the real ones spin on the IOP or need COP0).
constexpr u32 kSifBindRpc = 0x507050u, kSifCallRpc = 0x507230u, kPadGetModVersion = 0x512640u;
constexpr u32 kQueryIntrContext = 0x503C30u, kDIntr = 0x50D3A0u, kEIntr = 0x50D3F0u;
constexpr u32 kReferThreadStatus = 0x503060u, kSceStartThread = 0x502F80u, kDeci2Call = 0x503590u;
constexpr u32 kScePrintf = 0x505E48u;
// Other callees the host-rule cases stand in.
constexpr u32 kModelGetPlacement = 0x318B60u, kResourceRelease = 0x3B7090u,
              kModelDestroy = 0x3174E0u, kTaskDestroyHier = 0x195020u, kMcCoreCreateSocket = 0x51C130u,
              kMcFatInit2 = 0x515400u, kMcChangeSocketType = 0x51C330u, kBuildGlyphList = 0x3B0970u,
              kGetStyleSize = 0x3B35C0u, kLineFadeStep = 0x3B0EC0u, kChainRelease = 0x3B0030u;

// The world of the snapshot pairs: the field world (heap, printf / sprintf, the file layer) plus the wrappers above.
void sif_world(StandInWorld& w) {
    w.si.install(kSifBindRpc, "sceSifBindRpc", [](EEContext& ctx, StandIns&, StandInCall& c) {
        ctx.memory->write<u32>(static_cast<u32>(c.args[0]) + 36, 1);  // the client's server field: bound
        c.v0 = 0;
    });
    w.si.install_recorder(kSifCallRpc, "sceSifCallRpc", 0);
    w.si.install_recorder(kPadGetModVersion, "scePadGetModVersion", 0x400);
    w.si.install_recorder(kQueryIntrContext, "QueryIntrContext", 0);
    w.si.install_recorder(kDIntr, "DIntr", 1);
    w.si.install_recorder(kEIntr, "EIntr", 1);
    w.si.install_recorder(kScePrintf, "scePrintf", 0);
}

u32 word(std::mt19937& rng) { return rng(); }

// The arguments of a function on a machine (the ELF, or a snapshot): its kind of structures in the scratch, live
// records of the snapshot where it has them. `t` gets $t0..$t3 (arguments 5..8).
Args args_of(Machine& m, const Case& c, std::mt19937& rng, u64 (&t)[4]) {
    const auto s = [&](u32 va, const char* text) {
        wstr(m, va, text);
        return static_cast<u64>(va);
    };
    const auto task = [&] {
        std::memset(m.at(kTask), 0, 0x68);
        wstr(m, kTask, "finalA task");
        w32(m, kTask + 0x1C, 2);
        w32(m, kTask + 0x3C, kTaskWork);
        std::memset(m.at(kTaskWork), 0, 0x100);
        return static_cast<u64>(kTask);
    };
    switch (c.addr) {
    case 0x10A410u:  // (slot, file): slots 0..5 start a channel, others return at once
        return Args{sx(rng() % 8), s(kStr, rng() % 2 ? "ENV_050.ADX" : "ENV_001.ADX"), 0, 0};
    case 0x195DE0u:
        return Args{0, 0, 0, 0};
    case 0x1A60D0u: {  // (parent task, model, frames, colour): no model -> 0
        const u32 model = rng() % 4 == 0 ? 0u : r32(m, 0x8717A0u + 80);  // the leader's model (0 off the field)
        return Args{task(), model, sx(static_cast<u32>(static_cast<s32>(rng() % 120) - 20)), rng() & 0xFFFFFFFFu};
    }
    case 0x1A9400u: {  // (task, index): the work's effect slots +36[4], the count at +32
        const u64 a0 = task();
        w32(m, kTaskWork + 32, rng() % 5);
        for (u32 i = 0; i < 4; ++i) w32(m, kTaskWork + 36 + 4 * i, rng() % 2 ? 0u : kVec);
        return Args{a0, sx(static_cast<u32>(static_cast<s32>(rng() % 6) - 2)), 0, 0};
    }
    case 0x1AB390u:
    case 0x1ABD20u: {  // (world, pos, delta, kind): the snapshot's RpWorld (0 off the field)
        const u32 world = rng() % 4 == 0 ? 0u : r32(m, 0x7CE0A0u);
        for (u32 i = 0; i < 8; ++i) wf32(m, kVec + 4 * i, static_cast<float>(static_cast<s32>(rng() % 2000) - 1000));
        static const u32 kinds[] = {0u, 1024u, 100u, 5u, 0x3FFu};
        return Args{world, kVec, kVec + 16, sx(kinds[rng() % 5])};
    }
    case 0x1CF940u: {  // (encounter id | kind << 16, spawn record): the record's floats at +256 / +264
        for (u32 i = 0; i < 272; i += 4) w32(m, kSpawn + i, rng());
        wf32(m, kSpawn + 256, static_cast<float>(static_cast<s32>(rng() % 8000) - 4000));
        wf32(m, kSpawn + 264, static_cast<float>(static_cast<s32>(rng() % 8000) - 4000));
        static const u32 kinds[] = {1u, 2u, 4u, 1u, 2u, 3u};
        return Args{sx((kinds[rng() % 6] << 16) | (rng() % 400)), kSpawn, 0, 0};
    }
    case 0x1D1640u: {  // (unit, destroy model): a live unit of the snapshot, or a scratch one
        u32 unit = 0;
        for (u32 i = 0; i < 28 && unit == 0; ++i) {
            const u32 u = i < 24 ? 0x86EDA0u + 448 * i : 0x8717A0u + 448 * (i - 24);
            if (r32(m, u + 72) != 0 && r32(m, u + 84) != 0 && rng() % 3 != 0) unit = u;
        }
        if (unit == 0) {
            unit = kUnit;
            for (u32 i = 0; i < 448; i += 4) w32(m, kUnit + i, rng() % 2 ? 0u : rng());
            w32(m, kUnit + 72, rng() % 2);
            w32(m, kUnit + 84, rng() % 2 ? 0u : kVec);
            w32(m, kUnit + 80, 0);
            w32(m, kUnit + 364, 0);
            w32(m, kUnit + 368, 0);
            w32(m, kUnit + 372, 0);
            w32(m, kUnit + 376, 0);
            w32(m, kUnit + 384, 0);
        }
        return Args{unit, sx(rng() % 2), 0, 0};
    }
    case 0x2664C0u:  // (parent task)
        return Args{task(), 0, 0, 0};
    case 0x4D1260u:  // (name, mask name or 0)
        return Args{s(kStr, "finalA_tex"), rng() % 2 ? s(kStr + 0x40, "finalA_mask") : 0u, 0, 0};
    case 0x503090u:
    case 0x5030D0u:
    case 0x5030F0u:
        return Args{sx(rng() % 64), 0, 0, 0};
    case 0x5042A0u:  // (thread id, argument)
        return Args{sx(1 + rng() % 60), rng(), 0, 0};
    case 0x504650u:
        return Args{s(kStr, "finalA kputs\n"), 0, 0, 0};
    case 0x511138u:  // (mode): the init flag 0x782748 clear or set, the verbose flag 0x78274C
        w32(m, 0x782748u, rng() % 2);
        w32(m, 0x78274Cu, rng() % 2);
        return Args{sx(rng() % 2), 0, 0, 0};
    case 0x511590u: {  // (port, slot, buffer): a 64-byte aligned buffer, sometimes not; the record sometimes open
        w32(m, 0x78274Cu, rng() % 2);
        const u32 port = rng() % 2, slot = 0;
        const u32 rec = 0x96DD10u + 112 * port + 28 * slot;
        w32(m, rec + 16, rng() % 3 == 0 ? 1u : 0u);
        std::memset(m.at(kBuf), 0xEE, 256);
        return Args{sx(port), sx(slot), sx(kBuf + (rng() % 4 == 0 ? 8u : 0u)), 0};
    }
    case 0x513368u: {  // (parameters): +4 type 2 / 3 valid, +8 must be 0; the library flag 0x7827D8
        w32(m, 0x7827D8u, rng() % 4 ? 1u : 0u);
        w32(m, kParam, rng());
        w32(m, kParam + 4, rng() % 5);
        w32(m, kParam + 8, rng() % 3 ? 0u : 1u);
        return Args{kParam, 0, 0, 0};
    }
    case 0x3B2CB0u: {  // (x, y, rgba, kind, font ($t0), text ($t1), align flags ($t2); $f12 scale)
        std::memset(m.at(kFont), 0, 0x400);
        static const u32 flags[] = {0u, 2u, 4u, 8u, 0x10u, 0xBu, 0x1Fu, rng()};
        t[0] = kFont;
        t[1] = s(kStr, "finalA");
        t[2] = sx(flags[rng() % 8]);
        return Args{sx(rng() % 640), sx(rng() % 448), rng(), sx(rng() % 3 ? 10u : rng() % 8)};
    }
    }
    return Args{word(rng), word(rng), word(rng), word(rng)};
}

u32 v0_u32(const SiPair& sp) { return static_cast<u32>(sp.hw.recomp.base.v0); }

// One pair of `c` on the stand-in world (install_field_world + `world`), every callee this build does not emit stood
// in by a recorder and the pair re-run (at most 24 times); `prepare` re-applies the test's edits after each reset and
// `regs` sets $t0..$t3. The recompiled run's memory is left in `m`.
SiPair run_w(Machine& m, const std::vector<u8>& base, const Case& c, const Args& args, u32 seed,
             const std::function<void(Machine&)>& prepare, const WorldSetup& world, const std::map<unsigned, u64>& regs) {
    HwCheck hw = whole_ram_check();
    hw.gpr_in = regs;
    std::vector<u32> absent;
    for (int tries = 0;; ++tries) {
        reset(m, base);
        write_rw_slots(m);
        if (prepare) prepare(m);
        try {
            const std::vector<u32> list = absent;
            return run_pair_si(m, c.hand, c.recomp, args, seed, c.name, hw, [list, world](StandInWorld& w) {
                install_field_world(w);
                if (world) world(w);
                for (u32 va : list)
                    if (!w.si.has(va)) w.si.install_recorder(va, "absent", 0);
            });
        } catch (const rt_test::FatalEvent& e) {
            const std::size_t k = e.what.find("function at 0x");
            if (k == std::string::npos || tries >= 24) throw;
            absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
        }
    }
}

}  // namespace

TEST_CASE("game(finalA): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, kWorld, kWorldSize, 64);
}

// Every body on the packet's snapshots with arguments of its kind (args_of), the snapshot restored between pairs; the
// pairs run on the stand-ins (the SIF / interrupt wrappers, every callee this build does not emit recorded). A pair
// whose original faults is run again as a plain pair, which compares the two stops.
TEST_CASE("game(finalA): every body on the replay snapshots with real structures") {
    struct Snap {
        const char* dir;
        u32 reps;
    };
    const Snap snaps[] = {{"b_5800", 3}, {"dorm_replay_4900", 2}, {"climb_ref_17000", 3}, {"fusion_ref_6300", 1}, {"shop_ref_4100", 1}};
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    int pairs = 0, stood = 0, stops = 0, used = 0;
    std::map<std::string, int> stop_of;
    for (const Snap& sn : snaps) {
        std::vector<u8> base;
        auto mp = real_machine(sn.dir, base);
        if (!mp) {
            MESSAGE("SKIP: no ELF or snapshot " << std::string(sn.dir));
            continue;
        }
        Machine& m = *mp;
        write_rw_slots(m);
        base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        ++used;
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                const std::mt19937 rng0{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                Args a{};
                u64 t[4] = {};
                auto draw = [&](Machine& mm) {
                    std::mt19937 rng = rng0;
                    a = args_of(mm, c, rng, t);
                    return rng();
                };
                const u32 seed = draw(m);
                ++pairs;
                try {
                    run_w(m, base, c, a, seed, [&](Machine& mm) { draw(mm); }, sif_world,
                          {{GPR_T0, t[0]}, {GPR_T1, t[1]}, {GPR_T2, t[2]}});
                    ++stood;
                } catch (const rt_test::FatalEvent&) {
                    reset(m, base);
                    draw(m);
                    HwCheck h = hw;
                    h.gpr_in[GPR_T0] = t[0];
                    h.gpr_in[GPR_T1] = t[1];
                    h.gpr_in[GPR_T2] = t[2];
                    const hgp::Run r = hgp::pair(m, c.hand, c.recomp, a, seed, c.name, h);
                    if (r.stopped) {
                        ++stops;
                        ++stop_of[std::string(c.name) + " (" + r.what.substr(0, 40) + " at " + hex64(r.stop_pc) + ")"];
                    }
                }
                reset(m, base);
            }
        }
    }
    std::string why;
    for (const auto& [k, n] : stop_of) why += " " + k + " x" + std::to_string(n) + ";";
    MESSAGE("snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stood << " on the stand-ins, " << stops
                          << " ended at a compared fault stop:" << why.substr(0, 1500));
}

// sub_10A410 (slot, file): a slot below 6 marks the BGM channel record active (+0 = 1, +8 / +12 = 0, +20 = 6) with the
// name "BGM:<file>" at +22 and calls sub_109180(slot); every call returns 1; a slot of 6 or more leaves the table.
TEST_CASE("game(finalA): the BGM channel start writes the channel record") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    // (the slot is a 16-bit signed value: 0xFFFF is -1, which passes the "< 6" test and names the record before
    // the table -- the original's behaviour, no caller passes it)
    for (const u32 slot : {0u, 3u, 5u, 6u, 9u, 0x7FFFu, 0xFFFFu}) {
        SiPair sp = run_w(m, base, find_case(kCases, "sub_10A410"), Args{sx(slot), kStr, 0, 0}, seed++, [](Machine& mm) {
            wstr(mm, kStr, "ENV_050.ADX");
            std::memset(mm.at(fa::kBgmChannels - fa::kBgmChannelSize), 0xEE, 7 * fa::kBgmChannelSize);
        }, [](StandInWorld& w) { w.si.install_recorder(0x109180u, "sub_109180 (channel start)", 0); }, {});
        CHECK(v0_u32(sp) == 1u);
        const s32 s = static_cast<s16>(slot);
        if (s < 6) {
            const u32 rec = fa::kBgmChannels + static_cast<u32>(fa::kBgmChannelSize * s);
            CHECK(r32(m, rec + fa::kBgmActive) == 1u);
            CHECK(r16(m, rec + fa::kBgmWord8) == 0u);
            CHECK(r16(m, rec + fa::kBgmWord12) == 0u);
            CHECK(r16(m, rec + fa::kBgmState) == 6u);
            CHECK(gstr(m, rec + fa::kBgmName) == "BGM:ENV_050.ADX");
            REQUIRE(calls(sp, 0x109180u).size() == 1u);
            CHECK(static_cast<u32>(calls(sp, 0x109180u)[0].args[0]) == static_cast<u32>(s));
        } else {
            CHECK(calls(sp, 0x109180u).empty());
            for (u32 i = 0; i < 7 * fa::kBgmChannelSize; ++i) CHECK(r8(m, fa::kBgmChannels - fa::kBgmChannelSize + i) == 0xEEu);
        }
    }
}

// sub_1A9400 (task, index): index < 0 clears the work's +16; 0..3 with a live slot destroys it (sub_34FCF0, whose
// entry is a typed shim: it runs for real), clears the slot and counts the +32 down; an empty slot changes nothing.
TEST_CASE("game(finalA): the floor effect stop releases one slot") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    const auto work = [](Machine& mm, s32 index, bool live) {
        std::memset(mm.at(kTask), 0, 0x68);
        w32(mm, kTask + 0x3C, kTaskWork);
        std::memset(mm.at(kTaskWork), 0, 0x100);
        w32(mm, kTaskWork + 16, 7);
        w32(mm, kTaskWork + 32, 3);
        for (u32 i = 0; i < 4; ++i) w32(mm, kTaskWork + 36 + 4 * i, 0x1000u + i);
        if (index >= 0 && !live) w32(mm, kTaskWork + 36 + 4 * static_cast<u32>(index), 0);
    };
    for (const s32 index : {-1, 0, 1, 2, 3}) {
        for (const bool live : {true, false}) {
            if (index >= 0 && live) {
                // sub_34FCF0's entry point is a typed shim, not a hooked forwarder: the destroy runs for real on the
                // fake node and faults there in both runs (a compared stop); the slot and the count are only written
                // after it
                reset(m, base);
                work(m, index, true);
                const hgp::Run r = hgp::pair(m, find_case(kCases, "sub_1A9400").hand, find_case(kCases, "sub_1A9400").recomp,
                                             Args{kTask, sx(static_cast<u32>(index)), 0, 0}, seed++, "sub_1A9400 (live slot)");
                CHECK(r.stopped);
                CHECK(r32(m, kTaskWork + 32) == 3u);
                continue;
            }
            SiPair sp = run_w(m, base, find_case(kCases, "sub_1A9400"), Args{kTask, sx(static_cast<u32>(index)), 0, 0}, seed++,
                              [&work, index, live](Machine& mm) { work(mm, index, live); }, {}, {});
            (void)sp;
            if (index < 0) {
                CHECK(r32(m, kTaskWork + 16) == 0u);
                CHECK(r32(m, kTaskWork + 32) == 3u);
                for (u32 i = 0; i < 4; ++i) CHECK(r32(m, kTaskWork + 36 + 4 * i) == 0x1000u + i);
            } else {
                CHECK(r32(m, kTaskWork + 16) == 7u);
                CHECK(r32(m, kTaskWork + 32) == 3u);
                for (u32 i = 0; i < 4; ++i)
                    CHECK(r32(m, kTaskWork + 36 + 4 * i) == (i == static_cast<u32>(index) ? 0u : 0x1000u + i));
            }
        }
    }
}

// sceMc2CreateSocket: 0x81018001 while the library is not initialised (0x7827D8 = 0); 0x81010016 for a type other than
// 2 / 3 or a non-zero +8; 0x81010017 when _sceMcCoreCreateSocket fails; else the socket goes through _sceMcFatInit2
// and the result is _sceMcCoreChangeSocketTypeMc2Dbc's.
TEST_CASE("game(finalA): the sceMc2 socket creation's error codes") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    struct Row {
        u32 init, type, word8, expect;
    };
    // the early returns: before any core call
    const Row rows[] = {{0, 2, 0, 0x81018001u}, {1, 1, 0, 0x81010016u}, {1, 4, 0, 0x81010016u}, {1, 2, 1, 0x81010016u}};
    for (const Row& r : rows) {
        SiPair sp = run_w(m, base, find_case(kCases, "sceMc2CreateSocket"), Args{kParam, 0, 0, 0}, seed++, [r](Machine& mm) {
            w32(mm, 0x7827D8u, r.init);
            w32(mm, kParam + 4, r.type);
            w32(mm, kParam + 8, r.word8);
        }, [](StandInWorld& w) { w.si.install_recorder(kMcCoreCreateSocket, "_sceMcCoreCreateSocket", 0); }, {});
        CHECK(v0_u32(sp) == r.expect);
        CHECK(calls(sp, kMcCoreCreateSocket).empty());
    }
    // the success path with the three core calls stood in
    for (const s32 sock : {-1, 0, 3}) {
        HwCheck hw = whole_ram_check();
        std::vector<u32> absent;
        reset(m, base);
        w32(m, 0x7827D8u, 1);
        w32(m, kParam + 4, 2);
        w32(m, kParam + 8, 0);
        SiPair sp = run_pair_si(m, find_case(kCases, "sceMc2CreateSocket").hand, find_case(kCases, "sceMc2CreateSocket").recomp,
                                Args{kParam, 0, 0, 0}, seed++, "sceMc2CreateSocket (stood in)", hw, [sock](StandInWorld& w) {
                                    install_field_world(w);
                                    w.si.install_recorder(kMcCoreCreateSocket, "_sceMcCoreCreateSocket", static_cast<u64>(static_cast<s64>(sock)));
                                    w.si.install_recorder(kMcFatInit2, "_sceMcFatInit2", 0);
                                    w.si.install_recorder(kMcChangeSocketType, "_sceMcCoreChangeSocketTypeMc2Dbc", 0x1234);
                                });
        if (sock < 0) {
            CHECK(v0_u32(sp) == 0x81010017u);
            CHECK(calls(sp, kMcFatInit2).empty());
        } else {
            CHECK(v0_u32(sp) == 0x1234u);
            CHECK(calls(sp, kMcFatInit2).size() == 1u);
            CHECK(static_cast<u32>(calls(sp, kMcFatInit2)[0].args[0]) == static_cast<u32>(sock));
            CHECK(static_cast<u32>(calls(sp, kMcChangeSocketType)[0].args[0]) == static_cast<u32>(sock));
        }
    }
}

// scePadPortOpen (port, slot, buf): a buffer that is not 64-byte aligned returns 0 (a message when 0x78274C is set);
// an already open record (+16 == 1) returns 0; else both 128-byte halves of the buffer are prepared (+88 / +96 = 0,
// +103 = 0, +112 = 5, +113 = 2, the first 32 bytes 0xFF), the open request {1, port, slot, buf} goes to the pad server
// through sceSifCallRpc (stood in), and on success the record gets +16 = 1, +0 = buf, +8 = the reply's +20, +4 = its
// state word (cleared); the result is the reply's +12.
TEST_CASE("game(finalA): scePadPortOpen's alignment, already-open and success paths") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    constexpr u32 kRpcBuf = 0x96DF00u, kPadRecords = 0x96DD10u, kPadStates = 0x96DE00u;
    for (const u32 port : {0u, 1u}) {
        for (const int kind : {0, 1, 2, 3}) {  // 0 misaligned, 1 already open, 2 rpc fails, 3 success
            const u32 buf = kBuf + (kind == 0 ? 16u : 0u);
            const s64 rpc = kind == 2 ? -1 : 0;
            const u32 rec = kPadRecords + 112 * port;
            HwCheck hw = whole_ram_check();
            reset(m, base);
            w32(m, 0x78274Cu, 1);
            std::memset(m.at(kBuf), 0xEE, 256);
            w32(m, rec + 16, kind == 1 ? 1u : 0u);
            w32(m, kPadStates + 128 * port, 0x5555u);
            SiPair sp = run_pair_si(m, find_case(kCases, "scePadPortOpen").hand, find_case(kCases, "scePadPortOpen").recomp,
                                    Args{sx(port), 0, buf, 0}, seed++, "scePadPortOpen", hw, [rpc](StandInWorld& w) {
                                        install_field_world(w);
                                        w.si.install_recorder(kScePrintf, "scePrintf", 0);
                                        w.si.install(kSifCallRpc, "sceSifCallRpc", [rpc](EEContext& ctx, StandIns&, StandInCall& c) {
                                            // the reply: +12 the result, +20 the IOP-side address
                                            ctx.memory->write<u32>(kRpcBuf + 12, 0x7777u);
                                            ctx.memory->write<u32>(kRpcBuf + 20, 0xBEEF00u);
                                            c.v0 = static_cast<u64>(rpc);
                                        });
                                    });
            if (kind == 0 || kind == 1) {
                CHECK(v0_u32(sp) == 0u);
                CHECK(calls(sp, kScePrintf).size() == 1u);
                CHECK(calls(sp, kSifCallRpc).empty());
                for (u32 i = 0; i < 256; ++i) CHECK(r8(m, kBuf + i) == 0xEEu);
                continue;
            }
            // the buffer halves prepared, the request written
            for (u32 half = 0; half < 2; ++half) {
                const u32 h = kBuf + 128 * half;
                for (u32 i = 0; i < 32; ++i) CHECK(r8(m, h + i) == 0xFFu);
                CHECK(r32(m, h + 88) == 0u);
                CHECK(r32(m, h + 96) == 0u);
                CHECK(r8(m, h + 103) == 0u);
                CHECK(r8(m, h + 112) == 5u);
                CHECK(r8(m, h + 113) == 2u);
            }
            CHECK(r32(m, kRpcBuf) == 1u);
            CHECK(r32(m, kRpcBuf + 4) == port);
            CHECK(r32(m, kRpcBuf + 8) == 0u);
            CHECK(r32(m, kRpcBuf + 16) == buf);
            REQUIRE(calls(sp, kSifCallRpc).size() == 1u);
            CHECK(static_cast<u32>(calls(sp, kSifCallRpc)[0].args[1]) == 1u);
            if (kind == 2) {
                CHECK(v0_u32(sp) == 0u);
                CHECK(r32(m, rec + 16) == 0u);
            } else {
                CHECK(v0_u32(sp) == 0x7777u);
                CHECK(r32(m, rec + 16) == 1u);
                CHECK(r32(m, rec + 0) == buf);
                CHECK(r32(m, rec + 4) == kPadStates + 128 * port);
                CHECK(r32(m, rec + 8) == 0xBEEF00u);
                CHECK(r32(m, rec + 12) == 0u);
                CHECK(r32(m, kPadStates + 128 * port) == 0u);
            }
        }
    }
}

// StartThread (thread, argument): -1 from an interrupt context (QueryIntrContext != 0) or when DIntr fails; the status
// read through _sceReferThreadStatus must be 16 (dormant) or the result is -1 after EIntr; a negative status read is
// returned as is; else the 0x2A0-byte context at the top of the thread's stack (stack + size - 672) is cleared (the
// 64 bytes at +448 excepted), the argument stored at +64, the four saved words at +448 / +464 / +480 / +496 widened to
// 64 bits, and _sceStartThread(thread, argument) gives the result.
TEST_CASE("game(finalA): StartThread's context set-up") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    for (const int kind : {0, 1, 2, 3, 4}) {  // 0 intr context, 1 DIntr fails, 2 status read fails, 3 not dormant, 4 dormant
        const u64 intr = kind == 0 ? 1u : 0u, dintr = kind == 1 ? 0u : 1u;
        const s64 refer = kind == 2 ? -5 : 0;
        const u32 status = kind == 3 ? 4u : 16u;
        HwCheck hw = whole_ram_check();
        reset(m, base);
        std::memset(m.at(kStatus), 0xAB, kStackSize);
        SiPair sp = run_pair_si(m, find_case(kCases, "StartThread").hand, find_case(kCases, "StartThread").recomp,
                                Args{7, 0x12345678u, 0, 0}, seed++, "StartThread", hw, [intr, dintr, refer, status](StandInWorld& w) {
                                    install_field_world(w);
                                    w.si.install_recorder(kQueryIntrContext, "QueryIntrContext", intr);
                                    w.si.install_recorder(kDIntr, "DIntr", dintr);
                                    w.si.install_recorder(kEIntr, "EIntr", 1);
                                    w.si.install(kReferThreadStatus, "_sceReferThreadStatus", [refer, status](EEContext& ctx, StandIns&, StandInCall& c) {
                                        const u32 out = static_cast<u32>(c.args[1]);
                                        ctx.memory->write<u32>(out, status);
                                        ctx.memory->write<u32>(out + 8, kStatus);
                                        ctx.memory->write<u32>(out + 12, kStackSize);
                                        c.v0 = static_cast<u64>(refer);
                                    });
                                    w.si.install_recorder(kSceStartThread, "_sceStartThread", 0x42);
                                });
        const u32 ctxva = kStatus + kStackSize - 672;
        if (kind == 0) {
            CHECK(v0_u32(sp) == 0xFFFFFFFFu);
            CHECK(calls(sp, kDIntr).empty());
        } else if (kind == 1) {
            CHECK(v0_u32(sp) == 0xFFFFFFFFu);
            CHECK(calls(sp, kReferThreadStatus).empty());
        } else if (kind == 2) {
            CHECK(v0_u32(sp) == 0xFFFFFFFBu);
            CHECK(calls(sp, kEIntr).size() == 1u);
            CHECK(calls(sp, kSceStartThread).empty());
        } else if (kind == 3) {
            CHECK(v0_u32(sp) == 0xFFFFFFFFu);
            CHECK(calls(sp, kEIntr).size() == 1u);
            CHECK(calls(sp, kSceStartThread).empty());
            CHECK(r8(m, ctxva) == 0xABu);
        } else {
            CHECK(v0_u32(sp) == 0x42u);
            REQUIRE(calls(sp, kSceStartThread).size() == 1u);
            CHECK(static_cast<u32>(calls(sp, kSceStartThread)[0].args[0]) == 7u);
            CHECK(static_cast<u32>(calls(sp, kSceStartThread)[0].args[1]) == 0x12345678u);
            for (u32 off = 0; off < 672; off += 4) {
                if (off == 64) {
                    CHECK(r32(m, ctxva + 64) == 0x12345678u);
                    CHECK(r32(m, ctxva + 68) == 0u);
                    off += 4;
                    continue;
                }
                if (off >= 448 && off < 512) {
                    // the four saved words widened from the stack's bytes (0xABABABAB, negative): the high half -1,
                    // the following double word cleared
                    if ((off - 448) % 16 == 0) CHECK(r32(m, ctxva + off) == 0xABABABABu);
                    else if ((off - 448) % 16 == 4) CHECK(r32(m, ctxva + off) == 0xFFFFFFFFu);
                    else CHECK(r32(m, ctxva + off) == 0u);
                    continue;
                }
                // the 36 quad-word stores cover [0, 448) and [512, 640): the last 32 bytes keep the stack's bytes
                if (off >= 640) {
                    CHECK(r32(m, ctxva + off) == 0xABABABABu);
                    continue;
                }
                CHECK(r32(m, ctxva + off) == 0u);
            }
            CHECK(r8(m, ctxva - 1) == 0xABu);
        }
    }
}

// sub_1D1640 (unit, destroy model): a unit without an instance (+72) or resource (+84) is left alone; a live one keeps
// its placement (the eight words of sub_318B60's matrix, stood in), releases the resource (sub_3B7090 on the resource's
// u16 id, stood in) and clears +84, destroys the model (+80, sub_3174E0) only when the flag is 1, and destroys the
// tasks at +364 / +368 / +376 / +384 / +372 (kwlnTaskDestroyWithHierarchy) clearing each.
TEST_CASE("game(finalA): the unit model release") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    std::mt19937 rng{0xF1A1Au};
    for (int it = 0; it < 24; ++it) {
        const bool instance = it % 4 != 1, resource = it % 4 != 2, destroy = it % 2 == 1;
        const u32 tasks = static_cast<u32>(rng() % 32);
        HwCheck hw = whole_ram_check();
        reset(m, base);
        for (u32 i = 0; i < 448; i += 4) w32(m, kUnit + i, 0x11000000u + i);
        w32(m, kUnit + 72, instance ? 0x2000u : 0u);
        w32(m, kUnit + 80, it % 8 == 3 ? 0u : 0x3000u);
        w32(m, kUnit + 84, resource ? kVec + 64 : 0u);
        w16(m, kVec + 64, 0x1234);
        static const u32 slots[] = {364, 368, 376, 384, 372};
        for (u32 i = 0; i < 5; ++i) w32(m, kUnit + slots[i], (tasks >> i) & 1 ? 0x4000u + 0x100 * i : 0u);
        for (u32 i = 0; i < 16; ++i) w32(m, kVec + 4 * i, 0x5A000000u + i);
        SiPair sp = run_pair_si(m, find_case(kCases, "sub_1D1640").hand, find_case(kCases, "sub_1D1640").recomp,
                                Args{kUnit, sx(destroy ? 1u : 2u), 0, 0}, seed++, "sub_1D1640", hw, [](StandInWorld& w) {
                                    install_field_world(w);
                                    w.si.install_recorder(kModelGetPlacement, "sub_318B60", kVec);
                                    w.si.install_recorder(kResourceRelease, "sub_3B7090", 0);
                                    w.si.install_recorder(kModelDestroy, "sub_3174E0", 0);
                                    w.si.install_recorder(kTaskDestroyHier, "kwlnTaskDestroyWithHierarchy", 0);
                                });
        const bool live = instance && resource;
        if (!live) {
            CHECK(sp.recomp->si.log.empty());
            for (u32 i = 0; i < 448; i += 4)
                if (i != 72 && i != 80 && i != 84 && i != 364 && i != 368 && i != 372 && i != 376 && i != 384)
                    CHECK(r32(m, kUnit + i) == 0x11000000u + i);
            continue;
        }
        for (u32 i = 0; i < 16; ++i) CHECK(r32(m, kUnit + 4 * i) == 0x5A000000u + i);
        CHECK(r32(m, kUnit + 64) == 0x11000000u + 64);
        REQUIRE(calls(sp, kResourceRelease).size() == 1u);
        CHECK(static_cast<u32>(calls(sp, kResourceRelease)[0].args[0]) == 0x1234u);
        CHECK(r32(m, kUnit + 84) == 0u);
        const bool model = it % 8 != 3;
        CHECK(calls(sp, kModelDestroy).size() == (model && destroy ? 1u : 0u));
        CHECK(r32(m, kUnit + 80) == (model && destroy ? 0u : (model ? 0x3000u : 0u)));
        u32 destroyed = 0;
        for (u32 i = 0; i < 5; ++i) {
            if ((tasks >> i) & 1) ++destroyed;
            CHECK(r32(m, kUnit + slots[i]) == 0u);
        }
        CHECK(calls(sp, kTaskDestroyHier).size() == destroyed);
    }
}

// sub_3B2CB0 (x, y, rgba, kind, font, text, flags; $f12 scale): the glyph list (frFontBuildGlyphList, stood in with a
// chain of two lines) gets x * 16 at +4, y * 8 at +8, the scale at +20 and the colour on every glyph (+16); the width is
// the first line's advances (+12) plus the spacing (+3, signed) per glyph when flags & 0xB, centred (8: x - width / 2)
// or right-aligned (2: x - width); flag 4 lifts y by the style size, 0x10 by *0x7CAD7C times it; kind 10 becomes 5 with
// the alpha scaled by *0x7CAD94; the chain is drawn and released unless a fade step is pending; the width is returned.
TEST_CASE("game(finalA): the frFontEx string layout") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    u32 seed = 1;
    for (const u32 flags : {0u, 1u, 2u, 8u, 4u, 0x10u, 0xBu}) {
        for (const u32 kind : {10u, 3u}) {
            for (const u32 fade : {0u, 1u}) {
                HwCheck hw = whole_ram_check();
                hw.gpr_in = {{GPR_T0, kFont}, {GPR_T1, kStr}, {GPR_T2, flags}};
                reset(m, base);
                wstr(m, kStr, "finalA");
                std::memset(m.at(kFont), 0, 0x100);
                wf32(m, 0x7CAD94u, 0.5f);
                wf32(m, 0x7CAD7Cu, 0.25f);
                w16(m, 0x7CD500u, 0x7FFCu);
                SiPair sp = run_pair_si(m, find_case(kCases, "sub_3B2CB0").hand, find_case(kCases, "sub_3B2CB0").recomp,
                                        Args{100, 200, 0x80FF4020u, sx(kind)}, seed++, "sub_3B2CB0", hw, [fade](StandInWorld& w) {
                                            install_field_world(w);
                                            w.si.install(kBuildGlyphList, "frFontBuildGlyphList", [](EEContext& ctx, StandIns&, StandInCall& c) {
                                                // two lines: the first with three glyphs (advances 10, 20, 30), the second with
                                                // two (5, 7); spacing +3 = -1 on the first line
                                                std::memset(ctx.memory->main_ram() + kChain, 0, 0x400);
                                                ctx.memory->write<u8>(kChain + 3, 0xFF);
                                                ctx.memory->write<u32>(kChain + 28, kGlyph);
                                                ctx.memory->write<u32>(kChain + 36, kChain + 64);
                                                ctx.memory->write<u8>(kChain + 64 + 3, 2);
                                                ctx.memory->write<u32>(kChain + 64 + 28, kGlyph + 48 * 3);
                                                static const u32 adv[] = {10, 20, 30, 5, 7};
                                                for (u32 i = 0; i < 5; ++i) {
                                                    ctx.memory->write<u32>(kGlyph + 48 * i + 12, adv[i]);
                                                    ctx.memory->write<u32>(kGlyph + 48 * i + 16, 0xDEADBEEFu);
                                                    ctx.memory->write<u32>(kGlyph + 48 * i + 40, i == 2 || i == 4 ? 0u : kGlyph + 48 * (i + 1));
                                                }
                                                c.v0 = kChain;
                                            });
                                            w.si.install_recorder(kGetStyleSize, "frFontGetStyleSize", 16);
                                            // (frFontDraw's entry point is a typed shim, not a hooked forwarder: it
                                            // draws the chain for real)
                                            w.si.install_recorder(kLineFadeStep, "frFontLineFadeStep", fade);
                                            w.si.install_recorder(kChainRelease, "sub_3B0030", 0);
                                        });
                const u32 width = flags & 0xBu ? 10u + 20u + 30u - 3u : 0u;
                CHECK(v0_u32(sp) == width);
                u32 x = 100, y = 200;
                if (flags & 8u) x -= width / 2;
                else if (flags & 2u) x -= width;
                if (flags & 4u) y -= 16;
                else if (flags & 0x10u) y = static_cast<u32>(static_cast<s32>(200.0f - 0.25f * 16.0f));
                CHECK(r32(m, kChain + 4) == x * 16u);
                CHECK(r32(m, kChain + 8) == y * 8u);
                const u32 colour = kind == 10u ? ((0x80FF4020u & 0xFFFFFF00u) | static_cast<u32>(0x20 * 0.5f)) : 0x80FF4020u;
                for (u32 i = 0; i < 5; ++i) CHECK(r32(m, kGlyph + 48 * i + 16) == colour);
                REQUIRE(calls(sp, kBuildGlyphList).size() == 1u);
                CHECK(static_cast<u32>(calls(sp, kBuildGlyphList)[0].args[2]) == (kind == 10u ? 5u : kind));
                CHECK(static_cast<u32>(calls(sp, kBuildGlyphList)[0].args[0]) == kStr);
                CHECK(calls(sp, kChainRelease).size() == (fade ? 0u : 1u));
                CHECK(calls(sp, kGetStyleSize).size() == ((flags & 0x14u) ? 1u : 0u));
                CHECK((r16(m, 0x7CD500u) & 3u) == 2u);
            }
        }
    }
}

#else

TEST_CASE("game(finalA): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
