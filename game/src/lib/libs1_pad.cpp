// libpad's EE-side readers (0x511988-0x512838): every reader takes the newest of the two 128-byte DMA frames padman
// writes for an open port / slot (through scePadGetDmaStr, still recompiled: it masks interrupts and syncs the cache)
// and decodes it -- the button data, the state and request state, the actuator / combination / mode tables and the
// pressure-button capability of a DualShock 2. The port / slot table is libs1::pad::kPortTable (0x96DD10).
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass (scratch spec.py, checked by check.py) adds the
// role comments and the named offsets of game/include/p3fes/game/libs1_pad.h, each equal to the literal it replaces.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs1_pad.h"

namespace p3fes::recomp_gen {
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_scePadEnterPressMode_005123f0(p3fes::EEContext&);
void fn_scePadExitPressMode_00512448(p3fes::EEContext&);
void fn_scePadGetButtonMask_00512210(p3fes::EEContext&);
void fn_scePadGetDmaStr_00511830(p3fes::EEContext&);
void fn_scePadGetFrameCount_00511988(p3fes::EEContext&);
void fn_scePadGetReqState_00511bc0(p3fes::EEContext&);
void fn_scePadGetState_00511a58(p3fes::EEContext&);
void fn_scePadInfoAct_00511c50(p3fes::EEContext&);
void fn_scePadInfoComb_00511d68(p3fes::EEContext&);
void fn_scePadInfoMode_00511e80(p3fes::EEContext&);
void fn_scePadInfoPressMode_00512370(p3fes::EEContext&);
void fn_scePadRead_005119e0(p3fes::EEContext&);
void fn_scePadReqIntToStr_00511c18(p3fes::EEContext&);
void fn_scePadSetButtonInfo_005122c0(p3fes::EEContext&);
void fn_scePadSetFlushRate_00512838(p3fes::EEContext&);
void fn_scePadStateIntToStr_00511ad0(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00511988 scePadGetFrameCount -- 88 bytes; frame 0x10: ra sp+0x0
// The frame counter of the newest DMA frame (+88) of an open port / slot; 0 when it is not open.
void scePadGetFrameCount(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00511988
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x10);
    v0 = 0x970000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x005119c8
        charge(ctx, 3);
        a2 = 0;
        jal(ctx, 0x5119C8u, gen::fn_scePadGetDmaStr_00511830);
        lw(v0, v0, 88);
    } else {
        // 0x005119c0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x005119d4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005119E0 scePadRead -- 116 bytes; frame 0xA0: s0 sp+0x80, ra sp+0x90
// Copy the newest pad data of an open port / slot (the DMA frame through scePadGetDmaStr into a stack copy, then its
// length (+96) bytes from it) to the caller's buffer; returns the length, 0 when the port is not open.
void scePadRead(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005119e0
    enter(ctx, 15);  // entry check point + this block's cycles
    a3 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a3, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0xA0);
    v0 = 0x970000;
    sd(s0, sp, 0x80);
    sd(ra, sp, 0x90);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    s0 = a2;
    if (v1 != 0) {
        // 0x00511a24
        charge(ctx, 8);
        a0 = a3;
        a2 = sp;
        jal(ctx, 0x511A28u, gen::fn_scePadGetDmaStr_00511830);
        lw(a2, sp, 0x60);
        a0 = s0;
        a1 = sp;
        jal(ctx, 0x511A38u, gen::fn_memcpy_00521250);
        lw(v0, sp, 0x60);
    } else {
        // 0x00511a1c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00511a44 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x90);
    ld(s0, sp, 0x80);
    sp = addiu(sp, 0xA0);
}

// 0x00511A58 scePadGetState -- 120 bytes; frame 0x90: ra sp+0x80
// The pad state of a port / slot: 99 when it is not open, 5 ("stable") for a frame in state 6 with sub-state 2, else
// the frame's state byte (+112).
void scePadGetState(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511a58
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x90);
    v0 = 0x970000;
    sd(ra, sp, 0x80);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x00511a98
        charge(ctx, 6);
        a2 = sp;
        jal(ctx, 0x511A98u, gen::fn_scePadGetDmaStr_00511830);
        lbu(v1, sp, 0x70);
        v0 = 6;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        lbu(v0, sp, 0x70);
        if (!cc) {
            // 0x00511ab0
            charge(ctx, 4);
            lbu(v1, sp, 0x71);
            v0 = 2;
            cc = v1 != v0;  // the condition, before the delay slot changes it
            lbu(v0, sp, 0x70);
            if (!cc) {
                // 0x00511ac0
                charge(ctx, 1);
                v0 = 5;
            }
        }
    } else {
        // 0x00511a90
        charge(ctx, 2);
        v0 = 99;
    }
    // 0x00511ac4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0x90);
}

// 0x00511AD0 scePadStateIntToStr -- 52 bytes; leaf frame (no stack)
// The name of a pad state 0..7 (the string table 0x782758) copied with strcpy; an empty string otherwise.
void scePadStateIntToStr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511ad0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a0, 8);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x7C0000;
    if (cc) {
        // 0x00511af8
        charge(ctx, 3);
        lbu(v1, v0, -7088);
        sb(v1, a1, 0);
        return;
    }
    // 0x00511adc
    charge(ctx, 7);
    v0 = 0x780000;
    v1 = sll(a0, 2);
    v0 = addiu(v0, 10072);  // &0x782758
    a0 = a1;
    v1 = addu(v1, v0);
    lw(a1, v1, 0);
    gen::fn_strcpy_00524270(ctx);  // tail call
}

// 0x00511BC0 scePadGetReqState -- 88 bytes; frame 0x10: ra sp+0x0
// The request state of an open port / slot (the newest frame's byte +113); 0 when not open.
void scePadGetReqState(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00511bc0
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x10);
    v0 = 0x970000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x00511c00
        charge(ctx, 3);
        a2 = 0;
        jal(ctx, 0x511C00u, gen::fn_scePadGetDmaStr_00511830);
        lbu(v0, v0, 113);
    } else {
        // 0x00511bf8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00511c0c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00511C18 scePadReqIntToStr -- 52 bytes; leaf frame (no stack)
// The name of a request state 0..3 (table 0x782778); an empty string otherwise.
void scePadReqIntToStr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511c18
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = sltiu(a0, 4);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x7C0000;
    if (cc) {
        // 0x00511c40
        charge(ctx, 3);
        lbu(v1, v0, -7088);
        sb(v1, a1, 0);
        return;
    }
    // 0x00511c24
    charge(ctx, 7);
    v0 = 0x780000;
    v1 = sll(a0, 2);
    v0 = addiu(v0, 10104);  // &0x782778
    a0 = a1;
    v1 = addu(v1, v0);
    lw(a1, v1, 0);
    gen::fn_strcpy_00524270(ctx);  // tail call
}

// 0x00511C50 scePadInfoAct -- 280 bytes; frame 0xB0: s1 sp+0x90, s0 sp+0x80, ra sp+0xA0
// Actuator information of a DualShock in extended mode (state byte +114 == 1, mode +100 >= 2): -1 asks for the
// actuator count (+106), 1..4 the actuator's four description bytes (+48.. + 4 x index); 0 otherwise.
void scePadInfoAct(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511c50
    enter(ctx, 17);  // entry check point + this block's cycles
    t0 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, t0, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0xB0);
    v0 = 0x970000;
    sd(s1, sp, 0x90);
    sd(s0, sp, 0x80);
    v0 = addiu(v0, -8944);  // &0x96DD10
    sd(ra, sp, 0xA0);
    s1 = a2;
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    s0 = a3;
    if (v1 != 0) {
        // 0x00511c94
        charge(ctx, 7);
        a0 = t0;
        a2 = sp;
        jal(ctx, 0x511C98u, gen::fn_scePadGetDmaStr_00511830);
        lbu(a0, sp, 0x72);
        v0 = 1;
        cc = a0 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00511cb0
            charge(ctx, 4);
            lbu(v0, sp, 0x64);
            v0 = sltiu(v0, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x00511cc0
                charge(ctx, 4);
                lbu(v1, sp, 0x6A);
                v0 = slt(s1, v1);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = si(-1);
                if (cc) {
                    goto L_00511d50;
                }
                // 0x00511cd0
                charge(ctx, 2);
                cc = s1 != v0;  // the condition, before the delay slot changes it
                v0 = 2;
                if (cc) {
                    // 0x00511ce0
                    charge(ctx, 2);
                    cc = s0 == v0;  // the condition, before the delay slot changes it
                    v0 = sll(s1, 2);
                    if (cc) {
                        // 0x00511d2c
                        charge(ctx, 3);
                        v1 = addu(sp, v0);
                        lbu(v0, v1, 49);
                    } else {
                        // 0x00511ce8
                        charge(ctx, 3);
                        v0 = slti(s0, 3);
                        if (v0 == 0) {
                            v0 = 3;
                            // 0x00511d04
                            charge(ctx, 2);
                            cc = s0 == v0;  // the condition, before the delay slot changes it
                            v0 = sll(s1, 2);
                            if (cc) {
                                // 0x00511d38
                                charge(ctx, 3);
                                v1 = addu(sp, v0);
                                lbu(v0, v1, 50);
                            } else {
                                // 0x00511d0c
                                charge(ctx, 3);
                                v0 = 4;
                                cc = s0 == v0;  // the condition, before the delay slot changes it
                                v0 = sll(s1, 2);
                                if (cc) {
                                    // 0x00511d44
                                    charge(ctx, 3);
                                    v1 = addu(sp, v0);
                                    lbu(v0, v1, 51);
                                } else {
                                    // 0x00511d18
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                            }
                        } else {
                            // 0x00511cf4
                            charge(ctx, 2);
                            v0 = sll(s1, 2);
                            if (s0 == a0) {
                                // 0x00511d20
                                charge(ctx, 3);
                                v1 = addu(sp, v0);
                                lbu(v0, v1, 48);
                            } else {
                                // 0x00511cfc
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        }
                    }
                } else {
                    // 0x00511cd8
                    charge(ctx, 2);
                    v0 = v1;
                }
            }
        }
        // 0x00511d54 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0xA0);
        ld(s1, sp, 0x90);
        ld(s0, sp, 0x80);
        sp = addiu(sp, 0xB0);
        return;
    }
L_00511d50:
    charge(ctx, 1);
    v0 = 0;
    // 0x00511d54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0xA0);
    ld(s1, sp, 0x90);
    ld(s0, sp, 0x80);
    sp = addiu(sp, 0xB0);
}

// 0x00511D68 scePadInfoComb -- 276 bytes; frame 0xB0: s1 sp+0x90, s0 sp+0x80, ra sp+0xA0
// Actuator combination information (count +107; -1 / 0 / 1 / 2 pick the bytes +64 / +65 / +66 / +67 of the entry); 0
// outside extended mode.
void scePadInfoComb(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511d68
    enter(ctx, 17);  // entry check point + this block's cycles
    t0 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, t0, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0xB0);
    v0 = 0x970000;
    sd(s1, sp, 0x90);
    sd(s0, sp, 0x80);
    v0 = addiu(v0, -8944);  // &0x96DD10
    sd(ra, sp, 0xA0);
    s1 = a2;
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    s0 = a3;
    if (v1 == 0) {
        // 0x00511e64
        charge(ctx, 1);
        v0 = 0;
    L_00511e68:
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
    } else {
        // 0x00511dac
        charge(ctx, 7);
        a0 = t0;
        a2 = sp;
        jal(ctx, 0x511DB0u, gen::fn_scePadGetDmaStr_00511830);
        lbu(v1, sp, 0x72);
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            goto L_00511e68;
        }
        // 0x00511dc8
        charge(ctx, 4);
        lbu(v0, sp, 0x64);
        v0 = sltiu(v0, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            goto L_00511e68;
        }
        // 0x00511dd8
        charge(ctx, 3);
        a0 = si(-1);
        lbu(v0, sp, 0x6B);
        if (s1 != a0) {
            // 0x00511dec
            charge(ctx, 3);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                v0 = 0;
            } else {
                // 0x00511df8
                charge(ctx, 2);
                if (s0 == 0) {
                    v0 = sll(s1, 2);
                    // 0x00511e40
                    charge(ctx, 3);
                    v1 = addu(sp, v0);
                    lbu(v0, v1, 65);
                } else {
                    // 0x00511e00
                    charge(ctx, 2);
                    if (i64(s0) > 0) {
                        // 0x00511e18
                        charge(ctx, 2);
                        v0 = sll(s1, 2);
                        if (s0 == v1) {
                            // 0x00511e4c
                            charge(ctx, 3);
                            v1 = addu(sp, v0);
                            lbu(v0, v1, 66);
                        } else {
                            // 0x00511e20
                            charge(ctx, 3);
                            v0 = 2;
                            cc = s0 == v0;  // the condition, before the delay slot changes it
                            v0 = sll(s1, 2);
                            if (cc) {
                                // 0x00511e58
                                charge(ctx, 3);
                                v1 = addu(sp, v0);
                                lbu(v0, v1, 67);
                            } else {
                                // 0x00511e2c
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        }
                    } else {
                        // 0x00511e08
                        charge(ctx, 2);
                        v0 = sll(s1, 2);
                        if (s0 == a0) {
                            // 0x00511e34
                            charge(ctx, 3);
                            v1 = addu(sp, v0);
                            lbu(v0, v1, 64);
                        } else {
                            // 0x00511e10
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    }
                }
            }
            goto L_00511e68;
        }
        // 0x00511de4
        charge(ctx, 2);
        ld(ra, sp, 0xA0);
    }
    // 0x00511e6c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x90);
    ld(s0, sp, 0x80);
    sp = addiu(sp, 0xB0);
}

// 0x00511E80 scePadInfoMode -- 308 bytes; frame 0xB0: s1 sp+0x90, s0 sp+0x80, ra sp+0xA0
// Mode information: 1 the current mode id (high nibble of +101, 0 for 0xF3), 2 / 3 / 4 the mode table (+80.., count
// +104, current index +105); 0 when the pad is not ready or in config mode.
void scePadInfoMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00511e80
    enter(ctx, 17);  // entry check point + this block's cycles
    t0 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, t0, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0xB0);
    v0 = 0x970000;
    sd(s1, sp, 0x90);
    sd(s0, sp, 0x80);
    v0 = addiu(v0, -8944);  // &0x96DD10
    sd(ra, sp, 0xA0);
    s0 = a2;
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    s1 = a3;
    if (v1 != 0) {
        // 0x00511ec4
        charge(ctx, 7);
        a0 = t0;
        a2 = sp;
        jal(ctx, 0x511EC8u, gen::fn_scePadGetDmaStr_00511830);
        lbu(v1, sp, 0x72);
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
        L_00511fa0:
            charge(ctx, 1);
            ld(ra, sp, 0xA0);
        } else {
            // 0x00511ee0
            charge(ctx, 4);
            lbu(v0, sp, 0x71);
            a0 = 2;
            cc = v0 == a0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (cc) {
                goto L_00511fa0;
            }
            // 0x00511ef0
            charge(ctx, 2);
            v0 = slti(s0, 3);
            if (s0 == a0) {
                // 0x00511f40
                charge(ctx, 3);
                lbu(v0, sp, 0x64);
                cc = v0 == v1;  // the condition, before the delay slot changes it
                lbu(v0, sp, 0x69);
                if (cc) {
                    goto L_00511f9c;
                }
                // 0x00511f4c
                charge(ctx, 2);
                v0 = sll(v0, 1);
            L_00511f90:
                charge(ctx, 3);
                v1 = addu(sp, v0);
                lhu(v0, v1, 80);
                goto L_00511fa0;
            }
            // 0x00511ef8
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (cc) {
                // 0x00511f10
                charge(ctx, 2);
                cc = s0 == v0;  // the condition, before the delay slot changes it
                v0 = 4;
                if (cc) {
                    // 0x00511f54
                    charge(ctx, 3);
                    lbu(v0, sp, 0x64);
                    cc = v0 == v1;  // the condition, before the delay slot changes it
                    lbu(v0, sp, 0x69);
                    if (cc) {
                        goto L_00511f9c;
                    }
                    // 0x00511f60
                    charge(ctx, 2);
                    ld(ra, sp, 0xA0);
                } else {
                    // 0x00511f18
                    charge(ctx, 2);
                    cc = s0 == v0;  // the condition, before the delay slot changes it
                    v0 = 0;
                    if (cc) {
                        // 0x00511f68
                        charge(ctx, 3);
                        lbu(v0, sp, 0x64);
                        cc = v0 == v1;  // the condition, before the delay slot changes it
                        v0 = si(-1);
                        if (cc) {
                            goto L_00511f9c;
                        }
                        // 0x00511f74
                        charge(ctx, 2);
                        cc = s1 != v0;  // the condition, before the delay slot changes it
                        lbu(v0, sp, 0x68);
                        if (cc) {
                            // 0x00511f84
                            charge(ctx, 3);
                            v0 = slt(s1, v0);
                            cc = v0 == 0;  // the condition, before the delay slot changes it
                            v0 = sll(s1, 1);
                            if (cc) {
                                goto L_00511f9c;
                            }
                            goto L_00511f90;
                        }
                        // 0x00511f7c
                        charge(ctx, 2);
                        ld(ra, sp, 0xA0);
                    } else {
                        // 0x00511f20
                        charge(ctx, 2);
                        ld(ra, sp, 0xA0);
                    }
                }
            } else {
                // 0x00511f00
                charge(ctx, 2);
                v0 = 0;
                if (s0 == v1) {
                    // 0x00511f28
                    charge(ctx, 4);
                    lbu(v1, sp, 0x65);
                    v0 = 243;
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    v0 = srl(v1, 4);
                    if (cc) {
                        goto L_00511f9c;
                    }
                    // 0x00511f38
                    charge(ctx, 2);
                    ld(ra, sp, 0xA0);
                } else {
                    // 0x00511f08
                    charge(ctx, 2);
                    ld(ra, sp, 0xA0);
                }
            }
        }
        // 0x00511fa4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x90);
        ld(s0, sp, 0x80);
        sp = addiu(sp, 0xB0);
        return;
    }
L_00511f9c:
    charge(ctx, 1);
    v0 = 0;
    goto L_00511fa0;
}

// 0x00512210 scePadGetButtonMask -- 176 bytes; frame 0x90: ra sp+0x80
// The pressure-button mask of a DualShock 2 (+121..+124, little-endian) in extended mode with the pressure capability
// (+102 >= 2); 0 otherwise.
void scePadGetButtonMask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512210
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x90);
    v0 = 0x970000;
    sd(ra, sp, 0x80);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x00512248
        charge(ctx, 6);
        a2 = sp;
        jal(ctx, 0x512248u, gen::fn_scePadGetDmaStr_00511830);
        lbu(v1, sp, 0x72);
        v0 = 1;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        lbu(v0, sp, 0x64);
        if (!cc) {
            goto L_00512260;
        }
        // 0x00512268
        charge(ctx, 3);
        v0 = sltiu(v0, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00512274
            charge(ctx, 4);
            lbu(v0, sp, 0x66);
            v0 = sltiu(v0, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x00512284
                charge(ctx, 12);
                lbu(a1, sp, 0x7C);
                lbu(v1, sp, 0x7B);
                lbu(a0, sp, 0x7A);
                a1 = dsll(a1, 24);
                lbu(v0, sp, 0x79);
                v1 = dsll(v1, 16);
                a0 = dsll(a0, 8);
                v0 = v0 + a1;
                v1 = v1 + a0;
                v0 = v0 + v1;
                v0 = dsll32(v0, 0);
                v0 = dsra32(v0, 0);
            }
        }
        // 0x005122b4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x80);
        sp = addiu(sp, 0x90);
        return;
    }
L_00512260:
    charge(ctx, 2);
    v0 = 0;
    // 0x005122b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0x90);
}

// 0x00512370 scePadInfoPressMode -- 128 bytes; frame 0x90: ra sp+0x80
// 1 when the pad reports pressure-sensitive buttons (+102 bit 1) in extended mode, else 0.
void scePadInfoPressMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512370
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x90);
    v0 = 0x970000;
    sd(ra, sp, 0x80);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x005123a8
        charge(ctx, 6);
        a2 = sp;
        jal(ctx, 0x5123A8u, gen::fn_scePadGetDmaStr_00511830);
        lbu(v1, sp, 0x72);
        v0 = 1;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        lbu(v0, sp, 0x64);
        if (!cc) {
            goto L_005123c0;
        }
        // 0x005123c8
        charge(ctx, 3);
        v0 = sltiu(v0, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x005123d4
            charge(ctx, 4);
            lbu(v0, sp, 0x66);
            v0 = v0 & 0x2;
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                backedge(ctx);
                goto L_005123c0;
            }
        }
        // 0x005123e4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x80);
        sp = addiu(sp, 0x90);
        return;
    }
L_005123c0:
    charge(ctx, 2);
    v0 = 0;
    // 0x005123e4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0x90);
}

// 0x005123F0 scePadEnterPressMode -- 84 bytes; frame 0x10: ra sp+0x0
// Turn the pressure-sensitive buttons on (scePadSetButtonInfo with the 12-button mask 0xFFF) for an open port; 0
// otherwise.
void scePadEnterPressMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005123f0
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x10);
    v0 = 0x970000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x00512430
        charge(ctx, 2);
        a2 = 4095;
        jal(ctx, 0x512430u, gen::fn_scePadSetButtonInfo_005122c0);
    } else {
        // 0x00512428
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00512438 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00512448 scePadExitPressMode -- 84 bytes; frame 0x10: ra sp+0x0
// Turn the pressure-sensitive buttons off (scePadSetButtonInfo with mask 0) for an open port; 0 otherwise.
void scePadExitPressMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00512448
    enter(ctx, 14);  // entry check point + this block's cycles
    a2 = a0;
    v1 = 112;
    a0 = 28;
    mult1(v1, a2, v1);
    mult(a0, a1, a0);
    sp = addiu(sp, -0x10);
    v0 = 0x970000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -8944);  // &0x96DD10
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    a0 = a2;
    if (v1 != 0) {
        // 0x00512488
        charge(ctx, 2);
        a2 = 0;
        jal(ctx, 0x512488u, gen::fn_scePadSetButtonInfo_005122c0);
    } else {
        // 0x00512480
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00512490 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00512838 scePadSetFlushRate -- 48 bytes; leaf frame (no stack)
// Set the pad flush rate (0x782754): accepts 0 or a value in 16675..66675; returns 1 when set, 0 (unchanged)
// otherwise.
void scePadSetFlushRate(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00512838
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0xC348;
    v1 = addiu(a0, -16675);
    v0 = sltu(v0, v1);
    v1 = 0x780000;
    if (v0 == 0) {
        // 0x0051285c
        charge(ctx, 1);
        v0 = 1;
        // 0x00512860 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(a0, v1, 10068);
        return;
    }
    // 0x0051284c
    charge(ctx, 2);
    v0 = 1;
    if (a0 == 0) {
        // 0x00512860 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(a0, v1, 10068);
        return;
    }
    // 0x00512854
    charge(ctx, 2);
    v0 = 0;
}

}  // namespace p3fes::game
