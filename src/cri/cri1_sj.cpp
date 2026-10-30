// Phase 5 slice cri1 -- SJ: the stream joints SJMEM / SJRBF / SJUNI (handle pools, chunk get / put / unget, the vtables' entries).
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
namespace sj = cri1::sj;
namespace sjmem = cri1::sjmem;
namespace sjrbf = cri1::sjrbf;
namespace sjuni = cri1::sjuni;

// 0x00561758 sub_561758 -- 52 bytes; leaf frame (no stack)
// SJ library init counter (the first init clears 0x7AC770). [sj_Init]
void sub_561758(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00561758
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    a1 = 1;
    v1 = addiu(v1, -14472);  // &0x7AC778
    lw(v0, v1, 0);  // 0x7AC778
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x7AC778
    lw(a0, v1, 0);  // 0x7AC778
    v0 = 0x7B0000;
    if (a0 == a1) {
        // 0x0056177c
        charge(ctx, 2);
        v0 = addiu(v0, -14480);
        sw(zero, v0, 0);
    }
    // 0x00561784 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005617C0 sub_5617C0 -- 20 bytes; frame 0x10: ra sp+0x0
// SJ lock: SVM lock of type 1. [sj_Lock]
void sub_5617C0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005617c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x005617D8 sub_5617D8 -- 20 bytes; frame 0x10: ra sp+0x0
// SJ unlock: SVM unlock of type 1. [sj_Unlock]
void sub_5617D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005617d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x005617F0 sub_5617F0 -- 20 bytes; frame 0x10: ra sp+0x0
// Report an SJ error text through the SVM error callback. [sj_Error]
void sub_5617F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005617f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564B50_00564b50(ctx);  // tail call
}

// 0x00561808 sub_561808 -- 28 bytes; frame 0x10: ra sp+0x0
// The SJMEM handles' default error callback ("SJMEM Error"). [sjmem_DefaultErrFn]
void sub_561808(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561808
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 26624);  // "SJMEM Error"
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617F0_005617f0(ctx);  // tail call
}

// 0x00561828 sub_561828 -- 68 bytes; frame 0x50: s0 sp+0x40, ra sp+0x48
// SJMEM error: code + message joined in a 64-byte stack buffer, then reported. [sjmem_Error]
void sub_561828(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561828
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = a0;
    sd(s0, sp, 0x40);
    s0 = a1;
    a0 = sp;
    sd(ra, sp, 0x48);
    a1 = v0;
    jal(ctx, 0x561840u, gen::fn_strcpy_00524270);
    a0 = sp;
    a1 = s0;
    jal(ctx, 0x56184Cu, gen::fn_strcat_00523e68);
    a0 = sp;
    jal(ctx, 0x561854u, gen::fn_sub_5617F0_005617f0);
    ld(s0, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00561870 sub_561870 -- 44 bytes; frame 0x10: ra sp+0x0
// SJMEM init (locked): the SJ counter and the handle pool. [SJMEM_Init]
void sub_561870(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00561870
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x561878u, gen::fn_sub_561758_00561758);
    jal(ctx, 0x561880u, gen::fn_sub_5617C0_005617c0);
    jal(ctx, 0x561888u, gen::fn_sub_5618A0_005618a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005618A0 sub_5618A0 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SJMEM pool init: the first call clears the 32 handles. [sjmem_InitPool]
void sub_5618A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005618a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -14416);  // &0x7AC7B0
    lw(v0, s0, 0);  // 0x7AC7B0
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x005618bc
        charge(ctx, 6);
        a0 = 0x7B0000;
        a1 = 0;
        a0 = addiu(a0, -14408);  // &0x7AC7B8
        a2 = 1152;
        jal(ctx, 0x5618C8u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x005618d4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005618F0 sub_5618F0 -- 92 bytes, 2 chunks; frame 0x10: ra sp+0x0
// SJMEM finish (locked). [SJMEM_Finish]
void sub_5618F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005618f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5618F8u, gen::fn_sub_5617C0_005617c0);
    jal(ctx, 0x561900u, gen::fn_sub_561920_00561920);
    jal(ctx, 0x561908u, gen::fn_sub_5617D8_005617d8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00561790
    charge(ctx, 8);
    v0 = 0x7B0000;
    v0 = addiu(v0, -14472);  // &0x7AC778
    lw(v1, v0, 0);  // 0x7AC778
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x7AC778
    lw(a0, v0, 0);  // 0x7AC778
    v0 = 0x7B0000;
    if (a0 == 0) {
        // 0x005617b0
        charge(ctx, 2);
        v0 = addiu(v0, -14480);
        sw(zero, v0, 0);
    }
    // 0x005617b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00561920 sub_561920 -- 76 bytes; frame 0x10: ra sp+0x0
// SJMEM pool finish: the last call clears the 32 handles. [sjmem_FinishPool]
void sub_561920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561920
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7B0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, -14416);  // &0x7AC7B0
    lw(v0, v1, 0);  // 0x7AC7B0
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7AC7B0
    if (v0 != 0) {
        // 0x00561960
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00561940
    charge(ctx, 7);
    a0 = 0x7B0000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, -14408);  // &0x7AC7B8
    a2 = 1152;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00561970 sub_561970 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Create an SJMEM handle (locked): buffer, size. [SJMEM_Create]
void sub_561970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561970
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x561984u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x561990u, gen::fn_sub_5619B8_005619b8);
    s0 = v0;
    jal(ctx, 0x561998u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x005619B8 sub_5619B8 -- 200 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Take a free SJMEM handle, fill vtable / uuid / buffer / size / error callback, reset it. [sjmem_Create]
void sub_5619B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005619b8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x7B0000;
    v0 = addiu(a2, -14408);  // &0x7AC7B8
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    v1 = addiu(v0, 4);  // &0x7AC7BC
    t0 = a0;
    a0 = 0;
    lw(v0, v1, 0);  // 0x7AC7BC
    a3 = a1;
    if (v0 != 0) {
        // 0x005619e4
        charge(ctx, 1);
        a0 = addiu(a0, 1);
        for (;;) {
            // 0x005619e8
            charge(ctx, 3);
            v0 = slti(a0, 32);
            v1 = addiu(v1, 36);
            if (v0 != 0) {
                // 0x005619f4
                charge(ctx, 6);
                lw(v0, v1, 0);
                if (v0 != 0) {
                    a0 = addiu(a0, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00561a0c
    charge(ctx, 3);
    v1 = 32;
    v0 = 0;
    if (a0 != v1) {
        // 0x00561a18
        charge(ctx, 22);
        s0 = sll(a0, 3);
        v0 = addiu(a2, -14408);
        s0 = addu(s0, a0);
        v1 = 0x7B0000;
        s0 = sll(s0, 2);
        a2 = 0x7C0000;
        a1 = 0x560000;
        s0 = addu(s0, v0);
        v1 = addiu(v1, -14464);  // &0x7AC780
        a2 = addiu(a2, 26608);  // &0x7C67F0
        v0 = 1;
        a1 = addiu(a1, 6152);  // &sub_561808
        sw(v0, s0, sj::kUsed);
        a0 = s0;
        sw(v1, s0, sj::kVtbl);
        sw(t0, s0, sjmem::kBuf);
        sw(a3, s0, sjmem::kBufSize);
        sw(a2, s0, sj::kUuid);
        sw(a1, s0, sjmem::kErrFn);
        link(ctx, 0x561A64u);  // $ra first: the delay slot below depends on it
        sw(s0, s0, sjmem::kErrObj);
        call(ctx, gen::fn_sub_561CA8_00561ca8);
        v0 = s0;
    }
    // 0x00561a70 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00561A80 sub_561A80 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroy an SJMEM handle (locked). [SJMEM_Destroy]
void sub_561A80(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561a80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x561A8Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x561A94u, gen::fn_sub_561AB0_00561ab0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00561AB0 sub_561AB0 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroy: zero the 36 bytes. [sjmem_Destroy]
void sub_561AB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561ab0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00561ac4
        charge(ctx, 8);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 26640);  // "E2004090231"
        ld(ra, sp, 0x8);
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00561ae8
    charge(ctx, 3);
    lw(v0, s0, sj::kUsed);
    a1 = 0;
    if (v0 != 0) {
        // 0x00561b18
        charge(ctx, 7);
        a2 = 36;
        jal(ctx, 0x561B18u, gen::fn_memset_00521408);
        sw(zero, s0, sj::kUsed);
        ld(ra, sp, 0x8);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00561af4
    charge(ctx, 8);
    a0 = 0x7C0000;
    a1 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 26688);  // "E2004090232"
    ld(ra, sp, 0x8);
    a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_561828_00561828(ctx);  // tail call
}

// 0x00561B38 sub_561B38 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The uuid of an SJMEM handle (locked). [SJMEM_GetUuid]
void sub_561B38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561b38
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x561B44u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x561B4Cu, gen::fn_sub_561B70_00561b70);
    s0 = v0;
    jal(ctx, 0x561B54u, gen::fn_sub_5617D8_005617d8);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561B70 sub_561B70 -- 84 bytes; frame 0x10: ra sp+0x0
// The uuid pointer (+8). [sjmem_GetUuid]
void sub_561B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561b70
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00561b7c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 26736);  // "E2004090233"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        goto L_00561bac;
    }
    // 0x00561b90
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    if (v0 != 0) {
        lw(v0, a0, sj::kUuid);
    } else {
        // 0x00561b9c
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 26752);  // "E2004090234"
        a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
    L_00561bac:
        charge(ctx, 3);
        jal(ctx, 0x561BACu, gen::fn_sub_561828_00561828);
        v0 = 0;
    }
    // 0x00561bb8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561BC8 sub_561BC8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Set an SJMEM handle's error callback (locked). [SJMEM_EntryErrFunc]
void sub_561BC8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561bc8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x561BE4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x561BF4u, gen::fn_sub_561C18_00561c18);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00561C18 sub_561C18 -- 96 bytes; frame 0x10: ra sp+0x0
// Store the error callback and its object (+28 / +32). [sjmem_EntryErrFunc]
void sub_561C18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561c18
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00561c24
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26768);  // "E2004090235"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00561c40
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    ld(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x00561c68
        charge(ctx, 4);
        sw(a2, a0, sjmem::kErrObj);
        sw(a1, a0, sjmem::kErrFn);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00561c4c
    charge(ctx, 6);
    a0 = 0x7C0000;
    a1 = 0x7C0000;
    a0 = addiu(a0, 26784);  // "E2004090236"
    a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_561828_00561828(ctx);  // tail call
}

// 0x00561C78 sub_561C78 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Reset an SJMEM handle (locked). [SJMEM_Reset]
void sub_561C78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561c78
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x561C84u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x561C8Cu, gen::fn_sub_561CA8_00561ca8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00561CA8 sub_561CA8 -- 100 bytes; frame 0x10: ra sp+0x0
// Reset: data = size, read offset = 0. [sjmem_Reset]
void sub_561CA8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561ca8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00561cb4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26800);  // "E2004090237"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00561cd0
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    if (v0 != 0) {
        lw(v0, a0, sjmem::kBufSize);
        // 0x00561cf8
        charge(ctx, 5);
        ld(ra, sp, 0x0);
        sw(zero, a0, sjmem::kOffset);
        sw(v0, a0, sjmem::kLeft);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00561cdc
    charge(ctx, 7);
    a0 = 0x7C0000;
    a1 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26816);  // "E2004090238"
    a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_561828_00561828(ctx);  // tail call
}

// 0x00561D10 sub_561D10 -- 72 bytes; frame 0x10: ra sp+0x0
// Bytes on a line: line 1 = the data left, line 0 = none; another line calls the error callback (-3).
// [SJMEM_GetNumData]
void sub_561D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561d10
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a1 != v0) {
        // 0x00561d28
        charge(ctx, 2);
        v0 = 0;
        if (a1 != 0) {
            // 0x00561d30
            charge(ctx, 3);
            lw(v0, a0, sjmem::kErrFn);
            if (v0 == 0) {
                v0 = 0;
            } else {
                // 0x00561d3c
                charge(ctx, 4);
                lw(a0, a0, sjmem::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x561D40u, v0.u());
                v0 = 0;
            }
        }
    } else {
        // 0x00561d20
        charge(ctx, 2);
        lw(v0, a0, sjmem::kLeft);
    }
    // 0x00561d4c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561D58 sub_561D58 -- 92 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Get a chunk (locked). [SJMEM_GetChunk]
void sub_561D58(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561d58
    enter(ctx, 23);  // entry check point + this block's cycles
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
    jal(ctx, 0x561D7Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x561D90u, gen::fn_sub_561DB8_00561db8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00561DB8 sub_561DB8 -- 220 bytes; frame 0x10: ra sp+0x0
// Get a chunk: line 1 gives min(n, data left) bytes at buffer + offset and advances; line 0 gives an empty chunk.
// [sjmem_GetChunk]
void sub_561DB8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561db8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    sd(ra, sp, 0x0);
    if (t0 == 0) {
        // 0x00561dc8
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26832);  // "E2004090241"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00561de8
    charge(ctx, 3);
    lw(v0, t0, sj::kUsed);
    a0 = 0x7C0000;
    if (v0 == 0) {
        // 0x00561df4
        charge(ctx, 6);
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26848);
        a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00561e10
    charge(ctx, 2);
    v0 = 1;
    if (a1 != 0) {
        // 0x00561e28
        charge(ctx, 2);
        if (a1 != v0) {
            lw(v0, t0, sjmem::kErrFn);
            // 0x00561e70
            charge(ctx, 3);
            sw(zero, a3, sj::kChunkData);
            sw(zero, a3, sj::kChunkSize);
            if (v0 != 0) {
                // 0x00561e7c
                charge(ctx, 3);
                lw(a0, t0, sjmem::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x561E80u, v0.u());
            }
        } else {
            // 0x00561e30
            charge(ctx, 15);
            lw(v0, t0, sjmem::kLeft);
            lw(a1, t0, sjmem::kBuf);
            v1 = slt(v0, a2);
            if (v1 == 0) v0 = a2;
            sw(v0, a3, sj::kChunkSize);
            lw(a0, t0, sjmem::kOffset);
            lw(v1, t0, sjmem::kLeft);
            v0 = addu(a0, v0);
            a1 = addu(a1, a0);
            sw(v0, t0, sjmem::kOffset);
            sw(a1, a3, sj::kChunkData);
            lw(v0, a3, sj::kChunkSize);
            v1 = subu(v1, v0);
            sw(v1, t0, sjmem::kLeft);
        }
    } else {
        // 0x00561e18
        charge(ctx, 3);
        sw(zero, a3, sj::kChunkData);
        sw(zero, a3, sj::kChunkSize);
    }
    // 0x00561e88 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561E98 sub_561E98 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Put a chunk (locked). [SJMEM_PutChunk]
void sub_561E98(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561e98
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x561EB4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x561EC4u, gen::fn_sub_561EE8_00561ee8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00561EE8 sub_561EE8 -- 156 bytes; frame 0x10: ra sp+0x0
// Put a chunk: lines 0 / 1 accept and drop it; another line clears it and calls the error callback. [sjmem_PutChunk]
void sub_561EE8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561ee8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00561ef4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26864);  // "E2004090243"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00561f10
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    if (v0 == 0) {
        // 0x00561f1c
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26880);  // "E2004090244"
        a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    lw(v0, a2, sj::kChunkSize);
    // 0x00561f38
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (i64(v0) > 0) {
        // 0x00561f40
        charge(ctx, 3);
        lw(v0, a2, sj::kChunkData);
        if (v0 != 0) {
            // 0x00561f4c
            charge(ctx, 2);
            v0 = 1;
            if (a1 != 0) {
                // 0x00561f54
                charge(ctx, 2);
                if (a1 != v0) {
                    // 0x00561f5c
                    charge(ctx, 4);
                    lw(v0, a0, sjmem::kErrFn);
                    sw(zero, a2, sj::kChunkData);
                    sw(zero, a2, sj::kChunkSize);
                    if (v0 != 0) {
                        // 0x00561f6c
                        charge(ctx, 4);
                        lw(a0, a0, sjmem::kErrObj);
                        a1 = si(-3);
                        jalr(ctx, 0x561F70u, v0.u());
                        ld(ra, sp, 0x0);
                    }
                }
            }
        }
    }
    // 0x00561f7c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00561F88 sub_561F88 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Unget a chunk (locked). [SJMEM_UngetChunk]
void sub_561F88(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561f88
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x561FA4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x561FB4u, gen::fn_sub_561FD8_00561fd8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00561FD8 sub_561FD8 -- 252 bytes; frame 0x10: ra sp+0x0
// Unget a chunk on line 1: step the read offset back (an out-of-order chunk calls the error callback).
// [sjmem_UngetChunk]
void sub_561FD8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561fd8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    sd(ra, sp, 0x0);
    v1 = a2;
    if (t0 == 0) {
        // 0x00561fec
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26896);  // "E2004090245"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    // 0x00562008
    charge(ctx, 3);
    lw(v0, t0, sj::kUsed);
    if (v0 == 0) {
        // 0x00562014
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 26912);  // "E2004090246"
        a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_561828_00561828(ctx);  // tail call
        return;
    }
    lw(a2, v1, sj::kChunkSize);
    // 0x00562030
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (i64(a2) > 0) {
        // 0x00562038
        charge(ctx, 3);
        lw(t1, v1, sj::kChunkData);
        if (t1 != 0) {
            // 0x00562044
            charge(ctx, 2);
            v0 = 1;
            if (a1 != 0) {
                // 0x0056204c
                charge(ctx, 2);
                if (a1 != v0) {
                    lw(v0, t0, sjmem::kErrFn);
                    // 0x005620b0
                    charge(ctx, 3);
                    sw(zero, v1, sj::kChunkData);
                    sw(zero, v1, sj::kChunkSize);
                    if (v0 != 0) {
                        // 0x005620bc
                        charge(ctx, 3);
                        lw(a0, t0, sjmem::kErrObj);
                        a1 = si(-3);
                        jalr(ctx, 0x5620C0u, v0.u());
                    }
                    // 0x005620c8
                    charge(ctx, 1);
                    ld(ra, sp, 0x0);
                } else {
                    // 0x00562054
                    charge(ctx, 15);
                    lw(a0, t0, sjmem::kOffset);
                    lw(a1, t0, sjmem::kLeft);
                    a0 = subu(a0, a2);
                    lw(a2, t0, sjmem::kBuf);
                    v0 = slti(a0, 0);
                    lw(a3, t0, sjmem::kBufSize);
                    if (v0 != 0) a0 = 0;
                    a2 = subu(t1, a2);
                    sw(a0, t0, sjmem::kOffset);
                    lw(v0, v1, sj::kChunkSize);
                    a1 = addu(a1, v0);
                    v1 = slt(a3, a1);
                    if (v1 != 0) a1 = a3;
                    sw(a1, t0, sjmem::kLeft);
                    if (a0 != a2) {
                        goto L_00562090;
                    }
                }
                // 0x005620cc (the shared epilogue, written out on this path)
                charge(ctx, 2);
                sp = addiu(sp, 0x10);
                return;
            }
        L_00562090:
            charge(ctx, 3);
            lw(v0, t0, sjmem::kErrFn);
            if (v0 == 0) {
                ld(ra, sp, 0x0);
            } else {
                // 0x0056209c
                charge(ctx, 5);
                lw(a0, t0, sjmem::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x5620A0u, v0.u());
                ld(ra, sp, 0x0);
            }
        }
    }
    // 0x005620cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005620D8 sub_5620D8 -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Is a chunk of n bytes available (locked). [SJMEM_IsGetChunk]
void sub_5620D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005620d8
    enter(ctx, 26);  // entry check point + this block's cycles
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
    jal(ctx, 0x5620FCu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x562110u, gen::fn_sub_562140_00562140);
    s0 = v0;
    jal(ctx, 0x562118u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00562140 sub_562140 -- 208 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Is a chunk of n bytes available: the size that can be got and whether it is n. [sjmem_IsGetChunk]
void sub_562140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562140
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    if (a0 == 0) {
        // 0x00562160
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 26928);  // "E2004090247"
        a1 = addiu(a1, 26656);  // " : NULL pointer is specified."
        goto L_00562194;
    }
    // 0x00562178
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    if (v0 != 0) {
        // 0x005621a8
        charge(ctx, 2);
        s0 = 0;
        if (a1 != 0) {
            // 0x005621b0
            charge(ctx, 3);
            v0 = 1;
            if (a1 != v0) {
                lw(v0, a0, sjmem::kErrFn);
                // 0x005621d8
                charge(ctx, 2);
                s0 = 0;
                if (v0 != 0) {
                    // 0x005621e0
                    charge(ctx, 3);
                    lw(a0, a0, sjmem::kErrObj);
                    a1 = si(-3);
                    jalr(ctx, 0x5621E4u, v0.u());
                }
            } else {
                // 0x005621bc
                charge(ctx, 4);
                lw(a0, a0, sjmem::kLeft);
                v0 = slt(a0, s1);
                s0 = s1;
                if (v0 != 0) {
                    // 0x005621cc
                    charge(ctx, 2);
                    s0 = a0;
                }
            }
        }
        // 0x005621ec
        charge(ctx, 3);
        v0 = s0 ^ s1;
        sw(s0, s2, 0);
        v0 = sltiu(v0, 1);
    } else {
        // 0x00562184
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 26944);  // "E2004090248"
        a1 = addiu(a1, 26704);  // " : Specified handle is invalid."
    L_00562194:
        charge(ctx, 4);
        jal(ctx, 0x562194u, gen::fn_sub_561828_00561828);
        v0 = 0;
    }
    // 0x005621f8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00562210 _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3 -- 8 bytes; leaf frame (no stack)
// An SJRBF handle's line-0 position (+20). [SJRBF_GetWritePos]
void _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00562210
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, sjrbf::kPos0);
}

// 0x00562218 width__CQ24_STL8ios_base_0 -- 8 bytes; leaf frame (no stack)
// An SJRBF handle's line-1 position (+24). [SJRBF_GetReadPos]
void width__CQ24_STL8ios_base_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00562218
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, sjrbf::kPos1);
}

// 0x00562220 sub_562220 -- 28 bytes; frame 0x10: ra sp+0x0
// The SJRBF handles' default error callback ("SJRBF Error"). [sjrbf_DefaultErrFn]
void sub_562220(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562220
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 26976);  // "SJRBF Error"
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617F0_005617f0(ctx);  // tail call
}

// 0x00562240 sub_562240 -- 68 bytes; frame 0x50: s0 sp+0x40, ra sp+0x48
// SJRBF error: code + message joined, then reported. [sjrbf_Error]
void sub_562240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562240
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = a0;
    sd(s0, sp, 0x40);
    s0 = a1;
    a0 = sp;
    sd(ra, sp, 0x48);
    a1 = v0;
    jal(ctx, 0x562258u, gen::fn_strcpy_00524270);
    a0 = sp;
    a1 = s0;
    jal(ctx, 0x562264u, gen::fn_strcat_00523e68);
    a0 = sp;
    jal(ctx, 0x56226Cu, gen::fn_sub_5617F0_005617f0);
    ld(s0, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00562288 sub_562288 -- 44 bytes; frame 0x10: ra sp+0x0
// SJRBF init (locked). [SJRBF_Init]
void sub_562288(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00562288
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x562290u, gen::fn_sub_561758_00561758);
    jal(ctx, 0x562298u, gen::fn_sub_5617C0_005617c0);
    jal(ctx, 0x5622A0u, gen::fn_sub_5622B8_005622b8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005622B8 sub_5622B8 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SJRBF pool init: the first call clears the 256 handles. [sjrbf_InitPool]
void sub_5622B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005622b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -13160);  // &0x7ACC98
    lw(v0, s0, 0);  // 0x7ACC98
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x005622d4
        charge(ctx, 6);
        a0 = 0x7B0000;
        a1 = 0;
        a0 = addiu(a0, -13152);  // &0x7ACCA0
        a2 = 16384;
        jal(ctx, 0x5622E0u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x005622ec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00562308 sub_562308 -- 92 bytes, 2 chunks; frame 0x10: ra sp+0x0
// SJRBF finish (locked). [SJRBF_Finish]
void sub_562308(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562308
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x562310u, gen::fn_sub_5617C0_005617c0);
    jal(ctx, 0x562318u, gen::fn_sub_562338_00562338);
    jal(ctx, 0x562320u, gen::fn_sub_5617D8_005617d8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00561790
    charge(ctx, 8);
    v0 = 0x7B0000;
    v0 = addiu(v0, -14472);  // &0x7AC778
    lw(v1, v0, 0);  // 0x7AC778
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x7AC778
    lw(a0, v0, 0);  // 0x7AC778
    v0 = 0x7B0000;
    if (a0 == 0) {
        // 0x005617b0
        charge(ctx, 2);
        v0 = addiu(v0, -14480);
        sw(zero, v0, 0);
    }
    // 0x005617b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00562338 sub_562338 -- 76 bytes; frame 0x10: ra sp+0x0
// SJRBF pool finish: the last call clears the 256 handles. [sjrbf_FinishPool]
void sub_562338(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562338
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7B0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, -13160);  // &0x7ACC98
    lw(v0, v1, 0);  // 0x7ACC98
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7ACC98
    if (v0 != 0) {
        // 0x00562378
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00562358
    charge(ctx, 7);
    a0 = 0x7B0000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, -13152);  // &0x7ACCA0
    a2 = 16384;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00562388 sub_562388 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Create an SJRBF handle (locked): buffer, size, extra (mirror) size. [SJRBF_Create]
void sub_562388(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562388
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x5623A4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x5623B4u, gen::fn_sub_5623E0_005623e0);
    s0 = v0;
    jal(ctx, 0x5623BCu, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005623E0 sub_5623E0 -- 204 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Take a free SJRBF handle, fill it and reset it. [sjrbf_Create]
void sub_5623E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005623e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0x7B0000;
    v0 = addiu(a3, -13152);  // &0x7ACCA0
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    v1 = addiu(v0, 4);  // &0x7ACCA4
    t2 = a0;
    a0 = 0;
    lw(v0, v1, 0);  // 0x7ACCA4
    t1 = a1;
    t0 = a2;
    if (v0 != 0) {
        // 0x00562410
        charge(ctx, 2);
        a0 = addiu(a0, 1);
        for (;;) {
            // 0x00562418
            charge(ctx, 3);
            v0 = slti(a0, 256);
            v1 = addiu(v1, 64);
            if (v0 != 0) {
                // 0x00562424
                charge(ctx, 6);
                lw(v0, v1, 0);
                if (v0 != 0) {
                    a0 = addiu(a0, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0056243c
    charge(ctx, 3);
    v0 = 256;
    s0 = 0;
    if (a0 != v0) {
        // 0x00562448
        charge(ctx, 20);
        a0 = sll(a0, 6);
        v0 = addiu(a3, -13152);
        v1 = 0x7B0000;
        a1 = 0x7C0000;
        a2 = 0x560000;
        s0 = addu(a0, v0);
        v1 = addiu(v1, -13208);  // &0x7ACC68
        a1 = addiu(a1, 26960);  // &0x7C6950
        a2 = addiu(a2, 8736);  // &sub_562220
        v0 = 1;
        sw(v0, s0, sj::kUsed);
        a0 = s0;
        sw(v1, s0, sj::kVtbl);
        sw(t2, s0, sjrbf::kBuf);
        sw(t1, s0, sjrbf::kBufSize);
        sw(t0, s0, sjrbf::kXtrSize);
        sw(a1, s0, sj::kUuid);
        sw(a2, s0, sjrbf::kErrFn);
        link(ctx, 0x562490u);  // $ra first: the delay slot below depends on it
        sw(s0, s0, sjrbf::kErrObj);
        call(ctx, gen::fn_sub_5625B0_005625b0);
    }
    // 0x00562498 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005624B0 sub_5624B0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroy an SJRBF handle (locked). [SJRBF_Destroy]
void sub_5624B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005624b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5624BCu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x5624C4u, gen::fn_sub_5624E0_005624e0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005624E0 sub_5624E0 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroy: zero the 64 bytes. [sjrbf_Destroy]
void sub_5624E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005624e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005624f4
        charge(ctx, 8);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 26992);  // "E2004090201"
        ld(ra, sp, 0x8);
        a1 = addiu(a1, 27008);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    // 0x00562518
    charge(ctx, 3);
    lw(v0, s0, sj::kUsed);
    a1 = 0;
    if (v0 != 0) {
        // 0x00562548
        charge(ctx, 7);
        a2 = 64;
        jal(ctx, 0x562548u, gen::fn_memset_00521408);
        sw(zero, s0, sj::kUsed);
        ld(ra, sp, 0x8);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00562524
    charge(ctx, 8);
    a0 = 0x7C0000;
    a1 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 27040);  // "E2004090202"
    ld(ra, sp, 0x8);
    a1 = addiu(a1, 27056);  // " : Specified handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_562240_00562240(ctx);  // tail call
}

// 0x00562568 sub_562568 -- 8 bytes; leaf frame (no stack)
// The uuid pointer (+8). [SJRBF_GetUuid]
void sub_562568(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00562568
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, sj::kUuid);
}

// 0x00562570 sub_562570 -- 12 bytes; leaf frame (no stack)
// Store the error callback and its object (+56 / +60). [SJRBF_EntryErrFunc]
void sub_562570(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00562570
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, sjrbf::kErrObj);
    sw(a1, a0, sjrbf::kErrFn);
}

// 0x00562580 sub_562580 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Reset an SJRBF handle (locked). [SJRBF_Reset]
void sub_562580(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562580
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56258Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x562594u, gen::fn_sub_5625B0_005625b0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005625B0 sub_5625B0 -- 124 bytes; frame 0x10: ra sp+0x0
// Reset: free = size, data = 0, both positions and the three counters 0. [sjrbf_Reset]
void sub_5625B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005625b0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x005625bc
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27088);  // "E2004090207"
        a1 = addiu(a1, 27008);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    // 0x005625d8
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    if (v0 == 0) {
        // 0x005625e4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27104);  // "E2004090208"
        a1 = addiu(a1, 27056);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    lw(v0, a0, sjrbf::kBufSize);
    // 0x00562600
    charge(ctx, 11);
    ld(ra, sp, 0x0);
    sw(zero, a0, sjrbf::kPut1);
    sw(v0, a0, sjrbf::kFree);
    sw(zero, a0, sjrbf::kData);
    sw(zero, a0, sjrbf::kPos0);
    sw(zero, a0, sjrbf::kPos1);
    sw(zero, a0, sjrbf::kGot0);
    sw(zero, a0, sjrbf::kPut0);
    sw(zero, a0, sjrbf::kGot1);
    sp = addiu(sp, 0x10);
}

// 0x00562630 sub_562630 -- 76 bytes; frame 0x10: ra sp+0x0
// Bytes on a line: line 0 = free space, line 1 = data; another line calls the error callback. [SJRBF_GetNumData]
void sub_562630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562630
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a1 != v0) {
        // 0x00562648
        charge(ctx, 2);
        if (a1 != 0) {
            lw(v0, a0, sjrbf::kErrFn);
            // 0x00562658
            charge(ctx, 2);
            if (v0 == 0) {
                v0 = 0;
            } else {
                // 0x00562660
                charge(ctx, 4);
                lw(a0, a0, sjrbf::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x562664u, v0.u());
                v0 = 0;
            }
        } else {
            // 0x00562650
            charge(ctx, 2);
            lw(v0, a0, sjrbf::kFree);
        }
    } else {
        // 0x00562640
        charge(ctx, 2);
        lw(v0, a0, sjrbf::kData);
    }
    // 0x00562670 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00562680 sub_562680 -- 92 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Get a chunk (locked). [SJRBF_GetChunk]
void sub_562680(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562680
    enter(ctx, 23);  // entry check point + this block's cycles
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
    jal(ctx, 0x5626A4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x5626B8u, gen::fn_sub_5626E0_005626e0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005626E0 sub_5626E0 -- 412 bytes; frame 0x10: ra sp+0x0
// Get a chunk from line 0 (free) or 1 (data): min(n, line bytes, bytes to the end + extra) at buffer + position; the
// position advances modulo the size. [sjrbf_GetChunk]
// Line 0 hands out free space at the write position, line 1 data at the read position; a chunk may run past the
// buffer's end into the extra area (the position wraps modulo the size).
void sub_5626E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005626e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    sd(ra, sp, 0x0);
    t1 = a2;
    if (t0 == 0) {
        // 0x005626f4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27120);  // "E2004090211"
        a1 = addiu(a1, 27008);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    // 0x00562710
    charge(ctx, 3);
    lw(v0, t0, sj::kUsed);
    if (v0 == 0) {
        // 0x0056271c
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27136);  // "E2004090212"
        a1 = addiu(a1, 27056);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    lw(a0, t0, sjrbf::kBufSize);
    // 0x00562738
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00562740
        charge(ctx, 6);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27152);  // "E2004090219"
        a1 = addiu(a1, 27168);  // " : Illegal buffer size."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    // 0x00562758
    charge(ctx, 2);
    v0 = 1;
    if (a1 != 0) {
        // 0x005627d8
        charge(ctx, 2);
        if (a1 != v0) {
            lw(v0, t0, sjrbf::kErrFn);
            // 0x00562858
            charge(ctx, 3);
            sw(zero, a3, sj::kChunkData);
            sw(zero, a3, sj::kChunkSize);
            if (v0 != 0) {
                // 0x00562864
                charge(ctx, 3);
                lw(a0, t0, sjrbf::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x562868u, v0.u());
            }
        } else {
            // 0x005627e0
            charge(ctx, 19);
            lw(v0, t0, sjrbf::kPos1);
            lw(v1, t0, sjrbf::kXtrSize);
            lw(a1, t0, sjrbf::kData);
            v0 = subu(a0, v0);
            v0 = addu(v0, v1);
            lw(a2, t0, sjrbf::kBuf);
            v1 = slt(a1, v0);
            if (v1 != 0) v0 = a1;
            a0 = slt(v0, t1);
            if (a0 == 0) v0 = t1;
            sw(v0, a3, sj::kChunkSize);
            lw(a0, t0, sjrbf::kPos1);
            lw(v1, t0, sjrbf::kBufSize);
            v0 = addu(a0, v0);
            a2 = addu(a2, a0);
            div(v0, v1);
            sw(a2, a3, sj::kChunkData);
            if (v1 == 0) {
                brk(ctx, 0x562828u, 0x7u);
            }
            // 0x0056282c
            charge(ctx, 11);
            lw(a0, t0, sjrbf::kData);
            lw(v1, t0, sjrbf::kGot1);
            mfhi(a1);
            sw(a1, t0, sjrbf::kPos1);
            lw(v0, a3, sj::kChunkSize);
            a0 = subu(a0, v0);
            sw(a0, t0, sjrbf::kData);
            lw(v0, a3, sj::kChunkSize);
            v1 = addu(v1, v0);
            sw(v1, t0, sjrbf::kGot1);
        }
    } else {
        // 0x00562760
        charge(ctx, 19);
        lw(v0, t0, sjrbf::kPos0);
        lw(v1, t0, sjrbf::kXtrSize);
        lw(a1, t0, sjrbf::kFree);
        v0 = subu(a0, v0);
        v0 = addu(v0, v1);
        lw(a2, t0, sjrbf::kBuf);
        v1 = slt(a1, v0);
        if (v1 != 0) v0 = a1;
        a0 = slt(v0, t1);
        if (a0 == 0) v0 = t1;
        sw(v0, a3, sj::kChunkSize);
        lw(a0, t0, sjrbf::kPos0);
        lw(v1, t0, sjrbf::kBufSize);
        v0 = addu(a0, v0);
        a2 = addu(a2, a0);
        div(v0, v1);
        sw(a2, a3, sj::kChunkData);
        if (v1 == 0) {
            brk(ctx, 0x5627A8u, 0x7u);
        }
        // 0x005627ac
        charge(ctx, 11);
        lw(a0, t0, sjrbf::kFree);
        lw(v1, t0, sjrbf::kGot0);
        mfhi(a1);
        sw(a1, t0, sjrbf::kPos0);
        lw(v0, a3, sj::kChunkSize);
        a0 = subu(a0, v0);
        sw(a0, t0, sjrbf::kFree);
        lw(v0, a3, sj::kChunkSize);
        v1 = addu(v1, v0);
        sw(v1, t0, sjrbf::kGot0);
    }
    // 0x00562870 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00562880 sub_562880 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Put a chunk (locked). [SJRBF_PutChunk]
void sub_562880(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562880
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x56289Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x5628ACu, gen::fn_sub_5628D0_005628d0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005628D0 sub_5628D0 -- 380 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Put a chunk on line 0 (free += n) or 1 (data += n); a chunk on line 1 that ran into the extra area or the buffer
// start is mirrored (memcpy) to the other side. [sjrbf_PutChunk]
// Line 1 (data written into a free chunk): the part of the chunk inside the first `extra` bytes is copied to the
// extra area, the part that ran into the extra area is copied back to the start, so both views of the ring stay
// equal.
void sub_5628D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005628d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x005628f0
        charge(ctx, 9);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 27192);  // "E2004090213"
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 27008);  // " : NULL pointer is specified."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    // 0x00562918
    charge(ctx, 3);
    lw(v0, s0, sj::kUsed);
    if (v0 == 0) {
        // 0x00562924
        charge(ctx, 9);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 27208);  // "E2004090214"
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 27056);  // " : Specified handle is invalid."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    lw(t0, s1, sj::kChunkSize);
    // 0x00562948
    charge(ctx, 2);
    t1 = t0;
    if (i64(t0) > 0) {
        // 0x00562950
        charge(ctx, 3);
        lw(a1, s1, sj::kChunkData);
        v0 = 1;
        if (a1 != 0) {
            // 0x0056295c
            charge(ctx, 2);
            if (v1 != v0) {
                // 0x005629f8
                charge(ctx, 2);
                if (v1 != 0) {
                    lw(v0, s0, sjrbf::kErrFn);
                    // 0x00562a20
                    charge(ctx, 3);
                    sw(zero, s1, sj::kChunkData);
                    sw(zero, s1, sj::kChunkSize);
                    if (v0 != 0) {
                        // 0x00562a2c
                        charge(ctx, 3);
                        lw(a0, s0, sjrbf::kErrObj);
                        a1 = si(-3);
                        jalr(ctx, 0x562A30u, v0.u());
                    }
                } else {
                    // 0x00562a00
                    charge(ctx, 8);
                    lw(v0, s0, sjrbf::kFree);
                    lw(a0, s0, sjrbf::kPut0);
                    v0 = addu(v0, t0);
                    sw(v0, s0, sjrbf::kFree);
                    lw(v1, s1, sj::kChunkSize);
                    a0 = addu(a0, v1);
                    sw(a0, s0, sjrbf::kPut0);
                }
            } else {
                // 0x00562964
                charge(ctx, 6);
                lw(a3, s0, sjrbf::kBuf);
                lw(a2, s0, sjrbf::kXtrSize);
                v1 = subu(a1, a3);
                v0 = slt(v1, a2);
                lw(a0, s0, sjrbf::kBufSize);
                if (v0 != 0) {
                    // 0x0056297c
                    charge(ctx, 11);
                    a2 = subu(a2, v1);
                    v0 = slt(t0, a2);
                    a0 = addu(a0, v1);
                    if (v0 != 0) a2 = t0;
                    a0 = addu(a3, a0);
                    jal(ctx, 0x56298Cu, gen::fn_memcpy_00521250);
                    lw(t1, s1, sj::kChunkSize);
                    lw(a1, s1, sj::kChunkData);
                    lw(a3, s0, sjrbf::kBuf);
                    v1 = subu(a1, a3);
                    lw(a0, s0, sjrbf::kBufSize);
                }
                // 0x005629a8
                charge(ctx, 4);
                v1 = addu(v1, t1);
                v0 = slt(a0, v1);
                if (v0 == 0) {
                    lw(v0, s0, sjrbf::kData);
                } else {
                    // 0x005629b8
                    charge(ctx, 9);
                    a2 = subu(v1, a0);
                    a0 = a3;
                    v0 = slt(t1, a2);
                    if (v0 != 0) a2 = t1;
                    a1 = subu(v1, a2);
                    a1 = addu(a0, a1);
                    jal(ctx, 0x5629CCu, gen::fn_memcpy_00521250);
                    lw(t1, s1, sj::kChunkSize);
                    lw(v0, s0, sjrbf::kData);
                }
                // 0x005629dc
                charge(ctx, 7);
                lw(a0, s0, sjrbf::kPut1);
                v0 = addu(v0, t1);
                sw(v0, s0, sjrbf::kData);
                lw(v1, s1, sj::kChunkSize);
                a0 = addu(a0, v1);
                sw(a0, s0, sjrbf::kPut1);
            }
        }
    }
    // 0x00562a38 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00562A50 sub_562A50 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Unget a chunk (locked). [SJRBF_UngetChunk]
void sub_562A50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562a50
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x562A6Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x562A7Cu, gen::fn_sub_562AA0_00562aa0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00562AA0 sub_562AA0 -- 476 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Unget a chunk: the line's position steps back by n (modulo the size) when the chunk was the last one got.
// [sjrbf_UngetChunk]
// The position steps back only when (position - size) mod buffer size is the chunk's offset (the chunk was the last
// one got); otherwise the error callback. The running total is reduced either way.
void sub_562AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562aa0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x00562abc
        charge(ctx, 9);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 27224);  // "E2004090215"
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 27008);  // " : NULL pointer is specified."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    // 0x00562ae0
    charge(ctx, 3);
    lw(v0, s0, sj::kUsed);
    if (v0 == 0) {
        // 0x00562aec
        charge(ctx, 9);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 27240);  // "E2004090216"
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 27056);  // " : Specified handle is invalid."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    lw(a2, s0, sjrbf::kBufSize);
    // 0x00562b10
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x00562b18
        charge(ctx, 9);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 27256);  // "E2004090220"
        ld(s1, sp, 0x8);
        a1 = addiu(a1, 27168);  // " : Illegal buffer size."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_562240_00562240(ctx);  // tail call
        return;
    }
    lw(a3, s1, sj::kChunkSize);
    // 0x00562b40
    charge(ctx, 2);
    if (i64(a3) <= 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00562b48
        charge(ctx, 3);
        lw(t0, s1, sj::kChunkData);
        if (t0 == 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00562b54
            charge(ctx, 2);
            v0 = 1;
            if (a1 != 0) {
                // 0x00562bd0
                charge(ctx, 2);
                if (a1 != v0) {
                    lw(v0, s0, sjrbf::kErrFn);
                    // 0x00562c50
                    charge(ctx, 3);
                    sw(zero, s1, sj::kChunkData);
                    sw(zero, s1, sj::kChunkSize);
                    if (v0 != 0) {
                        // 0x00562c5c
                        charge(ctx, 3);
                        lw(a0, s0, sjrbf::kErrObj);
                        a1 = si(-3);
                        jalr(ctx, 0x562C60u, v0.u());
                    }
                } else {
                    // 0x00562bd8
                    charge(ctx, 3);
                    lw(v0, s0, sjrbf::kPos1);
                    if (a2 == 0) {
                        brk(ctx, 0x562BE0u, 0x7u);
                    }
                    // 0x00562be4
                    charge(ctx, 10);
                    lw(a0, s0, sjrbf::kBuf);
                    v0 = addu(v0, a2);
                    v0 = subu(v0, a3);
                    a0 = subu(t0, a0);
                    div(v0, a2);
                    div1(a0, a2);
                    mfhi(v0);
                    mfhi1(v1);
                    if (v0 == v1) {
                        // 0x00562c0c
                        charge(ctx, 6);
                        sw(v0, s0, sjrbf::kPos1);
                        lw(v0, s0, sjrbf::kData);
                        lw(v1, s1, sj::kChunkSize);
                        v0 = addu(v0, v1);
                        sw(v0, s0, sjrbf::kData);
                        goto L_00562c3c;
                    }
                    lw(v0, s0, sjrbf::kErrFn);
                    // 0x00562c28
                    charge(ctx, 2);
                    if (v0 == 0) {
                        lw(v0, s0, sjrbf::kGot1);
                    } else {
                        // 0x00562c30
                        charge(ctx, 3);
                        lw(a0, s0, sjrbf::kErrObj);
                        a1 = si(-3);
                        jalr(ctx, 0x562C34u, v0.u());
                    L_00562c3c:
                        charge(ctx, 2);
                        lw(a3, s1, sj::kChunkSize);
                        lw(v0, s0, sjrbf::kGot1);
                    }
                    // 0x00562c44
                    charge(ctx, 3);
                    v0 = subu(v0, a3);
                    sw(v0, s0, sjrbf::kGot1);
                }
            } else {
                // 0x00562b5c
                charge(ctx, 3);
                lw(v0, s0, sjrbf::kPos0);
                if (a2 == 0) {
                    brk(ctx, 0x562B64u, 0x7u);
                }
                // 0x00562b68
                charge(ctx, 10);
                lw(v1, s0, sjrbf::kBuf);
                v0 = addu(v0, a2);
                v0 = subu(v0, a3);
                v1 = subu(t0, v1);
                div(v0, a2);
                div1(v1, a2);
                mfhi(a0);
                mfhi1(a1);
                if (a0 == a1) {
                    // 0x00562b90
                    charge(ctx, 6);
                    sw(a0, s0, sjrbf::kPos0);
                    lw(v0, s0, sjrbf::kFree);
                    lw(v1, s1, sj::kChunkSize);
                    v0 = addu(v0, v1);
                    sw(v0, s0, sjrbf::kFree);
                    goto L_00562bbc;
                }
                lw(v0, s0, sjrbf::kErrFn);
                // 0x00562ba8
                charge(ctx, 2);
                if (v0 == 0) {
                    lw(v0, s0, sjrbf::kGot0);
                } else {
                    // 0x00562bb0
                    charge(ctx, 3);
                    lw(a0, s0, sjrbf::kErrObj);
                    a1 = si(-3);
                    jalr(ctx, 0x562BB4u, v0.u());
                L_00562bbc:
                    charge(ctx, 2);
                    lw(a3, s1, sj::kChunkSize);
                    lw(v0, s0, sjrbf::kGot0);
                }
                // 0x00562bc4
                charge(ctx, 3);
                v0 = subu(v0, a3);
                sw(v0, s0, sjrbf::kGot0);
            }
            // 0x00562c68
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00562c6c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00562C80 sub_562C80 -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Is a chunk of n bytes available (locked). [SJRBF_IsGetChunk]
void sub_562C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562c80
    enter(ctx, 26);  // entry check point + this block's cycles
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
    jal(ctx, 0x562CA4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x562CB8u, gen::fn_sub_562CE8_00562ce8);
    s0 = v0;
    jal(ctx, 0x562CC0u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00562CE8 sub_562CE8 -- 248 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Is a chunk of n bytes available: min(line bytes, bytes to the end + extra, n) and whether it is n.
// [sjrbf_IsGetChunk]
void sub_562CE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562ce8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    if (a0 == 0) {
        // 0x00562d08
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27272);  // "E2004090217"
        a1 = addiu(a1, 27008);  // " : NULL pointer is specified."
        goto L_00562d3c;
    }
    // 0x00562d20
    charge(ctx, 3);
    lw(v0, a0, sj::kUsed);
    if (v0 != 0) {
        // 0x00562d50
        charge(ctx, 2);
        v0 = 1;
        if (a1 == 0) {
            // 0x00562d58
            charge(ctx, 6);
            lw(v0, a0, sjrbf::kPos0);
            lw(v1, a0, sjrbf::kBufSize);
            lw(a1, a0, sjrbf::kXtrSize);
            v1 = subu(v1, v0);
            lw(a0, a0, sjrbf::kFree);
            goto L_00562d8c;
        }
        // 0x00562d70
        charge(ctx, 2);
        if (a1 != v0) {
            lw(v0, a0, sjrbf::kErrFn);
            // 0x00562da8
            charge(ctx, 2);
            s0 = 0;
            if (v0 != 0) {
                // 0x00562db0
                charge(ctx, 3);
                lw(a0, a0, sjrbf::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x562DB4u, v0.u());
            }
        } else {
            // 0x00562d78
            charge(ctx, 5);
            lw(v0, a0, sjrbf::kPos1);
            lw(v1, a0, sjrbf::kBufSize);
            lw(a1, a0, sjrbf::kXtrSize);
            v1 = subu(v1, v0);
            lw(a0, a0, sjrbf::kData);
        L_00562d8c:
            charge(ctx, 6);
            s0 = addu(v1, a1);
            v0 = slt(a0, s0);
            if (v0 != 0) s0 = a0;
            v1 = slt(s0, s1);
            if (v1 == 0) s0 = s1;
        }
        // 0x00562dbc
        charge(ctx, 3);
        v0 = s0 ^ s1;
        sw(s0, s2, 0);
        v0 = sltiu(v0, 1);
    } else {
        // 0x00562d2c
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27288);  // "E2004090218"
        a1 = addiu(a1, 27056);  // " : Specified handle is invalid."
    L_00562d3c:
        charge(ctx, 4);
        jal(ctx, 0x562D3Cu, gen::fn_sub_562240_00562240);
        v0 = 0;
    }
    // 0x00562dc8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00562DE0 sub_562DE0 -- 8 bytes; leaf frame (no stack)
// Word +28 of a stream record (callers 0x541E28 / 0x542438).
void sub_562DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00562de0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 28);
}

// 0x00562DE8 sub_562DE8 -- 8 bytes; leaf frame (no stack)
// Word +32 of a stream record.
void sub_562DE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00562de8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 32);
}

// 0x00562DF0 sub_562DF0 -- 8 bytes; leaf frame (no stack)
// Word +36 of a stream record.
void sub_562DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00562df0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 36);
}

// 0x00562DF8 sub_562DF8 -- 24 bytes; leaf frame (no stack)
// Store a word of the 2-column table at +40 of a stream record ([2 * row + column]).
void sub_562DF8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00562df8
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = sll(a1, 1);
    a1 = addu(a1, a2);
    a1 = sll(a1, 2);
    a1 = addu(a1, a0);
    sw(a3, a1, 40);
}

// 0x00562E10 sub_562E10 -- 24 bytes; leaf frame (no stack)
// Read a word of the 2-column table at +40 of a stream record.
void sub_562E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00562e10
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = sll(a1, 1);
    a1 = addu(a1, a2);
    a1 = sll(a1, 2);
    a1 = addu(a1, a0);
    lw(v0, a1, 40);
}

// 0x00562E28 sub_562E28 -- 28 bytes; frame 0x10: ra sp+0x0
// The SJUNI handles' default error callback ("SJUNI Error"). [sjuni_DefaultErrFn]
void sub_562E28(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562e28
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 27320);  // "SJUNI Error"
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617F0_005617f0(ctx);  // tail call
}

// 0x00562E48 sub_562E48 -- 68 bytes; frame 0x50: s0 sp+0x40, ra sp+0x48
// SJUNI error: code + message joined, then reported. [sjuni_Error]
void sub_562E48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562e48
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = a0;
    sd(s0, sp, 0x40);
    s0 = a1;
    a0 = sp;
    sd(ra, sp, 0x48);
    a1 = v0;
    jal(ctx, 0x562E60u, gen::fn_strcpy_00524270);
    a0 = sp;
    a1 = s0;
    jal(ctx, 0x562E6Cu, gen::fn_strcat_00523e68);
    a0 = sp;
    jal(ctx, 0x562E74u, gen::fn_sub_5617F0_005617f0);
    ld(s0, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x00562E90 sub_562E90 -- 44 bytes; frame 0x10: ra sp+0x0
// SJUNI init (locked). [SJUNI_Init]
void sub_562E90(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00562e90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x562E98u, gen::fn_sub_561758_00561758);
    jal(ctx, 0x562EA0u, gen::fn_sub_5617C0_005617c0);
    jal(ctx, 0x562EA8u, gen::fn_sub_562EC0_00562ec0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00562EC0 sub_562EC0 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SJUNI pool init: the first call clears the 64 handles. [sjuni_InitPool]
void sub_562EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562ec0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 3280);  // &0x7B0CD0
    lw(v0, s0, 0);  // 0x7B0CD0
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x00562edc
        charge(ctx, 6);
        a0 = 0x7B0000;
        a1 = 0;
        a0 = addiu(a0, 3288);  // &0x7B0CD8
        a2 = 3072;
        jal(ctx, 0x562EE8u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x00562ef4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00562F10 sub_562F10 -- 92 bytes, 2 chunks; frame 0x10: ra sp+0x0
// SJUNI finish (locked). [SJUNI_Finish]
void sub_562F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562f10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x562F18u, gen::fn_sub_5617C0_005617c0);
    jal(ctx, 0x562F20u, gen::fn_sub_562F40_00562f40);
    jal(ctx, 0x562F28u, gen::fn_sub_5617D8_005617d8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00561790
    charge(ctx, 8);
    v0 = 0x7B0000;
    v0 = addiu(v0, -14472);  // &0x7AC778
    lw(v1, v0, 0);  // 0x7AC778
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x7AC778
    lw(a0, v0, 0);  // 0x7AC778
    v0 = 0x7B0000;
    if (a0 == 0) {
        // 0x005617b0
        charge(ctx, 2);
        v0 = addiu(v0, -14480);
        sw(zero, v0, 0);
    }
    // 0x005617b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00562F40 sub_562F40 -- 76 bytes; frame 0x10: ra sp+0x0
// SJUNI pool finish: the last call clears the 64 handles. [sjuni_FinishPool]
void sub_562F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562f40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7B0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 3280);  // &0x7B0CD0
    lw(v0, v1, 0);  // 0x7B0CD0
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7B0CD0
    if (v0 != 0) {
        // 0x00562f80
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00562f60
    charge(ctx, 7);
    a0 = 0x7B0000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 3288);  // &0x7B0CD8
    a2 = 3072;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00562F90 sub_562F90 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Create an SJUNI handle (locked): merge mode, node work area, work size. [SJUNI_Create]
void sub_562F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562f90
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x562FACu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x562FBCu, gen::fn_sub_562FE8_00562fe8);
    s0 = v0;
    jal(ctx, 0x562FC4u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00562FE8 sub_562FE8 -- 228 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Take a free SJUNI handle: mode, work area, node count = size / 16, reset it. [sjuni_Create]
void sub_562FE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00562fe8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x7B0000;
    sd(s0, sp, 0x0);
    v1 = addiu(t0, 3288);  // &0x7B0CD8
    sd(ra, sp, 0x8);
    t1 = a0;
    t2 = a1;
    a3 = a2;
    lb(v0, v1, 4);  // 0x7B0CDC
    a0 = 0;
    if (v0 != 0) {
        // 0x00563014
        charge(ctx, 3);
        v1 = addiu(v1, 4);
        a0 = addiu(a0, 1);
        for (;;) {
            // 0x00563020
            charge(ctx, 3);
            v0 = slti(a0, 64);
            v1 = addiu(v1, 48);
            if (v0 != 0) {
                // 0x0056302c
                charge(ctx, 6);
                lb(v0, v1, 0);
                if (v0 != 0) {
                    a0 = addiu(a0, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x00563044
    charge(ctx, 3);
    v1 = 64;
    v0 = 0;
    if (a0 != v1) {
        // 0x00563050
        charge(ctx, 27);
        s0 = sll(a0, 1);
        v1 = addiu(t0, 3288);
        s0 = addu(s0, a0);
        a0 = addiu(a3, 15);
        v0 = slti(a3, 0);
        s0 = sll(s0, 4);
        s0 = addu(s0, v1);
        v1 = 0x7B0000;
        if (v0 != 0) a3 = a0;
        v0 = 1;
        a1 = 0x7C0000;
        a2 = 0x560000;
        v1 = addiu(v1, 3232);  // &0x7B0CA0
        a1 = addiu(a1, 27304);  // &0x7C6AA8
        a3 = sra(a3, 4);
        a2 = addiu(a2, 11816);  // &sub_562E28
        sb(v0, s0, sj::kUsed);
        a0 = s0;
        sw(v1, s0, sj::kVtbl);
        sb(t1, s0, sjuni::kMerge);
        sw(a1, s0, sj::kUuid);
        sw(t2, s0, sjuni::kWork);
        sw(a3, s0, sjuni::kNodes);
        sw(a2, s0, sjuni::kErrFn);
        link(ctx, 0x5630B0u);  // $ra first: the delay slot below depends on it
        sw(s0, s0, sjuni::kErrObj);
        call(ctx, gen::fn_sub_5632F8_005632f8);
        v0 = s0;
    }
    // 0x005630bc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005630D0 sub_5630D0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroy an SJUNI handle (locked). [SJUNI_Destroy]
void sub_5630D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005630d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5630DCu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x5630E4u, gen::fn_sub_563100_00563100);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00563100 sub_563100 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroy: zero the 48 bytes. [sjuni_Destroy]
void sub_563100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563100
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00563114
        charge(ctx, 8);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 27336);  // "E2004090261"
        ld(ra, sp, 0x8);
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x00563138
    charge(ctx, 3);
    lb(v0, s0, 4);
    a1 = 0;
    if (v0 != 0) {
        // 0x00563168
        charge(ctx, 7);
        a2 = 48;
        jal(ctx, 0x563168u, gen::fn_memset_00521408);
        sb(zero, s0, 4);
        ld(ra, sp, 0x8);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00563144
    charge(ctx, 8);
    a0 = 0x7C0000;
    a1 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 27384);  // "E2004090262"
    ld(ra, sp, 0x8);
    a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_562E48_00562e48(ctx);  // tail call
}

// 0x00563188 sub_563188 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The uuid of an SJUNI handle (locked). [SJUNI_GetUuid]
void sub_563188(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563188
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x563194u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x56319Cu, gen::fn_sub_5631C0_005631c0);
    s0 = v0;
    jal(ctx, 0x5631A4u, gen::fn_sub_5617D8_005617d8);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005631C0 sub_5631C0 -- 84 bytes; frame 0x10: ra sp+0x0
// The uuid pointer (+8). [sjuni_GetUuid]
void sub_5631C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005631c0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x005631cc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27432);  // "E2004090263"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        goto L_005631fc;
    }
    // 0x005631e0
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    if (v0 != 0) {
        lw(v0, a0, sj::kUuid);
    } else {
        // 0x005631ec
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27448);  // "E2004090264"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    L_005631fc:
        charge(ctx, 3);
        jal(ctx, 0x5631FCu, gen::fn_sub_562E48_00562e48);
        v0 = 0;
    }
    // 0x00563208 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00563218 sub_563218 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Set an SJUNI handle's error callback (locked). [SJUNI_EntryErrFunc]
void sub_563218(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563218
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x563234u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x563244u, gen::fn_sub_563268_00563268);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00563268 sub_563268 -- 96 bytes; frame 0x10: ra sp+0x0
// Store the error callback and its object (+40 / +44). [sjuni_EntryErrFunc]
void sub_563268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563268
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00563274
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27464);  // "E2004090265"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x00563290
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    ld(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x005632b8
        charge(ctx, 4);
        sw(a2, a0, sjuni::kErrObj);
        sw(a1, a0, sjuni::kErrFn);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056329c
    charge(ctx, 6);
    a0 = 0x7C0000;
    a1 = 0x7C0000;
    a0 = addiu(a0, 27480);  // "E2004090266"
    a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_562E48_00562e48(ctx);  // tail call
}

// 0x005632C8 sub_5632C8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Reset an SJUNI handle (locked). [SJUNI_Reset]
void sub_5632C8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005632c8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5632D4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x5632DCu, gen::fn_sub_5632F8_005632f8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005632F8 sub_5632F8 -- 216 bytes; frame 0x10: ra sp+0x0
// Reset: chain every 16-byte node into the free list, empty the four lines. [sjuni_Reset]
void sub_5632F8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005632f8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00563304
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27496);  // "E2004090267"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x00563320
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    if (v0 == 0) {
        // 0x0056332c
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27512);  // "E2004090268"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    lw(v0, a0, sjuni::kNodes);
    // 0x00563348
    charge(ctx, 5);
    a2 = 0;
    lw(a3, a0, sjuni::kWork);
    v0 = addiu(v0, -1);
    sw(a3, a0, sjuni::kFreeList);
    if (i64(v0) > 0) {
        // 0x0056335c
        charge(ctx, 1);
        a1 = a3;
        for (;;) {
            // 0x00563360
            charge(ctx, 10);
            sw(zero, a1, 12);
            a2 = addiu(a2, 1);
            v1 = addiu(a1, 16);
            sw(zero, a1, 8);
            lw(v0, a0, sjuni::kNodes);
            sw(v1, a1, 0);
            v0 = addiu(v0, -1);
            v0 = slt(a2, v0);
            a1 = v1;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00563388
    charge(ctx, 8);
    v0 = sll(a2, 4);
    a2 = 3;
    v0 = addu(v0, a3);
    a0 = addiu(a0, 36);
    sw(zero, v0, 12);
    sw(zero, v0, 0);
    sw(zero, v0, 8);
    for (;;) {
        // 0x005633a8
        charge(ctx, 7);
        a2 = addiu(a2, -1);
        sw(zero, a0, 0);
        a0 = addiu(a0, -4);
        if (i64(a2) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005633c4
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005633D0 sub_5633D0 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Bytes on a line (locked). [SJUNI_GetNumData]
void sub_5633D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005633d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5633E4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x5633F0u, gen::fn_sub_563418_00563418);
    s0 = v0;
    jal(ctx, 0x5633F8u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00563418 sub_563418 -- 180 bytes; frame 0x10: ra sp+0x0
// Bytes on a line: the sum of its chunks' sizes (lines 0..3). [sjuni_GetNumData]
void sub_563418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00563418
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00563424
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27528);  // "E2004090269"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        goto L_00563454;
    }
    // 0x00563438
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    if (v0 != 0) {
        v0 = sltiu(a1, 4);
        // 0x00563468
        charge(ctx, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = sll(a1, 2);
        if (cc) {
            // 0x00563490
            charge(ctx, 4);
            v0 = addu(v0, a0);
            lw(a0, v0, 24);
            v1 = 0;
            if (a0 != 0) {
                for (;;) {
                    // 0x005634a0
                    charge(ctx, 7);
                    lw(v0, a0, 12);
                    lw(a0, a0, 0);
                    v1 = addu(v1, v0);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x005634bc
            charge(ctx, 1);
            v0 = v1;
        } else {
            // 0x00563470
            charge(ctx, 3);
            lw(v0, a0, sjuni::kErrFn);
            if (v0 == 0) {
                v0 = 0;
            } else {
                // 0x0056347c
                charge(ctx, 5);
                lw(a0, a0, sjuni::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x563480u, v0.u());
                v0 = 0;
            }
        }
    } else {
        // 0x00563444
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27544);  // "E2004090270"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    L_00563454:
        charge(ctx, 4);
        jal(ctx, 0x563454u, gen::fn_sub_562E48_00562e48);
        v0 = 0;
    }
    // 0x005634c0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005634D0 sub_5634D0 -- 92 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Get a chunk (locked). [SJUNI_GetChunk]
void sub_5634D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005634d0
    enter(ctx, 23);  // entry check point + this block's cycles
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
    jal(ctx, 0x5634F4u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x563508u, gen::fn_sub_563530_00563530);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00563530 sub_563530 -- 336 bytes; frame 0x40: s1 sp+0x28, s0 sp+0x20, s2 sp+0x30, ra sp+0x38
// Get a chunk from a line: its first node whole when it fits n (the node goes back to the free list), else in merge
// mode the first n bytes (sub_563C28 splits it), else an empty chunk. [sjuni_GetChunk]
// Lines 0..3; a whole node goes back to the free list (pushed at its head).
void sub_563530(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00563530
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x28);
    s1 = a3;
    sd(s0, sp, 0x20);
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x38);
    if (a0 != 0) {
        // 0x00563568
        charge(ctx, 3);
        lb(v0, a0, sj::kUsed);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = sltiu(a1, 4);
        if (cc) {
            // 0x00563590
            charge(ctx, 2);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = sll(a1, 2);
            if (!cc) {
                // 0x00563598
                charge(ctx, 3);
                lw(v0, a0, sjuni::kErrFn);
                if (v0 == 0) {
                    sw(zero, s1, sj::kChunkSize);
                } else {
                    // 0x005635a4
                    charge(ctx, 5);
                    lw(a0, a0, sjuni::kErrObj);
                    a1 = si(-3);
                    jalr(ctx, 0x5635A8u, v0.u());
                    sw(zero, s1, sj::kChunkSize);
                }
                goto L_00563664;
            }
            // 0x005635b8
            charge(ctx, 5);
            v0 = addu(v0, a0);
            a1 = addiu(v0, 24);
            lw(a3, a1, 0);
            s2 = addiu(a3, 8);
            if (a3 == 0) {
                // 0x00563660
                charge(ctx, 1);
                sw(zero, s1, sj::kChunkSize);
            L_00563664:
                charge(ctx, 1);
                sw(zero, s1, sj::kChunkData);
            } else {
                // 0x005635cc
                charge(ctx, 8);
                ldl(v0, s2, 7);
                ldr(v0, s2, 0);
                sdl(v0, sp, 0x7);
                sdr(v0, sp, 0x0);
                lw(v0, sp, 0x4);
                v0 = slt(a2, v0);
                if (v0 != 0) {
                    lb(v1, a0, sjuni::kMerge);
                    // 0x00563618
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        sw(zero, s1, sj::kChunkSize);
                        goto L_00563664;
                    }
                    // 0x00563624
                    charge(ctx, 15);
                    s0 = addiu(sp, 0x10);
                    a1 = a2;
                    a0 = sp;
                    a3 = s0;
                    a2 = sp;
                    jal(ctx, 0x563634u, gen::fn_sub_563C28_00563c28);
                    ldl(v0, sp, 0x7);
                    ldr(v0, sp, 0x0);
                    sdl(v0, s1, 7);
                    sdr(v0, s1, 0);
                    ldl(a2, s0, 7);
                    ldr(a2, s0, 0);
                    sdl(a2, s2, 7);
                    sdr(a2, s2, 0);
                } else {
                    // 0x005635ec
                    charge(ctx, 10);
                    lw(v1, a3, 0);
                    ldl(v0, sp, 0x7);
                    ldr(v0, sp, 0x0);
                    sdl(v0, s1, 7);
                    sdr(v0, s1, 0);
                    sw(v1, a1, 0);
                    lw(v0, a0, sjuni::kFreeList);
                    sw(v0, a3, 0);
                    sw(a3, a0, sjuni::kFreeList);
                }
            }
            // 0x00563668
            charge(ctx, 1);
            ld(s0, sp, 0x20);
        } else {
            // 0x00563574
            charge(ctx, 7);
            a0 = 0x7C0000;
            a1 = 0x7C0000;
            a0 = addiu(a0, 27576);  // "E2004090272"
            a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
            jal(ctx, 0x563580u, gen::fn_sub_562E48_00562e48);
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x0056354c
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27560);  // "E2004090271"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        jal(ctx, 0x563558u, gen::fn_sub_562E48_00562e48);
        ld(s0, sp, 0x20);
    }
    // 0x0056366c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00563680 sub_563680 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Put a chunk (locked). [SJUNI_PutChunk]
void sub_563680(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563680
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x56369Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x5636ACu, gen::fn_sub_5636D0_005636d0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x005636D0 sub_5636D0 -- 296 bytes; frame 0x10: ra sp+0x0
// Put a chunk at a line's tail (merge mode: grown into the last node when contiguous); a free node is taken, none
// left calls the error callback. [sjuni_PutChunk]
// Walks the line to its last node first; the new node is appended (next 0).
void sub_5636D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005636d0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x005636dc
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27592);  // "E2004090273"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x005636f8
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = sltiu(a1, 4);
    if (!cc) {
        // 0x00563704
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27608);  // "E2004090274"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x00563720
    charge(ctx, 2);
    if (v0 == 0) {
        lw(v0, a0, sjuni::kErrFn);
    } else {
        // 0x00563728
        charge(ctx, 3);
        lw(t1, a2, sj::kChunkSize);
        ld(ra, sp, 0x0);
        if (i64(t1) > 0) {
            // 0x00563734
            charge(ctx, 3);
            lw(t0, a2, sj::kChunkData);
            v0 = sll(a1, 2);
            if (t0 != 0) {
                // 0x00563740
                charge(ctx, 5);
                v0 = addu(a0, v0);
                a1 = addiu(v0, 24);
                lw(v0, a1, 0);
                a3 = 0;
                if (v0 != 0) {
                    for (;;) {
                        // 0x00563754
                        charge(ctx, 7);
                        a3 = v0;
                        lw(v0, a3, 0);
                        a1 = a3;
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00563770
                charge(ctx, 4);
                lb(v1, a0, sjuni::kMerge);
                v0 = 1;
                if (v1 != v0) {
                    lw(a3, a0, sjuni::kFreeList);
                } else {
                    // 0x00563780
                    charge(ctx, 2);
                    if (a3 == 0) {
                        lw(a3, a0, sjuni::kFreeList);
                        goto L_005637a8;
                    }
                    // 0x00563788
                    charge(ctx, 5);
                    lw(v0, a3, 8);
                    lw(v1, a3, 12);
                    v0 = addu(v0, v1);
                    if (v0 != t0) {
                        lw(a3, a0, sjuni::kFreeList);
                        goto L_005637a8;
                    }
                    // 0x0056379c
                    charge(ctx, 3);
                    v0 = addu(v1, t1);
                    sw(v0, a3, 12);
                L_005637ec:
                    charge(ctx, 1);
                    ld(ra, sp, 0x0);
                    // 0x005637f0 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    sp = addiu(sp, 0x10);
                    return;
                }
            L_005637a8:
                charge(ctx, 2);
                if (a3 == 0) {
                    // 0x005637b0
                    charge(ctx, 1);
                    lw(v0, a0, sjuni::kErrFn);
                    goto L_005637b4;
                }
                lw(v0, a3, 0);
                // 0x005637d0
                charge(ctx, 7);
                ldl(v1, a2, 7);
                ldr(v1, a2, 0);
                sdl(v1, a3, 15);
                sdr(v1, a3, 8);
                sw(v0, a0, sjuni::kFreeList);
                sw(zero, a3, 0);
                sw(a3, a1, 0);
                goto L_005637ec;
            }
        }
        // 0x005637f0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_005637b4:
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x005637bc
        charge(ctx, 5);
        lw(a0, a0, sjuni::kErrObj);
        a1 = si(-3);
        jalr(ctx, 0x5637C0u, v0.u());
        ld(ra, sp, 0x0);
    }
    // 0x005637f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005637F8 sub_5637F8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Unget a chunk (locked). [SJUNI_UngetChunk]
void sub_5637F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005637f8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x563814u, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x563824u, gen::fn_sub_563848_00563848);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00563848 sub_563848 -- 288 bytes; frame 0x10: ra sp+0x0
// Unget a chunk at a line's head (merge mode: joined to the first node when contiguous). [sjuni_UngetChunk]
void sub_563848(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00563848
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    sd(ra, sp, 0x0);
    if (t0 == 0) {
        // 0x00563858
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27624);  // "E2004090275"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x00563878
    charge(ctx, 3);
    lb(v0, t0, sj::kUsed);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = sltiu(a1, 4);
    if (!cc) {
        // 0x00563884
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 27640);  // "E2004090276"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_562E48_00562e48(ctx);  // tail call
        return;
    }
    // 0x005638a0
    charge(ctx, 2);
    if (v0 == 0) {
        lw(v0, t0, sjuni::kErrFn);
    } else {
        // 0x005638a8
        charge(ctx, 3);
        lw(t2, a2, sj::kChunkSize);
        ld(ra, sp, 0x0);
        if (i64(t2) > 0) {
            // 0x005638b4
            charge(ctx, 3);
            lw(t1, a2, sj::kChunkData);
            a1 = sll(a1, 2);
            if (t1 != 0) {
                // 0x005638c0
                charge(ctx, 6);
                t3 = addiu(t0, 8);
                lb(v0, t0, sjuni::kMerge);
                v1 = addu(a1, t3);
                a0 = 1;
                lw(a3, v1, 16);
                if (v0 == a0) {
                    // 0x005638d8
                    charge(ctx, 2);
                    v0 = addu(t1, t2);
                    if (a3 == 0) {
                        goto L_00563900;
                    }
                    // 0x005638e0
                    charge(ctx, 3);
                    lw(v1, a3, 8);
                    if (v0 != v1) {
                        lw(a3, t0, sjuni::kFreeList);
                    L_00563904:
                        charge(ctx, 2);
                        if (a3 == 0) {
                            // 0x0056390c
                            charge(ctx, 1);
                            lw(v0, t0, sjuni::kErrFn);
                            goto L_00563910;
                        }
                        lw(v0, a3, 0);
                        // 0x00563930
                        charge(ctx, 12);
                        v1 = addiu(a1, 16);
                        v1 = addu(t3, v1);
                        ldl(a0, a2, 7);
                        ldr(a0, a2, 0);
                        sdl(a0, a3, 15);
                        sdr(a0, a3, 8);
                        sw(v0, t0, sjuni::kFreeList);
                        sw(zero, a3, 0);
                        lw(v0, v1, 0);
                        sw(v0, a3, 0);
                        sw(a3, v1, 0);
                        ld(ra, sp, 0x0);
                    } else {
                        // 0x005638ec
                        charge(ctx, 5);
                        lw(v0, a3, 12);
                        sw(t1, a3, 8);
                        v0 = addu(v0, t2);
                        sw(v0, a3, 12);
                    }
                    // 0x00563960 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    sp = addiu(sp, 0x10);
                    return;
                }
            L_00563900:
                charge(ctx, 1);
                lw(a3, t0, sjuni::kFreeList);
                goto L_00563904;
            }
        }
        // 0x00563960 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00563910:
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x00563918
        charge(ctx, 5);
        lw(a0, t0, sjuni::kErrObj);
        a1 = si(-3);
        jalr(ctx, 0x56391Cu, v0.u());
        ld(ra, sp, 0x0);
    }
    // 0x00563960 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00563968 sub_563968 -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Is a chunk of n bytes available (locked). [SJUNI_IsGetChunk]
void sub_563968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563968
    enter(ctx, 26);  // entry check point + this block's cycles
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
    jal(ctx, 0x56398Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x5639A0u, gen::fn_sub_5639D0_005639d0);
    s0 = v0;
    jal(ctx, 0x5639A8u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005639D0 sub_5639D0 -- 200 bytes; frame 0x20: ra sp+0x10
// Is a chunk of n bytes available: the first node's size; merge mode: size >= n, else size == n. [sjuni_IsGetChunk]
void sub_5639D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005639d0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    if (a0 == 0) {
        // 0x005639dc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27656);  // "E2004090277"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        goto L_00563a0c;
    }
    // 0x005639f0
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    if (v0 != 0) {
        v0 = sltiu(a1, 4);
        // 0x00563a20
        charge(ctx, 2);
        sw(zero, a3, 0);
        if (v0 != 0) {
            // 0x00563a48
            charge(ctx, 5);
            v1 = sll(a1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 24);
            v0 = 0;
            if (v1 != 0) {
                // 0x00563a5c
                charge(ctx, 10);
                ldl(v0, v1, 15);
                ldr(v0, v1, 8);
                sdl(v0, sp, 0x7);
                sdr(v0, sp, 0x0);
                v1 = 1;
                lw(a1, sp, 0x4);
                sw(a1, a3, 0);
                lb(v0, a0, sjuni::kMerge);
                if (v0 != v1) {
                    v0 = a1 ^ a2;
                } else {
                    // 0x00563a84
                    charge(ctx, 1);
                    v0 = slt(a1, a2);
                }
                // 0x00563a88
                charge(ctx, 1);
                v0 = sltiu(v0, 1);
            }
        } else {
            // 0x00563a28
            charge(ctx, 3);
            lw(v0, a0, sjuni::kErrFn);
            if (v0 == 0) {
                v0 = 0;
            } else {
                // 0x00563a34
                charge(ctx, 5);
                lw(a0, a0, sjuni::kErrObj);
                a1 = si(-3);
                jalr(ctx, 0x563A38u, v0.u());
                v0 = 0;
            }
        }
    } else {
        // 0x005639fc
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27672);  // "E2004090278"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    L_00563a0c:
        charge(ctx, 4);
        jal(ctx, 0x563A0Cu, gen::fn_sub_562E48_00562e48);
        v0 = 0;
    }
    // 0x00563a8c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00563A98 sub_563A98 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Chunks on a line (locked). [SJUNI_GetNumChunk]
void sub_563A98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563a98
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x563AACu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x563AB8u, gen::fn_sub_563AE0_00563ae0);
    s0 = v0;
    jal(ctx, 0x563AC0u, gen::fn_sub_5617D8_005617d8);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00563AE0 sub_563AE0 -- 140 bytes; frame 0x10: ra sp+0x0
// Chunks on a line: its node count. [sjuni_GetNumChunk]
void sub_563AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563ae0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00563aec
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27688);  // "E2004090279"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        goto L_00563b1c;
    }
    // 0x00563b00
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    if (v0 != 0) {
        v0 = sll(a1, 2);
        // 0x00563b30
        charge(ctx, 4);
        v0 = addu(v0, a0);
        lw(v0, v0, 24);
        v1 = 0;
        if (v0 != 0) {
            for (;;) {
                // 0x00563b40
                charge(ctx, 7);
                lw(v0, v0, 0);
                v1 = addiu(v1, 1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00563b5c
        charge(ctx, 1);
        v0 = v1;
    } else {
        // 0x00563b0c
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27704);  // "E2004090280"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    L_00563b1c:
        charge(ctx, 4);
        jal(ctx, 0x563B1Cu, gen::fn_sub_562E48_00562e48);
        v0 = 0;
    }
    // 0x00563b60 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00563B70 sub_563B70 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Free nodes (locked). [SJUNI_GetNumChainPool]
void sub_563B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563b70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x563B7Cu, gen::fn_sub_5617C0_005617c0);
    a0 = s0;
    jal(ctx, 0x563B84u, gen::fn_sub_563BA8_00563ba8);
    s0 = v0;
    jal(ctx, 0x563B8Cu, gen::fn_sub_5617D8_005617d8);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00563BA8 sub_563BA8 -- 128 bytes; frame 0x10: ra sp+0x0
// Free nodes: the free list's length. [sjuni_GetNumChainPool]
void sub_563BA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563ba8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00563bb4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27720);  // "E2004090281"
        a1 = addiu(a1, 27352);  // " : NULL pointer is specified."
        goto L_00563be4;
    }
    // 0x00563bc8
    charge(ctx, 3);
    lb(v0, a0, sj::kUsed);
    if (v0 != 0) {
        lw(a0, a0, sjuni::kFreeList);
        // 0x00563bf8
        charge(ctx, 2);
        v0 = 0;
        if (a0 != 0) {
            for (;;) {
                // 0x00563c00
                charge(ctx, 7);
                lw(a0, a0, 0);
                v0 = addiu(v0, 1);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x00563bd4
        charge(ctx, 4);
        a0 = 0x7C0000;
        a1 = 0x7C0000;
        a0 = addiu(a0, 27736);  // "E2004090282"
        a1 = addiu(a1, 27400);  // " : Specified handle is invalid."
    L_00563be4:
        charge(ctx, 4);
        jal(ctx, 0x563BE4u, gen::fn_sub_562E48_00562e48);
        v0 = 0;
    }
    // 0x00563c1c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00563C28 sub_563C28 -- 92 bytes; leaf frame (no stack)
// Split a chunk {data, size} at n: the first part (size min(n, size)) and the rest (data + n, or {0, 0}).
// [SJ_SplitChunk]
void sub_563C28(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00563c28
    enter(ctx, 10);  // entry check point + this block's cycles
    ldl(v0, a0, 7);
    ldr(v0, a0, 0);
    sdl(v0, a2, 7);
    sdr(v0, a2, 0);
    lw(v0, a2, 4);
    sw(v0, a3, 4);
    lw(v1, a2, 4);
    v0 = slt(a1, v1);
    if (v0 == 0) {
        lw(v0, a3, 4);
    } else {
        // 0x00563c50
        charge(ctx, 3);
        sw(a1, a2, 4);
        v1 = a1;
        lw(v0, a3, 4);
    }
    // 0x00563c5c
    charge(ctx, 3);
    v0 = subu(v0, v1);
    sw(v0, a3, 4);
    if (v0 == 0) {
        // 0x00563c68
        charge(ctx, 2);
        sw(zero, a3, 0);
        return;
    }
    // 0x00563c70
    charge(ctx, 5);
    lw(v0, a2, 0);
    lw(v1, a2, 4);
    v0 = addu(v0, v1);
    sw(v0, a3, 0);
}

}  // namespace p3fes::game
