// The battle code, sixth pass (slice battle6; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle6.h for the
// layouts): the battle panel modules -- the command panel's draw and persona marks (bpc_main.c), the message window
// (bpm_main.c), the item message (bpe_main.c), the bas work, the two battle tutorials (bp_tut.c / bp_tuta.c), the bpo
// banner, the persona status (bp_persona.c) and the select marker (bp_select.c). The bodies are p3fes_handgen's
// (frame, spills, $ra links, every register, cycle charges, check points); this file names their offsets (battle3.h's
// b3::, battle4.h's b4::, battle5.h's b5:: records reused, this slice's in b6::) and gives each function its role --
// proposed names in brackets (ADR-0009), symbols in code are functions.json's. Still-recompiled callees are reached
// through their gen:: entry points (the relaxed callee rule).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle6.h"

namespace p3fes::recomp_gen {
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_fclMisc_CreatePsStatusTasks_003c9850(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_msgWinClose_003c7650(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_110F80_00110f80(p3fes::EEContext&);
void fn_sub_1114B0_001114b0(p3fes::EEContext&);
void fn_sub_111500_00111500(p3fes::EEContext&);
void fn_sub_111530_00111530(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_1749A0_001749a0(p3fes::EEContext&);
void fn_sub_1756F0_001756f0(p3fes::EEContext&);
void fn_sub_1775A0_001775a0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1FE580_001fe580(p3fes::EEContext&);
void fn_sub_1FF430_001ff430(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21C550_0021c550(p3fes::EEContext&);
void fn_sub_21C7F0_0021c7f0(p3fes::EEContext&);
void fn_sub_21C860_0021c860(p3fes::EEContext&);
void fn_sub_21C8B0_0021c8b0(p3fes::EEContext&);
void fn_sub_21C930_0021c930(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_242C20_00242c20(p3fes::EEContext&);
void fn_sub_243150_00243150(p3fes::EEContext&);
void fn_sub_244E80_00244e80(p3fes::EEContext&);
void fn_sub_2459D0_002459d0(p3fes::EEContext&);
void fn_sub_245CD0_00245cd0(p3fes::EEContext&);
void fn_sub_245EA0_00245ea0(p3fes::EEContext&);
void fn_sub_248580_00248580(p3fes::EEContext&);
void fn_sub_248FC0_00248fc0(p3fes::EEContext&);
void fn_sub_2491F0_002491f0(p3fes::EEContext&);
void fn_sub_249420_00249420(p3fes::EEContext&);
void fn_sub_24A6E0_0024a6e0(p3fes::EEContext&);
void fn_sub_24A750_0024a750(p3fes::EEContext&);
void fn_sub_24A7A0_0024a7a0(p3fes::EEContext&);
void fn_sub_2510D0_002510d0(p3fes::EEContext&);
void fn_sub_2518B0_002518b0(p3fes::EEContext&);
void fn_sub_251A20_00251a20(p3fes::EEContext&);
void fn_sub_251A80_00251a80(p3fes::EEContext&);
void fn_sub_251ED0_00251ed0(p3fes::EEContext&);
void fn_sub_251F40_00251f40(p3fes::EEContext&);
void fn_sub_266F60_00266f60(p3fes::EEContext&);
void fn_sub_267070_00267070(p3fes::EEContext&);
void fn_sub_267210_00267210(p3fes::EEContext&);
void fn_sub_27B6C0_0027b6c0(p3fes::EEContext&);
void fn_sub_27B9F0_0027b9f0(p3fes::EEContext&);
void fn_sub_27BA90_0027ba90(p3fes::EEContext&);
void fn_sub_27BAE0_0027bae0(p3fes::EEContext&);
void fn_sub_301CA0_00301ca0(p3fes::EEContext&);
void fn_sub_30C0C0_0030c0c0(p3fes::EEContext&);
void fn_sub_3A52C0_003a52c0(p3fes::EEContext&);
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7990_003c7990(p3fes::EEContext&);
void fn_sub_3C7BC0_003c7bc0(p3fes::EEContext&);
void fn_sub_3C7C20_003c7c20(p3fes::EEContext&);
void fn_sub_3C94E0_003c94e0(p3fes::EEContext&);
void fn_sub_3C9790_003c9790(p3fes::EEContext&);
void fn_sub_3C9B00_003c9b00(p3fes::EEContext&);
void fn_sub_3C9CD0_003c9cd0(p3fes::EEContext&);
void fn_sub_3C9D00_003c9d00(p3fes::EEContext&);
void fn_sub_3C9E00_003c9e00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b6;  // this slice's additions (battle6.h)

// 0x00242C20 sub_242C20 -- 28 bytes; leaf frame (no stack)
// [biSlotSetWords] Sets a battle info slot's two words (a0 a slot of the bi work, 3,920 bytes each: b4::bi;
// sub_1FE650): flag 0x20, +3908 = a1, +3904 = a2.
// Arguments: a0 the bi slot, a1 / a2 the words.
void sub_242C20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00242c20
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, a0, bi::kFlags);
    v1 = v1 | 0x20;
    sw(v1, a0, bi::kFlags);
    sw(a1, a0, 3908);
    sw(a2, a0, 3904);
}

// 0x00243150 sub_243150 -- 4048 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcDraw] Draws the battle panel command work (bpc_main.c, *$gp 0x7CE320; K_Assert line 151; bpRoot's draw task).
// Takes the texture sets 2 / 1 / 5 / 3; while shown (flag 1) or sliding (0x20): the entries' draw lists (sub_245EA0)
// unless flag 0x100, the 2D render states (RwRenderStateSet 9 / 20 / 8 / 6), then every listed entry (mode 2: one of
// the entry flags 0x400 / 0x20 / 0x80; modes 0 / 1: its uid in the uid list, or sliding) that is not hidden (0x40):
// the cursor highlight (texture 44, flag 1), the frame (2), the name plate (texture 55 of set 2 for the enemy panel,
// 4 otherwise), the analysis plate (8, mode 2), the gauge frame (3), the low-HP mark (69, flag 2), the enemy panel's
// two analysis bars (61 / 57) or the party panel's HP / SP bars (1, and texture 4 of set 5); each quad drawn as two
// triangles through the Im2D slot 0x96009C with the render state 0x7381B (additive 0x71821 for the highlight /
// plates). With one listed unit (flag 2, not 0x80): the name line backdrop (texture 0), the plates 67 and the name
// text (frFontDraw of +27840), the plates 66; with persona marks shown (flag 4): the three marks' plates (59..64 by
// their states +27844..+27852) and their state icons (texture 17 / 18 of set 3, or 65).
void sub_243150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00243150
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
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
    lw(v0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v0 == 0) {
        // 0x00243188
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x243194u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024319c
    charge(ctx, 22);
    lw(s2, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    a0 = 2;
    jal(ctx, 0x2431A4u, gen::fn_sub_21C3F0_0021c3f0);
    s7 = v0;
    a0 = 1;
    jal(ctx, 0x2431B4u, gen::fn_sub_21C3F0_0021c3f0);
    s5 = v0;
    a0 = 5;
    jal(ctx, 0x2431C4u, gen::fn_sub_21C3F0_0021c3f0);
    sw(v0, sp, 0xAC);
    a0 = 3;
    jal(ctx, 0x2431D4u, gen::fn_sub_21C3F0_0021c3f0);
    fp = v0;
    lw(v1, s2, bpc::kFlags);
    a0 = nor(v1, 0);
    v1 = a0 & 0x1;
    if (v1 != 0) {
        // 0x002431f4
        charge(ctx, 3);
        v1 = a0 & 0x20;
        if (v1 == 0) {
            goto L_00243200;
        }
        // 0x002440ec (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xB0);
        return;
    }
L_00243200:
    charge(ctx, 3);
    v0 = a0 & 0x100;
    if (v0 != 0) {
        // 0x0024320c
        charge(ctx, 2);
        jal(ctx, 0x24320Cu, gen::fn_sub_245EA0_00245ea0);
    }
    // 0x00243214
    charge(ctx, 25);
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x243228u, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x24323Cu, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x243250u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x243264u, v0.u());
    s4 = 0;
    for (;;) {
        // 0x00243a1c
        charge(ctx, 4);
        lw(v1, s2, 12);
        v1 = slt(s4, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00243278
        charge(ctx, 11);
        v1 = sll(s4, 2);
        v1 = addu(v1, s4);
        v1 = sll(v1, 3);
        v1 = addu(v1, s4);
        v1 = sll(v1, 6);
        v1 = addu(s2, v1);
        s0 = addiu(v1, 64);
        lw(a0, s2, 4);
        v1 = 2;
        if (a0 == v1) {
            // 0x0024331c
            charge(ctx, 5);
            lw(v1, s0, 0);
            a0 = nor(v1, 0);
            v1 = a0 & 0x400;
            if (v1 == 0) {
            L_00243348:
                charge(ctx, 4);
                lw(a0, s0, 0);
                v1 = a0 & 0x40;
                if (v1 == 0) {
                    // 0x00243358
                    charge(ctx, 3);
                    v0 = a0 & 0x1;
                    if (v0 != 0) {
                        // 0x00243364
                        charge(ctx, 39);
                        a0 = s5;
                        a1 = 44;
                        jal(ctx, 0x24336Cu, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x243378u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s1, 0);
                        jalr(ctx, 0x24338Cu, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x1801;
                        jal(ctx, 0x2433A0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 72;
                        jal(ctx, 0x2433B0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        s3 = 0x960000;
                        s3 = addiu(s3, 156);  // &0x96009C
                        a0 = addiu(s0, 1296);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x2433D8u, v0.u());
                        a0 = addiu(s0, 1296);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x2433F8u, v0.u());
                    }
                    // 0x00243400
                    charge(ctx, 44);
                    a0 = s5;
                    a1 = 2;
                    jal(ctx, 0x243408u, gen::fn_sub_21CCA0_0021cca0);
                    s3 = v0;
                    a0 = s3;
                    jal(ctx, 0x243418u, gen::fn_sub_21CCE0_0021cce0);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x24342Cu, v0.u());
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x243440u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x243450u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    s6 = 0x960000;
                    s6 = addiu(s6, 156);  // &0x96009C
                    a0 = addiu(s0, 528);
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s6, 0);  // 0x96009C
                    jalr(ctx, 0x243478u, v0.u());
                    a0 = addiu(s0, 528);
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s6, 0);  // 0x96009C
                    jalr(ctx, 0x243498u, v0.u());
                    lw(v1, s2, 4);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x002434e8
                        charge(ctx, 5);
                        a0 = s7;
                        a1 = 55;
                        jal(ctx, 0x2434F0u, gen::fn_sub_21CCA0_0021cca0);
                        s3 = v0;
                    } else {
                        // 0x002434b0
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x002434bc
                            charge(ctx, 2);
                            if (v1 == 0) {
                                goto L_002434cc;
                            }
                            // 0x002434c4
                            charge(ctx, 2);
                            goto L_002434fc;
                        }
                    L_002434cc:
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 4;
                        jal(ctx, 0x2434D4u, gen::fn_sub_21CCA0_0021cca0);
                        s3 = v0;
                    }
                L_002434fc:
                    charge(ctx, 39);
                    a0 = s3;
                    jal(ctx, 0x243500u, gen::fn_sub_21CCE0_0021cce0);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x243514u, v0.u());
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x1801;
                    jal(ctx, 0x243528u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 72;
                    jal(ctx, 0x243538u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    s3 = 0x960000;
                    s3 = addiu(s3, 156);  // &0x96009C
                    a0 = addiu(s0, 272);
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s3, 0);  // 0x96009C
                    jalr(ctx, 0x243560u, v0.u());
                    a0 = addiu(s0, 272);
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s3, 0);  // 0x96009C
                    jalr(ctx, 0x243580u, v0.u());
                    lw(v1, s2, 4);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x002435a0
                        charge(ctx, 37);
                        a0 = s5;
                        a1 = 8;
                        jal(ctx, 0x2435A8u, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x2435B4u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s1, 0);
                        jalr(ctx, 0x2435C8u, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x1801;
                        jal(ctx, 0x2435DCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 72;
                        jal(ctx, 0x2435ECu, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = addiu(s0, 2336);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);
                        jalr(ctx, 0x24360Cu, v0.u());
                        a0 = addiu(s0, 2336);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);
                        jalr(ctx, 0x24362Cu, v0.u());
                    } else {
                        // 0x00243598
                        charge(ctx, 2);
                    }
                    // 0x00243634
                    charge(ctx, 43);
                    a0 = s5;
                    a1 = 3;
                    jal(ctx, 0x24363Cu, gen::fn_sub_21CCA0_0021cca0);
                    a0 = v0;
                    jal(ctx, 0x243648u, gen::fn_sub_21CCE0_0021cce0);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x24365Cu, v0.u());
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x243670u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x243680u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    s3 = 0x960000;
                    s3 = addiu(s3, 156);  // &0x96009C
                    a0 = addiu(s0, 16);
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s3, 0);  // 0x96009C
                    jalr(ctx, 0x2436A8u, v0.u());
                    a0 = addiu(s0, 16);
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s3, 0);  // 0x96009C
                    jalr(ctx, 0x2436C8u, v0.u());
                    lw(v1, s0, 0);
                    v1 = v1 & 0x2;
                    if (v1 != 0) {
                        // 0x002436e0
                        charge(ctx, 37);
                        a0 = s5;
                        a1 = 69;
                        jal(ctx, 0x2436E8u, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x2436F4u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s1, 0);
                        jalr(ctx, 0x243708u, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x24371Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x24372Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = addiu(s0, 1552);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);
                        jalr(ctx, 0x24374Cu, v0.u());
                        a0 = addiu(s0, 1552);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);
                        jalr(ctx, 0x24376Cu, v0.u());
                    }
                    // 0x00243774
                    charge(ctx, 4);
                    lw(a0, s2, 4);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x002438e0
                        charge(ctx, 78);
                        a0 = s7;
                        a1 = 61;
                        jal(ctx, 0x2438E8u, gen::fn_sub_21CCA0_0021cca0);
                        s6 = 0x960000;
                        s6 = addiu(s6, 144);  // &pfn_RwRenderStateSet
                        a0 = v0;
                        jal(ctx, 0x2438FCu, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s6, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x243910u, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x243924u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x243934u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        s3 = 0x960000;
                        s3 = addiu(s3, 156);  // &0x96009C
                        a0 = addiu(s0, 2080);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x24395Cu, v0.u());
                        a0 = addiu(s0, 2080);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x24397Cu, v0.u());
                        a0 = s7;
                        a1 = 57;
                        jal(ctx, 0x24398Cu, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x243998u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s6, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x2439ACu, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x2439C0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x2439D0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = addiu(s0, 1824);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x2439F0u, v0.u());
                        a0 = addiu(s0, 1824);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x243A10u, v0.u());
                    } else {
                        // 0x00243784
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 != v1) {
                            // 0x00243790
                            charge(ctx, 2);
                            if (a0 == 0) {
                                goto L_002437a0;
                            }
                            // 0x00243798
                            charge(ctx, 2);
                            goto L_00243a18;
                        }
                    L_002437a0:
                        charge(ctx, 80);
                        a0 = s5;
                        a1 = 1;
                        jal(ctx, 0x2437A8u, gen::fn_sub_21CCA0_0021cca0);
                        s6 = 0x960000;
                        s6 = addiu(s6, 144);  // &pfn_RwRenderStateSet
                        a0 = v0;
                        jal(ctx, 0x2437BCu, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s6, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x2437D0u, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x2437E4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x2437F4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        s3 = 0x960000;
                        s3 = addiu(s3, 156);  // &0x96009C
                        a0 = addiu(s0, 1040);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x24381Cu, v0.u());
                        a0 = addiu(s0, 1040);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x24383Cu, v0.u());
                        lw(a0, sp, 0xAC);
                        a1 = 4;
                        jal(ctx, 0x24384Cu, gen::fn_sub_21CCA0_0021cca0);
                        a0 = v0;
                        jal(ctx, 0x243858u, gen::fn_sub_21CCE0_0021cce0);
                        a0 = 1;
                        a1 = v0;
                        lw(v0, s6, 0);  // pfn_RwRenderStateSet
                        jalr(ctx, 0x24386Cu, v0.u());
                        a0 = 3;
                        v0 = 0x70000;
                        a1 = v0 | 0x17FB;
                        jal(ctx, 0x243880u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = 2;
                        a1 = 68;
                        jal(ctx, 0x243890u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        a0 = addiu(s0, 784);
                        a1 = 4;
                        a2 = 0;
                        a3 = 1;
                        t0 = 2;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x2438B0u, v0.u());
                        a0 = addiu(s0, 784);
                        a1 = 4;
                        a2 = 0;
                        a3 = 2;
                        t0 = 3;
                        lw(v0, s3, 0);  // 0x96009C
                        jalr(ctx, 0x2438D0u, v0.u());
                    }
                }
            } else {
                // 0x00243330
                charge(ctx, 3);
                v1 = a0 & 0x20;
                if (v1 == 0) {
                    goto L_00243348;
                }
                // 0x0024333c
                charge(ctx, 3);
                v1 = a0 & 0x80;
                if (v1 == 0) {
                    goto L_00243348;
                }
            }
        } else {
            // 0x002432a4
            charge(ctx, 3);
            v1 = 1;
            if (a0 != v1) {
                // 0x002432b0
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_002432c0;
                }
                // 0x002432b8
                charge(ctx, 2);
                goto L_00243348;
            }
        L_002432c0:
            charge(ctx, 4);
            a2 = 0;
            lw(a1, s2, 8);
            for (;;) {
                // 0x002432ec
                charge(ctx, 3);
                v1 = slt(a2, a1);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x002432d0
                    charge(ctx, 6);
                    v1 = sll(a2, 2);
                    v1 = addu(s2, v1);
                    lw(a0, v1, 16);
                    lw(v1, s0, 8);
                    if (a0 != v1) {
                        // 0x002432e8
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x002432f8
            charge(ctx, 5);
            lw(v1, s0, 0);
            v1 = nor(v1, 0);
            v1 = v1 & 0x20;
            if (v1 == 0) {
                goto L_00243348;
            }
            // 0x0024330c
            charge(ctx, 2);
            if (a2 != a1) {
                goto L_00243348;
            }
            // 0x00243314
            charge(ctx, 2);
        }
    L_00243a18:
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x00243a2c
    charge(ctx, 4);
    lw(a0, s2, 0);
    v1 = a0 & 0x2;
    if (v1 != 0) {
        // 0x00243a3c
        charge(ctx, 4);
        v1 = nor(a0, 0);
        v1 = v1 & 0x80;
        if (v1 != 0) {
            // 0x00243a4c
            charge(ctx, 173);
            a0 = s5;
            a1 = 0;
            jal(ctx, 0x243A54u, gen::fn_sub_21CCA0_0021cca0);
            s4 = 0x960000;
            s4 = addiu(s4, 144);  // &pfn_RwRenderStateSet
            a0 = v0;
            jal(ctx, 0x243A68u, gen::fn_sub_21CCE0_0021cce0);
            a0 = 1;
            a1 = v0;
            lw(v0, s4, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x243A7Cu, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x243A90u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x243AA0u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s3 = 0x960000;
            s3 = addiu(s3, 156);  // &0x96009C
            a0 = addiu(s2, 27072);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243AC8u, v0.u());
            a0 = addiu(s2, 27072);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243AE8u, v0.u());
            a0 = s5;
            a1 = 67;
            jal(ctx, 0x243AF8u, gen::fn_sub_21CCA0_0021cca0);
            a0 = v0;
            jal(ctx, 0x243B04u, gen::fn_sub_21CCE0_0021cce0);
            a0 = 1;
            a1 = v0;
            lw(v0, s4, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x243B18u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x243B2Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x243B3Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = addiu(s2, 26304);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243B5Cu, v0.u());
            a0 = addiu(s2, 26304);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243B7Cu, v0.u());
            a0 = addiu(s2, 26560);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243B9Cu, v0.u());
            a0 = addiu(s2, 26560);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243BBCu, v0.u());
            a0 = addiu(s2, 26816);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243BDCu, v0.u());
            a0 = addiu(s2, 26816);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243BFCu, v0.u());
            lw(a0, s2, 27840);
            a1 = 1;
            a2 = 0;
            jal(ctx, 0x243C10u, gen::fn_frFontDraw_003b1360);
            a0 = s5;
            a1 = 66;
            jal(ctx, 0x243C20u, gen::fn_sub_21CCA0_0021cca0);
            s0 = v0;
            a0 = s0;
            jal(ctx, 0x243C30u, gen::fn_sub_21CCE0_0021cce0);
            a0 = 1;
            a1 = v0;
            lw(v0, s4, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x243C44u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x243C58u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x243C68u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = addiu(s2, 27328);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243C88u, v0.u());
            a0 = addiu(s2, 27328);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243CA8u, v0.u());
            a0 = addiu(s2, 27584);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243CC8u, v0.u());
            a0 = addiu(s2, 27584);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C
            jalr(ctx, 0x243CE8u, v0.u());
            lw(v1, s2, 0);
            v1 = v1 & 0x4;
            if (v1 != 0) {
                // 0x00243d00
                charge(ctx, 3);
                lw(v1, s2, 27844);
                if (v1 == 0) {
                    // 0x00243d48
                    charge(ctx, 5);
                    a0 = s5;
                    a1 = 60;
                    jal(ctx, 0x243D50u, gen::fn_sub_21CCA0_0021cca0);
                    s0 = v0;
                } else {
                    // 0x00243d0c
                    charge(ctx, 3);
                    v0 = 2;
                    bool take_243d2c = true;  // the shared block runs when v1 matches the first test or 1
                    if (v1 != v0) {
                        // 0x00243d18
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x00243d24
                            charge(ctx, 2);
                            take_243d2c = false;
                        }
                    }
                    if (take_243d2c) {
                        // 0x00243d2c
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 59;
                        jal(ctx, 0x243D34u, gen::fn_sub_21CCA0_0021cca0);
                        s0 = v0;
                    }
                }
            // 0x00243d5c
                charge(ctx, 38);
                a0 = s0;
                jal(ctx, 0x243D60u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s1, 0);
                jalr(ctx, 0x243D74u, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x243D88u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x243D98u, gen::fn_RpSkyRenderStateSet_004d7f60);
                s3 = 0x960000;
                s3 = addiu(s3, 156);  // &0x96009C
                a0 = addiu(s2, 27856);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s3, 0);  // 0x96009C
                jalr(ctx, 0x243DC0u, v0.u());
                a0 = addiu(s2, 27856);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s3, 0);  // 0x96009C
                jalr(ctx, 0x243DE0u, v0.u());
                lw(v1, s2, 27848);
                if (v1 == 0) {
                    // 0x00243e30
                    charge(ctx, 5);
                    a0 = s5;
                    a1 = 62;
                    jal(ctx, 0x243E38u, gen::fn_sub_21CCA0_0021cca0);
                    s0 = v0;
                } else {
                    // 0x00243df4
                    charge(ctx, 3);
                    v0 = 2;
                    bool take_243e14 = true;  // the shared block runs when v1 matches the first test or 1
                    if (v1 != v0) {
                        // 0x00243e00
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x00243e0c
                            charge(ctx, 2);
                            take_243e14 = false;
                        }
                    }
                    if (take_243e14) {
                        // 0x00243e14
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 61;
                        jal(ctx, 0x243E1Cu, gen::fn_sub_21CCA0_0021cca0);
                        s0 = v0;
                    }
                }
            // 0x00243e44
                charge(ctx, 38);
                a0 = s0;
                jal(ctx, 0x243E48u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s1, 0);
                jalr(ctx, 0x243E5Cu, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x243E70u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x243E80u, gen::fn_RpSkyRenderStateSet_004d7f60);
                s3 = 0x960000;
                s3 = addiu(s3, 156);  // &0x96009C
                a0 = addiu(s2, 28112);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s3, 0);  // 0x96009C
                jalr(ctx, 0x243EA8u, v0.u());
                a0 = addiu(s2, 28112);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s3, 0);  // 0x96009C
                jalr(ctx, 0x243EC8u, v0.u());
                lw(v1, s2, 27852);
                if (v1 == 0) {
                    // 0x00243f18
                    charge(ctx, 5);
                    a0 = s5;
                    a1 = 64;
                    jal(ctx, 0x243F20u, gen::fn_sub_21CCA0_0021cca0);
                    s0 = v0;
                } else {
                    // 0x00243edc
                    charge(ctx, 3);
                    v0 = 2;
                    bool take_243efc = true;  // the shared block runs when v1 matches the first test or 1
                    if (v1 != v0) {
                        // 0x00243ee8
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x00243ef4
                            charge(ctx, 2);
                            take_243efc = false;
                        }
                    }
                    if (take_243efc) {
                        // 0x00243efc
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 63;
                        jal(ctx, 0x243F04u, gen::fn_sub_21CCA0_0021cca0);
                        s0 = v0;
                    }
                }
            // 0x00243f2c
                charge(ctx, 38);
                a0 = s0;
                jal(ctx, 0x243F30u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s1, 0);
                jalr(ctx, 0x243F44u, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x243F58u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x243F68u, gen::fn_RpSkyRenderStateSet_004d7f60);
                s3 = 0x960000;
                s3 = addiu(s3, 156);  // &0x96009C
                a0 = addiu(s2, 28368);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s3, 0);  // 0x96009C
                jalr(ctx, 0x243F90u, v0.u());
                a0 = addiu(s2, 28368);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s3, 0);  // 0x96009C
                jalr(ctx, 0x243FB0u, v0.u());
                s3 = 0;
                for (;;) {
                    // 0x002440e0
                    charge(ctx, 3);
                    v1 = slti(s3, 3);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00243fc4
                    charge(ctx, 5);
                    v0 = sll(s3, 2);
                    v0 = addu(s2, v0);
                    lw(v1, v0, 27844);
                    if (v1 == 0) {
                        // 0x00244030
                        charge(ctx, 5);
                        a0 = s5;
                        a1 = 65;
                        jal(ctx, 0x244038u, gen::fn_sub_21CCA0_0021cca0);
                        s0 = v0;
                    } else {
                        // 0x00243fd8
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x00244014
                            charge(ctx, 7);
                            a0 = fp;
                            a1 = 18;
                            jal(ctx, 0x24401Cu, gen::fn_sub_21CCA0_0021cca0);
                            s0 = v0;
                        } else {
                            // 0x00243fe4
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x00243ff8
                                charge(ctx, 7);
                                a0 = fp;
                                a1 = 17;
                                jal(ctx, 0x244000u, gen::fn_sub_21CCA0_0021cca0);
                                s0 = v0;
                            } else {
                                // 0x00243ff0
                                charge(ctx, 2);
                            }
                        }
                    }
                    // 0x00244044
                    charge(ctx, 39);
                    a0 = s0;
                    jal(ctx, 0x244048u, gen::fn_sub_21CCE0_0021cce0);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x24405Cu, v0.u());
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x244070u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x244080u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    v0 = sll(s3, 8);
                    v0 = addu(s2, v0);
                    s4 = addiu(v0, 28624);
                    s6 = 0x960000;
                    s6 = addiu(s6, 156);  // &0x96009C
                    a0 = s4;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s6, 0);  // 0x96009C
                    jalr(ctx, 0x2440B4u, v0.u());
                    a0 = s4;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s6, 0);  // 0x96009C
                    jalr(ctx, 0x2440D4u, v0.u());
                    s3 = addiu(s3, 1);
                }
            }
        }
    }
    // 0x002440ec (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}

// 0x00244E80 sub_244E80 -- 1352 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcSetPersonaMarks] Sets the three persona marks of the battle panel command work (K_Assert line 151) from the
// cursor unit's DatUnit (sub_1FF430 of uid +16; K_Assert 1008 / 1009: open with one listed unit): for each pair of
// status bits -- 5 / 10, 64 / 128, 528 / 288 (sub_301CA0) -- the mark state is 1 (the first; K_Assert when both), 2
// (the second) or 0, stored at +27844 / +27848 / +27852; then each mark's plate (textures 59 / 61 / 63, or 60 / 62 /
// 64 when off) into +27856 / +28112 / +28368 and its icon (17 / 18 of set 3, or 65) into +28624 / +28880 / +29136
// (sub_21D3B0).
void sub_244E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00244e80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v0 == 0) {
        // 0x00244ea4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x244EB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00244eb8
    charge(ctx, 17);
    lw(s1, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    a0 = 1;
    jal(ctx, 0x244EC0u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    a0 = 3;
    jal(ctx, 0x244ED0u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    lw(a0, s1, bpc::kUids);
    jal(ctx, 0x244EE0u, gen::fn_sub_1FF430_001ff430);
    s0 = v0;
    lw(v0, s1, bpc::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00244efc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 1008;
        jal(ctx, 0x244F08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00244f10
    charge(ctx, 4);
    lw(v1, s1, bpc::kUidCount);
    v0 = 1;
    if (v1 != v0) {
        // 0x00244f20
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 1009;
        jal(ctx, 0x244F2Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00244f34
    charge(ctx, 6);
    lw(a0, s0, unit::kDat);
    a1 = 5;
    jal(ctx, 0x244F3Cu, gen::fn_sub_301CA0_00301ca0);
    if (v0 == 0) {
        // 0x00244f88
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 10;
        jal(ctx, 0x244F90u, gen::fn_sub_301CA0_00301ca0);
        if (v0 == 0) {
            // 0x00244fb0
            charge(ctx, 1);
            sw(zero, s1, bpc6::kMarkStates);
        } else {
            // 0x00244fa0
            charge(ctx, 4);
            v0 = 2;
            sw(v0, s1, bpc6::kMarkStates);
        }
    } else {
        // 0x00244f4c
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 10;
        jal(ctx, 0x244F54u, gen::fn_sub_301CA0_00301ca0);
        if (v0 != 0) {
            // 0x00244f64
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -6016);  // "bpc_main.c"
            a1 = 1014;
            jal(ctx, 0x244F70u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00244f78
        charge(ctx, 4);
        v0 = 1;
        sw(v0, s1, bpc6::kMarkStates);
    }
    // 0x00244fb4
    charge(ctx, 6);
    lw(a0, s0, unit::kDat);
    a1 = 64;
    jal(ctx, 0x244FBCu, gen::fn_sub_301CA0_00301ca0);
    if (v0 == 0) {
        // 0x00245008
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 128;
        jal(ctx, 0x245010u, gen::fn_sub_301CA0_00301ca0);
        if (v0 == 0) {
            // 0x00245030
            charge(ctx, 1);
            sw(zero, s1, bpc6::kMarkStates + 4);
        } else {
            // 0x00245020
            charge(ctx, 4);
            v0 = 2;
            sw(v0, s1, bpc6::kMarkStates + 4);
        }
    } else {
        // 0x00244fcc
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 128;
        jal(ctx, 0x244FD4u, gen::fn_sub_301CA0_00301ca0);
        if (v0 != 0) {
            // 0x00244fe4
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -6016);  // "bpc_main.c"
            a1 = 1029;
            jal(ctx, 0x244FF0u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00244ff8
        charge(ctx, 4);
        v0 = 1;
        sw(v0, s1, bpc6::kMarkStates + 4);
    }
    // 0x00245034
    charge(ctx, 6);
    lw(a0, s0, unit::kDat);
    a1 = 528;
    jal(ctx, 0x24503Cu, gen::fn_sub_301CA0_00301ca0);
    if (v0 == 0) {
        // 0x00245088
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 288;
        jal(ctx, 0x245090u, gen::fn_sub_301CA0_00301ca0);
        if (v0 == 0) {
            // 0x002450b0
            charge(ctx, 1);
            sw(zero, s1, bpc6::kMarkStates + 8);
        } else {
            // 0x002450a0
            charge(ctx, 4);
            v1 = 2;
            sw(v1, s1, bpc6::kMarkStates + 8);
        }
    } else {
        // 0x0024504c
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 288;
        jal(ctx, 0x245054u, gen::fn_sub_301CA0_00301ca0);
        if (v0 != 0) {
            // 0x00245064
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -6016);  // "bpc_main.c"
            a1 = 1044;
            jal(ctx, 0x245070u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00245078
        charge(ctx, 4);
        v1 = 1;
        sw(v1, s1, bpc6::kMarkStates + 8);
    }
    // 0x002450b4
    charge(ctx, 3);
    lw(a0, s1, bpc6::kMarkStates);
    if (a0 == 0) {
        // 0x00245170
        charge(ctx, 16);
        a0 = s3;
        a1 = 60;
        jal(ctx, 0x245178u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, 27856);
        a1 = v0;
        jal(ctx, 0x245188u, gen::fn_sub_21D3B0_0021d3b0);
        a0 = s3;
        a1 = 65;
        jal(ctx, 0x245198u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, 28624);
        a1 = v0;
        jal(ctx, 0x2451A8u, gen::fn_sub_21D3B0_0021d3b0);
    } else {
        // 0x002450c0
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x00245128
            charge(ctx, 18);
            a0 = s3;
            a1 = 59;
            jal(ctx, 0x245130u, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 27856);
            a1 = v0;
            jal(ctx, 0x245140u, gen::fn_sub_21D3B0_0021d3b0);
            a0 = s2;
            a1 = 18;
            jal(ctx, 0x245150u, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 28624);
            a1 = v0;
            jal(ctx, 0x245160u, gen::fn_sub_21D3B0_0021d3b0);
        } else {
            // 0x002450cc
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x002450e0
                charge(ctx, 18);
                a0 = s3;
                a1 = 59;
                jal(ctx, 0x2450E8u, gen::fn_sub_21CCA0_0021cca0);
                a0 = addiu(s1, 27856);
                a1 = v0;
                jal(ctx, 0x2450F8u, gen::fn_sub_21D3B0_0021d3b0);
                a0 = s2;
                a1 = 17;
                jal(ctx, 0x245108u, gen::fn_sub_21CCA0_0021cca0);
                a0 = addiu(s1, 28624);
                a1 = v0;
                jal(ctx, 0x245118u, gen::fn_sub_21D3B0_0021d3b0);
            } else {
                // 0x002450d8
                charge(ctx, 2);
            }
        }
    }
    // 0x002451b0
    charge(ctx, 3);
    lw(a0, s1, bpc6::kMarkStates + 4);
    if (a0 == 0) {
        // 0x0024526c
        charge(ctx, 16);
        a0 = s3;
        a1 = 62;
        jal(ctx, 0x245274u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, 28112);
        a1 = v0;
        jal(ctx, 0x245284u, gen::fn_sub_21D3B0_0021d3b0);
        a0 = s3;
        a1 = 65;
        jal(ctx, 0x245294u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, 28880);
        a1 = v0;
        jal(ctx, 0x2452A4u, gen::fn_sub_21D3B0_0021d3b0);
    } else {
        // 0x002451bc
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x00245224
            charge(ctx, 18);
            a0 = s3;
            a1 = 61;
            jal(ctx, 0x24522Cu, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 28112);
            a1 = v0;
            jal(ctx, 0x24523Cu, gen::fn_sub_21D3B0_0021d3b0);
            a0 = s2;
            a1 = 18;
            jal(ctx, 0x24524Cu, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 28880);
            a1 = v0;
            jal(ctx, 0x24525Cu, gen::fn_sub_21D3B0_0021d3b0);
        } else {
            // 0x002451c8
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x002451dc
                charge(ctx, 18);
                a0 = s3;
                a1 = 61;
                jal(ctx, 0x2451E4u, gen::fn_sub_21CCA0_0021cca0);
                a0 = addiu(s1, 28112);
                a1 = v0;
                jal(ctx, 0x2451F4u, gen::fn_sub_21D3B0_0021d3b0);
                a0 = s2;
                a1 = 17;
                jal(ctx, 0x245204u, gen::fn_sub_21CCA0_0021cca0);
                a0 = addiu(s1, 28880);
                a1 = v0;
                jal(ctx, 0x245214u, gen::fn_sub_21D3B0_0021d3b0);
            } else {
                // 0x002451d4
                charge(ctx, 2);
            }
        }
    }
    // 0x002452ac
    charge(ctx, 3);
    lw(a0, s1, bpc6::kMarkStates + 8);
    if (a0 == 0) {
        // 0x00245368
        charge(ctx, 16);
        a0 = s3;
        a1 = 64;
        jal(ctx, 0x245370u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, 28368);
        a1 = v0;
        jal(ctx, 0x245380u, gen::fn_sub_21D3B0_0021d3b0);
        a0 = s3;
        a1 = 65;
        jal(ctx, 0x245390u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, 29136);
        a1 = v0;
        jal(ctx, 0x2453A0u, gen::fn_sub_21D3B0_0021d3b0);
    } else {
        // 0x002452b8
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x00245320
            charge(ctx, 18);
            a0 = s3;
            a1 = 63;
            jal(ctx, 0x245328u, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 28368);
            a1 = v0;
            jal(ctx, 0x245338u, gen::fn_sub_21D3B0_0021d3b0);
            a0 = s2;
            a1 = 18;
            jal(ctx, 0x245348u, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 29136);
            a1 = v0;
            jal(ctx, 0x245358u, gen::fn_sub_21D3B0_0021d3b0);
        } else {
            // 0x002452c4
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x002452d8
                charge(ctx, 18);
                a0 = s3;
                a1 = 63;
                jal(ctx, 0x2452E0u, gen::fn_sub_21CCA0_0021cca0);
                a0 = addiu(s1, 28368);
                a1 = v0;
                jal(ctx, 0x2452F0u, gen::fn_sub_21D3B0_0021d3b0);
                a0 = s2;
                a1 = 17;
                jal(ctx, 0x245300u, gen::fn_sub_21CCA0_0021cca0);
                a0 = addiu(s1, 29136);
                a1 = v0;
                jal(ctx, 0x245310u, gen::fn_sub_21D3B0_0021d3b0);
            } else {
                // 0x002452d0
                charge(ctx, 2);
            }
        }
    }
    // 0x002453a8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002459D0 sub_2459D0 -- 48 bytes; leaf frame (no stack)
// [bpcEntryPrepareAnalysed] Prepares a battle panel command entry (a0) of an analysed enemy for its slide-in: clears
// +1808 (the slide counter) and flags 0x10 / 0x20, sets 0x200.
// Arguments: a0 the entry.
void sub_2459D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002459d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sw(zero, a0, bpce::kSlide);
    lw(a1, a0, bpce::kFlags);
    v1 = si(-17);
    a1 = a1 & v1;
    sw(a1, a0, bpce::kFlags);
    v1 = si(-33);
    v1 = a1 & v1;
    sw(v1, a0, bpce::kFlags);
    v1 = v1 | 0x200;
    sw(v1, a0, bpce::kFlags);
}

// 0x00245CD0 sub_245CD0 -- 296 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpcSetEntryRelations] Sets the relation word of every listed battle panel command entry (K_Assert line 151): of
// the entries flagged 0x80, the cursor unit's own entry gets 0, an entry whose DatUnit has the cursor unit's id
// (DatUnit +2) gets 1, any other 2 (+2656 of the 2,624-byte entry). Takes the texture sets 2 / 1 first.
void sub_245CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00245cd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    if (v0 == 0) {
        // 0x00245cf4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x245D00u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245d08
    charge(ctx, 15);
    lw(s2, gp, kGpBpcWork);  // the battle panel command work (bpc_main.c) 0x7CE320
    a0 = 2;
    jal(ctx, 0x245D10u, gen::fn_sub_21C3F0_0021c3f0);
    a0 = 1;
    jal(ctx, 0x245D1Cu, gen::fn_sub_21C3F0_0021c3f0);
    lw(a0, s2, bpc::kUids);
    jal(ctx, 0x245D28u, gen::fn_sub_1FF430_001ff430);
    lw(v1, v0, unit::kDat);
    lhu(s1, v1, dat::kId);
    s3 = 0;
    for (;;) {
        // 0x00245dc8
        charge(ctx, 4);
        lw(v1, s2, bpc::kEntryCount);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00245d44
        charge(ctx, 12);
        v1 = sll(s3, 2);
        v1 = addu(v1, s3);
        v1 = sll(v1, 3);
        v1 = addu(v1, s3);
        v1 = sll(v1, 6);
        v1 = addu(s2, v1);
        s0 = addiu(v1, 64);
        lw(v1, v1, 64);
        v1 = nor(v1, 0);
        v1 = v1 & 0x80;
        if (v1 == 0) {
            // 0x00245d74
            charge(ctx, 7);
            lw(a0, s0, 8);
            jal(ctx, 0x245D78u, gen::fn_sub_1FF430_001ff430);
            lw(a0, v0, unit::kUid);
            lw(v1, s2, bpc::kUids);
            if (a0 != v1) {
                // 0x00245d9c
                charge(ctx, 4);
                lw(v1, v0, unit::kDat);
                lhu(v1, v1, dat::kId);
                if (v1 != s1) {
                    // 0x00245dbc
                    charge(ctx, 2);
                    v1 = 2;
                    sw(v1, s0, 2592);
                } else {
                    // 0x00245dac
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, s0, 2592);
                }
            } else {
                // 0x00245d90
                charge(ctx, 3);
                sw(zero, s0, 2592);
            }
        }
        // 0x00245dc4
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00245dd8
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00248580 sub_248580 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpmOpenText] Opens the battle panel message window (bpm_main.c, *$gp 0x7CE324; K_Assert line 61) with the text a0
// / a1: closes the open one first (sub_2491F0), builds the text task (sub_3A52C0(100, 100, -1, 2, 6, a0, a1)) and
// shows it (sub_248FC0).
// Arguments: a0 / a1 the text.
void sub_248580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00248580
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    if (v0 == 0) {
        // 0x002485a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x2485B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002485b8
    charge(ctx, 5);
    lw(v0, gp, kGpBpmWork);  // the battle panel message work (bpm_main.c) 0x7CE324
    lw(v0, v0, bpm::kFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x002485cc
        charge(ctx, 2);
        jal(ctx, 0x2485CCu, gen::fn_sub_2491F0_002491f0);
    }
    // 0x002485d4
    charge(ctx, 19);
    mtc1(zero, f12);
    a0 = 100;
    a1 = a0;
    a2 = si(-1);
    a3 = 2;
    t0 = 6;
    t1 = s1;
    t2 = s0;
    jal(ctx, 0x2485F4u, gen::fn_sub_3A52C0_003a52c0);
    a0 = v0;
    jal(ctx, 0x248600u, gen::fn_sub_248FC0_00248fc0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00249420 sub_249420 -- 468 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpeShowItemMessage] Shows the item-get message of the bpe work (bpe_main.c, *$gp 0x7CE328; K_Assert lines 55 /
// 140): the message files 0 / 1 (sub_21C550), the item record (sub_30C0C0) sets its seen flag (4800 + item) and flag
// 4865; the first time (flag 4865 clear) it shows the explanation page (sub_3C94E0, the name sub_1775A0(1),
// sub_3C9790(0), mode 0), later the short line with the two item names (sub_173220 of a1 / a2) and the count a0
// (message 0, mode 1); stores a0..a2 at +8 / +10 / +12 and sets flag 1.
// Arguments: a0 u16 count, a1 / a2 item ids.
void sub_249420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00249420
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(v0, gp, kGpBpWork328);  // the bpe work (bpe_main.c; registered by sub_249240) 0x7CE328
    if (v0 == 0) {
        // 0x00249460
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5984);  // "bpe_main.c"
        a1 = 55;
        jal(ctx, 0x24946Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00249474
    charge(ctx, 19);
    lw(s4, gp, kGpBpWork328);  // the bpe work (bpe_main.c; registered by sub_249240) 0x7CE328
    a0 = 0;
    jal(ctx, 0x24947Cu, gen::fn_sub_21C550_0021c550);
    s5 = v0;
    a0 = 1;
    jal(ctx, 0x24948Cu, gen::fn_sub_21C550_0021c550);
    s6 = v0;
    a0 = 4865;
    jal(ctx, 0x24949Cu, gen::fn_datGetFlag_0016f190);
    v0 = sltu(0, v0);
    s7 = v0 ^ 0x1;
    jal(ctx, 0x2494ACu, gen::fn_sub_30C0C0_0030c0c0);
    s3 = v0;
    if (s3 == 0) {
        // 0x002494c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5984);  // "bpe_main.c"
        a1 = 140;
        jal(ctx, 0x2494CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002494d4
    charge(ctx, 11);
    lhu(v0, s3, 0);
    a0 = addiu(v0, 4800);
    a1 = 1;
    jal(ctx, 0x2494E0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 4865;
    a1 = 1;
    jal(ctx, 0x2494F0u, gen::fn_datSetFlag_0016f1f0);
    if (s7 == 0) {
        // 0x00249540
        charge(ctx, 27);
        a0 = s6;
        jal(ctx, 0x249544u, gen::fn_sub_3C72D0_003c72d0);
        a0 = s1;
        jal(ctx, 0x249550u, gen::fn_sub_173220_00173220);
        a0 = 0;
        a1 = v0;
        jal(ctx, 0x249560u, gen::fn_sub_3C7BC0_003c7bc0);
        a0 = s0;
        jal(ctx, 0x24956Cu, gen::fn_sub_173220_00173220);
        a0 = 1;
        a1 = v0;
        jal(ctx, 0x24957Cu, gen::fn_sub_3C7BC0_003c7bc0);
        a1 = s2 & 0xFFFF;
        a0 = 2;
        a2 = 5;
        jal(ctx, 0x249590u, gen::fn_sub_3C7C20_003c7c20);
        a0 = 0;
        jal(ctx, 0x24959Cu, gen::fn_msgWinRequestMessage_003c7430);
        v1 = 1;
        sw(v1, s4, bpe::kState);
    } else {
        // 0x00249500
        charge(ctx, 16);
        a0 = s5;
        jal(ctx, 0x249504u, gen::fn_sub_3C94E0_003c94e0);
        a0 = 1;
        jal(ctx, 0x249510u, gen::fn_sub_1775A0_001775a0);
        a0 = 0;
        a1 = v0;
        jal(ctx, 0x249520u, gen::fn_sub_3C7BC0_003c7bc0);
        a0 = 0;
        jal(ctx, 0x24952Cu, gen::fn_sub_3C9790_003c9790);
        sw(zero, s4, bpe::kState);
    }
    // 0x002495ac (the shared epilogue, written out on this path)
    charge(ctx, 18);
    sh(s2, s4, bpe::kNumber);
    sh(s1, s4, bpe::kItemA);
    sh(s0, s4, bpe::kItemB);
    lw(v1, s4, bpe::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s4, bpe::kFlags);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0024A6E0 sub_24A6E0 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [basOpen] Opens the bas work (bas_main.c, *$gp 0x7CE32C; K_Assert line 29) for a0: sub_1FE580(a0), +4 = a0, flag 1.
// Arguments: a0.
void sub_24A6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024a6e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBasWork);  // the bas work (bas_main.c) 0x7CE32C
    if (v0 == 0) {
        // 0x0024a700
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5928);  // "bas_main.c"
        a1 = 29;
        jal(ctx, 0x24A70Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024a714
    charge(ctx, 14);
    lw(s0, gp, kGpBasWork);  // the bas work (bas_main.c) 0x7CE32C
    a0 = s1;
    jal(ctx, 0x24A71Cu, gen::fn_sub_1FE580_001fe580);
    sw(s1, s0, bas::kArg);
    lw(v1, s0, bas::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, bas::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024A750 sub_24A750 -- 68 bytes; frame 0x10: ra sp+0x0
// [basIsOpen] Nonzero while the bas work is open (flag 1; K_Assert line 29).
void sub_24A750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024a750
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBasWork);  // the bas work (bas_main.c) 0x7CE32C
    if (v0 == 0) {
        // 0x0024a764
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5928);  // "bas_main.c"
        a1 = 29;
        jal(ctx, 0x24A770u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024a778 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBasWork);  // the bas work (bas_main.c) 0x7CE32C
    lw(v0, v0, bas::kFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0024A7A0 sub_24A7A0 -- 76 bytes; frame 0x10: ra sp+0x0
// [basClose] Closes the bas work (clears flag 1; K_Assert line 29).
void sub_24A7A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024a7a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBasWork);  // the bas work (bas_main.c) 0x7CE32C
    if (v1 == 0) {
        // 0x0024a7b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5928);  // "bas_main.c"
        a1 = 29;
        jal(ctx, 0x24A7C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024a7c8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBasWork);  // the bas work (bas_main.c) 0x7CE32C
    lw(a0, a1, bas::kFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, a1, bas::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002510D0 sub_2510D0 -- 2012 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [bpTutUpdate] Per-frame update of the battle tutorial (bp_tut.c, *$gp 0x7CE344; K_Assert line 57; bpRoot's task)
// while open: phase 0 waits for the panel (sub_21C860) and the picture task (sub_1114B0), shows the tutorial's first
// page (messages 0 / 5 / 11 / 16 by the tutorial kind +8, choice lists 1 / 6 / 12 / 17), step 0, phase 1. Phase 1 is
// a step machine (+12): 0 / 1 the yes / no choices -- 'no' shows the next page (4 / 10 / 15 / 20) and goes to 2,
// 'yes' repeats (2 / 7 / 13 / 18, kind 1 ends after message 7 at step 3); 2 / 3 close the window and the picture
// (sub_111500), 3 also the window set -> 4 / 7; 4 when the picture task ended shows the explanation (sub_3C94E0) ->
// 5; 5 closes it, shows message 8 and starts a new picture task (sub_110F80) -> 6; 6 when it is ready starts it
// (sub_111530) -> 1; 7 when the picture task ended closes (sub_251A20) and clears flag 1.
void sub_2510D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002510d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpTut);  // the battle tutorial (bp_tut.c) 0x7CE344
    if (v1 == 0) {
        // 0x002510e8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5696);  // "bp_tut.c"
        a1 = 57;
        jal(ctx, 0x2510F4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002510fc
    charge(ctx, 6);
    lw(s0, gp, kGpBpTut);  // the battle tutorial (bp_tut.c) 0x7CE344
    lw(v1, s0, tut::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00251114
        charge(ctx, 4);
        lw(v1, s0, tut::kPhase);
        a0 = 1;
        if (v1 == a0) {
            // 0x00251298
            charge(ctx, 4);
            lw(v1, s0, tut::kStep);
            at = sltiu(v1, 8);
            if (at != 0) {
                // 0x002512a8
                charge(ctx, 7);
                a1 = 0x7B0000;
                a1 = addiu(a1, 30992);  // &0x7B7910
                v1 = sll(v1, 2);
                v1 = addu(v1, a1);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x2512C4u:  // table[0]: step 0, the first page's yes / no
                    // 0x002512c4
                    charge(ctx, 6);
                    jal(ctx, 0x2512C4u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x2512CCu, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x002512dc
                        charge(ctx, 5);
                        jal(ctx, 0x2512DCu, gen::fn_msgWinLastSelection_003c7610);
                        a0 = 1;
                        if (v0 == a0) {
                            // 0x0025142c
                            charge(ctx, 6);
                            jal(ctx, 0x25142Cu, gen::fn_msgWinClose_003c7650);
                            lw(a0, s0, tut::kKind);
                            v1 = 3;
                            if (a0 == v1) {
                                // 0x002514a8
                                charge(ctx, 3);
                                a0 = 20;
                                jal(ctx, 0x2514ACu, gen::fn_msgWinRequestMessage_003c7430);
                            } else {
                                // 0x00251444
                                charge(ctx, 3);
                                v1 = 2;
                                if (a0 == v1) {
                                    // 0x00251494
                                    charge(ctx, 5);
                                    a0 = 15;
                                    jal(ctx, 0x251498u, gen::fn_msgWinRequestMessage_003c7430);
                                } else {
                                    // 0x00251450
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (a0 == v1) {
                                        // 0x00251480
                                        charge(ctx, 5);
                                        a0 = 10;
                                        jal(ctx, 0x251484u, gen::fn_msgWinRequestMessage_003c7430);
                                    } else {
                                        // 0x0025145c
                                        charge(ctx, 2);
                                        if (a0 == 0) {
                                            // 0x0025146c
                                            charge(ctx, 5);
                                            a0 = 4;
                                            jal(ctx, 0x251470u, gen::fn_msgWinRequestMessage_003c7430);
                                        } else {
                                            // 0x00251464
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                            // 0x002514b4
                            charge(ctx, 4);
                            v1 = 2;
                            sw(v1, s0, tut::kStep);
                        } else {
                            // 0x002512f0
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x00251300
                                charge(ctx, 6);
                                jal(ctx, 0x251300u, gen::fn_msgWinClose_003c7650);
                                lw(a1, s0, tut::kKind);
                                v1 = 1;
                                if (a1 == v1) {
                                    // 0x00251410
                                    charge(ctx, 7);
                                    a0 = 7;
                                    jal(ctx, 0x251414u, gen::fn_msgWinRequestMessage_003c7430);
                                    v1 = 3;
                                    sw(v1, s0, tut::kStep);
                                } else {
                                    // 0x00251318
                                    charge(ctx, 3);
                                    v1 = 3;
                                    if (a1 != v1) {
                                        // 0x00251324
                                        charge(ctx, 3);
                                        v1 = 2;
                                        if (a1 == v1) {
                                            goto L_00251340;
                                        }
                                        // 0x00251330
                                        charge(ctx, 2);
                                        if (a1 == 0) {
                                            goto L_00251340;
                                        }
                                        // 0x00251338
                                        charge(ctx, 2);
                                        break;
                                    }
                                L_00251340:
                                    charge(ctx, 3);
                                    v0 = 3;
                                    if (a1 == v0) {
                                        // 0x0025138c
                                        charge(ctx, 3);
                                        a0 = 18;
                                        jal(ctx, 0x251390u, gen::fn_msgWinRequestMessage_003c7430);
                                    } else {
                                        // 0x0025134c
                                        charge(ctx, 3);
                                        a0 = 2;
                                        if (a1 == a0) {
                                            // 0x00251378
                                            charge(ctx, 5);
                                            a0 = 13;
                                            jal(ctx, 0x25137Cu, gen::fn_msgWinRequestMessage_003c7430);
                                        } else {
                                            // 0x00251358
                                            charge(ctx, 2);
                                            if (a1 == 0) {
                                                // 0x00251368
                                                charge(ctx, 4);
                                                jal(ctx, 0x251368u, gen::fn_msgWinRequestMessage_003c7430);
                                            } else {
                                                // 0x00251360
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                    // 0x00251398
                                    charge(ctx, 4);
                                    lw(v1, s0, tut::kKind);
                                    a0 = 3;
                                    if (v1 == a0) {
                                        // 0x002513e8
                                        charge(ctx, 3);
                                        a0 = 19;
                                        jal(ctx, 0x2513ECu, gen::fn_sub_3C74E0_003c74e0);
                                    } else {
                                        // 0x002513a8
                                        charge(ctx, 3);
                                        v0 = 2;
                                        if (v1 == v0) {
                                            // 0x002513d4
                                            charge(ctx, 5);
                                            a0 = 14;
                                            jal(ctx, 0x2513D8u, gen::fn_sub_3C74E0_003c74e0);
                                        } else {
                                            // 0x002513b4
                                            charge(ctx, 2);
                                            if (v1 == 0) {
                                                // 0x002513c4
                                                charge(ctx, 4);
                                                jal(ctx, 0x2513C4u, gen::fn_sub_3C74E0_003c74e0);
                                            } else {
                                                // 0x002513bc
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                    // 0x002513f4
                                    charge(ctx, 7);
                                    a0 = 0;
                                    jal(ctx, 0x2513F8u, gen::fn_msgWinSetType_003c7560);
                                    v1 = 1;
                                    sw(v1, s0, tut::kStep);
                                }
                            } else {
                                // 0x002512f8
                                charge(ctx, 2);
                            }
                        }
                    }
                    break;
                case 0x2514C4u:  // table[1]: step 1, the repeated page's yes / no
                    // 0x002514c4
                    charge(ctx, 6);
                    jal(ctx, 0x2514C4u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x2514CCu, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x002514dc
                        charge(ctx, 4);
                        jal(ctx, 0x2514DCu, gen::fn_msgWinLastSelection_003c7610);
                        if (v0 == 0) {
                            // 0x0025162c
                            charge(ctx, 7);
                            a0 = 1;
                            jal(ctx, 0x251630u, gen::fn_msgWinClose_003c7650);
                            lw(a0, s0, tut::kKind);
                            v1 = 3;
                            if (a0 == v1) {
                                // 0x002516ac
                                charge(ctx, 3);
                                a0 = 20;
                                jal(ctx, 0x2516B0u, gen::fn_msgWinRequestMessage_003c7430);
                            } else {
                                // 0x00251648
                                charge(ctx, 3);
                                v1 = 2;
                                if (a0 == v1) {
                                    // 0x00251698
                                    charge(ctx, 5);
                                    a0 = 15;
                                    jal(ctx, 0x25169Cu, gen::fn_msgWinRequestMessage_003c7430);
                                } else {
                                    // 0x00251654
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (a0 == v1) {
                                        // 0x00251684
                                        charge(ctx, 5);
                                        a0 = 10;
                                        jal(ctx, 0x251688u, gen::fn_msgWinRequestMessage_003c7430);
                                    } else {
                                        // 0x00251660
                                        charge(ctx, 2);
                                        if (a0 == 0) {
                                            // 0x00251670
                                            charge(ctx, 5);
                                            a0 = 4;
                                            jal(ctx, 0x251674u, gen::fn_msgWinRequestMessage_003c7430);
                                        } else {
                                            // 0x00251668
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                            // 0x002516b8
                            charge(ctx, 4);
                            v1 = 2;
                            sw(v1, s0, tut::kStep);
                        } else {
                            // 0x002514ec
                            charge(ctx, 3);
                            a0 = 1;
                            if (v0 == a0) {
                                // 0x00251500
                                charge(ctx, 6);
                                jal(ctx, 0x251500u, gen::fn_msgWinClose_003c7650);
                                lw(a1, s0, tut::kKind);
                                v1 = 1;
                                if (a1 == v1) {
                                    // 0x00251610
                                    charge(ctx, 7);
                                    a0 = 7;
                                    jal(ctx, 0x251614u, gen::fn_msgWinRequestMessage_003c7430);
                                    v1 = 3;
                                    sw(v1, s0, tut::kStep);
                                } else {
                                    // 0x00251518
                                    charge(ctx, 3);
                                    v1 = 3;
                                    if (a1 != v1) {
                                        // 0x00251524
                                        charge(ctx, 3);
                                        v1 = 2;
                                        if (a1 == v1) {
                                            goto L_00251540;
                                        }
                                        // 0x00251530
                                        charge(ctx, 2);
                                        if (a1 == 0) {
                                            goto L_00251540;
                                        }
                                        // 0x00251538
                                        charge(ctx, 2);
                                        break;
                                    }
                                L_00251540:
                                    charge(ctx, 3);
                                    v0 = 3;
                                    if (a1 == v0) {
                                        // 0x0025158c
                                        charge(ctx, 3);
                                        a0 = 18;
                                        jal(ctx, 0x251590u, gen::fn_msgWinRequestMessage_003c7430);
                                    } else {
                                        // 0x0025154c
                                        charge(ctx, 3);
                                        a0 = 2;
                                        if (a1 == a0) {
                                            // 0x00251578
                                            charge(ctx, 5);
                                            a0 = 13;
                                            jal(ctx, 0x25157Cu, gen::fn_msgWinRequestMessage_003c7430);
                                        } else {
                                            // 0x00251558
                                            charge(ctx, 2);
                                            if (a1 == 0) {
                                                // 0x00251568
                                                charge(ctx, 4);
                                                jal(ctx, 0x251568u, gen::fn_msgWinRequestMessage_003c7430);
                                            } else {
                                                // 0x00251560
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                    // 0x00251598
                                    charge(ctx, 4);
                                    lw(v1, s0, tut::kKind);
                                    a0 = 3;
                                    if (v1 == a0) {
                                        // 0x002515e8
                                        charge(ctx, 3);
                                        a0 = 19;
                                        jal(ctx, 0x2515ECu, gen::fn_sub_3C74E0_003c74e0);
                                    } else {
                                        // 0x002515a8
                                        charge(ctx, 3);
                                        v0 = 2;
                                        if (v1 == v0) {
                                            // 0x002515d4
                                            charge(ctx, 5);
                                            a0 = 14;
                                            jal(ctx, 0x2515D8u, gen::fn_sub_3C74E0_003c74e0);
                                        } else {
                                            // 0x002515b4
                                            charge(ctx, 2);
                                            if (v1 == 0) {
                                                // 0x002515c4
                                                charge(ctx, 4);
                                                jal(ctx, 0x2515C4u, gen::fn_sub_3C74E0_003c74e0);
                                            } else {
                                                // 0x002515bc
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                    // 0x002515f4
                                    charge(ctx, 7);
                                    a0 = 0;
                                    jal(ctx, 0x2515F8u, gen::fn_msgWinSetType_003c7560);
                                    v1 = 1;
                                    sw(v1, s0, tut::kStep);
                                }
                            } else {
                                // 0x002514f8
                                charge(ctx, 2);
                            }
                        }
                    }
                    break;
                case 0x2516C8u:  // table[2]: step 2, close the window and the picture -> 7
                    // 0x002516c8
                    charge(ctx, 6);
                    jal(ctx, 0x2516C8u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x2516D0u, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x002516e0
                        charge(ctx, 10);
                        a0 = 1;
                        jal(ctx, 0x2516E4u, gen::fn_msgWinClose_003c7650);
                        lw(a0, s0, tut::kPicture);
                        jal(ctx, 0x2516F0u, gen::fn_sub_111500_00111500);
                        v1 = 7;
                        sw(v1, s0, tut::kStep);
                    }
                    break;
                case 0x251708u:  // table[3]: step 3, close the window, the picture and the window set -> 4
                    // 0x00251708
                    charge(ctx, 6);
                    jal(ctx, 0x251708u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x251710u, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x00251720
                        charge(ctx, 12);
                        a0 = 1;
                        jal(ctx, 0x251724u, gen::fn_msgWinClose_003c7650);
                        lw(a0, s0, tut::kPicture);
                        jal(ctx, 0x251730u, gen::fn_sub_111500_00111500);
                        jal(ctx, 0x251738u, gen::fn_sub_3C77A0_003c77a0);
                        v1 = 4;
                        sw(v1, s0, tut::kStep);
                    }
                    break;
                case 0x251750u:  // table[4]: step 4, the picture task ended: the explanation page -> 5
                    // 0x00251750
                    charge(ctx, 5);
                    lw(a0, s0, tut::kPicture);
                    jal(ctx, 0x251754u, gen::fn_kwlnTaskExists_00195460);
                    if (v0 == 0) {
                        // 0x00251764
                        charge(ctx, 13);
                        a0 = 1;
                        jal(ctx, 0x251768u, gen::fn_sub_21C8B0_0021c8b0);
                        a0 = v0;
                        jal(ctx, 0x251774u, gen::fn_sub_3C94E0_003c94e0);
                        a0 = 0;
                        jal(ctx, 0x251780u, gen::fn_sub_3C9790_003c9790);
                        v1 = 5;
                        sw(v1, s0, tut::kStep);
                    }
                    break;
                case 0x251798u:  // table[5]: step 5, close it, message 8 and a new picture task -> 6
                    // 0x00251798
                    charge(ctx, 6);
                    jal(ctx, 0x251798u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x2517A0u, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x002517b0
                        charge(ctx, 35);
                        a0 = 1;
                        jal(ctx, 0x2517B4u, gen::fn_msgWinClose_003c7650);
                        jal(ctx, 0x2517BCu, gen::fn_sub_3C77A0_003c77a0);
                        a0 = 0;
                        jal(ctx, 0x2517C8u, gen::fn_sub_21C8B0_0021c8b0);
                        a0 = v0;
                        jal(ctx, 0x2517D4u, gen::fn_sub_3C72D0_003c72d0);
                        a0 = 8;
                        jal(ctx, 0x2517E0u, gen::fn_msgWinRequestMessage_003c7430);
                        a0 = 9;
                        jal(ctx, 0x2517ECu, gen::fn_sub_3C74E0_003c74e0);
                        a0 = 0;
                        jal(ctx, 0x2517F8u, gen::fn_msgWinSetType_003c7560);
                        v0 = 4;
                        sh(v0, sp, 0x28);
                        sh(v0, sp, 0x2A);
                        v0 = 2;
                        sh(v0, sp, 0x2C);
                        sh(zero, sp, 0x2E);
                        a0 = 0;
                        ld(a1, sp, 0x28);
                        jal(ctx, 0x251820u, gen::fn_sub_110F80_00110f80);
                        sw(v0, s0, tut::kPicture);
                        v1 = 6;
                        sw(v1, s0, tut::kStep);
                    }
                    break;
                case 0x25183Cu:  // table[6]: step 6, the picture is ready: start it -> 1
                    // 0x0025183c
                    charge(ctx, 5);
                    lw(a0, s0, tut::kPicture);
                    jal(ctx, 0x251840u, gen::fn_sub_1114B0_001114b0);
                    if (v0 != 0) {
                        // 0x00251850
                        charge(ctx, 7);
                        lw(a0, s0, tut::kPicture);
                        jal(ctx, 0x251854u, gen::fn_sub_111530_00111530);
                        v1 = 1;
                        sw(v1, s0, tut::kStep);
                    }
                    break;
                case 0x25186Cu:  // table[7]: step 7, the picture task ended: close, the tutorial ends
                    // 0x0025186c
                    charge(ctx, 5);
                    lw(a0, s0, tut::kPicture);
                    jal(ctx, 0x251870u, gen::fn_kwlnTaskExists_00195460);
                    if (v0 == 0) {
                        // 0x00251880
                        charge(ctx, 6);
                        jal(ctx, 0x251880u, gen::fn_sub_251A20_00251a20);
                        lw(a0, s0, tut::kFlags);
                        v1 = si(-2);
                        v1 = a0 & v1;
                        sw(v1, s0, tut::kFlags);
                    }
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
        } else {
            // 0x00251124
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00251134
                charge(ctx, 4);
                jal(ctx, 0x251134u, gen::fn_sub_21C860_0021c860);
                if (v0 == 0) {
                    // 0x00251144
                    charge(ctx, 5);
                    lw(a0, s0, tut::kPicture);
                    jal(ctx, 0x251148u, gen::fn_sub_1114B0_001114b0);
                    if (v0 != 0) {
                        // 0x00251158
                        charge(ctx, 13);
                        a0 = 0;
                        jal(ctx, 0x25115Cu, gen::fn_sub_21C8B0_0021c8b0);
                        a0 = v0;
                        jal(ctx, 0x251168u, gen::fn_sub_3C72D0_003c72d0);
                        lw(a0, s0, tut::kPicture);
                        jal(ctx, 0x251174u, gen::fn_sub_111530_00111530);
                        lw(v1, s0, tut::kKind);
                        v0 = 3;
                        if (v1 == v0) {
                            // 0x002511f0
                            charge(ctx, 3);
                            a0 = 16;
                            jal(ctx, 0x2511F4u, gen::fn_msgWinRequestMessage_003c7430);
                        } else {
                            // 0x0025118c
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 == v0) {
                                // 0x002511dc
                                charge(ctx, 5);
                                a0 = 11;
                                jal(ctx, 0x2511E0u, gen::fn_msgWinRequestMessage_003c7430);
                            } else {
                                // 0x00251198
                                charge(ctx, 3);
                                v0 = 1;
                                if (v1 == v0) {
                                    // 0x002511c8
                                    charge(ctx, 5);
                                    a0 = 5;
                                    jal(ctx, 0x2511CCu, gen::fn_msgWinRequestMessage_003c7430);
                                } else {
                                    // 0x002511a4
                                    charge(ctx, 2);
                                    if (v1 == 0) {
                                        // 0x002511b4
                                        charge(ctx, 5);
                                        a0 = 0;
                                        jal(ctx, 0x2511B8u, gen::fn_msgWinRequestMessage_003c7430);
                                    } else {
                                        // 0x002511ac
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                        // 0x002511fc
                        charge(ctx, 4);
                        lw(v1, s0, tut::kKind);
                        v0 = 3;
                        if (v1 == v0) {
                            // 0x0025126c
                            charge(ctx, 3);
                            a0 = 17;
                            jal(ctx, 0x251270u, gen::fn_sub_3C74E0_003c74e0);
                        } else {
                            // 0x0025120c
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 == v0) {
                                // 0x00251258
                                charge(ctx, 5);
                                a0 = 12;
                                jal(ctx, 0x25125Cu, gen::fn_sub_3C74E0_003c74e0);
                            } else {
                                // 0x00251218
                                charge(ctx, 3);
                                a0 = 1;
                                if (v1 == a0) {
                                    // 0x00251244
                                    charge(ctx, 5);
                                    a0 = 6;
                                    jal(ctx, 0x251248u, gen::fn_sub_3C74E0_003c74e0);
                                } else {
                                    // 0x00251224
                                    charge(ctx, 2);
                                    if (v1 == 0) {
                                        // 0x00251234
                                        charge(ctx, 4);
                                        jal(ctx, 0x251234u, gen::fn_sub_3C74E0_003c74e0);
                                    } else {
                                        // 0x0025122c
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                        // 0x00251278
                        charge(ctx, 8);
                        a0 = 0;
                        jal(ctx, 0x25127Cu, gen::fn_msgWinSetType_003c7560);
                        sw(zero, s0, tut::kStep);
                        v1 = 1;
                        sw(v1, s0, tut::kPhase);
                    }
                }
            } else {
                // 0x0025112c
                charge(ctx, 2);
            }
        }
    }
    // 0x00251898 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002518B0 sub_2518B0 -- 284 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpTutOpen] Opens the battle tutorial of kind a0 (K_Assert line 57): sets its seen flag 4871 + kind (0..3), the
// message set (sub_21C7F0), starts the picture task (sub_110F80(0, 0x200040004)) into +16, phase 0, flag 1, +8 = the
// kind.
// Arguments: a0 the tutorial kind 0..3.
void sub_2518B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002518b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpTut);  // the battle tutorial (bp_tut.c) 0x7CE344
    if (v0 == 0) {
        // 0x002518d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5696);  // "bp_tut.c"
        a1 = 57;
        jal(ctx, 0x2518DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002518e4
    charge(ctx, 4);
    lw(s0, gp, kGpBpTut);  // the battle tutorial (bp_tut.c) 0x7CE344
    v0 = 3;
    if (s1 == v0) {
        // 0x0025195c
        charge(ctx, 4);
        a0 = 4874;
        a1 = 1;
        jal(ctx, 0x251964u, gen::fn_datSetFlag_0016f1f0);
    } else {
        // 0x002518f4
        charge(ctx, 3);
        v0 = 2;
        if (s1 == v0) {
            // 0x00251944
            charge(ctx, 6);
            a0 = 4873;
            a1 = 1;
            jal(ctx, 0x25194Cu, gen::fn_datSetFlag_0016f1f0);
        } else {
            // 0x00251900
            charge(ctx, 3);
            a1 = 1;
            if (s1 == a1) {
                // 0x00251930
                charge(ctx, 5);
                a0 = 4872;
                jal(ctx, 0x251934u, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x0025190c
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x0025191c
                    charge(ctx, 5);
                    a0 = 4871;
                    jal(ctx, 0x251920u, gen::fn_datSetFlag_0016f1f0);
                } else {
                    // 0x00251914
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0025196c
    charge(ctx, 24);
    jal(ctx, 0x25196Cu, gen::fn_sub_21C7F0_0021c7f0);
    v0 = 4;
    sh(v0, sp, 0x38);
    sh(v0, sp, 0x3A);
    v0 = 2;
    sh(v0, sp, 0x3C);
    sh(zero, sp, 0x3E);
    a0 = 0;
    ld(a1, sp, 0x38);
    jal(ctx, 0x251994u, gen::fn_sub_110F80_00110f80);
    sw(v0, s0, tut::kPicture);
    sw(zero, s0, tut::kPhase);
    lw(v1, s0, tut::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, tut::kFlags);
    sw(s1, s0, tut::kKind);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00251A20 sub_251A20 -- 72 bytes; frame 0x10: ra sp+0x0
// [bpTutClose] Closes the battle tutorial's windows (K_Assert line 57): sub_3C77A0, sub_21C930.
void sub_251A20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251a20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpTut);  // the battle tutorial (bp_tut.c) 0x7CE344
    if (v0 == 0) {
        // 0x00251a34
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5696);  // "bp_tut.c"
        a1 = 57;
        jal(ctx, 0x251A40u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251a48
    charge(ctx, 8);
    jal(ctx, 0x251A48u, gen::fn_sub_3C77A0_003c77a0);
    jal(ctx, 0x251A50u, gen::fn_sub_21C930_0021c930);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00251A80 sub_251A80 -- 912 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpTutaUpdate] Per-frame update of the second battle tutorial (bp_tuta.c, *$gp 0x7CE348; K_Assert line 49) while
// open: phase 0 waits for the panel, then shows message 0 (5 for the alternate episode, sub_17D800) with choice list
// 1 -> phase 1. Phase 1 (step +8): 0 / 1 the choices -- 'yes' shows message 4 (7) -> 2, 'no' message 2 (6) with list
// 3 -> 1; 2 closes and, in the alternate episode, shows the explanation page 8 -> 3, else ends; 3 closes and ends
// (sub_251ED0, flag 1 cleared).
void sub_251A80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251a80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpTuta);  // the second battle tutorial (bp_tuta.c) 0x7CE348
    if (v1 == 0) {
        // 0x00251a98
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5680);  // "bp_tuta.c"
        a1 = 49;
        jal(ctx, 0x251AA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251aac
    charge(ctx, 6);
    lw(s0, gp, kGpBpTuta);  // the second battle tutorial (bp_tuta.c) 0x7CE348
    lw(v1, s0, tuta::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00251ac4
        charge(ctx, 4);
        lw(v1, s0, tuta::kPhase);
        a0 = 1;
        if (v1 == a0) {
            // 0x00251b60
            charge(ctx, 4);
            lw(a1, s0, tuta::kStep);
            v1 = 3;
            if (a1 == v1) {
                // 0x00251db8
                charge(ctx, 6);
                jal(ctx, 0x251DB8u, gen::fn_sub_3C7990_003c7990);
                jal(ctx, 0x251DC0u, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x00251dd0
                    charge(ctx, 11);
                    a0 = 1;
                    jal(ctx, 0x251DD4u, gen::fn_msgWinClose_003c7650);
                    jal(ctx, 0x251DDCu, gen::fn_sub_3C77A0_003c77a0);
                    jal(ctx, 0x251DE4u, gen::fn_sub_251ED0_00251ed0);
                    lw(a0, s0, tuta::kFlags);
                    v1 = si(-2);
                    v1 = a0 & v1;
                    sw(v1, s0, tuta::kFlags);
                }
            } else {
                // 0x00251b70
                charge(ctx, 3);
                v1 = 2;
                if (a1 == v1) {
                    // 0x00251d30
                    charge(ctx, 6);
                    jal(ctx, 0x251D30u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x251D38u, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x00251d48
                        charge(ctx, 7);
                        a0 = 1;
                        jal(ctx, 0x251D4Cu, gen::fn_msgWinClose_003c7650);
                        jal(ctx, 0x251D54u, gen::fn_sub_17D800_0017d800);
                        if (v0 != 0) {
                            // 0x00251d84
                            charge(ctx, 13);
                            a0 = 2;
                            jal(ctx, 0x251D88u, gen::fn_sub_21C8B0_0021c8b0);
                            a0 = v0;
                            jal(ctx, 0x251D94u, gen::fn_sub_3C94E0_003c94e0);
                            a0 = 8;
                            jal(ctx, 0x251DA0u, gen::fn_sub_3C9790_003c9790);
                            v1 = 3;
                            sw(v1, s0, tuta::kStep);
                        } else {
                            // 0x00251d64
                            charge(ctx, 8);
                            jal(ctx, 0x251D64u, gen::fn_sub_251ED0_00251ed0);
                            lw(a0, s0, tuta::kFlags);
                            v1 = si(-2);
                            v1 = a0 & v1;
                            sw(v1, s0, tuta::kFlags);
                        }
                    }
                } else {
                    // 0x00251b7c
                    charge(ctx, 2);
                    if (a1 == a0) {
                        // 0x00251c5c
                        charge(ctx, 6);
                        jal(ctx, 0x251C5Cu, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x251C64u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x00251c74
                            charge(ctx, 5);
                            jal(ctx, 0x251C74u, gen::fn_msgWinLastSelection_003c7610);
                            a0 = 1;
                            if (v0 == a0) {
                                // 0x00251cf0
                                charge(ctx, 6);
                                jal(ctx, 0x251CF0u, gen::fn_msgWinClose_003c7650);
                                jal(ctx, 0x251CF8u, gen::fn_sub_17D800_0017d800);
                                if (v0 == 0) {
                                    // 0x00251d14
                                    charge(ctx, 1);
                                    a0 = 4;
                                } else {
                                    // 0x00251d08
                                    charge(ctx, 3);
                                    a0 = 7;
                                }
                                // 0x00251d18
                                charge(ctx, 6);
                                jal(ctx, 0x251D18u, gen::fn_msgWinRequestMessage_003c7430);
                                v1 = 2;
                                sw(v1, s0, tuta::kStep);
                            } else {
                                // 0x00251c88
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x00251c98
                                    charge(ctx, 6);
                                    jal(ctx, 0x251C98u, gen::fn_msgWinClose_003c7650);
                                    jal(ctx, 0x251CA0u, gen::fn_sub_17D800_0017d800);
                                    if (v0 == 0) {
                                        // 0x00251cbc
                                        charge(ctx, 1);
                                        a0 = 2;
                                    } else {
                                        // 0x00251cb0
                                        charge(ctx, 3);
                                        a0 = 6;
                                    }
                                    // 0x00251cc0
                                    charge(ctx, 12);
                                    jal(ctx, 0x251CC0u, gen::fn_msgWinRequestMessage_003c7430);
                                    a0 = 3;
                                    jal(ctx, 0x251CCCu, gen::fn_sub_3C74E0_003c74e0);
                                    a0 = 1;
                                    jal(ctx, 0x251CD8u, gen::fn_msgWinSetType_003c7560);
                                    v1 = 1;
                                    sw(v1, s0, tuta::kStep);
                                } else {
                                    // 0x00251c90
                                    charge(ctx, 2);
                                }
                            }
                        }
                    } else {
                        // 0x00251b84
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x00251b94
                            charge(ctx, 6);
                            jal(ctx, 0x251B94u, gen::fn_sub_3C7990_003c7990);
                            jal(ctx, 0x251B9Cu, gen::fn_sub_3C7850_003c7850);
                            if (v0 == 0) {
                                // 0x00251bac
                                charge(ctx, 5);
                                jal(ctx, 0x251BACu, gen::fn_msgWinLastSelection_003c7610);
                                a0 = 1;
                                if (v0 == a0) {
                                    // 0x00251c1c
                                    charge(ctx, 6);
                                    jal(ctx, 0x251C1Cu, gen::fn_msgWinClose_003c7650);
                                    jal(ctx, 0x251C24u, gen::fn_sub_17D800_0017d800);
                                    if (v0 == 0) {
                                        // 0x00251c40
                                        charge(ctx, 1);
                                        a0 = 4;
                                    } else {
                                        // 0x00251c34
                                        charge(ctx, 3);
                                        a0 = 7;
                                    }
                                    // 0x00251c44
                                    charge(ctx, 6);
                                    jal(ctx, 0x251C44u, gen::fn_msgWinRequestMessage_003c7430);
                                    v1 = 2;
                                    sw(v1, s0, tuta::kStep);
                                } else {
                                    // 0x00251bc0
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        // 0x00251bd0
                                        charge(ctx, 6);
                                        jal(ctx, 0x251BD0u, gen::fn_msgWinClose_003c7650);
                                        jal(ctx, 0x251BD8u, gen::fn_sub_17D800_0017d800);
                                        if (v0 == 0) {
                                            // 0x00251bf4
                                            charge(ctx, 1);
                                            a0 = 2;
                                        } else {
                                            // 0x00251be8
                                            charge(ctx, 3);
                                            a0 = 6;
                                        }
                                        // 0x00251bf8
                                        charge(ctx, 9);
                                        jal(ctx, 0x251BF8u, gen::fn_msgWinRequestMessage_003c7430);
                                        a0 = 3;
                                        jal(ctx, 0x251C04u, gen::fn_sub_3C74E0_003c74e0);
                                        v1 = 1;
                                        sw(v1, s0, tuta::kStep);
                                    } else {
                                        // 0x00251bc8
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        } else {
                            // 0x00251b8c
                            charge(ctx, 2);
                        }
                    }
                }
            }
        } else {
            // 0x00251ad4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00251ae4
                charge(ctx, 4);
                jal(ctx, 0x251AE4u, gen::fn_sub_21C860_0021c860);
                if (v0 == 0) {
                    // 0x00251af4
                    charge(ctx, 12);
                    v0 = 1;
                    sw(v0, s0, tuta::kPhase);
                    a0 = 2;
                    jal(ctx, 0x251B00u, gen::fn_sub_21C8B0_0021c8b0);
                    a0 = v0;
                    jal(ctx, 0x251B0Cu, gen::fn_sub_3C72D0_003c72d0);
                    jal(ctx, 0x251B14u, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x00251b30
                        charge(ctx, 1);
                        a0 = 0;
                    } else {
                        // 0x00251b24
                        charge(ctx, 3);
                        a0 = 5;
                    }
                    // 0x00251b34
                    charge(ctx, 11);
                    jal(ctx, 0x251B34u, gen::fn_msgWinRequestMessage_003c7430);
                    a0 = 1;
                    jal(ctx, 0x251B40u, gen::fn_sub_3C74E0_003c74e0);
                    a0 = 0;
                    jal(ctx, 0x251B4Cu, gen::fn_msgWinSetType_003c7560);
                    sw(zero, s0, tuta::kStep);
                }
            } else {
                // 0x00251adc
                charge(ctx, 2);
            }
        }
    }
    // 0x00251dfc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00251ED0 sub_251ED0 -- 72 bytes; frame 0x10: ra sp+0x0
// [bpTutaClose] Closes the second battle tutorial's windows (K_Assert line 49): sub_3C77A0, sub_21C930.
void sub_251ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251ed0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpTuta);  // the second battle tutorial (bp_tuta.c) 0x7CE348
    if (v0 == 0) {
        // 0x00251ee4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5680);  // "bp_tuta.c"
        a1 = 49;
        jal(ctx, 0x251EF0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251ef8
    charge(ctx, 8);
    jal(ctx, 0x251EF8u, gen::fn_sub_3C77A0_003c77a0);
    jal(ctx, 0x251F00u, gen::fn_sub_21C930_0021c930);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00251F40 sub_251F40 -- 280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpoOpen] Opens the bpo banner (bpo_main.c, *$gp 0x7CE34C; K_Assert line 54) of kind a0: the plate (texture 57 for
// kind 0, 58 for kind 1, of set 1) into its three quads (+16 / +272 / +528), sound request (1, 15, 2, 15), frame 0,
// flags 1 | 2.
// Arguments: a0 kind 0 / 1.
void sub_251F40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251f40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
    if (v0 == 0) {
        // 0x00251f64
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5664);  // "bpo_main.c"
        a1 = 54;
        jal(ctx, 0x251F70u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251f78
    charge(ctx, 9);
    lw(s0, gp, kGpBpoWork);  // the bpo work (bpo_main.c) 0x7CE34C
    a0 = 1;
    jal(ctx, 0x251F80u, gen::fn_sub_21C3F0_0021c3f0);
    sw(zero, s0, bpo::kFlags);
    sw(s2, s0, bpo::kKind);
    v1 = 1;
    if (s2 == v1) {
        // 0x00251fc8
        charge(ctx, 5);
        a0 = v0;
        a1 = 58;
        jal(ctx, 0x251FD0u, gen::fn_sub_21CCA0_0021cca0);
        s1 = v0;
    } else {
        // 0x00251f9c
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x00251fac
            charge(ctx, 7);
            a0 = v0;
            a1 = 57;
            jal(ctx, 0x251FB4u, gen::fn_sub_21CCA0_0021cca0);
            s1 = v0;
        } else {
            // 0x00251fa4
            charge(ctx, 2);
        }
    }
    // 0x00251fdc
    charge(ctx, 31);
    a0 = addiu(s0, 16);
    a1 = s1;
    jal(ctx, 0x251FE4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 272);
    a1 = s1;
    jal(ctx, 0x251FF4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 528);
    a1 = s1;
    jal(ctx, 0x252004u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 1;
    a1 = 15;
    a2 = 2;
    a3 = a1;
    jal(ctx, 0x25201Cu, gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, bpo::kFrame);
    lw(v1, s0, bpo::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, bpo::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, bpo::kFlags);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00266F60 sub_266F60 -- 264 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpPersonaOpen] Opens the battle panel persona status (bp_persona.c, *$gp 0x7CE398; K_Assert line 36) for persona
// a0: its record (sub_1749A0), a status task set (fclMisc_CreatePsStatusTasks(0, 0, 5, 0)) into +4 showing it
// (sub_3C9B00), sub_3C9CD0(-1), sub_3C9D00(8), page 1 when the party has two or more members (sub_1756F0) else 0
// (sub_3C9E00); +8 = the persona, flags 1 | 2.
// Arguments: a0 persona id.
void sub_266F60(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00266f60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpPersona);  // the battle panel persona work (bp_persona.c) 0x7CE398
    if (v0 == 0) {
        // 0x00266f80
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4920);  // "bp_persona.c"
        a1 = 36;
        jal(ctx, 0x266F8Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00266f94
    charge(ctx, 32);
    lw(s0, gp, kGpBpPersona);  // the battle panel persona work (bp_persona.c) 0x7CE398
    sh(s1, s0, bppersona::kPersona);
    a0 = s1;
    jal(ctx, 0x266FA0u, gen::fn_sub_1749A0_001749a0);
    s1 = v0;
    a0 = 0;
    a1 = 0;
    a2 = 5;
    a3 = 0;
    jal(ctx, 0x266FBCu, gen::fn_fclMisc_CreatePsStatusTasks_003c9850);
    sw(v0, s0, bppersona::kStatus);
    a0 = v0;
    a1 = s1;
    a2 = 0;
    jal(ctx, 0x266FD4u, gen::fn_sub_3C9B00_003c9b00);
    lw(a0, s0, bppersona::kStatus);
    a1 = si(-1);
    jal(ctx, 0x266FE4u, gen::fn_sub_3C9CD0_003c9cd0);
    lw(a0, s0, bppersona::kStatus);
    a1 = 8;
    jal(ctx, 0x266FF4u, gen::fn_sub_3C9D00_003c9d00);
    jal(ctx, 0x266FFCu, gen::fn_sub_1756F0_001756f0);
    v0 = v0 & 0xFFFF;
    at = slti(v0, 2);
    if (at != 0) {
        // 0x0026702c
        charge(ctx, 4);
        lw(a0, s0, bppersona::kStatus);
        a1 = 0;
        jal(ctx, 0x267034u, gen::fn_sub_3C9E00_003c9e00);
    } else {
        // 0x00267014
        charge(ctx, 6);
        lw(a0, s0, bppersona::kStatus);
        a1 = 1;
        jal(ctx, 0x26701Cu, gen::fn_sub_3C9E00_003c9e00);
    }
    // 0x0026703c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v1, s0, bppersona::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, bppersona::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, bppersona::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00267070 sub_267070 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpPersonaSet] Switches the battle panel persona status to persona a0 (K_Assert line 92: a different one): +8, the
// record shown (sub_3C9B00), flag 2.
// Arguments: a0 persona id.
void sub_267070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00267070
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpPersona);  // the battle panel persona work (bp_persona.c) 0x7CE398
    if (v0 == 0) {
        // 0x00267090
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4920);  // "bp_persona.c"
        a1 = 36;
        jal(ctx, 0x26709Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002670a4
    charge(ctx, 5);
    lw(s0, gp, kGpBpPersona);  // the battle panel persona work (bp_persona.c) 0x7CE398
    lhu(v1, s0, bppersona::kPersona);
    v0 = s1 & 0xFFFF;
    if (v1 == v0) {
        // 0x002670b8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4920);  // "bp_persona.c"
        a1 = 92;
        jal(ctx, 0x2670C4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002670cc
    charge(ctx, 18);
    sh(s1, s0, bppersona::kPersona);
    a0 = s1;
    jal(ctx, 0x2670D4u, gen::fn_sub_1749A0_001749a0);
    lw(a0, s0, bppersona::kStatus);
    a1 = v0;
    a2 = 0;
    jal(ctx, 0x2670E8u, gen::fn_sub_3C9B00_003c9b00);
    lw(v1, s0, bppersona::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, bppersona::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00267210 sub_267210 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpPersonaIsShown] Flag 2 of the battle panel persona status (set when a persona is shown; K_Assert line 36).
void sub_267210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00267210
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpPersona);  // the battle panel persona work (bp_persona.c) 0x7CE398
    if (v0 == 0) {
        // 0x00267224
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4920);  // "bp_persona.c"
        a1 = 36;
        jal(ctx, 0x267230u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00267238 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpPersona);  // the battle panel persona work (bp_persona.c) 0x7CE398
    lw(v0, v0, bppersona::kFlags);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027B9F0 sub_27B9F0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpSelectOpen] Opens the battle select marker (bp_select.c, *$gp 0x7CE3E4; K_Assert line 39): texture 58 of set 2
// into its quad (+16), the frame +272 = 0, clears flag 2 (closing), places it (sub_27B6C0), flag 1.
void sub_27B9F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b9f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpSelect);  // the battle select work (bp_select.c) 0x7CE3E4
    if (v0 == 0) {
        // 0x0027ba08
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4152);  // "bp_select.c"
        a1 = 39;
        jal(ctx, 0x27BA14u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027ba1c
    charge(ctx, 27);
    lw(s0, gp, kGpBpSelect);  // the battle select work (bp_select.c) 0x7CE3E4
    a0 = 2;
    jal(ctx, 0x27BA24u, gen::fn_sub_21C3F0_0021c3f0);
    a0 = v0;
    a1 = 58;
    jal(ctx, 0x27BA34u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 16);
    a1 = v0;
    jal(ctx, 0x27BA44u, gen::fn_sub_21D3B0_0021d3b0);
    sw(zero, s0, bpselect::kFrame);
    lw(v1, s0, bpselect::kFlags);
    v0 = si(-3);
    v0 = v1 & v0;
    sw(v0, s0, bpselect::kFlags);
    jal(ctx, 0x27BA60u, gen::fn_sub_27B6C0_0027b6c0);
    lw(v1, s0, bpselect::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, bpselect::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027BA90 sub_27BA90 -- 76 bytes; frame 0x10: ra sp+0x0
// [bpSelectClose] Starts closing the battle select marker: frame +272 = 0, flag 2 (K_Assert line 39).
void sub_27BA90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ba90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpSelect);  // the battle select work (bp_select.c) 0x7CE3E4
    if (v1 == 0) {
        // 0x0027baa4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4152);  // "bp_select.c"
        a1 = 39;
        jal(ctx, 0x27BAB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bab8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, gp, kGpBpSelect);  // the battle select work (bp_select.c) 0x7CE3E4
    sw(zero, a0, bpselect::kFrame);
    lw(v1, a0, bpselect::kFlags);
    v1 = v1 | 0x2;
    sw(v1, a0, bpselect::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027BAE0 sub_27BAE0 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpSelectSetPos] Moves the battle select marker to the screen point a0 {f32 x, y} (+276 / +280; K_Assert line 39)
// and places it again while open (sub_27B6C0).
// Arguments: a0 f32[2].
void sub_27BAE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0027bae0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBpSelect);  // the battle select work (bp_select.c) 0x7CE3E4
    if (v1 == 0) {
        // 0x0027bafc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4152);  // "bp_select.c"
        a1 = 39;
        jal(ctx, 0x27BB08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bb10
    charge(ctx, 9);
    lw(v1, gp, kGpBpSelect);  // the battle select work (bp_select.c) 0x7CE3E4
    lwc1(f1, s0, 0);
    lwc1(f0, s0, 4);
    swc1(f1, v1, bpselect::kPos);
    swc1(f0, v1, bpselect::kPos + 4);
    lw(v1, v1, bpselect::kFlags);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0027bb34
        charge(ctx, 2);
        jal(ctx, 0x27BB34u, gen::fn_sub_27B6C0_0027b6c0);
    }
    // 0x0027bb3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
