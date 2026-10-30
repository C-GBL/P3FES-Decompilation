// Slice libc: the soft-float double helpers the compiler calls (pack / unpack, add, sub, mul, div, compare, the int <-> double <-> float conversions).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions and the C standard only
// (ADR-0010: no GPL or newlib source was opened). Pair tests: tests/game/test_libc.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libc.h"

namespace p3fes::recomp_gen {
void fn___fixdfdi_0052ed30(p3fes::EEContext&);
void fn___fixunsdfdi_0052ec28(p3fes::EEContext&);
void fn___floatdidf_0052eac8(p3fes::EEContext&);
void fn___floatdisf_0052eb60(p3fes::EEContext&);
void fn___fpcmp_parts_d_005315d0(p3fes::EEContext&);
void fn___make_dp_00531870(p3fes::EEContext&);
void fn___make_fp_00530d70(p3fes::EEContext&);
void fn___pack_d_00530de0(p3fes::EEContext&);
void fn___pack_f_00530c60(p3fes::EEContext&);
void fn___unpack_d_00530eb8(p3fes::EEContext&);
void fn___unpack_f_00530d18(p3fes::EEContext&);
void fn__fpadd_parts_00530f48(p3fes::EEContext&);
void fn__fpdiv_parts_005314d8(p3fes::EEContext&);
void fn__fpmul_parts_00531288(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_dptoul_005318f8(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace libc;  // the named offsets of p3fes/game/libc.h
namespace gen = ::p3fes::recomp_gen;

// 0x0052EAC8 __floatdidf -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x18, s2 sp+0x10
// __floatdidf(i $a0) -> $v0: the signed 64-bit integer as a double: hi(i) * 2^32 + (unsigned) lo(i) on the soft-float
// helpers (litodp of each half, the unsigned correction +2^32 when lo is negative as an int, dpmul / dpadd).
void __floatdidf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052eac8
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s0 = a0;
    sd(s2, sp, 0x10);
    a0 = dsra32(a0, 0);
    s1 = 1039;
    s0 = dsll32(s0, 0);
    jal(ctx, 0x52EAE8u, gen::fn_litodp_00531720);
    s1 = dsll32(s1, 20);
    a0 = v0;
    a1 = s1;
    jal(ctx, 0x52EAF8u, gen::fn_dpmul_00531230);
    s0 = dsrl32(s0, 0);
    a1 = s1;
    a0 = v0;
    s0 = dsll32(s0, 0);
    jal(ctx, 0x52EB0Cu, gen::fn_dpmul_00531230);
    s0 = dsra32(s0, 0);
    s2 = v0;
    a0 = s0;
    jal(ctx, 0x52EB1Cu, gen::fn_litodp_00531720);
    a1 = 1055;
    a0 = v0;
    a1 = dsll32(a1, 20);
    if (i64(s0) < 0) {
        // 0x0052eb34
        charge(ctx, 2);
        jal(ctx, 0x52EB34u, gen::fn_dpadd_00531170);
    }
    // 0x0052eb3c
    charge(ctx, 9);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x52EB40u, gen::fn_dpadd_00531170);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0052EB60 __floatdisf -- 200 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// __floatdisf(i $a0) -> $f0: the 64-bit integer as a float: the __floatdidf computation, then dptofp (the result
// returned in $f0 through mtc1).
void __floatdisf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052eb60
    enter(ctx, 15);  // entry check point + this block's cycles
    t7 = si(-2048);
    sp = addiu(sp, -0x20);
    t7 = dsrl(t7, 11);
    sd(s2, sp, 0x10);
    t6 = si(-2048);
    sd(s0, sp, 0x0);
    t7 = a0 + t7;
    sd(s1, sp, 0x8);
    t6 = dsrl(t6, 10);
    sd(ra, sp, 0x18);
    t6 = sltu(t6, t7);
    s2 = a0;
    t5 = a0 & 0x7FF;
    t7 = a0 | 0x800;
    if (t6 != 0) {
        // 0x0052eb9c
        charge(ctx, 1);
        if (t5 != 0) s2 = t7;
    }
    // 0x0052eba0
    charge(ctx, 21);
    a0 = dsra32(s2, 0);
    s0 = 1039;
    s0 = dsll32(s0, 20);
    jal(ctx, 0x52EBA8u, gen::fn_litodp_00531720);
    a1 = s0;
    a0 = v0;
    jal(ctx, 0x52EBB4u, gen::fn_dpmul_00531230);
    a1 = s0;
    a0 = v0;
    s0 = dsll32(s2, 0);
    jal(ctx, 0x52EBC4u, gen::fn_dpmul_00531230);
    s0 = dsrl32(s0, 0);
    s1 = v0;
    s0 = dsll32(s0, 0);
    s0 = dsra32(s0, 0);
    a0 = s0;
    jal(ctx, 0x52EBDCu, gen::fn_litodp_00531720);
    a1 = 1055;
    a0 = v0;
    a1 = dsll32(a1, 20);
    if (i64(s0) < 0) {
        // 0x0052ebf4
        charge(ctx, 2);
        jal(ctx, 0x52EBF4u, gen::fn_dpadd_00531170);
    }
    // 0x0052ebfc
    charge(ctx, 11);
    a1 = v0;
    a0 = s1;
    jal(ctx, 0x52EC00u, gen::fn_dpadd_00531170);
    a0 = v0;
    jal(ctx, 0x52EC08u, gen::fn_dptofp_005318a0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0052EC28 __fixunsdfdi -- 264 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// __fixunsdfdi(x $a0) -> $v0: the double as an unsigned 64-bit integer: negative -> 0; hi = dptoul(x / 2^32), lo =
// dptoul(x - hi * 2^32) with a correction when the remainder is negative.
void __fixunsdfdi(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052ec28
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s2 = a0;
    jal(ctx, 0x52EC40u, gen::fn_dpcmp_005316d0);
    a1 = 991;
    a0 = s2;
    a1 = dsll32(a1, 20);
    t7 = 0;
    if (i64(v0) >= 0) {
        // 0x0052ec5c
        charge(ctx, 12);
        jal(ctx, 0x52EC5Cu, gen::fn_dpmul_00531230);
        a0 = v0;
        jal(ctx, 0x52EC64u, gen::fn_dptoul_005318f8);
        s1 = dsll32(v0, 0);
        s1 = dsrl32(s1, 0);
        s1 = dsll32(s1, 0);
        t7 = dsrl(s1, 1);
        t6 = s1 & 0x1;
        t6 = t6 | t7;
        a0 = s1;
        if (i64(s1) < 0) {
            // 0x0052ed14
            charge(ctx, 7);
            a0 = t6;
            jal(ctx, 0x52ED14u, gen::fn___floatdidf_0052eac8);
            a0 = v0;
            a1 = v0;
            jal(ctx, 0x52ED20u, gen::fn_dpadd_00531170);
            a0 = s2;
            backedge(ctx);
        } else {
            // 0x0052ec8c
            charge(ctx, 3);
            jal(ctx, 0x52EC8Cu, gen::fn___floatdidf_0052eac8);
            a0 = s2;
        }
        // 0x0052ec98
        charge(ctx, 10);
        a1 = v0;
        jal(ctx, 0x52EC98u, gen::fn_dpsub_005311c8);
        s0 = 0;
        s2 = v0;
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x52ECACu, gen::fn_dpcmp_005316d0);
        a1 = s2;
        a0 = s0;
        if (i64(v0) >= 0) {
            // 0x0052ecfc
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x52ECFCu, gen::fn_dptoul_005318f8);
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            s1 = s1 + v0;
            backedge(ctx);
        } else {
            // 0x0052ecc0
            charge(ctx, 7);
            jal(ctx, 0x52ECC0u, gen::fn_dpsub_005311c8);
            a0 = v0;
            jal(ctx, 0x52ECC8u, gen::fn_dptoul_005318f8);
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            s1 = s1 - v0;
        }
        // 0x0052ecdc
        charge(ctx, 1);
        t7 = s1;
    }
    // 0x0052ece0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    v0 = t7;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0052ED30 __fixdfdi -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// __fixdfdi(x $a0) -> $v0: the double as a signed 64-bit integer: x < 0 -> -__fixunsdfdi(-x), else __fixunsdfdi(x).
void __fixdfdi(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052ed30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s0 = 0;
    sd(ra, sp, 0x10);
    s1 = a0;
    a1 = s0;
    jal(ctx, 0x52ED48u, gen::fn_dpcmp_005316d0);
    a1 = s1;
    a0 = s0;
    if (i64(v0) >= 0) {
        // 0x0052ed5c
        charge(ctx, 6);
        a0 = s1;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn___fixunsdfdi_0052ec28(ctx);  // tail call
        return;
    }
    // 0x0052ed74
    charge(ctx, 10);
    jal(ctx, 0x52ED74u, gen::fn_dpsub_005311c8);
    a0 = v0;
    jal(ctx, 0x52ED7Cu, gen::fn___fixunsdfdi_0052ec28);
    ld(s0, sp, 0x0);
    v0 = 0 - v0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00530C60 __pack_f -- 180 bytes; leaf frame (no stack)
// __pack_f(fp $a0) -> $f0: an unpacked single (fp-bit layout: +0 class, +4 sign, +8 unbiased exponent, +12 fraction
// with the implicit bit at bit 30) packed into IEEE bits: zero -> +-0; exponent < -126 -> +-0 (no denormals); normal
// -> (exponent + 127) << 23 | fraction >> 7 (no rounding; exponent 128 packs as the ordinary field 0xFF, which the EE
// reads as a number); NaN / Inf classes and exponents past 128 -> exponent 0xFF with fraction 0x7FFFFF (0x7FFFFFFF /
// 0xFFFFFFFF: the EE's largest magnitude, not an IEEE infinity).
void __pack_f(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0};
    // 0x00530c60
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(t6, a0, parts::kClass);
    t3 = 0;
    lw(t5, a0, parts::kFracF);
    t7 = sltiu(t6, 2);
    lw(t2, a0, parts::kSign);
    if (t7 == 0) {
        // 0x00530c78
        charge(ctx, 3);
        t7 = t6 ^ 0x4;
        if (t7 == 0) {
            t5 = 0x7F0000;
        L_00530d08:
            charge(ctx, 3);
            t3 = 255;
            t5 = t5 | 0xFFFF;
            backedge(ctx);
        L_00530cac:
            charge(ctx, 1);
            t6 = 0x7F0000;
        } else {
            // 0x00530c84
            charge(ctx, 3);
            t7 = t6 ^ 0x2;
            if (t7 == 0) {
                t5 = 0;
                goto L_00530cac;
            }
            // 0x00530c90
            charge(ctx, 2);
            t6 = 0x7F0000;
            if (t5 != 0) {
                // 0x00530c98
                charge(ctx, 4);
                lw(a0, a0, parts::kExp);
                t7 = slti(a0, -126);
                if (t7 == 0) {
                    t3 = addiu(a0, 127);
                    // 0x00530cf8
                    charge(ctx, 3);
                    t7 = slti(t3, 256);
                    t5 = srl(t5, 7);
                    if (t7 == 0) {
                        goto L_00530d04;
                    }
                    backedge(ctx);
                } else {
                    // 0x00530ca8
                    charge(ctx, 1);
                    t5 = 0;
                }
                goto L_00530cac;
            }
        }
        // 0x00530cb0 (the shared epilogue, written out on this path)
        charge(ctx, 18);
        t7 = lui(0xFF80);
        t6 = t6 | 0xFFFF;
        t4 = t4 & t7;
        t6 = t5 & t6;
        t7 = t3 & 0xFF;
        t5 = lui(0x807F);
        t4 = t4 | t6;
        t5 = t5 | 0xFFFF;
        t7 = sll(t7, 23);
        t4 = t4 & t5;
        t6 = 0x7FFF0000;
        t4 = t4 | t7;
        t6 = t6 | 0xFFFF;
        t5 = sll(t2, 31);
        t4 = t4 & t6;
        t7 = t4 | t5;
        mtc1(t7, f0);
        return;
    }
L_00530d04:
    charge(ctx, 1);
    t5 = 0x7F0000;
    goto L_00530d08;
}

// 0x00530D18 __unpack_f -- 84 bytes; leaf frame (no stack)
// __unpack_f(src $a0, fp $a1): an IEEE single at *src into the fp-bit layout: sign; exponent field 0 -> class 2 (zero;
// denormals flush to zero); otherwise class 3 (normal), exponent - 127 and fraction << 7 | 1 << 30. Exponent 0xFF is
// NOT special here (the EE has no Inf / NaN singles).
void __unpack_f(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00530d18
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t7, a0, 0);
    t5 = 0x7F0000;
    t5 = t5 | 0xFFFF;  // &0x7FFFFF
    t4 = srl(t7, 31);
    t6 = srl(t7, 23);
    t7 = t7 & t5;
    sw(t4, a1, parts::kSign);
    t5 = sll(t7, 7);
    t6 = t6 & 0xFF;
    t7 = addiu(t6, -127);
    if (t6 == 0) {
        // 0x00530d44
        charge(ctx, 3);
        t7 = 2;
        sw(t7, a1, parts::kClass);
        return;
    }
    // 0x00530d50
    charge(ctx, 7);
    sw(t7, a1, parts::kExp);
    t6 = 3;
    sw(t6, a1, parts::kClass);
    t7 = 0x40000000;
    t7 = t5 | t7;
    sw(t7, a1, parts::kFracF);
}

// 0x00530D70 __make_fp -- 44 bytes; frame 0x20: ra sp+0x10
// __make_fp(class $a0, sign $a1, exp $a2, frac $a3) -> $f0: the four words stored as an unpacked single on the stack
// and packed with __pack_f.
void __make_fp(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00530d70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a0, sp, 0x0);
    sd(ra, sp, 0x10);
    sw(a1, sp, 0x4);
    a0 = sp;
    sw(a2, sp, 0x8);
    link(ctx, 0x530D88u);  // $ra first: the delay slot below depends on it
    sw(a3, sp, 0xC);
    call(ctx, gen::fn___pack_f_00530c60);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00530DE0 __pack_d -- 212 bytes; leaf frame (no stack)
// __pack_d(fp $a0) -> $v0: an unpacked double (+0 class, +4 sign, +8 unbiased exponent, +16 64-bit fraction with the
// implicit bit at bit 60) packed into IEEE bits: NaN classes (0, 1) -> exponent 0x7FF with the quiet bit OR-ed into
// the fraction; Inf -> exponent 0x7FF, fraction 0; zero or a zero fraction -> +-0; exponent < -1022 -> +-0 (no
// denormals); exponent > 1023 -> +-Inf; else (exponent + 1023) << 52 | (fraction >> 8) & (2^52 - 1). Truncates the 8
// guard bits (no rounding anywhere in this soft-float library).
void __pack_d(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00530de0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(t5, a0, parts::kClass);
    t6 = 0;
    ld(t4, a0, parts::kFrac);
    t7 = sltiu(t5, 2);
    lw(t3, a0, parts::kSign);
    if (t7 != 0) {
        // 0x00530df8
        charge(ctx, 4);
        t7 = 1;
        t6 = 2047;
        t7 = dsll32(t7, 19);
        t4 = t4 | t7;
        goto L_00530e08;
    }
    // 0x00530e68
    charge(ctx, 3);
    t7 = t5 ^ 0x4;
    if (t7 == 0) {
        t6 = 2047;
    } else {
        // 0x00530e74
        charge(ctx, 3);
        t7 = t5 ^ 0x2;
        if (t7 == 0) {
            t4 = 0;
            backedge(ctx);
        L_00530e08:
            charge(ctx, 1);
            t7 = si(-1);
        } else {
            // 0x00530e80
            charge(ctx, 2);
            t7 = si(-1);
            if (t4 != 0) {
                // 0x00530e88
                charge(ctx, 4);
                lw(a0, a0, parts::kExp);
                t7 = slti(a0, -1022);
                if (t7 != 0) {
                    t4 = 0;
                    backedge(ctx);
                } else {
                    // 0x00530e98
                    charge(ctx, 4);
                    t7 = slti(a0, 1024);
                    t6 = addiu(a0, 1023);
                    t4 = dsrl(t4, 8);
                    if (t7 == 0) {
                        // 0x00530ea8
                        charge(ctx, 1);
                        t6 = 2047;
                        goto L_00530eac;
                    }
                    backedge(ctx);
                }
                goto L_00530e08;
            }
            backedge(ctx);
        }
        // 0x00530e0c (the shared epilogue, written out on this path)
        charge(ctx, 23);
        t5 = si(-4096);
        t7 = dsll32(t7, 20);
        t5 = dsrl(t5, 12);
        v0 = v0 & t7;
        t5 = t4 & t5;
        t7 = 2047;
        t6 = dsll32(t6, 0);
        t7 = dsll32(t7, 20);
        v0 = v0 | t5;
        t7 = nor(0, t7);
        t6 = dsrl32(t6, 0);
        v0 = v0 & t7;
        t6 = t6 & 0x7FF;
        t6 = dsll32(t6, 20);
        t5 = dsll32(t3, 0);
        t7 = si(-2);
        v0 = v0 | t6;
        t7 = dsrl(t7, 1);
        t5 = dsrl32(t5, 0);
        t5 = dsll32(t5, 31);
        v0 = v0 & t7;
        v0 = v0 | t5;
        return;
    }
L_00530eac:
    charge(ctx, 2);
    t4 = 0;
    backedge(ctx);
    goto L_00530e08;
}

// 0x00530EB8 __unpack_d -- 144 bytes; leaf frame (no stack)
// __unpack_d(src $a0, fp $a1): an IEEE double at *src into the fp-bit layout: exponent 0 -> zero (denormals flush),
// 0x7FF with fraction 0 -> Inf (class 4), with a fraction -> NaN (class 1 when the quiet bit is set, 0 otherwise; the
// raw fraction kept), else normal: exponent - 1023, fraction << 8 | 1 << 60.
void __unpack_d(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00530eb8
    enter(ctx, 10);  // entry check point + this block's cycles
    ld(t6, a0, 0);
    t7 = si(-4096);
    t7 = dsrl(t7, 12);
    t5 = dsrl32(t6, 31);
    t4 = dsrl32(t6, 20);
    t6 = t6 & t7;
    sw(t5, a1, parts::kSign);
    t4 = t4 & 0x7FF;
    t7 = 2;
    if (t4 == 0) {
        // 0x00530f20 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(t7, a1, parts::kClass);
        return;
    }
    // 0x00530ee0
    charge(ctx, 3);
    t7 = 2047;
    cc = t4 != t7;  // the condition, before the delay slot changes it
    t7 = dsll(t6, 8);
    if (cc) {
        // 0x00530f28
        charge(ctx, 8);
        t5 = addiu(t4, -1023);
        t6 = 1;
        sw(t5, a1, parts::kExp);
        t6 = dsll32(t6, 28);
        t7 = t7 | t6;
        sd(t7, a1, parts::kFrac);
        t7 = 3;
        backedge(ctx);
        // 0x00530f20 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(t7, a1, parts::kClass);
        return;
    }
    // 0x00530eec
    charge(ctx, 2);
    t7 = 4;
    if (t6 == 0) {
        // 0x00530f20 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sw(t7, a1, parts::kClass);
        return;
    }
    // 0x00530ef4
    charge(ctx, 5);
    t7 = 1;
    t7 = dsll32(t7, 19);
    t7 = t6 & t7;
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = 1;
    if (cc) {
        // 0x00530f14
        charge(ctx, 2);
        sw(zero, a1, parts::kClass);
        backedge(ctx);
    } else {
        // 0x00530f08
        charge(ctx, 1);
        sw(t7, a1, parts::kClass);
    }
    // 0x00530f0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sd(t6, a1, parts::kFrac);
}

// 0x00530F48 _fpadd_parts -- 548 bytes; leaf frame (no stack)
// _fpadd_parts(a $a0, b $a1, tmp $a2) -> $v0: the sum of two unpacked doubles: a NaN operand is returned as it is, Inf
// + -Inf returns the NaN record at 0x7C0488, Inf + x returns the Inf, 0 + 0 gives tmp = 0 with the AND of the signs, x
// + 0 returns x. Otherwise the fraction of the smaller exponent is shifted right one bit at a time to the larger
// exponent (each lost bit OR-ed into bit 0: a sticky bit; 64 or more bits apart it becomes 0), same signs add,
// different signs subtract into a sign / magnitude pair (zero is +0), the result is renormalised left until bit 60
// leads, a carry past bit 61 shifts right once (sticky kept); class normal. Returns a, b or tmp. No rounding: __pack_d
// truncates the 8 guard bits.
void _fpadd_parts(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00530f48
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(t6, a0, parts::kClass);
    t7 = sltiu(t6, 2);
    v0 = a0;
    if (t7 != 0) {
        // 0x005310f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00530f58
    charge(ctx, 4);
    lw(t5, a1, parts::kClass);
    t7 = sltiu(t5, 2);
    v0 = a1;
    if (t7 != 0) {
        // 0x005310f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00530f68
    charge(ctx, 3);
    t7 = t6 ^ 0x4;
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t5 ^ 0x4;
    if (!cc) {
        // 0x00530f74
        charge(ctx, 2);
        if (t7 != 0) {
            // 0x00530f94 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = a0;
            return;
        }
        // 0x00530f7c
        charge(ctx, 4);
        lw(t6, a1, parts::kSign);
        lw(t7, a0, parts::kSign);
        cc = t7 == t6;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (cc) {
            // 0x00530f94 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = a0;
            return;
        }
        // 0x00530f8c
        charge(ctx, 2);
        v0 = addiu(t7, 1160);
        return;
    }
    // 0x00530f9c
    charge(ctx, 2);
    v0 = a1;
    if (t7 == 0) {
        // 0x005310f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00530fa4
    charge(ctx, 3);
    t7 = t5 ^ 0x2;
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t6 ^ 0x2;
    if (!cc) {
        // 0x00530fb0
        charge(ctx, 2);
        if (t7 != 0) {
            backedge(ctx);
            // 0x00530f94 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = a0;
            return;
        }
        // 0x00530fb8
        charge(ctx, 12);
        ld(t6, a0, 0);
        v0 = a2;
        sd(t6, a2, 0);
        ld(t7, a0, 8);
        sd(t7, a2, 8);
        ld(t6, a0, parts::kFrac);
        sd(t6, a2, parts::kFrac);
        lw(t7, a0, parts::kSign);
        lw(t6, a1, parts::kSign);
        t7 = t7 & t6;
        sw(t7, a2, parts::kSign);
        return;
    }
    // 0x00530fe8
    charge(ctx, 2);
    v0 = a1;
    if (t7 != 0) {
        // 0x00530ff0
        charge(ctx, 6);
        lw(t1, a0, parts::kExp);
        lw(t4, a1, parts::kExp);
        ld(t3, a0, parts::kFrac);
        t7 = subu(t1, t4);
        if (i64(t7) < 0) {
            t7 = subu(0, t7);
        }
        // 0x00531008
        charge(ctx, 3);
        t7 = slti(t7, 64);
        ld(t2, a1, parts::kFrac);
        if (t7 == 0) {
            // 0x00531150
            charge(ctx, 3);
            t7 = slt(t4, t1);
            if (t7 == 0) {
                t1 = t4;
                // 0x00531164
                charge(ctx, 2);
                t3 = 0;
                backedge(ctx);
            } else {
                // 0x0053115c
                charge(ctx, 2);
                t2 = 0;
                backedge(ctx);
            }
        L_0053106c:
            charge(ctx, 1);
            lw(a0, a0, parts::kSign);
        } else {
            // 0x00531014
            charge(ctx, 3);
            t7 = slt(t4, t1);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = slt(t1, t4);
            if (!cc) {
                // 0x00531020
                charge(ctx, 1);
                t4 = subu(t1, t4);
                for (;;) {
                    // 0x00531024
                    charge(ctx, 7);
                    t6 = dsrl(t2, 1);
                    t7 = t2 & 0x1;
                    t4 = addiu(t4, -1);
                    t2 = t7 | t6;
                    if (t4 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00531040
                charge(ctx, 2);
                t4 = t1;
                t7 = slt(t1, t4);
            }
            // 0x00531048
            charge(ctx, 2);
            if (t7 != 0) {
                for (;;) {
                    // 0x00531050
                    charge(ctx, 7);
                    t7 = dsrl(t3, 1);
                    t1 = addiu(t1, 1);
                    t6 = t3 & 0x1;
                    t5 = slt(t1, t4);
                    t3 = t6 | t7;
                    if (t5 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_0053106c;
            }
            lw(a0, a0, parts::kSign);
        }
        // 0x00531070
        charge(ctx, 3);
        lw(t7, a1, parts::kSign);
        cc = a0 == t7;  // the condition, before the delay slot changes it
        t7 = t3 - t2;
        if (cc) {
            // 0x00531138
            charge(ctx, 6);
            t7 = t3 + t2;
            sw(a0, a2, parts::kSign);
            sw(t1, a2, parts::kExp);
            t4 = t7;
            sd(t7, a2, parts::kFrac);
            backedge(ctx);
        } else {
            // 0x0053107c
            charge(ctx, 4);
            t6 = t2 - t3;
            if (a0 == 0) t6 = t7;
            if (i64(t6) < 0) {
                t6 = 0 - t6;
                // 0x00531124
                charge(ctx, 5);
                sw(t1, a2, parts::kExp);
                t7 = 1;
                sd(t6, a2, parts::kFrac);
                sw(t7, a2, parts::kSign);
                backedge(ctx);
            } else {
                // 0x0053108c
                charge(ctx, 3);
                sw(t1, a2, parts::kExp);
                sd(t6, a2, parts::kFrac);
                sw(zero, a2, parts::kSign);
            }
            // 0x00531098
            charge(ctx, 8);
            ld(t4, a2, parts::kFrac);
            t7 = si(-32);
            t3 = si(-32);
            t7 = dsrl(t7, 4);
            t6 = daddiu(t4, -1);
            t7 = sltu(t7, t6);
            t3 = dsrl(t3, 4);
            if (t7 == 0) {
                // 0x005310f8
                charge(ctx, 1);
                lw(t6, a2, parts::kExp);
                for (;;) {
                    // 0x005310fc
                    charge(ctx, 8);
                    t5 = dsll(t4, 1);
                    t7 = daddiu(t5, -1);
                    sd(t5, a2, parts::kFrac);
                    t6 = addiu(t6, -1);
                    t7 = sltu(t3, t7);
                    sw(t6, a2, parts::kExp);
                    t4 = t5;
                    if (t7 == 0) {
                        // 0x0053111c
                        charge(ctx, 2);
                        lw(t6, a2, parts::kExp);
                        backedge(ctx);
                        continue;
                    }
                    backedge(ctx);
                    break;
                }
            }
        }
        // 0x005310b8
        charge(ctx, 6);
        t6 = 3;
        t7 = si(-8);
        t7 = dsrl(t7, 3);
        t7 = sltu(t7, t4);
        sw(t6, a2, parts::kClass);
        if (t7 != 0) {
            // 0x005310d0
            charge(ctx, 7);
            lw(t7, a2, parts::kExp);
            t5 = dsrl(t4, 1);
            t6 = t4 & 0x1;
            t6 = t6 | t5;
            t7 = addiu(t7, 1);
            sd(t6, a2, parts::kFrac);
            sw(t7, a2, parts::kExp);
        }
        // 0x005310ec
        charge(ctx, 1);
        v0 = a2;
    }
    // 0x005310f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00531170 dpadd -- 88 bytes; frame 0x80: ra sp+0x78, s0 sp+0x70
// dpadd(a $a0, b $a1) -> $v0: double a + b: both operands stored to the frame, unpacked (__unpack_d), added
// (_fpadd_parts) and packed (__pack_d). Results are truncated toward zero, not rounded (test_libc.cpp measures it
// against the host).
void dpadd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531170
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(a0, sp, 0x60);
    sd(a1, sp, 0x68);
    sd(ra, sp, 0x78);
    a0 = addiu(sp, 0x60);
    sd(s0, sp, 0x70);
    a1 = sp;
    jal(ctx, 0x531188u, gen::fn___unpack_d_00530eb8);
    s0 = addiu(sp, 0x20);
    a0 = addiu(sp, 0x68);
    a1 = s0;
    jal(ctx, 0x531198u, gen::fn___unpack_d_00530eb8);
    a1 = s0;
    a2 = addiu(sp, 0x40);
    a0 = sp;
    jal(ctx, 0x5311A8u, gen::fn__fpadd_parts_00530f48);
    a0 = v0;
    jal(ctx, 0x5311B0u, gen::fn___pack_d_00530de0);
    ld(s0, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

// 0x005311C8 dpsub -- 100 bytes; frame 0x80: ra sp+0x78, s0 sp+0x70
// dpsub(a $a0, b $a1) -> $v0: double a - b: b's unpacked sign flipped, then as dpadd.
void dpsub(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005311c8
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(a0, sp, 0x60);
    sd(a1, sp, 0x68);
    sd(ra, sp, 0x78);
    a0 = addiu(sp, 0x60);
    sd(s0, sp, 0x70);
    a1 = sp;
    jal(ctx, 0x5311E0u, gen::fn___unpack_d_00530eb8);
    s0 = addiu(sp, 0x20);
    a0 = addiu(sp, 0x68);
    a1 = s0;
    jal(ctx, 0x5311F0u, gen::fn___unpack_d_00530eb8);
    lw(t7, sp, 0x24);
    a1 = s0;
    a2 = addiu(sp, 0x40);
    a0 = sp;
    t7 = t7 ^ 0x1;
    link(ctx, 0x53120Cu);  // $ra first: the delay slot below depends on it
    sw(t7, sp, 0x24);
    call(ctx, gen::fn__fpadd_parts_00530f48);
    a0 = v0;
    jal(ctx, 0x531214u, gen::fn___pack_d_00530de0);
    ld(s0, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

// 0x00531230 dpmul -- 88 bytes; frame 0x80: ra sp+0x78, s0 sp+0x70
// dpmul(a $a0, b $a1) -> $v0: double a * b: unpack, _fpmul_parts, pack.
void dpmul(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531230
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(a0, sp, 0x60);
    sd(a1, sp, 0x68);
    sd(ra, sp, 0x78);
    a0 = addiu(sp, 0x60);
    sd(s0, sp, 0x70);
    a1 = sp;
    jal(ctx, 0x531248u, gen::fn___unpack_d_00530eb8);
    s0 = addiu(sp, 0x20);
    a0 = addiu(sp, 0x68);
    a1 = s0;
    jal(ctx, 0x531258u, gen::fn___unpack_d_00530eb8);
    a1 = s0;
    a2 = addiu(sp, 0x40);
    a0 = sp;
    jal(ctx, 0x531268u, gen::fn__fpmul_parts_00531288);
    a0 = v0;
    jal(ctx, 0x531270u, gen::fn___pack_d_00530de0);
    ld(s0, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

// 0x00531288 _fpmul_parts -- 500 bytes; leaf frame (no stack)
// _fpmul_parts(a $a0, b $a1, tmp $a2) -> $v0: the product of two unpacked doubles: NaN operands are returned (with the
// sign set to sign(a) != sign(b)), Inf * 0 returns the NaN record at 0x7C0488, Inf or zero operands are returned with
// the product's sign. Otherwise the 61-bit fractions are multiplied into 128 bits from four 32x32 partial products
// (multu / multu1, read with pmfhl.lw, carries added by hand), exponent = ea + eb + 4, the high half normalised so bit
// 60 leads (bits shifted out of / into the low half). No rounding: the low half is dropped.
void _fpmul_parts(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00531288
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(t6, a0, parts::kClass);
    t4 = a1;
    t7 = sltiu(t6, 2);
    v0 = a2;
    if (t7 != 0) {
        // 0x005312c4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        lw(t6, t4, parts::kSign);
        v0 = a0;
        lw(t7, a0, parts::kSign);
        t7 = t7 ^ t6;
        t7 = sltu(0, t7);
        sw(t7, a0, parts::kSign);
        return;
    }
    // 0x0053129c
    charge(ctx, 4);
    lw(t5, a1, parts::kClass);
    t7 = sltiu(t5, 2);
    if (t7 != 0) {
        lw(t7, a0, parts::kSign);
        // 0x005312fc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = t4;
        lw(t6, t4, parts::kSign);
        t7 = t7 ^ t6;
        t7 = sltu(0, t7);
        sw(t7, t4, parts::kSign);
        return;
    }
    // 0x005312ac
    charge(ctx, 3);
    t7 = t6 ^ 0x4;
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t5 ^ 0x4;
    if (!cc) {
        // 0x005312b8
        charge(ctx, 3);
        t7 = t5 ^ 0x2;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (cc) {
            // 0x005312e0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = addiu(t7, 1160);
            return;
        }
        // 0x005312c4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        lw(t6, t4, parts::kSign);
        v0 = a0;
        lw(t7, a0, parts::kSign);
        t7 = t7 ^ t6;
        t7 = sltu(0, t7);
        sw(t7, a0, parts::kSign);
        return;
    }
    // 0x005312e8
    charge(ctx, 2);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t6 ^ 0x2;
    if (!cc) {
        // 0x005312f0
        charge(ctx, 2);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (cc) {
            backedge(ctx);
            // 0x005312e0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = addiu(t7, 1160);
            return;
        }
        // 0x005312f8
        charge(ctx, 1);
        lw(t7, a0, parts::kSign);
        // 0x005312fc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = t4;
        lw(t6, t4, parts::kSign);
        t7 = t7 ^ t6;
        t7 = sltu(0, t7);
        sw(t7, t4, parts::kSign);
        return;
    }
    // 0x00531314
    charge(ctx, 2);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = t5 ^ 0x2;
    if (cc) {
        backedge(ctx);
        // 0x005312c4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        lw(t6, t4, parts::kSign);
        v0 = a0;
        lw(t7, a0, parts::kSign);
        t7 = t7 ^ t6;
        t7 = sltu(0, t7);
        sw(t7, a0, parts::kSign);
        return;
    }
    // 0x0053131c
    charge(ctx, 2);
    if (t7 == 0) {
        lw(t7, a0, parts::kSign);
        backedge(ctx);
        // 0x005312fc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = t4;
        lw(t6, t4, parts::kSign);
        t7 = t7 ^ t6;
        t7 = sltu(0, t7);
        sw(t7, t4, parts::kSign);
        return;
    }
    // 0x00531324
    charge(ctx, 46);
    ld(t5, a0, parts::kFrac);
    ld(t6, a1, parts::kFrac);
    a2 = dsra32(t5, 0);
    lw(a3, t4, parts::kExp);
    t5 = dsll32(t5, 0);
    lw(t2, a0, parts::kSign);
    t0 = dsra32(t6, 0);
    lw(a1, a1, parts::kSign);
    t5 = dsra32(t5, 0);
    lw(t1, a0, parts::kExp);
    multu(zero, t0, t5);
    t6 = dsll32(t6, 0);
    t6 = dsra32(t6, 0);
    t1 = addu(t1, a3);
    t2 = t2 ^ a1;
    t1 = addiu(t1, 4);
    t2 = sltu(0, t2);
    sw(t1, v0, parts::kExp);
    pmfhl(at, 0);
    t3 = at;
    multu(zero, t6, a2);
    pmfhl(at, 0);
    t7 = at;
    multu(zero, t6, t5);
    t7 = t3 + t7;
    t4 = sltu(t7, t3);
    t3 = dsll32(t7, 0);
    t4 = dsll32(t4, 0);
    t3 = dsra32(t3, 0);
    t7 = dsrl32(t7, 0);
    pmfhl(at, 0);
    t6 = at;
    multu(zero, t0, a2);
    t3 = dsll32(t3, 0);
    t5 = t6 + t3;
    t6 = sltu(t5, t6);
    t4 = t4 + t6;
    pmfhl(at, 0);
    t0 = at;
    t7 = t7 + t0;
    t4 = t4 + t7;
    t7 = si(-8);
    t7 = dsrl(t7, 3);
    t7 = sltu(t7, t4);
    sw(t2, v0, parts::kSign);
    if (t7 != 0) {
        // 0x005313dc
        charge(ctx, 5);
        t1 = si(-1);
        t2 = si(-8);
        t1 = dsll32(t1, 31);
        t2 = dsrl(t2, 3);
        lw(t7, v0, parts::kExp);
        for (;;) {
            // 0x005313f0
            charge(ctx, 8);
            t6 = t4 & 0x1;
            t4 = dsrl(t4, 1);
            t6 = dsll32(t6, 0);
            t7 = addiu(t7, 1);
            t6 = dsra32(t6, 0);
            sw(t7, v0, parts::kExp);
            t3 = sltu(t2, t4);
            if (t6 != 0) {
                // 0x00531410
                charge(ctx, 2);
                t5 = dsrl(t5, 1);
                t5 = t5 | t1;
            }
            // 0x00531418
            charge(ctx, 2);
            if (t3 == 0) {
                break;
            }
            lw(t7, v0, parts::kExp);
            backedge(ctx);
        }
    }
    // 0x00531420
    charge(ctx, 5);
    t7 = si(-16);
    t7 = dsrl(t7, 4);
    t7 = sltu(t7, t4);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = 3;
    if (!cc) {
        // 0x00531434
        charge(ctx, 5);
        t1 = si(-1);
        lw(t3, v0, parts::kExp);
        t2 = si(-16);
        t1 = dsll32(t1, 31);
        t2 = dsrl(t2, 4);
        for (;;) {
            // 0x00531448
            charge(ctx, 8);
            t4 = dsll(t4, 1);
            t6 = t5 & t1;
            t7 = t4 | 0x1;
            t3 = addiu(t3, -1);
            if (t6 != 0) t4 = t7;
            t7 = sltu(t2, t4);
            t5 = dsll(t5, 1);
            if (t7 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00531468
        charge(ctx, 2);
        sw(t3, v0, parts::kExp);
        t7 = 3;
    }
    // 0x00531470 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sd(t4, v0, parts::kFrac);
    sw(t7, v0, parts::kClass);
}

// 0x00531480 dpdiv -- 84 bytes; frame 0x60: ra sp+0x58, s0 sp+0x50
// dpdiv(a $a0, b $a1) -> $v0: double a / b: unpack, _fpdiv_parts, pack.
void dpdiv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531480
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(a0, sp, 0x40);
    sd(a1, sp, 0x48);
    sd(ra, sp, 0x58);
    a0 = addiu(sp, 0x40);
    sd(s0, sp, 0x50);
    a1 = sp;
    jal(ctx, 0x531498u, gen::fn___unpack_d_00530eb8);
    s0 = addiu(sp, 0x20);
    a0 = addiu(sp, 0x48);
    a1 = s0;
    jal(ctx, 0x5314A8u, gen::fn___unpack_d_00530eb8);
    a1 = s0;
    a0 = sp;
    jal(ctx, 0x5314B4u, gen::fn__fpdiv_parts_005314d8);
    a0 = v0;
    jal(ctx, 0x5314BCu, gen::fn___pack_d_00530de0);
    ld(s0, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x005314D8 _fpdiv_parts -- 248 bytes; leaf frame (no stack)
// _fpdiv_parts(a $a0, b $a1) -> $v0: the quotient of two unpacked doubles, written into a: NaN operands are returned
// as they are; sign = sign(a) ^ sign(b); Inf / Inf and 0 / 0 return the NaN record at 0x7C0488, Inf / x and 0 / x
// return a, x / Inf gives a zero fraction (packs as 0), x / 0 sets a's class to Inf. Otherwise exponent = ea - eb
// (minus one when a's fraction is the smaller, after doubling it), and 61 steps of restoring shift-and-subtract
// division from bit 60 down. No sticky bit and no rounding: the quotient is truncated.
void _fpdiv_parts(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005314d8
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(t4, a0, parts::kClass);
    t7 = sltiu(t4, 2);
    v0 = a0;
    if (t7 != 0) {
        // 0x005315c8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005314e8
    charge(ctx, 4);
    lw(t3, a1, parts::kClass);
    t7 = sltiu(t3, 2);
    v0 = a1;
    if (t7 != 0) {
        // 0x005315c8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x005314f8
    charge(ctx, 6);
    lw(t7, a0, parts::kSign);
    t5 = t4 ^ 0x4;
    lw(t6, a1, parts::kSign);
    t7 = t7 ^ t6;
    sw(t7, a0, parts::kSign);
    if (t5 != 0) {
        // 0x00531510
        charge(ctx, 3);
        t7 = t4 ^ 0x2;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = t3 ^ 0x4;
        if (!cc) {
            goto L_0053151c;
        }
        // 0x00531534
        charge(ctx, 2);
        if (t7 == 0) {
            // 0x0053153c
            charge(ctx, 4);
            sd(zero, a0, parts::kFrac);
            v0 = a0;
            sw(zero, a0, parts::kExp);
            return;
        }
        t7 = t3 ^ 0x2;
        // 0x0053154c
        charge(ctx, 2);
        if (t7 == 0) {
            // 0x00531554
            charge(ctx, 4);
            t7 = 4;
            v0 = a0;
            sw(t7, a0, parts::kClass);
            return;
        }
        lw(t7, a1, parts::kExp);
        // 0x00531564
        charge(ctx, 7);
        lw(t6, a0, parts::kExp);
        ld(a1, a1, parts::kFrac);
        t6 = subu(t6, t7);
        ld(t5, a0, parts::kFrac);
        t7 = sltu(t5, a1);
        sw(t6, a0, parts::kExp);
        if (t7 != 0) {
            // 0x00531580
            charge(ctx, 4);
            t7 = addiu(t6, -1);
            t5 = dsll(t5, 1);
            sw(t7, a0, parts::kExp);
            t7 = sltu(t5, a1);
        }
        // 0x00531590
        charge(ctx, 3);
        t6 = 1;
        t4 = 0;
        t6 = dsll32(t6, 28);
        for (;;) {
            // 0x0053159c
            charge(ctx, 2);
            if (t7 != 0) {
                t7 = dsll(t5, 1);
            } else {
                // 0x005315a4
                charge(ctx, 3);
                t5 = t5 - a1;
                t4 = t4 | t6;
                t7 = dsll(t5, 1);
            }
            // 0x005315b0
            charge(ctx, 4);
            t6 = dsrl(t6, 1);
            t5 = t7;
            t7 = sltu(t7, a1);
            if (t6 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005315c0
        charge(ctx, 2);
        sd(t4, a0, parts::kFrac);
        v0 = a0;
        // 0x005315c8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0053151c:
    charge(ctx, 2);
    t7 = 0x7C0000;
    if (t4 != t3) {
        // 0x0053152c
        charge(ctx, 2);
        v0 = a0;
        return;
    }
    // 0x00531524
    charge(ctx, 2);
    v0 = addiu(t7, 1160);
}

// 0x005315D0 __fpcmp_parts_d -- 252 bytes; leaf frame (no stack)
// __fpcmp_parts_d(a $a0, b $a1) -> $v0: three-way compare of unpacked doubles: 1 when either is a NaN; Inf against Inf
// by sign; Inf / zero rules; otherwise by sign, then exponent, then fraction (reversed for negatives): -1 (a < b), 0,
// 1.
void __fpcmp_parts_d(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005315d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(t6, a0, parts::kClass);
    t7 = sltiu(t6, 2);
    if (t7 != 0) {
        // 0x005315f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x005315e0
    charge(ctx, 4);
    lw(t5, a1, parts::kClass);
    t7 = sltiu(t5, 2);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = t6 ^ 0x4;
    if (!cc) {
        // 0x005315f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x005315f8
    charge(ctx, 2);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = t6 ^ 0x4;
    if (!cc) {
        // 0x00531600
        charge(ctx, 3);
        t7 = t5 ^ 0x4;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = t6 ^ 0x4;
        if (cc) {
            goto L_0053161c;
        }
        // 0x0053160c
        charge(ctx, 4);
        lw(t6, a1, parts::kSign);
        lw(t7, a0, parts::kSign);
        v0 = subu(t6, t7);
        return;
    }
L_0053161c:
    charge(ctx, 2);
    if (t7 == 0) {
        lw(t6, a0, parts::kSign);
    } else {
        // 0x00531624
        charge(ctx, 3);
        t7 = t5 ^ 0x4;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = t6 ^ 0x2;
        if (!cc) {
            // 0x00531630
            charge(ctx, 2);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = t5 ^ 0x2;
            if (!cc) {
                // 0x00531638
                charge(ctx, 2);
                v0 = 0;
                if (t7 == 0) {
                    // 0x005316c4 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    return;
                }
                // 0x00531640
                charge(ctx, 3);
                t7 = t6 ^ 0x2;
                cc = t7 != 0;  // the condition, before the delay slot changes it
                t7 = t5 ^ 0x2;
                if (cc) {
                    goto L_00531660;
                }
                goto L_0053164c;
            }
        L_00531660:
            charge(ctx, 2);
            lw(t6, a0, parts::kSign);
            if (t7 == 0) {
                goto L_00531668;
            }
            // 0x00531674
            charge(ctx, 3);
            lw(t7, a1, parts::kSign);
            v0 = si(-1);
            if (t6 != t7) {
                backedge(ctx);
            L_0053166c:
                charge(ctx, 2);
                t7 = 1;
                backedge(ctx);
                // 0x00531658 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                if (t6 == 0) v0 = t7;
                return;
            }
            // 0x00531680
            charge(ctx, 5);
            lw(t4, a0, parts::kExp);
            lw(t5, a1, parts::kExp);
            t7 = slt(t5, t4);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 1;
            if (cc) {
                backedge(ctx);
                // 0x00531658 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                if (t6 == 0) v0 = t7;
                return;
            }
            // 0x00531694
            charge(ctx, 3);
            t7 = slt(t4, t5);
            if (t7 != 0) {
                v0 = 1;
                backedge(ctx);
            L_00531654:
                charge(ctx, 1);
                t7 = si(-1);
                // 0x00531658 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                if (t6 == 0) v0 = t7;
                return;
            }
            // 0x005316a0
            charge(ctx, 5);
            ld(t5, a0, parts::kFrac);
            ld(a0, a1, parts::kFrac);
            t7 = sltu(a0, t5);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 1;
            if (cc) {
                backedge(ctx);
                // 0x00531658 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                if (t6 == 0) v0 = t7;
                return;
            }
            // 0x005316b4
            charge(ctx, 3);
            t7 = sltu(t5, a0);
            if (t7 != 0) {
                v0 = 1;
                backedge(ctx);
                goto L_00531654;
            }
            // 0x005316c0
            charge(ctx, 1);
            v0 = 0;
            // 0x005316c4 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_0053164c:
        charge(ctx, 2);
        lw(t6, a1, parts::kSign);
        v0 = 1;
        goto L_00531654;
    }
L_00531668:
    charge(ctx, 1);
    v0 = si(-1);
    goto L_0053166c;
}

// 0x005316D0 dpcmp -- 76 bytes; frame 0x60: ra sp+0x58, s0 sp+0x50
// dpcmp(a $a0, b $a1) -> $v0: compare two doubles (__fpcmp_parts_d of the unpacked stack copies): -1, 0 or 1, 1 when
// unordered. The game's double comparisons (sub_45EC00 / sub_45EC20) call it.
void dpcmp(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005316d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(a0, sp, 0x40);
    sd(a1, sp, 0x48);
    sd(ra, sp, 0x58);
    a0 = addiu(sp, 0x40);
    sd(s0, sp, 0x50);
    a1 = sp;
    jal(ctx, 0x5316E8u, gen::fn___unpack_d_00530eb8);
    s0 = addiu(sp, 0x20);
    a0 = addiu(sp, 0x48);
    a1 = s0;
    jal(ctx, 0x5316F8u, gen::fn___unpack_d_00530eb8);
    a1 = s0;
    a0 = sp;
    jal(ctx, 0x531704u, gen::fn___fpcmp_parts_d_005315d0);
    ld(s0, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00531720 litodp -- 176 bytes; frame 0x30: ra sp+0x20
// litodp(i $a0) -> $v0: the signed 32-bit integer as a double: 0 -> +0; INT_MIN -> -2^31 directly
// (0xC1E0000000000000); else |i| shifted left until bit 60 is the leading bit (the exponent counted down from 60) and
// packed (exact).
void litodp(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531720
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t6 = srl(a0, 31);
    t7 = 3;
    sd(ra, sp, 0x20);
    sw(t7, sp, 0x0);
    sw(t6, sp, 0x4);
    if (a0 == 0) {
        // 0x0053173c
        charge(ctx, 2);
        t7 = 2;
        sw(t7, sp, 0x0);
        goto L_00531744;
    }
    // 0x00531758
    charge(ctx, 3);
    t7 = 60;
    sw(t7, sp, 0x8);
    if (t6 == 0) {
        // 0x005317c8
        charge(ctx, 2);
        t7 = a0;
        backedge(ctx);
    L_0053177c:
        charge(ctx, 7);
        sd(t7, sp, 0x10);
        t7 = si(-16);
        ld(t4, sp, 0x10);
        t7 = dsrl(t7, 4);
        t7 = sltu(t7, t4);
        t3 = si(-16);
        if (t7 != 0) {
            backedge(ctx);
        } else {
            // 0x00531798
            charge(ctx, 2);
            lw(t5, sp, 0x8);
            t3 = dsrl(t3, 4);
            for (;;) {
                // 0x005317a0
                charge(ctx, 7);
                t6 = dsll(t4, 1);
                t5 = addiu(t5, -1);
                t7 = sltu(t3, t6);
                t4 = t6;
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005317bc
            charge(ctx, 3);
            sw(t5, sp, 0x8);
            sd(t6, sp, 0x10);
            backedge(ctx);
        }
    L_00531744:
        charge(ctx, 2);
        a0 = sp;
        jal(ctx, 0x531744u, gen::fn___pack_d_00530de0);
    } else {
        // 0x00531764
        charge(ctx, 4);
        v0 = si(-497);
        t7 = lui(0x8000);
        v0 = dsll32(v0, 21);
        if (a0 != t7) {
            // 0x00531774
            charge(ctx, 2);
            t7 = subu(0, a0);
            // daddu t7: a 64-bit move to itself (no effect)
            goto L_0053177c;
        }
        backedge(ctx);
    }
    // 0x0053174c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005317D0 dptoli -- 156 bytes; frame 0x40: ra sp+0x30
// dptoli(x $a0) -> $v0: the double as a signed 32-bit integer, truncated toward zero: NaN -> 0, zero / |x| < 1 -> 0,
// Inf or exponent >= 31 -> INT_MAX / INT_MIN by the sign, else fraction >> (60 - exponent), negated for negative x.
void dptoli(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005317d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(a0, sp, 0x20);
    a1 = sp;
    sd(ra, sp, 0x30);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x5317E0u, gen::fn___unpack_d_00530eb8);
    lw(t6, sp, 0x0);
    v0 = 0;
    t7 = t6 ^ 0x2;
    t5 = sltiu(t6, 2);
    if (t7 != 0) {
        // 0x005317fc
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        if (t5 == 0) {
            // 0x00531804
            charge(ctx, 3);
            t7 = t6 ^ 0x4;
            cc = t7 == 0;  // the condition, before the delay slot changes it
            lw(t7, sp, 0x8);
            if (!cc) {
                // 0x00531810
                charge(ctx, 3);
                v0 = 0;
                t6 = slti(t7, 31);
                if (i64(t7) >= 0) {
                    // 0x0053181c
                    charge(ctx, 2);
                    cc = t6 != 0;  // the condition, before the delay slot changes it
                    t6 = 60;
                    if (!cc) {
                        goto L_00531824;
                    }
                    // 0x00531844
                    charge(ctx, 10);
                    t6 = subu(t6, t7);
                    ld(t7, sp, 0x10);
                    t7 = dsrlv(t7, t6);
                    t7 = dsll32(t7, 0);
                    lw(t6, sp, 0x4);
                    t7 = dsra32(t7, 0);
                    t5 = subu(0, t7);
                    v0 = t7;
                    if (t6 != 0) v0 = t5;
                    backedge(ctx);
                    goto L_00531838;
                }
                // 0x0053183c (the shared epilogue, written out on this path)
                charge(ctx, 2);
                sp = addiu(sp, 0x40);
                return;
            }
        L_00531824:
            charge(ctx, 5);
            t6 = 0x7FFF0000;
            lw(t7, sp, 0x4);
            v0 = lui(0x8000);
            t6 = t6 | 0xFFFF;
            if (t7 == 0) v0 = t6;
            goto L_00531838;
        }
        // 0x0053183c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x40);
        return;
    }
L_00531838:
    charge(ctx, 1);
    ld(ra, sp, 0x30);
    // 0x0053183c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x40);
}

// 0x00531870 __make_dp -- 44 bytes; frame 0x30: ra sp+0x20
// __make_dp(class $a0, sign $a1, exp $a2, frac $a3) -> $v0: the words stored as an unpacked double on the stack (the
// 64-bit fraction from $a3) and packed with __pack_d.
void __make_dp(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00531870
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sw(a0, sp, 0x0);
    sd(ra, sp, 0x20);
    sw(a1, sp, 0x4);
    a0 = sp;
    sw(a2, sp, 0x8);
    link(ctx, 0x531888u);  // $ra first: the delay slot below depends on it
    sd(a3, sp, 0x10);
    call(ctx, gen::fn___pack_d_00530de0);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005318A0 dptofp -- 84 bytes; frame 0x40: ra sp+0x30
// dptofp(x $a0) -> $f0: the double as a float: unpack, the fraction cut to 30 bits with the lost low bits OR-ed in as
// a sticky bit (no rounding), __make_fp with the same class / sign / exponent.
void dptofp(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005318a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(a0, sp, 0x20);
    a1 = sp;
    sd(ra, sp, 0x30);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x5318B0u, gen::fn___unpack_d_00530eb8);
    ld(t6, sp, 0x10);
    t7 = 0x3FFF0000;
    t7 = t7 | 0xFFFF;
    lw(a0, sp, 0x0);
    a3 = dsll(t6, 2);
    lw(a1, sp, 0x4);
    a3 = dsra32(a3, 0);
    lw(a2, sp, 0x8);
    t6 = t6 & t7;
    t5 = a3 | 0x1;
    if (t6 != 0) a3 = t5;
    jal(ctx, 0x5318E0u, gen::fn___make_fp_00530d70);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005318F8 dptoul -- 156 bytes; frame 0x40: ra sp+0x30
// dptoul(x $a0) -> $v0: the double as an unsigned 32-bit integer: NaN, zero, negative or |x| < 1 -> 0; Inf or exponent
// >= 32 -> 0xFFFFFFFF (sign-extended -1); else fraction >> (60 - exponent) (sign-extended 32-bit result).
void dptoul(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005318f8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(a0, sp, 0x20);
    a1 = sp;
    sd(ra, sp, 0x30);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x531908u, gen::fn___unpack_d_00530eb8);
    lw(t5, sp, 0x0);
    v0 = 0;
    t7 = t5 ^ 0x2;
    t4 = sltiu(t5, 2);
    if (t7 != 0) {
        // 0x00531924
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        if (t4 == 0) {
            // 0x0053192c
            charge(ctx, 3);
            lw(t7, sp, 0x4);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = t5 ^ 0x4;
            if (!cc) {
                // 0x00531938
                charge(ctx, 2);
                v0 = si(-1);
                if (t7 != 0) {
                    // 0x00531940
                    charge(ctx, 4);
                    lw(t5, sp, 0x8);
                    v0 = 0;
                    t7 = slti(t5, 32);
                    if (i64(t5) >= 0) {
                        // 0x00531950
                        charge(ctx, 2);
                        v0 = si(-1);
                        if (t7 != 0) {
                            // 0x00531958
                            charge(ctx, 3);
                            t7 = slti(t5, 61);
                            t6 = 60;
                            if (t7 != 0) {
                                // 0x00531984
                                charge(ctx, 4);
                                ld(t7, sp, 0x10);
                                t6 = subu(t6, t5);
                                t7 = dsrlv(t7, t6);
                                backedge(ctx);
                            } else {
                                // 0x00531964
                                charge(ctx, 3);
                                ld(t7, sp, 0x10);
                                t6 = addiu(t5, -60);
                                t7 = dsllv(t7, t6);
                            }
                            // 0x00531970
                            charge(ctx, 2);
                            v0 = dsll32(t7, 0);
                            v0 = dsra32(v0, 0);
                            goto L_00531978;
                        }
                    }
                }
            }
        }
        // 0x0053197c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x40);
        return;
    }
L_00531978:
    charge(ctx, 1);
    ld(ra, sp, 0x30);
    // 0x0053197c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game
