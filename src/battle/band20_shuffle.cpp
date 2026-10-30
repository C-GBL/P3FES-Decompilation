// Phase 5 slice band20 -- Shuffle Time: sfl_data.c tables, gc_model.c (card grid / positions), sfl_res.c (the
// Shuffle Time files), sfl_psel.c, gc_res.c (the card textures), sfl_ground.c and sfl_panel.c.
// The bodies come from p3fes_handgen (register ABI: arguments in $a0.., the result in $v0) and keep every register,
// frame slot, $ra link, cycle charge and check point of the recompiled body (game/include/p3fes/game/hg_cpu.h); this
// file adds the names: one role comment per function ([proposed name] first), named offsets of the records in
// game/include/p3fes/game/band20.h (a constant replaces only a literal of its own value), the K_Assert(file, line)
// calls (`jr $ra` in retail: a failed check carries on), the RW slots the bodies call through, the float constants of
// the $gp area with their values, and `while` notes on the counted loops.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/band20.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_209C80_00209c80(p3fes::EEContext&);
void fn_sub_209D40_00209d40(p3fes::EEContext&);
void fn_sub_209E80_00209e80(p3fes::EEContext&);
void fn_sub_209E90_00209e90(p3fes::EEContext&);
void fn_sub_20C660_0020c660(p3fes::EEContext&);
void fn_sub_20C8D0_0020c8d0(p3fes::EEContext&);
void fn_sub_20CC80_0020cc80(p3fes::EEContext&);
void fn_sub_20D630_0020d630(p3fes::EEContext&);
void fn_sub_20D820_0020d820(p3fes::EEContext&);
void fn_sub_20E030_0020e030(p3fes::EEContext&);
void fn_sub_20E200_0020e200(p3fes::EEContext&);
void fn_sub_20E380_0020e380(p3fes::EEContext&);
void fn_sub_20E3D0_0020e3d0(p3fes::EEContext&);
void fn_sub_20E510_0020e510(p3fes::EEContext&);
void fn_sub_20E590_0020e590(p3fes::EEContext&);
void fn_sub_20E610_0020e610(p3fes::EEContext&);
void fn_sub_20E690_0020e690(p3fes::EEContext&);
void fn_sub_20E790_0020e790(p3fes::EEContext&);
void fn_sub_20E800_0020e800(p3fes::EEContext&);
void fn_sub_20EA80_0020ea80(p3fes::EEContext&);
void fn_sub_20EB40_0020eb40(p3fes::EEContext&);
void fn_sub_20ECC0_0020ecc0(p3fes::EEContext&);
void fn_sub_215AA0_00215aa0(p3fes::EEContext&);
void fn_sub_216800_00216800(p3fes::EEContext&);
void fn_sub_2172C0_002172c0(p3fes::EEContext&);
void fn_sub_219B00_00219b00(p3fes::EEContext&);
void fn_sub_219D90_00219d90(p3fes::EEContext&);
void fn_sub_21A120_0021a120(p3fes::EEContext&);
void fn_sub_21A1B0_0021a1b0(p3fes::EEContext&);
void fn_sub_21A840_0021a840(p3fes::EEContext&);
void fn_sub_21B2D0_0021b2d0(p3fes::EEContext&);
void fn_sub_21B4A0_0021b4a0(p3fes::EEContext&);
void fn_sub_21C9F0_0021c9f0(p3fes::EEContext&);
void fn_sub_21CC20_0021cc20(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21E170_0021e170(p3fes::EEContext&);
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);
void fn_sub_21EC40_0021ec40(p3fes::EEContext&);
void fn_sub_23B990_0023b990(p3fes::EEContext&);
void fn_sub_23C350_0023c350(p3fes::EEContext&);
void fn_sub_23C520_0023c520(p3fes::EEContext&);
void fn_sub_23C850_0023c850(p3fes::EEContext&);
void fn_sub_23C8C0_0023c8c0(p3fes::EEContext&);
void fn_sub_23D0E0_0023d0e0(p3fes::EEContext&);
void fn_sub_23D130_0023d130(p3fes::EEContext&);
void fn_sub_23D1F0_0023d1f0(p3fes::EEContext&);
void fn_sub_23D7B0_0023d7b0(p3fes::EEContext&);
void fn_sub_23D870_0023d870(p3fes::EEContext&);
void fn_sub_23D8F0_0023d8f0(p3fes::EEContext&);
void fn_sub_23DAC0_0023dac0(p3fes::EEContext&);
void fn_sub_23E970_0023e970(p3fes::EEContext&);
void fn_sub_23EE50_0023ee50(p3fes::EEContext&);
void fn_sub_23F390_0023f390(p3fes::EEContext&);
void fn_sub_23F3E0_0023f3e0(p3fes::EEContext&);
void fn_sub_23F430_0023f430(p3fes::EEContext&);
void fn_sub_2496E0_002496e0(p3fes::EEContext&);
void fn_sub_24A180_0024a180(p3fes::EEContext&);
void fn_sub_255130_00255130(p3fes::EEContext&);
void fn_sub_260BD0_00260bd0(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b20;  // the named offsets and $gp slots of band20.h

// 0x00209C80 sub_209C80 -- 64 bytes; frame 0x10: ra sp+0x0
// [sflData_GetTableH] sfl_data.c: the table 0x68AB80 in The Answer (sub_17D800), else 0x6892C0.
void sub_209C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209c80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x209C88u, gen::fn_sub_17D800_0017d800);  // the game-mode test (The Answer)
    if (v0 == 0) {
        // 0x00209ca8
        charge(ctx, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -27968);  // &0x6892C0
    } else {
        // 0x00209c98
        charge(ctx, 4);
        v0 = 0x690000;
        v0 = addiu(v0, -21632);  // &0x68AB80
    }
    // 0x00209cb0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209D40 sub_209D40 -- 124 bytes; frame 0x10: ra sp+0x0
// [sflData_CardSide](s16 *v) maps a card's side word: -1 -> 2, 0 -> 0, 1 -> 1, anything else -> -1 after
// K_Assert line 140.
void sub_209D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209d40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(v1, a0, 0);
    v0 = si(-1);
    if (v1 == v0) {
        // 0x00209d88
        charge(ctx, 3);
        v0 = 2;
    } else {
        // 0x00209d58
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00209d80
            charge(ctx, 2);
        } else {
            // 0x00209d64
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00209d74
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x00209d6c
                charge(ctx, 2);
                // 0x00209d94
                charge(ctx, 6);
                a0 = 0x690000;
                a0 = addiu(a0, -8064);  // "sfl_data.c"
                a1 = 140;
                jal(ctx, 0x209DA0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_data.c", 140): `jr $ra` in retail, execution goes on
                v0 = si(-1);
            }
        }
    }
    // 0x00209dac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209E80 sub_209E80 -- 16 bytes; leaf frame (no stack)
// [sflData_GetTableI] returns the table 0x68DF60.
void sub_209E80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00209e80
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x690000;
    v0 = addiu(v0, -8352);  // &0x68DF60
}

// 0x00209E90 sub_209E90 -- 16 bytes; leaf frame (no stack)
// [sflData_GetTableJ] returns the table 0x68E020.
void sub_209E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00209e90
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x690000;
    v0 = addiu(v0, -8160);  // &0x68E020
}

// 0x0020C660 sub_20C660 -- 320 bytes; frame 0x10: ra sp+0x0
// [gcModel_CardX](i, n) -> $f0 gc_model.c: the screen x of card i of a row of n cards: n = 3..5 -> (i + 1) *
// 640 / (n + 1); n = 6 -> 500 i / 5 + 70; n = 2 -> 200 i + 220; any other n is K_Assert line 1198 and 0.
void sub_20C660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0020c660
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    // n = 5, 4 or 3 (tested in that order, a charge between the tests): (i + 1) * 640 / (n + 1)
    v0 = 5;
    bool even = a1 == v0;
    if (!even) {
        // 0x0020c674
        charge(ctx, 3);
        v0 = 4;
        even = a1 == v0;
        if (!even) {
            // 0x0020c680
            charge(ctx, 3);
            v0 = 3;
            even = a1 == v0;
        }
    }
    if (!even) {
        // 0x0020c68c: n = 6, n = 2, or K_Assert and 0
        charge(ctx, 3);
        v0 = 6;
        if (a1 == v0) {
            // 0x0020c6f0
            charge(ctx, 17);
            v0 = 0x43FA0000;
            mtc1(v0, f1);
            mtc1(a0, f0);
            cvt_s_w(f0, f0);
            mul_s(f1, f1, f0);
            v0 = addiu(a1, -1);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f1, f1, f0);
            v0 = 0x428C0000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
        } else {
            // 0x0020c698
            charge(ctx, 3);
            v0 = 2;
            if (a1 == v0) {
                // 0x0020c6ac
                charge(ctx, 17);
                v0 = 0x43480000;
                mtc1(v0, f1);
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                mul_s(f1, f1, f0);
                v0 = addiu(a1, -1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f1, f1, f0);
                v0 = 0x435C0000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
            } else {
                // 0x0020c6a4
                charge(ctx, 2);
                // 0x0020c778
                charge(ctx, 6);
                a0 = 0x690000;
                a0 = addiu(a0, -8032);  // "gc_model.c"
                a1 = 1198;
                jal(ctx, 0x20C784u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_model.c", 1198): `jr $ra` in retail, execution goes on
                mtc1(zero, f0);
            }
        }
        // 0x0020c790 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0020c734: the even split
    charge(ctx, 17);
    v0 = addiu(a0, 1);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    v0 = addiu(a1, 1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x44200000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    mul_s(f0, f2, f0);
    // 0x0020c790 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020C8D0 sub_20C8D0 -- 448 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcModel_Initialize] "gcm initialize": builds the card grid's triangle index list at 0x875A90 (kwlnInitMain):
// 8 rows of 6 quads, two triangles each, the diagonal alternating per row, plus the row ends -- the 68-vertex grid of
// sub_20CDA0 (battle_ui3).
void sub_20C8D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020c8d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x690000;
    a0 = addiu(a0, -8016);  // "gcm initialize \n"
    jal(ctx, 0x20C8E8u, gen::fn_printf_005225a8);
    t1 = 0;
    s1 = 0x870000;
    s1 = addiu(s1, 23184);  // &0x875A90
    a3 = 0;
    for (;;) {  // while (a3 < 8)
        // 0x0020c9dc
        charge(ctx, 3);
        v1 = slti(a3, 8);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020c908
        charge(ctx, 5);
        t0 = 0;
        v1 = nor(a3, 0);
        a2 = v1 & 0x1;
        for (;;) {  // while (t0 < 6)
            // 0x0020c984
            charge(ctx, 3);
            v1 = slti(t0, 6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020c91c
            charge(ctx, 2);
            if (a2 == 0) {
                // 0x0020c958
                charge(ctx, 10);
                sh(t1, s1, 0);
                a0 = addiu(t1, 8);
                sh(a0, s1, 2);
                v1 = addiu(t1, 7);
                sh(v1, s1, 4);
                sh(t1, s1, 6);
                t1 = addiu(t1, 1);
                sh(t1, s1, 8);
                sh(a0, s1, 10);
                s1 = addiu(s1, 12);
            } else {
                // 0x0020c924
                charge(ctx, 13);
                sh(t1, s1, 0);
                a1 = addiu(t1, 1);
                sh(a1, s1, 2);
                a0 = addiu(t1, 8);
                sh(a0, s1, 4);
                sh(a1, s1, 6);
                v1 = addiu(t1, 9);
                sh(v1, s1, 8);
                sh(a0, s1, 10);
                s1 = addiu(s1, 12);
                t1 = a1;
            }
            // 0x0020c980
            charge(ctx, 1);
            t0 = addiu(t0, 1);
        }
        // 0x0020c990
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x0020c9bc
            charge(ctx, 7);
            sh(t1, s1, 0);
            v1 = addiu(t1, 8);
            sh(v1, s1, 2);
            v1 = addiu(t1, 7);
            sh(v1, s1, 4);
            s1 = addiu(s1, 6);
            t1 = addiu(t1, 1);
        } else {
            // 0x0020c998
            charge(ctx, 9);
            sh(t1, s1, 0);
            v1 = addiu(t1, 1);
            sh(v1, s1, 2);
            v1 = addiu(t1, 8);
            sh(v1, s1, 4);
            s1 = addiu(s1, 6);
            t1 = addiu(t1, 2);
        }
        // 0x0020c9d8
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x0020c9e8
    charge(ctx, 3);
    s0 = 0;
    for (;;) {  // while (s0 < 312)
        // 0x0020ca2c
        charge(ctx, 3);
        v1 = slti(s0, 312);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020c9f4
        charge(ctx, 8);
        a0 = sll(s0, 1);
        v1 = 0x870000;
        v1 = addiu(v1, 23184);  // &0x875A90
        v1 = addu(v1, a0);
        lhu(v1, v1, 0);
        v1 = slti(v1, 68);
        if (v1 == 0) {
            // 0x0020ca14
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -8032);  // "gc_model.c"
            a1 = 1301;
            jal(ctx, 0x20CA20u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_model.c", 1301): `jr $ra` in retail, execution goes on
        }
        // 0x0020ca28
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0020ca38
    charge(ctx, 6);
    v1 = 0x870000;
    v1 = addiu(v1, 23184);  // &0x875A90
    v1 = subu(s1, v1);
    a0 = sra(v1, 1);
    if (i64(v1) < 0) {
        // 0x0020ca50
        charge(ctx, 2);
        v1 = addiu(v1, 1);
        a0 = sra(v1, 1);
    }
    // 0x0020ca58
    charge(ctx, 3);
    v1 = 312;
    if (a0 != v1) {
        // 0x0020ca64
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -8032);  // "gc_model.c"
        a1 = 1303;
        jal(ctx, 0x20CA70u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_model.c", 1303): `jr $ra` in retail, execution goes on
    }
    // 0x0020ca78 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020CC80 sub_20CC80 -- 52 bytes; leaf frame (no stack)
// [gcModel_SetColour](model, rgba*) copies the four colour bytes to model +64 and sets flag bit 2.
void sub_20CC80(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0020cc80
    enter(ctx, 13);  // entry check point + this block's cycles
    lbu(t0, a1, 0);
    lbu(a3, a1, 1);
    lbu(a2, a1, 2);
    lbu(v1, a1, 3);
    sb(t0, a0, 64);
    sb(a3, a0, 65);
    sb(a2, a0, 66);
    sb(v1, a0, 67);
    lw(v1, a0, 0);
    v1 = v1 | 0x4;
    sw(v1, a0, 0);
}

// 0x0020D630 sub_20D630 -- 32 bytes; leaf frame (no stack)
// [gcModel_SetScale](model, xyz*) copies three floats to model +44 / +48 / +52.
void sub_20D630(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0020d630
    enter(ctx, 8);  // entry check point + this block's cycles
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, a0, 44);
    swc1(f1, a0, 48);
    swc1(f0, a0, 52);
}

// 0x0020D820 sub_20D820 -- 1980 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_Update] sfl_res.c's per-frame loader. For each requested file whose H_Cdvd node has loaded:
// sfl_base.bin (15 files: rasters into +20.. / +40.., file 3 / 13 / 14 copied into RwMalloc blocks, file 11 to gc_res
// sub_21B4A0); sfl_ground.bin (sub_20E800: three rasters); sfl_effect.bin (six rasters); sfl_tutorial.bin (two heap
// blocks); i_change_per01.spr (a sprite set). Each moves its bit from +0 to +4 and destroys the node. The tutorial
// branch destroys its node inside the two-file loop (after the first file) and reads the second file from it.
void sub_20D820(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020d820
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v1 == 0) {
        // 0x0020d844: the slot is empty: K_Assert (retail carries on)
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20D850u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020d858
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v1, s0, kSrRequested);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0020d86c
        charge(ctx, 5);
        lw(a0, s0, kSrLoaded);
        v1 = nor(a0, 0);
        v1 = v1 & 0x2;
        if (v1 == 0) {
            // 0x0020db84
            charge(ctx, 3);
            v1 = a0 & 0x2;
            if (v1 == 0) {
                // 0x0020db90
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7912);  // "sfl_res.c"
                a1 = 198;
                jal(ctx, 0x20DB9Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 198): `jr $ra` in retail, execution goes on
            }
        } else {
            // 0x0020d880
            charge(ctx, 5);
            lw(a0, s0, kSrBaseNode);
            jal(ctx, 0x20D884u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
            if (v0 != 0) {
                // 0x0020d894
                charge(ctx, 3);
                s2 = 0;
                for (;;) {  // while (s2 < 15)
                    // 0x0020db58
                    charge(ctx, 3);
                    v0 = slti(s2, 15);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0020d8a0
                    charge(ctx, 3);
                    at = sltiu(s2, 15);
                    if (at == 0) {
                        // 0x0020db40
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7912);  // "sfl_res.c"
                        a1 = 187;
                        jal(ctx, 0x20DB4Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 187): `jr $ra` in retail, execution goes on
                    } else {
                        // 0x0020d8ac
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 29696);  // &0x7B7400
                        v0 = sll(s2, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x20D8C8u:  // table[0]
                            // 0x0020d8c8
                            charge(ctx, 11);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20D8D4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20D8E0u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 20);
                            break;
                        case 0x20D8F4u:  // table[1]
                            // 0x0020d8f4
                            charge(ctx, 11);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20D900u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20D90Cu, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 24);
                            break;
                        case 0x20D920u:  // table[2]
                            // 0x0020d920
                            charge(ctx, 11);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20D92Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20D938u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 28);
                            break;
                        case 0x20D94Cu:  // table[3]
                            // 0x0020d94c
                            charge(ctx, 20);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20D958u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s1 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x20D974u, v0.u());
                            sw(v0, s0, 88);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s1;
                            jal(ctx, 0x20D98Cu, gen::fn_memcpy_00521250);
                            break;
                        case 0x20D99Cu:  // table[4]
                            // 0x0020d99c
                            charge(ctx, 11);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20D9A8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20D9B4u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 32);
                            break;
                        case 0x20D9C8u:  // table[5, 6, 7, 8, 9, 10]
                            // 0x0020d9c8
                            charge(ctx, 9);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20D9D4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s1 = v0;
                            v0 = addiu(s2, -5);
                            if (i64(v0) < 0) {
                                // 0x0020d9ec
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, -7912);  // "sfl_res.c"
                                a1 = 162;
                                jal(ctx, 0x20D9F8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 162): `jr $ra` in retail, execution goes on
                            }
                            // 0x0020da00
                            charge(ctx, 4);
                            v0 = addiu(s2, -5);
                            v0 = slti(v0, 6);
                            if (v0 == 0) {
                                // 0x0020da10
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, -7912);  // "sfl_res.c"
                                a1 = 163;
                                jal(ctx, 0x20DA1Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 163): `jr $ra` in retail, execution goes on
                            }
                            // 0x0020da24
                            charge(ctx, 8);
                            a0 = s1;
                            jal(ctx, 0x20DA28u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            v1 = sll(s2, 2);
                            v1 = addu(s0, v1);
                            sw(v0, v1, 20);
                            break;
                        case 0x20DA44u:  // table[11]
                            // 0x0020da44
                            charge(ctx, 10);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DA50u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DA5Cu, gen::fn_sub_21B4A0_0021b4a0);
                            break;
                        case 0x20DA6Cu:  // table[12]
                            // 0x0020da6c
                            charge(ctx, 11);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DA78u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DA84u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 36);
                            break;
                        case 0x20DA98u:  // table[13]
                            // 0x0020da98
                            charge(ctx, 21);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DAA4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s1 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x20DAC0u, v0.u());
                            s3 = v0;
                            lw(a2, sp, 0x5C);
                            a0 = s3;
                            a1 = s1;
                            jal(ctx, 0x20DAD8u, gen::fn_memcpy_00521250);
                            sw(s3, s0, 120);
                            break;
                        case 0x20DAECu:  // table[14]
                            // 0x0020daec
                            charge(ctx, 21);
                            lw(a0, s0, 104);
                            a1 = s2;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DAF8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s1 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x20DB14u, v0.u());
                            s3 = v0;
                            lw(a2, sp, 0x5C);
                            a0 = s3;
                            a1 = s1;
                            jal(ctx, 0x20DB2Cu, gen::fn_memcpy_00521250);
                            sw(s3, s0, 124);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                    // 0x0020db54
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0020db64
                charge(ctx, 8);
                lw(a0, s0, kSrBaseNode);
                jal(ctx, 0x20DB68u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                lw(v1, s0, kSrLoaded);
                v1 = v1 | 0x2;
                sw(v1, s0, kSrLoaded);
            }
        }
        // 0x0020dba4
        charge(ctx, 4);
        lw(v1, s0, kSrLoaded);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            // 0x0020dbb4
            charge(ctx, 4);
            lw(a0, s0, kSrRequested);
            v1 = si(-2);
            v1 = a0 & v1;
            sw(v1, s0, kSrRequested);
        }
    }
    // 0x0020dbc4
    charge(ctx, 4);
    lw(v1, s0, kSrRequested);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0020dbd4
        charge(ctx, 5);
        lw(a0, s0, kSrGroundNode);
        jal(ctx, 0x20DBD8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0020dbe8
            charge(ctx, 5);
            lw(v0, s0, kSrLoaded);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0020dbfc
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7912);  // "sfl_res.c"
                a1 = 210;
                jal(ctx, 0x20DC08u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 210): `jr $ra` in retail, execution goes on
            }
            // 0x0020dc10
            charge(ctx, 14);
            lw(v0, s0, kSrGroundNode);
            lw(a0, v0, 272);
            jal(ctx, 0x20DC18u, gen::fn_sub_20E800_0020e800);
            lw(a0, s0, kSrGroundNode);
            jal(ctx, 0x20DC24u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
            lw(v1, s0, kSrLoaded);
            v1 = v1 | 0x1;
            sw(v1, s0, kSrLoaded);
            lw(a0, s0, kSrRequested);
            v1 = si(-3);
            v1 = a0 & v1;
            sw(v1, s0, kSrRequested);
        }
    }
    // 0x0020dc48
    charge(ctx, 4);
    lw(v1, s0, kSrRequested);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0020dc58
        charge(ctx, 5);
        lw(a0, s0, kSrLoaded);
        v1 = nor(a0, 0);
        v1 = v1 & 0x4;
        if (v1 == 0) {
            // 0x0020de00
            charge(ctx, 3);
            v1 = a0 & 0x4;
            if (v1 == 0) {
                // 0x0020de0c
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7912);  // "sfl_res.c"
                a1 = 265;
                jal(ctx, 0x20DE18u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 265): `jr $ra` in retail, execution goes on
            }
        } else {
            // 0x0020dc6c
            charge(ctx, 5);
            lw(a0, s0, kSrEffectNode);
            jal(ctx, 0x20DC70u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
            if (v0 != 0) {
                // 0x0020dc80
                charge(ctx, 3);
                s1 = 0;
                for (;;) {  // while (s1 < 6)
                    // 0x0020ddd4
                    charge(ctx, 3);
                    v0 = slti(s1, 6);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0020dc8c
                    charge(ctx, 3);
                    at = sltiu(s1, 6);
                    if (at == 0) {
                        // 0x0020ddbc
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7912);  // "sfl_res.c"
                        a1 = 254;
                        jal(ctx, 0x20DDC8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 254): `jr $ra` in retail, execution goes on
                    } else {
                        // 0x0020dc98
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 29664);  // &0x7B73E0
                        v0 = sll(s1, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x20DCB4u:  // table[0]
                            // 0x0020dcb4
                            charge(ctx, 11);
                            lw(a0, s0, 108);
                            a1 = s1;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DCC0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DCCCu, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 64);
                            break;
                        case 0x20DCE0u:  // table[1]
                            // 0x0020dce0
                            charge(ctx, 11);
                            lw(a0, s0, 108);
                            a1 = s1;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DCECu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DCF8u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 68);
                            break;
                        case 0x20DD0Cu:  // table[2]
                            // 0x0020dd0c
                            charge(ctx, 11);
                            lw(a0, s0, 108);
                            a1 = s1;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DD18u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DD24u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 72);
                            break;
                        case 0x20DD38u:  // table[3]
                            // 0x0020dd38
                            charge(ctx, 11);
                            lw(a0, s0, 108);
                            a1 = s1;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DD44u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DD50u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 76);
                            break;
                        case 0x20DD64u:  // table[4]
                            // 0x0020dd64
                            charge(ctx, 11);
                            lw(a0, s0, 108);
                            a1 = s1;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DD70u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DD7Cu, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 80);
                            break;
                        case 0x20DD90u:  // table[5]
                            // 0x0020dd90
                            charge(ctx, 11);
                            lw(a0, s0, 108);
                            a1 = s1;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x20DD9Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x20DDA8u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            sw(v0, s0, 84);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                    // 0x0020ddd0
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x0020dde0
                charge(ctx, 8);
                lw(a0, s0, kSrEffectNode);
                jal(ctx, 0x20DDE4u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                lw(v1, s0, kSrLoaded);
                v1 = v1 | 0x4;
                sw(v1, s0, kSrLoaded);
            }
        }
        // 0x0020de20
        charge(ctx, 4);
        lw(v1, s0, kSrLoaded);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0020de30
            charge(ctx, 4);
            lw(a0, s0, kSrRequested);
            v1 = si(-5);
            v1 = a0 & v1;
            sw(v1, s0, kSrRequested);
        }
    }
    // 0x0020de40
    charge(ctx, 4);
    lw(v1, s0, kSrRequested);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x0020de50
        charge(ctx, 5);
        lw(a0, s0, kSrTutorialNode);
        jal(ctx, 0x20DE54u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0020de64
            charge(ctx, 3);
            s1 = 0;
            for (;;) {  // while (s1 < 2)
                // 0x0020df50
                charge(ctx, 3);
                v1 = slti(s1, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0020de70
                charge(ctx, 3);
                v0 = 1;
                if (s1 == v0) {
                    // 0x0020dedc
                    charge(ctx, 18);
                    lw(a0, s0, kSrTutorialNode);
                    a1 = s1;
                    a2 = addiu(sp, 0x5C);
                    jal(ctx, 0x20DEE8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                    s2 = v0;
                    lw(a0, sp, 0x5C);
                    a1 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                    jalr(ctx, 0x20DF04u, v0.u());
                    sw(v0, s0, 96);
                    lw(a2, sp, 0x5C);
                    a0 = v0;
                    a1 = s2;
                    jal(ctx, 0x20DF1Cu, gen::fn_memcpy_00521250);
                } else {
                    // 0x0020de7c
                    charge(ctx, 2);
                    if (s1 == 0) {
                        // 0x0020de8c
                        charge(ctx, 20);
                        lw(a0, s0, kSrTutorialNode);
                        a1 = s1;
                        a2 = addiu(sp, 0x5C);
                        jal(ctx, 0x20DE98u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                        s2 = v0;
                        lw(a0, sp, 0x5C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                        jalr(ctx, 0x20DEB4u, v0.u());
                        sw(v0, s0, kSrTutorial);
                        lw(a2, sp, 0x5C);
                        a0 = v0;
                        a1 = s2;
                        jal(ctx, 0x20DECCu, gen::fn_memcpy_00521250);
                    } else {
                        // 0x0020de84
                        charge(ctx, 2);
                    }
                }
                // 0x0020df24
                charge(ctx, 11);
                lw(a0, s0, kSrTutorialNode);
                jal(ctx, 0x20DF28u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                lw(v1, s0, kSrLoaded);
                v1 = v1 | 0x8;
                sw(v1, s0, kSrLoaded);
                lw(a0, s0, kSrRequested);
                v1 = si(-9);
                v1 = a0 & v1;
                sw(v1, s0, kSrRequested);
                s1 = addiu(s1, 1);
            }
        }
    }
    // 0x0020df5c
    charge(ctx, 4);
    lw(v1, s0, kSrRequested);
    v1 = v1 & 0x10;
    if (v1 != 0) {
        // 0x0020df6c
        charge(ctx, 5);
        lw(a0, s0, kSrSprNode);
        jal(ctx, 0x20DF70u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0020df80
            charge(ctx, 15);
            lw(v0, s0, kSrSprNode);
            lw(a0, v0, 272);
            jal(ctx, 0x20DF88u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
            sw(v0, s0, kSrSprSet);
            lw(a0, s0, kSrSprNode);
            jal(ctx, 0x20DF98u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
            lw(v1, s0, kSrLoaded);
            v1 = v1 | 0x10;
            sw(v1, s0, kSrLoaded);
            lw(a0, s0, kSrRequested);
            v1 = si(-17);
            v1 = a0 & v1;
            sw(v1, s0, kSrRequested);
        }
    }
    // 0x0020dfbc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0020E030 sub_20E030 -- 452 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_Release] frees everything sfl_res.c loaded (by the loaded bits: rasters through sub_4CDE90, heap
// blocks through the RwFree slot, the sprite set through sub_20ECC0) and clears the $gp slot.
void sub_20E030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e030
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v1 == 0) {
        // 0x0020e050
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E05Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e064
    charge(ctx, 5);
    lw(s1, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v1, s1, kSrLoaded);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x0020e078
        charge(ctx, 2);
        jal(ctx, 0x20E078u, gen::fn_sub_20EA80_0020ea80);
    }
    // 0x0020e080
    charge(ctx, 4);
    lw(v1, s1, kSrLoaded);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0020e090
        charge(ctx, 9);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C
        lw(a0, s1, kSrBaseBlock);
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x20E0A0u, v0.u());
        s2 = 0;
        for (;;) {  // while (s2 < 5)
            // 0x0020e0cc
            charge(ctx, 3);
            v1 = slti(s2, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020e0b4
            charge(ctx, 6);
            v0 = sll(s2, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kSrBase);
            jal(ctx, 0x20E0C0u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
            s2 = addiu(s2, 1);
        }
        // 0x0020e0d8
        charge(ctx, 3);
        s2 = 0;
        for (;;) {  // while (s2 < 6)
            // 0x0020e0fc
            charge(ctx, 3);
            v1 = slti(s2, 6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020e0e4
            charge(ctx, 6);
            v0 = sll(s2, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kSrBaseB);
            jal(ctx, 0x20E0F0u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
            s2 = addiu(s2, 1);
        }
        // 0x0020e108
        charge(ctx, 3);
        s2 = 0;
        for (;;) {  // while (s2 < 2)
            // 0x0020e130
            charge(ctx, 3);
            v1 = slti(s2, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020e114
            charge(ctx, 7);
            v0 = sll(s2, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kSrBaseBlocks);
            lw(v0, s0, 0);
            jalr(ctx, 0x20E124u, v0.u());
            s2 = addiu(s2, 1);
        }
    }
    // 0x0020e13c
    charge(ctx, 4);
    lw(v1, s1, kSrLoaded);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0020e14c
        charge(ctx, 3);
        s0 = 0;
        for (;;) {  // while (s0 < 3)
            // 0x0020e170
            charge(ctx, 3);
            v1 = slti(s0, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020e158
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kSrGround);
            jal(ctx, 0x20E164u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
            s0 = addiu(s0, 1);
        }
    }
    // 0x0020e17c
    charge(ctx, 4);
    lw(v1, s1, kSrLoaded);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0020e18c
        charge(ctx, 3);
        s0 = 0;
        for (;;) {  // while (s0 < 6)
            // 0x0020e1b0
            charge(ctx, 3);
            v1 = slti(s0, 6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020e198
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kSrEffect);
            jal(ctx, 0x20E1A4u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
            s0 = addiu(s0, 1);
        }
    }
    // 0x0020e1bc
    charge(ctx, 4);
    lw(v1, s1, kSrLoaded);
    v1 = v1 & 0x10;
    if (v1 != 0) {
        // 0x0020e1cc
        charge(ctx, 2);
        jal(ctx, 0x20E1CCu, gen::fn_sub_20ECC0_0020ecc0);
    }
    // 0x0020e1d4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0020E200 sub_20E200 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRes_RequestBase] requests battle/shuffle/sfl_base.bin (archive) into +104, requested bit 0;
// K_Assert 384 / 385 if it is loaded or requested already.
void sub_20E200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e200
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020e218
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E224u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e22c
    charge(ctx, 6);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0020e244
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 384;
        jal(ctx, 0x20E250u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 384): `jr $ra` in retail, execution goes on
    }
    // 0x0020e258
    charge(ctx, 5);
    lw(v0, s0, kSrRequested);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0020e26c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 385;
        jal(ctx, 0x20E278u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 385): `jr $ra` in retail, execution goes on
    }
    // 0x0020e280
    charge(ctx, 14);
    a0 = 0x690000;
    a0 = addiu(a0, -7888);  // "battle/shuffle/sfl_base.bin"
    a1 = 1;
    jal(ctx, 0x20E28Cu, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
    sw(v0, s0, kSrBaseNode);
    lw(v1, s0, kSrRequested);
    v1 = v1 | 0x1;
    sw(v1, s0, kSrRequested);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020E380 sub_20E380 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflRes_IsGroundPending] returns requested & 2 (sfl_ground.bin not in yet).
void sub_20E380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e380
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020e394
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E3A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e3a8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, v0, kSrRequested);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020E3D0 sub_20E3D0 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRes_RequestEffect] requests battle/shuffle/AGS_sfl_effect.bin (The Answer) or sfl_effect.bin into +108,
// requested bit 2.
void sub_20E3D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e3d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020e3e8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E3F4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e3fc
    charge(ctx, 6);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x0020e414
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 411;
        jal(ctx, 0x20E420u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 411): `jr $ra` in retail, execution goes on
    }
    // 0x0020e428
    charge(ctx, 5);
    lw(v0, s0, kSrRequested);
    v0 = nor(v0, 0);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x0020e43c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 412;
        jal(ctx, 0x20E448u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 412): `jr $ra` in retail, execution goes on
    }
    // 0x0020e450
    charge(ctx, 4);
    jal(ctx, 0x20E450u, gen::fn_sub_17D800_0017d800);  // the game-mode test (The Answer)
    if (v0 == 0) {
        // 0x0020e480
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -7776);  // "battle/shuffle/sfl_effect.bin"
        a1 = 1;
        jal(ctx, 0x20E48Cu, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
        sw(v0, s0, kSrEffectNode);
    } else {
        // 0x0020e460
        charge(ctx, 8);
        a0 = 0x690000;
        a0 = addiu(a0, -7824);  // "battle/shuffle/AGS_sfl_effect.bin"
        a1 = 1;
        jal(ctx, 0x20E46Cu, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
        sw(v0, s0, kSrEffectNode);
    }
    // 0x0020e498 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s0, kSrRequested);
    v1 = v1 | 0x4;
    sw(v1, s0, kSrRequested);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020E610 sub_20E610 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_GetBaseB](i) the base raster +40 + 4 i (asserts the base archive is loaded, line 453).
void sub_20E610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e610
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020e630
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E63Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e644
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrLoaded);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0020e658
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 453;
        jal(ctx, 0x20E664u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 453): `jr $ra` in retail, execution goes on
    }
    // 0x0020e66c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kSrBaseB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020E790 sub_20E790 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRes_GetBaseBlock] the heap copy of base file 3 (+88).
void sub_20E790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e790
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020e7a8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E7B4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e7bc
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrLoaded);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0020e7d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 474;
        jal(ctx, 0x20E7DCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 474): `jr $ra` in retail, execution goes on
    }
    // 0x0020e7e4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, kSrBaseBlock);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020E800 sub_20E800 -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_SetGround](file) takes sfl_ground.bin (a 3-entry table: u16 count +4 must be 3, K_Assert 487) and
// builds its three rasters into +8 / +12 / +16; loaded bit 0.
void sub_20E800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e800
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020e824
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E830u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020e838
    charge(ctx, 6);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0020e850
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 483;
        jal(ctx, 0x20E85Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 483): `jr $ra` in retail, execution goes on
    }
    // 0x0020e864
    charge(ctx, 4);
    lhu(v1, s1, 4);
    v0 = 3;
    if (v1 != v0) {
        // 0x0020e874
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 487;
        jal(ctx, 0x20E880u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 487): `jr $ra` in retail, execution goes on
    }
    // 0x0020e888
    charge(ctx, 26);
    s2 = addiu(s1, 8);
    lw(v0, s1, 8);
    a0 = addu(s1, v0);
    jal(ctx, 0x20E894u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
    sw(v0, s0, kSrGround);
    lw(v0, s2, 8);
    a0 = addu(s1, v0);
    jal(ctx, 0x20E8A8u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
    sw(v0, s0, kSrGround1);
    lw(v0, s2, 16);
    a0 = addu(s1, v0);
    jal(ctx, 0x20E8BCu, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
    sw(v0, s0, kSrGround2);
    lw(v1, s0, kSrLoaded);
    v1 = v1 | 0x1;
    sw(v1, s0, kSrLoaded);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0020EA80 sub_20EA80 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_FreeTutorial] frees the two tutorial blocks (+92, +96) through the RwFree slot; clears loaded bit 3.
void sub_20EA80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020ea80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v1 == 0) {
        // 0x0020ea9c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20EAA8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020eab0
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v1, s0, kSrLoaded);
    v1 = v1 & 0x8;
    if (v1 == 0) {
        // 0x0020eac4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 524;
        jal(ctx, 0x20EAD0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 524): `jr $ra` in retail, execution goes on
    }
    // 0x0020ead8
    charge(ctx, 3);
    s1 = 0;
    for (;;) {  // while (s1 < 2)
        // 0x0020eb04
        charge(ctx, 3);
        v1 = slti(s1, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020eae4
        charge(ctx, 8);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kSrTutorial);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x20EAF8u, v0.u());
        s1 = addiu(s1, 1);
    }
    // 0x0020eb10
    charge(ctx, 10);
    lw(a0, s0, kSrLoaded);
    v1 = si(-9);
    v1 = a0 & v1;
    sw(v1, s0, kSrLoaded);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020EB40 sub_20EB40 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRes_RequestSpr] requests battle/shuffle/i_change_per01.spr (not an archive) into +116, requested bit 4.
void sub_20EB40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020eb40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020eb58
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20EB64u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020eb6c
    charge(ctx, 6);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrRequested);
    v0 = nor(v0, 0);
    v0 = v0 & 0x10;
    if (v0 == 0) {
        // 0x0020eb84
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 536;
        jal(ctx, 0x20EB90u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 536): `jr $ra` in retail, execution goes on
    }
    // 0x0020eb98
    charge(ctx, 5);
    lw(v0, s0, kSrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x10;
    if (v0 == 0) {
        // 0x0020ebac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 537;
        jal(ctx, 0x20EBB8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 537): `jr $ra` in retail, execution goes on
    }
    // 0x0020ebc0
    charge(ctx, 14);
    a0 = 0x690000;
    a0 = addiu(a0, -7712);  // "battle/shuffle/i_change_per01.spr"
    a1 = 0;
    jal(ctx, 0x20EBCCu, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
    sw(v0, s0, kSrSprNode);
    lw(v1, s0, kSrRequested);
    v1 = v1 | 0x10;
    sw(v1, s0, kSrRequested);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020ECC0 sub_20ECC0 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRes_FreeSpr] destroys the i_change_per01.spr sprite set (+128); clears loaded bit 4.
void sub_20ECC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020ecc0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    if (v0 == 0) {
        // 0x0020ecd8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20ECE4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0020ecec
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0 sfl_res.c work (the Shuffle Time resources)
    lw(v0, s0, kSrLoaded);
    v0 = v0 & 0x10;
    if (v0 == 0) {
        // 0x0020ed00
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 562;
        jal(ctx, 0x20ED0Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_res.c", 562): `jr $ra` in retail, execution goes on
    }
    // 0x0020ed14
    charge(ctx, 12);
    lw(a0, s0, kSrSprSet);
    jal(ctx, 0x20ED18u, gen::fn_sub_21CC20_0021cc20);  // [bpTex_DestroySpriteSet](set)
    lw(a0, s0, kSrLoaded);
    v1 = si(-17);
    v1 = a0 & v1;
    sw(v1, s0, kSrLoaded);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00215AA0 sub_215AA0 -- 88 bytes; frame 0x10: ra sp+0x0
// [sflPsel_Unregister] sfl_psel.c: closes the persona select if it is open and clears the slot.
void sub_215AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00215aa0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    if (v1 == 0) {
        // 0x00215ab4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 203;
        jal(ctx, 0x215AC0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_psel.c", 203): `jr $ra` in retail, execution goes on
    }
    // 0x00215ac8
    charge(ctx, 5);
    lw(v1, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    lw(v1, v1, kPsFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x00215adc
        charge(ctx, 2);
        jal(ctx, 0x215ADCu, gen::fn_sub_216800_00216800);
    }
    // 0x00215ae4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00216800 sub_216800 -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPsel_Close] closes the persona select: sub_260BD0, destroys the entries' font chains (sub_2172C0)
// and the caption (sub_219B00, bit 3); clears bit 0.
void sub_216800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00216800
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    if (v0 == 0) {
        // 0x00216818
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 203;
        jal(ctx, 0x216824u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_psel.c", 203): `jr $ra` in retail, execution goes on
    }
    // 0x0021682c
    charge(ctx, 5);
    lw(s0, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    lw(v0, s0, kPsFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00216840
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 687;
        jal(ctx, 0x21684Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_psel.c", 687): `jr $ra` in retail, execution goes on
    }
    // 0x00216854
    charge(ctx, 8);
    jal(ctx, 0x216854u, gen::fn_sub_260BD0_00260bd0);
    jal(ctx, 0x21685Cu, gen::fn_sub_2172C0_002172c0);
    lw(v1, s0, kPsFlags);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x00216874
        charge(ctx, 2);
        jal(ctx, 0x216874u, gen::fn_sub_219B00_00219b00);
    }
    // 0x0021687c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, kPsFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, kPsFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002172C0 sub_2172C0 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflPsel_DestroyChains] destroys the font chain of each entry (2,320-byte stride, chain at +2640).
void sub_2172C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002172c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    if (v1 == 0) {
        // 0x002172dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 203;
        jal(ctx, 0x2172E8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_psel.c", 203): `jr $ra` in retail, execution goes on
    }
    // 0x002172f0
    charge(ctx, 4);
    lw(s0, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    s1 = 0;
    for (;;) {
        // 0x00217328
        charge(ctx, 4);
        lw(v1, s0, kPsCount);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00217300
        charge(ctx, 10);
        v0 = sll(s1, 3);
        v0 = addu(v0, s1);
        v0 = sll(v0, 4);
        v0 = addu(v0, s1);
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        lw(a0, v0, 2640);
        jal(ctx, 0x21731Cu, gen::fn_sub_3B0170_003b0170);  // [frFontDestroyChain](chain)
        s1 = addiu(s1, 1);
    }
    // 0x00217338
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00219B00 sub_219B00 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPsel_DestroyCaption] destroys the caption chain (+21200); clears bit 3 (K_Assert 2075 if not set).
void sub_219B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00219b00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    if (v0 == 0) {
        // 0x00219b18
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 203;
        jal(ctx, 0x219B24u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_psel.c", 203): `jr $ra` in retail, execution goes on
    }
    // 0x00219b2c
    charge(ctx, 5);
    lw(s0, gp, kGpSflPsel);  // 0x7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
    lw(v0, s0, kPsFlags);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x00219b40
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 2075;
        jal(ctx, 0x219B4Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_psel.c", 2075): `jr $ra` in retail, execution goes on
    }
    // 0x00219b54
    charge(ctx, 12);
    lw(a0, s0, kPsCaption);
    jal(ctx, 0x219B58u, gen::fn_sub_3B0170_003b0170);  // [frFontDestroyChain](chain)
    lw(a0, s0, kPsFlags);
    v1 = si(-9);
    v1 = a0 & v1;
    sw(v1, s0, kPsFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00219D90 sub_219D90 -- 904 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_Update] gc_res.c's loader: walks the 32 load slots; a slot whose file has loaded becomes a raster
// (sub_21EC40 on the file's image) in the id record (kind 1), raster B (kind 2 index 1: the back texture) or raster A
// (kind 2 index 0), then the node is destroyed and the slot freed. Kind 2 of the slot itself is K_Assert line 248.
void sub_219D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00219d90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    if (v1 == 0) {
        // 0x00219db0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x219DBCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 124): `jr $ra` in retail, execution goes on
    }
    // 0x00219dc4
    charge(ctx, 4);
    lw(s1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    s2 = 0;
    for (;;) {  // while (s2 < 32)
        // 0x0021a0f0
        charge(ctx, 3);
        v1 = slti(s2, 32);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00219dd4
        charge(ctx, 12);
        v1 = sll(s2, 3);
        v1 = addu(v1, s2);
        v1 = sll(v1, 3);
        v1 = addu(v1, s2);
        v1 = sll(v1, 2);
        v1 = addu(s1, v1);
        s0 = addiu(v1, kGrSlots);
        lw(v1, v1, kGrSlots);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x00219e04
            charge(ctx, 4);
            lw(a0, s0, 4);
            v1 = 2;
            if (a0 == v1) {
                // 0x0021a0d8
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7624);  // "gc_res.c"
                a1 = 248;
                jal(ctx, 0x21A0E4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 248): `jr $ra` in retail, execution goes on
            } else {
                // 0x00219e14
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00219e4c
                    charge(ctx, 5);
                    lw(a0, s0, 8);
                    jal(ctx, 0x219E50u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
                    if (v0 != 0) {
                        // 0x00219e60
                        charge(ctx, 4);
                        lw(a1, s0, 272);
                        a0 = 1;
                        if (a1 == a0) {
                            // 0x0021a040
                            charge(ctx, 8);
                            lw(v0, s0, 276);
                            v0 = sll(v0, 4);
                            v0 = addu(s1, v0);
                            lw(v0, v0, kGrIds);
                            v0 = nor(v0, 0);
                            v0 = v0 & 0x2;
                            if (v0 == 0) {
                                // 0x0021a060
                                charge(ctx, 5);
                                a0 = 0x690000;
                                a0 = addiu(a0, -7624);  // "gc_res.c"
                                a1 = 235;
                                jal(ctx, 0x21A06Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 235): `jr $ra` in retail, execution goes on
                            }
                            // 0x0021a074
                            charge(ctx, 21);
                            lw(v0, s0, 8);
                            lw(a0, v0, 272);
                            jal(ctx, 0x21A07Cu, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                            lw(v1, s0, 276);
                            v1 = sll(v1, 4);
                            v1 = addu(s1, v1);
                            sw(v0, v1, 404);
                            lw(v0, s0, 276);
                            v0 = sll(v0, 4);
                            v1 = addu(s1, v0);
                            lw(v0, v1, kGrIds);
                            v0 = v0 | 0x2;
                            sw(v0, v1, kGrIds);
                            lw(a0, s0, 8);
                            jal(ctx, 0x21A0B0u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                            lw(a0, s0, 0);
                            v1 = si(-2);
                            v1 = a0 & v1;
                            sw(v1, s0, 0);
                        } else {
                            // 0x00219e70
                            charge(ctx, 2);
                            if (a1 == 0) {
                                // 0x00219f98
                                charge(ctx, 10);
                                lw(v1, s0, 276);
                                v0 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s1, v0);
                                lw(v0, v0, kGrPairs);
                                v0 = nor(v0, 0);
                                v0 = v0 & 0x2;
                                if (v0 == 0) {
                                    // 0x00219fc0
                                    charge(ctx, 5);
                                    a0 = 0x690000;
                                    a0 = addiu(a0, -7624);  // "gc_res.c"
                                    a1 = 227;
                                    jal(ctx, 0x219FCCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 227): `jr $ra` in retail, execution goes on
                                }
                                // 0x00219fd4
                                charge(ctx, 27);
                                lw(v0, s0, 8);
                                lw(a0, v0, 272);
                                jal(ctx, 0x219FDCu, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                                lw(a0, s0, 276);
                                v1 = sll(a0, 2);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 2);
                                v1 = addu(s1, v1);
                                sw(v0, v1, 88);
                                lw(v1, s0, 276);
                                v0 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v1 = addu(s1, v0);
                                lw(v0, v1, kGrPairs);
                                v0 = v0 | 0x2;
                                sw(v0, v1, kGrPairs);
                                lw(a0, s0, 8);
                                jal(ctx, 0x21A020u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                                lw(a0, s0, 0);
                                v1 = si(-2);
                                v1 = a0 & v1;
                                sw(v1, s0, 0);
                            } else {
                                // 0x00219e78
                                charge(ctx, 3);
                                v1 = 2;
                                if (a1 == v1) {
                                    // 0x00219e8c
                                    charge(ctx, 3);
                                    lw(v1, s0, 276);
                                    if (v1 == a0) {
                                        // 0x00219f14
                                        charge(ctx, 5);
                                        lw(v0, s1, kGrLoaded);
                                        v0 = nor(v0, 0);
                                        v0 = v0 & 0x2;
                                        if (v0 == 0) {
                                            // 0x00219f28
                                            charge(ctx, 5);
                                            a0 = 0x690000;
                                            a0 = addiu(a0, -7624);  // "gc_res.c"
                                            a1 = 214;
                                            jal(ctx, 0x219F34u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 214): `jr $ra` in retail, execution goes on
                                        }
                                        // 0x00219f3c
                                        charge(ctx, 23);
                                        lw(v0, s0, 8);
                                        lw(a0, v0, 272);
                                        jal(ctx, 0x219F44u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                                        sw(v0, s1, kGrResB);
                                        lw(v0, s1, kGrLoaded);
                                        v0 = v0 | 0x2;
                                        sw(v0, s1, kGrLoaded);
                                        v0 = 1;
                                        sw(v0, s1, kGrBackRefs);
                                        lw(v1, s1, kGrState);
                                        v0 = si(-5);
                                        v0 = v1 & v0;
                                        sw(v0, s1, kGrState);
                                        lw(a0, s0, 8);
                                        jal(ctx, 0x219F78u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                                        lw(a0, s0, 0);
                                        v1 = si(-2);
                                        v1 = a0 & v1;
                                        sw(v1, s0, 0);
                                    } else {
                                        // 0x00219e98
                                        charge(ctx, 2);
                                        if (v1 == 0) {
                                            // 0x00219ea8
                                            charge(ctx, 5);
                                            lw(v0, s1, kGrLoaded);
                                            v0 = nor(v0, 0);
                                            v0 = v0 & 0x1;
                                            if (v0 == 0) {
                                                // 0x00219ebc
                                                charge(ctx, 5);
                                                a0 = 0x690000;
                                                a0 = addiu(a0, -7624);  // "gc_res.c"
                                                a1 = 207;
                                                jal(ctx, 0x219EC8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 207): `jr $ra` in retail, execution goes on
                                            }
                                            // 0x00219ed0
                                            charge(ctx, 17);
                                            lw(v0, s0, 8);
                                            lw(a0, v0, 272);
                                            jal(ctx, 0x219ED8u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                                            sw(v0, s1, kGrResA);
                                            lw(v0, s1, kGrLoaded);
                                            v0 = v0 | 0x1;
                                            sw(v0, s1, kGrLoaded);
                                            lw(a0, s0, 8);
                                            jal(ctx, 0x219EF4u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
                                            lw(a0, s0, 0);
                                            v1 = si(-2);
                                            v1 = a0 & v1;
                                            sw(v1, s0, 0);
                                        } else {
                                            // 0x00219ea0
                                            charge(ctx, 2);
                                        }
                                    }
                                } else {
                                    // 0x00219e84
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x0021a0c8
                        charge(ctx, 4);
                        v1 = 2;
                        sw(v1, s0, 4);
                    }
                } else {
                    // 0x00219e20
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00219e30
                        charge(ctx, 7);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7624);  // "gc_res.c"
                        a1 = 193;
                        jal(ctx, 0x219E3Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 193): `jr $ra` in retail, execution goes on
                    } else {
                        // 0x00219e28
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x0021a0ec
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0021a0fc
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0021A120 sub_21A120 -- 132 bytes; frame 0x10: ra sp+0x0
// [gcRes_IsLoading] 1 while any load slot is busy (bit 0), else 0.
void sub_21A120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a120
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    if (v0 == 0) {
        // 0x0021a134
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A140u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 124): `jr $ra` in retail, execution goes on
    }
    // 0x0021a148
    charge(ctx, 4);
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    a0 = 0;
    for (;;) {
        // 0x0021a184
        charge(ctx, 3);
        v0 = slti(a0, 32);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0021a158
            charge(ctx, 10);
            v0 = sll(a0, 3);
            v0 = addu(v0, a0);
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lw(v0, v0, kGrSlots);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0021a180
                charge(ctx, 1);
                a0 = addiu(a0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0021a190 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = slti(a0, 32);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0021A1B0 sub_21A1B0 -- 488 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_Release] frees the rasters by the loaded bits (A, B, table C x7, table D x2), the pair and id
// records' rasters (K_Assert 303 / 312 for a record without its raster) and clears the slot.
void sub_21A1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a1b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    if (v1 == 0) {
        // 0x0021a1d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A1DCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 124): `jr $ra` in retail, execution goes on
    }
    // 0x0021a1e4
    charge(ctx, 5);
    lw(s1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    lw(v1, s1, kGrLoaded);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0021a1f8
        charge(ctx, 3);
        lw(a0, s1, kGrResA);
        jal(ctx, 0x21A1FCu, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
    }
    // 0x0021a204
    charge(ctx, 4);
    lw(v1, s1, kGrLoaded);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0021a214
        charge(ctx, 3);
        lw(a0, s1, kGrResB);
        jal(ctx, 0x21A218u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
    }
    // 0x0021a220
    charge(ctx, 4);
    lw(v1, s1, kGrLoaded);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0021a230
        charge(ctx, 3);
        s0 = 0;
        for (;;) {  // while (s0 < 7)
            // 0x0021a254
            charge(ctx, 3);
            v1 = slti(s0, 7);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0021a23c
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kGrTableC);
            jal(ctx, 0x21A248u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
            s0 = addiu(s0, 1);
        }
    }
    // 0x0021a260
    charge(ctx, 4);
    lw(v1, s1, kGrLoaded);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x0021a270
        charge(ctx, 3);
        s0 = 0;
        for (;;) {  // while (s0 < 2)
            // 0x0021a294
            charge(ctx, 3);
            v1 = slti(s0, 2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0021a27c
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            lw(a0, v0, kGrTableD);
            jal(ctx, 0x21A288u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
            s0 = addiu(s0, 1);
        }
    }
    // 0x0021a2a0
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < 16)
        // 0x0021a304
        charge(ctx, 3);
        v1 = slti(s2, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021a2ac
        charge(ctx, 10);
        v1 = sll(s2, 2);
        v1 = addu(v1, s2);
        v1 = sll(v1, 2);
        v1 = addu(s1, v1);
        s0 = addiu(v1, kGrPairs);
        lw(a0, v1, kGrPairs);
        v1 = nor(a0, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0021a2d4
            charge(ctx, 3);
            v0 = a0 & 0x2;
            if (v0 == 0) {
                // 0x0021a2e0
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7624);  // "gc_res.c"
                a1 = 303;
                jal(ctx, 0x21A2ECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 303): `jr $ra` in retail, execution goes on
            }
            // 0x0021a2f4
            charge(ctx, 3);
            lw(a0, s0, 12);
            jal(ctx, 0x21A2F8u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
        }
        // 0x0021a300
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0021a310
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < 16)
        // 0x0021a36c
        charge(ctx, 3);
        v1 = slti(s2, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021a31c
        charge(ctx, 8);
        v1 = sll(s2, 4);
        v1 = addu(s1, v1);
        s0 = addiu(v1, kGrIds);
        lw(a0, v1, kGrIds);
        v1 = nor(a0, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0021a33c
            charge(ctx, 3);
            v0 = a0 & 0x2;
            if (v0 == 0) {
                // 0x0021a348
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7624);  // "gc_res.c"
                a1 = 312;
                jal(ctx, 0x21A354u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 312): `jr $ra` in retail, execution goes on
            }
            // 0x0021a35c
            charge(ctx, 3);
            lw(a0, s0, 8);
            jal(ctx, 0x21A360u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
        }
        // 0x0021a368
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0021a378
    charge(ctx, 8);
    sw(zero, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0021A840 sub_21A840 -- 216 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_RequestBack] requests card/misc/w_c00.tmx into a free load slot (kind 2, index 1) once; later calls
// only count references (+72).
void sub_21A840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a840
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    if (v1 == 0) {
        // 0x0021a858
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A864u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 124): `jr $ra` in retail, execution goes on
    }
    // 0x0021a86c
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    lw(a0, s0, kGrState);
    v1 = a0 & 0x4;
    if (v1 == 0) {
        // 0x0021a8b4
        charge(ctx, 20);
        v0 = a0 | 0x4;
        sw(v0, s0, kGrState);
        jal(ctx, 0x21A8BCu, gen::fn_sub_21B2D0_0021b2d0);
        s0 = v0;
        v1 = 2;
        sw(v1, v0, 272);
        v1 = 1;
        sw(v1, v0, 276);
        a0 = 0x690000;
        a0 = addiu(a0, -7600);  // "card/misc/w_c00.tmx"
        a1 = 0;
        jal(ctx, 0x21A8E4u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
        sw(v0, s0, 8);
        v1 = 1;
        sw(v1, s0, 4);
        lw(v1, s0, 0);
        v1 = v1 | 0x1;
        sw(v1, s0, 0);
    } else {
        // 0x0021a880
        charge(ctx, 3);
        lw(v1, s0, kGrBackRefs);
        if (v1 == 0) {
            // 0x0021a88c
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7624);  // "gc_res.c"
            a1 = 458;
            jal(ctx, 0x21A898u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 458): `jr $ra` in retail, execution goes on
        }
        // 0x0021a8a0
        charge(ctx, 5);
        lw(v1, s0, kGrBackRefs);
        v1 = addiu(v1, 1);
        sw(v1, s0, kGrBackRefs);
    }
    // 0x0021a904 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021B4A0 sub_21B4A0 -- 432 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_SetCards](file) takes the 10-entry card file (u16 +4 must be 10) of sfl_base.bin: table C (7 rasters),
// raster A, table D (2); loaded bits 0 / 2 / 3.
void sub_21B4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b4a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    if (v0 == 0) {
        // 0x0021b4c8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B4D4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 124): `jr $ra` in retail, execution goes on
    }
    // 0x0021b4dc
    charge(ctx, 6);
    lw(s1, gp, kGpGcRes);  // 0x7CE2FC gc_res.c work (the card textures)
    lw(v0, s1, kGrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x0021b4f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 791;
        jal(ctx, 0x21B500u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 791): `jr $ra` in retail, execution goes on
    }
    // 0x0021b508
    charge(ctx, 5);
    lw(v0, s1, kGrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0021b51c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 792;
        jal(ctx, 0x21B528u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 792): `jr $ra` in retail, execution goes on
    }
    // 0x0021b530
    charge(ctx, 5);
    lw(v0, s1, kGrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021b544
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 793;
        jal(ctx, 0x21B550u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 793): `jr $ra` in retail, execution goes on
    }
    // 0x0021b558
    charge(ctx, 4);
    lhu(v1, s3, 4);
    v0 = 10;
    if (v1 != v0) {
        // 0x0021b568
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 794;
        jal(ctx, 0x21B574u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("gc_res.c", 794): `jr $ra` in retail, execution goes on
    }
    // 0x0021b57c
    charge(ctx, 3);
    s0 = 0;
    for (;;) {  // while (s0 < 7)
        // 0x0021b5b0
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021b588
        charge(ctx, 10);
        v0 = sll(s0, 3);
        v0 = addu(v0, s3);
        lw(v0, v0, 8);
        a0 = addu(s3, v0);
        jal(ctx, 0x21B598u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
        v1 = sll(s0, 2);
        v1 = addu(s1, v1);
        sw(v0, v1, kGrTableC);
        s0 = addiu(s0, 1);
    }
    // 0x0021b5bc
    charge(ctx, 9);
    s0 = addiu(s3, 8);
    lw(v0, s3, 64);
    a0 = addu(s3, v0);
    jal(ctx, 0x21B5C8u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
    sw(v0, s1, kGrResA);
    s2 = 0;
    for (;;) {  // while (s2 < 2)
        // 0x0021b608
        charge(ctx, 3);
        v1 = slti(s2, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021b5e0
        charge(ctx, 10);
        v0 = sll(s2, 3);
        v0 = addu(s0, v0);
        lw(v0, v0, 64);
        a0 = addu(s3, v0);
        jal(ctx, 0x21B5F0u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
        v1 = sll(s2, 2);
        v1 = addu(s1, v1);
        sw(v0, v1, kGrTableD);
        s2 = addiu(s2, 1);
    }
    // 0x0021b614
    charge(ctx, 15);
    lw(v1, s1, kGrLoaded);
    v1 = v1 | 0x1;
    sw(v1, s1, kGrLoaded);
    v1 = v1 | 0x4;
    sw(v1, s1, kGrLoaded);
    v1 = v1 | 0x8;
    sw(v1, s1, kGrLoaded);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0023B990 sub_23B990 -- 2276 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflGround_Draw] sfl_ground.c: draws the Shuffle Time ground (sflRoot_UpdateShuffleRootDraw0Task):
// render states, the ground rasters (sub_20E590 / sub_20E690), the indexed Im2D grid, the card pose (sub_24A180).
void sub_23B990(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023b990
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    if (v0 == 0) {
        // 0x0023b9c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 135;
        jal(ctx, 0x23B9CCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_ground.c", 135): `jr $ra` in retail, execution goes on
    }
    // 0x0023b9d4
    charge(ctx, 27);
    lw(s2, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23B9ECu, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23BA00u, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23BA14u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23BA28u, v0.u());
    lw(v1, s2, kSgMode);
    v0 = 5;
    if (v1 != v0) {
        // 0x0023ba40
        charge(ctx, 3);
        v0 = 4;
        if (v1 == v0) {
            goto L_0023ba78;
        }
        // 0x0023ba4c
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            goto L_0023ba78;
        }
        // 0x0023ba58
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            goto L_0023ba78;
        }
        // 0x0023ba64
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_0023ba78;
        }
        // 0x0023ba70
        charge(ctx, 2);
        goto L_0023bb2c;
    }
L_0023ba78:
    charge(ctx, 45);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x23BA84u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x23BA94u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 0;
    jal(ctx, 0x23BAA0u, gen::fn_sub_20E590_0020e590);  // [sflRes_GetBase](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x23BAB4u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 16);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23BADCu, v0.u());
    a0 = addiu(s2, 16);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23BAFCu, v0.u());
    a0 = 3;
    a1 = addiu(s2, 27392);
    a2 = 99;
    at = 0x83C0;
    a3 = addu(s2, at);
    t0 = 480;
    v0 = 0x960000;
    lw(v0, v0, 164);  // 0x9600A4 (RwIm2DRenderIndexedPrimitive slot)
    jalr(ctx, 0x23BB24u, v0.u());
L_0023bb2c:
    charge(ctx, 4);
    lw(v1, s2, 12);
    v0 = 1;
    if (v1 == v0) {
        // 0x0023bb44
        charge(ctx, 35);
        s0 = 0x960000;
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23BB58u, v0.u());
        a0 = 9;
        a1 = 3;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23BB6Cu, v0.u());
        a0 = 9;
        a1 = 4;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23BB80u, v0.u());
        a0 = 9;
        a1 = 6;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23BB94u, v0.u());
        a0 = 9;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23BBA8u, v0.u());
        a0 = 9;
        a1 = 5;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23BBBCu, v0.u());
        s0 = 0;
        for (;;) {  // while (s0 < 6)
            // 0x0023bbe8
            charge(ctx, 3);
            v0 = slti(s0, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023bbd0
            charge(ctx, 6);
            v0 = sll(s0, 9);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 272);
            jal(ctx, 0x23BBDCu, gen::fn_sub_23C8C0_0023c8c0);
            s0 = addiu(s0, 1);
        }
    } else {
        // 0x0023bb3c
        charge(ctx, 2);
    }
    // 0x0023bbf4
    charge(ctx, 4);
    lw(v1, s2, 12);
    v0 = 5;
    if (v1 != v0) {
        // 0x0023bc04
        charge(ctx, 3);
        v0 = 4;
        if (v1 == v0) {
            goto L_0023bc3c;
        }
        // 0x0023bc10
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            goto L_0023bc3c;
        }
        // 0x0023bc1c
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            goto L_0023bc3c;
        }
        // 0x0023bc28
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_0023bc3c;
        }
        // 0x0023bc34
        charge(ctx, 2);
        goto L_0023bd6c;
    }
L_0023bc3c:
    charge(ctx, 11);
    a0 = 2;
    jal(ctx, 0x23BC40u, gen::fn_sub_20E590_0020e590);  // [sflRes_GetBase](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x23BC54u, v0.u());
    s3 = 0;
    for (;;) {  // while (s3 < 48)
        // 0x0023bd60
        charge(ctx, 3);
        v0 = slti(s3, 48);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023bc68
        charge(ctx, 12);
        v0 = sll(s3, 3);
        v0 = addu(v0, s3);
        v0 = sll(v0, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 4);
        v0 = addu(s2, v0);
        s0 = addiu(v0, 3344);
        lw(v0, v0, 3344);
        v0 = nor(v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0023bc98
            charge(ctx, 4);
            lw(v1, s0, 4);
            v0 = 1;
            if (v1 == v0) {
                // 0x0023bcf0
                charge(ctx, 9);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x23BCFCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x23BD0Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            } else {
                // 0x0023bca8
                charge(ctx, 3);
                v0 = 2;
                if (v1 != v0) {
                    // 0x0023bcb4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        goto L_0023bcc4;
                    }
                    // 0x0023bcbc
                    charge(ctx, 2);
                    goto L_0023bd14;
                }
            L_0023bcc4:
                charge(ctx, 11);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x23BCD0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x23BCE0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            }
        L_0023bd14:
            charge(ctx, 18);
            s4 = 0x960000;
            s4 = addiu(s4, 156);  // &0x96009C
            a0 = addiu(s0, 16);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23BD34u, v0.u());
            a0 = addiu(s0, 16);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23BD54u, v0.u());
        }
        // 0x0023bd5c
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
L_0023bd6c:
    charge(ctx, 4);
    lw(v1, s2, 12);
    v0 = 4;
    if (v1 != v0) {
        // 0x0023bd7c
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            goto L_0023bd90;
        }
        // 0x0023bd88
        charge(ctx, 2);
        goto L_0023be74;
    }
L_0023bd90:
    charge(ctx, 20);
    a0 = 4;
    jal(ctx, 0x23BD94u, gen::fn_sub_20E690_0020e690);  // [sflRes_GetEffect](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x23BDA8u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x23BDBCu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x23BDCCu, gen::fn_RpSkyRenderStateSet_004d7f60);
    s3 = 0;
    for (;;) {  // while (s3 < 7)
        // 0x0023be68
        charge(ctx, 3);
        v0 = slti(s3, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023bde0
        charge(ctx, 8);
        v0 = sll(s3, 5);
        v0 = addu(v0, s3);
        v0 = sll(v0, 5);
        v0 = addu(s2, v0);
        s6 = addiu(v0, 18448);
        s5 = 0;
        for (;;) {  // while (s5 < 4)
            // 0x0023be58
            charge(ctx, 3);
            v0 = slti(s5, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023be00
            charge(ctx, 22);
            v0 = sll(s5, 8);
            v0 = addu(s6, v0);
            s4 = addiu(v0, 16);
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = s4;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23BE2Cu, v0.u());
            a0 = s4;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23BE4Cu, v0.u());
            s5 = addiu(s5, 1);
        }
        // 0x0023be64
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
L_0023be74:
    charge(ctx, 8);
    at = 0x8780;
    a0 = addu(s2, at);
    jal(ctx, 0x23BE7Cu, gen::fn_sub_24A180_0024a180);
    lw(a0, s2, 12);
    v1 = 4;
    if (a0 != v1) {
        // 0x0023be94
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            goto L_0023beb4;
        }
        // 0x0023bea0
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            goto L_0023beb4;
        }
        // 0x0023beac
        charge(ctx, 2);
        goto L_0023bf40;
    }
L_0023beb4:
    charge(ctx, 35);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x23BEC0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x23BED0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    jal(ctx, 0x23BEDCu, gen::fn_sub_20E510_0020e510);  // [sflRes_GetGround](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x23BEF0u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 17936);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23BF18u, v0.u());
    a0 = addiu(s2, 17936);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23BF38u, v0.u());
L_0023bf40:
    charge(ctx, 4);
    lw(a0, s2, 12);
    v1 = 4;
    if (a0 != v1) {
        // 0x0023bf50
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            goto L_0023bf64;
        }
        // 0x0023bf5c
        charge(ctx, 2);
        goto L_0023bff0;
    }
L_0023bf64:
    charge(ctx, 35);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x23BF70u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x23BF80u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 5;
    jal(ctx, 0x23BF8Cu, gen::fn_sub_20E690_0020e690);  // [sflRes_GetEffect](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x23BFA0u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 18192);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23BFC8u, v0.u());
    a0 = addiu(s2, 18192);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23BFE8u, v0.u());
L_0023bff0:
    charge(ctx, 4);
    lw(a0, s2, 12);
    v1 = 4;
    if (a0 != v1) {
        // 0x0023c000
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            goto L_0023c014;
        }
        // 0x0023c00c
        charge(ctx, 2);
        // 0x0023c248 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
L_0023c014:
    charge(ctx, 40);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x1801;
    jal(ctx, 0x23C020u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 72;
    jal(ctx, 0x23C030u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    jal(ctx, 0x23C03Cu, gen::fn_sub_20E690_0020e690);  // [sflRes_GetEffect](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x23C050u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 25840);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23C078u, v0.u());
    a0 = addiu(s2, 25840);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23C098u, v0.u());
    lw(v0, s2, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x0023c0b4
        charge(ctx, 16);
        a0 = addiu(s2, 26096);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);
        jalr(ctx, 0x23C0CCu, v0.u());
        a0 = addiu(s2, 26096);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);
        jalr(ctx, 0x23C0ECu, v0.u());
    }
    // 0x0023c0f4
    charge(ctx, 5);
    lw(v0, s2, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x0023c108
        charge(ctx, 18);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 26352);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x23C128u, v0.u());
        a0 = addiu(s2, 26352);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x23C148u, v0.u());
    }
    // 0x0023c150
    charge(ctx, 23);
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 26608);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23C170u, v0.u());
    a0 = addiu(s2, 26608);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23C190u, v0.u());
    lw(v1, s2, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x0023c1ac
        charge(ctx, 16);
        a0 = addiu(s2, 26864);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);
        jalr(ctx, 0x23C1C4u, v0.u());
        a0 = addiu(s2, 26864);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);
        jalr(ctx, 0x23C1E4u, v0.u());
    }
    // 0x0023c1ec
    charge(ctx, 5);
    lw(v1, s2, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x10;
    if (v1 != 0) {
        // 0x0023c200
        charge(ctx, 18);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 27120);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x23C220u, v0.u());
        a0 = addiu(s2, 27120);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x23C240u, v0.u());
    }
    // 0x0023c248 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0023C350 sub_23C350 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflGround_IsShown] returns flag bit 0.
void sub_23C350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023c350
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    if (v0 == 0) {
        // 0x0023c364
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 135;
        jal(ctx, 0x23C370u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_ground.c", 135): `jr $ra` in retail, execution goes on
    }
    // 0x0023c378 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    lw(v0, v0, kSgFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0023C520 sub_23C520 -- 808 bytes; frame 0xD0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [sflGround_SetCardQuads](quads, pos*, dir*, scale*) the two 4-vertex quads of a card on the ground:
// the template corners (0x68E7C0) centred, rotated by atan2 of the direction, scaled and placed (sub_21D890).
void sub_23C520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0023c520
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s6 = a0;
    s0 = a1;
    s1 = a3;
    a3 = 0x690000;
    a3 = addiu(a3, -6208);  // &0x68E7C0
    a1 = addiu(sp, 0x90);
    a0 = 8;
    for (;;) {
        // 0x0023c570
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0023c594
    charge(ctx, 21);
    lwc1(f2, a2, 4);
    lwc1(f1, a2, 0);
    mula_s(f2, f2);
    madd_s(f0, f1, f1);
    sqrt_s(f0, f0);
    div_s(f12, f1, f0);
    div_s(f0, f2, f0);
    neg_s(f13, f0);
    jal(ctx, 0x23C5C0u, gen::fn_atan2f_0052ea18);
    lwc1(f1, gp, -32496);  // 0x7CAE00 = 1.5708f
    sub_s(f20, f0, f1);
    a2 = 0;
    lwc1(f2, gp, -31928);  // 0x7CB038 = 216.5f
    v1 = 0x41CC0000;
    mtc1(v1, f1);
    for (;;) {  // while (a2 < 2)
        // 0x0023c634
        charge(ctx, 3);
        v1 = slti(a2, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c5e8
        charge(ctx, 6);
        a1 = 0;
        v1 = sll(a2, 5);
        v1 = addu(v1, sp);
        a0 = addiu(v1, 144);
        for (;;) {  // while (a1 < 4)
            // 0x0023c624
            charge(ctx, 3);
            v1 = slti(a1, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023c600
            charge(ctx, 9);
            v1 = sll(a1, 3);
            v1 = addu(a0, v1);
            lwc1(f0, v1, 0);
            sub_s(f0, f0, f2);
            swc1(f0, v1, 0);
            lwc1(f0, v1, 4);
            sub_s(f0, f0, f1);
            swc1(f0, v1, 4);
            a1 = addiu(a1, 1);
        }
        // 0x0023c630
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0023c640
    charge(ctx, 4);
    a2 = 0;
    lwc1(f2, gp, -32084);  // 0x7CAF9C = 1.4f
    for (;;) {  // while (a2 < 2)
        // 0x0023c6ac
        charge(ctx, 3);
        v1 = slti(a2, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c650
        charge(ctx, 6);
        a1 = 0;
        v1 = sll(a2, 5);
        v1 = addu(v1, sp);
        a0 = addiu(v1, 144);
        for (;;) {  // while (a1 < 4)
            // 0x0023c69c
            charge(ctx, 3);
            v1 = slti(a1, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023c668
            charge(ctx, 13);
            v1 = sll(a1, 3);
            v1 = addu(a0, v1);
            lwc1(f0, s1, 0);
            mul_s(f1, f2, f0);
            lwc1(f0, v1, 0);
            mul_s(f0, f0, f1);
            swc1(f0, v1, 0);
            lwc1(f0, s1, 4);
            mul_s(f1, f2, f0);
            lwc1(f0, v1, 4);
            mul_s(f0, f0, f1);
            swc1(f0, v1, 4);
            a1 = addiu(a1, 1);
        }
        // 0x0023c6a8
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0023c6b8
    charge(ctx, 3);
    s5 = 0;
    for (;;) {  // while (s5 < 2)
        // 0x0023c75c
        charge(ctx, 3);
        v1 = slti(s5, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c6c4
        charge(ctx, 6);
        s4 = 0;
        v1 = sll(s5, 5);
        v1 = addu(v1, sp);
        s3 = addiu(v1, 144);
        for (;;) {  // while (s4 < 4)
            // 0x0023c74c
            charge(ctx, 3);
            v1 = slti(s4, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023c6dc
            charge(ctx, 28);
            v0 = sll(s4, 3);
            s2 = addu(s3, v0);
            s1 = addiu(s2, 4);
            mov_s(f12, f20);
            jal(ctx, 0x23C6ECu, gen::fn_sinf_0052e878);
            mov_s(f22, f0);
            lwc1(f21, s1, 0);
            mov_s(f12, f20);
            jal(ctx, 0x23C700u, gen::fn_cosf_0052e6d8);
            lwc1(f1, s2, 0);
            mula_s(f1, f0);
            msub_s(f23, f21, f22);
            mov_s(f12, f20);
            jal(ctx, 0x23C718u, gen::fn_sinf_0052e878);
            mov_s(f22, f0);
            lwc1(f21, s2, 0);
            mov_s(f12, f20);
            jal(ctx, 0x23C72Cu, gen::fn_cosf_0052e6d8);
            lwc1(f1, s1, 0);
            mula_s(f1, f0);
            madd_s(f0, f21, f22);
            swc1(f23, s2, 0);
            swc1(f0, s1, 0);
            s4 = addiu(s4, 1);
        }
        // 0x0023c758
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x0023c768
    charge(ctx, 3);
    a2 = 0;
    for (;;) {  // while (a2 < 2)
        // 0x0023c7c8
        charge(ctx, 3);
        v1 = slti(a2, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c774
        charge(ctx, 6);
        a1 = 0;
        v1 = sll(a2, 5);
        v1 = addu(v1, sp);
        a0 = addiu(v1, 144);
        for (;;) {  // while (a1 < 4)
            // 0x0023c7b8
            charge(ctx, 3);
            v1 = slti(a1, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023c78c
            charge(ctx, 11);
            v1 = sll(a1, 3);
            v1 = addu(a0, v1);
            lwc1(f1, v1, 0);
            lwc1(f0, s0, 0);
            add_s(f0, f1, f0);
            swc1(f0, v1, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, v1, 4);
            add_s(f0, f0, f1);
            swc1(f0, v1, 4);
            a1 = addiu(a1, 1);
        }
        // 0x0023c7c4
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0023c7d4
    charge(ctx, 3);
    s0 = 0;
    for (;;) {  // while (s0 < 2)
        // 0x0023c800
        charge(ctx, 3);
        v1 = slti(s0, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c7e0
        charge(ctx, 8);
        v0 = sll(s0, 8);
        a0 = addu(s6, v0);
        v0 = sll(s0, 5);
        v0 = addu(v0, sp);
        a1 = addiu(v0, 144);
        jal(ctx, 0x23C7F4u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
        s0 = addiu(s0, 1);
    }
    // 0x0023c80c
    charge(ctx, 15);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x0023C850 sub_23C850 -- 104 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflGround_SetCardColour](quads, rgba*) the colour of both quads.
void sub_23C850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023c850
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    for (;;) {  // while (s0 < 2)
        // 0x0023c890
        charge(ctx, 3);
        v1 = slti(s0, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023c878
        charge(ctx, 6);
        v0 = sll(s0, 8);
        a0 = addu(s2, v0);
        a1 = s1;
        jal(ctx, 0x23C884u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = addiu(s0, 1);
    }
    // 0x0023c89c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0023D0E0 sub_23D0E0 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflGround_Flag20] returns flag bit 5.
void sub_23D0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023d0e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    if (v0 == 0) {
        // 0x0023d0f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 135;
        jal(ctx, 0x23D100u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_ground.c", 135): `jr $ra` in retail, execution goes on
    }
    // 0x0023d108 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    lw(v0, v0, kSgFlags);
    v0 = v0 & 0x20;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0023D130 sub_23D130 -- 192 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [sflGround_ShowFar] the far quad shows ground raster 3 (full uv), the pose block resets (sub_2496E0);
// frame 0, mode 2, flag bit 2.
void sub_23D130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0023d130
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    if (v0 == 0) {
        // 0x0023d148
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 135;
        jal(ctx, 0x23D154u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_ground.c", 135): `jr $ra` in retail, execution goes on
    }
    // 0x0023d15c
    charge(ctx, 37);
    lw(s0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    a0 = 3;
    jal(ctx, 0x23D164u, gen::fn_sub_20E510_0020e510);  // [sflRes_GetGround](i) -> raster
    lwc1(f0, v0, 12);
    cvt_s_w(f3, f0);
    lwc1(f0, v0, 16);
    cvt_s_w(f2, f0);
    mtc1(zero, f1);
    div_s(f0, f1, f3);
    swc1(f0, sp, 0x20);
    div_s(f0, f1, f2);
    swc1(f0, sp, 0x24);
    div_s(f0, f3, f3);
    swc1(f0, sp, 0x28);
    div_s(f0, f2, f2);
    swc1(f0, sp, 0x2C);
    a0 = addiu(s0, kSgFarQuad);
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x23D1ACu, gen::fn_sub_21EB80_0021eb80);  // (quad, uv*): the uv rectangle
    at = 0x8780;
    a0 = addu(s0, at);
    jal(ctx, 0x23D1BCu, gen::fn_sub_2496E0_002496e0);
    sw(zero, s0, kSgFrame);
    lw(v1, s0, kSgFlags);
    v1 = v1 | 0x4;
    sw(v1, s0, kSgFlags);
    v1 = 2;
    sw(v1, s0, kSgMode);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0023D1F0 sub_23D1F0 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflGround_Flag4] returns flag bit 2.
void sub_23D1F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023d1f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    if (v0 == 0) {
        // 0x0023d204
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 135;
        jal(ctx, 0x23D210u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_ground.c", 135): `jr $ra` in retail, execution goes on
    }
    // 0x0023d218 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflGround);  // 0x7CE314 sfl_ground.c work (the Shuffle Time ground)
    lw(v0, v0, kSgFlags);
    v0 = v0 & 0x4;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0023D7B0 sub_23D7B0 -- 60 bytes; frame 0x10: ra sp+0x0
// [sflPanel_Unregister] sfl_panel.c: clears the slot.
void sub_23D7B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023d7b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v1 == 0) {
        // 0x0023d7c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23D7D0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023d7d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0023D870 sub_23D870 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPanel_Close] clears bit 0 (K_Assert 163 if it is not open).
void sub_23D870(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023d870
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v1 == 0) {
        // 0x0023d888
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23D894u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023d89c
    charge(ctx, 5);
    lw(s0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(v1, s0, kSpnFlags);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0023d8b0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 163;
        jal(ctx, 0x23D8BCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 163): `jr $ra` in retail, execution goes on
    }
    // 0x0023d8c4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, kSpnFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, kSpnFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0023D8F0 sub_23D8F0 -- 464 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPanel_Update] advances the panel animation (mode 0: 50 frames, 1 / 2: 30; at the end bit 1 clears),
// lays the panel out (sub_23DAC0) and moves it in (100 * (frame + 1) / 50 from 200 for mode 0).
void sub_23D8F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0023d8f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v0 == 0) {
        // 0x0023d908
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23D914u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023d91c
    charge(ctx, 5);
    lw(s0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(v0, s0, kSpnFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0023d930
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 178;
        jal(ctx, 0x23D93Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 178): `jr $ra` in retail, execution goes on
    }
    // 0x0023d944
    charge(ctx, 4);
    lw(v1, s0, kSpnMode);
    v0 = 2;
    if (v1 == v0) {
        // 0x0023d9e0
        charge(ctx, 4);
        lw(v0, s0, kSpnFrame);
        at = slti(v0, 30);
        if (at == 0) {
            // 0x0023da00
            charge(ctx, 4);
            lw(v1, s0, kSpnFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s0, kSpnFlags);
        } else {
            // 0x0023d9f0
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sw(v0, s0, kSpnFrame);
        }
    } else {
        // 0x0023d954
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0023d9a8
            charge(ctx, 4);
            lw(v0, s0, kSpnFrame);
            at = slti(v0, 30);
            if (at == 0) {
                // 0x0023d9c8
                charge(ctx, 6);
                lw(v1, s0, kSpnFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, kSpnFlags);
            } else {
                // 0x0023d9b8
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sw(v0, s0, kSpnFrame);
            }
        } else {
            // 0x0023d960
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0023d970
                charge(ctx, 4);
                lw(v0, s0, kSpnFrame);
                at = slti(v0, 50);
                if (at == 0) {
                    // 0x0023d990
                    charge(ctx, 6);
                    lw(v1, s0, kSpnFlags);
                    v0 = si(-3);
                    v0 = v1 & v0;
                    sw(v0, s0, kSpnFlags);
                } else {
                    // 0x0023d980
                    charge(ctx, 4);
                    v0 = addiu(v0, 1);
                    sw(v0, s0, kSpnFrame);
                }
            } else {
                // 0x0023d968
                charge(ctx, 2);
            }
        }
    }
    // 0x0023da10
    charge(ctx, 5);
    jal(ctx, 0x23DA10u, gen::fn_sub_23DAC0_0023dac0);
    lw(v1, s0, kSpnMode);
    if (v1 == 0) {
        // 0x0023da2c
        charge(ctx, 4);
        lw(v1, s0, kSpnFrame);
        at = slti(v1, 50);
        if (at != 0) {
            // 0x0023da3c
            charge(ctx, 28);
            v0 = addiu(v1, 1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42480000;
            mtc1(v0, f0);
            div_s(f3, f1, f0);
            v0 = 0x42C80000;
            mtc1(v0, f2);
            mul_s(f1, f2, f3);
            v0 = 0x43480000;
            mtc1(v0, f0);
            mula_s(f3, f0);
            msub_s(f0, f3, f1);
            sub_s(f0, f0, f2);
            sw(zero, sp, 0x20);
            sw(zero, sp, 0x24);
            swc1(f0, sp, 0x28);
            jal(ctx, 0x23DA90u, gen::fn_sub_198590_00198590);  // the current camera / render context
            lw(a0, v0, 4);
            a1 = addiu(sp, 0x20);
            a2 = 0;
            jal(ctx, 0x23DAA4u, gen::fn_sub_4CB750_004cb750);
        }
    } else {
        // 0x0023da24
        charge(ctx, 2);
    }
    // 0x0023daac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0023DAC0 sub_23DAC0 -- 3752 bytes; frame 0xA0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [sflPanel_Layout] lays out the Shuffle Time panel: the count, the title, the frames, the wobble (sin / cos)
// and the colour tables 0x68E800.., per mode and frame.
void sub_23DAC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x0023dac0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v1 == 0) {
        // 0x0023daf4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23DB00u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023db08
    charge(ctx, 5);
    lw(s0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(a0, s0, kSpnMode);
    v1 = 2;
    if (a0 != v1) {
        // 0x0023db1c
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            goto L_0023df20;
        }
        // 0x0023db28
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x0023db38
            charge(ctx, 4);
            lw(v1, s0, kSpnFrame);
            at = slti(v1, 4);
            if (at == 0) {
                // 0x0023db60
                charge(ctx, 3);
                at = slti(v1, 8);
                if (at == 0) {
                    // 0x0023dbb8
                    charge(ctx, 1);
                    mtc1(zero, f2);
                } else {
                    // 0x0023db6c
                    charge(ctx, 19);
                    v0 = addiu(v1, -4);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40800000;
                    mtc1(v0, f0);
                    div_s(f2, f1, f0);
                    v0 = 526;
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f0, f0, f2);
                    mul_s(f2, f1, f0);
                }
            } else {
                // 0x0023db48
                charge(ctx, 6);
                v0 = 526;
                mtc1(v0, f0);
                cvt_s_w(f2, f0);
            }
            // 0x0023dbbc
            charge(ctx, 3);
            at = slti(v1, 26);
            if (at == 0) {
                // 0x0023dbe0
                charge(ctx, 12);
                v0 = addiu(v1, -26);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41C00000;
                mtc1(v0, f0);
                div_s(f0, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f20);
                sub_s(f23, f20, f0);
            } else {
                // 0x0023dbc8
                charge(ctx, 6);
                v0 = 0x3F800000;
                mtc1(v0, f20);
                mov_s(f23, f20);
            }
            // 0x0023dc10
            charge(ctx, 13);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x64);
            v0 = 0x432E0000;
            sw(v0, sp, 0x68);
            sw(zero, sp, 0x6C);
            sw(v0, sp, 0x70);
            v0 = 0x42000000;
            sw(v0, sp, 0x74);
            sw(zero, sp, 0x78);
            sw(v0, sp, 0x7C);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x0023dc48
                charge(ctx, 6);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023dc44
                charge(ctx, 1);
                v1 = addiu(v1, 1);
            }
            // 0x0023dc60
            charge(ctx, 9);
            v1 = 0;
            v0 = 0x42E40000;
            mtc1(v0, f0);
            add_s(f2, f0, f2);
            v0 = 0x426C0000;
            mtc1(v0, f1);
            for (;;) {  // while (v1 < 4)
                // 0x0023dcac
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023dc84
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 96);
                lwc1(f0, v0, 0);
                add_s(f0, f0, f2);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                add_s(f0, f0, f1);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x0023dcb8
            charge(ctx, 18);
            a0 = addiu(s0, kSpnTitleQuad);
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x23DCC0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0x9C);
            sb(v0, sp, 0x9D);
            sb(v0, sp, 0x9E);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f23);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0023dd18
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0023dd00
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0023dd30
            charge(ctx, 9);
            sb(v1, sp, 0x9F);
            a0 = addiu(s0, kSpnTitleQuad);
            a1 = addiu(sp, 0x9C);
            jal(ctx, 0x23DD3Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            lw(v1, s0, kSpnFrame);
            at = slti(v1, 4);
            if (at == 0) {
                // 0x0023dd90
                charge(ctx, 1);
                mtc1(zero, f2);
            } else {
                // 0x0023dd54
                charge(ctx, 15);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                div_s(f2, f1, f0);
                v0 = 614;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                sub_s(f0, f20, f2);
                mul_s(f2, f1, f0);
            }
            // 0x0023dd94
            charge(ctx, 3);
            at = slti(v1, 26);
            if (at == 0) {
                // 0x0023dda8
                charge(ctx, 9);
                v0 = addiu(v1, -26);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41C00000;
                mtc1(v0, f0);
                div_s(f0, f1, f0);
                sub_s(f20, f20, f0);
            } else {
                // 0x0023dda0
                charge(ctx, 2);
            }
            // 0x0023ddcc
            charge(ctx, 13);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x64);
            v0 = 0x42800000;
            sw(v0, sp, 0x68);
            sw(zero, sp, 0x6C);
            sw(v0, sp, 0x70);
            sw(v0, sp, 0x74);
            sw(zero, sp, 0x78);
            sw(v0, sp, 0x7C);
            v1 = 0;
            lwc1(f1, gp, -32484);  // 0x7CAE0C = 1.6f
            for (;;) {  // while (v1 < 4)
                // 0x0023de28
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023de00
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 96);
                lwc1(f0, v0, 0);
                mul_s(f0, f0, f1);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                mul_s(f0, f0, f1);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x0023de34
            charge(ctx, 9);
            v1 = 0;
            v0 = 0x41D00000;
            mtc1(v0, f0);
            add_s(f2, f0, f2);
            v0 = 0x42820000;
            mtc1(v0, f1);
            for (;;) {  // while (v1 < 4)
                // 0x0023de80
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023de58
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 96);
                lwc1(f0, v0, 0);
                add_s(f0, f0, f2);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                add_s(f0, f0, f1);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x0023de8c
            charge(ctx, 18);
            a0 = addiu(s0, kSpnNumberQuad);
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x23DE94u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
            v0 = 255;
            sb(v0, sp, 0x9C);
            sb(v0, sp, 0x9D);
            sb(v0, sp, 0x9E);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f20);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0023deec
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0023ded4
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0023df04
            charge(ctx, 7);
            sb(v1, sp, 0x9F);
            a0 = addiu(s0, kSpnNumberQuad);
            a1 = addiu(sp, 0x9C);
            jal(ctx, 0x23DF10u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        } else {
            // 0x0023db30
            charge(ctx, 2);
        }
        // 0x0023e938 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xA0);
        return;
    }
L_0023df20:
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < 2)
        // 0x0023e348
        charge(ctx, 3);
        v0 = slti(s2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023df2c
        charge(ctx, 3);
        v0 = 1;
        if (s2 == v0) {
            // 0x0023e0c4
            charge(ctx, 6);
            v0 = 0x3F800000;
            mtc1(v0, f20);
            lw(a0, s0, 8);
            v0 = 30;
            if (a0 != v0) {
                // 0x0023e0f0
                charge(ctx, 6);
                s1 = si(-1);
                a1 = 0;
                v1 = 0x690000;
                v1 = addiu(v1, -6096);  // &0x68E830
                for (;;) {  // while (a1 < 3)
                    // 0x0023e130
                    charge(ctx, 3);
                    v0 = slti(a1, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0023e108
                    charge(ctx, 6);
                    v0 = sll(a1, 2);
                    v0 = addu(v1, v0);
                    lw(v0, v0, 0);
                    at = slt(a0, v0);
                    if (at != 0) {
                        goto L_0023e120_63;
                    }
                    // 0x0023e12c
                    charge(ctx, 1);
                    a1 = addiu(a1, 1);
                }
            L_0023e13c:
                charge(ctx, 2);
                if (i64(s1) < 0) {
                    // 0x0023e144
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -6048);  // "sfl_panel.c"
                    a1 = 472;
                    jal(ctx, 0x23E150u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 472): `jr $ra` in retail, execution goes on
                }
            } else {
                // 0x0023e0dc
                charge(ctx, 5);
                v0 = 0x690000;
                lwc1(f20, v0, -6056);  // 0x68E858
                s1 = 2;
            }
            // 0x0023e158
            charge(ctx, 2);
            if (i64(s1) < 0) {
                // 0x0023e160
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -6048);  // "sfl_panel.c"
                a1 = 475;
                jal(ctx, 0x23E16Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 475): `jr $ra` in retail, execution goes on
            }
            // 0x0023e174
            charge(ctx, 3);
            v0 = slti(s1, 3);
            if (v0 == 0) {
                // 0x0023e180
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -6048);  // "sfl_panel.c"
                a1 = 476;
                jal(ctx, 0x23E18Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 476): `jr $ra` in retail, execution goes on
            }
            // 0x0023e194
            charge(ctx, 53);
            a1 = sll(s1, 2);
            v0 = 0x690000;
            v0 = addiu(v0, -6096);  // &0x68E830
            a0 = addu(v0, a1);
            lw(v1, a0, 0);
            lw(v0, s0, 8);
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lw(v0, a0, 4);
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f3, f1, f0);
            v0 = 0x690000;
            v0 = addiu(v0, -6080);  // &0x68E840
            v0 = addu(v0, a1);
            lwc1(f1, v0, 0);
            lwc1(f0, v0, 4);
            sub_s(f0, f0, f1);
            mtc1(zero, f2);
            adda_s(f2, f1);
            madd_s(f23, f3, f0);
            v0 = 0x690000;
            v0 = addiu(v0, -6064);  // &0x68E850
            v0 = addu(v0, a1);
            lwc1(f1, v0, 0);
            lwc1(f0, v0, 4);
            sub_s(f0, f0, f1);
            adda_s(f2, f1);
            madd_s(f1, f3, f0);
            v0 = 0x43B40000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x40000000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            lwc1(f0, gp, -32184);  // 0x7CAF38 = 3.14159f
            mul_s(f24, f0, f1);
            mov_s(f12, f24);
            jal(ctx, 0x23E248u, gen::fn_sinf_0052e878);
            swc1(f0, sp, 0x88);
            mov_s(f12, f24);
            jal(ctx, 0x23E258u, gen::fn_cosf_0052e6d8);
            neg_s(f0, f0);
            swc1(f0, sp, 0x8C);
        } else {
            // 0x0023df38
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x0023df48
                charge(ctx, 7);
                sw(zero, sp, 0x88);
                v0 = lui(0xBF80);
                sw(v0, sp, 0x8C);
                lw(a0, s0, 8);
                v0 = 30;
                if (a0 != v0) {
                    // 0x0023df70
                    charge(ctx, 6);
                    s1 = si(-1);
                    a1 = 0;
                    v1 = 0x690000;
                    v1 = addiu(v1, -6144);  // &0x68E800
                    for (;;) {  // while (a1 < 4)
                        // 0x0023dfb0
                        charge(ctx, 3);
                        v0 = slti(a1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0023df88
                        charge(ctx, 6);
                        v0 = sll(a1, 2);
                        v0 = addu(v1, v0);
                        lw(v0, v0, 0);
                        at = slt(a0, v0);
                        if (at != 0) {
                            goto L_0023dfa0_47;
                        }
                        // 0x0023dfac
                        charge(ctx, 1);
                        a1 = addiu(a1, 1);
                    }
                L_0023dfbc:
                    charge(ctx, 2);
                    if (i64(s1) < 0) {
                        // 0x0023dfc4
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -6048);  // "sfl_panel.c"
                        a1 = 439;
                        jal(ctx, 0x23DFD0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 439): `jr $ra` in retail, execution goes on
                    }
                    // 0x0023dfd8
                    charge(ctx, 3);
                    v0 = slti(s1, 4);
                    if (v0 == 0) {
                        // 0x0023dfe4
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -6048);  // "sfl_panel.c"
                        a1 = 440;
                        jal(ctx, 0x23DFF0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 440): `jr $ra` in retail, execution goes on
                    }
                } else {
                    // 0x0023df64
                    charge(ctx, 3);
                    s1 = 3;
                }
                // 0x0023dff8
                charge(ctx, 2);
                if (i64(s1) < 0) {
                    // 0x0023e000
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -6048);  // "sfl_panel.c"
                    a1 = 443;
                    jal(ctx, 0x23E00Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 443): `jr $ra` in retail, execution goes on
                }
                // 0x0023e014
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    // 0x0023e020
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -6048);  // "sfl_panel.c"
                    a1 = 444;
                    jal(ctx, 0x23E02Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 444): `jr $ra` in retail, execution goes on
                }
                // 0x0023e034
                charge(ctx, 36);
                a1 = sll(s1, 2);
                v0 = 0x690000;
                v0 = addiu(v0, -6144);  // &0x68E800
                a0 = addu(v0, a1);
                lw(v1, a0, 0);
                lw(v0, s0, 8);
                v0 = subu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lw(v0, a0, 4);
                v0 = subu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f3, f1, f0);
                v0 = 0x690000;
                v0 = addiu(v0, -6112);  // &0x68E820
                v0 = addu(v0, a1);
                lwc1(f1, v0, 0);
                lwc1(f0, v0, 4);
                sub_s(f0, f0, f1);
                mtc1(zero, f2);
                adda_s(f2, f1);
                madd_s(f23, f3, f0);
                v0 = 0x690000;
                v0 = addiu(v0, -6128);  // &0x68E810
                v0 = addu(v0, a1);
                lwc1(f1, v0, 0);
                lwc1(f0, v0, 4);
                sub_s(f0, f0, f1);
                adda_s(f2, f1);
                madd_s(f20, f3, f0);
            } else {
                // 0x0023df40
                charge(ctx, 2);
            }
        }
        // 0x0023e268
        charge(ctx, 38);
        v0 = 0x43A00000;
        sw(v0, sp, 0x90);
        v0 = 0x43600000;
        sw(v0, sp, 0x94);
        v0 = 690;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f0, f20);
        swc1(f0, sp, 0x80);
        v0 = 0x43F40000;
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        swc1(f0, sp, 0x84);
        v0 = sll(s2, 8);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 528);
        a0 = s1;
        a1 = addiu(sp, 0x90);
        a2 = addiu(sp, 0x88);
        a3 = addiu(sp, 0x80);
        jal(ctx, 0x23E2C0u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
        v0 = 255;
        sb(v0, sp, 0x9C);
        sb(v0, sp, 0x9D);
        sb(v0, sp, 0x9E);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f1, f0, f23);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0023e318
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0023e300
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0023e330
        charge(ctx, 6);
        sb(v1, sp, 0x9F);
        a0 = s1;
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x23E33Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s2 = addiu(s2, 1);
    }
    // 0x0023e354
    charge(ctx, 4);
    lw(v1, s0, 4);
    v0 = 2;
    if (v1 == v0) {
        // 0x0023e398
        charge(ctx, 4);
        v0 = 0x43FF0000;
        mtc1(v0, f22);
        v0 = 0x42B20000;
        mtc1(v0, f21);
    } else {
        // 0x0023e364
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0023e378
            charge(ctx, 8);
            v0 = 463;
            mtc1(v0, f0);
            cvt_s_w(f22, f0);
            v0 = 0x42B20000;
            mtc1(v0, f21);
        } else {
            // 0x0023e370
            charge(ctx, 2);
        }
    }
    // 0x0023e3a8
    charge(ctx, 17);
    lwc1(f12, gp, -31932);  // 0x7CB034 = -0.174533f
    jal(ctx, 0x23E3ACu, gen::fn_sinf_0052e878);
    swc1(f0, sp, 0x88);
    lwc1(f12, gp, -31932);  // 0x7CB034 = -0.174533f
    jal(ctx, 0x23E3BCu, gen::fn_cosf_0052e6d8);
    neg_s(f0, f0);
    swc1(f0, sp, 0x8C);
    v0 = 0x43A00000;
    sw(v0, sp, 0x90);
    v0 = 0x43360000;
    sw(v0, sp, 0x94);
    lw(v1, s0, 8);
    at = slti(v1, 7);
    if (at == 0) {
        // 0x0023e434
        charge(ctx, 2);
        v0 = 0x3F800000;
        mtc1(v0, f20);
    } else {
        // 0x0023e3ec
        charge(ctx, 18);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40E00000;
        mtc1(v0, f0);
        div_s(f0, f1, f0);
        lwc1(f3, gp, -32632);  // 0x7CAD78 = 0.4f
        v0 = 0x3F800000;
        mtc1(v0, f2);
        sub_s(f1, f2, f0);
        mtc1(zero, f0);
        adda_s(f0, f2);
        madd_s(f20, f3, f1);
    }
    // 0x0023e43c
    charge(ctx, 3);
    at = slti(v1, 7);
    if (at == 0) {
        // 0x0023e478
        charge(ctx, 3);
        at = slti(v1, 15);
        if (at == 0) {
            // 0x0023e4bc
            charge(ctx, 1);
            mtc1(zero, f23);
        } else {
            // 0x0023e484
            charge(ctx, 14);
            v0 = addiu(v1, -7);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41000000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f23, f0, f1);
        }
    } else {
        // 0x0023e448
        charge(ctx, 12);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40E00000;
        mtc1(v0, f0);
        div_s(f23, f1, f0);
    }
    // 0x0023e4c0
    charge(ctx, 24);
    mul_s(f0, f22, f20);
    swc1(f0, sp, 0x80);
    mul_s(f0, f21, f20);
    swc1(f0, sp, 0x84);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x90);
    a2 = addiu(sp, 0x88);
    a3 = addiu(sp, 0x80);
    jal(ctx, 0x23E4E0u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f23);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0023e538
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0023e520
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0023e550
    charge(ctx, 22);
    sb(v1, sp, 0x9F);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x23E55Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lwc1(f12, gp, -31932);  // 0x7CB034 = -0.174533f
    jal(ctx, 0x23E568u, gen::fn_sinf_0052e878);
    swc1(f0, sp, 0x88);
    lwc1(f12, gp, -31932);  // 0x7CB034 = -0.174533f
    jal(ctx, 0x23E578u, gen::fn_cosf_0052e6d8);
    neg_s(f0, f0);
    swc1(f0, sp, 0x8C);
    v0 = 0x43A00000;
    sw(v0, sp, 0x90);
    v0 = 0x43360000;
    sw(v0, sp, 0x94);
    lw(v0, s0, 8);
    at = slti(v0, 7);
    if (at == 0) {
        // 0x0023e5b4
        charge(ctx, 3);
        at = slti(v0, 15);
        if (at == 0) {
            // 0x0023e5f4
            charge(ctx, 3);
            at = slti(v0, 22);
            if (at == 0) {
                // 0x0023e610
                charge(ctx, 12);
                v0 = addiu(v0, -22);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41000000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f20, f0, f1);
            } else {
                // 0x0023e600
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f20);
            }
        } else {
            // 0x0023e5c0
            charge(ctx, 13);
            v0 = addiu(v0, -7);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41000000;
            mtc1(v0, f0);
            div_s(f20, f1, f0);
        }
    } else {
        // 0x0023e5a8
        charge(ctx, 3);
        mtc1(zero, f20);
    }
    // 0x0023e640
    charge(ctx, 27);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    mul_s(f0, f22, f1);
    swc1(f0, sp, 0x80);
    mul_s(f0, f21, f1);
    swc1(f0, sp, 0x84);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x90);
    a2 = addiu(sp, 0x88);
    a3 = addiu(sp, 0x80);
    jal(ctx, 0x23E66Cu, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0023e6c4
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0023e6ac
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0023e6dc
    charge(ctx, 22);
    sb(v1, sp, 0x9F);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x23E6E8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lwc1(f12, gp, -31932);  // 0x7CB034 = -0.174533f
    jal(ctx, 0x23E6F4u, gen::fn_sinf_0052e878);
    swc1(f0, sp, 0x88);
    lwc1(f12, gp, -31932);  // 0x7CB034 = -0.174533f
    jal(ctx, 0x23E704u, gen::fn_cosf_0052e6d8);
    neg_s(f0, f0);
    swc1(f0, sp, 0x8C);
    v0 = 0x43A00000;
    sw(v0, sp, 0x90);
    v0 = 0x43360000;
    sw(v0, sp, 0x94);
    lw(v1, s0, 8);
    at = slti(v1, 7);
    if (at == 0) {
        // 0x0023e744
        charge(ctx, 3);
        at = slti(v1, 15);
        if (at == 0) {
            // 0x0023e79c
            charge(ctx, 3);
            at = slti(v1, 26);
            if (at == 0) {
                // 0x0023e7ec
                charge(ctx, 2);
                v0 = 0x3F800000;
                mtc1(v0, f2);
            } else {
                // 0x0023e7a8
                charge(ctx, 17);
                v0 = addiu(v1, -15);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41300000;
                mtc1(v0, f0);
                div_s(f3, f1, f0);
                lwc1(f2, gp, -32632);  // 0x7CAD78 = 0.4f
                v0 = 0x3F800000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f2, f2, f3);
            }
        } else {
            // 0x0023e750
            charge(ctx, 19);
            v0 = addiu(v1, -7);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41000000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            lwc1(f3, gp, -32632);  // 0x7CAD78 = 0.4f
            v0 = 0x3F800000;
            mtc1(v0, f2);
            sub_s(f1, f2, f0);
            mtc1(zero, f0);
            adda_s(f0, f2);
            madd_s(f2, f3, f1);
        }
    } else {
        // 0x0023e734
        charge(ctx, 4);
        v0 = 0x3F800000;
        mtc1(v0, f2);
    }
    // 0x0023e7f4
    charge(ctx, 3);
    at = slti(v1, 7);
    if (at == 0) {
        // 0x0023e80c
        charge(ctx, 3);
        at = slti(v1, 15);
        if (at == 0) {
            // 0x0023e84c
            charge(ctx, 3);
            at = slti(v1, 26);
            if (at == 0) {
                // 0x0023e890
                charge(ctx, 1);
                mtc1(zero, f20);
            } else {
                // 0x0023e858
                charge(ctx, 14);
                v0 = addiu(v1, -15);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41300000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f20, f0, f1);
            }
        } else {
            // 0x0023e818
            charge(ctx, 13);
            v0 = addiu(v1, -7);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41000000;
            mtc1(v0, f0);
            div_s(f20, f1, f0);
        }
    } else {
        // 0x0023e800
        charge(ctx, 3);
        mtc1(zero, f20);
    }
    // 0x0023e894
    charge(ctx, 24);
    mul_s(f0, f22, f2);
    swc1(f0, sp, 0x80);
    mul_s(f0, f21, f2);
    swc1(f0, sp, 0x84);
    a0 = addiu(s0, 1552);
    a1 = addiu(sp, 0x90);
    a2 = addiu(sp, 0x88);
    a3 = addiu(sp, 0x80);
    jal(ctx, 0x23E8B4u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0023e90c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0023e8f4
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0023e924
    charge(ctx, 5);
    sb(v1, sp, 0x9F);
    a0 = addiu(s0, 1552);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x23E930u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    // 0x0023e938 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_0023dfa0_47:
    charge(ctx, 3);
    s1 = addiu(a1, -1);
    goto L_0023dfbc;
L_0023e120_63:
    charge(ctx, 3);
    s1 = addiu(a1, -1);
    goto L_0023e13c;
}

// 0x0023E970 sub_23E970 -- 1236 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflPanel_Draw] draws the Shuffle Time panel (sflRoot_UpdateShuffleRootDraw1Task).
void sub_23E970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023e970
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v0 == 0) {
        // 0x0023e99c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23E9A8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023e9b0
    charge(ctx, 5);
    lw(s0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(v0, s0, kSpnFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0023e9c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 667;
        jal(ctx, 0x23E9D0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 667): `jr $ra` in retail, execution goes on
    }
    // 0x0023e9d8
    charge(ctx, 35);
    s3 = 0x960000;
    s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23E9ECu, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23EA00u, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23EA14u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23EA28u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x23EA3Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x23EA4Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    lw(a0, s0, kSpnMode);
    v1 = 2;
    if (a0 != v1) {
        // 0x0023ea64
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            goto L_0023eb7c;
        }
        // 0x0023ea70
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x0023ea80
            charge(ctx, 63);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x23EA8Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x23EA9Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            s2 = s3;
            a0 = 0;
            jal(ctx, 0x23EAACu, gen::fn_sub_20E510_0020e510);  // [sflRes_GetGround](i) -> raster
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);
            jalr(ctx, 0x23EAC0u, v0.u());
            s1 = 0x960000;
            s1 = addiu(s1, 156);  // &0x96009C
            a0 = addiu(s0, kSpnTitleQuad);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23EAE8u, v0.u());
            a0 = addiu(s0, kSpnTitleQuad);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23EB08u, v0.u());
            lw(v0, s0, kSpnCount);
            a0 = addiu(v0, -1);
            jal(ctx, 0x23EB18u, gen::fn_sub_20E610_0020e610);
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);
            jalr(ctx, 0x23EB2Cu, v0.u());
            a0 = addiu(s0, kSpnNumberQuad);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23EB4Cu, v0.u());
            a0 = addiu(s0, kSpnNumberQuad);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23EB6Cu, v0.u());
        } else {
            // 0x0023ea78
            charge(ctx, 2);
        }
        // 0x0023ee1c (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_0023eb7c:
    charge(ctx, 27);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x1801;
    jal(ctx, 0x23EB88u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 72;
    jal(ctx, 0x23EB98u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s2 = 0x960000;
    s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23EBB4u, v0.u());
    a0 = 0;
    jal(ctx, 0x23EBC0u, gen::fn_sub_20E690_0020e690);  // [sflRes_GetEffect](i) -> raster
    a0 = 1;
    a1 = v0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23EBD4u, v0.u());
    s5 = 0;
    for (;;) {  // while (s5 < 2)
        // 0x0023ec40
        charge(ctx, 3);
        v0 = slti(s5, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023ebe8
        charge(ctx, 22);
        v0 = sll(s5, 8);
        v0 = addu(s0, v0);
        s4 = addiu(v0, 528);
        s2 = 0x960000;
        s2 = addiu(s2, 156);  // &0x96009C
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x23EC14u, v0.u());
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x23EC34u, v0.u());
        s5 = addiu(s5, 1);
    }
    // 0x0023ec4c
    charge(ctx, 9);
    a0 = 6;
    a1 = 0;
    lw(v0, s3, 0);
    jalr(ctx, 0x23EC58u, v0.u());
    lw(v0, s0, 4);
    a0 = 2;
    if (v0 == a0) {
        // 0x0023ec98
        charge(ctx, 3);
        jal(ctx, 0x23EC98u, gen::fn_sub_20E690_0020e690);  // [sflRes_GetEffect](i) -> raster
        s1 = v0;
    } else {
        // 0x0023ec70
        charge(ctx, 3);
        a0 = 1;
        if (v0 == a0) {
            // 0x0023ec84
            charge(ctx, 5);
            jal(ctx, 0x23EC84u, gen::fn_sub_20E690_0020e690);  // [sflRes_GetEffect](i) -> raster
            s1 = v0;
        } else {
            // 0x0023ec7c
            charge(ctx, 2);
        }
    }
    // 0x0023eca4
    charge(ctx, 94);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x1801;
    jal(ctx, 0x23ECB0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 72;
    jal(ctx, 0x23ECC0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s3 = 0x960000;
    s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
    a0 = 1;
    a1 = s1;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23ECDCu, v0.u());
    s2 = 0x960000;
    s2 = addiu(s2, 156);  // &0x96009C
    a0 = addiu(s0, 1552);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23ED04u, v0.u());
    a0 = addiu(s0, 1552);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23ED24u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x23ED38u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x23ED48u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    a1 = s1;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23ED5Cu, v0.u());
    a0 = addiu(s0, 1296);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23ED7Cu, v0.u());
    a0 = addiu(s0, 1296);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23ED9Cu, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x1801;
    jal(ctx, 0x23EDB0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 72;
    jal(ctx, 0x23EDC0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    a1 = s1;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x23EDD4u, v0.u());
    a0 = addiu(s0, 1040);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23EDF4u, v0.u());
    a0 = addiu(s0, 1040);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x23EE14u, v0.u());
    // 0x0023ee1c (the shared epilogue, written out on this path)
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

// 0x0023EE50 sub_23EE50 -- 448 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflPanel_Start] starts the panel with the count of sub_255130 (1..6, K_Assert 765 / 766): the count's
// raster (base B, count - 1) and the title (ground raster 0, 174 x 32), mode 0, bit 1; plays sound 6 (sub_10A4E0).
void sub_23EE50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0023ee50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v0 == 0) {
        // 0x0023ee6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23EE78u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023ee80
    charge(ctx, 16);
    lw(s1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    jal(ctx, 0x23EE84u, gen::fn_sub_255130_00255130);
    s0 = v0;
    sw(zero, sp, 0x40);
    sw(zero, sp, 0x44);
    sw(zero, sp, 0x48);
    jal(ctx, 0x23EE9Cu, gen::fn_sub_198590_00198590);  // the current camera / render context
    lw(a0, v0, 4);
    a1 = addiu(sp, 0x40);
    a2 = 0;
    jal(ctx, 0x23EEB0u, gen::fn_sub_4CB750_004cb750);
    if (s0 == 0) {
        // 0x0023eec0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 765;
        jal(ctx, 0x23EECCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 765): `jr $ra` in retail, execution goes on
    }
    // 0x0023eed4
    charge(ctx, 3);
    at = slti(s0, 7);
    if (at == 0) {
        // 0x0023eee0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 766;
        jal(ctx, 0x23EEECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 766): `jr $ra` in retail, execution goes on
    }
    // 0x0023eef4
    charge(ctx, 71);
    a0 = addiu(s0, -1);
    jal(ctx, 0x23EEF8u, gen::fn_sub_20E610_0020e610);
    lwc1(f0, v0, 12);
    cvt_s_w(f3, f0);
    lwc1(f0, v0, 16);
    cvt_s_w(f2, f0);
    mtc1(zero, f1);
    div_s(f0, f1, f3);
    swc1(f0, sp, 0x30);
    div_s(f0, f1, f2);
    swc1(f0, sp, 0x34);
    div_s(f0, f3, f3);
    swc1(f0, sp, 0x38);
    div_s(f0, f2, f2);
    swc1(f0, sp, 0x3C);
    a0 = addiu(s1, kSpnNumberQuad);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x23EF40u, gen::fn_sub_21EB80_0021eb80);  // (quad, uv*): the uv rectangle
    a0 = 0;
    jal(ctx, 0x23EF4Cu, gen::fn_sub_20E510_0020e510);  // [sflRes_GetGround](i) -> raster
    lwc1(f0, v0, 12);
    cvt_s_w(f2, f0);
    lwc1(f0, v0, 16);
    cvt_s_w(f1, f0);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0x30);
    mtc1(zero, f0);
    div_s(f0, f0, f1);
    swc1(f0, sp, 0x34);
    v0 = 0x432E0000;
    mtc1(v0, f0);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0x38);
    v0 = 0x42000000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    swc1(f0, sp, 0x3C);
    a0 = addiu(s1, kSpnTitleQuad);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x23EFB8u, gen::fn_sub_21EB80_0021eb80);  // (quad, uv*): the uv rectangle
    sw(zero, s1, kSpnFrame);
    sw(zero, s1, kSpnMode);
    lw(v0, s1, kSpnFlags);
    v0 = v0 | 0x2;
    sw(v0, s1, kSpnFlags);
    sw(s0, s1, kSpnCount);
    jal(ctx, 0x23EFD8u, gen::fn_sub_23DAC0_0023dac0);
    a0 = 1;
    a1 = 0;
    a2 = 6;
    a3 = 0;
    jal(ctx, 0x23EFF0u, gen::fn_sub_10A4E0_0010a4e0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0023F390 sub_23F390 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflPanel_IsAnimating] returns flag bit 1.
void sub_23F390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023f390
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v0 == 0) {
        // 0x0023f3a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23F3B0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023f3b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(v0, v0, kSpnFlags);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0023F3E0 sub_23F3E0 -- 72 bytes; frame 0x10: ra sp+0x0
// [sflPanel_Hold] sets flag bit 3.
void sub_23F3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023f3e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v1 == 0) {
        // 0x0023f3f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23F400u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023f408 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(v1, a0, kSpnFlags);
    v1 = v1 | 0x8;
    sw(v1, a0, kSpnFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0023F430 sub_23F430 -- 76 bytes; frame 0x10: ra sp+0x0
// [sflPanel_Release] clears flag bit 3.
void sub_23F430(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023f430
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    if (v1 == 0) {
        // 0x0023f444
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23F450u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("sfl_panel.c", 127): `jr $ra` in retail, execution goes on
    }
    // 0x0023f458 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpSflPanel);  // 0x7CE318 sfl_panel.c work (the Shuffle Time panel)
    lw(a0, a1, kSpnFlags);
    v1 = si(-9);
    v1 = a0 & v1;
    sw(v1, a1, kSpnFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
