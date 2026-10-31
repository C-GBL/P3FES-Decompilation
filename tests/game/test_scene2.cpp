// Pair tests of slice scene2 (game/src/scene/scene2_{func,msg,fcl}.cpp; the records in game/include/p3fes/game/scene2.h):
// every hand body against its recompiled body on identical guest machines, compared by tests/game/handgen_pairs.h (the
// whole register file and cycles at every check point and at the return / stop, all 32 MiB of RAM -- the dead stack and
// the stand-in heap included --, the scratchpad, the BIOS window, the bus log) and, through stand-in worlds
// (tests/game/stand_ins.h: the heap behind the RW slots, printf / sprintf, the H_Cdvd layer, recorders for the callees
// this test library does not emit), the two call logs.
//   1. Random worlds: all 46 functions.
//   2. The live scenes of dorm_replay_4900 / b_5800 / climb_ref_17000 / fusion_vr_5000 / shop_ref_4100: every resource
//      of every type list through the SceneManager's per-resource update, the SceneManager task and draw, the active
//      camera (eye + placement), the effect-depth comparator on every pair of effects (antisymmetric, 0 on itself), the
//      NPC icon wrapper; the MsgAssist / fclBank tasks and their helpers on the live work blocks.
//   3. The per-resource update on made-up records (documented rules): the timed and the speed move, the rotation with
//      the shorter turn and the angle wrap, the scale tween, the type-7 fov tween (its +92 time-base quirk), the alpha
//      fade timer, the step count (flag 0x20 / bit 3), the bezier path move (request, length, point, heading).
//   4. The camera shake (off / expiring / one decaying axis, clamped), the camera eye without a target.
//   5. The message-window slot (open always creates a handle -- its reset makes the "already open" test dead --,
//      release, show, the update's states 2 / 3, clear), the message-handle table, nmListSort with a guest comparator.
//   6. fclBank (KILL / CLOSE / END / the panel pick), psStatus (fades, slide, the layout callback, the load states),
//      psModel (no model, the model request, the rgba fade), the psStatus layouts over every kind / page / row count.
// (frFontEx draw string sub_3B2CB0 is hand-written since finalA; test_field_hi stands it in as a stop.)
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function (random worlds), one function, a trace line per pair.
// Every random draw is a statement of its own (MSVC and clang-cl evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/scene.h"
#include "p3fes/game/scene2.h"

#include <array>
#include <cmath>
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
using namespace p3fes::game;

namespace p3fes::recomp_gen {
#define S2_FN(name, addr8)                     \
    void fn_##name##_##addr8(EEContext&);      \
    void fn_##name##_##addr8##__recomp(EEContext&);
S2_FN(sub_3B8540, 003b8540)
S2_FN(sub_3B88C0, 003b88c0)
S2_FN(sub_3B9610, 003b9610)
S2_FN(sub_3BB060, 003bb060)
S2_FN(sub_3BB620, 003bb620)
S2_FN(sub_3BB7A0, 003bb7a0)
S2_FN(sub_3BBB90, 003bbb90)
S2_FN(sub_3BBED0, 003bbed0)
S2_FN(sub_3BC220, 003bc220)
S2_FN(sub_3BC940, 003bc940)
S2_FN(sub_3BCCB0, 003bccb0)
S2_FN(sub_3BCD80, 003bcd80)
S2_FN(sub_3BCDA0, 003bcda0)
S2_FN(sub_3BCEB0, 003bceb0)
S2_FN(sub_3BD010, 003bd010)
S2_FN(sub_3BD230, 003bd230)
S2_FN(sub_3C4FC0, 003c4fc0)
S2_FN(sub_3C7990, 003c7990)
S2_FN(sub_3C7DD0, 003c7dd0)
S2_FN(sub_3C8550, 003c8550)
S2_FN(fclMisc_UpdateMsgAssistTask, 003c89a0)
S2_FN(sub_3C8B50, 003c8b50)
S2_FN(sub_3C8FA0, 003c8fa0)
S2_FN(sub_3C9000, 003c9000)
S2_FN(sub_3C91B0, 003c91b0)
S2_FN(sub_3C9240, 003c9240)
S2_FN(sub_3C9290, 003c9290)
S2_FN(sub_3C9390, 003c9390)
S2_FN(sub_3C9460, 003c9460)
S2_FN(sub_3C9FE0, 003c9fe0)
S2_FN(fclMisc_UpdatePsStatusTask, 003ca230)
S2_FN(sub_3CA6B0, 003ca6b0)
S2_FN(sub_3CA780, 003ca780)
S2_FN(sub_3CACC0, 003cacc0)
S2_FN(sub_3CB1F0, 003cb1f0)
S2_FN(sub_3CB960, 003cb960)
S2_FN(sub_3CBA50, 003cba50)
S2_FN(sub_3CCC40, 003ccc40)
S2_FN(sub_3CD0B0, 003cd0b0)
S2_FN(sub_3CD5A0, 003cd5a0)
S2_FN(fclMisc_UpdatePsModelDummyTask, 003cda00)
S2_FN(sub_3CE2A0, 003ce2a0)
S2_FN(sub_3CEA50, 003cea50)
S2_FN(fclMisc_CreatePsModelDummyTask, 003cf080)
S2_FN(sub_3CF6C0, 003cf6c0)
S2_FN(fclBank_UpdateTask, 003cfe50)
#undef S2_FN
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

#define S2_CASE(name, addr, addr8) {#name, addr, &recomp_gen::fn_##name##_##addr8, &recomp_gen::fn_##name##_##addr8##__recomp}
const Case kCases[] = {
    S2_CASE(sub_3B8540, 0x3B8540, 003b8540),
    S2_CASE(sub_3B88C0, 0x3B88C0, 003b88c0),
    S2_CASE(sub_3B9610, 0x3B9610, 003b9610),
    S2_CASE(sub_3BB060, 0x3BB060, 003bb060),
    S2_CASE(sub_3BB620, 0x3BB620, 003bb620),
    S2_CASE(sub_3BB7A0, 0x3BB7A0, 003bb7a0),
    S2_CASE(sub_3BBB90, 0x3BBB90, 003bbb90),
    S2_CASE(sub_3BBED0, 0x3BBED0, 003bbed0),
    S2_CASE(sub_3BC220, 0x3BC220, 003bc220),
    S2_CASE(sub_3BC940, 0x3BC940, 003bc940),
    S2_CASE(sub_3BCCB0, 0x3BCCB0, 003bccb0),
    S2_CASE(sub_3BCD80, 0x3BCD80, 003bcd80),
    S2_CASE(sub_3BCDA0, 0x3BCDA0, 003bcda0),
    S2_CASE(sub_3BCEB0, 0x3BCEB0, 003bceb0),
    S2_CASE(sub_3BD010, 0x3BD010, 003bd010),
    S2_CASE(sub_3BD230, 0x3BD230, 003bd230),
    S2_CASE(sub_3C4FC0, 0x3C4FC0, 003c4fc0),
    S2_CASE(sub_3C7990, 0x3C7990, 003c7990),
    S2_CASE(sub_3C7DD0, 0x3C7DD0, 003c7dd0),
    S2_CASE(sub_3C8550, 0x3C8550, 003c8550),
    S2_CASE(fclMisc_UpdateMsgAssistTask, 0x3C89A0, 003c89a0),
    S2_CASE(sub_3C8B50, 0x3C8B50, 003c8b50),
    S2_CASE(sub_3C8FA0, 0x3C8FA0, 003c8fa0),
    S2_CASE(sub_3C9000, 0x3C9000, 003c9000),
    S2_CASE(sub_3C91B0, 0x3C91B0, 003c91b0),
    S2_CASE(sub_3C9240, 0x3C9240, 003c9240),
    S2_CASE(sub_3C9290, 0x3C9290, 003c9290),
    S2_CASE(sub_3C9390, 0x3C9390, 003c9390),
    S2_CASE(sub_3C9460, 0x3C9460, 003c9460),
    S2_CASE(sub_3C9FE0, 0x3C9FE0, 003c9fe0),
    S2_CASE(fclMisc_UpdatePsStatusTask, 0x3CA230, 003ca230),
    S2_CASE(sub_3CA6B0, 0x3CA6B0, 003ca6b0),
    S2_CASE(sub_3CA780, 0x3CA780, 003ca780),
    S2_CASE(sub_3CACC0, 0x3CACC0, 003cacc0),
    S2_CASE(sub_3CB1F0, 0x3CB1F0, 003cb1f0),
    S2_CASE(sub_3CB960, 0x3CB960, 003cb960),
    S2_CASE(sub_3CBA50, 0x3CBA50, 003cba50),
    S2_CASE(sub_3CCC40, 0x3CCC40, 003ccc40),
    S2_CASE(sub_3CD0B0, 0x3CD0B0, 003cd0b0),
    S2_CASE(sub_3CD5A0, 0x3CD5A0, 003cd5a0),
    S2_CASE(fclMisc_UpdatePsModelDummyTask, 0x3CDA00, 003cda00),
    S2_CASE(sub_3CE2A0, 0x3CE2A0, 003ce2a0),
    S2_CASE(sub_3CEA50, 0x3CEA50, 003cea50),
    S2_CASE(fclMisc_CreatePsModelDummyTask, 0x3CF080, 003cf080),
    S2_CASE(sub_3CF6C0, 0x3CF6C0, 003cf6c0),
    S2_CASE(fclBank_UpdateTask, 0x3CFE50, 003cfe50),
};
#undef S2_CASE

constexpr u32 kWorld = 0x01810000u;  // the random worlds: 64 KiB of free RAM above the harness's arena
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;
constexpr u32 kOut = 0x01F40000u;     // free in every snapshot (above the stand-in heap) and in the ELF image
constexpr u32 kSceneSlot = 0x7CD540u; // gp-0x57B0: -> the scene record (MT_Scene)
constexpr u32 kAssistSlot = 0x7CE67Cu;
constexpr u32 kBankSlot = 0x7CE680u;
constexpr u32 kShakeOn = 0x7CE658u, kShakeFrames = 0x7CE65Cu, kShakeAmpX = 0x7CE660u, kShakeAmpZ = 0x7CE664u;
constexpr u32 kShakeRateX = 0x7CD560u, kShakeScale = 0x7CADA0u, kShakeOffset = 0x95AFF0u;
constexpr u32 kMsgHandles = 0x6A3E50u;
constexpr u32 kModelVa = kOut + 0x800;  // psModel: the model address the request stand-in hands out
constexpr u32 kStubCompare = 0x3CB050u;  // not emitted here: a guest-callable address for a custom comparator / callback
constexpr const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_vr_5000", "shop_ref_4100"};

// --- the pair runner (as test_scene.cpp) ----------------------------------------------------------------------------
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool persist = false;
    WorldSetup setup;
};
Tramp g_t;
int g_pairs = 0;
std::map<std::string, int> g_stops;

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.persist || !g_t.world[K]) {
        g_t.world[K] = std::make_unique<StandInWorld>();
        install_standard(*g_t.world[K]);
        if (g_t.setup) g_t.setup(*g_t.world[K]);
    }
    g_t.world[K]->si.log.clear();
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// The callees this test library does not emit (tests/game/CMakeLists.txt): recorders, so pairs run past them and
// compare each call's arguments, $ra and entry check point. (printf, the heap and the H_Cdvd requests come from
// install_standard.)
void scene2_world(StandInWorld& w) {
    const std::pair<u32, const char*> recorders[] = {
        {0x1052B0u, "sub_1052B0 (debug print)"}, {0x112420u, "sprCreateHandleFromData"}, {0x1124B0u, "sub_1124B0 (sprite file release)"},
        {0x1A4580u, "sub_1A4580 (camera update)"}, {0x316E00u, "sub_316E00 (model request)"}, {0x316F70u, "sub_316F70 (model ready)"},
        {0x3A2A30u, "sub_3A2A30"}, {0x3A2D80u, "itfMesMngInitialize"}, {0x3A30C0u, "itfMesMngRequestMessage"},
        {0x3A3420u, "sub_3A3420"}, {0x3A37C0u, "sub_3A37C0"}, {0x3A4360u, "sub_3A4360"}, {0x3BB010u, "sub_3BB010"},
        {0x3BCC80u, "sub_3BCC80"}, {0x3B55B0u, "sub_3B55B0 (curve row)"}, {kStubCompare, "guest callback stand-in"},
    };
    for (const auto& [va, name] : recorders) w.si.install_recorder(va, name, 0);
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12.. (float arguments, bits)
    bool persist = false;
    WorldSetup setup = scene2_world;
};

hgp::Run run_fns(Machine& m, Fn hand, Fn recomp, const char* name, const Args& a, u32 seed, const char* what, const Opt& o) {
    g_t.fn[0] = hand;
    g_t.fn[1] = recomp;
    g_t.fpr = o.fpr;
    if (!o.persist) {
        g_t.world[0].reset();
        g_t.world[1].reset();
    }
    g_t.persist = o.persist;
    g_t.setup = o.setup;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s (%s) seed %u\n", name, what, seed);
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    if (r.stopped) ++g_stops[std::string(name) + " @ " + hex64(r.stop_pc) + " (" + r.what.substr(0, 60) + ")"];
    ++g_pairs;
    return r;
}
// A pair of the slice function `name` (hand body vs its recompiled body).
hgp::Run spair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    return run_fns(m, c.hand, c.recomp, name, a, seed, what, o);
}
u32 v0u(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
s32 v0s(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }
u32 fb(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
// The stand-in log of the last pair's recompiled run.
const std::vector<StandInCall>& calls() {
    static const std::vector<StandInCall> none;
    return g_t.world[1] ? g_t.world[1]->si.log : none;
}
std::size_t calls_to(u32 va) { return g_t.world[1] ? g_t.world[1]->si.calls_to(va) : 0; }
bool printed_has(const std::string& s) {
    for (const StandInCall& c : calls())
        if (c.va == kPrintf && c.text.find(s) != std::string::npos) return true;
    return false;
}

// --- guest memory helpers -------------------------------------------------------------------------------------------
u32 ram_off(u32 va, u32 n) {
    const u32 a = va & 0x01FFFFFFu;
    return a + n <= EEMemory::kMainRamSize ? a : 0;
}
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 2), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[ram_off(va, 1)]; }
float rf(const Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void wvec(Machine& m, u32 va, float x, float y, float z) {
    wf(m, va, x);
    wf(m, va + 4, y);
    wf(m, va + 8, z);
}
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
void wstr(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }

const std::vector<u8>& snapshot(const char* dir) {
    static std::map<std::string, std::vector<u8>> cache;
    auto it = cache.find(dir);
    if (it == cache.end()) it = cache.emplace(dir, read_snapshot(dir)).first;
    return it->second;
}
bool restore(Machine& m, const char* dir) {
    const std::vector<u8>& s = snapshot(dir);
    if (s.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), s.data(), s.size());
    return true;
}
std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

// The scene manager of a machine (0 without one) and a host walk of one type list.
u32 scene_manager(const Machine& m) {
    const u32 scene = r32(m, kSceneSlot);
    return scene ? r32(m, scene + scn::scene::kResMgr) : 0u;
}
std::vector<u32> res_list(const Machine& m, u32 mgr, u32 type) {
    std::vector<u32> out;
    if (!mgr || type >= 22) return out;
    for (u32 r = r32(m, mgr + 4 * type); r != 0 && out.size() < 1024; r = r32(m, r + scn::res::kNext)) out.push_back(r);
    return out;
}
// A made-up resource record: zeroed, the id, scale 1.0 (as resrcMngAddRes leaves it).
void make_res(Machine& m, u32 va, u16 id) {
    zero(m, va, 544);
    w16(m, va + scn::res::kId, id);
    wvec(m, va + scn::res::kScale, 1.0f, 1.0f, 1.0f);
}
bool near(float a, float b, float tol = 1e-3f) { return std::fabs(a - b) <= tol; }
// The heading rule of sub_3B8540 / sub_3BBB90: acos(dot(normalised dir with y zeroed afterwards, axis)) * 57.29578,
// negated for x < 0 (the axis and the factor read from the ELF image).
float heading(const Machine& m, u32 axis_va, float x, float y, float z) {
    const float len = std::sqrt(x * x + y * y + z * z);
    const float nx = x / len, nz = z / len;
    const float dot = nx * rf(m, axis_va) + 0.0f * rf(m, axis_va + 4) + nz * rf(m, axis_va + 8);
    float a = static_cast<float>(std::acos(static_cast<double>(dot))) * rf(m, 0x7CAF18u);
    if (nx < 0.0f) a = -a;
    return a;
}
}  // namespace

// =====================================================================================================================
// 1. Every body on random worlds
// =====================================================================================================================
TEST_CASE("game(scene2): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const int before = g_pairs;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const u64 a0 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWorld, kWorldSize);
            run_fns(*m, c.hand, c.recomp, c.name, {a0, a1, a2, a3}, seed, c.name, {});
        }
    }
    MESSAGE("random worlds: " << (g_pairs - before) << " pairs");
}

// =====================================================================================================================
// 2. The live scenes and the facility tasks of the snapshots
// =====================================================================================================================
TEST_CASE("game(scene2): the SceneManager and the facility tasks on the live snapshots") {
    auto m = elf_machine();
    if (!m) return;
    int scenes = 0, resources = 0, cameras = 0, compares = 0, npcs = 0, tasks = 0;
    u32 seed = 1;
    for (const char* dir : kSnaps) {
        if (!restore(*m, dir)) {
            MESSAGE("SKIP " << dir << ": no snapshot");
            continue;
        }
        const u32 mgr = scene_manager(*m);
        if (mgr) {
            ++scenes;
            // every resource of every type list through the per-resource update
            for (u32 type = 1; type < 22; ++type)
                for (u32 res : res_list(*m, mgr, type)) {
                    REQUIRE(restore(*m, dir));
                    spair(*m, "sub_3B9610", {sx(res)}, seed++, dir);
                    ++resources;
                }
            REQUIRE(restore(*m, dir));
            spair(*m, "sub_3BCCB0", {0}, seed++, dir);  // the whole SceneManager frame
            REQUIRE(restore(*m, dir));
            spair(*m, "sub_3BD010", {0}, seed++, dir);  // the SceneManager draw
            REQUIRE(restore(*m, dir));
            spair(*m, "sub_3BCD80", {0}, seed++, dir);  // the task's destroy (a tail call)
            // the cameras: the eye (no matter whether active) and the placement
            for (u32 cam : res_list(*m, mgr, 7)) {
                REQUIRE(restore(*m, dir));
                Opt o;
                o.fpr[12] = fb(0.0f);
                spair(*m, "sub_3BB620", {sx(kOut), sx(cam)}, seed++, dir, o);
                REQUIRE(restore(*m, dir));
                spair(*m, "sub_3BB7A0", {sx(cam)}, seed++, dir);
                ++cameras;
            }
            // the effect-depth comparator: antisymmetric (int of a float difference truncates towards 0), 0 on itself
            const std::vector<u32> effs = res_list(*m, mgr, 6);
            for (std::size_t i = 0; i < effs.size() && i < 6; ++i)
                for (std::size_t j = i; j < effs.size() && j < 6; ++j) {
                    REQUIRE(restore(*m, dir));
                    w32(*m, kOut, effs[i]);
                    w32(*m, kOut + 4, effs[j]);
                    const hgp::Run ab = spair(*m, "sub_3BCDA0", {sx(kOut), sx(kOut + 4)}, seed++, dir);
                    const hgp::Run ba = spair(*m, "sub_3BCDA0", {sx(kOut + 4), sx(kOut)}, seed++, dir);
                    if (!ab.stopped && !ba.stopped) {
                        CHECK(v0s(ab) == -v0s(ba));
                        if (i == j) CHECK(v0s(ab) == 0);
                    }
                    ++compares;
                }
            // the sorted effect draw on the live list
            if (!effs.empty()) {
                REQUIRE(restore(*m, dir));
                spair(*m, "sub_3BCEB0", {sx(effs[0])}, seed++, dir);
            }
            // the NPC icon wrapper: found NPCs give sub_3BAC40's 1, a missing one 0
            for (u32 npc : res_list(*m, mgr, 3)) {
                REQUIRE(restore(*m, dir));
                const u32 n = r16(*m, npc + scn::res::kId) & 0x3FFu;
                const hgp::Run r = spair(*m, "sub_3BB060", {n, 10}, seed++, dir);
                if (!r.stopped) CHECK(v0u(r) == 1u);
                ++npcs;
            }
            REQUIRE(restore(*m, dir));
            const hgp::Run none = spair(*m, "sub_3BB060", {0x3FF, 1}, seed++, dir);
            if (!none.stopped && res_list(*m, mgr, 3).size() < 0x3FF) CHECK(v0u(none) == 0u);
        }
        // the MsgAssist task and its helpers on the live work
        if (const u32 work = r32(*m, kAssistSlot)) {
            REQUIRE(restore(*m, dir));
            spair(*m, "fclMisc_UpdateMsgAssistTask", {0}, seed++, dir);
            REQUIRE(restore(*m, dir));
            spair(*m, "sub_3C8550", {sx(work)}, seed++, dir);
            REQUIRE(restore(*m, dir));
            spair(*m, "sub_3C8FA0", {0}, seed++, dir);
            const u32 list = r32(*m, work + scene2::assist::kList);
            for (u32 node = list ? r32(*m, list + scene2::nml::kFirst) : 0u, k = 0; node && k < 8; node = r32(*m, node + scene2::nmnode::kNext), ++k) {
                REQUIRE(restore(*m, dir));
                spair(*m, "sub_3C8B50", {sx(work), sx(r32(*m, node + scene2::nmnode::kPayload))}, seed++, dir);
            }
            ++tasks;
        }
        // the fclBank task
        if (r32(*m, kBankSlot)) {
            REQUIRE(restore(*m, dir));
            spair(*m, "fclBank_UpdateTask", {0}, seed++, dir);
            ++tasks;
        }
    }
    MESSAGE("snapshots: " << scenes << " scenes, " << resources << " resources updated, " << cameras << " cameras, " << compares
                          << " effect comparisons, " << npcs << " NPC icons, " << tasks << " facility tasks");
}

// =====================================================================================================================
// 3. The per-resource update on made-up records (documented rules)
// =====================================================================================================================
TEST_CASE("game(scene2): the per-resource update -- moves, rotation, scale, tween, fade, steps, paths") {
    auto m = elf_machine();
    if (!m) return;
    using namespace scene2;
    const u32 res = kOut;
    u32 seed = 100;
    auto flags = [&]() { return r32(*m, res + scn::res::kFlags); };
    SUBCASE("timed move, linear: pos = from + (to - from) / frames * time; time += steps; at the end the target") {
        make_res(*m, res, 0x2000 | 5);  // a position resource: no object to transform
        w32(*m, res + scn::res::kFlags, 1);
        wvec(*m, res + scn::res::kMoveFrom, 0, 0, 0);
        wvec(*m, res + scn::res::kMoveTo, 30, 60, 90);
        w8(*m, res + res::kMoveKind, 1);
        w32(*m, res + res::kMoveFrames, 3);
        w32(*m, res + res::kMoveTime, 1);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "timed move");
        CHECK(near(rf(*m, res + scn::res::kPos), 10));
        CHECK(near(rf(*m, res + scn::res::kPosY), 20));
        CHECK(near(rf(*m, res + scn::res::kPosZ), 30));
        CHECK(r32(*m, res + res::kMoveTime) == 2u);
        CHECK((flags() & 1u) == 1u);
        w32(*m, res + res::kMoveTime, 3);  // time == frames: the target, the move ends
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "timed move end");
        CHECK(rf(*m, res + scn::res::kPosY) == 60.0f);
        CHECK((flags() & 1u) == 0u);
        // 0 frames: "move length0 end", the target at once
        w32(*m, res + scn::res::kFlags, 1);
        w32(*m, res + res::kMoveFrames, 0);
        wvec(*m, res + scn::res::kPos, 0, 0, 0);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "timed move, 0 frames");
        CHECK(rf(*m, res + scn::res::kPosZ) == 90.0f);
        CHECK((flags() & 1u) == 0u);
        CHECK(printed_has("move length0  end="));
    }
    SUBCASE("speed move: one step of +88 towards the target; within one step the target and \"move idou end\"") {
        make_res(*m, res, 0x2000 | 6);
        w32(*m, res + scn::res::kFlags, 1);
        wvec(*m, res + scn::res::kMoveTo, 100, 0, 0);
        wf(*m, res + res::kMoveSpeed, 10.0f);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "speed move");
        CHECK(near(rf(*m, res + scn::res::kPos), 10.0f));
        CHECK((flags() & 1u) == 1u);
        wvec(*m, res + scn::res::kPos, 95, 0, 0);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "speed move end");
        CHECK(rf(*m, res + scn::res::kPos) == 100.0f);
        CHECK((flags() & 1u) == 0u);
        CHECK(printed_has("move idou end="));
    }
    SUBCASE("rotation: the shorter turn, linear in time, the angles wrapped to [0, 360); the first frame only arms the time") {
        make_res(*m, res, 0x2000 | 7);
        w32(*m, res + scn::res::kFlags, 4);
        wvec(*m, res + scn::res::kRotFrom, 0, 0, 0);
        wvec(*m, res + scn::res::kRotTo, 90, 350, 0);
        w32(*m, res + scn::res::kRotFrames, 3);
        w32(*m, res + scn::res::kRotTime, 0);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "rotation arm");
        CHECK(r32(*m, res + scn::res::kRotTime) == 1u);  // = the steps of this frame, nothing turned
        CHECK(rf(*m, res + scn::res::kRot) == 0.0f);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "rotation step");
        CHECK(near(rf(*m, res + scn::res::kRot), 30.0f));
        CHECK(near(rf(*m, res + scn::res::kRotY), 360.0f - 10.0f / 3.0f));  // 350 is -10 the shorter way, wrapped
        CHECK(r32(*m, res + scn::res::kRotTime) == 2u);
        w32(*m, res + scn::res::kRotFrames, 0);  // 0 frames: the target at once, the request ends
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "rotation 0 frames");
        CHECK(rf(*m, res + scn::res::kRotY) == 350.0f);
        CHECK((flags() & 4u) == 0u);
    }
    SUBCASE("scale tween (0x8000): from + (to - from) / frames * time") {
        make_res(*m, res, 0x2000 | 8);
        w32(*m, res + scn::res::kFlags, 0x8000);
        wvec(*m, res + res::kScaleFrom, 1, 1, 1);
        wvec(*m, res + res::kScaleTo, 2, 4, 8);
        w32(*m, res + res::kScaleFrames, 4);
        w32(*m, res + res::kScaleTime, 2);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "scale");
        CHECK(near(rf(*m, res + scn::res::kScale), 1.5f));
        CHECK(near(rf(*m, res + scn::res::kScaleY), 2.5f));
        CHECK(near(rf(*m, res + scn::res::kScaleZ), 4.5f));
        CHECK(r32(*m, res + res::kScaleTime) == 3u);
    }
    SUBCASE("type-7 fov tween (0x400): the time base is +92 (the move time), its own counter +208 only ends it") {
        make_res(*m, res, 0x1C00 | 1);
        w32(*m, res + scn::res::kFlags, 0x400);
        wf(*m, res + res::kTweenFrom, 30.0f);
        wf(*m, res + res::kTweenTo, 60.0f);
        w32(*m, res + res::kTweenFrames, 10);
        w32(*m, res + res::kTweenTime, 0);
        w32(*m, res + res::kMoveTime, 5);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "fov tween");
        CHECK(near(rf(*m, res + cam::kFov), 45.0f));  // 30 + 3 * 5 (the quirk), not 30 + 3 * 0
        CHECK(r32(*m, res + res::kTweenTime) == 1u);
        w32(*m, res + res::kTweenTime, 10);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "fov tween end");
        CHECK(rf(*m, res + cam::kFov) == 60.0f);
        CHECK((flags() & 0x400u) == 0u);
    }
    SUBCASE("alpha fade (0x4000) on a type without an object: the timer runs, the flag ends it") {
        make_res(*m, res, 0x2000 | 9);
        w32(*m, res + scn::res::kFlags, 0x4000);
        w8(*m, res + scn::res::kFadeFrom, 0);
        w8(*m, res + scn::res::kFadeTo, 255);
        w32(*m, res + scn::res::kFadeFrames, 4);
        w32(*m, res + scn::res::kFadeTime, 1);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "fade");
        CHECK(r32(*m, res + scn::res::kFadeTime) == 2u);
        CHECK((flags() & 0x4000u) != 0u);
        w32(*m, res + scn::res::kFadeTime, 4);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "fade end");
        CHECK((flags() & 0x4000u) == 0u);
    }
    SUBCASE("steps: flag 0x20 takes +244 once; flag bit 3 stops the per-frame step") {
        make_res(*m, res, 0x2000 | 10);
        w32(*m, res + scn::res::kFlags, 1 | 0x20);
        w32(*m, res + res::kPendingSteps, 3);
        wvec(*m, res + scn::res::kMoveTo, 40, 0, 0);
        w8(*m, res + res::kMoveKind, 1);
        w32(*m, res + res::kMoveFrames, 8);
        w32(*m, res + res::kMoveTime, 1);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "pending steps");
        CHECK(r32(*m, res + res::kMoveTime) == 4u);
        CHECK(r32(*m, res + res::kPendingSteps) == 0u);
        CHECK((flags() & 0x20u) == 0u);
        w32(*m, res + scn::res::kFlags, 1 | 8);  // shown: no step this frame
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "no step");
        CHECK(r32(*m, res + res::kMoveTime) == 4u);
    }
    SUBCASE("bezier path move: the request (block, copy, length, print), the point and heading at a distance") {
        const u32 path = kOut + 0x1000;
        zero(*m, path, 512);
        w8(*m, path, 1);  // one segment along +x: (0,0,0) (10,0,0) (20,0,0) (30,0,0) -- B(t) = 30 t
        for (int i = 0; i < 4; ++i) wvec(*m, path + 4 + 12 * i, 10.0f * i, 0, 0);
        make_res(*m, res, 0x2000 | 11);
        w32(*m, res + scn::res::kFlags, 0x40);
        Opt o;
        o.fpr[12] = fb(5.0f);
        o.persist = true;  // the block stays in the heap for the update below
        g_t.world[0].reset();
        g_t.world[1].reset();
        const hgp::Run rq = spair(*m, "sub_3B88C0", {sx(res), sx(path), 0}, seed++, "path request", o);
        CHECK(v0u(rq) == 1u);
        const u32 block = r32(*m, res + res::kPathBlock);
        CHECK(block != 0u);
        CHECK(std::memcmp(m->at(block), m->at(path), 304) == 0);
        CHECK((flags() & 0x41u) == 1u);  // bit 0 on, 0x40 off (loop argument 0)
        CHECK(r8(*m, res + res::kMoveKind) == 2u);
        CHECK(rf(*m, res + res::kMoveSpeed) == 5.0f);
        CHECK(near(rf(*m, res + res::kMoveFrames), 30.0f));  // the path length
        CHECK(printed_has("path bezier max kyori = 30.00"));  // 20 chords of float sums (29.999989 with the old truncating SQRT.S)
        wf(*m, res + res::kMoveTime, 15.0f);  // halfway
        const hgp::Run up = spair(*m, "sub_3B9610", {sx(res)}, seed++, "path step", o);
        CHECK(near(rf(*m, res + scn::res::kPos), 15.0f));
        CHECK(near(rf(*m, res + scn::res::kPosY), 0.0f));
        CHECK(near(rf(*m, res + res::kMoveTime), 20.0f));  // + speed x steps
        // the heading of the path's local direction (sub_3BBB90 of one chord; which end it points from is the
        // original's: either sign of the +x heading, wrapped to [0, 360))
        const float h = heading(*m, 0x6A2F48u, -1, 0, 0);
        const float ry = rf(*m, res + scn::res::kRotY);
        CHECK((near(ry, h < 0 ? h + 360.0f : h, 1e-2f) || near(ry, -h < 0 ? -h + 360.0f : -h, 1e-2f)));
        (void)up;
        // the point beyond the end: the last point, flag bit 0 off (no loop)
        wf(*m, res + res::kMoveTime, 31.0f);
        spair(*m, "sub_3B9610", {sx(res)}, seed++, "path end", o);
        CHECK(near(rf(*m, res + scn::res::kPos), 30.0f));
        CHECK((flags() & 1u) == 0u);
        g_t.world[0].reset();
        g_t.world[1].reset();
    }
    SUBCASE("the path at a distance and the direction angle helpers") {
        const u32 path = kOut + 0x1000;
        zero(*m, path, 512);
        w8(*m, path, 1);
        for (int i = 0; i < 4; ++i) wvec(*m, path + 4 + 12 * i, 0, 0, 10.0f * i);  // along +z
        for (float d : {0.0f, 7.5f, 15.0f, 29.0f, 30.0f, 45.0f}) {
            Opt o;
            o.fpr[12] = fb(d);
            o.fpr[13] = fb(30.0f);
            const hgp::Run r = spair(*m, "sub_3BC220", {sx(path), sx(kOut), sx(kOut + 16)}, seed++, "path at", o);
            INFO("d = " << d);
            CHECK(near(rf(*m, kOut + 8), std::min(d, 30.0f), 2e-3f));
            CHECK(near(rf(*m, kOut), 0.0f));
            if (d >= 30.0f) CHECK(v0u(r) == 0x3F800000u);
        }
        // sub_3B8540: the direction (not normalised) and its heading; a zero direction returns 0 and writes nothing
        wvec(*m, kOut, 1, 2, 3);
        wvec(*m, kOut + 16, 1, 2, 3);
        w32(*m, kOut + 32, 0xDEADBEEFu);
        const hgp::Run z = spair(*m, "sub_3B8540", {sx(kOut), sx(kOut + 16), sx(kOut + 48), sx(kOut + 32)}, seed++, "zero direction");
        CHECK(v0u(z) == 0u);
        CHECK(r32(*m, kOut + 32) == 0xDEADBEEFu);
        for (const auto& d : std::vector<std::array<float, 3>>{{10, 0, 0}, {-10, 0, 0}, {0, 0, 10}, {3, 4, -12}, {-5, 1, -5}}) {
            wvec(*m, kOut, 0, 0, 0);
            wvec(*m, kOut + 16, d[0], d[1], d[2]);
            const hgp::Run r = spair(*m, "sub_3B8540", {sx(kOut), sx(kOut + 16), sx(kOut + 48), sx(kOut + 32)}, seed++, "direction");
            CHECK(v0u(r) == 1u);
            CHECK(rf(*m, kOut + 48) == d[0]);
            CHECK(rf(*m, kOut + 56) == d[2]);
            CHECK(near(rf(*m, kOut + 32), heading(*m, 0x6A2DC8u, d[0], d[1], d[2]), 1e-2f));
            wvec(*m, kOut + 64, d[0], d[1], d[2]);
            spair(*m, "sub_3BBB90", {sx(kOut + 64), sx(kOut + 80)}, seed++, "angles");
            CHECK(rf(*m, kOut + 80) == 0.0f);
            CHECK(rf(*m, kOut + 88) == 0.0f);
            CHECK(near(rf(*m, kOut + 84), heading(*m, 0x6A2F48u, d[0], d[1], d[2]), 1e-2f));
        }
    }
}

// =====================================================================================================================
// 4. The camera shake and the camera eye
// =====================================================================================================================
TEST_CASE("game(scene2): the camera shake and the camera eye (documented rules)") {
    auto m = elf_machine();
    if (!m) return;
    u32 seed = 300;
    // off: the offset words are cleared
    w16(*m, kShakeOn, 0);
    for (u32 i = 0; i < 4; ++i) w32(*m, kShakeOffset + 4 * i, 0x41200000u + i);
    spair(*m, "sub_3BC940", {0}, seed++, "shake off");
    for (u32 i = 0; i < 4; ++i) CHECK(r32(*m, kShakeOffset + 4 * i) == 0u);
    // on with no frames left: switched off, the offset kept
    w16(*m, kShakeOn, 1);
    w16(*m, kShakeFrames, 0);
    wf(*m, kShakeOffset, 3.0f);
    spair(*m, "sub_3BC940", {0}, seed++, "shake expired");
    CHECK(r16(*m, kShakeOn) == 0u);
    CHECK(rf(*m, kShakeOffset) == 3.0f);
    // one axis: the amplitude decays by 1 / (frames + 5), the offset stays within +-a; the other axis untouched
    wf(*m, kShakeRateX, 0.5f);
    wf(*m, kShakeRateX + 4, 0.5f);
    for (int frame = 0; frame < 12; ++frame) {
        w16(*m, kShakeOn, 1);
        w16(*m, kShakeFrames, 3);
        w16(*m, kShakeAmpX, 10);
        w16(*m, kShakeAmpZ, 0);
        wf(*m, kShakeOffset + 4, 7.0f);
        const float a = 10.0f * rf(*m, kShakeScale);
        spair(*m, "sub_3BC940", {0}, seed++, "shake step");
        CHECK(r16(*m, kShakeAmpX) == 9u);  // 10 - 10 / 8
        CHECK(r16(*m, kShakeFrames) == 2u);
        CHECK(rf(*m, kShakeOffset + 4) == 7.0f);
        CHECK(std::fabs(rf(*m, kShakeOffset)) <= a);
    }
    // the eye without a target: out = pos - $f12 x the view direction (sub_3BB450: +z for unturned angles); on the dorm
    // machine (the matrix helpers reach the RW engine's slots, empty in the bare ELF image)
    if (!restore(*m, "dorm_replay_4900")) {
        MESSAGE("SKIP the eye: no dorm_replay_4900");
        return;
    }
    const u32 cam = kOut;
    make_res(*m, cam, 0x1C00 | 2);
    wvec(*m, cam + scn::res::kPos, 1, 2, 3);
    for (float dist : {0.0f, 5.0f, -2.5f}) {
        Opt o;
        o.fpr[12] = fb(dist);
        const hgp::Run r = spair(*m, "sub_3BB620", {sx(kOut + 0x800), sx(cam)}, seed++, "eye", o);
        INFO("eye dist " << dist << (r.stopped ? " stopped: " + r.what : std::string()) << ": " << rf(*m, kOut + 0x800) << " "
                         << rf(*m, kOut + 0x804) << " " << rf(*m, kOut + 0x808));
        REQUIRE(!r.stopped);
        const float dir[3] = {0.0f, 0.0f, 1.0f};
        for (u32 k = 0; k < 3; ++k) CHECK(near(rf(*m, kOut + 0x800 + 4 * k), (1.0f + k) - dist * dir[k], 1e-3f));
    }
}

// =====================================================================================================================
// 5. The message-window slot, the message handles, nmListSort
// =====================================================================================================================
TEST_CASE("game(scene2): message-window slots, message handles and nmListSort (documented rules)") {
    auto m = elf_machine();
    if (!m) return;
    using namespace scene2;
    u32 seed = 500;
    const u32 slot = kOut;
    auto st = [&]() { return static_cast<s8>(r8(*m, slot + msgw::kState)); };
    // open: the reset (handle -1 first) makes the "already open" branch dead -- a handle is always created
    for (s32 before : {-1, 3}) {
        zero(*m, slot, 16);
        w32(*m, slot + msgw::kHandle, static_cast<u32>(before));
        Opt o;
        o.setup = [](StandInWorld& w) {
            scene2_world(w);
            w.si.install_recorder(0x3A2D80u, "itfMesMngInitialize", 7);
        };
        const hgp::Run r = spair(*m, "sub_3C91B0", {sx(slot), 4}, seed++, "open", o);
        CHECK(v0u(r) == 1u);
        CHECK(r32(*m, slot + msgw::kHandle) == 7u);
        CHECK(st() == 0);
        CHECK(r8(*m, slot + msgw::kHold) == 0u);
        CHECK(r32(*m, slot + msgw::kSelect) == 0xFFFFFFFFu);
        CHECK(r8(*m, slot + msgw::kFlag12) == 1u);
        CHECK(r8(*m, slot + msgw::kChoice) == 1u);
        CHECK(calls_to(0x3A2D80u) == 1u);
        CHECK(calls_to(0x3A4360u) == 1u);
    }
    // the update: 2 drops a pending selection and closes unless held; 3 clears (state 0)
    zero(*m, slot, 16);
    w32(*m, slot + msgw::kHandle, 2);
    w8(*m, slot + msgw::kState, 2);
    w32(*m, slot + msgw::kSelect, 5);
    spair(*m, "sub_3C9390", {sx(slot)}, seed++, "state 2");
    CHECK(r32(*m, slot + msgw::kSelect) == 0xFFFFFFFFu);
    CHECK(st() == 3);
    w8(*m, slot + msgw::kState, 2);
    w8(*m, slot + msgw::kHold, 1);
    spair(*m, "sub_3C9390", {sx(slot)}, seed++, "state 2 held");
    CHECK(st() == 2);
    w8(*m, slot + msgw::kState, 3);
    spair(*m, "sub_3C9390", {sx(slot)}, seed++, "state 3");
    CHECK(st() == 0);
    CHECK(calls_to(0x3A3420u) == 1u);
    // no handle: nothing
    w32(*m, slot + msgw::kHandle, 0xFFFFFFFFu);
    w8(*m, slot + msgw::kState, 3);
    spair(*m, "sub_3C9390", {sx(slot)}, seed++, "no handle");
    CHECK(st() == 3);
    // show: state 1, the request recorded with the message id
    w32(*m, slot + msgw::kHandle, 2);
    w8(*m, slot + msgw::kState, 0);
    const hgp::Run sh = spair(*m, "sub_3C9290", {sx(slot), 3, 0x1234}, seed++, "show");
    CHECK(v0u(sh) == 0u);
    CHECK(st() == 1);
    REQUIRE(calls_to(0x3A30C0u) == 1u);
    for (const StandInCall& c : calls())
        if (c.va == 0x3A30C0u) CHECK(c.args[1] == 0x1234u);
    // clear: 1 with a handle (state 0), 0 without, 0 for NULL
    w8(*m, slot + msgw::kState, 2);
    CHECK(v0u(spair(*m, "sub_3C9460", {sx(slot)}, seed++, "clear")) == 1u);
    CHECK(st() == 0);
    CHECK(v0u(spair(*m, "sub_3C9460", {0}, seed++, "clear NULL")) == 0u);
    // release: handle -1, state / hold 0
    w8(*m, slot + msgw::kState, 1);
    w8(*m, slot + msgw::kHold, 1);
    spair(*m, "sub_3C9240", {sx(slot)}, seed++, "release");
    CHECK(r32(*m, slot + msgw::kHandle) == 0xFFFFFFFFu);
    CHECK(st() == 0);
    CHECK(r8(*m, slot + msgw::kHold) == 0u);
    // the message-handle table 0x6A3E50: a live handle destroyed and marked -1; -1 left alone
    for (u32 i = 0; i < 4; ++i) {
        const u32 before = r32(*m, kMsgHandles + 4 * i);
        const hgp::Run r = spair(*m, "sub_3C7DD0", {i}, seed++, "handle table");
        if (!r.stopped) CHECK(r32(*m, kMsgHandles + 4 * i) == (static_cast<s32>(before) >= 0 ? 0xFFFFFFFFu : before));
    }
    // nmListSort: the nodes into an array, qsort with a guest comparator (here a stand-in comparing the payload words),
    // relinked in that order, the cursor on the first
    const u32 list = kOut + 0x400;
    const u32 values[] = {50, 10, 40, 30, 20};
    zero(*m, list, 0x400);
    u32 prev = 0;
    for (u32 i = 0; i < 5; ++i) {
        const u32 node = list + 0x40 + 0x40 * i;
        w32(*m, node + nmnode::kPayload, node + 0x30);
        w32(*m, node + 0x30, values[i]);
        if (prev) w32(*m, prev + nmnode::kNext, node);
        else w32(*m, list + nml::kFirst, node);
        prev = node;
    }
    w16(*m, list + nml::kCount, 5);
    Opt o;
    o.setup = [](StandInWorld& w) {
        scene2_world(w);
        w.si.install(kStubCompare, "compare payload words", [](EEContext& ctx, StandIns&, StandInCall& c) {
            auto word = [&](u32 pp) {
                const u32 node = ctx.memory->read<u32>(pp);
                return static_cast<s32>(ctx.memory->read<u32>(ctx.memory->read<u32>(node + 20)));
            };
            c.v0 = static_cast<u64>(static_cast<s64>(word(static_cast<u32>(c.args[0])) - word(static_cast<u32>(c.args[1]))));
        });
    };
    const hgp::Run r = spair(*m, "sub_3C4FC0", {sx(list), kStubCompare}, seed++, "nmListSort", o);
    if (!r.stopped) {
        std::vector<u32> got;
        for (u32 node = r32(*m, list + nml::kFirst); node && got.size() < 8; node = r32(*m, node + nmnode::kNext))
            got.push_back(r32(*m, r32(*m, node + nmnode::kPayload)));
        CHECK(got == std::vector<u32>{10, 20, 30, 40, 50});
        CHECK(r32(*m, list + nml::kCursor) == r32(*m, list + nml::kFirst));
    } else {
        MESSAGE("nmListSort stopped: " << r.what << " at " << hex64(r.stop_pc));
    }
    // an empty list: nothing (no allocation)
    zero(*m, list, 0x40);
    spair(*m, "sub_3C4FC0", {sx(list), kStubCompare}, seed++, "nmListSort empty", o);
    CHECK(calls_to(kStubCompare) == 0u);
}

// =====================================================================================================================
// 6. fclBank, psStatus, psModel
// =====================================================================================================================
TEST_CASE("game(scene2): fclBank, psStatus and psModel (documented rules)") {
    auto m = elf_machine();
    if (!m) return;
    using namespace scene2;
    u32 seed = 700;
    SUBCASE("fclBank: KILL / CLOSE / END and the panel pick") {
        const u32 obj = kOut, work = kOut + 0x100;
        zero(*m, obj, 0x400);
        w32(*m, kBankSlot, obj);
        w32(*m, obj + bank::kWork, work);
        auto panel = [&](u32 i) { return work + bank::kPanels + bank::kPanelStride * i; };
        w16(*m, panel(0) + bank::kPFlags, 1 | 4 | 0x1000);
        w16(*m, panel(0) + bank::kPSlot, 0);
        w16(*m, panel(1) + bank::kPFlags, 1 | 4 | 8 | 0x400);
        w16(*m, panel(1) + bank::kPSlot, 1);
        w16(*m, panel(2) + bank::kPFlags, 1 | 4 | 0x800);
        w16(*m, panel(2) + bank::kPSlot, 2);
        const hgp::Run r = spair(*m, "fclBank_UpdateTask", {0}, seed++, "bank update");
        CHECK(v0u(r) == 0u);
        CHECK(r16(*m, panel(0) + bank::kPFlags) == 0u);  // KILL: 0x1000, open, used off
        CHECK((r16(*m, panel(1) + bank::kPFlags) & 0x40Du) == 9u);  // CLOSE while shown: 0x400 and open off, state 4
        CHECK(r16(*m, panel(1) + bank::kPState) != 0u);
        CHECK(r16(*m, panel(2) + bank::kPFlags) == 0u);  // END while not shown
        CHECK(printed_has("KILL"));
        CHECK(printed_has("CLOSE"));
        CHECK(printed_has("END"));
        // END while shown: turns into a close request
        w16(*m, panel(2) + bank::kPFlags, 1 | 4 | 8 | 0x800);
        spair(*m, "fclBank_UpdateTask", {0}, seed++, "bank end shown");
        CHECK((r16(*m, panel(2) + bank::kPFlags) & 0x400u) != 0u);
        // the pick: the first free panel takes the request (bank, flags | used | opening, its slot); "BankNo:%d"
        const u32 node = kOut + 0x300, req = kOut + 0x380;
        zero(*m, work, 0x100);
        zero(*m, node, 0x40);
        w32(*m, node + nmnode::kPayload, req);
        w16(*m, req + bankreq::kFlags, 0x100);
        w32(*m, req + bankreq::kBank, 0x00120304u);
        w32(*m, obj + nml::kFirst, node);
        w16(*m, panel(0) + bank::kPFlags, 1 | 8);  // used and shown
        const hgp::Run p = spair(*m, "sub_3CF6C0", {sx(node)}, seed++, "bank pick");
        if (!p.stopped) CHECK(v0s(p) == 1);  // (on the bare ELF image H_ChrDsp_Request reaches an empty RW slot)
        CHECK(r32(*m, panel(1) + bank::kPBank) == 0x00120304u);
        CHECK(r16(*m, panel(1) + bank::kPFlags) == (0x100u | 1u | 2u));
        CHECK(r16(*m, panel(1) + bank::kPSlot) == 1u);
        CHECK(printed_has("BankNo:1"));
        // every panel used and opening or shown: -1
        for (u32 i = 0; i < 3; ++i) w16(*m, panel(i) + bank::kPFlags, 1 | 2);
        const hgp::Run none = spair(*m, "sub_3CF6C0", {sx(node)}, seed++, "bank pick none");
        CHECK(v0s(none) == -1);
        CHECK(printed_has("BankNo:-1"));
        // on the dorm machine the bust-up request runs through: the file of character 0x12 is asked for
        if (restore(*m, "dorm_replay_4900")) {
            zero(*m, obj, 0x400);
            w32(*m, kBankSlot, obj);
            w32(*m, obj + bank::kWork, work);
            zero(*m, node, 0x40);
            w32(*m, node + nmnode::kPayload, req);
            w16(*m, req + bankreq::kFlags, 0x100);
            w32(*m, req + bankreq::kBank, 0x00120304u);
            w32(*m, obj + nml::kFirst, node);
            w16(*m, panel(0) + bank::kPFlags, 1 | 8);
            // (the made-up node has no owner callbacks: the unlink's release ends the run at an empty pointer, in both
            // bodies alike, after everything checked here)
            spair(*m, "sub_3CF6C0", {sx(node)}, seed++, "bank pick (dorm)");
            CHECK(r16(*m, panel(1) + bank::kPFlags) == (0x100u | 1u | 2u));
            CHECK(r32(*m, panel(1) + bank::kPBank) == 0x00120304u);
            CHECK(calls_to(kHCdvdRequestFn) == 1u);
            CHECK(r32(*m, obj + nml::kFirst) == 0u);  // the request unlinked
        }
    }
    SUBCASE("psStatus: fades, slide, the layout callback, the load states") {
        const u32 task = kOut, work = kOut + 0x100;
        zero(*m, task, 0x400);
        w32(*m, task + scn::task::kWork, work);
        w32(*m, work + ps::kState, 4);
        w32(*m, work + ps::kLayout, kStubCompare);
        w32(*m, work + ps::kFlags, 8);
        w16(*m, work + ps::kFadeIn, 10);
        w16(*m, work + ps::kTimer, 4);
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "fade in");
        CHECK(r16(*m, work + ps::kTimer) == 5u);
        CHECK(r16(*m, work + ps::kAlpha) == 127u);  // 255 x 5 / 10
        CHECK((r32(*m, work + ps::kFlags) & 9u) == 9u);
        REQUIRE(calls_to(kStubCompare) == 1u);
        for (const StandInCall& c : calls())
            if (c.va == kStubCompare) CHECK(static_cast<u32>(c.args[0]) == work);
        w16(*m, work + ps::kTimer, 9);
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "fade in end");
        CHECK(r16(*m, work + ps::kAlpha) == 255u);
        CHECK(r16(*m, work + ps::kTimer) == 0u);
        CHECK((r32(*m, work + ps::kFlags) & 8u) == 0u);
        w32(*m, work + ps::kFlags, 0x10 | 1);
        w16(*m, work + ps::kFadeOut, 4);
        w16(*m, work + ps::kTimer, 1);
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "fade out");
        CHECK(r16(*m, work + ps::kAlpha) == 128u);  // 255 - 510 / 4
        w16(*m, work + ps::kTimer, 3);
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "fade out end");
        CHECK((r32(*m, work + ps::kFlags) & 0x11u) == 0u);
        // slide: side 1 counts +22 up to +20, side 0 down to 0
        w32(*m, work + ps::kFlags, 0x40);
        w16(*m, work + ps::kSlideFrames, 3);
        w16(*m, work + ps::kSlideTime, 2);
        w8(*m, work + ps::kRow, 1);
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "slide in");
        CHECK(r16(*m, work + ps::kSlideTime) == 3u);
        CHECK((r32(*m, work + ps::kFlags) & 0x40u) == 0u);
        w32(*m, work + ps::kFlags, 0x40);
        w8(*m, work + ps::kRow, 0);
        w16(*m, work + ps::kSlideTime, 2);
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "slide out");
        CHECK(r16(*m, work + ps::kSlideTime) == 1u);
        CHECK((r32(*m, work + ps::kFlags) & 0x40u) != 0u);
        // the load states: 1 prints and requests the file (state 3, +200 = the request); unknown states do nothing
        wstr(*m, kOut + 0x300, "facility/psstatus.bin");
        w32(*m, work + ps::kFile, kOut + 0x300);
        w32(*m, work + ps::kState, 1);
        Opt o;
        o.setup = [](StandInWorld& w) {
            scene2_world(w);
            w.cd.load = false;
        };
        spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "load start", o);
        CHECK(r32(*m, work + ps::kState) == 3u);
        CHECK(r32(*m, work + ps::kCdReq) != 0u);
        CHECK(printed_has("psStatusCalc START"));
        CHECK(printed_has("psStatusCalc LOAD facility/psstatus.bin"));
        w32(*m, work + ps::kState, 9);
        const hgp::Run u = spair(*m, "fclMisc_UpdatePsStatusTask", {sx(task)}, seed++, "unknown state");
        CHECK(v0u(u) == 0u);
        CHECK(r32(*m, work + ps::kState) == 9u);
    }
    SUBCASE("psStatus layouts: every kind, page, row count and cursor") {
        const u32 work = kOut + 0x100;
        int n = 0;
        for (s32 kind = 0; kind <= 4; ++kind)
            for (s16 page = 0; page <= 4; ++page)
                for (s8 rows = 3; rows <= 5; ++rows) {
                    zero(*m, work, 0x100);
                    w32(*m, work + ps::kKind, static_cast<u32>(kind));
                    w16(*m, work + ps::kAlpha, 200);
                    w16(*m, work + ps::kPage, static_cast<u16>(page));
                    w8(*m, work + ps::kRows, static_cast<u8>(rows));
                    w8(*m, work + ps::kRow, static_cast<u8>((kind + page) % rows));
                    w16(*m, work + ps::kPersona, static_cast<u16>(kind ? 3 * kind : 0));
                    w32(*m, work + ps::kValue, static_cast<u32>(page * 11));
                    for (const char* f : {"sub_3CACC0", "sub_3CB1F0", "sub_3CB960", "sub_3CBA50", "sub_3CCC40", "sub_3CD0B0", "sub_3CD5A0"}) {
                        spair(*m, f, {sx(work)}, seed++, "layout");
                        ++n;
                    }
                }
        MESSAGE("layouts: " << n << " pairs");
    }
    SUBCASE("psModel: no model, the model request, the rgba fade") {
        const u32 task = kOut, work = kOut + 0x100, model = kModelVa;
        zero(*m, task, 0x1000);
        w32(*m, task + scn::task::kWork, work);
        w32(*m, work + psm::kState, 1);
        spair(*m, "sub_3CE2A0", {sx(task)}, seed++, "no persona");
        CHECK(r32(*m, work + psm::kState) == 4u);
        CHECK((r32(*m, work + psm::kFlags) & 1u) == 1u);
        Opt o;
        o.setup = [](StandInWorld& w) {
            scene2_world(w);
            w.si.install_recorder(0x316E00u, "sub_316E00 (model request)", kModelVa);
        };
        zero(*m, work, 0x100);
        w32(*m, work + psm::kState, 1);
        w16(*m, work + psm::kPersona, 5);
        spair(*m, "sub_3CE2A0", {sx(task)}, seed++, "model request", o);
        CHECK(r32(*m, work + psm::kModel) == model);
        CHECK(r32(*m, work + psm::kState) == 3u);  // sub_316F70 answers 0: still loading
        bool req = false;
        for (const StandInCall& c : calls())
            if (c.va == 0x316E00u) req = c.args[0] == 11 && c.args[1] == 5 && c.args[2] == 0;
        CHECK(req);
        // state 4 (shown, animating): one step of the rgba fade from -> to over the frames
        zero(*m, work, 0x100);
        w32(*m, work + psm::kState, 4);
        w32(*m, work + psm::kFlags, 1 | 0x10000);
        const u8 to[4] = {200, 100, 50, 250};
        for (u32 k = 0; k < 4; ++k) w8(*m, work + psm::kFadeTo + k, to[k]);
        w16(*m, work + psm::kFadeFrames, 2);
        spair(*m, "sub_3CE2A0", {sx(task)}, seed++, "rgba fade");
        CHECK(r16(*m, work + psm::kFadeTime) == 1u);
        for (u32 k = 0; k < 4; ++k) CHECK(r8(*m, work + psm::kRgba + k) == to[k] / 2);
        // the dummy task: done (-1) once the model reports ready
        w32(*m, task + scn::task::kWork, model);
        Opt ready;
        ready.setup = [](StandInWorld& w) {
            scene2_world(w);
            w.si.install_recorder(0x316F70u, "sub_316F70 (model ready)", 1);
        };
        CHECK(v0u(spair(*m, "fclMisc_UpdatePsModelDummyTask", {sx(task)}, seed++, "dummy ready", ready)) == 0xFFFFFFFFu);
        CHECK(v0u(spair(*m, "fclMisc_UpdatePsModelDummyTask", {sx(task)}, seed++, "dummy waiting")) == 0u);
    }
}

TEST_CASE("game(scene2): pair summary") {
    MESSAGE("pairs: " << g_pairs);
    for (const auto& [where, n] : g_stops) MESSAGE("  stopped " << n << " x: " << where);
}

#else

TEST_CASE("game(scene2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
