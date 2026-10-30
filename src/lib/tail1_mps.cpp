// Slice tail1: CRI MPS (the MPEG program-stream demultiplexer) and the MPV start-code helpers.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions only (no CRI material was
// opened). Pair tests: tests/game/test_tail1.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/tail1.h"

namespace p3fes::recomp_gen {
void fn___env_unlock_3_00575950(p3fes::EEContext&);
void fn___env_unlock_4_005777f0(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_17_00577a28(p3fes::EEContext&);
void fn_sub_577B40_00577b40(p3fes::EEContext&);
void fn_sub_577BE0_00577be0(p3fes::EEContext&);
void fn_sub_577C30_00577c30(p3fes::EEContext&);
void fn_sub_577C68_00577c68(p3fes::EEContext&);
void fn_sub_577D00_00577d00(p3fes::EEContext&);
void fn_sub_577D10_00577d10(p3fes::EEContext&);
void fn_sub_577DB0_00577db0(p3fes::EEContext&);
void fn_sub_577E10_00577e10(p3fes::EEContext&);
void fn_sub_577F08_00577f08(p3fes::EEContext&);
void fn_sub_577F20_00577f20(p3fes::EEContext&);
void fn_sub_577F48_00577f48(p3fes::EEContext&);
void fn_sub_577F78_00577f78(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578060_00578060(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
void fn_sub_578D98_00578d98(p3fes::EEContext&);
void fn_sub_578E08_00578e08(p3fes::EEContext&);
void fn_sub_578E88_00578e88(p3fes::EEContext&);
void fn_sub_578ED8_00578ed8(p3fes::EEContext&);
void fn_sub_578FC0_00578fc0(p3fes::EEContext&);
void fn_sub_579070_00579070(p3fes::EEContext&);
void fn_sub_579078_00579078(p3fes::EEContext&);
void fn_sub_579138_00579138(p3fes::EEContext&);
void fn_sub_579240_00579240(p3fes::EEContext&);
void fn_sub_5792A0_005792a0(p3fes::EEContext&);
void fn_sub_579368_00579368(p3fes::EEContext&);
void fn_sub_5793E0_005793e0(p3fes::EEContext&);
void fn_sub_5793E8_005793e8(p3fes::EEContext&);
void fn_sub_579410_00579410(p3fes::EEContext&);
void fn_sub_579428_00579428(p3fes::EEContext&);
void fn_sub_579660_00579660(p3fes::EEContext&);
void fn_sub_579770_00579770(p3fes::EEContext&);
void fn_sub_57B7F0_0057b7f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tail1;  // the named offsets of p3fes/game/tail1.h
namespace gen = ::p3fes::recomp_gen;

// 0x00575950 __env_unlock_3 -- 8 bytes; leaf frame (no stack)
// [mpsFinishHookA] An empty function (jr $ra / nop). The FLIRT name is a false match (the same few instructions as the
// SDK function; this is CRI code). Byte-identical to nullsub_1 0x1007F0, which font2 already replaced: same contract,
// same pair tests. MPS calls it as the last step of its finish (sub_577B40).
void __env_unlock_3(EEContext& ctx) {
    using namespace hg;
    // 0x00575950
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005777F0 __env_unlock_4 -- 8 bytes; leaf frame (no stack)
// [mpsFinishHookB] An empty function (jr $ra / nop). The FLIRT name is a false match (the same few instructions as the
// SDK function; this is CRI code). Byte-identical to nullsub_1 0x1007F0, which font2 already replaced: same contract,
// same pair tests. MPS calls it after the first hook (sub_577B40 tail-calls it).
void __env_unlock_4(EEContext& ctx) {
    using namespace hg;
    // 0x005777f0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00577A28 sceLibgcc32GetErxEntries_17 -- 12 bytes; leaf frame (no stack)
// [mpsGetVersionStr] Returns the module's version banner string in $v0 (the 12-byte "return a constant address" shape).
// The FLIRT name is a false match (the same few instructions as the SDK function; this is CRI code). MPS: "CRI
// MPS/PS2EE Ver.1.924".
void sceLibgcc32GetErxEntries_17(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00577a28
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 31160);  // "\nCRI MPS/PS2EE Ver.1.924 Build:Mar  1 2005 10:53:57\n"
}

// 0x00577B40 sub_577B40 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpsFinish] MPS finish: walks the handle pool (*0x7B2998: count +12, 256-byte handles from +16) and destroys every
// handle in use (state != 1) through sub_577F78, then runs the two (empty) finish hooks, the second as a tail call.
void sub_577B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577b40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7B0000;
    lw(v1, v0, 10648);  // 0x7B2998 = mps::kWorkSlot: the work block
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, v1, mps::kWorkCount);
    a0 = addiu(v1, mps::kWorkHandles);
    if (i64(v0) > 0) {
        // 0x00577b68
        charge(ctx, 4);
        s0 = a0;
        s1 = v0;
        s2 = 1;
        for (;;) {
            // 0x00577b78
            charge(ctx, 3);
            lw(v0, s0, mps::kHandleState);
            if (v0 == s2) {
                s1 = addiu(s1, -1);
            } else {
                // 0x00577b84
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x577B84u, gen::fn_sub_577F78_00577f78);
                s1 = addiu(s1, -1);
            }
            // 0x00577b90
            charge(ctx, 2);
            s0 = addiu(s0, mps::kHandleStride);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00577b98
    charge(ctx, 8);
    jal(ctx, 0x577B98u, gen::fn___env_unlock_3_00575950);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn___env_unlock_4_005777f0(ctx);  // tail call
}

// 0x00577BE0 sub_577BE0 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mpsSetError] MPS raise(handle, code): the handle's error record (+4) or, for a null handle, the global one (the work
// block's first 12 bytes), through sub_577C30; returns the code.
void sub_577BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577be0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    a0 = addiu(v0, mps::kHandleErr);
    if (v0 != 0) {
        // 0x00577c10
        charge(ctx, 3);
        jal(ctx, 0x577C10u, gen::fn_sub_577C30_00577c30);
        v0 = s0;
    } else {
        // 0x00577bfc
        charge(ctx, 5);
        v0 = 0x7B0000;
        link(ctx, 0x577C00u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 10648);
        call(ctx, gen::fn_sub_577C30_00577c30);
        v0 = s0;
    }
    // 0x00577c1c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00577C30 sub_577C30 -- 52 bytes; frame 0x10: ra sp+0x0
// [mpsCallErrFn] Error-record call (shared shape, see tail1::err): record.code = code; when code != 0 and record.fn is
// set, record.fn(record.arg) through jalr (a tail call: the callback returns to our caller).
void sub_577C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00577c30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    sw(v0, a0, err::kCode);
    if (v0 != 0) {
        // 0x00577c44
        charge(ctx, 3);
        lw(v0, a0, err::kFn);
        if (v0 != 0) {
            // 0x00577c50
            charge(ctx, 2);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x577C50u);  // $ra = the return address
            lw(a0, a0, err::kArg);
            call_ptr(ctx, jt);
            goto L_00577c58;
        }
        ld(ra, sp, 0x0);
        // 0x00577c5c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00577c58:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x00577c5c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00577C68 sub_577C68 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpsEntryErrFunc] MPS set the error callback (handle, fn, arg): a bad handle raises 0xFF020101 on the global record;
// a null handle sets the global record, else the handle's (+4). Returns 0 (or the raised code).
void sub_577C68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577c68
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
        // 0x00577c8c
        charge(ctx, 5);
        v0 = 0x7B0000;
        link(ctx, 0x577C90u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 10648);
        call(ctx, gen::fn_sub_577D00_00577d00);
        ld(s0, sp, 0x0);
        // 0x00577ce4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00577ca0
    charge(ctx, 5);
    jal(ctx, 0x577CA0u, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    if (v0 != 0) {
        // 0x00577cb4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x101;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x00577cd0
    charge(ctx, 5);
    a0 = addiu(s0, mps::kHandleErr);
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x577CD8u, gen::fn_sub_577D00_00577d00);
    ld(s0, sp, 0x0);
    // 0x00577ce4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00577D00 sub_577D00 -- 12 bytes; leaf frame (no stack)
// [mpsSetErrRec] Stores {fn, arg} into an error record (fn at +0, arg at +4; the code stays).
void sub_577D00(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00577d00
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, err::kArg);
    sw(a1, a0, err::kFn);
}

// 0x00577D10 sub_577D10 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsGetErrInf] MPS get the error record (handle, out): copies {fn, arg, code} (12 bytes) of the handle (+4) or of the
// global record; a bad handle raises 0xFF020102.
void sub_577D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577d10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x00577d2c
        charge(ctx, 9);
        v0 = 0x7B0000;
        lw(v1, v0, 10648);  // 0x7B2998
        ldl(v0, v1, 7);
        ldr(v0, v1, 0);
        lw(a0, v1, 8);
        sdl(v0, s1, 7);
        sdr(v0, s1, 0);
        sw(a0, s1, 8);
        // 0x00577d98 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        v0 = 0;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00577d50
    charge(ctx, 5);
    jal(ctx, 0x577D50u, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    if (v0 != 0) {
        // 0x00577d64
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x102;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x00577d80
    charge(ctx, 6);
    ldl(v0, s0, 11);
    ldr(v0, s0, 4);
    lw(v1, s0, 12);
    sdl(v0, s1, 7);
    sdr(v0, s1, 0);
    sw(v1, s1, 8);
    // 0x00577d98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00577DB0 sub_577DB0 -- 36 bytes; leaf frame (no stack)
// [mpsCheckHandle] MPS handle check: remembers the handle in 0x99B2B4; returns 0 for a non-null handle in use (state !=
// 1), -1 otherwise.
void sub_577DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00577db0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    sw(a0, v0, -19788);  // 0x99B2B4
    v0 = si(-1);
    if (a0 != 0) {
        // 0x00577dc0
        charge(ctx, 3);
        lw(v1, a0, mps::kHandleState);
        v1 = v1 ^ 0x1;
        if (v1 != 0) v0 = 0;
    }
    // 0x00577dcc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00577E10 sub_577E10 -- 88 bytes; leaf frame (no stack)
// [mpsSearchFreeHandle] MPS find a free handle: the first pool entry whose state is 1, or 0 when all are in use.
void sub_577E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00577e10
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    a2 = 0;
    lw(v0, v1, 10648);  // 0x7B2998
    lw(a1, v0, mps::kWorkCount);
    v0 = addiu(v0, mps::kWorkHandles);
    if (i64(a1) > 0) {
        // 0x00577e28
        charge(ctx, 4);
        a0 = v0;
        a3 = 1;
        lw(v1, a0, 0);
        for (;;) {
            // 0x00577e38
            charge(ctx, 3);
            v0 = a0;
            a0 = addiu(a0, mps::kHandleStride);
            if (v1 == a3) {
                break;
            }
            // 0x00577e44
            charge(ctx, 6);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_00577e5c;
            }
            lw(v1, a0, 0);
            backedge(ctx);
        }
        // 0x00577e60 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00577e5c:
    charge(ctx, 1);
    v0 = 0;
    // 0x00577e60 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00577F08 sub_577F08 -- 24 bytes; leaf frame (no stack)
// [mpsResetRec16] Sets a 16-byte record to all ones (sd -1 at +0, sw -1 at +8 / +12); returns -1.
void sub_577F08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00577f08
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = si(-1);
    v0 = si(-1);
    sw(v1, a0, 12);
    sd(v0, a0, 0);
    sw(v1, a0, 8);
}

// 0x00577F20 sub_577F20 -- 40 bytes; leaf frame (no stack)
// [mpsResetRec32] Sets eight words (+0..+28) to -1; returns -1.
void sub_577F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00577f20
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = si(-1);
    sw(v0, a0, 28);
    sw(v0, a0, 0);
    sw(v0, a0, 4);
    sw(v0, a0, 8);
    sw(v0, a0, 12);
    sw(v0, a0, 16);
    sw(v0, a0, 20);
    sw(v0, a0, 24);
}

// 0x00577F48 sub_577F48 -- 44 bytes; leaf frame (no stack)
// [mpsResetRec40] Sets a 40-byte record to all ones (two sd, six sw); returns -1.
void sub_577F48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00577f48
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = si(-1);
    v1 = si(-1);
    sw(v0, a0, 36);
    sd(v1, a0, 8);
    sd(v1, a0, 0);
    sw(v0, a0, 16);
    sw(v0, a0, 20);
    sw(v0, a0, 24);
    sw(v0, a0, 28);
    sw(v0, a0, 32);
}

// 0x00577F78 sub_577F78 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mpsDestroy] MPS destroy(handle): a bad handle raises 0xFF020103; else the handle goes back to the pool (state = 1).
void sub_577F78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577f78
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x577F84u, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    a1 = a1 | 0x103;
    if (v0 != 0) {
        // 0x00577f9c
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x00577fb0
    charge(ctx, 6);
    v1 = 1;
    ld(ra, sp, 0x8);
    sw(v1, s0, mps::kHandleState);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00577FC8 sub_577FC8 -- 148 bytes; leaf frame (no stack)
// [mpvGetStartCodeType] Classifies the MPEG start code at p (its four bytes read big-endian): 0x100 picture 4, 0x101
// first slice 3 (slice | first slice), 0x102..0x1AF slice 1, 0x1B2 user data 32, 0x1B3 sequence header 64, 0x1B5
// extension 16, 0x1B7 sequence end 128, 0x1B8 group 8, anything else 0 (tail1::sc; ISO/IEC 13818-2 table 6-1).
void sub_577FC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00577fc8
    enter(ctx, 13);  // entry check point + this block's cycles
    lbu(a3, a0, 0);
    a2 = 256;
    lbu(v0, a0, 1);
    a3 = sll(a3, 8);
    lbu(v1, a0, 2);
    a3 = a3 | v0;
    lbu(a1, a0, 3);
    a3 = sll(a3, 8);
    a3 = a3 | v1;
    a3 = sll(a3, 8);
    a3 = a3 | a1;
    t0 = 4;
    if (a3 != a2) {
        // 0x00577ffc
        charge(ctx, 3);
        v0 = 257;
        t0 = 3;
        if (a3 != v0) {
            // 0x00578008
            charge(ctx, 4);
            v0 = addiu(a3, -258);
            v0 = sltiu(v0, 174);
            t0 = 1;
            if (v0 == 0) {
                // 0x00578018
                charge(ctx, 3);
                v0 = 434;
                t0 = 32;
                if (a3 != v0) {
                    // 0x00578024
                    charge(ctx, 3);
                    v0 = 435;
                    t0 = 64;
                    if (a3 != v0) {
                        // 0x00578030
                        charge(ctx, 3);
                        v0 = 437;
                        t0 = 16;
                        if (a3 != v0) {
                            // 0x0057803c
                            charge(ctx, 3);
                            v0 = 439;
                            t0 = 128;
                            if (a3 != v0) {
                                // 0x00578048
                                charge(ctx, 3);
                                v0 = a3 ^ 0x1B8;
                                t0 = 8;
                                if (v0 != 0) t0 = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x00578054 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = t0;
}

// 0x00578060 sub_578060 -- 256 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s2 sp+0x10, s4 sp+0x20, ra sp+0x28
// [mpvSearchStartCodeBack] Searches backwards for an MPEG start code: from end - 1 down to end - len, a small state
// machine finds "00 00 01" and returns the address of the first zero byte when the code's class (sub_577FC8) & mask !=
// 0; 0 when none. Arguments (end, len, mask).
void sub_578060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00578060
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = subu(s0, a1);
    v0 = sltu(s1, s0);
    sd(s3, sp, 0x18);
    sd(s2, sp, 0x10);
    s3 = a2;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (v0 != 0) {
        // 0x00578094
        charge(ctx, 3);
        s2 = 1;
        s4 = 3;
        s0 = addiu(s0, -1);
        for (;;) {
            // 0x005780a0
            charge(ctx, 2);
            lb(v0, s0, 0);
            if (v1 == s2) {
                // 0x005780d0
                charge(ctx, 2);
                if (v0 == v1) {
                    v1 = 2;
                L_00578130:
                    charge(ctx, 1);
                    v0 = sltu(s1, s0);
                } else {
                    // 0x005780d8
                    charge(ctx, 2);
                    v0 = sltu(s1, s0);
                }
            L_00578134:
                charge(ctx, 2);
                s0 = addiu(s0, -1);
                if (v0 == 0) {
                    goto L_0057813c;
                }
                backedge(ctx);
                continue;
            }
            // 0x005780a8
            charge(ctx, 2);
            if (v1 == 0) {
                v1 = 1;
                goto L_00578130;
            }
            // 0x005780b0
            charge(ctx, 3);
            a0 = 2;
            if (v1 == a0) {
                // 0x005780e0
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x005780e8
                    charge(ctx, 2);
                    v1 = 3;
                    goto L_00578130;
                }
                // 0x005780f0
                charge(ctx, 2);
                cc = v0 == s2;  // the condition, before the delay slot changes it
                v0 = sltu(s1, s0);
                if (!cc) {
                    // 0x005780f8
                    charge(ctx, 2);
                    v1 = 1;
                }
                goto L_00578134;
            }
            // 0x005780bc
            charge(ctx, 2);
            if (v1 != s4) {
                // 0x005780c4
                charge(ctx, 2);
                v0 = sltu(s1, s0);
                goto L_00578134;
            }
            // 0x00578100
            charge(ctx, 2);
            if (v0 != 0) {
                v0 = v0 ^ 0x1;
                // 0x00578128
                charge(ctx, 2);
                v1 = s2;
                if (v0 == 0) v1 = a0;
                goto L_00578130;
            }
            // 0x00578108
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x578108u, gen::fn_sub_577FC8_00577fc8);
            v1 = s3 & v0;
            v0 = s0;
            if (v1 == 0) {
                // 0x0057811c
                charge(ctx, 2);
                v1 = 0;
                goto L_00578130;
            }
            break;
        }
        // 0x00578140 (the shared epilogue, written out on this path)
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
L_0057813c:
    charge(ctx, 1);
    v0 = 0;
    // 0x00578140 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00578160 sub_578160 -- 264 bytes; frame 0x40: s1 sp+0x8, s2 sp+0x10, s5 sp+0x28, s0 sp+0x0, s3 sp+0x18, s4 sp+0x20, s6 sp+0x30, ra sp+0x38
// [mpvSearchStartCode] Searches forwards for an MPEG start code in [p, p + len): returns the address of the "00 00 01
// xx" whose class (sub_577FC8) & mask != 0, or 0. Arguments (p, len, mask).
void sub_578160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00578160
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = addu(s1, a1);
    v0 = sltu(s1, s2);
    sd(s5, sp, 0x28);
    sd(s0, sp, 0x0);
    s5 = a2;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    if (v0 != 0) {
        // 0x0057819c
        charge(ctx, 5);
        // the scan state in v1: 0 = looking for a zero byte, 1 = one zero seen, 2 = two (or more) zeros, 3 = "00 00 01"
        // seen -- the byte after it completes a start code, classified four bytes back (s1 has moved past it)
        s4 = 1;
        s3 = 2;
        s6 = 3;
        lb(v0, s1, 0);
        for (;;) {
            // 0x005781b0
            charge(ctx, 2);
            s1 = addiu(s1, 1);
            if (v1 == s4) {  // state 1: a second zero -> 2, anything else -> 0
                // 0x005781e8
                charge(ctx, 3);
                v1 = s3;
                if (v0 != 0) v1 = 0;
            L_00578230:
                charge(ctx, 1);
                v0 = sltu(s1, s2);
            L_00578234:
                charge(ctx, 2);
                if (v0 == 0) {
                    goto L_0057823c;
                }
                lb(v0, s1, 0);
                backedge(ctx);
                continue;
            }
            // 0x005781b8
            charge(ctx, 2);
            if (v1 == 0) {  // state 0: a zero -> 1
                // 0x005781d8
                charge(ctx, 2);
                if (v0 == 0) {
                    v1 = 1;
                    goto L_00578230;
                }
                // 0x005781e0
                charge(ctx, 2);
                v0 = sltu(s1, s2);
                goto L_00578234;
            }
            // 0x005781c0
            charge(ctx, 2);
            if (v1 == s3) {  // state 2: 0x01 -> 3, another zero stays 2, anything else -> 0
                // 0x005781f8
                charge(ctx, 2);
                if (v0 == s4) {
                    // 0x00578200
                    charge(ctx, 2);
                    v1 = 3;
                    goto L_00578230;
                }
                // 0x00578208
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = sltu(s1, s2);
                if (!cc) {
                    // 0x00578210
                    charge(ctx, 2);
                    v1 = 0;
                }
                goto L_00578234;
            }
            // 0x005781c8
            charge(ctx, 2);
            if (v1 != s6) {
                // 0x005781d0
                charge(ctx, 2);
                v0 = sltu(s1, s2);
                goto L_00578234;
            }
            // state 3: the start code's class against the mask; a miss starts over at state 0
            s0 = addiu(s1, -4);
            // 0x00578218
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x578218u, gen::fn_sub_577FC8_00577fc8);
            v1 = s5 & v0;
            v0 = s0;
            if (v1 == 0) {
                // 0x0057822c
                charge(ctx, 1);
                v1 = 0;
                goto L_00578230;
            }
            break;
        }
        // 0x00578240 (the shared epilogue, written out on this path)
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
    }
L_0057823c:
    charge(ctx, 1);
    v0 = 0;
    // 0x00578240 (the shared epilogue, written out on this path)
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

// 0x00578D98 sub_578D98 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpvEntryErrFunc] MPV set the error callback (handle, fn, arg) into the handle's record (+592); a bad handle raises
// 0xFF030203 on the global record.
void sub_578D98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00578d98
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x578DB4u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    s0 = addiu(s0, mpv::kHandleErr);
    a0 = 0;
    a1 = a1 | 0x203;
    if (v0 != 0) {
        // 0x00578dd0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x00578de8
    charge(ctx, 8);
    sw(s1, s0, err::kArg);
    sw(s2, s0, err::kFn);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00578E08 sub_578E08 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpvGetErrInf] MPV get the error record: copies the handle's 20 bytes at +592 to out; a bad handle raises 0xFF030204.
void sub_578E08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00578e08
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x578E1Cu, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a0 = 0;
    if (v0 != 0) {
        // 0x00578e30
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x204;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x00578e48
    charge(ctx, 15);
    ldl(v1, s0, 599);
    ldr(v1, s0, 592);
    ldl(a0, s0, 607);
    ldr(a0, s0, 600);
    lw(a1, s0, 608);
    sdl(v1, s1, 7);
    sdr(v1, s1, 0);
    sdl(a0, s1, 15);
    sdr(a0, s1, 8);
    sw(a1, s1, 16);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00578E88 sub_578E88 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mpvSetError] MPV raise(handle, code): the handle's record (+592) or the global one (0x7B29E8), through sub_578ED8;
// returns the code.
void sub_578E88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00578e88
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    a0 = addiu(v0, mpv::kHandleErr);
    if (v0 != 0) {
        // 0x00578eb8
        charge(ctx, 3);
        jal(ctx, 0x578EB8u, gen::fn_sub_578ED8_00578ed8);
        v0 = s0;
    } else {
        // 0x00578ea4
        charge(ctx, 5);
        a0 = 0x7B0000;
        a0 = addiu(a0, 10728);  // &0x7B29E8
        jal(ctx, 0x578EA8u, gen::fn_sub_578ED8_00578ed8);
        v0 = s0;
    }
    // 0x00578ec4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00578ED8 sub_578ED8 -- 52 bytes; frame 0x10: ra sp+0x0
// [mpvCallErrFn] Error-record call, the MPV copy of sub_577C30 (byte-identical to sub_56F9C8 of the CRI band and to
// sub_577C30): code at +8, then fn(arg) when code != 0 and fn is set.
void sub_578ED8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00578ed8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    sw(v0, a0, err::kCode);
    if (v0 != 0) {
        // 0x00578eec
        charge(ctx, 3);
        lw(v0, a0, err::kFn);
        if (v0 != 0) {
            // 0x00578ef8
            charge(ctx, 2);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x578EF8u);  // $ra = the return address
            lw(a0, a0, err::kArg);
            call_ptr(ctx, jt);
            goto L_00578f00;
        }
        ld(ra, sp, 0x0);
        // 0x00578f04 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00578f00:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x00578f04 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00578FC0 sub_578FC0 -- 172 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// [mpvSearchPictureLevel] MPV find the next picture-level start code in a buffer {ptr, len}: searches for sequence end
// / sequence header / group / picture (mask 0xCC); *out = its offset (0 = found, raised code 0) or len (raised
// 0xFF030305); a bad handle raises 0xFF03020A. Always ends in sub_578E88 (handle 0 on the bad-handle path).
void sub_578FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00578fc0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    s3 = a2;
    jal(ctx, 0x578FE0u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a2 = 204;
    a0 = 0;
    a1 = a1 | 0x20A;
    if (v0 != 0) {
        // 0x00578ffc
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x00579018
    charge(ctx, 10);
    lw(s1, s0, 4);
    lw(s0, s0, 0);
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x579024u, gen::fn_sub_578160_00578160);
    a0 = s2;
    a1 = lui(0xFF03);
    s0 = subu(v0, s0);
    a1 = a1 | 0x305;
    if (v0 != 0) {
        // 0x00579048
        charge(ctx, 2);
        sw(s0, s3, 0);
        a1 = 0;
    } else {
        // 0x00579040
        charge(ctx, 2);
        sw(s1, s3, 0);
    }
    // 0x00579050
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_578E88_00578e88(ctx);  // tail call
}

// 0x00579070 sub_579070 -- 8 bytes; leaf frame (no stack)
// [mpvNullHook] An empty function (jr $ra / nop). The FLIRT name is a false match (the same few instructions as the SDK
// function; this is CRI code). Byte-identical to nullsub_1 0x1007F0, which font2 already replaced: same contract, same
// pair tests. (MPV)
void sub_579070(EEContext& ctx) {
    using namespace hg;
    // 0x00579070
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00579078 sub_579078 -- 8 bytes; leaf frame (no stack)
// [mpvStubMinusOne] Returns -1 (jr $ra / li v0, -1): an unsupported-operation stub of the MPV stream interface;
// byte-identical to the close / ioctl / lseek stubs at 0x503848.
void sub_579078(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00579078
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
}

// 0x00579138 sub_579138 -- 260 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpvGetSeqBlock] MPV copy out the handle's 128-byte block +464..+592 (32-byte strides of four doublewords; the two
// loops are the aligned / unaligned paths of an inlined copy and do the same); a bad handle raises 0xFF03020C.
void sub_579138(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00579138
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x57914Cu, gen::fn_sub_57B7F0_0057b7f0);
    a0 = 0;
    if (v0 != 0) {
        // 0x0057915c
        charge(ctx, 7);
        a1 = lui(0xFF03);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        a1 = a1 | 0x20C;
        sp = addiu(sp, 0x20);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x00579178
    charge(ctx, 6);
    a1 = s1;
    v1 = addiu(s0, mpv::kSeqBlock);
    v0 = v1 | a1;
    v0 = v0 & 0x7;
    a0 = addiu(s0, mpv::kHandleErr);  // the block's end
    if (v0 == 0) {
        for (;;) {
            // 0x005791f0
            charge(ctx, 13);
            ld(v0, v1, 0);
            ld(a2, v1, 8);
            ld(a3, v1, 16);
            ld(t0, v1, 24);
            sd(v0, a1, 0);
            sd(a2, a1, 8);
            sd(a3, a1, 16);
            sd(t0, a1, 24);
            v1 = addiu(v1, 32);
            a1 = addiu(a1, 32);
            if (v1 == a0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00579224
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        for (;;) {
            // 0x00579190
            charge(ctx, 21);
            ldl(v0, v1, 7);
            ldr(v0, v1, 0);
            ldl(a2, v1, 15);
            ldr(a2, v1, 8);
            ldl(a3, v1, 23);
            ldr(a3, v1, 16);
            ldl(t0, v1, 31);
            ldr(t0, v1, 24);
            sdl(v0, a1, 7);
            sdr(v0, a1, 0);
            sdl(a2, a1, 15);
            sdr(a2, a1, 8);
            sdl(a3, a1, 23);
            sdr(a3, a1, 16);
            sdl(t0, a1, 31);
            sdr(t0, a1, 24);
            v1 = addiu(v1, 32);
            a1 = addiu(a1, 32);
            if (v1 == a0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005791e4
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x00579228 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00579240 sub_579240 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpvGetBitRateValue] MPV *out = the handle's bit_rate_value (+680); a bad handle raises 0xFF03020D.
void sub_579240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00579240
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x579254u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a0 = 0;
    if (v0 == 0) {
        // 0x00579280
        charge(ctx, 7);
        lw(v1, s0, mpv::kBitRate);
        ld(s0, sp, 0x0);
        sw(v1, s1, 0);
        ld(ra, sp, 0x10);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00579268
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = a1 | 0x20D;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_578E88_00578e88(ctx);  // tail call
}

// 0x005792A0 sub_5792A0 -- 196 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [mpvGetStreamFigures] MPV stream figures: *a1 = vbv_buffer_size_value (+684) * 2,048 (bytes), *a2 = word +700, *a3 =
// +700 * bit_rate_value / 1,800, or -1 when bit_rate_value is 0x3FFFF (the variable-rate marker); a bad handle raises
// 0xFF03020F and leaves the outputs alone.
void sub_5792A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005792a0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a3;
    jal(ctx, 0x5792C4u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a2 = 0x30000;
    a0 = 0;
    a1 = a1 | 0x20F;
    a2 = a2 | 0xFFFF;
    if (v0 != 0) {
        // 0x005792e4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x00579300
    charge(ctx, 8);
    lw(v0, s0, mpv::kVbvSize);
    v0 = sll(v0, 11);
    sw(v0, s1, 0);
    lw(v1, s0, mpv::kWord700);
    sw(v1, s2, 0);
    lw(a0, s0, mpv::kBitRate);
    if (a0 != a2) {
        lw(v0, s0, mpv::kWord700);
        // 0x00579328
        charge(ctx, 3);
        v1 = 1800;
        if (v1 == 0) {
            brk(ctx, 0x579330u, 0x7u);
        }
        // 0x00579334
        charge(ctx, 3);
        mult(v0, v0, a0);
        div(v0, v1);
        mflo(v0);
    } else {
        // 0x00579320
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00579340 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sw(v0, s3, 0);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00579368 sub_579368 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpvGetWordPair] MPV *a1 = word +692, *a2 = word +696; a bad handle raises 0xFF03020E.
void sub_579368(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00579368
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x579384u, gen::fn_sub_57B7F0_0057b7f0);
    a1 = lui(0xFF03);
    a0 = 0;
    a1 = a1 | 0x20E;
    if (v0 != 0) {
        // 0x0057939c
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_578E88_00578e88(ctx);  // tail call
        return;
    }
    // 0x005793b8
    charge(ctx, 10);
    lw(v1, s0, mpv::kWord692);
    ld(ra, sp, 0x18);
    sw(v1, s1, 0);
    ld(s1, sp, 0x8);
    lw(a0, s0, mpv::kWord696);
    ld(s0, sp, 0x0);
    sw(a0, s2, 0);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005793E0 sub_5793E0 -- 8 bytes; leaf frame (no stack)
// [mpvNullHook2] An empty function (jr $ra / nop). The FLIRT name is a false match (the same few instructions as the
// SDK function; this is CRI code). Byte-identical to nullsub_1 0x1007F0, which font2 already replaced: same contract,
// same pair tests. (MPV)
void sub_5793E0(EEContext& ctx) {
    using namespace hg;
    // 0x005793e0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005793E8 sub_5793E8 -- 36 bytes; leaf frame (no stack)
// [mpvSetRow] MPV row write: row a1 (12-byte rows at +952) = {a2, a3, t0}; returns 12 * a1 in $v0.
void sub_5793E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x005793e8
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = sll(a1, 1);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    a0 = addiu(a0, mpv::kRows);
    sw(t0, a0, 8);
    sw(a2, a0, 0);
    sw(a3, a0, 4);
}

// 0x00579410 sub_579410 -- 20 bytes; leaf frame (no stack)
// [mpvSetWindow] MPV window = {a1, a2, 0} at +1000.
void sub_579410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00579410
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = addiu(a0, mpv::kWindow);
    sw(a1, a0, 0);
    sw(a2, a0, 4);
    sw(zero, a0, 8);
}

// 0x00579428 sub_579428 -- 40 bytes; leaf frame (no stack)
// [mpvGetWindow] MPV window read: *a1 = word 0, *a2 = word 2 of +1000 (each only when its pointer is non-null).
void sub_579428(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00579428
    enter(ctx, 2);  // entry check point + this block's cycles
    a0 = addiu(a0, mpv::kWindow);
    if (a1 != 0) {
        // 0x00579430
        charge(ctx, 2);
        lw(v0, a0, 0);
        sw(v0, a1, 0);
    }
    // 0x00579438
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00579440
        charge(ctx, 2);
        lw(v0, a0, 8);
        sw(v0, a2, 0);
    }
    // 0x00579448 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00579660 sub_579660 -- 108 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// [mpvPeekStartCode] MPV peek the next start code of a stream object: its interface's get-chunk (+24: (obj, 1,
// 0x7FFFFFFF, &chunk)) and unget-chunk (+28) calls through jalr, then the class of the code at chunk.ptr (sub_577FC8)
// when the chunk holds at least 4 bytes, else 0.
void sub_579660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00579660
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0x7FFF0000;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a1 = 1;
    a2 = a2 | 0xFFFF;
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a3 = sp;
    jalr(ctx, 0x579684u, v0.u());
    lw(v1, s0, 0);
    a0 = s0;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x57969Cu, v0.u());
    lw(v1, sp, 0x4);
    v1 = slti(v1, 4);
    v0 = 0;
    if (v1 == 0) {
        // 0x005796b4
        charge(ctx, 2);
        link(ctx, 0x5796B4u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x0);
        call(ctx, gen::fn_sub_577FC8_00577fc8);
    }
    // 0x005796bc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00579770 sub_579770 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpvDecideMpegKind] MPV decide MPEG-1 or MPEG-2, once (+856): find a sequence header in {ptr, len}, then the next
// start code after it: an extension start code means MPEG-2 (2; ISO/IEC 13818-2 puts sequence_extension right after
// every sequence header), any other code MPEG-1 (1); 0 = not decided yet. Returns the kind.
void sub_579770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00579770
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    lw(v1, s1, mpv::kMpegKind);
    v0 = v1;
    if (v1 == 0) {
        // 0x00579794
        charge(ctx, 7);
        lw(a0, s0, 0);
        a2 = 64;
        link(ctx, 0x57979Cu);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 4);
        call(ctx, gen::fn_sub_578160_00578160);
        v1 = v0;
        cc = v1 == 0;  // the condition, before the delay slot changes it
        v1 = addiu(v1, 4);
        if (!cc) {
            // 0x005797b0
            charge(ctx, 10);
            lw(a1, s0, 0);
            lw(v0, s0, 4);
            a0 = v1;
            a1 = subu(v1, a1);
            a2 = si(-1);
            a1 = subu(v0, a1);
            jal(ctx, 0x5797C4u, gen::fn_sub_578160_00578160);
            v1 = v0;
            if (v1 != 0) {
                // 0x005797d8
                charge(ctx, 6);
                a0 = v1;
                jal(ctx, 0x5797D8u, gen::fn_sub_577FC8_00577fc8);
                v1 = v0;
                v0 = v1 & 0x10;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 2;
                if (!cc) {
                    // 0x005797f0
                    charge(ctx, 2);
                    v0 = 1;
                    if (v1 != 0) {
                        goto L_005797f8;
                    }
                    goto L_005797fc;
                }
            L_005797f8:
                charge(ctx, 1);
                sw(v0, s1, mpv::kMpegKind);
                goto L_005797fc;
            }
            lw(v0, s1, mpv::kMpegKind);
            // 0x00579800 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_005797fc:
        charge(ctx, 1);
        lw(v0, s1, mpv::kMpegKind);
    }
    // 0x00579800 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057B7F0 sub_57B7F0 -- 36 bytes; leaf frame (no stack)
// [mpvCheckHandle] MPV handle check: remembers the handle in 0x99B31C; 0 for a non-null handle whose state (+392) is 2,
// else -1.
void sub_57B7F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0057b7f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    sw(a0, v0, -19684);  // 0x99B31C
    v0 = si(-1);
    if (a0 != 0) {
        // 0x0057b800
        charge(ctx, 3);
        lw(v1, a0, mpv::kHandleState);
        v1 = v1 ^ 0x2;
        if (v1 == 0) v0 = 0;
    }
    // 0x0057b80c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game
