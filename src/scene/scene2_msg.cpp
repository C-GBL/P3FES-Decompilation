// Slice scene2 (game/include/p3fes/game/scene2.h has the records): nmlist.c's sort, the message-window slot helpers and
// fclMisc.c's "MsgAssist" task.
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; a script checks the bodies stay
// token-identical to the generator's output).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"
#include "p3fes/game/scene2.h"

namespace p3fes::recomp_gen {
void fn_fclMisc_UpdateMsgAssistTask_003c89a0(p3fes::EEContext&);
void fn_itfMesMngDestroyHandle_003a3060(p3fes::EEContext&);
void fn_itfMesMngGetBusy_003a2580(p3fes::EEContext&);
void fn_itfMesMngGetSelectWord84_003a2750(p3fes::EEContext&);
void fn_itfMesMngGetSelection_003a2830(p3fes::EEContext&);
void fn_itfMesMngGetState_003a3da0(p3fes::EEContext&);
void fn_itfMesMngInitialize_003a2d80(p3fes::EEContext&);
void fn_itfMesMngRequestMessage_003a30c0(p3fes::EEContext&);
void fn_itfMesMngSetBusy_003a25f0(p3fes::EEContext&);
void fn_itfMesMngSetSelection_003a3c10(p3fes::EEContext&);
void fn_itfMesMngSetStateFlags_003a3e10(p3fes::EEContext&);
void fn_nmListRebuild_003c50b0(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3A2A30_003a2a30(p3fes::EEContext&);
void fn_sub_3A3420_003a3420(p3fes::EEContext&);
void fn_sub_3A37C0_003a37c0(p3fes::EEContext&);
void fn_sub_3A4360_003a4360(p3fes::EEContext&);
void fn_sub_3A5210_003a5210(p3fes::EEContext&);
void fn_sub_3A8600_003a8600(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C4A90_003c4a90(p3fes::EEContext&);
void fn_sub_3C4FC0_003c4fc0(p3fes::EEContext&);
void fn_sub_3C7990_003c7990(p3fes::EEContext&);
void fn_sub_3C7C90_003c7c90(p3fes::EEContext&);
void fn_sub_3C7D50_003c7d50(p3fes::EEContext&);
void fn_sub_3C7DD0_003c7dd0(p3fes::EEContext&);
void fn_sub_3C8400_003c8400(p3fes::EEContext&);
void fn_sub_3C8550_003c8550(p3fes::EEContext&);
void fn_sub_3C8770_003c8770(p3fes::EEContext&);
void fn_sub_3C8810_003c8810(p3fes::EEContext&);
void fn_sub_3C8B50_003c8b50(p3fes::EEContext&);
void fn_sub_3C8D80_003c8d80(p3fes::EEContext&);
void fn_sub_3C8DC0_003c8dc0(p3fes::EEContext&);
void fn_sub_3C8FA0_003c8fa0(p3fes::EEContext&);
void fn_sub_3C9000_003c9000(p3fes::EEContext&);
void fn_sub_3C91B0_003c91b0(p3fes::EEContext&);
void fn_sub_3C9240_003c9240(p3fes::EEContext&);
void fn_sub_3C9290_003c9290(p3fes::EEContext&);
void fn_sub_3C9340_003c9340(p3fes::EEContext&);
void fn_sub_3C9390_003c9390(p3fes::EEContext&);
void fn_sub_3C9460_003c9460(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scene2;

// 0x003C4FC0 sub_3C4FC0 -- 228 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [nmListSort] (list, compare) Sorts an nmList: its nodes (+4 first, +16 next; +16 u16 count) into an RwMalloc'd array,
// qsort with `compare`, relinked in that order (nmListRebuild), the cursor +12 reset to the first; nothing for an
// empty list.
void sub_3C4FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4fc0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = 0;
    lw(s2, a0, nml::kFirst);
    if (s2 != 0) {
        // 0x003c4ff4
        charge(ctx, 10);
        lhu(v0, s4, nml::kCount);
        a0 = sll(v0, 2);
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, g::kLoRwMalloc);  // 0x960178
        jalr(ctx, 0x3C5008u, v0.u());
        s1 = v0;
        for (;;) {
            // 0x003c5030
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c501c
            charge(ctx, 5);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            sw(s2, v0, 0);
            s0 = addiu(s0, 1);
            lw(s2, s2, nmnode::kNext);
        }
        // 0x003c5038
        charge(ctx, 18);
        a0 = s1;
        a1 = s0;
        a2 = 4;
        a3 = s3;
        jal(ctx, 0x3C5048u, gen::fn_qsort_005225f8);
        a0 = s4;
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x3C505Cu, gen::fn_nmListRebuild_003c50b0);
        lw(v0, s4, nml::kFirst);
        sw(v0, s4, nml::kCursor);
        a0 = s1;
        v0 = 0x960000;
        lw(v0, v0, g::kLoRwFree);  // 0x96017C
        jalr(ctx, 0x3C5078u, v0.u());
    }
    // 0x003c5080 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003C7990 sub_3C7990 -- 508 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MsgWinStep] (clear) One step of the current message-window slot (sub_3C7D50; nothing when absent or without a
// handle): state 1 -> 2 once the manager is not busy; 2 sets a pending selection (+8) and, unless held (+5), reads the
// choice (+13; itfMesMngGetSelectWord84 / itfMesMngGetSelection) or goes to 3; 3 closes the window (busy off, the
// optional clear sub_3A2A30, sub_3A3420(handle, 0), sub_3C7C90(1)) and returns to 0.
void sub_3C7990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7990
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3C79A4u, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 != 0) {
        // 0x003c79b8
        charge(ctx, 3);
        lw(a0, s0, msgw::kHandle);
        if (i64(a0) >= 0) {
            // 0x003c79c4
            charge(ctx, 4);
            // by the slot's state: 3 closes the window, 2 sets a pending selection and reads the choice, 1 waits until the manager is not busy
            lb(a1, s0, msgw::kState);
            v1 = 3;
            if (a1 == v1) {
                // 0x003c7b14
                charge(ctx, 5);
                jal(ctx, 0x3C7B14u, gen::fn_sub_3C7D50_003c7d50);
                s0 = v0;
                if (s0 != 0) {
                    // 0x003c7b28
                    charge(ctx, 3);
                    lw(a0, s0, msgw::kHandle);
                    if (i64(a0) >= 0) {
                        // 0x003c7b34
                        charge(ctx, 5);
                        a1 = 0;
                        jal(ctx, 0x3C7B38u, gen::fn_itfMesMngSetBusy_003a25f0);
                        if (s1 != 0) {
                            // 0x003c7b48
                            charge(ctx, 3);
                            lw(a0, s0, msgw::kHandle);
                            jal(ctx, 0x3C7B4Cu, gen::fn_sub_3A2A30_003a2a30);
                        }
                        // 0x003c7b54
                        charge(ctx, 8);
                        lw(a0, s0, msgw::kHandle);
                        a1 = 0;
                        jal(ctx, 0x3C7B5Cu, gen::fn_sub_3A3420_003a3420);
                        a0 = 1;
                        jal(ctx, 0x3C7B68u, gen::fn_sub_3C7C90_003c7c90);
                        sb(zero, s0, msgw::kState);
                    }
                }
            } else {
                // 0x003c79d4
                charge(ctx, 3);
                v1 = 2;
                if (a1 == v1) {
                    // 0x003c7a24
                    charge(ctx, 3);
                    lw(v1, s0, msgw::kSelect);
                    if (i64(v1) >= 0) {
                        // 0x003c7a30
                        charge(ctx, 9);
                        lb(a1, s0, msgw::kFlag12);
                        jal(ctx, 0x3C7A34u, gen::fn_itfMesMngSetSelection_003a3c10);
                        lw(a0, s0, msgw::kHandle);
                        lw(a1, s0, msgw::kSelect);
                        jal(ctx, 0x3C7A44u, gen::fn_sub_3A37C0_003a37c0);
                        v1 = si(-1);
                        sw(v1, s0, msgw::kSelect);
                    }
                    // 0x003c7a54
                    charge(ctx, 3);
                    lb(v1, s0, msgw::kHold);
                    if (v1 == 0) {
                        // 0x003c7a60
                        charge(ctx, 5);
                        jal(ctx, 0x3C7A60u, gen::fn_sub_3C7D50_003c7d50);
                        s1 = v0;
                        if (s1 != 0) {
                            // 0x003c7a80
                            charge(ctx, 3);
                            lw(a0, s1, msgw::kHandle);
                            if (i64(a0) >= 0) {
                                // 0x003c7a98
                                charge(ctx, 4);
                                jal(ctx, 0x3C7A98u, gen::fn_itfMesMngGetSelectWord84_003a2750);
                                if (i64(v0) >= 0) {
                                    // 0x003c7ab4
                                    charge(ctx, 4);
                                    jal(ctx, 0x3C7AB4u, gen::fn_sub_3C7D50_003c7d50);
                                    if (v0 != 0) {
                                        // 0x003c7ad0
                                        charge(ctx, 3);
                                        lw(a0, v0, msgw::kHandle);
                                        if (i64(a0) >= 0) {
                                            // 0x003c7ae8
                                            charge(ctx, 3);
                                            jal(ctx, 0x3C7AE8u, gen::fn_itfMesMngGetSelection_003a2830);
                                            v1 = v0;
                                        } else {
                                            // 0x003c7adc
                                            charge(ctx, 3);
                                            v1 = si(-1);
                                        }
                                    } else {
                                        // 0x003c7ac4
                                        charge(ctx, 3);
                                        v1 = si(-1);
                                    }
                                    // 0x003c7af4
                                    charge(ctx, 2);
                                    sb(v1, s1, msgw::kChoice);
                                    v1 = 1;
                                } else {
                                    // 0x003c7aa8
                                    charge(ctx, 3);
                                    v1 = 0;
                                }
                            } else {
                                // 0x003c7a8c
                                charge(ctx, 3);
                                v1 = 0;
                            }
                        } else {
                            // 0x003c7a74
                            charge(ctx, 3);
                            v1 = 0;
                        }
                        // 0x003c7afc
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x003c7b04
                            charge(ctx, 4);
                            v1 = 3;
                            sb(v1, s0, msgw::kState);
                        }
                    }
                } else {
                    // 0x003c79e0
                    charge(ctx, 3);
                    v1 = 1;
                    if (a1 == v1) {
                        // 0x003c7a04
                        charge(ctx, 4);
                        jal(ctx, 0x3C7A04u, gen::fn_itfMesMngGetBusy_003a2580);
                        if (i64(v0) < 0) {
                            // 0x003c7a14
                            charge(ctx, 4);
                            v1 = 2;
                            sb(v1, s0, msgw::kState);
                        }
                    } else {
                        // 0x003c79ec
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x003c79fc
                            charge(ctx, 2);
                        } else {
                            // 0x003c79f4
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x003c7b74 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C7DD0 sub_3C7DD0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MsgHandleRelease] (i) Destroys message handle i of the table 0x6A3E50 (itfMesMngDestroyHandle) and marks it -1.
void sub_3C7DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7dd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = sll(a0, 2);
    v1 = 0x6A0000;
    v1 = addiu(v1, 15952);  // &0x6A3E50
    s0 = addu(v1, a0);
    lw(a0, s0, 0);
    if (i64(a0) >= 0) {
        // 0x003c7df8
        charge(ctx, 4);
        jal(ctx, 0x3C7DF8u, gen::fn_itfMesMngDestroyHandle_003a3060);
        v1 = si(-1);
        sw(v1, s0, 0);
    }
    // 0x003c7e08 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C8550 sub_3C8550 -- 536 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclMiscAssistUpdateSprites] (work) The MsgAssist sprite loads: the head sprite request (+24 list) is loaded once
// (sprAddFile of "facility/i_jmes01.spr", "facility/i_jmes_bNN.spr" or, for kind 9 on the AGS build (sub_17D800),
// "facility/AGS_i_jmes_b09.spr" -- sprintf) and finished when ready (flag 2, sub_3C49E0 unlinks it); then every icon
// slot marked for release drops its sprite file once it is ready (sub_1124B0). Asserts fclMisc.c 941 on NULL.
void sub_3C8550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8550
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 == 0) {
        // 0x003c8570
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 941;
        jal(ctx, 0x3C857Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003c8584
    charge(ctx, 4);
    // the head sprite request: loaded once (the file name by its kind), finished and unlinked once ready
    lw(v0, s1, assist::kSprList);
    lw(s2, v0, nml::kFirst);
    if (s2 != 0) {
        // 0x003c8594
        charge(ctx, 4);
        lw(s0, s2, nmnode::kPayload);
        lw(a0, s0, sprslot::kFile);
        if (a0 != 0) {
            // 0x003c867c
            charge(ctx, 4);
            jal(ctx, 0x3C867Cu, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x003c868c
                charge(ctx, 8);
                lw(v0, s0, sprslot::kFlags);
                v0 = v0 | 0x2;
                sw(v0, s0, sprslot::kFlags);
                lw(a0, s1, assist::kSprList);
                a1 = addiu(a0, 4);
                a2 = s2;
                jal(ctx, 0x3C86A4u, gen::fn_sub_3C49E0_003c49e0);
            }
        } else {
            // 0x003c85a4
            charge(ctx, 3);
            lw(v0, s0, sprslot::kKind);
            if (v0 != 0) {
                // 0x003c85cc
                charge(ctx, 4);
                jal(ctx, 0x3C85CCu, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x003c864c
                    charge(ctx, 6);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x6A0000;
                    a1 = addiu(a1, 16192);  // "facility/i_jmes_b%02d.spr"
                    lw(a2, s0, sprslot::kKind);
                    jal(ctx, 0x3C865Cu, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x003c85dc
                    charge(ctx, 4);
                    lw(a2, s0, sprslot::kKind);
                    v0 = 1;
                    if (a2 != v0) {
                        // 0x003c8608
                        charge(ctx, 3);
                        v0 = 9;
                        if (a2 != v0) {
                            // 0x003c8630
                            charge(ctx, 7);
                            a0 = addiu(sp, 0x40);
                            a1 = 0x6A0000;
                            a1 = addiu(a1, 16192);  // "facility/i_jmes_b%02d.spr"
                            jal(ctx, 0x3C863Cu, gen::fn_sprintf_00523ac8);
                        } else {
                            // 0x003c8614
                            charge(ctx, 7);
                            a0 = addiu(sp, 0x40);
                            a1 = 0x6A0000;
                            a1 = addiu(a1, 16160);  // "facility/AGS_i_jmes_b%02d.spr"
                            jal(ctx, 0x3C8620u, gen::fn_sprintf_00523ac8);
                        }
                    } else {
                        // 0x003c85ec
                        charge(ctx, 7);
                        a0 = addiu(sp, 0x40);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 16128);  // "facility/i_jmes_b03.spr"
                        jal(ctx, 0x3C85F8u, gen::fn_sprintf_00523ac8);
                    }
                }
            } else {
                // 0x003c85b0
                charge(ctx, 7);
                a0 = addiu(sp, 0x40);
                a1 = 0x6A0000;
                a1 = addiu(a1, 16096);  // "facility/i_jmes01.spr"
                jal(ctx, 0x3C85BCu, gen::fn_sprintf_00523ac8);
            }
            // 0x003c8664
            charge(ctx, 6);
            a0 = addiu(sp, 0x40);
            jal(ctx, 0x3C8668u, gen::fn_sprAddFile_00112370);
            sw(v0, s0, sprslot::kFile);
        }
    }
    // 0x003c86ac
    charge(ctx, 4);
    // the eleven icon slots: one marked for release drops its sprite file once it is ready
    s0 = addiu(s1, 28);
    s1 = 0;
    for (;;) {
        // 0x003c873c
        charge(ctx, 3);
        v0 = slti(s1, 11);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c86bc
        charge(ctx, 4);
        lw(v1, s0, sprslot::kFlags);
        v0 = v1 & 0x4;
        if (v0 != 0) {
            // 0x003c86cc
            charge(ctx, 3);
            lw(a0, s0, sprslot::kFile);
            if (a0 == 0) {
                // 0x003c871c
                charge(ctx, 6);
                v0 = si(-5);
                v1 = v1 & v0;
                sw(v1, s0, sprslot::kFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, sprslot::kFlags);
            } else {
                // 0x003c86d8
                charge(ctx, 4);
                jal(ctx, 0x3C86D8u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x003c86e8
                    charge(ctx, 13);
                    lw(v1, s0, sprslot::kFlags);
                    v0 = si(-5);
                    v1 = v1 & v0;
                    sw(v1, s0, sprslot::kFlags);
                    v0 = si(-3);
                    v0 = v1 & v0;
                    sw(v0, s0, sprslot::kFlags);
                    lw(a0, s0, sprslot::kFile);
                    jal(ctx, 0x3C8708u, gen::fn_sub_1124B0_001124b0);
                    sw(zero, s0, sprslot::kFile);
                }
            }
        }
        // 0x003c8734
        charge(ctx, 2);
        s0 = addiu(s0, 12);
        s1 = addiu(s1, 1);
    }
    // 0x003c8748
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003C89A0 fclMisc_UpdateMsgAssistTask -- 424 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Update of the "MsgAssist" task. While it is free (+4 bit 0): with the icon sprites loading (bit 1) it waits for them
// (sub_3C8810 / sub_3C8D80), then advances the request list (sub_3C8DC0, sub_3C4A90) and refreshes the eleven icon slots
// (sub_3C8770); otherwise the head request takes the window (bit 0 off; sub_3C91B0 on its slot with its kind,
// sub_3C8400 for icon 0 and its icon, request flags 3). Then a shown head request whose window finished (sub_3C8B50)
// frees the task again (bit 0) and is unlinked (sub_3C49E0); the sprites are updated (sub_3C8550); returns 0.
void fclMisc_UpdateMsgAssistTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c89a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, gp, g::kGpAssist);  // 0x7CE67C
    // free (bit 0): bit 1 -> wait for the icon sprites, else the head request takes the window
    lw(v1, s1, assist::kFlags);
    v0 = v1 & 0x1;
    if (v0 != 0) {
        // 0x003c89c4
        charge(ctx, 3);
        v0 = v1 & 0x2;
        if (v0 == 0) {
            // 0x003c8a4c
            charge(ctx, 4);
            lw(v0, s1, assist::kList);
            lw(v0, v0, nml::kFirst);
            if (v0 != 0) {
                // 0x003c8a68
                charge(ctx, 1);
                lw(s0, v0, nmnode::kPayload);
            } else {
                // 0x003c8a5c
                charge(ctx, 3);
                s0 = 0;
            }
            // 0x003c8a6c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x003c8a74
                charge(ctx, 21);
                lw(v1, s1, assist::kFlags);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s1, assist::kFlags);
                a0 = addiu(s0, 16);
                lw(a1, s0, req::kKind);
                jal(ctx, 0x3C8A8Cu, gen::fn_sub_3C91B0_003c91b0);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x3C8A9Cu, gen::fn_sub_3C8400_003c8400);
                a0 = s1;
                lw(a1, s0, req::kIcon);
                jal(ctx, 0x3C8AACu, gen::fn_sub_3C8400_003c8400);
                lw(v0, s0, req::kFlags);
                v0 = v0 | 0x2;
                sw(v0, s0, req::kFlags);
                v0 = v0 | 0x1;
                sw(v0, s0, req::kFlags);
            }
        } else {
            // 0x003c89d0
            charge(ctx, 7);
            a0 = s1;
            jal(ctx, 0x3C89D4u, gen::fn_sub_3C8810_003c8810);
            jal(ctx, 0x3C89DCu, gen::fn_sub_3C8D80_003c8d80);
            if (v0 != 0) {
                // 0x003c89ec
                charge(ctx, 14);
                lw(v1, s1, assist::kFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s1, assist::kFlags);
                a0 = 0;
                jal(ctx, 0x3C8A00u, gen::fn_sub_3C8DC0_003c8dc0);
                lw(a0, s1, assist::kList);
                a1 = addiu(a0, 4);
                jal(ctx, 0x3C8A10u, gen::fn_sub_3C4A90_003c4a90);
                s0 = 0;
                for (;;) {
                    // 0x003c8a38
                    charge(ctx, 3);
                    v0 = slti(s0, 11);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003c8a24
                    charge(ctx, 5);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x3C8A2Cu, gen::fn_sub_3C8770_003c8770);
                    s0 = addiu(s0, 1);
                }
                // 0x003c8a44
                charge(ctx, 2);
            }
        }
    }
    // 0x003c8ac8
    charge(ctx, 4);
    // the shown head request: once its window finished, the task is free again and the node unlinked
    lw(v0, s1, assist::kList);
    lw(s0, v0, nml::kFirst);
    if (s0 != 0) {
        // 0x003c8ad8
        charge(ctx, 5);
        lw(a1, s0, nmnode::kPayload);
        lw(v0, a1, req::kFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x003c8aec
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x3C8AF0u, gen::fn_sub_3C8B50_003c8b50);
            if (v0 != 0) {
                // 0x003c8b00
                charge(ctx, 8);
                lw(v0, s1, assist::kFlags);
                v0 = v0 | 0x1;
                sw(v0, s1, assist::kFlags);
                lw(a0, s1, assist::kList);
                a1 = addiu(a0, 4);
                a2 = s0;
                jal(ctx, 0x3C8B18u, gen::fn_sub_3C49E0_003c49e0);
            }
        }
    }
    // 0x003c8b20
    charge(ctx, 10);
    a0 = s1;
    jal(ctx, 0x3C8B24u, gen::fn_sub_3C8550_003c8550);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C8B50 sub_3C8B50 -- 552 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclMiscAssistStepRequest] (work, request) One request: finished (+4 bit 2) -> once the manager state has none of
// 0x3300 the window is released (sub_3C9240) and the icon slots it used marked for release unless kept (+20; asserts
// fclMisc.c 1003 / 1004), 1; pending (bit 0) -> waits for the slot sprites, then shows the message (sub_3C9290); then the
// window steps (sub_3C9390) and, once it closed (sub_3C9340 == 0), is cleared (sub_3C9460) and marked finished. 0
// otherwise. Asserts fclMisc.c 995 on a NULL work.
void sub_3C8B50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8b50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a1, 4);
    // finished (bit 2) -> released once the manager's state has none of 0x3300; pending (bit 0) -> shown once the slot sprites are in
    v0 = v1 & 0x4;
    if (v0 == 0) {
        // 0x003c8c6c
        charge(ctx, 3);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x003c8c78
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x003c8c80
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 15896);  // "fclMisc.c"
                a1 = 995;
                jal(ctx, 0x3C8C8Cu, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003c8c94
            charge(ctx, 4);
            lw(v0, s1, assist::kSlots);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x003c8cb0
                charge(ctx, 3);
                lw(s2, s0, req::kIcon);
                if (s1 == 0) {
                    // 0x003c8cbc
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 15896);  // "fclMisc.c"
                    a1 = 995;
                    jal(ctx, 0x3C8CC8u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003c8cd0
                charge(ctx, 8);
                v0 = sll(s2, 1);
                v0 = addu(v0, s2);
                v0 = sll(v0, 2);
                v0 = addu(s1, v0);
                lw(v0, v0, assist::kSlots);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x003c8cfc
                    charge(ctx, 9);
                    lw(v1, s0, req::kFlags);
                    v0 = si(-2);
                    v0 = v1 & v0;
                    sw(v0, s0, req::kFlags);
                    a0 = addiu(s0, 16);
                    lw(a1, s0, req::kIcon);
                    lw(a2, s0, req::kMsg);
                    jal(ctx, 0x3C8D18u, gen::fn_sub_3C9290_003c9290);
                    goto L_003c8d20;
                }
                // 0x003c8cf0
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x003c8ca4
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x003c8d5c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    // the window steps; once it closed it is cleared and the request marked finished
    L_003c8d20:
        charge(ctx, 8);
        a0 = addiu(s0, 16);
        jal(ctx, 0x3C8D24u, gen::fn_sub_3C9390_003c9390);
        a0 = addiu(s0, 16);
        jal(ctx, 0x3C8D30u, gen::fn_sub_3C9340_003c9340);
        if (v0 == 0) {
            // 0x003c8d40
            charge(ctx, 6);
            a0 = addiu(s0, 16);
            jal(ctx, 0x3C8D44u, gen::fn_sub_3C9460_003c9460);
            lw(v0, s0, req::kFlags);
            v0 = v0 | 0x4;
            sw(v0, s0, req::kFlags);
        }
        // 0x003c8d58
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c8b7c
        charge(ctx, 6);
        lw(a0, s0, req::kWin);
        jal(ctx, 0x3C8B80u, gen::fn_itfMesMngGetState_003a3da0);
        v0 = v0 & 0x3300;
        if (v0 != 0) {
            // 0x003c8c60
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x003c8b94
            charge(ctx, 7);
            a0 = addiu(s0, 16);
            jal(ctx, 0x3C8B98u, gen::fn_sub_3C9240_003c9240);
            lw(v0, s1, assist::kKeepMask);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x003c8bb0
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x003c8bb8
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 15896);  // "fclMisc.c"
                    a1 = 1003;
                    jal(ctx, 0x3C8BC4u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003c8bcc
                charge(ctx, 3);
                lw(v0, s1, assist::kSlots);
                v0 = v0 | 0x4;
                sw(v0, s1, assist::kSlots);
            }
            // 0x003c8bd8
            charge(ctx, 7);
            lw(s0, s0, req::kIcon);
            v0 = 1;
            v1 = sllv(v0, s0);
            lw(v0, s1, assist::kKeepMask);
            v0 = v0 & v1;
            if (v0 == 0) {
                // 0x003c8bf4
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x003c8bfc
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 15896);  // "fclMisc.c"
                    a1 = 1003;
                    jal(ctx, 0x3C8C08u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x003c8c10
                charge(ctx, 2);
                if (i64(s0) >= 0) {
                    // 0x003c8c18
                    charge(ctx, 3);
                    at = slti(s0, 12);
                    if (at == 0) {
                        goto L_003c8c24;
                    }
                    goto L_003c8c38;
                }
            L_003c8c24:
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 15896);  // "fclMisc.c"
                a1 = 1004;
                jal(ctx, 0x3C8C30u, gen::fn_sub_19D3F0_0019d3f0);
            L_003c8c38:
                charge(ctx, 7);
                v0 = sll(s0, 1);
                v0 = addu(v0, s0);
                v0 = sll(v0, 2);
                v1 = addu(s1, v0);
                lw(v0, v1, assist::kSlots);
                v0 = v0 | 0x4;
                sw(v0, v1, assist::kSlots);
            }
            // 0x003c8c54
            charge(ctx, 3);
            v0 = 1;
        }
    }
    // 0x003c8d5c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C8FA0 sub_3C8FA0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclMiscAssistClose] Closes the head request's window when it is shown (sub_3C9460) and marks it finished.
void sub_3C8FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c8fa0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, g::kGpAssist);  // 0x7CE67C
    lw(v1, v1, assist::kList);
    lw(v1, v1, nml::kFirst);
    if (v1 != 0) {
        // 0x003c8fc0
        charge(ctx, 5);
        lw(s0, v1, nmnode::kPayload);
        lw(v1, s0, req::kFlags);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            // 0x003c8fd4
            charge(ctx, 6);
            a0 = addiu(s0, 16);
            jal(ctx, 0x3C8FD8u, gen::fn_sub_3C9460_003c9460);
            lw(v1, s0, req::kFlags);
            v1 = v1 | 0x4;
            sw(v1, s0, req::kFlags);
        }
    }
    // 0x003c8fec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9000 sub_3C9000 -- 428 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclMiscAssistDrawIcon] (x, y, alpha, slot, sprite, $f12 z, $f13, $f14) Draws icon slot `slot` when its sprite file
// is loaded: a sprite handle (sprCreateHandle(0, file, sprite)) at (x, y, z), alpha 255 - a, $f13 / $f14 as the two
// 4096-scaled fixed values +40 / +42 (the float -> u16 conversion with its 2^31 bias), drawn (sub_1127D0(h, 1)) and
// freed (sub_115980).
void sub_3C9000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x003c9000
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    mov_s(f22, f12);
    s1 = a2;
    mov_s(f21, f13);
    mov_s(f20, f14);
    lw(a0, gp, g::kGpAssist);  // 0x7CE67C
    v1 = sll(a3, 1);
    v1 = addu(v1, a3);
    v1 = sll(v1, 2);
    a1 = addu(v1, a0);
    lw(v1, a1, assist::kSlots);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x003c9060
        charge(ctx, 29);
        a0 = 0;
        lw(a1, a1, assist::kSlotFile);
        a2 = t0;
        jal(ctx, 0x3C906Cu, gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v0, sprh::kX);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v0, sprh::kY);
        swc1(f22, v0, sprh::kZ);
        a0 = 255;
        v1 = s1 & 0xFF;
        v1 = subu(a0, v1);
        sb(v1, v0, sprh::kInvAlpha);
        v0 = 0x45800000;
        mtc1(v0, f0);
        mul_s(f1, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x003c90ec
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFFFF;
        } else {
            // 0x003c90d4
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFFFF;
        }
        // 0x003c9104
        charge(ctx, 11);
        sh(v1, s0, sprh::kFix0);
        v0 = 0x45800000;
        mtc1(v0, f0);
        mul_s(f1, f0, f20);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x003c9148
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFFFF;
        } else {
            // 0x003c9130
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFFFF;
        }
        // 0x003c9160
        charge(ctx, 8);
        sh(v1, s0, sprh::kFix1);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x3C916Cu, gen::fn_sub_1127D0_001127d0);
        a0 = s0;
        jal(ctx, 0x3C9178u, gen::fn_sub_115980_00115980);
    }
    // 0x003c9180 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003C91B0 sub_3C91B0 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MsgWinOpen] (slot, kind) Resets a message-window slot (handle -1, state 0, hold 0, selection -1, +12 / +13 1) and,
// when it has no handle, creates one (itfMesMngInitialize(kind), sub_3A4360(h, 5)): 1; else 0. Since the reset writes
// handle -1 first, the "already has one" branch is dead: a non-NULL slot always gets a new handle (1) -- an old one
// is dropped without itfMesMngDestroyHandle. A NULL slot skips the reset and reads address 0.
void sub_3C91B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c91b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x003c91c8
        charge(ctx, 8);
        v0 = si(-1);
        sw(v0, s0, msgw::kHandle);
        sb(zero, s0, msgw::kState);
        sb(zero, s0, msgw::kHold);
        sw(v0, s0, msgw::kSelect);
        v0 = 1;
        sb(v0, s0, msgw::kFlag12);
        sb(v0, s0, msgw::kChoice);
    }
    // 0x003c91e8
    charge(ctx, 3);
    lw(v0, s0, msgw::kHandle);
    if (i64(v0) >= 0) {
        // 0x003c9220
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c91f4
        charge(ctx, 11);
        a0 = a1;
        jal(ctx, 0x3C91F8u, gen::fn_itfMesMngInitialize_003a2d80);
        sw(v0, s0, msgw::kHandle);
        a0 = v0;
        a1 = 5;
        jal(ctx, 0x3C920Cu, gen::fn_sub_3A4360_003a4360);
        v0 = 1;
    }
    // 0x003c9224 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9240 sub_3C9240 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MsgWinRelease] (slot) Clears the window (sub_3C9460) and destroys its handle: handle -1, state 0, hold 0.
void sub_3C9240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9240
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x3C9250u, gen::fn_sub_3C9460_003c9460);
    lw(a0, s0, msgw::kHandle);
    if (i64(a0) >= 0) {
        // 0x003c9264
        charge(ctx, 6);
        jal(ctx, 0x3C9264u, gen::fn_itfMesMngDestroyHandle_003a3060);
        v1 = si(-1);
        sw(v1, s0, msgw::kHandle);
        sb(zero, s0, msgw::kState);
        sb(zero, s0, msgw::kHold);
    }
    // 0x003c927c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9290 sub_3C9290 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [MsgWinShow] (slot, icon, msg) Shows message `msg` in the slot's window: state flags, the request
// (itfMesMngRequestMessage(h, msg, 0)), the layout sub_3A5210(h, 1, 5, 32, 0), the icon (sub_3A8600(h, icon)); state 1.
void sub_3C9290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(a0, a0, msgw::kHandle);
    if (i64(a0) >= 0) {
        // 0x003c92c8
        charge(ctx, 22);
        a1 = 0x200000;
        jal(ctx, 0x3C92CCu, gen::fn_itfMesMngSetStateFlags_003a3e10);
        lw(a0, s2, msgw::kHandle);
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x3C92E0u, gen::fn_itfMesMngRequestMessage_003a30c0);
        lw(a0, s2, msgw::kHandle);
        a1 = 1;
        a2 = 5;
        a3 = 32;
        t0 = 0;
        jal(ctx, 0x3C92FCu, gen::fn_sub_3A5210_003a5210);
        lw(a0, s2, msgw::kHandle);
        a1 = s1;
        jal(ctx, 0x3C930Cu, gen::fn_sub_3A8600_003a8600);
        v0 = 1;
        sb(v0, s2, msgw::kState);
        v0 = 0;
    } else {
        // 0x003c92bc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c9320 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C9390 sub_3C9390 -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MsgWinUpdate] (slot) One step of a window slot: 1 -> 2 once not busy; 2 drops a pending selection and goes to 3
// unless held; 3 clears the window (sub_3C9460).
void sub_3C9390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9390
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a2, a0, msgw::kHandle);
    if (i64(a2) >= 0) {
        // 0x003c93ac
        charge(ctx, 4);
        // 3 clears the window; 2 drops a pending selection and closes unless held; 1 -> 2 once the manager is not busy
        lb(a1, s0, msgw::kState);
        v1 = 3;
        if (a1 == v1) {
            // 0x003c9440
            charge(ctx, 2);
            jal(ctx, 0x3C9440u, gen::fn_sub_3C9460_003c9460);
        } else {
            // 0x003c93bc
            charge(ctx, 3);
            v1 = 2;
            if (a1 == v1) {
                // 0x003c9410
                charge(ctx, 3);
                lw(v1, s0, msgw::kSelect);
                if (i64(v1) >= 0) {
                    // 0x003c941c
                    charge(ctx, 2);
                    v1 = si(-1);
                    sw(v1, s0, msgw::kSelect);
                }
                // 0x003c9424
                charge(ctx, 3);
                lb(v1, s0, msgw::kHold);
                if (v1 == 0) {
                    // 0x003c9430
                    charge(ctx, 4);
                    v1 = 3;
                    sb(v1, s0, msgw::kState);
                }
            } else {
                // 0x003c93c8
                charge(ctx, 3);
                v1 = 1;
                if (a1 == v1) {
                    // 0x003c93ec
                    charge(ctx, 5);
                    a0 = a2;
                    jal(ctx, 0x3C93F0u, gen::fn_itfMesMngGetBusy_003a2580);
                    if (i64(v0) < 0) {
                        // 0x003c9400
                        charge(ctx, 4);
                        v1 = 2;
                        sb(v1, s0, msgw::kState);
                    }
                } else {
                    // 0x003c93d4
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x003c93e4
                        charge(ctx, 2);
                    } else {
                        // 0x003c93dc
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x003c9448 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C9460 sub_3C9460 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MsgWinClear] (slot) For a slot with a handle: busy off, sub_3A2A30, sub_3A3420(h, 0), state 0: 1; else 0.
void sub_3C9460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9460
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x003c9484
        charge(ctx, 3);
        lw(a0, s0, msgw::kHandle);
        if (i64(a0) >= 0) {
            // 0x003c949c
            charge(ctx, 12);
            a1 = 0;
            jal(ctx, 0x3C94A0u, gen::fn_itfMesMngSetBusy_003a25f0);
            lw(a0, s0, msgw::kHandle);
            jal(ctx, 0x3C94ACu, gen::fn_sub_3A2A30_003a2a30);
            lw(a0, s0, msgw::kHandle);
            a1 = 0;
            jal(ctx, 0x3C94BCu, gen::fn_sub_3A3420_003a3420);
            sb(zero, s0, msgw::kState);
            v0 = 1;
        } else {
            // 0x003c9490
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c9478
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c94cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
