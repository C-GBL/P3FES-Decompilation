// Pair tests of slice sweep2, group fx (game/src/sweep/sweep2_fx.cpp): every body against its recompiled body
// (handgen_pairs.h / pair_harness.h / stand_ins.h) on
//   * random worlds: the p3fes_handgen sweep;
//   * the dorm snapshot's RenderWare: class 10 kind 9's constructor (block layout, a real strip mesh and its texture
//     coordinates), its coordinate rule in both background modes and its init on a fake mesh;
//   * hand-built instances: effect class 23's bare create, clone and step past the end, class 30 kind 1's re-roll
//     period and alpha rule.
#include "sweep2_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s2t;

namespace p3fes::recomp_gen {
void fn_sub_3402C0_003402c0(EEContext&);  // generated body
void fn_sub_3402C0_003402c0__recomp(EEContext&);  // recompiled
void fn_sub_3403B0_003403b0(EEContext&);  // generated body
void fn_sub_3403B0_003403b0__recomp(EEContext&);  // recompiled
void fn_sub_340600_00340600(EEContext&);  // generated body
void fn_sub_340600_00340600__recomp(EEContext&);  // recompiled
void fn_sub_3406F0_003406f0(EEContext&);  // generated body
void fn_sub_3406F0_003406f0__recomp(EEContext&);  // recompiled
void fn_sub_340790_00340790(EEContext&);  // generated body
void fn_sub_340790_00340790__recomp(EEContext&);  // recompiled
void fn_sub_3407E0_003407e0(EEContext&);  // generated body
void fn_sub_3407E0_003407e0__recomp(EEContext&);  // recompiled
void fn_sub_341BA0_00341ba0(EEContext&);  // generated body
void fn_sub_341BA0_00341ba0__recomp(EEContext&);  // recompiled
void fn_sub_350230_00350230(EEContext&);  // generated body
void fn_sub_350230_00350230__recomp(EEContext&);  // recompiled
void fn_sub_350450_00350450(EEContext&);  // generated body
void fn_sub_350450_00350450__recomp(EEContext&);  // recompiled
void fn_sub_3505D0_003505d0(EEContext&);  // generated body
void fn_sub_3505D0_003505d0__recomp(EEContext&);  // recompiled
void fn_sub_351250_00351250(EEContext&);  // generated body
void fn_sub_351250_00351250__recomp(EEContext&);  // recompiled
void fn_sub_351E70_00351e70(EEContext&);  // generated body
void fn_sub_351E70_00351e70__recomp(EEContext&);  // recompiled
void fn_sub_3520A0_003520a0(EEContext&);  // generated body
void fn_sub_3520A0_003520a0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_3402C0", 0x3402C0, &recomp_gen::fn_sub_3402C0_003402c0, &recomp_gen::fn_sub_3402C0_003402c0__recomp},
    {"sub_3403B0", 0x3403B0, &recomp_gen::fn_sub_3403B0_003403b0, &recomp_gen::fn_sub_3403B0_003403b0__recomp},
    {"sub_340600", 0x340600, &recomp_gen::fn_sub_340600_00340600, &recomp_gen::fn_sub_340600_00340600__recomp},
    {"sub_3406F0", 0x3406F0, &recomp_gen::fn_sub_3406F0_003406f0, &recomp_gen::fn_sub_3406F0_003406f0__recomp},
    {"sub_340790", 0x340790, &recomp_gen::fn_sub_340790_00340790, &recomp_gen::fn_sub_340790_00340790__recomp},
    {"sub_3407E0", 0x3407E0, &recomp_gen::fn_sub_3407E0_003407e0, &recomp_gen::fn_sub_3407E0_003407e0__recomp},
    {"sub_341BA0", 0x341BA0, &recomp_gen::fn_sub_341BA0_00341ba0, &recomp_gen::fn_sub_341BA0_00341ba0__recomp},
    {"sub_350230", 0x350230, &recomp_gen::fn_sub_350230_00350230, &recomp_gen::fn_sub_350230_00350230__recomp},
    {"sub_350450", 0x350450, &recomp_gen::fn_sub_350450_00350450, &recomp_gen::fn_sub_350450_00350450__recomp},
    {"sub_3505D0", 0x3505D0, &recomp_gen::fn_sub_3505D0_003505d0, &recomp_gen::fn_sub_3505D0_003505d0__recomp},
    {"sub_351250", 0x351250, &recomp_gen::fn_sub_351250_00351250, &recomp_gen::fn_sub_351250_00351250__recomp},
    {"sub_351E70", 0x351E70, &recomp_gen::fn_sub_351E70_00351e70, &recomp_gen::fn_sub_351E70_00351e70__recomp},
    {"sub_3520A0", 0x3520A0, &recomp_gen::fn_sub_3520A0_003520a0, &recomp_gen::fn_sub_3520A0_003520a0__recomp},
};

}  // namespace

TEST_CASE("game(sweep2 fx): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep2 cases (real data and documented rules) ---

namespace {

constexpr u32 kInst = kScratch;           // a hand-built effect instance
constexpr u32 kParams = kScratch + 0x400;  // its parameters
constexpr u32 kObj = kScratch + 0x800;     // a kind object {records, mesh, block}
constexpr u32 kRecords = kScratch + 0x900;
constexpr u32 kMesh = kScratch + 0x1000;   // a fake RW mesh: +0 flags, +8 vertex count, +16 the atomic
constexpr u32 kAtomic = kScratch + 0x1100;
constexpr u32 kGeometry = kScratch + 0x1200;  // RpGeometry: +12 lock flags, +20 vertices, +24 morph targets, +52 uv, +92 morph
constexpr u32 kMorph = kScratch + 0x1400;
constexpr u32 kVerts = kScratch + 0x1800;
constexpr u32 kUv = kScratch + 0x2000;

u32 rw_malloc_size(const SiPair& sp) {
    const std::vector<StandInCall> c = calls(sp, kRwSlotFns[0]);
    return c.empty() ? 0u : static_cast<u32>(c[0].args[0]);
}

// The fake mesh of the kind-9 helpers: `nverts` vertices of 12 bytes, a texture-coordinate array of 8 records x 64
// bytes, one morph target.
void put_fake_mesh(Machine& m, u16 mesh_flags, u16 nverts) {
    std::memset(m.at(kMesh), 0, 0x3000);
    w16(m, kMesh + 0, mesh_flags);
    w16(m, kMesh + 8, nverts);
    w32(m, kMesh + 16, kAtomic);
    w32(m, kAtomic + 24, kGeometry);
    w32(m, kGeometry + 20, nverts);
    w32(m, kGeometry + 24, 1);
    w32(m, kGeometry + 52, kUv);
    w32(m, kGeometry + 92, kMorph);
    w32(m, kMorph + 20, kVerts);
    for (u32 i = 0; i < 12u * nverts; ++i) w8(m, kVerts + i, static_cast<u8>(0xA0 + i));
}

}  // namespace

// sub_3403B0 [k10Band9BuildUv]: the documented coordinate rule on a fake mesh, both background modes -- with the mode
// set every record spans the whole texture; clear, odd records start at 0.5 and even records end at 0.5. The u values
// +164 (top) / +168 (bottom) land in words 9 / 11 and 1 / 3 of each 64-byte record.
TEST_CASE("game(sweep2 fx): the class-10 kind 9 texture coordinates") {
    std::vector<u8> base;
    auto mp = snap_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or dorm snapshot");
        return;
    }
    Machine& m = *mp;
    for (const s8 bg : {s8{0}, s8{1}}) {
        for (const u32 count : {1u, 2u, 7u}) {
            auto prep = [&](Machine& mm) {
                put_fake_mesh(mm, 4, 16);
                std::memset(mm.at(kParams), 0, 0x108);
                w32(mm, kParams + 56, count);
                wf32(mm, kParams + game::sw2::kBand9TopU, 0.25f);
                wf32(mm, kParams + game::sw2::kBand9BottomU, 0.75f);
                w8(mm, kParams + game::sw2::kBand9BgMode, static_cast<u8>(bg));
                w32(mm, kObj + 4, kMesh);
            };
            const SiPair sp = run_case_w(m, base, kCases, "sub_3403B0", {kObj, kParams, 0, 0}, 100 + count + 10u * bg, prep);
            INFO("bg " << int(bg) << " count " << count);
            for (u32 i = 0; i < count; ++i) {
                const u32 r = kUv + 64 * i;
                CHECK(rf32(m, r + 4) == 0.75f);
                CHECK(rf32(m, r + 12) == 0.75f);
                CHECK(rf32(m, r + 36) == 0.25f);
                CHECK(rf32(m, r + 44) == 0.25f);
                if (bg) {
                    CHECK(rf32(m, r + 0) == 0.0f);
                    CHECK(rf32(m, r + 8) == 1.0f);
                } else if (i & 1) {
                    CHECK(rf32(m, r + 0) == 0.5f);
                    CHECK(rf32(m, r + 8) == 1.0f);
                } else {
                    CHECK(rf32(m, r + 0) == 0.0f);
                    CHECK(rf32(m, r + 8) == 0.5f);
                }
            }
            CHECK(r32(m, kUv + 64 * count) == 0u);  // nothing past the count
            CHECK((r16(m, kGeometry + 12) & 1u) == 1u);  // mesh flags bit 2 -> double-sided
        }
    }
}

// sub_3402C0 [k10Band9Init]: the vertices are cleared (12 bytes x the mesh's count), every record of the parameters'
// count is freed (word 0 = -1, stride 40) and nothing past it; the double-sided flag follows the mesh flags bit 2.
TEST_CASE("game(sweep2 fx): the class-10 kind 9 init") {
    std::vector<u8> base;
    auto mp = snap_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or dorm snapshot");
        return;
    }
    Machine& m = *mp;
    for (const u16 flags : {u16{0}, u16{4}}) {
        for (const u32 count : {0u, 3u, 9u}) {
            auto prep = [&](Machine& mm) {
                put_fake_mesh(mm, flags, 10);
                std::memset(mm.at(kInst), 0, 0x100);
                std::memset(mm.at(kParams), 0, 0x108);
                w32(mm, kInst + game::sw2::kK10Obj, kObj);
                w32(mm, kInst + game::sw2::kK10Params, kParams);
                w32(mm, kParams + 56, count);
                w32(mm, kObj + 0, kRecords);
                w32(mm, kObj + 4, kMesh);
                for (u32 i = 0; i < 12; ++i) w32(mm, kRecords + 40 * i, 5 + i);
            };
            const SiPair sp = run_case_w(m, base, kCases, "sub_3402C0", {kInst, 0, 0, 0}, 200 + count + flags, prep);
            INFO("flags " << flags << " count " << count);
            for (u32 i = 0; i < 12u * 10u; ++i) CHECK(r8(m, kVerts + i) == 0u);
            for (u32 i = 0; i < 12; ++i) CHECK(r32(m, kRecords + 40 * i) == (i < count ? 0xFFFFFFFFu : 5 + i));
            CHECK((r16(m, kGeometry + 12) & 1u) == (flags & 4u ? 1u : 0u));
        }
    }
}

// sub_340600 [k10Band9Create] on the dorm snapshot's RenderWare: one RwMalloc block of 16 + 40 * count bytes with the
// effect hint, its head pointing at its records (+0) and at itself (+8), a real strip mesh at +4 whose texture
// coordinates follow the rule above (background mode 0).
TEST_CASE("game(sweep2 fx): the class-10 kind 9 constructor") {
    std::vector<u8> base;
    auto mp = snap_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or dorm snapshot");
        return;
    }
    Machine& m = *mp;
    for (const u32 count : {1u, 4u}) {
        auto prep = [&](Machine& mm) {
            std::memset(mm.at(kParams), 0, 0x108);
            w32(mm, kParams + 56, count);
            wf32(mm, kParams + game::sw2::kBand9TopU, 0.125f);
            wf32(mm, kParams + game::sw2::kBand9BottomU, 0.875f);
        };
        const SiPair sp = run_case_w(m, base, kCases, "sub_340600", {kParams, 0, 0, 0}, 300 + count, prep);
        INFO("count " << count);
        CHECK(rw_malloc_size(sp) == 16u + 40u * count);
        const std::vector<StandInCall> c = calls(sp, kRwSlotFns[0]);
        REQUIRE(!c.empty());
        CHECK(static_cast<u32>(c[0].args[1]) == 0x40000u);
        const u32 blk = static_cast<u32>(v0_of(sp.hw));
        REQUIRE(blk != 0u);
        CHECK(r32(m, blk + 0) == blk + 16);
        CHECK(r32(m, blk + 8) == blk);
        const u32 mesh = r32(m, blk + 4);
        if (mesh == 0) continue;  // no mesh on this snapshot's heap: the pair above is the check
        const u32 geo = r32(m, r32(m, mesh + 16) + 24);
        const u32 uv = r32(m, geo + 52);
        REQUIRE(uv != 0u);
        for (u32 i = 0; i < count; ++i) {
            CHECK(rf32(m, uv + 64 * i + 4) == 0.875f);
            CHECK(rf32(m, uv + 64 * i + 36) == 0.125f);
            CHECK(rf32(m, uv + 64 * i + 0) == ((i & 1) ? 0.5f : 0.0f));
        }
    }
}

// Effect class 23: the bare create (sub_350230(0): 176 zero bytes but word 0 = -1), the clone of a hand-built instance
// without a mesh (frame count and the 152-byte body copied, no mesh) and the step past the end frame (+152: only the
// frame counts, nothing is drawn).
TEST_CASE("game(sweep2 fx): effect class 23 create / clone / step") {
    std::vector<u8> base;
    auto mp = snap_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or dorm snapshot");
        return;
    }
    Machine& m = *mp;
    {
        const SiPair sp = run_case_w(m, base, kCases, "sub_350230", {0, 0, 0, 0}, 400, {});
        CHECK(rw_malloc_size(sp) == u32{game::sw2::kC23Size});
        const u32 blk = static_cast<u32>(v0_of(sp.hw));
        REQUIRE(blk != 0u);
        CHECK(r32(m, blk) == 0xFFFFFFFFu);
        for (u32 i = 4; i < 176; ++i) CHECK(r8(m, blk + i) == 0u);
    }
    auto inst = [&](Machine& mm) {
        std::memset(mm.at(kInst), 0, 176);
        w32(mm, kInst + 0, 7);
        w32(mm, kInst + 4, 33);
        for (u32 i = 0; i < 152; ++i) w8(mm, kInst + 12 + i, static_cast<u8>(i * 3 + 1));
    };
    {
        const SiPair sp = run_case_w(m, base, kCases, "sub_350450", {kInst, 0, 0, 0}, 401, inst);
        const u32 blk = static_cast<u32>(v0_of(sp.hw));
        REQUIRE(blk != 0u);
        CHECK(r32(m, blk + 0) == 0xFFFFFFFFu);
        CHECK(r32(m, blk + 4) == 33u);
        CHECK(std::memcmp(m.at(blk + 12), m.at(kInst + 12), 152) == 0);
        CHECK(r32(m, blk + game::sw2::kC23Mesh) == 0u);
    }
    for (const u32 frame : {0u, 9u}) {
        const SiPair sp = run_case_w(m, base, kCases, "sub_351250", {kInst, 0, 0, 0}, 402 + frame, [&](Machine& mm) {
            inst(mm);
            w32(mm, kInst + 8, frame);
            w32(mm, kInst + 152, 1);  // the end frame: frame + 1 is past it
        });
        CHECK(r32(m, kInst + 8) == frame + 1);
        CHECK(sp.recomp->si.log.empty());
    }
}

// Class 30 kind 1's update (sub_351E70): the rows are re-rolled only every +76 frames (frame % period == 0), each row's
// alpha = 255 x (1 - k + k x r) -- 255 for k (+100) = 0 --, the frame always counts; past a non-zero end nothing runs.
TEST_CASE("game(sweep2 fx): class 30 kind 1 strip re-roll period") {
    std::vector<u8> base;
    auto mp = snap_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or dorm snapshot");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kState = kScratch + 0x600, kRows = kScratch + 0x700;
    for (const u32 frame : {5u, 8u, 12u, 40u}) {
        const u32 end = frame == 40u ? 20u : 0u;
        auto prep = [&](Machine& mm) {
            std::memset(mm.at(kInst), 0, 0x40);
            std::memset(mm.at(kParams), 0, 0x94);
            std::memset(mm.at(kRows), 0x11, 8 * 6);
            w32(mm, kInst + 20, frame);
            w32(mm, kInst + 28, kState);
            w32(mm, kInst + 32, kParams);
            w32(mm, kState, kRows);
            w32(mm, kParams + 52, end);
            w32(mm, kParams + 56, 6);
            w32(mm, kParams + 76, 4);
        };
        run_case_w(m, base, kCases, "sub_351E70", {kInst, 0, 0, 0}, 500 + frame, prep);
        INFO("frame " << frame);
        const bool runs = end == 0;
        CHECK(r32(m, kInst + 20) == (runs ? frame + 1 : frame));
        const bool reroll = runs && frame % 4 == 0;
        for (u32 i = 0; i < 6; ++i) CHECK(r8(m, kRows + 8 * i + 2) == (reroll ? 255u : 0x11u));
    }
}

// Class 10 kind 9's update (sub_3407E0) on a fake mesh with every record free (-1): each update spawns at most the
// budget +80 records (word 0 = 0), a burst (+85) at frame 0 spawns the whole count at random start ages below the life
// +76, a life of 0 emits nothing, and past a non-zero end (+52) nothing runs at all.
TEST_CASE("game(sweep2 fx): the class-10 kind 9 emission budget") {
    std::vector<u8> base;
    auto mp = snap_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or dorm snapshot");
        return;
    }
    Machine& m = *mp;
    constexpr u32 kFrame = kScratch + 0x2C00, kColors = kScratch + 0x2800;
    struct Run {
        u32 frame, life, budget, end;
        u8 burst;
    };
    const Run runs[] = {{3, 10, 2, 0, 0}, {0, 10, 2, 0, 0}, {0, 10, 2, 0, 1}, {3, 10, 2, 0, 1}, {3, 0, 2, 0, 0}, {9, 10, 2, 5, 1}};
    u32 seed = 600;
    for (const Run& r : runs) {
        constexpr u32 kCount = 6;
        run_case_w(m, base, kCases, "sub_3407E0", {kInst, 0, 0, 0}, ++seed, [&](Machine& mm) {
            put_fake_mesh(mm, 0, 8 * kCount);
            std::memset(mm.at(kFrame), 0, 0x100);
            std::memset(mm.at(kColors), 0, 4 * 8 * kCount);
            w32(mm, kAtomic + 4, kFrame);
            w32(mm, kGeometry + 48, kColors);
            std::memset(mm.at(kInst), 0, 0x100);
            std::memset(mm.at(kParams), 0, 0x108);
            w32(mm, kInst + game::sw2::kK10Frame, r.frame);
            w32(mm, kInst + game::sw2::kK10Obj, kObj);
            w32(mm, kInst + game::sw2::kK10Params, kParams);
            w32(mm, kObj + 0, kRecords);
            w32(mm, kObj + 4, kMesh);
            w32(mm, kParams + 52, r.end);
            w32(mm, kParams + 56, kCount);
            w32(mm, kParams + 76, r.life);
            w32(mm, kParams + 80, r.budget);
            w8(mm, kParams + 85, r.burst);
            wf32(mm, kParams + 96, 1.0f);
            for (u32 i = 0; i < kCount; ++i) {
                std::memset(mm.at(kRecords + game::sw2::kBand9Record * i), 0, game::sw2::kBand9Record);
                w32(mm, kRecords + game::sw2::kBand9Record * i, 0xFFFFFFFFu);
            }
        });
        INFO("frame " << r.frame << " life " << r.life << " burst " << int(r.burst) << " end " << r.end);
        const bool runs_now = r.end == 0 || r.frame <= r.end;
        const u32 want = !runs_now || r.life == 0 ? 0u : (r.burst && r.frame == 0 ? kCount : r.budget);
        u32 spawned = 0;
        for (u32 i = 0; i < kCount; ++i) {
            const u32 w = r32(m, kRecords + game::sw2::kBand9Record * i);
            if (w == 0xFFFFFFFFu) continue;
            ++spawned;
            if (r.burst && r.frame == 0)
                CHECK(w < r.life);
            else
                CHECK(w == 0u);
        }
        CHECK(spawned == want);
    }
}

// --- end of the sweep2 cases ---

#else

TEST_CASE("game(sweep2 fx): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
