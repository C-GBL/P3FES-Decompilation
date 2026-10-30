// Pair tests for slice field3, part `event` (game/src/field/field3_event.cpp): every body against its recompiled body.
//   1. The p3fes_handgen skeleton: every function on random worlds (tests/game/handgen_pairs.h: the whole register file
//      and cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the
//      bus log).
//   2. Field worlds built from the real layouts (26_field.md; game/src/field/field3_event.cpp names them): the party /
//      shadow field units (448 bytes) with models (RwMatrix first: at +32, position +48; flags +312), DatUnit holders
//      and DatUnits, the bucket table 0x86B180, the treasure boxes 0x86BE80, the special object 0x86E580, the scene
//      record (gp-22448 -> 0x95AFC0) and its type-3 NPC list, the collision record sField +4460, an encounter task in
//      0x875A40, sField's exit table. Paired with tests/game/stand_ins.h (run_pair_si: the whole RAM write-tracked,
//      every GPR in 128 bits, HI/LO, the register file at every check point, the dead stack, the stand-ins' call logs
//      and heaps): the heap behind the RW slots; RpCollisionWorldForAllIntersections 0x464020 stood in by a
//      deterministic "wall" (a ray crossing x = wall is blocked) so the hand-written collision ray sub_1ACC30 answers
//      both ways; the clump walk 0x4916D0 and what the (hand-written, since 2c463df) model band's sub_3182D0 calls
//      without an emitted body -- sub_314850, sub_3138E0, sub_31EF80 -- recorded; the models carry an animation set so
//      the look-at / animation functions run for real. The float arguments ($f12 / $f13) are set by a wrapper both
//      bodies share.
//   3. Documented rules on the recompiled run's output: the field-of-view window, the nearest-member choice, the
//      battle packet's near / far split at 2000, the "member near the hero" test, the after-battle placement spots,
//      the record reset, the task creation and the frees.
//   4. Real data: the Tartarus climb snapshots (climb_ref_17000 / climb_ref_39820: field 51/4, two party members, five
//      / two NPCs), the finders and the packet builder on the snapshot's own units; skipped when absent.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field3_event.h"

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

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define F3EV_DECL(name, addr) void fn_##name##_##addr(EEContext&); void fn_##name##_##addr##__recomp(EEContext&);
P3FES_FIELD3_EVENT_BODIES(F3EV_DECL)
#undef F3EV_DECL
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
#define F3EV_CASE(name, addr) {#name, 0x##addr##u, &rg::fn_##name##_##addr, &rg::fn_##name##_##addr##__recomp},
    P3FES_FIELD3_EVENT_BODIES(F3EV_CASE)
#undef F3EV_CASE
};

// The skeleton's world: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

// --- guest helpers -----------------------------------------------------------------------------------------------
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
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }
u32 v0_of(const SiPair& p) { return static_cast<u32>(p.hw.recomp.base.v0); }

// The float arguments: both bodies of a pair run through the same wrapper, which sets $f12 / $f13 first.
u32 g_f12 = 0, g_f13 = 0;
template <Fn F>
void with_f(EEContext& c) {
    c.fpr[12] = g_f12;
    c.fpr[13] = g_f13;
    F(c);
}
#define HAND(name, addr) &with_f<&rg::fn_##name##_##addr>
#define RECOMP(name, addr) &with_f<&rg::fn_##name##_##addr##__recomp>

// --- the field world ---------------------------------------------------------------------------------------------
constexpr u32 kPcUnits = 0x8717A0u, kEcUnits = 0x86EDA0u, kUnitSize = 448u;
constexpr u32 kBuckets = 0x86B180u, kBucketsSize = 3136u;
constexpr u32 kBoxes = 0x86BE80u, kBoxSize = 312u, kBoxCount = 32u;
constexpr u32 kSpecial = 0x86E580u;
constexpr u32 kSceneSlot = 0x7CD540u, kScene = 0x95AFC0u;
constexpr u32 kSField = 0x869F60u;
constexpr u32 kKosakaSlots = 0x875A40u;
constexpr u32 kModelSlots = 0x871EA0u;
// the world's blocks
// 40 models x 0x400: RwMatrix (at +32, position +48), the bone matrix +64.. (sub_3182D0 copies an animation entry's
// 64 bytes there), anim id s16 +240, anim set +280 ({entries, u16 count +4}; 80-byte entries, +64 nonzero = usable),
// flags u16 +312, look-at target f32[3] +372 (sub_3190B0), +860 / +948.. / +1016 zero (no extra sets, no children)
constexpr u32 kModels = 0x01840000u;
constexpr u32 kModelStride = 0x400u;
constexpr u32 kModelsEnd = kModels + 40u * kModelStride;
constexpr u32 kAnimSet = 0x0181E700u, kAnimEntries = 0x0181E800u, kAnimCount = 12u;
constexpr u32 kHolders = 0x01818000u;     // 32 x 0x20: {u16 kind, u16 1, DatUnit*, ..., u16 flags +10}
constexpr u32 kDatUnits = 0x01819000u;    // 32 x 0x40: u16 id +2, u16 hp +8, u32 flags +12
constexpr u32 kNpcs = 0x0181A000u;        // 12 x 0x200: scene resources, next +248, model +296
constexpr u32 kResMgr = 0x0181E000u;      // the scene's resource manager: list heads by type
constexpr u32 kCollRec = 0x0181E100u;     // the collision record: word 0 bit 0 = world, +12 the world
constexpr u32 kTask = 0x0181E200u, kTaskWork = 0x0181E300u;  // an encounter ("battle kosaka") task and its work
constexpr u32 kPacket = 0x0181E400u;      // the 52-byte battle packet
constexpr u32 kBusyTask = 0x0181E500u, kBusyWork = 0x0181E600u;  // what sub_43A230 reads through unit +364
constexpr u32 kFakeWorld = 0x01830000u;   // the collision world handle (only passed to the stand-in)
constexpr u32 kWorldEnd = 0x01831000u;

constexpr u32 kCollideWorld = 0x464020u;  // RpCollisionWorldForAllIntersections(world, line, callback, data)
constexpr u32 kClumpAtomics = 0x4916D0u;  // RpClumpForAllAtomics (the mesh path of sub_1ACC30)
// The model band (game/replaced.txt since 2c463df: sub_3190B0 look-at, sub_318540 anim id, sub_3182D0 set anim run
// hand-written); what sub_3182D0 calls and this build does not emit is recorded: the motion start sub_314850, the
// layer's track set sub_3138E0 (its first argument = model +236, the second = the new id), sub_31EF80 (not reached).
constexpr u32 kMotionStart = 0x314850u, kTrackSet = 0x3138E0u, kExtraSet = 0x31EF80u;

float g_wall = 1e30f;  // the stand-in wall: a ray whose ends lie on both sides of x = g_wall is blocked

struct Pos {
    float x, y, z;
};
u32 model_of(u32 i) { return kModels + kModelStride * i; }
u32 pc(u32 i) { return kPcUnits + kUnitSize * i; }
u32 ec(u32 i) { return kEcUnits + kUnitSize * i; }
Pos model_pos(Machine& m, u32 model) { return {getf(m, model + 48), getf(m, model + 52), getf(m, model + 56)}; }
float dist(Pos a, Pos b) { return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)); }

// A model: the matrix rows (right, up, at), the position; heading `yaw` (at = (sin, 0, cos)).
void make_model(Machine& m, u32 model, Pos p, float yaw, std::mt19937& rng) {
    std::memset(m.at(model), 0, kModelStride);
    const float s = std::sin(yaw), c = std::cos(yaw);
    putf(m, model + 0, c);
    putf(m, model + 8, -s);
    putf(m, model + 20, 1.0f);
    putf(m, model + 32, s);
    putf(m, model + 36, chance(rng, 20) ? frand(rng, -0.2f, 0.2f) : 0.0f);
    putf(m, model + 40, c);
    putf(m, model + 48, p.x);
    putf(m, model + 52, p.y);
    putf(m, model + 56, p.z);
    put16(m, model + 312, static_cast<u16>(rng() & 0x0F0F));
    put16(m, model + 240, static_cast<u16>(chance(rng, 80) ? rng() % 13 : rng()));  // the current animation id
    put32(m, model + 280, chance(rng, 85) ? kAnimSet : 0u);                          // without a set: id -1
}

// The animation set every model shares: 12 entries of 80 bytes, distinct contents, +64 nonzero.
void make_anim_set(Machine& m, std::mt19937& rng) {
    put32(m, kAnimSet, kAnimEntries);
    put16(m, kAnimSet + 4, static_cast<u16>(kAnimCount));
    const u32 sentinel = get32(m, 0x9571D0u);  // sub_3182D0 refuses an entry whose +64 equals this word
    for (u32 i = 0; i < kAnimCount; ++i) {
        const u32 e = kAnimEntries + 80u * i;
        for (u32 off = 0; off < 80; off += 4) put32(m, e + off, rng());
        u32 w64 = 0x01826000u + 16u * i;
        if (w64 == sentinel) w64 += 4;
        put32(m, e + 64, w64);
    }
}

// The scene record and its lists.
void set_scene(Machine& m, u32 major, u32 minor) {
    put32(m, kSceneSlot, kScene);
    put32(m, kScene + 0, major);
    put32(m, kScene + 4, minor);
    put32(m, kScene + 8, kResMgr);
}

struct World {
    Pos hero{};
    u32 n_pc = 0, n_ec = 0;
};

// A field: the hero (party unit 0) and up to three members, up to `max_ec` shadows in the hero's bucket, boxes, the
// special object, NPCs; positions around the hero within `spread`.
World build_world(Machine& m, std::mt19937& rng, bool random_floor, float spread, u32 max_ec = 8) {
    World w;
    std::memset(m.at(kPcUnits), 0, 4 * kUnitSize);
    std::memset(m.at(kEcUnits), 0, 24 * kUnitSize);
    std::memset(m.at(kBuckets), 0, kBucketsSize);
    std::memset(m.at(kBoxes), 0, kBoxSize * kBoxCount);
    std::memset(m.at(kSpecial), 0, 280);
    std::memset(m.at(kKosakaSlots), 0, 12);
    std::memset(m.at(kHolders), 0, kWorldEnd - kHolders);
    std::memset(m.at(kModels), 0, kModelsEnd - kModels);
    make_anim_set(m, rng);
    if (random_floor) set_scene(m, 21 + rng() % 7, 0);
    else {
        static const u32 kFields[][2] = {{51, 4}, {51, 1}, {7, 2}, {26, 51}, {32, 2}, {8, 3}};
        const auto& f = kFields[rng() % 6];
        set_scene(m, f[0], f[1]);
    }
    // the collision record: the RW world path (bit 0) with a world, so the ray reaches the wall stand-in
    put32(m, kSField + 4460, kCollRec);
    put32(m, kCollRec, 1);
    put32(m, kCollRec + 12, chance(rng, 90) ? kFakeWorld : 0u);
    g_wall = chance(rng, 50) ? 1e30f : 0.0f;
    // the hero inside one 4 x 4-cell bucket on random floors (cells of 800, buckets of 3200)
    w.hero = {frand(rng, 400.0f, 12000.0f), frand(rng, -50.0f, 50.0f), frand(rng, 400.0f, 12000.0f)};
    auto near_hero = [&](float r) {
        const float a = frand(rng, 0.0f, 6.2831f), d = frand(rng, 0.0f, r);
        return Pos{w.hero.x + d * std::sin(a), w.hero.y + frand(rng, -30.0f, 30.0f), w.hero.z + d * std::cos(a)};
    };
    if (g_wall < 1e29f) g_wall = w.hero.x + frand(rng, -spread, spread);
    u32 model = 0;
    // party units 0..3
    w.n_pc = 1 + rng() % 4;
    for (u32 i = 0; i < 4; ++i) {
        const u32 u = pc(i);
        const Pos p = i == 0 ? w.hero : near_hero(spread);
        putf(m, u + 48, i == 0 ? w.hero.x : p.x + frand(rng, -5.0f, 5.0f));  // the stored position (+48)
        putf(m, u + 52, p.y);
        putf(m, u + 56, i == 0 ? w.hero.z : p.z + frand(rng, -5.0f, 5.0f));
        put16(m, u + 424, static_cast<u16>(i == 0 ? 1 : 1 + rng() % 10));
        if (i >= w.n_pc && !chance(rng, 10)) continue;
        const u32 holder = kHolders + 0x20 * i, dat = kDatUnits + 0x40 * i;
        put16(m, holder + 0, 0);
        put16(m, holder + 2, 1);
        put32(m, holder + 4, dat);
        put16(m, holder + 10, static_cast<u16>(rng() & 0xFFFF));
        put16(m, dat + 2, get16(m, u + 424));
        put16(m, dat + 8, static_cast<u16>(chance(rng, 20) ? 0 : 1 + rng() % 300));
        put32(m, dat + 12, chance(rng, 10) ? 0x80000u : 0u);
        put32(m, u + 72, holder);
        make_model(m, model_of(model), p, frand(rng, -3.2f, 3.2f), rng);
        put32(m, u + 80, model_of(model++));
        if (chance(rng, 15)) {  // sub_43A230: unit +84 set and +364 -> task -> work: byte +1 == 5, +4632 in {3, 6}
            put32(m, u + 84, 1);
            put32(m, u + 364, kBusyTask);
            put32(m, kBusyTask + 60, kBusyWork);
            m.at(kBusyWork + 1)[0] = chance(rng, 70) ? 5 : 4;
            m.at(kBusyWork + 4632)[0] = chance(rng, 70) ? 3 : 6;
        }
    }
    // shadows, listed in the hero's bucket (random floors) or bucket (0, 0)
    u32 bucket = kBuckets;
    if (random_floor) {
        const int bx = static_cast<int>((w.hero.x + 400.0f) / 800.0f) / 4, bz = static_cast<int>((w.hero.z + 400.0f) / 800.0f) / 4;
        bucket = kBuckets + 4u * (196u * static_cast<u32>(bz) + 49u * static_cast<u32>(bx));
    }
    w.n_ec = rng() % (max_ec + 1);
    for (u32 i = 0; i < w.n_ec; ++i) {
        const u32 u = ec(i);
        const Pos p = near_hero(spread);
        putf(m, u + 48, p.x);
        putf(m, u + 52, p.y);
        putf(m, u + 56, p.z);
        if (!chance(rng, 10)) put32(m, u + 72, kHolders + 0x200 + 0x10 * i);
        make_model(m, model_of(model), p, frand(rng, -3.2f, 3.2f), rng);
        put32(m, u + 80, model_of(model++));
        put32(m, bucket + 4 * i, u);
    }
    // treasure boxes: live ones listed in the bucket's box words
    u32 nb = 0;
    for (u32 i = 0; i < kBoxCount; ++i) {
        if (!chance(rng, 15)) continue;
        const u32 b = kBoxes + kBoxSize * i;
        const Pos p = near_hero(spread);
        put32(m, b, chance(rng, 85) ? 1u : 0u);
        putf(m, b + 268, p.x);
        putf(m, b + 272, p.y);
        putf(m, b + 276, p.z);
        if (nb < 20) put32(m, bucket + 96 + 4 * nb++, b);
    }
    if (chance(rng, 40)) {
        const Pos p = near_hero(spread);
        put32(m, kSpecial, chance(rng, 80) ? 1u : 2u);
        putf(m, kSpecial + 260, p.x);
        putf(m, kSpecial + 264, p.y);
        putf(m, kSpecial + 268, p.z);
    }
    // NPCs: a type-3 list
    const u32 n_npc = rng() % 7;
    put32(m, kResMgr + 4 * 3, n_npc ? kNpcs : 0u);
    for (u32 i = 0; i < n_npc; ++i) {
        const u32 r = kNpcs + 0x200 * i;
        put32(m, r + 248, i + 1 < n_npc ? r + 0x200 : 0u);
        make_model(m, model_of(model), near_hero(chance(rng, 50) ? 250.0f : spread), frand(rng, -3.2f, 3.2f), rng);
        put32(m, r + 296, model_of(model++));
    }
    return w;
}

WorldSetup field_setup(Machine& m) {
    return [&m](StandInWorld& w) {
        install_standard(w);
        w.si.install(kCollideWorld, "RpCollisionWorldForAllIntersections", [&m](EEContext&, StandIns&, StandInCall& c) {
            const u32 line = static_cast<u32>(c.args[1]), data = static_cast<u32>(c.args[3]);
            const float sx = getf(m, line), ex = getf(m, line + 12);
            if ((sx - g_wall) * (ex - g_wall) < 0.0f) put32(m, data + 4, 1);  // blocked: the hit count sub_1ACC30 returns
            c.v0 = c.args[0];
        });
        w.si.install_recorder(kClumpAtomics, "RpClumpForAllAtomics");
        w.si.install_recorder(kMotionStart, "sub_314850");
        w.si.install_recorder(kTrackSet, "sub_3138E0");
        w.si.install_recorder(kExtraSet, "sub_31EF80");
    };
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

std::unique_ptr<Machine> fresh_machine() {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    write_rw_slots(*m);
    return m;
}
#define NEED_MACHINE()                                    \
    std::unique_ptr<Machine> mp = fresh_machine();        \
    if (!mp) {                                            \
        MESSAGE("SKIP: no ELF at " << elf_path());        \
        return;                                           \
    }                                                     \
    Machine& m = *mp

// The host's reading of sub_1C6200: heading of v = acos(v.z / |v|) in degrees, negated for v.x < 0, + 180.
float heading(float x, float y, float z) {
    const float n = std::sqrt(x * x + y * y + z * z);
    float h = std::acos(std::fmax(-1.0f, std::fmin(1.0f, z / n))) * 57.2957795f;
    if (x / n < 0.0f) h = -h;
    return h + 180.0f;
}
// 1 inside, 0 outside, -1 when too close to a window edge to decide on the host.
int fov_rule(float h, float d, float fov) {
    const float half = fov / 2.0f, lo = h - half, hi = h + half;
    auto near_edge = [&](float e) { return std::fabs(d - e) < 0.05f; };
    if (near_edge(lo) || near_edge(hi) || near_edge(lo + 360.0f) || near_edge(hi - 360.0f)) return -1;
    if (hi <= 360.0f) {
        if (lo >= 0.0f) return lo <= d && d <= hi;
        return d <= hi || d >= lo + 360.0f;
    }
    return d >= lo || d <= hi - 360.0f;
}

}  // namespace

TEST_CASE("game(field3_event): every body equals its recompiled body on random worlds") {
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

// sub_1C6200 on models of every heading against points all around; sub_1C6450 adds the range and the two rays.
TEST_CASE("game(field3_event): the field-of-view test and the sight test") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3E0001u};
    int inside = 0, outside = 0, decided = 0, seen = 0, blocked = 0, pairs = 0;
    for (int i = 0; i < 260; ++i) {
        build_world(m, rng, chance(rng, 50), 1500.0f, 0);
        const u32 model = model_of(39);
        const Pos p{frand(rng, -2000.0f, 2000.0f), frand(rng, -40.0f, 40.0f), frand(rng, -2000.0f, 2000.0f)};
        make_model(m, model, p, frand(rng, -3.2f, 3.2f), rng);
        const u32 pt = kWorldEnd - 0x100;
        const Pos q = chance(rng, 5) ? p : Pos{p.x + frand(rng, -1500.0f, 1500.0f), p.y + frand(rng, -40.0f, 40.0f), p.z + frand(rng, -1500.0f, 1500.0f)};
        putf(m, pt, q.x);
        putf(m, pt + 4, q.y);
        putf(m, pt + 8, q.z);
        const float fov = chance(rng, 10) ? (chance(rng, 50) ? 0.0f : 360.0f) : frand(rng, 10.0f, 300.0f);
        const float range = frand(rng, 100.0f, 2500.0f);
        if (chance(rng, 40)) g_wall = (p.x + q.x) / 2.0f;  // a wall between the eye and the point
        g_f12 = fbits(fov);
        g_f13 = fbits(range);
        {
            const SiPair r = run_pair_si(m, HAND(sub_1C6200, 001c6200), RECOMP(sub_1C6200, 001c6200), {model, pt, 0, 0}, rng(),
                                         "sub_1C6200", hw, field_setup(m));
            ++pairs;
            const float h = heading(getf(m, model + 32), getf(m, model + 36), getf(m, model + 40));
            const float d = heading(q.x - p.x, q.y - p.y, q.z - p.z);
            const int rule = (q.x == p.x && q.z == p.z) ? -1 : fov_rule(h, d, fov);
            if (rule >= 0) {
                CHECK(v0_of(r) == static_cast<u32>(rule));
                ++decided;
            }
            (v0_of(r) ? inside : outside)++;
        }
        {
            const SiPair r = run_pair_si(m, HAND(sub_1C6450, 001c6450), RECOMP(sub_1C6450, 001c6450), {model, pt, 0, 0}, rng(),
                                         "sub_1C6450", hw, field_setup(m));
            ++pairs;
            if (v0_of(r)) {
                ++seen;
                // seen: inside the range, and no wall between the two ends
                CHECK(dist(p, q) < range + 0.01f);
                CHECK(!((p.x - g_wall) * (q.x - g_wall) < 0.0f && get32(m, kCollRec + 12) != 0));
            } else if ((p.x - g_wall) * (q.x - g_wall) < 0.0f) {
                ++blocked;
            }
        }
    }
    MESSAGE("pairs " << pairs << ": FOV inside " << inside << ", outside " << outside << " (" << decided << " checked on the host); seen "
                     << seen << ", blocked " << blocked);
    CHECK(inside > 40);
    CHECK(outside > 40);
    CHECK(decided > 150);
    CHECK(seen > 10);
    CHECK(blocked > 10);
}

// The finders over the hero's bucket and the party, with the distance helpers.
TEST_CASE("game(field3_event): the finders over the bucket and the party") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3E0002u};
    int found_vis = 0, found_fov = 0, found_pc = 0, found_box = 0, near = 0, pairs = 0;
    for (int i = 0; i < 150; ++i) {
        const World w = build_world(m, rng, chance(rng, 60), chance(rng, 50) ? 600.0f : 2500.0f);
        const u32 hero = pc(0);
        const float range = chance(rng, 10) ? 0.0f : frand(rng, 50.0f, 3000.0f);
        const float fov = frand(rng, 30.0f, 240.0f);
        // sub_1C6720 / sub_1C6A20: the hero (or a member) against the bucket
        const u32 who = chance(rng, 80) ? hero : pc(rng() % 4);
        g_f12 = fbits(range);
        g_f13 = fbits(fov);
        {
            const SiPair r = run_pair_si(m, HAND(sub_1C6720, 001c6720), RECOMP(sub_1C6720, 001c6720), {who, 0, 0, 0}, rng(),
                                         "sub_1C6720", hw, field_setup(m));
            ++pairs;
            if (const u32 u = v0_of(r)) {
                ++found_vis;
                CHECK(get32(m, u + 72) != 0);
                CHECK(dist(model_pos(m, get32(m, u + 80)), model_pos(m, get32(m, who + 80))) < range);
            }
        }
        if (get32(m, who + 80) != 0) {
            const SiPair r = run_pair_si(m, HAND(sub_1C6A20, 001c6a20), RECOMP(sub_1C6A20, 001c6a20), {who, 0, 0, 0}, rng(),
                                         "sub_1C6A20", hw, field_setup(m));
            ++pairs;
            if (v0_of(r)) ++found_fov;
        }
        // sub_1C6DD0 / sub_1C6D70: the nearest living party member other than the unit (host rule below)
        {
            const SiPair r = run_pair_si(m, HAND(sub_1C6DD0, 001c6dd0), RECOMP(sub_1C6DD0, 001c6dd0), {sx(who), 0, 0, 0}, rng(),
                                         "sub_1C6DD0", hw, field_setup(m));
            ++pairs;
            const s32 got = static_cast<s32>(v0_of(r));
            if (get32(m, who + 80) != 0) {
                s32 want = -1;
                float best = 3.4e38f, second = 3.4e38f;
                for (u32 k = 0; k < 4; ++k) {
                    const u32 u = pc(k);
                    if (u == who || get32(m, u + 72) == 0) continue;
                    const u32 dat = get32(m, get32(m, u + 72) + 4);
                    if ((get32(m, dat + 12) & 0x80000u) != 0 || get16(m, dat + 8) == 0) continue;
                    const float d = dist(model_pos(m, get32(m, u + 80)), model_pos(m, get32(m, who + 80)));
                    if (d < range && d < best) {
                        second = best;
                        best = d;
                        want = static_cast<s32>(k);
                    } else if (d < range && d < second) {
                        second = d;
                    }
                }
                if (std::fabs(best - range) > 0.01f && std::fabs(second - best) > 0.01f) CHECK(got == want);
                if (got >= 0) ++found_pc;
            }
        }
        if (get32(m, who + 80) != 0) {
            const SiPair r = run_pair_si(m, HAND(sub_1C6D70, 001c6d70), RECOMP(sub_1C6D70, 001c6d70), {sx(who), 0, 0, 0}, rng(),
                                         "sub_1C6D70", hw, field_setup(m));
            ++pairs;
            const u32 u = v0_of(r);
            CHECK((u == 0 || (u >= kPcUnits && u < kPcUnits + 4 * kUnitSize && (u - kPcUnits) % kUnitSize == 0)));
            g_f12 = fbits(fov);
            g_f13 = fbits(range);
            run_pair_si(m, HAND(sub_1C6F50, 001c6f50), RECOMP(sub_1C6F50, 001c6f50), {sx(who), 0, 0, 0}, rng(), "sub_1C6F50", hw,
                        field_setup(m));
            ++pairs;
            g_f12 = fbits(range);
        }
        // sub_1C7160 / sub_1C71F0: two units / two points
        {
            const u32 a = chance(rng, 50) ? pc(rng() % 4) : ec(rng() % 4), b = chance(rng, 50) ? pc(rng() % 4) : ec(rng() % 4);
            const SiPair r = run_pair_si(m, HAND(sub_1C7160, 001c7160), RECOMP(sub_1C7160, 001c7160), {a, b, 0, 0}, rng(),
                                         "sub_1C7160", hw, field_setup(m));
            ++pairs;
            if (get32(m, a + 72) == 0 || get32(m, b + 72) == 0) CHECK(v0_of(r) == 0);
            else {
                const float d = dist(model_pos(m, get32(m, a + 80)), model_pos(m, get32(m, b + 80)));
                if (std::fabs(d - range) > 0.01f) CHECK(v0_of(r) == (d < range ? 1u : 0u));
                if (v0_of(r)) ++near;
            }
        }
        // sub_1C7270: the first live box of the bucket within the range
        if (get32(m, who + 80) != 0) {
            const SiPair r = run_pair_si(m, HAND(sub_1C7270, 001c7270), RECOMP(sub_1C7270, 001c7270), {who, 0, 0, 0}, rng(),
                                         "sub_1C7270", hw, field_setup(m));
            ++pairs;
            if (const u32 b = v0_of(r)) {
                ++found_box;
                CHECK(get32(m, b) != 0);
                CHECK(dist({getf(m, b + 268), getf(m, b + 272), getf(m, b + 276)}, model_pos(m, get32(m, who + 80))) < range);
            }
        }
        (void)w;
    }
    MESSAGE("pairs " << pairs << ": visible unit " << found_vis << ", in FOV " << found_fov << ", party member " << found_pc << ", box "
                     << found_box << ", units near " << near);
    CHECK(found_vis > 10);
    CHECK(found_pc > 10);
    CHECK(found_box > 5);
    CHECK(near > 5);
}

// sub_1C74C0 on the NPC list (look-at, animation pairs in field 7) and sub_1C7CE0 (a member near the hero).
TEST_CASE("game(field3_event): the NPC finder and the member-near-hero test") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3E0003u};
    int npc = 0, looks = 0, anims = 0, near = 0, pairs = 0;
    for (int i = 0; i < 160; ++i) {
        build_world(m, rng, false, 1200.0f);
        if (chance(rng, 40)) set_scene(m, 7, 1 + rng() % 4);
        {
            const SiPair r = run_pair_si(m, &rg::fn_sub_1C74C0_001c74c0, &rg::fn_sub_1C74C0_001c74c0__recomp, {0, 0, 0, 0}, rng(),
                                         "sub_1C74C0", hw, field_setup(m));
            ++pairs;
            const StandIns& si = r.recomp->si;
            // the look-ats (the hand-written sub_3190B0): target +372 = the hero's head (position + 140 up), flag 0x40
            const Pos hp = model_pos(m, get32(m, pc(0) + 80));
            const Pos head{hp.x, hp.y + 140.0f, hp.z};
            int looked = 0;
            for (u32 n = get32(m, kResMgr + 12); n != 0; n = get32(m, n + 248)) {
                const u32 model = get32(m, n + 296);
                // (y within an ulp or so: the EE FPU's add rounds toward zero, the host's to nearest)
                if (getf(m, model + 372) == head.x && std::fabs(getf(m, model + 376) - head.y) < 0.01f && getf(m, model + 380) == head.z) {
                    ++looked;
                    CHECK(dist(hp, model_pos(m, model)) < 200.0f);
                    CHECK((get16(m, model + 312) & 0x1140u) == 0x1040u);  // 0x40 and 0x1000 set, 0x100 clear
                }
            }
            looks += looked;
            if (const u32 res = v0_of(r)) {
                ++npc;
                // the rule: in reach (< 200) of the hero, in the 120-degree view; the first NPC looking at the hero
                const u32 model = get32(m, res + 296);
                CHECK(dist(hp, model_pos(m, model)) < 200.0f);
                CHECK(getf(m, model + 372) == head.x);
                CHECK(std::fabs(getf(m, model + 376) - head.y) < 0.01f);
                CHECK((get16(m, model + 312) & 0x1000u) != 0);
                CHECK(looked >= 1);
            } else {
                CHECK(looked == 0);
            }
            // the animation pairs (field 7; the hand-written sub_318540 / sub_3182D0): each change copies the new
            // entry's 64 bytes to the model's +64 and hands model +236 and the new id to sub_3138E0
            for (const StandInCall& c : si.log) {
                if (c.va != kTrackSet) continue;
                ++anims;
                CHECK(get32(m, kScene) == 7);
                const u32 model = static_cast<u32>(c.args[0]) - 236u;
                const s32 old_id = static_cast<s16>(get16(m, model + 240)), new_id = static_cast<s16>(c.args[1]);
                CHECK(old_id >= 4);
                CHECK(new_id == ((old_id & 1) == 0 ? old_id + 1 : old_id - 1));
                if (new_id >= 0 && new_id < static_cast<s32>(kAnimCount))
                    CHECK(std::memcmp(m.at(model + 64), m.at(kAnimEntries + 80u * static_cast<u32>(new_id)), 64) == 0);
            }
            if (get32(m, kScene) != 7) CHECK(si.calls_to(kMotionStart) == 0);
        }
        {
            const u32 id = chance(rng, 70) ? get16(m, pc(rng() % 4) + 424) : rng() % 12;
            const SiPair r = run_pair_si(m, &rg::fn_sub_1C7CE0_001c7ce0, &rg::fn_sub_1C7CE0_001c7ce0__recomp, {id, 0, 0, 0}, rng(),
                                         "sub_1C7CE0", hw, field_setup(m));
            ++pairs;
            const u32 major = get32(m, kScene), minor = get32(m, kScene + 4);
            bool want = (major == 26 && minor >= 51 && minor <= 53) || (major == 32 && minor == 2);
            bool edge = false;
            for (u32 k = 0; k < 4; ++k) {
                const u32 u = pc(k);
                if (get32(m, u + 72) == 0 || get16(m, u + 424) != id) continue;
                const float d = dist({getf(m, u + 48), getf(m, u + 52), getf(m, u + 56)}, {getf(m, pc(0) + 48), getf(m, pc(0) + 52), getf(m, pc(0) + 56)});
                edge |= std::fabs(d - 1600.0f) < 0.01f;
                want |= d < 1600.0f;
            }
            if (!edge) CHECK(v0_of(r) == (want ? 1u : 0u));
            if (v0_of(r)) ++near;
        }
    }
    MESSAGE("pairs " << pairs << ": NPC found " << npc << " (" << looks << " look-ats, " << anims << " animation changes), member near "
                     << near);
    CHECK(npc > 20);
    CHECK(anims > 5);
    CHECK(near > 20);
}

// sub_1C7830: the battle packet's party half (near / far split at 2000, the encounter task's members, sub_43A230).
// sub_1C8120: the far members that fought placed next to the hero on random floors.
TEST_CASE("game(field3_event): the battle packet and the after-battle placement") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3E0004u};
    int far = 0, nearc = 0, in_task = 0, placed = 0, pairs = 0;
    for (int i = 0; i < 200; ++i) {
        build_world(m, rng, chance(rng, 70), chance(rng, 50) ? 1500.0f : 4000.0f, 4);
        const u32 enemy = ec(0);
        put32(m, enemy + 72, kHolders + 0x300);
        // sometimes the shadow is in an encounter task with some of the members
        if (chance(rng, 35)) {
            put32(m, kKosakaSlots + 4 * (rng() % 3), kTask);
            put32(m, kTask + 60, kTaskWork);
            const u32 np = 1 + rng() % 3;
            put32(m, kTaskWork + 16, np);
            for (u32 k = 0; k < np; ++k) put32(m, kTaskWork + 24 + 4 * k, pc(1 + rng() % 3));
            put32(m, kTaskWork + 20, 1);
            put32(m, kTaskWork + 40, enemy);
            ++in_task;
        }
        std::memset(m.at(kPacket), 0xA5, 52);
        const SiPair r = run_pair_si(m, &rg::fn_sub_1C7830_001c7830, &rg::fn_sub_1C7830_001c7830__recomp, {kPacket, sx(enemy), 0, 0},
                                     rng(), "sub_1C7830", hw, field_setup(m));
        ++pairs;
        // the rules: +4 the hero's holder, +20 the shadow's instance, +0 / +24 / +26 zero; near members' holders from
        // +8 with flag bit 0 set, far ones {holder, distance >= 2000} from +28 with bit 0 clear
        CHECK(get32(m, kPacket + 0) == 0);
        CHECK(get32(m, kPacket + 4) == get32(m, pc(0) + 72));
        CHECK(get32(m, kPacket + 20) == get32(m, enemy + 72));
        CHECK(get32(m, kPacket + 24) == 0);
        const bool f51_1 = get32(m, kScene) == 51 && get32(m, kScene + 4) == 1;
        for (u32 k = 0; k < 3; ++k) {
            if (const u32 h = get32(m, kPacket + 8 + 4 * k)) {
                CHECK((get16(m, h + 10) & 1u) == 1u);
                ++nearc;
            }
            if (const u32 h = get32(m, kPacket + 28 + 8 * k)) {
                CHECK((get16(m, h + 10) & 1u) == 0u);
                CHECK(getf(m, kPacket + 32 + 8 * k) >= 2000.0f);
                CHECK(!f51_1);
                ++far;
            }
        }
        // sub_1C8120 on the same packet: mark some far holders as having fought
        for (u32 k = 0; k < 3; ++k)
            if (const u32 h = get32(m, kPacket + 28 + 8 * k))
                if (chance(rng, 70)) put16(m, h + 10, static_cast<u16>(get16(m, h + 10) | 1u));
        Pos before[4];
        for (u32 k = 0; k < 4; ++k) before[k] = {getf(m, pc(k) + 48), getf(m, pc(k) + 52), getf(m, pc(k) + 56)};
        run_pair_si(m, &rg::fn_sub_1C8120_001c8120, &rg::fn_sub_1C8120_001c8120__recomp, {kPacket, 0, 0, 0}, rng(), "sub_1C8120", hw,
                    field_setup(m));
        ++pairs;
        // the rule: a moved member stands on one of the five spots around the hero's cell centre at the hero's height
        const float hx = getf(m, pc(0) + 48), hy = getf(m, pc(0) + 52), hz = getf(m, pc(0) + 56);
        const float cx = 800.0f * static_cast<float>(static_cast<int>((hx + 400.0f) / 800.0f));
        const float cz = 800.0f * static_cast<float>(static_cast<int>((hz + 400.0f) / 800.0f));
        for (u32 k = 1; k < 4; ++k) {
            const Pos now{getf(m, pc(k) + 48), getf(m, pc(k) + 52), getf(m, pc(k) + 56)};
            if (now.x == before[k].x && now.y == before[k].y && now.z == before[k].z) continue;
            ++placed;
            CHECK(now.y == hy);
            const float dx = now.x - cx, dz = now.z - cz;
            const bool spot = (dx == 0.0f && dz == 0.0f) || (std::fabs(std::fabs(dx) - 250.0f) < 0.01f && std::fabs(std::fabs(dz) - 250.0f) < 0.01f);
            // (the fallback "spot 5" -- the stack words after the table, when all five are taken -- never comes up here)
            CHECK(spot);
        }
    }
    MESSAGE("pairs " << pairs << ": near holders " << nearc << ", far " << far << ", encounter tasks " << in_task << ", members placed "
                     << placed);
    CHECK(nearc > 50);
    CHECK(far > 30);
    CHECK(placed > 10);
}

// The record reset, the exit table's free, the task creation and their destroy callbacks.
TEST_CASE("game(field3_event): the record reset, the frees and the task creation") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3E0005u};
    int pairs = 0;
    for (int i = 0; i < 24; ++i) {
        // sub_1CD7A0: every record cleared
        build_world(m, rng, true, 2000.0f);
        put32(m, 0x7CE28Cu, rng());
        put32(m, 0x7CE288u, rng());
        for (u32 off = 0; off < 32; off += 4) put32(m, kModelSlots + off, rng());
        run_pair_si(m, &rg::fn_sub_1CD7A0_001cd7a0, &rg::fn_sub_1CD7A0_001cd7a0__recomp, {0, 0, 0, 0}, rng(), "sub_1CD7A0", hw,
                    field_setup(m));
        ++pairs;
        for (u32 va : {kPcUnits, kPcUnits + 1788u, kEcUnits, kEcUnits + 10748u, kBuckets, kBuckets + 3132u, kBoxes, kBoxes + 9980u,
                       kSpecial, kSpecial + 276u, kModelSlots, 0x86BDC0u, 0x7CE28Cu, 0x7CE288u, 0x7CE284u, 0x7CE280u})
            CHECK(get32(m, va) == 0);
        // sub_1C80C0: a table in a heap block (the first block of each body's fresh stand-in heap) is freed
        const bool has_table = chance(rng, 75);
        put32(m, kSField + 4424, has_table ? kStandInHeap : 0u);
        put32(m, kSField + 4420, 1 + rng() % 9);
        const SiPair f = run_pair_si(m, &rg::fn_sub_1C80C0_001c80c0, &rg::fn_sub_1C80C0_001c80c0__recomp, {0, 0, 0, 0}, rng(),
                                     "sub_1C80C0", hw, [&m](StandInWorld& w) {
                                         field_setup(m)(w);
                                         w.heap.alloc(9 * 44);
                                     });
        ++pairs;
        CHECK(get32(m, kSField + 4424) == 0);
        if (has_table) {
            CHECK(get32(m, kSField + 4420) == 0);
            CHECK(f.recomp->heap.live().empty());
            CHECK(f.recomp->heap.bad_frees == 0);
        }
        // K_FldEvent_CreateTasks: the "field event" task with a 288-byte work and its "draw command" child (+92)
        const u32 parent = 0;
        const SiPair c = run_pair_si(m, &rg::fn_K_FldEvent_CreateTasks_001cd5a0, &rg::fn_K_FldEvent_CreateTasks_001cd5a0__recomp,
                                     {parent, 0, 0, 0}, rng(), "K_FldEvent_CreateTasks", hw, field_setup(m));
        ++pairs;
        const u32 task = v0_of(c);
        if (task != 0) {
            const u32 work = get32(m, task + 60);
            CHECK(c.recomp->heap.size_of(work) >= 288);
            const u32 draw = get32(m, work + 92);
            CHECK(draw != 0);
            if (draw != 0) {
                CHECK(c.recomp->heap.size_of(get32(m, draw + 60)) >= 4);
                // the destroy callbacks (RwFree(task +60); on a fresh stand-in heap the block is not live: a bad free,
                // counted alike in both runs)
                run_pair_si(m, &rg::fn_sub_1CD6E0_001cd6e0, &rg::fn_sub_1CD6E0_001cd6e0__recomp, {draw, 0, 0, 0}, rng(), "sub_1CD6E0", hw,
                            field_setup(m));
                run_pair_si(m, &rg::fn_sub_1CD570_001cd570, &rg::fn_sub_1CD570_001cd570__recomp, {task, 0, 0, 0}, rng(), "sub_1CD570", hw,
                            field_setup(m));
                pairs += 2;
            }
        }
        run_pair_si(m, &rg::fn_sub_1CD710_001cd710, &rg::fn_sub_1CD710_001cd710__recomp, {parent, 0, 0, 0}, rng(), "sub_1CD710", hw,
                    field_setup(m));
        ++pairs;
    }
    MESSAGE("pairs " << pairs);
}

// The finders and the packet builder on the Tartarus climb's own units (field 51/4: the hero and one member live).
TEST_CASE("game(field3_event): the finders on the climb snapshots") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xF3E0006u};
    int pairs = 0;
    for (const char* dir : {"climb_ref_17000", "climb_ref_39820"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        std::memcpy(m.at(0), snap.data(), snap.size());
        write_rw_slots(m);
        REQUIRE(get32(m, pc(0) + 72) != 0);
        const u32 member = pc(1);
        for (int i = 0; i < 6; ++i) {
            const float range = i == 0 ? 3.0e4f : frand(rng, 50.0f, 4000.0f);
            g_f12 = fbits(range);
            g_f13 = fbits(frand(rng, 60.0f, 360.0f));
            g_wall = 1e30f;
            const SiPair a = run_pair_si(m, HAND(sub_1C6DD0, 001c6dd0), RECOMP(sub_1C6DD0, 001c6dd0), {sx(pc(0)), 0, 0, 0}, rng(),
                                         "sub_1C6DD0 snapshot", hw, field_setup(m));
            // the rule: the only other live member is party unit 1, at its model's distance from the hero's
            const float d = dist(model_pos(m, get32(m, member + 80)), model_pos(m, get32(m, pc(0) + 80)));
            const u32 holder = get32(m, member + 72), dat = get32(m, holder + 4);
            const bool dead = (get32(m, dat + 12) & 0x80000u) != 0 || get16(m, dat + 8) == 0;  // datCalcIsDead
            if (get16(m, holder) != 1 && std::fabs(d - range) > 0.01f) CHECK(static_cast<s32>(v0_of(a)) == (d < range && !dead ? 1 : -1));
            run_pair_si(m, HAND(sub_1C6D70, 001c6d70), RECOMP(sub_1C6D70, 001c6d70), {sx(member), 0, 0, 0}, rng(), "sub_1C6D70 snapshot",
                        hw, field_setup(m));
            run_pair_si(m, HAND(sub_1C6720, 001c6720), RECOMP(sub_1C6720, 001c6720), {pc(0), 0, 0, 0}, rng(), "sub_1C6720 snapshot", hw,
                        field_setup(m));
            run_pair_si(m, HAND(sub_1C6A20, 001c6a20), RECOMP(sub_1C6A20, 001c6a20), {pc(0), 0, 0, 0}, rng(), "sub_1C6A20 snapshot", hw,
                        field_setup(m));
            run_pair_si(m, HAND(sub_1C7270, 001c7270), RECOMP(sub_1C7270, 001c7270), {pc(0), 0, 0, 0}, rng(), "sub_1C7270 snapshot", hw,
                        field_setup(m));
            run_pair_si(m, &rg::fn_sub_1C74C0_001c74c0, &rg::fn_sub_1C74C0_001c74c0__recomp, {0, 0, 0, 0}, rng(), "sub_1C74C0 snapshot", hw,
                        field_setup(m));
            const SiPair n = run_pair_si(m, &rg::fn_sub_1C7CE0_001c7ce0, &rg::fn_sub_1C7CE0_001c7ce0__recomp, {2, 0, 0, 0}, rng(),
                                         "sub_1C7CE0 snapshot", hw, field_setup(m));
            // member id 2 stands 214 from the hero's stored position in both snapshots: near
            CHECK(v0_of(n) == 1);
            pairs += 7;
        }
        // the packet: a live party member as the "shadow" (the snapshots hold no live shadow)
        const u32 pkt = kArena;
        const SiPair p = run_pair_si(m, &rg::fn_sub_1C7830_001c7830, &rg::fn_sub_1C7830_001c7830__recomp, {pkt, sx(member), 0, 0}, rng(),
                                     "sub_1C7830 snapshot", hw, field_setup(m));
        ++pairs;
        CHECK(get32(m, pkt + 4) == get32(m, pc(0) + 72));
        CHECK(get32(m, pkt + 20) == get32(m, member + 72));
        (void)p;
    }
    MESSAGE("snapshot pairs " << pairs);
}

#else

TEST_CASE("game(field3_event): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
