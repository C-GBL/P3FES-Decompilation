// Phase 5 slice facility2 (part 3 of 3): fclShopMisc.c 0x4003A0 .. 0x40D330 -- the background part lists, the
// weapon-fusion recipes and orders, the inventory slot test, Elizabeth's requests (accessors, accept / cancel,
// deadline, the list and its animations), the date panel, the compendium (list, price, sorts, registering) and the
// list window part drivers. p3fes_handgen bodies made readable (see part 1).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/facility2.h"

namespace p3fes::recomp_gen {
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetMonthFromDaysSinceApr5_0017d830(p3fes::EEContext&);
void fn_clndIsHolidayOrSunday_0017dcf0(p3fes::EEContext&);
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext&);
void fn_nmCmdListCursorLine_003c6fb0(p3fes::EEContext&);
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);
void fn_nmCmdListMovedDownRow_003c6ce0(p3fes::EEContext&);
void fn_nmCmdListMovedUp_003c6cc0(p3fes::EEContext&);
void fn_nmCmdListPagedDown_003c6ca0(p3fes::EEContext&);
void fn_nmCmdListScrolledRow_003c6d10(p3fes::EEContext&);
void fn_nmCmdListSelect_003c5d40(p3fes::EEContext&);
void fn_nmCmdListSort_003c7000(p3fes::EEContext&);
void fn_nmCmdListUpdate_003c6270(p3fes::EEContext&);
void fn_nmListRemoveFiltered_003c4e70(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F810_0016f810(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_170D60_00170d60(p3fes::EEContext&);
void fn_sub_170ED0_00170ed0(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_173580_00173580(p3fes::EEContext&);
void fn_sub_173A00_00173a00(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_17C4E0_0017c4e0(p3fes::EEContext&);
void fn_sub_17C590_0017c590(p3fes::EEContext&);
void fn_sub_17C8C0_0017c8c0(p3fes::EEContext&);
void fn_sub_17C960_0017c960(p3fes::EEContext&);
void fn_sub_17CA10_0017ca10(p3fes::EEContext&);
void fn_sub_1828D0_001828d0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3D9820_003d9820(p3fes::EEContext&);
void fn_sub_3DF100_003df100(p3fes::EEContext&);
void fn_sub_3DFEB0_003dfeb0(p3fes::EEContext&);
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);
void fn_sub_3DFFC0_003dffc0(p3fes::EEContext&);
void fn_sub_3E0650_003e0650(p3fes::EEContext&);
void fn_sub_3E0680_003e0680(p3fes::EEContext&);
void fn_sub_3F03E0_003f03e0(p3fes::EEContext&);
void fn_sub_3F1A10_003f1a10(p3fes::EEContext&);
void fn_sub_3FFA20_003ffa20(p3fes::EEContext&);
void fn_sub_4003A0_004003a0(p3fes::EEContext&);
void fn_sub_4006C0_004006c0(p3fes::EEContext&);
void fn_sub_4008F0_004008f0(p3fes::EEContext&);
void fn_sub_400E30_00400e30(p3fes::EEContext&);
void fn_sub_4016D0_004016d0(p3fes::EEContext&);
void fn_sub_401800_00401800(p3fes::EEContext&);
void fn_sub_401A00_00401a00(p3fes::EEContext&);
void fn_sub_401C90_00401c90(p3fes::EEContext&);
void fn_sub_401CF0_00401cf0(p3fes::EEContext&);
void fn_sub_401D90_00401d90(p3fes::EEContext&);
void fn_sub_401DE0_00401de0(p3fes::EEContext&);
void fn_sub_402400_00402400(p3fes::EEContext&);
void fn_sub_402510_00402510(p3fes::EEContext&);
void fn_sub_4032F0_004032f0(p3fes::EEContext&);
void fn_sub_403340_00403340(p3fes::EEContext&);
void fn_sub_403410_00403410(p3fes::EEContext&);
void fn_sub_403760_00403760(p3fes::EEContext&);
void fn_sub_403780_00403780(p3fes::EEContext&);
void fn_sub_4037A0_004037a0(p3fes::EEContext&);
void fn_sub_4037C0_004037c0(p3fes::EEContext&);
void fn_sub_4037E0_004037e0(p3fes::EEContext&);
void fn_sub_403860_00403860(p3fes::EEContext&);
void fn_sub_4038E0_004038e0(p3fes::EEContext&);
void fn_sub_404470_00404470(p3fes::EEContext&);
void fn_sub_404750_00404750(p3fes::EEContext&);
void fn_sub_405A90_00405a90(p3fes::EEContext&);
void fn_sub_405D60_00405d60(p3fes::EEContext&);
void fn_sub_405DB0_00405db0(p3fes::EEContext&);
void fn_sub_405E00_00405e00(p3fes::EEContext&);
void fn_sub_405E30_00405e30(p3fes::EEContext&);
void fn_sub_406AA0_00406aa0(p3fes::EEContext&);
void fn_sub_407180_00407180(p3fes::EEContext&);
void fn_sub_407210_00407210(p3fes::EEContext&);
void fn_sub_409C80_00409c80(p3fes::EEContext&);
void fn_sub_409E90_00409e90(p3fes::EEContext&);
void fn_sub_409F20_00409f20(p3fes::EEContext&);
void fn_sub_40A200_0040a200(p3fes::EEContext&);
void fn_sub_40A260_0040a260(p3fes::EEContext&);
void fn_sub_40A5B0_0040a5b0(p3fes::EEContext&);
void fn_sub_40A640_0040a640(p3fes::EEContext&);
void fn_sub_40A6D0_0040a6d0(p3fes::EEContext&);
void fn_sub_40A7C0_0040a7c0(p3fes::EEContext&);
void fn_sub_40B630_0040b630(p3fes::EEContext&);
void fn_sub_40B780_0040b780(p3fes::EEContext&);
void fn_sub_40C150_0040c150(p3fes::EEContext&);
void fn_sub_40C1E0_0040c1e0(p3fes::EEContext&);
void fn_sub_40C460_0040c460(p3fes::EEContext&);
void fn_sub_40C520_0040c520(p3fes::EEContext&);
void fn_sub_40C5B0_0040c5b0(p3fes::EEContext&);
void fn_sub_40C650_0040c650(p3fes::EEContext&);
void fn_sub_40C6A0_0040c6a0(p3fes::EEContext&);
void fn_sub_40CA00_0040ca00(p3fes::EEContext&);
void fn_sub_40D330_0040d330(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40EBC0_0040ebc0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fac2;  // the records of facility2.h

// 0x004003A0 sub_4003A0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopFreeListPair] Destroys a {command list, object} pair a0 (null: nothing): frees the object at +4 when set
// (sub_3C45F0), then the list at +0.
void sub_4003A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004003a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x004003b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        if (a0 != 0) {
            // 0x004003c4
            charge(ctx, 2);
            jal(ctx, 0x4003C4u, gen::fn_sub_3C45F0_003c45f0);
        }
        // 0x004003cc
        charge(ctx, 3);
        lw(a0, s0, 0);
        jal(ctx, 0x4003D0u, gen::fn_nmCmdListDestroy_003c5a20);
    }
    // 0x004003d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004006C0 sub_4006C0 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBgPartsPurge] A background part list's draw callback (data ref): walks the part list (the list a3's user +4) and
// removes every part whose event pair (+4 / +6) has happened (sub_3FFA20).
void sub_4006C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004006c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a3, lst::kState);
    lw(v1, v1, 68);
    lw(s1, v1, 4);
    lw(s0, s1, lst::kHead);
    for (;;) {
        // 0x0040071c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004006e8
        charge(ctx, 9);
        lw(a2, s0, node::kPayload);
        lh(a0, a2, bgpart::kCondA);
        lh(a1, a2, bgpart::kCondB);
        jal(ctx, 0x4006F4u, gen::fn_sub_3FFA20_003ffa20);
        a2 = s0;
        lw(s0, s0, node::kNext);
        if (v0 != 0) {
            // 0x0040070c
            charge(ctx, 4);
            a0 = s1;
            a1 = addiu(s1, 4);
            jal(ctx, 0x400714u, gen::fn_sub_3C49E0_003c49e0);
        }
    }
    // 0x00400724
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004008F0 sub_4008F0 -- 408 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBgPartsDraw] A background part list's draw: by the list's row count 6 / 5 / 4 the sprites 79 80 / 81 82 / 83 84 at
// (a0, a1) with alpha a2, then the purge of sub_4006C0.
void sub_4008F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004008f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    lw(v1, a3, lst::kState);
    lw(s0, v1, 68);
    lhu(a2, a3, lst::kCount);
    v1 = 6;
    if (a2 == v1) {
        // 0x004009dc: 6 rows
        charge(ctx, 16);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a2 = s1 & 0xFF;
        a3 = 79;
        t0 = 0;
        jal(ctx, 0x4009F0u, gen::fn_sub_40E3C0_0040e3c0);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a2 = s1 & 0xFF;
        a0 = s3;
        a1 = s2;
        a3 = 80;
        t0 = 0;
        jal(ctx, 0x400A14u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x0040092c
        charge(ctx, 3);
        v1 = 5;
        if (a2 == v1) {
            // 0x00400994: 5 rows
            charge(ctx, 18);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a2 = s1 & 0xFF;
            a3 = 81;
            t0 = 0;
            jal(ctx, 0x4009A8u, gen::fn_sub_40E3C0_0040e3c0);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a2 = s1 & 0xFF;
            a0 = s3;
            a1 = s2;
            a3 = 82;
            t0 = 0;
            jal(ctx, 0x4009CCu, gen::fn_sub_40E3C0_0040e3c0);
        } else {
            // 0x00400938
            charge(ctx, 3);
            v1 = 4;
            if (a2 == v1) {
                // 0x0040094c: 4 rows
                charge(ctx, 18);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a2 = s1 & 0xFF;
                a3 = 83;
                t0 = 0;
                jal(ctx, 0x400960u, gen::fn_sub_40E3C0_0040e3c0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a2 = s1 & 0xFF;
                a0 = s3;
                a1 = s2;
                a3 = 84;
                t0 = 0;
                jal(ctx, 0x400984u, gen::fn_sub_40E3C0_0040e3c0);
            } else {
                // 0x00400944
                charge(ctx, 2);
            }
        }
    }
    // 0x00400a1c: remove the parts whose events happened
    charge(ctx, 4);
    lw(s1, s0, 4);
    lw(s0, s1, lst::kHead);
    for (;;) {
        // 0x00400a60
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00400a2c
        charge(ctx, 9);
        lw(a2, s0, node::kPayload);
        lh(a0, a2, bgpart::kCondA);
        lh(a1, a2, bgpart::kCondB);
        jal(ctx, 0x400A38u, gen::fn_sub_3FFA20_003ffa20);
        a2 = s0;
        lw(s0, s0, node::kNext);
        if (v0 != 0) {
            // 0x00400a50
            charge(ctx, 4);
            a0 = s1;
            a1 = addiu(s1, 4);
            jal(ctx, 0x400A58u, gen::fn_sub_3C49E0_003c49e0);
        }
    }
    // 0x00400a68
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00400E30 sub_400E30 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopBgManagerDestroy] Destroys the background manager a0 (shops.h kBg*; null or without a list: nothing): its task with
// the children (kwlnTaskDestroyWithHierarchy, when there is one), then the element list.
void sub_400E30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00400e30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x00400e48
        charge(ctx, 3);
        lw(v1, s0, bgm::kList);
        if (v1 != 0) {
            // 0x00400e54
            charge(ctx, 3);
            lw(a0, s0, bgm::kTask);
            if (a0 != 0) {
                // 0x00400e60
                charge(ctx, 2);
                jal(ctx, 0x400E60u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            }
            // 0x00400e68
            charge(ctx, 3);
            lw(a0, s0, bgm::kList);
            jal(ctx, 0x400E6Cu, gen::fn_sub_3C45F0_003c45f0);
        }
    }
    // 0x00400e74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004016D0 sub_4016D0 -- 296 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclPersonaBestStats] The best-stat mask of persona a0: the stats St Ma En Ag Lu (sub_173A00(persona, 0..4)) as the bits
// 1 2 4 8 16 of the highest one. A tie is kept only between St and Ma (mask 3); for En / Ag / Lu a later stat replaces
// the mask only when it is strictly higher (the equal test inside "higher" can never hold).
void sub_4016D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004016d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a1 = 0;
    jal(ctx, 0x4016ECu, gen::fn_sub_173A00_00173a00);
    s0 = v0;
    s1 = 1;
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x401704u, gen::fn_sub_173A00_00173a00);
    at = slt(v0, s0);
    if (at == 0) {
        // 0x00401718: Ma vs St
        charge(ctx, 2);
        if (s0 != v0) {
            // 0x0040172c
            charge(ctx, 1);
            s1 = 2;
        } else {
            // 0x00401720: a tie: St and Ma
            charge(ctx, 3);
            s1 = s1 | 0x2;
        }
        // 0x00401730
        charge(ctx, 1);
        s0 = v0;
    }
    // 0x00401734
    charge(ctx, 7);
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x40173Cu, gen::fn_sub_173A00_00173a00);
    at = slt(s0, v0);
    if (at != 0) {
        // 0x00401750: En higher
        charge(ctx, 2);
        if (s0 != v0) {
            // 0x00401764
            charge(ctx, 1);
            s1 = 4;
        } else {
            // 0x00401758
            charge(ctx, 3);
            s1 = s1 | 0x4;
        }
        // 0x00401768
        charge(ctx, 1);
        s0 = v0;
    }
    // 0x0040176c
    charge(ctx, 7);
    a0 = s2;
    a1 = 3;
    jal(ctx, 0x401774u, gen::fn_sub_173A00_00173a00);
    at = slt(s0, v0);
    if (at != 0) {
        // 0x00401788: Ag higher
        charge(ctx, 2);
        if (s0 != v0) {
            // 0x0040179c
            charge(ctx, 1);
            s1 = 8;
        } else {
            // 0x00401790
            charge(ctx, 3);
            s1 = s1 | 0x8;
        }
        // 0x004017a0
        charge(ctx, 1);
        s0 = v0;
    }
    // 0x004017a4
    charge(ctx, 7);
    a0 = s2;
    a1 = 4;
    jal(ctx, 0x4017ACu, gen::fn_sub_173A00_00173a00);
    at = slt(s0, v0);
    if (at != 0) {
        // 0x004017c0: Lu higher
        charge(ctx, 2);
        if (s0 != v0) {
            // 0x004017d4
            charge(ctx, 1);
            s1 = 16;
        } else {
            // 0x004017c8
            charge(ctx, 3);
            s1 = s1 | 0x10;
        }
    }
    // 0x004017d8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00401800 sub_401800 -- 136 bytes; frame 0x30
// [fclFusionItemFlag] The game flag of a weapon-fusion item: the index i of item a0 in the 24 halfwords of 0x6AF3A0 (copied
// to the stack) -> flag 4736 + i; not listed -> 0.
void sub_401800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29};
    // 0x00401800
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a3 = 0x6B0000;
    a3 = addiu(a3, -3168);  // &0x6AF3A0
    a2 = addiu(sp, 0x0);
    a1 = 12;
    for (;;) {
        // 0x00401814
        charge(ctx, 9);
        lh(v1, a3, 0);
        lh(v0, a3, 2);
        a3 = addiu(a3, 4);
        a1 = addiu(a1, -1);
        sh(v1, a2, 0);
        sh(v0, a2, 2);
        a2 = addiu(a2, 4);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00401838
    charge(ctx, 4);
    a1 = 0;
    v1 = a0 & 0xFFFF;
    for (;;) {
        // 0x0040186c
        charge(ctx, 3);
        v0 = sltiu(a1, 24);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401848
        charge(ctx, 5);
        v0 = sll(a1, 1);
        v0 = addu(v0, sp);
        lhu(v0, v0, 0);
        if (v1 == v0) {
            goto L_0040185c_4;
        }
        // 0x00401868
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x00401878
    charge(ctx, 1);
    v0 = 0;
    // 0x0040187c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x30);
    return;
L_0040185c_4:
    charge(ctx, 3);
    v0 = addiu(a1, 4736);
    // 0x0040187c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x30);
}

// 0x00401A00 sub_401A00 -- 652 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclFusionResult] The item persona a1 makes from base item a0 in weapon fusion; *a2 (a stack word when a2 is null) gets it.
// The fixed table (gp - 21512 = 0x7CD8E8 -> 0x6AD1D0, 16 {persona id, item} pairs) wins: returns 2. Else the base item's
// group -- the item itself when it is one of the eight of 0x6AF180, else table 0x7CD8C0 -> 0x6ACCE0 (24 {item, group}) --
// and the first recipe of 0x7CD8D0 -> 0x6ACE30 (25 x 16 bytes, recipe::) of that group whose stat mask shares a bit with
// the persona's best stats (sub_4016D0): *a2 = its item, returns 1; none: 0 (with *a2 = 0 from the first lookup). A null
// persona is K_Assert("fclShopMisc.c", 6824); a null recipe pointer K_Assert(6727) (both continue).
void sub_401A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401a00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s4 = a1;
    if (a2 == 0) {
        // 0x00401a38
        charge(ctx, 1);
        s1 = addiu(sp, 0x8E);
    } else {
        // 0x00401a2c
        charge(ctx, 3);
        s1 = a2;
    }
    // 0x00401a3c
    charge(ctx, 2);
    if (s4 == 0) {
        // 0x00401a44: no persona: K_Assert (retail continues)
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 6824;
        jal(ctx, 0x401A50u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00401a58
    charge(ctx, 6);
    lhu(a2, s4, persona::kId);
    lw(a1, gp, -21512);  // 0x7CD8E8
    lw(a0, gp, -21508);  // 0x7CD8EC
    a3 = 0;
    for (;;) {
        // 0x00401a94
        charge(ctx, 3);
        v0 = slt(a3, a0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401a70
        charge(ctx, 5);
        v0 = sll(a3, 2);
        v1 = addu(a1, v0);
        lhu(v0, v1, 0);
        if (a2 == v0) {
            goto L_00401a84_7;
        }
        // 0x00401a90
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x00401aa0
    charge(ctx, 1);
    v0 = 0;
L_00401aa4:
    charge(ctx, 3);
    sh(v0, s1, 0);
    if (v0 == 0) {
        // 0x00401abc: not fixed: the base item's group
        charge(ctx, 10);
        t3 = 0;
        t2 = s0 & 0xFFFF;
        v0 = 0x6B0000;
        lq(v0, v0, -3712);  // 0x6AF180
        sq(v0, sp, 0x60);
        a1 = addiu(sp, 0x60);
        a0 = addiu(sp, 0x70);
        v1 = 4;
        for (;;) {
            // 0x00401afc
            charge(ctx, 3);
            a3 = v1;
            t1 = a1;
            t0 = a0;
            for (;;) {
                // 0x00401b08
                charge(ctx, 9);
                lh(a2, t1, 0);
                lh(v0, t1, 2);
                t1 = addiu(t1, 4);
                a3 = addiu(a3, -1);
                sh(a2, t0, 0);
                sh(v0, t0, 2);
                t0 = addiu(t0, 4);
                if (i64(a3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00401b2c
            charge(ctx, 3);
            v0 = sltiu(t3, 8);
            if (v0 != 0) {
                // 0x00401b44
                charge(ctx, 3);
                v0 = sll(t3, 1);
                v0 = addu(v0, sp);
                lhu(v0, v0, 112);
            } else {
                // 0x00401b38
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00401b50
            charge(ctx, 3);
            v0 = v0 & 0xFFFF;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00401ae4
            charge(ctx, 2);
            if (t2 == v0) {
                goto L_00401aec_15;
            }
            // 0x00401af8
            charge(ctx, 1);
            t3 = addiu(t3, 1);
        }
        // 0x00401b5c
        charge(ctx, 1);
        v0 = 0;
    L_00401b60:
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x00401b78: not one of the eight: the group table
            charge(ctx, 5);
            lw(a0, gp, -21552);  // 0x7CD8C0
            a1 = 0;
            lw(v1, gp, -21548);  // 0x7CD8C4
            for (;;) {
                // 0x00401bac
                charge(ctx, 3);
                v0 = sltu(a1, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00401b8c
                charge(ctx, 3);
                lh(v0, a0, 0);
                if (v0 == t2) {
                    goto L_00401b98_28;
                }
                // 0x00401ba4
                charge(ctx, 2);
                a0 = addiu(a0, 4);
                a1 = addiu(a1, 1);
            }
            // 0x00401bb8
            charge(ctx, 1);
            v0 = 0;
        L_00401bbc:
            charge(ctx, 2);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        } else {
            // 0x00401b68
            charge(ctx, 4);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
        }
        // 0x00401bc4: the first recipe of the group matching the best stats
        charge(ctx, 6);
        lw(s3, gp, -21536);  // 0x7CD8D0
        s2 = 0;
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        for (;;) {
            // 0x00401c34
            charge(ctx, 4);
            lw(v0, gp, -21532);  // 0x7CD8D4
            v0 = sltu(s2, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00401bdc
            charge(ctx, 3);
            lhu(v0, s3, recipe::kGroup);
            if (v0 == s0) {
                // 0x00401be8
                charge(ctx, 2);
                if (s3 == 0) {
                    // 0x00401bf0
                    charge(ctx, 5);
                    a0 = 0x6B0000;
                    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                    a1 = 6727;
                    jal(ctx, 0x401BFCu, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x00401c04
                charge(ctx, 8);
                a0 = s4;
                jal(ctx, 0x401C08u, gen::fn_sub_4016D0_004016d0);
                lw(v1, s3, recipe::kMask);
                v0 = v1 & v0;
                v0 = sltu(0, v0);
                if (v0 == 0) {
                    goto L_00401c2c;
                }
                goto L_00401c24_38;
            }
        L_00401c2c:
            charge(ctx, 2);
            s3 = addiu(s3, 16);
            s2 = addiu(s2, 1);
        }
        // 0x00401c44
        charge(ctx, 1);
        s3 = 0;
    L_00401c48:
        charge(ctx, 2);
        if (s3 != 0) {
            // 0x00401c5c: no recipe
            charge(ctx, 3);
            lhu(v0, s3, recipe::kItem);
            sh(v0, s1, 0);
            v0 = 1;
        } else {
            // 0x00401c50: a recipe: its item
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00401ab0
        charge(ctx, 3);
        v0 = 2;
    }
    // 0x00401c68 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
    return;
L_00401a84_7:
    charge(ctx, 3);
    lhu(v0, v1, 2);
    goto L_00401aa4;
L_00401aec_15:
    charge(ctx, 3);
    v0 = 1;
    goto L_00401b60;
L_00401b98_28:
    charge(ctx, 3);
    lhu(v0, a0, 2);
    goto L_00401bbc;
L_00401c24_38:
    charge(ctx, 2);
    goto L_00401c48;
}

// 0x00401C90 sub_401C90 -- 96 bytes; leaf frame (no stack)
// [fclFusionFindBand] The level band of persona a1 in the band table a0 {6-byte entries {u8 lo, u8 hi, s16, s16}, count}:
// the first with lo <= level <= hi, else 0.
void sub_401C90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00401c90
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    a3 = 0;
    lw(a2, a0, 4);
    for (;;) {
        // 0x00401cd8
        charge(ctx, 3);
        v1 = sltu(a3, a2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401ca4
        charge(ctx, 5);
        lbu(a0, a1, persona::kLevel);
        lbu(v1, v0, band::kLo);
        at = slt(a0, v1);
        if (at == 0) {
            // 0x00401cb8
            charge(ctx, 4);
            lbu(v1, v0, band::kHi);
            v1 = slt(v1, a0);
            if (v1 != 0) {
                goto L_00401cd0;
            }
            goto L_00401cc8_3;
        }
    L_00401cd0:
        charge(ctx, 2);
        v0 = addiu(v0, 6);
        a3 = addiu(a3, 1);
    }
    // 0x00401ce4
    charge(ctx, 1);
    v0 = 0;
    // 0x00401ce8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00401cc8_3:
    charge(ctx, 2);
    // 0x00401ce8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00401CF0 sub_401CF0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclFusionFindArcanaBand] The 46-byte level band of persona a0 in table 0x7CD8D8 -> 0x6ACFC0 (10 entries {u8 lo, u8 hi,
// u16 per arcana ...}): the first containing its level, else 0. A null persona is K_Assert("fclShopMisc.c", 6874).
void sub_401CF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401cf0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x00401d08
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 6874;
        jal(ctx, 0x401D14u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00401d1c
    charge(ctx, 5);
    lw(v0, gp, -21528);  // 0x7CD8D8
    a2 = 0;
    lw(a1, gp, -21524);  // 0x7CD8DC
    for (;;) {
        // 0x00401d64
        charge(ctx, 3);
        v1 = sltu(a2, a1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401d30
        charge(ctx, 5);
        lbu(a0, s0, persona::kLevel);
        lbu(v1, v0, band::kLo);
        at = slt(a0, v1);
        if (at == 0) {
            // 0x00401d44
            charge(ctx, 4);
            lbu(v1, v0, band::kHi);
            v1 = slt(v1, a0);
            if (v1 != 0) {
                goto L_00401d5c;
            }
            goto L_00401d54_5;
        }
    L_00401d5c:
        charge(ctx, 2);
        v0 = addiu(v0, 46);
        a2 = addiu(a2, 1);
    }
    // 0x00401d70
    charge(ctx, 1);
    v0 = 0;
    // 0x00401d74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_00401d54_5:
    charge(ctx, 2);
    // 0x00401d74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00401D90 sub_401D90 -- 76 bytes; leaf frame (no stack)
// [fclFusionFindFoolEntry] The 6-byte entry {u16 persona id, u8, u8, u8} of persona a0 in table 0x7CD8E0 -> 0x6AD190 (9
// entries; the Fool personas' values), else 0.
void sub_401D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x00401d90
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, -21520);  // 0x7CD8E0
    a3 = 0;
    lw(a2, gp, -21516);  // 0x7CD8E4
    for (;;) {
        // 0x00401dc4
        charge(ctx, 3);
        v1 = sltu(a3, a2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401da4
        charge(ctx, 4);
        lhu(a1, v0, fent::kId);
        lhu(v1, a0, persona::kId);
        if (a1 == v1) {
            goto L_00401db4_2;
        }
        // 0x00401dbc
        charge(ctx, 2);
        v0 = addiu(v0, 6);
        a3 = addiu(a3, 1);
    }
    // 0x00401dd0
    charge(ctx, 1);
    v0 = 0;
    // 0x00401dd4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00401db4_2:
    charge(ctx, 2);
    // 0x00401dd4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00401DE0 sub_401DE0 -- 1564 bytes; frame 0xB0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclFusionMakeOrder] Builds the weapon-fusion order a0 (order::, cleared) for base item a1 and persona a2. A fixed result
// (the table of sub_401A00) sets flag 2 and fills the order from that item (sub_1828D0). Else the recipe as in sub_401A00
// (no recipe: returns 0): the item and its record word (+8, sub_170D60 / sub_3F1A10), the two values of the recipe's level
// band for the persona's level (+14 / +16), the byte of the arcana level band (+13; for a Fool persona the Fool table's
// three values replace +14 / +16 / +13). Then the pick-up date: today (datGetDaysSinceApr5) + 1, + 2 for a fixed result,
// as month / day; flag 1; +24 = the item record's value (by kind: +24 / +32 / +28 / +28 / +36) when the item's fusion flag
// (sub_401800) exists and is unset, else level / 5 + 1. Returns 1. The K_Asserts (7005 / 7006 / 6959 / 6727 / 6967 /
// 6906 / 6917 / 6993 / 6994) continue in retail.
void sub_401DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401de0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s0 = a1;
    s3 = a2;
    if (s0 == 0) {
        // 0x00401e18
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 7005;
        jal(ctx, 0x401E24u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00401e2c
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x00401e34
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 7006;
        jal(ctx, 0x401E40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00401e48
    charge(ctx, 11);
    a0 = s4;
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x401E54u, gen::fn_memset_00521408);
    lhu(v0, s3, persona::kId);
    lw(a2, gp, -21512);  // 0x7CD8E8
    lw(a1, gp, -21508);  // 0x7CD8EC
    a3 = 0;
    for (;;) {
        // 0x00401e98
        charge(ctx, 3);
        v1 = slt(a3, a1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401e74
        charge(ctx, 5);
        v1 = sll(a3, 2);
        a0 = addu(a2, v1);
        lhu(v1, a0, 0);
        if (v0 == v1) {
            goto L_00401e88_6;
        }
        // 0x00401e94
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x00401ea4
    charge(ctx, 1);
    v1 = 0;
L_00401ea8:
    charge(ctx, 4);
    s1 = dsll32(v1, 16);
    s1 = dsra32(s1, 16);
    if (v1 != 0) {
        // 0x00401eb8
        charge(ctx, 6);
        lh(v0, s4, order::kFlags);
        v0 = v0 | 0x2;
        sh(v0, s4, order::kFlags);
        v0 = addiu(s4, 4);
        if (v0 == 0) {
            // 0x00401ed0
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 6959;
            jal(ctx, 0x401EDCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00401ee4: a fixed result
        charge(ctx, 7);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = addiu(s4, 4);
        jal(ctx, 0x401EF0u, gen::fn_sub_1828D0_001828d0);
        goto L_0040226c;
    }
    // 0x00401f00: the base item's group
    charge(ctx, 11);
    lh(t4, s0, item::kId);
    t5 = 0;
    v1 = t4 & 0xFFFF;
    a0 = 0x6B0000;
    lq(a0, a0, -3712);  // 0x6AF180
    sq(a0, sp, 0x80);
    a3 = addiu(sp, 0x80);
    a2 = addiu(sp, 0x90);
    a1 = 4;
    for (;;) {
        // 0x00401f44
        charge(ctx, 3);
        t1 = a1;
        t3 = a3;
        t2 = a2;
        for (;;) {
            // 0x00401f50
            charge(ctx, 9);
            lh(t0, t3, 0);
            lh(a0, t3, 2);
            t3 = addiu(t3, 4);
            t1 = addiu(t1, -1);
            sh(t0, t2, 0);
            sh(a0, t2, 2);
            t2 = addiu(t2, 4);
            if (i64(t1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00401f74
        charge(ctx, 3);
        a0 = sltiu(t5, 8);
        if (a0 != 0) {
            // 0x00401f8c
            charge(ctx, 3);
            a0 = sll(t5, 1);
            a0 = addu(a0, sp);
            lhu(a0, a0, 144);
        } else {
            // 0x00401f80
            charge(ctx, 3);
            a0 = 0;
        }
        // 0x00401f98
        charge(ctx, 3);
        a0 = a0 & 0xFFFF;
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401f2c
        charge(ctx, 2);
        if (v1 == a0) {
            goto L_00401f34_16;
        }
        // 0x00401f40
        charge(ctx, 1);
        t5 = addiu(t5, 1);
    }
    // 0x00401fa4
    charge(ctx, 1);
    a0 = 0;
L_00401fa8:
    charge(ctx, 2);
    if (a0 == 0) {
        // 0x00401ff8
        charge(ctx, 5);
        lw(a2, gp, -21552);  // 0x7CD8C0
        a3 = 0;
        lw(a1, gp, -21548);  // 0x7CD8C4
        for (;;) {
            // 0x0040202c
            charge(ctx, 3);
            a0 = sltu(a3, a1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0040200c
            charge(ctx, 3);
            lh(a0, a2, 0);
            if (a0 == v1) {
                goto L_00402018_31;
            }
            // 0x00402024
            charge(ctx, 2);
            a2 = addiu(a2, 4);
            a3 = addiu(a3, 1);
        }
        // 0x00402038
        charge(ctx, 1);
        v1 = 0;
    L_0040203c:
        charge(ctx, 11);
        a1 = dsll32(v1, 16);
        a1 = dsra32(a1, 16);
        lw(a0, gp, -18640);  // 0x7CE420
        v1 = sll(v0, 3);
        v0 = subu(v1, v0);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lbu(v1, v0, 2);
        v0 = 1;
        if (v1 != v0) {
            // 0x00402078
            charge(ctx, 1);
            s2 = 0;
        } else {
            // 0x00402068
            charge(ctx, 4);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
        }
    } else {
        // 0x00401fb0
        charge(ctx, 11);
        a1 = dsll32(t4, 16);
        a1 = dsra32(a1, 16);
        lw(a0, gp, -18640);  // 0x7CE420
        v1 = sll(v0, 3);
        v0 = subu(v1, v0);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lbu(v1, v0, 2);
        v0 = 1;
        if (v1 != v0) {
            // 0x00401fec
            charge(ctx, 3);
            s2 = 0;
        } else {
            // 0x00401fdc
            charge(ctx, 4);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
        }
    }
    // 0x0040207c: the recipe of the group matching the best stats
    charge(ctx, 6);
    lw(s1, gp, -21536);  // 0x7CD8D0
    s0 = 0;
    s6 = dsll32(a1, 16);
    s6 = dsra32(s6, 16);
    for (;;) {
        // 0x004020ec
        charge(ctx, 4);
        lw(v0, gp, -21532);  // 0x7CD8D4
        v0 = sltu(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00402094
        charge(ctx, 3);
        lhu(v0, s1, recipe::kGroup);
        if (v0 == s6) {
            // 0x004020a0
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x004020a8
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 6727;
                jal(ctx, 0x4020B4u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x004020bc
            charge(ctx, 8);
            a0 = s3;
            jal(ctx, 0x4020C0u, gen::fn_sub_4016D0_004016d0);
            lw(v1, s1, recipe::kMask);
            v0 = v1 & v0;
            v0 = sltu(0, v0);
            if (v0 == 0) {
                goto L_004020e4;
            }
            goto L_004020dc_43;
        }
    L_004020e4:
        charge(ctx, 2);
        s1 = addiu(s1, 16);
        s0 = addiu(s0, 1);
    }
    // 0x004020fc
    charge(ctx, 1);
    s1 = 0;
L_00402100:
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x00402114
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x0040211c
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 6967;
            jal(ctx, 0x402128u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00402130: the recipe's item and level band
        charge(ctx, 21);
        lhu(s0, s1, recipe::kItem);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x40213Cu, gen::fn_sub_170D60_00170d60);
        sh(s0, s4, order::kItem);
        lw(a0, v0, 4);
        sw(a0, s4, order::kRaw);
        jal(ctx, 0x402150u, gen::fn_sub_3F1A10_003f1a10);
        lh(v0, s4, order::kItem);
        a0 = v0;
        jal(ctx, 0x402160u, gen::fn_sub_170D60_00170d60);
        a0 = addiu(s1, 8);
        a1 = s3;
        jal(ctx, 0x402170u, gen::fn_sub_401C90_00401c90);
        s0 = v0;
        if (s0 == 0) {
            // 0x00402184
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 6906;
            jal(ctx, 0x402190u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00402198: the arcana level band
        charge(ctx, 10);
        lhu(v0, s0, band::kValueA);
        sh(v0, s4, order::kStatA);
        lhu(v0, s0, band::kValueB);
        sh(v0, s4, order::kStatB);
        a0 = s3;
        jal(ctx, 0x4021ACu, gen::fn_sub_401CF0_00401cf0);
        s0 = v0;
        if (s0 == 0) {
            // 0x004021c0
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 6917;
            jal(ctx, 0x4021CCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x004021d4
        charge(ctx, 13);
        lhu(v1, s3, persona::kId);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);
        lw(v0, gp, -18640);  // 0x7CE420
        v0 = addu(v1, v0);
        lbu(v0, v0, 2);
        v0 = sll(v0, 1);
        v0 = addu(s0, v0);
        lhu(v0, v0, 0);
        sb(v0, s4, order::kByte13);
        if (s2 != 0) {
            // 0x00402208: a Fool persona: the Fool table
            charge(ctx, 6);
            a0 = s3;
            jal(ctx, 0x40220Cu, gen::fn_sub_401D90_00401d90);
            s0 = v0;
            if (s0 == 0) {
                // 0x00402220
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 6993;
                jal(ctx, 0x40222Cu, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x00402234
            charge(ctx, 3);
            v0 = addiu(s4, 4);
            if (v0 == 0) {
                // 0x00402240
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 6994;
                jal(ctx, 0x40224Cu, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x00402254
            charge(ctx, 6);
            lbu(v0, s0, fent::kValueA);
            sh(v0, s4, order::kStatA);
            lbu(v0, s0, fent::kValueB);
            sh(v0, s4, order::kStatB);
            lbu(v0, s0, fent::kByte);
            sb(v0, s4, order::kByte13);
        }
    L_0040226c:
        charge(ctx, 8);
        jal(ctx, 0x40226Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        lh(v0, s4, order::kFlags);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x004022a0
            charge(ctx, 3);
            v0 = addiu(v1, 1);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        } else {
            // 0x0040228c
            charge(ctx, 5);
            v0 = addiu(v1, 2);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        }
        // 0x004022ac
        charge(ctx, 18);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        a0 = s0;
        jal(ctx, 0x4022B8u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
        sb(v0, s4, order::kMonth);
        a0 = s0;
        jal(ctx, 0x4022C8u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
        sb(v0, s4, order::kDay);
        lh(v0, s4, order::kFlags);
        v0 = v0 | 0x1;
        sh(v0, s4, order::kFlags);
        lhu(a0, s4, order::kItem);
        jal(ctx, 0x4022E4u, gen::fn_sub_401800_00401800);
        if (v0 != 0) {
            // 0x004022f4
            charge(ctx, 5);
            a0 = v0;
            jal(ctx, 0x4022F8u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                goto L_00402314;
            }
            // 0x00402308
            charge(ctx, 3);
            v0 = 1;
            goto L_00402318;
        }
    L_00402314:
        charge(ctx, 1);
        v0 = 0;
    L_00402318:
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x004023b4: level / 5 + 1
            charge(ctx, 6);
            lbu(v1, s3, persona::kLevel);
            v0 = 5;
            div(v1, v0);
            mflo(v0);
            v0 = addiu(v0, 1);
            sw(v0, s4, order::kValue);
        } else {
            // 0x00402320: the item record's value
            charge(ctx, 8);
            lh(a0, s4, order::kItem);
            a1 = addiu(sp, 0xAC);
            jal(ctx, 0x402328u, gen::fn_sub_170ED0_00170ed0);
            lw(a0, sp, 0xAC);
            v1 = 4;
            if (a0 == v1) {
                // 0x004023a4
                charge(ctx, 1);
                lw(s5, v0, 24);
            } else {
                // 0x00402340
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x00402398
                    charge(ctx, 3);
                    lw(s5, v0, 32);
                } else {
                    // 0x0040234c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x0040238c
                        charge(ctx, 3);
                        lw(s5, v0, 28);
                    } else {
                        // 0x00402358
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x00402380
                            charge(ctx, 3);
                            lw(s5, v0, 28);
                        } else {
                            // 0x00402364
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x00402374
                                charge(ctx, 3);
                                lw(s5, v0, 36);
                            } else {
                                // 0x0040236c
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
            // 0x004023a8
            charge(ctx, 3);
            sw(s5, s4, order::kValue);
        }
        // 0x004023cc
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x00402108
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004023d0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
    return;
L_00401e88_6:
    charge(ctx, 3);
    lhu(v1, a0, 2);
    goto L_00401ea8;
L_00401f34_16:
    charge(ctx, 3);
    a0 = 1;
    goto L_00401fa8;
L_00402018_31:
    charge(ctx, 3);
    lhu(v1, a2, 2);
    goto L_0040203c;
L_004020dc_43:
    charge(ctx, 2);
    goto L_00402100;
}

// 0x00402400 sub_402400 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclFusionOrderItem] The shop item entry a1 of order a0: the item, count 1, the order's bytes +13 / +12 at +9 / +8, the
// category of its record word, +12 = 1 and the two values (+14 / +16 at +16 / +18).
void sub_402400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00402400
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lhu(v0, a0, order::kItem);
    sh(v0, a1, item::kId);
    v0 = 1;
    sh(v0, a1, item::kCount);
    lbu(v0, a0, order::kByte13);
    sb(v0, a1, item::kEquip);
    lbu(v0, a0, order::kByte12);
    sb(v0, a1, item::kKind);
    lw(a0, a0, order::kRaw);
    jal(ctx, 0x40243Cu, gen::fn_sub_3F1A10_003f1a10);
    sw(v0, s0, item::kCategory);
    v1 = 1;
    sw(v1, s0, item::kPrice);
    lhu(v1, s1, order::kStatA);
    sh(v1, s0, item::kStatA);
    lhu(v1, s1, order::kStatB);
    sh(v1, s0, item::kStatB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00402510 sub_402510 -- 408 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopSlotHolds] Does inventory slot a3 hold item a0 under the options a2? (a1 = the member, -1: the item's own,
// sub_171250): the slot's item (sub_16F630(1, slot)) must be a0; unless option 8 the slot must not be the member's equipped
// one (datGetEquipmentIdx); unless option 2 the slot's byte (sub_16F810) must equal a0 >> 24 & 15 (option 1: at most it);
// unless option 4 the byte of sub_16F900 must equal a0 >> 16 & 0xFF. Returns 1 / 0.
void sub_402510(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00402510
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    v0 = si(-1);
    if (s2 == v0) {
        // 0x00402548: no member given: the item's own
        charge(ctx, 6);
        v0 = s3 & 0xFFFF;
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x402554u, gen::fn_sub_171250_00171250);
        s2 = v0;
    }
    // 0x00402560
    charge(ctx, 8);
    s4 = s3 & 0xFFFF;
    a0 = 1;
    a1 = s0;
    jal(ctx, 0x40256Cu, gen::fn_sub_16F630_0016f630);
    v0 = v0 & 0xFFFF;
    if (s4 != v0) {
        // 0x00402680
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00402580
        charge(ctx, 3);
        v0 = s1 & 0x8;
        if (v0 == 0) {
            // 0x0040258c
            charge(ctx, 9);
            a1 = dsll32(s2, 16);
            a1 = dsra32(a1, 16);
            a0 = 1;
            jal(ctx, 0x402598u, gen::fn_datGetEquipmentIdx_0016cb80);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (s0 != v0) {
                goto L_004025bc;
            }
            // 0x004025b0
            charge(ctx, 3);
            v0 = 0;
            // 0x00402684 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004025bc:
        charge(ctx, 3);
        v0 = s1 & 0x2;
        if (v0 == 0) {
            // 0x004025c8
            charge(ctx, 9);
            v0 = sra(s3, 24);
            s2 = v0 & 0xF;
            a0 = 1;
            a1 = s0;
            jal(ctx, 0x4025D8u, gen::fn_sub_16F810_0016f810);
            v0 = v0 & 0xFF;
            if (s2 == v0) {
                goto L_004025f8;
            }
            // 0x004025ec
            charge(ctx, 3);
            v0 = 0;
            // 0x00402684 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004025f8:
        charge(ctx, 3);
        v0 = s1 & 0x4;
        if (v0 == 0) {
            // 0x00402604
            charge(ctx, 9);
            v0 = sra(s3, 16);
            s2 = v0 & 0xFF;
            a0 = 1;
            a1 = s0;
            jal(ctx, 0x402614u, gen::fn_sub_16F900_0016f900);
            v0 = v0 & 0xFF;
            if (s2 == v0) {
                goto L_00402634;
            }
            // 0x00402628
            charge(ctx, 3);
            v0 = 0;
            // 0x00402684 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00402634:
        charge(ctx, 3);
        v0 = s1 & 0x1;
        if (v0 != 0) {
            // 0x00402640
            charge(ctx, 10);
            a0 = 1;
            a1 = s0;
            jal(ctx, 0x402648u, gen::fn_sub_16F810_0016f810);
            v1 = v0 & 0xFF;
            v0 = sra(s3, 24);
            v0 = v0 & 0xF;
            at = slt(v0, v1);
            if (at == 0) {
                goto L_00402674;
            }
            // 0x00402668
            charge(ctx, 3);
            v0 = 0;
            // 0x00402684 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00402674:
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00402684 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004032F0 sub_4032F0 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclQuestAccept] Accepts request a0: sets its game flag (sub_404470(id, 1)) and records it (sub_17C4E0).
void sub_4032F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004032f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = 1;
    jal(ctx, 0x40330Cu, gen::fn_sub_404470_00404470);
    a0 = s0;
    jal(ctx, 0x403318u, gen::fn_sub_17C4E0_0017c4e0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00403340 sub_403340 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclQuestCancel] Cancels request a0: drops the record (sub_17C590) and clears its game flag (sub_404470(id, 0)).
void sub_403340(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403340
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x403350u, gen::fn_sub_17C590_0017c590);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    jal(ctx, 0x403364u, gen::fn_sub_404470_00404470);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00403410 sub_403410 -- 272 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclQuestDeadline] The deadline state of request a0 from its condition block (sub_4037E0): kind (+7 >> 4) 0 -> 3 (no
// deadline); kind 1 -> the date +6 (bits 6..11 month, 0..5 day); kind 2 -> the date +4 plus the day count of +6's low 12
// bits; then 2 when today is that day, 1 when today is before it, 0 after.
void sub_403410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00403410
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x403424u, gen::fn_sub_4037E0_004037e0);
    s0 = v0;
    lb(v0, v0, qcond::kKind);
    v0 = dsll32(v0, 24);
    v1 = dsra32(v0, 28);
    v0 = 2;
    if (v1 == v0) {
        // 0x004034ac: kind 2: a date plus a day count
        charge(ctx, 16);
        jal(ctx, 0x4034ACu, gen::fn_datGetDaysSinceApr5_0016ef20);
        s2 = dsll32(v0, 16);
        s2 = dsra32(s2, 16);
        lh(v0, s0, qcond::kDateA);
        v0 = dsll32(v0, 20);
        a0 = dsra32(v0, 26);
        lb(v0, s0, qcond::kDateA);
        a1 = dsll32(v0, 26);
        a1 = dsra32(a1, 26);
        jal(ctx, 0x4034D4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
        lh(v1, s0, qcond::kDateB);
        v1 = dsll32(v1, 20);
        v1 = dsra32(v1, 20);
        s1 = addu(v1, v0);
    L_004034ec:
        charge(ctx, 2);
        if (s2 != s1) {
            // 0x00403500: before: 1, after: 0
            charge(ctx, 1);
            v0 = slt(s2, s1);
        } else {
            // 0x004034f4: today is the day: 2
            charge(ctx, 3);
            v0 = 2;
        }
    } else {
        // 0x00403448
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00403470: kind 1: a date
            charge(ctx, 15);
            jal(ctx, 0x403470u, gen::fn_datGetDaysSinceApr5_0016ef20);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
            lh(v0, s0, qcond::kDateB);
            v0 = dsll32(v0, 20);
            a0 = dsra32(v0, 26);
            lb(v0, s0, qcond::kDateB);
            a1 = dsll32(v0, 26);
            a1 = dsra32(a1, 26);
            jal(ctx, 0x403498u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
            s1 = v0;
            goto L_004034ec;
        }
        // 0x00403454
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x0040345c
            charge(ctx, 2);
            goto L_004034ec;
        }
        // 0x00403464: kind 0: no deadline (3)
        charge(ctx, 3);
        v0 = 3;
    }
    // 0x00403504 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00403760 sub_403760 -- 32 bytes; leaf frame (no stack)
// [fclQuestGet48] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): s16 +48.
void sub_403760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403760
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(v0, v0, quest::kHalf48);
}

// 0x00403780 sub_403780 -- 32 bytes; leaf frame (no stack)
// [fclQuestGet50] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): s16 +50.
void sub_403780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403780
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(v0, v0, quest::kHalf50);
}

// 0x004037A0 sub_4037A0 -- 32 bytes; leaf frame (no stack)
// [fclQuestGet54] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): s16 +54.
void sub_4037A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004037a0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(v0, v0, quest::kHalf54);
}

// 0x004037C0 sub_4037C0 -- 32 bytes; leaf frame (no stack)
// [fclQuestGet52] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): s16 +52.
void sub_4037C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004037c0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lh(v0, v0, quest::kHalf52);
}

// 0x004037E0 sub_4037E0 -- 32 bytes; leaf frame (no stack)
// [fclQuestGetCond] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): the address of the condition block +8.
void sub_4037E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004037e0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    v0 = addiu(v0, 8);
}

// 0x00403860 sub_403860 -- 32 bytes; leaf frame (no stack)
// [fclQuestGetBlock16] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): the address of +16.
void sub_403860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00403860
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v1 = sll(v0, 6);
    lw(v0, gp, -21504);  // 0x7CD8F0
    v0 = addu(v0, v1);
    v0 = addiu(v0, 16);
}

// 0x004038E0 sub_4038E0 -- 32 bytes; leaf frame (no stack)
// [fclQuestGet44] Quest record accessor (the 64-byte records at *(gp - 21504) = 0x7CD8F0 -> 0x6AD4C0, index a0): the word +44.
void sub_4038E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004038e0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -21504);  // 0x7CD8F0
    v0 = dsll32(a0, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 6);
    v0 = addu(v0, v1);
    lw(v0, v0, quest::kWord44);
}

// 0x00404470 sub_404470 -- 68 bytes; frame 0x10: ra sp+0x0
// [fclQuestSetFlag] Sets (a1 = 1) or clears request a0's game flag (+20) unless it is 0xFFFF.
void sub_404470(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00404470
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    a0 = sll(v1, 6);
    lw(v1, gp, -21504);  // 0x7CD8F0
    v1 = addu(v1, a0);
    lhu(a0, v1, quest::kFlag);
    v1 = 0xFFFF;
    if (a0 != v1) {
        // 0x0040449c
        charge(ctx, 2);
        jal(ctx, 0x40449Cu, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x004044a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00404750 sub_404750 -- 4632 bytes; frame 0x2230: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclQuestListAnim] The request list's element animations (the QUEST / QUESTCANCEL lists): a0 -> the list, a1 = the part 0..7
// (jump table 0x7BBDE0), a2 = 0 in / 1 out. Each case copies the eighteen 28-byte templates of 0x6AF3E0 (63 x 8 bytes) to
// the stack, takes the part's template and starts the element with its id (sub_3DFFC0 / sub_3DF100) -- part 0: every row's
// element 0 (in and out); part 1: every row's element 0 in, the cursor row's element 1 out; parts 2..7: the window element
// set's (user +8) element of that part. The 0x2230-byte frame holds one template copy per call site.
void sub_404750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00404750
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2230);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, lst::kState);
    lw(t0, v1, 68);
    at = sltiu(a1, 8);
    if (at != 0) {
        // 0x00404774
        charge(ctx, 7);
        a3 = 0x7C0000;
        a3 = addiu(a3, -16928);  // &0x7BBDE0
        v1 = sll(a1, 2);
        v1 = addu(v1, a3);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x404790u:  // table[0]
            // 0x00404790: part 0
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x004048c0
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x004048cc
                    charge(ctx, 3);
                    lw(s0, a0, lst::kHead);
                    for (;;) {
                        // 0x004049e4
                        charge(ctx, 2);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x004048d8
                        charge(ctx, 7);
                        lw(v0, s0, node::kPayload);
                        lw(v0, v0, 28);
                        lw(s1, v0, 8);
                        a2 = 0x6B0000;
                        a2 = addiu(a2, -3104);  // &0x6AF3E0
                        a1 = addiu(sp, 0x1C30);
                        a0 = 63;
                        for (;;) {
                            // 0x004048f4
                            charge(ctx, 9);
                            lw(v1, a2, 0);
                            lw(v0, a2, 4);
                            a2 = addiu(a2, 8);
                            a0 = addiu(a0, -1);
                            sw(v1, a1, 0);
                            sw(v0, a1, 4);
                            a1 = addiu(a1, 8);
                            if (i64(a0) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00404918
                        charge(ctx, 51);
                        sw(zero, sp, 0x1C30);
                        sh(zero, sp, 0x1C48);
                        sw(zero, sp, 0x1C4C);
                        sh(zero, sp, 0x1C64);
                        sw(zero, sp, 0x1C68);
                        sh(zero, sp, 0x1C80);
                        sw(zero, sp, 0x1C84);
                        sh(zero, sp, 0x1C9C);
                        sw(zero, sp, 0x1CA0);
                        sh(zero, sp, 0x1CB8);
                        sw(zero, sp, 0x1CBC);
                        sh(zero, sp, 0x1CD4);
                        sw(zero, sp, 0x1CD8);
                        sh(zero, sp, 0x1CF0);
                        sw(zero, sp, 0x1CF4);
                        sh(zero, sp, 0x1D0C);
                        sw(zero, sp, 0x1D10);
                        sh(zero, sp, 0x1D28);
                        sw(zero, sp, 0x1D2C);
                        sh(zero, sp, 0x1D44);
                        sw(zero, sp, 0x1D48);
                        sh(zero, sp, 0x1D60);
                        sw(zero, sp, 0x1D64);
                        sh(zero, sp, 0x1D7C);
                        sw(zero, sp, 0x1D80);
                        sh(zero, sp, 0x1D98);
                        sw(zero, sp, 0x1D9C);
                        sh(zero, sp, 0x1DB4);
                        sw(zero, sp, 0x1DB8);
                        sh(zero, sp, 0x1DD0);
                        sw(zero, sp, 0x1DD4);
                        sh(zero, sp, 0x1DEC);
                        sw(zero, sp, 0x1DF0);
                        sh(zero, sp, 0x1E08);
                        sw(zero, sp, 0x1E0C);
                        sh(zero, sp, 0x1E24);
                        a0 = addiu(sp, 0x21F0);
                        a1 = addiu(sp, 0x1C4C);
                        a2 = 28;
                        jal(ctx, 0x4049B4u, gen::fn_memcpy_00521250);
                        lw(a2, sp, 0x21F4);
                        a0 = s1;
                        a1 = 0;
                        jal(ctx, 0x4049C8u, gen::fn_sub_3DFFC0_003dffc0);
                        a0 = v0;
                        a1 = addiu(sp, 0x21F0);
                        jal(ctx, 0x4049D8u, gen::fn_sub_3DF100_003df100);
                        lw(s0, s0, node::kNext);
                    }
                    // 0x004049ec
                    charge(ctx, 2);
                }
            } else {
                // 0x00404798
                charge(ctx, 3);
                lw(s1, a0, lst::kHead);
                for (;;) {
                    // 0x004048b0
                    charge(ctx, 2);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004047a4
                    charge(ctx, 7);
                    lw(v0, s1, node::kPayload);
                    lw(v0, v0, 28);
                    lw(s0, v0, 8);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x1E30);
                    a0 = 63;
                    for (;;) {
                        // 0x004047c0
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004047e4
                    charge(ctx, 51);
                    sw(zero, sp, 0x1E30);
                    sh(zero, sp, 0x1E48);
                    sw(zero, sp, 0x1E4C);
                    sh(zero, sp, 0x1E64);
                    sw(zero, sp, 0x1E68);
                    sh(zero, sp, 0x1E80);
                    sw(zero, sp, 0x1E84);
                    sh(zero, sp, 0x1E9C);
                    sw(zero, sp, 0x1EA0);
                    sh(zero, sp, 0x1EB8);
                    sw(zero, sp, 0x1EBC);
                    sh(zero, sp, 0x1ED4);
                    sw(zero, sp, 0x1ED8);
                    sh(zero, sp, 0x1EF0);
                    sw(zero, sp, 0x1EF4);
                    sh(zero, sp, 0x1F0C);
                    sw(zero, sp, 0x1F10);
                    sh(zero, sp, 0x1F28);
                    sw(zero, sp, 0x1F2C);
                    sh(zero, sp, 0x1F44);
                    sw(zero, sp, 0x1F48);
                    sh(zero, sp, 0x1F60);
                    sw(zero, sp, 0x1F64);
                    sh(zero, sp, 0x1F7C);
                    sw(zero, sp, 0x1F80);
                    sh(zero, sp, 0x1F98);
                    sw(zero, sp, 0x1F9C);
                    sh(zero, sp, 0x1FB4);
                    sw(zero, sp, 0x1FB8);
                    sh(zero, sp, 0x1FD0);
                    sw(zero, sp, 0x1FD4);
                    sh(zero, sp, 0x1FEC);
                    sw(zero, sp, 0x1FF0);
                    sh(zero, sp, 0x2008);
                    sw(zero, sp, 0x200C);
                    sh(zero, sp, 0x2024);
                    a0 = addiu(sp, 0x2210);
                    a1 = addiu(sp, 0x1E30);
                    a2 = 28;
                    jal(ctx, 0x404880u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x2214);
                    a0 = s0;
                    a1 = 0;
                    jal(ctx, 0x404894u, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x2210);
                    jal(ctx, 0x4048A4u, gen::fn_sub_3DF100_003df100);
                    lw(s1, s1, node::kNext);
                }
                // 0x004048b8
                charge(ctx, 2);
            }
            break;
        case 0x4049F4u:  // table[1]
            // 0x004049f4: part 1
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x00404b24
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x00404b30
                    charge(ctx, 3);
                    lw(v1, a0, lst::kCursor);
                    if (v1 != 0) {
                        // 0x00404b3c
                        charge(ctx, 7);
                        lw(v0, v1, 20);
                        lw(v0, v0, 28);
                        lw(s0, v0, 8);
                        a2 = 0x6B0000;
                        a2 = addiu(a2, -3104);  // &0x6AF3E0
                        a1 = addiu(sp, 0x1830);
                        a0 = 63;
                        for (;;) {
                            // 0x00404b58
                            charge(ctx, 9);
                            lw(v1, a2, 0);
                            lw(v0, a2, 4);
                            a2 = addiu(a2, 8);
                            a0 = addiu(a0, -1);
                            sw(v1, a1, 0);
                            sw(v0, a1, 4);
                            a1 = addiu(a1, 8);
                            if (i64(a0) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00404b7c
                        charge(ctx, 53);
                        v0 = 1;
                        sw(v0, sp, 0x1830);
                        sh(zero, sp, 0x1848);
                        sw(v0, sp, 0x184C);
                        sh(zero, sp, 0x1864);
                        sw(v0, sp, 0x1868);
                        sh(zero, sp, 0x1880);
                        sw(v0, sp, 0x1884);
                        sh(zero, sp, 0x189C);
                        sw(v0, sp, 0x18A0);
                        sh(zero, sp, 0x18B8);
                        sw(v0, sp, 0x18BC);
                        sh(zero, sp, 0x18D4);
                        sw(v0, sp, 0x18D8);
                        sh(zero, sp, 0x18F0);
                        sw(v0, sp, 0x18F4);
                        sh(zero, sp, 0x190C);
                        sw(v0, sp, 0x1910);
                        sh(zero, sp, 0x1928);
                        sw(v0, sp, 0x192C);
                        sh(zero, sp, 0x1944);
                        sw(v0, sp, 0x1948);
                        sh(zero, sp, 0x1960);
                        sw(v0, sp, 0x1964);
                        sh(zero, sp, 0x197C);
                        sw(v0, sp, 0x1980);
                        sh(zero, sp, 0x1998);
                        sw(v0, sp, 0x199C);
                        sh(zero, sp, 0x19B4);
                        sw(v0, sp, 0x19B8);
                        sh(zero, sp, 0x19D0);
                        sw(v0, sp, 0x19D4);
                        sh(zero, sp, 0x19EC);
                        sw(v0, sp, 0x19F0);
                        sh(zero, sp, 0x1A08);
                        sw(v0, sp, 0x1A0C);
                        sh(zero, sp, 0x1A24);
                        a0 = addiu(sp, 0x21B0);
                        a1 = addiu(sp, 0x1884);
                        a2 = 28;
                        jal(ctx, 0x404C1Cu, gen::fn_memcpy_00521250);
                        lw(a2, sp, 0x21B4);
                        a0 = s0;
                        a1 = 1;
                        jal(ctx, 0x404C30u, gen::fn_sub_3DFFC0_003dffc0);
                        a0 = v0;
                        a1 = addiu(sp, 0x21B0);
                        jal(ctx, 0x404C40u, gen::fn_sub_3DF100_003df100);
                    }
                }
            } else {
                // 0x004049fc
                charge(ctx, 3);
                lw(s0, a0, lst::kHead);
                for (;;) {
                    // 0x00404b14
                    charge(ctx, 2);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00404a08
                    charge(ctx, 7);
                    lw(v0, s0, node::kPayload);
                    lw(v0, v0, 28);
                    lw(s1, v0, 8);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x1A30);
                    a0 = 63;
                    for (;;) {
                        // 0x00404a24
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00404a48
                    charge(ctx, 51);
                    sw(zero, sp, 0x1A30);
                    sh(zero, sp, 0x1A48);
                    sw(zero, sp, 0x1A4C);
                    sh(zero, sp, 0x1A64);
                    sw(zero, sp, 0x1A68);
                    sh(zero, sp, 0x1A80);
                    sw(zero, sp, 0x1A84);
                    sh(zero, sp, 0x1A9C);
                    sw(zero, sp, 0x1AA0);
                    sh(zero, sp, 0x1AB8);
                    sw(zero, sp, 0x1ABC);
                    sh(zero, sp, 0x1AD4);
                    sw(zero, sp, 0x1AD8);
                    sh(zero, sp, 0x1AF0);
                    sw(zero, sp, 0x1AF4);
                    sh(zero, sp, 0x1B0C);
                    sw(zero, sp, 0x1B10);
                    sh(zero, sp, 0x1B28);
                    sw(zero, sp, 0x1B2C);
                    sh(zero, sp, 0x1B44);
                    sw(zero, sp, 0x1B48);
                    sh(zero, sp, 0x1B60);
                    sw(zero, sp, 0x1B64);
                    sh(zero, sp, 0x1B7C);
                    sw(zero, sp, 0x1B80);
                    sh(zero, sp, 0x1B98);
                    sw(zero, sp, 0x1B9C);
                    sh(zero, sp, 0x1BB4);
                    sw(zero, sp, 0x1BB8);
                    sh(zero, sp, 0x1BD0);
                    sw(zero, sp, 0x1BD4);
                    sh(zero, sp, 0x1BEC);
                    sw(zero, sp, 0x1BF0);
                    sh(zero, sp, 0x1C08);
                    sw(zero, sp, 0x1C0C);
                    sh(zero, sp, 0x1C24);
                    a0 = addiu(sp, 0x21D0);
                    a1 = addiu(sp, 0x1A30);
                    a2 = 28;
                    jal(ctx, 0x404AE4u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x21D4);
                    a0 = s1;
                    a1 = 0;
                    jal(ctx, 0x404AF8u, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x21D0);
                    jal(ctx, 0x404B08u, gen::fn_sub_3DF100_003df100);
                    lw(s0, s0, node::kNext);
                }
                // 0x00404b1c
                charge(ctx, 2);
            }
            break;
        case 0x404C50u:  // table[2]
            // 0x00404c50: part 2
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x00404d64
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x00404d70
                    charge(ctx, 5);
                    lw(s0, t0, menu::kElems);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x1430);
                    a0 = 63;
                    for (;;) {
                        // 0x00404d84
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00404da8
                    charge(ctx, 53);
                    v0 = 2;
                    sw(v0, sp, 0x1430);
                    sh(zero, sp, 0x1448);
                    sw(v0, sp, 0x144C);
                    sh(zero, sp, 0x1464);
                    sw(v0, sp, 0x1468);
                    sh(zero, sp, 0x1480);
                    sw(v0, sp, 0x1484);
                    sh(zero, sp, 0x149C);
                    sw(v0, sp, 0x14A0);
                    sh(zero, sp, 0x14B8);
                    sw(v0, sp, 0x14BC);
                    sh(zero, sp, 0x14D4);
                    sw(v0, sp, 0x14D8);
                    sh(zero, sp, 0x14F0);
                    sw(v0, sp, 0x14F4);
                    sh(zero, sp, 0x150C);
                    sw(v0, sp, 0x1510);
                    sh(zero, sp, 0x1528);
                    sw(v0, sp, 0x152C);
                    sh(zero, sp, 0x1544);
                    sw(v0, sp, 0x1548);
                    sh(zero, sp, 0x1560);
                    sw(v0, sp, 0x1564);
                    sh(zero, sp, 0x157C);
                    sw(v0, sp, 0x1580);
                    sh(zero, sp, 0x1598);
                    sw(v0, sp, 0x159C);
                    sh(zero, sp, 0x15B4);
                    sw(v0, sp, 0x15B8);
                    sh(zero, sp, 0x15D0);
                    sw(v0, sp, 0x15D4);
                    sh(zero, sp, 0x15EC);
                    sw(v0, sp, 0x15F0);
                    sh(zero, sp, 0x1608);
                    sw(v0, sp, 0x160C);
                    sh(zero, sp, 0x1624);
                    a0 = addiu(sp, 0x2170);
                    a1 = addiu(sp, 0x14BC);
                    a2 = 28;
                    jal(ctx, 0x404E48u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x2174);
                    a0 = s0;
                    a1 = 2;
                    jal(ctx, 0x404E5Cu, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x2170);
                    jal(ctx, 0x404E6Cu, gen::fn_sub_3DF100_003df100);
                }
            } else {
                // 0x00404c58
                charge(ctx, 5);
                lw(s0, t0, menu::kElems);
                a2 = 0x6B0000;
                a2 = addiu(a2, -3104);  // &0x6AF3E0
                a1 = addiu(sp, 0x1630);
                a0 = 63;
                for (;;) {
                    // 0x00404c6c
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00404c90
                charge(ctx, 53);
                v0 = 2;
                sw(v0, sp, 0x1630);
                sh(zero, sp, 0x1648);
                sw(v0, sp, 0x164C);
                sh(zero, sp, 0x1664);
                sw(v0, sp, 0x1668);
                sh(zero, sp, 0x1680);
                sw(v0, sp, 0x1684);
                sh(zero, sp, 0x169C);
                sw(v0, sp, 0x16A0);
                sh(zero, sp, 0x16B8);
                sw(v0, sp, 0x16BC);
                sh(zero, sp, 0x16D4);
                sw(v0, sp, 0x16D8);
                sh(zero, sp, 0x16F0);
                sw(v0, sp, 0x16F4);
                sh(zero, sp, 0x170C);
                sw(v0, sp, 0x1710);
                sh(zero, sp, 0x1728);
                sw(v0, sp, 0x172C);
                sh(zero, sp, 0x1744);
                sw(v0, sp, 0x1748);
                sh(zero, sp, 0x1760);
                sw(v0, sp, 0x1764);
                sh(zero, sp, 0x177C);
                sw(v0, sp, 0x1780);
                sh(zero, sp, 0x1798);
                sw(v0, sp, 0x179C);
                sh(zero, sp, 0x17B4);
                sw(v0, sp, 0x17B8);
                sh(zero, sp, 0x17D0);
                sw(v0, sp, 0x17D4);
                sh(zero, sp, 0x17EC);
                sw(v0, sp, 0x17F0);
                sh(zero, sp, 0x1808);
                sw(v0, sp, 0x180C);
                sh(zero, sp, 0x1824);
                a0 = addiu(sp, 0x2190);
                a1 = addiu(sp, 0x16A0);
                a2 = 28;
                jal(ctx, 0x404D30u, gen::fn_memcpy_00521250);
                lw(a2, sp, 0x2194);
                a0 = s0;
                a1 = 2;
                jal(ctx, 0x404D44u, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0x2190);
                jal(ctx, 0x404D54u, gen::fn_sub_3DF100_003df100);
            }
            break;
        case 0x404E7Cu:  // table[3]
            // 0x00404e7c: part 3
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x00404f90
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x00404f9c
                    charge(ctx, 5);
                    lw(s0, t0, menu::kElems);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x1030);
                    a0 = 63;
                    for (;;) {
                        // 0x00404fb0
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00404fd4
                    charge(ctx, 53);
                    v0 = 3;
                    sw(v0, sp, 0x1030);
                    sh(zero, sp, 0x1048);
                    sw(v0, sp, 0x104C);
                    sh(zero, sp, 0x1064);
                    sw(v0, sp, 0x1068);
                    sh(zero, sp, 0x1080);
                    sw(v0, sp, 0x1084);
                    sh(zero, sp, 0x109C);
                    sw(v0, sp, 0x10A0);
                    sh(zero, sp, 0x10B8);
                    sw(v0, sp, 0x10BC);
                    sh(zero, sp, 0x10D4);
                    sw(v0, sp, 0x10D8);
                    sh(zero, sp, 0x10F0);
                    sw(v0, sp, 0x10F4);
                    sh(zero, sp, 0x110C);
                    sw(v0, sp, 0x1110);
                    sh(zero, sp, 0x1128);
                    sw(v0, sp, 0x112C);
                    sh(zero, sp, 0x1144);
                    sw(v0, sp, 0x1148);
                    sh(zero, sp, 0x1160);
                    sw(v0, sp, 0x1164);
                    sh(zero, sp, 0x117C);
                    sw(v0, sp, 0x1180);
                    sh(zero, sp, 0x1198);
                    sw(v0, sp, 0x119C);
                    sh(zero, sp, 0x11B4);
                    sw(v0, sp, 0x11B8);
                    sh(zero, sp, 0x11D0);
                    sw(v0, sp, 0x11D4);
                    sh(zero, sp, 0x11EC);
                    sw(v0, sp, 0x11F0);
                    sh(zero, sp, 0x1208);
                    sw(v0, sp, 0x120C);
                    sh(zero, sp, 0x1224);
                    a0 = addiu(sp, 0x2130);
                    a1 = addiu(sp, 0x10F4);
                    a2 = 28;
                    jal(ctx, 0x405074u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x2134);
                    a0 = s0;
                    a1 = 3;
                    jal(ctx, 0x405088u, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x2130);
                    jal(ctx, 0x405098u, gen::fn_sub_3DF100_003df100);
                }
            } else {
                // 0x00404e84
                charge(ctx, 5);
                lw(s0, t0, menu::kElems);
                a2 = 0x6B0000;
                a2 = addiu(a2, -3104);  // &0x6AF3E0
                a1 = addiu(sp, 0x1230);
                a0 = 63;
                for (;;) {
                    // 0x00404e98
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00404ebc
                charge(ctx, 53);
                v0 = 3;
                sw(v0, sp, 0x1230);
                sh(zero, sp, 0x1248);
                sw(v0, sp, 0x124C);
                sh(zero, sp, 0x1264);
                sw(v0, sp, 0x1268);
                sh(zero, sp, 0x1280);
                sw(v0, sp, 0x1284);
                sh(zero, sp, 0x129C);
                sw(v0, sp, 0x12A0);
                sh(zero, sp, 0x12B8);
                sw(v0, sp, 0x12BC);
                sh(zero, sp, 0x12D4);
                sw(v0, sp, 0x12D8);
                sh(zero, sp, 0x12F0);
                sw(v0, sp, 0x12F4);
                sh(zero, sp, 0x130C);
                sw(v0, sp, 0x1310);
                sh(zero, sp, 0x1328);
                sw(v0, sp, 0x132C);
                sh(zero, sp, 0x1344);
                sw(v0, sp, 0x1348);
                sh(zero, sp, 0x1360);
                sw(v0, sp, 0x1364);
                sh(zero, sp, 0x137C);
                sw(v0, sp, 0x1380);
                sh(zero, sp, 0x1398);
                sw(v0, sp, 0x139C);
                sh(zero, sp, 0x13B4);
                sw(v0, sp, 0x13B8);
                sh(zero, sp, 0x13D0);
                sw(v0, sp, 0x13D4);
                sh(zero, sp, 0x13EC);
                sw(v0, sp, 0x13F0);
                sh(zero, sp, 0x1408);
                sw(v0, sp, 0x140C);
                sh(zero, sp, 0x1424);
                a0 = addiu(sp, 0x2150);
                a1 = addiu(sp, 0x12D8);
                a2 = 28;
                jal(ctx, 0x404F5Cu, gen::fn_memcpy_00521250);
                lw(a2, sp, 0x2154);
                a0 = s0;
                a1 = 3;
                jal(ctx, 0x404F70u, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0x2150);
                jal(ctx, 0x404F80u, gen::fn_sub_3DF100_003df100);
            }
            break;
        case 0x4050A8u:  // table[4]
            // 0x004050a8: part 4
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x004051bc
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x004051c8
                    charge(ctx, 5);
                    lw(s0, t0, menu::kElems);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0xC30);
                    a0 = 63;
                    for (;;) {
                        // 0x004051dc
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00405200
                    charge(ctx, 53);
                    v0 = 4;
                    sw(v0, sp, 0xC30);
                    sh(zero, sp, 0xC48);
                    sw(v0, sp, 0xC4C);
                    sh(zero, sp, 0xC64);
                    sw(v0, sp, 0xC68);
                    sh(zero, sp, 0xC80);
                    sw(v0, sp, 0xC84);
                    sh(zero, sp, 0xC9C);
                    sw(v0, sp, 0xCA0);
                    sh(zero, sp, 0xCB8);
                    sw(v0, sp, 0xCBC);
                    sh(zero, sp, 0xCD4);
                    sw(v0, sp, 0xCD8);
                    sh(zero, sp, 0xCF0);
                    sw(v0, sp, 0xCF4);
                    sh(zero, sp, 0xD0C);
                    sw(v0, sp, 0xD10);
                    sh(zero, sp, 0xD28);
                    sw(v0, sp, 0xD2C);
                    sh(zero, sp, 0xD44);
                    sw(v0, sp, 0xD48);
                    sh(zero, sp, 0xD60);
                    sw(v0, sp, 0xD64);
                    sh(zero, sp, 0xD7C);
                    sw(v0, sp, 0xD80);
                    sh(zero, sp, 0xD98);
                    sw(v0, sp, 0xD9C);
                    sh(zero, sp, 0xDB4);
                    sw(v0, sp, 0xDB8);
                    sh(zero, sp, 0xDD0);
                    sw(v0, sp, 0xDD4);
                    sh(zero, sp, 0xDEC);
                    sw(v0, sp, 0xDF0);
                    sh(zero, sp, 0xE08);
                    sw(v0, sp, 0xE0C);
                    sh(zero, sp, 0xE24);
                    a0 = addiu(sp, 0x20F0);
                    a1 = addiu(sp, 0xD2C);
                    a2 = 28;
                    jal(ctx, 0x4052A0u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x20F4);
                    a0 = s0;
                    a1 = 4;
                    jal(ctx, 0x4052B4u, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x20F0);
                    jal(ctx, 0x4052C4u, gen::fn_sub_3DF100_003df100);
                }
            } else {
                // 0x004050b0
                charge(ctx, 5);
                lw(s0, t0, menu::kElems);
                a2 = 0x6B0000;
                a2 = addiu(a2, -3104);  // &0x6AF3E0
                a1 = addiu(sp, 0xE30);
                a0 = 63;
                for (;;) {
                    // 0x004050c4
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004050e8
                charge(ctx, 53);
                v0 = 4;
                sw(v0, sp, 0xE30);
                sh(zero, sp, 0xE48);
                sw(v0, sp, 0xE4C);
                sh(zero, sp, 0xE64);
                sw(v0, sp, 0xE68);
                sh(zero, sp, 0xE80);
                sw(v0, sp, 0xE84);
                sh(zero, sp, 0xE9C);
                sw(v0, sp, 0xEA0);
                sh(zero, sp, 0xEB8);
                sw(v0, sp, 0xEBC);
                sh(zero, sp, 0xED4);
                sw(v0, sp, 0xED8);
                sh(zero, sp, 0xEF0);
                sw(v0, sp, 0xEF4);
                sh(zero, sp, 0xF0C);
                sw(v0, sp, 0xF10);
                sh(zero, sp, 0xF28);
                sw(v0, sp, 0xF2C);
                sh(zero, sp, 0xF44);
                sw(v0, sp, 0xF48);
                sh(zero, sp, 0xF60);
                sw(v0, sp, 0xF64);
                sh(zero, sp, 0xF7C);
                sw(v0, sp, 0xF80);
                sh(zero, sp, 0xF98);
                sw(v0, sp, 0xF9C);
                sh(zero, sp, 0xFB4);
                sw(v0, sp, 0xFB8);
                sh(zero, sp, 0xFD0);
                sw(v0, sp, 0xFD4);
                sh(zero, sp, 0xFEC);
                sw(v0, sp, 0xFF0);
                sh(zero, sp, 0x1008);
                sw(v0, sp, 0x100C);
                sh(zero, sp, 0x1024);
                a0 = addiu(sp, 0x2110);
                a1 = addiu(sp, 0xF10);
                a2 = 28;
                jal(ctx, 0x405188u, gen::fn_memcpy_00521250);
                lw(a2, sp, 0x2114);
                a0 = s0;
                a1 = 4;
                jal(ctx, 0x40519Cu, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0x2110);
                jal(ctx, 0x4051ACu, gen::fn_sub_3DF100_003df100);
            }
            break;
        case 0x4052D4u:  // table[5]
            // 0x004052d4: part 5
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x004053e8
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x004053f4
                    charge(ctx, 5);
                    lw(s0, t0, menu::kElems);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x830);
                    a0 = 63;
                    for (;;) {
                        // 0x00405408
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0040542c
                    charge(ctx, 53);
                    v0 = 5;
                    sw(v0, sp, 0x830);
                    sh(zero, sp, 0x848);
                    sw(v0, sp, 0x84C);
                    sh(zero, sp, 0x864);
                    sw(v0, sp, 0x868);
                    sh(zero, sp, 0x880);
                    sw(v0, sp, 0x884);
                    sh(zero, sp, 0x89C);
                    sw(v0, sp, 0x8A0);
                    sh(zero, sp, 0x8B8);
                    sw(v0, sp, 0x8BC);
                    sh(zero, sp, 0x8D4);
                    sw(v0, sp, 0x8D8);
                    sh(zero, sp, 0x8F0);
                    sw(v0, sp, 0x8F4);
                    sh(zero, sp, 0x90C);
                    sw(v0, sp, 0x910);
                    sh(zero, sp, 0x928);
                    sw(v0, sp, 0x92C);
                    sh(zero, sp, 0x944);
                    sw(v0, sp, 0x948);
                    sh(zero, sp, 0x960);
                    sw(v0, sp, 0x964);
                    sh(zero, sp, 0x97C);
                    sw(v0, sp, 0x980);
                    sh(zero, sp, 0x998);
                    sw(v0, sp, 0x99C);
                    sh(zero, sp, 0x9B4);
                    sw(v0, sp, 0x9B8);
                    sh(zero, sp, 0x9D0);
                    sw(v0, sp, 0x9D4);
                    sh(zero, sp, 0x9EC);
                    sw(v0, sp, 0x9F0);
                    sh(zero, sp, 0xA08);
                    sw(v0, sp, 0xA0C);
                    sh(zero, sp, 0xA24);
                    a0 = addiu(sp, 0x20B0);
                    a1 = addiu(sp, 0x964);
                    a2 = 28;
                    jal(ctx, 0x4054CCu, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x20B4);
                    a0 = s0;
                    a1 = 5;
                    jal(ctx, 0x4054E0u, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x20B0);
                    jal(ctx, 0x4054F0u, gen::fn_sub_3DF100_003df100);
                }
            } else {
                // 0x004052dc
                charge(ctx, 5);
                lw(s0, t0, menu::kElems);
                a2 = 0x6B0000;
                a2 = addiu(a2, -3104);  // &0x6AF3E0
                a1 = addiu(sp, 0xA30);
                a0 = 63;
                for (;;) {
                    // 0x004052f0
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00405314
                charge(ctx, 53);
                v0 = 5;
                sw(v0, sp, 0xA30);
                sh(zero, sp, 0xA48);
                sw(v0, sp, 0xA4C);
                sh(zero, sp, 0xA64);
                sw(v0, sp, 0xA68);
                sh(zero, sp, 0xA80);
                sw(v0, sp, 0xA84);
                sh(zero, sp, 0xA9C);
                sw(v0, sp, 0xAA0);
                sh(zero, sp, 0xAB8);
                sw(v0, sp, 0xABC);
                sh(zero, sp, 0xAD4);
                sw(v0, sp, 0xAD8);
                sh(zero, sp, 0xAF0);
                sw(v0, sp, 0xAF4);
                sh(zero, sp, 0xB0C);
                sw(v0, sp, 0xB10);
                sh(zero, sp, 0xB28);
                sw(v0, sp, 0xB2C);
                sh(zero, sp, 0xB44);
                sw(v0, sp, 0xB48);
                sh(zero, sp, 0xB60);
                sw(v0, sp, 0xB64);
                sh(zero, sp, 0xB7C);
                sw(v0, sp, 0xB80);
                sh(zero, sp, 0xB98);
                sw(v0, sp, 0xB9C);
                sh(zero, sp, 0xBB4);
                sw(v0, sp, 0xBB8);
                sh(zero, sp, 0xBD0);
                sw(v0, sp, 0xBD4);
                sh(zero, sp, 0xBEC);
                sw(v0, sp, 0xBF0);
                sh(zero, sp, 0xC08);
                sw(v0, sp, 0xC0C);
                sh(zero, sp, 0xC24);
                a0 = addiu(sp, 0x20D0);
                a1 = addiu(sp, 0xB48);
                a2 = 28;
                jal(ctx, 0x4053B4u, gen::fn_memcpy_00521250);
                lw(a2, sp, 0x20D4);
                a0 = s0;
                a1 = 5;
                jal(ctx, 0x4053C8u, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0x20D0);
                jal(ctx, 0x4053D8u, gen::fn_sub_3DF100_003df100);
            }
            break;
        case 0x405500u:  // table[6]
            // 0x00405500: part 6
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x00405614
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x00405620
                    charge(ctx, 5);
                    lw(s0, t0, menu::kElems);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x430);
                    a0 = 63;
                    for (;;) {
                        // 0x00405634
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00405658
                    charge(ctx, 53);
                    v0 = 6;
                    sw(v0, sp, 0x430);
                    sh(zero, sp, 0x448);
                    sw(v0, sp, 0x44C);
                    sh(zero, sp, 0x464);
                    sw(v0, sp, 0x468);
                    sh(zero, sp, 0x480);
                    sw(v0, sp, 0x484);
                    sh(zero, sp, 0x49C);
                    sw(v0, sp, 0x4A0);
                    sh(zero, sp, 0x4B8);
                    sw(v0, sp, 0x4BC);
                    sh(zero, sp, 0x4D4);
                    sw(v0, sp, 0x4D8);
                    sh(zero, sp, 0x4F0);
                    sw(v0, sp, 0x4F4);
                    sh(zero, sp, 0x50C);
                    sw(v0, sp, 0x510);
                    sh(zero, sp, 0x528);
                    sw(v0, sp, 0x52C);
                    sh(zero, sp, 0x544);
                    sw(v0, sp, 0x548);
                    sh(zero, sp, 0x560);
                    sw(v0, sp, 0x564);
                    sh(zero, sp, 0x57C);
                    sw(v0, sp, 0x580);
                    sh(zero, sp, 0x598);
                    sw(v0, sp, 0x59C);
                    sh(zero, sp, 0x5B4);
                    sw(v0, sp, 0x5B8);
                    sh(zero, sp, 0x5D0);
                    sw(v0, sp, 0x5D4);
                    sh(zero, sp, 0x5EC);
                    sw(v0, sp, 0x5F0);
                    sh(zero, sp, 0x608);
                    sw(v0, sp, 0x60C);
                    sh(zero, sp, 0x624);
                    a0 = addiu(sp, 0x2070);
                    a1 = addiu(sp, 0x59C);
                    a2 = 28;
                    jal(ctx, 0x4056F8u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x2074);
                    a0 = s0;
                    a1 = 6;
                    jal(ctx, 0x40570Cu, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x2070);
                    jal(ctx, 0x40571Cu, gen::fn_sub_3DF100_003df100);
                }
            } else {
                // 0x00405508
                charge(ctx, 5);
                lw(s0, t0, menu::kElems);
                a2 = 0x6B0000;
                a2 = addiu(a2, -3104);  // &0x6AF3E0
                a1 = addiu(sp, 0x630);
                a0 = 63;
                for (;;) {
                    // 0x0040551c
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00405540
                charge(ctx, 53);
                v0 = 6;
                sw(v0, sp, 0x630);
                sh(zero, sp, 0x648);
                sw(v0, sp, 0x64C);
                sh(zero, sp, 0x664);
                sw(v0, sp, 0x668);
                sh(zero, sp, 0x680);
                sw(v0, sp, 0x684);
                sh(zero, sp, 0x69C);
                sw(v0, sp, 0x6A0);
                sh(zero, sp, 0x6B8);
                sw(v0, sp, 0x6BC);
                sh(zero, sp, 0x6D4);
                sw(v0, sp, 0x6D8);
                sh(zero, sp, 0x6F0);
                sw(v0, sp, 0x6F4);
                sh(zero, sp, 0x70C);
                sw(v0, sp, 0x710);
                sh(zero, sp, 0x728);
                sw(v0, sp, 0x72C);
                sh(zero, sp, 0x744);
                sw(v0, sp, 0x748);
                sh(zero, sp, 0x760);
                sw(v0, sp, 0x764);
                sh(zero, sp, 0x77C);
                sw(v0, sp, 0x780);
                sh(zero, sp, 0x798);
                sw(v0, sp, 0x79C);
                sh(zero, sp, 0x7B4);
                sw(v0, sp, 0x7B8);
                sh(zero, sp, 0x7D0);
                sw(v0, sp, 0x7D4);
                sh(zero, sp, 0x7EC);
                sw(v0, sp, 0x7F0);
                sh(zero, sp, 0x808);
                sw(v0, sp, 0x80C);
                sh(zero, sp, 0x824);
                a0 = addiu(sp, 0x2090);
                a1 = addiu(sp, 0x780);
                a2 = 28;
                jal(ctx, 0x4055E0u, gen::fn_memcpy_00521250);
                lw(a2, sp, 0x2094);
                a0 = s0;
                a1 = 6;
                jal(ctx, 0x4055F4u, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0x2090);
                jal(ctx, 0x405604u, gen::fn_sub_3DF100_003df100);
            }
            break;
        case 0x40572Cu:  // table[7]
            // 0x0040572c: part 7
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x00405840
                charge(ctx, 3);
                v1 = 1;
                if (a2 == v1) {
                    // 0x0040584c
                    charge(ctx, 5);
                    lw(s0, t0, menu::kElems);
                    a2 = 0x6B0000;
                    a2 = addiu(a2, -3104);  // &0x6AF3E0
                    a1 = addiu(sp, 0x30);
                    a0 = 63;
                    for (;;) {
                        // 0x00405860
                        charge(ctx, 9);
                        lw(v1, a2, 0);
                        lw(v0, a2, 4);
                        a2 = addiu(a2, 8);
                        a0 = addiu(a0, -1);
                        sw(v1, a1, 0);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00405884
                    charge(ctx, 51);
                    v0 = 7;
                    sw(v0, sp, 0x30);
                    sh(zero, sp, 0x48);
                    sw(v0, sp, 0x4C);
                    sh(zero, sp, 0x64);
                    sw(v0, sp, 0x68);
                    sh(zero, sp, 0x80);
                    sw(v0, sp, 0x84);
                    sh(zero, sp, 0x9C);
                    sw(v0, sp, 0xA0);
                    sh(zero, sp, 0xB8);
                    sw(v0, sp, 0xBC);
                    sh(zero, sp, 0xD4);
                    sw(v0, sp, 0xD8);
                    sh(zero, sp, 0xF0);
                    sw(v0, sp, 0xF4);
                    sh(zero, sp, 0x10C);
                    sw(v0, sp, 0x110);
                    sh(zero, sp, 0x128);
                    sw(v0, sp, 0x12C);
                    sh(zero, sp, 0x144);
                    sw(v0, sp, 0x148);
                    sh(zero, sp, 0x160);
                    sw(v0, sp, 0x164);
                    sh(zero, sp, 0x17C);
                    sw(v0, sp, 0x180);
                    sh(zero, sp, 0x198);
                    sw(v0, sp, 0x19C);
                    sh(zero, sp, 0x1B4);
                    sw(v0, sp, 0x1B8);
                    sh(zero, sp, 0x1D0);
                    sw(v0, sp, 0x1D4);
                    sh(zero, sp, 0x1EC);
                    sw(v0, sp, 0x1F0);
                    sh(zero, sp, 0x208);
                    sw(v0, sp, 0x20C);
                    sh(zero, sp, 0x224);
                    a0 = addiu(sp, 0x2030);
                    a1 = addiu(sp, 0x1D4);
                    a2 = 28;
                    jal(ctx, 0x405924u, gen::fn_memcpy_00521250);
                    lw(a2, sp, 0x2034);
                    a0 = s0;
                    a1 = 7;
                    jal(ctx, 0x405938u, gen::fn_sub_3DFFC0_003dffc0);
                    a0 = v0;
                    a1 = addiu(sp, 0x2030);
                    jal(ctx, 0x405948u, gen::fn_sub_3DF100_003df100);
                }
            } else {
                // 0x00405734
                charge(ctx, 5);
                lw(s0, t0, menu::kElems);
                a2 = 0x6B0000;
                a2 = addiu(a2, -3104);  // &0x6AF3E0
                a1 = addiu(sp, 0x230);
                a0 = 63;
                for (;;) {
                    // 0x00405748
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0040576c
                charge(ctx, 53);
                v0 = 7;
                sw(v0, sp, 0x230);
                sh(zero, sp, 0x248);
                sw(v0, sp, 0x24C);
                sh(zero, sp, 0x264);
                sw(v0, sp, 0x268);
                sh(zero, sp, 0x280);
                sw(v0, sp, 0x284);
                sh(zero, sp, 0x29C);
                sw(v0, sp, 0x2A0);
                sh(zero, sp, 0x2B8);
                sw(v0, sp, 0x2BC);
                sh(zero, sp, 0x2D4);
                sw(v0, sp, 0x2D8);
                sh(zero, sp, 0x2F0);
                sw(v0, sp, 0x2F4);
                sh(zero, sp, 0x30C);
                sw(v0, sp, 0x310);
                sh(zero, sp, 0x328);
                sw(v0, sp, 0x32C);
                sh(zero, sp, 0x344);
                sw(v0, sp, 0x348);
                sh(zero, sp, 0x360);
                sw(v0, sp, 0x364);
                sh(zero, sp, 0x37C);
                sw(v0, sp, 0x380);
                sh(zero, sp, 0x398);
                sw(v0, sp, 0x39C);
                sh(zero, sp, 0x3B4);
                sw(v0, sp, 0x3B8);
                sh(zero, sp, 0x3D0);
                sw(v0, sp, 0x3D4);
                sh(zero, sp, 0x3EC);
                sw(v0, sp, 0x3F0);
                sh(zero, sp, 0x408);
                sw(v0, sp, 0x40C);
                sh(zero, sp, 0x424);
                a0 = addiu(sp, 0x2050);
                a1 = addiu(sp, 0x3B8);
                a2 = 28;
                jal(ctx, 0x40580Cu, gen::fn_memcpy_00521250);
                lw(a2, sp, 0x2054);
                a0 = s0;
                a1 = 7;
                jal(ctx, 0x405820u, gen::fn_sub_3DFFC0_003dffc0);
                a0 = v0;
                a1 = addiu(sp, 0x2050);
                jal(ctx, 0x405830u, gen::fn_sub_3DF100_003df100);
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00405950 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x2230);
}

// 0x00405A90 sub_405A90 -- 44 bytes; frame 0x10: ra sp+0x0
// [fclQuestRowFree] Row-removed callback: frees the row's element set (row user +8) with sub_3DFF00.
void sub_405A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00405a90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a1, 20);
    lw(v0, v0, 28);
    lw(a0, v0, 8);
    jal(ctx, 0x405AA4u, gen::fn_sub_3DFF00_003dff00);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00405D60 sub_405D60 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclQuestListDestroy] Destroys a request list a0: its window element set (user +8), then the list.
void sub_405D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00405d60
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, lst::kState);
    lw(v0, v0, 68);
    lw(a0, v0, 8);
    jal(ctx, 0x405D7Cu, gen::fn_sub_3DFF00_003dff00);
    a0 = s0;
    jal(ctx, 0x405D88u, gen::fn_nmCmdListDestroy_003c5a20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00405DB0 sub_405DB0 -- 76 bytes; leaf frame (no stack)
// [fclQuestCompare] The request list's sort comparator (nmCmdListSort): the order key (+58) of b's request minus a's (the
// row user +4 is the request id).
void sub_405DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00405db0
    enter(ctx, 19);  // entry check point + this block's cycles
    lw(v0, gp, -21504);  // 0x7CD8F0
    a2 = addiu(v0, 58);
    lw(v0, a0, 0);
    lw(v0, v0, 20);
    lw(v0, v0, 28);
    lh(v0, v0, 4);
    v0 = sll(v0, 6);
    v0 = addu(a2, v0);
    lh(v1, v0, 0);
    lw(v0, a1, 0);
    lw(v0, v0, 20);
    lw(v0, v0, 28);
    lh(v0, v0, 4);
    v0 = sll(v0, 6);
    v0 = addu(a2, v0);
    lh(v0, v0, 0);
    v0 = subu(v0, v1);
}

// 0x00405E00 sub_405E00 -- 44 bytes; frame 0x10: ra sp+0x0
// [fclQuestListSort] Sorts the request list a0 with sub_405DB0.
void sub_405E00(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00405e00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0x400000;
    a1 = addiu(a1, 23984);  // &sub_405DB0
    a2 = 0;
    jal(ctx, 0x405E14u, gen::fn_nmCmdListSort_003c7000);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00405E30 sub_405E30 -- 320 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclQuestListUpdate] One frame of the request list a0: steps the window elements and every row's, the list
// (nmCmdListUpdate) with the cursor sounds 0 / 5, the part-1 out animation (sub_404750(list, 1, 1)), and sets the
// cursor request's "seen" flag 4351 + id. Returns 1 when the update returned 3, else 0.
void sub_405E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00405e30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, lst::kState);
    lw(v0, v0, 68);
    lw(a0, v0, 8);
    jal(ctx, 0x405E50u, gen::fn_sub_3E0650_003e0650);
    lw(s1, s0, lst::kHead);
    for (;;) {
        // 0x00405e7c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00405e64
        charge(ctx, 6);
        lw(v0, s1, node::kPayload);
        lw(v0, v0, 28);
        lw(a0, v0, 8);
        jal(ctx, 0x405E70u, gen::fn_sub_3E0650_003e0650);
        lw(s1, s1, node::kNext);
    }
    // 0x00405e84
    charge(ctx, 10);
    a0 = s0;
    jal(ctx, 0x405E88u, gen::fn_nmCmdListUpdate_003c6270);
    v0 = v0 ^ 0x3;
    s1 = sltiu(v0, 1);
    a0 = s0;
    jal(ctx, 0x405E9Cu, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x00405eac
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x405EB0u, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_00405ec0;
        }
        goto L_00405ed8;
    }
L_00405ec0:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x405ED0u, gen::fn_sub_10A4E0_0010a4e0);
L_00405ed8:
    charge(ctx, 5);
    a0 = s0;
    jal(ctx, 0x405EDCu, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x00405eec
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x405EF0u, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_00405f00;
        }
        goto L_00405f18;
    }
L_00405f00:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x405F10u, gen::fn_sub_10A4E0_0010a4e0);
L_00405f18:
    charge(ctx, 8);
    a0 = s0;
    a1 = 1;
    a2 = a1;
    jal(ctx, 0x405F24u, gen::fn_sub_404750_00404750);
    lw(v0, s0, lst::kCursor);
    if (v0 != 0) {
        // 0x00405f38: a cursor row: its seen flag
        charge(ctx, 7);
        lw(v0, v0, 20);
        lw(v0, v0, 28);
        lh(v0, v0, 4);
        a0 = addiu(v0, 4351);
        a1 = 1;
        jal(ctx, 0x405F4Cu, gen::fn_datSetFlag_0016f1f0);
    }
    // 0x00405f54 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00406AA0 sub_406AA0 -- 504 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawDatePanel] Draws the date panel at (a0, a1) with alpha a2: sprite 3, the time-of-day sprite 5 + (t - 1) (t =
// datGetTime, 8 counted as 9, the slots 2..5 drawn as 8 on a holiday / Sunday), the month and day ("%d" at 0x7CD900, sub_40EBC0, alpha
// x 0.8 through the float to byte conversion) at +530 / +572, sprite 14 and the weekday sprite 15 at +96.
void sub_406AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00406aa0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    jal(ctx, 0x406AC4u, gen::fn_datGetTime_0016ef30);
    s0 = v0 & 0xFF;
    v0 = 8;
    if (s0 == v0) {
        // 0x00406adc: slot 8 is drawn as 9
        charge(ctx, 1);
        s0 = 9;
    }
    // 0x00406ae0
    charge(ctx, 5);
    jal(ctx, 0x406AE0u, gen::fn_clndIsHolidayOrSunday_0017dcf0);
    v1 = 1;
    if (v0 == v1) {
        // 0x00406af4
        charge(ctx, 4);
        v0 = addiu(s0, -2);
        at = sltiu(v0, 4);
        if (at != 0) {
            // 0x00406b04: a holiday: the day slots as 8
            charge(ctx, 1);
            s0 = 8;
        }
    }
    // 0x00406b08
    charge(ctx, 3);
    s0 = addiu(s0, -1);
    if (i64(s0) < 0) {
        // 0x00406b14
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x00406b18
    charge(ctx, 34);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a0 = s3;
    a1 = s2;
    a3 = 3;
    t0 = 0;
    jal(ctx, 0x406B30u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a3 = addiu(s0, 5);
    a0 = s3;
    a1 = s2;
    t0 = 0;
    jal(ctx, 0x406B50u, gen::fn_sub_40E3C0_0040e3c0);
    jal(ctx, 0x406B58u, gen::fn_clndGetCurrentMonth_0017d920);
    a0 = addiu(sp, 0x58);
    a1 = addiu(gp, -21488);  // "%d"
    a2 = v0;
    jal(ctx, 0x406B6Cu, gen::fn_sprintf_00523ac8);
    mtc1(s1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32636);  // 0x7CAD74
    mul_s(f1, f0, f1);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00406bb0
        charge(ctx, 5);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
    } else {
        // 0x00406ba0
        charge(ctx, 4);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
    }
    // 0x00406bc4
    charge(ctx, 53);
    v0 = si(-256);
    s0 = v1 | v0;
    a0 = addiu(s3, 530);
    a1 = addiu(s2, 27);
    mtc1(zero, f12);
    a2 = s0;
    a3 = 3;
    t0 = addiu(sp, 0x58);
    t1 = 2;
    jal(ctx, 0x406BE8u, gen::fn_sub_40EBC0_0040ebc0);
    a0 = addiu(s3, 96);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 14;
    t0 = 0;
    jal(ctx, 0x406C08u, gen::fn_sub_40E3C0_0040e3c0);
    jal(ctx, 0x406C10u, gen::fn_clndGetCurrentDay_0017da40);
    a0 = addiu(sp, 0x58);
    a1 = addiu(gp, -21488);  // "%d"
    a2 = v0;
    jal(ctx, 0x406C24u, gen::fn_sprintf_00523ac8);
    a0 = addiu(s3, 572);
    a1 = addiu(s2, 27);
    mtc1(zero, f12);
    a2 = s0;
    a3 = 3;
    t0 = addiu(sp, 0x58);
    t1 = 2;
    jal(ctx, 0x406C48u, gen::fn_sub_40EBC0_0040ebc0);
    jal(ctx, 0x406C50u, gen::fn_clndGetCurrentWeekDay_0017db00);
    a0 = addiu(s3, 96);
    a1 = addiu(s2, 1);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a3 = 15;
    t0 = v0;
    jal(ctx, 0x406C70u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00407180 sub_407180 -- 140 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq), s1 sp+0x3C
// [fclQuestDrawWindow] The request list's window draw (data ref): draws the window element set (user +8) through
// sub_406CA0 with {x, y, alpha, list, 0}, then removes the filtered rows with the user flag 1 set meanwhile.
void sub_407180(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00407180
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a3;
    lw(v0, a3, lst::kState);
    lw(s0, v0, 68);
    lw(v0, s0, menu::kElems);
    sw(a0, sp, 0x30);
    sw(a1, sp, 0x34);
    sh(a2, sp, 0x38);
    sw(s1, sp, 0x3C);
    sw(zero, sp, 0x40);
    a0 = v0;
    a1 = 0x400000;
    a1 = addiu(a1, 27808);  // &sub_406CA0
    a2 = addiu(sp, 0x30);
    jal(ctx, 0x4071C4u, gen::fn_sub_3E0680_003e0680);
    lw(v0, s0, menu::kFlags);
    v0 = v0 | 0x1;
    sw(v0, s0, menu::kFlags);
    a0 = s1;
    jal(ctx, 0x4071DCu, gen::fn_nmListRemoveFiltered_003c4e70);
    lw(a0, s0, menu::kFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, menu::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00407210 sub_407210 -- 192 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclQuestDrawRow] The request list's row draw: draws the row's element set (row user +8) through sub_406CA0 with {x, y,
// alpha, flags (1 on the cursor row), list, row}.
void sub_407210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00407210
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    lw(v0, t0, node::kPayload);
    lw(v0, v0, 28);
    lw(s0, v0, 8);
    a0 = addiu(sp, 0x70);
    a1 = 0;
    a2 = 24;
    jal(ctx, 0x40725Cu, gen::fn_memset_00521408);
    lw(v0, s2, lst::kCursor);
    if (v0 == s1) {
        // 0x00407270
        charge(ctx, 3);
        lh(v0, sp, 0x7A);
        v0 = v0 | 0x1;
        sh(v0, sp, 0x7A);
    }
    // 0x0040727c
    charge(ctx, 21);
    sw(s5, sp, 0x70);
    sw(s4, sp, 0x74);
    sh(s3, sp, 0x78);
    sw(s2, sp, 0x7C);
    sw(s1, sp, 0x80);
    a0 = s0;
    a1 = 0x400000;
    a1 = addiu(a1, 27808);  // &sub_406CA0
    a2 = addiu(sp, 0x70);
    jal(ctx, 0x4072A0u, gen::fn_sub_3E0680_003e0680);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00409C80 sub_409C80 -- 524 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBookFillList] BOOK: fills the compendium list a0 with the registered personas 1..255 (sub_17C8C0(id), after
// sub_3F03E0(8)): a row (16-byte crow::) with the persona, the summon price 3 s^2 + 2000 (s = the five stats,
// sub_173580(persona, 0..4)), x4 with game flag 4889 unless that reaches 10,000,000 (then 9,999,999), and an element set
// (sub_3DFEB0(0)). Returns 0.
void sub_409C80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00409c80
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    a0 = 8;
    jal(ctx, 0x409CA8u, gen::fn_sub_3F03E0_003f03e0);
    s2 = 1;
    for (;;) {
        // 0x00409e54
        charge(ctx, 3);
        v0 = slti(s2, 256);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00409cbc
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x409CC0u, gen::fn_sub_17C8C0_0017c8c0);
        s3 = v0;
        if (v0 != 0) {
            // 0x00409cd4: a registered persona: its row and price
            charge(ctx, 78);
            lhu(v0, s4, lst::kCount);
            a1 = addiu(v0, 1);
            a0 = s4;
            a2 = 16;
            a3 = 0;
            jal(ctx, 0x409CE8u, gen::fn_nmCmdListAddRow_003c5a40);
            lw(v0, v0, 20);
            lw(s1, v0, 28);
            sw(s3, s1, crow::kPersona);
            a0 = s3;
            a1 = 0;
            jal(ctx, 0x409D04u, gen::fn_sub_173580_00173580);
            s0 = v0 & 0xFF;
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x409D18u, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s0 = addu(s0, v0);
            a0 = s3;
            a1 = 2;
            jal(ctx, 0x409D30u, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s0 = addu(v0, s0);
            a0 = s3;
            a1 = 3;
            jal(ctx, 0x409D48u, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s0 = addu(v0, s0);
            a0 = s3;
            a1 = 4;
            jal(ctx, 0x409D60u, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s0 = addu(v0, s0);
            a0 = s3;
            a1 = 0;
            jal(ctx, 0x409D78u, gen::fn_sub_173580_00173580);
            s5 = v0 & 0xFF;
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x409D8Cu, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s5 = addu(s5, v0);
            a0 = s3;
            a1 = 2;
            jal(ctx, 0x409DA4u, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s5 = addu(v0, s5);
            a0 = s3;
            a1 = 3;
            jal(ctx, 0x409DBCu, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            s5 = addu(v0, s5);
            a0 = s3;
            a1 = 4;
            jal(ctx, 0x409DD4u, gen::fn_sub_173580_00173580);
            v0 = v0 & 0xFF;
            v0 = addu(v0, s5);
            mult(v1, s0, v0);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = addiu(v0, 2000);
            sw(v0, s1, crow::kPrice);
            a0 = 4889;
            jal(ctx, 0x409DFCu, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00409e0c: flag 4889: x4, at most 9,999,999
                charge(ctx, 7);
                lw(v0, s1, crow::kPrice);
                v0 = sll(v0, 2);
                at = 0x980000;
                at = at | 0x9680;  // &0x989680
                at = slt(v0, at);
                if (at != 0) {
                    // 0x00409e3c: below the cap
                    charge(ctx, 1);
                    sw(v0, s1, crow::kPrice);
                } else {
                    // 0x00409e28: the cap
                    charge(ctx, 5);
                    v0 = 0x980000;
                    v0 = v0 | 0x967F;  // &0x98967F
                    sw(v0, s1, crow::kPrice);
                }
            }
            // 0x00409e40
            charge(ctx, 4);
            a0 = 0;
            jal(ctx, 0x409E44u, gen::fn_sub_3DFEB0_003dfeb0);
            sw(v0, s1, crow::kElems);
        }
        // 0x00409e50
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00409e60
    charge(ctx, 11);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00409E90 sub_409E90 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBookStockRegistered] Returns 1 when a stock persona (sub_174A90 over the stock, sub_175410 slots) is registered in its
// current form (sub_17CA10 == 1), else 0.
void sub_409E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00409e90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x00409ee8
        charge(ctx, 6);
        jal(ctx, 0x409EE8u, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00409ea8
        charge(ctx, 6);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x409EB0u, gen::fn_sub_174A90_00174a90);
        if (v0 != 0) {
            // 0x00409ec0
            charge(ctx, 6);
            a0 = v0;
            jal(ctx, 0x409EC4u, gen::fn_sub_17CA10_0017ca10);
            v1 = 1;
            if (v0 != v1) {
                goto L_00409ee4;
            }
            goto L_00409ed8_3;
        }
    L_00409ee4:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00409f00
    charge(ctx, 1);
    v0 = 0;
    // 0x00409f04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_00409ed8_3:
    charge(ctx, 3);
    v0 = v1;
    // 0x00409f04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00409F20 sub_409F20 -- 44 bytes; frame 0x10: ra sp+0x0
// [fclBookRowFree] Row-removed callback: frees the row's element set (row user +12) with sub_3DFF00.
void sub_409F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00409f20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a1, 20);
    lw(v0, v0, 28);
    lw(a0, v0, 12);
    jal(ctx, 0x409F34u, gen::fn_sub_3DFF00_003dff00);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040A200 sub_40A200 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBookListDestroy] Destroys a compendium list a0: its element sets (user +28, and +32 when set), then the list.
void sub_40A200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040a200
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, lst::kState);
    lw(s0, v0, 68);
    lw(a0, s0, menu::kElemsA);
    jal(ctx, 0x40A220u, gen::fn_sub_3DFF00_003dff00);
    lw(a0, s0, menu::kElemsB);
    if (a0 != 0) {
        // 0x0040a234
        charge(ctx, 2);
        jal(ctx, 0x40A234u, gen::fn_sub_3DFF00_003dff00);
    }
    // 0x0040a23c
    charge(ctx, 9);
    a0 = s1;
    jal(ctx, 0x40A240u, gen::fn_nmCmdListDestroy_003c5a20);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040A260 sub_40A260 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBookRegisterAll] BOOKREGIST: registers every row's persona (sub_17C960(row user +4)).
void sub_40A260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040a260
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, lst::kHead);
    for (;;) {
        // 0x0040a290
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040a278
        charge(ctx, 6);
        lw(v0, s0, node::kPayload);
        lw(v0, v0, 28);
        lw(a0, v0, 4);
        jal(ctx, 0x40A284u, gen::fn_sub_17C960_0017c960);
        lw(s0, s0, node::kNext);
    }
    // 0x0040a298
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0040A5B0 sub_40A5B0 -- 132 bytes; leaf frame (no stack)
// [fclBookCompareLevel] Compendium comparator: by level (b - a), then arcana (PERSONA.TBL +2, gp - 18640), then id.
void sub_40A5B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0040a5b0
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v0, v0, 20);
    lw(v1, v0, 28);
    lw(v0, a1, 0);
    lw(v0, v0, 20);
    lw(v0, v0, 28);
    lw(a3, v1, 4);
    lw(a0, v0, 4);
    lbu(v1, a0, 4);
    lbu(v0, a3, 4);
    v0 = subu(v1, v0);
    if (v0 == 0) {
        // 0x0040a5e4
        charge(ctx, 17);
        lhu(a2, a0, 2);
        lw(v0, gp, -18640);  // 0x7CE420
        a1 = addiu(v0, 2);
        lhu(a0, a3, 2);
        v0 = sll(a0, 3);
        v0 = subu(v0, a0);
        v0 = sll(v0, 1);
        v0 = addu(a1, v0);
        lbu(v1, v0, 0);
        v0 = sll(a2, 3);
        v0 = subu(v0, a2);
        v0 = sll(v0, 1);
        v0 = addu(a1, v0);
        lbu(v0, v0, 0);
        v0 = subu(v1, v0);
        if (v0 == 0) {
            // 0x0040a628
            charge(ctx, 1);
            v0 = subu(a0, a2);
        }
    }
    // 0x0040a62c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0040A640 sub_40A640 -- 132 bytes; leaf frame (no stack)
// [fclBookCompareArcana] Compendium comparator: by arcana (a - b), then level (b - a), then id (a - b).
void sub_40A640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x0040a640
    enter(ctx, 25);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v0, v0, 20);
    lw(v1, v0, 28);
    lw(v0, a1, 0);
    lw(v0, v0, 20);
    lw(v0, v0, 28);
    lw(t0, v0, 4);
    lhu(a3, t0, 2);
    lw(v0, gp, -18640);  // 0x7CE420
    a2 = addiu(v0, 2);
    lw(a1, v1, 4);
    lhu(a0, a1, 2);
    v0 = sll(a0, 3);
    v0 = subu(v0, a0);
    v0 = sll(v0, 1);
    v0 = addu(a2, v0);
    lbu(v1, v0, 0);
    v0 = sll(a3, 3);
    v0 = subu(v0, a3);
    v0 = sll(v0, 1);
    v0 = addu(a2, v0);
    lbu(v0, v0, 0);
    v0 = subu(v1, v0);
    if (v0 == 0) {
        // 0x0040a6a4
        charge(ctx, 5);
        lbu(v1, t0, 4);
        lbu(v0, a1, 4);
        v0 = subu(v1, v0);
        if (v0 == 0) {
            // 0x0040a6b8
            charge(ctx, 1);
            v0 = subu(a0, a3);
        }
    }
    // 0x0040a6bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0040A6D0 sub_40A6D0 -- 232 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBookSort] Re-sorts the compendium list a0 by arcana (a1 = 1, sub_40A640) or by level (sub_40A5B0), keeping the cursor
// row on its screen line (nmCmdListSelect), and records the order in the user flag 2.
void sub_40A6D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040a6d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(v0, a0, 36);
    lw(s0, v0, 68);
    jal(ctx, 0x40A6FCu, gen::fn_nmCmdListCursorLine_003c6fb0);
    s4 = v0;
    lw(s3, s2, lst::kCursor);
    v0 = 1;
    if (s1 != v0) {
        // 0x0040a738: by arcana
        charge(ctx, 6);
        a0 = s2;
        a1 = 0x410000;
        a1 = addiu(a1, -23120);  // &sub_40A5B0
        a2 = 0;
        jal(ctx, 0x40A748u, gen::fn_nmCmdListSort_003c7000);
    } else {
        // 0x0040a718: by level
        charge(ctx, 8);
        a0 = s2;
        a1 = 0x410000;
        a1 = addiu(a1, -22976);  // &sub_40A640
        a2 = 0;
        jal(ctx, 0x40A728u, gen::fn_nmCmdListSort_003c7000);
    }
    // 0x0040a750
    charge(ctx, 8);
    a0 = s2;
    a1 = s3;
    a2 = s4;
    jal(ctx, 0x40A75Cu, gen::fn_nmCmdListSelect_003c5d40);
    v1 = 1;
    if (s1 != v1) {
        // 0x0040a784: flag 2: by arcana
        charge(ctx, 4);
        lw(a0, s0, menu::kFlags);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, s0, menu::kFlags);
    } else {
        // 0x0040a770: by level
        charge(ctx, 5);
        lw(v1, s0, menu::kFlags);
        v1 = v1 | 0x2;
        sw(v1, s0, menu::kFlags);
    }
    // 0x0040a794 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0040A7C0 sub_40A7C0 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclBookDrawMark] Draws sprite 120 at (a0, a1) with alpha a2.
void sub_40A7C0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040a7c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a2 & 0xFF;
    a3 = 120;
    jal(ctx, 0x40A7D0u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040B630 sub_40B630 -- 332 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s5 sp+0x80, s4 sp+0x84, s2 sp+0x8C
// [fclBookDrawWindow] The compendium's window draw: sprite 27, the element set +28 through sub_40A7F0 (user flag 4 while the
// filtered rows are removed, then again), and the element set +32 when set through sub_40B3A0 with the cursor row.
void sub_40B630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0040b630
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    lw(v0, a3, lst::kState);
    lw(s0, v0, 68);
    lw(s1, s0, menu::kElemsA);
    lw(s6, s0, menu::kElemsB);
    mtc1(zero, f12);
    a2 = s3 & 0xFF;
    a0 = 0;
    a1 = 0;
    a3 = 27;
    t0 = 0;
    jal(ctx, 0x40B68Cu, gen::fn_sub_40E3C0_0040e3c0);
    sw(s5, sp, 0x80);
    sw(s4, sp, 0x84);
    sh(s3, sp, 0x88);
    sw(s2, sp, 0x8C);
    sw(zero, sp, 0x90);
    lw(v0, s0, menu::kFlags);
    v0 = v0 | 0x4;
    sw(v0, s0, menu::kFlags);
    a0 = s1;
    a1 = 0x410000;
    a1 = addiu(a1, -22544);  // &sub_40A7F0
    a2 = addiu(sp, 0x80);
    jal(ctx, 0x40B6C4u, gen::fn_sub_3E0680_003e0680);
    lw(v1, s0, menu::kFlags);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, s0, menu::kFlags);
    v0 = v0 | 0x4;
    sw(v0, s0, menu::kFlags);
    a0 = s2;
    jal(ctx, 0x40B6E8u, gen::fn_nmListRemoveFiltered_003c4e70);
    lw(v1, s0, menu::kFlags);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, s0, menu::kFlags);
    a0 = s1;
    a1 = 0x410000;
    a1 = addiu(a1, -22544);  // &sub_40A7F0
    a2 = addiu(sp, 0x80);
    jal(ctx, 0x40B710u, gen::fn_sub_3E0680_003e0680);
    if (s6 != 0) {
        // 0x0040b720
        charge(ctx, 12);
        sw(s5, sp, 0x80);
        sw(s4, sp, 0x84);
        sh(s3, sp, 0x88);
        sw(s2, sp, 0x8C);
        lw(v0, s2, lst::kCursor);
        sw(v0, sp, 0x90);
        a0 = s6;
        a1 = 0x410000;
        a1 = addiu(a1, -19552);  // &sub_40B3A0
        a2 = addiu(sp, 0x80);
        jal(ctx, 0x40B748u, gen::fn_sub_3E0680_003e0680);
    }
    // 0x0040b750 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x0040B780 sub_40B780 -- 192 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBookDrawRow] The compendium's row draw: the row's element set (+12) through sub_40A7F0 with {x, y, alpha, flags (1 on
// the cursor row), list, row}.
void sub_40B780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040b780
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    lw(v0, t0, node::kPayload);
    lw(v0, v0, 28);
    lw(s0, v0, 12);
    a0 = addiu(sp, 0x70);
    a1 = 0;
    a2 = 24;
    jal(ctx, 0x40B7CCu, gen::fn_memset_00521408);
    lw(v0, s2, lst::kCursor);
    if (v0 == s1) {
        // 0x0040b7e0
        charge(ctx, 3);
        lh(v0, sp, 0x7A);
        v0 = v0 | 0x1;
        sh(v0, sp, 0x7A);
    }
    // 0x0040b7ec
    charge(ctx, 21);
    sw(s5, sp, 0x70);
    sw(s4, sp, 0x74);
    sh(s3, sp, 0x78);
    sw(s2, sp, 0x7C);
    sw(s1, sp, 0x80);
    a0 = s0;
    a1 = 0x410000;
    a1 = addiu(a1, -22544);  // &sub_40A7F0
    a2 = addiu(sp, 0x70);
    jal(ctx, 0x40B810u, gen::fn_sub_3E0680_003e0680);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0040C150 sub_40C150 -- 24 bytes; leaf frame (no stack)
// [fclShopListFlagBit] Reads list a0's user flag bit 0 into $v1 (a leftover: nothing is returned in $v0).
void sub_40C150(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0040c150
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, lst::kState);
    lw(v1, v1, 68);
    lw(v1, v1, 0);
    v1 = v1 & 0x1;
}

// 0x0040C1E0 sub_40C1E0 -- 304 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopAddOptionRows] Adds the option entries of table a1 {16-byte entries, count} to the list of work a0 (+12): an entry
// whose two flags are 0 or set gets a row (12-byte user: +4 the entry, +8 an element set) keyed by a2[i] when a2 is given,
// else count + 1. A null work or table is K_Assert("fclShopMisc.c", 10043).
void sub_40C1E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c1e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s4 = a1;
    s3 = a2;
    if (s0 != 0) {
        // 0x0040c214
        charge(ctx, 2);
        if (s4 == 0) {
            goto L_0040c21c;
        }
        goto L_0040c230;
    }
L_0040c21c:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 10043;
    jal(ctx, 0x40C228u, gen::fn_sub_19D3F0_0019d3f0);
L_0040c230:
    charge(ctx, 5);
    lw(s1, s0, 12);
    lw(s2, s4, ttab::kEntries);
    s0 = 0;
    for (;;) {
        // 0x0040c2d8
        charge(ctx, 4);
        lw(v1, s4, ttab::kCount);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040c244
        charge(ctx, 3);
        lw(a0, s2, hent::kFlagA);
        if (a0 != 0) {
            // 0x0040c250
            charge(ctx, 4);
            jal(ctx, 0x40C250u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                goto L_0040c260;
            }
            goto L_0040c2d0;
        }
    L_0040c260:
        charge(ctx, 3);
        lw(a0, s2, hent::kFlagB);
        if (a0 != 0) {
            // 0x0040c26c
            charge(ctx, 4);
            jal(ctx, 0x40C26Cu, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                goto L_0040c27c;
            }
            goto L_0040c2d0;
        }
    L_0040c27c:
        charge(ctx, 2);
        if (s3 == 0) {
            // 0x0040c298
            charge(ctx, 2);
            lhu(v0, s1, lst::kCount);
            a1 = addiu(v0, 1);
        } else {
            // 0x0040c284
            charge(ctx, 5);
            v0 = sll(s0, 2);
            v0 = addu(s3, v0);
            lw(a1, v0, 0);
        }
        // 0x0040c2a0: add the row
        charge(ctx, 12);
        a0 = s1;
        a2 = 12;
        a3 = 0;
        jal(ctx, 0x40C2ACu, gen::fn_nmCmdListAddRow_003c5a40);
        lw(v0, v0, 20);
        lw(s5, v0, 28);
        sw(s2, s5, hrow::kEntry);
        a0 = s4;
        jal(ctx, 0x40C2C4u, gen::fn_sub_3DFEB0_003dfeb0);
        sw(v0, s5, hrow::kElems);
    L_0040c2d0:
        charge(ctx, 2);
        s0 = addiu(s0, 1);
        s2 = addiu(s2, 16);
    }
    // 0x0040c2e8
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0040C460 sub_40C460 -- 44 bytes; frame 0x10: ra sp+0x0
// [fclShopOptionRowFree] Row-removed callback: frees the row's element set (row user +8) with sub_3DFF00.
void sub_40C460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c460
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a1, 20);
    lw(v0, v0, 28);
    lw(a0, v0, 8);
    jal(ctx, 0x40C474u, gen::fn_sub_3DFF00_003dff00);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040C520 sub_40C520 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclListPanelCloseSub] The panel a0's closing for a sub-window: parts 4, 0, 1, 5, 6 out (sub_3D9820).
void sub_40C520(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c520
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 4;
    a2 = 1;
    jal(ctx, 0x40C538u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x40C54Cu, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 1;
    a2 = a1;
    jal(ctx, 0x40C560u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 5;
    a2 = 1;
    jal(ctx, 0x40C574u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 6;
    a2 = 1;
    jal(ctx, 0x40C588u, gen::fn_sub_3D9820_003d9820);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0040C5B0 sub_40C5B0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclListPanelClose] The panel a0's closing: parts 4, 0, 1, 2, 3, 7 out.
void sub_40C5B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c5b0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 4;
    a2 = 1;
    jal(ctx, 0x40C5C8u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x40C5DCu, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 1;
    a2 = a1;
    jal(ctx, 0x40C5F0u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 2;
    a2 = 1;
    jal(ctx, 0x40C604u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 3;
    a2 = 1;
    jal(ctx, 0x40C618u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 7;
    a2 = 1;
    jal(ctx, 0x40C62Cu, gen::fn_sub_3D9820_003d9820);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0040C650 sub_40C650 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclListPanelDecide] The panel a0's decision: part 0 out with the cursor row highlighted, part 7 out.
void sub_40C650(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c650
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    a2 = 3;
    jal(ctx, 0x40C668u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 7;
    a2 = 1;
    jal(ctx, 0x40C67Cu, gen::fn_sub_3D9820_003d9820);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0040C6A0 sub_40C6A0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclListPanelOpen] The panel a0's opening: parts 0 and 7 in.
void sub_40C6A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040c6a0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x40C6B8u, gen::fn_sub_3D9820_003d9820);
    a0 = s0;
    a1 = 7;
    a2 = 0;
    jal(ctx, 0x40C6CCu, gen::fn_sub_3D9820_003d9820);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0040CA00 sub_40CA00 -- 196 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclListPanelUpdate] Steps the panel a0's list (nmCmdListUpdate); on a cancel (2) the closing of sub_40C5B0. Returns the
// update's result.
void sub_40CA00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040ca00
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, panel::kList);
    jal(ctx, 0x40CA18u, gen::fn_nmCmdListUpdate_003c6270);
    s0 = v0;
    v1 = 2;
    if (v0 == v1) {
        // 0x0040ca30: cancelled: close
        charge(ctx, 30);
        a0 = s1;
        a1 = 4;
        a2 = 1;
        jal(ctx, 0x40CA3Cu, gen::fn_sub_3D9820_003d9820);
        a0 = s1;
        a1 = 0;
        a2 = 1;
        jal(ctx, 0x40CA50u, gen::fn_sub_3D9820_003d9820);
        a0 = s1;
        a1 = 1;
        a2 = a1;
        jal(ctx, 0x40CA64u, gen::fn_sub_3D9820_003d9820);
        a0 = s1;
        a1 = 2;
        a2 = 1;
        jal(ctx, 0x40CA78u, gen::fn_sub_3D9820_003d9820);
        a0 = s1;
        a1 = 3;
        a2 = 1;
        jal(ctx, 0x40CA8Cu, gen::fn_sub_3D9820_003d9820);
        a0 = s1;
        a1 = 7;
        a2 = 1;
        jal(ctx, 0x40CAA0u, gen::fn_sub_3D9820_003d9820);
    }
    // 0x0040caa8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040D330 sub_40D330 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclListPanelStep] A list's per-frame callback: steps the window elements (user +8) and every row's, then part 1 out
// (sub_3D9820(user, 1, 1)).
void sub_40D330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040d330
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, lst::kState);
    lw(s1, v0, 68);
    lw(a0, s1, panel::kElems);
    jal(ctx, 0x40D350u, gen::fn_sub_3E0650_003e0650);
    lw(s0, s0, lst::kHead);
    for (;;) {
        // 0x0040d37c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040d364
        charge(ctx, 6);
        lw(v0, s0, node::kPayload);
        lw(v0, v0, 28);
        lw(a0, v0, 8);
        jal(ctx, 0x40D370u, gen::fn_sub_3E0650_003e0650);
        lw(s0, s0, node::kNext);
    }
    // 0x0040d384
    charge(ctx, 11);
    a0 = s1;
    a1 = 1;
    a2 = a1;
    jal(ctx, 0x40D390u, gen::fn_sub_3D9820_003d9820);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
