// Phase 5 slice band20 -- the battle result screen: br_res.c (its resources), br_panel.c (layout / draw / digits)
// and bp_ifont.c (numbers in the sprite font, left / right / centred).
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
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_frFontClearDefaultGlyphFlags_003b0e90(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_frFontSetDefaultGlyphFlags_003b0e70(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_21C9F0_0021c9f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_21EC40_0021ec40(p3fes::EEContext&);
void fn_sub_233C00_00233c00(p3fes::EEContext&);
void fn_sub_234070_00234070(p3fes::EEContext&);
void fn_sub_234570_00234570(p3fes::EEContext&);
void fn_sub_234690_00234690(p3fes::EEContext&);
void fn_sub_234710_00234710(p3fes::EEContext&);
void fn_sub_2350F0_002350f0(p3fes::EEContext&);
void fn_sub_235F30_00235f30(p3fes::EEContext&);
void fn_sub_235FF0_00235ff0(p3fes::EEContext&);
void fn_sub_2361D0_002361d0(p3fes::EEContext&);
void fn_sub_236390_00236390(p3fes::EEContext&);
void fn_sub_238A50_00238a50(p3fes::EEContext&);
void fn_sub_238BF0_00238bf0(p3fes::EEContext&);
void fn_sub_238DC0_00238dc0(p3fes::EEContext&);
void fn_sub_239140_00239140(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b20;  // the named offsets and $gp slots of band20.h

// 0x00233C00 sub_233C00 -- 284 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brRes_RequestLvh] br_res.c: requests battle/result/AGS_br_lvh.bin / AGS2_br_lvh.bin (The Answer, flag 752)
// or br_lvh.bin into +20; requested bit 2 (K_Assert 140 / 141).
void sub_233C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00233c00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrRes);  // 0x7CE30C br_res.c work (the result resources)
    if (v0 == 0) {
        // 0x00233c18
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6496);  // "br_res.c"
        a1 = 82;
        jal(ctx, 0x233C24u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 82): `jr $ra` in retail, execution goes on
    }
    // 0x00233c2c
    charge(ctx, 6);
    lw(s0, gp, kGpBrRes);  // 0x7CE30C br_res.c work (the result resources)
    lw(v0, s0, kBrrRequested);
    v0 = nor(v0, 0);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x00233c44
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6496);  // "br_res.c"
        a1 = 140;
        jal(ctx, 0x233C50u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 140): `jr $ra` in retail, execution goes on
    }
    // 0x00233c58
    charge(ctx, 5);
    lw(v0, s0, kBrrLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x10;
    if (v0 == 0) {
        // 0x00233c6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6496);  // "br_res.c"
        a1 = 141;
        jal(ctx, 0x233C78u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 141): `jr $ra` in retail, execution goes on
    }
    // 0x00233c80
    charge(ctx, 4);
    jal(ctx, 0x233C80u, gen::fn_sub_17D800_0017d800);  // the game-mode test (The Answer)
    if (v0 == 0) {
        // 0x00233ce4
        charge(ctx, 6);
        a0 = 0x690000;
        a0 = addiu(a0, -6288);  // "battle/result/br_lvh.bin"
        a1 = 1;
        jal(ctx, 0x233CF0u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
        sw(v0, s0, kBrrLvhNode);
    } else {
        // 0x00233c90
        charge(ctx, 5);
        a0 = 752;
        jal(ctx, 0x233C94u, gen::fn_datGetFlag_0016f190);  // datGetFlag(id)
        if (v0 == 0) {
            // 0x00233cc4
            charge(ctx, 8);
            a0 = 0x690000;
            a0 = addiu(a0, -6320);  // "battle/result/AGS2_br_lvh.bin"
            a1 = 1;
            jal(ctx, 0x233CD0u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
            sw(v0, s0, kBrrLvhNode);
        } else {
            // 0x00233ca4
            charge(ctx, 8);
            a0 = 0x690000;
            a0 = addiu(a0, -6352);  // "battle/result/AGS_br_lvh.bin"
            a1 = 1;
            jal(ctx, 0x233CB0u, gen::fn_H_Cdvd_Request_00100d80);  // H_Cdvd_Request(path, isArchive)
            sw(v0, s0, kBrrLvhNode);
        }
    }
    // 0x00233cfc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s0, kBrrRequested);
    v1 = v1 | 0x4;
    sw(v1, s0, kBrrRequested);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00234070 sub_234070 -- 1276 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brRes_Update] br_res.c's loader: the result archives' files become sprite sets / heap copies / rasters
// when their nodes have loaded; requested -> loaded.
void sub_234070(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00234070
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBrRes);  // 0x7CE30C br_res.c work (the result resources)
    if (v1 == 0) {
        // 0x00234090
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6496);  // "br_res.c"
        a1 = 82;
        jal(ctx, 0x23409Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 82): `jr $ra` in retail, execution goes on
    }
    // 0x002340a4
    charge(ctx, 5);
    lw(s0, gp, kGpBrRes);  // 0x7CE30C br_res.c work (the result resources)
    lw(v1, s0, kBrrRequested);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002340b8
        charge(ctx, 5);
        lw(a1, s0, kBrrLoaded);
        a0 = nor(a1, 0);
        v1 = a0 & 0x1;
        if (v1 == 0) {
            // 0x002341d0
            charge(ctx, 3);
            v1 = a1 & 0x1;
            if (v1 != 0) {
                // 0x002341dc
                charge(ctx, 3);
                v1 = a1 & 0x2;
                if (v1 == 0) {
                    goto L_002341e8;
                }
                goto L_002341fc;
            }
        L_002341e8:
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -6496);  // "br_res.c"
            a1 = 265;
            jal(ctx, 0x2341F4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 265): `jr $ra` in retail, execution goes on
        } else {
            // 0x002340cc
            charge(ctx, 3);
            v0 = a0 & 0x2;
            if (v0 == 0) {
                // 0x002340d8
                charge(ctx, 5);
                a0 = 0x690000;
                a0 = addiu(a0, -6496);  // "br_res.c"
                a1 = 234;
                jal(ctx, 0x2340E4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 234): `jr $ra` in retail, execution goes on
            }
            // 0x002340ec
            charge(ctx, 5);
            lw(a0, s0, 12);
            jal(ctx, 0x2340F0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
            if (v0 != 0) {
                // 0x00234100
                charge(ctx, 3);
                s1 = 0;
                for (;;) {  // while (s1 < 2)
                    // 0x002341b0
                    charge(ctx, 3);
                    v0 = slti(s1, 2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0023410c
                    charge(ctx, 3);
                    v0 = 1;
                    if (s1 == v0) {
                        // 0x00234160
                        charge(ctx, 14);
                        lw(a0, s0, 12);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x23416Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                        a0 = v0;
                        jal(ctx, 0x234178u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                        sw(v0, s0, kBrrSetB);
                        lw(v0, s0, kBrrLoaded);
                        v0 = v0 | 0x2;
                        sw(v0, s0, kBrrLoaded);
                    } else {
                        // 0x00234118
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x00234128
                            charge(ctx, 14);
                            lw(a0, s0, 12);
                            a1 = s1;
                            a2 = addiu(sp, 0x4C);
                            jal(ctx, 0x234134u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            a0 = v0;
                            jal(ctx, 0x234140u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                            sw(v0, s0, kBrrSetA);
                            lw(v0, s0, kBrrLoaded);
                            v0 = v0 | 0x1;
                            sw(v0, s0, kBrrLoaded);
                        } else {
                            // 0x00234120
                            charge(ctx, 2);
                            // 0x00234198
                            charge(ctx, 5);
                            a0 = 0x690000;
                            a0 = addiu(a0, -6496);  // "br_res.c"
                            a1 = 254;
                            jal(ctx, 0x2341A4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 254): `jr $ra` in retail, execution goes on
                        }
                    }
                    // 0x002341ac
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x002341bc
                charge(ctx, 5);
                lw(a0, s0, 12);
                jal(ctx, 0x2341C0u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
            }
        }
    L_002341fc:
        charge(ctx, 4);
        lw(a0, s0, 4);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            // 0x0023420c
            charge(ctx, 3);
            v1 = a0 & 0x2;
            if (v1 != 0) {
                // 0x00234218
                charge(ctx, 4);
                lw(a0, s0, 0);
                v1 = si(-2);
                v1 = a0 & v1;
                sw(v1, s0, 0);
            }
        }
    }
    // 0x00234228
    charge(ctx, 4);
    lw(v1, s0, 0);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x00234238
        charge(ctx, 5);
        lw(a0, s0, 16);
        jal(ctx, 0x23423Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0023424c
            charge(ctx, 3);
            s1 = 0;
            for (;;) {  // while (s1 < 5)
                // 0x002343d4
                charge(ctx, 3);
                v0 = slti(s1, 5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00234258
                charge(ctx, 3);
                v0 = 4;
                if (s1 == v0) {
                    // 0x00234390
                    charge(ctx, 11);
                    lw(a0, s0, 16);
                    a1 = s1;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x23439Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                    a0 = 1;
                    a1 = v0;
                    jal(ctx, 0x2343ACu, gen::fn_sub_234690_00234690);
                } else {
                    // 0x00234264
                    charge(ctx, 3);
                    v0 = 3;
                    if (s1 == v0) {
                        // 0x00234364
                        charge(ctx, 11);
                        lw(a0, s0, 16);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x234370u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                        a0 = 0;
                        a1 = v0;
                        jal(ctx, 0x234380u, gen::fn_sub_234690_00234690);
                    } else {
                        // 0x00234270
                        charge(ctx, 3);
                        v0 = 2;
                        if (s1 == v0) {
                            // 0x00234338
                            charge(ctx, 11);
                            lw(a0, s0, 16);
                            a1 = s1;
                            a2 = addiu(sp, 0x4C);
                            jal(ctx, 0x234344u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                            lw(a1, sp, 0x4C);
                            a0 = v0;
                            jal(ctx, 0x234354u, gen::fn_sub_234710_00234710);
                        } else {
                            // 0x0023427c
                            charge(ctx, 3);
                            v0 = 1;
                            if (s1 == v0) {
                                // 0x002342e8
                                charge(ctx, 20);
                                lw(a0, s0, 16);
                                a1 = s1;
                                a2 = addiu(sp, 0x4C);
                                jal(ctx, 0x2342F4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                                s2 = v0;
                                lw(a0, sp, 0x4C);
                                a1 = 0x40000;
                                v0 = 0x960000;
                                lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                                jalr(ctx, 0x234310u, v0.u());
                                sw(v0, s0, 40);
                                lw(a2, sp, 0x4C);
                                a0 = v0;
                                a1 = s2;
                                jal(ctx, 0x234328u, gen::fn_memcpy_00521250);
                            } else {
                                // 0x00234288
                                charge(ctx, 2);
                                if (s1 == 0) {
                                    // 0x00234298
                                    charge(ctx, 20);
                                    lw(a0, s0, 16);
                                    a1 = s1;
                                    a2 = addiu(sp, 0x4C);
                                    jal(ctx, 0x2342A4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                                    s2 = v0;
                                    lw(a0, sp, 0x4C);
                                    a1 = 0x40000;
                                    v0 = 0x960000;
                                    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                                    jalr(ctx, 0x2342C0u, v0.u());
                                    sw(v0, s0, 36);
                                    lw(a2, sp, 0x4C);
                                    a0 = v0;
                                    a1 = s2;
                                    jal(ctx, 0x2342D8u, gen::fn_memcpy_00521250);
                                } else {
                                    // 0x00234290
                                    charge(ctx, 2);
                                    // 0x002343bc
                                    charge(ctx, 5);
                                    a0 = 0x690000;
                                    a0 = addiu(a0, -6496);  // "br_res.c"
                                    a1 = 306;
                                    jal(ctx, 0x2343C8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 306): `jr $ra` in retail, execution goes on
                                }
                            }
                        }
                    }
                }
                // 0x002343d0
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x002343e0
            charge(ctx, 10);
            lw(v0, s0, 4);
            v0 = v0 | 0x4;
            sw(v0, s0, 4);
            lw(a0, s0, 16);
            jal(ctx, 0x2343F0u, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
            lw(a0, s0, 0);
            v1 = si(-3);
            v1 = a0 & v1;
            sw(v1, s0, 0);
        }
    }
    // 0x00234408
    charge(ctx, 4);
    lw(v1, s0, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x00234418
        charge(ctx, 5);
        lw(a0, s0, 20);
        jal(ctx, 0x23441Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);  // H_Cdvd_IsFileLoaded(node)
        if (v0 != 0) {
            // 0x0023442c
            charge(ctx, 3);
            s1 = 0;
            for (;;) {  // while (s1 < 6)
                // 0x0023451c
                charge(ctx, 3);
                v0 = slti(s1, 6);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00234438
                charge(ctx, 8);
                lw(a0, s0, 20);
                a1 = s1;
                a2 = addiu(sp, 0x4C);
                jal(ctx, 0x234444u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // H_Cdvd_ArchiveGetFile(node, i, &size)
                at = sltiu(s1, 6);
                if (at == 0) {
                    // 0x00234504
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -6496);  // "br_res.c"
                    a1 = 345;
                    jal(ctx, 0x234510u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_res.c", 345): `jr $ra` in retail, execution goes on
                } else {
                    // 0x00234458
                    charge(ctx, 7);
                    a0 = 0x7B0000;
                    a0 = addiu(a0, 30784);  // "tD#"
                    v1 = sll(s1, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    switch (v1.u()) {
                    case 0x234474u:  // table[0]
                        // 0x00234474
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x234478u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                        sw(v0, s0, 56);
                        break;
                    case 0x23448Cu:  // table[1]
                        // 0x0023448c
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x234490u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                        sw(v0, s0, 72);
                        break;
                    case 0x2344A4u:  // table[2]
                        // 0x002344a4
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x2344A8u, gen::fn_sub_21EC40_0021ec40);  // [bpTex_CreateRaster](image) -> RwRaster
                        sw(v0, s0, 76);
                        break;
                    case 0x2344BCu:  // table[4]
                        // 0x002344bc
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x2344C0u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                        sw(v0, s0, 60);
                        break;
                    case 0x2344D4u:  // table[5]
                        // 0x002344d4
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x2344D8u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                        sw(v0, s0, 64);
                        break;
                    case 0x2344ECu:  // table[3]
                        // 0x002344ec
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x2344F0u, gen::fn_sub_21C9F0_0021c9f0);  // [bpTex_CreateSpriteSet](file) -> sprite set
                        sw(v0, s0, 68);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v1.u());
                        return;
                    }
                }
                // 0x00234518
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00234528
            charge(ctx, 10);
            lw(a0, s0, 20);
            jal(ctx, 0x23452Cu, gen::fn_H_Cdvd_Destroy_00100ec0);  // H_Cdvd_Destroy(node)
            lw(v1, s0, 4);
            v1 = v1 | 0x10;
            sw(v1, s0, 4);
            lw(a0, s0, 0);
            v1 = si(-5);
            v1 = a0 & v1;
            sw(v1, s0, 0);
        }
    }
    // 0x00234550 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002350F0 sub_2350F0 -- 3644 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brPanel_Draw] draws the result panel (sub_1F08C0 / sub_1F0900): render states, the quads as Im2D
// triangle pairs, the font chains.
void sub_2350F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002350f0
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
    lw(v1, gp, kGpBrPanel);  // 0x7CE310 br_panel.c work (the result panel)
    if (v1 == 0) {
        // 0x00235128
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6256);  // "br_panel.c"
        a1 = 153;
        jal(ctx, 0x235134u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_panel.c", 153): `jr $ra` in retail, execution goes on
    }
    // 0x0023513c
    charge(ctx, 6);
    lw(s2, gp, kGpBrPanel);  // 0x7CE310 br_panel.c work (the result panel)
    lw(v1, s2, kBrpFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00235154
        charge(ctx, 173);
        a0 = 0;
        jal(ctx, 0x235158u, gen::fn_sub_234570_00234570);
        s5 = v0;
        a0 = 1;
        jal(ctx, 0x235168u, gen::fn_sub_234570_00234570);
        s7 = v0;
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235188u, v0.u());
        a0 = 20;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23519Cu, v0.u());
        a0 = 8;
        a1 = 1;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2351B0u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2351C4u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x2351D8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2351E8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 1;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2351FCu, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 9568);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235224u, v0.u());
        a0 = addiu(s2, 9568);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235244u, v0.u());
        a0 = 8;
        a1 = 1;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235258u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23526Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x235280u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x235290u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 1;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2352A4u, v0.u());
        a0 = addiu(s2, 8800);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2352C4u, v0.u());
        a0 = addiu(s2, 8800);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2352E4u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2352F8u, v0.u());
        a0 = 6;
        a1 = 1;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23530Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x235320u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x235330u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = s5;
        a1 = 4;
        jal(ctx, 0x235340u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x23534Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235360u, v0.u());
        a0 = addiu(s2, 3360);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235380u, v0.u());
        a0 = addiu(s2, 3360);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2353A0u, v0.u());
        a0 = s7;
        a1 = 13;
        jal(ctx, 0x2353B0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2353BCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2353D0u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x2353E4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2353F4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s3 = 0;
        for (;;) {  // while (s3 < 7)
            // 0x00235460
            charge(ctx, 3);
            v0 = slti(s3, 7);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00235408
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s2, v0);
            s0 = addiu(v0, 1312);
            s4 = 0x960000;
            s4 = addiu(s4, 156);  // &0x96009C
            a0 = s0;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235434u, v0.u());
            a0 = s0;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235454u, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x0023546c
        charge(ctx, 51);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x235478u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x235488u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = s5;
        a1 = 2;
        jal(ctx, 0x235498u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2354A4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x2354B8u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 3104);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2354E0u, v0.u());
        a0 = addiu(s2, 3104);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235500u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x235514u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x235524u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s3 = 0;
        for (;;) {
            // 0x00235844
            charge(ctx, 4);
            lw(v0, s2, 7504);
            v0 = slt(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00235538
            charge(ctx, 121);
            v0 = sll(s3, 3);
            v1 = addu(v0, s3);
            v0 = sll(v1, 3);
            v0 = addu(v1, v0);
            v0 = sll(v0, 4);
            v0 = addu(s2, v0);
            s0 = addiu(v0, 3616);
            a0 = s5;
            a1 = 4;
            jal(ctx, 0x23555Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            fp = 0x960000;
            fp = addiu(fp, 0x90);
            a0 = v0;
            jal(ctx, 0x235570u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, fp, 0x0);
            jalr(ctx, 0x235584u, v0.u());
            s4 = 0x960000;
            s4 = addiu(s4, 156);  // &0x96009C
            a0 = addiu(s0, 16);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2355ACu, v0.u());
            a0 = addiu(s0, 16);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2355CCu, v0.u());
            a0 = 64;
            jal(ctx, 0x2355D8u, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x2355ECu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x2355FCu, gen::fn_RpSkyRenderStateSet_004d7f60);
            lw(a0, s0, 12);
            a1 = 1;
            a2 = 0;
            jal(ctx, 0x235610u, gen::fn_frFontDraw_003b1360);
            a0 = 64;
            jal(ctx, 0x23561Cu, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x235630u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x235640u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = s5;
            a1 = 1;
            jal(ctx, 0x235650u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x23565Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, fp, 0x0);
            jalr(ctx, 0x235670u, v0.u());
            a0 = addiu(s0, 272);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235690u, v0.u());
            a0 = addiu(s0, 272);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x2356B0u, v0.u());
            a0 = s7;
            a1 = 0;
            jal(ctx, 0x2356C0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s6 = v0;
            a0 = s6;
            jal(ctx, 0x2356D0u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, fp, 0x0);
            jalr(ctx, 0x2356E4u, v0.u());
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x2356F8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x235708u, gen::fn_RpSkyRenderStateSet_004d7f60);
            s4 = 0;
            for (;;) {  // while (s4 < 2)
                // 0x0023577c
                charge(ctx, 3);
                v0 = slti(s4, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0023571c
                charge(ctx, 24);
                v0 = sll(s4, 8);
                v0 = addu(s0, v0);
                fp = addiu(v0, 0x210);
                v0 = 0x960000;
                v0 = addiu(v0, 156);  // &0x96009C
                sq(v0, sp, 0xA0);
                a0 = fp;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, v0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
                jalr(ctx, 0x23574Cu, v0.u());
                a0 = fp;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lq(v0, sp, 0xA0);
                lw(v0, v0, 0);
                jalr(ctx, 0x235770u, v0.u());
                s4 = addiu(s4, 1);
            }
            // 0x00235788
            charge(ctx, 4);
            lw(v1, s0, 0);
            v0 = 1;
            if (v1 == v0) {
                // 0x002357c4
                charge(ctx, 5);
                a0 = s7;
                a1 = 11;
                jal(ctx, 0x2357CCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s6 = v0;
            } else {
                // 0x00235798
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x002357a8
                    charge(ctx, 7);
                    a0 = s7;
                    a1 = 10;
                    jal(ctx, 0x2357B0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                    s6 = v0;
                } else {
                    // 0x002357a0
                    charge(ctx, 2);
                }
            }
            // 0x002357d8
            charge(ctx, 27);
            a0 = s6;
            jal(ctx, 0x2357DCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);
            jalr(ctx, 0x2357F0u, v0.u());
            s4 = 0x960000;
            s4 = addiu(s4, 156);  // &0x96009C
            a0 = addiu(s0, 1040);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235818u, v0.u());
            a0 = addiu(s0, 1040);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s4, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235838u, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00235854
        charge(ctx, 197);
        s3 = 0x960000;
        s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
        a0 = 8;
        a1 = 0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235868u, v0.u());
        a0 = 6;
        a1 = 1;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x23587Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x235890u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x2358A0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = s5;
        a1 = 0;
        jal(ctx, 0x2358B0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2358BCu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2358D0u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2358F8u, v0.u());
        a0 = addiu(s2, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235918u, v0.u());
        a0 = s5;
        a1 = 5;
        jal(ctx, 0x235928u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x235934u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235948u, v0.u());
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235968u, v0.u());
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235988u, v0.u());
        a0 = s5;
        a1 = 3;
        jal(ctx, 0x235998u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x2359A4u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2359B8u, v0.u());
        a0 = addiu(s2, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2359D8u, v0.u());
        a0 = addiu(s2, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x2359F8u, v0.u());
        a0 = 64;
        jal(ctx, 0x235A04u, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
        lw(a0, s2, 784);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x235A18u, gen::fn_frFontDraw_003b1360);
        a0 = 64;
        jal(ctx, 0x235A24u, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
        a0 = 1;
        jal(ctx, 0x235A30u, gen::fn_sub_239140_00239140);  // (quad*, n): draw n quads
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235A44u, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x235A58u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x235A68u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 800);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235A88u, v0.u());
        a0 = addiu(s2, 800);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235AA8u, v0.u());
        a0 = addiu(s2, 1056);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235AC8u, v0.u());
        a0 = addiu(s2, 1056);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235AE8u, v0.u());
        a0 = 6;
        a1 = 1;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235AFCu, v0.u());
        a0 = 1;
        a1 = 0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235B10u, v0.u());
        a0 = addiu(s2, 9312);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235B30u, v0.u());
        a0 = addiu(s2, 9312);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235B50u, v0.u());
        lw(v1, s2, 9836);
        v0 = 2;
        if (v1 == v0) {
            // 0x00235bd4
            charge(ctx, 34);
            s0 = s3;
            a0 = 6;
            a1 = 0;
            lw(v0, s0, 0);
            jalr(ctx, 0x235BE4u, v0.u());
            a0 = 8;
            a1 = 0;
            lw(v0, s0, 0);
            jalr(ctx, 0x235BF8u, v0.u());
            a0 = 1;
            a1 = 0;
            lw(v0, s0, 0);
            jalr(ctx, 0x235C0Cu, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s2, 9056);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235C34u, v0.u());
            a0 = addiu(s2, 9056);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
            jalr(ctx, 0x235C54u, v0.u());
        } else {
            // 0x00235b68
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x00235b7c
                charge(ctx, 22);
                a1 = 0;
                lw(v0, s1, 0);
                jalr(ctx, 0x235B84u, v0.u());
                a0 = addiu(s2, 9056);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);
                jalr(ctx, 0x235BA4u, v0.u());
                a0 = addiu(s2, 9056);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);
                jalr(ctx, 0x235BC4u, v0.u());
            } else {
                // 0x00235b74
                charge(ctx, 2);
            }
        }
        // 0x00235c5c
        charge(ctx, 69);
        s3 = 0x960000;
        s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
        a0 = 6;
        a1 = 1;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235C70u, v0.u());
        a0 = s5;
        a1 = 6;
        jal(ctx, 0x235C80u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x235C8Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235CA0u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 7520);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235CC8u, v0.u());
        a0 = addiu(s2, 7520);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235CE8u, v0.u());
        a0 = s5;
        a1 = 9;
        jal(ctx, 0x235CF8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        a0 = v0;
        jal(ctx, 0x235D04u, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x235D18u, v0.u());
        a0 = addiu(s2, 7776);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235D38u, v0.u());
        a0 = addiu(s2, 7776);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235D58u, v0.u());
        lw(v0, s2, kBrpFlags);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x00235d88
            charge(ctx, 4);
            a0 = s5;
            a1 = 8;
            jal(ctx, 0x235D90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        } else {
            // 0x00235d70
            charge(ctx, 6);
            a0 = s5;
            a1 = 10;
            jal(ctx, 0x235D78u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        }
        // 0x00235d98
        charge(ctx, 30);
        a0 = v0;
        jal(ctx, 0x235D9Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
        a0 = 1;
        a1 = v0;
        lw(v0, s1, 0);
        jalr(ctx, 0x235DB0u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 8032);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235DD8u, v0.u());
        a0 = addiu(s2, 8032);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C (RwIm2DRenderTriangle slot)
        jalr(ctx, 0x235DF8u, v0.u());
        lw(v1, s2, kBrpFlags);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x00235e10
            charge(ctx, 58);
            a0 = s5;
            a1 = 7;
            jal(ctx, 0x235E18u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s1 = 0x960000;
            s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
            a0 = v0;
            jal(ctx, 0x235E2Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x235E40u, v0.u());
            a0 = addiu(s2, 8544);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);
            jalr(ctx, 0x235E60u, v0.u());
            a0 = addiu(s2, 8544);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);
            jalr(ctx, 0x235E80u, v0.u());
            a0 = s5;
            a1 = 9;
            jal(ctx, 0x235E90u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            a0 = v0;
            jal(ctx, 0x235E9Cu, gen::fn_sub_21CCE0_0021cce0);  // (page) -> its raster
            a0 = 1;
            a1 = v0;
            lw(v0, s1, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x235EB0u, v0.u());
            a0 = addiu(s2, 8288);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);
            jalr(ctx, 0x235ED0u, v0.u());
            a0 = addiu(s2, 8288);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);
            jalr(ctx, 0x235EF0u, v0.u());
        }
    }
    // 0x00235ef8 (the shared epilogue, written out on this path)
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

// 0x00235F30 sub_235F30 -- 192 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brPanel_SetDigitPages](quads, n, ...) prints n (format 0x7CC45C) and sets each digit (sub_2361D0);
// K_Assert 621 for too many digits.
void sub_235F30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00235f30
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s1 = a1;
    s2 = a3;
    a0 = addiu(sp, 0x50);
    a1 = addiu(gp, -26772);  // "%d"
    jal(ctx, 0x235F5Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x235F68u, gen::fn_strlen_00524388);
    s0 = v0;
    at = slt(s1, s0);
    if (at != 0) {
        // 0x00235f80
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6256);  // "br_panel.c"
        a1 = 621;
        jal(ctx, 0x235F8Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_panel.c", 621): `jr $ra` in retail, execution goes on
    }
    // 0x00235f94
    charge(ctx, 3);
    s1 = 0;
    for (;;) {  // while (s1 < s0)
        // 0x00235fc4
        charge(ctx, 3);
        v1 = slt(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00235fa0
        charge(ctx, 9);
        v0 = sll(s1, 8);
        a0 = addu(s3, v0);
        v0 = addu(s1, sp);
        lb(v0, v0, 80);
        a1 = addiu(v0, -48);
        a2 = s2;
        jal(ctx, 0x235FB8u, gen::fn_sub_2361D0_002361d0);
        s1 = addiu(s1, 1);
    }
    // 0x00235fd0
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x00235FF0 sub_235FF0 -- 468 bytes; frame 0x1B0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brPanel_PlaceDigits](quads, n, value, style, xy*) places the digits of `value` (style 1: pages
// 0..9, 16 px; style 0: pages digit - 35 + 48.., 23 px) of result set 1; K_Assert 641.
void sub_235FF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00235ff0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
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
    s6 = a0;
    s7 = a1;
    fp = a3;
    s0 = t0;
    a0 = addiu(sp, 0xA0);
    a1 = addiu(gp, -26772);  // "%d"
    jal(ctx, 0x236034u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0xA0);
    jal(ctx, 0x236040u, gen::fn_strlen_00524388);
    s2 = v0;
    at = slt(s7, s2);
    if (at != 0) {
        // 0x00236058
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6256);  // "br_panel.c"
        a1 = 641;
        jal(ctx, 0x236064u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_panel.c", 641): `jr $ra` in retail, execution goes on
    }
    // 0x0023606c
    charge(ctx, 7);
    a0 = 1;
    jal(ctx, 0x236070u, gen::fn_sub_234570_00234570);
    s5 = v0;
    s3 = 0;
    for (;;) {  // while (s3 < s2)
        // 0x00236140
        charge(ctx, 3);
        v1 = slt(s3, s2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00236088
        charge(ctx, 8);
        v0 = addiu(s2, -1);
        v0 = subu(v0, s3);
        v0 = addu(v0, sp);
        lb(v0, v0, 160);
        a1 = addiu(v0, -48);
        v0 = 1;
        if (fp == v0) {
            // 0x002360d8
            charge(ctx, 5);
            a0 = s5;
            jal(ctx, 0x2360DCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s4 = v0;
            s1 = 16;
        } else {
            // 0x002360a8
            charge(ctx, 2);
            if (fp == 0) {
                // 0x002360b8
                charge(ctx, 8);
                a1 = addiu(a1, 13);
                a0 = s5;
                jal(ctx, 0x2360C0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s4 = v0;
                s1 = 23;
            } else {
                // 0x002360b0
                charge(ctx, 2);
            }
        }
        // 0x002360ec
        charge(ctx, 21);
        lwc1(f1, s0, 0);
        mult(v0, s1, s3);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x1A0);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x1A4);
        lwc1(f0, s4, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x1A8);
        lwc1(f0, s4, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x1AC);
        v0 = sll(s3, 8);
        a0 = addu(s6, v0);
        a1 = addiu(sp, 0x1A0);
        jal(ctx, 0x236134u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s3 = addiu(s3, 1);
    }
    // 0x0023614c
    charge(ctx, 2);
    for (;;) {  // while (s2 < s7)
        // 0x00236184
        charge(ctx, 3);
        v1 = slt(s2, s7);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00236154
        charge(ctx, 12);
        lwc1(f0, s0, 0);
        swc1(f0, sp, 0x1A0);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x1A4);
        sw(zero, sp, 0x1A8);
        sw(zero, sp, 0x1AC);
        v0 = sll(s2, 8);
        a0 = addu(s6, v0);
        a1 = addiu(sp, 0x1A0);
        jal(ctx, 0x236178u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s2 = addiu(s2, 1);
    }
    // 0x00236190
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
    sp = addiu(sp, 0x1B0);
}

// 0x00236390 sub_236390 -- 9704 bytes; frame 0x2E0: ra sp+0xA0, s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [brPanel_Layout] the result panel's layout: the fade (+9836 mode, +9832 frame), the frame, the yen / exp
// numbers (sub_235FF0, bpIfont sub_238A50), the per-member rows, the font lines.
void sub_236390(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28};
    // 0x00236390
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(ra, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
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
    lw(v0, gp, kGpBrPanel);  // 0x7CE310 br_panel.c work (the result panel)
    if (v0 == 0) {
        // 0x002363e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6256);  // "br_panel.c"
        a1 = 153;
        jal(ctx, 0x2363F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_panel.c", 153): `jr $ra` in retail, execution goes on
    }
    // 0x002363f8
    charge(ctx, 23);
    lw(s3, gp, kGpBrPanel);  // 0x7CE310 br_panel.c work (the result panel)
    v0 = 0x40000000;
    mtc1(v0, f0);
    sqrt_s(f24, f0);
    a0 = 0;
    jal(ctx, 0x236418u, gen::fn_sub_234570_00234570);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x236428u, gen::fn_sub_234570_00234570);
    s6 = v0;
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x23643Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    lw(a0, s3, 9836);
    v1 = 2;
    if (a0 == v1) {
        // 0x002364f8
        charge(ctx, 4);
        lw(v1, v0, kSpW);
        v0 = sra(v1, 1);
        if (i64(v1) < 0) {
            // 0x00236508
            charge(ctx, 2);
            v0 = addiu(v1, 1);
            v0 = sra(v0, 1);
        }
        // 0x00236510
        charge(ctx, 7);
        mtc1(v0, f0);
        cvt_s_w(f27, f0);
        lw(v0, s3, 9832);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x00236564
            charge(ctx, 1);
            mtc1(zero, f26);
        } else {
            // 0x0023652c
            charge(ctx, 14);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            mul_s(f27, f1, f27);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f26, f0, f1);
        }
    } else {
        // 0x00236454
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x00236484
            charge(ctx, 8);
            lwc1(f0, v0, kSpW);
            cvt_s_w(f27, f0);
            v0 = 0x3F800000;
            mtc1(v0, f26);
            lw(v0, s3, 9832);
            at = slti(v0, 2);
            if (at == 0) {
                // 0x002364ac
                charge(ctx, 3);
                at = slti(v0, 8);
                if (at == 0) {
                    // 0x002364ec
                    charge(ctx, 3);
                    mtc1(zero, f27);
                } else {
                    // 0x002364b8
                    charge(ctx, 13);
                    v0 = addiu(v0, -2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    div_s(f0, f1, f0);
                    sub_s(f0, f26, f0);
                    mul_s(f27, f0, f27);
                }
            } else {
                // 0x002364a4
                charge(ctx, 2);
            }
        } else {
            // 0x00236460
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00236470
                charge(ctx, 5);
                mtc1(zero, f27);
                mov_s(f26, f27);
            } else {
                // 0x00236468
                charge(ctx, 2);
            }
        }
    }
    // 0x00236568
    charge(ctx, 43);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x236570u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 381;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f27);
    swc1(f0, sp, 0x2B0);
    v1 = 0x425C0000;
    sw(v1, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 16);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x2365B8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = 40;
    jal(ctx, 0x2365C4u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 16);
    mov_s(f12, f0);
    jal(ctx, 0x2365D4u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0023662c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00236614
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00236644
    charge(ctx, 9);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 16);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x236650u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x00236724
        charge(ctx, 3);
        lw(v0, s3, 9832);
        if (i64(v0) >= 0) {
            // 0x00236744
            charge(ctx, 3);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x00236794
                charge(ctx, 3);
                v0 = 0x42C80000;
                mtc1(v0, f27);
                mtc1(zero, f26);
            } else {
                // 0x00236750
                charge(ctx, 17);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x42C80000;
                mtc1(v0, f0);
                mul_s(f27, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f26, f0, f1);
            }
        } else {
            // 0x00236730
            charge(ctx, 5);
            mtc1(zero, f27);
            v0 = 0x3F800000;
            mtc1(v0, f26);
        }
    } else {
        // 0x00236668
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00236698
            charge(ctx, 4);
            lw(v0, s3, 9832);
            at = slti(v0, 3);
            if (at == 0) {
                // 0x002366bc
                charge(ctx, 3);
                at = slti(v0, 9);
                if (at == 0) {
                    // 0x00236710
                    charge(ctx, 5);
                    mtc1(zero, f27);
                    v0 = 0x3F800000;
                    mtc1(v0, f26);
                } else {
                    // 0x002366c8
                    charge(ctx, 18);
                    v0 = addiu(v0, -3);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    div_s(f26, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f1, f0, f26);
                    v0 = 0x42C80000;
                    mtc1(v0, f0);
                    mul_s(f27, f1, f0);
                }
            } else {
                // 0x002366a8
                charge(ctx, 5);
                v0 = 0x42C80000;
                mtc1(v0, f27);
                mtc1(zero, f26);
            }
        } else {
            // 0x00236674
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00236684
                charge(ctx, 5);
                mtc1(zero, f27);
                mov_s(f26, f27);
            } else {
                // 0x0023667c
                charge(ctx, 2);
            }
        }
    }
    // 0x002367a0
    charge(ctx, 43);
    a0 = s0;
    a1 = 5;
    jal(ctx, 0x2367A8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 397;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f27);
    swc1(f0, sp, 0x2B0);
    v1 = 0x43AB0000;
    sw(v1, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 272);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x2367F0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = 40;
    jal(ctx, 0x2367FCu, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 272);
    mov_s(f12, f0);
    jal(ctx, 0x23680Cu, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00236864
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0023684c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0023687c
    charge(ctx, 9);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 272);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x236888u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x0023695c
        charge(ctx, 3);
        lw(v0, s3, 9832);
        if (i64(v0) >= 0) {
            // 0x0023697c
            charge(ctx, 3);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x002369cc
                charge(ctx, 3);
                v0 = 0x42200000;
                mtc1(v0, f27);
                mtc1(zero, f26);
            } else {
                // 0x00236988
                charge(ctx, 17);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                mul_s(f27, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f26, f0, f1);
            }
        } else {
            // 0x00236968
            charge(ctx, 5);
            mtc1(zero, f27);
            v0 = 0x3F800000;
            mtc1(v0, f26);
        }
    } else {
        // 0x002368a0
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x002368d0
            charge(ctx, 4);
            lw(v0, s3, 9832);
            at = slti(v0, 4);
            if (at == 0) {
                // 0x002368f4
                charge(ctx, 3);
                at = slti(v0, 10);
                if (at == 0) {
                    // 0x00236948
                    charge(ctx, 5);
                    mtc1(zero, f27);
                    v0 = 0x3F800000;
                    mtc1(v0, f26);
                } else {
                    // 0x00236900
                    charge(ctx, 18);
                    v0 = addiu(v0, -4);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    div_s(f26, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f1, f0, f26);
                    v0 = 0x42480000;
                    mtc1(v0, f0);
                    mul_s(f27, f1, f0);
                }
            } else {
                // 0x002368e0
                charge(ctx, 5);
                v0 = 0x42480000;
                mtc1(v0, f27);
                mtc1(zero, f26);
            }
        } else {
            // 0x002368ac
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002368bc
                charge(ctx, 5);
                mtc1(zero, f27);
                mov_s(f26, f27);
            } else {
                // 0x002368b4
                charge(ctx, 2);
            }
        }
    }
    // 0x002369d8
    charge(ctx, 43);
    a0 = s0;
    a1 = 3;
    jal(ctx, 0x2369E0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 413;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f27);
    swc1(f0, sp, 0x2B0);
    v1 = 0x43BA0000;
    sw(v1, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 528);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x236A28u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = 40;
    jal(ctx, 0x236A34u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 528);
    mov_s(f12, f0);
    jal(ctx, 0x236A44u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f20, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00236a9c
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00236a84
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00236ab4
    charge(ctx, 8);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 528);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x236AC0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v0, s3, 9824);
    if (i64(v0) > 0) {
        // 0x00236ad4
        charge(ctx, 3);
        at = slti(v0, 100);
        if (at == 0) {
            goto L_00236ae0;
        }
        goto L_00236af4;
    }
L_00236ae0:
    charge(ctx, 5);
    a0 = 0x690000;
    a0 = addiu(a0, -6256);  // "br_panel.c"
    a1 = 957;
    jal(ctx, 0x236AECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("br_panel.c", 957): `jr $ra` in retail, execution goes on
L_00236af4:
    charge(ctx, 4);
    lw(v0, s3, 9824);
    v0 = slti(v0, 10);
    if (v0 != 0) {
        // 0x00236b2c
        charge(ctx, 8);
        v0 = 473;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f27);
        swc1(f0, sp, 0x2B0);
        v0 = 0x43BA0000;
        sw(v0, sp, 0x2B4);
    } else {
        // 0x00236b04
        charge(ctx, 10);
        v0 = 465;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f27);
        swc1(f0, sp, 0x2B0);
        v0 = 0x43BA0000;
        sw(v0, sp, 0x2B4);
    }
    // 0x00236b4c
    charge(ctx, 17);
    a0 = addiu(s3, 800);
    a1 = 2;
    lw(a2, s3, 9824);
    a3 = 1;
    t0 = addiu(sp, 0x2B0);
    jal(ctx, 0x236B60u, gen::fn_sub_238A50_00238a50);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00236ba8
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00236b90
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00236bc0
    charge(ctx, 4);
    sb(v1, sp, 0x2DF);
    s1 = 0;
    for (;;) {  // while (s1 < 2)
        // 0x00236bec
        charge(ctx, 3);
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00236bd0
        charge(ctx, 7);
        v0 = sll(s1, 8);
        v0 = addu(s3, v0);
        a0 = addiu(v0, 800);
        a1 = addiu(sp, 0x2DC);
        jal(ctx, 0x236BE0u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s1 = addiu(s1, 1);
    }
    // 0x00236bf8
    charge(ctx, 4);
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x00236cc4
        charge(ctx, 3);
        lw(v0, s3, 9832);
        if (i64(v0) >= 0) {
            // 0x00236ce4
            charge(ctx, 3);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x00236d34
                charge(ctx, 3);
                v0 = 0x42200000;
                mtc1(v0, f27);
                mtc1(zero, f26);
            } else {
                // 0x00236cf0
                charge(ctx, 17);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                mul_s(f27, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f26, f0, f1);
            }
        } else {
            // 0x00236cd0
            charge(ctx, 5);
            mtc1(zero, f27);
            v0 = 0x3F800000;
            mtc1(v0, f26);
        }
    } else {
        // 0x00236c08
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00236c38
            charge(ctx, 4);
            lw(v0, s3, 9832);
            at = slti(v0, 5);
            if (at == 0) {
                // 0x00236c5c
                charge(ctx, 3);
                at = slti(v0, 11);
                if (at == 0) {
                    // 0x00236cb0
                    charge(ctx, 5);
                    mtc1(zero, f27);
                    v0 = 0x3F800000;
                    mtc1(v0, f26);
                } else {
                    // 0x00236c68
                    charge(ctx, 18);
                    v0 = addiu(v0, -5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40C00000;
                    mtc1(v0, f0);
                    div_s(f26, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f1, f0, f26);
                    v0 = 0x42200000;
                    mtc1(v0, f0);
                    mul_s(f27, f1, f0);
                }
            } else {
                // 0x00236c48
                charge(ctx, 5);
                v0 = 0x42200000;
                mtc1(v0, f27);
                mtc1(zero, f26);
            }
        } else {
            // 0x00236c14
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00236c24
                charge(ctx, 5);
                mtc1(zero, f27);
                mov_s(f26, f27);
            } else {
                // 0x00236c1c
                charge(ctx, 2);
            }
        }
    }
    // 0x00236d40
    charge(ctx, 4);
    jal(ctx, 0x236D40u, gen::fn_sub_17D800_0017d800);  // the game-mode test (The Answer)
    if (v0 == 0) {
        // 0x00236d8c
        charge(ctx, 13);
        v0 = 427;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f27);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        lw(a0, s3, 784);
        a2 = 3112;
        jal(ctx, 0x236DB8u, gen::fn_frFontLineSetPos_003b0d70);
    } else {
        // 0x00236d50
        charge(ctx, 15);
        v0 = 477;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f27);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        lw(a0, s3, 784);
        a2 = 3112;
        jal(ctx, 0x236D7Cu, gen::fn_frFontLineSetPos_003b0d70);
    }
    // 0x00236dc0
    charge(ctx, 10);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00236e00
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00236de8
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00236e18
    charge(ctx, 10);
    v1 = v1 & 0xFF;
    v0 = si(-256);
    a1 = v1 | v0;
    lw(a0, s3, 784);
    jal(ctx, 0x236E28u, gen::fn_frFontLineSetRgba_003b0e20);
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x00236efc
        charge(ctx, 5);
        mtc1(zero, f27);
        lw(v0, s3, 9832);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x00236f44
            charge(ctx, 1);
            mov_s(f26, f27);
        } else {
            // 0x00236f10
            charge(ctx, 13);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f26, f0, f1);
        }
    } else {
        // 0x00236e40
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00236e70
            charge(ctx, 4);
            lw(v0, s3, 9832);
            at = slti(v0, 2);
            if (at == 0) {
                // 0x00236e94
                charge(ctx, 3);
                at = slti(v0, 7);
                if (at == 0) {
                    // 0x00236ee8
                    charge(ctx, 5);
                    mtc1(zero, f27);
                    v0 = 0x3F800000;
                    mtc1(v0, f26);
                } else {
                    // 0x00236ea0
                    charge(ctx, 18);
                    v0 = addiu(v0, -2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40A00000;
                    mtc1(v0, f0);
                    div_s(f26, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f1, f0, f26);
                    v0 = lui(0xC220);
                    mtc1(v0, f0);
                    mul_s(f27, f1, f0);
                }
            } else {
                // 0x00236e80
                charge(ctx, 5);
                v0 = lui(0xC220);
                mtc1(v0, f27);
                mtc1(zero, f26);
            }
        } else {
            // 0x00236e4c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00236e5c
                charge(ctx, 5);
                mtc1(zero, f27);
                mov_s(f26, f27);
            } else {
                // 0x00236e54
                charge(ctx, 2);
            }
        }
    }
    // 0x00236f48
    charge(ctx, 57);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x236F50u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    s1 = v0;
    a0 = addiu(sp, 0x1B0);
    a1 = addiu(gp, -26772);  // "%d"
    lw(a2, s3, 9828);
    jal(ctx, 0x236F68u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x1B0);
    jal(ctx, 0x236F74u, gen::fn_strlen_00524388);
    v1 = sll(v0, 1);
    v1 = addu(v1, v0);
    v1 = sll(v1, 3);
    v0 = subu(v1, v0);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x40A00000;
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    lwc1(f0, s1, kSpW);
    cvt_s_w(f0, f0);
    add_s(f1, f1, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x43980000;
    mtc1(v0, f0);
    sub_s(f20, f0, f1);
    add_s(f0, f20, f27);
    swc1(f0, sp, 0x2B0);
    v0 = 0x431A0000;
    sw(v0, sp, 0x2B4);
    a0 = addiu(s3, 1312);
    a1 = 7;
    lw(a2, s3, 9828);
    a3 = 0;
    t0 = addiu(sp, 0x2B0);
    jal(ctx, 0x236FF8u, gen::fn_sub_235FF0_00235ff0);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    s1 = 0;
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f21, f0, f26);
    for (;;) {  // while (s1 < 7)
        // 0x00237094
        charge(ctx, 3);
        v0 = slti(s1, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0023702c
        charge(ctx, 6);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x0023705c
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00237044
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00237074
        charge(ctx, 8);
        sb(v1, sp, 0x2DF);
        v0 = sll(s1, 8);
        v0 = addu(s3, v0);
        a0 = addiu(v0, 1312);
        a1 = addiu(sp, 0x2DC);
        jal(ctx, 0x237088u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s1 = addiu(s1, 1);
    }
    // 0x002370a0
    charge(ctx, 55);
    a0 = addiu(sp, 0xB0);
    a1 = addiu(gp, -26772);  // "%d"
    lw(a2, s3, 9828);
    jal(ctx, 0x2370ACu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0xB0);
    jal(ctx, 0x2370B8u, gen::fn_strlen_00524388);
    v1 = sll(v0, 1);
    v1 = addu(v1, v0);
    v1 = sll(v1, 3);
    v0 = subu(v1, v0);
    mtc1(v0, f0);
    cvt_s_w(f28, f0);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x2370E4u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    add_s(f1, f20, f28);
    v1 = 0x40A00000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    add_s(f0, f27, f0);
    swc1(f0, sp, 0x2B0);
    v1 = 0x431E0000;
    sw(v1, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 3104);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x237130u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = 40;
    jal(ctx, 0x23713Cu, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 3104);
    mov_s(f12, f0);
    jal(ctx, 0x23714Cu, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f21);
    if (cond(ctx)) {
        // 0x00237194
        charge(ctx, 6);
        sub_s(f0, f21, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0023717c
        charge(ctx, 6);
        cvt_w_s(f0, f21);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002371ac
    charge(ctx, 9);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 3104);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x2371B8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x00237268
        charge(ctx, 10);
        lwc1(f0, s3, 9832);
        cvt_s_w(f1, f0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        div_s(f0, f1, f0);
        v0 = 0x3F800000;
        mtc1(v0, f27);
        sub_s(f26, f27, f0);
    } else {
        // 0x002371d0
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00237200
            charge(ctx, 5);
            v0 = 0x3F800000;
            mtc1(v0, f26);
            lw(v0, s3, 9832);
            if (i64(v0) >= 0) {
                // 0x00237220
                charge(ctx, 3);
                at = slti(v0, 2);
                if (at == 0) {
                    // 0x0023725c
                    charge(ctx, 3);
                    mov_s(f27, f26);
                } else {
                    // 0x0023722c
                    charge(ctx, 12);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40000000;
                    mtc1(v0, f0);
                    div_s(f27, f1, f0);
                }
            } else {
                // 0x00237214
                charge(ctx, 3);
                mtc1(zero, f27);
            }
        } else {
            // 0x002371dc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002371ec
                charge(ctx, 5);
                mtc1(zero, f27);
                mov_s(f26, f27);
            } else {
                // 0x002371e4
                charge(ctx, 2);
            }
        }
    }
    // 0x00237290
    charge(ctx, 40);
    a0 = s0;
    a1 = 4;
    jal(ctx, 0x237298u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    sw(zero, sp, 0x2B0);
    v1 = 0x43290000;
    sw(v1, sp, 0x2B4);
    v1 = 0x44200000;
    mtc1(v1, f0);
    mul_s(f0, f0, f27);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 3360);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x2372D4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    a0 = 40;
    jal(ctx, 0x2372E0u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 3360);
    mov_s(f12, f0);
    jal(ctx, 0x2372F0u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00237348
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00237330
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00237360
    charge(ctx, 8);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 3360);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x23736Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    s4 = 0;
    for (;;) {
        // 0x00237988
        charge(ctx, 4);
        lw(v0, s3, 7504);
        v0 = slt(s4, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00237380
        charge(ctx, 11);
        v0 = sll(s4, 3);
        v1 = addu(v0, s4);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v0 = sll(v0, 4);
        v0 = addu(s3, v0);
        s2 = addiu(v0, 3616);
        lw(v1, s3, 9836);
        v0 = 2;
        if (v1 == v0) {
            // 0x002374cc
            charge(ctx, 7);
            v0 = 0x3F800000;
            mtc1(v0, f25);
            mtc1(zero, f27);
            lw(v0, s3, 9832);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x00237518
                charge(ctx, 1);
                mov_s(f26, f27);
            } else {
                // 0x002374e8
                charge(ctx, 12);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f0, f1, f0);
                sub_s(f26, f25, f0);
            }
        } else {
            // 0x002373ac
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x002373e4
                charge(ctx, 5);
                lw(v1, s3, 9832);
                v0 = addiu(s4, 4);
                v1 = subu(v1, v0);
                if (i64(v1) > 0) {
                    // 0x0023740c
                    charge(ctx, 3);
                    at = slti(v1, 4);
                    if (at == 0) {
                        // 0x00237460
                        charge(ctx, 3);
                        mtc1(zero, f27);
                        v0 = 0x3F800000;
                        mtc1(v0, f26);
                    } else {
                        // 0x00237418
                        charge(ctx, 18);
                        v0 = addiu(v1, -1);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40400000;
                        mtc1(v0, f0);
                        div_s(f26, f1, f0);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f1, f0, f26);
                        v0 = lui(0xC220);
                        mtc1(v0, f0);
                        mul_s(f27, f1, f0);
                    }
                } else {
                    // 0x002373f8
                    charge(ctx, 5);
                    v0 = lui(0xC220);
                    mtc1(v0, f27);
                    mtc1(zero, f26);
                }
                // 0x0023746c
                charge(ctx, 2);
                if (i64(v1) >= 0) {
                    // 0x00237480
                    charge(ctx, 3);
                    at = slti(v1, 2);
                    if (at == 0) {
                        // 0x002374bc
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f25);
                    } else {
                        // 0x0023748c
                        charge(ctx, 12);
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        div_s(f25, f1, f0);
                    }
                } else {
                    // 0x00237474
                    charge(ctx, 3);
                    mtc1(zero, f25);
                }
            } else {
                // 0x002373b8
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x002373c8
                    charge(ctx, 7);
                    mtc1(zero, f27);
                    mov_s(f26, f27);
                    v0 = 0x3F800000;
                    mtc1(v0, f25);
                } else {
                    // 0x002373c0
                    charge(ctx, 2);
                }
            }
        }
        // 0x0023751c
        charge(ctx, 28);
        v0 = sll(s4, 4);
        v0 = subu(v0, s4);
        s1 = sll(v0, 1);
        v0 = 174;
        v0 = subu(v0, s1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f27, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        v0 = addiu(s1, 210);
        a2 = sll(v0, 3);
        lw(a0, s2, 12);
        jal(ctx, 0x23755Cu, gen::fn_frFontLineSetPos_003b0d70);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f21, f0, f26);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x002375a4
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0023758c
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002375bc
        charge(ctx, 98);
        v1 = v1 & 0xFF;
        v0 = si(-256);
        a1 = v1 | v0;
        lw(a0, s2, 12);
        jal(ctx, 0x2375CCu, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = s0;
        a1 = 4;
        jal(ctx, 0x2375DCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        mtc1(zero, f3);
        sw(zero, sp, 0x2B0);
        v1 = 0x41F00000;
        mtc1(v1, f2);
        mtc1(s4, f0);
        cvt_s_w(f1, f0);
        v1 = 0x43690000;
        mtc1(v1, f0);
        adda_s(f3, f0);
        madd_s(f0, f2, f1);
        swc1(f0, sp, 0x2B4);
        v1 = 0x44200000;
        mtc1(v1, f0);
        mul_s(f0, f0, f25);
        swc1(f0, sp, 0x2B8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x2BC);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0x2B0);
        jal(ctx, 0x237640u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        a0 = 40;
        jal(ctx, 0x23764Cu, gen::fn_sub_21EA00_0021ea00);
        a0 = addiu(s2, 16);
        mov_s(f12, f0);
        jal(ctx, 0x23765Cu, gen::fn_sub_21EAC0_0021eac0);
        v0 = 255;
        sb(v0, sp, 0x2DC);
        sb(v0, sp, 0x2DD);
        sb(v0, sp, 0x2DE);
        sb(v0, sp, 0x2DF);
        a0 = addiu(s2, 16);
        a1 = addiu(sp, 0x2DC);
        jal(ctx, 0x237680u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x237690u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        s5 = v0;
        v1 = 373;
        mtc1(v1, f0);
        cvt_s_w(f2, f0);
        mtc1(s1, f0);
        cvt_s_w(f1, f0);
        sub_s(f0, f2, f1);
        add_s(f0, f27, f0);
        swc1(f0, sp, 0x2B0);
        v1 = 0x435D0000;
        mtc1(v1, f0);
        add_s(f20, f0, f1);
        swc1(f20, sp, 0x2B4);
        lwc1(f0, v0, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x2B8);
        lwc1(f0, v0, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x2BC);
        a0 = addiu(s2, 272);
        a1 = addiu(sp, 0x2B0);
        jal(ctx, 0x2376F8u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        a0 = 40;
        jal(ctx, 0x237704u, gen::fn_sub_21EA00_0021ea00);
        a0 = addiu(s2, 272);
        mov_s(f12, f0);
        jal(ctx, 0x237714u, gen::fn_sub_21EAC0_0021eac0);
        v0 = 255;
        sb(v0, sp, 0x2DC);
        sb(v0, sp, 0x2DD);
        sb(v0, sp, 0x2DE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x0023775c
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00237744
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00237774
        charge(ctx, 9);
        sb(v1, sp, 0x2DF);
        a0 = addiu(s2, 272);
        a1 = addiu(sp, 0x2DC);
        jal(ctx, 0x237780u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        lw(v0, s2, 8);
        v0 = slti(v0, 10);
        if (v0 != 0) {
            // 0x002377c8
            charge(ctx, 10);
            v0 = 401;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            sub_s(f0, f1, f0);
            add_s(f0, f27, f0);
            swc1(f0, sp, 0x2B0);
        } else {
            // 0x00237798
            charge(ctx, 12);
            v0 = 393;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            sub_s(f0, f1, f0);
            add_s(f0, f27, f0);
            swc1(f0, sp, 0x2B0);
        }
        // 0x002377f0
        charge(ctx, 11);
        swc1(f20, sp, 0x2B4);
        a0 = addiu(s2, 528);
        a1 = 2;
        lw(a2, s2, 8);
        a3 = 1;
        t0 = addiu(sp, 0x2B0);
        jal(ctx, 0x237808u, gen::fn_sub_235FF0_00235ff0);
        s1 = 0;
        for (;;) {  // while (s1 < 2)
            // 0x00237838
            charge(ctx, 3);
            v0 = slti(s1, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0023781c
            charge(ctx, 7);
            v0 = sll(s1, 8);
            v0 = addu(s2, v0);
            a0 = addiu(v0, 528);
            a1 = addiu(sp, 0x2DC);
            jal(ctx, 0x23782Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
            s1 = addiu(s1, 1);
        }
        // 0x00237844
        charge(ctx, 4);
        lw(v1, s2, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x00237880
            charge(ctx, 5);
            a0 = s6;
            a1 = 11;
            jal(ctx, 0x237888u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
            s5 = v0;
        } else {
            // 0x00237854
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00237864
                charge(ctx, 7);
                a0 = s6;
                a1 = 10;
                jal(ctx, 0x23786Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
                s5 = v0;
            } else {
                // 0x0023785c
                charge(ctx, 2);
            }
        }
        // 0x00237894
        charge(ctx, 43);
        v0 = sll(s4, 4);
        v0 = subu(v0, s4);
        v1 = sll(v0, 1);
        v0 = 0x430E0000;
        mtc1(v0, f2);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        sub_s(f0, f2, f1);
        add_s(f0, f27, f0);
        swc1(f0, sp, 0x2B0);
        v0 = 0x434D0000;
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x2B4);
        lwc1(f0, s5, kSpW);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x2B8);
        lwc1(f0, s5, kSpH);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x2BC);
        a0 = addiu(s2, 1040);
        a1 = addiu(sp, 0x2B0);
        jal(ctx, 0x2378F4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        a0 = 40;
        jal(ctx, 0x237900u, gen::fn_sub_21EA00_0021ea00);
        a0 = addiu(s2, 1040);
        mov_s(f12, f0);
        jal(ctx, 0x237910u, gen::fn_sub_21EAC0_0021eac0);
        v0 = 255;
        sb(v0, sp, 0x2DC);
        sb(v0, sp, 0x2DD);
        sb(v0, sp, 0x2DE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x00237958
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00237940
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00237970
        charge(ctx, 6);
        sb(v1, sp, 0x2DF);
        a0 = addiu(s2, 1040);
        a1 = addiu(sp, 0x2DC);
        jal(ctx, 0x23797Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
        s4 = addiu(s4, 1);
    }
    // 0x00237998
    charge(ctx, 8);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x2379A0u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    lw(a0, s3, 9836);
    v1 = 2;
    if (a0 == v1) {
        // 0x00237a90
        charge(ctx, 4);
        lw(v1, s3, 9832);
        at = slti(v1, 3);
        if (at == 0) {
            // 0x00237b0c
            charge(ctx, 5);
            v1 = 0x42F20000;
            sw(v1, sp, 0x2B0);
            v1 = 0x42B00000;
            sw(v1, sp, 0x2B4);
            mtc1(zero, f26);
        } else {
            // 0x00237aa0
            charge(ctx, 27);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x40400000;
            mtc1(v1, f0);
            div_s(f2, f1, f0);
            v1 = 0x42C80000;
            mtc1(v1, f0);
            mul_s(f1, f2, f0);
            v1 = 0x41A80000;
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x2B0);
            v1 = lui(0xC140);
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x2B4);
            v1 = 0x3F800000;
            mtc1(v1, f0);
            sub_s(f26, f0, f2);
        }
    } else {
        // 0x002379b8
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x002379e8
            charge(ctx, 6);
            v1 = 0x3F800000;
            mtc1(v1, f26);
            lw(v1, s3, 9832);
            at = slti(v1, 5);
            if (at == 0) {
                // 0x00237a78
                charge(ctx, 6);
                v1 = 0x41A80000;
                sw(v1, sp, 0x2B0);
                v1 = lui(0xC140);
                sw(v1, sp, 0x2B4);
            } else {
                // 0x00237a00
                charge(ctx, 30);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f5, f1, f0);
                lwc1(f0, v0, kSpH);
                cvt_s_w(f0, f0);
                v1 = lui(0xC140);
                mtc1(v1, f4);
                add_s(f1, f4, f0);
                v1 = 0x41A80000;
                mtc1(v1, f0);
                add_s(f3, f0, f1);
                sub_s(f2, f4, f1);
                sub_s(f0, f0, f3);
                mtc1(zero, f1);
                adda_s(f1, f3);
                madd_s(f0, f5, f0);
                swc1(f0, sp, 0x2B0);
                sub_s(f0, f4, f2);
                adda_s(f1, f2);
                madd_s(f0, f5, f0);
                swc1(f0, sp, 0x2B4);
            }
        } else {
            // 0x002379c4
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x002379d4
                charge(ctx, 5);
                mtc1(zero, f26);
                sw(zero, sp, 0x2B0);
                sw(zero, sp, 0x2B4);
            } else {
                // 0x002379cc
                charge(ctx, 2);
            }
        }
    }
    // 0x00237b20
    charge(ctx, 24);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 7520);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x237B40u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x00237b98
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00237b80
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00237bb0
    charge(ctx, 13);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 7520);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x237BBCu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s0;
    a1 = 7;
    jal(ctx, 0x237BCCu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    lw(a0, s3, 9836);
    v1 = 2;
    if (a0 == v1) {
        // 0x00237cb0
        charge(ctx, 4);
        lw(v0, s3, 9832);
        at = slti(v0, 3);
        if (at == 0) {
            // 0x00237d08
            charge(ctx, 5);
            v0 = 0x42C80000;
            mtc1(v0, f23);
            mov_s(f22, f23);
            mtc1(zero, f26);
        } else {
            // 0x00237cc0
            charge(ctx, 18);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x42C80000;
            mtc1(v0, f0);
            mul_s(f23, f0, f1);
            mov_s(f22, f23);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f26, f0, f1);
        }
    } else {
        // 0x00237be4
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x00237c18
            charge(ctx, 12);
            lwc1(f0, v0, kSpH);
            cvt_s_w(f1, f0);
            v0 = 0x43820000;
            mtc1(v0, f0);
            add_s(f2, f0, f1);
            v0 = 0x3F800000;
            mtc1(v0, f26);
            lw(v0, s3, 9832);
            at = slti(v0, 3);
            if (at == 0) {
                // 0x00237c58
                charge(ctx, 3);
                at = slti(v0, 6);
                if (at == 0) {
                    // 0x00237c9c
                    charge(ctx, 5);
                    mtc1(zero, f23);
                    mov_s(f22, f23);
                } else {
                    // 0x00237c64
                    charge(ctx, 14);
                    v0 = addiu(v0, -3);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40400000;
                    mtc1(v0, f0);
                    div_s(f0, f1, f0);
                    sub_s(f1, f26, f0);
                    mul_s(f23, f1, f2);
                    neg_s(f0, f2);
                    mul_s(f22, f1, f0);
                }
            } else {
                // 0x00237c48
                charge(ctx, 4);
                mov_s(f23, f2);
                neg_s(f22, f2);
            }
        } else {
            // 0x00237bf0
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00237c00
                charge(ctx, 6);
                mtc1(zero, f26);
                mov_s(f23, f26);
                mov_s(f22, f26);
            } else {
                // 0x00237bf8
                charge(ctx, 2);
            }
        }
    }
    // 0x00237d1c
    charge(ctx, 4);
    lw(v0, s3, 0);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x00237d6c
        charge(ctx, 14);
        a0 = s0;
        a1 = 8;
        jal(ctx, 0x237D74u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x431E0000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0x2B0);
        v1 = 0x42300000;
        mtc1(v1, f0);
        add_s(f0, f0, f22);
        swc1(f0, sp, 0x2B4);
    } else {
        // 0x00237d2c
        charge(ctx, 16);
        a0 = s0;
        a1 = 10;
        jal(ctx, 0x237D34u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
        v1 = 0x430D0000;
        mtc1(v1, f0);
        add_s(f0, f0, f23);
        swc1(f0, sp, 0x2B0);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        add_s(f0, f0, f22);
        swc1(f0, sp, 0x2B4);
    }
    // 0x00237da4
    charge(ctx, 24);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 8032);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x237DC4u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f20, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00237e1c
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00237e04
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00237e34
    charge(ctx, 39);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 8032);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x237E40u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s0;
    a1 = 9;
    jal(ctx, 0x237E50u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x43040000;
    mtc1(v1, f0);
    add_s(f0, f0, f23);
    swc1(f0, sp, 0x2B0);
    v1 = 0x43080000;
    mtc1(v1, f0);
    add_s(f0, f0, f22);
    swc1(f0, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 7776);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x237EA0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00237ee8
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00237ed0
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00237f00
    charge(ctx, 39);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 7776);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x237F0Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s0;
    a1 = 7;
    jal(ctx, 0x237F1Cu, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x42080000;
    mtc1(v1, f0);
    add_s(f0, f0, f23);
    swc1(f0, sp, 0x2B0);
    v1 = 0x43340000;
    mtc1(v1, f0);
    add_s(f0, f0, f22);
    swc1(f0, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 8544);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x237F6Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00237fb4
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00237f9c
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00237fcc
    charge(ctx, 39);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 8544);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x237FD8u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    a0 = s0;
    a1 = 9;
    jal(ctx, 0x237FE8u, gen::fn_sub_21CCA0_0021cca0);  // (set, i) -> page record i (44 bytes)
    v1 = 0x41000000;
    mtc1(v1, f0);
    add_s(f0, f0, f23);
    swc1(f0, sp, 0x2B0);
    v1 = 0x43820000;
    mtc1(v1, f0);
    add_s(f0, f0, f22);
    swc1(f0, sp, 0x2B4);
    lwc1(f0, v0, kSpW);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2B8);
    lwc1(f0, v0, kSpH);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2BC);
    a0 = addiu(s3, 8288);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x238038u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
    v0 = 255;
    sb(v0, sp, 0x2DC);
    sb(v0, sp, 0x2DD);
    sb(v0, sp, 0x2DE);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00238080
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00238068
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00238098
    charge(ctx, 9);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 8288);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x2380A4u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x00238250
        charge(ctx, 4);
        lw(v0, s3, 9832);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x00238328
            charge(ctx, 35);
            v0 = 0x44880000;
            mtc1(v0, f0);
            div_s(f0, f0, f24);
            div_s(f4, f0, f24);
            v0 = 0x43A00000;
            mtc1(v0, f0);
            add_s(f3, f0, f4);
            swc1(f3, sp, 0x2C0);
            v0 = 0x44200000;
            mtc1(v0, f0);
            div_s(f0, f0, f24);
            neg_s(f0, f0);
            div_s(f0, f0, f24);
            add_s(f2, f4, f0);
            swc1(f2, sp, 0x2C4);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            div_s(f0, f0, f24);
            neg_s(f0, f0);
            div_s(f0, f0, f24);
            add_s(f1, f4, f0);
            swc1(f1, sp, 0x2C8);
            v0 = 0x43600000;
            mtc1(v0, f0);
            add_s(f0, f0, f4);
            swc1(f0, sp, 0x2CC);
            swc1(f1, sp, 0x2B0);
            swc1(f0, sp, 0x2B4);
            swc1(f3, sp, 0x2B8);
            swc1(f2, sp, 0x2BC);
        } else {
            // 0x00238260
            charge(ctx, 50);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f7, f1, f0);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f8, f0);
            v0 = 0x44580000;
            mtc1(v0, f6);
            sw(v0, sp, 0x2C0);
            v0 = 0x43600000;
            mtc1(v0, f5);
            sw(v0, sp, 0x2C4);
            v0 = 0x43A00000;
            mtc1(v0, f4);
            sw(v0, sp, 0x2C8);
            v0 = 0x44400000;
            mtc1(v0, f3);
            sw(v0, sp, 0x2CC);
            lwc1(f2, gp, -32000);  // 0x7CAFF0 = 172.5f
            v0 = 0x43AF0000;
            mtc1(v0, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f0, f2, f8);
            div_s(f1, f0, f8);
            v0 = 0x44080000;
            mtc1(v0, f0);
            sub_s(f1, f0, f1);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f0, f7);
            mul_s(f1, f0, f1);
            sub_s(f0, f4, f1);
            swc1(f0, sp, 0x2B0);
            sub_s(f0, f3, f1);
            swc1(f0, sp, 0x2B4);
            sub_s(f0, f6, f1);
            swc1(f0, sp, 0x2B8);
            sub_s(f0, f5, f1);
            swc1(f0, sp, 0x2BC);
        }
    } else {
        // 0x002380bc
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00238100
            charge(ctx, 4);
            lw(v1, s3, 9832);
            at = slti(v1, 8);
            if (at == 0) {
                // 0x002381c8
                charge(ctx, 34);
                v0 = 0x43A00000;
                mtc1(v0, f5);
                sw(v0, sp, 0x2B0);
                v0 = 0x44200000;
                mtc1(v0, f0);
                div_s(f0, f0, f24);
                neg_s(f0, f0);
                div_s(f4, f0, f24);
                swc1(f4, sp, 0x2B4);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                div_s(f0, f0, f24);
                neg_s(f0, f0);
                div_s(f3, f0, f24);
                swc1(f3, sp, 0x2B8);
                v0 = 0x43600000;
                mtc1(v0, f2);
                sw(v0, sp, 0x2BC);
                v0 = 0x44880000;
                mtc1(v0, f0);
                div_s(f1, f0, f24);
                add_s(f0, f3, f1);
                swc1(f0, sp, 0x2C0);
                add_s(f0, f2, f1);
                swc1(f0, sp, 0x2C4);
                add_s(f0, f5, f1);
                swc1(f0, sp, 0x2C8);
                add_s(f0, f4, f1);
                swc1(f0, sp, 0x2CC);
            } else {
                // 0x00238110
                charge(ctx, 46);
                v0 = 0x40000000;
                mtc1(v0, f0);
                sqrt_s(f6, f0);
                v0 = 0x43A00000;
                mtc1(v0, f5);
                sw(v0, sp, 0x2B0);
                v0 = 0x44200000;
                mtc1(v0, f0);
                div_s(f0, f0, f6);
                neg_s(f0, f0);
                div_s(f4, f0, f6);
                swc1(f4, sp, 0x2B4);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                div_s(f0, f0, f6);
                neg_s(f0, f0);
                div_s(f3, f0, f6);
                swc1(f3, sp, 0x2B8);
                v0 = 0x43600000;
                mtc1(v0, f2);
                sw(v0, sp, 0x2BC);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41000000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x44880000;
                mtc1(v0, f0);
                mul_s(f0, f0, f1);
                div_s(f1, f0, f6);
                add_s(f0, f3, f1);
                swc1(f0, sp, 0x2C0);
                add_s(f0, f2, f1);
                swc1(f0, sp, 0x2C4);
                add_s(f0, f5, f1);
                swc1(f0, sp, 0x2C8);
                add_s(f0, f4, f1);
                swc1(f0, sp, 0x2CC);
            }
        } else {
            // 0x002380c8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002380d8
                charge(ctx, 10);
                sw(zero, sp, 0x2B0);
                sw(zero, sp, 0x2B4);
                sw(zero, sp, 0x2B8);
                sw(zero, sp, 0x2BC);
                sw(zero, sp, 0x2C0);
                sw(zero, sp, 0x2C4);
                sw(zero, sp, 0x2C8);
                sw(zero, sp, 0x2CC);
            } else {
                // 0x002380d0
                charge(ctx, 2);
            }
        }
    }
    // 0x002383b4
    charge(ctx, 27);
    a0 = addiu(s3, 8800);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x2383BCu, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
    a0 = 50;
    jal(ctx, 0x2383C8u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 8800);
    mov_s(f12, f0);
    jal(ctx, 0x2383D8u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 14;
    sb(v0, sp, 0x2DC);
    v0 = 139;
    sb(v0, sp, 0x2DD);
    v0 = 236;
    sb(v0, sp, 0x2DE);
    v0 = 255;
    sb(v0, sp, 0x2DF);
    a0 = addiu(s3, 8800);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x238408u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x0023850c
        charge(ctx, 9);
        v0 = 0x40000000;
        mtc1(v0, f0);
        sqrt_s(f0, f0);
        lw(v0, s3, 9832);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x00238640
            charge(ctx, 9);
            mtc1(zero, f26);
            sw(zero, sp, 0x2B0);
            sw(zero, sp, 0x2B4);
            sw(zero, sp, 0x2B8);
            sw(zero, sp, 0x2BC);
            sw(zero, sp, 0x2C0);
            sw(zero, sp, 0x2C4);
            sw(zero, sp, 0x2C8);
            sw(zero, sp, 0x2CC);
        } else {
            // 0x00238530
            charge(ctx, 68);
            mtc1(v0, f1);
            cvt_s_w(f2, f1);
            v0 = 0x41200000;
            mtc1(v0, f1);
            div_s(f3, f2, f1);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            sub_s(f26, f1, f3);
            v0 = 0x43AF0000;
            mtc1(v0, f1);
            div_s(f2, f1, f0);
            lwc1(f1, gp, -32000);  // 0x7CAFF0 = 172.5f
            sub_s(f1, f2, f1);
            div_s(f2, f1, f0);
            v0 = 0x44080000;
            mtc1(v0, f1);
            sub_s(f1, f1, f2);
            mul_s(f7, f3, f1);
            v0 = 0x42200000;
            mtc1(v0, f6);
            div_s(f2, f6, f0);
            v0 = 0x43A00000;
            mtc1(v0, f1);
            sub_s(f1, f1, f2);
            add_s(f5, f1, f7);
            swc1(f5, sp, 0x2B0);
            v0 = lui(0xC3A0);
            mtc1(v0, f1);
            sub_s(f1, f1, f2);
            add_s(f4, f1, f7);
            swc1(f4, sp, 0x2B4);
            v0 = lui(0xC360);
            mtc1(v0, f1);
            sub_s(f1, f1, f2);
            add_s(f3, f1, f7);
            swc1(f3, sp, 0x2B8);
            v0 = 0x43600000;
            mtc1(v0, f1);
            sub_s(f1, f1, f2);
            add_s(f2, f1, f7);
            swc1(f2, sp, 0x2BC);
            v0 = 283;
            mtc1(v0, f1);
            cvt_s_w(f1, f1);
            div_s(f1, f1, f0);
            add_s(f1, f6, f1);
            div_s(f1, f1, f0);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x2C0);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x2C4);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x2C8);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x2CC);
        }
    } else {
        // 0x00238420
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00238464
            charge(ctx, 42);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f5);
            sw(v0, sp, 0x2B0);
            v0 = 0x44200000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            neg_s(f0, f0);
            div_s(f4, f0, f1);
            swc1(f4, sp, 0x2B4);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            neg_s(f0, f0);
            div_s(f3, f0, f1);
            swc1(f3, sp, 0x2B8);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, sp, 0x2BC);
            v0 = 283;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f0, f1);
            div_s(f1, f0, f1);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x2C0);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x2C4);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x2C8);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x2CC);
            v0 = 0x3F800000;
            mtc1(v0, f26);
        } else {
            // 0x0023842c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0023843c
                charge(ctx, 10);
                sw(zero, sp, 0x2B0);
                sw(zero, sp, 0x2B4);
                sw(zero, sp, 0x2B8);
                sw(zero, sp, 0x2BC);
                sw(zero, sp, 0x2C0);
                sw(zero, sp, 0x2C4);
                sw(zero, sp, 0x2C8);
                sw(zero, sp, 0x2CC);
            } else {
                // 0x00238434
                charge(ctx, 2);
            }
        }
    }
    // 0x00238664
    charge(ctx, 27);
    a0 = addiu(s3, 9056);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x23866Cu, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
    a0 = 35;
    jal(ctx, 0x238678u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 9056);
    mov_s(f12, f0);
    jal(ctx, 0x238688u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 4;
    sb(v0, sp, 0x2DC);
    v0 = 41;
    sb(v0, sp, 0x2DD);
    v0 = 70;
    sb(v0, sp, 0x2DE);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f26);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x002386e8
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002386d0
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00238700
    charge(ctx, 9);
    sb(v1, sp, 0x2DF);
    a0 = addiu(s3, 9056);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x23870Cu, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    lw(v1, s3, 9836);
    v0 = 2;
    if (v1 == v0) {
        // 0x002387e4
        charge(ctx, 59);
        lwc1(f0, s3, 9832);
        cvt_s_w(f1, f0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        div_s(f2, f1, f0);
        v0 = 0x40000000;
        mtc1(v0, f0);
        sqrt_s(f8, f0);
        v0 = 0x43AF0000;
        mtc1(v0, f0);
        div_s(f7, f0, f8);
        lwc1(f0, gp, -32000);  // 0x7CAFF0 = 172.5f
        sub_s(f0, f7, f0);
        div_s(f1, f0, f8);
        v0 = 0x44080000;
        mtc1(v0, f0);
        sub_s(f0, f0, f1);
        mul_s(f6, f2, f0);
        v0 = 0x43A00000;
        mtc1(v0, f5);
        add_s(f0, f5, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2B0);
        v0 = lui(0xC3A0);
        mtc1(v0, f4);
        add_s(f0, f4, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2B4);
        v0 = lui(0xC360);
        mtc1(v0, f3);
        add_s(f0, f3, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2B8);
        v0 = 0x43600000;
        mtc1(v0, f2);
        add_s(f0, f2, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2BC);
        div_s(f1, f7, f8);
        add_s(f0, f3, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2C0);
        add_s(f0, f2, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2C4);
        add_s(f0, f5, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2C8);
        add_s(f0, f4, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x2CC);
    } else {
        // 0x00238724
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00238768
            charge(ctx, 31);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f5);
            sw(v0, sp, 0x2B0);
            v0 = lui(0xC3A0);
            mtc1(v0, f4);
            sw(v0, sp, 0x2B4);
            v0 = lui(0xC360);
            mtc1(v0, f3);
            sw(v0, sp, 0x2B8);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, sp, 0x2BC);
            v0 = 0x43AF0000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            div_s(f1, f0, f1);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x2C0);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x2C4);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x2C8);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x2CC);
        } else {
            // 0x00238730
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00238740
                charge(ctx, 10);
                sw(zero, sp, 0x2B0);
                sw(zero, sp, 0x2B4);
                sw(zero, sp, 0x2B8);
                sw(zero, sp, 0x2BC);
                sw(zero, sp, 0x2C0);
                sw(zero, sp, 0x2C4);
                sw(zero, sp, 0x2C8);
                sw(zero, sp, 0x2CC);
            } else {
                // 0x00238738
                charge(ctx, 2);
            }
        }
    }
    // 0x002388d0
    charge(ctx, 42);
    a0 = addiu(s3, 9312);
    a1 = addiu(sp, 0x2B0);
    jal(ctx, 0x2388D8u, gen::fn_sub_21D890_0021d890);  // (quad, xy[4]*): the four corners
    a0 = 35;
    jal(ctx, 0x2388E4u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s3, 9312);
    mov_s(f12, f0);
    jal(ctx, 0x2388F4u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 79;
    sb(v0, sp, 0x2DC);
    v0 = 164;
    sb(v0, sp, 0x2DD);
    v0 = 255;
    sb(v0, sp, 0x2DE);
    sb(v0, sp, 0x2DF);
    a0 = addiu(s3, 9312);
    a1 = addiu(sp, 0x2DC);
    jal(ctx, 0x238920u, gen::fn_sub_21D950_0021d950);  // (quad, rgba*): the colour
    ld(ra, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
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
    sp = addiu(sp, 0x2E0);
}

// 0x00238A50 sub_238A50 -- 416 bytes; frame 0x180: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpIfont_PlaceLeft](quads, n, value, font, xy*) bp_ifont.c: the digits of `value` (format
// 0x7CC460) from the sprite font `font` (sprFontGetFile; glyph = font +388 + 128 (c - 37)), right to left from x, 15 px
// apart; unused quads get a zero-size rectangle; K_Assert 56.
void sub_238A50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00238a50
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s4 = a2;
    s0 = t0;
    a0 = a3;
    jal(ctx, 0x238A84u, gen::fn_sprFontGetFile_001120a0);
    s3 = v0;
    a0 = addiu(sp, 0x70);
    a1 = addiu(gp, -26768);  // "%d"
    a2 = s4;
    jal(ctx, 0x238A9Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x70);
    jal(ctx, 0x238AA8u, gen::fn_strlen_00524388);
    s4 = v0;
    at = slt(s1, s4);
    if (at != 0) {
        // 0x00238ac0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6240);  // "bp_ifont.c"
        a1 = 56;
        jal(ctx, 0x238ACCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_ifont.c", 56): `jr $ra` in retail, execution goes on
    }
    // 0x00238ad4
    charge(ctx, 3);
    s5 = 0;
    for (;;) {  // while (s5 < s4)
        // 0x00238b78
        charge(ctx, 3);
        v1 = slt(s5, s4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00238ae0
        charge(ctx, 38);
        v0 = addiu(s4, -1);
        a1 = subu(v0, s5);
        v0 = addu(a1, sp);
        lb(v0, v0, 112);
        v0 = addiu(v0, -37);
        v1 = sll(v0, 7);
        lw(v0, s3, 388);
        a0 = addu(v0, v1);
        lwc1(f1, s0, 0);
        v0 = sll(a1, 4);
        v0 = subu(v0, a1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x170);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x174);
        lw(v1, a0, 92);
        lw(v0, a0, 84);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x178);
        lw(v1, a0, 96);
        lw(v0, a0, 88);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x17C);
        v0 = sll(s5, 8);
        a0 = addu(s2, v0);
        a1 = addiu(sp, 0x170);
        jal(ctx, 0x238B6Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s5 = addiu(s5, 1);
    }
    // 0x00238b84
    charge(ctx, 2);
    for (;;) {  // while (s4 < s1)
        // 0x00238bbc
        charge(ctx, 3);
        v1 = slt(s4, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00238b8c
        charge(ctx, 12);
        lwc1(f0, s0, 0);
        swc1(f0, sp, 0x170);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x174);
        sw(zero, sp, 0x178);
        sw(zero, sp, 0x17C);
        v0 = sll(s4, 8);
        a0 = addu(s2, v0);
        a1 = addiu(sp, 0x170);
        jal(ctx, 0x238BB0u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s4 = addiu(s4, 1);
    }
    // 0x00238bc8
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x00238BF0 sub_238BF0 -- 452 bytes; frame 0x190: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpIfont_PlaceRight](quads, n, value, font, xy*) the same, right-aligned in an n-digit field (shifted
// by 15 (n - digits)); K_Assert 89.
void sub_238BF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00238bf0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s3 = a2;
    s0 = t0;
    a0 = a3;
    jal(ctx, 0x238C28u, gen::fn_sprFontGetFile_001120a0);
    s6 = v0;
    a0 = addiu(sp, 0x80);
    a1 = addiu(gp, -26768);  // "%d"
    a2 = s3;
    jal(ctx, 0x238C40u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x80);
    jal(ctx, 0x238C4Cu, gen::fn_strlen_00524388);
    s4 = v0;
    at = slt(s1, s4);
    if (at != 0) {
        // 0x00238c64
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6240);  // "bp_ifont.c"
        a1 = 89;
        jal(ctx, 0x238C70u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_ifont.c", 89): `jr $ra` in retail, execution goes on
    }
    // 0x00238c78
    charge(ctx, 6);
    s5 = 0;
    a0 = subu(s1, s4);
    v1 = sll(a0, 4);
    s3 = subu(v1, a0);
    for (;;) {  // while (s5 < s4)
        // 0x00238d38
        charge(ctx, 3);
        v1 = slt(s5, s4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00238c90
        charge(ctx, 42);
        v0 = addiu(s4, -1);
        a1 = subu(v0, s5);
        v0 = addu(a1, sp);
        lb(v0, v0, 128);
        v0 = addiu(v0, -37);
        v1 = sll(v0, 7);
        lw(v0, s6, 388);
        a0 = addu(v0, v1);
        lwc1(f1, s0, 0);
        v0 = sll(a1, 4);
        v0 = subu(v0, a1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x180);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x184);
        lw(v1, a0, 92);
        lw(v0, a0, 84);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x188);
        lw(v1, a0, 96);
        lw(v0, a0, 88);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x18C);
        v0 = sll(s5, 8);
        a0 = addu(s2, v0);
        a1 = addiu(sp, 0x180);
        jal(ctx, 0x238D2Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s5 = addiu(s5, 1);
    }
    // 0x00238d44
    charge(ctx, 2);
    for (;;) {  // while (s4 < s1)
        // 0x00238d7c
        charge(ctx, 3);
        v1 = slt(s4, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00238d4c
        charge(ctx, 12);
        lwc1(f0, s0, 0);
        swc1(f0, sp, 0x180);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x184);
        sw(zero, sp, 0x188);
        sw(zero, sp, 0x18C);
        v0 = sll(s4, 8);
        a0 = addu(s2, v0);
        a1 = addiu(sp, 0x180);
        jal(ctx, 0x238D70u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s4 = addiu(s4, 1);
    }
    // 0x00238d88
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x00238DC0 sub_238DC0 -- 520 bytes; frame 0x1A0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpIfont_PlaceCentred](quads, n, value, font, xy*) the same, centred in the n-digit field
// (+ 15 n / 2 - 15 digits / 2, both halves rounded towards zero); K_Assert 122.
void sub_238DC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00238dc0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s6 = a0;
    s1 = a1;
    s2 = a2;
    s0 = t0;
    a0 = a3;
    jal(ctx, 0x238DFCu, gen::fn_sprFontGetFile_001120a0);
    s7 = v0;
    a0 = addiu(sp, 0x90);
    a1 = addiu(gp, -26768);  // "%d"
    a2 = s2;
    jal(ctx, 0x238E14u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x90);
    jal(ctx, 0x238E20u, gen::fn_strlen_00524388);
    s4 = v0;
    at = slt(s1, s4);
    if (at != 0) {
        // 0x00238e38
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6240);  // "bp_ifont.c"
        a1 = 122;
        jal(ctx, 0x238E44u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert("bp_ifont.c", 122): `jr $ra` in retail, execution goes on
    }
    // 0x00238e4c
    charge(ctx, 6);
    s5 = 0;
    v1 = sll(s1, 4);
    v1 = subu(v1, s1);
    s3 = sra(v1, 1);
    if (i64(v1) < 0) {
        // 0x00238e64
        charge(ctx, 2);
        v1 = addiu(v1, 1);
        s3 = sra(v1, 1);
    }
    // 0x00238e6c
    charge(ctx, 5);
    v1 = sll(s4, 4);
    v1 = subu(v1, s4);
    s2 = sra(v1, 1);
    if (i64(v1) < 0) {
        // 0x00238e80
        charge(ctx, 2);
        v1 = addiu(v1, 1);
        s2 = sra(v1, 1);
    }
    // 0x00238e88
    charge(ctx, 2);
    for (;;) {  // while (s5 < s4)
        // 0x00238f48
        charge(ctx, 3);
        v1 = slt(s5, s4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00238e90
        charge(ctx, 46);
        v0 = addiu(s4, -1);
        a1 = subu(v0, s5);
        v0 = addu(a1, sp);
        lb(v0, v0, 144);
        v0 = addiu(v0, -37);
        v1 = sll(v0, 7);
        lw(v0, s7, 388);
        a0 = addu(v0, v1);
        lwc1(f1, s0, 0);
        v0 = sll(a1, 4);
        v0 = subu(v0, a1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x190);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x194);
        lw(v1, a0, 92);
        lw(v0, a0, 84);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x198);
        lw(v1, a0, 96);
        lw(v0, a0, 88);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x19C);
        v0 = sll(s5, 8);
        a0 = addu(s6, v0);
        a1 = addiu(sp, 0x190);
        jal(ctx, 0x238F3Cu, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s5 = addiu(s5, 1);
    }
    // 0x00238f54
    charge(ctx, 2);
    for (;;) {  // while (s4 < s1)
        // 0x00238f8c
        charge(ctx, 3);
        v1 = slt(s4, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00238f5c
        charge(ctx, 12);
        lwc1(f0, s0, 0);
        swc1(f0, sp, 0x190);
        lwc1(f0, s0, 4);
        swc1(f0, sp, 0x194);
        sw(zero, sp, 0x198);
        sw(zero, sp, 0x19C);
        v0 = sll(s4, 8);
        a0 = addu(s6, v0);
        a1 = addiu(sp, 0x190);
        jal(ctx, 0x238F80u, gen::fn_sub_21D8E0_0021d8e0);  // (quad, rect*): x / y / w / h
        s4 = addiu(s4, 1);
    }
    // 0x00238f98
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

}  // namespace p3fes::game
