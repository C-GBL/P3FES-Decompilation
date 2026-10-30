// Phase 5 slice band20 -- the battle panels: baus_main.c (the auto-battle setting display), bpp_main.c /
// bpp_panel.c (the party panel and its member panels), the analysis panel's layout / draw (bsa band), bse_main.c,
// bp_res.c / bp_tex.c (the panel resources, sprite sets, rasters), bi_main.c's work.
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
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1FF430_001ff430(p3fes::EEContext&);
void fn_sub_1FF5B0_001ff5b0(p3fes::EEContext&);
void fn_sub_1FF630_001ff630(p3fes::EEContext&);
void fn_sub_208AD0_00208ad0(p3fes::EEContext&);
void fn_sub_208B20_00208b20(p3fes::EEContext&);
void fn_sub_208F60_00208f60(p3fes::EEContext&);
void fn_sub_209540_00209540(p3fes::EEContext&);
void fn_sub_209A00_00209a00(p3fes::EEContext&);
void fn_sub_20ED50_0020ed50(p3fes::EEContext&);
void fn_sub_20ED70_0020ed70(p3fes::EEContext&);
void fn_sub_20EDC0_0020edc0(p3fes::EEContext&);
void fn_sub_20EDF0_0020edf0(p3fes::EEContext&);
void fn_sub_20F260_0020f260(p3fes::EEContext&);
void fn_sub_20F3B0_0020f3b0(p3fes::EEContext&);
void fn_sub_20F680_0020f680(p3fes::EEContext&);
void fn_sub_20F720_0020f720(p3fes::EEContext&);
void fn_sub_20F9A0_0020f9a0(p3fes::EEContext&);
void fn_sub_20FDD0_0020fdd0(p3fes::EEContext&);
void fn_sub_20FE20_0020fe20(p3fes::EEContext&);
void fn_sub_210D90_00210d90(p3fes::EEContext&);
void fn_sub_213E80_00213e80(p3fes::EEContext&);
void fn_sub_215770_00215770(p3fes::EEContext&);
void fn_sub_215830_00215830(p3fes::EEContext&);
void fn_sub_21B650_0021b650(p3fes::EEContext&);
void fn_sub_21B660_0021b660(p3fes::EEContext&);
void fn_sub_21B920_0021b920(p3fes::EEContext&);
void fn_sub_21B940_0021b940(p3fes::EEContext&);
void fn_sub_21BCB0_0021bcb0(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21C450_0021c450(p3fes::EEContext&);
void fn_sub_21C5D0_0021c5d0(p3fes::EEContext&);
void fn_sub_21C640_0021c640(p3fes::EEContext&);
void fn_sub_21C6B0_0021c6b0(p3fes::EEContext&);
void fn_sub_21C790_0021c790(p3fes::EEContext&);
void fn_sub_21C9F0_0021c9f0(p3fes::EEContext&);
void fn_sub_21CC20_0021cc20(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21CD00_0021cd00(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21DD60_0021dd60(p3fes::EEContext&);
void fn_sub_21E170_0021e170(p3fes::EEContext&);
void fn_sub_21EAE0_0021eae0(p3fes::EEContext&);
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);
void fn_sub_21EC40_0021ec40(p3fes::EEContext&);
void fn_sub_22C720_0022c720(p3fes::EEContext&);
void fn_sub_22C850_0022c850(p3fes::EEContext&);
void fn_sub_22C8A0_0022c8a0(p3fes::EEContext&);
void fn_sub_22DF10_0022df10(p3fes::EEContext&);
void fn_sub_22E780_0022e780(p3fes::EEContext&);
void fn_sub_22E850_0022e850(p3fes::EEContext&);
void fn_sub_22E900_0022e900(p3fes::EEContext&);
void fn_sub_22E9A0_0022e9a0(p3fes::EEContext&);
void fn_sub_22EA40_0022ea40(p3fes::EEContext&);
void fn_sub_22EB30_0022eb30(p3fes::EEContext&);
void fn_sub_22ECB0_0022ecb0(p3fes::EEContext&);
void fn_sub_22F1C0_0022f1c0(p3fes::EEContext&);
void fn_sub_22F3B0_0022f3b0(p3fes::EEContext&);
void fn_sub_22FA80_0022fa80(p3fes::EEContext&);
void fn_sub_232EA0_00232ea0(p3fes::EEContext&);
void fn_sub_2337E0_002337e0(p3fes::EEContext&);
void fn_sub_233850_00233850(p3fes::EEContext&);
void fn_sub_2338F0_002338f0(p3fes::EEContext&);
void fn_sub_233950_00233950(p3fes::EEContext&);
void fn_sub_233960_00233960(p3fes::EEContext&);
void fn_sub_238A50_00238a50(p3fes::EEContext&);
void fn_sub_239140_00239140(p3fes::EEContext&);
void fn_sub_23F480_0023f480(p3fes::EEContext&);
void fn_sub_23F500_0023f500(p3fes::EEContext&);
void fn_sub_267370_00267370(p3fes::EEContext&);
void fn_sub_280580_00280580(p3fes::EEContext&);
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);
void fn_sub_29B0C0_0029b0c0(p3fes::EEContext&);
void fn_sub_2D20A0_002d20a0(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE40_004cde40(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_4CDF30_004cdf30(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b20;  // the named offsets and $gp slots of band20.h

// 0x00208AD0 sub_208AD0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bausMain_Register](work) baus_main.c: asserts the slot is free (K_Assert line 78), clears the work's
// flags and stores it in the $gp slot (bpRoot_CreateBattlePanelTasks).
void sub_208AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00208ad0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
    if (v1 != 0) {
        // 0x00208aec
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 20648);  // "baus_main.c"
        a1 = 78;
        jal(ctx, 0x208AF8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("baus_main.c", 78): `jr $ra` in retail, execution goes on
    }
    // 0x00208b00 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00208B20 sub_208B20 -- 12 bytes; leaf frame (no stack)
// [bausMain_Unregister] clears the baus_main.c slot (sub_1FDC00, the panel teardown).
void sub_208B20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x00208b20
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
}

// 0x00208F60 sub_208F60 -- 1420 bytes; frame 0x100: ra sp+0x90, s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bausMain_Layout] lays out every unit's auto-battle entry: the unit's screen position (sub_280580 ->
// sub_2D20A0; off-screen entries get flag bit 0 and are skipped), up to two setting digits (sub_209A00; -1 = the other
// setting) or the empty mark (panel set 1 page 70), the frame (page 1) and the gauge (set 5 page 4, its width scaled by
// entry +8 / entry +12) -- all opaque white.
void sub_208F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x00208f60
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
    if (v0 == 0) {
        // 0x00208fac
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 20648);  // "baus_main.c"
        a1 = 71;
        jal(ctx, 0x208FB8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("baus_main.c", 71): `jr $ra` in retail, execution goes on
    }
    // 0x00208fc0
    charge(ctx, 12);
    lw(s5, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
    a0 = 1;
    jal(ctx, 0x208FC8u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    a0 = 5;
    jal(ctx, 0x208FD8u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s6 = v0;
    s1 = 0;
    for (;;) {
        // 0x00209494
        charge(ctx, 4);
        lw(v1, s5, kBausCount);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00208ff0
        charge(ctx, 22);
        v0 = sll(s1, 5);
        v0 = addu(v0, s1);
        v0 = sll(v0, 5);
        a0 = addu(s5, v0);
        s3 = addiu(a0, kBausEntries);
        lw(v1, a0, kBausEntries);
        v0 = si(-2);
        v0 = v1 & v0;
        sw(v0, a0, kBausEntries);
        lw(a0, a0, 20);
        jal(ctx, 0x209018u, gen::fn_sub_1FF430_001ff430);  // the btlUnit of an id
        a0 = v0;
        a1 = addiu(sp, 0xD8);
        jal(ctx, 0x209028u, gen::fn_sub_280580_00280580);
        a0 = addiu(sp, 0xD8);
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x209038u, gen::fn_sub_2D20A0_002d20a0);
        if (v0 == 0) {
            // 0x00209048
            charge(ctx, 3);
            lw(v1, s3, 0);
            v1 = v1 | 0x1;
            sw(v1, s3, 0);
        }
        // 0x00209054
        charge(ctx, 4);
        lw(v1, s3, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x00209064
            charge(ctx, 33);
            lwc1(f0, sp, 0xF0);
            v0 = 0x425C0000;
            mtc1(v0, f2);
            sub_s(f24, f0, f2);
            v0 = 0x41A00000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0xF4);
            sub_s(f0, f0, f2);
            add_s(f23, f1, f0);
            s0 = 0;
            v0 = 0x421C0000;
            mtc1(v0, f0);
            add_s(f21, f0, f24);
            v0 = 0x423C0000;
            mtc1(v0, f0);
            add_s(f1, f0, f23);
            v0 = 0x40400000;
            mtc1(v0, f0);
            sub_s(f20, f1, f0);
            v0 = 0x42200000;
            mtc1(v0, f0);
            add_s(f26, f0, f23);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            add_s(f25, f0, f21);
            for (;;) {
                // 0x0020926c
                charge(ctx, 4);
                lw(v0, s3, 536);
                v0 = slt(s0, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002090e8
                charge(ctx, 6);
                v0 = sll(s0, 2);
                v0 = addu(s3, v0);
                a0 = addiu(v0, 528);
                lw(v1, v0, 528);
                if (v1 == 0) {
                    // 0x00209100
                    charge(ctx, 3);
                    v0 = si(-1);
                    if (v1 == v0) {
                        goto L_00209184;
                    }
                    // 0x0020910c
                    charge(ctx, 30);
                    a0 = s2;
                    a1 = 70;
                    jal(ctx, 0x209114u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    swc1(f21, sp, 0xB0);
                    swc1(f20, sp, 0xB4);
                    lwc1(f0, v0, kSpW);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xB8);
                    lwc1(f0, v0, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xBC);
                    v0 = sll(s0, 8);
                    v0 = addu(s3, v0);
                    s4 = addiu(v0, 16);
                    a0 = s4;
                    a1 = addiu(sp, 0xB0);
                    jal(ctx, 0x209150u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 255;
                    sb(v0, sp, 0xFC);
                    sb(v0, sp, 0xFD);
                    sb(v0, sp, 0xFE);
                    sb(v0, sp, 0xFF);
                    a0 = s4;
                    a1 = addiu(sp, 0xFC);
                    jal(ctx, 0x209174u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                    goto L_00209268;
                }
            L_00209184:
                charge(ctx, 3);
                v0 = 1;
                if (s0 == v0) {
                    // 0x002091cc
                    charge(ctx, 8);
                    swc1(f25, sp, 0xE8);
                    swc1(f26, sp, 0xEC);
                    lwc1(f22, gp, -32544);  // 0x7CADD0 = 0.7f
                    v0 = 255;
                    sb(v0, sp, 0xFC);
                    sb(v0, sp, 0xFD);
                    sb(v0, sp, 0xFE);
                    sb(v0, sp, 0xFF);
                } else {
                    // 0x00209190
                    charge(ctx, 2);
                    if (s0 == 0) {
                        // 0x002091a0
                        charge(ctx, 11);
                        swc1(f21, sp, 0xE8);
                        swc1(f26, sp, 0xEC);
                        v0 = 0x3F800000;
                        mtc1(v0, f22);
                        v0 = 255;
                        sb(v0, sp, 0xFC);
                        sb(v0, sp, 0xFD);
                        sb(v0, sp, 0xFE);
                        sb(v0, sp, 0xFF);
                    } else {
                        // 0x00209198
                        charge(ctx, 2);
                    }
                }
                // 0x002091ec
                charge(ctx, 4);
                lw(v1, a0, 0);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00209230
                    charge(ctx, 10);
                    v0 = sll(s0, 8);
                    v0 = addu(s3, v0);
                    s4 = addiu(v0, 16);
                    a2 = addiu(v1, 1);
                    a0 = s4;
                    a1 = 1;
                    a3 = addiu(sp, 0xE8);
                    mov_s(f12, f22);
                    jal(ctx, 0x209250u, gen::fn_sub_209A00_00209a00);
                } else {
                    // 0x002091fc
                    charge(ctx, 13);
                    v0 = sll(s0, 8);
                    v0 = addu(s3, v0);
                    s4 = addiu(v0, 16);
                    a1 = 1;
                    a2 = subu(a1, s0);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    a0 = s4;
                    a3 = addiu(sp, 0xE8);
                    jal(ctx, 0x209220u, gen::fn_sub_209A00_00209a00);
                }
                // 0x00209258
                charge(ctx, 4);
                a0 = s4;
                a1 = addiu(sp, 0xFC);
                jal(ctx, 0x209260u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            L_00209268:
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0020927c
            charge(ctx, 33);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x209284u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x425C0000;
            mtc1(v1, f1);
            add_s(f0, f1, f24);
            swc1(f0, sp, 0xB0);
            add_s(f0, f1, f23);
            swc1(f0, sp, 0xB4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xB8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xBC);
            a0 = addiu(s3, 800);
            a1 = addiu(sp, 0xB0);
            jal(ctx, 0x2092C8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xFC);
            sb(v0, sp, 0xFD);
            sb(v0, sp, 0xFE);
            v0 = 0x437F0000;
            mtc1(v0, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00209318
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00209300
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00209330
            charge(ctx, 71);
            sb(v1, sp, 0xFF);
            a0 = addiu(s3, 800);
            a1 = addiu(sp, 0xFC);
            jal(ctx, 0x20933Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s6;
            a1 = 4;
            jal(ctx, 0x20934Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            a0 = s0;
            a1 = addiu(sp, 0xA0);
            jal(ctx, 0x209360u, gen::fn_sub_21CD00_0021cd00);  // (page, uv*) -> the page's uv rectangle
            lwc1(f0, s3, 8);
            cvt_s_w(f1, f0);
            lwc1(f0, s3, 12);
            cvt_s_w(f0, f0);
            div_s(f20, f1, f0);
            lwc1(f1, sp, 0xA0);
            lwc1(f0, sp, 0xA8);
            sub_s(f0, f0, f1);
            mul_s(f0, f0, f20);
            swc1(f1, sp, 0xB0);
            lwc1(f1, sp, 0xA4);
            swc1(f1, sp, 0xB4);
            swc1(f0, sp, 0xB8);
            lwc1(f0, sp, 0xAC);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0xBC);
            a0 = addiu(s3, 544);
            a1 = addiu(sp, 0xB0);
            jal(ctx, 0x2093B0u, gen::fn_sub_21EB80_0021eb80);  // (quad, uv*): the uv rectangle
            v0 = 0x425C0000;
            mtc1(v0, f1);
            v0 = 0x41000000;
            mtc1(v0, f0);
            add_s(f0, f0, f24);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            v0 = 0x40800000;
            mtc1(v0, f0);
            add_s(f0, f0, f23);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB4);
            lwc1(f0, s0, kSpW);
            cvt_s_w(f0, f0);
            mul_s(f0, f0, f20);
            swc1(f0, sp, 0xB8);
            lwc1(f0, s0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xBC);
            a0 = addiu(s3, 544);
            a1 = addiu(sp, 0xB0);
            jal(ctx, 0x209414u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xFC);
            sb(v0, sp, 0xFD);
            sb(v0, sp, 0xFE);
            v0 = 0x437F0000;
            mtc1(v0, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00209464
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0020944c
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0020947c
            charge(ctx, 5);
            sb(v1, sp, 0xFF);
            a0 = addiu(s3, 544);
            a1 = addiu(sp, 0xFC);
            jal(ctx, 0x209488u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        }
        // 0x00209490
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x002094a4
    charge(ctx, 18);
    ld(ra, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x00209540 sub_209540 -- 88 bytes; frame 0x10: ra sp+0x0
// [bausMain_Draw] the draw task's hook: lays the entries out when the display is on (flag bit 0).
void sub_209540(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209540
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
    if (v1 == 0) {
        // 0x00209554
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 20648);  // "baus_main.c"
        a1 = 71;
        jal(ctx, 0x209560u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("baus_main.c", 71): `jr $ra` in retail, execution goes on
    }
    // 0x00209568
    charge(ctx, 6);
    lw(v1, gp, kGpBausMain);  // 0x7CE2EC baus_main.c work (the auto-battle setting display)
    lw(v1, v1, kBausFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00209580
        charge(ctx, 2);
        jal(ctx, 0x209580u, gen::fn_sub_208F60_00208f60);
    }
    // 0x00209588 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209A00 sub_209A00 -- 404 bytes; frame 0x1A0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [bausMain_SetDigits](quads, n, value, xy*, scale $f12) prints `value` with the format at 0x7CC420 and
// puts each digit's page (panel set 1, page 46 + value) into one quad, 15 px apart from the right; the quads past the
// string get a zero-size rectangle at xy. More digits than n is K_Assert line 478.
void sub_209A00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00209a00
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    mov_s(f20, f12);
    a0 = 1;
    jal(ctx, 0x209A40u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s6 = v0;
    a0 = addiu(sp, 0x90);
    a1 = addiu(gp, -26832);  // "%d"
    a2 = s1;
    jal(ctx, 0x209A58u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x90);
    jal(ctx, 0x209A64u, gen::fn_strlen_00524388);
    s4 = v0;
    at = slt(s2, s4);
    if (at != 0) {
        // 0x00209a7c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 20648);  // "baus_main.c"
        a1 = 478;
        jal(ctx, 0x209A88u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("baus_main.c", 478): `jr $ra` in retail, execution goes on
    }
    // 0x00209a90
    charge(ctx, 3);
    s5 = 0;
    for (;;) {  // while (s5 < s4)
        // 0x00209b14
        charge(ctx, 3);
        v1 = slt(s5, s4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00209a9c
        charge(ctx, 30);
        a1 = addiu(s1, 46);
        a0 = s6;
        jal(ctx, 0x209AA4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = addiu(s4, -1);
        a0 = subu(v1, s5);
        v1 = sll(a0, 4);
        v1 = subu(v1, a0);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s0, 0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x190);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x194);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        mul_s(f0, f0, f20);
        swc1(f0, sp, 0x198);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        mul_s(f0, f0, f20);
        swc1(f0, sp, 0x19C);
        v0 = sll(s5, 8);
        a0 = addu(s3, v0);
        a1 = addiu(sp, 0x190);
        jal(ctx, 0x209B08u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s5 = addiu(s5, 1);
    }
    // 0x00209b20
    charge(ctx, 2);
    for (;;) {  // while (s4 < s2)
        // 0x00209b58
        charge(ctx, 3);
        v1 = slt(s4, s2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00209b28
        charge(ctx, 12);
        lwc1(f0, s0, 0);
        swc1(f0, sp, 0x190);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x194);
        sw(zero, sp, 0x198);
        sw(zero, sp, 0x19C);
        v0 = sll(s4, 8);
        a0 = addu(s3, v0);
        a1 = addiu(sp, 0x190);
        jal(ctx, 0x209B4Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s4 = addiu(s4, 1);
    }
    // 0x00209b64
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x0020ED50 sub_20ED50 -- 28 bytes; leaf frame (no stack)
// [bppMain_Register](work) bpp_main.c: clears the flags, the member count and the slide words and stores the
// work in the $gp slot.
void sub_20ED50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0020ed50
    enter(ctx, 7);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 23120);
    sw(zero, a0, 23132);
    sw(zero, a0, 23136);
    sw(a0, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
}

// 0x0020ED70 sub_20ED70 -- 72 bytes; frame 0x10: ra sp+0x0
// [bppMain_Activate] sets flag bit 7 (the panel runs).
void sub_20ED70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020ed70
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v1 == 0) {
        // 0x0020ed84
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20ED90u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020ed98 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    lw(v1, a0, kBppFlags);
    v1 = v1 | 0x80;
    sw(v1, a0, kBppFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020EDC0 sub_20EDC0 -- 36 bytes; frame 0x10: ra sp+0x0
// [bppMain_Unregister] closes the member panels (sub_20F680) and clears the slot.
void sub_20EDC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020edc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x20EDC8u, gen::fn_sub_20F680_0020f680);
    sw(zero, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020EDF0 sub_20EDF0 -- 1124 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppMain_Update] the party panel's update (bpRoot_UpdateBattlePanelTask), while flag bit 7 is set:
// slides the panel out (bits 4 / 5 / 6) or back in; follows the acting unit (sub_29AD20): opens a member's target panel
// (bppPanel_Open, sub_2337E0) when a party member acts, closes it (sub_233850) when the actor changes; then refreshes
// each member's HP / SP digits, ailment icon and state when the value changed (sub_22E900 / sub_22E9A0 / sub_22F1C0 /
// sub_22E780).
void sub_20EDF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020edf0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v1 == 0) {
        // 0x0020ee10
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20EE1Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020ee24
    charge(ctx, 6);
    lw(s1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    lw(a0, s1, kBppFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x80;
    if (v1 == 0) {
        // 0x0020ee3c
        charge(ctx, 3);
        v1 = a0 & 0x10;
        if (v1 == 0) {
            // 0x0020ee48
            charge(ctx, 3);
            v1 = a0 & 0x20;
            if (v1 != 0) {
                goto L_0020ee60;
            }
            // 0x0020ee54
            charge(ctx, 3);
            v1 = a0 & 0x40;
            if (v1 != 0) {
                goto L_0020ee60;
            }
            // 0x0020ee7c
            charge(ctx, 5);
            lw(a0, s1, kBppSlide);
            lw(v1, s1, kBppSlideMax);
            at = slt(a0, v1);
            if (at != 0) {
                // 0x0020ee90
                charge(ctx, 2);
                v1 = addiu(a0, 1);
                sw(v1, s1, kBppSlide);
            }
            goto L_0020ee98;
        }
    L_0020ee60:
        charge(ctx, 3);
        lw(v1, s1, 23132);
        if (i64(v1) > 0) {
            // 0x0020ee6c
            charge(ctx, 4);
            v1 = addiu(v1, -1);
            sw(v1, s1, 23132);
        }
    L_0020ee98:
        charge(ctx, 4);
        lw(v1, s1, 0);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            // 0x0020eea8
            charge(ctx, 5);
            jal(ctx, 0x20EEA8u, gen::fn_sub_29AD20_0029ad20);
            s0 = v0;
            if (s0 != 0) {
                // 0x0020eebc
                charge(ctx, 4);
                lw(v1, s1, 0);
                v1 = v1 & 0x1;
                if (v1 == 0) {
                    goto L_0020ef7c;
                }
                // 0x0020eecc
                charge(ctx, 5);
                lw(v1, s0, 48);
                lw(a0, v1, 168);
                lw(v1, s1, 23124);
                if (a0 != v1) {
                    goto L_0020ef7c;
                }
                // 0x0020eee0
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x20EEE4u, gen::fn_sub_29B0C0_0029b0c0);
                if (v0 != 0) {
                    goto L_0020ef7c;
                }
                // 0x0020eef4
                charge(ctx, 7);
                lw(a0, s1, 23124);
                jal(ctx, 0x20EEF8u, gen::fn_sub_1FF430_001ff430);  // the btlUnit of an id
                s0 = v0;
                lbu(v1, v0, 162);
                if (v1 == 0) {
                    // 0x0020ef18
                    charge(ctx, 4);
                    lw(v0, s1, 0);
                    v0 = v0 & 0x4;
                    if (v0 == 0) {
                        // 0x0020ef28
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7672);  // "bpp_main.c"
                        a1 = 147;
                        jal(ctx, 0x20EF34u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 147): `jr $ra` in retail, execution goes on
                    }
                    // 0x0020ef3c
                    charge(ctx, 7);
                    lw(v0, s0, 2604);
                    lhu(a0, v0, 2);
                    jal(ctx, 0x20EF44u, gen::fn_sub_20F720_0020f720);  // [bppMain_FindMember](u16 id) -> member record
                    a0 = addiu(v0, kBmPanel);
                    jal(ctx, 0x20EF50u, gen::fn_sub_233850_00233850);
                } else {
                    // 0x0020ef10
                    charge(ctx, 2);
                }
                // 0x0020ef58
                charge(ctx, 9);
                lw(a0, s1, 0);
                v1 = si(-5);
                a0 = a0 & v1;
                sw(a0, s1, 0);
                v1 = si(-2);
                v1 = a0 & v1;
                sw(v1, s1, 0);
                goto L_0020f150;
            }
        L_0020ef7c:
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0020ef84
                charge(ctx, 4);
                lw(a1, s1, 0);
                v1 = a1 & 0x1;
                if (v1 == 0) {
                    goto L_0020f0b8;
                }
                // 0x0020ef94
                charge(ctx, 5);
                lw(a0, s1, 23124);
                lw(v1, s0, 48);
                lw(v1, v1, 168);
                if (v1 == a0) {
                    goto L_0020f0b8;
                }
                // 0x0020efa8
                charge(ctx, 3);
                v0 = a1 & 0x4;
                if (v0 != 0) {
                    // 0x0020efb4
                    charge(ctx, 6);
                    jal(ctx, 0x20EFB4u, gen::fn_sub_1FF430_001ff430);  // the btlUnit of an id
                    s2 = v0;
                    lbu(v0, v0, 162);
                    if (v0 == 0) {
                        // 0x0020efd4
                        charge(ctx, 4);
                        lw(v0, s1, 0);
                        v0 = v0 & 0x4;
                        if (v0 == 0) {
                            // 0x0020efe4
                            charge(ctx, 5);
                            a0 = 0x690000;
                            a0 = addiu(a0, -7672);  // "bpp_main.c"
                            a1 = 173;
                            jal(ctx, 0x20EFF0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 173): `jr $ra` in retail, execution goes on
                        }
                        // 0x0020eff8
                        charge(ctx, 7);
                        lw(v0, s2, 2604);
                        lhu(a0, v0, 2);
                        jal(ctx, 0x20F000u, gen::fn_sub_20F720_0020f720);  // [bppMain_FindMember](u16 id) -> member record
                        a0 = addiu(v0, kBmPanel);
                        jal(ctx, 0x20F00Cu, gen::fn_sub_233850_00233850);
                    } else {
                        // 0x0020efcc
                        charge(ctx, 2);
                    }
                    // 0x0020f014
                    charge(ctx, 4);
                    lw(v1, s1, 0);
                    v0 = si(-5);
                    v0 = v1 & v0;
                    sw(v0, s1, 0);
                }
                // 0x0020f024
                charge(ctx, 9);
                lw(v1, s1, 0);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s1, 0);
                a0 = s0;
                jal(ctx, 0x20F038u, gen::fn_sub_29B0C0_0029b0c0);
                if (v0 != 0) {
                    // 0x0020f048
                    charge(ctx, 4);
                    lw(a0, s0, 48);
                    lbu(v1, a0, 162);
                    if (v1 == 0) {
                        // 0x0020f060
                        charge(ctx, 14);
                        lw(v0, a0, 2604);
                        lhu(a0, v0, 2);
                        jal(ctx, 0x20F068u, gen::fn_sub_20F720_0020f720);  // [bppMain_FindMember](u16 id) -> member record
                        a0 = addiu(v0, kBmPanel);
                        jal(ctx, 0x20F074u, gen::fn_sub_2337E0_002337e0);
                        lw(v1, s0, 48);
                        lw(v1, v1, 2604);
                        lhu(v1, v1, 2);
                        sh(v1, s1, 23128);
                        lw(v1, s1, 0);
                        v1 = v1 | 0x4;
                        sw(v1, s1, 0);
                    } else {
                        // 0x0020f058
                        charge(ctx, 2);
                    }
                    // 0x0020f098
                    charge(ctx, 8);
                    lw(v1, s0, 48);
                    lw(v1, v1, 168);
                    sw(v1, s1, 23124);
                    lw(v1, s1, 0);
                    v1 = v1 | 0x1;
                    sw(v1, s1, 0);
                }
                goto L_0020f150;
            }
        L_0020f0b8:
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0020f0c0
                charge(ctx, 5);
                lw(v1, s1, 0);
                v1 = nor(v1, 0);
                v1 = v1 & 0x1;
                if (v1 != 0) {
                    // 0x0020f0d4
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x20F0D8u, gen::fn_sub_29B0C0_0029b0c0);
                    if (v0 != 0) {
                        // 0x0020f0e8
                        charge(ctx, 4);
                        lw(a0, s0, 48);
                        lbu(v1, a0, 162);
                        if (v1 == 0) {
                            // 0x0020f100
                            charge(ctx, 14);
                            lw(v0, a0, 2604);
                            lhu(a0, v0, 2);
                            jal(ctx, 0x20F108u, gen::fn_sub_20F720_0020f720);  // [bppMain_FindMember](u16 id) -> member record
                            a0 = addiu(v0, kBmPanel);
                            jal(ctx, 0x20F114u, gen::fn_sub_2337E0_002337e0);
                            lw(v1, s0, 48);
                            lw(v1, v1, 2604);
                            lhu(v1, v1, 2);
                            sh(v1, s1, 23128);
                            lw(v1, s1, 0);
                            v1 = v1 | 0x4;
                            sw(v1, s1, 0);
                        } else {
                            // 0x0020f0f8
                            charge(ctx, 2);
                        }
                        // 0x0020f138
                        charge(ctx, 6);
                        lw(v1, s0, 48);
                        lw(v1, v1, 168);
                        sw(v1, s1, 23124);
                        lw(v1, s1, 0);
                        v1 = v1 | 0x1;
                        sw(v1, s1, 0);
                    }
                }
            }
        }
    L_0020f150:
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x0020f228
            charge(ctx, 4);
            lw(v1, s1, 23120);
            v1 = slt(s2, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020f15c
            charge(ctx, 11);
            v0 = 5776;
            mult(v0, s2, v0);
            v0 = addu(s1, v0);
            s0 = addiu(v0, 16);
            lh(a0, v0, 20);
            jal(ctx, 0x20F170u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp](id)
            a1 = v0 & 0xFFFF;
            lw(v0, s0, 16);
            if (v0 != a1) {
                // 0x0020f188
                charge(ctx, 4);
                sw(a1, s0, 16);
                a0 = addiu(s0, 32);
                jal(ctx, 0x20F190u, gen::fn_sub_22E900_0022e900);
            }
            // 0x0020f198
            charge(ctx, 7);
            lh(a0, s0, 4);
            jal(ctx, 0x20F19Cu, gen::fn_sub_16C570_0016c570);  // [datGetPcSp](id)
            a1 = v0 & 0xFFFF;
            lw(v0, s0, 20);
            if (v0 != a1) {
                // 0x0020f1b4
                charge(ctx, 4);
                sw(a1, s0, 20);
                a0 = addiu(s0, 32);
                jal(ctx, 0x20F1BCu, gen::fn_sub_22E9A0_0022e9a0);
            }
            // 0x0020f1c4
            charge(ctx, 8);
            lh(a0, s0, 4);
            jal(ctx, 0x20F1C8u, gen::fn_sub_16C970_0016c970);  // the member's ailment bits
            a0 = dsll32(v0, 12);
            a0 = dsrl32(a0, 12);
            lw(v1, s0, 24);
            if (v1 != a0) {
                // 0x0020f1e4
                charge(ctx, 5);
                sw(a0, s0, 24);
                a0 = addiu(s0, 32);
                a1 = v0;
                jal(ctx, 0x20F1F0u, gen::fn_sub_22F1C0_0022f1c0);
            }
            // 0x0020f1f8
            charge(ctx, 7);
            lh(a0, s0, 4);
            jal(ctx, 0x20F1FCu, gen::fn_sub_16C920_0016c920);  // the member's state (0..5)
            a1 = v0 & 0xFFFF;
            lw(v1, s0, 28);
            if (v1 != a1) {
                // 0x0020f214
                charge(ctx, 4);
                sw(a1, s0, 28);
                a0 = addiu(s0, 32);
                jal(ctx, 0x20F21Cu, gen::fn_sub_22E780_0022e780);
            }
            // 0x0020f224
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
    }
    // 0x0020f238 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0020F260 sub_20F260 -- 324 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppMain_Draw] the draw task's hook: for each member panel the four panel steps (sub_233950 /
// sub_233960, the layout sub_22C8A0, the draw sub_22DF10).
void sub_20F260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0020f260
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v1 == 0) {
        // 0x0020f280
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20F28Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020f294
    charge(ctx, 6);
    lw(s1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    lw(v1, s1, kBppFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x80;
    if (v1 == 0) {
        // 0x0020f2ac
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x0020f378
            charge(ctx, 4);
            lw(a0, s1, kBppCount);
            v1 = slt(s2, a0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020f2b8
            charge(ctx, 11);
            v0 = 5776;
            mult(v0, s2, v0);
            v0 = addu(s1, v0);
            s0 = addiu(v0, kBppMembers);
            v0 = addiu(a0, -1);
            v0 = subu(v0, s2);
            a0 = sll(v0, 1);
            lw(v1, s1, kBppSlide);
            at = slt(v1, a0);
            if (at == 0) {
                // 0x0020f2f0
                charge(ctx, 4);
                v0 = addiu(a0, 6);
                at = slt(v1, v0);
                if (at == 0) {
                    // 0x0020f334
                    charge(ctx, 2);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                } else {
                    // 0x0020f300
                    charge(ctx, 13);
                    v0 = subu(v1, a0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    div_s(f12, f1, f0);
                }
            } else {
                // 0x0020f2e4
                charge(ctx, 3);
                mtc1(zero, f12);
            }
            // 0x0020f33c
            charge(ctx, 15);
            a0 = addiu(s0, kBmPanel);
            jal(ctx, 0x20F340u, gen::fn_sub_233950_00233950);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a0 = addiu(s0, kBmPanel);
            jal(ctx, 0x20F354u, gen::fn_sub_233960_00233960);
            a0 = addiu(s0, kBmPanel);
            jal(ctx, 0x20F360u, gen::fn_sub_22C8A0_0022c8a0);
            a0 = addiu(s0, kBmPanel);
            jal(ctx, 0x20F36Cu, gen::fn_sub_22DF10_0022df10);
            s2 = addiu(s2, 1);
        }
    }
    // 0x0020f388 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0020F3B0 sub_20F3B0 -- 436 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppMain_Build] builds one member record per party member (sub_1FF5B0 / sub_1FF630): id, values -1
// (refresh on the first update), the panel (sub_22C720) at x 476, y 4 + 100 * row, max HP / SP; rescales the slide
// position to the new slide length 2 * (n - 1) + 6; flag bit 1.
void sub_20F3B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0020f3b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v0 == 0) {
        // 0x0020f3d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20F3E0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020f3e8
    charge(ctx, 7);
    lw(s1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    jal(ctx, 0x20F3ECu, gen::fn_sub_1FF5B0_001ff5b0);  // the party size
    s0 = v0;
    s2 = 0;
    for (;;) {  // while (s2 < s0)
        // 0x0020f440
        charge(ctx, 3);
        v1 = slt(s2, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020f404
        charge(ctx, 15);
        v0 = 5776;
        mult(v0, s2, v0);
        v0 = addu(s1, v0);
        s3 = addiu(v0, kBppMembers);
        sw(zero, v0, kBppMembers);
        a0 = s2;
        jal(ctx, 0x20F41Cu, gen::fn_sub_1FF630_001ff630);  // (i) -> the party member id
        sh(v0, s3, kBmId);
        v1 = si(-1);
        sw(v1, s3, kBmHp);
        sw(v1, s3, kBmSp);
        sw(v1, s3, kBmAilments);
        sw(v1, s3, kBmState);
        s2 = addiu(s2, 1);
    }
    // 0x0020f44c
    charge(ctx, 8);
    lw(a1, s1, kBppSlideMax);
    lw(a0, s1, kBppSlide);
    v1 = addiu(s0, -1);
    v1 = sll(v1, 1);
    v1 = addiu(v1, 6);
    sw(v1, s1, kBppSlideMax);
    if (a1 == 0) {
        // 0x0020f490
        charge(ctx, 1);
        sw(zero, s1, kBppSlide);
    } else {
        // 0x0020f46c
        charge(ctx, 9);
        lw(v1, s1, kBppSlideMax);
        mult(v1, a0, v1);
        div(v1, a1);
        mflo(v1);
        sw(v1, s1, kBppSlide);
    }
    // 0x0020f494
    charge(ctx, 4);
    sw(s0, s1, kBppCount);
    s2 = 0;
    for (;;) {
        // 0x0020f528
        charge(ctx, 4);
        lw(v1, s1, kBppCount);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020f4a4
        charge(ctx, 33);
        v0 = 5776;
        mult(v0, s2, v0);
        v0 = addu(s1, v0);
        s0 = addiu(v0, kBppMembers);
        a0 = addiu(s0, kBmPanel);
        lhu(a1, v0, kBppMembers + kBmId);
        jal(ctx, 0x20F4BCu, gen::fn_sub_22C720_0022c720);
        v0 = 0x43EE0000;
        sw(v0, s0, kBmPanel + kBpnX);
        v0 = 0x42C80000;
        mtc1(v0, f3);
        mtc1(s2, f0);
        cvt_s_w(f2, f0);
        v0 = 0x40800000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f0, f3, f2);
        swc1(f0, s0, kBmPanel + kBpnY);
        lh(a0, s0, kBmId);
        jal(ctx, 0x20F500u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp](id)
        v0 = v0 & 0xFFFF;
        sw(v0, s0, kBmPanel + kBpnMaxHp);
        lh(a0, s0, kBmId);
        jal(ctx, 0x20F514u, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp](id)
        v1 = v0 & 0xFFFF;
        sw(v1, s0, kBmPanel + kBpnMaxSp);
        s2 = addiu(s2, 1);
    }
    // 0x0020f538
    charge(ctx, 11);
    lw(v1, s1, kBppFlags);
    v1 = v1 | 0x2;
    sw(v1, s1, kBppFlags);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0020F680 sub_20F680 -- 152 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppMain_Close] closes every member panel (sub_22C850), count 0, clears flag bit 1.
void sub_20F680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020f680
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v1 == 0) {
        // 0x0020f69c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20F6A8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020f6b0
    charge(ctx, 4);
    lw(s0, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    s1 = 0;
    for (;;) {
        // 0x0020f6dc
        charge(ctx, 4);
        lw(v1, s0, kBppCount);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020f6c0
        charge(ctx, 7);
        v0 = 5776;
        mult(v0, s1, v0);
        v0 = addu(s0, v0);
        a0 = addiu(v0, kBppMembers + kBmPanel);
        jal(ctx, 0x20F6D0u, gen::fn_sub_22C850_0022c850);
        s1 = addiu(s1, 1);
    }
    // 0x0020f6ec
    charge(ctx, 11);
    sw(zero, s0, kBppCount);
    lw(a0, s0, kBppFlags);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, kBppFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020F9A0 sub_20F9A0 -- 212 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bppMain_RefreshMember](u16 id) finds the member record of `id` (K_Assert 412 and record 0 when there is
// none) and calls sub_2338F0 on its panel.
void sub_20F9A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020f9a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v0 == 0) {
        // 0x0020f9bc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20F9C8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020f9d0
    charge(ctx, 3);
    lw(v0, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v0 == 0) {
        // 0x0020f9dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20F9E8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020f9f0
    charge(ctx, 7);
    lw(a2, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    a3 = 0;
    a1 = s0 & 0xFFFF;
    lw(a0, a2, kBppCount);
    v1 = 5776;
    bool found = false;  // t0 = the member record whose id is the argument's low half
    for (;;) {  // while (a3 < a0)
        // 0x0020fa30
        charge(ctx, 3);
        v0 = slt(a3, a0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020fa0c
        charge(ctx, 6);
        mult(v0, a3, v1);
        v0 = addu(a2, v0);
        t0 = addiu(v0, kBppMembers);
        lhu(v0, v0, kBppMembers + kBmId);
        if (v0 == a1) {
            found = true;
            break;
        }
        // 0x0020fa2c
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    if (found) {
        // 0x0020fa24
        charge(ctx, 2);
    } else {
        // 0x0020fa3c: no member has the id
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 412;
        jal(ctx, 0x20FA48u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 412): `jr $ra` in retail, execution goes on
        t0 = 0;
    }
    // 0x0020fa54: sub_2338F0 on the member's panel (record +32)
    charge(ctx, 8);
    a0 = addiu(t0, 32);
    jal(ctx, 0x20FA58u, gen::fn_sub_2338F0_002338f0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020FDD0 sub_20FDD0 -- 76 bytes; frame 0x10: ra sp+0x0
// [bppMain_ClearFlag40] clears flag bit 6 (a slide-out request).
void sub_20FDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020fdd0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    if (v1 == 0) {
        // 0x0020fde4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20FDF0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_main.c", 67): `jr $ra` in retail, execution goes on
    }
    // 0x0020fdf8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBppMain);  // 0x7CE2F4 bpp_main.c work (the party panel)
    lw(a0, a1, kBppFlags);
    v1 = si(-65);
    v1 = a0 & v1;
    sw(v1, a1, kBppFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020FE20 sub_20FE20 -- 12 bytes; leaf frame (no stack)
// [panel work +4 = 0] stores 0 at a0 +4 (bpRoot_CreateBattlePanelTasks).
void sub_20FE20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0020fe20
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, 4);
}

// 0x00210D90 sub_210D90 -- 12516 bytes; frame 0xF0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bsaPanel_Layout](panel) lays out the 42,688-byte analysis panel (bpRoot_UpdateBattlePanelTask): a 10-frame fade
// in / out (+42672 frame, +42676 direction; the fade-out ends by closing the panel through sub_215770), then the quads
// of the frame, the title, the level digits (bpIfont sub_238A50), the HP / SP gauges, the affinity and status rows of
// the enemy (gBtlEnemyTbl) and the font lines, all with the fade's alpha.
void sub_210D90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    // 0x00210d90
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    a0 = 6;
    jal(ctx, 0x210DE0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s7 = v0;
    a0 = 1;
    jal(ctx, 0x210DF0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s3 = v0;
    a0 = 2;
    jal(ctx, 0x210E00u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s1 = v0;
    lw(a0, s2, 4);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00210e20
        charge(ctx, 3);
        v0 = a0 & 0x40;
        if (v0 == 0) {
            // 0x00210f54
            charge(ctx, 2);
            v0 = 0x3F800000;
            mtc1(v0, f22);
        } else {
            // 0x00210e2c
            charge(ctx, 6);
            v0 = 0x10000;
            v0 = addu(s2, v0);
            lw(v1, v0, -22860);
            v0 = 1;
            if (v1 == v0) {
                // 0x00210ec4
                charge(ctx, 6);
                v0 = 0x10000;
                v0 = addu(s2, v0);
                lw(v0, v0, -22864);
                at = slti(v0, 10);
                if (at == 0) {
                    // 0x00210ef4
                    charge(ctx, 10);
                    v0 = si(-65);
                    v0 = a0 & v0;
                    sw(v0, s2, 4);
                    a0 = s2;
                    jal(ctx, 0x210F04u, gen::fn_sub_215770_00215770);
                    lw(v1, s2, 4);
                    v0 = si(-2);
                    v0 = v1 & v0;
                    sw(v0, s2, 4);
                } else {
                    // 0x00210edc
                    charge(ctx, 6);
                    v1 = addiu(v0, 1);
                    v0 = 0x10000;
                    v0 = addu(s2, v0);
                    sw(v1, v0, -22864);
                }
                // 0x00210f1c
                charge(ctx, 14);
                v0 = 0x10000;
                v0 = addu(s2, v0);
                lwc1(f0, v0, -22864);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f22, f0, f1);
            } else {
                // 0x00210e44
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00210e54
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s2, v0);
                    lw(v0, v0, -22864);
                    at = slti(v0, 10);
                    if (at == 0) {
                        // 0x00210e84
                        charge(ctx, 3);
                        v0 = si(-65);
                        v0 = a0 & v0;
                        sw(v0, s2, 4);
                    } else {
                        // 0x00210e6c
                        charge(ctx, 6);
                        v1 = addiu(v0, 1);
                        v0 = 0x10000;
                        v0 = addu(s2, v0);
                        sw(v1, v0, -22864);
                    }
                    // 0x00210e90
                    charge(ctx, 13);
                    v0 = 0x10000;
                    v0 = addu(s2, v0);
                    lwc1(f0, v0, -22864);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f22, f1, f0);
                } else {
                    // 0x00210e4c
                    charge(ctx, 2);
                }
            }
        }
        // 0x00210f5c
        charge(ctx, 5);
        mtc1(zero, f23);
        lw(v1, s2, 0);
        v0 = 1;
        if (v1 != v0) {
            // 0x00210f70
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00210f80
                charge(ctx, 2);
                v0 = 0x43340000;
                mtc1(v0, f23);
            } else {
                // 0x00210f78
                charge(ctx, 2);
            }
        }
        // 0x00210f88
        charge(ctx, 35);
        a0 = s1;
        a1 = 31;
        jal(ctx, 0x210F90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x426C0000;
        sw(v1, sp, 0xC0);
        v1 = 0x42700000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 64);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x210FD4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f20, f0, f22);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0021102c
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00211014
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00211044
        charge(ctx, 10);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 64);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x211050u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        lw(v0, s2, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x40;
        if (v0 == 0) {
            // 0x00211080
            charge(ctx, 6);
            v0 = 0x10000;
            v0 = addu(s2, v0);
            lw(v1, v0, -22860);
            v0 = 1;
            if (v1 == v0) {
                // 0x00211138
                charge(ctx, 13);
                v0 = 0x10000;
                v0 = addu(s2, v0);
                lwc1(f0, v0, -22864);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f21, f0, f1);
                mtc1(zero, f24);
            } else {
                // 0x00211098
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x002110a8
                    charge(ctx, 6);
                    v0 = 0x10000;
                    v0 = addu(s2, v0);
                    lw(v0, v0, -22864);
                    at = slti(v0, 4);
                    if (at == 0) {
                        // 0x002110d4
                        charge(ctx, 3);
                        at = slti(v0, 8);
                        if (at == 0) {
                            // 0x00211124
                            charge(ctx, 5);
                            v0 = 0x3F800000;
                            mtc1(v0, f21);
                            mtc1(zero, f24);
                        } else {
                            // 0x002110e0
                            charge(ctx, 17);
                            v0 = addiu(v0, -4);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x40800000;
                            mtc1(v0, f0);
                            div_s(f21, f1, f0);
                            v0 = lui(0xC1A0);
                            mtc1(v0, f1);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            sub_s(f0, f0, f21);
                            mul_s(f24, f1, f0);
                        }
                    } else {
                        // 0x002110c0
                        charge(ctx, 5);
                        mtc1(zero, f21);
                        mov_s(f24, f21);
                    }
                } else {
                    // 0x002110a0
                    charge(ctx, 2);
                }
            }
        } else {
            // 0x0021106c
            charge(ctx, 5);
            mtc1(zero, f24);
            v0 = 0x3F800000;
            mtc1(v0, f21);
        }
        // 0x0021116c
        charge(ctx, 36);
        a0 = s1;
        a1 = 40;
        jal(ctx, 0x211174u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x41900000;
        sw(v1, sp, 0xC0);
        v1 = 0x42580000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        add_s(f0, f0, f24);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 5184);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x2111BCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f1, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x00211214
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002111fc
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0021122c
        charge(ctx, 10);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 5184);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x211238u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        lw(v0, s2, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x20;
        if (v0 == 0) {
            // 0x00211344
            charge(ctx, 35);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            a0 = s1;
            a1 = 50;
            jal(ctx, 0x21135Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42DC0000;
            sw(v1, sp, 0xC0);
            v1 = 0x42680000;
            mtc1(v1, f0);
            add_s(f26, f0, f23);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 24752);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x2113A0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f25, f0, f22);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x002113e8
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002113d0
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211400
            charge(ctx, 29);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 24752);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x21140Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 51;
            jal(ctx, 0x21141Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            v1 = 0x42D40000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 25008);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211454u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x0021148c
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211474
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x002114a4
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 25008);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x2114B0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            lwc1(f0, s0, kSpW);
            cvt_s_w(f1, f0);
            v0 = 0x42D40000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            v0 = 0x41F00000;
            sw(v0, sp, 0xC8);
            lwc1(f0, s0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 25264);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x2114F4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x0021152c
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211514
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211544
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 25264);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211550u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 54;
            jal(ctx, 0x211560u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x430C0000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 25520);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211594u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x002115cc
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002115b4
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x002115e4
            charge(ctx, 5);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 25520);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x2115F0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        } else {
            // 0x00211254
            charge(ctx, 4);
            lw(v0, s2, 19520);
            v0 = slti(v0, 10);
            if (v0 != 0) {
                // 0x00211274
                charge(ctx, 2);
                v0 = 0x42E20000;
                sw(v0, sp, 0xE0);
            } else {
                // 0x00211264
                charge(ctx, 4);
                v0 = 0x42D40000;
                sw(v0, sp, 0xE0);
            }
            // 0x0021127c
            charge(ctx, 22);
            v0 = 0x42780000;
            mtc1(v0, f0);
            add_s(f0, f0, f23);
            swc1(f0, sp, 0xE4);
            a0 = addiu(s2, 19536);
            a1 = 2;
            lw(a2, s2, 19520);
            a3 = 1;
            t0 = addiu(sp, 0xE0);
            jal(ctx, 0x2112A4u, gen::fn_sub_238A50_00238a50);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f20);
            if (cond(ctx)) {
                // 0x002112ec
                charge(ctx, 6);
                sub_s(f0, f20, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002112d4
                charge(ctx, 6);
                cvt_w_s(f0, f20);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211304
            charge(ctx, 4);
            sb(v1, sp, 0xEF);
            s0 = 0;
            for (;;) {  // while (s0 < 2)
                // 0x00211330
                charge(ctx, 3);
                v0 = slti(s0, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00211314
                charge(ctx, 7);
                v0 = sll(s0, 8);
                v0 = addu(s2, v0);
                a0 = addiu(v0, 19536);
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x211324u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s0 = addiu(s0, 1);
            }
            // 0x0021133c
            charge(ctx, 2);
        }
        // 0x002115f8
        charge(ctx, 5);
        lw(v0, s2, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x002116dc
            charge(ctx, 35);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            a0 = s1;
            a1 = 50;
            jal(ctx, 0x2116F4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43320000;
            sw(v1, sp, 0xC0);
            v1 = 0x42DA0000;
            mtc1(v1, f0);
            add_s(f26, f0, f23);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 25776);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211738u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f25, f0, f22);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211780
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211768
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211798
            charge(ctx, 29);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 25776);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x2117A4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 52;
            jal(ctx, 0x2117B4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            v1 = 0x43270000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 26032);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x2117ECu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211824
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0021180c
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0021183c
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 26032);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211848u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            lwc1(f0, s0, kSpW);
            cvt_s_w(f1, f0);
            v0 = 0x43270000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            v0 = 0x422C0000;
            sw(v0, sp, 0xC8);
            lwc1(f0, s0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 26288);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x21188Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x002118c4
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002118ac
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x002118dc
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 26288);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x2118E8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 54;
            jal(ctx, 0x2118F8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43560000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 26544);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x21192Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211964
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0021194c
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0021197c
            charge(ctx, 5);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 26544);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211988u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        } else {
            // 0x0021160c
            charge(ctx, 24);
            v0 = 0x43220000;
            sw(v0, sp, 0xE0);
            v0 = 0x42E20000;
            mtc1(v0, f0);
            add_s(f0, f0, f23);
            swc1(f0, sp, 0xE4);
            a0 = addiu(s2, 20064);
            a1 = 4;
            lw(a2, s2, 20048);
            a3 = 1;
            t0 = addiu(sp, 0xE0);
            jal(ctx, 0x21163Cu, gen::fn_sub_238A50_00238a50);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f20);
            if (cond(ctx)) {
                // 0x00211684
                charge(ctx, 6);
                sub_s(f0, f20, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0021166c
                charge(ctx, 6);
                cvt_w_s(f0, f20);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0021169c
            charge(ctx, 4);
            sb(v1, sp, 0xEF);
            s0 = 0;
            for (;;) {  // while (s0 < 4)
                // 0x002116c8
                charge(ctx, 3);
                v0 = slti(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002116ac
                charge(ctx, 7);
                v0 = sll(s0, 8);
                v0 = addu(s2, v0);
                a0 = addiu(v0, 20064);
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x2116BCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s0 = addiu(s0, 1);
            }
            // 0x002116d4
            charge(ctx, 2);
        }
        // 0x00211990
        charge(ctx, 5);
        lw(v0, s2, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x00211a74
            charge(ctx, 35);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            a0 = s1;
            a1 = 50;
            jal(ctx, 0x211A8Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43320000;
            sw(v1, sp, 0xC0);
            v1 = 0x42FC0000;
            mtc1(v1, f0);
            add_s(f26, f0, f23);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 26800);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211AD0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f25, f0, f22);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211b18
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211b00
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211b30
            charge(ctx, 29);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 26800);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211B3Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 52;
            jal(ctx, 0x211B4Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            v1 = 0x43270000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 27056);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211B84u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211bbc
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211ba4
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211bd4
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 27056);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211BE0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            lwc1(f0, s0, kSpW);
            cvt_s_w(f1, f0);
            v0 = 0x43270000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            v0 = 0x422C0000;
            sw(v0, sp, 0xC8);
            lwc1(f0, s0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 27312);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211C24u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211c5c
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211c44
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211c74
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 27312);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211C80u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 54;
            jal(ctx, 0x211C90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43560000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 27568);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x211CC4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00211cfc
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211ce4
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211d14
            charge(ctx, 5);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 27568);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x211D20u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        } else {
            // 0x002119a4
            charge(ctx, 24);
            v0 = 0x43220000;
            sw(v0, sp, 0xE0);
            v0 = 0x43020000;
            mtc1(v0, f0);
            add_s(f0, f0, f23);
            swc1(f0, sp, 0xE4);
            a0 = addiu(s2, 21104);
            a1 = 4;
            lw(a2, s2, 21088);
            a3 = 1;
            t0 = addiu(sp, 0xE0);
            jal(ctx, 0x2119D4u, gen::fn_sub_238A50_00238a50);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f20);
            if (cond(ctx)) {
                // 0x00211a1c
                charge(ctx, 6);
                sub_s(f0, f20, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00211a04
                charge(ctx, 6);
                cvt_w_s(f0, f20);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00211a34
            charge(ctx, 4);
            sb(v1, sp, 0xEF);
            s0 = 0;
            for (;;) {  // while (s0 < 4)
                // 0x00211a60
                charge(ctx, 3);
                v0 = slti(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00211a44
                charge(ctx, 7);
                v0 = sll(s0, 8);
                v0 = addu(s2, v0);
                a0 = addiu(v0, 21104);
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x211A54u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s0 = addiu(s0, 1);
            }
            // 0x00211a6c
            charge(ctx, 2);
        }
        // 0x00211d28
        charge(ctx, 11);
        lw(s0, s2, 16);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f26, f0, f22);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x00211d6c
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00211d54
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00211d84
        charge(ctx, 55);
        v1 = v1 & 0xFF;
        v0 = si(-256);
        s6 = v1 | v0;
        a0 = s0;
        a1 = s6;
        jal(ctx, 0x211D98u, gen::fn_frFontLineSetRgba_003b0e20);
        v0 = 0x429A0000;
        mtc1(v0, f0);
        add_s(f0, f0, f23);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        a0 = s0;
        a1 = 2576;
        jal(ctx, 0x211DC8u, gen::fn_frFontLineSetPos_003b0d70);
        lhu(v1, s2, 12);
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);
        lw(v0, gp, kGpBtlEnemyTbl);  // gBtlEnemyTbl gBtlEnemyTbl
        v0 = addu(v1, v0);
        lbu(a0, v0, 2);
        jal(ctx, 0x211DECu, gen::fn_sub_215830_00215830);  // [bsaMain_GetKindPage](kind) -> page record of panel set 2
        v1 = 0x426C0000;
        sw(v1, sp, 0xC0);
        v1 = 0x429C0000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 5696);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x211E30u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x00211e78
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00211e60
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00211e90
        charge(ctx, 36);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 5696);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x211E9Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s1;
        a1 = 47;
        jal(ctx, 0x211EACu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x43140000;
        sw(v1, sp, 0xC0);
        v1 = 0x42B00000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 5952);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x211EF0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x00211f38
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00211f20
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00211f50
        charge(ctx, 36);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 5952);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x211F5Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s3;
        a1 = 71;
        jal(ctx, 0x211F6Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x426C0000;
        sw(v1, sp, 0xC0);
        v1 = 0x42DE0000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 320);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x211FB0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x00211ff8
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00211fe0
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212010
        charge(ctx, 36);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 320);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x21201Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s1;
        a1 = 48;
        jal(ctx, 0x21202Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x43120000;
        sw(v1, sp, 0xC0);
        v1 = 0x42E00000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 576);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x212070u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x002120b8
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002120a0
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002120d0
        charge(ctx, 36);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 576);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x2120DCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s3;
        a1 = 72;
        jal(ctx, 0x2120ECu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x426C0000;
        sw(v1, sp, 0xC0);
        v1 = 0x43000000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 832);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x212130u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x00212178
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00212160
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212190
        charge(ctx, 36);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 832);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x21219Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s1;
        a1 = 48;
        jal(ctx, 0x2121ACu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x43120000;
        sw(v1, sp, 0xC0);
        v1 = 0x43010000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 1088);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x2121F0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x00212238
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00212220
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212250
        charge(ctx, 37);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 1088);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x21225Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s1;
        a1 = 33;
        jal(ctx, 0x21226Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        v1 = 0x42380000;
        sw(v1, sp, 0xC0);
        v1 = 0x430D0000;
        mtc1(v1, f0);
        add_s(f25, f0, f23);
        swc1(f25, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 1344);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x2122B4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x002122fc
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002122e4
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212314
        charge(ctx, 31);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 1344);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x212320u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 0x42380000;
        sw(v0, sp, 0xC0);
        v0 = 0x42540000;
        mtc1(v0, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        v0 = 0x42B00000;
        sw(v0, sp, 0xCC);
        a0 = addiu(s2, 1600);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x212360u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x002123a8
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00212390
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002123c0
        charge(ctx, 33);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 1600);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x2123CCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s1;
        a1 = 36;
        jal(ctx, 0x2123DCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        v1 = 0x42680000;
        sw(v1, sp, 0xC0);
        swc1(f25, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 1856);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x212414u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x0021245c
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00212444
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212474
        charge(ctx, 32);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 1856);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x212480u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        lwc1(f0, s0, kSpW);
        cvt_s_w(f1, f0);
        v0 = 0x42680000;
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0xC0);
        swc1(f25, sp, 0xC4);
        v0 = 0x439F0000;
        sw(v0, sp, 0xC8);
        lwc1(f0, s0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 2112);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x2124C4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x0021250c
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002124f4
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212524
        charge(ctx, 37);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 2112);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x212530u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s1;
        a1 = 34;
        jal(ctx, 0x212540u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        v1 = 0x42380000;
        sw(v1, sp, 0xC0);
        v1 = 0x434B0000;
        mtc1(v1, f0);
        add_s(f25, f0, f23);
        swc1(f25, sp, 0xC4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xCC);
        a0 = addiu(s2, 2368);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x212588u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x002125d0
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002125b8
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002125e8
        charge(ctx, 31);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 2368);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x2125F4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 0x42380000;
        sw(v0, sp, 0xC0);
        v0 = 0x431E0000;
        mtc1(v0, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0xC4);
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC8);
        v0 = 0x42340000;
        sw(v0, sp, 0xCC);
        a0 = addiu(s2, 2624);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x212634u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xEC);
        sb(v0, sp, 0xED);
        sb(v0, sp, 0xEE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f26);
        if (cond(ctx)) {
            // 0x0021267c
            charge(ctx, 6);
            sub_s(f0, f26, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00212664
            charge(ctx, 6);
            cvt_w_s(f0, f26);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00212694
        charge(ctx, 8);
        sb(v1, sp, 0xEF);
        a0 = addiu(s2, 2624);
        a1 = addiu(sp, 0xEC);
        jal(ctx, 0x2126A0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = 0;
        for (;;) {  // while (s0 < 9)
            // 0x0021279c
            charge(ctx, 3);
            v0 = slti(s0, 9);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002126b4
            charge(ctx, 40);
            a0 = s1;
            a1 = 38;
            jal(ctx, 0x2126BCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42140000;
            mtc1(v1, f3);
            mtc1(s0, f0);
            cvt_s_w(f2, f0);
            v1 = 0x42540000;
            mtc1(v1, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f3, f2);
            swc1(f0, sp, 0xC0);
            swc1(f25, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            v0 = sll(s0, 8);
            v0 = addu(s2, v0);
            s3 = addiu(v0, 2880);
            a0 = s3;
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212724u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f26);
            if (cond(ctx)) {
                // 0x0021276c
                charge(ctx, 6);
                sub_s(f0, f26, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212754
                charge(ctx, 6);
                cvt_w_s(f0, f26);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212784
            charge(ctx, 6);
            sb(v1, sp, 0xEF);
            a0 = s3;
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212790u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            s0 = addiu(s0, 1);
        }
        // 0x002127a8
        charge(ctx, 7);
        s0 = 0;
        v0 = 0x43260000;
        mtc1(v0, f0);
        add_s(f25, f0, f23);
        for (;;) {  // while (s0 < 9)
            // 0x002128ac
            charge(ctx, 3);
            v0 = slti(s0, 9);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002127c4
            charge(ctx, 40);
            a1 = addiu(s0, 22);
            a0 = s1;
            jal(ctx, 0x2127CCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42140000;
            mtc1(v1, f3);
            mtc1(s0, f0);
            cvt_s_w(f2, f0);
            v1 = 0x42540000;
            mtc1(v1, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f3, f2);
            swc1(f0, sp, 0xC0);
            swc1(f25, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            v0 = sll(s0, 8);
            v0 = addu(s2, v0);
            s3 = addiu(v0, 6208);
            a0 = s3;
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212834u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f20);
            if (cond(ctx)) {
                // 0x0021287c
                charge(ctx, 6);
                sub_s(f0, f20, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212864
                charge(ctx, 6);
                cvt_w_s(f0, f20);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212894
            charge(ctx, 6);
            sb(v1, sp, 0xEF);
            a0 = s3;
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x2128A0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            s0 = addiu(s0, 1);
        }
        // 0x002128b8
        charge(ctx, 5);
        lw(v0, s2, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            // 0x002129fc
            charge(ctx, 35);
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            a0 = s1;
            a1 = 50;
            jal(ctx, 0x212A14u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43320000;
            sw(v1, sp, 0xC0);
            v1 = 0x432B0000;
            mtc1(v1, f0);
            add_s(f26, f0, f23);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 27824);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212A58u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f25, f0, f22);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00212aa0
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212a88
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212ab8
            charge(ctx, 29);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 27824);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212AC4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 53;
            jal(ctx, 0x212AD4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            v1 = 0x43090000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 28080);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212B0Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00212b44
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212b2c
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212b5c
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 28080);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212B68u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            lwc1(f0, s0, kSpW);
            cvt_s_w(f1, f0);
            v0 = 0x43090000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            v0 = 0x42CE0000;
            sw(v0, sp, 0xC8);
            lwc1(f0, s0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 28336);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212BACu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00212be4
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212bcc
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212bfc
            charge(ctx, 28);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 28336);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212C08u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 54;
            jal(ctx, 0x212C18u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43740000;
            sw(v1, sp, 0xC0);
            swc1(f26, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 28592);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212C4Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f25);
            if (cond(ctx)) {
                // 0x00212c84
                charge(ctx, 6);
                sub_s(f0, f25, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212c6c
                charge(ctx, 6);
                cvt_w_s(f0, f25);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212c9c
            charge(ctx, 5);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 28592);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212CA8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        } else {
            // 0x002128cc
            charge(ctx, 7);
            s0 = 0;
            v0 = 0x433E0000;
            mtc1(v0, f0);
            add_s(f25, f0, f23);
            for (;;) {  // while (s0 < 9)
                // 0x002129e8
                charge(ctx, 3);
                v0 = slti(s0, 9);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002128e8
                charge(ctx, 6);
                v0 = sll(s0, 2);
                v0 = addu(s2, v0);
                lw(v1, v0, 22128);
                v0 = 5;
                if (v1 != v0) {
                    // 0x00212900
                    charge(ctx, 40);
                    a1 = addiu(v1, 41);
                    a0 = s1;
                    jal(ctx, 0x212908u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    v1 = 0x42140000;
                    mtc1(v1, f3);
                    mtc1(s0, f0);
                    cvt_s_w(f2, f0);
                    v1 = 0x42540000;
                    mtc1(v1, f1);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f0, f3, f2);
                    swc1(f0, sp, 0xC0);
                    swc1(f25, sp, 0xC4);
                    lwc1(f0, v0, kSpW);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xC8);
                    lwc1(f0, v0, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xCC);
                    v0 = sll(s0, 8);
                    v0 = addu(s2, v0);
                    s3 = addiu(v0, 22176);
                    a0 = s3;
                    a1 = addiu(sp, 0xC0);
                    jal(ctx, 0x212970u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 255;
                    sb(v0, sp, 0xEC);
                    sb(v0, sp, 0xED);
                    sb(v0, sp, 0xEE);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f20);
                    if (cond(ctx)) {
                        // 0x002129b8
                        charge(ctx, 6);
                        sub_s(f0, f20, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x002129a0
                        charge(ctx, 6);
                        cvt_w_s(f0, f20);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x002129d0
                    charge(ctx, 5);
                    sb(v1, sp, 0xEF);
                    a0 = s3;
                    a1 = addiu(sp, 0xEC);
                    jal(ctx, 0x2129DCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                }
                // 0x002129e4
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x002129f4
            charge(ctx, 2);
        }
        // 0x00212cb0
        charge(ctx, 4);
        lw(v0, s2, 0);
        v1 = 1;
        if (v0 == v1) {
            // 0x00212cd0
            charge(ctx, 5);
            lw(v0, s2, 4);
            v0 = nor(v0, 0);
            v0 = v0 & 0x40;
            if (v0 == 0) {
                // 0x00212cf8
                charge(ctx, 5);
                v0 = 0x10000;
                v0 = addu(s2, v0);
                lw(v0, v0, -22860);
                if (v0 == v1) {
                    // 0x00212dac
                    charge(ctx, 13);
                    v0 = 0x10000;
                    v0 = addu(s2, v0);
                    lwc1(f0, v0, -22864);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f21, f0, f1);
                    mtc1(zero, f24);
                } else {
                    // 0x00212d0c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00212d1c
                        charge(ctx, 6);
                        v0 = 0x10000;
                        v0 = addu(s2, v0);
                        lw(v0, v0, -22864);
                        at = slti(v0, 2);
                        if (at == 0) {
                            // 0x00212d48
                            charge(ctx, 3);
                            at = slti(v0, 6);
                            if (at == 0) {
                                // 0x00212d98
                                charge(ctx, 5);
                                v0 = 0x3F800000;
                                mtc1(v0, f21);
                                mtc1(zero, f24);
                            } else {
                                // 0x00212d54
                                charge(ctx, 17);
                                v0 = addiu(v0, -2);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                v0 = 0x40800000;
                                mtc1(v0, f0);
                                div_s(f21, f1, f0);
                                v0 = lui(0xC1A0);
                                mtc1(v0, f1);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                sub_s(f0, f0, f21);
                                mul_s(f24, f1, f0);
                            }
                        } else {
                            // 0x00212d34
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            mov_s(f24, f21);
                        }
                    } else {
                        // 0x00212d14
                        charge(ctx, 2);
                    }
                }
            } else {
                // 0x00212ce4
                charge(ctx, 5);
                mtc1(zero, f24);
                v0 = 0x3F800000;
                mtc1(v0, f21);
            }
            // 0x00212de0
            charge(ctx, 35);
            a0 = s1;
            a1 = 39;
            jal(ctx, 0x212DE8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x41900000;
            sw(v1, sp, 0xC0);
            v1 = 0x43890000;
            mtc1(v1, f0);
            add_s(f0, f0, f24);
            swc1(f0, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 5440);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212E2Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f21);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00212e84
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212e6c
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212e9c
            charge(ctx, 37);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 5440);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212EA8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 32;
            jal(ctx, 0x212EB8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42380000;
            sw(v1, sp, 0xC0);
            v1 = 0x43630000;
            sw(v1, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 19264);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212EF0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f21, f0, f22);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f21);
            if (cond(ctx)) {
                // 0x00212f48
                charge(ctx, 6);
                sub_s(f0, f21, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212f30
                charge(ctx, 6);
                cvt_w_s(f0, f21);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00212f60
            charge(ctx, 33);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 19264);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x212F6Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s1;
            a1 = 49;
            jal(ctx, 0x212F7Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42A40000;
            sw(v1, sp, 0xC0);
            v1 = 0x43630000;
            sw(v1, sp, 0xC4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 18752);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x212FB4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0xEC);
            sb(v0, sp, 0xED);
            sb(v0, sp, 0xEE);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f21);
            if (cond(ctx)) {
                // 0x00212ffc
                charge(ctx, 6);
                sub_s(f0, f21, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00212fe4
                charge(ctx, 6);
                cvt_w_s(f0, f21);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00213014
            charge(ctx, 9);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 18752);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x213020u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            lw(v0, s2, 4);
            v0 = v0 & 0x80;
            if (v0 == 0) {
                // 0x00213038
                charge(ctx, 4);
                lw(v1, s2, 24480);
                v0 = 7;
                if (v1 == v0) {
                    goto L_00213048;
                }
                // 0x00213060
                charge(ctx, 4);
                a1 = addiu(v1, 22);
                a0 = s1;
                jal(ctx, 0x213068u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                goto L_00213070;
            }
        L_00213048:
            charge(ctx, 6);
            a0 = s1;
            a1 = 60;
            jal(ctx, 0x213050u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        L_00213070:
            charge(ctx, 27);
            v1 = 0x42480000;
            sw(v1, sp, 0xC0);
            v1 = 0x43690000;
            sw(v1, sp, 0xC4);
            lwc1(f0, v0, 12);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC8);
            lwc1(f0, v0, 16);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xCC);
            a0 = addiu(s2, 24496);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x2130A0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            sb(zero, sp, 0xEC);
            sb(zero, sp, 0xED);
            sb(zero, sp, 0xEE);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f26, f0, f22);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f26);
            if (cond(ctx)) {
                // 0x002130f4
                charge(ctx, 6);
                sub_s(f0, f26, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002130dc
                charge(ctx, 6);
                cvt_w_s(f0, f26);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0021310c
            charge(ctx, 8);
            sb(v1, sp, 0xEF);
            a0 = addiu(s2, 24496);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x213118u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            s0 = 0;
            for (;;) {  // while (s0 < 8)
                // 0x002138f4
                charge(ctx, 3);
                v0 = slti(s0, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0021312c
                charge(ctx, 3);
                v0 = sra(s0, 2);
                if (i64(s0) < 0) {
                    // 0x00213138
                    charge(ctx, 2);
                    v0 = addiu(s0, 3);
                    v0 = sra(v0, 2);
                }
                // 0x00213140
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x00213154
                    charge(ctx, 2);
                    v0 = 0x43870000;
                    mtc1(v0, f27);
                } else {
                    // 0x00213148
                    charge(ctx, 3);
                    mtc1(zero, f27);
                }
                // 0x0021315c
                charge(ctx, 46);
                v0 = s0 & 0x3;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41F00000;
                mtc1(v0, f0);
                mul_s(f24, f0, f1);
                a0 = s1;
                a1 = 35;
                jal(ctx, 0x213184u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s5 = v0;
                v1 = 0x42380000;
                mtc1(v1, f0);
                add_s(f21, f0, f27);
                swc1(f21, sp, 0xC0);
                v1 = 0x43920000;
                mtc1(v1, f0);
                add_s(f25, f0, f24);
                swc1(f25, sp, 0xC4);
                lwc1(f0, v0, kSpW);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xC8);
                lwc1(f0, v0, kSpH);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xCC);
                v0 = sll(s0, 9);
                s4 = addu(s2, v0);
                s3 = addiu(s4, 8512);
                a0 = s3;
                a1 = addiu(sp, 0xC0);
                jal(ctx, 0x2131E4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                v0 = 255;
                sb(v0, sp, 0xEC);
                sb(v0, sp, 0xED);
                sb(v0, sp, 0xEE);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f26);
                if (cond(ctx)) {
                    // 0x0021322c
                    charge(ctx, 6);
                    sub_s(f0, f26, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00213214
                    charge(ctx, 6);
                    cvt_w_s(f0, f26);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00213244
                charge(ctx, 30);
                sb(v1, sp, 0xEF);
                a0 = s3;
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x213250u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                swc1(f21, sp, 0xC0);
                v0 = 0x41880000;
                mtc1(v0, f0);
                sub_s(f0, f25, f0);
                swc1(f0, sp, 0xC4);
                lwc1(f0, s5, kSpW);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xC8);
                sw(v0, sp, 0xCC);
                s3 = addiu(s4, 8768);
                a0 = s3;
                a1 = addiu(sp, 0xC0);
                jal(ctx, 0x21328Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                v0 = 255;
                sb(v0, sp, 0xEC);
                sb(v0, sp, 0xED);
                sb(v0, sp, 0xEE);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f26);
                if (cond(ctx)) {
                    // 0x002132d4
                    charge(ctx, 6);
                    sub_s(f0, f26, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002132bc
                    charge(ctx, 6);
                    cvt_w_s(f0, f26);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002132ec
                charge(ctx, 37);
                sb(v1, sp, 0xEF);
                a0 = s3;
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x2132F8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                a0 = s1;
                a1 = 37;
                jal(ctx, 0x213308u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s3 = v0;
                v1 = 0x42680000;
                mtc1(v1, f0);
                add_s(f21, f0, f27);
                swc1(f21, sp, 0xC0);
                swc1(f25, sp, 0xC4);
                lwc1(f0, v0, kSpW);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xC8);
                lwc1(f0, v0, kSpH);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xCC);
                s5 = addiu(s4, 12608);
                a0 = s5;
                a1 = addiu(sp, 0xC0);
                jal(ctx, 0x213350u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                v0 = 255;
                sb(v0, sp, 0xEC);
                sb(v0, sp, 0xED);
                sb(v0, sp, 0xEE);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f26);
                if (cond(ctx)) {
                    // 0x00213398
                    charge(ctx, 6);
                    sub_s(f0, f26, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00213380
                    charge(ctx, 6);
                    cvt_w_s(f0, f26);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002133b0
                charge(ctx, 30);
                sb(v1, sp, 0xEF);
                a0 = s5;
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x2133BCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                lwc1(f0, s3, kSpW);
                cvt_s_w(f0, f0);
                add_s(f0, f21, f0);
                swc1(f0, sp, 0xC0);
                swc1(f25, sp, 0xC4);
                v0 = 0x436C0000;
                sw(v0, sp, 0xC8);
                lwc1(f0, s3, kSpH);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xCC);
                s3 = addiu(s4, 12864);
                a0 = s3;
                a1 = addiu(sp, 0xC0);
                jal(ctx, 0x2133F8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                v0 = 255;
                sb(v0, sp, 0xEC);
                sb(v0, sp, 0xED);
                sb(v0, sp, 0xEE);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f26);
                if (cond(ctx)) {
                    // 0x00213440
                    charge(ctx, 6);
                    sub_s(f0, f26, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00213428
                    charge(ctx, 6);
                    cvt_w_s(f0, f26);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00213458
                charge(ctx, 9);
                sb(v1, sp, 0xEF);
                a0 = s3;
                a1 = addiu(sp, 0xEC);
                jal(ctx, 0x213464u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                lw(v0, s2, 52);
                at = slt(s0, v0);
                if (at != 0) {
                    // 0x0021347c
                    charge(ctx, 44);
                    v0 = sll(s0, 1);
                    v1 = addu(s2, v0);
                    v0 = 0x10000;
                    v0 = addu(v1, v0);
                    lh(a1, v0, -22856);
                    a0 = s7;
                    jal(ctx, 0x213494u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    v1 = 0x42580000;
                    mtc1(v1, f0);
                    add_s(f0, f0, f27);
                    swc1(f0, sp, 0xC0);
                    v1 = 271;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f24);
                    swc1(f0, sp, 0xC4);
                    lwc1(f0, v0, kSpW);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xC8);
                    lwc1(f0, v0, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xCC);
                    v0 = sll(s0, 8);
                    v0 = addu(s2, v0);
                    s3 = addiu(v0, 16704);
                    a0 = s3;
                    a1 = addiu(sp, 0xC0);
                    jal(ctx, 0x2134F4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 169;
                    sb(v0, sp, 0xEC);
                    v0 = 181;
                    sb(v0, sp, 0xED);
                    v0 = 197;
                    sb(v0, sp, 0xEE);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f26);
                    if (cond(ctx)) {
                        // 0x00213544
                        charge(ctx, 6);
                        sub_s(f0, f26, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x0021352c
                        charge(ctx, 6);
                        cvt_w_s(f0, f26);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x0021355c
                    charge(ctx, 5);
                    sb(v1, sp, 0xEF);
                    a0 = s3;
                    a1 = addiu(sp, 0xEC);
                    jal(ctx, 0x213568u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                }
                // 0x00213570
                charge(ctx, 5);
                lw(v0, s2, 4);
                v0 = nor(v0, 0);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x0021360c
                    charge(ctx, 37);
                    v0 = 255;
                    sb(v0, sp, 0xEC);
                    sb(v0, sp, 0xED);
                    sb(v0, sp, 0xEE);
                    a0 = s1;
                    a1 = 50;
                    jal(ctx, 0x213624u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    v1 = 0x430E0000;
                    mtc1(v1, f0);
                    add_s(f0, f0, f27);
                    swc1(f0, sp, 0xC0);
                    v1 = 0x438B0000;
                    mtc1(v1, f0);
                    add_s(f21, f0, f24);
                    swc1(f21, sp, 0xC4);
                    lwc1(f0, v0, kSpW);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xC8);
                    lwc1(f0, v0, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xCC);
                    v0 = sll(s0, 10);
                    s4 = addu(s2, v0);
                    s3 = addiu(s4, 28848);
                    a0 = s3;
                    a1 = addiu(sp, 0xC0);
                    jal(ctx, 0x213680u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f26);
                    if (cond(ctx)) {
                        // 0x002136b8
                        charge(ctx, 6);
                        sub_s(f0, f26, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x002136a0
                        charge(ctx, 6);
                        cvt_w_s(f0, f26);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x002136d0
                    charge(ctx, 33);
                    sb(v1, sp, 0xEF);
                    a0 = s3;
                    a1 = addiu(sp, 0xEC);
                    jal(ctx, 0x2136DCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                    a0 = s1;
                    a1 = 53;
                    jal(ctx, 0x2136ECu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s3 = v0;
                    v1 = 0x42CA0000;
                    mtc1(v1, f0);
                    add_s(f0, f0, f27);
                    swc1(f0, sp, 0xC0);
                    swc1(f21, sp, 0xC4);
                    lwc1(f0, v0, kSpW);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xC8);
                    lwc1(f0, v0, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xCC);
                    s5 = addiu(s4, 29104);
                    a0 = s5;
                    a1 = addiu(sp, 0xC0);
                    jal(ctx, 0x213734u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f26);
                    if (cond(ctx)) {
                        // 0x0021376c
                        charge(ctx, 6);
                        sub_s(f0, f26, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x00213754
                        charge(ctx, 6);
                        cvt_w_s(f0, f26);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x00213784
                    charge(ctx, 30);
                    sb(v1, sp, 0xEF);
                    a0 = s5;
                    a1 = addiu(sp, 0xEC);
                    jal(ctx, 0x213790u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                    lwc1(f0, s3, kSpW);
                    cvt_s_w(f1, f0);
                    v0 = 0x42CA0000;
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    add_s(f0, f0, f27);
                    swc1(f0, sp, 0xC0);
                    swc1(f21, sp, 0xC4);
                    v0 = 0x42CE0000;
                    sw(v0, sp, 0xC8);
                    lwc1(f0, s3, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xCC);
                    s3 = addiu(s4, 29360);
                    a0 = s3;
                    a1 = addiu(sp, 0xC0);
                    jal(ctx, 0x2137DCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f26);
                    if (cond(ctx)) {
                        // 0x00213814
                        charge(ctx, 6);
                        sub_s(f0, f26, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x002137fc
                        charge(ctx, 6);
                        cvt_w_s(f0, f26);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x0021382c
                    charge(ctx, 32);
                    sb(v1, sp, 0xEF);
                    a0 = s3;
                    a1 = addiu(sp, 0xEC);
                    jal(ctx, 0x213838u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                    a0 = s1;
                    a1 = 54;
                    jal(ctx, 0x213848u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    v1 = 0x43500000;
                    mtc1(v1, f0);
                    add_s(f0, f0, f27);
                    swc1(f0, sp, 0xC0);
                    swc1(f21, sp, 0xC4);
                    lwc1(f0, v0, kSpW);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xC8);
                    lwc1(f0, v0, kSpH);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0xCC);
                    s3 = addiu(s4, 29616);
                    a0 = s3;
                    a1 = addiu(sp, 0xC0);
                    jal(ctx, 0x21388Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f26);
                    if (cond(ctx)) {
                        // 0x002138c4
                        charge(ctx, 6);
                        sub_s(f0, f26, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x002138ac
                        charge(ctx, 6);
                        cvt_w_s(f0, f26);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x002138dc
                    charge(ctx, 5);
                    sb(v1, sp, 0xEF);
                    a0 = s3;
                    a1 = addiu(sp, 0xEC);
                    jal(ctx, 0x2138E8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                } else {
                    // 0x00213584
                    charge(ctx, 4);
                    lw(v0, s2, 52);
                    at = slt(s0, v0);
                    if (at != 0) {
                        // 0x00213594
                        charge(ctx, 30);
                        v0 = sll(s0, 2);
                        v0 = addu(s2, v0);
                        lw(s3, v0, 20);
                        v0 = 0x41800000;
                        mtc1(v0, f1);
                        v0 = 0x42B20000;
                        mtc1(v0, f0);
                        add_s(f0, f0, f27);
                        mul_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = 0x41000000;
                        mtc1(v0, f1);
                        v0 = 0x43890000;
                        mtc1(v0, f0);
                        add_s(f0, f0, f24);
                        mul_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a2, f0);
                        a0 = s3;
                        jal(ctx, 0x2135ECu, gen::fn_frFontLineSetPos_003b0d70);
                        a0 = s3;
                        a1 = s6;
                        jal(ctx, 0x2135FCu, gen::fn_frFontLineSetRgba_003b0e20);
                    }
                }
                // 0x002138f0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
        } else {
            // 0x00212cc0
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00212cc8
                charge(ctx, 2);
            }
        }
        // 0x00213900
        charge(ctx, 4);
        lw(v1, s2, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x00213948
            charge(ctx, 8);
            v0 = lui(0xBF80);
            sw(v0, sp, 0xC0);
            v0 = 0x421C0000;
            sw(v0, sp, 0xC4);
            v0 = 0x424C0000;
            sw(v0, sp, 0xC8);
            v0 = 0x43B90000;
            sw(v0, sp, 0xCC);
        } else {
            // 0x00213910
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00213920
                charge(ctx, 10);
                v0 = lui(0xBF80);
                sw(v0, sp, 0xC0);
                v0 = 0x435B0000;
                sw(v0, sp, 0xC4);
                v0 = 0x424C0000;
                sw(v0, sp, 0xC8);
                v0 = 0x433E0000;
                sw(v0, sp, 0xCC);
            } else {
                // 0x00213918
                charge(ctx, 2);
            }
        }
        // 0x00213968
        charge(ctx, 9);
        at = 0x90B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x213974u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lw(v1, s2, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x002139c4
            charge(ctx, 8);
            v0 = 0x42480000;
            sw(v0, sp, 0xC0);
            v0 = 0x421C0000;
            sw(v0, sp, 0xC4);
            v0 = 0x43FA0000;
            sw(v0, sp, 0xC8);
            v0 = 0x43B90000;
            sw(v0, sp, 0xCC);
        } else {
            // 0x0021398c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0021399c
                charge(ctx, 10);
                v0 = 0x42480000;
                sw(v0, sp, 0xC0);
                v0 = 0x435B0000;
                sw(v0, sp, 0xC4);
                v0 = 0x43FA0000;
                sw(v0, sp, 0xC8);
                v0 = 0x433E0000;
                sw(v0, sp, 0xCC);
            } else {
                // 0x00213994
                charge(ctx, 2);
            }
        }
        // 0x002139e4
        charge(ctx, 70);
        at = 0x91B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x2139F0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 0x42540000;
        sw(v0, sp, 0xC0);
        v0 = 0x42580000;
        mtc1(v0, f0);
        add_s(f21, f0, f23);
        swc1(f21, sp, 0xC4);
        v0 = 0x435C0000;
        sw(v0, sp, 0xC8);
        v0 = 0x42C20000;
        sw(v0, sp, 0xCC);
        at = 0x92B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x213A30u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 273;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC0);
        swc1(f21, sp, 0xC4);
        v0 = 0x42F00000;
        sw(v0, sp, 0xC8);
        v0 = 0x42C20000;
        sw(v0, sp, 0xCC);
        at = 0x93B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x213A6Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 0x42540000;
        sw(v0, sp, 0xC0);
        v0 = 0x431E0000;
        mtc1(v0, f0);
        add_s(f21, f0, f23);
        swc1(f21, sp, 0xC4);
        v0 = 0x435C0000;
        sw(v0, sp, 0xC8);
        v0 = 0x42580000;
        sw(v0, sp, 0xCC);
        at = 0x94B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x213AACu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 273;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC0);
        swc1(f21, sp, 0xC4);
        v0 = 0x43020000;
        sw(v0, sp, 0xC8);
        v0 = 0x42580000;
        sw(v0, sp, 0xCC);
        at = 0x95B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x213AE8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s0 = 0;
        for (;;) {  // while (s0 < 8)
            // 0x00213be4
            charge(ctx, 3);
            v0 = slti(s0, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00213afc
            charge(ctx, 3);
            v0 = sra(s0, 2);
            if (i64(s0) < 0) {
                // 0x00213b08
                charge(ctx, 2);
                v0 = addiu(s0, 3);
                v0 = sra(v0, 2);
            }
            // 0x00213b10
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00213b24
                charge(ctx, 2);
                v0 = 0x43870000;
                mtc1(v0, f21);
            } else {
                // 0x00213b18
                charge(ctx, 3);
                mtc1(zero, f21);
            }
            // 0x00213b2c
            charge(ctx, 46);
            v0 = s0 & 0x3;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x42540000;
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xC0);
            v0 = 275;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f23, f0, f1);
            swc1(f23, sp, 0xC4);
            v0 = 0x42EC0000;
            sw(v0, sp, 0xC8);
            v0 = 0x41D00000;
            sw(v0, sp, 0xCC);
            v0 = sll(s0, 9);
            s1 = addu(s2, v0);
            at = 0x96B0;
            a0 = addu(s1, at);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x213B9Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x432B0000;
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xC0);
            swc1(f23, sp, 0xC4);
            v0 = 0x43480000;
            sw(v0, sp, 0xC8);
            v0 = 0x41D00000;
            sw(v0, sp, 0xCC);
            at = 0x97B0;
            a0 = addu(s1, at);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x213BD8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            s0 = addiu(s0, 1);
        }
        // 0x00213bf0
        charge(ctx, 10);
        v0 = 30;
        sb(v0, sp, 0xE8);
        sb(v0, sp, 0xE9);
        sb(v0, sp, 0xEA);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x00213c30
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00213c18
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00213c48
        charge(ctx, 47);
        sb(v1, sp, 0xEB);
        lbu(a1, sp, 0xE8);
        sb(a1, sp, 0xB0);
        lbu(a0, sp, 0xE9);
        sb(a0, sp, 0xB1);
        lbu(v1, sp, 0xEA);
        sb(v1, sp, 0xB2);
        lbu(v0, sp, 0xEB);
        sb(v0, sp, 0xB3);
        sb(a1, sp, 0xB4);
        sb(a0, sp, 0xB5);
        sb(v1, sp, 0xB6);
        sb(zero, sp, 0xB7);
        sb(a1, sp, 0xB8);
        sb(a0, sp, 0xB9);
        sb(v1, sp, 0xBA);
        sb(zero, sp, 0xBB);
        sb(a1, sp, 0xBC);
        sb(a0, sp, 0xBD);
        sb(v1, sp, 0xBE);
        sb(v0, sp, 0xBF);
        at = 0x90B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xE8);
        jal(ctx, 0x213CA8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        at = 0x91B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xB0);
        jal(ctx, 0x213CBCu, gen::fn_sub_21DD60_0021dd60);  // (quad, ...)
        v0 = 34;
        sb(v0, sp, 0xE8);
        v0 = 33;
        sb(v0, sp, 0xE9);
        v0 = 31;
        sb(v0, sp, 0xEA);
        v0 = 0x434C0000;
        mtc1(v0, f0);
        mul_s(f1, f0, f22);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x00213d1c
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00213d04
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00213d34
        charge(ctx, 44);
        sb(v1, sp, 0xEB);
        lbu(a1, sp, 0xE8);
        sb(a1, sp, 0xB0);
        lbu(a0, sp, 0xE9);
        sb(a0, sp, 0xB1);
        lbu(v1, sp, 0xEA);
        sb(v1, sp, 0xB2);
        lbu(v0, sp, 0xEB);
        sb(v0, sp, 0xB3);
        sb(a1, sp, 0xB4);
        sb(a0, sp, 0xB5);
        sb(v1, sp, 0xB6);
        sb(zero, sp, 0xB7);
        sb(a1, sp, 0xB8);
        sb(a0, sp, 0xB9);
        sb(v1, sp, 0xBA);
        sb(zero, sp, 0xBB);
        sb(a1, sp, 0xBC);
        sb(a0, sp, 0xBD);
        sb(v1, sp, 0xBE);
        sb(v0, sp, 0xBF);
        at = 0x92B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xE8);
        jal(ctx, 0x213D94u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        at = 0x93B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xB0);
        jal(ctx, 0x213DA8u, gen::fn_sub_21DD60_0021dd60);  // (quad, ...)
        at = 0x94B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xE8);
        jal(ctx, 0x213DBCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        at = 0x95B0;
        a0 = addu(s2, at);
        a1 = addiu(sp, 0xB0);
        jal(ctx, 0x213DD0u, gen::fn_sub_21DD60_0021dd60);  // (quad, ...)
        s1 = 0;
        for (;;) {  // while (s1 < 8)
            // 0x00213e18
            charge(ctx, 3);
            v1 = slti(s1, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00213de4
            charge(ctx, 13);
            v0 = sll(s1, 9);
            s0 = addu(s2, v0);
            at = 0x96B0;
            a0 = addu(s0, at);
            a1 = addiu(sp, 0xE8);
            jal(ctx, 0x213DF8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            at = 0x97B0;
            a0 = addu(s0, at);
            a1 = addiu(sp, 0xB0);
            jal(ctx, 0x213E0Cu, gen::fn_sub_21DD60_0021dd60);  // (quad, ...)
            s1 = addiu(s1, 1);
        }
    }
    // 0x00213e24 (the shared epilogue, written out on this path)
    charge(ctx, 20);
    ld(ra, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x00213E80 sub_213E80 -- 6384 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bsaPanel_Draw](panel) draws the analysis panel the layout above built: render states (RwRenderStateSet,
// RpSkyRenderStateSet), the quads as two Im2D triangles each through the RwIm2DRenderTriangle slot, the font chains
// (frFontDraw), the rows' kind pages (sub_215830).
void sub_213E80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00213e80
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    a0 = 6;
    jal(ctx, 0x213EB4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    fp = v0;
    a0 = 1;
    jal(ctx, 0x213EC4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s7 = v0;
    a0 = 2;
    jal(ctx, 0x213ED4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s3 = v0;
    lw(v1, s4, 4);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00213ef4
        charge(ctx, 145);
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = 1;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x213F08u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x213F1Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x213F2Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 8;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x213F40u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x213F54u, v0.u());
        a0 = 1;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x213F68u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        at = 0x90B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x213F94u, v0.u());
        at = 0x90B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x213FB8u, v0.u());
        at = 0x91B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x213FDCu, v0.u());
        at = 0x91B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x214000u, v0.u());
        at = 0x92B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x214024u, v0.u());
        at = 0x92B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x214048u, v0.u());
        at = 0x93B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21406Cu, v0.u());
        at = 0x93B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x214090u, v0.u());
        at = 0x94B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2140B4u, v0.u());
        at = 0x94B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2140D8u, v0.u());
        at = 0x95B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2140FCu, v0.u());
        at = 0x95B0;
        a0 = addu(s4, at);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x214120u, v0.u());
        lw(v1, s4, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x00214148
            charge(ctx, 3);
            s2 = 0;
            for (;;) {  // while (s2 < 8)
                // 0x002141f8
                charge(ctx, 3);
                v0 = slti(s2, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00214154
                charge(ctx, 41);
                v0 = sll(s2, 9);
                s6 = addu(s4, v0);
                at = 0x96B0;
                s5 = addu(s6, at);
                s0 = 0x960000;
                s0 = addiu(s0, 156);  // &0x96009C
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214184u, v0.u());
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2141A4u, v0.u());
                at = 0x97B0;
                s5 = addu(s6, at);
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2141CCu, v0.u());
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2141ECu, v0.u());
                s2 = addiu(s2, 1);
            }
        } else {
            // 0x00214138
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00214140
                charge(ctx, 2);
            }
        }
        // 0x00214204
        charge(ctx, 319);
        a0 = s3;
        a1 = 31;
        jal(ctx, 0x21420Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s2 = 0x960000;
        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x214220u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x214234u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s4, 64);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21425Cu, v0.u());
        a0 = addiu(s4, 64);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21427Cu, v0.u());
        a0 = s3;
        a1 = 40;
        jal(ctx, 0x21428Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x214298u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2142ACu, v0.u());
        a0 = addiu(s4, 5184);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2142CCu, v0.u());
        a0 = addiu(s4, 5184);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2142ECu, v0.u());
        a0 = s7;
        a1 = 71;
        jal(ctx, 0x2142FCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x214308u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x21431Cu, v0.u());
        a0 = addiu(s4, 320);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21433Cu, v0.u());
        a0 = addiu(s4, 320);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21435Cu, v0.u());
        a0 = s3;
        a1 = 48;
        jal(ctx, 0x21436Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x214378u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x21438Cu, v0.u());
        a0 = addiu(s4, 576);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2143ACu, v0.u());
        a0 = addiu(s4, 576);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2143CCu, v0.u());
        a0 = s7;
        a1 = 72;
        jal(ctx, 0x2143DCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2143E8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2143FCu, v0.u());
        a0 = addiu(s4, 832);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21441Cu, v0.u());
        a0 = addiu(s4, 832);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21443Cu, v0.u());
        a0 = s3;
        a1 = 48;
        jal(ctx, 0x21444Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x214458u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x21446Cu, v0.u());
        a0 = addiu(s4, 1088);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21448Cu, v0.u());
        a0 = addiu(s4, 1088);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2144ACu, v0.u());
        a0 = s3;
        a1 = 33;
        jal(ctx, 0x2144BCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2144C8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2144DCu, v0.u());
        a0 = addiu(s4, 1344);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2144FCu, v0.u());
        a0 = addiu(s4, 1344);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21451Cu, v0.u());
        a0 = addiu(s4, 1600);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21453Cu, v0.u());
        a0 = addiu(s4, 1600);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21455Cu, v0.u());
        a0 = s3;
        a1 = 36;
        jal(ctx, 0x21456Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x214578u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x21458Cu, v0.u());
        a0 = addiu(s4, 1856);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2145ACu, v0.u());
        a0 = addiu(s4, 1856);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2145CCu, v0.u());
        a0 = addiu(s4, 2112);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2145ECu, v0.u());
        a0 = addiu(s4, 2112);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21460Cu, v0.u());
        a0 = s3;
        a1 = 34;
        jal(ctx, 0x21461Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x214628u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x21463Cu, v0.u());
        a0 = addiu(s4, 2368);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21465Cu, v0.u());
        a0 = addiu(s4, 2368);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21467Cu, v0.u());
        a0 = addiu(s4, 2624);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x21469Cu, v0.u());
        a0 = addiu(s4, 2624);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2146BCu, v0.u());
        a0 = s3;
        a1 = 38;
        jal(ctx, 0x2146CCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2146D8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2146ECu, v0.u());
        s0 = 0;
        for (;;) {  // while (s0 < 9)
            // 0x00214758
            charge(ctx, 3);
            v0 = slti(s0, 9);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00214700
            charge(ctx, 22);
            v0 = sll(s0, 8);
            v0 = addu(s4, v0);
            s2 = addiu(v0, 2880);
            s5 = 0x960000;
            s5 = addiu(s5, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x21472Cu, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x21474Cu, v0.u());
            s0 = addiu(s0, 1);
        }
        // 0x00214764
        charge(ctx, 5);
        lw(v0, s4, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            // 0x002148d8
            charge(ctx, 78);
            a0 = s3;
            a1 = 50;
            jal(ctx, 0x2148E0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x2148ECu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214900u, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s4, 27824);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214928u, v0.u());
            a0 = addiu(s4, 27824);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214948u, v0.u());
            a0 = addiu(s4, 28080);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214968u, v0.u());
            a0 = addiu(s4, 28080);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214988u, v0.u());
            a0 = addiu(s4, 28336);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2149A8u, v0.u());
            a0 = addiu(s4, 28336);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2149C8u, v0.u());
            a0 = addiu(s4, 28592);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2149E8u, v0.u());
            a0 = addiu(s4, 28592);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214A08u, v0.u());
        } else {
            // 0x00214778
            charge(ctx, 3);
            s0 = 0;
            for (;;) {  // while (s0 < 9)
                // 0x0021480c
                charge(ctx, 3);
                v0 = slti(s0, 9);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00214784
                charge(ctx, 34);
                a1 = addiu(s0, 22);
                a0 = s3;
                jal(ctx, 0x21478Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                a0 = v0;
                jal(ctx, 0x214798u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
                a0 = 1;
                a1 = v0;
                lw(v0, s1, 0);
                jalr(ctx, 0x2147ACu, v0.u());
                v0 = sll(s0, 8);
                v0 = addu(s4, v0);
                s2 = addiu(v0, 6208);
                s5 = 0x960000;
                s5 = addiu(s5, 156);  // &0x96009C
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2147E0u, v0.u());
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214800u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00214818
            charge(ctx, 3);
            s0 = 0;
            for (;;) {  // while (s0 < 9)
                // 0x002148c4
                charge(ctx, 3);
                v0 = slti(s0, 9);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00214824
                charge(ctx, 6);
                v0 = sll(s0, 2);
                v0 = addu(s4, v0);
                lw(v1, v0, 22128);
                v0 = 5;
                if (v1 != v0) {
                    // 0x0021483c
                    charge(ctx, 33);
                    a1 = addiu(v1, 41);
                    a0 = s3;
                    jal(ctx, 0x214844u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    a0 = v0;
                    jal(ctx, 0x214850u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x214864u, v0.u());
                    v0 = sll(s0, 8);
                    v0 = addu(s4, v0);
                    s2 = addiu(v0, 22176);
                    s5 = 0x960000;
                    s5 = addiu(s5, 156);  // &0x96009C
                    a0 = s2;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x214898u, v0.u());
                    a0 = s2;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x2148B8u, v0.u());
                }
                // 0x002148c0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x002148d0
            charge(ctx, 2);
        }
        // 0x00214a10
        charge(ctx, 5);
        lw(v0, s4, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x20;
        if (v0 == 0) {
            // 0x00214abc
            charge(ctx, 78);
            a0 = s3;
            a1 = 50;
            jal(ctx, 0x214AC4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x214AD0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214AE4u, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s4, 24752);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214B0Cu, v0.u());
            a0 = addiu(s4, 24752);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214B2Cu, v0.u());
            a0 = addiu(s4, 25008);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214B4Cu, v0.u());
            a0 = addiu(s4, 25008);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214B6Cu, v0.u());
            a0 = addiu(s4, 25264);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214B8Cu, v0.u());
            a0 = addiu(s4, 25264);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214BACu, v0.u());
            a0 = addiu(s4, 25520);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214BCCu, v0.u());
            a0 = addiu(s4, 25520);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214BECu, v0.u());
        } else {
            // 0x00214a24
            charge(ctx, 11);
            a0 = 1;
            jal(ctx, 0x214A28u, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214A3Cu, v0.u());
            s0 = 0;
            for (;;) {  // while (s0 < 2)
                // 0x00214aa8
                charge(ctx, 3);
                v0 = slti(s0, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00214a50
                charge(ctx, 22);
                v0 = sll(s0, 8);
                v0 = addu(s4, v0);
                s2 = addiu(v0, 19536);
                s5 = 0x960000;
                s5 = addiu(s5, 156);  // &0x96009C
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214A7Cu, v0.u());
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214A9Cu, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00214ab4
            charge(ctx, 2);
        }
        // 0x00214bf4
        charge(ctx, 5);
        lw(v0, s4, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x00214ca0
            charge(ctx, 78);
            a0 = s3;
            a1 = 50;
            jal(ctx, 0x214CA8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x214CB4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214CC8u, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s4, 25776);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214CF0u, v0.u());
            a0 = addiu(s4, 25776);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214D10u, v0.u());
            a0 = addiu(s4, 26032);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214D30u, v0.u());
            a0 = addiu(s4, 26032);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214D50u, v0.u());
            a0 = addiu(s4, 26288);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214D70u, v0.u());
            a0 = addiu(s4, 26288);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214D90u, v0.u());
            a0 = addiu(s4, 26544);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214DB0u, v0.u());
            a0 = addiu(s4, 26544);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214DD0u, v0.u());
        } else {
            // 0x00214c08
            charge(ctx, 11);
            a0 = 1;
            jal(ctx, 0x214C0Cu, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214C20u, v0.u());
            s0 = 0;
            for (;;) {  // while (s0 < 4)
                // 0x00214c8c
                charge(ctx, 3);
                v0 = slti(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00214c34
                charge(ctx, 22);
                v0 = sll(s0, 8);
                v0 = addu(s4, v0);
                s2 = addiu(v0, 20064);
                s5 = 0x960000;
                s5 = addiu(s5, 156);  // &0x96009C
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214C60u, v0.u());
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214C80u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00214c98
            charge(ctx, 2);
        }
        // 0x00214dd8
        charge(ctx, 5);
        lw(v0, s4, 4);
        v0 = nor(v0, 0);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x00214e84
            charge(ctx, 78);
            a0 = s3;
            a1 = 50;
            jal(ctx, 0x214E8Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x214E98u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214EACu, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s4, 26800);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214ED4u, v0.u());
            a0 = addiu(s4, 26800);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214EF4u, v0.u());
            a0 = addiu(s4, 27056);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214F14u, v0.u());
            a0 = addiu(s4, 27056);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214F34u, v0.u());
            a0 = addiu(s4, 27312);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214F54u, v0.u());
            a0 = addiu(s4, 27312);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214F74u, v0.u());
            a0 = addiu(s4, 27568);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214F94u, v0.u());
            a0 = addiu(s4, 27568);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x214FB4u, v0.u());
        } else {
            // 0x00214dec
            charge(ctx, 11);
            a0 = 1;
            jal(ctx, 0x214DF0u, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x214E04u, v0.u());
            s0 = 0;
            for (;;) {  // while (s0 < 4)
                // 0x00214e70
                charge(ctx, 3);
                v0 = slti(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00214e18
                charge(ctx, 22);
                v0 = sll(s0, 8);
                v0 = addu(s4, v0);
                s2 = addiu(v0, 21104);
                s5 = 0x960000;
                s5 = addiu(s5, 156);  // &0x96009C
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214E44u, v0.u());
                a0 = s2;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x214E64u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00214e7c
            charge(ctx, 2);
        }
        // 0x00214fbc
        charge(ctx, 74);
        lhu(v1, s4, 12);
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);
        lw(v0, gp, kGpBtlEnemyTbl);  // gBtlEnemyTbl gBtlEnemyTbl
        v0 = addu(v1, v0);
        lbu(a0, v0, 2);
        jal(ctx, 0x214FD8u, gen::fn_sub_215830_00215830);  // [bsaMain_GetKindPage](kind) -> page record of panel set 2
        s2 = 0x960000;
        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x214FECu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x215000u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s4, 5696);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x215028u, v0.u());
        a0 = addiu(s4, 5696);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x215048u, v0.u());
        a0 = s3;
        a1 = 47;
        jal(ctx, 0x215058u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x215064u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x215078u, v0.u());
        a0 = addiu(s4, 5952);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x215098u, v0.u());
        a0 = addiu(s4, 5952);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2150B8u, v0.u());
        lw(a0, s4, 16);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x2150CCu, gen::fn_frFontDraw_003b1360);
        lw(a0, s4, 0);
        v1 = 1;
        if (a0 == v1) {
            // 0x002150f4
            charge(ctx, 88);
            a0 = s3;
            a1 = 39;
            jal(ctx, 0x2150FCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x215108u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);
            jalr(ctx, 0x21511Cu, v0.u());
            a0 = addiu(s4, 5440);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);
            jalr(ctx, 0x21513Cu, v0.u());
            a0 = addiu(s4, 5440);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);
            jalr(ctx, 0x21515Cu, v0.u());
            a0 = s3;
            a1 = 32;
            jal(ctx, 0x21516Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x215178u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);
            jalr(ctx, 0x21518Cu, v0.u());
            a0 = addiu(s4, 19264);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);
            jalr(ctx, 0x2151ACu, v0.u());
            a0 = addiu(s4, 19264);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);
            jalr(ctx, 0x2151CCu, v0.u());
            a0 = s3;
            a1 = 49;
            jal(ctx, 0x2151DCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x2151E8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);
            jalr(ctx, 0x2151FCu, v0.u());
            a0 = addiu(s4, 18752);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);
            jalr(ctx, 0x21521Cu, v0.u());
            a0 = addiu(s4, 18752);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);
            jalr(ctx, 0x21523Cu, v0.u());
            lw(v0, s4, 4);
            v0 = v0 & 0x80;
            if (v0 == 0) {
                // 0x00215254
                charge(ctx, 4);
                lw(v1, s4, 24480);
                v0 = 7;
                if (v1 == v0) {
                    goto L_00215264;
                }
                // 0x0021527c
                charge(ctx, 4);
                a1 = addiu(v1, 22);
                a0 = s3;
                jal(ctx, 0x215284u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                goto L_0021528c;
            }
        L_00215264:
            charge(ctx, 6);
            a0 = s3;
            a1 = 60;
            jal(ctx, 0x21526Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        L_0021528c:
            charge(ctx, 43);
            s2 = 0x960000;
            s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
            a0 = v0;
            jal(ctx, 0x215298u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x2152ACu, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s4, 24496);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2152D4u, v0.u());
            a0 = addiu(s4, 24496);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2152F4u, v0.u());
            a0 = s3;
            a1 = 35;
            jal(ctx, 0x215304u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x215310u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s2, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x215324u, v0.u());
            s2 = 0;
            for (;;) {  // while (s2 < 8)
                // 0x002153d4
                charge(ctx, 3);
                v0 = slti(s2, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00215338
                charge(ctx, 39);
                v0 = sll(s2, 9);
                s6 = addu(s4, v0);
                s5 = addiu(s6, 8512);
                s0 = 0x960000;
                s0 = addiu(s0, 156);  // &0x96009C
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x215364u, v0.u());
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x215384u, v0.u());
                s5 = addiu(s6, 8768);
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2153A8u, v0.u());
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2153C8u, v0.u());
                s2 = addiu(s2, 1);
            }
            // 0x002153e0
            charge(ctx, 15);
            a0 = s3;
            a1 = 37;
            jal(ctx, 0x2153E8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x2153F4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x215408u, v0.u());
            s2 = 0;
            for (;;) {  // while (s2 < 8)
                // 0x002154b8
                charge(ctx, 3);
                v1 = slti(s2, 8);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0021541c
                charge(ctx, 39);
                v0 = sll(s2, 9);
                s6 = addu(s4, v0);
                s5 = addiu(s6, 12608);
                s0 = 0x960000;
                s0 = addiu(s0, 156);  // &0x96009C
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x215448u, v0.u());
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x215468u, v0.u());
                s5 = addiu(s6, 12864);
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x21548Cu, v0.u());
                a0 = s5;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2154ACu, v0.u());
                s2 = addiu(s2, 1);
            }
            // 0x002154c4
            charge(ctx, 5);
            lw(v1, s4, 4);
            v1 = nor(v1, 0);
            v1 = v1 & 0x2;
            if (v1 == 0) {
                // 0x002155d0
                charge(ctx, 3);
                s5 = 0;
                for (;;) {  // while (s5 < 8)
                    // 0x00215730
                    charge(ctx, 3);
                    v1 = slti(s5, 8);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002155dc
                    charge(ctx, 85);
                    a0 = s3;
                    a1 = 50;
                    jal(ctx, 0x2155E4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    a0 = v0;
                    jal(ctx, 0x2155F0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x215604u, v0.u());
                    v0 = sll(s5, 10);
                    s2 = addu(s4, v0);
                    s6 = addiu(s2, 28848);
                    s0 = 0x960000;
                    s0 = addiu(s0, 156);  // &0x96009C
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x215638u, v0.u());
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x215658u, v0.u());
                    s6 = addiu(s2, 29104);
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x21567Cu, v0.u());
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x21569Cu, v0.u());
                    s6 = addiu(s2, 29360);
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x2156C0u, v0.u());
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x2156E0u, v0.u());
                    s2 = addiu(s2, 29616);
                    a0 = s2;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x215704u, v0.u());
                    a0 = s2;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x215724u, v0.u());
                    s5 = addiu(s5, 1);
                }
            } else {
                // 0x002154d8
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x0021557c
                    charge(ctx, 4);
                    lw(v1, s4, 52);
                    v1 = slt(s2, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002154e4
                    charge(ctx, 38);
                    v0 = sll(s2, 1);
                    v1 = addu(s4, v0);
                    v0 = 0x10000;
                    v0 = addu(v1, v0);
                    lh(a1, v0, -22856);
                    a0 = fp;
                    jal(ctx, 0x2154FCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    a0 = v0;
                    jal(ctx, 0x215508u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x21551Cu, v0.u());
                    v0 = sll(s2, 8);
                    v0 = addu(s4, v0);
                    s3 = addiu(v0, 16704);
                    s0 = 0x960000;
                    s0 = addiu(s0, 156);  // &0x96009C
                    a0 = s3;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x215550u, v0.u());
                    a0 = s3;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                    jalr(ctx, 0x215570u, v0.u());
                    s2 = addiu(s2, 1);
                }
                // 0x0021558c
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x002155b8
                    charge(ctx, 4);
                    lw(v1, s4, 52);
                    v1 = slt(s0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00215598
                    charge(ctx, 8);
                    v0 = sll(s0, 2);
                    v0 = addu(s4, v0);
                    lw(a0, v0, 20);
                    a1 = 1;
                    a2 = 0;
                    jal(ctx, 0x2155ACu, gen::fn_frFontDraw_003b1360);
                    s0 = addiu(s0, 1);
                }
                // 0x002155c8
                charge(ctx, 2);
            }
        } else {
            // 0x002150e4
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x002150ec
                charge(ctx, 2);
            }
        }
    }
    // 0x0021573c (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00215770 sub_215770 -- 180 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bsaPanel_Close](panel) destroys the panel's font chains (+16, and +20.. x +52 for kind 1 without bit 1) when
// it is open (+4 bit 0).
void sub_215770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00215770
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 4);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00215798
        charge(ctx, 7);
        lw(a0, s0, 16);
        jal(ctx, 0x21579Cu, gen::fn_sub_3B0170_003b0170);  // [frFontDestroyChain](chain)
        lw(a0, s0, 0);
        v1 = 1;
        if (a0 == v1) {
            // 0x002157c4
            charge(ctx, 5);
            lw(v1, s0, 4);
            v1 = nor(v1, 0);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x002157d8
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x002157fc
                    charge(ctx, 4);
                    lw(v1, s0, 52);
                    v1 = slt(s1, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002157e4
                    charge(ctx, 6);
                    v0 = sll(s1, 2);
                    v0 = addu(s0, v0);
                    lw(a0, v0, 20);
                    jal(ctx, 0x2157F0u, gen::fn_sub_3B0170_003b0170);  // [frFontDestroyChain](chain)
                    s1 = addiu(s1, 1);
                }
            }
        } else {
            // 0x002157b4
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x002157bc
                charge(ctx, 2);
            }
        }
    }
    // 0x0021580c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021B650 sub_21B650 -- 16 bytes; leaf frame (no stack)
// [bseMain_Register](work) bse_main.c: clears the flags and stores the work in the slot.
void sub_21B650(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0021b650
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBseMain);  // 0x7CE300 bse_main.c work
}

// 0x0021B660 sub_21B660 -- 12 bytes; leaf frame (no stack)
// [bseMain_Unregister] clears the bse_main.c slot.
void sub_21B660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x0021b660
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBseMain);  // 0x7CE300 bse_main.c work
}

// 0x0021B920 sub_21B920 -- 20 bytes; leaf frame (no stack)
// [bpRes_Register](work) bp_res.c: clears the two flag words and stores the work in the slot.
void sub_21B920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0021b920
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(a0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
}

// 0x0021B940 sub_21B940 -- 364 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpRes_Request] requests the panel archive: snd_benc/panel/AGS_bp_all.bin or AGS2_bp_all.bin (The Answer,
// by flag 752) or bp_all.bin; collects the party's non-zero persona-select ids (sub_16DD60, up to 3) into +72; flag
// bit 0.
void sub_21B940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b940
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    if (v0 == 0) {
        // 0x0021b95c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21B968u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x0021b970
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    jal(ctx, 0x21B974u, gen::fn_sub_17D800_0017d800);  // the game-mode test (The Answer)
    if (v0 == 0) {
        // 0x0021b9d8
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -7376);  // "snd_benc/panel/bp_all.bin"
        a1 = 1;
        jal(ctx, 0x21B9E4u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
        sw(v0, s0, kBrNode);
    } else {
        // 0x0021b984
        charge(ctx, 5);
        a0 = 752;
        jal(ctx, 0x21B988u, gen::fn_datGetFlag_0016f190);  // datGetFlag(id)
        if (v0 == 0) {
            // 0x0021b9b8
            charge(ctx, 8);
            a0 = 0x690000;
            a0 = addiu(a0, -7408);  // "snd_benc/panel/AGS2_bp_all.bin"
            a1 = 1;
            jal(ctx, 0x21B9C4u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
            sw(v0, s0, kBrNode);
        } else {
            // 0x0021b998
            charge(ctx, 8);
            a0 = 0x690000;
            a0 = addiu(a0, -7440);  // "snd_benc/panel/AGS_bp_all.bin"
            a1 = 1;
            jal(ctx, 0x21B9A4u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
            sw(v0, s0, kBrNode);
        }
    }
    // 0x0021b9f0
    charge(ctx, 4);
    sw(zero, s0, kBrIdCount);
    s1 = 0;
    for (;;) {  // while (s1 < 3)
        // 0x0021ba50
        charge(ctx, 3);
        v1 = slti(s1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021ba00
        charge(ctx, 7);
        a0 = s1;
        jal(ctx, 0x21BA04u, gen::fn_sub_16DD60_0016dd60);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        if (v1 != 0) {
            // 0x0021ba1c
            charge(ctx, 12);
            a0 = s1;
            jal(ctx, 0x21BA20u, gen::fn_sub_16DD60_0016dd60);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            lw(v1, s0, kBrIdCount);
            v1 = sll(v1, 2);
            v1 = addu(s0, v1);
            sw(a0, v1, kBrIds);
            lw(v1, s0, kBrIdCount);
            v1 = addiu(v1, 1);
            sw(v1, s0, kBrIdCount);
        }
        // 0x0021ba4c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0021ba5c
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x0021ba78
        charge(ctx, 4);
        lw(v1, s0, kBrIdCount);
        v1 = slt(a0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021ba68
        charge(ctx, 4);
        v1 = sll(a0, 2);
        v1 = addu(s0, v1);
        sw(zero, v1, kBrIdSetRefs);
        a0 = addiu(a0, 1);
    }
    // 0x0021ba88
    charge(ctx, 9);
    lw(v1, s0, kBrFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, kBrFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021BCB0 sub_21BCB0 -- 1852 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpRes_Update] bp_res.c's loader: when the panel archive has loaded, its 13 files become sprite sets
// (sub_21C9F0) or RwMalloc copies; then the per-id sets; loaded bit 0.
void sub_21BCB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021bcb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    if (v1 == 0) {
        // 0x0021bcd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21BCE0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x0021bce8
    charge(ctx, 5);
    lw(s1, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    lw(v1, s1, kBrFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0021bcfc
        charge(ctx, 5);
        lw(v1, s1, kBrLoaded);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x0021bd10
            charge(ctx, 5);
            lw(a0, s1, kBrNode);
            jal(ctx, 0x21BD14u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
            if (v0 != 0) {
                // 0x0021bd24
                charge(ctx, 3);
                s0 = 0;
                for (;;) {  // while (s0 < 13)
                    // 0x0021c084
                    charge(ctx, 3);
                    v0 = slti(s0, 13);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0021bd30
                    charge(ctx, 3);
                    at = sltiu(s0, 13);
                    if (at == 0) {
                        // 0x0021c06c
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7456);  // "bp_res.c"
                        a1 = 288;
                        jal(ctx, 0x21C078u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 288): `jr $ra` in retail, execution goes on
                    } else {
                        // 0x0021bd3c
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 30128);  // &0x7B75B0
                        v0 = sll(s0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x21BD58u:  // table[0]
                            // 0x0021bd58
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BD64u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BD70u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 16);
                            break;
                        case 0x21BD84u:  // table[1]
                            // 0x0021bd84
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BD90u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BD9Cu, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 28);
                            break;
                        case 0x21BDB0u:  // table[2]
                            // 0x0021bdb0
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BDBCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BDC8u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 32);
                            break;
                        case 0x21BDDCu:  // table[3]
                            // 0x0021bddc
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BDE8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BDF4u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 36);
                            break;
                        case 0x21BE08u:  // table[4]
                            // 0x0021be08
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BE14u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BE20u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 20);
                            break;
                        case 0x21BE34u:  // table[5]
                            // 0x0021be34
                            charge(ctx, 20);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BE40u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21BE5Cu, v0.u());
                            sw(v0, s1, 96);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21BE74u, gen::fn_memcpy_00521250);
                            break;
                        case 0x21BE84u:  // table[6]
                            // 0x0021be84
                            charge(ctx, 20);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BE90u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21BEACu, v0.u());
                            sw(v0, s1, 100);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21BEC4u, gen::fn_memcpy_00521250);
                            break;
                        case 0x21BED4u:  // table[7]
                            // 0x0021bed4
                            charge(ctx, 20);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BEE0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21BEFCu, v0.u());
                            sw(v0, s1, 88);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21BF14u, gen::fn_memcpy_00521250);
                            break;
                        case 0x21BF24u:  // table[8]
                            // 0x0021bf24
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BF30u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BF3Cu, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 40);
                            break;
                        case 0x21BF50u:  // table[9]
                            // 0x0021bf50
                            charge(ctx, 20);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BF5Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21BF78u, v0.u());
                            sw(v0, s1, 84);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21BF90u, gen::fn_memcpy_00521250);
                            break;
                        case 0x21BFA0u:  // table[10]
                            // 0x0021bfa0
                            charge(ctx, 11);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BFACu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x21BFB8u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s1, 24);
                            break;
                        case 0x21BFCCu:  // table[11]
                            // 0x0021bfcc
                            charge(ctx, 20);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21BFD8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21BFF4u, v0.u());
                            sw(v0, s1, 92);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21C00Cu, gen::fn_memcpy_00521250);
                            break;
                        case 0x21C01Cu:  // table[12]
                            // 0x0021c01c
                            charge(ctx, 20);
                            lw(a0, s1, 8);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21C028u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21C044u, v0.u());
                            sw(v0, s1, 104);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21C05Cu, gen::fn_memcpy_00521250);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                    // 0x0021c080
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x0021c090
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x0021c11c
                    charge(ctx, 4);
                    lw(v0, s1, kBrIdCount);
                    v0 = slt(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0021c09c
                    charge(ctx, 6);
                    v0 = 16;
                    s0 = sllv(v0, s2);
                    lw(v0, s1, kBrLoaded);
                    v0 = v0 & s0;
                    if (v0 == 0) {
                        // 0x0021c0b4
                        charge(ctx, 6);
                        v0 = sll(s2, 2);
                        s3 = addu(s1, v0);
                        lw(v0, s3, kBrIds);
                        at = slti(v0, 6);
                        if (at == 0) {
                            // 0x0021c0e8
                            charge(ctx, 5);
                            a1 = addiu(v0, 10);
                            lw(a0, s1, kBrNode);
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21C0F4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                        } else {
                            // 0x0021c0cc
                            charge(ctx, 7);
                            a1 = addiu(v0, 11);
                            lw(a0, s1, kBrNode);
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21C0D8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                        }
                        // 0x0021c0fc
                        charge(ctx, 7);
                        a0 = v0;
                        jal(ctx, 0x21C100u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                        sw(v0, s3, kBrIdSets);
                        lw(v0, s1, kBrLoaded);
                        v0 = v0 | s0;
                        sw(v0, s1, kBrLoaded);
                    }
                    // 0x0021c118
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0021c12c
                charge(ctx, 6);
                lw(v0, s1, kBrLoaded);
                v0 = v0 | 0x1;
                sw(v0, s1, kBrLoaded);
                lw(a0, s1, kBrNode);
                jal(ctx, 0x21C13Cu, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
            }
        }
        // 0x0021c144
        charge(ctx, 4);
        lw(a0, s1, kBrLoaded);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            // 0x0021c154
            charge(ctx, 6);
            a3 = 0;
            lw(a2, s1, kBrIdCount);
            a1 = nor(a0, 0);
            a0 = 16;
            for (;;) {
                // 0x0021c180
                charge(ctx, 3);
                v1 = slt(a3, a2);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x0021c16c
                    charge(ctx, 4);
                    v1 = sllv(a0, a3);
                    v1 = a1 & v1;
                    if (v1 == 0) {
                        // 0x0021c17c
                        charge(ctx, 1);
                        a3 = addiu(a3, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x0021c18c
            charge(ctx, 2);
            if (a3 == a2) {
                // 0x0021c194
                charge(ctx, 4);
                lw(a0, s1, kBrFlags);
                v1 = si(-2);
                v1 = a0 & v1;
                sw(v1, s1, kBrFlags);
            }
        }
    }
    // 0x0021c1a4
    charge(ctx, 4);
    lw(v1, s1, kBrFlags);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0021c1b4
        charge(ctx, 5);
        lw(a0, s1, 112);
        jal(ctx, 0x21C1B8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0021c1c8
            charge(ctx, 9);
            lw(v1, s1, kBrFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s1, kBrFlags);
            lw(v0, s1, kBrLoaded);
            v0 = nor(v0, 0);
            v0 = v0 & 0x80;
            if (v0 == 0) {
                // 0x0021c1ec
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7456);  // "bp_res.c"
                a1 = 347;
                jal(ctx, 0x21C1F8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 347): `jr $ra` in retail, execution goes on
            }
            // 0x0021c200
            charge(ctx, 11);
            lw(v0, s1, 112);
            lw(a0, v0, 272);
            jal(ctx, 0x21C208u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
            sw(v0, s1, 116);
            lw(v0, s1, kBrLoaded);
            v0 = v0 | 0x80;
            sw(v0, s1, kBrLoaded);
            lw(a0, s1, 112);
            jal(ctx, 0x21C224u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
        }
    }
    // 0x0021c22c
    charge(ctx, 4);
    lw(v1, s1, kBrFlags);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0021c23c
        charge(ctx, 5);
        lw(a0, s1, 132);
        jal(ctx, 0x21C240u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0021c250
            charge(ctx, 9);
            lw(v1, s1, kBrFlags);
            v0 = si(-5);
            v0 = v1 & v0;
            sw(v0, s1, kBrFlags);
            lw(v0, s1, kBrLoaded);
            v0 = nor(v0, 0);
            v0 = v0 & 0x100;
            if (v0 == 0) {
                // 0x0021c274
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -7456);  // "bp_res.c"
                a1 = 357;
                jal(ctx, 0x21C280u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 357): `jr $ra` in retail, execution goes on
            }
            // 0x0021c288
            charge(ctx, 3);
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x0021c3a8
                charge(ctx, 3);
                v0 = slti(s0, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0021c294
                charge(ctx, 3);
                v0 = 2;
                if (s0 == v0) {
                    // 0x0021c35c
                    charge(ctx, 18);
                    lw(a0, s1, 132);
                    a1 = s0;
                    a2 = addiu(sp, 0x5C);
                    jal(ctx, 0x21C368u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                    s2 = v0;
                    lw(a0, sp, 0x5C);
                    a1 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                    jalr(ctx, 0x21C384u, v0.u());
                    sw(v0, s1, 128);
                    lw(a2, sp, 0x5C);
                    a0 = v0;
                    a1 = s2;
                    jal(ctx, 0x21C39Cu, gen::fn_memcpy_00521250);
                } else {
                    // 0x0021c2a0
                    charge(ctx, 3);
                    v0 = 1;
                    if (s0 == v0) {
                        // 0x0021c30c
                        charge(ctx, 20);
                        lw(a0, s1, 132);
                        a1 = s0;
                        a2 = addiu(sp, 0x5C);
                        jal(ctx, 0x21C318u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                        s2 = v0;
                        lw(a0, sp, 0x5C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                        jalr(ctx, 0x21C334u, v0.u());
                        sw(v0, s1, 124);
                        lw(a2, sp, 0x5C);
                        a0 = v0;
                        a1 = s2;
                        jal(ctx, 0x21C34Cu, gen::fn_memcpy_00521250);
                    } else {
                        // 0x0021c2ac
                        charge(ctx, 2);
                        if (s0 == 0) {
                            // 0x0021c2bc
                            charge(ctx, 20);
                            lw(a0, s1, 132);
                            a1 = s0;
                            a2 = addiu(sp, 0x5C);
                            jal(ctx, 0x21C2C8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            s2 = v0;
                            lw(a0, sp, 0x5C);
                            a1 = 0x40000;
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                            jalr(ctx, 0x21C2E4u, v0.u());
                            sw(v0, s1, 120);
                            lw(a2, sp, 0x5C);
                            a0 = v0;
                            a1 = s2;
                            jal(ctx, 0x21C2FCu, gen::fn_memcpy_00521250);
                        } else {
                            // 0x0021c2b4
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x0021c3a4
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0021c3b4
            charge(ctx, 6);
            lw(v0, s1, kBrLoaded);
            v0 = v0 | 0x100;
            sw(v0, s1, kBrLoaded);
            lw(a0, s1, 132);
            jal(ctx, 0x21C3C4u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
        }
    }
    // 0x0021c3cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0021C5D0 sub_21C5D0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpRes_GetBlock88] the heap block +88 (asserts loaded bit 0, line 433).
void sub_21C5D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c5d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    if (v0 == 0) {
        // 0x0021c5e8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C5F4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x0021c5fc
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    lw(v0, s0, kBrLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021c610
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 433;
        jal(ctx, 0x21C61Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 433): `jr $ra` in retail, execution goes on
    }
    // 0x0021c624 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, 88);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021C640 sub_21C640 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpRes_GetBlock84] the heap block +84 (line 441).
void sub_21C640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c640
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    if (v0 == 0) {
        // 0x0021c658
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C664u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x0021c66c
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    lw(v0, s0, kBrLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021c680
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 441;
        jal(ctx, 0x21C68Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 441): `jr $ra` in retail, execution goes on
    }
    // 0x0021c694 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, kBrBlocks);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021C6B0 sub_21C6B0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpRes_GetBlock92] the heap block +92 (line 449).
void sub_21C6B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c6b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    if (v0 == 0) {
        // 0x0021c6c8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C6D4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x0021c6dc
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    lw(v0, s0, kBrLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021c6f0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 449;
        jal(ctx, 0x21C6FCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 449): `jr $ra` in retail, execution goes on
    }
    // 0x0021c704 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, 92);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021C790 sub_21C790 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpRes_Forward](a) asserts the bp_res.c slot and returns sub_267370(a).
void sub_21C790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c790
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBpRes);  // 0x7CE304 bp_res.c work (the panel resources)
    if (v0 == 0) {
        // 0x0021c7ac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C7B8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_res.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x0021c7c0
    charge(ctx, 8);
    a0 = s0;
    jal(ctx, 0x21C7C4u, gen::fn_sub_267370_00267370);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021C9F0 sub_21C9F0 -- 556 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpTex_CreateSpriteSet](file) -> set builds a sprite set from a sprite file in one RwMalloc block:
// 20-byte header {+4 pages, +8 rasters, +12 raster count, +16 page count}, the 44-byte page records (raster index, flags,
// width / height from the rectangle, left / top, four RGBA corners scaled x 255 / 128), the rasters (sub_21EC40 per
// image).
void sub_21C9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c9f0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v0 = 0;
    a1 = addiu(v0, 20);
    lhu(v1, a0, 22);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v1 = addu(a1, v0);
    lhu(v0, a0, 20);
    v0 = sll(v0, 2);
    a0 = addu(v1, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    jalr(ctx, 0x21CA48u, v0.u());
    s0 = v0;
    a1 = addiu(s0, 20);
    sw(a1, v0, 4);
    lhu(a0, s1, 22);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(a1, v1);
    sw(v1, v0, 8);
    lhu(v1, s1, 22);
    sw(v1, v0, 16);
    lhu(v1, s1, 20);
    sw(v1, v0, 12);
    lw(v0, s1, 24);
    s2 = addu(s1, v0);
    s3 = 0;
    for (;;) {
        // 0x0021cacc
        charge(ctx, 4);
        lhu(v0, s1, 20);
        v0 = slt(s3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021caa0
        charge(ctx, 11);
        v0 = sll(s3, 3);
        v0 = addu(s2, v0);
        lw(v0, v0, 4);
        a0 = addu(s1, v0);
        jal(ctx, 0x21CAB0u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
        a0 = sll(s3, 2);
        lw(v1, s0, 8);
        v1 = addu(v1, a0);
        sw(v0, v1, 0);
        s3 = addiu(s3, 1);
    }
    // 0x0021cadc
    charge(ctx, 5);
    lw(v0, s1, 28);
    a1 = addu(s1, v0);
    a2 = 0;
    for (;;) {
        // 0x0021cbe8
        charge(ctx, 4);
        lhu(v0, s1, 22);
        v0 = slt(a2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021caf0
        charge(ctx, 31);
        v0 = sll(a2, 3);
        v0 = addu(a1, v0);
        lw(v0, v0, 4);
        a0 = addu(s1, v0);
        v0 = sll(a2, 2);
        v0 = addu(v0, a2);
        v0 = sll(v0, 1);
        v0 = addu(v0, a2);
        v1 = sll(v0, 2);
        lw(v0, s0, 4);
        v1 = addu(v0, v1);
        sw(s0, v1, 0);
        lw(v0, a0, 20);
        sw(v0, v1, 8);
        lw(v0, a0, 24);
        sw(v0, v1, 4);
        lw(a3, a0, 92);
        lw(v0, a0, 84);
        v0 = subu(a3, v0);
        sw(v0, v1, 12);
        lw(a3, a0, 96);
        lw(v0, a0, 88);
        v0 = subu(a3, v0);
        sw(v0, v1, 16);
        lw(v0, a0, 84);
        sw(v0, v1, 20);
        lw(v0, a0, 88);
        sw(v0, v1, 24);
        a3 = 0;
        for (;;) {  // while (a3 < 4)
            // 0x0021cbd8
            charge(ctx, 3);
            v0 = slti(a3, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0021cb6c
            charge(ctx, 27);
            t0 = sll(a3, 2);
            v0 = addu(a0, t0);
            lw(t2, v0, 100);
            v0 = addu(v1, t0);
            t1 = srl(t2, 24);
            t0 = sll(t1, 8);
            t0 = subu(t0, t1);
            t0 = srl(t0, 7);
            sb(t0, v0, 28);
            t0 = srl(t2, 16);
            t1 = t0 & 0xFF;
            t0 = sll(t1, 8);
            t0 = subu(t0, t1);
            t0 = srl(t0, 7);
            sb(t0, v0, 29);
            t0 = srl(t2, 8);
            t1 = t0 & 0xFF;
            t0 = sll(t1, 8);
            t0 = subu(t0, t1);
            t0 = srl(t0, 7);
            sb(t0, v0, 30);
            t1 = t2 & 0xFF;
            t0 = sll(t1, 8);
            t0 = subu(t0, t1);
            t0 = srl(t0, 7);
            sb(t0, v0, 31);
            a3 = addiu(a3, 1);
        }
        // 0x0021cbe4
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0021cbf8
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0021CC20 sub_21CC20 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpTex_DestroySpriteSet](set) frees the set's rasters (sub_4CDE90) and the block (the RwFree slot).
void sub_21CC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021cc20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0;
    for (;;) {
        // 0x0021cc5c
        charge(ctx, 4);
        lw(v0, s0, 12);
        v0 = slt(s1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021cc40
        charge(ctx, 7);
        v1 = sll(s1, 2);
        lw(v0, s0, 8);
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        jal(ctx, 0x21CC50u, gen::fn_sub_4CDE90_004cde90);  // RwRasterDestroy-like: frees a raster
        s1 = addiu(s1, 1);
    }
    // 0x0021cc6c
    charge(ctx, 11);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jalr(ctx, 0x21CC78u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021EC40 sub_21EC40 -- 1144 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpTex_CreateRaster](image) -> RwRaster bp_tex.c: creates a raster for a TIM2-like image: the depth
// from the format byte +22 (4 / 8 bpp palettised, 16, 24, 32; anything else is K_Assert 101 / 141), the palette
// copied for 4 / 8 bpp, then the texels row by row (lock, copy, unlock).
void sub_21EC40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021ec40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = a0;
    s5 = s0;
    s3 = 0;
    lbu(v1, a0, 22);
    v0 = 44;
    if (v1 != v0) {
        // 0x0021ec80
        charge(ctx, 3);
        v0 = 36;
        if (v1 == v0) {
            goto L_0021ed14;
        }
        // 0x0021ec8c
        charge(ctx, 3);
        v0 = 20;
        if (v1 == v0) {
            goto L_0021ed14;
        }
        // 0x0021ec98
        charge(ctx, 3);
        v0 = 27;
        if (v1 != v0) {
            // 0x0021eca4
            charge(ctx, 3);
            v0 = 19;
            if (v1 == v0) {
                goto L_0021ed08;
            }
            // 0x0021ecb0
            charge(ctx, 3);
            v0 = 10;
            if (v1 != v0) {
                // 0x0021ecbc
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_0021ecfc;
                }
                // 0x0021ecc8
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0021ecf0
                    charge(ctx, 3);
                    s3 = 24;
                } else {
                    // 0x0021ecd4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0021ece4
                        charge(ctx, 3);
                        s3 = 32;
                    } else {
                        // 0x0021ecdc
                        charge(ctx, 2);
                    }
                }
                goto L_0021ed18;
            }
        L_0021ecfc:
            charge(ctx, 3);
            s3 = 16;
            goto L_0021ed18;
        }
    L_0021ed08:
        charge(ctx, 3);
        s3 = 8;
        goto L_0021ed18;
    }
L_0021ed14:
    charge(ctx, 1);
    s3 = 4;
L_0021ed18:
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x0021ed20
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7312);  // "bp_tex.c"
        a1 = 101;
        jal(ctx, 0x21ED2Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_tex.c", 101): `jr $ra` in retail, execution goes on
    }
    // 0x0021ed34
    charge(ctx, 4);
    s0 = addiu(s0, 64);
    v0 = 4;
    if (s3 == v0) {
        // 0x0021ed74
        charge(ctx, 5);
        s2 = s0;
        lbu(v0, s5, 16);
        v0 = sll(v0, 6);
        s0 = addu(s0, v0);
        s1 = s1 | 0x1;
    } else {
        // 0x0021ed44
        charge(ctx, 3);
        v0 = 8;
        if (s3 == v0) {
            // 0x0021ed58
            charge(ctx, 7);
            s2 = s0;
            lbu(v0, s5, 16);
            v0 = sll(v0, 10);
            s0 = addu(s0, v0);
            s1 = s1 | 0x1;
        } else {
            // 0x0021ed50
            charge(ctx, 2);
        }
    }
    // 0x0021ed88
    charge(ctx, 5);
    s4 = 0;
    s4 = s4 | 0x4;
    v0 = 4;
    if (s3 == v0) {
        // 0x0021edec
        charge(ctx, 3);
        s4 = s4 | 0x4500;
    } else {
        // 0x0021ed9c
        charge(ctx, 3);
        v0 = 8;
        if (s3 == v0) {
            // 0x0021ede0
            charge(ctx, 3);
            s4 = s4 | 0x2500;
        } else {
            // 0x0021eda8
            charge(ctx, 3);
            v0 = 24;
            if (s3 == v0) {
                // 0x0021edd4
                charge(ctx, 3);
                s4 = s4 | 0x600;
            } else {
                // 0x0021edb4
                charge(ctx, 3);
                v0 = 32;
                if (s3 == v0) {
                    // 0x0021edc8
                    charge(ctx, 3);
                    s4 = s4 | 0x500;
                } else {
                    // 0x0021edc0
                    charge(ctx, 2);
                    // 0x0021edf8
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -7312);  // "bp_tex.c"
                    a1 = 141;
                    jal(ctx, 0x21EE04u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_tex.c", 141): `jr $ra` in retail, execution goes on
                }
            }
        }
    }
    // 0x0021ee0c
    charge(ctx, 10);
    lhu(a0, s5, 18);
    lhu(a1, s5, 20);
    a2 = s3;
    a3 = s4;
    jal(ctx, 0x21EE1Cu, gen::fn_sub_4CE0F0_004ce0f0);
    s4 = v0;
    v0 = s1 & 0x1;
    if (v0 != 0) {
        // 0x0021ee34
        charge(ctx, 7);
        a0 = s4;
        a1 = 1;
        jal(ctx, 0x21EE3Cu, gen::fn_sub_4CDF30_004cdf30);
        v1 = 4;
        if (s3 == v1) {
            // 0x0021ee98
            charge(ctx, 3);
            a0 = 0;
            for (;;) {  // while (a0 < 16)
                // 0x0021eeb8
                charge(ctx, 3);
                v1 = slti(a0, 16);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0021eea4
                charge(ctx, 5);
                lw(v1, s2, 0);
                sw(v1, v0, 0);
                s2 = addiu(s2, 4);
                v0 = addiu(v0, 4);
                a0 = addiu(a0, 1);
            }
        } else {
            // 0x0021ee50
            charge(ctx, 3);
            v1 = 8;
            if (s3 == v1) {
                // 0x0021ee64
                charge(ctx, 3);
                a0 = 0;
                for (;;) {  // while (a0 < 256)
                    // 0x0021ee84
                    charge(ctx, 3);
                    v1 = slti(a0, 256);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0021ee70
                    charge(ctx, 5);
                    lw(v1, s2, 0);
                    sw(v1, v0, 0);
                    s2 = addiu(s2, 4);
                    v0 = addiu(v0, 4);
                    a0 = addiu(a0, 1);
                }
                // 0x0021ee90
                charge(ctx, 2);
            } else {
                // 0x0021ee5c
                charge(ctx, 2);
            }
        }
        // 0x0021eec4
        charge(ctx, 3);
        a0 = s4;
        jal(ctx, 0x21EEC8u, gen::fn_sub_4CDE40_004cde40);
    }
    // 0x0021eed0
    charge(ctx, 8);
    a0 = s4;
    a1 = 0;
    a2 = 1;
    jal(ctx, 0x21EEDCu, gen::fn_sub_4CE200_004ce200);
    v1 = 4;
    if (s3 == v1) {
        // 0x0021f02c
        charge(ctx, 3);
        a1 = 0;
        for (;;) {
            // 0x0021f070
            charge(ctx, 4);
            lhu(v1, s5, 20);
            v1 = slt(a1, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0021f038
            charge(ctx, 3);
            a0 = 0;
            for (;;) {
                // 0x0021f058
                charge(ctx, 5);
                lhu(v1, s5, 18);
                v1 = sra(v1, 3);
                v1 = slt(a0, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0021f044
                charge(ctx, 5);
                lw(v1, s0, 0);
                sw(v1, v0, 0);
                s0 = addiu(s0, 4);
                v0 = addiu(v0, 4);
                a0 = addiu(a0, 1);
            }
            // 0x0021f06c
            charge(ctx, 1);
            a1 = addiu(a1, 1);
        }
    } else {
        // 0x0021eef0
        charge(ctx, 3);
        v1 = 8;
        if (s3 == v1) {
            // 0x0021efd4
            charge(ctx, 3);
            a1 = 0;
            for (;;) {
                // 0x0021f014
                charge(ctx, 4);
                lhu(v1, s5, 20);
                v1 = slt(a1, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0021efe0
                charge(ctx, 3);
                a0 = 0;
                for (;;) {
                    // 0x0021f000
                    charge(ctx, 4);
                    lhu(v1, s5, 18);
                    v1 = slt(a0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0021efec
                    charge(ctx, 5);
                    lbu(v1, s0, 0);
                    sb(v1, v0, 0);
                    s0 = addiu(s0, 1);
                    v0 = addiu(v0, 1);
                    a0 = addiu(a0, 1);
                }
                // 0x0021f010
                charge(ctx, 1);
                a1 = addiu(a1, 1);
            }
            // 0x0021f024
            charge(ctx, 2);
        } else {
            // 0x0021eefc
            charge(ctx, 3);
            v1 = 24;
            if (s3 == v1) {
                // 0x0021ef74
                charge(ctx, 3);
                a2 = 0;
                for (;;) {
                    // 0x0021efbc
                    charge(ctx, 4);
                    lhu(v1, s5, 20);
                    v1 = slt(a2, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0021ef80
                    charge(ctx, 3);
                    a1 = 0;
                    for (;;) {
                        // 0x0021efa0
                        charge(ctx, 6);
                        lhu(a0, s5, 18);
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        v1 = slt(a1, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0021ef8c
                        charge(ctx, 5);
                        lbu(v1, s0, 0);
                        sb(v1, v0, 0);
                        s0 = addiu(s0, 1);
                        v0 = addiu(v0, 1);
                        a1 = addiu(a1, 1);
                    }
                    // 0x0021efb8
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                }
                // 0x0021efcc
                charge(ctx, 2);
            } else {
                // 0x0021ef08
                charge(ctx, 3);
                v1 = 32;
                if (s3 == v1) {
                    // 0x0021ef1c
                    charge(ctx, 3);
                    a0 = 0;
                    for (;;) {
                        // 0x0021ef5c
                        charge(ctx, 4);
                        lhu(v1, s5, 20);
                        v1 = slt(a0, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0021ef28
                        charge(ctx, 3);
                        a1 = 0;
                        for (;;) {
                            // 0x0021ef48
                            charge(ctx, 4);
                            lhu(v1, s5, 18);
                            v1 = slt(a1, v1);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0021ef34
                            charge(ctx, 5);
                            lw(v1, s0, 0);
                            sw(v1, v0, 0);
                            s0 = addiu(s0, 4);
                            v0 = addiu(v0, 4);
                            a1 = addiu(a1, 1);
                        }
                        // 0x0021ef58
                        charge(ctx, 1);
                        a0 = addiu(a0, 1);
                    }
                    // 0x0021ef6c
                    charge(ctx, 2);
                } else {
                    // 0x0021ef14
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0021f080
    charge(ctx, 14);
    a0 = s4;
    jal(ctx, 0x21F084u, gen::fn_sub_4CDE00_004cde00);
    v0 = s4;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0022C720 sub_22C720 -- 296 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_Init](panel, u16 id) bpp_panel.c: the member's portrait and frames (pages 0 / 1 of its set,
// sub_21C450), the bars (panel set 3 page 10), x = y = 100, scales 0; flag bit 0.
void sub_22C720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022c720
    enter(ctx, 74);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    sw(zero, a0, kBpnFlags);
    a0 = 3;
    jal(ctx, 0x22C744u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    v0 = 0x42C80000;
    sw(v0, s0, kBpnX);
    sw(v0, s0, kBpnY);
    sh(s1, s0, kBpnId);
    a0 = s1;
    jal(ctx, 0x22C764u, gen::fn_sub_21C450_0021c450);  // [bpRes_GetSetById](u16 id): a member's sprite set
    s1 = v0;
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x22C778u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBpnPortrait);
    a1 = v0;
    jal(ctx, 0x22C788u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x22C798u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s1 = v0;
    a0 = addiu(s0, kBpnFrame);
    a1 = s1;
    jal(ctx, 0x22C7ACu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = addiu(s0, 528);
    a1 = s1;
    jal(ctx, 0x22C7BCu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = addiu(s0, 784);
    a1 = s1;
    jal(ctx, 0x22C7CCu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = addiu(s0, 1040);
    a1 = s1;
    jal(ctx, 0x22C7DCu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s2;
    a1 = 10;
    jal(ctx, 0x22C7ECu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s1 = v0;
    a0 = addiu(s0, kBpnBars);
    a1 = s1;
    jal(ctx, 0x22C800u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = addiu(s0, 1840);
    a1 = s1;
    jal(ctx, 0x22C810u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    sw(zero, s0, kBpnScale);
    sw(zero, s0, kBpnScale2);
    lw(v1, s0, kBpnFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, kBpnFlags);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0022C850 sub_22C850 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bppPanel_Close](panel) clears the panel's flags (K_Assert 435 if it is not open).
void sub_22C850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022c850
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, kBpnFlags);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0022c870
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 435;
        jal(ctx, 0x22C87Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 435): `jr $ra` in retail, execution goes on
    }
    // 0x0022c884 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(zero, s0, kBpnFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0022C8A0 sub_22C8A0 -- 5744 bytes; frame 0xA0: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bppPanel_Layout](panel) one member panel's per-frame layout: the open (16 frames), flash (8) and fade (20)
// counters, the slide offsets (table 0x68E3BC), the colours of the open / close / flash / ailment states, the portrait
// and frame quads, the bars, the HP / SP digits (sub_22EB30) and the ailment animation (sub_22FA80).
void sub_22C8A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x0022c8a0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    lw(v0, a0, kBpnFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0022c8e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 461;
        jal(ctx, 0x22C8F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 461): `jr $ra` in retail, execution goes on
    }
    // 0x0022c8f8
    charge(ctx, 16);
    a0 = 3;
    jal(ctx, 0x22C8FCu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s1 = v0;
    a0 = 5;
    jal(ctx, 0x22C90Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s0 = v0;
    lhu(a0, s2, kBpnId);
    jal(ctx, 0x22C91Cu, gen::fn_sub_21C450_0021c450);  // [bpRes_GetSetById](u16 id): a member's sprite set
    s3 = v0;
    lw(v1, s2, kBpnFlags);
    v0 = v1 & 0x20;
    if (v0 != 0) {
        // 0x0022c938
        charge(ctx, 4);
        lw(v0, s2, kBpnOpenFrame);
        at = slti(v0, 16);
        if (at == 0) {
            // 0x0022c958
            charge(ctx, 3);
            v0 = si(-33);
            v0 = v1 & v0;
            sw(v0, s2, kBpnFlags);
        } else {
            // 0x0022c948
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sw(v0, s2, kBpnOpenFrame);
        }
    }
    // 0x0022c964
    charge(ctx, 4);
    lw(v1, s2, kBpnFlags);
    v0 = v1 & 0x40;
    if (v0 == 0) {
        // 0x0022c9a8
        charge(ctx, 3);
        v0 = v1 & 0x80;
        if (v0 != 0) {
            // 0x0022c9b4
            charge(ctx, 4);
            lw(v0, s2, kBpnFlashFrame);
            at = slti(v0, 8);
            if (at == 0) {
                // 0x0022c9d4
                charge(ctx, 3);
                v0 = si(-129);
                v0 = v1 & v0;
                sw(v0, s2, kBpnFlags);
            } else {
                // 0x0022c9c4
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sw(v0, s2, kBpnFlashFrame);
            }
        }
    } else {
        // 0x0022c974
        charge(ctx, 4);
        lw(v0, s2, kBpnFlashFrame);
        at = slti(v0, 8);
        if (at == 0) {
            // 0x0022c994
            charge(ctx, 5);
            v0 = si(-65);
            v0 = v1 & v0;
            sw(v0, s2, kBpnFlags);
        } else {
            // 0x0022c984
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sw(v0, s2, kBpnFlashFrame);
        }
    }
    // 0x0022c9e0
    charge(ctx, 5);
    lw(v1, s2, kBpnFlags);
    v0 = nor(v1, 0);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x0022c9f4
        charge(ctx, 3);
        v0 = v1 & 0x100;
        if (v0 != 0) {
            // 0x0022ca00
            charge(ctx, 4);
            lw(v0, s2, kBpnFadeFrame);
            at = slti(v0, 20);
            if (at == 0) {
                // 0x0022ca20
                charge(ctx, 3);
                v0 = si(-257);
                v0 = v1 & v0;
                sw(v0, s2, kBpnFlags);
            } else {
                // 0x0022ca10
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sw(v0, s2, kBpnFadeFrame);
            }
        }
    }
    // 0x0022ca2c
    charge(ctx, 4);
    lw(v1, s2, kBpnFlags);
    v0 = v1 & 0x10;
    if (v0 == 0) {
        // 0x0022caa8
        charge(ctx, 3);
        v0 = v1 & 0x80;
        if (v0 == 0) {
            // 0x0022cb0c
            charge(ctx, 2);
            sw(zero, s2, 1304);
            sw(zero, s2, 1308);
        } else {
            // 0x0022cab4
            charge(ctx, 22);
            lwc1(f0, s2, kBpnFlashFrame);
            cvt_s_w(f1, f0);
            v0 = 0x41000000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            lwc1(f0, s2, kBpnScale2);
            mul_s(f3, f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f2);
            mul_s(f1, f2, f3);
            v0 = 0x42700000;
            mtc1(v0, f0);
            mula_s(f0, f3);
            msub_s(f0, f3, f1);
            sub_s(f0, f0, f2);
            swc1(f0, s2, 1304);
            sw(zero, s2, 1308);
        }
    } else {
        // 0x0022ca3c
        charge(ctx, 3);
        v0 = v1 & 0x40;
        if (v0 == 0) {
            // 0x0022ca94
            charge(ctx, 5);
            v0 = lui(0xC1F0);
            sw(v0, s2, 1304);
            sw(zero, s2, 1308);
        } else {
            // 0x0022ca48
            charge(ctx, 19);
            lwc1(f0, s2, kBpnFlashFrame);
            cvt_s_w(f1, f0);
            v0 = 0x41000000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = lui(0xC1F0);
            mtc1(v0, f0);
            mul_s(f1, f0, f2);
            v0 = lui(0xC270);
            mtc1(v0, f0);
            mula_s(f0, f2);
            msub_s(f0, f2, f1);
            swc1(f0, s2, 1304);
            sw(zero, s2, 1308);
        }
    }
    // 0x0022cb14
    charge(ctx, 35);
    lwc1(f3, s2, kBpnScale);
    v0 = 0x3F800000;
    mtc1(v0, f2);
    mul_s(f1, f2, f3);
    v0 = 0x40000000;
    mtc1(v0, f0);
    mula_s(f0, f3);
    msub_s(f0, f3, f1);
    sub_s(f1, f2, f0);
    v0 = 0x43340000;
    mtc1(v0, f0);
    mul_s(f0, f0, f1);
    swc1(f0, s2, 1312);
    v0 = lui(0xC2A0);
    mtc1(v0, f0);
    mul_s(f0, f0, f1);
    swc1(f0, s2, 1316);
    lwc1(f1, s2, kBpnX);
    lwc1(f0, s2, 1304);
    add_s(f1, f1, f0);
    lwc1(f0, s2, 1312);
    add_s(f25, f0, f1);
    lwc1(f1, s2, kBpnY);
    lwc1(f0, s2, 1308);
    add_s(f1, f1, f0);
    lwc1(f0, s2, 1316);
    add_s(f24, f0, f1);
    lw(v0, s2, kBpnFlags);
    v1 = v0 & 0x20;
    if (v1 != 0) {
        // 0x0022cba0
        charge(ctx, 4);
        lw(v0, s2, kBpnOpenFrame);
        at = slti(v0, 11);
        if (at == 0) {
            goto L_0022cc2c;
        }
        // 0x0022cbb0
        charge(ctx, 31);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -7284);  // &0x68E38C
        v0 = addu(v0, v1);
        lwc1(f20, v0, 0);
        lwc1(f12, gp, -31772);  // 0x7CB0D4 = 0.349066f
        jal(ctx, 0x22CBC8u, gen::fn_cosf_0052e6d8);
        mul_s(f23, f20, f0);
        lwc1(f12, gp, -31772);  // 0x7CB0D4 = 0.349066f
        jal(ctx, 0x22CBD8u, gen::fn_sinf_0052e878);
        neg_s(f1, f20);
        mul_s(f22, f1, f0);
        lw(v0, s2, kBpnOpenFrame);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -7236);  // &0x68E3BC
        v0 = addu(v0, v1);
        lwc1(f20, v0, 0);
        lwc1(f12, gp, -31772);  // 0x7CB0D4 = 0.349066f
        jal(ctx, 0x22CC04u, gen::fn_cosf_0052e6d8);
        mul_s(f21, f20, f0);
        lwc1(f12, gp, -31772);  // 0x7CB0D4 = 0.349066f
        jal(ctx, 0x22CC14u, gen::fn_sinf_0052e878);
        neg_s(f1, f20);
        mul_s(f0, f1, f0);
        goto L_0022ccb4;
    }
L_0022cc2c:
    charge(ctx, 5);
    mtc1(zero, f23);
    mov_s(f22, f23);
    if (v1 == 0) {
        // 0x0022ccac
        charge(ctx, 2);
        mov_s(f21, f23);
        mov_s(f0, f23);
    } else {
        // 0x0022cc40
        charge(ctx, 5);
        lw(v0, s2, 2116);
        v0 = addiu(v0, -1);
        v0 = slti(v0, 16);
        if (v0 == 0) {
            // 0x0022cc54
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -6512);  // "bpp_panel.c"
            a1 = 563;
            jal(ctx, 0x22CC60u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 563): `jr $ra` in retail, execution goes on
        }
        // 0x0022cc68
        charge(ctx, 17);
        lw(v0, s2, 2116);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -7236);  // &0x68E3BC
        v0 = addu(v0, v1);
        lwc1(f20, v0, 0);
        lwc1(f12, gp, -31772);  // 0x7CB0D4 = 0.349066f
        jal(ctx, 0x22CC84u, gen::fn_cosf_0052e6d8);
        mul_s(f21, f20, f0);
        lwc1(f12, gp, -31772);  // 0x7CB0D4 = 0.349066f
        jal(ctx, 0x22CC94u, gen::fn_sinf_0052e878);
        neg_s(f1, f20);
        mul_s(f0, f1, f0);
    }
L_0022ccb4:
    charge(ctx, 8);
    add_s(f23, f25, f23);
    add_s(f22, f24, f22);
    add_s(f21, f25, f21);
    add_s(f20, f24, f0);
    lw(a0, s2, 0);
    v0 = a0 & 0x4;
    if (v0 != 0) {
        // 0x0022ccd4
        charge(ctx, 4);
        lw(v1, s2, 2096);
        v0 = 8;
        if (v1 != v0) {
            goto L_0022cd08;
        }
        // 0x0022cce4
        charge(ctx, 9);
        v1 = 255;
        sb(v1, sp, 0x9C);
        v0 = 225;
        sb(v0, sp, 0x9D);
        v0 = 185;
        sb(v0, sp, 0x9E);
        sb(v1, sp, 0x9F);
        goto L_0022d100;
    }
L_0022cd08:
    charge(ctx, 3);
    v1 = a0 & 0x20;
    if (v1 != 0) {
        // 0x0022cd14
        charge(ctx, 4);
        lw(v0, s2, 2116);
        at = slti(v0, 11);
        if (at == 0) {
            goto L_0022ce28;
        }
        // 0x0022cd24
        charge(ctx, 8);
        v0 = 0x42480000;
        mtc1(v0, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022cd5c
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022cd44
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022cd74
        charge(ctx, 8);
        sb(v1, sp, 0x9C);
        mtc1(zero, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022cdac
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022cd94
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022cdc4
        charge(ctx, 8);
        sb(v1, sp, 0x9D);
        mtc1(zero, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022cdfc
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022cde4
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022ce14
        charge(ctx, 5);
        sb(v1, sp, 0x9E);
        v0 = 255;
        sb(v0, sp, 0x9F);
        goto L_0022d100;
    }
L_0022ce28:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x0022cf98
        charge(ctx, 3);
        v0 = a0 & 0x8;
        if (v0 == 0) {
            // 0x0022cfc8
            charge(ctx, 3);
            v0 = a0 & 0x100;
            if (v0 == 0) {
                // 0x0022d0ec
                charge(ctx, 5);
                v0 = 255;
                sb(v0, sp, 0x9C);
                sb(v0, sp, 0x9D);
                sb(v0, sp, 0x9E);
                sb(v0, sp, 0x9F);
            } else {
                // 0x0022cfd4
                charge(ctx, 26);
                lwc1(f0, s2, 2124);
                cvt_s_w(f1, f0);
                v0 = 0x41A00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 255;
                sb(v0, sp, 0x9C);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f3, f0, f1);
                v0 = lui(0xC2E6);
                mtc1(v0, f2);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f2, f3);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022d054
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0022d03c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022d06c
                charge(ctx, 15);
                sb(v1, sp, 0x9D);
                v0 = lui(0xC339);
                mtc1(v0, f2);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f2, f3);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022d0c0
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0022d0a8
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022d0d8
                charge(ctx, 5);
                sb(v1, sp, 0x9E);
                v0 = 255;
                sb(v0, sp, 0x9F);
            }
        } else {
            // 0x0022cfa4
            charge(ctx, 9);
            v1 = 255;
            sb(v1, sp, 0x9C);
            v0 = 140;
            sb(v0, sp, 0x9D);
            v0 = 70;
            sb(v0, sp, 0x9E);
            sb(v1, sp, 0x9F);
        }
    } else {
        // 0x0022ce30
        charge(ctx, 27);
        lw(v0, s2, 2116);
        v0 = addiu(v0, -10);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40C00000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f3, f0, f1);
        v0 = lui(0xC34D);
        mtc1(v0, f2);
        v0 = 0x437F0000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f1, f2, f3);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022ceb4
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022ce9c
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022cecc
        charge(ctx, 15);
        sb(v1, sp, 0x9C);
        v0 = lui(0xC37F);
        mtc1(v0, f0);
        mul_s(f1, f0, f3);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022cf20
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022cf08
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022cf38
        charge(ctx, 7);
        sb(v1, sp, 0x9D);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022cf6c
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022cf54
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022cf84
        charge(ctx, 5);
        sb(v1, sp, 0x9E);
        v0 = 255;
        sb(v0, sp, 0x9F);
    }
L_0022d100:
    charge(ctx, 6);
    lwc1(f0, sp, 0x9C);
    swc1(f0, sp, 0x98);
    lw(a0, s2, 0);
    v0 = a0 & 0x8;
    if (v0 == 0) {
        // 0x0022d13c
        charge(ctx, 3);
        v0 = a0 & 0x4;
        if (v0 != 0) {
            // 0x0022d148
            charge(ctx, 4);
            lw(v1, s2, 2096);
            v0 = 8;
            if (v1 != v0) {
                goto L_0022d158;
            }
            goto L_0022d2b4;
        }
    L_0022d158:
        charge(ctx, 3);
        v1 = a0 & 0x20;
        if (v1 != 0) {
            // 0x0022d164
            charge(ctx, 4);
            lw(v0, s2, 2116);
            at = slti(v0, 11);
            if (at == 0) {
                goto L_0022d278;
            }
            // 0x0022d174
            charge(ctx, 8);
            v0 = 0x42480000;
            mtc1(v0, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0022d1ac
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0022d194
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0022d1c4
            charge(ctx, 8);
            sb(v1, sp, 0x9C);
            mtc1(zero, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0022d1fc
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0022d1e4
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0022d214
            charge(ctx, 8);
            sb(v1, sp, 0x9D);
            mtc1(zero, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0022d24c
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0022d234
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0022d264
            charge(ctx, 5);
            sb(v1, sp, 0x9E);
            v0 = 255;
            sb(v0, sp, 0x9F);
            goto L_0022d2b4;
        }
    L_0022d278:
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0022d2a0
            charge(ctx, 5);
            v0 = 255;
            sb(v0, sp, 0x9C);
            sb(v0, sp, 0x9D);
            sb(v0, sp, 0x9E);
            sb(v0, sp, 0x9F);
        } else {
            // 0x0022d280
            charge(ctx, 8);
            v0 = 50;
            sb(v0, sp, 0x9C);
            sb(zero, sp, 0x9D);
            sb(zero, sp, 0x9E);
            v0 = 255;
            sb(v0, sp, 0x9F);
        }
    } else {
        // 0x0022d118
        charge(ctx, 9);
        v1 = 255;
        sb(v1, sp, 0x9C);
        v0 = 140;
        sb(v0, sp, 0x9D);
        v0 = 70;
        sb(v0, sp, 0x9E);
        sb(v1, sp, 0x9F);
    }
L_0022d2b4:
    charge(ctx, 6);
    lwc1(f0, sp, 0x9C);
    swc1(f0, sp, 0x94);
    lw(a0, s2, 0);
    v1 = a0 & 0x20;
    if (v1 != 0) {
        // 0x0022d2cc
        charge(ctx, 4);
        lw(v0, s2, 2116);
        at = slti(v0, 11);
        if (at == 0) {
            goto L_0022d42c;
        }
        // 0x0022d2dc
        charge(ctx, 8);
        v0 = 0x43480000;
        mtc1(v0, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d314
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d2fc
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d32c
        charge(ctx, 8);
        sb(v1, sp, 0x9C);
        mtc1(zero, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d364
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d34c
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d37c
        charge(ctx, 8);
        sb(v1, sp, 0x9D);
        mtc1(zero, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d3b4
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d39c
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d3cc
        charge(ctx, 9);
        sb(v1, sp, 0x9E);
        v0 = 0x437F0000;
        mtc1(v0, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d408
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d3f0
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d420
        charge(ctx, 3);
        sb(v1, sp, 0x9F);
        goto L_0022d7ac;
    }
L_0022d42c:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x0022d5f0
        charge(ctx, 3);
        v0 = a0 & 0x8;
        if (v0 == 0) {
            // 0x0022d620
            charge(ctx, 3);
            v0 = a0 & 0x100;
            if (v0 == 0) {
                // 0x0022d798
                charge(ctx, 5);
                v0 = 255;
                sb(v0, sp, 0x9C);
                sb(v0, sp, 0x9D);
                sb(v0, sp, 0x9E);
                sb(v0, sp, 0x9F);
            } else {
                // 0x0022d62c
                charge(ctx, 26);
                lwc1(f0, s2, 2124);
                cvt_s_w(f1, f0);
                v0 = 0x41A00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 255;
                sb(v0, sp, 0x9C);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f3, f0, f1);
                v0 = lui(0xC282);
                mtc1(v0, f2);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f2, f3);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022d6ac
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0022d694
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022d6c4
                charge(ctx, 15);
                sb(v1, sp, 0x9D);
                v0 = lui(0xC2FA);
                mtc1(v0, f2);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f2, f3);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022d718
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0022d700
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022d730
                charge(ctx, 11);
                sb(v1, sp, 0x9E);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f3);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022d774
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0022d75c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022d78c
                charge(ctx, 3);
                sb(v1, sp, 0x9F);
            }
        } else {
            // 0x0022d5fc
            charge(ctx, 9);
            v1 = 255;
            sb(v1, sp, 0x9C);
            v0 = 190;
            sb(v0, sp, 0x9D);
            v0 = 130;
            sb(v0, sp, 0x9E);
            sb(v1, sp, 0x9F);
        }
    } else {
        // 0x0022d434
        charge(ctx, 27);
        lw(v0, s2, 2116);
        v0 = addiu(v0, -10);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40C00000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f3, f0, f1);
        v0 = lui(0xC25C);
        mtc1(v0, f2);
        v0 = 0x437F0000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f1, f2, f3);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d4b8
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d4a0
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d4d0
        charge(ctx, 15);
        sb(v1, sp, 0x9C);
        v0 = lui(0xC37F);
        mtc1(v0, f0);
        mul_s(f1, f0, f3);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d524
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d50c
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d53c
        charge(ctx, 7);
        sb(v1, sp, 0x9D);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d570
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d558
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d588
        charge(ctx, 11);
        sb(v1, sp, 0x9E);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f1, f0, f3);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022d5cc
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022d5b4
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022d5e4
        charge(ctx, 3);
        sb(v1, sp, 0x9F);
    }
L_0022d7ac:
    charge(ctx, 30);
    lwc1(f0, sp, 0x9C);
    swc1(f0, sp, 0x90);
    a0 = s3;
    a1 = 0;
    jal(ctx, 0x22D7BCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x41F00000;
    mtc1(v1, f0);
    add_s(f23, f0, f23);
    swc1(f23, sp, 0x70);
    v1 = 0x41700000;
    mtc1(v1, f0);
    add_s(f22, f0, f22);
    swc1(f22, sp, 0x74);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s2, 16);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22D80Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    lw(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x0022d87c
        charge(ctx, 5);
        v0 = 255;
        sb(v0, sp, 0x9C);
        sb(v0, sp, 0x9D);
        sb(v0, sp, 0x9E);
        sb(v0, sp, 0x9F);
    } else {
        // 0x0022d824
        charge(ctx, 22);
        lw(v1, s2, 2096);
        v0 = sll(v1, 1);
        v1 = addu(v0, v1);
        v0 = 0x690000;
        v0 = addiu(v0, -6992);  // &0x68E4B0
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        sb(v0, sp, 0x9C);
        v0 = 0x690000;
        v0 = addiu(v0, -6991);  // &0x68E4B1
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        sb(v0, sp, 0x9D);
        v0 = 0x690000;
        v0 = addiu(v0, -6990);  // &0x68E4B2
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        sb(v0, sp, 0x9E);
        v0 = 255;
        sb(v0, sp, 0x9F);
    }
    // 0x0022d890
    charge(ctx, 4);
    lw(v0, s2, 0);
    v0 = v0 & 0x200;
    if (v0 != 0) {
        // 0x0022d8a0
        charge(ctx, 8);
        lbu(v1, sp, 0x9F);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 4);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        sb(v0, sp, 0x9F);
    }
    // 0x0022d8c0
    charge(ctx, 124);
    a0 = addiu(s2, 16);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x22D8C8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s3;
    a1 = 1;
    jal(ctx, 0x22D8D8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s3 = v0;
    swc1(f23, sp, 0x70);
    swc1(f22, sp, 0x74);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s2, 272);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22D90Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = addiu(s2, 528);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22D91Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 0x41F00000;
    mtc1(v0, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x70);
    v0 = 0x41700000;
    mtc1(v0, f0);
    add_s(f0, f0, f20);
    swc1(f0, sp, 0x74);
    lwc1(f0, s3, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, s3, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s2, 784);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22D96Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = addiu(s2, 1040);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22D97Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = addiu(s2, 272);
    a1 = addiu(sp, 0x98);
    jal(ctx, 0x22D98Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s2, 784);
    a1 = addiu(sp, 0x94);
    jal(ctx, 0x22D99Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s2, 528);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x22D9ACu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s2, 1040);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x22D9BCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s1;
    a1 = 10;
    jal(ctx, 0x22D9CCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x42700000;
    mtc1(v1, f0);
    add_s(f0, f0, f25);
    swc1(f0, sp, 0x70);
    v1 = 0x429E0000;
    mtc1(v1, f0);
    add_s(f0, f0, f24);
    swc1(f0, sp, 0x74);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s2, 1584);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22DA1Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = addiu(s2, 1840);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22DA2Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = addiu(s2, 1584);
    a1 = addiu(sp, 0x98);
    jal(ctx, 0x22DA3Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s2, 1840);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x22DA4Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    v0 = 0x42CC0000;
    mtc1(v0, f0);
    add_s(f1, f0, f25);
    v0 = 0x40000000;
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    swc1(f21, sp, 0x70);
    v0 = 0x42900000;
    mtc1(v0, f0);
    add_s(f20, f0, f24);
    swc1(f20, sp, 0x74);
    a0 = addiu(s2, 2144);
    lw(a1, s2, 2100);
    a2 = addiu(sp, 0x70);
    jal(ctx, 0x22DA98u, gen::fn_sub_22EB30_0022eb30);
    lw(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0022dab0
        charge(ctx, 4);
        lw(v1, s2, 2096);
        v0 = 8;
        if (v1 != v0) {
            goto L_0022dae0;
        }
        // 0x0022dac0
        charge(ctx, 8);
        v0 = 120;
        sb(v0, sp, 0x9C);
        sb(v0, sp, 0x9D);
        sb(v0, sp, 0x9E);
        v0 = 255;
        sb(v0, sp, 0x9F);
        goto L_0022daf4;
    }
L_0022dae0:
    charge(ctx, 5);
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    sb(v0, sp, 0x9F);
L_0022daf4:
    charge(ctx, 3);
    s3 = 0;
    for (;;) {  // while (s3 < 3)
        // 0x0022db1c
        charge(ctx, 3);
        v0 = slti(s3, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022db00
        charge(ctx, 7);
        v0 = sll(s3, 8);
        v0 = addu(s2, v0);
        a0 = addiu(v0, 2144);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x22DB10u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s3 = addiu(s3, 1);
    }
    // 0x0022db28
    charge(ctx, 15);
    swc1(f21, sp, 0x70);
    v0 = 0x41600000;
    mtc1(v0, f0);
    add_s(f0, f0, f20);
    swc1(f0, sp, 0x74);
    a0 = addiu(s2, 2912);
    lw(a1, s2, 2108);
    a2 = addiu(sp, 0x70);
    jal(ctx, 0x22DB4Cu, gen::fn_sub_22EB30_0022eb30);
    lw(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0022db64
        charge(ctx, 4);
        lw(v1, s2, 2096);
        v0 = 8;
        if (v1 != v0) {
            goto L_0022db94;
        }
        // 0x0022db74
        charge(ctx, 8);
        v0 = 120;
        sb(v0, sp, 0x9C);
        sb(v0, sp, 0x9D);
        sb(v0, sp, 0x9E);
        v0 = 255;
        sb(v0, sp, 0x9F);
        goto L_0022dba8;
    }
L_0022db94:
    charge(ctx, 5);
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    sb(v0, sp, 0x9F);
L_0022dba8:
    charge(ctx, 3);
    s3 = 0;
    for (;;) {  // while (s3 < 3)
        // 0x0022dbd0
        charge(ctx, 3);
        v0 = slti(s3, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022dbb4
        charge(ctx, 7);
        v0 = sll(s3, 8);
        v0 = addu(s2, v0);
        a0 = addiu(v0, 2912);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x22DBC4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s3 = addiu(s3, 1);
    }
    // 0x0022dbdc
    charge(ctx, 62);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x22DBE4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x42820000;
    mtc1(v1, f0);
    add_s(f20, f0, f25);
    swc1(f20, sp, 0x70);
    v1 = 0x42A60000;
    mtc1(v1, f0);
    add_s(f0, f0, f24);
    swc1(f0, sp, 0x74);
    lw(a0, v0, kSpW);
    lw(v1, s2, 2100);
    mult(a0, a0, v1);
    lw(v1, s2, 2104);
    div(a0, v1);
    mflo(v1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s2, 3680);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22DC50u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s0;
    a1 = 3;
    jal(ctx, 0x22DC60u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f20, sp, 0x70);
    v1 = 0x42B20000;
    mtc1(v1, f0);
    add_s(f0, f0, f24);
    swc1(f0, sp, 0x74);
    lw(a0, v0, kSpW);
    lw(v1, s2, 2108);
    mult(a0, a0, v1);
    lw(v1, s2, 2112);
    div(a0, v1);
    mflo(v1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s2, 3936);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22DCBCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    lw(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0022dcd4
        charge(ctx, 4);
        lw(v1, s2, 2096);
        v0 = 8;
        if (v1 != v0) {
            goto L_0022dd08;
        }
        // 0x0022dce4
        charge(ctx, 9);
        v0 = 215;
        sb(v0, sp, 0x9C);
        v1 = 255;
        sb(v1, sp, 0x9D);
        v0 = 145;
        sb(v0, sp, 0x9E);
        sb(v1, sp, 0x9F);
        goto L_0022dd1c;
    }
L_0022dd08:
    charge(ctx, 5);
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    sb(v0, sp, 0x9F);
L_0022dd1c:
    charge(ctx, 8);
    a0 = addiu(s2, 3936);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x22DD24u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s2, 0);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0022dd3c
        charge(ctx, 32);
        lw(a0, s2, 1320);
        jal(ctx, 0x22DD40u, gen::fn_sub_22E850_0022e850);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x22DD50u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x42E80000;
        mtc1(v1, f0);
        add_s(f0, f0, f25);
        swc1(f0, sp, 0x70);
        v1 = 0x422C0000;
        mtc1(v1, f0);
        add_s(f0, f0, f24);
        swc1(f0, sp, 0x74);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x78);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x7C);
        a0 = addiu(s2, 1328);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x22DDA0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s0 = 0;
        lw(v0, s2, 0);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x0022ddbc
            charge(ctx, 4);
            lw(v1, s2, 2096);
            v0 = 8;
            if (v1 != v0) {
                goto L_0022de98;
            }
            // 0x0022ddcc
            charge(ctx, 4);
            lw(v0, s2, 1320);
            at = sltiu(v0, 6);
            if (at != 0) {
                // 0x0022dddc
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 30576);  // &0x7B7770
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x22DDF8u:  // table[0]
                    // 0x0022ddf8
                    charge(ctx, 7);
                    a0 = 0x690000;
                    a0 = addiu(a0, -6512);  // "bpp_panel.c"
                    a1 = 873;
                    jal(ctx, 0x22DE04u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 873): `jr $ra` in retail, execution goes on
                    break;
                case 0x22DE14u:  // table[1]
                    // 0x0022de14
                    charge(ctx, 2);
                    break;
                case 0x22DE1Cu:  // table[2]
                    // 0x0022de1c
                    charge(ctx, 3);
                    s0 = 1;
                    break;
                case 0x22DE28u:  // table[3]
                    // 0x0022de28
                    charge(ctx, 3);
                    s0 = 2;
                    break;
                case 0x22DE34u:  // table[4]
                    // 0x0022de34
                    charge(ctx, 3);
                    s0 = 3;
                    break;
                case 0x22DE40u:  // table[5]
                    // 0x0022de40
                    charge(ctx, 1);
                    s0 = 4;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x0022de44
            charge(ctx, 21);
            v0 = sll(s0, 1);
            v1 = addu(v0, s0);
            v0 = 0x690000;
            v0 = addiu(v0, -6952);  // &0x68E4D8
            v0 = addu(v0, v1);
            lbu(v0, v0, 0);
            sb(v0, sp, 0x9C);
            v0 = 0x690000;
            v0 = addiu(v0, -6951);  // &0x68E4D9
            v0 = addu(v0, v1);
            lbu(v0, v0, 0);
            sb(v0, sp, 0x9D);
            v0 = 0x690000;
            v0 = addiu(v0, -6950);  // &0x68E4DA
            v0 = addu(v0, v1);
            lbu(v0, v0, 0);
            sb(v0, sp, 0x9E);
            v0 = 255;
            sb(v0, sp, 0x9F);
            goto L_0022deac;
        }
    L_0022de98:
        charge(ctx, 5);
        v0 = 255;
        sb(v0, sp, 0x9C);
        sb(v0, sp, 0x9D);
        sb(v0, sp, 0x9E);
        sb(v0, sp, 0x9F);
    L_0022deac:
        charge(ctx, 4);
        a0 = addiu(s2, 1328);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x22DEB4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    }
    // 0x0022debc
    charge(ctx, 4);
    lw(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0022decc
        charge(ctx, 3);
        a0 = s2;
        jal(ctx, 0x22DED0u, gen::fn_sub_22FA80_0022fa80);
    }
    // 0x0022ded8 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x0022DF10 sub_22DF10 -- 2156 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_Draw](panel) draws the member panel: render states, portrait / frame / bar quads as Im2D triangle
// pairs, the HP / SP bars and digits, the ailment icon (sub_232EA0).
void sub_22DF10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022df10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(v0, a0, kBpnFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0022df44
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 912;
        jal(ctx, 0x22DF50u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 912): `jr $ra` in retail, execution goes on
    }
    // 0x0022df58
    charge(ctx, 45);
    a0 = 3;
    jal(ctx, 0x22DF5Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s3 = v0;
    a0 = 5;
    jal(ctx, 0x22DF6Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    lhu(a0, s4, kBpnId);
    jal(ctx, 0x22DF7Cu, gen::fn_sub_21C450_0021c450);  // [bpRes_GetSetById](u16 id): a member's sprite set
    s1 = v0;
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 20;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22DF9Cu, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22DFB0u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22DFC4u, v0.u());
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x22DFD4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x22DFE0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22DFF4u, v0.u());
    lw(v0, s4, kBpnFlags);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x0022e00c
        charge(ctx, 31);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22E018u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22E028u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s5 = 0x960000;
        s5 = addiu(s5, 156);  // &0x96009C
        a0 = addiu(s4, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E050u, v0.u());
        a0 = addiu(s4, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E070u, v0.u());
        lw(v0, s4, kBpnFlags);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x0022e088
            charge(ctx, 4);
            lw(v1, s4, kBpnIcon);
            v0 = 8;
            if (v1 != v0) {
                goto L_0022e098;
            }
            goto L_0022e104;
        }
    L_0022e098:
        charge(ctx, 27);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x22E0A4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x22E0B4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s5 = 0x960000;
        s5 = addiu(s5, 156);  // &0x96009C
        a0 = addiu(s4, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E0DCu, v0.u());
        a0 = addiu(s4, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E0FCu, v0.u());
    }
L_0022e104:
    charge(ctx, 31);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x22E110u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x22E120u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s5 = 0x960000;
    s5 = addiu(s5, 156);  // &0x96009C
    a0 = addiu(s4, 272);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E148u, v0.u());
    a0 = addiu(s4, 272);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E168u, v0.u());
    lw(a0, s4, 0);
    v0 = a0 & 0x20;
    if (v0 != 0) {
        // 0x0022e180
        charge(ctx, 3);
        v0 = a0 & 0x4;
        if (v0 != 0) {
            // 0x0022e18c
            charge(ctx, 4);
            lw(v1, s4, 2096);
            v0 = 8;
            if (v1 != v0) {
                goto L_0022e1b4;
            }
            goto L_0022e19c;
        }
    L_0022e1b4:
        charge(ctx, 27);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x22E1C0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x22E1D0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s5 = 0x960000;
        s5 = addiu(s5, 156);  // &0x96009C
        a0 = addiu(s4, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E1F8u, v0.u());
        a0 = addiu(s4, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s5, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E218u, v0.u());
        goto L_0022e220;
    }
L_0022e19c:
    charge(ctx, 3);
    v0 = a0 & 0x8;
    if (v0 != 0) {
        goto L_0022e1b4;
    }
    // 0x0022e1a8
    charge(ctx, 3);
    v0 = a0 & 0x100;
    if (v0 != 0) {
        goto L_0022e1b4;
    }
L_0022e220:
    charge(ctx, 73);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x22E22Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x22E23Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x22E24Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s5 = 0x960000;
    s5 = addiu(s5, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x22E260u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22E274u, v0.u());
    s1 = 0x960000;
    s1 = addiu(s1, 156);  // &0x96009C
    a0 = addiu(s4, 16);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E29Cu, v0.u());
    a0 = addiu(s4, 16);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E2BCu, v0.u());
    a0 = s3;
    a1 = 10;
    jal(ctx, 0x22E2CCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x22E2D8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22E2ECu, v0.u());
    a0 = addiu(s4, 1584);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E30Cu, v0.u());
    a0 = addiu(s4, 1584);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E32Cu, v0.u());
    lw(a0, s4, 0);
    v0 = a0 & 0x20;
    if (v0 != 0) {
        // 0x0022e344
        charge(ctx, 3);
        v0 = a0 & 0x4;
        if (v0 != 0) {
            // 0x0022e350
            charge(ctx, 4);
            lw(v1, s4, 2096);
            v0 = 8;
            if (v1 != v0) {
                goto L_0022e378;
            }
            goto L_0022e360;
        }
    L_0022e378:
        charge(ctx, 27);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x22E384u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x22E394u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s1 = 0x960000;
        s1 = addiu(s1, 156);  // &0x96009C
        a0 = addiu(s4, 1840);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E3BCu, v0.u());
        a0 = addiu(s4, 1840);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22E3DCu, v0.u());
        goto L_0022e3e4;
    }
L_0022e360:
    charge(ctx, 3);
    v0 = a0 & 0x8;
    if (v0 != 0) {
        goto L_0022e378;
    }
    // 0x0022e36c
    charge(ctx, 3);
    v0 = a0 & 0x100;
    if (v0 != 0) {
        goto L_0022e378;
    }
L_0022e3e4:
    charge(ctx, 181);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x22E3F0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x22E400u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = s3;
    a1 = 0;
    jal(ctx, 0x22E410u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s5 = 0x960000;
    s5 = addiu(s5, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x22E424u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22E438u, v0.u());
    s1 = 0x960000;
    s1 = addiu(s1, 156);  // &0x96009C
    a0 = addiu(s4, 2144);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E460u, v0.u());
    a0 = addiu(s4, 2144);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E480u, v0.u());
    a0 = addiu(s4, 2400);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E4A0u, v0.u());
    a0 = addiu(s4, 2400);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E4C0u, v0.u());
    a0 = addiu(s4, 2656);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E4E0u, v0.u());
    a0 = addiu(s4, 2656);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E500u, v0.u());
    a0 = addiu(s4, 2912);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E520u, v0.u());
    a0 = addiu(s4, 2912);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E540u, v0.u());
    a0 = addiu(s4, 3168);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E560u, v0.u());
    a0 = addiu(s4, 3168);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E580u, v0.u());
    a0 = addiu(s4, 3424);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E5A0u, v0.u());
    a0 = addiu(s4, 3424);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E5C0u, v0.u());
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x22E5D0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x22E5DCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22E5F0u, v0.u());
    a0 = addiu(s4, 3680);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E610u, v0.u());
    a0 = addiu(s4, 3680);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E630u, v0.u());
    a0 = s2;
    a1 = 3;
    jal(ctx, 0x22E640u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x22E64Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s5, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22E660u, v0.u());
    a0 = addiu(s4, 3936);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E680u, v0.u());
    a0 = addiu(s4, 3936);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22E6A0u, v0.u());
    lw(v1, s4, 0);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0022e6b8
        charge(ctx, 32);
        lw(a0, s4, 1320);
        jal(ctx, 0x22E6BCu, gen::fn_sub_22E850_0022e850);
        a0 = s3;
        a1 = v0;
        jal(ctx, 0x22E6CCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x22E6D8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s0, 0);
        jalr(ctx, 0x22E6ECu, v0.u());
        s0 = s1;
        a0 = addiu(s4, 1328);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);
        jalr(ctx, 0x22E710u, v0.u());
        a0 = addiu(s4, 1328);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);
        jalr(ctx, 0x22E730u, v0.u());
    }
    // 0x0022e738
    charge(ctx, 4);
    lw(v1, s4, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0022e748
        charge(ctx, 3);
        a0 = s4;
        jal(ctx, 0x22E74Cu, gen::fn_sub_232EA0_00232ea0);
    }
    // 0x0022e754 (the shared epilogue, written out on this path)
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

// 0x0022E900 sub_22E900 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_SetHp](panel, hp) stores the HP, sets its digits (sub_22EA40) and the HP bar (set 5 page 2).
void sub_22E900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0022e900
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 5;
    jal(ctx, 0x22E920u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x22E930u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s0 = v0;
    sw(s1, s2, kBpnHp);
    a0 = addiu(s2, kBpnHpDigits);
    a1 = s1;
    jal(ctx, 0x22E948u, gen::fn_sub_22EA40_0022ea40);
    lwc1(f0, s2, kBpnMaxHp);
    cvt_s_w(f1, f0);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    div_s(f12, f0, f1);
    a0 = addiu(s2, kBpnHpBar);
    a1 = s0;
    jal(ctx, 0x22E974u, gen::fn_sub_22ECB0_0022ecb0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0022E9A0 sub_22E9A0 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_SetSp](panel, sp) stores the SP, its digits and the SP bar (set 5 page 3).
void sub_22E9A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0022e9a0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 5;
    jal(ctx, 0x22E9C0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    a0 = v0;
    a1 = 3;
    jal(ctx, 0x22E9D0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s0 = v0;
    sw(s1, s2, kBpnSp);
    a0 = addiu(s2, kBpnSpDigits);
    a1 = s1;
    jal(ctx, 0x22E9E8u, gen::fn_sub_22EA40_0022ea40);
    lwc1(f0, s2, kBpnMaxSp);
    cvt_s_w(f1, f0);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    div_s(f12, f0, f1);
    a0 = addiu(s2, kBpnSpBar);
    a1 = s0;
    jal(ctx, 0x22EA14u, gen::fn_sub_22ECB0_0022ecb0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0022EA40 sub_22EA40 -- 228 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_SetDigitPages](quads, n) prints n with the format at 0x7CC458 (at most three digits, K_Assert 1114)
// and gives each quad its digit's page of panel set 3, the last digit first.
void sub_22EA40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022ea40
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = a1;
    a0 = 3;
    jal(ctx, 0x22EA64u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    a0 = addiu(sp, 0x50);
    a1 = addiu(gp, -26776);  // "%d"
    a2 = s0;
    jal(ctx, 0x22EA7Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x22EA88u, gen::fn_strlen_00524388);
    s0 = v0;
    at = slti(s0, 4);
    if (at == 0) {
        // 0x0022eaa0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 1114;
        jal(ctx, 0x22EAACu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 1114): `jr $ra` in retail, execution goes on
    }
    // 0x0022eab4
    charge(ctx, 3);
    s1 = 0;
    for (;;) {  // while (s1 < s0)
        // 0x0022eaf8
        charge(ctx, 3);
        v1 = slt(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022eac0
        charge(ctx, 14);
        v0 = addiu(s0, -1);
        v0 = subu(v0, s1);
        v0 = addu(v0, sp);
        lb(v0, v0, 80);
        a1 = addiu(v0, -48);
        a0 = s2;
        jal(ctx, 0x22EAD8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = sll(s1, 8);
        a0 = addu(s3, v1);
        a1 = v0;
        jal(ctx, 0x22EAECu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
        s1 = addiu(s1, 1);
    }
    // 0x0022eb04
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x0022EB30 sub_22EB30 -- 376 bytes; frame 0x170: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_PlaceDigits](quads, n, xy*) places the digits of n right-aligned, 16 px apart (x = x0 + 16 (2 - i));
// unused quads get a zero-size rectangle (K_Assert 1137 for four digits).
void sub_22EB30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0022eb30
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s0 = a1;
    s3 = a2;
    a0 = 3;
    jal(ctx, 0x22EB5Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    a0 = addiu(sp, 0x60);
    a1 = addiu(gp, -26776);  // "%d"
    a2 = s0;
    jal(ctx, 0x22EB74u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x60);
    jal(ctx, 0x22EB80u, gen::fn_strlen_00524388);
    s0 = v0;
    at = slti(s0, 4);
    if (at == 0) {
        // 0x0022eb98
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 1137;
        jal(ctx, 0x22EBA4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 1137): `jr $ra` in retail, execution goes on
    }
    // 0x0022ebac
    charge(ctx, 3);
    s1 = 0;
    for (;;) {  // while (s1 < s0)
        // 0x0022ec34
        charge(ctx, 3);
        v1 = slt(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022ebb8
        charge(ctx, 31);
        v0 = addiu(s0, -1);
        v0 = subu(v0, s1);
        v0 = addu(v0, sp);
        lb(v0, v0, 96);
        a1 = addiu(v0, -48);
        a0 = s2;
        jal(ctx, 0x22EBD0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 2;
        v1 = subu(v1, s1);
        v1 = sll(v1, 4);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s3, 0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x160);
        lwc1(f0, s3, 4);
        swc1(f0, sp, 0x164);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x168);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x16C);
        v0 = sll(s1, 8);
        a0 = addu(s4, v0);
        a1 = addiu(sp, 0x160);
        jal(ctx, 0x22EC28u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s1 = addiu(s1, 1);
    }
    // 0x0022ec40
    charge(ctx, 2);
    for (;;) {  // while (s0 < 3)
        // 0x0022ec78
        charge(ctx, 3);
        v1 = slti(s0, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022ec48
        charge(ctx, 12);
        lwc1(f0, s3, 0);
        swc1(f0, sp, 0x160);
        lwc1(f0, s3, 4);
        swc1(f0, sp, 0x164);
        sw(zero, sp, 0x168);
        sw(zero, sp, 0x16C);
        v0 = sll(s0, 8);
        a0 = addu(s4, v0);
        a1 = addiu(sp, 0x160);
        jal(ctx, 0x22EC6Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s0 = addiu(s0, 1);
    }
    // 0x0022ec84
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x0022ECB0 sub_22ECB0 -- 1284 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [bppPanel_SetBar](im2d quad, page) fills a 4-vertex Im2D quad from a page: uv from sub_21CD00, z =
// g_rwIm2DNearScreenZ, 1 / w from the camera, the four corner colours as floats.
void sub_22ECB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0022ecb0
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mov_s(f21, f12);
    jal(ctx, 0x22ECD4u, gen::fn_sub_198590_00198590);  // the current camera / render context
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f20, f1, f0);
    a0 = s0;
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x22ECF8u, gen::fn_sub_21CD00_0021cd00);  // (page, uv*) -> the page's uv rectangle
    lwc1(f2, sp, 0x40);
    lwc1(f0, sp, 0x48);
    sub_s(f1, f0, f2);
    mtc1(zero, f0);
    adda_s(f0, f2);
    madd_s(f0, f21, f1);
    swc1(f0, sp, 0x48);
    swc1(f2, s1, 16);
    lwc1(f0, sp, 0x44);
    swc1(f0, s1, 20);
    swc1(f20, s1, 24);
    v1 = 0x960000;
    v1 = addiu(v1, 136);  // &g_rwIm2DNearScreenZ
    lwc1(f0, v1, 0);  // g_rwIm2DNearScreenZ
    swc1(f0, s1, 8);
    lbu(a0, s0, 28);
    if (i64(a0) < 0) {
        // 0x0022ed60
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022ed4c
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022ed7c
    charge(ctx, 4);
    swc1(f0, s1, 32);
    lbu(a0, s0, 29);
    if (i64(a0) < 0) {
        // 0x0022eda0
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022ed8c
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022edbc
    charge(ctx, 4);
    swc1(f0, s1, 36);
    lbu(a0, s0, 30);
    if (i64(a0) < 0) {
        // 0x0022ede0
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022edcc
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022edfc
    charge(ctx, 4);
    swc1(f0, s1, 40);
    lbu(a0, s0, 31);
    if (i64(a0) < 0) {
        // 0x0022ee20
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022ee0c
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022ee3c
    charge(ctx, 11);
    swc1(f0, s1, 44);
    lwc1(f0, sp, 0x48);
    swc1(f0, s1, 80);
    lwc1(f0, sp, 0x44);
    swc1(f0, s1, 84);
    swc1(f20, s1, 88);
    lwc1(f0, v1, 0);
    swc1(f0, s1, 72);
    lbu(a0, s0, 32);
    if (i64(a0) < 0) {
        // 0x0022ee7c
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022ee68
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022ee98
    charge(ctx, 4);
    swc1(f0, s1, 96);
    lbu(a0, s0, 33);
    if (i64(a0) < 0) {
        // 0x0022eebc
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022eea8
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022eed8
    charge(ctx, 4);
    swc1(f0, s1, 100);
    lbu(a0, s0, 34);
    if (i64(a0) < 0) {
        // 0x0022eefc
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022eee8
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022ef18
    charge(ctx, 4);
    swc1(f0, s1, 104);
    lbu(a0, s0, 35);
    if (i64(a0) < 0) {
        // 0x0022ef3c
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022ef28
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022ef58
    charge(ctx, 11);
    swc1(f0, s1, 108);
    lwc1(f0, sp, 0x48);
    swc1(f0, s1, 144);
    lwc1(f0, sp, 0x4C);
    swc1(f0, s1, 148);
    swc1(f20, s1, 152);
    lwc1(f0, v1, 0);
    swc1(f0, s1, 136);
    lbu(a0, s0, 36);
    if (i64(a0) < 0) {
        // 0x0022ef98
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022ef84
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022efb4
    charge(ctx, 4);
    swc1(f0, s1, 160);
    lbu(a0, s0, 37);
    if (i64(a0) < 0) {
        // 0x0022efd8
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022efc4
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022eff4
    charge(ctx, 4);
    swc1(f0, s1, 164);
    lbu(a0, s0, 38);
    if (i64(a0) < 0) {
        // 0x0022f018
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022f004
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022f034
    charge(ctx, 4);
    swc1(f0, s1, 168);
    lbu(a0, s0, 39);
    if (i64(a0) < 0) {
        // 0x0022f058
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022f044
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022f074
    charge(ctx, 11);
    swc1(f0, s1, 172);
    lwc1(f0, sp, 0x40);
    swc1(f0, s1, 208);
    lwc1(f0, sp, 0x4C);
    swc1(f0, s1, 212);
    swc1(f20, s1, 216);
    lwc1(f0, v1, 0);
    swc1(f0, s1, 200);
    lbu(v1, s0, 40);
    if (i64(v1) < 0) {
        // 0x0022f0b4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022f0a0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022f0d0
    charge(ctx, 4);
    swc1(f0, s1, 224);
    lbu(v1, s0, 41);
    if (i64(v1) < 0) {
        // 0x0022f0f4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022f0e0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022f110
    charge(ctx, 4);
    swc1(f0, s1, 228);
    lbu(v1, s0, 42);
    if (i64(v1) < 0) {
        // 0x0022f134
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022f120
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022f150
    charge(ctx, 4);
    swc1(f0, s1, 232);
    lbu(v1, s0, 43);
    if (i64(v1) < 0) {
        // 0x0022f174
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0022f160
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022f190 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    swc1(f0, s1, 236);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0022F1C0 sub_22F1C0 -- 484 bytes; frame 0x10: ra sp+0x0
// [bppPanel_SetAilment](panel, bits) maps the ailment bits to an icon (0x80000 -> 8, 0x200 -> 10, 0x80 -> 7,
// 0x40 -> 6, 0x20 -> 5, 0x10 -> 4, 8 -> 3, 4 -> 2, 2 -> 1, 1 -> 0: one bit exactly) and sets the icon (sub_22F3B0) with flag
// bit 2; other values clear it.
void sub_22F1C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022f1c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, kBpnFlags);
    v1 = a2 & 0x4;
    if (v1 != 0) {
        // 0x0022f1d8
        charge(ctx, 3);
        v1 = si(-5);
        v1 = a2 & v1;
        sw(v1, a0, kBpnFlags);
    }
    // 0x0022f1e4
    charge(ctx, 4);
    v1 = 0x80000;
    v1 = a1 & v1;
    if (v1 == 0) {
        // 0x0022f210
        charge(ctx, 5);
        a1 = dsll32(a1, 12);
        a1 = dsrl32(a1, 12);
        v1 = 512;
        if (a1 == v1) {
            // 0x0022f368
            charge(ctx, 5);
            v1 = 10;
            sw(v1, a0, kBpnIcon);
            lw(v1, a0, kBpnFlags);
            v1 = v1 | 0x4;
            sw(v1, a0, kBpnFlags);
        } else {
            // 0x0022f224
            charge(ctx, 3);
            v1 = 128;
            if (a1 == v1) {
                // 0x0022f34c
                charge(ctx, 7);
                v1 = 7;
                sw(v1, a0, kBpnIcon);
                lw(v1, a0, kBpnFlags);
                v1 = v1 | 0x4;
                sw(v1, a0, kBpnFlags);
            } else {
                // 0x0022f230
                charge(ctx, 3);
                v1 = 64;
                if (a1 == v1) {
                    // 0x0022f330
                    charge(ctx, 7);
                    v1 = 6;
                    sw(v1, a0, kBpnIcon);
                    lw(v1, a0, kBpnFlags);
                    v1 = v1 | 0x4;
                    sw(v1, a0, kBpnFlags);
                } else {
                    // 0x0022f23c
                    charge(ctx, 3);
                    v1 = 32;
                    if (a1 == v1) {
                        // 0x0022f314
                        charge(ctx, 7);
                        v1 = 5;
                        sw(v1, a0, kBpnIcon);
                        lw(v1, a0, kBpnFlags);
                        v1 = v1 | 0x4;
                        sw(v1, a0, kBpnFlags);
                    } else {
                        // 0x0022f248
                        charge(ctx, 3);
                        v1 = 16;
                        if (a1 == v1) {
                            // 0x0022f2f8
                            charge(ctx, 7);
                            v1 = 4;
                            sw(v1, a0, kBpnIcon);
                            lw(v1, a0, kBpnFlags);
                            v1 = v1 | 0x4;
                            sw(v1, a0, kBpnFlags);
                        } else {
                            // 0x0022f254
                            charge(ctx, 3);
                            v1 = 8;
                            if (a1 == v1) {
                                // 0x0022f2dc
                                charge(ctx, 7);
                                v1 = 3;
                                sw(v1, a0, kBpnIcon);
                                lw(v1, a0, kBpnFlags);
                                v1 = v1 | 0x4;
                                sw(v1, a0, kBpnFlags);
                            } else {
                                // 0x0022f260
                                charge(ctx, 3);
                                v1 = 4;
                                if (a1 == v1) {
                                    // 0x0022f2c0
                                    charge(ctx, 7);
                                    v1 = 2;
                                    sw(v1, a0, kBpnIcon);
                                    lw(v1, a0, kBpnFlags);
                                    v1 = v1 | 0x4;
                                    sw(v1, a0, kBpnFlags);
                                } else {
                                    // 0x0022f26c
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (a1 == v1) {
                                        // 0x0022f2a4
                                        charge(ctx, 7);
                                        v1 = 1;
                                        sw(v1, a0, kBpnIcon);
                                        lw(v1, a0, kBpnFlags);
                                        v1 = v1 | 0x4;
                                        sw(v1, a0, kBpnFlags);
                                    } else {
                                        // 0x0022f278
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (a1 == v1) {
                                            // 0x0022f28c
                                            charge(ctx, 6);
                                            sw(zero, a0, kBpnIcon);
                                            lw(v1, a0, kBpnFlags);
                                            v1 = v1 | 0x4;
                                            sw(v1, a0, kBpnFlags);
                                        } else {
                                            // 0x0022f284
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        // 0x0022f1f4
        charge(ctx, 7);
        v1 = 8;
        sw(v1, a0, kBpnIcon);
        lw(v1, a0, kBpnFlags);
        v1 = v1 | 0x4;
        sw(v1, a0, kBpnFlags);
    }
    // 0x0022f37c
    charge(ctx, 4);
    lw(v1, a0, kBpnFlags);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0022f38c
        charge(ctx, 2);
        jal(ctx, 0x22F38Cu, gen::fn_sub_22F3B0_0022f3b0);
    }
    // 0x0022f394 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0022F3B0 sub_22F3B0 -- 1744 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_SetIconQuads](panel) sets the ailment icon's quads for icon +2096 (jump table 0x7B77B0).
void sub_22F3B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0022f3b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 4;
    jal(ctx, 0x22F3D8u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s0 = v0;
    lw(v1, s2, kBpnIcon);
    at = sltiu(v1, 11);
    if (at != 0) {
        // 0x0022f3f4
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 30640);  // &0x7B77B0
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x22F410u:  // table[0]
            // 0x0022f410
            charge(ctx, 9);
            s2 = addiu(s2, 4192);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x22F41Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s1 = v0;
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x0022f44c
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f434
                charge(ctx, 6);
                v0 = sll(s0, 8);
                a0 = addu(s2, v0);
                a1 = s1;
                jal(ctx, 0x22F440u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                s0 = addiu(s0, 1);
            }
            // 0x0022f458
            charge(ctx, 3);
            sw(zero, s2, 780);
            break;
        case 0x22F464u:  // table[1]
            // 0x0022f464
            charge(ctx, 4);
            s2 = addiu(s2, 4192);
            s3 = 0;
            for (;;) {  // while (s3 < 3)
                // 0x0022f4c0
                charge(ctx, 3);
                v1 = slti(s3, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f474
                charge(ctx, 19);
                a0 = s0;
                a1 = 1;
                jal(ctx, 0x22F47Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                v1 = sll(s3, 9);
                s1 = addu(s2, v1);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x22F494u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                a0 = s0;
                a1 = 2;
                jal(ctx, 0x22F4A4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                a0 = addiu(s1, 256);
                a1 = v0;
                jal(ctx, 0x22F4B4u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                s3 = addiu(s3, 1);
            }
            // 0x0022f4cc
            charge(ctx, 3);
            sw(zero, s2, 1548);
            break;
        case 0x22F4D8u:  // table[2]
            // 0x0022f4d8
            charge(ctx, 4);
            s4 = addiu(s2, 4192);
            s5 = 0;
            for (;;) {  // while (s5 < 3)
                // 0x0022f60c
                charge(ctx, 3);
                v1 = slti(s5, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f4e8
                charge(ctx, 13);
                s3 = addu(s4, s5);
                s2 = addiu(s3, 780);
                jal(ctx, 0x22F4F0u, gen::fn_sub_488F30_00488f30);
                a2 = 5;
                divu(v0, a2);
                mfhi(v0);
                sb(v0, s2, 0);
                sb(s5, s3, 783);
                lb(a0, s2, 0);
                v1 = 4;
                if (a0 == v1) {
                    // 0x0022f5bc
                    charge(ctx, 5);
                    a0 = s0;
                    a1 = 7;
                    jal(ctx, 0x22F5C4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s1 = v0;
                } else {
                    // 0x0022f51c
                    charge(ctx, 3);
                    a1 = 3;
                    if (a0 == a1) {
                        // 0x0022f5a0
                        charge(ctx, 7);
                        a0 = s0;
                        a1 = 6;
                        jal(ctx, 0x22F5A8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s1 = v0;
                    } else {
                        // 0x0022f528
                        charge(ctx, 3);
                        v0 = 2;
                        if (a0 == v0) {
                            // 0x0022f584
                            charge(ctx, 7);
                            a0 = s0;
                            a1 = a2;
                            jal(ctx, 0x22F58Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                            s1 = v0;
                        } else {
                            // 0x0022f534
                            charge(ctx, 3);
                            v0 = 1;
                            if (a0 == v0) {
                                // 0x0022f568
                                charge(ctx, 7);
                                a0 = s0;
                                a1 = v1;
                                jal(ctx, 0x22F570u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                s1 = v0;
                            } else {
                                // 0x0022f540
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x0022f550
                                    charge(ctx, 6);
                                    a0 = s0;
                                    jal(ctx, 0x22F554u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                    s1 = v0;
                                } else {
                                    // 0x0022f548
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
                // 0x0022f5d0
                charge(ctx, 15);
                v0 = sll(s5, 8);
                a0 = addu(s4, v0);
                a1 = s1;
                jal(ctx, 0x22F5DCu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                v1 = sll(s5, 1);
                v1 = addu(v1, s5);
                a0 = sll(v1, 2);
                v1 = 3;
                div(a0, v1);
                mflo(a0);
                v1 = sll(s5, 2);
                v1 = addu(s4, v1);
                sw(a0, v1, 768);
                s5 = addiu(s5, 1);
            }
            // 0x0022f618
            charge(ctx, 3);
            sw(zero, s4, 788);
            break;
        case 0x22F624u:  // table[3]
            // 0x0022f624
            charge(ctx, 35);
            s1 = addiu(s2, 4192);
            a0 = s0;
            a1 = 8;
            jal(ctx, 0x22F630u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x22F644u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            a0 = addiu(s1, 256);
            a1 = s0;
            jal(ctx, 0x22F654u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            a0 = s0;
            a1 = addiu(sp, 0x70);
            jal(ctx, 0x22F664u, gen::fn_sub_21CD00_0021cd00);  // (page, uv*) -> the page's uv rectangle
            lwc1(f1, sp, 0x70);
            lwc1(f0, sp, 0x78);
            swc1(f0, sp, 0x70);
            swc1(f1, sp, 0x78);
            a0 = addiu(s1, 256);
            a1 = addiu(sp, 0x70);
            jal(ctx, 0x22F684u, gen::fn_sub_21EAE0_0021eae0);  // (quad, uv*)
            jal(ctx, 0x22F68Cu, gen::fn_sub_488F30_00488f30);
            a2 = 30;
            divu(v0, a2);
            mfhi(v1);
            sw(v1, s1, 524);
            a3 = 0;
            for (;;) {  // while (a3 < 2)
                // 0x0022f6fc
                charge(ctx, 3);
                v1 = slti(a3, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f6b0
                charge(ctx, 10);
                v1 = sll(a3, 2);
                v1 = addu(s1, v1);
                a1 = addiu(v1, 512);
                v1 = sll(a3, 4);
                a0 = subu(v1, a3);
                v1 = sll(a0, 1);
                a0 = dsll32(a0, 1);
                a0 = dsra32(a0, 1);
                if (i64(v1) < 0) {
                    // 0x0022f6d8
                    charge(ctx, 2);
                    v1 = addiu(v1, 1);
                    a0 = sra(v1, 1);
                }
                // 0x0022f6e0
                charge(ctx, 7);
                lw(v1, s1, 524);
                v1 = addu(v1, a0);
                sw(v1, a1, 0);
                div(v1, a2);
                mfhi(v1);
                sw(v1, a1, 0);
                a3 = addiu(a3, 1);
            }
            // 0x0022f708
            charge(ctx, 2);
            break;
        case 0x22F710u:  // table[4, 10]
            // 0x0022f710
            charge(ctx, 4);
            s4 = addiu(s2, 4192);
            s5 = 0;
            for (;;) {  // while (s5 < 2)
                // 0x0022f7d0
                charge(ctx, 3);
                v1 = slti(s5, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f720
                charge(ctx, 11);
                s3 = addu(s4, s5);
                s2 = addiu(s3, 520);
                jal(ctx, 0x22F728u, gen::fn_sub_488F30_00488f30);
                v0 = v0 & 0x1;
                sb(v0, s2, 0);
                sb(s5, s3, 522);
                lb(v1, s2, 0);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0022f778
                    charge(ctx, 5);
                    a0 = s0;
                    a1 = 9;
                    jal(ctx, 0x22F780u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s1 = v0;
                } else {
                    // 0x0022f74c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0022f75c
                        charge(ctx, 7);
                        a0 = s0;
                        a1 = 9;
                        jal(ctx, 0x22F764u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s1 = v0;
                    } else {
                        // 0x0022f754
                        charge(ctx, 2);
                    }
                }
                // 0x0022f78c
                charge(ctx, 11);
                v0 = sll(s5, 8);
                a0 = addu(s4, v0);
                a1 = s1;
                jal(ctx, 0x22F798u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                v1 = sll(s5, 1);
                v1 = addu(v1, s5);
                v1 = sll(v1, 2);
                a0 = sra(v1, 1);
                if (i64(v1) < 0) {
                    // 0x0022f7b8
                    charge(ctx, 2);
                    v1 = addiu(v1, 1);
                    a0 = sra(v1, 1);
                }
                // 0x0022f7c0
                charge(ctx, 4);
                v1 = sll(s5, 2);
                v1 = addu(s4, v1);
                sw(a0, v1, 512);
                s5 = addiu(s5, 1);
            }
            // 0x0022f7dc
            charge(ctx, 3);
            sw(zero, s4, 524);
            break;
        case 0x22F7E8u:  // table[5]
            // 0x0022f7e8
            charge(ctx, 22);
            s2 = addiu(s2, 4192);
            a0 = s0;
            a1 = 11;
            jal(ctx, 0x22F7F4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s1 = v0;
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x22F808u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            a0 = addiu(s2, 256);
            a1 = s1;
            jal(ctx, 0x22F818u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            a0 = s0;
            a1 = 12;
            jal(ctx, 0x22F828u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s1 = v0;
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x0022f884
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f840
                charge(ctx, 17);
                v0 = addu(s2, s0);
                sb(s0, v0, 1292);
                v0 = sll(s0, 8);
                v0 = addu(s2, v0);
                a0 = addiu(v0, 512);
                a1 = s1;
                jal(ctx, 0x22F858u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                a1 = sll(s0, 2);
                v1 = addu(a1, s0);
                a0 = sll(v1, 3);
                v1 = 3;
                div(a0, v1);
                mflo(a0);
                v1 = addu(s2, a1);
                sw(a0, v1, 1280);
                s0 = addiu(s0, 1);
            }
            // 0x0022f890
            charge(ctx, 3);
            sw(zero, s2, 1296);
            break;
        case 0x22F89Cu:  // table[6]
            // 0x0022f89c
            charge(ctx, 33);
            s1 = addiu(s2, 4192);
            a0 = s0;
            a1 = 13;
            jal(ctx, 0x22F8A8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = s1;
            a1 = v0;
            jal(ctx, 0x22F8B8u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            a0 = s0;
            a1 = 14;
            jal(ctx, 0x22F8C8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = addiu(s1, 256);
            a1 = v0;
            jal(ctx, 0x22F8D8u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            a0 = s0;
            a1 = 14;
            jal(ctx, 0x22F8E8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = addiu(s1, 512);
            a1 = v0;
            jal(ctx, 0x22F8F8u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            jal(ctx, 0x22F900u, gen::fn_sub_488F30_00488f30);
            v1 = 20;
            divu(v0, v1);
            mfhi(v1);
            sw(v1, s1, 768);
            break;
        case 0x22F920u:  // table[7]
            // 0x0022f920
            charge(ctx, 4);
            s4 = addiu(s2, 4192);
            s5 = 0;
            for (;;) {  // while (s5 < 4)
                // 0x0022f9f8
                charge(ctx, 3);
                v1 = slti(s5, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022f930
                charge(ctx, 17);
                s3 = addu(s4, s5);
                s2 = addiu(s3, 1040);
                jal(ctx, 0x22F938u, gen::fn_sub_488F30_00488f30);
                v0 = v0 & 0x1;
                sb(v0, s2, 0);
                jal(ctx, 0x22F948u, gen::fn_sub_488F30_00488f30);
                sb(v0, s3, 1044);
                jal(ctx, 0x22F954u, gen::fn_sub_488F30_00488f30);
                v0 = v0 & 0x1;
                sb(v0, s3, 1048);
                lb(v1, s2, 0);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0022f9a0
                    charge(ctx, 5);
                    a0 = s0;
                    a1 = 16;
                    jal(ctx, 0x22F9A8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s1 = v0;
                } else {
                    // 0x0022f974
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0022f984
                        charge(ctx, 7);
                        a0 = s0;
                        a1 = 15;
                        jal(ctx, 0x22F98Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s1 = v0;
                    } else {
                        // 0x0022f97c
                        charge(ctx, 2);
                    }
                }
                // 0x0022f9b4
                charge(ctx, 11);
                v0 = sll(s5, 8);
                a0 = addu(s4, v0);
                a1 = s1;
                jal(ctx, 0x22F9C0u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                v1 = sll(s5, 2);
                v1 = addu(v1, s5);
                v1 = sll(v1, 3);
                a0 = sra(v1, 2);
                if (i64(v1) < 0) {
                    // 0x0022f9e0
                    charge(ctx, 2);
                    v1 = addiu(v1, 3);
                    a0 = sra(v1, 2);
                }
                // 0x0022f9e8
                charge(ctx, 4);
                v1 = sll(s5, 2);
                v1 = addu(s4, v1);
                sw(a0, v1, 1024);
                s5 = addiu(s5, 1);
            }
            // 0x0022fa04
            charge(ctx, 3);
            sw(zero, s4, 1052);
            break;
        case 0x22FA10u:  // table[8]
            // 0x0022fa10
            charge(ctx, 10);
            a0 = s0;
            a1 = 17;
            jal(ctx, 0x22FA18u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = addiu(s2, 4192);
            a1 = v0;
            jal(ctx, 0x22FA28u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            break;
        case 0x22FA38u:  // table[9]
            // 0x0022fa38
            charge(ctx, 8);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x22FA40u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = addiu(s2, 4192);
            a1 = v0;
            jal(ctx, 0x22FA50u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0022fa58 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0022FA80 sub_22FA80 -- 13344 bytes; frame 0x120: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bppPanel_LayoutAilment](panel) the ailment icons' animations (13 KB: a jump table on the icon, sin / cos wobble,
// the tables at 0x68E400.., rotated quads through sub_21E170).
void sub_22FA80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    // 0x0022fa80
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f31, sp, 0x2C);
    swc1(f30, sp, 0x28);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lwc1(f1, a0, kBpnX);
    lwc1(f0, a0, 1304);
    add_s(f1, f1, f0);
    lwc1(f0, a0, 1312);
    add_s(f29, f0, f1);
    lwc1(f1, a0, kBpnY);
    lwc1(f0, a0, 1308);
    add_s(f1, f1, f0);
    lwc1(f0, a0, 1316);
    add_s(f23, f0, f1);
    a0 = 4;
    jal(ctx, 0x22FB0Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    lw(v1, s1, kBpnIcon);
    at = sltiu(v1, 11);
    if (at != 0) {
        // 0x0022fb28
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 30688);  // &0x7B77E0
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x22FB44u:  // table[0]
            // 0x0022fb44
            charge(ctx, 9);
            s3 = addiu(s1, 4192);
            lw(v0, s1, 4972);
            v0 = addiu(v0, 1);
            sw(v0, s1, 4972);
            a3 = 0;
            a1 = 3;
            v1 = 30;
            for (;;) {  // while (a3 < 3)
                // 0x0022fba0
                charge(ctx, 3);
                v0 = slti(a3, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022fb68
                charge(ctx, 14);
                v0 = sll(a3, 2);
                a2 = addu(s3, v0);
                v0 = sll(a3, 4);
                v0 = subu(v0, a3);
                v0 = sll(v0, 1);
                div(v0, a1);
                mflo(a0);
                lw(v0, s3, 780);
                v0 = addu(v0, a0);
                sw(v0, a2, 768);
                div(v0, v1);
                mfhi(v0);
                sw(v0, a2, 768);
                a3 = addiu(a3, 1);
            }
            // 0x0022fbac
            charge(ctx, 8);
            v0 = 255;
            sb(v0, sp, 0x11C);
            sb(v0, sp, 0x11D);
            sb(v0, sp, 0x11E);
            sb(v0, sp, 0x11F);
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x0022fd18
                charge(ctx, 3);
                v0 = slti(s0, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022fbcc
                charge(ctx, 13);
                v0 = sll(s0, 2);
                v0 = addu(s3, v0);
                lwc1(f0, v0, 768);
                cvt_s_w(f1, f0);
                v0 = 0x41F00000;
                mtc1(v0, f0);
                div_s(f2, f1, f0);
                lwc1(f1, gp, -26792);  // 0x7CC448 = 0.5f
                c_lt_s(f2, f1);
                if (!cond(ctx)) {
                    // 0x0022fc68
                    charge(ctx, 4);
                    lwc1(f3, gp, -26788);  // 0x7CC44C = 0.8f
                    c_lt_s(f2, f3);
                    if (!cond(ctx)) {
                        // 0x0022fc88
                        charge(ctx, 17);
                        sub_s(f0, f2, f3);
                        v0 = 0x437F0000;
                        mtc1(v0, f2);
                        mul_s(f1, f2, f0);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f3);
                        div_s(f0, f1, f0);
                        sub_s(f1, f2, f0);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x0022fce4
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFF;
                        } else {
                            // 0x0022fccc
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFF;
                        }
                        // 0x0022fcfc
                        charge(ctx, 1);
                        sb(v1, sp, 0x11F);
                    } else {
                        // 0x0022fc78
                        charge(ctx, 4);
                        v0 = 255;
                        sb(v0, sp, 0x11F);
                    }
                } else {
                    // 0x0022fc00
                    charge(ctx, 11);
                    v0 = 0x437F0000;
                    mtc1(v0, f0);
                    mul_s(f0, f0, f2);
                    div_s(f1, f0, f1);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x0022fc44
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x0022fc2c
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x0022fc5c
                    charge(ctx, 3);
                    sb(v1, sp, 0x11F);
                }
                // 0x0022fd00
                charge(ctx, 6);
                v0 = sll(s0, 8);
                a0 = addu(s3, v0);
                a1 = addiu(sp, 0x11C);
                jal(ctx, 0x22FD0Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s0 = addiu(s0, 1);
            }
            // 0x0022fd24
            charge(ctx, 16);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x22FD2Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s0 = v0;
            s1 = 0;
            v1 = 0x42840000;
            mtc1(v1, f0);
            add_s(f21, f0, f29);
            v1 = 0x41300000;
            mtc1(v1, f0);
            add_s(f20, f0, f23);
            for (;;) {  // while (s1 < 3)
                // 0x00230064
                charge(ctx, 3);
                v1 = slti(s1, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022fd64
                charge(ctx, 13);
                v0 = sll(s1, 2);
                v0 = addu(s3, v0);
                lwc1(f0, v0, 768);
                cvt_s_w(f1, f0);
                v0 = 0x41F00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                lwc1(f2, gp, -26784);  // 0x7CC450 = 0.5f
                c_lt_s(f1, f2);
                if (!cond(ctx)) {
                    // 0x0022fda8
                    charge(ctx, 4);
                    lwc1(f0, gp, -26788);  // 0x7CC44C = 0.8f
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x0022fde8
                        charge(ctx, 11);
                        lwc1(f2, gp, -26780);  // 0x7CC454 = 0.7f
                        sub_s(f1, f1, f2);
                        lwc1(f0, gp, -31856);  // 0x7CB080 = 0.3f
                        mul_s(f1, f0, f1);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f2);
                        div_s(f1, f1, f0);
                        lwc1(f0, gp, -32656);  // 0x7CAD60 = 1.2f
                        add_s(f13, f0, f1);
                    } else {
                        // 0x0022fdb8
                        charge(ctx, 12);
                        sub_s(f1, f1, f2);
                        lwc1(f0, gp, -32004);  // 0x7CAFEC = 0.2f
                        mul_s(f1, f0, f1);
                        lwc1(f0, gp, -26780);  // 0x7CC454 = 0.7f
                        sub_s(f0, f0, f2);
                        div_s(f1, f1, f0);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                    }
                } else {
                    // 0x0022fd98
                    charge(ctx, 4);
                    v0 = 0x3F800000;
                    mtc1(v0, f13);
                }
                // 0x0022fe14
                charge(ctx, 148);
                a0 = sll(s1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -7120);  // &0x68E430
                v1 = addu(v0, a0);
                lwc1(f1, v1, 0);
                lwc1(f0, v1, 4);
                swc1(f1, sp, 0xF8);
                swc1(f0, sp, 0xFC);
                ld(v0, sp, 0xF8);
                sd(v0, sp, 0xD0);
                lwc1(f1, sp, 0xF8);
                lwc1(f0, sp, 0xFC);
                swc1(f1, sp, 0xD8);
                swc1(f0, sp, 0xDC);
                lwc1(f1, v1, 8);
                lwc1(f0, v1, 12);
                swc1(f1, sp, 0xF0);
                swc1(f0, sp, 0xF4);
                lwc1(f1, sp, 0xF0);
                lwc1(f0, sp, 0xF4);
                swc1(f1, sp, 0xE0);
                swc1(f0, sp, 0xE4);
                swc1(f1, sp, 0xE8);
                swc1(f0, sp, 0xEC);
                v0 = 0x690000;
                v0 = addiu(v0, -7168);  // &0x68E400
                v0 = addu(v0, a0);
                lwc1(f1, sp, 0xD8);
                lwc1(f0, v0, 0);
                add_s(f3, f1, f0);
                swc1(f3, sp, 0xD8);
                lwc1(f1, v0, 4);
                lwc1(f0, sp, 0xDC);
                add_s(f6, f0, f1);
                swc1(f6, sp, 0xDC);
                lwc1(f1, v0, 8);
                lwc1(f0, sp, 0xE0);
                add_s(f2, f0, f1);
                swc1(f2, sp, 0xE0);
                lwc1(f1, v0, 12);
                lwc1(f0, sp, 0xE4);
                add_s(f15, f0, f1);
                swc1(f15, sp, 0xE4);
                v0 = sll(s1, 2);
                v0 = addu(s3, v0);
                lw(v1, v0, 768);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                v0 = 0x41F00000;
                mtc1(v0, f12);
                div_s(f1, f0, f12);
                v0 = 0x3F800000;
                mtc1(v0, f11);
                sub_s(f0, f11, f1);
                v0 = 0x40400000;
                mtc1(v0, f14);
                mul_s(f10, f14, f3);
                lwc1(f9, sp, 0xD0);
                mul_s(f8, f14, f2);
                lwc1(f7, sp, 0xE8);
                mul_s(f2, f7, f1);
                mul_s(f5, f1, f2);
                mul_s(f2, f8, f1);
                mul_s(f4, f1, f2);
                mul_s(f2, f9, f0);
                mul_s(f3, f0, f2);
                mul_s(f2, f10, f1);
                mul_s(f2, f0, f2);
                mula_s(f0, f2);
                madda_s(f0, f3);
                madda_s(f0, f4);
                madd_s(f17, f1, f5);
                mul_s(f6, f14, f6);
                lwc1(f5, sp, 0xD4);
                mul_s(f4, f14, f15);
                lwc1(f3, sp, 0xEC);
                mul_s(f2, f3, f1);
                mul_s(f16, f1, f2);
                mul_s(f2, f4, f1);
                mul_s(f15, f1, f2);
                mul_s(f2, f5, f0);
                mul_s(f14, f0, f2);
                mul_s(f2, f6, f1);
                mul_s(f2, f0, f2);
                mula_s(f0, f2);
                madda_s(f0, f14);
                madda_s(f0, f15);
                madd_s(f0, f1, f16);
                add_s(f2, f17, f21);
                add_s(f1, f0, f20);
                v0 = addiu(v1, 1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f0, f12);
                sub_s(f14, f11, f0);
                mul_s(f7, f7, f0);
                mul_s(f12, f0, f7);
                mul_s(f7, f8, f0);
                mul_s(f11, f0, f7);
                mul_s(f7, f9, f14);
                mul_s(f8, f14, f7);
                mul_s(f7, f10, f0);
                mul_s(f7, f14, f7);
                mula_s(f14, f7);
                madda_s(f14, f8);
                madda_s(f14, f11);
                madd_s(f9, f0, f12);
                mul_s(f3, f3, f0);
                mul_s(f8, f0, f3);
                mul_s(f3, f4, f0);
                mul_s(f7, f0, f3);
                mul_s(f3, f5, f14);
                mul_s(f4, f14, f3);
                mul_s(f3, f6, f0);
                mul_s(f3, f14, f3);
                mula_s(f14, f3);
                madda_s(f14, f4);
                madda_s(f14, f7);
                madd_s(f0, f0, f8);
                add_s(f4, f9, f21);
                add_s(f3, f0, f20);
                swc1(f2, sp, 0x100);
                swc1(f1, sp, 0x104);
                lwc1(f0, s0, kSpW);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f13);
                swc1(f0, sp, 0x108);
                lwc1(f0, s0, kSpH);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f13);
                swc1(f0, sp, 0x10C);
                sub_s(f0, f4, f2);
                swc1(f0, sp, 0x110);
                sub_s(f0, f3, f1);
                swc1(f0, sp, 0x114);
                v0 = sll(s1, 8);
                a0 = addu(s3, v0);
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x230058u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                s1 = addiu(s1, 1);
            }
            // 0x00230070
            charge(ctx, 2);
            break;
        case 0x230078u:  // table[1]
            // 0x00230078
            charge(ctx, 9);
            s0 = addiu(s1, 4192);
            lw(v1, s1, 5740);
            v1 = addiu(v1, 1);
            sw(v1, s1, 5740);
            t0 = 0;
            a2 = 3;
            a0 = 10;
            for (;;) {  // while (t0 < 3)
                // 0x002300d0
                charge(ctx, 3);
                v1 = slti(t0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023009c
                charge(ctx, 13);
                v1 = sll(t0, 2);
                a3 = addu(s0, v1);
                v1 = addu(v1, t0);
                v1 = sll(v1, 1);
                div(v1, a2);
                mflo(a1);
                lw(v1, s0, 1548);
                v1 = addu(v1, a1);
                sw(v1, a3, 1536);
                div(v1, a0);
                mfhi(v1);
                sw(v1, a3, 1536);
                t0 = addiu(t0, 1);
            }
            // 0x002300dc
            charge(ctx, 8);
            v1 = 255;
            sb(v1, sp, 0x11C);
            sb(v1, sp, 0x11D);
            sb(v1, sp, 0x11E);
            sb(v1, sp, 0x11F);
            s3 = 0;
            for (;;) {  // while (s3 < 3)
                // 0x00230280
                charge(ctx, 3);
                v1 = slti(s3, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002300fc
                charge(ctx, 7);
                s4 = 0;
                v1 = sll(s3, 2);
                s1 = addu(s0, v1);
                v1 = sll(s3, 9);
                s5 = addu(s0, v1);
                for (;;) {  // while (s4 < 2)
                    // 0x00230270
                    charge(ctx, 3);
                    v1 = slti(s4, 2);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00230118
                    charge(ctx, 16);
                    lwc1(f0, s1, 1536);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = sll(s4, 1);
                    v0 = addu(v0, s4);
                    v1 = sll(v0, 2);
                    v0 = 0x690000;
                    v0 = addiu(v0, -7024);  // &0x68E490
                    v0 = addu(v0, v1);
                    lwc1(f2, v0, 0);
                    c_lt_s(f1, f2);
                    if (!cond(ctx)) {
                        // 0x00230164
                        charge(ctx, 4);
                        lwc1(f0, v0, 4);
                        c_lt_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x00230194
                            charge(ctx, 4);
                            lwc1(f0, v0, 8);
                            c_lt_s(f1, f0);
                            if (!cond(ctx)) {
                                // 0x002301b4
                                charge(ctx, 7);
                                sub_s(f2, f1, f0);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                                sub_s(f0, f1, f0);
                                div_s(f0, f2, f0);
                                sub_s(f1, f1, f0);
                            } else {
                                // 0x002301a4
                                charge(ctx, 4);
                                v0 = 0x3F800000;
                                mtc1(v0, f1);
                            }
                        } else {
                            // 0x00230174
                            charge(ctx, 8);
                            sub_s(f1, f1, f2);
                            sub_s(f0, f0, f2);
                            div_s(f1, f1, f0);
                        }
                    } else {
                        // 0x00230158
                        charge(ctx, 3);
                        mtc1(zero, f1);
                    }
                    // 0x002301d0
                    charge(ctx, 3);
                    v0 = 1;
                    if (s4 == v0) {
                        // 0x002301dc
                        charge(ctx, 8);
                        v0 = 0x41700000;
                        mtc1(v0, f0);
                        mul_s(f1, f0, f1);
                        v0 = 0x42C80000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                    }
                    // 0x002301fc
                    charge(ctx, 10);
                    v0 = 0x437F0000;
                    mtc1(v0, f0);
                    mul_s(f1, f0, f1);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x0023023c
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x00230224
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x00230254
                    charge(ctx, 7);
                    sb(v1, sp, 0x11F);
                    v0 = sll(s4, 8);
                    a0 = addu(s5, v0);
                    a1 = addiu(sp, 0x11C);
                    jal(ctx, 0x230264u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                    s4 = addiu(s4, 1);
                }
                // 0x0023027c
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x0023028c
            charge(ctx, 11);
            s4 = 0;
            v1 = 0x42840000;
            mtc1(v1, f0);
            add_s(f21, f0, f29);
            v1 = 0x41300000;
            mtc1(v1, f0);
            add_s(f20, f0, f23);
            for (;;) {  // while (s4 < 3)
                // 0x002305d0
                charge(ctx, 3);
                v1 = slti(s4, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002302b8
                charge(ctx, 106);
                v0 = sll(s4, 2);
                v0 = addu(s0, v0);
                s7 = addiu(v0, 1536);
                lw(v0, v0, 1536);
                v0 = addiu(v0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f2, f1, f0);
                mtc1(zero, f4);
                mul_s(f1, f4, f2);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                mula_s(f0, f2);
                msub_s(f2, f2, f1);
                v1 = sll(s4, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -7072);  // &0x68E460
                s3 = addu(v0, v1);
                lwc1(f1, s3, 0);
                s1 = addiu(s3, 8);
                lwc1(f0, gp, -32472);  // 0x7CAE18 = 0.95f
                mul_s(f3, f0, f2);
                lwc1(f0, s3, 8);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f2, f3, f0);
                s6 = addiu(s3, 4);
                lwc1(f1, s3, 4);
                s5 = addiu(s3, 12);
                lwc1(f0, s3, 12);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f0, f3, f0);
                add_s(f23, f2, f21);
                add_s(f22, f0, f20);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x230364u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                swc1(f23, sp, 0x100);
                swc1(f22, sp, 0x104);
                lwc1(f0, v0, kSpW);
                cvt_s_w(f0, f0);
                v1 = 0x3F400000;
                mtc1(v1, f1);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x108);
                lwc1(f0, v0, kSpH);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x10C);
                lwc1(f1, s1, 0);
                lwc1(f0, s3, 0);
                sub_s(f24, f1, f0);
                lwc1(f1, s5, 0);
                lwc1(f0, s6, 0);
                sub_s(f23, f1, f0);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x2303BCu, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x2303CCu, gen::fn_cosf_0052e6d8);
                mula_s(f24, f0);
                msub_s(f0, f23, f22);
                swc1(f0, sp, 0x110);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x2303E4u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x2303F4u, gen::fn_cosf_0052e6d8);
                mula_s(f23, f0);
                madd_s(f0, f24, f22);
                swc1(f0, sp, 0x114);
                v0 = sll(s4, 9);
                s3 = addu(s0, v0);
                a0 = s3;
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x230420u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                lw(v0, s7, 0);
                v0 = addiu(v0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f0, f1, f0);
                v0 = 0x690000;
                lwc1(f2, v0, -7012);  // 0x68E49C
                c_lt_s(f0, f2);
                if (!cond(ctx)) {
                    // 0x00230474
                    charge(ctx, 33);
                    sub_s(f1, f0, f2);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f0, f0, f2);
                    div_s(f2, f1, f0);
                    v0 = 0x40A00000;
                    mtc1(v0, f0);
                    mul_s(f1, f0, f2);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    mula_s(f0, f2);
                    mtc1(zero, f3);
                    msub_s(f4, f2, f1);
                    v1 = sll(s4, 4);
                    v0 = 0x690000;
                    v0 = addiu(v0, -7072);  // &0x68E460
                    v0 = addu(v0, v1);
                    lwc1(f1, v0, 0);
                    lwc1(f0, s1, 0);
                    sub_s(f0, f0, f1);
                    adda_s(f3, f1);
                    madd_s(f2, f4, f0);
                    lwc1(f1, v0, 4);
                    lwc1(f0, s5, 0);
                    sub_s(f0, f0, f1);
                    adda_s(f3, f1);
                    madd_s(f0, f4, f0);
                    add_s(f23, f2, f21);
                    add_s(f22, f0, f20);
                } else {
                    // 0x00230460
                    charge(ctx, 5);
                    mtc1(zero, f23);
                    mov_s(f22, f23);
                }
                // 0x002304f8
                charge(ctx, 54);
                a0 = s2;
                a1 = 2;
                jal(ctx, 0x230500u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                swc1(f23, sp, 0x100);
                swc1(f22, sp, 0x104);
                lwc1(f0, v0, kSpW);
                cvt_s_w(f0, f0);
                v1 = 0x3F800000;
                mtc1(v1, f1);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x108);
                lwc1(f0, v0, kSpH);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x10C);
                v1 = sll(s4, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -7072);  // &0x68E460
                v0 = addu(v0, v1);
                lwc1(f1, s1, 0);
                lwc1(f0, v0, 0);
                sub_s(f24, f1, f0);
                lwc1(f1, s5, 0);
                lwc1(f0, s6, 0);
                sub_s(f23, f1, f0);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x230568u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x230578u, gen::fn_cosf_0052e6d8);
                mula_s(f24, f0);
                msub_s(f0, f23, f22);
                swc1(f0, sp, 0x110);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x230590u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                lwc1(f12, gp, -31748);  // 0x7CB0EC = -1.25664f
                jal(ctx, 0x2305A0u, gen::fn_cosf_0052e6d8);
                mula_s(f23, f0);
                madd_s(f0, f24, f22);
                swc1(f0, sp, 0x114);
                a0 = addiu(s3, 256);
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x2305C4u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                s4 = addiu(s4, 1);
            }
            // 0x002305dc
            charge(ctx, 2);
            break;
        case 0x2305E4u:  // table[2]
            // 0x002305e4
            charge(ctx, 7);
            s0 = addiu(s1, 4192);
            lw(v1, s1, 4980);
            v1 = addiu(v1, 1);
            sw(v1, s1, 4980);
            s5 = 0;
            for (;;) {  // while (s5 < 3)
                // 0x002307d0
                charge(ctx, 3);
                v1 = slti(s5, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00230600
                charge(ctx, 9);
                v1 = sll(s5, 2);
                a0 = addu(s0, v1);
                s6 = addiu(a0, 768);
                lw(v1, a0, 768);
                v1 = addiu(v1, 1);
                sw(v1, a0, 768);
                v1 = slti(v1, 12);
                if (v1 == 0) {
                    // 0x00230624
                    charge(ctx, 13);
                    v0 = addu(s0, s5);
                    s7 = addiu(v0, 780);
                    jal(ctx, 0x23062Cu, gen::fn_sub_488F30_00488f30);
                    v1 = 5;
                    divu(v0, v1);
                    mfhi(v0);
                    sb(v0, s7, 0);
                    jal(ctx, 0x230644u, gen::fn_sub_488F30_00488f30);
                    s1 = v0 & 0x3;
                    if (i64(v0) < 0) {
                        // 0x00230658
                        charge(ctx, 2);
                        if (s1 != 0) {
                            // 0x00230660
                            charge(ctx, 1);
                            s1 = addiu(s1, -4);
                        }
                    }
                    // 0x00230664
                    charge(ctx, 3);
                    s4 = 0;
                    for (;;) {  // while (s4 < 3)
                        // 0x002306ac
                        charge(ctx, 3);
                        v0 = slti(s4, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00230670
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {  // while (v1 < 3)
                            // 0x0023069c
                            charge(ctx, 3);
                            v0 = slti(v1, 3);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0023067c
                            charge(ctx, 2);
                            if (s5 != v1) {
                                // 0x00230684
                                charge(ctx, 4);
                                v0 = addu(s0, v1);
                                lb(v0, v0, 783);
                                if (v0 == s1) {
                                    // 0x00230694
                                    charge(ctx, 1);
                                    s1 = addiu(s1, 1);
                                }
                            }
                            // 0x00230698
                            charge(ctx, 1);
                            v1 = addiu(v1, 1);
                        }
                        // 0x002306a8
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                    // 0x002306b8
                    charge(ctx, 3);
                    v0 = slti(s1, 6);
                    if (v0 == 0) {
                        // 0x002306c4
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -6512);  // "bpp_panel.c"
                        a1 = 1762;
                        jal(ctx, 0x2306D0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 1762): `jr $ra` in retail, execution goes on
                    }
                    // 0x002306d8
                    charge(ctx, 6);
                    v0 = addu(s0, s5);
                    sb(s1, v0, 783);
                    lb(a0, s7, 0);
                    v1 = 4;
                    if (a0 == v1) {
                        // 0x00230790
                        charge(ctx, 5);
                        a0 = s2;
                        a1 = 7;
                        jal(ctx, 0x230798u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s3 = v0;
                    } else {
                        // 0x002306f0
                        charge(ctx, 3);
                        a1 = 3;
                        if (a0 == a1) {
                            // 0x00230774
                            charge(ctx, 7);
                            a0 = s2;
                            a1 = 6;
                            jal(ctx, 0x23077Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                            s3 = v0;
                        } else {
                            // 0x002306fc
                            charge(ctx, 3);
                            v0 = 2;
                            if (a0 == v0) {
                                // 0x00230758
                                charge(ctx, 7);
                                a0 = s2;
                                a1 = 5;
                                jal(ctx, 0x230760u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                s3 = v0;
                            } else {
                                // 0x00230708
                                charge(ctx, 3);
                                v0 = 1;
                                if (a0 == v0) {
                                    // 0x0023073c
                                    charge(ctx, 7);
                                    a0 = s2;
                                    a1 = v1;
                                    jal(ctx, 0x230744u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                    s3 = v0;
                                } else {
                                    // 0x00230714
                                    charge(ctx, 2);
                                    if (a0 == 0) {
                                        // 0x00230724
                                        charge(ctx, 6);
                                        a0 = s2;
                                        jal(ctx, 0x230728u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                        s3 = v0;
                                    } else {
                                        // 0x0023071c
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                    }
                    // 0x002307a4
                    charge(ctx, 10);
                    v0 = sll(s5, 8);
                    a0 = addu(s0, v0);
                    a1 = s3;
                    jal(ctx, 0x2307B0u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                    lw(a0, s6, 0);
                    v1 = 12;
                    div(a0, v1);
                    mfhi(v1);
                    sw(v1, s6, 0);
                }
                // 0x002307cc
                charge(ctx, 1);
                s5 = addiu(s5, 1);
            }
            // 0x002307dc
            charge(ctx, 8);
            v1 = 255;
            sb(v1, sp, 0x11C);
            sb(v1, sp, 0x11D);
            sb(v1, sp, 0x11E);
            sb(v1, sp, 0x11F);
            s1 = 0;
            for (;;) {  // while (s1 < 3)
                // 0x00230950
                charge(ctx, 3);
                v1 = slti(s1, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002307fc
                charge(ctx, 13);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lwc1(f0, v0, 768);
                cvt_s_w(f1, f0);
                v0 = 0x41400000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x690000;
                lwc1(f2, v0, -6528);  // 0x68E680
                c_lt_s(f1, f2);
                if (!cond(ctx)) {
                    // 0x0023083c
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lwc1(f0, v0, -6524);  // 0x68E684
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x00230870
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lwc1(f0, v0, -6520);  // 0x68E688
                        c_lt_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x00230894
                            charge(ctx, 7);
                            sub_s(f2, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                            sub_s(f0, f1, f0);
                            div_s(f0, f2, f0);
                            sub_s(f1, f1, f0);
                        } else {
                            // 0x00230884
                            charge(ctx, 4);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                        }
                    } else {
                        // 0x00230850
                        charge(ctx, 8);
                        sub_s(f1, f1, f2);
                        sub_s(f0, f0, f2);
                        div_s(f1, f1, f0);
                    }
                } else {
                    // 0x00230830
                    charge(ctx, 3);
                    mtc1(zero, f1);
                }
                // 0x002308b0
                charge(ctx, 3);
                v0 = 1;
                if (s4 == v0) {
                    // 0x002308bc
                    charge(ctx, 8);
                    v0 = 0x41700000;
                    mtc1(v0, f0);
                    mul_s(f1, f0, f1);
                    v0 = 0x42C80000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                }
                // 0x002308dc
                charge(ctx, 10);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0023091c
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00230904
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00230934
                charge(ctx, 7);
                sb(v1, sp, 0x11F);
                v0 = sll(s1, 8);
                a0 = addu(s0, v0);
                a1 = addiu(sp, 0x11C);
                jal(ctx, 0x230944u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s1 = addiu(s1, 1);
            }
            // 0x0023095c
            charge(ctx, 11);
            s4 = 0;
            v1 = 0x42B40000;
            mtc1(v1, f0);
            add_s(f21, f0, f29);
            v1 = 0x42200000;
            mtc1(v1, f0);
            add_s(f20, f0, f23);
            for (;;) {  // while (s4 < 3)
                // 0x00230bdc
                charge(ctx, 3);
                v1 = slti(s4, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00230988
                charge(ctx, 56);
                a0 = addu(s0, s4);
                lb(s1, a0, 783);
                v0 = sll(s4, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, 768);
                v0 = addiu(v0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41400000;
                mtc1(v0, f0);
                div_s(f5, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                mul_s(f1, f0, f5);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mula_s(f0, f5);
                mtc1(zero, f4);
                msub_s(f2, f5, f1);
                v1 = sll(s1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -6624);  // &0x68E620
                v0 = addu(v0, v1);
                lwc1(f1, v0, 0);
                s5 = addiu(v0, 8);
                lwc1(f0, gp, -32472);  // 0x7CAE18 = 0.95f
                mul_s(f3, f0, f2);
                lwc1(f0, v0, 8);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f2, f3, f0);
                s6 = addiu(v0, 4);
                lwc1(f1, v0, 4);
                s7 = addiu(v0, 12);
                lwc1(f0, v0, 12);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f0, f3, f0);
                add_s(f23, f2, f21);
                add_s(f22, f0, f20);
                v0 = 0x3F400000;
                mtc1(v0, f1);
                v0 = 0x3F000000;
                mtc1(v0, f0);
                adda_s(f4, f0);
                madd_s(f24, f1, f5);
                lb(a0, a0, 780);
                v1 = 4;
                if (a0 == v1) {
                    // 0x00230b08
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = 7;
                    jal(ctx, 0x230B10u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s3 = v0;
                } else {
                    // 0x00230a68
                    charge(ctx, 3);
                    a1 = 3;
                    if (a0 == a1) {
                        // 0x00230aec
                        charge(ctx, 7);
                        a0 = s2;
                        a1 = 6;
                        jal(ctx, 0x230AF4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s3 = v0;
                    } else {
                        // 0x00230a74
                        charge(ctx, 3);
                        v0 = 2;
                        if (a0 == v0) {
                            // 0x00230ad0
                            charge(ctx, 7);
                            a0 = s2;
                            a1 = 5;
                            jal(ctx, 0x230AD8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                            s3 = v0;
                        } else {
                            // 0x00230a80
                            charge(ctx, 3);
                            v0 = 1;
                            if (a0 == v0) {
                                // 0x00230ab4
                                charge(ctx, 7);
                                a0 = s2;
                                a1 = v1;
                                jal(ctx, 0x230ABCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                s3 = v0;
                            } else {
                                // 0x00230a8c
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x00230a9c
                                    charge(ctx, 6);
                                    a0 = s2;
                                    jal(ctx, 0x230AA0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                                    s3 = v0;
                                } else {
                                    // 0x00230a94
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
                // 0x00230b1c
                charge(ctx, 48);
                swc1(f23, sp, 0x100);
                swc1(f22, sp, 0x104);
                lwc1(f0, s3, 12);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f24);
                swc1(f0, sp, 0x108);
                lwc1(f0, s3, 16);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f24);
                swc1(f0, sp, 0x10C);
                v1 = sll(s1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -6624);  // &0x68E620
                v0 = addu(v0, v1);
                lwc1(f1, s5, 0);
                lwc1(f0, v0, 0);
                sub_s(f24, f1, f0);
                lwc1(f1, s7, 0);
                lwc1(f0, s6, 0);
                sub_s(f23, f1, f0);
                mtc1(zero, f12);
                jal(ctx, 0x230B70u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                mtc1(zero, f12);
                jal(ctx, 0x230B80u, gen::fn_cosf_0052e6d8);
                mula_s(f24, f0);
                mtc1(zero, f12);
                msub_s(f0, f23, f22);
                swc1(f0, sp, 0x110);
                jal(ctx, 0x230B98u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                mtc1(zero, f12);
                jal(ctx, 0x230BA8u, gen::fn_cosf_0052e6d8);
                mula_s(f23, f0);
                madd_s(f0, f24, f22);
                swc1(f0, sp, 0x114);
                v0 = sll(s4, 8);
                a0 = addu(s0, v0);
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x230BD0u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                s4 = addiu(s4, 1);
            }
            // 0x00230be8
            charge(ctx, 2);
            break;
        case 0x230BF0u:  // table[3]
            // 0x00230bf0
            charge(ctx, 12);
            s3 = addiu(s1, 4192);
            a0 = s2;
            a1 = 8;
            jal(ctx, 0x230BFCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s1 = v0;
            lw(v1, s3, 524);
            v1 = addiu(v1, 1);
            sw(v1, s3, 524);
            s2 = 0;
            for (;;) {  // while (s2 < 2)
                // 0x00230c6c
                charge(ctx, 3);
                v1 = slti(s2, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00230c20
                charge(ctx, 9);
                v1 = sll(s2, 2);
                a0 = addu(s3, v1);
                s0 = addiu(a0, 512);
                lw(v1, a0, 512);
                v1 = addiu(v1, 1);
                sw(v1, a0, 512);
                v1 = slti(v1, 30);
                if (v1 == 0) {
                    // 0x00230c44
                    charge(ctx, 9);
                    jal(ctx, 0x230C44u, gen::fn_sub_488F30_00488f30);
                    v1 = addu(s3, s2);
                    sb(v0, v1, 520);
                    lw(a0, s0, 0);
                    v1 = 30;
                    div(a0, v1);
                    mfhi(v1);
                    sw(v1, s0, 0);
                }
                // 0x00230c68
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00230c78
            charge(ctx, 19);
            s4 = 0;
            v1 = 0x42A00000;
            mtc1(v1, f0);
            add_s(f22, f0, f29);
            v1 = 0x41700000;
            mtc1(v1, f0);
            add_s(f21, f0, f23);
            v1 = 0x42200000;
            mtc1(v1, f0);
            add_s(f20, f0, f29);
            v1 = 0x41200000;
            mtc1(v1, f0);
            add_s(f31, f0, f23);
            for (;;) {  // while (s4 < 2)
                // 0x002310f4
                charge(ctx, 3);
                v1 = slti(s4, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00230cc4
                charge(ctx, 15);
                v0 = sll(s4, 2);
                v0 = addu(s3, v0);
                lw(s0, v0, 512);
                mtc1(s0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41F00000;
                mtc1(v0, f0);
                div_s(f2, f1, f0);
                v0 = 1;
                if (s4 == v0) {
                    // 0x00230d30
                    charge(ctx, 8);
                    mov_s(f28, f20);
                    mov_s(f27, f31);
                    lwc1(f0, s1, kSpW);
                    cvt_s_w(f0, f0);
                    add_s(f26, f20, f0);
                    lwc1(f0, s1, kSpH);
                    cvt_s_w(f0, f0);
                    add_s(f25, f31, f0);
                } else {
                    // 0x00230d00
                    charge(ctx, 2);
                    if (s4 == 0) {
                        // 0x00230d10
                        charge(ctx, 8);
                        mov_s(f28, f22);
                        mov_s(f27, f21);
                        mov_s(f26, f22);
                        lwc1(f0, s1, kSpH);
                        cvt_s_w(f0, f0);
                        add_s(f25, f21, f0);
                    } else {
                        // 0x00230d08
                        charge(ctx, 2);
                    }
                }
                // 0x00230d50
                charge(ctx, 17);
                swc1(f28, sp, 0xD0);
                swc1(f27, sp, 0xD4);
                lwc1(f0, s1, kSpW);
                cvt_s_w(f0, f0);
                add_s(f0, f28, f0);
                swc1(f0, sp, 0xD8);
                swc1(f27, sp, 0xDC);
                swc1(f0, sp, 0xE0);
                lwc1(f0, s1, kSpH);
                cvt_s_w(f0, f0);
                add_s(f0, f27, f0);
                swc1(f0, sp, 0xE4);
                swc1(f28, sp, 0xE8);
                swc1(f0, sp, 0xEC);
                v1 = 0;
                for (;;) {  // while (v1 < 4)
                    // 0x00230dbc
                    charge(ctx, 3);
                    v0 = slti(v1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00230d94
                    charge(ctx, 10);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 208);
                    lwc1(f0, v0, 0);
                    sub_s(f0, f0, f26);
                    swc1(f0, v0, 0);
                    lwc1(f0, v0, 4);
                    sub_s(f0, f0, f25);
                    swc1(f0, v0, 4);
                    v1 = addiu(v1, 1);
                }
                // 0x00230dc8
                charge(ctx, 3);
                v0 = 1;
                if (s4 == v0) {
                    // 0x00230e08
                    charge(ctx, 7);
                    v0 = 0x3E800000;
                    mtc1(v0, f1);
                    mul_s(f0, f1, f2);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x108);
                    swc1(f0, sp, 0x10C);
                } else {
                    // 0x00230dd4
                    charge(ctx, 2);
                    if (s4 == 0) {
                        // 0x00230de4
                        charge(ctx, 9);
                        v0 = 0x3F000000;
                        mtc1(v0, f1);
                        mul_s(f0, f1, f2);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0x108);
                        swc1(f0, sp, 0x10C);
                    } else {
                        // 0x00230ddc
                        charge(ctx, 2);
                    }
                }
                // 0x00230e24
                charge(ctx, 5);
                v1 = 0;
                lwc1(f2, sp, 0x108);
                lwc1(f1, sp, 0x10C);
                for (;;) {  // while (v1 < 4)
                    // 0x00230e60
                    charge(ctx, 3);
                    v0 = slti(v1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00230e38
                    charge(ctx, 10);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 208);
                    lwc1(f0, v0, 0);
                    mul_s(f0, f0, f2);
                    swc1(f0, v0, 0);
                    lwc1(f0, v0, 4);
                    mul_s(f0, f0, f1);
                    swc1(f0, v0, 4);
                    v1 = addiu(v1, 1);
                }
                // 0x00230e6c
                charge(ctx, 3);
                v0 = 1;
                if (s4 == v0) {
                    // 0x00230e94
                    charge(ctx, 1);
                    lwc1(f24, gp, -31772);  // 0x7CB0D4 = 0.349066f
                } else {
                    // 0x00230e78
                    charge(ctx, 2);
                    if (s4 == 0) {
                        // 0x00230e88
                        charge(ctx, 3);
                        mtc1(zero, f24);
                    } else {
                        // 0x00230e80
                        charge(ctx, 2);
                    }
                }
                // 0x00230e98
                charge(ctx, 31);
                v0 = addu(s3, s4);
                lb(v0, v0, 520);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x43800000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x43B40000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mul_s(f2, f0, f1);
                lwc1(f1, gp, -32184);  // 0x7CAF38 = 3.14159f
                mtc1(zero, f0);
                adda_s(f0, f24);
                madd_s(f1, f1, f2);
                lwc1(f0, gp, -31744);  // 0x7CB0F0 = -0.349066f
                add_s(f24, f1, f0);
                s2 = 0;
                for (;;) {  // while (s2 < 4)
                    // 0x00230f88
                    charge(ctx, 3);
                    v0 = slti(s2, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00230f14
                    charge(ctx, 29);
                    v0 = sll(s2, 3);
                    v0 = addu(v0, sp);
                    s5 = addiu(v0, 208);
                    s6 = addiu(s5, 4);
                    mov_s(f12, f24);
                    jal(ctx, 0x230F28u, gen::fn_sinf_0052e878);
                    mov_s(f29, f0);
                    lwc1(f23, s6, 0);
                    mov_s(f12, f24);
                    jal(ctx, 0x230F3Cu, gen::fn_cosf_0052e6d8);
                    lwc1(f1, s5, 0);
                    mula_s(f1, f0);
                    msub_s(f30, f23, f29);
                    mov_s(f12, f24);
                    jal(ctx, 0x230F54u, gen::fn_sinf_0052e878);
                    mov_s(f29, f0);
                    lwc1(f23, s5, 0);
                    mov_s(f12, f24);
                    jal(ctx, 0x230F68u, gen::fn_cosf_0052e6d8);
                    lwc1(f1, s6, 0);
                    mula_s(f1, f0);
                    madd_s(f0, f23, f29);
                    swc1(f30, s5, 0);
                    swc1(f0, s6, 0);
                    s2 = addiu(s2, 1);
                }
                // 0x00230f94
                charge(ctx, 3);
                v1 = 0;
                for (;;) {  // while (v1 < 4)
                    // 0x00230fc8
                    charge(ctx, 3);
                    v0 = slti(v1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00230fa0
                    charge(ctx, 10);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, sp);
                    v0 = addiu(v0, 208);
                    lwc1(f0, v0, 0);
                    add_s(f0, f0, f26);
                    swc1(f0, v0, 0);
                    lwc1(f0, v0, 4);
                    add_s(f0, f0, f25);
                    swc1(f0, v0, 4);
                    v1 = addiu(v1, 1);
                }
                // 0x00230fd4
                charge(ctx, 9);
                v0 = sll(s4, 8);
                s2 = addu(s3, v0);
                a0 = s2;
                a1 = addiu(sp, 0xD0);
                jal(ctx, 0x230FE4u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
                at = slti(s0, 7);
                if (at == 0) {
                    // 0x00231028
                    charge(ctx, 3);
                    at = slti(s0, 20);
                    if (at == 0) {
                        // 0x00231044
                        charge(ctx, 12);
                        v0 = addiu(s0, -20);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x41200000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f1, f0, f1);
                    } else {
                        // 0x00231034
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                    }
                } else {
                    // 0x00230ff8
                    charge(ctx, 12);
                    mtc1(s0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40E00000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                }
                // 0x00231074
                charge(ctx, 14);
                v0 = 255;
                sb(v0, sp, 0x11C);
                sb(v0, sp, 0x11D);
                sb(v0, sp, 0x11E);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002310c4
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002310ac
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002310dc
                charge(ctx, 6);
                sb(v1, sp, 0x11F);
                a0 = s2;
                a1 = addiu(sp, 0x11C);
                jal(ctx, 0x2310E8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s4 = addiu(s4, 1);
            }
            // 0x00231100
            charge(ctx, 2);
            break;
        case 0x231108u:  // table[4, 10]
            // 0x00231108
            charge(ctx, 7);
            s0 = addiu(s1, 4192);
            lw(v1, s1, 4716);
            v1 = addiu(v1, 1);
            sw(v1, s1, 4716);
            s4 = 0;
            for (;;) {  // while (s4 < 2)
                // 0x0023126c
                charge(ctx, 3);
                v1 = slti(s4, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231124
                charge(ctx, 9);
                v1 = sll(s4, 2);
                a0 = addu(s0, v1);
                s6 = addiu(a0, 512);
                lw(v1, a0, 512);
                v1 = addiu(v1, 1);
                sw(v1, a0, 512);
                v1 = slti(v1, 12);
                if (v1 == 0) {
                    // 0x00231148
                    charge(ctx, 14);
                    v0 = addu(s0, s4);
                    s7 = addiu(v0, 520);
                    jal(ctx, 0x231150u, gen::fn_sub_488F30_00488f30);
                    v0 = v0 & 0x1;
                    sb(v0, s7, 0);
                    jal(ctx, 0x231160u, gen::fn_sub_488F30_00488f30);
                    v1 = 3;
                    div(v0, v1);
                    mfhi(s5);
                    a0 = 0;
                    for (;;) {  // while (a0 < 2)
                        // 0x002311bc
                        charge(ctx, 3);
                        v0 = slti(a0, 2);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00231180
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {  // while (v1 < 2)
                            // 0x002311ac
                            charge(ctx, 3);
                            v0 = slti(v1, 2);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0023118c
                            charge(ctx, 2);
                            if (s4 != v1) {
                                // 0x00231194
                                charge(ctx, 4);
                                v0 = addu(s0, v1);
                                lb(v0, v0, 522);
                                if (v0 == s5) {
                                    // 0x002311a4
                                    charge(ctx, 1);
                                    s5 = addiu(s5, 1);
                                }
                            }
                            // 0x002311a8
                            charge(ctx, 1);
                            v1 = addiu(v1, 1);
                        }
                        // 0x002311b8
                        charge(ctx, 1);
                        a0 = addiu(a0, 1);
                    }
                    // 0x002311c8
                    charge(ctx, 3);
                    v0 = slti(s5, 4);
                    if (v0 == 0) {
                        // 0x002311d4
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -6512);  // "bpp_panel.c"
                        a1 = 2003;
                        jal(ctx, 0x2311E0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 2003): `jr $ra` in retail, execution goes on
                    }
                    // 0x002311e8
                    charge(ctx, 6);
                    v0 = addu(s0, s4);
                    sb(s5, v0, 522);
                    lb(v1, s7, 0);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0023122c
                        charge(ctx, 5);
                        a0 = s2;
                        a1 = 10;
                        jal(ctx, 0x231234u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s3 = v0;
                    } else {
                        // 0x00231200
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00231210
                            charge(ctx, 7);
                            a0 = s2;
                            a1 = 9;
                            jal(ctx, 0x231218u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                            s3 = v0;
                        } else {
                            // 0x00231208
                            charge(ctx, 2);
                        }
                    }
                    // 0x00231240
                    charge(ctx, 10);
                    v0 = sll(s4, 8);
                    a0 = addu(s0, v0);
                    a1 = s3;
                    jal(ctx, 0x23124Cu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                    lw(a0, s6, 0);
                    v1 = 12;
                    div(a0, v1);
                    mfhi(v1);
                    sw(v1, s6, 0);
                }
                // 0x00231268
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x00231278
            charge(ctx, 4);
            lw(a0, s1, 2096);
            v1 = 4;
            if (a0 != v1) {
                // 0x002312a4
                charge(ctx, 7);
                v1 = 120;
                sb(v1, sp, 0x11C);
                v1 = 30;
                sb(v1, sp, 0x11D);
                sb(v1, sp, 0x11E);
                v1 = 255;
                sb(v1, sp, 0x11F);
            } else {
                // 0x00231288
                charge(ctx, 7);
                v1 = 255;
                sb(v1, sp, 0x11C);
                sb(v1, sp, 0x11D);
                sb(v1, sp, 0x11E);
                sb(v1, sp, 0x11F);
            }
            // 0x002312c0
            charge(ctx, 3);
            s1 = 0;
            for (;;) {  // while (s1 < 2)
                // 0x002313f4
                charge(ctx, 3);
                v1 = slti(s1, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002312cc
                charge(ctx, 13);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lwc1(f0, v0, 512);
                cvt_s_w(f1, f0);
                v0 = 0x41400000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x690000;
                lwc1(f2, v0, -6784);  // 0x68E580
                c_lt_s(f1, f2);
                if (!cond(ctx)) {
                    // 0x0023130c
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lwc1(f0, v0, -6780);  // 0x68E584
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x00231340
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lwc1(f0, v0, -6776);  // 0x68E588
                        c_lt_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x00231364
                            charge(ctx, 7);
                            sub_s(f2, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                            sub_s(f0, f1, f0);
                            div_s(f0, f2, f0);
                            sub_s(f1, f1, f0);
                        } else {
                            // 0x00231354
                            charge(ctx, 4);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                        }
                    } else {
                        // 0x00231320
                        charge(ctx, 8);
                        sub_s(f1, f1, f2);
                        sub_s(f0, f0, f2);
                        div_s(f1, f1, f0);
                    }
                } else {
                    // 0x00231300
                    charge(ctx, 3);
                    mtc1(zero, f1);
                }
                // 0x00231380
                charge(ctx, 10);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002313c0
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002313a8
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002313d8
                charge(ctx, 7);
                sb(v1, sp, 0x11F);
                v0 = sll(s1, 8);
                a0 = addu(s0, v0);
                a1 = addiu(sp, 0x11C);
                jal(ctx, 0x2313E8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s1 = addiu(s1, 1);
            }
            // 0x00231400
            charge(ctx, 11);
            s4 = 0;
            v1 = 0x42840000;
            mtc1(v1, f0);
            add_s(f22, f0, f29);
            v1 = 0x41300000;
            mtc1(v1, f0);
            add_s(f21, f0, f23);
            for (;;) {  // while (s4 < 2)
                // 0x002316c4
                charge(ctx, 3);
                v1 = slti(s4, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023142c
                charge(ctx, 8);
                v0 = addu(s0, s4);
                lb(s1, v0, 522);
                v1 = sll(s4, 2);
                v1 = addu(s0, v1);
                lw(a1, v1, 512);
                at = slti(a1, 8);
                if (at == 0) {
                    // 0x002314f0
                    charge(ctx, 22);
                    a0 = sll(s1, 4);
                    v1 = 0x690000;
                    v1 = addiu(v1, -6848);  // &0x68E540
                    v1 = addu(v1, a0);
                    lwc1(f1, v1, 0);
                    s6 = addiu(v1, 8);
                    lwc1(f0, v1, 8);
                    sub_s(f0, f0, f1);
                    lwc1(f4, gp, -32472);  // 0x7CAE18 = 0.95f
                    mtc1(zero, f2);
                    adda_s(f2, f1);
                    madd_s(f3, f4, f0);
                    s5 = addiu(v1, 4);
                    lwc1(f1, v1, 4);
                    s7 = addiu(v1, 12);
                    lwc1(f0, v1, 12);
                    sub_s(f0, f0, f1);
                    adda_s(f2, f1);
                    madd_s(f0, f4, f0);
                    add_s(f20, f3, f22);
                    add_s(f23, f0, f21);
                } else {
                    // 0x0023144c
                    charge(ctx, 41);
                    v1 = addiu(a1, 1);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x41000000;
                    mtc1(v1, f0);
                    div_s(f2, f1, f0);
                    v1 = 0x3F800000;
                    mtc1(v1, f0);
                    mul_s(f1, f0, f2);
                    v1 = 0x40000000;
                    mtc1(v1, f0);
                    mula_s(f0, f2);
                    mtc1(zero, f4);
                    msub_s(f2, f2, f1);
                    a0 = sll(s1, 4);
                    v1 = 0x690000;
                    v1 = addiu(v1, -6848);  // &0x68E540
                    v1 = addu(v1, a0);
                    lwc1(f1, v1, 0);
                    s6 = addiu(v1, 8);
                    lwc1(f0, gp, -32472);  // 0x7CAE18 = 0.95f
                    mul_s(f3, f0, f2);
                    lwc1(f0, v1, 8);
                    sub_s(f0, f0, f1);
                    adda_s(f4, f1);
                    madd_s(f2, f3, f0);
                    s5 = addiu(v1, 4);
                    lwc1(f1, v1, 4);
                    s7 = addiu(v1, 12);
                    lwc1(f0, v1, 12);
                    sub_s(f0, f0, f1);
                    adda_s(f4, f1);
                    madd_s(f0, f3, f0);
                    add_s(f20, f2, f22);
                    add_s(f23, f0, f21);
                }
                // 0x00231548
                charge(ctx, 19);
                v1 = addiu(a1, 1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x41400000;
                mtc1(v1, f0);
                div_s(f2, f1, f0);
                v1 = 0x3F000000;
                mtc1(v1, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f25, f1, f2);
                fp = addiu(v0, 0x208);
                lb(v1, v0, 520);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002315c0
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = 10;
                    jal(ctx, 0x2315C8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s3 = v0;
                } else {
                    // 0x00231594
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x002315a4
                        charge(ctx, 7);
                        a0 = s2;
                        a1 = 9;
                        jal(ctx, 0x2315ACu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s3 = v0;
                    } else {
                        // 0x0023159c
                        charge(ctx, 2);
                    }
                }
                // 0x002315d4
                charge(ctx, 24);
                swc1(f20, sp, 0x100);
                swc1(f23, sp, 0x104);
                lwc1(f0, s3, 12);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f25);
                swc1(f0, sp, 0x108);
                lwc1(f0, s3, 16);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f25);
                swc1(f0, sp, 0x10C);
                v1 = sll(s1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -6848);  // &0x68E540
                v0 = addu(v0, v1);
                lwc1(f1, s6, 0);
                lwc1(f0, v0, 0);
                sub_s(f25, f1, f0);
                lwc1(f1, s7, 0);
                lwc1(f0, s5, 0);
                sub_s(f23, f1, f0);
                lb(v1, fp, 0x0);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00231650
                    charge(ctx, 1);
                    lwc1(f24, gp, -31772);  // 0x7CB0D4 = 0.349066f
                } else {
                    // 0x00231634
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00231644
                        charge(ctx, 3);
                        lwc1(f24, gp, -31740);  // 0x7CB0F4 = -0.698132f
                    } else {
                        // 0x0023163c
                        charge(ctx, 2);
                    }
                }
                // 0x00231654
                charge(ctx, 28);
                mov_s(f12, f24);
                jal(ctx, 0x231658u, gen::fn_sinf_0052e878);
                mov_s(f20, f0);
                mov_s(f12, f24);
                jal(ctx, 0x231668u, gen::fn_cosf_0052e6d8);
                mula_s(f25, f0);
                msub_s(f0, f23, f20);
                swc1(f0, sp, 0x110);
                mov_s(f12, f24);
                jal(ctx, 0x231680u, gen::fn_sinf_0052e878);
                mov_s(f20, f0);
                mov_s(f12, f24);
                jal(ctx, 0x231690u, gen::fn_cosf_0052e6d8);
                mula_s(f23, f0);
                madd_s(f0, f25, f20);
                swc1(f0, sp, 0x114);
                v0 = sll(s4, 8);
                a0 = addu(s0, v0);
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x2316B8u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                s4 = addiu(s4, 1);
            }
            // 0x002316d0
            charge(ctx, 2);
            break;
        case 0x2316D8u:  // table[5]
            // 0x002316d8
            charge(ctx, 39);
            s0 = addiu(s1, 4192);
            lw(v0, s1, 5488);
            v0 = addiu(v0, 1);
            sw(v0, s1, 5488);
            a0 = s2;
            a1 = 11;
            jal(ctx, 0x2316F0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42A00000;
            mtc1(v1, f0);
            add_s(f0, f0, f29);
            swc1(f0, sp, 0xD0);
            v1 = 0x41980000;
            mtc1(v1, f0);
            add_s(f0, f0, f23);
            swc1(f0, sp, 0xD4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xD8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xDC);
            a0 = s0;
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x231740u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            a0 = addiu(s0, 256);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x231750u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            lw(v1, s0, 1296);
            v0 = 40;
            div(v1, v0);
            mfhi(v0);
            v1 = sra(v0, 1);
            if (i64(v0) < 0) {
                // 0x00231774
                charge(ctx, 2);
                v0 = addiu(v0, 1);
                v1 = sra(v0, 1);
            }
            // 0x0023177c
            charge(ctx, 3);
            v0 = 16;
            if (v1 != v0) {
                // 0x00231788
                charge(ctx, 3);
                v0 = 18;
                if (v1 == v0) {
                    goto L_00231794;
                }
                // 0x002317a4
                charge(ctx, 1);
                mtc1(zero, f2);
                goto L_002317a8;
            }
        L_00231794:
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f2);
        L_002317a8:
            charge(ctx, 21);
            v0 = 255;
            sb(v0, sp, 0x11C);
            sb(v0, sp, 0x11D);
            sb(v0, sp, 0x11E);
            v0 = 0x41F00000;
            mtc1(v0, f1);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f0, f0, f2);
            mul_s(f1, f1, f0);
            v0 = 0x42C80000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00231814
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002317fc
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0023182c
            charge(ctx, 13);
            sb(v1, sp, 0x11F);
            a0 = addiu(s0, 256);
            a1 = addiu(sp, 0x11C);
            jal(ctx, 0x231838u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s2;
            a1 = 12;
            jal(ctx, 0x231848u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s5 = v0;
            s4 = 0;
            for (;;) {  // while (s4 < 3)
                // 0x00231944
                charge(ctx, 3);
                v1 = slti(s4, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231860
                charge(ctx, 9);
                v1 = sll(s4, 2);
                a0 = addu(s0, v1);
                s1 = addiu(a0, 1280);
                lw(v1, a0, 1280);
                v1 = addiu(v1, 1);
                sw(v1, a0, 1280);
                v1 = slti(v1, 40);
                if (v1 == 0) {
                    // 0x00231884
                    charge(ctx, 8);
                    jal(ctx, 0x231884u, gen::fn_sub_488F30_00488f30);
                    v1 = 6;
                    divu(v0, v1);
                    mfhi(s3);
                    a0 = 0;
                    for (;;) {  // while (a0 < 3)
                        // 0x002318e0
                        charge(ctx, 3);
                        v0 = slti(a0, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002318a4
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {  // while (v1 < 3)
                            // 0x002318d0
                            charge(ctx, 3);
                            v0 = slti(v1, 3);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x002318b0
                            charge(ctx, 2);
                            if (s4 != v1) {
                                // 0x002318b8
                                charge(ctx, 4);
                                v0 = addu(s0, v1);
                                lb(v0, v0, 1292);
                                if (v0 == s3) {
                                    // 0x002318c8
                                    charge(ctx, 1);
                                    s3 = addiu(s3, 1);
                                }
                            }
                            // 0x002318cc
                            charge(ctx, 1);
                            v1 = addiu(v1, 1);
                        }
                        // 0x002318dc
                        charge(ctx, 1);
                        a0 = addiu(a0, 1);
                    }
                    // 0x002318ec
                    charge(ctx, 3);
                    v0 = slti(s3, 8);
                    if (v0 == 0) {
                        // 0x002318f8
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -6512);  // "bpp_panel.c"
                        a1 = 2158;
                        jal(ctx, 0x231904u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bpp_panel.c", 2158): `jr $ra` in retail, execution goes on
                    }
                    // 0x0023190c
                    charge(ctx, 13);
                    v0 = addu(s0, s4);
                    sb(s3, v0, 1292);
                    v0 = sll(s4, 8);
                    v0 = addu(s0, v0);
                    a0 = addiu(v0, 512);
                    a1 = s5;
                    jal(ctx, 0x231924u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                    lw(a0, s1, 0);
                    v1 = 40;
                    div(a0, v1);
                    mfhi(v1);
                    sw(v1, s1, 0);
                }
                // 0x00231940
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x00231950
            charge(ctx, 8);
            v1 = 255;
            sb(v1, sp, 0x11C);
            sb(v1, sp, 0x11D);
            sb(v1, sp, 0x11E);
            sb(v1, sp, 0x11F);
            s1 = 0;
            for (;;) {  // while (s1 < 3)
                // 0x00231a9c
                charge(ctx, 3);
                v1 = slti(s1, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231970
                charge(ctx, 13);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lwc1(f0, v0, 1280);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x690000;
                lwc1(f2, v0, -6640);  // 0x68E610
                c_lt_s(f1, f2);
                if (!cond(ctx)) {
                    // 0x002319b0
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lwc1(f0, v0, -6636);  // 0x68E614
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x002319e4
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lwc1(f0, v0, -6632);  // 0x68E618
                        c_lt_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x00231a08
                            charge(ctx, 7);
                            sub_s(f2, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                            sub_s(f0, f1, f0);
                            div_s(f0, f2, f0);
                            sub_s(f1, f1, f0);
                        } else {
                            // 0x002319f8
                            charge(ctx, 4);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                        }
                    } else {
                        // 0x002319c4
                        charge(ctx, 8);
                        sub_s(f1, f1, f2);
                        sub_s(f0, f0, f2);
                        div_s(f1, f1, f0);
                    }
                } else {
                    // 0x002319a4
                    charge(ctx, 3);
                    mtc1(zero, f1);
                }
                // 0x00231a24
                charge(ctx, 10);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00231a64
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00231a4c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00231a7c
                charge(ctx, 8);
                sb(v1, sp, 0x11F);
                v0 = sll(s1, 8);
                v0 = addu(s0, v0);
                a0 = addiu(v0, 512);
                a1 = addiu(sp, 0x11C);
                jal(ctx, 0x231A90u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s1 = addiu(s1, 1);
            }
            // 0x00231aa8
            charge(ctx, 11);
            s4 = 0;
            v1 = 0x42840000;
            mtc1(v1, f0);
            add_s(f21, f0, f29);
            v1 = 0x41300000;
            mtc1(v1, f0);
            add_s(f20, f0, f23);
            for (;;) {  // while (s4 < 3)
                // 0x00231c68
                charge(ctx, 3);
                v1 = slti(s4, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231ad4
                charge(ctx, 101);
                v0 = addu(s0, s4);
                lb(v1, v0, 1292);
                v0 = sll(s4, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, 1280);
                v0 = addiu(v0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                div_s(f5, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                mul_s(f1, f0, f5);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mula_s(f0, f5);
                mtc1(zero, f4);
                msub_s(f2, f5, f1);
                v1 = sll(v1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -6768);  // &0x68E590
                s3 = addu(v0, v1);
                lwc1(f1, s3, 0);
                s1 = addiu(s3, 8);
                lwc1(f0, gp, -32472);  // 0x7CAE18 = 0.95f
                mul_s(f3, f0, f2);
                lwc1(f0, s3, 8);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f2, f3, f0);
                s5 = addiu(s3, 4);
                lwc1(f1, s3, 4);
                s6 = addiu(s3, 12);
                lwc1(f0, s3, 12);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f0, f3, f0);
                add_s(f24, f2, f21);
                add_s(f23, f0, f20);
                v0 = 0x3E800000;
                mtc1(v0, f1);
                v0 = 0x3F000000;
                mtc1(v0, f0);
                adda_s(f4, f0);
                madd_s(f22, f1, f5);
                a0 = s2;
                a1 = 12;
                jal(ctx, 0x231BACu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                swc1(f24, sp, 0x100);
                swc1(f23, sp, 0x104);
                lwc1(f0, v0, kSpW);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f22);
                swc1(f0, sp, 0x108);
                lwc1(f0, v0, kSpH);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f22);
                swc1(f0, sp, 0x10C);
                lwc1(f1, s1, 0);
                lwc1(f0, s3, 0);
                sub_s(f24, f1, f0);
                lwc1(f1, s6, 0);
                lwc1(f0, s5, 0);
                sub_s(f23, f1, f0);
                mtc1(zero, f12);
                jal(ctx, 0x231BF8u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                mtc1(zero, f12);
                jal(ctx, 0x231C08u, gen::fn_cosf_0052e6d8);
                mula_s(f24, f0);
                mtc1(zero, f12);
                msub_s(f0, f23, f22);
                swc1(f0, sp, 0x110);
                jal(ctx, 0x231C20u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                mtc1(zero, f12);
                jal(ctx, 0x231C30u, gen::fn_cosf_0052e6d8);
                mula_s(f23, f0);
                madd_s(f0, f24, f22);
                swc1(f0, sp, 0x114);
                v0 = sll(s4, 8);
                v0 = addu(s0, v0);
                a0 = addiu(v0, 512);
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x231C5Cu, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                s4 = addiu(s4, 1);
            }
            // 0x00231c74
            charge(ctx, 2);
            break;
        case 0x231C7Cu:  // table[6]
            // 0x00231c7c
            charge(ctx, 24);
            s0 = addiu(s1, 4192);
            lw(v0, s1, 4960);
            v1 = addiu(v0, 1);
            sw(v1, s1, 4960);
            v0 = 20;
            div(v1, v0);
            mfhi(v0);
            sw(v0, s1, 4960);
            a0 = s2;
            a1 = 13;
            jal(ctx, 0x231CA4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42A00000;
            mtc1(v1, f0);
            add_s(f25, f0, f29);
            v1 = 0x41500000;
            mtc1(v1, f0);
            add_s(f3, f0, f23);
            lw(v1, s0, 768);
            at = slti(v1, 2);
            if (at == 0) {
                // 0x00231d04
                charge(ctx, 3);
                at = slti(v1, 12);
                if (at == 0) {
                    // 0x00231d74
                    charge(ctx, 1);
                    mov_s(f21, f25);
                } else {
                    // 0x00231d10
                    charge(ctx, 25);
                    v1 = addiu(v1, -2);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x41200000;
                    mtc1(v1, f0);
                    div_s(f1, f1, f0);
                    v1 = 0x3F800000;
                    mtc1(v1, f0);
                    sub_s(f2, f0, f1);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    mtc1(zero, f1);
                    adda_s(f1, f25);
                    madd_s(f21, f0, f2);
                    v1 = lui(0xC0E0);
                    mtc1(v1, f0);
                    adda_s(f1, f3);
                    madd_s(f3, f0, f2);
                }
            } else {
                // 0x00231cdc
                charge(ctx, 10);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                add_s(f21, f25, f0);
                v1 = lui(0xC0E0);
                mtc1(v1, f0);
                add_s(f3, f3, f0);
            }
            // 0x00231d78
            charge(ctx, 17);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            add_s(f20, f3, f0);
            swc1(f21, sp, 0xD0);
            swc1(f3, sp, 0xD4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            add_s(f0, f21, f0);
            swc1(f0, sp, 0xD8);
            swc1(f3, sp, 0xDC);
            swc1(f0, sp, 0xE0);
            swc1(f20, sp, 0xE4);
            swc1(f21, sp, 0xE8);
            swc1(f20, sp, 0xEC);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x00231de4
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231dbc
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 208);
                lwc1(f0, v0, 0);
                sub_s(f0, f0, f21);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                sub_s(f0, f0, f20);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x00231df0
            charge(ctx, 4);
            lw(v1, s0, 768);
            at = slti(v1, 2);
            if (at == 0) {
                // 0x00231e0c
                charge(ctx, 3);
                at = slti(v1, 12);
                if (at == 0) {
                    // 0x00231e94
                    charge(ctx, 1);
                    mtc1(zero, f24);
                } else {
                    // 0x00231e18
                    charge(ctx, 31);
                    v0 = addiu(v1, -2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f3, f0, f1);
                    lwc1(f0, gp, -31736);  // 0x7CB0F8 = 0.04f
                    mul_s(f1, f0, f3);
                    v0 = v1 & 0x1;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f0, f1, f0);
                    v0 = 0x40000000;
                    mtc1(v0, f2);
                    mul_s(f0, f2, f0);
                    lwc1(f1, gp, -32184);  // 0x7CAF38 = 3.14159f
                    mula_s(f1, f0);
                    lwc1(f0, gp, -32108);  // 0x7CAF84 = 0.01f
                    mul_s(f0, f0, f3);
                    mul_s(f0, f2, f0);
                    msub_s(f24, f1, f0);
                }
            } else {
                // 0x00231e00
                charge(ctx, 3);
                mtc1(zero, f24);
            }
            // 0x00231e98
            charge(ctx, 3);
            s1 = 0;
            for (;;) {  // while (s1 < 4)
                // 0x00231f18
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231ea4
                charge(ctx, 29);
                v0 = sll(s1, 3);
                v0 = addu(v0, sp);
                s4 = addiu(v0, 208);
                s3 = addiu(s4, 4);
                mov_s(f12, f24);
                jal(ctx, 0x231EB8u, gen::fn_sinf_0052e878);
                mov_s(f26, f0);
                lwc1(f22, s3, 0);
                mov_s(f12, f24);
                jal(ctx, 0x231ECCu, gen::fn_cosf_0052e6d8);
                lwc1(f1, s4, 0);
                mula_s(f1, f0);
                msub_s(f27, f22, f26);
                mov_s(f12, f24);
                jal(ctx, 0x231EE4u, gen::fn_sinf_0052e878);
                mov_s(f26, f0);
                lwc1(f22, s4, 0);
                mov_s(f12, f24);
                jal(ctx, 0x231EF8u, gen::fn_cosf_0052e6d8);
                lwc1(f1, s3, 0);
                mula_s(f1, f0);
                madd_s(f0, f22, f26);
                swc1(f27, s4, 0);
                swc1(f0, s3, 0);
                s1 = addiu(s1, 1);
            }
            // 0x00231f24
            charge(ctx, 3);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x00231f58
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00231f30
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 208);
                lwc1(f0, v0, 0);
                add_s(f0, f0, f21);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                add_s(f0, f0, f20);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x00231f64
            charge(ctx, 8);
            a0 = s0;
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x231F6Cu, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
            lw(v0, s0, 768);
            at = slti(v0, 2);
            if (at == 0) {
                // 0x00231f90
                charge(ctx, 3);
                at = slti(v0, 12);
                if (at == 0) {
                    // 0x00231fd0
                    charge(ctx, 3);
                    at = slti(v0, 18);
                    if (at == 0) {
                        // 0x00231fec
                        charge(ctx, 3);
                        at = slti(v0, 20);
                        if (at == 0) {
                            // 0x00232030
                            charge(ctx, 1);
                            mtc1(zero, f1);
                        } else {
                            // 0x00231ff8
                            charge(ctx, 14);
                            v0 = addiu(v0, -18);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x40000000;
                            mtc1(v0, f0);
                            div_s(f1, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            sub_s(f1, f0, f1);
                        }
                    } else {
                        // 0x00231fdc
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                    }
                } else {
                    // 0x00231f9c
                    charge(ctx, 13);
                    v0 = addiu(v0, -2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                }
            } else {
                // 0x00231f84
                charge(ctx, 3);
                mtc1(zero, f1);
            }
            // 0x00232034
            charge(ctx, 14);
            v0 = 255;
            sb(v0, sp, 0x11C);
            sb(v0, sp, 0x11D);
            sb(v0, sp, 0x11E);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00232084
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0023206c
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0023209c
            charge(ctx, 21);
            sb(v1, sp, 0x11F);
            a0 = s0;
            a1 = addiu(sp, 0x11C);
            jal(ctx, 0x2320A8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s2;
            a1 = 14;
            jal(ctx, 0x2320B8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x42C80000;
            mtc1(v1, f0);
            add_s(f22, f0, f29);
            v1 = 0x41F00000;
            mtc1(v1, f0);
            add_s(f23, f0, f23);
            lw(v1, s0, 768);
            at = slti(v1, 6);
            if (at == 0) {
                // 0x00232118
                charge(ctx, 3);
                at = slti(v1, 15);
                if (at == 0) {
                    // 0x00232188
                    charge(ctx, 1);
                    mov_s(f1, f23);
                } else {
                    // 0x00232124
                    charge(ctx, 25);
                    v1 = addiu(v1, -6);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x41100000;
                    mtc1(v1, f0);
                    div_s(f1, f1, f0);
                    v1 = 0x3F800000;
                    mtc1(v1, f0);
                    sub_s(f2, f0, f1);
                    v1 = 0x40A00000;
                    mtc1(v1, f0);
                    mtc1(zero, f1);
                    adda_s(f1, f22);
                    madd_s(f22, f0, f2);
                    v1 = lui(0xC080);
                    mtc1(v1, f0);
                    adda_s(f1, f23);
                    madd_s(f1, f0, f2);
                }
            } else {
                // 0x002320f0
                charge(ctx, 10);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                add_s(f22, f22, f0);
                v1 = lui(0xC080);
                mtc1(v1, f0);
                add_s(f1, f23, f0);
            }
            // 0x0023218c
            charge(ctx, 17);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            add_s(f21, f1, f0);
            swc1(f22, sp, 0xD0);
            swc1(f1, sp, 0xD4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            add_s(f0, f22, f0);
            swc1(f0, sp, 0xD8);
            swc1(f1, sp, 0xDC);
            swc1(f0, sp, 0xE0);
            swc1(f21, sp, 0xE4);
            swc1(f22, sp, 0xE8);
            swc1(f21, sp, 0xEC);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x002321f8
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002321d0
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 208);
                lwc1(f0, v0, 0);
                sub_s(f0, f0, f22);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                sub_s(f0, f0, f21);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x00232204
            charge(ctx, 4);
            lw(v1, s0, 768);
            at = slti(v1, 6);
            if (at == 0) {
                // 0x00232220
                charge(ctx, 3);
                at = slti(v1, 15);
                if (at == 0) {
                    // 0x002322a8
                    charge(ctx, 1);
                    mtc1(zero, f20);
                } else {
                    // 0x0023222c
                    charge(ctx, 31);
                    v0 = addiu(v1, -6);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41100000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f3, f0, f1);
                    lwc1(f0, gp, -32116);  // 0x7CAF7C = 0.02f
                    mul_s(f1, f0, f3);
                    v0 = v1 & 0x1;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f0, f1, f0);
                    v0 = 0x40000000;
                    mtc1(v0, f2);
                    mul_s(f0, f2, f0);
                    lwc1(f1, gp, -32184);  // 0x7CAF38 = 3.14159f
                    mula_s(f1, f0);
                    lwc1(f0, gp, -32108);  // 0x7CAF84 = 0.01f
                    mul_s(f0, f0, f3);
                    mul_s(f0, f2, f0);
                    msub_s(f20, f1, f0);
                }
            } else {
                // 0x00232214
                charge(ctx, 3);
                mtc1(zero, f20);
            }
            // 0x002322ac
            charge(ctx, 3);
            s1 = 0;
            for (;;) {  // while (s1 < 4)
                // 0x0023232c
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002322b8
                charge(ctx, 29);
                v0 = sll(s1, 3);
                v0 = addu(v0, sp);
                s4 = addiu(v0, 208);
                s3 = addiu(s4, 4);
                mov_s(f12, f20);
                jal(ctx, 0x2322CCu, gen::fn_sinf_0052e878);
                mov_s(f26, f0);
                lwc1(f24, s3, 0);
                mov_s(f12, f20);
                jal(ctx, 0x2322E0u, gen::fn_cosf_0052e6d8);
                lwc1(f1, s4, 0);
                mula_s(f1, f0);
                msub_s(f27, f24, f26);
                mov_s(f12, f20);
                jal(ctx, 0x2322F8u, gen::fn_sinf_0052e878);
                mov_s(f26, f0);
                lwc1(f24, s4, 0);
                mov_s(f12, f20);
                jal(ctx, 0x23230Cu, gen::fn_cosf_0052e6d8);
                lwc1(f1, s3, 0);
                mula_s(f1, f0);
                madd_s(f0, f24, f26);
                swc1(f27, s4, 0);
                swc1(f0, s3, 0);
                s1 = addiu(s1, 1);
            }
            // 0x00232338
            charge(ctx, 3);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x0023236c
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00232344
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 208);
                lwc1(f0, v0, 0);
                add_s(f0, f0, f22);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                add_s(f0, f0, f21);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x00232378
            charge(ctx, 8);
            a0 = addiu(s0, 256);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x232380u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
            lw(v0, s0, 768);
            at = slti(v0, 6);
            if (at == 0) {
                // 0x002323a4
                charge(ctx, 3);
                at = slti(v0, 15);
                if (at == 0) {
                    // 0x002323e4
                    charge(ctx, 3);
                    at = slti(v0, 18);
                    if (at == 0) {
                        // 0x00232400
                        charge(ctx, 12);
                        v0 = addiu(v0, -18);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f1, f0, f1);
                    } else {
                        // 0x002323f0
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                    }
                } else {
                    // 0x002323b0
                    charge(ctx, 13);
                    v0 = addiu(v0, -6);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41100000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                }
            } else {
                // 0x00232398
                charge(ctx, 3);
                mtc1(zero, f1);
            }
            // 0x00232430
            charge(ctx, 14);
            v0 = 255;
            sb(v0, sp, 0x11C);
            sb(v0, sp, 0x11D);
            sb(v0, sp, 0x11E);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00232480
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00232468
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00232498
            charge(ctx, 13);
            sb(v1, sp, 0x11F);
            a0 = addiu(s0, 256);
            a1 = addiu(sp, 0x11C);
            jal(ctx, 0x2324A4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            a0 = s2;
            a1 = 14;
            jal(ctx, 0x2324B4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            lw(v1, s0, 768);
            at = slti(v1, 7);
            if (at == 0) {
                // 0x002324f4
                charge(ctx, 3);
                at = slti(v1, 16);
                if (at != 0) {
                    // 0x00232500
                    charge(ctx, 23);
                    v1 = addiu(v1, -7);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    v1 = 0x41100000;
                    mtc1(v1, f0);
                    div_s(f1, f1, f0);
                    v1 = 0x3F800000;
                    mtc1(v1, f0);
                    sub_s(f2, f0, f1);
                    v1 = lui(0xC040);
                    mtc1(v1, f0);
                    mtc1(zero, f1);
                    adda_s(f1, f25);
                    madd_s(f25, f0, f2);
                    v1 = lui(0xC0A0);
                    mtc1(v1, f0);
                    adda_s(f1, f23);
                    madd_s(f23, f0, f2);
                }
            } else {
                // 0x002324cc
                charge(ctx, 10);
                v1 = lui(0xC040);
                mtc1(v1, f0);
                add_s(f25, f25, f0);
                v1 = lui(0xC0A0);
                mtc1(v1, f0);
                add_s(f23, f23, f0);
            }
            // 0x0023255c
            charge(ctx, 23);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            add_s(f20, f23, f0);
            swc1(f25, sp, 0xD0);
            swc1(f23, sp, 0xD4);
            lw(v0, v0, kSpW);
            v1 = sll(v0, 1);
            v0 = 3;
            div(v1, v0);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f25, f0);
            swc1(f0, sp, 0xD8);
            swc1(f23, sp, 0xDC);
            swc1(f0, sp, 0xE0);
            swc1(f20, sp, 0xE4);
            swc1(f25, sp, 0xE8);
            swc1(f20, sp, 0xEC);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x002325e0
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002325b8
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 208);
                lwc1(f0, v0, 0);
                sub_s(f0, f0, f25);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                sub_s(f0, f0, f20);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x002325ec
            charge(ctx, 4);
            lw(v1, s0, 768);
            at = slti(v1, 7);
            if (at == 0) {
                // 0x00232608
                charge(ctx, 3);
                at = slti(v1, 16);
                if (at == 0) {
                    // 0x00232690
                    charge(ctx, 1);
                    mtc1(zero, f24);
                } else {
                    // 0x00232614
                    charge(ctx, 31);
                    v0 = addiu(v1, -7);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41100000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f3, f0, f1);
                    lwc1(f0, gp, -32116);  // 0x7CAF7C = 0.02f
                    mul_s(f1, f0, f3);
                    v0 = v1 & 0x1;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f0, f1, f0);
                    v0 = 0x40000000;
                    mtc1(v0, f2);
                    mul_s(f0, f2, f0);
                    lwc1(f1, gp, -32184);  // 0x7CAF38 = 3.14159f
                    mula_s(f1, f0);
                    lwc1(f0, gp, -32108);  // 0x7CAF84 = 0.01f
                    mul_s(f0, f0, f3);
                    mul_s(f0, f2, f0);
                    msub_s(f24, f1, f0);
                }
            } else {
                // 0x002325fc
                charge(ctx, 3);
                mtc1(zero, f24);
            }
            // 0x00232694
            charge(ctx, 5);
            lwc1(f0, gp, -31748);  // 0x7CB0EC = -1.25664f
            add_s(f24, f24, f0);
            s1 = 0;
            for (;;) {  // while (s1 < 4)
                // 0x0023271c
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002326a8
                charge(ctx, 29);
                v0 = sll(s1, 3);
                v0 = addu(v0, sp);
                s3 = addiu(v0, 208);
                s2 = addiu(s3, 4);
                mov_s(f12, f24);
                jal(ctx, 0x2326BCu, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                lwc1(f21, s2, 0);
                mov_s(f12, f24);
                jal(ctx, 0x2326D0u, gen::fn_cosf_0052e6d8);
                lwc1(f1, s3, 0);
                mula_s(f1, f0);
                msub_s(f23, f21, f22);
                mov_s(f12, f24);
                jal(ctx, 0x2326E8u, gen::fn_sinf_0052e878);
                mov_s(f22, f0);
                lwc1(f21, s3, 0);
                mov_s(f12, f24);
                jal(ctx, 0x2326FCu, gen::fn_cosf_0052e6d8);
                lwc1(f1, s2, 0);
                mula_s(f1, f0);
                madd_s(f0, f21, f22);
                swc1(f23, s3, 0);
                swc1(f0, s2, 0);
                s1 = addiu(s1, 1);
            }
            // 0x00232728
            charge(ctx, 3);
            v1 = 0;
            for (;;) {  // while (v1 < 4)
                // 0x0023275c
                charge(ctx, 3);
                v0 = slti(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00232734
                charge(ctx, 10);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 208);
                lwc1(f0, v0, 0);
                add_s(f0, f0, f25);
                swc1(f0, v0, 0);
                lwc1(f0, v0, 4);
                add_s(f0, f0, f20);
                swc1(f0, v0, 4);
                v1 = addiu(v1, 1);
            }
            // 0x00232768
            charge(ctx, 8);
            a0 = addiu(s0, 512);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x232770u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
            lw(v0, s0, 768);
            at = slti(v0, 7);
            if (at == 0) {
                // 0x00232794
                charge(ctx, 3);
                at = slti(v0, 16);
                if (at == 0) {
                    // 0x002327d4
                    charge(ctx, 3);
                    at = slti(v0, 18);
                    if (at == 0) {
                        // 0x002327f0
                        charge(ctx, 12);
                        v0 = addiu(v0, -18);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f1, f0, f1);
                    } else {
                        // 0x002327e0
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f1);
                    }
                } else {
                    // 0x002327a0
                    charge(ctx, 13);
                    v0 = addiu(v0, -7);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41100000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                }
            } else {
                // 0x00232788
                charge(ctx, 3);
                mtc1(zero, f1);
            }
            // 0x00232820
            charge(ctx, 14);
            v0 = 255;
            sb(v0, sp, 0x11C);
            sb(v0, sp, 0x11D);
            sb(v0, sp, 0x11E);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f1);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00232870
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00232858
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00232888
            charge(ctx, 7);
            sb(v1, sp, 0x11F);
            a0 = addiu(s0, 512);
            a1 = addiu(sp, 0x11C);
            jal(ctx, 0x232894u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            break;
        case 0x2328A4u:  // table[7]
            // 0x002328a4
            charge(ctx, 7);
            s4 = addiu(s1, 4192);
            lw(v1, s1, 5244);
            v1 = addiu(v1, 1);
            sw(v1, s1, 5244);
            s1 = 0;
            for (;;) {  // while (s1 < 4)
                // 0x00232994
                charge(ctx, 3);
                v1 = slti(s1, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002328c0
                charge(ctx, 9);
                v1 = sll(s1, 2);
                a0 = addu(s4, v1);
                s5 = addiu(a0, 1024);
                lw(v1, a0, 1024);
                v1 = addiu(v1, 1);
                sw(v1, a0, 1024);
                v1 = slti(v1, 40);
                if (v1 == 0) {
                    // 0x002328e4
                    charge(ctx, 17);
                    s0 = addu(s4, s1);
                    s6 = addiu(s0, 1040);
                    jal(ctx, 0x2328ECu, gen::fn_sub_488F30_00488f30);
                    v0 = v0 & 0x1;
                    sb(v0, s6, 0);
                    jal(ctx, 0x2328FCu, gen::fn_sub_488F30_00488f30);
                    sb(v0, s0, 1044);
                    jal(ctx, 0x232908u, gen::fn_sub_488F30_00488f30);
                    v0 = v0 & 0x1;
                    sb(v0, s0, 1048);
                    lb(v1, s6, 0);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00232954
                        charge(ctx, 5);
                        a0 = s2;
                        a1 = 16;
                        jal(ctx, 0x23295Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s3 = v0;
                    } else {
                        // 0x00232928
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00232938
                            charge(ctx, 7);
                            a0 = s2;
                            a1 = 15;
                            jal(ctx, 0x232940u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                            s3 = v0;
                        } else {
                            // 0x00232930
                            charge(ctx, 2);
                        }
                    }
                    // 0x00232968
                    charge(ctx, 10);
                    v0 = sll(s1, 8);
                    a0 = addu(s4, v0);
                    a1 = s3;
                    jal(ctx, 0x232974u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
                    lw(a0, s5, 0);
                    v1 = 40;
                    div(a0, v1);
                    mfhi(v1);
                    sw(v1, s5, 0);
                }
                // 0x00232990
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x002329a0
            charge(ctx, 8);
            v1 = 255;
            sb(v1, sp, 0x11C);
            sb(v1, sp, 0x11D);
            sb(v1, sp, 0x11E);
            sb(v1, sp, 0x11F);
            s0 = 0;
            for (;;) {  // while (s0 < 4)
                // 0x00232ae8
                charge(ctx, 3);
                v1 = slti(s0, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002329c0
                charge(ctx, 13);
                v0 = sll(s0, 2);
                v0 = addu(s4, v0);
                lwc1(f0, v0, 1024);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x690000;
                lwc1(f2, v0, -6864);  // 0x68E530
                c_lt_s(f1, f2);
                if (!cond(ctx)) {
                    // 0x00232a00
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lwc1(f0, v0, -6860);  // 0x68E534
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x00232a34
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lwc1(f0, v0, -6856);  // 0x68E538
                        c_lt_s(f1, f0);
                        if (!cond(ctx)) {
                            // 0x00232a58
                            charge(ctx, 7);
                            sub_s(f2, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                            sub_s(f0, f1, f0);
                            div_s(f0, f2, f0);
                            sub_s(f1, f1, f0);
                        } else {
                            // 0x00232a48
                            charge(ctx, 4);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                        }
                    } else {
                        // 0x00232a14
                        charge(ctx, 8);
                        sub_s(f1, f1, f2);
                        sub_s(f0, f0, f2);
                        div_s(f1, f1, f0);
                    }
                } else {
                    // 0x002329f4
                    charge(ctx, 3);
                    mtc1(zero, f1);
                }
                // 0x00232a74
                charge(ctx, 10);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00232ab4
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00232a9c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00232acc
                charge(ctx, 7);
                sb(v1, sp, 0x11F);
                v0 = sll(s0, 8);
                a0 = addu(s4, v0);
                a1 = addiu(sp, 0x11C);
                jal(ctx, 0x232ADCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                s0 = addiu(s0, 1);
            }
            // 0x00232af4
            charge(ctx, 11);
            s1 = 0;
            v1 = 0x42840000;
            mtc1(v1, f0);
            add_s(f25, f0, f29);
            v1 = 0x41300000;
            mtc1(v1, f0);
            add_s(f24, f0, f23);
            for (;;) {  // while (s1 < 4)
                // 0x00232d5c
                charge(ctx, 3);
                v1 = slti(s1, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00232b20
                charge(ctx, 63);
                v0 = sll(s1, 2);
                v0 = addu(s4, v0);
                lw(v0, v0, 1024);
                v0 = addiu(v0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                div_s(f5, f1, f0);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f0, f5);
                mtc1(zero, f4);
                mula_s(f4, f5);
                msub_s(f2, f5, f0);
                v1 = sll(s1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -6928);  // &0x68E4F0
                v0 = addu(v0, v1);
                lwc1(f1, v0, 0);
                s0 = addiu(v0, 8);
                lwc1(f0, gp, -32472);  // 0x7CAE18 = 0.95f
                mul_s(f3, f0, f2);
                lwc1(f0, v0, 8);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f2, f3, f0);
                s5 = addiu(v0, 4);
                lwc1(f1, v0, 4);
                s6 = addiu(v0, 12);
                lwc1(f0, v0, 12);
                sub_s(f0, f0, f1);
                adda_s(f4, f1);
                madd_s(f0, f3, f0);
                add_s(f22, f2, f25);
                add_s(f21, f0, f24);
                v0 = 0x3E800000;
                mtc1(v0, f1);
                v0 = 0x3F000000;
                mtc1(v0, f0);
                adda_s(f4, f0);
                madd_s(f23, f1, f5);
                a0 = addu(s4, s1);
                lb(v0, a0, 1044);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -32264);  // 0x7CAEE8 = 6.28319f
                mul_s(f1, f0, f1);
                v0 = 0x43800000;
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                lb(v1, a0, 1048);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00232c40
                    charge(ctx, 3);
                    lwc1(f0, gp, -32496);  // 0x7CAE00 = 1.5708f
                    adda_s(f4, f20);
                    msub_s(f20, f0, f5);
                } else {
                    // 0x00232c1c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00232c2c
                        charge(ctx, 5);
                        lwc1(f0, gp, -32496);  // 0x7CAE00 = 1.5708f
                        adda_s(f4, f20);
                        madd_s(f20, f0, f5);
                    } else {
                        // 0x00232c24
                        charge(ctx, 2);
                    }
                }
                // 0x00232c4c
                charge(ctx, 4);
                lb(v1, a0, 1040);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00232c88
                    charge(ctx, 5);
                    a0 = s2;
                    a1 = 16;
                    jal(ctx, 0x232C90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s3 = v0;
                } else {
                    // 0x00232c5c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00232c6c
                        charge(ctx, 7);
                        a0 = s2;
                        a1 = 15;
                        jal(ctx, 0x232C74u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                        s3 = v0;
                    } else {
                        // 0x00232c64
                        charge(ctx, 2);
                    }
                }
                // 0x00232c9c
                charge(ctx, 48);
                swc1(f22, sp, 0x100);
                swc1(f21, sp, 0x104);
                lwc1(f0, s3, 12);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f23);
                swc1(f0, sp, 0x108);
                lwc1(f0, s3, 16);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f23);
                swc1(f0, sp, 0x10C);
                v1 = sll(s1, 4);
                v0 = 0x690000;
                v0 = addiu(v0, -6928);  // &0x68E4F0
                v0 = addu(v0, v1);
                lwc1(f1, s0, 0);
                lwc1(f0, v0, 0);
                sub_s(f23, f1, f0);
                lwc1(f1, s6, 0);
                lwc1(f0, s5, 0);
                sub_s(f22, f1, f0);
                mov_s(f12, f20);
                jal(ctx, 0x232CF0u, gen::fn_sinf_0052e878);
                mov_s(f21, f0);
                mov_s(f12, f20);
                jal(ctx, 0x232D00u, gen::fn_cosf_0052e6d8);
                mula_s(f23, f0);
                msub_s(f0, f22, f21);
                swc1(f0, sp, 0x110);
                mov_s(f12, f20);
                jal(ctx, 0x232D18u, gen::fn_sinf_0052e878);
                mov_s(f21, f0);
                mov_s(f12, f20);
                jal(ctx, 0x232D28u, gen::fn_cosf_0052e6d8);
                mula_s(f22, f0);
                madd_s(f0, f23, f21);
                swc1(f0, sp, 0x114);
                v0 = sll(s1, 8);
                a0 = addu(s4, v0);
                a1 = addiu(sp, 0x100);
                a2 = addiu(sp, 0x110);
                a3 = addiu(sp, 0x108);
                jal(ctx, 0x232D50u, gen::fn_sub_21E170_0021e170);  // (quad, ...): a rotated / scaled rectangle
                s1 = addiu(s1, 1);
            }
            // 0x00232d68
            charge(ctx, 2);
            break;
        case 0x232D70u:  // table[8]
            // 0x00232d70
            charge(ctx, 26);
            a0 = s2;
            a1 = 17;
            jal(ctx, 0x232D78u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x421C0000;
            mtc1(v1, f0);
            add_s(f0, f0, f29);
            swc1(f0, sp, 0xD0);
            v1 = 0x41500000;
            mtc1(v1, f0);
            add_s(f0, f0, f23);
            swc1(f0, sp, 0xD4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xD8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xDC);
            a0 = addiu(s1, 4192);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x232DC8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            break;
        case 0x232DD8u:  // table[9]
            // 0x00232dd8
            charge(ctx, 25);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x232DE0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x41F00000;
            mtc1(v1, f2);
            add_s(f0, f2, f29);
            add_s(f0, f2, f0);
            swc1(f0, sp, 0xD0);
            v1 = 0x41300000;
            mtc1(v1, f1);
            add_s(f0, f2, f23);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xD4);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xD8);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xDC);
            a0 = addiu(s1, 4192);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x232E34u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00232e3c (the shared epilogue, written out on this path)
    charge(ctx, 25);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f31, sp, 0x2C);
    lwc1(f30, sp, 0x28);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x00232EA0 sub_232EA0 -- 2276 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_DrawAilment](panel) draws the ailment icon's quads (jump table 0x7B7810 on the icon).
void sub_232EA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00232ea0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 4;
    jal(ctx, 0x232EC0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s1 = v0;
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x232EE0u, v0.u());
    lw(v1, s2, kBpnIcon);
    at = sltiu(v1, 11);
    if (at != 0) {
        // 0x00232ef8
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 30736);  // &0x7B7810
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x232F14u:  // table[0]
            // 0x00232f14
            charge(ctx, 25);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 0;
            jal(ctx, 0x232F20u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x232F2Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x232F40u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x232F54u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x232F64u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x00232fcc
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00232f78
                charge(ctx, 21);
                v0 = sll(s0, 8);
                s3 = addu(s2, v0);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x232FA0u, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x232FC0u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00232fd8
            charge(ctx, 2);
            break;
        case 0x232FE0u:  // table[1]
            // 0x00232fe0
            charge(ctx, 25);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x232FECu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x232FF8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x23300Cu, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x233020u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x233030u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x00233098
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00233044
                charge(ctx, 21);
                v0 = sll(s0, 9);
                s3 = addu(s2, v0);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x23306Cu, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x23308Cu, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x002330a4
            charge(ctx, 2);
            break;
        case 0x2330ACu:  // table[2]
            // 0x002330ac
            charge(ctx, 25);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 3;
            jal(ctx, 0x2330B8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x2330C4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x2330D8u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x2330ECu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x2330FCu, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x00233164
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00233110
                charge(ctx, 21);
                v0 = sll(s0, 8);
                s3 = addu(s2, v0);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x233138u, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x233158u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00233170
            charge(ctx, 2);
            break;
        case 0x233178u:  // table[3]
            // 0x00233178
            charge(ctx, 58);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 8;
            jal(ctx, 0x233184u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x233190u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x2331A4u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x2331B8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x2331C8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2331F0u, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x233210u, v0.u());
            a0 = addiu(s2, 256);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x233230u, v0.u());
            a0 = addiu(s2, 256);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x233250u, v0.u());
            break;
        case 0x233260u:  // table[4, 10]
            // 0x00233260
            charge(ctx, 25);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 9;
            jal(ctx, 0x23326Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x233278u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x23328Cu, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x2332A0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x2332B0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0;
            for (;;) {  // while (s0 < 2)
                // 0x00233318
                charge(ctx, 3);
                v1 = slti(s0, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002332c4
                charge(ctx, 21);
                v0 = sll(s0, 8);
                s3 = addu(s2, v0);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2332ECu, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x23330Cu, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00233324
            charge(ctx, 2);
            break;
        case 0x23332Cu:  // table[5]
            // 0x0023332c
            charge(ctx, 59);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 11;
            jal(ctx, 0x233338u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x233344u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x233358u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x23336Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x23337Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2333A4u, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2333C4u, v0.u());
            a0 = addiu(s2, 256);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2333E4u, v0.u());
            a0 = addiu(s2, 256);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x233404u, v0.u());
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x00233470
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00233418
                charge(ctx, 22);
                v0 = sll(s0, 8);
                v0 = addu(s2, v0);
                s3 = addiu(v0, 512);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x233444u, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x233464u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x0023347c
            charge(ctx, 2);
            break;
        case 0x233484u:  // table[6]
            // 0x00233484
            charge(ctx, 25);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 13;
            jal(ctx, 0x233490u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x23349Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x2334B0u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x2334C4u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x2334D4u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0;
            for (;;) {  // while (s0 < 3)
                // 0x0023353c
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002334e8
                charge(ctx, 21);
                v0 = sll(s0, 8);
                s3 = addu(s2, v0);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x233510u, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x233530u, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00233548
            charge(ctx, 2);
            break;
        case 0x233550u:  // table[7]
            // 0x00233550
            charge(ctx, 25);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 15;
            jal(ctx, 0x23355Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x233568u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x23357Cu, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x233590u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x2335A0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0;
            for (;;) {  // while (s0 < 4)
                // 0x00233608
                charge(ctx, 3);
                v1 = slti(s0, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002335b4
                charge(ctx, 21);
                v0 = sll(s0, 8);
                s3 = addu(s2, v0);
                s1 = 0x960000;
                s1 = addiu(s1, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2335DCu, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x2335FCu, v0.u());
                s0 = addiu(s0, 1);
            }
            // 0x00233614
            charge(ctx, 2);
            break;
        case 0x23361Cu:  // table[8]
            // 0x0023361c
            charge(ctx, 42);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 17;
            jal(ctx, 0x233628u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x233634u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x233648u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x23365Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x23366Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x233694u, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2336B4u, v0.u());
            break;
        case 0x2336C4u:  // table[9]
            // 0x002336c4
            charge(ctx, 40);
            s2 = addiu(s2, 4192);
            a0 = s1;
            a1 = 0;
            jal(ctx, 0x2336D0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x2336DCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s0, 0);
            jalr(ctx, 0x2336F0u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x233704u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x233714u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23373Cu, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x23375Cu, v0.u());
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00233764 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0023F480 sub_23F480 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [biMain_Register](work) bi_main.c: asserts the slot is free (line 146), clears the flags of the 16 records
// (3,920 bytes each) and stores the work.
void sub_23F480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023f480
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBiMain);  // 0x7CE31C bi_main.c work (16 x 3,920-byte records)
    if (v1 != 0) {
        // 0x0023f49c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 146;
        jal(ctx, 0x23F4A8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bi_main.c", 146): `jr $ra` in retail, execution goes on
    }
    // 0x0023f4b0
    charge(ctx, 4);
    a1 = 0;
    a0 = 3920;
    for (;;) {  // while (a1 < 16)
        // 0x0023f4d0
        charge(ctx, 3);
        v1 = slti(a1, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023f4c0
        charge(ctx, 4);
        mult(v1, a1, a0);
        v1 = addu(s0, v1);
        sw(zero, v1, 0);
        a1 = addiu(a1, 1);
    }
    // 0x0023f4dc
    charge(ctx, 6);
    sw(s0, gp, kGpBiMain);  // 0x7CE31C bi_main.c work (16 x 3,920-byte records)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0023F500 sub_23F500 -- 60 bytes; frame 0x10: ra sp+0x0
// [biMain_Unregister] clears the bi_main.c slot (K_Assert 138 if it is empty).
void sub_23F500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023f500
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBiMain);  // 0x7CE31C bi_main.c work (16 x 3,920-byte records)
    if (v1 == 0) {
        // 0x0023f514
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6032);  // "bi_main.c"
        a1 = 138;
        jal(ctx, 0x23F520u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bi_main.c", 138): `jr $ra` in retail, execution goes on
    }
    // 0x0023f528 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sw(zero, gp, kGpBiMain);  // 0x7CE31C bi_main.c work (16 x 3,920-byte records)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
