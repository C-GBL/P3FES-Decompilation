// The stratum title's drawing helpers (0x447F90-0x44A990, the leaves "y_StratumParts_proc" Y_StParts_UpdateStratumPartsTask calls) and a
// small Im2D vertex helper, hand-decompiled from SLUS_216.21 (game/include/p3fes/game/tartarus.h;
// docs/ANALYSIS/27_unmapped_bands.md section 8). Phase 5 slice `tartarus`: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_tartarus.cpp runs each against its __recomp body. The register view, the cycle
// model and the call convention: game/src/field/tartarus_cpu.h.
//
// The stratum title (the screen shown on entering a block of Tartarus, 26_field.md 6.1) draws from the stratum parts
// work (the "y_StratumParts_proc" task): +4 its sprite file, +232 a second one, +2366 / +2367 / +2368 / +2369 the cursor
// / count / total / scroll of the floor list, +2372 / +2376 the cursor's position; and from the stratum record at
// *(gp-0x4604) (the 0x425xxx COMM handlers fill it, comm_b.h): +4 + 4 i {s8 block, s16 floor} entries (+160 the count),
// +162 / +164 the current floor / block, +124 + 6 i the per-block fade counters, +166 + i the per-block state bytes.
#include "p3fes/game/tartarus.h"

#include "tartarus_cpu.h"

namespace p3fes::recomp_gen {
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_269C80_00269c80(p3fes::EEContext&);
void fn_sub_269CA0_00269ca0(p3fes::EEContext&);
void fn_sub_421FE0_00421fe0(p3fes::EEContext&);
void fn_sub_4221A0_004221a0(p3fes::EEContext&);
void fn_sub_4222D0_004222d0(p3fes::EEContext&);
void fn_sub_447F90_00447f90(p3fes::EEContext&);
void fn_sub_44A240_0044a240(p3fes::EEContext&);
void fn_sub_44A330_0044a330(p3fes::EEContext&);
// @@CALLEES@@
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace gen = ::p3fes::recomp_gen;
using namespace tartarus;
using namespace tart;

struct Stratum : Cpu {
    using Cpu::Cpu;

    // 0x447F90 (out, task, i): the screen position of entry (s8) i of the floor list: out = {(f32) the s16 0x6B4798,
    // (f32)(the s16 0x6B479A - 64 (block_i - 1) - 32 (6 - the s8 at work +595) + 32) - 32}, block_i = the s8 at stratum
    // record +4 + 4 i. The loop over the record's +160 count does nothing (a do-nothing loop kept by the compiler).
    void sub_447F90() {
        enter(27);
        sp = addiu(sp, -16);
        v1 = dsll32(a2, 24);
        v1 = dsra32(v1, 24);
        v1 = sll(v1, 2);
        a4 = lw(gp, kGpStratum);
        v1 = addu(v1, a4);
        v1 = lb(v1, 4);
        a3 = lui(0x6Bu);
        a3 = addiu(a3, 18326);  // 0x6B4796
        a2 = lh(a3, 4);
        v1 = addiu(v1, -1);
        v1 = sll(v1, 6);
        a2 = subu(a2, v1);
        v1 = lw(a1, kTaskWork);
        a1 = lb(v1, 595);
        v1 = si(6);
        v1 = subu(v1, a1);
        v1 = sll(v1, 5);
        v1 = subu(a2, v1);
        v1 = addiu(v1, 32);
        mtc1(v1, 0);
        cvt_s_w(1, 0);
        a2 = 0;
        a1 = lb(a4, 160);
        for (;;) {
            charge(6);
            v1 = slt(a2, a1);
            if (v1 == 0) break;
            backedge();
            charge(1);
            a2 = addiu(a2, 1);
        }
        charge(16);
        v1 = lui(0x4200u);
        mtc1(v1, 0);  // 32f
        sub_s(0, 1, 0);
        swc1(0, sp, 12);
        v1 = lh(a3, 2);
        mtc1(v1, 0);
        cvt_s_w(1, 0);
        swc1(1, sp, 8);
        lwc1(0, sp, 12);
        swc1(1, a0, 0);
        swc1(0, a0, 4);
        sp = addiu(sp, 16);
    }

    // 0x449C90 (task, i): the index (s8) of the first of the 30 four-byte records at 0x6B4650 ({s8 block, s16 floor})
    // matching the stratum record's entry (s8) i, -1 when none.
    void sub_449C90() {
        enter(10);
        a3 = 0;
        v0 = dsll32(a1, 24);
        v0 = dsra32(v0, 24);
        v1 = sll(v0, 2);
        v0 = lw(gp, kGpStratum);
        a2 = addu(v0, v1);
        a1 = lui(0x6Bu);
        a1 = addiu(a1, 18000);  // 0x6B4650
        for (;;) {
            charge(3);
            v0 = slti(a3, 30);
            if (v0 == 0) break;
            backedge();
            charge(6);
            v0 = sll(a3, 2);
            a0 = addu(a1, v0);
            v1 = lb(a2, 4);
            v0 = lb(a0, 0);
            if (v1 == v0) {
                charge(4);
                v1 = lh(a0, 2);
                v0 = lh(a2, 6);
                if (v1 == v0) {
                    charge(4);
                    v0 = dsll32(a3, 24);
                    v0 = dsra32(v0, 24);
                    charge(2);
                    return;
                }
            }
            charge(1);
            a3 = addiu(a3, 1);
        }
        charge(1);
        v0 = si(-1);
        charge(2);
    }

    // 0x449D10: clears the 56 s16 triples at work +236 + 6 i.
    void sub_449D10() {
        enter(4);
        a0 = lw(a0, kTaskWork);
        a1 = 0;
        for (;;) {
            charge(3);
            v1 = slti(a1, 56);
            if (v1 == 0) break;
            backedge();
            charge(8);
            v1 = sll(a1, 1);
            v1 = addu(v1, a1);
            v1 = sll(v1, 1);
            v1 = addu(a0, v1);
            sh(v1, 236, zero);
            sh(v1, 238, zero);
            sh(v1, 240, zero);
            a1 = addiu(a1, 1);
        }
        charge(2);
    }

    // 0x44A240 (task, index; $f13 y, $f15 scale, and the caller's $f21 alpha / $f23 x, kept by the convention of its
    // callers): sprite (s8) index of the stratum work's sprite file +4 with scale $f15, alpha (u8)(unsigned) $f21, at
    // ($f23, $f13), drawn and released.
    void sub_44A240() {
        enter(26);
        sp = addiu(sp, -48);
        sd(sp, 32, ra);
        sq(s0, sp, 16);
        swc1(23, sp, 12);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        mov_s(23, 12);
        mov_s(22, 13);
        mov_s(21, 14);
        mov_s(20, 15);
        v0 = lw(a0, kTaskWork);
        a2 = dsll32(a1, 24);
        a2 = dsra32(a2, 24);
        a0 = 0;
        a1 = lw(v0, 4);
        jal(0x44A280u, &gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        swc1(20, v0, 44);
        v0 = lui(0x4F00u);
        mtc1(v0, 0);  // 2^31
        c_le_s(0, 21);
        if (!cond()) {
            charge(6);
            cvt_w_s(0, 21);
            mfc1(v1, 0);
            v1 = v1 & 0xFFu;
        } else {
            charge(6);
            sub_s(0, 21, 0);
            cvt_w_s(0, 0);
            mfc1(v1, 0);
            v0 = lui(0x8000u);
            v1 = v1 | v0;
            v1 = v1 & 0xFFu;
        }
        charge(19);
        sb(s0, 24, v1);
        swc1(23, s0, 16);
        swc1(22, s0, 20);
        a0 = s0;
        a1 = si(1);
        jal(0x44A2ECu, &gen::fn_sub_1127D0_001127d0);
        a0 = s0;
        jal(0x44A2F8u, &gen::fn_sub_115980_00115980);
        ra = ld(sp, 32);
        lq(s0, sp, 16);
        lwc1(23, sp, 12);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 48);
    }

    // 0x44A330: sub_44A240 on the work's second sprite file (+232).
    void sub_44A330() {
        enter(26);
        sp = addiu(sp, -48);
        sd(sp, 32, ra);
        sq(s0, sp, 16);
        swc1(23, sp, 12);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        mov_s(23, 12);
        mov_s(22, 13);
        mov_s(21, 14);
        mov_s(20, 15);
        v0 = lw(a0, kTaskWork);
        a2 = dsll32(a1, 24);
        a2 = dsra32(a2, 24);
        a0 = 0;
        a1 = lw(v0, 232);
        jal(0x44A370u, &gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        swc1(20, v0, 44);
        v0 = lui(0x4F00u);
        mtc1(v0, 0);  // 2^31
        c_le_s(0, 21);
        if (!cond()) {
            charge(6);
            cvt_w_s(0, 21);
            mfc1(v1, 0);
            v1 = v1 & 0xFFu;
        } else {
            charge(6);
            sub_s(0, 21, 0);
            cvt_w_s(0, 0);
            mfc1(v1, 0);
            v0 = lui(0x8000u);
            v1 = v1 | v0;
            v1 = v1 & 0xFFu;
        }
        charge(19);
        sb(s0, 24, v1);
        swc1(23, s0, 16);
        swc1(22, s0, 20);
        a0 = s0;
        a1 = si(1);
        jal(0x44A3DCu, &gen::fn_sub_1127D0_001127d0);
        a0 = s0;
        jal(0x44A3E8u, &gen::fn_sub_115980_00115980);
        ra = ld(sp, 32);
        lq(s0, sp, 16);
        lwc1(23, sp, 12);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 48);
    }

    // 0x44A630: hides (handle +24 = 255) the four handles of each of the +2367 list entries (+1192 / +1216 / +1264 /
    // +1240 + 4 i), the four title handles indexed by the bytes 0x6B46D0 / 0x6B4784 / 0x6B477E / 0x6B478A, +2152 / +2156,
    // the six at +828 + 4 i, and the part handles +8 + 4 k of the 56 table rows 0x6B46D0 + 6 k whose first byte is not -1.
    void sub_44A630() {
        enter(5);
        a0 = lw(a0, kTaskWork);
        a3 = 0;
        a1 = si(255);
        for (;;) {
            charge(4);
            v1 = lb(a0, 2367);
            v1 = slt(a3, v1);
            if (v1 == 0) break;
            backedge();
            charge(11);
            v1 = sll(a3, 2);
            a2 = addu(a0, v1);
            v1 = lw(a2, 1192);
            sb(v1, 24, a1);
            v1 = lw(a2, 1216);
            sb(v1, 24, a1);
            v1 = lw(a2, 1264);
            sb(v1, 24, a1);
            v1 = lw(a2, 1240);
            sb(v1, 24, a1);
            a3 = addiu(a3, 1);
        }
        charge(35);
        v1 = si(255);
        a1 = lui(0x6Bu);
        a1 = lb(a1, 18128);  // 0x6B46D0
        a1 = sll(a1, 2);
        a1 = addu(a1, a0);
        a1 = lw(a1, 8);
        sb(a1, 24, v1);
        a1 = lui(0x6Bu);
        a1 = addiu(a1, 18308);  // 0x6B4784
        a1 = lb(a1, 0);
        a1 = sll(a1, 2);
        a1 = addu(a1, a0);
        a1 = lw(a1, 8);
        sb(a1, 24, v1);
        a1 = lui(0x6Bu);
        a1 = addiu(a1, 18302);  // 0x6B477E
        a1 = lb(a1, 0);
        a1 = sll(a1, 2);
        a1 = addu(a1, a0);
        a1 = lw(a1, 8);
        sb(a1, 24, v1);
        a1 = lui(0x6Bu);
        a1 = addiu(a1, 18314);  // 0x6B478A
        a1 = lb(a1, 0);
        a1 = sll(a1, 2);
        a1 = addu(a1, a0);
        a1 = lw(a1, 8);
        sb(a1, 24, v1);
        a1 = lw(a0, 2152);
        sb(a1, 24, v1);
        a1 = lw(a0, 2156);
        sb(a1, 24, v1);
        a2 = 0;
        for (;;) {
            charge(3);
            a1 = slti(a2, 6);
            if (a1 == 0) break;
            backedge();
            charge(5);
            a1 = sll(a2, 2);
            a1 = addu(a0, a1);
            a1 = lw(a1, 828);
            sb(a1, 24, v1);
            a2 = addiu(a2, 1);
        }
        charge(7);
        a4 = 0;
        a1 = si(255);
        a3 = lui(0x6Bu);
        a3 = addiu(a3, 18128);  // 0x6B46D0
        a2 = si(-1);
        for (;;) {
            charge(3);
            v1 = slti(a4, 56);
            if (v1 == 0) break;
            backedge();
            charge(7);
            v1 = sll(a4, 1);
            v1 = addu(v1, a4);
            v1 = sll(v1, 1);
            v1 = addu(a3, v1);
            v1 = lb(v1, 0);
            if (v1 != a2) {
                charge(4);
                v1 = sll(a4, 2);
                v1 = addu(a0, v1);
                v1 = lw(v1, 8);
                sb(v1, 24, a1);
            }
            charge(1);
            a4 = addiu(a4, 1);
        }
        charge(2);
    }

    // 0x448060 (task, i, xy (two f32 in $a2), block, floor, active ($a5)): one entry of the floor list at xy + (127, 10).
    // The cursor's entry (i == +2366 while active, else none) animates its two arrows (s16 frames +2388 / +2392 per side,
    // 23 steps with a delay, through the fade sub_4221A0) and draws them (parts 9 / 54); the stratum record's current
    // block / floor (+164 / +162) shows its marker twice (part 38). The floor number in up to three digits: from the
    // current-file parts 40.. (the record's floor), else the second file's 11..; the cursor's entry draws 25 and 15 + digit.
    // Finally the label sprite (50 for the current floor, else 26) offset by 4 / 14 / 24 for one / two / three digits.
    // Divisions by 100 / 10 are through HI/LO (div / mfhi / mflo).
    void sub_448060() {
        enter(26);
        sp = addiu(sp, -224);
        sd(sp, 160, ra);
        sq(fp, sp, 144);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s4 = a0;
        sd(sp, 216, a2);
        s7 = a3;
        s3 = a4;
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        s5 = 0;
        v1 = lb(s1, 2366);
        s6 = dsll32(a5, 24);
        s6 = dsra32(s6, 24);
        if (s6 == 0) {
            charge(1);
            v1 = si(-1);
        }
        charge(3);
        a0 = 0;
        for (;;) {
            charge(6);
            v0 = slti(a0, 256);
            if (v0 == 0) break;
            backedge();
            charge(1);
            a0 = addiu(a0, 1);
        }
        charge(19);
        lwc1(1, sp, 216);
        v0 = lui(0x42FEu);
        mtc1(v0, 0);  // 127f
        add_s(2, 1, 0);
        swc1(2, sp, 216);
        lwc1(1, sp, 220);
        v0 = lui(0x4120u);
        mtc1(v0, 0);  // 10.0
        add_s(20, 1, 0);
        swc1(20, sp, 220);
        fp = dsll32(v1, 24);
        fp = dsra32(fp, 24);
        v0 = dsll32(a1, 24);
        v0 = dsra32(v0, 24);
        sq(v0, sp, 192);
        if (v0 == fp) {
            charge(7);
            s0 = 0;
            v0 = lui(0x4170u);
            mtc1(v0, 0);  // 15f
            add_s(21, 0, 2);
            for (;;) {
                charge(3);
                v0 = slti(s0, 2);
                if (v0 == 0) break;
                backedge();
                charge(8);
                v0 = lui(0x437Fu);
                mtc1(v0, 22);  // 255.0
                v0 = sll(s0, 1);
                a0 = addu(s1, v0);
                v1 = addiu(a0, 2392);
                v0 = lh(a0, 2392);
                if (v0 == 0) {
                    charge(5);
                    v1 = addiu(a0, 2388);
                    v0 = lh(a0, 2388);
                    at = slti(v0, 23);
                    if (at != 0) {
                        charge(2);
                        v0 = addiu(v0, 1);
                        sh(v1, 0, v0);
                    }
                    charge(15);
                    v0 = lh(v1, 0);
                    mtc1(v0, 0);
                    cvt_s_w(14, 0);
                    mtc1(zero, 12);
                    v0 = lui(0x437Fu);
                    mtc1(v0, 13);  // 255.0
                    v0 = lui(0x41B8u);
                    mtc1(v0, 15);  // 23f
                    a0 = si(2);
                    jal(0x4481C0u, &gen::fn_sub_4221A0_004221a0);
                    mov_s(22, 0);
                } else {
                    charge(2);
                    v0 = addiu(v0, -1);
                    sh(v1, 0, v0);
                }
                charge(75);
                v0 = sll(s0, 1);
                v1 = addu(s1, v0);
                v0 = addiu(v1, 2388);
                sq(v0, sp, 176);
                v0 = lh(v1, 2388);
                mtc1(v0, 0);
                cvt_s_w(14, 0);
                v0 = lui(0x41B8u);
                mtc1(v0, 15);  // 23f
                a0 = si(1);
                lwc1(12, sp, 216);
                mov_s(13, 21);
                jal(0x448210u, &gen::fn_sub_4221A0_004221a0);
                v0 = si(1);
                v0 = subu(v0, s0);
                mtc1(v0, 1);
                cvt_s_w(3, 1);
                v0 = lui(0x41A0u);
                mtc1(v0, 2);  // 20f
                v0 = lui(0x42B4u);
                mtc1(v0, 1);  // 90f
                sub_s(1, 0, 1);
                mtc1(zero, 0);
                adda_s(0, 1);
                madd_s(12, 2, 3);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s4;
                a1 = si(9);
                mov_s(13, 20);
                mov_s(14, 22);
                jal(0x44826Cu, &gen::fn_sub_44A240_0044a240);
                lq(v0, sp, 176);
                v0 = lh(v0, 0);
                mtc1(v0, 0);
                cvt_s_w(14, 0);
                lwc1(12, sp, 216);
                v0 = lui(0x4170u);
                mtc1(v0, 0);  // 15f
                sub_s(13, 12, 0);
                v0 = lui(0x41B8u);
                mtc1(v0, 15);  // 23f
                a0 = si(1);
                jal(0x4482A8u, &gen::fn_sub_4221A0_004221a0);
                v0 = lui(0x41A0u);
                mtc1(v0, 3);  // 20f
                mtc1(s0, 1);
                cvt_s_w(2, 1);
                v0 = lui(0x4274u);
                mtc1(v0, 1);  // 61f
                add_s(1, 1, 0);
                mtc1(zero, 0);
                adda_s(0, 1);
                madd_s(12, 3, 2);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s4;
                a1 = si(54);
                mov_s(13, 20);
                mov_s(14, 22);
                jal(0x4482FCu, &gen::fn_sub_44A240_0044a240);
                s0 = addiu(s0, 1);
            }
            charge(4);
            v1 = lh(s1, 2390);
            v0 = si(23);
            if (v1 == v0) {
                charge(3);
                a0 = 0;
                for (;;) {
                    charge(3);
                    v0 = slti(a0, 2);
                    if (v0 == 0) break;
                    backedge();
                    charge(7);
                    v0 = sll(a0, 1);
                    v1 = addu(s1, v0);
                    sh(v1, 2388, zero);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 1);
                    sh(v1, 2392, v0);
                    a0 = addiu(a0, 1);
                }
                charge(2);
            }
        } else {
            charge(6);
            a0 = lw(gp, kGpStratum);
            v1 = lb(a0, 164);
            v0 = dsll32(s7, 24);
            v0 = dsra32(v0, 24);
            if (v1 == v0) {
                charge(5);
                v1 = lh(a0, 162);
                v0 = dsll32(s3, 16);
                v0 = dsra32(v0, 16);
                if (v1 == v0) {
                    charge(3);
                    v0 = si(1);
                    if (s6 == v0) {
                        charge(11);
                        s0 = 0;
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        add_s(22, 0, 20);
                        v0 = lui(0x4274u);
                        mtc1(v0, 0);  // 61f
                        add_s(21, 0, 2);
                        for (;;) {
                            charge(3);
                            v0 = slti(s0, 2);
                            if (v0 == 0) break;
                            backedge();
                            charge(30);
                            v0 = lui(0x41A0u);
                            mtc1(v0, 1);  // 20f
                            mtc1(s0, 0);
                            cvt_s_w(0, 0);
                            mul_s(20, 1, 0);
                            lwc1(1, sp, 216);
                            v0 = lui(0x42B4u);
                            mtc1(v0, 0);  // 90f
                            sub_s(0, 1, 0);
                            add_s(12, 0, 20);
                            mtc1(zero, 14);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s4;
                            a1 = si(38);
                            mov_s(13, 22);
                            jal(0x44840Cu, &gen::fn_sub_44A240_0044a240);
                            add_s(12, 21, 20);
                            mtc1(zero, 14);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s4;
                            a1 = si(38);
                            mov_s(13, 22);
                            jal(0x448430u, &gen::fn_sub_44A240_0044a240);
                            s0 = addiu(s0, 1);
                        }
                    }
                }
            }
        }
        charge(5);
        s0 = dsll32(s3, 16);
        s0 = dsra32(s0, 16);
        at = slti(s0, 10);
        if (at != 0) {
            charge(4);
            s3 = s0;
            lq(v0, sp, 192);
            if (v0 != fp) {
                charge(6);
                a0 = lw(gp, kGpStratum);
                v1 = lb(a0, 164);
                v0 = dsll32(s7, 24);
                v0 = dsra32(v0, 24);
                if (v1 == v0) {
                    charge(3);
                    v0 = lh(a0, 162);
                    if (v0 == s0) {
                        charge(3);
                        v0 = si(1);
                        if (s6 == v0) {
                            charge(17);
                            v0 = addiu(s0, 40);
                            a1 = dsll32(v0, 24);
                            a1 = dsra32(a1, 24);
                            lwc1(1, sp, 216);
                            v0 = lui(0x41A0u);
                            mtc1(v0, 0);  // 20f
                            sub_s(12, 1, 0);
                            mtc1(zero, 14);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s4;
                            lwc1(13, sp, 220);
                            jal(0x4484D0u, &gen::fn_sub_44A240_0044a240);
                            goto L_004488b8;
                        }
                    }
                }
                charge(17);
                v0 = addiu(s0, 11);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                lwc1(1, sp, 216);
                v0 = lui(0x41A0u);
                mtc1(v0, 0);  // 20f
                sub_s(12, 1, 0);
                mtc1(zero, 14);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s4;
                lwc1(13, sp, 220);
                jal(0x448514u, &gen::fn_sub_44A330_0044a330);
            }
        } else {
            charge(3);
            at = slti(s0, 100);
            if (at != 0) {
                charge(12);
                v1 = si(10);
                div(s0, v1);
                mflo(v0);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
                div(s0, v1);
                mfhi(v0);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lq(v0, sp, 192);
                if (v0 != fp) {
                    charge(6);
                    a0 = lw(gp, kGpStratum);
                    v1 = lb(a0, 164);
                    v0 = dsll32(s7, 24);
                    v0 = dsra32(v0, 24);
                    if (v1 == v0) {
                        charge(3);
                        v0 = lh(a0, 162);
                        if (v0 == s0) {
                            charge(3);
                            v0 = si(1);
                            if (s6 == v0) {
                                charge(37);
                                lwc1(20, sp, 220);
                                v0 = dsll32(s2, 16);
                                v0 = dsra32(v0, 16);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 216);
                                v0 = lui(0x41F0u);
                                mtc1(v0, 0);  // 30f
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s4;
                                mov_s(13, 20);
                                jal(0x4485D0u, &gen::fn_sub_44A240_0044a240);
                                v0 = dsll32(s3, 16);
                                v0 = dsra32(v0, 16);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 216);
                                v0 = lui(0x4120u);
                                mtc1(v0, 0);  // 10.0
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s4;
                                mov_s(13, 20);
                                jal(0x448614u, &gen::fn_sub_44A240_0044a240);
                                goto L_004488b8;
                            }
                        }
                    }
                    charge(37);
                    lwc1(20, sp, 220);
                    v0 = dsll32(s2, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x41F0u);
                    mtc1(v0, 0);  // 30f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x448664u, &gen::fn_sub_44A330_0044a330);
                    v0 = dsll32(s3, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x4120u);
                    mtc1(v0, 0);  // 10.0
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x4486A8u, &gen::fn_sub_44A330_0044a330);
                }
            } else {
                charge(26);
                v0 = si(100);
                div(s0, v0);
                mflo(v0);
                s5 = dsll32(v0, 16);
                s5 = dsra32(s5, 16);
                v0 = sll(s5, 2);
                v1 = addu(v0, s5);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                a0 = sll(v0, 2);
                v1 = subu(s0, a0);
                v0 = si(10);
                div(v1, v0);
                mflo(v0);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = sll(v0, 1);
                v0 = addu(a0, v0);
                v0 = subu(s0, v0);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lq(v0, sp, 192);
                if (v0 != fp) {
                    charge(6);
                    a0 = lw(gp, kGpStratum);
                    v1 = lb(a0, 164);
                    v0 = dsll32(s7, 24);
                    v0 = dsra32(v0, 24);
                    if (v1 == v0) {
                        charge(3);
                        v0 = lh(a0, 162);
                        if (v0 == s0) {
                            charge(3);
                            v0 = si(1);
                            if (s6 == v0) {
                                charge(46);
                                lwc1(20, sp, 220);
                                v0 = addiu(s5, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 216);
                                v0 = lui(0x4220u);
                                mtc1(v0, 0);  // 40f
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s4;
                                mov_s(13, 20);
                                jal(0x448788u, &gen::fn_sub_44A240_0044a240);
                                v0 = addiu(s2, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 216);
                                v0 = lui(0x41A0u);
                                mtc1(v0, 0);  // 20f
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s4;
                                mov_s(13, 20);
                                jal(0x4487C4u, &gen::fn_sub_44A240_0044a240);
                                v0 = dsll32(s3, 16);
                                v0 = dsra32(v0, 16);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s4;
                                lwc1(12, sp, 216);
                                mov_s(13, 20);
                                jal(0x4487F8u, &gen::fn_sub_44A240_0044a240);
                                goto L_004488b8;
                            }
                        }
                    }
                    charge(44);
                    lwc1(20, sp, 220);
                    v0 = addiu(s5, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x4220u);
                    mtc1(v0, 0);  // 40f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x448840u, &gen::fn_sub_44A330_0044a330);
                    v0 = addiu(s2, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x41A0u);
                    mtc1(v0, 0);  // 20f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x44887Cu, &gen::fn_sub_44A330_0044a330);
                    v0 = dsll32(s3, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    lwc1(12, sp, 216);
                    mov_s(13, 20);
                    jal(0x4488B0u, &gen::fn_sub_44A330_0044a330);
                }
            }
        }
      L_004488b8:
        charge(3);
        lq(v0, sp, 192);
        if (v0 != fp) {
            charge(6);
            a0 = lw(gp, kGpStratum);
            v1 = lb(a0, 164);
            v0 = dsll32(s7, 24);
            v0 = dsra32(v0, 24);
            if (v1 == v0) {
                charge(3);
                v0 = lh(a0, 162);
                if (v0 == s0) {
                    charge(3);
                    v0 = si(1);
                    if (s6 == v0) {
                        charge(10);
                        a0 = 0;
                        a1 = lw(s1, 4);
                        a2 = si(50);
                        jal(0x448900u, &gen::fn_sprCreateHandle_001158b0);
                        s1 = v0;
                        sb(v0, 24, zero);
                        at = slti(s0, 10);
                        if (at != 0) {
                            charge(7);
                            v0 = lui(0x4080u);
                            mtc1(v0, 1);  // 4.0
                            lwc1(0, sp, 216);
                            add_s(0, 1, 0);
                            swc1(0, s1, 16);
                        } else {
                            charge(3);
                            at = slti(s0, 100);
                            if (at != 0) {
                                charge(7);
                                v0 = lui(0x4160u);
                                mtc1(v0, 1);  // 14f
                                lwc1(0, sp, 216);
                                add_s(0, 1, 0);
                                swc1(0, s1, 16);
                            } else {
                                charge(5);
                                v0 = lui(0x41C0u);
                                mtc1(v0, 1);  // 24f
                                lwc1(0, sp, 216);
                                add_s(0, 1, 0);
                                swc1(0, s1, 16);
                            }
                        }
                        charge(13);
                        lwc1(0, sp, 220);
                        swc1(0, s1, 20);
                        v0 = lui(0x4040u);
                        sw(s1, 44, v0);
                        a0 = s1;
                        a1 = si(1);
                        jal(0x44898Cu, &gen::fn_sub_1127D0_001127d0);
                        a0 = s1;
                        jal(0x448998u, &gen::fn_sub_115980_00115980);
                        goto L_00448ca8;
                    }
                }
            }
            charge(10);
            a0 = 0;
            a1 = lw(s1, 4);
            a2 = si(26);
            jal(0x4489B4u, &gen::fn_sprCreateHandle_001158b0);
            s1 = v0;
            sb(v0, 24, zero);
            at = slti(s0, 10);
            if (at != 0) {
                charge(7);
                v0 = lui(0x4080u);
                mtc1(v0, 1);  // 4.0
                lwc1(0, sp, 216);
                add_s(0, 1, 0);
                swc1(0, s1, 16);
            } else {
                charge(3);
                at = slti(s0, 100);
                if (at != 0) {
                    charge(7);
                    v0 = lui(0x4160u);
                    mtc1(v0, 1);  // 14f
                    lwc1(0, sp, 216);
                    add_s(0, 1, 0);
                    swc1(0, s1, 16);
                } else {
                    charge(5);
                    v0 = lui(0x41C0u);
                    mtc1(v0, 1);  // 24f
                    lwc1(0, sp, 216);
                    add_s(0, 1, 0);
                    swc1(0, s1, 16);
                }
            }
            charge(13);
            lwc1(0, sp, 220);
            swc1(0, s1, 20);
            v0 = lui(0x4040u);
            sw(s1, 44, v0);
            a0 = s1;
            a1 = si(1);
            jal(0x448A40u, &gen::fn_sub_1127D0_001127d0);
            a0 = s1;
            jal(0x448A4Cu, &gen::fn_sub_115980_00115980);
        } else {
            charge(3);
            at = slti(s0, 10);
            if (at != 0) {
                charge(32);
                lwc1(20, sp, 220);
                v0 = lui(0x4080u);
                mtc1(v0, 1);  // 4.0
                lwc1(0, sp, 216);
                add_s(12, 1, 0);
                mtc1(zero, 14);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s4;
                a1 = si(25);
                mov_s(13, 20);
                jal(0x448A94u, &gen::fn_sub_44A240_0044a240);
                v0 = dsll32(s3, 16);
                v0 = dsra32(v0, 16);
                v0 = addiu(v0, 15);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                lwc1(1, sp, 216);
                v0 = lui(0x41A0u);
                mtc1(v0, 0);  // 20f
                sub_s(12, 1, 0);
                mtc1(zero, 14);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s4;
                mov_s(13, 20);
                jal(0x448AD8u, &gen::fn_sub_44A240_0044a240);
            } else {
                charge(3);
                at = slti(s0, 100);
                if (at != 0) {
                    charge(49);
                    lwc1(20, sp, 220);
                    v0 = lui(0x4160u);
                    mtc1(v0, 1);  // 14f
                    lwc1(0, sp, 216);
                    add_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    a1 = si(25);
                    mov_s(13, 20);
                    jal(0x448B20u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s2, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x41F0u);
                    mtc1(v0, 0);  // 30f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x448B64u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s3, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x4120u);
                    mtc1(v0, 0);  // 10.0
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x448BA8u, &gen::fn_sub_44A240_0044a240);
                } else {
                    charge(60);
                    lwc1(20, sp, 220);
                    v0 = lui(0x41C0u);
                    mtc1(v0, 1);  // 24f
                    lwc1(0, sp, 216);
                    add_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    a1 = si(25);
                    mov_s(13, 20);
                    jal(0x448BE4u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s5, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x4220u);
                    mtc1(v0, 0);  // 40f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x448C28u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s2, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 216);
                    v0 = lui(0x41A0u);
                    mtc1(v0, 0);  // 20f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    mov_s(13, 20);
                    jal(0x448C6Cu, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s3, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s4;
                    lwc1(12, sp, 216);
                    mov_s(13, 20);
                    jal(0x448CA0u, &gen::fn_sub_44A240_0044a240);
                }
            }
        }
      L_00448ca8:
        charge(16);
        ra = ld(sp, 160);
        lq(fp, sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 224);
    }

    // 0x448CF0 (task, i, xy, block, floor, active ($a5), alpha ($a6)): sub_448060 with the work's own current block / floor
    // (+1179 / +1180) instead of the record's; the cursor's entry draws label 25, the current one 26 then 50 with `alpha`,
    // the others 26. The cursor test copies the byte through `paddub $v1, $v0, $zero`.
    void sub_448CF0() {
        enter(27);
        sp = addiu(sp, -304);
        sd(sp, 160, ra);
        sq(fp, sp, 144);
        sq(s7, sp, 128);
        sq(s6, sp, 112);
        sq(s5, sp, 96);
        sq(s4, sp, 80);
        sq(s3, sp, 64);
        sq(s2, sp, 48);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s1 = a0;
        sd(sp, 296, a2);
        fp = a3;
        s5 = a4;
        s0 = a6;
        s3 = lw(a0, kTaskWork);
        s4 = 0;
        s6 = 0;
        v1 = lb(s3, 2366);
        s7 = dsll32(a5, 24);
        s7 = dsra32(s7, 24);
        if (s7 == 0) {
            charge(1);
            v1 = si(-1);
        }
        charge(3);
        a0 = 0;
        for (;;) {
            charge(6);
            v0 = slti(a0, 256);
            if (v0 == 0) break;
            backedge();
            charge(1);
            a0 = addiu(a0, 1);
        }
        charge(22);
        lwc1(1, sp, 296);
        v0 = lui(0x42FEu);
        mtc1(v0, 0);  // 127f
        add_s(2, 1, 0);
        swc1(2, sp, 296);
        lwc1(1, sp, 300);
        v0 = lui(0x4120u);
        mtc1(v0, 0);  // 10.0
        add_s(20, 1, 0);
        swc1(20, sp, 300);
        v0 = dsll32(v1, 24);
        v0 = dsra32(v0, 24);
        sq(v0, sp, 272);
        v0 = dsll32(a1, 24);
        v0 = dsra32(v0, 24);
        sq(v0, sp, 256);
        paddub(v1, v0, zero);
        lq(v0, sp, 272);
        if (v1 == v0) {
            charge(7);
            s2 = 0;
            v0 = lui(0x4170u);
            mtc1(v0, 0);  // 15f
            add_s(21, 0, 2);
            for (;;) {
                charge(3);
                v0 = slti(s2, 2);
                if (v0 == 0) break;
                backedge();
                charge(8);
                v0 = lui(0x437Fu);
                mtc1(v0, 22);  // 255.0
                v0 = sll(s2, 1);
                a0 = addu(s3, v0);
                v1 = addiu(a0, 2392);
                v0 = lh(a0, 2392);
                if (v0 == 0) {
                    charge(5);
                    v1 = addiu(a0, 2388);
                    v0 = lh(a0, 2388);
                    at = slti(v0, 23);
                    if (at != 0) {
                        charge(2);
                        v0 = addiu(v0, 1);
                        sh(v1, 0, v0);
                    }
                    charge(15);
                    v0 = lh(v1, 0);
                    mtc1(v0, 0);
                    cvt_s_w(14, 0);
                    mtc1(zero, 12);
                    v0 = lui(0x437Fu);
                    mtc1(v0, 13);  // 255.0
                    v0 = lui(0x41B8u);
                    mtc1(v0, 15);  // 23f
                    a0 = si(2);
                    jal(0x448E60u, &gen::fn_sub_4221A0_004221a0);
                    mov_s(22, 0);
                } else {
                    charge(2);
                    v0 = addiu(v0, -1);
                    sh(v1, 0, v0);
                }
                charge(75);
                v0 = sll(s2, 1);
                v1 = addu(s3, v0);
                v0 = addiu(v1, 2388);
                sq(v0, sp, 240);
                v0 = lh(v1, 2388);
                mtc1(v0, 0);
                cvt_s_w(14, 0);
                v0 = lui(0x41B8u);
                mtc1(v0, 15);  // 23f
                a0 = si(1);
                lwc1(12, sp, 296);
                mov_s(13, 21);
                jal(0x448EB0u, &gen::fn_sub_4221A0_004221a0);
                v0 = si(1);
                v0 = subu(v0, s2);
                mtc1(v0, 1);
                cvt_s_w(3, 1);
                v0 = lui(0x41A0u);
                mtc1(v0, 2);  // 20f
                v0 = lui(0x42B4u);
                mtc1(v0, 1);  // 90f
                sub_s(1, 0, 1);
                mtc1(zero, 0);
                adda_s(0, 1);
                madd_s(12, 2, 3);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s1;
                a1 = si(9);
                mov_s(13, 20);
                mov_s(14, 22);
                jal(0x448F0Cu, &gen::fn_sub_44A240_0044a240);
                lq(v0, sp, 240);
                v0 = lh(v0, 0);
                mtc1(v0, 0);
                cvt_s_w(14, 0);
                lwc1(12, sp, 296);
                v0 = lui(0x4170u);
                mtc1(v0, 0);  // 15f
                sub_s(13, 12, 0);
                v0 = lui(0x41B8u);
                mtc1(v0, 15);  // 23f
                a0 = si(1);
                jal(0x448F48u, &gen::fn_sub_4221A0_004221a0);
                v0 = lui(0x41A0u);
                mtc1(v0, 3);  // 20f
                mtc1(s2, 1);
                cvt_s_w(2, 1);
                v0 = lui(0x4274u);
                mtc1(v0, 1);  // 61f
                add_s(1, 1, 0);
                mtc1(zero, 0);
                adda_s(0, 1);
                madd_s(12, 3, 2);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s1;
                a1 = si(54);
                mov_s(13, 20);
                mov_s(14, 22);
                jal(0x448F9Cu, &gen::fn_sub_44A240_0044a240);
                s2 = addiu(s2, 1);
            }
            charge(4);
            v1 = lh(s3, 2390);
            v0 = si(23);
            if (v1 == v0) {
                charge(3);
                a0 = 0;
                for (;;) {
                    charge(3);
                    v0 = slti(a0, 2);
                    if (v0 == 0) break;
                    backedge();
                    charge(7);
                    v0 = sll(a0, 1);
                    v1 = addu(s3, v0);
                    sh(v1, 2388, zero);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 1);
                    sh(v1, 2392, v0);
                    a0 = addiu(a0, 1);
                }
                charge(2);
            }
        } else {
            charge(6);
            a0 = lw(gp, kGpStratum);
            v1 = lb(a0, 164);
            v0 = dsll32(fp, 24);
            v0 = dsra32(v0, 24);
            if (v1 == v0) {
                charge(5);
                v1 = lh(a0, 162);
                v0 = dsll32(s5, 16);
                v0 = dsra32(v0, 16);
                if (v1 == v0) {
                    charge(3);
                    v0 = si(1);
                    if (s7 == v0) {
                        charge(11);
                        s2 = 0;
                        v0 = lui(0x4000u);
                        mtc1(v0, 0);  // 2.0
                        add_s(22, 0, 20);
                        v0 = lui(0x4274u);
                        mtc1(v0, 0);  // 61f
                        add_s(21, 0, 2);
                        for (;;) {
                            charge(3);
                            v0 = slti(s2, 2);
                            if (v0 == 0) break;
                            backedge();
                            charge(30);
                            v0 = lui(0x41A0u);
                            mtc1(v0, 1);  // 20f
                            mtc1(s2, 0);
                            cvt_s_w(0, 0);
                            mul_s(20, 1, 0);
                            lwc1(1, sp, 296);
                            v0 = lui(0x42B4u);
                            mtc1(v0, 0);  // 90f
                            sub_s(0, 1, 0);
                            add_s(12, 0, 20);
                            mtc1(zero, 14);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s1;
                            a1 = si(38);
                            mov_s(13, 22);
                            jal(0x4490ACu, &gen::fn_sub_44A240_0044a240);
                            add_s(12, 21, 20);
                            mtc1(zero, 14);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s1;
                            a1 = si(38);
                            mov_s(13, 22);
                            jal(0x4490D0u, &gen::fn_sub_44A240_0044a240);
                            s2 = addiu(s2, 1);
                        }
                    }
                }
            }
        }
        charge(5);
        s2 = dsll32(s5, 16);
        s2 = dsra32(s2, 16);
        at = slti(s2, 10);
        if (at != 0) {
            charge(5);
            s5 = s2;
            lq(v1, sp, 256);
            lq(v0, sp, 272);
            if (v1 != v0) {
                charge(5);
                v1 = lb(s3, 1179);
                v0 = dsll32(fp, 24);
                v0 = dsra32(v0, 24);
                if (v1 == v0) {
                    charge(3);
                    v0 = lb(s3, 1180);
                    if (v0 == s2) {
                        charge(3);
                        v0 = si(1);
                        if (s7 == v0) {
                            charge(35);
                            lwc1(20, sp, 300);
                            v0 = addiu(s2, 11);
                            a1 = dsll32(v0, 24);
                            a1 = dsra32(a1, 24);
                            lwc1(1, sp, 296);
                            v0 = lui(0x41A0u);
                            mtc1(v0, 0);  // 20f
                            sub_s(12, 1, 0);
                            mtc1(zero, 14);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s1;
                            mov_s(13, 20);
                            jal(0x449174u, &gen::fn_sub_44A330_0044a330);
                            mtc1(s0, 0);
                            cvt_s_w(14, 0);
                            v0 = addiu(s2, 40);
                            a1 = dsll32(v0, 24);
                            a1 = dsra32(a1, 24);
                            lwc1(1, sp, 296);
                            v0 = lui(0x41A0u);
                            mtc1(v0, 0);  // 20f
                            sub_s(12, 1, 0);
                            v0 = lui(0x4040u);
                            mtc1(v0, 15);  // 3.0
                            a0 = s1;
                            mov_s(13, 20);
                            jal(0x4491B8u, &gen::fn_sub_44A240_0044a240);
                            goto L_0044970c;
                        }
                    }
                }
                charge(17);
                v0 = addiu(s2, 11);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                lwc1(1, sp, 296);
                v0 = lui(0x41A0u);
                mtc1(v0, 0);  // 20f
                sub_s(12, 1, 0);
                mtc1(zero, 14);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s1;
                lwc1(13, sp, 300);
                jal(0x4491FCu, &gen::fn_sub_44A330_0044a330);
            }
        } else {
            charge(3);
            at = slti(s2, 100);
            if (at != 0) {
                charge(13);
                v1 = si(10);
                div(s2, v1);
                mflo(v0);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                div(s2, v1);
                mfhi(v0);
                s5 = dsll32(v0, 16);
                s5 = dsra32(s5, 16);
                lq(v1, sp, 256);
                lq(v0, sp, 272);
                if (v1 != v0) {
                    charge(5);
                    v1 = lb(s3, 1179);
                    v0 = dsll32(fp, 24);
                    v0 = dsra32(v0, 24);
                    if (v1 == v0) {
                        charge(3);
                        v0 = lb(s3, 1180);
                        if (v0 == s2) {
                            charge(3);
                            v0 = si(1);
                            if (s7 == v0) {
                                charge(75);
                                lwc1(20, sp, 300);
                                v0 = dsll32(s4, 16);
                                v0 = dsra32(v0, 16);
                                sq(v0, sp, 224);
                                v0 = addiu(v0, 11);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x41F0u);
                                mtc1(v0, 0);  // 30f
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x4492BCu, &gen::fn_sub_44A330_0044a330);
                                v0 = dsll32(s5, 16);
                                v0 = dsra32(v0, 16);
                                sq(v0, sp, 208);
                                v0 = addiu(v0, 11);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x4120u);
                                mtc1(v0, 0);  // 10.0
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x449304u, &gen::fn_sub_44A330_0044a330);
                                mtc1(s0, 0);
                                cvt_s_w(14, 0);
                                lq(v0, sp, 224);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x41F0u);
                                mtc1(v0, 0);  // 30f
                                sub_s(12, 1, 0);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x44934Cu, &gen::fn_sub_44A240_0044a240);
                                mtc1(s0, 0);
                                cvt_s_w(14, 0);
                                lq(v0, sp, 208);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x4120u);
                                mtc1(v0, 0);  // 10.0
                                sub_s(12, 1, 0);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x449394u, &gen::fn_sub_44A240_0044a240);
                                goto L_0044970c;
                            }
                        }
                    }
                    charge(37);
                    lwc1(20, sp, 300);
                    v0 = dsll32(s4, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x41F0u);
                    mtc1(v0, 0);  // 30f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x4493E4u, &gen::fn_sub_44A330_0044a330);
                    v0 = dsll32(s5, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x4120u);
                    mtc1(v0, 0);  // 10.0
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x449428u, &gen::fn_sub_44A330_0044a330);
                }
            } else {
                charge(27);
                v0 = si(100);
                div(s2, v0);
                mflo(v0);
                s6 = dsll32(v0, 16);
                s6 = dsra32(s6, 16);
                v0 = sll(s6, 2);
                v1 = addu(v0, s6);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                a0 = sll(v0, 2);
                v1 = subu(s2, a0);
                v0 = si(10);
                div(v1, v0);
                mflo(v0);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                v0 = sll(s4, 2);
                v0 = addu(v0, s4);
                v0 = sll(v0, 1);
                v0 = addu(a0, v0);
                v0 = subu(s2, v0);
                s5 = dsll32(v0, 16);
                s5 = dsra32(s5, 16);
                lq(v1, sp, 256);
                lq(v0, sp, 272);
                if (v1 != v0) {
                    charge(5);
                    v1 = lb(s3, 1179);
                    v0 = dsll32(fp, 24);
                    v0 = dsra32(v0, 24);
                    if (v1 == v0) {
                        charge(3);
                        v0 = lb(s3, 1180);
                        if (v0 == s2) {
                            charge(3);
                            v0 = si(1);
                            if (s7 == v0) {
                                charge(99);
                                lwc1(20, sp, 300);
                                v0 = addiu(s6, 11);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x4220u);
                                mtc1(v0, 0);  // 40f
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x449508u, &gen::fn_sub_44A330_0044a330);
                                v0 = dsll32(s4, 16);
                                v0 = dsra32(v0, 16);
                                sq(v0, sp, 192);
                                v0 = addiu(v0, 11);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x41A0u);
                                mtc1(v0, 0);  // 20f
                                sub_s(12, 1, 0);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x449550u, &gen::fn_sub_44A330_0044a330);
                                v0 = dsll32(s5, 16);
                                v0 = dsra32(v0, 16);
                                sq(v0, sp, 176);
                                v0 = addiu(v0, 11);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                mtc1(zero, 14);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                lwc1(12, sp, 296);
                                mov_s(13, 20);
                                jal(0x449588u, &gen::fn_sub_44A330_0044a330);
                                mtc1(s0, 0);
                                cvt_s_w(14, 0);
                                v0 = addiu(s6, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x4220u);
                                mtc1(v0, 0);  // 40f
                                sub_s(12, 1, 0);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x4495CCu, &gen::fn_sub_44A240_0044a240);
                                mtc1(s0, 0);
                                cvt_s_w(14, 0);
                                lq(v0, sp, 192);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                lwc1(1, sp, 296);
                                v0 = lui(0x41A0u);
                                mtc1(v0, 0);  // 20f
                                sub_s(12, 1, 0);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                mov_s(13, 20);
                                jal(0x449614u, &gen::fn_sub_44A240_0044a240);
                                mtc1(s0, 0);
                                cvt_s_w(14, 0);
                                lq(v0, sp, 176);
                                v0 = addiu(v0, 40);
                                a1 = dsll32(v0, 24);
                                a1 = dsra32(a1, 24);
                                v0 = lui(0x4040u);
                                mtc1(v0, 15);  // 3.0
                                a0 = s1;
                                lwc1(12, sp, 296);
                                mov_s(13, 20);
                                jal(0x44964Cu, &gen::fn_sub_44A240_0044a240);
                                goto L_0044970c;
                            }
                        }
                    }
                    charge(44);
                    lwc1(20, sp, 300);
                    v0 = addiu(s6, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x4220u);
                    mtc1(v0, 0);  // 40f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x449694u, &gen::fn_sub_44A330_0044a330);
                    v0 = addiu(s4, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x41A0u);
                    mtc1(v0, 0);  // 20f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x4496D0u, &gen::fn_sub_44A330_0044a330);
                    v0 = dsll32(s5, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 11);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    lwc1(12, sp, 296);
                    mov_s(13, 20);
                    jal(0x449704u, &gen::fn_sub_44A330_0044a330);
                }
            }
        }
      L_0044970c:
        charge(4);
        lq(v1, sp, 256);
        lq(v0, sp, 272);
        if (v1 != v0) {
            charge(5);
            v1 = lb(s3, 1179);
            v0 = dsll32(fp, 24);
            v0 = dsra32(v0, 24);
            if (v1 == v0) {
                charge(3);
                v0 = lb(s3, 1180);
                if (v0 == s2) {
                    charge(3);
                    v0 = si(1);
                    if (s7 == v0) {
                        charge(10);
                        a0 = 0;
                        a1 = lw(s3, 4);
                        a2 = si(26);
                        jal(0x449754u, &gen::fn_sprCreateHandle_001158b0);
                        s1 = v0;
                        sb(v0, 24, zero);
                        at = slti(s2, 10);
                        if (at != 0) {
                            charge(7);
                            v0 = lui(0x4080u);
                            mtc1(v0, 1);  // 4.0
                            lwc1(0, sp, 296);
                            add_s(0, 1, 0);
                            swc1(0, s1, 16);
                        } else {
                            charge(3);
                            at = slti(s2, 100);
                            if (at != 0) {
                                charge(7);
                                v0 = lui(0x4160u);
                                mtc1(v0, 1);  // 14f
                                lwc1(0, sp, 296);
                                add_s(0, 1, 0);
                                swc1(0, s1, 16);
                            } else {
                                charge(5);
                                v0 = lui(0x41C0u);
                                mtc1(v0, 1);  // 24f
                                lwc1(0, sp, 296);
                                add_s(0, 1, 0);
                                swc1(0, s1, 16);
                            }
                        }
                        charge(21);
                        lwc1(20, sp, 300);
                        swc1(20, s1, 20);
                        v0 = lui(0x4040u);
                        sw(s1, 44, v0);
                        a0 = s1;
                        a1 = si(1);
                        jal(0x4497E0u, &gen::fn_sub_1127D0_001127d0);
                        a0 = s1;
                        jal(0x4497ECu, &gen::fn_sub_115980_00115980);
                        a0 = 0;
                        a1 = lw(s3, 4);
                        a2 = si(50);
                        jal(0x449800u, &gen::fn_sprCreateHandle_001158b0);
                        s1 = v0;
                        sb(v0, 24, s0);
                        at = slti(s2, 10);
                        if (at != 0) {
                            charge(7);
                            v0 = lui(0x4080u);
                            mtc1(v0, 1);  // 4.0
                            lwc1(0, sp, 296);
                            add_s(0, 1, 0);
                            swc1(0, s1, 16);
                        } else {
                            charge(3);
                            at = slti(s2, 100);
                            if (at != 0) {
                                charge(7);
                                v0 = lui(0x4160u);
                                mtc1(v0, 1);  // 14f
                                lwc1(0, sp, 296);
                                add_s(0, 1, 0);
                                swc1(0, s1, 16);
                            } else {
                                charge(5);
                                v0 = lui(0x41C0u);
                                mtc1(v0, 1);  // 24f
                                lwc1(0, sp, 296);
                                add_s(0, 1, 0);
                                swc1(0, s1, 16);
                            }
                        }
                        charge(12);
                        swc1(20, s1, 20);
                        v0 = lui(0x4040u);
                        sw(s1, 44, v0);
                        a0 = s1;
                        a1 = si(1);
                        jal(0x449888u, &gen::fn_sub_1127D0_001127d0);
                        a0 = s1;
                        jal(0x449894u, &gen::fn_sub_115980_00115980);
                        goto L_00449c50;
                    }
                }
            }
            charge(10);
            a0 = 0;
            a1 = lw(s3, 4);
            a2 = si(26);
            jal(0x4498B0u, &gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            sb(v0, 24, zero);
            at = slti(s2, 10);
            if (at != 0) {
                charge(7);
                v0 = lui(0x4080u);
                mtc1(v0, 1);  // 4.0
                lwc1(0, sp, 296);
                add_s(0, 1, 0);
                swc1(0, s0, 16);
            } else {
                charge(3);
                at = slti(s2, 100);
                if (at != 0) {
                    charge(7);
                    v0 = lui(0x4160u);
                    mtc1(v0, 1);  // 14f
                    lwc1(0, sp, 296);
                    add_s(0, 1, 0);
                    swc1(0, s0, 16);
                } else {
                    charge(5);
                    v0 = lui(0x41C0u);
                    mtc1(v0, 1);  // 24f
                    lwc1(0, sp, 296);
                    add_s(0, 1, 0);
                    swc1(0, s0, 16);
                }
            }
            charge(13);
            lwc1(0, sp, 300);
            swc1(0, s0, 20);
            v0 = lui(0x4040u);
            sw(s0, 44, v0);
            a0 = s0;
            a1 = si(1);
            jal(0x44993Cu, &gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(0x449948u, &gen::fn_sub_115980_00115980);
        } else {
            charge(10);
            a0 = 0;
            a1 = lw(s3, 4);
            a2 = si(25);
            jal(0x449964u, &gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            sb(v0, 24, zero);
            at = slti(s2, 10);
            if (at != 0) {
                charge(7);
                v0 = lui(0x4080u);
                mtc1(v0, 1);  // 4.0
                lwc1(0, sp, 296);
                add_s(0, 1, 0);
                swc1(0, s0, 16);
            } else {
                charge(3);
                at = slti(s2, 100);
                if (at != 0) {
                    charge(7);
                    v0 = lui(0x4160u);
                    mtc1(v0, 1);  // 14f
                    lwc1(0, sp, 296);
                    add_s(0, 1, 0);
                    swc1(0, s0, 16);
                } else {
                    charge(5);
                    v0 = lui(0x41C0u);
                    mtc1(v0, 1);  // 24f
                    lwc1(0, sp, 296);
                    add_s(0, 1, 0);
                    swc1(0, s0, 16);
                }
            }
            charge(14);
            lwc1(0, sp, 300);
            swc1(0, s0, 20);
            v0 = lui(0x4040u);
            sw(s0, 44, v0);
            a0 = s0;
            a1 = si(1);
            jal(0x4499F0u, &gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(0x4499FCu, &gen::fn_sub_115980_00115980);
            at = slti(s2, 10);
            if (at != 0) {
                charge(32);
                lwc1(20, sp, 300);
                v0 = lui(0x4080u);
                mtc1(v0, 1);  // 4.0
                lwc1(0, sp, 296);
                add_s(12, 1, 0);
                mtc1(zero, 14);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s1;
                a1 = si(25);
                mov_s(13, 20);
                jal(0x449A3Cu, &gen::fn_sub_44A240_0044a240);
                v0 = dsll32(s5, 16);
                v0 = dsra32(v0, 16);
                v0 = addiu(v0, 15);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                lwc1(1, sp, 296);
                v0 = lui(0x41A0u);
                mtc1(v0, 0);  // 20f
                sub_s(12, 1, 0);
                mtc1(zero, 14);
                v0 = lui(0x4040u);
                mtc1(v0, 15);  // 3.0
                a0 = s1;
                mov_s(13, 20);
                jal(0x449A80u, &gen::fn_sub_44A240_0044a240);
            } else {
                charge(3);
                at = slti(s2, 100);
                if (at != 0) {
                    charge(49);
                    lwc1(20, sp, 300);
                    v0 = lui(0x4160u);
                    mtc1(v0, 1);  // 14f
                    lwc1(0, sp, 296);
                    add_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    a1 = si(25);
                    mov_s(13, 20);
                    jal(0x449AC8u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s4, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x41F0u);
                    mtc1(v0, 0);  // 30f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x449B0Cu, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s5, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x4120u);
                    mtc1(v0, 0);  // 10.0
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x449B50u, &gen::fn_sub_44A240_0044a240);
                } else {
                    charge(60);
                    lwc1(20, sp, 300);
                    v0 = lui(0x41C0u);
                    mtc1(v0, 1);  // 24f
                    lwc1(0, sp, 296);
                    add_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    a1 = si(25);
                    mov_s(13, 20);
                    jal(0x449B8Cu, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s6, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x4220u);
                    mtc1(v0, 0);  // 40f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x449BD0u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s4, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    lwc1(1, sp, 296);
                    v0 = lui(0x41A0u);
                    mtc1(v0, 0);  // 20f
                    sub_s(12, 1, 0);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    mov_s(13, 20);
                    jal(0x449C14u, &gen::fn_sub_44A240_0044a240);
                    v0 = dsll32(s5, 16);
                    v0 = dsra32(v0, 16);
                    v0 = addiu(v0, 15);
                    a1 = dsll32(v0, 24);
                    a1 = dsra32(a1, 24);
                    mtc1(zero, 14);
                    v0 = lui(0x4040u);
                    mtc1(v0, 15);  // 3.0
                    a0 = s1;
                    lwc1(12, sp, 296);
                    mov_s(13, 20);
                    jal(0x449C48u, &gen::fn_sub_44A240_0044a240);
                }
            }
        }
      L_00449c50:
        charge(16);
        ra = ld(sp, 160);
        lq(fp, sp, 144);
        lq(s7, sp, 128);
        lq(s6, sp, 112);
        lq(s5, sp, 96);
        lq(s4, sp, 80);
        lq(s3, sp, 64);
        lq(s2, sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 304);
    }

    // 0x449D60: steps the floor-list cursor (+2366, wrapping at the +2367 count; with 7 or more entries (+2368) the list
    // scrolls through +2369) until the entry's floor (record +6 + 4 i) is the record's current floor (+162); each step
    // stores the entry's position (sub_447F90) at +2372 / +2376.
    void sub_449D60() {
        enter(8);
        sp = addiu(sp, -80);
        sd(sp, 48, ra);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s2 = a0;
        s0 = lw(a0, kTaskWork);
        s1 = 0;
        for (;;) {
            charge(4);
            a2 = lb(s0, 2368);
            at = slti(a2, 7);
            if (at != 0) {
                charge(6);
                v0 = lb(s0, 2367);
                v1 = addiu(v0, -1);
                v0 = lb(s0, 2366);
                at = slt(v0, v1);
                if (at != 0) {
                    charge(4);
                    v0 = addiu(v0, 1);
                    sb(s0, 2366, v0);
                } else {
                    charge(3);
                    sb(s0, 2366, zero);
                }
            } else {
                charge(6);
                a1 = lb(s0, 2366);
                a0 = lb(s0, 2367);
                v0 = addiu(a0, -2);
                at = slt(a1, v0);
                if (at != 0) {
                    charge(4);
                    v0 = addiu(a1, 1);
                    sb(s0, 2366, v0);
                } else {
                    charge(5);
                    v1 = lb(s0, 2369);
                    v0 = subu(a2, a0);
                    at = slt(v1, v0);
                    if (at != 0) {
                        charge(4);
                        v0 = addiu(v1, 1);
                        sb(s0, 2369, v0);
                    } else {
                        charge(4);
                        v0 = addiu(a0, -1);
                        at = slt(a1, v0);
                        if (at != 0) {
                            charge(4);
                            v0 = addiu(a1, 1);
                            sb(s0, 2366, v0);
                        } else {
                            charge(2);
                            sb(s0, 2366, zero);
                            sb(s0, 2369, zero);
                        }
                    }
                }
            }
            charge(23);
            v1 = lb(s0, 2366);
            v0 = lb(s0, 2369);
            v0 = addu(v1, v0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = addiu(sp, 72);
            a1 = s2;
            jal(0x449E54u, &gen::fn_sub_447F90_00447f90);
            lwc1(1, sp, 72);
            lwc1(0, sp, 76);
            swc1(1, s0, 2372);
            swc1(0, s0, 2376);
            a1 = lw(gp, kGpStratum);
            a0 = lb(s0, 2366);
            v1 = lb(s0, 2369);
            v1 = addu(a0, v1);
            v1 = sll(v1, 2);
            v1 = addu(a1, v1);
            a0 = lh(v1, 6);
            v1 = lh(a1, 162);
            if (a0 == v1) {
                charge(1);
                s1 = si(1);
            }
            charge(4);
            v1 = dsll32(s1, 16);
            v1 = dsra32(v1, 16);
            if (v1 != 0) break;
            backedge();
        }
        charge(7);
        ra = ld(sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 80);
    }

    // 0x449FE0 (task, steps; $f12..$f15 the start / end x / y): with steps != 0 the position comes from sub_4222D0(sp,
    // 0, (s16) start x, (s16) end x, (s16) start y, (s16) end y, the s16 counter +238), which counts up to steps (returns 1
    // while it does); else the end point. Part 0 of the work's sprite file there, scale 3.0, alpha 0.
    void sub_449FE0() {
        enter(12);
        sp = addiu(sp, -80);
        sd(sp, 48, ra);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        a7 = a1;
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        s0 = dsll32(a7, 16);
        s0 = dsra32(s0, 16);
        if (s0 == 0) {
            charge(4);
            swc1(13, sp, 72);
            swc1(15, sp, 76);
        } else {
            charge(29);
            cvt_w_s(0, 12);
            mfc1(v0, 0);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            cvt_w_s(0, 13);
            mfc1(v0, 0);
            a3 = dsll32(v0, 16);
            a3 = dsra32(a3, 16);
            cvt_w_s(0, 14);
            mfc1(v0, 0);
            a4 = dsll32(v0, 16);
            a4 = dsra32(a4, 16);
            cvt_w_s(0, 15);
            mfc1(v0, 0);
            a5 = dsll32(v0, 16);
            a5 = dsra32(a5, 16);
            a0 = addiu(sp, 72);
            a1 = 0;
            a6 = lh(s1, 238);
            jal(0x44A07Cu, &gen::fn_sub_4222D0_004222d0);
            v0 = lh(s1, 238);
            at = slt(v0, s0);
            if (at != 0) {
                charge(3);
                v0 = addiu(v0, 1);
                sh(s1, 238, v0);
                s2 = si(1);
            }
        }
        charge(28);
        a0 = 0;
        a1 = lw(s1, 4);
        a2 = 0;
        jal(0x44A0ACu, &gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        sb(v0, 24, zero);
        lwc1(0, sp, 72);
        swc1(0, v0, 16);
        lwc1(0, sp, 76);
        swc1(0, v0, 20);
        v1 = lui(0x4040u);
        sw(v0, 44, v1);
        a0 = s0;
        a1 = si(1);
        jal(0x44A0DCu, &gen::fn_sub_1127D0_001127d0);
        a0 = s0;
        jal(0x44A0E8u, &gen::fn_sub_115980_00115980);
        v0 = s2;
        ra = ld(sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 80);
    }

    // 0x44A110: sub_449FE0 for part 1 with the counter +244.
    void sub_44A110() {
        enter(12);
        sp = addiu(sp, -80);
        sd(sp, 48, ra);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        a7 = a1;
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        s0 = dsll32(a7, 16);
        s0 = dsra32(s0, 16);
        if (s0 == 0) {
            charge(4);
            swc1(13, sp, 72);
            swc1(15, sp, 76);
        } else {
            charge(29);
            cvt_w_s(0, 12);
            mfc1(v0, 0);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            cvt_w_s(0, 13);
            mfc1(v0, 0);
            a3 = dsll32(v0, 16);
            a3 = dsra32(a3, 16);
            cvt_w_s(0, 14);
            mfc1(v0, 0);
            a4 = dsll32(v0, 16);
            a4 = dsra32(a4, 16);
            cvt_w_s(0, 15);
            mfc1(v0, 0);
            a5 = dsll32(v0, 16);
            a5 = dsra32(a5, 16);
            a0 = addiu(sp, 72);
            a1 = 0;
            a6 = lh(s1, 244);
            jal(0x44A1ACu, &gen::fn_sub_4222D0_004222d0);
            v0 = lh(s1, 244);
            at = slt(v0, s0);
            if (at != 0) {
                charge(3);
                v0 = addiu(v0, 1);
                sh(s1, 244, v0);
                s2 = si(1);
            }
        }
        charge(28);
        a0 = 0;
        a1 = lw(s1, 4);
        a2 = si(1);
        jal(0x44A1DCu, &gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        sb(v0, 24, zero);
        lwc1(0, sp, 72);
        swc1(0, v0, 16);
        lwc1(0, sp, 76);
        swc1(0, v0, 20);
        v1 = lui(0x4040u);
        sw(v0, 44, v1);
        a0 = s0;
        a1 = si(1);
        jal(0x44A20Cu, &gen::fn_sub_1127D0_001127d0);
        a0 = s0;
        jal(0x44A218u, &gen::fn_sub_115980_00115980);
        v0 = s2;
        ra = ld(sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 80);
    }

    // 0x44A420 (task, block, steps): the banner of block b: alpha = sub_421FE0(0, 0, 255, the record's s16 counter +124 + 6
    // b, steps) as u8 (2^31 split); state byte +166 + b == 0 draws the work's +628 + 4 b raster (sub_1140D0, 256 x 128)
    // and counts the fade up to steps; state 1 (b != 0) the +964 + 4 b raster likewise. Returns 1 while counting.
    void sub_44A420() {
        enter(29);
        sp = addiu(sp, -96);
        sd(sp, 80, ra);
        sq(s4, sp, 64);
        sq(s3, sp, 48);
        sq(s2, sp, 32);
        sq(s1, sp, 16);
        sq(s0, sp, 0);
        s4 = a1;
        s3 = a2;
        s1 = lw(a0, kTaskWork);
        s2 = 0;
        v0 = sll(s4, 1);
        v0 = addu(v0, s4);
        s0 = sll(v0, 1);
        v0 = lw(gp, kGpStratum);
        v0 = addu(s0, v0);
        a0 = 0;
        a1 = 0;
        a2 = si(255);
        a3 = lh(v0, 124);
        a4 = s3;
        jal(0x44A474u, &gen::fn_sub_421FE0_00421fe0);
        v0 = lui(0x4F00u);
        mtc1(v0, 1);  // 2^31
        c_le_s(1, 0);
        if (!cond()) {
            charge(4);
            cvt_w_s(0, 0);
            mfc1(v0, 0);
        } else {
            charge(5);
            sub_s(0, 0, 1);
            cvt_w_s(0, 0);
            mfc1(v0, 0);
            v1 = lui(0x8000u);
            v0 = v0 | v1;
        }
        charge(6);
        a0 = lw(gp, kGpStratum);
        v1 = addiu(a0, 166);
        v1 = addu(v1, s4);
        v1 = lb(v1, 0);
        if (v1 == 0) {
            charge(32);
            a1 = sll(s4, 3);
            v1 = lui(0x4080u);
            mtc1(v1, 12);  // 4.0
            v1 = si(-256);
            a0 = v0 | v1;
            v1 = addu(a1, s1);
            lwc1(1, v1, 716);
            v0 = lui(0x4300u);
            mtc1(v0, 0);  // 128.0
            sub_s(13, 1, 0);
            lwc1(1, v1, 720);
            v0 = lui(0x4280u);
            mtc1(v0, 0);  // 64f
            sub_s(14, 1, 0);
            v0 = sll(s4, 2);
            v0 = addu(v0, s1);
            a1 = si(256);
            a2 = si(128);
            a3 = lw(v0, 628);
            jal(0x44A524u, &gen::fn_sub_1140D0_001140d0);
            v0 = lw(gp, kGpStratum);
            v0 = addiu(v0, 124);
            a0 = addu(v0, s0);
            v1 = lh(a0, 0);
            v0 = dsll32(s3, 16);
            v0 = dsra32(v0, 16);
            at = slt(v1, v0);
            if (at != 0) {
                charge(5);
                v0 = addiu(v1, 1);
                sh(a0, 0, v0);
                s2 = si(1);
            }
        } else {
            charge(3);
            a2 = si(1);
            if (v1 == a2) {
                charge(2);
                if (s4 != 0) {
                    charge(8);
                    v1 = addiu(a0, 124);
                    a1 = addu(v1, s0);
                    a0 = lh(a1, 0);
                    v1 = dsll32(s3, 16);
                    v1 = dsra32(v1, 16);
                    at = slt(a0, v1);
                    if (at != 0) {
                        charge(4);
                        v1 = addiu(a0, 1);
                        sh(a1, 0, v1);
                        s2 = dsll32(a2, 24);
                        s2 = dsra32(s2, 24);
                    }
                    charge(23);
                    a1 = sll(s4, 3);
                    v1 = lui(0x4080u);
                    mtc1(v1, 12);  // 4.0
                    v1 = si(-256);
                    a0 = v0 | v1;
                    v1 = addu(a1, s1);
                    lwc1(1, v1, 716);
                    v0 = lui(0x4300u);
                    mtc1(v0, 0);  // 128.0
                    sub_s(13, 1, 0);
                    lwc1(1, v1, 712);
                    v0 = lui(0x4280u);
                    mtc1(v0, 0);  // 64f
                    sub_s(14, 1, 0);
                    v0 = sll(s4, 2);
                    v0 = addu(v0, s1);
                    a1 = si(256);
                    a2 = si(128);
                    a3 = lw(v0, 964);
                    jal(0x44A5FCu, &gen::fn_sub_1140D0_001140d0);
                }
            }
        }
        charge(10);
        v0 = s2;
        ra = ld(sp, 80);
        lq(s4, sp, 64);
        lq(s3, sp, 48);
        lq(s2, sp, 32);
        lq(s1, sp, 16);
        lq(s0, sp, 0);
        sp = addiu(sp, 96);
    }

    // 0x44A790 (rec): vertex rec->+16 (64-byte Im2D vertices) of the array at **rec. The screen point (640 rec->+4,
    // 448 rec->+8) relative to the centre (320, 224) as a radius r = sqrt(dx^2 + dy^2) and an angle (atan2f); r' = r + 20
    // sin(2 (r / 200 - phase) gp[-32184]) with phase = (f32) the s32 at rec->+12 -> +1152 / 180. The vertex: x / y = the
    // point, u / v = (320 + r' sinf(angle)) / 640, (224 + r' cosf(angle)) / 448 (sub_269C80 / sub_269CA0), rgba 255.0 x 4,
    // z = the Im2D near screen z (0x960088) - 100, +24 = 1 / (main camera +128) (kwlnGetMainCamera sub_198590).
    void sub_44A790() {
        enter(128);
        sp = addiu(sp, -80);
        sd(sp, 64, ra);
        sq(s1, sp, 48);
        sq(s0, sp, 32);
        swc1(25, sp, 20);
        swc1(24, sp, 16);
        swc1(23, sp, 12);
        swc1(22, sp, 8);
        swc1(21, sp, 4);
        swc1(20, sp, 0);
        s1 = a0;
        s0 = lw(a0, 12);
        jal(0x44A7C0u, &gen::fn_sub_198590_00198590);
        v1 = lui(0x3F80u);
        mtc1(v1, 1);  // 1.0
        lwc1(0, v0, 128);
        div_s(25, 1, 0);
        lwc1(0, s0, 1152);
        cvt_s_w(1, 0);
        v0 = lui(0x4334u);
        mtc1(v0, 0);  // 180f
        div_s(22, 1, 0);
        v0 = lw(s1, 16);
        v1 = sll(v0, 6);
        v0 = lw(s1, 0);
        v0 = lw(v0, 0);
        s0 = addu(v0, v1);
        v0 = lui(0x4420u);
        mtc1(v0, 1);  // 640f
        lwc1(0, s1, 4);
        mul_s(24, 1, 0);
        v0 = lui(0x43E0u);
        mtc1(v0, 1);  // 448f
        lwc1(0, s1, 8);
        mul_s(23, 1, 0);
        v0 = lui(0x43A0u);
        mtc1(v0, 0);  // 320f
        sub_s(12, 24, 0);
        v0 = lui(0x4360u);
        mtc1(v0, 0);  // 224f
        sub_s(13, 23, 0);
        mula_s(13, 13);
        madd_s(0, 12, 12);
        sqrt_s(21, 0);
        jal(0x44A85Cu, &gen::fn_atan2f_0052ea18);
        mov_s(20, 0);
        v0 = lui(0x4348u);
        mtc1(v0, 0);  // 200f
        div_s(0, 21, 0);
        sub_s(1, 0, 22);
        v0 = lui(0x4000u);
        mtc1(v0, 0);  // 2.0
        mul_s(1, 0, 1);
        lwc1(0, gp, -32184);
        mul_s(12, 0, 1);
        jal(0x44A894u, &gen::fn_sinf_0052e878);
        v0 = lui(0x41A0u);
        mtc1(v0, 2);  // 20f
        mtc1(zero, 1);
        adda_s(1, 21);
        madd_s(22, 2, 0);
        mov_s(12, 20);
        jal(0x44A8B8u, &gen::fn_sub_269C80_00269c80);
        v0 = lui(0x43A0u);
        mtc1(v0, 2);  // 320f
        mtc1(zero, 1);
        adda_s(1, 2);
        madd_s(21, 22, 0);
        mov_s(12, 20);
        jal(0x44A8DCu, &gen::fn_sub_269CA0_00269ca0);
        v1 = lui(0x4360u);
        mtc1(v1, 2);  // 224f
        mtc1(zero, 1);
        adda_s(1, 2);
        madd_s(1, 22, 0);
        swc1(24, s0, 0);
        swc1(23, s0, 4);
        v1 = lui(0x4420u);
        mtc1(v1, 0);  // 640f
        div_s(0, 21, 0);
        swc1(0, s0, 16);
        v1 = lui(0x43E0u);
        mtc1(v1, 0);  // 448f
        div_s(0, 1, 0);
        swc1(0, s0, 20);
        v1 = lui(0x437Fu);
        sw(s0, 32, v1);
        sw(s0, 36, v1);
        sw(s0, 40, v1);
        sw(s0, 44, v1);
        v1 = lui(0x96u);
        lwc1(1, v1, 136);  // 0x960088 g_rwIm2DNearScreenZ
        v1 = lui(0x42C8u);
        mtc1(v1, 0);  // 100.0
        sub_s(0, 1, 0);
        swc1(0, s0, 8);
        swc1(25, s0, 24);
        ra = ld(sp, 64);
        lq(s1, sp, 48);
        lq(s0, sp, 32);
        lwc1(25, sp, 20);
        lwc1(24, sp, 16);
        lwc1(23, sp, 12);
        lwc1(22, sp, 8);
        lwc1(21, sp, 4);
        lwc1(20, sp, 0);
        sp = addiu(sp, 80);
    }
};

// @@STRUCTS@@

}  // namespace

// --- typed entry points -------------------------------------------------------------------------------------------------
void sub_447F90(EEContext& ctx, u64 out, u64 task, u64 i) { set_args(ctx, {out, task, i}); Stratum{ctx}.sub_447F90(); }
u32 sub_449C90(EEContext& ctx, u64 task, u64 i) { set_args(ctx, {task, i}); Stratum{ctx}.sub_449C90(); return static_cast<u32>(v0_of(ctx)); }
void sub_449D10(EEContext& ctx, u64 task) { set_args(ctx, {task}); Stratum{ctx}.sub_449D10(); }
void sub_44A240(EEContext& ctx, u64 task, u64 index) { set_args(ctx, {task, index}); Stratum{ctx}.sub_44A240(); }
void sub_44A330(EEContext& ctx, u64 task, u64 index) { set_args(ctx, {task, index}); Stratum{ctx}.sub_44A330(); }
void sub_44A630(EEContext& ctx, u64 task) { set_args(ctx, {task}); Stratum{ctx}.sub_44A630(); }
void sub_448060(EEContext& ctx, u64 task, u64 i, u64 xy, u64 block, u64 floor, u64 active) { set_args(ctx, {task, i, xy, block, floor, active}); Stratum{ctx}.sub_448060(); }
void sub_448CF0(EEContext& ctx, u64 task, u64 i, u64 xy, u64 block, u64 floor, u64 active, u64 alpha) { set_args(ctx, {task, i, xy, block, floor, active, alpha}); Stratum{ctx}.sub_448CF0(); }
void sub_449D60(EEContext& ctx, u64 task) { set_args(ctx, {task}); Stratum{ctx}.sub_449D60(); }
u32 sub_449FE0(EEContext& ctx, u64 task, u64 steps) { set_args(ctx, {task, steps}); Stratum{ctx}.sub_449FE0(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44A110(EEContext& ctx, u64 task, u64 steps) { set_args(ctx, {task, steps}); Stratum{ctx}.sub_44A110(); return static_cast<u32>(v0_of(ctx)); }
u32 sub_44A420(EEContext& ctx, u64 task, u64 block, u64 steps) { set_args(ctx, {task, block, steps}); Stratum{ctx}.sub_44A420(); return static_cast<u32>(v0_of(ctx)); }
void sub_44A790(EEContext& ctx, u64 rec) { set_args(ctx, {rec}); Stratum{ctx}.sub_44A790(); }
// @@API@@

}  // namespace p3fes::game

// =====================================================================================================================
// The recompiled program's entry points (recomp/generated/functions.h signatures)
// =====================================================================================================================
namespace p3fes::recomp_gen {
namespace g = p3fes::game;
void fn_sub_447F90_00447f90(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_447F90(); }
void fn_sub_449C90_00449c90(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_449C90(); }
void fn_sub_449D10_00449d10(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_449D10(); }
void fn_sub_44A240_0044a240(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_44A240(); }
void fn_sub_44A330_0044a330(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_44A330(); }
void fn_sub_44A630_0044a630(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_44A630(); }
void fn_sub_448060_00448060(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_448060(); }
void fn_sub_448CF0_00448cf0(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_448CF0(); }
void fn_sub_449D60_00449d60(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_449D60(); }
void fn_sub_449FE0_00449fe0(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_449FE0(); }
void fn_sub_44A110_0044a110(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_44A110(); }
void fn_sub_44A420_0044a420(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_44A420(); }
void fn_sub_44A790_0044a790(p3fes::EEContext& ctx) { g::Stratum{ctx}.sub_44A790(); }
// @@SHIMS@@
}  // namespace p3fes::recomp_gen
