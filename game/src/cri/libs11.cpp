// Phase 5 slice libs11: 150 functions of the CRI middleware band 0x550808-0x55F670 -- the Dolby Pro Logic II
// encoder (PL2ENC 1.01) and its ADXT hooks and down-mix windows, the AIX player / parser accessors, the SRD host
// reader, the DVCI / HTCI file layers, the LSC stream queue, the DTX RPC server and a run of handle accessors / stubs.
// Each body starts from p3fes_handgen's faithful form (registers, frame, spills, $ra links, cycle charges and check
// points as the recompiled body; game/include/p3fes/game/hg_cpu.h); the role comment above each body, the record
// layouts of libs11.h and the named offsets are the readable layer. Pair tests: tests/game/test_libs11.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs11.h"

namespace p3fes::recomp_gen {
void fn_SRD_Create_00557a58(p3fes::EEContext&);
void fn_SRD_ExecServer_00558500(p3fes::EEContext&);
void fn_SRD_GetReadStatusDvd_00558768(p3fes::EEContext&);
void fn_SRD_SetDvdSeekPos_00558ae0(p3fes::EEContext&);
void fn_WTLS_set_table_0055d220(p3fes::EEContext&);
void fn___env_unlock_7_0055dc80(p3fes::EEContext&);
void fn___errno_6_005589f8(p3fes::EEContext&);
void fn___errno_7_00558a60(p3fes::EEContext&);
void fn_atan2l_7_0055b6e8(p3fes::EEContext&);
void fn_dvci_analysis_flist_0055ab80(p3fes::EEContext&);
void fn_dvci_get_fstate_0055b220(p3fes::EEContext&);
void fn_dvci_search_fstate_0055aea0(p3fes::EEContext&);
void fn_memcmp_005211b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nullsub_143_00553688(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_strtoul_00525e98(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_540D40_00540d40(p3fes::EEContext&);
void fn_sub_540D58_00540d58(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_5460E0_005460e0(p3fes::EEContext&);
void fn_sub_546270_00546270(p3fes::EEContext&);
void fn_sub_546368_00546368(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_546410_00546410(p3fes::EEContext&);
void fn_sub_546498_00546498(p3fes::EEContext&);
void fn_sub_5465A0_005465a0(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_546FA0_00546fa0(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_548768_00548768(p3fes::EEContext&);
void fn_sub_548AE8_00548ae8(p3fes::EEContext&);
void fn_sub_548EB8_00548eb8(p3fes::EEContext&);
void fn_sub_54AF38_0054af38(p3fes::EEContext&);
void fn_sub_54E7D8_0054e7d8_at_0054e7f0(p3fes::EEContext&);
void fn_sub_54E838_0054e838(p3fes::EEContext&);
void fn_sub_550808_00550808(p3fes::EEContext&);
void fn_sub_5509F8_005509f8(p3fes::EEContext&);
void fn_sub_550BE8_00550be8(p3fes::EEContext&);
void fn_sub_550DD8_00550dd8(p3fes::EEContext&);
void fn_sub_550FC8_00550fc8(p3fes::EEContext&);
void fn_sub_5511B8_005511b8(p3fes::EEContext&);
void fn_sub_551980_00551980(p3fes::EEContext&);
void fn_sub_551988_00551988(p3fes::EEContext&);
void fn_sub_552000_00552000(p3fes::EEContext&);
void fn_sub_552010_00552010(p3fes::EEContext&);
void fn_sub_552020_00552020(p3fes::EEContext&);
void fn_sub_5523B8_005523b8(p3fes::EEContext&);
void fn_sub_5523F8_005523f8(p3fes::EEContext&);
void fn_sub_552478_00552478(p3fes::EEContext&);
void fn_sub_552494_00552494(p3fes::EEContext&);
void fn_sub_5524A8_005524a8(p3fes::EEContext&);
void fn_sub_5524B8_005524b8(p3fes::EEContext&);
void fn_sub_5524C8_005524c8(p3fes::EEContext&);
void fn_sub_5524D0_005524d0(p3fes::EEContext&);
void fn_sub_5524D8_005524d8(p3fes::EEContext&);
void fn_sub_5524F0_005524f0(p3fes::EEContext&);
void fn_sub_552538_00552538(p3fes::EEContext&);
void fn_sub_552550_00552550(p3fes::EEContext&);
void fn_sub_552558_00552558(p3fes::EEContext&);
void fn_sub_552560_00552560(p3fes::EEContext&);
void fn_sub_552568_00552568(p3fes::EEContext&);
void fn_sub_552570_00552570(p3fes::EEContext&);
void fn_sub_552578_00552578(p3fes::EEContext&);
void fn_sub_552580_00552580(p3fes::EEContext&);
void fn_sub_552588_00552588(p3fes::EEContext&);
void fn_sub_5525A0_005525a0(p3fes::EEContext&);
void fn_sub_5525B8_005525b8(p3fes::EEContext&);
void fn_sub_5525D0_005525d0(p3fes::EEContext&);
void fn_sub_5525E8_005525e8(p3fes::EEContext&);
void fn_sub_552630_00552630(p3fes::EEContext&);
void fn_sub_552658_00552658(p3fes::EEContext&);
void fn_sub_552680_00552680(p3fes::EEContext&);
void fn_sub_552688_00552688(p3fes::EEContext&);
void fn_sub_552BD0_00552bd0(p3fes::EEContext&);
void fn_sub_552D08_00552d08(p3fes::EEContext&);
void fn_sub_552FA0_00552fa0(p3fes::EEContext&);
void fn_sub_5530D0_005530d0(p3fes::EEContext&);
void fn_sub_553188_00553188(p3fes::EEContext&);
void fn_sub_5531B8_005531b8(p3fes::EEContext&);
void fn_sub_553288_00553288(p3fes::EEContext&);
void fn_sub_553310_00553310(p3fes::EEContext&);
void fn_sub_553358_00553358(p3fes::EEContext&);
void fn_sub_553408_00553408(p3fes::EEContext&);
void fn_sub_553438_00553438(p3fes::EEContext&);
void fn_sub_553468_00553468(p3fes::EEContext&);
void fn_sub_553498_00553498(p3fes::EEContext&);
void fn_sub_553510_00553510(p3fes::EEContext&);
void fn_sub_553560_00553560(p3fes::EEContext&);
void fn_sub_553690_00553690(p3fes::EEContext&);
void fn_sub_553730_00553730(p3fes::EEContext&);
void fn_sub_553788_00553788(p3fes::EEContext&);
void fn_sub_5537E0_005537e0(p3fes::EEContext&);
void fn_sub_553838_00553838(p3fes::EEContext&);
void fn_sub_554008_00554008(p3fes::EEContext&);
void fn_sub_554048_00554048(p3fes::EEContext&);
void fn_sub_5545D8_005545d8(p3fes::EEContext&);
void fn_sub_554678_00554678(p3fes::EEContext&);
void fn_sub_5546F0_005546f0(p3fes::EEContext&);
void fn_sub_554708_00554708(p3fes::EEContext&);
void fn_sub_554778_00554778(p3fes::EEContext&);
void fn_sub_5547C8_005547c8(p3fes::EEContext&);
void fn_sub_554820_00554820(p3fes::EEContext&);
void fn_sub_5548D0_005548d0(p3fes::EEContext&);
void fn_sub_554900_00554900(p3fes::EEContext&);
void fn_sub_554940_00554940(p3fes::EEContext&);
void fn_sub_554948_00554948(p3fes::EEContext&);
void fn_sub_554950_00554950(p3fes::EEContext&);
void fn_sub_554960_00554960(p3fes::EEContext&);
void fn_sub_554968_00554968(p3fes::EEContext&);
void fn_sub_554970_00554970(p3fes::EEContext&);
void fn_sub_554980_00554980(p3fes::EEContext&);
void fn_sub_554990_00554990(p3fes::EEContext&);
void fn_sub_554A98_00554a98(p3fes::EEContext&);
void fn_sub_554AE8_00554ae8(p3fes::EEContext&);
void fn_sub_554EA0_00554ea0(p3fes::EEContext&);
void fn_sub_554EF0_00554ef0(p3fes::EEContext&);
void fn_sub_554FD0_00554fd0(p3fes::EEContext&);
void fn_sub_555120_00555120(p3fes::EEContext&);
void fn_sub_555470_00555470(p3fes::EEContext&);
void fn_sub_555738_00555738(p3fes::EEContext&);
void fn_sub_555788_00555788(p3fes::EEContext&);
void fn_sub_557AE0_00557ae0(p3fes::EEContext&);
void fn_sub_557C70_00557c70(p3fes::EEContext&);
void fn_sub_557D20_00557d20(p3fes::EEContext&);
void fn_sub_557D80_00557d80(p3fes::EEContext&);
void fn_sub_558320_00558320(p3fes::EEContext&);
void fn_sub_558610_00558610(p3fes::EEContext&);
void fn_sub_5587A8_005587a8(p3fes::EEContext&);
void fn_sub_558848_00558848(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_5589B8_005589b8(p3fes::EEContext&);
void fn_sub_558B68_00558b68(p3fes::EEContext&);
void fn_sub_558C20_00558c20(p3fes::EEContext&);
void fn_sub_558C98_00558c98(p3fes::EEContext&);
void fn_sub_558D00_00558d00(p3fes::EEContext&);
void fn_sub_558D58_00558d58(p3fes::EEContext&);
void fn_sub_559458_00559458(p3fes::EEContext&);
void fn_sub_559648_00559648(p3fes::EEContext&);
void fn_sub_559660_00559660(p3fes::EEContext&);
void fn_sub_559718_00559718(p3fes::EEContext&);
void fn_sub_5598B0_005598b0(p3fes::EEContext&);
void fn_sub_55B0F8_0055b0f8(p3fes::EEContext&);
void fn_sub_55B480_0055b480(p3fes::EEContext&);
void fn_sub_55B5C8_0055b5c8(p3fes::EEContext&);
void fn_sub_55B798_0055b798(p3fes::EEContext&);
void fn_sub_55B7C8_0055b7c8(p3fes::EEContext&);
void fn_sub_55B7F8_0055b7f8(p3fes::EEContext&);
void fn_sub_55B8B0_0055b8b0(p3fes::EEContext&);
void fn_sub_55B910_0055b910(p3fes::EEContext&);
void fn_sub_55BA68_0055ba68(p3fes::EEContext&);
void fn_sub_55BCE8_0055bce8(p3fes::EEContext&);
void fn_sub_55BD70_0055bd70(p3fes::EEContext&);
void fn_sub_55BFE0_0055bfe0(p3fes::EEContext&);
void fn_sub_55C078_0055c078(p3fes::EEContext&);
void fn_sub_55C0B0_0055c0b0(p3fes::EEContext&);
void fn_sub_55C370_0055c370(p3fes::EEContext&);
void fn_sub_55C378_0055c378(p3fes::EEContext&);
void fn_sub_55C3C8_0055c3c8(p3fes::EEContext&);
void fn_sub_55C3E0_0055c3e0(p3fes::EEContext&);
void fn_sub_55C400_0055c400(p3fes::EEContext&);
void fn_sub_55C430_0055c430(p3fes::EEContext&);
void fn_sub_55C450_0055c450(p3fes::EEContext&);
void fn_sub_55C480_0055c480(p3fes::EEContext&);
void fn_sub_55C548_0055c548(p3fes::EEContext&);
void fn_sub_55C5B8_0055c5b8(p3fes::EEContext&);
void fn_sub_55C610_0055c610(p3fes::EEContext&);
void fn_sub_55C728_0055c728(p3fes::EEContext&);
void fn_sub_55C740_0055c740(p3fes::EEContext&);
void fn_sub_55C798_0055c798(p3fes::EEContext&);
void fn_sub_55C830_0055c830(p3fes::EEContext&);
void fn_sub_55CB30_0055cb30(p3fes::EEContext&);
void fn_sub_55CCE8_0055cce8(p3fes::EEContext&);
void fn_sub_55CE18_0055ce18(p3fes::EEContext&);
void fn_sub_55CEE0_0055cee0(p3fes::EEContext&);
void fn_sub_55CF08_0055cf08(p3fes::EEContext&);
void fn_sub_55D108_0055d108(p3fes::EEContext&);
void fn_sub_55D198_0055d198(p3fes::EEContext&);
void fn_sub_55D400_0055d400(p3fes::EEContext&);
void fn_sub_55D428_0055d428(p3fes::EEContext&);
void fn_sub_55D7F0_0055d7f0(p3fes::EEContext&);
void fn_sub_55D880_0055d880(p3fes::EEContext&);
void fn_sub_55D918_0055d918(p3fes::EEContext&);
void fn_sub_55D9B0_0055d9b0(p3fes::EEContext&);
void fn_sub_55DAB0_0055dab0(p3fes::EEContext&);
void fn_sub_55DB20_0055db20(p3fes::EEContext&);
void fn_sub_55DBE8_0055dbe8(p3fes::EEContext&);
void fn_sub_55DDC8_0055ddc8(p3fes::EEContext&);
void fn_sub_55DEF0_0055def0(p3fes::EEContext&);
void fn_sub_55DFB8_0055dfb8(p3fes::EEContext&);
void fn_sub_55E190_0055e190(p3fes::EEContext&);
void fn_sub_55E1A8_0055e1a8(p3fes::EEContext&);
void fn_sub_55E1D8_0055e1d8(p3fes::EEContext&);
void fn_sub_55E208_0055e208(p3fes::EEContext&);
void fn_sub_55E318_0055e318(p3fes::EEContext&);
void fn_sub_55E408_0055e408(p3fes::EEContext&);
void fn_sub_55E800_0055e800(p3fes::EEContext&);
void fn_sub_55EA80_0055ea80(p3fes::EEContext&);
void fn_sub_55EA98_0055ea98(p3fes::EEContext&);
void fn_sub_55EAB0_0055eab0(p3fes::EEContext&);
void fn_sub_55EAF0_0055eaf0(p3fes::EEContext&);
void fn_sub_55EB08_0055eb08(p3fes::EEContext&);
void fn_sub_55EB38_0055eb38(p3fes::EEContext&);
void fn_sub_55EB68_0055eb68(p3fes::EEContext&);
void fn_sub_55EBA8_0055eba8(p3fes::EEContext&);
void fn_sub_55EBD8_0055ebd8(p3fes::EEContext&);
void fn_sub_55EBF0_0055ebf0(p3fes::EEContext&);
void fn_sub_55EC38_0055ec38(p3fes::EEContext&);
void fn_sub_55ED38_0055ed38(p3fes::EEContext&);
void fn_sub_55ED68_0055ed68(p3fes::EEContext&);
void fn_sub_55ED88_0055ed88(p3fes::EEContext&);
void fn_sub_55EDB8_0055edb8(p3fes::EEContext&);
void fn_sub_55EDF8_0055edf8(p3fes::EEContext&);
void fn_sub_55EE58_0055ee58(p3fes::EEContext&);
void fn_sub_55F028_0055f028(p3fes::EEContext&);
void fn_sub_55F1C8_0055f1c8(p3fes::EEContext&);
void fn_sub_55F218_0055f218(p3fes::EEContext&);
void fn_sub_55F2C8_0055f2c8(p3fes::EEContext&);
void fn_sub_55F308_0055f308(p3fes::EEContext&);
void fn_sub_55F390_0055f390(p3fes::EEContext&);
void fn_sub_55F4C8_0055f4c8(p3fes::EEContext&);
void fn_sub_55F598_0055f598(p3fes::EEContext&);
void fn_sub_55F608_0055f608(p3fes::EEContext&);
void fn_sub_55F620_0055f620(p3fes::EEContext&);
void fn_sub_55F658_0055f658(p3fes::EEContext&);
void fn_sub_55F670_0055f670(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_5649A8_005649a8(p3fes::EEContext&);
void fn_sub_564A20_00564a20(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs11;  // the record layouts of libs11.h

// 0x00550808 sub_550808 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// PL2 down-mix window: 32 s16 outputs, each the 32-tap dot product of the coefficient stream $a1 (read in order) and
// the circular history $a0 (strides 96 / 32 halves, rewound once by 992 or 928 halves); the sum >> 11 saturated to
// s16 into $a2[i]. The six variants differ only in the tap where the history rewinds.
void sub_550808(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550808
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550828
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, -1856);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x005509c0
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x005509d0
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x005509b4
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x005509d4
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005509e4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005509F8 sub_5509F8 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// PL2 down-mix window: 32 s16 outputs, each the 32-tap dot product of the coefficient stream $a1 (read in order) and
// the circular history $a0 (strides 96 / 32 halves, rewound once by 992 or 928 halves); the sum >> 11 saturated to
// s16 into $a2[i]. The six variants differ only in the tap where the history rewinds.
void sub_5509F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x005509f8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550a18
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, -1984);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00550bb0
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00550bc0
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00550ba4
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00550bc4
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550bd4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00550BE8 sub_550BE8 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// PL2 down-mix window: 32 s16 outputs, each the 32-tap dot product of the coefficient stream $a1 (read in order) and
// the circular history $a0 (strides 96 / 32 halves, rewound once by 992 or 928 halves); the sum >> 11 saturated to
// s16 into $a2[i]. The six variants differ only in the tap where the history rewinds.
void sub_550BE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550be8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550c08
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, -1856);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00550da0
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00550db0
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00550d94
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00550db4
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550dc4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00550DD8 sub_550DD8 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// PL2 down-mix window: 32 s16 outputs, each the 32-tap dot product of the coefficient stream $a1 (read in order) and
// the circular history $a0 (strides 96 / 32 halves, rewound once by 992 or 928 halves); the sum >> 11 saturated to
// s16 into $a2[i]. The six variants differ only in the tap where the history rewinds.
void sub_550DD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550dd8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550df8
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, -1984);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00550f90
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00550fa0
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00550f84
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00550fa4
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550fb4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00550FC8 sub_550FC8 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// PL2 down-mix window: 32 s16 outputs, each the 32-tap dot product of the coefficient stream $a1 (read in order) and
// the circular history $a0 (strides 96 / 32 halves, rewound once by 992 or 928 halves); the sum >> 11 saturated to
// s16 into $a2[i]. The six variants differ only in the tap where the history rewinds.
void sub_550FC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x00550fc8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x00550fe8
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, -1856);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00551180
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00551190
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00551174
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00551194
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005511a4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005511B8 sub_5511B8 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// PL2 down-mix window: 32 s16 outputs, each the 32-tap dot product of the coefficient stream $a1 (read in order) and
// the circular history $a0 (strides 96 / 32 halves, rewound once by 992 or 928 halves); the sum >> 11 saturated to
// s16 into $a2[i]. The six variants differ only in the tap where the history rewinds.
void sub_5511B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x005511b8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t8 = a1;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 32;
    for (;;) {
        // 0x005511d8
        charge(ctx, 99);
        v0 = s1;
        lh(a3, t8, 0);
        lh(a0, v0, 0);
        s1 = addiu(v0, 2);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        mult(t9, a3, a0);
        lh(a0, v0, 0);
        lh(a2, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult1(a1, a1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, -1984);
        mult(a2, a2, a0);
        lh(a0, v0, 0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(a3, a3, v1);
        lh(t3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        mult(t0, t0, a0);
        lh(a0, v0, 0);
        lh(t5, t8, 0);
        t8 = addiu(t8, 2);
        v0 = addiu(v0, 192);
        mult(t3, t3, v1);
        t9 = addu(t9, a1);
        lh(t6, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t5, t5, a0);
        t9 = addu(t9, a2);
        lh(t7, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t6, t6, v1);
        t9 = addu(t9, a3);
        lh(t4, t8, 0);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t8 = addiu(t8, 2);
        mult(t7, t7, a0);
        t9 = addu(t9, t0);
        lh(t2, t8, 0);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t8 = addiu(t8, 2);
        mult(t4, t4, v1);
        lh(t1, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t3);
        mult(t2, t2, a0);
        lh(t0, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        v0 = addiu(v0, 192);
        t9 = addu(t9, t5);
        mult(t1, t1, v1);
        lh(a3, t8, 0);
        t8 = addiu(t8, 2);
        lh(v1, v0, 0);
        v0 = addiu(v0, 64);
        t9 = addu(t9, t6);
        mult(t0, t0, a0);
        lh(a1, t8, 0);
        t8 = addiu(t8, 2);
        lh(a0, v0, 0);
        t9 = addu(t9, t7);
        mult(a3, a3, v1);
        lh(v1, t8, 0);
        lh(a2, v0, 192);
        v0 = 0x3FF0000;
        t9 = addu(t9, t4);
        mult(a1, a1, a0);
        t9 = addu(t9, t2);
        mult(v1, v1, a2);
        t9 = addu(t9, t1);
        v0 = v0 | 0xF800;
        t9 = addu(t9, t0);
        t9 = addu(t9, a3);
        t9 = addu(t9, a1);
        t9 = addu(t9, v1);
        v0 = slt(v0, t9);
        t8 = addiu(t8, 2);
        if (v0 == 0) {
            // 0x00551370
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00551380
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00551364
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00551384
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00551394
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00551980 sub_551980 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_551980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00551980
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00551988 sub_551988 -- 8 bytes; leaf frame (no stack)
// Returns $a1 - $a0 (32-bit).
void sub_551988(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00551988
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = subu(a1, a0);
}

// 0x00552000 sub_552000 -- 8 bytes; leaf frame (no stack)
// Returns the signed byte at $a0 + 6.
void sub_552000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00552000
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 6);
}

// 0x00552010 sub_552010 -- 16 bytes; leaf frame (no stack)
// Stores $a2 into the word table at $a0 + 20, slot $a1.
void sub_552010(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00552010
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 2);
    a1 = addu(a1, a0);
    sw(a2, a1, 20);
}

// 0x00552020 sub_552020 -- 8 bytes; leaf frame (no stack)
// Stores $a1 at $a0 + 44.
void sub_552020(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00552020
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 44);
}

// 0x005523F8 sub_5523F8 -- 104 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Walks the 16 handle pointers at 0x7986F0 (last to first) and serves each live one whose byte +4 is 1 through
// sub_5523B8.
void sub_5523F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005523f8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = 15;
    sd(s1, sp, 0x8);
    s1 = addiu(v0, -30992);  // &0x7986F0
    sd(s2, sp, 0x10);
    s2 = 1;
    lw(a0, s1, 0);  // 0x7986F0
    for (;;) {
        // 0x00552420
        charge(ctx, 2);
        s1 = addiu(s1, 4);
        if (a0 != 0) {
            // 0x00552428
            charge(ctx, 3);
            lb(v0, a0, 4);
            if (v0 == s2) {
                // 0x00552434
                charge(ctx, 2);
                jal(ctx, 0x552434u, gen::fn_sub_5523B8_005523b8);
                goto L_0055243c;
            }
            s0 = addiu(s0, -1);
            goto L_00552440;
        }
    L_0055243c:
        charge(ctx, 1);
        s0 = addiu(s0, -1);
    L_00552440:
        charge(ctx, 2);
        if (i64(s0) < 0) {
            break;
        }
        lw(a0, s1, 0);
        backedge(ctx);
    }
    // 0x00552448
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00552478 sub_552478 -- 8 bytes; leaf frame (no stack)
// Returns the word at $a0 + 40.
void sub_552478(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00552478
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 40);
}

// 0x00552494 sub_552494 -- 8 bytes; leaf frame (no stack)
// Stores $a1 at $a0 + 64.
void sub_552494(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00552494
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 64);
}

// 0x005524A8 sub_5524A8 -- 8 bytes; leaf frame (no stack)
// Returns the word at $a0 + 48.
void sub_5524A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005524a8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 48);
}

// 0x005524B8 sub_5524B8 -- 8 bytes; leaf frame (no stack)
// Returns the word at $a0 + 52.
void sub_5524B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005524b8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 52);
}

// 0x005524C8 sub_5524C8 -- 8 bytes; leaf frame (no stack)
// Returns the word at $a0 + 56.
void sub_5524C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005524c8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 56);
}

// 0x005524D0 sub_5524D0 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_5524D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005524d0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005524D8 sub_5524D8 -- 48 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stream info of the handle *$a0: the word +492 when the header-valid byte +421 is set, else 0 (shares its tail with
// sub_54E7A0).
void sub_5524D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005524d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e7a0
    charge(ctx, 3);
    lb(v1, a0, 421);
    v0 = 0;
    if (v1 != 0) {
        // 0x0054e7ac
        charge(ctx, 1);
        lw(v0, a0, 492);
    }
    // 0x0054e7b0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005524F0 sub_5524F0 -- 48 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stream info of the handle *$a0: the word +488 when the header-valid byte +421 is set, else 0 (shares its tail with
// sub_54E7B8).
void sub_5524F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005524f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e7b8
    charge(ctx, 3);
    lb(v1, a0, 421);
    v0 = 0;
    if (v1 != 0) {
        // 0x0054e7c4
        charge(ctx, 1);
        lw(v0, a0, 488);
    }
    // 0x0054e7c8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00552538 sub_552538 -- 24 bytes; frame 0x10: ra sp+0x0
// A six-instruction head that continues in the shared tail at 0x54E7F0 (kept block for block).
void sub_552538(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552538
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54E7D8_0054e7d8_at_0054e7f0(ctx);  // tail call
}

// 0x00552550 sub_552550 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552550
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552558 sub_552558 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552558(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552558
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552560 sub_552560 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552560
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552568 sub_552568 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552568(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552568
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552570 sub_552570 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552570
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552578 sub_552578 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552578(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552578
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552580 sub_552580 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a CRI library stub kept for its table slot).
void sub_552580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00552580
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00552588 sub_552588 -- 56 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Header field of *$a0: the s16 +514 when +421 and the half +512 are set, else 0.
void sub_552588(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552588
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e8a0
    charge(ctx, 3);
    lb(v1, a0, 421);
    v0 = 0;
    if (v1 != 0) {
        // 0x0054e8ac
        charge(ctx, 3);
        lh(v1, a0, 512);
        if (v1 != 0) {
            lh(v0, a0, 514);
        }
    }
    // 0x0054e8b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005525A0 sub_5525A0 -- 56 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Header field of *$a0: the s8 +517 when +421 and the byte +516 are set, else 0.
void sub_5525A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005525a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e8c0
    charge(ctx, 3);
    lb(v1, a0, 421);
    v0 = 0;
    if (v1 != 0) {
        // 0x0054e8cc
        charge(ctx, 3);
        lb(v1, a0, 516);
        if (v1 != 0) {
            lb(v0, a0, 517);
        }
    }
    // 0x0054e8d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005525B8 sub_5525B8 -- 96 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Two header fields of *$a0 into out-parameters: *$a1 = s8 +519 (when +518 > 0, else 0), *$a2 = s8 +521 (when +520 >
// 0, else -45).
void sub_5525B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005525b8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e8e0
    charge(ctx, 6);
    v0 = si(-45);
    sw(zero, a1, 0);
    sw(v0, a2, 0);
    lb(v0, a0, 421);
    if (v0 != 0) {
        // 0x0054e8f8
        charge(ctx, 3);
        lb(v0, a0, 518);
        if (i64(v0) <= 0) {
            lb(v0, a0, 520);
        } else {
            // 0x0054e904
            charge(ctx, 3);
            lb(v0, a0, 519);
            sw(v0, a1, 0);
            lb(v0, a0, 520);
        }
        // 0x0054e910
        charge(ctx, 2);
        if (i64(v0) > 0) {
            // 0x0054e918
            charge(ctx, 2);
            lb(v0, a0, 521);
            sw(v0, a2, 0);
        }
    }
    // 0x0054e920 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005525D0 sub_5525D0 -- 140 bytes, 3 chunks; frame 0x10: ra sp+0x0
// Channel pan of *$a0 for channel $a1: (s8 +523 or +535) >> 3, with the defaults 0 / -15 / 15 when the byte before it
// is not positive (stereo when +488 is 2).
void sub_5525D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005525d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054e928
    charge(ctx, 3);
    lb(v1, a0, 421);
    v0 = 0;
    if (v1 == 0) {
        // 0x0054e998 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0054e934
    charge(ctx, 4);
    lw(v1, a0, 488);
    v0 = 2;
    if (v1 != v0) {
        lb(v0, a0, 522);
        // 0x0054e980
        charge(ctx, 2);
        if (i64(v0) <= 0) {
            v0 = 0;
            // 0x0054e998 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0054e988
        charge(ctx, 1);
        lbu(v0, a0, 523);
        // 0x0054e98c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = sll(v0, 24);
        v0 = sra(v0, 27);
        return;
    }
    // 0x0054e944
    charge(ctx, 3);
    v0 = 1;
    if (a1 != v0) {
        lb(v0, a0, 522);
        // 0x0054e970
        charge(ctx, 2);
        if (i64(v0) <= 0) {
            // 0x0054e978
            charge(ctx, 2);
            v0 = si(-15);
            return;
        }
        lbu(v0, a0, 523);
        // 0x0054e98c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = sll(v0, 24);
        v0 = sra(v0, 27);
        return;
    }
    // 0x0054e950
    charge(ctx, 3);
    lb(v0, a0, 534);
    if (i64(v0) <= 0) {
        // 0x0054e968
        charge(ctx, 2);
        v0 = 15;
        return;
    }
    // 0x0054e95c
    charge(ctx, 2);
    lbu(v0, a0, 535);
    // 0x0054e98c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = sll(v0, 24);
    v0 = sra(v0, 27);
}

// 0x005525E8 sub_5525E8 -- 24 bytes; frame 0x10: ra sp+0x0
// Tail call: sub_54E838(*$a0).
void sub_5525E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005525e8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54E838_0054e838(ctx);  // tail call
}

// 0x00552688 sub_552688 -- 40 bytes; frame 0x10: ra sp+0x0
// Calls sub_552658(0) and sub_552680(0); returns 0.
void sub_552688(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552688
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x552690u, gen::fn_sub_552658_00552658);
    a0 = 0;
    jal(ctx, 0x552698u, gen::fn_sub_552680_00552680);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00552D08 sub_552D08 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// Walks the 4 records of 620 bytes at 0x799978 and calls sub_552BD0 on each whose first byte is 1.
void sub_552D08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552d08
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -26248);  // &0x799978
    sd(s1, sp, 0x8);
    s1 = 3;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00552d30
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00552d3c
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x552D3Cu, gen::fn_sub_552BD0_00552bd0);
            s1 = addiu(s1, -1);
        }
        // 0x00552d48
        charge(ctx, 2);
        s0 = addiu(s0, 620);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00552d50
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00552FA0 sub_552FA0 -- 132 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// AIX player: attach the data source $a1 to the handle $a0 (stop, then under the lock: +144 = $a1, the parser's +28,
// state +476 = 3, status +1 = 1). Null -> 'E2003050206'.
void sub_552FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552fa0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x10);
    if (s1 != 0) {
        // 0x00552fbc
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00552fc4;
        }
        // 0x00552fe0
        charge(ctx, 17);
        jal(ctx, 0x552FE0u, gen::fn_sub_5530D0_005530d0);
        jal(ctx, 0x552FE8u, gen::fn_sub_5546F0_005546f0);
        sw(s0, s1, aixp::kSource);
        a1 = s0;
        link(ctx, 0x552FF8u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, aixp::kParser);
        call(ctx, gen::fn_sub_554948_00554948);
        v0 = 3;
        v1 = 1;
        sw(v0, s1, aixp::kSrvState);
        sb(v1, s1, aixp::kStat);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_554708_00554708(ctx);  // tail call
        return;
    }
L_00552fc4:
    charge(ctx, 7);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 13080);  // "E2003050206 : NULL pointer is specified."
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_552630_00552630(ctx);  // tail call
}

// 0x005531B8 sub_5531B8 -- 116 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// AIX player: two counters of the handle's sub-player (+12) through sub_548AE8 into the optional out-parameters $a1 /
// $a2. Null -> 'E2004052101'.
void sub_5531B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005531b8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(ra, sp, 0x20);
    a1 = sp;
    a2 = addiu(sp, 0x4);
    if (a0 != 0) {
        // 0x005531f0
        charge(ctx, 6);
        lw(a0, a0, aixp::kSubPly);
        sw(zero, sp, 0x0);
        link(ctx, 0x5531F8u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x4);
        call(ctx, gen::fn_sub_548AE8_00548ae8);
        lw(v0, sp, 0x0);
        if (s0 != 0) {
            // 0x00553208
            charge(ctx, 1);
            sw(v0, s0, 0);
        }
        // 0x0055320c
        charge(ctx, 2);
        lw(v0, sp, 0x4);
        if (s1 != 0) {
            // 0x00553214
            charge(ctx, 1);
            sw(v0, s1, 0);
        }
        // 0x00553218
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x005531dc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13272);  // "E2004052101 : NULL pointer is specified."
        jal(ctx, 0x5531E0u, gen::fn_sub_552630_00552630);
        ld(s0, sp, 0x10);
    }
    // 0x0055321c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00553310 sub_553310 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIX player: store the float $f12 at +480 and, under the lock, re-apply it (sub_553288) when the status is 2.
void sub_553310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00553310
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x553320u);  // $ra first: the delay slot below depends on it
    swc1(f12, s0, aixp::kFloat480);
    call(ctx, gen::fn_sub_5546F0_005546f0);
    a0 = s0;
    jal(ctx, 0x553328u, gen::fn_sub_553188_00553188);
    v1 = 2;
    a0 = s0;
    if (v0 == v1) {
        // 0x0055333c
        charge(ctx, 2);
        jal(ctx, 0x55333Cu, gen::fn_sub_553288_00553288);
    }
    // 0x00553344
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00553358 sub_553358 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, f20 sp+0x18, ra sp+0x10
// AIX player: play time as a float -- the source's (+144) vtable slot 36 count divided by sub_553838's rate; 0.0 when
// either is missing.
void sub_553358(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x00553358
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    swc1(f20, sp, 0x18);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x55336Cu, gen::fn_sub_553838_00553838);
    mtc1(zero, f20);
    s1 = v0;
    mov_s(f0, f20);
    if (s1 != 0) {
        // 0x00553384
        charge(ctx, 3);
        lw(v1, s0, aixp::kSource);
        a0 = v1;
        if (v1 != 0) {
            // 0x00553390
            charge(ctx, 11);
            lw(v1, v1, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x553398u, v0.u());
            mtc1(s1, f1);
            cvt_s_w(f1, f1);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f0, f1);
        }
    }
    // 0x005533bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00553408 sub_553408 -- 48 bytes; frame 0x10: ra sp+0x0
// AIX player: the byte +433 = $a1. Null -> 'E2003050212'.
void sub_553408(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553408
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00553428
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sb(a1, a0, aixp::kByte433);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00553414
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 13472);  // "E2003050212 : NULL pointer is specified."
    sp = addiu(sp, 0x10);
    gen::fn_sub_552630_00552630(ctx);  // tail call
}

// 0x00553438 sub_553438 -- 48 bytes; frame 0x10: ra sp+0x0
// AIX player: the word +448 = $a1. Null -> 'E2003050213'.
void sub_553438(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553438
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00553458
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sw(a1, a0, aixp::kWord448);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00553444
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 13520);  // "E2003050213 : NULL pointer is specified."
    sp = addiu(sp, 0x10);
    gen::fn_sub_552630_00552630(ctx);  // tail call
}

// 0x00553468 sub_553468 -- 48 bytes; frame 0x10: ra sp+0x0
// AIX player: returns the word +448. Null -> 'E2003050214' and -1.
void sub_553468(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553468
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00553488
        charge(ctx, 1);
        lw(v0, a0, aixp::kWord448);
    } else {
        // 0x00553474
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13568);  // "E2003050214 : NULL pointer is specified."
        jal(ctx, 0x553478u, gen::fn_sub_552630_00552630);
        v0 = si(-1);
    }
    // 0x0055348c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00553498 sub_553498 -- 116 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AIX player: under the lock, the loop start +452 = $a1 and the loop end +456 = $a1 + $a2. Null -> 'E2003050215'.
void sub_553498(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553498
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 == 0) {
        // 0x005534bc
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 13616);  // "E2003050215 : NULL pointer is specified."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_552630_00552630(ctx);  // tail call
        return;
    }
    // 0x005534e0
    charge(ctx, 11);
    jal(ctx, 0x5534E0u, gen::fn_sub_5546F0_005546f0);
    sw(s1, s0, aixp::kRangeStart);
    v0 = addu(s1, s2);
    ld(s1, sp, 0x8);
    sw(v0, s0, aixp::kRangeEnd);
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00553510 sub_553510 -- 80 bytes; frame 0x10: ra sp+0x0
// AIX player: the loop start (+452) and length (+456 - +452) into the optional out-parameters. Null -> 'E2003050216'.
void sub_553510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553510
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055351c
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 13664);  // "E2003050216 : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_552630_00552630(ctx);  // tail call
        return;
    }
    // 0x00553530
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x00553538
        charge(ctx, 2);
        lw(v0, a0, aixp::kRangeStart);
        sw(v0, a1, 0);
    }
    // 0x00553540
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (a2 != 0) {
        // 0x00553548
        charge(ctx, 4);
        lw(v1, a0, aixp::kRangeStart);
        lw(v0, a0, aixp::kRangeEnd);
        v0 = subu(v0, v1);
        sw(v0, a2, 0);
    }
    // 0x00553558 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00553560 sub_553560 -- 48 bytes; frame 0x10: ra sp+0x0
// AIX player: returns the data source +144. Null -> 'E2003050221' and 0.
void sub_553560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553560
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00553580
        charge(ctx, 1);
        lw(v0, a0, aixp::kSource);
    } else {
        // 0x0055356c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13712);  // "E2003050221 : NULL pointer is specified."
        jal(ctx, 0x553570u, gen::fn_sub_552630_00552630);
        v0 = 0;
    }
    // 0x00553584 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00553688 nullsub_143 -- 8 bytes; leaf frame (no stack)
// Empty.
void nullsub_143(EEContext& ctx) {
    using namespace hg;
    // 0x00553688
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00553690 sub_553690 -- 212 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIXP_GetNumSmpl (the error string's name): the parser's sample count -- the sum of the track sample words (+700,
// stride 16) for a parsed header, or sub_548EB8 of the sub-player.
void sub_553690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00553690
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005536a4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13872);  // "E2003052000 AIXP_GetNumSmpl: NULL pointer is specified."
        jal(ctx, 0x5536A8u, gen::fn_sub_552630_00552630);
        v0 = si(-1);
        goto L_00553720;
    }
    // 0x005536b8
    charge(ctx, 5);
    lbu(v0, s0, aixp::kStat);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        v0 = 0;
    L_00553720:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00553724 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005536cc
    charge(ctx, 4);
    link(ctx, 0x5536CCu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, aixp::kParser);
    call(ctx, gen::fn_sub_554A98_00554a98);
    v1 = 1;
    if (v0 != 0) {
        // 0x005536dc
        charge(ctx, 2);
        cc = v0 == v1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (cc) {
            // 0x00553708
            charge(ctx, 5);
            lw(a0, s0, aixp::kSubPly);
            ld(ra, sp, 0x8);
            ld(s0, sp, 0x0);
            sp = addiu(sp, 0x10);
            gen::fn_sub_548EB8_00548eb8(ctx);  // tail call
            return;
        }
        // 0x005536e4
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        // 0x00553724 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005536f0
    charge(ctx, 5);
    lw(a0, s0, aixp::kParser);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00554a60
    charge(ctx, 3);
    lw(v1, a0, 688);
    a1 = 0;
    if (i64(v1) > 0) {
        // 0x00554a6c
        charge(ctx, 1);
        a0 = addiu(a0, 700);
        for (;;) {
            // 0x00554a70
            charge(ctx, 7);
            lw(v0, a0, 0);
            a0 = addiu(a0, 16);
            v1 = addiu(v1, -1);
            a1 = addu(a1, v0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00554a8c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a1;
}

// 0x00553730 sub_553730 -- 84 bytes; frame 0x10: ra sp+0x0
// AIXP_GetNumTrack (the error string's name): sub_554968 of the parser while the status +1 is 1..3, else 0; null ->
// -1.
void sub_553730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553730
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055373c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13928);  // "E2003052001 AIXP_GetNumTrack: NULL pointer is specified."
        jal(ctx, 0x553740u, gen::fn_sub_552630_00552630);
        v0 = si(-1);
        // 0x00553778 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00553750
    charge(ctx, 5);
    lbu(v0, a0, aixp::kStat);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        v0 = 0;
        // 0x00553778 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00553764
    charge(ctx, 4);
    lw(a0, a0, aixp::kParser);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554968_00554968(ctx);  // tail call
}

// 0x00553788 sub_553788 -- 84 bytes; frame 0x10: ra sp+0x0
// AIXP_GetNumPhrase (the error string's name): sub_554990 of the parser while the status +1 is 1..3, else 0; null ->
// -1.
void sub_553788(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553788
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00553794
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13992);  // "E2003052002 AIXP_GetNumPhrase: NULL pointer is specified."
        jal(ctx, 0x553798u, gen::fn_sub_552630_00552630);
        v0 = si(-1);
        // 0x005537d0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005537a8
    charge(ctx, 5);
    lbu(v0, a0, aixp::kStat);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        v0 = 0;
        // 0x005537d0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005537bc
    charge(ctx, 4);
    lw(a0, a0, aixp::kParser);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554990_00554990(ctx);  // tail call
}

// 0x005537E0 sub_5537E0 -- 92 bytes, 2 chunks; frame 0x10: ra sp+0x0
// AIXP_GetNumSong (the error string's name): the parser's word +6452 while the status +1 is 1..3, else 0; null -> -1.
void sub_5537E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005537e0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x005537ec
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 14056);  // "E2003052003 AIXP_GetNumSong: NULL pointer is specified."
        jal(ctx, 0x5537F0u, gen::fn_sub_552630_00552630);
        v0 = si(-1);
        // 0x00553828 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00553800
    charge(ctx, 5);
    lbu(v0, a0, aixp::kStat);
    v0 = addiu(v0, -1);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        v0 = 0;
        // 0x00553828 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00553814
    charge(ctx, 4);
    lw(a0, a0, aixp::kParser);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005549f8
    charge(ctx, 2);
    lw(v0, a0, aixparse::kNumSong);
}

// 0x00554008 sub_554008 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Under the lock: sub_554048($a0, $a1).
void sub_554008(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554008
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x55401Cu, gen::fn_sub_5546F0_005546f0);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x554028u, gen::fn_sub_554048_00554048);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x005545D8 sub_5545D8 -- 160 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// AIX: 1 when the parser state (sub_554900) is 3 and every one of the +3 track players (+12..) reports 0 or 5 from
// sub_548768; else 0.
void sub_5545D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005545d8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    link(ctx, 0x5545F4u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 4);
    call(ctx, gen::fn_sub_554900_00554900);
    v1 = 3;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00554608
        charge(ctx, 4);
        s2 = 0;
        s3 = 5;
        s1 = addiu(s0, 12);
        for (;;) {
            // 0x00554618
            charge(ctx, 4);
            lb(v0, s0, 3);
            v0 = slt(s2, v0);
            lbu(v1, s0, 3);
            if (v0 == 0) {
                break;
            }
            // 0x00554628
            charge(ctx, 5);
            lw(a0, s1, 0);
            s1 = addiu(s1, 4);
            jal(ctx, 0x55462Cu, gen::fn_sub_548768_00548768);
            if (v0 == s3) {
                s2 = addiu(s2, 1);
                backedge(ctx);
                continue;
            }
            // 0x0055463c
            charge(ctx, 2);
            if (v0 != 0) {
                goto L_00554644_5;
            }
            s2 = addiu(s2, 1);
            backedge(ctx);
        }
    L_00554648:
        charge(ctx, 4);
        v1 = sll(v1, 24);
        v1 = sra(v1, 24);
        v0 = 1;
        if (s2 != v1) {
            // 0x00554658
            charge(ctx, 1);
            v0 = 0;
        }
    }
    // 0x0055465c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_00554644_5:
    charge(ctx, 1);
    lbu(v1, s0, 3);
    goto L_00554648;
}

// 0x00554678 sub_554678 -- 116 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// AIX: calls sub_54AF38(track, $a1) on each of the +3 track players listed from +12.
void sub_554678(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554678
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    lb(v0, s1, 3);
    s3 = a1;
    if (i64(v0) > 0) {
        // 0x005546a4
        charge(ctx, 3);
        s0 = addiu(s1, 12);
        lw(a0, s0, 0);
        for (;;) {
            // 0x005546b0
            charge(ctx, 8);
            s0 = addiu(s0, 4);
            a1 = s3;
            s2 = addiu(s2, 1);
            jal(ctx, 0x5546B8u, gen::fn_sub_54AF38_0054af38);
            lb(v0, s1, 3);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x005546d0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00554778 sub_554778 -- 76 bytes; frame 0x10: ra sp+0x0
// AIX parser module finish: under the lock, drop the init count 0x79A328 and clear the 4 parser records (25968 bytes
// at 0x79A330) when it reaches 0.
void sub_554778(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554778
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x554780u, gen::fn_sub_5546F0_005546f0);
    v1 = 0x7A0000;
    a0 = 0x7A0000;
    v1 = addiu(v1, -23768);  // &0x79A328
    a0 = addiu(a0, -23760);  // &0x79A330
    lw(v0, v1, 0);  // 0x79A328
    a1 = 0;
    a2 = 25968;
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x79A328
    if (v0 == 0) {
        // 0x005547b0
        charge(ctx, 2);
        jal(ctx, 0x5547B0u, gen::fn_memset_00521408);
    }
    // 0x005547b8
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x005547C8 sub_5547C8 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Under the lock: sub_554820($a0, $a1, $a2) (create a parser); returns its result.
void sub_5547C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005547c8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x5547E4u, gen::fn_sub_5546F0_005546f0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x5547F4u, gen::fn_sub_554820_00554820);
    s0 = v0;
    jal(ctx, 0x5547FCu, gen::fn_sub_554708_00554708);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00554820 sub_554820 -- 172 bytes; leaf frame (no stack)
// AIX parser create: take the first free record of the 4 (6492 bytes each, 0x79A330), copy the $a0 track pointers
// from $a2, store $a1 at +28 and mark it used.
void sub_554820(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00554820
    enter(ctx, 5);  // entry check point + this block's cycles
    t0 = 0x7A0000;
    v1 = addiu(t0, -23760);  // &0x79A330
    lb(v0, v1, 0);  // 0x79A330
    a3 = 0;
    if (v0 != 0) {
        // 0x00554834
        charge(ctx, 1);
        a3 = addiu(a3, 1);
        for (;;) {
            // 0x00554838
            charge(ctx, 3);
            v0 = slti(a3, 4);
            v1 = addiu(v1, 6492);
            if (v0 != 0) {
                // 0x00554844
                charge(ctx, 6);
                lb(v0, v1, 0);
                if (v0 != 0) {
                    a3 = addiu(a3, 1);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0055485c
    charge(ctx, 3);
    v1 = 4;
    v0 = 0;
    if (a3 != v1) {
        // 0x00554868
        charge(ctx, 8);
        v0 = 6492;
        v1 = addiu(t0, -23760);
        mult(v0, a3, v0);
        t0 = 0;
        a3 = addu(v0, v1);
        sw(a1, a3, 28);
        sb(zero, a3, 1);
        if (i64(a0) > 0) {
            // 0x00554888
            charge(ctx, 2);
            a1 = addiu(a3, 32);
            for (;;) {
                // 0x00554890
                charge(ctx, 7);
                lw(v1, a2, 0);
                a2 = addiu(a2, 4);
                t0 = addiu(t0, 1);
                v0 = slt(t0, a0);
                sw(v1, a1, 0);
                a1 = addiu(a1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x005548ac
        charge(ctx, 6);
        v0 = 1;
        sb(a0, a3, 2);
        sb(zero, a3, 3);
        sb(zero, a3, 4);
        sb(v0, a3, 0);
        v0 = a3;
    }
    // 0x005548c4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005548D0 sub_5548D0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the lock: clear the first word of $a0 (when not null).
void sub_5548D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005548d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5548DCu, gen::fn_sub_5546F0_005546f0);
    if (s0 != 0) {
        sw(zero, s0, 0);
    }
    // 0x005548ec
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00554940 sub_554940 -- 8 bytes; leaf frame (no stack)
// Clears the status byte +1.
void sub_554940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00554940
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(zero, a0, 1);
}

// 0x00554950 sub_554950 -- 8 bytes; leaf frame (no stack)
// Returns the word +28.
void sub_554950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00554950
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 28);
}

// 0x00554960 sub_554960 -- 8 bytes; leaf frame (no stack)
// Stores the byte $a1 at +4.
void sub_554960(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00554960
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, 4);
}

// 0x00554970 sub_554970 -- 16 bytes; leaf frame (no stack)
// Returns the word +180 of track $a1 (stride 16).
void sub_554970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00554970
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 4);
    a1 = addu(a1, a0);
    lw(v0, a1, 180);
}

// 0x00554980 sub_554980 -- 16 bytes; leaf frame (no stack)
// Returns the signed byte +176 of track $a1 (stride 16).
void sub_554980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00554980
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = sll(a1, 4);
    a0 = addu(a0, a1);
    lb(v0, a0, 176);
}

// 0x00554EA0 sub_554EA0 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// AIX header record reset: clear 6328 bytes and set the defaults (+12 = 1, +528 = 1, +6292 = 1, +6298 = 1).
void sub_554EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554ea0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    a2 = 6328;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x554EB4u, gen::fn_memset_00521408);
    v1 = 1;
    v0 = 1;
    sh(v1, s0, 6298);
    sb(v0, s0, 12);
    sw(v1, s0, 528);
    sw(v1, s0, 6292);
    sh(zero, s0, 6296);
    sh(zero, s0, 6300);
    sh(zero, s0, 6302);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00554EF0 sub_554EF0 -- 224 bytes; frame 0x10: ra sp+0x0
// AIX chunk header: when $a1 >= 16, unpack the 16 big-endian bytes at $a0 (u32 id, u32 size, two bytes, u16, u32)
// into $a2; returns 16, else 0.
void sub_554EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554ef0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    a1 = sltiu(a1, 16);
    sd(ra, sp, 0x0);
    a3 = addiu(t0, 4);
    t1 = a2;
    v0 = 0;
    if (a1 == 0) {
        // 0x00554f10
        charge(ctx, 45);
        lbu(v1, t0, 0);
        v0 = 16;
        lbu(a0, t0, 2);
        lbu(a1, t0, 1);
        v1 = sll(v1, 24);
        lbu(a2, t0, 3);
        a0 = sll(a0, 8);
        a1 = sll(a1, 16);
        a0 = a0 | a1;
        v1 = v1 | a2;
        v1 = v1 | a0;
        sw(v1, t1, 0);
        lbu(a1, a3, 1);
        lbu(v1, a3, 0);
        lbu(a0, a3, 2);
        a1 = sll(a1, 16);
        lbu(a2, a3, 3);
        a3 = addiu(t0, 10);
        v1 = sll(v1, 24);
        a0 = sll(a0, 8);
        a0 = a0 | a1;
        v1 = v1 | a2;
        v1 = v1 | a0;
        sw(v1, t1, 4);
        lbu(a0, t0, 8);
        sb(a0, t1, 8);
        lbu(v1, t0, 9);
        sb(v1, t1, 9);
        lbu(a0, a3, 0);
        lbu(v1, a3, 1);
        a3 = addiu(t0, 12);
        a0 = sll(a0, 8);
        v1 = v1 | a0;
        sh(v1, t1, 10);
        lbu(a1, a3, 1);
        lbu(v1, a3, 0);
        lbu(a0, a3, 2);
        a1 = sll(a1, 16);
        lbu(a2, a3, 3);
        v1 = sll(v1, 24);
        a0 = sll(a0, 8);
        v1 = v1 | a2;
        a0 = a0 | a1;
        v1 = v1 | a0;
        sw(v1, t1, 12);
    }
    // 0x00554fc4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00554FD0 sub_554FD0 -- 332 bytes; frame 0x50: s0 sp+0x20, s2 sp+0x30, s3 sp+0x38, s1 sp+0x28, ra sp+0x40
// AIX parser: read the stream header from the source (+28) through its vtable, parse it (sub_554AE8) into +160 and
// consume it; a short header -> 'E2003043002', status 4.
void sub_554FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00554fd0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a1 = 1;
    sd(s0, sp, 0x20);
    a3 = sp;
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s3, sp, 0x38);
    a2 = 6144;
    sd(s1, sp, 0x28);
    s0 = addiu(s2, 160);
    sd(ra, sp, 0x40);
    lw(s1, s2, 28);
    lw(v1, s1, 0);
    lw(v0, v1, 24);
    a0 = s1;
    jalr(ctx, 0x555008u, v0.u());
    a2 = s0;
    lw(a0, sp, 0x0);
    link(ctx, 0x555018u);  // $ra first: the delay slot below depends on it
    lw(a1, sp, 0x4);
    call(ctx, gen::fn_sub_554AE8_00554ae8);
    a0 = s1;
    s3 = v0;
    v0 = si(-1);
    a1 = 1;
    a2 = sp;
    if (s3 != v0) {
        // 0x00555050
        charge(ctx, 2);
        lw(v0, sp, 0x4);
        if (s3 == 0) {
            // 0x00555058
            charge(ctx, 3);
            v0 = 1;
            sw(v0, s2, 6488);
            goto L_005550a4;
        }
        // 0x00555068
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s3 == v0) {
            // 0x005550a0
            charge(ctx, 1);
            sw(zero, s2, 6488);
        L_005550a4:
            charge(ctx, 23);
            s0 = addiu(sp, 0x10);
            a0 = sp;
            a2 = sp;
            a3 = s0;
            a1 = s3;
            jal(ctx, 0x5550B4u, gen::fn_sub_563C28_00563c28);
            lw(v1, s1, 0);
            a2 = sp;
            a0 = s1;
            lw(v0, v1, 32);
            a1 = 0;
            jalr(ctx, 0x5550CCu, v0.u());
            lw(a1, s1, 0);
            a0 = s1;
            a2 = s0;
            lw(v1, a1, 28);
            a1 = 1;
            jalr(ctx, 0x5550E4u, v1.u());
            lw(v0, s2, 8);
            v1 = 2;
            v0 = addu(v0, s3);
            sb(v1, s2, 1);
            sw(v0, s2, 8);
        } else {
            // 0x00555070
            charge(ctx, 11);
            a0 = addiu(a0, 14480);
            jal(ctx, 0x555070u, gen::fn_sub_552630_00552630);
            lw(v0, s1, 0);
            a0 = s1;
            a1 = 1;
            lw(v1, v0, 28);
            a2 = sp;
            jalr(ctx, 0x555088u, v1.u());
            v0 = 4;
            sb(v0, s2, 1);
        }
        // 0x00555100
        charge(ctx, 1);
        ld(s0, sp, 0x20);
    } else {
        // 0x00555038
        charge(ctx, 6);
        lw(v0, s1, 0);
        lw(v1, v0, 28);
        jalr(ctx, 0x555040u, v1.u());
        ld(s0, sp, 0x20);
    }
    // 0x00555104 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00555120 sub_555120 -- 844 bytes; frame 0xA0: s5 sp+0x78, fp sp+0x90, s0 sp+0x50, s1 sp+0x58, s2 sp+0x60, s3 sp+0x68, s4 sp+0x70, s6 sp+0x80, s7 sp+0x88, ra sp+0x98
// AIX parser: demultiplex up to +172 data chunks from the source into the track streams (+32..); 'AIXE' ends the
// stream; a bad track / length -> 'E2003043003' / 'E2003043004', status 4.
void sub_555120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00555120
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = si(-3);
    sd(s5, sp, 0x78);
    s5 = a0;
    sd(fp, sp, 0x90);
    fp = addiu(s5, 0x20);
    sd(s0, sp, 0x50);
    sd(s1, sp, 0x58);
    sd(s2, sp, 0x60);
    sd(s3, sp, 0x68);
    sd(s4, sp, 0x70);
    sd(s6, sp, 0x80);
    sd(s7, sp, 0x88);
    sd(ra, sp, 0x98);
    sw(v0, sp, 0x48);
    lb(a1, s5, 172);
    sw(a1, sp, 0x40);
    lw(s1, s5, 28);
    sw(zero, sp, 0x44);
    if (i64(a1) > 0) {
        // 0x00555170
        charge(ctx, 2);
        s4 = addiu(sp, 0x10);
        for (;;) {
            // 0x00555178
            charge(ctx, 12);
            lw(v1, s1, 0);
            a2 = 0x7FFF0000;
            a1 = 1;
            a0 = s1;
            lw(v0, v1, 24);
            a2 = a2 | 0xFFFF;
            a3 = s4;
            jalr(ctx, 0x555190u, v0.u());
            lw(a1, sp, 0x14);
            v0 = sltiu(a1, 16);
            lw(a0, sp, 0x10);
            if (v0 != 0) {
                goto L_005551a8;
            }
            // 0x005551c8
            charge(ctx, 4);
            a2 = sp;
            jal(ctx, 0x5551C8u, gen::fn_sub_554EF0_00554ef0);
            lw(v1, sp, 0x4);
            if (v0 == 0) {
                backedge(ctx);
                goto L_005551a8;
            }
            // 0x005551d8
            charge(ctx, 5);
            lw(v0, sp, 0x14);
            a1 = addiu(v1, 8);
            v0 = slt(v0, a1);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0x41490000;
            if (cc) {
                backedge(ctx);
                goto L_005551a8;
            }
            // 0x005551ec
            charge(ctx, 4);
            lw(v1, sp, 0x0);
            v0 = v0 | 0x5845;
            lbu(s0, sp, 0x8);
            if (v1 == v0) {
                goto L_005551fc_7;
            }
            // 0x00555278
            charge(ctx, 4);
            lb(v0, s5, 2);
            v0 = slt(s0, v0);
            s7 = sll(s0, 2);
            if (v0 == 0) {
                goto L_00555288_11;
            }
            // 0x005552b8
            charge(ctx, 10);
            v0 = addu(s7, fp);
            lw(a0, v0, 0);
            lw(v1, a0, 0);
            lw(v0, v1, 36);
            a1 = 0;
            jalr(ctx, 0x5552C8u, v0.u());
            lh(v1, sp, 0xA);
            v0 = slt(v0, v1);
            s6 = addiu(sp, 0x20);
            if (v0 != 0) {
                backedge(ctx);
                goto L_005551a8;
            }
            // 0x005552e0
            charge(ctx, 30);
            lw(a1, sp, 0x4);
            lw(v0, sp, 0xC);
            a3 = s6;
            a0 = s4;
            a1 = addiu(a1, 8);
            a2 = s4;
            link(ctx, 0x5552F8u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x48);
            call(ctx, gen::fn_sub_563C28_00563c28);
            lw(v1, s1, 0);
            a1 = 1;
            a2 = s6;
            lw(v0, v1, 28);
            a0 = s1;
            jalr(ctx, 0x555310u, v0.u());
            a0 = s4;
            a1 = 16;
            a2 = s4;
            a3 = s6;
            jal(ctx, 0x555324u, gen::fn_sub_563C28_00563c28);
            lw(v1, s1, 0);
            a2 = s4;
            a0 = s1;
            lw(v0, v1, 32);
            a1 = 0;
            jalr(ctx, 0x55533Cu, v0.u());
            lh(v1, sp, 0xA);
            lw(a2, sp, 0x24);
            v0 = slt(a2, v1);
            a0 = 0x7C0000;
            if (v0 != 0) {
                goto L_00555358_15;
            }
            // 0x00555380
            charge(ctx, 2);
            s2 = 0;
            if (i64(v1) > 0) {
                // 0x00555388
                charge(ctx, 1);
                s3 = addiu(sp, 0x30);
                for (;;) {
                    // 0x0055538c
                    charge(ctx, 25);
                    s0 = addu(s7, fp);
                    a2 = subu(a2, s2);
                    lw(a0, s0, 0);
                    a3 = s3;
                    lw(v1, a0, 0);
                    lw(v0, v1, 24);
                    a1 = 0;
                    jalr(ctx, 0x5553A4u, v0.u());
                    lw(a1, sp, 0x20);
                    lw(a0, sp, 0x30);
                    lw(a2, sp, 0x34);
                    a1 = addu(a1, s2);
                    jal(ctx, 0x5553B8u, gen::fn_memcpy_00521250);
                    lw(a0, s0, 0);
                    a1 = 1;
                    lw(v1, a0, 0);
                    lw(v0, v1, 32);
                    a2 = s3;
                    jalr(ctx, 0x5553D0u, v0.u());
                    lw(v1, sp, 0x34);
                    lh(v0, sp, 0xA);
                    s2 = addu(s2, v1);
                    v0 = slt(s2, v0);
                    lw(a2, sp, 0x24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x005553f0
            charge(ctx, 18);
            lw(v0, s1, 0);
            a2 = s6;
            a0 = s1;
            a1 = 0;
            lw(v1, v0, 32);
            lw(v0, sp, 0x44);
            v0 = addiu(v0, 1);
            jt = v1.u();  // the target, read before the delay slot
            link(ctx, 0x55540Cu);  // $ra = the return address
            sw(v0, sp, 0x44);
            call_ptr(ctx, jt);
            lw(v0, s5, 8);
            lw(v1, sp, 0x24);
            lw(a1, sp, 0x44);
            lw(a2, sp, 0x40);
            v0 = addu(v0, v1);
            v0 = addiu(v0, 16);
            a0 = slt(a1, a2);
            sw(v0, s5, 8);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
L_00555438:
    charge(ctx, 1);
    lw(v0, sp, 0x48);
    // 0x0055543c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x50);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(s6, sp, 0x80);
    ld(s7, sp, 0x88);
    ld(fp, sp, 0x90);
    ld(ra, sp, 0x98);
    sp = addiu(sp, 0xA0);
    return;
L_005551a8:
    charge(ctx, 8);
    lw(v1, s1, 0);
    a0 = s1;
    a2 = s4;
    lw(v0, v1, 28);
    a1 = 1;
    jalr(ctx, 0x5551B8u, v0.u());
    lw(v0, sp, 0x48);
    // 0x0055543c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x50);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(s6, sp, 0x80);
    ld(s7, sp, 0x88);
    ld(fp, sp, 0x90);
    ld(ra, sp, 0x98);
    sp = addiu(sp, 0xA0);
    return;
L_005551fc_7:
    charge(ctx, 25);
    a2 = addiu(sp, 0x20);
    a0 = s4;
    a3 = a2;
    a2 = s4;
    jal(ctx, 0x555208u, gen::fn_sub_563C28_00563c28);
    lw(v1, s1, 0);
    a2 = s4;
    a0 = s1;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x555220u, v0.u());
    lw(v1, s1, 0);
    v0 = addiu(sp, 0x20);
    a0 = s1;
    a2 = v0;
    lw(v0, v1, 28);
    a1 = 1;
    jalr(ctx, 0x55523Cu, v0.u());
    lw(v1, s1, 0);
    a0 = s1;
    lw(v0, v1, 36);
    a1 = 1;
    jalr(ctx, 0x555250u, v0.u());
    if (i64(v0) <= 0) {
        sb(zero, s5, 4);
    }
    // 0x00555260
    charge(ctx, 3);
    lb(v0, s5, 4);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    lw(v0, sp, 0x48);
    if (!cc) {
        // 0x0055526c
        charge(ctx, 3);
        v0 = 3;
        sb(v0, s5, 1);
        goto L_00555438;
    }
    // 0x0055543c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x50);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(s6, sp, 0x80);
    ld(s7, sp, 0x88);
    ld(fp, sp, 0x90);
    ld(ra, sp, 0x98);
    sp = addiu(sp, 0xA0);
    return;
L_00555288_11:
    charge(ctx, 4);
    a0 = 0x7C0000;
    a0 = addiu(a0, 14520);  // "E2003043003 : Illegal track number."
    jal(ctx, 0x55528Cu, gen::fn_sub_552630_00552630);
    lw(v1, s1, 0);
L_00555298:
    charge(ctx, 8);
    a1 = 1;
    a0 = s1;
    lw(v0, v1, 28);
    a2 = s4;
    jalr(ctx, 0x5552A4u, v0.u());
    a1 = 4;
    sb(a1, s5, 1);
    goto L_00555438;
L_00555358_15:
    charge(ctx, 10);
    a0 = addiu(a0, 14560);
    jal(ctx, 0x555358u, gen::fn_sub_552630_00552630);
    lw(v1, s1, 0);
    a2 = s6;
    a0 = s1;
    lw(v0, v1, 28);
    a1 = 1;
    jalr(ctx, 0x555370u, v0.u());
    lw(v1, s1, 0);
    backedge(ctx);
    goto L_00555298;
}

// 0x00555470 sub_555470 -- 256 bytes; frame 0x60: s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, ra sp+0x50, s0 sp+0x30
// AIX parser: copy one chunk from the source (+28) into the first track stream (+32) and advance the byte count +8.
void sub_555470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555470
    enter(ctx, 64);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a2 = 0x7FFF0000;
    sd(s1, sp, 0x38);
    a3 = sp;
    sd(s2, sp, 0x40);
    s2 = a0;
    sd(s3, sp, 0x48);
    s3 = addiu(s2, 32);
    sd(ra, sp, 0x50);
    a1 = 1;
    sd(s0, sp, 0x30);
    a2 = a2 | 0xFFFF;
    lw(s0, s2, 28);
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a0 = s0;
    jalr(ctx, 0x5554ACu, v0.u());
    lw(a0, s3, 0);
    s1 = addiu(sp, 0x20);
    lw(a2, sp, 0x4);
    lw(v1, a0, 0);
    a3 = s1;
    lw(v0, v1, 24);
    a1 = 0;
    jalr(ctx, 0x5554CCu, v0.u());
    lw(a0, sp, 0x20);
    lw(a1, sp, 0x0);
    link(ctx, 0x5554DCu);  // $ra first: the delay slot below depends on it
    lw(a2, sp, 0x24);
    call(ctx, gen::fn_memcpy_00521250);
    lw(a0, s3, 0);
    a2 = s1;
    lw(v1, a0, 0);
    lw(v0, v1, 32);
    a1 = 1;
    jalr(ctx, 0x5554F4u, v0.u());
    s1 = addiu(sp, 0x10);
    lw(a1, sp, 0x24);
    a0 = sp;
    a2 = sp;
    a3 = s1;
    jal(ctx, 0x55550Cu, gen::fn_sub_563C28_00563c28);
    lw(v1, s0, 0);
    a2 = sp;
    a0 = s0;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x555524u, v0.u());
    lw(a1, s0, 0);
    a0 = s0;
    a2 = s1;
    lw(v1, a1, 28);
    a1 = 1;
    jalr(ctx, 0x55553Cu, v1.u());
    lw(v0, s2, 8);
    lw(v1, sp, 0x24);
    ld(s0, sp, 0x30);
    v0 = addu(v0, v1);
    ld(s1, sp, 0x38);
    sw(v0, s2, 8);
    ld(s3, sp, 0x48);
    ld(s2, sp, 0x40);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x00555738 sub_555738 -- 80 bytes; leaf frame (no stack)
// Returns the first free 16-byte entry of the table *0x99740C (*0x997410 entries), or 0.
void sub_555738(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00555738
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x990000;
    v1 = 0x990000;
    lw(v0, v0, 29712);  // 0x997410
    a1 = 0;
    lw(a0, v1, 29708);  // 0x99740C
    if (i64(v0) > 0) {
        // 0x00555750
        charge(ctx, 2);
        a2 = v0;
        lb(v1, a0, 0);
        for (;;) {
            // 0x00555758
            charge(ctx, 3);
            v0 = a0;
            a0 = addiu(a0, 16);
            if (v1 == 0) {
                break;
            }
            // 0x00555764
            charge(ctx, 6);
            a1 = addiu(a1, 1);
            v0 = slt(a1, a2);
            if (v0 == 0) {
                goto L_0055577c;
            }
            lb(v1, a0, 0);
            backedge(ctx);
        }
        // 0x00555780 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0055577c:
    charge(ctx, 1);
    v0 = 0;
    // 0x00555780 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00555788 sub_555788 -- 152 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, ra sp+0x20
// Returns the table entry (*0x99740C, 16 bytes each) whose 12-char name equals $a0, or 0 (an empty name gives 0).
void sub_555788(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00555788
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lb(v0, s2, 0);
    s3 = 0x990000;
    if (v0 != 0) {
        // 0x005557c0
        charge(ctx, 5);
        v0 = 0x990000;
        lw(v1, s3, 29712);
        s1 = 0;
        lw(s0, v0, 29708);  // 0x99740C
        if (i64(v1) > 0) {
            // 0x005557d4
            charge(ctx, 1);
            for (;;) {
                // 0x005557d8
                charge(ctx, 6);
                a0 = s0;
                a1 = s2;
                a2 = 12;
                jal(ctx, 0x5557E0u, gen::fn_strncmp_00524670);
                s1 = addiu(s1, 1);
                if (v0 == 0) {
                    backedge(ctx);
                    goto L_005557b8;
                }
                // 0x005557f0
                charge(ctx, 4);
                lw(v0, s3, 29712);
                v0 = slt(s1, v0);
                s0 = addiu(s0, 16);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00555800
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x005557b0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00555804 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_005557b8:
    charge(ctx, 2);
    v0 = s0;
    // 0x00555804 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00557C70 sub_557C70 -- 176 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// SRD: under the lock, queue a read on the request $a0 when it is idle / done / failed (state 0, 3, 9): +48 = $a1,
// +40 = $a2, +32 = $a3, +24 = $t0, state 1; returns 1 when queued.
void sub_557C70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00557c70
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = t0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = 0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s5 = a2;
    jal(ctx, 0x557CA4u, gen::fn_sub_5649A8_005649a8);
    lb(v1, s0, srd::kStat);
    v0 = 3;
    if (v1 != 0) {
        // 0x00557cb8
        charge(ctx, 2);
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 9;
        if (cc) {
            goto L_00557cc8;
        }
        // 0x00557cc0
        charge(ctx, 2);
        if (v1 == v0) {
            goto L_00557cc8;
        }
        goto L_00557cf0;
    }
L_00557cc8:
    charge(ctx, 10);
    v0 = 2;
    sw(s2, s0, srd::kFd);
    sb(v0, s0, srd::kMode);
    v0 = 1;
    sb(v0, s0, srd::kStat);
    s4 = 1;
    sw(s1, s0, srd::kBuf);
    sd(s3, s0, srd::kSize);
    sd(s5, s0, srd::kOffset);
    sw(zero, s0, srd::kCancel);
L_00557cf0:
    charge(ctx, 12);
    jal(ctx, 0x557CF0u, gen::fn_sub_564A20_00564a20);
    v0 = s4;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00558320 sub_558320 -- 460 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// SRD host server step for the request $a0: cancel, then seek + read (state 1 -> 2, or 9 on an error), then poll the
// read (state 2 -> 3); 0x558988 marks each I/O call.
void sub_558320(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558320
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(v0, s1, srd::kCancel);
    lbu(a0, s1, srd::kStat);
    if (v0 == v1) {
        // 0x00558344
        charge(ctx, 4);
        lb(v1, s1, srd::kStat);
        v0 = sltiu(v1, 10);
        if (v0 == 0) {
            sw(zero, s1, srd::kCancel);
        } else {
            // 0x00558354
            charge(ctx, 6);
            v0 = sll(v1, 2);
            v1 = 0x7C0000;
            v1 = addu(v1, v0);
            lw(v1, v1, 18304);
            switch (v1.u()) {
            case 0x558370u:  // table[2]
                // 0x00558370
                charge(ctx, 8);
                a0 = s1;
                jal(ctx, 0x558370u, gen::fn_sub_557D80_00557d80);
                sb(zero, s1, srd::kStat);
                v1 = 0x7A0000;
                v1 = addiu(v1, 2316);  // &0x7A090C
                lw(v0, v1, 0);  // 0x7A090C
                v0 = addiu(v0, 1);
                sw(v0, v1, 0);  // 0x7A090C
            L_00558390:
                charge(ctx, 2);
                sb(zero, s1, srd::kStat);
                a0 = 0;
                break;
            case 0x558390u:  // table[1, 3, 9]
                goto L_00558390;
            case 0x558398u:  // table[0, 4, 5, 6, 7, 8]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
            // 0x00558398
            charge(ctx, 1);
            sw(zero, s1, srd::kCancel);
        }
    }
    // 0x0055839c
    charge(ctx, 5);
    v0 = sll(a0, 24);
    v1 = 1;
    v0 = sra(v0, 24);
    if (v0 != v1) {
        v0 = sll(a0, 24);
    } else {
        // 0x005583b0
        charge(ctx, 12);
        a0 = 8192;
        jal(ctx, 0x5583B0u, gen::fn_sub_558988_00558988);
        ld(a1, s1, srd::kOffset);
        lw(a0, s1, srd::kFd);
        a2 = 0;
        a1 = dsll(a1, 11);
        jal(ctx, 0x5583C4u, gen::fn_sub_558B68_00558b68);
        a0 = 8193;
        s0 = v0;
        jal(ctx, 0x5583D0u, gen::fn_sub_558988_00558988);
        v0 = 9;
        if (i64(s0) < 0) {
            // 0x005583e0
            charge(ctx, 4);
            v1 = dsll32(s0, 0);
            v1 = dsra32(v1, 0);
            sb(v0, s1, srd::kStat);
            sw(v1, s1, srd::kErr);
        }
        // 0x005583f0
        charge(ctx, 11);
        a0 = 8448;
        jal(ctx, 0x5583F0u, gen::fn_sub_558988_00558988);
        lw(a0, s1, srd::kFd);
        lw(a1, s1, srd::kBuf);
        link(ctx, 0x558400u);  // $ra first: the delay slot below depends on it
        lw(a2, s1, srd::kSize);
        call(ctx, gen::fn_sub_558D58_00558d58);
        a0 = 8449;
        s0 = v0;
        jal(ctx, 0x55840Cu, gen::fn_sub_558988_00558988);
        v0 = 2;
        if (i64(s0) < 0) {
            // 0x00558440
            charge(ctx, 7);
            v1 = dsll32(s0, 0);
            v1 = dsra32(v1, 0);
            v0 = 9;
            sb(v0, s1, srd::kStat);
            a0 = 9;
            sw(v1, s1, srd::kErr);
            v0 = sll(a0, 24);
        } else {
            // 0x0055841c
            charge(ctx, 9);
            v1 = 0x7A0000;
            sb(v0, s1, srd::kStat);
            v1 = addiu(v1, 2312);  // &0x7A0908
            a0 = 2;
            lw(v0, v1, 0);  // 0x7A0908
            v0 = addiu(v0, 1);
            sw(v0, v1, 0);  // 0x7A0908
            v0 = sll(a0, 24);
        }
    }
    // 0x0055845c
    charge(ctx, 4);
    v1 = 2;
    v0 = sra(v0, 24);
    ld(s0, sp, 0x10);
    if (v0 == v1) {
        // 0x0055846c
        charge(ctx, 8);
        a0 = 8704;
        jal(ctx, 0x55846Cu, gen::fn_sub_558988_00558988);
        lw(a0, s1, srd::kFd);
        a1 = 1;
        a2 = sp;
        jal(ctx, 0x55847Cu, gen::fn_sub_558C20_00558c20);
        if (i64(v0) < 0) {
            // 0x0055848c
            charge(ctx, 7);
            a0 = 8705;
            jal(ctx, 0x55848Cu, gen::fn_sub_558988_00558988);
            v0 = 9;
            v1 = si(-1);
            sb(v0, s1, srd::kStat);
            sw(v1, s1, srd::kErr);
            goto L_005584d8;
        }
        // 0x005584a8
        charge(ctx, 5);
        a0 = 8706;
        jal(ctx, 0x5584A8u, gen::fn_sub_558988_00558988);
        lw(v0, sp, 0x0);
        ld(s0, sp, 0x10);
        if (v0 == 0) {
            // 0x005584bc
            charge(ctx, 7);
            v0 = 3;
            v1 = 0x7A0000;
            sb(v0, s1, srd::kStat);
            v1 = addiu(v1, 2316);  // &0x7A090C
            lw(v0, v1, 0);  // 0x7A090C
            v0 = addiu(v0, 1);
            sw(v0, v1, 0);  // 0x7A090C
        L_005584d8:
            charge(ctx, 1);
            ld(s0, sp, 0x10);
        }
    }
    // 0x005584dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005587A8 sub_5587A8 -- 156 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// SRD host read status: under the lock, 1 while the host read of 0x7A08E0 is still busy, else 0.
void sub_5587A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005587a8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(s0, sp, 0x10);
    s0 = addiu(v0, 2224);  // &srd_obj
    lb(v1, s0, 2);  // 0x7A08B2
    a0 = 2;
    sd(ra, sp, 0x18);
    if (v1 == a0) {
        // 0x005587c8
        charge(ctx, 10);
        jal(ctx, 0x5587C8u, gen::fn_sub_564978_00564978);
        a0 = 9216;
        jal(ctx, 0x5587D0u, gen::fn_sub_558988_00558988);
        a1 = 1;
        lw(a0, s0, 48);
        a2 = sp;
        jal(ctx, 0x5587E0u, gen::fn_sub_558C20_00558c20);
        a0 = 9218;
        if (i64(v0) < 0) {
            // 0x005587f0
            charge(ctx, 4);
            a0 = 9217;
            jal(ctx, 0x5587F0u, gen::fn_sub_558988_00558988);
            goto L_00558828;
        }
        // 0x00558800
        charge(ctx, 5);
        jal(ctx, 0x558800u, gen::fn_sub_558988_00558988);
        lw(v0, sp, 0x0);
        if (v0 == 0) {
        L_00558828:
            charge(ctx, 2);
            jal(ctx, 0x558828u, gen::fn_sub_564990_00564990);
            goto L_00558830;
        }
        // 0x00558814
        charge(ctx, 4);
        jal(ctx, 0x558814u, gen::fn_sub_564990_00564990);
        v0 = 1;
        // 0x00558834 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00558830:
    charge(ctx, 1);
    v0 = 0;
    // 0x00558834 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00558848 sub_558848 -- 76 bytes; frame 0x10: ra sp+0x0
// SRD read status by device byte 0x7A08B1: DVD (1) -> SRD_GetReadStatusDvd * 2, host (2) -> sub_5587A8, else 0.
void sub_558848(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558848
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lb(a0, v0, 2225);  // 0x7A08B1
    v1 = 1;
    sd(ra, sp, 0x0);
    if (a0 == v1) {
        // 0x00558860
        charge(ctx, 4);
        jal(ctx, 0x558860u, gen::fn_SRD_GetReadStatusDvd_00558768);
        v0 = sll(v0, 1);
        // 0x00558888 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00558870
    charge(ctx, 3);
    v1 = 2;
    v0 = 0;
    if (a0 != v1) {
        // 0x00558888 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055887c
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5587A8_005587a8(ctx);  // tail call
}

// 0x005589B8 sub_5589B8 -- 60 bytes; frame 0x10: ra sp+0x0
// SRD: store the 64-bit host-filesystem flag 0x7A0920 = $a0 and print 'SRD: 64bit Host filesystem.' when it is 1.
void sub_5589B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005589b8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7A0000;
    v1 = 1;
    sd(ra, sp, 0x0);
    sw(a0, v0, 2336);  // 0x7A0920
    if (a0 != v1) {
        // 0x005589e8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005589d0
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 18600);  // &0x7C48A8
    sp = addiu(sp, 0x10);
    gen::fn_scePrintf_00505e48(ctx);  // tail call
}

// 0x005589F8 __errno_6 -- 12 bytes; leaf frame (no stack)
// Returns the SRD word 0x7A0920 (the 64-bit host flag).
void __errno_6(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005589f8
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 2336);  // 0x7A0920
}

// 0x00558A60 __errno_7 -- 12 bytes; leaf frame (no stack)
// Returns the SRD word 0x7A0924.
void __errno_7(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00558a60
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 2340);  // 0x7A0924
}

// 0x00559458 sub_559458 -- 176 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// DTX RPC server dispatch: function 2 creates a remote (sub_559718), 3 destroys one (sub_5598B0), 1024..1087 call the
// registered handler pair at 0x7A1B70 / 0x7A1C70; returns $a1.
void sub_559458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00559458
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    v1 = sltiu(a0, 2);
    if (a0 == v0) {
        // 0x00559490
        charge(ctx, 7);
        lw(a0, s0, 0);
        lw(a1, s0, 4);
        lw(a2, s0, 8);
        link(ctx, 0x55949Cu);  // $ra first: the delay slot below depends on it
        lw(a3, s0, 12);
        call(ctx, gen::fn_sub_559718_00559718);
        sw(v0, s0, 0);
    L_005594f4:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00559474
        charge(ctx, 2);
        v0 = s0;
        if (v1 == 0) {
            // 0x0055947c
            charge(ctx, 3);
            v0 = 3;
            cc = a0 == v0;  // the condition, before the delay slot changes it
            v0 = addiu(a0, -1024);
            if (cc) {
                // 0x005594b0
                charge(ctx, 4);
                link(ctx, 0x5594B0u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 0);
                call(ctx, gen::fn_sub_5598B0_005598b0);
                v0 = s0;
            } else {
                // 0x00559488
                charge(ctx, 2);
                v1 = sll(v0, 2);
                // 0x005594c0
                charge(ctx, 3);
                v0 = sltiu(v0, 64);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = s0;
                if (!cc) {
                    // 0x005594cc
                    charge(ctx, 5);
                    v0 = 0x7A0000;
                    v0 = addu(v0, v1);
                    lw(v0, v0, 7024);
                    a2 = srl(a2, 2);
                    if (v0 != 0) {
                        // 0x005594e0
                        charge(ctx, 5);
                        a0 = 0x7A0000;
                        a0 = addu(a0, v1);
                        lw(a0, a0, 7280);
                        a1 = s0;
                        jalr(ctx, 0x5594ECu, v0.u());
                    }
                    goto L_005594f4;
                }
            }
        }
    }
    // 0x005594f8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00559648 sub_559648 -- 24 bytes; leaf frame (no stack)
// Increments the counter 0x7A1150.
void sub_559648(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00559648
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    v1 = addiu(v1, 4432);  // &0x7A1150
    lw(v0, v1, 0);  // 0x7A1150
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x7A1150
}

// 0x00559660 sub_559660 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// DTX test RPC: fill $a1[0..$a2) with 0xAA, then sprintf 'Hello from EE (%d)' with the counter 0x7A1154 and count it.
void sub_559660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00559660
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(s0, sp, 0x0);
    a1 = 0;
    sd(ra, sp, 0x8);
    if (i64(a2) > 0) {
        // 0x00559678
        charge(ctx, 2);
        a3 = si(-86);
        for (;;) {
            // 0x00559680
            charge(ctx, 7);
            v1 = addu(a0, a1);
            a1 = addiu(a1, 1);
            v0 = slt(a1, a2);
            sb(a3, v1, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055969c
    charge(ctx, 13);
    s0 = 0x7A0000;
    a1 = 0x7C0000;
    s0 = addiu(s0, 4436);  // &0x7A1154
    a1 = addiu(a1, 19208);  // "Hello from EE (%d)"
    link(ctx, 0x5596ACu);  // $ra first: the delay slot below depends on it
    lw(a2, s0, 0);  // 0x7A1154
    call(ctx, gen::fn_sprintf_00523ac8);
    lw(v1, s0, 0);  // 0x7A1154
    ld(ra, sp, 0x8);
    v1 = addiu(v1, 1);
    sw(v1, s0, 0);  // 0x7A1154
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055B480 sub_55B480 -- 328 bytes; frame 0x40: s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s1 sp+0x8, s5 sp+0x28, s0 sp+0x0, ra sp+0x30
// DVCI: load the file list -- clear 0x997BC0, check the buffers ('DVCI: Invalidate filelist buffer ...'), analyse the
// list (dvci_analysis_flist) and return the bytes used.
void sub_55B480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b480
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x990000;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a0;
    a1 = 0;
    a2 = 4096;
    a0 = addiu(v0, 31680);  // &0x997BC0
    sd(s1, sp, 0x8);
    sd(s5, sp, 0x28);
    s5 = t0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s1 = a3;
    jal(ctx, 0x55B4C0u, gen::fn_memset_00521408);
    v1 = 0x7A0000;
    lw(v0, v1, 10848);  // 0x7A2A60
    if (v0 != 0) {
        // 0x0055b4d8
        charge(ctx, 2);
        jal(ctx, 0x55B4D8u, gen::fn_sub_55B0F8_0055b0f8);
    }
    // 0x0055b4e0
    charge(ctx, 2);
    if (s4 != 0) {
        // 0x0055b4e8
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_0055b500;
        }
        // 0x0055b4f0
        charge(ctx, 2);
        if (s3 == 0) {
            goto L_0055b500;
        }
        // 0x0055b4f8
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_0055b500;
        }
        goto L_0055b508;
    }
L_0055b500:
    charge(ctx, 2);
    jal(ctx, 0x55B500u, gen::fn_sub_55B0F8_0055b0f8);
L_0055b508:
    charge(ctx, 2);
    v0 = 0;
    if (s4 != 0) {
        // 0x0055b510
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s2 == 0) {
            // 0x0055b518
            charge(ctx, 3);
            a1 = 0;
            a0 = addiu(a0, 20272);
            goto L_0055b544;
        }
        // 0x0055b528
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s3 != 0) {
            // 0x0055b530
            charge(ctx, 2);
            s0 = addiu(s5, 9);
            if (s1 == 0) {
                // 0x0055b538
                charge(ctx, 1);
                a0 = 0x7C0000;
                goto L_0055b53c;
            }
            // 0x0055b558
            charge(ctx, 7);
            a2 = s3;
            divu(s1, s0);
            a1 = s4;
            t0 = s5;
            a0 = s2;
            if (s0 == 0) {
                brk(ctx, 0x55B570u, 0x7u);
            }
            // 0x0055b574
            charge(ctx, 9);
            mflo(s1);
            a3 = s1;
            s1 = sll(s1, 3);
            jal(ctx, 0x55B57Cu, gen::fn_dvci_analysis_flist_0055ab80);
            a0 = s2;
            a1 = v0;
            jal(ctx, 0x55B588u, gen::fn_dvci_search_fstate_0055aea0);
            if (s0 == 0) {
                brk(ctx, 0x55B594u, 0x7u);
            }
            // 0x0055b598
            charge(ctx, 3);
            v1 = addiu(s5, 1);
            mult(v0, v0, v1);
            v0 = addu(s1, v0);
            // 0x0055b5a4 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(s5, sp, 0x28);
            ld(ra, sp, 0x30);
            sp = addiu(sp, 0x40);
            return;
        }
    L_0055b53c:
        charge(ctx, 2);
        a1 = 0;
        a0 = addiu(a0, 20320);
    L_0055b544:
        charge(ctx, 4);
        jal(ctx, 0x55B544u, gen::fn_sub_5416E8_005416e8);
        v0 = 0;
    }
    // 0x0055b5a4 (the shared epilogue, written out on this path)
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

// 0x0055B5C8 sub_55B5C8 -- 36 bytes; frame 0x40: ra sp+0x30
// DVCI: 1 when dvci_get_fstate finds the file $a0, else 0.
void sub_55B5C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b5c8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    a1 = sp;
    jal(ctx, 0x55B5D0u, gen::fn_dvci_get_fstate_0055b220);
    lw(v0, sp, 0x0);
    ld(ra, sp, 0x30);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x40);
}

// 0x0055B6E8 atan2l_7 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: SRD_SetDvdSeekPos.
void atan2l_7(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b6e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_SRD_SetDvdSeekPos_00558ae0(ctx);  // tail call
}

// 0x0055B798 sub_55B798 -- 44 bytes; leaf frame (no stack)
// A delay loop: $v0 counts down from 8191 by 32 over five nops.
void sub_55B798(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055b798
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 8191;
    v0 = addiu(v0, -32);
    for (;;) {
        // 0x0055b7a0
        charge(ctx, 7);
        if (i64(v0) < 0) {
            break;
        }
        v0 = addiu(v0, -32);
        backedge(ctx);
    }
    // 0x0055b7bc
    charge(ctx, 2);
}

// 0x0055B7F8 sub_55B7F8 -- 80 bytes; leaf frame (no stack)
// File system: 1 when any of the 13 handles (12 bytes each, 0x7A2C80) is in use with a read pending (byte0 1, byte2
// 2), else 0.
void sub_55B7F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0055b7f8
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    a1 = 0;
    a0 = addiu(v0, 11392);  // &0x7A2C80
    a3 = 1;
    a2 = 2;
    for (;;) {
        // 0x0055b810
        charge(ctx, 3);
        lb(v0, a0, 0);
        if (v0 != a3) {
            a1 = addiu(a1, 1);
        } else {
            // 0x0055b81c
            charge(ctx, 3);
            lb(v1, a0, 2);
            v0 = 1;
            if (v1 == a2) {
                break;
            }
            // 0x0055b828
            charge(ctx, 1);
            a1 = addiu(a1, 1);
            goto L_0055b82c;
        }
    L_0055b82c:
        charge(ctx, 4);
        v0 = slti(a1, 13);
        a0 = addiu(a0, 48);
        if (v0 == 0) {
            goto L_0055b83c_5;
        }
        backedge(ctx);
    }
    // 0x0055b840 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0055b83c_5:
    charge(ctx, 1);
    v0 = 0;
    // 0x0055b840 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0055B8B0 sub_55B8B0 -- 96 bytes; frame 0x10: ra sp+0x0
// File handle $a0: zero the part of the read buffer (+32) that lies past the end of the file.
void sub_55B8B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b8b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    lw(a0, a1, fsh::kNreq);
    lw(v0, a1, fsh::kPos);
    ld(v1, a1, fsh::kSize);
    a3 = sll(a0, 11);
    v0 = v0 + a0;
    v0 = dsll(v0, 11);
    a0 = v0 - v1;
    v1 = sltu(v1, v0);
    v0 = dsll32(a0, 0);
    v0 = dsra32(v0, 0);
    ld(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x0055b908
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055b8ec
    charge(ctx, 7);
    lw(a0, a1, fsh::kBuf);
    a1 = 0;
    a2 = v0;
    a0 = addu(a0, a3);
    a0 = subu(a0, v0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055B910 sub_55B910 -- 196 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// File handle $a0: poll its SRD request (+44) under the lock -- done: state 1 and the position advances; idle: state
// 0; error: state 3; the request is destroyed.
void sub_55B910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b910
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, fsh::kSrd);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
        // 0x0055b9c8
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055b92c
    charge(ctx, 8);
    jal(ctx, 0x55B92Cu, gen::fn_sub_5649A8_005649a8);
    link(ctx, 0x55B934u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, fsh::kSrd);
    call(ctx, gen::fn_sub_557D20_00557d20);
    v1 = v0;
    v0 = sltiu(v1, 10);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0055b94c
        charge(ctx, 6);
        v0 = sll(v1, 2);
        v1 = 0x7C0000;
        v1 = addu(v1, v0);
        lw(v1, v1, 20528);
        switch (v1.u()) {
        case 0x55B968u:  // table[9]
            // 0x0055b968
            charge(ctx, 4);
            v0 = 3;
            lw(a0, s0, fsh::kSrd);
            sb(v0, s0, fsh::kStat);
        L_0055b9a8:
            charge(ctx, 3);
            jal(ctx, 0x55B9A8u, gen::fn_sub_557AE0_00557ae0);
            sw(zero, s0, fsh::kSrd);
            break;
        case 0x55B978u:  // table[3]
            // 0x0055b978
            charge(ctx, 9);
            lw(a0, s0, fsh::kNreq);
            v1 = 1;
            lw(v0, s0, fsh::kPos);
            sw(a0, s0, fsh::kNread);
            v0 = addu(v0, a0);
            lw(a0, s0, fsh::kSrd);
            sb(v1, s0, fsh::kStat);
            sw(v0, s0, fsh::kPos);
            goto L_0055b9a8;
        case 0x55B9A0u:  // table[0]
            // 0x0055b9a0
            charge(ctx, 2);
            sb(zero, s0, fsh::kStat);
            lw(a0, s0, fsh::kSrd);
            goto L_0055b9a8;
        case 0x55B9B4u:  // table[1, 2, 4, 5, 6, 7, 8]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x0055b9b4
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0055b9b8
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A20_00564a20(ctx);  // tail call
}

// 0x0055BA68 sub_55BA68 -- 160 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// HTCI: probe the file $a0 -- when the cache has no entry, open and close it on the host; returns 1 when it exists.
void sub_55BA68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ba68
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    if (s0 != 0) {
        // 0x0055ba84
        charge(ctx, 8);
        a1 = sp;
        jal(ctx, 0x55BA84u, gen::fn_sub_55CF08_0055cf08);
        v0 = 0x7A0000;
        s1 = addiu(v0, 12016);  // &0x7A2EF0
        lw(v0, sp, 0x4);
        a0 = s0;
        a1 = s1;
        if (v0 == 0) {
            // 0x0055baa4
            charge(ctx, 13);
            jal(ctx, 0x55BAA4u, gen::fn_sub_55C610_0055c610);
            a0 = 16896;
            jal(ctx, 0x55BAACu, gen::fn_sub_558988_00558988);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x55BAB8u, gen::fn_sub_558C98_00558c98);
            a0 = 16897;
            s0 = v0;
            jal(ctx, 0x55BAC4u, gen::fn_sub_558988_00558988);
            a0 = 17152;
            v0 = 0;
            if (i64(s0) >= 0) {
                // 0x0055bad8
                charge(ctx, 6);
                jal(ctx, 0x55BAD8u, gen::fn_sub_558988_00558988);
                a0 = s0;
                jal(ctx, 0x55BAE0u, gen::fn_sub_558D00_00558d00);
                a0 = 17153;
                jal(ctx, 0x55BAE8u, gen::fn_sub_558988_00558988);
                goto L_0055baf0;
            }
            // 0x0055baf4 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x10);
            ld(s1, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0055baf0:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x0055baf4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055BCE8 sub_55BCE8 -- 136 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// HTCI: size of the open host file $a0 (lseek to the end after a rewind); 0 on an error.
void sub_55BCE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055bce8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    a0 = 18176;
    jal(ctx, 0x55BCFCu, gen::fn_sub_558988_00558988);
    a0 = s1;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x55BD0Cu, gen::fn_sub_558B68_00558b68);
    a0 = 18177;
    s0 = v0;
    jal(ctx, 0x55BD18u, gen::fn_sub_558988_00558988);
    a0 = 18432;
    v0 = 0;
    if (i64(s0) >= 0) {
        // 0x0055bd2c
        charge(ctx, 12);
        jal(ctx, 0x55BD2Cu, gen::fn_sub_558988_00558988);
        a0 = s1;
        a1 = 0;
        a2 = 2;
        jal(ctx, 0x55BD3Cu, gen::fn_sub_558B68_00558b68);
        a0 = 18433;
        s0 = v0;
        jal(ctx, 0x55BD48u, gen::fn_sub_558988_00558988);
        v1 = slti(s0, 0);
        v0 = 0;
        if (v1 == 0) v0 = s0;
    }
    // 0x0055bd5c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055BD70 sub_55BD70 -- 52 bytes; leaf frame (no stack)
// Returns the last free entry of the 13 file handles at 0x7A2C80 (48-byte stride), or 0.
void sub_55BD70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055bd70
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    a1 = 0;
    v1 = addiu(v0, 11392);  // &0x7A2C80
    a0 = 12;
    for (;;) {
        // 0x0055bd80
        charge(ctx, 7);
        lb(v0, v1, 0);
        a0 = addiu(a0, -1);
        v0 = v0 ^ 0x0;
        if (v0 == 0) a1 = v1;
        v1 = addiu(v1, 48);
        if (i64(a0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055bd9c
    charge(ctx, 2);
    v0 = a1;
}

// 0x0055BFE0 sub_55BFE0 -- 148 bytes; frame 0x10: ra sp+0x0
// File seek: $a2 = 0 (set), 1 (current), 2 (end) moves the sector position +28 by $a1, clamped to [0, size +16]. Null
// -> 'E0092712:handl is null.'
void sub_55BFE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055bfe0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a0;
    sd(ra, sp, 0x0);
    if (a3 != 0) {
        // 0x0055c008
        charge(ctx, 2);
        v0 = 2;
        if (a2 != 0) {
            // 0x0055c018
            charge(ctx, 2);
            cc = a2 != v0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                // 0x0055c030
                charge(ctx, 2);
                lw(a0, a3, fsh::kNsct);
                if (a2 == v0) {
                    // 0x0055c038
                    charge(ctx, 4);
                    lw(v0, a3, fsh::kPos);
                    v0 = addu(v0, a1);
                    sw(v0, a3, fsh::kPos);
                }
            } else {
                // 0x0055c020
                charge(ctx, 4);
                lw(a0, a3, fsh::kNsct);
                v0 = addu(a0, a1);
                sw(v0, a3, fsh::kPos);
            }
        } else {
            // 0x0055c010
            charge(ctx, 2);
            sw(a1, a3, fsh::kPos);
            // 0x0055c048
            charge(ctx, 1);
            lw(a0, a3, fsh::kNsct);
        }
        // 0x0055c04c
        charge(ctx, 7);
        lw(v0, a3, fsh::kPos);
        sw(zero, a3, fsh::kNread);
        v1 = slt(v0, a0);
        if (v1 == 0) v0 = a0;
        a0 = slti(v0, 0);
        if (a0 != 0) v0 = 0;
        sw(v0, a3, fsh::kPos);
    } else {
        // 0x0055bff0
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 21168);  // "E0092712:handl is null."
        jal(ctx, 0x55BFF4u, gen::fn_sub_55B7C8_0055b7c8);
        v0 = 0;
    }
    // 0x0055c068 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055C078 sub_55C078 -- 56 bytes; frame 0x10: ra sp+0x0
// File tell: returns the sector position +28. Null -> 'E0092712:handl is null.' and 0.
void sub_55C078(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c078
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055c0a0
        charge(ctx, 1);
        lw(v0, v0, 28);
    } else {
        // 0x0055c088
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 21168);  // "E0092712:handl is null."
        jal(ctx, 0x55C08Cu, gen::fn_sub_55B7C8_0055b7c8);
        v0 = 0;
    }
    // 0x0055c0a4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055C0B0 sub_55C0B0 -- 400 bytes; frame 0x40: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// File read request: $a1 sectors into $a2 through a new SRD request (synchronous when 0x7A3030 is 1); returns the
// sectors queued. Null / bad arguments -> 'E0092712..14'.
void sub_55C0B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c0b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s0, sp, 0x0);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    if (s1 == 0) {
        // 0x0055c0e0
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 21168);  // "E0092712:handl is null."
        goto L_0055c10c;
    }
    // 0x0055c0f0
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (i64(s2) < 0) {
        // 0x0055c0f8
        charge(ctx, 2);
        a1 = addiu(a1, 21192);
        goto L_0055c10c;
    }
    // 0x0055c100
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (s3 == 0) {
        // 0x0055c108
        charge(ctx, 1);
        a1 = addiu(a1, 21224);
    L_0055c10c:
        charge(ctx, 4);
        jal(ctx, 0x55C10Cu, gen::fn_sub_55B7C8_0055b7c8);
        v0 = 0;
        goto L_0055c21c;
    }
    // 0x0055c120
    charge(ctx, 4);
    s4 = 1;
    jal(ctx, 0x55C120u, gen::fn_sub_55B7F8_0055b7f8);
    if (v0 == s4) {
        // 0x0055c130
        charge(ctx, 2);
        v0 = 0;
        goto L_0055c21c;
    }
    lb(v1, s1, fsh::kStat);
    // 0x0055c138
    charge(ctx, 3);
    s5 = 2;
    v0 = 0;
    if (v1 == s5) {
    L_0055c21c:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x0055c144
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x0055c14c
            charge(ctx, 2);
            sb(s4, s1, fsh::kStat);
            goto L_0055c21c;
        }
        // 0x0055c158
        charge(ctx, 5);
        jal(ctx, 0x55C158u, gen::fn_SRD_Create_00557a58);
        v1 = v0;
        sw(v1, s1, fsh::kSrd);
        if (v1 == 0) {
            goto L_0055c21c;
        }
        // 0x0055c16c
        charge(ctx, 22);
        lw(v1, s1, fsh::kPos);
        a1 = s2;
        lw(v0, s1, fsh::kNsct);
        s0 = sll(s2, 11);
        ld(a3, s1, fsh::kSize);
        v0 = subu(v0, v1);
        sw(s3, s1, fsh::kBuf);
        v1 = slt(s2, v0);
        a2 = sltu(a3, s0);
        if (v1 == 0) a1 = v0;
        a0 = s1;
        sw(a1, s1, fsh::kNreq);
        if (a2 != 0) s0 = a3;
        jal(ctx, 0x55C19Cu, gen::fn_sub_55B8B0_0055b8b0);
        lw(a0, s1, fsh::kSrd);
        lw(a1, s1, fsh::kFd);
        a3 = s0;
        lw(a2, s1, fsh::kPos);
        t0 = s3;
        jal(ctx, 0x55C1B4u, gen::fn_sub_557C70_00557c70);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            // 0x0055c1c4
            charge(ctx, 4);
            v0 = 0x7A0000;
            lw(s0, v0, 12336);  // 0x7A3030
            if (s0 != s4) {
                sb(s5, s1, fsh::kStat);
                // 0x0055c210
                charge(ctx, 2);
                sw(zero, s1, fsh::kNread);
                lw(v0, s1, fsh::kNreq);
            } else {
                // 0x0055c1d4
                charge(ctx, 15);
                jal(ctx, 0x55C1D4u, gen::fn_sub_558610_00558610);
                jal(ctx, 0x55C1DCu, gen::fn_SRD_ExecServer_00558500);
                lw(v0, s1, fsh::kPos);
                lw(v1, s1, fsh::kNreq);
                lw(a0, s1, fsh::kSrd);
                v0 = addu(v0, v1);
                link(ctx, 0x55C1F4u);  // $ra first: the delay slot below depends on it
                sw(v0, s1, fsh::kPos);
                call(ctx, gen::fn_sub_557AE0_00557ae0);
                sw(zero, s1, fsh::kSrd);
                lw(v0, s1, fsh::kNreq);
                sb(s0, s1, fsh::kStat);
                sw(v0, s1, fsh::kNread);
            }
            // 0x0055c218
            charge(ctx, 1);
            sw(zero, s1, fsh::kWord20);
            goto L_0055c21c;
        }
    }
    // 0x0055c220 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0055C370 sub_55C370 -- 8 bytes; leaf frame (no stack)
// Returns 2048 (the sector size).
void sub_55C370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055c370
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 2048;
}

// 0x0055C378 sub_55C378 -- 76 bytes; frame 0x10: ra sp+0x0
// File: bytes read by the last request (+40 sectors << 11) when the state is 1, else 0. Null -> 'E0092712:handl is
// null.'
void sub_55C378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c378
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    if (a1 != 0) {
        // 0x0055c3a0
        charge(ctx, 4);
        lb(v1, a1, fsh::kStat);
        v0 = 1;
        if (v1 != v0) {
            v0 = 0;
        } else {
            // 0x0055c3b0
            charge(ctx, 2);
            lw(v0, a1, fsh::kNread);
            v0 = sll(v0, 11);
        }
    } else {
        // 0x0055c388
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 21168);  // "E0092712:handl is null."
        jal(ctx, 0x55C38Cu, gen::fn_sub_55B7C8_0055b7c8);
        v0 = 0;
    }
    // 0x0055c3b8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055C3E0 sub_55C3E0 -- 28 bytes; leaf frame (no stack)
// File: the high word of min(size +8, +40 << 11).
void sub_55C3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055c3e0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, a0, fsh::kNread);
    ld(a1, a0, fsh::kSize);
    v0 = dsll(v0, 11);
    v1 = sltu(a1, v0);
    if (v1 != 0) v0 = a1;
    v0 = dsra32(v0, 0);
}

// 0x0055C400 sub_55C400 -- 44 bytes; leaf frame (no stack)
// File: the low word of min(size +8, +40 << 11).
void sub_55C400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0055c400
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(v0, a0, fsh::kNread);
    a2 = lui(0xFFFF);
    a2 = dsrl32(a2, 0);
    ld(a1, a0, fsh::kSize);
    v0 = dsll(v0, 11);
    v1 = sltu(a1, v0);
    if (v1 != 0) v0 = a1;
    v0 = v0 & a2;
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
}

// 0x0055C430 sub_55C430 -- 32 bytes; frame 0x10: ra sp+0x0
// The high word of sub_55C3C8.
void sub_55C430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c430
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x55C438u, gen::fn_sub_55C3C8_0055c3c8);
    ld(ra, sp, 0x0);
    v0 = dsra32(v0, 0);
    sp = addiu(sp, 0x10);
}

// 0x0055C450 sub_55C450 -- 48 bytes; frame 0x10: ra sp+0x0
// The low word of sub_55C3C8.
void sub_55C450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c450
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x55C458u, gen::fn_sub_55C3C8_0055c3c8);
    v1 = lui(0xFFFF);
    v1 = dsrl32(v1, 0);
    ld(ra, sp, 0x0);
    v0 = v0 & v1;
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    sp = addiu(sp, 0x10);
}

// 0x0055C480 sub_55C480 -- 196 bytes; frame 0x10: ra sp+0x0
// File info by code $a1 (handle $a0, 0 when null): 200 / 201 the high / low word of the bytes read (sub_55C3E0 /
// sub_55C400), 202 and 204 the high, 203 and 205 the low word of sub_55C3C8, 299 -> 1; any other code 0.
void sub_55C480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055c480
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0;
    sd(ra, sp, 0x0);
    v0 = 0;
    if (a0 != 0) {
        // 0x0055c494
        charge(ctx, 3);
        v0 = 203;
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = slti(a1, 204);
        if (!cc) {
            // 0x0055c4a0
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 205;
            if (cc) {
                // 0x0055c4d0
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(a1, 205);
                if (cc) {
                    goto L_0055c520;
                }
                // 0x0055c4d8
                charge(ctx, 2);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 299;
                if (cc) {
                L_0055c510:
                    charge(ctx, 4);
                    jal(ctx, 0x55C510u, gen::fn_sub_55C430_0055c430);
                    v1 = v0;
                L_0055c534:
                    charge(ctx, 1);
                    v0 = v1;
                    goto L_0055c538;
                }
                // 0x0055c4e0
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = v1;
                if (cc) {
                    // 0x0055c530
                    charge(ctx, 1);
                    v1 = 1;
                    goto L_0055c534;
                }
                // 0x0055c4e8
                charge(ctx, 2);
                ld(ra, sp, 0x0);
            } else {
                // 0x0055c4a8
                charge(ctx, 3);
                v0 = 201;
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(a1, 202);
                if (cc) {
                    // 0x0055c500
                    charge(ctx, 4);
                    jal(ctx, 0x55C500u, gen::fn_sub_55C400_0055c400);
                    v1 = v0;
                    goto L_0055c534;
                }
                // 0x0055c4b4
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 200;
                if (cc) {
                    goto L_0055c510;
                }
                // 0x0055c4bc
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = v1;
                if (cc) {
                    // 0x0055c4f0
                    charge(ctx, 4);
                    jal(ctx, 0x55C4F0u, gen::fn_sub_55C3E0_0055c3e0);
                    v1 = v0;
                    goto L_0055c534;
                }
                // 0x0055c4c4
                charge(ctx, 2);
                ld(ra, sp, 0x0);
            }
            // 0x0055c53c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0055c520:
        charge(ctx, 4);
        jal(ctx, 0x55C520u, gen::fn_sub_55C450_0055c450);
        v1 = v0;
        goto L_0055c534;
    }
L_0055c538:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0055c53c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0055C548 sub_55C548 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// 1 when the first 16 characters of $a0 hold a ':' (a device prefix), else 0.
void sub_55C548(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c548
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55C554u, gen::fn_strlen_00524388);
    a2 = v0;
    v0 = 16;
    v1 = sltiu(a2, 17);
    if (v1 == 0) a2 = v0;
    a1 = 0;
    if (a2 != 0) {
        // 0x0055c574
        charge(ctx, 3);
        a3 = 58;
        v0 = addu(s0, a1);
        for (;;) {
            // 0x0055c580
            charge(ctx, 5);
            a1 = addiu(a1, 1);
            lb(v1, v0, 0);
            v0 = 1;
            a0 = sltu(a1, a2);
            if (v1 == a3) {
                break;
            }
            // 0x0055c594
            charge(ctx, 4);
            v0 = addu(s0, a1);
            if (a0 == 0) {
                goto L_0055c5a4;
            }
            backedge(ctx);
        }
        // 0x0055c5a8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0055c5a4:
    charge(ctx, 1);
    v0 = 0;
    // 0x0055c5a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0055C5B8 sub_55C5B8 -- 88 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// 1 when the first four characters of $a0 are 'host', else 0.
void sub_55C5B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c5b8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 6;
    sd(s0, sp, 0x10);
    s0 = a0;
    a1 = 0;
    sd(ra, sp, 0x18);
    a0 = sp;
    jal(ctx, 0x55C5D0u, gen::fn_memset_00521408);
    lwl(v0, s0, 3);
    lwr(v0, s0, 0);
    swl(v0, sp, 0x3);
    a1 = 0x7C0000;
    a1 = addiu(a1, 21320);  // "host"
    a0 = sp;
    swr(v0, sp, 0x0);
    link(ctx, 0x55C5F4u);  // $ra first: the delay slot below depends on it
    sb(zero, sp, 0x5);
    call(ctx, gen::fn_strcmp_00524128);
    ld(s0, sp, 0x10);
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0055C728 sub_55C728 -- 24 bytes; leaf frame (no stack)
// Folds '\\' to '/'; any other character is returned as is.
void sub_55C728(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0055c728
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = sll(a0, 24);
    v0 = 47;
    a0 = sra(a0, 24);
    v1 = a0 ^ 0x5C;
    if (v1 != 0) v0 = a0;
}

// 0x0055C740 sub_55C740 -- 84 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// 0 when the characters $a0 and $a1 are equal after folding '\\' to '/', else -1.
void sub_55C740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055c740
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = sll(a0, 24);
    sd(s1, sp, 0x8);
    s1 = sll(a1, 24);
    s1 = sra(s1, 24);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    a0 = sra(a0, 24);
    jal(ctx, 0x55C75Cu, gen::fn_sub_55C728_0055c728);
    a0 = s1;
    s0 = v0;
    jal(ctx, 0x55C768u, gen::fn_sub_55C728_0055c728);
    v1 = si(-1);
    s0 = s0 ^ v0;
    v0 = 0;
    if (s0 != 0) v0 = v1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055C798 sub_55C798 -- 148 bytes; frame 0x30: s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Path compare: 0 when $a0 and $a1 have the same length and every character matches with '\\' == '/', else -1.
void sub_55C798(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055c798
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x55C7B4u, gen::fn_strlen_00524388);
    a0 = s2;
    s1 = v0;
    jal(ctx, 0x55C7C0u, gen::fn_strlen_00524388);
    if (s1 == v0) {
        // 0x0055c7d8
        charge(ctx, 2);
        s0 = 0;
        if (i64(s1) > 0) {
            // 0x0055c7e0
            charge(ctx, 2);
            v1 = addu(s2, s0);
            for (;;) {
                // 0x0055c7e8
                charge(ctx, 7);
                v0 = addu(s3, s0);
                lb(a1, v1, 0);
                s0 = addiu(s0, 1);
                link(ctx, 0x55C7F4u);  // $ra first: the delay slot below depends on it
                lb(a0, v0, 0);
                call(ctx, gen::fn_sub_55C740_0055c740);
                v1 = slt(s0, s1);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_0055c7d0;
                }
                // 0x0055c804
                charge(ctx, 2);
                cc = v1 != 0;  // the condition, before the delay slot changes it
                v1 = addu(s2, s0);
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0055c80c
        charge(ctx, 1);
        v0 = 0;
        // 0x0055c810 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0055c7d0:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x0055c810 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055C830 sub_55C830 -- 412 bytes; frame 0x60: s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, fp sp+0x50, s0 sp+0x10, s1 sp+0x18, s6 sp+0x40, s7 sp+0x48, ra sp+0x58
// HTCI: split the file-list text $a1 into up to $a2 names (CR / LF separated, '\\' -> '/') into the table $a0 (entry
// size $a3); the first call keeps the table in 0x7A3020..2C; returns the count.
void sub_55C830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055c830
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    s4 = 0;
    sd(s5, sp, 0x38);
    s5 = a2;
    sd(fp, sp, 0x50);
    fp = a3;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x58);
    sw(a0, sp, 0x0);
    lb(v0, s3, 0);
    a1 = 0;
    if (v0 != 0) {
        // 0x0055c880
        charge(ctx, 6);
        v0 = sll(s5, 3);
        a0 = s3;
        sw(v0, sp, 0x4);
        s7 = 10;
        s6 = 13;
        lb(v0, a0, 0);
        for (;;) {
            // 0x0055c898
            charge(ctx, 3);
            a2 = 92;
            lbu(v1, a0, 0);
            if (v0 == a2) {
                // 0x0055c8a4
                charge(ctx, 3);
                v0 = 47;
                v1 = 47;
                sb(v0, a0, 0);
            }
            // 0x0055c8b0
            charge(ctx, 4);
            v0 = sll(v1, 24);
            v0 = sra(v0, 24);
            if (v0 == s7) {
                lb(v0, a0, 1);
            } else {
                // 0x0055c8c0
                charge(ctx, 2);
                if (v0 == s6) {
                    lb(v0, a0, 1);
                    goto L_0055c8d4;
                }
                // 0x0055c8c8
                charge(ctx, 2);
                v1 = addiu(s2, 1);
                if (v0 == 0) {
                    // 0x0055c8d0
                    charge(ctx, 1);
                    lb(v0, a0, 1);
                    goto L_0055c8d4;
                }
            L_0055c958:
                charge(ctx, 6);
                s2 = v1;
                v0 = addu(s3, s2);
                a0 = v0;
                lb(v1, a0, 0);
                if (v1 != 0) {
                    lb(v0, a0, 0);
                    backedge(ctx);
                    continue;
                }
                break;
            }
        L_0055c8d4:
            charge(ctx, 2);
            if (v0 == s7) {
                s2 = addiu(s2, 1);
            } else {
                // 0x0055c8dc
                charge(ctx, 2);
                if (v0 == s6) {
                    s2 = addiu(s2, 1);
                    goto L_0055c8f0;
                }
                // 0x0055c8e4
                charge(ctx, 2);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = addiu(a0, -1);
                if (!cc) {
                    // 0x0055c8ec
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                    goto L_0055c8f0;
                }
                goto L_0055c8f8;
            }
        L_0055c8f0:
            charge(ctx, 2);
            a0 = addu(s3, s2);
            v0 = addiu(a0, -1);
        L_0055c8f8:
            charge(ctx, 3);
            lb(v1, v0, 0);
            s1 = subu(s2, a1);
            if (v1 != s7) {
                // 0x0055c904
                charge(ctx, 2);
                if (v1 == s6) {
                    goto L_0055c90c;
                }
                mult(v0, fp, s4);
                goto L_0055c914;
            }
        L_0055c90c:
            charge(ctx, 2);
            sb(zero, v0, 0);
            mult(v0, fp, s4);
        L_0055c914:
            charge(ctx, 13);
            lw(v1, sp, 0x4);
            a2 = s1;
            a1 = addu(s3, a1);
            s0 = addu(v0, s4);
            lw(v0, sp, 0x0);
            s0 = addu(v1, s0);
            s0 = addu(v0, s0);
            a0 = s0;
            jal(ctx, 0x55C930u, gen::fn_memcpy_00521250);
            a2 = addu(s0, s1);
            lb(v0, a2, -1);
            if (v0 != 0) {
                sb(zero, a2, 0);
            }
            // 0x0055c948
            charge(ctx, 4);
            v1 = addiu(s2, 1);
            s4 = addiu(s4, 1);
            a1 = v1;
            if (s4 == s5) {
                break;
            }
            goto L_0055c958;
        }
    }
    // 0x0055c970
    charge(ctx, 5);
    v0 = 0x7A0000;
    v0 = addiu(v0, 12320);  // &0x7A3020
    lw(v1, v0, 0);  // 0x7A3020
    if (v1 != 0) {
        v0 = s4;
    } else {
        // 0x0055c984
        charge(ctx, 6);
        sw(fp, v0, 12);
        lw(v1, sp, 0x0);
        sw(s5, v0, 8);
        sw(v1, v0, 0);
        sw(s4, v0, 4);
        v0 = s4;
    }
    // 0x0055c99c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x0055CB30 sub_55CB30 -- 440 bytes; frame 0x150: s4 sp+0x120, s5 sp+0x128, s3 sp+0x118, s6 sp+0x130, fp sp+0x140, s0 sp+0x100, s1 sp+0x108, s2 sp+0x110, s7 sp+0x138, ra sp+0x148
// HTCI: open every listed cache file (at most 13), keep its descriptor and size in $a0, and report the total ('HTCI:
// ...').
void sub_55CB30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0055cb30
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    a2 = 256;
    sd(s4, sp, 0x120);
    s4 = a1;
    sd(s5, sp, 0x128);
    s5 = a0;
    a1 = 0;
    a0 = sp;
    sd(s3, sp, 0x118);
    s3 = 0;
    sd(s6, sp, 0x130);
    s6 = 0;
    sd(fp, sp, 0x140);
    sd(s0, sp, 0x100);
    sd(s1, sp, 0x108);
    sd(s2, sp, 0x110);
    sd(s7, sp, 0x138);
    sd(ra, sp, 0x148);
    fp = 0;
    jal(ctx, 0x55CB78u, gen::fn_memset_00521408);
    v1 = slti(s4, 14);
    v0 = 13;
    if (v1 == 0) s4 = v0;
    if (i64(s4) <= 0) {
        a0 = 0x7C0000;
    } else {
        // 0x0055cb94
        charge(ctx, 3);
        v0 = 0x7A0000;
        s2 = s5;
        s7 = addiu(v0, 12320);  // &0x7A3020
        for (;;) {
            // 0x0055cba0
            charge(ctx, 14);
            lw(v1, s7, 12);
            a1 = sp;
            lw(v0, s7, 8);
            mult(a0, v1, s3);
            v0 = sll(v0, 3);
            v1 = addu(a0, s3);
            s3 = addiu(s3, 1);
            v0 = addu(v0, v1);
            s1 = addu(s5, v0);
            a0 = s1;
            jal(ctx, 0x55CBC4u, gen::fn_sub_55C610_0055c610);
            lb(v0, s1, 0);
            a0 = 26112;
            if (v0 != 0) {
                // 0x0055cbd8
                charge(ctx, 11);
                jal(ctx, 0x55CBD8u, gen::fn_sub_558988_00558988);
                a1 = 1;
                a0 = sp;
                jal(ctx, 0x55CBE4u, gen::fn_sub_558C98_00558c98);
                a0 = 26113;
                s0 = v0;
                jal(ctx, 0x55CBF0u, gen::fn_sub_558988_00558988);
                a1 = sp;
                a0 = s0;
                if (i64(s0) >= 0) {
                    // 0x0055cc20
                    charge(ctx, 24);
                    sw(s0, s2, 0);
                    s6 = addiu(s6, 1);
                    jal(ctx, 0x55CC24u, gen::fn_sub_55BCE8_0055bce8);
                    v1 = 0x7C0000;
                    v0 = dsll32(v0, 0);
                    v0 = dsra32(v0, 0);
                    a0 = addiu(v1, 21376);  // "HTCI: \"%s\" Opened.(sceOpen)\n"
                    sw(v0, s2, 4);
                    a1 = s1;
                    jal(ctx, 0x55CC40u, gen::fn_sub_5416E8_005416e8);
                    a0 = 26624;
                    jal(ctx, 0x55CC48u, gen::fn_sub_558988_00558988);
                    a0 = s0;
                    jal(ctx, 0x55CC50u, gen::fn_sub_558D00_00558d00);
                    a0 = 26625;
                    jal(ctx, 0x55CC58u, gen::fn_sub_558988_00558988);
                    a0 = 26368;
                    jal(ctx, 0x55CC60u, gen::fn_sub_558988_00558988);
                    v0 = 0x7A0000;
                    lw(a1, v0, 12336);  // 0x7A3030
                    a0 = sp;
                    jal(ctx, 0x55CC70u, gen::fn_sub_558C98_00558c98);
                    a0 = 26369;
                    jal(ctx, 0x55CC78u, gen::fn_sub_558988_00558988);
                    goto L_0055cc80;
                }
                // 0x0055cc04
                charge(ctx, 6);
                v0 = 0x7C0000;
                fp = addiu(fp, 0x1);
                a0 = addiu(v0, 21336);  // "HTCI: \"%s\" can't Open.(sceOpen)\n"
                jal(ctx, 0x55CC0Cu, gen::fn_sub_5416E8_005416e8);
                v0 = slt(s3, s4);
                goto L_0055cc84;
            }
        L_0055cc80:
            charge(ctx, 1);
            v0 = slt(s3, s4);
        L_0055cc84:
            charge(ctx, 2);
            s2 = addiu(s2, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0055cc8c
        charge(ctx, 1);
        a0 = 0x7C0000;
    }
    // 0x0055cc90
    charge(ctx, 5);
    a1 = s6;
    a0 = addiu(a0, 21408);
    jal(ctx, 0x55CC94u, gen::fn_sub_5416E8_005416e8);
    v0 = s6;
    if (i64(fp) > 0) {
        // 0x0055cca4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 10;
        a0 = addiu(a0, 21432);  // "HTCI: Error, Can't load all cache file.%c"
        jal(ctx, 0x55CCACu, gen::fn_sub_541760_00541760);
        v0 = s6;
    }
    // 0x0055ccb8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x100);
    ld(s1, sp, 0x108);
    ld(s2, sp, 0x110);
    ld(s3, sp, 0x118);
    ld(s4, sp, 0x120);
    ld(s5, sp, 0x128);
    ld(s6, sp, 0x130);
    ld(s7, sp, 0x138);
    ld(fp, sp, 0x140);
    ld(ra, sp, 0x148);
    sp = addiu(sp, 0x150);
}

// 0x0055CCE8 sub_55CCE8 -- 304 bytes; frame 0x150: s6 sp+0x130, s0 sp+0x100, s1 sp+0x108, s2 sp+0x110, s3 sp+0x118, s4 sp+0x120, s5 sp+0x128, s7 sp+0x138, fp sp+0x140, ra sp+0x148
// HTCI: close every cached file and clear the table ('HTCI: ... Closed', the total).
void sub_55CCE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0055cce8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    v0 = 0x7A0000;
    sd(s6, sp, 0x130);
    s6 = 0;
    sd(s0, sp, 0x100);
    v1 = addiu(v0, 12320);  // &0x7A3020
    sd(s1, sp, 0x108);
    sd(s2, sp, 0x110);
    sd(s3, sp, 0x118);
    sd(s4, sp, 0x120);
    sd(s5, sp, 0x128);
    sd(s7, sp, 0x138);
    sd(fp, sp, 0x140);
    sd(ra, sp, 0x148);
    lw(s3, v1, 0);  // 0x7A3020
    v0 = 0;
    if (s3 != 0) {
        // 0x0055cd2c
        charge(ctx, 3);
        lw(s4, v1, 4);
        s1 = 0;
        if (s4 != 0) {
            // 0x0055cd38
            charge(ctx, 4);
            s5 = v1;
            fp = 0x7C0000;
            s7 = 0x7C0000;
            s2 = s3;
            for (;;) {
                // 0x0055cd48
                charge(ctx, 14);
                lw(v0, s5, 12);
                a1 = sp;
                lw(s0, s5, 8);
                mult(v1, v0, s1);
                s0 = sll(s0, 3);
                v0 = addu(v1, s1);
                s1 = addiu(s1, 1);
                s0 = addu(s0, v0);
                s0 = addu(s3, s0);
                a0 = s0;
                jal(ctx, 0x55CD6Cu, gen::fn_sub_55C610_0055c610);
                lb(v0, s0, 0);
                a0 = 26880;
                if (v0 != 0) {
                    // 0x0055cd80
                    charge(ctx, 10);
                    jal(ctx, 0x55CD80u, gen::fn_sub_558988_00558988);
                    link(ctx, 0x55CD88u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, 0);
                    call(ctx, gen::fn_sub_558D00_00558d00);
                    a0 = 26881;
                    s0 = v0;
                    jal(ctx, 0x55CD94u, gen::fn_sub_558988_00558988);
                    a1 = sp;
                    a0 = addiu(s7, 21520);
                    if (i64(s0) >= 0) {
                        // 0x0055cdb8
                        charge(ctx, 2);
                        s6 = addiu(s6, 1);
                        jal(ctx, 0x55CDB8u, gen::fn_sub_541760_00541760);
                        goto L_0055cdc0;
                    }
                    // 0x0055cda8
                    charge(ctx, 4);
                    a0 = addiu(fp, 0x53E8);
                    jal(ctx, 0x55CDA8u, gen::fn_sub_541760_00541760);
                    v0 = sltu(s1, s4);
                    goto L_0055cdc4;
                }
            L_0055cdc0:
                charge(ctx, 1);
                v0 = sltu(s1, s4);
            L_0055cdc4:
                charge(ctx, 2);
                s2 = addiu(s2, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0055cdcc
        charge(ctx, 7);
        a0 = 0x7C0000;
        a1 = s6;
        a0 = addiu(a0, 21552);  // "HTCI: Total %d files\n"
        jal(ctx, 0x55CDD4u, gen::fn_sub_541760_00541760);
        jal(ctx, 0x55CDDCu, gen::fn_sub_55CEE0_0055cee0);
        v0 = 1;
    }
    // 0x0055cde8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x100);
    ld(s1, sp, 0x108);
    ld(s2, sp, 0x110);
    ld(s3, sp, 0x118);
    ld(s4, sp, 0x120);
    ld(s5, sp, 0x128);
    ld(s6, sp, 0x130);
    ld(s7, sp, 0x138);
    ld(fp, sp, 0x140);
    ld(ra, sp, 0x148);
    sp = addiu(sp, 0x150);
}

// 0x0055CE18 sub_55CE18 -- 200 bytes; frame 0x40: s4 sp+0x20, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s6 sp+0x30, s1 sp+0x8, s5 sp+0x28, ra sp+0x38
// HTCI: look the name $a1 up in the table $a2 ($a3 entries); copy its descriptor and size to $a0, or zeros.
void sub_55CE18(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ce18
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s1, sp, 0x8);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    if (i64(s4) > 0) {
        // 0x0055ce54
        charge(ctx, 3);
        v0 = 0x7A0000;
        s1 = s2;
        s5 = addiu(v0, 12320);  // &0x7A3020
        for (;;) {
            // 0x0055ce60
            charge(ctx, 12);
            lw(v0, s5, 12);
            a0 = s6;
            lw(a1, s5, 8);
            mult(v1, v0, s0);
            a1 = sll(a1, 3);
            v0 = addu(v1, s0);
            s0 = addiu(s0, 1);
            a1 = addu(a1, v0);
            a1 = addu(s2, a1);
            jal(ctx, 0x55CE80u, gen::fn_sub_55C798_0055c798);
            v1 = slt(s0, s4);
            if (v0 == 0) {
                goto L_0055ce90_3;
            }
            // 0x0055cea8
            charge(ctx, 2);
            s1 = addiu(s1, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055ceb0
    charge(ctx, 2);
    sw(zero, s3, 4);
    sw(zero, s3, 0);
    // 0x0055ceb8 (the shared epilogue, written out on this path)
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
    return;
L_0055ce90_3:
    charge(ctx, 5);
    lw(v0, s1, 0);
    sw(v0, s3, 0);
    lw(v1, s1, 4);
    sw(v1, s3, 4);
    // 0x0055ceb8 (the shared epilogue, written out on this path)
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
}

// 0x0055D108 sub_55D108 -- 128 bytes; frame 0x10: ra sp+0x0
// Sets the root directory 0x7A3038 to a copy of $a0; null clears it. When $a0 starts with neither '/' nor '\' it
// first writes "/" there, but the tail call is strcpy (not strcat) to the same address, so the copy overwrites it:
// the result is $a0 as given (the retail behaviour, kept; the pair test checks it).
void sub_55D108(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055d108
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055d118
        charge(ctx, 5);
        ld(ra, sp, 0x0);
        v0 = 0x7A0000;
        sb(zero, v0, 12344);  // 0x7A3038
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055d130
    charge(ctx, 4);
    lb(a0, a0, 0);
    v0 = 47;
    cc = a0 == v0;  // the condition, before the delay slot changes it
    v0 = 92;
    if (!cc) {
        // 0x0055d140
        charge(ctx, 2);
        cc = a0 == v0;  // the condition, before the delay slot changes it
        a0 = 0x7A0000;
        if (cc) {
            goto L_0055d170;
        }
        // 0x0055d148
        charge(ctx, 9);
        v0 = 0x7C0000;
        t0 = addiu(v0, 21328);  // &0x7C5350
        a3 = addiu(a0, 12344);
        lb(v1, t0, 0);  // 0x7C5350
        lb(a2, t0, 1);  // 0x7C5351
        sb(v1, a3, 0);
        sb(a2, a3, 1);
        ld(ra, sp, 0x0);
        goto L_0055d17c;
    }
L_0055d170:
    charge(ctx, 3);
    a0 = 0x7A0000;
    sb(zero, a0, 12344);  // 0x7A3038
    ld(ra, sp, 0x0);
L_0055d17c:
    charge(ctx, 3);
    a0 = addiu(a0, 12344);
    sp = addiu(sp, 0x10);
    gen::fn_strcpy_00524270(ctx);  // tail call
}

// 0x0055D198 sub_55D198 -- 100 bytes; frame 0x10: ra sp+0x0
// Sets the device prefix 0x7A3140 from $a0, or 'host:' when null.
void sub_55D198(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d198
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055d1e8
        charge(ctx, 5);
        a0 = 0x7A0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 12608);  // &0x7A3140
        sp = addiu(sp, 0x10);
        gen::fn_strcpy_00524270(ctx);  // tail call
        return;
    }
    // 0x0055d1a8
    charge(ctx, 15);
    v1 = 0x7A0000;
    v0 = 0x7C0000;
    a3 = addiu(v0, 21760);  // "host:"
    a2 = addiu(v1, 12608);  // &0x7A3140
    lwl(a0, a3, 3);  // 0x7C5503
    lwr(a0, a3, 0);  // 0x7C5500
    lb(a1, a3, 4);  // 0x7C5504
    swl(a0, a2, 3);  // 0x7A3143
    swr(a0, a2, 0);  // 0x7A3140
    sb(a1, a2, 4);  // 0x7A3144
    lb(a0, a3, 5);  // 0x7C5505
    sb(a0, a2, 5);  // 0x7A3145
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055D220 WTLS_set_table -- 12 bytes; leaf frame (no stack)
// WTLS_set_table: stores $a0 at 0x7A3034.
void WTLS_set_table(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0055d220
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sw(a0, v0, 12340);  // 0x7A3034
}

// 0x0055D400 sub_55D400 -- 36 bytes; frame 0x10: ra sp+0x0
// Tail call: sub_55D428($a0, $a1, 0, 0, 0xFFFFF).
void sub_55D400(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d400
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0xF0000;
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = t0 | 0xFFFF;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D428_0055d428(ctx);  // tail call
}

// 0x0055D7F0 sub_55D7F0 -- 144 bytes; frame 0x10: ra sp+0x0
// LSC: the stream id of queue slot $a1 (ring of 16 at +56, stride 32, from the head +32). Null / bad slot ->
// 'E2005012811' / '12', -1.
void sub_55D7F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d7f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a0;
    sd(ra, sp, 0x0);
    v1 = a1;
    if (a2 != 0) {
        // 0x0055d818
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (i64(v1) >= 0) {
            // 0x0055d820
            charge(ctx, 4);
            lw(v0, a2, lsc::kCount);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                // 0x0055d830
                charge(ctx, 1);
                a0 = 0x7C0000;
                goto L_0055d834;
            }
            lw(a1, a2, lsc::kHead);
            // 0x0055d848
            charge(ctx, 11);
            a1 = addu(a1, v1);
            a0 = addiu(a1, 15);
            v1 = slti(a1, 0);
            v0 = a1;
            if (v1 != 0) v0 = a0;
            v0 = sra(v0, 4);
            a0 = sll(v0, 4);
            v0 = subu(a1, a0);
            v1 = sll(v0, 5);
            v1 = addu(v1, a2);
            lw(v0, v1, 56);
            // 0x0055d874 (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0055d834:
        charge(ctx, 4);
        a0 = addiu(a0, 22296);
        jal(ctx, 0x55D834u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    } else {
        // 0x0055d804
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22248);  // "E2005012811: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D808u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    }
    // 0x0055d874 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055D880 sub_55D880 -- 148 bytes; frame 0x10: ra sp+0x0
// LSC: the word +60 of the stream with id $a1. Null / unknown id -> 'E2005012813' / '14', 0.
void sub_55D880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d880
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055d8a0
        charge(ctx, 4);
        a2 = addiu(a0, 56);
        lw(v0, a2, 0);
        v1 = 0;
        if (v0 != a1) {
            // 0x0055d8b0
            charge(ctx, 2);
            v1 = addiu(v1, 1);
            for (;;) {
                // 0x0055d8b8
                charge(ctx, 3);
                v0 = slti(v1, 16);
                a2 = addiu(a2, 32);
                if (v0 != 0) {
                    // 0x0055d8c4
                    charge(ctx, 6);
                    lw(v0, a2, 0);
                    if (v0 != a1) {
                        v1 = addiu(v1, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x0055d8dc
        charge(ctx, 3);
        v0 = 16;
        if (v1 != v0) {
            v1 = sll(v1, 5);
            // 0x0055d900
            charge(ctx, 2);
            v1 = addu(v1, a0);
            lw(v0, v1, 60);
        } else {
            // 0x0055d8e8
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 22384);  // "E2005012814: Can not find stream ID =%d\n"
            jal(ctx, 0x55D8ECu, gen::fn_sub_55DBE8_0055dbe8);
            v0 = 0;
        }
    } else {
        // 0x0055d88c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22336);  // "E2005012813: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D890u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = 0;
    }
    // 0x0055d908 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055D918 sub_55D918 -- 148 bytes; frame 0x10: ra sp+0x0
// LSC: the word +80 of the stream with id $a1. Null / unknown id -> 'E2005012815' / '16', -1.
void sub_55D918(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d918
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055d938
        charge(ctx, 4);
        a2 = addiu(a0, 56);
        lw(v0, a2, 0);
        v1 = 0;
        if (v0 != a1) {
            // 0x0055d948
            charge(ctx, 2);
            v1 = addiu(v1, 1);
            for (;;) {
                // 0x0055d950
                charge(ctx, 3);
                v0 = slti(v1, 16);
                a2 = addiu(a2, 32);
                if (v0 != 0) {
                    // 0x0055d95c
                    charge(ctx, 6);
                    lw(v0, a2, 0);
                    if (v0 != a1) {
                        v1 = addiu(v1, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x0055d974
        charge(ctx, 3);
        v0 = 16;
        if (v1 != v0) {
            v1 = sll(v1, 5);
            // 0x0055d998
            charge(ctx, 2);
            v1 = addu(v1, a0);
            lw(v0, v1, 80);
        } else {
            // 0x0055d980
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 22480);  // "E2005012816: Can not find stream ID =%d\n"
            jal(ctx, 0x55D984u, gen::fn_sub_55DBE8_0055dbe8);
            v0 = si(-1);
        }
    } else {
        // 0x0055d924
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22432);  // "E2005012815: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D928u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    }
    // 0x0055d9a0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055D9B0 sub_55D9B0 -- 148 bytes; frame 0x10: ra sp+0x0
// LSC: the word +84 of the stream with id $a1. Null / unknown id -> 'E2005012817' / '18', 0.
void sub_55D9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055d9b0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055d9d0
        charge(ctx, 4);
        a2 = addiu(a0, 56);
        lw(v0, a2, 0);
        v1 = 0;
        if (v0 != a1) {
            // 0x0055d9e0
            charge(ctx, 2);
            v1 = addiu(v1, 1);
            for (;;) {
                // 0x0055d9e8
                charge(ctx, 3);
                v0 = slti(v1, 16);
                a2 = addiu(a2, 32);
                if (v0 != 0) {
                    // 0x0055d9f4
                    charge(ctx, 6);
                    lw(v0, a2, 0);
                    if (v0 != a1) {
                        v1 = addiu(v1, 1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x0055da0c
        charge(ctx, 3);
        v0 = 16;
        if (v1 != v0) {
            v1 = sll(v1, 5);
            // 0x0055da30
            charge(ctx, 2);
            v1 = addu(v1, a0);
            lw(v0, v1, 84);
        } else {
            // 0x0055da18
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 22576);  // "E2005012818: Can not find stream ID =%d\n"
            jal(ctx, 0x55DA1Cu, gen::fn_sub_55DBE8_0055dbe8);
            v0 = 0;
        }
    } else {
        // 0x0055d9bc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22528);  // "E2005012817: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55D9C0u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = 0;
    }
    // 0x0055da38 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055DAB0 sub_55DAB0 -- 48 bytes; frame 0x10: ra sp+0x0
// LSC: returns the word +20. Null -> 'E2005012821' and -1.
void sub_55DAB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055dab0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0055dad0
        charge(ctx, 1);
        lw(v0, a0, lsc::kWord20);
    } else {
        // 0x0055dabc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 22720);  // "E2005012821: Illigal parameter lsc=NULL\n"
        jal(ctx, 0x55DAC0u, gen::fn_sub_55DBE8_0055dbe8);
        v0 = si(-1);
    }
    // 0x0055dad4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055DB20 sub_55DB20 -- 52 bytes; frame 0x10: ra sp+0x0
// LSC: calls the end-of-queue callback 0x7A3168(0x7A316C, 0x7A3170) when one is set.
void sub_55DB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0055db20
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7A0000;
    sp = addiu(sp, -0x10);
    lw(a2, v0, 12648);  // 0x7A3168
    sd(ra, sp, 0x0);
    if (a2 != 0) {
        // 0x0055db34
        charge(ctx, 5);
        v0 = 0x7A0000;
        v1 = 0x7A0000;
        lw(a0, v0, 12652);  // 0x7A316C
        jt = a2.u();  // the target, read before the delay slot
        link(ctx, 0x55DB40u);  // $ra = the return address
        lw(a1, v1, 12656);
        call_ptr(ctx, jt);
    }
    // 0x0055db48 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055DC80 __env_unlock_7 -- 8 bytes; leaf frame (no stack)
// Empty.
void __env_unlock_7(EEContext& ctx) {
    using namespace hg;
    // 0x0055dc80
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0055DDC8 sub_55DDC8 -- 296 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// LSC server: start the head stream -- check the name checksum ('E0013: ...' on a mismatch), then open, seek and
// start the reader (sub_5460E0 ..) and mark it running.
void sub_55DDC8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ddc8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s0, lsc::kHead);
    lw(v1, s0, lsc::kCount);
    v0 = sll(v0, 5);
    v0 = addu(s0, v0);
    s1 = addiu(v0, 56);
    if (i64(v1) <= 0) {
        // 0x0055ded8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055ddf8
    charge(ctx, 11);
    link(ctx, 0x55DDF8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, lsc::kFp);
    call(ctx, gen::fn_sub_5465A0_005465a0);
    link(ctx, 0x55DE00u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, lsc::kFp);
    call(ctx, gen::fn_sub_546270_00546270);
    lw(s2, s1, lsc::ent::kName);
    a0 = s2;
    jal(ctx, 0x55DE0Cu, gen::fn_strlen_00524388);
    a1 = 0;
    a2 = v0;
    a3 = 0;
    if (a2 != 0) {
        // 0x0055de24
        charge(ctx, 1);
        for (;;) {
            // 0x0055de28
            charge(ctx, 7);
            v0 = addu(s2, a1);
            a1 = addiu(a1, 1);
            lbu(v1, v0, 0);
            a0 = sltu(a1, a2);
            a3 = addu(a3, v1);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055de44
    charge(ctx, 3);
    lw(v0, s1, lsc::ent::kSum);
    a0 = 0x7C0000;
    if (a3 != v0) {
        // 0x0055de50
        charge(ctx, 8);
        lw(a1, s1, lsc::ent::kName);
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 22864);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
        return;
    }
    // 0x0055de70
    charge(ctx, 26);
    lw(a3, s1, lsc::ent::kSize);
    lw(t0, s1, lsc::ent::kWord20);
    lw(a2, s1, lsc::ent::kOffset);
    lw(a0, s0, lsc::kFp);
    link(ctx, 0x55DE80u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, lsc::ent::kName);
    call(ctx, gen::fn_sub_5460E0_005460e0);
    lw(a0, s0, lsc::kFp);
    link(ctx, 0x55DE8Cu);  // $ra first: the delay slot below depends on it
    lw(a1, s1, lsc::ent::kWord20);
    call(ctx, gen::fn_sub_546718_00546718);
    lw(v0, s1, lsc::ent::kWord20);
    lw(a0, s0, lsc::kFp);
    sw(v0, s0, lsc::kPos);
    sw(zero, s1, lsc::ent::kPos);
    sb(zero, s0, lsc::kSvr);
    lw(a2, s0, lsc::kWord24);
    link(ctx, 0x55DEACu);  // $ra first: the delay slot below depends on it
    lw(a1, s0, lsc::kWord20);
    call(ctx, gen::fn_sub_546FA0_00546fa0);
    lw(a0, s0, lsc::kFp);
    a1 = 0;
    jal(ctx, 0x55DEB8u, gen::fn_sub_5463A8_005463a8);
    link(ctx, 0x55DEC0u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, lsc::kFp);
    call(ctx, gen::fn_sub_546498_00546498);
    v1 = 1;
    v0 = 1;
    sb(v1, s0, lsc::kSvr);
    sw(v0, s1, lsc::ent::kStat);
    // 0x0055ded8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0055DEF0 sub_55DEF0 -- 196 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// LSC server: poll the reader of the head stream (sub_546368): 3 -> done (2), 2 -> running (its position), 4 -> error
// status; no reader -> 'E0007: lsc->fp=NULL'.
void sub_55DEF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055def0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(a0, s0, lsc::kFp);
    if (a0 == 0) {
        // 0x0055df10
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 22928);  // "E0007: lsc->fp=NULL\n"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_55DBE8_0055dbe8(ctx);  // tail call
        return;
    }
    lw(v0, s0, lsc::kHead);
    // 0x0055df30
    charge(ctx, 8);
    v0 = sll(v0, 5);
    v0 = addu(s0, v0);
    s1 = addiu(v0, 56);
    jal(ctx, 0x55DF38u, gen::fn_sub_546368_00546368);
    v1 = v0;
    a0 = 3;
    v0 = slti(v1, 4);
    if (v1 == a0) {
        // 0x0055df90
        charge(ctx, 4);
        lw(v1, s0, lsc::kPos);
        v0 = 2;
        sw(v0, s1, lsc::ent::kStat);
        sw(v1, s1, lsc::ent::kPos);
    L_0055dfa0:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x0055df50
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (cc) {
            // 0x0055df70
            charge(ctx, 2);
            if (v1 == v0) {
                sb(a0, s0, lsc::kStat);
                goto L_0055dfa0;
            }
            // 0x0055df78
            charge(ctx, 2);
            ld(s0, sp, 0x0);
        } else {
            // 0x0055df58
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x0055df80
                charge(ctx, 4);
                link(ctx, 0x55DF80u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, lsc::kFp);
                call(ctx, gen::fn_sub_546410_00546410);
                sw(v0, s1, lsc::ent::kPos);
                goto L_0055dfa0;
            }
            // 0x0055df64
            charge(ctx, 2);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0055dfa4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055DFB8 sub_55DFB8 -- 260 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s1 sp+0x8, ra sp+0x30
// LSC server: pop the head stream (advance the ring, count down +36, end-of-queue callback at 0) and re-queue it when
// the loop flag +3 is 1.
void sub_55DFB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055dfb8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s4, sp, 0x20);
    s4 = 0;
    sd(s5, sp, 0x28);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x30);
    lw(v0, s0, lsc::kFp);
    s5 = 0;
    if (v0 != 0) {
        // 0x0055dff4
        charge(ctx, 4);
        lb(v0, s0, lsc::kLoop);
        s1 = 1;
        lbu(a3, s0, lsc::kLoop);
        if (v0 != s1) {
            // 0x0055e028
            charge(ctx, 1);
            lw(a2, s0, lsc::kHead);
        } else {
            // 0x0055e004
            charge(ctx, 9);
            lw(a2, s0, lsc::kHead);
            v0 = sll(a2, 5);
            v0 = addu(s0, v0);
            v0 = addiu(v0, 56);
            lw(s5, v0, 20);
            lw(s4, v0, 16);
            lw(s3, v0, 4);
            lw(s2, v0, 12);
        }
        // 0x0055e02c
        charge(ctx, 13);
        a0 = addiu(a2, 1);
        a2 = addiu(a2, 16);
        a1 = slti(a0, 0);
        v0 = a0;
        if (a1 != 0) v0 = a2;
        lw(v1, s0, lsc::kCount);
        v0 = sra(v0, 4);
        v0 = sll(v0, 4);
        v1 = addiu(v1, -1);
        a0 = subu(a0, v0);
        sw(v1, s0, lsc::kCount);
        sw(a0, s0, lsc::kHead);
        if (i64(v1) <= 0) {
            // 0x0055e060
            charge(ctx, 4);
            jal(ctx, 0x55E060u, gen::fn_sub_55DB20_0055db20);
            sb(s1, s0, lsc::kStat);
            lbu(a3, s0, lsc::kLoop);
        }
        // 0x0055e070
        charge(ctx, 4);
        v0 = sll(a3, 24);
        v0 = sra(v0, 24);
        if (v0 == s1) {
            // 0x0055e080
            charge(ctx, 6);
            a0 = s0;
            a1 = s3;
            a2 = s2;
            a3 = s4;
            t0 = s5;
            jal(ctx, 0x55E090u, gen::fn_sub_55D428_0055d428);
            goto L_0055e098;
        }
        ld(s0, sp, 0x0);
        // 0x0055e09c (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_0055e098:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0055e09c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0055E208 sub_55E208 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail call: strtoul.
void sub_55E208(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e208
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_strtoul_00525e98(ctx);  // tail call
}

// 0x0055E318 sub_55E318 -- 8 bytes; leaf frame (no stack)
// Empty.
void sub_55E318(EEContext& ctx) {
    using namespace hg;
    // 0x0055e318
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0055E408 sub_55E408 -- 28 bytes; frame 0x10: ra sp+0x0
// Clears 56 bytes at $a0.
void sub_55E408(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e408
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 56;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055E800 sub_55E800 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Under the lock: clears the status byte +1 of $a0. Null -> 'E0092912:handl is null.'
void sub_55E800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e800
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x0055e830
        charge(ctx, 7);
        jal(ctx, 0x55E830u, gen::fn_sub_55E190_0055e190);
        sb(zero, s0, 1);
        ld(ra, sp, 0x8);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_55E1A8_0055e1a8(ctx);  // tail call
        return;
    }
    // 0x0055e814
    charge(ctx, 6);
    a1 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a1 = addiu(a1, 23432);  // "E0092912:handl is null."
    sp = addiu(sp, 0x10);
    gen::fn_sub_55E1D8_0055e1d8(ctx);  // tail call
}

// 0x0055EAB0 sub_55EAB0 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// PL2 encoder: under the lock, set the error callback (sub_55EAF0).
void sub_55EAB0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055eab0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x55EAC4u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x55EAD0u, gen::fn_sub_55EAF0_0055eaf0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055EAF0 sub_55EAF0 -- 20 bytes; leaf frame (no stack)
// PL2 encoder: the error callback 0x7A843C = $a0 and its argument 0x7A8440 = $a1.
void sub_55EAF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055eaf0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v1 = 0x7B0000;
    sw(a0, v0, -31684);  // 0x7A843C
    sw(a1, v1, -31680);  // 0x7A8440
}

// 0x0055EB38 sub_55EB38 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PL2 encoder init: under the lock, sub_55EB68.
void sub_55EB38(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055eb38
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55EB44u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    jal(ctx, 0x55EB4Cu, gen::fn_sub_55EB68_0055eb68);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055EB68 sub_55EB68 -- 60 bytes; frame 0x10: ra sp+0x0
// PL2 encoder init: compare the version string with itself (keeps it linked) and count the init (0x7A8438).
void sub_55EB68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055eb68
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7B0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, -31736);  // "\nPL2ENC Ver.1.01 Build:Feb 28 2005 19:25:06\n"
    a2 = 360;
    a1 = a0;
    jal(ctx, 0x55EB7Cu, gen::fn_memcmp_005211b8);
    v1 = 0x7B0000;
    v1 = addiu(v1, -31688);  // &0x7A8438
    ld(ra, sp, 0x0);
    lw(v0, v1, 0);  // 0x7A8438
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x7A8438
    sp = addiu(sp, 0x10);
}

// 0x0055EBA8 sub_55EBA8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PL2 encoder finish: under the lock, sub_55EBD8.
void sub_55EBA8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055eba8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55EBB4u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    jal(ctx, 0x55EBBCu, gen::fn_sub_55EBD8_0055ebd8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055EBD8 sub_55EBD8 -- 24 bytes; leaf frame (no stack)
// PL2 encoder finish: count the init down (0x7A8438).
void sub_55EBD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0055ebd8
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    v1 = addiu(v1, -31688);  // &0x7A8438
    lw(v0, v1, 0);  // 0x7A8438
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7A8438
}

// 0x0055EBF0 sub_55EBF0 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// PL2 encoder create: under the lock, sub_55EC38($a0, $a1); returns the handle.
void sub_55EBF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ebf0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x55EC04u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x55EC10u, gen::fn_sub_55EC38_0055ec38);
    s0 = v0;
    jal(ctx, 0x55EC18u, gen::fn_sub_55EA98_0055ea98);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0055EC38 sub_55EC38 -- 256 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, ra sp+0x20
// PL2 encoder create in the work area $a0 ($a1 bytes, at least 1024): align, clear the 44-byte handle, place the two
// 384-byte delay lines and reset it; errors 'E03090101 / 102 / E03091001'.
void sub_55EC38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ec38
    enter(ctx, 16);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x30);
    v0 = addiu(v0, -31736);  // "\nPL2ENC Ver.1.01 Build:Feb 28 2005 19:25:06\n"
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = a1;
    s2 = a0;
    a0 = v0;
    sd(s0, sp, 0x0);
    a2 = 360;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    a1 = a0;
    jal(ctx, 0x55EC68u, gen::fn_memcmp_005211b8);
    if (s2 == 0) {
        // 0x0055ec78
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 24672);  // "E03090101 : NULL pointer is specified."
        goto L_0055ed10;
    }
    v0 = slti(s3, 1024);
    // 0x0055ec88
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0055ec90
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 24712);  // "E03090102 : Work size is too short."
        goto L_0055ed10;
    }
    v0 = s2 & 0x3;
    // 0x0055eca0
    charge(ctx, 2);
    s0 = s2;
    if (v0 != 0) {
        // 0x0055eca8
        charge(ctx, 2);
        v0 = subu(s2, v0);
        s0 = addiu(v0, 4);
    }
    // 0x0055ecb0
    charge(ctx, 10);
    s1 = s0;
    a1 = 0;
    a0 = s1;
    a2 = 44;
    s0 = addiu(s1, 44);
    jal(ctx, 0x55ECC0u, gen::fn_memset_00521408);
    v0 = s0 & 0x3;
    sw(s2, s1, pl2::kWork);
    sw(s3, s1, pl2::kWorkSize);
    if (v0 != 0) {
        // 0x0055ecd8
        charge(ctx, 2);
        v0 = subu(s0, v0);
        s0 = addiu(v0, 4);
    }
    // 0x0055ece0
    charge(ctx, 10);
    v0 = addiu(s0, 384);
    sw(s0, s1, pl2::kDelay0);
    sw(v0, s1, pl2::kDelay1);
    a0 = s1;
    jal(ctx, 0x55ECECu, gen::fn_sub_55EDB8_0055edb8);
    v1 = addiu(s0, 768);
    v0 = addu(s2, s3);
    v0 = sltu(v0, v1);
    if (v0 == 0) {
        v0 = s1;
    } else {
        // 0x0055ed08
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 24752);  // "E03091001 : Work size is too short."
    L_0055ed10:
        charge(ctx, 3);
        jal(ctx, 0x55ED10u, gen::fn_sub_55EB08_0055eb08);
        v0 = 0;
    }
    // 0x0055ed1c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055ED38 sub_55ED38 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PL2 encoder destroy: under the lock, sub_55ED68.
void sub_55ED38(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ed38
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55ED44u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    jal(ctx, 0x55ED4Cu, gen::fn_sub_55ED68_0055ed68);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055ED68 sub_55ED68 -- 28 bytes; frame 0x10: ra sp+0x0
// PL2 encoder destroy: clears the 44-byte handle.
void sub_55ED68(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ed68
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a2 = 44;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0055ED88 sub_55ED88 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// PL2 encoder reset: under the lock, sub_55EDB8.
void sub_55ED88(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ed88
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x55ED94u, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    jal(ctx, 0x55ED9Cu, gen::fn_sub_55EDB8_0055edb8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055EDF8 sub_55EDF8 -- 96 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// PL2 encoder: under the lock, encode one sample (sub_55EE58).
void sub_55EDF8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055edf8
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = sll(a1, 16);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(ra, sp, 0x20);
    s0 = sra(s0, 16);
    jal(ctx, 0x55EE20u, gen::fn_sub_55EA80_0055ea80);
    a0 = s1;
    a1 = s0;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x55EE34u, gen::fn_sub_55EE58_0055ee58);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055EE58 sub_55EE58 -- 368 bytes; frame 0x10: s0 sp+0x0
// PL2 encoder: one sample -- the input s16 $a1 scaled by the four gain-table entries (0x7C5C60) of the handle, mixed
// with the two delay lines (+8, +12) and written saturated to *$a2 / *$a3.
void sub_55EE58(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, t8{ctx, 24}, sp{ctx, 29};
    // 0x0055ee58
    enter(ctx, 88);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t8 = a0;
    sd(s0, sp, 0x0);
    t5 = 0x7C0000;
    t5 = addiu(t5, 23648);  // &0x7C5C60
    a1 = sll(a1, 16);
    lw(v1, t8, pl2::kGain0);
    a1 = sra(a1, 16);
    lw(v0, t8, pl2::kGain1);
    t3 = si(-3567);
    v1 = sll(v1, 2);
    t7 = si(-2006);
    v0 = sll(v0, 2);
    v1 = addu(v1, t5);
    v0 = addu(v0, t5);
    lw(a0, v1, 0);
    lw(t0, v0, 0);
    lw(v0, t8, pl2::kGain3);
    mult(a0, a1, a0);
    mult1(a1, a1, t0);
    lw(t0, t8, pl2::kDelay0);
    v0 = sll(v0, 2);
    lw(t2, t8, pl2::kPos);
    v0 = addu(v0, t5);
    lw(t4, t8, pl2::kGain2);
    lw(v1, v0, 0);
    v0 = 3567;
    a0 = sra(a0, 12);
    a1 = sra(a1, 12);
    mult(t1, a1, v1);
    mult1(v1, a0, v1);
    lw(s0, t8, pl2::kDelay1);
    t6 = sll(t2, 2);
    t2 = t6;
    t6 = addu(t6, t0);
    t4 = sll(t4, 2);
    t0 = 2006;
    v1 = sra(v1, 12);
    t1 = sra(t1, 12);
    mult(t3, v1, t3);
    mult1(v1, v1, t0);
    mult1(t7, t1, t7);
    mult(t1, t1, v0);
    t4 = addu(t4, t5);
    t5 = addu(t2, s0);
    t2 = t6;
    lw(v0, t4, 0);
    lw(t0, t5, 0);
    t3 = addu(t3, t7);
    lw(t4, t2, 0);
    t3 = sra(t3, 12);
    mult(a1, a1, v0);
    sw(t3, t6, 0);
    t3 = 32767;
    mult1(a0, a0, v0);
    t1 = addu(t1, v1);
    lw(v0, t8, pl2::kPos);
    t1 = sra(t1, 12);
    a1 = sra(a1, 12);
    t2 = 32767;
    v0 = sll(v0, 2);
    a1 = addu(a1, t0);
    v0 = addu(v0, s0);
    a0 = sra(a0, 12);
    sw(t1, v0, 0);
    v0 = si(-32768);
    a0 = addu(a0, t4);
    t4 = si(-32768);
    lw(t0, t8, pl2::kPos);
    t2 = slt(t2, a0);
    t3 = slt(t3, a1);
    v1 = slti(a1, -32768);
    t5 = slti(a0, -32768);
    lw(t1, t8, pl2::kDelayLen);
    if (v1 != 0) a1 = v0;
    v0 = 32767;
    t0 = addiu(t0, 1);
    if (t5 != 0) a0 = t4;
    t2 = t2 ^ 0x0;
    t3 = t3 ^ 0x0;
    v1 = 32767;
    if (t2 != 0) a0 = v0;
    if (t3 != 0) a1 = v1;
    t1 = slt(t0, t1);
    sh(a0, a2, 0);
    sw(t0, t8, pl2::kPos);
    sh(a1, a3, 0);
    if (t1 == 0) {
        // 0x0055efb8
        charge(ctx, 1);
        sw(zero, t8, pl2::kPos);
    }
    // 0x0055efbc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055F028 sub_55F028 -- 412 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, s7 sp+0x38, fp sp+0x40
// PL2 encoder: 32 samples from $a1 into the two s16 outputs $a2 / $a3, with the gains and delay lines as sub_55EE58.
void sub_55F028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // 0x0055f028
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t7 = a0;
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s1, sp, 0x8);
    v0 = 0x7C0000;
    sd(s2, sp, 0x10);
    s2 = si(-32768);
    sd(s3, sp, 0x18);
    s3 = 32767;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s7, sp, 0x38);
    s7 = 2006;
    sd(fp, sp, 0x40);
    fp = 0xDEF;
    s1 = addiu(v0, 23648);  // &0x7C5C60
    lw(t9, t7, pl2::kDelay1);
    lw(t8, t7, pl2::kDelay0);
    for (;;) {
        // 0x0055f088
        charge(ctx, 68);
        lw(v1, t7, pl2::kGain0);
        t4 = sll(s0, 1);
        lw(v0, t7, pl2::kGain1);
        a0 = addu(t4, s6);
        v1 = sll(v1, 2);
        lh(a1, a0, 0);
        v0 = sll(v0, 2);
        v1 = addu(v1, s1);
        v0 = addu(v0, s1);
        lw(a0, v1, 0);
        lw(a2, v0, 0);
        t6 = 32767;
        lw(v0, t7, pl2::kGain3);
        mult(a0, a1, a0);
        mult1(a1, a1, a2);
        lw(v1, t7, pl2::kGain2);
        v0 = sll(v0, 2);
        lw(a3, t8, 0);
        v0 = addu(v0, s1);
        v1 = sll(v1, 2);
        lw(a2, v0, 0);
        a0 = sra(a0, 12);
        a1 = sra(a1, 12);
        v1 = addu(v1, s1);
        mult(t0, a1, a2);
        mult1(a2, a0, a2);
        lw(v0, v1, 0);
        t5 = 32767;
        lw(v1, t9, 0);
        s0 = addiu(s0, 1);
        mult(a1, a1, v0);
        mult1(a0, a0, v0);
        a2 = sra(a2, 12);
        v0 = si(-3567);
        t0 = sra(t0, 12);
        mult1(t3, a2, s7);
        mult(a2, a2, v0);
        v0 = si(-2006);
        mult(t2, t0, fp);
        mult1(t0, t0, v0);
        a0 = sra(a0, 12);
        a1 = sra(a1, 12);
        a0 = addu(a0, a3);
        a1 = addu(a1, v1);
        v0 = slt(s3, a0);
        v1 = slt(s3, a1);
        a3 = slti(a0, -32768);
        t1 = slti(a1, -32768);
        v0 = v0 ^ 0x0;
        v1 = v1 ^ 0x0;
        a2 = addu(a2, t0);
        t2 = addu(t2, t3);
        if (a3 != 0) a0 = s2;
        if (t1 != 0) a1 = s2;
        if (v0 != 0) a0 = t6;
        v0 = addu(t4, s4);
        if (v1 != 0) a1 = t5;
        v1 = slti(s0, 32);
        a2 = sra(a2, 12);
        t2 = sra(t2, 12);
        t4 = addu(t4, s5);
        sw(a2, t8, 0);
        sh(a0, t4, 0);
        t8 = addiu(t8, 4);
        sw(t2, t9, 0);
        t9 = addiu(t9, 4);
        sh(a1, v0, 0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0055f198
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

// 0x0055F218 sub_55F218 -- 176 bytes; frame 0x10: ra sp+0x0
// PL2 encoder: position $a1 / $a2 (each -127..127) into the four gain indices +28..+40. Null / out of range ->
// 'E03090306' / '307'.
void sub_55F218(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f218
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0055f224
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 24792);  // "E03090306 : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_55EB08_0055eb08(ctx);  // tail call
        return;
    }
    // 0x0055f238
    charge(ctx, 4);
    v1 = addiu(a1, 127);
    v0 = sltiu(v1, 255);
    if (v0 == 0) {
        a0 = 0x7C0000;
    } else {
        // 0x0055f248
        charge(ctx, 3);
        v0 = slti(a2, -127);
        if (v0 != 0) {
            a0 = 0x7C0000;
            goto L_0055f264;
        }
        // 0x0055f254
        charge(ctx, 3);
        v0 = slti(a2, 128);
        a3 = addiu(a1, -127);
        if (v0 == 0) {
            // 0x0055f260
            charge(ctx, 1);
            a0 = 0x7C0000;
            goto L_0055f264;
        }
        // 0x0055f278
        charge(ctx, 2);
        v0 = v1;
        if (i64(v1) < 0) {
            // 0x0055f280
            charge(ctx, 1);
            v0 = subu(0, v0);
        }
        // 0x0055f284
        charge(ctx, 2);
        sw(v0, a0, pl2::kGain0);
        if (i64(a3) < 0) {
            // 0x0055f28c
            charge(ctx, 2);
            v0 = 127;
            a3 = subu(v0, a1);
        }
        // 0x0055f294
        charge(ctx, 4);
        v0 = addiu(a2, 127);
        v1 = addiu(a2, -127);
        if (i64(v0) < 0) {
            v0 = subu(0, v0);
        }
        // 0x0055f2a4
        charge(ctx, 3);
        sw(a3, a0, pl2::kGain1);
        sw(v0, a0, pl2::kGain2);
        if (i64(v1) < 0) {
            // 0x0055f2b0
            charge(ctx, 2);
            v0 = 127;
            v1 = subu(v0, a2);
        }
        // 0x0055f2b8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sw(v1, a0, pl2::kGain3);
        sp = addiu(sp, 0x10);
        return;
    }
L_0055f264:
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 24832);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55EB08_0055eb08(ctx);  // tail call
}

// 0x0055F2C8 sub_55F2C8 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// PL2 encoder: under the lock, set the sample rate (sub_55F308).
void sub_55F2C8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f2c8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x55F2DCu, gen::fn_sub_55EA80_0055ea80);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x55F2E8u, gen::fn_sub_55F308_0055f308);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55EA98_0055ea98(ctx);  // tail call
}

// 0x0055F308 sub_55F308 -- 136 bytes; frame 0x10: ra sp+0x0
// PL2 encoder: sample rate +16 = $a1 and the delay +24 = $a1 / 750 clamped to 1..96. Null / not positive ->
// 'E03091601' / '602'.
void sub_55F308(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f308
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a0;
    sd(ra, sp, 0x0);
    a0 = a1;
    if (a3 == 0) {
        // 0x0055f31c
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 24880);  // "E03091601 : NULL pointer is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_55EB08_0055eb08(ctx);  // tail call
        return;
    }
    // 0x0055f330
    charge(ctx, 2);
    v1 = 750;
    if (i64(a0) <= 0) {
        // 0x0055f338
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 24920);  // "E03091602 : Illegal parameter is specified."
        sp = addiu(sp, 0x10);
        gen::fn_sub_55EB08_0055eb08(ctx);  // tail call
        return;
    }
    // 0x0055f350
    charge(ctx, 4);
    a1 = 1;
    div(a0, v1);
    if (v1 == 0) {
        brk(ctx, 0x55F35Cu, 0x7u);
    }
    // 0x0055f360
    charge(ctx, 12);
    sw(a0, a3, pl2::kRate);
    a2 = 96;
    ld(ra, sp, 0x0);
    mflo(v0);
    v1 = slti(v0, 97);
    a0 = slt(0, v0);
    if (a0 == 0) v0 = a1;
    v1 = v1 ^ 0x0;
    if (v1 == 0) v0 = a2;
    sw(v0, a3, pl2::kDelayLen);
    sp = addiu(sp, 0x10);
}

// 0x0055F390 sub_55F390 -- 308 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// ADXT: attach the Dolby Pro Logic II encoder to the stereo handle $a0 -- create it in $a1 / $a2, set its position
// and install the four hooks; errors 'E2003091101' / 'E2003091002'.
void sub_55F390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f390
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    lb(v0, s0, 3);
    v0 = slti(v0, 2);
    s3 = a1;
    if (v0 != 0) {
        // 0x0055f3c0
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 24968);  // "E2003091101 : ADXT handle must be created for stereo output."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0055f3e8
    charge(ctx, 19);
    jal(ctx, 0x55F3E8u, gen::fn_sub_548678_00548678);
    a0 = s0;
    jal(ctx, 0x55F3F0u, gen::fn_sub_55F4C8_0055f4c8);
    a0 = 0x560000;
    a1 = 0;
    a0 = addiu(a0, -2448);  // &sub_55F670
    jal(ctx, 0x55F400u, gen::fn_sub_55EAB0_0055eab0);
    a0 = 0;
    jal(ctx, 0x55F408u, gen::fn_sub_55EB38_0055eb38);
    lw(v0, s0, 4);
    link(ctx, 0x55F414u);  // $ra first: the delay slot below depends on it
    lw(s1, v0, 4);
    call(ctx, gen::fn_sub_540D40_00540d40);
    a0 = s3;
    a1 = s2;
    jal(ctx, 0x55F420u, gen::fn_sub_55EBF0_0055ebf0);
    s0 = v0;
    a0 = s0;
    if (s0 == 0) {
        // 0x0055f434
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 25032);  // "E2003091002 : Fail to attach Dolby Pro Logic II."
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0055f458
    charge(ctx, 27);
    lw(a1, s1, adxt_pl2::kPos0);
    link(ctx, 0x55F45Cu);  // $ra first: the delay slot below depends on it
    lw(a2, s1, adxt_pl2::kPos1);
    call(ctx, gen::fn_sub_55F1C8_0055f1c8);
    sw(s0, s1, adxt_pl2::kPl2);
    v0 = 0x560000;
    v1 = 0x560000;
    a0 = 0x560000;
    a1 = 0x560000;
    ld(s0, sp, 0x0);
    v0 = addiu(v0, -2664);  // &sub_55F598
    ld(s1, sp, 0x8);
    v1 = addiu(v1, -2528);  // &sub_55F620
    ld(s2, sp, 0x10);
    a0 = addiu(a0, -2552);  // &sub_55F608
    ld(s3, sp, 0x18);
    a1 = addiu(a1, -2472);  // &sub_55F658
    ld(ra, sp, 0x20);
    a2 = 0x790000;
    a3 = 0x780000;
    t0 = 0x780000;
    t1 = 0x790000;
    sw(v0, a2, 15152);  // 0x793B30
    sw(v1, a3, 14556);  // 0x7838DC
    sw(a0, t0, 14560);  // 0x7838E0
    sw(a1, t1, -108);  // 0x78FF94
    sp = addiu(sp, 0x30);
    gen::fn_sub_540D58_00540d58(ctx);  // tail call
}

// 0x0055F4C8 sub_55F4C8 -- 40 bytes; frame 0x10: ra sp+0x0
// Calls the detach hook 0x793B30 when one is set.
void sub_55F4C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f4c8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 15152);  // 0x793B30
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055f4dc
        charge(ctx, 2);
        jalr(ctx, 0x55F4DCu, v0.u());
    }
    // 0x0055f4e4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055F598 sub_55F598 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXT hook: detach the PL2 encoder of the handle (destroy it, clear +232, finish the module).
void sub_55F598(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f598
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v0, a0, 4);
    lw(s1, v0, 4);
    lw(s0, s1, adxt_pl2::kPl2);
    if (s0 == 0) {
        ld(s0, sp, 0x0);
        // 0x0055f5f8
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0055f5bc
    charge(ctx, 14);
    jal(ctx, 0x55F5BCu, gen::fn_sub_548678_00548678);
    jal(ctx, 0x55F5C4u, gen::fn_sub_540D40_00540d40);
    a0 = s0;
    jal(ctx, 0x55F5CCu, gen::fn_sub_55ED38_0055ed38);
    sw(zero, s1, adxt_pl2::kPl2);
    a0 = 0;
    jal(ctx, 0x55F5D8u, gen::fn_sub_55EBA8_0055eba8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_540D58_00540d58(ctx);  // tail call
}

// 0x0055F608 sub_55F608 -- 24 bytes; frame 0x10: ra sp+0x0
// ADXT hook: reset the handle's PL2 encoder (+232).
void sub_55F608(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f608
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt_pl2::kPl2);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55ED88_0055ed88(ctx);  // tail call
}

// 0x0055F620 sub_55F620 -- 32 bytes; frame 0x10: ra sp+0x0
// ADXT hook: encode one sample with the handle's PL2 encoder (+232).
void sub_55F620(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f620
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = sll(a1, 16);
    sd(ra, sp, 0x0);
    a1 = sra(a1, 16);
    lw(a0, a0, adxt_pl2::kPl2);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55EDF8_0055edf8(ctx);  // tail call
}

// 0x0055F658 sub_55F658 -- 24 bytes; frame 0x10: ra sp+0x0
// ADXT hook: set the handle's PL2 encoder sample rate (+232).
void sub_55F658(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f658
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt_pl2::kPl2);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55F2C8_0055f2c8(ctx);  // tail call
}

// 0x0055F670 sub_55F670 -- 24 bytes; frame 0x10: ra sp+0x0
// PL2 error callback: forwards the message $a1 to the ADX error handler sub_53AE08.
void sub_55F670(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f670
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

}  // namespace p3fes::game
