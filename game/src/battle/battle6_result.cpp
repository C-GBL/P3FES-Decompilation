// The battle code, sixth pass (slice battle6; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle6.h for the
// layouts): the result screen -- the persona birth's resources (brp_birth.c / brp_res.c), the item stock-over panel
// (br_item.c), the hero panel (br_hero.c), the persona panels (br_persona.c / brp_persona.c), the persona sequence's
// steps (brp_seq.c), the 'persona grow' screen (brp_root.c), the level panel (br_lvpnl.c) and the parameter panel
// (brp_param.c). The bodies are p3fes_handgen's (frame, spills, $ra links, every register, cycle charges, check
// points); this file names their offsets (battle3.h's b3::, battle4.h's b4::, battle5.h's b5:: records reused, this
// slice's in b6::) and gives each function its role -- proposed names in brackets (ADR-0009), symbols in code are
// functions.json's. Still-recompiled callees are reached through their gen:: entry points (the relaxed callee rule).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle6.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_bpIfontDrawNumber_00238980(p3fes::EEContext&);
void fn_brItem_UpdateStockOverBgTask_0025f4a0(p3fes::EEContext&);
void fn_datGetAcademicLevel_00177280(p3fes::EEContext&);
void fn_datGetCharmLevel_001772f0(p3fes::EEContext&);
void fn_datGetCourageLevel_00177360(p3fes::EEContext&);
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);
void fn_frFontClearDefaultGlyphFlags_003b0e90(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_frFontSetDefaultGlyphFlags_003b0e70(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskInitEx_00194e10(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_msgWinClose_003c7650(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_nullsub_66_0020ac80(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_10A370_0010a370(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_119A60_00119a60(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C6F0_0016c6f0(p3fes::EEContext&);
void fn_sub_16C740_0016c740(p3fes::EEContext&);
void fn_sub_16C790_0016c790(p3fes::EEContext&);
void fn_sub_16C7E0_0016c7e0(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16D2F0_0016d2f0(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_173370_00173370(p3fes::EEContext&);
void fn_sub_173580_00173580(p3fes::EEContext&);
void fn_sub_1749A0_001749a0(p3fes::EEContext&);
void fn_sub_176840_00176840(p3fes::EEContext&);
void fn_sub_1768E0_001768e0(p3fes::EEContext&);
void fn_sub_176A30_00176a30(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_1828D0_001828d0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1FB1F0_001fb1f0(p3fes::EEContext&);
void fn_sub_1FB560_001fb560(p3fes::EEContext&);
void fn_sub_1FBA70_001fba70(p3fes::EEContext&);
void fn_sub_1FC230_001fc230(p3fes::EEContext&);
void fn_sub_1FC3C0_001fc3c0(p3fes::EEContext&);
void fn_sub_20E030_0020e030(p3fes::EEContext&);
void fn_sub_20E800_0020e800(p3fes::EEContext&);
void fn_sub_21A1B0_0021a1b0(p3fes::EEContext&);
void fn_sub_21B4A0_0021b4a0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21CD00_0021cd00(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21E380_0021e380(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_21EAE0_0021eae0(p3fes::EEContext&);
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);
void fn_sub_233970_00233970(p3fes::EEContext&);
void fn_sub_233D70_00233d70(p3fes::EEContext&);
void fn_sub_233DF0_00233df0(p3fes::EEContext&);
void fn_sub_233E70_00233e70(p3fes::EEContext&);
void fn_sub_234070_00234070(p3fes::EEContext&);
void fn_sub_234630_00234630(p3fes::EEContext&);
void fn_sub_234690_00234690(p3fes::EEContext&);
void fn_sub_234710_00234710(p3fes::EEContext&);
void fn_sub_2347E0_002347e0(p3fes::EEContext&);
void fn_sub_238BF0_00238bf0(p3fes::EEContext&);
void fn_sub_238DC0_00238dc0(p3fes::EEContext&);
void fn_sub_239140_00239140(p3fes::EEContext&);
void fn_sub_239280_00239280(p3fes::EEContext&);
void fn_sub_24A7F0_0024a7f0(p3fes::EEContext&);
void fn_sub_24A870_0024a870(p3fes::EEContext&);
void fn_sub_24AA90_0024aa90(p3fes::EEContext&);
void fn_sub_24AB10_0024ab10(p3fes::EEContext&);
void fn_sub_24ABD0_0024abd0(p3fes::EEContext&);
void fn_sub_24AC40_0024ac40(p3fes::EEContext&);
void fn_sub_24AC90_0024ac90(p3fes::EEContext&);
void fn_sub_24ADF0_0024adf0(p3fes::EEContext&);
void fn_sub_24B9E0_0024b9e0(p3fes::EEContext&);
void fn_sub_24BA50_0024ba50(p3fes::EEContext&);
void fn_sub_24BB30_0024bb30(p3fes::EEContext&);
void fn_sub_24BF80_0024bf80(p3fes::EEContext&);
void fn_sub_25D8A0_0025d8a0(p3fes::EEContext&);
void fn_sub_25D9E0_0025d9e0(p3fes::EEContext&);
void fn_sub_25DA30_0025da30(p3fes::EEContext&);
void fn_sub_25ED40_0025ed40(p3fes::EEContext&);
void fn_sub_25F510_0025f510(p3fes::EEContext&);
void fn_sub_25F5D0_0025f5d0(p3fes::EEContext&);
void fn_sub_260900_00260900(p3fes::EEContext&);
void fn_sub_260920_00260920(p3fes::EEContext&);
void fn_sub_260940_00260940(p3fes::EEContext&);
void fn_sub_262790_00262790(p3fes::EEContext&);
void fn_sub_263170_00263170(p3fes::EEContext&);
void fn_sub_263DB0_00263db0(p3fes::EEContext&);
void fn_sub_264CA0_00264ca0(p3fes::EEContext&);
void fn_sub_264EF0_00264ef0(p3fes::EEContext&);
void fn_sub_272330_00272330(p3fes::EEContext&);
void fn_sub_272380_00272380(p3fes::EEContext&);
void fn_sub_272400_00272400(p3fes::EEContext&);
void fn_sub_2727C0_002727c0(p3fes::EEContext&);
void fn_sub_272810_00272810(p3fes::EEContext&);
void fn_sub_273800_00273800(p3fes::EEContext&);
void fn_sub_273B30_00273b30(p3fes::EEContext&);
void fn_sub_273C00_00273c00(p3fes::EEContext&);
void fn_sub_273C70_00273c70(p3fes::EEContext&);
void fn_sub_273D50_00273d50(p3fes::EEContext&);
void fn_sub_273E10_00273e10(p3fes::EEContext&);
void fn_sub_274100_00274100(p3fes::EEContext&);
void fn_sub_274C00_00274c00(p3fes::EEContext&);
void fn_sub_275370_00275370(p3fes::EEContext&);
void fn_sub_2753C0_002753c0(p3fes::EEContext&);
void fn_sub_275440_00275440(p3fes::EEContext&);
void fn_sub_275520_00275520(p3fes::EEContext&);
void fn_sub_2755D0_002755d0(p3fes::EEContext&);
void fn_sub_275670_00275670(p3fes::EEContext&);
void fn_sub_2756C0_002756c0(p3fes::EEContext&);
void fn_sub_2757A0_002757a0(p3fes::EEContext&);
void fn_sub_2757E0_002757e0(p3fes::EEContext&);
void fn_sub_2758E0_002758e0(p3fes::EEContext&);
void fn_sub_275A70_00275a70(p3fes::EEContext&);
void fn_sub_275A80_00275a80(p3fes::EEContext&);
void fn_sub_275A90_00275a90(p3fes::EEContext&);
void fn_sub_275BC0_00275bc0(p3fes::EEContext&);
void fn_sub_275CB0_00275cb0(p3fes::EEContext&);
void fn_sub_276870_00276870(p3fes::EEContext&);
void fn_sub_2768C0_002768c0(p3fes::EEContext&);
void fn_sub_276910_00276910(p3fes::EEContext&);
void fn_sub_276920_00276920(p3fes::EEContext&);
void fn_sub_276930_00276930(p3fes::EEContext&);
void fn_sub_2769C0_002769c0(p3fes::EEContext&);
void fn_sub_276A80_00276a80(p3fes::EEContext&);
void fn_sub_276B10_00276b10(p3fes::EEContext&);
void fn_sub_276BA0_00276ba0(p3fes::EEContext&);
void fn_sub_276C30_00276c30(p3fes::EEContext&);
void fn_sub_276CC0_00276cc0(p3fes::EEContext&);
void fn_sub_276D10_00276d10(p3fes::EEContext&);
void fn_sub_276D30_00276d30(p3fes::EEContext&);
void fn_sub_276D90_00276d90(p3fes::EEContext&);
void fn_sub_277070_00277070(p3fes::EEContext&);
void fn_sub_2770F0_002770f0(p3fes::EEContext&);
void fn_sub_2771F0_002771f0(p3fes::EEContext&);
void fn_sub_278550_00278550(p3fes::EEContext&);
void fn_sub_279120_00279120(p3fes::EEContext&);
void fn_sub_2791B0_002791b0(p3fes::EEContext&);
void fn_sub_2792C0_002792c0(p3fes::EEContext&);
void fn_sub_279330_00279330(p3fes::EEContext&);
void fn_sub_279450_00279450(p3fes::EEContext&);
void fn_sub_2794C0_002794c0(p3fes::EEContext&);
void fn_sub_279510_00279510(p3fes::EEContext&);
void fn_sub_279580_00279580(p3fes::EEContext&);
void fn_sub_2795F0_002795f0(p3fes::EEContext&);
void fn_sub_2796B0_002796b0(p3fes::EEContext&);
void fn_sub_279700_00279700(p3fes::EEContext&);
void fn_sub_279750_00279750(p3fes::EEContext&);
void fn_sub_2797A0_002797a0(p3fes::EEContext&);
void fn_sub_2797F0_002797f0(p3fes::EEContext&);
void fn_sub_279840_00279840(p3fes::EEContext&);
void fn_sub_279890_00279890(p3fes::EEContext&);
void fn_sub_2798F0_002798f0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7990_003c7990(p3fes::EEContext&);
void fn_sub_3C7BC0_003c7bc0(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
void fn_sub_3C9B00_003c9b00(p3fes::EEContext&);
void fn_sub_3C9D00_003c9d00(p3fes::EEContext&);
void fn_sub_3C9D80_003c9d80(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b6;  // this slice's additions (battle6.h)

// 0x0024AC90 sub_24AC90 -- 340 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpBirthTerm] Closes the persona birth work (brp_birth.c, *$gp 0x7CE330; K_Assert lines 127 / 259: not busy): the
// texture set (sub_239280), sub_20E030, the resources (brpResTerm), sub_21A1B0, the effect objects of flags 0x10 /
// 0x20 / 0x40 / 0x100 (+4036..+4048, sub_34FCF0), the task (flag 4, +50528, kwlnTaskDestroyWithHierarchy), the model
// (flag 8, nullsub_66 of +28); frees the work (RwFree slot) and clears the $gp slot.
void sub_24AC90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024ac90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpBirth);  // the persona birth work (brp_birth.c) 0x7CE330
    if (v0 == 0) {
        // 0x0024aca8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5912);  // "brp_birth.c"
        a1 = 127;
        jal(ctx, 0x24ACB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024acbc
    charge(ctx, 6);
    lw(s0, gp, kGpBrpBirth);  // the persona birth work (brp_birth.c) 0x7CE330
    lw(v0, s0, birth::kHeld);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0024acd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5912);  // "brp_birth.c"
        a1 = 259;
        jal(ctx, 0x24ACE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024ace8
    charge(ctx, 12);
    jal(ctx, 0x24ACE8u, gen::fn_sub_239280_00239280);
    jal(ctx, 0x24ACF0u, gen::fn_sub_20E030_0020e030);
    jal(ctx, 0x24ACF8u, gen::fn_sub_24BA50_0024ba50);
    jal(ctx, 0x24AD00u, gen::fn_sub_21A1B0_0021a1b0);
    lw(v0, s0, birth::kHeld);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x0024ad18
        charge(ctx, 3);
        lw(a0, s0, birth::kFxObjects);
        jal(ctx, 0x24AD1Cu, gen::fn_sub_34FCF0_0034fcf0);
    }
    // 0x0024ad24
    charge(ctx, 4);
    lw(v0, s0, birth::kHeld);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x0024ad34
        charge(ctx, 3);
        lw(a0, s0, 4040);
        jal(ctx, 0x24AD38u, gen::fn_sub_34FCF0_0034fcf0);
    }
    // 0x0024ad40
    charge(ctx, 4);
    lw(v0, s0, birth::kHeld);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        // 0x0024ad50
        charge(ctx, 3);
        lw(a0, s0, 4044);
        jal(ctx, 0x24AD54u, gen::fn_sub_34FCF0_0034fcf0);
    }
    // 0x0024ad5c
    charge(ctx, 4);
    lw(v0, s0, birth::kHeld);
    v0 = v0 & 0x100;
    if (v0 != 0) {
        // 0x0024ad6c
        charge(ctx, 3);
        lw(a0, s0, 4048);
        jal(ctx, 0x24AD70u, gen::fn_sub_34FCF0_0034fcf0);
    }
    // 0x0024ad78
    charge(ctx, 4);
    lw(v0, s0, birth::kHeld);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0024ad88
        charge(ctx, 5);
        v0 = 0x10000;
        v0 = addu(s0, v0);
        lw(a0, v0, -15008);
        jal(ctx, 0x24AD94u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    // 0x0024ad9c
    charge(ctx, 4);
    lw(v0, s0, birth::kHeld);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x0024adac
        charge(ctx, 3);
        a0 = addiu(s0, 28);
        jal(ctx, 0x24ADB0u, gen::fn_nullsub_66_0020ac80);
    }
    // 0x0024adb8
    charge(ctx, 11);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x24ADC4u, v0.u());
    sw(zero, gp, kGpBrpBirth);  // the persona birth work (brp_birth.c) 0x7CE330
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024BA50 sub_24BA50 -- 224 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpResTerm] Closes the persona birth resource work (brp_res.c, *$gp 0x7CE334; K_Assert line 57): frees the four
// loaded files (+16..+28, flag 1), the message file copy (+32, flag 2) and the block +36 (flag 4) through the RwFree
// slot, clears the $gp slot.
void sub_24BA50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024ba50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    if (v1 == 0) {
        // 0x0024ba6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5848);  // "brp_res.c"
        a1 = 57;
        jal(ctx, 0x24BA78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024ba80
    charge(ctx, 5);
    lw(s0, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    lw(v1, s0, brpres::kLoaded);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0024ba94
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x0024bac0
            charge(ctx, 3);
            v1 = slti(s1, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0024baa0
            charge(ctx, 8);
            v0 = sll(s1, 2);
            v0 = addu(s0, v0);
            lw(a0, v0, 16);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x24BAB4u, v0.u());
            s1 = addiu(s1, 1);
        }
    }
    // 0x0024bacc
    charge(ctx, 4);
    lw(v1, s0, brpres::kLoaded);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0024badc
        charge(ctx, 5);
        lw(a0, s0, brpres::kMessages);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x24BAE8u, v0.u());
    }
    // 0x0024baf0
    charge(ctx, 4);
    lw(v1, s0, brpres::kLoaded);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0024bb00
        charge(ctx, 5);
        lw(a0, s0, brpres::kBlock);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x24BB0Cu, v0.u());
    }
    // 0x0024bb14 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024BB30 sub_24BB30 -- 780 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpResUpdate] Per-frame step of the persona birth resource work (K_Assert lines 57 / 142): once the archive
// request (+8, flag 1) is loaded it takes its six files -- 0 the texture set (sub_20E800), 1 the model set
// (sub_21B4A0), 2..5 copied into RwMalloc blocks +16..+28 --, sets loaded flag 1, destroys the request; once the
// message request (+12, flag 2) is loaded it copies the BMD (request +272 / +280) into +32, sets loaded flag 2 and
// destroys it.
void sub_24BB30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024bb30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    if (v1 == 0) {
        // 0x0024bb50
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5848);  // "brp_res.c"
        a1 = 57;
        jal(ctx, 0x24BB5Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024bb64
    charge(ctx, 5);
    lw(s0, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    lw(v1, s0, brpres::kLoading);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x0024bb78
        charge(ctx, 5);
        lw(a0, s0, brpres::kArchiveReq);
        jal(ctx, 0x24BB7Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        if (v0 != 0) {
            // 0x0024bb8c
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0024bd68
                charge(ctx, 3);
                v0 = slti(s1, 6);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0024bb98
                charge(ctx, 3);
                at = sltiu(s1, 6);
                if (at == 0) {
                    // 0x0024bd50
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -5848);  // "brp_res.c"
                    a1 = 142;
                    jal(ctx, 0x24BD5Cu, gen::fn_sub_19D3F0_0019d3f0);
                } else {
                    // 0x0024bba4
                    charge(ctx, 7);
                    v1 = 0x7B0000;
                    v1 = addiu(v1, 30960);  // &0x7B78F0
                    v0 = sll(s1, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x24BBC0u:  // table[0]: file 0, the texture set (sub_20E800)
                        // 0x0024bbc0
                        charge(ctx, 10);
                        lw(a0, s0, brpres::kArchiveReq);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x24BBCCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x24BBD8u, gen::fn_sub_20E800_0020e800);
                        break;
                    case 0x24BBE8u:  // table[1]: file 1, the model set (sub_21B4A0)
                        // 0x0024bbe8
                        charge(ctx, 10);
                        lw(a0, s0, brpres::kArchiveReq);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x24BBF4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x24BC00u, gen::fn_sub_21B4A0_0021b4a0);
                        break;
                    case 0x24BC10u:  // table[2]: file 2 -> +16
                        // 0x0024bc10
                        charge(ctx, 20);
                        lw(a0, s0, brpres::kArchiveReq);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x24BC1Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        s2 = v0;
                        lw(a0, sp, 0x4C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x24BC38u, v0.u());
                        sw(v0, s0, brpres::kFiles);
                        lw(a2, sp, 0x4C);
                        a0 = v0;
                        a1 = s2;
                        jal(ctx, 0x24BC50u, gen::fn_memcpy_00521250);
                        break;
                    case 0x24BC60u:  // table[3]: file 3 -> +20
                        // 0x0024bc60
                        charge(ctx, 20);
                        lw(a0, s0, brpres::kArchiveReq);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x24BC6Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        s2 = v0;
                        lw(a0, sp, 0x4C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x24BC88u, v0.u());
                        sw(v0, s0, 20);
                        lw(a2, sp, 0x4C);
                        a0 = v0;
                        a1 = s2;
                        jal(ctx, 0x24BCA0u, gen::fn_memcpy_00521250);
                        break;
                    case 0x24BCB0u:  // table[4]: file 4 -> +24
                        // 0x0024bcb0
                        charge(ctx, 20);
                        lw(a0, s0, brpres::kArchiveReq);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x24BCBCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        s2 = v0;
                        lw(a0, sp, 0x4C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x24BCD8u, v0.u());
                        sw(v0, s0, 24);
                        lw(a2, sp, 0x4C);
                        a0 = v0;
                        a1 = s2;
                        jal(ctx, 0x24BCF0u, gen::fn_memcpy_00521250);
                        break;
                    case 0x24BD00u:  // table[5]: file 5 -> +28
                        // 0x0024bd00
                        charge(ctx, 20);
                        lw(a0, s0, brpres::kArchiveReq);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x24BD0Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        s2 = v0;
                        lw(a0, sp, 0x4C);
                        a1 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        jalr(ctx, 0x24BD28u, v0.u());
                        sw(v0, s0, 28);
                        lw(a2, sp, 0x4C);
                        a0 = v0;
                        a1 = s2;
                        jal(ctx, 0x24BD40u, gen::fn_memcpy_00521250);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
                // 0x0024bd64
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0024bd74
            charge(ctx, 10);
            lw(v0, s0, brpres::kLoaded);
            v0 = v0 | 0x1;
            sw(v0, s0, brpres::kLoaded);
            lw(a0, s0, brpres::kArchiveReq);
            jal(ctx, 0x24BD84u, gen::fn_H_Cdvd_Destroy_00100ec0);
            lw(a0, s0, brpres::kLoading);
            v1 = si(-2);
            v1 = a0 & v1;
            sw(v1, s0, brpres::kLoading);
        }
    }
    // 0x0024bd9c
    charge(ctx, 4);
    lw(v1, s0, brpres::kLoading);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0024bdac
        charge(ctx, 5);
        lw(a0, s0, brpres::kMessageReq);
        jal(ctx, 0x24BDB0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        if (v0 != 0) {
            // 0x0024bdc0
            charge(ctx, 24);
            lw(v0, s0, brpres::kMessageReq);
            lw(a0, v0, 280);
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            jalr(ctx, 0x24BDD4u, v0.u());
            sw(v0, s0, brpres::kMessages);
            lw(v1, s0, brpres::kMessageReq);
            lw(a2, v1, 280);
            a0 = v0;
            lw(a1, v1, 272);
            jal(ctx, 0x24BDF0u, gen::fn_memcpy_00521250);
            lw(v0, s0, brpres::kLoaded);
            v0 = v0 | 0x2;
            sw(v0, s0, brpres::kLoaded);
            lw(a0, s0, brpres::kMessageReq);
            jal(ctx, 0x24BE08u, gen::fn_H_Cdvd_Destroy_00100ec0);
            lw(a0, s0, brpres::kLoading);
            v1 = si(-3);
            v1 = a0 & v1;
            sw(v1, s0, brpres::kLoading);
        }
    }
    // 0x0024be20 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0024BF80 sub_24BF80 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpResRequestMessages] Requests facility/msg/msg_combine.bmd for the persona birth (K_Assert lines 191 / 192: not
// loading, not loaded) through H_Cdvd_Request (kind 0) into +12; sets flag 2.
void sub_24BF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024bf80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    if (v0 == 0) {
        // 0x0024bf98
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5848);  // "brp_res.c"
        a1 = 57;
        jal(ctx, 0x24BFA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024bfac
    charge(ctx, 6);
    lw(s0, gp, kGpBrpRes);  // the persona birth resources (brp_res.c) 0x7CE334
    lw(v0, s0, brpres::kLoading);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0024bfc4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5848);  // "brp_res.c"
        a1 = 191;
        jal(ctx, 0x24BFD0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024bfd8
    charge(ctx, 5);
    lw(v0, s0, brpres::kLoaded);
    v0 = nor(v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0024bfec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5848);  // "brp_res.c"
        a1 = 192;
        jal(ctx, 0x24BFF8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024c000
    charge(ctx, 14);
    a0 = 0x690000;
    a0 = addiu(a0, -5792);  // "facility/msg/msg_combine.bmd"
    a1 = 0;
    jal(ctx, 0x24C00Cu, gen::fn_H_Cdvd_Request_00100d80);
    sw(v0, s0, brpres::kMessageReq);
    lw(v1, s0, brpres::kLoading);
    v1 = v1 | 0x2;
    sw(v1, s0, brpres::kLoading);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0025D8A0 sub_25D8A0 -- 320 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brItemOpen] Lays out the item stock-over panel (br_item.c, *$gp 0x7CE370; K_Assert line 117) for the texture set
// a0 (+8): the plates 52 / 53 / 54 / 58 into the quads +1040 / +1296 / +1552 / +1808 with alpha 30 / 30 / 30 / 50,
// three more alphas 50, starts the opening (brItemStartOpen) and sets flag 1.
// Arguments: a0 the texture set.
void sub_25D8A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0025d8a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    if (v0 == 0) {
        // 0x0025d8c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25D8CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d8d4
    charge(ctx, 67);
    lw(s0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    sw(s1, s0, britem::kTextures);
    a0 = addiu(s0, 1040);
    a1 = s1;
    a2 = 52;
    jal(ctx, 0x25D8E8u, gen::fn_sub_25F5D0_0025f5d0);
    a0 = 30;
    jal(ctx, 0x25D8F4u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1040);
    mov_s(f12, f0);
    jal(ctx, 0x25D904u, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s0, 1296);
    lw(a1, s0, britem::kTextures);
    a2 = 53;
    jal(ctx, 0x25D918u, gen::fn_sub_25F5D0_0025f5d0);
    a0 = 30;
    jal(ctx, 0x25D924u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1296);
    mov_s(f12, f0);
    jal(ctx, 0x25D934u, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s0, 1552);
    lw(a1, s0, britem::kTextures);
    a2 = 54;
    jal(ctx, 0x25D948u, gen::fn_sub_25F5D0_0025f5d0);
    a0 = 30;
    jal(ctx, 0x25D954u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1552);
    mov_s(f12, f0);
    jal(ctx, 0x25D964u, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s0, 1808);
    lw(a1, s0, britem::kTextures);
    a2 = 58;
    jal(ctx, 0x25D978u, gen::fn_sub_25F5D0_0025f5d0);
    a0 = 50;
    jal(ctx, 0x25D984u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 1808);
    mov_s(f12, f0);
    jal(ctx, 0x25D994u, gen::fn_sub_21EAC0_0021eac0);
    a0 = 50;
    jal(ctx, 0x25D9A0u, gen::fn_sub_21EA00_0021ea00);
    swc1(f0, s0, 2072);
    swc1(f0, s0, 2136);
    swc1(f0, s0, 2200);
    jal(ctx, 0x25D9B4u, gen::fn_sub_25D9E0_0025d9e0);
    lw(v1, s0, britem::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, britem::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0025D9E0 sub_25D9E0 -- 80 bytes; frame 0x10: ra sp+0x0
// [brItemStartOpen] Starts the item stock-over panel's opening (K_Assert line 117): frame +12 = 0, mode +4 = 0, flag
// 2.
void sub_25D9E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d9e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    if (v1 == 0) {
        // 0x0025d9f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25DA00u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025da08 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(a0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    sw(zero, a0, britem::kFrame);
    sw(zero, a0, britem::kMode);
    lw(v1, a0, britem::kFlags);
    v1 = v1 | 0x2;
    sw(v1, a0, britem::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025DA30 sub_25DA30 -- 4876 bytes; frame 0x80: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [brItemLayout] Lays out the item stock-over panel for the current frame (K_Assert line 117): advances the frame
// (+12) of the opening (mode 0, 10 frames, then flag 2 clears) or the closing (mode 1, 10 frames, then flag 1
// clears); each quad slides and fades over its own span (the plates over 3 / 5 / 6 frames, the band 544 px wide over
// 8 / 10) through sub_21D8E0 / sub_21D950 / sub_21D890, the panel's fixed corners (224, 352).
void sub_25DA30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0025da30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    if (v0 == 0) {
        // 0x0025da5c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25DA68u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025da70
    charge(ctx, 5);
    lw(s0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    lw(v1, s0, britem::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025dacc
        charge(ctx, 4);
        lw(v0, s0, britem::kFrame);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x0025daec
            charge(ctx, 7);
            lw(v1, s0, britem::kFlags);
            v0 = si(-3);
            v1 = v1 & v0;
            sw(v1, s0, britem::kFlags);
            v0 = si(-2);
            v0 = v1 & v0;
            sw(v0, s0, britem::kFlags);
        } else {
            // 0x0025dadc
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sw(v0, s0, britem::kFrame);
        }
    } else {
        // 0x0025da84
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025da94
            charge(ctx, 4);
            lw(v0, s0, britem::kFrame);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x0025dab4
                charge(ctx, 6);
                lw(v1, s0, britem::kFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, britem::kFlags);
            } else {
                // 0x0025daa4
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sw(v0, s0, britem::kFrame);
            }
        } else {
            // 0x0025da8c
            charge(ctx, 2);
        }
    }
    // 0x0025db08
    charge(ctx, 13);
    lw(a0, s0, britem::kTextures);
    a1 = 52;
    jal(ctx, 0x25DB10u, gen::fn_sub_260900_00260900);
    s1 = v0;
    lw(a0, s0, britem::kTextures);
    a1 = 52;
    jal(ctx, 0x25DB24u, gen::fn_sub_260920_00260920);
    lw(a0, s0, britem::kMode);
    v1 = 1;
    if (a0 == v1) {
        // 0x0025dbe4
        charge(ctx, 4);
        lw(v1, s0, britem::kFrame);
        at = slti(v1, 3);
        if (at == 0) {
            // 0x0025dc50
            charge(ctx, 4);
            v1 = 0x431C0000;
            sw(v1, sp, 0x50);
            sw(v1, sp, 0x54);
            mtc1(zero, f21);
        } else {
            // 0x0025dbf4
            charge(ctx, 23);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x40400000;
            mtc1(v1, f0);
            div_s(f2, f1, f0);
            v1 = 0x43160000;
            mtc1(v1, f0);
            mul_s(f1, f2, f0);
            v1 = 0x40C00000;
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x50);
            swc1(f0, sp, 0x54);
            v1 = 0x3F800000;
            mtc1(v1, f0);
            sub_s(f21, f0, f2);
        }
    } else {
        // 0x0025db3c
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x0025db4c
            charge(ctx, 6);
            v1 = 0x3F800000;
            mtc1(v1, f21);
            lw(v1, s0, britem::kFrame);
            at = slti(v1, 5);
            if (at == 0) {
                // 0x0025dbd0
                charge(ctx, 5);
                v1 = 0x40C00000;
                sw(v1, sp, 0x50);
                sw(v1, sp, 0x54);
            } else {
                // 0x0025db64
                charge(ctx, 27);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v1 = 0x40A00000;
                mtc1(v1, f0);
                div_s(f5, f1, f0);
                v1 = 0x40C00000;
                mtc1(v1, f4);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f4, f0);
                add_s(f3, f4, f0);
                sub_s(f2, f4, f0);
                sub_s(f0, f4, f3);
                mtc1(zero, f1);
                adda_s(f1, f3);
                madd_s(f0, f5, f0);
                swc1(f0, sp, 0x50);
                sub_s(f0, f4, f2);
                adda_s(f1, f2);
                madd_s(f0, f5, f0);
                swc1(f0, sp, 0x54);
            }
        } else {
            // 0x0025db44
            charge(ctx, 2);
        }
    }
    // 0x0025dc60
    charge(ctx, 26);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25DC88u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x7C);
    sb(v0, sp, 0x7D);
    sb(v0, sp, 0x7E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0025dce0
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0025dcc8
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0025dcf8
    charge(ctx, 19);
    sb(v1, sp, 0x7F);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25DD04u, gen::fn_sub_21D950_0021d950);
    lw(a0, s0, britem::kTextures);
    a1 = 53;
    jal(ctx, 0x25DD14u, gen::fn_sub_260900_00260900);
    s2 = v0;
    lw(a0, s0, britem::kTextures);
    a1 = 53;
    jal(ctx, 0x25DD28u, gen::fn_sub_260920_00260920);
    s1 = v0;
    lw(v1, s0, britem::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025de10
        charge(ctx, 4);
        lw(v0, s0, britem::kFrame);
        at = slti(v0, 3);
        if (at == 0) {
            // 0x0025de8c
            charge(ctx, 8);
            v0 = 0x432D0000;
            sw(v0, sp, 0x50);
            v0 = 259;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x54);
            mtc1(zero, f21);
        } else {
            // 0x0025de20
            charge(ctx, 27);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x43160000;
            mtc1(v0, f0);
            mul_s(f1, f2, f0);
            v0 = 0x41B80000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x50);
            v0 = 0x42DA0000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x54);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
        }
    } else {
        // 0x0025dd44
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025dd54
            charge(ctx, 6);
            v0 = 0x3F800000;
            mtc1(v0, f21);
            lw(v0, s0, britem::kFrame);
            at = slti(v0, 6);
            if (at == 0) {
                // 0x0025ddf8
                charge(ctx, 6);
                v0 = 0x41B80000;
                sw(v0, sp, 0x50);
                v0 = 0x42DA0000;
                sw(v0, sp, 0x54);
            } else {
                // 0x0025dd6c
                charge(ctx, 35);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                lw(a0, s0, britem::kTextures);
                a1 = 53;
                jal(ctx, 0x25DD94u, gen::fn_sub_260920_00260920);
                v1 = 0x42DA0000;
                mtc1(v1, f4);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f1, f4, f0);
                v0 = 0x41B80000;
                mtc1(v0, f0);
                add_s(f3, f0, f1);
                sub_s(f2, f4, f1);
                sub_s(f0, f0, f3);
                mtc1(zero, f1);
                adda_s(f1, f3);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x50);
                sub_s(f0, f4, f2);
                adda_s(f1, f2);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x54);
            }
        } else {
            // 0x0025dd4c
            charge(ctx, 2);
        }
    }
    // 0x0025deac
    charge(ctx, 26);
    mtc1(s2, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25DED4u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x7C);
    sb(v0, sp, 0x7D);
    sb(v0, sp, 0x7E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0025df2c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0025df14
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0025df44
    charge(ctx, 19);
    sb(v1, sp, 0x7F);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25DF50u, gen::fn_sub_21D950_0021d950);
    lw(a0, s0, britem::kTextures);
    a1 = 54;
    jal(ctx, 0x25DF60u, gen::fn_sub_260900_00260900);
    s2 = v0;
    lw(a0, s0, britem::kTextures);
    a1 = 54;
    jal(ctx, 0x25DF74u, gen::fn_sub_260920_00260920);
    s1 = v0;
    lw(v1, s0, britem::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025e068
        charge(ctx, 4);
        lw(v0, s0, britem::kFrame);
        at = slti(v0, 3);
        if (at == 0) {
            // 0x0025e0e4
            charge(ctx, 5);
            v0 = 0x43850000;
            sw(v0, sp, 0x50);
            v0 = 0x432C0000;
            sw(v0, sp, 0x54);
            mtc1(zero, f21);
        } else {
            // 0x0025e078
            charge(ctx, 27);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x40400000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x43160000;
            mtc1(v0, f0);
            mul_s(f1, f2, f0);
            v0 = 0x42E80000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x50);
            v0 = 0x41B00000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x54);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
        }
    } else {
        // 0x0025df90
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025dfa0
            charge(ctx, 6);
            v0 = 0x3F800000;
            mtc1(v0, f21);
            lw(v0, s0, britem::kFrame);
            at = slti(v0, 6);
            if (at == 0) {
                // 0x0025e050
                charge(ctx, 6);
                v0 = 0x42E80000;
                sw(v0, sp, 0x50);
                v0 = 0x41B00000;
                sw(v0, sp, 0x54);
            } else {
                // 0x0025dfb8
                charge(ctx, 38);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                lw(a0, s0, britem::kTextures);
                a1 = 53;
                jal(ctx, 0x25DFE0u, gen::fn_sub_260920_00260920);
                v1 = 0x42DA0000;
                mtc1(v1, f1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f1, f1, f0);
                v0 = 0x42E80000;
                mtc1(v0, f0);
                add_s(f4, f0, f1);
                v0 = 0x41B00000;
                mtc1(v0, f3);
                sub_s(f2, f3, f1);
                sub_s(f0, f0, f4);
                mtc1(zero, f1);
                adda_s(f1, f4);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x50);
                sub_s(f0, f3, f2);
                adda_s(f1, f2);
                madd_s(f0, f20, f0);
                swc1(f0, sp, 0x54);
            }
        } else {
            // 0x0025df98
            charge(ctx, 2);
        }
    }
    // 0x0025e0f8
    charge(ctx, 26);
    mtc1(s2, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    a0 = addiu(s0, 1552);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25E120u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x7C);
    sb(v0, sp, 0x7D);
    sb(v0, sp, 0x7E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0025e178
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0025e160
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0025e190
    charge(ctx, 9);
    sb(v1, sp, 0x7F);
    a0 = addiu(s0, 1552);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25E19Cu, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, britem::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025e314
        charge(ctx, 4);
        lw(v0, s0, britem::kFrame);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x0025e3ec
            charge(ctx, 35);
            v0 = 0x44880000;
            mtc1(v0, f0);
            div_s(f0, f0, f22);
            div_s(f4, f0, f22);
            v0 = 0x43A00000;
            mtc1(v0, f0);
            add_s(f3, f0, f4);
            swc1(f3, sp, 0x60);
            v0 = 0x44200000;
            mtc1(v0, f0);
            div_s(f0, f0, f22);
            neg_s(f0, f0);
            div_s(f0, f0, f22);
            add_s(f2, f4, f0);
            swc1(f2, sp, 0x64);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            div_s(f0, f0, f22);
            neg_s(f0, f0);
            div_s(f0, f0, f22);
            add_s(f1, f4, f0);
            swc1(f1, sp, 0x68);
            v0 = 0x43600000;
            mtc1(v0, f0);
            add_s(f0, f0, f4);
            swc1(f0, sp, 0x6C);
            swc1(f1, sp, 0x50);
            swc1(f0, sp, 0x54);
            swc1(f3, sp, 0x58);
            swc1(f2, sp, 0x5C);
        } else {
            // 0x0025e324
            charge(ctx, 50);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f7, f1, f0);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f8, f0);
            v0 = 0x44580000;
            mtc1(v0, f6);
            sw(v0, sp, 0x60);
            v0 = 0x43600000;
            mtc1(v0, f5);
            sw(v0, sp, 0x64);
            v0 = 0x43A00000;
            mtc1(v0, f4);
            sw(v0, sp, 0x68);
            v0 = 0x44400000;
            mtc1(v0, f3);
            sw(v0, sp, 0x6C);
            lwc1(f2, gp, -32000);  // 0x7CAFF0
            v0 = 0x43800000;
            mtc1(v0, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f0, f2, f8);
            div_s(f1, f0, f8);
            v0 = 0x44080000;
            mtc1(v0, f0);
            sub_s(f1, f0, f1);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f0, f0, f7);
            mul_s(f1, f0, f1);
            sub_s(f0, f4, f1);
            swc1(f0, sp, 0x50);
            sub_s(f0, f3, f1);
            swc1(f0, sp, 0x54);
            sub_s(f0, f6, f1);
            swc1(f0, sp, 0x58);
            sub_s(f0, f5, f1);
            swc1(f0, sp, 0x5C);
        }
    } else {
        // 0x0025e1b4
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025e1c4
            charge(ctx, 4);
            lw(v1, s0, britem::kFrame);
            at = slti(v1, 8);
            if (at == 0) {
                // 0x0025e28c
                charge(ctx, 34);
                v0 = 0x43A00000;
                mtc1(v0, f5);
                sw(v0, sp, 0x50);
                v0 = 0x44200000;
                mtc1(v0, f0);
                div_s(f0, f0, f22);
                neg_s(f0, f0);
                div_s(f4, f0, f22);
                swc1(f4, sp, 0x54);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                div_s(f0, f0, f22);
                neg_s(f0, f0);
                div_s(f3, f0, f22);
                swc1(f3, sp, 0x58);
                v0 = 0x43600000;
                mtc1(v0, f2);
                sw(v0, sp, 0x5C);
                v0 = 0x44880000;
                mtc1(v0, f0);
                div_s(f1, f0, f22);
                add_s(f0, f3, f1);
                swc1(f0, sp, 0x60);
                add_s(f0, f2, f1);
                swc1(f0, sp, 0x64);
                add_s(f0, f5, f1);
                swc1(f0, sp, 0x68);
                add_s(f0, f4, f1);
                swc1(f0, sp, 0x6C);
            } else {
                // 0x0025e1d4
                charge(ctx, 46);
                v0 = 0x40000000;
                mtc1(v0, f0);
                sqrt_s(f6, f0);
                v0 = 0x43A00000;
                mtc1(v0, f5);
                sw(v0, sp, 0x50);
                v0 = 0x44200000;
                mtc1(v0, f0);
                div_s(f0, f0, f6);
                neg_s(f0, f0);
                div_s(f4, f0, f6);
                swc1(f4, sp, 0x54);
                v0 = 0x43E00000;
                mtc1(v0, f0);
                div_s(f0, f0, f6);
                neg_s(f0, f0);
                div_s(f3, f0, f6);
                swc1(f3, sp, 0x58);
                v0 = 0x43600000;
                mtc1(v0, f2);
                sw(v0, sp, 0x5C);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41000000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x44880000;
                mtc1(v0, f0);
                mul_s(f0, f0, f1);
                div_s(f1, f0, f6);
                add_s(f0, f3, f1);
                swc1(f0, sp, 0x60);
                add_s(f0, f2, f1);
                swc1(f0, sp, 0x64);
                add_s(f0, f5, f1);
                swc1(f0, sp, 0x68);
                add_s(f0, f4, f1);
                swc1(f0, sp, 0x6C);
            }
        } else {
            // 0x0025e1bc
            charge(ctx, 2);
        }
    }
    // 0x0025e478
    charge(ctx, 23);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25E480u, gen::fn_sub_21D890_0021d890);
    a0 = 50;
    jal(ctx, 0x25E48Cu, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 16);
    mov_s(f12, f0);
    jal(ctx, 0x25E49Cu, gen::fn_sub_21EAC0_0021eac0);
    sb(zero, sp, 0x7C);
    sb(zero, sp, 0x7D);
    sb(zero, sp, 0x7E);
    sb(zero, sp, 0x7F);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25E4BCu, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, britem::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025e588
        charge(ctx, 9);
        v0 = 0x40000000;
        mtc1(v0, f0);
        sqrt_s(f7, f0);
        lw(v0, s0, britem::kFrame);
        at = slti(v0, 10);
        if (at == 0) {
            // 0x0025e6b8
            charge(ctx, 9);
            mtc1(zero, f21);
            sw(zero, sp, 0x50);
            sw(zero, sp, 0x54);
            sw(zero, sp, 0x58);
            sw(zero, sp, 0x5C);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x64);
            sw(zero, sp, 0x68);
            sw(zero, sp, 0x6C);
        } else {
            // 0x0025e5ac
            charge(ctx, 67);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f2, f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f21, f0, f2);
            v0 = 0x43800000;
            mtc1(v0, f0);
            div_s(f1, f0, f7);
            lwc1(f0, gp, -32000);  // 0x7CAFF0
            sub_s(f0, f1, f0);
            div_s(f1, f0, f7);
            v0 = 0x44080000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            mul_s(f2, f2, f0);
            v0 = 0x42200000;
            mtc1(v0, f6);
            div_s(f1, f6, f7);
            v0 = 0x43A00000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f5, f0, f2);
            swc1(f5, sp, 0x50);
            v0 = lui(0xC3A0);
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f4, f0, f2);
            swc1(f4, sp, 0x54);
            v0 = lui(0xC360);
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f3, f0, f2);
            swc1(f3, sp, 0x58);
            v0 = 0x43600000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            add_s(f2, f0, f2);
            swc1(f2, sp, 0x5C);
            v0 = 0x43580000;
            mtc1(v0, f0);
            div_s(f0, f0, f7);
            add_s(f0, f6, f0);
            div_s(f1, f0, f7);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x60);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x64);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x68);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x6C);
        }
    } else {
        // 0x0025e4d4
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025e4e4
            charge(ctx, 41);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f5);
            sw(v0, sp, 0x50);
            v0 = 0x44200000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            neg_s(f0, f0);
            div_s(f4, f0, f1);
            swc1(f4, sp, 0x54);
            v0 = 0x43E00000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            neg_s(f0, f0);
            div_s(f3, f0, f1);
            swc1(f3, sp, 0x58);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, sp, 0x5C);
            v0 = 0x43580000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            div_s(f1, f0, f1);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x60);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x64);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x68);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x6C);
            v0 = 0x3F800000;
            mtc1(v0, f21);
        } else {
            // 0x0025e4dc
            charge(ctx, 2);
        }
    }
    // 0x0025e6dc
    charge(ctx, 27);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25E6E4u, gen::fn_sub_21D890_0021d890);
    a0 = 35;
    jal(ctx, 0x25E6F0u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 272);
    mov_s(f12, f0);
    jal(ctx, 0x25E700u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 4;
    sb(v0, sp, 0x7C);
    v0 = 41;
    sb(v0, sp, 0x7D);
    v0 = 70;
    sb(v0, sp, 0x7E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0025e760
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0025e748
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0025e778
    charge(ctx, 9);
    sb(v1, sp, 0x7F);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25E784u, gen::fn_sub_21D950_0021d950);
    lw(v1, s0, britem::kMode);
    v0 = 1;
    if (v1 == v0) {
        // 0x0025e828
        charge(ctx, 59);
        lwc1(f0, s0, britem::kFrame);
        cvt_s_w(f1, f0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        div_s(f2, f1, f0);
        v0 = 0x40000000;
        mtc1(v0, f0);
        sqrt_s(f8, f0);
        v0 = 0x43800000;
        mtc1(v0, f0);
        div_s(f7, f0, f8);
        lwc1(f0, gp, -32000);  // 0x7CAFF0
        sub_s(f0, f7, f0);
        div_s(f1, f0, f8);
        v0 = 0x44080000;
        mtc1(v0, f0);
        sub_s(f0, f0, f1);
        mul_s(f6, f2, f0);
        v0 = 0x43A00000;
        mtc1(v0, f5);
        add_s(f0, f5, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x50);
        v0 = lui(0xC3A0);
        mtc1(v0, f4);
        add_s(f0, f4, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x54);
        v0 = lui(0xC360);
        mtc1(v0, f3);
        add_s(f0, f3, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x58);
        v0 = 0x43600000;
        mtc1(v0, f2);
        add_s(f0, f2, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x5C);
        div_s(f1, f7, f8);
        add_s(f0, f3, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x60);
        add_s(f0, f2, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x64);
        add_s(f0, f5, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x68);
        add_s(f0, f4, f1);
        add_s(f0, f0, f6);
        swc1(f0, sp, 0x6C);
    } else {
        // 0x0025e79c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0025e7ac
            charge(ctx, 31);
            v0 = 0x40000000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f5);
            sw(v0, sp, 0x50);
            v0 = lui(0xC3A0);
            mtc1(v0, f4);
            sw(v0, sp, 0x54);
            v0 = lui(0xC360);
            mtc1(v0, f3);
            sw(v0, sp, 0x58);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, sp, 0x5C);
            v0 = 0x43800000;
            mtc1(v0, f0);
            div_s(f0, f0, f1);
            div_s(f1, f0, f1);
            add_s(f0, f3, f1);
            swc1(f0, sp, 0x60);
            add_s(f0, f2, f1);
            swc1(f0, sp, 0x64);
            add_s(f0, f5, f1);
            swc1(f0, sp, 0x68);
            add_s(f0, f4, f1);
            swc1(f0, sp, 0x6C);
        } else {
            // 0x0025e7a4
            charge(ctx, 2);
        }
    }
    // 0x0025e914
    charge(ctx, 67);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25E91Cu, gen::fn_sub_21D890_0021d890);
    a0 = 35;
    jal(ctx, 0x25E928u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 528);
    mov_s(f12, f0);
    jal(ctx, 0x25E938u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 79;
    sb(v0, sp, 0x7C);
    v0 = 164;
    sb(v0, sp, 0x7D);
    v0 = 255;
    sb(v0, sp, 0x7E);
    sb(v0, sp, 0x7F);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25E964u, gen::fn_sub_21D950_0021d950);
    sw(zero, sp, 0x50);
    sw(zero, sp, 0x54);
    v0 = 0x44200000;
    sw(v0, sp, 0x58);
    v0 = 0x43E00000;
    sw(v0, sp, 0x5C);
    a0 = addiu(s0, 1808);
    a1 = addiu(sp, 0x50);
    jal(ctx, 0x25E98Cu, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x7C);
    sb(v0, sp, 0x7D);
    sb(v0, sp, 0x7E);
    sb(v0, sp, 0x7F);
    a0 = addiu(s0, 1808);
    a1 = addiu(sp, 0x7C);
    jal(ctx, 0x25E9B0u, gen::fn_sub_21D950_0021d950);
    v1 = 517;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s0, 2064);
    a1 = 0x43E00000;
    sw(a1, s0, 2068);
    a0 = 0x44200000;
    sw(a0, s0, 2128);
    v1 = 325;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s0, 2132);
    sw(a0, s0, 2192);
    sw(a1, s0, 2196);
    v1 = 79;
    sb(v1, sp, 0x7C);
    v1 = 164;
    sb(v1, sp, 0x7D);
    v1 = 255;
    sb(v1, sp, 0x7E);
    sb(v1, sp, 0x7F);
    lbu(v1, sp, 0x7C);
    if (i64(v1) < 0) {
        // 0x0025ea34
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025ea20
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ea50
    charge(ctx, 4);
    swc1(f0, s0, 2096);
    lbu(v1, sp, 0x7D);
    if (i64(v1) < 0) {
        // 0x0025ea74
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025ea60
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ea90
    charge(ctx, 4);
    swc1(f0, s0, 2100);
    lbu(v1, sp, 0x7E);
    if (i64(v1) < 0) {
        // 0x0025eab4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025eaa0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ead0
    charge(ctx, 4);
    swc1(f0, s0, 2104);
    lbu(v1, sp, 0x7F);
    if (i64(v1) < 0) {
        // 0x0025eaf4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025eae0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025eb10
    charge(ctx, 4);
    swc1(f0, s0, 2108);
    lbu(v1, sp, 0x7C);
    if (i64(v1) < 0) {
        // 0x0025eb34
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025eb20
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025eb50
    charge(ctx, 4);
    swc1(f0, s0, 2160);
    lbu(v1, sp, 0x7D);
    if (i64(v1) < 0) {
        // 0x0025eb74
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025eb60
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025eb90
    charge(ctx, 4);
    swc1(f0, s0, 2164);
    lbu(v1, sp, 0x7E);
    if (i64(v1) < 0) {
        // 0x0025ebb4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025eba0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ebd0
    charge(ctx, 4);
    swc1(f0, s0, 2168);
    lbu(v1, sp, 0x7F);
    if (i64(v1) < 0) {
        // 0x0025ebf4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025ebe0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ec10
    charge(ctx, 4);
    swc1(f0, s0, 2172);
    lbu(v1, sp, 0x7C);
    if (i64(v1) < 0) {
        // 0x0025ec34
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025ec20
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ec50
    charge(ctx, 4);
    swc1(f0, s0, 2224);
    lbu(v1, sp, 0x7D);
    if (i64(v1) < 0) {
        // 0x0025ec74
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025ec60
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ec90
    charge(ctx, 4);
    swc1(f0, s0, 2228);
    lbu(v1, sp, 0x7E);
    if (i64(v1) < 0) {
        // 0x0025ecb4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025eca0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ecd0
    charge(ctx, 4);
    swc1(f0, s0, 2232);
    lbu(v1, sp, 0x7F);
    if (i64(v1) < 0) {
        // 0x0025ecf4
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0025ece0
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0025ed10 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    swc1(f0, s0, 2236);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0025ED40 sub_25ED40 -- 1576 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brItemDraw] Draws the item stock-over panel (K_Assert line 117): the backdrop quads (+784, +16), the band (+1808,
// texture 58) and its shadow (+2064), the frame (+528), the window (+272, its blend by the mode) and the plates 52 /
// 53 / 54 (+1040 / +1296 / +1552) through the Im2D slot, with the render states between.
void sub_25ED40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025ed40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    if (v0 == 0) {
        // 0x0025ed60
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25ED6Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025ed74
    charge(ctx, 207);
    lw(s2, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 9;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25ED8Cu, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EDA0u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EDB4u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EDC8u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x25EDDCu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x25EDECu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EE00u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 784);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EE28u, v0.u());
    a0 = addiu(s2, 784);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EE48u, v0.u());
    a0 = 20;
    a1 = 2;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EE5Cu, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EE70u, v0.u());
    a0 = 6;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EE84u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x25EE98u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x25EEA8u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EEBCu, v0.u());
    a0 = addiu(s2, 16);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EEDCu, v0.u());
    a0 = addiu(s2, 16);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EEFCu, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EF10u, v0.u());
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EF24u, v0.u());
    lw(a0, s2, britem::kTextures);
    a1 = 58;
    jal(ctx, 0x25EF34u, gen::fn_sub_260940_00260940);
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EF48u, v0.u());
    a0 = addiu(s2, 1808);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EF68u, v0.u());
    a0 = addiu(s2, 1808);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EF88u, v0.u());
    a0 = 1;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EF9Cu, v0.u());
    a0 = addiu(s2, 2064);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25EFBCu, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EFD0u, v0.u());
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25EFE4u, v0.u());
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x25EFF8u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x25F008u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F01Cu, v0.u());
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F030u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F044u, v0.u());
    a0 = 1;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F058u, v0.u());
    a0 = addiu(s2, 528);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F078u, v0.u());
    a0 = addiu(s2, 528);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F098u, v0.u());
    lw(v0, s2, britem::kMode);
    a1 = 1;
    if (v0 == a1) {
        // 0x0025f14c
        charge(ctx, 34);
        s0 = s1;
        a0 = 6;
        a1 = 0;
        lw(v0, s0, 0);
        jalr(ctx, 0x25F15Cu, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s0, 0);
        jalr(ctx, 0x25F170u, v0.u());
        a0 = 1;
        a1 = 0;
        lw(v0, s0, 0);
        jalr(ctx, 0x25F184u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25F1ACu, v0.u());
        a0 = addiu(s2, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x25F1CCu, v0.u());
    } else {
        // 0x0025f0b0
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0025f0c0
            charge(ctx, 35);
            s0 = s1;
            a0 = 6;
            lw(v0, s0, 0);
            jalr(ctx, 0x25F0CCu, v0.u());
            a0 = 8;
            a1 = 1;
            lw(v0, s0, 0);
            jalr(ctx, 0x25F0E0u, v0.u());
            a0 = 1;
            a1 = 0;
            lw(v0, s0, 0);
            jalr(ctx, 0x25F0F4u, v0.u());
            s0 = 0x960000;
            s0 = addiu(s0, 156);  // &0x96009C
            a0 = addiu(s2, 272);
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s0, 0);  // 0x96009C
            jalr(ctx, 0x25F11Cu, v0.u());
            a0 = addiu(s2, 272);
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s0, 0);  // 0x96009C
            jalr(ctx, 0x25F13Cu, v0.u());
        } else {
            // 0x0025f0b8
            charge(ctx, 2);
        }
    }
    // 0x0025f1d4
    charge(ctx, 101);
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F1E8u, v0.u());
    a0 = 6;
    a1 = 1;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F1FCu, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F210u, v0.u());
    lw(a0, s2, britem::kTextures);
    a1 = 52;
    jal(ctx, 0x25F220u, gen::fn_sub_260940_00260940);
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F234u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 156);  // &0x96009C
    a0 = addiu(s2, 1040);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F25Cu, v0.u());
    a0 = addiu(s2, 1040);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F27Cu, v0.u());
    lw(a0, s2, britem::kTextures);
    a1 = 53;
    jal(ctx, 0x25F28Cu, gen::fn_sub_260940_00260940);
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F2A0u, v0.u());
    a0 = addiu(s2, 1296);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F2C0u, v0.u());
    a0 = addiu(s2, 1296);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F2E0u, v0.u());
    lw(a0, s2, britem::kTextures);
    a1 = 54;
    jal(ctx, 0x25F2F0u, gen::fn_sub_260940_00260940);
    a0 = 1;
    a1 = v0;
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x25F304u, v0.u());
    a0 = addiu(s2, 1552);
    a1 = 4;
    a2 = 0;
    a3 = 1;
    t0 = 2;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F324u, v0.u());
    a0 = addiu(s2, 1552);
    a1 = 4;
    a2 = 0;
    a3 = 2;
    t0 = 3;
    lw(v0, s0, 0);  // 0x96009C
    jalr(ctx, 0x25F344u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0025F4A0 brItem_UpdateStockOverBgTask -- 108 bytes; frame 0x10: ra sp+0x0
// [brItemTaskUpdate] Update callback of the 'stock over bg' task: lays out and draws the panel, returns 0 while it is
// open (flag 1) and -1 (the task ends) once it closed.
void brItem_UpdateStockOverBgTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025f4a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x25F4A8u, gen::fn_sub_25DA30_0025da30);
    jal(ctx, 0x25F4B0u, gen::fn_sub_25ED40_0025ed40);
    lw(v0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    if (v0 == 0) {
        // 0x0025f4c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25F4D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025f4d8
    charge(ctx, 5);
    lw(v0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    lw(v0, v0, britem::kFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0025f4f8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0025f4ec
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x0025f4fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025F510 sub_25F510 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brItemTaskDestroy] Destroy callback of the 'stock over bg' task: clears the $gp slots 0x7CE370 / 0x7CE374 and
// frees the task's work (a0 +60) through the RwFree slot (K_Assert line 117).
// Arguments: a0 the task.
void sub_25F510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025f510
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, ktask::kWork);
    lw(v0, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    if (v0 == 0) {
        // 0x0025f52c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25F538u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025f540
    charge(ctx, 12);
    sw(zero, gp, kGpBrItem);  // the item stock-over panel (br_item.c) 0x7CE370
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x25F550u, v0.u());
    sw(zero, gp, kGpBrItemTask);  // the stock-over panel's task 0x7CE374
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00262790 sub_262790 -- 2376 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brHeroOpen] Opens the result screen's hero panel (br_hero.c, *$gp 0x7CE37C; K_Assert lines 83 / 137..139): the
// hero's level (sub_16C7E0), the experience to the next level (sub_16D2F0, capped at 99,999), HP / max HP / SP / max
// SP (sub_16C4F0..sub_16C670), the Academics / Charm / Courage ranks (datGet*Level - 1) and sub_16C920; flag 2 when
// the level went up; then the panel's quads (textures 22..29 and the rank plates rank / rank + 7 / rank + 14), the
// numbers (bpIfontDrawNumber), the HP / SP bars scaled by value / max, the level-up plates (6..10, flag 2), the name
// line (frFontBuildGlyphList with the glyph x scale 120), the experience plates and number; frame +14688 = 0, flag 1.
void sub_262790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00262790
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrHero);  // the result screen hero panel (br_hero.c) 0x7CE37C
    if (v0 == 0) {
        // 0x002627b8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 83;
        jal(ctx, 0x2627C4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002627cc
    charge(ctx, 83);
    lw(s3, gp, kGpBrHero);  // the result screen hero panel (br_hero.c) 0x7CE37C
    a0 = 0;
    jal(ctx, 0x2627D4u, gen::fn_sub_233D70_00233d70);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x2627E4u, gen::fn_sub_233D70_00233d70);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x2627F4u, gen::fn_sub_16C470_0016c470);
    s4 = v0 & 0xFF;
    a0 = 1;
    jal(ctx, 0x262804u, gen::fn_sub_16C7E0_0016c7e0);
    a0 = 1;
    jal(ctx, 0x262810u, gen::fn_sub_16C970_0016c970);
    s2 = v0;
    sw(s4, s3, brhero::kLevel);
    a0 = 1;
    jal(ctx, 0x262824u, gen::fn_sub_16D2F0_0016d2f0);
    sw(v0, s3, brhero::kNextExp);
    a0 = 1;
    jal(ctx, 0x262834u, gen::fn_sub_16C4F0_0016c4f0);
    v0 = v0 & 0xFFFF;
    sw(v0, s3, brhero::kHp);
    a0 = 1;
    jal(ctx, 0x262848u, gen::fn_sub_16C570_0016c570);
    v0 = v0 & 0xFFFF;
    sw(v0, s3, brhero::kSp);
    a0 = 1;
    jal(ctx, 0x26285Cu, gen::fn_sub_16C5F0_0016c5f0);
    v0 = v0 & 0xFFFF;
    sw(v0, s3, brhero::kMaxHp);
    a0 = 1;
    jal(ctx, 0x262870u, gen::fn_sub_16C670_0016c670);
    v0 = v0 & 0xFFFF;
    sw(v0, s3, brhero::kMaxSp);
    a0 = 1;
    jal(ctx, 0x262884u, gen::fn_sub_16C6F0_0016c6f0);
    a0 = v0;
    jal(ctx, 0x262890u, gen::fn_datGetAcademicLevel_00177280);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = addiu(v0, -1);
    sw(v0, s3, brhero::kAcademics);
    a0 = 1;
    jal(ctx, 0x2628ACu, gen::fn_sub_16C740_0016c740);
    a0 = v0;
    jal(ctx, 0x2628B8u, gen::fn_datGetCharmLevel_001772f0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = addiu(v0, -1);
    sw(v0, s3, brhero::kCharm);
    a0 = 1;
    jal(ctx, 0x2628D4u, gen::fn_sub_16C790_0016c790);
    a0 = v0;
    jal(ctx, 0x2628E0u, gen::fn_datGetCourageLevel_00177360);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = addiu(v0, -1);
    sw(v0, s3, brhero::kCourage);
    a0 = 1;
    jal(ctx, 0x2628FCu, gen::fn_sub_16C920_0016c920);
    v0 = v0 & 0xFFFF;
    sw(v0, s3, brhero::kWord5684);
    lw(v0, s3, brhero::kAcademics);
    if (i64(v0) < 0) {
        // 0x00262918
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 137;
        jal(ctx, 0x262924u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0026292c
    charge(ctx, 3);
    lw(v0, s3, brhero::kCharm);
    if (i64(v0) < 0) {
        // 0x00262938
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 138;
        jal(ctx, 0x262944u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0026294c
    charge(ctx, 3);
    lw(v0, s3, brhero::kCourage);
    if (i64(v0) < 0) {
        // 0x00262958
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 139;
        jal(ctx, 0x262964u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0026296c
    charge(ctx, 7);
    lw(v1, s3, brhero::kFlags);
    v0 = si(-3);
    v0 = v1 & v0;
    sw(v0, s3, brhero::kFlags);
    v0 = s2 & 0x80;
    if (v0 != 0) {
        // 0x00262988
        charge(ctx, 3);
        lw(v0, s3, brhero::kFlags);
        v0 = v0 | 0x2;
        sw(v0, s3, brhero::kFlags);
    }
    // 0x00262994
    charge(ctx, 6);
    lw(v0, s3, brhero::kNextExp);
    at = 0x10000;
    at = at | 0x86A0;
    at = slt(v0, at);
    if (at == 0) {
        // 0x002629ac
        charge(ctx, 3);
        v0 = 0x10000;
        v0 = v0 | 0x869F;
        sw(v0, s3, brhero::kNextExp);
    }
    // 0x002629b8
    charge(ctx, 51);
    a0 = s1;
    a1 = 22;
    jal(ctx, 0x2629C0u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 16);
    a1 = v0;
    jal(ctx, 0x2629D0u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 23;
    jal(ctx, 0x2629E0u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 272);
    a1 = v0;
    jal(ctx, 0x2629F0u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 24;
    jal(ctx, 0x262A00u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 528);
    a1 = v0;
    jal(ctx, 0x262A10u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 25;
    jal(ctx, 0x262A20u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 784);
    a1 = v0;
    jal(ctx, 0x262A30u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 26;
    jal(ctx, 0x262A40u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 1040);
    a1 = v0;
    jal(ctx, 0x262A50u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 27;
    jal(ctx, 0x262A60u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 1296);
    a1 = v0;
    jal(ctx, 0x262A70u, gen::fn_sub_21D3B0_0021d3b0);
    s2 = 0;
    for (;;) {
        // 0x00262aa0
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00262a84
        charge(ctx, 7);
        v0 = sll(s2, 8);
        v0 = addu(s3, v0);
        mtc1(zero, f12);
        a0 = addiu(v0, 1552);
        jal(ctx, 0x262A94u, gen::fn_sub_21EAC0_0021eac0);
        s2 = addiu(s2, 1);
    }
    // 0x00262aac
    charge(ctx, 8);
    a0 = s1;
    a1 = 28;
    jal(ctx, 0x262AB4u, gen::fn_sub_21CCA0_0021cca0);
    s4 = v0;
    s2 = 0;
    for (;;) {
        // 0x00262ae8
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00262acc
        charge(ctx, 7);
        v0 = sll(s2, 8);
        v0 = addu(s3, v0);
        a0 = addiu(v0, 2320);
        a1 = s4;
        jal(ctx, 0x262ADCu, gen::fn_sub_21D3B0_0021d3b0);
        s2 = addiu(s2, 1);
    }
    // 0x00262af4
    charge(ctx, 8);
    a0 = s1;
    a1 = 29;
    jal(ctx, 0x262AFCu, gen::fn_sub_21CCA0_0021cca0);
    s4 = v0;
    s2 = 0;
    for (;;) {
        // 0x00262b30
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00262b14
        charge(ctx, 7);
        v0 = sll(s2, 8);
        v0 = addu(s3, v0);
        a0 = addiu(v0, 3088);
        a1 = s4;
        jal(ctx, 0x262B24u, gen::fn_sub_21D3B0_0021d3b0);
        s2 = addiu(s2, 1);
    }
    // 0x00262b3c
    charge(ctx, 39);
    a0 = s1;
    lw(a1, s3, brhero::kAcademics);
    jal(ctx, 0x262B44u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 3856);
    a1 = v0;
    jal(ctx, 0x262B54u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s3, brhero::kCharm);
    a1 = addiu(v0, 7);
    a0 = s1;
    jal(ctx, 0x262B68u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 4112);
    a1 = v0;
    jal(ctx, 0x262B78u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s3, brhero::kCourage);
    a1 = addiu(v0, 14);
    a0 = s1;
    jal(ctx, 0x262B8Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 4368);
    a1 = v0;
    jal(ctx, 0x262B9Cu, gen::fn_sub_21D3B0_0021d3b0);
    sw(zero, sp, 0x70);
    sw(zero, sp, 0x74);
    v0 = 0x3F800000;
    sw(v0, sp, 0x78);
    sw(v0, sp, 0x7C);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    sb(v0, sp, 0x8F);
    s1 = 0;
    for (;;) {
        // 0x00262c18
        charge(ctx, 3);
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00262bd8
        charge(ctx, 16);
        v0 = sll(s1, 8);
        v0 = addu(s3, v0);
        s2 = addiu(v0, 4896);
        a0 = s2;
        a1 = addiu(sp, 0x70);
        jal(ctx, 0x262BECu, gen::fn_sub_21EB80_0021eb80);
        mtc1(zero, f12);
        a0 = s2;
        jal(ctx, 0x262BFCu, gen::fn_sub_21EAC0_0021eac0);
        a0 = s2;
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x262C0Cu, gen::fn_sub_21D950_0021d950);
        s1 = addiu(s1, 1);
    }
    // 0x00262c24
    charge(ctx, 171);
    sw(zero, sp, 0x70);
    sw(zero, sp, 0x74);
    v0 = 0x3F800000;
    sw(v0, sp, 0x78);
    sw(v0, sp, 0x7C);
    a0 = addiu(s3, 4640);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x262C40u, gen::fn_sub_21EB80_0021eb80);
    mtc1(zero, f12);
    a0 = addiu(s3, 4640);
    jal(ctx, 0x262C50u, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s3, 4640);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x262C60u, gen::fn_sub_21D950_0021d950);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x262C70u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 5408);
    a1 = v0;
    jal(ctx, 0x262C80u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s3, 5712);
    a1 = 2;
    lw(a2, s3, brhero::kLevel);
    a3 = a1;
    jal(ctx, 0x262C98u, gen::fn_bpIfontDrawNumber_00238980);
    a0 = addiu(s3, 6224);
    a1 = 3;
    lw(a2, s3, brhero::kHp);
    a3 = 2;
    jal(ctx, 0x262CB0u, gen::fn_bpIfontDrawNumber_00238980);
    a0 = addiu(s3, 6992);
    a1 = 3;
    lw(a2, s3, brhero::kMaxHp);
    a3 = 2;
    jal(ctx, 0x262CC8u, gen::fn_bpIfontDrawNumber_00238980);
    a0 = s0;
    a1 = 4;
    jal(ctx, 0x262CD8u, gen::fn_sub_21CCA0_0021cca0);
    a0 = v0;
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x262CE8u, gen::fn_sub_21CD00_0021cd00);
    lwc1(f2, sp, 0x60);
    swc1(f2, sp, 0x70);
    lwc1(f0, sp, 0x64);
    swc1(f0, sp, 0x74);
    lwc1(f0, s3, brhero::kHp);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x68);
    sub_s(f0, f0, f2);
    mul_s(f1, f1, f0);
    lwc1(f0, s3, brhero::kMaxHp);
    cvt_s_w(f0, f0);
    div_s(f0, f1, f0);
    add_s(f0, f2, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, sp, 0x6C);
    swc1(f0, sp, 0x7C);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    sb(v0, sp, 0x8F);
    mtc1(zero, f12);
    a0 = addiu(s3, 7760);
    jal(ctx, 0x262D4Cu, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s3, 7760);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x262D5Cu, gen::fn_sub_21EAE0_0021eae0);
    a0 = addiu(s3, 7760);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x262D6Cu, gen::fn_sub_21D950_0021d950);
    a0 = addiu(s3, 8016);
    a1 = 3;
    lw(a2, s3, brhero::kSp);
    a3 = 2;
    jal(ctx, 0x262D84u, gen::fn_bpIfontDrawNumber_00238980);
    a0 = addiu(s3, 8784);
    a1 = 3;
    lw(a2, s3, brhero::kMaxSp);
    a3 = 2;
    jal(ctx, 0x262D9Cu, gen::fn_bpIfontDrawNumber_00238980);
    a0 = s0;
    a1 = 5;
    jal(ctx, 0x262DACu, gen::fn_sub_21CCA0_0021cca0);
    a0 = v0;
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x262DBCu, gen::fn_sub_21CD00_0021cd00);
    lwc1(f2, sp, 0x60);
    swc1(f2, sp, 0x70);
    lwc1(f0, sp, 0x64);
    swc1(f0, sp, 0x74);
    lwc1(f0, s3, brhero::kSp);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x68);
    sub_s(f0, f0, f2);
    mul_s(f1, f1, f0);
    lwc1(f0, s3, brhero::kMaxSp);
    cvt_s_w(f0, f0);
    div_s(f0, f1, f0);
    add_s(f0, f2, f0);
    swc1(f0, sp, 0x78);
    lwc1(f0, sp, 0x6C);
    swc1(f0, sp, 0x7C);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    sb(v0, sp, 0x8F);
    mtc1(zero, f12);
    a0 = addiu(s3, 9552);
    jal(ctx, 0x262E20u, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s3, 9552);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x262E30u, gen::fn_sub_21EAE0_0021eae0);
    a0 = addiu(s3, 9552);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x262E40u, gen::fn_sub_21D950_0021d950);
    sw(zero, sp, 0x70);
    sw(zero, sp, 0x74);
    v0 = 0x3F800000;
    sw(v0, sp, 0x78);
    sw(v0, sp, 0x7C);
    v0 = 255;
    sb(v0, sp, 0x8C);
    sb(v0, sp, 0x8D);
    sb(v0, sp, 0x8E);
    sb(v0, sp, 0x8F);
    a0 = addiu(s3, 10576);
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x262E78u, gen::fn_sub_21EB80_0021eb80);
    mtc1(zero, f12);
    a0 = addiu(s3, 10576);
    jal(ctx, 0x262E88u, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s3, 10576);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x262E98u, gen::fn_sub_21D950_0021d950);
    lw(a0, s3, brhero::kWord5684);
    jal(ctx, 0x262EA4u, gen::fn_sub_264CA0_00264ca0);
    s2 = v0;
    a0 = addiu(s3, 10832);
    a1 = s2;
    jal(ctx, 0x262EB8u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s3, brhero::kFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00262ed0
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00262fc0
            charge(ctx, 3);
            v0 = slti(s1, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00262edc
            charge(ctx, 3);
            at = sltiu(s1, 6);
            if (at != 0) {
                // 0x00262ee8
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 31120);  // &0x7B7990
                v0 = sll(s1, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x262F04u:  // table[0]: plate 0: texture 6
                    // 0x00262f04
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = 6;
                    jal(ctx, 0x262F0Cu, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    break;
                case 0x262F20u:  // table[1]: plate 1: texture 7
                    // 0x00262f20
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = 7;
                    jal(ctx, 0x262F28u, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    break;
                case 0x262F3Cu:  // table[2]: plate 2: texture 8
                    // 0x00262f3c
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = 8;
                    jal(ctx, 0x262F44u, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    break;
                case 0x262F58u:  // table[3]: plate 3: texture 10
                    // 0x00262f58
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = 10;
                    jal(ctx, 0x262F60u, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    break;
                case 0x262F74u:  // table[4]: plate 4: texture 9
                    // 0x00262f74
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = 9;
                    jal(ctx, 0x262F7Cu, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    break;
                case 0x262F90u:  // table[5]: plate 5: texture 9
                    // 0x00262f90
                    charge(ctx, 5);
                    a0 = s0;
                    a1 = 9;
                    jal(ctx, 0x262F98u, gen::fn_sub_21CCA0_0021cca0);
                    s2 = v0;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x00262fa4
            charge(ctx, 7);
            v0 = sll(s1, 8);
            v0 = addu(s3, v0);
            a0 = addiu(v0, 11104);
            a1 = s2;
            jal(ctx, 0x262FB4u, gen::fn_sub_21D3B0_0021d3b0);
            s1 = addiu(s1, 1);
        }
    }
    // 0x00262fcc
    charge(ctx, 67);
    a0 = 1;
    jal(ctx, 0x262FD0u, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    a0 = 2;
    jal(ctx, 0x262FDCu, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    v0 = 120;
    sw(v0, gp, kGpGlyphScaleX);  // the glyph x scale / 128 of frFontBuildGlyphList (font2.h kGpScaleX; <= 0 off) 0x7CE638
    a0 = 1;
    jal(ctx, 0x262FF0u, gen::fn_sub_177790_00177790);
    a0 = v0;
    a1 = 1;
    a2 = 5;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x26300Cu, gen::fn_frFontBuildGlyphList_003b0970);
    sw(zero, gp, kGpGlyphScaleX);  // the glyph x scale / 128 of frFontBuildGlyphList (font2.h kGpScaleX; <= 0 off) 0x7CE638
    sw(v0, s3, brhero::kNameLine);
    a0 = 1;
    jal(ctx, 0x263020u, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    a0 = 2;
    jal(ctx, 0x26302Cu, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    a0 = s0;
    a1 = 17;
    jal(ctx, 0x26303Cu, gen::fn_sub_21CCA0_0021cca0);
    s1 = v0;
    a0 = addiu(s3, 12640);
    a1 = s1;
    jal(ctx, 0x263050u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s3, 12896);
    a1 = s1;
    a2 = 1;
    jal(ctx, 0x263064u, gen::fn_sub_21E380_0021e380);
    a0 = s0;
    a1 = 34;
    jal(ctx, 0x263074u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s3, 13152);
    a1 = v0;
    jal(ctx, 0x263084u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s3, 13408);
    a1 = 5;
    lw(a2, s3, brhero::kNextExp);
    a3 = 2;
    jal(ctx, 0x26309Cu, gen::fn_bpIfontDrawNumber_00238980);
    sw(zero, s3, brhero::kFrame);
    lw(v1, s3, brhero::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s3, brhero::kFlags);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00263170 sub_263170 -- 3128 bytes; frame 0x90: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [brHeroLayout] Places the result screen's hero panel for the current frame (K_Assert line 83) while open: the frame
// counter cycles 0..1050 (+14688); every quad's position from its texture cell (sub_21D8E0, the slide-in offsets
// 0x7CB098 / 0x7CB09C), the numbers (sub_238DC0 / sub_238BF0), the name line at (155, 206) with colour 0xFFFFFFCD.
void sub_263170(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00263170
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, gp, kGpBrHero);  // the result screen hero panel (br_hero.c) 0x7CE37C
    if (v1 == 0) {
        // 0x0026319c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 83;
        jal(ctx, 0x2631A8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002631b0
    charge(ctx, 6);
    lw(s1, gp, kGpBrHero);  // the result screen hero panel (br_hero.c) 0x7CE37C
    lw(v1, s1, brhero::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x002631c8
        charge(ctx, 4);
        lw(v0, s1, brhero::kFrame);
        at = slti(v0, 1050);
        if (at == 0) {
            // 0x002631e8
            charge(ctx, 1);
            sw(zero, s1, brhero::kFrame);
        } else {
            // 0x002631d8
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sw(v0, s1, brhero::kFrame);
        }
        // 0x002631ec
        charge(ctx, 498);
        a0 = 0;
        jal(ctx, 0x2631F0u, gen::fn_sub_233D70_00233d70);
        s0 = v0;
        a0 = 1;
        jal(ctx, 0x263200u, gen::fn_sub_233D70_00233d70);
        s2 = v0;
        a0 = s0;
        a1 = 22;
        jal(ctx, 0x263214u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x41A80000;
        sw(v1, sp, 0x60);
        v1 = 0x42440000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 16);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x26324Cu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 23;
        jal(ctx, 0x26325Cu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x41A80000;
        sw(v1, sp, 0x60);
        v1 = 0x42C20000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 272);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263294u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 24;
        jal(ctx, 0x2632A4u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x41A80000;
        sw(v1, sp, 0x60);
        v1 = 0x43130000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 528);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2632DCu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 25;
        jal(ctx, 0x2632ECu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42FE0000;
        sw(v1, sp, 0x60);
        v1 = 0x42440000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 784);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263324u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 26;
        jal(ctx, 0x263334u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42FE0000;
        sw(v1, sp, 0x60);
        v1 = 0x42C20000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 1040);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x26336Cu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 27;
        jal(ctx, 0x26337Cu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42FE0000;
        sw(v1, sp, 0x60);
        v1 = 0x43130000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 1296);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2633B4u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 28;
        jal(ctx, 0x2633C4u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42FE0000;
        sw(v1, sp, 0x60);
        v1 = 0x427C0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 2320);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2633FCu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 28;
        jal(ctx, 0x26340Cu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42FE0000;
        sw(v1, sp, 0x60);
        v1 = 0x42DE0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 2576);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263444u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 28;
        jal(ctx, 0x263454u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42FE0000;
        sw(v1, sp, 0x60);
        v1 = 0x43210000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 2832);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x26348Cu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 29;
        jal(ctx, 0x26349Cu, gen::fn_sub_21CCA0_0021cca0);
        lwc1(f0, s1, brhero::kAcademics);
        cvt_s_w(f3, f0);
        v1 = 0x41A00000;
        mtc1(v1, f2);
        v1 = 0x42FE0000;
        mtc1(v1, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f0, f2, f3);
        swc1(f0, sp, 0x60);
        v1 = 0x427C0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 3088);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2634F8u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 29;
        jal(ctx, 0x263508u, gen::fn_sub_21CCA0_0021cca0);
        lwc1(f0, s1, brhero::kCharm);
        cvt_s_w(f3, f0);
        v1 = 0x41A00000;
        mtc1(v1, f2);
        v1 = 0x42FE0000;
        mtc1(v1, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f0, f2, f3);
        swc1(f0, sp, 0x60);
        v1 = 0x42DE0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 3344);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263564u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s0;
        a1 = 29;
        jal(ctx, 0x263574u, gen::fn_sub_21CCA0_0021cca0);
        lwc1(f0, s1, brhero::kCourage);
        cvt_s_w(f3, f0);
        v1 = 0x41A00000;
        mtc1(v1, f2);
        v1 = 0x42FE0000;
        mtc1(v1, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f0, f2, f3);
        swc1(f0, sp, 0x60);
        v1 = 0x43210000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 3600);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2635D0u, gen::fn_sub_21D8E0_0021d8e0);
        sw(zero, sp, 0x60);
        sw(zero, sp, 0x64);
        v0 = 0x44200000;
        sw(v0, sp, 0x68);
        v0 = 0x42140000;
        sw(v0, sp, 0x6C);
        a0 = addiu(s1, 1552);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2635F8u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 254;
        sb(v0, sp, 0x8C);
        v0 = 189;
        sb(v0, sp, 0x8D);
        v0 = 94;
        sb(v0, sp, 0x8E);
        v0 = 255;
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 1552);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x263628u, gen::fn_sub_21D950_0021d950);
        sw(zero, sp, 0x60);
        v0 = 0x42140000;
        sw(v0, sp, 0x64);
        v0 = 0x44200000;
        sw(v0, sp, 0x68);
        v0 = 0x43210000;
        sw(v0, sp, 0x6C);
        a0 = addiu(s1, 1808);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263654u, gen::fn_sub_21D8E0_0021d8e0);
        sb(zero, sp, 0x8C);
        v0 = 40;
        sb(v0, sp, 0x8D);
        v0 = 63;
        sb(v0, sp, 0x8E);
        v0 = 255;
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 1808);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x263680u, gen::fn_sub_21D950_0021d950);
        sw(zero, sp, 0x60);
        v0 = 0x43460000;
        sw(v0, sp, 0x64);
        v0 = 0x44200000;
        sw(v0, sp, 0x68);
        v0 = 0x43E00000;
        sw(v0, sp, 0x6C);
        a0 = addiu(s1, 2064);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2636ACu, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 13;
        sb(v0, sp, 0x8C);
        v0 = 138;
        sb(v0, sp, 0x8D);
        v0 = 235;
        sb(v0, sp, 0x8E);
        v0 = 255;
        sb(v0, sp, 0x8F);
        a0 = addiu(s1, 2064);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x2636DCu, gen::fn_sub_21D950_0021d950);
        a0 = s0;
        lw(a1, s1, brhero::kAcademics);
        jal(ctx, 0x2636ECu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x43010000;
        sw(v1, sp, 0x60);
        v1 = 0x42900000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 3856);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263724u, gen::fn_sub_21D8E0_0021d8e0);
        lw(v0, s1, brhero::kCharm);
        a1 = addiu(v0, 7);
        a0 = s0;
        jal(ctx, 0x263738u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x43010000;
        sw(v1, sp, 0x60);
        v1 = 0x42F00000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 4112);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263770u, gen::fn_sub_21D8E0_0021d8e0);
        lw(v0, s1, brhero::kCourage);
        a1 = addiu(v0, 14);
        a0 = s0;
        jal(ctx, 0x263784u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x43010000;
        sw(v1, sp, 0x60);
        v1 = 0x432A0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 4368);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2637BCu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = 1;
        jal(ctx, 0x2637C8u, gen::fn_sub_233DF0_00233df0);
        lw(v1, v0, 12);
        s0 = sll(v1, 2);
        v0 = 0x41F00000;
        mtc1(v0, f1);
        mtc1(s0, f0);
        cvt_s_w(f2, f0);
        add_s(f20, f1, f2);
        lwc1(f0, s1, brhero::kFrame);
        cvt_s_w(f1, f0);
        v0 = 1050;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        neg_s(f0, f20);
        mul_s(f21, f1, f0);
        v0 = 0x433E0000;
        sw(v0, sp, 0x60);
        swc1(f21, sp, 0x64);
        s3 = sll(v1, 1);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        swc1(f2, sp, 0x6C);
        a0 = addiu(s1, 4896);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263840u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 0x433E0000;
        sw(v0, sp, 0x60);
        add_s(f0, f21, f20);
        swc1(f0, sp, 0x64);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 5152);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263880u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 449;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x60);
        v0 = 0x41E80000;
        sw(v0, sp, 0x64);
        lwc1(f0, gp, -31832);  // 0x7CB098
        swc1(f0, sp, 0x68);
        lwc1(f0, gp, -31828);  // 0x7CB09C
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 4640);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x2638BCu, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x2638CCu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x42500000;
        sw(v1, sp, 0x60);
        v1 = 0x434E0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 5408);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263904u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 0x42EC0000;
        sw(v0, sp, 0x60);
        v0 = 0x435A0000;
        sw(v0, sp, 0x64);
        a0 = addiu(s1, 5712);
        a1 = 2;
        lw(a2, s1, brhero::kLevel);
        a3 = a1;
        t0 = addiu(sp, 0x60);
        jal(ctx, 0x263930u, gen::fn_sub_238DC0_00238dc0);
        v0 = 0x42DA0000;
        sw(v0, sp, 0x60);
        v0 = 0x436C0000;
        sw(v0, sp, 0x64);
        a0 = addiu(s1, 6224);
        a1 = 3;
        lw(a2, s1, brhero::kHp);
        a3 = 2;
        t0 = addiu(sp, 0x60);
        jal(ctx, 0x26395Cu, gen::fn_sub_238BF0_00238bf0);
        v0 = 0x43280000;
        sw(v0, sp, 0x60);
        v0 = 0x436C0000;
        sw(v0, sp, 0x64);
        a0 = addiu(s1, 6992);
        a1 = 3;
        lw(a2, s1, brhero::kMaxHp);
        a3 = 2;
        t0 = addiu(sp, 0x60);
        jal(ctx, 0x263988u, gen::fn_sub_238BF0_00238bf0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        v0 = 153;
        sb(v0, sp, 0x8F);
        s0 = 0;
        for (;;) {
            // 0x002639d0
            charge(ctx, 3);
            v0 = slti(s0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002639b4
            charge(ctx, 7);
            v0 = sll(s0, 8);
            v0 = addu(s1, v0);
            a0 = addiu(v0, 6992);
            a1 = addiu(sp, 0x8C);
            jal(ctx, 0x2639C4u, gen::fn_sub_21D950_0021d950);
            s0 = addiu(s0, 1);
        }
        // 0x002639dc
        charge(ctx, 59);
        a0 = s2;
        a1 = 4;
        jal(ctx, 0x2639E4u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x43600000;
        sw(v1, sp, 0x60);
        v1 = 0x436E0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f1, f0);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        lwc1(f0, s1, brhero::kHp);
        cvt_s_w(f0, f0);
        mul_s(f1, f1, f0);
        lwc1(f0, s1, brhero::kMaxHp);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 7760);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263A44u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 0x42DA0000;
        sw(v0, sp, 0x60);
        v0 = 0x437C0000;
        sw(v0, sp, 0x64);
        a0 = addiu(s1, 8016);
        a1 = 3;
        lw(a2, s1, brhero::kSp);
        a3 = 2;
        t0 = addiu(sp, 0x60);
        jal(ctx, 0x263A70u, gen::fn_sub_238BF0_00238bf0);
        v0 = 0x43280000;
        sw(v0, sp, 0x60);
        v0 = 0x437C0000;
        sw(v0, sp, 0x64);
        a0 = addiu(s1, 8784);
        a1 = 3;
        lw(a2, s1, brhero::kMaxSp);
        a3 = 2;
        t0 = addiu(sp, 0x60);
        jal(ctx, 0x263A9Cu, gen::fn_sub_238BF0_00238bf0);
        v0 = 255;
        sb(v0, sp, 0x8C);
        sb(v0, sp, 0x8D);
        sb(v0, sp, 0x8E);
        v0 = 153;
        sb(v0, sp, 0x8F);
        s0 = 0;
        for (;;) {
            // 0x00263ae4
            charge(ctx, 3);
            v0 = slti(s0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00263ac8
            charge(ctx, 7);
            v0 = sll(s0, 8);
            v0 = addu(s1, v0);
            a0 = addiu(v0, 8784);
            a1 = addiu(sp, 0x8C);
            jal(ctx, 0x263AD8u, gen::fn_sub_21D950_0021d950);
            s0 = addiu(s0, 1);
        }
        // 0x00263af0
        charge(ctx, 164);
        a0 = s2;
        a1 = 5;
        jal(ctx, 0x263AF8u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 0x43600000;
        sw(v1, sp, 0x60);
        v1 = 0x437E0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f1, f0);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        lwc1(f0, s1, brhero::kSp);
        cvt_s_w(f0, f0);
        mul_s(f1, f1, f0);
        lwc1(f0, s1, brhero::kMaxSp);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 9552);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263B58u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = 0;
        jal(ctx, 0x263B64u, gen::fn_sub_233DF0_00233df0);
        v0 = 0x42480000;
        sw(v0, sp, 0x60);
        sw(zero, sp, 0x64);
        v0 = 353;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        v0 = 0x42280000;
        sw(v0, sp, 0x6C);
        a0 = addiu(s1, 10576);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263B9Cu, gen::fn_sub_21D8E0_0021d8e0);
        lw(a0, s1, brhero::kWord5684);
        jal(ctx, 0x263BA8u, gen::fn_sub_264CA0_00264ca0);
        v1 = 0x43580000;
        sw(v1, sp, 0x60);
        v1 = 0x437F0000;
        sw(v1, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 10832);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263BE0u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 0x431B0000;
        mtc1(v0, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = sll(v0, 4);
        v0 = 0x434E0000;
        mtc1(v0, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a2 = sll(v0, 3);
        lw(a0, s1, brhero::kNameLine);
        jal(ctx, 0x263C24u, gen::fn_frFontLineSetPos_003b0d70);
        lw(a0, s1, brhero::kNameLine);
        a1 = si(-51);
        jal(ctx, 0x263C34u, gen::fn_frFontLineSetRgba_003b0e20);
        a0 = s2;
        a1 = 17;
        jal(ctx, 0x263C44u, gen::fn_sub_21CCA0_0021cca0);
        s0 = v0;
        v1 = 0x424C0000;
        sw(v1, sp, 0x60);
        v1 = 299;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 12640);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263C8Cu, gen::fn_sub_21D8E0_0021d8e0);
        lwc1(f0, s0, 12);
        cvt_s_w(f1, f0);
        v0 = 0x424C0000;
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x60);
        v0 = 299;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x64);
        v0 = 0x42D40000;
        sw(v0, sp, 0x68);
        lwc1(f0, s0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 12896);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263CE0u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s2;
        a1 = 34;
        jal(ctx, 0x263CF0u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 305;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x60);
        v1 = 299;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x64);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x68);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x6C);
        a0 = addiu(s1, 13152);
        a1 = addiu(sp, 0x60);
        jal(ctx, 0x263D40u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 0x43590000;
        sw(v0, sp, 0x60);
        v0 = 301;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x64);
        a0 = addiu(s1, 13408);
        a1 = 5;
        lw(a2, s1, brhero::kNextExp);
        a3 = 2;
        t0 = addiu(sp, 0x60);
        jal(ctx, 0x263D78u, gen::fn_sub_238DC0_00238dc0);
    }
    // 0x00263d80 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00263DB0 sub_263DB0 -- 3812 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brHeroDraw] Draws the result screen's hero panel (K_Assert line 83) while open: the quads in panel order (textures
// 22..29, the rank plates, the bars, the level-up plates, the numbers sub_239140) and the name line (frFontDraw)
// through the Im2D slot.
void sub_263DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00263db0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBrHero);  // the result screen hero panel (br_hero.c) 0x7CE37C
    if (v1 == 0) {
        // 0x00263de4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 83;
        jal(ctx, 0x263DF0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00263df8
    charge(ctx, 6);
    lw(s1, gp, kGpBrHero);  // the result screen hero panel (br_hero.c) 0x7CE37C
    lw(v1, s1, brhero::kFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00263e10
        charge(ctx, 46);
        a0 = 0;
        jal(ctx, 0x263E14u, gen::fn_sub_233D70_00233d70);
        s5 = v0;
        a0 = 1;
        jal(ctx, 0x263E24u, gen::fn_sub_233D70_00233d70);
        s4 = v0;
        a0 = 3;
        jal(ctx, 0x263E34u, gen::fn_sub_233D70_00233d70);
        s7 = v0;
        s0 = 0x960000;
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x263E54u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x263E68u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x263E7Cu, v0.u());
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x263E90u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x263EA0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 1;
        a1 = 0;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x263EB4u, v0.u());
        s3 = 0;
        for (;;) {
            // 0x00263f20
            charge(ctx, 3);
            v0 = slti(s3, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00263ec8
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s1, v0);
            s2 = addiu(v0, 1552);
            s6 = 0x960000;
            s6 = addiu(s6, 156);  // &0x96009C
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s6, 0);  // 0x96009C
            jalr(ctx, 0x263EF4u, v0.u());
            a0 = s2;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s6, 0);  // 0x96009C
            jalr(ctx, 0x263F14u, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00263f2c
        charge(ctx, 187);
        a0 = s5;
        a1 = 22;
        jal(ctx, 0x263F34u, gen::fn_sub_21CCA0_0021cca0);
        s3 = 0x960000;
        s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x263F48u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x263F5Cu, v0.u());
        s2 = 0x960000;
        s2 = addiu(s2, 156);  // &0x96009C
        a0 = addiu(s1, 16);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x263F84u, v0.u());
        a0 = addiu(s1, 16);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x263FA4u, v0.u());
        a0 = s5;
        a1 = 23;
        jal(ctx, 0x263FB4u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x263FC0u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x263FD4u, v0.u());
        a0 = addiu(s1, 272);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x263FF4u, v0.u());
        a0 = addiu(s1, 272);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264014u, v0.u());
        a0 = s5;
        a1 = 24;
        jal(ctx, 0x264024u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264030u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264044u, v0.u());
        a0 = addiu(s1, 528);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264064u, v0.u());
        a0 = addiu(s1, 528);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264084u, v0.u());
        a0 = s5;
        a1 = 25;
        jal(ctx, 0x264094u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x2640A0u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2640B4u, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2640D4u, v0.u());
        a0 = addiu(s1, 784);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2640F4u, v0.u());
        a0 = s5;
        a1 = 26;
        jal(ctx, 0x264104u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264110u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264124u, v0.u());
        a0 = addiu(s1, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264144u, v0.u());
        a0 = addiu(s1, 1040);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264164u, v0.u());
        a0 = s5;
        a1 = 27;
        jal(ctx, 0x264174u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264180u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264194u, v0.u());
        a0 = addiu(s1, 1296);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2641B4u, v0.u());
        a0 = addiu(s1, 1296);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2641D4u, v0.u());
        a0 = s5;
        a1 = 28;
        jal(ctx, 0x2641E4u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x2641F0u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264204u, v0.u());
        s2 = 0;
        for (;;) {
            // 0x00264270
            charge(ctx, 3);
            v0 = slti(s2, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00264218
            charge(ctx, 22);
            v0 = sll(s2, 8);
            v0 = addu(s1, v0);
            s3 = addiu(v0, 2320);
            s6 = 0x960000;
            s6 = addiu(s6, 156);  // &0x96009C
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s6, 0);  // 0x96009C
            jalr(ctx, 0x264244u, v0.u());
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s6, 0);  // 0x96009C
            jalr(ctx, 0x264264u, v0.u());
            s2 = addiu(s2, 1);
        }
        // 0x0026427c
        charge(ctx, 15);
        a0 = s5;
        a1 = 29;
        jal(ctx, 0x264284u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264290u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s0, 0);
        jalr(ctx, 0x2642A4u, v0.u());
        s2 = 0;
        for (;;) {
            // 0x00264310
            charge(ctx, 3);
            v0 = slti(s2, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002642b8
            charge(ctx, 22);
            v0 = sll(s2, 8);
            v0 = addu(s1, v0);
            s3 = addiu(v0, 3088);
            s6 = 0x960000;
            s6 = addiu(s6, 156);  // &0x96009C
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s6, 0);  // 0x96009C
            jalr(ctx, 0x2642E4u, v0.u());
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s6, 0);  // 0x96009C
            jalr(ctx, 0x264304u, v0.u());
            s2 = addiu(s2, 1);
        }
        // 0x0026431c
        charge(ctx, 125);
        a0 = s5;
        lw(a1, s1, brhero::kAcademics);
        jal(ctx, 0x264324u, gen::fn_sub_21CCA0_0021cca0);
        s3 = 0x960000;
        s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x264338u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x26434Cu, v0.u());
        s2 = 0x960000;
        s2 = addiu(s2, 156);  // &0x96009C
        a0 = addiu(s1, 3856);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264374u, v0.u());
        a0 = addiu(s1, 3856);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264394u, v0.u());
        lw(v0, s1, brhero::kCharm);
        a1 = addiu(v0, 7);
        a0 = s5;
        jal(ctx, 0x2643A8u, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x2643B4u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2643C8u, v0.u());
        a0 = addiu(s1, 4112);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2643E8u, v0.u());
        a0 = addiu(s1, 4112);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x264408u, v0.u());
        lw(v0, s1, brhero::kCourage);
        a1 = addiu(v0, 14);
        a0 = s5;
        jal(ctx, 0x26441Cu, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264428u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x26443Cu, v0.u());
        a0 = addiu(s1, 4368);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x26445Cu, v0.u());
        a0 = addiu(s1, 4368);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x26447Cu, v0.u());
        a0 = 0;
        jal(ctx, 0x264488u, gen::fn_sub_233DF0_00233df0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x26449Cu, v0.u());
        a0 = addiu(s1, 10576);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2644BCu, v0.u());
        a0 = addiu(s1, 10576);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2644DCu, v0.u());
        a0 = 1;
        jal(ctx, 0x2644E8u, gen::fn_sub_233DF0_00233df0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2644FCu, v0.u());
        s3 = 0;
        for (;;) {
            // 0x00264568
            charge(ctx, 3);
            v0 = slti(s3, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00264510
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s1, v0);
            s5 = addiu(v0, 4896);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26453Cu, v0.u());
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26455Cu, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00264574
        charge(ctx, 71);
        a0 = s7;
        a1 = 0;
        jal(ctx, 0x26457Cu, gen::fn_sub_21CCA0_0021cca0);
        s3 = 0x960000;
        s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x264590u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2645A4u, v0.u());
        s2 = 0x960000;
        s2 = addiu(s2, 156);  // &0x96009C
        a0 = addiu(s1, 4640);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2645CCu, v0.u());
        a0 = addiu(s1, 4640);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x2645ECu, v0.u());
        a0 = s4;
        a1 = 0;
        jal(ctx, 0x2645FCu, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264608u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x26461Cu, v0.u());
        a0 = addiu(s1, 5408);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x26463Cu, v0.u());
        a0 = addiu(s1, 5408);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s2, 0);  // 0x96009C
        jalr(ctx, 0x26465Cu, v0.u());
        a0 = 2;
        jal(ctx, 0x264668u, gen::fn_sub_239140_00239140);
        a0 = 1;
        a1 = v0;
        lw(v0, s3, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x26467Cu, v0.u());
        s3 = 0;
        for (;;) {
            // 0x002646e8
            charge(ctx, 3);
            v0 = slti(s3, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00264690
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s1, v0);
            s5 = addiu(v0, 5712);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x2646BCu, v0.u());
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x2646DCu, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x002646f4
        charge(ctx, 11);
        a0 = 2;
        jal(ctx, 0x2646F8u, gen::fn_sub_239140_00239140);
        a0 = 1;
        a1 = v0;
        lw(v0, s0, 0);
        jalr(ctx, 0x26470Cu, v0.u());
        s3 = 0;
        for (;;) {
            // 0x00264778
            charge(ctx, 3);
            v0 = slti(s3, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00264720
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s1, v0);
            s5 = addiu(v0, 6224);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26474Cu, v0.u());
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26476Cu, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00264784
        charge(ctx, 11);
        a0 = 2;
        jal(ctx, 0x264788u, gen::fn_sub_239140_00239140);
        a0 = 1;
        a1 = v0;
        lw(v0, s0, 0);
        jalr(ctx, 0x26479Cu, v0.u());
        s3 = 0;
        for (;;) {
            // 0x00264808
            charge(ctx, 3);
            v0 = slti(s3, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002647b0
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s1, v0);
            s5 = addiu(v0, 6992);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x2647DCu, v0.u());
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x2647FCu, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00264814
        charge(ctx, 43);
        a0 = s4;
        a1 = 4;
        jal(ctx, 0x26481Cu, gen::fn_sub_21CCA0_0021cca0);
        s2 = 0x960000;
        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x264830u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264844u, v0.u());
        s3 = 0x960000;
        s3 = addiu(s3, 156);  // &0x96009C
        a0 = addiu(s1, 7760);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s3, 0);  // 0x96009C
        jalr(ctx, 0x26486Cu, v0.u());
        a0 = addiu(s1, 7760);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s3, 0);  // 0x96009C
        jalr(ctx, 0x26488Cu, v0.u());
        a0 = 2;
        jal(ctx, 0x264898u, gen::fn_sub_239140_00239140);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2648ACu, v0.u());
        s3 = 0;
        for (;;) {
            // 0x00264918
            charge(ctx, 3);
            v0 = slti(s3, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002648c0
            charge(ctx, 22);
            v0 = sll(s3, 8);
            v0 = addu(s1, v0);
            s5 = addiu(v0, 8016);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x2648ECu, v0.u());
            a0 = s5;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26490Cu, v0.u());
            s3 = addiu(s3, 1);
        }
        // 0x00264924
        charge(ctx, 11);
        a0 = 2;
        jal(ctx, 0x264928u, gen::fn_sub_239140_00239140);
        a0 = 1;
        a1 = v0;
        lw(v0, s0, 0);
        jalr(ctx, 0x26493Cu, v0.u());
        s0 = 0;
        for (;;) {
            // 0x002649a8
            charge(ctx, 3);
            v0 = slti(s0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00264950
            charge(ctx, 22);
            v0 = sll(s0, 8);
            v0 = addu(s1, v0);
            s3 = addiu(v0, 8784);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26497Cu, v0.u());
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x26499Cu, v0.u());
            s0 = addiu(s0, 1);
        }
        // 0x002649b4
        charge(ctx, 147);
        a0 = s4;
        a1 = 5;
        jal(ctx, 0x2649BCu, gen::fn_sub_21CCA0_0021cca0);
        s2 = 0x960000;
        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
        a0 = v0;
        jal(ctx, 0x2649D0u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x2649E4u, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 156);  // &0x96009C
        a0 = addiu(s1, 9552);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264A0Cu, v0.u());
        a0 = addiu(s1, 9552);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264A2Cu, v0.u());
        lw(a0, s1, brhero::kWord5684);
        jal(ctx, 0x264A38u, gen::fn_sub_264CA0_00264ca0);
        a0 = v0;
        jal(ctx, 0x264A44u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264A58u, v0.u());
        a0 = addiu(s1, 10832);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264A78u, v0.u());
        a0 = addiu(s1, 10832);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264A98u, v0.u());
        lw(a0, s1, brhero::kNameLine);
        a1 = 1;
        a2 = 0;
        jal(ctx, 0x264AACu, gen::fn_frFontDraw_003b1360);
        a0 = s4;
        a1 = 17;
        jal(ctx, 0x264ABCu, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264AC8u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264ADCu, v0.u());
        a0 = addiu(s1, 12640);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264AFCu, v0.u());
        a0 = addiu(s1, 12640);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264B1Cu, v0.u());
        a0 = addiu(s1, 12896);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264B3Cu, v0.u());
        a0 = addiu(s1, 12896);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264B5Cu, v0.u());
        a0 = s4;
        a1 = 34;
        jal(ctx, 0x264B6Cu, gen::fn_sub_21CCA0_0021cca0);
        a0 = v0;
        jal(ctx, 0x264B78u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264B8Cu, v0.u());
        a0 = addiu(s1, 13152);
        a1 = 4;
        a2 = 0;
        a3 = 1;
        t0 = 2;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264BACu, v0.u());
        a0 = addiu(s1, 13152);
        a1 = 4;
        a2 = 0;
        a3 = 2;
        t0 = 3;
        lw(v0, s0, 0);  // 0x96009C
        jalr(ctx, 0x264BCCu, v0.u());
        a0 = 2;
        jal(ctx, 0x264BD8u, gen::fn_sub_239140_00239140);
        a0 = 1;
        a1 = v0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x264BECu, v0.u());
        s0 = 0;
        for (;;) {
            // 0x00264c58
            charge(ctx, 3);
            v1 = slti(s0, 5);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00264c00
            charge(ctx, 22);
            v0 = sll(s0, 8);
            v0 = addu(s1, v0);
            s3 = addiu(v0, 13408);
            s2 = 0x960000;
            s2 = addiu(s2, 156);  // &0x96009C
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 1;
            t0 = 2;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x264C2Cu, v0.u());
            a0 = s3;
            a1 = 4;
            a2 = 0;
            a3 = 2;
            t0 = 3;
            lw(v0, s2, 0);  // 0x96009C
            jalr(ctx, 0x264C4Cu, v0.u());
            s0 = addiu(s0, 1);
        }
    }
    // 0x00264c64 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00264EF0 sub_264EF0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brPersonaSet] Switches the result screen's persona panel to persona a0 (br_persona.c, *$gp 0x7CE380; K_Assert
// lines 39 / 89: a different one): its record shown in the status task set (sub_3C9B00).
// Arguments: a0 persona id.
void sub_264EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00264ef0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBrPersona);  // the result screen persona panel (br_persona.c) 0x7CE380
    if (v0 == 0) {
        // 0x00264f10
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5064);  // "br_persona.c"
        a1 = 39;
        jal(ctx, 0x264F1Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00264f24
    charge(ctx, 5);
    lw(s0, gp, kGpBrPersona);  // the result screen persona panel (br_persona.c) 0x7CE380
    lhu(v1, s0, brpersona::kPersona);
    v0 = s1 & 0xFFFF;
    if (v1 == v0) {
        // 0x00264f38
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5064);  // "br_persona.c"
        a1 = 89;
        jal(ctx, 0x264F44u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00264f4c
    charge(ctx, 14);
    a0 = s1;
    jal(ctx, 0x264F50u, gen::fn_sub_1749A0_001749a0);
    lw(a0, s0, brpersona::kStatus);
    a1 = v0;
    a2 = 0;
    jal(ctx, 0x264F64u, gen::fn_sub_3C9B00_003c9b00);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00272810 sub_272810 -- 3976 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpSeqUpdate] Per-frame update of the result screen's persona sequence (brp_seq.c, *$gp 0x7CE3C0; K_Assert line
// 176) while open, by its step (+16): 0 waits for the model (flag 0x100, sub_276CC0); 1 the level-up message, then
// the parameter rises (brpSeqNext) or more level-ups; 2 the stat increases one by one (the five rises +90.. by name
// 0x68ED70 with sprintf('%d'), sound 1/0/8/1), then the next step; 3 the new skills (+24: 0 show 'learned' / 1
// confirm / 2 the 'forget a skill' grid when eight are known (3 x 4 cursor +440 / +444 on the pad's left / right / up
// / down) / 3 cursor / 4 confirm the forget / 5 next); 4 the skill power-up or change offer (+32, the two names of
// +160 / +162, messages 14 / 15 / 16, sub_1768E0 / sub_176840); 5 the evolution (+28: the shift to another persona
// (sub_1FB560, 'shift %d') or an item (sub_1FBA70, 'get item %d'), the fade, the birth screen (sub_24A7F0 /
// sub_24AB10 / sub_24ABD0)); afterwards the birth step (sub_24ADF0) while flag 0x40.
void sub_272810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00272810
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    if (v1 == 0) {
        // 0x00272830
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x27283Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00272844
    charge(ctx, 6);
    lw(s2, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    lw(a1, s2, brpseq::kFlags);
    v1 = nor(a1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0027285c
        charge(ctx, 4);
        lw(v1, s2, brpseq::kStep);
        at = sltiu(v1, 6);
        if (at != 0) {
            // 0x0027286c
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, 31392);  // &0x7B7AA0
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x272888u:  // table[0]: step 0, wait for the persona model (flag 0x100)
                // 0x00272888
                charge(ctx, 3);
                v1 = a1 & 0x100;
                if (v1 != 0) {
                    // 0x00272894
                    charge(ctx, 4);
                    jal(ctx, 0x272894u, gen::fn_sub_276CC0_00276cc0);
                    if (v0 == 0) {
                        // 0x002728a4
                        charge(ctx, 6);
                        lw(a0, s2, brpseq::kFlags);
                        v1 = si(-257);
                        v1 = a0 & v1;
                        sw(v1, s2, brpseq::kFlags);
                    }
                }
                break;
            case 0x2728BCu:  // table[1]: step 1, the level-up message
                // 0x002728bc
                charge(ctx, 3);
                lw(v1, s2, brpseq::kFrame);
                if (v1 == 0) {
                    // 0x002728d0
                    charge(ctx, 7);
                    a0 = 0;
                    jal(ctx, 0x2728D4u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x2728DCu, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x002728ec
                        charge(ctx, 4);
                        lw(v0, s2, brpseq::kFirstStat);
                        at = slti(v0, 5);
                        if (at != 0) {
                            // 0x002728fc
                            charge(ctx, 4);
                            lw(v0, s2, brpseq::kLastStat);
                            at = slti(v0, 5);
                            if (at == 0) {
                                goto L_00272928;
                            }
                            // 0x0027290c
                            charge(ctx, 7);
                            a0 = 0;
                            jal(ctx, 0x272910u, gen::fn_msgWinClose_003c7650);
                            jal(ctx, 0x272918u, gen::fn_sub_273B30_00273b30);
                            break;
                        }
                    L_00272928:
                        charge(ctx, 9);
                        a0 = 1;
                        jal(ctx, 0x27292Cu, gen::fn_msgWinClose_003c7650);
                        v0 = 2;
                        sw(v0, s2, brpseq::kStep);
                        jal(ctx, 0x27293Cu, gen::fn_sub_273800_00273800);
                    }
                } else {
                    // 0x002728c8
                    charge(ctx, 2);
                }
                break;
            case 0x27294Cu:  // table[2]: step 2, the stat rises one by one
                // 0x0027294c
                charge(ctx, 4);
                lw(a0, s2, brpseq::kStatFrame);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00272a78
                    charge(ctx, 4);
                    jal(ctx, 0x272A78u, gen::fn_sub_279700_00279700);
                    if (v0 == 0) {
                        // 0x00272a88
                        charge(ctx, 4);
                        jal(ctx, 0x272A88u, gen::fn_sub_273800_00273800);
                    }
                } else {
                    // 0x0027295c
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0027296c
                        charge(ctx, 11);
                        lw(v1, s2, brpseq::kFirstStat);
                        lw(v0, s2, brpseq::kLastStat);
                        s0 = v1 ^ v0;
                        s0 = sltiu(s0, 1);
                        a0 = s0;
                        jal(ctx, 0x272980u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x272988u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x00272998
                            charge(ctx, 8);
                            a0 = s0;
                            jal(ctx, 0x27299Cu, gen::fn_msgWinClose_003c7650);
                            lw(v1, s2, brpseq::kFirstStat);
                            lw(v0, s2, brpseq::kLastStat);
                            at = slt(v1, v0);
                            if (at == 0) {
                                // 0x00272a60
                                charge(ctx, 6);
                                jal(ctx, 0x272A60u, gen::fn_sub_2796B0_002796b0);
                                v1 = 1;
                                sw(v1, s2, brpseq::kStatFrame);
                            } else {
                                // 0x002729b8
                                charge(ctx, 3);
                                v1 = addiu(v1, 1);
                                for (;;) {
                                    // 0x002729d8
                                    charge(ctx, 3);
                                    v0 = slti(v1, 5);
                                    if (v0 != 0) {
                                        backedge(ctx);
                                        // 0x002729c4
                                        charge(ctx, 4);
                                        v0 = addu(s2, v1);
                                        lbu(v0, v0, 90);
                                        if (v0 == 0) {
                                            // 0x002729d4
                                            charge(ctx, 1);
                                            v1 = addiu(v1, 1);
                                            continue;
                                        }
                                    }
                                    break;
                                }
                                // 0x002729e4
                                charge(ctx, 31);
                                sw(v1, s2, brpseq::kFirstStat);
                                v0 = addu(v1, s2);
                                lbu(a2, v0, 90);
                                a0 = addiu(sp, 0x40);
                                a1 = addiu(gp, -26672);  // "%d"
                                jal(ctx, 0x2729F8u, gen::fn_sprintf_00523ac8);
                                lw(v0, s2, brpseq::kFirstStat);
                                v1 = sll(v0, 2);
                                v0 = 0x690000;
                                v0 = addiu(v0, -4752);  // &0x68ED70
                                v0 = addu(v0, v1);
                                a0 = 0;
                                lw(a1, v0, 0);
                                jal(ctx, 0x272A1Cu, gen::fn_sub_3C7BC0_003c7bc0);
                                a0 = 1;
                                a1 = addiu(sp, 0x40);
                                jal(ctx, 0x272A2Cu, gen::fn_sub_3C7BC0_003c7bc0);
                                a0 = 1;
                                jal(ctx, 0x272A38u, gen::fn_msgWinRequestMessage_003c7430);
                                a0 = 1;
                                a1 = 0;
                                a2 = 8;
                                a3 = a0;
                                jal(ctx, 0x272A50u, gen::fn_sub_10A4E0_0010a4e0);
                            }
                        }
                    } else {
                        // 0x00272964
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x272A98u:  // table[3]: step 3, the new skills (substep +24)
                // 0x00272a98
                charge(ctx, 4);
                lw(v1, s2, brpseq6::kSkillStep);
                at = sltiu(v1, 6);
                if (at != 0) {
                    // 0x00272aa8
                    charge(ctx, 7);
                    a0 = 0x7B0000;
                    a0 = addiu(a0, 31360);  // &0x7B7A80
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    switch (v1.u()) {
                    case 0x272AC4u:  // table[0]: substep 0, "learned" with the skill's name
                        // 0x00272ac4
                        charge(ctx, 4);
                        jal(ctx, 0x272AC4u, gen::fn_sub_2797A0_002797a0);
                        if (v0 == 0) {
                            // 0x00272ad4
                            charge(ctx, 38);
                            lw(v0, s2, brpseq::kWord432);
                            v0 = sll(v0, 3);
                            v0 = addu(v0, s2);
                            lhu(v1, v0, 452);
                            lw(v0, s2, brpseq::kSkillCount);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, s2);
                            sh(v1, v0, 96);
                            lw(v0, s2, brpseq::kSkillCount);
                            v0 = addiu(v0, 1);
                            sw(v0, s2, brpseq::kSkillCount);
                            lhu(a0, s2, brpseq::kPersona);
                            jal(ctx, 0x272B04u, gen::fn_sub_173220_00173220);
                            a0 = 0;
                            a1 = v0;
                            jal(ctx, 0x272B14u, gen::fn_sub_3C7BC0_003c7bc0);
                            lw(v0, s2, brpseq::kWord432);
                            v0 = sll(v0, 3);
                            v0 = addu(v0, s2);
                            lhu(v1, v0, 452);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 1);
                            v1 = addu(v0, v1);
                            lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                            a1 = addu(v0, v1);
                            a0 = 1;
                            jal(ctx, 0x272B48u, gen::fn_sub_3C7BC0_003c7bc0);
                            a0 = 2;
                            jal(ctx, 0x272B54u, gen::fn_msgWinRequestMessage_003c7430);
                            v1 = 1;
                            sw(v1, s2, brpseq6::kSkillStep);
                        }
                        break;
                    case 0x272B6Cu:  // table[1]: substep 1, confirmed: the next skill, or the forget grid once nine are known
                        // 0x00272b6c
                        charge(ctx, 9);
                        lw(v0, s2, brpseq::kSkillCount);
                        s0 = slti(v0, 9);
                        a0 = s0;
                        jal(ctx, 0x272B78u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x272B80u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x00272b90
                            charge(ctx, 7);
                            a0 = s0;
                            jal(ctx, 0x272B94u, gen::fn_msgWinClose_003c7650);
                            lw(v0, s2, brpseq::kSkillCount);
                            at = slti(v0, 9);
                            if (at != 0) {
                                // 0x00272bbc
                                charge(ctx, 4);
                                jal(ctx, 0x272BBCu, gen::fn_sub_274100_00274100);
                            } else {
                                // 0x00272bac
                                charge(ctx, 4);
                                jal(ctx, 0x272BACu, gen::fn_sub_273E10_00273e10);
                            }
                        }
                        break;
                    case 0x272BCCu:  // table[2]: substep 2, open the forget grid
                        // 0x00272bcc
                        charge(ctx, 7);
                        a0 = 1;
                        jal(ctx, 0x272BD0u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x272BD8u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x00272be8
                            charge(ctx, 15);
                            a0 = 1;
                            jal(ctx, 0x272BECu, gen::fn_msgWinClose_003c7650);
                            jal(ctx, 0x272BF4u, gen::fn_sub_2797F0_002797f0);
                            sw(zero, s2, brpseq6::kGridColumn);
                            sw(zero, s2, brpseq6::kGridRow);
                            lw(a0, s2, brpseq6::kGridColumn);
                            a1 = 0;
                            jal(ctx, 0x272C0Cu, gen::fn_sub_279890_00279890);
                            v1 = 3;
                            sw(v1, s2, brpseq6::kSkillStep);
                        }
                        break;
                    case 0x272C24u:  // table[3]: substep 3, the grid cursor (3 columns x 4 rows; confirm asks)
                        // 0x00272c24
                        charge(ctx, 5);
                        v1 = 0x7E0000;
                        lhu(v1, v1, 2382);  // gPadFlags
                        v1 = v1 & 0x40;
                        if (v1 == 0) {
                            // 0x00272cd0
                            charge(ctx, 4);
                            lw(a1, s2, brpseq6::kGridColumn);
                            at = slti(a1, 2);
                            if (at != 0) {
                                // 0x00272ce0
                                charge(ctx, 5);
                                v1 = 0x7E0000;
                                lhu(v1, v1, 2386);  // 0x7E0952
                                v1 = v1 & 0x4000;
                                if (v1 == 0) {
                                    goto L_00272d68;
                                }
                                // 0x00272cf4
                                charge(ctx, 4);
                                lw(v0, s2, brpseq6::kGridRow);
                                at = slti(v0, 3);
                                if (at == 0) {
                                    // 0x00272d14
                                    charge(ctx, 1);
                                    sw(zero, s2, brpseq6::kGridRow);
                                } else {
                                    // 0x00272d04
                                    charge(ctx, 4);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s2, brpseq6::kGridRow);
                                }
                                // 0x00272d18
                                charge(ctx, 4);
                                lw(a0, s2, brpseq6::kGridColumn);
                                v0 = 2;
                                if (a0 != v0) {
                                    // 0x00272d3c
                                    charge(ctx, 3);
                                    lw(a1, s2, brpseq6::kGridRow);
                                    jal(ctx, 0x272D40u, gen::fn_sub_279890_00279890);
                                } else {
                                    // 0x00272d28
                                    charge(ctx, 5);
                                    a1 = 1;
                                    jal(ctx, 0x272D2Cu, gen::fn_sub_279890_00279890);
                                }
                                // 0x00272d48
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x272D58u, gen::fn_sub_10A4E0_0010a4e0);
                                goto L_00272efc;
                            }
                        L_00272d68:
                            charge(ctx, 3);
                            at = slti(a1, 2);
                            if (at != 0) {
                                // 0x00272d74
                                charge(ctx, 5);
                                v1 = 0x7E0000;
                                lhu(v1, v1, 2386);  // 0x7E0952
                                v1 = v1 & 0x1000;
                                if (v1 == 0) {
                                    goto L_00272dfc;
                                }
                                // 0x00272d88
                                charge(ctx, 3);
                                lw(v0, s2, brpseq6::kGridRow);
                                if (i64(v0) <= 0) {
                                    // 0x00272da4
                                    charge(ctx, 2);
                                    v0 = 3;
                                    sw(v0, s2, brpseq6::kGridRow);
                                } else {
                                    // 0x00272d94
                                    charge(ctx, 4);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s2, brpseq6::kGridRow);
                                }
                                // 0x00272dac
                                charge(ctx, 4);
                                lw(a0, s2, brpseq6::kGridColumn);
                                v0 = 2;
                                if (a0 != v0) {
                                    // 0x00272dd0
                                    charge(ctx, 3);
                                    lw(a1, s2, brpseq6::kGridRow);
                                    jal(ctx, 0x272DD4u, gen::fn_sub_279890_00279890);
                                } else {
                                    // 0x00272dbc
                                    charge(ctx, 5);
                                    a1 = 1;
                                    jal(ctx, 0x272DC0u, gen::fn_sub_279890_00279890);
                                }
                                // 0x00272ddc
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x272DECu, gen::fn_sub_10A4E0_0010a4e0);
                                goto L_00272efc;
                            }
                        L_00272dfc:
                            charge(ctx, 5);
                            v1 = 0x7E0000;
                            lhu(a0, v1, 2386);  // 0x7E0952
                            v1 = a0 & 0x2000;
                            if (v1 == 0) {
                                // 0x00272e84
                                charge(ctx, 3);
                                v1 = a0 & 0x8000;
                                if (v1 != 0) {
                                    // 0x00272e90
                                    charge(ctx, 2);
                                    if (i64(a1) <= 0) {
                                        // 0x00272eac
                                        charge(ctx, 2);
                                        v0 = 2;
                                        sw(v0, s2, brpseq6::kGridColumn);
                                    } else {
                                        // 0x00272e98
                                        charge(ctx, 5);
                                        lw(v0, s2, brpseq6::kGridColumn);
                                        v0 = addiu(v0, -1);
                                        sw(v0, s2, brpseq6::kGridColumn);
                                    }
                                    // 0x00272eb4
                                    charge(ctx, 4);
                                    lw(a0, s2, brpseq6::kGridColumn);
                                    v0 = 2;
                                    if (a0 != v0) {
                                        // 0x00272ed8
                                        charge(ctx, 3);
                                        lw(a1, s2, brpseq6::kGridRow);
                                        jal(ctx, 0x272EDCu, gen::fn_sub_279890_00279890);
                                    } else {
                                        // 0x00272ec4
                                        charge(ctx, 5);
                                        a1 = 1;
                                        jal(ctx, 0x272EC8u, gen::fn_sub_279890_00279890);
                                    }
                                    // 0x00272ee4
                                    charge(ctx, 6);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x272EF4u, gen::fn_sub_10A4E0_0010a4e0);
                                }
                            } else {
                                // 0x00272e10
                                charge(ctx, 3);
                                at = slti(a1, 2);
                                if (at == 0) {
                                    // 0x00272e30
                                    charge(ctx, 1);
                                    sw(zero, s2, brpseq6::kGridColumn);
                                } else {
                                    // 0x00272e1c
                                    charge(ctx, 5);
                                    lw(v0, s2, brpseq6::kGridColumn);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s2, brpseq6::kGridColumn);
                                }
                                // 0x00272e34
                                charge(ctx, 4);
                                lw(a0, s2, brpseq6::kGridColumn);
                                v0 = 2;
                                if (a0 != v0) {
                                    // 0x00272e58
                                    charge(ctx, 3);
                                    lw(a1, s2, brpseq6::kGridRow);
                                    jal(ctx, 0x272E5Cu, gen::fn_sub_279890_00279890);
                                } else {
                                    // 0x00272e44
                                    charge(ctx, 5);
                                    a1 = 1;
                                    jal(ctx, 0x272E48u, gen::fn_sub_279890_00279890);
                                }
                                // 0x00272e64
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x272E74u, gen::fn_sub_10A4E0_0010a4e0);
                            }
                        L_00272efc:
                            charge(ctx, 4);
                            lw(a0, s2, brpseq6::kGridColumn);
                            v1 = 2;
                            if (a0 != v1) {
                                // 0x00272f18
                                charge(ctx, 3);
                                a0 = sll(a0, 2);
                                lw(v1, s2, brpseq6::kGridRow);
                                v1 = addu(v1, a0);
                            } else {
                                // 0x00272f0c
                                charge(ctx, 3);
                                v1 = 8;
                            }
                            // 0x00272f24
                            charge(ctx, 5);
                            v1 = sll(v1, 1);
                            v1 = addu(v1, s2);
                            lhu(v1, v1, 96);
                            if (v1 == 0) {
                                // 0x00272f44
                                charge(ctx, 4);
                                v1 = si(-1);
                                sw(v1, gp, kGpSeqHelpSkill);  // the skill the forget grid of the persona sequence points at (-1 none; 0x7CC4DC) 0x7CC4DC
                            } else {
                                // 0x00272f38
                                charge(ctx, 3);
                                sw(v1, gp, kGpSeqHelpSkill);  // the skill the forget grid of the persona sequence points at (-1 none; 0x7CC4DC) 0x7CC4DC
                            }
                        } else {
                            // 0x00272c38
                            charge(ctx, 4);
                            lw(v1, s2, brpseq6::kGridColumn);
                            v0 = 2;
                            if (v1 != v0) {
                                // 0x00272c54
                                charge(ctx, 3);
                                v1 = sll(v1, 2);
                                lw(v0, s2, brpseq6::kGridRow);
                                v0 = addu(v0, v1);
                            } else {
                                // 0x00272c48
                                charge(ctx, 3);
                                v0 = 8;
                            }
                            // 0x00272c60
                            charge(ctx, 28);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, s2);
                            lhu(v1, v0, 96);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 1);
                            v1 = addu(v0, v1);
                            lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                            a1 = addu(v0, v1);
                            a0 = 0;
                            jal(ctx, 0x272C88u, gen::fn_sub_3C7BC0_003c7bc0);
                            a0 = 4;
                            jal(ctx, 0x272C94u, gen::fn_msgWinRequestMessage_003c7430);
                            a0 = 5;
                            jal(ctx, 0x272CA0u, gen::fn_sub_3C74E0_003c74e0);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 1;
                            jal(ctx, 0x272CB8u, gen::fn_sub_10A4E0_0010a4e0);
                            v1 = 4;
                            sw(v1, s2, brpseq6::kSkillStep);
                        }
                        break;
                    case 0x272F54u:  // table[4]: substep 4, confirm the forget (the list closes up)
                        // 0x00272f54
                        charge(ctx, 7);
                        a0 = 1;
                        jal(ctx, 0x272F58u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x272F60u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x00272f70
                            charge(ctx, 4);
                            jal(ctx, 0x272F70u, gen::fn_msgWinLastSelection_003c7610);
                            if (v0 == 0) {
                                // 0x00272f88
                                charge(ctx, 7);
                                a0 = 1;
                                jal(ctx, 0x272F8Cu, gen::fn_msgWinClose_003c7650);
                                lw(v1, s2, brpseq6::kGridColumn);
                                v0 = 2;
                                if (v1 != v0) {
                                    // 0x00272fb0
                                    charge(ctx, 3);
                                    v1 = sll(v1, 2);
                                    lw(v0, s2, brpseq6::kGridRow);
                                    s1 = addu(v0, v1);
                                } else {
                                    // 0x00272fa4
                                    charge(ctx, 3);
                                    s1 = 8;
                                }
                                // 0x00272fbc
                                charge(ctx, 6);
                                v0 = sll(s1, 1);
                                v0 = addu(v0, s2);
                                lhu(s0, v0, 96);
                                a0 = s1;
                                for (;;) {
                                    // 0x00272fe8
                                    charge(ctx, 5);
                                    lw(v0, s2, brpseq::kSkillCount);
                                    v1 = addiu(v0, -1);
                                    v0 = slt(a0, v1);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x00272fd4
                                    charge(ctx, 5);
                                    v0 = sll(a0, 1);
                                    v1 = addu(s2, v0);
                                    lhu(v0, v1, 98);
                                    sh(v0, v1, 96);
                                    a0 = addiu(a0, 1);
                                }
                                // 0x00272ffc
                                charge(ctx, 21);
                                sw(v1, s2, brpseq::kSkillCount);
                                lhu(a0, s2, brpseq::kPersona);
                                jal(ctx, 0x273004u, gen::fn_sub_173220_00173220);
                                a0 = 0;
                                a1 = v0;
                                jal(ctx, 0x273014u, gen::fn_sub_3C7BC0_003c7bc0);
                                v1 = s0 & 0xFFFF;
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 1);
                                v1 = addu(v0, v1);
                                lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                                a1 = addu(v0, v1);
                                a0 = 1;
                                jal(ctx, 0x27303Cu, gen::fn_sub_3C7BC0_003c7bc0);
                                v0 = 8;
                                if (s1 != v0) {
                                    // 0x00273064
                                    charge(ctx, 3);
                                    a0 = 7;
                                    jal(ctx, 0x273068u, gen::fn_msgWinRequestMessage_003c7430);
                                } else {
                                    // 0x00273050
                                    charge(ctx, 5);
                                    a0 = 6;
                                    jal(ctx, 0x273054u, gen::fn_msgWinRequestMessage_003c7430);
                                }
                                // 0x00273070
                                charge(ctx, 4);
                                v1 = 5;
                                sw(v1, s2, brpseq6::kSkillStep);
                            } else {
                                // 0x00272f80
                                charge(ctx, 2);
                                // 0x00273080
                                charge(ctx, 7);
                                a0 = 1;
                                jal(ctx, 0x273084u, gen::fn_msgWinClose_003c7650);
                                v1 = 3;
                                sw(v1, s2, brpseq6::kSkillStep);
                            }
                        }
                        break;
                    case 0x27309Cu:  // table[5]: substep 5, the next skill
                        // 0x0027309c
                        charge(ctx, 7);
                        a0 = 1;
                        jal(ctx, 0x2730A0u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x2730A8u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x002730b8
                            charge(ctx, 7);
                            a0 = 1;
                            jal(ctx, 0x2730BCu, gen::fn_msgWinClose_003c7650);
                            jal(ctx, 0x2730C4u, gen::fn_sub_274100_00274100);
                        }
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v1.u());
                        return;
                    }
                }
                break;
            case 0x2730D4u:  // table[5]: step 5, the evolution (substep +28)
                // 0x002730d4
                charge(ctx, 4);
                lw(v1, s2, brpseq6::kEvolveStep);
                at = sltiu(v1, 7);
                if (at != 0) {
                    // 0x002730e4
                    charge(ctx, 7);
                    a0 = 0x7B0000;
                    a0 = addiu(a0, 31328);  // &0x7B7A60
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    switch (v1.u()) {
                    case 0x273100u:  // table[0]: substep 0, the evolution choice: a persona shift or an item
                        // 0x00273100
                        charge(ctx, 7);
                        a0 = 0;
                        jal(ctx, 0x273104u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x27310Cu, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x0027311c
                            charge(ctx, 5);
                            jal(ctx, 0x27311Cu, gen::fn_msgWinLastSelection_003c7610);
                            a0 = 1;
                            if (v0 == a0) {
                                // 0x0027325c
                                charge(ctx, 15);
                                a0 = 0;
                                jal(ctx, 0x273260u, gen::fn_msgWinClose_003c7650);
                                lhu(a0, s2, brpseq::kPersona);
                                jal(ctx, 0x27326Cu, gen::fn_sub_173220_00173220);
                                a0 = 0;
                                a1 = v0;
                                jal(ctx, 0x27327Cu, gen::fn_sub_3C7BC0_003c7bc0);
                                a0 = 10;
                                jal(ctx, 0x273288u, gen::fn_msgWinRequestMessage_003c7430);
                                v1 = 1;
                                sw(v1, s2, brpseq6::kEvolveStep);
                            } else {
                                // 0x00273130
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x00273140
                                    charge(ctx, 8);
                                    jal(ctx, 0x273140u, gen::fn_msgWinClose_003c7650);
                                    lw(v0, s2, brpseq::kRecord);
                                    lhu(v0, v0, 0);
                                    v0 = nor(v0, 0);
                                    v0 = v0 & 0x8;
                                    if (v0 == 0) {
                                        // 0x002731d8
                                        charge(ctx, 29);
                                        lhu(a0, s2, brpseq::kPersona);
                                        jal(ctx, 0x2731DCu, gen::fn_sub_1FBA70_001fba70);
                                        v0 = v0 & 0xFFFF;
                                        sw(v0, s2, brpseq::kChangeSkill);
                                        v0 = 1;
                                        sw(v0, s2, brpseq6::kEvolveKind);
                                        lw(v0, s2, brpseq::kFlags);
                                        v0 = v0 | 0x8;
                                        sw(v0, s2, brpseq::kFlags);
                                        a0 = 0x690000;
                                        a0 = addiu(a0, -4696);  // "get item %d\n"
                                        lw(a1, s2, brpseq::kChangeSkill);
                                        jal(ctx, 0x27320Cu, gen::fn_printf_005225a8);
                                        jal(ctx, 0x273214u, gen::fn_sub_24A7F0_0024a7f0);
                                        lw(v0, s2, brpseq::kFlags);
                                        v0 = v0 | 0x40;
                                        sw(v0, s2, brpseq::kFlags);
                                        jal(ctx, 0x273228u, gen::fn_sub_24ABD0_0024abd0);
                                        jal(ctx, 0x273230u, gen::fn_sub_108570_00108570);
                                        a0 = 2;
                                        jal(ctx, 0x27323Cu, gen::fn_sub_108670_00108670);
                                        v0 = 3;
                                        sw(v0, s2, brpseq6::kEvolveStep);
                                    } else {
                                        // 0x00273160
                                        charge(ctx, 30);
                                        lhu(a0, s2, brpseq::kPersona);
                                        jal(ctx, 0x273164u, gen::fn_sub_1FB560_001fb560);
                                        sh(v0, s2, brpseq6::kShiftPersona);
                                        sw(zero, s2, brpseq6::kEvolveKind);
                                        lw(v0, s2, brpseq::kFlags);
                                        v0 = v0 | 0x4;
                                        sw(v0, s2, brpseq::kFlags);
                                        lhu(a1, s2, brpseq6::kShiftPersona);
                                        a0 = 0x690000;
                                        a0 = addiu(a0, -4712);  // "shift %d\n"
                                        jal(ctx, 0x27318Cu, gen::fn_printf_005225a8);
                                        jal(ctx, 0x273194u, gen::fn_sub_24A7F0_0024a7f0);
                                        lw(v0, s2, brpseq::kFlags);
                                        v0 = v0 | 0x40;
                                        sw(v0, s2, brpseq::kFlags);
                                        lhu(a0, s2, brpseq6::kShiftPersona);
                                        jal(ctx, 0x2731ACu, gen::fn_sub_24AB10_0024ab10);
                                        jal(ctx, 0x2731B4u, gen::fn_sub_108570_00108570);
                                        a0 = 2;
                                        jal(ctx, 0x2731C0u, gen::fn_sub_108670_00108670);
                                        v0 = 3;
                                        sw(v0, s2, brpseq6::kEvolveStep);
                                    }
                                    // 0x0027324c
                                    charge(ctx, 4);
                                    jal(ctx, 0x27324Cu, gen::fn_sub_3C77A0_003c77a0);
                                } else {
                                    // 0x00273138
                                    charge(ctx, 2);
                                }
                            }
                            // 0x00273298
                            charge(ctx, 10);
                            lw(a0, s2, brpseq::kRecord);
                            lhu(v1, a0, 0);
                            v1 = v1 & 0xFFFB;
                            sh(v1, a0, 0);
                            lw(a0, s2, brpseq::kRecord);
                            lhu(v1, a0, 0);
                            v1 = v1 & 0xFFF7;
                            sh(v1, a0, 0);
                        }
                        break;
                    case 0x2732C0u:  // table[1]: substep 1, the message closed: the sequence goes on
                        // 0x002732c0
                        charge(ctx, 7);
                        a0 = 0;
                        jal(ctx, 0x2732C4u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x2732CCu, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x002732dc
                            charge(ctx, 7);
                            a0 = 0;
                            jal(ctx, 0x2732E0u, gen::fn_msgWinClose_003c7650);
                            jal(ctx, 0x2732E8u, gen::fn_sub_273800_00273800);
                        }
                        break;
                    case 0x2732F8u:  // table[3]: substep 3, wait for the birth screen and the fade
                        // 0x002732f8
                        charge(ctx, 4);
                        jal(ctx, 0x2732F8u, gen::fn_sub_24AC40_0024ac40);
                        if (v0 == 0) {
                            // 0x00273308
                            charge(ctx, 4);
                            jal(ctx, 0x273308u, gen::fn_sub_108710_00108710);
                            if (v0 != 0) {
                                // 0x00273318
                                charge(ctx, 12);
                                jal(ctx, 0x273318u, gen::fn_sub_276A80_00276a80);
                                jal(ctx, 0x273320u, gen::fn_sub_2798F0_002798f0);
                                jal(ctx, 0x273328u, gen::fn_sub_276870_00276870);
                                jal(ctx, 0x273330u, gen::fn_sub_24A870_0024a870);
                                v1 = 4;
                                sw(v1, s2, brpseq6::kEvolveStep);
                            }
                        }
                        break;
                    case 0x273348u:  // table[4]: substep 4
                        // 0x00273348
                        charge(ctx, 4);
                        jal(ctx, 0x273348u, gen::fn_sub_24B9E0_0024b9e0);
                        if (v0 == 0) {
                            // 0x00273358
                            charge(ctx, 9);
                            jal(ctx, 0x273358u, gen::fn_sub_2347E0_002347e0);
                            a0 = v0;
                            jal(ctx, 0x273364u, gen::fn_sub_3C72D0_003c72d0);
                            lw(a0, s2, brpseq6::kEvolveKind);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x002733d8
                                charge(ctx, 6);
                                lh(a0, s2, brpseq::kChangeSkill);
                                jal(ctx, 0x2733DCu, gen::fn_sub_171250_00171250);
                                v1 = 4;
                                if (v0 == v1) {
                                    // 0x0027345c
                                    charge(ctx, 8);
                                    lh(a0, s2, brpseq::kChangeSkill);
                                    a1 = 0;
                                    jal(ctx, 0x273464u, gen::fn_sub_171110_00171110);
                                    a0 = 1;
                                    a1 = v0;
                                    jal(ctx, 0x273474u, gen::fn_sub_3C7BC0_003c7bc0);
                                } else {
                                    // 0x002733f0
                                    charge(ctx, 3);
                                    v1 = 3;
                                    if (v0 != v1) {
                                        // 0x002733fc
                                        charge(ctx, 3);
                                        v1 = 2;
                                        if (v0 == v1) {
                                            goto L_00273424;
                                        }
                                        // 0x00273408
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (v0 == v1) {
                                            goto L_00273424;
                                        }
                                        // 0x00273414
                                        charge(ctx, 2);
                                        if (v0 == 0) {
                                            goto L_00273424;
                                        }
                                        // 0x0027341c
                                        charge(ctx, 2);
                                        goto L_0027347c;
                                    }
                                L_00273424:
                                    charge(ctx, 14);
                                    lh(a0, s2, brpseq::kChangeSkill);
                                    a1 = addiu(s2, 136);
                                    jal(ctx, 0x27342Cu, gen::fn_sub_1828D0_001828d0);
                                    lh(a0, s2, brpseq::kChangeSkill);
                                    lbu(a1, s2, 144);
                                    jal(ctx, 0x27343Cu, gen::fn_sub_171110_00171110);
                                    a0 = 1;
                                    a1 = v0;
                                    jal(ctx, 0x27344Cu, gen::fn_sub_3C7BC0_003c7bc0);
                                }
                            L_0027347c:
                                charge(ctx, 10);
                                lhu(a0, s2, brpseq::kPersona);
                                jal(ctx, 0x273480u, gen::fn_sub_173220_00173220);
                                a0 = 0;
                                a1 = v0;
                                jal(ctx, 0x273490u, gen::fn_sub_3C7BC0_003c7bc0);
                                a0 = 12;
                                jal(ctx, 0x27349Cu, gen::fn_msgWinRequestMessage_003c7430);
                            } else {
                                // 0x0027337c
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x0027338c
                                    charge(ctx, 19);
                                    lhu(a0, s2, brpseq::kPersona);
                                    jal(ctx, 0x273390u, gen::fn_sub_173220_00173220);
                                    a0 = 0;
                                    a1 = v0;
                                    jal(ctx, 0x2733A0u, gen::fn_sub_3C7BC0_003c7bc0);
                                    lhu(a0, s2, brpseq6::kShiftPersona);
                                    jal(ctx, 0x2733ACu, gen::fn_sub_173220_00173220);
                                    a0 = 1;
                                    a1 = v0;
                                    jal(ctx, 0x2733BCu, gen::fn_sub_3C7BC0_003c7bc0);
                                    a0 = 11;
                                    jal(ctx, 0x2733C8u, gen::fn_msgWinRequestMessage_003c7430);
                                } else {
                                    // 0x00273384
                                    charge(ctx, 2);
                                }
                            }
                            // 0x002734a4
                            charge(ctx, 4);
                            v1 = 2;
                            sw(v1, s2, brpseq6::kEvolveStep);
                        }
                        break;
                    case 0x2734B4u:  // table[2]: substep 2
                        // 0x002734b4
                        charge(ctx, 7);
                        a0 = 1;
                        jal(ctx, 0x2734B8u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x2734C0u, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x002734d0
                            charge(ctx, 9);
                            a0 = 1;
                            jal(ctx, 0x2734D4u, gen::fn_msgWinClose_003c7650);
                            jal(ctx, 0x2734DCu, gen::fn_sub_24AA90_0024aa90);
                            v1 = 5;
                            sw(v1, s2, brpseq6::kEvolveStep);
                        }
                        break;
                    case 0x2734F4u:  // table[5]: substep 5
                        // 0x002734f4
                        charge(ctx, 4);
                        jal(ctx, 0x2734F4u, gen::fn_sub_24B9E0_0024b9e0);
                        if (v0 == 0) {
                            // 0x00273504
                            charge(ctx, 16);
                            jal(ctx, 0x273504u, gen::fn_sub_24AC90_0024ac90);
                            lw(v1, s2, brpseq::kFlags);
                            v0 = si(-65);
                            v0 = v1 & v0;
                            sw(v0, s2, brpseq::kFlags);
                            jal(ctx, 0x27351Cu, gen::fn_sub_2798F0_002798f0);
                            jal(ctx, 0x273524u, gen::fn_sub_276B10_00276b10);
                            jal(ctx, 0x27352Cu, gen::fn_sub_2768C0_002768c0);
                            v1 = 6;
                            sw(v1, s2, brpseq6::kEvolveStep);
                        }
                        break;
                    case 0x273544u:  // table[6]: substep 6
                        // 0x00273544
                        charge(ctx, 4);
                        jal(ctx, 0x273544u, gen::fn_sub_108710_00108710);
                        if (v0 != 0) {
                            // 0x00273554
                            charge(ctx, 4);
                            jal(ctx, 0x273554u, gen::fn_sub_273800_00273800);
                        }
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v1.u());
                        return;
                    }
                }
                break;
            case 0x273564u:  // table[4]: step 4, the skill power-up / change offer (+32)
                // 0x00273564
                charge(ctx, 4);
                lw(v1, s2, brpseq6::kChangeStep);
                a0 = 1;
                if (v1 == a0) {
                    // 0x00273738
                    charge(ctx, 6);
                    jal(ctx, 0x273738u, gen::fn_sub_3C7990_003c7990);
                    jal(ctx, 0x273740u, gen::fn_sub_3C7850_003c7850);
                    if (v0 == 0) {
                        // 0x00273750
                        charge(ctx, 5);
                        a0 = 1;
                        jal(ctx, 0x273754u, gen::fn_msgWinClose_003c7650);
                        jal(ctx, 0x27375Cu, gen::fn_sub_273800_00273800);
                    }
                } else {
                    // 0x00273574
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00273584
                        charge(ctx, 6);
                        jal(ctx, 0x273584u, gen::fn_sub_3C7990_003c7990);
                        jal(ctx, 0x27358Cu, gen::fn_sub_3C7850_003c7850);
                        if (v0 == 0) {
                            // 0x0027359c
                            charge(ctx, 8);
                            a0 = 1;
                            jal(ctx, 0x2735A0u, gen::fn_msgWinClose_003c7650);
                            jal(ctx, 0x2735A8u, gen::fn_msgWinLastSelection_003c7610);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x00273700
                                charge(ctx, 10);
                                lhu(a0, s2, brpseq::kPersona);
                                jal(ctx, 0x273704u, gen::fn_sub_173220_00173220);
                                a0 = 0;
                                a1 = v0;
                                jal(ctx, 0x273714u, gen::fn_sub_3C7BC0_003c7bc0);
                                a0 = 14;
                                jal(ctx, 0x273720u, gen::fn_msgWinRequestMessage_003c7430);
                            } else {
                                // 0x002735bc
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x002735cc
                                    charge(ctx, 3);
                                    lw(v0, s2, brpseq::kUpgradeKind);
                                    if (v0 == v1) {
                                        // 0x00273664
                                        charge(ctx, 29);
                                        lhu(v1, s2, brpseq::kUpgradeFrom);
                                        v0 = sll(v1, 3);
                                        v0 = addu(v0, v1);
                                        v0 = sll(v0, 1);
                                        v1 = addu(v0, v1);
                                        lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                                        a1 = addu(v0, v1);
                                        a0 = 0;
                                        jal(ctx, 0x273684u, gen::fn_sub_3C7BC0_003c7bc0);
                                        lhu(v1, s2, brpseq::kUpgradeTo);
                                        v0 = sll(v1, 3);
                                        v0 = addu(v0, v1);
                                        v0 = sll(v0, 1);
                                        v1 = addu(v0, v1);
                                        lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                                        a1 = addu(v0, v1);
                                        a0 = 1;
                                        jal(ctx, 0x2736ACu, gen::fn_sub_3C7BC0_003c7bc0);
                                        a0 = 16;
                                        jal(ctx, 0x2736B8u, gen::fn_msgWinRequestMessage_003c7430);
                                        a0 = 1;
                                        a1 = 0;
                                        a2 = 8;
                                        a3 = 3;
                                        jal(ctx, 0x2736D0u, gen::fn_sub_10A4E0_0010a4e0);
                                    } else {
                                        // 0x002735d8
                                        charge(ctx, 2);
                                        if (v0 == 0) {
                                            // 0x002735e8
                                            charge(ctx, 31);
                                            lhu(v1, s2, brpseq::kUpgradeFrom);
                                            v0 = sll(v1, 3);
                                            v0 = addu(v0, v1);
                                            v0 = sll(v0, 1);
                                            v1 = addu(v0, v1);
                                            lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                                            a1 = addu(v0, v1);
                                            a0 = 0;
                                            jal(ctx, 0x273608u, gen::fn_sub_3C7BC0_003c7bc0);
                                            lhu(v1, s2, brpseq::kUpgradeTo);
                                            v0 = sll(v1, 3);
                                            v0 = addu(v0, v1);
                                            v0 = sll(v0, 1);
                                            v1 = addu(v0, v1);
                                            lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
                                            a1 = addu(v0, v1);
                                            a0 = 1;
                                            jal(ctx, 0x273630u, gen::fn_sub_3C7BC0_003c7bc0);
                                            a0 = 15;
                                            jal(ctx, 0x27363Cu, gen::fn_msgWinRequestMessage_003c7430);
                                            a0 = 1;
                                            a1 = 0;
                                            a2 = 8;
                                            a3 = 3;
                                            jal(ctx, 0x273654u, gen::fn_sub_10A4E0_0010a4e0);
                                        } else {
                                            // 0x002735e0
                                            charge(ctx, 2);
                                        }
                                    }
                                    // 0x002736d8
                                    charge(ctx, 10);
                                    lw(a0, s2, brpseq::kRecord);
                                    lhu(a1, s2, brpseq::kUpgradeFrom);
                                    jal(ctx, 0x2736E0u, gen::fn_sub_1768E0_001768e0);
                                    lw(a0, s2, brpseq::kRecord);
                                    lhu(a1, s2, brpseq::kUpgradeTo);
                                    jal(ctx, 0x2736F0u, gen::fn_sub_176840_00176840);
                                } else {
                                    // 0x002735c4
                                    charge(ctx, 2);
                                }
                            }
                            // 0x00273728
                            charge(ctx, 4);
                            v1 = 1;
                            sw(v1, s2, brpseq6::kChangeStep);
                        }
                    } else {
                        // 0x0027357c
                        charge(ctx, 2);
                    }
                }
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
        // 0x00273764
        charge(ctx, 4);
        lw(v1, s2, brpseq::kFlags);
        v1 = v1 & 0x40;
        if (v1 != 0) {
            // 0x00273774
            charge(ctx, 2);
            jal(ctx, 0x273774u, gen::fn_sub_24ADF0_0024adf0);
        }
    }
    // 0x0027377c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x00273C00 sub_273C00 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeqStepSkills] Persona sequence: go to the new-skill step (K_Assert line 176): sub_279750, sound (1, 0, 8, 2),
// substep +24 = 0, step 3.
void sub_273C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00273c00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    if (v0 == 0) {
        // 0x00273c18
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x273C24u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00273c2c
    charge(ctx, 17);
    lw(s0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    jal(ctx, 0x273C30u, gen::fn_sub_279750_00279750);
    a0 = 1;
    a1 = 0;
    a2 = 8;
    a3 = 2;
    jal(ctx, 0x273C48u, gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, brpseq6::kSkillStep);
    v1 = 3;
    sw(v1, s0, brpseq::kStep);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00273C70 sub_273C70 -- 224 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeqStepEvolve] Persona sequence: go to the power-up offer step (K_Assert lines 176 / 1007): clears flag 0x10,
// the persona's name (sub_173220 of +4) into the message, message 8 with choice list 9 (type 0), sound (1, 0, 8, 4),
// substep +28 = 0, step 5.
void sub_273C70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00273c70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    if (v0 == 0) {
        // 0x00273c88
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x273C94u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00273c9c
    charge(ctx, 10);
    lw(s0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    lw(v1, s0, brpseq::kFlags);
    v0 = si(-17);
    v0 = v1 & v0;
    sw(v0, s0, brpseq::kFlags);
    lw(v0, s0, brpseq::kOwner);
    v0 = nor(v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00273cc4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 1007;
        jal(ctx, 0x273CD0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00273cd8
    charge(ctx, 30);
    lhu(a0, s0, brpseq::kPersona);
    jal(ctx, 0x273CDCu, gen::fn_sub_173220_00173220);
    a0 = 0;
    a1 = v0;
    jal(ctx, 0x273CECu, gen::fn_sub_3C7BC0_003c7bc0);
    a0 = 8;
    jal(ctx, 0x273CF8u, gen::fn_msgWinRequestMessage_003c7430);
    a0 = 9;
    jal(ctx, 0x273D04u, gen::fn_sub_3C74E0_003c74e0);
    a0 = 0;
    jal(ctx, 0x273D10u, gen::fn_msgWinSetType_003c7560);
    a0 = 1;
    a1 = 0;
    a2 = 8;
    a3 = 4;
    jal(ctx, 0x273D28u, gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, brpseq6::kEvolveStep);
    v1 = 5;
    sw(v1, s0, brpseq::kStep);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00273D50 sub_273D50 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeqStepChange] Persona sequence: go to the skill change step (K_Assert line 176): the persona's name and the
// skill name of +160 (the 19-byte skill name rows *0x7CE4EC) into the message, message 13 with choice list 9, clears
// flag 0x20, substep +32 = 0, step 4.
void sub_273D50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00273d50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    if (v0 == 0) {
        // 0x00273d68
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x273D74u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00273d7c
    charge(ctx, 36);
    lw(s0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    lhu(a0, s0, brpseq::kPersona);
    jal(ctx, 0x273D84u, gen::fn_sub_173220_00173220);
    a0 = 0;
    a1 = v0;
    jal(ctx, 0x273D94u, gen::fn_sub_3C7BC0_003c7bc0);
    lhu(v1, s0, brpseq::kUpgradeFrom);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v1 = addu(v0, v1);
    lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
    a1 = addu(v0, v1);
    a0 = 1;
    jal(ctx, 0x273DBCu, gen::fn_sub_3C7BC0_003c7bc0);
    a0 = 13;
    jal(ctx, 0x273DC8u, gen::fn_msgWinRequestMessage_003c7430);
    a0 = 9;
    jal(ctx, 0x273DD4u, gen::fn_sub_3C74E0_003c74e0);
    lw(a0, s0, brpseq::kFlags);
    v1 = si(-33);
    v1 = a0 & v1;
    sw(v1, s0, brpseq::kFlags);
    sw(zero, s0, brpseq6::kChangeStep);
    v1 = 4;
    sw(v1, s0, brpseq::kStep);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00274100 sub_274100 -- 228 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeqNextSkill] Persona sequence: the next new skill (K_Assert line 176): +432 counts; the learn-list views
// (sub_279120, sub_2792C0, sub_274C00, sub_279840); after the last (+436) the sequence moves on (sub_273800), else
// the next skill's step (as brpSeqStepSkills).
void sub_274100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00274100
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    if (v0 == 0) {
        // 0x00274118
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x274124u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027412c
    charge(ctx, 17);
    lw(s0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
    lw(v0, s0, brpseq::kWord432);
    v0 = addiu(v0, 1);
    sw(v0, s0, brpseq::kWord432);
    jal(ctx, 0x27413Cu, gen::fn_sub_279120_00279120);
    jal(ctx, 0x274144u, gen::fn_sub_2792C0_002792c0);
    jal(ctx, 0x27414Cu, gen::fn_sub_274C00_00274c00);
    jal(ctx, 0x274154u, gen::fn_sub_279840_00279840);
    lw(v1, s0, brpseq::kWord432);
    lw(v0, s0, brpseq::kNewSkillCount);
    at = slt(v1, v0);
    if (at == 0) {
        // 0x002741c8
        charge(ctx, 2);
        jal(ctx, 0x2741C8u, gen::fn_sub_273800_00273800);
    } else {
        // 0x00274170
        charge(ctx, 3);
        lw(v0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
        if (v0 == 0) {
            // 0x0027417c
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -4728);  // "brp_seq.c"
            a1 = 176;
            jal(ctx, 0x274188u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x00274190
        charge(ctx, 14);
        lw(s0, gp, kGpBrpSeq);  // the result screen persona sequence (brp_seq.c) 0x7CE3C0
        jal(ctx, 0x274194u, gen::fn_sub_279750_00279750);
        a0 = 1;
        a1 = 0;
        a2 = 8;
        a3 = 2;
        jal(ctx, 0x2741ACu, gen::fn_sub_10A4E0_0010a4e0);
        sw(zero, s0, brpseq6::kSkillStep);
        v1 = 3;
        sw(v1, s0, brpseq::kStep);
    }
    // 0x002741d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00275440 sub_275440 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpRootCreate] Creates the 'persona grow' screen (a script command, sub_3D3D20): a 17,680-byte work (RwMalloc)
// with the persona sequence (+0, sub_272330), the panel works +528 / +608 / +2176 / +2192 (sub_233970, sub_275A70,
// sub_276910, sub_276D10), the 'persona grow' task (update brpRootTaskUpdate) and its 'persona grow draw' task
// (priority 6315, brpRootTaskDraw); registers the work at $gp 0x7CE3C4.
void sub_275440(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00275440
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 17680;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x27545Cu, v0.u());
    s0 = v0;
    sw(zero, v0, 17664);
    a0 = s0;
    jal(ctx, 0x275470u, gen::fn_sub_272330_00272330);
    a0 = addiu(s0, 528);
    jal(ctx, 0x27547Cu, gen::fn_sub_233970_00233970);
    a0 = addiu(s0, 608);
    jal(ctx, 0x275488u, gen::fn_sub_275A70_00275a70);
    a0 = addiu(s0, 2176);
    jal(ctx, 0x275494u, gen::fn_sub_276910_00276910);
    a0 = addiu(s0, 2192);
    jal(ctx, 0x2754A0u, gen::fn_sub_276D10_00276d10);
    a0 = 0;
    a1 = 10;
    a2 = 0x690000;
    a2 = addiu(a2, -4424);  // "persona grow"
    a3 = 0x270000;
    a3 = addiu(a3, 22208);  // &sub_2756C0
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x2754C8u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    sw(v0, s0, 17668);
    a0 = 0x690000;
    a0 = addiu(a0, -4400);  // "persona grow draw"
    a1 = 6315;
    a2 = 1;
    a3 = 2;
    t0 = 0x270000;
    t0 = addiu(t0, 22432);  // &sub_2757A0
    t1 = 0;
    t2 = 0;
    jal(ctx, 0x2754F8u, gen::fn_kwlnTaskInitEx_00194e10);
    sw(v0, s0, 17672);
    sw(s0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00275520 sub_275520 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpRootDestroy] Destroys the 'persona grow' screen (brp_root.c; K_Assert line 70): the persona status, sequence
// and panels (sub_276C30, sub_272380, sub_233E70, sub_275A80, sub_276920, sub_276D30), both tasks, the work, the $gp
// slot.
void sub_275520(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00275520
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    if (v0 == 0) {
        // 0x00275538
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4440);  // "brp_root.c"
        a1 = 70;
        jal(ctx, 0x275544u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027554c
    charge(ctx, 30);
    lw(s0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    jal(ctx, 0x275550u, gen::fn_sub_276C30_00276c30);
    jal(ctx, 0x275558u, gen::fn_sub_272380_00272380);
    jal(ctx, 0x275560u, gen::fn_sub_233E70_00233e70);
    jal(ctx, 0x275568u, gen::fn_sub_275A80_00275a80);
    jal(ctx, 0x275570u, gen::fn_sub_276920_00276920);
    jal(ctx, 0x275578u, gen::fn_sub_276D30_00276d30);
    lw(a0, s0, brproot::kTask);
    jal(ctx, 0x275584u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    lw(a0, s0, brproot::kDrawTask);
    jal(ctx, 0x275590u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x2755A4u, v0.u());
    sw(zero, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002755D0 sub_2755D0 -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpRootStart] Starts the 'persona grow' screen for the start block a0 (K_Assert line 70): the panels (sub_275A90,
// sub_277070), the sequence (sub_272400(a0)), sub_276D90, the ADX SOUND2\EVENT\EVE_530.ADX on channel 3 (sub_10A370),
// flags 1 | 2.
// Arguments: a0 the start block.
void sub_2755D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002755d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    if (v0 == 0) {
        // 0x002755f0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4440);  // "brp_root.c"
        a1 = 70;
        jal(ctx, 0x2755FCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00275604
    charge(ctx, 26);
    lw(s0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    jal(ctx, 0x275608u, gen::fn_sub_275A90_00275a90);
    jal(ctx, 0x275610u, gen::fn_sub_277070_00277070);
    a0 = s1;
    jal(ctx, 0x27561Cu, gen::fn_sub_272400_00272400);
    jal(ctx, 0x275624u, gen::fn_sub_276D90_00276d90);
    a0 = 3;
    a1 = 0x690000;
    a1 = addiu(a1, -4368);  // "SOUND2\\EVENT\\EVE_530.ADX"
    jal(ctx, 0x275638u, gen::fn_sub_10A370_0010a370);
    lw(v1, s0, brproot::kFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, brproot::kFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, brproot::kFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00275670 sub_275670 -- 68 bytes; frame 0x10: ra sp+0x0
// [brpRootIsRunning] Nonzero while the 'persona grow' screen runs (flag 1 of +17664; K_Assert line 70).
void sub_275670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00275670
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    if (v0 == 0) {
        // 0x00275684
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4440);  // "brp_root.c"
        a1 = 70;
        jal(ctx, 0x275690u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00275698 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    lw(v0, v0, brproot::kFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002756C0 sub_2756C0 -- 216 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpRootTaskUpdate] Update callback of the 'persona grow' task: the panel updates (sub_234070, sub_275BC0), the
// persona sequence (brpSeqUpdate), sub_276930, sub_2770F0; the music flag 2 clears once the sequence is done with it
// (sub_275370 -> sub_2753C0), the running flag 1 once sub_2727C0 says so; returns 0.
void sub_2756C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002756c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    if (v0 == 0) {
        // 0x002756d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4440);  // "brp_root.c"
        a1 = 70;
        jal(ctx, 0x2756E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002756ec
    charge(ctx, 15);
    lw(s0, gp, kGpBrpRoot);  // the 'persona grow' screen (brp_root.c) 0x7CE3C4
    jal(ctx, 0x2756F0u, gen::fn_sub_234070_00234070);
    jal(ctx, 0x2756F8u, gen::fn_sub_275BC0_00275bc0);
    jal(ctx, 0x275700u, gen::fn_sub_272810_00272810);
    jal(ctx, 0x275708u, gen::fn_sub_276930_00276930);
    jal(ctx, 0x275710u, gen::fn_sub_2770F0_002770f0);
    lw(v0, s0, brproot::kFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00275728
        charge(ctx, 4);
        jal(ctx, 0x275728u, gen::fn_sub_275370_00275370);
        if (v0 == 0) {
            // 0x00275738
            charge(ctx, 6);
            jal(ctx, 0x275738u, gen::fn_sub_2753C0_002753c0);
            lw(v1, s0, brproot::kFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s0, brproot::kFlags);
        }
    }
    // 0x00275750
    charge(ctx, 4);
    lw(v0, s0, brproot::kFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00275760
        charge(ctx, 4);
        jal(ctx, 0x275760u, gen::fn_sub_2727C0_002727c0);
        if (v0 == 0) {
            // 0x00275770
            charge(ctx, 4);
            lw(v1, s0, brproot::kFlags);
            v0 = si(-2);
            v0 = v1 & v0;
            sw(v0, s0, brproot::kFlags);
        }
    }
    // 0x00275780 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002757A0 sub_2757A0 -- 64 bytes; frame 0x10: ra sp+0x0
// [brpRootTaskDraw] Draw callback of the 'persona grow' task: printf('%x', *0x960070), sub_275CB0, the parameter
// panel's draw (brpParamDraw); returns 0.
void sub_2757A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002757a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = addiu(gp, -26648);  // "%x\n"
    v0 = 0x960000;
    lw(a1, v0, 112);  // 0x960070
    jal(ctx, 0x2757B4u, gen::fn_printf_005225a8);
    jal(ctx, 0x2757BCu, gen::fn_sub_275CB0_00275cb0);
    jal(ctx, 0x2757C4u, gen::fn_sub_278550_00278550);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002757E0 sub_2757E0 -- 252 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpRootLoadPack] Installs the 'persona grow' screen's resource pack a0 (K_Assert line 201: 3 entries): entry 0
// (sub_234710 with its size), entries 1 / 2 (sub_234690 0 / 1) by their offsets +8 / +16 / +24.
// Arguments: a0 the pack.
void sub_2757E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002757e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lhu(a0, a0, 4);
    v1 = 3;
    if (a0 != v1) {
        // 0x00275804
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4440);  // "brp_root.c"
        a1 = 201;
        jal(ctx, 0x275810u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00275818
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x002758b8
        charge(ctx, 3);
        v1 = slti(s0, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00275824
        charge(ctx, 3);
        v1 = 2;
        if (s0 == v1) {
            // 0x00275898
            charge(ctx, 7);
            v0 = sll(s0, 3);
            v0 = addu(v0, s1);
            lw(v0, v0, 8);
            a1 = addu(s1, v0);
            a0 = 1;
            jal(ctx, 0x2758ACu, gen::fn_sub_234690_00234690);
        } else {
            // 0x00275830
            charge(ctx, 3);
            v1 = 1;
            if (s0 == v1) {
                // 0x00275874
                charge(ctx, 9);
                v0 = sll(s0, 3);
                v0 = addu(v0, s1);
                lw(v0, v0, 8);
                a1 = addu(s1, v0);
                a0 = 0;
                jal(ctx, 0x275888u, gen::fn_sub_234690_00234690);
            } else {
                // 0x0027583c
                charge(ctx, 2);
                if (s0 == 0) {
                    // 0x0027584c
                    charge(ctx, 10);
                    v1 = addiu(s1, 8);
                    v0 = sll(s0, 3);
                    v1 = addu(v1, v0);
                    lw(v0, v1, 0);
                    a0 = addu(s1, v0);
                    lw(a1, v1, 4);
                    jal(ctx, 0x275864u, gen::fn_sub_234710_00234710);
                } else {
                    // 0x00275844
                    charge(ctx, 2);
                }
            }
        }
        // 0x002758b4
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x002758c4
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002758E0 sub_2758E0 -- 396 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpRootFillParams] Fills the 'persona grow' screen's parameter panel for persona a1: sub_2769C0, sub_276BA0; its
// record (sub_1749A0): the skills (sub_176A30 count, sub_173370 list) into sub_2791B0, the next skill to learn
// (sub_1FB1F0, sub_1FC230 / sub_1FC3C0 -> sub_279330 / sub_279450), the shown count (sub_2794C0), the five stats
// (sub_173580 -> sub_279510 / sub_279580 / sub_2795F0), sub_276D90.
// Arguments: a0, a1 persona id.
void sub_2758E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002758e0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x2758F8u, gen::fn_sub_2769C0_002769c0);
    jal(ctx, 0x275900u, gen::fn_sub_276BA0_00276ba0);
    a0 = s0;
    jal(ctx, 0x27590Cu, gen::fn_sub_1749A0_001749a0);
    s1 = v0;
    a0 = s1;
    jal(ctx, 0x27591Cu, gen::fn_sub_176A30_00176a30);
    sw(v0, sp, 0x5C);
    a0 = s1;
    jal(ctx, 0x27592Cu, gen::fn_sub_173370_00173370);
    s0 = v0;
    s2 = 0;
    for (;;) {
        // 0x0027595c
        charge(ctx, 4);
        lw(v0, sp, 0x5C);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00275944
        charge(ctx, 6);
        v0 = sll(s2, 1);
        v0 = addu(s0, v0);
        lhu(a0, v0, 0);
        jal(ctx, 0x275950u, gen::fn_sub_2791B0_002791b0);
        s2 = addiu(s2, 1);
    }
    // 0x0027596c
    charge(ctx, 10);
    a0 = s1;
    a1 = addiu(sp, 0x40);
    a2 = addiu(sp, 0x5C);
    jal(ctx, 0x275978u, gen::fn_sub_1FB1F0_001fb1f0);
    a0 = s1;
    jal(ctx, 0x275984u, gen::fn_sub_1FC230_001fc230);
    if (v0 != 0) {
        // 0x00275994
        charge(ctx, 9);
        lhu(a0, sp, 0x40);
        jal(ctx, 0x275998u, gen::fn_sub_279330_00279330);
        a0 = s1;
        jal(ctx, 0x2759A4u, gen::fn_sub_1FC3C0_001fc3c0);
        a0 = v0;
        jal(ctx, 0x2759B0u, gen::fn_sub_279450_00279450);
    }
    // 0x002759b8
    charge(ctx, 4);
    lw(v0, sp, 0x5C);
    at = slti(v0, 2);
    if (at != 0) {
        // 0x002759dc
        charge(ctx, 3);
        a0 = 0;
        jal(ctx, 0x2759E0u, gen::fn_sub_2794C0_002794c0);
    } else {
        // 0x002759c8
        charge(ctx, 5);
        a0 = addiu(v0, -1);
        jal(ctx, 0x2759CCu, gen::fn_sub_2794C0_002794c0);
    }
    // 0x002759e8
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00275a3c
        charge(ctx, 3);
        v0 = slti(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002759f4
        charge(ctx, 18);
        a1 = s0 & 0xFFFF;
        a0 = s1;
        jal(ctx, 0x2759FCu, gen::fn_sub_173580_00173580);
        s2 = v0 & 0xFF;
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x275A10u, gen::fn_sub_279510_00279510);
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x275A20u, gen::fn_sub_279580_00279580);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x275A30u, gen::fn_sub_2795F0_002795f0);
        s0 = addiu(s0, 1);
    }
    // 0x00275a48
    charge(ctx, 9);
    jal(ctx, 0x275A48u, gen::fn_sub_276D90_00276d90);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002768C0 sub_2768C0 -- 76 bytes; frame 0x10: ra sp+0x0
// [brLvPanelClearFlag8] Clears flag 8 of the result screen level panel (br_lvpnl.c, *$gp 0x7CE3C8; K_Assert line 59).
void sub_2768C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002768c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrLvPanel);  // the result screen level panel (br_lvpnl.c) 0x7CE3C8
    if (v1 == 0) {
        // 0x002768d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4336);  // "br_lvpnl.c"
        a1 = 59;
        jal(ctx, 0x2768E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002768e8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBrLvPanel);  // the result screen level panel (br_lvpnl.c) 0x7CE3C8
    lw(a0, a1, lvpnl::kFlags);
    v1 = si(-9);
    v1 = a0 & v1;
    sw(v1, a1, lvpnl::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00276A80 sub_276A80 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpPersonaShowPage] Shows the result screen persona status page 16 (brp_persona.c, *$gp 0x7CE3CC; K_Assert lines
// 37 / 89: open): sub_3C9D00(16), flag 4.
void sub_276A80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00276a80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpPersona);  // the result screen persona status (brp_persona.c) 0x7CE3CC
    if (v0 == 0) {
        // 0x00276a98
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 37;
        jal(ctx, 0x276AA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276aac
    charge(ctx, 5);
    lw(s0, gp, kGpBrpPersona);  // the result screen persona status (brp_persona.c) 0x7CE3CC
    lw(v0, s0, brppersona::kFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00276ac0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 89;
        jal(ctx, 0x276ACCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276ad4
    charge(ctx, 12);
    lw(a0, s0, brppersona::kStatus);
    a1 = 16;
    jal(ctx, 0x276ADCu, gen::fn_sub_3C9D00_003c9d00);
    lw(v1, s0, brppersona::kFlags);
    v1 = v1 | 0x4;
    sw(v1, s0, brppersona::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00276B10 sub_276B10 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpPersonaShowMain] Back to the result screen persona status page 8 (K_Assert lines 37 / 98): sub_3C9D00(8), flag
// 4 cleared.
void sub_276B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00276b10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpPersona);  // the result screen persona status (brp_persona.c) 0x7CE3CC
    if (v0 == 0) {
        // 0x00276b28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 37;
        jal(ctx, 0x276B34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276b3c
    charge(ctx, 5);
    lw(s0, gp, kGpBrpPersona);  // the result screen persona status (brp_persona.c) 0x7CE3CC
    lw(v0, s0, brppersona::kFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00276b50
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 98;
        jal(ctx, 0x276B5Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276b64
    charge(ctx, 13);
    lw(a0, s0, brppersona::kStatus);
    a1 = 8;
    jal(ctx, 0x276B6Cu, gen::fn_sub_3C9D00_003c9d00);
    lw(a0, s0, brppersona::kFlags);
    v1 = si(-5);
    v1 = a0 & v1;
    sw(v1, s0, brppersona::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00276C30 sub_276C30 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpPersonaClose] Closes the result screen persona status (K_Assert lines 37 / 116): sub_3C9D80(2), flag 2 cleared.
void sub_276C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00276c30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpPersona);  // the result screen persona status (brp_persona.c) 0x7CE3CC
    if (v0 == 0) {
        // 0x00276c48
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 37;
        jal(ctx, 0x276C54u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276c5c
    charge(ctx, 5);
    lw(s0, gp, kGpBrpPersona);  // the result screen persona status (brp_persona.c) 0x7CE3CC
    lw(v0, s0, brppersona::kFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00276c70
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 116;
        jal(ctx, 0x276C7Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276c84
    charge(ctx, 13);
    lw(a0, s0, brppersona::kStatus);
    a1 = 2;
    jal(ctx, 0x276C8Cu, gen::fn_sub_3C9D80_003c9d80);
    lw(a0, s0, brppersona::kFlags);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, brppersona::kFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002771F0 sub_2771F0 -- 4952 bytes; frame 0xB0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [brpParamLayout] Lays out the result screen's parameter panel (brp_param.c, *$gp 0x7CE3D0; K_Assert line 97): the
// frame quads (textures 21 / 23), the eight skill cells (272 bytes from +16, two columns of four) and their name
// lines, the new-skill line (flag 2) blinking by the frame (+0x10: 5 / 10 / 20 / 30 frame steps) at (424, 338), the
// stat bars and numbers (sub_238DC0), the evolution marks (sin pulse), through sub_21D8E0 / sub_21D950 /
// frFontLineSetPos / frFontLineSetRgba.
void sub_2771F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x002771f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBrpParam);  // the result screen parameter panel (brp_param.c) 0x7CE3D0
    if (v0 == 0) {
        // 0x00277228
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x277234u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027723c
    charge(ctx, 116);
    lw(s1, gp, kGpBrpParam);  // the result screen parameter panel (brp_param.c) 0x7CE3D0
    a0 = 8;
    jal(ctx, 0x277244u, gen::fn_sub_119A60_00119a60);
    s2 = v0;
    a0 = 10;
    jal(ctx, 0x277254u, gen::fn_sub_119A60_00119a60);
    s4 = v0;
    a0 = 1;
    jal(ctx, 0x277264u, gen::fn_sub_234630_00234630);
    s5 = v0;
    v0 = 411;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x80);
    v0 = 0x43A30000;
    sw(v0, sp, 0x84);
    a0 = s2;
    a1 = 21;
    jal(ctx, 0x277294u, gen::fn_sub_260900_00260900);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    a0 = s2;
    a1 = 21;
    jal(ctx, 0x2772B4u, gen::fn_sub_260920_00260920);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 11568);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x2772D4u, gen::fn_sub_21D8E0_0021d8e0);
    a0 = s2;
    a1 = 21;
    jal(ctx, 0x2772E4u, gen::fn_sub_260900_00260900);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 411;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x80);
    v0 = 0x43A30000;
    sw(v0, sp, 0x84);
    v0 = 0x41F80000;
    sw(v0, sp, 0x88);
    a0 = s2;
    a1 = 21;
    jal(ctx, 0x277328u, gen::fn_sub_260920_00260920);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 11824);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x277348u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 557;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x80);
    v0 = 0x43A30000;
    sw(v0, sp, 0x84);
    a0 = s2;
    a1 = 23;
    jal(ctx, 0x277374u, gen::fn_sub_260900_00260900);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    a0 = s2;
    a1 = 23;
    jal(ctx, 0x277394u, gen::fn_sub_260920_00260920);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 12080);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x2773B4u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0xAC);
    sb(v0, sp, 0xAD);
    sb(v0, sp, 0xAE);
    sb(v0, sp, 0xAF);
    a0 = addiu(s1, 11568);
    a1 = addiu(sp, 0xAC);
    jal(ctx, 0x2773D8u, gen::fn_sub_21D950_0021d950);
    a0 = addiu(s1, 11824);
    a1 = addiu(sp, 0xAC);
    jal(ctx, 0x2773E8u, gen::fn_sub_21D950_0021d950);
    a0 = addiu(s1, 12080);
    a1 = addiu(sp, 0xAC);
    jal(ctx, 0x2773F8u, gen::fn_sub_21D950_0021d950);
    s0 = 0;
    for (;;) {
        // 0x00277524
        charge(ctx, 3);
        v0 = slti(s0, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027740c
        charge(ctx, 8);
        v0 = sll(s0, 4);
        v0 = addu(v0, s0);
        v0 = sll(v0, 4);
        v0 = addu(s1, v0);
        s3 = addiu(v0, 16);
        v0 = sra(s0, 2);
        if (i64(s0) < 0) {
            // 0x0027742c
            charge(ctx, 2);
            v0 = addiu(s0, 3);
            v0 = sra(v0, 2);
        }
        // 0x00277434
        charge(ctx, 14);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        v0 = 0x433E0000;
        mtc1(v0, f2);
        v0 = 0x42080000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f4, f2, f3);
        v0 = s0 & 0x3;
        if (i64(s0) < 0) {
            // 0x0027746c
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00277474
                charge(ctx, 1);
                v0 = addiu(v0, -4);
            }
        }
        // 0x00277478
        charge(ctx, 43);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        v0 = 0x41C00000;
        mtc1(v0, f2);
        v0 = 0x439E0000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f0, f2, f3);
        swc1(f4, sp, 0x80);
        swc1(f0, sp, 0x84);
        a0 = s2;
        a1 = 18;
        jal(ctx, 0x2774B4u, gen::fn_sub_260900_00260900);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        a0 = s2;
        a1 = 18;
        jal(ctx, 0x2774D4u, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = s3;
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x2774F4u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        a0 = s3;
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277518u, gen::fn_sub_21D950_0021d950);
        s0 = addiu(s0, 1);
    }
    // 0x00277530
    charge(ctx, 10);
    v0 = 199;
    sb(v0, sp, 0xAC);
    v0 = 185;
    sb(v0, sp, 0xAD);
    v0 = 255;
    sb(v0, sp, 0xAE);
    sb(v0, sp, 0xAF);
    s0 = 0;
    for (;;) {
        // 0x00277680
        charge(ctx, 4);
        lw(v0, s1, brpparam::kSkillCount);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00277558
        charge(ctx, 8);
        v0 = sll(s0, 4);
        v0 = addu(v0, s0);
        v0 = sll(v0, 4);
        v0 = addu(s1, v0);
        s3 = addiu(v0, 16);
        v0 = sra(s0, 2);
        if (i64(s0) < 0) {
            // 0x00277578
            charge(ctx, 2);
            v0 = addiu(s0, 3);
            v0 = sra(v0, 2);
        }
        // 0x00277580
        charge(ctx, 14);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        v0 = 0x433E0000;
        mtc1(v0, f2);
        v0 = 0x42080000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f4, f2, f3);
        v0 = s0 & 0x3;
        if (i64(s0) < 0) {
            // 0x002775b8
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x002775c0
                charge(ctx, 1);
                v0 = addiu(v0, -4);
            }
        }
        // 0x002775c4
        charge(ctx, 47);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        v0 = 0x41C00000;
        mtc1(v0, f2);
        v0 = 315;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f2, f2, f3);
        v0 = 0x41800000;
        mtc1(v0, f1);
        v0 = 0x41200000;
        mtc1(v0, f0);
        add_s(f0, f0, f4);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        lwc1(f0, gp, -32636);  // 0x7CAD74
        sub_s(f1, f2, f0);
        v0 = 0x41000000;
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        lw(a0, s3, 256);
        jal(ctx, 0x277640u, gen::fn_frFontLineSetPos_003b0d70);
        lbu(v0, sp, 0xAC);
        v1 = sll(v0, 24);
        lbu(v0, sp, 0xAD);
        v0 = sll(v0, 16);
        v1 = v1 | v0;
        lbu(v0, sp, 0xAE);
        v0 = sll(v0, 8);
        v1 = v0 | v1;
        lbu(v0, sp, 0xAF);
        a1 = v0 | v1;
        lw(a0, s3, 256);
        jal(ctx, 0x277674u, gen::fn_frFontLineSetRgba_003b0e20);
        s0 = addiu(s0, 1);
    }
    // 0x00277690
    charge(ctx, 4);
    lw(v1, s1, brpparam::kFlags);
    v0 = v1 & 0x2;
    if (v0 != 0) {
        // 0x002776a0
        charge(ctx, 3);
        v0 = v1 & 0x10;
        if (v0 == 0) {
            // 0x00277774
            charge(ctx, 1);
            mtc1(zero, f20);
        } else {
            // 0x002776ac
            charge(ctx, 4);
            lw(v0, s1, brpparam::kBlinkFrame);
            at = slti(v0, 5);
            if (at == 0) {
                // 0x002776c8
                charge(ctx, 3);
                at = slti(v0, 10);
                if (at == 0) {
                    // 0x00277708
                    charge(ctx, 3);
                    at = slti(v0, 20);
                    if (at == 0) {
                        // 0x00277724
                        charge(ctx, 3);
                        at = slti(v0, 30);
                        if (at == 0) {
                            // 0x00277768
                            charge(ctx, 3);
                            mtc1(zero, f20);
                        } else {
                            // 0x00277730
                            charge(ctx, 14);
                            v0 = addiu(v0, -20);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x41200000;
                            mtc1(v0, f0);
                            div_s(f1, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            sub_s(f20, f0, f1);
                        }
                    } else {
                        // 0x00277714
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f20);
                    }
                } else {
                    // 0x002776d4
                    charge(ctx, 13);
                    v0 = addiu(v0, -5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40A00000;
                    mtc1(v0, f0);
                    div_s(f20, f1, f0);
                }
            } else {
                // 0x002776bc
                charge(ctx, 3);
                mtc1(zero, f20);
            }
        }
        // 0x00277778
        charge(ctx, 27);
        v0 = 0x45D40000;
        mtc1(v0, f0);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = 0x45290000;
        mtc1(v0, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        lw(a0, s1, brpparam::kNewSkillLine);
        jal(ctx, 0x2777A4u, gen::fn_frFontLineSetPos_003b0d70);
        v0 = 0x425C0000;
        mtc1(v0, f2);
        v0 = 0x43470000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f1, f20, f2);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x002777fc
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002777e4
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00277814
        charge(ctx, 15);
        sb(v1, sp, 0xAC);
        v0 = 0x428C0000;
        mtc1(v0, f2);
        v0 = 0x43390000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f1, f20, f2);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x00277868
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00277850
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00277880
        charge(ctx, 15);
        sb(v1, sp, 0xAD);
        v0 = lui(0xC2BE);
        mtc1(v0, f2);
        v0 = 0x437F0000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f1, f20, f2);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x002778d4
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x002778bc
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x002778ec
        charge(ctx, 13);
        sb(v1, sp, 0xAE);
        mtc1(zero, f1);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        adda_s(f1, f0);
        madd_s(f1, f20, f1);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x00277938
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00277920
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00277950
        charge(ctx, 54);
        sb(v1, sp, 0xAF);
        lbu(v0, sp, 0xAC);
        v1 = sll(v0, 24);
        lbu(v0, sp, 0xAD);
        v0 = sll(v0, 16);
        v1 = v1 | v0;
        lbu(v0, sp, 0xAE);
        v0 = sll(v0, 8);
        v1 = v0 | v1;
        lbu(v0, sp, 0xAF);
        a1 = v0 | v1;
        lw(a0, s1, brpparam::kNewSkillLine);
        jal(ctx, 0x277980u, gen::fn_frFontLineSetRgba_003b0e20);
        v0 = 0x43CF0000;
        sw(v0, sp, 0x80);
        v0 = 343;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x84);
        a0 = s2;
        a1 = 19;
        jal(ctx, 0x2779ACu, gen::fn_sub_260900_00260900);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        a0 = s2;
        a1 = 19;
        jal(ctx, 0x2779CCu, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s1, 11312);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x2779ECu, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        a0 = addiu(s1, 11312);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277A10u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, brpparam::kFlags);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            // 0x00277af0
            charge(ctx, 1);
            mtc1(zero, f22);
        } else {
            // 0x00277a28
            charge(ctx, 4);
            lw(v0, s1, brpparam::kBlinkFrame);
            at = slti(v0, 5);
            if (at == 0) {
                // 0x00277a44
                charge(ctx, 3);
                at = slti(v0, 10);
                if (at == 0) {
                    // 0x00277a84
                    charge(ctx, 3);
                    at = slti(v0, 20);
                    if (at == 0) {
                        // 0x00277aa0
                        charge(ctx, 3);
                        at = slti(v0, 30);
                        if (at == 0) {
                            // 0x00277ae4
                            charge(ctx, 3);
                            mtc1(zero, f22);
                        } else {
                            // 0x00277aac
                            charge(ctx, 14);
                            v0 = addiu(v0, -20);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x41200000;
                            mtc1(v0, f0);
                            div_s(f1, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            sub_s(f22, f0, f1);
                        }
                    } else {
                        // 0x00277a90
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f22);
                    }
                } else {
                    // 0x00277a50
                    charge(ctx, 13);
                    v0 = addiu(v0, -5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40A00000;
                    mtc1(v0, f0);
                    div_s(f22, f1, f0);
                }
            } else {
                // 0x00277a38
                charge(ctx, 3);
                mtc1(zero, f22);
            }
        }
        // 0x00277af4
        charge(ctx, 38);
        a0 = s5;
        a1 = 1;
        jal(ctx, 0x277AFCu, gen::fn_sub_21CCA0_0021cca0);
        v1 = 407;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x80);
        v1 = 319;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x84);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s1, 14688);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x277B4Cu, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f20, f0, f22);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x00277ba4
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00277b8c
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00277bbc
        charge(ctx, 39);
        sb(v1, sp, 0xAF);
        a0 = addiu(s1, 14688);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277BC8u, gen::fn_sub_21D950_0021d950);
        a0 = s5;
        a1 = 0;
        jal(ctx, 0x277BD8u, gen::fn_sub_21CCA0_0021cca0);
        v1 = 405;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x80);
        v1 = 333;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x84);
        lwc1(f0, v0, 12);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        lwc1(f0, v0, 16);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s1, 14944);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x277C28u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f20);
        if (cond(ctx)) {
            // 0x00277c70
            charge(ctx, 6);
            sub_s(f0, f20, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x00277c58
            charge(ctx, 6);
            cvt_w_s(f0, f20);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x00277c88
        charge(ctx, 5);
        sb(v1, sp, 0xAF);
        a0 = addiu(s1, 14944);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277C94u, gen::fn_sub_21D950_0021d950);
    }
    // 0x00277c9c
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00277db8
        charge(ctx, 4);
        lw(v0, s1, brpparam::kStatCount);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00277ca8
        charge(ctx, 3);
        v0 = sra(s0, 1);
        if (i64(s0) < 0) {
            // 0x00277cb4
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            v0 = sra(v0, 1);
        }
        // 0x00277cbc
        charge(ctx, 14);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        v0 = 0x42780000;
        mtc1(v0, f2);
        v0 = 0x43CF0000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f4, f2, f3);
        v0 = s0 & 0x1;
        if (i64(s0) < 0) {
            // 0x00277cf4
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00277cfc
                charge(ctx, 1);
                v0 = addiu(v0, -2);
            }
        }
        // 0x00277d00
        charge(ctx, 46);
        mtc1(v0, f0);
        cvt_s_w(f3, f0);
        v0 = 0x41C00000;
        mtc1(v0, f2);
        v0 = 0x43B70000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f0, f2, f3);
        swc1(f4, sp, 0x80);
        swc1(f0, sp, 0x84);
        a0 = s2;
        a1 = 20;
        jal(ctx, 0x277D3Cu, gen::fn_sub_260900_00260900);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        a0 = s2;
        a1 = 20;
        jal(ctx, 0x277D5Cu, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        s3 = addiu(v0, 12336);
        a0 = s3;
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x277D88u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        a0 = s3;
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277DACu, gen::fn_sub_21D950_0021d950);
        s0 = addiu(s0, 1);
    }
    // 0x00277dc8
    charge(ctx, 22);
    v0 = 526;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x80);
    v0 = 0x43A40000;
    sw(v0, sp, 0x84);
    a0 = addiu(s1, 14160);
    a1 = 2;
    lw(a2, s1, brpparam::kWord14132);
    a3 = a1;
    t0 = addiu(sp, 0x80);
    jal(ctx, 0x277DF8u, gen::fn_sub_238DC0_00238dc0);
    v0 = 255;
    sb(v0, sp, 0xAC);
    sb(v0, sp, 0xAD);
    sb(v0, sp, 0xAE);
    sb(v0, sp, 0xAF);
    s0 = 0;
    for (;;) {
        // 0x00277e3c
        charge(ctx, 3);
        v0 = slti(s0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00277e20
        charge(ctx, 7);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 14160);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277E30u, gen::fn_sub_21D950_0021d950);
        s0 = addiu(s0, 1);
    }
    // 0x00277e48
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x00278454
        charge(ctx, 3);
        v0 = slti(s2, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00277e54
        charge(ctx, 148);
        v0 = sll(s2, 3);
        v0 = subu(v0, s2);
        v0 = sll(v0, 3);
        v0 = addu(v0, s2);
        v0 = sll(v0, 5);
        v0 = addu(s1, v0);
        s0 = addiu(v0, 2192);
        v0 = 0x42D00000;
        sw(v0, sp, 0x80);
        v0 = 0x41980000;
        mtc1(v0, f1);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
        mul_s(f21, f1, f0);
        v0 = 0x43010000;
        mtc1(v0, f0);
        add_s(f1, f0, f21);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        sub_s(f20, f1, f0);
        swc1(f20, sp, 0x84);
        a0 = s4;
        a1 = 20;
        jal(ctx, 0x277EBCu, gen::fn_sub_260900_00260900);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        a0 = s4;
        a1 = 20;
        jal(ctx, 0x277EDCu, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32100);  // 0x7CAF8C
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s0, 1056);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x277F04u, gen::fn_sub_21D8E0_0021d8e0);
        a0 = s4;
        a1 = 20;
        jal(ctx, 0x277F14u, gen::fn_sub_260900_00260900);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x42D00000;
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x80);
        swc1(f20, sp, 0x84);
        v0 = 0x435C0000;
        sw(v0, sp, 0x88);
        a0 = s4;
        a1 = 20;
        jal(ctx, 0x277F50u, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32100);  // 0x7CAF8C
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s0, 1312);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x277F78u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        a0 = addiu(s0, 1056);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277F9Cu, gen::fn_sub_21D950_0021d950);
        a0 = addiu(s0, 1312);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x277FACu, gen::fn_sub_21D950_0021d950);
        lwc1(f0, gp, -31908);  // 0x7CB04C
        swc1(f0, sp, 0x80);
        swc1(f20, sp, 0x84);
        a0 = s4;
        a1 = 21;
        jal(ctx, 0x277FC8u, gen::fn_sub_260900_00260900);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x88);
        a0 = s4;
        a1 = 21;
        jal(ctx, 0x277FE8u, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32100);  // 0x7CAF8C
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s0, 1568);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x278010u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        a0 = addiu(s0, 1568);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x278034u, gen::fn_sub_21D950_0021d950);
        v0 = 0x428A0000;
        sw(v0, sp, 0x80);
        v0 = 0x43030000;
        mtc1(v0, f0);
        add_s(f1, f0, f21);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x84);
        a0 = addiu(s0, 16);
        a1 = 2;
        lw(a2, s0, 0);
        a3 = a1;
        t0 = addiu(sp, 0x80);
        jal(ctx, 0x27807Cu, gen::fn_sub_238DC0_00238dc0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        s3 = 0;
        for (;;) {
            // 0x002780c0
            charge(ctx, 3);
            v0 = slti(s3, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002780a4
            charge(ctx, 7);
            v0 = sll(s3, 8);
            v0 = addu(s0, v0);
            a0 = addiu(v0, 16);
            a1 = addiu(sp, 0xAC);
            jal(ctx, 0x2780B4u, gen::fn_sub_21D950_0021d950);
            s3 = addiu(s3, 1);
        }
        // 0x002780cc
        charge(ctx, 4);
        lw(v1, s0, 528);
        v0 = 99;
        if (v1 == v0) {
            // 0x002780f8
            charge(ctx, 4);
            v0 = 0x43650000;
            mtc1(v0, f1);
        } else {
            // 0x002780dc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002780ec
                charge(ctx, 3);
                mtc1(zero, f1);
            } else {
                // 0x002780e4
                charge(ctx, 2);
                // 0x00278108
                charge(ctx, 14);
                v0 = 0x43610000;
                mtc1(v0, f1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                mul_s(f1, f1, f0);
                v0 = 0x42C40000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x40000000;
                mtc1(v0, f0);
                add_s(f1, f0, f1);
            }
        }
        // 0x00278140
        charge(ctx, 40);
        v0 = 0x42D80000;
        sw(v0, sp, 0x80);
        v0 = 0x42D20000;
        mtc1(v0, f0);
        add_s(f20, f0, f21);
        swc1(f20, sp, 0x84);
        swc1(f1, sp, 0x88);
        a0 = s4;
        a1 = 24;
        jal(ctx, 0x278168u, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s0, 544);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x278188u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 0xFFFF;
        mtc1(v0, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s0, 544);
        jal(ctx, 0x2781A4u, gen::fn_sub_21EAC0_0021eac0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        sb(v0, sp, 0xAF);
        a0 = addiu(s0, 544);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x2781C8u, gen::fn_sub_21D950_0021d950);
        lw(v0, s1, brpparam::kFlags);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x00278244
            charge(ctx, 2);
            v0 = 0x3F800000;
            mtc1(v0, f22);
        } else {
            // 0x002781e0
            charge(ctx, 4);
            lw(v0, s1, brpparam::kWord14140);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x00278200
                charge(ctx, 3);
                at = slti(v0, 20);
                if (at != 0) {
                    // 0x0027820c
                    charge(ctx, 14);
                    v0 = addiu(v0, -10);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    sub_s(f22, f0, f1);
                }
            } else {
                // 0x002781f0
                charge(ctx, 4);
                v0 = 0x3F800000;
                mtc1(v0, f22);
            }
        }
        // 0x0027824c
        charge(ctx, 24);
        lwc1(f0, s1, brpparam::kBlink);
        cvt_s_w(f1, f0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        v0 = 0x40000000;
        mtc1(v0, f0);
        mul_s(f1, f0, f1);
        lwc1(f0, gp, -32184);  // 0x7CAF38
        mul_s(f12, f0, f1);
        jal(ctx, 0x27827Cu, gen::fn_sinf_0052e878);
        lwc1(f2, gp, -32004);  // 0x7CAFEC
        lwc1(f1, gp, -32636);  // 0x7CAD74
        mtc1(zero, f3);
        adda_s(f3, f1);
        madd_s(f21, f2, f0);
        lw(v1, s0, 528);
        v0 = 99;
        if (v1 == v0) {
            // 0x002782c4
            charge(ctx, 4);
            v0 = 0x43650000;
            mtc1(v0, f3);
        } else {
            // 0x002782ac
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002782bc
                charge(ctx, 2);
            } else {
                // 0x002782b4
                charge(ctx, 2);
                // 0x002782d4
                charge(ctx, 14);
                v0 = 0x43610000;
                mtc1(v0, f1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                mul_s(f1, f1, f0);
                v0 = 0x42C40000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x40000000;
                mtc1(v0, f0);
                add_s(f3, f0, f1);
            }
        }
        // 0x0027830c
        charge(ctx, 4);
        lw(v1, s0, 532);
        v0 = 1;
        if (v1 == v0) {
            // 0x00278338
            charge(ctx, 4);
            v0 = 0x40800000;
            mtc1(v0, f1);
        } else {
            // 0x0027831c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0027832c
                charge(ctx, 3);
                mtc1(zero, f1);
            } else {
                // 0x00278324
                charge(ctx, 2);
                // 0x00278348
                charge(ctx, 14);
                v0 = 0x43600000;
                mtc1(v0, f1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                mul_s(f1, f1, f0);
                v0 = 0x42C40000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x40400000;
                mtc1(v0, f0);
                add_s(f1, f0, f1);
            }
        }
        // 0x00278380
        charge(ctx, 35);
        v0 = 0x42D80000;
        mtc1(v0, f0);
        add_s(f0, f0, f3);
        sub_s(f0, f0, f1);
        swc1(f0, sp, 0x80);
        swc1(f20, sp, 0x84);
        swc1(f1, sp, 0x88);
        a0 = s4;
        a1 = 27;
        jal(ctx, 0x2783A8u, gen::fn_sub_260920_00260920);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8C);
        a0 = addiu(s0, 800);
        a1 = addiu(sp, 0x80);
        jal(ctx, 0x2783C8u, gen::fn_sub_21D8E0_0021d8e0);
        v0 = 255;
        sb(v0, sp, 0xAC);
        sb(v0, sp, 0xAD);
        sb(v0, sp, 0xAE);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f22);
        mul_s(f1, f0, f21);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x00278424
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            // 0x0027840c
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFF;
        }
        // 0x0027843c
        charge(ctx, 6);
        sb(v1, sp, 0xAF);
        a0 = addiu(s0, 800);
        a1 = addiu(sp, 0xAC);
        jal(ctx, 0x278448u, gen::fn_sub_21D950_0021d950);
        s2 = addiu(s2, 1);
    }
    // 0x00278460
    charge(ctx, 58);
    lwc1(f0, s1, 15200);
    cvt_s_w(f2, f0);
    v0 = 0x433E0000;
    mtc1(v0, f1);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    mtc1(zero, f3);
    adda_s(f3, f0);
    madd_s(f21, f1, f2);
    lwc1(f0, s1, 15204);
    cvt_s_w(f2, f0);
    v0 = 0x41C00000;
    mtc1(v0, f1);
    v0 = 309;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    adda_s(f3, f0);
    madd_s(f20, f1, f2);
    a0 = s5;
    a1 = 0;
    jal(ctx, 0x2784B8u, gen::fn_sub_21CCA0_0021cca0);
    swc1(f21, sp, 0x80);
    swc1(f20, sp, 0x84);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x88);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x8C);
    a0 = addiu(s1, 15216);
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x2784E8u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0xAC);
    sb(v0, sp, 0xAD);
    sb(v0, sp, 0xAE);
    sb(v0, sp, 0xAF);
    a0 = addiu(s1, 15216);
    a1 = addiu(sp, 0xAC);
    jal(ctx, 0x27850Cu, gen::fn_sub_21D950_0021d950);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00278550 sub_278550 -- 3024 bytes; frame 0x1C0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpParamDraw] Draws the result screen's parameter panel (K_Assert line 97): the frame, the skill cells and their
// names (frFontDraw), the stat bars, numbers (sub_239140) and marks through the Im2D slot.
void sub_278550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00278550
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpParam);  // the result screen parameter panel (brp_param.c) 0x7CE3D0
    if (v0 == 0) {
        // 0x00278588
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x278594u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027859c
    charge(ctx, 18);
    lw(s1, gp, kGpBrpParam);  // the result screen parameter panel (brp_param.c) 0x7CE3D0
    a0 = 8;
    jal(ctx, 0x2785A4u, gen::fn_sub_119A60_00119a60);
    s4 = v0;
    a0 = 10;
    jal(ctx, 0x2785B4u, gen::fn_sub_119A60_00119a60);
    s5 = v0;
    a0 = 1;
    jal(ctx, 0x2785C4u, gen::fn_sub_234630_00234630);
    fp = v0;
    lw(a0, s1, brpparam::kFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x002785e4
        charge(ctx, 3);
        v1 = a0 & 0x40;
        if (v1 == 0) {
            // 0x002785f0
            charge(ctx, 41);
            s0 = 0x960000;
            s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
            a0 = 20;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x278604u, v0.u());
            a0 = 8;
            a1 = 0;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x278618u, v0.u());
            a0 = 6;
            a1 = 0;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x27862Cu, v0.u());
            a0 = 9;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x278640u, v0.u());
            a0 = 14;
            a1 = 0;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x278654u, v0.u());
            a0 = 7;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x278668u, v0.u());
            a0 = 12;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x27867Cu, v0.u());
            lw(v1, s1, brpparam::kFlags);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x00278694
                charge(ctx, 58);
                a0 = fp;
                a1 = 2;
                jal(ctx, 0x27869Cu, gen::fn_sub_21CCA0_0021cca0);
                s2 = v0;
                a0 = addiu(sp, 0xC0);
                a1 = s2;
                jal(ctx, 0x2786B0u, gen::fn_sub_21D3B0_0021d3b0);
                v0 = 0x43970000;
                sw(v0, sp, 0xA0);
                v0 = 0x43610000;
                sw(v0, sp, 0xA4);
                lwc1(f0, s2, 12);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xA8);
                lwc1(f0, s2, 16);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xAC);
                a0 = addiu(sp, 0xC0);
                a1 = addiu(sp, 0xA0);
                jal(ctx, 0x2786E8u, gen::fn_sub_21D8E0_0021d8e0);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x2786FCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x27870Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = s2;
                jal(ctx, 0x278718u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x27872Cu, v0.u());
                s2 = 0x960000;
                s2 = addiu(s2, 156);  // &0x96009C
                a0 = addiu(sp, 0xC0);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278754u, v0.u());
                a0 = addiu(sp, 0xC0);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278774u, v0.u());
            }
            // 0x0027877c
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00278838
                charge(ctx, 3);
                v1 = slti(s2, 8);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00278788
                charge(ctx, 44);
                v0 = 7;
                v1 = subu(v0, s2);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                s3 = addiu(v0, 16);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x2787B0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x2787C0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = s4;
                a1 = 18;
                jal(ctx, 0x2787D0u, gen::fn_sub_260940_00260940);
                a0 = 1;
                a1 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x2787E4u, v0.u());
                s6 = 0x960000;
                s6 = addiu(s6, 156);  // &0x96009C
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s6, 0);  // 0x96009C
                jalr(ctx, 0x27880Cu, v0.u());
                a0 = s3;
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s6, 0);  // 0x96009C
                jalr(ctx, 0x27882Cu, v0.u());
                s2 = addiu(s2, 1);
            }
            // 0x00278844
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00278878
                charge(ctx, 4);
                lw(v1, s1, brpparam::kSkillCount);
                v1 = slt(s2, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00278850
                charge(ctx, 10);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                lw(a0, v0, 272);
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x27886Cu, gen::fn_frFontDraw_003b1360);
                s2 = addiu(s2, 1);
            }
            // 0x00278888
            charge(ctx, 4);
            lw(v1, s1, brpparam::kFlags);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x00278898
                charge(ctx, 177);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x2788A4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x2788B4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = s4;
                a1 = 21;
                jal(ctx, 0x2788C4u, gen::fn_sub_260940_00260940);
                s3 = 0x960000;
                s3 = addiu(s3, 144);  // &pfn_RwRenderStateSet
                a0 = 1;
                a1 = v0;
                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x2788E0u, v0.u());
                s2 = 0x960000;
                s2 = addiu(s2, 156);  // &0x96009C
                a0 = addiu(s1, 11568);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278908u, v0.u());
                a0 = addiu(s1, 11568);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278928u, v0.u());
                a0 = addiu(s1, 11824);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278948u, v0.u());
                a0 = addiu(s1, 11824);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278968u, v0.u());
                a0 = s4;
                a1 = 23;
                jal(ctx, 0x278978u, gen::fn_sub_260940_00260940);
                a0 = 1;
                a1 = v0;
                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x27898Cu, v0.u());
                a0 = addiu(s1, 12080);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x2789ACu, v0.u());
                a0 = addiu(s1, 12080);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x2789CCu, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x2789E0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x2789F0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = s4;
                a1 = 19;
                jal(ctx, 0x278A00u, gen::fn_sub_260940_00260940);
                a0 = 1;
                a1 = v0;
                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x278A14u, v0.u());
                a0 = addiu(s1, 11312);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278A34u, v0.u());
                a0 = addiu(s1, 11312);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278A54u, v0.u());
                a0 = fp;
                a1 = 1;
                jal(ctx, 0x278A64u, gen::fn_sub_21CCA0_0021cca0);
                a0 = v0;
                jal(ctx, 0x278A70u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x278A84u, v0.u());
                a0 = addiu(s1, 14688);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278AA4u, v0.u());
                a0 = addiu(s1, 14688);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278AC4u, v0.u());
                a0 = fp;
                a1 = 0;
                jal(ctx, 0x278AD4u, gen::fn_sub_21CCA0_0021cca0);
                a0 = v0;
                jal(ctx, 0x278AE0u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s3, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x278AF4u, v0.u());
                a0 = addiu(s1, 14944);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278B14u, v0.u());
                a0 = addiu(s1, 14944);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278B34u, v0.u());
                lw(a0, s1, brpparam::kNewSkillLine);
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x278B48u, gen::fn_frFontDraw_003b1360);
                s2 = 0;
                for (;;) {
                    // 0x00278bfc
                    charge(ctx, 4);
                    lw(v0, s1, brpparam::kStatCount);
                    v0 = slt(s2, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00278b5c
                    charge(ctx, 40);
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x278B68u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x278B78u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = s4;
                    a1 = 20;
                    jal(ctx, 0x278B88u, gen::fn_sub_260940_00260940);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s0, 0);
                    jalr(ctx, 0x278B9Cu, v0.u());
                    v0 = sll(s2, 8);
                    v0 = addu(s1, v0);
                    s3 = addiu(v0, 12336);
                    s6 = 0x960000;
                    s6 = addiu(s6, 156);  // &0x96009C
                    a0 = s3;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s6, 0);  // 0x96009C
                    jalr(ctx, 0x278BD0u, v0.u());
                    a0 = s3;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s6, 0);  // 0x96009C
                    jalr(ctx, 0x278BF0u, v0.u());
                    s2 = addiu(s2, 1);
                }
                // 0x00278c0c
                charge(ctx, 20);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x278C18u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x278C28u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                jal(ctx, 0x278C34u, gen::fn_sub_239140_00239140);
                a0 = 1;
                a1 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x278C48u, v0.u());
                s2 = 0;
                for (;;) {
                    // 0x00278cb4
                    charge(ctx, 3);
                    v1 = slti(s2, 2);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00278c5c
                    charge(ctx, 22);
                    v0 = sll(s2, 8);
                    v0 = addu(s1, v0);
                    s3 = addiu(v0, 14160);
                    s4 = 0x960000;
                    s4 = addiu(s4, 156);  // &0x96009C
                    a0 = s3;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s4, 0);  // 0x96009C
                    jalr(ctx, 0x278C88u, v0.u());
                    a0 = s3;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s4, 0);  // 0x96009C
                    jalr(ctx, 0x278CA8u, v0.u());
                    s2 = addiu(s2, 1);
                }
            }
            // 0x00278cc0
            charge(ctx, 3);
            s4 = 0;
            for (;;) {
                // 0x00279004
                charge(ctx, 3);
                v1 = slti(s4, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00278ccc
                charge(ctx, 106);
                v0 = sll(s4, 3);
                v0 = subu(v0, s4);
                v0 = sll(v0, 3);
                v0 = addu(v0, s4);
                v0 = sll(v0, 5);
                v0 = addu(s1, v0);
                s3 = addiu(v0, 2192);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x278CF4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x278D04u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = s5;
                a1 = 20;
                jal(ctx, 0x278D14u, gen::fn_sub_260940_00260940);
                s6 = 0x960000;
                s6 = addiu(s6, 144);  // &pfn_RwRenderStateSet
                a0 = 1;
                a1 = v0;
                lw(v0, s6, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x278D30u, v0.u());
                s2 = 0x960000;
                s2 = addiu(s2, 156);  // &0x96009C
                a0 = addiu(s3, 1056);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278D58u, v0.u());
                a0 = addiu(s3, 1056);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278D78u, v0.u());
                a0 = addiu(s3, 1312);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278D98u, v0.u());
                a0 = addiu(s3, 1312);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278DB8u, v0.u());
                a0 = s5;
                a1 = 21;
                jal(ctx, 0x278DC8u, gen::fn_sub_260940_00260940);
                a0 = 1;
                a1 = v0;
                lw(v0, s6, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x278DDCu, v0.u());
                a0 = addiu(s3, 1568);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278DFCu, v0.u());
                a0 = addiu(s3, 1568);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278E1Cu, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x278E30u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x278E40u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                jal(ctx, 0x278E4Cu, gen::fn_sub_239140_00239140);
                a0 = 1;
                a1 = v0;
                lw(v0, s6, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x278E60u, v0.u());
                s2 = 0;
                for (;;) {
                    // 0x00278ecc
                    charge(ctx, 3);
                    v0 = slti(s2, 2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00278e74
                    charge(ctx, 22);
                    v0 = sll(s2, 8);
                    v0 = addu(s3, v0);
                    s6 = addiu(v0, 16);
                    s7 = 0x960000;
                    s7 = addiu(s7, 156);  // &0x96009C
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s7, 0);  // 0x96009C
                    jalr(ctx, 0x278EA0u, v0.u());
                    a0 = s6;
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s7, 0);  // 0x96009C
                    jalr(ctx, 0x278EC0u, v0.u());
                    s2 = addiu(s2, 1);
                }
                // 0x00278ed8
                charge(ctx, 40);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x17FB;
                jal(ctx, 0x278EE4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 68;
                jal(ctx, 0x278EF4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = s5;
                a1 = 24;
                jal(ctx, 0x278F04u, gen::fn_sub_260940_00260940);
                a0 = 1;
                a1 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x278F18u, v0.u());
                s2 = 0x960000;
                s2 = addiu(s2, 156);  // &0x96009C
                a0 = addiu(s3, 544);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278F40u, v0.u());
                a0 = addiu(s3, 544);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s2, 0);  // 0x96009C
                jalr(ctx, 0x278F60u, v0.u());
                lw(v1, s1, brpparam::kFlags);
                v1 = v1 & 0x8;
                if (v1 != 0) {
                    // 0x00278f78
                    charge(ctx, 34);
                    a0 = 3;
                    v0 = 0x70000;
                    a1 = v0 | 0x17FB;
                    jal(ctx, 0x278F84u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = 2;
                    a1 = 68;
                    jal(ctx, 0x278F94u, gen::fn_RpSkyRenderStateSet_004d7f60);
                    a0 = s5;
                    a1 = 27;
                    jal(ctx, 0x278FA4u, gen::fn_sub_260940_00260940);
                    a0 = 1;
                    a1 = v0;
                    lw(v0, s0, 0);
                    jalr(ctx, 0x278FB8u, v0.u());
                    a0 = addiu(s3, 800);
                    a1 = 4;
                    a2 = 0;
                    a3 = 1;
                    t0 = 2;
                    lw(v0, s2, 0);
                    jalr(ctx, 0x278FD8u, v0.u());
                    a0 = addiu(s3, 800);
                    a1 = 4;
                    a2 = 0;
                    a3 = 2;
                    t0 = 3;
                    lw(v0, s2, 0);
                    jalr(ctx, 0x278FF8u, v0.u());
                }
                // 0x00279000
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x00279010
            charge(ctx, 4);
            lw(v1, s1, brpparam::kFlags);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x00279020
                charge(ctx, 4);
                lw(t2, gp, kGpSeqHelpSkill);  // the skill the forget grid of the persona sequence points at (-1 none; 0x7CC4DC) 0x7CC4DC
                a2 = si(-1);
                if (t2 != a2) {
                    // 0x00279030
                    charge(ctx, 8);
                    mtc1(zero, f12);
                    a0 = 316;
                    a1 = 256;
                    a3 = 1;
                    t0 = 6;
                    t1 = 3;
                    jal(ctx, 0x279048u, gen::fn_sub_3C7E20_003c7e20);
                }
                // 0x00279050
                charge(ctx, 39);
                a0 = fp;
                a1 = 0;
                jal(ctx, 0x279058u, gen::fn_sub_21CCA0_0021cca0);
                a0 = v0;
                jal(ctx, 0x279064u, gen::fn_sub_21CCE0_0021cce0);
                a0 = 1;
                a1 = v0;
                lw(v0, s0, 0);
                jalr(ctx, 0x279078u, v0.u());
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x27908Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x27909Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                s0 = 0x960000;
                s0 = addiu(s0, 156);  // &0x96009C
                a0 = addiu(s1, 15216);
                a1 = 4;
                a2 = 0;
                a3 = 1;
                t0 = 2;
                lw(v0, s0, 0);  // 0x96009C
                jalr(ctx, 0x2790C4u, v0.u());
                a0 = addiu(s1, 15216);
                a1 = 4;
                a2 = 0;
                a3 = 2;
                t0 = 3;
                lw(v0, s0, 0);  // 0x96009C
                jalr(ctx, 0x2790E4u, v0.u());
            }
        }
    }
    // 0x002790ec (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1C0);
}

}  // namespace p3fes::game
