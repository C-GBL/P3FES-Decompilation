// Slice libs3: CRI Sofdec's MPV module (the MPEG video layer): the header decoders, the user-data tags, the pool and
// callbacks, the clip table, the decoder-side hooks; the CRI muldiv, key schedule and descrambler and MWSFD's buffer-
// size helpers that sit before MWSFD's banner.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___env_lock_5_0057b630(p3fes::EEContext&);
void fn___env_unlock_5_0057b638(p3fes::EEContext&);
void fn___errno_11_0056f500(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn_atoi_0051e0f0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_18_0057aef8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_56F570_0056f570(p3fes::EEContext&);
void fn_sub_56F598_0056f598(p3fes::EEContext&);
void fn_sub_56F5C0_0056f5c0(p3fes::EEContext&);
void fn_sub_56F5F0_0056f5f0(p3fes::EEContext&);
void fn_sub_56F640_0056f640(p3fes::EEContext&);
void fn_sub_56F708_0056f708(p3fes::EEContext&);
void fn_sub_56F730_0056f730(p3fes::EEContext&);
void fn_sub_56F758_0056f758(p3fes::EEContext&);
void fn_sub_56F780_0056f780(p3fes::EEContext&);
void fn_sub_56F7B0_0056f7b0(p3fes::EEContext&);
void fn_sub_56F7D8_0056f7d8(p3fes::EEContext&);
void fn_sub_56F800_0056f800(p3fes::EEContext&);
void fn_sub_56F828_0056f828(p3fes::EEContext&);
void fn_sub_574CA8_00574ca8(p3fes::EEContext&);
void fn_sub_5756A0_005756a0(p3fes::EEContext&);
void fn_sub_575880_00575880(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
void fn_sub_578D60_00578d60(p3fes::EEContext&);
void fn_sub_578D60_00578d60_at_00578d80(p3fes::EEContext&);
void fn_sub_578E88_00578e88(p3fes::EEContext&);
void fn_sub_578F10_00578f10(p3fes::EEContext&);
void fn_sub_579078_00579078(p3fes::EEContext&);
void fn_sub_579080_00579080(p3fes::EEContext&);
void fn_sub_5793E0_005793e0(p3fes::EEContext&);
void fn_sub_5793E8_005793e8(p3fes::EEContext&);
void fn_sub_579410_00579410(p3fes::EEContext&);
void fn_sub_579450_00579450(p3fes::EEContext&);
void fn_sub_579660_00579660(p3fes::EEContext&);
void fn_sub_5796D0_005796d0(p3fes::EEContext&);
void fn_sub_579770_00579770(p3fes::EEContext&);
void fn_sub_579818_00579818(p3fes::EEContext&);
void fn_sub_579ED8_00579ed8(p3fes::EEContext&);
void fn_sub_57A158_0057a158(p3fes::EEContext&);
void fn_sub_57A740_0057a740(p3fes::EEContext&);
void fn_sub_57A800_0057a800(p3fes::EEContext&);
void fn_sub_57A8F0_0057a8f0(p3fes::EEContext&);
void fn_sub_57AAB8_0057aab8(p3fes::EEContext&);
void fn_sub_57ABC0_0057abc0(p3fes::EEContext&);
void fn_sub_57AC68_0057ac68(p3fes::EEContext&);
void fn_sub_57ADC0_0057adc0(p3fes::EEContext&);
void fn_sub_57AE90_0057ae90(p3fes::EEContext&);
void fn_sub_57AEE8_0057aee8(p3fes::EEContext&);
void fn_sub_57AEF0_0057aef0(p3fes::EEContext&);
void fn_sub_57AF08_0057af08(p3fes::EEContext&);
void fn_sub_57AFA0_0057afa0(p3fes::EEContext&);
void fn_sub_57B078_0057b078(p3fes::EEContext&);
void fn_sub_57B0F0_0057b0f0(p3fes::EEContext&);
void fn_sub_57B0F8_0057b0f8(p3fes::EEContext&);
void fn_sub_57B100_0057b100(p3fes::EEContext&);
void fn_sub_57B118_0057b118(p3fes::EEContext&);
void fn_sub_57B120_0057b120(p3fes::EEContext&);
void fn_sub_57B138_0057b138(p3fes::EEContext&);
void fn_sub_57B140_0057b140(p3fes::EEContext&);
void fn_sub_57B158_0057b158(p3fes::EEContext&);
void fn_sub_57B1A8_0057b1a8(p3fes::EEContext&);
void fn_sub_57B230_0057b230(p3fes::EEContext&);
void fn_sub_57B278_0057b278(p3fes::EEContext&);
void fn_sub_57B2B0_0057b2b0(p3fes::EEContext&);
void fn_sub_57B2B8_0057b2b8(p3fes::EEContext&);
void fn_sub_57B368_0057b368(p3fes::EEContext&);
void fn_sub_57B418_0057b418(p3fes::EEContext&);
void fn_sub_57B440_0057b440(p3fes::EEContext&);
void fn_sub_57B498_0057b498(p3fes::EEContext&);
void fn_sub_57B4E8_0057b4e8(p3fes::EEContext&);
void fn_sub_57B5B0_0057b5b0(p3fes::EEContext&);
void fn_sub_57B5C8_0057b5c8(p3fes::EEContext&);
void fn_sub_57B640_0057b640(p3fes::EEContext&);
void fn_sub_57B648_0057b648(p3fes::EEContext&);
void fn_sub_57B710_0057b710(p3fes::EEContext&);
void fn_sub_57B760_0057b760(p3fes::EEContext&);
void fn_sub_57B7F0_0057b7f0(p3fes::EEContext&);
void fn_sub_57B818_0057b818(p3fes::EEContext&);
void fn_sub_57B830_0057b830(p3fes::EEContext&);
void fn_sub_57B860_0057b860(p3fes::EEContext&);
void fn_sub_57B878_0057b878(p3fes::EEContext&);
void fn_sub_57B890_0057b890(p3fes::EEContext&);
void fn_sub_57B8A8_0057b8a8(p3fes::EEContext&);
void fn_sub_57B8D0_0057b8d0(p3fes::EEContext&);
void fn_sub_57B998_0057b998(p3fes::EEContext&);
void fn_sub_57BAD8_0057bad8(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_57BB60_0057bb60(p3fes::EEContext&);
void fn_sub_57BC10_0057bc10(p3fes::EEContext&);
void fn_sub_57BCB8_0057bcb8(p3fes::EEContext&);
void fn_sub_57BCD8_0057bcd8(p3fes::EEContext&);
void fn_sub_57BD10_0057bd10(p3fes::EEContext&);
void fn_sub_57BD30_0057bd30(p3fes::EEContext&);
void fn_sub_57BD50_0057bd50(p3fes::EEContext&);
void fn_sub_57BF08_0057bf08(p3fes::EEContext&);
void fn_sub_57BF78_0057bf78(p3fes::EEContext&);
void fn_sub_57BF98_0057bf98(p3fes::EEContext&);
void fn_sub_57BFB8_0057bfb8(p3fes::EEContext&);
void fn_sub_57BFC0_0057bfc0(p3fes::EEContext&);
void fn_sub_57C0C0_0057c0c0_at_0057c138(p3fes::EEContext&);
void fn_sub_57C188_0057c188(p3fes::EEContext&);
void fn_sub_57C210_0057c210(p3fes::EEContext&);
void fn_sub_57C270_0057c270(p3fes::EEContext&);
void fn_sub_57C2B0_0057c2b0(p3fes::EEContext&);
void fn_sub_57C398_0057c398(p3fes::EEContext&);
void fn_sub_57C3E8_0057c3e8(p3fes::EEContext&);
void fn_sub_57C4E8_0057c4e8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00578F10 sub_578F10 -- 176 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [mpvDecodeHdrMem0] MPV over a memory buffer (h, {ptr, len}, &used, arg): wraps the buffer in a memory stream joint
// (sub_561970 in the CRI band), runs sub_579078 (tail1: returns -1) on it, reports the bytes used (len minus what is
// left) and destroys the joint. The stream object's methods are called through its vtable (+24 get a chunk, +28 put it
// back, +32 commit, +36 / +12 the memory-stream joint's byte count and destroy) with jalr. No caller.
void sub_578F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00578f10
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(ra, sp, 0x28);
    lw(a1, s3, 4);
    link(ctx, 0x578F40u);  // $ra first: the delay slot below depends on it
    lw(a0, s3, 0);
    call(ctx, gen::fn_sub_561970_00561970);
    a0 = s1;
    s2 = v0;
    v0 = si(-1);
    a2 = s0;
    a1 = s2;
    if (s2 != 0) {
        // 0x00578f60
        charge(ctx, 16);
        jal(ctx, 0x578F60u, gen::fn_sub_579078_00579078);
        lw(v1, s2, 0);
        s0 = v0;
        a0 = s2;
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x578F78u, v0.u());
        lw(v1, s3, 4);
        lw(a1, s2, 0);
        v1 = subu(v1, v0);
        sw(v1, s4, 0);
        lw(v0, a1, 12);
        a0 = s2;
        jalr(ctx, 0x578F94u, v0.u());
        v0 = s0;
    }
    // 0x00578fa0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00579080 sub_579080 -- 184 bytes; frame 0x30: s0 sp+0x0, s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// [mpvSeekPicture] MPV seek to a picture (h, stream): the handle check sub_57B7F0 (tail1); on failure MPV raises
// 0xFF03020A; otherwise scans start codes (sub_57AC68) until one of the classes 0xCC (picture, group, sequence header,
// sequence end) appears -- result 0 -- or the stream runs dry (sub_57AE90 moves on 4 bytes at a time) -- result
// 0xFF030305; the code goes through the handle's error record (sub_578E88).
void sub_579080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00579080
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s3, sp, 0x18);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x57909Cu, gen::fn_sub_57B7F0_0057b7f0);
    ld(s1, sp, 0x8);
    if (v0 != 0) {
        // 0x005790ac
        charge(ctx, 9);
        a1 = lui(0xFF03);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(s2, sp, 0x10);
        a1 = a1 | 0x20A;
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x005790d0
    charge(ctx, 4);
    s1 = lui(0xFF03);
    s2 = 4;
    s1 = s1 | 0x305;
    for (;;) {
        // 0x005790e0
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x5790E0u, gen::fn_sub_57AC68_0057ac68);
        a0 = s0;
        a1 = 1;
        a2 = 4;
        v1 = v0 & 0xCC;
        if (v0 != 0) {
            // 0x005790fc
            charge(ctx, 2);
            if (v1 != 0) {
                s1 = 0;
            } else {
                // 0x00579104
                charge(ctx, 4);
                jal(ctx, 0x579104u, gen::fn_sub_57AE90_0057ae90);
                if (v0 == s2) {
                    backedge(ctx);
                    continue;
                }
            }
        }
        break;
    }
    // 0x00579114
    charge(ctx, 9);
    a0 = s3;
    ld(s3, sp, 0x18);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_578E88_00578e88(ctx);  // tail call
}

// 0x00579450 sub_579450 -- 524 bytes; frame 0x70: s1 sp+0x28, s2 sp+0x30, s0 sp+0x20, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, s7 sp+0x58, fp sp+0x60, ra sp+0x68
// [mpvDecodeHeaders] MPV header decoder (h, stream): the handle check sub_57B7F0 (tail1); on failure MPV raises
// 0xFF03020C; clears +1008, peeks the stream (+24 / +28) to decide MPEG-1 / MPEG-2 (sub_579770); an MPEG-2 stream goes
// to the decoder-side parser (sub_57B8D0); otherwise it loops over start codes (sub_57ADC0) dispatching each header --
// sequence (sub_579818), group (sub_579ED8), picture (sub_57A158), extension (sub_57A740), user data (sub_57A800) --
// through the class test sub_579660, until a slice or an error; errors go through the handle's error record
// (sub_578E88).
void sub_579450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00579450
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(s2, sp, 0x30);
    sd(s0, sp, 0x20);
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(s7, sp, 0x58);
    sd(fp, sp, 0x60);
    sd(ra, sp, 0x68);
    s2 = a0;
    jal(ctx, 0x579480u, gen::fn_sub_57B7F0_0057b7f0);
    a0 = 0;
    if (v0 == 0) {
        // 0x005794a8
        charge(ctx, 25);
        lw(v0, s1, 0);
        a2 = 0x7FFF0000;
        sw(zero, s2, 1008);
        a3 = sp;
        lw(t0, v0, 24);
        a0 = s1;
        a1 = 1;
        a2 = a2 | 0xFFFF;
        jalr(ctx, 0x5794C4u, t0.u());
        lw(v1, s1, 0);
        a0 = s1;
        a1 = 1;
        lw(v0, v1, 28);
        a2 = sp;
        jalr(ctx, 0x5794DCu, v0.u());
        a0 = s2;
        lw(v1, sp, 0x0);
        a1 = addiu(sp, 0x10);
        lw(v0, sp, 0x4);
        sw(v1, sp, 0x10);
        link(ctx, 0x5794F8u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x14);
        call(ctx, gen::fn_sub_579770_00579770);
        v1 = 2;
        s3 = 0;
        if (v0 != v1) {
            // 0x00579530
            charge(ctx, 6);
            s4 = 16;
            s6 = 4;
            fp = 0x8;
            s5 = 32;
            s7 = 64;
            for (;;) {
            L_005795e4:
                charge(ctx, 1);
                a0 = s2;
                for (;;) {
                L_005795e8:
                    charge(ctx, 1);
                    a1 = si(-1);
                    for (;;) {
                        // 0x005795ec
                        charge(ctx, 5);
                        a2 = s1;
                        jal(ctx, 0x5795ECu, gen::fn_sub_57ADC0_0057adc0);
                        s0 = v0;
                        if (s0 != 0) {
                            a0 = s2;
                            backedge(ctx);
                            goto L_00579520;
                        }
                        // 0x00579600
                        charge(ctx, 5);
                        a0 = s1;
                        jal(ctx, 0x579600u, gen::fn_sub_579660_00579660);
                        v1 = v0;
                        v0 = v1 & 0x3;
                        if (v1 == 0) {
                            break;
                        }
                        // 0x00579614
                        charge(ctx, 2);
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = s0;
                        if (cc) {
                            goto L_0057962c;
                        }
                        // 0x0057961c
                        charge(ctx, 3);
                        v0 = v1 & 0x80;
                        s0 = si(-2);
                        if (v0 != 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00579548
                        charge(ctx, 2);
                        a0 = s2;
                        if (v1 == s4) {
                            goto L_005795c0;
                        }
                        // 0x00579550
                        charge(ctx, 3);
                        v0 = slti(v1, 17);
                        if (v0 == 0) {
                            // 0x00579578
                            charge(ctx, 2);
                            a0 = s2;
                            if (v1 == s5) {
                                goto L_005795d8;
                            }
                            // 0x00579580
                            charge(ctx, 2);
                            a1 = si(-1);
                            if (v1 == s7) {
                                goto L_00579588_13;
                            }
                        } else {
                            // 0x0057955c
                            charge(ctx, 2);
                            a1 = s1;
                            if (v1 == s6) {
                                goto L_005795b0;
                            }
                            // 0x00579564
                            charge(ctx, 2);
                            if (v1 == fp) {
                                goto L_005795a0;
                            }
                            // 0x0057956c
                            charge(ctx, 2);
                            a1 = si(-1);
                        }
                    }
                    break;
                }
                break;
            }
            // 0x00579628
            charge(ctx, 1);
            v0 = s0;
        L_0057962c:
            charge(ctx, 1);
            ld(s0, sp, 0x20);
        } else {
            // 0x0057950c
            charge(ctx, 5);
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x579510u, gen::fn_sub_57B8D0_0057b8d0);
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x00579490
        charge(ctx, 5);
        a1 = lui(0xFF03);
        a1 = a1 | 0x20C;
        jal(ctx, 0x579494u, gen::fn_sub_578E88_00578e88);
        ld(s0, sp, 0x20);
    }
    // 0x00579630 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
    return;
L_00579520:
    charge(ctx, 4);
    a1 = s0;
    jal(ctx, 0x579520u, gen::fn_sub_578E88_00578e88);
    ld(s0, sp, 0x20);
    // 0x00579630 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
    return;
L_00579588_13:
    charge(ctx, 6);
    a0 = s2;
    a1 = s1;
    s3 = 64;
    jal(ctx, 0x579590u, gen::fn_sub_579818_00579818);
    a0 = s2;
    goto L_005795e8;
L_005795a0:
    charge(ctx, 4);
    s3 = 8;
    jal(ctx, 0x5795A0u, gen::fn_sub_579ED8_00579ed8);
    a0 = s2;
    goto L_005795e8;
L_005795b0:
    charge(ctx, 4);
    s3 = 4;
    jal(ctx, 0x5795B0u, gen::fn_sub_57A158_0057a158);
    a0 = s2;
    goto L_005795e8;
L_005795c0:
    charge(ctx, 5);
    a1 = s1;
    a2 = s3;
    jal(ctx, 0x5795C4u, gen::fn_sub_57A740_0057a740);
    a0 = s2;
    goto L_005795e8;
L_005795d8:
    charge(ctx, 3);
    a1 = s1;
    a2 = s3;
    jal(ctx, 0x5795DCu, gen::fn_sub_57A800_0057a800);
    goto L_005795e4;
}

// 0x005796D0 sub_5796D0 -- 160 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [mpvDecodeHdrMem] MPV header decoder over a memory buffer (h, {ptr, len}, &used): a memory stream joint (sub_561970),
// sub_579450 on it, the bytes used, the joint destroyed. The stream object's methods are called through its vtable (+24
// get a chunk, +28 put it back, +32 commit, +36 / +12 the memory-stream joint's byte count and destroy) with jalr.
void sub_5796D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005796d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(ra, sp, 0x20);
    lw(a1, s2, 4);
    link(ctx, 0x5796F8u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sub_561970_00561970);
    a0 = s0;
    s1 = v0;
    v0 = si(-1);
    a1 = s1;
    if (s1 != 0) {
        // 0x00579714
        charge(ctx, 16);
        jal(ctx, 0x579714u, gen::fn_sub_579450_00579450);
        lw(v1, s1, 0);
        s0 = v0;
        a0 = s1;
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x57972Cu, v0.u());
        lw(v1, s2, 4);
        lw(a1, s1, 0);
        v1 = subu(v1, v0);
        sw(v1, s3, 0);
        lw(v0, a1, 12);
        a0 = s1;
        jalr(ctx, 0x579748u, v0.u());
        v0 = s0;
    }
    // 0x00579754 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00579818 sub_579818 -- 1728 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// [mpvReadSequenceHeader] MPV sequence header (after 0x000001B3; state +948 = 1): horizontal_size and vertical_size (12
// bits each, into the sequence block +464 / +468), aspect_ratio_information and frame_rate_code (4 bits each),
// bit_rate_value (18 bits), the marker, vbv_buffer_size_value (10 bits), constrained_parameters_flag, then the load
// flags and the 64-byte intra / non-intra quantiser matrices; the bit reader is a 64-bit window over the chunk the
// stream object hands out, and the bytes read are committed (sub_563C28, +32 / +28).
void sub_579818(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00579818
    enter(ctx, 66);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 1;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = addiu(s0, 464);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = addiu(s0, 904);
    sd(ra, sp, 0x30);
    a2 = 0x7FFF0000;
    sw(v0, s0, 948);
    a1 = 1;
    lw(v1, s1, 52);
    a2 = a2 | 0xFFFF;
    lw(a0, s2, 0);
    a3 = s3;
    v1 = addiu(v1, 1);
    sw(v1, s1, 52);
    lw(v0, a0, 24);
    a0 = s2;
    sw(zero, s0, 1016);
    sw(zero, s0, 1020);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x579878u);  // $ra = the return address
    sw(zero, s1, 104);
    call_ptr(ctx, jt);
    lw(v1, s3, 0);
    v0 = si(-4);
    a2 = v1 & v0;
    v1 = subu(v1, a2);
    a2 = addiu(a2, 4);
    lb(a1, a2, 0);
    a2 = addiu(a2, 1);
    lbu(v0, a2, 0);
    a2 = addiu(a2, 1);
    a1 = sll(a1, 8);
    lbu(a0, a2, 0);
    a1 = a1 | v0;
    a2 = addiu(a2, 1);
    a1 = sll(a1, 8);
    lbu(v0, a2, 0);
    a1 = a1 | a0;
    t0 = sll(v1, 3);
    a1 = sll(a1, 8);
    a2 = addiu(a2, 1);
    a1 = a1 | v0;
    v1 = t0 ^ 0x0;
    v0 = sllv(a1, t0);
    a3 = a1;
    lb(a1, a2, 0);
    a2 = addiu(a2, 1);
    if (v1 != 0) a3 = v0;
    lbu(v0, a2, 0);
    a1 = sll(a1, 8);
    a2 = addiu(a2, 1);
    lbu(v1, a2, 0);
    a2 = addiu(a2, 1);
    a1 = a1 | v0;
    lbu(v0, a2, 0);
    a1 = sll(a1, 8);
    a0 = slti(t0, 20);
    a1 = a1 | v1;
    a2 = addiu(a2, 1);
    a1 = sll(a1, 8);
    a1 = a1 | v0;
    if (a0 != 0) {
        // 0x00579990
        charge(ctx, 4);
        v0 = srl(a3, 20);
        a3 = sll(a3, 12);
        sw(v0, s1, 0);
        t0 = addiu(t0, 12);
    } else {
        // 0x00579920
        charge(ctx, 3);
        t0 = addiu(t0, -20);
        v0 = 12;
        if (t0 == 0) {
            // 0x00579948
            charge(ctx, 3);
            v0 = srl(a3, 20);
            a3 = a1;
            sw(v0, s1, 0);
        } else {
            // 0x0057992c
            charge(ctx, 7);
            v0 = subu(v0, t0);
            v0 = srlv(a1, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 20);
            a3 = sllv(a1, t0);
            sw(v1, s1, 0);
        }
        // 0x00579954
        charge(ctx, 15);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x005799a0
    charge(ctx, 3);
    v0 = slti(t0, 20);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(a3, 20);
    if (cc) {
        // 0x00579a20
        charge(ctx, 3);
        a3 = sll(a3, 12);
        sw(v0, s1, 4);
        t0 = addiu(t0, 12);
    } else {
        // 0x005799ac
        charge(ctx, 3);
        t0 = addiu(t0, -20);
        v0 = 12;
        if (t0 == 0) {
            // 0x005799d8
            charge(ctx, 3);
            v0 = srl(a3, 20);
            a3 = a1;
            sw(v0, s1, 4);
        } else {
            // 0x005799b8
            charge(ctx, 7);
            v0 = subu(v0, t0);
            v0 = srlv(a1, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 20);
            a3 = sllv(a1, t0);
            sw(v1, s1, 4);
        }
        // 0x005799e4
        charge(ctx, 15);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579a2c
    charge(ctx, 3);
    v0 = slti(t0, 28);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(a3, 28);
    if (cc) {
        // 0x00579aa8
        charge(ctx, 3);
        a3 = sll(a3, 4);
        sw(v0, s0, 676);
        t0 = addiu(t0, 4);
    } else {
        // 0x00579a38
        charge(ctx, 3);
        t0 = addiu(t0, -28);
        v0 = 4;
        if (t0 == 0) {
            // 0x00579a60
            charge(ctx, 3);
            v0 = srl(a3, 28);
            a3 = a1;
            sw(v0, s0, 676);
        } else {
            // 0x00579a44
            charge(ctx, 7);
            v0 = subu(v0, t0);
            v0 = srlv(a1, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 28);
            a3 = sllv(a1, t0);
            sw(v1, s0, 676);
        }
        // 0x00579a6c
        charge(ctx, 15);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579ab4
    charge(ctx, 3);
    v0 = slti(t0, 28);
    a0 = srl(a3, 28);
    if (v0 != 0) {
        // 0x00579b28
        charge(ctx, 2);
        a3 = sll(a3, 4);
        t0 = addiu(t0, 4);
    } else {
        // 0x00579ac0
        charge(ctx, 3);
        t0 = addiu(t0, -28);
        v0 = 4;
        if (t0 == 0) {
            // 0x00579ae8
            charge(ctx, 1);
            a3 = a1;
        } else {
            // 0x00579acc
            charge(ctx, 6);
            v0 = subu(v0, t0);
            v0 = srlv(a1, v0);
            a3 = a3 | v0;
            a0 = srl(a3, 28);
            a3 = sllv(a1, t0);
        }
        // 0x00579aec
        charge(ctx, 15);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579b30
    charge(ctx, 3);
    v0 = slti(t0, 14);
    sw(a0, s1, 16);
    if (v0 != 0) {
        // 0x00579bb0
        charge(ctx, 4);
        v0 = srl(a3, 14);
        a3 = sll(a3, 18);
        sw(v0, s0, 680);
        t0 = addiu(t0, 18);
    } else {
        // 0x00579b3c
        charge(ctx, 3);
        t0 = addiu(t0, -14);
        v0 = 18;
        if (t0 == 0) {
            // 0x00579b68
            charge(ctx, 3);
            v0 = srl(a3, 14);
            a3 = a1;
            sw(v0, s0, 680);
        } else {
            // 0x00579b48
            charge(ctx, 7);
            v0 = subu(v0, t0);
            v0 = srlv(a1, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 14);
            a3 = sllv(a1, t0);
            sw(v1, s0, 680);
        }
        // 0x00579b74
        charge(ctx, 15);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579bc0
    charge(ctx, 4);
    t0 = addiu(t0, 1);
    v0 = slti(t0, 32);
    if (v0 != 0) {
        a3 = sll(a3, 1);
    } else {
        // 0x00579bd0
        charge(ctx, 16);
        t0 = addiu(t0, -32);
        a3 = sllv(a1, t0);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579c10
    charge(ctx, 3);
    v0 = slti(t0, 22);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(a3, 22);
    if (cc) {
        // 0x00579c90
        charge(ctx, 3);
        a3 = sll(a3, 10);
        sw(v0, s0, 684);
        t0 = addiu(t0, 10);
    } else {
        // 0x00579c1c
        charge(ctx, 3);
        t0 = addiu(t0, -22);
        v0 = 10;
        if (t0 == 0) {
            // 0x00579c48
            charge(ctx, 3);
            v0 = srl(a3, 22);
            a3 = a1;
            sw(v0, s0, 684);
        } else {
            // 0x00579c28
            charge(ctx, 7);
            v0 = subu(v0, t0);
            v0 = srlv(a1, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 22);
            a3 = sllv(a1, t0);
            sw(v1, s0, 684);
        }
        // 0x00579c54
        charge(ctx, 15);
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579c9c
    charge(ctx, 4);
    v0 = srl(a3, 31);
    v1 = 31;
    sw(v0, s0, 688);
    if (t0 != v1) {
        // 0x00579cf0
        charge(ctx, 2);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 1);
    } else {
        // 0x00579cac
        charge(ctx, 17);
        a3 = a1;
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        t0 = 0;
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579cf8
    charge(ctx, 3);
    v0 = 31;
    a0 = srl(a3, 31);
    if (t0 != v0) {
        // 0x00579d48
        charge(ctx, 2);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 1);
    } else {
        // 0x00579d04
        charge(ctx, 17);
        a3 = a1;
        lb(a1, a2, 0);
        a2 = addiu(a2, 1);
        t0 = 0;
        lbu(v0, a2, 0);
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v1, a2, 0);
        a1 = a1 | v0;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        lbu(v0, a2, 0);
        a1 = a1 | v1;
        a2 = addiu(a2, 1);
        a1 = sll(a1, 8);
        a1 = a1 | v0;
    }
    // 0x00579d50
    charge(ctx, 2);
    cc = a0 == 0;  // the condition, before the delay slot changes it
    a0 = 63;
    if (!cc) {
        // 0x00579d58
        charge(ctx, 2);
        v0 = slti(t0, 24);
        for (;;) {
            // 0x00579d60
            charge(ctx, 2);
            if (v0 != 0) {
                t0 = addiu(t0, 8);
                // 0x00579db8
                charge(ctx, 1);
                a3 = sll(a3, 8);
            } else {
                // 0x00579d68
                charge(ctx, 20);
                t0 = addiu(t0, -24);
                a3 = a1;
                v1 = sllv(a1, t0);
                lb(a1, a2, 0);
                v0 = t0 ^ 0x0;
                a2 = addiu(a2, 1);
                if (v0 != 0) a3 = v1;
                lbu(v0, a2, 0);
                a1 = sll(a1, 8);
                a2 = addiu(a2, 1);
                lbu(v1, a2, 0);
                a2 = addiu(a2, 1);
                a1 = a1 | v0;
                lbu(v0, a2, 0);
                a1 = sll(a1, 8);
                a2 = addiu(a2, 1);
                a1 = a1 | v1;
                a1 = sll(a1, 8);
                a1 = a1 | v0;
            }
            // 0x00579dbc
            charge(ctx, 3);
            a0 = addiu(a0, -1);
            v0 = slti(t0, 24);
            if (i64(a0) < 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00579dc8
    charge(ctx, 3);
    v0 = 31;
    a0 = srl(a3, 31);
    if (t0 != v0) {
        // 0x00579de0
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    } else {
        // 0x00579dd4
        charge(ctx, 3);
        t0 = 0;
        a2 = addiu(a2, 4);
    }
    // 0x00579de4
    charge(ctx, 2);
    cc = a0 == 0;  // the condition, before the delay slot changes it
    a0 = 63;
    if (!cc) {
        // 0x00579dec
        charge(ctx, 1);
        v0 = slti(t0, 24);
        for (;;) {
            // 0x00579df0
            charge(ctx, 2);
            if (v0 != 0) {
                t0 = addiu(t0, 8);
            } else {
                // 0x00579df8
                charge(ctx, 2);
                t0 = addiu(t0, -24);
                a2 = addiu(a2, 4);
            }
            // 0x00579e00
            charge(ctx, 5);
            a0 = addiu(a0, -1);
            v0 = slti(t0, 24);
            if (i64(a0) < 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00579e14
    charge(ctx, 49);
    lw(v0, s1, 0);
    t0 = addiu(t0, 7);
    lw(v1, s1, 4);
    t0 = sra(t0, 3);
    v0 = addiu(v0, 15);
    t0 = addu(a2, t0);
    v1 = addiu(v1, 15);
    v0 = sra(v0, 4);
    v1 = sra(v1, 4);
    sw(v0, s1, 8);
    mult(v0, v1, v0);
    sw(v1, s1, 12);
    t0 = addiu(t0, -8);
    a3 = sp;
    lw(v1, s0, 680);
    a0 = s3;
    a2 = s3;
    v0 = addiu(v0, -1);
    sw(v0, s0, 832);
    sw(v1, s1, 72);
    lw(v0, s0, 684);
    sw(v0, s1, 76);
    lbu(v1, s0, 676);
    sb(v1, s1, 89);
    lbu(v0, s0, 688);
    sb(v0, s1, 90);
    lw(a1, s0, 904);
    a1 = subu(t0, a1);
    jal(ctx, 0x579E80u, gen::fn_sub_563C28_00563c28);
    lw(v1, s2, 0);
    a2 = s3;
    a0 = s2;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x579E98u, v0.u());
    lw(v1, s2, 0);
    a0 = s2;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x579EB0u, v0.u());
    v0 = 0;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00579ED8 sub_579ED8 -- 636 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// [mpvReadGopHeader] MPV group-of-pictures header (after 0x000001B8; state +948 = 2): the 25-bit time_code, closed_gop
// (+692) and broken_link (+696).
void sub_579ED8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00579ed8
    enter(ctx, 66);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 2;
    sd(s0, sp, 0x10);
    a2 = 0x7FFF0000;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = addiu(s1, 904);
    sd(ra, sp, 0x30);
    s0 = addiu(s1, 464);
    sw(v0, s1, 948);
    a1 = 1;
    lw(v1, s0, 48);
    a2 = a2 | 0xFFFF;
    lw(a0, s2, 0);
    a3 = s3;
    v1 = addiu(v1, 1);
    sw(v1, s0, 48);
    lw(v0, a0, 24);
    a0 = s2;
    sw(zero, s1, 1016);
    sw(zero, s1, 1020);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x579F38u);  // $ra = the return address
    sw(zero, s0, 104);
    call_ptr(ctx, jt);
    lw(v1, s3, 0);
    v0 = si(-4);
    t2 = v1 & v0;
    v1 = subu(v1, t2);
    t2 = addiu(t2, 4);
    lb(t1, t2, 0);
    t2 = addiu(t2, 1);
    lbu(v0, t2, 0);
    t2 = addiu(t2, 1);
    t1 = sll(t1, 8);
    lbu(a0, t2, 0);
    t1 = t1 | v0;
    t2 = addiu(t2, 1);
    t1 = sll(t1, 8);
    lbu(v0, t2, 0);
    t1 = t1 | a0;
    t3 = sll(v1, 3);
    t1 = sll(t1, 8);
    t2 = addiu(t2, 1);
    t1 = t1 | v0;
    v1 = t3 ^ 0x0;
    v0 = sllv(t1, t3);
    t4 = t1;
    lb(t1, t2, 0);
    t2 = addiu(t2, 1);
    if (v1 != 0) t4 = v0;
    lbu(v0, t2, 0);
    t1 = sll(t1, 8);
    t2 = addiu(t2, 1);
    lbu(v1, t2, 0);
    t2 = addiu(t2, 1);
    t1 = t1 | v0;
    lbu(v0, t2, 0);
    t1 = sll(t1, 8);
    a0 = slti(t3, 7);
    t1 = t1 | v1;
    t2 = addiu(t2, 1);
    t1 = sll(t1, 8);
    t1 = t1 | v0;
    if (a0 != 0) {
        // 0x0057a050
        charge(ctx, 3);
        a0 = srl(t4, 7);
        t4 = sll(t4, 25);
        t3 = addiu(t3, 25);
    } else {
        // 0x00579fe0
        charge(ctx, 3);
        t3 = addiu(t3, -7);
        v0 = 25;
        if (t3 == 0) {
            // 0x0057a008
            charge(ctx, 2);
            a0 = srl(t4, 7);
            t4 = t1;
        } else {
            // 0x00579fec
            charge(ctx, 6);
            v0 = subu(v0, t3);
            v0 = srlv(t1, v0);
            t4 = t4 | v0;
            a0 = srl(t4, 7);
            t4 = sllv(t1, t3);
        }
        // 0x0057a010
        charge(ctx, 15);
        lb(t1, t2, 0);
        t2 = addiu(t2, 1);
        lbu(v0, t2, 0);
        t2 = addiu(t2, 1);
        t1 = sll(t1, 8);
        lbu(v1, t2, 0);
        t1 = t1 | v0;
        t2 = addiu(t2, 1);
        t1 = sll(t1, 8);
        lbu(v0, t2, 0);
        t1 = t1 | v1;
        t2 = addiu(t2, 1);
        t1 = sll(t1, 8);
        t1 = t1 | v0;
    }
    // 0x0057a05c
    charge(ctx, 17);
    t0 = a0 & 0x3F;
    a0 = srl(a0, 6);
    a3 = a0 & 0x3F;
    a0 = srl(a0, 7);
    a2 = a0 & 0x3F;
    a0 = srl(a0, 6);
    v0 = srl(a0, 5);
    v1 = a0 & 0x1F;
    a1 = 31;
    a0 = srl(t4, 31);
    sw(v0, s0, 28);
    sw(t0, s0, 44);
    sw(a3, s0, 40);
    sw(a2, s0, 36);
    sw(v1, s0, 32);
    sw(a0, s1, 692);
    if (t3 != a1) {
        // 0x0057a0b0
        charge(ctx, 2);
        t3 = addiu(t3, 1);
        t4 = sll(t4, 1);
    } else {
        // 0x0057a0a0
        charge(ctx, 4);
        t4 = t1;
        t3 = 0;
        t2 = addiu(t2, 4);
    }
    // 0x0057a0b8
    charge(ctx, 4);
    v0 = srl(t4, 31);
    v1 = 31;
    sw(v0, s1, 696);
    if (t3 != v1) {
        // 0x0057a0d8
        charge(ctx, 1);
        t3 = addiu(t3, 1);
    } else {
        // 0x0057a0c8
        charge(ctx, 3);
        t3 = 0;
        t2 = addiu(t2, 4);
    }
    // 0x0057a0dc
    charge(ctx, 30);
    a1 = addiu(t3, 7);
    lw(v0, s1, 904);
    a1 = sra(a1, 3);
    a3 = sp;
    a1 = addu(t2, a1);
    a0 = s3;
    a1 = addiu(a1, -8);
    a2 = s3;
    a1 = subu(a1, v0);
    jal(ctx, 0x57A0FCu, gen::fn_sub_563C28_00563c28);
    lw(v1, s2, 0);
    a2 = s3;
    a0 = s2;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x57A114u, v0.u());
    lw(v1, s2, 0);
    a0 = s2;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x57A12Cu, v0.u());
    v0 = 0;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0057A158 sub_57A158 -- 1512 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// [mpvReadPictureHeader] MPV picture header (after 0x00000100; state +948 = 3): temporal_reference (10 bits, +484),
// picture_coding_type (3 bits, +488), vbv_delay (16 bits, +700), and for P / B pictures full_pel_forward_vector /
// forward_f_code (and the backward pair) with the derived r_size / f / limits (+748.. / +784..).
void sub_57A158(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057a158
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 3;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = addiu(s0, 904);
    sd(ra, sp, 0x28);
    a2 = 0x7FFF0000;
    sw(v0, s0, 948);
    a1 = 1;
    lw(v1, s1, 0);
    a0 = s1;
    a2 = a2 | 0xFFFF;
    lw(v0, v1, 24);
    a3 = s2;
    jalr(ctx, 0x57A198u, v0.u());
    lw(v1, s2, 0);
    v0 = si(-4);
    t1 = addiu(s0, 464);
    t0 = v1 & v0;
    v1 = subu(v1, t0);
    t0 = addiu(t0, 4);
    lb(a2, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    a2 = sll(a2, 8);
    lbu(a0, t0, 0);
    a2 = a2 | v0;
    t0 = addiu(t0, 1);
    a2 = sll(a2, 8);
    lbu(v0, t0, 0);
    a2 = a2 | a0;
    a1 = sll(v1, 3);
    a2 = sll(a2, 8);
    t0 = addiu(t0, 1);
    a2 = a2 | v0;
    v1 = a1 ^ 0x0;
    v0 = sllv(a2, a1);
    a3 = a2;
    lb(a2, t0, 0);
    t0 = addiu(t0, 1);
    if (v1 != 0) a3 = v0;
    lbu(v0, t0, 0);
    a2 = sll(a2, 8);
    t0 = addiu(t0, 1);
    lbu(v1, t0, 0);
    t0 = addiu(t0, 1);
    a2 = a2 | v0;
    lbu(v0, t0, 0);
    a2 = sll(a2, 8);
    a0 = slti(a1, 22);
    a2 = a2 | v1;
    t0 = addiu(t0, 1);
    a2 = sll(a2, 8);
    a2 = a2 | v0;
    if (a0 != 0) {
        // 0x0057a2b8
        charge(ctx, 4);
        v0 = srl(a3, 22);
        a3 = sll(a3, 10);
        sw(v0, t1, 20);
        a1 = addiu(a1, 10);
    } else {
        // 0x0057a244
        charge(ctx, 3);
        a1 = addiu(a1, -22);
        v0 = 10;
        if (a1 == 0) {
            // 0x0057a270
            charge(ctx, 3);
            v0 = srl(a3, 22);
            a3 = a2;
            sw(v0, t1, 20);
        } else {
            // 0x0057a250
            charge(ctx, 7);
            v0 = subu(v0, a1);
            v0 = srlv(a2, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 22);
            a3 = sllv(a2, a1);
            sw(v1, t1, 20);
        }
        // 0x0057a27c
        charge(ctx, 15);
        lb(a2, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        lbu(v1, t0, 0);
        a2 = a2 | v0;
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        lbu(v0, t0, 0);
        a2 = a2 | v1;
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        a2 = a2 | v0;
    }
    // 0x0057a2c8
    charge(ctx, 3);
    v0 = slti(a1, 29);
    a0 = srl(a3, 29);
    if (v0 != 0) {
        // 0x0057a338
        charge(ctx, 2);
        a3 = sll(a3, 3);
        a1 = addiu(a1, 3);
    } else {
        // 0x0057a2d4
        charge(ctx, 3);
        a1 = addiu(a1, -29);
        v0 = 3;
        if (a1 == 0) {
            // 0x0057a2f8
            charge(ctx, 1);
            a3 = a2;
        } else {
            // 0x0057a2e0
            charge(ctx, 6);
            v0 = subu(v0, a1);
            v0 = srlv(a2, v0);
            a3 = a3 | v0;
            a0 = srl(a3, 29);
            a3 = sllv(a2, a1);
        }
        // 0x0057a2fc
        charge(ctx, 15);
        lb(a2, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        lbu(v1, t0, 0);
        a2 = a2 | v0;
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        lbu(v0, t0, 0);
        a2 = a2 | v1;
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        a2 = a2 | v0;
    }
    // 0x0057a340
    charge(ctx, 3);
    v0 = slti(a1, 16);
    sw(a0, t1, 24);
    if (v0 != 0) {
        // 0x0057a3c0
        charge(ctx, 4);
        v0 = srl(a3, 16);
        a3 = sll(a3, 16);
        sw(v0, s0, 700);
        a1 = addiu(a1, 16);
    } else {
        // 0x0057a34c
        charge(ctx, 3);
        a1 = addiu(a1, -16);
        v0 = 16;
        if (a1 == 0) {
            // 0x0057a378
            charge(ctx, 3);
            v0 = srl(a3, 16);
            a3 = a2;
            sw(v0, s0, 700);
        } else {
            // 0x0057a358
            charge(ctx, 7);
            v0 = subu(v0, a1);
            v0 = srlv(a2, v0);
            a3 = a3 | v0;
            v1 = srl(a3, 16);
            a3 = sllv(a2, a1);
            sw(v1, s0, 700);
        }
        // 0x0057a384
        charge(ctx, 15);
        lb(a2, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        lbu(v1, t0, 0);
        a2 = a2 | v0;
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        lbu(v0, t0, 0);
        a2 = a2 | v1;
        t0 = addiu(t0, 1);
        a2 = sll(a2, 8);
        a2 = a2 | v0;
    }
    // 0x0057a3d0
    charge(ctx, 5);
    lw(t2, t1, 24);
    v0 = addiu(t2, -1);
    v0 = sltiu(v0, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    lw(v0, s0, 1016);
    if (cc) {
        // 0x0057a400
        charge(ctx, 7);
        lw(v1, s0, 1020);
        v0 = addiu(v0, -1);
        v1 = addiu(v1, 1);
        v0 = sll(v0, 16);
        v0 = v0 | v1;
        sw(v1, s0, 1020);
        sw(v0, t1, 104);
    } else {
        // 0x0057a3e4
        charge(ctx, 6);
        sw(zero, s0, 1020);
        v0 = addiu(v0, 1);
        v1 = sll(v0, 16);
        sw(v0, s0, 1016);
        sw(v1, t1, 104);
    }
    // 0x0057a41c
    charge(ctx, 4);
    v0 = addiu(t2, -2);
    v0 = sltiu(v0, 2);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (!cc) {
        // 0x0057a42c
        charge(ctx, 5);
        t1 = addiu(s0, 748);
        v0 = srl(a3, 31);
        v1 = 31;
        sw(v0, t1, 0);
        if (a1 != v1) {
            // 0x0057a488
            charge(ctx, 2);
            a1 = addiu(a1, 1);
            a3 = sll(a3, 1);
        } else {
            // 0x0057a440
            charge(ctx, 17);
            a3 = a2;
            lb(a2, t0, 0);
            t0 = addiu(t0, 1);
            a1 = 0;
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v1, t0, 0);
            a2 = a2 | v0;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v0, t0, 0);
            a2 = a2 | v1;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            a2 = a2 | v0;
        }
        // 0x0057a490
        charge(ctx, 3);
        v0 = slti(a1, 29);
        a0 = srl(a3, 29);
        if (v0 != 0) {
            // 0x0057a500
            charge(ctx, 2);
            a3 = sll(a3, 3);
            a1 = addiu(a1, 3);
        } else {
            // 0x0057a49c
            charge(ctx, 3);
            a1 = addiu(a1, -29);
            v0 = 3;
            if (a1 == 0) {
                // 0x0057a4c0
                charge(ctx, 1);
                a3 = a2;
            } else {
                // 0x0057a4a8
                charge(ctx, 6);
                v0 = subu(v0, a1);
                v0 = srlv(a2, v0);
                a3 = a3 | v0;
                a0 = srl(a3, 29);
                a3 = sllv(a2, a1);
            }
            // 0x0057a4c4
            charge(ctx, 15);
            lb(a2, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v1, t0, 0);
            a2 = a2 | v0;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v0, t0, 0);
            a2 = a2 | v1;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            a2 = a2 | v0;
        }
        // 0x0057a508
        charge(ctx, 9);
        a0 = addiu(a0, -1);
        v0 = 27;
        v1 = 1;
        v0 = subu(v0, a0);
        v1 = sllv(v1, a0);
        sw(v0, t1, 8);
        sw(v1, t1, 12);
        sw(a0, t1, 4);
        v0 = 3;
    }
    // 0x0057a52c
    charge(ctx, 2);
    if (t2 != v0) {
        lw(v0, s0, 732);
    } else {
        // 0x0057a534
        charge(ctx, 5);
        t1 = addiu(s0, 784);
        v0 = srl(a3, 31);
        v1 = 31;
        sw(v0, t1, 0);
        if (a1 != v1) {
            // 0x0057a590
            charge(ctx, 2);
            a1 = addiu(a1, 1);
            a3 = sll(a3, 1);
        } else {
            // 0x0057a548
            charge(ctx, 17);
            a3 = a2;
            lb(a2, t0, 0);
            t0 = addiu(t0, 1);
            a1 = 0;
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v1, t0, 0);
            a2 = a2 | v0;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v0, t0, 0);
            a2 = a2 | v1;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            a2 = a2 | v0;
        }
        // 0x0057a598
        charge(ctx, 3);
        v0 = slti(a1, 29);
        a0 = srl(a3, 29);
        if (v0 != 0) {
            // 0x0057a610
            charge(ctx, 2);
            a3 = sll(a3, 3);
            a1 = addiu(a1, 3);
        } else {
            // 0x0057a5a4
            charge(ctx, 3);
            a1 = addiu(a1, -29);
            v0 = 3;
            if (a1 == 0) {
                // 0x0057a5c8
                charge(ctx, 1);
                a3 = a2;
            } else {
                // 0x0057a5b0
                charge(ctx, 6);
                v0 = subu(v0, a1);
                v0 = srlv(a2, v0);
                a3 = a3 | v0;
                a0 = srl(a3, 29);
                a3 = sllv(a2, a1);
            }
            // 0x0057a5cc
            charge(ctx, 15);
            lb(a2, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v1, t0, 0);
            a2 = a2 | v0;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v0, t0, 0);
            a2 = a2 | v1;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            a2 = a2 | v0;
        }
        // 0x0057a618
        charge(ctx, 9);
        a0 = addiu(a0, -1);
        v0 = 27;
        v1 = 1;
        v0 = subu(v0, a0);
        v1 = sllv(v1, a0);
        sw(v0, t1, 8);
        sw(v1, t1, 12);
        sw(a0, t1, 4);
        lw(v0, s0, 732);
    }
    // 0x0057a63c
    charge(ctx, 3);
    sw(v0, s0, 724);
    lw(t1, s0, 904);
    for (;;) {
        // 0x0057a6b8
        charge(ctx, 2);
        if (i64(a3) >= 0) {
            goto L_0057a6c0_49;
        }
        a1 = addiu(a1, 9);
        backedge(ctx);
        // 0x0057a648
        charge(ctx, 3);
        v0 = slti(a1, 32);
        if (v0 != 0) {
            a3 = sll(a3, 9);
        } else {
            // 0x0057a654
            charge(ctx, 16);
            a1 = addiu(a1, -32);
            a3 = sllv(a2, a1);
            lb(a2, t0, 0);
            t0 = addiu(t0, 1);
            lbu(v0, t0, 0);
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v1, t0, 0);
            a2 = a2 | v0;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            lbu(v0, t0, 0);
            a2 = a2 | v1;
            t0 = addiu(t0, 1);
            a2 = sll(a2, 8);
            a2 = a2 | v0;
        }
        // 0x0057a694
        charge(ctx, 9);
        v1 = addiu(a1, 7);
        lw(a0, s0, 908);
        v1 = sra(v1, 3);
        v1 = addu(t0, v1);
        v1 = addiu(v1, -8);
        v1 = subu(v1, t1);
        v1 = slt(v1, a0);
        v0 = si(-3);
        if (v1 != 0) {
            continue;
        }
        break;
    }
    // 0x0057a728 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0057a608:
    charge(ctx, 2);
    t0 = addiu(t0, 4);
L_0057a6d0:
    charge(ctx, 22);
    a1 = addiu(a1, 7);
    a3 = sp;
    a1 = sra(a1, 3);
    a0 = s2;
    a1 = addu(t0, a1);
    a2 = s2;
    a1 = addiu(a1, -8);
    a1 = subu(a1, t1);
    jal(ctx, 0x57A6ECu, gen::fn_sub_563C28_00563c28);
    lw(v1, s1, 0);
    a2 = s2;
    a0 = s1;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x57A704u, v0.u());
    lw(v1, s1, 0);
    a0 = s1;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x57A71Cu, v0.u());
    v0 = 0;
    // 0x0057a728 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0057a6c0_49:
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 == 0) {
        a1 = addiu(a1, -32);
        backedge(ctx);
        goto L_0057a608;
    }
    goto L_0057a6d0;
}

// 0x0057A740 sub_57A740 -- 188 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// [mpvSkipExtension] MPV extension start code: skips the extension (the stream's chunk is committed past the start
// code, sub_563C28) and finds the next start code (sub_57AC68). The stream object's methods are called through its
// vtable (+24 get a chunk, +28 put it back, +32 commit, +36 / +12 the memory-stream joint's byte count and destroy)
// with jalr. Returns 0.
void sub_57A740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057a740
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 0x7FFF0000;
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = addiu(a0, 904);
    sd(ra, sp, 0x20);
    a3 = s1;
    a0 = s0;
    a1 = 1;
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a2 = a2 | 0xFFFF;
    jalr(ctx, 0x57A770u, v0.u());
    lw(v1, s1, 0);
    a1 = si(-4);
    a3 = sp;
    a1 = v1 & a1;
    a0 = s1;
    v0 = subu(v1, a1);
    a2 = s1;
    v0 = sll(v0, 3);
    v0 = sra(v0, 3);
    a1 = addu(a1, v0);
    a1 = addiu(a1, 4);
    a1 = subu(a1, v1);
    jal(ctx, 0x57A7A4u, gen::fn_sub_563C28_00563c28);
    lw(v1, s0, 0);
    a2 = s1;
    a0 = s0;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x57A7BCu, v0.u());
    lw(v1, s0, 0);
    a1 = 1;
    a2 = sp;
    lw(v0, v1, 28);
    a0 = s0;
    jalr(ctx, 0x57A7D4u, v0.u());
    a0 = s0;
    jal(ctx, 0x57A7DCu, gen::fn_sub_57AC68_0057ac68);
    v0 = 0;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057A800 sub_57A800 -- 240 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// [mpvReadUserData] MPV user data (after 0x000001B2): reads the user data up to the next start code (sub_57A8F0),
// commits the chunk and finds the next start code. Returns sub_57A8F0's result.
void sub_57A800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057a800
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = 0x7FFF0000;
    sd(s0, sp, 0x10);
    s0 = si(-4);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = addiu(s1, 904);
    sd(s4, sp, 0x30);
    a3 = s3;
    sd(ra, sp, 0x38);
    a0 = s2;
    a1 = 1;
    lw(v0, s2, 0);
    lw(v1, v0, 24);
    a2 = a2 | 0xFFFF;
    jalr(ctx, 0x57A844u, v1.u());
    lw(a1, s3, 0);
    a0 = s1;
    s0 = a1 & s0;
    lw(a2, a0, 908);
    s1 = subu(a1, s0);
    s0 = addiu(s0, 8);
    s1 = sll(s1, 3);
    jal(ctx, 0x57A864u, gen::fn_sub_57A8F0_0057a8f0);
    s1 = sra(s1, 3);
    lw(a1, s3, 0);
    s0 = addu(s0, s1);
    a3 = sp;
    s0 = addiu(s0, -4);
    a0 = s3;
    a1 = subu(s0, a1);
    a2 = s3;
    s4 = v0;
    jal(ctx, 0x57A88Cu, gen::fn_sub_563C28_00563c28);
    lw(v1, s2, 0);
    a2 = s3;
    a0 = s2;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x57A8A4u, v0.u());
    lw(v1, s2, 0);
    a1 = 1;
    a2 = sp;
    lw(v0, v1, 28);
    a0 = s2;
    jalr(ctx, 0x57A8BCu, v0.u());
    a0 = s2;
    jal(ctx, 0x57A8C4u, gen::fn_sub_57AC68_0057ac68);
    v0 = s4;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0057A8F0 sub_57A8F0 -- 456 bytes; frame 0x70: s2 sp+0x30, s3 sp+0x38, s5 sp+0x48, fp sp+0x60, s0 sp+0x20, s1 sp+0x28, s4 sp+0x40, s6 sp+0x50, s7 sp+0x58, ra sp+0x68
// [mpvCopyUserData] MPV user-data body (h, p, len): finds where the user data ends (the first start code, sub_577FC8);
// after a sequence header (state 1) parses the CRI tags (sub_57AAB8); the row of the header kind just read
// (tail1::mpv::kRows + 12 * state: {stream joint, callback, argument}) gets the bytes written into its stream joint
// (get / commit through the joint's vtable +24 / +32, memcpy, in two pieces when the ring wraps) and then
// callback(argument, state); after a picture header (state 3) the bytes also go into the window (+1000, at most +1004
// bytes, the count in +1008). Returns -1 when no start code ends the data, else 0.
void sub_57A8F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057a8f0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s2, sp, 0x30);
    s2 = 4;
    sd(s3, sp, 0x38);
    s3 = a0;
    sd(s5, sp, 0x48);
    s5 = a1;
    sd(fp, sp, 0x60);
    fp = 0;
    sd(s0, sp, 0x20);
    sd(s1, sp, 0x28);
    sd(s4, sp, 0x40);
    sd(s6, sp, 0x50);
    sd(s7, sp, 0x58);
    sd(ra, sp, 0x68);
    lw(s6, s3, 948);
    s0 = addiu(a2, -3);
    for (;;) {
        // 0x0057a93c
        charge(ctx, 3);
        v0 = slt(s2, s0);
        v1 = s2 ^ s0;
        if (v0 != 0) {
            // 0x0057a948
            charge(ctx, 4);
            a0 = addu(s5, s2);
            jal(ctx, 0x57A948u, gen::fn_sub_577FC8_00577fc8);
            v1 = s2 ^ s0;
            if (v0 == 0) {
                backedge(ctx);
                // 0x0057a938
                charge(ctx, 1);
                s2 = addiu(s2, 1);
                continue;
            }
        }
        break;
    }
    // 0x0057a958
    charge(ctx, 4);
    s7 = si(-1);
    v0 = 1;
    if (v1 != 0) s7 = 0;
    if (s6 == v0) {
        // 0x0057a968
        charge(ctx, 5);
        a0 = s3;
        a1 = s5;
        a2 = s2;
        jal(ctx, 0x57A970u, gen::fn_sub_57AAB8_0057aab8);
        fp = v0;
    }
    // 0x0057a97c
    charge(ctx, 8);
    v0 = sll(s6, 1);
    v0 = addu(v0, s6);
    v0 = sll(v0, 2);
    s4 = addiu(v0, 944);
    v1 = addu(s3, s4);
    lw(s1, v1, 8);
    a3 = sp;
    if (s1 != 0) {
        // 0x0057a99c
        charge(ctx, 20);
        lw(v1, s1, 0);
        a0 = s1;
        a1 = 0;
        lw(v0, v1, 24);
        a2 = s2;
        jalr(ctx, 0x57A9ACu, v0.u());
        a1 = s5;
        lw(a0, sp, 0x0);
        link(ctx, 0x57A9BCu);  // $ra first: the delay slot below depends on it
        lw(a2, sp, 0x4);
        call(ctx, gen::fn_memcpy_00521250);
        lw(v1, s1, 0);
        a0 = s1;
        a1 = 1;
        lw(v0, v1, 32);
        a2 = sp;
        jalr(ctx, 0x57A9D4u, v0.u());
        lw(a0, sp, 0x4);
        v0 = slt(a0, s2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = addu(s3, s4);
        if (!cc) {
            // 0x0057a9ec
            charge(ctx, 20);
            lw(v1, s1, 0);
            s0 = addiu(sp, 0x10);
            a2 = subu(s2, a0);
            a0 = s1;
            lw(v0, v1, 24);
            a1 = 0;
            a3 = s0;
            jalr(ctx, 0x57AA04u, v0.u());
            lw(a1, sp, 0x4);
            lw(a0, sp, 0x10);
            lw(a2, sp, 0x14);
            a1 = addu(s5, a1);
            jal(ctx, 0x57AA18u, gen::fn_memcpy_00521250);
            lw(v1, s1, 0);
            a0 = s1;
            a2 = s0;
            lw(v0, v1, 32);
            a1 = 1;
            jalr(ctx, 0x57AA30u, v0.u());
            v0 = addu(s3, s4);
        }
        // 0x0057aa3c
        charge(ctx, 3);
        lw(v1, v0, 12);
        if (v1 != 0) {
            // 0x0057aa48
            charge(ctx, 3);
            lw(a0, v0, 16);
            a1 = s6;
            jalr(ctx, 0x57AA4Cu, v1.u());
            goto L_0057aa54;
        }
        v0 = 3;
        goto L_0057aa58;
    }
L_0057aa54:
    charge(ctx, 1);
    v0 = 3;
L_0057aa58:
    charge(ctx, 2);
    cc = s6 != v0;  // the condition, before the delay slot changes it
    v0 = fp;
    if (!cc) {
        // 0x0057aa60
        charge(ctx, 3);
        lw(a0, s3, 1000);
        a1 = s5;
        if (a0 != 0) {
            // 0x0057aa6c
            charge(ctx, 6);
            lw(a2, s3, 1004);
            v0 = slt(s2, a2);
            if (v0 != 0) a2 = s2;
            link(ctx, 0x57AA78u);  // $ra first: the delay slot below depends on it
            sw(a2, s3, 1008);
            call(ctx, gen::fn_memcpy_00521250);
            v0 = fp;
        }
    }
    // 0x0057aa84 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(s0, sp, 0x20);
    if (fp == 0) v0 = s7;
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
}

// 0x0057AAB8 sub_57AAB8 -- 260 bytes; frame 0x50: s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s0 sp+0x0, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// [mpvParseUserTags] MPV user-data tags (h, p, len): scans the bytes for "IDCPREC" (atoi of the value 16 bytes on:
// non-zero sets +916 = 3, else 0) and "STCCODE" (three atoi values at +16 / +24 / +32 into +860 / +864 / +868), until a
// start code (sub_577FC8). Returns 0.
void sub_57AAB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057aab8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x18);
    s3 = addiu(a2, -4);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s4, sp, 0x20);
    s4 = addiu(a1, 4);
    sd(s0, sp, 0x0);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    if (i64(s3) > 0) {
        // 0x0057aaf4
        charge(ctx, 5);
        s7 = 0x7C0000;
        s6 = 0x7C0000;
        s5 = 3;
        s0 = addu(s4, s2);
        for (;;) {
            // 0x0057ab08
            charge(ctx, 7);
            s2 = addiu(s2, 1);
            a0 = s0;
            a1 = addiu(s7, 31248);
            a2 = 7;
            jal(ctx, 0x57AB14u, gen::fn_strncmp_00524670);
            a0 = addiu(s0, 16);
            if (v0 == 0) {
                // 0x0057ab24
                charge(ctx, 5);
                jal(ctx, 0x57AB24u, gen::fn_atoi_0051e0f0);
                v1 = 0;
                if (v0 != 0) v1 = s5;
                sw(v1, s1, 916);
            }
            // 0x0057ab38
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(s6, 31256);
            a2 = 7;
            jal(ctx, 0x57AB40u, gen::fn_strncmp_00524670);
            a0 = addiu(s0, 16);
            if (v0 == 0) {
                // 0x0057ab50
                charge(ctx, 9);
                jal(ctx, 0x57AB50u, gen::fn_atoi_0051e0f0);
                a0 = addiu(s0, 24);
                link(ctx, 0x57AB5Cu);  // $ra first: the delay slot below depends on it
                sw(v0, s1, 860);
                call(ctx, gen::fn_atoi_0051e0f0);
                a0 = addiu(s0, 32);
                link(ctx, 0x57AB68u);  // $ra first: the delay slot below depends on it
                sw(v0, s1, 864);
                call(ctx, gen::fn_atoi_0051e0f0);
                sw(v0, s1, 868);
            }
            // 0x0057ab74
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x57AB74u, gen::fn_sub_577FC8_00577fc8);
            v1 = slt(s2, s3);
            if (v0 == 0) {
                // 0x0057ab84
                charge(ctx, 2);
                s0 = addu(s4, s2);
                if (v1 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0057ab8c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0057ABC0 sub_57ABC0 -- 164 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [mpvNextStartCode] MPV start-code step over (&ptr, &len, &count): finds the next start code (sub_578160), advances
// ptr / len / count to it (or to the end) and returns its class (sub_577FC8) or 0. No caller.
void sub_57ABC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057abc0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(ra, sp, 0x20);
    a2 = si(-1);
    lw(a0, s2, 0);
    link(ctx, 0x57ABECu);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 0);
    call(ctx, gen::fn_sub_578160_00578160);
    s0 = v0;
    v0 = 0;
    a0 = s0;
    if (s0 != 0) {
        // 0x0057ac18
        charge(ctx, 5);
        jal(ctx, 0x57AC18u, gen::fn_sub_577FC8_00577fc8);
        lw(a0, s2, 0);
        lw(v1, s1, 0);
        a1 = subu(s0, a0);
    } else {
        // 0x0057ac04
        charge(ctx, 4);
        lw(a1, s1, 0);
        lw(a0, s2, 0);
        v1 = a1;
    }
    // 0x0057ac2c (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v1 = subu(v1, a1);
    a0 = addu(a0, a1);
    sw(v1, s1, 0);
    sw(a0, s2, 0);
    lw(v1, s3, 0);
    ld(s0, sp, 0x0);
    v1 = addu(v1, a1);
    ld(s1, sp, 0x8);
    sw(v1, s3, 0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057ADC0 sub_57ADC0 -- 204 bytes; frame 0x30: s0 sp+0x0, s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// [mpvSeekStartCode] MPV start-code search with a class mask (h, mask, stream): counts a pending picture (+896 -> +900,
// the frame counters +604 / +608; -2 when no decoder is attached at +404), then finds start codes (sub_57AC68) until
// one matches mask (0) or the stream runs dry (sub_57AE90 by 4 bytes; -2, or -3 with a decoder).
void sub_57ADC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057adc0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s1, sp, 0x8);
    a1 = addiu(a0, 592);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(v0, a0, 896);
    lw(a2, a0, 404);
    if (v0 != 0) {
        // 0x0057adf0
        charge(ctx, 8);
        lw(v1, a0, 900);
        sw(zero, a0, 896);
        v1 = addiu(v1, 1);
        sw(v1, a0, 900);
        lw(v0, a1, 12);
        v0 = addiu(v0, 1);
        sw(v0, a1, 12);
        if (a2 != 0) {
            // 0x0057ae18
            charge(ctx, 3);
            lw(v0, a1, 16);
            v0 = addiu(v0, 1);
            sw(v0, a1, 16);
            goto L_0057ae24;
        }
        // 0x0057ae10
        charge(ctx, 2);
        v0 = si(-2);
        // 0x0057ae70 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0057ae24:
    charge(ctx, 5);
    v0 = si(-3);
    s1 = si(-2);
    if (a2 != 0) s1 = v0;
    s2 = 4;
    for (;;) {
        // 0x0057ae38
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x57AE38u, gen::fn_sub_57AC68_0057ac68);
        a0 = s0;
        a1 = 1;
        a2 = 4;
        v1 = v0 & s3;
        if (v0 != 0) {
            // 0x0057ae54
            charge(ctx, 2);
            if (v1 != 0) {
                s1 = 0;
            } else {
                // 0x0057ae5c
                charge(ctx, 4);
                jal(ctx, 0x57AE5Cu, gen::fn_sub_57AE90_0057ae90);
                if (v0 == s2) {
                    backedge(ctx);
                    continue;
                }
            }
        }
        break;
    }
    // 0x0057ae6c
    charge(ctx, 1);
    v0 = s1;
    // 0x0057ae70 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057AEE8 sub_57AEE8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an 8-byte stub; no caller).
void sub_57AEE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057aee8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0057AEF0 sub_57AEF0 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an 8-byte stub; no caller).
void sub_57AEF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057aef0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0057AEF8 sceLibgcc32GetErxEntries_18 -- 12 bytes; leaf frame (no stack)
// [mpvGetVersionStr] Returns MPV's version banner ("CRI MPV/PS2EE Ver.1.958") in $v0. The FLIRT name is a false match
// of a short code shape; the role is read from the instructions.
void sceLibgcc32GetErxEntries_18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057aef8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 31264);  // "\nCRI MPV/PS2EE Ver.1.958 Build:Mar  1 2005 10:54:00\n"
}

// 0x0057AF08 sub_57AF08 -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpvIsMpeg1] MPV probe (buf, len): finds a sequence header (sub_578160, class 64); returns 1 when the decoder-side
// check sub_57B818 says so, else 1 unless the next start code is an extension (class 16: MPEG-2) -- i.e. 1 for MPEG-1
// video. No caller.
void sub_57AF08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057af08
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 64;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x57AF24u, gen::fn_sub_578160_00578160);
    s0 = v0;
    if (s0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0057af38
        charge(ctx, 4);
        jal(ctx, 0x57AF38u, gen::fn_sub_57B818_0057b818);
        s0 = addiu(s0, 4);
        if (v0 == 0) {
            // 0x0057af50
            charge(ctx, 5);
            v1 = subu(s0, s2);
            a0 = s0;
            s1 = subu(s1, v1);
            a1 = s1;
            if (i64(s1) > 0) {
                // 0x0057af64
                charge(ctx, 5);
                a2 = si(-1);
                jal(ctx, 0x57AF64u, gen::fn_sub_578160_00578160);
                s0 = v0;
                a0 = s0;
                if (s0 != 0) {
                    // 0x0057af78
                    charge(ctx, 4);
                    jal(ctx, 0x57AF78u, gen::fn_sub_577FC8_00577fc8);
                    v0 = v0 & 0x10;
                    v0 = sltiu(v0, 1);
                }
            }
        } else {
            // 0x0057af48
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x0057af88
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0057af8c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057AFA0 sub_57AFA0 -- 216 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpvInit] MPV init (n, work): stores the banner at 0x99B2B8, checks the build (sub_57B078; an unexpected error spins
// forever), then the setup chain: sub_57B0F0, the work address (sub_57B0F8), the handle pool (sub_57B2B8), sub_578D60,
// sub_5793E0, the clip table at work + 6,112 (sub_57B158), the handles freed (sub_57B230), sub_57B2B0 and the M2V link
// (sub_57B830). Returns 0.
void sub_57AFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057afa0
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = 0x9A0000;
    v0 = 0x7C0000;
    sp = addiu(sp, -0x20);
    v1 = addiu(v1, -19784);  // &0x99B2B8
    v0 = addiu(v0, 31264);  // "\nCRI MPV/PS2EE Ver.1.958 Build:Mar  1 2005 10:54:00\n"
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    s0 = a1;
    link(ctx, 0x57AFC8u);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 0);
    call(ctx, gen::fn_sub_57B078_0057b078);
    a0 = v0;
    if (a0 == 0) {
        // 0x0057b010
        charge(ctx, 22);
        jal(ctx, 0x57B010u, gen::fn_sub_57B0F0_0057b0f0);
        a0 = s0;
        jal(ctx, 0x57B018u, gen::fn_sub_57B0F8_0057b0f8);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x57B024u, gen::fn_sub_57B2B8_0057b2b8);
        v0 = 0x9A0000;
        link(ctx, 0x57B030u);  // $ra first: the delay slot below depends on it
        lw(s0, v0, -19696);
        call(ctx, gen::fn_sub_578D60_00578d60);
        jal(ctx, 0x57B038u, gen::fn_sub_5793E0_005793e0);
        a0 = addiu(s0, 6112);
        jal(ctx, 0x57B040u, gen::fn_sub_57B158_0057b158);
        jal(ctx, 0x57B048u, gen::fn_sub_57B230_0057b230);
        a0 = s0;
        jal(ctx, 0x57B050u, gen::fn_sub_57B2B0_0057b2b0);
        jal(ctx, 0x57B058u, gen::fn_sub_57B830_0057b830);
        v0 = 0;
        ld(s0, sp, 0x0);
    } else {
        // 0x0057afdc
        charge(ctx, 4);
        v1 = lui(0xFF03);
        v1 = v1 | 0xFF05;
        if (a0 != v1) {
            // 0x0057afec
            charge(ctx, 1);
            for (;;) {
                // 0x0057aff0
                charge(ctx, 7);
                backedge(ctx);
            }
        }
        ld(s0, sp, 0x0);
    }
    // 0x0057b068 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057B078 sub_57B078 -- 116 bytes; frame 0x10: ra sp+0x0
// [mpvCheckBuild] MPV build check: the magic word 0x7C7AB0 must be 0x5A5A5A5A (else error 0xFF03FF02 through
// sub_578E88) and the build word 0x7C7AC0 must be 4 (else a jump to address 0xFFFFFFFF, a deliberate trap). Returns 0.
void sub_57B078(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b078
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v1 = 0x5A5A0000;
    lw(a0, v0, 31408);  // 0x7C7AB0
    sp = addiu(sp, -0x10);
    v1 = v1 | 0x5A5A;
    sd(ra, sp, 0x0);
    if (a0 != v1) {
        // 0x0057b094
        charge(ctx, 6);
        a1 = lui(0xFF03);
        ld(ra, sp, 0x0);
        a0 = 0;
        a1 = a1 | 0xFF02;
        sp = addiu(sp, 0x10);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x0057b0b0
    charge(ctx, 5);
    v0 = 0x7C0000;
    a0 = 4;
    lbu(v1, v0, 31424);  // 0x7C7AC0
    ld(ra, sp, 0x0);
    if (v1 != a0) {
        // 0x0057b0c4
        charge(ctx, 1);
        for (;;) {
            // 0x0057b0c8
            charge(ctx, 5);
            at = si(-1);
            jalr(ctx, 0x57B0CCu, at.u());
            backedge(ctx);
        }
    }
    // 0x0057b0e0
    charge(ctx, 3);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0057B0F0 sub_57B0F0 -- 8 bytes; leaf frame (no stack)
// An empty init step (jr $ra / nop).
void sub_57B0F0(EEContext& ctx) {
    using namespace hg;
    // 0x0057b0f0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0057B0F8 sub_57B0F8 -- 8 bytes; leaf frame (no stack)
// Returns its argument (an init step of MPV: the work address unchanged).
void sub_57B0F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057b0f8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0057B100 sub_57B100 -- 24 bytes; leaf frame (no stack)
// [mpvMapAddressA] Address conversion: a0 | 0x2000000 when the flag 0x99B300 is set, else a0 (sub_57B118 returns it).
// No caller.
void sub_57B100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057b100
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x9A0000;
    lw(v0, v1, -19712);  // 0x99B300
    if (v0 == 0) {
        gen::fn_sub_57B118_0057b118(ctx);  // tail call
        return;
    }
    // 0x0057b110
    charge(ctx, 2);
    v0 = 0x2000000;
    a0 = a0 | v0;
    gen::fn_sub_57B118_0057b118(ctx);  // tail call
}

// 0x0057B118 sub_57B118 -- 8 bytes; leaf frame (no stack)
// Returns its argument (the identity step of sub_57B100).
void sub_57B118(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057b118
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0057B120 sub_57B120 -- 24 bytes; leaf frame (no stack)
// [mpvMapAddressB] Address conversion: a0 | 0x2000000 when the flag 0x99B304 is set, else a0 (via sub_57B138). No
// caller.
void sub_57B120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057b120
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x9A0000;
    lw(v0, v1, -19708);  // 0x99B304
    if (v0 == 0) {
        gen::fn_sub_57B138_0057b138(ctx);  // tail call
        return;
    }
    // 0x0057b130
    charge(ctx, 2);
    v0 = 0x2000000;
    a0 = a0 | v0;
    gen::fn_sub_57B138_0057b138(ctx);  // tail call
}

// 0x0057B138 sub_57B138 -- 8 bytes; leaf frame (no stack)
// Returns its argument (the identity step of sub_57B120).
void sub_57B138(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057b138
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// 0x0057B140 sub_57B140 -- 24 bytes; leaf frame (no stack)
// [mpvToKseg0] Address conversion to KSEG0: (a0 & 0x0FFFFFFF) | 0x80000000 (sign-extended). No caller.
void sub_57B140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057b140
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0xFFF0000;
    v0 = lui(0x8000);
    v1 = v1 | 0xFFFF;
    a0 = a0 & v1;
    v0 = a0 | v0;
}

// 0x0057B158 sub_57B158 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mpvSetupClipTable] MPV clip table (p): builds the 1,024-byte table at 0x7B2A10 (sub_57B1A8); with p non-null copies
// it to p (256 words, sub_5756A0) and points the table word 0x7B2A04 at p + 384 (the table's zero point). Returns that
// address.
void sub_57B158(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b158
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57B164u, gen::fn_sub_57B1A8_0057b1a8);
    a1 = 0x7B0000;
    a0 = s0;
    a1 = addiu(a1, 10768);  // &0x7B2A10
    a2 = 256;
    if (s0 != 0) {
        // 0x0057b180
        charge(ctx, 5);
        jal(ctx, 0x57B180u, gen::fn_sub_5756A0_005756a0);
        v1 = 0x7B0000;
        v0 = addiu(s0, 384);
        sw(v0, v1, 10756);  // 0x7B2A04
    }
    // 0x0057b194 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057B1A8 sub_57B1A8 -- 136 bytes; leaf frame (no stack)
// [mpvBuildClipTable] Fills the clip table at 0x7B2A10: 384 zero bytes, the bytes 0..255, 384 bytes of 255 -- clip(x) =
// table[384 + x] for x in -384..639.
void sub_57B1A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057b1a8
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v1 = 383;
    a0 = addiu(v0, 10768);  // &0x7B2A10
    for (;;) {
        // 0x0057b1b8
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sb(zero, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057b1d4
    charge(ctx, 1);
    v1 = 0;
    for (;;) {
        // 0x0057b1d8
        charge(ctx, 7);
        sb(v1, a0, 0);
        v1 = addiu(v1, 1);
        v0 = slti(v1, 256);
        a0 = addiu(a0, 1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057b1f4
    charge(ctx, 3);
    v0 = si(-1);
    v1 = 383;
    for (;;) {
        // 0x0057b200
        charge(ctx, 7);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057b21c
    charge(ctx, 5);
    v0 = 0x7B0000;
    v1 = 0x7B0000;
    v0 = addiu(v0, 11152);  // &0x7B2B90
    sw(v0, v1, 10756);  // 0x7B2A04
}

// 0x0057B230 sub_57B230 -- 68 bytes; leaf frame (no stack)
// [mpvFreeAllHandles] Marks every MPV handle free (state +392 = 1; pool 0x99B318, count 0x99B314, 1,056-byte stride).
void sub_57B230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057b230
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    v0 = addiu(v0, -19776);  // &0x99B2C0
    lw(a0, v0, 84);  // 0x99B314
    lw(v1, v0, 88);  // 0x99B318
    if (i64(a0) > 0) {
        // 0x0057b244
        charge(ctx, 3);
        v0 = a0;
        a0 = 1;
        for (;;) {
            // 0x0057b250
            charge(ctx, 7);
            v0 = addiu(v0, -1);
            sw(a0, v1, 392);
            v1 = addiu(v1, libs3::mpv::kHandleStride);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0057b26c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057B278 sub_57B278 -- 52 bytes; leaf frame (no stack)
// [mpvAttachTables] Points an MPV handle's table words at the shared work tables (+44 / +48 / +52 = work + 4,384 /
// 4,352 / 4,448; +272 and +64 = the clip table 0x7B2A04).
void sub_57B278(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0057b278
    enter(ctx, 13);  // entry check point + this block's cycles
    v1 = 0x9A0000;
    a2 = 0x7B0000;
    lw(v0, v1, -19696);  // 0x99B310
    a1 = addiu(v0, 4448);
    v1 = addiu(v0, 4384);
    v0 = addiu(v0, 4352);
    sw(v1, a0, 44);
    sw(v0, a0, 48);
    sw(a1, a0, 52);
    lw(v0, a2, 10756);  // 0x7B2A04
    sw(v0, a0, 272);
    sw(v0, a0, 64);
}

// 0x0057B2B0 sub_57B2B0 -- 8 bytes; leaf frame (no stack)
// An empty init step (jr $ra / nop).
void sub_57B2B0(EEContext& ctx) {
    using namespace hg;
    // 0x0057b2b0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0057B2B8 sub_57B2B8 -- 172 bytes; frame 0x30: s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s0 sp+0x0, ra sp+0x28
// [mpvSetupPool] MPV pool layout (n, work): the work aligned up to 64 bytes, 264 * n + 2,048 words cleared
// (sub_575880), the lock hook on the 7,136-byte shared area (__env_lock_5; it starts one 1,056-byte record past the n
// handles), the 16 default callbacks copied from 0x7C7A70 to 0x99B2C0 (sub_5756A0), and the pool words 0x99B30C /
// 0x99B318 / 0x99B310 / 0x99B314.
void sub_57B2B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b2b8
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-64);
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s1, sp, 0x8);
    s1 = sll(s3, 5);
    sd(s2, sp, 0x10);
    s2 = addiu(a1, 63);
    s1 = addu(s1, s3);
    s2 = s2 & v0;
    a2 = sll(s1, 3);
    s1 = sll(s1, 5);
    s1 = addu(s2, s1);
    sd(s4, sp, 0x20);
    a0 = s2;
    a2 = addiu(a2, 2048);
    s4 = addiu(s1, 1056);
    a1 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x28);
    s0 = 0x9A0000;
    jal(ctx, 0x57B308u, gen::fn_sub_575880_00575880);
    a0 = s4;
    a1 = 7136;
    jal(ctx, 0x57B314u, gen::fn___env_lock_5_0057b630);
    a1 = 0x7C0000;
    s0 = addiu(s0, -19776);  // &0x99B2C0
    a1 = addiu(a1, 31344);  // &0x7C7A70
    a0 = s0;
    a2 = 16;
    jal(ctx, 0x57B32Cu, gen::fn_sub_5756A0_005756a0);
    sw(s1, s0, 76);  // 0x99B30C
    sw(s2, s0, 88);  // 0x99B318
    sw(s4, s0, 80);  // 0x99B310
    sw(s3, s0, 84);  // 0x99B314
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0057B368 sub_57B368 -- 176 bytes; leaf frame (no stack)
// [mpvResetSequence] Resets an MPV sequence block (handle + 464): every word cleared, then the defaults (byte +89 = 1,
// +56 = 3, +60 / +64 / +68 = 1, the halfwords +80 / +82 = -1, ...).
void sub_57B368(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0057b368
    enter(ctx, 44);  // entry check point + this block's cycles
    v1 = si(-1);
    a1 = 1;
    v0 = 3;
    sb(a1, a0, 89);
    sw(v0, a0, 56);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    sw(zero, a0, 16);
    sw(zero, a0, 20);
    sw(zero, a0, 24);
    sw(zero, a0, 28);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    sw(zero, a0, 44);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
    sw(a1, a0, 60);
    sw(a1, a0, 64);
    sw(a1, a0, 68);
    sw(zero, a0, 72);
    sw(zero, a0, 76);
    sh(v1, a0, 80);
    sh(v1, a0, 82);
    sb(zero, a0, 84);
    sb(v1, a0, 85);
    sb(v1, a0, 86);
    sb(v1, a0, 87);
    sb(zero, a0, 88);
    sb(zero, a0, 90);
    sb(zero, a0, 91);
    sb(zero, a0, 92);
    sb(v1, a0, 93);
    sb(v1, a0, 94);
    sb(v1, a0, 95);
    sb(v1, a0, 100);
    sw(zero, a0, 104);
    sb(v1, a0, 96);
    sb(zero, a0, 97);
    sb(v1, a0, 98);
    sb(v1, a0, 99);
}

// 0x0057B418 sub_57B418 -- 40 bytes; frame 0x10: ra sp+0x0
// [mpvFinish] MPV finish: the decoder side (sub_57B860) and the unlock hook on the shared area (__env_unlock_5, 7,136
// bytes at 0x99B310).
void sub_57B418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b418
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57B420u, gen::fn_sub_57B860_0057b860);
    v0 = 0x9A0000;
    ld(ra, sp, 0x0);
    lw(a0, v0, -19696);  // 0x99B310
    a1 = 7136;
    sp = addiu(sp, 0x10);
    gen::fn___env_unlock_5_0057b638(ctx);  // tail call
}

// 0x0057B440 sub_57B440 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mpvCreate] MPV create: the first free handle (sub_57B498); the lock hook over its 1,028 bytes, initialisation
// (sub_57B4E8) and its decoder handle (+944, sub_57B878). Returns the handle or 0.
void sub_57B440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b440
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x57B44Cu, gen::fn_sub_57B498_0057b498);
    s0 = v0;
    a1 = 1028;
    a0 = s0;
    if (s0 != 0) {
        // 0x0057b464
        charge(ctx, 9);
        jal(ctx, 0x57B464u, gen::fn___env_lock_5_0057b630);
        a0 = s0;
        jal(ctx, 0x57B46Cu, gen::fn_sub_57B4E8_0057b4e8);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x57B478u, gen::fn_sub_57B878_0057b878);
        sw(v0, s0, 944);
        v0 = s0;
    }
    // 0x0057b488 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057B498 sub_57B498 -- 80 bytes; leaf frame (no stack)
// [mpvFindFreeHandle] The first free MPV handle (state +392 == 1) of the pool, or 0.
void sub_57B498(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0057b498
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    a2 = 0;
    v0 = addiu(v0, -19776);  // &0x99B2C0
    lw(a1, v0, 84);  // 0x99B314
    lw(a0, v0, 88);  // 0x99B318
    if (i64(a1) > 0) {
        // 0x0057b4b0
        charge(ctx, 2);
        a3 = libs3::mpv::kStateFree;
        lw(v1, a0, tail1::mpv::kHandleState);
        for (;;) {
            // 0x0057b4b8
            charge(ctx, 3);
            v0 = a0;
            a0 = addiu(a0, libs3::mpv::kHandleStride);
            if (v1 == a3) {
                break;
            }
            // 0x0057b4c4
            charge(ctx, 6);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_0057b4dc;
            }
            lw(v1, a0, tail1::mpv::kHandleState);
            backedge(ctx);
        }
        // 0x0057b4e0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0057b4dc:
    charge(ctx, 1);
    v0 = 0;
    // 0x0057b4e0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057B4E8 sub_57B4E8 -- 196 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpvInitHandle] Initialises an MPV handle: the shared tables (sub_57B278), +396 = 0, the 16 callbacks copied from the
// defaults 0x99B2C0 to +400, the error record (loc_578D80, the mid-body entry of sub_578D60) at +592, the sequence
// block reset (sub_57B368 at +464), the counters and the four user-data rows (sub_5793E8), the window (sub_579410),
// state 2 (valid).
void sub_57B4E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b4e8
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 0;
    jal(ctx, 0x57B4FCu, gen::fn_sub_57B278_0057b278);
    sw(zero, s0, 396);
    a1 = 0x9A0000;
    a1 = addiu(a1, -19776);  // &0x99B2C0
    a2 = 16;
    a0 = addiu(s0, 400);
    jal(ctx, 0x57B514u, gen::fn_sub_5756A0_005756a0);
    a0 = addiu(s0, 592);
    link(ctx, 0x57B51Cu);
    gen::fn_sub_578D60_00578d60_at_00578d80(ctx);
    a0 = addiu(s0, 464);
    jal(ctx, 0x57B524u, gen::fn_sub_57B368_0057b368);
    sw(zero, s0, 896);
    lw(v0, s0, 428);
    sw(zero, s0, 900);
    sw(v0, s0, 932);
    sw(zero, s0, 856);
    sw(zero, s0, 860);
    sw(zero, s0, 864);
    sw(zero, s0, 868);
    sw(zero, s0, 916);
    a1 = s1;
    for (;;) {
        // 0x0057b558
        charge(ctx, 9);
        s1 = addiu(s1, 1);
        a0 = s0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x57B568u, gen::fn_sub_5793E8_005793e8);
        v0 = slti(s1, 4);
        a1 = s1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057b57c
    charge(ctx, 12);
    a0 = s0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x57B584u, gen::fn_sub_579410_00579410);
    v0 = 2;
    sw(v0, s0, 392);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057B5B0 sub_57B5B0 -- 24 bytes; leaf frame (no stack)
// [mpvGetPair] Reads two words of an MPV handle's record at +120: *a = +144, *b = +148.
void sub_57B5B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0057b5b0
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = addiu(a0, 120);
    lw(v0, a0, 24);
    sw(v0, a1, 0);
    lw(v1, a0, 28);
    sw(v1, a2, 0);
}

// 0x0057B5C8 sub_57B5C8 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mpvDestroy] MPV destroy (h): the handle check sub_57B7F0 (tail1); on failure MPV raises 0xFF030201 (with a null
// handle); otherwise destroys the decoder handle (sub_57B890), runs the unlock hook over the 1,028 bytes and frees the
// handle (state 1). Returns 0.
void sub_57B5C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b5c8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x57B5D4u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a0 = s0;
    a1 = a1 | 0x201;
    if (v0 != 0) {
        // 0x0057b5ec
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x0057b600
    charge(ctx, 12);
    jal(ctx, 0x57B600u, gen::fn_sub_57B890_0057b890);
    a0 = s0;
    a1 = 1028;
    jal(ctx, 0x57B60Cu, gen::fn___env_unlock_5_0057b638);
    v0 = 1;
    sw(v0, s0, 392);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0057B630 __env_lock_5 -- 8 bytes; leaf frame (no stack)
// [mpvLockHook] An empty lock hook (jr $ra / nop) MPV calls around its pool (area, size). The FLIRT name is a false
// match of a short code shape; the role is read from the instructions.
void __env_lock_5(EEContext& ctx) {
    using namespace hg;
    // 0x0057b630
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0057B638 __env_unlock_5 -- 8 bytes; leaf frame (no stack)
// [mpvUnlockHook] An empty unlock hook (jr $ra / nop). The FLIRT name is a false match of a short code shape; the role
// is read from the instructions.
void __env_unlock_5(EEContext& ctx) {
    using namespace hg;
    // 0x0057b638
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0057B640 sub_57B640 -- 8 bytes; leaf frame (no stack)
// [mpvNullCallback] An empty function (jr $ra / nop): the default callback 8 of MPV.
void sub_57B640(EEContext& ctx) {
    using namespace hg;
    // 0x0057b640
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0057B648 sub_57B648 -- 196 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// [mpvSetCallback] MPV set-callback (h, id, fn): callback 8 defaults to sub_57B640; h == 0 sets the default table
// (0x99B2C0) and every valid handle (sub_57B710); a handle that fails the handle check sub_57B7F0 (tail1); on failure
// MPV raises 0xFF030202; then the decoder side is told (sub_57B8A8). Returns 0.
void sub_57B648(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b648
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 8;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x18);
    a0 = s2;
    if (s2 == v0) {
        // 0x0057b674
        charge(ctx, 2);
        v0 = 0x580000;
        if (s0 == 0) {
            // 0x0057b67c
            charge(ctx, 1);
            s0 = addiu(v0, -18880);
        }
    }
    // 0x0057b680
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x0057b688
        charge(ctx, 5);
        a1 = s0;
        jal(ctx, 0x57B688u, gen::fn_sub_57B710_0057b710);
        v0 = 0x9A0000;
        v1 = addiu(v0, -19776);  // &0x99B2C0
        goto L_0057b6d4;
    }
    // 0x0057b6a0
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x57B6A0u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a0 = 0;
    if (v0 != 0) {
        // 0x0057b6b4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x202;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x0057b6d0
    charge(ctx, 1);
    v1 = addiu(s1, 400);
L_0057b6d4:
    charge(ctx, 14);
    v0 = sll(s2, 2);
    a0 = s1;
    v0 = addu(v0, v1);
    a1 = s2;
    sw(s0, v0, 0);
    a2 = s0;
    jal(ctx, 0x57B6E8u, gen::fn_sub_57B8A8_0057b8a8);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057B710 sub_57B710 -- 76 bytes; leaf frame (no stack)
// [mpvSetCallbackAll] Sets callback id to fn in every valid MPV handle (state 2; +400 + 4 * id).
void sub_57B710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0057b710
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    v0 = addiu(v0, -19776);  // &0x99B2C0
    lw(a2, v0, 84);  // 0x99B314
    lw(v1, v0, 88);  // 0x99B318
    if (i64(a2) > 0) {
        // 0x0057b724
        charge(ctx, 3);
        v0 = sll(a0, 2);
        a3 = 2;
        a0 = addiu(v0, 400);
        for (;;) {
            // 0x0057b730
            charge(ctx, 3);
            lw(v0, v1, 392);
            a2 = addiu(a2, -1);
            if (v0 == a3) {
                // 0x0057b73c
                charge(ctx, 2);
                v0 = addu(v1, a0);
                sw(a1, v0, 0);
            }
            // 0x0057b744
            charge(ctx, 4);
            v1 = addiu(v1, libs3::mpv::kHandleStride);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0057b754 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057B760 sub_57B760 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpvGetCallback] MPV get-callback (h, id, &fn): from the handle (+400) or, for h == 0, the default table; a handle
// that fails the handle check sub_57B7F0 (tail1); on failure MPV raises 0xFF030210. Returns 0.
void sub_57B760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b760
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 == 0) {
        // 0x0057b784
        charge(ctx, 3);
        v0 = 0x9A0000;
        a0 = addiu(v0, -19776);  // &0x99B2C0
        // 0x0057b7c4 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        v1 = sll(s1, 2);
        ld(s1, sp, 0x8);
        v1 = addu(v1, a0);
        ld(s0, sp, 0x0);
        lw(a0, v1, 0);
        v0 = 0;
        ld(ra, sp, 0x18);
        sw(a0, s2, 0);
        ld(s2, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0057b790
    charge(ctx, 5);
    jal(ctx, 0x57B790u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a0 = 0;
    if (v0 != 0) {
        // 0x0057b7a4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x210;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x0057b7c0
    charge(ctx, 1);
    a0 = addiu(s0, 400);
    // 0x0057b7c4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v1 = sll(s1, 2);
    ld(s1, sp, 0x8);
    v1 = addu(v1, a0);
    ld(s0, sp, 0x0);
    lw(a0, v1, 0);
    v0 = 0;
    ld(ra, sp, 0x18);
    sw(a0, s2, 0);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057B818 sub_57B818 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into __errno_11 (0x56F500, a CRI getter despite the FLIRT name).
void sub_57B818(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b818
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___errno_11_0056f500(ctx);  // tail call
}

// 0x0057B830 sub_57B830 -- 44 bytes; frame 0x10: ra sp+0x0
// [mpvLinkM2v] MPV's link to M2V: fills M2V's entry table (sub_574CA8) and registers it (sub_56F570(8, 0x99B320,
// 14,400) in the CRI band).
void sub_57B830(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b830
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57B838u, gen::fn_sub_574CA8_00574ca8);
    ld(ra, sp, 0x0);
    a1 = 0x9A0000;
    a1 = addiu(a1, -19680);  // &0x99B320
    a0 = 8;
    a2 = 14400;
    sp = addiu(sp, 0x10);
    gen::fn_sub_56F570_0056f570(ctx);  // tail call
}

// 0x0057B860 sub_57B860 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into sub_56F598 (the decoder side's finish).
void sub_57B860(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b860
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56F598_0056f598(ctx);  // tail call
}

// 0x0057B878 sub_57B878 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into sub_56F5C0 (the decoder side's create).
void sub_57B878(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b878
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56F5C0_0056f5c0(ctx);  // tail call
}

// 0x0057B890 sub_57B890 -- 24 bytes; frame 0x10: ra sp+0x0
// Destroys an MPV handle's decoder handle (+944) through sub_56F5F0.
void sub_57B890(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b890
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 944);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56F5F0_0056f5f0(ctx);  // tail call
}

// 0x0057B8A8 sub_57B8A8 -- 36 bytes; frame 0x10: ra sp+0x0
// Tells the decoder side a callback changed: sub_56F640(the handle's decoder handle +944, or 0).
void sub_57B8A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b8a8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0057b8b8
        charge(ctx, 1);
        lw(v0, a0, 944);
    }
    // 0x0057b8bc
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_sub_56F640_0056f640(ctx);  // tail call
}

// 0x0057B8D0 sub_57B8D0 -- 200 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// [mpvDecodeHeadersM2v] MPV over the decoder side (h, stream) for MPEG-2 input: needs the decoder (__errno_11, -1
// without); passes the four user-data rows (sub_56F708) and the window (sub_56F730), runs the decoder's header parse
// (sub_56F780; -2 on failure), fetches its user data into +1008 (sub_56F758) and copies its header state back
// (sub_57B998).
void sub_57B8D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057b8d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s3 = a1;
    jal(ctx, 0x57B8ECu, gen::fn___errno_11_0056f500);
    s2 = 0;
    if (v0 == 0) {
        // 0x0057b978
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x0057b8fc
        charge(ctx, 3);
        s0 = addiu(s1, 952);
        lw(a2, s0, 0);
        for (;;) {
            // 0x0057b908
            charge(ctx, 10);
            a1 = s2;
            lw(a3, s0, 4);
            s2 = addiu(s2, 1);
            lw(t0, s0, 8);
            s0 = addiu(s0, 12);
            link(ctx, 0x57B91Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 944);
            call(ctx, gen::fn_sub_56F708_0056f708);
            v0 = slti(s2, 4);
            if (v0 == 0) {
                break;
            }
            lw(a2, s0, 0);
            backedge(ctx);
        }
        // 0x0057b930
        charge(ctx, 9);
        lw(a0, s1, 944);
        lw(a1, s1, 1000);
        link(ctx, 0x57B938u);  // $ra first: the delay slot below depends on it
        lw(a2, s1, 1004);
        call(ctx, gen::fn_sub_56F730_0056f730);
        lw(a0, s1, 944);
        a1 = s3;
        jal(ctx, 0x57B944u, gen::fn_sub_56F780_0056f780);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = si(-2);
        if (!cc) {
            // 0x0057b954
            charge(ctx, 8);
            lw(a0, s1, 944);
            a1 = 0;
            a2 = addiu(s1, 1008);
            jal(ctx, 0x57B95Cu, gen::fn_sub_56F758_0056f758);
            a0 = s1;
            jal(ctx, 0x57B964u, gen::fn_sub_57B998_0057b998);
            v0 = 0;
        }
    }
    // 0x0057b97c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057B998 sub_57B998 -- 320 bytes; frame 0xB0: s0 sp+0xA0, ra sp+0xA8
// [mpvFetchM2vState] Copies the decoder side's header state into an MPV handle: the 128-byte sequence block (sub_56F7B0
// into a stack buffer, then +464 in 8-byte or 4-byte steps by alignment) and the picture / GOP words (sub_56F7D8,
// sub_56F800, sub_56F828).
void sub_57B998(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057b998
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(s0, sp, 0xA0);
    s0 = a0;
    sd(ra, sp, 0xA8);
    a1 = sp;
    link(ctx, 0x57B9ACu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 944);
    call(ctx, gen::fn_sub_56F7B0_0056f7b0);
    lw(a0, s0, 944);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x57B9B8u, gen::fn_sub_56F7D8_0056f7d8);
    lw(a0, s0, 944);
    a1 = addiu(sp, 0x84);
    a2 = addiu(sp, 0x88);
    a3 = addiu(sp, 0x8C);
    jal(ctx, 0x57B9CCu, gen::fn_sub_56F800_0056f800);
    lw(a0, s0, 944);
    a1 = addiu(sp, 0x90);
    a2 = addiu(sp, 0x94);
    jal(ctx, 0x57B9DCu, gen::fn_sub_56F828_0056f828);
    v1 = addiu(s0, 464);
    v0 = v1 & 0x7;
    a0 = sp;
    if (v0 == 0) {
        // 0x0057ba58
        charge(ctx, 1);
        v0 = addiu(sp, 0x80);
        for (;;) {
            // 0x0057ba5c
            charge(ctx, 13);
            ld(a1, a0, 0);
            ld(a2, a0, 8);
            ld(a3, a0, 16);
            ld(t0, a0, 24);
            sd(a1, v1, 0);
            sd(a2, v1, 8);
            sd(a3, v1, 16);
            sd(t0, v1, 24);
            a0 = addiu(a0, 32);
            v1 = addiu(v1, 32);
            if (a0 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0057ba90
        charge(ctx, 1);
        lw(v0, sp, 0x84);
    } else {
        // 0x0057b9f4
        charge(ctx, 1);
        v0 = addiu(sp, 0x80);
        for (;;) {
            // 0x0057b9f8
            charge(ctx, 21);
            ldl(a1, a0, 7);
            ldr(a1, a0, 0);
            ldl(a2, a0, 15);
            ldr(a2, a0, 8);
            ldl(a3, a0, 23);
            ldr(a3, a0, 16);
            ldl(t0, a0, 31);
            ldr(t0, a0, 24);
            sdl(a1, v1, 7);
            sdr(a1, v1, 0);
            sdl(a2, v1, 15);
            sdr(a2, v1, 8);
            sdl(a3, v1, 23);
            sdr(a3, v1, 16);
            sdl(t0, v1, 31);
            sdr(t0, v1, 24);
            a0 = addiu(a0, 32);
            v1 = addiu(v1, 32);
            if (a0 == v0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0057ba4c
        charge(ctx, 2);
        lw(v0, sp, 0x84);
    }
    // 0x0057ba94 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    lw(a2, sp, 0x80);
    a0 = addiu(v0, 2047);
    v1 = slti(v0, 0);
    lw(a1, sp, 0x88);
    if (v1 != 0) v0 = a0;
    lw(a0, sp, 0x90);
    v0 = sra(v0, 11);
    lw(v1, sp, 0x94);
    ld(ra, sp, 0xA8);
    sw(a2, s0, 680);
    sw(v1, s0, 696);
    sw(v0, s0, 684);
    sw(a1, s0, 700);
    sw(a0, s0, 692);
    ld(s0, sp, 0xA0);
    sp = addiu(sp, 0xB0);
}

// 0x0057BAD8 sub_57BAD8 -- 20 bytes; frame 0x10: ra sp+0x0
// A tail call into sub_57BAF0 (muldiv). No caller.
void sub_57BAD8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0057bad8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_57BAF0_0057baf0(ctx);  // tail call
}

// 0x0057BAF0 sub_57BAF0 -- 104 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [criMulDiv] CRI's muldiv (a, b, c): the 64-bit product a * b (mult) divided by c (__divdi3), truncated to 32 bits; c
// == 0 saturates to 0x7FFFFFFF, or to -0x80000000 when a and b have opposite signs. Two chunks (the saturating tail
// sits after the next function's entry).
void sub_57BAF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057baf0
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = a1;
    a1 = a2;
    mult(zero, a0, v0);
    sp = addiu(sp, -0x10);
    a0 = a0 ^ v0;
    sd(ra, sp, 0x0);
    a0 = slti(a0, 0);
    mflo(a3);
    mfhi(v1);
    a3 = dsll32(a3, 0);
    v1 = dsll32(v1, 0);
    a3 = dsrl32(a3, 0);
    v1 = v1 | a3;
    if (a2 != 0) {
        // 0x0057bb40
        charge(ctx, 4);
        a0 = v1;
        jal(ctx, 0x57BB40u, gen::fn___divdi3_0052eeb0);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
    } else {
        // 0x0057bb28
        charge(ctx, 5);
        v0 = 0x7FFF0000;
        v1 = lui(0x8000);
        v0 = v0 | 0xFFFF;
        if (a0 != 0) v0 = v1;
    }
    // 0x0057bb50 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0057BB60 sub_57BB60 -- 176 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [criMulDivRound] CRI's rounded muldiv (a, b, c): |a| * |b| + |c| / 2 divided by |c| (64-bit, __muldi3 / __divdi3),
// with the sign of a * b / c; c == 0 returns 0 (unlike sub_57BAF0). No caller.
void sub_57BB60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057bb60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (a2 != 0) {
        // 0x0057bb90
        charge(ctx, 3);
        s0 = a2;
        s1 = 1;
        if (i64(a0) < 0) {
            // 0x0057bb9c
            charge(ctx, 2);
            s1 = si(-1);
            a0 = 0 - a0;
        }
        // 0x0057bba4
        charge(ctx, 2);
        if (i64(a1) < 0) {
            // 0x0057bbac
            charge(ctx, 2);
            s1 = subu(0, s1);
            a1 = 0 - a1;
        }
        // 0x0057bbb4
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x0057bbbc
            charge(ctx, 2);
            s0 = 0 - s0;
            s1 = subu(0, s1);
        }
        // 0x0057bbc4
        charge(ctx, 14);
        jal(ctx, 0x57BBC4u, gen::fn___muldi3_0052ea78);
        a0 = dsrl32(s0, 31);
        a0 = s0 + a0;
        a1 = s0;
        a0 = dsra(a0, 1);
        a0 = v0 + a0;
        jal(ctx, 0x57BBDCu, gen::fn___divdi3_0052eeb0);
        a0 = slti(s1, 0);
        v1 = 0 - v0;
        if (a0 != 0) v0 = v1;
        a0 = v0;
        v0 = dsll32(a0, 0);
        v0 = dsra32(v0, 0);
    } else {
        // 0x0057bb74
        charge(ctx, 7);
        v1 = a0 ^ a1;
        a0 = lui(0x8000);
        v0 = 0x7FFF0000;
        v1 = slti(v1, 0);
        v0 = v0 | 0xFFFF;
        if (v1 != 0) v0 = a0;
    }
    // 0x0057bbfc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057BC10 sub_57BC10 -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [criMulDivRound2] The same rounded muldiv as sub_57BB60 (a second copy, the result negated with a 64-bit negu); used
// by sub_590AE8.
void sub_57BC10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057bc10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 != 0) {
        // 0x0057bc48
        charge(ctx, 2);
        s1 = 1;
        if (i64(a0) < 0) {
            // 0x0057bc50
            charge(ctx, 2);
            s1 = si(-1);
            a0 = 0 - a0;
        }
        // 0x0057bc58
        charge(ctx, 2);
        if (i64(a1) < 0) {
            // 0x0057bc60
            charge(ctx, 2);
            s1 = subu(0, s1);
            a1 = 0 - a1;
        }
        // 0x0057bc68
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x0057bc70
            charge(ctx, 2);
            s0 = 0 - s0;
            s1 = subu(0, s1);
        }
        // 0x0057bc78
        charge(ctx, 11);
        jal(ctx, 0x57BC78u, gen::fn___muldi3_0052ea78);
        a0 = dsrl32(s0, 31);
        a0 = s0 + a0;
        a1 = s0;
        a0 = dsra(a0, 1);
        a0 = v0 + a0;
        jal(ctx, 0x57BC90u, gen::fn___divdi3_0052eeb0);
        a0 = slti(s1, 0);
        v1 = 0 - v0;
        if (a0 != 0) v0 = v1;
    } else {
        // 0x0057bc28
        charge(ctx, 8);
        v1 = a0 ^ a1;
        a0 = 0x8000;
        a0 = dsll32(a0, 16);
        v1 = slti(v1, 0);
        v0 = si(-1);
        v0 = dsrl(v0, 1);
        if (v1 != 0) v0 = a0;
    }
    // 0x0057bca4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057BCB8 sub_57BCB8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an 8-byte stub; no caller).
void sub_57BCB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057bcb8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0057BCD8 sub_57BCD8 -- 52 bytes; frame 0x10: ra sp+0x0
// [criCallHook] Calls the hook 0x7B2E14 (when set) with its argument 0x7B2E18 and a0; returns 0. No caller.
void sub_57BCD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0057bcd8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 11796);  // 0x7B2E14
    a1 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0057bcf0
        charge(ctx, 3);
        v0 = 0x7B0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x57BCF4u);  // $ra = the return address
        lw(a0, v0, 11800);
        call_ptr(ctx, jt);
    }
    // 0x0057bcfc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0057BD10 sub_57BD10 -- 28 bytes; leaf frame (no stack)
// [criKeyRetain] Increments the key-schedule user count 0x7B2E10; returns 0.
void sub_57BD10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057bd10
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x7B0000;
    v0 = 0;
    a0 = addiu(a0, 11792);  // &0x7B2E10
    lw(v1, a0, 0);  // 0x7B2E10
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x7B2E10
}

// 0x0057BD30 sub_57BD30 -- 28 bytes; leaf frame (no stack)
// [criKeyRelease] Decrements the key-schedule user count 0x7B2E10; returns 0.
void sub_57BD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057bd30
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x7B0000;
    v0 = 0;
    a0 = addiu(a0, 11792);  // &0x7B2E10
    lw(v1, a0, 0);  // 0x7B2E10
    v1 = addiu(v1, -1);
    sw(v1, a0, 0);  // 0x7B2E10
}

// 0x0057BD50 sub_57BD50 -- 436 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [criKeyFromString] CRI's key derivation (s, n, &k0, &k1, &k2): retains the key tables (sub_57BD10) when unused,
// clears the outputs, then runs three hash chains over the n bytes of s, seeded with the halfwords 0x7C13B8 / 0x7C15B8
// / 0x7C17B8: v = T[(v * U[c]) mod 1024] with T the 1,024 halfwords at 0x7C11B8 and U the halfwords at 0x7C12B8 indexed
// by the signed byte c; the three final values are the keys. Returns 0.
void sub_57BD50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057bd50
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, 11792);  // 0x7B2E10
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(ra, sp, 0x28);
    if (v1 == 0) {
        // 0x0057bd8c
        charge(ctx, 2);
        jal(ctx, 0x57BD8Cu, gen::fn_sub_57BD10_0057bd10);
    }
    // 0x0057bd94
    charge(ctx, 4);
    sh(zero, s2, 0);
    sh(zero, s3, 0);
    sh(zero, s4, 0);
    if (s1 == 0) {
        // 0x0057bda4
        charge(ctx, 2);
        v0 = 0;
        if (i64(s0) > 0) {
            goto L_0057bdac;
        }
        // 0x0057bee4 (the shared epilogue, written out on this path)
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
L_0057bdac:
    charge(ctx, 5);
    t3 = 0x7C0000;
    a3 = 0;
    v0 = addiu(t3, 4536);  // &0x7C11B8
    lh(t2, v0, 512);  // 0x7C13B8
    if (i64(s0) > 0) {
        // 0x0057bdc0
        charge(ctx, 2);
        t0 = v0;
        for (;;) {
            // 0x0057bdc8
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t0);
            lh(v1, v0, 256);
            mult(v1, t2, v1);
            a1 = addiu(v1, 1023);
            a0 = slti(v1, 0);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t0);
            lh(t2, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0057be14
        charge(ctx, 2);
        v0 = addiu(t3, 4536);
        a3 = 0;
    }
    // 0x0057be1c
    charge(ctx, 2);
    lh(t0, v0, 1024);
    if (i64(s0) > 0) {
        // 0x0057be24
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x0057be28
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t1);
            lh(v1, v0, 256);
            mult(v1, t0, v1);
            a1 = addiu(v1, 1023);
            a0 = slti(v1, 0);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t1);
            lh(t0, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0057be74
    charge(ctx, 4);
    v0 = addiu(t3, 4536);
    a3 = 0;
    lh(a0, v0, 1536);
    if (i64(s0) > 0) {
        // 0x0057be84
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x0057be88
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t1);
            lh(v1, v0, 256);
            mult(v1, a0, v1);
            a0 = slti(v1, 0);
            a1 = addiu(v1, 1023);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t1);
            lh(a0, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0057bed4
    charge(ctx, 4);
    sh(t2, s2, 0);
    v0 = 0;
    sh(t0, s3, 0);
    sh(a0, s4, 0);
    // 0x0057bee4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0057BF08 sub_57BF08 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [criKeyDefault] CRI key from the fixed string "CRI-MW" (6 bytes, sub_57BD50). Returns 0. No caller.
void sub_57BF08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057bf08
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 11792);  // 0x7B2E10
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (v1 == 0) {
        // 0x0057bf34
        charge(ctx, 2);
        jal(ctx, 0x57BF34u, gen::fn_sub_57BD10_0057bd10);
    }
    // 0x0057bf3c
    charge(ctx, 14);
    a0 = 0x7C0000;
    a2 = s0;
    a3 = s1;
    t0 = s2;
    a0 = addiu(a0, 31440);  // "CRI-MW"
    a1 = 6;
    jal(ctx, 0x57BF50u, gen::fn_sub_57BD50_0057bd50);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0057BF78 sub_57BF78 -- 32 bytes; leaf frame (no stack)
// [criKeyStep] One step of the key generator: *x = *x * *a + *c (16-bit).
void sub_57BF78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0057bf78
    enter(ctx, 8);  // entry check point + this block's cycles
    lhu(a3, a1, 0);
    v0 = 0;
    lhu(a1, a0, 0);
    lhu(v1, a2, 0);
    mult(a1, a1, a3);
    v1 = addu(v1, a1);
    sh(v1, a0, 0);
}

// 0x0057BF98 sub_57BF98 -- 32 bytes; leaf frame (no stack)
// [criKeyTableInit] Key-table setup (p, size): needs 140 bytes; marks p valid (*p = 1) and returns p, else 0.
void sub_57BF98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0057bf98
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = sltiu(a1, 140);
    v0 = 0;
    if (a1 == 0) {
        // 0x0057bfa4
        charge(ctx, 3);
        v1 = 1;
        v0 = a0;
        sw(v1, a0, 0);
    }
    // 0x0057bfb0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0057BFB8 sub_57BFB8 -- 8 bytes; leaf frame (no stack)
// [criKeyTableReset] Clears a key table's valid word (*p = 0).
void sub_57BFB8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x0057bfb8
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(zero, a0, 0);
}

// 0x0057BFC0 sub_57BFC0 -- 256 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// [criKeyTableFill] Key table from a string (table, s): derives the three values from s (strlen, sub_57BD50), stores
// them at +4 / +6 / +8 and fills the 32 halfwords +10.. by stepping the generator (sub_57BF78).
void sub_57BFC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057bfc0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = 31;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x40);
    s5 = addiu(s2, 10);
    jal(ctx, 0x57BFECu, gen::fn_sub_57BD10_0057bd10);
    a0 = s0;
    jal(ctx, 0x57BFF4u, gen::fn_strlen_00524388);
    a0 = s0;
    s4 = addiu(sp, 0x2);
    s3 = addiu(sp, 0x4);
    a1 = v0;
    a2 = sp;
    a3 = s4;
    t0 = s3;
    jal(ctx, 0x57C014u, gen::fn_sub_57BD50_0057bd50);
    s0 = s5;
    lhu(a0, sp, 0x0);
    lhu(v0, sp, 0x2);
    lhu(v1, sp, 0x4);
    sh(v0, s2, 6);
    sh(v1, s2, 8);
    sh(a0, s2, 4);
    for (;;) {
        // 0x0057c038
        charge(ctx, 10);
        sh(a0, s0, 0);
        s0 = addiu(s0, 2);
        a0 = sp;
        a1 = s4;
        a2 = s3;
        s1 = addiu(s1, -1);
        jal(ctx, 0x57C04Cu, gen::fn_sub_57BF78_0057bf78);
        lhu(a0, sp, 0x0);
        sh(a0, s2, 4);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057c060
    charge(ctx, 2);
    s0 = addiu(s5, 64);
    s1 = 31;
    for (;;) {
        // 0x0057c068
        charge(ctx, 11);
        sh(a0, s0, 0);
        s0 = addiu(s0, 2);
        a0 = sp;
        a1 = s4;
        a2 = s3;
        s1 = addiu(s1, -1);
        jal(ctx, 0x57C07Cu, gen::fn_sub_57BF78_0057bf78);
        lhu(v1, sp, 0x0);
        a0 = v1;
        sh(a0, s2, 4);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057c094
    charge(ctx, 11);
    jal(ctx, 0x57C094u, gen::fn_sub_57BD30_0057bd30);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0057C188 sub_57C188 -- 132 bytes; leaf frame (no stack)
// [criDescramble] Descrambles 1,024 halfwords in place with a key table: x ^= table[(i + 16) % 32] ^ table[i / 32] (the
// halfwords at +74).
void sub_57C188(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x0057c188
    enter(ctx, 4);  // entry check point + this block's cycles
    t1 = addiu(a0, 10);
    t0 = a1;
    a3 = 0;
    for (;;) {
        // 0x0057c198
        charge(ctx, 27);
        a1 = addiu(a3, 16);
        a0 = addiu(a3, 47);
        v1 = slti(a1, 0);
        v0 = a1;
        if (v1 != 0) v0 = a0;
        a0 = slti(a3, 0);
        a2 = addiu(a3, 31);
        v1 = a3;
        v0 = sra(v0, 5);
        if (a0 != 0) v1 = a2;
        v0 = sll(v0, 5);
        v1 = sra(v1, 5);
        v0 = subu(a1, v0);
        v1 = sll(v1, 1);
        v0 = sll(v0, 1);
        v1 = addu(v1, t1);
        v0 = addu(v0, t1);
        lhu(a1, v1, 64);
        lhu(a0, v0, 64);
        a3 = addiu(a3, 1);
        lhu(v0, t0, 0);
        a2 = slti(a3, 1024);
        a0 = a0 ^ a1;
        v0 = v0 ^ a0;
        sh(v0, t0, 0);
        t0 = addiu(t0, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057c204
    charge(ctx, 2);
}

// 0x0057C210 sub_57C210 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [criDescrambleBlock] Descrambles a block when needed (table, block): the key words (loc_57C138, the mid-body entry of
// sub_57C0C0), then, unless the block already starts with a pack or end start code (sub_57C270), the descrambler
// sub_57C188 on it.
void sub_57C210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c210
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    link(ctx, 0x57C224u);
    gen::fn_sub_57C0C0_0057c0c0_at_0057c138(ctx);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x57C230u, gen::fn_sub_57C270_0057c270);
    a0 = s0;
    a1 = s1;
    if (v0 != 0) {
        // 0x0057c258
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0057c244
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_57C188_0057c188(ctx);  // tail call
}

// 0x0057C270 sub_57C270 -- 64 bytes; leaf frame (no stack)
// [criIsPackStart] Returns 1 when its second argument p starts with 00 00 01 B9 or 00 00 01 BA (start code byte + 71 <
// 2 as a byte), else 0 (the first argument, the key table of the caller, is not read).
void sub_57C270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0057c270
    enter(ctx, 3);  // entry check point + this block's cycles
    lbu(v0, a1, 0);
    a0 = 0;
    if (v0 == 0) {
        // 0x0057c27c
        charge(ctx, 3);
        lbu(v0, a1, 1);
        if (v0 == 0) {
            // 0x0057c288
            charge(ctx, 4);
            lbu(v1, a1, 2);
            v0 = 1;
            if (v1 == v0) {
                // 0x0057c298
                charge(ctx, 4);
                lbu(v0, a1, 3);
                v0 = addiu(v0, 71);
                v0 = v0 & 0xFF;
                a0 = sltiu(v0, 2);
            }
        }
    }
    // 0x0057c2a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x0057C2B0 sub_57C2B0 -- 228 bytes; leaf frame (no stack)
// [mwsfdCalcBufferSizes] MWSFD work sizes of the buffers a creation parameter asks for (cprm, &a, &b, &c, &d, &e, &f):
// by the buffer format (+0: 2, 3 or other) and the size words (+4 bit rate, +20 count) -- 2,048-byte units of the
// stream buffer, the audio and the supplementary buffers -- each output a byte count.
void sub_57C2B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25};
    // 0x0057c2b0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t5, a0, 20);
    v1 = 1;
    lw(t6, a0, 0);
    t3 = 2;
    v0 = slt(0, t5);
    t7 = a1;
    t8 = a2;
    if (v0 == 0) t5 = v1;
    t9 = a3;
    lw(t4, a0, 4);
    if (t6 == t3) {
        // 0x0057c2dc
        charge(ctx, 10);
        a0 = addiu(t4, 16383);
        v1 = slti(t4, 0);
        if (v1 != 0) t4 = a0;
        v0 = sra(t4, 14);
        mult(v0, v0, t5);
        v0 = sll(v0, 11);
        sw(v0, t7, 0);
        sw(zero, t8, 0);
        sw(zero, t9, 0);
        // 0x0057c340 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        sw(zero, t0, 0);
        sw(zero, t1, 0);
        sw(zero, t2, 0);
        return;
    }
    // 0x0057c308
    charge(ctx, 3);
    v0 = 3;
    v1 = slti(t4, 0);
    if (t6 != v0) {
        // 0x0057c350
        charge(ctx, 17);
        a0 = addiu(t4, 16383);
        if (v1 != 0) t4 = a0;
        a1 = 24012;
        v0 = sra(t4, 14);
        a2 = 24332;
        mult(v1, v0, t5);
        v0 = sll(v0, 10);
        a3 = 0x81C0;
        v0 = addiu(v0, 2048);
        v1 = sll(v1, 11);
        sw(v1, t7, 0);
        sw(zero, t8, 0);
        sw(v0, t9, 0);
        sw(a1, t0, 0);
        sw(a2, t1, 0);
        sw(a3, t2, 0);
        return;
    }
    // 0x0057c314
    charge(ctx, 11);
    v0 = slti(t4, 0);
    a0 = addiu(t4, 16383);
    if (v0 != 0) t4 = a0;
    v1 = sra(t4, 14);
    mult(v0, v1, t5);
    v1 = sll(v1, 10);
    v1 = addiu(v1, 2048);
    v0 = sll(v0, 11);
    sw(v0, t7, 0);
    sw(zero, t8, 0);
    sw(v1, t9, 0);
    // 0x0057c340 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sw(zero, t0, 0);
    sw(zero, t1, 0);
    sw(zero, t2, 0);
}

// 0x0057C398 sub_57C398 -- 76 bytes; leaf frame (no stack)
// [mwsfdCalcPictureSizes] Picture sizes of a creation parameter: width (+8), height (+12), the half width rounded up to
// 32 and the half height.
void sub_57C398(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0057c398
    enter(ctx, 19);  // entry check point + this block's cycles
    lw(t2, a0, 8);
    lw(t3, a0, 12);
    v1 = srl(t2, 31);
    v1 = addu(t2, v1);
    a0 = srl(t3, 31);
    v1 = sra(v1, 1);
    a0 = addu(t3, a0);
    v0 = addiu(v1, 31);
    v1 = addiu(v1, 62);
    t1 = slti(v0, 0);
    a0 = sra(a0, 1);
    if (t1 != 0) v0 = v1;
    v0 = sra(v0, 5);
    v0 = sll(v0, 5);
    sw(v0, a3, 0);
    sw(a0, t0, 0);
    sw(t2, a1, 0);
    sw(t3, a2, 0);
}

// 0x0057C3E8 sub_57C3E8 -- 256 bytes; frame 0x40: s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, s1 sp+0x18, ra sp+0x30
// [mwsfdCalcFrameSizes] Frame-buffer work size of a creation parameter (cprm, &a, &b): 0 when the external frame pool
// is in use (0x7B2F40); otherwise from the picture sizes (sub_57C398), the buffer format (sub_57C4E8 on +36) and the
// frame count (+16).
void sub_57C3E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057c3e8
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x40);
    lw(v1, v0, 12096);  // 0x7B2F40
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(s1, sp, 0x18);
    a1 = sp;
    sd(ra, sp, 0x30);
    a2 = addiu(sp, 0x4);
    if (v1 == 0) {
        // 0x0057c430
        charge(ctx, 37);
        a3 = addiu(sp, 0x8);
        t0 = addiu(sp, 0xC);
        link(ctx, 0x57C438u);  // $ra first: the delay slot below depends on it
        lw(s1, s0, 16);
        call(ctx, gen::fn_sub_57C398_0057c398);
        link(ctx, 0x57C440u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 36);
        call(ctx, gen::fn_sub_57C4E8_0057c4e8);
        t1 = 2;
        lw(a1, sp, 0x0);
        lw(a0, sp, 0x4);
        a3 = addiu(a1, 15);
        v1 = slti(a1, 0);
        mult(t0, a1, a0);
        if (v1 != 0) a1 = a3;
        a2 = addiu(a0, 15);
        v1 = slti(a0, 0);
        if (v1 != 0) a0 = a2;
        a1 = sra(a1, 4);
        a0 = sra(a0, 4);
        mult(a3, a1, a0);
        v1 = sll(t0, 3);
        v1 = addu(v1, t0);
        a2 = srl(v1, 31);
        v1 = addu(v1, a2);
        a1 = a3;
        a0 = sll(a3, 1);
        a0 = addu(a0, a3);
        v1 = sra(v1, 1);
        a1 = sll(a1, 10);
        at = 0x80000;
        at = at | 0x6910;
        v1 = addu(at, v1);
        a0 = sll(a0, 7);
        a1 = addiu(a1, 64);
        sw(v1, s2, 0);
        mult(v1, s1, a1);
        a0 = addiu(a0, 64);
        if (v0 != t1) {
            // 0x0057c4c4
            charge(ctx, 1);
            mult(v1, s1, a0);
        }
        // 0x0057c4c8
        charge(ctx, 1);
        sw(v1, s3, 0);
    } else {
        // 0x0057c420
        charge(ctx, 3);
        sw(zero, s2, 0);
        sw(zero, s3, 0);
    }
    // 0x0057c4cc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game
