// Phase 5 slice libs18: the small CRI middleware entry points between 0x535DC0 and 0x545440 (100 functions): the
// ADX key module (callback, "CRI-MW" keys, key-stream step, decoder finish / server), the locked public wrappers of
// ADXF (sub_53E088 / sub_53E0A0 around each adxf_ worker) and of ADXT (the empty ADX lock stubs sub_539848 /
// sub_539850), the SVM server-type thunks, the ADXRNA / PS2RNA thunks and getters, ADX header writer / reader
// (ADXT_GetHdrInfo), the ADX encoder's keys and size calculation, and record getters / setters.
// Made by p3fes_handgen from SLUS_216.21 and symbols/: every body keeps the recompiled body's registers, frame,
// spills, $ra links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h); the readability is a role
// comment per function. Pair tests: tests/game/test_libs18.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs18.h"

namespace p3fes::recomp_gen {
void fn_PS2RNA_StartPcmTrans_00560558(p3fes::EEContext&);
void fn_PS2RNA_StopPcmTrans_005605e8(p3fes::EEContext&);
void fn_SVM_ExecSvrFs_00565420(p3fes::EEContext&);
void fn__M_ctype_facet__CQ24_STL8ios_base_0_005430c0(p3fes::EEContext&);
void fn___env_lock_0053b598(p3fes::EEContext&);
void fn___env_lock_6_00541c78(p3fes::EEContext&);
void fn___env_unlock_0053b5a0(p3fes::EEContext&);
void fn___env_unlock_6_00541cc0(p3fes::EEContext&);
void fn_atan2l_0_0053f808(p3fes::EEContext&);
void fn_atan2l_1_00541a60(p3fes::EEContext&);
void fn_coshl_0_0053f838(p3fes::EEContext&);
void fn_cosl_0_0053f820(p3fes::EEContext&);
void fn_expl_0_0053f850(p3fes::EEContext&);
void fn_hypotf_0_0053f868(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_3_0053e9b8(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_4_005436c0(p3fes::EEContext&);
void fn_sqrtl_1_00541c80(p3fes::EEContext&);
void fn_sub_535DC0_00535dc0(p3fes::EEContext&);
void fn_sub_535DC8_00535dc8(p3fes::EEContext&);
void fn_sub_535DD0_00535dd0(p3fes::EEContext&);
void fn_sub_537490_00537490(p3fes::EEContext&);
void fn_sub_537498_00537498(p3fes::EEContext&);
void fn_sub_5374B0_005374b0(p3fes::EEContext&);
void fn_sub_5374E8_005374e8(p3fes::EEContext&);
void fn_sub_537508_00537508(p3fes::EEContext&);
void fn_sub_537528_00537528(p3fes::EEContext&);
void fn_sub_5376E0_005376e0(p3fes::EEContext&);
void fn_sub_537750_00537750(p3fes::EEContext&);
void fn_sub_5377D0_005377d0(p3fes::EEContext&);
void fn_sub_537F18_00537f18(p3fes::EEContext&);
void fn_sub_537FE0_00537fe0(p3fes::EEContext&);
void fn_sub_537FF0_00537ff0(p3fes::EEContext&);
void fn_sub_537FF8_00537ff8(p3fes::EEContext&);
void fn_sub_538038_00538038(p3fes::EEContext&);
void fn_sub_538408_00538408(p3fes::EEContext&);
void fn_sub_5389B0_005389b0(p3fes::EEContext&);
void fn_sub_538B00_00538b00(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_539AE0_00539ae0(p3fes::EEContext&);
void fn_sub_53A3B8_0053a3b8(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53B278_0053b278(p3fes::EEContext&);
void fn_sub_53B2A0_0053b2a0(p3fes::EEContext&);
void fn_sub_53B3D8_0053b3d8(p3fes::EEContext&);
void fn_sub_53B408_0053b408(p3fes::EEContext&);
void fn_sub_53B468_0053b468(p3fes::EEContext&);
void fn_sub_53B4A0_0053b4a0(p3fes::EEContext&);
void fn_sub_53B6F8_0053b6f8(p3fes::EEContext&);
void fn_sub_53B760_0053b760(p3fes::EEContext&);
void fn_sub_53BC88_0053bc88(p3fes::EEContext&);
void fn_sub_53BD10_0053bd10(p3fes::EEContext&);
void fn_sub_53BD50_0053bd50(p3fes::EEContext&);
void fn_sub_53BDD8_0053bdd8(p3fes::EEContext&);
void fn_sub_53BE28_0053be28(p3fes::EEContext&);
void fn_sub_53BEB0_0053beb0(p3fes::EEContext&);
void fn_sub_53C1D8_0053c1d8(p3fes::EEContext&);
void fn_sub_53C200_0053c200(p3fes::EEContext&);
void fn_sub_53C720_0053c720(p3fes::EEContext&);
void fn_sub_53C758_0053c758(p3fes::EEContext&);
void fn_sub_53CA78_0053ca78(p3fes::EEContext&);
void fn_sub_53CAE0_0053cae0(p3fes::EEContext&);
void fn_sub_53CC78_0053cc78(p3fes::EEContext&);
void fn_sub_53CCC0_0053ccc0(p3fes::EEContext&);
void fn_sub_53D040_0053d040(p3fes::EEContext&);
void fn_sub_53D098_0053d098(p3fes::EEContext&);
void fn_sub_53D128_0053d128(p3fes::EEContext&);
void fn_sub_53D180_0053d180(p3fes::EEContext&);
void fn_sub_53D418_0053d418(p3fes::EEContext&);
void fn_sub_53D450_0053d450(p3fes::EEContext&);
void fn_sub_53D540_0053d540(p3fes::EEContext&);
void fn_sub_53D578_0053d578(p3fes::EEContext&);
void fn_sub_53D790_0053d790(p3fes::EEContext&);
void fn_sub_53D7E8_0053d7e8(p3fes::EEContext&);
void fn_sub_53D900_0053d900(p3fes::EEContext&);
void fn_sub_53D938_0053d938(p3fes::EEContext&);
void fn_sub_53D9E0_0053d9e0(p3fes::EEContext&);
void fn_sub_53DA18_0053da18(p3fes::EEContext&);
void fn_sub_53DA90_0053da90(p3fes::EEContext&);
void fn_sub_53DAD8_0053dad8(p3fes::EEContext&);
void fn_sub_53DB28_0053db28(p3fes::EEContext&);
void fn_sub_53DB60_0053db60(p3fes::EEContext&);
void fn_sub_53DC70_0053dc70(p3fes::EEContext&);
void fn_sub_53DCE8_0053dce8(p3fes::EEContext&);
void fn_sub_53DF40_0053df40(p3fes::EEContext&);
void fn_sub_53DFC8_0053dfc8(p3fes::EEContext&);
void fn_sub_53E000_0053e000(p3fes::EEContext&);
void fn_sub_53E038_0053e038(p3fes::EEContext&);
void fn_sub_53E070_0053e070(p3fes::EEContext&);
void fn_sub_53E088_0053e088(p3fes::EEContext&);
void fn_sub_53E0A0_0053e0a0(p3fes::EEContext&);
void fn_sub_53E190_0053e190(p3fes::EEContext&);
void fn_sub_53E1B8_0053e1b8(p3fes::EEContext&);
void fn_sub_53E1D0_0053e1d0(p3fes::EEContext&);
void fn_sub_53E208_0053e208(p3fes::EEContext&);
void fn_sub_53E220_0053e220(p3fes::EEContext&);
void fn_sub_53E238_0053e238(p3fes::EEContext&);
void fn_sub_53E270_0053e270(p3fes::EEContext&);
void fn_sub_53E520_0053e520(p3fes::EEContext&);
void fn_sub_53E6D8_0053e6d8(p3fes::EEContext&);
void fn_sub_53E7D0_0053e7d0(p3fes::EEContext&);
void fn_sub_53E850_0053e850(p3fes::EEContext&);
void fn_sub_53E9C8_0053e9c8(p3fes::EEContext&);
void fn_sub_53EA08_0053ea08(p3fes::EEContext&);
void fn_sub_53EA90_0053ea90(p3fes::EEContext&);
void fn_sub_53EC00_0053ec00(p3fes::EEContext&);
void fn_sub_53EF00_0053ef00(p3fes::EEContext&);
void fn_sub_53EF40_0053ef40(p3fes::EEContext&);
void fn_sub_53F030_0053f030(p3fes::EEContext&);
void fn_sub_53F080_0053f080(p3fes::EEContext&);
void fn_sub_53F148_0053f148(p3fes::EEContext&);
void fn_sub_53F178_0053f178(p3fes::EEContext&);
void fn_sub_53F228_0053f228(p3fes::EEContext&);
void fn_sub_53F268_0053f268(p3fes::EEContext&);
void fn_sub_53F408_0053f408(p3fes::EEContext&);
void fn_sub_53F458_0053f458(p3fes::EEContext&);
void fn_sub_53F508_0053f508(p3fes::EEContext&);
void fn_sub_53F510_0053f510(p3fes::EEContext&);
void fn_sub_53F548_0053f548(p3fes::EEContext&);
void fn_sub_53F580_0053f580(p3fes::EEContext&);
void fn_sub_53F5B0_0053f5b0(p3fes::EEContext&);
void fn_sub_53F7C0_0053f7c0(p3fes::EEContext&);
void fn_sub_53F7D8_0053f7d8(p3fes::EEContext&);
void fn_sub_53F7F0_0053f7f0(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_541978_00541978(p3fes::EEContext&);
void fn_sub_541990_00541990(p3fes::EEContext&);
void fn_sub_5419A8_005419a8(p3fes::EEContext&);
void fn_sub_541A48_00541a48(p3fes::EEContext&);
void fn_sub_541AF0_00541af0(p3fes::EEContext&);
void fn_sub_541B40_00541b40(p3fes::EEContext&);
void fn_sub_541BE8_00541be8(p3fes::EEContext&);
void fn_sub_541C00_00541c00(p3fes::EEContext&);
void fn_sub_541C18_00541c18(p3fes::EEContext&);
void fn_sub_541C30_00541c30(p3fes::EEContext&);
void fn_sub_541C48_00541c48(p3fes::EEContext&);
void fn_sub_542050_00542050(p3fes::EEContext&);
void fn_sub_542F90_00542f90(p3fes::EEContext&);
void fn_sub_542FA0_00542fa0(p3fes::EEContext&);
void fn_sub_542FD8_00542fd8(p3fes::EEContext&);
void fn_sub_542FF0_00542ff0(p3fes::EEContext&);
void fn_sub_5430D0_005430d0(p3fes::EEContext&);
void fn_sub_5430E0_005430e0(p3fes::EEContext&);
void fn_sub_543160_00543160(p3fes::EEContext&);
void fn_sub_543190_00543190(p3fes::EEContext&);
void fn_sub_5431C0_005431c0(p3fes::EEContext&);
void fn_sub_543250_00543250(p3fes::EEContext&);
void fn_sub_5433D8_005433d8(p3fes::EEContext&);
void fn_sub_5433F8_005433f8(p3fes::EEContext&);
void fn_sub_543430_00543430(p3fes::EEContext&);
void fn_sub_543470_00543470(p3fes::EEContext&);
void fn_sub_543628_00543628(p3fes::EEContext&);
void fn_sub_5436B8_005436b8(p3fes::EEContext&);
void fn_sub_5436D0_005436d0(p3fes::EEContext&);
void fn_sub_543700_00543700(p3fes::EEContext&);
void fn_sub_543858_00543858(p3fes::EEContext&);
void fn_sub_543A80_00543a80(p3fes::EEContext&);
void fn_sub_543B08_00543b08(p3fes::EEContext&);
void fn_sub_543EE0_00543ee0(p3fes::EEContext&);
void fn_sub_545440_00545440(p3fes::EEContext&);
void fn_sub_549EA0_00549ea0(p3fes::EEContext&);
void fn_sub_54CBA0_0054cba0(p3fes::EEContext&);
void fn_sub_560BE0_00560be0(p3fes::EEContext&);
void fn_sub_560C28_00560c28(p3fes::EEContext&);
void fn_sub_5611E0_005611e0(p3fes::EEContext&);
void fn_sub_5653C0_005653c0(p3fes::EEContext&);
void fn_sub_5653D8_005653d8(p3fes::EEContext&);
void fn_sub_5653F0_005653f0(p3fes::EEContext&);
void fn_sub_565408_00565408(p3fes::EEContext&);
void fn_sub_565438_00565438(p3fes::EEContext&);
void fn_sub_565450_00565450(p3fes::EEContext&);
void fn_sub_565468_00565468(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00535DC0 sub_535DC0 -- 8 bytes; leaf frame (no stack)
// Getter: the float at +36 into $f0.
void sub_535DC0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x00535dc0
    enter(ctx, 2);  // entry check point + this block's cycles
    lwc1(f0, a0, 36);
}

// 0x00535DC8 sub_535DC8 -- 8 bytes; leaf frame (no stack)
// Setter: the float $f12 into +40.
void sub_535DC8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x00535dc8
    enter(ctx, 2);  // entry check point + this block's cycles
    swc1(f12, a0, 40);
}

// 0x00535DD0 sub_535DD0 -- 8 bytes; leaf frame (no stack)
// Getter: the float at +40 into $f0.
void sub_535DD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x00535dd0
    enter(ctx, 2);  // entry check point + this block's cycles
    lwc1(f0, a0, 40);
}

// 0x00537490 sub_537490 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty hook of the ADX key module).
void sub_537490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00537490
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00537498 sub_537498 -- 24 bytes; leaf frame (no stack)
// Sets the ADX key module callback: function 0x7838D0 = $a0, its argument 0x7838D4 = $a1; returns 0.
void sub_537498(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00537498
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x780000;
    v1 = 0x780000;
    sw(a0, v0, 14544);  // 0x7838D0
    v0 = 0;
    sw(a1, v1, 14548);  // 0x7838D4
}

// 0x005374B0 sub_5374B0 -- 52 bytes; frame 0x10: ra sp+0x0
// Calls the callback 0x7838D0 (when set) as fn(arg 0x7838D4, $a0) through `jalr`; returns 0.
void sub_5374B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005374b0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 14544);  // 0x7838D0
    a1 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x005374c8
        charge(ctx, 3);
        v0 = 0x780000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5374CCu);  // $ra = the return address
        lw(a0, v0, 14548);
        call_ptr(ctx, jt);
    }
    // 0x005374d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x005376E0 sub_5376E0 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADX keys for the built-in phrase: counts an init (sub_5374E8) when none yet, then derives the three keys of
// "CRI-MW" (sub_537528, length 6) into *$a0, *$a1, *$a2; returns 0.
void sub_5376E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005376e0
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 14540);  // 0x7838CC
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (v1 == 0) {
        // 0x0053770c
        charge(ctx, 2);
        jal(ctx, 0x53770Cu, gen::fn_sub_5374E8_005374e8);
    }
    // 0x00537714
    charge(ctx, 14);
    a0 = 0x7C0000;
    a2 = s0;
    a3 = s1;
    t0 = s2;
    a0 = addiu(a0, 6584);  // "CRI-MW"
    a1 = 6;
    jal(ctx, 0x537728u, gen::fn_sub_537528_00537528);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00537750 sub_537750 -- 32 bytes; leaf frame (no stack)
// One step of the 16-bit key stream: *a0 = *a0 * *a1 + *a2 (halfwords); returns 0.
void sub_537750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00537750
    enter(ctx, 8);  // entry check point + this block's cycles
    lhu(a3, a1, 0);
    v0 = 0;
    lhu(a1, a0, 0);
    lhu(v1, a2, 0);
    mult(a1, a1, a3);
    v1 = addu(v1, a1);
    sh(v1, a0, 0);
}

// 0x005377D0 sub_5377D0 -- 52 bytes; frame 0x10: ra sp+0x0
// ADX decoder finish: clears the 16 decoder objects (sub_54CBA0), drops an init count (sub_537508) and zeroes
// the 16 x 260-byte object table at 0x7838F0 (memset, tail call).
void sub_5377D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005377d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5377D8u, gen::fn_sub_54CBA0_0054cba0);
    jal(ctx, 0x5377E0u, gen::fn_sub_537508_00537508);
    a0 = 0x780000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 14576);  // &0x7838F0
    a2 = 4160;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00537F18 sub_537F18 -- 12 bytes; leaf frame (no stack)
// Stores $a1 at +128 and $a2 at +132.
void sub_537F18(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00537f18
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a2, a0, 132);
    sw(a1, a0, 128);
}

// 0x00538408 sub_538408 -- 8 bytes; leaf frame (no stack)
// Getter: the word at +8.
void sub_538408(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00538408
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 8);
}

// 0x00538B00 sub_538B00 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Decoder server: for the 16 objects at 0x7838F0 (260 bytes each), runs sub_5389B0 on each whose s16 state at +0
// is 1.
void sub_538B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00538b00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 14576);  // &0x7838F0
    sd(s1, sp, 0x8);
    s1 = 15;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00538b28
        charge(ctx, 3);
        lh(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00538b34
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x538B34u, gen::fn_sub_5389B0_005389b0);
            s1 = addiu(s1, -1);
        }
        // 0x00538b40
        charge(ctx, 2);
        s0 = addiu(s0, 260);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00538b48
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053B278 sub_53B278 -- 36 bytes; frame 0x10: ra sp+0x0
// Removes the ROFS device (sub_53B2A0) inside __env_lock / __env_unlock.
void sub_53B278(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b278
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53B280u, gen::fn___env_lock_0053b598);
    jal(ctx, 0x53B288u, gen::fn_sub_53B2A0_0053b2a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___env_unlock_0053b5a0(ctx);  // tail call
}

// 0x0053B3D8 sub_53B3D8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Removes a ROFS volume (sub_53B408) inside __env_lock / __env_unlock.
void sub_53B3D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b3d8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53B3E4u, gen::fn___env_lock_0053b598);
    a0 = s0;
    jal(ctx, 0x53B3ECu, gen::fn_sub_53B408_0053b408);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn___env_unlock_0053b5a0(ctx);  // tail call
}

// 0x0053B468 sub_53B468 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Whether the ROFS volume $a0 is registered (sub_53B4A0), inside __env_lock / __env_unlock; returns its $v0.
void sub_53B468(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b468
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53B474u, gen::fn___env_lock_0053b598);
    a0 = s0;
    jal(ctx, 0x53B47Cu, gen::fn_sub_53B4A0_0053b4a0);
    s0 = v0;
    jal(ctx, 0x53B484u, gen::fn___env_unlock_0053b5a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053B6F8 sub_53B6F8 -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// ADXF public wrapper: sub_53B760($a0..$a3) between the ADXF lock and unlock (sub_53E088 / sub_53E0A0).
void sub_53B6F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b6f8
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
    jal(ctx, 0x53B71Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x53B730u, gen::fn_sub_53B760_0053b760);
    s0 = v0;
    jal(ctx, 0x53B738u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053BC88 sub_53BC88 -- 136 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// ADXF public wrapper: loads a partition by range, no wait (sub_53BD10, six arguments) under the ADXF lock.
void sub_53BC88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053bc88
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s5 = t1;
    jal(ctx, 0x53BCBCu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    t1 = s5;
    jal(ctx, 0x53BCD8u, gen::fn_sub_53BD10_0053bd10);
    s0 = v0;
    jal(ctx, 0x53BCE0u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0053BD50 sub_53BD50 -- 136 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// ADXF public wrapper: loads a partition by file name, extended form (sub_53BDD8, six arguments) under the ADXF
// lock.
void sub_53BD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053bd50
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s5 = t1;
    jal(ctx, 0x53BD84u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    t1 = s5;
    jal(ctx, 0x53BDA0u, gen::fn_sub_53BDD8_0053bdd8);
    s0 = v0;
    jal(ctx, 0x53BDA8u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0053BE28 sub_53BE28 -- 136 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// ADXF public wrapper: loads a partition by range, extended form (sub_53BEB0, six arguments) under the ADXF lock.
void sub_53BE28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053be28
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s5 = t1;
    jal(ctx, 0x53BE5Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    t1 = s5;
    jal(ctx, 0x53BE78u, gen::fn_sub_53BEB0_0053beb0);
    s0 = v0;
    jal(ctx, 0x53BE80u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0053C1D8 sub_53C1D8 -- 36 bytes; frame 0x10: ra sp+0x0
// ADXF public wrapper: sub_53C200() under the ADXF lock (unlock as a tail call).
void sub_53C1D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c1d8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53C1E0u, gen::fn_sub_53E088_0053e088);
    jal(ctx, 0x53C1E8u, gen::fn_sub_53C200_0053c200);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53E0A0_0053e0a0(ctx);  // tail call
}

// 0x0053C720 sub_53C720 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: a partition's file count (sub_53C758) under the ADXF lock.
void sub_53C720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c720
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53C72Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53C734u, gen::fn_sub_53C758_0053c758);
    s0 = v0;
    jal(ctx, 0x53C73Cu, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053CA78 sub_53CA78 -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// ADXF public wrapper: opens a handle on a sector range (sub_53CAE0) under the ADXF lock; returns the handle.
void sub_53CA78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ca78
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
    jal(ctx, 0x53CA9Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x53CAB0u, gen::fn_sub_53CAE0_0053cae0);
    s0 = v0;
    jal(ctx, 0x53CAB8u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0053CC78 sub_53CC78 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXF public wrapper: opens a handle on a partition entry (sub_53CCC0) under the ADXF lock; returns the handle.
void sub_53CC78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053cc78
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x53CC8Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x53CC98u, gen::fn_sub_53CCC0_0053ccc0);
    s0 = v0;
    jal(ctx, 0x53CCA0u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0053D040 sub_53D040 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXF public wrapper: the checked ReadSj32 (sub_53D098) under the ADXF lock.
void sub_53D040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d040
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53D05Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53D06Cu, gen::fn_sub_53D098_0053d098);
    s0 = v0;
    jal(ctx, 0x53D074u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D128 sub_53D128 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXF public wrapper: sub_53D180 (the thunk to sub_53D098) under the ADXF lock.
void sub_53D128(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d128
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53D144u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53D154u, gen::fn_sub_53D180_0053d180);
    s0 = v0;
    jal(ctx, 0x53D15Cu, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D418 sub_53D418 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: stops a read with completion (sub_53D450) under the ADXF lock.
void sub_53D418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d418
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53D424u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53D42Cu, gen::fn_sub_53D450_0053d450);
    s0 = v0;
    jal(ctx, 0x53D434u, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053D540 sub_53D540 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: stops a read without completion (sub_53D578) under the ADXF lock.
void sub_53D540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d540
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53D54Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53D554u, gen::fn_sub_53D578_0053d578);
    s0 = v0;
    jal(ctx, 0x53D55Cu, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053D790 sub_53D790 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXF public wrapper: seek (sub_53D7E8; type 0 start, 1 current, 2 end) under the ADXF lock.
void sub_53D790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d790
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53D7ACu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53D7BCu, gen::fn_sub_53D7E8_0053d7e8);
    s0 = v0;
    jal(ctx, 0x53D7C4u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053D900 sub_53D900 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: tell, the current sector (sub_53D938), under the ADXF lock.
void sub_53D900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d900
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53D90Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53D914u, gen::fn_sub_53D938_0053d938);
    s0 = v0;
    jal(ctx, 0x53D91Cu, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053D9E0 sub_53D9E0 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: the file size in bytes (sub_53DA18) under the ADXF lock.
void sub_53D9E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053d9e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53D9ECu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53D9F4u, gen::fn_sub_53DA18_0053da18);
    s0 = v0;
    jal(ctx, 0x53D9FCu, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DA90 sub_53DA90 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXF public wrapper: the requested range (sub_53DAD8: start into *$a1, returns the count) under the ADXF lock.
void sub_53DA90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053da90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x53DAA4u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x53DAB0u, gen::fn_sub_53DAD8_0053dad8);
    s0 = v0;
    jal(ctx, 0x53DAB8u, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0053DB28 sub_53DB28 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: sectors read by the last request (sub_53DB60) under the ADXF lock.
void sub_53DB28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053db28
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53DB34u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53DB3Cu, gen::fn_sub_53DB60_0053db60);
    s0 = v0;
    jal(ctx, 0x53DB44u, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053DC70 sub_53DC70 -- 120 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// ADXF public wrapper: a partition entry's range (sub_53DCE8, five arguments) under the ADXF lock.
void sub_53DC70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dc70
    enter(ctx, 30);  // entry check point + this block's cycles
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
    jal(ctx, 0x53DC9Cu, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    jal(ctx, 0x53DCB4u, gen::fn_sub_53DCE8_0053dce8);
    s0 = v0;
    jal(ctx, 0x53DCBCu, gen::fn_sub_53E0A0_0053e0a0);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0053DF40 sub_53DF40 -- 12 bytes; leaf frame (no stack)
// Stores $a0 into the ADXF word 0x7852A0.
void sub_53DF40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0053df40
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    sw(a0, v0, 21152);  // 0x7852A0
}

// 0x0053DFC8 sub_53DFC8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: a handle's stream status (sub_53E000) under the ADXF lock.
void sub_53DFC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053dfc8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53DFD4u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53DFDCu, gen::fn_sub_53E000_0053e000);
    s0 = v0;
    jal(ctx, 0x53DFE4u, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053E038 sub_53E038 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXF public wrapper: sub_53E070 (the thunk to sub_5470E8) under the ADXF lock.
void sub_53E038(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e038
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53E044u, gen::fn_sub_53E088_0053e088);
    a0 = s0;
    jal(ctx, 0x53E04Cu, gen::fn_sub_53E070_0053e070);
    s0 = v0;
    jal(ctx, 0x53E054u, gen::fn_sub_53E0A0_0053e0a0);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053E190 sub_53E190 -- 36 bytes; frame 0x10: ra sp+0x0
// ADXT: updates the file-system status (sub_53E1B8, the ADXT_UpdateFsStat thunk) inside the ADX lock stubs.
void sub_53E190(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e190
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x53E198u, gen::fn_sub_539848_00539848);
    jal(ctx, 0x53E1A0u, gen::fn_sub_53E1B8_0053e1b8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053E1D0 sub_53E1D0 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXT: whether the word 0x787538 is set (sub_53E208), inside the ADX lock stubs; returns it.
void sub_53E1D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e1d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x53E1DCu, gen::fn_sub_539848_00539848);
    jal(ctx, 0x53E1E4u, gen::fn_sub_53E208_0053e208);
    s0 = v0;
    jal(ctx, 0x53E1ECu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053E238 sub_53E238 -- 24 bytes; leaf frame (no stack)
// Stores the s16 $a1 little-endian into the two bytes at $a0 (byte by byte, any alignment).
void sub_53E238(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0053e238
    enter(ctx, 6);  // entry check point + this block's cycles
    a1 = sll(a1, 16);
    a1 = sra(a1, 16);
    v0 = srl(a1, 8);
    sb(a1, a0, 0);
    sb(v0, a0, 1);
}

// 0x0053E270 sub_53E270 -- 32 bytes; leaf frame (no stack)
// Stores the word $a1 little-endian into the four bytes at $a0 (byte by byte, any alignment).
void sub_53E270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0053e270
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = srl(a1, 24);
    v1 = srl(a1, 8);
    a2 = srl(a1, 16);
    sb(v0, a0, 3);
    sb(v1, a0, 1);
    sb(a2, a0, 2);
    sb(a1, a0, 0);
}

// 0x0053E7D0 sub_53E7D0 -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADX header writer: *$a2 = 0 when given; -1 when the buffer size $a1 is under 36; else the 0x80 0x00 magic,
// the 32 offset (sub_53E220 at +2), the format (sub_53E6D8 from $a3 at +4), *$a2 = 36 and 0.
void sub_53E7D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e7d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(ra, sp, 0x18);
    a0 = addiu(s0, 2);
    a1 = 32;
    v1 = slti(v0, 36);
    if (s1 != 0) {
        // 0x0053e804
        charge(ctx, 1);
        sw(zero, s1, 0);
    }
    // 0x0053e808
    charge(ctx, 2);
    v0 = si(-1);
    if (v1 == 0) {
        // 0x0053e810
        charge(ctx, 10);
        v0 = si(-128);
        sb(zero, s0, 1);
        link(ctx, 0x53E818u);  // $ra first: the delay slot below depends on it
        sb(v0, s0, 0);
        call(ctx, gen::fn_sub_53E220_0053e220);
        a0 = addiu(s0, 4);
        a1 = s2;
        jal(ctx, 0x53E824u, gen::fn_sub_53E6D8_0053e6d8);
        v0 = 36;
        sw(v0, s1, 0);
        v0 = 0;
    }
    // 0x0053e838 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053E850 sub_53E850 -- 360 bytes; frame 0xA0: s1 sp+0x78, s2 sp+0x80, s3 sp+0x88, s0 sp+0x70, ra sp+0x90
// ADXT_GetHdrInfo(buf $a0, size $a1, info $a2): clears two locals, decodes the header (sub_53E520) and copies
// an 8-word info record (1, or 2 when the decoded byte +0x3C is 6; then six fields of the decoded header) into *$a2;
// "NULL pointer" / short-buffer / bad-header errors through sub_53AE08.
void sub_53E850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053e850
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s1, sp, 0x78);
    s1 = a0;
    sd(s2, sp, 0x80);
    s2 = a1;
    sd(s3, sp, 0x88);
    s3 = a2;
    sd(s0, sp, 0x70);
    sd(ra, sp, 0x90);
    if (s1 != 0) {
        // 0x0053e878
        charge(ctx, 2);
        if (s3 == 0) {
            goto L_0053e880;
        }
        a0 = sp;
        // 0x0053e898
        charge(ctx, 17);
        a1 = 0;
        a2 = 32;
        jal(ctx, 0x53E89Cu, gen::fn_memset_00521408);
        a1 = 0;
        s0 = addiu(sp, 0x20);
        a2 = 64;
        a0 = s0;
        jal(ctx, 0x53E8B0u, gen::fn_memset_00521408);
        a0 = s1;
        a1 = s2;
        a3 = s0;
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x53E8C4u, gen::fn_sub_53E520_0053e520);
        v1 = v0;
        v0 = si(-4);
        a0 = 0x7C0000;
        if (v1 != v0) {
            // 0x0053e8f0
            charge(ctx, 2);
            if (i64(v1) >= 0) {
                lb(v1, sp, 0x5C);
                // 0x0053e910
                charge(ctx, 3);
                v0 = 6;
                if (v1 != v0) {
                    v0 = 1;
                } else {
                    // 0x0053e91c
                    charge(ctx, 1);
                    v0 = 2;
                }
                // 0x0053e920
                charge(ctx, 32);
                sw(v0, sp, 0x0);
                lw(v0, sp, 0x24);
                lb(v1, sp, 0x23);
                lb(a0, sp, 0x22);
                lw(a1, sp, 0x28);
                lh(a2, sp, 0x2E);
                lw(a3, sp, 0x34);
                lw(t0, sp, 0x3C);
                sw(v0, sp, 0x4);
                sw(v1, sp, 0x8);
                sw(a0, sp, 0xC);
                sw(a1, sp, 0x10);
                sw(a2, sp, 0x14);
                sw(a3, sp, 0x18);
                sw(t0, sp, 0x1C);
                ldl(v0, sp, 0x7);
                ldr(v0, sp, 0x0);
                ldl(v1, sp, 0xF);
                ldr(v1, sp, 0x8);
                ldl(a0, sp, 0x17);
                ldr(a0, sp, 0x10);
                ldl(a1, sp, 0x1F);
                ldr(a1, sp, 0x18);
                sdl(v0, s3, 7);
                sdr(v0, s3, 0);
                sdl(v1, s3, 15);
                sdr(v1, s3, 8);
                sdl(a0, s3, 23);
                sdr(a0, s3, 16);
                sdl(a1, s3, 31);
                sdr(a1, s3, 24);
                ld(s0, sp, 0x70);
            } else {
                // 0x0053e8f8
                charge(ctx, 5);
                a0 = 0x7C0000;
                a0 = addiu(a0, 8752);  // "E02041201: Buffer size is too short.(ADXT_GetHdrInfo)"
                jal(ctx, 0x53E8FCu, gen::fn_sub_53AE08_0053ae08);
                ld(s0, sp, 0x70);
            }
        } else {
            // 0x0053e8dc
            charge(ctx, 4);
            a0 = addiu(a0, 8688);
            jal(ctx, 0x53E8DCu, gen::fn_sub_53AE08_0053ae08);
            ld(s0, sp, 0x70);
        }
        // 0x0053e9a0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x78);
        ld(s2, sp, 0x80);
        ld(s3, sp, 0x88);
        ld(ra, sp, 0x90);
        sp = addiu(sp, 0xA0);
        return;
    }
L_0053e880:
    charge(ctx, 5);
    a0 = 0x7C0000;
    a0 = addiu(a0, 8632);  // "E02041201: NULL pointer is specified.(ADXT_GetHdrInfo)"
    jal(ctx, 0x53E884u, gen::fn_sub_53AE08_0053ae08);
    ld(s0, sp, 0x70);
    // 0x0053e9a0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x78);
    ld(s2, sp, 0x80);
    ld(s3, sp, 0x88);
    ld(ra, sp, 0x90);
    sp = addiu(sp, 0xA0);
}

// 0x0053E9B8 sceLibgcc32GetErxEntries_3 -- 12 bytes; leaf frame (no stack)
// Returns the ADXT version string ("ADXT/PS2EE Ver.9.44 ...").
void sceLibgcc32GetErxEntries_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0053e9b8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 8808);  // "\nADXT/PS2EE Ver.9.44 Build:Feb 28 2005 19:25:20\n"
}

// 0x0053E9C8 sub_53E9C8 -- 12 bytes; leaf frame (no stack)
// Stores $a0 into the ADXT word 0x78755C.
void sub_53E9C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0053e9c8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    sw(a0, v0, 30044);  // 0x78755C
}

// 0x0053EA08 sub_53EA08 -- 40 bytes; frame 0x10: ra sp+0x0
// ADXT: counts a server call (0x787568) and runs the server (sub_549EA0, ADXT_ExecServer; tail call).
void sub_53EA08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ea08
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x780000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 30056);  // &0x787568
    lw(v0, v1, 0);  // 0x787568
    ld(ra, sp, 0x0);
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x787568
    sp = addiu(sp, 0x10);
    gen::fn_sub_549EA0_00549ea0(ctx);  // tail call
}

// 0x0053EC00 sub_53EC00 -- 28 bytes; frame 0x10: ra sp+0x0
// ADXT: clears the word 0x787550 and tails into sub_53EA90 (the ADXT init with its server entries).
void sub_53EC00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ec00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    sw(zero, v0, 30032);  // 0x787550
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53EA90_0053ea90(ctx);  // tail call
}

// 0x0053EF00 sub_53EF00 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXT public wrapper: adxt_EntryFnameRange (sub_53EF40, two arguments) inside the ADX lock stubs.
void sub_53EF00(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ef00
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x53EF14u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x53EF20u, gen::fn_sub_53EF40_0053ef40);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F030 sub_53F030 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXT public wrapper: enters a partition file into the play list (sub_53F080) inside the ADX lock stubs.
void sub_53F030(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f030
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53F04Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53F05Cu, gen::fn_sub_53F080_0053f080);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F148 sub_53F148 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXT public wrapper: restarts the stream (sub_53F178) inside the ADX lock stubs.
void sub_53F148(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f148
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53F154u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x53F15Cu, gen::fn_sub_53F178_0053f178);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F228 sub_53F228 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXT public wrapper: sub_53F268 (two arguments) inside the ADX lock stubs.
void sub_53F228(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f228
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x53F23Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x53F248u, gen::fn_sub_53F268_0053f268);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F408 sub_53F408 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADXT public wrapper: sub_53F458 (three arguments) inside the ADX lock stubs.
void sub_53F408(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f408
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x53F424u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x53F434u, gen::fn_sub_53F458_0053f458);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F508 sub_53F508 -- 8 bytes; leaf frame (no stack)
// Empty function (`jr $ra`).
void sub_53F508(EEContext& ctx) {
    using namespace hg;
    // 0x0053f508
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0053F510 sub_53F510 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXT public wrapper: sub_53F548 inside the ADX lock stubs; returns its $v0.
void sub_53F510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f510
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53F51Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x53F524u, gen::fn_sub_53F548_0053f548);
    s0 = v0;
    jal(ctx, 0x53F52Cu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0053F580 sub_53F580 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXT public wrapper: sub_53F5B0 inside the ADX lock stubs.
void sub_53F580(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f580
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x53F58Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x53F594u, gen::fn_sub_53F5B0_0053f5b0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0053F7C0 sub_53F7C0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 0 (sub_5653C0).
void sub_53F7C0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f7c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5653C0_005653c0(ctx);  // tail call
}

// 0x0053F7D8 sub_53F7D8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 1 (sub_5653D8).
void sub_53F7D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f7d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5653D8_005653d8(ctx);  // tail call
}

// 0x0053F7F0 sub_53F7F0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 2 (sub_5653F0).
void sub_53F7F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f7f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5653F0_005653f0(ctx);  // tail call
}

// 0x0053F808 atan2l_0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 3 (sub_565408); IDA's name is a mislabel.
void atan2l_0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f808
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565408_00565408(ctx);  // tail call
}

// 0x0053F820 cosl_0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM file-system servers, type 4 (SVM_ExecSvrFs); IDA's name is a mislabel.
void cosl_0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f820
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_SVM_ExecSvrFs_00565420(ctx);  // tail call
}

// 0x0053F838 coshl_0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 5 (sub_565438); IDA's name is a mislabel.
void coshl_0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f838
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565438_00565438(ctx);  // tail call
}

// 0x0053F850 expl_0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 6 (sub_565450); IDA's name is a mislabel.
void expl_0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f850
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565450_00565450(ctx);  // tail call
}

// 0x0053F868 hypotf_0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: runs the SVM servers of type 7 (sub_565468); IDA's name is a mislabel.
void hypotf_0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f868
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565468_00565468(ctx);  // tail call
}

// 0x00541978 sub_541978 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXRNA thunk: PS2RNA_StartPcmTrans.
void sub_541978(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541978
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_PS2RNA_StartPcmTrans_00560558(ctx);  // tail call
}

// 0x00541990 sub_541990 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXRNA thunk: PS2RNA_StopPcmTrans.
void sub_541990(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541990
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_PS2RNA_StopPcmTrans_005605e8(ctx);  // tail call
}

// 0x005419A8 sub_5419A8 -- 56 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXRNA thunk with the target body (0x560670) inlined: for $a0 < 2 the word table 0x7A9430[$a0], else 0.
void sub_5419A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005419a8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00560670
    charge(ctx, 4);
    v1 = sll(a0, 2);
    a0 = sltiu(a0, 2);
    v0 = 0;
    if (a0 != 0) {
        // 0x00560680
        charge(ctx, 3);
        v0 = 0x7B0000;
        v0 = addu(v0, v1);
        lw(v0, v0, -27600);
    }
    // 0x0056068c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541A48 sub_541A48 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXRNA thunk: sub_560BE0 (prints "not implemented").
void sub_541A48(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541a48
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560BE0_00560be0(ctx);  // tail call
}

// 0x00541A60 atan2l_1 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXRNA thunk: sub_560C28; IDA's name is a mislabel.
void atan2l_1(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541a60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560C28_00560c28(ctx);  // tail call
}

// 0x00541AF0 sub_541AF0 -- 52 bytes; frame 0x10: ra sp+0x0
// ADXRNA_GetStat: prints "ADXRNA_GetStat: not implemented" (sub_541760) and spins forever.
void sub_541AF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541af0
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = 0x7C0000;
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 9624);  // "ADXRNA_GetStat: not implemented\n"
    jal(ctx, 0x541AFCu, gen::fn_sub_541760_00541760);
    for (;;) {
        // 0x00541b08
        charge(ctx, 7);
        backedge(ctx);
    }
}

// 0x00541B40 sub_541B40 -- 20 bytes; frame 0x10: ra sp+0x0
// ADXRNA thunk: sub_5611E0 (PS2RNA_SetStartSmpl, "not implemented").
void sub_541B40(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541b40
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5611E0_005611e0(ctx);  // tail call
}

// 0x00541BE8 sub_541BE8 -- 68 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXRNA getter (target 0x561428 inlined): 0 when the mode word 0x7A93F8 is 1 and the count 0x7A93F0 is <= 0,
// else the handle's word +48.
void sub_541BE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541be8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00561428
    charge(ctx, 5);
    v0 = 0x7B0000;
    a1 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a2 = a0;
    if (v1 == a1) {
        // 0x0056143c
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_0056144c;
        }
        // 0x00561450 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0056144c:
    charge(ctx, 1);
    lw(v0, a2, 48);
    // 0x00561450 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541C00 sub_541C00 -- 68 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXRNA getter (target 0x561458 inlined): as sub_541BE8, the handle's word +56.
void sub_541C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541c00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00561458
    charge(ctx, 5);
    v0 = 0x7B0000;
    a1 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a2 = a0;
    if (v1 == a1) {
        // 0x0056146c
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_0056147c;
        }
        // 0x00561480 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0056147c:
    charge(ctx, 1);
    lw(v0, a2, 56);
    // 0x00561480 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541C18 sub_541C18 -- 76 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXRNA getter (target 0x561488 inlined): as sub_541BE8, the handle's word +64 + 4 * $a1 (per channel).
void sub_541C18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541c18
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00561488
    charge(ctx, 6);
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a3 = a0;
    a1 = sll(a1, 2);
    if (v1 == a2) {
        // 0x005614a0
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_005614b0;
        }
        // 0x005614b8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005614b0:
    charge(ctx, 2);
    v1 = addu(a1, a3);
    lw(v0, v1, 64);
    // 0x005614b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541C30 sub_541C30 -- 68 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXRNA getter (target 0x5614C0 inlined): as sub_541BE8, the handle's word +92.
void sub_541C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541c30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005614c0
    charge(ctx, 5);
    v0 = 0x7B0000;
    a1 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a2 = a0;
    if (v1 == a1) {
        // 0x005614d4
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_005614e4;
        }
        // 0x005614e8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005614e4:
    charge(ctx, 1);
    lw(v0, a2, 92);
    // 0x005614e8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541C48 sub_541C48 -- 56 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXRNA getter (target 0x5614F0 inlined): returns 16; reads the count 0x7A93F0 into $v1 when the mode is 1.
void sub_541C48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541c48
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005614f0
    charge(ctx, 5);
    v0 = 0x7B0000;
    a0 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    v0 = 16;
    if (v1 == a0) {
        // 0x00561504
        charge(ctx, 2);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
    }
    // 0x0056150c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541C78 __env_lock_6 -- 8 bytes; leaf frame (no stack)
// Empty lock stub (`jr $ra`).
void __env_lock_6(EEContext& ctx) {
    using namespace hg;
    // 0x00541c78
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00541C80 sqrtl_1 -- 8 bytes; leaf frame (no stack)
// Empty stub (`jr $ra`); IDA's name is a mislabel.
void sqrtl_1(EEContext& ctx) {
    using namespace hg;
    // 0x00541c80
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00541CC0 __env_unlock_6 -- 8 bytes; leaf frame (no stack)
// Empty unlock stub (`jr $ra`).
void __env_unlock_6(EEContext& ctx) {
    using namespace hg;
    // 0x00541cc0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00542050 sub_542050 -- 16 bytes; leaf frame (no stack)
// Setter: the word at +12 + 4 * $a1 = $a2.
void sub_542050(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00542050
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 2);
    a0 = addu(a0, a1);
    sw(a2, a0, 12);
}

// 0x00542F90 sub_542F90 -- 8 bytes; leaf frame (no stack)
// Getter: the word at +52.
void sub_542F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00542f90
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 52);
}

// 0x00542FA0 sub_542FA0 -- 8 bytes; leaf frame (no stack)
// Getter: the word at +156.
void sub_542FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00542fa0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 156);
}

// 0x00542FD8 sub_542FD8 -- 52 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXT thunk on the decoder handle (+4), target 0x538190 inlined: the three u16 at +160, +162, +164 into *$a1,
// *$a2, *$a3.
void sub_542FD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542fd8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00538190
    charge(ctx, 7);
    lhu(v0, a0, 160);
    sh(v0, a1, 0);
    lhu(v1, a0, 162);
    sh(v1, a2, 0);
    lhu(v0, a0, 164);
    sh(v0, a3, 0);
}

// 0x00542FF0 sub_542FF0 -- 64 bytes, 2 chunks; frame 0x10: ra sp+0x0
// ADXT thunk on the decoder handle (+4), target 0x5381B0 inlined: sets the three s16 at +160, +162, +164.
void sub_542FF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542ff0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sll(a1, 16);
    sd(ra, sp, 0x0);
    a2 = sll(a2, 16);
    a3 = sll(a3, 16);
    a1 = sra(a1, 16);
    lw(a0, a0, 4);
    a2 = sra(a2, 16);
    ld(ra, sp, 0x0);
    a3 = sra(a3, 16);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005381b0
    charge(ctx, 4);
    sh(a3, a0, 164);
    sh(a1, a0, 160);
    sh(a2, a0, 162);
}

// 0x005430C0 _M_ctype_facet__CQ24_STL8ios_base_0 -- 8 bytes; leaf frame (no stack)
// Getter: the word at +60; IDA's name is a mislabel.
void _M_ctype_facet__CQ24_STL8ios_base_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005430c0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 60);
}

// 0x005430D0 sub_5430D0 -- 8 bytes; leaf frame (no stack)
// Getter: the word at +64.
void sub_5430D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005430d0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 64);
}

// 0x005430E0 sub_5430E0 -- 8 bytes; leaf frame (no stack)
// Getter: the word at +68.
void sub_5430E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005430e0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 68);
}

// 0x00543160 sub_543160 -- 24 bytes; frame 0x10: ra sp+0x0
// ADXT thunk on the decoder handle (+4): bits per sample (sub_537FE0).
void sub_543160(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543160
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537FE0_00537fe0(ctx);  // tail call
}

// 0x00543190 sub_543190 -- 24 bytes; frame 0x10: ra sp+0x0
// ADXT thunk on the decoder handle (+4): the s16 at +28 (sub_537FF0).
void sub_543190(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543190
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537FF0_00537ff0(ctx);  // tail call
}

// 0x005431C0 sub_5431C0 -- 24 bytes; frame 0x10: ra sp+0x0
// ADXT thunk on the decoder handle (+4): decoded samples (sub_537FF8).
void sub_5431C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005431c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_537FF8_00537ff8(ctx);  // tail call
}

// 0x00543250 sub_543250 -- 24 bytes; frame 0x10: ra sp+0x0
// ADXT thunk on the decoder handle (+4): sub_538038.
void sub_543250(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543250
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_538038_00538038(ctx);  // tail call
}

// 0x005433D8 sub_5433D8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty hook of the ADX encoder).
void sub_5433D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005433d8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005433F8 sub_5433F8 -- 52 bytes; frame 0x10: ra sp+0x0
// ADX encoder: calls the callback 0x790A1C (when set) as fn(arg 0x790A20, $a0) through `jalr`; returns 0.
void sub_5433F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005433f8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 2588);  // 0x790A1C
    a1 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x00543410
        charge(ctx, 3);
        v0 = 0x790000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x543414u);  // $ra = the return address
        lw(a0, v0, 2592);
        call_ptr(ctx, jt);
    }
    // 0x0054341c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00543628 sub_543628 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// ADX encoder keys for "CRI-MW": counts an init (sub_543430) when none yet (0x790A18), then sub_543470 (the key
// calculation, length 6) into *$a0, *$a1, *$a2; returns 0.
void sub_543628(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543628
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 2584);  // 0x790A18
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (v1 == 0) {
        // 0x00543654
        charge(ctx, 2);
        jal(ctx, 0x543654u, gen::fn_sub_543430_00543430);
    }
    // 0x0054365c
    charge(ctx, 14);
    a0 = 0x7C0000;
    a2 = s0;
    a3 = s1;
    t0 = s2;
    a0 = addiu(a0, 9800);  // "CRI-MW"
    a1 = 6;
    jal(ctx, 0x543670u, gen::fn_sub_543470_00543470);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005436B8 sub_5436B8 -- 8 bytes; leaf frame (no stack)
// Returns 256.
void sub_5436B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005436b8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 256;
}

// 0x005436C0 sceLibgcc32GetErxEntries_4 -- 12 bytes; leaf frame (no stack)
// Returns the ADX encoder version string ("ADXENC.DLL Ver.1.10 Feb 28 2005").
void sceLibgcc32GetErxEntries_4(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005436c0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 9864);  // "ADXENC.DLL Ver.1.10 Feb 28 2005"
}

// 0x00543700 sub_543700 -- 344 bytes; frame 0x50: s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// ADX encoder sizes: pads the sample count $a1 to a multiple of 64 (one channel) or 32 (*$t0 = the pad), takes
// the header size (sub_53A3B8), rounds the header to a 2048-byte sector (*$a3), then the stream sizes for $a1 and
// $a2 samples plus the pad (sub_5436D0) into *$t1 and *$t2.
void sub_543700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543700
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t3 = 32;
    sd(s2, sp, 0x10);
    s2 = a0;
    v0 = s2 ^ 0x1;
    v1 = 64;
    if (v0 != 0) v1 = t3;
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 0;
    div(s1, v1);
    sd(s3, sp, 0x18);
    s3 = t0;
    sd(s0, sp, 0x0);
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s5, sp, 0x28);
    s5 = t1;
    sd(s6, sp, 0x30);
    s6 = t2;
    sd(s7, sp, 0x38);
    s7 = a2;
    sd(ra, sp, 0x40);
    if (v1 == 0) {
        brk(ctx, 0x543760u, 0x7u);
    }
    // 0x00543764
    charge(ctx, 61);
    a0 = 1;
    a2 = 4;
    a3 = 4;
    mfhi(t3);
    t3 = subu(v1, t3);
    div(t3, v1);
    mfhi(t0);
    v0 = addu(s1, t0);
    sw(t0, s3, 0);
    t1 = addiu(v0, 31);
    v1 = slti(v0, 0);
    if (v1 != 0) v0 = t1;
    v0 = sra(v0, 5);
    mult(v0, v0, s2);
    s0 = sll(v0, 3);
    s0 = addu(s0, v0);
    jal(ctx, 0x5437A0u, gen::fn_sub_53A3B8_0053a3b8);
    s0 = sll(s0, 1);
    a2 = 2048;
    s0 = addu(s0, v0);
    a1 = addiu(s0, 4);
    s0 = addiu(s0, 2051);
    a0 = slti(a1, 0);
    v1 = a1;
    if (a0 != 0) v1 = s0;
    a0 = s2;
    v1 = sra(v1, 11);
    v1 = sll(v1, 11);
    a1 = subu(a1, v1);
    a2 = subu(a2, a1);
    a3 = addiu(a2, 2047);
    a1 = slti(a2, 0);
    v1 = a2;
    if (a1 != 0) v1 = a3;
    v1 = sra(v1, 11);
    a1 = sll(v1, 11);
    v1 = subu(a2, a1);
    v0 = addu(v0, v1);
    sw(v0, s4, 0);
    a1 = v0;
    lw(a2, s3, 0);
    a2 = addu(s1, a2);
    jal(ctx, 0x543808u, gen::fn_sub_5436D0_005436d0);
    a0 = s2;
    sw(v0, s5, 0);
    lw(a2, s3, 0);
    lw(a1, s4, 0);
    a2 = addu(s7, a2);
    jal(ctx, 0x543820u, gen::fn_sub_5436D0_005436d0);
    sw(v0, s6, 0);
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
}

// 0x00543858 sub_543858 -- 100 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// sub_539AE0 with seven local out-pointers; the two bytes it writes at sp+0x13 and sp+0x15 go to *$a2 and *$a3.
void sub_543858(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543858
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t3 = t0;
    sd(s0, sp, 0x20);
    s0 = a3;
    sd(s1, sp, 0x28);
    s1 = a2;
    sw(t1, sp, 0x0);
    t1 = addiu(sp, 0x14);
    v0 = addiu(sp, 0x18);
    t0 = addiu(sp, 0x13);
    a2 = addiu(sp, 0x10);
    a3 = addiu(sp, 0x12);
    t2 = addiu(sp, 0x15);
    sd(ra, sp, 0x30);
    link(ctx, 0x543890u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x8);
    call(ctx, gen::fn_sub_539AE0_00539ae0);
    lb(v1, sp, 0x15);
    lb(a0, sp, 0x13);
    sw(v1, s0, 0);
    ld(ra, sp, 0x30);
    sw(a0, s1, 0);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    sp = addiu(sp, 0x40);
}

// 0x00543A80 sub_543A80 -- 36 bytes; frame 0x10: ra sp+0x0
// Zeroes the 192-byte table at 0x7921F8 (memset, tail call).
void sub_543A80(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543a80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x790000;
    sd(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 8696);  // &0x7921F8
    a2 = 192;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00543B08 sub_543B08 -- 52 bytes; frame 0x10: ra sp+0x0
// Clears a 12-byte record when $a0 is set (first byte, then memset; tail call); returns $a0.
void sub_543B08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00543b08
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00543b30
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00543b18
    charge(ctx, 6);
    ld(ra, sp, 0x0);
    a1 = 0;
    a2 = 12;
    sb(zero, v0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00543EE0 sub_543EE0 -- 24 bytes; leaf frame (no stack)
// The s8 at $a0 + 88 + $a1 for a non-null $a0, else 0.
void sub_543EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00543ee0
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = addu(a1, a0);
    v0 = 0;
    if (a0 != 0) {
        // 0x00543eec
        charge(ctx, 1);
        lb(v0, a1, 88);
    }
    // 0x00543ef0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00545440 sub_545440 -- 8 bytes; leaf frame (no stack)
// Getter: the s8 at +1.
void sub_545440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00545440
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 1);
}

}  // namespace p3fes::game
