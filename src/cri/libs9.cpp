// Phase 5 slice libs9 (game/include/p3fes/game/libs9.h has the overview): ADXM's thread layer, the ADX encoder, ADXSTM /
// ADXT accessors and the MPEG-audio Layer II decoder. Each body started as p3fes_handgen's faithful body (SLUS_216.21,
// symbols/) and keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h). On top: a role block per function (the proposed name in [brackets]) and the
// handle fields by name -- the ADXT handle from cri2.h, the ADX encoder and MPEG-audio handles from libs9.h.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs9.h"
#include "p3fes/game/cri2.h"

namespace p3fes::recomp_gen {
void fn_ADXM_SetupThrdEx_005411b0(p3fes::EEContext&);
void fn_ADXM_SetupThrd_00540588(p3fes::EEContext&);
void fn_ADXSTMF_ExecHndl_00546bb0(p3fes::EEContext&);
void fn_ADXT_UpdateFsStat_0053e0b8(p3fes::EEContext&);
void fn_WTLS_set_table_0055d220(p3fes::EEContext&);
void fn___errno_0_00540d70(p3fes::EEContext&);
void fn___errno_1_00541628(p3fes::EEContext&);
void fn___errno_2_00547500(p3fes::EEContext&);
void fn__sceChangeThreadPriority_00502ff0(p3fes::EEContext&);
void fn__sceGetThreadId_00503050(p3fes::EEContext&);
void fn__sceReferThreadStatus_00503060(p3fes::EEContext&);
void fn_adxm_SetupFsThrd_00540360(p3fes::EEContext&);
void fn_adxm_SetupMwIdleThrd_005403e8(p3fes::EEContext&);
void fn_adxm_SetupSafeThrd_00540178(p3fes::EEContext&);
void fn_adxm_SetupUsrIdleThrd_00540480(p3fes::EEContext&);
void fn_adxm_SetupUsrVsyncThrd_00540220(p3fes::EEContext&);
void fn_adxm_SetupVsyncThrd_005402d8(p3fes::EEContext&);
void fn_atan2l_6_0054f7a0(p3fes::EEContext&);
void fn_coshl_1_00541a90(p3fes::EEContext&);
void fn_coshl_2_00545c38(p3fes::EEContext&);
void fn_coshl_6_0054f7d0(p3fes::EEContext&);
void fn_cosl_1_00541a78(p3fes::EEContext&);
void fn_cosl_2_00545c20(p3fes::EEContext&);
void fn_cosl_6_0054f7b8(p3fes::EEContext&);
void fn_cvFsGetFileSize_005566d0(p3fes::EEContext&);
void fn_expl_1_00541aa8(p3fes::EEContext&);
void fn_log10l_3_00547a58(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceInsockBind_2_00548b38(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_539AE0_00539ae0(p3fes::EEContext&);
void fn_sub_53A138_0053a138(p3fes::EEContext&);
void fn_sub_53A3B8_0053a3b8(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53E520_0053e520(p3fes::EEContext&);
void fn_sub_53F630_0053f630(p3fes::EEContext&);
void fn_sub_540718_00540718(p3fes::EEContext&);
void fn_sub_540768_00540768(p3fes::EEContext&);
void fn_sub_540800_00540800(p3fes::EEContext&);
void fn_sub_5408D0_005408d0(p3fes::EEContext&);
void fn_sub_5409A0_005409a0(p3fes::EEContext&);
void fn_sub_540A70_00540a70(p3fes::EEContext&);
void fn_sub_540BA0_00540ba0(p3fes::EEContext&);
void fn_sub_540C70_00540c70(p3fes::EEContext&);
void fn_sub_540D40_00540d40(p3fes::EEContext&);
void fn_sub_540D58_00540d58(p3fes::EEContext&);
void fn_sub_541008_00541008(p3fes::EEContext&);
void fn_sub_541040_00541040(p3fes::EEContext&);
void fn_sub_541058_00541058(p3fes::EEContext&);
void fn_sub_5410A0_005410a0(p3fes::EEContext&);
void fn_sub_541100_00541100(p3fes::EEContext&);
void fn_sub_541118_00541118(p3fes::EEContext&);
void fn_sub_541180_00541180(p3fes::EEContext&);
void fn_sub_541198_00541198(p3fes::EEContext&);
void fn_sub_5413A0_005413a0(p3fes::EEContext&);
void fn_sub_541450_00541450(p3fes::EEContext&);
void fn_sub_541478_00541478(p3fes::EEContext&);
void fn_sub_5414A0_005414a0(p3fes::EEContext&);
void fn_sub_5414B8_005414b8(p3fes::EEContext&);
void fn_sub_541540_00541540(p3fes::EEContext&);
void fn_sub_5415C0_005415c0(p3fes::EEContext&);
void fn_sub_541610_00541610(p3fes::EEContext&);
void fn_sub_541638_00541638(p3fes::EEContext&);
void fn_sub_541668_00541668(p3fes::EEContext&);
void fn_sub_5417F8_005417f8(p3fes::EEContext&);
void fn_sub_541838_00541838(p3fes::EEContext&);
void fn_sub_541878_00541878(p3fes::EEContext&);
void fn_sub_5418B0_005418b0(p3fes::EEContext&);
void fn_sub_5418E8_005418e8(p3fes::EEContext&);
void fn_sub_541900_00541900(p3fes::EEContext&);
void fn_sub_541918_00541918(p3fes::EEContext&);
void fn_sub_541930_00541930(p3fes::EEContext&);
void fn_sub_541948_00541948(p3fes::EEContext&);
void fn_sub_541960_00541960(p3fes::EEContext&);
void fn_sub_541C60_00541c60(p3fes::EEContext&);
void fn_sub_541C88_00541c88(p3fes::EEContext&);
void fn_sub_541CA0_00541ca0(p3fes::EEContext&);
void fn_sub_541D18_00541d18(p3fes::EEContext&);
void fn_sub_541D30_00541d30(p3fes::EEContext&);
void fn_sub_5420A0_005420a0(p3fes::EEContext&);
void fn_sub_542100_00542100(p3fes::EEContext&);
void fn_sub_542F60_00542f60(p3fes::EEContext&);
void fn_sub_542F68_00542f68(p3fes::EEContext&);
void fn_sub_542F70_00542f70(p3fes::EEContext&);
void fn_sub_542FA8_00542fa8(p3fes::EEContext&);
void fn_sub_542FC0_00542fc0(p3fes::EEContext&);
void fn_sub_543020_00543020(p3fes::EEContext&);
void fn_sub_543038_00543038(p3fes::EEContext&);
void fn_sub_543100_00543100(p3fes::EEContext&);
void fn_sub_543130_00543130(p3fes::EEContext&);
void fn_sub_543178_00543178(p3fes::EEContext&);
void fn_sub_543268_00543268(p3fes::EEContext&);
void fn_sub_5432C0_005432c0(p3fes::EEContext&);
void fn_sub_543328_00543328(p3fes::EEContext&);
void fn_sub_543380_00543380(p3fes::EEContext&);
void fn_sub_543388_00543388(p3fes::EEContext&);
void fn_sub_543430_00543430(p3fes::EEContext&);
void fn_sub_543450_00543450(p3fes::EEContext&);
void fn_sub_5438C0_005438c0(p3fes::EEContext&);
void fn_sub_543BF0_00543bf0(p3fes::EEContext&);
void fn_sub_543C90_00543c90(p3fes::EEContext&);
void fn_sub_543CD8_00543cd8(p3fes::EEContext&);
void fn_sub_544850_00544850(p3fes::EEContext&);
void fn_sub_544900_00544900(p3fes::EEContext&);
void fn_sub_544A00_00544a00(p3fes::EEContext&);
void fn_sub_545158_00545158(p3fes::EEContext&);
void fn_sub_5451B0_005451b0(p3fes::EEContext&);
void fn_sub_545208_00545208(p3fes::EEContext&);
void fn_sub_5453D8_005453d8(p3fes::EEContext&);
void fn_sub_545448_00545448(p3fes::EEContext&);
void fn_sub_545570_00545570(p3fes::EEContext&);
void fn_sub_545580_00545580(p3fes::EEContext&);
void fn_sub_545590_00545590(p3fes::EEContext&);
void fn_sub_545610_00545610(p3fes::EEContext&);
void fn_sub_545838_00545838(p3fes::EEContext&);
void fn_sub_545948_00545948(p3fes::EEContext&);
void fn_sub_545AB8_00545ab8(p3fes::EEContext&);
void fn_sub_545B50_00545b50(p3fes::EEContext&);
void fn_sub_545B90_00545b90(p3fes::EEContext&);
void fn_sub_545C40_00545c40(p3fes::EEContext&);
void fn_sub_545CC8_00545cc8(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_546410_00546410(p3fes::EEContext&);
void fn_sub_546498_00546498(p3fes::EEContext&);
void fn_sub_546638_00546638(p3fes::EEContext&);
void fn_sub_546770_00546770(p3fes::EEContext&);
void fn_sub_546EC0_00546ec0(p3fes::EEContext&);
void fn_sub_546EF0_00546ef0(p3fes::EEContext&);
void fn_sub_546F48_00546f48(p3fes::EEContext&);
void fn_sub_546F98_00546f98(p3fes::EEContext&);
void fn_sub_546FA0_00546fa0(p3fes::EEContext&);
void fn_sub_5470E8_005470e8(p3fes::EEContext&);
void fn_sub_547120_00547120(p3fes::EEContext&);
void fn_sub_5471B8_005471b8(p3fes::EEContext&);
void fn_sub_547248_00547248(p3fes::EEContext&);
void fn_sub_5472E8_005472e8(p3fes::EEContext&);
void fn_sub_547418_00547418(p3fes::EEContext&);
void fn_sub_547468_00547468(p3fes::EEContext&);
void fn_sub_5474B8_005474b8(p3fes::EEContext&);
void fn_sub_547548_00547548(p3fes::EEContext&);
void fn_sub_547558_00547558(p3fes::EEContext&);
void fn_sub_547590_00547590(p3fes::EEContext&);
void fn_sub_547598_00547598(p3fes::EEContext&);
void fn_sub_5475C8_005475c8(p3fes::EEContext&);
void fn_sub_547650_00547650(p3fes::EEContext&);
void fn_sub_547AA8_00547aa8(p3fes::EEContext&);
void fn_sub_547C18_00547c18(p3fes::EEContext&);
void fn_sub_547F78_00547f78(p3fes::EEContext&);
void fn_sub_548250_00548250(p3fes::EEContext&);
void fn_sub_548278_00548278(p3fes::EEContext&);
void fn_sub_548300_00548300(p3fes::EEContext&);
void fn_sub_548318_00548318(p3fes::EEContext&);
void fn_sub_5485A8_005485a8(p3fes::EEContext&);
void fn_sub_5485D8_005485d8(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_5487A0_005487a0(p3fes::EEContext&);
void fn_sub_548800_00548800(p3fes::EEContext&);
void fn_sub_548888_00548888(p3fes::EEContext&);
void fn_sub_548AD0_00548ad0(p3fes::EEContext&);
void fn_sub_548E68_00548e68(p3fes::EEContext&);
void fn_sub_548F78_00548f78(p3fes::EEContext&);
void fn_sub_549000_00549000(p3fes::EEContext&);
void fn_sub_549088_00549088(p3fes::EEContext&);
void fn_sub_549110_00549110(p3fes::EEContext&);
void fn_sub_5492C8_005492c8(p3fes::EEContext&);
void fn_sub_549310_00549310(p3fes::EEContext&);
void fn_sub_549568_00549568(p3fes::EEContext&);
void fn_sub_5495D0_005495d0(p3fes::EEContext&);
void fn_sub_549638_00549638(p3fes::EEContext&);
void fn_sub_549690_00549690(p3fes::EEContext&);
void fn_sub_5496E0_005496e0(p3fes::EEContext&);
void fn_sub_5497A8_005497a8(p3fes::EEContext&);
void fn_sub_5498D0_005498d0(p3fes::EEContext&);
void fn_sub_5499B0_005499b0(p3fes::EEContext&);
void fn_sub_549A70_00549a70(p3fes::EEContext&);
void fn_sub_549B08_00549b08(p3fes::EEContext&);
void fn_sub_549C58_00549c58(p3fes::EEContext&);
void fn_sub_549D78_00549d78(p3fes::EEContext&);
void fn_sub_549E68_00549e68(p3fes::EEContext&);
void fn_sub_549EA0_00549ea0(p3fes::EEContext&);
void fn_sub_549EC8_00549ec8(p3fes::EEContext&);
void fn_sub_549FE0_00549fe0(p3fes::EEContext&);
void fn_sub_54A090_0054a090(p3fes::EEContext&);
void fn_sub_54A108_0054a108(p3fes::EEContext&);
void fn_sub_54A2B8_0054a2b8(p3fes::EEContext&);
void fn_sub_54A328_0054a328(p3fes::EEContext&);
void fn_sub_54A390_0054a390(p3fes::EEContext&);
void fn_sub_54A5C8_0054a5c8(p3fes::EEContext&);
void fn_sub_54A618_0054a618(p3fes::EEContext&);
void fn_sub_54A678_0054a678(p3fes::EEContext&);
void fn_sub_54A6B0_0054a6b0(p3fes::EEContext&);
void fn_sub_54A710_0054a710(p3fes::EEContext&);
void fn_sub_54A758_0054a758(p3fes::EEContext&);
void fn_sub_54A878_0054a878(p3fes::EEContext&);
void fn_sub_54A880_0054a880(p3fes::EEContext&);
void fn_sub_54A8C0_0054a8c0(p3fes::EEContext&);
void fn_sub_54A910_0054a910(p3fes::EEContext&);
void fn_sub_54A9D8_0054a9d8(p3fes::EEContext&);
void fn_sub_54AA30_0054aa30(p3fes::EEContext&);
void fn_sub_54AA80_0054aa80(p3fes::EEContext&);
void fn_sub_54AAF0_0054aaf0(p3fes::EEContext&);
void fn_sub_54AB78_0054ab78(p3fes::EEContext&);
void fn_sub_54ABA8_0054aba8(p3fes::EEContext&);
void fn_sub_54AC80_0054ac80(p3fes::EEContext&);
void fn_sub_54ACD8_0054acd8(p3fes::EEContext&);
void fn_sub_54AF38_0054af38(p3fes::EEContext&);
void fn_sub_54AF78_0054af78(p3fes::EEContext&);
void fn_sub_54AFD8_0054afd8(p3fes::EEContext&);
void fn_sub_54B028_0054b028(p3fes::EEContext&);
void fn_sub_54B070_0054b070(p3fes::EEContext&);
void fn_sub_54B388_0054b388(p3fes::EEContext&);
void fn_sub_54B3F0_0054b3f0(p3fes::EEContext&);
void fn_sub_54C580_0054c580(p3fes::EEContext&);
void fn_sub_54CB08_0054cb08(p3fes::EEContext&);
void fn_sub_54D88C_0054d88c(p3fes::EEContext&);
void fn_sub_54D898_0054d898(p3fes::EEContext&);
void fn_sub_54DAD8_0054dad8(p3fes::EEContext&);
void fn_sub_54DB38_0054db38(p3fes::EEContext&);
void fn_sub_54DBE8_0054dbe8(p3fes::EEContext&);
void fn_sub_54DBF0_0054dbf0(p3fes::EEContext&);
void fn_sub_54DD08_0054dd08(p3fes::EEContext&);
void fn_sub_54DE50_0054de50(p3fes::EEContext&);
void fn_sub_54DE90_0054de90(p3fes::EEContext&);
void fn_sub_54E048_0054e048(p3fes::EEContext&);
void fn_sub_54E0D8_0054e0d8(p3fes::EEContext&);
void fn_sub_54E130_0054e130(p3fes::EEContext&);
void fn_sub_54E180_0054e180(p3fes::EEContext&);
void fn_sub_54E260_0054e260(p3fes::EEContext&);
void fn_sub_54E2C0_0054e2c0(p3fes::EEContext&);
void fn_sub_54E388_0054e388(p3fes::EEContext&);
void fn_sub_54E3C0_0054e3c0(p3fes::EEContext&);
void fn_sub_54E648_0054e648(p3fes::EEContext&);
void fn_sub_54E658_0054e658(p3fes::EEContext&);
void fn_sub_54E838_0054e838(p3fes::EEContext&);
void fn_sub_54E9A0_0054e9a0(p3fes::EEContext&);
void fn_sub_54EAB8_0054eab8(p3fes::EEContext&);
void fn_sub_54EAD8_0054ead8(p3fes::EEContext&);
void fn_sub_54EBC0_0054ebc0(p3fes::EEContext&);
void fn_sub_54ED48_0054ed48(p3fes::EEContext&);
void fn_sub_54F028_0054f028(p3fes::EEContext&);
void fn_sub_54F730_0054f730(p3fes::EEContext&);
void fn_sub_54F8C8_0054f8c8(p3fes::EEContext&);
void fn_sub_54FA78_0054fa78(p3fes::EEContext&);
void fn_sub_54FC68_0054fc68(p3fes::EEContext&);
void fn_sub_54FE58_0054fe58(p3fes::EEContext&);
void fn_sub_551978_00551978(p3fes::EEContext&);
void fn_sub_551990_00551990(p3fes::EEContext&);
void fn_sub_551A88_00551a88(p3fes::EEContext&);
void fn_sub_551AD8_00551ad8(p3fes::EEContext&);
void fn_sub_551BB0_00551bb0(p3fes::EEContext&);
void fn_sub_551BF0_00551bf0(p3fes::EEContext&);
void fn_sub_551DA0_00551da0(p3fes::EEContext&);
void fn_sub_551F80_00551f80(p3fes::EEContext&);
void fn_sub_551FF8_00551ff8(p3fes::EEContext&);
void fn_sub_552028_00552028(p3fes::EEContext&);
void fn_sub_552080_00552080(p3fes::EEContext&);
void fn_sub_5523B8_005523b8(p3fes::EEContext&);
void fn_sub_552460_00552460(p3fes::EEContext&);
void fn_sub_552468_00552468(p3fes::EEContext&);
void fn_sub_55F390_0055f390(p3fes::EEContext&);
void fn_sub_560240_00560240(p3fes::EEContext&);
void fn_sub_5603D8_005603d8(p3fes::EEContext&);
void fn_sub_560448_00560448(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564218_00564218(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_564FD0_00564fd0(p3fes::EEContext&);
void fn_sub_565158_00565158(p3fes::EEContext&);
void fn_sub_5651B0_005651b0(p3fes::EEContext&);
void fn_sub_565230_00565230(p3fes::EEContext&);
void fn_sub_565248_00565248(p3fes::EEContext&);
void fn_sub_565550_00565550(p3fes::EEContext&);
void fn_sub_565590_00565590(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace adxt = cri2::adxt;      // the ADXT handle (cri2.h)
namespace enc = libs9::adxenc;     // the ADX encoder handle (libs9.h)
namespace mpa = libs9::mpa;        // the MPEG-audio decoder handle (libs9.h)

// 0x00540D70 __errno_0 -- 12 bytes; leaf frame (no stack)
// Returns the word 0x788680 (FLIRT's __errno is a shape match: a one-word getter).
void __errno_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00540d70
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x790000;
    lw(v0, v1, -31104);  // 0x788680
}

// 0x00541040 sub_541040 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_541008 with the caller's arguments.
void sub_541040(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541040
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541008_00541008(ctx);  // tail call
}

// 0x00541058 sub_541058 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The file-system server tick, re-entry guarded: when the busy word 0x788758 is 0 it sets it, runs sub_549EA0 (the
// ADXT server) and ADXT_UpdateFsStat, then clears it; returns 0. [adxm_ExecFsSvr]
void sub_541058(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541058
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, -30888);  // &0x788758
    lw(v1, s0, 0);  // 0x788758
    sd(ra, sp, 0x8);
    if (v1 == 0) {
        // 0x00541074
        charge(ctx, 6);
        v0 = 1;
        link(ctx, 0x541078u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 0);
        call(ctx, gen::fn_sub_549EA0_00549ea0);
        jal(ctx, 0x541080u, gen::fn_ADXT_UpdateFsStat_0053e0b8);
        sw(zero, s0, 0);
    }
    // 0x0054108c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = 0;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005410A0 sub_5410A0 -- 96 bytes; frame 0x30: ra sp+0x20
// ADXM_SetupThrd with a parameter record built on the stack from a 4-word caller record ($a0: priorities at +0..+12;
// the copy holds +8 + 1 and a fixed 25), or with null when $a0 is null.
void sub_5410A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005410a0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a0;
    sd(ra, sp, 0x20);
    if (v0 == 0) {
        // 0x005410e8
        charge(ctx, 1);
        t0 = 0;
    } else {
        // 0x005410b0
        charge(ctx, 14);
        lw(a2, v0, 8);
        a3 = 25;
        lw(a0, v0, 12);
        t0 = sp;
        lw(v1, v0, 0);
        a1 = addiu(a2, 1);
        lw(v0, v0, 4);
        sw(a0, sp, 0x10);
        sw(v1, sp, 0x0);
        sw(v0, sp, 0x4);
        sw(a1, sp, 0xC);
        sw(a3, sp, 0x14);
        sw(a2, sp, 0x8);
    }
    // 0x005410ec
    charge(ctx, 5);
    a0 = t0;
    jal(ctx, 0x5410ECu, gen::fn_ADXM_SetupThrd_00540588);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00541100 sub_541100 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_540768 (the thread-layer shutdown, owned by another slice).
void sub_541100(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541100
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_540768_00540768(ctx);  // tail call
}

// 0x00541118 sub_541118 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The guarded server tick under the ADXM lock: sub_540D40 (lock); if the busy word 0x788758 is set, unlock and return;
// else set it, unlock, run the ADXT server and ADXT_UpdateFsStat, clear it.
void sub_541118(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541118
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x541124u, gen::fn_sub_540D40_00540d40);
    v0 = 0x790000;
    s0 = addiu(v0, -30888);  // &0x788758
    lw(v1, s0, 0);  // 0x788758
    if (v1 != 0) {
        ld(s0, sp, 0x0);
        // 0x00541170
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_540D58_00540d58(ctx);  // tail call
        return;
    }
    // 0x00541140
    charge(ctx, 12);
    v0 = 1;
    link(ctx, 0x541144u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_540D58_00540d58);
    jal(ctx, 0x54114Cu, gen::fn_sub_549EA0_00549ea0);
    jal(ctx, 0x541154u, gen::fn_ADXT_UpdateFsStat_0053e0b8);
    sw(zero, s0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00541180 sub_541180 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_564978.
void sub_541180(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541180
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x00541198 sub_541198 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_564990.
void sub_541198(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541198
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x005411B0 ADXM_SetupThrdEx -- 492 bytes; frame 0x50: s2 sp+0x40, s1 sp+0x38, s0 sp+0x30, ra sp+0x48
// ADXM_SetupThrdEx: the first call (use count 0x788644 == 0) installs the vsync / idle hooks, copies the caller's
// 12-word thread-priority record (or the defaults 1, 8, 15, 16, 18, 24, 25, 26) into 0x788650.., records the main
// thread id (0x7886E8) and its priority (0x78FF78), creates the safe / vsync / file-system / idle threads and raises
// the main thread to the configured priority; every call bumps the use count and returns it.
void ADXM_SetupThrdEx(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005411b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x790000;
    sd(s2, sp, 0x40);
    s2 = 0x790000;
    sd(s1, sp, 0x38);
    s1 = a0;
    sd(s0, sp, 0x30);
    v0 = addiu(v0, -31168);  // &0x788640
    sd(ra, sp, 0x48);
    lw(v1, s2, -31164);  // 0x788644
    lw(a1, v0, 0);  // 0x788640
    if (v1 != 0) {
        v1 = addiu(s2, -31164);  // &0x788644
    } else {
        // 0x005411e4
        charge(ctx, 12);
        jal(ctx, 0x5411E4u, gen::fn_sub_565550_00565550);
        a0 = 0x540000;
        a0 = addiu(a0, -1864);  // &sub_53F8B8
        a1 = 0;
        jal(ctx, 0x5411F4u, gen::fn_sub_565230_00565230);
        a0 = 0x540000;
        a0 = addiu(a0, -1728);  // &sub_53F940
        a1 = 0;
        jal(ctx, 0x541204u, gen::fn_sub_565248_00565248);
        if (s1 != 0) {
            lw(v1, s1, 20);
            // 0x00541270
            charge(ctx, 25);
            s0 = 0x790000;
            a0 = addiu(s0, -31152);  // &0x788650
            lw(v0, s1, 32);
            sw(v1, a0, 20);  // 0x788664
            sw(v0, a0, 32);  // 0x788670
            lw(v1, s1, 0);
            lw(a1, s1, 40);
            sw(v1, a0, 0);  // 0x788650
            sw(a1, a0, 40);  // 0x788678
            lw(v0, s1, 4);
            sw(v0, a0, 4);  // 0x788654
            lw(v1, s1, 8);
            sw(v1, a0, 8);  // 0x788658
            lw(v0, s1, 12);
            sw(v0, a0, 12);  // 0x78865C
            lw(v1, s1, 16);
            sw(v1, a0, 16);  // 0x788660
            lw(v0, s1, 24);
            sw(v0, a0, 24);  // 0x788668
            lw(v1, s1, 28);
            sw(v1, a0, 28);  // 0x78866C
            lw(v0, s1, 36);
            sw(v0, a0, 36);  // 0x788674
            lw(v1, s1, 44);
            sw(v1, a0, 44);  // 0x78867C
        } else {
            // 0x00541214
            charge(ctx, 23);
            s0 = 0x790000;
            t2 = 24;
            v0 = addiu(s0, -31152);  // &0x788650
            v1 = 1;
            a0 = 8;
            a1 = 15;
            a2 = 16;
            a3 = 18;
            t0 = 25;
            t1 = 26;
            sw(t2, v0, 20);  // 0x788664
            sw(v1, v0, 0);  // 0x788650
            sw(a0, v0, 4);  // 0x788654
            sw(a1, v0, 8);  // 0x788658
            sw(a2, v0, 12);  // 0x78865C
            sw(a3, v0, 16);  // 0x788660
            sw(t0, v0, 24);  // 0x788668
            sw(t1, v0, 28);  // 0x78866C
            sw(zero, v0, 44);  // 0x78867C
            sw(zero, v0, 32);  // 0x788670
            sw(zero, v0, 36);  // 0x788674
            sw(zero, v0, 40);  // 0x788678
        }
        // 0x005412d4
        charge(ctx, 41);
        s1 = 0x790000;
        jal(ctx, 0x5412D4u, gen::fn__sceGetThreadId_00503050);
        s1 = addiu(s1, -31000);  // &0x7886E8
        a1 = sp;
        sw(v0, s1, 0);  // 0x7886E8
        s0 = addiu(s0, -31152);
        link(ctx, 0x5412ECu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);  // 0x7886E8
        call(ctx, gen::fn__sceReferThreadStatus_00503060);
        v1 = 0x790000;
        lw(v0, sp, 0x18);
        link(ctx, 0x5412FCu);  // $ra first: the delay slot below depends on it
        sw(v0, v1, -136);
        call(ctx, gen::fn_adxm_SetupSafeThrd_00540178);
        lw(a0, s0, 32);
        link(ctx, 0x541308u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 36);
        call(ctx, gen::fn_adxm_SetupUsrVsyncThrd_00540220);
        jal(ctx, 0x541310u, gen::fn_adxm_SetupVsyncThrd_005402d8);
        jal(ctx, 0x541318u, gen::fn_adxm_SetupFsThrd_00540360);
        jal(ctx, 0x541320u, gen::fn_adxm_SetupMwIdleThrd_005403e8);
        lw(a0, s0, 40);
        link(ctx, 0x54132Cu);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 44);
        call(ctx, gen::fn_adxm_SetupUsrIdleThrd_00540480);
        lw(a0, s1, 0);  // 0x7886E8
        link(ctx, 0x541338u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 20);
        call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
        a1 = 0x540000;
        a1 = addiu(a1, -1384);  // &sub_53FA98
        a0 = 6;
        a2 = 0;
        jal(ctx, 0x54134Cu, gen::fn_sub_565158_00565158);
        a1 = 0x540000;
        a1 = addiu(a1, -1344);  // &sub_53FAC0
        a0 = 7;
        a2 = 0;
        jal(ctx, 0x541360u, gen::fn_sub_565158_00565158);
        v1 = 0x790000;
        v0 = 1;
        sw(v0, v1, -31160);  // 0x788648
        v1 = addiu(s2, -31164);
    }
    // 0x00541378 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s2, sp, 0x40);
    lw(v0, v1, 0);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x48);
    sw(v0, v1, 0);
    sp = addiu(sp, 0x50);
}

// 0x005413A0 sub_5413A0 -- 172 bytes; frame 0x10: ra sp+0x0
// The ADXM shutdown: the last release (use count 0x788644 drops to 0) destroys the seven ADXM threads, restores the
// main thread's priority, removes the hooks and clears 0x788648. [ADXM_ShutdownThrd]
void sub_5413A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005413a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, -31164);  // &0x788644
    lw(v0, v1, 0);  // 0x788644
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x788644
    if (v0 != 0) {
        // 0x00541440
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005413c0
    charge(ctx, 31);
    jal(ctx, 0x5413C0u, gen::fn_sub_540718_00540718);
    jal(ctx, 0x5413C8u, gen::fn_sub_540800_00540800);
    jal(ctx, 0x5413D0u, gen::fn_sub_5408D0_005408d0);
    jal(ctx, 0x5413D8u, gen::fn_sub_540A70_00540a70);
    jal(ctx, 0x5413E0u, gen::fn_sub_5409A0_005409a0);
    jal(ctx, 0x5413E8u, gen::fn_sub_540BA0_00540ba0);
    jal(ctx, 0x5413F0u, gen::fn_sub_540C70_00540c70);
    v0 = 0x790000;
    v1 = 0x790000;
    v0 = addiu(v0, -31000);  // &0x7886E8
    lw(a1, v1, -136);  // 0x78FF78
    link(ctx, 0x541408u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x541414u, gen::fn_sub_565230_00565230);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x541420u, gen::fn_sub_565248_00565248);
    v0 = 0x790000;
    ld(ra, sp, 0x0);
    sw(zero, v0, -31160);  // 0x788648
    sp = addiu(sp, 0x10);
    gen::fn_sub_565590_00565590(ctx);  // tail call
}

// 0x00541450 sub_541450 -- 36 bytes; frame 0x10: ra sp+0x0
// Registers a callback ($a0, $a1) in slot 1 of sub_564FD0's table (kind 0).
void sub_541450(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541450
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a0;
    sd(ra, sp, 0x0);
    a3 = a1;
    a0 = 1;
    a1 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564FD0_00564fd0(ctx);  // tail call
}

// 0x00541478 sub_541478 -- 36 bytes; frame 0x10: ra sp+0x0
// Registers a callback ($a0, $a1) in slot 7 of sub_564FD0's table (kind 0).
void sub_541478(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541478
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a0;
    sd(ra, sp, 0x0);
    a3 = a1;
    a0 = 7;
    a1 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564FD0_00564fd0(ctx);  // tail call
}

// 0x005414A0 sub_5414A0 -- 24 bytes; frame 0x10: ra sp+0x0
// Calls sub_5651B0(7): the slot-7 query.
void sub_5414A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005414a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 7;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5651B0_005651b0(ctx);  // tail call
}

// 0x005414B8 sub_5414B8 -- 36 bytes; leaf frame (no stack)
// Stores the four arguments into the record 0x997038 (+0..+12) and returns its address.
void sub_5414B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005414b8
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x990000;
    v1 = 0x990000;
    v0 = addiu(v0, 28728);  // &0x997038
    v1 = addiu(v1, 28736);  // &0x997040
    sw(a1, v0, 4);  // 0x99703C
    sw(a0, v0, 0);  // 0x997038
    sw(a3, v1, 4);  // 0x997044
    sw(a2, v1, 0);  // 0x997040
}

// 0x00541540 sub_541540 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Selects the ADXM thread mode ($a0, kept in 0x78FF7C): mode 1 returns 1 at once; modes 0 and 2 set up the threads
// with $a1's record and return 1; any other mode returns 0. sub_53F630 gets sub_541610's value first.
void sub_541540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541540
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = 1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x54155Cu, gen::fn_sub_541610_00541610);
    a0 = v0;
    jal(ctx, 0x541564u, gen::fn_sub_53F630_0053f630);
    v0 = 0x790000;
    sw(s0, v0, -132);  // 0x78FF7C
    if (s0 != s1) {
        // 0x00541578
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00541580
            charge(ctx, 3);
            v0 = 2;
            if (s0 == v0) {
                goto L_0054158c;
            }
            s1 = 0;
            goto L_005415a0;
        }
    L_0054158c:
        charge(ctx, 4);
        a0 = s2;
        jal(ctx, 0x54158Cu, gen::fn_ADXM_SetupThrd_00540588);
        v0 = s1;
        // 0x005415a4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_005415a0:
    charge(ctx, 1);
    v0 = s1;
    // 0x005415a4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005415C0 sub_5415C0 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The counterpart of sub_541540: modes 0 / 2 shut the threads down, mode 1 does nothing, others report 0;
// sub_53F630(-1) runs last.
void sub_5415C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005415c0
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -132);  // 0x78FF7C
    sd(s0, sp, 0x0);
    s0 = 1;
    sd(ra, sp, 0x8);
    if (v1 != s0) {
        // 0x005415dc
        charge(ctx, 2);
        v0 = 2;
        if (v1 != 0) {
            // 0x005415e4
            charge(ctx, 2);
            if (v1 == v0) {
                goto L_005415ec;
            }
            s0 = 0;
            goto L_005415f4;
        }
    L_005415ec:
        charge(ctx, 2);
        jal(ctx, 0x5415ECu, gen::fn_sub_540768_00540768);
    }
L_005415f4:
    charge(ctx, 7);
    a0 = si(-1);
    jal(ctx, 0x5415F4u, gen::fn_sub_53F630_0053f630);
    v0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00541628 __errno_1 -- 12 bytes; leaf frame (no stack)
// Returns the debug-print level word 0x78FF80.
void __errno_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00541628
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x790000;
    lw(v0, v1, -128);  // 0x78FF80
}

// 0x00541638 sub_541638 -- 60 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets the debug-print level ($a0 into 0x78FF80 and 0x7A2A78) around WTLS_set_table.
void sub_541638(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541638
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x54164Cu);  // $ra first: the delay slot below depends on it
    sw(s0, v0, -128);
    call(ctx, gen::fn_WTLS_set_table_0055d220);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0055a7b0
    charge(ctx, 3);
    v0 = 0x7A0000;
    sw(a0, v0, 10872);  // 0x7A2A78
}

// 0x00541668 sub_541668 -- 128 bytes; frame 0xF0: ra sp+0x80
// A printf-style debug print: spills the variadic register arguments ($a1..$t3, $f12..$f19) to the frame, formats into
// a 128-byte stack buffer with vsprintf and prints with scePrintf unless the level word 0x78FF80 is 2.
void sub_541668(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19};
    // 0x00541668
    enter(ctx, 25);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0xF0);
    lw(t4, v0, -128);  // 0x78FF80
    v1 = a0;
    t5 = 2;
    sd(a1, sp, 0xB8);
    sd(a2, sp, 0xC0);
    a2 = addiu(sp, 0xB8);
    sd(ra, sp, 0x80);
    a0 = sp;
    a1 = v1;
    sd(a3, sp, 0xC8);
    sd(t0, sp, 0xD0);
    sd(t1, sp, 0xD8);
    sd(t2, sp, 0xE0);
    sd(t3, sp, 0xE8);
    swc1(f12, sp, 0x98);
    swc1(f13, sp, 0x9C);
    swc1(f14, sp, 0xA0);
    swc1(f15, sp, 0xA4);
    swc1(f16, sp, 0xA8);
    swc1(f17, sp, 0xAC);
    swc1(f18, sp, 0xB0);
    swc1(f19, sp, 0xB4);
    if (t4 != t5) {
        // 0x005416cc
        charge(ctx, 4);
        jal(ctx, 0x5416CCu, gen::fn_vsprintf_005288c8);
        a0 = sp;
        jal(ctx, 0x5416D4u, gen::fn_scePrintf_00505e48);
    }
    // 0x005416dc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0xF0);
}

// 0x005417F8 sub_5417F8 -- 60 bytes; frame 0x10: ra sp+0x0
// Channel $a1's stream joint (handle +12 -> +8 + 4 * $a1 -> +8), asked for its line-1 data size through its interface
// (+36): the result halved (bytes -> 16-bit samples).
void sub_5417F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005417f8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 12);
    a0 = sll(a1, 2);
    v0 = addu(v0, a0);
    lw(v1, v0, 8);
    lw(a0, v1, 8);
    lw(a2, a0, 0);
    lw(v0, a2, 36);
    a1 = 1;
    jalr(ctx, 0x54181Cu, v0.u());
    ld(ra, sp, 0x0);
    v0 = srl(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00541838 sub_541838 -- 60 bytes; frame 0x10: ra sp+0x0
// As sub_5417F8 for line 0 (free space).
void sub_541838(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541838
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 12);
    a0 = sll(a1, 2);
    v0 = addu(v0, a0);
    lw(v1, v0, 8);
    lw(a0, v1, 8);
    lw(a2, a0, 0);
    lw(v0, a2, 36);
    a1 = 0;
    jalr(ctx, 0x54185Cu, v0.u());
    ld(ra, sp, 0x0);
    v0 = srl(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00541878 sub_541878 -- 52 bytes; frame 0x10: ra sp+0x0
// Channel $a1's output (+4 of its record) through sub_564218(.., 1), halved.
void sub_541878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541878
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 12);
    a0 = sll(a1, 2);
    a1 = 1;
    v0 = addu(v0, a0);
    lw(v1, v0, 8);
    link(ctx, 0x541894u);  // $ra first: the delay slot below depends on it
    lw(a0, v1, 4);
    call(ctx, gen::fn_sub_564218_00564218);
    ld(ra, sp, 0x0);
    v0 = srl(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x005418B0 sub_5418B0 -- 52 bytes; frame 0x10: ra sp+0x0
// As sub_541878 with line 0.
void sub_5418B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005418b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 12);
    a0 = sll(a1, 2);
    a1 = 0;
    v0 = addu(v0, a0);
    lw(v1, v0, 8);
    link(ctx, 0x5418CCu);  // $ra first: the delay slot below depends on it
    lw(a0, v1, 4);
    call(ctx, gen::fn_sub_564218_00564218);
    ld(ra, sp, 0x0);
    v0 = srl(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x005418E8 sub_5418E8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_560240.
void sub_5418E8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005418e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560240_00560240(ctx);  // tail call
}

// 0x00541900 sub_541900 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_5603D8.
void sub_541900(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541900
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5603D8_005603d8(ctx);  // tail call
}

// 0x00541918 sub_541918 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_560448.
void sub_541918(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00541918
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_560448_00560448(ctx);  // tail call
}

// 0x00541930 sub_541930 -- 100 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Sets byte +84 of the output record ($a0 +12) to $a1 when it differs, unless mode 0x7A93F8 is 1 with 0x7A93F0 <= 0;
// $a1 == 1 is taken only when 0x7A9420 is set; the tail lives in the second chunk at 0x5604B0.
void sub_541930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00541930
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 12);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005604b0
    charge(ctx, 5);
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    if (v1 != a2) {
        lb(v0, a0, 84);
    } else {
        // 0x005604c4
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            // 0x005604d4
            charge(ctx, 1);
            lb(v0, a0, 84);
            goto L_005604d8;
        }
        // 0x005604f4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_005604d8:
    charge(ctx, 2);
    cc = v0 == a1;  // the condition, before the delay slot changes it
    v0 = 0x7B0000;
    if (!cc) {
        // 0x005604e0
        charge(ctx, 3);
        lw(v1, v0, -27616);
        if (v1 != 0) {
            sb(a1, a0, 84);
        } else {
            // 0x005604ec
            charge(ctx, 2);
            if (a1 != a2) {
                sb(a1, a0, 84);
            }
        }
    }
    // 0x005604f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541948 sub_541948 -- 100 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Sets byte +86 of the output record ($a0 +12) to $a1 when it differs and the mode word 0x7A9438 is 2 (gated as
// sub_541930); second chunk at 0x560500.
void sub_541948(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541948
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 12);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00560500
    charge(ctx, 5);
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    a3 = a0;
    if (v1 == a2) {
        // 0x00560514
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00560524;
        }
        // 0x00560544 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00560524:
    charge(ctx, 5);
    v0 = 0x7B0000;
    a0 = 2;
    lw(v1, v0, -27592);  // 0x7A9438
    if (v1 == a0) {
        // 0x00560538
        charge(ctx, 3);
        lb(v0, a3, 86);
        if (v0 != a1) {
            sb(a1, a3, 86);
        }
    }
    // 0x00560544 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00541960 sub_541960 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Returns the signed byte +87 of the output record ($a0 +12); second chunk at 0x560550.
void sub_541960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00541960
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 12);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00560550
    charge(ctx, 2);
    lb(v0, a0, 87);
}

// 0x00544900 sub_544900 -- 252 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// The ADX encoder's footer: pads the output to the sector-aligned total (when the handle's +108 loop count is set) and
// writes the 0x8001 end marker, the padding length and that many zero bytes through sub_5438C0 (the stream-joint
// write); returns the bytes written or 0 when the joint lacks room. [adxenc_WriteFooter]
void sub_544900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00544900
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    lw(v0, a0, enc::kLoopCnt);
    lw(s2, a0, enc::kSjOut);
    lw(a1, a0, enc::kOutBytes);
    if (i64(v0) > 0) {
        // 0x00544930
        charge(ctx, 9);
        lw(v0, a0, enc::kBlockSize);
        v0 = addu(a1, v0);
        v1 = addiu(v0, 2047);
        v0 = addiu(v0, 4094);
        a0 = slti(v1, 0);
        if (a0 != 0) v1 = v0;
        v1 = sra(v1, 11);
        v1 = sll(v1, 11);
        s1 = subu(v1, a1);
    } else {
        // 0x00544928
        charge(ctx, 2);
        lw(s1, a0, enc::kBlockSize);
    }
    // 0x00544954
    charge(ctx, 9);
    lw(v1, s2, 0);
    a0 = s2;
    a1 = 0;
    lw(v0, v1, 36);
    s0 = addiu(s1, -4);
    jalr(ctx, 0x544964u, v0.u());
    v1 = slt(v0, s1);
    v0 = 0;
    if (v1 == 0) {
        // 0x00544978
        charge(ctx, 15);
        a0 = sp;
        a1 = 2;
        a2 = 1;
        a3 = s2;
        v0 = 0x8001;
        link(ctx, 0x54498Cu);  // $ra first: the delay slot below depends on it
        sh(v0, sp, 0x0);
        call(ctx, gen::fn_sub_5438C0_005438c0);
        a0 = sp;
        a1 = 2;
        a2 = 1;
        a3 = s2;
        link(ctx, 0x5449A4u);  // $ra first: the delay slot below depends on it
        sh(s0, sp, 0x0);
        call(ctx, gen::fn_sub_5438C0_005438c0);
        sb(zero, sp, 0x2);
        if (i64(s0) > 0) {
            // 0x005449b4
            charge(ctx, 3);
            s3 = addiu(sp, 0x2);
            s0 = addiu(s1, -4);
            s0 = addiu(s0, -1);
            for (;;) {
                // 0x005449c0
                charge(ctx, 7);
                a0 = s3;
                a1 = 1;
                a2 = 1;
                a3 = s2;
                jal(ctx, 0x5449CCu, gen::fn_sub_5438C0_005438c0);
                cc = s0 != 0;  // the condition, before the delay slot changes it
                s0 = addiu(s0, -1);
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x005449dc
        charge(ctx, 1);
        v0 = s1;
    }
    // 0x005449e0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00544A00 sub_544A00 -- 1876 bytes; frame 0x70: s4 sp+0x40, s0 sp+0x20, s3 sp+0x38, fp sp+0x60, s1 sp+0x28, s2 sp+0x30, s5 sp+0x48, s6 sp+0x50, s7 sp+0x58, ra sp+0x68
// The ADX encoder's header writer: checks the output joint holds the header (+72 + 4 bytes), then writes the 0x8000
// signature, the header offset (+72), encoding (+76), block size (+80), bits (+84), channels (+88), sample rate (+92),
// total samples (+96), high-pass frequency (+100), version 4, the flags, the history words (+712..+718), the loop
// records (+104 / +108, 20 bytes each: +112..+124), the optional AINF (0x41494E46, +726..+748) and CINF (0x43494E46,
// +750..+756) chunks, zero padding and the copyright string at 0x790A30; returns the header size or 0 on any short
// write. [adxenc_WriteHdr]
void sub_544A00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00544a00
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0x790000;
    sd(s4, sp, 0x40);
    s4 = a0;
    lw(a0, v0, 2608);  // 0x790A30
    sd(s0, sp, 0x20);
    sd(s3, sp, 0x38);
    sd(fp, sp, 0x60);
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    sd(s7, sp, 0x58);
    sd(ra, sp, 0x68);
    s3 = a1;
    jal(ctx, 0x544A38u, gen::fn_strlen_00524388);
    fp = v0;
    lw(v0, s3, 0);
    a2 = 0x7FFF0000;
    a3 = sp;
    lw(v1, v0, 24);
    a0 = s3;
    a1 = 0;
    a2 = a2 | 0xFFFF;
    jalr(ctx, 0x544A5Cu, v1.u());
    lw(v0, s3, 0);
    a0 = s3;
    a1 = 0;
    lw(a3, v0, 28);
    a2 = sp;
    jt = a3.u();  // the target, read before the delay slot
    link(ctx, 0x544A78u);  // $ra = the return address
    lw(s0, sp, 0x4);
    call_ptr(ctx, jt);
    lw(v1, s4, enc::kHdrOfs);
    v1 = addiu(v1, 4);
    s0 = slt(s0, v1);
    v0 = 0;
    if (s0 == 0) {
        // 0x00544a94
        charge(ctx, 11);
        v0 = 0x8000;
        a0 = addiu(sp, 0x10);
        a1 = 2;
        a2 = 1;
        a3 = s3;
        link(ctx, 0x544AA8u);  // $ra first: the delay slot below depends on it
        sh(v0, sp, 0x10);
        call(ctx, gen::fn_sub_5438C0_005438c0);
        s1 = v0;
        v0 = 1;
        cc = s1 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00544ac0
            charge(ctx, 10);
            lh(v0, s4, enc::kHdrOfs);
            a0 = addiu(sp, 0x12);
            a1 = 2;
            a2 = 1;
            a3 = s3;
            link(ctx, 0x544AD4u);  // $ra first: the delay slot below depends on it
            sh(v0, sp, 0x12);
            call(ctx, gen::fn_sub_5438C0_005438c0);
            s0 = v0;
            v0 = 0;
            if (s0 == s1) {
                // 0x00544ae8
                charge(ctx, 10);
                lb(v0, s4, enc::kEncoding);
                s7 = addiu(sp, 0x14);
                a0 = s7;
                a1 = 1;
                a2 = 1;
                a3 = s3;
                link(ctx, 0x544B00u);  // $ra first: the delay slot below depends on it
                sb(v0, sp, 0x14);
                call(ctx, gen::fn_sub_5438C0_005438c0);
                cc = v0 != s0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x00544b10
                    charge(ctx, 11);
                    lbu(v0, s4, enc::kBlockSize);
                    a0 = s7;
                    a1 = 1;
                    a2 = 1;
                    a3 = s3;
                    link(ctx, 0x544B24u);  // $ra first: the delay slot below depends on it
                    sb(v0, sp, 0x14);
                    call(ctx, gen::fn_sub_5438C0_005438c0);
                    s2 = 1;
                    s1 = v0;
                    v0 = 0;
                    if (s1 == s2) {
                        // 0x00544b3c
                        charge(ctx, 10);
                        lbu(v0, s4, enc::kBits);
                        a0 = s7;
                        a1 = 1;
                        a2 = 1;
                        a3 = s3;
                        link(ctx, 0x544B50u);  // $ra first: the delay slot below depends on it
                        sb(v0, sp, 0x14);
                        call(ctx, gen::fn_sub_5438C0_005438c0);
                        s0 = v0;
                        v0 = 0;
                        if (s0 == s1) {
                            // 0x00544b64
                            charge(ctx, 10);
                            lbu(v0, s4, enc::kNch);
                            a0 = s7;
                            a1 = 1;
                            a2 = 1;
                            a3 = s3;
                            link(ctx, 0x544B78u);  // $ra first: the delay slot below depends on it
                            sb(v0, sp, 0x14);
                            call(ctx, gen::fn_sub_5438C0_005438c0);
                            s1 = v0;
                            v0 = 0;
                            if (s1 == s0) {
                                // 0x00544b8c
                                charge(ctx, 10);
                                lw(v0, s4, enc::kRate);
                                a0 = addiu(sp, 0x18);
                                a1 = 4;
                                a2 = 1;
                                a3 = s3;
                                link(ctx, 0x544BA0u);  // $ra first: the delay slot below depends on it
                                sw(v0, sp, 0x18);
                                call(ctx, gen::fn_sub_5438C0_005438c0);
                                s0 = v0;
                                v0 = 0;
                                if (s0 == s1) {
                                    // 0x00544bb4
                                    charge(ctx, 10);
                                    lw(v0, s4, enc::kTotal);
                                    a0 = addiu(sp, 0x18);
                                    a1 = 4;
                                    a2 = 1;
                                    a3 = s3;
                                    link(ctx, 0x544BC8u);  // $ra first: the delay slot below depends on it
                                    sw(v0, sp, 0x18);
                                    call(ctx, gen::fn_sub_5438C0_005438c0);
                                    s1 = v0;
                                    v0 = 0;
                                    if (s1 == s0) {
                                        // 0x00544bdc
                                        charge(ctx, 11);
                                        lh(v0, s4, enc::kHighpass);
                                        s6 = addiu(sp, 0x16);
                                        a0 = s6;
                                        a1 = 2;
                                        a2 = 1;
                                        a3 = s3;
                                        link(ctx, 0x544BF4u);  // $ra first: the delay slot below depends on it
                                        sh(v0, sp, 0x16);
                                        call(ctx, gen::fn_sub_5438C0_005438c0);
                                        s0 = v0;
                                        v0 = 0;
                                        if (s0 == s1) {
                                            // 0x00544c08
                                            charge(ctx, 9);
                                            v0 = 4;
                                            a0 = s7;
                                            a1 = 1;
                                            a2 = 1;
                                            a3 = s3;
                                            link(ctx, 0x544C1Cu);  // $ra first: the delay slot below depends on it
                                            sb(v0, sp, 0x14);
                                            call(ctx, gen::fn_sub_5438C0_005438c0);
                                            cc = v0 != s0;  // the condition, before the delay slot changes it
                                            v0 = 0;
                                            if (!cc) {
                                                // 0x00544c2c
                                                charge(ctx, 3);
                                                lh(v0, s4, enc::kFlag720);
                                                cc = v0 != 0;  // the condition, before the delay slot changes it
                                                v0 = 8;
                                                if (cc) {
                                                    // 0x00544c40
                                                    charge(ctx, 1);
                                                    sb(v0, sp, 0x14);
                                                } else {
                                                    // 0x00544c38
                                                    charge(ctx, 2);
                                                    sb(zero, sp, 0x14);
                                                }
                                                // 0x00544c44
                                                charge(ctx, 9);
                                                a0 = s7;
                                                a1 = 1;
                                                a2 = 1;
                                                a3 = s3;
                                                jal(ctx, 0x544C50u, gen::fn_sub_5438C0_005438c0);
                                                s0 = v0;
                                                v0 = 1;
                                                cc = s0 != v0;  // the condition, before the delay slot changes it
                                                v0 = 0;
                                                if (!cc) {
                                                    // 0x00544c68
                                                    charge(ctx, 9);
                                                    a0 = addiu(sp, 0x18);
                                                    a1 = 4;
                                                    a2 = 1;
                                                    a3 = s3;
                                                    link(ctx, 0x544C78u);  // $ra first: the delay slot below depends on it
                                                    sw(zero, sp, 0x18);
                                                    call(ctx, gen::fn_sub_5438C0_005438c0);
                                                    s1 = v0;
                                                    v0 = 0;
                                                    if (s1 == s0) {
                                                        // 0x00544c8c
                                                        charge(ctx, 10);
                                                        lhu(v0, s4, enc::kHist);
                                                        a0 = s6;
                                                        a1 = 2;
                                                        a2 = 1;
                                                        a3 = s3;
                                                        link(ctx, 0x544CA0u);  // $ra first: the delay slot below depends on it
                                                        sh(v0, sp, 0x16);
                                                        call(ctx, gen::fn_sub_5438C0_005438c0);
                                                        s0 = v0;
                                                        v0 = 0;
                                                        if (s0 == s1) {
                                                            // 0x00544cb4
                                                            charge(ctx, 10);
                                                            lhu(v0, s4, enc::kHist + 4);
                                                            a0 = s6;
                                                            a1 = 2;
                                                            a2 = 1;
                                                            a3 = s3;
                                                            link(ctx, 0x544CC8u);  // $ra first: the delay slot below depends on it
                                                            sh(v0, sp, 0x16);
                                                            call(ctx, gen::fn_sub_5438C0_005438c0);
                                                            s1 = v0;
                                                            v0 = 0;
                                                            if (s1 == s0) {
                                                                // 0x00544cdc
                                                                charge(ctx, 10);
                                                                lhu(v0, s4, enc::kHist + 2);
                                                                a0 = s6;
                                                                a1 = 2;
                                                                a2 = 1;
                                                                a3 = s3;
                                                                link(ctx, 0x544CF0u);  // $ra first: the delay slot below depends on it
                                                                sh(v0, sp, 0x16);
                                                                call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                s0 = v0;
                                                                v0 = 0;
                                                                if (s0 == s1) {
                                                                    // 0x00544d04
                                                                    charge(ctx, 10);
                                                                    lhu(v0, s4, enc::kHist + 6);
                                                                    a0 = s6;
                                                                    a1 = 2;
                                                                    a2 = 1;
                                                                    a3 = s3;
                                                                    link(ctx, 0x544D18u);  // $ra first: the delay slot below depends on it
                                                                    sh(v0, sp, 0x16);
                                                                    call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                    s1 = v0;
                                                                    v0 = 0;
                                                                    if (s1 == s0) {
                                                                        // 0x00544d2c
                                                                        charge(ctx, 3);
                                                                        lw(v1, s4, enc::kLoopCnt);
                                                                        s2 = 28;
                                                                        if (i64(v1) > 0) {
                                                                            // 0x00544d38
                                                                            charge(ctx, 10);
                                                                            lhu(v0, s4, enc::kAlignSmpl);
                                                                            a0 = s6;
                                                                            a1 = 2;
                                                                            a2 = 1;
                                                                            a3 = s3;
                                                                            link(ctx, 0x544D4Cu);  // $ra first: the delay slot below depends on it
                                                                            sh(v0, sp, 0x16);
                                                                            call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                            s0 = v0;
                                                                            v0 = 0;
                                                                            if (s0 == s1) {
                                                                                // 0x00544d60
                                                                                charge(ctx, 9);
                                                                                lhu(v0, s4, enc::kLoopCnt);
                                                                                a0 = s6;
                                                                                a1 = 2;
                                                                                a2 = 1;
                                                                                a3 = s3;
                                                                                link(ctx, 0x544D74u);  // $ra first: the delay slot below depends on it
                                                                                sh(v0, sp, 0x16);
                                                                                call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                cc = v0 != s0;  // the condition, before the delay slot changes it
                                                                                v0 = 0;
                                                                                if (!cc) {
                                                                                    // 0x00544d84
                                                                                    charge(ctx, 4);
                                                                                    lw(v1, s4, enc::kLoopCnt);
                                                                                    s2 = 32;
                                                                                    s5 = 0;
                                                                                    if (i64(v1) <= 0) {
                                                                                        goto L_00544e90;
                                                                                    }
                                                                                    // 0x00544d94
                                                                                    charge(ctx, 1);
                                                                                    a0 = s6;
                                                                                    for (;;) {
                                                                                        // 0x00544d98
                                                                                        charge(ctx, 12);
                                                                                        a1 = 2;
                                                                                        a2 = 1;
                                                                                        a3 = s3;
                                                                                        sh(s5, sp, 0x16);
                                                                                        s5 = addiu(s5, 1);
                                                                                        jal(ctx, 0x544DA8u, gen::fn_sub_5438C0_005438c0);
                                                                                        a0 = s6;
                                                                                        s0 = v0;
                                                                                        a2 = 1;
                                                                                        a1 = 2;
                                                                                        a3 = s3;
                                                                                        if (s0 != a2) {
                                                                                            goto L_00545120;
                                                                                        }
                                                                                        // 0x00544dc8
                                                                                        charge(ctx, 14);
                                                                                        s2 = addiu(s2, 2);
                                                                                        sh(s0, sp, 0x16);
                                                                                        s2 = addiu(s2, 2);
                                                                                        jal(ctx, 0x544DD0u, gen::fn_sub_5438C0_005438c0);
                                                                                        s2 = addiu(s2, 4);
                                                                                        s1 = v0;
                                                                                        s2 = addiu(s2, 4);
                                                                                        a1 = 4;
                                                                                        s2 = addiu(s2, 4);
                                                                                        a0 = addiu(sp, 0x18);
                                                                                        s2 = addiu(s2, 4);
                                                                                        a2 = 1;
                                                                                        a3 = s3;
                                                                                        if (s1 != s0) {
                                                                                            goto L_00545120;
                                                                                        }
                                                                                        // 0x00544e00
                                                                                        charge(ctx, 9);
                                                                                        lw(v0, s4, enc::kLoop);
                                                                                        link(ctx, 0x544E04u);  // $ra first: the delay slot below depends on it
                                                                                        sw(v0, sp, 0x18);
                                                                                        call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                        s0 = v0;
                                                                                        a0 = addiu(sp, 0x18);
                                                                                        a1 = 4;
                                                                                        a2 = 1;
                                                                                        a3 = s3;
                                                                                        if (s0 != s1) {
                                                                                            goto L_00545120;
                                                                                        }
                                                                                        // 0x00544e24
                                                                                        charge(ctx, 9);
                                                                                        lw(v0, s4, enc::kLoop + 4);
                                                                                        link(ctx, 0x544E28u);  // $ra first: the delay slot below depends on it
                                                                                        sw(v0, sp, 0x18);
                                                                                        call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                        s1 = v0;
                                                                                        a0 = addiu(sp, 0x18);
                                                                                        a1 = 4;
                                                                                        a2 = 1;
                                                                                        a3 = s3;
                                                                                        if (s1 != s0) {
                                                                                            goto L_00545120;
                                                                                        }
                                                                                        // 0x00544e48
                                                                                        charge(ctx, 9);
                                                                                        lw(v0, s4, enc::kLoop + 8);
                                                                                        link(ctx, 0x544E4Cu);  // $ra first: the delay slot below depends on it
                                                                                        sw(v0, sp, 0x18);
                                                                                        call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                        s0 = v0;
                                                                                        a0 = addiu(sp, 0x18);
                                                                                        a1 = 4;
                                                                                        a2 = 1;
                                                                                        a3 = s3;
                                                                                        if (s0 != s1) {
                                                                                            goto L_00545120;
                                                                                        }
                                                                                        // 0x00544e6c
                                                                                        charge(ctx, 5);
                                                                                        lw(v0, s4, enc::kLoop + 12);
                                                                                        link(ctx, 0x544E70u);  // $ra first: the delay slot below depends on it
                                                                                        sw(v0, sp, 0x18);
                                                                                        call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                        cc = v0 != s0;  // the condition, before the delay slot changes it
                                                                                        v0 = 0;
                                                                                        if (!cc) {
                                                                                            // 0x00544e80
                                                                                            charge(ctx, 4);
                                                                                            lw(v1, s4, enc::kLoopCnt);
                                                                                            v0 = slt(s5, v1);
                                                                                            a0 = s6;
                                                                                            if (v0 == 0) {
                                                                                                goto L_00544e90;
                                                                                            }
                                                                                            backedge(ctx);
                                                                                            continue;
                                                                                        }
                                                                                        break;
                                                                                    }
                                                                                }
                                                                            }
                                                                            // 0x00545124 (the shared epilogue, written out on this path)
                                                                            charge(ctx, 12);
                                                                            ld(s0, sp, 0x20);
                                                                            ld(s1, sp, 0x28);
                                                                            ld(s2, sp, 0x30);
                                                                            ld(s3, sp, 0x38);
                                                                            ld(s4, sp, 0x40);
                                                                            ld(s5, sp, 0x48);
                                                                            ld(s6, sp, 0x50);
                                                                            ld(s7, sp, 0x58);
                                                                            ld(fp, sp, 0x60);
                                                                            ld(ra, sp, 0x68);
                                                                            sp = addiu(sp, 0x70);
                                                                            return;
                                                                        }
                                                                    L_00544e90:
                                                                        charge(ctx, 4);
                                                                        lb(s0, s4, enc::kAinf);
                                                                        v0 = 1;
                                                                        if (s0 != v0) {
                                                                            lb(s0, s4, enc::kCinf);
                                                                        } else {
                                                                            // 0x00544ea0
                                                                            charge(ctx, 2);
                                                                            v0 = 0x41490000;
                                                                            if (v1 == 0) {
                                                                                // 0x00544ea8
                                                                                charge(ctx, 8);
                                                                                a0 = addiu(sp, 0x18);
                                                                                a1 = 4;
                                                                                a2 = 1;
                                                                                a3 = s3;
                                                                                link(ctx, 0x544EB8u);  // $ra first: the delay slot below depends on it
                                                                                sw(zero, sp, 0x18);
                                                                                call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                cc = v0 != s0;  // the condition, before the delay slot changes it
                                                                                v0 = 0;
                                                                                if (!cc) {
                                                                                    // 0x00544ec8
                                                                                    charge(ctx, 2);
                                                                                    s2 = addiu(s2, 4);
                                                                                    v0 = 0x41490000;
                                                                                    goto L_00544ed0;
                                                                                }
                                                                                // 0x00545124 (the shared epilogue, written out on this path)
                                                                                charge(ctx, 12);
                                                                                ld(s0, sp, 0x20);
                                                                                ld(s1, sp, 0x28);
                                                                                ld(s2, sp, 0x30);
                                                                                ld(s3, sp, 0x38);
                                                                                ld(s4, sp, 0x40);
                                                                                ld(s5, sp, 0x48);
                                                                                ld(s6, sp, 0x50);
                                                                                ld(s7, sp, 0x58);
                                                                                ld(fp, sp, 0x60);
                                                                                ld(ra, sp, 0x68);
                                                                                sp = addiu(sp, 0x70);
                                                                                return;
                                                                            }
                                                                        L_00544ed0:
                                                                            charge(ctx, 10);
                                                                            a0 = addiu(sp, 0x18);
                                                                            v0 = v0 | 0x4E46;
                                                                            a1 = 4;
                                                                            a2 = 1;
                                                                            a3 = s3;
                                                                            link(ctx, 0x544EE4u);  // $ra first: the delay slot below depends on it
                                                                            sw(v0, sp, 0x18);
                                                                            call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                            s1 = v0;
                                                                            v0 = 0;
                                                                            if (s1 == s0) {
                                                                                // 0x00544ef8
                                                                                charge(ctx, 10);
                                                                                v0 = 24;
                                                                                a0 = addiu(sp, 0x18);
                                                                                a1 = 4;
                                                                                a2 = 1;
                                                                                a3 = s3;
                                                                                link(ctx, 0x544F0Cu);  // $ra first: the delay slot below depends on it
                                                                                sw(v0, sp, 0x18);
                                                                                call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                s5 = v0;
                                                                                s2 = addiu(s2, 4);
                                                                                if (s5 != s1) {
                                                                                L_00545120:
                                                                                    charge(ctx, 1);
                                                                                    v0 = 0;
                                                                                } else {
                                                                                    // 0x00544f20
                                                                                    charge(ctx, 8);
                                                                                    a0 = addiu(s4, enc::kAinfData);
                                                                                    a1 = 1;
                                                                                    a2 = 16;
                                                                                    a3 = s3;
                                                                                    jal(ctx, 0x544F2Cu, gen::fn_sub_5438C0_005438c0);
                                                                                    v1 = 16;
                                                                                    s2 = addiu(s2, 4);
                                                                                    if (v0 != v1) {
                                                                                        goto L_00545120;
                                                                                    }
                                                                                    // 0x00544f40
                                                                                    charge(ctx, 10);
                                                                                    lhu(v0, s4, enc::kAinfVol);
                                                                                    a0 = s6;
                                                                                    a1 = 2;
                                                                                    a2 = 1;
                                                                                    a3 = s3;
                                                                                    link(ctx, 0x544F54u);  // $ra first: the delay slot below depends on it
                                                                                    sh(v0, sp, 0x16);
                                                                                    call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                    s0 = v0;
                                                                                    s2 = addiu(s2, 16);
                                                                                    if (s0 != s5) {
                                                                                        goto L_00545120;
                                                                                    }
                                                                                    // 0x00544f68
                                                                                    charge(ctx, 9);
                                                                                    a0 = s6;
                                                                                    a1 = 2;
                                                                                    a2 = 1;
                                                                                    a3 = s3;
                                                                                    link(ctx, 0x544F78u);  // $ra first: the delay slot below depends on it
                                                                                    sh(zero, sp, 0x16);
                                                                                    call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                    s1 = v0;
                                                                                    s2 = addiu(s2, 2);
                                                                                    if (s1 != s0) {
                                                                                        goto L_00545120;
                                                                                    }
                                                                                    // 0x00544f8c
                                                                                    charge(ctx, 10);
                                                                                    lhu(v0, s4, enc::kAinfPanL);
                                                                                    a0 = s6;
                                                                                    a1 = 2;
                                                                                    a2 = 1;
                                                                                    a3 = s3;
                                                                                    link(ctx, 0x544FA0u);  // $ra first: the delay slot below depends on it
                                                                                    sh(v0, sp, 0x16);
                                                                                    call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                    s0 = v0;
                                                                                    s2 = addiu(s2, 2);
                                                                                    if (s0 != s1) {
                                                                                        goto L_00545120;
                                                                                    }
                                                                                    // 0x00544fb4
                                                                                    charge(ctx, 10);
                                                                                    lhu(v0, s4, enc::kAinfPanR);
                                                                                    a0 = s6;
                                                                                    a1 = 2;
                                                                                    a2 = 1;
                                                                                    a3 = s3;
                                                                                    sh(v0, sp, 0x16);
                                                                                    s2 = addiu(s2, 2);
                                                                                    jal(ctx, 0x544FCCu, gen::fn_sub_5438C0_005438c0);
                                                                                    cc = v0 != s0;  // the condition, before the delay slot changes it
                                                                                    v0 = 0;
                                                                                    if (!cc) {
                                                                                        // 0x00544fdc
                                                                                        charge(ctx, 3);
                                                                                        s2 = addiu(s2, 2);
                                                                                        lb(s0, s4, enc::kCinf);
                                                                                        v0 = 1;
                                                                                        goto L_00544fe8;
                                                                                    }
                                                                                }
                                                                            }
                                                                            // 0x00545124 (the shared epilogue, written out on this path)
                                                                            charge(ctx, 12);
                                                                            ld(s0, sp, 0x20);
                                                                            ld(s1, sp, 0x28);
                                                                            ld(s2, sp, 0x30);
                                                                            ld(s3, sp, 0x38);
                                                                            ld(s4, sp, 0x40);
                                                                            ld(s5, sp, 0x48);
                                                                            ld(s6, sp, 0x50);
                                                                            ld(s7, sp, 0x58);
                                                                            ld(fp, sp, 0x60);
                                                                            ld(ra, sp, 0x68);
                                                                            sp = addiu(sp, 0x70);
                                                                            return;
                                                                        }
                                                                    L_00544fe8:
                                                                        charge(ctx, 2);
                                                                        if (s0 != v0) {
                                                                            lw(v1, s4, enc::kHdrOfs);
                                                                        } else {
                                                                            // 0x00544ff0
                                                                            charge(ctx, 3);
                                                                            lw(v0, s4, enc::kLoopCnt);
                                                                            cc = v0 != 0;  // the condition, before the delay slot changes it
                                                                            v0 = 0x43490000;
                                                                            if (!cc) {
                                                                                // 0x00544ffc
                                                                                charge(ctx, 8);
                                                                                a0 = addiu(sp, 0x18);
                                                                                a1 = 4;
                                                                                a2 = 1;
                                                                                a3 = s3;
                                                                                link(ctx, 0x54500Cu);  // $ra first: the delay slot below depends on it
                                                                                sw(zero, sp, 0x18);
                                                                                call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                                cc = v0 != s0;  // the condition, before the delay slot changes it
                                                                                v0 = 0;
                                                                                if (!cc) {
                                                                                    // 0x0054501c
                                                                                    charge(ctx, 2);
                                                                                    s2 = addiu(s2, 4);
                                                                                    v0 = 0x43490000;
                                                                                    goto L_00545024;
                                                                                }
                                                                                // 0x00545124 (the shared epilogue, written out on this path)
                                                                                charge(ctx, 12);
                                                                                ld(s0, sp, 0x20);
                                                                                ld(s1, sp, 0x28);
                                                                                ld(s2, sp, 0x30);
                                                                                ld(s3, sp, 0x38);
                                                                                ld(s4, sp, 0x40);
                                                                                ld(s5, sp, 0x48);
                                                                                ld(s6, sp, 0x50);
                                                                                ld(s7, sp, 0x58);
                                                                                ld(fp, sp, 0x60);
                                                                                ld(ra, sp, 0x68);
                                                                                sp = addiu(sp, 0x70);
                                                                                return;
                                                                            }
                                                                        L_00545024:
                                                                            charge(ctx, 10);
                                                                            a0 = addiu(sp, 0x18);
                                                                            v0 = v0 | 0x4E46;
                                                                            a1 = 4;
                                                                            a2 = 1;
                                                                            a3 = s3;
                                                                            link(ctx, 0x545038u);  // $ra first: the delay slot below depends on it
                                                                            sw(v0, sp, 0x18);
                                                                            call(ctx, gen::fn_sub_5438C0_005438c0);
                                                                            s1 = v0;
                                                                            v0 = 0;
                                                                            if (s1 == s0) {
                                                                                // 0x0054504c
                                                                                charge(ctx, 10);
                                                                                lw(v0, s4, enc::kCinfSize);
                                                                                a0 = addiu(sp, 0x18);
                                                                                a1 = 4;
                                                                                a2 = 1;
                                                                                a3 = s3;
                                                                                sw(v0, sp, 0x18);
                                                                                s2 = addiu(s2, 4);
                                                                                jal(ctx, 0x545064u, gen::fn_sub_5438C0_005438c0);
                                                                                if (v0 == s1) {
                                                                                    // 0x00545074
                                                                                    charge(ctx, 3);
                                                                                    lw(a2, s4, enc::kCinfSize);
                                                                                    s2 = addiu(s2, 4);
                                                                                    if (a2 != 0) {
                                                                                        // 0x00545080
                                                                                        charge(ctx, 3);
                                                                                        lw(a0, s4, enc::kCinfData);
                                                                                        a1 = 1;
                                                                                        if (a0 == 0) {
                                                                                            goto L_005450a8;
                                                                                        }
                                                                                        // 0x0054508c
                                                                                        charge(ctx, 6);
                                                                                        a3 = s3;
                                                                                        jal(ctx, 0x54508Cu, gen::fn_sub_5438C0_005438c0);
                                                                                        v1 = v0;
                                                                                        lw(v0, s4, enc::kCinfSize);
                                                                                        cc = v1 != v0;  // the condition, before the delay slot changes it
                                                                                        v0 = 0;
                                                                                        if (!cc) {
                                                                                            // 0x005450a4
                                                                                            charge(ctx, 1);
                                                                                            s2 = addu(s2, v1);
                                                                                            goto L_005450a8;
                                                                                        }
                                                                                        // 0x00545124 (the shared epilogue, written out on this path)
                                                                                        charge(ctx, 12);
                                                                                        ld(s0, sp, 0x20);
                                                                                        ld(s1, sp, 0x28);
                                                                                        ld(s2, sp, 0x30);
                                                                                        ld(s3, sp, 0x38);
                                                                                        ld(s4, sp, 0x40);
                                                                                        ld(s5, sp, 0x48);
                                                                                        ld(s6, sp, 0x50);
                                                                                        ld(s7, sp, 0x58);
                                                                                        ld(fp, sp, 0x60);
                                                                                        ld(ra, sp, 0x68);
                                                                                        sp = addiu(sp, 0x70);
                                                                                        return;
                                                                                    }
                                                                                L_005450a8:
                                                                                    charge(ctx, 1);
                                                                                    lw(v1, s4, enc::kHdrOfs);
                                                                                    goto L_005450ac;
                                                                                }
                                                                                v0 = 0;
                                                                            }
                                                                            // 0x00545124 (the shared epilogue, written out on this path)
                                                                            charge(ctx, 12);
                                                                            ld(s0, sp, 0x20);
                                                                            ld(s1, sp, 0x28);
                                                                            ld(s2, sp, 0x30);
                                                                            ld(s3, sp, 0x38);
                                                                            ld(s4, sp, 0x40);
                                                                            ld(s5, sp, 0x48);
                                                                            ld(s6, sp, 0x50);
                                                                            ld(s7, sp, 0x58);
                                                                            ld(fp, sp, 0x60);
                                                                            ld(ra, sp, 0x68);
                                                                            sp = addiu(sp, 0x70);
                                                                            return;
                                                                        }
                                                                    L_005450ac:
                                                                        charge(ctx, 4);
                                                                        s0 = subu(v1, fp);
                                                                        v0 = slt(s2, s0);
                                                                        sb(zero, sp, 0x14);
                                                                        if (v0 != 0) {
                                                                            // 0x005450bc
                                                                            charge(ctx, 3);
                                                                            s1 = 1;
                                                                            a0 = s7;
                                                                            for (;;) {
                                                                                // 0x005450c8
                                                                                charge(ctx, 6);
                                                                                a1 = 1;
                                                                                a2 = 1;
                                                                                a3 = s3;
                                                                                jal(ctx, 0x5450D0u, gen::fn_sub_5438C0_005438c0);
                                                                                cc = v0 != s1;  // the condition, before the delay slot changes it
                                                                                v0 = 0;
                                                                                if (cc) {
                                                                                    break;
                                                                                }
                                                                                // 0x005450e0
                                                                                charge(ctx, 4);
                                                                                s2 = addiu(s2, 1);
                                                                                v0 = slt(s2, s0);
                                                                                a0 = s7;
                                                                                if (v0 == 0) {
                                                                                    goto L_005450f0;
                                                                                }
                                                                                backedge(ctx);
                                                                            }
                                                                            // 0x00545124 (the shared epilogue, written out on this path)
                                                                            charge(ctx, 12);
                                                                            ld(s0, sp, 0x20);
                                                                            ld(s1, sp, 0x28);
                                                                            ld(s2, sp, 0x30);
                                                                            ld(s3, sp, 0x38);
                                                                            ld(s4, sp, 0x40);
                                                                            ld(s5, sp, 0x48);
                                                                            ld(s6, sp, 0x50);
                                                                            ld(s7, sp, 0x58);
                                                                            ld(fp, sp, 0x60);
                                                                            ld(ra, sp, 0x68);
                                                                            sp = addiu(sp, 0x70);
                                                                            return;
                                                                        }
                                                                    L_005450f0:
                                                                        charge(ctx, 8);
                                                                        v0 = 0x790000;
                                                                        a3 = s3;
                                                                        lw(a0, v0, 2608);  // 0x790A30
                                                                        a1 = 1;
                                                                        a2 = fp;
                                                                        jal(ctx, 0x545100u, gen::fn_sub_5438C0_005438c0);
                                                                        if (v0 != fp) {
                                                                            v0 = 0;
                                                                        } else {
                                                                            // 0x00545110
                                                                            charge(ctx, 3);
                                                                            s2 = addu(s2, fp);
                                                                            v0 = addiu(s2, 4);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x00545124 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
}

// 0x00545158 sub_545158 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The ADX encoder's init: the first call (count 0x790A28 == 0) runs sub_543430 and clears the 8 x 760-byte handle pool
// 0x790A38; returns the incremented count. [ADXENC_Init]
void sub_545158(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545158
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 2600);  // &0x790A28
    lw(v1, s0, 0);  // 0x790A28
    sd(ra, sp, 0x8);
    if (v1 == 0) {
        // 0x00545174
        charge(ctx, 7);
        jal(ctx, 0x545174u, gen::fn_sub_543430_00543430);
        a0 = 0x790000;
        a0 = addiu(a0, 2616);  // &0x790A38
        a1 = 0;
        a2 = 6080;
        jal(ctx, 0x545188u, gen::fn_memset_00521408);
    }
    // 0x00545190 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, 0);
    ld(ra, sp, 0x8);
    v0 = addiu(v0, 1);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005451B0 sub_5451B0 -- 88 bytes; frame 0x10: ra sp+0x0
// The ADX encoder's finish: the last call runs sub_543450 and clears the handle pool. [ADXENC_Finish]
void sub_5451B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005451b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 2600);  // &0x790A28
    lw(v1, v0, 0);  // 0x790A28
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x790A28
    lw(a0, v0, 0);  // 0x790A28
    ld(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00545200
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005451d8
    charge(ctx, 9);
    jal(ctx, 0x5451D8u, gen::fn_sub_543450_00543450);
    a0 = 0x790000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 2616);  // &0x790A38
    a1 = 0;
    a2 = 6080;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00545208 sub_545208 -- 464 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// The ADX encoder's create: takes the first free handle of the 8-entry pool (0 when none), stores the channel count
// ($a0), the channel joints ($a1[0..n]) and the output joint ($a2), and fills the defaults (44100 Hz, block 18, 4
// bits, encoding 3, high-pass 500, no loops, pan -128) and two work buffers from sub_543BF0. [ADXENC_Create]
void sub_545208(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545208
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = 0x790000;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    v1 = addiu(a3, 2616);  // &0x790A38
    sd(s1, sp, 0x8);
    t0 = a1;
    sd(ra, sp, 0x18);
    t1 = a2;
    lb(v0, v1, 0);  // 0x790A38
    a1 = 0;
    if (v0 != 0) {
        // 0x0054523c
        charge(ctx, 1);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x00545240
            charge(ctx, 3);
            v0 = slti(a1, 8);
            v1 = addiu(v1, 760);
            if (v0 != 0) {
                // 0x0054524c
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
    // 0x00545264
    charge(ctx, 3);
    v1 = 8;
    v0 = 0;
    if (a1 != v1) {
        // 0x00545270
        charge(ctx, 10);
        v0 = sll(a1, 1);
        v1 = addiu(a3, 2616);
        v0 = addu(v0, a1);
        a2 = 0;
        v0 = sll(v0, 5);
        v0 = subu(v0, a1);
        v0 = sll(v0, 3);
        s1 = addu(v0, v1);
        sb(s2, s1, enc::kNchIn);
        if (i64(s2) > 0) {
            // 0x00545298
            charge(ctx, 2);
            a3 = addiu(s1, enc::kSjIn);
            for (;;) {
                // 0x005452a0
                charge(ctx, 8);
                v0 = sll(a2, 2);
                a2 = addiu(a2, 1);
                v1 = addu(v0, t0);
                v0 = addu(a3, v0);
                lw(a0, v1, 0);
                a1 = slt(a2, s2);
                sw(a0, v0, 0);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x005452c0
        charge(ctx, 30);
        s0 = 0x7FFF0000;
        sw(t1, s1, enc::kSjOut);
        sb(zero, s1, enc::kState);
        a1 = 0;
        sw(zero, s1, enc::kCnt40);
        a2 = 4;
        sw(zero, s1, enc::kOutBytes);
        a3 = 4;
        sw(zero, s1, enc::kSmplDone);
        a0 = 0;
        link(ctx, 0x5452E8u);  // $ra first: the delay slot below depends on it
        sw(s0, s1, 52);
        call(ctx, gen::fn_sub_53A3B8_0053a3b8);
        v1 = 4;
        a1 = 128;
        a2 = 3;
        div(a1, v1);
        a3 = 0xAC44;
        t0 = 18;
        t1 = 4;
        t2 = 500;
        t3 = 32;
        sw(a2, s1, enc::kEncoding);
        a0 = 32;
        sw(a3, s1, enc::kRate);
        sw(t0, s1, enc::kBlockSize);
        sw(v1, s1, enc::kBits);
        sw(v0, s1, enc::kHdrOfs);
        sw(s2, s1, enc::kNch);
        if (t1 == 0) {
            brk(ctx, 0x545334u, 0x7u);
        }
        // 0x00545338
        charge(ctx, 34);
        sw(t2, s1, enc::kHighpass);
        sw(s0, s1, enc::kTotal);
        sw(zero, s1, enc::kAlignSmpl);
        sw(zero, s1, enc::kLoopCnt);
        sw(zero, s1, enc::kLoop);
        sw(zero, s1, enc::kLoop + 4);
        sw(zero, s1, enc::kLoop + 8);
        sw(zero, s1, enc::kLoop + 12);
        sw(zero, s1, 56);
        sw(zero, s1, enc::kLimit);
        mflo(a1);
        sw(a1, s1, enc::kWorkSize);
        link(ctx, 0x545368u);  // $ra first: the delay slot below depends on it
        sw(s0, s1, 64);
        call(ctx, gen::fn_sub_543BF0_00543bf0);
        lw(a0, s1, enc::kWorkSize);
        link(ctx, 0x545374u);  // $ra first: the delay slot below depends on it
        sw(v0, s1, enc::kWork);
        call(ctx, gen::fn_sub_543BF0_00543bf0);
        sh(zero, s1, enc::kHist + 4);
        v1 = si(-128);
        sw(v0, s1, enc::kWork + 4);
        sh(v1, s1, enc::kAinfPanR);
        a0 = addiu(s1, enc::kAinfData);
        sh(v1, s1, enc::kAinfPanL);
        a1 = 0;
        sh(zero, s1, enc::kHist);
        a2 = 16;
        sh(zero, s1, enc::kHist + 6);
        sh(zero, s1, enc::kHist + 2);
        sb(zero, s1, enc::kAinf);
        link(ctx, 0x5453ACu);  // $ra first: the delay slot below depends on it
        sh(zero, s1, enc::kAinfVol);
        call(ctx, gen::fn_memset_00521408);
        v1 = 1;
        sb(v1, s1, enc::kUsed);
        v0 = s1;
    }
    // 0x005453c0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005453D8 sub_5453D8 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The ADX encoder's destroy: under the CRI lock, frees the two work buffers (+128 / +132) through sub_543C90 and marks
// the handle free. [ADXENC_Destroy]
void sub_5453D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005453d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x00545430
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005453ec
    charge(ctx, 5);
    jal(ctx, 0x5453ECu, gen::fn_sub_539818_00539818);
    lw(v0, s0, enc::kWork);
    a0 = v0;
    if (v0 != 0) {
        // 0x00545400
        charge(ctx, 2);
        jal(ctx, 0x545400u, gen::fn_sub_543C90_00543c90);
    }
    // 0x00545408
    charge(ctx, 3);
    lw(a0, s0, enc::kWork + 4);
    if (a0 == 0) {
        sw(zero, s0, enc::kUsed);
    } else {
        // 0x00545414
        charge(ctx, 3);
        jal(ctx, 0x545414u, gen::fn_sub_543C90_00543c90);
        sw(zero, s0, enc::kUsed);
    }
    // 0x00545420
    charge(ctx, 4);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00545448 sub_545448 -- 292 bytes; frame 0x50: s1 sp+0x18, s5 sp+0x38, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x40
// The ADX encoder's start: for each channel joint, takes 2 * (+104) bytes of line 0, clears them and puts them back as
// data (spins forever when the joint gives less), then resets the counters (+40 / +44 / +48), the state (+1 = 1) and
// the end flag (+3). [ADXENC_Start]
void sub_545448(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545448
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s5, sp, 0x38);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x40);
    lw(v1, s1, enc::kNch);
    s5 = 0;
    if (i64(v1) > 0) {
        // 0x00545478
        charge(ctx, 2);
        s4 = 0;
        for (;;) {
            // 0x00545480
            charge(ctx, 4);
            lw(v0, s1, enc::kAlignSmpl);
            s0 = sll(v0, 1);
            a2 = s0;
            if (i64(s0) > 0) {
                // 0x00545490
                charge(ctx, 12);
                s3 = addiu(s1, enc::kSjIn);
                a1 = 0;
                s2 = addu(s3, s4);
                lw(a0, s2, 0);
                lw(v1, a0, 0);
                lw(v0, v1, 24);
                a3 = sp;
                jalr(ctx, 0x5454A8u, v0.u());
                a1 = 0;
                lw(v0, sp, 0x4);
                a2 = v0;
                if (v0 != s0) {
                    goto L_005454c0_4;
                }
                // 0x005454f8
                charge(ctx, 10);
                link(ctx, 0x5454F8u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0x0);
                call(ctx, gen::fn_memset_00521408);
                v1 = addu(s3, s4);
                lw(a0, v1, 0);
                a1 = 1;
                lw(v1, a0, 0);
                lw(v0, v1, 32);
                a2 = sp;
                jalr(ctx, 0x545514u, v0.u());
                lw(v1, s1, enc::kNch);
            }
            // 0x00545520
            charge(ctx, 4);
            s5 = addiu(s5, 1);
            v0 = slt(s5, v1);
            s4 = addiu(s4, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00545530 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    v0 = 1;
    sw(zero, s1, enc::kCnt40);
    sb(v0, s1, enc::kState);
    sw(zero, s1, enc::kOutBytes);
    sw(zero, s1, enc::kSmplDone);
    sb(zero, s1, enc::kEnd);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
    return;
L_005454c0_4:
    charge(ctx, 6);
    lw(a0, s2, 0);
    lw(v1, a0, 0);
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x5454CCu, v0.u());
    for (;;) {
        // 0x005454d8
        charge(ctx, 7);
        backedge(ctx);
    }
}

// 0x00545570 sub_545570 -- 12 bytes; leaf frame (no stack)
// The ADX encoder's stop request: sets the end flag (+3) and returns 1.
void sub_545570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00545570
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 1;
    sb(v0, a0, enc::kEnd);
}

// 0x00545580 sub_545580 -- 8 bytes; leaf frame (no stack)
// Stores $a1 as the encoder's sample rate (+92).
void sub_545580(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00545580
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, enc::kRate);
}

// 0x00545590 sub_545590 -- 8 bytes; leaf frame (no stack)
// Stores $a1 as the encoder's channel count (+88).
void sub_545590(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00545590
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, enc::kNch);
}

// 0x00545610 sub_545610 -- 12 bytes; leaf frame (no stack)
// Stores $a1 as the encoder's total sample count (+96) and the encode limit (+60).
void sub_545610(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00545610
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, enc::kTotal);
    sw(a1, a0, enc::kLimit);
}

// 0x00545838 sub_545838 -- 100 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Configures an encoder: channels ($a1), sample rate ($a2), total samples ($a3), and the header offset 284 (+72).
void sub_545838(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545838
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a3;
    jal(ctx, 0x545854u, gen::fn_sub_545590_00545590);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x545860u, gen::fn_sub_545580_00545580);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x54586Cu, gen::fn_sub_545610_00545610);
    a0 = s1;
    ld(s0, sp, 0x0);
    a1 = 284;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x00545588
    charge(ctx, 2);
    sw(a1, a0, enc::kHdrOfs);
}

// 0x00545948 sub_545948 -- 364 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// The encoder's header stage: takes each channel's first sample (the predictor history at +712 / +716), writes the
// header (sub_544A00), adds its size to the output count (+44), primes each channel's predictor (sub_543CD8 with the
// high-pass and rate) and moves to state 2.
void sub_545948(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545948
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = addiu(s1, enc::kHist);
    sd(s3, sp, 0x28);
    s3 = 0;
    sd(s4, sp, 0x30);
    s0 = addiu(s1, enc::kSjIn);
    sd(ra, sp, 0x38);
    lw(s4, s1, enc::kSjOut);
    for (;;) {
        // 0x005459b0
        charge(ctx, 4);
        lw(v1, s1, enc::kNch);
        v0 = slt(s3, v1);
        a3 = sp;
        if (v0 == 0) {
            goto L_005459fc;
        }
        // 0x005459c0
        charge(ctx, 11);
        lw(t0, s0, 0);
        a1 = 1;
        a2 = 2;
        lw(v0, t0, 0);
        lw(v1, v0, 24);
        a0 = t0;
        jalr(ctx, 0x5459D4u, v1.u());
        a1 = 1;
        lw(v0, sp, 0x4);
        a2 = sp;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00545980
        charge(ctx, 12);
        lw(a3, s0, 0);
        s0 = addiu(s0, 4);
        lw(v1, sp, 0x0);
        s3 = addiu(s3, 1);
        lw(t0, a3, 0);
        a0 = a3;
        lhu(v0, v1, 0);
        sh(v0, s2, 0);
        sh(v0, s2, 4);
        lw(v0, t0, 28);
        s2 = addiu(s2, 2);
        jalr(ctx, 0x5459A8u, v0.u());
    }
    // 0x005459ec
    charge(ctx, 4);
    lw(v1, s1, enc::kNch);
    v0 = slt(s3, v1);
    if (v0 != 0) {
        ld(s0, sp, 0x10);
    } else {
    L_005459fc:
        charge(ctx, 2);
        if (i64(v1) <= 0) {
            a0 = s1;
        } else {
            // 0x00545a04
            charge(ctx, 3);
            s3 = v1;
            v1 = addiu(s1, 136);
            a0 = addiu(s1, 140);
            for (;;) {
                // 0x00545a10
                charge(ctx, 8);
                lhu(v0, v1, 576);
                s3 = addiu(s3, -1);
                sh(v0, v1, 0);
                v1 = addiu(v1, 2);
                lhu(v0, a0, 576);
                sh(v0, a0, 0);
                a0 = addiu(a0, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00545a30
            charge(ctx, 1);
            a0 = s1;
        }
        // 0x00545a34
        charge(ctx, 5);
        a1 = s4;
        jal(ctx, 0x545A34u, gen::fn_sub_544A00_00544a00);
        a0 = v0;
        s3 = 0;
        if (a0 != 0) {
            // 0x00545a48
            charge(ctx, 5);
            lw(v0, s1, enc::kOutBytes);
            lw(v1, s1, enc::kNch);
            v0 = addu(v0, a0);
            sw(v0, s1, enc::kOutBytes);
            if (i64(v1) > 0) {
                // 0x00545a5c
                charge(ctx, 3);
                s0 = addiu(s1, enc::kWork);
                lw(a0, s0, 0);
                for (;;) {
                    // 0x00545a68
                    charge(ctx, 9);
                    s0 = addiu(s0, 4);
                    lw(a1, s1, enc::kHighpass);
                    s3 = addiu(s3, 1);
                    link(ctx, 0x545A74u);  // $ra first: the delay slot below depends on it
                    lw(a2, s1, enc::kRate);
                    call(ctx, gen::fn_sub_543CD8_00543cd8);
                    lw(v0, s1, enc::kNch);
                    v0 = slt(s3, v0);
                    if (v0 == 0) {
                        break;
                    }
                    lw(a0, s0, 0);
                    backedge(ctx);
                }
            }
            // 0x00545a8c
            charge(ctx, 2);
            v0 = 2;
            sb(v0, s1, enc::kState);
        }
        // 0x00545a94
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x00545a98 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00545AB8 sub_545AB8 -- 148 bytes; frame 0x20: s1 sp+0x8, ra sp+0x10, s0 sp+0x0
// The encoder's data stage: encodes blocks (sub_544850) until none is ready, counting the output (+44); at the sample
// limit (+48 >= +60) sets the end flag; with the end flag set writes the footer and moves to state 3.
void sub_545AB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545ab8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    for (;;) {
    L_00545acc:
        charge(ctx, 3);
        lb(v0, s0, enc::kEnd);
        s1 = 1;
        if (v0 != 0) {
            goto L_00545b20;
        }
        // 0x00545ad8
        charge(ctx, 2);
        for (;;) {
            // 0x00545b00
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x545B00u, gen::fn_sub_544850_00544850);
            a1 = v0;
            if (a1 == 0) {
                break;
            }
            lw(v0, s0, enc::kOutBytes);
            backedge(ctx);
            // 0x00545ae0
            charge(ctx, 6);
            lw(v1, s0, enc::kSmplDone);
            lw(a0, s0, enc::kLimit);
            v0 = addu(v0, a1);
            v1 = slt(v1, a0);
            sw(v0, s0, enc::kOutBytes);
            if (v1 != 0) {
                continue;
            }
            goto L_00545af8_4;
        }
        break;
    }
    // 0x00545b14
    charge(ctx, 2);
    ld(s0, sp, 0x0);
    // 0x00545b3c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    return;
L_00545af8_4:
    charge(ctx, 2);
    sb(s1, s0, enc::kEnd);
    backedge(ctx);
    goto L_00545acc;
L_00545b20:
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x545B20u, gen::fn_sub_544900_00544900);
    if (i64(v0) <= 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00545b30
        charge(ctx, 3);
        v0 = 3;
        sb(v0, s0, enc::kState);
        ld(s0, sp, 0x0);
    }
    // 0x00545b3c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00545B50 sub_545B50 -- 64 bytes; frame 0x10: ra sp+0x0
// Runs one encoder by its state: 1 = header stage, 2 = data stage; returns 2 otherwise.
void sub_545B50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00545b50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    lb(v1, a0, enc::kState);
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 2;
    if (!cc) {
        // 0x00545b68
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_545948_00545948(ctx);  // tail call
        return;
    }
    // 0x00545b78
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x00545b88
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00545b80
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545AB8_00545ab8(ctx);  // tail call
}

// 0x00545B90 sub_545B90 -- 96 bytes; frame 0x20: ra sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// The ADX encoder server: runs every in-use handle of the pool (8 entries, 760 bytes apart). [ADXENC_ExecServer]
void sub_545B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545b90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x790000;
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 2616);  // &0x790A38
    sd(s1, sp, 0x8);
    s1 = 7;
    sd(s2, sp, 0x10);
    s2 = 1;
    for (;;) {
        // 0x00545bb8
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00545bc4
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x545BC4u, gen::fn_sub_545B50_00545b50);
            s1 = addiu(s1, -1);
        }
        // 0x00545bd0
        charge(ctx, 2);
        s0 = addiu(s0, 760);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00545bd8
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00545CC8 sub_545CC8 -- 76 bytes; frame 0x10: ra sp+0x0
// The ADXSTM finish: the last release (count 0x792BB8) clears the 3840-byte streamer pool 0x792BD8.
void sub_545CC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00545cc8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 11192);  // &0x792BB8
    lw(v0, v1, 0);  // 0x792BB8
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x792BB8
    if (v0 != 0) {
        // 0x00545d08
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00545ce8
    charge(ctx, 7);
    a0 = 0x790000;
    ld(ra, sp, 0x0);
    a1 = 0;
    a0 = addiu(a0, 11224);  // &0x792BD8
    a2 = 3840;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00546770 sub_546770 -- 24 bytes; leaf frame (no stack)
// Bumps ADXSTM's read counter 0x792BD4 and returns it.
void sub_546770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00546770
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, 11220);  // &0x792BD4
    lw(v0, v1, 0);  // 0x792BD4
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x792BD4
}

// 0x00546EC0 sub_546EC0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stores sub_546410($a0) into *$a1 and returns 1.
void sub_546EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546ec0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x546ECCu, gen::fn_sub_546410_00546410);
    sw(v0, s0, 0);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00546EF0 sub_546EF0 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// The locked form of sub_546F48 (under the ADXSTM lock coshl_2 / sub_545C40): returns its result.
void sub_546EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00546ef0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x546F0Cu, gen::fn_coshl_2_00545c38);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x546F1Cu, gen::fn_sub_546F48_00546f48);
    s0 = v0;
    jal(ctx, 0x546F24u, gen::fn_sub_545C40_00545c40);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00546F48 sub_546F48 -- 24 bytes; leaf frame (no stack)
// A streamer's file position: *$a1 = +28, *$a2 = +24; returns 1.
void sub_546F48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00546f48
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 28);
    v0 = 1;
    sw(v1, a1, 0);
    lw(a1, a0, 24);
    sw(a1, a2, 0);
}

// 0x00546F98 sub_546F98 -- 8 bytes; leaf frame (no stack)
// Returns word +4 of the streamer.
void sub_546F98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00546f98
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 4);
}

// 0x005470E8 sub_5470E8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The locked form of sub_547120 (the file size under the ADXSTM lock).
void sub_5470E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005470e8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5470F4u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x5470FCu, gen::fn_sub_547120_00547120);
    s0 = v0;
    jal(ctx, 0x547104u, gen::fn_sub_545C40_00545c40);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00547120 sub_547120 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls cvFsGetFileSize.
void sub_547120(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00547120
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_cvFsGetFileSize_005566d0(ctx);  // tail call
}

// 0x005471B8 sub_5471B8 -- 8 bytes; leaf frame (no stack)
// Returns the signed byte +68 of the streamer.
void sub_5471B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005471b8
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 68);
}

// 0x00547248 sub_547248 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The file size in 2 KiB sectors, rounded up, into *$a1 (cvFsGetFileSize); returns 1.
void sub_547248(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547248
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x547254u, gen::fn_cvFsGetFileSize_005566d0);
    a1 = v0;
    v0 = 1;
    a2 = addiu(a1, 2047);
    a0 = slti(a1, 0);
    v1 = a1;
    if (a0 != 0) v1 = a2;
    v1 = sra(v1, 11);
    a0 = sll(v1, 11);
    a2 = addiu(v1, 1);
    a1 = subu(a1, a0);
    sw(v1, s0, 0);
    if (i64(a1) > 0) {
        // 0x0054728c
        charge(ctx, 1);
        sw(a2, s0, 0);
    }
    // 0x00547290 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005472E8 sub_5472E8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The file size in bytes into *$a1 (cvFsGetFileSize); returns 1.
void sub_5472E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005472e8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x5472F4u, gen::fn_cvFsGetFileSize_005566d0);
    sw(v0, s0, 0);
    v0 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00547418 sub_547418 -- 16 bytes; leaf frame (no stack)
// Sets a streamer's request size: +20 = $a1 sectors, +16 = $a1 << 11 bytes.
void sub_547418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00547418
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = sll(a1, 11);
    sw(a1, a0, 20);
    sw(v0, a0, 16);
}

// 0x00547468 sub_547468 -- 28 bytes; frame 0x10: ra sp+0x0
// Sets word +12 of the streamer to $a1, then tail-calls sub_5463A8 (ADXSTM_SetBufSize).
void sub_547468(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547468
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sw(a1, a0, 12);
    a1 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5463A8_005463a8(ctx);  // tail call
}

// 0x005474B8 sub_5474B8 -- 12 bytes; leaf frame (no stack)
// Stores $a0 in ADXSTM's word 0x792BD0.
void sub_5474B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005474b8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x790000;
    sw(a0, v0, 11216);  // 0x792BD0
}

// 0x00547500 __errno_2 -- 12 bytes; leaf frame (no stack)
// Returns ADXSTM's word 0x792BD0.
void __errno_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00547500
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x790000;
    lw(v0, v1, 11216);  // 0x792BD0
}

// 0x00547548 sub_547548 -- 12 bytes; leaf frame (no stack)
// Returns word +76 of the record at +8 of $a0.
void sub_547548(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00547548
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, 8);
    lw(v0, v1, 76);
}

// 0x00547590 sub_547590 -- 8 bytes; leaf frame (no stack)
// Returns the signed byte +2 (the status) of a streamer.
void sub_547590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00547590
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, 2);
}

// 0x00547598 sub_547598 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The locked form of sub_5475C8.
void sub_547598(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547598
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5475A4u, gen::fn_coshl_2_00545c38);
    a0 = s0;
    jal(ctx, 0x5475ACu, gen::fn_sub_5475C8_005475c8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_545C40_00545c40(ctx);  // tail call
}

// 0x005475C8 sub_5475C8 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Waits for a streamer: when it has a file (+80) and no read is pending (+8 == 0), sets +69 and runs ADXSTMF_ExecHndl
// whenever the try-lock cosl_2(0x792BCC) succeeds, until the handle clears +69.
void sub_5475C8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005475c8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s0, 80);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005475ec
        charge(ctx, 3);
        lw(v0, s0, 8);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x005475f8
            charge(ctx, 6);
            v0 = 1;
            v1 = 0x790000;
            sb(v0, s0, 69);
            s1 = addiu(v1, 11212);  // &0x792BCC
            s2 = 1;
            for (;;) {
                // 0x00547610
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x547610u, gen::fn_cosl_2_00545c20);
                a0 = s0;
                if (v0 == s2) {
                    // 0x00547620
                    charge(ctx, 3);
                    jal(ctx, 0x547620u, gen::fn_ADXSTMF_ExecHndl_00546bb0);
                    sw(zero, s1, 0);
                }
                // 0x0054762c
                charge(ctx, 3);
                lb(v0, s0, 69);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00547638
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0054763c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00547650 sub_547650 -- 24 bytes; frame 0x10: ra sp+0x0
// An error callback adapter: passes $a1 (the message) to ADXERR_CallErrFunc1.
void sub_547650(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547650
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x00547A58 log10l_3 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_541D18.
void log10l_3(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00547a58
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541D18_00541d18(ctx);  // tail call
}

// 0x00547AA8 sub_547AA8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_541D30.
void sub_547AA8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00547aa8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541D30_00541d30(ctx);  // tail call
}

// 0x00547F78 sub_547F78 -- 84 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Creates an ADXT handle over a caller's work area with its first 1 KiB as the header buffer: sub_547C18(2, $a0 +
// 1024, $a1 - 1024), then (when created) sub_55F390(handle, $a0, 1024).
void sub_547F78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547f78
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = addiu(a1, -1024);
    sd(s0, sp, 0x0);
    s0 = a0;
    a1 = addiu(s0, 1024);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    a0 = 2;
    jal(ctx, 0x547F94u, gen::fn_sub_547C18_00547c18);
    s1 = v0;
    a1 = s0;
    if (s1 != 0) {
        // 0x00547fa8
        charge(ctx, 4);
        a0 = s1;
        a2 = 1024;
        jal(ctx, 0x547FACu, gen::fn_sub_55F390_0055f390);
        v0 = s1;
    }
    // 0x00547fb8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00548250 sub_548250 -- 36 bytes; frame 0x10: ra sp+0x0
// Runs sub_548278 under the CRI lock (sub_539848 / sub_539850).
void sub_548250(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00548250
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x548258u, gen::fn_sub_539848_00539848);
    jal(ctx, 0x548260u, gen::fn_sub_548278_00548278);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00548300 sub_548300 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_548278.
void sub_548300(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00548300
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_548278_00548278(ctx);  // tail call
}

// 0x005485A8 sub_5485A8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Runs sub_5485D8($a0) under the CRI lock.
void sub_5485A8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005485a8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5485B4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x5485BCu, gen::fn_sub_5485D8_005485d8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00548800 sub_548800 -- 56 bytes; leaf frame (no stack)
// Sets ADXT's time mode ($a0 into 0x793B14) and, for modes 1 and 2, the vsync rate 0x793B60 (5994 / 5000: NTSC / PAL
// hundredths of Hz).
void sub_548800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00548800
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 1;
    if (a0 == v0) {
        // 0x0054880c
        charge(ctx, 3);
        v1 = 0x790000;
        v0 = 5994;
        goto L_00548828;
    }
    v0 = 2;
    // 0x00548818
    charge(ctx, 2);
    if (a0 != v0) {
        v0 = 0x790000;
    } else {
        // 0x00548820
        charge(ctx, 2);
        v1 = 0x790000;
        v0 = 5000;
    L_00548828:
        charge(ctx, 2);
        sw(v0, v1, 15200);
        v0 = 0x790000;
    }
    // 0x00548830 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sw(a0, v0, 15124);
}

// 0x00548888 sub_548888 -- 200 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// An ADXT handle's play time: for states 3 / 4 from sub_541AA8(+12) (the output), for state 5 from the decoder
// (sub_543178 samples, scaled by 16 / sub_543130, and sub_543100 the rate), else 0 / 1; the time offset (+136) is
// added to *$a1.
void sub_548888(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548888
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    lbu(v0, s0, adxt::kStat);
    v1 = sll(v0, 24);
    v0 = addiu(v0, -3);
    v0 = sltiu(v0, 2);
    v1 = sra(v1, 24);
    if (v0 == 0) {
        // 0x005488d0
        charge(ctx, 3);
        v0 = 5;
        if (v1 != v0) {
            v0 = 1;
            // 0x00548920
            charge(ctx, 2);
            sw(zero, s1, 0);
            sw(v0, s2, 0);
        } else {
            // 0x005488dc
            charge(ctx, 12);
            link(ctx, 0x5488DCu);  // $ra first: the delay slot below depends on it
            lw(a0, s0, adxt::kSjd);
            call(ctx, gen::fn_sub_543178_00543178);
            lw(a0, s0, adxt::kSjd);
            link(ctx, 0x5488E8u);  // $ra first: the delay slot below depends on it
            sw(v0, s1, 0);
            call(ctx, gen::fn_sub_543100_00543100);
            lw(a0, s0, adxt::kSjd);
            link(ctx, 0x5488F4u);  // $ra first: the delay slot below depends on it
            sw(v0, s2, 0);
            call(ctx, gen::fn_sub_543130_00543130);
            v1 = 16;
            div(v1, v0);
            if (v0 == 0) {
                brk(ctx, 0x548908u, 0x7u);
            }
            // 0x0054890c
            charge(ctx, 5);
            lw(v0, s1, 0);
            mflo(v1);
            mult(v0, v0, v1);
            sw(v0, s1, 0);
        }
        // 0x00548928
        charge(ctx, 1);
        lw(v1, s0, adxt::kTimeOfs);
    } else {
        // 0x005488c0
        charge(ctx, 4);
        link(ctx, 0x5488C0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxt::kRna);
        call(ctx, gen::fn_expl_1_00541aa8);
        lw(v1, s0, adxt::kTimeOfs);
    }
    // 0x0054892c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v0, s1, 0);
    ld(s0, sp, 0x0);
    v0 = addu(v0, v1);
    ld(s2, sp, 0x10);
    sw(v0, s1, 0);
    ld(ra, sp, 0x18);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x00548AD0 sub_548AD0 -- 24 bytes; leaf frame (no stack)
// Bumps the counter 0x793B34 and returns it.
void sub_548AD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00548ad0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x790000;
    v1 = addiu(v1, 15156);  // &0x793B34
    lw(v0, v1, 0);  // 0x793B34
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x793B34
}

// 0x00548E68 sub_548E68 -- 80 bytes; frame 0x20: ra sp+0x10
// The play time in hundredths: sceInsockBind_2 (the time getter) into a stack pair, then (samples / rate) * 100 as an
// integer.
void sub_548E68(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00548e68
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = sp;
    sd(ra, sp, 0x10);
    a2 = addiu(sp, 0x4);
    jal(ctx, 0x548E74u, gen::fn_sceInsockBind_2_00548b38);
    lwc1(f1, sp, 0x0);
    cvt_s_w(f1, f1);
    at = 0x42C80000;
    mtc1(at, f0);
    lwc1(f2, sp, 0x4);
    cvt_s_w(f2, f2);
    ld(ra, sp, 0x10);
    div_s(f1, f1, f2);
    mul_s(f1, f1, f0);
    cvt_w_s(f0, f1);
    mfc1(v0, f0);
    sp = addiu(sp, 0x20);
}

// 0x00549088 sub_549088 -- 76 bytes; frame 0x10: ra sp+0x0
// An ADXT accessor (error E02080822): null reports and gives -1; status < 2 gives 0; else sub_543380(the decoder).
void sub_549088(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549088
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00549094
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10520);  // "E02080822 adxt_GetHdrLen: parameter error"
        jal(ctx, 0x549098u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
        // 0x005490c8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005490a8
    charge(ctx, 4);
    lb(v0, a0, adxt::kStat);
    v0 = slti(v0, 2);
    if (v0 != 0) {
        v0 = 0;
        // 0x005490c8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005490b8
    charge(ctx, 4);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543380_00543380(ctx);  // tail call
}

// 0x00549110 sub_549110 -- 76 bytes; frame 0x10: ra sp+0x0
// An ADXT accessor (error E02080821): as sub_549088 with sub_543388.
void sub_549110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549110
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0054911c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10568);  // "E02080821 adxt_GetFmtBps: parameter error"
        jal(ctx, 0x549120u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
        // 0x00549150 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00549130
    charge(ctx, 4);
    lb(v0, a0, adxt::kStat);
    v0 = slti(v0, 2);
    if (v0 != 0) {
        v0 = 0;
        // 0x00549150 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00549140
    charge(ctx, 4);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543388_00543388(ctx);  // tail call
}

// 0x005492C8 sub_5492C8 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Runs sub_549310($a0, $a1) under the CRI lock and returns its result.
void sub_5492C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005492c8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5492DCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x5492E8u, gen::fn_sub_549310_00549310);
    s0 = v0;
    jal(ctx, 0x5492F0u, gen::fn_sub_539850_00539850);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00549568 sub_549568 -- 48 bytes; frame 0x10: ra sp+0x0
// Returns an ADXT handle's output volume (+64, s16); null reports E02080824 and gives 0.
void sub_549568(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549568
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549588
        charge(ctx, 1);
        lh(v0, a0, adxt::kOutVol);
    } else {
        // 0x00549574
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10904);  // "E02080824 adxt_GetOutVol: parameter error"
        jal(ctx, 0x549578u, gen::fn_sub_53AE08_0053ae08);
        v0 = 0;
    }
    // 0x0054958c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005495D0 sub_5495D0 -- 28 bytes; frame 0x10: ra sp+0x0
// Calls sub_543268 on the handle's decoder (+4).
void sub_5495D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005495d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x5495D8u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, adxt::kSjd);
    call(ctx, gen::fn_sub_543268_00543268);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549638 sub_549638 -- 28 bytes; frame 0x10: ra sp+0x0
// Calls sub_5432C0 on the handle's decoder (+4).
void sub_549638(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549638
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x549640u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, adxt::kSjd);
    call(ctx, gen::fn_sub_5432C0_005432c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549690 sub_549690 -- 24 bytes; frame 0x10: ra sp+0x0
// Calls sub_543328 on the handle's decoder (+4).
void sub_549690(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549690
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543328_00543328(ctx);  // tail call
}

// 0x005496E0 sub_5496E0 -- 72 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// Probes $a0's header with sub_53A138 into the scratch record 0x997048 (2048 bytes); returns 0x997048 when the header
// is valid, else 0.
void sub_5496E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005496e0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a1 = 2048;
    sd(s0, sp, 0x20);
    s0 = 0x990000;
    s0 = addiu(s0, 28744);  // &0x997048
    a2 = addiu(sp, 0x14);
    a3 = s0;
    t0 = addiu(sp, 0x10);
    sd(ra, sp, 0x28);
    t1 = sp;
    jal(ctx, 0x549704u, gen::fn_sub_53A138_0053a138);
    v0 = 0;
    lw(v1, sp, 0x14);
    ld(ra, sp, 0x28);
    if (v1 != 0) v0 = s0;
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x005497A8 sub_5497A8 -- 8 bytes; leaf frame (no stack)
// Returns an ADXT handle's pan mode byte (+173).
void sub_5497A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005497a8
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, adxt::kPanMode);
}

// 0x005498D0 sub_5498D0 -- 176 bytes; frame 0x10: ra sp+0x0
// Sets an ADXT handle's refill threshold from a time ($f12 seconds * $a2 Hz / 32 samples per block * 18 bytes * $a1
// channels, in sectors, capped at the buffer's sectors +60) into +62 and passes it to the streamer (sub_546FA0); null
// reports E02080838.
void sub_5498D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x005498d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t1 = a0;
    sd(ra, sp, 0x0);
    t2 = a1;
    if (t1 == 0) {
        // 0x005498e4
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 11000);  // "E02080838 adxt_SetReloadTime: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x005498f8
    charge(ctx, 29);
    mtc1(a2, f0);
    cvt_s_w(f0, f0);
    lh(a3, t1, adxt::kMaxSct);
    lw(t0, t1, adxt::kStm);
    a2 = a3;
    a0 = t0;
    a2 = sll(a2, 11);
    mul_s(f0, f12, f0);
    cvt_w_s(f1, f0);
    mfc1(v1, f1);
    a1 = addiu(v1, 31);
    v0 = slti(v1, 0);
    if (v0 != 0) v1 = a1;
    v1 = sra(v1, 5);
    mult(v1, v1, t2);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    a1 = addiu(v0, 2047);
    v1 = v0;
    v0 = slti(v0, 0);
    if (v0 != 0) v1 = a1;
    v1 = sra(v1, 11);
    v0 = slt(v1, a3);
    if (v0 != 0) a3 = v1;
    a1 = sll(a3, 16);
    sh(a3, t1, adxt::kMinSct);
    a1 = sra(a1, 5);
    if (t0 != 0) {
        // 0x0054996c
        charge(ctx, 2);
        jal(ctx, 0x54996Cu, gen::fn_sub_546FA0_00546fa0);
    }
    // 0x00549974 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005499B0 sub_5499B0 -- 124 bytes; frame 0x10: ra sp+0x0
// Resets the refill threshold (+62) to 85 % of the buffer's sectors and passes it to the streamer; null reports
// E03111501.
void sub_5499B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x005499b0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a0;
    sd(ra, sp, 0x0);
    if (a3 == 0) {
        // 0x005499c0
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 11048);  // "E03111501 adxt_ResetReloadTime: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x005499d8
    charge(ctx, 16);
    lh(a2, a3, adxt::kMaxSct);
    at = 0x3F590000;
    at = at | 0x9999;
    mtc1(at, f1);
    mtc1(a2, f0);
    cvt_s_w(f0, f0);
    a2 = sll(a2, 11);
    lw(v1, a3, adxt::kStm);
    a0 = v1;
    mul_s(f0, f0, f1);
    cvt_w_s(f1, f0);
    mfc1(v0, f1);
    a1 = sll(v0, 16);
    sh(v0, a3, adxt::kMinSct);
    a1 = sra(a1, 5);
    if (v1 != 0) {
        // 0x00549a18
        charge(ctx, 2);
        jal(ctx, 0x549A18u, gen::fn_sub_546FA0_00546fa0);
    }
    // 0x00549a20 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549A70 sub_549A70 -- 88 bytes; frame 0x10: ra sp+0x0
// Sets the refill threshold (+62) to $a1 sectors and passes it to the streamer; null reports E02080839.
void sub_549A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549a70
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x00549a80
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 11096);  // "E02080839 adxt_SetReloadSct: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x00549a98
    charge(ctx, 4);
    lw(v0, v1, adxt::kStm);
    sh(a1, v1, adxt::kMinSct);
    a0 = v0;
    if (v0 != 0) {
        // 0x00549aa8
        charge(ctx, 5);
        lh(a2, v1, adxt::kMaxSct);
        a1 = sll(a1, 16);
        a1 = sra(a1, 5);
        a2 = sll(a2, 11);
        jal(ctx, 0x549AB4u, gen::fn_sub_546FA0_00546fa0);
    }
    // 0x00549abc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549B08 sub_549B08 -- 96 bytes; frame 0x10: ra sp+0x0
// The input buffer's data in sectors: the input joint's (+20) line-1 size >> 11, 0 without a joint; null reports
// E02080834 and gives -1.
void sub_549B08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549b08
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549b28
        charge(ctx, 3);
        lw(v1, a0, adxt::kSji);
        a0 = v1;
        if (v1 == 0) {
            // 0x00549b58
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00549b34
            charge(ctx, 9);
            lw(v1, v1, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x549B3Cu, v0.u());
            a0 = addiu(v0, 2047);
            v1 = slti(v0, 0);
            if (v1 != 0) v0 = a0;
            v0 = sra(v0, 11);
        }
    } else {
        // 0x00549b14
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11144);  // "E02080834 adxt_GetNumSctIbuf: parameter error"
        jal(ctx, 0x549B18u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x00549b5c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549C58 sub_549C58 -- 228 bytes; frame 0x30: s2 sp+0x10, f20 sp+0x20, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// The buffered play time in seconds (float): with the handle's state (adxt_GetStat) >= 2 and an input joint, (32 *
// (data / (18 * channels))) / rate; null reports E02080835 and gives -1.0.
void sub_549C58(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x00549c58
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a0;
    swc1(f20, sp, 0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    mtc1(zero, f20);
    sd(ra, sp, 0x18);
    if (s2 != 0) {
        // 0x00549c98
        charge(ctx, 5);
        jal(ctx, 0x549C98u, gen::fn_sub_5487A0_005487a0);
        v0 = slti(v0, 2);
        mov_s(f0, f20);
        if (v0 == 0) {
            // 0x00549cac
            charge(ctx, 3);
            lw(v1, s2, adxt::kSji);
            a0 = v1;
            if (v1 != 0) {
                // 0x00549cb8
                charge(ctx, 18);
                lw(v1, v1, 0);
                lw(v0, v1, 36);
                a1 = 1;
                jalr(ctx, 0x549CC0u, v0.u());
                a0 = s2;
                s0 = v0;
                jal(ctx, 0x549CCCu, gen::fn_sub_549000_00549000);
                s1 = v0;
                a0 = s2;
                jal(ctx, 0x549CD8u, gen::fn_sub_548F78_00548f78);
                v1 = sll(s1, 3);
                v1 = addu(v1, s1);
                mtc1(v0, f1);
                cvt_s_w(f1, f1);
                v1 = sll(v1, 1);
                div(s0, v1);
                if (v1 == 0) {
                    brk(ctx, 0x549CFCu, 0x7u);
                }
                // 0x00549d00
                charge(ctx, 8);
                mflo(s0);
                s0 = sll(s0, 5);
                mtc1(s0, f0);
                cvt_s_w(f0, f0);
                div_s(f20, f0, f1);
                mov_s(f0, f20);
            }
        }
        // 0x00549d20
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x00549c7c
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11240);  // "E02080835 adxt_GetIbufRemainTime: parameter error"
        jal(ctx, 0x549C80u, gen::fn_sub_53AE08_0053ae08);
        at = lui(0xBF80);
        mtc1(at, f0);
        ld(s0, sp, 0x0);
    }
    // 0x00549d24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    lwc1(f20, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00549D78 sub_549D78 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Whether the input buffer holds at least the refill threshold (+62 sectors); null reports E02080836 and gives -1.
void sub_549D78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549d78
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x00549da0
        charge(ctx, 3);
        lw(v1, s0, adxt::kSji);
        a0 = v1;
        if (v1 == 0) {
            // 0x00549dd0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00549dac
            charge(ctx, 9);
            lw(v1, v1, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x549DB4u, v0.u());
            lh(v1, s0, adxt::kMinSct);
            v1 = sll(v1, 11);
            v0 = slt(v0, v1);
            v0 = sltiu(v0, 1);
        }
    } else {
        // 0x00549d8c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11296);  // "E02080836 ADXT_IsIbufSafety: parameter error"
        jal(ctx, 0x549D90u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x00549dd4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00549E68 sub_549E68 -- 56 bytes; frame 0x10: ra sp+0x0
// Whether the handle's status is 5 (play end); null reports E02080802 and gives -1.
void sub_549E68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549e68
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549e88
        charge(ctx, 3);
        lb(v0, a0, adxt::kStat);
        v0 = v0 ^ 0x5;
        v0 = sltiu(v0, 1);
    } else {
        // 0x00549e74
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11344);  // "E02080802 adxt_IsCompleted: parameter error"
        jal(ctx, 0x549E78u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x00549e94 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549FE0 sub_549FE0 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_549EC8.
void sub_549FE0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00549fe0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_549EC8_00549ec8(ctx);  // tail call
}

// 0x0054A090 sub_54A090 -- 60 bytes; frame 0x10: ra sp+0x0
// Clears the handle's error fields (+96, +100, +104, +106); null reports E02080844.
void sub_54A090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a090
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x0054a09c
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 11440);  // "E02080844 adxt_ClearErrCode: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0054a0b0
    charge(ctx, 7);
    ld(ra, sp, 0x0);
    sh(zero, a0, 106);
    sh(zero, a0, adxt::kErrCode);
    sw(zero, a0, 100);
    sh(zero, a0, 104);
    sp = addiu(sp, 0x10);
}

// 0x0054A108 sub_54A108 -- 48 bytes; frame 0x10: ra sp+0x0
// Returns the handle's word +76; null reports E02080829 and gives -1.
void sub_54A108(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a108
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054a128
        charge(ctx, 1);
        lw(v0, a0, 76);
    } else {
        // 0x0054a114
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11488);  // "E02080829 adxt_GetLpCnt: parameter error"
        jal(ctx, 0x54A118u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x0054a12c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A2B8 sub_54A2B8 -- 48 bytes; frame 0x10: ra sp+0x0
// Returns the handle's input joint (+20); null reports E02080833 and gives 0.
void sub_54A2B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a2b8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054a2d8
        charge(ctx, 1);
        lw(v0, a0, adxt::kSji);
    } else {
        // 0x0054a2c4
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11584);  // "E02080833 adxt_GetInputSj: parameter error"
        jal(ctx, 0x54A2C8u, gen::fn_sub_53AE08_0053ae08);
        v0 = 0;
    }
    // 0x0054a2dc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A328 sub_54A328 -- 48 bytes; frame 0x10: ra sp+0x0
// Sets the handle's hold flag (+112) to $a1; null reports E02080830.
void sub_54A328(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a328
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054a348
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sb(a1, a0, adxt::kHold);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054a334
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 11632);  // "E02080830 adxt_SetWaitPlayStart: parameter error"
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0054A390 sub_54A390 -- 48 bytes; frame 0x10: ra sp+0x0
// Returns the handle's started flag (+113); null reports E02080831 and gives -1.
void sub_54A390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a390
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054a3b0
        charge(ctx, 1);
        lb(v0, a0, adxt::kStarted);
    } else {
        // 0x0054a39c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11688);  // "E02080831 adxt_IsReadyPlayStart: parameter error"
        jal(ctx, 0x54A3A0u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x0054a3b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A5C8 sub_54A5C8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_541C88.
void sub_54A5C8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a5c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541C88_00541c88(ctx);  // tail call
}

// 0x0054A618 sub_54A618 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_541CA0.
void sub_54A618(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a618
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541CA0_00541ca0(ctx);  // tail call
}

// 0x0054A678 sub_54A678 -- 8 bytes; leaf frame (no stack)
// Returns the handle's streamer (+8).
void sub_54A678(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054a678
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxt::kStm);
}

// 0x0054A6B0 sub_54A6B0 -- 24 bytes; frame 0x10: ra sp+0x0
// Calls sub_5420A0 on the handle's decoder (+4).
void sub_54A6B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a6b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5420A0_005420a0(ctx);  // tail call
}

// 0x0054A710 sub_54A710 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Runs sub_54A758($a0, $a1) under the CRI lock and returns its result.
void sub_54A710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a710
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54A724u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54A730u, gen::fn_sub_54A758_0054a758);
    s0 = v0;
    jal(ctx, 0x54A738u, gen::fn_sub_539850_00539850);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0054A758 sub_54A758 -- 228 bytes; frame 0x40: s3 sp+0x28, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x30
// Pauses an ADXT handle's clock: when the pause byte (+114) is set, pauses the output (sub_541C60), runs the server,
// reads the play time with the time lock 0x793B14 forced to 0, and stores it as vsyncs (time / rate * 0x793B60, kept
// unsigned past 2^31) in +156 with the vsync count 0x787568 in +160.
void sub_54A758(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0054a758
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x30);
    lb(v1, s3, adxt::kPause);
    v0 = 0;
    if (v1 != 0) {
        // 0x0054a780
        charge(ctx, 31);
        lw(a0, s3, adxt::kRna);
        s0 = 0x790000;
        s0 = addiu(s0, 15124);  // &0x793B14
        jal(ctx, 0x54A788u, gen::fn_sub_541C60_00541c60);
        s2 = v0;
        jal(ctx, 0x54A790u, gen::fn_sub_549EA0_00549ea0);
        lw(s1, s0, 0);  // 0x793B14
        a1 = sp;
        sw(zero, s0, 0);  // 0x793B14
        a0 = s3;
        a2 = addiu(sp, 0x4);
        jal(ctx, 0x54A7A8u, gen::fn_sceInsockBind_2_00548b38);
        v0 = 0x790000;
        lwc1(f0, sp, 0x0);
        cvt_s_w(f0, f0);
        at = 0x4F000000;
        mtc1(at, f3);
        lwc1(f2, sp, 0x4);
        cvt_s_w(f2, f2);
        lwc1(f1, v0, 15200);  // 0x793B60
        cvt_s_w(f1, f1);
        sw(s1, s0, 0);  // 0x793B14
        div_s(f0, f0, f2);
        mul_s(f0, f0, f1);
        c_le_s(f3, f0);
        cvt_w_s(f1, f0);
        mfc1(a0, f1);
        v0 = s2;
        if (cond(ctx)) {
            // 0x0054a7fc
            charge(ctx, 5);
            sub_s(f0, f0, f3);
            cvt_w_s(f1, f0);
            mfc1(a0, f1);
            v1 = lui(0x8000);
            a0 = a0 | v1;
        }
        // 0x0054a810
        charge(ctx, 4);
        sw(a0, s3, adxt::kPauseTime);
        v1 = 0x780000;
        lw(a0, v1, 30056);  // 0x787568
        sw(a0, s3, adxt::kVsyncAtPause);
    }
    // 0x0054a820 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0054A878 sub_54A878 -- 8 bytes; leaf frame (no stack)
// Returns the handle's time offset (+136).
void sub_54A878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054a878
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxt::kTimeOfs);
}

// 0x0054A880 sub_54A880 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Stores $a1 as the handle's time offset under the CRI lock.
void sub_54A880(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a880
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54A894u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54A8A0u, gen::fn_sub_54A8C0_0054a8c0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054A8C0 sub_54A8C0 -- 8 bytes; leaf frame (no stack)
// Stores $a1 as the handle's time offset (+136).
void sub_54A8C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0054a8c0
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, adxt::kTimeOfs);
}

// 0x0054A910 sub_54A910 -- 24 bytes; frame 0x10: ra sp+0x0
// Calls sub_543038 on the handle's decoder (+4).
void sub_54A910(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a910
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543038_00543038(ctx);  // tail call
}

// 0x0054A9D8 sub_54A9D8 -- 8 bytes; leaf frame (no stack)
// Returns the handle's trap flag byte (+152).
void sub_54A9D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054a9d8
    enter(ctx, 2);  // entry check point + this block's cycles
    lb(v0, a0, adxt::kTrapFlag);
}

// 0x0054AA30 sub_54AA30 -- 36 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 / $a2 in the decoder's (+4) words +80 / +84; second chunk at 0x543098.
void sub_54AA30(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aa30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00543098
    charge(ctx, 3);
    sw(a2, a0, 84);
    sw(a1, a0, 80);
}

// 0x0054AA80 sub_54AA80 -- 56 bytes; frame 0x10: ra sp+0x0
// sub_542F68 on the decoder (+4); null reports E02080818 and gives -1.
void sub_54AA80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aa80
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054aaa8
        charge(ctx, 4);
        lw(a0, a0, adxt::kSjd);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_542F68_00542f68(ctx);  // tail call
        return;
    }
    // 0x0054aa8c
    charge(ctx, 7);
    a0 = 0x7C0000;
    a0 = addiu(a0, 11832);  // "E02080818 adxt_GetDecNumSmpl: parameter error"
    jal(ctx, 0x54AA90u, gen::fn_sub_53AE08_0053ae08);
    v0 = si(-1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054AAF0 sub_54AAF0 -- 56 bytes; frame 0x10: ra sp+0x0
// sub_542F60 on the decoder (+4); null reports E04041901 and gives -1.
void sub_54AAF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aaf0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054ab18
        charge(ctx, 4);
        lw(a0, a0, adxt::kSjd);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_542F60_00542f60(ctx);  // tail call
        return;
    }
    // 0x0054aafc
    charge(ctx, 7);
    a0 = 0x7C0000;
    a0 = addiu(a0, 11880);  // "E04041901 adxt_GetDecDtLen: parameter error"
    jal(ctx, 0x54AB00u, gen::fn_sub_53AE08_0053ae08);
    v0 = si(-1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054AB78 sub_54AB78 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_542F70 on the decoder (+4); null reports E04041902.
void sub_54AB78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054ab78
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054ab98
        charge(ctx, 4);
        lw(a0, a0, adxt::kSjd);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_542F70_00542f70(ctx);  // tail call
        return;
    }
    // 0x0054ab84
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 11928);  // "E04041902 ADXT_SetCbDec: parameter error"
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0054ABA8 sub_54ABA8 -- 152 bytes; frame 0x40: s0 sp+0x30, ra sp+0x38
// Reads an ADX header's sample count: a buffer ($a0, $a1 bytes) starting with the big-endian 0x8000 signature is
// parsed by sub_539AE0; on success *$a2 = the parsed s16 and 1, else 0.
void sub_54ABA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054aba8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = slti(a1, 2);
    sd(s0, sp, 0x30);
    s0 = a2;
    sd(ra, sp, 0x38);
    v0 = 0;
    a2 = a0;
    if (v1 == 0) {
        // 0x0054abc8
        charge(ctx, 8);
        lhu(v1, a2, 0);
        a3 = 0x8000;
        a2 = sll(v1, 8);
        v1 = srl(v1, 8);
        v1 = v1 | a2;
        v1 = v1 & 0xFFFF;
        if (v1 == a3) {
            // 0x0054abe8
            charge(ctx, 13);
            v0 = addiu(sp, 0x18);
            v1 = addiu(sp, 0x1C);
            a2 = addiu(sp, 0x10);
            a3 = addiu(sp, 0x12);
            t0 = addiu(sp, 0x13);
            t1 = addiu(sp, 0x14);
            t2 = addiu(sp, 0x15);
            t3 = addiu(sp, 0x20);
            sw(v0, sp, 0x0);
            link(ctx, 0x54AC0Cu);  // $ra first: the delay slot below depends on it
            sw(v1, sp, 0x8);
            call(ctx, gen::fn_sub_539AE0_00539ae0);
            lh(v1, sp, 0x10);
            if (i64(v0) >= 0) {
                // 0x0054ac28
                charge(ctx, 2);
                v0 = 1;
                sw(v1, s0, 0);
            } else {
                // 0x0054ac1c
                charge(ctx, 2);
                v0 = 0;
            }
            goto L_0054ac30;
        }
        ld(s0, sp, 0x30);
        // 0x0054ac34 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0054ac30:
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x0054ac34 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0054AC80 sub_54AC80 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Runs sub_54ACD8 under the CRI lock and returns its result.
void sub_54AC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054ac80
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x54AC9Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x54ACACu, gen::fn_sub_54ACD8_0054acd8);
    s0 = v0;
    jal(ctx, 0x54ACB4u, gen::fn_sub_539850_00539850);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0054ACD8 sub_54ACD8 -- 420 bytes; frame 0x60: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, ra sp+0x50
// Pre-fills an ADXT handle's input joint with silent ADX blocks: two passes over line 0 of the input joint (+20), each
// taking whole 18 * channels-byte frames, clearing them, stamping them through sub_563C28 and putting them back as
// data; returns the samples written (32 per frame).
void sub_54ACD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054acd8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = addiu(a2, 31);
    sd(s0, sp, 0x20);
    v0 = slti(a2, 0);
    sd(s1, sp, 0x28);
    if (v0 != 0) a2 = v1;
    sd(s2, sp, 0x30);
    v0 = a1;
    sd(s3, sp, 0x38);
    v1 = sll(v0, 3);
    sd(s4, sp, 0x40);
    v1 = addu(v1, v0);
    sd(s5, sp, 0x48);
    a2 = sra(a2, 5);
    sd(ra, sp, 0x50);
    a1 = 0;
    v0 = 0;
    s0 = sll(v1, 1);
    lw(s4, a0, adxt::kSji);
    a0 = s4;
    if (s4 != 0) {
        // 0x0054ad2c
        charge(ctx, 8);
        mult(s3, a2, s0);
        lw(v1, s4, 0);
        a3 = sp;
        lw(v0, v1, 24);
        a2 = s3;
        jalr(ctx, 0x54AD3Cu, v0.u());
        if (s0 == 0) {
            brk(ctx, 0x54AD48u, 0x7u);
        }
        // 0x0054ad4c
        charge(ctx, 36);
        lw(v0, sp, 0x4);
        a1 = 0;
        lw(a0, sp, 0x0);
        div(v0, s0);
        mflo(v0);
        mult(s5, v0, s0);
        s1 = s5;
        a2 = s1;
        jal(ctx, 0x54AD68u, gen::fn_memset_00521408);
        a1 = s1;
        s2 = addiu(sp, 0x10);
        a0 = sp;
        a2 = sp;
        a3 = s2;
        jal(ctx, 0x54AD80u, gen::fn_sub_563C28_00563c28);
        lw(v1, s4, 0);
        a2 = sp;
        a0 = s4;
        lw(v0, v1, 32);
        a1 = 1;
        jalr(ctx, 0x54AD98u, v0.u());
        lw(v1, s4, 0);
        a0 = s4;
        a1 = 0;
        lw(v0, v1, 28);
        a2 = s2;
        jalr(ctx, 0x54ADB0u, v0.u());
        lw(v1, s4, 0);
        a3 = sp;
        a2 = subu(s3, s1);
        lw(v0, v1, 24);
        a0 = s4;
        a1 = 0;
        jalr(ctx, 0x54ADCCu, v0.u());
        if (s0 == 0) {
            brk(ctx, 0x54ADD8u, 0x7u);
        }
        // 0x0054addc
        charge(ctx, 29);
        lw(v0, sp, 0x4);
        a1 = 0;
        lw(a0, sp, 0x0);
        div(v0, s0);
        mflo(v0);
        mult(s5, v0, s0);
        a2 = s5;
        s1 = addu(s1, s5);
        jal(ctx, 0x54ADF8u, gen::fn_memset_00521408);
        a1 = s5;
        a0 = sp;
        a2 = sp;
        a3 = s2;
        jal(ctx, 0x54AE0Cu, gen::fn_sub_563C28_00563c28);
        lw(v1, s4, 0);
        a2 = sp;
        a0 = s4;
        lw(v0, v1, 32);
        a1 = 1;
        jalr(ctx, 0x54AE24u, v0.u());
        lw(v1, s4, 0);
        a0 = s4;
        a2 = s2;
        lw(v0, v1, 28);
        a1 = 0;
        jalr(ctx, 0x54AE3Cu, v0.u());
        div(s1, s0);
        if (s0 == 0) {
            brk(ctx, 0x54AE4Cu, 0x7u);
        }
        // 0x0054ae50
        charge(ctx, 2);
        mflo(s1);
        v0 = sll(s1, 5);
    }
    // 0x0054ae58 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
}

// 0x0054AF38 sub_54AF38 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Runs sub_54AF78 under the CRI lock.
void sub_54AF38(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054af38
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54AF4Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54AF58u, gen::fn_sub_54AF78_0054af78);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054AF78 sub_54AF78 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_542FA8 on the decoder (+4); null reports E02080860.
void sub_54AF78(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054af78
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054af98
        charge(ctx, 4);
        lw(a0, a0, adxt::kSjd);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_542FA8_00542fa8(ctx);  // tail call
        return;
    }
    // 0x0054af84
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 11976);  // "E02080860 adxt_SetKeyString: parameter error"
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0054AFD8 sub_54AFD8 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_542FC0.
void sub_54AFD8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0054afd8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_542FC0_00542fc0(ctx);  // tail call
}

// 0x0054B028 sub_54B028 -- 8 bytes; leaf frame (no stack)
// Returns the handle's output (+12).
void sub_54B028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054b028
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, adxt::kRna);
}

// 0x0054B070 sub_54B070 -- 24 bytes; frame 0x10: ra sp+0x0
// Calls sub_543020 on the handle's decoder (+4).
void sub_54B070(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b070
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543020_00543020(ctx);  // tail call
}

// 0x0054B388 sub_54B388 -- 24 bytes; frame 0x10: ra sp+0x0
// Calls sub_54B3F0($a0, $a1, 0x40000000).
void sub_54B388(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b388
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x40000000;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54B3F0_0054b3f0(ctx);  // tail call
}

// 0x0054C580 sub_54C580 -- 236 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Restarts an ADXT handle from its input: under the CRI lock the output's transfer and play switches off (cosl_1 /
// coshl_1 on +12) and the decoder stopped (sub_542100); with a streamer (+8) it is stopped (sub_546638) and the input
// joint (+20) reset through its interface (+20); then, locked again, every output joint (+24.., +3 of them) reset, the
// streamer re-armed (sub_5463A8(stm, 0), sub_546498) and the common start sub_548318(handle, input joint).
void sub_54C580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054c580
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s1 = a0;
    jal(ctx, 0x54C594u, gen::fn_sub_539818_00539818);
    lw(a0, s1, adxt::kRna);
    a1 = 0;
    jal(ctx, 0x54C5A0u, gen::fn_cosl_1_00541a78);
    lw(a0, s1, adxt::kRna);
    a1 = 0;
    jal(ctx, 0x54C5ACu, gen::fn_coshl_1_00541a90);
    link(ctx, 0x54C5B4u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, adxt::kSjd);
    call(ctx, gen::fn_sub_542100_00542100);
    jal(ctx, 0x54C5BCu, gen::fn_sub_539830_00539830);
    lw(a0, s1, adxt::kStm);
    if (a0 != 0) {
        // 0x0054c5d0
        charge(ctx, 7);
        jal(ctx, 0x54C5D0u, gen::fn_sub_546638_00546638);
        lw(a0, s1, adxt::kSji);
        lw(v1, a0, 0);
        lw(v0, v1, 20);
        jalr(ctx, 0x54C5E4u, v0.u());
    }
    // 0x0054c5ec
    charge(ctx, 5);
    s2 = 0;
    jal(ctx, 0x54C5ECu, gen::fn_sub_539818_00539818);
    lb(v0, s1, adxt::kMaxCh);
    if (i64(v0) <= 0) {
        lw(a0, s1, adxt::kStm);
    } else {
        // 0x0054c600
        charge(ctx, 2);
        s0 = addiu(s1, 24);
        lw(a0, s0, 0);
        for (;;) {
            // 0x0054c608
            charge(ctx, 9);
            s0 = addiu(s0, 4);
            lw(v0, a0, 0);
            lw(v1, v0, 20);
            s2 = addiu(s2, 1);
            jalr(ctx, 0x54C614u, v1.u());
            lb(v0, s1, adxt::kMaxCh);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
        // 0x0054c62c
        charge(ctx, 1);
        lw(a0, s1, adxt::kStm);
    }
    // 0x0054c630
    charge(ctx, 2);
    if (a0 == 0) {
        a0 = s1;
    } else {
        // 0x0054c638
        charge(ctx, 5);
        a1 = 0;
        jal(ctx, 0x54C638u, gen::fn_sub_5463A8_005463a8);
        link(ctx, 0x54C640u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, adxt::kStm);
        call(ctx, gen::fn_sub_546498_00546498);
        a0 = s1;
    }
    // 0x0054c64c
    charge(ctx, 8);
    link(ctx, 0x54C64Cu);  // $ra first: the delay slot below depends on it
    lw(a1, a0, 20);
    call(ctx, gen::fn_sub_548318_00548318);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x0054CB08 sub_54CB08 -- 108 bytes; frame 0x10: ra sp+0x0
// The streamer of an ADXT handle (+8, else the list streamer's +40 via +148) passed to sub_547558; 0 when none.
void sub_54CB08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054cb08
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(ra, sp, 0x0);
    v0 = 0;
    if (v1 == 0) {
        // 0x0054cb68 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054cb1c
    charge(ctx, 3);
    lw(v0, v1, adxt::kStm);
    a0 = v0;
    if (v0 != 0) {
        // 0x0054cb58
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_547558_00547558(ctx);  // tail call
        return;
    }
    // 0x0054cb28
    charge(ctx, 3);
    lw(a0, v1, adxt::kLsc);
    v0 = 0;
    if (a0 == 0) {
        // 0x0054cb68 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054cb34
    charge(ctx, 3);
    lw(v0, a0, 40);
    a0 = v0;
    if (v0 != 0) {
        // 0x0054cb40
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_547558_00547558(ctx);  // tail call
        return;
    }
    // 0x0054cb50
    charge(ctx, 2);
    v0 = 0;
    // 0x0054cb68 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054D88C sub_54D88C -- 8 bytes; leaf frame (no stack)
// Returns $a1.
void sub_54D88C(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x0054d88c
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a1;
}

// 0x0054DAD8 sub_54DAD8 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MPEG audio: counts the call (0x796F54) and refills the bit reader (sub_54D898) when its fill (+12) is below $a1;
// returns whether it then holds $a1.
void sub_54DAD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054dad8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 28500);  // &0x796F54
    lw(a2, s1, 12);
    lw(v1, v0, 0);  // 0x796F54
    a1 = slt(a2, s0);
    v1 = addiu(v1, 1);
    sw(v1, v0, 0);  // 0x796F54
    if (a1 != 0) {
        // 0x0054db10
        charge(ctx, 3);
        jal(ctx, 0x54DB10u, gen::fn_sub_54D898_0054d898);
        lw(a2, s1, 12);
    }
    // 0x0054db1c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = slt(a2, s0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054DD08 sub_54DD08 -- 192 bytes; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, s4 sp+0x20, ra sp+0x28
// MPEG audio: seeks the next frame sync -- byte-aligns the bit reader, then shifts in 4 bits at a time until the
// 12-bit 0xFFF sync (masked by 0x796F88) gives 1 or the 0x8001000C marker gives 2; -1 at the end of data.
void sub_54DD08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054dd08
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x790000;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    link(ctx, 0x54DD2Cu);  // $ra first: the delay slot below depends on it
    lw(s3, v0, 28552);
    call(ctx, gen::fn_sub_54DBE8_0054dbe8);
    v0 = v0 & 0x7;
    a1 = 8;
    if (v0 != 0) {
        // 0x0054dd40
        charge(ctx, 3);
        a0 = s1;
        a1 = subu(a1, v0);
        jal(ctx, 0x54DD44u, gen::fn_sub_54DB38_0054db38);
    }
    // 0x0054dd4c
    charge(ctx, 8);
    a0 = s1;
    s2 = lui(0x8001);
    a1 = 12;
    jal(ctx, 0x54DD54u, gen::fn_sub_54DB38_0054db38);
    s0 = v0;
    s4 = 4095;
    s2 = s2 | 0xC;
    for (;;) {
        // 0x0054dd8c
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x54DD8Cu, gen::fn_sub_54DBF0_0054dbf0);
        a0 = s1;
        a1 = 4;
        v1 = s0 & s3;
        if (v0 != 0) {
            goto L_0054dda4_7;
        }
        backedge(ctx);
        // 0x0054dd70
        charge(ctx, 2);
        v0 = 1;
        if (v1 != s4) {
            // 0x0054dd78
            charge(ctx, 2);
            v0 = 2;
            if (s0 != s2) {
                // 0x0054dd80
                charge(ctx, 3);
                s0 = sll(s0, 4);
                jal(ctx, 0x54DD80u, gen::fn_sub_54DB38_0054db38);
                s0 = s0 | v0;
                continue;
            }
        }
        break;
    }
    // 0x0054dda8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0054dda4_7:
    charge(ctx, 1);
    v0 = si(-1);
    // 0x0054dda8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0054E048 sub_54E048 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Hashes the stream key: on first use initialises the table (sub_54DE50), then sub_54DE90("CRI-MW", 6, $a0, $a1, $a2);
// returns 0.
void sub_54E048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e048
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 29600);  // 0x7973A0
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (v1 == 0) {
        // 0x0054e074
        charge(ctx, 2);
        jal(ctx, 0x54E074u, gen::fn_sub_54DE50_0054de50);
    }
    // 0x0054e07c
    charge(ctx, 14);
    a0 = 0x7C0000;
    a2 = s0;
    a3 = s1;
    t0 = s2;
    a0 = addiu(a0, 12600);  // "CRI-MW"
    a1 = 6;
    jal(ctx, 0x54E090u, gen::fn_sub_54DE90_0054de90);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0054E0D8 sub_54E0D8 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The MPEG-audio decoder's init: the first call runs sub_551990 and clears the 16-entry handle table 0x797598; returns
// the incremented use count 0x797568.
void sub_54E0D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e0d8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x790000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 30056);  // &0x797568
    lw(v0, s0, 0);  // 0x797568
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x0054e0f4
        charge(ctx, 8);
        jal(ctx, 0x54E0F4u, gen::fn_sub_551990_00551990);
        a0 = 0x790000;
        a0 = addiu(a0, 30104);  // &0x797598
        a1 = 0;
        a2 = 64;
        jal(ctx, 0x54E108u, gen::fn_memset_00521408);
        lw(v0, s0, 0);
    }
    // 0x0054e114 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = addiu(v0, 1);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054E130 sub_54E130 -- 76 bytes; frame 0x10: ra sp+0x0
// The MPEG-audio decoder's finish: the last call clears the handle table and runs sub_551A88.
void sub_54E130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e130
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x790000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 30056);  // &0x797568
    lw(v0, v1, 0);  // 0x797568
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x797568
    if (v0 != 0) {
        // 0x0054e170
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054e150
    charge(ctx, 8);
    a0 = 0x790000;
    a1 = 0;
    a0 = addiu(a0, 30104);  // &0x797598
    a2 = 64;
    jal(ctx, 0x54E15Cu, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_551A88_00551a88(ctx);  // tail call
}

// 0x0054E180 sub_54E180 -- 224 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// The MPEG-audio decoder's create: takes a free slot of the 16-entry table, clears the caller's work area ($a0, $a1
// bytes), records its slot (+422), creates the synthesis work (sub_551AD8 at +2600, 4116 bytes; +432), aligns the
// sample buffer (+0) to 32 bytes and marks it ready (+420).
void sub_54E180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e180
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = 0x790000;
    sd(ra, sp, 0x18);
    v1 = addiu(s2, 30104);  // &0x797598
    lw(v0, v1, 0);  // 0x797598
    s1 = 0;
    if (v0 != 0) {
        // 0x0054e1ac
        charge(ctx, 1);
        s1 = addiu(s1, 1);
        for (;;) {
            // 0x0054e1b0
            charge(ctx, 3);
            v0 = slti(s1, 16);
            v1 = addiu(v1, 4);
            if (v0 != 0) {
                // 0x0054e1bc
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
    // 0x0054e1d4
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (s1 != v1) {
        // 0x0054e1e0
        charge(ctx, 15);
        a2 = a1;
        a1 = 0;
        a0 = s0;
        jal(ctx, 0x54E1E8u, gen::fn_memset_00521408);
        v1 = addiu(s2, 30104);
        v0 = sll(s1, 2);
        a0 = addiu(s0, 2600);
        v0 = addu(v0, v1);
        a1 = 4116;
        sw(s0, v0, 0);
        link(ctx, 0x54E208u);  // $ra first: the delay slot below depends on it
        sb(s1, s0, mpa::kSlot);
        call(ctx, gen::fn_sub_551AD8_00551ad8);
        v1 = v0;
        sw(v1, s0, mpa::kSynth);
        if (v1 != 0) {
            // 0x0054e21c
            charge(ctx, 11);
            v0 = addiu(s0, 35);
            v1 = si(-32);
            v0 = v0 & v1;
            sw(v0, s0, mpa::kSamples);
            a0 = addiu(s0, 484);
            a1 = 0;
            a2 = 8;
            jal(ctx, 0x54E234u, gen::fn_memset_00521408);
            v1 = 1;
            sb(v1, s0, mpa::kReady);
            v0 = s0;
        }
    }
    // 0x0054e248 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0054E260 sub_54E260 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// The MPEG-audio decoder's destroy: releases the synthesis work (+432), clears the 2600-byte handle and frees its
// table slot.
void sub_54E260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e260
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lw(v0, s0, mpa::kSynth);
    lb(s1, s0, mpa::kSlot);
    a0 = v0;
    if (v0 != 0) {
        // 0x0054e284
        charge(ctx, 2);
        link(ctx, 0x54E284u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, mpa::kSynth);
        call(ctx, gen::fn_sub_551BB0_00551bb0);
    }
    // 0x0054e28c
    charge(ctx, 13);
    a0 = s0;
    a1 = 0;
    a2 = 2600;
    jal(ctx, 0x54E294u, gen::fn_memset_00521408);
    v1 = sll(s1, 2);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    at = 0x790000;
    at = addu(at, v1);
    sw(zero, at, 30104);
    sp = addiu(sp, 0x20);
}

// 0x0054E388 sub_54E388 -- 52 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Calls sub_54E2C0 and stores $a1 as the decoder's bit reader (+428).
void sub_54E388(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e388
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54E39Cu, gen::fn_sub_54E2C0_0054e2c0);
    ld(ra, sp, 0x10);
    sw(s1, s0, mpa::kBitRd);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0054E3C0 sub_54E3C0 -- 424 bytes; frame 0x90: s1 sp+0x58, s4 sp+0x70, s0 sp+0x50, s2 sp+0x60, s3 sp+0x68, s5 sp+0x78, ra sp+0x80
// Reads the decoder's in-stream CRI header: copies bytes from the bit reader into 0x997108.. while sub_53E520 parses
// it (4 bytes, then the full length), then fills the decoder's info block (+484..+536) and its key (+536: cleared,
// copied from +2592, or hashed by sub_54E048).
void sub_54E3C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e3c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s1, sp, 0x58);
    sd(s4, sp, 0x70);
    s4 = a0;
    sd(s0, sp, 0x50);
    sd(s2, sp, 0x60);
    sd(s3, sp, 0x68);
    sd(s5, sp, 0x78);
    sd(ra, sp, 0x80);
    lw(s3, s4, 428);
    s1 = addiu(s4, 484);
    if (s3 != 0) {
        // 0x0054e3f0
        charge(ctx, 9);
        s5 = 0x990000;
        a0 = sp;
        a1 = 0;
        a2 = 64;
        s0 = addiu(s5, 28936);  // &0x997108
        jal(ctx, 0x54E400u, gen::fn_memset_00521408);
        s2 = addiu(s0, 4);  // &0x99710C
        sw(zero, sp, 0x40);
        if (s0 != s2) {
            // 0x0054e414
            charge(ctx, 1);
            a0 = s3;
            for (;;) {
                // 0x0054e418
                charge(ctx, 6);
                a1 = 8;
                jal(ctx, 0x54E418u, gen::fn_sub_54DB38_0054db38);
                sb(v0, s0, 0);
                s0 = addiu(s0, 1);
                a0 = s3;
                if (s0 == s2) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0054e430
        charge(ctx, 9);
        a0 = addiu(s5, 28936);
        a1 = 4;
        a2 = addiu(sp, 0x40);
        a3 = 0;
        jal(ctx, 0x54E43Cu, gen::fn_sub_53E520_0053e520);
        lw(v1, sp, 0x40);
        s2 = addu(s2, v1);
        a0 = addiu(s5, 28936);
        if (s0 != s2) {
            // 0x0054e454
            charge(ctx, 1);
            a0 = s3;
            for (;;) {
                // 0x0054e458
                charge(ctx, 6);
                a1 = 8;
                jal(ctx, 0x54E458u, gen::fn_sub_54DB38_0054db38);
                sb(v0, s0, 0);
                s0 = addiu(s0, 1);
                a0 = s3;
                if (s0 == s2) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0054e470
            charge(ctx, 1);
            a0 = addiu(s5, 28936);
        }
        // 0x0054e474
        charge(ctx, 6);
        a1 = 512;
        a2 = addiu(sp, 0x40);
        a3 = sp;
        jal(ctx, 0x54E47Cu, gen::fn_sub_53E520_0053e520);
        lb(a3, sp, 0x3D);
        if (i64(v0) < 0) {
            goto L_0054e544;
        }
        // 0x0054e48c
        charge(ctx, 26);
        a2 = 1;
        lb(v1, sp, 0x3);
        lw(a0, sp, 0x4);
        a1 = slti(a3, 16);
        lw(v0, sp, 0x8);
        ldl(t0, sp, 0x2B);
        ldr(t0, sp, 0x24);
        lwl(t1, sp, 0x2F);
        lwr(t1, sp, 0x2C);
        sdl(t0, s1, 35);
        sdr(t0, s1, 28);
        swl(t1, s1, 39);
        swr(t1, s1, 36);
        sw(v1, s1, 4);
        ldl(t0, sp, 0x37);
        ldr(t0, sp, 0x30);
        lwl(t1, sp, 0x3B);
        lwr(t1, sp, 0x38);
        sdl(t0, s1, 47);
        sdr(t0, s1, 40);
        swl(t1, s1, 51);
        swr(t1, s1, 48);
        sw(a0, s1, 8);
        sw(v0, s1, 12);
        sw(a2, s1, 0);
        if (a1 != 0) {
            // 0x0054e510
            charge(ctx, 3);
            v0 = slti(a3, 8);
            a0 = addiu(s1, 52);
            if (v0 != 0) {
                // 0x0054e538
                charge(ctx, 3);
                a1 = 0;
                a2 = 8;
                jal(ctx, 0x54E53Cu, gen::fn_memset_00521408);
                goto L_0054e544;
            }
            // 0x0054e51c
            charge(ctx, 6);
            ldl(v0, s4, 2599);
            ldr(v0, s4, 2592);
            sdl(v0, s1, 59);
            sdr(v0, s1, 52);
            ld(s0, sp, 0x50);
        } else {
            // 0x0054e4f4
            charge(ctx, 7);
            sh(zero, s1, 52);
            a2 = addiu(s1, 58);
            a0 = addiu(s1, 54);
            a1 = addiu(s1, 56);
            jal(ctx, 0x54E500u, gen::fn_sub_54E048_0054e048);
            ld(s0, sp, 0x50);
        }
        // 0x0054e548 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x58);
        ld(s2, sp, 0x60);
        ld(s3, sp, 0x68);
        ld(s4, sp, 0x70);
        ld(s5, sp, 0x78);
        ld(ra, sp, 0x80);
        sp = addiu(sp, 0x90);
        return;
    }
L_0054e544:
    charge(ctx, 1);
    ld(s0, sp, 0x50);
    // 0x0054e548 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(ra, sp, 0x80);
    sp = addiu(sp, 0x90);
}

// 0x0054E648 sub_54E648 -- 16 bytes; leaf frame (no stack)
// Whether the decoder has produced all 12 granules (+424 == 12).
void sub_54E648(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0054e648
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, mpa::kGranule);
    v0 = v0 ^ 0xC;
    v0 = sltiu(v0, 1);
}

// 0x0054E658 sub_54E658 -- 324 bytes; frame 0x40: s1 sp+0x8, s3 sp+0x18, s5 sp+0x28, s0 sp+0x0, s2 sp+0x10, s4 sp+0x20, s6 sp+0x30, ra sp+0x38
// Decodes one MPEG-audio granule group: dequantises (sub_54F028), then synthesises 3 x 32 samples for the left channel
// and, in stereo, the right (sub_551BF0), timing each stage with sub_551978 into 0x7975D8..0x7975EC; returns 96, or 0
// when all 12 granules are done.
void sub_54E658(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e658
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s5, sp, 0x28);
    s5 = a2;
    sd(s0, sp, 0x0);
    a0 = 12;
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(v1, s1, mpa::kGranule);
    lw(s6, s1, mpa::kInfoNch);
    if (v1 != a0) {
        // 0x0054e69c
        charge(ctx, 17);
        s4 = 0x790000;
        jal(ctx, 0x54E69Cu, gen::fn_sub_551978_00551978);
        s0 = addiu(s4, 30168);  // &0x7975D8
        lw(a0, s1, mpa::kBitRd);
        sw(v0, s0, 0);  // 0x7975D8
        a1 = addiu(s1, 484);
        lw(t1, s1, mpa::kSamples);
        a2 = addiu(s1, 544);
        lw(t0, s1, mpa::kGranule);
        a3 = addiu(s1, 1056);
        s2 = 0;
        t0 = sra(t0, 2);
        jal(ctx, 0x54E6C8u, gen::fn_sub_54F028_0054f028);
        jal(ctx, 0x54E6D0u, gen::fn_sub_551978_00551978);
        sw(v0, s0, 12);  // 0x7975E4
        lw(a1, s1, mpa::kSamples);
        for (;;) {
            // 0x0054e6e0
            charge(ctx, 10);
            v0 = sll(s2, 6);
            lw(a0, s1, mpa::kSynth);
            a3 = addu(s3, v0);
            a1 = addu(a1, v0);
            a2 = 0;
            s2 = addiu(s2, 1);
            jal(ctx, 0x54E6F4u, gen::fn_sub_551BF0_00551bf0);
            v0 = slti(s2, 3);
            if (v0 == 0) {
                break;
            }
            lw(a1, s1, mpa::kSamples);
            backedge(ctx);
        }
        // 0x0054e708
        charge(ctx, 6);
        jal(ctx, 0x54E708u, gen::fn_sub_551978_00551978);
        v1 = addiu(s4, 30168);
        a0 = slti(s6, 2);
        sw(v0, v1, 16);
        if (a0 == 0) {
            // 0x0054e720
            charge(ctx, 2);
            s2 = 0;
            lw(a1, s1, mpa::kSamples);
            for (;;) {
                // 0x0054e728
                charge(ctx, 11);
                v0 = sll(s2, 6);
                lw(a0, s1, mpa::kSynth);
                a3 = addu(s5, v0);
                a1 = addu(a1, v0);
                a2 = 1;
                a1 = addiu(a1, 192);
                s2 = addiu(s2, 1);
                jal(ctx, 0x54E740u, gen::fn_sub_551BF0_00551bf0);
                v0 = slti(s2, 3);
                if (v0 == 0) {
                    break;
                }
                lw(a1, s1, mpa::kSamples);
                backedge(ctx);
            }
        }
        // 0x0054e754
        charge(ctx, 8);
        jal(ctx, 0x54E754u, gen::fn_sub_551978_00551978);
        v1 = addiu(s4, 30168);
        sw(v0, v1, 20);
        v0 = 96;
        lw(v1, s1, mpa::kGranule);
        v1 = addiu(v1, 1);
        sw(v1, s1, mpa::kGranule);
    }
    // 0x0054e774 (the shared epilogue, written out on this path)
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

// 0x0054E838 sub_54E838 -- 80 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Sets the decoder's key from a string: sub_54DE90(the string, its length, +2594, +2596, +2598) and clears +2592.
void sub_54E838(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e838
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x54E850u, gen::fn_strlen_00524388);
    a0 = s1;
    a2 = addiu(s0, 2594);
    a3 = addiu(s0, 2596);
    t0 = addiu(s0, 2598);
    a1 = v0;
    jal(ctx, 0x54E868u, gen::fn_sub_54DE90_0054de90);
    sh(zero, s0, mpa::kKey);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054E9A0 sub_54E9A0 -- 276 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Parses an MPEG-audio frame header from the bit reader into $a1[0..11] (id, layer as 4 - code, CRC present, bitrate
// index, rate index, padding, private, mode, mode extension, copyright, original, emphasis); returns -1 unless the
// mode is 3 with extension 0 (mono), else 0.
void sub_54E9A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054e9a0
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x54E9B8u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 0);
    a1 = 2;
    jal(ctx, 0x54E9C8u, gen::fn_sub_54DB38_0054db38);
    v1 = 4;
    v1 = subu(v1, v0);
    a0 = s0;
    sw(v1, s1, 4);
    a1 = 1;
    jal(ctx, 0x54E9E0u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    v0 = sltiu(v0, 1);
    a1 = 4;
    link(ctx, 0x54E9F4u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 8);
    call(ctx, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 12);
    a1 = 2;
    jal(ctx, 0x54EA04u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 16);
    a1 = 1;
    jal(ctx, 0x54EA14u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 20);
    a1 = 1;
    jal(ctx, 0x54EA24u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 24);
    a1 = 2;
    jal(ctx, 0x54EA34u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 28);
    a1 = 2;
    jal(ctx, 0x54EA44u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 32);
    a1 = 1;
    jal(ctx, 0x54EA54u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 36);
    a1 = 1;
    jal(ctx, 0x54EA64u, gen::fn_sub_54DB38_0054db38);
    a0 = s0;
    sw(v0, s1, 40);
    a1 = 2;
    jal(ctx, 0x54EA74u, gen::fn_sub_54DB38_0054db38);
    lw(a0, s1, 28);
    v1 = 3;
    sw(v0, s1, 44);
    v0 = 0;
    if (a0 == v1) {
        // 0x0054ea90
        charge(ctx, 3);
        lw(v1, s1, 32);
        ld(s0, sp, 0x0);
        if (v1 != 0) {
            goto L_0054ea9c;
        }
        // 0x0054eaa4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0054ea9c:
    charge(ctx, 2);
    v0 = si(-1);
    ld(s0, sp, 0x0);
    // 0x0054eaa4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054EAB8 sub_54EAB8 -- 76 bytes, 2 chunks; frame 0x10: ra sp+0x0
// The Layer II allocation table: *$a2 = the table 0x793F50, returns its sub-band count 0x793F48; second chunk at
// 0x54DDC8.
void sub_54EAB8(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054eab8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a2;
    sd(ra, sp, 0x0);
    a0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0054ddc8
    charge(ctx, 12);
    v1 = sll(a0, 1);
    a2 = sll(a0, 2);
    v1 = addu(v1, a0);
    v0 = 0x790000;
    v0 = addu(v0, a2);
    lw(v0, v0, 16200);
    v1 = sll(v1, 12);
    at = 0x790000;
    at = addiu(at, 16208);  // &0x793F50
    v1 = addu(at, v1);
    sw(v1, a1, 0);
}

// 0x0054EAD8 sub_54EAD8 -- 228 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Fills the frame's decode parameters: channels (1 for mode 3, else 2), the sub-band limit and the allocation table
// (sub_54EAB8 for Layer II, else 32), the joint-stereo bound (0x797538) and the frame size (0x7973B0).
void sub_54EAD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054ead8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    lw(a0, s0, 0);
    if (a0 != 0) {
        lw(v1, s1, 4);
    } else {
        // 0x0054eafc
        charge(ctx, 4);
        lw(v1, s1, 28);
        v0 = 3;
        if (v1 != v0) {
            v0 = 2;
        } else {
            // 0x0054eb0c
            charge(ctx, 1);
            v0 = 1;
        }
        // 0x0054eb10
        charge(ctx, 2);
        sw(v0, s0, 4);
        lw(v1, s1, 4);
    }
    // 0x0054eb18
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        v0 = 32;
    } else {
        // 0x0054eb24
        charge(ctx, 5);
        lw(a1, s0, 4);
        a0 = s1;
        a2 = addiu(s0, 24);
        jal(ctx, 0x54EB2Cu, gen::fn_sub_54EAB8_0054eab8);
        lw(a0, s0, 0);
    }
    // 0x0054eb38
    charge(ctx, 5);
    sw(v0, s0, 16);
    lw(v1, s1, 28);
    v0 = 1;
    if (v1 != v0) {
        lw(v0, s0, 16);
        // 0x0054eb78
        charge(ctx, 1);
        sw(v0, s0, 20);
    } else {
        // 0x0054eb4c
        charge(ctx, 10);
        lw(v0, s1, 4);
        lw(v1, s1, 32);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v1 = 0x790000;
        v1 = addu(v1, v0);
        lw(v1, v1, 30008);
        sw(v1, s0, 20);
    }
    // 0x0054eb7c
    charge(ctx, 2);
    if (a0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0054eb84
        charge(ctx, 10);
        lw(v0, s1, 0);
        lw(v1, s1, 16);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v1 = 0x790000;
        v1 = addu(v1, v0);
        lw(v1, v1, 29616);
        sw(v1, s0, 8);
        ld(s0, sp, 0x0);
    }
    // 0x0054ebac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054EBC0 sub_54EBC0 -- 388 bytes; frame 0x60: s2 sp+0x20, s7 sp+0x48, fp sp+0x50, s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, ra sp+0x58
// Reads the Layer II bit allocation: per sub-band below the bound one code per channel, joint sub-bands one code
// shared, the rest 0 (32 sub-bands, 128-byte channel stride).
void sub_54EBC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0054ebc0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s7, sp, 0x48);
    s7 = a0;
    sd(fp, sp, 0x50);
    fp = a2;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    sd(ra, sp, 0x58);
    lw(v0, a1, 24);
    lw(s6, a1, 20);
    sw(v0, sp, 0x4);
    lw(v1, a1, 16);
    sw(v1, sp, 0x0);
    lw(s5, a1, 4);
    if (i64(s6) > 0) {
        // 0x0054ec14
        charge(ctx, 1);
        s4 = v0;
        for (;;) {
            // 0x0054ec18
            charge(ctx, 2);
            if (i64(s5) <= 0) {
                s2 = addiu(s2, 1);
            } else {
                // 0x0054ec20
                charge(ctx, 4);
                v0 = sll(s2, 2);
                s3 = s4;
                s1 = addu(v0, fp);
                s0 = s5;
                for (;;) {
                    // 0x0054ec30
                    charge(ctx, 7);
                    lw(a1, s3, 4);
                    a0 = s7;
                    s0 = addiu(s0, -1);
                    jal(ctx, 0x54EC38u, gen::fn_sub_54DB38_0054db38);
                    sw(v0, s1, 0);
                    s1 = addiu(s1, 128);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0054ec4c
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0054ec50
            charge(ctx, 3);
            v0 = slt(s2, s6);
            s4 = addiu(s4, 384);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054ec5c
    charge(ctx, 5);
    lw(a0, sp, 0x0);
    s2 = s6;
    v0 = slt(s2, a0);
    if (v0 == 0) {
        lw(s2, sp, 0x0);
    } else {
        // 0x0054ec70
        charge(ctx, 10);
        v1 = sll(s2, 2);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        s2 = subu(a0, s2);
        s0 = addu(v1, fp);
        lw(v1, sp, 0x4);
        v0 = sll(v0, 7);
        v0 = addu(v0, v1);
        s1 = addiu(v0, 4);
        for (;;) {
            // 0x0054ec98
            charge(ctx, 9);
            lw(a1, s1, 0);
            s1 = addiu(s1, 384);
            a0 = s7;
            s2 = addiu(s2, -1);
            jal(ctx, 0x54ECA4u, gen::fn_sub_54DB38_0054db38);
            sw(v0, s0, 0);
            sw(v0, s0, 128);
            s0 = addiu(s0, 4);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054ecbc
        charge(ctx, 1);
        lw(s2, sp, 0x0);
    }
    // 0x0054ecc0
    charge(ctx, 3);
    v0 = slti(s2, 32);
    if (v0 == 0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x0054eccc
        charge(ctx, 1);
        for (;;) {
            // 0x0054ecd0
            charge(ctx, 2);
            if (i64(s5) <= 0) {
                s2 = addiu(s2, 1);
            } else {
                // 0x0054ecd8
                charge(ctx, 4);
                v0 = sll(s2, 2);
                s0 = s5;
                v0 = addu(v0, fp);
                for (;;) {
                    // 0x0054ece8
                    charge(ctx, 7);
                    s0 = addiu(s0, -1);
                    sw(zero, v0, 0);
                    v0 = addiu(v0, 128);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0054ed04
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0054ed08
            charge(ctx, 3);
            v0 = slti(s2, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054ed14
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0054ed18 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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

// 0x0054ED48 sub_54ED48 -- 732 bytes; frame 0x60: s0 sp+0x10, s2 sp+0x20, s6 sp+0x40, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, s7 sp+0x48, fp sp+0x50, ra sp+0x58
// Reads the scale-factor selection and the scale factors of every allocated sub-band.
void sub_54ED48(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054ed48
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    lw(v0, a2, 0);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s6, sp, 0x40);
    s6 = a3;
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(s7, sp, 0x48);
    sd(fp, sp, 0x50);
    sd(ra, sp, 0x58);
    sw(a2, sp, 0x0);
    sw(t0, sp, 0x4);
    lw(fp, s0, 16);
    lw(s5, s0, 4);
    if (v0 == 0) {
        // 0x0054eda8
        charge(ctx, 1);
        sw(zero, s6, 0);
    } else {
        // 0x0054ed98
        charge(ctx, 4);
        a1 = 2;
        jal(ctx, 0x54ED98u, gen::fn_sub_54DB38_0054db38);
        sw(v0, s6, 0);
    }
    // 0x0054edac
    charge(ctx, 7);
    lw(v0, s6, 0);
    s3 = 1;
    v1 = slt(s3, fp);
    v0 = sll(v0, 1);
    v0 = addu(v0, s0);
    lh(s1, v0, 52);
    if (v1 != 0) {
        for (;;) {
            // 0x0054edc8
            charge(ctx, 6);
            lw(v1, sp, 0x0);
            s0 = sll(s3, 2);
            v0 = addu(s0, v1);
            lw(v1, v0, 0);
            s3 = addiu(s3, 1);
            if (v1 != 0) {
                // 0x0054ede0
                charge(ctx, 7);
                a0 = s2;
                a1 = 2;
                jal(ctx, 0x54EDE4u, gen::fn_sub_54DB38_0054db38);
                v1 = addu(s0, s6);
                a0 = s1 & 0x3;
                v0 = v0 ^ a0;
                sw(v0, v1, 0);
            }
            // 0x0054edfc
            charge(ctx, 3);
            v0 = slt(s3, fp);
            s1 = sra(s1, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054ee08
    charge(ctx, 4);
    s3 = fp;
    v0 = slti(s3, 32);
    if (v0 != 0) {
        for (;;) {
            // 0x0054ee18
            charge(ctx, 2);
            if (i64(s5) <= 0) {
                s3 = addiu(s3, 1);
            } else {
                // 0x0054ee20
                charge(ctx, 4);
                v0 = sll(s3, 2);
                s1 = s5;
                v0 = addu(v0, s6);
                for (;;) {
                    // 0x0054ee30
                    charge(ctx, 7);
                    s1 = addiu(s1, -1);
                    sw(zero, v0, 0);
                    v0 = addiu(v0, 128);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0054ee4c
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x0054ee50
            charge(ctx, 3);
            v0 = slti(s3, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054ee5c
    charge(ctx, 2);
    s3 = 0;
    if (i64(fp) > 0) {
        // 0x0054ee64
        charge(ctx, 1);
        for (;;) {
            // 0x0054ee68
            charge(ctx, 2);
            if (i64(s5) <= 0) {
                s3 = addiu(s3, 1);
            } else {
                // 0x0054ee70
                charge(ctx, 6);
                lw(a0, sp, 0x4);
                v0 = sll(s3, 2);
                s7 = 63;
                s4 = v0;
                s0 = addu(v0, a0);
                s1 = s5;
                for (;;) {
                    // 0x0054ee88
                    charge(ctx, 5);
                    lw(v1, sp, 0x0);
                    v0 = addu(s4, v1);
                    lw(v1, v0, 0);
                    v0 = addu(s4, s6);
                    if (v1 == 0) {
                        // 0x0054ef68
                        charge(ctx, 3);
                        sw(s7, s0, 256);
                        sw(s7, s0, 128);
                        sw(s7, s0, 0);
                    L_0054ef74:
                        charge(ctx, 1);
                        s1 = addiu(s1, -1);
                    } else {
                        // 0x0054ee9c
                        charge(ctx, 4);
                        v1 = 1;
                        lw(a0, v0, 0);
                        if (a0 == v1) {
                            a0 = s2;
                            // 0x0054eef8
                            charge(ctx, 6);
                            a1 = 6;
                            jal(ctx, 0x54EEF8u, gen::fn_sub_54DB38_0054db38);
                            a0 = s2;
                            sw(v0, s0, 0);
                            a1 = 6;
                            sw(v0, s0, 128);
                        L_0054ef10:
                            charge(ctx, 4);
                            s1 = addiu(s1, -1);
                            jal(ctx, 0x54EF10u, gen::fn_sub_54DB38_0054db38);
                            sw(v0, s0, 256);
                        } else {
                            // 0x0054eeac
                            charge(ctx, 2);
                            if (a0 == 0) {
                                a0 = s2;
                                // 0x0054eed0
                                charge(ctx, 10);
                                a1 = 6;
                                jal(ctx, 0x54EED0u, gen::fn_sub_54DB38_0054db38);
                                a0 = s2;
                                sw(v0, s0, 0);
                                a1 = 6;
                                jal(ctx, 0x54EEE0u, gen::fn_sub_54DB38_0054db38);
                                a0 = s2;
                                sw(v0, s0, 128);
                                a1 = 6;
                                goto L_0054ef10;
                            }
                            // 0x0054eeb4
                            charge(ctx, 3);
                            v0 = 2;
                            cc = a0 == v0;  // the condition, before the delay slot changes it
                            v0 = 3;
                            if (cc) {
                                // 0x0054ef48
                                charge(ctx, 7);
                                a0 = s2;
                                a1 = 6;
                                jal(ctx, 0x54EF4Cu, gen::fn_sub_54DB38_0054db38);
                                sw(v0, s0, 0);
                                sw(v0, s0, 256);
                                sw(v0, s0, 128);
                                goto L_0054ef74;
                            }
                            // 0x0054eec0
                            charge(ctx, 2);
                            cc = a0 == v0;  // the condition, before the delay slot changes it
                            a0 = s2;
                            if (cc) {
                                // 0x0054ef20
                                charge(ctx, 9);
                                a1 = 6;
                                jal(ctx, 0x54EF20u, gen::fn_sub_54DB38_0054db38);
                                a0 = s2;
                                sw(v0, s0, 0);
                                a1 = 6;
                                jal(ctx, 0x54EF30u, gen::fn_sub_54DB38_0054db38);
                                sw(v0, s0, 128);
                                sw(v0, s0, 256);
                                goto L_0054ef74;
                            }
                            // 0x0054eec8
                            charge(ctx, 2);
                            s1 = addiu(s1, -1);
                        }
                    }
                    // 0x0054ef78
                    charge(ctx, 3);
                    s0 = addiu(s0, 384);
                    s4 = addiu(s4, 128);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0054ef84
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x0054ef88
            charge(ctx, 3);
            v0 = slt(s3, fp);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054ef94
    charge(ctx, 4);
    s3 = fp;
    v0 = slti(s3, 32);
    if (v0 == 0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x0054efa4
        charge(ctx, 1);
        for (;;) {
            // 0x0054efa8
            charge(ctx, 2);
            if (i64(s5) <= 0) {
                s3 = addiu(s3, 1);
            } else {
                // 0x0054efb0
                charge(ctx, 6);
                lw(a0, sp, 0x4);
                v0 = sll(s3, 2);
                v1 = 63;
                s1 = s5;
                v0 = addu(v0, a0);
                for (;;) {
                    // 0x0054efc8
                    charge(ctx, 7);
                    s1 = addiu(s1, -1);
                    sw(v1, v0, 256);
                    sw(v1, v0, 128);
                    sw(v1, v0, 0);
                    v0 = addiu(v0, 384);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0054efe4
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x0054efe8
            charge(ctx, 3);
            v0 = slti(s3, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054eff4
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0054eff8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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

// 0x0054F028 sub_54F028 -- 1432 bytes; frame 0x80: s6 sp+0x60, s7 sp+0x68, s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, s4 sp+0x50, s5 sp+0x58, fp sp+0x70, ra sp+0x78
// Reads and dequantises the Layer II samples (grouped and ungrouped codes) of one granule group into the sample
// buffer.
void sub_54F028(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054f028
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = 0x790000;
    sd(s6, sp, 0x60);
    s6 = 0;
    sd(s7, sp, 0x68);
    s7 = t1;
    sd(s0, sp, 0x30);
    sd(s1, sp, 0x38);
    sd(s2, sp, 0x40);
    sd(s3, sp, 0x48);
    sd(s4, sp, 0x50);
    sd(s5, sp, 0x58);
    sd(fp, sp, 0x70);
    sd(ra, sp, 0x78);
    lw(v0, a1, 16);
    sw(v0, sp, 0x14);
    v0 = 0x790000;
    lw(t2, a1, 24);
    sw(a3, sp, 0x8);
    sw(t2, sp, 0x1C);
    sw(a0, sp, 0x0);
    sw(a2, sp, 0x4);
    sw(t0, sp, 0xC);
    lw(a3, sp, 0x14);
    lw(a0, a1, 4);
    sw(a0, sp, 0x10);
    lw(a1, a1, 20);
    sw(zero, v1, 30200);  // 0x7975F8
    sw(a1, sp, 0x18);
    sw(zero, v0, 28500);  // 0x796F54
    if (i64(a3) > 0) {
        // 0x0054f0a4
        charge(ctx, 3);
        sw(zero, sp, 0x24);
        sw(zero, sp, 0x28);
        for (;;) {
            // 0x0054f0b0
            charge(ctx, 5);
            fp = 0;
            lw(t0, sp, 0x18);
            t0 = slt(s6, t0);
            sw(t0, sp, 0x20);
            for (;;) {
                // 0x0054f4b8
                charge(ctx, 3);
                lw(a3, sp, 0x20);
                lw(t0, sp, 0x10);
                if (a3 != 0) {
                    // 0x0054f4c4
                    charge(ctx, 3);
                    v0 = slt(fp, t0);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = sll(fp, 5);
                    if (!cc) {
                        goto L_0054f4d0_28;
                    }
                    backedge(ctx);
                    goto L_0054f0c8;
                }
                // 0x0054f4d8
                charge(ctx, 2);
                v0 = sll(fp, 5);
                if (i64(fp) > 0) {
                    break;
                }
                backedge(ctx);
            L_0054f0c8:
                charge(ctx, 7);
                lw(t2, sp, 0x4);
                v0 = addu(v0, s6);
                v0 = sll(v0, 2);
                v0 = addu(v0, t2);
                lw(a1, v0, 0);
                v1 = sll(fp, 1);
                if (a1 == 0) {
                    // 0x0054f440
                    charge(ctx, 9);
                    v0 = sll(fp, 1);
                    v0 = addu(v0, fp);
                    v0 = sll(v0, 5);
                    v0 = addu(v0, s6);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s7);
                    sh(zero, v0, 128);
                    sh(zero, v0, 0);
                    sh(zero, v0, 64);
                L_0054f464:
                    charge(ctx, 1);
                    lw(t0, sp, 0x10);
                } else {
                    // 0x0054f0e4
                    charge(ctx, 26);
                    lw(a0, sp, 0xC);
                    s2 = addu(v1, fp);
                    v0 = sll(a1, 1);
                    v1 = addu(s2, a0);
                    v0 = addu(v0, a1);
                    v1 = sll(v1, 5);
                    lw(a3, sp, 0x28);
                    v1 = addu(v1, s6);
                    lw(t2, sp, 0x8);
                    v0 = sll(v0, 3);
                    lw(t0, sp, 0x1C);
                    v1 = sll(v1, 2);
                    v0 = addu(a3, v0);
                    v1 = addu(v1, t2);
                    a2 = addu(v0, t0);
                    lw(v0, v1, 0);
                    v1 = 0x790000;
                    v1 = addiu(v1, 29344);  // &0x7972A0
                    lw(a0, a2, 8);
                    v0 = sll(v0, 2);
                    s1 = 3;
                    v0 = addu(v0, v1);
                    lw(s4, a2, 20);
                    lw(s3, a2, 16);
                    lw(s5, v0, 0);
                    if (a0 == s1) {
                        // 0x0054f14c
                        charge(ctx, 4);
                        lw(s1, a2, 4);
                        v0 = slti(s1, 9);
                        lw(a0, sp, 0x0);
                        if (v0 == 0) {
                            // 0x0054f1e8
                            charge(ctx, 31);
                            a1 = s1;
                            s0 = sll(s2, 5);
                            jal(ctx, 0x54F1ECu, gen::fn_sub_54DB38_0054db38);
                            a1 = s1;
                            mult(v1, v0, s3);
                            s0 = addu(s0, s6);
                            s0 = sll(s0, 1);
                            lw(a0, sp, 0x0);
                            s0 = addu(s0, s7);
                            a2 = addu(v1, s4);
                            a2 = sra(a2, 2);
                            mult(a2, a2, s5);
                            a2 = sra(a2, 16);
                            link(ctx, 0x54F21Cu);  // $ra first: the delay slot below depends on it
                            sh(a2, s0, 0);
                            call(ctx, gen::fn_sub_54DB38_0054db38);
                            a1 = s1;
                            mult(v1, v0, s3);
                            lw(a0, sp, 0x0);
                            a2 = addu(v1, s4);
                            a2 = sra(a2, 2);
                            mult(a2, a2, s5);
                            a2 = sra(a2, 16);
                            link(ctx, 0x54F240u);  // $ra first: the delay slot below depends on it
                            sh(a2, s0, 64);
                            call(ctx, gen::fn_sub_54DB38_0054db38);
                            mult(v1, v0, s3);
                            a2 = addu(v1, s4);
                            a2 = sra(a2, 2);
                            mult(a2, a2, s5);
                            a2 = sra(a2, 16);
                            sh(a2, s0, 128);
                        } else {
                            // 0x0054f15c
                            charge(ctx, 35);
                            a1 = sll(s1, 1);
                            a1 = addu(a1, s1);
                            jal(ctx, 0x54F160u, gen::fn_sub_54DB38_0054db38);
                            v1 = sll(s1, 2);
                            a0 = 0x790000;
                            a0 = addiu(a0, 30064);  // &0x797570
                            v1 = addu(v1, a0);
                            a0 = sll(s2, 5);
                            lw(a1, v1, 0);
                            a0 = addu(a0, s6);
                            a0 = sll(a0, 1);
                            v1 = v0 & a1;
                            v0 = srav(v0, s1);
                            mult(a3, v1, s3);
                            a1 = v0 & a1;
                            mult(v1, a1, s3);
                            a0 = addu(a0, s7);
                            v0 = srav(v0, s1);
                            a2 = addu(a3, s4);
                            a2 = sra(a2, 2);
                            mult(a2, a2, s5);
                            a2 = sra(a2, 16);
                            sh(a2, a0, 128);
                            a2 = addu(v1, s4);
                            a2 = sra(a2, 2);
                            mult(v1, v0, s3);
                            mult(a2, a2, s5);
                            a2 = sra(a2, 16);
                            sh(a2, a0, 64);
                            a2 = addu(v1, s4);
                            a2 = sra(a2, 2);
                            mult(a2, a2, s5);
                            a2 = sra(a2, 16);
                            sh(a2, a0, 0);
                        }
                        goto L_0054f464;
                    }
                    // 0x0054f268
                    charge(ctx, 6);
                    lw(a1, a2, 4);
                    lw(a0, sp, 0x0);
                    link(ctx, 0x54F270u);  // $ra first: the delay slot below depends on it
                    lw(s0, a2, 0);
                    call(ctx, gen::fn_sub_54DB38_0054db38);
                    a3 = v0;
                    if (s0 == s1) {
                        // 0x0054f280
                        charge(ctx, 26);
                        v0 = 0x7A0000;
                        v1 = sll(s2, 5);
                        a0 = addiu(v0, -30912);  // &0x798740
                        v1 = addu(v1, s6);
                        v0 = addu(a3, a0);
                        a0 = addiu(a0, 32);  // &0x798760
                        lb(a1, v0, 0);
                        v0 = addu(a3, a0);
                        v1 = sll(v1, 1);
                        a0 = addu(a0, a3);
                        mult(t0, a1, s3);
                        v1 = addu(v1, s7);
                        a2 = addu(t0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 0);
                        lb(a1, v0, 0);
                        mult(v0, a1, s3);
                        a2 = addu(v0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 64);
                        lb(a1, a0, 32);
                        goto L_0054f3cc;
                    }
                    // 0x0054f2e8
                    charge(ctx, 3);
                    v0 = 5;
                    cc = s0 != v0;  // the condition, before the delay slot changes it
                    v0 = 9;
                    if (!cc) {
                        // 0x0054f2f4
                        charge(ctx, 26);
                        v0 = 0x7A0000;
                        v1 = sll(s2, 5);
                        a0 = addiu(v0, -30816);  // &0x7987A0
                        v1 = addu(v1, s6);
                        v0 = addu(a3, a0);
                        a0 = addiu(a0, 128);  // &0x798820
                        lb(a1, v0, 0);
                        v0 = addu(a3, a0);
                        v1 = sll(v1, 1);
                        a0 = addu(a0, a3);
                        mult(t0, a1, s3);
                        v1 = addu(v1, s7);
                        a2 = addu(t0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 0);
                        lb(a1, v0, 0);
                        mult(v0, a1, s3);
                        a2 = addu(v0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 64);
                        lb(a1, a0, 128);
                        goto L_0054f3cc;
                    }
                    // 0x0054f360
                    charge(ctx, 2);
                    cc = s0 != v0;  // the condition, before the delay slot changes it
                    v0 = sll(s2, 5);
                    if (!cc) {
                        // 0x0054f368
                        charge(ctx, 25);
                        v0 = 0x7A0000;
                        v1 = sll(s2, 5);
                        a0 = addiu(v0, -30432);  // &0x798920
                        v1 = addu(v1, s6);
                        v0 = addu(a3, a0);
                        a0 = addiu(a0, 1024);  // &0x798D20
                        lb(a1, v0, 0);
                        v0 = addu(a3, a0);
                        v1 = sll(v1, 1);
                        a0 = addu(a0, a3);
                        mult(t0, a1, s3);
                        v1 = addu(v1, s7);
                        a2 = addu(t0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 0);
                        lb(a1, v0, 0);
                        mult(v0, a1, s3);
                        a2 = addu(v0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 64);
                        lb(a1, a0, 1024);
                    L_0054f3cc:
                        charge(ctx, 7);
                        mult(v0, a1, s3);
                        a2 = addu(v0, s4);
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, v1, 128);
                        goto L_0054f464;
                    }
                    // 0x0054f3e8
                    charge(ctx, 4);
                    s1 = 0;
                    v0 = addu(v0, s6);
                    v0 = sll(v0, 1);
                    a1 = addu(v0, s7);
                    for (;;) {
                        // 0x0054f3f8
                        charge(ctx, 5);
                        div(a3, s0);
                        s1 = addiu(s1, 1);
                        a0 = slti(s1, 3);
                        if (s0 == 0) {
                            brk(ctx, 0x54F408u, 0x7u);
                        }
                        // 0x0054f40c
                        charge(ctx, 11);
                        mfhi(v0);
                        mflo(v1);
                        mult(a3, v0, s3);
                        a2 = addu(a3, s4);
                        a3 = v1;
                        a2 = sra(a2, 2);
                        mult(a2, a2, s5);
                        a2 = sra(a2, 16);
                        sh(a2, a1, 0);
                        a1 = addiu(a1, 64);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0054f438
                    charge(ctx, 2);
                    lw(t0, sp, 0x10);
                }
                // 0x0054f468
                charge(ctx, 3);
                v0 = 2;
                if (t0 != v0) {
                    fp = addiu(fp, 0x1);
                } else {
                    // 0x0054f474
                    charge(ctx, 3);
                    lw(t2, sp, 0x20);
                    if (t2 != 0) {
                        fp = addiu(fp, 0x1);
                    } else {
                        // 0x0054f480
                        charge(ctx, 6);
                        lw(a0, sp, 0x24);
                        v1 = sll(s6, 1);
                        v1 = addu(v1, s7);
                        s1 = 2;
                        v0 = addu(s7, a0);
                        a0 = addiu(v0, 192);
                        for (;;) {
                            // 0x0054f498
                            charge(ctx, 7);
                            lhu(v0, v1, 0);
                            v1 = addiu(v1, 64);
                            s1 = addiu(s1, -1);
                            sh(v0, a0, 0);
                            a0 = addiu(a0, 64);
                            if (i64(s1) < 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0054f4b4
                        charge(ctx, 1);
                        fp = addiu(fp, 0x1);
                    }
                }
            }
            // 0x0054f4e0
            charge(ctx, 1);
            lw(t2, sp, 0x24);
        L_0054f4e4:
            charge(ctx, 9);
            s6 = addiu(s6, 1);
            lw(a0, sp, 0x28);
            lw(v1, sp, 0x14);
            t2 = addiu(t2, 2);
            a0 = addiu(a0, 384);
            sw(t2, sp, 0x24);
            v0 = slt(s6, v1);
            sw(a0, sp, 0x28);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054f508
    charge(ctx, 4);
    lw(s6, sp, 0x14);
    v0 = slti(s6, 32);
    ld(s0, sp, 0x30);
    if (v0 != 0) {
        // 0x0054f518
        charge(ctx, 2);
        lw(a3, sp, 0x10);
        for (;;) {
            // 0x0054f520
            charge(ctx, 2);
            fp = 0;
            if (i64(a3) > 0) {
                // 0x0054f528
                charge(ctx, 2);
                v1 = 0;
                for (;;) {
                    // 0x0054f530
                    charge(ctx, 8);
                    v0 = addu(v1, fp);
                    s1 = 2;
                    v0 = sll(v0, 5);
                    v0 = addu(v0, s6);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s7);
                    v0 = addiu(v0, 128);
                    for (;;) {
                        // 0x0054f550
                        charge(ctx, 7);
                        s1 = addiu(s1, -1);
                        sh(zero, v0, 0);
                        v0 = addiu(v0, -64);
                        if (i64(s1) < 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0054f56c
                    charge(ctx, 5);
                    lw(t0, sp, 0x10);
                    fp = addiu(fp, 0x1);
                    v0 = slt(fp, t0);
                    v1 = addiu(v1, 2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0054f580
            charge(ctx, 4);
            s6 = addiu(s6, 1);
            v0 = slti(s6, 32);
            lw(a3, sp, 0x10);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0054f590
        charge(ctx, 1);
        ld(s0, sp, 0x30);
    }
    // 0x0054f594 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
    return;
L_0054f4d0_28:
    charge(ctx, 2);
    lw(t2, sp, 0x24);
    goto L_0054f4e4;
}

// 0x0054F730 sub_54F730 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Destroys an MPEG-audio stream's decoder under the ADXM lock: sub_548678, then when the handle (+4 -> +4) holds a
// decoder (+180), stops (sub_552080) and destroys it (sub_551F80), clears the slot and runs sub_551DA0.
void sub_54F730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054f730
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x54F740u, gen::fn_sub_548678_00548678);
    lw(v0, s0, 4);
    lw(s1, v0, 4);
    lw(s0, s1, 180);
    if (s0 == 0) {
        ld(s0, sp, 0x0);
        // 0x0054f790
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0054f75c
    charge(ctx, 13);
    jal(ctx, 0x54F75Cu, gen::fn_sub_540D40_00540d40);
    a0 = s0;
    jal(ctx, 0x54F764u, gen::fn_sub_552080_00552080);
    a0 = s0;
    jal(ctx, 0x54F76Cu, gen::fn_sub_551F80_00551f80);
    link(ctx, 0x54F774u);  // $ra first: the delay slot below depends on it
    sw(zero, s1, 180);
    call(ctx, gen::fn_sub_540D58_00540d58);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_551DA0_00551da0(ctx);  // tail call
}

// 0x0054F7A0 atan2l_6 -- 28 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 into word +44 of $a0; second chunk at 0x552618.
void atan2l_6(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054f7a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00552618
    charge(ctx, 2);
    sw(a1, a0, 44);
}

// 0x0054F7B8 cosl_6 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Sets word +8 of $a0 to 1 and returns 1; second chunk at 0x552620.
void cosl_6(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054f7b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00552620
    charge(ctx, 3);
    v0 = 1;
    sw(v0, a0, 8);
}

// 0x0054F7D0 coshl_6 -- 248 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// An MPEG-audio stream's server step under the ADXM lock: restarts a stopped decoder, starts it in state 1, and in
// state 2 runs sub_5523B8 (+188) times, accounts the produced samples (+136 / +144) and the position (+148), and stops
// at the decoder's end (status 3).
void coshl_6(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054f7d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    s0 = a0;
    jal(ctx, 0x54F7E4u, gen::fn_sub_540D40_00540d40);
    lw(s2, s0, 180);
    a0 = s2;
    jal(ctx, 0x54F7F0u, gen::fn_sub_551FF8_00551ff8);
    if (v0 != 0) {
        lw(v1, s0, 4);
    } else {
        // 0x0054f800
        charge(ctx, 5);
        sw(zero, s0, 144);
        a0 = s2;
        link(ctx, 0x54F808u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 136);
        call(ctx, gen::fn_sub_552080_00552080);
        lw(v1, s0, 4);
    }
    // 0x0054f814
    charge(ctx, 3);
    v0 = 1;
    if (v1 == v0) {
        // 0x0054f820
        charge(ctx, 6);
        sw(zero, s0, 136);
        a0 = s2;
        jal(ctx, 0x54F824u, gen::fn_sub_552028_00552028);
        v0 = 2;
        sw(v0, s0, 4);
        goto L_0054f8b0;
    }
    v0 = 2;
    // 0x0054f838
    charge(ctx, 2);
    if (v1 != v0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0054f840
        charge(ctx, 3);
        lw(v0, s0, 188);
        s1 = 0;
        if (i64(v0) > 0) {
            // 0x0054f84c
            charge(ctx, 1);
            a0 = s2;
            for (;;) {
                // 0x0054f850
                charge(ctx, 6);
                s1 = addiu(s1, 1);
                jal(ctx, 0x54F850u, gen::fn_sub_5523B8_005523b8);
                lw(v0, s0, 188);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                a0 = s2;
                backedge(ctx);
            }
        }
        // 0x0054f868
        charge(ctx, 15);
        a0 = s2;
        jal(ctx, 0x54F868u, gen::fn_sub_552468_00552468);
        lw(v1, s0, 136);
        a0 = s2;
        v0 = subu(v0, v1);
        v1 = addu(v1, v0);
        sw(v0, s0, 144);
        link(ctx, 0x54F884u);  // $ra first: the delay slot below depends on it
        sw(v1, s0, 136);
        call(ctx, gen::fn_sub_552460_00552460);
        a0 = s2;
        link(ctx, 0x54F890u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 148);
        call(ctx, gen::fn_sub_551FF8_00551ff8);
        v1 = 3;
        if (v0 != v1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0054f8a4
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x54F8A4u, gen::fn_sub_552080_00552080);
            sw(zero, s0, 4);
        L_0054f8b0:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0054f8b4
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_540D58_00540d58(ctx);  // tail call
}

// 0x0054F8C8 sub_54F8C8 -- 432 bytes; leaf frame (no stack)
// The synthesis matrixing, MMI form: each output is the dot product of the 32 s16 sub-band samples ($a0) with a
// 32-coefficient row ($a1, 64 bytes apart; phmadh over 4 quadwords, folded and >> 12), written to the 64-entry vector
// ($a2) forwards and mirrored (negated - 1 in the first half, as is in the second).
void sub_54F8C8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x0054f8c8
    enter(ctx, 7);  // entry check point + this block's cycles
    a3 = a0;
    v1 = a1;
    v0 = a2;
    t4 = addiu(a1, 0);
    t5 = addiu(a2, 0);
    t6 = addiu(a2, 64);
    t7 = addiu(a2, 32);
    for (;;) {
        // 0x0054f8e4
        charge(ctx, 34);
        lq(t0, a0, 0);
        lq(t1, t4, 0);
        phmadh(t2, t0, t1);
        lq(t0, a0, 16);
        lq(t1, t4, 16);
        phmadh(t3, t0, t1);
        paddw(t2, t2, t3);
        lq(t0, a0, 32);
        lq(t1, t4, 32);
        phmadh(t3, t0, t1);
        paddw(t2, t2, t3);
        lq(t0, a0, 48);
        lq(t1, t4, 48);
        phmadh(t3, t0, t1);
        paddw(t2, t2, t3);
        pxor(t0, t0, t0);
        mtsah(t0, 4);
        qfsrv(t3, t2, t2);
        paddw(t2, t2, t3);
        pxor(t1, t1, t1);
        mtsah(t1, 2);
        qfsrv(t3, t2, t2);
        paddw(t2, t2, t3);
        psraw(t2, t2, 12);
        sh(t2, t5, 0);
        t2 = subu(0, t2);
        t2 = addiu(t2, -1);
        sh(t2, t6, 0);
        t4 = addiu(t4, 64);
        t5 = addiu(t5, 2);
        t6 = addiu(t6, -2);
        if (t5 == t7) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054f96c
    charge(ctx, 6);
    sh(zero, t5, 0);
    t4 = addiu(t4, 1088);
    t5 = addiu(a2, 66);
    t6 = addiu(a2, 126);
    t7 = addiu(a2, 96);
    for (;;) {
        // 0x0054f984
        charge(ctx, 32);
        lq(t0, a0, 0);
        lq(t1, t4, 0);
        phmadh(t2, t0, t1);
        lq(t0, a0, 16);
        lq(t1, t4, 16);
        phmadh(t3, t0, t1);
        paddw(t2, t2, t3);
        lq(t0, a0, 32);
        lq(t1, t4, 32);
        phmadh(t3, t0, t1);
        paddw(t2, t2, t3);
        lq(t0, a0, 48);
        lq(t1, t4, 48);
        phmadh(t3, t0, t1);
        paddw(t2, t2, t3);
        pxor(t0, t0, t0);
        mtsah(t0, 4);
        qfsrv(t3, t2, t2);
        paddw(t2, t2, t3);
        pxor(t1, t1, t1);
        mtsah(t1, 2);
        qfsrv(t3, t2, t2);
        paddw(t2, t2, t3);
        psraw(t2, t2, 12);
        sh(t2, t5, 0);
        sh(t2, t6, 0);
        t4 = addiu(t4, 64);
        t5 = addiu(t5, 2);
        t6 = addiu(t6, -2);
        if (t5 == t7) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054fa04
    charge(ctx, 29);
    lq(t0, a0, 0);
    lq(t1, t4, 0);
    phmadh(t2, t0, t1);
    lq(t0, a0, 16);
    lq(t1, t4, 16);
    phmadh(t3, t0, t1);
    paddw(t2, t2, t3);
    lq(t0, a0, 32);
    lq(t1, t4, 32);
    phmadh(t3, t0, t1);
    paddw(t2, t2, t3);
    lq(t0, a0, 48);
    lq(t1, t4, 48);
    phmadh(t3, t0, t1);
    paddw(t2, t2, t3);
    pxor(t0, t0, t0);
    mtsah(t0, 4);
    qfsrv(t3, t2, t2);
    paddw(t2, t2, t3);
    pxor(t1, t1, t1);
    mtsah(t1, 2);
    qfsrv(t3, t2, t2);
    paddw(t2, t2, t3);
    psraw(t2, t2, 12);
    sh(t2, t5, 0);
}

// 0x0054FA78 sub_54FA78 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// The synthesis window: 32 outputs, each 16 taps of the vector buffer ($a0, alternating 96 / 32 sample strides) times
// the window ($a1), the second-pipeline mult1 interleaved; written to $a2.
void sub_54FA78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x0054fa78
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
        // 0x0054fa98
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
            // 0x0054fc30
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x0054fc40
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x0054fc24
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x0054fc44
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054fc54
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054FC68 sub_54FC68 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// The synthesis window, the shape of sub_54FA78 for another buffer phase.
void sub_54FC68(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x0054fc68
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
        // 0x0054fc88
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
        lh(a2, v0, -1856);
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
            // 0x0054fe20
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x0054fe30
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x0054fe14
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x0054fe34
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0054fe44
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0054FE58 sub_54FE58 -- 496 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10
// The synthesis window, the shape of sub_54FA78 for another buffer phase.
void sub_54FE58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x0054fe58
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
        // 0x0054fe78
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
        v0 = addiu(v0, -1984);
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
            // 0x00550010
            charge(ctx, 4);
            v0 = lui(0xFC00);
            v0 = slt(t9, v0);
            if (v0 == 0) {
                v0 = sra(t9, 11);
            } else {
                // 0x00550020
                charge(ctx, 1);
                v0 = si(-32768);
            }
        } else {
            // 0x00550004
            charge(ctx, 2);
            v0 = 32767;
        }
        // 0x00550024
        charge(ctx, 4);
        sh(v0, s0, 0);
        s2 = addiu(s2, -1);
        s0 = addiu(s0, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00550034
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
