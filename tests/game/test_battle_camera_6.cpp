// Phase 5 pair tests for slice battle_camera, part 6 (game/src/battle/battle_camera_6.cpp): the camera object's set-up
// sub_2A4A70 (RwMalloc / RwFree), its tear-down sub_2A4C20 and the debug marker sub_2A48F0 -- the band's heap users --
// and, again, the scene fade callback sub_2A0440 (battle_camera_4.cpp) past its sub_19F8F0 calls, all on the stand-in
// world (tests/game/stand_ins.h: the guest heap behind the RW memory slots; recorders for the callees this build does
// not emit: the RW camera / object functions, the ambient-light setter, the debug draw). Every pair compares the whole
// RAM (write-tracked), the scratchpad, every GPR in 128 bits, HI/LO, the register file and cycles at every check
// point, the dead stack, the stand-ins' call logs and the heaps' live blocks; documented rules are checked on the
// recompiled run's output. The fade callback also runs on the battle route's snapshots (b_5800, battle_ref_6150).
#include <doctest.h>

#include "stand_ins.h"

#include "p3fes/game/battle_camera_6.h"

#include <cmath>
#include <cstring>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
#define BC6_DECL(name, addr) void fn_##name##_##addr(p3fes::EEContext&); void fn_##name##_##addr##__recomp(p3fes::EEContext&);
P3FES_BCAM_BODIES_6(BC6_DECL)
BC6_DECL(sub_2A0440, 002a0440)
#undef BC6_DECL
}  // namespace p3fes::recomp_gen

namespace p3fes::game_test {
namespace {

namespace rg = p3fes::recomp_gen;

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
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }

// the battle world: gBtl at kG (the slot gp-18692), units and models after it
constexpr u32 kGBtlSlot = 0x7CE3ECu;
constexpr u32 kG = 0x01810000u;
constexpr u32 kUnits = kG + 0x2000u;  // 8 x 0xB00
constexpr u32 kModels = kG + 0x8000u; // 8 x 0x400
constexpr u32 kData = kG + 0xA000u;   // the fade packet's data block
constexpr u32 kWorldSize = 0xC000u;

// the callees not emitted in this build: recorders (the RW camera settings, the RW object create / destroy, the
// ambient light, the debug draw)
constexpr u32 kCamSetA = 0x4C9D70u, kCamSetB = 0x1A4580u, kObjCreate = 0x48DAB0u, kObjDestroy = 0x48DA30u;
constexpr u32 kAmbientSet = 0x19F8F0u, kDebugSphere = 0x358A30u, kDebugAxes = 0x359380u;
constexpr u32 kObjHandle = 0x01830000u;  // what the object-create recorder returns

void random_world(Machine& m, std::mt19937& rng) {
    std::memset(m.at(kG), 0, kWorldSize);
    for (u32 off = 0; off < kWorldSize; off += 4)
        if (chance(rng, 40)) putf(m, kG + off, frand(rng, -2.0f, 2.0f));
    put32(m, kGBtlSlot, kG);
    // the four btlUnit lists gBtl+336 + 8k (along +2612): 0..3 units each
    u32 next = 0;
    for (u32 k = 0; k < 4; ++k) {
        const u32 n = rng() % 3;
        u32 prev = 0;
        put32(m, kG + 336 + 8 * k, 0);
        for (u32 i = 0; i < n && next < 8; ++i, ++next) {
            const u32 u = kUnits + 0xB00u * next;
            if (prev == 0) put32(m, kG + 336 + 8 * k, u);
            else put32(m, prev + 2612, u);
            put32(m, u + 2612, 0);
            put32(m, u + 152, chance(rng, 60) ? (rng() | 2u) : (rng() & ~2u));
            const u32 model = kModels + 0x400u * next;
            put32(m, u + 2548, model);
            for (u32 b = 56; b < 64; ++b) m.at(u + b)[0] = static_cast<u8>(rng());
            for (u32 off = 96; off < 128; off += 4) putf(m, u + off, frand(rng, 0.0f, 1.0f));
            m.at(model + 904)[0] = static_cast<u8>(rng());
            m.at(model + 936)[0] = static_cast<u8>(rng());
            putf(m, model + 928, frand(rng, 0.0f, 1.2f));
            prev = u;
        }
    }
}

WorldSetup with_recorders() {
    return [](StandInWorld& w) {
        install_standard(w);
        w.si.install_recorder(kCamSetA, "sub_4C9D70");
        w.si.install_recorder(kCamSetB, "sub_1A4580");
        w.si.install_recorder(kObjCreate, "sub_48DAB0", kObjHandle);
        w.si.install_recorder(kObjDestroy, "sub_48DA30");
        w.si.install_recorder(kAmbientSet, "sub_19F8F0");
        w.si.install_recorder(kDebugSphere, "sub_358A30");
        w.si.install_recorder(kDebugAxes, "sub_359380");
    };
}

float gpf(Machine& m, s32 off) { return getf(m, kGp + static_cast<u32>(off)); }

}  // namespace

TEST_CASE("game(battle_camera_6): the camera object's set-up on the stand-in heap") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xBC6001u};
    int pairs = 0;
    for (int i = 0; i < 120; ++i) {
        random_world(m, rng);
        const SiPair p = run_pair_si(m, rg::fn_sub_2A4A70_002a4a70, rg::fn_sub_2A4A70_002a4a70__recomp,
                                     {rng(), rng(), rng(), rng()}, rng(), "sub_2A4A70", hw, with_recorders());
        ++pairs;
        // the rules: RwMalloc(48, 0x40000) -> the template handed to sub_48DAB0(4, 1, template), freed again; the object
        // in +152; the ring reset; the default key; no current row; the history cleared; gBtl+244 bit 1
        const StandIns& si = p.recomp->si;
        CHECK(si.calls_to(kObjCreate) == 1);
        CHECK(si.calls_to(kCamSetA) == 1);
        CHECK(si.calls_to(kCamSetB) == 1);
        for (const StandInCall& c : si.log)
            if (c.va == kObjCreate) {
                CHECK(c.args[0] == 4);
                CHECK(c.args[1] == 1);
            }
        CHECK(p.recomp->heap.live().empty());
        CHECK(get32(m, kG + 184) == kObjHandle);
        CHECK(get16(m, kG + 32) == 1);
        CHECK(get16(m, kG + 148) == 0);
        CHECK(get16(m, kG + 150) == 0);
        CHECK(get16(m, kG + 152) == 0);
        CHECK(getf(m, kG + 188) == gpf(m, -32164));
        CHECK(getf(m, kG + 212) == gpf(m, -32180));
        CHECK(getf(m, kG + 216) == gpf(m, -32440));
        CHECK(get16(m, kG + 240) == 0);
        for (u32 k = 0; k < 3; ++k) CHECK(get16(m, kG + 260 + 2 * k) == 0);
        CHECK((get32(m, kG + 244) & 2u) == 2u);
    }
    MESSAGE("sub_2A4A70: " << pairs << " pairs");
}

TEST_CASE("game(battle_camera_6): the tear-down and the debug marker") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xBC6002u};
    int destroyed = 0, drawn = 0, pairs = 0;
    for (int i = 0; i < 200; ++i) {
        random_world(m, rng);
        // sub_2A4C20: the object +152 (gBtl+184) destroyed when there is one
        const u32 obj = chance(rng, 30) ? 0u : kObjHandle + 16u * (rng() % 16);
        put32(m, kG + 184, obj);
        {
            const SiPair p = run_pair_si(m, rg::fn_sub_2A4C20_002a4c20, rg::fn_sub_2A4C20_002a4c20__recomp,
                                         {rng(), rng(), rng(), rng()}, rng(), "sub_2A4C20", hw, with_recorders());
            ++pairs;
            const StandIns& si = p.recomp->si;
            CHECK(si.calls_to(kObjDestroy) == (obj != 0 ? 1u : 0u));
            if (obj != 0 && si.calls_to(kObjDestroy) == 1) {
                CHECK(si.log[0].args[0] == obj);
                ++destroyed;
            }
        }
        // sub_2A48F0: drawn only with gBtl+12 bit 2 clear, gBtl+20 bit 2 clear and bit 3 set
        u32 f12 = rng(), f20 = rng();
        if (chance(rng, 70)) f12 &= ~4u;
        if (chance(rng, 70)) f20 = (f20 & ~4u) | 8u;
        put32(m, kG + 12, f12);
        put32(m, kG + 20, f20);
        for (u32 k = 0; k < 4; ++k) putf(m, kG + 200 + 4 * k, frand(rng, -1.0f, 1.0f));
        {
            const SiPair p = run_pair_si(m, rg::fn_sub_2A48F0_002a48f0, rg::fn_sub_2A48F0_002a48f0__recomp,
                                         {rng(), rng(), rng(), rng()}, rng(), "sub_2A48F0", hw, with_recorders());
            ++pairs;
            const bool draw = (f12 & 4u) == 0 && (f20 & 4u) == 0 && (f20 & 8u) != 0;
            const StandIns& si = p.recomp->si;
            CHECK(si.calls_to(kDebugSphere) == (draw ? 1u : 0u));
            CHECK(si.calls_to(kDebugAxes) == (draw ? 1u : 0u));
            if (draw && si.log.size() == 2) {
                CHECK(si.log[0].args[0] == static_cast<u64>(static_cast<s64>(static_cast<s32>(kG + 188))));
                ++drawn;
            }
        }
    }
    MESSAGE("pairs " << pairs << ": " << destroyed << " objects destroyed, " << drawn << " markers drawn");
    CHECK(destroyed > 50);
    CHECK(drawn > 30);
}

// The scene fade callback sub_2A0440 (battle_camera_4.cpp) with sub_19F8F0 recorded: every path runs to the end.
TEST_CASE("game(battle_camera_6): the scene fade callback past the ambient-light calls") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xBC6003u};
    int first = 0, mid = 0, last = 0, pairs = 0;
    for (int i = 0; i < 240; ++i) {
        random_world(m, rng);
        u32 f = rng();
        if (chance(rng, 90)) f |= 0x2000002u;
        put32(m, kG + 12, f);
        for (u32 off = 0; off < 80; off += 4) putf(m, kData + off, frand(rng, 0.0f, 1.0f));
        const u32 frames = chance(rng, 10) ? 0u : 1 + rng() % 40;
        const u32 frame = chance(rng, 25) ? 0u : chance(rng, 25) ? frames : rng() % (frames + 2);
        put32(m, kData + 80, frames);
        put32(m, kData + 84, frame);
        put16(m, kData + 88, static_cast<u16>(rng() % 8));
        const SiPair p = run_pair_si(m, rg::fn_sub_2A0440_002a0440, rg::fn_sub_2A0440_002a0440__recomp,
                                     {kData, rng(), rng(), rng()}, rng(), "sub_2A0440", hw, with_recorders());
        ++pairs;
        if ((f & 0x2000002u) != 0x2000002u) {
            CHECK(p.hw.recomp.base.v0 == 1);
            continue;
        }
        // the rules: frame < frames -> frame + 1 and 0; else 1 (and the ambient = the gp-25472 bytes / 255)
        if (frame == 0) ++first;
        if (frame < frames) {
            CHECK(p.hw.recomp.base.v0 == 0);
            CHECK(get32(m, kData + 84) == frame + 1);
            ++mid;
        } else {
            CHECK(p.hw.recomp.base.v0 == 1);
            for (u32 k = 0; k < 4; ++k)
                CHECK(std::fabs(getf(m, kG + 548 + 4 * k) - m.at(kGp - 25472u + k)[0] / 255.0f) < 1e-5f);
            ++last;
        }
    }
    MESSAGE("sub_2A0440: " << pairs << " pairs (" << first << " first frames, " << mid << " fade frames, " << last << " last frames)");
    CHECK(mid > 50);
    CHECK(last > 20);
}

TEST_CASE("game(battle_camera_6): the scene fade callback on the battle route's snapshots") {
    NEED_MACHINE();
    const HwCheck hw = full_check();
    std::mt19937 rng{0xBC6004u};
    int pairs = 0;
    for (const char* dir : {"b_5800", "battle_ref_6150"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.empty()) {
            MESSAGE("SKIP: extracted/_ours/" << dir << "/eeMemory.bin not found");
            continue;
        }
        for (int i = 0; i < 12; ++i) {
            std::memcpy(m.at(0), snap.data(), snap.size());
            write_rw_slots(m);
            const u32 g = get32(m, kGBtlSlot);
            REQUIRE(g != 0);
            put32(m, g + 12, get32(m, g + 12) | 0x2000002u);
            const u32 d = kArena;  // a data block in the harness arena (free in the snapshots)
            for (u32 off = 0; off < 80; off += 4) putf(m, d + off, frand(rng, 0.0f, 1.0f));
            put32(m, d + 80, 8);
            put32(m, d + 84, static_cast<u32>(i % 10));
            put16(m, d + 88, static_cast<u16>(i % 4));
            run_pair_si(m, rg::fn_sub_2A0440_002a0440, rg::fn_sub_2A0440_002a0440__recomp, {d, 0, 0, 0}, rng(),
                        "sub_2A0440 snapshot", hw, with_recorders());
            ++pairs;
        }
    }
    MESSAGE("snapshot pairs: " << pairs);
}

}  // namespace p3fes::game_test

#else
TEST_CASE("game(battle_camera_6): no recompiled code in this build") { MESSAGE("SKIP: p3fes_game_tests built without P3FES_RT_EXEC_ELF"); }
#endif
