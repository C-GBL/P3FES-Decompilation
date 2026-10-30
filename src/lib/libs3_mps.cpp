// Slice libs3: CRI Sofdec's MPS module (the MPEG program-stream demultiplexer): pack / system / PES header readers, the
// start-code classes, the getters; CRI's word copy / fill helpers before it.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn___env_lock_3_00575948(p3fes::EEContext&);
void fn___env_lock_4_005777e8(p3fes::EEContext&);
void fn_sub_5756A0_005756a0(p3fes::EEContext&);
void fn_sub_575880_00575880(p3fes::EEContext&);
void fn_sub_575958_00575958(p3fes::EEContext&);
void fn_sub_5759B0_005759b0(p3fes::EEContext&);
void fn_sub_575A00_00575a00(p3fes::EEContext&);
void fn_sub_575A50_00575a50(p3fes::EEContext&);
void fn_sub_575AA0_00575aa0(p3fes::EEContext&);
void fn_sub_575B48_00575b48(p3fes::EEContext&);
void fn_sub_575C68_00575c68(p3fes::EEContext&);
void fn_sub_575D70_00575d70(p3fes::EEContext&);
void fn_sub_5761D8_005761d8(p3fes::EEContext&);
void fn_sub_576A48_00576a48(p3fes::EEContext&);
void fn_sub_5776B0_005776b0(p3fes::EEContext&);
void fn_sub_577720_00577720(p3fes::EEContext&);
void fn_sub_577780_00577780(p3fes::EEContext&);
void fn_sub_5777F8_005777f8(p3fes::EEContext&);
void fn_sub_577860_00577860(p3fes::EEContext&);
void fn_sub_577910_00577910(p3fes::EEContext&);
void fn_sub_5779A8_005779a8(p3fes::EEContext&);
void fn_sub_577A38_00577a38(p3fes::EEContext&);
void fn_sub_577AB0_00577ab0(p3fes::EEContext&);
void fn_sub_577BB8_00577bb8(p3fes::EEContext&);
void fn_sub_577BB8_00577bb8_at_00577bd0(p3fes::EEContext&);
void fn_sub_577BE0_00577be0(p3fes::EEContext&);
void fn_sub_577DB0_00577db0(p3fes::EEContext&);
void fn_sub_577DD8_00577dd8(p3fes::EEContext&);
void fn_sub_577E10_00577e10(p3fes::EEContext&);
void fn_sub_577E68_00577e68(p3fes::EEContext&);
void fn_sub_577F08_00577f08(p3fes::EEContext&);
void fn_sub_577F20_00577f20(p3fes::EEContext&);
void fn_sub_577F48_00577f48(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x005756A0 sub_5756A0 -- 268 bytes; leaf frame (no stack)
// [criWordCopy] CRI's word copy (dst, src, nwords): the n % 16 odd words one at a time, then blocks of 16 words. Used
// by MPV and SFD as well as MPS.
void sub_5756A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x005756a0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = a2 & 0xF;
    if (v1 == 0) {
        a2 = srl(a2, 4);
    } else {
        // 0x005756ac
        charge(ctx, 1);
        for (;;) {
            // 0x005756b0
            charge(ctx, 7);
            lw(v0, a1, 0);
            a1 = addiu(a1, 4);
            v1 = addiu(v1, -1);
            sw(v0, a0, 0);
            a0 = addiu(a0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005756cc
        charge(ctx, 1);
        a2 = srl(a2, 4);
    }
    // 0x005756d0
    charge(ctx, 2);
    if (a2 != 0) {
        for (;;) {
            // 0x005756d8
            charge(ctx, 51);
            lw(t0, a1, 0);
            a1 = addiu(a1, 4);
            lw(a3, a1, 0);
            a1 = addiu(a1, 4);
            lw(v1, a1, 0);
            a1 = addiu(a1, 4);
            lw(v0, a1, 0);
            a1 = addiu(a1, 4);
            sw(t0, a0, 0);
            a2 = addiu(a2, -1);
            sw(a3, a0, 4);
            sw(v1, a0, 8);
            sw(v0, a0, 12);
            lw(t0, a1, 0);
            a1 = addiu(a1, 4);
            lw(a3, a1, 0);
            a1 = addiu(a1, 4);
            lw(v1, a1, 0);
            a1 = addiu(a1, 4);
            lw(v0, a1, 0);
            a1 = addiu(a1, 4);
            sw(t0, a0, 16);
            sw(a3, a0, 20);
            sw(v1, a0, 24);
            sw(v0, a0, 28);
            lw(t0, a1, 0);
            a1 = addiu(a1, 4);
            lw(a3, a1, 0);
            a1 = addiu(a1, 4);
            lw(v1, a1, 0);
            a1 = addiu(a1, 4);
            lw(v0, a1, 0);
            a1 = addiu(a1, 4);
            sw(t0, a0, 32);
            sw(a3, a0, 36);
            sw(v1, a0, 40);
            sw(v0, a0, 44);
            lw(t0, a1, 0);
            a1 = addiu(a1, 4);
            lw(a3, a1, 0);
            a1 = addiu(a1, 4);
            lw(v1, a1, 0);
            a1 = addiu(a1, 4);
            lw(v0, a1, 0);
            a1 = addiu(a1, 4);
            sw(t0, a0, 48);
            sw(a3, a0, 52);
            sw(v1, a0, 56);
            sw(v0, a0, 60);
            a0 = addiu(a0, 64);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005757a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00575948 __env_lock_3 -- 8 bytes; leaf frame (no stack)
// [mpsInitHookA] An empty init hook (jr $ra / nop) MPS's init calls. The FLIRT name is a false match of a short code
// shape; the role is read from the instructions.
void __env_lock_3(EEContext& ctx) {
    using namespace hg;
    // 0x00575948
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00575958 sub_575958 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsSetMode] MPS: stores a word at handle +16 after the handle check sub_577DB0 (tail1); on failure MPS raises
// 0xFF020302. No caller.
void sub_575958(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575958
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x57596Cu, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    if (v0 == 0) {
        // 0x00575998
        charge(ctx, 6);
        sw(s1, s0, 16);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00575980
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = a1 | 0x302;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_577BE0_00577be0(ctx);  // tail call
}

// 0x005759B0 sub_5759B0 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpsSetCallbackA] MPS: handle callback A (+228 = fn, +232 = argument) after the handle check; returns the check's
// result.
void sub_5759B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005759b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x5759CCu, gen::fn_sub_577DB0_00577db0);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005759dc
        charge(ctx, 3);
        sw(s1, s0, 232);
        sw(s2, s0, 228);
        ld(s0, sp, 0x0);
    }
    // 0x005759e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00575A00 sub_575A00 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpsSetCallbackB] MPS: handle callback B (+236 = fn, +240 = argument) after the handle check.
void sub_575A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575a00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x575A1Cu, gen::fn_sub_577DB0_00577db0);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00575a2c
        charge(ctx, 3);
        sw(s1, s0, 240);
        sw(s2, s0, 236);
        ld(s0, sp, 0x0);
    }
    // 0x00575a38 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00575A50 sub_575A50 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpsSetPesCallback] MPS: the PES callback (+244 = fn, +248 = argument; sub_575C68 calls it after each PES header with
// the stream id) after the handle check.
void sub_575A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575a50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x575A6Cu, gen::fn_sub_577DB0_00577db0);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00575a7c
        charge(ctx, 3);
        sw(s1, s0, 248);
        sw(s2, s0, 244);
        ld(s0, sp, 0x0);
    }
    // 0x00575a88 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00575AA0 sub_575AA0 -- 168 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [mpsDemux] MPS demultiplex (h, buf, len, &used, &classes): clears both outputs; the handle check sub_577DB0 (tail1);
// on failure MPS raises 0xFF020301; otherwise calls the handle's parser (+212, sub_575B48) through jalr with the same
// arguments.
void sub_575AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575aa0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s2, sp, 0x10);
    s2 = t0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = a1;
    sd(ra, sp, 0x28);
    sw(zero, s0, 0);
    link(ctx, 0x575AD4u);  // $ra first: the delay slot below depends on it
    sw(zero, s2, 0);
    call(ctx, gen::fn_sub_577DB0_00577db0);
    a0 = 0;
    a1 = lui(0xFF02);
    a2 = s1;
    a3 = s0;
    t0 = s2;
    a1 = a1 | 0x301;
    if (v0 != 0) {
        // 0x00575af8
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x00575b18
    charge(ctx, 12);
    lw(v0, s3, 212);
    a0 = s3;
    a1 = s4;
    jalr(ctx, 0x575B20u, v0.u());
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00575B48 sub_575B48 -- 284 bytes; frame 0x40: ra sp+0x38, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30
// [mpsParse] MPS's parser (h, buf, len, &used, &classes): reads packets (sub_575C68) while 4 or more bytes remain and
// the packet says go on, adding the bytes used and ORing the start-code classes; when a system header was read (class
// 0x20000) its 32-byte record (+40) is filed into the first of three slots (+72 + 32 * k) chosen by its words +48 /
// +52. Returns 0.
void sub_575B48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00575b48
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x38);
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = t0;
    sd(s3, sp, 0x28);
    s3 = a3;
    sd(s4, sp, 0x30);
    s4 = a0;
    for (;;) {
        // 0x00575b78
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            // 0x00575b84
            charge(ctx, 17);
            a1 = s1;
            a2 = s0;
            a0 = s4;
            a3 = sp;
            t0 = addiu(sp, 0x4);
            jal(ctx, 0x575B94u, gen::fn_sub_575C68_00575c68);
            lw(a1, s2, 0);
            lw(v1, sp, 0x0);
            lw(a0, s3, 0);
            lw(a2, sp, 0x4);
            s1 = addu(s1, v1);
            a0 = addu(a0, v1);
            s0 = subu(s0, v1);
            a1 = a1 | a2;
            sw(a0, s3, 0);
            sw(a1, s2, 0);
            if (v0 == 0) {
                goto L_00575bc8_3;
            }
            backedge(ctx);
            continue;
        }
        lw(v0, s2, 0);
        break;
    }
L_00575bcc:
    charge(ctx, 4);
    v1 = 0x20000;
    v0 = v0 & v1;
    a0 = addiu(s4, 40);
    if (v0 != 0) {
        // 0x00575bdc
        charge(ctx, 3);
        lw(v0, a0, 8);
        a1 = 0;
        if (v0 == 0) {
            // 0x00575be8
            charge(ctx, 4);
            lw(v1, a0, 12);
            v0 = 2;
            a1 = 1;
            if (v1 == 0) a1 = v0;
        }
        // 0x00575bf8
        charge(ctx, 18);
        v0 = sll(a1, 5);
        v0 = addu(v0, s4);
        ldl(v1, a0, 7);
        ldr(v1, a0, 0);
        ldl(a1, a0, 15);
        ldr(a1, a0, 8);
        ldl(a2, a0, 23);
        ldr(a2, a0, 16);
        ldl(a3, a0, 31);
        ldr(a3, a0, 24);
        sdl(v1, v0, 79);
        sdr(v1, v0, 72);
        sdl(a1, v0, 87);
        sdr(a1, v0, 80);
        sdl(a2, v0, 95);
        sdr(a2, v0, 88);
        sdl(a3, v0, 103);
        sdr(a3, v0, 96);
    }
    // 0x00575c40 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x10);
    v0 = 0;
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
    return;
L_00575bc8_3:
    charge(ctx, 1);
    lw(v0, s2, 0);
    goto L_00575bcc;
}

// 0x00575C68 sub_575C68 -- 260 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// [mpsParsePacket] MPS packet step (h, p, len, &used, &class): classifies the start code (sub_5776B0) -- pack header
// (0x10000): sub_575D70, go on; system header (0x20000): sub_5761D8, go on; PES packet (0x40000): sub_576A48, then the
// PES callback (+244) with its argument (+248) and the stream id (+184), stop; anything else: stop. Returns 1 to go on,
// 0 to stop.
void sub_575C68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00575c68
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s0, sp, 0x0);
    s0 = t0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x20);
    a0 = s2;
    link(ctx, 0x575C94u);  // $ra first: the delay slot below depends on it
    sw(zero, s3, 0);
    call(ctx, gen::fn_sub_5776B0_005776b0);
    v1 = v0;
    v0 = 0x20000;
    sw(v1, s0, 0);
    s0 = 0;
    if (v1 == v0) {
        // 0x00575d00
        charge(ctx, 7);
        a0 = s1;
        a1 = s2;
        a2 = s3;
        s0 = 1;
        jal(ctx, 0x575D0Cu, gen::fn_sub_5761D8_005761d8);
        v0 = s0;
    L_00575d50:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x00575cb0
        charge(ctx, 3);
        v0 = slt(v0, v1);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0x40000;
        if (cc) {
            // 0x00575cd0
            charge(ctx, 2);
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (cc) {
                // 0x00575d20
                charge(ctx, 8);
                lw(a3, s1, 16);
                a1 = s2;
                a2 = s3;
                a0 = s1;
                jal(ctx, 0x575D2Cu, gen::fn_sub_576A48_00576a48);
                lw(v0, s1, 244);
                if (v0 == 0) {
                    v0 = s0;
                } else {
                    // 0x00575d40
                    charge(ctx, 4);
                    lbu(a1, s1, 184);
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x575D44u);  // $ra = the return address
                    lw(a0, s1, 248);
                    call_ptr(ctx, jt);
                    v0 = s0;
                }
                goto L_00575d50;
            }
            // 0x00575cd8
            charge(ctx, 2);
            ld(s0, sp, 0x0);
        } else {
            // 0x00575cbc
            charge(ctx, 3);
            v0 = 0x10000;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = s0;
            if (cc) {
                // 0x00575ce0
                charge(ctx, 7);
                a0 = s1;
                a1 = s2;
                a2 = s3;
                s0 = 1;
                jal(ctx, 0x575CECu, gen::fn_sub_575D70_00575d70);
                v0 = s0;
                goto L_00575d50;
            }
            // 0x00575cc8
            charge(ctx, 2);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00575d54 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00575D70 sub_575D70 -- 1124 bytes; leaf frame (no stack)
// [mpsReadPackHeader] MPS pack header (ISO/IEC 11172-1 / 13818-1 pack_header): reads the bits after 0x000001BA with a
// 64-bit window -- the MPEG-1 layout (0010, SCR in 3 + 15 + 15 bits with markers, 22-bit mux_rate) or the MPEG-2 layout
// (01, SCR base + 9-bit extension, mux_rate, stuffing length) -- into the handle's pack record (+24); *used = the
// header's length.
void sub_575D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00575d70
    enter(ctx, 39);  // entry check point + this block's cycles
    v0 = addiu(a1, 4);
    v1 = si(-4);
    t1 = v0 & v1;
    t7 = a2;
    a1 = subu(a1, t1);
    lb(t2, t1, 0);
    t1 = addiu(t1, 1);
    t6 = addiu(a0, 24);
    lbu(v1, t1, 0);
    t1 = addiu(t1, 1);
    lbu(a2, t1, 0);
    t1 = addiu(t1, 1);
    lbu(a3, t1, 0);
    t1 = addiu(t1, 1);
    lb(t0, t1, 0);
    t1 = addiu(t1, 1);
    lbu(v0, t1, 0);
    t1 = addiu(t1, 1);
    t2 = sll(t2, 8);
    t0 = sll(t0, 8);
    t2 = t2 | v1;
    t0 = t0 | v0;
    lbu(a0, t1, 0);
    t1 = addiu(t1, 1);
    t2 = sll(t2, 8);
    a1 = addiu(a1, 4);
    t0 = sll(t0, 8);
    t2 = t2 | a2;
    a1 = sll(a1, 3);
    lbu(v1, t1, 0);
    t0 = t0 | a0;
    t2 = sll(t2, 8);
    t0 = sll(t0, 8);
    t2 = t2 | a3;
    v0 = slti(a1, 30);
    t0 = t0 | v1;
    t2 = sllv(t2, a1);
    t1 = addiu(t1, 1);
    if (v0 != 0) {
        // 0x00575e70
        charge(ctx, 3);
        t5 = srl(t2, 30);
        t2 = sll(t2, 2);
        a1 = addiu(a1, 2);
    } else {
        // 0x00575e0c
        charge(ctx, 3);
        a1 = addiu(a1, -30);
        v0 = srl(t0, 1);
        if (a1 == 0) {
            // 0x00575e28
            charge(ctx, 2);
            t5 = srl(t2, 30);
            t2 = t0;
        } else {
            // 0x00575e18
            charge(ctx, 4);
            t2 = t2 | v0;
            t5 = srl(t2, 30);
            t2 = sll(t0, 1);
        }
        // 0x00575e30
        charge(ctx, 15);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00575e7c
    charge(ctx, 4);
    a1 = addiu(a1, 2);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t2 = sll(t2, 2);
    } else {
        // 0x00575e8c
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t2 = sllv(t0, a1);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00575ecc
    charge(ctx, 3);
    v0 = slti(a1, 29);
    t4 = srl(t2, 29);
    if (v0 != 0) {
        // 0x00575f40
        charge(ctx, 2);
        t2 = sll(t2, 3);
        a1 = addiu(a1, 3);
    } else {
        // 0x00575ed8
        charge(ctx, 3);
        a1 = addiu(a1, -29);
        v0 = 3;
        if (a1 == 0) {
            // 0x00575f00
            charge(ctx, 1);
            t2 = t0;
        } else {
            // 0x00575ee4
            charge(ctx, 6);
            v0 = subu(v0, a1);
            v0 = srlv(t0, v0);
            t2 = t2 | v0;
            t4 = srl(t2, 29);
            t2 = sllv(t0, a1);
        }
        // 0x00575f04
        charge(ctx, 15);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00575f48
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t2 = sll(t2, 1);
    } else {
        // 0x00575f58
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t2 = sllv(t0, a1);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00575f98
    charge(ctx, 3);
    v0 = slti(a1, 17);
    t3 = srl(t2, 17);
    if (v0 != 0) {
        // 0x00576008
        charge(ctx, 2);
        t2 = sll(t2, 15);
        a1 = addiu(a1, 15);
    } else {
        // 0x00575fa4
        charge(ctx, 3);
        a1 = addiu(a1, -17);
        v0 = 15;
        if (a1 == 0) {
            // 0x00575fc8
            charge(ctx, 1);
            t2 = t0;
        } else {
            // 0x00575fb0
            charge(ctx, 6);
            v0 = subu(v0, a1);
            v0 = srlv(t0, v0);
            t2 = t2 | v0;
            t3 = srl(t2, 17);
            t2 = sllv(t0, a1);
        }
        // 0x00575fcc
        charge(ctx, 15);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00576010
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t2 = sll(t2, 1);
    } else {
        // 0x00576020
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t2 = sllv(t0, a1);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00576060
    charge(ctx, 3);
    v0 = slti(a1, 17);
    a3 = srl(t2, 17);
    if (v0 != 0) {
        // 0x005760d0
        charge(ctx, 2);
        t2 = sll(t2, 15);
        a1 = addiu(a1, 15);
    } else {
        // 0x0057606c
        charge(ctx, 3);
        a1 = addiu(a1, -17);
        v0 = 15;
        if (a1 == 0) {
            // 0x00576090
            charge(ctx, 1);
            t2 = t0;
        } else {
            // 0x00576078
            charge(ctx, 6);
            v0 = subu(v0, a1);
            v0 = srlv(t0, v0);
            t2 = t2 | v0;
            a3 = srl(t2, 17);
            t2 = sllv(t0, a1);
        }
        // 0x00576094
        charge(ctx, 15);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x005760d8
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t2 = sll(t2, 1);
    } else {
        // 0x005760e8
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t2 = sllv(t0, a1);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00576128
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t2 = sll(t2, 1);
    } else {
        // 0x00576138
        charge(ctx, 14);
        a1 = addiu(a1, -32);
        t2 = sllv(t0, a1);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        lbu(a0, t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v1;
        t0 = sll(t0, 8);
        t0 = t0 | a0;
    }
    // 0x00576170
    charge(ctx, 3);
    v0 = slti(a1, 10);
    a2 = srl(t2, 10);
    if (v0 == 0) {
        // 0x0057617c
        charge(ctx, 3);
        a1 = addiu(a1, -10);
        if (a1 != 0) {
            // 0x00576188
            charge(ctx, 5);
            v0 = 22;
            v0 = subu(v0, a1);
            v0 = srlv(t0, v0);
            t2 = t2 | v0;
            a2 = srl(t2, 10);
            goto L_0057619c;
        }
        v1 = t4 & 0x7;
        // 0x005761a0 (the shared epilogue, written out on this path)
        charge(ctx, 13);
        v0 = t3 & 0x7FFF;
        v0 = dsll(v0, 15);
        v1 = dsll(v1, 30);
        v1 = v1 | v0;
        v0 = sltiu(t5, 1);
        a0 = a3 & 0x7FFF;
        sw(a2, t6, 12);
        v1 = v1 | a0;
        a0 = 12;
        sw(v0, t6, 8);
        sd(v1, t6, 0);
        sw(a0, t7, 0);
        return;
    }
L_0057619c:
    charge(ctx, 1);
    v1 = t4 & 0x7;
    // 0x005761a0 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = t3 & 0x7FFF;
    v0 = dsll(v0, 15);
    v1 = dsll(v1, 30);
    v1 = v1 | v0;
    v0 = sltiu(t5, 1);
    a0 = a3 & 0x7FFF;
    sw(a2, t6, 12);
    v1 = v1 | a0;
    a0 = 12;
    sw(v0, t6, 8);
    sd(v1, t6, 0);
    sw(a0, t7, 0);
}

// 0x005761D8 sub_5761D8 -- 2156 bytes; frame 0x100: s1 sp+0xD8, s3 sp+0xE8, s4 sp+0xF0, s0 sp+0xD0, s2 sp+0xE0, ra sp+0xF8
// [mpsReadSystemHeader] MPS system header (system_header, 0x000001BB): header_length, rate_bound, audio_bound, the
// fixed / CSPS / lock flags, video_bound, then the stream_id / P-STD buffer list (into a stack table, copied to the
// handle's system record +40); *used = 6 + header_length.
void sub_5761D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005761d8
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    t3 = a1;
    sd(s1, sp, 0xD8);
    v1 = si(-4);
    sd(s3, sp, 0xE8);
    s3 = a2;
    sd(s4, sp, 0xF0);
    s4 = a0;
    sd(s0, sp, 0xD0);
    v0 = addiu(t3, 4);
    sd(s2, sp, 0xE0);
    t0 = v0 & v1;
    sd(ra, sp, 0xF8);
    v1 = subu(t3, t0);
    v1 = addiu(v1, 4);
    s1 = addiu(s4, 40);
    lb(t1, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a0, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a1, t0, 0);
    t0 = addiu(t0, 1);
    lbu(a2, t0, 0);
    t0 = addiu(t0, 1);
    lb(a3, t0, 0);
    t0 = addiu(t0, 1);
    lbu(v0, t0, 0);
    t0 = addiu(t0, 1);
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a0;
    lbu(a0, t0, 0);
    a3 = a3 | v0;
    t1 = sll(t1, 8);
    t0 = addiu(t0, 1);
    t1 = t1 | a1;
    a3 = sll(a3, 8);
    lbu(v0, t0, 0);
    a1 = sll(v1, 3);
    a3 = a3 | a0;
    t1 = sll(t1, 8);
    a3 = sll(a3, 8);
    t1 = t1 | a2;
    v1 = slti(a1, 16);
    a3 = a3 | v0;
    t1 = sllv(t1, a1);
    t0 = addiu(t0, 1);
    if (v1 != 0) {
        // 0x00576308
        charge(ctx, 4);
        v0 = srl(t1, 16);
        t1 = sll(t1, 16);
        sw(v0, s1, 0);
        a1 = addiu(a1, 16);
    } else {
        // 0x00576298
        charge(ctx, 3);
        a1 = addiu(a1, -16);
        v0 = 16;
        if (a1 == 0) {
            // 0x005762c0
            charge(ctx, 3);
            v0 = srl(t1, 16);
            t1 = a3;
            sw(v0, s1, 0);
        } else {
            // 0x005762a4
            charge(ctx, 7);
            v0 = subu(v0, a1);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 16);
            t1 = sllv(a3, a1);
            sw(v1, s1, 0);
        }
        // 0x005762cc
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576318
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t1 = sll(t1, 1);
    } else {
        // 0x00576328
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t1 = sllv(a3, a1);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576368
    charge(ctx, 3);
    v0 = slti(a1, 10);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 10);
    if (cc) {
        // 0x005763e8
        charge(ctx, 3);
        t1 = sll(t1, 22);
        sw(v0, s1, 4);
        a1 = addiu(a1, 22);
    } else {
        // 0x00576374
        charge(ctx, 3);
        a1 = addiu(a1, -10);
        v0 = 22;
        if (a1 == 0) {
            // 0x005763a0
            charge(ctx, 3);
            v0 = srl(t1, 10);
            t1 = a3;
            sw(v0, s1, 4);
        } else {
            // 0x00576380
            charge(ctx, 7);
            v0 = subu(v0, a1);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 10);
            t1 = sllv(a3, a1);
            sw(v1, s1, 4);
        }
        // 0x005763ac
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005763f4
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t1 = sll(t1, 1);
    } else {
        // 0x00576404
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t1 = sllv(a3, a1);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576444
    charge(ctx, 3);
    v0 = slti(a1, 26);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 26);
    if (cc) {
        // 0x005764c0
        charge(ctx, 3);
        t1 = sll(t1, 6);
        sw(v0, s1, 8);
        a1 = addiu(a1, 6);
    } else {
        // 0x00576450
        charge(ctx, 3);
        a1 = addiu(a1, -26);
        v0 = 6;
        if (a1 == 0) {
            // 0x00576478
            charge(ctx, 3);
            v0 = srl(t1, 26);
            t1 = a3;
            sw(v0, s1, 8);
        } else {
            // 0x0057645c
            charge(ctx, 7);
            v0 = subu(v0, a1);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 26);
            t1 = sllv(a3, a1);
            sw(v1, s1, 8);
        }
        // 0x00576484
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005764cc
    charge(ctx, 4);
    v0 = srl(t1, 31);
    v1 = 31;
    sw(v0, s1, 16);
    if (a1 != v1) {
        // 0x00576520
        charge(ctx, 2);
        a1 = addiu(a1, 1);
        t1 = sll(t1, 1);
    } else {
        // 0x005764dc
        charge(ctx, 17);
        t1 = a3;
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        a1 = 0;
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576528
    charge(ctx, 4);
    v0 = srl(t1, 31);
    v1 = 31;
    sw(v0, s1, 20);
    if (a1 != v1) {
        // 0x00576580
        charge(ctx, 2);
        a1 = addiu(a1, 1);
        t1 = sll(t1, 1);
    } else {
        // 0x00576538
        charge(ctx, 17);
        t1 = a3;
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        a1 = 0;
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576588
    charge(ctx, 4);
    v0 = srl(t1, 31);
    v1 = 31;
    sw(v0, s1, 24);
    if (a1 != v1) {
        // 0x005765e0
        charge(ctx, 2);
        a1 = addiu(a1, 1);
        t1 = sll(t1, 1);
    } else {
        // 0x00576598
        charge(ctx, 17);
        t1 = a3;
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        a1 = 0;
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005765e8
    charge(ctx, 4);
    v0 = srl(t1, 31);
    v1 = 31;
    sw(v0, s1, 28);
    if (a1 != v1) {
        // 0x00576640
        charge(ctx, 2);
        a1 = addiu(a1, 1);
        t1 = sll(t1, 1);
    } else {
        // 0x005765f8
        charge(ctx, 17);
        t1 = a3;
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        a1 = 0;
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576648
    charge(ctx, 4);
    a1 = addiu(a1, 1);
    v0 = slti(a1, 32);
    if (v0 != 0) {
        t1 = sll(t1, 1);
    } else {
        // 0x00576658
        charge(ctx, 16);
        a1 = addiu(a1, -32);
        t1 = sllv(a3, a1);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576698
    charge(ctx, 3);
    v0 = slti(a1, 27);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = srl(t1, 27);
    if (cc) {
        // 0x00576718
        charge(ctx, 3);
        t1 = sll(t1, 5);
        sw(v0, s1, 12);
        a1 = addiu(a1, 5);
    } else {
        // 0x005766a4
        charge(ctx, 3);
        a1 = addiu(a1, -27);
        v0 = 5;
        if (a1 == 0) {
            // 0x005766d0
            charge(ctx, 3);
            v0 = srl(t1, 27);
            t1 = a3;
            sw(v0, s1, 12);
        } else {
            // 0x005766b0
            charge(ctx, 7);
            v0 = subu(v0, a1);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            v1 = srl(t1, 27);
            t1 = sllv(a3, a1);
            sw(v1, s1, 12);
        }
        // 0x005766dc
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x00576724
    charge(ctx, 3);
    v0 = slti(a1, 24);
    s2 = srl(t1, 24);
    if (v0 != 0) {
        // 0x00576798
        charge(ctx, 2);
        t1 = sll(t1, 8);
        a1 = addiu(a1, 8);
    } else {
        // 0x00576730
        charge(ctx, 3);
        a1 = addiu(a1, -24);
        v0 = 8;
        if (a1 == 0) {
            // 0x00576758
            charge(ctx, 1);
            t1 = a3;
        } else {
            // 0x0057673c
            charge(ctx, 6);
            v0 = subu(v0, a1);
            v0 = srlv(a3, v0);
            t1 = t1 | v0;
            s2 = srl(t1, 24);
            t1 = sllv(a3, a1);
        }
        // 0x0057675c
        charge(ctx, 15);
        lb(a3, t0, 0);
        t0 = addiu(t0, 1);
        lbu(v0, t0, 0);
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v1, t0, 0);
        a3 = a3 | v0;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        lbu(v0, t0, 0);
        a3 = a3 | v1;
        t0 = addiu(t0, 1);
        a3 = sll(a3, 8);
        a3 = a3 | v0;
    }
    // 0x005767a0
    charge(ctx, 2);
    sw(zero, sp, 0xC);
    if (i64(t1) < 0) {
        // 0x005767a8
        charge(ctx, 2);
        t4 = addiu(sp, 0x2);
        for (;;) {
            // 0x005767b0
            charge(ctx, 3);
            v0 = slti(a1, 24);
            a2 = srl(t1, 24);
            if (v0 != 0) {
                // 0x00576820
                charge(ctx, 2);
                t1 = sll(t1, 8);
                a1 = addiu(a1, 8);
            } else {
                // 0x005767bc
                charge(ctx, 3);
                a1 = addiu(a1, -24);
                v0 = 8;
                if (a1 == 0) {
                    // 0x005767e0
                    charge(ctx, 1);
                    t1 = a3;
                } else {
                    // 0x005767c8
                    charge(ctx, 6);
                    v0 = subu(v0, a1);
                    v0 = srlv(a3, v0);
                    t1 = t1 | v0;
                    a2 = srl(t1, 24);
                    t1 = sllv(a3, a1);
                }
                // 0x005767e4
                charge(ctx, 15);
                lb(a3, t0, 0);
                t0 = addiu(t0, 1);
                lbu(v0, t0, 0);
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v1, t0, 0);
                a3 = a3 | v0;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v0, t0, 0);
                a3 = a3 | v1;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            // 0x00576828
            charge(ctx, 4);
            a1 = addiu(a1, 2);
            v0 = slti(a1, 32);
            if (v0 != 0) {
                t1 = sll(t1, 2);
            } else {
                // 0x00576838
                charge(ctx, 16);
                a1 = addiu(a1, -32);
                t1 = sllv(a3, a1);
                lb(a3, t0, 0);
                t0 = addiu(t0, 1);
                lbu(v0, t0, 0);
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v1, t0, 0);
                a3 = a3 | v0;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v0, t0, 0);
                a3 = a3 | v1;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            // 0x00576878
            charge(ctx, 3);
            v0 = 31;
            t2 = srl(t1, 31);
            if (a1 != v0) {
                // 0x005768c8
                charge(ctx, 2);
                a1 = addiu(a1, 1);
                t1 = sll(t1, 1);
            } else {
                // 0x00576884
                charge(ctx, 17);
                t1 = a3;
                lb(a3, t0, 0);
                t0 = addiu(t0, 1);
                a1 = 0;
                lbu(v0, t0, 0);
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v1, t0, 0);
                a3 = a3 | v0;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v0, t0, 0);
                a3 = a3 | v1;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            // 0x005768d0
            charge(ctx, 3);
            v0 = slti(a1, 19);
            a0 = srl(t1, 19);
            if (v0 != 0) {
                // 0x00576940
                charge(ctx, 2);
                t1 = sll(t1, 13);
                a1 = addiu(a1, 13);
            } else {
                // 0x005768dc
                charge(ctx, 3);
                a1 = addiu(a1, -19);
                v0 = 13;
                if (a1 == 0) {
                    // 0x00576900
                    charge(ctx, 1);
                    t1 = a3;
                } else {
                    // 0x005768e8
                    charge(ctx, 6);
                    v0 = subu(v0, a1);
                    v0 = srlv(a3, v0);
                    t1 = t1 | v0;
                    a0 = srl(t1, 19);
                    t1 = sllv(a3, a1);
                }
                // 0x00576904
                charge(ctx, 15);
                lb(a3, t0, 0);
                t0 = addiu(t0, 1);
                lbu(v0, t0, 0);
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v1, t0, 0);
                a3 = a3 | v0;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                lbu(v0, t0, 0);
                a3 = a3 | v1;
                t0 = addiu(t0, 1);
                a3 = sll(a3, 8);
                a3 = a3 | v0;
            }
            // 0x00576948
            charge(ctx, 15);
            lw(v0, sp, 0xC);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            sb(a2, v0, 16);
            lw(v1, sp, 0xC);
            v1 = sll(v1, 2);
            v1 = addu(v1, sp);
            sb(t2, v1, 17);
            lw(v0, sp, 0xC);
            v1 = sll(v0, 2);
            v0 = addiu(v0, 1);
            v1 = addu(v1, t4);
            sw(v0, sp, 0xC);
            sh(a0, v1, 16);
            if (i64(t1) >= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00576984
    charge(ctx, 9);
    v0 = addiu(a1, 7);
    v0 = sra(v0, 3);
    s0 = addu(t0, v0);
    a0 = addiu(s0, -8);
    v0 = subu(a0, t3);
    link(ctx, 0x576998u);  // $ra first: the delay slot below depends on it
    sw(v0, s3, 0);
    call(ctx, gen::fn_sub_5776B0_005776b0);
    if (v0 != 0) {
        lw(t4, s4, 228);
    } else {
        // 0x005769a8
        charge(ctx, 5);
        a0 = addiu(s0, -7);
        jal(ctx, 0x5769A8u, gen::fn_sub_5776B0_005776b0);
        v1 = 0x40000;
        if (v0 != v1) {
            lw(t4, s4, 228);
        } else {
            // 0x005769bc
            charge(ctx, 4);
            lw(v0, s3, 0);
            v0 = addiu(v0, 1);
            sw(v0, s3, 0);
            lw(t4, s4, 228);
        }
    }
    // 0x005769cc
    charge(ctx, 2);
    t3 = s2 & 0x7F;
    if (t4 != 0) {
        // 0x005769d4
        charge(ctx, 20);
        lbu(a0, s1, 24);
        lbu(t2, s1, 12);
        t1 = srl(s2, 7);
        lbu(a3, s1, 8);
        a1 = sp;
        lbu(v0, s1, 16);
        lbu(v1, s1, 20);
        lbu(a2, s1, 28);
        lw(t0, s1, 4);
        sb(a3, sp, 0x4);
        sb(v0, sp, 0x5);
        sb(v1, sp, 0x6);
        sb(a0, sp, 0x7);
        sb(a2, sp, 0x8);
        sb(t2, sp, 0x9);
        sb(t1, sp, 0xA);
        sb(t3, sp, 0xB);
        sw(t0, sp, 0x0);
        jt = t4.u();  // the target, read before the delay slot
        link(ctx, 0x576A1Cu);  // $ra = the return address
        lw(a0, s4, 232);
        call_ptr(ctx, jt);
    }
    // 0x00576a24 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0xD0);
    ld(s1, sp, 0xD8);
    ld(s2, sp, 0xE0);
    ld(s3, sp, 0xE8);
    ld(s4, sp, 0xF0);
    ld(ra, sp, 0xF8);
    sp = addiu(sp, 0x100);
}

// 0x00576A48 sub_576A48 -- 3176 bytes; leaf frame (no stack)
// [mpsReadPesHeader] MPS PES packet header (h, p, &used, mode) for stream_id >= 0xBC: the stream id and its kind into
// the PES record (+168, with a kind / sub-kind pair at +20 / +24 that tells private_stream_1 / 2 and padding apart),
// then the packet length -- 16 bits (a 6-byte start) when mode (the handle's +16, 2 after sub_577E68) is 2, else a
// 32-bit field (8 bytes); padding (0xBE) and private_stream_2 (0xBF) end there; the others go on with the MPEG-1 form
// (stuffing bytes, STD buffer, PTS / PTS + DTS markers) or the MPEG-2 PES header (flags, header length, PTS / DTS).
// *used = the header bytes (checked against a host walk of every movie's first packs).
void sub_576A48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00576a48
    enter(ctx, 41);  // entry check point + this block's cycles
    t4 = a1;
    v1 = si(-4);
    v0 = addiu(t4, 3);
    t6 = a2;
    t1 = v0 & v1;
    t3 = a3;
    v1 = subu(t4, t1);
    lb(t2, t1, 0);
    t1 = addiu(t1, 1);
    v1 = addiu(v1, 3);
    lbu(a1, t1, 0);
    t1 = addiu(t1, 1);
    lbu(a2, t1, 0);
    t1 = addiu(t1, 1);
    lbu(a3, t1, 0);
    t1 = addiu(t1, 1);
    lb(t0, t1, 0);
    t1 = addiu(t1, 1);
    lbu(v0, t1, 0);
    t1 = addiu(t1, 1);
    t2 = sll(t2, 8);
    t0 = sll(t0, 8);
    t2 = t2 | a1;
    lbu(a1, t1, 0);
    t0 = t0 | v0;
    t2 = sll(t2, 8);
    t1 = addiu(t1, 1);
    t2 = t2 | a2;
    t0 = sll(t0, 8);
    t2 = sll(t2, 8);
    a2 = sll(v1, 3);
    lbu(v1, t1, 0);
    t0 = t0 | a1;
    t2 = t2 | a3;
    t0 = sll(t0, 8);
    v0 = slti(a2, 24);
    a3 = addiu(a0, 168);
    t0 = t0 | v1;
    t2 = sllv(t2, a2);
    t1 = addiu(t1, 1);
    if (v0 != 0) {
        // 0x00576b58
        charge(ctx, 3);
        a1 = srl(t2, 24);
        t2 = sll(t2, 8);
        a2 = addiu(a2, 8);
    } else {
        // 0x00576aec
        charge(ctx, 3);
        a2 = addiu(a2, -24);
        v0 = 8;
        if (a2 == 0) {
            // 0x00576b10
            charge(ctx, 2);
            a1 = srl(t2, 24);
            t2 = t0;
        } else {
            // 0x00576af8
            charge(ctx, 6);
            v0 = subu(v0, a2);
            v0 = srlv(t0, v0);
            t2 = t2 | v0;
            a1 = srl(t2, 24);
            t2 = sllv(t0, a2);
        }
        // 0x00576b18
        charge(ctx, 15);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        t0 = t0 | v0;
    }
    // 0x00576b64
    charge(ctx, 5);
    v1 = addiu(a1, -224);
    sw(a1, a3, 16);
    v0 = sltiu(v1, 16);
    a0 = 1;
    if (v0 == 0) {
        // 0x00576b78
        charge(ctx, 4);
        v1 = addiu(a1, -192);
        v0 = sltiu(v1, 32);
        a0 = 0;
        if (v0 == 0) {
            // 0x00576b88
            charge(ctx, 3);
            v0 = 189;
            cc = a1 != v0;  // the condition, before the delay slot changes it
            v0 = 191;
            if (cc) {
                // 0x00576ba0
                charge(ctx, 2);
                cc = a1 != v0;  // the condition, before the delay slot changes it
                v0 = 190;
                if (cc) {
                    // 0x00576bb8
                    charge(ctx, 2);
                    if (a1 != v0) {
                        a0 = 4;
                    } else {
                        // 0x00576bc0
                        charge(ctx, 1);
                        a0 = 3;
                    }
                    // 0x00576bc4
                    charge(ctx, 1);
                    v1 = 0;
                } else {
                    // 0x00576ba8
                    charge(ctx, 3);
                    a0 = 2;
                    v1 = 2;
                }
            } else {
                // 0x00576b94
                charge(ctx, 3);
                a0 = 2;
                v1 = 1;
            }
        }
    }
    // 0x00576bc8
    charge(ctx, 4);
    v0 = 2;
    sw(a0, a3, 20);
    sw(v1, a3, 24);
    if (t3 != v0) {
        // 0x00576c70
        charge(ctx, 2);
        v0 = subu(0, a2);
        if (a2 == 0) {
            // 0x00576c90
            charge(ctx, 2);
            sw(t2, a3, 28);
            t2 = t0;
        } else {
            // 0x00576c78
            charge(ctx, 5);
            v0 = srlv(t0, v0);
            v0 = t2 | v0;
            t2 = sllv(t0, a2);
            sw(v0, a3, 28);
        }
        // 0x00576c98
        charge(ctx, 15);
        lb(t0, t1, 0);
        t1 = addiu(t1, 1);
        lbu(v0, t1, 0);
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v1, t1, 0);
        t0 = t0 | v0;
        t1 = addiu(t1, 1);
        t0 = sll(t0, 8);
        lbu(v0, t1, 0);
        t0 = t0 | v1;
        t5 = 8;
        t0 = sll(t0, 8);
        t1 = addiu(t1, 1);
        t0 = t0 | v0;
    } else {
        // 0x00576bd8
        charge(ctx, 3);
        v0 = slti(a2, 16);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(t2, 16);
        if (cc) {
            // 0x00576c58
            charge(ctx, 3);
            t2 = sll(t2, 16);
            sw(v0, a3, 28);
            a2 = addiu(a2, 16);
        } else {
            // 0x00576be4
            charge(ctx, 3);
            a2 = addiu(a2, -16);
            v0 = 16;
            if (a2 == 0) {
                // 0x00576c10
                charge(ctx, 3);
                v0 = srl(t2, 16);
                t2 = t0;
                sw(v0, a3, 28);
            } else {
                // 0x00576bf0
                charge(ctx, 7);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                v1 = srl(t2, 16);
                t2 = sllv(t0, a2);
                sw(v1, a3, 28);
            }
            // 0x00576c1c
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00576c64
        charge(ctx, 2);
        t5 = 6;
    }
    // 0x00576cd4
    charge(ctx, 4);
    v0 = addiu(a1, -190);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        // 0x00576ce4
        charge(ctx, 4);
        sw(t5, t6, 0);
        lw(v0, a3, 28);
        sw(v0, a3, 36);
        return;
    }
    a1 = 56;
    // 0x00576cf8
    charge(ctx, 2);
    a0 = 255;
    for (;;) {
        // 0x00576d50
        charge(ctx, 3);
        v0 = slti(a2, 25);
        v1 = srl(t2, 24);
        if (v0 == 0) {
            // 0x00576d5c
            charge(ctx, 3);
            v0 = subu(a1, a2);
            v0 = srlv(t0, v0);
            v1 = v1 | v0;
        }
        // 0x00576d68
        charge(ctx, 2);
        v0 = slti(a2, 31);
        if (v1 != a0) {
            break;
        }
        backedge(ctx);
        // 0x00576d00
        charge(ctx, 4);
        a2 = addiu(a2, 8);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 8);
        } else {
            // 0x00576d10
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
    }
    // 0x00576d70
    charge(ctx, 2);
    v1 = srl(t2, 30);
    if (v0 == 0) {
        // 0x00576d78
        charge(ctx, 4);
        v0 = 62;
        v0 = subu(v0, a2);
        v0 = srlv(t0, v0);
        v1 = v1 | v0;
    }
    // 0x00576d88
    charge(ctx, 3);
    v0 = 1;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = slti(a2, 29);
    if (!cc) {
        // 0x00576d94
        charge(ctx, 4);
        a2 = addiu(a2, 2);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 2);
        } else {
            // 0x00576da4
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00576de4
        charge(ctx, 3);
        v0 = 31;
        a1 = srl(t2, 31);
        if (a2 != v0) {
            // 0x00576e38
            charge(ctx, 2);
            a2 = addiu(a2, 1);
            t2 = sll(t2, 1);
        } else {
            // 0x00576df0
            charge(ctx, 17);
            t2 = t0;
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            a2 = 0;
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00576e40
        charge(ctx, 3);
        v0 = slti(a2, 19);
        a0 = srl(t2, 19);
        if (v0 != 0) {
            // 0x00576eb0
            charge(ctx, 2);
            t2 = sll(t2, 13);
            a2 = addiu(a2, 13);
        } else {
            // 0x00576e4c
            charge(ctx, 3);
            a2 = addiu(a2, -19);
            v0 = 13;
            if (a2 == 0) {
                // 0x00576e70
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x00576e58
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a0 = srl(t2, 19);
                t2 = sllv(t0, a2);
            }
            // 0x00576e74
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00576eb8
        charge(ctx, 5);
        a0 = sll(a0, 7);
        v0 = sll(a0, 3);
        if (a1 != 0) a0 = v0;
        sw(a0, a3, 32);
        v0 = slti(a2, 29);
    }
    // 0x00576ecc
    charge(ctx, 2);
    v1 = srl(t2, 28);
    if (v0 == 0) {
        // 0x00576ed4
        charge(ctx, 4);
        v0 = 60;
        v0 = subu(v0, a2);
        v0 = srlv(t0, v0);
        v1 = v1 | v0;
    }
    // 0x00576ee4
    charge(ctx, 3);
    v0 = 2;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (!cc) {
        // 0x00576ef0
        charge(ctx, 4);
        a2 = addiu(a2, 4);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 4);
        } else {
            // 0x00576f00
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00576f40
        charge(ctx, 3);
        v0 = slti(a2, 29);
        t3 = srl(t2, 29);
        if (v0 != 0) {
            // 0x00576fb0
            charge(ctx, 2);
            t2 = sll(t2, 3);
            a2 = addiu(a2, 3);
        } else {
            // 0x00576f4c
            charge(ctx, 3);
            a2 = addiu(a2, -29);
            v0 = 3;
            if (a2 == 0) {
                // 0x00576f70
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x00576f58
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                t3 = srl(t2, 29);
                t2 = sllv(t0, a2);
            }
            // 0x00576f74
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00576fb8
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x00576fc8
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577008
        charge(ctx, 3);
        v0 = slti(a2, 17);
        a1 = srl(t2, 17);
        if (v0 != 0) {
            // 0x00577078
            charge(ctx, 2);
            t2 = sll(t2, 15);
            a2 = addiu(a2, 15);
        } else {
            // 0x00577014
            charge(ctx, 3);
            a2 = addiu(a2, -17);
            v0 = 15;
            if (a2 == 0) {
                // 0x00577038
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x00577020
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a1 = srl(t2, 17);
                t2 = sllv(t0, a2);
            }
            // 0x0057703c
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577080
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x00577090
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005770d0
        charge(ctx, 3);
        v0 = slti(a2, 17);
        a0 = srl(t2, 17);
        if (v0 != 0) {
            // 0x00577100
            charge(ctx, 1);
            a2 = addiu(a2, 15);
        } else {
            // 0x005770dc
            charge(ctx, 3);
            a2 = addiu(a2, -17);
            v0 = 15;
            if (a2 != 0) {
                // 0x005770e8
                charge(ctx, 4);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a0 = srl(t2, 17);
            }
            // 0x005770f8
            charge(ctx, 2);
            t1 = addiu(t1, 4);
        }
        // 0x00577104
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = t3 & 0x7;
        if (!cc) {
            // 0x00577114
            charge(ctx, 2);
            a2 = addiu(a2, -32);
            t1 = addiu(t1, 4);
        }
        // 0x0057711c
        charge(ctx, 9);
        v1 = a1 & 0x7FFF;
        v1 = dsll(v1, 15);
        v0 = dsll(v0, 30);
        v0 = v0 | v1;
        v1 = si(-1);
        a0 = a0 & 0x7FFF;
        sd(v1, a3, 8);
        v0 = v0 | a0;
        goto L_00577680;
    }
    // 0x00577140
    charge(ctx, 2);
    if (v1 != v0) {
        a2 = addiu(a2, 8);
        // 0x00577668
        charge(ctx, 3);
        v0 = slti(a2, 32);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x00577674
            charge(ctx, 2);
            a2 = addiu(a2, -32);
            t1 = addiu(t1, 4);
        }
        // 0x0057767c
        charge(ctx, 1);
        sd(v0, a3, 8);
    L_00577680:
        charge(ctx, 1);
        sd(v0, a3, 0);
    } else {
        // 0x00577148
        charge(ctx, 4);
        a2 = addiu(a2, 4);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 4);
        } else {
            // 0x00577158
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577198
        charge(ctx, 3);
        v0 = slti(a2, 29);
        t3 = srl(t2, 29);
        if (v0 != 0) {
            // 0x00577208
            charge(ctx, 2);
            t2 = sll(t2, 3);
            a2 = addiu(a2, 3);
        } else {
            // 0x005771a4
            charge(ctx, 3);
            a2 = addiu(a2, -29);
            v0 = 3;
            if (a2 == 0) {
                // 0x005771c8
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x005771b0
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                t3 = srl(t2, 29);
                t2 = sllv(t0, a2);
            }
            // 0x005771cc
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577210
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x00577220
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577260
        charge(ctx, 3);
        v0 = slti(a2, 17);
        a1 = srl(t2, 17);
        if (v0 != 0) {
            // 0x005772d0
            charge(ctx, 2);
            t2 = sll(t2, 15);
            a2 = addiu(a2, 15);
        } else {
            // 0x0057726c
            charge(ctx, 3);
            a2 = addiu(a2, -17);
            v0 = 15;
            if (a2 == 0) {
                // 0x00577290
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x00577278
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a1 = srl(t2, 17);
                t2 = sllv(t0, a2);
            }
            // 0x00577294
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005772d8
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x005772e8
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577328
        charge(ctx, 3);
        v0 = slti(a2, 17);
        a0 = srl(t2, 17);
        if (v0 != 0) {
            // 0x00577398
            charge(ctx, 2);
            t2 = sll(t2, 15);
            a2 = addiu(a2, 15);
        } else {
            // 0x00577334
            charge(ctx, 3);
            a2 = addiu(a2, -17);
            v0 = 15;
            if (a2 == 0) {
                // 0x00577358
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x00577340
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a0 = srl(t2, 17);
                t2 = sllv(t0, a2);
            }
            // 0x0057735c
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005773a0
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x005773b0
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005773f0
        charge(ctx, 11);
        v0 = t3 & 0x7;
        v1 = a1 & 0x7FFF;
        v1 = dsll(v1, 15);
        v0 = dsll(v0, 30);
        v0 = v0 | v1;
        a0 = a0 & 0x7FFF;
        a2 = addiu(a2, 4);
        v0 = v0 | a0;
        v1 = slti(a2, 32);
        sd(v0, a3, 0);
        if (v1 != 0) {
            // 0x00577460
            charge(ctx, 1);
            t2 = sll(t2, 4);
        } else {
            // 0x0057741c
            charge(ctx, 17);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577464
        charge(ctx, 3);
        v0 = slti(a2, 29);
        t3 = srl(t2, 29);
        if (v0 != 0) {
            // 0x005774d8
            charge(ctx, 2);
            t2 = sll(t2, 3);
            a2 = addiu(a2, 3);
        } else {
            // 0x00577470
            charge(ctx, 3);
            a2 = addiu(a2, -29);
            v0 = 3;
            if (a2 == 0) {
                // 0x00577498
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x0057747c
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                t3 = srl(t2, 29);
                t2 = sllv(t0, a2);
            }
            // 0x0057749c
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005774e0
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x005774f0
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x00577530
        charge(ctx, 3);
        v0 = slti(a2, 17);
        a1 = srl(t2, 17);
        if (v0 != 0) {
            // 0x005775a0
            charge(ctx, 2);
            t2 = sll(t2, 15);
            a2 = addiu(a2, 15);
        } else {
            // 0x0057753c
            charge(ctx, 3);
            a2 = addiu(a2, -17);
            v0 = 15;
            if (a2 == 0) {
                // 0x00577560
                charge(ctx, 1);
                t2 = t0;
            } else {
                // 0x00577548
                charge(ctx, 6);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a1 = srl(t2, 17);
                t2 = sllv(t0, a2);
            }
            // 0x00577564
            charge(ctx, 15);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005775a8
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        if (v0 != 0) {
            t2 = sll(t2, 1);
        } else {
            // 0x005775b8
            charge(ctx, 16);
            a2 = addiu(a2, -32);
            t2 = sllv(t0, a2);
            lb(t0, t1, 0);
            t1 = addiu(t1, 1);
            lbu(v0, t1, 0);
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v1, t1, 0);
            t0 = t0 | v0;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            lbu(v0, t1, 0);
            t0 = t0 | v1;
            t1 = addiu(t1, 1);
            t0 = sll(t0, 8);
            t0 = t0 | v0;
        }
        // 0x005775f8
        charge(ctx, 3);
        v0 = slti(a2, 17);
        a0 = srl(t2, 17);
        if (v0 != 0) {
            // 0x00577628
            charge(ctx, 1);
            a2 = addiu(a2, 15);
        } else {
            // 0x00577604
            charge(ctx, 3);
            a2 = addiu(a2, -17);
            v0 = 15;
            if (a2 != 0) {
                // 0x00577610
                charge(ctx, 4);
                v0 = subu(v0, a2);
                v0 = srlv(t0, v0);
                t2 = t2 | v0;
                a0 = srl(t2, 17);
            }
            // 0x00577620
            charge(ctx, 2);
            t1 = addiu(t1, 4);
        }
        // 0x0057762c
        charge(ctx, 4);
        a2 = addiu(a2, 1);
        v0 = slti(a2, 32);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = t3 & 0x7;
        if (!cc) {
            // 0x0057763c
            charge(ctx, 2);
            a2 = addiu(a2, -32);
            t1 = addiu(t1, 4);
        }
        // 0x00577644
        charge(ctx, 8);
        v1 = a1 & 0x7FFF;
        v0 = dsll(v0, 30);
        v1 = dsll(v1, 15);
        v0 = v0 | v1;
        a0 = a0 & 0x7FFF;
        v0 = v0 | a0;
        sd(v0, a3, 8);
    }
    // 0x00577684 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = addiu(a2, 7);
    v0 = sra(v0, 3);
    v0 = addu(t1, v0);
    v0 = addiu(v0, -8);
    v0 = subu(v0, t4);
    sw(v0, t6, 0);
    lw(v1, a3, 28);
    v1 = addu(v1, t5);
    v1 = subu(v1, v0);
    sw(v1, a3, 36);
}

// 0x005776B0 sub_5776B0 -- 112 bytes; leaf frame (no stack)
// [mpsStartCodeClass] MPEG program-stream start-code class of p: 00 00 01 BA -> 0x10000 (pack), 00 00 01 BB -> 0x20000
// (system header), 00 00 01 B9 -> 0x80000 (program end), 00 00 01 xx with xx >= 0xBC -> 0x40000 (a PES packet),
// anything else 0.
void sub_5776B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005776b0
    enter(ctx, 3);  // entry check point + this block's cycles
    lbu(v0, a0, 0);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x005776bc
        charge(ctx, 3);
        lbu(v0, a0, 1);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x005776c8
            charge(ctx, 4);
            lbu(v1, a0, 2);
            v0 = 1;
            cc = v1 != v0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x005776d8
                charge(ctx, 4);
                lbu(a0, a0, 3);
                v1 = 186;
                v0 = 0x10000;
                if (a0 != v1) {
                    // 0x005776e8
                    charge(ctx, 3);
                    v0 = slti(a0, 187);
                    if (v0 == 0) {
                        v1 = 187;
                        // 0x00577700
                        charge(ctx, 1);
                        v0 = 0x20000;
                    } else {
                        // 0x005776f4
                        charge(ctx, 3);
                        v1 = 185;
                        v0 = 0x80000;
                    }
                    // 0x00577704
                    charge(ctx, 2);
                    cc = a0 == v1;  // the condition, before the delay slot changes it
                    v1 = sltiu(a0, 188);
                    if (!cc) {
                        // 0x0057770c
                        charge(ctx, 2);
                        v0 = 0x40000;
                        if (v1 != 0) {
                            // 0x00577714
                            charge(ctx, 1);
                            v0 = 0;
                        }
                    }
                }
            }
        }
    }
    // 0x00577718 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00577720 sub_577720 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsIsMpeg1Pack] MPS probe (buf, len): finds a pack start code (sub_577780 for 0xBA) and returns 1 when the byte
// after it has 00 in its top two bits (the MPEG-1 0010 pack layout; MPEG-2 starts 01), else 0. No caller.
void sub_577720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00577720
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 186;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x577738u, gen::fn_sub_577780_00577780);
    a1 = v0;
    cc = a1 == 0;  // the condition, before the delay slot changes it
    a1 = addiu(a1, 4);
    if (!cc) {
        // 0x0057774c
        charge(ctx, 4);
        v1 = subu(a1, s1);
        s0 = subu(s0, v1);
        v0 = 0;
        if (i64(s0) > 0) {
            // 0x0057775c
            charge(ctx, 3);
            lbu(v0, a1, 0);
            v0 = srl(v0, 6);
            v0 = sltiu(v0, 1);
        }
    }
    // 0x00577768 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00577780 sub_577780 -- 104 bytes; leaf frame (no stack)
// [mpsFindStartCode] Byte search for the start code 00 00 01 <code> in (buf, len); returns its address or 0.
void sub_577780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00577780
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 3;
    a2 = a2 & 0xFF;
    v0 = slt(v0, a1);
    a3 = 0;
    if (v0 != 0) {
        // 0x00577794
        charge(ctx, 1);
        t0 = 1;
        for (;;) {
            // 0x00577798
            charge(ctx, 3);
            lbu(v0, a0, 0);
            if (v0 != 0) {
                a3 = addiu(a3, 1);
            } else {
                // 0x005777a4
                charge(ctx, 3);
                lbu(v0, a0, 1);
                if (v0 != 0) {
                    a3 = addiu(a3, 1);
                    goto L_005777cc;
                }
                // 0x005777b0
                charge(ctx, 3);
                lbu(v0, a0, 2);
                if (v0 != t0) {
                    a3 = addiu(a3, 1);
                    goto L_005777cc;
                }
                // 0x005777bc
                charge(ctx, 3);
                lbu(v1, a0, 3);
                v0 = a0;
                if (v1 != a2) {
                    // 0x005777c8
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                    goto L_005777cc;
                }
                break;
            }
        L_005777cc:
            charge(ctx, 4);
            v0 = addiu(a3, 3);
            v0 = slt(v0, a1);
            a0 = addiu(a0, 1);
            if (v0 == 0) {
                goto L_005777dc;
            }
            backedge(ctx);
        }
        // 0x005777e0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005777dc:
    charge(ctx, 1);
    v0 = 0;
    // 0x005777e0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005777E8 __env_lock_4 -- 8 bytes; leaf frame (no stack)
// [mpsInitHookB] An empty init hook (jr $ra / nop) MPS's init calls. The FLIRT name is a false match of a short code
// shape; the role is read from the instructions.
void __env_lock_4(EEContext& ctx) {
    using namespace hg;
    // 0x005777e8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005777F8 sub_5777F8 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsGetPackInfo] MPS: copies the handle's 16-byte pack record (+24) out, after the handle check sub_577DB0 (tail1);
// on failure MPS raises 0xFF020201.
void sub_5777F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005777f8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x57780Cu, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    if (v0 != 0) {
        // 0x00577820
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x201;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x00577838
    charge(ctx, 9);
    ld(v1, s0, 24);
    ld(ra, sp, 0x10);
    sd(v1, s1, 0);
    ld(a0, s0, 32);
    ld(s0, sp, 0x0);
    sd(a0, s1, 8);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00577860 sub_577860 -- 176 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mpsGetStreamInfo] MPS: copies stream-info slot i (32 bytes at +72 + 32 * i) out, after the handle check sub_577DB0
// (tail1); on failure MPS raises 0xFF020202.
void sub_577860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577860
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x57787Cu, gen::fn_sub_577DB0_00577db0);
    s0 = sll(s0, 5);
    a1 = lui(0xFF02);
    s0 = addu(s0, s1);
    a0 = 0;
    a1 = a1 | 0x202;
    if (v0 != 0) {
        // 0x0057789c
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x005778b8
    charge(ctx, 22);
    ldl(v1, s0, 79);
    ldr(v1, s0, 72);
    ldl(a0, s0, 87);
    ldr(a0, s0, 80);
    ldl(a1, s0, 95);
    ldr(a1, s0, 88);
    ldl(a2, s0, 103);
    ldr(a2, s0, 96);
    sdl(v1, s2, 7);
    sdr(v1, s2, 0);
    sdl(a0, s2, 15);
    sdr(a0, s2, 8);
    sdl(a1, s2, 23);
    sdr(a1, s2, 16);
    sdl(a2, s2, 31);
    sdr(a2, s2, 24);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00577910 sub_577910 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsGetSystemInfo] MPS: copies the 32-byte system-header record (+40) out, after the handle check sub_577DB0 (tail1);
// on failure MPS raises 0xFF020202.
void sub_577910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577910
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x577924u, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    if (v0 != 0) {
        // 0x00577938
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x202;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x00577950
    charge(ctx, 21);
    ldl(v1, s0, 47);
    ldr(v1, s0, 40);
    ldl(a0, s0, 55);
    ldr(a0, s0, 48);
    ldl(a1, s0, 63);
    ldr(a1, s0, 56);
    ldl(a2, s0, 71);
    ldr(a2, s0, 64);
    sdl(v1, s1, 7);
    sdr(v1, s1, 0);
    sdl(a0, s1, 15);
    sdr(a0, s1, 8);
    sdl(a1, s1, 23);
    sdr(a1, s1, 16);
    sdl(a2, s1, 31);
    sdr(a2, s1, 24);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005779A8 sub_5779A8 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsGetPesInfo] MPS: copies the 40-byte PES record (+168) out, after the handle check sub_577DB0 (tail1); on failure
// MPS raises 0xFF020203.
void sub_5779A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005779a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5779BCu, gen::fn_sub_577DB0_00577db0);
    a1 = lui(0xFF02);
    a0 = 0;
    if (v0 != 0) {
        // 0x005779d0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x203;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_577BE0_00577be0(ctx);  // tail call
        return;
    }
    // 0x005779e8
    charge(ctx, 15);
    ld(v1, s0, 168);
    ld(ra, sp, 0x10);
    sd(v1, s1, 0);
    ld(a0, s0, 176);
    sd(a0, s1, 8);
    ld(v1, s0, 184);
    sd(v1, s1, 16);
    ld(a0, s0, 192);
    sd(a0, s1, 24);
    ld(v1, s0, 200);
    ld(s0, sp, 0x0);
    sd(v1, s1, 32);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00577A38 sub_577A38 -- 120 bytes; frame 0x10: ra sp+0x0
// [mpsInit] MPS init (n, work): stores the banner at 0x99B2B0, checks a build-time word (== 4) and otherwise jumps to
// address 0xFFFFFFFF (a deliberate trap the recompiled body reproduces); lays out the work block (sub_577AB0) and runs
// the two (empty) init hooks.
void sub_577A38(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577a38
    enter(ctx, 11);  // entry check point + this block's cycles
    a2 = 0x7C0000;
    v1 = 0x9A0000;
    lbu(a3, a2, 31240);  // 0x7C7A08
    a2 = 4;
    v0 = 0x7C0000;
    sp = addiu(sp, -0x10);
    v1 = addiu(v1, -19792);  // &0x99B2B0
    v0 = addiu(v0, 31160);  // "\nCRI MPS/PS2EE Ver.1.924 Build:Mar  1 2005 10:53:57\n"
    sd(ra, sp, 0x0);
    sw(v0, v1, 0);  // 0x99B2B0
    if (a3 != a2) {
        // 0x00577a64
        charge(ctx, 1);
        for (;;) {
            // 0x00577a68
            charge(ctx, 5);
            at = si(-1);
            jalr(ctx, 0x577A6Cu, at.u());
            backedge(ctx);
        }
    }
    // 0x00577a80
    charge(ctx, 4);
    jal(ctx, 0x577A80u, gen::fn_sub_577AB0_00577ab0);
    ld(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00577a90
        charge(ctx, 6);
        jal(ctx, 0x577A90u, gen::fn___env_lock_3_00575948);
        jal(ctx, 0x577A98u, gen::fn___env_lock_4_005777e8);
        v0 = 0;
        ld(ra, sp, 0x0);
    }
    // 0x00577aa8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00577AB0 sub_577AB0 -- 140 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsSetupWork] MPS work layout (n, work): the work slot 0x7B2998 = work, 64 * n + 4 words cleared, the global error
// record reset (sub_577BB8), the handle count (+12) and every handle free (state 1, 256-byte stride).
void sub_577AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577ab0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a1;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    sd(s1, sp, 0x8);
    s1 = a0;
    s0 = addiu(s0, 10648);  // &0x7B2998
    sd(ra, sp, 0x10);
    a2 = sll(s1, 6);
    sw(v0, s0, 0);  // 0x7B2998
    a0 = v0;
    a2 = addiu(a2, 4);
    a1 = 0;
    jal(ctx, 0x577AE0u, gen::fn_sub_575880_00575880);
    link(ctx, 0x577AE8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7B2998
    call(ctx, gen::fn_sub_577BB8_00577bb8);
    lw(v0, s0, 0);  // 0x7B2998
    sw(s1, v0, 12);
    v0 = addiu(v0, 16);
    if (i64(s1) > 0) {
        // 0x00577b00
        charge(ctx, 2);
        a0 = s1;
        v1 = 1;
        for (;;) {
            // 0x00577b08
            charge(ctx, 7);
            a0 = addiu(a0, -1);
            sw(v1, v0, 0);
            v0 = addiu(v0, 256);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00577b24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00577DD8 sub_577DD8 -- 52 bytes; frame 0x10: ra sp+0x0
// [mpsCreate] MPS create: the first free handle (sub_577E10) initialised by sub_577E68, or 0.
void sub_577DD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577dd8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x577DE0u, gen::fn_sub_577E10_00577e10);
    v1 = v0;
    a0 = v1;
    if (v1 == 0) {
        // 0x00577e00
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00577df4
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_577E68_00577e68(ctx);  // tail call
}

// 0x00577E68 sub_577E68 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mpsInitHandle] Initialises an MPS handle: 64 words cleared, state 2 (valid), its error record reset (loc_577BD0, the
// mid-body entry of sub_577BB8), +16 = 2, the pack record (sub_577F08) and the four 32-byte records (sub_577F20) and
// the PES record (sub_577F48) reset, the parser +212 = sub_575B48, the callback words cleared.
void sub_577E68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00577e68
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = 2;
    sd(ra, sp, 0x10);
    a2 = 64;
    jal(ctx, 0x577E84u, gen::fn_sub_575880_00575880);
    sw(s1, s0, 0);
    a0 = addiu(s0, 4);
    link(ctx, 0x577E90u);
    gen::fn_sub_577BB8_00577bb8_at_00577bd0(ctx);
    sw(s1, s0, 16);
    a0 = addiu(s0, 24);
    jal(ctx, 0x577E9Cu, gen::fn_sub_577F08_00577f08);
    a0 = addiu(s0, 40);
    jal(ctx, 0x577EA4u, gen::fn_sub_577F20_00577f20);
    a0 = addiu(s0, 72);
    jal(ctx, 0x577EACu, gen::fn_sub_577F20_00577f20);
    a0 = addiu(s0, 104);
    jal(ctx, 0x577EB4u, gen::fn_sub_577F20_00577f20);
    a0 = addiu(s0, 136);
    jal(ctx, 0x577EBCu, gen::fn_sub_577F20_00577f20);
    a0 = addiu(s0, 168);
    jal(ctx, 0x577EC4u, gen::fn_sub_577F48_00577f48);
    sw(zero, s0, 208);
    v0 = 0x570000;
    sw(zero, s0, 216);
    v0 = addiu(v0, 23368);  // &sub_575B48
    sw(zero, s0, 220);
    sw(v0, s0, 212);
    v0 = s0;
    sw(zero, s0, 224);
    sw(zero, s0, 228);
    sw(zero, s0, 232);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
