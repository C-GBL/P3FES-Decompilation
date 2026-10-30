// Phase 5 slice libs23: the leftover CRI Sofdec entry points 0x58C138-0x5A1518 (no callers in the game). Every body
// is p3fes_handgen's, register for register and block for block as the recompiled body (frame, spills, $ra links,
// cycle charges and check points: game/include/p3fes/game/hg_cpu.h), with the records' offsets named (libs23.h, and
// tail1.h / libs5.h / libs13.h for the SFD handle) and the error codes written out. The full role of each function is
// on its declaration in libs23.h; the line above each body is the short form.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs23.h"

namespace p3fes::recomp_gen {
void fn_WTLS_set_table_2_0059fd70(p3fes::EEContext&);
void fn___errno_14_0059fd80(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nullsub_177_00595bb8(p3fes::EEContext&);
void fn_r_lock_def_free_7_0058ea40(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_5793E8_005793e8(p3fes::EEContext&);
void fn_sub_57B418_0057b418(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_588F48_00588f48(p3fes::EEContext&);
void fn_sub_589D10_00589d10(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C138_0058c138(p3fes::EEContext&);
void fn_sub_58C178_0058c178(p3fes::EEContext&);
void fn_sub_58C180_0058c180(p3fes::EEContext&);
void fn_sub_58C188_0058c188(p3fes::EEContext&);
void fn_sub_58C190_0058c190(p3fes::EEContext&);
void fn_sub_58E260_0058e260(p3fes::EEContext&);
void fn_sub_58E400_0058e400(p3fes::EEContext&);
void fn_sub_58E758_0058e758(p3fes::EEContext&);
void fn_sub_5930E0_005930e0(p3fes::EEContext&);
void fn_sub_5930E8_005930e8(p3fes::EEContext&);
void fn_sub_5930F0_005930f0(p3fes::EEContext&);
void fn_sub_5930F8_005930f8(p3fes::EEContext&);
void fn_sub_593100_00593100(p3fes::EEContext&);
void fn_sub_593120_00593120(p3fes::EEContext&);
void fn_sub_593598_00593598(p3fes::EEContext&);
void fn_sub_593608_00593608(p3fes::EEContext&);
void fn_sub_593730_00593730(p3fes::EEContext&);
void fn_sub_5937D0_005937d0(p3fes::EEContext&);
void fn_sub_593878_00593878(p3fes::EEContext&);
void fn_sub_594BD0_00594bd0(p3fes::EEContext&);
void fn_sub_595770_00595770(p3fes::EEContext&);
void fn_sub_595780_00595780(p3fes::EEContext&);
void fn_sub_5959D0_005959d0(p3fes::EEContext&);
void fn_sub_595CB8_00595cb8(p3fes::EEContext&);
void fn_sub_595D10_00595d10(p3fes::EEContext&);
void fn_sub_596B68_00596b68(p3fes::EEContext&);
void fn_sub_5973C0_005973c0(p3fes::EEContext&);
void fn_sub_5979F8_005979f8(p3fes::EEContext&);
void fn_sub_598300_00598300(p3fes::EEContext&);
void fn_sub_598348_00598348(p3fes::EEContext&);
void fn_sub_5984C8_005984c8(p3fes::EEContext&);
void fn_sub_598528_00598528(p3fes::EEContext&);
void fn_sub_598588_00598588(p3fes::EEContext&);
void fn_sub_5985F8_005985f8(p3fes::EEContext&);
void fn_sub_598910_00598910(p3fes::EEContext&);
void fn_sub_598980_00598980(p3fes::EEContext&);
void fn_sub_5989F0_005989f0(p3fes::EEContext&);
void fn_sub_598A90_00598a90(p3fes::EEContext&);
void fn_sub_598AE8_00598ae8(p3fes::EEContext&);
void fn_sub_598B90_00598b90(p3fes::EEContext&);
void fn_sub_598C28_00598c28(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599760_00599760(p3fes::EEContext&);
void fn_sub_59A0D8_0059a0d8(p3fes::EEContext&);
void fn_sub_59A150_0059a150(p3fes::EEContext&);
void fn_sub_59A188_0059a188(p3fes::EEContext&);
void fn_sub_59A200_0059a200(p3fes::EEContext&);
void fn_sub_59A4A8_0059a4a8(p3fes::EEContext&);
void fn_sub_59A910_0059a910(p3fes::EEContext&);
void fn_sub_59A9A0_0059a9a0(p3fes::EEContext&);
void fn_sub_59AA48_0059aa48(p3fes::EEContext&);
void fn_sub_59ADF8_0059adf8(p3fes::EEContext&);
void fn_sub_59AEF8_0059aef8(p3fes::EEContext&);
void fn_sub_59AF80_0059af80(p3fes::EEContext&);
void fn_sub_59B048_0059b048(p3fes::EEContext&);
void fn_sub_59BB88_0059bb88(p3fes::EEContext&);
void fn_sub_59C468_0059c468(p3fes::EEContext&);
void fn_sub_59C7B8_0059c7b8(p3fes::EEContext&);
void fn_sub_59C9F8_0059c9f8(p3fes::EEContext&);
void fn_sub_59CC30_0059cc30(p3fes::EEContext&);
void fn_sub_59CC50_0059cc50(p3fes::EEContext&);
void fn_sub_59CD00_0059cd00(p3fes::EEContext&);
void fn_sub_59CEC8_0059cec8(p3fes::EEContext&);
void fn_sub_59CED0_0059ced0(p3fes::EEContext&);
void fn_sub_59CED8_0059ced8(p3fes::EEContext&);
void fn_sub_59CEE0_0059cee0(p3fes::EEContext&);
void fn_sub_59CEE8_0059cee8(p3fes::EEContext&);
void fn_sub_59CF08_0059cf08(p3fes::EEContext&);
void fn_sub_59EAA8_0059eaa8(p3fes::EEContext&);
void fn_sub_59EAD0_0059ead0(p3fes::EEContext&);
void fn_sub_59FDA0_0059fda0(p3fes::EEContext&);
void fn_sub_59FE58_0059fe58(p3fes::EEContext&);
void fn_sub_5A0050_005a0050(p3fes::EEContext&);
void fn_sub_5A00B0_005a00b0(p3fes::EEContext&);
void fn_sub_5A00D8_005a00d8(p3fes::EEContext&);
void fn_sub_5A04C0_005a04c0(p3fes::EEContext&);
void fn_sub_5A10F8_005a10f8(p3fes::EEContext&);
void fn_sub_5A1188_005a1188(p3fes::EEContext&);
void fn_sub_5A1218_005a1218(p3fes::EEContext&);
void fn_sub_5A12F8_005a12f8(p3fes::EEContext&);
void fn_sub_5A13C0_005a13c0(p3fes::EEContext&);
void fn_sub_5A1420_005a1420(p3fes::EEContext&);
void fn_sub_5A14B0_005a14b0(p3fes::EEContext&);
void fn_sub_5A1518_005a1518(p3fes::EEContext&);
void fn_sub_5A1778_005a1778(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

namespace {
constexpr s32 kVdecWork = libs13::sfd::kVdecWork;  // u32: the handle's video-decoder work
constexpr s32 kHdrObj = libs13::sfd::kHdrObj;      // u32: the handle's header object
}  // namespace

// 0x0058C138 sub_58C138 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_58C138(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c138
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C178 sub_58C178 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_58C178(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c178
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C180 sub_58C180 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_58C180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c180
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C188 sub_58C188 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_58C188(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c188
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C190 sub_58C190 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_58C190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c190
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058E260 sub_58E260 -- 172 bytes; frame 0x10: ra sp+0x0
// Keeps a copy of a frame-buffer configuration (64-aligned) and clears the two areas after it.
void sub_58E260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e260
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0x9B0000;
    sd(ra, sp, 0x0);
    a3 = addiu(a3, -13584);  // &0x9ACAF0
    v0 = 0x9B0000;
    t0 = si(-64);  // ~63: rounds up to 64
    ldl(v1, a0, 7);
    ldr(v1, a0, 0);
    ldl(a1, a0, 15);
    ldr(a1, a0, 8);
    ldl(a2, a0, 23);
    ldr(a2, a0, 16);
    ldl(t1, a0, 31);
    ldr(t1, a0, 24);
    sdl(v1, a3, 7);  // 0x9ACAF7
    sdr(v1, a3, 0);  // 0x9ACAF0
    sdl(a1, a3, 15);  // 0x9ACAFF
    sdr(a1, a3, 8);  // 0x9ACAF8
    sdl(a2, a3, 23);  // 0x9ACB07
    sdr(a2, a3, 16);  // 0x9ACB00
    sdl(t1, a3, 31);  // 0x9ACB0F
    sdr(t1, a3, 24);  // 0x9ACB08
    lw(v1, a0, 32);
    sw(v1, a3, 32);  // 0x9ACB10
    a0 = addiu(v0, -13544);  // &0x9ACB18
    a1 = 0;
    a2 = 8;
    lw(v0, a3, libs23::fbcfg::kSize16);  // 0x9ACB00
    lw(v1, a3, libs23::fbcfg::kBase);  // 0x9ACB10
    v0 = addiu(v0, 63);
    v1 = addiu(v1, 63);
    v0 = v0 & t0;
    v1 = v1 & t0;
    sw(v0, a3, libs23::fbcfg::kSize16);  // 0x9ACB00
    link(ctx, 0x58E2E8u);  // $ra first: the delay slot below depends on it
    sw(v1, a3, libs23::fbcfg::kBase);  // 0x9ACB10
    call(ctx, gen::fn_memset_00521408);
    a0 = 0x9B0000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, -13536);  // &0x9ACB20
    a2 = 64;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0058E400 sub_58E400 -- 156 bytes; leaf frame (no stack)
// Frame-buffer plane layout from a configuration (macroblock rows and 64-byte pitches).
void sub_58E400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0058e400
    enter(ctx, 39);  // entry check point + this block's cycles
    lw(v1, a0, libs23::fbcfg::kWidth);
    lw(t2, a0, libs23::fbcfg::kHeight);
    v0 = addiu(v1, 15);
    v1 = addiu(v1, 30);
    a2 = slti(v0, 0);
    t1 = addiu(t2, 15);
    if (a2 != 0) v0 = v1;
    t3 = slti(t1, 0);
    v0 = sra(v0, 4);
    t2 = addiu(t2, 30);
    t0 = sll(v0, 4);
    v0 = sll(v0, 3);
    a3 = addiu(t0, 63);
    t0 = addiu(t0, 126);
    a2 = addiu(v0, 63);
    v0 = addiu(v0, 126);
    v1 = slti(a3, 0);
    if (t3 != 0) t1 = t2;
    if (v1 != 0) a3 = t0;
    v1 = slti(a2, 0);
    if (v1 != 0) a2 = v0;
    lw(v1, a0, libs23::fbcfg::kBase);
    a3 = sra(a3, 6);
    t1 = sra(t1, 4);
    mult(v0, a3, t1);
    a3 = sll(a3, 6);
    a2 = sra(a2, 6);
    sh(a3, a1, 14);
    mult1(t1, a2, t1);
    a2 = sll(a2, 6);
    sh(a2, a1, 12);
    v0 = sll(v0, 10);
    sw(v1, a1, 8);
    v0 = addu(v1, v0);
    t1 = sll(t1, 9);
    sw(v0, a1, 0);
    t1 = addu(v0, t1);
    sw(t1, a1, 4);
}

// 0x0058E758 sub_58E758 -- 164 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Handle check, then sub_5793E8 on the video decoder's MPV handle.
void sub_58E758(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e758
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = t0;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = a1;
    jal(ctx, 0x58E784u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a2 = s0;
    a3 = s1;
    t0 = s2;
    a0 = 0;
    a1 = a1 | 0x184;  // error 0xFF000184
    if (v0 != 0) {
        // 0x0058e7a8
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058e7c8
    charge(ctx, 13);
    lw(v0, s3, kVdecWork);
    a1 = s4;
    link(ctx, 0x58E7D0u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, libs13::vdec::kMpv);
    call(ctx, gen::fn_sub_5793E8_005793e8);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058EA40 r_lock_def_free_7 -- 32 bytes; frame 0x10: ra sp+0x0
// mpvFinish, returning 0.
void r_lock_def_free_7(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ea40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x58EA48u, gen::fn_sub_57B418_0057b418);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x005930E0 sub_5930E0 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_5930E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005930e0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005930E8 sub_5930E8 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_5930E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005930e8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005930F0 sub_5930F0 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_5930F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005930f0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005930F8 sub_5930F8 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_5930F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005930f8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00593100 sub_593100 -- 28 bytes; frame 0x10: ra sp+0x0
// "Unsupported" (0xFF000F0D).
void sub_593100(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593100
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xF0D;  // error 0xFF000F0D
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00593120 sub_593120 -- 28 bytes; frame 0x10: ra sp+0x0
// "Unsupported" (0xFF000F0D).
void sub_593120(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593120
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xF0D;  // error 0xFF000F0D
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00593598 sub_593598 -- 112 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Video decoder setup step: skip mode 2 and the +120 size (200 / 192).
void sub_593598(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593598
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    a2 = sp;
    sd(ra, sp, 0x20);
    lw(s0, s1, kVdecWork);
    a1 = s0;
    jal(ctx, 0x5935B4u, gen::fn_sub_593608_00593608);
    if (v0 != 0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x005935c4
        charge(ctx, 4);
        lw(v1, sp, 0x0);
        v0 = 2;
        sw(v0, s0, libs13::vdec::kSkipMode);
        if (v1 != 0) {
            // 0x005935d4
            charge(ctx, 5);
            a0 = s1;
            a1 = 48;  // parameter 48
            jal(ctx, 0x5935D8u, gen::fn_sub_599408_00599408);
            if (v0 == 0) {
                goto L_005935e8;
            }
            v0 = 200;
            goto L_005935ec;
        }
    L_005935e8:
        charge(ctx, 1);
        v0 = 192;
    L_005935ec:
        charge(ctx, 3);
        sw(v0, s0, 120);
        v0 = 0;
        ld(s0, sp, 0x10);
    }
    // 0x005935f8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00593730 sub_593730 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Locks a frame (by its output record) and counts the handle's lock total.
void sub_593730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x593744u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00593758
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x188;  // error 0xFF000188
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00593770
    charge(ctx, 7);
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x593774u, gen::fn_sub_593878_00593878);
    v1 = v0;
    a1 = lui(0xFF00);
    a0 = s0;
    if (v1 != 0) {
        // 0x005937a0
        charge(ctx, 4);
        lw(v0, v1, libs23::kFrmLocks);
        v0 = addiu(v0, 1);
        sw(v0, v1, libs23::kFrmLocks);
        lw(v0, s0, libs23::sfd::kFrameLocks);
    } else {
        // 0x0059378c
        charge(ctx, 4);
        a1 = a1 | 0xF30;  // error 0xFF000F30
        jal(ctx, 0x59378Cu, gen::fn_sub_58BE40_0058be40);
        lw(v0, s0, libs23::sfd::kFrameLocks);
    }
    // 0x005937b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x10);
    sw(v0, s0, libs23::sfd::kFrameLocks);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x005937D0 sub_5937D0 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Unlocks a frame (by its output record) and takes one from the handle's lock total.
void sub_5937D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005937d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5937E4u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x005937f8
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x189;  // error 0xFF000189
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00593810
    charge(ctx, 7);
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x593814u, gen::fn_sub_593878_00593878);
    a2 = v0;
    a1 = lui(0xFF00);
    a0 = s0;
    if (a2 != 0) {
        // 0x00593840
        charge(ctx, 6);
        lw(v0, a2, libs23::kFrmLocks);
        v0 = addiu(v0, -1);
        v1 = slti(v0, 0);
        if (v1 != 0) v0 = 0;
        sw(v0, a2, libs23::kFrmLocks);
        lw(v0, s0, libs23::sfd::kFrameLocks);
    } else {
        // 0x0059382c
        charge(ctx, 4);
        a1 = a1 | 0xF31;  // error 0xFF000F31
        jal(ctx, 0x59382Cu, gen::fn_sub_58BE40_0058be40);
        lw(v0, s0, libs23::sfd::kFrameLocks);
    }
    // 0x00593858 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    v0 = addiu(v0, -1);
    ld(ra, sp, 0x10);
    sw(v0, s0, libs23::sfd::kFrameLocks);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00594BD0 sub_594BD0 -- 100 bytes; leaf frame (no stack)
// The video-input ring's size and positions in bytes.
void sub_594BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00594bd0
    enter(ctx, 16);  // entry check point + this block's cycles
    lw(t1, a0, kVdecWork);
    t1 = addiu(t1, libs13::vdec::kViBuf);  // the video-input ring
    lw(v1, t1, libs13::vibuf::kBytes);
    sw(v1, a1, 0);
    lw(v0, t1, 12);
    v0 = sll(v0, 11);
    sw(v0, a3, 0);
    lw(a0, t1, 16);
    lw(v1, t1, 12);
    lw(a1, t1, libs13::vibuf::kCount);
    v1 = addu(v1, a0);
    lw(v0, t1, libs13::vibuf::kBytes);
    v1 = sll(v1, 11);
    v1 = addu(v1, a1);
    if (v0 == 0) {
        brk(ctx, 0x594C0Cu, 0x7u);
    }
    // 0x00594c10
    charge(ctx, 9);
    div(v1, v0);
    mfhi(a0);
    sw(a0, a2, 0);
    lw(v0, t1, 16);
    lw(v1, t1, libs13::vibuf::kCount);
    v0 = sll(v0, 11);
    v0 = addu(v0, v1);
    sw(v0, t0, 0);
}

// 0x00595770 sub_595770 -- 12 bytes; leaf frame (no stack)
// The video decoder's sceMpeg record.
void sub_595770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00595770
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, kVdecWork);
    v0 = addiu(v0, libs13::vdec::kMpeg);
}

// 0x00595780 sub_595780 -- 8 bytes; leaf frame (no stack)
// The sceMpeg record's size (72).
void sub_595780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00595780
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 72;  // sizeof the sceMpeg record
}

// 0x00595BB8 nullsub_177 -- 8 bytes; leaf frame (no stack)
// Empty.
void nullsub_177(EEContext& ctx) {
    using namespace hg;
    // 0x00595bb8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00595CB8 sub_595CB8 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0, s1 sp+0x8
// SFD server sweep over the 8-handle table.
void sub_595CB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00595cb8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7B0000;
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 18292);  // &0x7B4774 (tail1::sfd::kHandles)
    sd(s1, sp, 0x8);
    s1 = 7;  // kHandleCount - 1
    for (;;) {
        // 0x00595cd8
        charge(ctx, 4);
        link(ctx, 0x595CD8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_58C060_0058c060);
        if (v0 != 0) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00595ce8
            charge(ctx, 3);
            link(ctx, 0x595CE8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_595D10_00595d10);
            s1 = addiu(s1, -1);
        }
        // 0x00595cf4
        charge(ctx, 2);
        s0 = addiu(s0, 4);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00595cfc
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_596B68_00596b68(ctx);  // tail call
}

// 0x005979F8 sub_5979F8 -- 32 bytes; frame 0x10: ra sp+0x0
// Whether transfer slot 0's stream has ended.
void sub_5979F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005979f8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x597A00u);  // $ra first: the delay slot below depends on it
    lw(a1, a0, libs5::sfdh::kTrn0Stream);
    call(ctx, gen::fn_sub_589D10_00589d10);
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x00598300 sub_598300 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Initialises n 3,544-byte records.
void sub_598300(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598300
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (i64(a1) > 0) {
        // 0x00598314
        charge(ctx, 3);
        s1 = a0;
        s0 = a1;
        a0 = s1;
        for (;;) {
            // 0x00598320
            charge(ctx, 5);
            s1 = addiu(s1, libs23::sfd::kRec3544);
            s0 = addiu(s0, -1);
            jal(ctx, 0x598324u, gen::fn_sub_598348_00598348);
            a0 = s1;
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00598334 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005984C8 sub_5984C8 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check; header object +3520 = $a1.
void sub_5984C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005984c8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5984DCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 == 0) {
        // 0x00598508
        charge(ctx, 7);
        lw(v1, s0, kHdrObj);
        ld(s0, sp, 0x0);
        sw(s1, v1, libs23::hdr::kUserWord);
        ld(ra, sp, 0x10);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005984f0
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = a1 | 0x152;  // error 0xFF000152
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00598528 sub_598528 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle check; parameter 47 = 1 and the stop request.
void sub_598528(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598528
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x598534u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a2 = 1;
    a1 = a1 | 0x153;  // error 0xFF000153
    if (v0 != 0) {
        // 0x00598550
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598568
    charge(ctx, 7);
    a1 = 47;  // parameter 47 = $a2 (1)
    jal(ctx, 0x598568u, gen::fn_sub_599240_00599240);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5959D0_005959d0(ctx);  // tail call
}

// 0x00598588 sub_598588 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Header-object query through sub_5985F8.
void sub_598588(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598588
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    link(ctx, 0x5985A0u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x005985b4
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x154;  // error 0xFF000154
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005985d0
    charge(ctx, 9);
    lw(a0, s1, kHdrObj);
    a1 = s0;
    jal(ctx, 0x5985D4u, gen::fn_sub_5985F8_005985f8);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00598910 sub_598910 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Header-object query through sub_598980.
void sub_598910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598910
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    link(ctx, 0x598928u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0059893c
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x155;  // error 0xFF000155
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598958
    charge(ctx, 9);
    lw(a0, s1, kHdrObj);
    a1 = s0;
    jal(ctx, 0x59895Cu, gen::fn_sub_598980_00598980);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005989F0 sub_5989F0 -- 160 bytes; frame 0x40: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// Header-object query through sub_598980 / sub_598A90.
void sub_5989F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005989f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = a0;
    sd(s1, sp, 0x18);
    s1 = a3;
    sd(s0, sp, 0x10);
    s0 = addiu(v0, kHdrObj);  // &the header object
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(ra, sp, 0x30);
    link(ctx, 0x598A1Cu);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    a1 = sp;
    if (v0 == 0) {
        // 0x00598a48
        charge(ctx, 8);
        link(ctx, 0x598A48u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_598980_00598980);
        a1 = s2;
        lw(v1, sp, 0x0);
        a2 = s3;
        a3 = s1;
        v0 = 0;
        if (v1 != 0) {
            // 0x00598a68
            charge(ctx, 3);
            link(ctx, 0x598A68u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_598A90_00598a90);
            v0 = 0;
        }
        // 0x00598a74
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x00598a30
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x156;  // error 0xFF000156
        jal(ctx, 0x598A34u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
    }
    // 0x00598a78 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00598AE8 sub_598AE8 -- 168 bytes; frame 0x40: s2 sp+0x20, s3 sp+0x28, s0 sp+0x10, s1 sp+0x18, ra sp+0x30
// Header-object query through sub_598980 / sub_598B90.
void sub_598AE8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598ae8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 1;
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s3, sp, 0x28);
    s3 = a3;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(ra, sp, 0x30);
    sw(zero, s2, 0);
    sw(v0, s3, 0);
    v0 = a0;
    s0 = addiu(v0, kHdrObj);  // &the header object
    jal(ctx, 0x598B1Cu, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    a1 = sp;
    if (v0 == 0) {
        // 0x00598b48
        charge(ctx, 8);
        link(ctx, 0x598B48u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_598980_00598980);
        a1 = s1;
        lw(v1, sp, 0x0);
        a2 = s2;
        a3 = s3;
        v0 = 0;
        if (v1 != 0) {
            // 0x00598b68
            charge(ctx, 3);
            link(ctx, 0x598B68u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_598B90_00598b90);
            v0 = 0;
        }
        // 0x00598b74
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x00598b30
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x157;  // error 0xFF000157
        jal(ctx, 0x598B34u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
    }
    // 0x00598b78 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00598C28 sub_598C28 -- 248 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Restart with a header object: stop, parameters 47 / 5 / 6, the 12-byte record, transfer method 13.
void sub_598C28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00598c28
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x598C40u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00598c54
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x158;  // error 0xFF000158
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00598c70
    charge(ctx, 3);
    lw(s1, s0, kHdrObj);
    if (s1 == 0) {
        ld(s0, sp, 0x0);
        // 0x00598d0c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00598c7c
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x598C7Cu, gen::fn_sub_5973C0_005973c0);
    a0 = s0;
    a1 = 47;
    a2 = 0;
    if (v0 != 0) {
        // 0x00598d08
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00598d0c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00598c94
    charge(ctx, 7);
    jal(ctx, 0x598C94u, gen::fn_sub_599240_00599240);
    a0 = s0;
    lw(v0, s1, libs23::hdr::kNoParam5);
    a1 = 5;
    a2 = 0;
    if (v0 == 0) {
        // 0x00598cb0
        charge(ctx, 2);
        jal(ctx, 0x598CB0u, gen::fn_sub_599240_00599240);
    }
    // 0x00598cb8
    charge(ctx, 3);
    lw(v0, s1, libs23::hdr::kNoParam6);
    a0 = s0;
    if (v0 == 0) {
        // 0x00598cc4
        charge(ctx, 3);
        a1 = 6;
        a2 = 0;
        jal(ctx, 0x598CC8u, gen::fn_sub_599240_00599240);
    }
    // 0x00598cd0
    charge(ctx, 14);
    ldl(v0, s2, 7);
    ldr(v0, s2, 0);
    lw(v1, s2, 8);
    sdl(v0, s0, libs23::kStartRec + 7);
    sdr(v0, s0, libs23::kStartRec);
    sw(v1, s0, libs23::kStartRecW2);
    a0 = s0;
    ld(s1, sp, 0x8);
    a1 = 13;  // transfer method 13
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BB88_0059bb88(ctx);  // tail call
}

// 0x00599760 sub_599760 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// The header-sector copy and its size.
void sub_599760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00599760
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x59977Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x11C;  // error 0xFF00011C
    if (v0 != 0) {
        // 0x00599794
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005997b0
    charge(ctx, 3);
    lw(v0, s0, tail1::sfd::kHandleInfo);  // sfdinfo::kValid
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = addiu(s0, tail1::sfd::kHandleInfo + tail1::sfdinfo::kHdrCopy);
    if (cc) {
        // 0x005997d0
        charge(ctx, 2);
        sw(zero, s1, 0);
        sw(zero, s2, 0);
    } else {
        // 0x005997bc
        charge(ctx, 4);
        lw(v1, s0, tail1::sfd::kHandleInfo + tail1::sfdinfo::kHdrSize);
        sw(v0, s1, 0);
        sw(v1, s2, 0);
    }
    // 0x005997d8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059A0D8 sub_59A0D8 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Handle check, then the time (sub_59A150).
void sub_59A0D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a0d8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x59A0F4u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a2 = s1;
    a1 = a1 | 0x127;  // error 0xFF000127
    if (v0 == 0) {
        // 0x0059a130
        charge(ctx, 7);
        a1 = s2;
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59A150_0059a150(ctx);  // tail call
        return;
    }
    // 0x0059a110
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059A188 sub_59A188 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Handle check, then the time through the time source (sub_59A200).
void sub_59A188(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a188
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x59A1A4u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a2 = s1;
    a1 = a1 | 0x128;  // error 0xFF000128
    if (v0 == 0) {
        // 0x0059a1e0
        charge(ctx, 7);
        a1 = s2;
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59A200_0059a200(ctx);  // tail call
        return;
    }
    // 0x0059a1c0
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059A4A8 sub_59A4A8 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Counts a time tick and marks the time updated.
void sub_59A4A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a4a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x59A4B4u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a2 = addiu(s0, libs5::sfdh::kTimeRec);
    a0 = 0;
    a1 = a1 | 0x122;  // error 0xFF000122
    if (v0 != 0) {
        // 0x0059a4d0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059a4e0
    charge(ctx, 9);
    lw(v1, a2, libs23::sfd::kTimeTick);
    a0 = 1;
    ld(ra, sp, 0x8);
    v1 = addiu(v1, 1);
    sw(v1, a2, libs23::sfd::kTimeTick);
    sw(a0, s0, libs5::sfdh::kTimeUpd);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059A9A0 sub_59A9A0 -- 56 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Time code to time with the 24,000 unit.
void sub_59A9A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a9a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    a0 = 24000;  // the unit
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a3;
    jal(ctx, 0x59A9B8u, gen::fn_sub_59A910_0059a910);
    sw(s1, s0, 0);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0059AA48 sub_59AA48 -- 156 bytes; leaf frame (no stack)
// 23.976 drop-frame time code to time.
void sub_59AA48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0059aa48
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t0, a1, 12);
    t3 = 10;
    lw(t4, a1, 16);
    v0 = 0x10000;
    div(t0, t3);
    lw(t2, a1, 8);
    v0 = v0 | 0x5114;
    t1 = 1438;
    v1 = sll(t4, 1);
    if (t3 == 0) {
        brk(ctx, 0x59AA70u, 0x7u);
    }
    // 0x0059aa74
    charge(ctx, 28);
    v1 = addu(v1, t4);
    lw(t4, a1, 20);
    v1 = sll(v1, 2);
    mflo(t5);
    mult(t2, t2, v0);
    mult(t0, t0, t1);
    lw(t1, a1, 24);
    lh(v0, a1, 30);
    v1 = addu(v1, t5);
    v1 = sll(v1, 1);
    t4 = addu(t4, t1);
    a1 = sll(v0, 5);
    t2 = addu(t2, t0);
    a1 = subu(a1, v0);
    v1 = addu(v1, t2);
    a1 = sll(a1, 2);
    v1 = addu(v1, t4);
    a1 = addu(a1, v0);
    v0 = sll(v1, 5);
    a1 = sll(a1, 2);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    v0 = addu(v0, a1);
    sw(v0, a2, 0);
    sw(a0, a3, 0);
}

// 0x0059ADF8 sub_59ADF8 -- 140 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// The time source's rate scaled by the time record's unit.
void sub_59ADF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059adf8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    link(ctx, 0x59AE14u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0059ae28
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x118;  // error 0xFF000118
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059ae40
    charge(ctx, 3);
    lw(v1, s0, libs23::sfd::kTimeSrc);
    a0 = addiu(s0, libs5::sfdh::kTimeRec);
    if (v1 != 0) {
        // 0x0059ae4c
        charge(ctx, 9);
        v0 = sll(v1, 2);
        lw(a1, a0, libs23::sfd::kTimeUnit);
        a0 = 0x7D0000;
        a0 = addu(a0, v0);
        lw(a0, a0, -23872);  // 0x7CA2C0[source] (libs23::kRateTable)
        a2 = 1000;
        jal(ctx, 0x59AE60u, gen::fn_sub_57BAF0_0057baf0);
        sw(v0, s1, 0);
        v0 = 0;
    }
    // 0x0059ae70 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059AEF8 sub_59AEF8 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Stores a time pair in the time record and marks the time updated.
void sub_59AEF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059aef8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x59AF14u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a2 = addiu(s0, libs5::sfdh::kTimeRec);
    a0 = 0;
    a1 = a1 | 0x125;  // error 0xFF000125
    if (v0 != 0) {
        // 0x0059af30
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059af48
    charge(ctx, 13);
    lw(v1, a2, libs23::sfd::kTimeSet);
    a0 = 1;
    sw(s1, a2, libs23::sfd::kTimeSetB);
    v1 = addiu(v1, 1);
    sw(s2, a2, libs23::sfd::kTimeSetA);
    sw(v1, a2, libs23::sfd::kTimeSet);
    ld(s1, sp, 0x8);
    sw(a0, s0, libs5::sfdh::kTimeUpd);
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0059AF80 sub_59AF80 -- 196 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Whether a time is due on the play clock.
void sub_59AF80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059af80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(ra, sp, 0x20);
    link(ctx, 0x59AFA8u);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 0);
    call(ctx, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    a1 = lui(0xFF00);
    a2 = addiu(s0, libs5::sfdh::kPara);
    a1 = a1 | 0x126;  // error 0xFF000126
    if (v0 != 0) {
        // 0x0059afc4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059afe0
    charge(ctx, 3);
    lw(v1, a2, libs23::sfd::kParaClock);  // parameter 14
    if (v1 != 0) {
        lw(a0, s0, libs13::sfd::kReq);
        // 0x0059aff8
        charge(ctx, 3);
        v1 = 4;  // start requested
        if (a0 == v1) {
            lw(t0, a2, libs23::sfd::kParaClockArg);  // parameter 45
            // 0x0059b010
            charge(ctx, 6);
            a2 = s2;
            a0 = s0;
            a1 = s3;
            a3 = s1;
            jal(ctx, 0x59B01Cu, gen::fn_sub_59B048_0059b048);
            v0 = 0;
        } else {
            // 0x0059b004
            charge(ctx, 2);
            sw(zero, s1, 0);
        }
    } else {
        // 0x0059afec
        charge(ctx, 3);
        v1 = 1;
        sw(v1, s1, 0);
    }
    // 0x0059b028 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059C468 sub_59C468 -- 20 bytes; leaf frame (no stack)
// Stores two globals.
void sub_59C468(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059c468
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v1 = 0x7B0000;
    sw(a0, v0, 18396);  // 0x7B47DC
    sw(a1, v1, 18392);  // 0x7B47D8
}

// 0x0059C7B8 sub_59C7B8 -- 292 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s2 sp+0x10, ra sp+0x38
// Sets an entry of transfer slot 8.
void sub_59C7B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059c7b8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = t0;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s5, sp, 0x28);
    s5 = a3;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x38);
    s0 = addiu(s1, libs5::sfdh::kTrn8InEnd);  // transfer slot 8
    jal(ctx, 0x59C7F0u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x192;  // error 0xFF000192
    v1 = 8;
    if (v0 != 0) {
        // 0x0059c80c
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
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059c838
    charge(ctx, 3);
    lw(s2, s0, libs5::sfdh::kTrn8Stream - libs5::sfdh::kTrn8InEnd);
    lw(v0, s0, libs5::sfdh::kTrn8Work - libs5::sfdh::kTrn8InEnd);
    if (s2 == v1) {
        // 0x0059c844
        charge(ctx, 13);
        a0 = s1;
        ld(s1, sp, 0x8);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x10);
        a1 = a1 | 0x602;  // error 0xFF000602
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059c878
    charge(ctx, 25);
    s0 = sll(s6, 4);
    t0 = s3;
    s0 = addu(v0, s0);
    a1 = s4;
    s0 = addiu(s0, 4);
    a3 = s5;
    a0 = s0;
    a2 = 0;
    jal(ctx, 0x59C894u, gen::fn_sub_59CC30_0059cc30);
    a0 = s1;
    a1 = s2;
    a2 = s6;
    a3 = s0;
    jal(ctx, 0x59C8A8u, gen::fn_sub_588F48_00588f48);
    v0 = 0;
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

// 0x0059C9F8 sub_59C9F8 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59C9F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059c9f8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CC50 sub_59CC50 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59CC50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cc50
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CD00 sub_59CD00 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59CD00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cd00
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CEC8 sub_59CEC8 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59CEC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cec8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CED0 sub_59CED0 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59CED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059ced0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CED8 sub_59CED8 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59CED8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059ced8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CEE0 sub_59CEE0 -- 8 bytes; leaf frame (no stack)
// SFD stub: returns 0.
void sub_59CEE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cee0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0059CEE8 sub_59CEE8 -- 28 bytes; frame 0x10: ra sp+0x0
// "Unsupported" (0xFF000701).
void sub_59CEE8(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cee8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x701;  // error 0xFF000701
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059CF08 sub_59CF08 -- 28 bytes; frame 0x10: ra sp+0x0
// "Unsupported" (0xFF000701).
void sub_59CF08(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cf08
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0x701;  // error 0xFF000701
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0059EAA8 sub_59EAA8 -- 40 bytes; leaf frame (no stack)
// Reverses a stepping record.
void sub_59EAA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059eaa8
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a0, libs23::step::kCount);
    lw(v0, a0, libs23::step::kStep);
    v1 = addiu(v1, -1);
    lw(a1, a0, libs23::step::kPtr);
    mult(v1, v0, v1);
    v0 = subu(0, v0);
    sw(v0, a0, libs23::step::kStep);
    a1 = addu(a1, v1);
    sw(a1, a0, libs23::step::kPtr);
}

// 0x0059EAD0 sub_59EAD0 -- 40 bytes; leaf frame (no stack)
// Reverses a stepping record.
void sub_59EAD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059ead0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a0, libs23::step::kCount);
    lw(v0, a0, libs23::step::kStep);
    v1 = addiu(v1, -1);
    lw(a1, a0, libs23::step::kPtr);
    mult(v1, v0, v1);
    v0 = subu(0, v0);
    sw(v0, a0, libs23::step::kStep);
    a1 = addu(a1, v1);
    sw(a1, a0, libs23::step::kPtr);
}

// 0x0059FD70 WTLS_set_table_2 -- 12 bytes; leaf frame (no stack)
// Sets the word 0x7B491C.
void WTLS_set_table_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059fd70
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 18716);  // 0x7B491C
}

// 0x0059FD80 __errno_14 -- 12 bytes; leaf frame (no stack)
// Returns the word 0x7B491C.
void __errno_14(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0059fd80
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 18716);  // 0x7B491C
}

// 0x0059FDA0 sub_59FDA0 -- 12 bytes; leaf frame (no stack)
// Sets word +72 of the record at +36.
void sub_59FDA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0059fda0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 36);
    sw(a1, v0, 72);
}

// 0x0059FE58 sub_59FE58 -- 8 bytes; leaf frame (no stack)
// Returns word +52.
void sub_59FE58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059fe58
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 52);
}

// 0x005A0050 sub_5A0050 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Sets up the three planes (Y full, Cb / Cr half).
void sub_5A0050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a0050
    enter(ctx, 23);  // entry check point + this block's cycles
    v0 = srl(a1, 31);
    sp = addiu(sp, -0x20);
    v0 = addu(v0, a1);
    sd(s0, sp, 0x0);
    v0 = sra(v0, 1);
    s0 = a0;
    v0 = sll(v0, 1);
    sd(s1, sp, 0x8);
    a1 = v0;
    a0 = addiu(s0, libs23::planes::kY);
    sd(ra, sp, 0x10);
    s1 = sra(v0, 1);
    jal(ctx, 0x5A007Cu, gen::fn_sub_5A00B0_005a00b0);
    a0 = addiu(s0, libs23::planes::kCb);
    a1 = s1;
    jal(ctx, 0x5A0088u, gen::fn_sub_5A00B0_005a00b0);
    a0 = addiu(s0, libs23::planes::kCr);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5A00B0_005a00b0(ctx);  // tail call
}

// 0x005A00D8 sub_5A00D8 -- 36 bytes; leaf frame (no stack)
// Sets the three plane pitches (Y full, Cb / Cr half).
void sub_5A00D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005a00d8
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = srl(a1, 31);
    v0 = addu(v0, a1);
    v0 = sra(v0, 1);
    v0 = sll(v0, 1);
    v1 = sra(v0, 1);
    sw(v0, a0, libs23::planes::kYPitch);
    sw(v1, a0, libs23::planes::kCrPitch);
    sw(v1, a0, libs23::planes::kCbPitch);
}

// 0x005A04C0 sub_5A04C0 -- 48 bytes; leaf frame (no stack)
// Reads the pair +12 / +16 when +8 is 1.
void sub_5A04C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005a04c0
    enter(ctx, 5);  // entry check point + this block's cycles
    a0 = addiu(a0, 8);
    v1 = 1;
    lw(v0, a0, 0);
    if (v0 != v1) {
        // 0x005a04d4
        charge(ctx, 3);
        sw(zero, a1, 0);
        sw(zero, a2, 0);
        return;
    }
    lw(v0, a0, 8);
    // 0x005a04e0
    charge(ctx, 4);
    lw(v1, a0, 4);
    sw(v0, a2, 0);
    sw(v1, a1, 0);
}

// 0x005A10F8 sub_5A10F8 -- 12 bytes; leaf frame (no stack)
// Returns word +4 of the record at +36.
void sub_5A10F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005a10f8
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, 36);
    lw(v0, v1, 4);
}

// 0x005A1188 sub_5A1188 -- 144 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Writes a "<SUDPS_>" tag.
void sub_5A1188(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1188
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 0x7D0000;
    sd(s1, sp, 0x18);
    s1 = a2;
    a1 = addiu(a1, -21592);  // "<SUDPS_>"
    a2 = 8;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x5A11A8u, gen::fn_strncpy_00524828);
    a1 = 0x7D0000;
    a0 = sp;
    a2 = 19;  // "<000013>"
    a1 = addiu(a1, -21576);  // "<%06X>"
    jal(ctx, 0x5A11BCu, gen::fn_sprintf_00523ac8);
    a0 = s0;
    a1 = sp;
    s0 = addiu(s0, 16);
    jal(ctx, 0x5A11CCu, gen::fn_strcat_00523e68);
    a1 = 0x7D0000;
    a2 = 2;
    a0 = s0;
    a1 = addiu(a1, -21568);  // "02"
    jal(ctx, 0x5A11E0u, gen::fn_strncpy_00524828);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x5A11ECu, gen::fn_sub_5A1218_005a1218);
    a1 = 0x7D0000;
    a0 = s0;
    a1 = addiu(a1, -21560);  // "\n"
    jal(ctx, 0x5A11FCu, gen::fn_strcat_00523e68);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005A13C0 sub_5A13C0 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Tag byte +20 is 'I'.
void sub_5A13C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a13c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x005a13d8
        charge(ctx, 2);
        if (i64(v0) < 0) {
            goto L_005a13e0;
        }
        // 0x005a13e8
        charge(ctx, 7);
        jal(ctx, 0x5A13E8u, gen::fn_sub_5A12F8_005a12f8);
        a1 = 0x7D0000;
        a0 = addiu(s0, 20);
        a1 = addiu(a1, -21496);  // &0x7CAC08
        a2 = 1;
        if (v0 != 0) {
            // 0x005a1404
            charge(ctx, 3);
            jal(ctx, 0x5A1404u, gen::fn_strncmp_00524670);
            v0 = sltiu(v0, 1);
        }
        // 0x005a1410 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_005a13e0:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a1410 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005A1420 sub_5A1420 -- 144 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Tag byte +21: 'P' 1, 'I' 2.
void sub_5A1420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1420
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x005a1438
        charge(ctx, 2);
        if (i64(v0) < 0) {
            goto L_005a1440;
        }
        // 0x005a1448
        charge(ctx, 8);
        jal(ctx, 0x5A1448u, gen::fn_sub_5A12F8_005a12f8);
        a1 = 0x7D0000;
        v1 = sltiu(v0, 2);
        v0 = 0;
        a1 = addiu(a1, -21504);  // &0x7CAC00
        a2 = 1;
        if (v1 == 0) {
            // 0x005a1468
            charge(ctx, 9);
            s0 = addiu(s0, 21);
            a0 = s0;
            jal(ctx, 0x5A146Cu, gen::fn_strncmp_00524670);
            a1 = 0x7D0000;
            a0 = s0;
            a1 = addiu(a1, -21496);  // &0x7CAC08
            a2 = 1;
            v1 = 1;
            if (v0 != 0) {
                // 0x005a148c
                charge(ctx, 4);
                jal(ctx, 0x5A148Cu, gen::fn_strncmp_00524670);
                v1 = 2;
                if (v0 != 0) v1 = 0;
            }
            // 0x005a149c
            charge(ctx, 1);
            v0 = v1;
        }
        // 0x005a14a0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_005a1440:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a14a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005A14B0 sub_5A14B0 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Tag byte +22 is not 'A'.
void sub_5A14B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a14b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x005a14c8
        charge(ctx, 2);
        if (i64(v0) < 0) {
            goto L_005a14d0;
        }
        // 0x005a14d8
        charge(ctx, 9);
        jal(ctx, 0x5A14D8u, gen::fn_sub_5A12F8_005a12f8);
        a1 = 0x7D0000;
        v1 = sltiu(v0, 2);
        v0 = 0;
        a0 = addiu(s0, 22);
        a1 = addiu(a1, -21552);  // &0x7CABD0
        a2 = 1;
        if (v1 == 0) {
            // 0x005a14fc
            charge(ctx, 3);
            jal(ctx, 0x5A14FCu, gen::fn_strncmp_00524670);
            v0 = sltu(0, v0);
        }
        // 0x005a1508 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_005a14d0:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a1508 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005A1518 sub_5A1518 -- 604 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Tag bytes +23..+25 as hexadecimal.
void sub_5A1518(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a1518
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (s0 != 0) {
        // 0x005a1534
        charge(ctx, 2);
        if (i64(s1) < 0) {
            goto L_005a153c;
        }
        // 0x005a1548
        charge(ctx, 8);
        jal(ctx, 0x5A1548u, gen::fn_sub_5A12F8_005a12f8);
        a2 = 23;
        v1 = sltiu(v0, 2);
        v0 = 0;
        a0 = s0;
        a1 = s1;
        if (v1 != 0) {
            // 0x005a1580 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
        // 0x005a1568
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        // 0x005a1718
        charge(ctx, 3);
        sp = addiu(sp, -0x30);
        sd(ra, sp, 0x20);
        if (a0 != 0) {
            // 0x005a1724
            charge(ctx, 2);
            if (i64(a1) < 0) {
                goto L_005a172c;
            }
            v0 = addu(a0, a2);
            // 0x005a1738
            charge(ctx, 12);
            a0 = sp;
            lb(v1, v0, 0);
            lb(a3, v0, 1);
            lb(t0, v0, 2);
            sb(v1, sp, 0x0);
            sb(a3, sp, 0x1);
            a1 = addiu(sp, 0x10);
            a2 = 16;
            link(ctx, 0x5A1758u);  // $ra first: the delay slot below depends on it
            sb(t0, sp, 0x2);
            call(ctx, gen::fn_sub_5A1778_005a1778);
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            // 0x005a1768 (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_005a172c:
        charge(ctx, 2);
        v0 = 0;
        // 0x005a1768 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_005a153c:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a1580 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
