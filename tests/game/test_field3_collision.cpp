// Pair tests for slice field3, part "collision" (game/src/field/field3_collision.cpp): the collision controller, the
// sphere-contact push-out, the ground ray, the transparent-wall pickers, the move / warp helpers and the "collis
// mover" / "death se" tasks, each body against its recompiled body (`__recomp`) on identical guest machines.
//  * Every pair compares the whole register file (GPRs in 128 bits, HI/LO, FPRs, FCR31, ACC) and the cycle count at
//    every check point and at the return / stop, all 32 MiB of RAM (write-tracked) including the dead stack, the
//    scratchpad and the bus log -- tests/game/handgen_pairs.h (hgp::pair: random FPRs, so $f12 arguments vary) or
//    tests/game/stand_ins.h (run_pair_si: the heap / kwln task creation / file layer stand-ins, recorders for the RW
//    walks this build does not emit, call logs compared).
//  * The worlds are the functions' real records (the controller work, the model matrix, sField +4460, the scene
//    record, the field units, the mover queue), built by hand, and the real Tartarus floor of the climb route's
//    snapshot climb_ref_17000 (skipped when absent); the generic random pass of the skeleton stays.
//  * Documented rules (26_field.md 4.2, the file comments) are checked on the recompiled run's output: the grid cell
//    (int)((x + 400) / 800), the controller's state machine, the three-thirds move, the ground snap, the footstep
//    for characters only, the unit lookup of K_FldFrame_CreateCtlTask, the queue rules of the mover.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field3_collision.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
#define F3C_DECL(name, addr) void fn_##name##_##addr(p3fes::EEContext&); void fn_##name##_##addr##__recomp(p3fes::EEContext&);
P3FES_FIELD3_COLLISION_BODIES(F3C_DECL)
#undef F3C_DECL
}  // namespace p3fes::recomp_gen

namespace p3fes::game_test {
namespace {

namespace rg = p3fes::recomp_gen;

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
#define F3C_CASE(name, addr) {#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp},
    P3FES_FIELD3_COLLISION_BODIES(F3C_CASE)
#undef F3C_CASE
};

Machine* machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        write_rw_slots(*mm);
        return mm;
    }();
    return m;
}
#define NEED_MACHINE()                                    \
    Machine* mp = machine();                              \
    if (!mp) {                                            \
        MESSAGE("SKIP: no ELF at " << elf_path());        \
        return;                                           \
    }                                                     \
    Machine& m = *mp

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void putf(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }
u32 get32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 get16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
float getf(Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
float bits_f(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
s32 grid_cell(float x) { return static_cast<s32>((x + 400.0f) / 800.0f); }  // cvt.w.s truncates

// guest memory from a stand-in
u32 g32(EEContext& ctx, u32 va) {
    u32 v;
    std::memcpy(&v, ctx.memory->main_ram() + va, 4);
    return v;
}
float gf(EEContext& ctx, u32 va) { return bits_f(g32(ctx, va)); }
void s32g(EEContext& ctx, u32 va, u32 v) { std::memcpy(ctx.memory->main_ram() + va, &v, 4); }
void sfg(EEContext& ctx, u32 va, float f) { std::memcpy(ctx.memory->main_ram() + va, &f, 4); }

// --- the built world ------------------------------------------------------------------------------------------------
constexpr u32 kField = 0x869F60u;           // sField
constexpr u32 kFieldCollision = 4460;       // sField +4460: the collision record
constexpr u32 kSceneSlot = 0x7CD540u;       // gp-22448 -> the scene record
constexpr u32 kW = 0x01810000u;             // the world (above the harness arena, below the stand-in heap)
constexpr u32 kTask = kW;                   // a kwln task record: +60 work, +80 first child
constexpr u32 kChild = kW + 0x80u;          // the "collis sphere" child task
constexpr u32 kChildWork = kW + 0xC0u;
constexpr u32 kWork = kW + 0x100u;          // the controller work (52 bytes)
constexpr u32 kModel = kW + 0x200u;         // the model matrix (position at +48)
constexpr u32 kCollRec = kW + 0x300u;       // the field's collision record {+0 flags, +8 clump, +12 world}
constexpr u32 kScene = kW + 0x340u;         // the scene record {major, minor, mgr}
constexpr u32 kRwWorld = kW + 0x380u;       // a stand-in "RW collision world"
constexpr u32 kLine = kW + 0x400u;          // a line {start, end}
constexpr u32 kOut = kW + 0x440u;           // a result vector
constexpr u32 kMover = kW + 0x1000u;        // the "collis mover" work (1,440 bytes)
constexpr u32 kWorldSize = 0x2000u;

constexpr u32 kRayWorldCb = 0x1AC950u;      // sub_1AC950: the ground ray's world triangle callback
constexpr u32 kCollideWorldCb = 0x1AAF30u;  // sub_1AAF30: the sphere's world triangle callback
constexpr u32 kWorldWalk = 0x464020u;       // the RW collision-world walk (not emitted in this build)

void clear_world(Machine& m) { std::memset(m.at(kW), 0, kWorldSize); }

void put_scene(Machine& m, std::mt19937& rng) {
    static const s32 majors[] = {1, 8, 21, 22, 27, 32, 51, 60, 4};
    put32(m, kSceneSlot, kScene);
    put32(m, kScene + 0, static_cast<u32>(majors[rng() % 9]));
    put32(m, kScene + 4, chance(rng, 60) ? 0u : 1u + rng() % 3);
    put32(m, kScene + 8, 0);  // no resource manager: MT_Scene_GetRes / GetResListHead give 0
}

void put_matrix(Machine& m, u32 at, std::mt19937& rng) {
    for (u32 k = 0; k < 64; k += 4) put32(m, at + k, 0);
    putf(m, at + 0, 1.0f);
    putf(m, at + 20, 1.0f);
    putf(m, at + 40, 1.0f);
    // a forward axis (+32) that is not unit length, now and then
    if (chance(rng, 50)) {
        putf(m, at + 32, frand(rng, -2.0f, 2.0f));
        putf(m, at + 36, frand(rng, -0.5f, 0.5f));
        putf(m, at + 40, frand(rng, -2.0f, 2.0f));
    }
    put32(m, at + 12, rng() % 4);  // the RwMatrix flags word
    putf(m, at + 48, frand(rng, -6000.0f, 6000.0f));
    putf(m, at + 52, frand(rng, -300.0f, 300.0f));
    putf(m, at + 56, frand(rng, -6000.0f, 6000.0f));
}

// The ground the stand-in walk reports for the ray (sub_1AC950's query {+0 result pointer, +4 hit}).
struct Ground {
    bool hit = false;
    float y = 0.0f;
};

WorldSetup controller_world(Ground g) {
    return [g](StandInWorld& w) {
        install_standard(w);
        w.si.install_recorder(0x1DA020u, "K_Footstep_Update(sub_1DA020)");
        w.si.install_recorder(0x4916D0u, "RpClumpForAllAtomics(sub_4916D0)");
        w.si.install_recorder(0x464120u, "RpAtomicForAllIntersections(sub_464120)");
        w.si.install_recorder(0x318B80u, "sub_318B80");
        w.si.install_recorder(0x4C2CC0u, "sub_4C2CC0");
        w.si.install_recorder(0x4C2D20u, "sub_4C2D20");
        w.si.install_recorder(0x4C2F10u, "sub_4C2F10");
        w.si.install_recorder(0x1A4CD0u, "sub_1A4CD0", kW + 0x1F00u);
        w.si.install_recorder(0x1A4DC0u, "sub_1A4DC0");
        w.si.install_recorder(0x1A4E60u, "sub_1A4E60");
        // the push-out halves of K_FldFrame_HandleCollis (left recompiled, not emitted here): "step unchanged"
        w.si.install_recorder(0x1AB390u, "K_FldFrame_CollideWorld(sub_1AB390)");
        w.si.install_recorder(0x1ABD20u, "K_FldFrame_CollideClump(sub_1ABD20)");
        w.si.install_recorder(0x1AD9E0u, "K_FldFrame_CtlSetOrientation(sub_1AD9E0)");
        w.si.install(kWorldWalk, "RpCollisionWorldForAllIntersections(sub_464020)",
                     [g](EEContext& ctx, StandIns&, StandInCall& c) {
                         const u32 line = static_cast<u32>(c.args[1]);
                         const u32 cb = static_cast<u32>(c.args[2]);
                         const u32 data = static_cast<u32>(c.args[3]);
                         if (cb == kRayWorldCb && g.hit) {  // the first triangle the line meets
                             const u32 out = g32(ctx, data);
                             sfg(ctx, out + 0, gf(ctx, line + 0));
                             sfg(ctx, out + 4, g.y);
                             sfg(ctx, out + 8, gf(ctx, line + 8));
                             s32g(ctx, data + 4, 1);
                         }
                         c.v0 = c.args[0];
                     });
    };
}

}  // namespace

TEST_CASE("game(field3_collision): every body equals its recompiled body on random worlds") {
    NEED_MACHINE();
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 48u;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(m, kW, 0x10000u, rng);
            const Args args{hgp::random_arg(rng, kW, 0x10000u), hgp::random_arg(rng, kW, 0x10000u),
                            hgp::random_arg(rng, kW, 0x10000u), hgp::random_arg(rng, kW, 0x10000u)};
            stops += hgp::pair(m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " random pairs, " + std::to_string(stops) +
                                    " stopped early";
        MESSAGE(summary);
    }
}

TEST_CASE("game(field3_collision): K_FldFrame_UpdateCtlTask -- the state machine, the three thirds, the ground snap") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3C001};
    int pairs = 0, moved = 0, snapped = 0, footsteps = 0;
    for (int i = 0; i < 600; ++i) {
        clear_world(m);
        put_scene(m, rng);
        // the task, its child (the debug sphere) and the work
        put32(m, kTask + 60, kWork);
        put32(m, kTask + 80, kChild);
        put32(m, kChild + 60, kChildWork);
        static const u32 states[] = {0, 0, 0, 0, 1, 1, 2};
        const u32 state = states[rng() % 7];
        u32 flags = rng() & 0x00FFFFFFu;
        if (chance(rng, 50)) flags |= 0x80000000u;  // debug sphere
        if (chance(rng, 60)) flags |= 0x40000000u;  // snap to the ground
        if (chance(rng, 20)) flags |= 0x10000000u;  // no collision
        if (chance(rng, 10)) flags |= 0x08000000u;  // frozen
        const u32 type = chance(rng, 70) ? 1u : 3u;
        const u32 low = chance(rng, 70) ? rng() % 100 : 100 + rng() % 924;
        const u32 id = (type << 10) | low;
        put32(m, kWork + 0, state);
        put32(m, kWork + 4, flags);
        put16(m, kWork + 8, static_cast<u16>(id));
        put16(m, kWork + 10, static_cast<u16>(rng() % 30));
        put32(m, kWork + 16, kModel);
        const float mv[3] = {frand(rng, -60.0f, 60.0f), frand(rng, -20.0f, 20.0f), frand(rng, -60.0f, 60.0f)};
        for (int k = 0; k < 3; ++k) putf(m, kWork + 20 + 4 * k, mv[k]);
        putf(m, kWork + 32, frand(rng, 0.0f, 60.0f));
        put32(m, kWork + 40, rng() % 5000);
        put_matrix(m, kModel, rng);
        // the field's collision record: an RW world (the stand-in walk) or none
        put32(m, kField + kFieldCollision, kCollRec);
        put32(m, kCollRec + 0, 1);
        const bool world = chance(rng, 50);
        put32(m, kCollRec + 12, world ? kRwWorld : 0u);
        Ground g;
        g.hit = world && chance(rng, 70);
        const float pos0[3] = {getf(m, kModel + 48), getf(m, kModel + 52), getf(m, kModel + 56)};
        g.y = pos0[1] + frand(rng, -150.0f, 150.0f);
        const SiPair p = run_pair_si(m, rg::fn_K_FldFrame_UpdateCtlTask_001ad2f0, rg::fn_K_FldFrame_UpdateCtlTask_001ad2f0__recomp,
                                     {kTask, rng(), rng(), rng()}, rng(), "K_FldFrame_UpdateCtlTask", hw, controller_world(g));
        ++pairs;
        CHECK(p.hw.recomp.gpr[GPR_V0].u64[0] == 0u);  // the kwln contract: keep running
        const std::size_t steps = p.recomp->si.calls_to(0x1DA020u);
        if (flags & 0x08000000u) {  // frozen: nothing
            CHECK(get32(m, kWork + 0) == state);
            CHECK(getf(m, kModel + 48) == pos0[0]);
            CHECK(steps == 0u);
        } else if (state == 1) {    // idle: the debug sphere follows flag bit 31
            CHECK(get32(m, kChildWork) == (flags >> 31));
            CHECK(get32(m, kWork + 0) == 1u);
        } else if (state == 2) {
            CHECK(get32(m, kWork + 0) == 2u);
            CHECK(getf(m, kModel + 48) == pos0[0]);
        } else {                    // a move: three thirds, then idle, the grid cell, the footstep for characters
            ++moved;
            CHECK(get32(m, kWork + 0) == 1u);
            const float x = getf(m, kModel + 48), z = getf(m, kModel + 56);
            CHECK(static_cast<s32>(get32(m, kWork + 44)) == grid_cell(x));
            CHECK(static_cast<s32>(get32(m, kWork + 48)) == grid_cell(z));
            CHECK(steps == ((low < 100) ? 1u : 0u));
            footsteps += static_cast<int>(steps);
            // the collision walk never changes the step here (no contacts), so the model moved by the displacement
            const float third_x = mv[0] / 3.0f, third_z = mv[2] / 3.0f;
            CHECK(std::fabs(x - (pos0[0] + third_x + third_x + third_x)) <= 0.01f + 1e-5f * std::fabs(pos0[0]));
            CHECK(std::fabs(z - (pos0[2] + third_z + third_z + third_z)) <= 0.01f + 1e-5f * std::fabs(pos0[2]));
            const bool snap = (flags & 0x40000000u) && !(flags & 0x10000000u);
            if (snap && g.hit) {  // the vertical displacement lands the model on the hit
                ++snapped;
                CHECK(std::fabs(getf(m, kModel + 52) - g.y) <= 0.01f + 1e-5f * std::fabs(g.y));
            } else if (!snap) {
                const float third_y = mv[1] / 3.0f;
                CHECK(std::fabs(getf(m, kModel + 52) - (pos0[1] + third_y + third_y + third_y)) <= 0.01f);
            }
        }
    }
    MESSAGE("UpdateCtlTask: " << pairs << " pairs, " << moved << " moves, " << snapped << " ground snaps, " << footsteps
                              << " footsteps");
    CHECK(moved > 100);
    CHECK(snapped > 20);
}

TEST_CASE("game(field3_collision): the controller / mover / death-se task creators on the stand-in heap") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3C002};
    int pairs = 0;
    for (int i = 0; i < 120; ++i) {
        clear_world(m);
        put_scene(m, rng);
        // K_FldFrame_CreateCtlTask(parent 0, id): no scene manager here -> no model; the work's fixed fields
        const u32 type = rng() % 4;
        const u32 id = (type << 10) | (rng() % 1024);
        const SiPair p = run_pair_si(m, rg::fn_K_FldFrame_CreateCtlTask_001ad660, rg::fn_K_FldFrame_CreateCtlTask_001ad660__recomp,
                                     {0, id, rng(), rng()}, rng(), "K_FldFrame_CreateCtlTask", hw, controller_world({}));
        ++pairs;
        const StandIns& si = p.recomp->si;
        REQUIRE(si.calls_to(0x104040u) >= 1);  // RwCalloc(1, 52) first
        CHECK(si.log[0].args[1] == 52u);
        const u32 work = static_cast<u32>(si.log[0].v0);
        CHECK(static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]) != 0u);  // the task
        CHECK(get32(m, work + 0) == 1u);                                // idle
        CHECK(get16(m, work + 8) == static_cast<u16>(id));
        CHECK(get32(m, work + 36) == 0u);
        CHECK(si.calls_to(0x104040u) == 2u);                            // + the "collis sphere" child's 4 bytes
    }
    for (int i = 0; i < 120; ++i) {
        clear_world(m);
        // sub_1AF930(parent 0, resource): "collis mover", the kind from the model's u16 +214 (high byte when >= 256)
        const u32 res = kW + 0x500u, mdl = kW + 0x600u;
        const u32 low = chance(rng, 70) ? rng() % 100 : 100 + rng() % 924;
        put16(m, res, static_cast<u16>((1u << 10) | low));
        put32(m, res + 296, mdl);
        const u16 kind = static_cast<u16>(chance(rng, 50) ? rng() % 256 : rng());
        put16(m, mdl + 214, kind);
        const SiPair p = run_pair_si(m, rg::fn_sub_1AF930_001af930, rg::fn_sub_1AF930_001af930__recomp, {0, res, rng(), rng()},
                                     rng(), "sub_1AF930", hw, controller_world({}));
        ++pairs;
        const u32 work = static_cast<u32>(p.recomp->si.log[0].v0);
        CHECK(p.recomp->si.log[0].args[1] == 1440u);
        CHECK(get32(m, work + 12) == res);
        if (low < 100) {
            CHECK(get32(m, work + 16) == (kind >= 256 ? static_cast<u32>(kind >> 8) : kind));
            CHECK(get32(m, work + 1204) == 0u);
        } else {
            CHECK(get32(m, work + 1204) == 5u);
        }
    }
    for (int i = 0; i < 60; ++i) {
        // sub_1AAA20(parent 0, unit): "death se", work +0 = the unit
        const u32 unit = 0x86EDA0u + 448u * (rng() % 24);
        const SiPair p = run_pair_si(m, rg::fn_sub_1AAA20_001aaa20, rg::fn_sub_1AAA20_001aaa20__recomp, {0, unit, rng(), rng()},
                                     rng(), "sub_1AAA20", hw, controller_world({}));
        ++pairs;
        const u32 work = static_cast<u32>(p.recomp->si.log[0].v0);
        CHECK(p.recomp->si.log[0].args[1] == 12u);
        CHECK(get32(m, work) == unit);
        // sub_1AE3F0(parent 0): "collis sphere"
        const SiPair q = run_pair_si(m, rg::fn_sub_1AE3F0_001ae3f0, rg::fn_sub_1AE3F0_001ae3f0__recomp, {0, rng(), rng(), rng()},
                                     rng(), "sub_1AE3F0", hw, controller_world({}));
        ++pairs;
        CHECK(q.recomp->si.log[0].args[1] == 4u);
    }
    MESSAGE("task creators: " << pairs << " pairs");
}

TEST_CASE("game(field3_collision): the death-se update, the warp / snap / ray helpers on built worlds") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3C003};
    int pairs = 0, sounds = 0, rays = 0;
    for (int i = 0; i < 300; ++i) {
        clear_world(m);
        // sub_1AA8F0(task): the frame counter, the sound at 151 / 181 frames (the unit far from the hero: model positions)
        const u32 work = kW + 0x100u;
        put32(m, kTask + 60, work);
        const u32 unit = 0x86EDA0u;  // gFldUnitsEc[0] (its model at +80)
        put32(m, unit + 80, kModel);
        put_matrix(m, kModel, rng);
        put32(m, 0x8717A0u + 80, kModel + 0x80u);  // the hero's model
        put_matrix(m, kModel + 0x80u, rng);
        put32(m, work + 0, unit);
        const u32 mode = chance(rng, 30) ? 1u : rng() % 3;
        static const u32 counters[] = {0, 1, 150, 151, 152, 180, 181, 400};
        const u32 counter = counters[rng() % 8];
        put32(m, work + 4, mode);
        put32(m, work + 8, counter);
        const SiPair p = run_pair_si(m, rg::fn_sub_1AA8F0_001aa8f0, rg::fn_sub_1AA8F0_001aa8f0__recomp, {kTask, rng(), rng(), rng()},
                                     rng(), "sub_1AA8F0", hw, controller_world({}));
        ++pairs;
        const u32 after = get32(m, work + 8);
        CHECK((after == counter + 1u || after == 1u));  // counted, or reset at the period and counted
        if (mode == 1) CHECK(after == (counter >= 151u ? 1u : counter + 1u));
        if (after == 1u && counter != 0u) ++sounds;
    }
    for (int i = 0; i < 300; ++i) {
        clear_world(m);
        put_scene(m, rng);
        put32(m, kTask + 60, kWork);
        put32(m, kWork + 16, chance(rng, 90) ? kModel : 0u);
        putf(m, kWork + 32, frand(rng, 0.0f, 60.0f));
        put_matrix(m, kModel, rng);
        put32(m, kField + kFieldCollision, kCollRec);
        put32(m, kCollRec + 0, 1);
        put32(m, kCollRec + 12, kRwWorld);
        Ground g;
        g.hit = chance(rng, 70);
        g.y = getf(m, kModel + 52) - frand(rng, 0.0f, 300.0f);
        const float to[3] = {frand(rng, -9000.0f, 9000.0f), frand(rng, -100.0f, 100.0f), frand(rng, -9000.0f, 9000.0f)};
        for (int k = 0; k < 3; ++k) putf(m, kOut + 4 * k, to[k]);
        const bool model = get32(m, kWork + 16) != 0;
        // sub_1ADC20(task, position): warp + the grid cell
        run_pair_si(m, rg::fn_sub_1ADC20_001adc20, rg::fn_sub_1ADC20_001adc20__recomp, {kTask, kOut, rng(), rng()}, rng(),
                    "sub_1ADC20", hw, controller_world(g));
        ++pairs;
        if (model) {
            CHECK(getf(m, kModel + 48) == to[0]);
            CHECK(static_cast<s32>(get32(m, kWork + 44)) == grid_cell(to[0]));
            CHECK(static_cast<s32>(get32(m, kWork + 48)) == grid_cell(to[2]));
        }
        // sub_1AE0D0(task): 3.0 above the ground under the model
        if (!model) continue;
        const SiPair q = run_pair_si(m, rg::fn_sub_1AE0D0_001ae0d0, rg::fn_sub_1AE0D0_001ae0d0__recomp, {kTask, rng(), rng(), rng()},
                                     rng(), "sub_1AE0D0", hw, controller_world(g));
        ++pairs;
        if (g.hit) {
            ++rays;
            CHECK(getf(m, kModel + 52) == g.y + 3.0f);
            CHECK(static_cast<s32>(get32(m, kWork + 44)) == grid_cell(getf(m, kModel + 48)));
        } else {
            CHECK(q.hw.recomp.gpr[GPR_V0].u64[0] == 0u);
        }
        // sub_1ACC30(line, out): the world path -- the stand-in walk's first triangle
        for (int k = 0; k < 6; ++k) putf(m, kLine + 4 * k, frand(rng, -5000.0f, 5000.0f));
        const SiPair r = run_pair_si(m, rg::fn_sub_1ACC30_001acc30, rg::fn_sub_1ACC30_001acc30__recomp, {kLine, kOut, rng(), rng()},
                                     rng(), "sub_1ACC30", hw, controller_world(g));
        ++pairs;
        CHECK(r.hw.recomp.gpr[GPR_V0].u64[0] == (g.hit ? 1u : 0u));
        if (g.hit) CHECK(getf(m, kOut + 4) == g.y);
    }
    MESSAGE("death se / warp / snap / ray: " << pairs << " pairs, " << sounds << " sounds, " << rays << " ground hits");
}

TEST_CASE("game(field3_collision): the mover queue and the controller's forward move ($f12 from the pair's FPRs)") {
    NEED_MACHINE();
    std::mt19937 rng{0xF3C005};
    int pairs = 0, queued = 0, popped = 0, forward = 0;
    for (u32 seed = 1; seed <= 300; ++seed) {
        clear_world(m);
        put_scene(m, rng);
        put32(m, kField + kFieldCollision, kCollRec);
        put32(m, kCollRec + 0, 1);
        put32(m, kCollRec + 12, 0);  // no world: the ray misses, the target stays as given
        put32(m, kTask + 60, kMover);
        const u32 mode = chance(rng, 70) ? 0u : (chance(rng, 70) ? 1u : 2u);
        const u32 count = chance(rng, 15) ? 47u : rng() % 47;
        const u32 count2 = chance(rng, 15) ? 7u : rng() % 7;
        put32(m, kMover + 4, chance(rng, 20) ? 0x80000000u : 0u);  // debug markers (not emitted: the run stops there)
        put32(m, kMover + 24, mode);
        put32(m, kMover + 28, count);
        put32(m, kMover + 1240, count2);
        for (u32 k = 0; k < 47 * 24; k += 4) put32(m, kMover + 32 + k, rng());
        for (u32 k = 0; k < 47; ++k) put32(m, kMover + 32 + 24 * k + 20, 0);  // no marker tasks
        const float to[3] = {frand(rng, -5000.0f, 5000.0f), frand(rng, -100.0f, 100.0f), frand(rng, -5000.0f, 5000.0f)};
        for (int k = 0; k < 3; ++k) putf(m, kOut + 4 * k, to[k]);
        const bool nudge = chance(rng, 30);
        const hgp::Run r = nudge ? hgp::pair(m, rg::fn_sub_1AFD40_001afd40, rg::fn_sub_1AFD40_001afd40__recomp, {kTask, kOut, 0, 0},
                                             seed, "sub_1AFD40")
                                 : hgp::pair(m, rg::fn_sub_1AFA20_001afa20, rg::fn_sub_1AFA20_001afa20__recomp, {kTask, kOut, 0, 0},
                                             seed, "sub_1AFA20");
        ++pairs;
        if (r.stopped) continue;  // a debug marker: sub_1A4CD0 is not in this build
        const u32 v0 = static_cast<u32>(r.end.gpr[GPR_V0].u64[0]);
        const u32 speed = r.end.fpr[12];
        if (nudge || mode == 0) {
            const bool room = count < 47;
            CHECK(v0 == (room ? 1u : 0u));
            if (room) {
                ++queued;
                const u32 e = kMover + 32 + 24 * count;
                CHECK(get32(m, kMover + 28) == count + 1);
                CHECK(get32(m, e) == (nudge ? 3u : 0u));
                CHECK(getf(m, e + 4) == to[0]);
                CHECK(getf(m, e + 8) == to[1]);
                CHECK(get32(m, e + 16) == speed);
            }
        } else if (mode == 1) {
            const bool room = count2 < 7;
            CHECK(v0 == (room ? 1u : 0u));
            if (room) {
                ++queued;
                CHECK(get32(m, kMover + 1240) == count2 + 1);
                CHECK(getf(m, kMover + 1248 + 24 * count2) == to[0]);
                CHECK(get32(m, kMover + 1248 + 24 * count2 + 12) == speed);
            }
        } else {
            CHECK(v0 == 0u);
        }
        // sub_1AE480(task): the front entry goes, the rest move down
        const u32 before = get32(m, kMover + 28);
        u32 second[6];
        for (u32 k = 0; k < 6; ++k) second[k] = get32(m, kMover + 32 + 24 + 4 * k);
        const hgp::Run q = hgp::pair(m, rg::fn_sub_1AE480_001ae480, rg::fn_sub_1AE480_001ae480__recomp, {kTask, 0, 0, 0}, seed,
                                     "sub_1AE480");
        ++pairs;
        if (q.stopped) continue;
        if (static_cast<s32>(before) > 0) {
            ++popped;
            CHECK(q.end.gpr[GPR_V0].u64[0] == 1u);
            CHECK(get32(m, kMover + 28) == before - 1);
            if (before > 1)
                for (u32 k = 0; k < 5; ++k) CHECK(get32(m, kMover + 32 + 4 * k) == second[k]);
        } else {
            CHECK(q.end.gpr[GPR_V0].u64[0] == 0u);
        }
    }
    for (u32 seed = 1; seed <= 300; ++seed) {
        // sub_1ADEC0(task; $f12 speed): when idle, the displacement = normalize(model +32) * speed, state 0
        clear_world(m);
        put32(m, kTask + 60, kWork);
        const u32 state = chance(rng, 75) ? 1u : rng() % 3;
        put32(m, kWork + 0, state);
        put32(m, kWork + 16, kModel);
        put32(m, kWork + 40, rng());
        put_matrix(m, kModel, rng);
        const float at[3] = {getf(m, kModel + 32), getf(m, kModel + 36), getf(m, kModel + 40)};
        const u32 dist0 = get32(m, kWork + 40);
        const hgp::Run r = hgp::pair(m, rg::fn_sub_1ADEC0_001adec0, rg::fn_sub_1ADEC0_001adec0__recomp, {kTask, 0, 0, 0}, seed,
                                     "sub_1ADEC0");
        ++pairs;
        if (r.stopped) continue;
        const float speed = bits_f(r.end.fpr[12]);
        if (state != 1) {
            CHECK(get32(m, kWork + 0) == state);
            continue;
        }
        ++forward;
        CHECK(get32(m, kWork + 0) == 0u);
        const float len = std::sqrt(at[0] * at[0] + at[1] * at[1] + at[2] * at[2]);
        for (int k = 0; k < 3; ++k)
            CHECK(std::fabs(getf(m, kWork + 20 + 4 * k) - at[k] / len * speed) <= 1e-3f * (1.0f + std::fabs(speed)));
        if (speed >= 0.0f && speed < 2147483600.0f) CHECK(get32(m, kWork + 40) == dist0 + static_cast<u32>(static_cast<s32>(speed)));
    }
    MESSAGE("mover / forward: " << pairs << " pairs, " << queued << " queued, " << popped << " popped, " << forward << " forward moves");
    CHECK(queued > 50);
}

TEST_CASE("game(field3_collision): the climb route's Tartarus floor (snapshot climb_ref_17000)") {
    const std::vector<u8> snap = read_snapshot("climb_ref_17000");
    if (snap.empty()) {
        MESSAGE("SKIP: no snapshot climb_ref_17000");
        return;
    }
    auto mm = std::make_unique<Machine>();
    if (const char* err = mm->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    Machine& m = *mm;
    copy_from_snapshot(m, snap, 0, EEMemory::kMainRamSize);
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3C006};
    int pairs = 0, units = 0;
    for (u32 u = 0; u < 28; ++u) {
        const u32 unit = (u < 4) ? 0x8717A0u + 448u * u : 0x86EDA0u + 448u * (u - 4);
        const u32 res = get32(m, unit + 84);
        if (get32(m, unit + 72) == 0 || res == 0) continue;
        const u32 task = get32(m, res + 480);  // the resource's collision controller (K_FldFrame_HandleCollis)
        if (task == 0 || get32(m, task + 60) == 0) continue;
        ++units;
        const u32 work = get32(m, task + 60);
        const u16 id = get16(m, res + 0);
        // K_FldFrame_CreateCtlTask(0, the unit's resource id): the same model and unit as the live controller
        const SiPair c = run_pair_si(m, rg::fn_K_FldFrame_CreateCtlTask_001ad660, rg::fn_K_FldFrame_CreateCtlTask_001ad660__recomp,
                                     {0, id, rng(), rng()}, rng(), "K_FldFrame_CreateCtlTask (climb)", hw, controller_world({}));
        ++pairs;
        const u32 nw = static_cast<u32>(c.recomp->si.log[0].v0);
        CHECK(get32(m, nw + 16) == get32(m, res + 296));
        if ((id >> 10) == 1) {
            CHECK(get32(m, nw + 12) == unit);
            CHECK(get16(m, nw + 10) == get16(m, unit + 424));
        }
        // the live controller: idle update, then a pending move (the real floor; the RW walks recorded)
        run_pair_si(m, rg::fn_K_FldFrame_UpdateCtlTask_001ad2f0, rg::fn_K_FldFrame_UpdateCtlTask_001ad2f0__recomp,
                    {task, rng(), rng(), rng()}, rng(), "K_FldFrame_UpdateCtlTask (climb, as found)", hw, controller_world({}));
        ++pairs;
        const u32 flags = get32(m, work + 4);
        put32(m, work + 4, flags & ~0x08000000u);
        put32(m, work + 0, 0);
        putf(m, work + 20, frand(rng, -30.0f, 30.0f));
        putf(m, work + 24, 0.0f);
        putf(m, work + 28, frand(rng, -30.0f, 30.0f));
        run_pair_si(m, rg::fn_K_FldFrame_UpdateCtlTask_001ad2f0, rg::fn_K_FldFrame_UpdateCtlTask_001ad2f0__recomp,
                    {task, rng(), rng(), rng()}, rng(), "K_FldFrame_UpdateCtlTask (climb, a move)", hw, controller_world({}));
        ++pairs;
        CHECK(get32(m, work + 0) == 1u);
        const u32 model = get32(m, work + 16);
        if (model) {
            CHECK(static_cast<s32>(get32(m, work + 44)) == grid_cell(getf(m, model + 48)));
            CHECK(static_cast<s32>(get32(m, work + 48)) == grid_cell(getf(m, model + 56)));
            // the ground ray under the unit (the floor's world / block clump; the RW walks recorded)
            const u32 line = kArena + 0x100u, out = kArena + 0x140u;
            for (int k = 0; k < 3; ++k) putf(m, line + 4 * k, getf(m, model + 48 + 4 * k));
            for (int k = 0; k < 3; ++k) putf(m, line + 12 + 4 * k, getf(m, model + 48 + 4 * k));
            putf(m, line + 4, getf(m, model + 52) + 600.0f);
            putf(m, line + 16, getf(m, model + 52) - 1000.0f);
            run_pair_si(m, rg::fn_sub_1ACC30_001acc30, rg::fn_sub_1ACC30_001acc30__recomp, {line, out, rng(), rng()}, rng(),
                        "sub_1ACC30 (climb)", hw, controller_world({}));
            ++pairs;
            run_pair_si(m, rg::fn_sub_1AE0D0_001ae0d0, rg::fn_sub_1AE0D0_001ae0d0__recomp, {task, rng(), rng(), rng()}, rng(),
                        "sub_1AE0D0 (climb)", hw, controller_world({}));
            ++pairs;
        }
    }
    MESSAGE("climb_ref_17000: " << units << " units with a controller, " << pairs << " pairs");
}

}  // namespace p3fes::game_test

#else

TEST_CASE("game(field3_collision): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
