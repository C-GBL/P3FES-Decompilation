// Pair tests for slice field3, part camera (game/src/field/field3_camera.cpp): the field camera controller, its
// rotation tasks, save / restore, the per-field camera set-up, the opmap loader and the shadow encounter picker.
//
// 1. Every body against its recompiled body on random worlds (tests/game/handgen_pairs.h: the whole register file and
//    cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus).
// 2. Real structures: the Tartarus replay snapshot climb_ref_17000 (field 51/4, the camera controller live at sField+4
//    with its pivot frame, target, controller and the ENCOUNT tables), run on the stand-in world (tests/game/
//    stand_ins.h: the heap behind RwCalloc / RwFree / H_Malloc, sprintf, the H_Cdvd layer; recorders for the RW frame
//    calls, the camera aim / field-of-view calls, the debug-draw tasks, fabs and the double compare sub_45EC00, which
//    this build does not emit) so every path runs to its end; each pair compares the whole RAM (write-tracked), every
//    GPR in 128 bits, HI/LO, the register file and cycles at every check point, the dead stack and the stand-ins' call
//    logs. Documented rules (field3_camera.cpp's comments) are checked on the recompiled run's output.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field3_camera.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
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
#define F3CAM_DECL(name, addr) void fn_##name##_##addr(EEContext&); void fn_##name##_##addr##__recomp(EEContext&);
P3FES_FIELD3_CAMERA_BODIES(F3CAM_DECL)
#undef F3CAM_DECL
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
#define F3CAM_CASE(name, addr) {#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp},
    P3FES_FIELD3_CAMERA_BODIES(F3CAM_CASE)
#undef F3CAM_CASE
};

// The random world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(field3_camera): every body equals its recompiled body on random worlds") {
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
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

namespace p3fes::game_test {
namespace {

// --- guest addresses / layouts (field3_camera.cpp) -------------------------------------------------------------------
constexpr u32 kSFieldCamera = 0x869F64u;  // sField+4: the camera controller task
constexpr u32 kHeroUnit = 0x8717E8u;      // gFldUnitsPc[0] +72
constexpr u32 kGpPack = kGp - 0x4B94u;    // the resident field pack word (sub_1B0910)
constexpr u32 kGpScene = kGp - 22448u;    // -> the scene record
constexpr u32 kGpOpmap = kGp - 19008u;
constexpr u32 kGpEncGroups = kGp - 18500u, kGpEncFloorRows = kGp - 18496u, kGpEncFieldRows = kGp - 18492u;

// Fakes in snapshot runs live at the top of the stand-in heap arena (zero in every snapshot, compared and restored by
// run_pair_si; the stand-in heap allocates from its bottom).
constexpr u32 kFake = kStandInHeap + kStandInHeapSize - 0x4000u;
constexpr u32 kFakeMarkTask = kFake + 0x400; // what sub_1A46F0 returns (only on rail fields; none in these worlds)
constexpr u32 kFakeTask = kFake + 0x600;     // a hand-built task (rotation update)
constexpr u32 kFakeWork = kFake + 0x700;
constexpr u32 kFakeOut = kFake + 0x800;      // 16-aligned out buffers
constexpr u32 kFakeNode = kFake + 0x1000;    // a hand-built H_Cdvd request node (868 bytes)
constexpr u32 kFakeCmr = kFake + 0x1400;     // its .CMR record (104 bytes)

// RW / camera callees this build does not emit
constexpr u32 kMainCamera = 0x7CE0C0u;  // g_kwlnMainCamera (sub_198590 returns it)
constexpr u32 kFrameMatrix = 16;        // RwFrame +16: the modelling matrix (right, up, at, pos rows of 16 bytes)
constexpr u32 kCamAim = 0x1A1210u, kCamSetFov = 0x1A4580u, kCamGetFov = 0x1A4600u;
constexpr u32 kMarkCreate = 0x1A46F0u, kCylinderCreate = 0x1A4860u;
constexpr u32 kRwFree = 0x104280u;

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
void put32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void put16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void putf(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
u64 sx32(u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }

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
const std::vector<u8>& climb() {
    static const std::vector<u8> s = read_snapshot("climb_ref_17000");
    return s;
}
#define NEED_CLIMB()                                                        \
    Machine* mp = machine();                                                \
    if (!mp) {                                                              \
        MESSAGE("SKIP: no ELF at " << elf_path());                          \
        return;                                                             \
    }                                                                       \
    Machine& m = *mp;                                                       \
    if (climb().empty()) {                                                  \
        MESSAGE("SKIP: extracted/_ours/climb_ref_17000/eeMemory.bin not found"); \
        return;                                                             \
    }
void load_climb(Machine& m) {
    std::memcpy(m.at(0), climb().data(), climb().size());
    write_rw_slots(m);
}

HwCheck full_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// The stand-in world of these tests: install_standard plus the callees above. The RW frame create / destroy / reset /
// add / remove / rotate / translate (sub_4CAF10, sub_4CAF80, sub_4CB930, sub_4CB420, sub_4CB590, sub_4CB890,
// sub_4CB750), the rail start sub_48D270, fabs and the double compare sub_45EC00 are replaced and run for real: their
// recorders here were never served, and since the hooked forwarders (2026-10-29) they would be, so they are gone (the
// pairs run as they always did).
WorldSetup cam_world() {
    return [](StandInWorld& w) {
        install_standard(w);
        // H_Cdvd_FileExists(path): 1 when the fake file layer would find the file under extracted/
        StandInWorld* wp = &w;
        w.si.install(kHCdvdFileExistsFn, "H_Cdvd_FileExists", [wp](EEContext& ctx, StandIns&, StandInCall& c) {
            std::string path;
            for (u32 a = static_cast<u32>(c.args[0]); path.size() < 255; ++a) {
                const char ch = static_cast<char>(ctx.memory->read<u8>(a));
                if (ch == 0) break;
                path += ch;
            }
            c.text = path;
            c.v0 = wp->cd.host_path(path).empty() ? 0u : 1u;
        });
        w.si.install_recorder(kCamAim, "sub_1A1210");
        w.si.install_recorder(kCamSetFov, "sub_1A4580");
        w.si.install_recorder(kCamGetFov, "sub_1A4600");
        w.si.install_recorder(kMarkCreate, "sub_1A46F0", kFakeMarkTask);
        w.si.install_recorder(kCylinderCreate, "sub_1A4860");
    };
}

}  // namespace

// The camera controller's update on the live controller of climb_ref_17000, with the mode, state, flags, offset, dead
// zone and the pivot's position varied. Half of the runs clear the target controller's model (+16), so the target is
// (0, 0, 0) and the dead-zone rules can be checked exactly: the pivot moves horizontally by (d - radius) along the
// horizontal direction only when d > radius, vertically by sign(dy) (|dy| - height / 2) only when |dy| > height / 2;
// mode 2 re-aims after a move; the debug cylinder (the task's child) gets flag bit 31, the pivot, radius and height.
TEST_CASE("game(field3_camera): the controller update on the climb snapshot (dead zone, modes)") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0001u};
    int pairs = 0, hmoves = 0, vmoves = 0, aims = 0, checked = 0;
    for (int i = 0; i < 160; ++i) {
        load_climb(m);
        const u32 task = get32(m, kSFieldCamera);
        REQUIRE(task != 0);
        const u32 work = get32(m, task + 60);
        const u32 pivot = get32(m, work + 12);
        const u32 res = get32(m, work + 204);
        REQUIRE(res != 0);
        static const u32 kModes[] = {0, 0, 2, 2, 5, 1, 3, 4, 7};
        const u32 mode = kModes[rng() % 9];
        const u32 state = chance(rng, 90) ? 0u : 1u + rng() % 3;
        put32(m, work + 0, state);
        put32(m, work + 8, mode);
        put32(m, work + 4, chance(rng, 50) ? 0x80000000u : 0u);
        const float off[3] = {frand(rng, -100, 100), frand(rng, 0, 150), frand(rng, -100, 100)};
        for (int k = 0; k < 3; ++k) putf(m, work + 20 + 4 * k, off[k]);
        const float radius = frand(rng, 0, 400), height = frand(rng, 0, 400);
        putf(m, work + 32, radius);
        putf(m, work + 36, height);
        const bool zero_target = chance(rng, 50);
        if (zero_target) put32(m, get32(m, get32(m, res + 480) + 60) + 16, 0);
        float p[3];
        for (int k = 0; k < 3; ++k) {
            p[k] = zero_target ? off[k] + frand(rng, -600, 600) : getf(m, pivot + 64 + 4 * k) + frand(rng, -600, 600);
            putf(m, pivot + 64 + 4 * k, p[k]);
        }
        const SiPair r = run_pair_si(m, rg::fn_K_FldCamera_UpdateFieldCameraControlerTask_001d5220,
                                     rg::fn_K_FldCamera_UpdateFieldCameraControlerTask_001d5220__recomp, {task, 0, 0, 0}, rng(),
                                     "K_FldCamera_UpdateFieldCameraControlerTask climb", hw, cam_world());
        ++pairs;
        CHECK(r.hw.recomp.base.v0 == 0);
        const StandIns& si = r.recomp->si;
        // The pivot frame's move: the real RwFrameTranslate (sub_4CB750, emitted in the test library since the models /
        // render_game2 slices) adds each move to the modelling matrix's position row (frame +64..).
        float q[3], d[3];
        for (int k = 0; k < 3; ++k) {
            q[k] = getf(m, pivot + 64 + 4 * k);
            d[k] = q[k] - p[k];
        }
        const bool moved_h = d[0] != 0.0f || d[2] != 0.0f, moved_v = d[1] != 0.0f;
        if (state != 0) {
            CHECK(!moved_h);
            CHECK(!moved_v);
            continue;
        }
        // the debug cylinder: shown by flag bit 31, at the pivot (after the moves), the zone's radius and height
        const u32 cyl = get32(m, get32(m, task + 80) + 60);
        CHECK(get32(m, cyl + 0) == (get32(m, work + 4) >> 31));
        for (int k = 0; k < 3; ++k) CHECK(getf(m, cyl + 4 + 4 * k) == q[k]);
        CHECK(getf(m, cyl + 16) == radius);
        CHECK(getf(m, cyl + 20) == height);
        const bool follow = mode == 0 || mode == 2 || mode == 5;
        if (!follow) {
            CHECK(!moved_h);
            CHECK(!moved_v);
            continue;
        }
        const int h = moved_h ? 1 : 0, v = moved_v ? 1 : 0;
        if (zero_target) {
            const float dx = off[0] - p[0], dz = off[2] - p[2], dy = off[1] - p[1];
            const float dist = std::sqrt(dx * dx + dz * dz);
            if (std::fabs(dist - radius) > 0.5f) CHECK(h == (dist > radius ? 1 : 0));
            if (std::fabs(std::fabs(dy) - height / 2) > 0.5f) CHECK(v == (std::fabs(dy) > height / 2 ? 1 : 0));
            if (h) {  // by (d - radius) along the horizontal direction
                CHECK(std::fabs(std::sqrt(d[0] * d[0] + d[2] * d[2]) - (dist - radius)) < 1e-2f * (1.0f + dist));
                CHECK(d[0] * dx >= 0.0f);
                CHECK(d[2] * dz >= 0.0f);
            }
            if (v) {  // by sign(dy) (|dy| - height / 2)
                CHECK(std::fabs(std::fabs(d[1]) - (std::fabs(dy) - height / 2)) < 1e-2f * (1.0f + std::fabs(dy)));
                CHECK(d[1] * dy >= 0.0f);
            }
            ++checked;
        }
        CHECK(si.calls_to(kCamAim) == (mode == 2 && (h + v) > 0 ? 1u : 0u));
        hmoves += h;
        vmoves += v;
        aims += static_cast<int>(si.calls_to(kCamAim));
    }
    MESSAGE("update: " << pairs << " pairs, " << checked << " with exact zone rules, " << hmoves << " horizontal / " << vmoves
                       << " vertical moves, " << aims << " re-aims");
    CHECK(hmoves > 20);
    CHECK(vmoves > 20);
    CHECK(aims > 5);
}

// Create (on the snapshot's dungeon task as parent) and destroy (the live controller): the work from RwCalloc, the
// pivot from the frame-create call (or the task destroyed again when there is none), the pivot linked between the
// main camera frame's parent and the frame; the destroy unlinks, destroys the pivot, re-links and frees the work.
TEST_CASE("game(field3_camera): create and destroy the controller on the climb snapshot") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0002u};
    // The RW frame functions (RwFrameCreate / Destroy / AddChild / RemoveChild) are emitted in the test library since the
    // models / render_game2 slices, so they run for real (the frame from the stand-in heap's free list) and the
    // hierarchy is checked in guest memory: RwFrame +4 parent, +152 first child. (The "no frame" path -- RwFrameCreate
    // returning 0 -- cannot be forced any more; the random-world pass still reaches it.)
    constexpr u32 kFrameChild = 152;
    int made = 0;
    for (int i = 0; i < 16; ++i) {
        load_climb(m);
        const u32 old_task = get32(m, kSFieldCamera);
        const u32 old_pivot = get32(m, get32(m, old_task + 60) + 12);
        const u32 main_frame = get32(m, old_pivot + kFrameChild);  // in mode 0 the main camera frame hangs under the pivot
        const u32 parent = get32(m, old_task + 76);
        const SiPair r = run_pair_si(m, rg::fn_K_FldCamera_CreateFieldCameraControlerTask_001d5a90,
                                     rg::fn_K_FldCamera_CreateFieldCameraControlerTask_001d5a90__recomp, {parent, 0, 0, 0}, rng(),
                                     "K_FldCamera_CreateFieldCameraControlerTask climb", hw, cam_world());
        const StandIns& si = r.recomp->si;
        const u32 task = static_cast<u32>(r.hw.recomp.base.v0);
        REQUIRE(task != 0);
        CHECK(get32(m, task + 52) == 0x1D5220u);  // update
        CHECK(get32(m, task + 56) == 0x1D59E0u);  // destroy
        const u32 work = get32(m, task + 60);
        CHECK(r.recomp->heap.size_of(work) == 208);
        const u32 pivot = get32(m, work + 12);
        REQUIRE(pivot != 0);
        // +16 = the main camera frame's parent at creation (the old controller's pivot); parent -> pivot -> main frame
        CHECK(get32(m, work + 16) == old_pivot);
        CHECK(get32(m, pivot + 4) == old_pivot);
        CHECK(get32(m, main_frame + 4) == pivot);
        CHECK(get32(m, pivot + kFrameChild) == main_frame);
        // the new pivot's modelling matrix was reset to identity (sub_4CB930, hand-written since render_rw4: it runs for
        // real, so the result is checked in guest memory instead of a recorder's call count)
        for (u32 row = 0; row < 3; ++row)
            for (u32 col = 0; col < 3; ++col) CHECK(getf(m, pivot + kFrameMatrix + 16 * row + 4 * col) == (row == col ? 1.0f : 0.0f));
        CHECK(si.calls_to(kCylinderCreate) == 1);
        ++made;
    }
    for (int i = 0; i < 8; ++i) {
        load_climb(m);
        const u32 task = get32(m, kSFieldCamera);
        const u32 work = get32(m, task + 60);
        const u32 pivot = get32(m, work + 12), saved_parent = get32(m, work + 16);
        const u32 main_frame = get32(m, pivot + kFrameChild);
        const SiPair r = run_pair_si(m, rg::fn_sub_1D59E0_001d59e0, rg::fn_sub_1D59E0_001d59e0__recomp, {task, 0, 0, 0}, rng(),
                                     "sub_1D59E0 climb", hw, cam_world());
        const StandIns& si = r.recomp->si;
        // the main camera frame back under the saved parent, the work freed (RwFree through its slot)
        CHECK(get32(m, main_frame + 4) == saved_parent);
        CHECK(si.calls_to(kRwFree) == 1);
        for (const StandInCall& c : si.log)
            if (c.va == kRwFree) CHECK(c.args[0] == sx32(work));
    }
    MESSAGE("create: " << made << " made");
    CHECK(made == 16);
}

// The mode switch on the climb field (no rail: the samples are skipped) with a hand-built rail task / debug points left
// to be destroyed: +8 = mode; leaving the rail destroys what is there (kwlnTaskDestroyWithHierarchy, hand-written).
TEST_CASE("game(field3_camera): the mode switch and the rotation-about-y helper on the climb snapshot") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0003u};
    int pairs = 0, turned = 0;
    for (int i = 0; i < 40; ++i) {
        load_climb(m);
        const u32 task = get32(m, kSFieldCamera);
        const u32 work = get32(m, task + 60);
        const u32 mode = rng() % 7;
        run_pair_si(m, rg::fn_sub_1D5C10_001d5c10, rg::fn_sub_1D5C10_001d5c10__recomp, {task, mode, 0, 0}, rng(), "sub_1D5C10 climb",
                    hw, cam_world());
        CHECK(get32(m, work + 8) == mode);
        ++pairs;
        // sub_1D5E30: turns (sub_4CB890 about (0, 1, 0), combine 2) and re-aims only in mode 0
        load_climb(m);
        const u32 m2 = chance(rng, 60) ? 0u : 1u + rng() % 5;
        put32(m, work + 8, m2);
        // the main camera's frame (g_kwlnMainCamera +4) and its modelling matrix before the call
        const u32 cam_frame = get32(m, get32(m, kMainCamera) + 4);
        float before[16];
        for (u32 k = 0; k < 16; ++k) before[k] = getf(m, cam_frame + kFrameMatrix + 4 * k);
        HwCheck hw2 = hw;
        const SiPair r = run_pair_si(m, rg::fn_sub_1D5E30_001d5e30, rg::fn_sub_1D5E30_001d5e30__recomp, {task, 0, 0, 0}, rng(),
                                     "sub_1D5E30 climb", hw2, cam_world());
        const StandIns& si = r.recomp->si;
        CHECK(si.calls_to(kCamAim) == (m2 == 0 ? 1u : 0u));
        // the turn (sub_4CB890 about (0, 1, 0), post-concatenated; hand-written since render_rw4, so checked in guest
        // memory): mode 0 turns the frame about the world y axis -- every row keeps its y component -- other modes leave
        // the matrix alone
        bool changed = false;
        for (u32 k = 0; k < 16; ++k) {
            const float now = getf(m, cam_frame + kFrameMatrix + 4 * k);
            if (k % 4 == 3) continue;  // the rows' padding words
            if (k % 4 == 1) CHECK(now == doctest::Approx(before[k]).epsilon(1e-4));  // y components
            changed |= now != before[k];
        }
        if (m2 != 0) CHECK_FALSE(changed);
        else ++turned;  // mode 0 took the turn path; the angle is whatever $f12 holds (often 0 here), so the matrix may stay put
        ++pairs;
    }
    MESSAGE("mode / turn: " << pairs << " pairs, " << turned << " turns");
    CHECK(turned > 10);
}

// The rotation creators on the climb field (the hero unit is live): the work's frames and the chosen turn, which is
// the shorter of the two ways round (under this test's "less than" stand-in for sub_45EC00), and for two calls whose
// angles differ by d the turns differ by d modulo 360 (the camera's and the hero's yaws cancel out). (The turn is not
// always within 180: the target yaw is only brought down to <= 360, never up.)
TEST_CASE("game(field3_camera): the rotation task creators on the climb snapshot") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0004u};
    int pairs = 0, rel = 0;
    for (int i = 0; i < 40; ++i) {
        const bool to_angle = i % 2 == 1;
        const Fn hand = to_angle ? rg::fn_sub_1D6630_001d6630 : rg::fn_sub_1D6270_001d6270;
        const Fn recomp = to_angle ? rg::fn_sub_1D6630_001d6630__recomp : rg::fn_sub_1D6270_001d6270__recomp;
        const u32 frames = 1 + rng() % 60;
        const s32 a0 = to_angle ? static_cast<s32>(rng() % 1441) - 720 : (chance(rng, 30) ? -1 : static_cast<s32>(rng() % 721) - 360);
        const s32 d = static_cast<s32>(rng() % 200) - 100;
        float turns[2] = {0, 0};
        for (int k = 0; k < 2; ++k) {
            load_climb(m);
            REQUIRE(get32(m, kHeroUnit) != 0);
            const s32 ang = k == 0 ? a0 : a0 + d;
            if (k == 1 && a0 == -1) break;
            const u32 parent = get32(m, kSFieldCamera);
            const SiPair r = run_pair_si(m, hand, recomp, {parent, frames, sx32(static_cast<u32>(ang)), 0}, rng(),
                                         to_angle ? "sub_1D6630 climb" : "sub_1D6270 climb", hw, cam_world());
            ++pairs;
            const u32 task = static_cast<u32>(r.hw.recomp.base.v0);
            REQUIRE(task != 0);
            CHECK(get32(m, task + 52) == 0x1D5F90u);
            CHECK(get32(m, task + 56) == 0x1D6240u);
            const u32 work = get32(m, task + 60);
            CHECK(get32(m, work + 0) == 0);
            CHECK(get32(m, work + 4) == frames);
            CHECK(get32(m, work + 8) == 0);
            turns[k] = getf(m, work + 16);
            CHECK(std::fabs(turns[k]) <= 1080.0f);
        }
        if (a0 != -1) {
            const double diff = std::fmod(static_cast<double>(turns[1]) - turns[0] - d + 3600.0, 360.0);
            CHECK((diff < 0.01 || diff > 359.99));
            ++rel;
        }
    }
    // no hero unit: no task
    load_climb(m);
    put32(m, kHeroUnit, 0);
    const SiPair r = run_pair_si(m, rg::fn_sub_1D6270_001d6270, rg::fn_sub_1D6270_001d6270__recomp, {get32(m, kSFieldCamera), 10, sx32(~0u), 0},
                                 1, "sub_1D6270 no hero", hw, cam_world());
    CHECK(r.hw.recomp.base.v0 == 0);
    MESSAGE("rotation creators: " << pairs << " pairs, " << rel << " relative checks");
}

// The rotation update on a hand-built task (the camera controller of the snapshot decides whether the camera turns):
// state 2 -> -1; otherwise frame < frames -> frame + 1 and the last ease value = sinf(pi/2 frame / frames); at the end
// the state moves on.
TEST_CASE("game(field3_camera): the rotation update and its destroy") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0005u};
    int pairs = 0, eased = 0, ended = 0;
    for (int i = 0; i < 120; ++i) {
        load_climb(m);
        const u32 cam_work = get32(m, get32(m, kSFieldCamera) + 60);
        put32(m, cam_work + 8, chance(rng, 70) ? 0u : 2u);
        const u32 state = rng() % 4;
        const u32 frames = rng() % 30, frame = rng() % (frames + 3);
        put32(m, kFakeTask + 60, kFakeWork);
        put32(m, kFakeWork + 0, state);
        put32(m, kFakeWork + 4, frames);
        put32(m, kFakeWork + 8, frame);
        putf(m, kFakeWork + 12, frand(rng, -30, 30));
        putf(m, kFakeWork + 16, frand(rng, -180, 180));
        putf(m, kFakeWork + 20, frand(rng, 0, 1));
        const SiPair r = run_pair_si(m, rg::fn_sub_1D5F90_001d5f90, rg::fn_sub_1D5F90_001d5f90__recomp, {kFakeTask, 0, 0, 0}, rng(),
                                     "sub_1D5F90", hw, cam_world());
        ++pairs;
        if (state == 2) {
            CHECK(r.hw.recomp.base.v0 == ~0ull);
            continue;
        }
        CHECK(r.hw.recomp.base.v0 == 0);
        if (state != 0 && state != 1) {
            CHECK(get32(m, kFakeWork + 0) == state);
            continue;
        }
        if (static_cast<s32>(frame) < static_cast<s32>(frames)) {
            CHECK(get32(m, kFakeWork + 8) == frame + 1);
            const float want = std::sin(1.5707963f * static_cast<float>(frame + 1) / static_cast<float>(frames));
            CHECK(std::fabs(getf(m, kFakeWork + 20) - want) < 1e-5f);
            CHECK(get32(m, kFakeWork + 0) == 1);
            ++eased;
        } else {
            CHECK(get32(m, kFakeWork + 0) == 2);
            ++ended;
        }
    }
    // the destroy frees the work
    load_climb(m);
    put32(m, kFakeTask + 60, kFakeWork);
    const SiPair r = run_pair_si(m, rg::fn_sub_1D6240_001d6240, rg::fn_sub_1D6240_001d6240__recomp, {kFakeTask, 0, 0, 0}, 7, "sub_1D6240",
                                 hw, cam_world());
    CHECK(r.recomp->si.calls_to(kRwFree) == 1);
    MESSAGE("rotation update: " << pairs << " pairs, " << eased << " eased frames, " << ended << " ends");
    CHECK(eased > 30);
    CHECK(ended > 10);
}

// Save and restore around a battle: the 96-byte record holds the mode (u16 +68), offset, radius, height of the work;
// restoring a record into a changed work brings those back (and the mode goes through sub_1D5C10).
TEST_CASE("game(field3_camera): camera save / restore on the climb snapshot") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0006u};
    int pairs = 0;
    for (int i = 0; i < 24; ++i) {
        load_climb(m);
        const u32 task = get32(m, kSFieldCamera);
        const u32 work = get32(m, task + 60);
        const u32 mode = i % 3 == 0 ? 2u : (i % 3 == 1 ? 5u : 0u);
        put32(m, work + 8, mode);
        for (u32 k = 20; k <= 36; k += 4) putf(m, work + k, frand(rng, 0, 300));
        run_pair_si(m, rg::fn_sub_1D68E0_001d68e0, rg::fn_sub_1D68E0_001d68e0__recomp, {kFakeOut, task, 0, 0}, rng(), "sub_1D68E0 climb",
                    hw, cam_world());
        ++pairs;
        CHECK(get16(m, kFakeOut + 68) == mode);
        for (u32 k = 0; k < 5; ++k) CHECK(get32(m, kFakeOut + 72 + 4 * k) == get32(m, work + 20 + 4 * k));
        // change the work, restore the record
        std::vector<u8> rec(m.at(kFakeOut), m.at(kFakeOut) + 96);
        put32(m, work + 8, 1);
        for (u32 k = 20; k <= 36; k += 4) putf(m, work + k, -1.0f);
        const SiPair r = run_pair_si(m, rg::fn_sub_1D69E0_001d69e0, rg::fn_sub_1D69E0_001d69e0__recomp, {task, kFakeOut, 0, 0}, rng(),
                                     "sub_1D69E0 climb", hw, cam_world());
        ++pairs;
        CHECK(get32(m, work + 8) == mode);
        for (u32 k = 0; k < 5; ++k) {
            u32 v;
            std::memcpy(&v, rec.data() + 72 + 4 * k, 4);
            CHECK(get32(m, work + 20 + 4 * k) == v);
        }
        CHECK(r.recomp->si.calls_to(kCamSetFov) == 1);
        CHECK(r.recomp->si.calls_to(kCamAim) == (mode == 5 ? 0u : 1u));  // mode 2 directly, mode 0 through sub_1D5E30
    }
    MESSAGE("save / restore: " << pairs << " pairs");
}

// The .CMR set-up: the request (no scene -> 0; a resident pack -> 1; field/env/f051_004.CMR is not on the disc -> 0
// after sprintf / FileExists), and the apply / copy-out of a loaded record (a hand-built node in state 4): the record's
// fields reach the controller (radius 0.0 -> 50.0 outside random floors, written back) or the out pointers.
TEST_CASE("game(field3_camera): the .CMR camera request and apply") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0007u};
    for (int v = 0; v < 3; ++v) {
        load_climb(m);
        if (v == 0) put32(m, get32(m, kGpScene), ~0u);
        if (v == 1) put32(m, kGpPack, 0x01F00000u);
        if (v == 2) put32(m, kGpPack, 0);
        const SiPair r = run_pair_si(m, rg::fn_sub_1D6B10_001d6b10, rg::fn_sub_1D6B10_001d6b10__recomp, {0, 0, 0, 0}, rng(), "sub_1D6B10",
                                     hw, cam_world());
        CHECK(r.hw.recomp.base.v0 == (v == 1 ? 1u : 0u));
        if (v == 2) {
            bool printed = false;
            for (const StandInCall& c : r.recomp->si.log)
                if (c.va == kSprintf) printed = c.text == "field/env/f051_004.CMR";
            CHECK(printed);
        }
    }
    int applied = 0, copied = 0;
    for (int i = 0; i < 30; ++i) {
        load_climb(m);
        put32(m, kGpPack, 0);
        const bool loaded = i % 5 != 4;
        std::memset(m.at(kFakeNode), 0, 868);
        put32(m, kFakeNode + 12, loaded ? 4u : 0u);
        put32(m, kFakeNode + 272, kFakeCmr);
        putf(m, kFakeCmr + 8, frand(rng, 0.3f, 1.2f));
        for (u32 k = 0; k < 16; ++k) putf(m, kFakeCmr + 16 + 4 * k, (k % 5 == 0) ? 1.0f : frand(rng, -0.1f, 0.1f));
        const u16 mode = static_cast<u16>(i % 3 == 0 ? 2 : (i % 3 == 1 ? 0 : 5));
        put16(m, kFakeCmr + 80, mode);
        for (u32 k = 0; k < 3; ++k) putf(m, kFakeCmr + 84 + 4 * k, frand(rng, -50, 120));
        const float radius = chance(rng, 40) ? 0.0f : frand(rng, 10, 200);
        putf(m, kFakeCmr + 96, radius);
        putf(m, kFakeCmr + 100, frand(rng, 0, 100));
        const bool copy_out = i % 2 == 1;
        HwCheck h = hw;
        u64 a1 = 0;
        if (copy_out) {
            a1 = kFakeOut;
            h.gpr_in = {{8, kFakeOut + 0x60}, {9, kFakeOut + 0x70}, {10, kFakeOut + 0x74}};
        }
        const SiPair r = run_pair_si(m, rg::fn_sub_1D6BC0_001d6bc0, rg::fn_sub_1D6BC0_001d6bc0__recomp,
                                     {kFakeNode, a1, kFakeOut + 0x40, kFakeOut + 0x44}, rng(), "sub_1D6BC0", h, [](StandInWorld& w) {
                                         cam_world()(w);
                                         w.si.install_recorder(kHCdvdDestroyFn, "H_Cdvd_Destroy", 1);
                                     });
        CHECK(r.hw.recomp.base.v0 == (loaded ? 1u : 0u));
        if (!loaded) continue;
        CHECK(r.recomp->si.calls_to(kHCdvdDestroyFn) == 1);
        const float want_r = radius == 0.0f ? 50.0f : radius;  // field 51/4 is not a random floor
        if (copy_out) {
            CHECK(std::memcmp(m.at(kFakeOut), m.at(kFakeCmr + 16), 64) == 0);
            CHECK(get32(m, kFakeOut + 0x40) == get32(m, kFakeCmr + 8));
            CHECK(get32(m, kFakeOut + 0x44) == mode);
            for (u32 k = 0; k < 3; ++k) CHECK(get32(m, kFakeOut + 0x60 + 4 * k) == get32(m, kFakeCmr + 84 + 4 * k));
            CHECK(getf(m, kFakeOut + 0x70) == radius);  // the copy-out takes the record as it is
            CHECK(get32(m, kFakeOut + 0x74) == get32(m, kFakeCmr + 100));
            ++copied;
        } else {
            const u32 work = get32(m, get32(m, kSFieldCamera) + 60);
            CHECK(get32(m, work + 8) == mode);
            for (u32 k = 0; k < 3; ++k) CHECK(get32(m, work + 20 + 4 * k) == get32(m, kFakeCmr + 84 + 4 * k));
            CHECK(getf(m, work + 32) == want_r);
            CHECK(getf(m, kFakeCmr + 96) == want_r);
            CHECK(get32(m, work + 36) == get32(m, kFakeCmr + 100));
            ++applied;
        }
    }
    // no request: 1; the scene camera resource (none in this field): runs to the end
    load_climb(m);
    CHECK(run_pair_si(m, rg::fn_sub_1D6BC0_001d6bc0, rg::fn_sub_1D6BC0_001d6bc0__recomp, {0, 0, 0, 0}, 3, "sub_1D6BC0 none", hw, cam_world())
              .hw.recomp.base.v0 == 1);
    load_climb(m);
    run_pair_si(m, rg::fn_sub_1D70A0_001d70a0, rg::fn_sub_1D70A0_001d70a0__recomp, {0, 0, 0, 0}, 4, "sub_1D70A0 climb", hw, cam_world());
    MESSAGE(".CMR: " << applied << " applied, " << copied << " copied out");
    CHECK(applied > 5);
    CHECK(copied > 5);
}

// The opmap table: field/table/opmap.bin through the fake file layer, copied into a fresh RwCalloc block at gp-19008.
TEST_CASE("game(field3_camera): the opmap table loader") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    load_climb(m);
    put32(m, kGpOpmap, 0);
    const SiPair r = run_pair_si(m, rg::fn_sub_1D7260_001d7260, rg::fn_sub_1D7260_001d7260__recomp, {0, 0, 0, 0}, 5, "sub_1D7260", hw,
                                 cam_world());
    const std::string path = extracted_root() + "/DATA/FIELD/TABLE/OPMAP.BIN";
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        MESSAGE("SKIP the content check: " << path << " not found");
        return;
    }
    const std::vector<char> file((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    const u32 block = get32(m, kGpOpmap);
    REQUIRE(block != 0);
    CHECK(r.recomp->heap.size_of(block) >= file.size());
    CHECK(std::memcmp(m.at(block), file.data(), file.size()) == 0);
    MESSAGE("opmap: " << file.size() << " bytes at " << hex64(block));
}

// The shadow encounter picker on the snapshot's ENCOUNT tables: the group from the floor row (Tartarus floors) or the
// field row (majors 31..39), the tier by the group's three weights (forced to 4 by floor kind 3), the id one of the
// tier's entries with a non-zero id; -1 for other fields or an all-zero tier.
TEST_CASE("game(field3_camera): the shadow encounter picker on the climb snapshot's ENCOUNT tables") {
    NEED_CLIMB();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3CA0008u};
    int picks = 0, nones = 0, pairs = 0;
    for (int i = 0; i < 200; ++i) {
        load_climb(m);
        u32 major, minor = 0;
        const u32 k = rng() % 6;
        if (k == 0) major = 21 + rng() % 7;
        else if (k == 1) major = 41 + rng() % 7;
        else if (k == 2) major = 51 + rng() % 8, minor = rng() % 8;
        else if (k == 3) major = 31 + rng() % 9, minor = 1 + rng() % 9;
        else if (k == 4) major = 21 + rng() % 7, minor = 1 + rng() % 3;  // a scripted floor of a random block: no group
        else major = rng() % 100, minor = rng() % 4;
        const u32 floor = rng() % 500;
        const SiPair r = run_pair_si(m, rg::fn_sub_1D7300_001d7300, rg::fn_sub_1D7300_001d7300__recomp, {major, minor, floor, 0}, rng(),
                                     "sub_1D7300 climb", hw, cam_world());
        ++pairs;
        const u64 v0 = r.hw.recomp.base.v0;
        // the host's reading of the group
        const bool tartarus = ((major >= 20 && major < 29) && minor == 0) || ((major >= 40 && major < 49) && minor == 0) ||
                              (major >= 51 && major < 59) || (major >= 71 && major < 79);
        const bool field = major >= 31 && major < 40;
        if (!tartarus && !field) {
            CHECK(v0 == ~0ull);
            ++nones;
            continue;
        }
        const u32 group = tartarus ? get16(m, get32(m, kGpEncFloorRows) + 10 * floor)
                                   : get16(m, get32(m, kGpEncFieldRows) + 200 * major + 10 * minor - 6210);
        const u32 rec = get32(m, kGpEncGroups) + 124 * group;
        if (v0 == ~0ull) {
            ++nones;
            continue;
        }
        const u32 tier = static_cast<u32>(v0 >> 16), id = static_cast<u32>(v0 & 0xFFFF);
        u32 lo = 0, hi = 20;
        if (tier == 2) lo = 20, hi = 25;
        if (tier == 4) lo = 25, hi = 30;
        CHECK((tier == 1 || tier == 2 || tier == 4));
        bool found = false;
        for (u32 e = lo; e < hi; ++e)
            if (get16(m, rec + 4 + 4 * e) == id && id != 0) found = true;
        CHECK(found);
        ++picks;
    }
    MESSAGE("encounter picker: " << pairs << " pairs, " << picks << " picks, " << nones << " none");
    CHECK(picks > 30);
}

}  // namespace p3fes::game_test

#else

TEST_CASE("game(field3_camera): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
