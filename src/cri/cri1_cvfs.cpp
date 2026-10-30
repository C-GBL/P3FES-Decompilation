// Phase 5 slice cri1 -- cvFs: the CRI virtual file system's device table and name helpers (and newlib strncmp).
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

// 0x005558E8 sub_5558E8 -- 44 bytes; frame 0x10: ra sp+0x0
// Call the cvFs error callback (0x7A08A4) with its object (0x7A08A8). [cvfs_callErrFunc]
void sub_5558E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005558e8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 2212);  // 0x7A08A4
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x005558fc
        charge(ctx, 3);
        v0 = 0x7A0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x555900u);  // $ra = the return address
        lw(a0, v0, 2216);
        call_ptr(ctx, jt);
    }
    // 0x00555908 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00555918 sub_555918 -- 36 bytes; frame 0x10: ra sp+0x0
// CvFs error: the message through the error callback. [cvfs_Error]
void sub_555918(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555918
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    a0 = 0x7A0000;
    a0 = addiu(a0, 2216);  // &0x7A08A8
    a2 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5558E8_005558e8(ctx);  // tail call
}

// 0x00555940 cvFsInit -- 196 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// CvFs init: the first call clears the 40 handles, the 32 device names and the default device name.
void cvFsInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00555940
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(s1, sp, 0x8);
    s1 = 0x7A0000;
    sd(s0, sp, 0x0);
    v0 = addiu(v0, 2208);  // "X9|"
    sd(ra, sp, 0x10);
    lw(v1, s1, 2220);  // 0x7A08AC
    lw(a0, v0, 0);  // 0x7A08A0
    cc = v1 != 0;  // the condition, before the delay slot changes it
    v1 = addiu(s1, 2220);  // &0x7A08AC
    if (!cc) {
        // 0x0055596c
        charge(ctx, 3);
        v0 = 0x990000;
        v1 = 39;
        v0 = addiu(v0, 29976);  // &cvFsHandleTable
        for (;;) {
            // 0x00555978
            charge(ctx, 7);
            v1 = addiu(v1, -1);
            sw(zero, v0, 0);
            sw(zero, v0, 4);
            v0 = addiu(v0, 8);
            if (i64(v1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00555994
        charge(ctx, 5);
        v0 = 0x990000;
        v1 = 31;
        v0 = addiu(v0, 30296);  // &0x997658
        v0 = addiu(v0, 500);  // &0x99784C
        for (;;) {
            // 0x005559a8
            charge(ctx, 7);
            v1 = addiu(v1, -1);
            sb(zero, v0, 0);
            v0 = addiu(v0, -16);
            if (i64(v1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005559c4
        charge(ctx, 8);
        s0 = 0x990000;
        a1 = 0;
        s0 = addiu(s0, 30808);  // &0x997858
        a2 = 9;
        a0 = s0;
        jal(ctx, 0x5559D4u, gen::fn_memset_00521408);
        sb(zero, s0, 0);  // 0x997858
        v1 = addiu(s1, 2220);
    }
    // 0x005559e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    lw(v0, v1, 0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);
    sp = addiu(sp, 0x20);
}

// 0x00555D10 sub_555D10 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Upper-case a string in place (a-z only). [cvfs_ToUpperStr]
void sub_555D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555d10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x555D1Cu, gen::fn_strlen_00524388);
    v0 = addiu(v0, 1);
    a2 = 0;
    if (v0 != 0) {
        // 0x00555d30
        charge(ctx, 2);
        a3 = v0;
        a0 = addu(s0, a2);
        for (;;) {
            // 0x00555d38
            charge(ctx, 7);
            a2 = addiu(a2, 1);
            lbu(v0, a0, 0);
            v1 = addiu(v0, -32);
            v0 = addiu(v0, -97);
            v0 = sltiu(v0, 26);
            a1 = sltu(a2, a3);
            if (v0 != 0) {
                // 0x00555d54
                charge(ctx, 1);
                sb(v1, a0, 0);
            }
            // 0x00555d58
            charge(ctx, 2);
            a0 = addu(s0, a2);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00555d60 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005561E8 cvfs_getDevName -- 324 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Split "DEV:file" into an upper-case device name and the file name (no colon: no device; one-letter device names are
// drive letters and stay in the file name).
// Arguments: $a0 device name out, $a1 file name out, $a2 the path (at most 297 characters each).
void cvfs_getDevName(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005561e8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (a2 == 0) {
        // 0x00556318 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00556204
    charge(ctx, 4);
    lb(v1, a2, 0);
    v0 = 58;
    t0 = 0;
    if (v1 != v0) {
        // 0x00556214
        charge(ctx, 2);
        a1 = a2;
        if (v1 == 0) {
            goto L_00556270;
        }
        // 0x0055621c
        charge(ctx, 3);
        a3 = 58;
        lbu(a0, a1, 0);
        for (;;) {
            // 0x00556228
            charge(ctx, 6);
            v1 = addu(s0, t0);
            t0 = addiu(t0, 1);
            v0 = slti(t0, 297);
            a1 = addu(a2, t0);
            sb(a0, v1, 0);
            if (v0 == 0) {
                goto L_00556264;
            }
            // 0x00556240
            charge(ctx, 3);
            lb(v0, a1, 0);
            if (v0 != a3) {
                // 0x0055624c
                charge(ctx, 2);
                if (v0 == 0) {
                    goto L_00556254_7;
                }
                lbu(a0, a1, 0);
                backedge(ctx);
                continue;
            }
            break;
        }
        goto L_00556268;
    }
    // 0x00556260
    charge(ctx, 1);
    a1 = a2;
L_00556264:
    charge(ctx, 1);
    lb(v0, a1, 0);
L_00556268:
    charge(ctx, 2);
    v1 = addu(s0, t0);
    if (v0 == 0) {
    L_00556270:
        charge(ctx, 10);
        v0 = addu(s0, t0);
        a0 = s0;
        link(ctx, 0x556278u);  // $ra first: the delay slot below depends on it
        sb(zero, v0, 0);
        call(ctx, gen::fn_strlen_00524388);
        a0 = s1;
        a1 = s0;
        a2 = addiu(v0, 1);
        jal(ctx, 0x556288u, gen::fn_memcpy_00521250);
        sb(zero, s0, 0);
        // 0x00556318 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00556298
    charge(ctx, 4);
    t0 = addiu(t0, 1);
    v0 = 2;
    sb(zero, v1, 0);
    if (t0 == v0) {
        // 0x005562a8
        charge(ctx, 2);
        sb(zero, s0, 0);
        t0 = 0;
    }
    // 0x005562b0
    charge(ctx, 3);
    v0 = slti(t0, 297);
    a1 = t0;
    if (v0 != 0) {
        // 0x005562bc
        charge(ctx, 4);
        v1 = addu(a2, t0);
        lb(v0, v1, 0);
        a3 = s1;
        if (v0 != 0) {
            // 0x005562cc
            charge(ctx, 1);
            lbu(v0, v1, 0);
            for (;;) {
                // 0x005562d0
                charge(ctx, 6);
                a1 = addiu(a1, 1);
                a0 = slti(a1, 297);
                v1 = addu(a2, a1);
                sb(v0, a3, 0);
                a3 = addiu(a3, 1);
                if (a0 != 0) {
                    // 0x005562e8
                    charge(ctx, 3);
                    lb(v0, v1, 0);
                    if (v0 != 0) {
                        lbu(v0, v1, 0);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
    }
    // 0x005562f4
    charge(ctx, 9);
    v0 = subu(a1, t0);
    a0 = s0;
    v0 = addu(s1, v0);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sb(zero, v0, 0);
    sp = addiu(sp, 0x20);
    gen::fn_sub_555D10_00555d10(ctx);  // tail call
    return;
L_00556254_7:
    charge(ctx, 2);
    goto L_00556268;
}

// 0x00556330 cvfs_getDefDev -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copy the default device name (empty when none).
void cvfs_getDefDev(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00556330
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = 0x990000;
    s0 = addiu(s0, 30808);  // &0x997858
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    a0 = s0;
    jal(ctx, 0x55634Cu, gen::fn_strlen_00524388);
    a2 = addiu(v0, 1);
    lb(v0, s0, 0);  // 0x997858
    a0 = s1;
    a1 = s0;
    if (v0 != 0) {
        // 0x00556380
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_memcpy_00521250(ctx);  // tail call
        return;
    }
    // 0x00556368
    charge(ctx, 6);
    sb(zero, s1, 0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
