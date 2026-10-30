// Phase 5 slice cri2: ADXSJD, the ADX sound-joint decoder (0x541D48-0x5433A8) -- 16 handles of 168 bytes at 0x78FF98
// (cri2::adxsjd) that pull ADX blocks from an input stream joint, run the ADXB decoder on them and push 16-bit PCM
// into one output joint per channel. p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h) with a role comment
// per function and the handle's fields named where one register holds the handle for the whole body; every
// statement, charge and check point is the generator's. Roles and proposed names: game/include/p3fes/game/cri2.h.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/cri2.h"

namespace p3fes::recomp_gen {
void fn__get_peer_or_sock_name_3_0053a358(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_my_malloc_00537790(p3fes::EEContext&);
void fn_sceInsockGetErrnoMode_00537780(p3fes::EEContext&);
void fn_sub_535DD8_00535dd8(p3fes::EEContext&);
void fn_sub_535E28_00535e28(p3fes::EEContext&);
void fn_sub_535FC0_00535fc0(p3fes::EEContext&);
void fn_sub_535FF0_00535ff0(p3fes::EEContext&);
void fn_sub_536080_00536080(p3fes::EEContext&);
void fn_sub_537890_00537890(p3fes::EEContext&);
void fn_sub_5379B0_005379b0(p3fes::EEContext&);
void fn_sub_537CF0_00537cf0(p3fes::EEContext&);
void fn_sub_537D90_00537d90(p3fes::EEContext&);
void fn_sub_537F08_00537f08(p3fes::EEContext&);
void fn_sub_537F30_00537f30(p3fes::EEContext&);
void fn_sub_537F40_00537f40(p3fes::EEContext&);
void fn_sub_538038_00538038(p3fes::EEContext&);
void fn_sub_538040_00538040(p3fes::EEContext&);
void fn_sub_538048_00538048(p3fes::EEContext&);
void fn_sub_538060_00538060(p3fes::EEContext&);
void fn_sub_5382C0_005382c0(p3fes::EEContext&);
void fn_sub_5382C8_005382c8(p3fes::EEContext&);
void fn_sub_538348_00538348(p3fes::EEContext&);
void fn_sub_538360_00538360(p3fes::EEContext&);
void fn_sub_5383A8_005383a8(p3fes::EEContext&);
void fn_sub_5383E8_005383e8(p3fes::EEContext&);
void fn_sub_5383F0_005383f0(p3fes::EEContext&);
void fn_sub_5389B0_005389b0(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_53AE60_0053ae60(p3fes::EEContext&);
void fn_sub_541D48_00541d48(p3fes::EEContext&);
void fn_sub_541DE8_00541de8(p3fes::EEContext&);
void fn_sub_541E28_00541e28(p3fes::EEContext&);
void fn_sub_541FA8_00541fa8(p3fes::EEContext&);
void fn_sub_542008_00542008(p3fes::EEContext&);
void fn_sub_542010_00542010(p3fes::EEContext&);
void fn_sub_542060_00542060(p3fes::EEContext&);
void fn_sub_5420A0_005420a0(p3fes::EEContext&);
void fn_sub_5420D0_005420d0(p3fes::EEContext&);
void fn_sub_542100_00542100(p3fes::EEContext&);
void fn_sub_542130_00542130(p3fes::EEContext&);
void fn_sub_542438_00542438(p3fes::EEContext&);
void fn_sub_542558_00542558(p3fes::EEContext&);
void fn_sub_5428C0_005428c0(p3fes::EEContext&);
void fn_sub_542A88_00542a88(p3fes::EEContext&);
void fn_sub_542B18_00542b18(p3fes::EEContext&);
void fn_sub_542BC8_00542bc8(p3fes::EEContext&);
void fn_sub_542C70_00542c70(p3fes::EEContext&);
void fn_sub_542DC0_00542dc0(p3fes::EEContext&);
void fn_sub_542F00_00542f00(p3fes::EEContext&);
void fn_sub_542F60_00542f60(p3fes::EEContext&);
void fn_sub_542F68_00542f68(p3fes::EEContext&);
void fn_sub_542F88_00542f88(p3fes::EEContext&);
void fn_sub_5430A8_005430a8(p3fes::EEContext&);
void fn_sub_5430B8_005430b8(p3fes::EEContext&);
void fn_sub_5430C8_005430c8(p3fes::EEContext&);
void fn_sub_5430D8_005430d8(p3fes::EEContext&);
void fn_sub_5430E8_005430e8(p3fes::EEContext&);
void fn_sub_543100_00543100(p3fes::EEContext&);
void fn_sub_543118_00543118(p3fes::EEContext&);
void fn_sub_543130_00543130(p3fes::EEContext&);
void fn_sub_543148_00543148(p3fes::EEContext&);
void fn_sub_543178_00543178(p3fes::EEContext&);
void fn_sub_5431A8_005431a8(p3fes::EEContext&);
void fn_sub_5431D8_005431d8(p3fes::EEContext&);
void fn_sub_5431F0_005431f0(p3fes::EEContext&);
void fn_sub_543220_00543220(p3fes::EEContext&);
void fn_sub_543238_00543238(p3fes::EEContext&);
void fn_sub_543268_00543268(p3fes::EEContext&);
void fn_sub_5432C0_005432c0(p3fes::EEContext&);
void fn_sub_5433A8_005433a8(p3fes::EEContext&);
void fn_sub_562DE0_00562de0(p3fes::EEContext&);
void fn_sub_562DE8_00562de8(p3fes::EEContext&);
void fn_sub_562DF0_00562df0(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_width__CQ24_STL8ios_base_00537fe8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace cri2;

// 0x00541D48 sub_541D48 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSJD init: the first call clears the 16 handles. [ADXSJD_Init]
void sub_541D48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541d48
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -112);  // &0x78FF90
    lw(v1, s0, 0);  // 0x78FF90
    sd(ra, sp, 0x8);
    if (v1 == 0) {
        // 0x00541d64
        charge(ctx, 7);
        jal(ctx, 0x541D64u, gen::fn_my_malloc_00537790);
        a0 = 0x790000;
        a0 = addiu(a0, -104);  // &0x78FF98
        a1 = 0;
        a2 = 2688;
        jal(ctx, 0x541D78u, gen::fn_memset_00521408);
    }
    // 0x00541d80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, 0);
    ld(ra, sp, 0x8);
    v0 = addiu(v0, 1);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00541DE8 sub_541DE8 -- 60 bytes; leaf frame (no stack)
// reset a decoder handle's counters (trap -1, max 0x7FFFFFFF). [adxsjd_ResetCounters]
void sub_541DE8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00541de8
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x7FFF0000;
    v1 = si(-1);
    v0 = v0 | 0xFFFF;
    sw(v1, a0, adxsjd::kTrapSmp);
    sw(v0, a0, adxsjd::kMaxDec);
    sw(zero, a0, adxsjd::kPend1);
    sw(zero, a0, adxsjd::kHdrLen);
    sw(zero, a0, adxsjd::kDecSmpl);
    sw(zero, a0, adxsjd::kDecByte);
    sw(zero, a0, adxsjd::kDecSmplTotal);
    sw(zero, a0, adxsjd::kTrapCnt);
    sw(zero, a0, adxsjd::kTrapByte);
    sb(zero, a0, adxsjd::kAhx);
    sw(zero, a0, adxsjd::kPend0);
}

// 0x00541E28 sub_541E28 -- 380 bytes; frame 0x40: s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x30
// create a decoder handle on an input joint and N output joints (creates the ADXB decoder). [ADXSJD_Create]
void sub_541E28(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541e28
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a3 = 0x790000;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s5, sp, 0x28);
    s5 = a0;
    sd(s0, sp, 0x0);
    v1 = addiu(a3, -104);  // &0x78FF98
    sd(s1, sp, 0x8);
    a1 = 0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x30);
    lb(v0, v1, 0);  // 0x78FF98
    lw(s0, s4, 0);
    if (v0 != 0) {
        // 0x00541e6c
        charge(ctx, 1);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x00541e70
            charge(ctx, 3);
            v0 = slti(a1, 16);
            v1 = addiu(v1, 168);
            if (v0 != 0) {
                // 0x00541e7c
                charge(ctx, 6);
                lb(v0, v1, 0);
                if (v0 != 0) {
                    a1 = addiu(a1, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00541e94
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (a1 != v1) {
        // 0x00541ea0
        charge(ctx, 28);
        v0 = sll(a1, 2);
        v1 = addiu(a3, -104);
        v0 = addu(v0, a1);
        a0 = s0;
        v0 = sll(v0, 2);
        v0 = addu(v0, a1);
        v0 = sll(v0, 3);
        s2 = addu(v0, v1);
        jal(ctx, 0x541EBCu, gen::fn_sub_562DE0_00562de0);
        a0 = s0;
        s1 = v0;
        jal(ctx, 0x541EC8u, gen::fn_sub_562DE8_00562de8);
        a0 = s0;
        s0 = srl(v0, 31);
        s0 = addu(s0, v0);
        jal(ctx, 0x541ED8u, gen::fn_sub_562DF0_00562df0);
        a3 = srl(v0, 31);
        s0 = sra(s0, 1);
        a3 = addu(a3, v0);
        a2 = s0;
        a3 = sra(a3, 1);
        a0 = s3;
        a1 = s1;
        a3 = addu(a2, a3);
        jal(ctx, 0x541EFCu, gen::fn_sub_537890_00537890);
        a0 = v0;
        sw(a0, s2, adxsjd::kAdxb);
        if (a0 != 0) {
            // 0x00541f10
            charge(ctx, 8);
            a1 = 0x540000;
            a2 = s2;
            a1 = addiu(a1, 9272);  // &sub_542438
            jal(ctx, 0x541F18u, gen::fn_sub_537F08_00537f08);
            sw(s5, s2, adxsjd::kSji);
            sb(s3, s2, adxsjd::kNch);
            a2 = 0;
            if (i64(s3) > 0) {
                // 0x00541f30
                charge(ctx, 2);
                a3 = addiu(s2, 12);
                for (;;) {
                    // 0x00541f38
                    charge(ctx, 8);
                    v0 = sll(a2, 2);
                    a2 = addiu(a2, 1);
                    v1 = addu(v0, s4);
                    v0 = addu(a3, v0);
                    lw(a0, v1, 0);
                    a1 = slt(a2, s3);
                    sw(a0, v0, 0);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00541f58
            charge(ctx, 10);
            sb(zero, s2, adxsjd::kStat);
            a0 = s2;
            jal(ctx, 0x541F5Cu, gen::fn_sub_541DE8_00541de8);
            sw(zero, s2, adxsjd::kTrapFn);
            v0 = 1;
            sw(zero, s2, adxsjd::kTrapObj);
            sw(zero, s2, adxsjd::kFltFn);
            sw(zero, s2, adxsjd::kFltObj);
            sb(v0, s2, adxsjd::kUsed);
            v0 = s2;
        }
    }
    // 0x00541f80 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00541FA8 sub_541FA8 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// destroy a decoder handle (and its ADXB decoder). [ADXSJD_Destroy]
void sub_541FA8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541fa8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00541ff8
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00541fbc
    charge(ctx, 3);
    lw(v0, s0, adxsjd::kAdxb);
    a0 = v0;
    if (v0 != 0) {
        // 0x00541fc8
        charge(ctx, 2);
        link(ctx, 0x541FC8u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, adxsjd::kAdxb);
        call(ctx, gen::fn_sub_5379B0_005379b0);
    }
    // 0x00541fd0
    charge(ctx, 10);
    jal(ctx, 0x541FD0u, gen::fn_sub_539818_00539818);
    a0 = s0;
    a1 = 0;
    a2 = 168;
    jal(ctx, 0x541FE0u, gen::fn_memset_00521408);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00542008 sub_542008 -- 8 bytes; leaf frame (no stack)
// a decoder handle's state. [ADXSJD_GetStat]
void sub_542008(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00542008
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, adxsjd::kStat);
}

// 0x00542010 sub_542010 -- 64 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// set the input joint (also into the ADXB decoder). [ADXSJD_SetInSj]
void sub_542010(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542010
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(s1, s0, adxsjd::kSji);
    link(ctx, 0x54202Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxsjd::kAdxb);
    call(ctx, gen::fn_sub_535FC0_00535fc0);
    lw(a0, s0, adxsjd::kAdxb);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_535DD8_00535dd8(ctx);  // tail call
}

// 0x00542060 sub_542060 -- 96 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// set the samples per call (the ADXB decoder gets it and /1536). [ADXSJD_SetMaxDecSmpl]
void sub_542060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542060
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    sw(s1, s0, adxsjd::kMaxDec);
    link(ctx, 0x54207Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxsjd::kAdxb);
    call(ctx, gen::fn_sub_535FF0_00535ff0);
    lw(a0, s0, adxsjd::kAdxb);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x00535e08
    charge(ctx, 5);
    v0 = 1536;
    sw(a1, a0, 196);
    div(a1, v0);
    if (v0 == 0) {
        brk(ctx, 0x535E18u, 0x7u);
    }
    // 0x00535e1c
    charge(ctx, 3);
    mflo(v1);
    sw(v1, a0, 200);
}

// 0x005420A0 sub_5420A0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// tell the ADXB decoder the input ended. [ADXSJD_TermSupply]
void sub_5420A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005420a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x5420B0u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxsjd::kAdxb);
    call(ctx, gen::fn_sub_536080_00536080);
    lw(a0, s0, adxsjd::kAdxb);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_535E28_00535e28(ctx);  // tail call
}

// 0x005420D0 sub_5420D0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// start: reset the counters, state 1 (header). [ADXSJD_Start]
void sub_5420D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005420d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5420DCu, gen::fn_sub_541DE8_00541de8);
    v0 = 1;
    ld(ra, sp, 0x8);
    sb(v0, s0, adxsjd::kStat);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00542100 sub_542100 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// stop: stop the ADXB decoder, state 0. [ADXSJD_Stop]
void sub_542100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542100
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x542110u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxsjd::kAdxb);
    call(ctx, gen::fn_sub_538360_00538360);
    sb(zero, s0, adxsjd::kStat);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00542130 sub_542130 -- 776 bytes; frame 0x50: s3 sp+0x38, s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s4 sp+0x40, ra sp+0x48
// the header stage: skip zero padding, hand the header to ADXB, keep it for format 2, state 2 or 4.
//   [adxsjd_DecodeHeader]
void sub_542130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00542130
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a1 = 1;
    sd(s3, sp, 0x38);
    s3 = a0;
    sd(s0, sp, 0x20);
    a2 = 0xC800;
    sd(s1, sp, 0x28);
    a3 = sp;
    sd(s2, sp, 0x30);
    sd(s4, sp, 0x40);
    sd(ra, sp, 0x48);
    lw(s0, s3, adxsjd::kSji);
    lw(s2, s3, adxsjd::kAdxb);
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a0 = s0;
    jalr(ctx, 0x54216Cu, v0.u());
    lw(a0, sp, 0x4);
    a1 = 0;
    if (i64(a0) > 0) {
        // 0x00542180
        charge(ctx, 4);
        lw(v1, sp, 0x0);
        lb(v0, v1, 0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = srl(a1, 31);
        if (!cc) {
            // 0x00542190
            charge(ctx, 4);
            a2 = a0;
            a0 = v1;
            a1 = addiu(a1, 1);
            for (;;) {
                // 0x005421a0
                charge(ctx, 3);
                v0 = slt(a1, a2);
                v1 = addu(a0, a1);
                if (v0 != 0) {
                    // 0x005421ac
                    charge(ctx, 6);
                    lb(v0, v1, 0);
                    if (v0 == 0) {
                        a1 = addiu(a1, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            goto L_005421c4;
        }
        goto L_005421c8;
    }
L_005421c4:
    charge(ctx, 1);
    v0 = srl(a1, 31);
L_005421c8:
    charge(ctx, 6);
    v1 = addiu(a1, -1);
    v0 = addu(a1, v0);
    v0 = sra(v0, 1);
    v0 = sll(v0, 1);
    s4 = addiu(sp, 0x10);
    if (v0 == v1) {
        // 0x005421e0
        charge(ctx, 10);
        lw(v1, s0, 0);
        a0 = s0;
        a1 = 1;
        lw(v0, v1, 28);
        a2 = sp;
        jalr(ctx, 0x5421F0u, v0.u());
        jal(ctx, 0x5421F8u, gen::fn_sceInsockGetErrnoMode_00537780);
        if (v0 != 0) {
            v0 = 4;
        } else {
            // 0x00542208
            charge(ctx, 7);
            a0 = 0x7C0000;
            a1 = 0x7C0000;
            a0 = addiu(a0, 9664);  // "E04102501 adxsjd_decode_prep: "
            a1 = addiu(a1, 9696);  // "The data alignment is illegal."
            jal(ctx, 0x542214u, gen::fn_sub_53AE60_0053ae60);
            v0 = 4;
        }
        goto L_00542414;
    }
    // 0x00542228
    charge(ctx, 14);
    a0 = sp;
    a2 = s4;
    a3 = sp;
    jal(ctx, 0x542230u, gen::fn_sub_563C28_00563c28);
    lw(v1, s0, 0);
    a2 = s4;
    a0 = s0;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x542248u, v0.u());
    lw(a2, sp, 0x4);
    v0 = slti(a2, 16);
    if (v0 != 0) {
        lw(v1, s0, 0);
    } else {
        // 0x00542260
        charge(ctx, 6);
        lw(a1, sp, 0x0);
        a0 = s2;
        jal(ctx, 0x542264u, gen::fn_sub_537D90_00537d90);
        s1 = v0;
        lw(v0, sp, 0x4);
        if (s1 != 0) {
            // 0x00542278
            charge(ctx, 3);
            v0 = slt(v0, s1);
            if (v0 != 0) {
                goto L_00542284;
            }
            // 0x005422a8
            charge(ctx, 2);
            if (i64(s1) >= 0) {
                sw(s1, s3, adxsjd::kHdrLen);
            } else {
                // 0x005422b0
                charge(ctx, 3);
                lh(v0, s2, 154);
                a0 = s2;
                if (v0 != 0) {
                    // 0x005422bc
                    charge(ctx, 4);
                    s1 = 0;
                    jal(ctx, 0x5422BCu, gen::fn_sub_537CF0_00537cf0);
                    sw(s1, s3, adxsjd::kHdrLen);
                    goto L_00542318;
                }
                // 0x005422d0
                charge(ctx, 10);
                lw(v1, s0, 0);
                a0 = s0;
                a1 = 1;
                lw(v0, v1, 28);
                a2 = sp;
                jalr(ctx, 0x5422E0u, v0.u());
                jal(ctx, 0x5422E8u, gen::fn_sceInsockGetErrnoMode_00537780);
                if (v0 != 0) {
                    v0 = 4;
                } else {
                    // 0x005422f8
                    charge(ctx, 7);
                    a0 = 0x7C0000;
                    a1 = 0x7C0000;
                    a0 = addiu(a0, 9728);  // "E03010901 ADXB_DecodeHeader: "
                    a1 = addiu(a1, 9760);  // "Can not decode this file format."
                    jal(ctx, 0x542304u, gen::fn_sub_53AE60_0053ae60);
                    v0 = 4;
                }
                goto L_00542414;
            }
        L_00542318:
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x542318u, gen::fn_sub_537F30_00537f30);
            v1 = 4;
            cc = v0 != v1;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x0054232c
                charge(ctx, 1);
                sb(v0, s3, adxsjd::kAhx);
            }
            // 0x00542330
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x542330u, gen::fn_sub_537F30_00537f30);
            v1 = 2;
            cc = v0 != v1;  // the condition, before the delay slot changes it
            v1 = 64;
            if (!cc) {
                // 0x00542344
                charge(ctx, 6);
                lw(a2, sp, 0x4);
                lw(a1, sp, 0x0);
                a0 = addiu(s3, 88);
                v0 = slti(a2, 65);
                if (v0 == 0) a2 = v1;
                jal(ctx, 0x542354u, gen::fn_memcpy_00521250);
            }
            // 0x0054235c
            charge(ctx, 7);
            a0 = s2;
            jal(ctx, 0x54235Cu, gen::fn_sub_537F30_00537f30);
            v1 = v0;
            v0 = addiu(v1, -10);
            v0 = sltiu(v0, 3);
            if (v0 != 0) {
                lw(v1, s0, 0);
            } else {
                // 0x00542378
                charge(ctx, 3);
                v0 = 20;
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = 15;
                if (!cc) {
                    // 0x00542384
                    charge(ctx, 2);
                    a0 = sp;
                    if (v1 == v0) {
                        goto L_0054238c;
                    }
                    // 0x005423b0
                    charge(ctx, 17);
                    a2 = sp;
                    a1 = s1;
                    a3 = s4;
                    jal(ctx, 0x5423B8u, gen::fn_sub_563C28_00563c28);
                    lw(v1, s0, 0);
                    a0 = s0;
                    a1 = 0;
                    lw(v0, v1, 32);
                    a2 = sp;
                    jalr(ctx, 0x5423D0u, v0.u());
                    lw(v1, s0, 0);
                    a0 = s0;
                    a2 = s4;
                    lw(v0, v1, 28);
                    a1 = 1;
                    jalr(ctx, 0x5423E8u, v0.u());
                    lw(v0, s2, 232);
                    goto L_005423f4;
                }
            L_0054238c:
                charge(ctx, 1);
                lw(v1, s0, 0);
            }
            // 0x00542390
            charge(ctx, 7);
            a0 = s0;
            a1 = 1;
            lw(v0, v1, 28);
            a2 = sp;
            jalr(ctx, 0x54239Cu, v0.u());
            lw(v0, s2, 232);
        L_005423f4:
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 0x790000;
            if (!cc) {
                // 0x005423fc
                charge(ctx, 3);
                lw(v0, v0, -108);
                a0 = s2;
                if (v0 != 0) {
                    // 0x00542408
                    charge(ctx, 2);
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x542408u);  // $ra = the return address
                    lw(a1, a0, 20);
                    call_ptr(ctx, jt);
                }
            }
            // 0x00542410
            charge(ctx, 1);
            v0 = 2;
        L_00542414:
            charge(ctx, 2);
            sb(v0, s3, adxsjd::kStat);
            ld(s0, sp, 0x20);
            // 0x0054241c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s1, sp, 0x28);
            ld(s2, sp, 0x30);
            ld(s3, sp, 0x38);
            ld(s4, sp, 0x40);
            ld(ra, sp, 0x48);
            sp = addiu(sp, 0x50);
            return;
        }
    L_00542284:
        charge(ctx, 1);
        lw(v1, s0, 0);
    }
    // 0x00542288
    charge(ctx, 7);
    a0 = s0;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x542294u, v0.u());
    ld(s0, sp, 0x20);
    // 0x0054241c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00542438 sub_542438 -- 296 bytes, 2 chunks; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, s4 sp+0x20, ra sp+0x40
// the ADXB decoder's output callback: free room per channel, samples allowed before the trap. [adxsjd_GetWrInfo]
void sub_542438(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542438
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = a3;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s7, sp, 0x38);
    s7 = a2;
    sd(s4, sp, 0x20);
    s1 = addiu(s2, 28);
    sd(ra, sp, 0x40);
    s0 = addiu(s2, 12);
    lw(s4, s2, adxsjd::kSjo);
    for (;;) {
        // 0x005424a0
        charge(ctx, 9);
        link(ctx, 0x5424A0u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, adxsjd::kAdxb);
        call(ctx, gen::fn_sub_537F40_00537f40);
        a1 = 0;
        v0 = slt(s3, v0);
        s3 = addiu(s3, 1);
        a3 = s1;
        s1 = addiu(s1, 8);
        a2 = 16384;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00542488
        charge(ctx, 6);
        lw(v0, s0, 0);
        s0 = addiu(s0, 4);
        lw(v1, v0, 0);
        lw(t0, v1, 24);
        a0 = v0;
        jalr(ctx, 0x542498u, t0.u());
    }
    // 0x005424c4
    charge(ctx, 19);
    a0 = s4;
    jal(ctx, 0x5424C4u, gen::fn_sub_562DE0_00562de0);
    lw(v1, s2, adxsjd::kOutChunk);
    v1 = subu(v1, v0);
    v0 = srl(v1, 31);
    v1 = addu(v1, v0);
    v1 = sra(v1, 1);
    sw(v1, s6, 0);
    lw(v0, s2, 32);
    lw(a0, s2, adxsjd::kMaxDec);
    v1 = srl(v0, 31);
    v0 = addu(v0, v1);
    v0 = sra(v0, 1);
    v1 = slt(v0, a0);
    if (v1 != 0) a0 = v0;
    sw(a0, s7, 0);
    lw(v1, s2, adxsjd::kTrapSmp);
    if (i64(v1) < 0) {
        v0 = 0x1FFF0000;
        // 0x00542520
        charge(ctx, 1);
        v0 = v0 | 0xFFFF;
    } else {
        // 0x00542510
        charge(ctx, 3);
        lw(v0, s2, adxsjd::kTrapCnt);
        v0 = subu(v1, v0);
    }
    // 0x00542524
    charge(ctx, 13);
    sw(v0, s5, 0);
    lw(a0, s2, adxsjd::kAdxb);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    backedge(ctx);
    // 0x00537f28
    charge(ctx, 2);
    lw(v0, a0, 60);
}

// 0x00542558 sub_542558 -- 868 bytes; frame 0x50: s2 sp+0x30, s0 sp+0x20, s1 sp+0x28, s3 sp+0x38, s4 sp+0x40, ra sp+0x48
// the decode stage's input side: the trap, an AHX resync, feed ADXB the input chunk. [adxsjd_DecodeExec]
void sub_542558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00542558
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s0, sp, 0x20);
    sd(s1, sp, 0x28);
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(ra, sp, 0x48);
    lw(v1, s2, adxsjd::kTrapSmp);
    lw(s4, s2, adxsjd::kAdxb);
    lw(s1, s2, adxsjd::kSji);
    if (i64(v1) >= 0) {
        // 0x00542588
        charge(ctx, 4);
        lw(v0, s2, adxsjd::kTrapCnt);
        v0 = slt(v0, v1);
        if (v0 != 0) {
            lb(v1, s2, adxsjd::kAhx);
        } else {
            // 0x00542598
            charge(ctx, 3);
            lw(v0, s2, adxsjd::kTrapFn);
            if (v0 != 0) {
                // 0x005425a4
                charge(ctx, 2);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x5425A4u);  // $ra = the return address
                lw(a0, s2, adxsjd::kTrapObj);
                call_ptr(ctx, jt);
                goto L_005425ac;
            }
            lb(v1, s2, adxsjd::kAhx);
        }
        goto L_005425b0;
    }
L_005425ac:
    charge(ctx, 1);
    lb(v1, s2, adxsjd::kAhx);
L_005425b0:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
        lw(v0, s1, 0);
    } else {
        // 0x005425bc
        charge(ctx, 7);
        lw(v1, s1, 0);
        a0 = s1;
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x5425C8u, v0.u());
        if (v0 != 0) {
            lw(v0, s1, 0);
            goto L_005425e8;
        }
        // 0x005425d8
        charge(ctx, 3);
        v0 = 3;
        sb(v0, s2, adxsjd::kStat);
    L_0054289c:
        charge(ctx, 1);
        ld(s0, sp, 0x20);
        // 0x005428a0 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
L_005425e8:
    charge(ctx, 12);
    s3 = addiu(s2, 20);
    a2 = 0x7FFF0000;
    a0 = s1;
    lw(v1, v0, 24);
    a1 = 1;
    a2 = a2 | 0xFFFF;
    a3 = s3;
    jalr(ctx, 0x542600u, v1.u());
    a0 = s4;
    jal(ctx, 0x542608u, gen::fn_sub_537F30_00537f30);
    if (v0 == 0) {
        // 0x00542618
        charge(ctx, 4);
        lw(a2, s2, 24);
        v0 = slti(a2, 4);
        a1 = 0x8001;
        if (v0 != 0) {
            goto L_00542798;
        }
        // 0x00542628
        charge(ctx, 8);
        lw(a0, s3, 0);
        lhu(v1, a0, 0);
        lbu(v0, a0, 1);
        v1 = sll(v1, 8);
        v0 = v0 | v1;
        v0 = v0 & 0xFFFF;
        cc = v0 != a1;  // the condition, before the delay slot changes it
        v0 = 3;
        if (cc) {
            goto L_00542798;
        }
        // 0x00542648
        charge(ctx, 6);
        a1 = a2;
        sb(v0, s2, adxsjd::kStat);
        a2 = addiu(sp, 0x10);
        jal(ctx, 0x542650u, gen::fn__get_peer_or_sock_name_3_0053a358);
        if (v0 != 0) {
            lw(v0, s2, adxsjd::kTrapFlag);
        } else {
            // 0x00542660
            charge(ctx, 5);
            lh(a1, sp, 0x10);
            lw(v0, s2, 24);
            v0 = slt(v0, a1);
            if (v0 == 0) {
                // 0x00542674
                charge(ctx, 17);
                a0 = s3;
                a2 = s3;
                a3 = sp;
                jal(ctx, 0x54267Cu, gen::fn_sub_563C28_00563c28);
                lw(v1, s1, 0);
                a0 = s1;
                a1 = 0;
                lw(v0, v1, 32);
                a2 = s3;
                jalr(ctx, 0x542694u, v0.u());
                lw(v1, s1, 0);
                a0 = s1;
                a1 = 1;
                lw(v0, v1, 28);
                a2 = sp;
                jalr(ctx, 0x5426ACu, v0.u());
                lw(v0, s2, adxsjd::kTrapFlag);
                goto L_005426b8;
            }
            lw(v1, s1, 0);
        L_00542814:
            charge(ctx, 7);
            a0 = s1;
            a2 = s3;
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x542820u, v0.u());
            ld(s0, sp, 0x20);
            // 0x005428a0 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s1, sp, 0x28);
            ld(s2, sp, 0x30);
            ld(s3, sp, 0x38);
            ld(s4, sp, 0x40);
            ld(ra, sp, 0x48);
            sp = addiu(sp, 0x50);
            return;
        }
    L_005426b8:
        charge(ctx, 2);
        s4 = s3;
        if (v0 == 0) {
            goto L_0054289c;
        }
        // 0x005426c0
        charge(ctx, 2);
        lw(v1, s1, 0);
        for (;;) {
            // 0x00542764
            charge(ctx, 10);
            a2 = 0x7FFF0000;
            a0 = s1;
            a1 = 1;
            lw(v0, v1, 24);
            a2 = a2 | 0xFFFF;
            a3 = s3;
            jalr(ctx, 0x542778u, v0.u());
            lw(a0, s2, 24);
            a1 = 0;
            if (a0 == 0) {
                goto L_0054278c_26;
            }
            backedge(ctx);
            // 0x005426c8
            charge(ctx, 3);
            s0 = slt(a1, a0);
            if (s0 == 0) {
                a0 = s4;
            } else {
                // 0x005426d4
                charge(ctx, 4);
                lw(v0, s3, 0);
                lb(v1, v0, 0);
                if (v1 != 0) {
                    a0 = s4;
                } else {
                    // 0x005426e4
                    charge(ctx, 3);
                    a2 = a0;
                    a1 = addiu(a1, 1);
                    for (;;) {
                        // 0x005426f0
                        charge(ctx, 3);
                        v0 = slt(a1, a2);
                        if (v0 != 0) {
                            // 0x005426fc
                            charge(ctx, 6);
                            lw(v0, s2, adxsjd::kInChunk);
                            v0 = addu(v0, a1);
                            lb(v1, v0, 0);
                            if (v1 != 0) {
                                goto L_00542714_21;
                            }
                            a1 = addiu(a1, 1);
                            backedge(ctx);
                            continue;
                        }
                        s0 = slt(a1, a0);
                        break;
                    }
                L_00542718:
                    charge(ctx, 1);
                    a0 = s4;
                }
            }
            // 0x0054271c
            charge(ctx, 17);
            a2 = s4;
            a3 = sp;
            jal(ctx, 0x542720u, gen::fn_sub_563C28_00563c28);
            lw(v1, s1, 0);
            a0 = s1;
            a1 = 0;
            lw(v0, v1, 32);
            a2 = s4;
            jalr(ctx, 0x542738u, v0.u());
            lw(v1, s1, 0);
            a0 = s1;
            a1 = 1;
            lw(v0, v1, 28);
            a2 = sp;
            jalr(ctx, 0x542750u, v0.u());
            cc = s0 != 0;  // the condition, before the delay slot changes it
            ld(s0, sp, 0x20);
            if (!cc) {
                // 0x00542760
                charge(ctx, 1);
                lw(v1, s1, 0);
                continue;
            }
            break;
        }
        // 0x005428a0 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
L_00542798:
    charge(ctx, 6);
    a0 = s2;
    jal(ctx, 0x542798u, gen::fn_sub_543178_00543178);
    lw(v1, s2, adxsjd::kDecSmplTotal);
    v1 = slt(v1, v0);
    v0 = 3;
    if (v1 != 0) {
        // 0x005427d8
        charge(ctx, 14);
        a0 = s2;
        jal(ctx, 0x5427D8u, gen::fn_sub_543148_00543148);
        lw(a0, s2, adxsjd::kSjo);
        s0 = v0;
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        a1 = 0;
        jalr(ctx, 0x5427F0u, v0.u());
        v1 = srl(v0, 31);
        v1 = addu(v1, v0);
        v1 = sra(v1, 1);
        v1 = slt(v1, s0);
        if (v1 != 0) {
            // 0x00542810
            charge(ctx, 1);
            lw(v1, s1, 0);
            goto L_00542814;
        }
        // 0x00542830
        charge(ctx, 5);
        a0 = s4;
        jal(ctx, 0x542830u, gen::fn_sub_537F30_00537f30);
        v1 = 10;
        a1 = 1;
        if (v0 == v1) {
            // 0x00542844
            charge(ctx, 5);
            lw(v1, s1, 0);
            a0 = s1;
            lw(v0, v1, 28);
            a2 = s3;
            jalr(ctx, 0x542850u, v0.u());
        }
        // 0x00542858
        charge(ctx, 5);
        a0 = s4;
        jal(ctx, 0x542858u, gen::fn_sub_537F30_00537f30);
        v1 = 15;
        if (v0 != v1) {
            lw(a2, s2, 24);
        } else {
            // 0x0054286c
            charge(ctx, 7);
            lw(v1, s1, 0);
            a0 = s1;
            a2 = s3;
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x54287Cu, v0.u());
            lw(a2, s2, 24);
        }
        // 0x00542888
        charge(ctx, 5);
        a0 = s4;
        link(ctx, 0x54288Cu);  // $ra first: the delay slot below depends on it
        lw(a1, s2, adxsjd::kInChunk);
        call(ctx, gen::fn_sub_5382C8_005382c8);
        a0 = s4;
        jal(ctx, 0x542894u, gen::fn_sub_538348_00538348);
        goto L_0054289c;
    }
    // 0x005427b0
    charge(ctx, 9);
    a0 = s1;
    sb(v0, s2, adxsjd::kStat);
    a2 = s3;
    lw(v0, s1, 0);
    lw(v1, v0, 28);
    a1 = 1;
    jalr(ctx, 0x5427C4u, v1.u());
    ld(s0, sp, 0x20);
    // 0x005428a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_00542714_21:
    charge(ctx, 1);
    s0 = slt(a1, a0);
    goto L_00542718;
L_0054278c_26:
    charge(ctx, 2);
    ld(s0, sp, 0x20);
    // 0x005428a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x005428C0 sub_5428C0 -- 452 bytes; frame 0x80: s0 sp+0x30, s2 sp+0x40, s3 sp+0x48, s4 sp+0x50, s5 sp+0x58, s6 sp+0x60, fp sp+0x70, s1 sp+0x38, s7 sp+0x68, ra sp+0x78
// the decode stage's output side: put the consumed input back, the PCM chunks forward, run the filter.
//   [adxsjd_DecodeEnd]
void sub_5428C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005428c0
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s0, sp, 0x30);
    sd(s2, sp, 0x40);
    s2 = a0;
    sd(s3, sp, 0x48);
    sd(s4, sp, 0x50);
    s4 = addiu(s2, 12);
    sd(s5, sp, 0x58);
    s5 = addiu(s2, 28);
    sd(s6, sp, 0x60);
    s6 = 0;
    sd(fp, sp, 0x70);
    sd(s1, sp, 0x38);
    sd(s7, sp, 0x68);
    sd(ra, sp, 0x78);
    lw(s7, s2, adxsjd::kAdxb);
    lw(s1, s2, adxsjd::kSji);
    a0 = s7;
    jal(ctx, 0x542904u, gen::fn_width__CQ24_STL8ios_base_00537fe8);
    a0 = s7;
    s0 = v0;
    jal(ctx, 0x542910u, gen::fn_sub_5383E8_005383e8);
    a0 = s7;
    link(ctx, 0x54291Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x20);
    call(ctx, gen::fn_sub_5383F0_005383f0);
    a0 = addiu(s2, 20);
    s3 = v0;
    lw(v0, s2, adxsjd::kDecSmplTotal);
    fp = addiu(sp, 0x10);
    lw(a1, sp, 0x20);
    s0 = subu(s0, v0);
    a2 = sp;
    v0 = slt(s3, s0);
    a3 = fp;
    if (v0 == 0) s3 = s0;
    jal(ctx, 0x542948u, gen::fn_sub_563C28_00563c28);
    lw(v1, s1, 0);
    a2 = sp;
    a0 = s1;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x542960u, v0.u());
    lw(v1, s1, 0);
    a0 = s1;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = fp;
    jalr(ctx, 0x542978u, v0.u());
    for (;;) {
        // 0x005429e8
        charge(ctx, 8);
        link(ctx, 0x5429E8u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, adxsjd::kAdxb);
        call(ctx, gen::fn_sub_537F40_00537f40);
        a0 = s5;
        v0 = slt(s6, v0);
        a1 = sll(s3, 1);
        a2 = sp;
        a3 = fp;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00542988
        charge(ctx, 6);
        jal(ctx, 0x542988u, gen::fn_sub_563C28_00563c28);
        lw(v0, s2, adxsjd::kFltFn);
        a1 = s6;
        s6 = addiu(s6, 1);
        if (v0 != 0) {
            // 0x005429a0
            charge(ctx, 4);
            lw(a0, s2, adxsjd::kFltObj);
            lw(a2, sp, 0x0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x5429A8u);  // $ra = the return address
            lw(a3, sp, 0x4);
            call_ptr(ctx, jt);
        }
        // 0x005429b0
        charge(ctx, 14);
        lw(a0, s4, 0);
        a2 = sp;
        a1 = 1;
        lw(v1, a0, 0);
        lw(v0, v1, 32);
        s5 = addiu(s5, 8);
        jalr(ctx, 0x5429C4u, v0.u());
        lw(a0, s4, 0);
        a1 = 0;
        a2 = fp;
        lw(v1, a0, 0);
        lw(v0, v1, 28);
        s4 = addiu(s4, 4);
        jalr(ctx, 0x5429E0u, v0.u());
    }
    // 0x00542a08
    charge(ctx, 31);
    lw(v1, s2, adxsjd::kDecSmpl);
    a0 = s7;
    lw(v0, sp, 0x20);
    v1 = addu(v1, s3);
    lw(a1, s2, adxsjd::kDecByte);
    sw(v1, s2, adxsjd::kDecSmpl);
    lw(a3, s2, adxsjd::kDecSmplTotal);
    a1 = addu(a1, v0);
    lw(v1, sp, 0x20);
    lw(a2, s2, adxsjd::kTrapCnt);
    a3 = addu(a3, s3);
    lw(v0, s2, adxsjd::kTrapByte);
    a2 = addu(a2, s3);
    sw(a1, s2, adxsjd::kDecByte);
    v0 = addu(v0, v1);
    sw(a3, s2, adxsjd::kDecSmplTotal);
    sw(v0, s2, adxsjd::kTrapByte);
    link(ctx, 0x542A4Cu);  // $ra first: the delay slot below depends on it
    sw(a2, s2, adxsjd::kTrapCnt);
    call(ctx, gen::fn_sub_5383A8_005383a8);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(s6, sp, 0x60);
    ld(s7, sp, 0x68);
    ld(fp, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

// 0x00542B18 sub_542B18 -- 176 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// one decode step (exec ADXB, then collect; the AHX / WAV kinds finish in sub_542A88). [adxsjd_ExecDecode]
void sub_542B18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00542b18
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    lw(s0, s1, adxsjd::kAdxb);
    a0 = s0;
    jal(ctx, 0x542B30u, gen::fn_sub_5382C0_005382c0);
    if (v0 == 0) {
        // 0x00542b40
        charge(ctx, 2);
        a0 = s1;
        jal(ctx, 0x542B40u, gen::fn_sub_542558_00542558);
    }
    // 0x00542b48
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x542B48u, gen::fn_sub_5389B0_005389b0);
    a0 = s0;
    jal(ctx, 0x542B50u, gen::fn_sub_5382C0_005382c0);
    v1 = 3;
    if (v0 != v1) {
        lh(a0, s0, 152);
    } else {
        // 0x00542b64
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x542B64u, gen::fn_sub_5428C0_005428c0);
        lh(a0, s0, 152);
    }
    // 0x00542b70
    charge(ctx, 3);
    v0 = 10;
    cc = a0 == v0;  // the condition, before the delay slot changes it
    v0 = 20;
    if (!cc) {
        // 0x00542b7c
        charge(ctx, 2);
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 11;
        if (cc) {
            goto L_00542b9c;
        }
        // 0x00542b84
        charge(ctx, 2);
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 12;
        if (cc) {
            goto L_00542b9c;
        }
        // 0x00542b8c
        charge(ctx, 2);
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 15;
        if (cc) {
            goto L_00542b9c;
        }
        // 0x00542b94
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (a0 == v0) {
            goto L_00542b9c;
        }
        // 0x00542bb8
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00542b9c:
    charge(ctx, 6);
    a0 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_542A88_00542a88(ctx);  // tail call
}

// 0x00542BC8 sub_542BC8 -- 164 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// run one decoder handle (pending work under the SVM lock, header or decode stage). [ADXSJD_ExecHndl]
void sub_542BC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542bc8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, adxsjd::kPend0);
    if (i64(v0) <= 0) {
        lb(v1, s0, adxsjd::kStat);
    } else {
        // 0x00542be4
        charge(ctx, 7);
        jal(ctx, 0x542BE4u, gen::fn_sub_539818_00539818);
        a0 = s0;
        jal(ctx, 0x542BECu, gen::fn_sub_542C70_00542c70);
        jal(ctx, 0x542BF4u, gen::fn_sub_539830_00539830);
        lb(v1, s0, adxsjd::kStat);
    }
    // 0x00542c00
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        v0 = 1;
        // 0x00542c20
        charge(ctx, 2);
        if (v1 != v0) {
            lw(v0, s0, adxsjd::kPend1);
        } else {
            // 0x00542c28
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x542C28u, gen::fn_sub_542130_00542130);
            lw(v0, s0, adxsjd::kPend1);
        }
    } else {
        // 0x00542c0c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x542C0Cu, gen::fn_sub_542B18_00542b18);
        lw(v0, s0, adxsjd::kPend1);
    }
    // 0x00542c34
    charge(ctx, 2);
    if (i64(v0) <= 0) {
        ld(s0, sp, 0x0);
        // 0x00542c60
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00542c3c
    charge(ctx, 8);
    jal(ctx, 0x542C3Cu, gen::fn_sub_539818_00539818);
    a0 = s0;
    jal(ctx, 0x542C44u, gen::fn_sub_542DC0_00542dc0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00542F00 sub_542F00 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// run every used decoder handle. [ADXSJD_ExecServer]
void sub_542F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542f00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x790000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -104);  // &0x78FF98
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00542f28
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00542f34
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x542F34u, gen::fn_sub_542BC8_00542bc8);
            s1 = addiu(s1, -1);
        }
        // 0x00542f40
        charge(ctx, 2);
        s0 = addiu(s0, 168);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00542f48
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00542F60 sub_542F60 -- 8 bytes; leaf frame (no stack)
// input bytes consumed. [ADXSJD_GetDecDtLen]
void sub_542F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00542f60
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxsjd::kDecByte);
}

// 0x00542F68 sub_542F68 -- 8 bytes; leaf frame (no stack)
// samples decoded. [ADXSJD_GetDecNumSmpl]
void sub_542F68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00542f68
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxsjd::kDecSmpl);
}

// 0x00542F88 sub_542F88 -- 8 bytes; leaf frame (no stack)
// set the decoded-samples total (+52). [ADXSJD_SetDecNumSmpl]
void sub_542F88(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00542f88
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, adxsjd::kDecSmplTotal);
}

// 0x005430A8 sub_5430A8 -- 12 bytes; leaf frame (no stack)
// set the trap callback and its object. [ADXSJD_EntryTrapFunc]
void sub_5430A8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005430a8
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, adxsjd::kTrapObj);
    sw(a1, a0, adxsjd::kTrapFn);
}

// 0x005430B8 sub_5430B8 -- 8 bytes; leaf frame (no stack)
// set the trap sample. [ADXSJD_SetTrapNumSmpl]
void sub_5430B8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x005430b8
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, adxsjd::kTrapSmp);
}

// 0x005430C8 sub_5430C8 -- 8 bytes; leaf frame (no stack)
// set the trap count. [ADXSJD_SetTrapCnt]
void sub_5430C8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x005430c8
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, adxsjd::kTrapCnt);
}

// 0x005430D8 sub_5430D8 -- 8 bytes; leaf frame (no stack)
// set the trap byte count. [ADXSJD_SetTrapDtLen]
void sub_5430D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x005430d8
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, adxsjd::kTrapByte);
}

// 0x005430E8 sub_5430E8 -- 24 bytes; frame 0x10: ra sp+0x0
// the ADXB decoder's format. [ADXSJD_GetFormat]
void sub_5430E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005430e8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537F30_00537f30(ctx);  // tail call
}

// 0x00543100 sub_543100 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// the sample rate. [ADXSJD_GetSfreq]
void sub_543100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543100
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00537f38
    charge(ctx, 2);
    lw(v0, a0, adxsjd::kInChunk);
}

// 0x00543118 sub_543118 -- 24 bytes; frame 0x10: ra sp+0x0
// the channel count. [ADXSJD_GetNumChan]
void sub_543118(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543118
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537F40_00537f40(ctx);  // tail call
}

// 0x00543130 sub_543130 -- 120 bytes, 2 chunks; frame 0x10: ra sp+0x0
// bits per sample for the time functions: 16, or 4 / 8 for the AHX kinds. [ADXSJD_GetOutBps]
void sub_543130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00543130
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00537f78
    charge(ctx, 3);
    lh(a1, a0, 152);
    v0 = 16;
    if (a1 == 0) {
        // 0x00537fd0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00537f84
    charge(ctx, 3);
    v0 = 2;
    cc = a1 != v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (cc) {
        // 0x00537fb0
        charge(ctx, 2);
        if (a1 != v0) {
            v0 = 16;
            // 0x00537fd0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x00537fb8
        charge(ctx, 6);
        lh(v1, a0, 156);
        a0 = 16;
        v0 = 4;
        v1 = v1 ^ 0x2;
        if (v1 != 0) v0 = a0;
        return;
    }
    // 0x00537f90
    charge(ctx, 4);
    lh(v1, a0, 156);
    v0 = 4;
    a0 = v1 ^ 0x1;
    if (v1 == a1) {
        // 0x00537fd0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00537fa0
    charge(ctx, 4);
    v1 = 16;
    v0 = 8;
    if (a0 != 0) v0 = v1;
}

// 0x00543148 sub_543148 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// samples per block. [ADXSJD_GetBlkSmpl]
void sub_543148(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543148
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00537fd8
    charge(ctx, 2);
    lw(v0, a0, 16);
}

// 0x00543178 sub_543178 -- 24 bytes; frame 0x10: ra sp+0x0
// the total samples of the stream. [ADXSJD_GetTotalNumSmpl]
void sub_543178(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543178
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_width__CQ24_STL8ios_base_00537fe8(ctx);  // tail call
}

// 0x005431A8 sub_5431A8 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// the loop type (> 0 = looped). [ADXSJD_GetLpInsNsmpl]
void sub_5431A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005431a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00538000
    charge(ctx, 2);
    lh(v0, a0, 36);
}

// 0x005431D8 sub_5431D8 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// the loop start sample. [ADXSJD_GetLpStartPos]
void sub_5431D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005431d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00538008
    charge(ctx, 2);
    lw(v0, a0, 40);
}

// 0x005431F0 sub_5431F0 -- 64 bytes, 2 chunks; frame 0x10: ra sp+0x0
// the loop start offset (0 for a null handle or decoder). [ADXSJD_GetLpStartOfst]
void sub_5431F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005431f0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00543210
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00543200
    charge(ctx, 4);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00538010
    charge(ctx, 2);
    v0 = 0;
    if (a0 != 0) {
        // 0x00538018
        charge(ctx, 1);
        lw(v0, a0, adxsjd::kDecSmpl);
    }
    // 0x0053801c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00543220 sub_543220 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// the loop end sample. [ADXSJD_GetLpEndPos]
void sub_543220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543220
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00538028
    charge(ctx, 2);
    lw(v0, a0, adxsjd::kDecByte);
}

// 0x00543238 sub_543238 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// the loop end offset. [ADXSJD_GetLpEndOfst]
void sub_543238(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543238
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00538030
    charge(ctx, 2);
    lw(v0, a0, adxsjd::kDecSmplTotal);
}

// 0x00543268 sub_543268 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the header's volume while decoding (0 otherwise). [ADXSJD_GetDefOutVol]
void sub_543268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00543268
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x543278u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxsjd::kAdxb);
    call(ctx, gen::fn_sub_538038_00538038);
    cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00543288
        charge(ctx, 5);
        lbu(v0, s0, adxsjd::kStat);
        v0 = addiu(v0, -2);
        v0 = sltiu(v0, 2);
        if (v0 == 0) {
            v0 = 0;
            goto L_005432b0;
        }
        // 0x0054329c
        charge(ctx, 4);
        link(ctx, 0x54329Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxsjd::kAdxb);
        call(ctx, gen::fn_sub_538040_00538040);
        ld(s0, sp, 0x0);
        // 0x005432b4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_005432b0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005432b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005432C0 sub_5432C0 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// the header's pan of a channel while decoding (-128 otherwise). [ADXSJD_GetDefPan]
void sub_5432C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005432c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    link(ctx, 0x5432D8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxsjd::kAdxb);
    call(ctx, gen::fn_sub_538038_00538038);
    cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
    v0 = si(-128);
    if (!cc) {
        // 0x005432e8
        charge(ctx, 5);
        lbu(v0, s0, adxsjd::kStat);
        v0 = addiu(v0, -2);
        v0 = sltiu(v0, 2);
        if (v0 == 0) {
            v0 = si(-128);
            goto L_00543310;
        }
        // 0x005432fc
        charge(ctx, 5);
        lw(a0, s0, adxsjd::kAdxb);
        a1 = s1;
        jal(ctx, 0x543300u, gen::fn_sub_538048_00538048);
        ld(s0, sp, 0x0);
        // 0x00543314 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00543310:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00543314 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005433A8 sub_5433A8 -- 24 bytes; frame 0x10: ra sp+0x0
// seek the ADXB decoder to the loop start. [ADXSJD_SetLpStart]
void sub_5433A8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005433a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxsjd::kAdxb);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_538060_00538060(ctx);  // tail call
}

}  // namespace p3fes::game
