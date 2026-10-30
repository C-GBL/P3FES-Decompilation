// Phase 5 slice cri1 -- ADXB: the ADX / AHX / WAV / AIFF / SPSD header parsers and the ADPCM decoder objects (ADXPD).
// p3fes_handgen bodies made readable (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body keeps the
// recompiled body's registers, frame, spills, $ra links, cycle charges and check points. Roles, proposed names and
// record layouts: game/include/p3fes/game/cri1.h. Pair tests: tests/game/test_cri1.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/cri1.h"

namespace p3fes::recomp_gen {
void fn__ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3_00562210(p3fes::EEContext&);
void fn__get_peer_or_sock_name_3_0053a358(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_cvFsInit_00555940(p3fes::EEContext&);
void fn_cvfs_getDefDev_00556330(p3fes::EEContext&);
void fn_cvfs_getDevName_005561e8(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sqrtf_0052ea60(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_538EF0_00538ef0(p3fes::EEContext&);
void fn_sub_538F18_00538f18(p3fes::EEContext&);
void fn_sub_539148_00539148(p3fes::EEContext&);
void fn_sub_5396F8_005396f8(p3fes::EEContext&);
void fn_sub_5397B8_005397b8(p3fes::EEContext&);
void fn_sub_5397E8_005397e8(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_539858_00539858(p3fes::EEContext&);
void fn_sub_5399B8_005399b8(p3fes::EEContext&);
void fn_sub_539A38_00539a38(p3fes::EEContext&);
void fn_sub_539AE0_00539ae0(p3fes::EEContext&);
void fn_sub_539BE0_00539be0(p3fes::EEContext&);
void fn_sub_539C60_00539c60(p3fes::EEContext&);
void fn_sub_539CD8_00539cd8(p3fes::EEContext&);
void fn_sub_539E10_00539e10(p3fes::EEContext&);
void fn_sub_539ED8_00539ed8(p3fes::EEContext&);
void fn_sub_53A138_0053a138(p3fes::EEContext&);
void fn_sub_53A3B8_0053a3b8(p3fes::EEContext&);
void fn_sub_53A410_0053a410(p3fes::EEContext&);
void fn_sub_53AD00_0053ad00(p3fes::EEContext&);
void fn_sub_54CB78_0054cb78(p3fes::EEContext&);
void fn_sub_54CBA0_0054cba0(p3fes::EEContext&);
void fn_sub_54CBC8_0054cbc8(p3fes::EEContext&);
void fn_sub_54CC98_0054cc98(p3fes::EEContext&);
void fn_sub_54CCC0_0054ccc0(p3fes::EEContext&);
void fn_sub_54CCE8_0054cce8(p3fes::EEContext&);
void fn_sub_54CD10_0054cd10(p3fes::EEContext&);
void fn_sub_54CD40_0054cd40(p3fes::EEContext&);
void fn_sub_54CD78_0054cd78(p3fes::EEContext&);
void fn_sub_54CD80_0054cd80(p3fes::EEContext&);
void fn_sub_54CD88_0054cd88(p3fes::EEContext&);
void fn_sub_54CDB8_0054cdb8(p3fes::EEContext&);
void fn_sub_54CDE8_0054cde8(p3fes::EEContext&);
void fn_sub_54CE38_0054ce38(p3fes::EEContext&);
void fn_sub_54CE60_0054ce60(p3fes::EEContext&);
void fn_sub_54CE78_0054ce78(p3fes::EEContext&);
void fn_sub_54CE80_0054ce80(p3fes::EEContext&);
void fn_sub_54CE90_0054ce90(p3fes::EEContext&);
void fn_sub_54CF88_0054cf88(p3fes::EEContext&);
void fn_sub_5558E8_005558e8(p3fes::EEContext&);
void fn_sub_555918_00555918(p3fes::EEContext&);
void fn_sub_555D10_00555d10(p3fes::EEContext&);
void fn_sub_561758_00561758(p3fes::EEContext&);
void fn_sub_5617C0_005617c0(p3fes::EEContext&);
void fn_sub_5617D8_005617d8(p3fes::EEContext&);
void fn_sub_5617F0_005617f0(p3fes::EEContext&);
void fn_sub_561808_00561808(p3fes::EEContext&);
void fn_sub_561828_00561828(p3fes::EEContext&);
void fn_sub_561870_00561870(p3fes::EEContext&);
void fn_sub_5618A0_005618a0(p3fes::EEContext&);
void fn_sub_5618F0_005618f0(p3fes::EEContext&);
void fn_sub_561920_00561920(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_5619B8_005619b8(p3fes::EEContext&);
void fn_sub_561A80_00561a80(p3fes::EEContext&);
void fn_sub_561AB0_00561ab0(p3fes::EEContext&);
void fn_sub_561B38_00561b38(p3fes::EEContext&);
void fn_sub_561B70_00561b70(p3fes::EEContext&);
void fn_sub_561BC8_00561bc8(p3fes::EEContext&);
void fn_sub_561C18_00561c18(p3fes::EEContext&);
void fn_sub_561C78_00561c78(p3fes::EEContext&);
void fn_sub_561CA8_00561ca8(p3fes::EEContext&);
void fn_sub_561D10_00561d10(p3fes::EEContext&);
void fn_sub_561D58_00561d58(p3fes::EEContext&);
void fn_sub_561DB8_00561db8(p3fes::EEContext&);
void fn_sub_561E98_00561e98(p3fes::EEContext&);
void fn_sub_561EE8_00561ee8(p3fes::EEContext&);
void fn_sub_561F88_00561f88(p3fes::EEContext&);
void fn_sub_561FD8_00561fd8(p3fes::EEContext&);
void fn_sub_5620D8_005620d8(p3fes::EEContext&);
void fn_sub_562140_00562140(p3fes::EEContext&);
void fn_sub_562220_00562220(p3fes::EEContext&);
void fn_sub_562240_00562240(p3fes::EEContext&);
void fn_sub_562288_00562288(p3fes::EEContext&);
void fn_sub_5622B8_005622b8(p3fes::EEContext&);
void fn_sub_562308_00562308(p3fes::EEContext&);
void fn_sub_562338_00562338(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_5623E0_005623e0(p3fes::EEContext&);
void fn_sub_5624B0_005624b0(p3fes::EEContext&);
void fn_sub_5624E0_005624e0(p3fes::EEContext&);
void fn_sub_562568_00562568(p3fes::EEContext&);
void fn_sub_562570_00562570(p3fes::EEContext&);
void fn_sub_562580_00562580(p3fes::EEContext&);
void fn_sub_5625B0_005625b0(p3fes::EEContext&);
void fn_sub_562630_00562630(p3fes::EEContext&);
void fn_sub_562680_00562680(p3fes::EEContext&);
void fn_sub_5626E0_005626e0(p3fes::EEContext&);
void fn_sub_562880_00562880(p3fes::EEContext&);
void fn_sub_5628D0_005628d0(p3fes::EEContext&);
void fn_sub_562A50_00562a50(p3fes::EEContext&);
void fn_sub_562AA0_00562aa0(p3fes::EEContext&);
void fn_sub_562C80_00562c80(p3fes::EEContext&);
void fn_sub_562CE8_00562ce8(p3fes::EEContext&);
void fn_sub_562DE0_00562de0(p3fes::EEContext&);
void fn_sub_562DE8_00562de8(p3fes::EEContext&);
void fn_sub_562DF0_00562df0(p3fes::EEContext&);
void fn_sub_562DF8_00562df8(p3fes::EEContext&);
void fn_sub_562E10_00562e10(p3fes::EEContext&);
void fn_sub_562E28_00562e28(p3fes::EEContext&);
void fn_sub_562E48_00562e48(p3fes::EEContext&);
void fn_sub_562E90_00562e90(p3fes::EEContext&);
void fn_sub_562EC0_00562ec0(p3fes::EEContext&);
void fn_sub_562F10_00562f10(p3fes::EEContext&);
void fn_sub_562F40_00562f40(p3fes::EEContext&);
void fn_sub_562F90_00562f90(p3fes::EEContext&);
void fn_sub_562FE8_00562fe8(p3fes::EEContext&);
void fn_sub_5630D0_005630d0(p3fes::EEContext&);
void fn_sub_563100_00563100(p3fes::EEContext&);
void fn_sub_563188_00563188(p3fes::EEContext&);
void fn_sub_5631C0_005631c0(p3fes::EEContext&);
void fn_sub_563218_00563218(p3fes::EEContext&);
void fn_sub_563268_00563268(p3fes::EEContext&);
void fn_sub_5632C8_005632c8(p3fes::EEContext&);
void fn_sub_5632F8_005632f8(p3fes::EEContext&);
void fn_sub_5633D0_005633d0(p3fes::EEContext&);
void fn_sub_563418_00563418(p3fes::EEContext&);
void fn_sub_5634D0_005634d0(p3fes::EEContext&);
void fn_sub_563530_00563530(p3fes::EEContext&);
void fn_sub_563680_00563680(p3fes::EEContext&);
void fn_sub_5636D0_005636d0(p3fes::EEContext&);
void fn_sub_5637F8_005637f8(p3fes::EEContext&);
void fn_sub_563848_00563848(p3fes::EEContext&);
void fn_sub_563968_00563968(p3fes::EEContext&);
void fn_sub_5639D0_005639d0(p3fes::EEContext&);
void fn_sub_563A98_00563a98(p3fes::EEContext&);
void fn_sub_563AE0_00563ae0(p3fes::EEContext&);
void fn_sub_563B70_00563b70(p3fes::EEContext&);
void fn_sub_563BA8_00563ba8(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564888_00564888(p3fes::EEContext&);
void fn_sub_5648E8_005648e8(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_5649A8_005649a8(p3fes::EEContext&);
void fn_sub_5649C0_005649c0(p3fes::EEContext&);
void fn_sub_5649D8_005649d8(p3fes::EEContext&);
void fn_sub_5649F0_005649f0(p3fes::EEContext&);
void fn_sub_564A20_00564a20(p3fes::EEContext&);
void fn_sub_564A38_00564a38(p3fes::EEContext&);
void fn_sub_564A50_00564a50(p3fes::EEContext&);
void fn_sub_564A68_00564a68(p3fes::EEContext&);
void fn_sub_564AA8_00564aa8(p3fes::EEContext&);
void fn_sub_564B50_00564b50(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
void fn_width__CQ24_STL8ios_base_0_00562218(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace adx = cri1::adx;
namespace adxpd = cri1::adxpd;

// 0x00538EF0 sub_538EF0 -- 40 bytes; frame 0x10: ra sp+0x0
// Is the buffer an SPSD header ("SPSD" at +0)? 1 / 0. [spsd_IsHeader]
void sub_538EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538ef0
    enter(ctx, 10);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    sp = addiu(sp, -0x10);
    a2 = 4;
    sd(ra, sp, 0x0);
    a1 = addiu(a1, 6672);  // "SPSD"
    jal(ctx, 0x538F00u, gen::fn_memcmp_005211b8);
    ld(ra, sp, 0x0);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00538F18 sub_538F18 -- 560 bytes; frame 0x60: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s6 sp+0x40, s7 sp+0x48, fp sp+0x50, s5 sp+0x38, ra sp+0x58
// Parse a RIFF / WAVE header: the "fmt " chunk (4-byte aligned; format tag below 2, channels, rate, block align,
// bits) and the "data" chunk (data offset, sample count = size / block align); 16-bit, 8-bit and 4-bit kinds (the tag
// pointers at 0x784930 / 0x784934). [wav_DecodeHeader]
void sub_538F18(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00538f18
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x10);
    s0 = 0;
    sd(s1, sp, 0x18);
    s1 = 0x780000;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s4, sp, 0x30);
    s4 = t0;
    sd(s6, sp, 0x40);
    s6 = t2;
    sd(s7, sp, 0x48);
    s7 = t1;
    sd(fp, sp, 0x50);
    fp = a2;
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x58);
    sw(a3, sp, 0x0);
    sw(t3, sp, 0x4);
    for (;;) {
        // 0x00538f70
        charge(ctx, 3);
        v0 = slt(s0, s2);
        lw(a1, s1, 18736);
        if (v0 != 0) {
            // 0x00538f7c
            charge(ctx, 5);
            a0 = addu(s3, s0);
            a2 = 4;
            jal(ctx, 0x538F80u, gen::fn_memcmp_005211b8);
            if (v0 != 0) {
                s0 = addiu(s0, 1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x00538f90
    charge(ctx, 2);
    v0 = si(-1);
    if (s0 != s2) {
        // 0x00538f98
        charge(ctx, 3);
        v1 = s0 & 0x3;
        if (v1 != 0) {
            ld(s0, sp, 0x10);
        L_0053911c:
            charge(ctx, 1);
            ld(s1, sp, 0x18);
        } else {
            // 0x00538fa4
            charge(ctx, 6);
            a0 = addu(s3, s0);
            s1 = addiu(a0, 8);
            lh(v1, s1, 0);
            v1 = slti(v1, 2);
            if (v1 == 0) {
                ld(s0, sp, 0x10);
                goto L_0053911c;
            }
            // 0x00538fbc
            charge(ctx, 3);
            s0 = 0;
            s5 = 0x780000;
            for (;;) {
                // 0x00538fc8
                charge(ctx, 3);
                v0 = slt(s0, s2);
                lw(a1, s5, 18740);
                if (v0 != 0) {
                    // 0x00538fd4
                    charge(ctx, 5);
                    a0 = addu(s3, s0);
                    a2 = 4;
                    jal(ctx, 0x538FD8u, gen::fn_memcmp_005211b8);
                    if (v0 != 0) {
                        s0 = addiu(s0, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            // 0x00538fe8
            charge(ctx, 2);
            v0 = si(-1);
            if (s0 == s2) {
                goto L_00539118;
            }
            // 0x00538ff0
            charge(ctx, 23);
            v0 = addiu(s0, 8);
            v1 = addu(s3, s0);
            sh(v0, fp, 0x0);
            a0 = si(-1);
            lw(a2, v1, 4);
            a3 = 1;
            lw(v0, sp, 0x0);
            t0 = 16;
            sb(a0, v0, 0);
            lw(v0, s1, 4);
            lw(a0, sp, 0x4);
            lbu(v1, s1, 2);
            sw(v0, a0, 0);
            sb(v1, s6, 0);
            lbu(v0, s1, 14);
            sb(v0, s4, 0);
            lbu(v1, s1, 12);
            v0 = sll(v1, 24);
            sb(v1, s7, 0);
            v0 = sra(v0, 24);
            div(a2, v0);
            if (v0 == 0) {
                brk(ctx, 0x539048u, 0x7u);
            }
            // 0x0053904c
            charge(ctx, 8);
            lw(v0, sp, 0x60);
            mflo(v1);
            sw(v1, v0, 0);
            lw(a0, sp, 0x68);
            sw(a3, a0, 0);
            lb(a1, s4, 0);
            lbu(v1, s4, 0);
            if (a1 == t0) {
                // 0x0053906c
                charge(ctx, 3);
                lw(v0, sp, 0x70);
                sh(zero, v0, 0);
                goto L_005390e0;
            }
            // 0x00539078
            charge(ctx, 3);
            v0 = 8;
            cc = a1 != v0;  // the condition, before the delay slot changes it
            v0 = 4;
            if (!cc) {
                // 0x00539084
                charge(ctx, 3);
                lw(a0, sp, 0x70);
                sh(a3, a0, 0);
                goto L_005390e0;
            }
            // 0x00539090
            charge(ctx, 2);
            a0 = 2;
            if (a1 == v0) {
                // 0x00539098
                charge(ctx, 12);
                lb(v0, s6, 0);
                v1 = srl(a2, 31);
                v1 = addu(a2, v1);
                v0 = sll(v0, 1);
                v1 = sra(v1, 1);
                sb(v0, s7, 0);
                lw(v0, sp, 0x68);
                sw(a1, v0, 0);
                lb(v0, s6, 0);
                div(v1, v0);
                if (v0 == 0) {
                    brk(ctx, 0x5390C4u, 0x7u);
                }
                // 0x005390c8
                charge(ctx, 6);
                lw(v0, sp, 0x60);
                mflo(v1);
                sw(v1, v0, 0);
                sb(t0, s4, 0);
                lw(v0, sp, 0x70);
                sh(a0, v0, 0);
            L_005390e0:
                charge(ctx, 1);
                lbu(v1, s4, 0);
            }
            // 0x005390e4
            charge(ctx, 2);
            v0 = si(-1);
            if (v1 == 0) {
                goto L_00539118;
            }
            // 0x005390ec
            charge(ctx, 3);
            lb(v1, s7, 0);
            ld(s0, sp, 0x10);
            if (v1 == 0) {
                goto L_0053911c;
            }
            // 0x005390f8
            charge(ctx, 5);
            lbu(v1, s6, 0);
            v1 = addiu(v1, -1);
            v1 = sltiu(v1, 2);
            ld(s1, sp, 0x18);
            if (v1 != 0) {
                // 0x0053910c
                charge(ctx, 3);
                lw(a0, sp, 0x4);
                lw(v1, a0, 0);
                if (v1 != 0) v0 = 0;
                goto L_00539118;
            }
        }
        // 0x00539120 (the shared epilogue, written out on this path)
        charge(ctx, 10);
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
L_00539118:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    goto L_0053911c;
}

// 0x00539148 sub_539148 -- 252 bytes; frame 0x60: s0 sp+0x30, s4 sp+0x50, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, ra sp+0x58, s2 sp+0x8
// Fill a decoder record (+12 ... +156) from a WAV header (sub_538F18) and reset its counters; returns the data
// offset. [wav_SetupDecoder]
void sub_539148(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00539148
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s4, sp, 0x50);
    s4 = 1;
    sd(s1, sp, 0x38);
    s1 = addiu(s0, 14);
    sd(s2, sp, 0x40);
    s2 = addiu(s0, 16);
    sd(s3, sp, 0x48);
    s3 = addiu(s0, 15);
    sd(ra, sp, 0x58);
    a0 = a1;
    sh(s4, s0, 2);
    v0 = addiu(s0, 24);
    a1 = a2;
    a2 = addiu(sp, 0x20);
    v1 = addiu(s0, 156);
    a3 = addiu(s0, 12);
    t0 = addiu(s0, 13);
    t1 = s3;
    t2 = s1;
    t3 = addiu(s0, 20);
    sw(v0, sp, 0x0);
    sw(v1, sp, 0x10);
    link(ctx, 0x5391ACu);  // $ra first: the delay slot below depends on it
    sw(s2, sp, 0x8);
    call(ctx, gen::fn_sub_538F18_00538f18);
    if (i64(v0) >= 0) {
        sw(zero, s0, 52);
        // 0x005391c8
        charge(ctx, 23);
        sw(zero, s0, 48);
        sw(zero, s0, 44);
        sw(zero, s0, 40);
        sw(zero, s0, 32);
        sh(zero, s0, 28);
        sh(zero, s0, 38);
        sh(zero, s0, 36);
        lw(a1, s0, 60);
        lb(v1, s1, 0);
        lw(a2, s0, 64);
        sw(v1, s0, 80);
        lw(a3, s0, 68);
        lb(a0, s3, 0);
        lh(v0, sp, 0x20);
        sw(a0, s0, 84);
        sh(s4, s0, 152);
        lw(v1, s2, 0);
        sw(a1, s0, 92);
        sw(a2, s0, 96);
        sw(v1, s0, 88);
        sw(a3, s0, 100);
        sw(zero, s0, 140);
        sw(zero, s0, 136);
    } else {
        // 0x005391bc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00539224 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x005396F8 sub_5396F8 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Is the buffer a RIFF / WAVE header ("RIFF" at +0, "WAVE" at +8)? 1 / 0. [wav_IsHeader]
void sub_5396F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005396f8
    enter(ctx, 13);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    sp = addiu(sp, -0x10);
    a2 = 4;
    a1 = addiu(a1, 6696);  // "RIFF"
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x539710u, gen::fn_memcmp_005211b8);
    a1 = 0x7C0000;
    a0 = addiu(s0, 8);
    a1 = addiu(a1, 6704);  // "WAVE"
    a2 = 4;
    if (v0 != 0) {
        // 0x00539748
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0053972c
        charge(ctx, 4);
        jal(ctx, 0x53972Cu, gen::fn_memcmp_005211b8);
        if (v0 != 0) {
            v0 = 0;
        } else {
            // 0x0053973c
            charge(ctx, 2);
            v0 = 1;
        }
    }
    // 0x0053974c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005397B8 sub_5397B8 -- 48 bytes; leaf frame (no stack)
// ADXB lock counter: +1 (the first lock clears 0x784938). [adxb_Lock]
void sub_5397B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005397b8
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = 0x780000;
    a1 = 1;
    v1 = addiu(v1, 18752);  // &0x784940
    lw(v0, v1, 0);  // 0x784940
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x784940
    lw(a0, v1, 0);  // 0x784940
    v0 = 0x780000;
    if (a0 == a1) {
        // 0x005397dc
        charge(ctx, 1);
        sw(zero, v0, 18744);
    }
    // 0x005397e0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005397E8 sub_5397E8 -- 44 bytes; leaf frame (no stack)
// ADXB lock counter: -1 (the last unlock clears 0x784938). [adxb_Unlock]
void sub_5397E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005397e8
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x780000;
    v0 = addiu(v0, 18752);  // &0x784940
    lw(v1, v0, 0);  // 0x784940
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x784940
    lw(a0, v0, 0);  // 0x784940
    v0 = 0x780000;
    if (a0 == 0) {
        // 0x00539808
        charge(ctx, 1);
        sw(zero, v0, 18744);
    }
    // 0x0053980c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00539848 sub_539848 -- 8 bytes; leaf frame (no stack)
// The empty lock stub of the ADX libraries (100 callers; `jr $ra`). [adx_EnterCs (stub)]
void sub_539848(EEContext& ctx) {
    using namespace hg;
    // 0x00539848
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00539850 sub_539850 -- 8 bytes; leaf frame (no stack)
// The empty unlock stub of the ADX libraries (100 callers; `jr $ra`). [adx_LeaveCs (stub)]
void sub_539850(EEContext& ctx) {
    using namespace hg;
    // 0x00539850
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00539858 sub_539858 -- 348 bytes; frame 0x40: f22 sp+0x38, f20 sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, f21 sp+0x30, ra sp+0x20
// The ADX prediction coefficients from a high-pass cutoff and a sample rate (floats: sqrtf, cosf): a = sqrt2 - cos(2
// pi cutoff / rate), b = sqrt2 - 1, c = (a - sqrt((a + b)(a - b))) / b; coef1 = (s16)(2c * 4096), coef2 = (s16)(-c^2
// * 4096). [adx_CalcCoefficients]
void sub_539858(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00539858
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    swc1(f22, sp, 0x38);
    at = 0x40000000;
    mtc1(at, f22);
    swc1(f20, sp, 0x28);
    sqrt_s(f20, f22);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a2;
    swc1(f21, sp, 0x30);
    s0 = a0;
    sd(ra, sp, 0x20);
    mov_s(f12, f22);
    c_eq_s(f20, f20);
    mov_s(f21, f20);
    if (!cond(ctx)) {
        // 0x005398b0
        charge(ctx, 3);
        jal(ctx, 0x5398B0u, gen::fn_sqrtf_0052ea60);
        mov_s(f21, f0);
    }
    // 0x005398bc
    charge(ctx, 18);
    mtc1(s0, f12);
    cvt_s_w(f12, f12);
    at = 0x40C90000;
    at = at | 0xFDA;
    mtc1(at, f0);
    mtc1(s1, f1);
    cvt_s_w(f1, f1);
    mul_s(f12, f12, f0);
    div_s(f12, f12, f1);
    jal(ctx, 0x5398E8u, gen::fn_cosf_0052e6d8);
    mov_s(f12, f22);
    mov_s(f1, f20);
    c_eq_s(f1, f1);
    sub_s(f21, f21, f0);
    if (!cond(ctx)) {
        // 0x00539904
        charge(ctx, 3);
        jal(ctx, 0x539904u, gen::fn_sqrtf_0052ea60);
        mov_s(f1, f0);
    }
    // 0x00539910
    charge(ctx, 12);
    at = 0x3F800000;
    mtc1(at, f0);
    sub_s(f20, f1, f0);
    sub_s(f0, f21, f20);
    add_s(f12, f21, f20);
    mul_s(f12, f12, f0);
    sqrt_s(f0, f12);
    c_eq_s(f0, f0);
    if (cond(ctx)) {
        sub_s(f0, f21, f0);
    } else {
        // 0x00539940
        charge(ctx, 3);
        jal(ctx, 0x539940u, gen::fn_sqrtf_0052ea60);
        sub_s(f0, f21, f0);
    }
    // 0x0053994c (the shared epilogue, written out on this path)
    charge(ctx, 26);
    lwc1(f21, sp, 0x30);
    at = 0x45800000;
    mtc1(at, f3);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    div_s(f0, f0, f20);
    lwc1(f20, sp, 0x28);
    ld(ra, sp, 0x20);
    lwc1(f22, sp, 0x38);
    neg_s(f1, f0);
    add_s(f2, f0, f0);
    mul_s(f1, f1, f0);
    mul_s(f2, f2, f3);
    mul_s(f1, f1, f3);
    cvt_w_s(f0, f2);
    mfc1(v0, f0);
    cvt_w_s(f0, f1);
    mfc1(v1, f0);
    sh(v0, s3, 0);
    ld(s3, sp, 0x18);
    sh(v1, s2, 0);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x005399B8 sub_5399B8 -- 128 bytes; leaf frame (no stack)
// Find the first big-endian 0x0080 halfword (an AHX frame sync) in a buffer, 2-byte steps: offset or -1.
// [ahx_FindSync]
void sub_5399B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x005399b8
    enter(ctx, 6);  // entry check point + this block's cycles
    t0 = 0x7FFF0000;
    a1 = addiu(a1, -1);
    t0 = t0 | 0xFFFF;
    t1 = 128;
    a3 = 0;
    if (i64(a1) > 0) {
        // 0x005399d0
        charge(ctx, 3);
        lhu(v0, a0, 0);
        if (v0 != t1) {
            a3 = addiu(a3, 2);
            for (;;) {
                // 0x005399e8
                charge(ctx, 3);
                v0 = slt(a3, a1);
                v1 = addu(a0, a3);
                if (v0 == 0) {
                    break;
                }
                // 0x005399f4
                charge(ctx, 6);
                lhu(v0, v1, 0);
                if (v0 == t1) {
                    goto L_00539a0c_5;
                }
                a3 = addiu(a3, 2);
                backedge(ctx);
            }
        } else {
            // 0x005399dc
            charge(ctx, 2);
            t0 = 0;
        }
    }
L_00539a14:
    charge(ctx, 4);
    v0 = 0x7FFF0000;
    v0 = v0 | 0xFFFF;
    if (t0 == v0) {
        sh(zero, a2, 0);
        // 0x00539a30
        charge(ctx, 2);
        v0 = si(-1);
        return;
    }
    // 0x00539a24
    charge(ctx, 3);
    sh(t0, a2, 0);
    v0 = 0;
    return;
L_00539a0c_5:
    charge(ctx, 2);
    v0 = slt(a3, t0);
    if (v0 != 0) t0 = a3;
    goto L_00539a14;
}

// 0x00539A38 sub_539A38 -- 164 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Is the buffer an ADX file start? 0x8000 magic, at least 0x8000 bytes, "(c)CRI" just before the data offset; also
// returns the data offset (header size + 4). [adx_IsHeader]
void sub_539A38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00539a38
    enter(ctx, 10);  // entry check point + this block's cycles
    t0 = a1;
    sp = addiu(sp, -0x20);
    v1 = slti(t0, 16);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    a3 = a0;
    sd(ra, sp, 0x10);
    s1 = a2;
    v0 = 0;
    if (v1 == 0) {
        // 0x00539a60
        charge(ctx, 7);
        lbu(v1, a3, 0);
        a1 = 0x8000;
        lbu(a0, a3, 1);
        v1 = sll(v1, 8);
        a0 = a0 | v1;
        ld(s0, sp, 0x0);
        if (a0 == a1) {
            // 0x00539a7c
            charge(ctx, 10);
            lbu(v1, a3, 2);
            a1 = 32767;
            lbu(a0, a3, 3);
            a1 = slt(a1, t0);
            v1 = sll(v1, 8);
            v1 = v1 | a0;
            a0 = addiu(v1, -2);
            s0 = addiu(v1, 4);
            a0 = addu(a3, a0);
            if (a1 != 0) {
                // 0x00539aa4
                charge(ctx, 6);
                a1 = 0x7C0000;
                a2 = 6;
                a1 = addiu(a1, 6712);  // "(c)CRI"
                jal(ctx, 0x539AACu, gen::fn_memcmp_005211b8);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x00539abc
                    charge(ctx, 2);
                    if (s1 != 0) {
                        sh(s0, s1, 0);
                    }
                    // 0x00539ac4
                    charge(ctx, 1);
                    v0 = 1;
                }
            }
            goto L_00539ac8;
        }
        // 0x00539acc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00539ac8:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00539acc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00539AE0 sub_539AE0 -- 256 bytes; leaf frame (no stack)
// Decode an ADX main header: data offset, encoding, block size, bits per sample, channels, sample rate, total
// samples, samples per block (8 * block size - 16) / bits). [adx_DecodeHeader]
// Arguments: $a0 header, $a1 size, $a2 data offset (u16), $a3 encoding, $t0 bits, $t1 block size, $t2 channels (u8
// each), $t3 rate, stack: samples, samples per block. 0, -1 (shorter than 16 bytes), -2 (no 0x8000).
void sub_539AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, sp{ctx, 29};
    // 0x00539ae0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = slti(a1, 16);
    t4 = a0;
    lw(t5, sp, 0x8);
    v0 = si(-1);
    if (a1 == 0) {
        // 0x00539af4
        charge(ctx, 7);
        lbu(v1, t4, 0);
        a1 = 0x8000;
        lbu(a0, t4, 1);
        v1 = sll(v1, 8);
        a0 = a0 | v1;
        v0 = si(-2);
        if (a0 == a1) {
            // 0x00539b10
            charge(ctx, 40);
            lbu(v1, t4, adx::kHeaderSize);
            lbu(v0, t4, 3);
            v1 = sll(v1, 8);
            v0 = v0 | v1;
            v0 = addiu(v0, 4);
            sh(v0, a2, 0);
            lbu(v1, t4, adx::kEncoding);
            sb(v1, a3, 0);
            lbu(v0, t4, adx::kBlockSize);
            sb(v0, t1, 0);
            lbu(v1, t4, adx::kBits);
            sb(v1, t0, 0);
            lbu(a0, t4, adx::kChannels);
            sb(a0, t2, 0);
            lbu(v0, t4, 8);
            lbu(v1, t4, 10);
            lbu(a0, t4, 9);
            v0 = sll(v0, 24);
            lbu(a1, t4, 11);
            v1 = sll(v1, 8);
            a0 = sll(a0, 16);
            v1 = v1 | a0;
            v0 = v0 | a1;
            v0 = v0 | v1;
            sw(v0, t3, 0);
            lbu(v1, t4, 13);
            lbu(v0, t4, 12);
            lbu(a0, t4, 14);
            v1 = sll(v1, 16);
            lbu(a1, t4, 15);
            v0 = sll(v0, 24);
            a0 = sll(a0, 8);
            a0 = a0 | v1;
            lw(v1, sp, 0x0);
            v0 = v0 | a1;
            v0 = v0 | a0;
            sw(v0, v1, 0);
            lb(t0, t0, 0);
            if (t0 != 0) {
                lb(v0, t1, 0);
                // 0x00539bb8
                charge(ctx, 2);
                if (t0 == 0) {
                    brk(ctx, 0x539BBCu, 0x7u);
                }
                // 0x00539bc0
                charge(ctx, 5);
                v0 = sll(v0, 3);
                v0 = addiu(v0, -16);
                div(v0, t0);
                mflo(v0);
                sw(v0, t5, 0);
            } else {
                // 0x00539bb0
                charge(ctx, 2);
                sw(zero, t5, 0);
            }
            // 0x00539bd4
            charge(ctx, 1);
            v0 = 0;
        }
    }
    // 0x00539bd8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00539BE0 sub_539BE0 -- 128 bytes; leaf frame (no stack)
// The high-pass cutoff of an ADX header (u16 BE at +16; header at least 18 bytes). [adx_GetCutoff]
void sub_539BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00539be0
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = slti(a1, 18);
    a3 = a0;
    v0 = si(-1);
    if (a1 == 0) {
        // 0x00539bf0
        charge(ctx, 9);
        lhu(v1, a3, 0);
        a1 = 0x8000;
        t0 = si(-256);
        a0 = sll(v1, 8);
        v1 = srl(v1, 8);
        v1 = v1 | a0;
        v1 = v1 & 0xFFFF;
        v0 = si(-2);
        if (v1 == a1) {
            // 0x00539c14
            charge(ctx, 10);
            lhu(a0, a3, adx::kHeaderSize);
            lbu(v1, a3, 3);
            a0 = sll(a0, 8);
            a0 = a0 & t0;
            v1 = v1 | a0;
            v1 = sll(v1, 16);
            v1 = sra(v1, 16);
            v1 = slti(v1, 14);
            v0 = si(-1);
            if (v1 == 0) {
                // 0x00539c3c
                charge(ctx, 7);
                lhu(a0, a3, adx::kCutoff);
                v0 = 0;
                v1 = sll(a0, 8);
                a0 = srl(a0, 8);
                v1 = v1 & t0;
                a0 = a0 | v1;
                sh(a0, a2, 0);
            }
        }
    }
    // 0x00539c58 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00539C60 sub_539C60 -- 120 bytes; leaf frame (no stack)
// The version and flags bytes of an ADX header (+18 / +19). [adx_GetVersion]
void sub_539C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00539c60
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = slti(a1, 20);
    t0 = a0;
    v0 = si(-1);
    if (a1 == 0) {
        // 0x00539c70
        charge(ctx, 8);
        lhu(v1, t0, 0);
        a1 = 0x8000;
        a0 = sll(v1, 8);
        v1 = srl(v1, 8);
        v1 = v1 | a0;
        v1 = v1 & 0xFFFF;
        v0 = si(-2);
        if (v1 == a1) {
            // 0x00539c90
            charge(ctx, 11);
            lhu(v1, t0, adx::kHeaderSize);
            a1 = si(-256);
            lbu(a0, t0, 3);
            v1 = sll(v1, 8);
            v1 = v1 & a1;
            a0 = a0 | v1;
            a0 = sll(a0, 16);
            a0 = sra(a0, 16);
            a0 = slti(a0, 16);
            v0 = si(-1);
            if (a0 == 0) {
                // 0x00539cbc
                charge(ctx, 5);
                lbu(a0, t0, adx::kVersion);
                v0 = 0;
                sb(a0, a2, 0);
                lbu(v1, t0, adx::kFlags);
                sb(v1, a3, 0);
            }
        }
    }
    // 0x00539cd0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00539CD8 sub_539CD8 -- 308 bytes; frame 0x40: s2 sp+0x20, s3 sp+0x28, s0 sp+0x10, s1 sp+0x18, ra sp+0x30
// The two channels' initial histories of a version-4 ADX header (+24 ... +30; zeros before version 4).
// [adx_GetHistory]
void sub_539CD8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00539cd8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s3, sp, 0x28);
    s3 = a3;
    a2 = sp;
    a3 = addiu(sp, 0x1);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x30);
    s1 = a1;
    jal(ctx, 0x539D04u, gen::fn_sub_539C60_00539c60);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = si(-1);
    if (!cc) {
        // 0x00539d14
        charge(ctx, 4);
        lbu(v0, sp, 0x0);
        v0 = sltiu(v0, 4);
        if (v0 != 0) {
            sh(zero, s3, 2);
            // 0x00539de0
            charge(ctx, 3);
            sh(zero, s2, 2);
            sh(zero, s3, 0);
            sh(zero, s2, 0);
        L_00539dec:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00539d24
            charge(ctx, 3);
            v1 = slti(s1, 32);
            v0 = si(-1);
            if (v1 == 0) {
                // 0x00539d30
                charge(ctx, 9);
                lhu(v1, s0, 0);
                a1 = 0x8000;
                a2 = si(-256);
                a0 = sll(v1, 8);
                v1 = srl(v1, 8);
                v1 = v1 | a0;
                v1 = v1 & 0xFFFF;
                v0 = si(-2);
                if (v1 == a1) {
                    // 0x00539d54
                    charge(ctx, 10);
                    lhu(a0, s0, 2);
                    lbu(v1, s0, 3);
                    a0 = sll(a0, 8);
                    a0 = a0 & a2;
                    v1 = v1 | a0;
                    v1 = sll(v1, 16);
                    v1 = sra(v1, 16);
                    v1 = slti(v1, 28);
                    v0 = si(-1);
                    if (v1 == 0) {
                        // 0x00539d7c
                        charge(ctx, 25);
                        lhu(v0, s0, 24);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v1 = v1 & a2;
                        v0 = v0 | v1;
                        sh(v0, s2, 0);
                        lhu(v1, s0, 26);
                        v0 = sll(v1, 8);
                        v1 = srl(v1, 8);
                        v0 = v0 & a2;
                        v1 = v1 | v0;
                        sh(v1, s3, 0);
                        lhu(v0, s0, 28);
                        v1 = sll(v0, 8);
                        v0 = srl(v0, 8);
                        v1 = v1 & a2;
                        v0 = v0 | v1;
                        sh(v0, s2, 2);
                        lhu(v1, s0, 30);
                        v0 = sll(v1, 8);
                        v1 = srl(v1, 8);
                        v0 = v0 & a2;
                        v1 = v1 | v0;
                        sh(v1, s3, 2);
                        goto L_00539dec;
                    }
                }
            }
        }
    }
    // 0x00539df0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00539E10 sub_539E10 -- 200 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, ra sp+0x48
// The loop of an ADX header: the loop flag (0 unless the record says 1) and the loop start / end samples less the
// alignment samples modulo 2048. [adx_GetLoopInfo]
void sub_539E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00539e10
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    s0 = a2;
    sd(s1, sp, 0x38);
    s1 = t0;
    sd(s2, sp, 0x40);
    s2 = a3;
    v0 = addiu(sp, 0x14);
    t0 = addiu(sp, 0x12);
    a3 = addiu(sp, 0x10);
    a2 = addiu(sp, 0x18);
    t1 = addiu(sp, 0x1C);
    t2 = addiu(sp, 0x20);
    t3 = addiu(sp, 0x24);
    sd(ra, sp, 0x48);
    link(ctx, 0x539E4Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn_sub_539ED8_00539ed8);
    lh(a0, sp, 0x10);
    v1 = 1;
    v0 = 0;
    lhu(a1, sp, 0x10);
    if (a0 != v1) {
        // 0x00539e68
        charge(ctx, 2);
        sh(zero, sp, 0x10);
        a1 = 0;
    }
    // 0x00539e70
    charge(ctx, 2);
    sh(a1, s0, 0);
    if (a1 == 0) {
        // 0x00539eb8
        charge(ctx, 2);
        sw(zero, s1, 0);
        sw(zero, s2, 0);
    } else {
        // 0x00539e78
        charge(ctx, 15);
        lw(a1, sp, 0x18);
        lw(a2, sp, 0x1C);
        a0 = slti(a1, 0);
        t0 = addiu(a1, 2047);
        v1 = a1;
        lw(a3, sp, 0x24);
        if (a0 != 0) v1 = t0;
        v1 = sra(v1, 11);
        a0 = sll(v1, 11);
        v1 = subu(a1, a0);
        a3 = subu(a3, v1);
        a2 = subu(a2, v1);
        sw(a2, s2, 0);
        sw(a3, s1, 0);
    }
    // 0x00539ec0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00539ED8 sub_539ED8 -- 608 bytes; frame 0x60: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, s7 sp+0x48, ra sp+0x50
// Decode an ADX loop record (version 3 at +20, version 4 at +32): alignment samples, loop flag, start / end sample,
// start / end byte. [adx_DecodeLoop]
// Arguments: $a0 header, $a1 its size, $a2 alignment samples (s32), $a3 loop count (u16), $t0 loop flag (u16), $t1 /
// $t2 start sample / byte, $t3 end sample, stack: end byte. 0, -1 (too short) or -2 (bad magic / no loop).
void sub_539ED8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00539ed8
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s2, sp, 0x20);
    s2 = a3;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(s4, sp, 0x30);
    s4 = t1;
    sd(s5, sp, 0x38);
    s5 = t2;
    sd(s6, sp, 0x40);
    s6 = t0;
    sd(s7, sp, 0x48);
    s7 = t3;
    sd(ra, sp, 0x50);
    a3 = addiu(sp, 0x1);
    sh(zero, s2, 0);
    a2 = sp;
    jal(ctx, 0x539F28u, gen::fn_sub_539C60_00539c60);
    if (v0 != 0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x00539f38
        charge(ctx, 8);
        lbu(v1, sp, 0x0);
        a2 = 48;
        a0 = 60;
        a3 = v1 ^ 0x4;
        if (a3 == 0) a2 = a0;
        v1 = slt(s1, a2);
        if (v1 != 0) {
            v0 = si(-1);
        } else {
            // 0x00539f58
            charge(ctx, 8);
            lhu(v1, s0, 0);
            a1 = 0x8000;
            a0 = sll(v1, 8);
            v1 = srl(v1, 8);
            v1 = v1 | a0;
            v1 = v1 & 0xFFFF;
            t6 = si(-256);
            if (v1 == a1) {
                // 0x00539f78
                charge(ctx, 11);
                lhu(v1, s0, 2);
                a1 = addiu(a2, -4);
                lbu(a0, s0, 3);
                v1 = sll(v1, 8);
                v1 = v1 & t6;
                a0 = a0 | v1;
                a0 = sll(a0, 16);
                a0 = sra(a0, 16);
                a0 = slt(a0, a1);
                v1 = 32;
                if (a0 == 0) {
                    // 0x00539fb0
                    charge(ctx, 24);
                    t5 = 20;
                    if (a3 == 0) t5 = v1;
                    t0 = 1;
                    a2 = addu(s0, t5);
                    t5 = addiu(t5, 2);
                    a3 = addu(s0, t5);
                    t5 = addiu(t5, 2);
                    lhu(a1, a2, 0);
                    lhu(a0, a3, 0);
                    lbu(v1, a2, 1);
                    a1 = sll(a1, 8);
                    lbu(a2, a3, 1);
                    a0 = sll(a0, 8);
                    a0 = a0 & t6;
                    a1 = a1 & t6;
                    a2 = a2 | a0;
                    v1 = v1 | a1;
                    v1 = sll(v1, 16);
                    a0 = sll(a2, 16);
                    v1 = sra(v1, 16);
                    a0 = sra(a0, 16);
                    sw(v1, s3, 0);
                    sh(a2, s2, 0);
                    if (a0 != t0) {
                        goto L_0053a010;
                    }
                    // 0x0053a018
                    charge(ctx, 61);
                    t5 = addiu(t5, 2);
                    t1 = 0xFF0000;
                    t2 = addu(s0, t5);
                    t5 = addiu(t5, 2);
                    v1 = addu(s0, t5);
                    t5 = addiu(t5, 4);
                    lw(a1, v1, 0);
                    t3 = addu(s0, t5);
                    t5 = addiu(t5, 4);
                    lhu(a3, t2, 0);
                    a2 = sra(a1, 8);
                    a0 = sll(a1, 8);
                    a2 = a2 & 0xFF00;
                    v1 = srl(a1, 24);
                    a0 = a0 & t1;
                    a1 = sll(a1, 24);
                    a0 = a0 | a2;
                    v1 = v1 | a1;
                    v1 = v1 | a0;
                    t4 = addu(s0, t5);
                    sw(v1, s4, 0);
                    t5 = addu(t5, s0);
                    lbu(t0, t2, 1);
                    a3 = sll(a3, 8);
                    lw(a1, t3, 0);
                    a3 = a3 & t6;
                    t0 = t0 | a3;
                    a2 = sra(a1, 8);
                    a0 = sll(a1, 8);
                    a2 = a2 & 0xFF00;
                    v1 = srl(a1, 24);
                    a0 = a0 & t1;
                    a1 = sll(a1, 24);
                    a0 = a0 | a2;
                    v1 = v1 | a1;
                    v1 = v1 | a0;
                    sh(t0, s6, 0);
                    sw(v1, s5, 0);
                    lw(a0, t4, 0);
                    a2 = sra(a0, 8);
                    a1 = sll(a0, 8);
                    a2 = a2 & 0xFF00;
                    v1 = srl(a0, 24);
                    a1 = a1 & t1;
                    a0 = sll(a0, 24);
                    a1 = a1 | a2;
                    v1 = v1 | a0;
                    v1 = v1 | a1;
                    sw(v1, s7, 0);
                    lw(a0, t5, 4);
                    a2 = sra(a0, 8);
                    a1 = sll(a0, 8);
                    v1 = srl(a0, 24);
                    a0 = sll(a0, 24);
                    a1 = a1 & t1;
                    a2 = a2 & 0xFF00;
                    v1 = v1 | a0;
                    lw(a0, sp, 0x60);
                    a1 = a1 | a2;
                    v1 = v1 | a1;
                    sw(v1, a0, 0);
                } else {
                    // 0x00539fa4
                    charge(ctx, 2);
                    v0 = si(-1);
                }
                goto L_0053a10c;
            }
        L_0053a010:
            charge(ctx, 2);
            v0 = si(-2);
        }
    L_0053a10c:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0053a110 (the shared epilogue, written out on this path)
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

// 0x0053A138 sub_53A138 -- 540 bytes; frame 0x50: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// Decode the "AINF" extension of an ADX header (after the loop record): size, 16-byte id, volume, pan pair.
// [adx_DecodeAinf]
void sub_53A138(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053a138
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s3, sp, 0x28);
    s3 = t1;
    sd(s4, sp, 0x30);
    s4 = a3;
    sd(s5, sp, 0x38);
    s5 = t0;
    sd(ra, sp, 0x40);
    a2 = sp;
    sw(zero, s2, 0);
    a3 = addiu(sp, 0x1);
    jal(ctx, 0x53A178u, gen::fn_sub_539C60_00539c60);
    if (v0 != 0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x0053a188
        charge(ctx, 8);
        lbu(v1, sp, 0x0);
        a2 = 60;
        a0 = 72;
        a3 = v1 ^ 0x4;
        if (a3 == 0) a2 = a0;
        v1 = slt(s1, a2);
        if (v1 != 0) {
            v0 = si(-1);
        } else {
            // 0x0053a1a8
            charge(ctx, 8);
            lhu(v1, s0, 0);
            a1 = 0x8000;
            a0 = sll(v1, 8);
            v1 = srl(v1, 8);
            v1 = v1 | a0;
            v1 = v1 & 0xFFFF;
            t2 = si(-256);
            if (v1 == a1) {
                // 0x0053a1c8
                charge(ctx, 11);
                lhu(v1, s0, 2);
                a1 = addiu(a2, -4);
                lbu(a0, s0, 3);
                v1 = sll(v1, 8);
                v1 = v1 & t2;
                a0 = a0 | v1;
                a0 = sll(a0, 16);
                a0 = sra(a0, 16);
                a0 = slt(a0, a1);
                v1 = 32;
                if (a0 == 0) {
                    // 0x0053a200
                    charge(ctx, 28);
                    t1 = 20;
                    if (a3 == 0) t1 = v1;
                    t0 = 0x41490000;
                    t1 = addiu(t1, 2);
                    t0 = t0 | 0x4E46;
                    a1 = addu(s0, t1);
                    t1 = addiu(t1, 2);
                    lhu(v1, a1, 0);
                    a2 = addiu(t1, 20);
                    lbu(a0, a1, 1);
                    v1 = sll(v1, 8);
                    v1 = v1 & t2;
                    a0 = a0 | v1;
                    a0 = sll(a0, 16);
                    if (a0 != 0) t1 = a2;
                    a1 = addu(s0, t1);
                    lbu(a2, a1, 1);
                    lbu(v1, a1, 0);
                    lbu(a0, a1, 2);
                    a2 = sll(a2, 16);
                    lbu(a3, a1, 3);
                    v1 = sll(v1, 24);
                    a0 = sll(a0, 8);
                    v1 = v1 | a3;
                    a0 = a0 | a2;
                    v1 = v1 | a0;
                    t1 = addiu(t1, 4);
                    if (v1 != t0) {
                        goto L_0053a270;
                    }
                    // 0x0053a278
                    charge(ctx, 46);
                    v1 = addu(s0, t1);
                    t1 = addiu(t1, 4);
                    lw(a1, v1, 0);
                    a3 = 0xFF0000;
                    t0 = addu(s0, t1);
                    t1 = addiu(t1, 16);
                    a2 = sra(a1, 8);
                    a0 = sll(a1, 8);
                    a0 = a0 & a3;
                    a2 = a2 & 0xFF00;
                    v1 = srl(a1, 24);
                    a1 = sll(a1, 24);
                    a0 = a0 | a2;
                    v1 = v1 | a1;
                    v1 = v1 | a0;
                    a1 = addu(s0, t1);
                    sw(v1, s2, 0);
                    t1 = addiu(t1, 4);
                    a2 = addu(s0, t1);
                    a3 = addu(t1, s0);
                    ldl(v1, t0, 7);
                    ldr(v1, t0, 0);
                    ldl(a0, t0, 15);
                    ldr(a0, t0, 8);
                    sdl(v1, s4, 7);
                    sdr(v1, s4, 0);
                    sdl(a0, s4, 15);
                    sdr(a0, s4, 8);
                    lhu(v1, a1, 0);
                    lbu(a0, a1, 1);
                    v1 = sll(v1, 8);
                    v1 = v1 & t2;
                    a0 = a0 | v1;
                    sh(a0, s5, 0);
                    lhu(v1, a2, 0);
                    lbu(a0, a2, 1);
                    v1 = sll(v1, 8);
                    v1 = v1 & t2;
                    a0 = a0 | v1;
                    sh(a0, s3, 0);
                    lhu(v1, a3, 2);
                    lbu(a0, a3, 3);
                    v1 = sll(v1, 8);
                    v1 = v1 & t2;
                    a0 = a0 | v1;
                    sh(a0, s3, 2);
                } else {
                    // 0x0053a1f4
                    charge(ctx, 2);
                    v0 = si(-1);
                }
                goto L_0053a330;
            }
        L_0053a270:
            charge(ctx, 2);
            v0 = si(-2);
        }
    L_0053a330:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0053a334 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0053A358 _get_peer_or_sock_name_3 -- 92 bytes; leaf frame (no stack)
// Is the buffer an AHX header (0x8001 magic)? returns the data offset (header size + 4). [ahx_DecodeHeader]
void _get_peer_or_sock_name_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0053a358
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = slti(a1, 16);
    a3 = a0;
    v0 = si(-1);
    if (a1 == 0) {
        // 0x0053a368
        charge(ctx, 8);
        lhu(v1, a3, 0);
        a1 = 0x8001;
        a0 = sll(v1, 8);
        v1 = srl(v1, 8);
        v1 = v1 | a0;
        v1 = v1 & 0xFFFF;
        v0 = si(-2);
        if (v1 == a1) {
            // 0x0053a388
            charge(ctx, 9);
            lhu(v1, a3, 2);
            a1 = si(-256);
            lbu(a0, a3, 3);
            v0 = 0;
            v1 = sll(v1, 8);
            v1 = v1 & a1;
            a0 = a0 | v1;
            a0 = addiu(a0, 4);
            sh(a0, a2, 0);
        }
    }
    // 0x0053a3ac (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0053A3B8 sub_53A3B8 -- 84 bytes; leaf frame (no stack)
// (position + header + block size + 57 (a0 != 0) or 33) rounded down to whole blocks, less the header.
void sub_53A3B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0053a3b8
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = addu(a2, a3);
    v0 = v1;
    if (a0 != 0) {
        // 0x0053a3e8
        charge(ctx, 3);
        v0 = addu(a1, v0);
        if (a3 == 0) {
            brk(ctx, 0x53A3F0u, 0x7u);
        }
        // 0x0053a3f4
        charge(ctx, 6);
        v0 = addiu(v0, 57);
        divu(v0, a3);
        mflo(v0);
        mult(v0, v0, a3);
        v0 = subu(v0, a2);
        return;
    }
    // 0x0053a3c4
    charge(ctx, 3);
    v0 = addu(a1, v1);
    if (a3 == 0) {
        brk(ctx, 0x53A3CCu, 0x7u);
    }
    // 0x0053a3d0
    charge(ctx, 6);
    v0 = addiu(v0, 33);
    divu(v0, a3);
    mflo(v0);
    mult(v0, v0, a3);
    v0 = subu(v0, a2);
}

// 0x0053A410 sub_53A410 -- 476 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, fp sp+0x40
// Decode N mono ADX blocks (18 bytes: BE scale, 32 nibbles) to 16-bit PCM; the scale is XORed with the running key
// (key = (key * mult + add) & 0x7FFF per block); stops before an 0x8000 end block. [adxpd_DecodeMono]
// Arguments: $a0 blocks, $a1 count, $a2 PCM out, $a3 {hist1, hist2}, $t0 / $t1 coef1 / coef2, $t2 the key, $t3 its
// multiplier, the 9th (stack) its increment. Per block: the scale (+1) from the XORed BE word, then 16 bytes, two
// samples each (high nibble by an arithmetic shift, low nibble through the table 0x7C1A40); each sample ((coef1 *
// hist1 [LO1] + coef2 * hist2) >> 12) + nibble * scale, clamped to 16 bits.
void sub_53A410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // 0x0053a410
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t0 = sll(t0, 16);
    sd(s0, sp, 0x0);
    t1 = sll(t1, 16);
    sd(s1, sp, 0x8);
    s1 = sra(t0, 16);
    sd(s2, sp, 0x10);
    s2 = t2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s5, sp, 0x28);
    t3 = sll(t3, 16);
    sd(s6, sp, 0x30);
    s6 = sra(t3, 16);
    sd(s7, sp, 0x38);
    s0 = sra(t1, 16);
    sd(fp, sp, 0x40);
    t5 = a0;
    lh(s5, sp, 0x50);
    t2 = 0;
    lh(a1, s4, 0);
    lh(t6, s4, 2);
    if (i64(s3) > 0) {
        // 0x0053a474
        charge(ctx, 3);
        fp = si(-0x100);
        s7 = 0x7C0000;
        lhu(v1, t5, 0);
        for (;;) {
            // 0x0053a480
            charge(ctx, 9);
            lbu(a0, t5, 1);
            v1 = sll(v1, 8);
            v1 = v1 & fp;
            a0 = a0 | v1;
            a0 = sll(a0, 16);
            a0 = sra(a0, 16);
            v1 = a0 & 0x8000;
            v0 = t2;
            if (v1 != 0) {
                break;
            }
            // 0x0053a4a4
            charge(ctx, 15);
            lhu(v0, s2, 0);
            t5 = addiu(t5, 2);
            t1 = 0x8000;
            t0 = 0xFFFF;
            mult(a3, v0, s6);
            v0 = a0 ^ v0;
            v0 = v0 & 0x1FFF;
            t9 = 32767;
            t7 = addiu(v0, 1);
            t3 = addiu(s7, 6720);
            v1 = addu(a3, s5);
            a3 = 30;
            v1 = v1 & 0x7FFF;
            sh(v1, s2, 0);
            for (;;) {
                // 0x0053a4e0
                charge(ctx, 22);
                lbu(v1, t5, 0);
                t5 = addiu(t5, 1);
                mult(v0, s0, t6);
                t6 = a1;
                mult1(a0, s1, a1);
                v1 = sll(v1, 24);
                a1 = sra(v1, 28);
                v1 = sra(v1, 24);
                mult(a1, a1, t7);
                mult(t8, s0, t6);
                a0 = addu(a0, v0);
                v0 = v1 & 0xF;
                a0 = sra(a0, 12);
                v0 = sll(v0, 2);
                a0 = addu(a0, a1);
                t4 = addu(v0, t3);
                v0 = addu(a0, t1);
                v1 = slti(a0, -32768);
                v0 = sltu(t0, v0);
                a1 = slt(t9, a0);
                v1 = v1 ^ 0x0;
                if (v0 != 0) {
                    // 0x0053a538
                    charge(ctx, 3);
                    if (a1 != 0) a0 = t9;
                    v0 = si(-32768);
                    if (v1 != 0) a0 = v0;
                }
                // 0x0053a544
                charge(ctx, 16);
                a1 = a0;
                lw(v1, t4, 0);
                mult(v0, s1, a1);
                sh(a1, a2, 0);
                mult(a0, v1, t7);
                t6 = a1;
                a2 = addiu(a2, 2);
                v0 = addu(v0, t8);
                v0 = sra(v0, 12);
                a0 = addu(v0, a0);
                v1 = addu(a0, t1);
                v0 = slti(a0, -32768);
                v1 = sltu(t0, v1);
                a1 = slt(t9, a0);
                t4 = v0 ^ 0x0;
                if (v1 != 0) {
                    // 0x0053a584
                    charge(ctx, 3);
                    if (a1 != 0) a0 = t9;
                    v0 = si(-32768);
                    if (t4 != 0) a0 = v0;
                }
                // 0x0053a590
                charge(ctx, 5);
                a1 = a0;
                a3 = addiu(a3, -2);
                sh(a1, a2, 0);
                a2 = addiu(a2, 2);
                if (i64(a3) < 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0053a5a4
            charge(ctx, 4);
            t2 = addiu(t2, 1);
            v0 = slt(t2, s3);
            if (v0 == 0) {
                goto L_0053a5b4;
            }
            lhu(v1, t5, 0);
            backedge(ctx);
        }
        // 0x0053a5c0 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(s7, sp, 0x38);
        ld(fp, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_0053a5b4:
    charge(ctx, 3);
    sh(t6, s4, 2);
    v0 = s3;
    sh(a1, s4, 0);
    // 0x0053a5c0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0053AD00 sub_53AD00 -- 1916 bytes, 3 chunks; frame 0x30: ra sp+0x20
// Decode N interleaved stereo ADX blocks (left, right, ...) to two PCM buffers; with 0x784948 non-zero both outputs
// get the downmix (L + R) * 7 / 10 (histories stay per channel); same key rule as the mono decoder; an end block
// returns early without writing the histories back (both decoders). [adxpd_DecodeStereo]
// Arguments: $a0 blocks, $a1 count (both channels), $a2 / $t0 left / right PCM, $a3 / $t1 their histories, $t2 / $t3
// coef1 / coef2, the stack slots the key, multiplier and increment. The body re-enters its frame at one of two chunks
// (0x53A5F0 downmix, 0x53A9B8 plain) after the entry block; both walk pairs of blocks (left at +0, right at +18).
void sub_53AD00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0053ad00
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = 0x780000;
    t2 = sll(t2, 16);
    t3 = sll(t3, 16);
    lw(v1, v0, 18760);  // 0x784948
    sp = addiu(sp, -0x30);
    t4 = sra(t2, 16);
    t5 = sra(t3, 16);
    sd(ra, sp, 0x20);
    t2 = t4;
    t3 = t5;
    lw(t6, sp, 0x30);
    lh(t7, sp, 0x38);
    lh(v0, sp, 0x40);
    if (v1 == 0) {
        // 0x0053ad38
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        sw(v0, sp, 0x40);
        sw(t7, sp, 0x38);
        sp = addiu(sp, 0x30);
        backedge(ctx);
        // 0x0053a9b8
        charge(ctx, 34);
        v0 = srl(a1, 31);
        sp = addiu(sp, -0x70);
        v0 = addu(a1, v0);
        lh(v1, sp, 0x78);
        v0 = sra(v0, 1);
        sd(s2, sp, 0x30);
        sw(v0, sp, 0x18);
        t7 = a0;
        lh(v0, sp, 0x80);
        t2 = sll(t2, 16);
        sd(s3, sp, 0x38);
        s3 = sra(t2, 16);
        sd(s0, sp, 0x20);
        t3 = sll(t3, 16);
        sd(s1, sp, 0x28);
        t9 = a2;
        sd(s4, sp, 0x40);
        s2 = sra(t3, 16);
        sd(s5, sp, 0x48);
        sd(s6, sp, 0x50);
        sd(s7, sp, 0x58);
        sd(fp, sp, 0x60);
        sw(a1, sp, 0x0);
        sw(a3, sp, 0x4);
        sw(t1, sp, 0x8);
        sw(v0, sp, 0x10);
        sw(zero, sp, 0x14);
        sw(v1, sp, 0xC);
        lw(a0, sp, 0x18);
        lh(t5, a3, 0);
        lh(t2, a3, 2);
        lh(t6, t1, 0);
        lh(s0, t1, 2);
        if (i64(a0) > 0) {
            for (;;) {
                // 0x0053aa40
                charge(ctx, 13);
                lhu(v1, t7, 0);
                a2 = si(-256);
                lbu(a0, t7, 1);
                v1 = sll(v1, 8);
                lw(a1, sp, 0x14);
                v1 = v1 & a2;
                a0 = a0 | v1;
                v0 = sll(a1, 1);
                a0 = sll(a0, 16);
                a1 = sra(a0, 16);
                v1 = a1 & 0x8000;
                lw(a0, sp, 0x14);
                if (v1 == 0) {
                    // 0x0053aa74
                    charge(ctx, 24);
                    lw(v0, sp, 0x70);
                    lw(a2, sp, 0x10);
                    lhu(v1, v0, 0);
                    mtlo(a2);
                    lw(a2, sp, 0xC);
                    v0 = sll(a0, 1);
                    madd(a0, v1, a2);
                    v1 = a1 ^ v1;
                    v1 = v1 & 0x1FFF;
                    a1 = si(-256);
                    s7 = addiu(v1, 1);
                    lw(v1, sp, 0x70);
                    a2 = a0 & 0x7FFF;
                    sh(a2, v1, 0);
                    lhu(v1, t7, 18);
                    lbu(a0, t7, 19);
                    v1 = sll(v1, 8);
                    v1 = v1 & a1;
                    a0 = a0 | v1;
                    a0 = sll(a0, 16);
                    a1 = sra(a0, 16);
                    v1 = a1 & 0x8000;
                    cc = v1 != 0;  // the condition, before the delay slot changes it
                    lw(v1, sp, 0x10);
                    if (!cc) {
                        // 0x0053aad4
                        charge(ctx, 15);
                        t7 = addiu(t7, 2);
                        lw(a0, sp, 0x70);
                        s6 = 0x8000;
                        mtlo(v1);
                        lw(v1, sp, 0xC);
                        s5 = 0xFFFF;
                        t8 = 32767;
                        madd(v0, v1, a2);
                        v1 = a1 ^ a2;
                        v1 = v1 & 0x1FFF;
                        fp = 0x1E;
                        s4 = addiu(v1, 1);
                        v0 = v0 & 0x7FFF;
                        sh(v0, a0, 0);
                        for (;;) {
                            // 0x0053ab10
                            charge(ctx, 30);
                            lbu(v1, t7, 0);
                            mult(v0, s2, t2);
                            mult1(a0, s3, t5);
                            lbu(a2, t7, 18);
                            v1 = sll(v1, 24);
                            t2 = t5;
                            a1 = sra(v1, 28);
                            a2 = sll(a2, 24);
                            mult(a1, a1, s7);
                            t4 = sra(v1, 24);
                            a0 = addu(a0, v0);
                            v0 = t4 & 0xF;
                            v1 = sra(a2, 28);
                            a2 = sra(a2, 24);
                            a0 = sra(a0, 12);
                            mult(t4, v1, s4);
                            v1 = 0x7C0000;
                            a1 = addu(a0, a1);
                            v0 = sll(v0, 2);
                            v1 = addiu(v1, 6720);  // &0x7C1A40
                            t3 = addu(v0, v1);
                            v0 = addu(a1, s6);
                            v1 = slti(a1, -32768);
                            v0 = sltu(s5, v0);
                            mult(s1, s2, t2);
                            t7 = addiu(t7, 1);
                            a0 = slt(t8, a1);
                            v1 = v1 ^ 0x0;
                            t1 = a2 & 0xF;
                            if (v0 != 0) {
                                // 0x0053ab88
                                charge(ctx, 3);
                                if (a0 != 0) a1 = t8;
                                v0 = si(-32768);
                                if (v1 != 0) a1 = v0;
                            }
                            // 0x0053ab94
                            charge(ctx, 18);
                            mult(a0, s2, s0);
                            s0 = t6;
                            mult1(v0, s3, t6);
                            t5 = a1;
                            mult(v1, s3, t5);
                            mult(a3, s2, s0);
                            t2 = t5;
                            v0 = addu(v0, a0);
                            v0 = sra(v0, 12);
                            v1 = addu(v1, s1);
                            a1 = addu(v0, t4);
                            a2 = sra(v1, 12);
                            v1 = addu(a1, s6);
                            v0 = slti(a1, -32768);
                            v1 = sltu(s5, v1);
                            a0 = slt(t8, a1);
                            t4 = v0 ^ 0x0;
                            if (v1 != 0) {
                                // 0x0053abdc
                                charge(ctx, 3);
                                if (a0 != 0) a1 = t8;
                                v0 = si(-32768);
                                if (t4 != 0) a1 = v0;
                            }
                            // 0x0053abe8
                            charge(ctx, 24);
                            lw(t4, t3, 0);
                            t6 = a1;
                            mult(v0, s3, t6);
                            a1 = 0x7C0000;
                            mult(a0, t4, s7);
                            a1 = addiu(a1, 6720);  // &0x7C1A40
                            v1 = sll(t1, 2);
                            sh(t5, t9, 0);
                            v1 = addu(v1, a1);
                            s0 = t6;
                            v0 = addu(v0, a3);
                            sh(t6, t0, 0);
                            a1 = addu(a2, a0);
                            lw(a2, v1, 0);
                            t4 = sra(v0, 12);
                            v0 = addu(a1, s6);
                            v1 = slti(a1, -32768);
                            v0 = sltu(s5, v0);
                            t9 = addiu(t9, 2);
                            t0 = addiu(t0, 2);
                            mult(a2, a2, s4);
                            a0 = slt(t8, a1);
                            v1 = v1 ^ 0x0;
                            if (v0 != 0) {
                                // 0x0053ac48
                                charge(ctx, 3);
                                if (a0 != 0) a1 = t8;
                                v0 = si(-32768);
                                if (v1 != 0) a1 = v0;
                            }
                            // 0x0053ac54
                            charge(ctx, 8);
                            t5 = a1;
                            a1 = addu(t4, a2);
                            v0 = addu(a1, s6);
                            v1 = slti(a1, -32768);
                            v0 = sltu(s5, v0);
                            a0 = slt(t8, a1);
                            v1 = v1 ^ 0x0;
                            if (v0 != 0) {
                                // 0x0053ac74
                                charge(ctx, 3);
                                if (a0 != 0) a1 = t8;
                                v0 = si(-32768);
                                if (v1 != 0) a1 = v0;
                            }
                            // 0x0053ac80
                            charge(ctx, 7);
                            t6 = a1;
                            fp = addiu(fp, -0x2);
                            sh(t5, t9, 0);
                            t9 = addiu(t9, 2);
                            sh(t6, t0, 0);
                            t0 = addiu(t0, 2);
                            if (i64(fp) < 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0053ac9c
                        charge(ctx, 7);
                        lw(a2, sp, 0x14);
                        t7 = addiu(t7, 18);
                        lw(v1, sp, 0x18);
                        a2 = addiu(a2, 1);
                        v0 = slt(a2, v1);
                        sw(a2, sp, 0x14);
                        if (v0 == 0) {
                            goto L_0053acb8;
                        }
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            // 0x0053acd4 (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(s0, sp, 0x20);
            ld(s1, sp, 0x28);
            ld(s2, sp, 0x30);
            ld(s3, sp, 0x38);
            ld(s4, sp, 0x40);
            ld(s5, sp, 0x48);
            ld(s6, sp, 0x50);
            ld(s7, sp, 0x58);
            ld(fp, sp, 0x60);
            sp = addiu(sp, 0x70);
            return;
        }
    L_0053acb8:
        charge(ctx, 7);
        lw(a0, sp, 0x4);
        sh(t2, a0, 2);
        lw(v0, sp, 0x0);
        sh(t5, a0, 0);
        lw(a1, sp, 0x8);
        sh(s0, a1, 2);
        sh(t6, a1, 0);
        // 0x0053acd4 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(s0, sp, 0x20);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(s5, sp, 0x48);
        ld(s6, sp, 0x50);
        ld(s7, sp, 0x58);
        ld(fp, sp, 0x60);
        sp = addiu(sp, 0x70);
        return;
    }
    // 0x0053ad50
    charge(ctx, 8);
    ld(ra, sp, 0x20);
    t2 = t4;
    t3 = t5;
    sw(v0, sp, 0x40);
    sw(t6, sp, 0x30);
    sw(t7, sp, 0x38);
    sp = addiu(sp, 0x30);
    backedge(ctx);
    // 0x0053a5f0
    charge(ctx, 35);
    v0 = srl(a1, 31);
    sp = addiu(sp, -0x70);
    v0 = addu(a1, v0);
    sw(t1, sp, 0x8);
    v0 = sra(v0, 1);
    lh(v1, sp, 0x78);
    sw(v0, sp, 0x14);
    t1 = a2;
    lh(v0, sp, 0x80);
    t2 = sll(t2, 16);
    sd(s2, sp, 0x30);
    t3 = sll(t3, 16);
    sd(s3, sp, 0x38);
    s3 = sra(t2, 16);
    sd(s7, sp, 0x58);
    s7 = 0;
    sw(a1, sp, 0x0);
    s2 = sra(t3, 16);
    sd(s0, sp, 0x20);
    t7 = a0;
    sd(s1, sp, 0x28);
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(fp, sp, 0x60);
    sw(a3, sp, 0x4);
    sw(v0, sp, 0x10);
    sw(v1, sp, 0xC);
    lw(a1, sp, 0x8);
    lw(a2, sp, 0x14);
    lh(t8, a3, 0);
    lh(t4, a3, 2);
    lh(t9, a1, 0);
    lh(s1, a1, 2);
    if (i64(a2) > 0) {
        // 0x0053a67c
        charge(ctx, 1);
        for (;;) {
            // 0x0053a680
            charge(ctx, 11);
            lhu(v1, t7, 0);
            a1 = si(-256);
            lbu(a0, t7, 1);
            v1 = sll(v1, 8);
            v1 = v1 & a1;
            a0 = a0 | v1;
            a0 = sll(a0, 16);
            a1 = sra(a0, 16);
            v1 = a1 & 0x8000;
            v0 = sll(s7, 1);
            if (v1 == 0) {
                // 0x0053a6ac
                charge(ctx, 23);
                lw(a2, sp, 0x70);
                lhu(v1, a2, 0);
                lw(a2, sp, 0x10);
                mtlo(a2);
                lw(a2, sp, 0xC);
                madd(a0, v1, a2);
                v1 = a1 ^ v1;
                v1 = v1 & 0x1FFF;
                a1 = si(-256);
                s5 = addiu(v1, 1);
                lw(v1, sp, 0x70);
                a2 = a0 & 0x7FFF;
                sh(a2, v1, 0);
                lhu(v1, t7, 18);
                lbu(a0, t7, 19);
                v1 = sll(v1, 8);
                v1 = v1 & a1;
                a0 = a0 | v1;
                a0 = sll(a0, 16);
                a1 = sra(a0, 16);
                v1 = a1 & 0x8000;
                cc = v1 != 0;  // the condition, before the delay slot changes it
                lw(v1, sp, 0x10);
                if (!cc) {
                    // 0x0053a708
                    charge(ctx, 18);
                    a0 = 0x7C0000;
                    fp = addiu(a0, 0x1A40);  // &0x7C1A40
                    t7 = addiu(t7, 2);
                    mtlo(v1);
                    lw(v1, sp, 0xC);
                    s0 = 0x8000;
                    t3 = 0xFFFF;
                    madd(v0, v1, a2);
                    v1 = a1 ^ a2;
                    lw(a1, sp, 0x70);
                    v1 = v1 & 0x1FFF;
                    s4 = addiu(v1, 1);
                    t5 = 32767;
                    t2 = 10;
                    s6 = 30;
                    v0 = v0 & 0x7FFF;
                    sh(v0, a1, 0);
                    for (;;) {
                        // 0x0053a750
                        charge(ctx, 18);
                        lbu(v0, t7, 0);
                        mult(a2, s2, t4);
                        mult1(v1, s3, t8);
                        lbu(a0, t7, 18);
                        v0 = sll(v0, 24);
                        t7 = addiu(t7, 1);
                        a1 = sra(v0, 28);
                        t6 = sra(v0, 24);
                        mult(a1, a1, s5);
                        a0 = sll(a0, 24);
                        v1 = addu(v1, a2);
                        t4 = sra(a0, 28);
                        v1 = sra(v1, 12);
                        a2 = addu(v1, a1);
                        v0 = addu(a2, s0);
                        v0 = sltu(t3, v0);
                        a3 = sra(a0, 24);
                        if (v0 != 0) {
                            // 0x0053a798
                            charge(ctx, 6);
                            v0 = slti(a2, -32768);
                            v1 = slt(t5, a2);
                            if (v1 != 0) a2 = t5;
                            v1 = si(-32768);
                            v0 = v0 ^ 0x0;
                            if (v0 != 0) a2 = v1;
                        }
                        // 0x0053a7b0
                        charge(ctx, 12);
                        mult(v0, s2, s1);
                        mult1(v1, s3, t9);
                        mult(a0, t4, s4);
                        t4 = t8;
                        t8 = a2;
                        v1 = addu(v1, v0);
                        v1 = sra(v1, 12);
                        a2 = addu(v1, a0);
                        v0 = addu(a2, s0);
                        v0 = sltu(t3, v0);
                        s1 = t9;
                        if (v0 != 0) {
                            // 0x0053a7e0
                            charge(ctx, 6);
                            v0 = slti(a2, -32768);
                            v1 = slt(t5, a2);
                            if (v1 != 0) a2 = t5;
                            v1 = si(-32768);
                            v0 = v0 ^ 0x0;
                            if (v0 != 0) a2 = v1;
                        }
                        // 0x0053a7f8
                        charge(ctx, 4);
                        t9 = a2;
                        v1 = addu(t8, t9);
                        if (t2 == 0) {
                            brk(ctx, 0x53A804u, 0x7u);
                        }
                        // 0x0053a808
                        charge(ctx, 9);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        div(v0, t2);
                        mflo(v0);
                        a2 = v0;
                        v1 = addu(a2, s0);
                        v1 = sltu(t3, v1);
                        v0 = t6 & 0xF;
                        if (v1 != 0) {
                            // 0x0053a82c
                            charge(ctx, 7);
                            v0 = slti(a2, -32768);
                            v1 = slt(t5, a2);
                            if (v1 != 0) a2 = t5;
                            v1 = si(-32768);
                            v0 = v0 ^ 0x0;
                            if (v0 != 0) a2 = v1;
                            v0 = t6 & 0xF;
                        }
                        // 0x0053a848
                        charge(ctx, 20);
                        mult(a1, s2, t4);
                        mult1(a0, s3, t8);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, fp);
                        sh(a2, t0, 0);
                        lw(t6, v0, 0);
                        v1 = a3 & 0xF;
                        sh(a2, t1, 0);
                        t1 = addiu(t1, 2);
                        a0 = addu(a0, a1);
                        mult(a1, t6, s5);
                        a0 = sra(a0, 12);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, fp);
                        t0 = addiu(t0, 2);
                        a2 = addu(a0, a1);
                        v0 = addu(a2, s0);
                        v0 = sltu(t3, v0);
                        lw(a3, v1, 0);
                        if (v0 != 0) {
                            // 0x0053a898
                            charge(ctx, 6);
                            v0 = slti(a2, -32768);
                            v1 = slt(t5, a2);
                            if (v1 != 0) a2 = t5;
                            v1 = si(-32768);
                            v0 = v0 ^ 0x0;
                            if (v0 != 0) a2 = v1;
                        }
                        // 0x0053a8b0
                        charge(ctx, 12);
                        mult(v0, s2, s1);
                        mult1(v1, s3, t9);
                        mult(a0, a3, s4);
                        t4 = t8;
                        t8 = a2;
                        v1 = addu(v1, v0);
                        v1 = sra(v1, 12);
                        a2 = addu(v1, a0);
                        v0 = addu(a2, s0);
                        v0 = sltu(t3, v0);
                        s1 = t9;
                        if (v0 != 0) {
                            // 0x0053a8e0
                            charge(ctx, 6);
                            v0 = slti(a2, -32768);
                            v1 = slt(t5, a2);
                            if (v1 != 0) a2 = t5;
                            v1 = si(-32768);
                            v0 = v0 ^ 0x0;
                            if (v0 != 0) a2 = v1;
                        }
                        // 0x0053a8f8
                        charge(ctx, 4);
                        t9 = a2;
                        v1 = addu(t8, t9);
                        if (t2 == 0) {
                            brk(ctx, 0x53A904u, 0x7u);
                        }
                        // 0x0053a908
                        charge(ctx, 9);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        div(v0, t2);
                        mflo(v0);
                        a2 = v0;
                        v1 = addu(a2, s0);
                        v1 = sltu(t3, v1);
                        s6 = addiu(s6, -2);
                        if (v1 != 0) {
                            // 0x0053a92c
                            charge(ctx, 6);
                            v0 = slti(a2, -32768);
                            v1 = slt(t5, a2);
                            if (v1 != 0) a2 = t5;
                            v1 = si(-32768);
                            v0 = v0 ^ 0x0;
                            if (v0 != 0) a2 = v1;
                        }
                        // 0x0053a944
                        charge(ctx, 5);
                        sh(a2, t0, 0);
                        sh(a2, t1, 0);
                        t1 = addiu(t1, 2);
                        t0 = addiu(t0, 2);
                        if (i64(s6) < 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0053a958
                    charge(ctx, 5);
                    lw(v1, sp, 0x14);
                    s7 = addiu(s7, 1);
                    v0 = slt(s7, v1);
                    t7 = addiu(t7, 18);
                    if (v0 == 0) {
                        goto L_0053a96c;
                    }
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
        // 0x0053a988 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(s0, sp, 0x20);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(s5, sp, 0x48);
        ld(s6, sp, 0x50);
        ld(s7, sp, 0x58);
        ld(fp, sp, 0x60);
        sp = addiu(sp, 0x70);
        return;
    }
L_0053a96c:
    charge(ctx, 7);
    lw(a1, sp, 0x4);
    sh(t4, a1, 2);
    lw(v0, sp, 0x0);
    sh(t8, a1, 0);
    lw(a2, sp, 0x8);
    sh(s1, a2, 2);
    sh(t9, a2, 0);
    // 0x0053a988 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x0054CB78 sub_54CB78 -- 36 bytes; frame 0x10: ra sp+0x0
// Clear the 16 decoder objects (init). [ADXPD_Init]
void sub_54CB78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cb78
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x790000;
    sd(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 15232);  // &0x793B80
    a2 = 960;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0054CBA0 sub_54CBA0 -- 36 bytes; frame 0x10: ra sp+0x0
// Clear the 16 decoder objects (finish). [ADXPD_Finish]
void sub_54CBA0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cba0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x790000;
    sd(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 15232);  // &0x793B80
    a2 = 960;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0054CBC8 sub_54CBC8 -- 204 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Take a free decoder object: used = 1, id, state 0, coefficients for 500 Hz / 44100 Hz, histories 0. [ADXPD_Create]
void sub_54CBC8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cbc8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = 0x790000;
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    v1 = addiu(a0, 15232);  // &0x793B80
    sd(ra, sp, 0x10);
    lw(v0, v1, 0);  // 0x793B80
    s1 = 0;
    if (v0 != 0) {
        // 0x0054cbec
        charge(ctx, 1);
        s1 = addiu(s1, 1);
        for (;;) {
            // 0x0054cbf0
            charge(ctx, 3);
            v0 = slti(s1, 16);
            v1 = addiu(v1, 60);
            if (v0 != 0) {
                // 0x0054cbfc
                charge(ctx, 6);
                lw(v0, v1, 0);
                if (v0 != 0) {
                    s1 = addiu(s1, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0054cc14
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (s1 != v1) {
        // 0x0054cc20
        charge(ctx, 24);
        s0 = sll(s1, 4);
        v0 = addiu(a0, 15232);
        s0 = subu(s0, s1);
        a1 = 0;
        s0 = sll(s0, 2);
        a2 = 60;
        s0 = addu(s0, v0);
        a0 = s0;
        jal(ctx, 0x54CC3Cu, gen::fn_memset_00521408);
        v1 = 1;
        sw(v1, s0, adxpd::kUsed);
        a0 = 500;
        sw(s1, s0, adxpd::kId);
        a1 = 0xAC44;
        sw(zero, s0, adxpd::kMode);
        a2 = addiu(s0, 48);
        sw(zero, s0, adxpd::kState);
        a3 = addiu(s0, 50);
        jal(ctx, 0x54CC64u, gen::fn_sub_539858_00539858);
        a0 = addiu(s0, 40);
        a1 = 0;
        a2 = 8;
        jal(ctx, 0x54CC74u, gen::fn_memset_00521408);
        v0 = s0;
    }
    // 0x0054cc80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054CC98 sub_54CC98 -- 36 bytes; frame 0x10: ra sp+0x0
// Set a decoder object's coefficients from cutoff and rate. [ADXPD_SetCoef]
void sub_54CC98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cc98
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    a3 = addiu(v0, 50);
    a0 = a2;
    a2 = addiu(v0, 48);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539858_00539858(ctx);  // tail call
}

// 0x0054CCC0 sub_54CCC0 -- 36 bytes; leaf frame (no stack)
// Set a decoder object's two histories (+40 ... +46). [ADXPD_SetDly]
void sub_54CCC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0054ccc0
    enter(ctx, 9);  // entry check point + this block's cycles
    lhu(v1, a1, 0);
    sh(v1, a0, adxpd::kHistL);
    lhu(v0, a2, 0);
    sh(v0, a0, adxpd::kHistL + 2);
    lhu(v1, a1, 2);
    sh(v1, a0, adxpd::kHistR);
    lhu(v0, a2, 2);
    sh(v0, a0, adxpd::kHistR + 2);
}

// 0x0054CCE8 sub_54CCE8 -- 36 bytes; leaf frame (no stack)
// Get a decoder object's two histories. [ADXPD_GetDly]
void sub_54CCE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0054cce8
    enter(ctx, 9);  // entry check point + this block's cycles
    lhu(v1, a0, adxpd::kHistL);
    sh(v1, a1, 0);
    lhu(v0, a0, adxpd::kHistL + 2);
    sh(v0, a2, 0);
    lhu(v1, a0, adxpd::kHistR);
    sh(v1, a1, 2);
    lhu(v0, a0, adxpd::kHistR + 2);
    sh(v0, a2, 2);
}

// 0x0054CD10 sub_54CD10 -- 16 bytes; leaf frame (no stack)
// Set a decoder object's key (+52 start, +54 multiplier, +56 increment). [ADXPD_SetExtPrm]
void sub_54CD10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0054cd10
    enter(ctx, 4);  // entry check point + this block's cycles
    sh(a3, a0, adxpd::kKeyAdd);
    sh(a1, a0, adxpd::kKey);
    sh(a2, a0, adxpd::kKeyMul);
}

// 0x0054CD40 sub_54CD40 -- 52 bytes; frame 0x10: ra sp+0x0
// Release a decoder object (zero its 60 bytes). [ADXPD_Destroy]
void sub_54CD40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cd40
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x0054cd68
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054cd50
    charge(ctx, 6);
    ld(ra, sp, 0x0);
    a1 = 0;
    a2 = 60;
    sw(zero, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0054CD78 sub_54CD78 -- 8 bytes; leaf frame (no stack)
// Set a decoder object's word +8. [ADXPD_SetMode]
void sub_54CD78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0054cd78
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, adxpd::kMode);
}

// 0x0054CD80 sub_54CD80 -- 8 bytes; leaf frame (no stack)
// A decoder object's state (+12: 0 idle, 1 started, 2 decoding, 3 done). [ADXPD_GetStat]
void sub_54CD80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054cd80
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxpd::kState);
}

// 0x0054CD88 sub_54CD88 -- 48 bytes; leaf frame (no stack)
// Start a mono job (kind 1): source, block count, output; refused (0) unless idle. [ADXPD_EntryMono]
void sub_54CD88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0054cd88
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, adxpd::kState);
    v1 = 1;
    if (v0 != 0) {
        // 0x0054cdb0
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0054cd94
    charge(ctx, 7);
    sw(t0, a0, adxpd::kDstR);
    sw(a1, a0, adxpd::kSrc);
    v0 = 1;
    sw(a2, a0, adxpd::kBlocks);
    sw(v1, a0, adxpd::kKind);
    sw(a3, a0, adxpd::kDstL);
}

// 0x0054CDB8 sub_54CDB8 -- 48 bytes; leaf frame (no stack)
// Start a stereo job (kind 2): source, block count, left / right outputs; refused unless idle. [ADXPD_EntrySte]
void sub_54CDB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0054cdb8
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, adxpd::kState);
    v1 = 2;
    if (v0 != 0) {
        // 0x0054cde0
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0054cdc4
    charge(ctx, 7);
    sw(t0, a0, adxpd::kDstR);
    sw(a1, a0, adxpd::kSrc);
    v0 = 1;
    sw(a2, a0, adxpd::kBlocks);
    sw(v1, a0, adxpd::kKind);
    sw(a3, a0, adxpd::kDstL);
}

// 0x0054CDE8 sub_54CDE8 -- 48 bytes; leaf frame (no stack)
// Start a mono job (kind 1) with a second output word (+36); refused unless idle. [ADXPD_EntryPl2]
void sub_54CDE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0054cde8
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, adxpd::kState);
    v1 = 1;
    if (v0 != 0) {
        // 0x0054ce10
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0054cdf4
    charge(ctx, 7);
    sw(t0, a0, adxpd::kDstR);
    sw(a1, a0, adxpd::kSrc);
    v0 = 1;
    sw(a2, a0, adxpd::kBlocks);
    sw(v1, a0, adxpd::kKind);
    sw(a3, a0, adxpd::kDstL);
}

// 0x0054CE38 sub_54CE38 -- 36 bytes; frame 0x10: ra sp+0x0
// Stop a decoder object: state 0, histories cleared. [ADXPD_Stop]
void sub_54CE38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054ce38
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 8;
    sw(zero, a0, adxpd::kState);
    a0 = addiu(a0, 40);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0054CE60 sub_54CE60 -- 24 bytes; leaf frame (no stack)
// A decoder object's state; a finished job (3) goes back to idle (0). [ADXPD_Reset]
void sub_54CE60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0054ce60
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, adxpd::kState);
    v1 = 3;
    if (v0 == v1) {
        sw(zero, a0, adxpd::kState);
    }
    // 0x0054ce70
    charge(ctx, 2);
}

// 0x0054CE78 sub_54CE78 -- 8 bytes; leaf frame (no stack)
// The blocks the last job decoded (+16). [ADXPD_GetNumBlk]
void sub_54CE78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054ce78
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxpd::kDecoded);
}

// 0x0054CE80 sub_54CE80 -- 16 bytes; leaf frame (no stack)
// Flag an odd stereo block count (0x793B78 = 1). [adxpd_SetError]
void sub_54CE80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0054ce80
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x790000;
    v0 = 1;
    sw(v0, v1, 15224);  // 0x793B78
}

// 0x0054CE90 sub_54CE90 -- 244 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// Run one decoder object: started -> decoding -> the mono or stereo decoder -> done (an odd stereo result sets the
// error flag). [ADXPD_ExecHndl]
// State 1 becomes 2 on the first call; state 2 runs the kind's decoder over the whole job and leaves 3.
void sub_54CE90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054ce90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    s1 = 1;
    sd(ra, sp, 0x30);
    lw(v1, s0, adxpd::kState);
    v0 = 2;
    if (v1 == s1) {
        // 0x0054ceb4
        charge(ctx, 3);
        v1 = 2;
        sw(v0, s0, adxpd::kState);
        v0 = 2;
    }
    // 0x0054cec0
    charge(ctx, 2);
    if (v1 != v0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x0054cec8
        charge(ctx, 3);
        lw(v0, s0, adxpd::kKind);
        if (v0 == s1) {
            // 0x0054ced4
            charge(ctx, 13);
            lw(a0, s0, adxpd::kSrc);
            a3 = addiu(s0, 40);
            lw(a1, s0, adxpd::kBlocks);
            t2 = addiu(s0, 52);
            lw(a2, s0, adxpd::kDstL);
            lh(t0, s0, adxpd::kCoef1);
            lh(t1, s0, adxpd::kCoef2);
            lh(t3, s0, adxpd::kKeyMul);
            lh(v0, s0, adxpd::kKeyAdd);
            link(ctx, 0x54CEF8u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x0);
            call(ctx, gen::fn_sub_53A410_0053a410);
            sw(v0, s0, adxpd::kDecoded);
            goto L_0054cf68;
        }
        lh(v1, s0, adxpd::kKeyMul);
        // 0x0054cf08
        charge(ctx, 22);
        t4 = addiu(s0, 52);
        lw(a0, s0, adxpd::kSrc);
        a3 = addiu(s0, 40);
        lw(a1, s0, adxpd::kBlocks);
        t1 = addiu(s0, 44);
        lw(a2, s0, adxpd::kDstL);
        lw(t0, s0, adxpd::kDstR);
        lh(t2, s0, adxpd::kCoef1);
        lh(t3, s0, adxpd::kCoef2);
        lh(v0, s0, adxpd::kKeyAdd);
        sw(v1, sp, 0x8);
        sw(t4, sp, 0x0);
        link(ctx, 0x54CF38u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x10);
        call(ctx, gen::fn_sub_53AD00_0053ad00);
        v1 = srl(v0, 31);
        sw(v0, s0, adxpd::kDecoded);
        v1 = addu(v0, v1);
        v1 = sra(v1, 1);
        v1 = sll(v1, 1);
        v0 = subu(v0, v1);
        cc = v0 != s1;  // the condition, before the delay slot changes it
        v0 = 3;
        if (!cc) {
            // 0x0054cf60
            charge(ctx, 2);
            jal(ctx, 0x54CF60u, gen::fn_sub_54CE80_0054ce80);
        L_0054cf68:
            charge(ctx, 1);
            v0 = 3;
        }
        // 0x0054cf6c
        charge(ctx, 2);
        sw(v0, s0, adxpd::kState);
        ld(s0, sp, 0x20);
    }
    // 0x0054cf74 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0054CF88 sub_54CF88 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Run every used decoder object. [ADXPD_ExecServer]
void sub_54CF88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cf88
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x790000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 15232);  // &0x793B80
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x0054cfb0
        charge(ctx, 3);
        lw(v0, s0, adxpd::kUsed);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0054cfbc
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x54CFBCu, gen::fn_sub_54CE90_0054ce90);
            s1 = addiu(s1, -1);
        }
        // 0x0054cfc8
        charge(ctx, 2);
        s0 = addiu(s0, 60);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054cfd0
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
