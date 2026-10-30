// Slice tail1: CRI MWSFD (the Sofdec movie player layer, mwPly*): the header-sector callbacks.
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions only (no CRI material was
// opened). Pair tests: tests/game/test_tail1.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/tail1.h"

namespace p3fes::recomp_gen {
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn___gthread_get_ee_key_value_0057f730(p3fes::EEContext&);
void fn_sub_57F0C0_0057f0c0(p3fes::EEContext&);
void fn_sub_57F0F0_0057f0f0(p3fes::EEContext&);
void fn_sub_57F218_0057f218(p3fes::EEContext&);
void fn_sub_57F258_0057f258(p3fes::EEContext&);
void fn_sub_57F2C8_0057f2c8(p3fes::EEContext&);
void fn_sub_57F2F8_0057f2f8(p3fes::EEContext&);
void fn_sub_57F328_0057f328(p3fes::EEContext&);
void fn_sub_57F390_0057f390(p3fes::EEContext&);
void fn_sub_57F3E0_0057f3e0(p3fes::EEContext&);
void fn_sub_57F528_0057f528(p3fes::EEContext&);
void fn_sub_57F5F8_0057f5f8(p3fes::EEContext&);
void fn_sub_582A08_00582a08(p3fes::EEContext&);
void fn_sub_599100_00599100(p3fes::EEContext&);
void fn_sub_59D098_0059d098(p3fes::EEContext&);
void fn_sub_59D160_0059d160(p3fes::EEContext&);
void fn_sub_59D2B0_0059d2b0(p3fes::EEContext&);
void fn_sub_59D3A0_0059d3a0(p3fes::EEContext&);
void fn_sub_59DAC0_0059dac0(p3fes::EEContext&);
void fn_sub_59DB10_0059db10(p3fes::EEContext&);
void fn_sub_59DCB8_0059dcb8(p3fes::EEContext&);
void fn_sub_59E298_0059e298(p3fes::EEContext&);
void fn_sub_59E5E0_0059e5e0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace tail1;  // the named offsets of p3fes/game/tail1.h
namespace gen = ::p3fes::recomp_gen;

// 0x0057F0C0 sub_57F0C0 -- 48 bytes; frame 0x20: ra sp+0x10
// [mwsfdHdrSysWord16] Header system word +16 (the SFH getter sub_59DCB8) of a view, or -1.
void sub_57F0C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f0c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x57F0C8u, gen::fn_sub_59DCB8_0059dcb8);
    v1 = 1;
    lw(a1, sp, 0x0);
    a0 = v0 ^ v1;
    ld(ra, sp, 0x10);
    v0 = si(-1);
    if (a0 == 0) v0 = a1;
    sp = addiu(sp, 0x20);
}

// 0x0057F0F0 sub_57F0F0 -- 296 bytes; frame 0x60: s5 sp+0x38, s1 sp+0x18, s3 sp+0x28, s0 sp+0x10, s2 sp+0x20, s4 sp+0x30, s6 sp+0x40, s7 sp+0x48, ra sp+0x50
// [mwsfdProbeHdrInf] mwPlyGetHdrInf's header probe: looks for a Sofdec header in the 2nd and 3rd 2,048-byte sectors of
// (buf, size) (only when size >= 2,048); on the first one found, out[5..8] = system word +16, the video kind code
// (sub_57F258), system bytes +2 and +1; out[5] (and out[6]) = -1 for a sector that is not one.
void sub_57F0F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f0f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = si(-1);
    sd(s5, sp, 0x38);
    s5 = a1;
    sd(s1, sp, 0x18);
    s1 = a2;
    v1 = slti(s5, 2048);
    sd(s3, sp, 0x28);
    sd(s0, sp, 0x10);
    s3 = a0;
    sd(s2, sp, 0x20);
    sd(s4, sp, 0x30);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x50);
    sw(v0, s1, 20);  // out[5]
    if (v1 == 0) {
        // 0x0057f134
        charge(ctx, 2);
        s4 = 2;
        if (s3 == 0) {
            goto L_0057f1ec;
        }
        // 0x0057f13c
        charge(ctx, 5);
        s7 = 1;
        s6 = si(-1);
        s2 = 2048;
        a0 = addu(s3, s2);
        for (;;) {
            // 0x0057f150
            charge(ctx, 7);
            a1 = subu(s5, s2);
            jal(ctx, 0x57F150u, gen::fn_sub_59D098_0059d098);
            s2 = addiu(s2, 2048);
            s0 = v0;
            a1 = sp;
            a0 = s0;
            if (s0 != 0) {
                // 0x0057f16c
                charge(ctx, 5);
                jal(ctx, 0x57F16Cu, gen::fn_sub_59D2B0_0059d2b0);
                v1 = v0;
                a0 = s0;
                if (v1 == s7) {
                    // 0x0057f180
                    charge(ctx, 3);
                    lw(v0, sp, 0x0);
                    if (v0 == v1) {
                        goto L_0057f18c_6;
                    }
                    sw(s6, s1, 20);
                    goto L_0057f1d4;
                }
                // 0x0057f1d0
                charge(ctx, 1);
                sw(s6, s1, 20);
            L_0057f1d4:
                charge(ctx, 2);
                link(ctx, 0x57F1D4u);  // $ra first: the delay slot below depends on it
                sw(s6, s1, 24);
                call(ctx, gen::fn_sub_59D160_0059d160);
                goto L_0057f1dc;
            }
        L_0057f1dc:
            charge(ctx, 4);
            s4 = addiu(s4, 1);
            v0 = slti(s4, 4);
            a0 = addu(s3, s2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        goto L_0057f1ec;
    }
L_0057f1ec:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0057f1f0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
    return;
L_0057f18c_6:
    charge(ctx, 16);
    jal(ctx, 0x57F18Cu, gen::fn_sub_57F0C0_0057f0c0);
    a0 = s0;
    link(ctx, 0x57F198u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 20);  // out[5]
    call(ctx, gen::fn_sub_57F258_0057f258);
    a0 = s0;
    link(ctx, 0x57F1A4u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 24);
    call(ctx, gen::fn_sub_57F2F8_0057f2f8);
    a0 = s0;
    link(ctx, 0x57F1B0u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 28);
    call(ctx, gen::fn_sub_57F2C8_0057f2c8);
    a0 = s0;
    link(ctx, 0x57F1BCu);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 32);
    call(ctx, gen::fn_sub_59D160_0059d160);
    ld(s0, sp, 0x10);
    // 0x0057f1f0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x0057F218 sub_57F218 -- 60 bytes; frame 0x10: ra sp+0x0
// [mwsfdGetKindCode] The player's current kind code (ring entry at +184, sub_582A08), with 81 and 97 reported as 65.
void sub_57F218(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f218
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x57F220u);  // $ra first: the delay slot below depends on it
    lw(a1, a0, mwsfd::kRingRead);
    call(ctx, gen::fn_sub_582A08_00582a08);
    v1 = v0;
    v0 = 81;
    a0 = 97;
    if (v1 != v0) {
        // 0x0057f238
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (v1 == a0) {
            goto L_0057f240;
        }
        // 0x0057f248 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = v1;
        sp = addiu(sp, 0x10);
        return;
    }
L_0057f240:
    charge(ctx, 2);
    v1 = 65;
    ld(ra, sp, 0x0);
    // 0x0057f248 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x0057F258 sub_57F258 -- 112 bytes; frame 0x20: ra sp+0x10
// [mwsfdHdrKindCode] Video kind code of a header: the first video stream's byte +39 (sub_59E5E0, version >= 2.10)
// through the jump table 0x7C8430: 1 -> 33, 3 -> 81, 6 -> 97, 0 / 2 / 4 / 5 / 7 / 8 and a missing byte -> 17.
void sub_57F258(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057f258
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 224;
    sd(ra, sp, 0x10);
    a2 = sp;
    jal(ctx, 0x57F264u, gen::fn_sub_59E5E0_0059e5e0);
    v1 = 1;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 17;
    if (!cc) {
        // 0x0057f278
        charge(ctx, 4);
        lw(v1, sp, 0x0);
        v0 = sltiu(v1, 9);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 17;
        if (!cc) {
            // 0x0057f288
            charge(ctx, 6);
            v0 = sll(v1, 2);
            v1 = 0x7D0000;
            v1 = addu(v1, v0);
            lw(v1, v1, -31696);
            switch (v1.u()) {
            case 0x57F2A0u:  // table[1]
                // 0x0057f2a0
                charge(ctx, 2);
                v0 = 33;
                break;
            case 0x57F2A8u:  // table[3]
                // 0x0057f2a8
                charge(ctx, 2);
                v0 = 81;
                break;
            case 0x57F2B0u:  // table[6]
                // 0x0057f2b0
                charge(ctx, 2);
                v0 = 97;
                break;
            case 0x57F2B8u:  // table[0, 2, 4, 5, 7, 8]
                // 0x0057f2b8
                charge(ctx, 1);
                v0 = 17;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    }
    // 0x0057f2bc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0057F2C8 sub_57F2C8 -- 48 bytes; frame 0x20: ra sp+0x10
// [mwsfdHdrSysByte1] Header system byte +1 (sub_59DAC0), or -1.
void sub_57F2C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f2c8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x57F2D0u, gen::fn_sub_59DAC0_0059dac0);
    v1 = 1;
    lw(a1, sp, 0x0);
    a0 = v0 ^ v1;
    ld(ra, sp, 0x10);
    v0 = si(-1);
    if (a0 == 0) v0 = a1;
    sp = addiu(sp, 0x20);
}

// 0x0057F2F8 sub_57F2F8 -- 48 bytes; frame 0x20: ra sp+0x10
// [mwsfdHdrSysByte2] Header system byte +2 (sub_59DB10), or -1.
void sub_57F2F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f2f8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x57F300u, gen::fn_sub_59DB10_0059db10);
    v1 = 1;
    lw(a1, sp, 0x0);
    a0 = v0 ^ v1;
    ld(ra, sp, 0x10);
    v0 = si(-1);
    if (a0 == 0) v0 = a1;
    sp = addiu(sp, 0x20);
}

// 0x0057F328 sub_57F328 -- 100 bytes; leaf frame (no stack)
// [mwsfdResetHdrRing] Resets the player's header ring: count, read and write positions 0; each of the 8 entries (20
// bytes at +192): valid, index, flag and system word 0, kind code 17.
void sub_57F328(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0057f328
    enter(ctx, 10);  // entry check point + this block's cycles
    sw(zero, a0, mwsfd::kHdrCount);
    t3 = 17;
    sw(zero, a0, mwsfd::kRingRead);
    a1 = addiu(a0, 208);
    sw(zero, a0, mwsfd::kRingWrite);
    t2 = addiu(a0, 4);
    t1 = addiu(a0, 8);
    t0 = addiu(a0, 12);
    a3 = 0;
    a2 = 7;
    for (;;) {
        // 0x0057f350
        charge(ctx, 13);
        v0 = addiu(a3, 192);
        a3 = addiu(a3, 20);
        a0 = addu(t0, v0);
        v1 = addu(t2, v0);
        a2 = addiu(a2, -1);
        v0 = addu(t1, v0);
        sw(zero, a1, -16);
        sw(zero, v1, 0);
        sw(zero, v0, 0);
        sw(zero, a0, 0);
        sw(t3, a1, 0);
        a1 = addiu(a1, 20);
        if (i64(a2) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0057f384
    charge(ctx, 2);
}

// 0x0057F390 sub_57F390 -- 76 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10, s1 sp+0x8
// [mwsfdSetHdrCallback] Installs the header-sector callback on the player's SFD handle (+60): parameter 75 =
// sub_57F3E0, parameter 76 = the player (sub_599100).
void sub_57F390(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f390
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0x580000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a2 = addiu(a2, -3104);  // &sub_57F3E0
    sd(s1, sp, 0x8);
    a1 = 75;
    lw(s1, s0, mwsfd::kSfdHandle);
    a0 = s1;
    jal(ctx, 0x57F3B4u, gen::fn_sub_599100_00599100);
    a0 = s1;
    a2 = s0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = 76;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_599100_00599100(ctx);  // tail call
}

// 0x0057F3E0 sub_57F3E0 -- 324 bytes; frame 0x40: s3 sp+0x28, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s4 sp+0x30, ra sp+0x38
// [mwsfdOnHeader] The header-sector callback (player, buf, size), called by SFD for every header sector: counts it
// (+180); a Sofdec header of at least 2,048 bytes becomes the next ring entry (+188, mod 8): {1, number, sub_57F528,
// system word +16, kind code}.
void sub_57F3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057f3e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = slti(a2, 2048);
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s0, sp, 0x10);
    a0 = a1;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(v0, s3, mwsfd::kHdrCount);
    v0 = addiu(v0, 1);
    sw(v0, s3, mwsfd::kHdrCount);
    if (v1 == 0) {
        // 0x0057f418
        charge(ctx, 2);
        if (a0 == 0) {
            ld(s0, sp, 0x10);
        } else {
            // 0x0057f420
            charge(ctx, 6);
            a1 = a2;
            jal(ctx, 0x57F420u, gen::fn_sub_59D098_0059d098);
            s2 = v0;
            a1 = sp;
            a0 = s2;
            if (s2 == 0) {
                goto L_0057f504;
            }
            // 0x0057f438
            charge(ctx, 6);
            jal(ctx, 0x57F438u, gen::fn_sub_59D2B0_0059d2b0);
            v1 = v0;
            v0 = 1;
            a0 = s2;
            if (v1 == v0) {
                // 0x0057f450
                charge(ctx, 3);
                lw(s4, sp, 0x0);
                if (s4 != v1) {
                    goto L_0057f45c;
                }
                // 0x0057f470
                charge(ctx, 37);
                a0 = s2;
                jal(ctx, 0x57F470u, gen::fn_sub_57F528_0057f528);
                a0 = s2;
                s1 = v0;
                jal(ctx, 0x57F47Cu, gen::fn_sub_57F0C0_0057f0c0);
                a0 = s2;
                s0 = v0;
                jal(ctx, 0x57F488u, gen::fn_sub_57F258_0057f258);
                lw(a1, s3, mwsfd::kRingWrite);
                lw(a2, s3, mwsfd::kHdrCount);
                a0 = s2;
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                a2 = addiu(a2, -1);
                v1 = sll(v1, 2);
                a1 = addiu(v1, 192);
                v1 = addu(v1, s3);
                t1 = addu(s3, a1);
                a3 = t1;
                t0 = a3;
                sw(a2, a3, 4);
                a1 = t0;
                sw(s1, t0, 8);
                sw(s0, a1, 12);
                sw(v0, v1, 208);
                sw(s4, t1, 0);
                lw(v1, s3, mwsfd::kRingWrite);
                a1 = addiu(v1, 1);
                v1 = addiu(v1, 8);
                a2 = slti(a1, 0);
                v0 = a1;
                if (a2 != 0) v0 = v1;
                v0 = sra(v0, 3);
                v0 = sll(v0, 3);
                a1 = subu(a1, v0);
                link(ctx, 0x57F4FCu);  // $ra first: the delay slot below depends on it
                sw(a1, s3, mwsfd::kRingWrite);
                call(ctx, gen::fn_sub_59D160_0059d160);
                goto L_0057f504;
            }
        L_0057f45c:
            charge(ctx, 4);
            jal(ctx, 0x57F45Cu, gen::fn_sub_59D160_0059d160);
            ld(s0, sp, 0x10);
        }
        // 0x0057f508 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0057f504:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0057f508 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0057F528 sub_57F528 -- 116 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// [mwsfdHdrVideoFlag3] True when the header lists a video stream 0xE0 (sub_59D3A0) whose entry byte +33 (sub_59E298) is
// 3.
void sub_57F528(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0057f528
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 224;
    a2 = sp;
    sd(s1, sp, 0x18);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    jal(ctx, 0x57F540u, gen::fn_sub_59D3A0_0059d3a0);
    a0 = v0;
    v1 = 1;
    v0 = 0;
    if (a0 == v1) {
        // 0x0057f558
        charge(ctx, 3);
        lw(s0, sp, 0x0);
        if (s0 == a0) {
            // 0x0057f564
            charge(ctx, 6);
            a0 = s1;
            a1 = 224;
            a2 = addiu(sp, 0x4);
            jal(ctx, 0x57F56Cu, gen::fn_sub_59E298_0059e298);
            cc = v0 != s0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x0057f57c
                charge(ctx, 3);
                lw(v0, sp, 0x4);
                v0 = v0 ^ 0x3;
                v0 = sltiu(v0, 1);
            }
            goto L_0057f588;
        }
        ld(s0, sp, 0x10);
        // 0x0057f58c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0057f588:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0057f58c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0057F5F8 sub_57F5F8 -- 8 bytes; leaf frame (no stack)
// [mwsfdGetRingRead] Returns the player's ring read position (+184). Byte-identical to sub_5335A0 of the CRI band.
void sub_57F5F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0057f5f8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, mwsfd::kRingRead);
}

// 0x0057F730 __gthread_get_ee_key_value -- 12 bytes; leaf frame (no stack)
// [mwsfdGetVersionStr] Returns the module's version banner string in $v0 (the 12-byte "return a constant address"
// shape). The FLIRT name is a false match (the same few instructions as the SDK function; this is CRI code). MWSFD:
// "MWSFD/PS2EE Ver.3.50".
void __gthread_get_ee_key_value(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057f730
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7D0000;
    v0 = addiu(v0, -31600);  // "\nMWSFD/PS2EE Ver.3.50 Build:Mar  1 2005 10:54:15\n"
}

// 0x0057F740 __gthread_get_ee_key_use -- 12 bytes; leaf frame (no stack)
// [mwsfdGetWork] Returns the address of the MWSFD work record 0x7B2F50 (28 callers). The FLIRT name is a false match
// (the same few instructions as the SDK function; this is CRI code).
void __gthread_get_ee_key_use(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0057f740
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v0 = addiu(v0, 12112);  // &0x7B2F50
}

// 0x00582A08 sub_582A08 -- 76 bytes; leaf frame (no stack)
// [mwsfdRingKindCode] Kind code of ring entry (index mod 8, C's signed remainder): its +16 when the entry is valid,
// else 17.
void sub_582A08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00582a08
    enter(ctx, 16);  // entry check point + this block's cycles
    a2 = addiu(a1, 7);
    v0 = slti(a1, 0);
    v1 = a1;
    a3 = 1;
    if (v0 != 0) v1 = a2;
    v0 = 17;
    a2 = sra(v1, 3);
    a2 = sll(a2, 3);
    a2 = subu(a1, a2);
    v1 = sll(a2, 2);
    v1 = addu(v1, a2);
    v1 = sll(v1, 2);
    a1 = addu(v1, a0);
    lw(a0, a1, 192);
    v1 = a1;
    if (a0 == a3) {
        // 0x00582a48
        charge(ctx, 1);
        lw(v0, v1, 208);
    }
    // 0x00582a4c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game
