// Pair tests of slice field6, part misc (game/src/field/field6_misc.cpp): the field screen filter draw and the
// after-effect packs, each body against its recompiled body (handgen_pairs.h / pair_harness.h / stand_ins.h), on
//   * random worlds: the p3fes_handgen sweep;
//   * the replay snapshots' live filters (climb_ref_17000, dorm_replay_4900, shop_ref_4100: FILTER.FLD loaded, an entry
//     selected, the blend at 1.0): the Im2D quads 0x872240 are checked against the colours computed on the host from
//     the filter data (the 8 x 9 corner grid of the entry, the brightness on alpha clamped to 0..255, the global scale
//     x / 255), and the half-way blend (FPU accumulator path) is paired;
//   * a hand-built after-effect pack list: a finished pack is unlinked and both its blocks freed, an empty list only
//     opens and closes the camera update.
// The render-state / Im2D entry points the bodies reach are stood in by recorders when this build does not emit them.
#include "field6_util.h"

#include "p3fes/game/field6_misc.h"

#include <algorithm>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::f6t;

namespace p3fes::recomp_gen {
void fn_sub_1D4610_001d4610(EEContext&);  // generated body
void fn_sub_1D4610_001d4610__recomp(EEContext&);  // recompiled
void fn_sub_1EDF10_001edf10(EEContext&);  // generated body
void fn_sub_1EDF10_001edf10__recomp(EEContext&);  // recompiled
void fn_sub_1EF060_001ef060(EEContext&);  // generated body
void fn_sub_1EF060_001ef060__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_1D4610", 0x1D4610, &recomp_gen::fn_sub_1D4610_001d4610, &recomp_gen::fn_sub_1D4610_001d4610__recomp},
    {"sub_1EDF10", 0x1EDF10, &recomp_gen::fn_sub_1EDF10_001edf10, &recomp_gen::fn_sub_1EDF10_001edf10__recomp},
    {"sub_1EF060", 0x1EF060, &recomp_gen::fn_sub_1EF060_001ef060, &recomp_gen::fn_sub_1EF060_001ef060__recomp},
};

const Case& fc(const char* name) { return find_case(kCases, name); }
namespace gp6 = game::f6::gp6;
constexpr u32 kQuads = 0x872240u;

SiPair run(Machine& m, const std::vector<u8>& base, const char* fn, Args args, u32 seed, const std::function<void(Machine&)>& extra = {}) {
    std::vector<u32> absent;
    return run_pair_si_absent(m, base, fc(fn).hand, fc(fn).recomp, args, seed, fn, whole_ram_check(),
                              [&](Machine& mm) {
                                  write_rw_slots(mm);
                                  if (extra) extra(mm);
                              },
                              absent);
}

}  // namespace

TEST_CASE("game(field6 misc): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 64);
}

// The filter draw against the host's colour rule (field6.h "The screen filter").
TEST_CASE("game(field6 misc): the screen filter quads on the replay snapshots (stand-ins)") {
    int checked = 0;
    for (const char* snap : {"climb_ref_17000", "dorm_replay_4900", "shop_ref_4100"}) {
        std::vector<u8> base;
        auto mp = real_machine(snap, base);
        if (!mp) continue;
        Machine& m = *mp;
        INFO(snap);
        const u32 data = r32(m, gpv(gp6::kFilterData));
        const u32 entry = r32(m, gpv(gp6::kFilterTarget));
        if (data == 0 || entry == 0 || rf32(m, gpv(gp6::kFilterBlend)) < 1.0f) continue;
        const s32 bright = rs32(m, gpv(gp6::kFilterBright));
        const s32 scale = rs32(m, gpv(gp6::kFilterScale));
        std::memset(m.at(kQuads), 0, 7 * 2048);  // the quads' colours must come from this draw
        for (u32 row = 0; row < 7; ++row)
            for (u32 col = 0; col < 8; ++col)
                for (u32 v = 0; v < 4; ++v) {  // keep the vertices' positions: the draw writes only the colours
                    const u32 q = kQuads + 2048 * row + 256 * col + 64 * v;
                    std::memcpy(m.at(q), base.data() + q, 32);
                    std::memcpy(m.at(q + 48), base.data() + q + 48, 16);
                }
        std::vector<u8> mod(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        SiPair sp = run(m, mod, "sub_1D4610", {0, 0, 0, 0}, 1);
        u32 bad = 0;
        for (u32 row = 0; row < 7; ++row)
            for (u32 col = 0; col < 8; ++col) {
                const u32 rec = data + 292 * entry + 36 * row + 4 * col;
                const u32 corner[4] = {rec + 4, rec + 8, rec + 40, rec + 44};
                for (u32 v = 0; v < 4; ++v)
                    for (u32 ch = 0; ch < 4; ++ch) {
                        s32 x = r8(m, corner[v] + ch);
                        if (ch == 3) x = std::clamp(x + bright, 0, 255);
                        if (scale != 255) x = x * scale / 255;
                        const f32 got = rf32(m, kQuads + 2048 * row + 256 * col + 64 * v + 32 + 4 * ch);
                        bad += got != static_cast<f32>(x);
                    }
            }
        CHECK(bad == 0u);
        // the half-way blend from the previous entry (the FPU accumulator path), paired
        run(m, base, "sub_1D4610", {0, 0, 0, 0}, 2, [](Machine& mm) {
            const f32 half = 0.5f;
            std::memcpy(mm.at(gpv(gp6::kFilterBlend)), &half, 4);
            w32(mm, gpv(gp6::kFilterShown), 1);
        });
        // no entry -> nothing
        SiPair none = run(m, base, "sub_1D4610", {0, 0, 0, 0}, 3, [](Machine& mm) { w32(mm, gpv(gp6::kFilterTarget), 0); });
        CHECK(none.recomp->si.log.empty());
        ++checked;
    }
    if (checked == 0) MESSAGE("SKIP: no snapshot with a filter");
}

// The after-effect packs: a finished pack (no effects) is unlinked from the list and both blocks are freed; an empty
// list only brackets the draws with the field camera's update.
TEST_CASE("game(field6 misc): the after-effect pack list (stand-ins)") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or no dorm_replay_4900 snapshot");
        return;
    }
    Machine& m = *mp;
    const u32 pack = kScratch, pdata = kScratch + 0x100;
    SiPair sp = run(m, base, "sub_1EF060", {0, 0, 0, 0}, 1, [=](Machine& mm) {
        std::memset(mm.at(pack), 0, 0x200);
        w32(mm, pack + 0, 8);           // every frame
        w32(mm, pack + 4, pdata);       // the pack data: +4 s16 the effect count = 0
        w32(mm, pack + 8, pdata + 0x40);
        w32(mm, pack + 12, pdata + 0x40);
        w32(mm, pack + 16, pdata + 0x40);
        w32(mm, gpv(gp6::kAfHead), pack);
        w32(mm, gpv(gp6::kAfTail), pack);
    });
    CHECK(v0_of(sp.hw) == 0);
    CHECK(r32(m, gpv(gp6::kAfHead)) == 0u);
    CHECK(r32(m, gpv(gp6::kAfTail)) == 0u);
    CHECK(sp.recomp->si.calls_to(kRwSlotFns[1]) == 2);  // the pack and its data (RwFree)
    sp = run(m, base, "sub_1EF060", {0, 0, 0, 0}, 2, [](Machine& mm) {
        w32(mm, gpv(gp6::kAfHead), 0);
        w32(mm, gpv(gp6::kAfTail), 0);
    });
    CHECK(sp.recomp->si.calls_to(kRwSlotFns[1]) == 0);
    // one pack drawn with no effects: the render states are saved and restored
    run(m, base, "sub_1EDF10", {pack, 0, 0, 0}, 3, [=](Machine& mm) {
        std::memset(mm.at(pack), 0, 0x200);
        w32(mm, pack + 4, pdata);
    });
}

#else

TEST_CASE("game(field6 misc): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
