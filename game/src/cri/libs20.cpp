// Slice libs20 (Phase 5): 100 small CRI middleware and SDK functions of SLUS_216.21, hand-decompiled from p3fes_handgen
// bodies. Every body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); on top of that each has its role, its proposed name where the binary's own
// strings give one (htCiOpen, htCiLoadDirInfo, mfCiOpen, DTR_Init, the PS2RNA_* stubs) and, for the ADXT error check
// and the host / memory file handles, the field offsets named in libs20.h (l20::). Groups, in address order: the locked
// ADXT entry points and the error check (0x54AA48..), the ACS sound-server thunks and bit helpers (0x54D010..), AIX
// info readers, CRI CFG and the CVFS finish (0x554998..), SRD settings (0x557F60..), DTR (0x559200..), the host file
// system HTCI (0x55B6D8..), LSC and the memory files mfCi (0x55D6F0..), the PS2RNA "not implemented" stubs (0x560DE8..)
// and the DTX URPC commands (0x563DD0..). Pair tests: tests/game/test_libs20.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs20.h"

namespace p3fes::recomp_gen {
void fn_DTX_CallUrpc_00559c10(p3fes::EEContext&);
void fn_SRD_WaitComplete_00557e50(p3fes::EEContext&);
void fn_WTLS_get_table_0055d210(p3fes::EEContext&);
void fn___errno_3_00558128(p3fes::EEContext&);
void fn___errno_5_00558600(p3fes::EEContext&);
void fn___errno_6_005589f8(p3fes::EEContext&);
void fn___errno_7_00558a60(p3fes::EEContext&);
void fn___errno_9_0055d230(p3fes::EEContext&);
void fn_coshl_7_0055b718(p3fes::EEContext&);
void fn_cosl_7_0055b700(p3fes::EEContext&);
void fn_expl_7_0055b730(p3fes::EEContext&);
void fn_hypotf_7_0055b748(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nullsub_144_005615a8(p3fes::EEContext&);
void fn_pvalloc_0_0054d618(p3fes::EEContext&);
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398(p3fes::EEContext&);
void fn_sceInsockAbortGethostbyaddr_2_0054b348(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_6_0055b6d8(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_7_0055d188(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_8_0055d200(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_set_new_handler__FPFv_v_0054c0e8(p3fes::EEContext&);
void fn_sqrtl_5_0054d5b0(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_534B60_00534b60(p3fes::EEContext&);
void fn_sub_535050_00535050(p3fes::EEContext&);
void fn_sub_5350D0_005350d0(p3fes::EEContext&);
void fn_sub_535170_00535170(p3fes::EEContext&);
void fn_sub_535388_00535388(p3fes::EEContext&);
void fn_sub_535390_00535390(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_542008_00542008(p3fes::EEContext&);
void fn_sub_542F68_00542f68(p3fes::EEContext&);
void fn_sub_546368_00546368(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_5491B0_005491b0(p3fes::EEContext&);
void fn_sub_549310_00549310(p3fes::EEContext&);
void fn_sub_549390_00549390(p3fes::EEContext&);
void fn_sub_549450_00549450(p3fes::EEContext&);
void fn_sub_54AA48_0054aa48(p3fes::EEContext&);
void fn_sub_54AA80_0054aa80(p3fes::EEContext&);
void fn_sub_54AAB8_0054aab8(p3fes::EEContext&);
void fn_sub_54AAF0_0054aaf0(p3fes::EEContext&);
void fn_sub_54AB28_0054ab28(p3fes::EEContext&);
void fn_sub_54AB78_0054ab78(p3fes::EEContext&);
void fn_sub_54AE80_0054ae80(p3fes::EEContext&);
void fn_sub_54AFA8_0054afa8(p3fes::EEContext&);
void fn_sub_54AFD8_0054afd8(p3fes::EEContext&);
void fn_sub_54AFF0_0054aff0(p3fes::EEContext&);
void fn_sub_54B028_0054b028(p3fes::EEContext&);
void fn_sub_54B030_0054b030(p3fes::EEContext&);
void fn_sub_54B070_0054b070(p3fes::EEContext&);
void fn_sub_54B1D0_0054b1d0(p3fes::EEContext&);
void fn_sub_54B230_0054b230(p3fes::EEContext&);
void fn_sub_54B388_0054b388(p3fes::EEContext&);
void fn_sub_54C580_0054c580(p3fes::EEContext&);
void fn_sub_54C670_0054c670(p3fes::EEContext&);
void fn_sub_54CAD0_0054cad0(p3fes::EEContext&);
void fn_sub_54CB08_0054cb08(p3fes::EEContext&);
void fn_sub_54D010_0054d010(p3fes::EEContext&);
void fn_sub_54D560_0054d560(p3fes::EEContext&);
void fn_sub_54D588_0054d588(p3fes::EEContext&);
void fn_sub_54D5D8_0054d5d8(p3fes::EEContext&);
void fn_sub_54D668_0054d668(p3fes::EEContext&);
void fn_sub_54D818_0054d818(p3fes::EEContext&);
void fn_sub_54D88C_0054d88c(p3fes::EEContext&);
void fn_sub_54DB38_0054db38(p3fes::EEContext&);
void fn_sub_54DBE8_0054dbe8(p3fes::EEContext&);
void fn_sub_54DBF0_0054dbf0(p3fes::EEContext&);
void fn_sub_54DC48_0054dc48(p3fes::EEContext&);
void fn_sub_54DDF8_0054ddf8(p3fes::EEContext&);
void fn_sub_54DE18_0054de18(p3fes::EEContext&);
void fn_sub_54E7D8_0054e7d8_at_0054e808(p3fes::EEContext&);
void fn_sub_54E810_0054e810(p3fes::EEContext&);
void fn_sub_552630_00552630(p3fes::EEContext&);
void fn_sub_554998_00554998(p3fes::EEContext&);
void fn_sub_554A00_00554a00(p3fes::EEContext&);
void fn_sub_554AA0_00554aa0(p3fes::EEContext&);
void fn_sub_554AE8_00554ae8(p3fes::EEContext&);
void fn_sub_5556A0_005556a0(p3fes::EEContext&);
void fn_sub_555720_00555720(p3fes::EEContext&);
void fn_sub_555738_00555738(p3fes::EEContext&);
void fn_sub_555820_00555820(p3fes::EEContext&);
void fn_sub_555A08_00555a08(p3fes::EEContext&);
void fn_sub_557F60_00557f60(p3fes::EEContext&);
void fn_sub_5580F8_005580f8(p3fes::EEContext&);
void fn_sub_558108_00558108(p3fes::EEContext&);
void fn_sub_558118_00558118(p3fes::EEContext&);
void fn_sub_5585F0_005585f0(p3fes::EEContext&);
void fn_sub_558610_00558610(p3fes::EEContext&);
void fn_sub_558678_00558678(p3fes::EEContext&);
void fn_sub_5586B0_005586b0(p3fes::EEContext&);
void fn_sub_5586E8_005586e8(p3fes::EEContext&);
void fn_sub_558720_00558720(p3fes::EEContext&);
void fn_sub_558758_00558758(p3fes::EEContext&);
void fn_sub_558848_00558848(p3fes::EEContext&);
void fn_sub_558898_00558898(p3fes::EEContext&);
void fn_sub_558968_00558968(p3fes::EEContext&);
void fn_sub_558978_00558978(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_5589A8_005589a8(p3fes::EEContext&);
void fn_sub_5589B8_005589b8(p3fes::EEContext&);
void fn_sub_558C20_00558c20(p3fes::EEContext&);
void fn_sub_558C98_00558c98(p3fes::EEContext&);
void fn_sub_558D00_00558d00(p3fes::EEContext&);
void fn_sub_559200_00559200(p3fes::EEContext&);
void fn_sub_5596D0_005596d0(p3fes::EEContext&);
void fn_sub_559700_00559700(p3fes::EEContext&);
void fn_sub_559E30_00559e30(p3fes::EEContext&);
void fn_sub_55B760_0055b760(p3fes::EEContext&);
void fn_sub_55B7C8_0055b7c8(p3fes::EEContext&);
void fn_sub_55B848_0055b848(p3fes::EEContext&);
void fn_sub_55BA50_0055ba50(p3fes::EEContext&);
void fn_sub_55BB08_0055bb08(p3fes::EEContext&);
void fn_sub_55BB30_0055bb30(p3fes::EEContext&);
void fn_sub_55BD70_0055bd70(p3fes::EEContext&);
void fn_sub_55BDA8_0055bda8(p3fes::EEContext&);
void fn_sub_55BDC8_0055bdc8(p3fes::EEContext&);
void fn_sub_55BF40_0055bf40(p3fes::EEContext&);
void fn_sub_55C240_0055c240(p3fes::EEContext&);
void fn_sub_55C610_0055c610(p3fes::EEContext&);
void fn_sub_55C830_0055c830(p3fes::EEContext&);
void fn_sub_55C9D0_0055c9d0(p3fes::EEContext&);
void fn_sub_55CB30_0055cb30(p3fes::EEContext&);
void fn_sub_55CCE8_0055cce8(p3fes::EEContext&);
void fn_sub_55CEE0_0055cee0(p3fes::EEContext&);
void fn_sub_55CF08_0055cf08(p3fes::EEContext&);
void fn_sub_55CF58_0055cf58(p3fes::EEContext&);
void fn_sub_55D0B0_0055d0b0(p3fes::EEContext&);
void fn_sub_55D0D8_0055d0d8(p3fes::EEContext&);
void fn_sub_55D108_0055d108(p3fes::EEContext&);
void fn_sub_55D198_0055d198(p3fes::EEContext&);
void fn_sub_55D6F0_0055d6f0(p3fes::EEContext&);
void fn_sub_55DAE0_0055dae0(p3fes::EEContext&);
void fn_sub_55DBE8_0055dbe8(p3fes::EEContext&);
void fn_sub_55E190_0055e190(p3fes::EEContext&);
void fn_sub_55E1A8_0055e1a8(p3fes::EEContext&);
void fn_sub_55E1D8_0055e1d8(p3fes::EEContext&);
void fn_sub_55E220_0055e220(p3fes::EEContext&);
void fn_sub_55E3B0_0055e3b0(p3fes::EEContext&);
void fn_sub_55E408_0055e408(p3fes::EEContext&);
void fn_sub_55E428_0055e428(p3fes::EEContext&);
void fn_sub_55E498_0055e498(p3fes::EEContext&);
void fn_sub_55E538_0055e538(p3fes::EEContext&);
void fn_sub_55E580_0055e580(p3fes::EEContext&);
void fn_sub_55E640_0055e640(p3fes::EEContext&);
void fn_sub_55E678_0055e678(p3fes::EEContext&);
void fn_sub_55E800_0055e800(p3fes::EEContext&);
void fn_sub_55E850_0055e850(p3fes::EEContext&);
void fn_sub_55E888_0055e888(p3fes::EEContext&);
void fn_sub_55E8C0_0055e8c0(p3fes::EEContext&);
void fn_sub_55EA80_0055ea80(p3fes::EEContext&);
void fn_sub_55EA98_0055ea98(p3fes::EEContext&);
void fn_sub_55EFC8_0055efc8(p3fes::EEContext&);
void fn_sub_55F028_0055f028(p3fes::EEContext&);
void fn_sub_55F1C8_0055f1c8(p3fes::EEContext&);
void fn_sub_55F640_0055f640(p3fes::EEContext&);
void fn_sub_560DE8_00560de8(p3fes::EEContext&);
void fn_sub_560E30_00560e30(p3fes::EEContext&);
void fn_sub_5613E0_005613e0(p3fes::EEContext&);
void fn_sub_561518_00561518(p3fes::EEContext&);
void fn_sub_561560_00561560(p3fes::EEContext&);
void fn_sub_5615F8_005615f8(p3fes::EEContext&);
void fn_sub_561708_00561708(p3fes::EEContext&);
void fn_sub_561718_00561718(p3fes::EEContext&);
void fn_sub_563DD0_00563dd0(p3fes::EEContext&);
void fn_sub_563F38_00563f38(p3fes::EEContext&);
void fn_sub_563F90_00563f90(p3fes::EEContext&);
void fn_sub_564068_00564068(p3fes::EEContext&);
void fn_sub_5640D8_005640d8(p3fes::EEContext&);
void fn_sub_564108_00564108(p3fes::EEContext&);
void fn_sub_564178_00564178(p3fes::EEContext&);
void fn_sub_5641C8_005641c8(p3fes::EEContext&);
void fn_sub_564268_00564268(p3fes::EEContext&);
void fn_valloc_0_0054d5f8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0054AA48 sub_54AA48 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AA80(handle), the decoded sample count of the
// handle's decoder (null: E02080818, -1); returns it. [proposed ADXT_GetDecNumSmpl]
void sub_54AA48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aa48
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54AA54u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54AA5Cu, gen::fn_sub_54AA80_0054aa80);
    s0 = v0;
    jal(ctx, 0x54AA64u, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054AAB8 sub_54AAB8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AAF0(handle), the decoded input bytes of the
// handle's decoder (null: E04041901, -1); returns it. [proposed ADXT_GetDecDtLen]
void sub_54AAB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aab8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54AAC4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54AACCu, gen::fn_sub_54AAF0_0054aaf0);
    s0 = v0;
    jal(ctx, 0x54AAD4u, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054AB28 sub_54AB28 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AB78(handle, $a1, $a2): sub_542F70 on the
// handle's decoder (null: E04041902). The unlock is a tail call.
void sub_54AB28(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054ab28
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x54AB44u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x54AB54u, gen::fn_sub_54AB78_0054ab78);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054AE80 sub_54AE80 -- 184 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18
// Stores $a0 in the global word 0x787560, then for each of the 16 ADXT handles (200 bytes at 0x787570) in use (byte +0
// == 1) re-applies every channel's pan (sub_5491B0(h, ch, sub_549310(h, ch)) for ch < +3 channels) and the output
// volume (sub_549390(h, sub_549450(h))): a global output mode that takes effect on the playing handles. [proposed
// ADXT_SetOutputMono]
void sub_54AE80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054ae80
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x780000;
    v1 = 0x780000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    sw(a0, v0, 30048);  // 0x787560
    sd(s1, sp, 0x8);
    s1 = addiu(v1, 30064);  // &0x787570
    sd(s2, sp, 0x10);
    s2 = 15;
    sd(s3, sp, 0x18);
    s3 = 1;
    for (;;) {
        // 0x0054aeb0
        charge(ctx, 3);
        lb(v0, s1, 0);
        if (v0 != s3) {
            s2 = addiu(s2, -1);
        } else {
            // 0x0054aebc
            charge(ctx, 3);
            lb(v0, s1, 3);
            s0 = 0;
            if (i64(v0) > 0) {
                // 0x0054aec8
                charge(ctx, 2);
                a1 = s0;
                for (;;) {
                    // 0x0054aed0
                    charge(ctx, 11);
                    a0 = s1;
                    jal(ctx, 0x54AED0u, gen::fn_sub_549310_00549310);
                    a0 = s1;
                    a1 = s0;
                    s0 = addiu(s0, 1);
                    a2 = v0;
                    jal(ctx, 0x54AEE4u, gen::fn_sub_5491B0_005491b0);
                    lb(v0, s1, 3);
                    v0 = slt(s0, v0);
                    a1 = s0;
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0054aefc
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x54AEFCu, gen::fn_sub_549450_00549450);
            a0 = s1;
            a1 = v0;
            jal(ctx, 0x54AF08u, gen::fn_sub_549390_00549390);
            s2 = addiu(s2, -1);
        }
        // 0x0054af14
        charge(ctx, 2);
        s1 = addiu(s1, 200);
        if (i64(s2) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054af1c
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0054AFA8 sub_54AFA8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AFD8(handle), a tail call of sub_542FC0. The
// unlock is a tail call.
void sub_54AFA8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054afa8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54AFB4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54AFBCu, gen::fn_sub_54AFD8_0054afd8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054AFF0 sub_54AFF0 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B028(handle), the handle's output object (+12);
// returns it.
void sub_54AFF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aff0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54AFFCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54B004u, gen::fn_sub_54B028_0054b028);
    s0 = v0;
    jal(ctx, 0x54B00Cu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054B030 sub_54B030 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B070(handle, $a1): sub_543020 on the handle's
// decoder (+4). The unlock is a tail call.
void sub_54B030(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b030
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54B044u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54B050u, gen::fn_sub_54B070_0054b070);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054B1D0 sub_54B1D0 -- 92 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B230(handle, fname, $a2, $a3),
// adxt_StartFnameRange: copy the name, request the open. The unlock is a tail call. [proposed ADXT_StartFnameRange]
void sub_54B1D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b1d0
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
    jal(ctx, 0x54B1F4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x54B208u, gen::fn_sub_54B230_0054b230);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054B348 sceInsockAbortGethostbyaddr_2 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B388(handle, $a1): sub_54B3F0(handle, $a1,
// 0x40000000). The unlock is a tail call. (A FLIRT name.)
void sceInsockAbortGethostbyaddr_2(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b348
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54B35Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54B368u, gen::fn_sub_54B388_0054b388);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054C0E8 set_new_handler__FPFv_v -- 20 bytes; leaf frame (no stack)
// set_new_handler: stores the new handler in 0x793B68 and returns the previous one.
void set_new_handler__FPFv_v(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0054c0e8
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, 15208);  // &0x793B68
    lw(v0, v1, 0);  // 0x793B68
    sw(a0, v1, 0);  // 0x793B68
}

// 0x0054C670 sub_54C670 -- 588 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The ADXT error check of one handle, run by the server. While playing (stat +1 == 3, not paused +114, decoder not
// ended): the same decoded sample count (+100) for more than 5 x (+56) calls sets the error code (+96) to -2 (a stuck
// decoder); while preparing or playing (stat 1..3), input under 64 bytes (the input joint +20, its +36 entry with lane
// 1) for more than 5 x (+56) calls (20 x when not yet playing) sets -1 (a starved input). Counters reset when their
// condition breaks. With an error code the recovery mode (+109) acts: after the stall check mode 1 or 2 stops the
// handle (sub_548678); after the input check mode 1 stops it and mode 2 restarts it from its input (sub_54C580); when
// the mode is set the error code and that counter are then cleared. A streamer (+8) in state 4 (error) runs the
// input-check recovery. [proposed adxt_ExecErrChk]
void sub_54C670(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054c670
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 3;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lb(s1, s0, l20::adxt::kStat);
    if (s1 != v0) {
        sh(zero, s0, l20::adxt::kStallCnt);
    } else {
        // 0x0054c694
        charge(ctx, 3);
        lb(v0, s0, l20::adxt::kPause);
        if (v0 != 0) {
            sh(zero, s0, l20::adxt::kStallCnt);
            goto L_0054c734;
        }
        // 0x0054c6a0
        charge(ctx, 4);
        link(ctx, 0x54C6A0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, l20::adxt::kSjd);
        call(ctx, gen::fn_sub_542008_00542008);
        if (v0 == s1) {
            sh(zero, s0, l20::adxt::kStallCnt);
            goto L_0054c734;
        }
        // 0x0054c6b0
        charge(ctx, 6);
        link(ctx, 0x54C6B0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, l20::adxt::kSjd);
        call(ctx, gen::fn_sub_542F68_00542f68);
        a2 = v0;
        lw(v0, s0, l20::adxt::kLastSmpl);
        if (v0 != a2) {
            sh(zero, s0, l20::adxt::kStallCnt);
        } else {
            // 0x0054c6c8
            charge(ctx, 10);
            lhu(a0, s0, l20::adxt::kStallCnt);
            lw(a1, s0, l20::adxt::kChkUnit);
            a0 = addiu(a0, 1);
            v1 = sll(a0, 16);
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v1 = sra(v1, 16);
            v0 = slt(v0, v1);
            sh(a0, s0, l20::adxt::kStallCnt);
            if (v0 != 0) {
                // 0x0054c6f0
                charge(ctx, 2);
                v0 = si(-2);
                sh(v0, s0, l20::adxt::kErrCode);
            }
        }
        // 0x0054c6f8
        charge(ctx, 3);
        lh(v0, s0, l20::adxt::kErrCode);
        sw(a2, s0, l20::adxt::kLastSmpl);
        if (v0 == 0) {
            goto L_0054c734;
        }
        // 0x0054c704
        charge(ctx, 5);
        lbu(v1, s0, l20::adxt::kRecover);
        v0 = addiu(v1, -1);
        v0 = sltiu(v0, 2);
        if (v0 != 0) {
            // 0x0054c718
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x54C718u, gen::fn_sub_548678_00548678);
            lbu(v1, s0, l20::adxt::kRecover);
        }
        // 0x0054c724
        charge(ctx, 2);
        v0 = addiu(s1, -1);
        if (v1 != 0) {
            // 0x0054c72c
            charge(ctx, 2);
            sh(zero, s0, l20::adxt::kErrCode);
            sh(zero, s0, l20::adxt::kStallCnt);
            goto L_0054c734;
        }
        goto L_0054c738;
    }
L_0054c734:
    charge(ctx, 1);
    v0 = addiu(s1, -1);
L_0054c738:
    charge(ctx, 3);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        sh(zero, s0, l20::adxt::kStarveCnt);
    } else {
        // 0x0054c744
        charge(ctx, 3);
        lb(v0, s0, l20::adxt::kPause);
        if (v0 != 0) {
            sh(zero, s0, l20::adxt::kStarveCnt);
            goto L_0054c840;
        }
        // 0x0054c750
        charge(ctx, 5);
        link(ctx, 0x54C750u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, l20::adxt::kSjd);
        call(ctx, gen::fn_sub_542008_00542008);
        v1 = 3;
        if (v0 == v1) {
            sh(zero, s0, l20::adxt::kStarveCnt);
            goto L_0054c840;
        }
        // 0x0054c764
        charge(ctx, 3);
        lw(a0, s0, l20::adxt::kSji);
        v0 = 0;
        if (a0 == 0) {
            // 0x0054c788
            charge(ctx, 1);
            v0 = slti(v0, 64);
        } else {
            // 0x0054c770
            charge(ctx, 6);
            lw(v1, a0, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x54C778u, v0.u());
            v0 = slti(v0, 64);
        }
        // 0x0054c78c
        charge(ctx, 2);
        if (v0 == 0) {
            sh(zero, s0, l20::adxt::kStarveCnt);
            goto L_0054c840;
        }
        // 0x0054c794
        charge(ctx, 5);
        lhu(v0, s0, l20::adxt::kStarveCnt);
        v1 = 3;
        v0 = addiu(v0, 1);
        sh(v0, s0, l20::adxt::kStarveCnt);
        if (s1 != v1) {
            // 0x0054c7c0
            charge(ctx, 6);
            lw(a0, s0, l20::adxt::kChkUnit);
            v1 = sll(v0, 16);
            v1 = sra(v1, 16);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
        } else {
            // 0x0054c7a8
            charge(ctx, 6);
            lw(a0, s0, l20::adxt::kChkUnit);
            v1 = sll(v0, 16);
            v1 = sra(v1, 16);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
        }
        // 0x0054c7d8
        charge(ctx, 3);
        v0 = slt(v0, v1);
        if (v0 == 0) {
            lh(v0, s0, l20::adxt::kErrCode);
        } else {
            // 0x0054c7e4
            charge(ctx, 3);
            v0 = si(-1);
            sh(v0, s0, l20::adxt::kErrCode);
            lh(v0, s0, l20::adxt::kErrCode);
        }
        // 0x0054c7f0
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            goto L_0054c840;
        }
        // 0x0054c7f8
        charge(ctx, 3);
        lb(a0, s0, l20::adxt::kRecover);
        lbu(v1, s0, l20::adxt::kRecover);
        if (a0 != v0) {
            // 0x0054c818
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                // 0x0054c824
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x54C824u, gen::fn_sub_54C580_0054c580);
                lbu(v1, s0, l20::adxt::kRecover);
            }
        } else {
            // 0x0054c804
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x54C804u, gen::fn_sub_548678_00548678);
            lbu(v1, s0, l20::adxt::kRecover);
        }
        // 0x0054c830
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x0054c838
            charge(ctx, 2);
            sh(zero, s0, l20::adxt::kErrCode);
            sh(zero, s0, l20::adxt::kStarveCnt);
            goto L_0054c840;
        }
        lw(a0, s0, l20::adxt::kStm);
        goto L_0054c844;
    }
L_0054c840:
    charge(ctx, 1);
    lw(a0, s0, l20::adxt::kStm);
L_0054c844:
    charge(ctx, 2);
    if (a0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0054c84c
        charge(ctx, 5);
        jal(ctx, 0x54C84Cu, gen::fn_sub_546368_00546368);
        v1 = 4;
        if (v0 != v1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0054c860
            charge(ctx, 4);
            lb(a0, s0, l20::adxt::kRecover);
            v0 = 1;
            lbu(v1, s0, l20::adxt::kRecover);
            if (a0 != v0) {
                // 0x0054c880
                charge(ctx, 3);
                v0 = 2;
                if (a0 == v0) {
                    // 0x0054c88c
                    charge(ctx, 3);
                    a0 = s0;
                    jal(ctx, 0x54C88Cu, gen::fn_sub_54C580_0054c580);
                    lbu(v1, s0, l20::adxt::kRecover);
                }
            } else {
                // 0x0054c870
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x54C870u, gen::fn_sub_548678_00548678);
                lbu(v1, s0, l20::adxt::kRecover);
            }
            // 0x0054c898
            charge(ctx, 2);
            if (v1 == 0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x0054c8a0
                charge(ctx, 3);
                sh(zero, s0, l20::adxt::kStarveCnt);
                sh(zero, s0, l20::adxt::kErrCode);
                ld(s0, sp, 0x0);
            }
        }
    }
    // 0x0054c8ac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054CAD0 sub_54CAD0 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54CB08(handle): the handle's streamer (+8, else the
// play list's) passed to sub_547558; returns it.
void sub_54CAD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cad0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54CADCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54CAE4u, gen::fn_sub_54CB08_0054cb08);
    s0 = v0;
    jal(ctx, 0x54CAECu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054D010 sub_54D010 -- 28 bytes; frame 0x10: ra sp+0x0
// ACSSVR_Finish on the sound server (*0x793F44), a tail call.
void sub_54D010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d010
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    lw(a0, v0, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_534B60_00534b60(ctx);  // tail call
}

// 0x0054D560 sub_54D560 -- 40 bytes; frame 0x10: ra sp+0x0
// The ducking lowering frames of the server's ducking object: ACSVHL_GetDownTime(ACSSVR_GetVhl(*0x793F44)), a tail
// call.
void sub_54D560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d560
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x0);
    jal(ctx, 0x54D570u, gen::fn_sub_535170_00535170);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_sub_535388_00535388(ctx);  // tail call
}

// 0x0054D588 sub_54D588 -- 40 bytes; frame 0x10: ra sp+0x0
// The ducking restoring frames: ACSVHL_GetUpTime(ACSSVR_GetVhl(*0x793F44)), a tail call.
void sub_54D588(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d588
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x0);
    jal(ctx, 0x54D598u, gen::fn_sub_535170_00535170);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_sub_535390_00535390(ctx);  // tail call
}

// 0x0054D5B0 sqrtl_5 -- 40 bytes; frame 0x10: ra sp+0x0
// The ducking depth (dB x 10): ACSVHL_GetDepth(ACSSVR_GetVhl(*0x793F44)), a tail call. (A FLIRT name.)
void sqrtl_5(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d5b0
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(a0, v0, 16196);  // 0x793F44
    sd(ra, sp, 0x0);
    jal(ctx, 0x54D5C0u, gen::fn_sub_535170_00535170);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00535398(ctx);  // tail call
}

// 0x0054D5D8 sub_54D5D8 -- 28 bytes; frame 0x10: ra sp+0x0
// One server frame: ACSSVR_ExecServer(*0x793F44), a tail call. (sub_535050)
void sub_54D5D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d5d8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    lw(a0, v0, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_535050_00535050(ctx);  // tail call
}

// 0x0054D5F8 valloc_0 -- 32 bytes; frame 0x10: ra sp+0x0
// One sound's frame: acssvr_ExecSnd(*0x793F44, $a0), a tail call. (sub_5350D0; a FLIRT name.)
void valloc_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d5f8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(a0, v0, 16196);  // 0x793F44
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5350D0_005350d0(ctx);  // tail call
}

// 0x0054D618 pvalloc_0 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The AHX init counter 0x796F50 (beside the bit reader's call count 0x796F54 and mask table 0x796F58): the first call
// clears the 704-byte work 0x796FE0; returns the new count. (A FLIRT name.)
void pvalloc_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d618
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 28496);  // &0x796F50
    lw(v0, s0, 0);  // 0x796F50
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x0054d634
        charge(ctx, 6);
        a0 = 0x790000;
        a1 = 0;
        a0 = addiu(a0, 28640);  // &0x796FE0
        a2 = 704;
        jal(ctx, 0x54D640u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x0054d64c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054D668 sub_54D668 -- 76 bytes; frame 0x10: ra sp+0x0
// The matching AHX finish: decrements 0x796F50 and clears the 704-byte work 0x796FE0 when it reaches 0.
void sub_54D668(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054d668
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 28496);  // &0x796F50
    lw(v0, v1, 0);  // 0x796F50
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x796F50
    if (v0 != 0) {
        // 0x0054d6a8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054d688
    charge(ctx, 7);
    a0 = 0x790000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 28640);  // &0x796FE0
    a2 = 704;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0054D818 sub_54D818 -- 116 bytes; leaf frame (no stack)
// A mask of the $a0 low bits: $a0 / 8 bytes of 0xFF shifted in, then $a0 % 8 single bits (signed division by 8); passed
// as $a1 to sub_54D88C, which returns it (a tail call).
void sub_54D818(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0054d818
    enter(ctx, 7);  // entry check point + this block's cycles
    a2 = addiu(a0, 7);
    v1 = slti(a0, 0);
    v0 = a0;
    if (v1 != 0) v0 = a2;
    v0 = sra(v0, 3);
    a1 = 0;
    if (i64(v0) > 0) {
        // 0x0054d834
        charge(ctx, 1);
        for (;;) {
            // 0x0054d838
            charge(ctx, 7);
            a1 = sll(a1, 8);
            v0 = addiu(v0, -1);
            a1 = a1 | 0xFF;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054d854
    charge(ctx, 7);
    v0 = a0;
    if (v1 != 0) v0 = a2;
    v0 = sra(v0, 3);
    v1 = sll(v0, 3);
    v0 = subu(a0, v1);
    if (i64(v0) <= 0) {
        gen::fn_sub_54D88C_0054d88c(ctx);  // tail call
        return;
    }
    for (;;) {
        // 0x0054d870
        charge(ctx, 7);
        a1 = sll(a1, 1);
        v0 = addiu(v0, -1);
        a1 = a1 | 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054d88c
    gen::fn_sub_54D88C_0054d88c(ctx);  // tail call
}

// 0x0054DC48 sub_54DC48 -- 188 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// AHX sync search on the bit reader $a0: mask = 0x796F58[$a2] ($a2 bits); skips to the byte boundary (the bits
// consumed, sub_54DBE8, & 7; sub_54DB38 takes the rest), takes $a2 bits, then while (bits & mask) != $a1 and the reader
// has data (sub_54DBF0) shifts in 8 more bits. Returns 1 when found (data left), else 0.
void sub_54DC48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054dc48
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a2;
    v0 = sll(s0, 2);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s1 = a0;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s2 = 0x790000;
    s2 = addu(s2, v0);
    lw(s2, s2, 28504);
    s3 = a1;
    jal(ctx, 0x54DC78u, gen::fn_sub_54DBE8_0054dbe8);
    v0 = v0 & 0x7;
    a1 = 8;
    if (v0 != 0) {
        // 0x0054dc8c
        charge(ctx, 3);
        a0 = s1;
        a1 = subu(a1, v0);
        jal(ctx, 0x54DC90u, gen::fn_sub_54DB38_0054db38);
    }
    // 0x0054dc98
    charge(ctx, 5);
    a1 = s0;
    a0 = s1;
    jal(ctx, 0x54DC9Cu, gen::fn_sub_54DB38_0054db38);
    s0 = v0;
    for (;;) {
        // 0x0054dcbc
        charge(ctx, 3);
        v0 = s0 & s2;
        s0 = sll(s0, 8);
        if (v0 != s3) {
            // 0x0054dcc8
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x54DCC8u, gen::fn_sub_54DBF0_0054dbf0);
            a0 = s1;
            a1 = 8;
            if (v0 == 0) {
                backedge(ctx);
                // 0x0054dcb0
                charge(ctx, 3);
                jal(ctx, 0x54DCB0u, gen::fn_sub_54DB38_0054db38);
                s0 = s0 | v0;
                continue;
            }
        }
        break;
    }
    // 0x0054dcdc
    charge(ctx, 10);
    a0 = s1;
    jal(ctx, 0x54DCDCu, gen::fn_sub_54DBF0_0054dbf0);
    ld(s0, sp, 0x0);
    v0 = sltiu(v0, 1);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0054DDF8 sub_54DDF8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a stub).
void sub_54DDF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0054ddf8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0054DE18 sub_54DE18 -- 52 bytes; frame 0x10: ra sp+0x0
// Calls the registered callback *0x7973A4 (when set) with its object *0x7973A8 and $a0 (jalr); returns 0.
void sub_54DE18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0054de18
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 29604);  // 0x7973A4
    a1 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0054de30
        charge(ctx, 3);
        v0 = 0x790000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x54DE34u);  // $ra = the return address
        lw(a0, v0, 29608);
        call_ptr(ctx, jt);
    }
    // 0x0054de3c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0054E810 sub_54E810 -- 40 bytes; frame 0x10: ra sp+0x0
// Calls the return stub at 0x54E808 (the tail of sub_54E7D8) and returns its $v0 x 12.
void sub_54E810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e810
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x54E818u);
    gen::fn_sub_54E7D8_0054e7d8_at_0054e808(ctx);
    v1 = sll(v0, 1);
    ld(ra, sp, 0x0);
    v1 = addu(v1, v0);
    v0 = sll(v1, 2);
    sp = addiu(sp, 0x10);
}

// 0x00554998 sub_554998 -- 48 bytes; leaf frame (no stack)
// Reads track $a1's two words of the AIX info $a0 (16-byte records: +700 and +704) into *$a2 / *$a3 (each when not
// null).
void sub_554998(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00554998
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = sll(a1, 4);
    v1 = addu(v0, a0);
    a1 = v1;
    if (a2 != 0) {
        // 0x005549a8
        charge(ctx, 2);
        lw(v0, a1, 700);
        sw(v0, a2, 0);
    }
    // 0x005549b0
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x005549b8
        charge(ctx, 2);
        lw(v0, v1, 704);
        sw(v0, a3, 0);
    }
    // 0x005549c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00554A00 sub_554A00 -- 92 bytes; leaf frame (no stack)
// Reads segment $a1's four u16 of the AIX info $a0 (8-byte records at +6456: +0, +2, +4, +6) into *$a2, *$a3, *$a4,
// *$a5 (each when not null).
void sub_554A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x00554a00
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    t2 = a2;
    t3 = addu(v0, a0);
    a2 = t3;
    v1 = a2;
    a1 = v1;
    if (t2 != 0) {
        // 0x00554a1c
        charge(ctx, 2);
        lhu(v0, a2, 6456);
        sw(v0, t2, 0);
    }
    // 0x00554a24
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x00554a2c
        charge(ctx, 2);
        lhu(v0, v1, 6458);
        sw(v0, a3, 0);
    }
    // 0x00554a34
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x00554a3c
        charge(ctx, 2);
        lhu(v0, a1, 6460);
        sw(v0, t0, 0);
    }
    // 0x00554a44
    charge(ctx, 2);
    if (t1 != 0) {
        // 0x00554a4c
        charge(ctx, 2);
        lhu(v0, t3, 6462);
        sw(v0, t1, 0);
    }
    // 0x00554a54 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00554AA0 sub_554AA0 -- 72 bytes; frame 0x10: ra sp+0x0
// Checks the arguments of the AIX header parse (buffer, size > 0, out): a bad one reports "E2003080101 : Illegal
// parameter is specified." (sub_552630) and returns -1; else sub_554AE8 (tail call) parses the header.
void sub_554AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554aa0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    v1 = a2;
    if (a0 != 0) {
        // 0x00554ab4
        charge(ctx, 2);
        if (i64(v0) <= 0) {
            a0 = 0x7C0000;
        L_00554ac8:
            charge(ctx, 6);
            a0 = addiu(a0, 14384);
            jal(ctx, 0x554AC8u, gen::fn_sub_552630_00552630);
            v0 = si(-1);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x00554abc
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (v1 == 0) {
            goto L_00554ac4;
        }
        // 0x00554ae0
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        gen::fn_sub_554AE8_00554ae8(ctx);  // tail call
        return;
    }
L_00554ac4:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_00554ac8;
}

// 0x005556A0 sub_5556A0 -- 128 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI CFG init: points 0x997408 at the version text "CRI CFG/PS2EE Ver.1.002 ...", clears the 256 bytes at 0x997418 and
// makes them a table of 16-byte entries (base 0x99740C = the word-aligned 0x99741B, count 0x997410 = 16).
void sub_5556A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005556a0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x990000;
    v0 = 0x7C0000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 29704);  // &0x997408
    v0 = addiu(v0, 14600);  // "\nCRI CFG/PS2EE Ver.1.002 Build:Feb 28 2005 19:25:35\n"
    s0 = 0x990000;
    sd(ra, sp, 0x8);
    s0 = addiu(s0, 29720);  // &0x997418
    sw(v0, v1, 0);  // 0x997408
    a0 = s0;
    a1 = 0;
    a2 = 256;
    jal(ctx, 0x5556D0u, gen::fn_memset_00521408);
    a3 = 0x990000;
    a0 = addiu(s0, 3);  // &0x99741B
    v1 = si(-4);
    a0 = a0 & v1;
    v0 = 256;
    s0 = subu(a0, s0);
    ld(ra, sp, 0x8);
    v0 = subu(v0, s0);
    ld(s0, sp, 0x0);
    a1 = addiu(v0, 15);
    v1 = slti(v0, 0);
    if (v1 != 0) v0 = a1;
    a2 = 0x990000;
    v0 = sra(v0, 4);
    sw(a0, a3, 29708);  // 0x99740C
    sw(v0, a2, 29712);  // 0x997410
    sp = addiu(sp, 0x10);
}

// 0x00555720 sub_555720 -- 20 bytes; leaf frame (no stack)
// CRI CFG finish: clears the entry table base (0x99740C) and count (0x997410).
void sub_555720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3};
    // 0x00555720
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x990000;
    v1 = 0x990000;
    sw(zero, v0, 29708);  // 0x99740C
    sw(zero, v1, 29712);  // 0x997410
}

// 0x00555820 sub_555820 -- 116 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// CRI CFG: adds an entry {name (12 chars, strncpy), $a1}: 0 when stored, -1 when CFG is not initialised (base 0), -2
// when the table is full (sub_555738 finds no free entry).
void sub_555820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555820
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x990000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 29708);  // 0x99740C
    v0 = si(-1);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    if (v1 != 0) {
        // 0x0055584c
        charge(ctx, 8);
        jal(ctx, 0x55584Cu, gen::fn_sub_555738_00555738);
        a2 = 12;
        s0 = v0;
        v0 = si(-2);
        a1 = s1;
        a0 = s0;
        if (s0 != 0) {
            // 0x0055586c
            charge(ctx, 4);
            jal(ctx, 0x55586Cu, gen::fn_strncpy_00524828);
            v0 = 0;
            sw(s2, s0, 12);
        }
    }
    // 0x0055587c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00555A08 sub_555A08 -- 260 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// CVFS finish: decrements the init count 0x7A08AC; at 0, for each of the 40 open-handle records {device interface,
// device handle} at 0x997518 calls the interface's +20 entry with the handle (jalr) when set and clears the record,
// clears the first byte of 32 16-byte device records (0x99765C..0x99784C), then the 9 bytes at 0x997858. [proposed
// cvFsFinish]
void sub_555A08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00555a08
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 0x7A0000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 2220);  // &0x7A08AC
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    lw(v0, v1, 0);  // 0x7A08AC
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7A08AC
    if (v0 == 0) {
        // 0x00555a40
        charge(ctx, 6);
        v0 = 0x990000;
        s1 = 0;
        s4 = addiu(v0, 29976);  // &cvFsHandleTable
        s5 = addiu(s4, 4);  // &0x99751C
        s2 = s4;
        for (;;) {
            // 0x00555a58
            charge(ctx, 4);
            lw(v0, s2, 0);
            s3 = sll(s1, 3);
            s1 = addiu(s1, 1);
            if (v0 == 0) {
                // 0x00555a80
                charge(ctx, 2);
                s0 = addiu(s4, 4);
                v0 = addu(s3, s0);
            } else {
                // 0x00555a68
                charge(ctx, 6);
                lw(v0, v0, 20);
                s0 = s5;
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x555A70u);  // $ra = the return address
                lw(a0, s2, 4);
                call_ptr(ctx, jt);
                v0 = addu(s3, s0);
            }
            // 0x00555a88
            charge(ctx, 5);
            v1 = slti(s1, 40);
            sw(zero, s2, 0);
            s2 = addiu(s2, 8);
            sw(zero, v0, 0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00555a9c
        charge(ctx, 5);
        v0 = 0x990000;
        s1 = 31;
        v0 = addiu(v0, 30296);  // &0x997658
        v0 = addiu(v0, 500);  // &0x99784C
        for (;;) {
            // 0x00555ab0
            charge(ctx, 7);
            s1 = addiu(s1, -1);
            sb(zero, v0, 0);
            v0 = addiu(v0, -16);
            if (i64(s1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00555acc
        charge(ctx, 7);
        s0 = 0x990000;
        a1 = 0;
        s0 = addiu(s0, 30808);  // &0x997858
        a2 = 9;
        a0 = s0;
        jal(ctx, 0x555ADCu, gen::fn_memset_00521408);
        sb(zero, s0, 0);  // 0x997858
    }
    // 0x00555ae8 (the shared epilogue, written out on this path)
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

// 0x00557F60 sub_557F60 -- 28 bytes; frame 0x10: ra sp+0x0
// SRD_WaitComplete(&srd_obj 0x7A08B0), a tail call.
void sub_557F60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557f60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7A0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 2224);  // &srd_obj
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_SRD_WaitComplete_00557e50(ctx);  // tail call
}

// 0x005580F8 sub_5580F8 -- 12 bytes; leaf frame (no stack)
// SRD: stores the byte 0x7A092C = $a0.
void sub_5580F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005580f8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sb(a0, v0, 2348);  // 0x7A092C
}

// 0x00558108 sub_558108 -- 12 bytes; leaf frame (no stack)
// SRD: stores the word 0x7A0928 = $a0.
void sub_558108(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00558108
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sw(a0, v0, 2344);  // 0x7A0928
}

// 0x00558118 sub_558118 -- 12 bytes; leaf frame (no stack)
// SRD: the byte 0x7A092C (sub_5580F8's).
void sub_558118(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558118
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lbu(v0, v1, 2348);  // 0x7A092C
}

// 0x00558128 __errno_3 -- 12 bytes; leaf frame (no stack)
// SRD: the word 0x7A0928 (sub_558108's). (A FLIRT name.)
void __errno_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558128
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 2344);  // 0x7A0928
}

// 0x005585F0 sub_5585F0 -- 12 bytes; leaf frame (no stack)
// SRD: srd_obj's device type byte (0x7A08B1: 1 DVD, 2 host).
void sub_5585F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005585f0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lb(v0, v1, 2225);  // 0x7A08B1
}

// 0x00558600 __errno_5 -- 12 bytes; leaf frame (no stack)
// SRD: the word 0x7A08E4. (A FLIRT name.)
void __errno_5(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558600
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 2276);  // 0x7A08E4
}

// 0x00558678 sub_558678 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08F0; returns its address.
void sub_558678(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558678
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x558684u, gen::fn_sub_558610_00558610);
    s0 = sll(s0, 24);
    v0 = 0x7A0000;
    v0 = addiu(v0, 2288);  // &0x7A08F0
    s0 = sra(s0, 24);
    sw(s0, v0, 0);  // 0x7A08F0
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005586B0 sub_5586B0 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08F4; returns its address.
void sub_5586B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005586b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5586BCu, gen::fn_sub_558610_00558610);
    s0 = sll(s0, 24);
    v0 = 0x7A0000;
    v0 = addiu(v0, 2292);  // &0x7A08F4
    s0 = sra(s0, 24);
    sw(s0, v0, 0);  // 0x7A08F4
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005586E8 sub_5586E8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08F8; returns its address.
void sub_5586E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005586e8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5586F4u, gen::fn_sub_558610_00558610);
    s0 = sll(s0, 24);
    v0 = 0x7A0000;
    v0 = addiu(v0, 2296);  // &0x7A08F8
    s0 = sra(s0, 24);
    sw(s0, v0, 0);  // 0x7A08F8
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00558720 sub_558720 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08FC; returns its address.
void sub_558720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558720
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55872Cu, gen::fn_sub_558610_00558610);
    s0 = sll(s0, 24);
    v0 = 0x7A0000;
    v0 = addiu(v0, 2300);  // &0x7A08FC
    s0 = sra(s0, 24);
    sw(s0, v0, 0);  // 0x7A08FC
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00558758 sub_558758 -- 16 bytes; leaf frame (no stack)
// SRD: srd_obj.stat (0x7A08B2) = 9; returns 9.
void sub_558758(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558758
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v0 = 9;
    sb(v0, v1, 2226);  // 0x7A08B2
}

// 0x00558898 sub_558898 -- 204 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SRD info dump (scePrintf): "SRD: SRD Info.", srd_enter_fg (0x7A08EC), srd_debug_geterror (0x7A0904), srd_obj.stat,
// the device type (DVD / HOST lines), the read status (sub_558848); returns 0.
void sub_558898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558898
    enter(ctx, 29);  // entry check point + this block's cycles
    a0 = 0x7C0000;
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    a0 = addiu(a0, 18392);  // "SRD: SRD Info.\n"
    jal(ctx, 0x5588A8u, gen::fn_scePrintf_00505e48);
    v0 = 0x7A0000;
    a0 = 0x7C0000;
    lw(a1, v0, 2284);  // 0x7A08EC
    a0 = addiu(a0, 18408);  // " srd_enter_fg       = %d\n"
    jal(ctx, 0x5588BCu, gen::fn_scePrintf_00505e48);
    a0 = 0x7C0000;
    v0 = 0x7A0000;
    a0 = addiu(a0, 18440);  // " srd_debug_geterror = %d\n"
    v0 = addiu(v0, 2308);  // &0x7A0904
    link(ctx, 0x5588D4u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 0);
    call(ctx, gen::fn_scePrintf_00505e48);
    a0 = 0x7C0000;
    v0 = 0x7A0000;
    a0 = addiu(a0, 18472);  // " srd_obj.stat       = %d\n"
    s0 = addiu(v0, 2224);  // &srd_obj
    link(ctx, 0x5588ECu);  // $ra first: the delay slot below depends on it
    lb(a1, s0, 2);  // 0x7A08B2
    call(ctx, gen::fn_scePrintf_00505e48);
    a0 = 0x7C0000;
    lb(v1, s0, 1);  // 0x7A08B1
    v0 = 1;
    a0 = addiu(a0, 18504);  // " srd_obj.devtype    = DVD\n"
    lbu(a1, s0, 1);  // 0x7A08B1
    if (v1 == v0) {
        // 0x0055890c
        charge(ctx, 3);
        jal(ctx, 0x55890Cu, gen::fn_scePrintf_00505e48);
        lbu(a1, s0, 1);
    }
    // 0x00558918
    charge(ctx, 5);
    v0 = sll(a1, 24);
    v1 = 2;
    v0 = sra(v0, 24);
    if (v0 == v1) {
        // 0x0055892c
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 18536);  // " srd_obj.devtype    = HOST\n"
        jal(ctx, 0x558930u, gen::fn_scePrintf_00505e48);
    }
    // 0x00558938
    charge(ctx, 11);
    jal(ctx, 0x558938u, gen::fn_sub_558848_00558848);
    a0 = 0x7C0000;
    a1 = v0;
    a0 = addiu(a0, 18568);  // " Read Status(DVD=2/HST=1) = %d\n"
    jal(ctx, 0x558948u, gen::fn_scePrintf_00505e48);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00558968 sub_558968 -- 16 bytes; leaf frame (no stack)
// SRD: the word 0x7A090C.
void sub_558968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558968
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v1 = addiu(v1, 2316);  // &0x7A090C
    lw(v0, v1, 0);  // 0x7A090C
}

// 0x00558978 sub_558978 -- 16 bytes; leaf frame (no stack)
// SRD: the word 0x7A0908.
void sub_558978(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558978
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v1 = addiu(v1, 2312);  // &0x7A0908
    lw(v0, v1, 0);  // 0x7A0908
}

// 0x005589A8 sub_5589A8 -- 16 bytes; leaf frame (no stack)
// SRD: the word 0x7A091C.
void sub_5589A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005589a8
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v1 = addiu(v1, 2332);  // &0x7A091C
    lw(v0, v1, 0);  // 0x7A091C
}

// 0x00559200 sub_559200 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Prints "DTR_Init: in (count)" (sub_541760), clears the 2048 bytes at 0x7A0938 on the first call, increments the init
// count 0x7A0934, prints "DTR_Init: out" (tail call). [named by its own text: DTR_Init]
void sub_559200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559200
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 2356);  // &0x7A0934
    sd(ra, sp, 0x8);
    a0 = 0x7C0000;
    a0 = addiu(a0, 19096);  // "DTR_Init: in (%d)\n"
    link(ctx, 0x55921Cu);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 0);  // 0x7A0934
    call(ctx, gen::fn_sub_541760_00541760);
    a0 = 0x7A0000;
    lw(v0, s0, 0);  // 0x7A0934
    a0 = addiu(a0, 2360);  // &0x7A0938
    a1 = 0;
    a2 = 2048;
    if (v0 == 0) {
        // 0x0055923c
        charge(ctx, 3);
        jal(ctx, 0x55923Cu, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x00559248
    charge(ctx, 8);
    v0 = addiu(v0, 1);
    a0 = 0x7C0000;
    sw(v0, s0, 0);
    a0 = addiu(a0, 19120);  // "DTR_Init: out\n"
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x005596D0 sub_5596D0 -- 44 bytes; leaf frame (no stack)
// DTX record $a0 of the 16 68-byte records at 0x7A1160 (unsigned $a0 < 16), else 0.
void sub_5596D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005596d0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = sll(a0, 4);
    a1 = sltiu(a0, 16);
    v0 = 0;
    v1 = addu(v1, a0);
    if (a1 != 0) {
        // 0x005596e4
        charge(ctx, 4);
        v0 = sll(v1, 2);
        at = 0x7A0000;
        at = addiu(at, 4448);  // &0x7A1160
        v0 = addu(at, v0);
    }
    // 0x005596f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00559700 sub_559700 -- 20 bytes; leaf frame (no stack)
// Clears a DTX record's send and receive callbacks: the words +32, +36 (send function, object), +40, +44 (receive
// function, object).
void sub_559700(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00559700
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, 44);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
}

// 0x00559E30 sub_559E30 -- 80 bytes; leaf frame (no stack)
// Whether any of the 40 DVD CI handles (72 bytes at 0x7A1DF0) is in use (byte +0 == 1) and transferring (status +2 ==
// 2): 1, else 0.
void sub_559E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00559e30
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    a1 = 0;
    a0 = addiu(v0, 7664);  // &0x7A1DF0
    a3 = 1;
    a2 = 2;
    for (;;) {
        // 0x00559e48
        charge(ctx, 3);
        lb(v0, a0, 0);
        if (v0 != a3) {
            a1 = addiu(a1, 1);
        } else {
            // 0x00559e54
            charge(ctx, 3);
            lb(v1, a0, 2);
            v0 = 1;
            if (v1 == a2) {
                break;
            }
            // 0x00559e60
            charge(ctx, 1);
            a1 = addiu(a1, 1);
            goto L_00559e64;
        }
    L_00559e64:
        charge(ctx, 4);
        v0 = slti(a1, 40);
        a0 = addiu(a0, 72);
        if (v0 == 0) {
            goto L_00559e74_5;
        }
        backedge(ctx);
    }
    // 0x00559e78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00559e74_5:
    charge(ctx, 1);
    v0 = 0;
    // 0x00559e78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0055B6D8 sceLibgcc32GetErxEntries_6 -- 12 bytes; leaf frame (no stack)
// The address of the 0x7A2A80 block. (A FLIRT name.)
void sceLibgcc32GetErxEntries_6(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055b6d8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v0 = addiu(v0, 10880);  // &dvg_ci_root_dir
}

// 0x0055B700 cosl_7 -- 20 bytes; frame 0x10: ra sp+0x0
// sub_5589B8($a0): the 64-bit host filesystem flag (a tail call). (A FLIRT name.)
void cosl_7(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b700
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5589B8_005589b8(ctx);  // tail call
}

// 0x0055B718 coshl_7 -- 20 bytes; frame 0x10: ra sp+0x0
// __errno_6 (0x5589F8), a tail call. (A FLIRT name.)
void coshl_7(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b718
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___errno_6_005589f8(ctx);  // tail call
}

// 0x0055B730 expl_7 -- 100 bytes, 3 chunks; frame 0x10: ra sp+0x0
// Stores the sign-extended byte $a0 in 0x7A08F4 and 0x7A0924 and prints "SRD: Enable HostLock" (scePrintf, a tail call)
// when $a0 == 1. Three chunks: an empty frame at 0x55B730, then the body at 0x558A08. (A FLIRT name.)
void expl_7(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b730
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00558a08
    charge(ctx, 12);
    v1 = 0x7A0000;
    v0 = sll(a0, 24);
    v1 = addiu(v1, 2292);  // &0x7A08F4
    v0 = sra(v0, 24);
    sp = addiu(sp, -0x10);
    a2 = 0x7A0000;
    sd(ra, sp, 0x0);
    a1 = 1;
    sw(v0, v1, 0);  // 0x7A08F4
    lw(v0, v1, 0);  // 0x7A08F4
    sw(v0, a2, 2340);  // 0x7A0924
    if (a0 != a1) {
        // 0x00558a50
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00558a38
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 18632);  // &0x7C48C8
    sp = addiu(sp, 0x10);
    gen::fn_scePrintf_00505e48(ctx);  // tail call
}

// 0x0055B748 hypotf_7 -- 20 bytes; frame 0x10: ra sp+0x0
// __errno_7 (0x558A60), a tail call. (A FLIRT name.)
void hypotf_7(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b748
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___errno_7_00558a60(ctx);  // tail call
}

// 0x0055B760 sub_55B760 -- 56 bytes; frame 0x10: ra sp+0x0
// Host CI setup: clears the root directory (sub_55D108(0)) and resets the device prefix (sub_55D198(0): "host:");
// returns the address of the function table 0x7A2C18 ($v1 keeps the word 0x7A2C08). [proposed htCiGetInterface]
void sub_55B760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b760
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 11272);  // &0x7A2C08
    a0 = 0;
    link(ctx, 0x55B774u);  // $ra first: the delay slot below depends on it
    lw(v1, v0, 0);
    call(ctx, gen::fn_sub_55D108_0055d108);
    a0 = 0;
    jal(ctx, 0x55B77Cu, gen::fn_sub_55D198_0055d198);
    v0 = 0x7A0000;
    ld(ra, sp, 0x0);
    v0 = addiu(v0, 11288);  // &0x7A2C18
    sp = addiu(sp, 0x10);
}

// 0x0055B848 sub_55B848 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Whether a host CI handle's transfer has ended: sceIoctl(fd +24, 1, &h+20) with the SRD trace codes 0x4000 / 0x4001
// around it; 1 when the call succeeded and +20 != 1 (not executing), else 0.
void sub_55B848(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b848
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    a0 = 16384;
    jal(ctx, 0x55B85Cu, gen::fn_sub_558988_00558988);
    s1 = addiu(s0, l20::htci::kIoStat);
    lw(a0, s0, l20::htci::kFd);
    a1 = 1;
    a2 = s1;
    jal(ctx, 0x55B870u, gen::fn_sub_558C20_00558c20);
    a0 = 16385;
    s0 = v0;
    jal(ctx, 0x55B87Cu, gen::fn_sub_558988_00558988);
    v0 = 0;
    if (i64(s0) >= 0) {
        // 0x0055b88c
        charge(ctx, 3);
        lw(v0, s1, 0);
        v0 = v0 ^ 0x1;
        v0 = sltu(0, v0);
    }
    // 0x0055b898 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055BA50 sub_55BA50 -- 20 bytes; leaf frame (no stack)
// The host CI error callback: function 0x7A2C0C = $a0, object 0x7A2C10 = $a1. [proposed htCiEntryErrFunc]
void sub_55BA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055ba50
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v1 = 0x7A0000;
    sw(a0, v0, 11276);  // 0x7A2C0C
    sw(a1, v1, 11280);  // 0x7A2C10
}

// 0x0055BB08 sub_55BB08 -- 36 bytes; frame 0x10: ra sp+0x0
// The host file's size (sub_55BB30) as a sign-extended 32-bit value. [proposed htCiGetFileSize]
void sub_55BB08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055bb08
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x55BB10u, gen::fn_sub_55BB30_0055bb30);
    ld(ra, sp, 0x0);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    sp = addiu(sp, 0x10);
}

// 0x0055BDC8 sub_55BDC8 -- 376 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, ra sp+0x28
// Opens a host file for reading: null name, a write mode or no free handle (sub_55BD70) report E0092708 / 09 / 10 and
// return 0. A file-cache hit (sub_55CF08) takes the cached offset and size (cached +1 = 1); else builds the full path
// (0x7A2EF0), prints "HTCI: File cache was not hit.", takes the size (sub_55BB30; 0 fails) and sceOpen's it with mode
// 0x7A3030 (trace 0x4900 / 0x4901; a failure reports E0092711 and frees the handle). Then the sector count (size +
// 2047) >> 11, the counters cleared, used = 1. [named by its own text: htCiOpen]
void sub_55BDC8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055bdc8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    sd(zero, sp, 0x0);
    if (s1 == 0) {
        // 0x0055bde8
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 20936);  // "E0092708:fname is null.(htCiOpen)"
        goto L_0055be30;
    }
    // 0x0055bdf8
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (a2 != 0) {
        // 0x0055be00
        charge(ctx, 3);
        a0 = 0;
        a1 = addiu(a1, 20976);
        goto L_0055be30;
    }
    // 0x0055be10
    charge(ctx, 5);
    jal(ctx, 0x55BE10u, gen::fn_sub_55BD70_0055bd70);
    s0 = v0;
    a0 = s1;
    if (s0 != 0) {
        // 0x0055be40
        charge(ctx, 5);
        a1 = sp;
        jal(ctx, 0x55BE40u, gen::fn_sub_55CF08_0055cf08);
        lw(v0, sp, 0x4);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (cc) {
            // 0x0055bee0
            charge(ctx, 5);
            sb(v0, s0, l20::htci::kCached);
            lw(v1, sp, 0x0);
            sw(v1, s0, l20::htci::kFd);
            lw(v0, sp, 0x4);
            sd(v0, s0, l20::htci::kSize);
        L_0055bef4:
            charge(ctx, 13);
            ld(v1, s0, l20::htci::kSize);
            v0 = 1;
            sw(zero, s0, 28);
            v1 = daddiu(v1, 2047);
            sw(zero, s0, 32);
            v1 = dsll(v1, 21);
            v1 = dsra32(v1, 0);
            sw(zero, s0, 36);
            sw(v1, s0, l20::htci::kNumSct);
            sw(zero, s0, l20::htci::kIoStat);
            sb(zero, s0, l20::htci::kTrState);
            sb(v0, s0, l20::htci::kUsed);
            v0 = s0;
        } else {
            // 0x0055be54
            charge(ctx, 15);
            v0 = 0x7A0000;
            a0 = s1;
            s2 = addiu(v0, 12016);  // &0x7A2EF0
            a1 = s2;
            jal(ctx, 0x55BE60u, gen::fn_sub_55C610_0055c610);
            a0 = 0x7C0000;
            a0 = addiu(a0, 21064);  // "HTCI: File cache was not hit. \"%s\"\n"
            a1 = s1;
            jal(ctx, 0x55BE70u, gen::fn_sub_5416E8_005416e8);
            a0 = s1;
            jal(ctx, 0x55BE78u, gen::fn_sub_55BB30_0055bb30);
            v1 = v0;
            v0 = 0;
            sd(v1, s0, l20::htci::kSize);
            if (v1 != 0) {
                // 0x0055be90
                charge(ctx, 12);
                a0 = 18688;
                jal(ctx, 0x55BE90u, gen::fn_sub_558988_00558988);
                v0 = 0x7A0000;
                lw(a1, v0, 12336);  // 0x7A3030
                a0 = s2;
                jal(ctx, 0x55BEA0u, gen::fn_sub_558C98_00558c98);
                a0 = 18689;
                link(ctx, 0x55BEACu);  // $ra first: the delay slot below depends on it
                sw(v0, s0, l20::htci::kFd);
                call(ctx, gen::fn_sub_558988_00558988);
                lw(v0, s0, l20::htci::kFd);
                if (i64(v0) >= 0) {
                    sb(zero, s0, l20::htci::kCached);
                    goto L_0055bef4;
                }
                // 0x0055bec0
                charge(ctx, 8);
                a1 = 0x7C0000;
                a0 = 0;
                a1 = addiu(a1, 21104);  // "E0092711:sceOpen fail.(htCiOpen)"
                jal(ctx, 0x55BEC8u, gen::fn_sub_55B7C8_0055b7c8);
                a0 = s0;
                jal(ctx, 0x55BED0u, gen::fn_sub_55BDA8_0055bda8);
                v0 = 0;
            }
        }
    } else {
        // 0x0055be24
        charge(ctx, 3);
        a1 = 0x7C0000;
        a0 = 0;
        a1 = addiu(a1, 21016);  // "E0092710:not enough handle resource.(htCiOpen)"
    L_0055be30:
        charge(ctx, 4);
        jal(ctx, 0x55BE30u, gen::fn_sub_55B7C8_0055b7c8);
        v0 = 0;
    }
    // 0x0055bf28 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055BF40 sub_55BF40 -- 156 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Closes a host CI handle: stops a running transfer (state +2 >= 2: sub_55C240), sceClose's an uncached one (trace
// 0x5000 / 0x5001; "HTCI: Failed sceClose" on error), marks it free and clears it (sub_55BDA8, a tail call). [proposed
// htCiClose]
void sub_55BF40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055bf40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (s1 == 0) {
        // 0x0055bfc8
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055bf58
    charge(ctx, 4);
    lbu(v0, s1, l20::htci::kTrState);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        lb(v0, s1, l20::htci::kCached);
    } else {
        // 0x0055bf68
        charge(ctx, 3);
        jal(ctx, 0x55BF68u, gen::fn_sub_55C240_0055c240);
        lb(v0, s1, l20::htci::kCached);
    }
    // 0x0055bf74
    charge(ctx, 2);
    if (v0 != 0) {
        sb(zero, s1, l20::htci::kUsed);
    } else {
        // 0x0055bf7c
        charge(ctx, 10);
        a0 = 20480;
        jal(ctx, 0x55BF7Cu, gen::fn_sub_558988_00558988);
        link(ctx, 0x55BF84u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, l20::htci::kFd);
        call(ctx, gen::fn_sub_558D00_00558d00);
        a0 = 20481;
        s0 = v0;
        jal(ctx, 0x55BF90u, gen::fn_sub_558988_00558988);
        a0 = 0x7C0000;
        a0 = addiu(a0, 21144);  // "HTCI: Failed sceClose\n"
        if (i64(s0) < 0) {
            // 0x0055bfa4
            charge(ctx, 2);
            jal(ctx, 0x55BFA4u, gen::fn_sub_5416E8_005416e8);
        }
        // 0x0055bfac
        charge(ctx, 1);
        sb(zero, s1, l20::htci::kUsed);
    }
    // 0x0055bfb0
    charge(ctx, 6);
    a0 = s1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55BDA8_0055bda8(ctx);  // tail call
}

// 0x0055CF58 sub_55CF58 -- 344 bytes; frame 0x30: s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s2 sp+0x10, ra sp+0x28
// Loads the host file list $a0 into the buffer $a1 ($a2 bytes, $a3 = the name length): clears the 4 KiB read buffer
// 0x998BC0, the cache descriptor once (sub_55CEE0) and the open files (sub_55CCE8); a null buffer or size prints "HTCI:
// Invalidate filelist ..." and returns 0; reads the file (sub_55C9D0; failure: "HTCI: Can't read filelist file." and
// E0111501) and parses it into $a2 / ($a3 + 9) entries (sub_55C830, sub_55CB30). Returns 8 x ($a2 / ($a3 + 9)) + n x
// ($a3 + 1), n from sub_55CB30. [named by its own text: htCiLoadDirInfo]
void sub_55CF58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055cf58
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x9A0000;
    sd(s4, sp, 0x20);
    s4 = addiu(v0, -29760);  // &0x998BC0
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    a2 = 4096;
    a0 = s4;
    a1 = 0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    s2 = a3;
    jal(ctx, 0x55CF94u, gen::fn_memset_00521408);
    v1 = 0x7A0000;
    lw(v0, v1, 12320);  // 0x7A3020
    if (v0 == 0) {
        // 0x0055cfac
        charge(ctx, 2);
        jal(ctx, 0x55CFACu, gen::fn_sub_55CEE0_0055cee0);
    }
    // 0x0055cfb4
    charge(ctx, 4);
    jal(ctx, 0x55CFB4u, gen::fn_sub_55CCE8_0055cce8);
    v0 = 0;
    if (s0 != 0) {
        // 0x0055cfc4
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s3 == 0) {
            // 0x0055cfcc
            charge(ctx, 3);
            a1 = 0;
            a0 = addiu(a0, 21576);
            goto L_0055cfec;
        }
        // 0x0055cfd8
        charge(ctx, 2);
        a0 = s3;
        if (s1 != 0) {
            // 0x0055d000
            charge(ctx, 8);
            a1 = 0;
            a2 = s1;
            jal(ctx, 0x55D004u, gen::fn_memset_00521408);
            a0 = s0;
            a1 = s4;
            jal(ctx, 0x55D010u, gen::fn_sub_55C9D0_0055c9d0);
            if (v0 != 0) {
                s0 = addiu(s2, 9);
                // 0x0055d048
                charge(ctx, 6);
                a3 = s2;
                divu(s1, s0);
                a1 = s4;
                a0 = s3;
                if (s0 == 0) {
                    brk(ctx, 0x55D05Cu, 0x7u);
                }
                // 0x0055d060
                charge(ctx, 10);
                s2 = addiu(s2, 1);
                mflo(s1);
                a2 = s1;
                s1 = sll(s1, 3);
                jal(ctx, 0x55D06Cu, gen::fn_sub_55C830_0055c830);
                a0 = s3;
                a1 = v0;
                jal(ctx, 0x55D078u, gen::fn_sub_55CB30_0055cb30);
                if (s0 == 0) {
                    brk(ctx, 0x55D084u, 0x7u);
                }
                // 0x0055d088
                charge(ctx, 2);
                mult(v0, v0, s2);
                v0 = addu(s1, v0);
            } else {
                // 0x0055d020
                charge(ctx, 10);
                a0 = 0x7C0000;
                a1 = s0;
                a0 = addiu(a0, 21672);  // "HTCI: Can't read filelist file.(%s)\n"
                jal(ctx, 0x55D028u, gen::fn_sub_5416E8_005416e8);
                a1 = 0x7C0000;
                a1 = addiu(a1, 21712);  // "E0111501:can't read filelist.(htCiLoadDirInfo)"
                a0 = 0;
                jal(ctx, 0x55D038u, gen::fn_sub_55B7C8_0055b7c8);
                v0 = 0;
            }
        } else {
            // 0x0055cfe0
            charge(ctx, 3);
            a0 = 0x7C0000;
            a1 = 0;
            a0 = addiu(a0, 21624);  // &0x7C5478
        L_0055cfec:
            charge(ctx, 4);
            jal(ctx, 0x55CFECu, gen::fn_sub_5416E8_005416e8);
            v0 = 0;
        }
    }
    // 0x0055d090 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055D0B0 sub_55D0B0 -- 36 bytes; frame 0x20: ra sp+0x10
// Whether $a0 is in the host file cache (sub_55CF08 into a stack record; its size word +4 != 0).
void sub_55D0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d0b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x55D0B8u, gen::fn_sub_55CF08_0055cf08);
    lw(v0, sp, 0x4);
    ld(ra, sp, 0x10);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x20);
}

// 0x0055D0D8 sub_55D0D8 -- 48 bytes; leaf frame (no stack)
// The host open mode 0x7A3030: 1 (SCE_RDONLY) when $a0 == 1, else 0x8001 (SCE_RDONLY | SCE_NOWAIT).
void sub_55D0D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0055d0d8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
    if (a0 == 0) {
        // 0x0055d0f8
        charge(ctx, 1);
        v1 = 0x7A0000;
        // 0x0055d0fc (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = 0x8001;
        sw(v0, v1, 12336);
        return;
    }
    // 0x0055d0e0
    charge(ctx, 2);
    v1 = 0x7A0000;
    if (a0 != v0) {
        // 0x0055d0fc (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = 0x8001;
        sw(v0, v1, 12336);
        return;
    }
    // 0x0055d0e8
    charge(ctx, 3);
    v0 = 0x7A0000;
    sw(a0, v0, 12336);  // 0x7A3030
}

// 0x0055D188 sceLibgcc32GetErxEntries_7 -- 12 bytes; leaf frame (no stack)
// The address of the root directory 0x7A3038. (A FLIRT name.)
void sceLibgcc32GetErxEntries_7(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055d188
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v0 = addiu(v0, 12344);  // &0x7A3038
}

// 0x0055D200 sceLibgcc32GetErxEntries_8 -- 12 bytes; leaf frame (no stack)
// The address of the device prefix 0x7A3140. (A FLIRT name.)
void sceLibgcc32GetErxEntries_8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055d200
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    v0 = addiu(v0, 12608);  // &0x7A3140
}

// 0x0055D210 WTLS_get_table -- 12 bytes; leaf frame (no stack)
// The host open mode 0x7A3030 (sub_55D0D8's). (A FLIRT name.)
void WTLS_get_table(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0055d210
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 12336);  // 0x7A3030
}

// 0x0055D230 __errno_9 -- 12 bytes; leaf frame (no stack)
// The word 0x7A3034. (A FLIRT name.)
void __errno_9(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0055d230
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 12340);  // 0x7A3034
}

// 0x0055D6F0 sub_55D6F0 -- 60 bytes; frame 0x10: ra sp+0x0
// LSC: the flag byte +4 of the stream queue $a0 = ($a1 == 1); returns 1. A null queue reports "E2005012808: Illigal
// parameter lsc=NULL" (sub_55DBE8, a tail call).
void sub_55D6F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d6f0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055d6fc
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 22104);  // "E2005012808: Illigal parameter lsc=NULL\n"
        sp = addiu(sp, 0x10);
        gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
        return;
    }
    // 0x0055d710
    charge(ctx, 3);
    v0 = 1;
    if (a1 != v0) {
        sb(zero, a0, 4);
    } else {
        // 0x0055d71c
        charge(ctx, 1);
        sb(a1, a0, 4);
    }
    // 0x0055d720 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055DAE0 sub_55DAE0 -- 64 bytes; leaf frame (no stack)
// The LSC error callback: function, object and a third word (0x7A3168 / 0x7A316C / 0x7A3170) = $a0..$a2, all 0 when $a0
// is null.
void sub_55DAE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0055dae0
    enter(ctx, 3);  // entry check point + this block's cycles
    a3 = a0;
    v0 = 0x7A0000;
    if (a3 != 0) {
        // 0x0055db08
        charge(ctx, 6);
        v1 = 0x7A0000;
        a0 = 0x7A0000;
        sw(a3, v0, 12648);
        sw(a1, v1, 12652);  // 0x7A316C
        sw(a2, a0, 12656);  // 0x7A3170
        return;
    }
    // 0x0055daec
    charge(ctx, 6);
    v1 = 0x7A0000;
    a0 = 0x7A0000;
    sw(zero, v0, 12648);
    sw(zero, v1, 12652);  // 0x7A316C
    sw(zero, a0, 12656);  // 0x7A3170
}

// 0x0055E498 sub_55E498 -- 156 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Opens a memory file whose name is "address.size" in hex: null name, a write mode or no free handle (sub_55E3B0)
// report E01100301 / 02 / 03 and return 0; else copies the name (+28) and opens it (sub_55E428). [named by its own
// text: mfCiOpen]
void sub_55E498(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e498
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (s1 == 0) {
        // 0x0055e4b0
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23136);  // "E01100301:fname is null.(mfCiOpen)"
        goto L_0055e4f4;
    }
    // 0x0055e4c0
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (a2 != 0) {
        // 0x0055e4c8
        charge(ctx, 3);
        a0 = 0;
        a1 = addiu(a1, 23176);
        goto L_0055e4f4;
    }
    // 0x0055e4d8
    charge(ctx, 7);
    jal(ctx, 0x55E4D8u, gen::fn_sub_55E3B0_0055e3b0);
    a1 = 0x7C0000;
    s0 = v0;
    a1 = addiu(a1, 23216);  // "E01100303:not enough handle resource.(mfCiOpen)"
    a0 = 0;
    if (s0 != 0) {
        // 0x0055e508
        charge(ctx, 6);
        a1 = s1;
        a0 = addiu(s0, l20::mfci::kName);
        jal(ctx, 0x55E50Cu, gen::fn_strcpy_00524270);
        a0 = s0;
        jal(ctx, 0x55E514u, gen::fn_sub_55E428_0055e428);
        v0 = s0;
    } else {
    L_0055e4f4:
        charge(ctx, 4);
        jal(ctx, 0x55E4F4u, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e520 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055E538 sub_55E538 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Closes a memory-file handle: clears its status (sub_55E800); a used one (+0 == 1) is marked free and cleared
// (sub_55E408). [proposed mfCiClose]
void sub_55E538(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e538
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x0055e54c
        charge(ctx, 6);
        jal(ctx, 0x55E54Cu, gen::fn_sub_55E800_0055e800);
        v1 = 1;
        lb(v0, s0, l20::mfci::kUsed);
        a0 = s0;
        if (v0 == v1) {
            // 0x0055e564
            charge(ctx, 2);
            link(ctx, 0x55E564u);  // $ra first: the delay slot below depends on it
            sb(zero, s0, l20::mfci::kUsed);
            call(ctx, gen::fn_sub_55E408_0055e408);
        }
    }
    // 0x0055e56c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0055E580 sub_55E580 -- 188 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Seeks a memory-file handle in sectors, inside the lock: whence $a2 = 0 from the start, 1 from the position, 2 from
// the end; clamped to 0..sectors (+12); returns the new position (+16). A null handle reports E01100305 and returns 0.
// [proposed mfCiSeek]
void sub_55E580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055e580
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x18);
    if (s0 != 0) {
        // 0x0055e5b8
        charge(ctx, 4);
        jal(ctx, 0x55E5B8u, gen::fn_sub_55E190_0055e190);
        v0 = 2;
        if (s1 != 0) {
            // 0x0055e5d0
            charge(ctx, 2);
            cc = s1 != v0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                // 0x0055e5e8
                charge(ctx, 2);
                lw(a0, s0, l20::mfci::kNumSct);
                if (s1 == v0) {
                    // 0x0055e5f0
                    charge(ctx, 4);
                    lw(v0, s0, l20::mfci::kPos);
                    v0 = addu(v0, s2);
                    sw(v0, s0, l20::mfci::kPos);
                }
            } else {
                // 0x0055e5d8
                charge(ctx, 4);
                lw(a0, s0, l20::mfci::kNumSct);
                v0 = addu(a0, s2);
                sw(v0, s0, l20::mfci::kPos);
            }
        } else {
            // 0x0055e5c8
            charge(ctx, 2);
            sw(s2, s0, l20::mfci::kPos);
            // 0x0055e600
            charge(ctx, 1);
            lw(a0, s0, l20::mfci::kNumSct);
        }
        // 0x0055e604
        charge(ctx, 8);
        lw(v0, s0, l20::mfci::kPos);
        v1 = slt(v0, a0);
        if (v1 == 0) v0 = a0;
        a0 = slti(v0, 0);
        if (a0 != 0) v0 = 0;
        link(ctx, 0x55E618u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, l20::mfci::kPos);
        call(ctx, gen::fn_sub_55E1A8_0055e1a8);
        lw(v0, s0, l20::mfci::kPos);
    } else {
        // 0x0055e5a4
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23264);  // "E01100305:handl is null."
        jal(ctx, 0x55E5A8u, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e624 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0055E640 sub_55E640 -- 56 bytes; frame 0x10: ra sp+0x0
// The position (+16, sectors) of a memory-file handle; null: E01100306, 0. [proposed mfCiTell]
void sub_55E640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e640
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055e668
        charge(ctx, 1);
        lw(v0, v0, l20::mfci::kPos);
    } else {
        // 0x0055e650
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23296);  // "E01100306:handl is null."
        jal(ctx, 0x55E654u, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e66c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055E678 sub_55E678 -- 392 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x10, s3 sp+0x28, s1 sp+0x18, ra sp+0x30
// Reads $a1 sectors of a memory file into $a2 (a memcpy from its address, the tail past the file end zeroed): a null
// handle / buffer or a negative count report E01100307 / 08 / 09 and return 0; 0 sectors completes at once; a busy
// handle (+1 == 2) returns 0. Clamps to the sectors left, advances the position, records the bytes moved (+20) and
// completes (+1 = 1); returns the sectors read. [proposed mfCiReqRd]
void sub_55E678(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e678
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x30);
    if (s2 == 0) {
        // 0x0055e6a0
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23328);  // "E01100307:handl is null."
        goto L_0055e6cc;
    }
    // 0x0055e6b0
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (i64(s0) < 0) {
        // 0x0055e6b8
        charge(ctx, 2);
        a1 = addiu(a1, 23360);
        goto L_0055e6cc;
    }
    // 0x0055e6c0
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (s3 != 0) {
        // 0x0055e6e0
        charge(ctx, 2);
        if (s0 != 0) {
            lb(v1, s2, l20::mfci::kStat);
            // 0x0055e6f8
            charge(ctx, 3);
            s1 = 2;
            v0 = 0;
            if (v1 != s1) {
                // 0x0055e704
                charge(ctx, 13);
                jal(ctx, 0x55E704u, gen::fn_sub_55E190_0055e190);
                sw(zero, s2, l20::mfci::kTrBytes);
                lw(a0, s2, l20::mfci::kPos);
                lw(v0, s2, l20::mfci::kNumSct);
                lw(a1, s2, l20::mfci::kSctLen);
                v0 = subu(v0, a0);
                v1 = slt(s0, v0);
                mult(a0, a0, a1);
                if (v1 != 0) v0 = s0;
                mult(v1, v0, a1);
                sw(v0, s2, l20::mfci::kReqSct);
                if (v1 != 0) {
                    // 0x0055e750
                    charge(ctx, 37);
                    sw(a0, s2, l20::mfci::kRdOfs);
                    a0 = addiu(s2, l20::mfci::kName);
                    sw(v1, s2, l20::mfci::kRdLen);
                    a1 = sp;
                    link(ctx, 0x55E760u);  // $ra first: the delay slot below depends on it
                    sb(s1, s2, l20::mfci::kStat);
                    call(ctx, gen::fn_sub_55E220_0055e220);
                    lw(a0, s2, l20::mfci::kRdOfs);
                    s1 = v0;
                    lw(v0, sp, 0x0);
                    lw(s0, s2, l20::mfci::kRdLen);
                    v0 = subu(v0, a0);
                    v1 = slt(v0, s0);
                    if (v1 != 0) s0 = v0;
                    jal(ctx, 0x55E780u, gen::fn_sub_55E1A8_0055e1a8);
                    lw(a1, s2, l20::mfci::kRdOfs);
                    a0 = s3;
                    lw(a2, s2, l20::mfci::kRdLen);
                    a1 = addu(s1, a1);
                    jal(ctx, 0x55E794u, gen::fn_memcpy_00521250);
                    lw(a2, s2, l20::mfci::kRdLen);
                    a0 = addu(s3, s0);
                    a1 = 0;
                    a2 = subu(a2, s0);
                    jal(ctx, 0x55E7A8u, gen::fn_memset_00521408);
                    jal(ctx, 0x55E7B0u, gen::fn_sub_55E190_0055e190);
                    lw(a0, s2, l20::mfci::kReqSct);
                    a1 = 1;
                    lw(v1, s2, l20::mfci::kSctLen);
                    lw(v0, s2, l20::mfci::kPos);
                    mult(v1, a0, v1);
                    sb(a1, s2, l20::mfci::kStat);
                    v0 = addu(v0, a0);
                    sw(v0, s2, l20::mfci::kPos);
                    link(ctx, 0x55E7D8u);  // $ra first: the delay slot below depends on it
                    sw(v1, s2, l20::mfci::kTrBytes);
                    call(ctx, gen::fn_sub_55E1A8_0055e1a8);
                    lw(v0, s2, l20::mfci::kReqSct);
                } else {
                    // 0x0055e738
                    charge(ctx, 5);
                    v0 = 1;
                    link(ctx, 0x55E73Cu);  // $ra first: the delay slot below depends on it
                    sb(v0, s2, l20::mfci::kStat);
                    call(ctx, gen::fn_sub_55E1A8_0055e1a8);
                    v0 = 0;
                }
            }
        } else {
            // 0x0055e6e8
            charge(ctx, 4);
            v1 = 1;
            v0 = 0;
            sb(v1, s2, l20::mfci::kStat);
        }
    } else {
        // 0x0055e6c8
        charge(ctx, 1);
        a1 = addiu(a1, 23392);
    L_0055e6cc:
        charge(ctx, 4);
        jal(ctx, 0x55E6CCu, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e7e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0055E850 sub_55E850 -- 56 bytes; frame 0x10: ra sp+0x0
// The status byte (+1) of a memory-file handle; null: E0092912, 0. [proposed mfCiGetStat]
void sub_55E850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e850
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055e878
        charge(ctx, 1);
        lb(v0, v0, l20::mfci::kStat);
    } else {
        // 0x0055e860
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23432);  // "E0092912:handl is null."
        jal(ctx, 0x55E864u, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e87c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055E888 sub_55E888 -- 56 bytes; frame 0x10: ra sp+0x0
// The sector length (+4) of a memory-file handle; null: E0040301, 0. [proposed mfCiGetSctLen]
void sub_55E888(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e888
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055e8b0
        charge(ctx, 1);
        lw(v0, v0, l20::mfci::kSctLen);
    } else {
        // 0x0055e898
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 23456);  // "E0040301:handl is null."
        jal(ctx, 0x55E89Cu, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e8b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055E8C0 sub_55E8C0 -- 124 bytes; frame 0x10: ra sp+0x0
// Sets the sector length of a memory-file handle and rescales by it: sectors = (size + len - 1) / len, position =
// position x old len / len, bytes moved = request x len. Null: E0040302. [proposed mfCiSetSctLen]
void sub_55E8C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e8c0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a0;
    sd(ra, sp, 0x0);
    if (a2 == 0) {
        // 0x0055e8d0
        charge(ctx, 5);
        a1 = 0x7C0000;
        ld(ra, sp, 0x0);
        a1 = addiu(a1, 23480);  // "E0040302:handl is null."
        sp = addiu(sp, 0x10);
        gen::fn_sub_55E1D8_0055e1d8(ctx);  // tail call
        return;
    }
    // 0x0055e8e8
    charge(ctx, 9);
    lw(v0, a2, l20::mfci::kSize);
    lw(v1, a2, l20::mfci::kPos);
    v0 = addu(v0, a1);
    lw(a0, a2, l20::mfci::kSctLen);
    v0 = addiu(v0, -1);
    sw(a1, a2, l20::mfci::kSctLen);
    div(v0, a1);
    if (a1 == 0) {
        brk(ctx, 0x55E908u, 0x7u);
    }
    // 0x0055e90c
    charge(ctx, 12);
    mflo(v0);
    mult(v1, v1, a0);
    sw(v0, a2, l20::mfci::kNumSct);
    lw(v0, a2, l20::mfci::kReqSct);
    ld(ra, sp, 0x0);
    div(v1, a1);
    mflo(v1);
    mult(v0, v0, a1);
    sw(v1, a2, l20::mfci::kPos);
    sw(v0, a2, l20::mfci::kTrBytes);
    sp = addiu(sp, 0x10);
}

// 0x0055EFC8 sub_55EFC8 -- 92 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// The PL2 encoder (sub_55F028) inside the CRI critical section.
void sub_55EFC8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055efc8
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
    jal(ctx, 0x55EFECu, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x55F000u, gen::fn_sub_55F028_0055f028);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055F640 sub_55F640 -- 24 bytes; frame 0x10: ra sp+0x0
// sub_55F1C8 on the object at $a0 + 232 (a tail call).
void sub_55F640(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f640
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 232);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55F1C8_0055f1c8(ctx);  // tail call
}

// 0x00560DE8 sub_560DE8 -- 72 bytes; frame 0x10: ra sp+0x0
// Prints "PS2RNA_ClearBuf: not implemented" (sub_541760, a tail call) unless the mode word 0x7A93F8 is 1 with no count
// (0x7A93F0 <= 0). [named by its own text: PS2RNA_ClearBuf]
void sub_560DE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560de8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00560e00
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00560e10;
        }
        // 0x00560e28
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560e10:
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26128);  // "PS2RNA_ClearBuf: not implemented\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x00560E30 sub_560E30 -- 72 bytes; frame 0x10: ra sp+0x0
// Prints "PS2RNA_SetPcmType: not implemented" unless the mode word 0x7A93F8 is 1 with no count (0x7A93F0 <= 0). [named
// by its own text: PS2RNA_SetPcmType]
void sub_560E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560e30
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00560e48
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00560e58;
        }
        // 0x00560e70
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560e58:
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26168);  // "PS2RNA_SetPcmType: not implemented\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x005613E0 sub_5613E0 -- 68 bytes; frame 0x10: ra sp+0x0
// Prints "PS2RNA_GetStartSmpl: not implemented" unless the mode word 0x7A93F8 is 1 with no count; returns 0. [named by
// its own text: PS2RNA_GetStartSmpl]
void sub_5613E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005613e0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x005613f8
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_00561408;
        }
        // 0x00561418 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00561408:
    charge(ctx, 4);
    a0 = 0x7C0000;
    a0 = addiu(a0, 26360);  // "PS2RNA_GetStartSmpl: not implemented\n"
    jal(ctx, 0x56140Cu, gen::fn_sub_541760_00541760);
    v0 = 0;
    // 0x00561418 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561518 sub_561518 -- 68 bytes; frame 0x10: ra sp+0x0
// Prints "PS2RNA_IsOverflow: not implemented" unless the mode word 0x7A93F8 is 1 with no count; returns 0. [named by
// its own text: PS2RNA_IsOverflow]
void sub_561518(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561518
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00561530
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_00561540;
        }
        // 0x00561550 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00561540:
    charge(ctx, 4);
    a0 = 0x7C0000;
    a0 = addiu(a0, 26400);  // "PS2RNA_IsOverflow: not implemented\n"
    jal(ctx, 0x561544u, gen::fn_sub_541760_00541760);
    v0 = 0;
    // 0x00561550 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00561560 sub_561560 -- 72 bytes; frame 0x10: ra sp+0x0
// Prints "PS2RNA_ClearOverflow: not implemented" unless the mode word 0x7A93F8 is 1 with no count. [named by its own
// text: PS2RNA_ClearOverflow]
void sub_561560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561560
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00561578
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00561588;
        }
        // 0x005615a0
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00561588:
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26440);  // "PS2RNA_ClearOverflow: not implemented\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x005615A8 nullsub_144 -- 8 bytes; leaf frame (no stack)
// An empty function.
void nullsub_144(EEContext& ctx) {
    using namespace hg;
    // 0x005615a8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005615F8 sub_5615F8 -- 72 bytes; frame 0x10: ra sp+0x0
// Prints "PS2RNA_SetTotalNumSmpl: not implemented" unless the mode word 0x7A93F8 is 1 with no count. [named by its own
// text: PS2RNA_SetTotalNumSmpl]
void sub_5615F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005615f8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    if (v1 == a0) {
        // 0x00561610
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00561620;
        }
        // 0x00561638
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_00561620:
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 26520);  // "PS2RNA_SetTotalNumSmpl: not implemented\n"
    sp = addiu(sp, 0x10);
    gen::fn_sub_541760_00541760(ctx);  // tail call
}

// 0x00561708 sub_561708 -- 12 bytes; leaf frame (no stack)
// Clears the word 0x7AC768.
void sub_561708(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2};
    // 0x00561708
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(zero, v0, -14488);  // 0x7AC768
}

// 0x00561718 sub_561718 -- 12 bytes; leaf frame (no stack)
// Clears the word 0x7AC768 (a twin of sub_561708).
void sub_561718(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2};
    // 0x00561718
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(zero, v0, -14488);  // 0x7AC768
}

// 0x00563DD0 sub_563DD0 -- 240 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Writes a 16-byte block header into the buffer {ptr, size} at $a0: clears the buffer, the tag $a1 (7 chars, strncpy)
// at +0 and (size - 16) as 7 lower-case hex digits at +8. Two chunks (0x563C88 and 0x563DD0).
void sub_563DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563dd0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a1 = 0;
    lw(a0, s0, 0);
    link(ctx, 0x563DF0u);  // $ra first: the delay slot below depends on it
    lw(a2, s0, 4);
    call(ctx, gen::fn_memset_00521408);
    lw(a0, s0, 0);
    a1 = s1;
    a2 = 7;
    jal(ctx, 0x563E00u, gen::fn_strncpy_00524828);
    lw(a0, s0, 4);
    lw(a1, s0, 0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, -16);
    ld(s0, sp, 0x0);
    a1 = addiu(a1, 8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x00563c88
    charge(ctx, 37);
    v1 = 0x7B0000;
    v0 = a0 & 0xF;
    v1 = addiu(v1, 6360);  // "0123456789abcdef"
    a0 = sra(a0, 4);
    v0 = addu(v0, v1);
    lbu(a2, v0, 0);
    v0 = a0 & 0xF;
    v0 = addu(v0, v1);
    a0 = sra(a0, 4);
    sb(a2, a1, 6);
    a2 = a0 & 0xF;
    a2 = addu(a2, v1);
    a0 = sra(a0, 4);
    lbu(a3, v0, 0);
    v0 = a0 & 0xF;
    v0 = addu(v0, v1);
    a0 = sra(a0, 4);
    sb(a3, a1, 5);
    t0 = a0 & 0xF;
    t0 = addu(t0, v1);
    a0 = sra(a0, 4);
    lbu(t1, a2, 0);
    a3 = a0 & 0xF;
    a0 = sra(a0, 4);
    a3 = addu(a3, v1);
    sb(t1, a1, 4);
    a0 = a0 & 0xF;
    a0 = addu(a0, v1);
    lbu(a2, v0, 0);
    sb(a2, a1, 3);
    lbu(v0, t0, 0);
    sb(v0, a1, 2);
    lbu(v1, a3, 0);
    sb(v1, a1, 1);
    lbu(v0, a0, 0);
    sb(v0, a1, 0);
}

// 0x00563F38 sub_563F38 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// DTX URPC command 32 with three words ($a0..$a2 into 0x999C00..): DTX_CallUrpc(32, 0x999C00, 3, 0x999D00, 1); returns
// the reply word.
void sub_563F38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563f38
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    sd(ra, sp, 0x8);
    s0 = addiu(s0, -25344);  // &0x999D00
    sw(a0, v0, 0);  // 0x999C00
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    sw(a2, v0, 8);  // 0x999C08
    a2 = 3;
    a3 = s0;
    a0 = 32;
    t0 = 1;
    jal(ctx, 0x563F70u, gen::fn_DTX_CallUrpc_00559c10);
    lw(v0, s0, 0);  // 0x999D00
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00563F90 sub_563F90 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// DTX URPC command 33 with two words: DTX_CallUrpc(33, 0x999C00, 2, 0x999D00, 1); returns the reply word.
void sub_563F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563f90
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    sd(ra, sp, 0x8);
    s0 = addiu(s0, -25344);  // &0x999D00
    sw(a0, v0, 0);  // 0x999C00
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    a3 = s0;
    a0 = 33;
    a2 = 2;
    t0 = 1;
    jal(ctx, 0x563FC4u, gen::fn_DTX_CallUrpc_00559c10);
    lw(v0, s0, 0);  // 0x999D00
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00564068 sub_564068 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// DTX URPC command 36 with one word, four reply words copied to 0x999BC0; returns that address.
void sub_564068(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564068
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    a1 = addiu(a1, -25600);  // &0x999C00
    s0 = addiu(s0, -25344);  // &0x999D00
    sd(ra, sp, 0x8);
    a3 = s0;
    sw(a0, a1, 0);  // 0x999C00
    a0 = 36;
    a2 = 1;
    t0 = 4;
    jal(ctx, 0x564094u, gen::fn_DTX_CallUrpc_00559c10);
    v1 = 0x9A0000;
    lw(a3, s0, 12);  // 0x999D0C
    v1 = addiu(v1, -25664);  // &0x999BC0
    lw(a2, s0, 0);  // 0x999D00
    v0 = v1;
    lw(a0, s0, 4);  // 0x999D04
    lw(a1, s0, 8);  // 0x999D08
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sw(a2, v1, 0);  // 0x999BC0
    sw(a0, v1, 4);  // 0x999BC4
    sw(a1, v1, 8);  // 0x999BC8
    sw(a3, v1, 12);  // 0x999BCC
    sp = addiu(sp, 0x10);
}

// 0x005640D8 sub_5640D8 -- 48 bytes; frame 0x10: ra sp+0x0
// DTX URPC command 37 with one word and no reply (a tail call).
void sub_5640D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005640d8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0x9A0000;
    sd(ra, sp, 0x0);
    a1 = addiu(a1, -25600);  // &0x999C00
    sw(a0, a1, 0);  // 0x999C00
    a0 = 37;
    ld(ra, sp, 0x0);
    a2 = 1;
    a3 = 0;
    t0 = 0;
    sp = addiu(sp, 0x10);
    gen::fn_DTX_CallUrpc_00559c10(ctx);  // tail call
}

// 0x00564108 sub_564108 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// DTX URPC command 38 with three words; the two reply words go to $a3[0], $a3[1].
void sub_564108(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564108
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = addiu(s0, -25344);  // &0x999D00
    sw(a0, v0, 0);  // 0x999C00
    a0 = 38;
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    sw(a2, v0, 8);  // 0x999C08
    a2 = 3;
    s1 = a3;
    a3 = s0;
    t0 = 2;
    jal(ctx, 0x564148u, gen::fn_DTX_CallUrpc_00559c10);
    lw(v1, s0, 0);  // 0x999D00
    lw(v0, s0, 4);  // 0x999D04
    sw(v1, s1, 0);
    sw(v0, s1, 4);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00564178 sub_564178 -- 76 bytes; frame 0x10: ra sp+0x0
// DTX URPC command 39 with $a0, $a1 and the two words at $a2; no reply (a tail call).
void sub_564178(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564178
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t1 = a2;
    sd(ra, sp, 0x0);
    v0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    a2 = 4;
    lw(v1, t1, 0);
    a3 = 0;
    sw(a0, v0, 0);  // 0x999C00
    a0 = 39;
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    sw(v1, v0, 8);  // 0x999C08
    t0 = 0;
    ld(ra, sp, 0x0);
    lw(v1, t1, 4);
    sw(v1, v0, 12);  // 0x999C0C
    sp = addiu(sp, 0x10);
    gen::fn_DTX_CallUrpc_00559c10(ctx);  // tail call
}

// 0x005641C8 sub_5641C8 -- 76 bytes; frame 0x10: ra sp+0x0
// DTX URPC command 40 with $a0, $a1 and the two words at $a2; no reply (a tail call).
void sub_5641C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005641c8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t1 = a2;
    sd(ra, sp, 0x0);
    v0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    a2 = 4;
    lw(v1, t1, 0);
    a3 = 0;
    sw(a0, v0, 0);  // 0x999C00
    a0 = 40;
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    sw(v1, v0, 8);  // 0x999C08
    t0 = 0;
    ld(ra, sp, 0x0);
    lw(v1, t1, 4);
    sw(v1, v0, 12);  // 0x999C0C
    sp = addiu(sp, 0x10);
    gen::fn_DTX_CallUrpc_00559c10(ctx);  // tail call
}

// 0x00564268 sub_564268 -- 104 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// DTX URPC command 42 with three words; the second reply word goes to *$a3, the first is returned.
void sub_564268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564268
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = addiu(s0, -25344);  // &0x999D00
    sw(a0, v0, 0);  // 0x999C00
    a0 = 42;
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    sw(a2, v0, 8);  // 0x999C08
    a2 = 3;
    s1 = a3;
    a3 = s0;
    t0 = 1;
    jal(ctx, 0x5642A8u, gen::fn_DTX_CallUrpc_00559c10);
    lw(v1, s0, 4);  // 0x999D04
    ld(ra, sp, 0x10);
    sw(v1, s1, 0);
    ld(s1, sp, 0x8);
    lw(v0, s0, 0);  // 0x999D00
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
