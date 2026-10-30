// Slice libs3: newlib's stdio core -- buffering setup, the low-level read / seek / close callbacks, the string FILE
// behind sscanf / sprintf, ungetc, vfscanf's converter, the floating-point conversion cvt. _fwalk, __srefill and
// __swrite stay recompiled: tests/game/test_libs1_newlib.cpp stands them in.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn___sbprintf_00526188(p3fes::EEContext&);
void fn___sccl_005287d8(p3fes::EEContext&);
void fn___sclose_00523da8(p3fes::EEContext&);
void fn___sinit_0051fa20(p3fes::EEContext&);
void fn___sprint_00526140(p3fes::EEContext&);
void fn___sread_00523c60(p3fes::EEContext&);
void fn___srefill_00523580(p3fes::EEContext&);
void fn___sseek_00523d40(p3fes::EEContext&);
void fn___submore_00525ec8(p3fes::EEContext&);
void fn___svfscanf_00527b00(p3fes::EEContext&);
void fn___svfscanf_r_00527b48(p3fes::EEContext&);
void fn___swsetup_005289d0(p3fes::EEContext&);
void fn__close_r_0051e230(p3fes::EEContext&);
void fn__dtoa_r_0051e4b0(p3fes::EEContext&);
void fn__execve_r_00520580(p3fes::EEContext&);
void fn__fork_r_005205d8(p3fes::EEContext&);
void fn__free_r_0051fbb0(p3fes::EEContext&);
void fn__fwalk_00520410(p3fes::EEContext&);
void fn__getpid_r_00520048(p3fes::EEContext&);
void fn__kill_r_0051fff0(p3fes::EEContext&);
void fn__malloc_r_005209c0(p3fes::EEContext&);
void fn__printf_r_00522568(p3fes::EEContext&);
void fn__read_r_00522f38(p3fes::EEContext&);
void fn__realloc_r_00522fc0(p3fes::EEContext&);
void fn__sprintf_r_00523a58(p3fes::EEContext&);
void fn__sscanf_r_00523bc8(p3fes::EEContext&);
void fn__strtod_r_00524aa8(p3fes::EEContext&);
void fn__strtol_r_00525a10(p3fes::EEContext&);
void fn__vfscanf_r_00527b30(p3fes::EEContext&);
void fn__vsprintf_r_00528920(p3fes::EEContext&);
void fn__write_r_00528970(p3fes::EEContext&);
void fn_cvt_00527810(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_fflush_0051f728(p3fes::EEContext&);
void fn_fread_0051faa0(p3fes::EEContext&);
void fn_isatty_00503910(p3fes::EEContext&);
void fn_lflush_00523550(p3fes::EEContext&);
void fn_lseek_00503858(p3fes::EEContext&);
void fn_memchr_005210d8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memmove_00521300(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sscanf_00523b40(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_ungetc_00525fb0(p3fes::EEContext&);
void fn_vfprintf_00526238(p3fes::EEContext&);
void fn_vfprintf_00526238_at_005262b0(p3fes::EEContext&);
void fn_vfscanf_00527a88(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00520048 _getpid_r -- 964 bytes; frame 0x50: s3 sp+0x18, s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// [__sfvwrite] The FLIRT name is a false match of a short code shape; the role is read from the instructions. newlib's
// vectored write into a FILE (the routine __sprint hands vfprintf's collected output to; it gathers an iovec list
// {base, len} of total length uio[+8]): makes the FILE writable (__swsetup), then for an unbuffered FILE (flags & 2)
// writes each piece straight through the write callback (+36) in chunks of at most 1,024 bytes; for a string FILE
// (flags & 0x200) copies into the buffer (memmove), never past its room; for a line-buffered FILE (flags & 1) looks for
// the newline (memchr) and flushes after it; otherwise fills the buffer and flushes (fflush) when it is full. Returns
// 0, or -1 with the error flag (0x40) set when a write fails.
void _getpid_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00520048
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t6 = 0;
    sd(s3, sp, 0x18);
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    s3 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    lw(s2, a1, 8);
    s5 = a1;
    if (s2 != 0) {
        // 0x00520084
        charge(ctx, 4);
        lhu(t6, a0, libc::file::kFlags);
        t7 = t6 & 0x8;
        if (t7 != 0) {
            // 0x00520094
            charge(ctx, 3);
            lw(t7, a0, libc::file::kBufBase);
            if (t7 == 0) {
                goto L_005200a0;
            }
            lw(s1, s5, 0);
        L_005200b8:
            charge(ctx, 3);
            t7 = t6 & 0x2;
            s2 = 0;
            if (t7 != 0) {
                // 0x005200c4
                charge(ctx, 1);
                s6 = 1024;
                for (;;) {
                    // 0x005200c8
                    charge(ctx, 2);
                    t7 = sltiu(s2, 1025);
                    if (s2 == 0) {
                        for (;;) {
                            // 0x005200d0
                            charge(ctx, 7);
                            lw(s4, s1, 0);
                            lw(a2, s1, 4);
                            s1 = addiu(s1, 8);
                            if (a2 != 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x005200ec
                        charge(ctx, 2);
                        s2 = a2;
                        t7 = sltiu(s2, 1025);
                    }
                    // 0x005200f4
                    charge(ctx, 8);
                    lw(v0, s3, libc::file::kWrite);
                    a2 = s6;
                    lw(a0, s3, libc::file::kCookie);
                    if (t7 != 0) a2 = s2;
                    a1 = s4;
                    jalr(ctx, 0x520104u, v0.u());
                    s4 = addu(s4, v0);
                    if (i64(v0) <= 0) {
                        goto L_0052015c;
                    }
                    // 0x00520114
                    charge(ctx, 5);
                    lw(t7, s5, 8);
                    s2 = subu(s2, v0);
                    t7 = subu(t7, v0);
                    sw(t7, s5, 8);
                    if (t7 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                goto L_00520128;
            }
            // 0x00520170
            charge(ctx, 5);
            t7 = t6 & 0x1;
            t7 = sll(t7, 16);
            t7 = sra(t7, 16);
            s7 = 0;
            if (t7 != 0) {
                for (;;) {
                    // 0x005202bc
                    charge(ctx, 2);
                    if (s2 == 0) {
                        // 0x005202c4
                        charge(ctx, 1);
                        s7 = 0;
                        for (;;) {
                            // 0x005202c8
                            charge(ctx, 7);
                            lw(s4, s1, 0);
                            lw(a2, s1, 4);
                            s1 = addiu(s1, 8);
                            if (a2 != 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x005202e4
                        charge(ctx, 1);
                        s2 = a2;
                    }
                    // 0x005202e8
                    charge(ctx, 2);
                    t7 = sltu(s2, s6);
                    if (s7 == 0) {
                        // 0x005202f0
                        charge(ctx, 6);
                        a0 = s4;
                        a1 = 10;
                        a2 = s2;
                        jal(ctx, 0x5202F8u, gen::fn_memchr_005210d8);
                        t7 = subu(v0, s4);
                        if (v0 == 0) {
                            // 0x00520404
                            charge(ctx, 2);
                            s6 = addiu(s2, 1);
                            backedge(ctx);
                        } else {
                            // 0x00520308
                            charge(ctx, 1);
                            s6 = addiu(t7, 1);
                        }
                        // 0x0052030c
                        charge(ctx, 2);
                        s7 = 1;
                        t7 = sltu(s2, s6);
                    }
                    // 0x00520314
                    charge(ctx, 9);
                    lw(t6, s3, libc::file::kW);
                    t5 = s2;
                    lw(t4, s3, libc::file::kBufSize);
                    if (t7 == 0) t5 = s6;
                    lw(a0, s3, libc::file::kP);
                    lw(t7, s3, libc::file::kBufBase);
                    t7 = sltu(t7, a0);
                    s0 = addu(t6, t4);
                    if (t7 != 0) {
                        // 0x00520338
                        charge(ctx, 3);
                        t7 = slt(s0, t5);
                        a1 = s4;
                        if (t7 == 0) {
                            goto L_005203a8;
                        }
                        // 0x00520344
                        charge(ctx, 9);
                        a2 = s0;
                        jal(ctx, 0x520344u, gen::fn_memmove_00521300);
                        lw(t7, s3, libc::file::kP);
                        a0 = s3;
                        t7 = addu(t7, s0);
                        link(ctx, 0x520358u);  // $ra first: the delay slot below depends on it
                        sw(t7, s3, libc::file::kP);
                        call(ctx, gen::fn_fflush_0051f728);
                        if (v0 != 0) {
                            lhu(t7, s3, libc::file::kFlags);
                            backedge(ctx);
                            goto L_00520160;
                        }
                    L_00520368:
                        charge(ctx, 3);
                        s6 = subu(s6, s0);
                        if (s6 != 0) {
                            lw(t7, s5, 8);
                        } else {
                            // 0x00520374
                            charge(ctx, 4);
                            a0 = s3;
                            jal(ctx, 0x520374u, gen::fn_fflush_0051f728);
                            s7 = 0;
                            if (v0 != 0) {
                                backedge(ctx);
                                break;
                            }
                            // 0x00520384
                            charge(ctx, 1);
                            lw(t7, s5, 8);
                            goto L_00520388;
                        }
                    L_00520388:
                        charge(ctx, 5);
                        s4 = addu(s4, s0);
                        s2 = subu(s2, s0);
                        t7 = subu(t7, s0);
                        sw(t7, s5, 8);
                        if (t7 == 0) {
                            goto L_0052039c_48;
                        }
                        backedge(ctx);
                        continue;
                    }
                L_005203a8:
                    charge(ctx, 3);
                    t7 = slt(t5, t4);
                    if (t7 == 0) {
                        // 0x005203b4
                        charge(ctx, 7);
                        lw(v0, s3, libc::file::kWrite);
                        a2 = t4;
                        lw(a0, s3, libc::file::kCookie);
                        a1 = s4;
                        jalr(ctx, 0x5203C0u, v0.u());
                        s0 = v0;
                        if (i64(v0) <= 0) {
                            goto L_005203d0_51;
                        }
                        backedge(ctx);
                        goto L_00520368;
                    }
                    lw(a0, s3, libc::file::kP);
                    // 0x005203d8
                    charge(ctx, 11);
                    s0 = t5;
                    a1 = s4;
                    a2 = t5;
                    jal(ctx, 0x5203E0u, gen::fn_memmove_00521300);
                    lw(t7, s3, libc::file::kW);
                    lw(t6, s3, libc::file::kP);
                    t7 = subu(t7, s0);
                    t6 = addu(t6, s0);
                    sw(t7, s3, libc::file::kW);
                    sw(t6, s3, libc::file::kP);
                    backedge(ctx);
                    goto L_00520368;
                }
            L_0052015c:
                charge(ctx, 1);
                lhu(t7, s3, libc::file::kFlags);
            L_00520160:
                charge(ctx, 4);
                t6 = si(-1);
                t7 = t7 | 0x40;
                sh(t7, s3, libc::file::kFlags);
                backedge(ctx);
            } else {
                for (;;) {
                    // 0x00520184
                    charge(ctx, 2);
                    t7 = t6 & 0x200;
                    if (s2 == 0) {
                        for (;;) {
                            // 0x0052018c
                            charge(ctx, 7);
                            lw(s4, s1, 0);
                            lw(a2, s1, 4);
                            s1 = addiu(s1, 8);
                            if (a2 != 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x005201a8
                        charge(ctx, 2);
                        s2 = a2;
                        t7 = t6 & 0x200;
                    }
                    // 0x005201b0
                    charge(ctx, 2);
                    lw(s0, s3, libc::file::kW);
                    if (t7 != 0) {
                        // 0x005201b8
                        charge(ctx, 13);
                        t7 = sltu(s2, s0);
                        lw(a0, s3, libc::file::kP);
                        if (t7 != 0) s0 = s2;
                        a1 = s4;
                        a2 = s0;
                        jal(ctx, 0x5201C8u, gen::fn_memmove_00521300);
                        lw(t7, s3, libc::file::kW);
                        lw(t6, s3, libc::file::kP);
                        t7 = subu(t7, s0);
                        t6 = addu(t6, s0);
                        sw(t7, s3, libc::file::kW);
                        sw(t6, s3, libc::file::kP);
                        s0 = s2;
                        goto L_005201ec;
                    }
                    // 0x0052020c
                    charge(ctx, 5);
                    lw(a0, s3, libc::file::kP);
                    lw(t7, s3, libc::file::kBufBase);
                    t7 = sltu(t7, a0);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = sltu(s0, s2);
                    if (!cc) {
                        // 0x00520220
                        charge(ctx, 2);
                        a1 = s4;
                        if (t7 == 0) {
                            goto L_00520258;
                        }
                        // 0x00520228
                        charge(ctx, 9);
                        a2 = s0;
                        jal(ctx, 0x520228u, gen::fn_memmove_00521300);
                        lw(t7, s3, libc::file::kP);
                        a0 = s3;
                        t7 = addu(t7, s0);
                        link(ctx, 0x52023Cu);  // $ra first: the delay slot below depends on it
                        sw(t7, s3, libc::file::kP);
                        call(ctx, gen::fn_fflush_0051f728);
                        if (v0 != 0) {
                            goto L_0052024c_28;
                        }
                        lw(t7, s5, 8);
                        backedge(ctx);
                    L_005201f0:
                        charge(ctx, 5);
                        s4 = addu(s4, s0);
                        s2 = subu(s2, s0);
                        t7 = subu(t7, s0);
                        sw(t7, s5, 8);
                        if (t7 == 0) {
                            backedge(ctx);
                            break;
                        }
                        // 0x00520204
                        charge(ctx, 2);
                        lhu(t6, s3, libc::file::kFlags);
                        backedge(ctx);
                        continue;
                    }
                L_00520258:
                    charge(ctx, 4);
                    lw(s0, s3, libc::file::kBufSize);
                    t7 = sltu(s2, s0);
                    if (t7 == 0) {
                        // 0x00520268
                        charge(ctx, 7);
                        lw(v0, s3, libc::file::kWrite);
                        a2 = s0;
                        lw(a0, s3, libc::file::kCookie);
                        a1 = s4;
                        jalr(ctx, 0x520274u, v0.u());
                        s0 = v0;
                        if (i64(v0) <= 0) {
                            goto L_00520284_31;
                        }
                        backedge(ctx);
                        goto L_005201ec;
                    }
                    lw(a0, s3, libc::file::kP);
                    // 0x00520290
                    charge(ctx, 11);
                    a1 = s4;
                    a2 = s2;
                    s0 = s2;
                    jal(ctx, 0x520298u, gen::fn_memmove_00521300);
                    lw(t7, s3, libc::file::kW);
                    lw(t6, s3, libc::file::kP);
                    t7 = subu(t7, s2);
                    t6 = addu(t6, s2);
                    sw(t7, s3, libc::file::kW);
                    sw(t6, s3, libc::file::kP);
                    backedge(ctx);
                L_005201ec:
                    charge(ctx, 1);
                    lw(t7, s5, 8);
                    goto L_005201f0;
                }
            L_00520128:
                charge(ctx, 1);
                t6 = 0;
            }
            // 0x0052012c (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(s0, sp, 0x0);
            v0 = t6;
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(s5, sp, 0x28);
            ld(s6, sp, 0x30);
            ld(s7, sp, 0x38);
            ld(ra, sp, 0x40);
            sp = addiu(sp, 0x50);
            return;
        }
    L_005200a0:
        charge(ctx, 4);
        jal(ctx, 0x5200A0u, gen::fn___swsetup_005289d0);
        t6 = si(-1);
        if (v0 == 0) {
            // 0x005200b0
            charge(ctx, 2);
            lhu(t6, s3, libc::file::kFlags);
            lw(s1, s5, 0);
            goto L_005200b8;
        }
    }
    // 0x0052012c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    v0 = t6;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_0052024c_28:
    charge(ctx, 2);
    lhu(t7, s3, libc::file::kFlags);
    backedge(ctx);
    goto L_00520160;
L_00520284_31:
    charge(ctx, 2);
    lhu(t7, s3, libc::file::kFlags);
    backedge(ctx);
    goto L_00520160;
L_0052039c_48:
    charge(ctx, 2);
    t6 = 0;
    backedge(ctx);
    // 0x0052012c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    v0 = t6;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_005203d0_51:
    charge(ctx, 2);
    lhu(t7, s3, libc::file::kFlags);
    backedge(ctx);
    goto L_00520160;
}

// 0x00520580 _execve_r -- 88 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [_lseek_r] The FLIRT name is a false match of a short code shape; the role is read from the instructions. newlib's
// _lseek_r(reent, fd, offset, whence): clears the system errno word 0x9ACC20, calls lseek (0x503858, a stub that
// returns -1 in this build) and, when it returns -1 with a non-zero errno word, copies that word into reent->errno.
// Returns lseek's result.
void _execve_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00520580
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x10);
    a0 = a1;
    s0 = 0x9B0000;
    a1 = a2;
    sw(zero, s0, -13280);  // 0x9ACC20 = libs3::kSysErrno: cleared before the call
    a2 = a3;
    jal(ctx, 0x5205A4u, gen::fn_lseek_00503858);
    t7 = si(-1);
    if (v0 != t7) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005205b8
        charge(ctx, 3);
        lw(t7, s0, -13280);  // libs3::kSysErrno
        if (t7 != 0) {
            sw(t7, s1, libc::reent::kErrno);
        }
        // 0x005205c4
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x005205c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005205D8 _fork_r -- 332 bytes; frame 0x90: s0 sp+0x70, s1 sp+0x78, s2 sp+0x80, ra sp+0x88
// [__smakebuf] The FLIRT name is a false match of a short code shape; the role is read from the instructions. newlib's
// buffer setup of a FILE (__smakebuf): an unbuffered FILE (flags & 2) gets its one-byte buffer +67; otherwise it asks
// _kill_r (0x51FFF0, this build's fstat) for the file's mode on a stack stat record and picks the block size (1,024,
// and the FILE is seekable when its seek callback is __sseek and the mode is a regular file), allocates the buffer with
// _malloc_r (falling back to the one-byte buffer when that fails), registers _cleanup_r in the _reent (+60) and marks a
// terminal (isatty) line-buffered (flags | 1). Flags 0x80: buffer from malloc; 0x400: a regular file with the standard
// seek callback; 0x800: anything else.
void _fork_r(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005205d8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s0, sp, 0x70);
    sd(s1, sp, 0x78);
    sd(s2, sp, 0x80);
    sd(ra, sp, 0x88);
    lhu(t6, a0, 12);
    t7 = t6 & 0x2;
    s0 = a0;
    if (t7 != 0) {
        // 0x005205fc
        charge(ctx, 5);
        t6 = addiu(a0, 67);
        t7 = 1;
        sw(t7, a0, 20);
        sw(t6, a0, 16);
        sw(t6, a0, 0);
        goto L_00520610;
    }
    // 0x00520628
    charge(ctx, 3);
    lh(a1, a0, 14);
    t7 = t6 | 0x800;
    if (i64(a1) >= 0) {
        // 0x00520634
        charge(ctx, 5);
        lw(a0, a0, 84);
        a2 = sp;
        jal(ctx, 0x520638u, gen::fn__kill_r_0051fff0);
        lw(t7, sp, 0x4);
        if (i64(v0) < 0) {
            // 0x00520648
            charge(ctx, 2);
            lhu(t6, s0, libc::file::kFlags);
            t7 = t6 | 0x800;
            goto L_00520650;
        }
        // 0x005206d8
        charge(ctx, 6);
        s1 = 1024;
        t5 = 0x8000;
        t7 = t7 & 0xF000;
        t6 = t7 ^ 0x2000;
        s2 = sltiu(t6, 1);
        if (t7 != t5) {
            // 0x00520718
            charge(ctx, 1);
            lhu(t7, s0, libc::file::kFlags);
        L_0052071c:
            charge(ctx, 2);
            t7 = t7 | 0x800;
            backedge(ctx);
        } else {
            // 0x005206f0
            charge(ctx, 5);
            t7 = 0x520000;
            lw(t6, s0, libc::file::kSeek);
            t7 = addiu(t7, 15680);  // &__sseek
            cc = t6 != t7;  // the condition, before the delay slot changes it
            lhu(t7, s0, libc::file::kFlags);
            if (cc) {
                goto L_0052071c;
            }
            // 0x00520704
            charge(ctx, 3);
            sw(s1, s0, libs3::file::kBlkSize);
            t7 = t7 | 0x400;
        }
        // 0x00520710
        charge(ctx, 2);
        sh(t7, s0, libc::file::kFlags);
        backedge(ctx);
        goto L_0052065c;
    }
L_00520650:
    charge(ctx, 3);
    s2 = 0;
    sh(t7, s0, libc::file::kFlags);
    s1 = 1024;
L_0052065c:
    charge(ctx, 5);
    lw(a0, s0, libc::file::kData);
    a1 = 1024;
    jal(ctx, 0x520660u, gen::fn__malloc_r_005209c0);
    lhu(t7, s0, libc::file::kFlags);
    if (v0 == 0) {
        // 0x00520670
        charge(ctx, 8);
        t5 = addiu(s0, 67);
        t6 = 1;
        sw(t5, s0, libc::file::kBufBase);
        t7 = t7 | 0x2;
        sw(t6, s0, libc::file::kBufSize);
        sh(t7, s0, libc::file::kFlags);
        sw(t5, s0, 0);
        backedge(ctx);
        goto L_00520610;
    }
    // 0x00520690
    charge(ctx, 10);
    t6 = 0x520000;
    lw(t5, s0, libc::file::kData);
    t6 = addiu(t6, -1568);  // &_cleanup_r
    t7 = t7 | 0x80;
    sw(v0, s0, libc::file::kBufBase);
    sw(t6, t5, 60);
    sh(t7, s0, libc::file::kFlags);
    sw(s1, s0, libc::file::kBufSize);
    sw(v0, s0, 0);
    if (s2 == 0) {
        backedge(ctx);
    L_00520610:
        charge(ctx, 1);
        ld(s0, sp, 0x70);
    } else {
        // 0x005206b8
        charge(ctx, 4);
        link(ctx, 0x5206B8u);  // $ra first: the delay slot below depends on it
        lh(a0, s0, libc::file::kFile);
        call(ctx, gen::fn_isatty_00503910);
        if (v0 != 0) {
            // 0x005206c8
            charge(ctx, 4);
            lhu(t7, s0, libc::file::kFlags);
            t7 = t7 | 0x1;
            sh(t7, s0, libc::file::kFlags);
            backedge(ctx);
            goto L_00520610;
        }
        ld(s0, sp, 0x70);
        backedge(ctx);
    }
    // 0x00520614 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x78);
    ld(s2, sp, 0x80);
    ld(ra, sp, 0x88);
    sp = addiu(sp, 0x90);
}

// 0x00522568 _printf_r -- 60 bytes; frame 0x40: ra sp+0x0
// printf_r(reent, fmt, ...): spills $a2..$t3 as the variadic save area, then vfprintf(reent->stdout (+8), fmt, ap) --
// entering vfprintf's body past its own reent setup (loc_5262B0, the mid-body entry that keeps vfprintf itself
// recompiled).
void _printf_r(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00522568
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(a2, sp, 0x10);
    sd(ra, sp, 0x0);
    sd(a3, sp, 0x18);
    a2 = a1;
    sd(t0, sp, 0x20);
    sd(t1, sp, 0x28);
    a3 = addiu(sp, 0x10);
    sd(t2, sp, 0x30);
    sd(t3, sp, 0x38);
    link(ctx, 0x522590u);
    lw(a1, a0, libs3::reent::kStdout);
    gen::fn_vfprintf_00526238_at_005262b0(ctx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00523550 lflush -- 48 bytes; frame 0x10: ra sp+0x0
// The _fwalk callback that flushes line-buffered output streams: fflush(fp) (a tail call) when both flags 1 (line
// buffered) and 8 (writing) are set, else 0.
void lflush(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523550
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = 9;  // line buffered | writing
    sd(ra, sp, 0x0);
    lhu(t6, a0, libc::file::kFlags);
    t6 = t6 & 0x9;
    ld(ra, sp, 0x0);
    if (t6 != t7) {
        // 0x00523574
        charge(ctx, 3);
        v0 = 0;
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0052356c
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_fflush_0051f728(ctx);  // tail call
}

// 0x00523A58 _sprintf_r -- 108 bytes; frame 0xA0: ra sp+0x60
// sprintf_r(reent, buf, fmt, ...): a string FILE on the stack (flags 0x208 = writing | string, buffer = buf, room
// 0x7FFFFFFF, _data = reent), vfprintf, then the terminating NUL at the final write position. Returns the character
// count.
void _sprintf_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523a58
    enter(ctx, 27);  // entry check point + this block's cycles
    t6 = 0x7FFF0000;
    sp = addiu(sp, -0xA0);
    t5 = a1;
    sd(ra, sp, 0x60);
    t4 = a0;
    sd(a3, sp, 0x78);
    t6 = t6 | 0xFFFF;
    sd(t0, sp, 0x80);
    t7 = 520;
    sd(t1, sp, 0x88);
    a1 = a2;
    sh(t7, sp, 0xC);
    sd(t2, sp, 0x90);
    a2 = addiu(sp, 0x78);
    sd(t3, sp, 0x98);
    a0 = sp;
    sw(t5, sp, 0x10);
    sw(t6, sp, 0x14);
    sw(t4, sp, 0x54);
    sw(t5, sp, 0x0);
    link(ctx, 0x523AA8u);  // $ra first: the delay slot below depends on it
    sw(t6, sp, 0x8);
    call(ctx, gen::fn_vfprintf_00526238);
    lw(t7, sp, 0x0);
    ld(ra, sp, 0x60);
    sb(zero, t7, 0);
    sp = addiu(sp, 0xA0);
}

// 0x00523B40 sscanf -- 136 bytes; frame 0xA0: s0 sp+0x60, ra sp+0x68
// sscanf(str, fmt, ...): a read-only string FILE on the stack (flags 4, buffer = str, count = strlen(str), read
// callback eofread, no ungetc buffer, _data = _impure_ptr) handed to __svfscanf_r with the variadic save area. Returns
// the number of conversions (EOF when the input ends first).
void sscanf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523b40
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    t7 = 4;
    sd(s0, sp, 0x60);
    sd(ra, sp, 0x68);
    sd(a2, sp, 0x70);
    s0 = a1;
    sd(a3, sp, 0x78);
    sd(t0, sp, 0x80);
    sd(t1, sp, 0x88);
    sd(t2, sp, 0x90);
    sd(t3, sp, 0x98);
    sh(t7, sp, 0xC);
    sw(a0, sp, 0x10);
    link(ctx, 0x523B74u);  // $ra first: the delay slot below depends on it
    sw(a0, sp, 0x0);
    call(ctx, gen::fn_strlen_00524388);
    t7 = 0x780000;
    sw(v0, sp, 0x14);
    lw(t6, t7, 12080);  // 0x782F30
    a2 = s0;
    sw(v0, sp, 0x4);
    a3 = addiu(sp, 0x70);
    t7 = 0x520000;
    sw(zero, sp, 0x30);
    t7 = addiu(t7, 15160);  // &eofread
    sw(zero, sp, 0x44);
    sw(t7, sp, 0x20);
    a0 = t6;
    sw(t6, sp, 0x54);
    a1 = sp;
    jal(ctx, 0x523BB0u, gen::fn___svfscanf_r_00527b48);
    ld(s0, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0xA0);
}

// 0x00523BC8 _sscanf_r -- 148 bytes; frame 0xB0: s0 sp+0x60, s1 sp+0x68, ra sp+0x70
// sscanf_r(reent, str, fmt, ...): sscanf with an explicit _reent (the FILE's _data and the reent argument of
// __svfscanf_r).
void _sscanf_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523bc8
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    t7 = 4;
    sd(s0, sp, 0x60);
    sd(s1, sp, 0x68);
    sd(ra, sp, 0x70);
    s0 = a0;
    sd(a3, sp, 0x88);
    s1 = a2;
    sd(t0, sp, 0x90);
    a0 = a1;
    sd(t1, sp, 0x98);
    sd(t2, sp, 0xA0);
    sd(t3, sp, 0xA8);
    sh(t7, sp, 0xC);
    sw(a1, sp, 0x0);
    link(ctx, 0x523C04u);  // $ra first: the delay slot below depends on it
    sw(a1, sp, 0x10);
    call(ctx, gen::fn_strlen_00524388);
    t7 = 0x780000;
    sw(v0, sp, 0x14);
    lw(t6, t7, 12080);  // 0x782F30
    a0 = s0;
    sw(v0, sp, 0x4);
    a2 = s1;
    t7 = 0x520000;
    sw(t6, sp, 0x54);
    t7 = addiu(t7, 15160);  // &eofread
    sw(zero, sp, 0x30);
    sw(t7, sp, 0x20);
    a3 = addiu(sp, 0x88);
    sw(zero, sp, 0x44);
    a1 = sp;
    jal(ctx, 0x523C40u, gen::fn___svfscanf_r_00527b48);
    ld(s0, sp, 0x60);
    ld(s1, sp, 0x68);
    ld(ra, sp, 0x70);
    sp = addiu(sp, 0xB0);
}

// 0x00523C60 __sread -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// newlib's __sread(cookie = fp, buf, n): _read_r(fp->_data, fp->_file, buf, n); a non-negative count advances the
// FILE's offset (+80), a failure clears flag 0x1000 (offset valid). Returns the count.
void __sread(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523c60
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = a1;
    sd(s0, sp, 0x0);
    a3 = a2;
    sd(ra, sp, 0x8);
    a2 = t7;
    s0 = a0;
    lh(a1, a0, libc::file::kFile);
    link(ctx, 0x523C80u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, libc::file::kData);
    call(ctx, gen::fn__read_r_00522f38);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    if (i64(v0) < 0) {
        lhu(t7, s0, libc::file::kFlags);
        // 0x00523cb4
        charge(ctx, 3);
        t7 = t7 & 0xEFFF;
        sh(t7, s0, libc::file::kFlags);
        backedge(ctx);
    } else {
        // 0x00523c98
        charge(ctx, 3);
        lw(t7, s0, libs3::file::kOffset);
        t7 = addu(t7, v0);
        sw(t7, s0, libs3::file::kOffset);
    }
    // 0x00523ca4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00523D40 __sseek -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// newlib's __sseek(cookie = fp, offset, whence): _lseek_r (this build's _execve_r); on success stores the new offset
// (+80) and sets flag 0x1000 (offset valid), on -1 clears it.
void __sseek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523d40
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t7 = a1;
    sd(s0, sp, 0x0);
    a3 = a2;
    sd(ra, sp, 0x8);
    a2 = t7;
    s0 = a0;
    lh(a1, a0, libc::file::kFile);
    link(ctx, 0x523D60u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, libc::file::kData);
    call(ctx, gen::fn__execve_r_00520580);
    t6 = dsll32(v0, 0);
    t7 = si(-1);
    t6 = dsra32(t6, 0);
    if (v0 != t7) {
        // 0x00523d94
        charge(ctx, 4);
        lhu(t7, s0, libc::file::kFlags);
        sw(t6, s0, libs3::file::kOffset);
        t7 = t7 | 0x1000;
        backedge(ctx);
    } else {
        // 0x00523d78
        charge(ctx, 2);
        lhu(t7, s0, libc::file::kFlags);
        t7 = t7 & 0xEFFF;
    }
    // 0x00523d80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    sh(t7, s0, libc::file::kFlags);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00523DA8 __sclose -- 28 bytes; frame 0x10: ra sp+0x0
// newlib's __sclose(cookie = fp): _close_r(fp->_data, fp->_file), a tail call.
void __sclose(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523da8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(a1, a0, libc::file::kFile);
    ld(ra, sp, 0x0);
    lw(a0, a0, libc::file::kData);
    sp = addiu(sp, 0x10);
    gen::fn__close_r_0051e230(ctx);  // tail call
}

// 0x00525EC8 __submore -- 228 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// newlib's __submore(fp): grows the ungetc buffer. The first time (the buffer is still the FILE's own 3 bytes at +64)
// it allocates 1,024 bytes with _malloc_r and moves the 3 bytes to the end; later it doubles the buffer with _realloc_r
// and moves the old contents to the upper half (memcpy). Returns 0, or -1 when the allocation fails.
void __submore(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00525ec8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t7 = addiu(a0, 64);
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    lw(a1, a0, libs3::file::kUbBase);
    s2 = a0;
    if (a1 != t7) {
        // 0x00525f64
        charge(ctx, 8);
        lw(s3, a0, libs3::file::kUbSize);
        lw(a0, a0, libc::file::kData);
        s4 = sll(s3, 1);
        a2 = s4;
        jal(ctx, 0x525F70u, gen::fn__realloc_r_00522fc0);
        s1 = v0;
        v0 = si(-1);
        if (s1 == 0) {
            backedge(ctx);
        } else {
            // 0x00525f84
            charge(ctx, 10);
            s0 = addu(s1, s3);
            a2 = s3;
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x525F90u, gen::fn_memcpy_00521250);
            sw(s4, s2, 52);
            v0 = 0;
            sw(s0, s2, libc::file::kP);
            sw(s1, s2, libs3::file::kUbBase);
            backedge(ctx);
        }
    } else {
        // 0x00525ef4
        charge(ctx, 6);
        lw(a0, a0, libc::file::kData);
        a1 = 1024;
        jal(ctx, 0x525EF8u, gen::fn__malloc_r_005209c0);
        s1 = v0;
        v0 = si(-1);
        if (s1 != 0) {
            // 0x00525f0c
            charge(ctx, 5);
            sw(s1, s2, libs3::file::kUbBase);
            t7 = 1024;
            sw(t7, s2, libs3::file::kUbSize);
            s3 = 2;
            s1 = addiu(s1, 1021);
            for (;;) {
                // 0x00525f20
                charge(ctx, 7);
                t7 = addu(s3, s2);
                t5 = addu(s1, s3);
                lbu(t6, t7, 64);
                s3 = addiu(s3, -1);
                sb(t6, t5, 0);
                if (i64(s3) < 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00525f3c
            charge(ctx, 2);
            sw(s1, s2, libc::file::kP);
            v0 = 0;
        }
    }
    // 0x00525f44 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00525FB0 ungetc -- 400 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ungetc(c, fp): EOF (-1) is refused; sets the FILE up for reading (like __srefill: __sinit, flush a writing FILE,
// flags | 4), clears EOF (0x20); when the byte just before the read position equals c it simply backs up; otherwise it
// saves the read position (+56 / +60) and switches to the ungetc buffer (+48, grown by __submore). Returns c as an
// unsigned char, or -1.
void ungetc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00525fb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t2 = si(-1);
    sd(s0, sp, 0x0);
    t7 = si(-1);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a1;
    s1 = a0;
    if (a0 != t7) {
        // 0x00525fd4
        charge(ctx, 3);
        lw(a0, a1, 84);
        if (a0 != 0) {
            lw(t7, a0, 56);
        } else {
            // 0x00525fe0
            charge(ctx, 5);
            t7 = 0x780000;
            lw(t6, t7, 12080);  // 0x782F30
            sw(t6, a1, 84);
            a0 = t6;
            lw(t7, a0, 56);
        }
        // 0x00525ff4
        charge(ctx, 2);
        if (t7 != 0) {
            lhu(t7, s0, libc::file::kFlags);
        } else {
            // 0x00525ffc
            charge(ctx, 3);
            jal(ctx, 0x525FFCu, gen::fn___sinit_0051fa20);
            lhu(t7, s0, libc::file::kFlags);
        }
        // 0x00526008
        charge(ctx, 4);
        t6 = t7 & 0xFFDF;
        t7 = t6 & 0x4;
        sh(t6, s0, libc::file::kFlags);
        if (t7 == 0) {
            // 0x00526018
            charge(ctx, 3);
            t7 = t6 & 0x10;
            t2 = si(-1);
            if (t7 != 0) {
                // 0x00526024
                charge(ctx, 3);
                t7 = t6 & 0x8;
                if (t7 == 0) {
                    lhu(t7, s0, libc::file::kFlags);
                } else {
                    // 0x00526030
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x526030u, gen::fn_fflush_0051f728);
                    t2 = si(-1);
                    if (v0 == 0) {
                        // 0x00526040
                        charge(ctx, 6);
                        lhu(t7, s0, libc::file::kFlags);
                        sw(zero, s0, libc::file::kW);
                        t7 = t7 & 0xFFF7;
                        sw(zero, s0, libc::file::kLbfSize);
                        sh(t7, s0, libc::file::kFlags);
                        lhu(t7, s0, libc::file::kFlags);
                        goto L_00526058;
                    }
                    // 0x005260b0 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(s0, sp, 0x0);
                    v0 = t2;
                    ld(s1, sp, 0x8);
                    ld(ra, sp, 0x10);
                    sp = addiu(sp, 0x20);
                    return;
                }
            L_00526058:
                charge(ctx, 2);
                t7 = t7 | 0x4;
                sh(t7, s0, libc::file::kFlags);
                goto L_00526060;
            }
            // 0x005260b0 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s0, sp, 0x0);
            v0 = t2;
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00526060:
        charge(ctx, 3);
        lw(t7, s0, libs3::file::kUbBase);
        s1 = s1 & 0xFF;
        if (t7 == 0) {
            // 0x005260c8
            charge(ctx, 3);
            lw(t7, s0, libc::file::kBufBase);
            lw(t3, s0, libc::file::kP);
            if (t7 == 0) {
                // 0x00526108
                charge(ctx, 1);
                lw(t6, s0, libc::file::kR);
            L_0052610c:
                charge(ctx, 13);
                t7 = 1;
                t5 = addiu(s0, 64);
                sw(t3, s0, libs3::file::kUp);
                sw(t7, s0, libc::file::kR);
                t4 = addiu(s0, 66);
                sw(t6, s0, libs3::file::kUr);
                t2 = s1;
                t7 = 3;
                sw(t5, s0, libs3::file::kUbBase);
                sw(t7, s0, libs3::file::kUbSize);
                sw(t4, s0, libc::file::kP);
                sb(s1, s0, 66);
                backedge(ctx);
            } else {
                // 0x005260d4
                charge(ctx, 3);
                t7 = sltu(t7, t3);
                lw(t6, s0, libc::file::kR);
                if (t7 == 0) {
                    goto L_0052610c;
                }
                // 0x005260e0
                charge(ctx, 3);
                lbu(t7, t3, -1);
                if (t7 != s1) {
                    goto L_0052610c;
                }
                // 0x005260ec
                charge(ctx, 6);
                t7 = addiu(t3, -1);
                sw(t7, s0, libc::file::kP);
                t2 = s1;
                t6 = addiu(t6, 1);
                sw(t6, s0, libc::file::kR);
                backedge(ctx);
            }
        } else {
            // 0x0052606c
            charge(ctx, 5);
            lw(t7, s0, libc::file::kR);
            lw(t6, s0, libs3::file::kUbSize);
            t7 = slt(t7, t6);
            if (t7 != 0) {
                lw(t6, s0, libc::file::kP);
            } else {
                // 0x00526080
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x526080u, gen::fn___submore_00525ec8);
                t2 = si(-1);
                if (v0 == 0) {
                    // 0x00526090
                    charge(ctx, 1);
                    lw(t6, s0, libc::file::kP);
                    goto L_00526094;
                }
                // 0x005260b0 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(s0, sp, 0x0);
                v0 = t2;
                ld(s1, sp, 0x8);
                ld(ra, sp, 0x10);
                sp = addiu(sp, 0x20);
                return;
            }
        L_00526094:
            charge(ctx, 7);
            t2 = s1;
            t7 = addiu(t6, -1);
            sw(t7, s0, libc::file::kP);
            sb(s1, t6, -1);
            lw(t7, s0, libc::file::kR);
            t7 = addiu(t7, 1);
            sw(t7, s0, libc::file::kR);
        }
    }
    // 0x005260b0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    v0 = t2;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00526140 __sprint -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// newlib's __sprint(fp, uio): hands vfprintf's collected iovec list to the vectored write (_getpid_r = __sfvwrite) when
// it holds anything (uio[+8] != 0), then empties it (uio[+4] = uio[+8] = 0). Returns the write's result (0 for an empty
// list).
void __sprint(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a1{ctx, 5}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00526140
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    lw(t7, a1, 8);
    s0 = a1;
    if (t7 != 0) {
        // 0x00526170
        charge(ctx, 5);
        jal(ctx, 0x526170u, gen::fn__getpid_r_00520048);
        sw(zero, s0, 4);
        sw(zero, s0, 8);
        backedge(ctx);
    } else {
        // 0x00526158
        charge(ctx, 2);
        sw(zero, a1, 4);
        v0 = 0;
    }
    // 0x00526160 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00526188 __sbprintf -- 176 bytes; frame 0x480: s0 sp+0x460, s1 sp+0x468, ra sp+0x470
// newlib's __sbprintf(fp, fmt, ap): vfprintf for an unbuffered FILE through a 1,024-byte stack buffer: a FILE copy on
// the stack (flags without 2 = unbuffered, same file / cookie / write callback / _data), vfprintf into it, fflush, and
// the error flag (0x40) copied back. Returns the count, or -1 when the flush fails.
void __sbprintf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00526188
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x480);
    t2 = 1024;
    sd(s0, sp, 0x460);
    t1 = addiu(sp, 0x60);
    sd(s1, sp, 0x468);
    sd(ra, sp, 0x470);
    s0 = a0;
    sw(t1, sp, 0x10);
    lhu(t7, a0, 12);
    lw(t4, a0, 84);
    lhu(t3, s0, 14);
    t7 = t7 & 0xFFFD;
    lw(t6, s0, 28);
    a0 = sp;
    lw(t5, s0, 36);
    sw(t4, sp, 0x54);
    sh(t7, sp, 0xC);
    sh(t3, sp, 0xE);
    sw(t6, sp, 0x1C);
    sw(t5, sp, 0x24);
    sw(t2, sp, 0x14);
    sw(t1, sp, 0x0);
    sw(t2, sp, 0x8);
    link(ctx, 0x5261E4u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn_vfprintf_00526238);
    s1 = v0;
    a0 = sp;
    if (i64(v0) >= 0) {
        // 0x005261f8
        charge(ctx, 4);
        jal(ctx, 0x5261F8u, gen::fn_fflush_0051f728);
        t7 = si(-1);
        if (v0 != 0) s1 = t7;
    }
    // 0x00526208
    charge(ctx, 4);
    lhu(t7, sp, 0xC);
    t7 = t7 & 0x40;
    v0 = s1;
    if (t7 != 0) {
        // 0x00526218
        charge(ctx, 3);
        lhu(t7, s0, 12);
        t7 = t7 | 0x40;
        sh(t7, s0, 12);
    }
    // 0x00526224 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x460);
    ld(s1, sp, 0x468);
    ld(ra, sp, 0x470);
    sp = addiu(sp, 0x480);
}

// 0x00527810 cvt -- 424 bytes; frame 0x60: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, s7 sp+0x48, fp sp+0x50, ra sp+0x58
// vfprintf's floating-point conversion helper cvt(reent, value, ndigits, flags, &sign, &decpt, ch, &length): a negative
// value gives sign '-' and its magnitude (dpsub from 0); _dtoa_r in mode 3 for %f, mode 2 with one more digit for %e /
// %E (mode 2 for %g); except for %g / %G without the alternate flag the digits are padded with '0' up to the precision
// (for %f counted from the decimal point, a zero value placing it by hand); *length = the digit count. Returns the
// digit string.
void cvt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00527810
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    t7 = 102;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s0 = t0;
    sd(s3, sp, 0x28);
    s1 = t2;
    sd(s4, sp, 0x30);
    s2 = 3;
    sd(s5, sp, 0x38);
    s3 = a1;
    sd(s6, sp, 0x40);
    s4 = a2;
    sd(s7, sp, 0x48);
    s5 = t1;
    sd(fp, sp, 0x50);
    s6 = a0;
    sd(ra, sp, 0x58);
    s7 = a3;
    fp = t3;
    if (t2 != t7) {
        // 0x00527868
        charge(ctx, 3);
        t7 = 101;
        cc = t2 == t7;  // the condition, before the delay slot changes it
        t7 = 69;
        if (!cc) {
            // 0x00527874
            charge(ctx, 2);
            s2 = 2;
            if (t2 == t7) {
                goto L_0052787c;
            }
            goto L_00527884;
        }
    L_0052787c:
        charge(ctx, 2);
        s4 = addiu(s4, 1);
        s2 = 2;
    }
L_00527884:
    charge(ctx, 3);
    t7 = dsra32(s3, 0);
    if (i64(t7) >= 0) {
        sb(zero, s0, 0);
    } else {
        // 0x00527890
        charge(ctx, 6);
        a1 = s3;
        a0 = 0;
        jal(ctx, 0x527894u, gen::fn_dpsub_005311c8);
        t7 = 45;
        s3 = v0;
        sb(t7, s0, 0);
    }
    // 0x005278a8
    charge(ctx, 11);
    a2 = s2;
    a0 = s6;
    a1 = s3;
    a3 = s4;
    t0 = s5;
    t1 = sp;
    t2 = addiu(sp, 0x4);
    jal(ctx, 0x5278C0u, gen::fn__dtoa_r_0051e4b0);
    t7 = 103;
    s2 = v0;
    if (s1 != t7) {
        // 0x005278d4
        charge(ctx, 3);
        t7 = 71;
        cc = s1 != t7;  // the condition, before the delay slot changes it
        t7 = 102;
        if (!cc) {
            goto L_005278e0;
        }
    L_005278ec:
        charge(ctx, 2);
        s0 = addu(s2, s4);
        if (s1 == t7) {
            // 0x005278f4
            charge(ctx, 4);
            lb(t6, s2, 0);
            t7 = 48;
            if (t6 != t7) {
                lw(t7, s5, 0);
            } else {
                // 0x00527904
                charge(ctx, 5);
                a0 = s3;
                a1 = 0;
                jal(ctx, 0x527908u, gen::fn_dpcmp_005316d0);
                t7 = 1;
                if (v0 != 0) {
                    // 0x00527918
                    charge(ctx, 2);
                    t7 = subu(t7, s4);
                    sw(t7, s5, 0);
                }
                // 0x00527920
                charge(ctx, 1);
                lw(t7, s5, 0);
            }
            // 0x00527924
            charge(ctx, 1);
            s0 = addu(s0, t7);
        }
        // 0x00527928
        charge(ctx, 11);
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x52792Cu, gen::fn_dpcmp_005316d0);
        lw(t7, sp, 0x4);
        v0 = v0 ^ 0x0;
        if (v0 == 0) t7 = s0;
        sw(t7, sp, 0x4);
        lw(t6, sp, 0x4);
        t7 = sltu(t6, s0);
        t5 = t6;
        if (t7 != 0) {
            // 0x00527954
            charge(ctx, 1);
            t4 = 48;
            for (;;) {
                // 0x00527958
                charge(ctx, 7);
                sb(t4, t5, 0);
                t6 = addiu(t5, 1);
                t7 = sltu(t6, s0);
                sw(t6, sp, 0x4);
                t5 = t6;
                if (t7 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00527974 (the shared epilogue, written out on this path)
        charge(ctx, 15);
        t7 = subu(t6, s2);
        ld(s0, sp, 0x10);
        sw(t7, fp, 0x0);
        v0 = s2;
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
        return;
    }
L_005278e0:
    charge(ctx, 3);
    t7 = s7 & 0x1;
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = 102;
    if (!cc) {
        goto L_005278ec;
    }
    // 0x005279b0
    charge(ctx, 2);
    lw(t6, sp, 0x4);
    backedge(ctx);
    // 0x00527974 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    t7 = subu(t6, s2);
    ld(s0, sp, 0x10);
    sw(t7, fp, 0x0);
    v0 = s2;
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

// 0x00527A88 vfscanf -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// vfscanf(fp, fmt, ap): sets the FILE's _data to _impure_ptr when unset, runs __sinit when the _reent is fresh (+56),
// then __svfscanf_r(fp->_data, fp, fmt, ap).
void vfscanf(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00527a88
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    s1 = a2;
    lw(a0, a0, libc::file::kData);
    s2 = a1;
    if (a0 == 0) {
        // 0x00527ab0
        charge(ctx, 4);
        t7 = 0x780000;
        lw(t6, t7, 12080);  // 0x782F30
        sw(t6, s0, libc::file::kData);
        a0 = t6;
    }
    // 0x00527ac0
    charge(ctx, 3);
    lw(t7, a0, libs3::reent::kInitDone);
    if (t7 != 0) {
        lw(a0, s0, libc::file::kData);
    } else {
        // 0x00527acc
        charge(ctx, 3);
        jal(ctx, 0x527ACCu, gen::fn___sinit_0051fa20);
        lw(a0, s0, libc::file::kData);
    }
    // 0x00527ad8
    charge(ctx, 9);
    a1 = s0;
    a2 = s2;
    ld(ra, sp, 0x18);
    a3 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn___svfscanf_r_00527b48(ctx);  // tail call
}

// 0x00527B00 __svfscanf -- 48 bytes; frame 0x10: ra sp+0x0
// __svfscanf(fp, fmt, ap) = __svfscanf_r(_impure_ptr, fp, fmt, ap).
void __svfscanf(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00527b00
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
    gen::fn___svfscanf_r_00527b48(ctx);  // tail call
}

// 0x00527B30 _vfscanf_r -- 20 bytes; frame 0x10: ra sp+0x0
// _vfscanf_r: a plain tail call into __svfscanf_r with the same arguments.
void _vfscanf_r(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00527b30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___svfscanf_r_00527b48(ctx);  // tail call
}

// 0x00527B48 __svfscanf_r -- 3216 bytes; frame 0x2E0: s1 sp+0x298, s3 sp+0x2A8, s5 sp+0x2B8, fp sp+0x2D0, s0 sp+0x290, s2 sp+0x2A0, s4 sp+0x2B0, s6 sp+0x2C0, s7 sp+0x2C8, ra sp+0x2D8
// newlib's scanf engine __svfscanf_r(reent, fp, fmt, ap): walks the format -- white space skips input white space (the
// <ctype.h> table 0x7BE9C8), literal characters must match, % conversions with the width, the assignment-suppress '*',
// the h / l / L sizes (l is 64-bit), %c / %s / %[ (__sccl's 256-byte table on the stack) / %n / %p and the integers
// (read into a stack buffer, then _strtol_r / _strtoul_r through jalr) and the floats (buffer, then _strtod_r, dptofp
// for float targets; the exponent through sprintf "e%ld"); input comes from the FILE's buffer (+0 / +4), refilled by
// __srefill, characters pushed back with ungetc. Returns the count of assignments, or EOF (-1) when input fails before
// the first.
void __svfscanf_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00527b48
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(s1, sp, 0x298);
    sd(s3, sp, 0x2A8);
    sd(s5, sp, 0x2B8);
    s1 = a1;
    sd(fp, sp, 0x2D0);
    s3 = a2;
    sd(s0, sp, 0x290);
    s5 = 0;
    sd(s2, sp, 0x2A0);
    fp = 0;
    sd(s4, sp, 0x2B0);
    sd(s6, sp, 0x2C0);
    sd(s7, sp, 0x2C8);
    sd(ra, sp, 0x2D8);
    sw(a0, sp, 0x260);
    sw(a3, sp, 0x264);
    sw(zero, sp, 0x26C);
    sw(zero, sp, 0x268);
    for (;;) {
    L_00527b94:
        charge(ctx, 1);
        lb(t5, s3, 0);
        for (;;) {
        L_00527b98:
            charge(ctx, 3);
            lw(v0, sp, 0x268);
            s3 = addiu(s3, 1);
            if (t5 == 0) {
                break;
            }
            // 0x00527ba4
            charge(ctx, 3);
            t7 = 1;
            cc = t7 != t7;  // the condition, before the delay slot changes it
            t7 = 37;
            if (!cc) {
                // 0x00527bb0
                charge(ctx, 7);
                t7 = 0x7C0000;
                t4 = addiu(t7, -5688);  // &0x7BE9C8
                t6 = addu(t5, t4);
                lbu(t7, t6, 0);
                t7 = t7 & 0x8;
                s0 = t4;
                if (t7 == 0) {
                    // 0x00527c20
                    charge(ctx, 1);
                    t7 = 37;
                    goto L_00527c24;
                }
                for (;;) {
                    // 0x00527bcc
                    charge(ctx, 3);
                    lw(t7, s1, 4);
                    if (i64(t7) > 0) {
                        lw(t5, s1, 0);
                    } else {
                        // 0x00527bd8
                        charge(ctx, 4);
                        a0 = s1;
                        jal(ctx, 0x527BD8u, gen::fn___srefill_00523580);
                        if (v0 == 0) {
                            // 0x00527be8
                            charge(ctx, 1);
                            lw(t5, s1, 0);
                            goto L_00527bec;
                        }
                        lb(t5, s3, 0);
                        backedge(ctx);
                        break;
                    }
                L_00527bec:
                    charge(ctx, 6);
                    lbu(t7, t5, 0);
                    t7 = addu(t7, s0);
                    lbu(t6, t7, 0);
                    t6 = t6 & 0x8;
                    t7 = addiu(t5, 1);
                    if (t6 == 0) {
                        backedge(ctx);
                        goto L_00527b94;
                    }
                    // 0x00527c04
                    charge(ctx, 6);
                    lw(t6, s1, 4);
                    sw(t7, s1, 0);
                    s5 = addiu(s5, 1);
                    t6 = addiu(t6, -1);
                    sw(t6, s1, 4);
                    backedge(ctx);
                }
                continue;
            }
        L_00527c24:
            charge(ctx, 2);
            s0 = addiu(s3, -1);
            if (t5 == t7) {
                // 0x00527c2c
                charge(ctx, 2);
                s7 = 0;
                s4 = 0;
                for (;;) {
                    // 0x00527c34
                    charge(ctx, 4);
                    lb(s0, s3, 0);
                    t7 = sltiu(s0, 121);
                    s3 = addiu(s3, 1);
                    if (t7 == 0) {
                        goto L_005287a0;
                    }
                    // 0x00527c44
                    charge(ctx, 7);
                    t6 = 0x7C0000;
                    t7 = sll(s0, 2);
                    t6 = addiu(t6, -4128);  // &0x7BEFE0
                    t7 = addu(t7, t6);
                    lw(t5, t7, 0);
                    switch (t5.u()) {
                    case 0x527C60u:  // table[37]
                        goto L_00527c60;
                    case 0x527D04u:  // table[0]
                        goto L_00527d04;
                    case 0x527D0Cu:  // table[42]
                        // 0x00527d0c
                        charge(ctx, 2);
                        s4 = s4 | 0x8;
                        backedge(ctx);
                        continue;
                    case 0x527D14u:  // table[48, 49, 50, 51, 52, 53, 54, 55, 56, 57]
                        // 0x00527d14
                        charge(ctx, 5);
                        t7 = 10;
                        mult(t7, s7, t7);
                        t7 = addu(t7, s0);
                        s7 = addiu(t7, -48);
                        backedge(ctx);
                        continue;
                    case 0x527D28u:  // table[68]
                        goto L_00527d28;
                    case 0x527D2Cu:  // table[100]
                        goto L_00527d2c;
                    case 0x528688u:  // table[76]
                        // 0x00528688
                        charge(ctx, 2);
                        s4 = s4 | 0x2;
                        backedge(ctx);
                        continue;
                    case 0x528690u:  // table[79]
                        goto L_00528690;
                    case 0x528694u:  // table[111]
                        goto L_00528694;
                    case 0x5286ACu:  // table[91]
                        goto L_005286ac;
                    case 0x5286C8u:  // table[99]
                        goto L_005286c8;
                    case 0x5286D4u:  // table[69, 71, 101, 102, 103]
                        goto L_005286d4;
                    case 0x5286DCu:  // table[104]
                        // 0x005286dc
                        charge(ctx, 2);
                        s4 = s4 | 0x4;
                        backedge(ctx);
                        continue;
                    case 0x5286E4u:  // table[105]
                        goto L_005286e4;
                    case 0x5286F8u:  // table[108]
                        // 0x005286f8
                        charge(ctx, 2);
                        s4 = s4 | 0x1;
                        backedge(ctx);
                        continue;
                    case 0x528700u:  // table[110]
                        goto L_00528700;
                    case 0x528770u:  // table[112]
                        goto L_00528770;
                    case 0x528788u:  // table[115]
                        goto L_00528788;
                    case 0x528790u:  // table[117]
                        goto L_00528790;
                    case 0x5287A0u:  // table[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 70, 72, 73, 74, 75, 77, 78, 80, 81, 82, 83, 84, 85, 86, 87, 89, 90, 92, 93, 94, 95, 96, 97, 98, 106, 107, 109, 113, 114, 116, 118, 119]
                        goto L_005287a0;
                    case 0x5287D0u:  // table[88, 120]
                        goto L_005287d0;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, t5.u());
                        return;
                    }
                }
            L_00528700:
                charge(ctx, 3);
                t7 = s4 & 0x8;
                if (t7 == 0) {
                    goto L_0052870c_197;
                }
                lb(t5, s3, 0);
                backedge(ctx);
                continue;
            }
        L_00527c64:
            charge(ctx, 1);
            s2 = 0;
            for (;;) {
                // 0x00527c68
                charge(ctx, 3);
                lw(t7, s1, 4);
                if (i64(t7) > 0) {
                    lw(t5, s1, 0);
                } else {
                    // 0x00527c74
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x527C74u, gen::fn___srefill_00523580);
                    lw(t5, sp, 0x268);
                    if (v0 != 0) {
                        goto L_00527cf8;
                    }
                    // 0x00527c84
                    charge(ctx, 1);
                    lw(t5, s1, 0);
                    goto L_00527c88;
                }
            L_00527c88:
                charge(ctx, 4);
                lb(t6, s0, 0);
                lbu(t7, t5, 0);
                cc = t7 != t6;  // the condition, before the delay slot changes it
                t7 = addiu(t5, 1);
                if (cc) {
                    goto L_00527cc0;
                }
                // 0x00527c98
                charge(ctx, 8);
                lw(t6, s1, 4);
                sw(t7, s1, 0);
                s5 = addiu(s5, 1);
                t6 = addiu(t6, -1);
                s0 = addiu(s0, 1);
                s2 = addiu(s2, 1);
                sw(t6, s1, 4);
                if (i64(s2) > 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00527cb8
            charge(ctx, 2);
            lb(t5, s3, 0);
            backedge(ctx);
        }
        // 0x00527cc4 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0x290);
        ld(s1, sp, 0x298);
        ld(s2, sp, 0x2A0);
        ld(s3, sp, 0x2A8);
        ld(s4, sp, 0x2B0);
        ld(s5, sp, 0x2B8);
        ld(s6, sp, 0x2C0);
        ld(s7, sp, 0x2C8);
        ld(fp, sp, 0x2D0);
        ld(ra, sp, 0x2D8);
        sp = addiu(sp, 0x2E0);
        return;
    }
L_00527cc0:
    charge(ctx, 1);
    lw(v0, sp, 0x268);
    // 0x00527cc4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x290);
    ld(s1, sp, 0x298);
    ld(s2, sp, 0x2A0);
    ld(s3, sp, 0x2A8);
    ld(s4, sp, 0x2B0);
    ld(s5, sp, 0x2B8);
    ld(s6, sp, 0x2C0);
    ld(s7, sp, 0x2C8);
    ld(fp, sp, 0x2D0);
    ld(ra, sp, 0x2D8);
    sp = addiu(sp, 0x2E0);
    return;
L_00527c60:
    charge(ctx, 1);
    s0 = addiu(s3, -1);
    goto L_00527c64;
L_00527cf4:
    charge(ctx, 1);
    lw(t5, sp, 0x268);
L_00527cf8:
    charge(ctx, 3);
    v0 = si(-1);
    if (t5 != 0) v0 = t5;
    backedge(ctx);
    // 0x00527cc4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x290);
    ld(s1, sp, 0x298);
    ld(s2, sp, 0x2A0);
    ld(s3, sp, 0x2A8);
    ld(s4, sp, 0x2B0);
    ld(s5, sp, 0x2B8);
    ld(s6, sp, 0x2C0);
    ld(s7, sp, 0x2C8);
    ld(fp, sp, 0x2D0);
    ld(ra, sp, 0x2D8);
    sp = addiu(sp, 0x2E0);
    return;
L_00527d04:
    charge(ctx, 2);
    v0 = si(-1);
    backedge(ctx);
    // 0x00527cc4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x290);
    ld(s1, sp, 0x298);
    ld(s2, sp, 0x2A0);
    ld(s3, sp, 0x2A8);
    ld(s4, sp, 0x2B0);
    ld(s5, sp, 0x2B8);
    ld(s6, sp, 0x2C0);
    ld(s7, sp, 0x2C8);
    ld(fp, sp, 0x2D0);
    ld(ra, sp, 0x2D8);
    sp = addiu(sp, 0x2E0);
    return;
L_00527d28:
    charge(ctx, 1);
    s4 = s4 | 0x1;
L_00527d2c:
    charge(ctx, 3);
    t7 = 0x520000;
    s0 = 3;
    t7 = addiu(t7, 23056);  // &_strtol_r
L_00527d38:
    charge(ctx, 2);
    sw(t7, sp, 0x26C);
    fp = 0xA;
L_00527d40:
    charge(ctx, 3);
    lw(t7, s1, 4);
    cc = i64(t7) > 0;  // the condition, before the delay slot changes it
    t7 = s4 & 0x20;
    if (!cc) {
        // 0x00527d4c
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x527D4Cu, gen::fn___srefill_00523580);
        t7 = s4 & 0x20;
        if (v0 == 0) {
            goto L_00527d5c;
        }
        backedge(ctx);
        goto L_00527cf4;
    }
L_00527d5c:
    charge(ctx, 2);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = sltiu(s0, 5);
    if (!cc) {
        // 0x00527d64
        charge(ctx, 9);
        lw(t5, s1, 0);
        t7 = 0x7C0000;
        t4 = addiu(t7, -5688);  // &0x7BE9C8
        lbu(t6, t5, 0);
        t6 = addu(t6, t4);
        lbu(t7, t6, 0);
        t7 = t7 & 0x8;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = sltiu(s0, 5);
        if (cc) {
            goto L_00527dc8;
        }
        // 0x00527d88
        charge(ctx, 2);
        s2 = t4;
        lw(t7, s1, 4);
        for (;;) {
            // 0x00527d90
            charge(ctx, 4);
            s5 = addiu(s5, 1);
            t7 = addiu(t7, -1);
            sw(t7, s1, 4);
            if (i64(t7) > 0) {
                // 0x00527da0
                charge(ctx, 3);
                t7 = addiu(t5, 1);
                sw(t7, s1, 0);
                lw(t5, s1, 0);
                goto L_00527dac;
            }
            // 0x00528670
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x528670u, gen::fn___srefill_00523580);
            if (v0 != 0) {
                lw(t5, sp, 0x268);
                backedge(ctx);
                break;
            }
            // 0x00528680
            charge(ctx, 2);
            lw(t5, s1, 0);
            backedge(ctx);
        L_00527dac:
            charge(ctx, 6);
            lbu(t7, t5, 0);
            t7 = addu(t7, s2);
            lbu(t6, t7, 0);
            t6 = t6 & 0x8;
            if (t6 == 0) {
                goto L_00527dc4_41;
            }
            lw(t7, s1, 4);
            backedge(ctx);
        }
        goto L_00527cf8;
    }
L_00527dc8:
    charge(ctx, 2);
    if (t7 == 0) {
        lb(t5, s3, 0);
        backedge(ctx);
        goto L_00527b98;
    }
    // 0x00527dd0
    charge(ctx, 7);
    t6 = 0x7C0000;
    t7 = sll(s0, 2);
    t6 = addiu(t6, -3644);  // &0x7BF1C4
    t7 = addu(t7, t6);
    lw(t5, t7, 0);
    switch (t5.u()) {
    case 0x527DECu:  // table[0]
        goto L_00527dec;
    case 0x527E98u:  // table[1]
        goto L_00527e98;
    case 0x527FE0u:  // table[2]
        goto L_00527fe0;
    case 0x528124u:  // table[3]
        goto L_00528124;
    case 0x52839Cu:  // table[4]
        // 0x0052839c
        charge(ctx, 12);
        s7 = addiu(s7, -1);
        sd(zero, sp, 0x270);
        t6 = sltiu(s7, 349);
        sw(zero, sp, 0x280);
        t7 = 348;
        sd(zero, sp, 0x278);
        if (t6 == 0) s7 = t7;
        s4 = s4 | 0x3C0;
        s7 = addiu(s7, 1);
        s2 = 0;
        s6 = addiu(sp, 0x100);
        if (s7 != 0) {
            // 0x005283cc
            charge(ctx, 1);
            lw(t7, s1, 0);
            for (;;) {
                // 0x005283d0
                charge(ctx, 5);
                lbu(s0, t7, 0);
                t6 = addiu(s0, -43);
                t7 = sltiu(t6, 59);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = sll(t6, 2);
                if (cc) {
                    goto L_00528438;
                }
                // 0x005283e4
                charge(ctx, 6);
                t6 = 0x7C0000;
                t6 = addiu(t6, -3312);  // &0x7BF310
                t7 = addu(t7, t6);
                lw(t5, t7, 0);
                switch (t5.u()) {
                case 0x5283FCu:  // table[5]
                    // 0x005283fc
                    charge(ctx, 3);
                    t7 = s4 & 0x80;
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = si(-65);
                    if (cc) {
                    L_005285e0:
                        charge(ctx, 1);
                        t7 = si(-193);
                    L_005285e4:
                        charge(ctx, 1);
                        s4 = s4 & t7;
                    L_005285e8:
                        charge(ctx, 4);
                        sb(s0, s6, 0);
                        s7 = addiu(s7, -1);
                        s6 = addiu(s6, 1);
                        backedge(ctx);
                    } else {
                        // 0x00528408
                        charge(ctx, 2);
                        s2 = daddiu(s2, 1);
                        s4 = s4 & t7;
                    }
                    // 0x00528410
                    charge(ctx, 5);
                    lw(t7, s1, 4);
                    s5 = addiu(s5, 1);
                    t7 = addiu(t7, -1);
                    sw(t7, s1, 4);
                    if (i64(t7) > 0) {
                        // 0x00528424
                        charge(ctx, 3);
                        lw(t7, s1, 0);
                        t7 = addiu(t7, 1);
                        sw(t7, s1, 0);
                        goto L_00528430;
                    }
                    // 0x005285c4
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x5285C4u, gen::fn___srefill_00523580);
                    if (v0 != 0) {
                        goto L_005285d4_170;
                    }
                    backedge(ctx);
                L_00528430:
                    charge(ctx, 2);
                    if (s7 == 0) {
                        goto L_00528438;
                    }
                    lw(t7, s1, 0);
                    backedge(ctx);
                    continue;
                case 0x528438u:  // table[1, 4, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57]
                    goto L_00528438;
                case 0x5285E0u:  // table[6, 7, 8, 9, 10, 11, 12, 13, 14]
                    goto L_005285e0;
                case 0x5285F8u:  // table[0, 2]
                    // 0x005285f8
                    charge(ctx, 3);
                    t7 = s4 & 0x40;
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = si(-65);
                    if (cc) {
                        backedge(ctx);
                        goto L_00528438;
                    }
                    // 0x00528604
                    charge(ctx, 2);
                    s4 = s4 & t7;
                    backedge(ctx);
                    goto L_005285e8;
                case 0x52860Cu:  // table[3]
                    // 0x0052860c
                    charge(ctx, 3);
                    t7 = s4 & 0x100;
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = si(-321);
                    if (cc) {
                        backedge(ctx);
                        goto L_00528438;
                    }
                    // 0x00528618
                    charge(ctx, 2);
                    sd(s2, sp, 0x270);
                    backedge(ctx);
                    goto L_005285e4;
                case 0x528620u:  // table[26, 58]
                    // 0x00528620
                    charge(ctx, 4);
                    t6 = s4 & 0x280;
                    t7 = 512;
                    cc = t6 == t7;  // the condition, before the delay slot changes it
                    t7 = s4 & 0x200;
                    if (!cc) {
                        // 0x00528630
                        charge(ctx, 2);
                        if (t7 == 0) {
                            backedge(ctx);
                            goto L_00528438;
                        }
                        // 0x00528638
                        charge(ctx, 2);
                        t7 = s4 & 0x80;
                        if (s2 != 0) {
                            goto L_00528640;
                        }
                        backedge(ctx);
                        break;
                    }
                L_00528640:
                    charge(ctx, 3);
                    t7 = s4 & 0x100;
                    cc = t7 != 0;  // the condition, before the delay slot changes it
                    t7 = si(-769);
                    if (!cc) {
                        // 0x0052864c
                        charge(ctx, 4);
                        ld(t6, sp, 0x270);
                        sw(s6, sp, 0x280);
                        s2 = s2 - t6;
                        sd(s2, sp, 0x278);
                    }
                    // 0x0052865c
                    charge(ctx, 4);
                    s2 = 0;
                    t7 = s4 & t7;
                    s4 = t7 | 0xC0;
                    backedge(ctx);
                    goto L_005285e8;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, t5.u());
                    return;
                }
                break;
            }
            goto L_00528448;
        }
    L_00528438:
        charge(ctx, 2);
        t7 = si(-129);
        if (s2 != 0) {
            // 0x00528440
            charge(ctx, 1);
            s4 = s4 & t7;
        }
        // 0x00528444
        charge(ctx, 1);
        t7 = s4 & 0x80;
    L_00528448:
        charge(ctx, 2);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = s4 & 0x200;
        if (!cc) {
            // 0x00528450
            charge(ctx, 2);
            t5 = addiu(sp, 0x100);
            if (t7 != 0) {
                goto L_00528458_148;
            }
            // 0x00528480
            charge(ctx, 5);
            s6 = addiu(s6, -1);
            lb(s0, s6, 0);
            t7 = 101;
            s5 = addiu(s5, -1);
            if (s0 != t7) {
                // 0x00528494
                charge(ctx, 3);
                t7 = 69;
                a0 = s0;
                if (s0 != t7) {
                    // 0x005284a0
                    charge(ctx, 5);
                    a1 = s1;
                    jal(ctx, 0x5284A0u, gen::fn_ungetc_00525fb0);
                    s6 = addiu(s6, -1);
                    lb(s0, s6, 0);
                    s5 = addiu(s5, -1);
                }
            }
            // 0x005284b4
            charge(ctx, 3);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x5284B8u, gen::fn_ungetc_00525fb0);
            goto L_005284c0;
        }
    L_005284c0:
        charge(ctx, 3);
        t7 = s4 & 0x8;
        if (t7 == 0) {
            goto L_005284cc_156;
        }
        lb(t5, s3, 0);
        backedge(ctx);
        goto L_00527b98;
    default:  // not one of the table's targets: the dispatch table, as the recompiled body
        tail(ctx, t5.u());
        return;
    }
L_00527dc4_41:
    charge(ctx, 1);
    t7 = sltiu(s0, 5);
    goto L_00527dc8;
L_00527dec:
    charge(ctx, 4);
    t7 = 1;
    t6 = s4 & 0x8;
    if (s7 == 0) s7 = t7;
    if (t6 == 0) {
        // 0x00527e60
        charge(ctx, 10);
        lw(t7, sp, 0x264);
        a2 = s7;
        a1 = 1;
        a3 = s1;
        lw(a0, t7, 0);
        t7 = addiu(t7, 8);
        link(ctx, 0x527E78u);  // $ra first: the delay slot below depends on it
        sw(t7, sp, 0x264);
        call(ctx, gen::fn_fread_0051faa0);
        s5 = addu(s5, v0);
        if (v0 == 0) {
            backedge(ctx);
            goto L_00527cf4;
        }
    L_00527e88:
        charge(ctx, 4);
        lw(t5, sp, 0x268);
        t5 = addiu(t5, 1);
        sw(t5, sp, 0x268);
        backedge(ctx);
        goto L_00527b94;
    }
    // 0x00527dfc
    charge(ctx, 2);
    s0 = 0;
    lw(s2, s1, 4);
    for (;;) {
        // 0x00527e04
        charge(ctx, 3);
        t7 = slt(s2, s7);
        a0 = s1;
        if (t7 == 0) {
            goto L_00527e40;
        }
        // 0x00527e10
        charge(ctx, 8);
        lw(t7, s1, 0);
        s0 = addu(s0, s2);
        s7 = subu(s7, s2);
        t7 = addu(t7, s2);
        link(ctx, 0x527E20u);  // $ra first: the delay slot below depends on it
        sw(t7, s1, 0);
        call(ctx, gen::fn___srefill_00523580);
        if (v0 != 0) {
            break;
        }
        lw(s2, s1, 4);
        backedge(ctx);
    }
    // 0x00527e30
    charge(ctx, 2);
    lw(t5, sp, 0x268);
    if (s0 == 0) {
        backedge(ctx);
        goto L_00527cf8;
    }
L_00527e38:
    charge(ctx, 2);
    s5 = addu(s5, s0);
    backedge(ctx);
    goto L_00527b94;
L_00527e40:
    charge(ctx, 7);
    lw(t6, s1, 0);
    t7 = subu(s2, s7);
    sw(t7, s1, 4);
    s0 = addu(s0, s7);
    t6 = addu(t6, s7);
    sw(t6, s1, 0);
    backedge(ctx);
    goto L_00527e38;
L_00527e98:
    charge(ctx, 4);
    t7 = si(-1);
    t6 = s4 & 0x8;
    if (s7 == 0) s7 = t7;
    if (t6 != 0) {
        // 0x00527ea8
        charge(ctx, 6);
        lw(t4, s1, 0);
        lbu(t7, t4, 0);
        t6 = addu(sp, t7);
        lb(t5, t6, 0);
        s2 = 0;
        if (t5 != 0) {
            // 0x00527ec0
            charge(ctx, 1);
            lw(t6, s1, 4);
            for (;;) {
                // 0x00527ec4
                charge(ctx, 7);
                t7 = addiu(t4, 1);
                sw(t7, s1, 0);
                s2 = addiu(s2, 1);
                t6 = addiu(t6, -1);
                s7 = addiu(s7, -1);
                sw(t6, s1, 4);
                if (s7 == 0) {
                    break;
                }
                // 0x00527ee0
                charge(ctx, 2);
                if (i64(t6) > 0) {
                    lw(t4, s1, 0);
                } else {
                    // 0x00527ee8
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x527EE8u, gen::fn___srefill_00523580);
                    if (v0 != 0) {
                        goto L_00527ef8_59;
                    }
                    lw(t4, s1, 0);
                    goto L_00527f08;
                }
            L_00527f08:
                charge(ctx, 5);
                lbu(t7, t4, 0);
                t6 = addu(sp, t7);
                lb(t5, t6, 0);
                if (t5 == 0) {
                    break;
                }
                lw(t6, s1, 4);
                backedge(ctx);
            }
        }
        // 0x00527f1c
        charge(ctx, 2);
        s5 = addu(s5, s2);
        if (s2 == 0) {
            goto L_00527f24_63;
        }
        backedge(ctx);
        goto L_00527b94;
    }
    // 0x00527f30
    charge(ctx, 10);
    lw(t7, sp, 0x264);
    lw(t4, s1, 0);
    t6 = addiu(t7, 8);
    lw(s6, t7, 0);
    sw(t6, sp, 0x264);
    lbu(t5, t4, 0);
    t7 = addu(sp, t5);
    lb(t6, t7, 0);
    s2 = s6;
    if (t6 != 0) {
        // 0x00527f58
        charge(ctx, 1);
        lw(t7, s1, 4);
        for (;;) {
            // 0x00527f5c
            charge(ctx, 9);
            t5 = addiu(t4, 1);
            s7 = addiu(s7, -1);
            t7 = addiu(t7, -1);
            sw(t7, s1, 4);
            lbu(t6, t4, 0);
            sb(t6, s6, 0);
            sw(t5, s1, 0);
            s6 = addiu(s6, 1);
            if (s7 == 0) {
                goto L_00527fa4;
            }
            // 0x00527f80
            charge(ctx, 3);
            lw(t7, s1, 4);
            if (i64(t7) > 0) {
                lw(t4, s1, 0);
            } else {
                // 0x00527f8c
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x527F8Cu, gen::fn___srefill_00523580);
                if (v0 != 0) {
                    goto L_00527f9c_69;
                }
                lw(t4, s1, 0);
                goto L_00527fc4;
            }
        L_00527fc4:
            charge(ctx, 5);
            lbu(t7, t4, 0);
            t6 = addu(sp, t7);
            lb(t5, t6, 0);
            if (t5 == 0) {
                break;
            }
            lw(t7, s1, 4);
            backedge(ctx);
        }
        // 0x00527fd8
        charge(ctx, 2);
        s2 = subu(s6, s2);
        backedge(ctx);
    L_00527fa8:
        charge(ctx, 2);
        lw(v0, sp, 0x268);
        if (s2 != 0) {
            // 0x00527fb0
            charge(ctx, 5);
            sb(zero, s6, 0);
            lw(t7, sp, 0x268);
            t7 = addiu(t7, 1);
            sw(t7, sp, 0x268);
            backedge(ctx);
        L_00527f00:
            charge(ctx, 2);
            s5 = addu(s5, s2);
            backedge(ctx);
            goto L_00527b94;
        }
        backedge(ctx);
        // 0x00527cc4 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0x290);
        ld(s1, sp, 0x298);
        ld(s2, sp, 0x2A0);
        ld(s3, sp, 0x2A8);
        ld(s4, sp, 0x2B0);
        ld(s5, sp, 0x2B8);
        ld(s6, sp, 0x2C0);
        ld(s7, sp, 0x2C8);
        ld(fp, sp, 0x2D0);
        ld(ra, sp, 0x2D8);
        sp = addiu(sp, 0x2E0);
        return;
    }
L_00527fa4:
    charge(ctx, 1);
    s2 = subu(s6, s2);
    goto L_00527fa8;
L_00527ef8_59:
    charge(ctx, 2);
    lw(t5, sp, 0x268);
    if (s2 != 0) {
        goto L_00527f00;
    }
    backedge(ctx);
    goto L_00527cf8;
L_00527f24_63:
    charge(ctx, 2);
    lw(v0, sp, 0x268);
    backedge(ctx);
    // 0x00527cc4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x290);
    ld(s1, sp, 0x298);
    ld(s2, sp, 0x2A0);
    ld(s3, sp, 0x2A8);
    ld(s4, sp, 0x2B0);
    ld(s5, sp, 0x2B8);
    ld(s6, sp, 0x2C0);
    ld(s7, sp, 0x2C8);
    ld(fp, sp, 0x2D0);
    ld(ra, sp, 0x2D8);
    sp = addiu(sp, 0x2E0);
    return;
L_00527f9c_69:
    charge(ctx, 2);
    lw(t5, sp, 0x268);
    if (s6 != s2) {
        goto L_00527fa4;
    }
    backedge(ctx);
    goto L_00527cf8;
L_00527fe0:
    charge(ctx, 4);
    t7 = si(-1);
    t6 = s4 & 0x8;
    if (s7 == 0) s7 = t7;
    if (t6 == 0) {
        // 0x00528078
        charge(ctx, 14);
        t7 = 0x7C0000;
        lw(t4, s1, 0);
        t3 = addiu(t7, -5688);  // &0x7BE9C8
        lw(t5, sp, 0x264);
        lw(t7, sp, 0x264);
        lbu(t6, t4, 0);
        t7 = addiu(t7, 8);
        lw(s6, t5, 0);
        sw(t7, sp, 0x264);
        t6 = addu(t6, t3);
        lbu(t7, t6, 0);
        t7 = t7 & 0x8;
        s2 = s6;
        if (t7 == 0) {
            // 0x005280b0
            charge(ctx, 2);
            s0 = t3;
            lw(t7, s1, 4);
            for (;;) {
                // 0x005280b8
                charge(ctx, 9);
                t5 = addiu(t4, 1);
                s7 = addiu(s7, -1);
                t7 = addiu(t7, -1);
                sw(t7, s1, 4);
                lbu(t6, t4, 0);
                sb(t6, s6, 0);
                sw(t5, s1, 0);
                s6 = addiu(s6, 1);
                if (s7 == 0) {
                    goto L_00528114;
                }
                // 0x005280dc
                charge(ctx, 3);
                lw(t7, s1, 4);
                if (i64(t7) > 0) {
                    lw(t4, s1, 0);
                } else {
                    // 0x005280e8
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x5280E8u, gen::fn___srefill_00523580);
                    t7 = subu(s6, s2);
                    if (v0 != 0) {
                        break;
                    }
                    // 0x005280f8
                    charge(ctx, 1);
                    lw(t4, s1, 0);
                    goto L_005280fc;
                }
            L_005280fc:
                charge(ctx, 6);
                lbu(t7, t4, 0);
                t7 = addu(t7, s0);
                lbu(t6, t7, 0);
                t6 = t6 & 0x8;
                if (t6 != 0) {
                    goto L_00528114;
                }
                lw(t7, s1, 4);
                backedge(ctx);
            }
            goto L_00528118;
        }
    L_00528114:
        charge(ctx, 1);
        t7 = subu(s6, s2);
    L_00528118:
        charge(ctx, 3);
        sb(zero, s6, 0);
        s5 = addu(s5, t7);
        backedge(ctx);
        goto L_00527e88;
    }
    // 0x00527ff0
    charge(ctx, 9);
    t7 = 0x7C0000;
    lw(t5, s1, 0);
    t4 = addiu(t7, -5688);  // &0x7BE9C8
    lbu(t7, t5, 0);
    t7 = addu(t7, t4);
    lbu(t6, t7, 0);
    t6 = t6 & 0x8;
    s2 = 0;
    if (t6 != 0) {
        backedge(ctx);
        goto L_00527f00;
    }
    // 0x00528014
    charge(ctx, 2);
    s0 = t4;
    lw(t6, s1, 4);
    for (;;) {
        // 0x0052801c
        charge(ctx, 7);
        t7 = addiu(t5, 1);
        sw(t7, s1, 0);
        s2 = addiu(s2, 1);
        t6 = addiu(t6, -1);
        s7 = addiu(s7, -1);
        sw(t6, s1, 4);
        if (s7 == 0) {
            backedge(ctx);
            goto L_00527f00;
        }
        // 0x00528038
        charge(ctx, 2);
        if (i64(t6) > 0) {
            lw(t5, s1, 0);
        } else {
            // 0x00528040
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x528040u, gen::fn___srefill_00523580);
            if (v0 == 0) {
                // 0x00528050
                charge(ctx, 1);
                lw(t5, s1, 0);
                goto L_00528054;
            }
            s5 = addu(s5, s2);
            backedge(ctx);
            break;
        }
    L_00528054:
        charge(ctx, 6);
        lbu(t7, t5, 0);
        t7 = addu(t7, s0);
        lbu(t6, t7, 0);
        t6 = t6 & 0x8;
        if (t6 != 0) {
            goto L_0052806c_83;
        }
        lw(t6, s1, 4);
        backedge(ctx);
    }
    goto L_00527b94;
L_0052806c_83:
    charge(ctx, 2);
    s5 = addu(s5, s2);
    backedge(ctx);
    goto L_00527b94;
L_00528124:
    charge(ctx, 8);
    s7 = addiu(s7, -1);
    t7 = 348;
    t6 = sltiu(s7, 349);
    s4 = s4 | 0x2C0;
    if (t6 == 0) s7 = t7;
    s7 = addiu(s7, 1);
    s6 = addiu(sp, 0x100);
    if (s7 != 0) {
        // 0x00528144
        charge(ctx, 1);
        lw(t7, s1, 0);
        for (;;) {
            // 0x00528148
            charge(ctx, 5);
            lbu(s0, t7, 0);
            t6 = addiu(s0, -43);
            t7 = sltiu(t6, 78);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sll(t6, 2);
            if (cc) {
                goto L_005281c8;
            }
            // 0x0052815c
            charge(ctx, 6);
            t6 = 0x7C0000;
            t6 = addiu(t6, -3624);  // &0x7BF1D8
            t7 = addu(t7, t6);
            lw(t5, t7, 0);
            switch (t5.u()) {
            case 0x528174u:  // table[5]
                // 0x00528174
                charge(ctx, 2);
                t7 = s4 & 0x200;
                if (fp == 0) {
                    // 0x0052817c
                    charge(ctx, 3);
                    fp = 0x8;
                    s4 = s4 | 0x100;
                    t7 = s4 & 0x200;
                }
                // 0x00528188
                charge(ctx, 2);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = si(-449);
                if (!cc) {
                    // 0x00528190
                    charge(ctx, 1);
                    t7 = si(-705);
                }
            L_00528194:
                charge(ctx, 1);
                s4 = s4 & t7;
            L_00528198:
                charge(ctx, 6);
                sb(s0, s6, 0);
                lw(t7, s1, 4);
                s6 = addiu(s6, 1);
                t7 = addiu(t7, -1);
                sw(t7, s1, 4);
                if (i64(t7) > 0) {
                    // 0x005281b0
                    charge(ctx, 4);
                    lw(t7, s1, 0);
                    t7 = addiu(t7, 1);
                    sw(t7, s1, 0);
                    s7 = addiu(s7, -1);
                    goto L_005281c0;
                }
                // 0x005282f4
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x5282F4u, gen::fn___srefill_00523580);
                t7 = s4 & 0x80;
                if (v0 == 0) {
                    // 0x00528304
                    charge(ctx, 2);
                    s7 = addiu(s7, -1);
                    backedge(ctx);
                L_005281c0:
                    charge(ctx, 2);
                    if (s7 == 0) {
                        goto L_005281c8;
                    }
                    lw(t7, s1, 0);
                    backedge(ctx);
                    continue;
                }
                backedge(ctx);
                break;
            case 0x5281C8u:  // table[1, 3, 4, 15, 16, 17, 18, 19, 20, 21, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76]
                goto L_005281c8;
            case 0x52830Cu:  // table[0, 2]
                // 0x0052830c
                charge(ctx, 3);
                t7 = s4 & 0x40;
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = si(-65);
                if (cc) {
                    backedge(ctx);
                    goto L_005281c8;
                }
                // 0x00528318
                charge(ctx, 2);
                s4 = s4 & t7;
                backedge(ctx);
                goto L_00528198;
            case 0x528320u:  // table[6, 7, 8, 9, 10, 11, 12]
                // 0x00528320
                charge(ctx, 8);
                t6 = 0x7C0000;
                t7 = sll(fp, 1);
                t6 = addiu(t6, -4176);  // "\n"
                t5 = si(-449);
                t7 = addu(t7, t6);
                s4 = s4 & t5;
                lh(fp, t7, 0);
                backedge(ctx);
                goto L_00528198;
            case 0x528340u:  // table[13, 14]
                // 0x00528340
                charge(ctx, 8);
                t6 = 0x7C0000;
                t7 = sll(fp, 1);
                t6 = addiu(t6, -4176);  // "\n"
                t7 = addu(t7, t6);
                lh(fp, t7, 0);
                t6 = slti(fp, 9);
                t7 = si(-449);
                if (t6 != 0) {
                    backedge(ctx);
                    goto L_005281c8;
                }
                // 0x00528360
                charge(ctx, 2);
                s4 = s4 & t7;
                backedge(ctx);
                goto L_00528198;
            case 0x528368u:  // table[22, 23, 24, 25, 26, 27, 54, 55, 56, 57, 58, 59]
                // 0x00528368
                charge(ctx, 3);
                t7 = slti(fp, 11);
                cc = t7 != 0;  // the condition, before the delay slot changes it
                t7 = si(-449);
                if (cc) {
                    backedge(ctx);
                    goto L_005281c8;
                }
                // 0x00528374
                charge(ctx, 2);
                s4 = s4 & t7;
                backedge(ctx);
                goto L_00528198;
            case 0x528380u:  // table[45, 77]
                // 0x00528380
                charge(ctx, 3);
                t7 = s4 & 0x100;
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = addiu(sp, 0x101);
                if (cc) {
                    backedge(ctx);
                    goto L_005281c8;
                }
                // 0x0052838c
                charge(ctx, 2);
                cc = s6 != t7;  // the condition, before the delay slot changes it
                t7 = si(-257);
                if (cc) {
                    backedge(ctx);
                    goto L_005281c8;
                }
                // 0x00528394
                charge(ctx, 2);
                fp = 0x10;
                backedge(ctx);
                goto L_00528194;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, t5.u());
                return;
            }
            break;
        }
        goto L_005281cc;
    }
L_005281c8:
    charge(ctx, 1);
    t7 = s4 & 0x80;
L_005281cc:
    charge(ctx, 2);
    t6 = addiu(sp, 0x100);
    if (t7 != 0) {
        goto L_005281d4_107;
    }
    // 0x005281f8
    charge(ctx, 4);
    lb(s0, s6, -1);
    t7 = 120;
    cc = s0 == t7;  // the condition, before the delay slot changes it
    t7 = 88;
    if (!cc) {
        // 0x00528208
        charge(ctx, 2);
        cc = s0 != t7;  // the condition, before the delay slot changes it
        t7 = s4 & 0x8;
        if (!cc) {
            goto L_00528210;
        }
        goto L_00528224;
    }
L_00528210:
    charge(ctx, 5);
    a0 = s0;
    s6 = addiu(s6, -1);
    a1 = s1;
    jal(ctx, 0x528218u, gen::fn_ungetc_00525fb0);
    t7 = s4 & 0x8;
L_00528224:
    charge(ctx, 2);
    t5 = addiu(sp, 0x100);
    if (t7 == 0) {
        // 0x0052822c
        charge(ctx, 10);
        sb(zero, s6, 0);
        a1 = addiu(sp, 0x100);
        a2 = 0;
        a3 = fp;
        lw(t7, sp, 0x26C);
        jt = t7.u();  // the target, read before the delay slot
        link(ctx, 0x528240u);  // $ra = the return address
        lw(a0, sp, 0x260);
        call_ptr(ctx, jt);
        t7 = s4 & 0x10;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        lw(t7, sp, 0x264);
        if (cc) {
            // 0x00528288
            charge(ctx, 3);
            t7 = s4 & 0x4;
            cc = t7 == 0;  // the condition, before the delay slot changes it
            lw(t7, sp, 0x264);
            if (cc) {
                // 0x005282b0
                charge(ctx, 3);
                t7 = s4 & 0x1;
                cc = t7 == 0;  // the condition, before the delay slot changes it
                lw(t7, sp, 0x264);
                if (cc) {
                    // 0x005282d4
                    charge(ctx, 8);
                    t6 = dsll32(v0, 0);
                    lw(t5, sp, 0x264);
                    t6 = dsra32(t6, 0);
                    lw(t7, t7, 0);
                    t5 = addiu(t5, 8);
                    sw(t5, sp, 0x264);
                    sw(t6, t7, 0);
                    backedge(ctx);
                } else {
                    // 0x005282bc
                    charge(ctx, 6);
                    lw(t6, sp, 0x264);
                    lw(t7, t7, 0);
                    t6 = addiu(t6, 8);
                    sw(t6, sp, 0x264);
                    sd(v0, t7, 0);
                    backedge(ctx);
                }
            } else {
                // 0x00528294
                charge(ctx, 7);
                t6 = v0 & 0xFFFF;
                lw(t5, sp, 0x264);
                lw(t7, t7, 0);
                t5 = addiu(t5, 8);
                sw(t5, sp, 0x264);
                sh(t6, t7, 0);
                backedge(ctx);
            }
        } else {
            // 0x00528254
            charge(ctx, 6);
            t5 = dsll32(v0, 0);
            t5 = dsra32(t5, 0);
            lw(t6, t7, 0);
            t7 = addiu(t7, 8);
            sw(t5, t6, 0);
            sw(t7, sp, 0x264);
        }
        // 0x0052826c
        charge(ctx, 4);
        lw(t6, sp, 0x268);
        t6 = addiu(t6, 1);
        sw(t6, sp, 0x268);
        t5 = addiu(sp, 0x100);
    }
    // 0x0052827c
    charge(ctx, 3);
    t7 = subu(s6, t5);
    s5 = addu(s5, t7);
    backedge(ctx);
    goto L_00527b94;
L_005281d4_107:
    charge(ctx, 3);
    t7 = sltu(t6, s6);
    if (t7 == 0) {
        lw(v0, sp, 0x268);
        backedge(ctx);
    } else {
        // 0x005281e0
        charge(ctx, 5);
        lb(a0, s6, -1);
        a1 = s1;
        jal(ctx, 0x5281E4u, gen::fn_ungetc_00525fb0);
        lw(v0, sp, 0x268);
        backedge(ctx);
    }
    // 0x00527cc4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x290);
    ld(s1, sp, 0x298);
    ld(s2, sp, 0x2A0);
    ld(s3, sp, 0x2A8);
    ld(s4, sp, 0x2B0);
    ld(s5, sp, 0x2B8);
    ld(s6, sp, 0x2C0);
    ld(s7, sp, 0x2C8);
    ld(fp, sp, 0x2D0);
    ld(ra, sp, 0x2D8);
    sp = addiu(sp, 0x2E0);
    return;
L_00528458_148:
    charge(ctx, 1);
    t7 = sltu(t5, s6);
    for (;;) {
        // 0x0052845c
        charge(ctx, 2);
        s6 = addiu(s6, -1);
        if (t7 != 0) {
            // 0x00528464
            charge(ctx, 6);
            a1 = s1;
            link(ctx, 0x528468u);  // $ra first: the delay slot below depends on it
            lb(a0, s6, 0);
            call(ctx, gen::fn_ungetc_00525fb0);
            t6 = addiu(sp, 0x100);
            t7 = sltu(t6, s6);
            backedge(ctx);
            continue;
        }
        backedge(ctx);
        break;
    }
    goto L_00527cc0;
L_005284cc_156:
    charge(ctx, 4);
    t6 = s4 & 0x300;
    t7 = 512;
    sb(zero, s6, 0);
    if (t6 == t7) {
        // 0x005284dc
        charge(ctx, 5);
        ld(t7, sp, 0x270);
        sw(s6, sp, 0x280);
        s2 = s2 - t7;
        sd(s2, sp, 0x278);
        a2 = 0 - s2;
        goto L_005284f0;
    }
    // 0x00528598
    charge(ctx, 3);
    ld(t5, sp, 0x278);
    lw(t6, sp, 0x280);
    if (t5 == 0) {
        backedge(ctx);
    } else {
        // 0x005285a4
        charge(ctx, 8);
        a2 = 0;
        lw(a0, sp, 0x260);
        a3 = 10;
        a1 = addiu(t6, 1);
        jal(ctx, 0x5285B0u, gen::fn__strtol_r_00525a10);
        ld(t7, sp, 0x278);
        a2 = v0 - t7;
        backedge(ctx);
    L_005284f0:
        charge(ctx, 3);
        ld(t5, sp, 0x278);
        lw(t6, sp, 0x280);
        if (t5 != 0) {
            // 0x005284fc
            charge(ctx, 10);
            t7 = addiu(sp, 0x249);
            lw(t5, sp, 0x280);
            a1 = 0x7C0000;
            t7 = sltu(t6, t7);
            a1 = addiu(a1, -4136);  // "e%ld"
            t6 = addiu(sp, 0x248);
            if (t7 == 0) t5 = t6;
            sw(t5, sp, 0x280);
            link(ctx, 0x52851Cu);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x280);
            call(ctx, gen::fn_sprintf_00523ac8);
        }
    }
    // 0x00528524
    charge(ctx, 7);
    lw(a0, sp, 0x260);
    a1 = addiu(sp, 0x100);
    a2 = 0;
    jal(ctx, 0x52852Cu, gen::fn__strtod_r_00524aa8);
    t7 = s4 & 0x1;
    cc = t7 == 0;  // the condition, before the delay slot changes it
    lw(t7, sp, 0x264);
    if (!cc) {
        // 0x00528540
        charge(ctx, 3);
        lw(t6, t7, 0);
        t7 = addiu(t7, 8);
        sw(t7, sp, 0x264);
        goto L_0052854c;
    }
    // 0x00528560
    charge(ctx, 3);
    t7 = s4 & 0x2;
    cc = t7 == 0;  // the condition, before the delay slot changes it
    lw(t7, sp, 0x264);
    if (cc) {
        // 0x0052857c
        charge(ctx, 7);
        a0 = v0;
        t6 = addiu(t7, 8);
        lw(s0, t7, 0);
        link(ctx, 0x528588u);  // $ra first: the delay slot below depends on it
        sw(t6, sp, 0x264);
        call(ctx, gen::fn_dptofp_005318a0);
        swc1(f0, s0, 0);
        backedge(ctx);
    } else {
        // 0x0052856c
        charge(ctx, 4);
        t5 = addiu(t7, 8);
        lw(t6, t7, 0);
        sw(t5, sp, 0x264);
        backedge(ctx);
    L_0052854c:
        charge(ctx, 1);
        sd(v0, t6, 0);
    }
    // 0x00528550
    charge(ctx, 4);
    lw(t7, sp, 0x268);
    t7 = addiu(t7, 1);
    sw(t7, sp, 0x268);
    backedge(ctx);
    goto L_00527b94;
L_005285d4_170:
    charge(ctx, 2);
    backedge(ctx);
    goto L_00528438;
L_00528690:
    charge(ctx, 1);
    s4 = s4 | 0x1;
L_00528694:
    charge(ctx, 4);
    t7 = 0x520000;
    s0 = 3;
    t7 = addiu(t7, 23680);  // &_strtoul_r
    fp = 0x8;
L_005286a4:
    charge(ctx, 2);
    sw(t7, sp, 0x26C);
    backedge(ctx);
    goto L_00527d40;
L_005286ac:
    charge(ctx, 7);
    a1 = s3;
    a0 = sp;
    jal(ctx, 0x5286B0u, gen::fn___sccl_005287d8);
    s4 = s4 | 0x20;
    s3 = v0;
    s0 = 1;
    backedge(ctx);
    goto L_00527d40;
L_005286c8:
    charge(ctx, 3);
    s4 = s4 | 0x20;
    s0 = 0;
    backedge(ctx);
    goto L_00527d40;
L_005286d4:
    charge(ctx, 2);
    s0 = 4;
    backedge(ctx);
    goto L_00527d40;
L_005286e4:
    charge(ctx, 5);
    t7 = 0x520000;
    s0 = 3;
    t7 = addiu(t7, 23056);  // &_strtol_r
    fp = 0;
    backedge(ctx);
    goto L_005286a4;
L_0052870c_197:
    charge(ctx, 3);
    t7 = s4 & 0x4;
    cc = t7 == 0;  // the condition, before the delay slot changes it
    lw(t7, sp, 0x264);
    if (cc) {
        // 0x00528730
        charge(ctx, 3);
        t7 = s4 & 0x1;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        lw(t7, sp, 0x264);
        if (cc) {
            // 0x00528758
            charge(ctx, 6);
            lw(t6, sp, 0x264);
            lw(t7, t7, 0);
            t6 = addiu(t6, 8);
            sw(t6, sp, 0x264);
            sw(s5, t7, 0);
            backedge(ctx);
        } else {
            // 0x0052873c
            charge(ctx, 7);
            t6 = s5;
            lw(t5, sp, 0x264);
            lw(t7, t7, 0);
            t5 = addiu(t5, 8);
            sw(t5, sp, 0x264);
            sd(t6, t7, 0);
            backedge(ctx);
        }
    } else {
        // 0x00528718
        charge(ctx, 6);
        lw(t5, sp, 0x264);
        lw(t7, t7, 0);
        t5 = addiu(t5, 8);
        sw(t5, sp, 0x264);
        sh(s5, t7, 0);
        backedge(ctx);
    }
    goto L_00527b94;
L_00528770:
    charge(ctx, 1);
    s4 = s4 | 0x110;
L_00528774:
    charge(ctx, 5);
    t7 = 0x520000;
    s0 = 3;
    t7 = addiu(t7, 23680);  // &_strtoul_r
    fp = 0x10;
    backedge(ctx);
    goto L_005286a4;
L_00528788:
    charge(ctx, 2);
    s0 = 2;
    backedge(ctx);
    goto L_00527d40;
L_00528790:
    charge(ctx, 4);
    t7 = 0x520000;
    s0 = 3;
    t7 = addiu(t7, 23680);  // &_strtoul_r
    backedge(ctx);
    goto L_00527d38;
L_005287a0:
    charge(ctx, 12);
    t7 = 0x520000;
    t6 = 0x7C0000;
    t7 = addiu(t7, 23056);  // &_strtol_r
    t6 = addiu(t6, -5688);  // &0x7BE9C8
    sw(t7, sp, 0x26C);
    t6 = addu(s0, t6);
    fp = 0xA;
    s0 = 3;
    lbu(t7, t6, 0);
    t7 = t7 & 0x1;
    s4 = s4 | t7;
    backedge(ctx);
    goto L_00527d40;
L_005287d0:
    charge(ctx, 2);
    s4 = s4 | 0x100;
    backedge(ctx);
    goto L_00528774;
}

// 0x00528920 _vsprintf_r -- 76 bytes; frame 0x70: ra sp+0x60
// vsprintf_r(reent, buf, fmt, ap): the string FILE of sprintf_r (flags 0x208, room 0x7FFFFFFF) and vfprintf entered
// past its reent setup (loc_5262B0), then the terminating NUL.
void _vsprintf_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00528920
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    t6 = 0x7FFF0000;
    t5 = a1;
    sw(a1, sp, 0x10);
    t6 = t6 | 0xFFFF;
    sd(ra, sp, 0x60);
    t7 = 520;
    sw(t6, sp, 0x14);
    sh(t7, sp, 0xC);
    a1 = sp;
    sw(a0, sp, 0x54);
    sw(t5, sp, 0x0);
    link(ctx, 0x528950u);
    sw(t6, sp, 0x8);
    gen::fn_vfprintf_00526238_at_005262b0(ctx);
    lw(t7, sp, 0x0);
    ld(ra, sp, 0x60);
    sb(zero, t7, 0);
    sp = addiu(sp, 0x70);
}

// 0x005289D0 __swsetup -- 272 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// newlib's __swsetup(fp): makes a FILE writable before the first write -- __sinit for a fresh _reent; a FILE that is
// neither writing (8) nor read-write (0x10) is refused (-1); a read-write FILE that was reading drops its ungetc buffer
// (freed with _free_r unless it is the built-in one) and read count, clears reading / EOF (~0x24) and rewinds to the
// buffer; flags | 8 (writing); a FILE without a buffer gets one (__smakebuf = _fork_r); then the write room (+8) is 0
// for line-buffered FILEs (with -bufsize in +24) and unbuffered ones, else the buffer size. Returns 0.
void __swsetup(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005289d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    lw(a0, a0, 84);
    if (a0 != 0) {
        lw(t7, a0, 56);
    } else {
        // 0x005289ec
        charge(ctx, 5);
        t7 = 0x780000;
        lw(t6, t7, 12080);  // 0x782F30
        sw(t6, s0, libc::file::kData);
        a0 = t6;
        lw(t7, a0, 56);
    }
    // 0x00528a00
    charge(ctx, 2);
    if (t7 != 0) {
        lhu(t6, s0, libc::file::kFlags);
    } else {
        // 0x00528a08
        charge(ctx, 3);
        jal(ctx, 0x528A08u, gen::fn___sinit_0051fa20);
        lhu(t6, s0, libc::file::kFlags);
    }
    // 0x00528a14
    charge(ctx, 3);
    t7 = t6 & 0x8;
    if (t7 != 0) {
        lw(t5, s0, libc::file::kBufBase);
    } else {
        // 0x00528a20
        charge(ctx, 3);
        t7 = t6 & 0x10;
        v0 = si(-1);
        if (t7 != 0) {
            // 0x00528a2c
            charge(ctx, 3);
            t7 = t6 & 0x4;
            if (t7 == 0) {
                lw(t5, s0, libc::file::kBufBase);
            } else {
                // 0x00528a38
                charge(ctx, 3);
                lw(a1, s0, libs3::file::kUbBase);
                t7 = addiu(s0, 64);
                if (a1 != 0) {
                    // 0x00528a44
                    charge(ctx, 2);
                    if (a1 == t7) {
                        sw(zero, s0, libs3::file::kUbBase);
                    } else {
                        // 0x00528a4c
                        charge(ctx, 4);
                        link(ctx, 0x528A4Cu);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, libc::file::kData);
                        call(ctx, gen::fn__free_r_0051fbb0);
                        lhu(t6, s0, libc::file::kFlags);
                        sw(zero, s0, libs3::file::kUbBase);
                    }
                }
                // 0x00528a5c
                charge(ctx, 7);
                lw(t5, s0, libc::file::kBufBase);
                t7 = si(-37);
                t7 = t6 & t7;
                sw(zero, s0, libc::file::kR);
                sh(t7, s0, libc::file::kFlags);
                t6 = t7;
                sw(t5, s0, 0);
            }
            // 0x00528a78
            charge(ctx, 2);
            t7 = t6 | 0x8;
            sh(t7, s0, libc::file::kFlags);
            goto L_00528a80;
        }
        // 0x00528abc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00528a80:
    charge(ctx, 2);
    if (t5 != 0) {
        lhu(t6, s0, libc::file::kFlags);
    } else {
        // 0x00528a88
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x528A88u, gen::fn__fork_r_005205d8);
        lhu(t6, s0, libc::file::kFlags);
    }
    // 0x00528a94
    charge(ctx, 5);
    t7 = t6 & 0x1;
    t7 = sll(t7, 16);
    t7 = sra(t7, 16);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = t6 & 0x2;
    if (cc) {
        // 0x00528acc
        charge(ctx, 2);
        t6 = 0;
        if (t7 == 0) {
            // 0x00528ad4
            charge(ctx, 1);
            lw(t6, s0, libc::file::kBufSize);
        }
        // 0x00528ad8
        charge(ctx, 2);
        sw(t6, s0, libc::file::kW);
        backedge(ctx);
    } else {
        // 0x00528aa8
        charge(ctx, 4);
        lw(t7, s0, libc::file::kBufSize);
        sw(zero, s0, libc::file::kW);
        t7 = subu(0, t7);
        sw(t7, s0, libc::file::kLbfSize);
    }
    // 0x00528ab8
    charge(ctx, 1);
    v0 = 0;
    // 0x00528abc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
