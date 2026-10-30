// Phase 5 slice libs5: CRI Sofdec SFD, the audio transfer (method table 0x7C9D78): the ADXT bridges, create /
// destroy, the request, start / stop, the per-frame server, the volume / pan accessors (0x5863D8-0x5883B8).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_R_LOCK_DEF_lock_free_4_005865c0(p3fes::EEContext&);
void fn_R_LOCK_DEF_lock_new_5_00587f00(p3fes::EEContext&);
void fn___errno_13_00587b00(p3fes::EEContext&);
void fn_r_lock_def_free_5_00587d90(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_0_00541ce8(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_4_005863f8(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_5_00587db0(p3fes::EEContext&);
void fn_sceInsockGetErrnoMode_1_00597438(p3fes::EEContext&);
void fn_sub_53EA90_0053ea90(p3fes::EEContext&);
void fn_sub_545FC8_00545fc8(p3fes::EEContext&);
void fn_sub_546058_00546058(p3fes::EEContext&);
void fn_sub_5460E0_005460e0(p3fes::EEContext&);
void fn_sub_546270_00546270(p3fes::EEContext&);
void fn_sub_546368_00546368(p3fes::EEContext&);
void fn_sub_546498_00546498(p3fes::EEContext&);
void fn_sub_5465A0_005465a0(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_546FA0_00546fa0(p3fes::EEContext&);
void fn_sub_547BC0_00547bc0(p3fes::EEContext&);
void fn_sub_548048_00548048(p3fes::EEContext&);
void fn_sub_5484E0_005484e0(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_548768_00548768(p3fes::EEContext&);
void fn_sub_548AE8_00548ae8(p3fes::EEContext&);
void fn_sub_548EB8_00548eb8(p3fes::EEContext&);
void fn_sub_548F40_00548f40(p3fes::EEContext&);
void fn_sub_548FC8_00548fc8(p3fes::EEContext&);
void fn_sub_5497F8_005497f8(p3fes::EEContext&);
void fn_sub_549DE8_00549de8(p3fes::EEContext&);
void fn_sub_549FF8_00549ff8(p3fes::EEContext&);
void fn_sub_54A680_0054a680(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_575410_00575410(p3fes::EEContext&);
void fn_sub_575880_00575880(p3fes::EEContext&);
void fn_sub_586428_00586428(p3fes::EEContext&);
void fn_sub_5864A8_005864a8(p3fes::EEContext&);
void fn_sub_5864C0_005864c0(p3fes::EEContext&);
void fn_sub_586530_00586530(p3fes::EEContext&);
void fn_sub_5865A8_005865a8(p3fes::EEContext&);
void fn_sub_586610_00586610(p3fes::EEContext&);
void fn_sub_586800_00586800(p3fes::EEContext&);
void fn_sub_586858_00586858(p3fes::EEContext&);
void fn_sub_5868C0_005868c0(p3fes::EEContext&);
void fn_sub_586950_00586950(p3fes::EEContext&);
void fn_sub_586A08_00586a08(p3fes::EEContext&);
void fn_sub_586A10_00586a10(p3fes::EEContext&);
void fn_sub_586AA0_00586aa0(p3fes::EEContext&);
void fn_sub_586AD0_00586ad0(p3fes::EEContext&);
void fn_sub_586B58_00586b58(p3fes::EEContext&);
void fn_sub_587268_00587268(p3fes::EEContext&);
void fn_sub_587310_00587310(p3fes::EEContext&);
void fn_sub_587338_00587338(p3fes::EEContext&);
void fn_sub_5874D8_005874d8(p3fes::EEContext&);
void fn_sub_587520_00587520(p3fes::EEContext&);
void fn_sub_587540_00587540(p3fes::EEContext&);
void fn_sub_5875E8_005875e8(p3fes::EEContext&);
void fn_sub_587600_00587600(p3fes::EEContext&);
void fn_sub_587618_00587618(p3fes::EEContext&);
void fn_sub_587638_00587638(p3fes::EEContext&);
void fn_sub_5876F0_005876f0(p3fes::EEContext&);
void fn_sub_587718_00587718(p3fes::EEContext&);
void fn_sub_587780_00587780(p3fes::EEContext&);
void fn_sub_5878D8_005878d8(p3fes::EEContext&);
void fn_sub_587A90_00587a90(p3fes::EEContext&);
void fn_sub_587B10_00587b10(p3fes::EEContext&);
void fn_sub_587B50_00587b50(p3fes::EEContext&);
void fn_sub_587C10_00587c10(p3fes::EEContext&);
void fn_sub_587CB8_00587cb8(p3fes::EEContext&);
void fn_sub_587DC8_00587dc8(p3fes::EEContext&);
void fn_sub_587DE8_00587de8(p3fes::EEContext&);
void fn_sub_588138_00588138(p3fes::EEContext&);
void fn_sub_589018_00589018(p3fes::EEContext&);
void fn_sub_5890F0_005890f0(p3fes::EEContext&);
void fn_sub_5895F0_005895f0(p3fes::EEContext&);
void fn_sub_589CB0_00589cb0(p3fes::EEContext&);
void fn_sub_589CD0_00589cd0(p3fes::EEContext&);
void fn_sub_589D10_00589d10(p3fes::EEContext&);
void fn_sub_589D80_00589d80(p3fes::EEContext&);
void fn_sub_589F38_00589f38(p3fes::EEContext&);
void fn_sub_58A108_0058a108(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_59A458_0059a458(p3fes::EEContext&);
void fn_sub_59A860_0059a860(p3fes::EEContext&);
void fn_sub_59BCF0_0059bcf0(p3fes::EEContext&);
void fn_sub_59BE10_0059be10(p3fes::EEContext&);
void fn_sub_59BE18_0059be18(p3fes::EEContext&);
void fn_sub_59BE30_0059be30(p3fes::EEContext&);
void fn_sub_59BE48_0059be48(p3fes::EEContext&);
void fn_sub_59BE60_0059be60(p3fes::EEContext&);
void fn_sub_59BE78_0059be78(p3fes::EEContext&);
void fn_sub_59BE90_0059be90(p3fes::EEContext&);
void fn_sub_59BEF0_0059bef0(p3fes::EEContext&);
void fn_sub_5A1868_005a1868(p3fes::EEContext&);
void fn_sub_5A19C0_005a19c0(p3fes::EEContext&);
void fn_sub_5A1A30_005a1a30(p3fes::EEContext&);
void fn_sub_5A1B80_005a1b80(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x005863F8 r_lock_def_get_free_item_4 -- 36 bytes; frame 0x10: ra sp+0x0
// [sfdAdxtIsError] SFD audio: true when the ADXT player reports status 4 (error) (FLIRT misname).
void r_lock_def_get_free_item_4(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005863f8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x586400u, gen::fn_sub_546368_00546368);
    v0 = v0 ^ 0x4;
    ld(ra, sp, 0x0);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00586428 sub_586428 -- 36 bytes; frame 0x10: ra sp+0x0
// [sfdAdxtSetReadSize] SFD audio: forwards to ADXT sub_546FA0 when the handle is not null.
void sub_586428(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586428
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00586440
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00586434
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546FA0_00546fa0(ctx);  // tail call
}

// 0x005864A8 sub_5864A8 -- 24 bytes; frame 0x10: ra sp+0x0
// [sfdAdxtCreate] SFD audio: creates an ADXT player (sub_545FC8(a0, 0)).
void sub_5864A8(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005864a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545FC8_00545fc8(ctx);  // tail call
}

// 0x005864C0 sub_5864C0 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdAdxtDestroy] SFD audio: thunk to ADXT destroy (sub_546058).
void sub_5864C0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005864c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546058_00546058(ctx);  // tail call
}

// 0x00586530 sub_586530 -- 116 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// [sfdAdxtStartFile] SFD audio: (re)starts an ADXT file: stop (sub_546270), the file request (sub_5460E0, five
// arguments), sub_546718(adxt, a4).
void sub_586530(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586530
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = t0;
    jal(ctx, 0x58655Cu, gen::fn_sub_546270_00546270);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    jal(ctx, 0x586574u, gen::fn_sub_5460E0_005460e0);
    a0 = s0;
    a1 = s4;
    ld(s4, sp, 0x20);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_546718_00546718(ctx);  // tail call
}

// 0x005865A8 sub_5865A8 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdAdxtStart] SFD audio: thunk to ADXT sub_546498 (the start; -1 on failure).
void sub_5865A8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005865a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546498_00546498(ctx);  // tail call
}

// 0x005865C0 R_LOCK_DEF_lock_free_4 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdAdxtStop] SFD audio: ADXT sub_5465A0, then stop (sub_546270) (FLIRT misname).
void R_LOCK_DEF_lock_free_4(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005865c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5865CCu, gen::fn_sub_5465A0_005465a0);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546270_00546270(ctx);  // tail call
}

// 0x00586610 sub_586610 -- 20 bytes; frame 0x10: ra sp+0x0
// [sfdAdxtGetStat] SFD audio: thunk to the ADXT status (sub_546368).
void sub_586610(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00586610
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_546368_00546368(ctx);  // tail call
}

// 0x00586800 sub_586800 -- 88 bytes; leaf frame (no stack)
// [sfdAudioSetConfig] SFD audio: keeps an ADXT configuration at 0x9A6ED0: words 0, 1 and 3..5, and the two buffer
// sizes (words 2 and 6) rounded up to 32.
void sub_586800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00586800
    enter(ctx, 22);  // entry check point + this block's cycles
    lw(v1, a0, 0);
    a1 = 0x9A0000;
    a1 = addiu(a1, 28368);  // &0x9A6ED0
    lw(v0, a0, 8);
    sw(v1, a1, 0);  // 0x9A6ED0
    a2 = si(-32);
    v0 = addiu(v0, 31);
    lw(v1, a0, 4);
    v0 = v0 & a2;
    sw(v0, a1, 8);  // 0x9A6ED8
    sw(v1, a1, 4);  // 0x9A6ED4
    lw(v0, a0, 24);
    lw(v1, a0, 12);
    v0 = addiu(v0, 31);
    sw(v1, a1, 12);  // 0x9A6EDC
    v0 = v0 & a2;
    sw(v0, a1, 24);  // 0x9A6EE8
    lw(v1, a0, 16);
    sw(v1, a1, 16);  // 0x9A6EE0
    lw(v0, a0, 20);
    sw(v0, a1, 20);  // 0x9A6EE4
}

// 0x00586858 sub_586858 -- 60 bytes; frame 0x10: ra sp+0x0
// [sfdAudioInit] SFD audio: the module init: ADXT init (sub_53EA90), sub_541CE8, and the configuration 0x9A6ED0
// cleared (7 words). Returns 0.
void sub_586858(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586858
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x586860u, gen::fn_sub_53EA90_0053ea90);
    jal(ctx, 0x586868u, gen::fn_r_lock_def_get_free_item_0_00541ce8);
    a0 = 0x9A0000;
    a1 = 0;
    a0 = addiu(a0, 28368);  // &0x9A6ED0
    a2 = 7;
    jal(ctx, 0x58687Cu, gen::fn_sub_575880_00575880);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005868C0 sub_5868C0 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [sfdAudioCheckFormat] SFD audio: when the time record's +500 equals +504, reads two ADXT figures (sub_548EB8 /
// sub_548F40) and, both positive, hands them to sub_58A108.
void sub_5868C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005868c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    v0 = addiu(s0, 3376);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(a0, s0, sfdh::kTrn3Work);
    lw(a1, v0, 504);
    lw(v1, v0, 500);
    lw(s1, a0, 0);
    if (v1 != a1) {
        // 0x00586938
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x0058693c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005868f0
    charge(ctx, 7);
    a0 = s1;
    jal(ctx, 0x5868F0u, gen::fn_sub_548EB8_00548eb8);
    a0 = s1;
    s2 = v0;
    jal(ctx, 0x5868FCu, gen::fn_sub_548F40_00548f40);
    if (i64(s2) <= 0) {
        ld(s0, sp, 0x0);
        // 0x0058693c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058690c
    charge(ctx, 2);
    if (i64(v0) <= 0) {
        ld(s0, sp, 0x0);
        // 0x0058693c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00586914
    charge(ctx, 9);
    a0 = s0;
    ld(s0, sp, 0x0);
    a1 = s2;
    ld(s2, sp, 0x10);
    ld(s1, sp, 0x8);
    a2 = v0;
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58A108_0058a108(ctx);  // tail call
}

// 0x00586950 sub_586950 -- 180 bytes; frame 0x10: ra sp+0x0
// [sfdAudioExecServer] SFD audio: the per-frame server (method 2): with parameter 6 set and the output not ended: the
// input step (sub_586A10), end of input, the ADXT status, the format record, the volume, the format check. Returns
// the input step's result.
void sub_586950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586950
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00586968
    charge(ctx, 9);
    sp = addiu(sp, -0x30);
    a1 = 6;
    sd(s1, sp, 0x18);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a0;
    jal(ctx, 0x58697Cu, gen::fn_sub_599408_00599408);
    a0 = s1;
    if (v0 != 0) {
        // 0x0058698c
        charge(ctx, 5);
        jal(ctx, 0x58698Cu, gen::fn_sub_587600_00587600);
        v1 = 1;
        a0 = s1;
        if (v0 != v1) {
            // 0x005869a8
            charge(ctx, 18);
            jal(ctx, 0x5869A8u, gen::fn_sub_586A08_00586a08);
            a0 = s1;
            a1 = sp;
            jal(ctx, 0x5869B4u, gen::fn_sub_586A10_00586a10);
            a0 = s1;
            s0 = v0;
            jal(ctx, 0x5869C0u, gen::fn_sub_587268_00587268);
            lw(a1, sp, 0x0);
            a0 = s1;
            jal(ctx, 0x5869CCu, gen::fn_sub_587338_00587338);
            a0 = s1;
            jal(ctx, 0x5869D4u, gen::fn_sub_587638_00587638);
            a0 = s1;
            jal(ctx, 0x5869DCu, gen::fn_sub_587718_00587718);
            a0 = s1;
            jal(ctx, 0x5869E4u, gen::fn_sub_5868C0_005868c0);
            v0 = s0;
        } else {
            // 0x005869a0
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x005869f0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00586A08 sub_586A08 -- 8 bytes; leaf frame (no stack)
// [sfdAudioNop] SFD audio: an empty step of the server.
void sub_586A08(EEContext& ctx) {
    using namespace hg;
    // 0x00586a08
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00586A10 sub_586A10 -- 140 bytes; frame 0x30: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, ra sp+0x28
// [sfdAudioFeed] SFD audio: the input step: takes the input stream's chunk (sub_5874D8), feeds the work's read
// callback (+60), advances the stream (sub_587520) and accounts the bytes (sub_587540).
void sub_586A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00586a10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    a1 = sp;
    sd(ra, sp, 0x28);
    a2 = addiu(sp, 0x4);
    sw(zero, s2, 0);
    link(ctx, 0x586A38u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, sfdh::kTrn3Work);
    call(ctx, gen::fn_sub_5874D8_005874d8);
    a3 = addiu(sp, 0x8);
    a0 = s0;
    if (v0 == 0) {
        // 0x00586a4c
        charge(ctx, 11);
        lw(v0, sp, 0x4);
        lw(a1, sp, 0x0);
        lw(v1, s1, 60);
        a2 = v0;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x586A5Cu);  // $ra = the return address
        sw(v0, s2, 0);
        call_ptr(ctx, jt);
        a0 = s0;
        link(ctx, 0x586A68u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x8);
        call(ctx, gen::fn_sub_587520_00587520);
        a0 = s0;
        if (v0 == 0) {
            // 0x00586a78
            charge(ctx, 3);
            jal(ctx, 0x586A78u, gen::fn_sub_587540_00587540);
            v0 = 0;
        }
    }
    // 0x00586a84 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00586AA0 sub_586AA0 -- 44 bytes; frame 0x10: ra sp+0x0
// [sfdSjGetChunk0] SFD audio: an SJ's get-chunk on channel 0 (method +24).
void sub_586AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586aa0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(v1, a0, 0);
    sd(ra, sp, 0x0);
    a3 = a2;
    a2 = a1;
    lw(v0, v1, 24);
    a1 = 0;
    jalr(ctx, 0x586AB8u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00586AD0 sub_586AD0 -- 136 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// [sfdSjPutChunk] SFD audio: returns a chunk to an SJ: nothing taken -> method +28 back on channel 0; else split it
// (sub_563C28), put the used part on channel 1 (+32) and the rest back on 0 (+28).
void sub_586AD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586ad0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(ra, sp, 0x20);
    if (a1 != 0) {
        // 0x00586b08
        charge(ctx, 16);
        a0 = s1;
        a3 = sp;
        jal(ctx, 0x586B0Cu, gen::fn_sub_563C28_00563c28);
        lw(v1, s0, 0);
        a2 = s1;
        a0 = s0;
        lw(v0, v1, 32);
        a1 = 1;
        jalr(ctx, 0x586B24u, v0.u());
        lw(v1, s0, 0);
        a0 = s0;
        a1 = 0;
        lw(v0, v1, 28);
        a2 = sp;
        jalr(ctx, 0x586B3Cu, v0.u());
        ld(s0, sp, 0x10);
    } else {
        // 0x00586aec
        charge(ctx, 6);
        lw(v0, s0, 0);
        lw(v1, v0, 28);
        jalr(ctx, 0x586AF4u, v1.u());
        ld(s0, sp, 0x10);
    }
    // 0x00586b48 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00586B58 sub_586B58 -- 180 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x20, s4 sp+0x30, s5 sp+0x38, ra sp+0x40, s1 sp+0x18, s3 sp+0x28
// [sfdAudioReadCb] SFD audio: the ADXT read callback: copies up to min(size, chunk, 102400) bytes from the work's SJ
// to the destination (sub_575410), returns the rest, counts the bytes (work +72) and reports the count.
void sub_586B58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586b58
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s4, sp, 0x30);
    s4 = a1;
    sd(s5, sp, 0x38);
    s5 = a3;
    sd(ra, sp, 0x40);
    a2 = sp;
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    lw(s1, a0, 8196);
    lw(s3, s1, 4);
    lw(a1, s1, 8);
    a0 = s3;
    jal(ctx, 0x586B94u, gen::fn_sub_586AA0_00586aa0);
    a2 = 0x10000;
    lw(s0, sp, 0x4);
    a2 = a2 | 0x9000;
    lw(a0, sp, 0x0);
    a1 = s4;
    v0 = slt(s2, s0);
    if (v0 != 0) s0 = s2;
    v1 = slt(a2, s0);
    if (v1 != 0) s0 = a2;
    a2 = s0;
    jal(ctx, 0x586BC0u, gen::fn_sub_575410_00575410);
    a0 = s3;
    a1 = s0;
    a2 = sp;
    jal(ctx, 0x586BD0u, gen::fn_sub_586AD0_00586ad0);
    lw(v0, s1, 72);
    ld(s2, sp, 0x20);
    v0 = addu(v0, s0);
    ld(s3, sp, 0x28);
    sw(v0, s1, 72);
    ld(s4, sp, 0x30);
    sw(s0, s5, 0);
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00587268 sub_587268 -- 164 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// [sfdAudioCheckEnd] SFD audio: when the output stream is open, the input stream ended and ADXT reports play end,
// marks the output stream ended.
void sub_587268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587268
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = 1;
    sd(s0, sp, 0x0);
    v0 = addiu(s1, 8188);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(s2, v0, 20);
    lw(s0, v0, 16);
    a1 = s2;
    jal(ctx, 0x587294u, gen::fn_sub_589CD0_00589cd0);
    a0 = s1;
    a1 = s0;
    if (v0 != s3) {
        // 0x005872a8
        charge(ctx, 4);
        jal(ctx, 0x5872A8u, gen::fn_sub_589CD0_00589cd0);
        if (v0 != s3) {
            ld(s0, sp, 0x0);
            // 0x005872f4 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x005872b8
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x5872B8u, gen::fn_sub_587310_00587310);
        a0 = s1;
        if (v0 == 0) {
            goto L_005872f0;
        }
        // 0x005872c8
        charge(ctx, 9);
        a1 = s2;
        ld(s2, sp, 0x10);
        ld(s0, sp, 0x0);
        a2 = 1;
        ld(s1, sp, 0x8);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_589CB0_00589cb0(ctx);  // tail call
        return;
    }
L_005872f0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005872f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00587310 sub_587310 -- 40 bytes; frame 0x10: ra sp+0x0
// [sfdAudioIsAdxtEnd] SFD audio: true when the work's ADXT reports status 3.
void sub_587310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587310
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 8196);
    link(ctx, 0x58731Cu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn_sub_548768_00548768);
    v0 = v0 ^ 0x3;
    ld(ra, sp, 0x0);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00587338 sub_587338 -- 412 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s5 sp+0x28, s6 sp+0x30, s2 sp+0x10, s4 sp+0x20, ra sp+0x38
// [sfdAudioCheckStat] SFD audio: the ADXT status check: raises 0xFF000308 / 0xFF000309 / 0xFF000307 for its error
// codes (parameter 26), resets the time base near play end, marks the output ended on status 5 or an error, and with
// the output ended and no data left stops ADXT.
void sub_587338(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587338
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    sd(s5, sp, 0x28);
    s5 = addiu(s1, 4128);
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x38);
    lw(s4, s1, sfdh::kTrn3Work);
    lw(s2, s4, 0);
    a0 = s2;
    jal(ctx, 0x587370u, gen::fn_sub_548768_00548768);
    a0 = s2;
    s3 = v0;
    jal(ctx, 0x58737Cu, gen::fn_sub_549FF8_00549ff8);
    s0 = v0;
    v0 = 0x9A0000;
    if (s0 != 0) {
        // 0x00587390
        charge(ctx, 1);
        sw(s0, v0, 28396);
    }
    // 0x00587394
    charge(ctx, 7);
    a0 = s1;
    a1 = 26;
    jal(ctx, 0x587398u, gen::fn_sub_599408_00599408);
    v1 = si(-1);
    if (v0 == 0) s0 = 0;
    a0 = s1;
    if (s0 == v1) {
        // 0x005873d8
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0xC08;
        jal(ctx, 0x5873DCu, gen::fn_sub_58BE40_0058be40);
        v0 = addiu(s3, -4);
    } else {
        // 0x005873b0
        charge(ctx, 2);
        v0 = si(-2);
        if (i64(s0) >= 0) {
            // 0x005873c8
            charge(ctx, 2);
            v0 = addiu(s3, -4);
            if (s0 != 0) {
                // 0x005873d0
                charge(ctx, 2);
            L_00587408:
                charge(ctx, 5);
                a1 = lui(0xFF00);
                a0 = s1;
                a1 = a1 | 0xC07;
                jal(ctx, 0x587410u, gen::fn_sub_58BE40_0058be40);
                v0 = addiu(s3, -4);
            }
        } else {
            // 0x005873b8
            charge(ctx, 2);
            if (s0 != v0) {
                // 0x005873c0
                charge(ctx, 2);
                goto L_00587408;
            }
            // 0x005873f0
            charge(ctx, 5);
            a1 = lui(0xFF00);
            a1 = a1 | 0xC09;
            jal(ctx, 0x5873F4u, gen::fn_sub_58BE40_0058be40);
            v0 = addiu(s3, -4);
        }
    }
    // 0x0058741c
    charge(ctx, 3);
    v0 = sltiu(v0, 2);
    if (v0 == 0) {
        v0 = 5;
    } else {
        // 0x00587428
        charge(ctx, 4);
        a0 = s5;
        a1 = 0;
        jal(ctx, 0x58742Cu, gen::fn_sub_59BE90_0059be90);
        v0 = 5;
    }
    // 0x00587438
    charge(ctx, 2);
    a0 = s1;
    if (s3 != v0) {
        // 0x00587440
        charge(ctx, 2);
        if (s0 != 0) {
            goto L_00587448;
        }
        goto L_00587450;
    }
L_00587448:
    charge(ctx, 2);
    a1 = 1;
    jal(ctx, 0x587448u, gen::fn_sub_587618_00587618);
L_00587450:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x587450u, gen::fn_sub_5875E8_005875e8);
    v1 = 1;
    ld(s0, sp, 0x0);
    if (v0 == v1) {
        // 0x00587464
        charge(ctx, 2);
        if (s6 != 0) {
            ld(s1, sp, 0x8);
            // 0x005874b4 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(s5, sp, 0x28);
            ld(s6, sp, 0x30);
            ld(ra, sp, 0x38);
            sp = addiu(sp, 0x40);
            return;
        }
        // 0x0058746c
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x58746Cu, gen::fn_sub_54A680_0054a680);
        lw(v0, s4, 72);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            goto L_005874b0;
        }
        // 0x00587480
        charge(ctx, 11);
        a0 = s1;
        ld(s1, sp, 0x8);
        a1 = 1;
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        gen::fn_sub_587618_00587618(ctx);  // tail call
        return;
    }
L_005874b0:
    charge(ctx, 1);
    ld(s1, sp, 0x8);
    // 0x005874b4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005874D8 sub_5874D8 -- 72 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// [sfdAudioGetInput] SFD audio: the input stream's chunk (sub_589018 on stream +8204) into two words.
void sub_5874D8(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005874d8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a2;
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(ra, sp, 0x30);
    a2 = sp;
    link(ctx, 0x5874F4u);  // $ra first: the delay slot below depends on it
    lw(a1, a0, 8204);
    call(ctx, gen::fn_sub_589018_00589018);
    lw(v1, sp, 0x0);
    lw(a0, sp, 0x4);
    sw(v1, s1, 0);
    sw(a0, s0, 0);
    ld(s1, sp, 0x28);
    ld(s0, sp, 0x20);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00587520 sub_587520 -- 32 bytes; frame 0x10: ra sp+0x0
// [sfdAudioAdvanceInput] SFD audio: advances the input stream (sub_5890F0).
void sub_587520(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587520
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a1;
    sd(ra, sp, 0x0);
    link(ctx, 0x58752Cu);  // $ra first: the delay slot below depends on it
    lw(a1, a0, 8204);
    call(ctx, gen::fn_sub_5890F0_005890f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00587540 sub_587540 -- 168 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// [sfdAudioAccount] SFD audio: adds the stream's and the SJ's byte counts to the 64-bit totals +2488 / +2496 / +2512
// / +2520.
void sub_587540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587540
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    v0 = addiu(s0, 8188);
    sd(ra, sp, 0x20);
    a2 = sp;
    lw(a1, v0, 16);
    link(ctx, 0x587560u);  // $ra first: the delay slot below depends on it
    lw(s1, v0, 8);
    call(ctx, gen::fn_sub_5895F0_005895f0);
    lw(v0, sp, 0x0);
    a1 = addiu(sp, 0x4);
    a2 = addiu(sp, 0x8);
    a0 = v0;
    if (v0 != 0) {
        // 0x0058757c
        charge(ctx, 22);
        jal(ctx, 0x58757Cu, gen::fn_sub_589D80_00589d80);
        ld(a0, s0, sfdh::kInBytes0);
        link(ctx, 0x587588u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x4);
        call(ctx, gen::fn_sub_589F38_00589f38);
        ld(a0, s0, sfdh::kInBytes1);
        sd(v0, s0, sfdh::kInBytes0);
        link(ctx, 0x587598u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x8);
        call(ctx, gen::fn_sub_589F38_00589f38);
        lw(a0, s1, 4);
        sd(v0, s0, sfdh::kInBytes1);
        a1 = addiu(sp, 0x4);
        a2 = addiu(sp, 0x8);
        jal(ctx, 0x5875ACu, gen::fn_sub_589D80_00589d80);
        ld(a0, s0, sfdh::kSjBytes0);
        link(ctx, 0x5875B8u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x4);
        call(ctx, gen::fn_sub_589F38_00589f38);
        ld(a0, s0, sfdh::kSjBytes1);
        sd(v0, s0, sfdh::kSjBytes0);
        link(ctx, 0x5875C8u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x8);
        call(ctx, gen::fn_sub_589F38_00589f38);
        sd(v0, s0, sfdh::kSjBytes1);
    }
    // 0x005875d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005875E8 sub_5875E8 -- 24 bytes; frame 0x10: ra sp+0x0
// [sfdAudioIsInputEnd] SFD audio: the input stream's ended flag (stream +8204).
void sub_5875E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005875e8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, 8204);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589D10_00589d10(ctx);  // tail call
}

// 0x00587600 sub_587600 -- 24 bytes; frame 0x10: ra sp+0x0
// [sfdAudioIsOutputEnd] SFD audio: the output stream's ended flag (stream +8208).
void sub_587600(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587600
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, 8208);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589D10_00589d10(ctx);  // tail call
}

// 0x00587638 sub_587638 -- 180 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdAudioSetFormat] SFD audio: fills the audio format record once ADXT knows the format: channels, rate, bits,
// used, and the byte rate 9 x channels x rate / 16.
void sub_587638(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587638
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x587648u, gen::fn_sub_588138_00588138);
    s1 = v0;
    if (s1 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0058765c
        charge(ctx, 3);
        lw(v0, s1, 0);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00587668
            charge(ctx, 6);
            lw(v0, s0, 8196);
            lw(s0, v0, 0);
            a0 = s0;
            jal(ctx, 0x587670u, gen::fn_sub_5876F0_005876f0);
            a0 = s0;
            if (v0 != 0) {
                // 0x00587680
                charge(ctx, 22);
                jal(ctx, 0x587680u, gen::fn_sub_548F40_00548f40);
                a0 = s0;
                link(ctx, 0x58768Cu);  // $ra first: the delay slot below depends on it
                sw(v0, s1, 16);
                call(ctx, gen::fn_sub_548EB8_00548eb8);
                a0 = s0;
                link(ctx, 0x587698u);  // $ra first: the delay slot below depends on it
                sw(v0, s1, 20);
                call(ctx, gen::fn_sub_548FC8_00548fc8);
                lw(a0, s1, 16);
                sw(v0, s1, 12);
                v1 = 1;
                mult(a0, a0, v0);
                sw(v1, s1, 0);
                sw(v1, s1, 8);
                v0 = sll(a0, 3);
                v0 = addu(v0, a0);
                v1 = v0;
                a0 = addiu(v0, 15);
                v0 = slti(v0, 0);
                if (v0 != 0) v1 = a0;
                v1 = sra(v1, 4);
                sw(v1, s1, 4);
            }
            // 0x005876d8
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x005876dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00587718 sub_587718 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [sfdAudioApplyVolume] SFD audio: applies the volume parameter to ADXT (sub_5497F8) when it changed (work +68).
void sub_587718(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587718
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 27;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(s1, a0, 8196);
    link(ctx, 0x587730u);  // $ra first: the delay slot below depends on it
    lw(s0, s1, 0);
    call(ctx, gen::fn_sub_599408_00599408);
    v1 = v0;
    lw(v0, s1, 68);
    a1 = v1;
    a0 = s0;
    if (v0 == v1) {
        // 0x00587768
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058774c
    charge(ctx, 6);
    sw(v1, s1, 68);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5497F8_005497f8(ctx);  // tail call
}

// 0x00587780 sub_587780 -- 340 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s3 sp+0x18, s2 sp+0x10, ra sp+0x20
// [sfdAudioCreate] SFD audio: create (method 3): with parameter 6 set: the work at +13736, the ADXT part
// (sub_5878D8), the ADXT player (sub_587A90; 0xFF000304), its SJ (sub_562388; 0xFF000305), the info record +13916
// with its five callbacks, the SJ hook-up (sub_5484E0), the time callback.
void sub_587780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587780
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 6;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    s0 = addiu(s1, 13744);
    sd(s3, sp, 0x18);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s3 = addiu(s1, 13736);
    jal(ctx, 0x5877A4u, gen::fn_sub_599408_00599408);
    a0 = s1;
    a1 = s3;
    if (v0 == 0) {
        // 0x005878b8 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x005877b8
    charge(ctx, 4);
    link(ctx, 0x5877B8u);  // $ra first: the delay slot below depends on it
    sw(s3, s1, sfdh::kTrn3Work);
    call(ctx, gen::fn_sub_5878D8_005878d8);
    a0 = s0;
    if (v0 != 0) {
        // 0x005878b8 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x005877c8
    charge(ctx, 7);
    jal(ctx, 0x5877C8u, gen::fn_sub_587A90_00587a90);
    a1 = lui(0xFF00);
    s2 = v0;
    a0 = 0;
    a1 = a1 | 0xC04;
    if (s2 == 0) {
        // 0x005877e4
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
    // 0x00587800
    charge(ctx, 19);
    lw(a2, s0, 4);
    lw(a0, s0, 8);
    link(ctx, 0x587808u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 0);
    call(ctx, gen::fn_sub_562388_00562388);
    a0 = 0;
    t1 = v0;
    v0 = 0x580000;
    a1 = 0x580000;
    v1 = 0x580000;
    a2 = 0x580000;
    a3 = 0x580000;
    t3 = addiu(a1, 26376);  // &sub_586708
    a1 = t1;
    t0 = addiu(s1, 13916);
    t2 = addiu(v0, 26312);  // &sub_5866C8
    v1 = addiu(v1, 26344);  // &sub_5866E8
    a2 = addiu(a2, 26408);  // &sub_586728
    a3 = addiu(a3, 26440);  // &R_LOCK_DEF_w_lock_4
    if (t1 == 0) {
        // 0x0058784c
        charge(ctx, 9);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = a1 | 0xC05;
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00587870
    charge(ctx, 18);
    sw(t1, s3, 4);
    a0 = s2;
    sw(s2, s3, 0);
    sw(t0, s1, sfdh::kTrn7Work);
    sw(a3, t0, 20);
    lw(v0, s2, 12);
    sw(t2, t0, 4);
    sw(v0, t0, 0);
    sw(v1, t0, 8);
    sw(t3, t0, 12);
    link(ctx, 0x587898u);  // $ra first: the delay slot below depends on it
    sw(a2, t0, 16);
    call(ctx, gen::fn_sub_5484E0_005484e0);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x5878A4u, gen::fn_R_LOCK_DEF_lock_new_5_00587f00);
    a0 = s1;
    jal(ctx, 0x5878ACu, gen::fn_sub_587B10_00587b10);
    v0 = 0;
    // 0x005878b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005878D8 sub_5878D8 -- 440 bytes; frame 0x60: s2 sp+0x50, s0 sp+0x40, s1 sp+0x48, ra sp+0x58
// [sfdAudioCreateWork] SFD audio: the ADXT part of create: needs a configuration (0xFF000306); copies it into the
// work, the read callback sub_586B58, the time base's settings from parameters 61..66 and 72.
void sub_5878D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005878d8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x9A0000;
    sd(s2, sp, 0x50);
    s2 = a0;
    sd(s0, sp, 0x40);
    t0 = addiu(v0, 28368);  // &0x9A6ED0
    sd(s1, sp, 0x48);
    a3 = a1;
    sd(ra, sp, 0x58);
    a1 = lui(0xFF00);
    lw(v0, t0, 8);  // 0x9A6ED8
    a1 = a1 | 0xC06;
    if (v0 != 0) {
        // 0x0058790c
        charge(ctx, 3);
        lw(v0, t0, 24);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0x580000;
        if (!cc) {
            goto L_00587918;
        }
        // 0x00587928
        charge(ctx, 85);
        a2 = si(-1);
        v1 = 1;
        v0 = addiu(v0, 27480);
        ldl(a1, t0, 7);
        ldr(a1, t0, 0);
        ldl(t1, t0, 15);
        ldr(t1, t0, 8);
        ldl(t2, t0, 23);
        ldr(t2, t0, 16);
        lw(t3, t0, 24);
        sdl(a1, a3, 15);
        sdr(a1, a3, 8);
        sdl(t1, a3, 23);
        sdr(t1, a3, 16);
        sdl(t2, a3, 31);
        sdr(t2, a3, 24);
        sw(t3, a3, 32);
        a1 = 63;
        sw(v1, a3, 40);
        s1 = 0xF0000;
        s1 = s1 | 0x4240;
        sw(v0, a3, 60);
        s0 = addiu(s2, 4128);
        sw(a2, a3, 68);
        sw(zero, a3, 76);
        sw(zero, a3, 0);
        sw(zero, a3, 4);
        sw(a2, a3, 36);
        sw(zero, a3, 44);
        sw(zero, a3, 48);
        sw(zero, a3, 52);
        sw(zero, a3, 56);
        sw(zero, a3, 64);
        link(ctx, 0x5879ACu);  // $ra first: the delay slot below depends on it
        sw(zero, a3, 72);
        call(ctx, gen::fn_sub_599408_00599408);
        a0 = s2;
        a1 = 64;
        sd(v0, sp, 0x0);
        link(ctx, 0x5879C0u);  // $ra first: the delay slot below depends on it
        sd(s1, sp, 0x8);
        call(ctx, gen::fn_sub_599408_00599408);
        a0 = s2;
        a1 = 65;
        sd(v0, sp, 0x10);
        link(ctx, 0x5879D4u);  // $ra first: the delay slot below depends on it
        sd(s1, sp, 0x18);
        call(ctx, gen::fn_sub_599408_00599408);
        a1 = 66;
        a0 = s2;
        sd(v0, sp, 0x20);
        link(ctx, 0x5879E8u);  // $ra first: the delay slot below depends on it
        sd(s1, sp, 0x28);
        call(ctx, gen::fn_sub_599408_00599408);
        a0 = s0;
        sd(v0, sp, 0x30);
        link(ctx, 0x5879F8u);  // $ra first: the delay slot below depends on it
        sd(s1, sp, 0x38);
        call(ctx, gen::fn_sub_59BCF0_0059bcf0);
        a0 = s2;
        a1 = 72;
        jal(ctx, 0x587A04u, gen::fn_sub_599408_00599408);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x587A10u, gen::fn_sub_59BE10_0059be10);
        a0 = s0;
        a1 = sp;
        jal(ctx, 0x587A1Cu, gen::fn_sub_59BE18_0059be18);
        a0 = s0;
        a1 = addiu(sp, 0x10);
        jal(ctx, 0x587A28u, gen::fn_sub_59BE30_0059be30);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x587A34u, gen::fn_sub_59BE48_0059be48);
        a0 = s0;
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x587A40u, gen::fn_sub_59BE60_0059be60);
        a0 = s2;
        a1 = 62;
        jal(ctx, 0x587A4Cu, gen::fn_sub_599408_00599408);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x587A58u, gen::fn_sub_59BE78_0059be78);
        a0 = s2;
        a1 = 61;
        jal(ctx, 0x587A64u, gen::fn_sub_599408_00599408);
        a0 = v0;
        jal(ctx, 0x587A6Cu, gen::fn_sub_5A1868_005a1868);
        v0 = 0;
        ld(s0, sp, 0x40);
        // 0x00587a7c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x48);
        ld(s2, sp, 0x50);
        ld(ra, sp, 0x58);
        sp = addiu(sp, 0x60);
        return;
    }
L_00587918:
    charge(ctx, 4);
    a0 = 0;
    jal(ctx, 0x587918u, gen::fn_sub_58BE40_0058be40);
    ld(s0, sp, 0x40);
    // 0x00587a7c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x48);
    ld(s2, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00587A90 sub_587A90 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdAudioCreateAdxt] SFD audio: the ADXT player: the preset one (0x7B4770) in mode 1, else a new one (sub_547BC0);
// sub_549DE8(h, 0).
void sub_587A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587a90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x587A9Cu, gen::fn_sceInsockGetErrnoMode_1_00597438);
    v1 = 1;
    if (v0 == v1) {
        // 0x00587ac8
        charge(ctx, 3);
        jal(ctx, 0x587AC8u, gen::fn___errno_13_00587b00);
        s0 = v0;
    } else {
        // 0x00587ab0
        charge(ctx, 6);
        lw(a2, s0, 20);
        lw(a0, s0, 12);
        link(ctx, 0x587AB8u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 24);
        call(ctx, gen::fn_sub_547BC0_00547bc0);
        s0 = v0;
    }
    // 0x00587ad4
    charge(ctx, 2);
    v0 = 0;
    if (s0 != 0) {
        // 0x00587adc
        charge(ctx, 4);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x587AE0u, gen::fn_sub_549DE8_00549de8);
        v0 = s0;
    }
    // 0x00587aec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00587B00 __errno_13 -- 12 bytes; leaf frame (no stack)
// [sfdAudioGetPresetAdxt] SFD audio: the preset ADXT player 0x7B4770 (FLIRT misname).
void __errno_13(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00587b00
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 18288);  // 0x7B4770
}

// 0x00587B10 sub_587B10 -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [sfdAudioSetTimeCb] SFD audio: installs the time callback sub_587B50 as time source 2 and selects it (parameter 15
// = 2).
void sub_587B10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587b10
    enter(ctx, 15);  // entry check point + this block's cycles
    a1 = 0x580000;
    sp = addiu(sp, -0x10);
    a2 = 2;
    a1 = addiu(a1, 31568);  // &sub_587B50
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x587B28u, gen::fn_sub_59A860_0059a860);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    a1 = 15;
    a2 = 2;
    sp = addiu(sp, 0x10);
    gen::fn_sub_599240_00599240(ctx);  // tail call
}

// 0x00587B50 sub_587B50 -- 188 bytes; frame 0x50: s0 sp+0x10, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s1 sp+0x18, s2 sp+0x20, ra sp+0x40
// [sfdAudioGetTime] SFD audio: the time callback: while playing (status 4) the ADXT time through the time base, kept
// monotonic in the work (+36 / +40).
void sub_587B50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587b50
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s3, sp, 0x28);
    s3 = addiu(s0, 4128);
    sd(s4, sp, 0x30);
    s4 = a1;
    sd(s5, sp, 0x38);
    s5 = a2;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x40);
    lw(s1, s0, sfdh::kTrn3Work);
    link(ctx, 0x587B84u);  // $ra first: the delay slot below depends on it
    lw(s2, s1, 0);
    call(ctx, gen::fn_sub_59A458_0059a458);
    v1 = 4;
    if (v0 != 0) {
        // 0x00587b94
        charge(ctx, 3);
        lw(v0, s0, sfdh::kStat);
        if (v0 != v1) {
            lw(a0, s1, 36);
        } else {
            // 0x00587ba0
            charge(ctx, 10);
            a0 = s3;
            a1 = s2;
            a2 = sp;
            a3 = addiu(sp, 0x4);
            jal(ctx, 0x587BACu, gen::fn_sub_587C10_00587c10);
            lw(a0, s1, 36);
            lw(v1, sp, 0x0);
            v0 = slt(a0, v1);
            if (v0 != 0) {
                // 0x00587bc8
                charge(ctx, 4);
                lw(v0, sp, 0x4);
                a0 = v1;
                sw(v1, s1, 36);
                sw(v0, s1, 40);
                goto L_00587bd8;
            }
            sw(a0, s4, 0);
            goto L_00587bdc;
        }
    L_00587bd8:
        charge(ctx, 1);
        sw(a0, s4, 0);
    L_00587bdc:
        charge(ctx, 3);
        v0 = 0;
        lw(v1, s1, 40);
        sw(v1, s5, 0);
    }
    // 0x00587be8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00587C10 sub_587C10 -- 168 bytes; frame 0x70: s0 sp+0x40, s1 sp+0x48, s2 sp+0x50, s3 sp+0x58, ra sp+0x60
// [sfdAudioReadTime] SFD audio: reads the ADXT status and time and the timer, and runs the time base (sub_59BEF0).
void sub_587C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587c10
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x40);
    s0 = a1;
    sd(s1, sp, 0x48);
    s1 = a0;
    a0 = s0;
    sd(s2, sp, 0x50);
    sd(s3, sp, 0x58);
    s3 = a3;
    sd(ra, sp, 0x60);
    s2 = a2;
    jal(ctx, 0x587C38u, gen::fn_sub_548768_00548768);
    a0 = s0;
    a1 = addiu(sp, 0x30);
    a2 = addiu(sp, 0x34);
    v1 = 0x7B0000;
    link(ctx, 0x587C50u);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 17744);
    call(ctx, gen::fn_sub_548AE8_00548ae8);
    lw(v1, sp, 0x34);
    lw(v0, sp, 0x30);
    sd(v1, sp, 0x8);
    link(ctx, 0x587C64u);  // $ra first: the delay slot below depends on it
    sd(v0, sp, 0x0);
    call(ctx, gen::fn_sub_5A1A30_005a1a30);
    link(ctx, 0x587C6Cu);  // $ra first: the delay slot below depends on it
    sd(v0, sp, 0x10);
    call(ctx, gen::fn_sub_5A1B80_005a1b80);
    a1 = sp;
    a2 = addiu(sp, 0x10);
    a0 = s1;
    a3 = addiu(sp, 0x20);
    link(ctx, 0x587C84u);  // $ra first: the delay slot below depends on it
    sd(v0, sp, 0x18);
    call(ctx, gen::fn_sub_59BEF0_0059bef0);
    lw(v0, sp, 0x20);
    lw(v1, sp, 0x28);
    sw(v0, s2, 0);
    ld(s0, sp, 0x40);
    sw(v1, s3, 0);
    ld(s1, sp, 0x48);
    ld(s2, sp, 0x50);
    ld(s3, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x00587CB8 sub_587CB8 -- 216 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// [sfdAudioDestroy] SFD audio: destroy (method 4): keeps the configuration back at 0x9A6ED0, releases or destroys the
// ADXT player, destroys the SJ (+12), the timer hook (sub_5A19C0).
void sub_587CB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587cb8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v1, s1, sfdh::kTrn3Work);
    lw(s0, v1, 0);
    lw(s2, v1, 4);
    if (s0 != 0) {
        // 0x00587ce4
        charge(ctx, 20);
        v0 = 0x9A0000;
        a3 = addiu(v0, 28368);  // &0x9A6ED0
        ldl(a0, v1, 15);
        ldr(a0, v1, 8);
        ldl(a1, v1, 23);
        ldr(a1, v1, 16);
        ldl(a2, v1, 31);
        ldr(a2, v1, 24);
        sdl(a0, a3, 7);  // 0x9A6ED7
        sdr(a0, a3, 0);  // 0x9A6ED0
        sdl(a1, a3, 15);  // 0x9A6EDF
        sdr(a1, a3, 8);  // 0x9A6ED8
        sdl(a2, a3, 23);  // 0x9A6EE7
        sdr(a2, a3, 16);  // 0x9A6EE0
        lw(a0, v1, 32);
        link(ctx, 0x587D20u);  // $ra first: the delay slot below depends on it
        sw(a0, a3, 24);
        call(ctx, gen::fn_sceInsockGetErrnoMode_1_00597438);
        v1 = 1;
        a0 = s1;
        if (v0 == v1) {
            // 0x00587d48
            charge(ctx, 5);
            jal(ctx, 0x587D48u, gen::fn_sub_587DE8_00587de8);
            a0 = s0;
            jal(ctx, 0x587D50u, gen::fn_r_lock_def_get_free_item_5_00587db0);
            s0 = v0;
        } else {
            // 0x00587d34
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x587D34u, gen::fn_r_lock_def_free_5_00587d90);
            s0 = v0;
        }
        // 0x00587d5c
        charge(ctx, 7);
        lw(v1, s2, 0);
        lw(v0, v1, 12);
        a0 = s2;
        jalr(ctx, 0x587D64u, v0.u());
        jal(ctx, 0x587D6Cu, gen::fn_sub_5A19C0_005a19c0);
        v0 = s0;
    }
    // 0x00587d78 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00587D90 r_lock_def_free_5 -- 32 bytes; frame 0x10: ra sp+0x0
// [sfdAudioDestroyAdxt] SFD audio: ADXT destroy (sub_548048), returns 0 (FLIRT misname).
void r_lock_def_free_5(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587d90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x587D98u, gen::fn_sub_548048_00548048);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00587DB0 r_lock_def_get_free_item_5 -- 16 bytes; leaf frame (no stack)
// [sfdAudioSetPresetAdxt] SFD audio: keeps an ADXT player as the preset 0x7B4770 (FLIRT misname).
void r_lock_def_get_free_item_5(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00587db0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    v0 = 0;
    sw(a0, v1, 18288);  // 0x7B4770
}

// 0x00587DC8 sub_587DC8 -- 32 bytes; frame 0x10: ra sp+0x0
// [sfdAudioRequestStop] SFD audio: stop request (method 6): R_LOCK_DEF_lock_new_5(h, 0).
void sub_587DC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587dc8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;
    jal(ctx, 0x587DD0u, gen::fn_R_LOCK_DEF_lock_new_5_00587f00);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00587DE8 sub_587DE8 -- 36 bytes; frame 0x10: ra sp+0x0
// [sfdAudioStopAdxt] SFD audio: ADXT stop (sub_548678) on the work's player.
void sub_587DE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587de8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 8196);
    link(ctx, 0x587DF4u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn_sub_548678_00548678);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00588138 sub_588138 -- 48 bytes; leaf frame (no stack)
// [sfdAudioGetFormatRec] SFD audio: the audio format record of the handle's header object (+14000, +3340) when no
// data is pending (work +64 <= 0); else 0.
void sub_588138(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00588138
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, 14000);
    v0 = 0;
    lw(a0, a0, 8196);
    a1 = addiu(v1, 3340);
    if (v1 != 0) {
        // 0x0058814c
        charge(ctx, 5);
        lw(v0, a0, 64);
        v1 = 0;
        v1 = slt(v1, v0);
        v0 = 0;
        if (v1 == 0) v0 = a1;
    }
    // 0x00588160 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

}  // namespace p3fes::game
