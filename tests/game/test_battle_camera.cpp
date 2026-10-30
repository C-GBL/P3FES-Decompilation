// Phase 5 pair tests for slice battle_camera (game/src/battle/battle_camera*.cpp): every hand-written body of the battle
// camera band and the recompiled body it replaces run on identical guest machines -- a random battle world (gBtl, the
// btlAction / btlUnit objects and their side lists, a SKILL.TBL stand-in, camera objects, packet data blocks, floats and
// pointers everywhere) and a random register file (GPRs in 128 bits, FPRs) -- and must leave the same:
//   * whole register file (GPRs in 128 bits, HI/LO, SA, FPRs, FCR31) and cycle count at EVERY check point, in order
//     (a check point may preempt the thread and the kernel then saves the full register file in guest memory);
//   * whole register file and cycle count at the return -- or, when a callee is not emitted in this build, at the
//     missing-function stop (same function, same arguments, same $ra / $sp / everything);
//   * the whole 32 MiB of main RAM (compared through a PairRange: only the pages a body writes are copied).
// The RW heap hook the packet allocator sub_27EC10 calls (0x960178) is served by the emitted leaf sub_4B3710
// (`jr ra; move v0, a1`): every packet is built at 0x40000 (as in test_battle_actions.cpp). A second test case runs
// the bodies on the battle route's snapshots (extracted/_ours/{b_5800,battle_ref_6150,b_6300}/eeMemory.bin: the live
// gBtl, its camera record and units), and a third checks documented rules on the host.
#include "battle_camera_harness.h"

#include "p3fes/game/battle_camera_1.h"
#include "p3fes/game/battle_camera_2.h"
#include "p3fes/game/battle_camera_3.h"
#include "p3fes/game/battle_camera_4.h"
#include "p3fes/game/battle_camera_5.h"

#include <cmath>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::bcam_test;

namespace p3fes::recomp_gen {
P3FES_BCAM_BODIES(P3FES_BCAM_DECL_PAIR)
P3FES_BCAM_BODIES_1(P3FES_BCAM_DECL_PAIR)
P3FES_BCAM_BODIES_2(P3FES_BCAM_DECL_PAIR)
P3FES_BCAM_BODIES_3(P3FES_BCAM_DECL_PAIR)
P3FES_BCAM_BODIES_4(P3FES_BCAM_DECL_PAIR)
P3FES_BCAM_BODIES_5(P3FES_BCAM_DECL_PAIR)
}  // namespace p3fes::recomp_gen

namespace {

// --- the camera set layer's world ----------------------------------------------------------------------------------
constexpr u32 kSkillAttr = kWorld + 0x1B000u;   // *(gp-18672): 256 x 28-byte skill attribute records
constexpr u32 kPersonaTbl = kWorld + 0x1D000u;  // *(gp-18628): 32 x 88-byte records
constexpr u32 kDats = kWorld + 0x1E000u;        // DatUnits for the units (+2604), 64 bytes apart
constexpr u32 kPersonas = kWorld + 0x1E400u;    // unit sub-objects (+2560), 0x40 apart
// A unit quaternion (x, y, z, w) at va: a turn about the up axis, sometimes any.
void quat(Machine& m, std::mt19937& rng, u32 va) {
    float q[4];
    if (chance(rng, 70)) {
        const float h = frand(rng, -3.1416f, 3.1416f) * 0.5f;
        q[0] = 0.0f;
        q[1] = std::sin(h);
        q[2] = 0.0f;
        q[3] = std::cos(h);
    } else {
        float n = 0.0f;
        for (float& x : q) {
            x = frand(rng, -1.0f, 1.0f);
            n += x * x;
        }
        n = std::sqrt(n) + 1e-6f;
        for (float& x : q) x /= n;
    }
    for (int k = 0; k < 4; ++k) storef(m, va + 4 * k, q[k]);
}
// A camera key at va: a position (sometimes beyond the arena limit 1500) and a rotation.
void key(Machine& m, std::mt19937& rng, u32 va) {
    const float r = chance(rng, 30) ? 3000.0f : 800.0f;
    storef(m, va + 0, frand(rng, -r, r));
    storef(m, va + 4, frand(rng, -50.0f, 200.0f));
    storef(m, va + 8, chance(rng, 10) ? 1500.0f : frand(rng, -r, r));
    quat(m, rng, va + 12);
}
// The tables, the units' DatUnits / sub-objects / geometry, a terminated btlAction list (gBtl+332 along +1192) and the
// camera fields of gBtl.
void cam_world(Machine& m, const World& w, std::mt19937& rng) {
    store32(m, kGp - 18672u, kSkillAttr);
    for (u32 k = 0; k < 256; ++k) store16(m, kSkillAttr + 28 * k + 2, static_cast<u16>(rng() & 0x4031u));
    store32(m, kGp - 18628u, kPersonaTbl);
    for (u32 k = 0; k < 32; ++k) store16(m, kPersonaTbl + 88 * k, static_cast<u16>(rng() & 1u));
    for (u32 i = 0; i < kNumUnits; ++i) {
        const u32 u = w.units[i];
        store32(m, u + 2604, kDats + 64 * i);
        store32(m, u + 2560, chance(rng, 50) ? 0u : kPersonas + 0x40 * i);
        store16(m, kPersonas + 0x40 * i + 164, static_cast<u16>(rng() % 32));
        store32(m, u + 156, chance(rng, 70) ? (rng() | 8u) : (rng() & ~8u));
        storef(m, u + 144, frand(rng, 0.5f, 3.0f));
        storef(m, u + 44, frand(rng, 5.0f, 40.0f));
        store32(m, u + 152, rng());
        m.at(u + 51)[0] = static_cast<u8>(chance(rng, 80) ? 1 + rng() % 200 : 0);
    }
    std::array<u32, kNumActions> order = w.actions;
    std::shuffle(order.begin(), order.end(), rng);
    const u32 n = chance(rng, 10) ? 0u : 1 + rng() % kNumActions;
    store32(m, kG + 332, n ? order[0] : 0u);
    for (u32 i = 0; i < kNumActions; ++i) {
        const u32 a = order[i];
        store32(m, a + 1192, i + 1 < n ? order[i + 1] : 0u);
        store16(m, a + 26, static_cast<u16>(rng() & (chance(rng, 80) ? 0xFFFFu : 0xFFFEu)));
        store16(m, a + 108, static_cast<u16>(rng() % 5));
        store16(m, a + 110, static_cast<u16>(rng() % 256));
        store16(m, a + 114, static_cast<u16>(rng() % 256));
        store16(m, a + 106, static_cast<u16>(rng() % 5));
        if (chance(rng, 10)) store32(m, a + 56, 0u);
    }
    store32(m, kG + 328, w.actions[rng() % kNumActions]);
    store32(m, kG + 16, rng() & ~(chance(rng, 90) ? 0x4u : 0u));
    store16(m, kG + 240, static_cast<u16>(chance(rng, 30) ? 12u : rng() % 37));
    store32(m, kG + 256, chance(rng, 20) ? 0u : w.actions[rng() % kNumActions]);
    store32(m, kG + 288, chance(rng, 20) ? 0u : w.actions[rng() % kNumActions]);
}
// The record helpers (sub_2A32F0 .. sub_2A3850): $a0 = the camera work record with a subject (or none).
Inputs gen_record(Machine& m, const World& w, std::mt19937& rng) {
    cam_world(m, w, rng);
    Inputs in;
    store32(m, kCamWork + 224, chance(rng, 10) ? 0u : w.actions[rng() % kNumActions]);
    in.gpr[GPR_A0] = wide(rng, kCamWork);
    return in;
}
// sub_2A3590(key, out or 0)
Inputs gen_clamp(Machine& m, const World&, std::mt19937& rng) {
    Inputs in;
    const u32 k = some_data(rng);
    key(m, rng, k);
    in.gpr[GPR_A0] = wide(rng, k);
    in.gpr[GPR_A1] = chance(rng, 20) ? 0u : wide(rng, some_data(rng));
    return in;
}
// sub_2A3750(record, unit or 0)
Inputs gen_strike(Machine& m, const World& w, std::mt19937& rng) {
    cam_world(m, w, rng);
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, kCamWork);
    in.gpr[GPR_A1] = chance(rng, 10) ? 0u : wide(rng, w.units[rng() % kNumUnits]);
    return in;
}
// sub_2A38F0(id, subject, hide): a camera table row (or a wild one), a subject, the hide flag; and the record set up as
// the rows' inits read it.
Inputs gen_switch(Machine& m, const World& w, std::mt19937& rng) {
    cam_world(m, w, rng);
    Inputs in;
    fill_floats(m, rng, kCamWork, 0xC0, -100.0f, 100.0f);
    key(m, rng, kCamWork + 156);
    store16(m, kCamWork + 116, static_cast<u16>(rng() % 4));
    store16(m, kCamWork + 118, static_cast<u16>(rng() % 5));
    store16(m, kCamWork + 120, static_cast<u16>(rng() % 4));
    store32(m, kCamWork + 152, 0u);
    const u32 id = chance(rng, 30) ? load16(m, kG + 240) : rng() % 37;
    in.gpr[GPR_A0] = wide(rng, chance(rng, 3) ? rng() : id);
    in.gpr[GPR_A1] = wide(rng, chance(rng, 10) ? 0u : w.actions[rng() % kNumActions]);
    in.gpr[GPR_A2] = wide(rng, rng() % 2);
    return in;
}
// sub_2A3A90(action): sometimes the subject / parameter of gBtl itself
Inputs gen_forget(Machine& m, const World& w, std::mt19937& rng) {
    cam_world(m, w, rng);
    Inputs in;
    const u32 pick = rng() % 3;
    in.gpr[GPR_A0] = wide(rng, pick == 0 ? load32(m, kG + 256) : pick == 1 ? load32(m, kG + 288) : w.actions[rng() % kNumActions]);
    if (in.gpr[GPR_A0] == 0) in.gpr[GPR_A0] = w.actions[0];
    return in;
}
// sub_2A3B00(data: +0 subject, +4 id) / sub_2A3BA0(data: +0 subject, +4/+16/+28/+40 points, +52 seconds, +56 flag)
Inputs gen_switch_data(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in = gen_switch(m, w, rng);
    const u32 d = some_data(rng);
    store32(m, d + 0, static_cast<u32>(in.gpr[GPR_A1]));
    store16(m, d + 4, static_cast<u16>(in.gpr[GPR_A0]));
    in.gpr[GPR_A0] = wide(rng, d);
    return in;
}
Inputs gen_move_data(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in = gen_switch(m, w, rng);
    const u32 d = some_data(rng);
    store32(m, d + 0, static_cast<u32>(in.gpr[GPR_A1]));
    fill_floats(m, rng, d + 4, 48, -500.0f, 500.0f);
    storef(m, d + 52, frand(rng, 0.1f, 3.0f));
    store32(m, d + 56, chance(rng, 40) ? 1u : 0u);
    in.gpr[GPR_A0] = wide(rng, d);
    return in;
}
// sub_2A3D70(subject, eye0, at0, eye1, at1; $f12)
Inputs gen_move(Machine& m, const World& w, std::mt19937& rng) {
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, w.actions[rng() % kNumActions]);
    for (unsigned r : {GPR_A1, GPR_A2, GPR_A3, GPR_T0}) {
        const u32 d = some_data(rng);
        fill_floats(m, rng, d, 12, -500.0f, 500.0f);
        in.gpr[r] = (r == GPR_A1 || r == GPR_A2) && chance(rng, 25) ? 0u : wide(rng, d);
    }
    in.fpr[12] = fbits(frand(rng, 0.1f, 3.0f));
    return in;
}
// sub_2A3E80(subject or 0, eye or 0, at or 0, flags; $f12 distance)
Inputs gen_show(Machine& m, const World& w, std::mt19937& rng) {
    cam_world(m, w, rng);
    Inputs in;
    in.gpr[GPR_A0] = chance(rng, 15) ? 0u : wide(rng, w.actions[rng() % kNumActions]);
    for (unsigned r : {GPR_A1, GPR_A2}) {
        const u32 d = some_data(rng);
        fill_floats(m, rng, d, 12, -300.0f, 300.0f);
        in.gpr[r] = chance(rng, 15) ? 0u : wide(rng, d);
    }
    in.gpr[GPR_A3] = wide(rng, rng() & (chance(rng, 50) ? 0xBFu : 0xFFu));
    in.fpr[12] = fbits(frand(rng, -50.0f, 400.0f));
    return in;
}
// no arguments: the world only
Inputs gen_world(Machine& m, const World& w, std::mt19937& rng) {
    cam_world(m, w, rng);
    return Inputs{};
}
// sub_2A4470 / 44B0 / 44F0(dst, src)
Inputs gen_copy(Machine& m, const World&, std::mt19937& rng) {
    Inputs in;
    const u32 s = some_data(rng);
    key(m, rng, s);
    in.gpr[GPR_A0] = wide(rng, some_data(rng));
    in.gpr[GPR_A1] = wide(rng, s);
    return in;
}
// sub_2A4530(out, at, eye, up) / sub_2A4690(out, eye, at, up): the up axis is mostly (0, 1, 0) at 0x697880
Inputs gen_look(Machine& m, const World&, std::mt19937& rng) {
    Inputs in;
    in.gpr[GPR_A0] = wide(rng, some_data(rng));
    for (unsigned r : {GPR_A1, GPR_A2}) {
        const u32 d = some_data(rng);
        fill_floats(m, rng, d, 12, -300.0f, 300.0f);
        in.gpr[r] = wide(rng, d);
    }
    if (chance(rng, 70)) {
        in.gpr[GPR_A3] = sx(0x697880u);
    } else {
        const u32 d = some_data(rng);
        fill_floats(m, rng, d, 12, -1.0f, 1.0f);
        in.gpr[GPR_A3] = wide(rng, d);
    }
    return in;
}

const Spec kSpecs[] = {
    {"sub_2A0050", PAIR(sub_2A0050, 002a0050), gen_creator},
    {"sub_2A1080", PAIR(sub_2A1080, 002a1080), gen_creator},
    {"sub_2A10E0", PAIR(sub_2A10E0, 002a10e0), [](Machine& m, const World& w, std::mt19937& rng) { return gen_fade_data(m, w, rng, 32, 36); }},
    {"sub_2A1280", PAIR(sub_2A1280, 002a1280), gen_creator},
    {"sub_2A1400", PAIR(sub_2A1400, 002a1400), [](Machine& m, const World& w, std::mt19937& rng) { return gen_fade_data(m, w, rng, 16, 20); }},
    {"sub_2A16C0", PAIR(sub_2A16C0, 002a16c0), gen_creator},
    {"sub_2A1710", PAIR(sub_2A1710, 002a1710), gen_unit_fade},
    {"sub_2A1B00", PAIR(sub_2A1B00, 002a1b00), gen_creator},
    {"sub_2A1B70", PAIR(sub_2A1B70, 002a1b70), gen_unit_fade_in},
    {"sub_2A1DB0", PAIR(sub_2A1DB0, 002a1db0), gen_creator},
    {"sub_2A32F0", PAIR(sub_2A32F0, 002a32f0), gen_record},
    {"sub_2A3380", PAIR(sub_2A3380, 002a3380), gen_record},
    {"sub_2A3420", PAIR(sub_2A3420, 002a3420), gen_record},
    {"sub_2A3520", PAIR(sub_2A3520, 002a3520), gen_record},
    {"sub_2A3550", PAIR(sub_2A3550, 002a3550), gen_record},
    {"sub_2A3590", PAIR(sub_2A3590, 002a3590), gen_clamp},
    {"sub_2A3750", PAIR(sub_2A3750, 002a3750), gen_strike},
    {"sub_2A3820", PAIR(sub_2A3820, 002a3820), gen_record},
    {"sub_2A3850", PAIR(sub_2A3850, 002a3850), gen_record},
    {"sub_2A38F0", PAIR(sub_2A38F0, 002a38f0), gen_switch},
    {"sub_2A3A80", PAIR(sub_2A3A80, 002a3a80), gen_world},
    {"sub_2A3A90", PAIR(sub_2A3A90, 002a3a90), gen_forget},
    {"sub_2A3B00", PAIR(sub_2A3B00, 002a3b00), gen_switch_data},
    {"sub_2A3B40", PAIR(sub_2A3B40, 002a3b40), gen_creator},
    {"sub_2A3BA0", PAIR(sub_2A3BA0, 002a3ba0), gen_move_data},
    {"sub_2A3D70", PAIR(sub_2A3D70, 002a3d70), gen_move},
    {"sub_2A3E80", PAIR(sub_2A3E80, 002a3e80), gen_show},
    {"sub_2A42A0", PAIR(sub_2A42A0, 002a42a0), gen_world},
    {"sub_2A4330", PAIR(sub_2A4330, 002a4330), gen_world},
    {"sub_2A4470", PAIR(sub_2A4470, 002a4470), gen_copy},
    {"sub_2A44B0", PAIR(sub_2A44B0, 002a44b0), gen_copy},
    {"sub_2A44F0", PAIR(sub_2A44F0, 002a44f0), gen_copy},
    {"sub_2A4530", PAIR(sub_2A4530, 002a4530), gen_look},
    {"sub_2A4690", PAIR(sub_2A4690, 002a4690), gen_look},
    {"sub_2A4C50", PAIR(sub_2A4C50, 002a4c50), gen_world},
};

}  // namespace

TEST_CASE("game(battle_camera): every replaced body equals its recompiled body on random battle worlds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
#ifdef NDEBUG
    constexpr int kWorlds = 400;
#else
    constexpr int kWorlds = 120;
#endif
    run_specs(m, std::vector<Spec>(std::begin(kSpecs), std::end(kSpecs)), kWorlds, 0xBCA0u, "battle_camera");
}

namespace {

// --- every function of the slice by address (the snapshot pairs pick the camera table's rows) ---------------------
struct Entry {
    const char* name;
    Fn hand;
    Fn recomp;
};
const std::map<u32, Entry>& by_address() {
#define P3FES_BCAM_ENTRY(name, addr) {0x##addr##u, {#name, &recomp_gen::fn_##name##_##addr, &recomp_gen::fn_##name##_##addr##__recomp}},
    static const std::map<u32, Entry> all = {
        P3FES_BCAM_BODIES(P3FES_BCAM_ENTRY) P3FES_BCAM_BODIES_1(P3FES_BCAM_ENTRY) P3FES_BCAM_BODIES_2(P3FES_BCAM_ENTRY)
        P3FES_BCAM_BODIES_3(P3FES_BCAM_ENTRY) P3FES_BCAM_BODIES_4(P3FES_BCAM_ENTRY) P3FES_BCAM_BODIES_5(P3FES_BCAM_ENTRY)};
#undef P3FES_BCAM_ENTRY
    return all;
}

std::vector<u8> read_snapshot(const char* dir) {
    const std::filesystem::path p =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    std::vector<u8> v((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return v.size() == EEMemory::kMainRamSize ? v : std::vector<u8>{};
}

constexpr u32 kCamTable = 0x6939F0u;  // 37 x 20-byte rows {init, update, flag, flag, name}
constexpr u32 kCamRows = 37;

}  // namespace

// The battle route's snapshots (the battle in progress at 5800, the result screen's lead-in at 6150 / 6300: the live
// gBtl, its camera work record gBtl+32 with its key ring, the units, the RW engine): every camera row's init and update
// of the slice with $a0 = gBtl+32, and the camera switch sub_2A38F0 to every row (its init runs through the table's
// jalr), each from the snapshot's bytes, with $a1 / $a2 = 0 / 1. The RW heap stays the game's (the allocator is not
// emitted in this build: a packet allocation is a compared missing-function stop).
TEST_CASE("game(battle_camera): the camera rows and the camera switch on the battle route's snapshots") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    g_stats.clear();
    int ran = 0;
    std::mt19937 rng{0x5A9Bu};
    for (const char* dir : {"b_5800", "battle_ref_6150", "b_6300"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found beside the ELF's tree");
            continue;
        }
        INFO(dir);
        std::memcpy(m.at(0), snap.data(), snap.size());
        const u32 gbtl = load32(m, kGBtlSlot);
        if (gbtl == 0 || gbtl >= EEMemory::kMainRamSize) {
            MESSAGE("SKIP: " << dir << ": no battle (gBtl = " << hex64(gbtl) << ")");
            continue;
        }
        const auto& all = by_address();
        for (u32 row = 0; row < kCamRows; ++row) {
            for (u32 col = 0; col < 3; ++col) {
                const u32 fn = col < 2 ? load32(m, kCamTable + 20 * row + 4 * col) : 0x2A38F0u;
                const auto it = all.find(fn);
                if (it == all.end()) continue;
                for (u32 variant = 0; variant < 4; ++variant) {
                    std::memcpy(m.at(0), snap.data(), snap.size());
                    Inputs in;
                    in.gpr[GPR_A0] = sx(col < 2 ? gbtl + 32 : row);
                    in.gpr[GPR_A1] = variant & 1;
                    in.gpr[GPR_A2] = variant >> 1;
                    in.gpr[GPR_A3] = 0;
                    for (unsigned f = 12; f < 16; ++f) in.fpr[f] = fbits(frand(rng, 0.0f, 1.5f));
                    const std::string what = std::string(dir) + " " + it->second.name + (col == 2 ? " row" : "");
                    const Run r = pair(m, it->second.hand, it->second.recomp, in, rng(), it->second.name);
                    ++ran;
                    // the documented rule of the switch: a returned switch leaves gBtl+240 = the row
                    if (col == 2 && !r.stopped) CHECK(load16(m, gbtl + 240) == row);
                }
            }
        }
    }
    MESSAGE("snapshot pairs: " << ran << "; " << report());
}

// Documented rules (battle_camera.cpp / battle_camera_4.cpp), checked on the host after each pair (the recompiled
// run's output is in place): the screen-fade creator's data block, the key ring push and the current-camera getter.
TEST_CASE("game(battle_camera): the documented rules (fade packet, key ring push, current camera)") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    g_stats.clear();
    std::mt19937 rng{0xD0C5u};
    int fades = 0, pushes = 0, full = 0, ids = 0;
    for (int it = 0; it < 300; ++it) {
        const World w = random_world(m, rng);
        (void)w;
        // sub_2A1280(rgba, frames): data +4k = byte k / 255, +32 = frames
        {
            const u32 rgba = rng(), frames = rng() % 100;
            Inputs in;
            in.gpr[GPR_A0] = sx(rgba);
            in.gpr[GPR_A1] = sx(frames);
            const Run r = pair(m, PAIR(sub_2A1280, 002a1280), in, rng(), "rule sub_2A1280");
            if (!r.stopped) {
                const u32 data = load32(m, kPacketBuf + bc::kPktData);
                for (u32 k = 0; k < 4; ++k) CHECK(std::fabs(loadf(m, data + 4 * k) - ((rgba >> (8 * k)) & 0xFF) / 255.0f) < 1e-5f);
                CHECK(load32(m, data + 32) == frames);
                CHECK(load32(m, kPacketBuf + bc::kPktCallback) == 0x2A10E0u);
                ++fades;
            }
        }
        // sub_2A2050(camera, position, rotation): a full ring (+118 >= 4) returns 0 and is left alone; otherwise the key
        // goes to slot +120 (28-byte keys from +4), +120 advances mod 4, +118 counts it, the result is 1
        {
            const u32 cam = some_data(rng);
            const u32 pos = some_data(rng), rot = some_data(rng);
            fill_floats(m, rng, pos, 16, -10.0f, 10.0f);
            fill_floats(m, rng, rot, 16, -1.0f, 1.0f);
            const u16 count = static_cast<u16>(rng() % 6), slot = static_cast<u16>(rng() % 4);
            store16(m, cam + 0, static_cast<u16>(load16(m, cam) | 1));  // no RwFrame update
            store16(m, cam + 118, count);
            store16(m, cam + 120, slot);
            Inputs in;
            in.gpr[GPR_A0] = sx(cam);
            in.gpr[GPR_A1] = sx(pos);
            in.gpr[GPR_A2] = sx(rot);
            const Run r = pair(m, PAIR(sub_2A2050, 002a2050), in, rng(), "rule sub_2A2050");
            if (!r.stopped) {
                if (count >= 4) {
                    CHECK(r.end.gpr[GPR_V0].u64[0] == 0);
                    CHECK(load16(m, cam + 118) == count);
                    ++full;
                } else {
                    CHECK(r.end.gpr[GPR_V0].u64[0] == 1);
                    CHECK(load16(m, cam + 118) == count + 1);
                    CHECK(load16(m, cam + 120) == (slot + 1) % 4);
                    for (u32 k = 0; k < 3; ++k) CHECK(load32(m, cam + 4 + 28 * slot + 4 * k) == load32(m, pos + 4 * k));
                    for (u32 k = 0; k < 4; ++k) CHECK(load32(m, cam + 16 + 28 * slot + 4 * k) == load32(m, rot + 4 * k));
                    ++pushes;
                }
            }
        }
        // sub_2A3A80(): the current camera id gBtl+240
        {
            store16(m, kG + 240, static_cast<u16>(rng() % 40));
            const Run r = pair(m, PAIR(sub_2A3A80, 002a3a80), Inputs{}, rng(), "rule sub_2A3A80");
            CHECK(r.end.gpr[GPR_V0].u64[0] == load16(m, kG + 240));
            ++ids;
        }
    }
    MESSAGE("rules: " << fades << " fade packets, " << pushes << " ring pushes, " << full << " full rings, " << ids << " camera ids");
    CHECK(fades > 200);
    CHECK(pushes > 100);
    CHECK(full > 30);
}

#else
TEST_CASE("game(battle_camera): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
