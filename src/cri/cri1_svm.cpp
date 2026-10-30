// Phase 5 slice cri1 -- SVM: the CRI server-manager lock / unlock and error-callback helpers.
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

// 0x00564888 sub_564888 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SVM lock: call the lock callback (0x99A0A0 / its object 0x99A0A4); the outermost lock records its type. [SVM_Lock]
// Without a lock callback nothing is counted (the SVM is not set up).
void sub_564888(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00564888
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    v0 = addiu(v0, -24416);  // &0x99A0A0
    lw(v1, v0, 0);  // 0x99A0A0
    s0 = a0;
    if (v1 != 0) {
        // 0x005648a8
        charge(ctx, 9);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5648A8u);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
        v0 = 0x7B0000;
        v1 = 0x7B0000;
        a0 = addiu(v0, 9780);  // &0x7B2634
        v1 = addiu(v1, 9776);  // &0x7B2630
        lw(v0, v1, 0);  // 0x7B2630
        if (v0 == 0) {
            sw(s0, a0, 0);  // 0x7B2634
        }
        // 0x005648cc
        charge(ctx, 3);
        lw(v0, v1, 0);
        v0 = addiu(v0, 1);
        sw(v0, v1, 0);
    }
    // 0x005648d8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005648E8 sub_5648E8 -- 140 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// SVM unlock: the outermost unlock checks the type (a mismatch is reported), then the unlock callback (0x99A0A8 /
// 0x99A0AC). [SVM_Unlock]
// Without an unlock callback nothing is counted; the type check happens on the outermost unlock only.
void sub_5648E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005648e8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = a0;
    sd(s1, sp, 0x8);
    s1 = 0x9A0000;
    lw(v0, s1, -24408);  // 0x99A0A8
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (v0 != 0) {
        // 0x00564908
        charge(ctx, 8);
        v0 = 0x7B0000;
        v0 = addiu(v0, 9776);  // &0x7B2630
        lw(v1, v0, 0);  // 0x7B2630
        v1 = addiu(v1, -1);
        sw(v1, v0, 0);  // 0x7B2630
        lw(a0, v0, 0);  // 0x7B2630
        v1 = addiu(s1, -24408);
        if (a0 == 0) {
            // 0x00564928
            charge(ctx, 5);
            v0 = 0x7B0000;
            s0 = addiu(v0, 9780);  // &0x7B2634
            lw(v1, s0, 0);  // 0x7B2634
            if (v1 != a2) {
                // 0x0056493c
                charge(ctx, 4);
                a0 = 0x7C0000;
                lw(a1, s0, 0);
                a0 = addiu(a0, 28024);  // "2103102:SVM:svm_unlock:lock type miss match.(type org=%d, type now=%d)"
                jal(ctx, 0x564944u, gen::fn_sub_564AA8_00564aa8);
            }
            // 0x0056494c
            charge(ctx, 2);
            sw(zero, s0, 0);
            v1 = addiu(s1, -24408);
        }
        // 0x00564954
        charge(ctx, 3);
        lw(v0, v1, 0);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x564958u);  // $ra = the return address
        lw(a0, v1, 4);
        call_ptr(ctx, jt);
    }
    // 0x00564960 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00564978 sub_564978 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM lock, type 1. [SVM_LockVar]
void sub_564978(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564978
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564888_00564888(ctx);  // tail call
}

// 0x00564990 sub_564990 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM unlock, type 1. [SVM_UnlockVar]
void sub_564990(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564990
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5648E8_005648e8(ctx);  // tail call
}

// 0x005649A8 sub_5649A8 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM lock, type 2. [SVM_LockRsc]
void sub_5649A8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005649a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 2;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564888_00564888(ctx);  // tail call
}

// 0x005649C0 sub_5649C0 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM lock, type 3.
void sub_5649C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005649c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 3;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564888_00564888(ctx);  // tail call
}

// 0x005649D8 sub_5649D8 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM lock, type 4.
void sub_5649D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005649d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 4;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564888_00564888(ctx);  // tail call
}

// 0x005649F0 sub_5649F0 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM lock, type 5.
void sub_5649F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005649f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 5;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564888_00564888(ctx);  // tail call
}

// 0x00564A20 sub_564A20 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM unlock, type 2. [SVM_UnlockRsc]
void sub_564A20(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564a20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 2;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5648E8_005648e8(ctx);  // tail call
}

// 0x00564A38 sub_564A38 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM unlock, type 3.
void sub_564A38(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564a38
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 3;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5648E8_005648e8(ctx);  // tail call
}

// 0x00564A50 sub_564A50 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM unlock, type 4.
void sub_564A50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564a50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 4;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5648E8_005648e8(ctx);  // tail call
}

// 0x00564A68 sub_564A68 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM unlock, type 5.
void sub_564A68(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564a68
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 5;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5648E8_005648e8(ctx);  // tail call
}

// 0x00564AA8 sub_564AA8 -- 168 bytes; frame 0x80: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SVM error with a format: the 128-byte text buffer 0x7B2678 cleared, vsprintf into it, then the error callback
// (0x99A0B0 / 0x99A0B4). [SVM_CallErr]
void sub_564AA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00564aa8
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 9848);  // &0x7B2678
    sd(s1, sp, 0x8);
    sd(a1, sp, 0x48);
    a1 = 0;
    sd(a2, sp, 0x50);
    a2 = 128;
    s1 = a0;
    a0 = s0;
    sd(ra, sp, 0x10);
    sd(a3, sp, 0x58);
    sd(t0, sp, 0x60);
    sd(t1, sp, 0x68);
    sd(t2, sp, 0x70);
    sd(t3, sp, 0x78);
    swc1(f12, sp, 0x28);
    swc1(f13, sp, 0x2C);
    swc1(f14, sp, 0x30);
    swc1(f15, sp, 0x34);
    swc1(f16, sp, 0x38);
    swc1(f17, sp, 0x3C);
    swc1(f18, sp, 0x40);
    link(ctx, 0x564B08u);  // $ra first: the delay slot below depends on it
    swc1(f19, sp, 0x44);
    call(ctx, gen::fn_memset_00521408);
    a2 = addiu(sp, 0x48);
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x564B18u, gen::fn_vsprintf_005288c8);
    v0 = 0x9A0000;
    v0 = addiu(v0, -24400);  // &0x99A0B0
    lw(v1, v0, 0);  // 0x99A0B0
    a1 = s0;
    if (v1 != 0) {
        // 0x00564b34
        charge(ctx, 2);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x564B34u);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
    }
    // 0x00564b3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x80);
}

// 0x00564B50 sub_564B50 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SVM error with a text: strncpy (127) into 0x7B2678, then the error callback. [SVM_CallErr1]
void sub_564B50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00564b50
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 9848);  // &0x7B2678
    a2 = 127;
    sd(ra, sp, 0x8);
    a0 = s0;
    jal(ctx, 0x564B6Cu, gen::fn_strncpy_00524828);
    v0 = 0x9A0000;
    v0 = addiu(v0, -24400);  // &0x99A0B0
    lw(v1, v0, 0);  // 0x99A0B0
    a1 = s0;
    if (v1 != 0) {
        // 0x00564b88
        charge(ctx, 2);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x564B88u);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
    }
    // 0x00564b90 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
