// Two small EE-side managers of the kernel / sound libraries: the timer alarms' counter operations
// (0x50E850-0x50F358, on sce1's alarm pool: records at (id >> 10) << 6 with a 10-bit tag; the timer itself --
// sub_50E508 reads it, sub_50E000 programs the compare -- stays recompiled) and the SPU2 memory manager sceSpu2Mem*
// (0x51D5B0-0x51D908: a caller table of 12-byte blocks, all bookkeeping on the EE; sceSpu2MemAllocate stays
// recompiled: test_field8_sys stands it in).
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass (scratch spec.py, checked by check.py) adds the
// role comments and the named offsets of game/include/p3fes/game/libs1_kernel.h, each equal to the literal it replaces.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs1_kernel.h"

namespace p3fes::recomp_gen {
void fn_bzero_0051e118(p3fes::EEContext&);
void fn_iReleaseTimerAlarm_0050f358(p3fes::EEContext&);
void fn_iSetTimerAlarm_0050f1c0(p3fes::EEContext&);
void fn_sceSpu2MemFree_0051d908(p3fes::EEContext&);
void fn_sceSpu2MemInit_0051d5b0(p3fes::EEContext&);
void fn_sceSpu2MemQuit_0051d6b0(p3fes::EEContext&);
void fn_sub_50E000_0050e000(p3fes::EEContext&);
void fn_sub_50E190_0050e190(p3fes::EEContext&);
void fn_sub_50E218_0050e218(p3fes::EEContext&);
void fn_sub_50E508_0050e508(p3fes::EEContext&);
void fn_sub_50E5D8_0050e5d8(p3fes::EEContext&);
void fn_sub_50E690_0050e690(p3fes::EEContext&);
void fn_sub_50E850_0050e850(p3fes::EEContext&);
void fn_sub_50E950_0050e950(p3fes::EEContext&);
void fn_sub_50EBE8_0050ebe8(p3fes::EEContext&);
void fn_sub_50ECA8_0050eca8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0050E850 sub_50E850 -- 172 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x10
// Start a counter: valid id (tag), not the running handler's; when stopped, stamps the start time and sets the
// running bit, and an armed alarm goes back into the pending list (the timer reprogrammed). [StartTimerCounter]
void sub_50E850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050e850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = srl(a0, 10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s0 = sll(v0, 6);
    sd(s1, sp, 0x10);
    if (i64(a0) >= 0) {
        // 0x0050e86c
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = a0 & 0x3FF;
        if (v0 != v1) {
            goto L_0050e87c;
        }
        v0 = 0x780000;
        // 0x0050e888
        charge(ctx, 4);
        v0 = addiu(v0, 2888);
        lw(v1, v0, 28);
        if (v1 != a0) {
            lw(v0, s0, 12);
            // 0x0050e8a4
            charge(ctx, 3);
            v0 = v0 & 0x1;
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x0050e8b0
                charge(ctx, 9);
                jal(ctx, 0x50E8B0u, gen::fn_sub_50E508_0050e508);
                s1 = v0;
                lw(v0, s0, 12);
                sd(s1, s0, 16);
                v0 = v0 | 0x1;
                v1 = v0 & 0x2;
                sw(v0, s0, 12);
                if (v1 != 0) {
                    // 0x0050e8d4
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x50E8D4u, gen::fn_sub_50E190_0050e190);
                    a0 = s1;
                    jal(ctx, 0x50E8DCu, gen::fn_sub_50E000_0050e000);
                }
                // 0x0050e8e4
                charge(ctx, 1);
                v0 = 0;
            }
        } else {
            // 0x0050e898
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x10;
        }
        // 0x0050e8e8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0050e87c:
    charge(ctx, 3);
    v0 = lui(0x8000);
    v0 = v0 | 0x8002;
    // 0x0050e8e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050E950 sub_50E950 -- 220 bytes; frame 0x40: s0 sp+0x0, ra sp+0x30, s2 sp+0x20, s1 sp+0x10
// Stop a counter: adds the elapsed time to its total, clears the running bit, takes an armed alarm off the pending
// list. [StopTimerCounter]
void sub_50E950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050e950
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = srl(a0, 10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s0 = sll(v0, 6);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    if (i64(a0) >= 0) {
        // 0x0050e970
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = a0 & 0x3FF;
        if (v0 != v1) {
            goto L_0050e980;
        }
        v0 = 0x780000;
        // 0x0050e98c
        charge(ctx, 4);
        s1 = addiu(v0, 2888);
        lw(v1, s1, 28);
        if (v1 != a0) {
            lw(v0, s0, 12);
            // 0x0050e9a8
            charge(ctx, 3);
            v0 = v0 & 0x1;
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x0050e9b4
                charge(ctx, 15);
                jal(ctx, 0x50E9B4u, gen::fn_sub_50E508_0050e508);
                lw(a1, s0, 12);
                s2 = v0;
                ld(a0, s0, 16);
                v0 = lui(0xFFFF);
                ld(v1, s0, 24);
                v0 = v0 | 0xFFFE;
                a0 = s2 - a0;
                a2 = a1 & 0x2;
                v1 = v1 + a0;
                a1 = a1 & v0;
                sd(v1, s0, 24);
                sw(a1, s0, 12);
                if (a2 != 0) {
                    // 0x0050e9f0
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x50E9F0u, gen::fn_sub_50E218_0050e218);
                    v1 = v0;
                    lw(v0, s1, 32);
                    if (v0 == s0) {
                        sw(v1, s1, 32);
                    }
                    // 0x0050ea08
                    charge(ctx, 2);
                    a0 = s2;
                    jal(ctx, 0x50EA08u, gen::fn_sub_50E000_0050e000);
                }
                // 0x0050ea10
                charge(ctx, 1);
                v0 = 1;
            }
        } else {
            // 0x0050e99c
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x10;
        }
        // 0x0050ea14 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_0050e980:
    charge(ctx, 3);
    v0 = lui(0x8000);
    v0 = v0 | 0x8002;
    // 0x0050ea14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050EBE8 sub_50EBE8 -- 108 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// A counter's total time, including the running stretch. [GetTimerCounterTime]
void sub_50EBE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050ebe8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = srl(a0, 10);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = sll(v0, 6);
    sd(s0, sp, 0x0);
    if (i64(a0) >= 0) {
        // 0x0050ec04
        charge(ctx, 4);
        lw(v1, s1, 8);
        v0 = a0 & 0x3FF;
        if (v0 != v1) {
            goto L_0050ec14;
        }
        lw(v0, s1, 12);
        // 0x0050ec1c
        charge(ctx, 3);
        v0 = v0 & 0x1;
        ld(s0, s1, 24);
        if (v0 != 0) {
            // 0x0050ec28
            charge(ctx, 5);
            jal(ctx, 0x50EC28u, gen::fn_sub_50E508_0050e508);
            ld(v1, s1, 16);
            v0 = v0 - v1;
            s0 = s0 + v0;
        }
        // 0x0050ec3c
        charge(ctx, 1);
        v0 = s0;
        // 0x0050ec40 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0050ec14:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x0050ec40 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050ECA8 sub_50ECA8 -- 268 bytes; frame 0x60: s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s0 sp+0x0, ra sp+0x50, s1 sp+0x10
// Arm or disarm a counter's alarm (target time, handler, argument, the caller's $gp) and reprogram the timer.
// [SetTimerCounterHandler]
void sub_50ECA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050eca8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = srl(a0, 10);
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    s4 = a3;
    sd(s2, sp, 0x20);
    s3 = a1;
    sd(s0, sp, 0x0);
    s2 = a2;
    sd(ra, sp, 0x50);
    s0 = sll(v0, 6);
    sd(s1, sp, 0x10);
    if (i64(a0) >= 0) {
        // 0x0050ecdc
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = a0 & 0x3FF;
        if (v0 != v1) {
            goto L_0050ecec;
        }
        v0 = 0x780000;
        // 0x0050ecf8
        charge(ctx, 4);
        s1 = addiu(v0, 2888);
        lw(v1, s1, 28);
        if (v1 != a0) {
            lw(v1, s0, 12);
            // 0x0050ed14
            charge(ctx, 3);
            v0 = v1 & 0x2;
            if (v0 != 0) {
                // 0x0050ed20
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x50ED20u, gen::fn_sub_50E218_0050e218);
                v1 = v0;
                lw(v0, s1, 32);
                if (v0 == s0) {
                    sw(v1, s1, 32);
                }
                // 0x0050ed38
                charge(ctx, 1);
                lw(v1, s0, 12);
            }
            // 0x0050ed3c
            charge(ctx, 2);
            sw(s2, s0, 40);
            if (s2 != 0) {
                // 0x0050ed58
                charge(ctx, 8);
                v0 = v1 | 0x2;
                sd(s3, s0, 32);
                sw(v0, s0, 12);
                sw(gp, s0, 44);
                lw(v0, s0, 12);
                v0 = v0 & 0x1;
                sw(s4, s0, 48);
                if (v0 != 0) {
                    // 0x0050ed78
                    charge(ctx, 2);
                    a0 = s0;
                    jal(ctx, 0x50ED78u, gen::fn_sub_50E190_0050e190);
                }
            } else {
                // 0x0050ed44
                charge(ctx, 5);
                v0 = lui(0xFFFF);
                v0 = v0 | 0xFFFD;
                v0 = v1 & v0;
                sw(v0, s0, 12);
            }
            // 0x0050ed80
            charge(ctx, 5);
            jal(ctx, 0x50ED80u, gen::fn_sub_50E508_0050e508);
            a0 = v0;
            jal(ctx, 0x50ED88u, gen::fn_sub_50E000_0050e000);
            v0 = 0;
        } else {
            // 0x0050ed08
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x10;
        }
        // 0x0050ed94 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        ld(s4, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_0050ecec:
    charge(ctx, 3);
    v0 = lui(0x8000);
    v0 = v0 | 0x8002;
    // 0x0050ed94 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0050F1C0 iSetTimerAlarm -- 240 bytes; frame 0x70: s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, ra sp+0x60, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// Interrupt-context alarm: takes an alarm record from the free list, allocates a counter, arms it with AlarmHandler
// and starts it; returns record << 4 | tag | 1, or an error.
void iSetTimerAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f1c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    s5 = a0;
    sd(s3, sp, 0x30);
    s4 = a2;
    sd(ra, sp, 0x60);
    s3 = a1;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (s3 == 0) {
        // 0x0050f1f0
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x16;
        goto L_0050f28c;
    }
    // 0x0050f1fc
    charge(ctx, 4);
    s2 = 0x970000;
    lw(s0, s2, -10304);  // 0x96D7C0
    if (s0 != 0) {
        // 0x0050f20c
        charge(ctx, 2);
        lw(v0, s0, 0);
        sw(v0, s2, -10304);
    }
    // 0x0050f214
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0050f21c
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x8005;
        goto L_0050f28c;
    }
    // 0x0050f228
    charge(ctx, 5);
    jal(ctx, 0x50F228u, gen::fn_sub_50E5D8_0050e5d8);
    s1 = v0;
    if (i64(s1) >= 0) {
        sw(s3, s0, 8);
        // 0x0050f254
        charge(ctx, 14);
        a2 = 0x510000;
        sw(s4, s0, 12);
        a2 = addiu(a2, -4048);  // &AlarmHandler
        sw(s1, s0, 4);
        a1 = s5;
        a0 = s1;
        a3 = s0;
        jal(ctx, 0x50F26Cu, gen::fn_sub_50ECA8_0050eca8);
        a0 = s1;
        jal(ctx, 0x50F274u, gen::fn_sub_50E850_0050e850);
        v0 = sll(s0, 4);
        v1 = s1 & 0xFE;
        v0 = v0 | v1;
        v0 = v0 | 0x1;
    L_0050f28c:
        charge(ctx, 1);
        ld(ra, sp, 0x60);
    } else {
        // 0x0050f23c
        charge(ctx, 6);
        lw(v1, s2, -10304);
        sw(s0, s2, -10304);
        sw(v1, s0, 0);
        sw(zero, s0, 4);
        ld(ra, sp, 0x60);
    }
    // 0x0050f290 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0050F358 iReleaseTimerAlarm -- 120 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// Interrupt-context release: frees the alarm's counter and returns its record to the free list.
void iReleaseTimerAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f358
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = srl(a0, 8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = sll(v0, 4);
    if (i64(a0) >= 0) {
        // 0x0050f370
        charge(ctx, 5);
        lw(v0, s0, 4);
        v0 = a0 ^ v0;
        v0 = v0 & 0xFF;
        if (v0 != 0) {
            goto L_0050f384;
        }
        // 0x0050f390
        charge(ctx, 6);
        lw(a0, s0, 4);
        jal(ctx, 0x50F394u, gen::fn_sub_50E690_0050e690);
        a0 = v0;
        v0 = a0;
        if (a0 == 0) {
            // 0x0050f3a8
            charge(ctx, 6);
            v0 = 0x970000;
            lw(v1, v0, -10304);  // 0x96D7C0
            sw(s0, v0, -10304);  // 0x96D7C0
            sw(v1, s0, 0);
            sw(zero, s0, 4);
            v0 = a0;
        }
        // 0x0050f3c0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0050f384:
    charge(ctx, 3);
    v0 = lui(0x8000);
    v0 = v0 | 0x8002;
    // 0x0050f3c0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0051D5B0 sceSpu2MemInit -- 252 bytes; frame 0x50: s1 sp+0x10, s2 sp+0x20, ra sp+0x40, s3 sp+0x30, s0 sp+0x0
// Set up the SPU2 memory manager over a caller table of N + 1 entries: one free block from 0x5010 (after the reserved
// area) to the end of SPU2 RAM (1.75 MiB, or 2 MiB with the flag).
void sceSpu2MemInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051d5b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a1 = addiu(a1, 1);
    sd(s1, sp, 0x10);
    v0 = a0;
    sd(s2, sp, 0x20);
    s1 = 0x780000;
    sw(a1, s1, 11044);  // 0x782B24
    s2 = 0x780000;
    sd(ra, sp, 0x40);
    sd(s3, sp, 0x30);
    sd(s0, sp, 0x0);
    sw(a2, s2, 11048);  // 0x782B28
    if (v0 != 0) {
        // 0x0051d5ec
        charge(ctx, 20);
        lw(a1, s1, 11044);
        s3 = 12;
        s0 = 0x780000;
        a0 = v0;
        mult(zero, a1, s3);
        mflo(a1);
        link(ctx, 0x51D604u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 11032);  // 0x782B18
        call(ctx, gen::fn_bzero_0051e118);
        lw(t1, s0, 11032);  // 0x782B18
        v0 = lui(0x8000);
        v0 = v0 | 0x5010;
        a0 = 0x780000;
        sw(v0, t1, 0);
        v1 = 0x1C0000;
        sw(v1, a0, 11056);  // 0x782B30
        t0 = 0x1B0000;
        t0 = t0 | 0xAFF0;  // "-0"
        lw(v0, s2, 11048);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x200000;
        if (!cc) {
            // 0x0051d63c
            charge(ctx, 3);
            t0 = 0x1F0000;
            sw(v0, a0, 11056);
            t0 = t0 | 0xAFF0;  // &0x1FAFF0
        }
        // 0x0051d648
        charge(ctx, 18);
        sw(t0, t1, 4);
        v0 = 0x780000;
        sw(t0, v0, 11052);  // 0x782B2C
        a1 = 0x780000;
        v0 = addiu(a1, 11064);  // &0x782B38
        a2 = 0x780000;
        lw(v1, s1, 11044);
        a3 = 0x780000;
        sw(t0, v0, 4);  // 0x782B3C
        a0 = 20496;
        mult(v1, v1, s3);
        sw(a0, a1, 11064);  // 0x782B38
        sw(t1, a2, 11036);  // 0x782B1C
        v0 = 0;
        sw(zero, t1, 8);
        v1 = addiu(v1, -12);
        v1 = addu(t1, v1);
        sw(v1, a3, 11040);  // 0x782B20
    } else {
        // 0x0051d5e4
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0051d690 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0051D6B0 sceSpu2MemQuit -- 72 bytes; frame 0x10: ra sp+0x0
// Clear the block table.
void sceSpu2MemQuit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051d6b0
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = 0x780000;
    a2 = 12;
    lw(a1, v1, 11044);  // 0x782B24
    v0 = 0x780000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 11032);  // 0x782B18
    mult(zero, a1, a2);
    sd(ra, sp, 0x0);
    mflo(a1);
    jal(ctx, 0x51D6D0u, gen::fn_bzero_0051e118);
    v0 = 0x780000;
    v1 = 0x780000;
    sw(zero, v0, 11040);  // 0x782B20
    ld(ra, sp, 0x0);
    v0 = 0;
    sw(zero, v1, 11036);  // 0x782B1C
    sp = addiu(sp, 0x10);
}

// 0x0051D908 sceSpu2MemFree -- 320 bytes; leaf frame (no stack)
// Free a block by address: marks it free, merges it with free neighbours, lowers the top when it was the last block.
void sceSpu2MemFree(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051d908
    enter(ctx, 2);  // entry check point + this block's cycles
    t2 = 0x780000;
    if (a0 != 0) {
        // 0x0051d910
        charge(ctx, 4);
        v1 = lui(0x8000);
        lw(a1, t2, 11032);
        a2 = a1;
        lw(v0, a1, 0);
        for (;;) {
            // 0x0051d920
            charge(ctx, 2);
            if (v0 == a0) {
                goto L_0051d928_3;
            }
            a2 = a1;
            // 0x0051d934
            charge(ctx, 3);
            lw(a1, a1, 8);
            if (a1 != 0) {
                lw(v0, a1, 0);
                backedge(ctx);
                continue;
            }
            break;
        }
    L_0051d940:
        charge(ctx, 2);
        if (a2 != a1) {
            // 0x0051d948
            charge(ctx, 3);
            lw(v0, a2, 0);
            if (i64(v0) < 0) {
                // 0x0051d954
                charge(ctx, 10);
                lw(v0, a2, 4);
                lw(v1, a1, 4);
                lw(a0, a1, 8);
                v0 = addu(v0, v1);
                sw(v0, a2, 4);
                sw(a0, a2, 8);
                sw(zero, a1, 8);
                sw(zero, a1, 4);
                sw(zero, a1, 0);
                a1 = a2;
            }
        }
        // 0x0051d97c
        charge(ctx, 2);
        lw(v1, t2, 11032);
        if (a1 != 0) {
            // 0x0051d984
            charge(ctx, 3);
            lw(a3, a1, 8);
            if (a3 != 0) {
                // 0x0051d990
                charge(ctx, 3);
                lw(v0, a3, 0);
                a2 = a3;
                if (i64(v0) < 0) {
                    // 0x0051d99c
                    charge(ctx, 9);
                    lw(v0, a1, 4);
                    lw(v1, a3, 4);
                    lw(a0, a2, 8);
                    v0 = addu(v0, v1);
                    sw(v0, a1, 4);
                    sw(a0, a1, 8);
                    sw(zero, a2, 8);
                    sw(zero, a3, 4);
                    sw(zero, a3, 0);
                }
            }
            // 0x0051d9c0
            charge(ctx, 2);
            v0 = 0x7FFF0000;
            if (a1 != 0) {
                // 0x0051d9c8
                charge(ctx, 9);
                lw(v1, a1, 0);
                v0 = v0 | 0xFFFF;
                t0 = 0x780000;
                a2 = v1 & v0;
                lw(a3, a1, 4);
                lw(v1, t0, 11064);  // 0x782B38
                v0 = addu(a2, a3);
                t1 = addiu(t0, 11064);  // &0x782B38
                if (v0 == v1) {
                    // 0x0051d9ec
                    charge(ctx, 8);
                    lw(v0, t1, 4);
                    v1 = 0x780000;
                    lw(a0, v1, 11056);  // 0x782B30
                    v0 = addu(a3, v0);
                    sw(v0, a1, 4);
                    a0 = subu(a0, a2);
                    sw(a0, t1, 4);
                    sw(a2, t0, 11064);
                }
            }
            // 0x0051da0c
            charge(ctx, 1);
            lw(v1, t2, 11032);
        }
        // 0x0051da10
        charge(ctx, 3);
        lw(v0, v1, 0);
        if (i64(v0) < 0) {
            // 0x0051da1c
            charge(ctx, 3);
            lw(v0, v1, 8);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0x780000;
            if (!cc) {
                // 0x0051da28
                charge(ctx, 6);
                v1 = 0x780000;
                lw(a1, v0, 11052);
                a0 = addiu(v1, 11064);  // &0x782B38
                v0 = 20496;
                sw(v0, v1, 11064);  // 0x782B38
                sw(a1, a0, 4);  // 0x782B3C
            }
        }
    }
    // 0x0051da40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0051d928_3:
    charge(ctx, 3);
    v0 = v0 | v1;
    sw(v0, a1, 0);
    goto L_0051d940;
}

}  // namespace p3fes::game
