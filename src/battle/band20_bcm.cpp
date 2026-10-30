// Phase 5 slice band20 -- the battle command panel bcm_panel.c: register / open, the per-frame layout and draw
// of the panel, its four sub-lists, steps, frame, help line and detail bar.
// The bodies come from p3fes_handgen (register ABI: arguments in $a0.., the result in $v0) and keep every register,
// frame slot, $ra link, cycle charge and check point of the recompiled body (game/include/p3fes/game/hg_cpu.h); this
// file adds the names: one role comment per function ([proposed name] first), named offsets of the records in
// game/include/p3fes/game/band20.h (a constant replaces only a literal of its own value), the K_Assert(file, line)
// calls (`jr $ra` in retail: a failed check carries on), the RW slots the bodies call through, the float constants of
// the $gp area with their values, and `while` notes on the counted loops.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/band20.h"

namespace p3fes::recomp_gen {
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLineGetWidth_003b19d0(p3fes::EEContext&);
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21DD60_0021dd60(p3fes::EEContext&);
void fn_sub_21F0C0_0021f0c0(p3fes::EEContext&);
void fn_sub_21F140_0021f140(p3fes::EEContext&);
void fn_sub_21F150_0021f150(p3fes::EEContext&);
void fn_sub_21F3C0_0021f3c0(p3fes::EEContext&);
void fn_sub_21F410_0021f410(p3fes::EEContext&);
void fn_sub_221B60_00221b60(p3fes::EEContext&);
void fn_sub_223290_00223290(p3fes::EEContext&);
void fn_sub_224150_00224150(p3fes::EEContext&);
void fn_sub_224940_00224940(p3fes::EEContext&);
void fn_sub_225040_00225040(p3fes::EEContext&);
void fn_sub_2255F0_002255f0(p3fes::EEContext&);
void fn_sub_225670_00225670(p3fes::EEContext&);
void fn_sub_2257F0_002257f0(p3fes::EEContext&);
void fn_sub_226040_00226040(p3fes::EEContext&);
void fn_sub_2265D0_002265d0(p3fes::EEContext&);
void fn_sub_227800_00227800(p3fes::EEContext&);
void fn_sub_227F30_00227f30(p3fes::EEContext&);
void fn_sub_2289B0_002289b0(p3fes::EEContext&);
void fn_sub_228E40_00228e40(p3fes::EEContext&);
void fn_sub_229B40_00229b40(p3fes::EEContext&);
void fn_sub_22A2B0_0022a2b0(p3fes::EEContext&);
void fn_sub_22AE80_0022ae80(p3fes::EEContext&);
void fn_sub_22B530_0022b530(p3fes::EEContext&);
void fn_sub_22B580_0022b580(p3fes::EEContext&);
void fn_sub_22B630_0022b630(p3fes::EEContext&);
void fn_sub_22BCF0_0022bcf0(p3fes::EEContext&);
void fn_sub_22C0A0_0022c0a0(p3fes::EEContext&);
void fn_sub_22C2D0_0022c2d0(p3fes::EEContext&);
void fn_sub_22C5A0_0022c5a0(p3fes::EEContext&);
void fn_sub_238BF0_00238bf0(p3fes::EEContext&);
void fn_sub_238DC0_00238dc0(p3fes::EEContext&);
void fn_sub_239140_00239140(p3fes::EEContext&);
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b20;  // the named offsets and $gp slots of band20.h

// 0x0021F0C0 sub_21F0C0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bcmPanel_Register](work) bcm_panel.c: asserts the slot is free (line 238), clears the flags, the list kind
// and the seven command states and stores the work.
void sub_21F0C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021f0c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v1 != 0) {
        // 0x0021f0dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 238;
        jal(ctx, 0x21F0E8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 238): `jr $ra` in retail, execution goes on
    }
    // 0x0021f0f0
    charge(ctx, 5);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    a0 = 0;
    for (;;) {  // while (a0 < 7)
        // 0x0021f114
        charge(ctx, 3);
        v1 = slti(a0, 7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021f104
        charge(ctx, 4);
        v1 = sll(a0, 2);
        v1 = addu(s0, v1);
        sw(zero, v1, 4624);
        a0 = addiu(a0, 1);
    }
    // 0x0021f120
    charge(ctx, 6);
    sw(s0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021F140 sub_21F140 -- 12 bytes; leaf frame (no stack)
// [bcmPanel_Unregister] clears the bcm_panel.c slot.
void sub_21F140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, gp{ctx, 28};
    // 0x0021f140
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
}

// 0x0021F150 sub_21F150 -- 616 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_Open](cmd) sets the panel up: the persona command hidden (bit 4) unless sub_2D1A70; the base quads
// (pages 16, 27, 28, 34, 14), the current command's page, the seven frames (17 usable / 65 not) and names (pages
// 20..26), the header (sub_22B580); current = cmd, previous / sub-list previous = -1; flag bit 0.
void sub_21F150(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021f150
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0021f178
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x21F184u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0021f18c
    charge(ctx, 10);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x21F194u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    lw(v0, s0, kBcmFlags);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021f1b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 259;
        jal(ctx, 0x21F1C0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 259): `jr $ra` in retail, execution goes on
    }
    // 0x0021f1c8
    charge(ctx, 8);
    lw(v1, s0, kBcmFlags);
    v0 = si(-17);
    v0 = v1 & v0;
    sw(v0, s0, kBcmFlags);
    jal(ctx, 0x21F1D8u, gen::fn_sub_2D1A70_002d1a70);
    if (v0 == 0) {
        // 0x0021f1e8
        charge(ctx, 3);
        lw(v0, s0, kBcmFlags);
        v0 = v0 | 0x10;
        sw(v0, s0, kBcmFlags);
    }
    // 0x0021f1f4
    charge(ctx, 51);
    a0 = s2;
    a1 = 16;
    jal(ctx, 0x21F1FCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBcmQuadBase);
    a1 = v0;
    jal(ctx, 0x21F20Cu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s2;
    a1 = 27;
    jal(ctx, 0x21F21Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBcmQuadA);
    a1 = v0;
    jal(ctx, 0x21F22Cu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s2;
    a1 = 28;
    jal(ctx, 0x21F23Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBcmQuadB);
    a1 = v0;
    jal(ctx, 0x21F24Cu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s2;
    a1 = 34;
    jal(ctx, 0x21F25Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBcmQuadD);
    a1 = v0;
    jal(ctx, 0x21F26Cu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s2;
    a1 = 14;
    jal(ctx, 0x21F27Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBcmQuadC);
    a1 = v0;
    jal(ctx, 0x21F28Cu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    a0 = s2;
    a1 = s3;
    jal(ctx, 0x21F29Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = addiu(s0, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x21F2ACu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
    s1 = 0;
    for (;;) {  // while (s1 < 7)
        // 0x0021f31c
        charge(ctx, 3);
        v0 = slti(s1, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021f2c0
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, kBcmCmdState);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0021f2f0
            charge(ctx, 4);
            a0 = s2;
            a1 = 65;
            jal(ctx, 0x21F2F8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        } else {
            // 0x0021f2d8
            charge(ctx, 6);
            a0 = s2;
            a1 = 17;
            jal(ctx, 0x21F2E0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        }
        // 0x0021f300
        charge(ctx, 7);
        v1 = sll(s1, 8);
        v1 = addu(s0, v1);
        a0 = addiu(v1, kBcmCmdFrames);
        a1 = v0;
        jal(ctx, 0x21F310u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
        s1 = addiu(s1, 1);
    }
    // 0x0021f328
    charge(ctx, 3);
    s1 = 0;
    for (;;) {  // while (s1 < 7)
        // 0x0021f360
        charge(ctx, 3);
        v0 = slti(s1, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021f334
        charge(ctx, 11);
        a1 = addiu(s1, 20);
        a0 = s2;
        jal(ctx, 0x21F33Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = sll(s1, 8);
        v1 = addu(s0, v1);
        a0 = addiu(v1, kBcmCmdNames);
        a1 = v0;
        jal(ctx, 0x21F354u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
        s1 = addiu(s1, 1);
    }
    // 0x0021f36c
    charge(ctx, 19);
    jal(ctx, 0x21F36Cu, gen::fn_sub_22B580_0022b580);
    sw(s3, s0, kBcmCur);
    v1 = si(-1);
    sw(v1, s0, kBcmPrev);
    sw(zero, s0, kBcmSub);
    sw(v1, s0, kBcmSubPrev);
    sw(zero, s0, kBcmState);
    lw(v1, s0, kBcmFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, kBcmFlags);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0021F3C0 sub_21F3C0 -- 76 bytes; frame 0x10: ra sp+0x0
// [bcmPanel_Close] clears flag bit 0.
void sub_21F3C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021f3c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v1 == 0) {
        // 0x0021f3d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x21F3E0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0021f3e8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    lw(a0, a1, kBcmFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, a1, kBcmFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0021F410 sub_21F410 -- 10052 bytes; frame 0xD0: ra sp+0x80, s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bcmPanel_Layout] the command panel's per-frame layout: the help line (sub_22B630), the state timers, the
// cursor's sweep between the previous and current command (sin / cos), the base quads and the current / previous
// command pages with the fades of the cursor and sub-list states, then the open sub-list's layout (kind 1 sub_22A2B0,
// 2 sub_228E40, 3 sub_223290 with its steps sub_227F30 / sub_2257F0, 4 sub_224940), the frame (sub_2265D0) and the
// detail bar (sub_22C2D0).
void sub_21F410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    // 0x0021f410
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0021f468
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x21F474u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0021f47c
    charge(ctx, 9);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x21F484u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s1 = v0;
    lw(v0, s0, kBcmFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021f4a0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 337;
        jal(ctx, 0x21F4ACu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 337): `jr $ra` in retail, execution goes on
    }
    // 0x0021f4b4
    charge(ctx, 7);
    lwc1(f24, s0, kBcmFade);
    jal(ctx, 0x21F4B8u, gen::fn_sub_22B630_0022b630);
    lw(v0, s0, kBcmState);
    at = sltiu(v0, 9);
    if (at != 0) {
        // 0x0021f4d0
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 30256);  // &0x7B7630
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x21F4ECu:  // table[1, 2, 8]
            // 0x0021f4ec
            charge(ctx, 4);
            lw(v0, s0, 17996);
            at = slti(v0, 4);
            if (at != 0) {
                // 0x0021f4fc
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sw(v0, s0, 17996);
            }
            break;
        case 0x21F50Cu:  // table[3]
            // 0x0021f50c
            charge(ctx, 4);
            lw(v0, s0, 18000);
            at = slti(v0, 3);
            if (at != 0) {
                // 0x0021f51c
                charge(ctx, 2);
                v0 = addiu(v0, 1);
                sw(v0, s0, 18000);
            }
            // 0x0021f524
            charge(ctx, 4);
            lw(v1, s0, 18000);
            v0 = 3;
            if (v1 == v0) {
                // 0x0021f534
                charge(ctx, 6);
                lw(v1, s0, 0);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, 0);
            }
            break;
        case 0x21F54Cu:  // table[4, 5]
            // 0x0021f54c
            charge(ctx, 4);
            lw(v0, s0, 18008);
            at = slti(v0, 6);
            if (at != 0) {
                // 0x0021f55c
                charge(ctx, 2);
                v0 = addiu(v0, 1);
                sw(v0, s0, 18008);
            }
            // 0x0021f564
            charge(ctx, 4);
            lw(v1, s0, 18008);
            v0 = 6;
            if (v1 == v0) {
                // 0x0021f574
                charge(ctx, 4);
                lw(v1, s0, 0);
                v0 = si(-9);
                v0 = v1 & v0;
                sw(v0, s0, 0);
            }
            break;
        case 0x21F584u:  // table[0, 6, 7]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x0021f584
    charge(ctx, 4);
    lw(v0, s0, 17968);
    a0 = 3;
    if (v0 == a0) {
        // 0x0021f59c
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x0021f5ac
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_0021f63c;
            }
            // 0x0021f5b4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_0021f63c;
            }
            // 0x0021f5c0
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0021f63c;
            }
            // 0x0021f5cc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0021f5dc
                charge(ctx, 24);
                lwc1(f0, s0, 18000);
                v0 = 0x42260000;
                mtc1(v0, f1);
                cvt_s_w(f3, f0);
                mul_s(f0, f1, f3);
                v0 = 0x40400000;
                mtc1(v0, f2);
                div_s(f1, f0, f2);
                v0 = 0x42760000;
                mtc1(v0, f0);
                add_s(f23, f0, f1);
                v0 = lui(0xC1DC);
                mtc1(v0, f0);
                mul_s(f0, f0, f3);
                div_s(f1, f0, f2);
                lwc1(f0, gp, -31764);  // 0x7CB0DC = 388.5f
                add_s(f22, f0, f1);
            } else {
                // 0x0021f5d4
                charge(ctx, 2);
                // 0x0021f6a4
                charge(ctx, 7);
                a0 = 0x690000;
                a0 = addiu(a0, -7296);  // "bcm_panel.c"
                a1 = 389;
                jal(ctx, 0x21F6B0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 389): `jr $ra` in retail, execution goes on
            }
            goto L_0021f72c;
        }
    L_0021f63c:
        charge(ctx, 26);
        lwc1(f0, s0, 18000);
        v0 = lui(0xC226);
        mtc1(v0, f1);
        cvt_s_w(f3, f0);
        mul_s(f0, f1, f3);
        v0 = 0x40400000;
        mtc1(v0, f2);
        div_s(f1, f0, f2);
        v0 = 0x42CE0000;
        mtc1(v0, f0);
        add_s(f23, f0, f1);
        v0 = 0x41DC0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f3);
        div_s(f1, f0, f2);
        v0 = 361;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f22, f0, f1);
    } else {
        // 0x0021f594
        charge(ctx, 2);
        // 0x0021f6c0
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x0021f6d0
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_0021f720;
            }
            // 0x0021f6d8
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_0021f720;
            }
            // 0x0021f6e4
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0021f720;
            }
            // 0x0021f6f0
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0021f700
                charge(ctx, 8);
                v0 = 0x42CE0000;
                mtc1(v0, f23);
                v0 = 361;
                mtc1(v0, f0);
                cvt_s_w(f22, f0);
            } else {
                // 0x0021f6f8
                charge(ctx, 2);
            }
            goto L_0021f72c;
        }
    L_0021f720:
        charge(ctx, 3);
        v0 = 0x42760000;
        mtc1(v0, f23);
        lwc1(f22, gp, -31764);  // 0x7CB0DC = 388.5f
    }
L_0021f72c:
    charge(ctx, 49);
    v0 = 0x43200000;
    mtc1(v0, f0);
    add_s(f1, f0, f23);
    v0 = 0x42CE0000;
    mtc1(v0, f0);
    sub_s(f21, f1, f0);
    v0 = 361;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    add_s(f0, f1, f22);
    sub_s(f20, f0, f1);
    v0 = 0x427A0000;
    mtc1(v0, f0);
    sub_s(f30, f23, f0);
    sub_s(f28, f22, f0);
    a0 = s1;
    a1 = 16;
    jal(ctx, 0x21F780u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f30, sp, 0x90);
    swc1(f28, sp, 0x94);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x98);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x9C);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x21F7B0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0xCC);
    sb(v0, sp, 0xCD);
    sb(v0, sp, 0xCE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f28, f0, f24);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f28);
    if (cond(ctx)) {
        // 0x0021f808
        charge(ctx, 6);
        sub_s(f0, f28, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0021f7f0
        charge(ctx, 6);
        cvt_w_s(f0, f28);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0021f820
    charge(ctx, 9);
    sb(v1, sp, 0xCF);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0xCC);
    jal(ctx, 0x21F82Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v0, s0, 17968);
    a0 = 3;
    if (v0 == a0) {
        // 0x0021f84c
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x0021f85c
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_0021f8f4;
            }
            // 0x0021f864
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_0021f8f4;
            }
            // 0x0021f870
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0021f8f4;
            }
            // 0x0021f87c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0021f88c
                charge(ctx, 26);
                lwc1(f0, s0, 18000);
                v0 = lui(0xC288);
                mtc1(v0, f1);
                cvt_s_w(f3, f0);
                mul_s(f0, f1, f3);
                v0 = 0x40400000;
                mtc1(v0, f2);
                div_s(f1, f0, f2);
                v0 = 0x42A40000;
                mtc1(v0, f0);
                add_s(f29, f0, f1);
                v0 = lui(0xC1B8);
                mtc1(v0, f0);
                mul_s(f0, f0, f3);
                div_s(f1, f0, f2);
                v0 = 369;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f27, f0, f1);
            } else {
                // 0x0021f884
                charge(ctx, 2);
            }
            goto L_0021f9c8;
        }
    L_0021f8f4:
        charge(ctx, 25);
        lwc1(f0, s0, 18000);
        v0 = 0x42880000;
        mtc1(v0, f1);
        cvt_s_w(f3, f0);
        mul_s(f0, f1, f3);
        v0 = 0x40400000;
        mtc1(v0, f2);
        div_s(f1, f0, f2);
        v0 = 0x41600000;
        mtc1(v0, f0);
        add_s(f29, f0, f1);
        v0 = 0x41B80000;
        mtc1(v0, f0);
        mul_s(f0, f0, f3);
        div_s(f1, f0, f2);
        v0 = 0x43AD0000;
        mtc1(v0, f0);
        add_s(f27, f0, f1);
    } else {
        // 0x0021f844
        charge(ctx, 2);
        // 0x0021f958
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x0021f968
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_0021f9b0;
            }
            // 0x0021f970
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_0021f9b0;
            }
            // 0x0021f97c
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0021f9b0;
            }
            // 0x0021f988
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0021f998
                charge(ctx, 6);
                v0 = 0x41600000;
                mtc1(v0, f29);
                v0 = 0x43AD0000;
                mtc1(v0, f27);
            } else {
                // 0x0021f990
                charge(ctx, 2);
            }
            goto L_0021f9c8;
        }
    L_0021f9b0:
        charge(ctx, 6);
        v0 = 0x42A40000;
        mtc1(v0, f29);
        v0 = 369;
        mtc1(v0, f0);
        cvt_s_w(f27, f0);
    }
L_0021f9c8:
    charge(ctx, 20);
    a0 = s1;
    lw(a1, s0, 17972);
    jal(ctx, 0x21F9D0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f29, sp, 0x90);
    swc1(f27, sp, 0x94);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x98);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x9C);
    a0 = addiu(s0, 4656);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x21FA00u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    lw(v1, s0, 17968);
    v0 = 8;
    if (v1 != v0) {
        // 0x0021fa18
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            goto L_0021fa38;
        }
        // 0x0021fa24
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_0021fa38;
        }
        // 0x0021fa30
        charge(ctx, 2);
        // 0x0021fa90
        charge(ctx, 16);
        a0 = s1;
        lw(a1, s0, 17972);
        jal(ctx, 0x21FA98u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        swc1(f29, sp, 0x90);
        swc1(f27, sp, 0x94);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x98);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x9C);
        a0 = addiu(s0, 4912);
        a1 = addiu(sp, 0x90);
        jal(ctx, 0x21FAC8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        goto L_0021fad0;
    }
L_0021fa38:
    charge(ctx, 4);
    lw(v1, s0, 17996);
    v0 = 4;
    if (v1 != v0) {
        // 0x0021fa48
        charge(ctx, 18);
        a0 = s1;
        lw(a1, s0, 17976);
        jal(ctx, 0x21FA50u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        swc1(f29, sp, 0x90);
        swc1(f27, sp, 0x94);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x98);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x9C);
        a0 = addiu(s0, 4912);
        a1 = addiu(sp, 0x90);
        jal(ctx, 0x21FA80u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    }
L_0021fad0:
    charge(ctx, 8);
    v0 = 255;
    sb(v0, sp, 0xCC);
    sb(v0, sp, 0xCD);
    sb(v0, sp, 0xCE);
    lw(v1, s0, 17968);
    a2 = 3;
    if (v1 == a2) {
        // 0x0021fc88
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x0021fc98
            charge(ctx, 2);
            if (v1 == a2) {
                goto L_0021fdf0;
            }
            // 0x0021fca0
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_0021fdf0;
            }
            // 0x0021fcac
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0021fdf0;
            }
            // 0x0021fcb8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0021fcc8
                charge(ctx, 17);
                lwc1(f0, s0, 18000);
                cvt_s_w(f1, f0);
                v0 = 0x40400000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f0, f0, f1);
                mul_s(f1, f0, f24);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0021fd24
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0021fd0c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0021fd3c
                charge(ctx, 26);
                sb(v1, sp, 0xCF);
                a0 = addiu(s0, 4656);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x21FD48u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                lw(v1, s0, 18000);
                v0 = 3;
                v0 = subu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40400000;
                mtc1(v0, f0);
                div_s(f25, f1, f0);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f0, f0, f25);
                mul_s(f1, f0, f24);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0021fdbc
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0021fda4
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0021fdd4
                charge(ctx, 7);
                sb(v1, sp, 0xCF);
                a0 = addiu(s0, 4912);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x21FDE0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            } else {
                // 0x0021fcc0
                charge(ctx, 2);
            }
            goto L_002200e8;
        }
    L_0021fdf0:
        charge(ctx, 21);
        lw(v1, s0, 18000);
        v0 = 3;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        mul_s(f1, f0, f24);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0021fe5c
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0021fe44
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0021fe74
        charge(ctx, 22);
        sb(v1, sp, 0xCF);
        a0 = addiu(s0, 4656);
        a1 = addiu(sp, 0xCC);
        jal(ctx, 0x21FE80u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        lwc1(f0, s0, 18000);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f25, f1, f0);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f25);
        mul_s(f1, f0, f24);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0021fee4
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0021fecc
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0021fefc
        charge(ctx, 7);
        sb(v1, sp, 0xCF);
        a0 = addiu(s0, 4912);
        a1 = addiu(sp, 0xCC);
        jal(ctx, 0x21FF08u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    } else {
        // 0x0021faf0
        charge(ctx, 3);
        v0 = 8;
        if (v1 != v0) {
            // 0x0021fafc
            charge(ctx, 3);
            a1 = 2;
            if (v1 == a1) {
                goto L_0021fb1c;
            }
            // 0x0021fb08
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                goto L_0021fb1c;
            }
            // 0x0021fb14
            charge(ctx, 2);
            // 0x0021ff18
            charge(ctx, 4);
            lw(v1, s0, 17980);
            v0 = 4;
            if (v1 != v0) {
                // 0x0021ff28
                charge(ctx, 2);
                if (v1 == a2) {
                    goto L_0022001c;
                }
                // 0x0021ff30
                charge(ctx, 2);
                if (v1 == a1) {
                    goto L_0022001c;
                }
                // 0x0021ff38
                charge(ctx, 2);
                if (v1 == a0) {
                    goto L_0022001c;
                }
                // 0x0021ff40
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0021ff50
                    charge(ctx, 6);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f28);
                    if (cond(ctx)) {
                        // 0x0021ff80
                        charge(ctx, 6);
                        sub_s(f0, f28, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x0021ff68
                        charge(ctx, 6);
                        cvt_w_s(f0, f28);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x0021ff98
                    charge(ctx, 14);
                    sb(v1, sp, 0xCF);
                    a0 = addiu(s0, 4656);
                    a1 = addiu(sp, 0xCC);
                    jal(ctx, 0x21FFA4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                    mtc1(zero, f25);
                    mul_s(f1, f25, f24);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x0021ffe8
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x0021ffd0
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x00220000
                    charge(ctx, 7);
                    sb(v1, sp, 0xCF);
                    a0 = addiu(s0, 4912);
                    a1 = addiu(sp, 0xCC);
                    jal(ctx, 0x22000Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                } else {
                    // 0x0021ff48
                    charge(ctx, 2);
                }
                goto L_002200e8;
            }
        L_0022001c:
            charge(ctx, 9);
            mtc1(zero, f0);
            mul_s(f1, f0, f24);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00220058
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00220040
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00220070
            charge(ctx, 13);
            sb(v1, sp, 0xCF);
            a0 = addiu(s0, 4656);
            a1 = addiu(sp, 0xCC);
            jal(ctx, 0x22007Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            v0 = 0x3F800000;
            mtc1(v0, f25);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f28);
            if (cond(ctx)) {
                // 0x002200bc
                charge(ctx, 6);
                sub_s(f0, f28, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002200a4
                charge(ctx, 6);
                cvt_w_s(f0, f28);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x002200d4
            charge(ctx, 5);
            sb(v1, sp, 0xCF);
            a0 = addiu(s0, 4912);
            a1 = addiu(sp, 0xCC);
            jal(ctx, 0x2200E0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            goto L_002200e8;
        }
    L_0021fb1c:
        charge(ctx, 7);
        lw(v0, s0, 17972);
        v0 = sll(v0, 2);
        v0 = addu(v0, s0);
        lw(v0, v0, 4624);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0021fb60
            charge(ctx, 9);
            v0 = 0x40800000;
            mtc1(v0, f27);
            lwc1(f0, s0, 17996);
            cvt_s_w(f1, f0);
            v0 = 0x3F000000;
            mtc1(v0, f0);
            mul_s(f0, f0, f1);
            div_s(f25, f0, f27);
        } else {
            // 0x0021fb38
            charge(ctx, 10);
            v0 = 0x40800000;
            mtc1(v0, f27);
            lwc1(f0, s0, 17996);
            cvt_s_w(f0, f0);
            div_s(f25, f0, f27);
        }
        // 0x0021fb84
        charge(ctx, 11);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f25);
        mul_s(f1, f0, f24);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0021fbc8
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0021fbb0
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0021fbe0
        charge(ctx, 23);
        sb(v1, sp, 0xCF);
        a0 = addiu(s0, 4656);
        a1 = addiu(sp, 0xCC);
        jal(ctx, 0x21FBECu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        lw(v1, s0, 17996);
        v0 = 4;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f25, f0, f27);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f25);
        mul_s(f1, f0, f24);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0021fc54
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0021fc3c
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0021fc6c
        charge(ctx, 7);
        sb(v1, sp, 0xCF);
        a0 = addiu(s0, 4912);
        a1 = addiu(sp, 0xCC);
        jal(ctx, 0x21FC78u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    }
L_002200e8:
    charge(ctx, 8);
    a0 = s1;
    a1 = 27;
    jal(ctx, 0x2200F0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    lw(v1, s0, 17968);
    a1 = 3;
    if (v1 == a1) {
        // 0x00220110
        charge(ctx, 4);
        lw(a0, s0, 17980);
        v1 = 4;
        if (a0 != v1) {
            // 0x00220120
            charge(ctx, 2);
            if (a0 == a1) {
                goto L_00220190;
            }
            // 0x00220128
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_00220190;
            }
            // 0x00220134
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_00220190;
            }
            // 0x00220140
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00220150
                charge(ctx, 16);
                lw(v1, s0, 18000);
                v1 = subu(a1, v1);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -31760);  // 0x7CB0E0 = 0.785398f
                mul_s(f1, f0, f1);
                v1 = 0x40400000;
                mtc1(v1, f0);
                div_s(f26, f1, f0);
            } else {
                // 0x00220148
                charge(ctx, 2);
            }
            goto L_00220214;
        }
    L_00220190:
        charge(ctx, 13);
        lwc1(f0, s0, 18000);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -31760);  // 0x7CB0E0 = 0.785398f
        mul_s(f1, f0, f1);
        v1 = 0x40400000;
        mtc1(v1, f0);
        div_s(f26, f1, f0);
    } else {
        // 0x00220108
        charge(ctx, 2);
        // 0x002201c4
        charge(ctx, 4);
        lw(a0, s0, 17980);
        v1 = 4;
        if (a0 != v1) {
            // 0x002201d4
            charge(ctx, 2);
            if (a0 == a1) {
                goto L_00220210;
            }
            // 0x002201dc
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_00220210;
            }
            // 0x002201e8
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_00220210;
            }
            // 0x002201f4
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00220204
                charge(ctx, 3);
                mtc1(zero, f26);
            } else {
                // 0x002201fc
                charge(ctx, 2);
            }
            goto L_00220214;
        }
    L_00220210:
        charge(ctx, 1);
        lwc1(f26, gp, -31760);  // 0x7CB0E0 = 0.785398f
    }
L_00220214:
    charge(ctx, 30);
    v1 = 0x42B60000;
    mtc1(v1, f0);
    sub_s(f0, f23, f0);
    v1 = 0x3F000000;
    mtc1(v1, f1);
    sub_s(f2, f0, f1);
    v1 = 0x42B40000;
    mtc1(v1, f0);
    sub_s(f0, f22, f0);
    sub_s(f1, f0, f1);
    swc1(f2, sp, 0xA0);
    swc1(f1, sp, 0xA4);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    add_s(f0, f2, f0);
    swc1(f0, sp, 0xA8);
    swc1(f1, sp, 0xAC);
    swc1(f0, sp, 0xB0);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xB4);
    swc1(f2, sp, 0xB8);
    swc1(f0, sp, 0xBC);
    v1 = 0;
    for (;;) {  // while (v1 < 4)
        // 0x002202b4
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022028c
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        sub_s(f0, f0, f23);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        sub_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x002202c0
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < 4)
        // 0x00220338
        charge(ctx, 3);
        v0 = slti(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002202cc
        charge(ctx, 27);
        v0 = sll(s2, 3);
        v0 = addu(v0, sp);
        s4 = addiu(v0, 160);
        lwc1(f30, s4, 0);
        s3 = addiu(s4, 4);
        lwc1(f29, s4, 4);
        mov_s(f12, f26);
        jal(ctx, 0x2202E8u, gen::fn_sinf_0052e878);
        mov_s(f27, f0);
        mov_s(f12, f26);
        jal(ctx, 0x2202F8u, gen::fn_cosf_0052e6d8);
        mula_s(f30, f0);
        msub_s(f27, f29, f27);
        mov_s(f12, f26);
        jal(ctx, 0x22030Cu, gen::fn_sinf_0052e878);
        mov_s(f31, f0);
        mov_s(f12, f26);
        jal(ctx, 0x22031Cu, gen::fn_cosf_0052e6d8);
        mula_s(f29, f0);
        madd_s(f0, f30, f31);
        swc1(f27, s4, 0);
        swc1(f0, s3, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00220344
    charge(ctx, 3);
    v1 = 0;
    for (;;) {  // while (v1 < 4)
        // 0x00220378
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00220350
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        add_s(f0, f0, f23);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        add_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x00220384
    charge(ctx, 14);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0xA0);
    jal(ctx, 0x22038Cu, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
    v0 = 255;
    sb(v0, sp, 0xCC);
    sb(v0, sp, 0xCD);
    sb(v0, sp, 0xCE);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f28);
    if (cond(ctx)) {
        // 0x002203d4
        charge(ctx, 6);
        sub_s(f0, f28, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002203bc
        charge(ctx, 6);
        cvt_w_s(f0, f28);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002203ec
    charge(ctx, 39);
    sb(v1, sp, 0xCF);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0xCC);
    jal(ctx, 0x2203F8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s1;
    a1 = 28;
    jal(ctx, 0x220408u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x429E0000;
    mtc1(v1, f0);
    sub_s(f0, f23, f0);
    v1 = 0x3F000000;
    mtc1(v1, f1);
    sub_s(f2, f0, f1);
    v1 = 0x42AA0000;
    mtc1(v1, f0);
    sub_s(f0, f22, f0);
    sub_s(f1, f0, f1);
    swc1(f2, sp, 0xA0);
    swc1(f1, sp, 0xA4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    add_s(f0, f2, f0);
    swc1(f0, sp, 0xA8);
    swc1(f1, sp, 0xAC);
    swc1(f0, sp, 0xB0);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xB4);
    swc1(f2, sp, 0xB8);
    swc1(f0, sp, 0xBC);
    v1 = 0;
    for (;;) {  // while (v1 < 4)
        // 0x002204b0
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00220488
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        sub_s(f0, f0, f23);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        sub_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x002204bc
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < 4)
        // 0x00220534
        charge(ctx, 3);
        v0 = slti(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002204c8
        charge(ctx, 27);
        v0 = sll(s2, 3);
        v0 = addu(v0, sp);
        s4 = addiu(v0, 160);
        lwc1(f30, s4, 0);
        s3 = addiu(s4, 4);
        lwc1(f29, s4, 4);
        mov_s(f12, f26);
        jal(ctx, 0x2204E4u, gen::fn_sinf_0052e878);
        mov_s(f27, f0);
        mov_s(f12, f26);
        jal(ctx, 0x2204F4u, gen::fn_cosf_0052e6d8);
        mula_s(f30, f0);
        msub_s(f28, f29, f27);
        mov_s(f12, f26);
        jal(ctx, 0x220508u, gen::fn_sinf_0052e878);
        mov_s(f27, f0);
        mov_s(f12, f26);
        jal(ctx, 0x220518u, gen::fn_cosf_0052e6d8);
        mula_s(f29, f0);
        madd_s(f0, f30, f27);
        swc1(f28, s4, 0);
        swc1(f0, s3, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00220540
    charge(ctx, 3);
    v1 = 0;
    for (;;) {  // while (v1 < 4)
        // 0x00220574
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022054c
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        add_s(f0, f0, f23);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        add_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x00220580
    charge(ctx, 8);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0xA0);
    jal(ctx, 0x220588u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
    lw(v0, s0, 17968);
    a0 = 3;
    if (v0 == a0) {
        // 0x002205a8
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x002205b8
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_00220614;
            }
            // 0x002205c0
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_00220614;
            }
            // 0x002205cc
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_00220614;
            }
            // 0x002205d8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002205e8
                charge(ctx, 11);
                lwc1(f0, s0, 18000);
                cvt_s_w(f1, f0);
                v0 = 0x40400000;
                mtc1(v0, f0);
                div_s(f25, f1, f0);
            } else {
                // 0x002205e0
                charge(ctx, 2);
            }
            goto L_002206a4;
        }
    L_00220614:
        charge(ctx, 15);
        lw(v1, s0, 18000);
        v0 = 3;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f25, f1, f0);
    } else {
        // 0x002205a0
        charge(ctx, 2);
        // 0x00220650
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x00220660
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_002206a0;
            }
            // 0x00220668
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_002206a0;
            }
            // 0x00220674
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_002206a0;
            }
            // 0x00220680
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00220690
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f25);
            } else {
                // 0x00220688
                charge(ctx, 2);
            }
            goto L_002206a4;
        }
    L_002206a0:
        charge(ctx, 1);
        mtc1(zero, f25);
    }
L_002206a4:
    charge(ctx, 15);
    v0 = 255;
    sb(v0, sp, 0xCC);
    sb(v0, sp, 0xCD);
    sb(v0, sp, 0xCE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f25);
    mul_s(f1, f0, f24);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002206f8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002206e0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00220710
    charge(ctx, 13);
    sb(v1, sp, 0xCF);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0xCC);
    jal(ctx, 0x22071Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s1;
    a1 = 34;
    jal(ctx, 0x22072Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    lw(v1, s0, 17968);
    a1 = 3;
    if (v1 == a1) {
        // 0x0022074c
        charge(ctx, 4);
        lw(a0, s0, 17980);
        v1 = 4;
        if (a0 != v1) {
            // 0x0022075c
            charge(ctx, 2);
            if (a0 == a1) {
                goto L_002207c0;
            }
            // 0x00220764
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_002207c0;
            }
            // 0x00220770
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_002207c0;
            }
            // 0x0022077c
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0022078c
                charge(ctx, 13);
                lwc1(f0, s0, 18000);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -31756);  // 0x7CB0E4 = -1.5708f
                mul_s(f1, f0, f1);
                v1 = 0x40400000;
                mtc1(v1, f0);
                div_s(f1, f1, f0);
                lwc1(f0, gp, -31752);  // 0x7CB0E8 = -0.125664f
                add_s(f26, f0, f1);
            } else {
                // 0x00220784
                charge(ctx, 2);
            }
            goto L_00220808;
        }
    L_002207c0:
        charge(ctx, 17);
        lw(a0, s0, 18000);
        v1 = 3;
        v1 = subu(v1, a0);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -31756);  // 0x7CB0E4 = -1.5708f
        mul_s(f1, f0, f1);
        v1 = 0x40400000;
        mtc1(v1, f0);
        div_s(f1, f1, f0);
        lwc1(f0, gp, -31752);  // 0x7CB0E8 = -0.125664f
        add_s(f26, f0, f1);
    } else {
        // 0x00220744
        charge(ctx, 2);
        // 0x00220804
        charge(ctx, 1);
        lwc1(f26, gp, -31752);  // 0x7CB0E8 = -0.125664f
    }
L_00220808:
    charge(ctx, 30);
    v1 = 0x42480000;
    mtc1(v1, f0);
    sub_s(f0, f23, f0);
    v1 = 0x3F000000;
    mtc1(v1, f1);
    sub_s(f2, f0, f1);
    v1 = 0x41F00000;
    mtc1(v1, f0);
    sub_s(f0, f22, f0);
    sub_s(f1, f0, f1);
    swc1(f2, sp, 0xA0);
    swc1(f1, sp, 0xA4);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    add_s(f0, f2, f0);
    swc1(f0, sp, 0xA8);
    swc1(f1, sp, 0xAC);
    swc1(f0, sp, 0xB0);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xB4);
    swc1(f2, sp, 0xB8);
    swc1(f0, sp, 0xBC);
    v1 = 0;
    for (;;) {  // while (v1 < 4)
        // 0x002208a8
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00220880
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        sub_s(f0, f0, f23);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        sub_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x002208b4
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < 4)
        // 0x0022092c
        charge(ctx, 3);
        v0 = slti(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002208c0
        charge(ctx, 27);
        v0 = sll(s2, 3);
        v0 = addu(v0, sp);
        s4 = addiu(v0, 160);
        lwc1(f30, s4, 0);
        s3 = addiu(s4, 4);
        lwc1(f29, s4, 4);
        mov_s(f12, f26);
        jal(ctx, 0x2208DCu, gen::fn_sinf_0052e878);
        mov_s(f27, f0);
        mov_s(f12, f26);
        jal(ctx, 0x2208ECu, gen::fn_cosf_0052e6d8);
        mula_s(f30, f0);
        msub_s(f28, f29, f27);
        mov_s(f12, f26);
        jal(ctx, 0x220900u, gen::fn_sinf_0052e878);
        mov_s(f27, f0);
        mov_s(f12, f26);
        jal(ctx, 0x220910u, gen::fn_cosf_0052e6d8);
        mula_s(f29, f0);
        madd_s(f0, f30, f27);
        swc1(f28, s4, 0);
        swc1(f0, s3, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00220938
    charge(ctx, 3);
    v1 = 0;
    for (;;) {  // while (v1 < 4)
        // 0x0022096c
        charge(ctx, 3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00220944
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        add_s(f0, f0, f23);
        swc1(f0, v0, 0);
        lwc1(f0, v0, 4);
        add_s(f0, f0, f22);
        swc1(f0, v0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x00220978
    charge(ctx, 8);
    a0 = addiu(s0, 5168);
    a1 = addiu(sp, 0xA0);
    jal(ctx, 0x220980u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
    lw(v0, s0, 17968);
    a0 = 3;
    if (v0 == a0) {
        // 0x002209a0
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x002209b0
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_00220a18;
            }
            // 0x002209b8
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_00220a18;
            }
            // 0x002209c4
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_00220a18;
            }
            // 0x002209d0
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002209e0
                charge(ctx, 14);
                lw(v0, s0, 18000);
                v0 = subu(a0, v0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40400000;
                mtc1(v0, f0);
                div_s(f25, f1, f0);
            } else {
                // 0x002209d8
                charge(ctx, 2);
            }
            goto L_00220a98;
        }
    L_00220a18:
        charge(ctx, 11);
        lwc1(f0, s0, 18000);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f25, f1, f0);
    } else {
        // 0x00220998
        charge(ctx, 2);
        // 0x00220a44
        charge(ctx, 4);
        lw(v1, s0, 17980);
        v0 = 4;
        if (v1 != v0) {
            // 0x00220a54
            charge(ctx, 2);
            if (v1 == a0) {
                goto L_00220a90;
            }
            // 0x00220a5c
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_00220a90;
            }
            // 0x00220a68
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_00220a90;
            }
            // 0x00220a74
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00220a84
                charge(ctx, 3);
                mtc1(zero, f25);
            } else {
                // 0x00220a7c
                charge(ctx, 2);
            }
            goto L_00220a98;
        }
    L_00220a90:
        charge(ctx, 2);
        v0 = 0x3F800000;
        mtc1(v0, f25);
    }
L_00220a98:
    charge(ctx, 15);
    v0 = 255;
    sb(v0, sp, 0xCC);
    sb(v0, sp, 0xCD);
    sb(v0, sp, 0xCE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f25);
    mul_s(f1, f0, f24);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00220aec
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00220ad4
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00220b04
    charge(ctx, 12);
    sb(v1, sp, 0xCF);
    a0 = addiu(s0, 5168);
    a1 = addiu(sp, 0xCC);
    jal(ctx, 0x220B10u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s3 = 0;
    v0 = 0x42640000;
    mtc1(v0, f0);
    neg_s(f28, f0);
    for (;;) {  // while (s3 < 7)
        // 0x00220df4
        charge(ctx, 3);
        v0 = slti(s3, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00220b34
        charge(ctx, 4);
        lw(v1, s0, 17968);
        v0 = 2;
        if (v1 == v0) {
            // 0x00220bc0
            charge(ctx, 26);
            lwc1(f0, s0, 17996);
            cvt_s_w(f1, f0);
            v0 = 0x40800000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            lwc1(f0, s0, 17972);
            cvt_s_w(f1, f0);
            mtc1(s3, f0);
            cvt_s_w(f0, f0);
            sub_s(f1, f0, f1);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            add_s(f1, f2, f0);
            v0 = 0x40E00000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
        } else {
            // 0x00220b44
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x00220b58
                charge(ctx, 26);
                lwc1(f0, s0, 17996);
                cvt_s_w(f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                div_s(f2, f1, f0);
                lwc1(f0, s0, 17972);
                cvt_s_w(f1, f0);
                mtc1(s3, f0);
                cvt_s_w(f0, f0);
                sub_s(f1, f0, f1);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                sub_s(f1, f0, f2);
                v0 = 0x40E00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
            } else {
                // 0x00220b50
                charge(ctx, 2);
                // 0x00220c28
                charge(ctx, 10);
                lwc1(f0, s0, 17972);
                cvt_s_w(f1, f0);
                mtc1(s3, f0);
                cvt_s_w(f0, f0);
                sub_s(f1, f0, f1);
                v0 = 0x40E00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
            }
        }
        // 0x00220c50
        charge(ctx, 20);
        v0 = 0x40000000;
        mtc1(v0, f0);
        mul_s(f1, f0, f1);
        lwc1(f0, gp, -32184);  // 0x7CAF38 = 3.14159f
        mul_s(f26, f0, f1);
        mov_s(f12, f26);
        jal(ctx, 0x220C6Cu, gen::fn_cosf_0052e6d8);
        mul_s(f27, f28, f0);
        mov_s(f12, f26);
        jal(ctx, 0x220C7Cu, gen::fn_sinf_0052e878);
        mul_s(f26, f28, f0);
        v0 = sll(s3, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, 4624);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00220cb8
            charge(ctx, 4);
            a0 = s1;
            a1 = 65;
            jal(ctx, 0x220CC0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        } else {
            // 0x00220ca0
            charge(ctx, 6);
            a0 = s1;
            a1 = 17;
            jal(ctx, 0x220CA8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        }
        // 0x00220cc8
        charge(ctx, 4);
        lw(a0, v0, kSpW);
        v1 = sra(a0, 1);
        if (i64(a0) < 0) {
            // 0x00220cd8
            charge(ctx, 2);
            v1 = addiu(a0, 1);
            v1 = sra(v1, 1);
        }
        // 0x00220ce0
        charge(ctx, 8);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        sub_s(f1, f27, f0);
        lw(a0, v0, kSpH);
        v1 = sra(a0, 1);
        if (i64(a0) < 0) {
            // 0x00220d00
            charge(ctx, 2);
            v1 = addiu(a0, 1);
            v1 = sra(v1, 1);
        }
        // 0x00220d08
        charge(ctx, 28);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        sub_s(f0, f26, f0);
        add_s(f1, f1, f21);
        add_s(f0, f0, f20);
        swc1(f1, sp, 0x90);
        swc1(f0, sp, 0x94);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x98);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x9C);
        v0 = sll(s3, 8);
        s2 = addu(s0, v0);
        a0 = addiu(s2, 1040);
        a1 = addiu(sp, 0x90);
        jal(ctx, 0x220D50u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        a1 = addiu(s3, 20);
        a0 = s1;
        jal(ctx, 0x220D60u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        lw(a0, v0, kSpW);
        v1 = sra(a0, 1);
        if (i64(a0) < 0) {
            // 0x00220d78
            charge(ctx, 2);
            v1 = addiu(a0, 1);
            v1 = sra(v1, 1);
        }
        // 0x00220d80
        charge(ctx, 8);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        sub_s(f1, f27, f0);
        lw(a0, v0, kSpH);
        v1 = sra(a0, 1);
        if (i64(a0) < 0) {
            // 0x00220da0
            charge(ctx, 2);
            v1 = addiu(a0, 1);
            v1 = sra(v1, 1);
        }
        // 0x00220da8
        charge(ctx, 19);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        sub_s(f0, f26, f0);
        add_s(f1, f1, f21);
        add_s(f0, f0, f20);
        swc1(f1, sp, 0x90);
        swc1(f0, sp, 0x94);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x98);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x9C);
        a0 = addiu(s2, 2832);
        a1 = addiu(sp, 0x90);
        jal(ctx, 0x220DE8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s3 = addiu(s3, 1);
    }
    // 0x00220e00
    charge(ctx, 4);
    lw(v0, s0, 17980);
    a2 = 4;
    if (v0 != a2) {
        // 0x00220e10
        charge(ctx, 3);
        a1 = 3;
        if (v0 == a1) {
            goto L_00220eb8;
        }
        // 0x00220e1c
        charge(ctx, 3);
        a0 = 2;
        if (v0 == a0) {
            goto L_00220eb8;
        }
        // 0x00220e28
        charge(ctx, 3);
        v1 = 1;
        if (v0 == v1) {
            goto L_00220eb8;
        }
        // 0x00220e34
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x00220e44
            charge(ctx, 3);
            lw(v0, s0, 17984);
            if (v0 != a0) {
                // 0x00220e50
                charge(ctx, 2);
                if (v0 == v1) {
                    goto L_00220e68;
                }
                // 0x00220e58
                charge(ctx, 2);
                if (v0 == a2) {
                    goto L_00220e68;
                }
                // 0x00220e60
                charge(ctx, 2);
                if (v0 == a1) {
                    goto L_00220e68;
                }
            L_00220ea8:
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f25);
                goto L_00220ee0;
            }
        L_00220e68:
            charge(ctx, 4);
            lw(v1, s0, 18000);
            v0 = 3;
            if (v1 == v0) {
                goto L_00220ea8;
            }
            // 0x00220e78
            charge(ctx, 12);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f25, f1, f0);
        } else {
            // 0x00220e3c
            charge(ctx, 2);
        }
        goto L_00220ee0;
    }
L_00220eb8:
    charge(ctx, 10);
    lw(v1, s0, 18000);
    v0 = 3;
    v0 = subu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x40400000;
    mtc1(v0, f0);
    div_s(f25, f1, f0);
L_00220ee0:
    charge(ctx, 48);
    a0 = s1;
    a1 = 14;
    jal(ctx, 0x220EE8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x42FC0000;
    mtc1(v1, f0);
    add_s(f1, f0, f23);
    v1 = 0x42CE0000;
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x90);
    v1 = 0x43B00000;
    mtc1(v1, f0);
    add_s(f1, f0, f22);
    v1 = 361;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x94);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x98);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x9C);
    a0 = addiu(s0, 784);
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x220F5Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0xCC);
    sb(v0, sp, 0xCD);
    sb(v0, sp, 0xCE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f20, f0, f25);
    mul_s(f1, f20, f24);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00220fb8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00220fa0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00220fd0
    charge(ctx, 8);
    sb(v1, sp, 0xCF);
    a0 = addiu(s0, 784);
    a1 = addiu(sp, 0xCC);
    jal(ctx, 0x220FDCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s2 = 0;
    for (;;) {  // while (s2 < 7)
        // 0x00221810
        charge(ctx, 3);
        v1 = slti(s2, 7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00220ff0
        charge(ctx, 4);
        lw(v1, s0, 17968);
        v0 = 2;
        if (v1 == v0) {
            // 0x0022107c
            charge(ctx, 26);
            lwc1(f0, s0, 17996);
            cvt_s_w(f1, f0);
            v0 = 0x40800000;
            mtc1(v0, f0);
            div_s(f22, f1, f0);
            lwc1(f0, s0, 17972);
            cvt_s_w(f1, f0);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            sub_s(f1, f0, f1);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            add_s(f1, f22, f0);
            v0 = 0x40E00000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
        } else {
            // 0x00221000
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x00221014
                charge(ctx, 26);
                lwc1(f0, s0, 17996);
                cvt_s_w(f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                div_s(f22, f1, f0);
                lwc1(f0, s0, 17972);
                cvt_s_w(f1, f0);
                mtc1(s2, f0);
                cvt_s_w(f0, f0);
                sub_s(f1, f0, f1);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                sub_s(f1, f0, f22);
                v0 = 0x40E00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
            } else {
                // 0x0022100c
                charge(ctx, 2);
                // 0x002210e4
                charge(ctx, 12);
                lwc1(f0, s0, 17972);
                cvt_s_w(f1, f0);
                mtc1(s2, f0);
                cvt_s_w(f0, f0);
                sub_s(f1, f0, f1);
                v0 = 0x40E00000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f22);
            }
        }
        // 0x00221114
        charge(ctx, 34);
        v0 = 0x40000000;
        mtc1(v0, f0);
        mul_s(f1, f0, f1);
        lwc1(f0, gp, -32184);  // 0x7CAF38 = 3.14159f
        mul_s(f12, f0, f1);
        jal(ctx, 0x22112Cu, gen::fn_cosf_0052e6d8);
        mul_s(f1, f28, f0);
        v0 = 0x42E40000;
        mtc1(v0, f2);
        v0 = 0x42640000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        sub_s(f1, f2, f0);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        div_s(f1, f0, f2);
        v0 = 0x42820000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x42C80000;
        mtc1(v0, f0);
        div_s(f21, f1, f0);
        lw(v0, s0, 17972);
        if (s2 != v0) {
            // 0x0022143c
            charge(ctx, 3);
            lw(v0, s0, 17976);
            if (s2 != v0) {
                // 0x002216d0
                charge(ctx, 6);
                v0 = sll(s2, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, 4624);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00221710
                    charge(ctx, 7);
                    v0 = 115;
                    sb(v0, sp, 0xCC);
                    v0 = 116;
                    sb(v0, sp, 0xCD);
                    sb(v0, sp, 0xCE);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                } else {
                    // 0x002216e8
                    charge(ctx, 10);
                    v0 = 60;
                    sb(v0, sp, 0xCC);
                    v0 = 94;
                    sb(v0, sp, 0xCD);
                    v0 = 100;
                    sb(v0, sp, 0xCE);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                }
                // 0x0022172c
                charge(ctx, 8);
                mul_s(f0, f20, f0);
                mul_s(f1, f24, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00221764
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x0022174c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022177c
                charge(ctx, 19);
                sb(v1, sp, 0xCF);
                v0 = sll(s2, 8);
                s1 = addu(s0, v0);
                a0 = addiu(s1, 2832);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x221790u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                v0 = 255;
                sb(v0, sp, 0xCC);
                sb(v0, sp, 0xCD);
                sb(v0, sp, 0xCE);
                mul_s(f0, f20, f21);
                mul_s(f1, f24, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002217e0
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002217c8
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002217f8
                charge(ctx, 5);
                sb(v1, sp, 0xCF);
                a0 = addiu(s1, 1040);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x221804u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            } else {
                // 0x00221448
                charge(ctx, 6);
                v0 = sll(s2, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, 4624);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x002215b4
                    charge(ctx, 7);
                    v0 = 115;
                    sb(v0, sp, 0xCC);
                    v0 = 116;
                    sb(v0, sp, 0xCD);
                    sb(v0, sp, 0xCE);
                    v0 = 0x3F800000;
                    mtc1(v0, f1);
                } else {
                    // 0x00221460
                    charge(ctx, 14);
                    v0 = lui(0xC34C);
                    mtc1(v0, f2);
                    v0 = 0x437F0000;
                    mtc1(v0, f1);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f1, f22, f2);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x002214b0
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x00221498
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x002214c8
                    charge(ctx, 15);
                    sb(v1, sp, 0xCC);
                    v0 = lui(0xC214);
                    mtc1(v0, f2);
                    v0 = 0x42F00000;
                    mtc1(v0, f1);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f1, f22, f2);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x0022151c
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x00221504
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x00221534
                    charge(ctx, 15);
                    sb(v1, sp, 0xCD);
                    v0 = lui(0xC2AA);
                    mtc1(v0, f2);
                    v0 = 0x432F0000;
                    mtc1(v0, f1);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    madd_s(f1, f22, f2);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x00221588
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x00221570
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x002215a0
                    charge(ctx, 5);
                    sb(v1, sp, 0xCE);
                    v0 = 0x3F800000;
                    mtc1(v0, f1);
                }
                // 0x002215d0
                charge(ctx, 13);
                v0 = 0x437F0000;
                mtc1(v0, f0);
                mul_s(f0, f0, f21);
                mul_s(f0, f0, f25);
                mul_s(f0, f1, f0);
                mul_s(f1, f24, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022161c
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00221604
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00221634
                charge(ctx, 20);
                sb(v1, sp, 0xCF);
                v0 = sll(s2, 8);
                s1 = addu(s0, v0);
                a0 = addiu(s1, 2832);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x221648u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                v0 = 255;
                sb(v0, sp, 0xCC);
                sb(v0, sp, 0xCD);
                sb(v0, sp, 0xCE);
                mul_s(f0, f20, f21);
                mul_s(f0, f22, f0);
                mul_s(f1, f24, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x0022169c
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00221684
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002216b4
                charge(ctx, 7);
                sb(v1, sp, 0xCF);
                a0 = addiu(s1, 1040);
                a1 = addiu(sp, 0xCC);
                jal(ctx, 0x2216C0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            }
        } else {
            // 0x0022119c
            charge(ctx, 6);
            v0 = sll(s2, 2);
            v0 = addu(s0, v0);
            lw(v0, v0, 4624);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x00221318
                charge(ctx, 7);
                v0 = 115;
                sb(v0, sp, 0xCC);
                v0 = 116;
                sb(v0, sp, 0xCD);
                sb(v0, sp, 0xCE);
                v0 = 0x3F800000;
                mtc1(v0, f1);
            } else {
                // 0x002211b4
                charge(ctx, 18);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f3, f0, f22);
                v0 = lui(0xC34C);
                mtc1(v0, f2);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f3, f2);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00221214
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002211fc
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x0022122c
                charge(ctx, 15);
                sb(v1, sp, 0xCC);
                v0 = lui(0xC214);
                mtc1(v0, f2);
                v0 = 0x42F00000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f3, f2);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00221280
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x00221268
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00221298
                charge(ctx, 15);
                sb(v1, sp, 0xCD);
                v0 = lui(0xC2AA);
                mtc1(v0, f2);
                v0 = 0x432F0000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                madd_s(f1, f3, f2);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002212ec
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002212d4
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00221304
                charge(ctx, 5);
                sb(v1, sp, 0xCE);
                v0 = 0x3F800000;
                mtc1(v0, f1);
            }
            // 0x00221334
            charge(ctx, 12);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f21, f0, f21);
            mul_s(f0, f21, f1);
            mul_s(f1, f24, f0);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0022137c
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x00221364
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00221394
            charge(ctx, 23);
            sb(v1, sp, 0xCF);
            v0 = sll(s2, 8);
            s1 = addu(s0, v0);
            a0 = addiu(s1, 2832);
            a1 = addiu(sp, 0xCC);
            jal(ctx, 0x2213A8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            v0 = 255;
            sb(v0, sp, 0xCC);
            sb(v0, sp, 0xCD);
            sb(v0, sp, 0xCE);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f0, f22);
            mul_s(f0, f21, f0);
            mul_s(f1, f24, f0);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x00221408
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x002213f0
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x00221420
            charge(ctx, 7);
            sb(v1, sp, 0xCF);
            a0 = addiu(s1, 1040);
            a1 = addiu(sp, 0xCC);
            jal(ctx, 0x22142Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        }
        // 0x0022180c
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0022181c
    charge(ctx, 3);
    lw(a0, s0, 17980);
    if (a0 == 0) {
        // 0x00221870
        charge(ctx, 4);
        lw(a0, s0, 17984);
        v1 = 2;
        if (a0 != v1) {
            // 0x00221880
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_002218a4;
            }
            // 0x0022188c
            charge(ctx, 3);
            v1 = 4;
            if (a0 == v1) {
                goto L_002218a4;
            }
            // 0x00221898
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                goto L_002218a4;
            }
            goto L_002218bc;
        }
    L_002218a4:
        charge(ctx, 4);
        lw(a0, s0, 18000);
        v1 = 3;
        if (a0 != v1) {
            // 0x002218b4
            charge(ctx, 2);
            jal(ctx, 0x2218B4u, gen::fn_sub_2265D0_002265d0);
        }
    } else {
        // 0x00221828
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x00221834
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                goto L_00221860;
            }
            // 0x00221840
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_00221860;
            }
            // 0x0022184c
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_00221860;
            }
            // 0x00221858
            charge(ctx, 2);
            goto L_002218bc;
        }
    L_00221860:
        charge(ctx, 4);
        jal(ctx, 0x221860u, gen::fn_sub_2265D0_002265d0);
    }
L_002218bc:
    charge(ctx, 4);
    lw(a0, s0, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x002218d4
        charge(ctx, 3);
        lw(a0, s0, 17988);
        if (a0 == 0) {
            // 0x00221904
            charge(ctx, 4);
            lw(a0, s0, 17992);
            v1 = 1;
            if (a0 == v1) {
                // 0x00221914
                charge(ctx, 4);
                lw(a0, s0, 18008);
                v1 = 6;
                if (a0 != v1) {
                    // 0x00221924
                    charge(ctx, 2);
                    jal(ctx, 0x221924u, gen::fn_sub_227F30_00227f30);
                }
            }
        } else {
            // 0x002218e0
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x002218f4
                charge(ctx, 4);
                jal(ctx, 0x2218F4u, gen::fn_sub_227F30_00227f30);
            } else {
                // 0x002218ec
                charge(ctx, 2);
            }
        }
    } else {
        // 0x002218cc
        charge(ctx, 2);
    }
    // 0x0022192c
    charge(ctx, 4);
    lw(a0, s0, 17980);
    v1 = 1;
    if (a0 != v1) {
        // 0x0022193c
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            goto L_00221950;
        }
        // 0x00221948
        charge(ctx, 2);
        goto L_00221984;
    }
L_00221950:
    charge(ctx, 4);
    lw(a0, s0, 17988);
    v1 = 4;
    if (a0 != v1) {
        // 0x00221960
        charge(ctx, 3);
        v1 = 3;
        if (a0 == v1) {
            goto L_0022197c;
        }
        // 0x0022196c
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_0022197c;
        }
        // 0x00221974
        charge(ctx, 2);
        goto L_00221984;
    }
L_0022197c:
    charge(ctx, 2);
    jal(ctx, 0x22197Cu, gen::fn_sub_22C2D0_0022c2d0);
L_00221984:
    charge(ctx, 4);
    lw(a1, s0, 17980);
    a0 = 2;
    if (a1 != a0) {
        // 0x00221994
        charge(ctx, 2);
        if (a1 == 0) {
            // 0x0022199c
            charge(ctx, 3);
            lw(v1, s0, 17984);
            if (v1 != a0) {
                goto L_002219c8;
            }
            // 0x002219a8
            charge(ctx, 4);
            lw(v1, s0, 18000);
            at = slti(v1, 3);
            if (at == 0) {
                goto L_002219c8;
            }
            goto L_002219b8;
        }
    L_002219c8:
        charge(ctx, 3);
        a0 = 1;
        if (a1 != a0) {
            // 0x002219d4
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x002219dc
                charge(ctx, 3);
                lw(v1, s0, 17984);
                if (v1 != a0) {
                    goto L_00221a08;
                }
                // 0x002219e8
                charge(ctx, 4);
                lw(v1, s0, 18000);
                at = slti(v1, 3);
                if (at == 0) {
                    goto L_00221a08;
                }
                goto L_002219f8;
            }
        L_00221a08:
            charge(ctx, 3);
            a0 = 4;
            if (a1 != a0) {
                // 0x00221a14
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00221a1c
                    charge(ctx, 3);
                    lw(v1, s0, 17984);
                    if (v1 != a0) {
                        goto L_00221a48;
                    }
                    // 0x00221a28
                    charge(ctx, 4);
                    lw(v1, s0, 18000);
                    at = slti(v1, 3);
                    if (at == 0) {
                        goto L_00221a48;
                    }
                    goto L_00221a38;
                }
            L_00221a48:
                charge(ctx, 3);
                a0 = 3;
                if (a1 != a0) {
                    // 0x00221a54
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x00221a5c
                        charge(ctx, 3);
                        lw(v1, s0, 17984);
                        if (v1 == a0) {
                            // 0x00221a68
                            charge(ctx, 4);
                            lw(v1, s0, 18000);
                            at = slti(v1, 3);
                            if (at != 0) {
                                goto L_00221a78;
                            }
                        }
                    }
                    goto L_00221a80;
                }
            L_00221a78:
                charge(ctx, 2);
                jal(ctx, 0x221A78u, gen::fn_sub_223290_00223290);
                goto L_00221a80;
            }
        L_00221a38:
            charge(ctx, 4);
            jal(ctx, 0x221A38u, gen::fn_sub_224940_00224940);
            goto L_00221a80;
        }
    L_002219f8:
        charge(ctx, 4);
        jal(ctx, 0x2219F8u, gen::fn_sub_22A2B0_0022a2b0);
        goto L_00221a80;
    }
L_002219b8:
    charge(ctx, 4);
    jal(ctx, 0x2219B8u, gen::fn_sub_228E40_00228e40);
L_00221a80:
    charge(ctx, 4);
    lw(a0, s0, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x00221a98
        charge(ctx, 4);
        lw(v1, s0, 17988);
        a1 = 2;
        if (v1 != a1) {
            // 0x00221aa8
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                goto L_00221af8;
            }
            // 0x00221ab4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00221ac4
                charge(ctx, 3);
                lw(v1, s0, 17992);
                if (v1 != a0) {
                    // 0x00221ad0
                    charge(ctx, 2);
                    if (v1 == a1) {
                        goto L_00221ad8;
                    }
                    // 0x00221b00 (the shared epilogue, written out on this path)
                    charge(ctx, 21);
                    ld(ra, sp, 0x80);
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
                    sp = addiu(sp, 0xD0);
                    return;
                }
            L_00221ad8:
                charge(ctx, 4);
                lw(v1, s0, 18008);
                at = slti(v1, 6);
                if (at != 0) {
                    // 0x00221ae8
                    charge(ctx, 4);
                    jal(ctx, 0x221AE8u, gen::fn_sub_2257F0_002257f0);
                }
            } else {
                // 0x00221abc
                charge(ctx, 2);
            }
            // 0x00221b00 (the shared epilogue, written out on this path)
            charge(ctx, 21);
            ld(ra, sp, 0x80);
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
            sp = addiu(sp, 0xD0);
            return;
        }
    L_00221af8:
        charge(ctx, 2);
        jal(ctx, 0x221AF8u, gen::fn_sub_2257F0_002257f0);
    } else {
        // 0x00221a90
        charge(ctx, 2);
    }
    // 0x00221b00 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    ld(ra, sp, 0x80);
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
    sp = addiu(sp, 0xD0);
}

// 0x00221B60 sub_221B60 -- 2948 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_Draw] draws what sub_21F410 laid out: the help line (sub_22BCF0), the base and command quads
// (two Im2D triangles each), the frame (sub_227800), the open sub-list (sub_22AE80 / sub_229B40 / sub_224150 /
// sub_225040 and the steps sub_2289B0 / sub_226040), the detail (sub_22C5A0).
void sub_221B60(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00221b60
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00221b90
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x221B9Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00221ba4
    charge(ctx, 9);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x221BACu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    lw(v0, s2, kBcmFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00221bc8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 1147;
        jal(ctx, 0x221BD4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 1147): `jr $ra` in retail, execution goes on
    }
    // 0x00221bdc
    charge(ctx, 189);
    s4 = 0;
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221BF4u, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221C08u, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221C1Cu, v0.u());
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221C30u, v0.u());
    a0 = 14;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221C44u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221C58u, v0.u());
    jal(ctx, 0x221C60u, gen::fn_sub_22BCF0_0022bcf0);
    a0 = s5;
    a1 = 16;
    jal(ctx, 0x221C70u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x221C7Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221C90u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x221CA4u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x221CB4u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, kBcmQuadBase);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221CDCu, v0.u());
    a0 = addiu(s2, kBcmQuadBase);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221CFCu, v0.u());
    a0 = s5;
    a1 = 27;
    jal(ctx, 0x221D0Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x221D18u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221D2Cu, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x221D40u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x221D50u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = addiu(s2, kBcmQuadA);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221D70u, v0.u());
    a0 = addiu(s2, kBcmQuadA);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221D90u, v0.u());
    a0 = s5;
    a1 = 28;
    jal(ctx, 0x221DA0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x221DACu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221DC0u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x221DD4u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x221DE4u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = addiu(s2, kBcmQuadB);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221E04u, v0.u());
    a0 = addiu(s2, kBcmQuadB);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221E24u, v0.u());
    a0 = s5;
    a1 = 34;
    jal(ctx, 0x221E34u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x221E40u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x221E54u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x221E68u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x221E78u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = addiu(s2, kBcmQuadD);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221E98u, v0.u());
    a0 = addiu(s2, kBcmQuadD);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x221EB8u, v0.u());
    lw(v0, s2, kBcmState);
    a2 = 3;
    if (v0 == a2) {
        // 0x00221f38
        charge(ctx, 15);
        a0 = s5;
        lw(a1, s2, kBcmCur);
        jal(ctx, 0x221F40u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s3 = v0;
        lw(v0, s2, kBcmCur);
        a1 = addiu(v0, 7);
        a0 = s5;
        jal(ctx, 0x221F58u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s6 = v0;
        lw(a0, s2, kBcmSub);
        v0 = 4;
        if (a0 != v0) {
            // 0x00221f74
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                goto L_00221fc4;
            }
            // 0x00221f80
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                goto L_00221fc4;
            }
            // 0x00221f8c
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                goto L_00221fc4;
            }
            // 0x00221f98
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00221fa8
                charge(ctx, 4);
                s4 = s4 | 0x1;
                lw(v0, s2, kBcmSubTimer);
                if (v0 != v1) {
                    // 0x00221fb8
                    charge(ctx, 3);
                    s4 = s4 | 0x2;
                }
            } else {
                // 0x00221fa0
                charge(ctx, 2);
            }
            goto L_00222058;
        }
    L_00221fc4:
        charge(ctx, 5);
        s4 = s4 | 0x2;
        lw(v1, s2, 18000);
        v0 = 3;
        if (v1 != v0) {
            // 0x00221fd8
            charge(ctx, 3);
            s4 = s4 | 0x1;
        }
    } else {
        // 0x00221ed0
        charge(ctx, 3);
        a1 = 2;
        if (v0 != a1) {
            // 0x00221edc
            charge(ctx, 3);
            a0 = 1;
            if (v0 == a0) {
                goto L_00221ef0;
            }
            // 0x00221ee8
            charge(ctx, 2);
            // 0x00221fe4
            charge(ctx, 4);
            lw(v1, s2, kBcmSub);
            v0 = 4;
            if (v1 != v0) {
                // 0x00221ff4
                charge(ctx, 2);
                if (v1 == a2) {
                    goto L_0022203c;
                }
                // 0x00221ffc
                charge(ctx, 2);
                if (v1 == a1) {
                    goto L_0022203c;
                }
                // 0x00222004
                charge(ctx, 2);
                if (v1 == a0) {
                    goto L_0022203c;
                }
                // 0x0022200c
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0022201c
                    charge(ctx, 8);
                    a0 = s5;
                    lw(a1, s2, kBcmCur);
                    jal(ctx, 0x222024u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s3 = v0;
                    s4 = s4 | 0x1;
                } else {
                    // 0x00222014
                    charge(ctx, 2);
                }
                goto L_00222058;
            }
        L_0022203c:
            charge(ctx, 7);
            lw(v0, s2, 17972);
            a1 = addiu(v0, 7);
            a0 = s5;
            jal(ctx, 0x222048u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s6 = v0;
            s4 = s4 | 0x2;
            goto L_00222058;
        }
    L_00221ef0:
        charge(ctx, 15);
        a0 = s5;
        lw(a1, s2, 17972);
        jal(ctx, 0x221EF8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s3 = v0;
        a0 = s5;
        lw(a1, s2, 17976);
        jal(ctx, 0x221F0Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s6 = v0;
        s4 = s4 | 0x1;
        lw(v1, s2, 17996);
        v0 = 4;
        if (v1 != v0) {
            // 0x00221f2c
            charge(ctx, 3);
            s4 = s4 | 0x2;
        }
    }
L_00222058:
    charge(ctx, 3);
    v0 = s4 & 0x1;
    if (v0 != 0) {
        // 0x00222064
        charge(ctx, 35);
        a0 = s3;
        jal(ctx, 0x222068u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x22207Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x222090u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2220A0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 4656);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2220C8u, v0.u());
        a0 = addiu(s2, 4656);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2220E8u, v0.u());
    }
    // 0x002220f0
    charge(ctx, 3);
    v0 = s4 & 0x2;
    if (v0 != 0) {
        // 0x002220fc
        charge(ctx, 35);
        a0 = s6;
        jal(ctx, 0x222100u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x222114u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x222128u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x222138u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 4912);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x222160u, v0.u());
        a0 = addiu(s2, 4912);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x222180u, v0.u());
    }
    // 0x00222188
    charge(ctx, 5);
    lw(v0, s2, 0);
    v0 = nor(v0, 0);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x0022219c
        charge(ctx, 39);
        a0 = s5;
        a1 = 14;
        jal(ctx, 0x2221A4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2221B0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x2221C4u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x2221D8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2221E8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x222210u, v0.u());
        a0 = addiu(s2, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x222230u, v0.u());
    }
    // 0x00222238
    charge(ctx, 12);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x222244u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x222254u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s4 = 0;
    for (;;) {  // while (s4 < 7)
        // 0x00222320
        charge(ctx, 3);
        v1 = slti(s4, 7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00222268
        charge(ctx, 6);
        v0 = sll(s4, 2);
        v0 = addu(s2, v0);
        lw(v0, v0, 4624);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00222298
            charge(ctx, 4);
            a0 = s5;
            a1 = 65;
            jal(ctx, 0x2222A0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        } else {
            // 0x00222280
            charge(ctx, 6);
            a0 = s5;
            a1 = 17;
            jal(ctx, 0x222288u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        }
        // 0x002222a8
        charge(ctx, 30);
        a0 = v0;
        jal(ctx, 0x2222ACu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x2222C0u, v0.u());
        v0 = sll(s4, 8);
        v0 = addu(s2, v0);
        s3 = addiu(v0, 1040);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = s3;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2222F4u, v0.u());
        a0 = s3;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x222314u, v0.u());
        s4 = addiu(s4, 1);
    }
    // 0x0022232c
    charge(ctx, 3);
    s3 = 0;
    for (;;) {  // while (s3 < 7)
        // 0x002223e4
        charge(ctx, 3);
        v1 = slti(s3, 7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00222338
        charge(ctx, 43);
        a1 = addiu(s3, 20);
        a0 = s5;
        jal(ctx, 0x222340u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x22234Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x222360u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x222374u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x222384u, gen::fn_RpSkyRenderStateSet_004d7f60);
        v0 = sll(s3, 8);
        v0 = addu(s2, v0);
        s4 = addiu(v0, 2832);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2223B8u, v0.u());
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2223D8u, v0.u());
        s3 = addiu(s3, 1);
    }
    // 0x002223f0
    charge(ctx, 3);
    lw(a0, s2, 17980);
    if (a0 == 0) {
        // 0x0022242c
        charge(ctx, 4);
        lw(a0, s2, 17984);
        v1 = 4;
        if (a0 != v1) {
            // 0x0022243c
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                goto L_00222448;
            }
            goto L_00222460;
        }
    L_00222448:
        charge(ctx, 4);
        lw(a0, s2, 18000);
        v1 = 3;
        if (a0 != v1) {
            // 0x00222458
            charge(ctx, 2);
            jal(ctx, 0x222458u, gen::fn_sub_227800_00227800);
        }
    } else {
        // 0x002223fc
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x00222408
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                goto L_0022241c;
            }
            // 0x00222414
            charge(ctx, 2);
            goto L_00222460;
        }
    L_0022241c:
        charge(ctx, 4);
        jal(ctx, 0x22241Cu, gen::fn_sub_227800_00227800);
    }
L_00222460:
    charge(ctx, 4);
    lw(a1, s2, 17980);
    a0 = 2;
    if (a1 != a0) {
        // 0x00222470
        charge(ctx, 2);
        if (a1 == 0) {
            // 0x00222478
            charge(ctx, 3);
            lw(v1, s2, 17984);
            if (v1 != a0) {
                goto L_002224dc;
            }
            // 0x00222484
            charge(ctx, 4);
            lw(v1, s2, 18000);
            at = slti(v1, 3);
            if (at == 0) {
                goto L_002224dc;
            }
            goto L_00222494;
        }
    L_002224dc:
        charge(ctx, 3);
        a0 = 1;
        if (a1 != a0) {
            // 0x002224e8
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x002224f0
                charge(ctx, 3);
                lw(v1, s2, 17984);
                if (v1 != a0) {
                    goto L_00222554;
                }
                // 0x002224fc
                charge(ctx, 4);
                lw(v1, s2, 18000);
                at = slti(v1, 3);
                if (at == 0) {
                    goto L_00222554;
                }
                goto L_0022250c;
            }
        L_00222554:
            charge(ctx, 3);
            a0 = 4;
            if (a1 != a0) {
                // 0x00222560
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00222568
                    charge(ctx, 3);
                    lw(v1, s2, 17984);
                    if (v1 == a0) {
                        // 0x00222574
                        charge(ctx, 4);
                        lw(v1, s2, 18000);
                        at = slti(v1, 3);
                        if (at != 0) {
                            goto L_00222584;
                        }
                    }
                }
                goto L_0022258c;
            }
        L_00222584:
            charge(ctx, 2);
            jal(ctx, 0x222584u, gen::fn_sub_225040_00225040);
            goto L_0022258c;
        }
    L_0022250c:
        charge(ctx, 4);
        lw(v1, s2, 17988);
        v0 = 4;
        if (v1 == v0) {
            // 0x0022253c
            charge(ctx, 2);
            jal(ctx, 0x22253Cu, gen::fn_sub_22C5A0_0022c5a0);
        } else {
            // 0x0022251c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0022252c
                charge(ctx, 4);
                jal(ctx, 0x22252Cu, gen::fn_sub_227800_00227800);
            } else {
                // 0x00222524
                charge(ctx, 2);
            }
        }
        // 0x00222544
        charge(ctx, 4);
        jal(ctx, 0x222544u, gen::fn_sub_22AE80_0022ae80);
        goto L_0022258c;
    }
L_00222494:
    charge(ctx, 4);
    lw(v1, s2, 17988);
    v0 = 3;
    if (v1 == v0) {
        // 0x002224c4
        charge(ctx, 2);
        jal(ctx, 0x2224C4u, gen::fn_sub_22C5A0_0022c5a0);
    } else {
        // 0x002224a4
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x002224b4
            charge(ctx, 4);
            jal(ctx, 0x2224B4u, gen::fn_sub_227800_00227800);
        } else {
            // 0x002224ac
            charge(ctx, 2);
        }
    }
    // 0x002224cc
    charge(ctx, 4);
    jal(ctx, 0x2224CCu, gen::fn_sub_229B40_00229b40);
L_0022258c:
    charge(ctx, 4);
    lw(v1, s2, 17980);
    a0 = 3;
    if (v1 != a0) {
        // 0x0022259c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x002225a4
            charge(ctx, 3);
            lw(v1, s2, 17984);
            if (v1 == a0) {
                // 0x002225b0
                charge(ctx, 4);
                lw(v1, s2, 18000);
                at = slti(v1, 3);
                if (at != 0) {
                    goto L_002225c0;
                }
            }
        }
        goto L_002225c8;
    }
L_002225c0:
    charge(ctx, 2);
    jal(ctx, 0x2225C0u, gen::fn_sub_224150_00224150);
L_002225c8:
    charge(ctx, 4);
    lw(a0, s2, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x002225e0
        charge(ctx, 3);
        lw(a0, s2, 17988);
        if (a0 == 0) {
            // 0x00222610
            charge(ctx, 4);
            lw(a0, s2, 17992);
            v1 = 1;
            if (a0 == v1) {
                // 0x00222620
                charge(ctx, 4);
                lw(a0, s2, 18008);
                v1 = 6;
                if (a0 != v1) {
                    // 0x00222630
                    charge(ctx, 2);
                    jal(ctx, 0x222630u, gen::fn_sub_2289B0_002289b0);
                }
            }
        } else {
            // 0x002225ec
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x00222600
                charge(ctx, 4);
                jal(ctx, 0x222600u, gen::fn_sub_2289B0_002289b0);
            } else {
                // 0x002225f8
                charge(ctx, 2);
            }
        }
    } else {
        // 0x002225d8
        charge(ctx, 2);
    }
    // 0x00222638
    charge(ctx, 4);
    lw(a0, s2, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x00222650
        charge(ctx, 4);
        lw(v1, s2, 17988);
        a1 = 2;
        if (v1 != a1) {
            // 0x00222660
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                goto L_002226b0;
            }
            // 0x0022266c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0022267c
                charge(ctx, 3);
                lw(v1, s2, 17992);
                if (v1 != a0) {
                    // 0x00222688
                    charge(ctx, 2);
                    if (v1 == a1) {
                        goto L_00222690;
                    }
                    // 0x002226b8 (the shared epilogue, written out on this path)
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
            L_00222690:
                charge(ctx, 4);
                lw(v1, s2, 18008);
                at = slti(v1, 6);
                if (at != 0) {
                    // 0x002226a0
                    charge(ctx, 4);
                    jal(ctx, 0x2226A0u, gen::fn_sub_226040_00226040);
                }
            } else {
                // 0x00222674
                charge(ctx, 2);
            }
            // 0x002226b8 (the shared epilogue, written out on this path)
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
    L_002226b0:
        charge(ctx, 2);
        jal(ctx, 0x2226B0u, gen::fn_sub_226040_00226040);
    } else {
        // 0x00222648
        charge(ctx, 2);
    }
    // 0x002226b8 (the shared epilogue, written out on this path)
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

// 0x00223290 sub_223290 -- 3768 bytes; frame 0x150: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutList3] lays out sub-list 3 (its rows at +18016, the fade of its steps, the font lines with
// their widths).
void sub_223290(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00223290
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x002232d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x2232DCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x002232e4
    charge(ctx, 10);
    lw(s3, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x2232ECu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s7 = v0;
    s2 = addiu(s3, 18016);
    lwc1(f20, s3, kBcmFade);
    lw(v1, s3, kBcmSub);
    if (v1 == 0) {
        // 0x002233f4
        charge(ctx, 10);
        lw(v0, s3, kBcmSubTimer);
        v1 = 3;
        v0 = subu(v1, v0);
        div(v0, v1);
        mflo(v0);
        mtc1(v0, f0);
        cvt_s_w(f21, f0);
    } else {
        // 0x0022330c
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00223320
            charge(ctx, 4);
            lw(v0, s3, kBcmSubStep);
            a0 = 2;
            if (v0 != a0) {
                // 0x00223330
                charge(ctx, 3);
                v1 = 1;
                if (v0 == v1) {
                    goto L_002233cc;
                }
                // 0x0022333c
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x0022334c
                    charge(ctx, 3);
                    lw(v0, s3, kBcmSubSel);
                    if (v0 != v1) {
                        // 0x00223358
                        charge(ctx, 2);
                        if (v0 == a0) {
                            goto L_00223360;
                        }
                    L_002233a0:
                        charge(ctx, 11);
                        lwc1(f0, s3, 18000);
                        cvt_s_w(f1, f0);
                        v0 = 0x40400000;
                        mtc1(v0, f0);
                        div_s(f21, f1, f0);
                        goto L_00223430;
                    }
                L_00223360:
                    charge(ctx, 4);
                    lw(v0, s3, 18008);
                    at = slti(v0, 6);
                    if (at == 0) {
                        goto L_002233a0;
                    }
                    // 0x00223370
                    charge(ctx, 12);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    div_s(f21, f1, f0);
                } else {
                    // 0x00223344
                    charge(ctx, 2);
                }
                goto L_00223430;
            }
        L_002233cc:
            charge(ctx, 10);
            lw(v0, s3, 18008);
            v1 = 6;
            v0 = subu(v1, v0);
            div(v0, v1);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f21, f0);
        } else {
            // 0x00223318
            charge(ctx, 2);
            // 0x0022341c
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7296);  // "bcm_panel.c"
            a1 = 1765;
            jal(ctx, 0x223428u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 1765): `jr $ra` in retail, execution goes on
        }
    }
L_00223430:
    charge(ctx, 107);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f21);
    mul_s(f0, f0, f20);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    s6 = v0 & 0xFF;
    s1 = addiu(s3, 24656);
    a0 = s7;
    a1 = 36;
    jal(ctx, 0x223460u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s1, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    lw(a0, s3, 24680);
    lw(v1, s3, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s1, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0x134);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x138);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x13C);
    a0 = addiu(s3, 16944);
    a1 = addiu(sp, 0x130);
    jal(ctx, 0x2234E4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s7;
    a1 = 36;
    jal(ctx, 0x2234F4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s1, 0);
    add_s(f1, f1, f0);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    lw(a0, s3, 24680);
    lw(v1, s3, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s1, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0x134);
    v1 = 0x439C0000;
    sw(v1, sp, 0x138);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x13C);
    a0 = addiu(s3, 17200);
    a1 = addiu(sp, 0x130);
    jal(ctx, 0x223580u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x14C);
    sb(v0, sp, 0x14D);
    sb(v0, sp, 0x14E);
    sb(s6, sp, 0x14F);
    a0 = addiu(s3, 16944);
    a1 = addiu(sp, 0x14C);
    jal(ctx, 0x2235A4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s3, 17200);
    a1 = addiu(sp, 0x14C);
    jal(ctx, 0x2235B4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(a0, s3, 0);
    v1 = si(-5);
    v1 = a0 & v1;
    sw(v1, s3, 0);
    lw(a0, s3, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x002235e4
        charge(ctx, 4);
        lw(v1, s3, 17988);
        a1 = 2;
        if (v1 != a1) {
            // 0x002235f4
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                goto L_002237f8;
            }
            // 0x00223600
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00223610
                charge(ctx, 3);
                lw(v1, s3, 17992);
                if (v1 != a0) {
                    // 0x0022361c
                    charge(ctx, 2);
                    if (v1 == a1) {
                        goto L_00223624;
                    }
                    goto L_00223990;
                }
            L_00223624:
                charge(ctx, 4);
                lw(v1, s3, 18008);
                at = slti(v1, 6);
                if (at != 0) {
                    // 0x00223634
                    charge(ctx, 4);
                    lw(v1, s3, 4);
                    v1 = v1 & 0x4;
                    if (v1 == 0) {
                        // 0x00223644
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7296);  // "bcm_panel.c"
                        a1 = 1809;
                        jal(ctx, 0x223650u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 1809): `jr $ra` in retail, execution goes on
                    }
                    // 0x00223658
                    charge(ctx, 21);
                    a0 = s6 & 0xFF;
                    a1 = si(-256);
                    v1 = a0 | a1;
                    sw(v1, s2, 6340);
                    v1 = 255;
                    a0 = subu(v1, a0);
                    v1 = lui(0xFF9D);
                    v1 = v1 | 0x9D00;
                    v1 = a0 | v1;
                    sw(v1, s2, 6344);
                    v1 = a0 | a1;
                    sw(v1, s2, 6348);
                    lw(a0, s2, 6336);
                    v1 = sll(a0, 5);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 5);
                    a1 = addu(s2, v1);
                    lw(a0, a1, 0);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x00223724
                        charge(ctx, 6);
                        lw(a0, a1, 8);
                        jal(ctx, 0x223728u, gen::fn_frFontLineGetWidth_003b19d0);
                        v1 = sra(v0, 1);
                        if (i64(v0) < 0) {
                            // 0x0022373c
                            charge(ctx, 2);
                            v1 = addiu(v0, 1);
                            v1 = sra(v1, 1);
                        }
                        // 0x00223744
                        charge(ctx, 29);
                        mtc1(v1, f0);
                        cvt_s_w(f2, f0);
                        v1 = 0x42E00000;
                        mtc1(v1, f1);
                        lwc1(f0, s1, 0);
                        add_s(f1, f1, f0);
                        v1 = 0x428D0000;
                        mtc1(v1, f0);
                        add_s(f0, f0, f1);
                        sub_s(f0, f0, f2);
                        swc1(f0, s2, 6352);
                        lwc1(f1, s1, 4);
                        v1 = 0x41980000;
                        mtc1(v1, f0);
                        add_s(f1, f0, f1);
                        lw(a0, s2, 6336);
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s2, 6356);
                    } else {
                        // 0x002236ac
                        charge(ctx, 3);
                        v1 = 2;
                        if (a0 != v1) {
                            // 0x002236b8
                            charge(ctx, 2);
                            if (a0 == 0) {
                                goto L_002236c8;
                            }
                            // 0x002236c0
                            charge(ctx, 2);
                            goto L_002237b8;
                        }
                    L_002236c8:
                        charge(ctx, 23);
                        v1 = 0x424C0000;
                        mtc1(v1, f1);
                        lwc1(f0, s1, 0);
                        add_s(f0, f1, f0);
                        swc1(f0, s2, 6352);
                        lwc1(f1, s1, 4);
                        v1 = 0x41980000;
                        mtc1(v1, f0);
                        add_s(f1, f0, f1);
                        lw(a0, s2, 6336);
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s2, 6356);
                    }
                L_002237b8:
                    charge(ctx, 16);
                    v1 = 0x432B0000;
                    mtc1(v1, f1);
                    lwc1(f0, s1, 0);
                    add_s(f0, f1, f0);
                    swc1(f0, s2, 6360);
                    lwc1(f1, s1, 4);
                    v1 = 0x41980000;
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, s2, 6364);
                    lw(v1, s3, 0);
                    v1 = v1 | 0x4;
                    sw(v1, s3, 0);
                }
            } else {
                // 0x00223608
                charge(ctx, 2);
            }
            goto L_00223990;
        }
    L_002237f8:
        charge(ctx, 21);
        a0 = s6 & 0xFF;
        a1 = si(-256);
        v1 = a0 | a1;
        sw(v1, s2, 6340);
        v1 = 255;
        a0 = subu(v1, a0);
        v1 = lui(0xFF9D);
        v1 = v1 | 0x9D00;
        v1 = a0 | v1;
        sw(v1, s2, 6344);
        v1 = a0 | a1;
        sw(v1, s2, 6348);
        lw(a0, s2, 6336);
        v1 = sll(a0, 5);
        v1 = addu(v1, a0);
        v1 = sll(v1, 5);
        a1 = addu(s2, v1);
        lw(a0, a1, 0);
        v1 = 1;
        if (a0 == v1) {
            // 0x002238c4
            charge(ctx, 6);
            lw(a0, a1, 8);
            jal(ctx, 0x2238C8u, gen::fn_frFontLineGetWidth_003b19d0);
            v1 = sra(v0, 1);
            if (i64(v0) < 0) {
                // 0x002238dc
                charge(ctx, 2);
                v1 = addiu(v0, 1);
                v1 = sra(v1, 1);
            }
            // 0x002238e4
            charge(ctx, 29);
            mtc1(v1, f0);
            cvt_s_w(f2, f0);
            v1 = 0x42E00000;
            mtc1(v1, f1);
            lwc1(f0, s1, 0);
            add_s(f1, f1, f0);
            v1 = 0x428D0000;
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            sub_s(f0, f0, f2);
            swc1(f0, s2, 6352);
            lwc1(f1, s1, 4);
            v1 = 0x41980000;
            mtc1(v1, f0);
            add_s(f1, f0, f1);
            lw(a0, s2, 6336);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            v1 = sll(v1, 1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s2, 6356);
        } else {
            // 0x0022384c
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x00223858
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_00223868;
                }
                // 0x00223860
                charge(ctx, 2);
                goto L_00223958;
            }
        L_00223868:
            charge(ctx, 23);
            v1 = 0x424C0000;
            mtc1(v1, f1);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, s2, 6352);
            lwc1(f1, s1, 4);
            v1 = 0x41980000;
            mtc1(v1, f0);
            add_s(f1, f0, f1);
            lw(a0, s2, 6336);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            v1 = sll(v1, 1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s2, 6356);
        }
    L_00223958:
        charge(ctx, 14);
        v1 = 0x432B0000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, s2, 6360);
        lwc1(f1, s1, 4);
        v1 = 0x41980000;
        mtc1(v1, f0);
        add_s(f0, f0, f1);
        swc1(f0, s2, 6364);
        lw(v1, s3, 0);
        v1 = v1 | 0x4;
        sw(v1, s3, 0);
    } else {
        // 0x002235dc
        charge(ctx, 2);
    }
L_00223990:
    charge(ctx, 4);
    lw(v1, s3, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x002239a0
        charge(ctx, 41);
        a0 = s7;
        a1 = 47;
        jal(ctx, 0x2239A8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        a0 = addiu(s2, 6384);
        a1 = s0;
        jal(ctx, 0x2239BCu, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
        v0 = 0x43320000;
        mtc1(v0, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x130);
        lwc1(f1, s1, 4);
        v0 = 0x425C0000;
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x134);
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x138);
        lwc1(f0, s0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x13C);
        a0 = addiu(s2, 6384);
        a1 = addiu(sp, 0x130);
        jal(ctx, 0x223A10u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v1 = 255;
        sb(v1, sp, 0x14C);
        sb(v1, sp, 0x14D);
        sb(v1, sp, 0x14E);
        v0 = s6 & 0xFF;
        v0 = subu(v1, v0);
        sb(v0, sp, 0x14F);
        a0 = addiu(s2, 6384);
        a1 = addiu(sp, 0x14C);
        jal(ctx, 0x223A3Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    }
    // 0x00223a44
    charge(ctx, 24);
    s5 = 0;
    a1 = s6 & 0xFF;
    v1 = si(-256);
    v1 = a1 | v1;
    sw(v1, sp, 0x120);
    v1 = lui(0xBEFF);
    v1 = v1 | 0xD200;
    v1 = a1 | v1;
    sw(v1, sp, 0x110);
    a0 = sll(a1, 7);
    v1 = 255;
    div(a0, v1);
    mflo(v1);
    sq(v1, sp, 0xE0);
    v1 = lui(0xCCCC);
    v1 = v1 | 0xCC00;
    v1 = a1 | v1;
    sw(v1, sp, 0x100);
    v1 = 0x64CC0000;
    v1 = v1 | 0x6400;
    v1 = a1 | v1;
    sw(v1, sp, 0xF0);
    for (;;) {
        // 0x002240fc
        charge(ctx, 4);
        lw(v1, s3, 24688);
        v1 = slt(s5, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00223aa4
        charge(ctx, 8);
        v1 = sll(s5, 5);
        v1 = addu(v1, s5);
        v1 = sll(v1, 5);
        s0 = addu(s2, v1);
        lw(a0, s0, 0);
        v1 = 1;
        if (a0 == v1) {
            // 0x00223dd8
            charge(ctx, 7);
            lw(fp, s0, 8);
            a0 = fp;
            jal(ctx, 0x223DE0u, gen::fn_frFontLineGetWidth_003b19d0);
            v1 = sra(v0, 1);
            if (i64(v0) < 0) {
                // 0x00223df4
                charge(ctx, 2);
                v0 = addiu(v0, 1);
                v1 = sra(v0, 1);
            }
            // 0x00223dfc
            charge(ctx, 33);
            mtc1(v1, f0);
            cvt_s_w(f2, f0);
            v0 = 0x42E00000;
            mtc1(v0, f1);
            lwc1(f0, s1, 0);
            add_s(f1, f1, f0);
            v0 = 0x428D0000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            sub_s(f0, f0, f2);
            swc1(f0, sp, 0x130);
            v0 = sll(s5, 1);
            v0 = addu(v0, s5);
            v0 = sll(v0, 2);
            v0 = addu(v0, s5);
            v1 = sll(v0, 1);
            lwc1(f1, s1, 4);
            v0 = 0x41980000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lw(v1, s3, 24680);
            lw(v0, s3, 24684);
            v0 = subu(v1, v0);
            if (s5 != v0) {
                // 0x00223e8c
                charge(ctx, 1);
                lw(s4, sp, 0x100);
            } else {
                // 0x00223e80
                charge(ctx, 3);
                lw(s4, sp, 0x120);
            }
            // 0x00223e90
            charge(ctx, 139);
            lwc1(f0, sp, 0x130);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a1 = sll(v0, 4);
            lwc1(f0, sp, 0x134);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a2 = sll(v0, 3);
            a0 = fp;
            jal(ctx, 0x223EBCu, gen::fn_frFontLineSetPos_003b0d70);
            a0 = fp;
            a1 = s4;
            jal(ctx, 0x223ECCu, gen::fn_frFontLineSetRgba_003b0e20);
            a0 = s7;
            a1 = 41;
            jal(ctx, 0x223EDCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            sq(v0, sp, 0xC0);
            v1 = 0x429E0000;
            mtc1(v1, f1);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            v1 = sll(s5, 1);
            v1 = addu(v1, s5);
            v1 = sll(v1, 2);
            v1 = addu(v1, s5);
            fp = sll(v1, 1);
            lwc1(f1, s1, 4);
            v1 = 0x41E80000;
            mtc1(v1, f0);
            add_s(f1, f0, f1);
            mtc1(fp, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x138);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x13C);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 0x130);
            jal(ctx, 0x223F58u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 0x42C60000;
            mtc1(v0, f1);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            lwc1(f1, s1, 4);
            v0 = 0x41E80000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            mtc1(fp, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lq(v0, sp, 0xC0);
            lwc1(f0, v0, 12);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x138);
            lwc1(f0, v0, 16);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x13C);
            a0 = addiu(s0, 272);
            a1 = addiu(sp, 0x130);
            jal(ctx, 0x223FC0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            a0 = s7;
            a1 = 42;
            jal(ctx, 0x223FD0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            sq(v0, sp, 0xB0);
            v1 = 0x437D0000;
            mtc1(v1, f1);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            lwc1(f1, s1, 4);
            v1 = 0x41E80000;
            mtc1(v1, f0);
            add_s(f1, f0, f1);
            mtc1(fp, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x138);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x13C);
            a0 = addiu(s0, 528);
            a1 = addiu(sp, 0x130);
            jal(ctx, 0x224038u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 273;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            lwc1(f1, s1, 4);
            v0 = 0x41E80000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            mtc1(fp, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lq(v0, sp, 0xB0);
            lwc1(f0, v0, 12);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x138);
            lwc1(f0, v0, 16);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x13C);
            a0 = addiu(s0, 784);
            a1 = addiu(sp, 0x130);
            jal(ctx, 0x2240A8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            fp = 0;
            for (;;) {  // while (fp < 4)
                // 0x002240ec
                charge(ctx, 3);
                v1 = slti(fp, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002240bc
                charge(ctx, 12);
                v0 = 255;
                sb(v0, sp, 0x14C);
                sb(v0, sp, 0x14D);
                sb(v0, sp, 0x14E);
                sb(s6, sp, 0x14F);
                v0 = sll(fp, 8);
                v0 = addu(s0, v0);
                a0 = addiu(v0, 16);
                a1 = addiu(sp, 0x14C);
                jal(ctx, 0x2240E0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
                fp = addiu(fp, 0x1);
            }
        } else {
            // 0x00223ac4
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x00223ad0
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_00223ae0;
                }
                // 0x00223ad8
                charge(ctx, 2);
                goto L_002240f8;
            }
        L_00223ae0:
            charge(ctx, 26);
            lw(fp, s0, 8);
            v0 = 0x424C0000;
            mtc1(v0, f1);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            v0 = sll(s5, 1);
            v0 = addu(v0, s5);
            v0 = sll(v0, 2);
            v0 = addu(v0, s5);
            v1 = sll(v0, 1);
            lwc1(f1, s1, 4);
            v0 = 0x41980000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lw(v1, s3, 24680);
            lw(v0, s3, 24684);
            v0 = subu(v1, v0);
            if (s5 != v0) {
                // 0x00223bd4
                charge(ctx, 3);
                lw(v0, s0, 1040);
                if (v0 != 0) {
                    // 0x00223c18
                    charge(ctx, 16);
                    v0 = 255;
                    sb(v0, sp, 0x14C);
                    sb(v0, sp, 0x14D);
                    sb(v0, sp, 0x14E);
                    lq(v0, sp, 0xE0);
                    sb(v0, sp, 0x14F);
                    lbu(v0, sp, 0x14C);
                    v1 = sll(v0, 24);
                    lbu(v0, sp, 0x14D);
                    v0 = sll(v0, 16);
                    v1 = v1 | v0;
                    lbu(v0, sp, 0x14E);
                    v0 = sll(v0, 8);
                    v1 = v0 | v1;
                    lbu(v0, sp, 0x14F);
                    s4 = v0 | v1;
                } else {
                    // 0x00223be0
                    charge(ctx, 4);
                    lw(v1, s0, 0);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00223c0c
                        charge(ctx, 3);
                        lw(s4, sp, 0xF0);
                    } else {
                        // 0x00223bf0
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00223c00
                            charge(ctx, 3);
                            lw(s4, sp, 0x100);
                        } else {
                            // 0x00223bf8
                            charge(ctx, 2);
                        }
                    }
                }
            } else {
                // 0x00223b48
                charge(ctx, 3);
                lw(v0, s0, 1040);
                if (v0 != 0) {
                    // 0x00223b8c
                    charge(ctx, 18);
                    v0 = 255;
                    sb(v0, sp, 0x14C);
                    sb(v0, sp, 0x14D);
                    sb(v0, sp, 0x14E);
                    lq(v0, sp, 0xE0);
                    sb(v0, sp, 0x14F);
                    lbu(v0, sp, 0x14C);
                    v1 = sll(v0, 24);
                    lbu(v0, sp, 0x14D);
                    v0 = sll(v0, 16);
                    v1 = v1 | v0;
                    lbu(v0, sp, 0x14E);
                    v0 = sll(v0, 8);
                    v1 = v0 | v1;
                    lbu(v0, sp, 0x14F);
                    s4 = v0 | v1;
                } else {
                    // 0x00223b54
                    charge(ctx, 4);
                    lw(v1, s0, 0);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00223b80
                        charge(ctx, 3);
                        lw(s4, sp, 0x110);
                    } else {
                        // 0x00223b64
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00223b74
                            charge(ctx, 3);
                            lw(s4, sp, 0x120);
                        } else {
                            // 0x00223b6c
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x00223c58
            charge(ctx, 96);
            lwc1(f0, sp, 0x130);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a1 = sll(v0, 4);
            lwc1(f0, sp, 0x134);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a2 = sll(v0, 3);
            a0 = fp;
            jal(ctx, 0x223C84u, gen::fn_frFontLineSetPos_003b0d70);
            a0 = fp;
            a1 = s4;
            jal(ctx, 0x223C94u, gen::fn_frFontLineSetRgba_003b0e20);
            lw(fp, s0, 12);
            v0 = 0x43360000;
            mtc1(v0, f1);
            lwc1(f0, s1, 0);
            add_s(f2, f1, f0);
            swc1(f2, sp, 0x130);
            v0 = sll(s5, 1);
            v0 = addu(v0, s5);
            v0 = sll(v0, 2);
            v0 = addu(v0, s5);
            v0 = sll(v0, 1);
            sq(v0, sp, 0xD0);
            lwc1(f1, s1, 4);
            v0 = 0x41980000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            lq(v0, sp, 0xD0);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f1, f0);
            swc1(f1, sp, 0x134);
            cvt_w_s(f0, f2);
            mfc1(v0, f0);
            a1 = sll(v0, 4);
            cvt_w_s(f0, f1);
            mfc1(v0, f0);
            a2 = sll(v0, 3);
            a0 = fp;
            jal(ctx, 0x223D1Cu, gen::fn_frFontLineSetPos_003b0d70);
            a0 = fp;
            a1 = s4;
            jal(ctx, 0x223D2Cu, gen::fn_frFontLineSetRgba_003b0e20);
            a0 = s7;
            a1 = 47;
            jal(ctx, 0x223D3Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x432B0000;
            mtc1(v1, f1);
            lwc1(f0, s1, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            lwc1(f1, s1, 4);
            v1 = 0x41E00000;
            mtc1(v1, f0);
            add_s(f1, f0, f1);
            lq(v1, sp, 0xD0);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x138);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x13C);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 0x130);
            jal(ctx, 0x223DA4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 255;
            sb(v0, sp, 0x14C);
            sb(v0, sp, 0x14D);
            sb(v0, sp, 0x14E);
            sb(s6, sp, 0x14F);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 0x14C);
            jal(ctx, 0x223DC8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        }
    L_002240f8:
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x0022410c
    charge(ctx, 15);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x00224150 sub_224150 -- 1292 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawList3] draws sub-list 3 (quads and font chains).
void sub_224150(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00224150
    enter(ctx, 14);  // entry check point + this block's cycles
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00224188
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x224194u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022419c
    charge(ctx, 59);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x2241A4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    s1 = addiu(s2, 18016);
    s0 = addiu(s2, 24704);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x2241C0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s6 = 0x960000;
    s6 = addiu(s6, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x2241D4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s6, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2241E8u, v0.u());
    s3 = 0x960000;
    s3 = addiu(s3, 156);  // &0x96009C
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s3, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x224210u, v0.u());
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s3, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x224230u, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s3, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x224250u, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s3, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x224270u, v0.u());
    lw(v1, s2, kBcmFlags);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x00224288
        charge(ctx, 9);
        lw(v1, s1, 6336);
        v0 = sll(v1, 5);
        v0 = addu(v0, v1);
        v0 = sll(v0, 5);
        v0 = addu(s1, v0);
        lw(v1, v0, 0);
        v0 = 1;
        if (v1 != v0) {
            // 0x002242ac
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002242bc
                charge(ctx, 37);
                a0 = s5;
                a1 = 47;
                jal(ctx, 0x2242C4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                a0 = v0;
                jal(ctx, 0x2242D0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
                a0 = 1;
                a1 = v0;
                lw(v0, s6, 0);
                jalr(ctx, 0x2242E4u, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x2242F8u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x224308u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = addiu(s1, 6384);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s3, 0);
                jalr(ctx, 0x224328u, v0.u());
                a0 = addiu(s1, 6384);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s3, 0);
                jalr(ctx, 0x224348u, v0.u());
            } else {
                // 0x002242b4
                charge(ctx, 2);
            }
        }
        // 0x00224350
        charge(ctx, 8);
        lw(a0, s0, 1376);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x22435Cu, gen::fn_frFontDraw_003b1360);
        lw(a0, s0, 1380);
        if (a0 != 0) {
            // 0x00224370
            charge(ctx, 4);
            a1 = 1;
            a2 = 0;
            jal(ctx, 0x224378u, gen::fn_frFontDraw_003b1360);
        }
    }
    // 0x00224380
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x00224618
        charge(ctx, 4);
        lw(v1, s2, 24688);
        v1 = slt(s4, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022438c
        charge(ctx, 8);
        v1 = sll(s4, 5);
        v1 = addu(v1, s4);
        v1 = sll(v1, 5);
        s0 = addu(s1, v1);
        lw(a0, s0, 0);
        a1 = 1;
        if (a0 == a1) {
            // 0x0022451c
            charge(ctx, 7);
            lw(a0, s0, 8);
            a2 = 0;
            jal(ctx, 0x224524u, gen::fn_frFontDraw_003b1360);
            s3 = 0;
            for (;;) {  // while (s3 < 4)
                // 0x00224608
                charge(ctx, 3);
                v1 = slti(s3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00224538
                charge(ctx, 3);
                at = slti(s3, 2);
                if (at == 0) {
                    // 0x0022455c
                    charge(ctx, 4);
                    a0 = s5;
                    a1 = 42;
                    jal(ctx, 0x224564u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                } else {
                    // 0x00224544
                    charge(ctx, 6);
                    a0 = s5;
                    a1 = 41;
                    jal(ctx, 0x22454Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                }
                // 0x0022456c
                charge(ctx, 39);
                a0 = v0;
                jal(ctx, 0x224570u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
                a0 = 1;
                a1 = v0;
                lw(v0, s6, 0);
                jalr(ctx, 0x224584u, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x224598u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x2245A8u, gen::fn_RpSkyRenderStateSet_004d7f60);
                v0 = sll(s3, 8);
                v0 = addu(s0, v0);
                s7 = addiu(v0, 16);
                fp = 0x960000;
                fp = addiu(fp, 0x9C);
                a0 = s7;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, fp, 0x0);
                jalr(ctx, 0x2245DCu, v0.u());
                a0 = s7;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, fp, 0x0);
                jalr(ctx, 0x2245FCu, v0.u());
                s3 = addiu(s3, 1);
            }
        } else {
            // 0x002243ac
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x002243b8
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_002243c8;
                }
                // 0x002243c0
                charge(ctx, 2);
                goto L_00224614;
            }
        L_002243c8:
            charge(ctx, 5);
            lw(v1, s2, 24680);
            lw(v0, s2, 24684);
            v0 = subu(v1, v0);
            if (s4 != v0) {
                // 0x00224408
                charge(ctx, 9);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x224414u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 66;
                jal(ctx, 0x224424u, gen::fn_RpSkyRenderStateSet_004d7f60);
            } else {
                // 0x002243dc
                charge(ctx, 11);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x2243E8u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x2243F8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            }
            // 0x0022442c
            charge(ctx, 60);
            lw(a0, s0, 8);
            a1 = 1;
            a2 = 0;
            jal(ctx, 0x224438u, gen::fn_frFontDraw_003b1360);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x22444Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x22445Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            lw(a0, s0, 12);
            a1 = 1;
            a2 = 0;
            jal(ctx, 0x224470u, gen::fn_frFontDraw_003b1360);
            a0 = s5;
            a1 = 47;
            jal(ctx, 0x224480u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x22448Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s6, 0);
            jalr(ctx, 0x2244A0u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x2244B4u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x2244C4u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s3 = 0x960000;
            s3 = addiu(s3, 156);  // &0x96009C
            a0 = addiu(s0, 16);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s3, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2244ECu, v0.u());
            a0 = addiu(s0, 16);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s3, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x22450Cu, v0.u());
        }
    L_00224614:
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x00224628
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

// 0x00224940 sub_224940 -- 1784 bytes; frame 0x110: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutList4] lays out sub-list 4: rows, numbers (centred bpIfont, sub_238DC0), font lines; the fade
// is sub-timer / 3 (K_Assert 2227 if another list is open).
void sub_224940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00224940
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00224980
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22498Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00224994
    charge(ctx, 18);
    lw(s3, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22499Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    fp = v0;
    a0 = 1;
    jal(ctx, 0x2249ACu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    sw(v0, sp, 0xEC);
    a0 = 3;
    jal(ctx, 0x2249BCu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    sw(v0, sp, 0xE8);
    s2 = addiu(s3, 18016);
    lwc1(f21, s3, kBcmFade);
    lw(v1, s3, kBcmSub);
    if (v1 == 0) {
        // 0x00224a1c
        charge(ctx, 15);
        lw(v1, s3, kBcmSubTimer);
        v0 = 3;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f20, f1, f0);
    } else {
        // 0x002249dc
        charge(ctx, 3);
        v0 = 4;
        if (v1 == v0) {
            // 0x002249f0
            charge(ctx, 11);
            lwc1(f0, s3, kBcmSubTimer);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f20, f1, f0);
        } else {
            // 0x002249e8
            charge(ctx, 2);
            // 0x00224a58
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7296);  // "bcm_panel.c"
            a1 = 2227;
            jal(ctx, 0x224A64u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 2227): `jr $ra` in retail, execution goes on
        }
    }
    // 0x00224a6c
    charge(ctx, 11);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00224ab0
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00224a98
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00224ac8
    charge(ctx, 99);
    s1 = v1 & 0xFF;
    s0 = addiu(s3, 24656);
    a0 = fp;
    a1 = 36;
    jal(ctx, 0x224AD8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s0, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    lw(a0, s3, 24680);
    lw(v1, s3, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s0, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xF4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xFC);
    a0 = addiu(s3, 16944);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x224B5Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = fp;
    a1 = 36;
    jal(ctx, 0x224B6Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s0, 0);
    add_s(f1, f1, f0);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    lw(a0, s3, 24680);
    lw(v1, s3, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s0, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xF4);
    v1 = 0x439C0000;
    sw(v1, sp, 0xF8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xFC);
    a0 = addiu(s3, 17200);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x224BF8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x10C);
    sb(v0, sp, 0x10D);
    sb(v0, sp, 0x10E);
    sb(s1, sp, 0x10F);
    a0 = addiu(s3, 16944);
    a1 = addiu(sp, 0x10C);
    jal(ctx, 0x224C1Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s3, 17200);
    a1 = addiu(sp, 0x10C);
    jal(ctx, 0x224C2Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s4 = 0;
    v0 = s1 & 0xFF;
    sq(v0, sp, 0xC0);
    v1 = si(-256);
    v0 = v0 | v1;
    sw(v0, sp, 0xD0);
    for (;;) {
        // 0x00224ed0
        charge(ctx, 4);
        lw(v0, s3, 24688);
        v0 = slt(s4, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00224c54
        charge(ctx, 30);
        v0 = sll(s4, 3);
        v1 = subu(v0, s4);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        s5 = addu(s2, v0);
        lw(s6, s5, 768);
        v0 = 0x430F0000;
        mtc1(v0, f1);
        lwc1(f0, s0, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        v0 = sll(s4, 1);
        v0 = addu(v0, s4);
        v0 = sll(v0, 2);
        v0 = addu(v0, s4);
        s7 = sll(v0, 1);
        lwc1(f1, s0, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(s7, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        lw(v0, s6, 28);
        if (v0 == 0) {
            // 0x00224cec
            charge(ctx, 2);
            lw(v0, sp, 0xD0);
            sq(v0, sp, 0xB0);
        } else {
            // 0x00224ccc
            charge(ctx, 8);
            lw(v1, v0, 16);
            v0 = si(-256);
            v1 = v1 & v0;
            lq(v0, sp, 0xC0);
            v0 = v1 | v0;
            sq(v0, sp, 0xB0);
        }
        // 0x00224cf4
        charge(ctx, 51);
        lwc1(f0, sp, 0xF0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        lwc1(f0, sp, 0xF4);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        a0 = s6;
        jal(ctx, 0x224D20u, gen::fn_frFontLineSetPos_003b0d70);
        a0 = s6;
        lq(a1, sp, 0xB0);
        jal(ctx, 0x224D30u, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = fp;
        a1 = 68;
        jal(ctx, 0x224D40u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x426C0000;
        mtc1(v1, f1);
        lwc1(f0, s0, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s0, 4);
        v1 = 0x41F00000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        mtc1(s7, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xF8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xFC);
        a0 = s5;
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x224DA4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lw(v1, s3, 24680);
        lw(v0, s3, 24684);
        v0 = subu(v1, v0);
        if (s4 != v0) {
            // 0x00224ddc
            charge(ctx, 4);
            v0 = 90;
            sb(v0, sp, 0x10C);
            sb(v0, sp, 0x10D);
            sb(v0, sp, 0x10E);
        } else {
            // 0x00224dc0
            charge(ctx, 7);
            v0 = 245;
            sb(v0, sp, 0x10C);
            sb(v0, sp, 0x10D);
            v0 = 255;
            sb(v0, sp, 0x10E);
        }
        // 0x00224dec
        charge(ctx, 32);
        sb(s1, sp, 0x10F);
        a0 = s5;
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x224DF8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 0x42BE0000;
        mtc1(v0, f1);
        lwc1(f0, s0, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s0, 4);
        v0 = 0x41F00000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(s7, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        a0 = addiu(s5, 256);
        a1 = 2;
        lw(a2, s5, 772);
        a3 = 1;
        t0 = addiu(sp, 0xF0);
        jal(ctx, 0x224E50u, gen::fn_sub_238DC0_00238dc0);
        lw(v1, s3, 24680);
        lw(v0, s3, 24684);
        v0 = subu(v1, v0);
        if (s4 != v0) {
            // 0x00224e84
            charge(ctx, 4);
            v0 = 90;
            sb(v0, sp, 0x10C);
            sb(v0, sp, 0x10D);
            sb(v0, sp, 0x10E);
        } else {
            // 0x00224e6c
            charge(ctx, 6);
            v0 = 255;
            sb(v0, sp, 0x10C);
            sb(v0, sp, 0x10D);
            sb(v0, sp, 0x10E);
        }
        // 0x00224e94
        charge(ctx, 4);
        sb(s1, sp, 0x10F);
        s6 = 0;
        for (;;) {  // while (s6 < 2)
            // 0x00224ec0
            charge(ctx, 3);
            v0 = slti(s6, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00224ea4
            charge(ctx, 7);
            v0 = sll(s6, 8);
            v0 = addu(s5, v0);
            a0 = addiu(v0, 256);
            a1 = addiu(sp, 0x10C);
            jal(ctx, 0x224EB4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            s6 = addiu(s6, 1);
        }
        // 0x00224ecc
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x00224ee0
    charge(ctx, 86);
    s0 = addiu(s3, 24656);
    lw(a0, sp, 0xE8);
    a1 = 19;
    jal(ctx, 0x224EECu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x43840000;
    mtc1(v1, f1);
    lwc1(f0, s0, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    lwc1(f1, s0, 4);
    v1 = 0x42FC0000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0xF4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xFC);
    a0 = addiu(s2, 3920);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x224F40u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x10C);
    sb(v0, sp, 0x10D);
    sb(v0, sp, 0x10E);
    sb(s1, sp, 0x10F);
    a0 = addiu(s2, 3920);
    a1 = addiu(sp, 0x10C);
    jal(ctx, 0x224F64u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(a0, sp, 0xEC);
    a1 = 75;
    jal(ctx, 0x224F74u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 287;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, s0, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    lwc1(f1, s0, 4);
    v1 = 0x42FC0000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0xF4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xFC);
    a0 = addiu(s2, 4176);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x224FD0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x10C);
    sb(v0, sp, 0x10D);
    sb(v0, sp, 0x10E);
    sb(s1, sp, 0x10F);
    a0 = addiu(s2, 4176);
    a1 = addiu(sp, 0x10C);
    jal(ctx, 0x224FF4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// 0x00225040 sub_225040 -- 1108 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawList4] draws sub-list 4.
void sub_225040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00225040
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00225078
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x225084u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022508c
    charge(ctx, 74);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x225094u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s7 = v0;
    a0 = 1;
    jal(ctx, 0x2250A4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    fp = v0;
    a0 = 3;
    jal(ctx, 0x2250B4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    sw(v0, sp, 0xAC);
    s0 = addiu(s1, 18016);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x2250D0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x2250E0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = s7;
    a1 = 35;
    jal(ctx, 0x2250F0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s2 = 0x960000;
    s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x225104u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x225118u, v0.u());
    s2 = 0x960000;
    s2 = addiu(s2, 156);  // &0x96009C
    a0 = addiu(s1, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x225140u, v0.u());
    a0 = addiu(s1, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x225160u, v0.u());
    a0 = addiu(s1, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x225180u, v0.u());
    a0 = addiu(s1, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x2251A0u, v0.u());
    s4 = 0;
    for (;;) {
        // 0x0022533c
        charge(ctx, 4);
        lw(v0, s1, 24688);
        v0 = slt(s4, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002251b4
        charge(ctx, 72);
        v0 = sll(s4, 3);
        v1 = subu(v0, s4);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        s5 = addu(s0, v0);
        lw(a0, s5, 768);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x2251D8u, gen::fn_frFontDraw_003b1360);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x2251ECu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2251FCu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = s7;
        a1 = 68;
        jal(ctx, 0x22520Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s3 = 0x960000;
        s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x225220u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x225234u, v0.u());
        s2 = 0x960000;
        s2 = addiu(s2, 156);  // &0x96009C
        a0 = s5;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22525Cu, v0.u());
        a0 = s5;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22527Cu, v0.u());
        a0 = 1;
        jal(ctx, 0x225288u, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22529Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x2252B0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2252C0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s3 = 0;
        for (;;) {  // while (s3 < 2)
            // 0x0022532c
            charge(ctx, 3);
            v0 = slti(s3, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002252d4
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s5, v0);
            s2 = addiu(v0, 256);
            s6 = 0x960000;
            s6 = addiu(s6, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s6, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x225300u, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s6, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x225320u, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00225338
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x0022534c
    charge(ctx, 82);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x225358u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x225368u, gen::fn_RpSkyRenderStateSet_004d7f60);
    lw(a0, sp, 0xAC);
    a1 = 19;
    jal(ctx, 0x225378u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s2 = 0x960000;
    s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x22538Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2253A0u, v0.u());
    s1 = 0x960000;
    s1 = addiu(s1, 156);  // &0x96009C
    a0 = addiu(s0, 3920);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x2253C8u, v0.u());
    a0 = addiu(s0, 3920);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x2253E8u, v0.u());
    a0 = fp;
    a1 = 75;
    jal(ctx, 0x2253F8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x225404u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s2, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x225418u, v0.u());
    a0 = addiu(s0, 4176);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x225438u, v0.u());
    a0 = addiu(s0, 4176);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s1, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x225458u, v0.u());
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

// 0x002255F0 sub_2255F0 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bcmPanel_EnterMenu5] state 5: menu timer 0, flag bit 3, sub-step 0, sub-selection 1.
void sub_2255F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002255f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00225608
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x225614u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022561c
    charge(ctx, 18);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x225624u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    v1 = 5;
    sw(v1, s0, kBcmState);
    sw(zero, s0, kBcmMenuTimer);
    lw(v1, s0, kBcmFlags);
    v1 = v1 | 0x8;
    sw(v1, s0, kBcmFlags);
    sw(zero, s0, kBcmSubStep);
    v1 = 1;
    sw(v1, s0, kBcmSubSel);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00225670 sub_225670 -- 372 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_LayoutScroll] the rows' marks (page 41, 272-byte stride) and the scroll mark (page 29) at
// y 237 + 36 + 55 * top / (total - shown).
void sub_225670(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00225670
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00225694
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x2256A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x002256a8
    charge(ctx, 9);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x2256B0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s3 = v0;
    s0 = addiu(s1, 24704);
    s2 = 0;
    for (;;) {
        // 0x00225700
        charge(ctx, 4);
        lw(v0, s0, 1372);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002256cc
        charge(ctx, 13);
        a0 = s3;
        a1 = 41;
        jal(ctx, 0x2256D4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = sll(s2, 4);
        v1 = addu(v1, s2);
        v1 = sll(v1, 4);
        v1 = addu(s0, v1);
        a0 = addiu(v1, 16);
        a1 = v0;
        jal(ctx, 0x2256F4u, gen::fn_sub_21D3B0_0021d3b0);  // (quad, page): the quad shows the page
        s2 = addiu(s2, 1);
    }
    // 0x00225710
    charge(ctx, 9);
    a0 = s3;
    a1 = 29;
    jal(ctx, 0x225718u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    lw(a1, s0, 1372);
    lw(a0, s0, 1360);
    at = slt(a1, a0);
    if (at == 0) {
        // 0x00225778
        charge(ctx, 2);
        v1 = 0x42100000;
        mtc1(v1, f1);
    } else {
        // 0x00225734
        charge(ctx, 17);
        lwc1(f0, s0, 1368);
        cvt_s_w(f1, f0);
        v1 = 0x425C0000;
        mtc1(v1, f0);
        mul_s(f1, f1, f0);
        v1 = subu(a0, a1);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        v1 = 0x42100000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
    }
    // 0x00225780
    charge(ctx, 25);
    v1 = 0x42700000;
    sw(v1, sp, 0x50);
    v1 = 0x436D0000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x54);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s1, kBcmScrollQuad);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x2257BCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002257F0 sub_2257F0 -- 2116 bytes; frame 0x150: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutStep] lays out the sub-list's step page (the 6-frame fade of sub-step 1 / 2; K_Assert 2528
// for another step).
void sub_2257F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x002257f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00225830
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22583Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00225844
    charge(ctx, 12);
    lw(s4, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22584Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    fp = v0;
    s3 = addiu(s4, 24704);
    lwc1(f21, s4, kBcmFade);
    s2 = addiu(s4, 24664);
    s1 = addiu(s4, 24656);
    lw(v1, s4, kBcmSubStep);
    if (v1 == 0) {
        // 0x002258c0
        charge(ctx, 15);
        lw(v1, s4, kBcmMenuTimer);
        v0 = 6;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40C00000;
        mtc1(v0, f0);
        div_s(f20, f1, f0);
    } else {
        // 0x00225874
        charge(ctx, 3);
        v0 = 2;
        if (v1 != v0) {
            // 0x00225880
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_00225894;
            }
            // 0x0022588c
            charge(ctx, 2);
            // 0x002258fc
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7296);  // "bcm_panel.c"
            a1 = 2528;
            jal(ctx, 0x225908u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 2528): `jr $ra` in retail, execution goes on
            goto L_00225910;
        }
    L_00225894:
        charge(ctx, 11);
        lwc1(f0, s4, 18008);
        cvt_s_w(f1, f0);
        v0 = 0x40C00000;
        mtc1(v0, f0);
        div_s(f20, f1, f0);
    }
L_00225910:
    charge(ctx, 11);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00225954
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022593c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022596c
    charge(ctx, 122);
    v0 = v1 & 0xFF;
    sq(v0, sp, 0xC0);
    a0 = fp;
    a1 = 36;
    jal(ctx, 0x22597Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s2, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    lw(a0, s3, 1364);
    lw(v1, s3, 1368);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s2, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0x134);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x138);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x13C);
    a0 = addiu(s4, 17456);
    a1 = addiu(sp, 0x130);
    jal(ctx, 0x225A00u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = fp;
    a1 = 36;
    jal(ctx, 0x225A10u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s2, 0);
    add_s(f1, f1, f0);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    lw(a0, s3, 1364);
    lw(v1, s3, 1368);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s2, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0x134);
    v1 = 0x438A0000;
    sw(v1, sp, 0x138);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x13C);
    a0 = addiu(s4, 17712);
    a1 = addiu(sp, 0x130);
    jal(ctx, 0x225A9Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x14C);
    sb(v0, sp, 0x14D);
    sb(v0, sp, 0x14E);
    lq(v0, sp, 0xC0);
    sb(v0, sp, 0x14F);
    a0 = addiu(s4, 17456);
    a1 = addiu(sp, 0x14C);
    jal(ctx, 0x225AC4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s4, 17712);
    a1 = addiu(sp, 0x14C);
    jal(ctx, 0x225AD4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s5 = 0;
    lq(v1, sp, 0xC0);
    s0 = v1 & 0xFF;
    v1 = si(-256);
    a0 = s0 | v1;
    sw(a0, sp, 0x110);
    a0 = lui(0xCCCC);
    a0 = a0 | 0xCC00;
    a0 = s0 | a0;
    sw(a0, sp, 0x100);
    a0 = lui(0xBEFF);
    a0 = a0 | 0xD200;
    a0 = s0 | a0;
    sw(a0, sp, 0xF0);
    a0 = 0x64CC0000;
    a0 = a0 | 0x6400;
    a0 = s0 | a0;
    sw(a0, sp, 0xE0);
    a0 = sll(s0, 2);
    a1 = addu(a0, s0);
    a0 = sll(a1, 2);
    a0 = addu(a1, a0);
    a1 = sll(a0, 1);
    a0 = 100;
    div(a1, a0);
    mflo(a0);
    v1 = a0 | v1;
    sw(v1, sp, 0xD0);
    for (;;) {
        // 0x00225d2c
        charge(ctx, 4);
        lw(v1, s3, 1372);
        v1 = slt(s5, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00225b54
        charge(ctx, 43);
        v0 = sll(s5, 4);
        v0 = addu(v0, s5);
        v0 = sll(v0, 4);
        s7 = addu(s3, v0);
        lw(v0, s7, 4);
        sw(v0, sp, 0x120);
        v0 = 0x42CE0000;
        mtc1(v0, f1);
        lwc1(f0, s2, 0);
        add_s(f2, f1, f0);
        swc1(f2, sp, 0x130);
        v0 = sll(s5, 1);
        v0 = addu(v0, s5);
        v0 = sll(v0, 2);
        v0 = addu(v0, s5);
        v0 = sll(v0, 1);
        sq(v0, sp, 0xB0);
        lwc1(f1, s2, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        lq(v0, sp, 0xB0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        swc1(f1, sp, 0x134);
        cvt_w_s(f0, f2);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        cvt_w_s(f0, f1);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        lw(a0, sp, 0x120);
        jal(ctx, 0x225BE8u, gen::fn_frFontLineSetPos_003b0d70);
        lw(v1, s7, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x00225c74
            charge(ctx, 1);
            lw(s6, sp, 0xD0);
        } else {
            // 0x00225c00
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00225c48
                charge(ctx, 5);
                lw(v1, s3, 1364);
                lw(v0, s3, 1368);
                v0 = subu(v1, v0);
                if (s5 != v0) {
                    // 0x00225c68
                    charge(ctx, 3);
                    lw(s6, sp, 0xE0);
                } else {
                    // 0x00225c5c
                    charge(ctx, 3);
                    lw(s6, sp, 0xF0);
                }
            } else {
                // 0x00225c0c
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00225c1c
                    charge(ctx, 5);
                    lw(v1, s3, 1364);
                    lw(v0, s3, 1368);
                    v0 = subu(v1, v0);
                    if (s5 != v0) {
                        // 0x00225c3c
                        charge(ctx, 3);
                        lw(s6, sp, 0x100);
                    } else {
                        // 0x00225c30
                        charge(ctx, 3);
                        lw(s6, sp, 0x110);
                    }
                } else {
                    // 0x00225c14
                    charge(ctx, 2);
                }
            }
        }
        // 0x00225c78
        charge(ctx, 45);
        lw(a0, sp, 0x120);
        a1 = s6;
        jal(ctx, 0x225C80u, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = fp;
        a1 = 41;
        jal(ctx, 0x225C90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x42AC0000;
        mtc1(v1, f1);
        lwc1(f0, s2, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x130);
        lwc1(f1, s2, 4);
        v1 = 0x41E80000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        lq(v1, sp, 0xB0);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x134);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x138);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x13C);
        a0 = addiu(s7, 16);
        a1 = addiu(sp, 0x130);
        jal(ctx, 0x225CF8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0x14C);
        sb(v0, sp, 0x14D);
        sb(v0, sp, 0x14E);
        lq(v0, sp, 0xC0);
        sb(v0, sp, 0x14F);
        a0 = addiu(s7, 16);
        a1 = addiu(sp, 0x14C);
        jal(ctx, 0x225D20u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s5 = addiu(s5, 1);
    }
    // 0x00225d3c
    charge(ctx, 4);
    lw(a0, s4, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x00225d54
        charge(ctx, 4);
        lw(v1, s4, 17988);
        a1 = 2;
        if (v1 != a1) {
            // 0x00225d64
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                goto L_00225edc;
            }
            // 0x00225d70
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00225d80
                charge(ctx, 3);
                lw(v1, s4, 17992);
                if (v1 != a0) {
                    // 0x00225d8c
                    charge(ctx, 2);
                    if (v1 == a1) {
                        goto L_00225d94;
                    }
                    // 0x00225ff8 (the shared epilogue, written out on this path)
                    charge(ctx, 15);
                    ld(ra, sp, 0xA0);
                    lq(fp, sp, 0x90);
                    lq(s7, sp, 0x80);
                    lq(s6, sp, 0x70);
                    lq(s5, sp, 0x60);
                    lq(s4, sp, 0x50);
                    lq(s3, sp, 0x40);
                    lq(s2, sp, 0x30);
                    lq(s1, sp, 0x20);
                    lq(s0, sp, 0x10);
                    lwc1(f21, sp, 0x4);
                    lwc1(f20, sp, 0x0);
                    sp = addiu(sp, 0x150);
                    return;
                }
            L_00225d94:
                charge(ctx, 4);
                lw(v1, s4, 18008);
                at = slti(v1, 6);
                if (at != 0) {
                    // 0x00225da4
                    charge(ctx, 4);
                    lw(v0, s4, 4);
                    v0 = v0 & 0x4;
                    if (v0 == 0) {
                        // 0x00225db4
                        charge(ctx, 5);
                        a0 = 0x690000;
                        a0 = addiu(a0, -7296);  // "bcm_panel.c"
                        a1 = 2616;
                        jal(ctx, 0x225DC0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 2616): `jr $ra` in retail, execution goes on
                    }
                    // 0x00225dc8
                    charge(ctx, 32);
                    lw(s2, s3, 1376);
                    v0 = lui(0xFF9D);
                    v0 = v0 | 0x9D00;
                    a1 = s0 | v0;
                    a0 = s2;
                    jal(ctx, 0x225DDCu, gen::fn_frFontLineSetRgba_003b0e20);
                    v0 = 0x432B0000;
                    mtc1(v0, f1);
                    lwc1(f0, s1, 0);
                    add_s(f2, f1, f0);
                    swc1(f2, sp, 0x130);
                    lwc1(f1, s1, 4);
                    v0 = 0x41980000;
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    swc1(f1, sp, 0x134);
                    cvt_w_s(f0, f2);
                    mfc1(v0, f0);
                    a1 = sll(v0, 4);
                    cvt_w_s(f0, f1);
                    mfc1(v0, f0);
                    a2 = sll(v0, 3);
                    a0 = s2;
                    jal(ctx, 0x225E34u, gen::fn_frFontLineSetPos_003b0d70);
                    lw(s2, s3, 1380);
                    if (s2 != 0) {
                        // 0x00225e48
                        charge(ctx, 37);
                        v0 = si(-256);
                        a1 = s0 | v0;
                        a0 = s2;
                        jal(ctx, 0x225E54u, gen::fn_frFontLineSetRgba_003b0e20);
                        v0 = 0x432B0000;
                        mtc1(v0, f1);
                        lwc1(f0, s1, 0);
                        add_s(f1, f1, f0);
                        v0 = 0x41D80000;
                        mtc1(v0, f0);
                        add_s(f2, f0, f1);
                        swc1(f2, sp, 0x130);
                        lwc1(f1, s1, 4);
                        v0 = 0x41980000;
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x41D00000;
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        swc1(f1, sp, 0x134);
                        cvt_w_s(f0, f2);
                        mfc1(v0, f0);
                        a1 = sll(v0, 4);
                        cvt_w_s(f0, f1);
                        mfc1(v0, f0);
                        a2 = sll(v0, 3);
                        a0 = s2;
                        jal(ctx, 0x225ECCu, gen::fn_frFontLineSetPos_003b0d70);
                    }
                }
            } else {
                // 0x00225d78
                charge(ctx, 2);
            }
            // 0x00225ff8 (the shared epilogue, written out on this path)
            charge(ctx, 15);
            ld(ra, sp, 0xA0);
            lq(fp, sp, 0x90);
            lq(s7, sp, 0x80);
            lq(s6, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x150);
            return;
        }
    L_00225edc:
        charge(ctx, 36);
        lw(s2, s3, 1376);
        v0 = lui(0xFF9D);
        v0 = v0 | 0x9D00;
        a1 = s0 | v0;
        a0 = s2;
        jal(ctx, 0x225EF0u, gen::fn_frFontLineSetRgba_003b0e20);
        v0 = 0x432B0000;
        mtc1(v0, f1);
        lwc1(f0, s1, 0);
        add_s(f2, f1, f0);
        swc1(f2, sp, 0x130);
        lwc1(f1, s1, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        swc1(f1, sp, 0x134);
        v0 = 0x41800000;
        mtc1(v0, f0);
        mul_s(f0, f0, f2);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = 0x41000000;
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        a0 = s2;
        jal(ctx, 0x225F58u, gen::fn_frFontLineSetPos_003b0d70);
        lw(s2, s3, 1380);
        if (s2 != 0) {
            // 0x00225f6c
            charge(ctx, 35);
            v0 = si(-256);
            a1 = s0 | v0;
            a0 = s2;
            jal(ctx, 0x225F78u, gen::fn_frFontLineSetRgba_003b0e20);
            v0 = 0x432B0000;
            mtc1(v0, f1);
            lwc1(f0, s1, 0);
            add_s(f1, f1, f0);
            v0 = 0x41D80000;
            mtc1(v0, f0);
            add_s(f2, f0, f1);
            swc1(f2, sp, 0x130);
            lwc1(f1, s1, 4);
            v0 = 0x41980000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x41D00000;
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            swc1(f1, sp, 0x134);
            cvt_w_s(f0, f2);
            mfc1(v0, f0);
            a1 = sll(v0, 4);
            cvt_w_s(f0, f1);
            mfc1(v0, f0);
            a2 = sll(v0, 3);
            a0 = s2;
            jal(ctx, 0x225FF0u, gen::fn_frFontLineSetPos_003b0d70);
        }
    } else {
        // 0x00225d4c
        charge(ctx, 2);
    }
    // 0x00225ff8 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x00226040 sub_226040 -- 724 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawStep] draws the step page.
void sub_226040(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00226040
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00226070
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22607Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00226084
    charge(ctx, 57);
    lw(s3, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22608Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    s2 = addiu(s3, 24704);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x2260A4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x2260B8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2260CCu, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s3, 17456);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x2260F4u, v0.u());
    a0 = addiu(s3, 17456);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x226114u, v0.u());
    a0 = addiu(s3, 17712);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x226134u, v0.u());
    a0 = addiu(s3, 17712);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x226154u, v0.u());
    s4 = 0;
    for (;;) {
        // 0x0022622c
        charge(ctx, 4);
        lw(a0, s2, 1372);
        v1 = slt(s4, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00226168
        charge(ctx, 49);
        v0 = sll(s4, 4);
        v0 = addu(v0, s4);
        v0 = sll(v0, 4);
        s0 = addu(s2, v0);
        lw(a0, s0, 4);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x226184u, gen::fn_frFontDraw_003b1360);
        a0 = s5;
        a1 = 41;
        jal(ctx, 0x226194u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2261A0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x2261B4u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x2261C8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2261D8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s6 = 0x960000;
        s6 = addiu(s6, 156);  // &0x96009C
        a0 = addiu(s0, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s6, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x226200u, v0.u());
        a0 = addiu(s0, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s6, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x226220u, v0.u());
        s4 = addiu(s4, 1);
    }
    // 0x0022623c
    charge(ctx, 4);
    lw(v1, s2, 1360);
    at = slt(a0, v1);
    if (at != 0) {
        // 0x0022624c
        charge(ctx, 39);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x226258u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x226268u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = s5;
        a1 = 29;
        jal(ctx, 0x226278u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x226284u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x226298u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s3, kBcmScrollQuad);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2262C0u, v0.u());
        a0 = addiu(s3, kBcmScrollQuad);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2262E0u, v0.u());
    }
    // 0x002262e8 (the shared epilogue, written out on this path)
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

// 0x002265D0 sub_2265D0 -- 4648 bytes; frame 0xA0: ra sp+0x70, s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutFrame] lays out the panel frame's quads (sweeping with the sub-list state and its timers,
// +29200 the frame mode).
void sub_2265D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28};
    // 0x002265d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00226618
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x226624u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022662c
    charge(ctx, 19);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x226634u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s3 = v0;
    lwc1(f26, s1, kBcmFade);
    lwc1(f0, s1, 29200);
    v0 = lui(0xC1D0);
    mtc1(v0, f2);
    cvt_s_w(f1, f0);
    mul_s(f28, f2, f1);
    v0 = 0x41D00000;
    mtc1(v0, f0);
    mul_s(f27, f0, f1);
    lw(v0, s1, kBcmSub);
    v1 = 3;
    if (v0 == v1) {
        // 0x00226778
        charge(ctx, 3);
        lw(a0, s1, kBcmSubStep);
        if (a0 == 0) {
            // 0x00226808
            charge(ctx, 4);
            lw(a0, s1, kBcmSubSel);
            v1 = 1;
            if (a0 != v1) {
                // 0x00226818
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_00226824;
                }
            L_0022689c:
                charge(ctx, 22);
                lwc1(f0, s1, 18000);
                v1 = 0x42180000;
                mtc1(v1, f1);
                cvt_s_w(f2, f0);
                mul_s(f0, f1, f2);
                v1 = 0x40400000;
                mtc1(v1, f1);
                div_s(f0, f0, f1);
                swc1(f0, sp, 0x90);
                v1 = lui(0xC220);
                mtc1(v1, f0);
                mul_s(f0, f0, f2);
                div_s(f1, f0, f1);
                v1 = 277;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x94);
                goto L_002268f4;
            }
        L_00226824:
            charge(ctx, 4);
            lw(v1, s1, 18008);
            at = slti(v1, 6);
            if (at == 0) {
                goto L_0022689c;
            }
            // 0x00226834
            charge(ctx, 26);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            div_s(f21, f1, f0);
            v1 = 0x433F0000;
            mtc1(v1, f1);
            v1 = lui(0xC319);
            mtc1(v1, f0);
            mtc1(zero, f2);
            adda_s(f2, f0);
            madd_s(f0, f1, f21);
            swc1(f0, sp, 0x90);
            v1 = 0x42840000;
            mtc1(v1, f1);
            v1 = 0x432B0000;
            mtc1(v1, f0);
            adda_s(f2, f0);
            madd_s(f0, f1, f21);
            swc1(f0, sp, 0x94);
        } else {
            // 0x00226784
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x00226790
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    goto L_002267a4;
                }
                // 0x0022679c
                charge(ctx, 2);
                goto L_002268f4;
            }
        L_002267a4:
            charge(ctx, 25);
            lwc1(f0, s1, 18008);
            cvt_s_w(f1, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            div_s(f21, f1, f0);
            v1 = lui(0xC33F);
            mtc1(v1, f1);
            v1 = 0x42180000;
            mtc1(v1, f0);
            mtc1(zero, f2);
            adda_s(f2, f0);
            madd_s(f0, f1, f21);
            swc1(f0, sp, 0x90);
            v1 = lui(0xC284);
            mtc1(v1, f1);
            v1 = 0x436D0000;
            mtc1(v1, f0);
            adda_s(f2, f0);
            madd_s(f0, f1, f21);
            swc1(f0, sp, 0x94);
        }
    } else {
        // 0x00226678
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0022670c
            charge(ctx, 27);
            lwc1(f0, s1, kBcmSubTimer);
            v1 = lui(0xC218);
            mtc1(v1, f1);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x40400000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 0x42180000;
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x90);
            v1 = 0x42200000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x436D0000;
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x94);
        } else {
            // 0x00226680
            charge(ctx, 3);
            v1 = 4;
            if (v0 != v1) {
                // 0x0022668c
                charge(ctx, 3);
                v1 = 1;
                if (v0 == v1) {
                    goto L_002266ac;
                }
                // 0x00226698
                charge(ctx, 3);
                v1 = 2;
                if (v0 == v1) {
                    goto L_002266ac;
                }
                // 0x002266a4
                charge(ctx, 2);
                goto L_002268f4;
            }
        L_002266ac:
            charge(ctx, 24);
            lwc1(f0, s1, 18000);
            v1 = 0x42180000;
            mtc1(v1, f1);
            cvt_s_w(f2, f0);
            mul_s(f0, f1, f2);
            v1 = 0x40400000;
            mtc1(v1, f1);
            div_s(f0, f0, f1);
            swc1(f0, sp, 0x90);
            v1 = lui(0xC220);
            mtc1(v1, f0);
            mul_s(f0, f0, f2);
            div_s(f1, f0, f1);
            v1 = 277;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x94);
        }
    }
L_002268f4:
    charge(ctx, 3);
    a0 = 3;
    if (v0 == a0) {
        // 0x00226984
        charge(ctx, 11);
        lwc1(f0, s1, 18000);
        cvt_s_w(f1, f0);
        v1 = 0x40400000;
        mtc1(v1, f0);
        div_s(f20, f1, f0);
        lw(a0, s1, 17988);
        if (a0 != 0) {
            // 0x002269b0
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x002269bc
                charge(ctx, 1);
                v1 = 1;
            }
        }
    } else {
        // 0x00226900
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x00226960
            charge(ctx, 9);
            lw(v1, s1, 18000);
            v1 = subu(a0, v1);
            div(v1, a0);
            mflo(v1);
            mtc1(v1, f0);
            cvt_s_w(f20, f0);
        } else {
            // 0x00226908
            charge(ctx, 3);
            v1 = 4;
            if (v0 != v1) {
                // 0x00226914
                charge(ctx, 3);
                v1 = 1;
                if (v0 == v1) {
                    goto L_00226934;
                }
                // 0x00226920
                charge(ctx, 3);
                v1 = 2;
                if (v0 == v1) {
                    goto L_00226934;
                }
                // 0x0022692c
                charge(ctx, 2);
                goto L_002269c0;
            }
        L_00226934:
            charge(ctx, 11);
            lwc1(f0, s1, 18000);
            cvt_s_w(f1, f0);
            v1 = 0x40400000;
            mtc1(v1, f0);
            div_s(f20, f1, f0);
        }
    }
L_002269c0:
    charge(ctx, 3);
    v1 = 3;
    if (v0 == v1) {
        // 0x002269d4
        charge(ctx, 3);
        lw(v1, s1, 17988);
        if (v1 == 0) {
            // 0x00226a3c
            charge(ctx, 4);
            lw(v1, s1, 17992);
            v0 = 1;
            if (v1 != v0) {
                // 0x00226a4c
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_00226a58;
                }
            L_00226a98:
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f21);
                goto L_00226ab0;
            }
        L_00226a58:
            charge(ctx, 4);
            lw(v0, s1, 18008);
            at = slti(v0, 6);
            if (at == 0) {
                goto L_00226a98;
            }
            // 0x00226a68
            charge(ctx, 12);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            div_s(f21, f1, f0);
        } else {
            // 0x002269e0
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x002269ec
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_00226a00;
                }
                // 0x002269f8
                charge(ctx, 2);
                goto L_00226ab0;
            }
        L_00226a00:
            charge(ctx, 15);
            lw(v1, s1, 18008);
            v0 = 6;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            div_s(f21, f1, f0);
        }
    } else {
        // 0x002269cc
        charge(ctx, 2);
        // 0x00226aa8
        charge(ctx, 2);
        v0 = 0x3F800000;
        mtc1(v0, f21);
    }
L_00226ab0:
    charge(ctx, 24);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    sub_s(f3, f0, f21);
    neg_s(f2, f28);
    lwc1(f1, sp, 0x94);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f0, f3, f2);
    swc1(f0, sp, 0x94);
    add_s(f25, f0, f28);
    swc1(f25, sp, 0x94);
    lwc1(f1, sp, 0x90);
    lwc1(f0, sp, 0x94);
    swc1(f1, s1, 24656);
    swc1(f0, s1, 24660);
    s0 = 0;
    v0 = 0x42960000;
    mtc1(v0, f0);
    add_s(f22, f0, f27);
    for (;;) {  // while (s0 < 9)
        // 0x00226d98
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00226b10
        charge(ctx, 3);
        at = sltiu(s0, 6);
        if (at != 0) {
            // 0x00226b1c
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30400);  // "8k\""
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x226B38u:  // table[0, 1, 2, 3]
                // 0x00226b38
                charge(ctx, 7);
                a1 = addiu(s0, 30);
                a0 = s3;
                jal(ctx, 0x226B40u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s2 = v0;
                break;
            case 0x226B54u:  // table[4, 5]
                // 0x00226b54
                charge(ctx, 5);
                a1 = addiu(s0, 26);
                a0 = s3;
                jal(ctx, 0x226B5Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s2 = v0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00226b68
        charge(ctx, 5);
        lwc1(f1, sp, 0x90);
        mov_s(f0, f25);
        at = sltiu(s0, 9);
        if (at != 0) {
            // 0x00226b7c
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30352);  // &0x7B7690
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x226B98u:  // table[0]
                // 0x00226b98
                charge(ctx, 10);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                add_s(f0, f25, f0);
                break;
            case 0x226BC0u:  // table[1]
                // 0x00226bc0
                charge(ctx, 7);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                add_s(f0, f25, f22);
                break;
            case 0x226BDCu:  // table[2]
                // 0x00226bdc
                charge(ctx, 10);
                v0 = 0x43710000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                add_s(f0, f25, f0);
                break;
            case 0x226C04u:  // table[3]
                // 0x00226c04
                charge(ctx, 7);
                v0 = 0x43710000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                add_s(f0, f25, f22);
                break;
            case 0x226C20u:  // table[4]
                // 0x00226c20
                charge(ctx, 10);
                v0 = 0x431F0000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                add_s(f0, f25, f0);
                break;
            case 0x226C48u:  // table[5]
                // 0x00226c48
                charge(ctx, 7);
                v0 = 0x431F0000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                add_s(f0, f25, f22);
                break;
            case 0x226C64u:  // table[6]
                // 0x00226c64
                charge(ctx, 10);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                v0 = 0x42960000;
                mtc1(v0, f0);
                add_s(f0, f25, f0);
                break;
            case 0x226C8Cu:  // table[7]
                // 0x00226c8c
                charge(ctx, 10);
                v0 = 0x43710000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                v0 = 0x42960000;
                mtc1(v0, f0);
                add_s(f0, f25, f0);
                break;
            case 0x226CB4u:  // table[8]
                // 0x00226cb4
                charge(ctx, 8);
                v0 = 0x431F0000;
                mtc1(v0, f0);
                add_s(f1, f1, f0);
                v0 = 0x42960000;
                mtc1(v0, f0);
                add_s(f0, f25, f0);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00226cd4
        charge(ctx, 3);
        at = sltiu(s0, 9);
        if (at != 0) {
            // 0x00226ce0
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30304);  // &0x7B7660
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x226CFCu:  // table[0, 1, 2, 3]
                // 0x00226cfc
                charge(ctx, 10);
                swc1(f1, sp, 0x80);
                swc1(f0, sp, 0x84);
                lwc1(f0, s2, 12);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x88);
                lwc1(f0, s2, 16);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x8C);
                break;
            case 0x226D24u:  // table[4, 5]
                // 0x00226d24
                charge(ctx, 9);
                swc1(f1, sp, 0x80);
                swc1(f0, sp, 0x84);
                v0 = 0x42A40000;
                sw(v0, sp, 0x88);
                lwc1(f0, s2, 16);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x8C);
                break;
            case 0x226D48u:  // table[6, 7]
                // 0x00226d48
                charge(ctx, 8);
                swc1(f1, sp, 0x80);
                swc1(f0, sp, 0x84);
                lwc1(f0, s2, 12);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x88);
                swc1(f27, sp, 0x8C);
                break;
            case 0x226D68u:  // table[8]
                // 0x00226d68
                charge(ctx, 5);
                swc1(f1, sp, 0x80);
                swc1(f0, sp, 0x84);
                v0 = 0x42A40000;
                sw(v0, sp, 0x88);
                swc1(f27, sp, 0x8C);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00226d7c
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 5424);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x226D8Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s0 = addiu(s0, 1);
    }
    // 0x00226da4
    charge(ctx, 4);
    lw(v1, s1, 17980);
    v0 = 3;
    if (v1 == v0) {
        // 0x00226dbc
        charge(ctx, 3);
        lw(v1, s1, 17988);
        if (v1 == 0) {
            // 0x00226e24
            charge(ctx, 4);
            lw(v1, s1, 17992);
            v0 = 1;
            if (v1 != v0) {
                // 0x00226e34
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_00226e40;
                }
            L_00226e80:
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f21);
                goto L_00226e98;
            }
        L_00226e40:
            charge(ctx, 4);
            lw(v0, s1, 18008);
            at = slti(v0, 6);
            if (at == 0) {
                goto L_00226e80;
            }
            // 0x00226e50
            charge(ctx, 12);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            div_s(f21, f1, f0);
        } else {
            // 0x00226dc8
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x00226dd4
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_00226de8;
                }
                // 0x00226de0
                charge(ctx, 2);
                goto L_00226e98;
            }
        L_00226de8:
            charge(ctx, 15);
            lw(v1, s1, 18008);
            v0 = 6;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            div_s(f21, f1, f0);
        }
    } else {
        // 0x00226db4
        charge(ctx, 2);
        // 0x00226e90
        charge(ctx, 2);
        v0 = 0x3F800000;
        mtc1(v0, f21);
    }
L_00226e98:
    charge(ctx, 14);
    v0 = 0x43570000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x42200000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00226ee8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00226ed0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00226f00
    charge(ctx, 7);
    sb(v1, sp, 0x9C);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00226f34
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00226f1c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00226f4c
    charge(ctx, 15);
    sb(v1, sp, 0x9D);
    v0 = 0x43610000;
    mtc1(v0, f2);
    v0 = 0x41F00000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00226fa0
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00226f88
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00226fb8
    charge(ctx, 25);
    sb(v1, sp, 0x9E);
    v0 = 0x41A00000;
    mtc1(v0, f2);
    v0 = 0x42A00000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f21);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    v0 = 0x42C80000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    mul_s(f0, f0, f20);
    mul_s(f1, f26, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00227034
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022701c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022704c
    charge(ctx, 4);
    sb(v1, sp, 0x9F);
    s0 = 0;
    for (;;) {  // while (s0 < 9)
        // 0x00227078
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022705c
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 5424);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x22706Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = addiu(s0, 1);
    }
    // 0x00227084
    charge(ctx, 103);
    a0 = s3;
    a1 = 38;
    jal(ctx, 0x22708Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x41A00000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x90);
    add_s(f24, f1, f0);
    swc1(f24, sp, 0x80);
    lwc1(f23, sp, 0x94);
    v1 = 0x42000000;
    mtc1(v1, f0);
    add_s(f22, f0, f23);
    v1 = 0x40400000;
    mtc1(v1, f0);
    sub_s(f0, f22, f0);
    swc1(f0, sp, 0x84);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 7728);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x2270F0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s3;
    a1 = 39;
    jal(ctx, 0x227100u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f24, sp, 0x80);
    v1 = 0x42CC0000;
    mtc1(v1, f0);
    add_s(f0, f0, f23);
    add_s(f0, f0, f27);
    swc1(f0, sp, 0x84);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 7984);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x227144u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s3;
    a1 = 38;
    jal(ctx, 0x227154u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f24, sp, 0x80);
    v1 = 0x41800000;
    mtc1(v1, f0);
    add_s(f1, f0, f22);
    v1 = 0x40400000;
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x84);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    v0 = 0x42640000;
    mtc1(v0, f0);
    add_s(f0, f0, f27);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 8240);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x2271ACu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s3;
    a1 = 29;
    jal(ctx, 0x2271BCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x42100000;
    mtc1(v1, f0);
    add_s(f0, f0, f23);
    add_s(f1, f0, f28);
    v1 = 0x40400000;
    mtc1(v1, f0);
    sub_s(f3, f1, f0);
    v1 = 0x42B60000;
    mtc1(v1, f0);
    add_s(f0, f0, f23);
    add_s(f2, f0, f28);
    v1 = 0x41B00000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x90);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    lw(v1, s1, 24692);
    at = slti(v1, 5);
    if (at != 0) {
        // 0x00227258
        charge(ctx, 1);
        swc1(f3, sp, 0x84);
    } else {
        // 0x00227220
        charge(ctx, 14);
        lwc1(f0, s1, 24684);
        cvt_s_w(f1, f0);
        sub_s(f0, f2, f3);
        mul_s(f1, f1, f0);
        v1 = addiu(v1, -4);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        add_s(f0, f3, f0);
        swc1(f0, sp, 0x84);
    }
    // 0x0022725c
    charge(ctx, 25);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 8496);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x22727Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x9C);
    sb(v0, sp, 0x9D);
    sb(v0, sp, 0x9E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002272d8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002272c0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002272f0
    charge(ctx, 4);
    sb(v1, sp, 0x9F);
    s0 = 0;
    for (;;) {  // while (s0 < 3)
        // 0x0022731c
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00227300
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 7728);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x227310u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = addiu(s0, 1);
    }
    // 0x00227328
    charge(ctx, 20);
    a0 = addiu(s1, 8496);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x227330u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s3;
    a1 = 44;
    jal(ctx, 0x227340u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s0 = v0;
    s2 = 0;
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x90);
    add_s(f24, f1, f0);
    v1 = 0x422C0000;
    mtc1(v1, f0);
    add_s(f23, f0, f25);
    for (;;) {  // while (s2 < 6)
        // 0x0022741c
        charge(ctx, 3);
        v1 = slti(s2, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00227378
        charge(ctx, 41);
        swc1(f24, sp, 0x80);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        v0 = addu(v0, s2);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f22, f23, f0);
        swc1(f22, sp, 0x84);
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        lwc1(f0, s0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        v0 = sll(s2, 9);
        s3 = addu(s1, v0);
        a0 = addiu(s3, 8752);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x2273CCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        add_s(f0, f24, f0);
        swc1(f0, sp, 0x80);
        swc1(f22, sp, 0x84);
        v0 = 311;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        lwc1(f0, s0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s3, 9008);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x227410u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s2 = addiu(s2, 1);
    }
    // 0x00227428
    charge(ctx, 4);
    lw(a0, s1, 17980);
    v1 = 3;
    if (a0 == v1) {
        // 0x00227460
        charge(ctx, 3);
        lw(a0, s1, 17988);
        if (a0 == 0) {
            // 0x002274c8
            charge(ctx, 4);
            lw(a0, s1, 17992);
            v1 = 1;
            if (a0 != v1) {
                // 0x002274d8
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_002274e4;
                }
            L_00227524:
                charge(ctx, 2);
                v1 = 0x3F800000;
                mtc1(v1, f21);
                goto L_0022752c;
            }
        L_002274e4:
            charge(ctx, 4);
            lw(v1, s1, 18008);
            at = slti(v1, 6);
            if (at == 0) {
                goto L_00227524;
            }
            // 0x002274f4
            charge(ctx, 12);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            div_s(f21, f1, f0);
        } else {
            // 0x0022746c
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x00227478
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    goto L_0022748c;
                }
                // 0x00227484
                charge(ctx, 2);
                goto L_0022752c;
            }
        L_0022748c:
            charge(ctx, 15);
            lw(a0, s1, 18008);
            v1 = 6;
            v1 = subu(v1, a0);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            div_s(f21, f1, f0);
        }
    } else {
        // 0x00227438
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x00227440
            charge(ctx, 3);
            v1 = 1;
            if (a0 != v1) {
                // 0x0022744c
                charge(ctx, 3);
                v1 = 2;
                if (a0 != v1) {
                    // 0x00227458
                    charge(ctx, 2);
                }
            }
        }
    }
L_0022752c:
    charge(ctx, 14);
    v1 = 0x43610000;
    mtc1(v1, f2);
    v1 = 0x41F00000;
    mtc1(v1, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f21);
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0022757c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
        a0 = a0 & 0xFF;
    } else {
        // 0x00227564
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(a0, f0);
        a0 = a0 & 0xFF;
    }
    // 0x00227594
    charge(ctx, 7);
    a1 = a0 & 0xFF;
    v1 = 255;
    sb(v1, sp, 0x9C);
    sb(v1, sp, 0x9D);
    sb(v1, sp, 0x9E);
    if (i64(a1) < 0) {
        // 0x002275c4
        charge(ctx, 7);
        a0 = srl(a1, 1);
        v1 = a1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002275b0
        charge(ctx, 5);
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x002275e0
    charge(ctx, 8);
    mul_s(f0, f20, f0);
    mul_s(f1, f26, f0);
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00227618
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
        a0 = a0 & 0xFF;
    } else {
        // 0x00227600
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(a0, f0);
        a0 = a0 & 0xFF;
    }
    // 0x00227630
    charge(ctx, 4);
    sb(a0, sp, 0x9F);
    s2 = 0;
    for (;;) {  // while (s2 < 2)
        // 0x0022766c
        charge(ctx, 3);
        v1 = slti(s2, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00227640
        charge(ctx, 11);
        v0 = sll(s2, 9);
        s0 = addu(s1, v0);
        a0 = addiu(s0, 8752);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x227650u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s0, 9008);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x227660u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s2 = addiu(s2, 1);
    }
    // 0x00227678
    charge(ctx, 10);
    v1 = 0x437F0000;
    mtc1(v1, f0);
    mul_s(f1, f0, f21);
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002276b8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
        a0 = a0 & 0xFF;
    } else {
        // 0x002276a0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(a0, f0);
        a0 = a0 & 0xFF;
    }
    // 0x002276d0
    charge(ctx, 7);
    a1 = a0 & 0xFF;
    v1 = 255;
    sb(v1, sp, 0x9C);
    sb(v1, sp, 0x9D);
    sb(v1, sp, 0x9E);
    if (i64(a1) < 0) {
        // 0x00227700
        charge(ctx, 7);
        a0 = srl(a1, 1);
        v1 = a1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x002276ec
        charge(ctx, 5);
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0022771c
    charge(ctx, 8);
    mul_s(f0, f20, f0);
    mul_s(f1, f26, f0);
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00227754
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
        a0 = a0 & 0xFF;
    } else {
        // 0x0022773c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(a0, f0);
        a0 = a0 & 0xFF;
    }
    // 0x0022776c
    charge(ctx, 4);
    sb(a0, sp, 0x9F);
    s2 = 2;
    for (;;) {  // while (s2 < 6)
        // 0x002277a8
        charge(ctx, 3);
        v1 = slti(s2, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022777c
        charge(ctx, 11);
        v0 = sll(s2, 9);
        s0 = addu(s1, v0);
        a0 = addiu(s0, 8752);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x22778Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s0, 9008);
        a1 = addiu(sp, 0x9C);
        jal(ctx, 0x22779Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s2 = addiu(s2, 1);
    }
    // 0x002277b4
    charge(ctx, 17);
    ld(ra, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00227800 sub_227800 -- 1288 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawFrame] draws the panel frame (jump table on the frame mode).
void sub_227800(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00227800
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00227830
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22783Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00227844
    charge(ctx, 17);
    lw(s3, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22784Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x227864u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x227874u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s0 = 0;
    for (;;) {  // while (s0 < 9)
        // 0x002279b0
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00227888
        charge(ctx, 3);
        at = sltiu(s0, 9);
        if (at != 0) {
            // 0x00227894
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30432);  // &0x7B76E0
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2278B0u:  // table[0, 1, 2, 3]
                // 0x002278b0
                charge(ctx, 7);
                a1 = addiu(s0, 30);
                a0 = s2;
                jal(ctx, 0x2278B8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s1 = v0;
                break;
            case 0x2278CCu:  // table[4, 5]
                // 0x002278cc
                charge(ctx, 7);
                a1 = addiu(s0, 26);
                a0 = s2;
                jal(ctx, 0x2278D4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s1 = v0;
                break;
            case 0x2278E8u:  // table[6]
                // 0x002278e8
                charge(ctx, 7);
                a0 = s2;
                a1 = 31;
                jal(ctx, 0x2278F0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s1 = v0;
                break;
            case 0x227904u:  // table[7]
                // 0x00227904
                charge(ctx, 7);
                a0 = s2;
                a1 = 33;
                jal(ctx, 0x22790Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s1 = v0;
                break;
            case 0x227920u:  // table[8]
                // 0x00227920
                charge(ctx, 5);
                a0 = s2;
                a1 = 31;
                jal(ctx, 0x227928u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s1 = v0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00227934
        charge(ctx, 31);
        a0 = s1;
        jal(ctx, 0x227938u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        v0 = 0x960000;
        lw(v0, v0, 144);  // pfn_RwRenderStateSet
        jalr(ctx, 0x227950u, v0.u());
        v0 = sll(s0, 8);
        v0 = addu(s3, v0);
        s4 = addiu(v0, 5424);
        s6 = 0x960000;
        s6 = addiu(s6, 156);  // &0x96009C
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s6, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x227984u, v0.u());
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s6, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2279A4u, v0.u());
        s0 = addiu(s0, 1);
    }
    // 0x002279bc
    charge(ctx, 93);
    a0 = s2;
    a1 = 38;
    jal(ctx, 0x2279C4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s1 = v0;
    s4 = 0x960000;
    s4 = addiu(s4, 144);  // &pfn_RwRenderStateSet
    a0 = s1;
    jal(ctx, 0x2279DCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s4, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2279F0u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s3, 7728);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x227A18u, v0.u());
    a0 = addiu(s3, 7728);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x227A38u, v0.u());
    a0 = s2;
    a1 = 39;
    jal(ctx, 0x227A48u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x227A54u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s4, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x227A68u, v0.u());
    a0 = addiu(s3, 7984);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x227A88u, v0.u());
    a0 = addiu(s3, 7984);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x227AA8u, v0.u());
    a0 = s2;
    a1 = 38;
    jal(ctx, 0x227AB8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x227AC4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s4, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x227AD8u, v0.u());
    a0 = addiu(s3, 8240);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x227AF8u, v0.u());
    a0 = addiu(s3, 8240);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x227B18u, v0.u());
    lw(v1, s3, kBcmSub);
    v0 = 3;
    if (v1 != v0) {
        // 0x00227b30
        charge(ctx, 4);
        lw(v0, s3, 24692);
        at = slti(v0, 5);
        if (at == 0) {
            // 0x00227b40
            charge(ctx, 28);
            a0 = s2;
            a1 = 29;
            jal(ctx, 0x227B48u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x227B54u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s4, 0);
            jalr(ctx, 0x227B68u, v0.u());
            a0 = addiu(s3, 8496);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);
            jalr(ctx, 0x227B88u, v0.u());
            a0 = addiu(s3, 8496);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);
            jalr(ctx, 0x227BA8u, v0.u());
        }
    }
    // 0x00227bb0
    charge(ctx, 16);
    a0 = s2;
    a1 = 44;
    jal(ctx, 0x227BB8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x227BC4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s4, 0);
    jalr(ctx, 0x227BD8u, v0.u());
    lw(a0, s3, 29200);
    v1 = 2;
    if (a0 == v1) {
        // 0x00227c24
        charge(ctx, 1);
        s5 = 6;
    } else {
        // 0x00227bf0
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x00227c18
            charge(ctx, 3);
            s5 = 5;
        } else {
            // 0x00227bfc
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00227c0c
                charge(ctx, 3);
                s5 = 4;
            } else {
                // 0x00227c04
                charge(ctx, 2);
            }
        }
    }
    // 0x00227c28
    charge(ctx, 3);
    s2 = 0;
    for (;;) {  // while (s2 < s5)
        // 0x00227cd0
        charge(ctx, 3);
        v1 = slt(s2, s5);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00227c34
        charge(ctx, 39);
        v0 = sll(s2, 9);
        s1 = addu(s3, v0);
        s4 = addiu(s1, 8752);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x227C60u, v0.u());
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x227C80u, v0.u());
        s1 = addiu(s1, 9008);
        a0 = s1;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x227CA4u, v0.u());
        a0 = s1;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x227CC4u, v0.u());
        s2 = addiu(s2, 1);
    }
    // 0x00227cdc
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

// 0x00227F30 sub_227F30 -- 2680 bytes; frame 0x90: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutGrid] lays out the six-entry page grid (pages 30..33, 30 / 31) at 38, 237.
void sub_227F30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x00227f30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00227f6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x227F78u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00227f80
    charge(ctx, 18);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x227F88u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s3 = v0;
    lwc1(f25, s1, kBcmFade);
    v0 = 0x42180000;
    sw(v0, sp, 0x80);
    v0 = 0x436D0000;
    mtc1(v0, f23);
    sw(v0, sp, 0x84);
    lwc1(f1, sp, 0x80);
    lwc1(f0, sp, 0x84);
    swc1(f1, s1, 24664);
    swc1(f0, s1, 24668);
    s0 = 0;
    for (;;) {  // while (s0 < 6)
        // 0x002281d8
        charge(ctx, 3);
        v0 = slti(s0, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00227fc8
        charge(ctx, 3);
        at = sltiu(s0, 6);
        if (at != 0) {
            // 0x00227fd4
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30544);  // &0x7B7750
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x227FF0u:  // table[0, 1, 2, 3]
                // 0x00227ff0
                charge(ctx, 7);
                a1 = addiu(s0, 30);
                a0 = s3;
                jal(ctx, 0x227FF8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s2 = v0;
                break;
            case 0x22800Cu:  // table[4, 5]
                // 0x0022800c
                charge(ctx, 5);
                a1 = addiu(s0, 26);
                a0 = s3;
                jal(ctx, 0x228014u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s2 = v0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00228020
        charge(ctx, 5);
        lwc1(f2, sp, 0x80);
        mov_s(f0, f23);
        at = sltiu(s0, 6);
        if (at != 0) {
            // 0x00228034
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30512);  // &0x7B7730
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x228050u:  // table[0]
                // 0x00228050
                charge(ctx, 10);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f2, f2, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                add_s(f0, f23, f0);
                break;
            case 0x228078u:  // table[1]
                // 0x00228078
                charge(ctx, 10);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f2, f2, f0);
                v0 = 0x42960000;
                mtc1(v0, f0);
                add_s(f0, f23, f0);
                break;
            case 0x2280A0u:  // table[2]
                // 0x002280a0
                charge(ctx, 10);
                v0 = 0x43490000;
                mtc1(v0, f0);
                add_s(f2, f2, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                add_s(f0, f23, f0);
                break;
            case 0x2280C8u:  // table[3]
                // 0x002280c8
                charge(ctx, 10);
                v0 = 0x43490000;
                mtc1(v0, f0);
                add_s(f2, f2, f0);
                v0 = 0x42960000;
                mtc1(v0, f0);
                add_s(f0, f23, f0);
                break;
            case 0x2280F0u:  // table[4]
                // 0x002280f0
                charge(ctx, 13);
                lwc1(f0, s2, 12);
                cvt_s_w(f1, f0);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                add_s(f2, f2, f0);
                v0 = 0x40800000;
                mtc1(v0, f0);
                add_s(f0, f23, f0);
                break;
            case 0x228124u:  // table[5]
                // 0x00228124
                charge(ctx, 11);
                lwc1(f0, s2, 12);
                cvt_s_w(f1, f0);
                v0 = 0x41300000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                add_s(f2, f2, f0);
                v0 = 0x42960000;
                mtc1(v0, f0);
                add_s(f0, f23, f0);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00228150
        charge(ctx, 3);
        at = sltiu(s0, 6);
        if (at != 0) {
            // 0x0022815c
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 30480);  // &0x7B7710
            v0 = sll(s0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x228178u:  // table[0, 1, 2, 3]
                // 0x00228178
                charge(ctx, 10);
                swc1(f2, sp, 0x70);
                swc1(f0, sp, 0x74);
                lwc1(f0, s2, 12);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x78);
                lwc1(f0, s2, 16);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x7C);
                break;
            case 0x2281A0u:  // table[4, 5]
                // 0x002281a0
                charge(ctx, 7);
                swc1(f2, sp, 0x70);
                swc1(f0, sp, 0x74);
                v0 = 0x42280000;
                sw(v0, sp, 0x78);
                lwc1(f0, s2, 16);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x7C);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x002281bc
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 11824);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x2281CCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s0 = addiu(s0, 1);
    }
    // 0x002281e4
    charge(ctx, 4);
    lw(a0, s1, kBcmSub);
    v1 = 3;
    if (a0 == v1) {
        // 0x00228280
        charge(ctx, 3);
        lw(v1, s1, kBcmSubStep);
        if (v1 == 0) {
            // 0x002282d8
            charge(ctx, 4);
            lw(v1, s1, kBcmMenuTimer);
            v0 = 6;
            if (v1 != v0) {
                // 0x002282f8
                charge(ctx, 8);
                v0 = subu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                div_s(f24, f1, f0);
            } else {
                // 0x002282e8
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f24);
            }
        } else {
            // 0x0022828c
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x00228298
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_002282ac;
                }
                // 0x002282a4
                charge(ctx, 2);
                goto L_00228318;
            }
        L_002282ac:
            charge(ctx, 11);
            lwc1(f0, s1, 18008);
            cvt_s_w(f1, f0);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            div_s(f24, f1, f0);
        }
    } else {
        // 0x002281f4
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x00228248
            charge(ctx, 14);
            lw(v0, s1, kBcmSubTimer);
            v0 = subu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f24, f1, f0);
        } else {
            // 0x002281fc
            charge(ctx, 3);
            v0 = 1;
            if (a0 != v0) {
                // 0x00228208
                charge(ctx, 3);
                v0 = 2;
                if (a0 == v0) {
                    goto L_0022821c;
                }
                // 0x00228214
                charge(ctx, 2);
                goto L_00228318;
            }
        L_0022821c:
            charge(ctx, 11);
            lwc1(f0, s1, 18000);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f24, f1, f0);
        }
    }
L_00228318:
    charge(ctx, 11);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f24);
    mul_s(f1, f0, f25);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0022835c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00228344
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00228374
    charge(ctx, 4);
    a1 = v1 & 0xFF;
    lw(v1, s1, 17988);
    if (v1 == 0) {
        // 0x002283d4
        charge(ctx, 9);
        lw(v1, s1, 18008);
        v0 = sll(v1, 8);
        v1 = subu(v0, v1);
        v0 = 6;
        div(v1, v0);
        mflo(v0);
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
    } else {
        // 0x00228384
        charge(ctx, 3);
        v0 = 2;
        if (v1 != v0) {
            // 0x00228390
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_002283a4;
            }
            // 0x0022839c
            charge(ctx, 2);
            goto L_002283f8;
        }
    L_002283a4:
        charge(ctx, 12);
        lw(v0, s1, 18008);
        a0 = 6;
        v1 = subu(a0, v0);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(v0);
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
    }
L_002283f8:
    charge(ctx, 8);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    sb(a1, sp, 0x8F);
    s0 = 0;
    for (;;) {  // while (s0 < 6)
        // 0x00228434
        charge(ctx, 3);
        v0 = slti(s0, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00228418
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 11824);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x228428u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = addiu(s0, 1);
    }
    // 0x00228440
    charge(ctx, 90);
    a0 = s3;
    a1 = 38;
    jal(ctx, 0x228448u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x41A00000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x80);
    add_s(f22, f1, f0);
    swc1(f22, sp, 0x70);
    lwc1(f21, sp, 0x84);
    v1 = 0x42000000;
    mtc1(v1, f0);
    add_s(f20, f0, f21);
    swc1(f20, sp, 0x74);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s1, 13360);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x22849Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s3;
    a1 = 39;
    jal(ctx, 0x2284ACu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f22, sp, 0x70);
    v1 = 0x42CC0000;
    mtc1(v1, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x74);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    a0 = addiu(s1, 13616);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x2284ECu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s3;
    a1 = 38;
    jal(ctx, 0x2284FCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    swc1(f22, sp, 0x70);
    v1 = 0x41800000;
    mtc1(v1, f0);
    add_s(f0, f0, f20);
    swc1(f0, sp, 0x74);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    v0 = 0x42580000;
    sw(v0, sp, 0x7C);
    a0 = addiu(s1, 13872);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x228538u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s3;
    a1 = 29;
    jal(ctx, 0x228548u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x42100000;
    mtc1(v1, f0);
    add_s(f0, f0, f21);
    v1 = 0x40400000;
    mtc1(v1, f1);
    sub_s(f3, f0, f1);
    v1 = 0x42B60000;
    mtc1(v1, f0);
    add_s(f0, f0, f21);
    sub_s(f2, f0, f1);
    v1 = 0x41B00000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x80);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    lw(v1, s1, 24692);
    at = slti(v1, 5);
    if (at != 0) {
        // 0x002285e0
        charge(ctx, 1);
        swc1(f3, sp, 0x74);
    } else {
        // 0x002285a8
        charge(ctx, 14);
        lwc1(f0, s1, 24684);
        cvt_s_w(f1, f0);
        sub_s(f0, f2, f3);
        mul_s(f1, f1, f0);
        v1 = addiu(v1, -4);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        add_s(f0, f3, f0);
        swc1(f0, sp, 0x74);
    }
    // 0x002285e4
    charge(ctx, 17);
    lw(a0, v0, kSpW);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x7C);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    lw(v1, s1, 17980);
    if (v1 == 0) {
        // 0x00228680
        charge(ctx, 10);
        lw(v1, s1, 18000);
        v0 = 3;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f24, f1, f0);
    } else {
        // 0x00228628
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x00228634
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_00228654;
            }
            // 0x00228640
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_00228654;
            }
            // 0x0022864c
            charge(ctx, 2);
            goto L_002286a8;
        }
    L_00228654:
        charge(ctx, 11);
        lwc1(f0, s1, 18000);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f24, f1, f0);
    }
L_002286a8:
    charge(ctx, 11);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f24);
    mul_s(f1, f0, f25);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002286ec
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002286d4
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00228704
    charge(ctx, 4);
    sb(v1, sp, 0x8F);
    s0 = 0;
    for (;;) {  // while (s0 < 3)
        // 0x00228730
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00228714
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 13360);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x228724u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = addiu(s0, 1);
    }
    // 0x0022873c
    charge(ctx, 20);
    a0 = addiu(s1, 14128);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x228744u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s3;
    a1 = 44;
    jal(ctx, 0x228754u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s0 = v0;
    s2 = 0;
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x80);
    add_s(f21, f1, f0);
    v1 = 0x422C0000;
    mtc1(v1, f0);
    add_s(f20, f0, f23);
    for (;;) {  // while (s2 < 4)
        // 0x00228824
        charge(ctx, 3);
        v1 = slti(s2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022878c
        charge(ctx, 38);
        swc1(f21, sp, 0x70);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        v0 = addu(v0, s2);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f22, f20, f0);
        swc1(f22, sp, 0x74);
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x78);
        lwc1(f0, s0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x7C);
        v0 = sll(s2, 9);
        s3 = addu(s1, v0);
        a0 = addiu(s3, 14384);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x2287E0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lwc1(f0, s0, kSpW);
        cvt_s_w(f0, f0);
        add_s(f0, f21, f0);
        swc1(f0, sp, 0x70);
        swc1(f22, sp, 0x74);
        v0 = 0x438A0000;
        sw(v0, sp, 0x78);
        lwc1(f0, s0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x7C);
        a0 = addiu(s3, 14640);
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x228818u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s2 = addiu(s2, 1);
    }
    // 0x00228830
    charge(ctx, 7);
    v1 = 255;
    sb(v1, sp, 0x8C);
    sb(v1, sp, 0x8D);
    sb(v1, sp, 0x8E);
    s0 = 0;
    for (;;) {  // while (s0 < 4)
        // 0x00228964
        charge(ctx, 3);
        v1 = slti(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022884c
        charge(ctx, 3);
        lw(v1, s1, 17980);
        if (v1 == 0) {
            // 0x002288b0
            charge(ctx, 10);
            lw(v1, s1, 18000);
            v0 = 3;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f24, f1, f0);
        } else {
            // 0x00228858
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x00228864
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_00228884;
                }
                // 0x00228870
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_00228884;
                }
                // 0x0022887c
                charge(ctx, 2);
                goto L_002288d8;
            }
        L_00228884:
            charge(ctx, 11);
            lwc1(f0, s1, 18000);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f24, f1, f0);
        }
    L_002288d8:
        charge(ctx, 11);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f24);
        mul_s(f1, f0, f25);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0022891c
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00228904
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00228934
        charge(ctx, 12);
        sb(v1, sp, 0x8F);
        v0 = sll(s0, 9);
        s2 = addu(s1, v0);
        a0 = addiu(s2, 14384);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x228948u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s2, 14640);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x228958u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s0 = addiu(s0, 1);
    }
    // 0x00228970
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
    sp = addiu(sp, 0x90);
}

// 0x002289B0 sub_2289B0 -- 1156 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawGrid] draws the six-entry grid.
void sub_2289B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002289b0
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x002289e0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x2289ECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x002289f4
    charge(ctx, 24);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x2289FCu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x228A1Cu, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x228A30u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x228A40u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s4 = 0;
    for (;;) {  // while (s4 < 6)
        // 0x00228b00
        charge(ctx, 3);
        v0 = slti(s4, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00228a54
        charge(ctx, 3);
        at = slti(s4, 4);
        if (at == 0) {
            // 0x00228a78
            charge(ctx, 4);
            a1 = addiu(s4, 26);
            a0 = s5;
            jal(ctx, 0x228A80u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        } else {
            // 0x00228a60
            charge(ctx, 6);
            a1 = addiu(s4, 30);
            a0 = s5;
            jal(ctx, 0x228A68u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        }
        // 0x00228a88
        charge(ctx, 30);
        a0 = v0;
        jal(ctx, 0x228A8Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x228AA0u, v0.u());
        v0 = sll(s4, 8);
        v0 = addu(s2, v0);
        s3 = addiu(v0, 11824);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = s3;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x228AD4u, v0.u());
        a0 = s3;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x228AF4u, v0.u());
        s4 = addiu(s4, 1);
    }
    // 0x00228b0c
    charge(ctx, 103);
    a0 = s5;
    a1 = 38;
    jal(ctx, 0x228B14u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s3 = 0x960000;
    s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x228B28u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x228B3Cu, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 13360);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228B64u, v0.u());
    a0 = addiu(s2, 13360);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228B84u, v0.u());
    a0 = s5;
    a1 = 39;
    jal(ctx, 0x228B94u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x228BA0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x228BB4u, v0.u());
    a0 = addiu(s2, 13616);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228BD4u, v0.u());
    a0 = addiu(s2, 13616);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228BF4u, v0.u());
    a0 = s5;
    a1 = 38;
    jal(ctx, 0x228C04u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x228C10u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x228C24u, v0.u());
    a0 = addiu(s2, 13872);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228C44u, v0.u());
    a0 = addiu(s2, 13872);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228C64u, v0.u());
    a0 = s5;
    a1 = 44;
    jal(ctx, 0x228C74u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x228C80u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s3, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x228C94u, v0.u());
    s3 = 0;
    for (;;) {  // while (s3 < 4)
        // 0x00228d44
        charge(ctx, 3);
        v0 = slti(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00228ca8
        charge(ctx, 39);
        v0 = sll(s3, 9);
        s6 = addu(s2, v0);
        s4 = addiu(s6, 14384);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x228CD4u, v0.u());
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x228CF4u, v0.u());
        s4 = addiu(s6, 14640);
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x228D18u, v0.u());
        a0 = s4;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x228D38u, v0.u());
        s3 = addiu(s3, 1);
    }
    // 0x00228d50
    charge(ctx, 57);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x228D58u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    a0 = v0;
    jal(ctx, 0x228D64u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);
    jalr(ctx, 0x228D78u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228DA0u, v0.u());
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228DC0u, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228DE0u, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x228E00u, v0.u());
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

// 0x00228E40 sub_228E40 -- 3320 bytes; frame 0x110: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutList2] lays out sub-list 2: rows, right-aligned numbers (bpIfont sub_238BF0), font lines; the
// fade is sub-timer / 3 (K_Assert 3673 if another list is open).
void sub_228E40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00228e40
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00228e84
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x228E90u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00228e98
    charge(ctx, 16);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x228EA0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    a0 = 6;
    jal(ctx, 0x228EB0u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s4 = v0;
    v0 = addiu(s2, 18016);
    sq(v0, sp, 0xB0);
    s1 = addiu(s2, 24656);
    lwc1(f21, s2, kBcmFade);
    lw(v1, s2, kBcmSub);
    if (v1 == 0) {
        // 0x00228f18
        charge(ctx, 15);
        lw(v1, s2, kBcmSubTimer);
        v0 = 3;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f22, f1, f0);
    } else {
        // 0x00228ed8
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x00228eec
            charge(ctx, 11);
            lwc1(f0, s2, kBcmSubTimer);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f22, f1, f0);
        } else {
            // 0x00228ee4
            charge(ctx, 2);
            // 0x00228f54
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7296);  // "bcm_panel.c"
            a1 = 3673;
            jal(ctx, 0x228F60u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 3673): `jr $ra` in retail, execution goes on
        }
    }
    // 0x00228f68
    charge(ctx, 4);
    lw(v1, s2, kBcmSubStep);
    v0 = 3;
    if (v1 == v0) {
        // 0x00228f98
        charge(ctx, 1);
        mtc1(zero, f20);
    } else {
        // 0x00228f78
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x00228f88
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f20);
        } else {
            // 0x00228f80
            charge(ctx, 2);
        }
    }
    // 0x00228f9c
    charge(ctx, 96);
    mul_s(f20, f22, f20);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    sub_s(f22, f0, f20);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x228FB8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s1, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    lw(a0, s2, 24680);
    lw(v1, s2, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s1, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xF4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xFC);
    a0 = addiu(s2, 16944);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x22903Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x22904Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s1, 0);
    add_s(f1, f1, f0);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    lw(a0, s2, 24680);
    lw(v1, s2, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s1, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xF4);
    v1 = 0x439C0000;
    sw(v1, sp, 0xF8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xFC);
    a0 = addiu(s2, 17200);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x2290D8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x10C);
    sb(v0, sp, 0x10D);
    sb(v0, sp, 0x10E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    mul_s(f20, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00229134
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022911c
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022914c
    charge(ctx, 16);
    sb(v1, sp, 0x10F);
    a0 = addiu(s2, 16944);
    a1 = addiu(sp, 0x10C);
    jal(ctx, 0x229158u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s2, 17200);
    a1 = addiu(sp, 0x10C);
    jal(ctx, 0x229168u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s3 = 0;
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x002291a4
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
        a0 = a0 & 0xFF;
    } else {
        // 0x0022918c
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a0, f0);
        a0 = a0 & 0xFF;
    }
    // 0x002291bc
    charge(ctx, 18);
    a0 = a0 & 0xFF;
    v1 = sll(a0, 2);
    a0 = addu(v1, a0);
    v1 = sll(a0, 2);
    v1 = addu(a0, v1);
    a0 = sll(v1, 1);
    v1 = 100;
    div(a0, v1);
    mflo(a0);
    v1 = si(-256);
    v1 = a0 | v1;
    sw(v1, sp, 0xE0);
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00229214
        charge(ctx, 5);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
    } else {
        // 0x00229204
        charge(ctx, 4);
        cvt_w_s(f0, f20);
        mfc1(a0, f0);
    }
    // 0x00229228
    charge(ctx, 9);
    v1 = si(-256);
    v1 = a0 | v1;
    sw(v1, sp, 0xD0);
    v1 = lui(0xCCCC);
    v1 = v1 | 0xCC00;
    v1 = a0 | v1;
    sw(v1, sp, 0xC0);
    for (;;) {
        // 0x002296c8
        charge(ctx, 4);
        lw(v1, s2, 24688);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022924c
        charge(ctx, 51);
        v0 = sll(s3, 3);
        v1 = addu(v0, s3);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v1 = sll(v0, 4);
        lq(v0, sp, 0xB0);
        s0 = addu(v0, v1);
        a0 = s4;
        a1 = 43;
        jal(ctx, 0x229270u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s6 = v0;
        lw(s7, s0, 4);
        v1 = 0x42820000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f1, f1, f0);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        add_s(f2, f1, f0);
        swc1(f2, sp, 0xF0);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        v0 = addu(v0, s3);
        fp = sll(v0, 1);
        lwc1(f1, s1, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(fp, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        swc1(f1, sp, 0xF4);
        cvt_w_s(f0, f2);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        cvt_w_s(f0, f1);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        a0 = s7;
        jal(ctx, 0x229300u, gen::fn_frFontLineSetPos_003b0d70);
        lw(v0, s0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00229324
            charge(ctx, 5);
            lw(v1, s2, 24680);
            lw(v0, s2, 24684);
            v0 = subu(v1, v0);
            if (s3 != v0) {
                // 0x00229344
                charge(ctx, 1);
                lw(a1, sp, 0xC0);
            } else {
                // 0x00229338
                charge(ctx, 3);
                lw(a1, sp, 0xD0);
            }
        } else {
            // 0x00229318
            charge(ctx, 3);
            lw(a1, sp, 0xE0);
        }
        // 0x00229348
        charge(ctx, 7);
        a0 = s7;
        jal(ctx, 0x22934Cu, gen::fn_frFontLineSetRgba_003b0e20);
        lw(v1, s0, 8);
        v0 = 1;
        if (v1 == v0) {
            // 0x00229390
            charge(ctx, 5);
            a0 = s5;
            a1 = 49;
            jal(ctx, 0x229398u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s6 = v0;
        } else {
            // 0x00229364
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00229374
                charge(ctx, 7);
                a0 = s5;
                a1 = 48;
                jal(ctx, 0x22937Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s6 = v0;
            } else {
                // 0x0022936c
                charge(ctx, 2);
            }
        }
        // 0x002293a4
        charge(ctx, 42);
        v0 = 327;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        v0 = addu(v0, s3);
        s7 = sll(v0, 1);
        lwc1(f1, s1, 4);
        v0 = 0x42000000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(s7, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        lwc1(f0, s6, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xF8);
        lwc1(f0, s6, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xFC);
        a0 = addiu(s0, 16);
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x22941Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0x10C);
        sb(v0, sp, 0x10D);
        sb(v0, sp, 0x10E);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x00229464
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022944c
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022947c
        charge(ctx, 34);
        sb(v1, sp, 0x10F);
        a0 = addiu(s0, 16);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x229488u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 281;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s1, 4);
        v0 = 0x41F00000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(s7, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        a0 = addiu(s0, 272);
        a1 = 3;
        lw(a2, s0, 12);
        a3 = 1;
        t0 = addiu(sp, 0xF0);
        jal(ctx, 0x2294E8u, gen::fn_sub_238BF0_00238bf0);
        lw(v1, s2, 24680);
        lw(v0, s2, 24684);
        v0 = subu(v1, v0);
        if (s3 != v0) {
            // 0x0022951c
            charge(ctx, 4);
            v0 = 90;
            sb(v0, sp, 0x10C);
            sb(v0, sp, 0x10D);
            sb(v0, sp, 0x10E);
        } else {
            // 0x00229504
            charge(ctx, 6);
            v0 = 255;
            sb(v0, sp, 0x10C);
            sb(v0, sp, 0x10D);
            sb(v0, sp, 0x10E);
        }
        // 0x0022952c
        charge(ctx, 6);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022955c
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00229544
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00229574
        charge(ctx, 47);
        sb(v1, sp, 0x10F);
        a0 = addiu(s0, 272);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x229580u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s0, 528);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x229590u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s0, 784);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x2295A0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s4;
        a1 = 43;
        jal(ctx, 0x2295B0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x42600000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s1, 4);
        v1 = 0x41800000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        mtc1(fp, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xF8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xFC);
        a0 = addiu(s0, 1040);
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x229614u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lw(v1, s2, 24680);
        lw(v0, s2, 24684);
        v0 = subu(v1, v0);
        if (s3 != v0) {
            // 0x00229650
            charge(ctx, 6);
            v0 = 68;
            sb(v0, sp, 0x10C);
            v0 = 78;
            sb(v0, sp, 0x10D);
            v0 = 80;
            sb(v0, sp, 0x10E);
        } else {
            // 0x00229630
            charge(ctx, 8);
            v0 = 199;
            sb(v0, sp, 0x10C);
            v0 = 211;
            sb(v0, sp, 0x10D);
            v0 = 227;
            sb(v0, sp, 0x10E);
        }
        // 0x00229668
        charge(ctx, 6);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x00229698
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00229680
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002296b0
        charge(ctx, 6);
        sb(v1, sp, 0x10F);
        a0 = addiu(s0, 1040);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x2296BCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s3 = addiu(s3, 1);
    }
    // 0x002296d8
    charge(ctx, 4);
    lw(a0, s2, kBcmSubStep);
    v1 = 3;
    if (a0 == v1) {
        // 0x002296f0
        charge(ctx, 47);
        s2 = addiu(s2, 27904);
        a0 = s4;
        a1 = 43;
        jal(ctx, 0x2296FCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s3 = v0;
        lw(s0, s2, 4);
        v1 = 0x42820000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f1, f1, f0);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        add_s(f2, f1, f0);
        swc1(f2, sp, 0xF0);
        lwc1(f1, s1, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x429A0000;
        mtc1(v0, f0);
        add_s(f1, f1, f0);
        swc1(f1, sp, 0xF4);
        cvt_w_s(f0, f2);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        cvt_w_s(f0, f1);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        a0 = s0;
        jal(ctx, 0x229778u, gen::fn_frFontLineSetPos_003b0d70);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f22);
        mul_s(f1, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x002297bc
            charge(ctx, 5);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
        } else {
            // 0x002297ac
            charge(ctx, 4);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
        }
        // 0x002297d0
        charge(ctx, 9);
        v0 = si(-256);
        a1 = v1 | v0;
        a0 = s0;
        jal(ctx, 0x2297DCu, gen::fn_frFontLineSetRgba_003b0e20);
        lw(v1, s2, 8);
        v0 = 1;
        if (v1 == v0) {
            // 0x00229820
            charge(ctx, 5);
            a0 = s5;
            a1 = 49;
            jal(ctx, 0x229828u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s3 = v0;
        } else {
            // 0x002297f4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00229804
                charge(ctx, 7);
                a0 = s5;
                a1 = 48;
                jal(ctx, 0x22980Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s3 = v0;
            } else {
                // 0x002297fc
                charge(ctx, 2);
            }
        }
        // 0x00229834
        charge(ctx, 42);
        v0 = 327;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s1, 4);
        v0 = 0x42040000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x429A0000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        lwc1(f0, s3, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xF8);
        lwc1(f0, s3, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xFC);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x229898u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0x10C);
        sb(v0, sp, 0x10D);
        sb(v0, sp, 0x10E);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f22);
        mul_s(f20, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x002298f4
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002298dc
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022990c
        charge(ctx, 39);
        sb(v1, sp, 0x10F);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x229918u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 281;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s1, 4);
        v0 = 0x41F80000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x429A0000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        a0 = addiu(s2, 272);
        a1 = 3;
        lw(a2, s2, 12);
        a3 = 1;
        t0 = addiu(sp, 0xF0);
        jal(ctx, 0x229978u, gen::fn_sub_238BF0_00238bf0);
        v0 = 255;
        sb(v0, sp, 0x10C);
        sb(v0, sp, 0x10D);
        sb(v0, sp, 0x10E);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x002299c0
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002299a8
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002299d8
        charge(ctx, 55);
        sb(v1, sp, 0x10F);
        a0 = addiu(s2, 272);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x2299E4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s2, 528);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x2299F4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s2, 784);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x229A04u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s4;
        a1 = 43;
        jal(ctx, 0x229A14u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        v1 = 0x42600000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF0);
        lwc1(f1, s1, 4);
        v1 = 0x41800000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        v1 = 0x429A0000;
        mtc1(v1, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xF4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xF8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xFC);
        a0 = addiu(s2, 1040);
        a1 = addiu(sp, 0xF0);
        jal(ctx, 0x229A7Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lbu(v0, s0, kSpRgba);
        sb(v0, sp, 0x10C);
        lbu(v0, s0, 29);
        sb(v0, sp, 0x10D);
        lbu(v0, s0, 30);
        sb(v0, sp, 0x10E);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x00229acc
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00229ab4
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00229ae4
        charge(ctx, 5);
        sb(v1, sp, 0x10F);
        a0 = addiu(s2, 1040);
        a1 = addiu(sp, 0x10C);
        jal(ctx, 0x229AF0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    } else {
        // 0x002296e8
        charge(ctx, 2);
    }
    // 0x00229af8 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// 0x00229B40 sub_229B40 -- 1904 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawList2] draws sub-list 2.
void sub_229B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00229b40
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x00229b78
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x229B84u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x00229b8c
    charge(ctx, 63);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x229B94u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    a0 = 6;
    jal(ctx, 0x229BA4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s6 = v0;
    v0 = addiu(s2, 18016);
    sq(v0, sp, 0xA0);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x229BC0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s4 = v0;
    s7 = 0x960000;
    s7 = addiu(s7, 144);  // &pfn_RwRenderStateSet
    a0 = s4;
    jal(ctx, 0x229BD8u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s7, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x229BECu, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x229C14u, v0.u());
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x229C34u, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x229C54u, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x229C74u, v0.u());
    s3 = 0;
    for (;;) {
        // 0x00229fa0
        charge(ctx, 4);
        lw(v1, s2, 24688);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00229c88
        charge(ctx, 25);
        v0 = sll(s3, 3);
        v1 = addu(v0, s3);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v1 = sll(v0, 4);
        lq(v0, sp, 0xA0);
        s1 = addu(v0, v1);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x229CB0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x229CC0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        lw(a0, s1, 4);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x229CD4u, gen::fn_frFontDraw_003b1360);
        lw(v1, s1, 8);
        v0 = 1;
        if (v1 == v0) {
            // 0x00229d18
            charge(ctx, 5);
            a0 = s5;
            a1 = 49;
            jal(ctx, 0x229D20u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s4 = v0;
        } else {
            // 0x00229cec
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00229cfc
                charge(ctx, 7);
                a0 = s5;
                a1 = 48;
                jal(ctx, 0x229D04u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s4 = v0;
            } else {
                // 0x00229cf4
                charge(ctx, 2);
            }
        }
        // 0x00229d2c
        charge(ctx, 13);
        a0 = s4;
        jal(ctx, 0x229D30u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s7, 0);
        jalr(ctx, 0x229D44u, v0.u());
        lw(v1, s2, 24680);
        lw(v0, s2, 24684);
        v0 = subu(v1, v0);
        if (s3 != v0) {
            // 0x00229d8c
            charge(ctx, 9);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x229D98u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x229DA8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        } else {
            // 0x00229d60
            charge(ctx, 11);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x1801;
            jal(ctx, 0x229D6Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 72;
            jal(ctx, 0x229D7Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        }
        // 0x00229db0
        charge(ctx, 124);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s1, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229DD0u, v0.u());
        a0 = addiu(s1, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229DF0u, v0.u());
        fp = 0x960000;
        fp = addiu(fp, 0x90);
        a0 = 1;
        jal(ctx, 0x229E04u, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
        a0 = 1;
        a1 = v0;
        lw(v0, fp, 0x0);
        jalr(ctx, 0x229E18u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x229E2Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x229E3Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s1, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229E5Cu, v0.u());
        a0 = addiu(s1, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229E7Cu, v0.u());
        a0 = addiu(s1, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229E9Cu, v0.u());
        a0 = addiu(s1, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229EBCu, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229EDCu, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229EFCu, v0.u());
        a0 = s6;
        a1 = 43;
        jal(ctx, 0x229F0Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s4 = v0;
        a0 = s4;
        jal(ctx, 0x229F1Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, fp, 0x0);
        jalr(ctx, 0x229F30u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x229F44u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x229F54u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s1, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229F74u, v0.u());
        a0 = addiu(s1, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x229F94u, v0.u());
        s3 = addiu(s3, 1);
    }
    // 0x00229fb0
    charge(ctx, 4);
    lw(v1, s2, kBcmSubStep);
    a0 = 3;
    if (v1 == a0) {
        // 0x00229fc8
        charge(ctx, 18);
        s2 = addiu(s2, 27904);
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x229FD4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x229FE4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        lw(a0, s2, 4);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x229FF8u, gen::fn_frFontDraw_003b1360);
        lw(v1, s2, 8);
        v0 = 1;
        if (v1 == v0) {
            // 0x0022a03c
            charge(ctx, 5);
            a0 = s5;
            a1 = 49;
            jal(ctx, 0x22A044u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s4 = v0;
        } else {
            // 0x0022a010
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0022a020
                charge(ctx, 7);
                a0 = s5;
                a1 = 48;
                jal(ctx, 0x22A028u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s4 = v0;
            } else {
                // 0x0022a018
                charge(ctx, 2);
            }
        }
        // 0x0022a050
        charge(ctx, 139);
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = s4;
        jal(ctx, 0x22A05Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22A070u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x1801;
        jal(ctx, 0x22A084u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(ctx, 0x22A094u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A0BCu, v0.u());
        a0 = addiu(s2, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A0DCu, v0.u());
        a0 = 1;
        jal(ctx, 0x22A0E8u, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22A0FCu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22A110u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22A120u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A140u, v0.u());
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A160u, v0.u());
        a0 = addiu(s2, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A180u, v0.u());
        a0 = addiu(s2, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A1A0u, v0.u());
        a0 = addiu(s2, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A1C0u, v0.u());
        a0 = addiu(s2, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A1E0u, v0.u());
        a0 = s6;
        a1 = 43;
        jal(ctx, 0x22A1F0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x22A1FCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22A210u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22A224u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22A234u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A254u, v0.u());
        a0 = addiu(s2, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22A274u, v0.u());
    } else {
        // 0x00229fc0
        charge(ctx, 2);
    }
    // 0x0022a27c (the shared epilogue, written out on this path)
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

// 0x0022A2B0 sub_22A2B0 -- 3016 bytes; frame 0x100: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [bcmPanel_LayoutList1] lays out sub-list 1 like sub-list 2 (K_Assert 4020).
void sub_22A2B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0022a2b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0022a2f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22A300u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022a308
    charge(ctx, 16);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22A310u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    a0 = 6;
    jal(ctx, 0x22A320u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s4 = v0;
    v0 = addiu(s2, 18016);
    sq(v0, sp, 0xB0);
    s1 = addiu(s2, 24656);
    lwc1(f21, s2, kBcmFade);
    lw(v1, s2, kBcmSub);
    if (v1 == 0) {
        // 0x0022a388
        charge(ctx, 15);
        lw(v1, s2, kBcmSubTimer);
        v0 = 3;
        v0 = subu(v0, v1);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40400000;
        mtc1(v0, f0);
        div_s(f22, f1, f0);
    } else {
        // 0x0022a348
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0022a35c
            charge(ctx, 11);
            lwc1(f0, s2, kBcmSubTimer);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f22, f1, f0);
        } else {
            // 0x0022a354
            charge(ctx, 2);
            // 0x0022a3c4
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7296);  // "bcm_panel.c"
            a1 = 4020;
            jal(ctx, 0x22A3D0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 4020): `jr $ra` in retail, execution goes on
        }
    }
    // 0x0022a3d8
    charge(ctx, 4);
    lw(v1, s2, kBcmSubStep);
    v0 = 4;
    if (v1 == v0) {
        // 0x0022a408
        charge(ctx, 1);
        mtc1(zero, f20);
    } else {
        // 0x0022a3e8
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0022a3f8
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f20);
        } else {
            // 0x0022a3f0
            charge(ctx, 2);
        }
    }
    // 0x0022a40c
    charge(ctx, 96);
    mul_s(f20, f22, f20);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    sub_s(f22, f0, f20);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x22A428u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s1, 0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xE0);
    lw(a0, s2, 24680);
    lw(v1, s2, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s1, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xE4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xE8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xEC);
    a0 = addiu(s2, 16944);
    a1 = addiu(sp, 0xE0);
    jal(ctx, 0x22A4ACu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x22A4BCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x423C0000;
    mtc1(v1, f1);
    lwc1(f0, s1, 0);
    add_s(f1, f1, f0);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xE0);
    lw(a0, s2, 24680);
    lw(v1, s2, 24684);
    a0 = subu(a0, v1);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    lwc1(f1, s1, 4);
    v1 = 0x41980000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xE4);
    v1 = 0x439C0000;
    sw(v1, sp, 0xE8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xEC);
    a0 = addiu(s2, 17200);
    a1 = addiu(sp, 0xE0);
    jal(ctx, 0x22A548u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0xFC);
    sb(v0, sp, 0xFD);
    sb(v0, sp, 0xFE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    mul_s(f20, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0022a5a4
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022a58c
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022a5bc
    charge(ctx, 16);
    sb(v1, sp, 0xFF);
    a0 = addiu(s2, 16944);
    a1 = addiu(sp, 0xFC);
    jal(ctx, 0x22A5C8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = addiu(s2, 17200);
    a1 = addiu(sp, 0xFC);
    jal(ctx, 0x22A5D8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s3 = 0;
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0022a60c
        charge(ctx, 5);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
    } else {
        // 0x0022a5fc
        charge(ctx, 4);
        cvt_w_s(f0, f20);
        mfc1(a0, f0);
    }
    // 0x0022a620
    charge(ctx, 9);
    v1 = si(-256);
    v1 = a0 | v1;
    sw(v1, sp, 0xD0);
    v1 = lui(0xCCCC);
    v1 = v1 | 0xCC00;
    v1 = a0 | v1;
    sw(v1, sp, 0xC0);
    for (;;) {
        // 0x0022aa5c
        charge(ctx, 4);
        lw(v1, s2, 24688);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022a644
        charge(ctx, 38);
        v0 = sll(s3, 6);
        v0 = addu(v0, s3);
        v1 = sll(v0, 4);
        lq(v0, sp, 0xB0);
        s0 = addu(v0, v1);
        a0 = s4;
        a1 = 26;
        jal(ctx, 0x22A660u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        lw(s6, s0, 0);
        v1 = 0x42820000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f1, f1, f0);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        v0 = addu(v0, s3);
        fp = sll(v0, 1);
        lwc1(f1, s1, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(fp, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        lw(v1, s2, 24680);
        lw(v0, s2, 24684);
        v0 = subu(v1, v0);
        if (s3 != v0) {
            // 0x0022a6e8
            charge(ctx, 1);
            lw(s7, sp, 0xC0);
        } else {
            // 0x0022a6dc
            charge(ctx, 3);
            lw(s7, sp, 0xD0);
        }
        // 0x0022a6ec
        charge(ctx, 61);
        lwc1(f0, sp, 0xE0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        lwc1(f0, sp, 0xE4);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        a0 = s6;
        jal(ctx, 0x22A718u, gen::fn_frFontLineSetPos_003b0d70);
        a0 = s6;
        a1 = s7;
        jal(ctx, 0x22A728u, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = s5;
        a1 = 40;
        jal(ctx, 0x22A738u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x43930000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        v1 = sll(s3, 1);
        v1 = addu(v1, s3);
        v1 = sll(v1, 2);
        v1 = addu(v1, s3);
        s6 = sll(v1, 1);
        lwc1(f1, s1, 4);
        v1 = 0x41F80000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        mtc1(s6, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xE8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xEC);
        a0 = addiu(s0, 16);
        a1 = addiu(sp, 0xE0);
        jal(ctx, 0x22A7B0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xFC);
        sb(v0, sp, 0xFD);
        sb(v0, sp, 0xFE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022a7f8
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022a7e0
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022a810
        charge(ctx, 34);
        sb(v1, sp, 0xFF);
        a0 = addiu(s0, 16);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22A81Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 315;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        lwc1(f1, s1, 4);
        v0 = 0x41E80000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        mtc1(s6, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        a0 = addiu(s0, 272);
        a1 = 2;
        lw(a2, s0, 4);
        a3 = 1;
        t0 = addiu(sp, 0xE0);
        jal(ctx, 0x22A87Cu, gen::fn_sub_238BF0_00238bf0);
        lw(v1, s2, 24680);
        lw(v0, s2, 24684);
        v0 = subu(v1, v0);
        if (s3 != v0) {
            // 0x0022a8b0
            charge(ctx, 4);
            v0 = 90;
            sb(v0, sp, 0xFC);
            sb(v0, sp, 0xFD);
            sb(v0, sp, 0xFE);
        } else {
            // 0x0022a898
            charge(ctx, 6);
            v0 = 255;
            sb(v0, sp, 0xFC);
            sb(v0, sp, 0xFD);
            sb(v0, sp, 0xFE);
        }
        // 0x0022a8c0
        charge(ctx, 6);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022a8f0
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022a8d8
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022a908
        charge(ctx, 47);
        sb(v1, sp, 0xFF);
        a0 = addiu(s0, 272);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22A914u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s0, 528);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22A924u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s0, 784);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22A934u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s4;
        a1 = 26;
        jal(ctx, 0x22A944u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x42600000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        lwc1(f1, s1, 4);
        v1 = 0x41800000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        mtc1(fp, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xE8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xEC);
        a0 = addiu(s0, 784);
        a1 = addiu(sp, 0xE0);
        jal(ctx, 0x22A9A8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lw(v1, s2, 24680);
        lw(v0, s2, 24684);
        v0 = subu(v1, v0);
        if (s3 != v0) {
            // 0x0022a9e4
            charge(ctx, 6);
            v0 = 68;
            sb(v0, sp, 0xFC);
            v0 = 78;
            sb(v0, sp, 0xFD);
            v0 = 80;
            sb(v0, sp, 0xFE);
        } else {
            // 0x0022a9c4
            charge(ctx, 8);
            v0 = 199;
            sb(v0, sp, 0xFC);
            v0 = 211;
            sb(v0, sp, 0xFD);
            v0 = 227;
            sb(v0, sp, 0xFE);
        }
        // 0x0022a9fc
        charge(ctx, 6);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022aa2c
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022aa14
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022aa44
        charge(ctx, 6);
        sb(v1, sp, 0xFF);
        a0 = addiu(s0, 784);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22AA50u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s3 = addiu(s3, 1);
    }
    // 0x0022aa6c
    charge(ctx, 4);
    lw(a0, s2, kBcmSubStep);
    v1 = 4;
    if (a0 == v1) {
        // 0x0022aa84
        charge(ctx, 35);
        s2 = addiu(s2, 27904);
        a0 = s4;
        a1 = 26;
        jal(ctx, 0x22AA90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        lw(s3, s2, 0);
        v1 = 0x42820000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f1, f1, f0);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        lwc1(f1, s1, 4);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x429A0000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f22);
        mul_s(f20, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022ab20
            charge(ctx, 5);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
        } else {
            // 0x0022ab10
            charge(ctx, 4);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
        }
        // 0x0022ab34
        charge(ctx, 58);
        v0 = si(-256);
        s0 = v1 | v0;
        lwc1(f0, sp, 0xE0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        lwc1(f0, sp, 0xE4);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        a0 = s3;
        jal(ctx, 0x22AB68u, gen::fn_frFontLineSetPos_003b0d70);
        a0 = s3;
        a1 = s0;
        jal(ctx, 0x22AB78u, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = s5;
        a1 = 40;
        jal(ctx, 0x22AB88u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x43930000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        lwc1(f1, s1, 4);
        v1 = 0x42040000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        v1 = 0x429A0000;
        mtc1(v1, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xE8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xEC);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0xE0);
        jal(ctx, 0x22ABECu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        v0 = 255;
        sb(v0, sp, 0xFC);
        sb(v0, sp, 0xFD);
        sb(v0, sp, 0xFE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022ac34
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022ac1c
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022ac4c
        charge(ctx, 39);
        sb(v1, sp, 0xFF);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22AC58u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        v0 = 315;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        lwc1(f1, s1, 4);
        v0 = 0x41F80000;
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x429A0000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        a0 = addiu(s2, 272);
        a1 = 2;
        lw(a2, s2, 4);
        a3 = 1;
        t0 = addiu(sp, 0xE0);
        jal(ctx, 0x22ACB8u, gen::fn_sub_238BF0_00238bf0);
        v0 = 255;
        sb(v0, sp, 0xFC);
        sb(v0, sp, 0xFD);
        sb(v0, sp, 0xFE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022ad00
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022ace8
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022ad18
        charge(ctx, 55);
        sb(v1, sp, 0xFF);
        a0 = addiu(s2, 272);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22AD24u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s2, 528);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22AD34u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = addiu(s2, 784);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22AD44u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s4;
        a1 = 26;
        jal(ctx, 0x22AD54u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        v1 = 0x42600000;
        mtc1(v1, f1);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE0);
        lwc1(f1, s1, 4);
        v1 = 0x41800000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        v1 = 0x429A0000;
        mtc1(v1, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0xE4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xE8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xEC);
        a0 = addiu(s2, 784);
        a1 = addiu(sp, 0xE0);
        jal(ctx, 0x22ADBCu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        lbu(v0, s0, kSpRgba);
        sb(v0, sp, 0xFC);
        lbu(v0, s0, 29);
        sb(v0, sp, 0xFD);
        lbu(v0, s0, 30);
        sb(v0, sp, 0xFE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x0022ae0c
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0022adf4
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0022ae24
        charge(ctx, 5);
        sb(v1, sp, 0xFF);
        a0 = addiu(s2, 784);
        a1 = addiu(sp, 0xFC);
        jal(ctx, 0x22AE30u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    } else {
        // 0x0022aa7c
        charge(ctx, 2);
    }
    // 0x0022ae38 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x0022AE80 sub_22AE80 -- 1620 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawList1] draws sub-list 1.
void sub_22AE80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0022ae80
    enter(ctx, 14);  // entry check point + this block's cycles
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
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0022aeb8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22AEC4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022aecc
    charge(ctx, 61);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22AED4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    a0 = 6;
    jal(ctx, 0x22AEE4u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s4 = v0;
    fp = addiu(s2, 0x4660);
    a0 = s5;
    a1 = 35;
    jal(ctx, 0x22AEFCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s7 = 0x960000;
    s7 = addiu(s7, 144);  // &pfn_RwRenderStateSet
    a0 = v0;
    jal(ctx, 0x22AF10u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
    a0 = 1;
    a1 = v0;
    lw(v0, s7, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22AF24u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22AF4Cu, v0.u());
    a0 = addiu(s2, 16944);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22AF6Cu, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22AF8Cu, v0.u());
    a0 = addiu(s2, 17200);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
    jalr(ctx, 0x22AFACu, v0.u());
    s3 = 0;
    for (;;) {
        // 0x0022b224
        charge(ctx, 4);
        lw(v1, s2, 24688);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022afc0
        charge(ctx, 153);
        v0 = sll(s3, 6);
        v0 = addu(v0, s3);
        v0 = sll(v0, 4);
        s1 = addu(fp, v0);
        lw(a0, s1, 0);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x22AFDCu, gen::fn_frFontDraw_003b1360);
        a0 = s5;
        a1 = 40;
        jal(ctx, 0x22AFECu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s6 = 0x960000;
        s6 = addiu(s6, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x22B000u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s6, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22B014u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22B028u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22B038u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s1, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B060u, v0.u());
        a0 = addiu(s1, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B080u, v0.u());
        a0 = 1;
        jal(ctx, 0x22B08Cu, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
        a0 = 1;
        a1 = v0;
        lw(v0, s6, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22B0A0u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22B0B4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22B0C4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s1, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B0E4u, v0.u());
        a0 = addiu(s1, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B104u, v0.u());
        a0 = addiu(s1, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B124u, v0.u());
        a0 = addiu(s1, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B144u, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B164u, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B184u, v0.u());
        a0 = s4;
        a1 = 26;
        jal(ctx, 0x22B194u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x22B1A0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s7, 0);
        jalr(ctx, 0x22B1B4u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22B1C8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22B1D8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B1F8u, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B218u, v0.u());
        s3 = addiu(s3, 1);
    }
    // 0x0022b234
    charge(ctx, 4);
    lw(a0, s2, kBcmSubStep);
    v1 = 4;
    if (a0 == v1) {
        // 0x0022b24c
        charge(ctx, 149);
        s3 = addiu(s2, 27904);
        lw(a0, s2, 27904);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x22B25Cu, gen::fn_frFontDraw_003b1360);
        a0 = s5;
        a1 = 40;
        jal(ctx, 0x22B26Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x22B280u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22B294u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22B2A8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22B2B8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s3, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B2E0u, v0.u());
        a0 = addiu(s3, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B300u, v0.u());
        a0 = 1;
        jal(ctx, 0x22B30Cu, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22B320u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22B334u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22B344u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s3, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B364u, v0.u());
        a0 = addiu(s3, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B384u, v0.u());
        a0 = addiu(s3, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B3A4u, v0.u());
        a0 = addiu(s3, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B3C4u, v0.u());
        a0 = addiu(s3, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B3E4u, v0.u());
        a0 = addiu(s3, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B404u, v0.u());
        a0 = s4;
        a1 = 26;
        jal(ctx, 0x22B414u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x22B420u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x22B434u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x22B448u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x22B458u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s3, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B478u, v0.u());
        a0 = addiu(s3, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22B498u, v0.u());
    } else {
        // 0x0022b244
        charge(ctx, 2);
    }
    // 0x0022b4a0 (the shared epilogue, written out on this path)
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

// 0x0022B530 sub_22B530 -- 68 bytes; frame 0x10: ra sp+0x0
// [bcmPanel_InMenu] returns flag bit 3.
void sub_22B530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022b530
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0022b544
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22B550u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022b558 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    lw(v0, v0, kBcmFlags);
    v0 = v0 & 0x8;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0022B630 sub_22B630 -- 1728 bytes; frame 0xB0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [bcmPanel_LayoutHelp] the three help tabs (pages 62..64; their x by the sub-list state) and the help line's
// font position / colour with the panel alpha.
void sub_22B630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0022b630
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0022b660
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22B66Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022b674
    charge(ctx, 13);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22B67Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s4 = v0;
    a0 = 6;
    jal(ctx, 0x22B68Cu, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    lwc1(f20, s1, kBcmFade);
    s3 = 0;
    for (;;) {  // while (s3 < 3)
        // 0x0022b950
        charge(ctx, 3);
        v1 = slti(s3, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022b6a8
        charge(ctx, 9);
        a1 = addiu(s3, 62);
        a0 = s4;
        jal(ctx, 0x22B6B0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s0 = v0;
        lw(a0, s1, kBcmSub);
        v0 = 4;
        if (a0 != v0) {
            // 0x0022b6cc
            charge(ctx, 3);
            v0 = 3;
            if (a0 == v0) {
                goto L_0022b798;
            }
            // 0x0022b6d8
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_0022b798;
            }
            // 0x0022b6e4
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                goto L_0022b798;
            }
            // 0x0022b6f0
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0022b700
                charge(ctx, 2);
                if (s3 == v0) {
                    // 0x0022b768
                    charge(ctx, 12);
                    v0 = 485;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x90);
                    v0 = 379;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x94);
                } else {
                    // 0x0022b708
                    charge(ctx, 2);
                    if (s3 == v1) {
                        // 0x0022b744
                        charge(ctx, 9);
                        v0 = 0x42C40000;
                        sw(v0, sp, 0x90);
                        v0 = 379;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        swc1(f0, sp, 0x94);
                    } else {
                        // 0x0022b710
                        charge(ctx, 2);
                        if (s3 == 0) {
                            // 0x0022b720
                            charge(ctx, 9);
                            v0 = 0x43690000;
                            sw(v0, sp, 0x90);
                            v0 = 379;
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            swc1(f0, sp, 0x94);
                        } else {
                            // 0x0022b718
                            charge(ctx, 2);
                        }
                    }
                }
            } else {
                // 0x0022b6f8
                charge(ctx, 2);
            }
            goto L_0022b830;
        }
    L_0022b798:
        charge(ctx, 3);
        v0 = 2;
        if (s3 == v0) {
            // 0x0022b808
            charge(ctx, 10);
            v0 = 445;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x90);
            v0 = 379;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x94);
        } else {
            // 0x0022b7a4
            charge(ctx, 3);
            v0 = 1;
            if (s3 == v0) {
                // 0x0022b7e4
                charge(ctx, 9);
                v0 = 0x42680000;
                sw(v0, sp, 0x90);
                v0 = 379;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x94);
            } else {
                // 0x0022b7b0
                charge(ctx, 2);
                if (s3 == 0) {
                    // 0x0022b7c0
                    charge(ctx, 9);
                    v0 = 0x43410000;
                    sw(v0, sp, 0x90);
                    v0 = 379;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x94);
                } else {
                    // 0x0022b7b8
                    charge(ctx, 2);
                }
            }
        }
    L_0022b830:
        charge(ctx, 19);
        lwc1(f0, s0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x98);
        lwc1(f0, s0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x9C);
        v0 = sll(s3, 8);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 26096);
        a0 = s2;
        a1 = addiu(sp, 0x90);
        jal(ctx, 0x22B85Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        t1 = 0;
        v0 = 0x4F000000;
        mtc1(v0, f1);
        v1 = lui(0x8000);
        for (;;) {  // while (t1 < 4)
            // 0x0022b930
            charge(ctx, 3);
            v0 = slti(t1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0022b87c
            charge(ctx, 15);
            v0 = sll(t1, 2);
            t0 = addu(s0, v0);
            v0 = addu(v0, sp);
            a3 = addiu(v0, 128);
            lbu(a2, t0, 28);
            lbu(a1, t0, 29);
            lbu(a0, t0, 30);
            lbu(v0, t0, 31);
            sb(a2, a3, 0);
            sb(a1, a3, 1);
            sb(a0, a3, 2);
            sb(v0, a3, 3);
            lbu(v0, t0, 31);
            if (i64(v0) < 0) {
                // 0x0022b8cc
                charge(ctx, 7);
                a0 = srl(v0, 1);
                v0 = v0 & 0x1;
                a0 = a0 | v0;
                mtc1(a0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x0022b8b8
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x0022b8e8
            charge(ctx, 4);
            mul_s(f0, f0, f20);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x0022b910
                charge(ctx, 6);
                sub_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                v0 = v0 | v1;
                v0 = v0 & 0xFF;
            } else {
                // 0x0022b8f8
                charge(ctx, 6);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                v0 = v0 & 0xFF;
            }
            // 0x0022b928
            charge(ctx, 2);
            sb(v0, a3, 3);
            t1 = addiu(t1, 1);
        }
        // 0x0022b93c
        charge(ctx, 5);
        a0 = s2;
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x22B944u, gen::fn_sub_21DD60_0021dd60);  // (quad, ...)
        s3 = addiu(s3, 1);
    }
    // 0x0022b95c
    charge(ctx, 14);
    v1 = 198;
    sb(v1, sp, 0xAC);
    v1 = 202;
    sb(v1, sp, 0xAD);
    v1 = 219;
    sb(v1, sp, 0xAE);
    lwc1(f0, gp, -31768);  // 0x7CB0D8 = 229.5f
    mul_s(f1, f0, f20);
    v1 = 0x4F000000;
    mtc1(v1, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0022b9ac
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = lui(0x8000);
        a0 = a0 | v1;
        a0 = a0 & 0xFF;
    } else {
        // 0x0022b994
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(a0, f0);
        a0 = a0 & 0xFF;
    }
    // 0x0022b9c4
    charge(ctx, 15);
    sb(a0, sp, 0xAF);
    lbu(v1, sp, 0xAC);
    a0 = sll(v1, 24);
    lbu(v1, sp, 0xAD);
    v1 = sll(v1, 16);
    a0 = a0 | v1;
    lbu(v1, sp, 0xAE);
    v1 = sll(v1, 8);
    a0 = v1 | a0;
    lbu(v1, sp, 0xAF);
    s0 = v1 | a0;
    lw(a0, s1, kBcmSub);
    v1 = 3;
    if (a0 == v1) {
        // 0x0022bc1c
        charge(ctx, 4);
        lw(a0, s1, kBcmSubStep);
        v1 = 2;
        if (a0 != v1) {
            // 0x0022bc2c
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                goto L_0022bc40;
            }
            // 0x0022bc38
            charge(ctx, 2);
            // 0x0022bcc4 (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(ra, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xB0);
            return;
        }
    L_0022bc40:
        charge(ctx, 4);
        lw(v0, s1, 26864);
        lw(a0, v0, 36);
        if (a0 == 0) {
            // 0x0022bca0
            charge(ctx, 9);
            a0 = v0;
            a1 = 3168;
            a2 = 3048;
            jal(ctx, 0x22BCACu, gen::fn_frFontLineSetPos_003b0d70);
            lw(a0, s1, 26864);
            a1 = s0;
            jal(ctx, 0x22BCBCu, gen::fn_frFontLineSetRgba_003b0e20);
        } else {
            // 0x0022bc50
            charge(ctx, 20);
            a1 = 3168;
            a2 = 3048;
            jal(ctx, 0x22BC58u, gen::fn_frFontLineSetPos_003b0d70);
            lw(a0, s1, 26864);
            a1 = 3168;
            a2 = 3224;
            jal(ctx, 0x22BC6Cu, gen::fn_frFontLineSetPos_003b0d70);
            lw(v0, s1, 26864);
            lw(a0, v0, 36);
            a1 = s0;
            jal(ctx, 0x22BC80u, gen::fn_frFontLineSetRgba_003b0e20);
            lw(a0, s1, 26864);
            a1 = s0;
            jal(ctx, 0x22BC90u, gen::fn_frFontLineSetRgba_003b0e20);
        }
    } else {
        // 0x0022ba00
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0022ba0c
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_0022bab4;
            }
            // 0x0022ba18
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0022ba28
                charge(ctx, 4);
                lw(v0, s1, kBcmHelpChain);
                lw(a0, v0, 36);
                if (a0 == 0) {
                    // 0x0022ba88
                    charge(ctx, 11);
                    a0 = v0;
                    a1 = 4128;
                    a2 = 3048;
                    jal(ctx, 0x22BA94u, gen::fn_frFontLineSetPos_003b0d70);
                    lw(a0, s1, kBcmHelpChain);
                    a1 = s0;
                    jal(ctx, 0x22BAA4u, gen::fn_frFontLineSetRgba_003b0e20);
                } else {
                    // 0x0022ba38
                    charge(ctx, 20);
                    a1 = 4128;
                    a2 = 3048;
                    jal(ctx, 0x22BA40u, gen::fn_frFontLineSetPos_003b0d70);
                    lw(a0, s1, kBcmHelpChain);
                    a1 = 4128;
                    a2 = 3224;
                    jal(ctx, 0x22BA54u, gen::fn_frFontLineSetPos_003b0d70);
                    lw(v0, s1, kBcmHelpChain);
                    lw(a0, v0, 36);
                    a1 = s0;
                    jal(ctx, 0x22BA68u, gen::fn_frFontLineSetRgba_003b0e20);
                    lw(a0, s1, kBcmHelpChain);
                    a1 = s0;
                    jal(ctx, 0x22BA78u, gen::fn_frFontLineSetRgba_003b0e20);
                }
            } else {
                // 0x0022ba20
                charge(ctx, 2);
            }
            // 0x0022bcc4 (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(ra, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xB0);
            return;
        }
    L_0022bab4:
        charge(ctx, 4);
        lw(v0, s1, 26864);
        lw(a0, v0, 36);
        if (a0 == 0) {
            // 0x0022bb14
            charge(ctx, 9);
            a0 = v0;
            a1 = 3168;
            a2 = 3048;
            jal(ctx, 0x22BB20u, gen::fn_frFontLineSetPos_003b0d70);
            lw(a0, s1, 26864);
            a1 = s0;
            jal(ctx, 0x22BB30u, gen::fn_frFontLineSetRgba_003b0e20);
        } else {
            // 0x0022bac4
            charge(ctx, 20);
            a1 = 3168;
            a2 = 3048;
            jal(ctx, 0x22BACCu, gen::fn_frFontLineSetPos_003b0d70);
            lw(a0, s1, 26864);
            a1 = 3168;
            a2 = 3224;
            jal(ctx, 0x22BAE0u, gen::fn_frFontLineSetPos_003b0d70);
            lw(v0, s1, 26864);
            lw(a0, v0, 36);
            a1 = s0;
            jal(ctx, 0x22BAF4u, gen::fn_frFontLineSetRgba_003b0e20);
            lw(a0, s1, 26864);
            a1 = s0;
            jal(ctx, 0x22BB04u, gen::fn_frFontLineSetRgba_003b0e20);
        }
        // 0x0022bb38
        charge(ctx, 3);
        lw(v1, s1, 26872);
        if (v1 != 0) {
            // 0x0022bb44
            charge(ctx, 35);
            lw(v0, s1, 26868);
            a1 = addiu(v0, 32);
            a0 = s5;
            jal(ctx, 0x22BB50u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            v1 = 0x43210000;
            sw(v1, sp, 0x90);
            v1 = 0x43BE0000;
            sw(v1, sp, 0x94);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x98);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x9C);
            a0 = addiu(s1, 26880);
            a1 = addiu(sp, 0x90);
            jal(ctx, 0x22BB88u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
            v0 = 140;
            sb(v0, sp, 0xAC);
            v0 = 150;
            sb(v0, sp, 0xAD);
            v0 = 180;
            sb(v0, sp, 0xAE);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            mul_s(f1, f0, f20);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0022bbe8
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFF;
            } else {
                // 0x0022bbd0
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFF;
            }
            // 0x0022bc00
            charge(ctx, 7);
            sb(v1, sp, 0xAF);
            a0 = addiu(s1, 26880);
            a1 = addiu(sp, 0xAC);
            jal(ctx, 0x22BC0Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        }
    }
    // 0x0022bcc4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x0022BCF0 sub_22BCF0 -- 612 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_DrawHelp] draws the help tabs, the help line's chain and the cursor quad (page +26868 + 32).
void sub_22BCF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022bcf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0022bd1c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22BD28u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022bd30
    charge(ctx, 27);
    lw(s2, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22BD38u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    a0 = 6;
    jal(ctx, 0x22BD44u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s5 = v0;
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 1;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x22BD64u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x22BD78u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x22BD88u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s4 = 0;
    for (;;) {  // while (s4 < 3)
        // 0x0022bdf4
        charge(ctx, 3);
        v1 = slti(s4, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022bd9c
        charge(ctx, 22);
        v0 = sll(s4, 8);
        v0 = addu(s2, v0);
        s3 = addiu(v0, kBcmTabs);
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = s3;
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22BDC8u, v0.u());
        a0 = s3;
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x22BDE8u, v0.u());
        s4 = addiu(s4, 1);
    }
    // 0x0022be00
    charge(ctx, 5);
    a1 = 0;
    lw(a0, s2, kBcmSub);
    v1 = 3;
    if (a0 == v1) {
        // 0x0022be48
        charge(ctx, 4);
        lw(a0, s2, kBcmSubStep);
        v1 = 1;
        if (a0 == v1) {
            // 0x0022be60
            charge(ctx, 1);
            a1 = v1;
        } else {
            // 0x0022be58
            charge(ctx, 2);
        }
    } else {
        // 0x0022be14
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0022be20
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_0022be3c;
            }
            // 0x0022be2c
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_0022be3c;
            }
            // 0x0022be34
            charge(ctx, 2);
            goto L_0022be64;
        }
    L_0022be3c:
        charge(ctx, 3);
        a1 = 1;
    }
L_0022be64:
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x0022be6c
        charge(ctx, 8);
        lw(a0, s2, 26864);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x22BE78u, gen::fn_frFontDraw_003b1360);
        lw(v1, s2, 26872);
        if (v1 != 0) {
            // 0x0022be8c
            charge(ctx, 40);
            lw(v0, s2, 26868);
            a1 = addiu(v0, 32);
            a0 = s5;
            jal(ctx, 0x22BE98u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x22BEA4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x22BEB8u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x22BECCu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x22BEDCu, gen::fn_RpSkyRenderStateSet_004d7f60);
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s2, 26880);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x22BF04u, v0.u());
            a0 = addiu(s2, 26880);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x22BF24u, v0.u());
        }
    }
    // 0x0022bf2c (the shared epilogue, written out on this path)
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

// 0x0022C0A0 sub_22C0A0 -- 64 bytes; frame 0x10: ra sp+0x0
// [bcmPanel_ResetStep] sub-step 0.
void sub_22C0A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022c0a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v1 == 0) {
        // 0x0022c0b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22C0C0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022c0c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    sw(zero, v1, kBcmSubStep);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0022C2D0 sub_22C2D0 -- 708 bytes; frame 0x70: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [bcmPanel_LayoutDetail] the detail bar's quads (page 66 at 57, 317, its tail 133 px wide) with the panel
// alpha.
void sub_22C2D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0022c2d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    if (v0 == 0) {
        // 0x0022c2f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22C300u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bcm_panel.c", 230): `jr $ra` in retail, execution goes on
    }
    // 0x0022c308
    charge(ctx, 42);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308 bcm_panel.c work (the command panel)
    a0 = 0;
    jal(ctx, 0x22C310u, gen::fn_sub_21C3F0_0021c3f0);  // [bpRes_GetSet](i): a panel sprite set
    s2 = v0;
    lwc1(f20, s1, kBcmFade);
    a0 = s2;
    a1 = 66;
    jal(ctx, 0x22C328u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s0 = v0;
    v1 = 0x42640000;
    sw(v1, sp, 0x50);
    v1 = 317;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x54);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s1, kBcmDetailBar);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x22C370u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f20, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0022c3c8
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022c3b0
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022c3e0
    charge(ctx, 36);
    sb(v1, sp, 0x6F);
    a0 = addiu(s1, kBcmDetailBar);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x22C3ECu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lwc1(f0, s0, kSpW);
    cvt_s_w(f1, f0);
    v0 = 0x42640000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x50);
    v0 = 317;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x54);
    v0 = 0x43050000;
    sw(v0, sp, 0x58);
    lwc1(f0, s0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s1, 27392);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x22C440u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0022c488
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022c470
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022c4a0
    charge(ctx, 36);
    sb(v1, sp, 0x6F);
    a0 = addiu(s1, 27392);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x22C4ACu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s2;
    a1 = 67;
    jal(ctx, 0x22C4BCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x43C80000;
    sw(v1, sp, 0x50);
    v1 = 317;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x54);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s1, 27648);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x22C500u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0022c548
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0022c530
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0022c560
    charge(ctx, 13);
    sb(v1, sp, 0x6F);
    a0 = addiu(s1, 27648);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x22C56Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

}  // namespace p3fes::game
