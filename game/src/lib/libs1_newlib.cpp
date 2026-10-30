// The newlib tail 0x51E178-0x51FFF0 that the libc slice left: _calloc_r, the _close_r / _kill_r errno wrappers,
// _dtoa_r, exit, the stdio glue (fflush, __sfmoreglue, __sfp, _cleanup(_r), __sinit, fread) and dlmalloc's _free_r /
// _malloc_trim_r (libc.h's `reent::` / `file::` records). Kept recompiled below them: _malloc_r, __malloc_lock / unlock
// (interrupt masking), _sbrk_r, __srefill, _fwalk, the FILE callbacks.
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass (scratch spec.py, checked by check.py) adds the
// role comments and the named offsets of game/include/p3fes/game/libs1_newlib.h, each equal to the literal it replaces.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs1_newlib.h"

namespace p3fes::recomp_gen {
void fn__Balloc_00521578(p3fes::EEContext&);
void fn__Bfree_00521620(p3fes::EEContext&);
void fn___malloc_lock_005214c8(p3fes::EEContext&);
void fn___malloc_unlock_00521520(p3fes::EEContext&);
void fn___mcmp_00521e70(p3fes::EEContext&);
void fn___mdiff_00521ed8(p3fes::EEContext&);
void fn___sfmoreglue_0051f898(p3fes::EEContext&);
void fn___sfp_0051f908(p3fes::EEContext&);
void fn___sinit_0051fa20(p3fes::EEContext&);
void fn___srefill_00523580(p3fes::EEContext&);
void fn__calloc_r_0051e178(p3fes::EEContext&);
void fn__cleanup_0051fa00(p3fes::EEContext&);
void fn__cleanup_r_0051f9e0(p3fes::EEContext&);
void fn__close_r_0051e230(p3fes::EEContext&);
void fn__d2b_005222c0(p3fes::EEContext&);
void fn__dtoa_r_0051e4b0(p3fes::EEContext&);
void fn__free_r_0051fbb0(p3fes::EEContext&);
void fn__fwalk_00520410(p3fes::EEContext&);
void fn__hi0bits_00521888(p3fes::EEContext&);
void fn__i2b_005219c8(p3fes::EEContext&);
void fn__kill_r_0051fff0(p3fes::EEContext&);
void fn__lshift_00521d10(p3fes::EEContext&);
void fn__malloc_r_005209c0(p3fes::EEContext&);
void fn__malloc_trim_r_0051fe90(p3fes::EEContext&);
void fn__multadd_00521650(p3fes::EEContext&);
void fn__multiply_00521a00(p3fes::EEContext&);
void fn__pow5mult_00521c08(p3fes::EEContext&);
void fn__sbrk_r_00523930(p3fes::EEContext&);
void fn_close_00503848(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_exit_0051f6a0(p3fes::EEContext&);
void fn_fflush_0051f728(p3fes::EEContext&);
void fn_fread_0051faa0(p3fes::EEContext&);
void fn_fstat_00503918(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_quorem_0051e280(p3fes::EEContext&);
void fn_std_0051f838(p3fes::EEContext&);
void fn_sub_100218_00100218(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0051E178 _calloc_r -- 180 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// calloc on a reentrancy record: _malloc_r(n x size), then zero the chunk's usable size (memset from 37 bytes,
// unrolled stores below).
void _calloc_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051e178
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    mult(a1, a1, a2);
    jal(ctx, 0x51E184u, gen::fn__malloc_r_005209c0);
    s0 = v0;
    v0 = 0;
    if (s0 != 0) {
        // 0x0051e198
        charge(ctx, 8);
        lw(t7, s0, -4);
        t6 = si(-4);
        t7 = t7 & t6;
        t5 = addiu(t7, -4);
        a2 = t5;
        t7 = sltiu(t5, 37);
        t4 = sltiu(t5, 20);
        if (t7 == 0) {
            // 0x0051e218
            charge(ctx, 5);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x51E21Cu, gen::fn_memset_00521408);
            v0 = s0;
            backedge(ctx);
        } else {
            // 0x0051e1b8
            charge(ctx, 2);
            t6 = s0;
            if (t4 == 0) {
                // 0x0051e1c0
                charge(ctx, 5);
                sw(zero, s0, 0);
                t6 = addiu(s0, 8);
                t7 = sltiu(t5, 28);
                sw(zero, s0, 4);
                if (t7 == 0) {
                    // 0x0051e1d4
                    charge(ctx, 5);
                    sw(zero, s0, 8);
                    t7 = sltiu(t5, 36);
                    sw(zero, s0, 12);
                    t6 = addiu(s0, 16);
                    if (t7 == 0) {
                        // 0x0051e1e8
                        charge(ctx, 3);
                        sw(zero, s0, 16);
                        t6 = addiu(s0, 24);
                        sw(zero, s0, 20);
                    }
                }
            }
            // 0x0051e1f4
            charge(ctx, 5);
            sw(zero, t6, 0);
            t6 = addiu(t6, 4);
            sw(zero, t6, 4);
            sw(zero, t6, 0);
            v0 = s0;
        }
    }
    // 0x0051e208 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0051E230 _close_r -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// close(fd) with errno cleared first and copied into the reentrancy record on -1.
void _close_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051e230
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s0 = 0x9B0000;
    sd(ra, sp, 0x10);
    s1 = a0;
    sw(zero, s0, -13280);  // 0x9ACC20
    a0 = a1;
    jal(ctx, 0x51E24Cu, gen::fn_close_00503848);
    t7 = si(-1);
    if (v0 != t7) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0051e260
        charge(ctx, 3);
        lw(t7, s0, -13280);
        if (t7 != 0) {
            sw(t7, s1, 0);
        }
        // 0x0051e26c
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0051e270 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0051E4B0 _dtoa_r -- 4576 bytes; frame 0xB0: s0 sp+0x60, s4 sp+0x80, s5 sp+0x88, s1 sp+0x68, s2 sp+0x70, s3 sp+0x78, s6 sp+0x90, s7 sp+0x98, fp sp+0xA0, ra sp+0xA8
// newlib's double to decimal digits (David Gay's dtoa): mode / ndigits, decimal point position, sign, end pointer;
// Bigints from the reentrancy record's pool.
void _dtoa_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051e4b0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(s0, sp, 0x60);
    sd(s4, sp, 0x80);
    sd(s5, sp, 0x88);
    s0 = t1;
    sd(s1, sp, 0x68);
    s4 = a1;
    sd(s2, sp, 0x70);
    s5 = a0;
    sd(s3, sp, 0x78);
    sd(s6, sp, 0x90);
    sd(s7, sp, 0x98);
    sd(fp, sp, 0xA0);
    sd(ra, sp, 0xA8);
    sw(a2, sp, 0x8);
    lw(t5, a0, 64);
    sw(a3, sp, 0xC);
    sw(t0, sp, 0x10);
    sw(t2, sp, 0x14);
    sw(zero, sp, 0x48);
    if (t5 != 0) {
        // 0x0051e504
        charge(ctx, 9);
        lw(t7, a0, 68);
        a1 = t5;
        sw(t7, t5, 4);
        lw(t6, a0, 68);
        t7 = 1;
        t7 = sllv(t7, t6);
        link(ctx, 0x51E51Cu);  // $ra first: the delay slot below depends on it
        sw(t7, t5, 8);
        call(ctx, gen::fn__Bfree_00521620);
        sw(zero, s5, 64);
    }
    // 0x0051e528
    charge(ctx, 5);
    t6 = dsrl32(s4, 0);
    t5 = dsll32(t6, 0);
    t5 = dsra32(t5, 0);
    if (i64(t5) >= 0) {
        sw(zero, s0, 0);
    } else {
        // 0x0051e53c
        charge(ctx, 12);
        t7 = 0x7FFF0000;
        t6 = 1;
        t7 = t7 | 0xFFFF;
        sw(t6, s0, 0);
        t7 = t5 & t7;
        s4 = dsll32(s4, 0);
        t7 = dsll32(t7, 0);
        s4 = dsrl32(s4, 0);
        t7 = dsrl32(t7, 0);
        t7 = dsll32(t7, 0);
        s4 = s4 | t7;
        t6 = dsrl32(s4, 0);
    }
    // 0x0051e56c
    charge(ctx, 6);
    s0 = dsll32(t6, 0);
    s0 = dsra32(s0, 0);
    t6 = 0x7FF00000;
    t7 = s0 & t6;
    a0 = s4;
    if (t7 == t6) {
        // 0x0051e584
        charge(ctx, 7);
        lw(t5, sp, 0x10);
        t6 = 9999;
        t7 = si(-4096);
        t7 = dsrl(t7, 12);
        t7 = s4 & t7;
        sw(t6, t5, 0);
        if (t7 != 0) {
            // 0x0051e5fc
            charge(ctx, 3);
            t7 = 0x7C0000;
            s6 = addiu(t7, -5416);  // "NaN"
            backedge(ctx);
        } else {
            // 0x0051e5a0
            charge(ctx, 2);
            t7 = 0x7C0000;
            s6 = addiu(t7, -5432);  // "Infinity"
        }
        // 0x0051e5a8
        charge(ctx, 3);
        lw(t6, sp, 0x14);
        cc = t6 == 0;  // the condition, before the delay slot changes it
        t6 = addiu(s6, 8);
        if (!cc) {
            // 0x0051e5b4
            charge(ctx, 5);
            lb(t7, s6, 3);
            t5 = addiu(s6, 3);
            if (t7 == 0) t6 = t5;
            lw(t7, sp, 0x14);
            sw(t6, t7, 0);
        }
        goto L_0051e5c8;
    }
    // 0x0051e608
    charge(ctx, 4);
    a1 = 0;
    jal(ctx, 0x51E608u, gen::fn_dpcmp_005316d0);
    a0 = s5;
    if (v0 != 0) {
        // 0x0051e640
        charge(ctx, 8);
        a1 = s4;
        a2 = sp;
        a3 = addiu(sp, 0x4);
        jal(ctx, 0x51E648u, gen::fn__d2b_005222c0);
        t7 = srl(s0, 20);
        s3 = t7 & 0x7FF;
        fp = v0;
        if (s3 == 0) {
            // 0x0051f5fc
            charge(ctx, 7);
            lw(t7, sp, 0x0);
            lw(s2, sp, 0x4);
            t5 = addu(s2, t7);
            s3 = addiu(t5, 1074);
            t7 = slti(s3, 33);
            t6 = dsll32(s4, 0);
            if (t7 != 0) {
                // 0x0051f680
                charge(ctx, 4);
                t7 = subu(0, s3);
                t6 = dsra32(t6, 0);
                s0 = sllv(t6, t7);
                backedge(ctx);
            } else {
                // 0x0051f618
                charge(ctx, 7);
                t7 = dsll32(s4, 0);
                t5 = addiu(t5, 1042);
                t6 = subu(0, s3);
                t7 = dsra32(t7, 0);
                t6 = sllv(s0, t6);
                t7 = srlv(t7, t5);
                s0 = t6 | t7;
            }
            // 0x0051f634
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x51F634u, gen::fn_litodp_00531720);
            t7 = lui(0xFE10);
            if (i64(s0) < 0) {
                // 0x0051f644
                charge(ctx, 5);
                a1 = 1055;
                a0 = v0;
                a1 = dsll32(a1, 20);
                jal(ctx, 0x51F64Cu, gen::fn_dpadd_00531170);
                t7 = lui(0xFE10);
            }
            // 0x0051f658
            charge(ctx, 10);
            t6 = dsra32(v0, 0);
            t6 = addu(t6, t7);
            s7 = dsll32(v0, 0);
            t7 = 1;
            s7 = dsrl32(s7, 0);
            t6 = dsll32(t6, 0);
            sw(t7, sp, 0x44);
            s3 = addiu(s3, -1075);
            s7 = s7 | t6;
            backedge(ctx);
        } else {
            // 0x0051e660
            charge(ctx, 22);
            t6 = 0xF0000;
            lw(s2, sp, 0x4);
            t6 = t6 | 0xFFFF;
            sw(zero, sp, 0x44);
            t7 = dsra32(s4, 0);
            t5 = si(-1);
            t7 = t7 & t6;
            t5 = dsrl32(t5, 0);
            t7 = dsll32(t7, 0);
            s7 = s4 & t5;
            t7 = dsrl32(t7, 0);
            t6 = 0x3FF00000;
            t7 = dsll32(t7, 0);
            s3 = addiu(s3, -1023);
            s7 = s7 | t7;
            t7 = dsra32(s7, 0);
            t7 = t7 | t6;
            s7 = s7 & t5;
            t7 = dsll32(t7, 0);
            t7 = dsrl32(t7, 0);
            t7 = dsll32(t7, 0);
            s7 = s7 | t7;
        }
        // 0x0051e6b8
        charge(ctx, 31);
        a1 = 2047;
        a0 = s7;
        a1 = dsll32(a1, 19);
        jal(ctx, 0x51E6C0u, gen::fn_dpsub_005311c8);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x51E6D0u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -5400);
        call(ctx, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x51E6E0u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -5392);
        call(ctx, gen::fn_dpadd_00531170);
        s0 = v0;
        a0 = s3;
        jal(ctx, 0x51E6ECu, gen::fn_litodp_00531720);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x51E6FCu);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -5384);
        call(ctx, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x51E708u, gen::fn_dpadd_00531170);
        s1 = v0;
        a0 = v0;
        jal(ctx, 0x51E714u, gen::fn_dptoli_005317d0);
        sw(v0, sp, 0x2C);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x51E724u, gen::fn_dpcmp_005316d0);
        t6 = 1;
        if (i64(v0) < 0) {
            // 0x0051e734
            charge(ctx, 10);
            link(ctx, 0x51E734u);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x2C);
            call(ctx, gen::fn_litodp_00531720);
            a1 = v0;
            a0 = s1;
            jal(ctx, 0x51E740u, gen::fn_dpcmp_005316d0);
            lw(t5, sp, 0x2C);
            t7 = addiu(t5, -1);
            if (v0 != 0) t5 = t7;
            sw(t5, sp, 0x2C);
            t6 = 1;
        }
        // 0x0051e75c
        charge(ctx, 4);
        lw(t5, sp, 0x2C);
        t7 = sltiu(t5, 23);
        sw(t6, sp, 0x34);
        if (t7 != 0) {
            // 0x0051e76c
            charge(ctx, 13);
            t7 = 0x7C0000;
            sw(zero, sp, 0x34);
            t7 = addiu(t7, -5256);  // &0x7BEB78
            t6 = sll(t5, 3);
            t6 = addu(t6, t7);
            a0 = s4;
            link(ctx, 0x51E784u);  // $ra first: the delay slot below depends on it
            ld(a1, t6, 0);
            call(ctx, gen::fn_dpcmp_005316d0);
            lw(t6, sp, 0x2C);
            v0 = slti(v0, 0);
            t7 = addiu(t6, -1);
            if (v0 != 0) t6 = t7;
            sw(t6, sp, 0x2C);
        }
        // 0x0051e7a0
        charge(ctx, 4);
        t7 = subu(s2, s3);
        s0 = addiu(t7, -1);
        if (i64(s0) < 0) {
            s0 = subu(0, s0);
            // 0x0051f5f0
            charge(ctx, 3);
            sw(zero, sp, 0x3C);
            sw(s0, sp, 0x18);
            backedge(ctx);
        } else {
            // 0x0051e7b0
            charge(ctx, 2);
            sw(s0, sp, 0x3C);
            sw(zero, sp, 0x18);
        }
        // 0x0051e7b8
        charge(ctx, 3);
        lw(t7, sp, 0x2C);
        lw(t5, sp, 0x3C);
        if (i64(t7) < 0) {
            // 0x0051f5d0
            charge(ctx, 8);
            lw(t6, sp, 0x18);
            lw(t7, sp, 0x2C);
            sw(zero, sp, 0x40);
            t6 = subu(t6, t7);
            t5 = subu(0, t7);
            sw(t6, sp, 0x18);
            sw(t5, sp, 0x1C);
            backedge(ctx);
        } else {
            // 0x0051e7c4
            charge(ctx, 4);
            sw(zero, sp, 0x1C);
            t5 = addu(t5, t7);
            sw(t7, sp, 0x40);
            sw(t5, sp, 0x3C);
        }
        // 0x0051e7d4
        charge(ctx, 7);
        lw(t7, sp, 0x8);
        t6 = sltiu(t7, 10);
        if (t6 == 0) t7 = 0;
        sw(t7, sp, 0x8);
        t7 = slti(t7, 6);
        s1 = 1;
        if (t7 == 0) {
            // 0x0051e7f0
            charge(ctx, 4);
            lw(t5, sp, 0x8);
            s1 = 0;
            t5 = addiu(t5, -4);
            sw(t5, sp, 0x8);
        }
        // 0x0051e800
        charge(ctx, 8);
        t7 = si(-1);
        lw(t5, sp, 0x8);
        t6 = 1;
        sw(t7, sp, 0x28);
        sw(t7, sp, 0x20);
        t7 = sltiu(t5, 6);
        sw(t6, sp, 0x38);
        if (t7 != 0) {
            // 0x0051e820
            charge(ctx, 7);
            t6 = 0x7C0000;
            t7 = sll(t5, 2);
            t6 = addiu(t6, -5376);  // &0x7BEB00
            t7 = addu(t7, t6);
            lw(t5, t7, 0);
            switch (t5.u()) {
            case 0x51E83Cu:  // table[0, 1]
                // 0x0051e83c
                charge(ctx, 2);
                sw(zero, sp, 0xC);
                s3 = 18;
                break;
            case 0x51F580u:  // table[2]
                // 0x0051f580
                charge(ctx, 1);
                sw(zero, sp, 0x38);
            L_0051f584:
                charge(ctx, 8);
                lw(t6, sp, 0xC);
                s3 = 1;
                t7 = slt(0, t6);
                if (t7 != 0) s3 = t6;
                sw(s3, sp, 0xC);
                sw(s3, sp, 0x28);
                sw(s3, sp, 0x20);
                backedge(ctx);
                break;
            case 0x51F584u:  // table[4]
                goto L_0051f584;
            case 0x51F5A4u:  // table[3]
                // 0x0051f5a4
                charge(ctx, 1);
                sw(zero, sp, 0x38);
            L_0051f5a8:
                charge(ctx, 10);
                lw(t6, sp, 0x2C);
                lw(t5, sp, 0xC);
                t7 = addu(t5, t6);
                s3 = addiu(t7, 1);
                sw(t7, sp, 0x28);
                sw(s3, sp, 0x20);
                t6 = slt(0, s3);
                t7 = 1;
                if (t6 == 0) s3 = t7;
                backedge(ctx);
                break;
            case 0x51F5A8u:  // table[5]
                goto L_0051f5a8;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, t5.u());
                return;
            }
        }
        // 0x0051e844
        charge(ctx, 4);
        sw(zero, s5, 68);
        t7 = sltiu(s3, 24);
        s0 = 4;
        if (t7 == 0) {
            // 0x0051e854
            charge(ctx, 1);
            t5 = 0;
            for (;;) {
                // 0x0051e858
                charge(ctx, 7);
                s0 = sll(s0, 1);
                t7 = addiu(s0, 20);
                t7 = sltu(s3, t7);
                t5 = addiu(t5, 1);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051e874
            charge(ctx, 1);
            sw(t5, s5, 68);
        }
        // 0x0051e878
        charge(ctx, 9);
        lw(a1, s5, 68);
        a0 = s5;
        jal(ctx, 0x51E87Cu, gen::fn__Balloc_00521578);
        sw(v0, sp, 0x54);
        lw(t5, sp, 0x20);
        sw(v0, s5, 64);
        t7 = sltiu(t5, 15);
        lw(s6, sp, 0x54);
        if (t7 != 0) {
            // 0x0051e89c
            charge(ctx, 2);
            lw(t6, sp, 0x2C);
            if (s1 == 0) {
                goto L_0051ea44;
            }
            // 0x0051e8a4
            charge(ctx, 5);
            s7 = s4;
            sw(t5, sp, 0x24);
            s3 = 2;
            sw(t6, sp, 0x30);
            if (i64(t6) > 0) {
                // 0x0051e8b8
                charge(ctx, 10);
                t7 = t6 & 0xF;
                lw(t5, sp, 0x2C);
                t6 = 0x7C0000;
                t7 = sll(t7, 3);
                t6 = addiu(t6, -5256);  // &0x7BEB78
                s0 = sra(t5, 4);
                t7 = addu(t7, t6);
                t6 = s0 & 0x10;
                ld(s1, t7, 0);
                if (t6 != 0) {
                    // 0x0051e8e0
                    charge(ctx, 7);
                    t7 = 0x7C0000;
                    a0 = s4;
                    ld(a1, t7, -5024);  // 0x7BEC60
                    s0 = s0 & 0xF;
                    s3 = 3;
                    jal(ctx, 0x51E8F0u, gen::fn_dpdiv_00531480);
                    s4 = v0;
                }
                // 0x0051e8fc
                charge(ctx, 2);
                t7 = 0x7C0000;
                if (s0 != 0) {
                    // 0x0051e904
                    charge(ctx, 2);
                    s2 = s0;
                    s0 = addiu(t7, -5056);
                    for (;;) {
                        // 0x0051e90c
                        charge(ctx, 3);
                        t7 = s2 & 0x1;
                        a0 = s1;
                        if (t7 != 0) {
                            // 0x0051e918
                            charge(ctx, 4);
                            ld(a1, s0, 0);
                            s3 = addiu(s3, 1);
                            jal(ctx, 0x51E91Cu, gen::fn_dpmul_00531230);
                            s1 = v0;
                        }
                        // 0x0051e928
                        charge(ctx, 3);
                        s2 = sra(s2, 1);
                        s0 = addiu(s0, 8);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0051e934
                charge(ctx, 4);
                a0 = s4;
                a1 = s1;
                jal(ctx, 0x51E938u, gen::fn_dpdiv_00531480);
                s4 = v0;
                goto L_0051e944;
            }
            // 0x0051f50c
            charge(ctx, 4);
            lw(t6, sp, 0x2C);
            s2 = subu(0, t6);
            t6 = s2 & 0xF;
            if (s2 == 0) {
                backedge(ctx);
            L_0051e944:
                charge(ctx, 1);
                lw(t7, sp, 0x34);
            } else {
                // 0x0051f51c
                charge(ctx, 10);
                t7 = 0x7C0000;
                t7 = addiu(t7, -5256);  // &0x7BEB78
                t6 = sll(t6, 3);
                t6 = addu(t6, t7);
                a1 = s4;
                ld(a0, t6, 0);
                s0 = sra(s2, 4);
                jal(ctx, 0x51F534u, gen::fn_dpmul_00531230);
                s4 = v0;
                if (s0 == 0) {
                    backedge(ctx);
                    goto L_0051e944;
                }
                // 0x0051f544
                charge(ctx, 3);
                s2 = s0;
                t7 = 0x7C0000;
                s0 = addiu(t7, -5056);  // &0x7BEC40
                for (;;) {
                    // 0x0051f550
                    charge(ctx, 3);
                    t7 = s2 & 0x1;
                    a1 = s4;
                    if (t7 != 0) {
                        // 0x0051f55c
                        charge(ctx, 4);
                        ld(a0, s0, 0);
                        s3 = addiu(s3, 1);
                        jal(ctx, 0x51F560u, gen::fn_dpmul_00531230);
                        s4 = v0;
                    }
                    // 0x0051f56c
                    charge(ctx, 3);
                    s2 = sra(s2, 1);
                    s0 = addiu(s0, 8);
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0051f578
                charge(ctx, 2);
                lw(t7, sp, 0x34);
                backedge(ctx);
            }
            // 0x0051e948
            charge(ctx, 2);
            a0 = s4;
            if (t7 != 0) {
                // 0x0051e950
                charge(ctx, 5);
                a1 = 1023;
                a1 = dsll32(a1, 20);
                jal(ctx, 0x51E954u, gen::fn_dpcmp_005316d0);
                lw(t5, sp, 0x20);
                if (i64(v0) >= 0) {
                    goto L_0051e998;
                }
                // 0x0051e964
                charge(ctx, 2);
                lw(t6, sp, 0x28);
                if (i64(t5) <= 0) {
                    goto L_0051e998;
                }
                // 0x0051e96c
                charge(ctx, 2);
                a1 = s4;
                if (i64(t6) <= 0) {
                L_0051ea2c:
                    charge(ctx, 6);
                    lw(t6, sp, 0x30);
                    s4 = s7;
                    lw(t7, sp, 0x24);
                    sw(t6, sp, 0x2C);
                    sw(t7, sp, 0x20);
                    lw(s6, sp, 0x54);
                    goto L_0051ea44;
                }
                // 0x0051e974
                charge(ctx, 9);
                a0 = 4105;
                sw(t6, sp, 0x20);
                a0 = dsll32(a0, 18);
                jal(ctx, 0x51E97Cu, gen::fn_dpmul_00531230);
                s3 = addiu(s3, 1);
                lw(t7, sp, 0x2C);
                s4 = v0;
                t7 = addiu(t7, -1);
                sw(t7, sp, 0x2C);
                goto L_0051e998;
            }
        L_0051e998:
            charge(ctx, 18);
            a0 = s3;
            jal(ctx, 0x51E998u, gen::fn_litodp_00531720);
            a0 = v0;
            a1 = s4;
            jal(ctx, 0x51E9A4u, gen::fn_dpmul_00531230);
            a1 = 4103;
            a0 = v0;
            a1 = dsll32(a1, 18);
            jal(ctx, 0x51E9B4u, gen::fn_dpadd_00531170);
            t7 = dsra32(v0, 0);
            lw(t5, sp, 0x20);
            t6 = lui(0xFCC0);
            s2 = dsll32(v0, 0);
            t7 = addu(t7, t6);
            s2 = dsrl32(s2, 0);
            t7 = dsll32(t7, 0);
            s2 = s2 | t7;
            if (t5 == 0) {
                // 0x0051e9e0
                charge(ctx, 12);
                a1 = 4101;
                sw(zero, sp, 0x4C);
                a0 = s4;
                a1 = dsll32(a1, 18);
                jal(ctx, 0x51E9ECu, gen::fn_dpsub_005311c8);
                sw(zero, sp, 0x50);
                s0 = v0;
                a0 = s2;
                a1 = v0;
                jal(ctx, 0x51EA00u, gen::fn_dpcmp_005316d0);
                a1 = s2;
                if (i64(v0) >= 0) {
                    // 0x0051ea10
                    charge(ctx, 7);
                    a0 = 0;
                    jal(ctx, 0x51EA10u, gen::fn_dpsub_005311c8);
                    a1 = v0;
                    a0 = s0;
                    jal(ctx, 0x51EA1Cu, gen::fn_dpcmp_005316d0);
                    lw(t7, sp, 0xC);
                    if (i64(v0) >= 0) {
                        goto L_0051ea2c;
                    }
                L_0051eb48:
                    charge(ctx, 3);
                    t7 = nor(0, t7);
                    sw(t7, sp, 0x2C);
                    backedge(ctx);
                    goto L_0051ead0;
                }
            L_0051eab4:
                charge(ctx, 1);
                lw(t5, sp, 0x54);
            L_0051eab8:
                charge(ctx, 6);
                t7 = 49;
                sb(t7, t5, 0);
                s6 = addiu(t5, 1);
                lw(t6, sp, 0x2C);
                t6 = addiu(t6, 1);
                sw(t6, sp, 0x2C);
            L_0051ead0:
                charge(ctx, 6);
                lw(a1, sp, 0x50);
                a0 = s5;
                jal(ctx, 0x51EAD4u, gen::fn__Bfree_00521620);
                lw(t7, sp, 0x4C);
                lw(t5, sp, 0x48);
                if (t7 != 0) {
                    // 0x0051eae8
                    charge(ctx, 2);
                    lw(a1, sp, 0x4C);
                    if (t5 != 0) {
                        // 0x0051eaf0
                        charge(ctx, 2);
                        if (t5 != t7) {
                            // 0x0051eaf8
                            charge(ctx, 4);
                            lw(a1, sp, 0x48);
                            a0 = s5;
                            jal(ctx, 0x51EAFCu, gen::fn__Bfree_00521620);
                            lw(a1, sp, 0x4C);
                        }
                    }
                    // 0x0051eb08
                    charge(ctx, 2);
                    a0 = s5;
                    jal(ctx, 0x51EB08u, gen::fn__Bfree_00521620);
                }
                goto L_0051eb10;
            }
            // 0x0051f344
            charge(ctx, 3);
            lw(t6, sp, 0x38);
            lw(t7, sp, 0x20);
            if (t6 != 0) {
                // 0x0051f350
                charge(ctx, 14);
                a0 = 511;
                a0 = dsll32(a0, 21);
                s3 = 0;
                t6 = sll(t7, 3);
                t7 = 0x7C0000;
                t7 = addiu(t7, -5256);  // &0x7BEB78
                t6 = addu(t6, t7);
                link(ctx, 0x51F36Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t6, -8);
                call(ctx, gen::fn_dpdiv_00531480);
                a1 = s2;
                a0 = v0;
                jal(ctx, 0x51F378u, gen::fn_dpsub_005311c8);
                s2 = v0;
                for (;;) {
                    // 0x0051f388
                    charge(ctx, 16);
                    a0 = s4;
                    jal(ctx, 0x51F388u, gen::fn_dptoli_005317d0);
                    s0 = v0;
                    a0 = v0;
                    jal(ctx, 0x51F394u, gen::fn_litodp_00531720);
                    a1 = v0;
                    a0 = s4;
                    jal(ctx, 0x51F3A0u, gen::fn_dpsub_005311c8);
                    t7 = addiu(s0, 48);
                    s1 = v0;
                    sb(t7, s6, 0);
                    a0 = v0;
                    a1 = s2;
                    jal(ctx, 0x51F3B8u, gen::fn_dpcmp_005316d0);
                    s6 = addiu(s6, 1);
                    if (i64(v0) < 0) {
                        backedge(ctx);
                        goto L_0051eb10;
                    }
                    // 0x0051f3c8
                    charge(ctx, 9);
                    a0 = 1023;
                    a1 = s1;
                    a0 = dsll32(a0, 20);
                    jal(ctx, 0x51F3D0u, gen::fn_dpsub_005311c8);
                    a0 = v0;
                    a1 = s2;
                    jal(ctx, 0x51F3DCu, gen::fn_dpcmp_005316d0);
                    lw(t5, sp, 0x20);
                    if (i64(v0) < 0) {
                        backedge(ctx);
                        goto L_0051ebdc;
                    }
                    // 0x0051f3ec
                    charge(ctx, 4);
                    s3 = addiu(s3, 1);
                    t7 = slt(s3, t5);
                    a1 = s2;
                    if (t7 == 0) {
                        backedge(ctx);
                        break;
                    }
                    // 0x0051f3fc
                    charge(ctx, 10);
                    a0 = 4105;
                    a0 = dsll32(a0, 18);
                    jal(ctx, 0x51F400u, gen::fn_dpmul_00531230);
                    a0 = 4105;
                    s2 = v0;
                    a1 = s1;
                    a0 = dsll32(a0, 18);
                    jal(ctx, 0x51F414u, gen::fn_dpmul_00531230);
                    s4 = v0;
                    backedge(ctx);
                }
                goto L_0051ea2c;
            }
            // 0x0051f424
            charge(ctx, 9);
            a1 = s2;
            s3 = 1;
            t6 = sll(t7, 3);
            t7 = 0x7C0000;
            t7 = addiu(t7, -5256);  // &0x7BEB78
            t6 = addu(t6, t7);
            link(ctx, 0x51F43Cu);  // $ra first: the delay slot below depends on it
            ld(a0, t6, -8);
            call(ctx, gen::fn_dpmul_00531230);
            s2 = v0;
            for (;;) {
                // 0x0051f448
                charge(ctx, 14);
                a0 = s4;
                jal(ctx, 0x51F448u, gen::fn_dptoli_005317d0);
                s0 = v0;
                a0 = v0;
                jal(ctx, 0x51F454u, gen::fn_litodp_00531720);
                a1 = v0;
                a0 = s4;
                jal(ctx, 0x51F460u, gen::fn_dpsub_005311c8);
                t7 = addiu(s0, 48);
                s1 = v0;
                sb(t7, s6, 0);
                lw(t5, sp, 0x20);
                s6 = addiu(s6, 1);
                if (s3 == t5) {
                    break;
                }
                // 0x0051f4f0
                charge(ctx, 7);
                a0 = 4105;
                a1 = v0;
                a0 = dsll32(a0, 18);
                s3 = addiu(s3, 1);
                jal(ctx, 0x51F4FCu, gen::fn_dpmul_00531230);
                s4 = v0;
                backedge(ctx);
            }
            // 0x0051f480
            charge(ctx, 10);
            s0 = 511;
            a1 = s2;
            s0 = dsll32(s0, 21);
            a0 = s0;
            jal(ctx, 0x51F48Cu, gen::fn_dpadd_00531170);
            a0 = v0;
            a1 = s1;
            jal(ctx, 0x51F498u, gen::fn_dpcmp_005316d0);
            a0 = s0;
            if (i64(v0) >= 0) {
                // 0x0051f4a8
                charge(ctx, 7);
                a1 = s2;
                jal(ctx, 0x51F4A8u, gen::fn_dpsub_005311c8);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x51F4B4u, gen::fn_dpcmp_005316d0);
                t6 = 48;
                if (i64(v0) >= 0) {
                    backedge(ctx);
                    goto L_0051ea2c;
                }
                // 0x0051f4c4
                charge(ctx, 1);
                s6 = addiu(s6, -1);
                for (;;) {
                    // 0x0051f4c8
                    charge(ctx, 7);
                    lb(t7, s6, 0);
                    if (t7 != t6) {
                        break;
                    }
                    s6 = addiu(s6, -1);
                    backedge(ctx);
                }
                // 0x0051f4e4
                charge(ctx, 2);
                s6 = addiu(s6, 1);
                backedge(ctx);
                goto L_0051eb10;
            }
            backedge(ctx);
        L_0051ebdc:
            charge(ctx, 7);
            s6 = addiu(s6, -1);
            t7 = 57;
            lbu(t5, s6, 0);
            t6 = sll(t5, 24);
            t6 = sra(t6, 24);
            cc = t6 != t7;  // the condition, before the delay slot changes it
            t7 = addiu(t5, 1);
            if (!cc) {
                // 0x0051ebf8
                charge(ctx, 2);
                t6 = 57;
                lw(t7, sp, 0x54);
                for (;;) {
                    // 0x0051ec00
                    charge(ctx, 2);
                    lw(t5, sp, 0x2C);
                    if (s6 == t7) {
                        goto L_0051ec30;
                    }
                    // 0x0051ec08
                    charge(ctx, 6);
                    s6 = addiu(s6, -1);
                    lbu(t5, s6, 0);
                    t7 = sll(t5, 24);
                    t7 = sra(t7, 24);
                    cc = t7 == t6;  // the condition, before the delay slot changes it
                    lw(t7, sp, 0x54);
                    if (cc) {
                        backedge(ctx);
                        continue;
                    }
                    break;
                }
            L_0051ec20:
                charge(ctx, 1);
                t7 = addiu(t5, 1);
            }
            // 0x0051ec24
            charge(ctx, 3);
            sb(t7, s6, 0);
            s6 = addiu(s6, 1);
            backedge(ctx);
        L_0051eb10:
            charge(ctx, 1);
            a0 = s5;
            goto L_0051eb14;
        }
    L_0051ea44:
        charge(ctx, 3);
        lw(v0, sp, 0x0);
        lw(t5, sp, 0x2C);
        if (i64(v0) >= 0) {
            // 0x0051ea50
            charge(ctx, 3);
            t7 = slti(t5, 15);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 0x7C0000;
            if (cc) {
                goto L_0051ec84;
            }
            // 0x0051ea5c
            charge(ctx, 7);
            t6 = sll(t5, 3);
            t7 = addiu(t7, -5256);
            t6 = addu(t6, t7);
            ld(s1, t6, 0);
            lw(t6, sp, 0xC);
            if (i64(t6) >= 0) {
                s3 = 1;
            } else {
                // 0x0051ea78
                charge(ctx, 3);
                lw(t7, sp, 0x20);
                if (i64(t7) > 0) {
                    s3 = 1;
                    goto L_0051eb54;
                }
                // 0x0051ea84
                charge(ctx, 3);
                sw(zero, sp, 0x4C);
                sw(zero, sp, 0x50);
                if (i64(t7) < 0) {
                L_0051eb44:
                    charge(ctx, 1);
                    lw(t7, sp, 0xC);
                    goto L_0051eb48;
                }
                // 0x0051ea90
                charge(ctx, 9);
                a1 = 4101;
                a0 = s1;
                a1 = dsll32(a1, 18);
                jal(ctx, 0x51EA98u, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s4;
                jal(ctx, 0x51EAA4u, gen::fn_dpcmp_005316d0);
                lw(t7, sp, 0xC);
                if (i64(v0) <= 0) {
                    goto L_0051eb48;
                }
                goto L_0051eab4;
            }
        L_0051eb54:
            charge(ctx, 1);
            a1 = s1;
            for (;;) {
                // 0x0051eb58
                charge(ctx, 18);
                a0 = s4;
                jal(ctx, 0x51EB58u, gen::fn_dpdiv_00531480);
                a0 = v0;
                jal(ctx, 0x51EB60u, gen::fn_dptoli_005317d0);
                s0 = v0;
                a0 = v0;
                jal(ctx, 0x51EB6Cu, gen::fn_litodp_00531720);
                a0 = v0;
                a1 = s1;
                jal(ctx, 0x51EB78u, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s4;
                jal(ctx, 0x51EB84u, gen::fn_dpsub_005311c8);
                t7 = addiu(s0, 48);
                sb(t7, s6, 0);
                lw(t5, sp, 0x20);
                s6 = addiu(s6, 1);
                if (s3 == t5) {
                    goto L_0051eba0_75;
                }
                // 0x0051ec50
                charge(ctx, 11);
                a0 = 4105;
                a1 = v0;
                a0 = dsll32(a0, 18);
                s3 = addiu(s3, 1);
                jal(ctx, 0x51EC5Cu, gen::fn_dpmul_00531230);
                a0 = v0;
                a1 = 0;
                s4 = v0;
                jal(ctx, 0x51EC6Cu, gen::fn_dpcmp_005316d0);
                a1 = s1;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051ec7c
            charge(ctx, 2);
            a0 = s5;
            backedge(ctx);
            goto L_0051eb14;
        }
    L_0051ec84:
        charge(ctx, 8);
        lw(t7, sp, 0x8);
        lw(s1, sp, 0x18);
        lw(s2, sp, 0x1C);
        sw(zero, sp, 0x48);
        sw(zero, sp, 0x4C);
        lw(t5, sp, 0x38);
        s7 = slti(t7, 2);
        if (t5 != 0) {
            // 0x0051eca4
            charge(ctx, 2);
            lw(t6, sp, 0x44);
            if (s7 == 0) {
                // 0x0051f2f4
                charge(ctx, 6);
                lw(t7, sp, 0x20);
                lw(t5, sp, 0x1C);
                s0 = addiu(t7, -1);
                t7 = slt(t5, s0);
                s2 = subu(t5, s0);
                if (t7 != 0) {
                    // 0x0051f30c
                    charge(ctx, 7);
                    lw(t6, sp, 0x40);
                    s0 = subu(s0, t5);
                    t5 = addu(t5, s0);
                    s2 = 0;
                    t6 = addu(t6, s0);
                    sw(t5, sp, 0x1C);
                    sw(t6, sp, 0x40);
                }
                // 0x0051f328
                charge(ctx, 3);
                lw(s3, sp, 0x20);
                lw(t5, sp, 0x3C);
                if (i64(s3) >= 0) {
                    backedge(ctx);
                } else {
                    // 0x0051f334
                    charge(ctx, 4);
                    lw(t7, sp, 0x18);
                    s1 = subu(t7, s3);
                    s3 = 0;
                    backedge(ctx);
                }
            } else {
                // 0x0051ecac
                charge(ctx, 2);
                s3 = addiu(v0, 1075);
                if (t6 == 0) {
                    // 0x0051ecb4
                    charge(ctx, 3);
                    lw(t7, sp, 0x4);
                    t6 = 54;
                    s3 = subu(t6, t7);
                }
                // 0x0051ecc0
                charge(ctx, 1);
                lw(t5, sp, 0x3C);
            }
            // 0x0051ecc4
            charge(ctx, 9);
            a0 = s5;
            a1 = 1;
            t5 = addu(t5, s3);
            link(ctx, 0x51ECD0u);  // $ra first: the delay slot below depends on it
            sw(t5, sp, 0x3C);
            call(ctx, gen::fn__i2b_005219c8);
            lw(t6, sp, 0x18);
            sw(v0, sp, 0x4C);
            t6 = addu(t6, s3);
            sw(t6, sp, 0x18);
        }
        // 0x0051ece8
        charge(ctx, 2);
        lw(t7, sp, 0x3C);
        if (i64(s1) > 0) {
            // 0x0051ecf0
            charge(ctx, 2);
            lw(s3, sp, 0x3C);
            if (i64(t7) > 0) {
                // 0x0051ecf8
                charge(ctx, 9);
                lw(t5, sp, 0x3C);
                t7 = slt(s1, s3);
                lw(t6, sp, 0x18);
                if (t7 != 0) s3 = s1;
                t5 = subu(t5, s3);
                t6 = subu(t6, s3);
                sw(t5, sp, 0x3C);
                s1 = subu(s1, s3);
                sw(t6, sp, 0x18);
            }
        }
        // 0x0051ed1c
        charge(ctx, 3);
        lw(t7, sp, 0x1C);
        lw(t5, sp, 0x38);
        if (i64(t7) > 0) {
            // 0x0051ed28
            charge(ctx, 2);
            lw(a2, sp, 0x1C);
            if (t5 == 0) {
                // 0x0051f2ec
                charge(ctx, 2);
                a1 = fp;
                backedge(ctx);
            L_0051ed80:
                charge(ctx, 3);
                a0 = s5;
                jal(ctx, 0x51ED80u, gen::fn__pow5mult_00521c08);
                fp = v0;
            } else {
                // 0x0051ed30
                charge(ctx, 2);
                lw(a1, sp, 0x4C);
                if (i64(s2) > 0) {
                    // 0x0051ed38
                    charge(ctx, 13);
                    a0 = s5;
                    a2 = s2;
                    jal(ctx, 0x51ED3Cu, gen::fn__pow5mult_00521c08);
                    sw(v0, sp, 0x4C);
                    a2 = fp;
                    a0 = s5;
                    link(ctx, 0x51ED50u);  // $ra first: the delay slot below depends on it
                    lw(a1, sp, 0x4C);
                    call(ctx, gen::fn__multiply_00521a00);
                    s0 = v0;
                    a1 = fp;
                    a0 = s5;
                    fp = s0;
                    jal(ctx, 0x51ED64u, gen::fn__Bfree_00521620);
                }
                // 0x0051ed6c
                charge(ctx, 4);
                lw(t6, sp, 0x1C);
                s0 = subu(t6, s2);
                a1 = fp;
                if (s0 != 0) {
                    // 0x0051ed7c
                    charge(ctx, 1);
                    a2 = s0;
                    goto L_0051ed80;
                }
            }
        }
        // 0x0051ed8c
        charge(ctx, 7);
        a0 = s5;
        a1 = 1;
        jal(ctx, 0x51ED90u, gen::fn__i2b_005219c8);
        sw(v0, sp, 0x50);
        lw(t7, sp, 0x40);
        lw(a1, sp, 0x50);
        if (i64(t7) > 0) {
            // 0x0051eda8
            charge(ctx, 4);
            a0 = s5;
            link(ctx, 0x51EDACu);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x40);
            call(ctx, gen::fn__pow5mult_00521c08);
            sw(v0, sp, 0x50);
        }
        // 0x0051edb8
        charge(ctx, 2);
        s0 = 0;
        if (s7 != 0) {
            // 0x0051edc0
            charge(ctx, 5);
            t7 = si(-4096);
            t7 = dsrl(t7, 12);
            t7 = s4 & t7;
            cc = t7 != 0;  // the condition, before the delay slot changes it
            lw(t7, sp, 0x40);
            if (!cc) {
                // 0x0051edd4
                charge(ctx, 5);
                t7 = dsra32(s4, 0);
                t6 = 0x7FF00000;
                t7 = t7 & t6;
                lw(t5, sp, 0x18);
                if (t7 != 0) {
                    // 0x0051ede8
                    charge(ctx, 6);
                    s0 = 1;
                    lw(t6, sp, 0x3C);
                    t5 = addiu(t5, 1);
                    t6 = addiu(t6, 1);
                    sw(t5, sp, 0x18);
                    sw(t6, sp, 0x3C);
                }
                goto L_0051ee00;
            }
            goto L_0051ee04;
        }
    L_0051ee00:
        charge(ctx, 1);
        lw(t7, sp, 0x40);
    L_0051ee04:
        charge(ctx, 2);
        lw(t5, sp, 0x50);
        if (t7 == 0) {
            // 0x0051f2dc
            charge(ctx, 4);
            lw(t5, sp, 0x3C);
            t7 = addiu(t5, 1);
            s3 = t7 & 0x1F;
            backedge(ctx);
        } else {
            // 0x0051ee0c
            charge(ctx, 8);
            lw(t7, t5, 16);
            t7 = sll(t7, 2);
            t7 = addu(t7, t5);
            link(ctx, 0x51EE18u);  // $ra first: the delay slot below depends on it
            lw(a0, t7, 16);
            call(ctx, gen::fn__hi0bits_00521888);
            lw(t6, sp, 0x3C);
            v0 = subu(t6, v0);
            s3 = v0 & 0x1F;
        }
        // 0x0051ee2c
        charge(ctx, 2);
        t7 = 32;
        if (s3 != 0) {
            // 0x0051ee34
            charge(ctx, 1);
            s3 = subu(t7, s3);
        }
        // 0x0051ee38
        charge(ctx, 3);
        t7 = slti(s3, 5);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = slti(s3, 4);
        if (!cc) {
            // 0x0051ee44
            charge(ctx, 7);
            lw(t6, sp, 0x3C);
            s3 = addiu(s3, -4);
            lw(t7, sp, 0x18);
            t6 = addu(t6, s3);
            t7 = addu(t7, s3);
            sw(t6, sp, 0x3C);
            sw(t7, sp, 0x18);
            goto L_0051ee60;
        }
        // 0x0051f2b8
        charge(ctx, 2);
        lw(t5, sp, 0x3C);
        if (t7 == 0) {
            backedge(ctx);
        } else {
            // 0x0051f2c0
            charge(ctx, 7);
            s3 = addiu(s3, 28);
            lw(t6, sp, 0x18);
            t5 = addu(t5, s3);
            t6 = addu(t6, s3);
            sw(t5, sp, 0x3C);
            sw(t6, sp, 0x18);
            backedge(ctx);
        L_0051ee60:
            charge(ctx, 1);
            s1 = addu(s1, s3);
        }
        // 0x0051ee64
        charge(ctx, 3);
        lw(t7, sp, 0x18);
        lw(a2, sp, 0x18);
        if (i64(t7) > 0) {
            // 0x0051ee70
            charge(ctx, 4);
            a1 = fp;
            a0 = s5;
            jal(ctx, 0x51EE74u, gen::fn__lshift_00521d10);
            fp = v0;
        }
        // 0x0051ee80
        charge(ctx, 3);
        lw(t5, sp, 0x3C);
        lw(a1, sp, 0x50);
        if (i64(t5) > 0) {
            // 0x0051ee8c
            charge(ctx, 4);
            a0 = s5;
            link(ctx, 0x51EE90u);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x3C);
            call(ctx, gen::fn__lshift_00521d10);
            sw(v0, sp, 0x50);
        }
        // 0x0051ee9c
        charge(ctx, 3);
        lw(t6, sp, 0x34);
        lw(a1, sp, 0x50);
        if (t6 != 0) {
            // 0x0051eea8
            charge(ctx, 4);
            a0 = fp;
            jal(ctx, 0x51EEA8u, gen::fn___mcmp_00521e70);
            lw(t7, sp, 0x20);
            if (i64(v0) < 0) {
                // 0x0051eeb8
                charge(ctx, 11);
                a1 = fp;
                a0 = s5;
                a2 = 10;
                a3 = 0;
                jal(ctx, 0x51EEC4u, gen::fn__multadd_00521650);
                lw(t7, sp, 0x2C);
                fp = v0;
                lw(t5, sp, 0x38);
                t7 = addiu(t7, -1);
                sw(t7, sp, 0x2C);
                if (t5 != 0) {
                    // 0x0051eee4
                    charge(ctx, 6);
                    lw(a1, sp, 0x4C);
                    a0 = s5;
                    a2 = 10;
                    a3 = 0;
                    jal(ctx, 0x51EEF0u, gen::fn__multadd_00521650);
                    sw(v0, sp, 0x4C);
                }
                // 0x0051eefc
                charge(ctx, 2);
                lw(t6, sp, 0x28);
                sw(t6, sp, 0x20);
                goto L_0051ef04;
            }
            goto L_0051ef08;
        }
    L_0051ef04:
        charge(ctx, 1);
        lw(t7, sp, 0x20);
    L_0051ef08:
        charge(ctx, 2);
        cc = i64(t7) > 0;  // the condition, before the delay slot changes it
        lw(t7, sp, 0x38);
        if (!cc) {
            // 0x0051ef10
            charge(ctx, 4);
            lw(t5, sp, 0x8);
            t7 = slti(t5, 3);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            lw(t7, sp, 0x38);
            if (cc) {
                goto L_0051ef60;
            }
            // 0x0051ef20
            charge(ctx, 3);
            lw(t6, sp, 0x20);
            lw(a1, sp, 0x50);
            if (i64(t6) < 0) {
                backedge(ctx);
                goto L_0051eb44;
            }
            // 0x0051ef2c
            charge(ctx, 10);
            a0 = s5;
            a2 = 5;
            a3 = 0;
            jal(ctx, 0x51EF34u, gen::fn__multadd_00521650);
            sw(v0, sp, 0x50);
            a0 = fp;
            link(ctx, 0x51EF44u);  // $ra first: the delay slot below depends on it
            lw(a1, sp, 0x50);
            call(ctx, gen::fn___mcmp_00521e70);
            lw(t5, sp, 0x54);
            if (i64(v0) > 0) {
                backedge(ctx);
                goto L_0051eab8;
            }
            // 0x0051ef54
            charge(ctx, 2);
            lw(t7, sp, 0xC);
            backedge(ctx);
            goto L_0051eb48;
        }
    L_0051ef60:
        charge(ctx, 2);
        s3 = 1;
        if (t7 != 0) {
            // 0x0051ef68
            charge(ctx, 2);
            lw(a1, sp, 0x4C);
            if (i64(s1) > 0) {
                // 0x0051ef70
                charge(ctx, 4);
                a2 = s1;
                a0 = s5;
                jal(ctx, 0x51EF74u, gen::fn__lshift_00521d10);
                sw(v0, sp, 0x4C);
            }
            // 0x0051ef80
            charge(ctx, 3);
            lw(t5, sp, 0x4C);
            sw(t5, sp, 0x48);
            if (s0 != 0) {
                // 0x0051ef8c
                charge(ctx, 16);
                lw(a1, t5, 4);
                a0 = s5;
                jal(ctx, 0x51EF90u, gen::fn__Balloc_00521578);
                lw(t6, sp, 0x48);
                a0 = addiu(v0, 12);
                sw(v0, sp, 0x4C);
                lw(a2, t6, 16);
                a1 = addiu(t6, 12);
                a2 = sll(a2, 2);
                a2 = addiu(a2, 8);
                jal(ctx, 0x51EFB0u, gen::fn_memcpy_00521250);
                lw(a1, sp, 0x4C);
                a0 = s5;
                a2 = 1;
                jal(ctx, 0x51EFC0u, gen::fn__lshift_00521d10);
                sw(v0, sp, 0x4C);
            }
            // 0x0051efcc
            charge(ctx, 5);
            t7 = dsll32(s4, 0);
            s3 = 1;
            t7 = dsra32(t7, 0);
            s7 = t7 & 0x1;
            sw(s7, sp, 0x58);
            for (;;) {
                // 0x0051efe0
                charge(ctx, 15);
                lw(a1, sp, 0x50);
                a0 = fp;
                jal(ctx, 0x51EFE4u, gen::fn_quorem_0051e280);
                lw(a1, sp, 0x48);
                a0 = fp;
                s4 = addiu(v0, 48);
                jal(ctx, 0x51EFF4u, gen::fn___mcmp_00521e70);
                lw(a1, sp, 0x50);
                s0 = v0;
                lw(a2, sp, 0x4C);
                a0 = s5;
                jal(ctx, 0x51F008u, gen::fn___mdiff_00521ed8);
                lw(t7, v0, 12);
                s1 = v0;
                if (t7 != 0) {
                    // 0x0051f268
                    charge(ctx, 2);
                    s2 = 1;
                    backedge(ctx);
                } else {
                    // 0x0051f01c
                    charge(ctx, 4);
                    a0 = fp;
                    a1 = v0;
                    jal(ctx, 0x51F020u, gen::fn___mcmp_00521e70);
                    s2 = v0;
                }
                // 0x0051f02c
                charge(ctx, 5);
                a1 = s1;
                a0 = s5;
                jal(ctx, 0x51F030u, gen::fn__Bfree_00521620);
                lw(t7, sp, 0x8);
                if (s2 == 0) {
                    // 0x0051f040
                    charge(ctx, 2);
                    if (t7 != 0) {
                        goto L_0051f0e0;
                    }
                    // 0x0051f048
                    charge(ctx, 2);
                    t7 = 57;
                    if (s7 != 0) {
                        goto L_0051f0e0;
                    }
                    break;
                }
            L_0051f0e0:
                charge(ctx, 2);
                if (i64(s0) < 0) {
                    goto L_0051f100;
                }
                // 0x0051f0e8
                charge(ctx, 2);
                lw(t5, sp, 0x8);
                if (s0 == 0) {
                    // 0x0051f0f0
                    charge(ctx, 2);
                    lw(t6, sp, 0x58);
                    if (t5 != 0) {
                        goto L_0051f158;
                    }
                    // 0x0051f0f8
                    charge(ctx, 2);
                    if (t6 != 0) {
                        goto L_0051f158;
                    }
                    goto L_0051f100;
                }
            L_0051f158:
                charge(ctx, 2);
                t7 = 57;
                if (i64(s2) > 0) {
                    goto L_0051f160_168;
                }
                // 0x0051f170
                charge(ctx, 4);
                sb(s4, s6, 0);
                lw(t7, sp, 0x20);
                s6 = addiu(s6, 1);
                if (s3 == t7) {
                    goto L_0051f1fc;
                }
                // 0x0051f180
                charge(ctx, 9);
                a1 = fp;
                a0 = s5;
                a2 = 10;
                a3 = 0;
                jal(ctx, 0x51F18Cu, gen::fn__multadd_00521650);
                lw(t5, sp, 0x48);
                lw(t6, sp, 0x4C);
                fp = v0;
                if (t5 != t6) {
                    // 0x0051f1c8
                    charge(ctx, 13);
                    lw(a1, sp, 0x48);
                    a2 = 10;
                    a3 = 0;
                    a0 = s5;
                    jal(ctx, 0x51F1D4u, gen::fn__multadd_00521650);
                    sw(v0, sp, 0x48);
                    a0 = s5;
                    lw(a1, sp, 0x4C);
                    a2 = 10;
                    a3 = 0;
                    jal(ctx, 0x51F1ECu, gen::fn__multadd_00521650);
                    sw(v0, sp, 0x4C);
                    backedge(ctx);
                } else {
                    // 0x0051f1a4
                    charge(ctx, 7);
                    lw(a1, sp, 0x4C);
                    a0 = s5;
                    a2 = 10;
                    a3 = 0;
                    jal(ctx, 0x51F1B0u, gen::fn__multadd_00521650);
                    sw(v0, sp, 0x4C);
                    sw(v0, sp, 0x48);
                }
                // 0x0051f1c0
                charge(ctx, 2);
                s3 = addiu(s3, 1);
                backedge(ctx);
            }
            // 0x0051f050
            charge(ctx, 2);
            cc = s4 == t7;  // the condition, before the delay slot changes it
            t7 = slt(s2, s0);
            if (!cc) {
                // 0x0051f058
                charge(ctx, 1);
                s4 = addu(s4, t7);
            L_0051f05c:
                charge(ctx, 1);
                sb(s4, s6, 0);
                goto L_0051f060;
            }
        L_0051f068:
            charge(ctx, 1);
            t7 = 57;
        L_0051f06c:
            charge(ctx, 3);
            sb(t7, s6, 0);
            s6 = addiu(s6, 1);
            s6 = addiu(s6, -1);
            goto L_0051f078;
        }
        for (;;) {
            // 0x0051f270
            charge(ctx, 10);
            lw(a1, sp, 0x50);
            a0 = fp;
            jal(ctx, 0x51F274u, gen::fn_quorem_0051e280);
            t6 = s6;
            s4 = addiu(v0, 48);
            sb(s4, t6, 0);
            lw(t5, sp, 0x20);
            t7 = slt(s3, t5);
            s6 = addiu(s6, 1);
            if (t7 != 0) {
                // 0x0051f298
                charge(ctx, 8);
                a1 = fp;
                a0 = s5;
                a2 = 10;
                a3 = 0;
                jal(ctx, 0x51F2A4u, gen::fn__multadd_00521650);
                s3 = addiu(s3, 1);
                fp = v0;
                backedge(ctx);
                continue;
            }
            backedge(ctx);
            break;
        }
    L_0051f1fc:
        charge(ctx, 10);
        a1 = fp;
        a0 = s5;
        a2 = 1;
        jal(ctx, 0x51F204u, gen::fn__lshift_00521d10);
        lw(a1, sp, 0x50);
        fp = v0;
        a0 = v0;
        jal(ctx, 0x51F214u, gen::fn___mcmp_00521e70);
        if (i64(v0) > 0) {
            s6 = addiu(s6, -1);
            backedge(ctx);
        L_0051f078:
            charge(ctx, 6);
            t7 = 57;
            lbu(t5, s6, 0);
            t6 = sll(t5, 24);
            t6 = sra(t6, 24);
            cc = t6 != t7;  // the condition, before the delay slot changes it
            t7 = addiu(t5, 1);
            if (!cc) {
                // 0x0051f090
                charge(ctx, 2);
                t6 = 57;
                lw(t7, sp, 0x54);
                for (;;) {
                    // 0x0051f098
                    charge(ctx, 2);
                    lw(t5, sp, 0x2C);
                    if (s6 == t7) {
                        goto L_0051f0c4;
                    }
                    // 0x0051f0a0
                    charge(ctx, 6);
                    s6 = addiu(s6, -1);
                    lbu(t5, s6, 0);
                    t7 = sll(t5, 24);
                    t7 = sra(t7, 24);
                    cc = t7 == t6;  // the condition, before the delay slot changes it
                    lw(t7, sp, 0x54);
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0051f0b8
                charge(ctx, 1);
                t7 = addiu(t5, 1);
            }
            // 0x0051f0bc
            charge(ctx, 2);
            sb(t7, s6, 0);
            backedge(ctx);
        L_0051f060:
            charge(ctx, 2);
            s6 = addiu(s6, 1);
            backedge(ctx);
        } else {
            // 0x0051f224
            charge(ctx, 2);
            t6 = 48;
            if (v0 == 0) {
                // 0x0051f22c
                charge(ctx, 3);
                t7 = s4 & 0x1;
                if (t7 != 0) {
                    s6 = addiu(s6, -1);
                    backedge(ctx);
                    goto L_0051f078;
                }
                // 0x0051f238
                charge(ctx, 1);
                t6 = 48;
                goto L_0051f23c;
            }
        L_0051f23c:
            charge(ctx, 1);
            s6 = addiu(s6, -1);
            for (;;) {
                // 0x0051f240
                charge(ctx, 7);
                lb(t7, s6, 0);
                if (t7 != t6) {
                    break;
                }
                s6 = addiu(s6, -1);
                backedge(ctx);
            }
            // 0x0051f25c
            charge(ctx, 2);
            s6 = addiu(s6, 1);
            backedge(ctx);
        }
        goto L_0051ead0;
    }
    // 0x0051e618
    charge(ctx, 8);
    t6 = 0x7C0000;
    lw(t5, sp, 0x10);
    t7 = 1;
    s6 = addiu(t6, -5408);  // &0x7BEAE0
    sw(t7, t5, 0);
    lw(t6, sp, 0x14);
    t7 = addiu(s6, 1);  // &0x7BEAE1
    if (t6 == 0) {
        backedge(ctx);
    } else {
        // 0x0051e638
        charge(ctx, 2);
        sw(t7, t6, 0);
        backedge(ctx);
    }
L_0051e5c8:
    charge(ctx, 1);
    v0 = s6;
    // 0x0051e5cc (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x60);
    ld(s1, sp, 0x68);
    ld(s2, sp, 0x70);
    ld(s3, sp, 0x78);
    ld(s4, sp, 0x80);
    ld(s5, sp, 0x88);
    ld(s6, sp, 0x90);
    ld(s7, sp, 0x98);
    ld(fp, sp, 0xA0);
    ld(ra, sp, 0xA8);
    sp = addiu(sp, 0xB0);
    return;
L_0051eb14:
    charge(ctx, 10);
    a1 = fp;
    jal(ctx, 0x51EB14u, gen::fn__Bfree_00521620);
    sb(zero, s6, 0);
    lw(t6, sp, 0x2C);
    lw(t5, sp, 0x10);
    t7 = addiu(t6, 1);
    sw(t7, t5, 0);
    lw(t6, sp, 0x14);
    if (t6 != 0) {
        sw(s6, t6, 0);
    }
    // 0x0051eb3c
    charge(ctx, 2);
    lw(v0, sp, 0x54);
    backedge(ctx);
    // 0x0051e5cc (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x60);
    ld(s1, sp, 0x68);
    ld(s2, sp, 0x70);
    ld(s3, sp, 0x78);
    ld(s4, sp, 0x80);
    ld(s5, sp, 0x88);
    ld(s6, sp, 0x90);
    ld(s7, sp, 0x98);
    ld(fp, sp, 0xA0);
    ld(ra, sp, 0xA8);
    sp = addiu(sp, 0xB0);
    return;
L_0051eba0_75:
    charge(ctx, 9);
    a0 = v0;
    a1 = v0;
    jal(ctx, 0x51EBA4u, gen::fn_dpadd_00531170);
    s2 = v0;
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x51EBB4u, gen::fn_dpcmp_005316d0);
    a0 = s1;
    if (i64(v0) < 0) {
        goto L_0051ebdc;
    }
    // 0x0051ebc4
    charge(ctx, 4);
    a1 = s2;
    jal(ctx, 0x51EBC4u, gen::fn_dpcmp_005316d0);
    t7 = s0 & 0x1;
    if (v0 != 0) {
        backedge(ctx);
        goto L_0051eb10;
    }
    // 0x0051ebd4
    charge(ctx, 2);
    a0 = s5;
    if (t7 != 0) {
        goto L_0051ebdc;
    }
    backedge(ctx);
    goto L_0051eb14;
L_0051ec30:
    charge(ctx, 7);
    t7 = 48;
    lw(t6, sp, 0x54);
    t5 = addiu(t5, 1);
    sw(t5, sp, 0x2C);
    sb(t7, t6, 0);
    t5 = 48;
    backedge(ctx);
    goto L_0051ec20;
L_0051f0c4:
    charge(ctx, 7);
    t7 = 49;
    lw(t6, sp, 0x54);
    t5 = addiu(t5, 1);
    sw(t5, sp, 0x2C);
    s6 = addiu(t6, 1);
    sb(t7, t6, 0);
    backedge(ctx);
    goto L_0051ead0;
L_0051f100:
    charge(ctx, 2);
    a1 = fp;
    if (i64(s2) <= 0) {
        backedge(ctx);
        goto L_0051f05c;
    }
    // 0x0051f108
    charge(ctx, 9);
    a0 = s5;
    a2 = 1;
    jal(ctx, 0x51F10Cu, gen::fn__lshift_00521d10);
    lw(a1, sp, 0x50);
    fp = v0;
    a0 = v0;
    jal(ctx, 0x51F11Cu, gen::fn___mcmp_00521e70);
    if (i64(v0) > 0) {
        s4 = addiu(s4, 1);
    } else {
        // 0x0051f12c
        charge(ctx, 2);
        if (v0 != 0) {
            sb(s4, s6, 0);
            backedge(ctx);
            goto L_0051f060;
        }
        // 0x0051f134
        charge(ctx, 3);
        t7 = s4 & 0x1;
        if (t7 == 0) {
            sb(s4, s6, 0);
            backedge(ctx);
            goto L_0051f060;
        }
        // 0x0051f140
        charge(ctx, 1);
        s4 = addiu(s4, 1);
        goto L_0051f144;
    }
L_0051f144:
    charge(ctx, 3);
    t7 = 58;
    cc = s4 == t7;  // the condition, before the delay slot changes it
    t7 = 57;
    if (cc) {
        backedge(ctx);
        goto L_0051f06c;
    }
    // 0x0051f150
    charge(ctx, 2);
    sb(s4, s6, 0);
    backedge(ctx);
    goto L_0051f060;
L_0051f160_168:
    charge(ctx, 2);
    cc = s4 == t7;  // the condition, before the delay slot changes it
    t7 = addiu(s4, 1);
    if (cc) {
        backedge(ctx);
        goto L_0051f068;
    }
    // 0x0051f168
    charge(ctx, 2);
    sb(t7, s6, 0);
    backedge(ctx);
    goto L_0051f060;
}

// 0x0051F6A0 exit -- 136 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// Run the atexit handlers (newest first, every block), the cleanup hook, then _exit (sub_100218).
void exit(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051f6a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t7 = 0x780000;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(t6, t7, 12080);  // 0x782F30
    lw(s2, t6, 328);
    s3 = a0;
    if (s2 != 0) {
        // 0x0051f6cc
        charge(ctx, 1);
        lw(s1, s2, 4);
        for (;;) {
            // 0x0051f6d0
            charge(ctx, 3);
            s1 = addiu(s1, -1);
            t7 = sll(s1, 2);
            if (i64(s1) >= 0) {
                // 0x0051f6dc
                charge(ctx, 2);
                t7 = addu(t7, s2);
                s0 = addiu(t7, 8);
                for (;;) {
                    // 0x0051f6e4
                    charge(ctx, 5);
                    lw(t7, s0, 0);
                    s1 = addiu(s1, -1);
                    jalr(ctx, 0x51F6E8u, t7.u());
                    s0 = addiu(s0, -4);
                    if (i64(s1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0051f6f8
            charge(ctx, 3);
            lw(s2, s2, 0);
            if (s2 == 0) {
                break;
            }
            lw(s1, s2, 4);
            backedge(ctx);
        }
        // 0x0051f704
        charge(ctx, 1);
        t7 = 0x780000;
    }
    // 0x0051f708
    charge(ctx, 4);
    lw(a0, t7, 12080);
    lw(t7, a0, 60);
    if (t7 != 0) {
        // 0x0051f718
        charge(ctx, 2);
        jalr(ctx, 0x51F718u, t7.u());
    }
    // 0x0051f720
    charge(ctx, 2);
    a0 = s3;
    jal(ctx, 0x51F720u, gen::fn_sub_100218_00100218);
    gen::fn_fflush_0051f728(ctx);  // tail call
}

// 0x0051F728 fflush -- 268 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Flush a FILE (all FILEs through _fwalk for NULL): writes the buffered bytes through its write callback, sets the
// error flag on a failure.
void fflush(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051f728
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s1 = a0;
    if (a0 == 0) {
        // 0x0051f744
        charge(ctx, 10);
        t7 = 0x780000;
        ld(s0, sp, 0x0);
        lw(a0, t7, 12080);  // 0x782F30
        a1 = 0x520000;
        ld(s1, sp, 0x8);
        a1 = addiu(a1, -2264);  // &fflush
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn__fwalk_00520410(ctx);  // tail call
        return;
    }
    // 0x0051f770
    charge(ctx, 3);
    lw(a0, a0, 84);
    if (a0 != 0) {
        lw(t7, a0, 56);
    } else {
        // 0x0051f77c
        charge(ctx, 5);
        t7 = 0x780000;
        lw(t6, t7, 12080);  // 0x782F30
        sw(t6, s1, 84);
        a0 = t6;
        lw(t7, a0, 56);
    }
    // 0x0051f790
    charge(ctx, 2);
    if (t7 != 0) {
        lh(v0, s1, 12);
    } else {
        // 0x0051f798
        charge(ctx, 3);
        jal(ctx, 0x51F798u, gen::fn___sinit_0051fa20);
        lh(v0, s1, 12);
    }
    // 0x0051f7a4
    charge(ctx, 3);
    t7 = v0 & 0x8;
    if (t7 == 0) {
        v0 = 0;
    } else {
        // 0x0051f7b0
        charge(ctx, 3);
        lw(s2, s1, 16);
        t6 = v0 & 0x3;
        if (s2 != 0) {
            // 0x0051f7bc
            charge(ctx, 5);
            lw(t7, s1, 0);
            t5 = 0;
            sw(s2, s1, 0);
            s0 = subu(t7, s2);
            if (t6 == 0) {
                // 0x0051f7d0
                charge(ctx, 1);
                lw(t5, s1, 20);
            }
            // 0x0051f7d4
            charge(ctx, 2);
            sw(t5, s1, 8);
            if (i64(s0) <= 0) {
                goto L_0051f804;
            }
            // 0x0051f7dc
            charge(ctx, 1);
            lw(v0, s1, 36);
            for (;;) {
                // 0x0051f7e0
                charge(ctx, 7);
                a1 = s2;
                lw(a0, s1, 28);
                a2 = s0;
                jalr(ctx, 0x51F7E8u, v0.u());
                s0 = subu(s0, v0);
                s2 = addu(s2, v0);
                if (i64(v0) <= 0) {
                    goto L_0051f820;
                }
                // 0x0051f7fc
                charge(ctx, 2);
                if (i64(s0) <= 0) {
                    break;
                }
                lw(v0, s1, 36);
                backedge(ctx);
            }
            goto L_0051f804;
        }
    L_0051f804:
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0051f808 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    return;
L_0051f820:
    charge(ctx, 5);
    lhu(t7, s1, 12);
    v0 = si(-1);
    t7 = t7 | 0x40;
    sh(t7, s1, 12);
    backedge(ctx);
    // 0x0051f808 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0051F898 __sfmoreglue -- 112 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Allocate a glue block of N zeroed FILEs.
void __sfmoreglue(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051f898
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s0 = 88;
    sd(s1, sp, 0x8);
    mult(s0, a1, s0);
    sd(ra, sp, 0x18);
    s2 = a1;
    a1 = addiu(s0, 12);
    jal(ctx, 0x51F8B8u, gen::fn__malloc_r_005209c0);
    t7 = addiu(v0, 12);
    s1 = v0;
    a2 = s0;
    a0 = t7;
    a1 = 0;
    v0 = 0;
    if (s1 != 0) {
        // 0x0051f8dc
        charge(ctx, 5);
        sw(s2, s1, 4);
        sw(zero, s1, 0);
        link(ctx, 0x51F8E4u);  // $ra first: the delay slot below depends on it
        sw(t7, s1, 8);
        call(ctx, gen::fn_memset_00521408);
        v0 = s1;
    }
    // 0x0051f8f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0051F908 __sfp -- 216 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Find a free FILE (flags 0) in the glue chain, adding a block of 4 when all are used; initialises it.
void __sfp(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051f908
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    lw(t7, a0, 56);
    s1 = a0;
    if (t7 == 0) {
        // 0x0051f924
        charge(ctx, 2);
        jal(ctx, 0x51F924u, gen::fn___sinit_0051fa20);
    }
    // 0x0051f92c
    charge(ctx, 1);
    s0 = addiu(s1, 472);
    for (;;) {
        // 0x0051f930
        charge(ctx, 4);
        lw(t6, s0, 4);
        t6 = addiu(t6, -1);
        lw(t5, s0, 8);
        if (i64(t6) >= 0) {
            for (;;) {
                // 0x0051f940
                charge(ctx, 3);
                lh(t7, t5, 12);
                t6 = addiu(t6, -1);
                if (t7 == 0) {
                    goto L_0051f99c;
                }
                // 0x0051f94c
                charge(ctx, 2);
                t5 = addiu(t5, 88);
                if (i64(t6) < 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0051f954
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 != 0) {
            s0 = v0;
            backedge(ctx);
            continue;
        }
        // 0x0051f960
        charge(ctx, 5);
        a0 = s1;
        a1 = 4;
        jal(ctx, 0x51F964u, gen::fn___sfmoreglue_0051f898);
        sw(v0, s0, 0);
        if (v0 == 0) {
            break;
        }
        // 0x0051f974
        charge(ctx, 2);
        s0 = v0;
        backedge(ctx);
    }
    // 0x0051f97c
    charge(ctx, 3);
    t7 = 12;
    v0 = 0;
    sw(t7, s1, 0);
    // 0x0051f988 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    return;
L_0051f99c:
    charge(ctx, 17);
    t7 = 1;
    sw(s1, t5, 84);
    sh(t7, t5, 12);
    v0 = t5;
    sw(zero, t5, 0);
    t7 = si(-1);
    sw(zero, t5, 8);
    sh(t7, t5, 14);
    sw(zero, t5, 4);
    sw(zero, t5, 16);
    sw(zero, t5, 20);
    sw(zero, t5, 24);
    sw(zero, t5, 48);
    sw(zero, t5, 52);
    sw(zero, t5, 68);
    sw(zero, t5, 72);
    backedge(ctx);
    // 0x0051f988 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0051F9E0 _cleanup_r -- 28 bytes; frame 0x10: ra sp+0x0
// Flush every FILE of a reentrancy record.
void _cleanup_r(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051f9e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0x520000;
    sd(ra, sp, 0x0);
    a1 = addiu(a1, -2264);  // &fflush
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__fwalk_00520410(ctx);  // tail call
}

// 0x0051FA00 _cleanup -- 28 bytes; frame 0x10: ra sp+0x0
// Flush every FILE of the global reentrancy record.
void _cleanup(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051fa00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = 0x780000;
    sd(ra, sp, 0x0);
    lw(a0, t7, 12080);  // 0x782F30
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn__cleanup_r_0051f9e0(ctx);  // tail call
}

// 0x0051FA20 __sinit -- 128 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Initialise a reentrancy record's stdio: the cleanup hook, the three standard FILEs (std with flags 4 / 9 / 10).
void __sinit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051fa20
    enter(ctx, 32);  // entry check point + this block's cycles
    t7 = 0x520000;
    sw(zero, a0, 472);
    t7 = addiu(t7, -1568);  // &_cleanup_r
    sp = addiu(sp, -0x10);
    sw(t7, a0, 60);
    t6 = addiu(a0, 484);
    sd(s0, sp, 0x0);
    a3 = a0;
    t7 = 1;
    sd(ra, sp, 0x8);
    sw(t7, a0, 56);
    s0 = a0;
    sw(t6, a0, 480);
    a1 = 4;
    t7 = 3;
    a2 = 0;
    sw(t7, a0, 476);
    link(ctx, 0x51FA64u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 4);
    call(ctx, gen::fn_std_0051f838);
    lw(a0, s0, 8);
    a3 = s0;
    a1 = 9;
    a2 = 1;
    jal(ctx, 0x51FA78u, gen::fn_std_0051f838);
    lw(a0, s0, 12);
    a3 = s0;
    ld(ra, sp, 0x8);
    a1 = 10;
    ld(s0, sp, 0x0);
    a2 = 2;
    sp = addiu(sp, 0x10);
    gen::fn_std_0051f838(ctx);  // tail call
}

// 0x0051FAA0 fread -- 272 bytes; frame 0x40: s2 sp+0x10, s1 sp+0x8, s4 sp+0x20, s5 sp+0x28, s0 sp+0x0, s3 sp+0x18, s6 sp+0x30, ra sp+0x38
// Read N items: copy what the buffer holds, refill (__srefill) until done or EOF; returns whole items read.
void fread(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051faa0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0;
    sd(s2, sp, 0x10);
    sd(s1, sp, 0x8);
    mult(s2, a2, a1);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    s1 = a3;
    sd(s0, sp, 0x0);
    s4 = a1;
    sd(s3, sp, 0x18);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    s5 = a2;
    if (s2 != 0) {
        // 0x0051fadc
        charge(ctx, 3);
        lw(a2, a3, 4);
        s0 = a2;
        if (i64(a2) < 0) {
            // 0x0051fae8
            charge(ctx, 3);
            sw(zero, a3, 4);
            a2 = 0;
            s0 = a2;
        }
        // 0x0051faf4
        charge(ctx, 4);
        s3 = a0;
        t7 = sltu(a2, s2);
        s6 = s2;
        if (t7 != 0) {
            // 0x0051fb04
            charge(ctx, 1);
            lw(a1, s1, 0);
            for (;;) {
                // 0x0051fb08
                charge(ctx, 12);
                a0 = s3;
                a2 = s0;
                s2 = subu(s2, s0);
                jal(ctx, 0x51FB10u, gen::fn_memcpy_00521250);
                s3 = addu(s3, s0);
                lw(t7, s1, 0);
                a0 = s1;
                t7 = addu(t7, s0);
                link(ctx, 0x51FB28u);  // $ra first: the delay slot below depends on it
                sw(t7, s1, 0);
                call(ctx, gen::fn___srefill_00523580);
                t7 = subu(s6, s2);
                if (v0 != 0) {
                    goto L_0051fb9c;
                }
                // 0x0051fb38
                charge(ctx, 4);
                lw(s0, s1, 4);
                t7 = sltu(s0, s2);
                if (t7 == 0) {
                    break;
                }
                lw(a1, s1, 0);
                backedge(ctx);
            }
        }
        // 0x0051fb48
        charge(ctx, 11);
        lw(a1, s1, 0);
        a0 = s3;
        a2 = s2;
        jal(ctx, 0x51FB50u, gen::fn_memcpy_00521250);
        lw(t6, s1, 4);
        v0 = s5;
        lw(t7, s1, 0);
        t6 = subu(t6, s2);
        t7 = addu(t7, s2);
        sw(t6, s1, 4);
        sw(t7, s1, 0);
    }
    // 0x0051fb74 (the shared epilogue, written out on this path)
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
    return;
L_0051fb9c:
    charge(ctx, 3);
    divu(t7, s4);
    if (s4 == 0) {
        brk(ctx, 0x51FBA4u, 0x7u);
    }
    // 0x0051fba8
    charge(ctx, 2);
    mflo(v0);
    backedge(ctx);
    // 0x0051fb74 (the shared epilogue, written out on this path)
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

// 0x0051FBB0 _free_r -- 732 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// dlmalloc free: coalesce with free neighbours and the top chunk, bin the result, trim when the top grows past the
// threshold.
void _free_r(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051fbb0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a1;
    s1 = a0;
    if (a1 == 0) {
        // 0x0051fe78
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0051fbcc
    charge(ctx, 14);
    jal(ctx, 0x51FBCCu, gen::fn___malloc_lock_005214c8);
    a3 = addiu(s0, -8);
    t6 = si(-2);
    lw(t3, a3, 4);
    t7 = 0x780000;
    a2 = addiu(t7, 12096);  // &0x782F40
    t1 = t3 & t6;
    lw(t5, a2, 8);  // 0x782F48
    t4 = addu(a3, t1);
    t7 = si(-4);
    lw(t6, t4, 4);
    t0 = t6 & t7;
    if (t4 != t5) {
        // 0x0051fc78
        charge(ctx, 4);
        sw(t0, t4, 4);
        t7 = t3 & 0x1;
        t5 = 0;
        if (t7 == 0) {
            // 0x0051fc88
            charge(ctx, 6);
            lw(a1, s0, -8);
            t7 = addiu(a2, 8);
            a3 = subu(a3, a1);
            lw(t6, a3, 8);
            t1 = addu(t1, a1);
            if (t6 != t7) {
                // 0x0051fe68
                charge(ctx, 4);
                lw(t2, a3, 12);
                sw(t6, t2, 8);
                sw(t2, t6, 12);
                backedge(ctx);
            } else {
                // 0x0051fca0
                charge(ctx, 1);
                t5 = 1;
            }
        }
        // 0x0051fca4
        charge(ctx, 5);
        t6 = addu(t4, t0);
        lw(t7, t6, 4);
        t7 = t7 & 0x1;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = t1 | 0x1;
        if (!cc) {
            // 0x0051fcb8
            charge(ctx, 2);
            t1 = addu(t1, t0);
            if (t5 != 0) {
                // 0x0051fe60
                charge(ctx, 2);
                lw(t6, t4, 8);
                backedge(ctx);
                // 0x0051fe50
                charge(ctx, 1);
                lw(t2, t4, 12);
            L_0051fe54:
                charge(ctx, 3);
                sw(t6, t2, 8);
                sw(t2, t6, 12);
                backedge(ctx);
            } else {
                // 0x0051fcc0
                charge(ctx, 5);
                t7 = 0x780000;
                lw(t6, t4, 8);
                t7 = addiu(t7, 12104);  // "@/x"
                if (t6 != t7) {
                    lw(t2, t4, 12);
                    goto L_0051fe54;
                }
                // 0x0051fcd4
                charge(ctx, 5);
                sw(a3, t6, 12);
                t5 = 1;
                sw(a3, t6, 8);
                sw(t6, a3, 12);
                sw(t6, a3, 8);
            }
            // 0x0051fce8
            charge(ctx, 1);
            t7 = t1 | 0x1;
        }
        // 0x0051fcec
        charge(ctx, 4);
        t6 = addu(a3, t1);
        sw(t7, a3, 4);
        sw(t1, t6, 0);
        if (t5 != 0) {
            backedge(ctx);
        } else {
            // 0x0051fcfc
            charge(ctx, 3);
            t7 = sltiu(t1, 512);
            t4 = srl(t1, 3);
            if (t7 == 0) {
                // 0x0051fd50
                charge(ctx, 3);
                t6 = srl(t1, 9);
                t7 = sltiu(t6, 5);
                if (t6 != 0) {
                    // 0x0051fd5c
                    charge(ctx, 2);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = srl(t1, 6);
                    if (cc) {
                        // 0x0051fdfc
                        charge(ctx, 3);
                        t7 = sltiu(t6, 21);
                        t4 = addiu(t6, 91);
                        if (t7 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x0051fe08
                            charge(ctx, 3);
                            t7 = sltiu(t6, 85);
                            cc = t7 == 0;  // the condition, before the delay slot changes it
                            t7 = srl(t1, 12);
                            if (cc) {
                                // 0x0051fe1c
                                charge(ctx, 3);
                                t7 = sltiu(t6, 341);
                                cc = t7 == 0;  // the condition, before the delay slot changes it
                                t7 = srl(t1, 15);
                                if (cc) {
                                    // 0x0051fe30
                                    charge(ctx, 3);
                                    t7 = sltiu(t6, 1365);
                                    cc = t7 == 0;  // the condition, before the delay slot changes it
                                    t7 = srl(t1, 18);
                                    if (cc) {
                                        // 0x0051fe44
                                        charge(ctx, 2);
                                        t4 = 126;
                                        backedge(ctx);
                                    } else {
                                        // 0x0051fe3c
                                        charge(ctx, 2);
                                        t4 = addiu(t7, 124);
                                        backedge(ctx);
                                    }
                                } else {
                                    // 0x0051fe28
                                    charge(ctx, 2);
                                    t4 = addiu(t7, 119);
                                    backedge(ctx);
                                }
                            } else {
                                // 0x0051fe14
                                charge(ctx, 2);
                                t4 = addiu(t7, 110);
                                backedge(ctx);
                            }
                        }
                    } else {
                        // 0x0051fd64
                        charge(ctx, 1);
                        t4 = addiu(t7, 56);
                    }
                }
                // 0x0051fd68
                charge(ctx, 7);
                t7 = 0x780000;
                t6 = sll(t4, 3);
                t0 = addiu(t7, 12096);  // &0x782F40
                t2 = addu(t6, t0);
                lw(t3, t2, 8);
                if (t3 != t2) {
                    lw(t7, t3, 4);
                    // 0x0051fdc0
                    charge(ctx, 5);
                    t6 = si(-4);
                    t7 = t7 & t6;
                    t7 = sltu(t1, t7);
                    if (t7 == 0) {
                        lw(t2, t3, 12);
                        backedge(ctx);
                    } else {
                        // 0x0051fdd4
                        charge(ctx, 1);
                        lw(t3, t3, 8);
                        for (;;) {
                            // 0x0051fdd8
                            charge(ctx, 2);
                            if (t3 != t2) {
                                // 0x0051fde0
                                charge(ctx, 5);
                                lw(t7, t3, 4);
                                t7 = t7 & t6;
                                t7 = sltu(t1, t7);
                                if (t7 == 0) {
                                    goto L_0051fdf4_29;
                                }
                                lw(t3, t3, 8);
                                backedge(ctx);
                                continue;
                            }
                            lw(t2, t3, 12);
                            backedge(ctx);
                            break;
                        }
                    }
                } else {
                    // 0x0051fd84
                    charge(ctx, 11);
                    t6 = addiu(t4, 3);
                    t7 = slti(t4, 0);
                    if (t7 != 0) t4 = t6;
                    t5 = sra(t4, 2);
                    lw(t6, t0, 4);
                    t7 = 1;
                    t7 = dsllv(t7, t5);
                    t7 = dsll32(t7, 0);
                    t7 = dsra32(t7, 0);
                    t6 = t6 | t7;
                    sw(t6, t0, 4);
                }
            L_0051fdb0:
                charge(ctx, 4);
                sw(t2, a3, 12);
                sw(t3, a3, 8);
                sw(a3, t3, 12);
                backedge(ctx);
            } else {
                // 0x0051fd08
                charge(ctx, 16);
                t5 = 0x780000;
                t5 = addiu(t5, 12096);  // &0x782F40
                t7 = sll(t4, 3);
                t2 = addu(t7, t5);
                lw(t6, t5, 4);  // 0x782F44
                t4 = srl(t4, 2);
                lw(t3, t2, 8);
                t7 = 1;
                sw(t2, a3, 12);
                t7 = dsllv(t7, t4);
                sw(t3, a3, 8);
                t7 = dsll32(t7, 0);
                sw(a3, t3, 12);
                t7 = dsra32(t7, 0);
                t6 = t6 | t7;
                sw(t6, t5, 4);  // 0x782F44
            }
            // 0x0051fd48
            charge(ctx, 2);
            sw(a3, t2, 8);
            backedge(ctx);
        }
    } else {
        // 0x0051fc04
        charge(ctx, 3);
        t7 = t3 & 0x1;
        t1 = addu(t1, t0);
        if (t7 == 0) {
            // 0x0051fc10
            charge(ctx, 7);
            lw(a1, s0, -8);
            a3 = subu(a3, a1);
            t1 = addu(t1, a1);
            lw(t2, a3, 12);
            lw(t3, a3, 8);
            sw(t3, t2, 8);
            sw(t2, t3, 12);
        }
        // 0x0051fc2c
        charge(ctx, 9);
        t7 = 0x780000;
        sw(a3, a2, 8);
        t6 = dsll32(t1, 0);
        ld(t4, t7, 13128);  // 0x783348
        t5 = t1 | 0x1;
        t6 = dsrl32(t6, 0);
        t6 = sltu(t6, t4);
        sw(t5, a3, 4);
        if (t6 == 0) {
            // 0x0051fc50
            charge(ctx, 4);
            t7 = 0x780000;
            a0 = s1;
            link(ctx, 0x51FC58u);  // $ra first: the delay slot below depends on it
            lw(a1, t7, 13136);
            call(ctx, gen::fn__malloc_trim_r_0051fe90);
        }
    }
    // 0x0051fc60
    charge(ctx, 6);
    a0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn___malloc_unlock_00521520(ctx);  // tail call
    return;
L_0051fdf4_29:
    charge(ctx, 2);
    lw(t2, t3, 12);
    backedge(ctx);
    goto L_0051fdb0;
}

// 0x0051FE90 _malloc_trim_r -- 348 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// dlmalloc trim: give whole pages above the top chunk back with sbrk.
void _malloc_trim_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051fe90
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s1, sp, 0x8);
    s0 = a1;
    sd(s3, sp, 0x18);
    s2 = a0;
    sd(s4, sp, 0x20);
    s0 = dsll32(s0, 0);
    sd(ra, sp, 0x28);
    s0 = dsrl32(s0, 0);
    jal(ctx, 0x51FEB8u, gen::fn___malloc_lock_005214c8);
    t7 = 0x780000;
    t6 = si(-4);
    s3 = addiu(t7, 12096);  // &0x782F40
    a0 = s2;
    lw(t5, s3, 8);  // 0x782F48
    lw(t7, t5, 4);
    t7 = t7 & t6;
    s1 = dsll32(t7, 0);
    s1 = dsrl32(s1, 0);
    s0 = s1 - s0;
    s0 = daddiu(s0, 4079);
    s0 = dsrl(s0, 12);
    s0 = daddiu(s0, -1);
    s0 = dsll(s0, 12);
    t7 = slti(s0, 4096);
    a1 = 0;
    if (t7 == 0) {
        // 0x0051ff04
        charge(ctx, 8);
        jal(ctx, 0x51FF04u, gen::fn__sbrk_r_00523930);
        lw(t7, s3, 8);
        t6 = dsll32(s1, 0);
        t6 = dsra32(t6, 0);
        t7 = addu(t7, t6);
        a0 = s2;
        if (v0 != t7) {
            goto L_0051ff9c;
        }
        // 0x0051ff24
        charge(ctx, 14);
        s4 = dsll32(s0, 0);
        a0 = s2;
        s4 = dsra32(s4, 0);
        a1 = subu(0, s4);
        jal(ctx, 0x51FF30u, gen::fn__sbrk_r_00523930);
        t7 = s1 - s0;
        t5 = 0x780000;
        t7 = t7 | 0x1;
        a0 = s2;
        t7 = dsll32(t7, 0);
        a1 = 0;
        t6 = si(-1);
        t7 = dsra32(t7, 0);
        if (v0 == t6) {
            // 0x0051ff5c
            charge(ctx, 10);
            jal(ctx, 0x51FF5Cu, gen::fn__sbrk_r_00523930);
            lw(t5, s3, 8);
            a0 = s2;
            s1 = subu(v0, t5);
            t7 = s1 | 0x1;
            t6 = slti(s1, 16);
            t4 = dsll32(t7, 0);
            t4 = dsra32(t4, 0);
            if (t6 == 0) {
                // 0x0051ff84
                charge(ctx, 6);
                t7 = 0x780000;
                lw(t6, t7, 13144);  // 0x783358
                t7 = 0x780000;
                t6 = subu(v0, t6);
                sw(t6, t7, 13168);  // 0x783370
                sw(t4, t5, 4);
            }
            goto L_0051ff9c;
        }
        // 0x0051ffc8
        charge(ctx, 9);
        lw(t6, s3, 8);
        a0 = s2;
        sw(t7, t6, 4);
        lw(t7, t5, 13168);
        t7 = subu(t7, s4);
        link(ctx, 0x51FFDCu);  // $ra first: the delay slot below depends on it
        sw(t7, t5, 13168);
        call(ctx, gen::fn___malloc_unlock_00521520);
        v0 = 1;
        backedge(ctx);
        // 0x0051ffa8 (the shared epilogue, written out on this path)
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
L_0051ff9c:
    charge(ctx, 3);
    jal(ctx, 0x51FF9Cu, gen::fn___malloc_unlock_00521520);
    v0 = 0;
    // 0x0051ffa8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0051FFF0 _kill_r -- 84 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The reentrant wrapper around fstat (sic: this build's _kill_r calls fstat), errno handled like _close_r.
void _kill_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051fff0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s0 = 0x9B0000;
    sd(ra, sp, 0x10);
    s1 = a0;
    sw(zero, s0, -13280);  // 0x9ACC20
    a0 = a1;
    a1 = a2;
    jal(ctx, 0x520010u, gen::fn_fstat_00503918);
    t7 = si(-1);
    if (v0 != t7) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00520024
        charge(ctx, 3);
        lw(t7, s0, -13280);
        if (t7 != 0) {
            sw(t7, s1, 0);
        }
        // 0x00520030
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00520034 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
