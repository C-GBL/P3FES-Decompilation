// Phase 5 slice libs5: CRI Sofdec SFX, frame conversion: init / finish, the handle pool's create / destroy and the
// work layout (0x59CFA0-0x5A1158).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_22_0059f9e0(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_23_005a1158(p3fes::EEContext&);
void fn_sub_56DE28_0056de28(p3fes::EEContext&);
void fn_sub_59E7A8_0059e7a8(p3fes::EEContext&);
void fn_sub_59E808_0059e808(p3fes::EEContext&);
void fn_sub_59E8F0_0059e8f0(p3fes::EEContext&);
void fn_sub_59F970_0059f970(p3fes::EEContext&);
void fn_sub_59F9F0_0059f9f0(p3fes::EEContext&);
void fn_sub_59FAA8_0059faa8(p3fes::EEContext&);
void fn_sub_59FBC0_0059fbc0(p3fes::EEContext&);
void fn_sub_59FC10_0059fc10(p3fes::EEContext&);
void fn_sub_59FCB0_0059fcb0(p3fes::EEContext&);
void fn_sub_59FCC0_0059fcc0(p3fes::EEContext&);
void fn_sub_59FD10_0059fd10(p3fes::EEContext&);
void fn_sub_59FD50_0059fd50(p3fes::EEContext&);
void fn_sub_5A0238_005a0238(p3fes::EEContext&);
void fn_sub_5A0268_005a0268(p3fes::EEContext&);
void fn_sub_5A02C8_005a02c8(p3fes::EEContext&);
void fn_sub_5A0320_005a0320(p3fes::EEContext&);
void fn_sub_5A0370_005a0370(p3fes::EEContext&);
void fn_sub_5A0388_005a0388(p3fes::EEContext&);
void fn_sub_5A1108_005a1108(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x0059F970 sub_59F970 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [SFX_Init] SFX init (counted, 0x7B4918): the banner, the handle pool, SUD's init, the Z pool, sub_59E7A8.
void sub_59F970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f970
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 18712);  // &0x7B4918
    lw(v1, s0, 0);  // 0x7B4918
    sd(ra, sp, 0x8);
    if (i64(v1) <= 0) {
        // 0x0059f98c
        charge(ctx, 17);
        jal(ctx, 0x59F98Cu, gen::fn_sceLibgcc32GetErxEntries_22_0059f9e0);
        v1 = 0x9B0000;
        v1 = addiu(v1, -13336);  // &0x9ACBE8
        link(ctx, 0x59F99Cu);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 0);
        call(ctx, gen::fn_sub_59F9F0_0059f9f0);
        jal(ctx, 0x59F9A4u, gen::fn_sub_5A0238_005a0238);
        jal(ctx, 0x59F9ACu, gen::fn_sub_5A0268_005a0268);
        jal(ctx, 0x59F9B4u, gen::fn_sub_59E7A8_0059e7a8);
        lw(v0, s0, 0);
        v1 = 0x7B0000;
        sw(zero, v1, 18716);  // 0x7B491C
        v0 = addiu(v0, 1);
        sw(v0, s0, 0);
    }
    // 0x0059f9d0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059F9E0 sceLibgcc32GetErxEntries_22 -- 12 bytes; leaf frame (no stack)
// [SFX_GetVersionStr] SFX: the version banner (FLIRT misname).
void sceLibgcc32GetErxEntries_22(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059f9e0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7D0000;
    v0 = addiu(v0, -22168);  // "\nCRI SFX/PS2EE Ver.2.29 Build:Mar  1 2005 10:54:12\n"
}

// 0x0059F9F0 sub_59F9F0 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfx_InitPool] SFX: clears the handle pool 0x7B4920 (1,224 bytes): 8 handles, sub_59FD50(1), sub_56DE28.
void sub_59F9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f9f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 18720);  // &0x7B4920
    a2 = 1224;
    sd(ra, sp, 0x8);
    a0 = s0;
    jal(ctx, 0x59FA0Cu, gen::fn_memset_00521408);
    v1 = 8;
    sw(v1, s0, 4);  // 0x7B4924
    a0 = 1;
    jal(ctx, 0x59FA1Cu, gen::fn_sub_59FD50_0059fd50);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56DE28_0056de28(ctx);  // tail call
}

// 0x0059FAA8 sub_59FAA8 -- 276 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [SFX_Create] SFX create: a free handle, the work size check ('sfx_InitHn: work size is short.'), the work layout,
// the Z handle ('SfxZHn: can't create.') and the alpha handle ('SfxAHn: can't create.'); counts the handle.
void sub_59FAA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059faa8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = a0;
    jal(ctx, 0x59FAD0u, gen::fn_sub_59FBC0_0059fbc0);
    s2 = v0;
    a0 = s3;
    a1 = s0;
    a2 = s1;
    if (s2 != 0) {
        // 0x0059faec
        charge(ctx, 7);
        jal(ctx, 0x59FAECu, gen::fn_sub_59FCB0_0059fcb0);
        v1 = 1;
        a0 = 0;
        a1 = s4;
        a2 = s3;
        if (v0 == v1) {
            // 0x0059fb20
            charge(ctx, 9);
            a0 = s2;
            jal(ctx, 0x59FB20u, gen::fn_sub_59FC10_0059fc10);
            jal(ctx, 0x59FB28u, gen::fn_sub_5A02C8_005a02c8);
            a2 = 0x7D0000;
            a1 = 0;
            a2 = addiu(a2, -22064);  // "E201281: SfxZHn: can't create."
            a0 = 0;
            if (v0 != 0) {
                // 0x0059fb44
                charge(ctx, 10);
                link(ctx, 0x59FB44u);  // $ra first: the delay slot below depends on it
                sw(v0, s2, 36);
                call(ctx, gen::fn_sub_59E808_0059e808);
                a2 = 0x7D0000;
                a3 = v0;
                v0 = 0x7B0000;
                t0 = addiu(v0, 18720);  // &0x7B4920
                a2 = addiu(a2, -22032);  // "E202011: SfxAHn: can't create."
                a1 = 0;
                a0 = 0;
                if (a3 == 0) {
                    goto L_0059fb6c;
                }
                // 0x0059fb88
                charge(ctx, 5);
                lw(v1, t0, 0);
                v0 = s2;
                sw(a3, s2, 48);
                v1 = addiu(v1, 1);
                sw(v1, t0, 0);
                // 0x0059fb9c (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(s0, sp, 0x0);
                ld(s1, sp, 0x8);
                ld(s2, sp, 0x10);
                ld(s3, sp, 0x18);
                ld(s4, sp, 0x20);
                ld(ra, sp, 0x28);
                sp = addiu(sp, 0x30);
                return;
            }
        L_0059fb6c:
            charge(ctx, 6);
            jal(ctx, 0x59FB6Cu, gen::fn_sub_59FD10_0059fd10);
            a0 = s2;
            jal(ctx, 0x59FB74u, gen::fn_sub_59FCC0_0059fcc0);
            v0 = 0;
        } else {
            // 0x0059fb08
            charge(ctx, 6);
            a2 = 0x7D0000;
            a1 = 0;
            a2 = addiu(a2, -22112);  // "E201194: sfx_InitHn: work size is short."
            jal(ctx, 0x59FB10u, gen::fn_sub_59FD10_0059fd10);
            v0 = 0;
        }
    }
    // 0x0059fb9c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0059FBC0 sub_59FBC0 -- 80 bytes; leaf frame (no stack)
// [sfx_FindFreeHn] SFX: the first free handle of the pool (8 x 148 bytes from 0x7B4938), or 0.
void sub_59FBC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059fbc0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 0;
    v0 = addiu(v0, 18720);  // &0x7B4920
    lw(a1, v0, 4);  // 0x7B4924
    v0 = addiu(v0, 24);  // &0x7B4938
    if (i64(a1) > 0) {
        // 0x0059fbd8
        charge(ctx, 2);
        a0 = v0;
        for (;;) {
            // 0x0059fbe0
            charge(ctx, 4);
            lw(v1, a0, 0);
            v0 = a0;
            a0 = addiu(a0, 148);
            if (v1 == 0) {
                break;
            }
            // 0x0059fbf0
            charge(ctx, 5);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_0059fc04;
            }
            backedge(ctx);
        }
        // 0x0059fc08 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0059fc04:
    charge(ctx, 1);
    v0 = 0;
    // 0x0059fc08 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0059FC10 sub_59FC10 -- 160 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// [sfx_InitHn] SFX: lays out a handle: cleared, in use, the work (+80) and size (+84), the work rounded up to 32
// (+56) and its +1024 / +2048 / +3072 areas, defaults.
void sub_59FC10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059fc10
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    a1 = 0;
    a2 = 148;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    s0 = a0;
    jal(ctx, 0x59FC34u, gen::fn_memset_00521408);
    v1 = addiu(s1, 31);
    v0 = si(-32);
    v1 = v1 & v0;
    a3 = 1;
    a1 = addiu(v1, 3072);
    v0 = addiu(v1, 1024);
    a0 = addiu(v1, 2048);
    a2 = si(-1);
    sw(s1, s0, 80);
    sw(s2, s0, 84);
    sw(a3, s0, 0);
    sw(v0, s0, 60);
    sw(a0, s0, 64);
    sw(a1, s0, 68);
    sw(a2, s0, 88);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(a3, s0, 40);
    sw(zero, s0, 44);
    sw(zero, s0, 52);
    sw(v1, s0, 56);
    sw(zero, s0, 100);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059FCB0 sub_59FCB0 -- 12 bytes; leaf frame (no stack)
// [sfx_IsWorkEnough] SFX: true when the work size is at least 6175 bytes.
void sub_59FCB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059fcb0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = slti(a0, 6175);
    v0 = v0 ^ 0x1;
}

// 0x0059FCC0 sub_59FCC0 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [SFX_Destroy] SFX destroy: frees the handle, its Z and alpha handles, uncounts it.
void sub_59FCC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059fcc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (v0 != 0) {
        // 0x0059fcd4
        charge(ctx, 11);
        lw(a0, v0, 36);
        lw(s0, v0, 48);
        link(ctx, 0x59FCDCu);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 0);
        call(ctx, gen::fn_sub_5A0388_005a0388);
        a0 = s0;
        jal(ctx, 0x59FCE4u, gen::fn_sub_59E8F0_0059e8f0);
        v1 = 0x7B0000;
        v1 = addiu(v1, 18720);  // &0x7B4920
        lw(v0, v1, 0);  // 0x7B4920
        v0 = addiu(v0, -1);
        sw(v0, v1, 0);  // 0x7B4920
    }
    // 0x0059fd00 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059FD50 sub_59FD50 -- 12 bytes; leaf frame (no stack)
// [sfx_SetCnvMode] SFX: stores the setting 0x7B4934; $v0 keeps 0x7B0000.
void sub_59FD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059fd50
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 18740);  // 0x7B4934
}

// 0x005A0238 sub_5A0238 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfx_InitSud] SFX: thunk to SUD's init (sub_5A1108).
void sub_5A0238(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0238
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5A1108_005a1108(ctx);  // tail call
}

// 0x005A0268 sub_5A0268 -- 100 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [sfxz_InitPool] SFX: clears the Z handle pool 0x7B4DE8 (620 bytes): 8 handles.
void sub_5A0268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0268
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a0280
    charge(ctx, 16);
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 19944);  // &0x7B4DE8
    a2 = 620;
    sd(ra, sp, 0x8);
    a0 = s0;
    jal(ctx, 0x5A029Cu, gen::fn_memset_00521408);
    v1 = 8;
    sw(v1, s0, 8);  // 0x7B4DF0
    a0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    // 0x005a0be0
    charge(ctx, 3);
    v0 = 0x7B0000;
    sw(a0, v0, 19948);  // 0x7B4DEC
}

// 0x005A02C8 sub_5A02C8 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [SFXZ_Create] SFX: a Z handle: the first free one, reset, counted, in use.
void sub_5A02C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a02c8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x5A02D4u, gen::fn_sub_5A0320_005a0320);
    s0 = v0;
    a0 = s0;
    if (s0 != 0) {
        // 0x005a02e8
        charge(ctx, 10);
        jal(ctx, 0x5A02E8u, gen::fn_sub_5A0370_005a0370);
        v1 = 0x7B0000;
        v1 = addiu(v1, 19944);  // &0x7B4DE8
        a1 = 1;
        lw(a0, v1, 0);  // 0x7B4DE8
        v0 = s0;
        a0 = addiu(a0, 1);
        sw(a0, v1, 0);  // 0x7B4DE8
        sw(a1, s0, 0);
    }
    // 0x005a0310 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005A0320 sub_5A0320 -- 80 bytes; leaf frame (no stack)
// [sfxz_FindFreeHn] SFX: the first free Z handle (8 x 76 bytes from 0x7B4DF4), or 0.
void sub_5A0320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005a0320
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 0;
    v0 = addiu(v0, 19944);  // &0x7B4DE8
    lw(a1, v0, 8);  // 0x7B4DF0
    v0 = addiu(v0, 12);  // &0x7B4DF4
    if (i64(a1) > 0) {
        // 0x005a0338
        charge(ctx, 2);
        a0 = v0;
        for (;;) {
            // 0x005a0340
            charge(ctx, 4);
            lw(v1, a0, 0);
            v0 = a0;
            a0 = addiu(a0, 76);
            if (v1 == 0) {
                break;
            }
            // 0x005a0350
            charge(ctx, 5);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_005a0364;
            }
            backedge(ctx);
        }
        // 0x005a0368 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005a0364:
    charge(ctx, 1);
    v0 = 0;
    // 0x005a0368 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005A0370 sub_5A0370 -- 24 bytes; leaf frame (no stack)
// [sfxz_ResetHn] SFX: resets a Z handle's fields (+4, +60..+72).
void sub_5A0370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x005a0370
    enter(ctx, 6);  // entry check point + this block's cycles
    sw(zero, a0, 4);
    sw(zero, a0, 60);
    sw(zero, a0, 64);
    sw(zero, a0, 68);
    sw(zero, a0, 72);
}

// 0x005A0388 sub_5A0388 -- 40 bytes; leaf frame (no stack)
// [SFXZ_Destroy] SFX: frees a Z handle and uncounts it.
void sub_5A0388(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005a0388
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x005a0390
        charge(ctx, 6);
        sw(zero, a0, 0);
        v1 = 0x7B0000;
        v1 = addiu(v1, 19944);  // &0x7B4DE8
        lw(v0, v1, 0);  // 0x7B4DE8
        v0 = addiu(v0, -1);
        sw(v0, v1, 0);  // 0x7B4DE8
    }
    // 0x005a03a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005A1108 sub_5A1108 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [SUD_Init] SUD init (counted, 0x7B5058): keeps the banner's address at 0x9ACBF0.
void sub_5A1108(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1108
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 20568);  // &0x7B5058
    lw(v1, s0, 0);  // 0x7B5058
    sd(ra, sp, 0x8);
    if (i64(v1) <= 0) {
        // 0x005a1124
        charge(ctx, 8);
        jal(ctx, 0x5A1124u, gen::fn_sceLibgcc32GetErxEntries_23_005a1158);
        v1 = 0x9B0000;
        lw(a0, s0, 0);
        v1 = addiu(v1, -13328);  // &0x9ACBF0
        sw(v0, v1, 0);  // 0x9ACBF0
        a0 = addiu(a0, 1);
        sw(a0, s0, 0);
    }
    // 0x005a1144 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
