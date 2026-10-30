// Slice libc: newlib's <stdlib.h> / <locale.h> leaves, the stdio leaves, the mprec bignum leaves of strtod / dtoa, copysign / scalbn.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions and the C standard only
// (ADR-0010: no GPL or newlib source was opened). Pair tests: tests/game/test_libc.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libc.h"

namespace p3fes::recomp_gen {
void fn__Bfree_00521620(p3fes::EEContext&);
void fn___mcmp_00521e70(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn___udivdi3_0052fe98(p3fes::EEContext&);
void fn___umoddi3_00530578(p3fes::EEContext&);
void fn__b2d_00522118(p3fes::EEContext&);
void fn__hi0bits_00521888(p3fes::EEContext&);
void fn__lo0bits_00521908(p3fes::EEContext&);
void fn__mbtowc_r_005210a8(p3fes::EEContext&);
void fn__mprec_log10_005224f8(p3fes::EEContext&);
void fn__ratio_00522440(p3fes::EEContext&);
void fn__setlocale_r_005204a0(p3fes::EEContext&);
void fn__strtol_r_00525a10(p3fes::EEContext&);
void fn__strtoul_r_00525c80(p3fes::EEContext&);
void fn__ulp_00522058(p3fes::EEContext&);
void fn_abs_0051e0e0(p3fes::EEContext&);
void fn_atoi_0051e0f0(p3fes::EEContext&);
void fn_copysign_005236f0(p3fes::EEContext&);
void fn_copysignf_00523980(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_eofread_00523b38(p3fes::EEContext&);
void fn_exponent_005279b8(p3fes::EEContext&);
void fn_localeconv_00520560(p3fes::EEContext&);
void fn_quorem_0051e280(p3fes::EEContext&);
void fn_scalbn_005237b0(p3fes::EEContext&);
void fn_scalbnf_005239a8(p3fes::EEContext&);
void fn_setlocale_00520538(p3fes::EEContext&);
void fn_std_0051f838(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strtol_00525c50(p3fes::EEContext&);
void fn_strtoul_00525e98(p3fes::EEContext&);
void fn_sub_51F690_0051f690(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace libc;  // the named offsets of p3fes/game/libc.h
namespace gen = ::p3fes::recomp_gen;

// 0x0051E0E0 abs -- 16 bytes; leaf frame (no stack)
// abs(j $a0) -> $v0: |j| (subu: INT_MIN stays INT_MIN).
void abs(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0051e0e0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (i64(a0) < 0) {
        a0 = subu(0, a0);
    }
    // 0x0051e0e8
    charge(ctx, 2);
    v0 = a0;
}

// 0x0051E0F0 atoi -- 40 bytes; frame 0x10: ra sp+0x0
// atoi(s $a0) -> $v0: strtol(s, NULL, 10) truncated to int (sign-extended low word).
void atoi(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051e0f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 10;
    jal(ctx, 0x51E0FCu, gen::fn_strtol_00525c50);
    v0 = dsll32(v0, 0);
    ld(ra, sp, 0x0);
    v0 = dsra32(v0, 0);
    sp = addiu(sp, 0x10);
}

// 0x0051E280 quorem -- 560 bytes; frame 0x40: s2 sp+0x10, s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s5 sp+0x28, s6 sp+0x30, ra sp+0x38
// quorem(b $a0, S $a1) -> $v0: one decimal digit of _dtoa_r: the quotient q = b / S (0..9) of two Bigints (dtoa's
// mprec numbers: +16 word count, +20.. the 32-bit words, least significant first), b -= q * S in place. q is first
// estimated from the top words (divu by top(S)+1), subtracted with 16-bit half-word borrows, then corrected once by
// __mcmp(b, S) >= 0 (another subtraction, q + 1); b's word count drops over the high zero words.
void quorem(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051e280
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0;
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(s2, a1, bigint::kWds);
    lw(t7, a0, bigint::kWds);
    t7 = slt(t7, s2);
    s4 = a0;
    if (t7 == 0) {
        // 0x0051e2bc: q estimate = top(b) / (top(S) + 1) (divu; break 7 on a zero divisor)
        charge(ctx, 14);
        s2 = addiu(s2, -1);
        a3 = addiu(a1, bigint::kX);
        t7 = sll(s2, 2);
        s3 = addiu(a0, bigint::kX);
        s0 = addu(a3, t7);
        a0 = addu(s3, t7);
        lw(t6, s0, 0);
        s6 = a3;
        lw(v1, a0, 0);
        t0 = s3;
        t6 = addiu(t6, 1);
        divu(v1, t6);
        if (t6 == 0) {
            brk(ctx, 0x51E2F0u, 0x7u);
        }
        // 0x0051e2f4
        charge(ctx, 3);
        mflo(s1);
        mflo(s5);
        if (s1 != 0) {
            // 0x0051e300: q != 0: b -= q * S, 16 bits at a time with borrow / carry
            charge(ctx, 2);
            a2 = 0;
            t1 = 0;
            for (;;) {
                // 0x0051e308: one 32-bit word of the q * S subtraction
                charge(ctx, 26);
                lw(t3, a3, 0);
                lw(t4, t0, 0);
                t7 = t3 & 0xFFFF;
                t5 = srl(t3, 16);
                mult(t7, t7, s1);
                mult1(t5, t5, s1);
                t6 = t4 & 0xFFFF;
                a3 = addiu(a3, 4);
                t4 = srl(t4, 16);
                t2 = sltu(s0, a3);
                t7 = addu(t7, t1);
                t3 = t7 & 0xFFFF;
                t7 = srl(t7, 16);
                t6 = subu(t6, t3);
                t1 = addu(t5, t7);
                t6 = addu(t6, a2);
                t7 = t1 & 0xFFFF;
                sh(t6, t0, 0);
                a2 = sra(t6, 16);
                t4 = subu(t4, t7);
                t4 = addu(t4, a2);
                t1 = srl(t1, 16);
                sh(t4, t0, 2);
                a2 = sra(t4, 16);
                t0 = addiu(t0, 4);
                if (t2 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051e370
            charge(ctx, 2);
            a0 = addiu(a0, -4);
            if (v1 == 0) {
                // 0x0051e378
                charge(ctx, 3);
                t7 = sltu(s3, a0);
                if (t7 == 0) {
                    sw(s2, s4, bigint::kWds);
                } else {
                    // 0x0051e384
                    charge(ctx, 3);
                    lw(t7, a0, 0);
                    if (t7 != 0) {
                        sw(s2, s4, bigint::kWds);
                    } else {
                        // 0x0051e390
                        charge(ctx, 1);
                        a0 = addiu(a0, -4);
                        for (;;) {
                            // 0x0051e394
                            charge(ctx, 3);
                            t7 = sltu(s3, a0);
                            s2 = addiu(s2, -1);
                            if (t7 != 0) {
                                // 0x0051e3a0
                                charge(ctx, 3);
                                lw(t7, a0, 0);
                                a0 = addiu(a0, -4);
                                if (t7 == 0) {
                                    backedge(ctx);
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x0051e3ac
                        charge(ctx, 1);
                        sw(s2, s4, bigint::kWds);
                    }
                }
            }
        }
        // 0x0051e3b0
        charge(ctx, 4);
        a0 = s4;
        jal(ctx, 0x51E3B0u, gen::fn___mcmp_00521e70);
        cc = i64(v0) < 0;  // the condition, before the delay slot changes it
        v0 = s5;
        if (!cc) {
            // 0x0051e3c0
            charge(ctx, 5);
            s5 = addiu(s1, 1);
            a3 = s6;
            a2 = 0;
            t1 = 0;
            t0 = s3;
            for (;;) {
                // 0x0051e3d4
                charge(ctx, 24);
                lw(t3, a3, 0);
                lw(t5, t0, 0);
                t7 = t3 & 0xFFFF;
                a3 = addiu(a3, 4);
                t7 = addu(t7, t1);
                t6 = t5 & 0xFFFF;
                t4 = t7 & 0xFFFF;
                t3 = srl(t3, 16);
                t7 = srl(t7, 16);
                t6 = subu(t6, t4);
                t1 = addu(t3, t7);
                t6 = addu(t6, a2);
                t7 = t1 & 0xFFFF;
                sh(t6, t0, 0);
                t5 = srl(t5, 16);
                a2 = sra(t6, 16);
                t5 = subu(t5, t7);
                t1 = srl(t1, 16);
                t4 = addu(t5, a2);
                t7 = sltu(s0, a3);
                sh(t4, t0, 2);
                a2 = sra(t4, 16);
                t0 = addiu(t0, 4);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051e434
            charge(ctx, 5);
            t7 = sll(s2, 2);
            a0 = addu(s3, t7);
            lw(t6, a0, 0);
            v0 = s5;
            if (t6 == 0) {
                // 0x0051e448
                charge(ctx, 4);
                a0 = addiu(a0, -4);
                t7 = sltu(s3, a0);
                if (t7 == 0) {
                    sw(s2, s4, bigint::kWds);
                } else {
                    // 0x0051e458
                    charge(ctx, 3);
                    lw(t7, a0, 0);
                    if (t7 != 0) {
                        sw(s2, s4, bigint::kWds);
                    } else {
                        // 0x0051e464
                        charge(ctx, 1);
                        a0 = addiu(a0, -4);
                        for (;;) {
                            // 0x0051e468
                            charge(ctx, 3);
                            t7 = sltu(s3, a0);
                            s2 = addiu(s2, -1);
                            if (t7 != 0) {
                                // 0x0051e474
                                charge(ctx, 3);
                                lw(t7, a0, 0);
                                if (t7 == 0) {
                                    a0 = addiu(a0, -4);
                                    backedge(ctx);
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x0051e480
                        charge(ctx, 2);
                        sw(s2, s4, bigint::kWds);
                        v0 = s5;
                    }
                }
            }
        }
    }
    // 0x0051e488 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0051F690 sub_51F690 -- 12 bytes; leaf frame (no stack)
// [__errno] -> $v0: the address of errno, i.e. newlib's _reent record itself (its word at +0 is errno): *(0x782F30),
// the _impure_ptr. The open / sbrk / stat / unlink wrappers store their error codes through it.
void sub_51F690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, t7{ctx, 15};
    // 0x0051f690
    enter(ctx, 3);  // entry check point + this block's cycles
    t7 = 0x780000;
    lw(v0, t7, 12080);  // 0x782F30: _impure_ptr (errno is its first word): _impure_ptr (errno is its first word): _impure_ptr (errno is its first word)
}

// 0x0051F838 std -- 92 bytes; leaf frame (no stack)
// [std](fp $a0, flags $a1, file $a2, reent $a3): initialise one FILE record of newlib's stdio for __sinit: cursor /
// read / write counts and the buffer zeroed, the flags (+12) and file number (+14) halfwords, the cookie (+28) = the
// FILE itself, the read / write / seek / close callbacks (+32..+44) = __sread, __swrite, __sseek, __sclose, and the
// owning _reent at +84.
void std(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15};
    // 0x0051f838
    enter(ctx, 23);  // entry check point + this block's cycles
    t7 = 0x520000;
    sw(a3, a0, file::kData);
    t6 = 0x520000;
    sh(a1, a0, file::kFlags);
    t7 = addiu(t7, 15456);  // &__sread
    sh(a2, a0, file::kFile);
    t6 = addiu(t6, 15552);  // &__swrite
    sw(t7, a0, file::kRead);
    sw(t6, a0, file::kWrite);
    t7 = 0x520000;
    sw(zero, a0, file::kP);
    t6 = 0x520000;
    sw(zero, a0, file::kR);
    t7 = addiu(t7, 15680);  // &__sseek
    sw(zero, a0, file::kW);
    t6 = addiu(t6, 15784);  // &__sclose
    sw(t7, a0, file::kSeek);
    sw(t6, a0, file::kClose);
    sw(zero, a0, file::kBufBase);
    sw(zero, a0, file::kBufSize);
    sw(zero, a0, file::kLbfSize);
    sw(a0, a0, file::kCookie);
}

// 0x005204A0 _setlocale_r -- 136 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// _setlocale_r(reent $a0, category $a1, locale $a2) -> $v0: NULL locale queries: returns "C" (0x7BEB60). Only "C" or
// the other built-in name at 0x7BEB28 (compared with strcmp) are accepted: they are stored in the _reent (+0x34
// locale, +0x30 category) and "C" is returned; any other name returns NULL (setlocale's 'cannot honour' result).
void _setlocale_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005204a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s1 = a0;
    sd(s3, sp, 0x18);
    s0 = a2;
    sd(ra, sp, 0x20);
    a0 = a2;
    s2 = a1;
    if (a2 != 0) {
        // 0x005204cc: locale == "C"?
        charge(ctx, 5);
        s3 = 0x7C0000;
        a1 = addiu(s3, -5280);  // &0x7BEB60: "C": "C": "C"
        jal(ctx, 0x5204D0u, gen::fn_strcmp_00524128);
        a0 = s0;
        if (v0 != 0) {
            // 0x005204e0: locale == the second built-in name?
            charge(ctx, 5);
            a1 = 0x7C0000;
            a1 = addiu(a1, -5336);  // &0x7BEB28
            jal(ctx, 0x5204E4u, gen::fn_strcmp_00524128);
            t7 = 0;
            if (v0 == 0) {
                goto L_005204f4;
            }
            // 0x00520500 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(s0, sp, 0x0);
            v0 = t7;
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_005204f4:
        charge(ctx, 2);
        sw(s0, s1, reent::kLocale);
        sw(s2, s1, reent::kCategory);
        goto L_005204fc;
    }
    // 0x00520520: locale == NULL: query
    charge(ctx, 2);
    s3 = 0x7C0000;
    backedge(ctx);
L_005204fc:
    charge(ctx, 1);
    t7 = addiu(s3, -5280);
    // 0x00520500 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    v0 = t7;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00520538 setlocale -- 40 bytes; frame 0x10: ra sp+0x0
// setlocale(category $a0, locale $a1) -> $v0: _setlocale_r(_impure_ptr, category, locale) as a tail call.
void setlocale(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00520538
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = a0;
    sd(ra, sp, 0x0);
    t6 = 0x780000;
    a2 = a1;
    lw(a0, t6, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    a1 = t7;
    sp = addiu(sp, 0x10);
    gen::fn__setlocale_r_005204a0(ctx);  // tail call
}

// 0x00520560 localeconv -- 40 bytes, 2 chunks; frame 0x10: ra sp+0x0
// localeconv() -> $v0: the address of the C locale's struct lconv (0x7BEB30). It loads _impure_ptr into $a0 first and
// returns through the shared tail at 0x520528 (the function's second chunk).
void localeconv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00520560
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = 0x780000;
    sd(ra, sp, 0x0);
    lw(a0, t7, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00520528
    charge(ctx, 3);
    v0 = 0x7C0000;
    v0 = addiu(v0, -5328);  // &0x7BEB30
}

// 0x005210A8 _mbtowc_r -- 48 bytes; frame 0x10
// _mbtowc_r(reent $a0, pwc $a1, s $a2, n $a3) -> $v0: the C locale's mbtowc: s == NULL -> 0 (no shift states); n == 0
// -> -1; otherwise *pwc (a stack slot when pwc is NULL) = (unsigned char)*s and the result is 1, or 0 for the NUL
// byte.
void _mbtowc_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29};
    // 0x005210a8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    if (a1 == 0) a1 = sp;
    if (a2 != 0) {
        // 0x005210b8: s != NULL; n == 0 -> -1
        charge(ctx, 2);
        v0 = si(-1);
        if (a3 != 0) {
            // 0x005210c0: *pwc = the byte; result = (byte != 0)
            charge(ctx, 4);
            lbu(t7, a2, 0);
            sw(t7, a1, 0);
            lbu(t6, a2, 0);
            v0 = sltu(0, t6);
        }
    }
    // 0x005210d0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00521620 _Bfree -- 44 bytes; leaf frame (no stack)
// _Bfree(reent $a0, v $a1): return Bigint v to its size class's free list (the _reent's list table at +0x4C, indexed
// by v->k at +4): v->next = list[k]; list[k] = v. NULL is ignored.
void _Bfree(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00521620
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 != 0) {
        // 0x00521628: v->next = freelist[v->k]; freelist[v->k] = v
        charge(ctx, 7);
        lw(t7, a1, bigint::kK);
        lw(t5, a0, reent::kFreelist);
        t7 = sll(t7, 2);
        t7 = addu(t7, t5);
        lw(t6, t7, 0);
        sw(t6, a1, 0);
        sw(a1, t7, 0);
    }
    // 0x00521644 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00521888 _hi0bits -- 124 bytes; leaf frame (no stack)
// _hi0bits(x $a0) -> $v0: the number of leading zero bits of the 32-bit x (binary search over 16 / 8 / 4 / 2 / 1
// bits); 32 for x == 0.
void _hi0bits(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00521888
    enter(ctx, 4);  // entry check point + this block's cycles
    t7 = lui(0xFFFF);
    t7 = a0 & t7;
    t6 = 0;
    if (t7 == 0) {
        // 0x00521898
        charge(ctx, 2);
        t6 = 16;
        a0 = sll(a0, 16);
    }
    // 0x005218a0
    charge(ctx, 4);
    t7 = lui(0xFF00);
    t7 = a0 & t7;
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = lui(0xF000);
    if (!cc) {
        // 0x005218b0
        charge(ctx, 2);
        t6 = addiu(t6, 8);
        a0 = sll(a0, 8);
    }
    // 0x005218b8
    charge(ctx, 3);
    t7 = a0 & t7;
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = lui(0xC000);
    if (!cc) {
        // 0x005218c4
        charge(ctx, 2);
        t6 = addiu(t6, 4);
        a0 = sll(a0, 4);
    }
    // 0x005218cc
    charge(ctx, 3);
    t7 = a0 & t7;
    if (t7 == 0) {
        // 0x005218d8
        charge(ctx, 2);
        t6 = addiu(t6, 2);
        a0 = sll(a0, 2);
    }
    // 0x005218e0
    charge(ctx, 2);
    t7 = 0x40000000;
    if (i64(a0) >= 0) {
        // 0x005218e8
        charge(ctx, 4);
        t6 = addiu(t6, 1);
        t7 = a0 & t7;
        v0 = 32;
        if (t7 != 0) {
            goto L_005218f8;
        }
        // 0x005218fc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005218f8:
    charge(ctx, 1);
    v0 = t6;
    // 0x005218fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00521908 _lo0bits -- 188 bytes; leaf frame (no stack)
// _lo0bits(px $a0) -> $v0: the number of trailing zero bits of *px, and *px shifted right by that count (stored back);
// 32 (and *px unchanged) for 0.
void _lo0bits(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00521908
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(t6, a0, 0);
    t7 = t6 & 0x7;
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = t6 & 0x1;
    if (!cc) {
        // 0x00521918
        charge(ctx, 2);
        v0 = 0;
        if (t7 != 0) {
            // 0x00521944 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x00521920
        charge(ctx, 3);
        t7 = t6 & 0x2;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = srl(t6, 2);
        if (cc) {
            // 0x0052193c
            charge(ctx, 2);
            v0 = 2;
            backedge(ctx);
        } else {
            // 0x0052192c
            charge(ctx, 2);
            t7 = srl(t6, 1);
            v0 = 1;
        }
        // 0x00521934 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(t7, a0, 0);
        return;
    }
    // 0x0052194c
    charge(ctx, 3);
    t7 = t6 & 0xFFFF;
    t5 = 0;
    if (t7 == 0) {
        // 0x00521958
        charge(ctx, 2);
        t5 = 16;
        t6 = srl(t6, 16);
    }
    // 0x00521960
    charge(ctx, 3);
    t7 = t6 & 0xFF;
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t6 & 0xF;
    if (!cc) {
        // 0x0052196c
        charge(ctx, 3);
        t5 = addiu(t5, 8);
        t6 = srl(t6, 8);
        t7 = t6 & 0xF;
    }
    // 0x00521978
    charge(ctx, 2);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t6 & 0x3;
    if (!cc) {
        // 0x00521980
        charge(ctx, 3);
        t5 = addiu(t5, 4);
        t6 = srl(t6, 4);
        t7 = t6 & 0x3;
    }
    // 0x0052198c
    charge(ctx, 2);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t6 & 0x1;
    if (!cc) {
        // 0x00521994
        charge(ctx, 3);
        t5 = addiu(t5, 2);
        t6 = srl(t6, 2);
        t7 = t6 & 0x1;
    }
    // 0x005219a0
    charge(ctx, 2);
    if (t7 != 0) {
        sw(t6, a0, 0);
        // 0x005219bc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = t5;
        return;
    }
    // 0x005219a8
    charge(ctx, 4);
    t5 = addiu(t5, 1);
    t6 = srl(t6, 1);
    v0 = 32;
    if (t6 == 0) {
        backedge(ctx);
        // 0x00521944 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005219b8
    charge(ctx, 1);
    sw(t6, a0, 0);
    // 0x005219bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t5;
}

// 0x00521E70 __mcmp -- 100 bytes; leaf frame (no stack)
// __mcmp(a $a0, b $a1) -> $v0: compare two Bigints: the word-count difference when the counts differ, else -1 / 0 / 1
// from the most significant differing 32-bit word (unsigned).
void __mcmp(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00521e70
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(t7, a0, bigint::kWds);
    lw(t6, a1, bigint::kWds);
    t7 = subu(t7, t6);
    v0 = t7;
    if (t7 == 0) {
        // 0x00521e84: same word counts: compare from the most significant word down
        charge(ctx, 6);
        t6 = sll(t6, 2);
        a0 = addiu(a0, bigint::kX);
        t7 = addiu(a1, bigint::kX);
        t3 = addu(a0, t6);
        a1 = addu(t7, t6);
        t3 = addiu(t3, -4);
        for (;;) {
            // 0x00521e9c: words differ: -1 / 1 by the unsigned order
            charge(ctx, 9);
            a1 = addiu(a1, -4);
            lw(t4, t3, 0);
            v0 = si(-1);
            lw(t5, a1, 0);
            t7 = 1;
            t2 = sltu(a0, t3);
            t6 = sltu(t4, t5);
            if (t6 == 0) v0 = t7;
            if (t4 != t5) {
                break;
            }
            // 0x00521ec0: equal so far: next lower word (none left: 0)
            charge(ctx, 2);
            if (t2 == 0) {
                goto L_00521ec8_4;
            }
            t3 = addiu(t3, -4);
            backedge(ctx);
        }
    }
    // 0x00521ecc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00521ec8_4:
    charge(ctx, 1);
    v0 = 0;
    // 0x00521ecc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00522058 _ulp -- 188 bytes; leaf frame (no stack)
// _ulp(x $a0) -> $v0: the unit in the last place of the double x (in one 64-bit register): 2^(e-52) built from x's
// exponent: a normal power of two when e - 52 is a normal exponent, else the denormal bit (1 << n in the high or low
// word), at least the smallest denormal.
void _ulp(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00522058
    enter(ctx, 9);  // entry check point + this block's cycles
    t6 = 0x7FF00000;
    t7 = dsra32(a0, 0);
    t7 = t7 & t6;
    t5 = lui(0xFCC0);
    t5 = addu(t7, t5);
    t6 = dsll32(t5, 0);
    t7 = subu(0, t5);
    t6 = dsrl32(t6, 0);
    if (i64(t5) > 0) {
        // 0x0052207c: normal result: the exponent field only
        charge(ctx, 8);
        v0 = dsll32(v0, 0);
        t6 = dsll32(t6, 0);
        v0 = dsrl32(v0, 0);
        t7 = si(-1);
        v0 = v0 | t6;
        t7 = dsll32(t7, 0);
        v0 = v0 & t7;
        return;
    }
    // 0x0052209c: denormal result
    charge(ctx, 4);
    t5 = sra(t7, 20);
    t7 = slti(t5, 20);
    if (t7 != 0) {
        // 0x005220ac: the bit lands in the high word
        charge(ctx, 10);
        t7 = 0x80000;
        v0 = dsll32(v0, 0);
        t7 = srav(t7, t5);
        v0 = dsrl32(v0, 0);
        t7 = dsll32(t7, 0);
        t6 = si(-1);
        v0 = v0 | t7;
        t6 = dsll32(t6, 0);
        v0 = v0 & t6;
        return;
    }
    t5 = addiu(t5, -20);
    // 0x005220d4: the bit lands in the low word (at least bit 0)
    charge(ctx, 5);
    v0 = dsll32(v0, 0);
    v0 = dsrl32(v0, 0);
    t7 = slti(t5, 31);
    t6 = nor(0, t5);
    if (t7 == 0) {
        // 0x0052210c
        charge(ctx, 2);
        t6 = 1;
        backedge(ctx);
    } else {
        // 0x005220e8
        charge(ctx, 2);
        t7 = 1;
        t6 = sllv(t7, t6);
    }
    // 0x005220f0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    t7 = si(-1);
    t6 = dsll32(t6, 0);
    t7 = dsll32(t7, 0);
    t6 = dsrl32(t6, 0);
    v0 = v0 & t7;
    v0 = v0 | t6;
}

// 0x00522118 _b2d -- 424 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s4 sp+0x20, s2 sp+0x10, s3 sp+0x18, ra sp+0x28
// _b2d(a $a0, e $a1) -> $v0: the top 53 bits of Bigint a as a double in [1, 2) (exponent 0x3FF; the high word's
// leading zeros from _hi0bits decide the shifts across the top three words) and *e = the number of significant bits in
// the top word (32 - leading zeros).
void _b2d(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00522118
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s4, sp, 0x20);
    s0 = a1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s4 = addiu(a0, bigint::kX);
    sd(ra, sp, 0x28);
    lw(t7, a0, 16);
    t7 = sll(t7, 2);
    s1 = addu(s4, t7);
    s1 = addiu(s1, -4);
    lw(s3, s1, 0);
    a0 = s3;
    jal(ctx, 0x522150u, gen::fn__hi0bits_00521888);
    t7 = 32;
    t6 = slti(v0, 11);
    t7 = subu(t7, v0);
    sw(t7, s0, 0);
    if (t6 == 0) {
        // 0x005221fc
        charge(ctx, 3);
        t7 = sltu(s4, s1);
        t4 = 0;
        if (t7 != 0) {
            // 0x00522208
            charge(ctx, 2);
            s1 = addiu(s1, -4);
            lw(t4, s1, 0);
        }
        // 0x00522210
        charge(ctx, 3);
        v0 = addiu(v0, -11);
        t6 = subu(0, v0);
        if (v0 == 0) {
            // 0x00522284
            charge(ctx, 15);
            t7 = 0x3FF00000;
            s2 = dsll32(s2, 0);
            t7 = s3 | t7;
            s2 = dsrl32(s2, 0);
            t7 = dsll32(t7, 0);
            t6 = si(-1);
            t7 = dsrl32(t7, 0);
            t5 = dsll32(t4, 0);
            t7 = dsll32(t7, 0);
            t6 = dsll32(t6, 0);
            s2 = s2 | t7;
            t5 = dsrl32(t5, 0);
            s2 = s2 & t6;
            s2 = s2 | t5;
            backedge(ctx);
        } else {
            // 0x0052221c
            charge(ctx, 14);
            t7 = sllv(s3, v0);
            t6 = srlv(t4, t6);
            s2 = dsll32(s2, 0);
            t7 = t7 | t6;
            s2 = dsrl32(s2, 0);
            t6 = 0x3FF00000;
            t5 = sltu(s4, s1);
            t7 = t7 | t6;
            s3 = 0;
            t7 = dsll32(t7, 0);
            t7 = dsrl32(t7, 0);
            t7 = dsll32(t7, 0);
            s2 = s2 | t7;
            if (t5 != 0) {
                // 0x00522254
                charge(ctx, 1);
                lw(s3, s1, -4);
            }
            // 0x00522258
            charge(ctx, 11);
            t7 = subu(0, v0);
            t6 = sllv(t4, v0);
            t7 = srlv(s3, t7);
            t5 = si(-1);
            t6 = t6 | t7;
            t5 = dsll32(t5, 0);
            t6 = dsll32(t6, 0);
            s2 = s2 & t5;
            t6 = dsrl32(t6, 0);
            s2 = s2 | t6;
            backedge(ctx);
        }
    } else {
        // 0x0052216c
        charge(ctx, 14);
        t7 = 11;
        t6 = 0x3FF00000;
        t7 = subu(t7, v0);
        s2 = dsll32(s2, 0);
        t7 = srlv(s3, t7);
        s2 = dsrl32(s2, 0);
        t7 = t7 | t6;
        t5 = sltu(s4, s1);
        t7 = dsll32(t7, 0);
        t4 = 0;
        t7 = dsrl32(t7, 0);
        t7 = dsll32(t7, 0);
        s2 = s2 | t7;
        if (t5 != 0) {
            // 0x005221a4
            charge(ctx, 1);
            lw(t4, s1, -4);
        }
        // 0x005221a8
        charge(ctx, 12);
        t6 = 11;
        t7 = addiu(v0, 21);
        t6 = subu(t6, v0);
        t7 = sllv(s3, t7);
        t6 = srlv(t4, t6);
        t5 = si(-1);
        t7 = t7 | t6;
        t5 = dsll32(t5, 0);
        t7 = dsll32(t7, 0);
        s2 = s2 & t5;
        t7 = dsrl32(t7, 0);
        s2 = s2 | t7;
    }
    // 0x005221d8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s2;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00522440 _ratio -- 180 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// _ratio(a $a0, b $a1) -> $v0: the double a / b of two Bigints for strtod's correction loop: _b2d of each (their
// top-word bit counts and the word-count difference x32 give the binary exponent difference), the difference folded
// into one operand's exponent field, then dpdiv.
void _ratio(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00522440
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s0 = a1;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s1 = a0;
    a1 = sp;
    jal(ctx, 0x52245Cu, gen::fn__b2d_00522118);
    s2 = v0;
    a0 = s0;
    a1 = addiu(sp, 0x4);
    jal(ctx, 0x52246Cu, gen::fn__b2d_00522118);
    lw(t7, s0, 16);
    t4 = dsra32(s2, 0);
    lw(t5, s1, 16);
    t3 = dsra32(v0, 0);
    lw(t6, sp, 0x4);
    t5 = subu(t5, t7);
    lw(t7, sp, 0x0);
    t5 = sll(t5, 5);
    t7 = subu(t7, t6);
    t7 = addu(t7, t5);
    t6 = sll(t7, 20);
    t4 = addu(t4, t6);
    t3 = subu(t3, t6);
    t4 = dsll32(t4, 0);
    t3 = dsll32(t3, 0);
    if (i64(t7) <= 0) {
        // 0x005224e4
        charge(ctx, 4);
        v0 = dsll32(v0, 0);
        v0 = dsrl32(v0, 0);
        v0 = v0 | t3;
        backedge(ctx);
    } else {
        // 0x005224b4
        charge(ctx, 3);
        s2 = dsll32(s2, 0);
        s2 = dsrl32(s2, 0);
        s2 = s2 | t4;
    }
    // 0x005224c0
    charge(ctx, 9);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x5224C4u, gen::fn_dpdiv_00531480);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005224F8 _mprec_log10 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// _mprec_log10(n $a0) -> $v0: the double 10^n: the table of exact powers at 0x7BEB78 for n < 24, else 1.0 multiplied
// by 10.0 n times (dpmul).
void _mprec_log10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005224f8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1023;
    sd(s0, sp, 0x0);
    v0 = dsll32(v0, 20);
    sd(ra, sp, 0x8);
    t7 = slti(a0, 24);
    s0 = a0;
    if (t7 == 0) {
        // 0x0052253c
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            ld(s0, sp, 0x0);
            backedge(ctx);
        } else {
            // 0x00522544
            charge(ctx, 1);
            a1 = 4105;
            for (;;) {
                // 0x00522548
                charge(ctx, 6);
                a0 = v0;
                a1 = dsll32(a1, 18);
                s0 = addiu(s0, -1);
                jal(ctx, 0x522550u, gen::fn_dpmul_00531230);
                a1 = 4105;
                if (i64(s0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00522560
            charge(ctx, 2);
            ld(s0, sp, 0x0);
            backedge(ctx);
        }
    } else {
        // 0x00522518
        charge(ctx, 6);
        t7 = 0x7C0000;
        t6 = sll(a0, 3);
        t7 = addiu(t7, -5256);  // &0x7BEB78
        t6 = addu(t6, t7);
        ld(v0, t6, 0);
        ld(s0, sp, 0x0);
    }
    // 0x00522530 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005236F0 copysign -- 60 bytes; leaf frame (no stack)
// copysign(x $a0, y $a1) -> $v0: the double x with y's sign bit (bit 63); doubles travel in one 64-bit register each.
void copysign(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x005236f0
    enter(ctx, 15);  // entry check point + this block's cycles
    t5 = 0x7FFF0000;
    t7 = dsra32(a0, 0);
    t4 = dsra32(a1, 0);
    t5 = t5 | 0xFFFF;
    t6 = lui(0x8000);
    t7 = t7 & t5;
    t4 = t4 & t6;
    t5 = dsll32(a0, 0);
    t7 = t7 | t4;
    t5 = dsrl32(t5, 0);
    t7 = dsll32(t7, 0);
    t7 = dsrl32(t7, 0);
    t7 = dsll32(t7, 0);
    v0 = t5 | t7;
}

// 0x005237B0 scalbn -- 384 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// scalbn(x $a0, n $a1) -> $v0: x * 2^n by editing the exponent field. Zero returns x; a denormal x is first scaled by
// 2^54 (n < -50000 then underflows); NaN / Inf (exponent 0x7FF) return x + x; an exponent pushed past 0x7FE overflows
// to copysign(huge, x) * huge, one below -53 underflows to copysign(tiny, x) * tiny (huge / tiny at 0x7BECC0 /
// 0x7BECB8); results that become denormal are formed at exponent + 54 and multiplied by 2^-54.
void scalbn(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005237b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t4 = dsra32(a0, 0);
    sd(s1, sp, 0x8);
    t6 = dsll32(a0, 0);
    sd(s0, sp, 0x0);
    v0 = a0;
    s1 = 0x7FF00000;
    sd(ra, sp, 0x10);
    t7 = t4 & s1;
    s0 = a1;
    t5 = sra(t7, 20);
    t6 = dsra32(t6, 0);
    if (t5 == 0) {
        // 0x005237e4
        charge(ctx, 6);
        t7 = 0x7FFF0000;
        t7 = t7 | 0xFFFF;
        t7 = t4 & t7;
        t7 = t6 | t7;
        a1 = 1077;
        if (t7 != 0) {
            // 0x005237fc
            charge(ctx, 10);
            a1 = dsll32(a1, 20);
            jal(ctx, 0x5237FCu, gen::fn_dpmul_00531230);
            t4 = dsra32(v0, 0);
            t6 = lui(0xFFFF);
            t7 = t4 & s1;
            t6 = t6 | 0x3CB0;
            t7 = sra(t7, 20);
            t6 = slt(s0, t6);
            t5 = addiu(t7, -54);
            if (t6 == 0) {
                goto L_0052384c;
            }
            // 0x00523824
            charge(ctx, 3);
            t7 = 0x7C0000;
            a0 = v0;
            ld(a1, t7, -4936);  // 0x7BECB8
        L_00523830:
            charge(ctx, 2);
            jal(ctx, 0x523830u, gen::fn_dpmul_00531230);
            goto L_00523838;
        }
    L_00523838:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x0052383c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0052384c:
    charge(ctx, 3);
    t7 = 2047;
    cc = t5 != t7;  // the condition, before the delay slot changes it
    t5 = addu(t5, s0);
    if (cc) {
        // 0x0052386c
        charge(ctx, 3);
        t7 = slti(t5, 2047);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (!cc) {
            // 0x00523878
            charge(ctx, 2);
            t7 = lui(0x800F);
            if (i64(t5) <= 0) {
                // 0x005238ac
                charge(ctx, 3);
                t7 = slti(t5, -53);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = 0xC350;
                if (cc) {
                    // 0x005238f0
                    charge(ctx, 16);
                    t7 = lui(0x800F);
                    t5 = addiu(t5, 54);
                    t7 = t7 | 0xFFFF;
                    t5 = sll(t5, 20);
                    t7 = t4 & t7;
                    t6 = dsll32(v0, 0);
                    t7 = t7 | t5;
                    t6 = dsrl32(t6, 0);
                    t7 = dsll32(t7, 0);
                    a1 = 969;
                    t7 = dsrl32(t7, 0);
                    a1 = dsll32(a1, 20);
                    t7 = dsll32(t7, 0);
                    v0 = t6 | t7;
                    a0 = v0;
                    backedge(ctx);
                } else {
                    // 0x005238b8
                    charge(ctx, 3);
                    t7 = slt(t7, s0);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = 0x7C0000;
                    if (!cc) {
                        goto L_005238c4;
                    }
                    // 0x005238e0
                    charge(ctx, 4);
                    t7 = 0x7C0000;
                    a1 = v0;
                    ld(s0, t7, -4936);  // 0x7BECB8
                    backedge(ctx);
                L_005238cc:
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x5238CCu, gen::fn_copysign_005236f0);
                    a0 = v0;
                    a1 = s0;
                    backedge(ctx);
                }
                goto L_00523830;
            }
            // 0x00523880
            charge(ctx, 11);
            t5 = sll(t5, 20);
            t7 = t7 | 0xFFFF;
            t6 = dsll32(v0, 0);
            t7 = t4 & t7;
            t6 = dsrl32(t6, 0);
            t7 = t7 | t5;
            t7 = dsll32(t7, 0);
            t7 = dsrl32(t7, 0);
            t7 = dsll32(t7, 0);
            v0 = t6 | t7;
            backedge(ctx);
            goto L_00523838;
        }
    L_005238c4:
        charge(ctx, 2);
        a1 = v0;
        ld(s0, t7, -4928);
        goto L_005238cc;
    }
    // 0x00523858
    charge(ctx, 5);
    a0 = v0;
    a1 = v0;
    jal(ctx, 0x52385Cu, gen::fn_dpadd_00531170);
    ld(s0, sp, 0x0);
    backedge(ctx);
    // 0x0052383c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00523980 copysignf -- 40 bytes; leaf frame (no stack)
// copysignf(x $f12, y $f13) -> $f0: x with y's sign bit.
void copysignf(EEContext& ctx) {
    using namespace hg;
    Gpr t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00523980
    enter(ctx, 10);  // entry check point + this block's cycles
    mfc1(t5, f12);
    t4 = 0x7FFF0000;
    mfc1(t7, f13);
    t4 = t4 | 0xFFFF;
    t6 = lui(0x8000);
    t5 = t5 & t4;
    t7 = t7 & t6;
    t5 = t5 | t7;
    mtc1(t5, f0);
}

// 0x005239A8 scalbnf -- 172 bytes; frame 0x10: ra sp+0x0, f20 sp+0x8
// scalbnf(n $a0, x $f12) -> $f0 (argument order of this build: the integer in $a0): x * 2^n by editing the 8-bit
// exponent: zero and denormal x (exponent 0) are returned as they are; an exponent >= 256 overflows and one <= 0
// underflows to copysignf(big or small constant at 0x7BECD8 / 0x7BECDC, x) * that constant (EE singles: no infinities,
// the big product saturates).
void scalbnf(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005239a8
    enter(ctx, 14);  // entry check point + this block's cycles
    t7 = 0x7FFF0000;
    mfc1(t3, f12);
    t7 = t7 | 0xFFFF;
    mfc1(t4, f12);
    sp = addiu(sp, -0x10);
    t7 = t3 & t7;
    t6 = 0x7F0000;
    sd(ra, sp, 0x0);
    t6 = t6 | 0xFFFF;  // &0x7FFFFF
    swc1(f20, sp, 0x8);
    t5 = srl(t7, 23);
    t6 = sltu(t6, t7);
    t5 = addu(t5, a0);
    if (t6 != 0) {
        // 0x005239e0
        charge(ctx, 3);
        t7 = slti(t5, 256);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (!cc) {
            // 0x005239ec
            charge(ctx, 2);
            t7 = lui(0x807F);
            if (i64(t5) <= 0) {
                // 0x00523a18
                charge(ctx, 4);
                t7 = 0xC350;
                t7 = slt(t7, a0);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = 0x7C0000;
                if (!cc) {
                    // 0x00523a28
                    charge(ctx, 1);
                    t7 = 0x7C0000;
                    goto L_00523a2c;
                }
                // 0x00523a4c
                charge(ctx, 2);
                t7 = addiu(t7, -4900);
                backedge(ctx);
            L_00523a30:
                charge(ctx, 7);
                mov_s(f13, f12);
                lwc1(f20, t7, 0);
                mov_s(f12, f20);
                jal(ctx, 0x523A38u, gen::fn_copysignf_00523980);
                mul_s(f0, f0, f20);
                mfc1(t4, f0);
                backedge(ctx);
            } else {
                // 0x005239f4
                charge(ctx, 4);
                t6 = sll(t5, 23);
                t7 = t7 | 0xFFFF;
                t7 = t3 & t7;
                t4 = t7 | t6;
            }
            // 0x00523a04 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            mtc1(t4, f0);
            ld(ra, sp, 0x0);
            lwc1(f20, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_00523a2c:
        charge(ctx, 1);
        t7 = addiu(t7, -4904);
        goto L_00523a30;
    }
    // 0x00523a04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    mtc1(t4, f0);
    ld(ra, sp, 0x0);
    lwc1(f20, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00523B38 eofread -- 8 bytes; leaf frame (no stack)
// eofread() -> $v0 = 0: the read callback of sscanf's string FILE (end of input at once).
void eofread(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00523b38
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00525A10 _strtol_r -- 576 bytes; frame 0x60: s1 sp+0x18, s3 sp+0x28, s7 sp+0x48, s0 sp+0x10, s2 sp+0x20, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, fp sp+0x50, ra sp+0x58
// _strtol_r(reent $a0, s $a1, endptr $a2, base $a3) -> $v0: strtol per C: skips <ctype.h> spaces (the class table at
// 0x7BE9C8), an optional sign, the 0x / 0X prefix for base 0 or 16 (base 0: 0 -> octal, else decimal), then digits /
// letters below the base. The overflow cut-off is LONG_MAX (or -LONG_MIN) divided and reduced by the base through
// __udivdi3 / __umoddi3 (long is 64-bit here); on overflow the result is LONG_MAX or LONG_MIN and the _reent's errno =
// ERANGE (34). *endptr = the first unused byte, or s when no digit was converted.
void _strtol_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00525a10
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    t7 = 0x7C0000;
    sd(s1, sp, 0x18);
    t5 = addiu(t7, -5688);  // &0x7BE9C8
    sd(s3, sp, 0x28);
    sd(s7, sp, 0x48);
    s1 = a1;
    sd(s0, sp, 0x10);
    s3 = a3;
    sd(s2, sp, 0x20);
    s7 = a1;
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    sd(fp, sp, 0x50);
    sd(ra, sp, 0x58);
    sw(a0, sp, 0x0);
    sw(a2, sp, 0x4);
    sw(zero, sp, 0x8);
    for (;;) {
        // 0x00525a5c
        charge(ctx, 7);
        lb(s0, s1, 0);
        t6 = addu(s0, t5);
        lbu(t7, t6, 0);
        t7 = t7 & 0x8;
        s1 = addiu(s1, 1);
        if (t7 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00525a78
    charge(ctx, 3);
    t7 = 45;
    cc = s0 != t7;  // the condition, before the delay slot changes it
    t7 = 43;
    if (!cc) {
        // 0x00525a84
        charge(ctx, 3);
        lb(s0, s1, 0);
        t6 = 1;
        sw(t6, sp, 0x8);
        goto L_00525a90;
    }
    // 0x00525c40
    charge(ctx, 2);
    if (s0 != t7) {
        backedge(ctx);
    } else {
        // 0x00525c48
        charge(ctx, 2);
        lb(s0, s1, 0);
        backedge(ctx);
    L_00525a90:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00525a94
    charge(ctx, 2);
    t7 = 16;
    if (s3 != 0) {
        // 0x00525a9c
        charge(ctx, 2);
        if (s3 == t7) {
            goto L_00525aa4;
        }
        goto L_00525ad0;
    }
L_00525aa4:
    charge(ctx, 3);
    t7 = 48;
    cc = s0 != t7;  // the condition, before the delay slot changes it
    t7 = 120;
    if (!cc) {
        // 0x00525ab0
        charge(ctx, 3);
        lb(t6, s1, 0);
        cc = t6 == t7;  // the condition, before the delay slot changes it
        t7 = 88;
        if (!cc) {
            // 0x00525abc
            charge(ctx, 2);
            if (t6 == t7) {
                goto L_00525ac4;
            }
            goto L_00525ad0;
        }
    L_00525ac4:
        charge(ctx, 3);
        lb(s0, s1, 1);
        s3 = 16;
        s1 = addiu(s1, 2);
    }
L_00525ad0:
    charge(ctx, 2);
    lw(t6, sp, 0x8);
    if (s3 == 0) {
        // 0x00525ad8
        charge(ctx, 5);
        s3 = 8;
        t6 = s0 ^ 0x30;
        t7 = 10;
        if (t6 != 0) s3 = t7;
        lw(t6, sp, 0x8);
    }
    // 0x00525aec
    charge(ctx, 19);
    s2 = si(-1);
    t7 = si(-2);
    s2 = dsll32(s2, 31);
    t7 = dsrl(t7, 1);
    s5 = s3;
    if (t6 == 0) s2 = t7;
    a1 = s5;
    a0 = s2;
    s4 = 0;
    jal(ctx, 0x525B0Cu, gen::fn___umoddi3_00530578);
    fp = dsll32(v0, 0);
    a0 = s2;
    a1 = s5;
    fp = dsra32(fp, 0);
    jal(ctx, 0x525B20u, gen::fn___udivdi3_0052fe98);
    s2 = v0;
    t7 = 0x7C0000;
    v0 = 0;
    s6 = addiu(t7, -5688);  // &0x7BE9C8
    for (;;) {
        // 0x00525b38
        charge(ctx, 5);
        t7 = addu(s0, s6);
        lbu(t5, t7, 0);
        t6 = t5 & 0x4;
        t7 = t5 & 0x3;
        if (t6 != 0) {
            // 0x00525b4c
            charge(ctx, 1);
            s0 = addiu(s0, -48);
            goto L_00525b50;
        }
        // 0x00525c24
        charge(ctx, 2);
        t6 = addiu(s0, -87);
        if (t7 == 0) {
            backedge(ctx);
        } else {
            // 0x00525c2c
            charge(ctx, 5);
            t7 = addiu(s0, -55);
            t5 = t5 & 0x1;
            s0 = t7;
            if (t5 == 0) s0 = t6;
            backedge(ctx);
        L_00525b50:
            charge(ctx, 3);
            t7 = slt(s0, s3);
            if (t7 != 0) {
                // 0x00525b5c
                charge(ctx, 2);
                t7 = sltu(s2, v0);
                if (i64(s4) >= 0) {
                    // 0x00525b64
                    charge(ctx, 2);
                    if (t7 != 0) {
                        s4 = si(-1);
                    } else {
                        // 0x00525b6c
                        charge(ctx, 2);
                        a0 = v0;
                        if (v0 == s2) {
                            // 0x00525b74
                            charge(ctx, 3);
                            t7 = slt(fp, s0);
                            if (t7 == 0) {
                                goto L_00525b90;
                            }
                            goto L_00525b80;
                        }
                    L_00525b90:
                        charge(ctx, 5);
                        a1 = s5;
                        jal(ctx, 0x525B90u, gen::fn___muldi3_0052ea78);
                        s4 = 1;
                        v0 = s0 + v0;
                        backedge(ctx);
                    }
                    goto L_00525b84;
                }
            L_00525b80:
                charge(ctx, 1);
                s4 = si(-1);
            L_00525b84:
                charge(ctx, 3);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x00525ba4
    charge(ctx, 2);
    lw(t6, sp, 0x8);
    if (i64(s4) >= 0) {
        // 0x00525c18
        charge(ctx, 3);
        t7 = 0 - v0;
        if (t6 != 0) v0 = t7;
        backedge(ctx);
    } else {
        // 0x00525bac
        charge(ctx, 9);
        lw(t6, sp, 0x0);
        t7 = 34;
        v0 = si(-1);
        sw(t7, t6, 0);
        v0 = dsll32(v0, 31);
        t7 = si(-2);
        lw(t6, sp, 0x8);
        t7 = dsrl(t7, 1);
        if (t6 == 0) v0 = t7;
    }
    // 0x00525bd0
    charge(ctx, 3);
    lw(t7, sp, 0x4);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = addiu(s1, -1);
    if (!cc) {
        // 0x00525bdc
        charge(ctx, 3);
        lw(t6, sp, 0x4);
        if (s4 != 0) s7 = t7;
        sw(s7, t6, 0);
    }
    // 0x00525be8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00525C50 strtol -- 48 bytes; frame 0x10: ra sp+0x0
// strtol(s $a0, endptr $a1, base $a2) -> $v0: _strtol_r(_impure_ptr, s, endptr, base).
void strtol(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00525c50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t6 = a0;
    sd(ra, sp, 0x0);
    t7 = 0x780000;
    t5 = a1;
    lw(a0, t7, 12080);  // 0x782F30
    a3 = a2;
    ld(ra, sp, 0x0);
    a1 = t6;
    a2 = t5;
    sp = addiu(sp, 0x10);
    gen::fn__strtol_r_00525a10(ctx);  // tail call
}

// 0x00525C80 _strtoul_r -- 532 bytes; frame 0x60: s1 sp+0x18, s2 sp+0x20, s7 sp+0x48, s0 sp+0x10, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, fp sp+0x50, ra sp+0x58
// _strtoul_r(reent $a0, s $a1, endptr $a2, base $a3) -> $v0: strtoul per C, the same scan as _strtol_r with ULONG_MAX
// as the cut-off (64-bit) and a leading '-' negating the result; overflow gives ULONG_MAX and errno = ERANGE.
void _strtoul_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00525c80
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    t7 = 0x7C0000;
    sd(s1, sp, 0x18);
    t5 = addiu(t7, -5688);  // &0x7BE9C8
    sd(s2, sp, 0x20);
    sd(s7, sp, 0x48);
    s1 = a1;
    sd(s0, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x28);
    s7 = a1;
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    sd(fp, sp, 0x50);
    sd(ra, sp, 0x58);
    sw(a0, sp, 0x0);
    sw(a2, sp, 0x4);
    sw(zero, sp, 0x8);
    for (;;) {
        // 0x00525ccc
        charge(ctx, 7);
        lb(s0, s1, 0);
        t6 = addu(s0, t5);
        lbu(t7, t6, 0);
        t7 = t7 & 0x8;
        s1 = addiu(s1, 1);
        if (t7 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00525ce8
    charge(ctx, 3);
    t7 = 45;
    cc = s0 != t7;  // the condition, before the delay slot changes it
    t7 = 43;
    if (!cc) {
        // 0x00525cf4
        charge(ctx, 3);
        lb(s0, s1, 0);
        t6 = 1;
        sw(t6, sp, 0x8);
        goto L_00525d00;
    }
    // 0x00525e84
    charge(ctx, 2);
    if (s0 != t7) {
        backedge(ctx);
    } else {
        // 0x00525e8c
        charge(ctx, 2);
        lb(s0, s1, 0);
        backedge(ctx);
    L_00525d00:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00525d04
    charge(ctx, 2);
    t7 = 16;
    if (s2 != 0) {
        // 0x00525d0c
        charge(ctx, 2);
        if (s2 == t7) {
            goto L_00525d14;
        }
        goto L_00525d40;
    }
L_00525d14:
    charge(ctx, 3);
    t7 = 48;
    cc = s0 != t7;  // the condition, before the delay slot changes it
    t7 = 120;
    if (!cc) {
        // 0x00525d20
        charge(ctx, 3);
        lb(t6, s1, 0);
        cc = t6 == t7;  // the condition, before the delay slot changes it
        t7 = 88;
        if (!cc) {
            // 0x00525d2c
            charge(ctx, 2);
            if (t6 == t7) {
                goto L_00525d34;
            }
            goto L_00525d40;
        }
    L_00525d34:
        charge(ctx, 3);
        lb(s0, s1, 1);
        s2 = 16;
        s1 = addiu(s1, 2);
    }
L_00525d40:
    charge(ctx, 2);
    s5 = s2;
    if (s2 == 0) {
        // 0x00525d48
        charge(ctx, 5);
        s2 = 8;
        t6 = s0 ^ 0x30;
        t7 = 10;
        if (t6 != 0) s2 = t7;
        s5 = s2;
    }
    // 0x00525d5c
    charge(ctx, 13);
    a0 = si(-1);
    a1 = s5;
    s3 = 0;
    jal(ctx, 0x525D64u, gen::fn___udivdi3_0052fe98);
    s4 = v0;
    a0 = si(-1);
    a1 = s5;
    jal(ctx, 0x525D74u, gen::fn___umoddi3_00530578);
    fp = dsll32(v0, 0);
    t7 = 0x7C0000;
    fp = dsra32(fp, 0);
    s6 = addiu(t7, -5688);  // &0x7BE9C8
    v0 = 0;
    for (;;) {
        // 0x00525d90
        charge(ctx, 5);
        t7 = addu(s0, s6);
        lbu(t5, t7, 0);
        t6 = t5 & 0x4;
        t7 = t5 & 0x3;
        if (t6 != 0) {
            // 0x00525da4
            charge(ctx, 1);
            s0 = addiu(s0, -48);
            goto L_00525da8;
        }
        // 0x00525e68
        charge(ctx, 2);
        t6 = addiu(s0, -87);
        if (t7 == 0) {
            backedge(ctx);
        } else {
            // 0x00525e70
            charge(ctx, 5);
            t7 = addiu(s0, -55);
            t5 = t5 & 0x1;
            s0 = t7;
            if (t5 == 0) s0 = t6;
            backedge(ctx);
        L_00525da8:
            charge(ctx, 3);
            t7 = slt(s0, s2);
            if (t7 != 0) {
                // 0x00525db4
                charge(ctx, 2);
                t7 = sltu(s4, v0);
                if (i64(s3) >= 0) {
                    // 0x00525dbc
                    charge(ctx, 2);
                    if (t7 != 0) {
                        s3 = si(-1);
                    } else {
                        // 0x00525dc4
                        charge(ctx, 2);
                        a0 = v0;
                        if (v0 == s4) {
                            // 0x00525dcc
                            charge(ctx, 3);
                            t7 = slt(fp, s0);
                            if (t7 == 0) {
                                goto L_00525de8;
                            }
                            goto L_00525dd8;
                        }
                    L_00525de8:
                        charge(ctx, 5);
                        a1 = s5;
                        jal(ctx, 0x525DE8u, gen::fn___muldi3_0052ea78);
                        s3 = 1;
                        v0 = s0 + v0;
                        backedge(ctx);
                    }
                    goto L_00525ddc;
                }
            L_00525dd8:
                charge(ctx, 1);
                s3 = si(-1);
            L_00525ddc:
                charge(ctx, 3);
                lb(s0, s1, 0);
                s1 = addiu(s1, 1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x00525dfc
    charge(ctx, 2);
    lw(t6, sp, 0x8);
    if (i64(s3) >= 0) {
        // 0x00525e5c
        charge(ctx, 3);
        t7 = 0 - v0;
        if (t6 != 0) v0 = t7;
        backedge(ctx);
    } else {
        // 0x00525e04
        charge(ctx, 4);
        lw(t6, sp, 0x0);
        t7 = 34;
        v0 = si(-1);
        sw(t7, t6, 0);
    }
    // 0x00525e14
    charge(ctx, 3);
    lw(t7, sp, 0x4);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = addiu(s1, -1);
    if (!cc) {
        // 0x00525e20
        charge(ctx, 3);
        lw(t6, sp, 0x4);
        if (s3 != 0) s7 = t7;
        sw(s7, t6, 0);
    }
    // 0x00525e2c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00525E98 strtoul -- 48 bytes; frame 0x10: ra sp+0x0
// strtoul(s $a0, endptr $a1, base $a2) -> $v0: _strtoul_r(_impure_ptr, s, endptr, base).
void strtoul(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00525e98
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t6 = a0;
    sd(ra, sp, 0x0);
    t7 = 0x780000;
    t5 = a1;
    lw(a0, t7, 12080);  // 0x782F30
    a3 = a2;
    ld(ra, sp, 0x0);
    a1 = t6;
    a2 = t5;
    sp = addiu(sp, 0x10);
    gen::fn__strtoul_r_00525c80(ctx);  // tail call
}

// 0x005279B8 exponent -- 208 bytes; frame 0x30
// exponent(p $a0, e $a1, fmtch $a2) -> $v0: vfprintf's exponent writer: stores fmtch ('e' / 'E'), the sign ('+' /
// '-'), then at least two decimal digits of |e| (digits produced backwards into a stack buffer with div by 10, then
// copied); returns the number of bytes written.
void exponent(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29};
    // 0x005279b8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sb(a2, a0, 0);
    if (i64(a1) >= 0) {
        // 0x00527a78
        charge(ctx, 4);
        t7 = 43;
        v0 = addiu(a0, 2);
        sb(t7, a0, 1);
        backedge(ctx);
    } else {
        // 0x005279c4
        charge(ctx, 4);
        t7 = 45;
        a1 = subu(0, a1);
        sb(t7, a0, 1);
        v0 = addiu(a0, 2);
    }
    // 0x005279d4
    charge(ctx, 4);
    t5 = addiu(sp, 0x28);
    t7 = slti(a1, 10);
    t2 = t5;
    if (t7 != 0) {
        // 0x00527a5c
        charge(ctx, 7);
        t7 = 48;
        t6 = addiu(a1, 48);
        sb(t7, v0, 0);
        v0 = addiu(v0, 1);
        sb(t6, v0, 0);
        v0 = addiu(v0, 1);
        backedge(ctx);
    } else {
        // 0x005279e4
        charge(ctx, 4);
        t4 = t5;
        t3 = 10;
        t5 = 10;
        div(a1, t5);
        for (;;) {
            // 0x005279f4
            charge(ctx, 3);
            t4 = addiu(t4, -1);
            if (t5 == 0) {
                brk(ctx, 0x5279FCu, 0x7u);
            }
            // 0x00527a00
            charge(ctx, 8);
            mfhi(t7);
            mflo(t6);
            t7 = addiu(t7, 48);
            mflo(a1);
            sb(t7, t4, 0);
            t6 = slti(t6, 10);
            if (t6 != 0) {
                break;
            }
            div(a1, t5);
            backedge(ctx);
        }
        // 0x00527a20
        charge(ctx, 5);
        t5 = addiu(t4, -1);
        t6 = addiu(a1, 48);
        t7 = sltu(t5, t2);
        sb(t6, t5, 0);
        if (t7 != 0) {
            for (;;) {
                // 0x00527a34
                charge(ctx, 7);
                lbu(t7, t5, 0);
                sb(t7, v0, 0);
                t5 = addiu(t5, 1);
                t7 = sltu(t5, t2);
                v0 = addiu(v0, 1);
                if (t7 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x00527a50 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = subu(v0, a0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
