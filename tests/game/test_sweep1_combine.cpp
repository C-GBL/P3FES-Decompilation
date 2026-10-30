// Pair tests of slice sweep1, group combine (game/src/sweep/sweep1_combine.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * hand-built nm steps: the fclCombine menu waits (done flag, payload, owner slot);
//   * the backdrop particles: the emitter's slots, life ranges, colour and angle, the step's delay.
#include "sweep1_util.h"

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s1t;

namespace p3fes::recomp_gen {
void fn_sub_3D2740_003d2740(EEContext&);  // generated body
void fn_sub_3D2740_003d2740__recomp(EEContext&);  // recompiled
void fn_sub_3D2C10_003d2c10(EEContext&);  // generated body
void fn_sub_3D2C10_003d2c10__recomp(EEContext&);  // recompiled
void fn_sub_3D2CE0_003d2ce0(EEContext&);  // generated body
void fn_sub_3D2CE0_003d2ce0__recomp(EEContext&);  // recompiled
void fn_sub_3D2E00_003d2e00(EEContext&);  // generated body
void fn_sub_3D2E00_003d2e00__recomp(EEContext&);  // recompiled
void fn_sub_3D3050_003d3050(EEContext&);  // generated body
void fn_sub_3D3050_003d3050__recomp(EEContext&);  // recompiled
void fn_sub_3D3D20_003d3d20(EEContext&);  // generated body
void fn_sub_3D3D20_003d3d20__recomp(EEContext&);  // recompiled
void fn_sub_3D4DE0_003d4de0(EEContext&);  // generated body
void fn_sub_3D4DE0_003d4de0__recomp(EEContext&);  // recompiled
void fn_sub_3D4E90_003d4e90(EEContext&);  // generated body
void fn_sub_3D4E90_003d4e90__recomp(EEContext&);  // recompiled
void fn_sub_3D4FF0_003d4ff0(EEContext&);  // generated body
void fn_sub_3D4FF0_003d4ff0__recomp(EEContext&);  // recompiled
void fn_sub_3DA700_003da700(EEContext&);  // generated body
void fn_sub_3DA700_003da700__recomp(EEContext&);  // recompiled
void fn_sub_3DC2D0_003dc2d0(EEContext&);  // generated body
void fn_sub_3DC2D0_003dc2d0__recomp(EEContext&);  // recompiled
void fn_sub_3DC700_003dc700(EEContext&);  // generated body
void fn_sub_3DC700_003dc700__recomp(EEContext&);  // recompiled
void fn_sub_3DCC90_003dcc90(EEContext&);  // generated body
void fn_sub_3DCC90_003dcc90__recomp(EEContext&);  // recompiled
void fn_sub_3DDB90_003ddb90(EEContext&);  // generated body
void fn_sub_3DDB90_003ddb90__recomp(EEContext&);  // recompiled
void fn_sub_3DDD20_003ddd20(EEContext&);  // generated body
void fn_sub_3DDD20_003ddd20__recomp(EEContext&);  // recompiled
void fn_sub_3DE470_003de470(EEContext&);  // generated body
void fn_sub_3DE470_003de470__recomp(EEContext&);  // recompiled
void fn_sub_3E0B70_003e0b70(EEContext&);  // generated body
void fn_sub_3E0B70_003e0b70__recomp(EEContext&);  // recompiled
void fn_sub_3E5B00_003e5b00(EEContext&);  // generated body
void fn_sub_3E5B00_003e5b00__recomp(EEContext&);  // recompiled
void fn_sub_3E5E20_003e5e20(EEContext&);  // generated body
void fn_sub_3E5E20_003e5e20__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_3D2740", 0x3D2740, &recomp_gen::fn_sub_3D2740_003d2740, &recomp_gen::fn_sub_3D2740_003d2740__recomp},
    {"sub_3D2C10", 0x3D2C10, &recomp_gen::fn_sub_3D2C10_003d2c10, &recomp_gen::fn_sub_3D2C10_003d2c10__recomp},
    {"sub_3D2CE0", 0x3D2CE0, &recomp_gen::fn_sub_3D2CE0_003d2ce0, &recomp_gen::fn_sub_3D2CE0_003d2ce0__recomp},
    {"sub_3D2E00", 0x3D2E00, &recomp_gen::fn_sub_3D2E00_003d2e00, &recomp_gen::fn_sub_3D2E00_003d2e00__recomp},
    {"sub_3D3050", 0x3D3050, &recomp_gen::fn_sub_3D3050_003d3050, &recomp_gen::fn_sub_3D3050_003d3050__recomp},
    {"sub_3D3D20", 0x3D3D20, &recomp_gen::fn_sub_3D3D20_003d3d20, &recomp_gen::fn_sub_3D3D20_003d3d20__recomp},
    {"sub_3D4DE0", 0x3D4DE0, &recomp_gen::fn_sub_3D4DE0_003d4de0, &recomp_gen::fn_sub_3D4DE0_003d4de0__recomp},
    {"sub_3D4E90", 0x3D4E90, &recomp_gen::fn_sub_3D4E90_003d4e90, &recomp_gen::fn_sub_3D4E90_003d4e90__recomp},
    {"sub_3D4FF0", 0x3D4FF0, &recomp_gen::fn_sub_3D4FF0_003d4ff0, &recomp_gen::fn_sub_3D4FF0_003d4ff0__recomp},
    {"sub_3DA700", 0x3DA700, &recomp_gen::fn_sub_3DA700_003da700, &recomp_gen::fn_sub_3DA700_003da700__recomp},
    {"sub_3DC2D0", 0x3DC2D0, &recomp_gen::fn_sub_3DC2D0_003dc2d0, &recomp_gen::fn_sub_3DC2D0_003dc2d0__recomp},
    {"sub_3DC700", 0x3DC700, &recomp_gen::fn_sub_3DC700_003dc700, &recomp_gen::fn_sub_3DC700_003dc700__recomp},
    {"sub_3DCC90", 0x3DCC90, &recomp_gen::fn_sub_3DCC90_003dcc90, &recomp_gen::fn_sub_3DCC90_003dcc90__recomp},
    {"sub_3DDB90", 0x3DDB90, &recomp_gen::fn_sub_3DDB90_003ddb90, &recomp_gen::fn_sub_3DDB90_003ddb90__recomp},
    {"sub_3DDD20", 0x3DDD20, &recomp_gen::fn_sub_3DDD20_003ddd20, &recomp_gen::fn_sub_3DDD20_003ddd20__recomp},
    {"sub_3DE470", 0x3DE470, &recomp_gen::fn_sub_3DE470_003de470, &recomp_gen::fn_sub_3DE470_003de470__recomp},
    {"sub_3E0B70", 0x3E0B70, &recomp_gen::fn_sub_3E0B70_003e0b70, &recomp_gen::fn_sub_3E0B70_003e0b70__recomp},
    {"sub_3E5B00", 0x3E5B00, &recomp_gen::fn_sub_3E5B00_003e5b00, &recomp_gen::fn_sub_3E5B00_003e5b00__recomp},
    {"sub_3E5E20", 0x3E5E20, &recomp_gen::fn_sub_3E5E20_003e5e20, &recomp_gen::fn_sub_3E5E20_003e5e20__recomp},
};

}  // namespace

TEST_CASE("game(sweep1 combine): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 48);
}


// --- sweep1 cases (real data and documented rules) ---

namespace {

constexpr u32 kOwner = kScratch + 0x100, kStep = kScratch + 0x200, kObj = kScratch + 0x300, kPayload = kScratch + 0x400;
constexpr u32 kBg = kScratch + 0x1000;  // a backdrop: 64 particles of 16 bytes, +1036 the live count

}  // namespace

// The fclCombine menu waits: a step whose object reports done (flag bit 3 at +20) gives its payload's first word and
// is dropped from the owner (+20 / +32); otherwise -1 and nothing changes.
TEST_CASE("game(sweep1 combine): the fclCombine menu-step waits") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    struct W { const char* fn; u32 off; };
    for (const W w : {W{"sub_3D2CE0", 20}, W{"sub_3D4E90", 32}}) {
        for (const u32 flags : {0u, 8u, 0xFFu}) {
            SiPair sp = run_case(m, base, kCases, w.fn, {kOwner, 0, 0, 0}, 1 + flags, [&](Machine& mm) {
                std::memset(mm.at(kOwner), 0, 0x400);
                w32(mm, kOwner + w.off, kStep);
                w32(mm, kStep + 20, kObj);
                w32(mm, kObj + 20, flags);
                w32(mm, kObj + 40, kPayload);  // the payload: *(node +20) +40 (nm_message.h sub_3C5470)
                w32(mm, kPayload, 6);
            }, 0, {}, {0x3D06D0u});  // sub_3D06D0: hand-written since sweep5, recorded as before
            INFO(w.fn << " flags " << flags);
            if (flags & 8) {
                CHECK(v0_of(sp.hw) == 6);
                CHECK(r32(m, kOwner + w.off) == 0u);
            } else {
                CHECK(v0_of(sp.hw) == -1);
                CHECK(r32(m, kOwner + w.off) == kStep);
            }
        }
        // no step: -1
        SiPair sp = run_case(m, base, kCases, w.fn, {kOwner, 0, 0, 0}, 9, [&](Machine& mm) { std::memset(mm.at(kOwner), 0, 0x40); },
                             0, {}, {0x3D06D0u});
        CHECK(v0_of(sp.hw) == -1);
    }
}

// The backdrop particles: the emitter fills free slots (life +22 == 0) up to n with lives 30..49 (mode != 0) or
// 20..29, the colour byte 255 and an angle below 360, and counts them (+1036); the step counts a delay down first.
TEST_CASE("game(sweep1 combine): the backdrop particle emitter and step") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    for (const u32 mode : {0u, 1u}) {
        for (const u32 n : {1u, 5u, 70u}) {
            SiPair sp = run_case(m, base, kCases, "sub_3E5B00", {kBg, mode, 10, n}, 1 + n + mode, [&](Machine& mm) {
                std::memset(mm.at(kBg), 0, 1040);
                w16(mm, kBg + 16 * 3 + 22, 9);  // slot 3 is busy
            }, 0, {{8u, 64}});
            u32 emitted = 0;
            for (u32 i = 0; i < 64; ++i) {
                if (i == 3) continue;
                const u16 life = r16(m, kBg + 16 * i + 22);
                if (life == 0) continue;
                ++emitted;
                CHECK(life >= (mode ? 30u : 20u));
                CHECK(life <= (mode ? 49u : 29u));
                CHECK(r8(m, kBg + 16 * i + 20) == 255u);
                CHECK(r16(m, kBg + 16 * i + 26) < 360u);
            }
            CHECK(emitted == std::min(n, 63u));
            CHECK(r32(m, kBg + 1036) == std::min(n, 63u));
        }
    }
    // a delayed particle only counts its delay down
    SiPair sp = run_case(m, base, kCases, "sub_3E5E20", {kBg, kBg + 0x100, 0, 0}, 20, [&](Machine& mm) {
        std::memset(mm.at(kBg), 0, 0x200);
        w8(mm, kBg + 0x100 + 13, 4);
        w16(mm, kBg + 0x100 + 4, 111);
    });
    CHECK(r8(m, kBg + 0x100 + 13) == 3u);
    CHECK(r16(m, kBg + 0x100 + 4) == 111u);
}

// --- end of the sweep1 cases ---

#else

TEST_CASE("game(sweep1 combine): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
