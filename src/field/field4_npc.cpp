// The NPC-placement / field-effect band 0x1DC6F0-0x1E8000 (slice field4): the Traesto effect task, the field icons
// (textures, the icon draw task), the party-panel / mini-map / area-name helpers, the party-member field rules (shown /
// walk / run / idle per scene), the developers' built-in field editor (free camera, NPC and position create / list
// modes, the record lists and the FBN writer -- the FBN layout of field4.h), the FBN / HBN / field-script / MAP
// loaders and the NPC placer (sub_1E2E50 / sub_1E3940), the HBN hit creator, the high-resolution screenshot, the debug
// quad helpers and the after-image trail helpers (eff_after.c). p3fes_handgen bodies (hg_cpu.h) with roles, proposed
// names in brackets and named offsets.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field4.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_FileExists_001008b0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);
void fn_K_FldFrame_CtlGetSphereCollisRadius_001ad8b0(p3fes::EEContext&);
void fn_K_FldFrame_CtlMoveInDir_001addf0(p3fes::EEContext&);
void fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);
void fn_asinf_0052ea00(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskMain_001949e0(p3fes::EEContext&);
void fn_kwlnTaskSetBandBEnabled_00195770(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrCreateTaskFromScriptMemory_0035bc00(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_173300_00173300(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_18BEE0_0018bee0(p3fes::EEContext&);
void fn_sub_18E5C0_0018e5c0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19C300_0019c300(p3fes::EEContext&);
void fn_sub_19C320_0019c320(p3fes::EEContext&);
void fn_sub_19C490_0019c490(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A01C0_001a01c0(p3fes::EEContext&);
void fn_sub_1A0310_001a0310(p3fes::EEContext&);
void fn_sub_1A0DC0_001a0dc0(p3fes::EEContext&);
void fn_sub_1A1540_001a1540(p3fes::EEContext&);
void fn_sub_1A3B10_001a3b10(p3fes::EEContext&);
void fn_sub_1A3BE0_001a3be0(p3fes::EEContext&);
void fn_sub_1A3BF0_001a3bf0(p3fes::EEContext&);
void fn_sub_1A3DC0_001a3dc0(p3fes::EEContext&);
void fn_sub_1A3F20_001a3f20(p3fes::EEContext&);
void fn_sub_1A4010_001a4010(p3fes::EEContext&);
void fn_sub_1A41B0_001a41b0(p3fes::EEContext&);
void fn_sub_1A4380_001a4380(p3fes::EEContext&);
void fn_sub_1A4510_001a4510(p3fes::EEContext&);
void fn_sub_1A4CD0_001a4cd0(p3fes::EEContext&);
void fn_sub_1A4DC0_001a4dc0(p3fes::EEContext&);
void fn_sub_1A4DF0_001a4df0(p3fes::EEContext&);
void fn_sub_1A4E50_001a4e50(p3fes::EEContext&);
void fn_sub_1A4E60_001a4e60(p3fes::EEContext&);
void fn_sub_1A4ED0_001a4ed0(p3fes::EEContext&);
void fn_sub_1A4F40_001a4f40(p3fes::EEContext&);
void fn_sub_1A5000_001a5000(p3fes::EEContext&);
void fn_sub_1A5AA0_001a5aa0(p3fes::EEContext&);
void fn_sub_1A5B30_001a5b30(p3fes::EEContext&);
void fn_sub_1A5BC0_001a5bc0(p3fes::EEContext&);
void fn_sub_1A9080_001a9080(p3fes::EEContext&);
void fn_sub_1A9180_001a9180(p3fes::EEContext&);
void fn_sub_1A91B0_001a91b0(p3fes::EEContext&);
void fn_sub_1A9390_001a9390(p3fes::EEContext&);
void fn_sub_1AD870_001ad870(p3fes::EEContext&);
void fn_sub_1AD890_001ad890(p3fes::EEContext&);
void fn_sub_1AD940_001ad940(p3fes::EEContext&);
void fn_sub_1ADC20_001adc20(p3fes::EEContext&);
void fn_sub_1ADFF0_001adff0(p3fes::EEContext&);
void fn_sub_1AE0D0_001ae0d0(p3fes::EEContext&);
void fn_sub_1B0910_001b0910(p3fes::EEContext&);
void fn_sub_1B7E30_001b7e30(p3fes::EEContext&);
void fn_sub_1B83F0_001b83f0(p3fes::EEContext&);
void fn_sub_1B85A0_001b85a0(p3fes::EEContext&);
void fn_sub_1B8CF0_001b8cf0(p3fes::EEContext&);
void fn_sub_1B8D60_001b8d60(p3fes::EEContext&);
void fn_sub_1B8DB0_001b8db0(p3fes::EEContext&);
void fn_sub_1D4180_001d4180(p3fes::EEContext&);
void fn_sub_1DC6F0_001dc6f0(p3fes::EEContext&);
void fn_sub_1DC8E0_001dc8e0(p3fes::EEContext&);
void fn_sub_1DC910_001dc910(p3fes::EEContext&);
void fn_sub_1DCA10_001dca10(p3fes::EEContext&);
void fn_sub_1DCB60_001dcb60(p3fes::EEContext&);
void fn_sub_1DD430_001dd430(p3fes::EEContext&);
void fn_sub_1DD460_001dd460(p3fes::EEContext&);
void fn_sub_1DD530_001dd530(p3fes::EEContext&);
void fn_sub_1DD5E0_001dd5e0(p3fes::EEContext&);
void fn_sub_1DD5F0_001dd5f0(p3fes::EEContext&);
void fn_sub_1DD600_001dd600(p3fes::EEContext&);
void fn_sub_1DD8E0_001dd8e0(p3fes::EEContext&);
void fn_sub_1DDB30_001ddb30(p3fes::EEContext&);
void fn_sub_1DDCA0_001ddca0(p3fes::EEContext&);
void fn_sub_1DDD30_001ddd30(p3fes::EEContext&);
void fn_sub_1DDE00_001dde00(p3fes::EEContext&);
void fn_sub_1DE630_001de630(p3fes::EEContext&);
void fn_sub_1DED40_001ded40(p3fes::EEContext&);
void fn_sub_1DF450_001df450(p3fes::EEContext&);
void fn_sub_1DFA70_001dfa70(p3fes::EEContext&);
void fn_sub_1E0510_001e0510(p3fes::EEContext&);
void fn_sub_1E1840_001e1840(p3fes::EEContext&);
void fn_sub_1E1850_001e1850(p3fes::EEContext&);
void fn_sub_1E2300_001e2300(p3fes::EEContext&);
void fn_sub_1E2370_001e2370(p3fes::EEContext&);
void fn_sub_1E2430_001e2430(p3fes::EEContext&);
void fn_sub_1E2810_001e2810(p3fes::EEContext&);
void fn_sub_1E2850_001e2850(p3fes::EEContext&);
void fn_sub_1E28A0_001e28a0(p3fes::EEContext&);
void fn_sub_1E2930_001e2930(p3fes::EEContext&);
void fn_sub_1E29E0_001e29e0(p3fes::EEContext&);
void fn_sub_1E2A20_001e2a20(p3fes::EEContext&);
void fn_sub_1E2A70_001e2a70(p3fes::EEContext&);
void fn_sub_1E2B10_001e2b10(p3fes::EEContext&);
void fn_sub_1E2BD0_001e2bd0(p3fes::EEContext&);
void fn_sub_1E2DA0_001e2da0(p3fes::EEContext&);
void fn_sub_1E2E50_001e2e50(p3fes::EEContext&);
void fn_sub_1E3940_001e3940(p3fes::EEContext&);
void fn_sub_1E3F10_001e3f10(p3fes::EEContext&);
void fn_sub_1E4B10_001e4b10(p3fes::EEContext&);
void fn_sub_1E4B40_001e4b40(p3fes::EEContext&);
void fn_sub_1E4BC0_001e4bc0(p3fes::EEContext&);
void fn_sub_1E5820_001e5820(p3fes::EEContext&);
void fn_sub_1E5850_001e5850(p3fes::EEContext&);
void fn_sub_1E58D0_001e58d0(p3fes::EEContext&);
void fn_sub_1E6000_001e6000(p3fes::EEContext&);
void fn_sub_1E6030_001e6030(p3fes::EEContext&);
void fn_sub_1E60B0_001e60b0(p3fes::EEContext&);
void fn_sub_1E6A40_001e6a40(p3fes::EEContext&);
void fn_sub_1E6A70_001e6a70(p3fes::EEContext&);
void fn_sub_1E6AF0_001e6af0(p3fes::EEContext&);
void fn_sub_1E6CB0_001e6cb0(p3fes::EEContext&);
void fn_sub_1E6D50_001e6d50(p3fes::EEContext&);
void fn_sub_1E6EA0_001e6ea0(p3fes::EEContext&);
void fn_sub_1E7200_001e7200(p3fes::EEContext&);
void fn_sub_1E7290_001e7290(p3fes::EEContext&);
void fn_sub_1E7410_001e7410(p3fes::EEContext&);
void fn_sub_1E7470_001e7470(p3fes::EEContext&);
void fn_sub_1E74E0_001e74e0(p3fes::EEContext&);
void fn_sub_1E7520_001e7520(p3fes::EEContext&);
void fn_sub_1E7540_001e7540(p3fes::EEContext&);
void fn_sub_1E75B0_001e75b0(p3fes::EEContext&);
void fn_sub_1E7720_001e7720(p3fes::EEContext&);
void fn_sub_1E78C0_001e78c0(p3fes::EEContext&);
void fn_sub_1E7A60_001e7a60(p3fes::EEContext&);
void fn_sub_1E7AA0_001e7aa0(p3fes::EEContext&);
void fn_sub_1E7B10_001e7b10(p3fes::EEContext&);
void fn_sub_1E7C20_001e7c20(p3fes::EEContext&);
void fn_sub_1E7CE0_001e7ce0(p3fes::EEContext&);
void fn_sub_1E7DE0_001e7de0(p3fes::EEContext&);
void fn_sub_1E7E30_001e7e30(p3fes::EEContext&);
void fn_sub_1E7F90_001e7f90(p3fes::EEContext&);
void fn_sub_1E8330_001e8330(p3fes::EEContext&);
void fn_sub_316B40_00316b40(p3fes::EEContext&);
void fn_sub_316E00_00316e00(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_317450_00317450(p3fes::EEContext&);
void fn_sub_317730_00317730(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_318A30_00318a30(p3fes::EEContext&);
void fn_sub_318A50_00318a50(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B5E90_003b5e90(p3fes::EEContext&);
void fn_sub_3B6270_003b6270(p3fes::EEContext&);
void fn_sub_3B6870_003b6870(p3fes::EEContext&);
void fn_sub_3B69A0_003b69a0(p3fes::EEContext&);
void fn_sub_3B6AD0_003b6ad0(p3fes::EEContext&);
void fn_sub_3B6B90_003b6b90(p3fes::EEContext&);
void fn_sub_3B6C50_003b6c50(p3fes::EEContext&);
void fn_sub_3B6D10_003b6d10(p3fes::EEContext&);
void fn_sub_3B6DD0_003b6dd0(p3fes::EEContext&);
void fn_sub_3B6E90_003b6e90(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3B78B0_003b78b0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_491880_00491880(p3fes::EEContext&);
void fn_sub_4919B0_004919b0(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_492D10_00492d10(p3fes::EEContext&);
void fn_sub_493210_00493210(p3fes::EEContext&);
void fn_sub_493230_00493230(p3fes::EEContext&);
void fn_sub_493710_00493710(p3fes::EEContext&);
void fn_sub_493B60_00493b60(p3fes::EEContext&);
void fn_sub_4BAD50_004bad50(p3fes::EEContext&);
void fn_sub_4BF540_004bf540(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C2FB0_004c2fb0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C20_004c6c20(p3fes::EEContext&);
void fn_sub_4CA560_004ca560(p3fes::EEContext&);
void fn_sub_4CA5B0_004ca5b0(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB890_004cb890(p3fes::EEContext&);
void fn_sub_4D1260_004d1260(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001DC6F0 sub_1DC6F0 [K_TraEst_Update] -- 492 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DC6F0(task) -> 0, or -1 to be destroyed: the "traest proc" task (the Traesto escape effect, TRAEST.EPL):
// state 0 waits for the EPL and starts it 240 above the hero's model (sub_318B60(0x8717F0) +48..+56), its
// instance mode 5; state 1 counts frames (+8): from 41 the party's field units (gFldUnitsPc[4], 448 bytes each, with
// a model +72 and a resource +84) lose their draw flag (resource +40 bit 1) and, for mode 1 (+4), the screen fades
// out (sub_108570, sub_1086A0(1), sub_108670(6)) and the state advances; at 84 -> 2; state 2 -> -1.
void sub_1DC6F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001dc6f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, f4::kTaskWork);
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 == v0) {
        // 0x001dc8b8
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001dc710
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x001dc7bc
            charge(ctx, 4);
            lw(v0, s0, 8);
            at = slti(v0, 84);
            if (at == 0) {
                // 0x001dc8a8
                charge(ctx, 4);
                v0 = addiu(v1, 1);
                sw(v0, s0, 0);
            } else {
                // 0x001dc7cc
                charge(ctx, 3);
                at = slti(v0, 41);
                if (at == 0) {
                    // 0x001dc7d8
                    charge(ctx, 9);
                    jal(ctx, 0x1DC7D8u, gen::fn_sub_1D4180_001d4180);
                    t0 = 0;
                    a1 = 1;
                    a2 = 0x870000;
                    a2 = addiu(a2, 6048);  // &gFldUnitsPc
                    v1 = si(-3);
                    for (;;) {
                        // 0x001dc84c
                        charge(ctx, 3);
                        v0 = sltiu(t0, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001dc7fc
                        charge(ctx, 8);
                        a3 = 0;
                        v0 = sll(t0, 3);
                        v0 = subu(v0, t0);
                        v0 = sll(v0, 6);
                        a0 = addu(a2, v0);
                        lw(v0, a0, 72);
                        if (v0 != 0) {
                            // 0x001dc81c
                            charge(ctx, 3);
                            lw(v0, a0, 84);
                            if (v0 != 0) {
                                // 0x001dc828
                                charge(ctx, 1);
                                a3 = a1;
                            }
                        }
                        // 0x001dc82c
                        charge(ctx, 3);
                        v0 = sltu(0, a3);
                        if (v0 != 0) {
                            // 0x001dc838
                            charge(ctx, 4);
                            lw(a0, a0, 84);
                            lw(v0, a0, 40);
                            v0 = v0 & v1;
                            sw(v0, a0, 40);
                        }
                        // 0x001dc848
                        charge(ctx, 1);
                        t0 = addiu(t0, 1);
                    }
                    // 0x001dc858
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x001dc868
                        charge(ctx, 11);
                        jal(ctx, 0x1DC868u, gen::fn_sub_108570_00108570);
                        a0 = 1;
                        jal(ctx, 0x1DC874u, gen::fn_sub_1086A0_001086a0);
                        a0 = 6;
                        jal(ctx, 0x1DC880u, gen::fn_sub_108670_00108670);
                        lw(v0, s0, 0);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, 0);
                    }
                }
                // 0x001dc894
                charge(ctx, 5);
                lw(v0, s0, 8);
                v0 = addiu(v0, 1);
                sw(v0, s0, 8);
            }
        } else {
            // 0x001dc71c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x001dc72c
                charge(ctx, 5);
                lw(a0, s0, 12);
                jal(ctx, 0x1DC730u, gen::fn_sub_1A9180_001a9180);
                if (v0 != 0) {
                    // 0x001dc740
                    charge(ctx, 31);
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    jal(ctx, 0x1DC748u, gen::fn_sub_318B60_00318b60);
                    a1 = addiu(sp, 0x20);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0x20);
                    swc1(f1, sp, 0x24);
                    swc1(f0, sp, 0x28);
                    lwc1(f1, sp, 0x24);
                    v0 = 0x43700000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x24);
                    lw(a0, s0, 12);
                    jal(ctx, 0x1DC788u, gen::fn_sub_1A91B0_001a91b0);
                    lw(a0, s0, 12);
                    a1 = v0;
                    a2 = 5;
                    jal(ctx, 0x1DC79Cu, gen::fn_sub_1A9390_001a9390);
                    sw(zero, s0, 8);
                    lw(v0, s0, 0);
                    v0 = addiu(v0, 1);
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001dc724
                charge(ctx, 2);
            }
        }
        // 0x001dc8c4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001dc8c8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001DC8E0 sub_1DC8E0 [K_TraEst_Destroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1DC8E0(task): frees the "traest proc" work.
void sub_1DC8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dc8e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1DC8F4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001DC910 sub_1DC910 [K_TraEst_CreateTask] -- 256 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1DC910(parent, mode) -> the "traest proc" task (16-byte work, priority 10): +4 = mode, +12 the effect
// "field/btl_effect/TRAEST.EPL" (sub_1A9080 with 83 frames for mode 0, 50 for mode 1). Caller: the COMM sub_1C4C50.
void sub_1DC910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dc910
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    a0 = 1;
    a1 = 16;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1DC940u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001dc960
        charge(ctx, 15);
        a0 = s1;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, 15304);  // "traest proc"
        a3 = 0x1E0000;
        a3 = addiu(a3, -14608);  // &sub_1DC6F0
        t0 = 0x1E0000;
        t0 = addiu(t0, -14112);  // &sub_1DC8E0
        t1 = s0;
        jal(ctx, 0x1DC984u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        sw(s2, s0, 4);
        if (s2 != 0) {
            // 0x001dc9c4
            charge(ctx, 3);
            v0 = 1;
            if (s2 == v0) {
                // 0x001dc9d0
                charge(ctx, 8);
                a0 = s1;
                a1 = 0x680000;
                a1 = addiu(a1, 15328);  // "field/btl_effect/TRAEST.EPL"
                a2 = 50;
                a3 = 0;
                jal(ctx, 0x1DC9E4u, gen::fn_sub_1A9080_001a9080);
                sw(v0, s0, 12);
            }
        } else {
            // 0x001dc99c
            charge(ctx, 10);
            a0 = s1;
            a1 = 0x680000;
            a1 = addiu(a1, 15328);  // "field/btl_effect/TRAEST.EPL"
            a2 = 83;
            a3 = 0;
            jal(ctx, 0x1DC9B0u, gen::fn_sub_1A9080_001a9080);
            sw(v0, s0, 12);
        }
        // 0x001dc9f0
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x001dc954
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001dc9f4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001DCA10 sub_1DCA10 [K_FieldIcon_LoadTextures] -- 332 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DCA10() (boot, kwlnInitMain): reads "field/icon/ficon.bin" (a texture dictionary, H_Cdvd_ReadSync) and looks
// up the nine field icons i_f_icon01..07, 01a, 01b (sub_4D1260 = RwTextureRead) into 0x875A60..0x875A80.
void sub_1DCA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dca10
    enter(ctx, 83);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, 15360);  // "field/icon/ficon.bin"
    a1 = 1;
    jal(ctx, 0x1DCA28u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x1DCA38u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x680000;
    a0 = addiu(a0, 15392);  // "field/icon/i_f_icon01"
    a1 = 0;
    jal(ctx, 0x1DCA4Cu, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23136);  // 0x875A60
    a0 = 0x680000;
    a0 = addiu(a0, 15424);  // "field/icon/i_f_icon02"
    a1 = 0;
    jal(ctx, 0x1DCA68u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23140);  // 0x875A64
    a0 = 0x680000;
    a0 = addiu(a0, 15456);  // "field/icon/i_f_icon03"
    a1 = 0;
    jal(ctx, 0x1DCA84u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23144);  // 0x875A68
    a0 = 0x680000;
    a0 = addiu(a0, 15488);  // "field/icon/i_f_icon04"
    a1 = 0;
    jal(ctx, 0x1DCAA0u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23148);  // 0x875A6C
    a0 = 0x680000;
    a0 = addiu(a0, 15520);  // "field/icon/i_f_icon05"
    a1 = 0;
    jal(ctx, 0x1DCABCu, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23152);  // 0x875A70
    a0 = 0x680000;
    a0 = addiu(a0, 15552);  // "field/icon/i_f_icon06"
    a1 = 0;
    jal(ctx, 0x1DCAD8u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23156);  // 0x875A74
    a0 = 0x680000;
    a0 = addiu(a0, 15584);  // "field/icon/i_f_icon07"
    a1 = 0;
    jal(ctx, 0x1DCAF4u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23160);  // 0x875A78
    a0 = 0x680000;
    a0 = addiu(a0, 15616);  // "field/icon/i_f_icon01a"
    a1 = 0;
    jal(ctx, 0x1DCB10u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23164);  // 0x875A7C
    a0 = 0x680000;
    a0 = addiu(a0, 15648);  // "field/icon/i_f_icon01b"
    a1 = 0;
    jal(ctx, 0x1DCB2Cu, gen::fn_sub_4D1260_004d1260);
    v1 = 0x870000;
    sw(v0, v1, 23168);  // 0x875A80
    a0 = s0;
    jal(ctx, 0x1DCB40u, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DCB60 sub_1DCB60 [K_FieldIcon_Draw] -- 2252 bytes; frame 0x70: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_1DCB60(task) -> 0: the "field icon draw" task (560-byte work): when enabled (+0), above its unit's model
// (+548: sub_318B60 +48.., 120 up; 30 when sub_318ED0) projected to the screen (sub_1DD530 -> +12 / +16 / +20 =
// x, y, depth; the depth eased through ACC), and inside -32..640 x -32..448: two 32 x 32 sprites as two 4-vertex
// Im2D strips (+32.. and +288..; 64-byte vertices, the 1 / z at +56..), the icon type +8 choosing the animation
// (0 / 3 / 5: a fade +544 -= 10; 1: a 9-frame bob; 2 / 4: a 5-frame bob) and the textures (0..3: icon 01, 4: 01a,
// 5: 01b; the second sprite 0x875A64 [type]). With +4 (created at priority 4184) it draws inside its own camera
// update (RwCameraBeginUpdate, z-test off). A draw task: RW render state and Im2D only (no hardware register).
void sub_1DCB60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    // 0x001dcb60
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    lw(s2, a0, f4::kTaskWork);
    jal(ctx, 0x1DCB9Cu, gen::fn_sub_198590_00198590);
    lwc1(f2, v0, 128);
    v0 = 0x3F800000;
    mtc1(v0, f0);
    div_s(f1, f0, f2);
    lw(v0, s2, 0);
    if (v0 != 0) {
        // 0x001dcbd8
        charge(ctx, 3);
        lw(a0, s2, 548);
        if (a0 != 0) {
            // 0x001dcbe4
            charge(ctx, 6);
            a1 = 2;
            a2 = addiu(sp, 0x60);
            jal(ctx, 0x1DCBECu, gen::fn_sub_318ED0_00318ed0);
            if (v0 != 0) {
                // 0x001dcc40
                charge(ctx, 6);
                lwc1(f1, sp, 0x64);
                v0 = 0x41F00000;
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x64);
            } else {
                // 0x001dcbfc
                charge(ctx, 17);
                lw(a0, s2, 548);
                jal(ctx, 0x1DCC00u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x60);
                swc1(f1, sp, 0x64);
                swc1(f0, sp, 0x68);
                lwc1(f1, sp, 0x64);
                v0 = 0x42F00000;
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x64);
            }
            // 0x001dcc58
            charge(ctx, 29);
            a0 = s0;
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x1DCC60u, gen::fn_sub_1DD530_001dd530);
            v0 = 0x960000;
            lwc1(f25, v0, 140);  // 0x96008C
            v0 = 0x960000;
            lwc1(f27, v0, 136);  // g_rwIm2DNearScreenZ
            jal(ctx, 0x1DCC78u, gen::fn_sub_198590_00198590);
            lwc1(f26, v0, 132);
            jal(ctx, 0x1DCC84u, gen::fn_sub_198590_00198590);
            lwc1(f4, v0, 128);
            lwc1(f3, s2, 20);
            sub_s(f1, f27, f25);
            sub_s(f0, f4, f26);
            div_s(f1, f1, f0);
            sub_s(f0, f3, f26);
            mul_s(f2, f0, f1);
            div_s(f1, f4, f3);
            mtc1(zero, f0);
            adda_s(f0, f25);
            madd_s(f1, f1, f2);
            swc1(f1, s2, 20);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001dcccc
                charge(ctx, 1);
                swc1(f0, s2, 20);
            }
            // 0x001dccd0
            charge(ctx, 5);
            lwc1(f2, s2, 20);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            div_s(f1, f0, f2);
        }
        // 0x001dcce4
        charge(ctx, 7);
        lwc1(f0, s2, 12);
        v0 = lui(0xC200);
        mtc1(v0, f3);
        c_lt_s(f0, f3);
        if (!cond(ctx)) {
            // 0x001dcd00
            charge(ctx, 4);
            lwc1(f4, s2, 16);
            c_lt_s(f4, f3);
            if (cond(ctx)) {
                goto L_001dcd40;
            }
            // 0x001dcd10
            charge(ctx, 6);
            v0 = 0x44200000;
            mtc1(v0, f3);
            c_le_s(f0, f3);
            if (!cond(ctx)) {
                goto L_001dcd40;
            }
            // 0x001dcd28
            charge(ctx, 6);
            v0 = 0x43E00000;
            mtc1(v0, f3);
            c_le_s(f4, f3);
            if (!cond(ctx)) {
                goto L_001dcd40;
            }
            // 0x001dcd4c
            charge(ctx, 5);
            v0 = 255;
            lw(v1, s2, 8);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x001dcd60
                charge(ctx, 7);
                a0 = 0x7B0000;
                a0 = addiu(a0, 27920);  // &0x7B6D10
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x1DCD7Cu:  // table[0, 3, 5]
                    // 0x001dcd7c
                    charge(ctx, 15);
                    lw(v0, s2, 544);
                    v0 = addiu(v0, -10);
                    sw(v0, s2, 544);
                    lbu(v0, s2, 544);
                    lwc1(f0, s2, 12);
                    mov_s(f24, f0);
                    lwc1(f23, s2, 16);
                    v1 = 0x42000000;
                    mtc1(v1, f3);
                    add_s(f22, f3, f0);
                    mov_s(f21, f0);
                    add_s(f20, f3, f23);
                    break;
                case 0x1DCDB8u:  // table[1]
                    // 0x001dcdb8
                    charge(ctx, 6);
                    lw(v1, s2, 544);
                    v1 = addiu(v1, 1);
                    sw(v1, s2, 544);
                    at = sltiu(v1, 9);
                    if (at == 0) {
                        // 0x001dcdd0
                        charge(ctx, 1);
                        sw(zero, s2, 544);
                    }
                    // 0x001dcdd4
                    charge(ctx, 5);
                    lw(v1, s2, 544);
                    a1 = srl(v1, 1);
                    lwc1(f0, s2, 12);
                    if (i64(a1) < 0) {
                        // 0x001dcdfc
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dcde8
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dce18
                    charge(ctx, 5);
                    add_s(f21, f0, f3);
                    mov_s(f24, f21);
                    lwc1(f5, s2, 16);
                    if (i64(a1) < 0) {
                        // 0x001dce40
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dce2c
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dce5c
                    charge(ctx, 7);
                    add_s(f23, f5, f3);
                    v1 = 0x42000000;
                    mtc1(v1, f3);
                    add_s(f4, f3, f0);
                    if (i64(a1) < 0) {
                        // 0x001dce8c
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dce78
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dcea8
                    charge(ctx, 7);
                    sub_s(f22, f4, f3);
                    v1 = 0x42000000;
                    mtc1(v1, f3);
                    add_s(f4, f3, f5);
                    if (i64(a1) < 0) {
                        // 0x001dced8
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dcec4
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dcef4
                    charge(ctx, 3);
                    sub_s(f20, f4, f3);
                    break;
                case 0x1DCF00u:  // table[2, 4]
                    // 0x001dcf00
                    charge(ctx, 6);
                    lw(v1, s2, 544);
                    v1 = addiu(v1, 1);
                    sw(v1, s2, 544);
                    at = sltiu(v1, 5);
                    if (at == 0) {
                        // 0x001dcf18
                        charge(ctx, 1);
                        sw(zero, s2, 544);
                    }
                    // 0x001dcf1c
                    charge(ctx, 4);
                    lw(a1, s2, 544);
                    lwc1(f0, s2, 12);
                    if (i64(a1) < 0) {
                        // 0x001dcf40
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dcf2c
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dcf5c
                    charge(ctx, 5);
                    add_s(f21, f0, f3);
                    mov_s(f24, f21);
                    lwc1(f5, s2, 16);
                    if (i64(a1) < 0) {
                        // 0x001dcf84
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dcf70
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dcfa0
                    charge(ctx, 7);
                    add_s(f23, f5, f3);
                    v1 = 0x42000000;
                    mtc1(v1, f3);
                    add_s(f4, f3, f0);
                    if (i64(a1) < 0) {
                        // 0x001dcfd0
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dcfbc
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dcfec
                    charge(ctx, 7);
                    sub_s(f22, f4, f3);
                    v1 = 0x42000000;
                    mtc1(v1, f3);
                    add_s(f4, f3, f5);
                    if (i64(a1) < 0) {
                        // 0x001dd01c
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f3);
                        cvt_s_w(f3, f3);
                        add_s(f3, f3, f3);
                    } else {
                        // 0x001dd008
                        charge(ctx, 5);
                        mtc1(a1, f3);
                        cvt_s_w(f3, f3);
                    }
                    // 0x001dd038
                    charge(ctx, 1);
                    sub_s(f20, f4, f3);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            // 0x001dd03c
            charge(ctx, 69);
            swc1(f0, s2, 32);
            lwc1(f0, s2, 16);
            swc1(f0, s2, 36);
            swc1(f2, s2, 40);
            lwc1(f0, s2, 12);
            v1 = 0x42000000;
            mtc1(v1, f3);
            add_s(f0, f3, f0);
            swc1(f0, s2, 96);
            lwc1(f0, s2, 16);
            swc1(f0, s2, 100);
            swc1(f2, s2, 104);
            lwc1(f0, s2, 12);
            swc1(f0, s2, 160);
            lwc1(f0, s2, 16);
            add_s(f0, f3, f0);
            swc1(f0, s2, 164);
            swc1(f2, s2, 168);
            lwc1(f0, s2, 12);
            add_s(f0, f3, f0);
            swc1(f0, s2, 224);
            lwc1(f0, s2, 16);
            add_s(f0, f3, f0);
            swc1(f0, s2, 228);
            swc1(f2, s2, 232);
            swc1(f1, s2, 56);
            swc1(f1, s2, 120);
            swc1(f1, s2, 184);
            swc1(f1, s2, 248);
            sw(zero, s2, 48);
            sw(zero, s2, 52);
            v1 = 0x3F800000;
            sw(v1, s2, 112);
            sw(zero, s2, 116);
            sw(zero, s2, 176);
            sw(v1, s2, 180);
            sw(v1, s2, 240);
            sw(v1, s2, 244);
            swc1(f24, s2, 288);
            swc1(f23, s2, 292);
            swc1(f2, s2, 296);
            swc1(f22, s2, 352);
            swc1(f23, s2, 356);
            swc1(f2, s2, 360);
            swc1(f21, s2, 416);
            swc1(f20, s2, 420);
            swc1(f2, s2, 424);
            swc1(f22, s2, 480);
            swc1(f20, s2, 484);
            swc1(f2, s2, 488);
            swc1(f1, s2, 312);
            swc1(f1, s2, 376);
            swc1(f1, s2, 440);
            swc1(f1, s2, 504);
            sw(zero, s2, 304);
            sw(zero, s2, 308);
            sw(v1, s2, 368);
            sw(zero, s2, 372);
            sw(zero, s2, 432);
            sw(v1, s2, 436);
            sw(v1, s2, 496);
            sw(v1, s2, 500);
            a3 = 0;
            a1 = 0x437F0000;
            a0 = v0 & 0x1;
            mtc1(v0, f1);
            for (;;) {
                // 0x001dd1a8
                charge(ctx, 3);
                v1 = slti(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001dd150
                charge(ctx, 11);
                v1 = sll(a3, 6);
                a2 = addu(s2, v1);
                sw(a1, a2, 64);
                sw(a1, a2, 68);
                sw(a1, a2, 72);
                sw(a1, a2, 76);
                sw(a1, a2, 320);
                sw(a1, a2, 324);
                sw(a1, a2, 328);
                if (i64(v0) < 0) {
                    // 0x001dd188
                    charge(ctx, 6);
                    v1 = srl(v0, 1);
                    v1 = v1 | a0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x001dd17c
                    charge(ctx, 3);
                    cvt_s_w(f0, f1);
                }
                // 0x001dd1a0
                charge(ctx, 2);
                swc1(f0, a2, 332);
                a3 = addiu(a3, 1);
            }
            // 0x001dd1b4
            charge(ctx, 3);
            lw(v0, s2, 4);
            if (v0 != 0) {
                // 0x001dd1c0
                charge(ctx, 17);
                jal(ctx, 0x1DD1C0u, gen::fn_sub_198590_00198590);
                a0 = v0;
                jal(ctx, 0x1DD1CCu, gen::fn_RwCameraBeginUpdate_004c9d10);
                a0 = 14;
                a1 = addiu(sp, 0x6C);
                v0 = 0x960000;
                lw(v0, v0, 148);  // pfn_RwRenderStateGet
                jalr(ctx, 0x1DD1E4u, v0.u());
                a0 = 14;
                a1 = 0;
                v0 = 0x960000;
                lw(v0, v0, 144);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1DD1FCu, v0.u());
            }
            // 0x001dd204
            charge(ctx, 10);
            s1 = 0x960000;
            s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
            a0 = 6;
            a1 = 1;
            lw(v0, s1, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x1DD218u, v0.u());
            lw(v0, s2, 4);
            if (v0 == 0) {
                // 0x001dd248
                charge(ctx, 5);
                a0 = 8;
                a1 = 0;
                lw(v0, s1, 0);
                jalr(ctx, 0x1DD254u, v0.u());
            } else {
                // 0x001dd22c
                charge(ctx, 7);
                a0 = 8;
                a1 = 1;
                lw(v0, s1, 0);
                jalr(ctx, 0x1DD238u, v0.u());
            }
            // 0x001dd25c
            charge(ctx, 30);
            s0 = 0x960000;
            s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
            a0 = 7;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x1DD270u, v0.u());
            a0 = 12;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x1DD284u, v0.u());
            a0 = 9;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x1DD298u, v0.u());
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x1DD2A8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x1DD2BCu, gen::fn_RpSkyRenderStateSet_004d7f60);
            lw(v0, s2, 8);
            at = sltiu(v0, 6);
            if (at != 0) {
                // 0x001dd2d4
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 27888);  // &0x7B6CF0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x1DD2F0u:  // table[0, 1, 2, 3]
                    // 0x001dd2f0
                    charge(ctx, 9);
                    v0 = 0x870000;
                    lw(v0, v0, 23136);  // 0x875A60
                    a0 = 1;
                    lw(a1, v0, 0);
                    lw(v0, s1, 0);
                    jalr(ctx, 0x1DD304u, v0.u());
                    break;
                case 0x1DD314u:  // table[4]
                    // 0x001dd314
                    charge(ctx, 9);
                    v0 = 0x870000;
                    lw(v0, v0, 23164);  // 0x875A7C
                    a0 = 1;
                    lw(a1, v0, 0);
                    lw(v0, s1, 0);
                    jalr(ctx, 0x1DD328u, v0.u());
                    break;
                case 0x1DD338u:  // table[5]
                    // 0x001dd338
                    charge(ctx, 7);
                    v0 = 0x870000;
                    lw(v0, v0, 23168);  // 0x875A80
                    a0 = 1;
                    lw(a1, v0, 0);
                    lw(v0, s1, 0);
                    jalr(ctx, 0x1DD34Cu, v0.u());
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x001dd354
            charge(ctx, 28);
            s0 = 0x960000;
            s0 = addiu(s0, 160);  // &pfn_RwIm2DRenderPrimitive
            a0 = 4;
            a1 = addiu(s2, 32);
            a2 = a0;
            lw(v0, s0, 0);  // pfn_RwIm2DRenderPrimitive
            jalr(ctx, 0x1DD36Cu, v0.u());
            lw(v0, s2, 8);
            v1 = sll(v0, 2);
            v0 = 0x870000;
            v0 = addiu(v0, 23140);  // &0x875A64
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            a0 = 1;
            lw(a1, v0, 0);
            lw(v0, s1, 0);
            jalr(ctx, 0x1DD398u, v0.u());
            a0 = 4;
            a1 = addiu(s2, 288);
            a2 = a0;
            lw(v0, s0, 0);  // pfn_RwIm2DRenderPrimitive
            jalr(ctx, 0x1DD3B0u, v0.u());
            lw(v0, s2, 4);
            if (v0 != 0) {
                // 0x001dd3c4
                charge(ctx, 10);
                a0 = 14;
                lw(a1, sp, 0x6C);
                lw(v0, s1, 0);
                jalr(ctx, 0x1DD3D0u, v0.u());
                jal(ctx, 0x1DD3D8u, gen::fn_sub_198590_00198590);
                a0 = v0;
                jal(ctx, 0x1DD3E4u, gen::fn_RwCameraEndUpdate_004c9d00);
            }
            // 0x001dd3ec
            charge(ctx, 1);
            v0 = 0;
            // 0x001dd3f0 (the shared epilogue, written out on this path)
            charge(ctx, 15);
            ld(ra, sp, 0x50);
            lq(s2, sp, 0x40);
            lq(s1, sp, 0x30);
            lq(s0, sp, 0x20);
            lwc1(f27, sp, 0x1C);
            lwc1(f26, sp, 0x18);
            lwc1(f25, sp, 0x14);
            lwc1(f24, sp, 0x10);
            lwc1(f23, sp, 0xC);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_001dcd40:
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x001dcbcc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001dd3f0 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001DD430 sub_1DD430 [K_FieldIcon_Destroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1DD430(task): frees the "field icon draw" work.
void sub_1DD430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dd430
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1DD444u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001DD460 sub_1DD460 [K_FieldIcon_CreateTask] -- 200 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1DD460(parent, type, priority) -> the "field icon draw" task (kwlnTaskCreate, 560-byte work): +8 = type,
// +4 = (priority == 4184): its own camera pass.
void sub_1DD460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dd460
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = 1;
    a1 = 560;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1DD498u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001dd4b8
        charge(ctx, 15);
        a0 = s3;
        a1 = 0x680000;
        a1 = addiu(a1, 15680);  // "field icon draw"
        a2 = s1;
        a3 = 0x1E0000;
        a3 = addiu(a3, -13472);  // &sub_1DCB60
        t0 = 0x1E0000;
        t0 = addiu(t0, -11216);  // &sub_1DD430
        t1 = s0;
        jal(ctx, 0x1DD4DCu, gen::fn_kwlnTaskCreate_00194b20);
        sw(s2, s0, 8);
        v1 = 4184;
        if (s1 != v1) {
            // 0x001dd504
            charge(ctx, 1);
            sw(zero, s0, 4);
        } else {
            // 0x001dd4f4
            charge(ctx, 4);
            v1 = 1;
            sw(v1, s0, 4);
        }
    } else {
        // 0x001dd4ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001dd508 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001DD530 sub_1DD530 [K_FieldIcon_SetWorldPos] -- 168 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1DD530(task, pos): projects pos with the main camera's view matrix (camera +32, RwV3dTransformPoint
// sub_4C6BE0) to the icon's screen position: +12 = 640 x / z - 16, +16 = 448 y / z - 16, +20 = z.
void sub_1DD530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001dd530
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, f4::kTaskWork);
    jal(ctx, 0x1DD548u, gen::fn_sub_198590_00198590);
    a2 = addiu(v0, 32);
    a0 = addiu(sp, 0x30);
    a1 = s1;
    jal(ctx, 0x1DD55Cu, gen::fn_sub_4C6BE0_004c6be0);
    lwc1(f1, sp, 0x30);
    lwc1(f0, sp, 0x38);
    div_s(f1, f1, f0);
    v1 = 0x44200000;
    mtc1(v1, f0);
    mul_s(f0, f0, f1);
    v1 = 0x41800000;
    mtc1(v1, f2);
    sub_s(f0, f0, f2);
    swc1(f0, s0, 12);
    lwc1(f1, sp, 0x34);
    lwc1(f0, sp, 0x38);
    div_s(f1, f1, f0);
    v1 = 0x43E00000;
    mtc1(v1, f0);
    mul_s(f0, f0, f1);
    sub_s(f0, f0, f2);
    swc1(f0, s0, 16);
    lwc1(f0, sp, 0x38);
    swc1(f0, s0, 20);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001DD600 sub_1DD600 [K_Field_HasPartyPanel] -- 724 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DD600() -> 1 when the field shows the party panel: Tartarus-type scenes (sub_1A01C0) except major 33, flag
// 3111, the Tartarus block-boss rooms 21/50, 22/50..51, 23/50..51, 24/50, 26/50..53, 27/50 and 41..47/50, and the
// rooms 4/10, 39/1, 39/3.
void sub_1DD600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dd600
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    jal(ctx, 0x1DD610u, gen::fn_sub_1A01C0_001a01c0);
    v1 = 1;
    if (v0 == v1) {
        // 0x001dd624
        charge(ctx, 1);
        s0 = v1;
    }
    // 0x001dd628
    charge(ctx, 5);
    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
    lw(v1, v0, f4::scene::kMajor);
    v0 = 33;
    if (v1 == v0) {
        // 0x001dd63c
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x001dd640
    charge(ctx, 6);
    a0 = 3111;
    jal(ctx, 0x1DD644u, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 == v1) {
        // 0x001dd658
        charge(ctx, 1);
        s0 = v1;
    }
    // 0x001dd65c
    charge(ctx, 5);
    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
    lw(v0, v1, f4::scene::kMajor);
    a0 = 21;
    if (v0 == a0) {
        // 0x001dd670
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 != a0) {
            goto L_001dd680;
        }
    L_001dd798:
        charge(ctx, 1);
        s0 = 1;
        goto L_001dd79c;
    }
L_001dd680:
    charge(ctx, 3);
    a0 = 22;
    if (v0 == a0) {
        // 0x001dd68c
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd69c;
    }
L_001dd69c:
    charge(ctx, 3);
    a0 = 22;
    if (v0 == a0) {
        // 0x001dd6a8
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 51;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd6b8;
    }
L_001dd6b8:
    charge(ctx, 3);
    a0 = 23;
    if (v0 == a0) {
        // 0x001dd6c4
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd6d4;
    }
L_001dd6d4:
    charge(ctx, 3);
    a0 = 23;
    if (v0 == a0) {
        // 0x001dd6e0
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 51;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd6f0;
    }
L_001dd6f0:
    charge(ctx, 3);
    a0 = 24;
    if (v0 == a0) {
        // 0x001dd6fc
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd70c;
    }
L_001dd70c:
    charge(ctx, 3);
    a0 = 26;
    if (v0 == a0) {
        // 0x001dd718
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd728;
    }
L_001dd728:
    charge(ctx, 3);
    a0 = 26;
    if (v0 == a0) {
        // 0x001dd734
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 51;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd744;
    }
L_001dd744:
    charge(ctx, 3);
    a0 = 26;
    if (v0 == a0) {
        // 0x001dd750
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 52;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd760;
    }
L_001dd760:
    charge(ctx, 3);
    a0 = 26;
    if (v0 == a0) {
        // 0x001dd76c
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 53;
        if (a1 == a0) {
            goto L_001dd798;
        }
        goto L_001dd77c;
    }
L_001dd77c:
    charge(ctx, 3);
    a0 = 27;
    if (v0 == a0) {
        // 0x001dd788
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd798;
        }
    }
L_001dd79c:
    charge(ctx, 3);
    a0 = 4;
    if (v0 == a0) {
        // 0x001dd7a8
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 10;
        if (a1 != a0) {
            goto L_001dd7b8;
        }
    L_001dd7f0:
        charge(ctx, 1);
        s0 = 1;
        goto L_001dd7f4;
    }
L_001dd7b8:
    charge(ctx, 3);
    a0 = 39;
    if (v0 == a0) {
        // 0x001dd7c4
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 1;
        if (a1 == a0) {
            goto L_001dd7f0;
        }
        goto L_001dd7d4;
    }
L_001dd7d4:
    charge(ctx, 3);
    a0 = 39;
    if (v0 == a0) {
        // 0x001dd7e0
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 3;
        if (a1 == a0) {
            goto L_001dd7f0;
        }
    }
L_001dd7f4:
    charge(ctx, 3);
    a0 = 41;
    if (v0 == a0) {
        // 0x001dd800
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 != a0) {
            goto L_001dd810;
        }
    L_001dd8b8:
        charge(ctx, 1);
        s0 = 1;
        // 0x001dd8bc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = s0;
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_001dd810:
    charge(ctx, 3);
    a0 = 42;
    if (v0 == a0) {
        // 0x001dd81c
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd8b8;
        }
        goto L_001dd82c;
    }
L_001dd82c:
    charge(ctx, 3);
    a0 = 43;
    if (v0 == a0) {
        // 0x001dd838
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd8b8;
        }
        goto L_001dd848;
    }
L_001dd848:
    charge(ctx, 3);
    a0 = 44;
    if (v0 == a0) {
        // 0x001dd854
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd8b8;
        }
        goto L_001dd864;
    }
L_001dd864:
    charge(ctx, 3);
    a0 = 45;
    if (v0 == a0) {
        // 0x001dd870
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd8b8;
        }
        goto L_001dd880;
    }
L_001dd880:
    charge(ctx, 3);
    a0 = 46;
    if (v0 == a0) {
        // 0x001dd88c
        charge(ctx, 4);
        lw(a1, v1, 4);
        a0 = 50;
        if (a1 == a0) {
            goto L_001dd8b8;
        }
        goto L_001dd89c;
    }
L_001dd89c:
    charge(ctx, 3);
    a0 = 47;
    if (v0 == a0) {
        // 0x001dd8a8
        charge(ctx, 4);
        lw(v1, v1, 4);
        v0 = 50;
        if (v1 == v0) {
            goto L_001dd8b8;
        }
    }
    // 0x001dd8bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DD8E0 sub_1DD8E0 [K_Field_UpdatePartyPanel] -- 584 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1DD8E0(): refreshes the party panel (sField +40, sub_18BEE0(panel, member, mode)) for each live party field
// unit (gFldUnitsPc, model and resource present): dead (datUnitIsGenusDead) -> mode 2; otherwise from the member's
// HP / SP (sub_173300 / sub_16C470 over +424 the member id): the hero (id 1) records +388 / +392 and shows mode 3
// when his value rose (else 0); a member records +388 and, when it rose, mode 3 plus its script procedure 8
// (scrCreateTaskFromScriptMemory(10, unit +436, +440, 8)).
void sub_1DD8E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dd8e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x1DD8FCu, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kPartyPanel);
    if (v1 != 0) {
        // 0x001dd910
        charge(ctx, 3);
        s4 = 0;
        for (;;) {
            // 0x001ddaf8
            charge(ctx, 3);
            v1 = slti(s4, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001dd91c
            charge(ctx, 10);
            a1 = 0;
            v1 = sll(s4, 3);
            v1 = subu(v1, s4);
            a0 = sll(v1, 6);
            v1 = 0x870000;
            v1 = addiu(v1, 6048);  // &gFldUnitsPc
            s3 = addu(v1, a0);
            lw(a0, s3, 72);
            if (a0 != 0) {
                // 0x001dd944
                charge(ctx, 3);
                lw(v1, s3, 84);
                if (v1 != 0) {
                    // 0x001dd950
                    charge(ctx, 1);
                    a1 = 1;
                }
            }
            // 0x001dd954
            charge(ctx, 3);
            v1 = sltu(0, a1);
            if (v1 != 0) {
                // 0x001dd960
                charge(ctx, 5);
                jal(ctx, 0x1DD960u, gen::fn_datUnitIsGenusDead_002ff790);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001dd998
                    charge(ctx, 19);
                    v0 = sll(s4, 3);
                    v0 = subu(v0, s4);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    v0 = addu(v0, v1);
                    s2 = addiu(v0, 424);
                    lhu(a0, v0, 424);
                    jal(ctx, 0x1DD9B8u, gen::fn_sub_173300_00173300);
                    s1 = v0 & 0xFF;
                    lh(a0, s2, 0);
                    jal(ctx, 0x1DD9C8u, gen::fn_sub_16C470_0016c470);
                    a1 = v0 & 0xFF;
                    lhu(s0, s2, 0);
                    v0 = 1;
                    if (s0 != v0) {
                        // 0x001dda68
                        charge(ctx, 6);
                        a1 = addiu(s3, 388);
                        lw(v0, s3, 388);
                        a0 = s1 & 0xFF;
                        at = sltu(v0, a0);
                        if (at == 0) {
                            // 0x001ddad8
                            charge(ctx, 7);
                            jal(ctx, 0x1DDAD8u, gen::fn_K_Field_Get_001b9120);
                            a1 = s0 & 0xFFFF;
                            lw(a0, v0, f4::fld::kPartyPanel);
                            a2 = 0;
                            jal(ctx, 0x1DDAECu, gen::fn_sub_18BEE0_0018bee0);
                        } else {
                            // 0x001dda80
                            charge(ctx, 22);
                            v0 = sll(s4, 3);
                            v0 = subu(v0, s4);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6048);  // &gFldUnitsPc
                            s0 = addu(v0, v1);
                            sw(a0, a1, 0);
                            jal(ctx, 0x1DDA9Cu, gen::fn_K_Field_Get_001b9120);
                            lhu(a1, s2, 0);
                            lw(a0, v0, f4::fld::kPartyPanel);
                            a2 = 3;
                            jal(ctx, 0x1DDAB0u, gen::fn_sub_18BEE0_0018bee0);
                            a0 = 10;
                            lw(a1, s0, 436);
                            lw(a2, s0, 440);
                            a3 = 8;
                            jal(ctx, 0x1DDAC8u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                        }
                    } else {
                        // 0x001dd9e4
                        charge(ctx, 14);
                        v0 = sll(s4, 3);
                        v0 = subu(v0, s4);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6048);  // &gFldUnitsPc
                        v1 = addu(v0, v1);
                        v0 = s1 & 0xFF;
                        sw(v0, v1, 388);
                        a0 = addiu(v1, 392);
                        lw(v1, v1, 392);
                        v0 = a1 & 0xFF;
                        at = sltu(v1, v0);
                        if (at == 0) {
                            // 0x001dda44
                            charge(ctx, 9);
                            jal(ctx, 0x1DDA44u, gen::fn_K_Field_Get_001b9120);
                            lhu(a1, s2, 0);
                            lw(a0, v0, f4::fld::kPartyPanel);
                            a2 = 0;
                            jal(ctx, 0x1DDA58u, gen::fn_sub_18BEE0_0018bee0);
                        } else {
                            // 0x001dda1c
                            charge(ctx, 10);
                            sw(v0, a0, 0);
                            jal(ctx, 0x1DDA20u, gen::fn_K_Field_Get_001b9120);
                            lhu(a1, s2, 0);
                            lw(a0, v0, f4::fld::kPartyPanel);
                            a2 = 3;
                            jal(ctx, 0x1DDA34u, gen::fn_sub_18BEE0_0018bee0);
                        }
                    }
                } else {
                    // 0x001dd974
                    charge(ctx, 9);
                    jal(ctx, 0x1DD974u, gen::fn_K_Field_Get_001b9120);
                    lhu(a1, s3, 424);
                    lw(a0, v0, f4::fld::kPartyPanel);
                    a2 = 2;
                    jal(ctx, 0x1DD988u, gen::fn_sub_18BEE0_0018bee0);
                }
            }
            // 0x001ddaf4
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
    }
    // 0x001ddb04 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001DDB30 sub_1DDB30 [K_Field_GetAreaName] -- 356 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DDB30() -> the area name for the area panel: in the dungeon the floor's 26-byte name record (0x67B160 + 26
// floor, The Answer 0x67CFE0) or the literals "Thebel 2F" (400) / "Arqa ???F" (401..403); outside it the scene's
// name index (0x6791A0 [major] -> u16 [minor]) into 0x6792E0.
void sub_1DDB30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ddb30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x1DDB3Cu, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
    s0 = v0;
    if (s0 != 0) {
        // 0x001ddbb0
        charge(ctx, 3);
        v0 = 403;
        if (s0 == v0) {
            // 0x001ddc18
            charge(ctx, 4);
            v0 = 0x680000;
            v0 = addiu(v0, -26038);  // "Arqa ???F"
        } else {
            // 0x001ddbbc
            charge(ctx, 3);
            v0 = 402;
            if (s0 == v0) {
                // 0x001ddc08
                charge(ctx, 4);
                v0 = 0x680000;
                v0 = addiu(v0, -26064);  // "Arqa ???F"
            } else {
                // 0x001ddbc8
                charge(ctx, 3);
                v0 = 401;
                if (s0 == v0) {
                    // 0x001ddbf8
                    charge(ctx, 4);
                    v0 = 0x680000;
                    v0 = addiu(v0, -26090);  // "Arqa ???F"
                } else {
                    // 0x001ddbd4
                    charge(ctx, 3);
                    v0 = 400;
                    if (s0 == v0) {
                        // 0x001ddbe8
                        charge(ctx, 4);
                        v0 = 0x680000;
                        v0 = addiu(v0, -26116);  // "Thebel 2F"
                    } else {
                        // 0x001ddbe0
                        charge(ctx, 2);
                        // 0x001ddc28
                        charge(ctx, 4);
                        jal(ctx, 0x1DDC28u, gen::fn_sub_17D800_0017d800);
                        if (v0 != 0) {
                            // 0x001ddc60
                            charge(ctx, 8);
                            v0 = sll(s0, 1);
                            v0 = addu(v0, s0);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, s0);
                            v1 = sll(v0, 1);
                            v0 = 0x680000;
                            v0 = addiu(v0, -12320);  // &0x67CFE0
                            v0 = addu(v0, v1);
                        } else {
                            // 0x001ddc38
                            charge(ctx, 10);
                            v0 = sll(s0, 1);
                            v0 = addu(v0, s0);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, s0);
                            v1 = sll(v0, 1);
                            v0 = 0x680000;
                            v0 = addiu(v0, -20128);  // &0x67B160
                            v0 = addu(v0, v1);
                        }
                    }
                }
            }
        }
    } else {
        // 0x001ddb50
        charge(ctx, 10);
        a1 = 0;
        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        lw(v0, a0, f4::scene::kMajor);
        v1 = sll(v0, 2);
        v0 = 0x680000;
        v0 = addiu(v0, -28256);  // &0x6791A0
        v0 = addu(v0, v1);
        lw(v1, v0, 0);
        if (v1 != 0) {
            // 0x001ddb78
            charge(ctx, 4);
            lw(v0, a0, 4);
            v0 = sll(v0, 1);
            v0 = addu(v1, v0);
            lhu(a1, v0, 0);
        }
        // 0x001ddb88
        charge(ctx, 10);
        v0 = sll(a1, 1);
        v0 = addu(v0, a1);
        v0 = sll(v0, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 1);
        v0 = 0x680000;
        v0 = addiu(v0, -27936);  // &0x6792E0
        v0 = addu(v0, v1);
    }
    // 0x001ddc80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DDCA0 sub_1DDCA0 [K_Field_SetAreaName] -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DDCA0(index): shows an area name on the area panel (sField +44): index -1 = the current one (sub_1DDB30), else
// record 0x6792E0 + 26 index (sub_18E5C0).
void sub_1DDCA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ddca0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1DDCB0u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kAreaPanel);
    if (v1 != 0) {
        // 0x001ddcc4
        charge(ctx, 3);
        v0 = si(-1);
        if (s0 != v0) {
            // 0x001ddce4
            charge(ctx, 8);
            v0 = sll(s0, 1);
            v0 = addu(v0, s0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            v1 = sll(v0, 1);
            v0 = 0x680000;
            v0 = addiu(v0, -27936);  // &0x6792E0
            s0 = addu(v0, v1);
        } else {
            // 0x001ddcd0
            charge(ctx, 5);
            jal(ctx, 0x1DDCD0u, gen::fn_sub_1DDB30_001ddb30);
            s0 = v0;
        }
        // 0x001ddd04
        charge(ctx, 6);
        jal(ctx, 0x1DDD04u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kAreaPanel);
        a1 = s0;
        jal(ctx, 0x1DDD14u, gen::fn_sub_18E5C0_0018e5c0);
    }
    // 0x001ddd1c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DDD30 sub_1DDD30 [K_Field_HasMiniMap] -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DDD30() -> 1 when the field has a mini-map: Tartarus-type scenes (sub_1A01C0) except 32/2, 31/1, 35/1, 37/1 and
// major 33. Caller: Y_SMap_CreateSmapDrawTask.
void sub_1DDD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ddd30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    jal(ctx, 0x1DDD40u, gen::fn_sub_1A01C0_001a01c0);
    v1 = 1;
    if (v0 == v1) {
        // 0x001ddd54
        charge(ctx, 1);
        s0 = v1;
    }
    // 0x001ddd58
    charge(ctx, 5);
    lw(a1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
    lw(a0, a1, f4::scene::kMajor);
    v0 = 32;
    if (a0 == v0) {
        // 0x001ddd6c
        charge(ctx, 4);
        lw(v1, a1, 4);
        v0 = 2;
        if (v1 != v0) {
            goto L_001ddd7c;
        }
    L_001ddddc:
        charge(ctx, 1);
        s0 = 0;
        // 0x001ddde0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        v0 = s0;
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_001ddd7c:
    charge(ctx, 3);
    v0 = 31;
    if (a0 == v0) {
        // 0x001ddd88
        charge(ctx, 4);
        lw(v1, a1, 4);
        v0 = 1;
        if (v1 == v0) {
            goto L_001ddddc;
        }
        goto L_001ddd98;
    }
L_001ddd98:
    charge(ctx, 3);
    v0 = 35;
    if (a0 == v0) {
        // 0x001ddda4
        charge(ctx, 4);
        lw(v1, a1, 4);
        v0 = 1;
        if (v1 == v0) {
            goto L_001ddddc;
        }
        goto L_001dddb4;
    }
L_001dddb4:
    charge(ctx, 3);
    v0 = 37;
    if (a0 == v0) {
        // 0x001dddc0
        charge(ctx, 4);
        lw(v1, a1, 4);
        v0 = 1;
        if (v1 == v0) {
            goto L_001ddddc;
        }
        goto L_001dddd0;
    }
L_001dddd0:
    charge(ctx, 3);
    v0 = 33;
    if (a0 == v0) {
        goto L_001ddddc;
    }
    // 0x001ddde0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DDE00 sub_1DDE00 [K_FldPc_IsShown] -- 2084 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DDE00(member) -> 1 when party member `member` follows the hero in this field. Members 13 / 10: never in field
// 14/5; 7: never in 14/5 or major 33; 5: never in 14/5, with flag 3119 or in major 33; 2: never in majors 6 / 7 or
// 14/5; otherwise every member but the hero follows when its party slot state (sub_16C970) is 128. The hero (1):
// in The Answer's majors 4 / 5, the sub_1A0310 scenes, 7/6, 8/1, 9/1 at time 8 and major 33, and outside the
// Tartarus-type scenes (sub_1A01C0) and the block rooms 21..27/50.., 41..47/50, 39/1..3 (or major 6 with flag
// 3680): when flag 3125 is clear; in Tartarus-type scenes by the slot state; never in 14/5 or major 7 with flag 3584.
void sub_1DDE00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001dde00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 13;
    if (s0 == v0) {
        // 0x001de580
        charge(ctx, 5);
        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        lw(v1, a0, f4::scene::kMajor);
        v0 = 14;
        if (v1 == v0) {
            // 0x001de594
            charge(ctx, 4);
            lw(v1, a0, 4);
            v0 = 5;
            if (v1 != v0) {
                goto L_001de5b0;
            }
            // 0x001de5a4
            charge(ctx, 3);
            v0 = 0;
            // 0x001de610 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_001de5b0:
        charge(ctx, 7);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1DE5B8u, gen::fn_sub_16C970_0016c970);
        v1 = 128;
        if (v0 != v1) {
            // 0x001de5d8
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x001de5cc
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x001dde1c
        charge(ctx, 3);
        v0 = 10;
        if (s0 == v0) {
            // 0x001de51c
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            v0 = 14;
            if (v1 == v0) {
                // 0x001de530
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 5;
                if (v1 != v0) {
                    goto L_001de54c;
                }
                // 0x001de540
                charge(ctx, 3);
                v0 = 0;
                // 0x001de610 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_001de54c:
            charge(ctx, 7);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1DE554u, gen::fn_sub_16C970_0016c970);
            v1 = 128;
            if (v0 != v1) {
                // 0x001de574
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x001de568
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x001dde28
            charge(ctx, 3);
            a2 = 7;
            if (s0 == a2) {
                // 0x001de4a0
                charge(ctx, 5);
                lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                lw(a0, v1, f4::scene::kMajor);
                v0 = 14;
                if (a0 == v0) {
                    // 0x001de4b4
                    charge(ctx, 4);
                    lw(v1, v1, 4);
                    v0 = 5;
                    if (v1 != v0) {
                        goto L_001de4d0;
                    }
                    // 0x001de4c4
                    charge(ctx, 3);
                    v0 = 0;
                    // 0x001de610 (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(ra, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x20);
                    return;
                }
            L_001de4d0:
                charge(ctx, 3);
                v0 = 33;
                if (a0 != v0) {
                    // 0x001de4e8
                    charge(ctx, 7);
                    a0 = dsll32(s0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x1DE4F0u, gen::fn_sub_16C970_0016c970);
                    v1 = 128;
                    if (v0 != v1) {
                        // 0x001de510
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x001de504
                        charge(ctx, 3);
                        v0 = 1;
                    }
                } else {
                    // 0x001de4dc
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x001dde34
                charge(ctx, 3);
                a1 = 5;
                if (s0 == a1) {
                    // 0x001de3fc
                    charge(ctx, 5);
                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    lw(v1, a0, f4::scene::kMajor);
                    v0 = 14;
                    if (v1 == v0) {
                        // 0x001de410
                        charge(ctx, 3);
                        lw(v0, a0, 4);
                        if (v0 != a1) {
                            goto L_001de428;
                        }
                        // 0x001de41c
                        charge(ctx, 3);
                        v0 = 0;
                        // 0x001de610 (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_001de428:
                    charge(ctx, 6);
                    a0 = 3119;
                    jal(ctx, 0x1DE42Cu, gen::fn_datGetFlag_0016f190);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x001de44c
                        charge(ctx, 5);
                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(v1, v0, f4::scene::kMajor);
                        v0 = 33;
                        if (v1 != v0) {
                            // 0x001de46c
                            charge(ctx, 7);
                            a0 = dsll32(s0, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x1DE474u, gen::fn_sub_16C970_0016c970);
                            v1 = 128;
                            if (v0 != v1) {
                                // 0x001de494
                                charge(ctx, 3);
                                v0 = 0;
                            } else {
                                // 0x001de488
                                charge(ctx, 3);
                                v0 = 1;
                            }
                        } else {
                            // 0x001de460
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x001de440
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x001dde40
                    charge(ctx, 3);
                    v0 = 2;
                    if (s0 == v0) {
                        // 0x001de37c
                        charge(ctx, 5);
                        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(v1, a0, f4::scene::kMajor);
                        v0 = 6;
                        if (v1 != v0) {
                            // 0x001de390
                            charge(ctx, 2);
                            if (v1 == a2) {
                                goto L_001de398;
                            }
                            // 0x001de3a4
                            charge(ctx, 3);
                            v0 = 14;
                            if (v1 == v0) {
                                // 0x001de3b0
                                charge(ctx, 3);
                                lw(v0, a0, 4);
                                if (v0 != a1) {
                                    goto L_001de3c8;
                                }
                                // 0x001de3bc
                                charge(ctx, 3);
                                v0 = 0;
                                // 0x001de610 (the shared epilogue, written out on this path)
                                charge(ctx, 5);
                                ld(ra, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x20);
                                return;
                            }
                        L_001de3c8:
                            charge(ctx, 7);
                            a0 = dsll32(s0, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x1DE3D0u, gen::fn_sub_16C970_0016c970);
                            v1 = 128;
                            if (v0 != v1) {
                                // 0x001de3f0
                                charge(ctx, 3);
                                v0 = 0;
                            } else {
                                // 0x001de3e4
                                charge(ctx, 3);
                                v0 = 1;
                            }
                            // 0x001de610 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            ld(ra, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_001de398:
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x001dde4c
                        charge(ctx, 3);
                        v0 = 1;
                        if (s0 == v0) {
                            // 0x001dde60
                            charge(ctx, 5);
                            jal(ctx, 0x1DDE60u, gen::fn_sub_17D800_0017d800);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x001dde74
                                charge(ctx, 5);
                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v1, v0, f4::scene::kMajor);
                                v0 = 4;
                                if (v1 != v0) {
                                    // 0x001dde88
                                    charge(ctx, 3);
                                    v0 = 5;
                                    if (v1 != v0) {
                                        goto L_001ddec0;
                                    }
                                    goto L_001dde94;
                                }
                            L_001dde94:
                                charge(ctx, 5);
                                a0 = 3125;
                                jal(ctx, 0x1DDE98u, gen::fn_datGetFlag_0016f190);
                                if (v0 == 0) {
                                    // 0x001ddeb4
                                    charge(ctx, 3);
                                    v0 = 1;
                                } else {
                                    // 0x001ddea8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x001de610 (the shared epilogue, written out on this path)
                                charge(ctx, 5);
                                ld(ra, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x20);
                                return;
                            }
                        L_001ddec0:
                            charge(ctx, 5);
                            jal(ctx, 0x1DDEC0u, gen::fn_sub_1A0310_001a0310);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x001ddf00
                                charge(ctx, 5);
                                lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v1, a0, f4::scene::kMajor);
                                v0 = 7;
                                if (v1 == v0) {
                                    // 0x001ddf14
                                    charge(ctx, 4);
                                    lw(v1, a0, 4);
                                    v0 = 6;
                                    if (v1 != v0) {
                                        goto L_001ddf3c;
                                    }
                                    // 0x001ddf24
                                    charge(ctx, 6);
                                    jal(ctx, 0x1DDF24u, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 != v0) {
                                        goto L_001ddf3c;
                                    }
                                L_001ddfb4:
                                    charge(ctx, 5);
                                    a0 = 3125;
                                    jal(ctx, 0x1DDFB8u, gen::fn_datGetFlag_0016f190);
                                    if (v0 == 0) {
                                        // 0x001ddfd4
                                        charge(ctx, 3);
                                        v0 = 1;
                                    } else {
                                        // 0x001ddfc8
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x001de610 (the shared epilogue, written out on this path)
                                    charge(ctx, 5);
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_001ddf3c:
                                charge(ctx, 5);
                                lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v1, a0, f4::scene::kMajor);
                                v0 = 8;
                                if (v1 == v0) {
                                    // 0x001ddf50
                                    charge(ctx, 4);
                                    lw(v1, a0, 4);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_001ddf78;
                                    }
                                    // 0x001ddf60
                                    charge(ctx, 6);
                                    jal(ctx, 0x1DDF60u, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 == v0) {
                                        goto L_001ddfb4;
                                    }
                                    goto L_001ddf78;
                                }
                            L_001ddf78:
                                charge(ctx, 5);
                                lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v1, a0, f4::scene::kMajor);
                                v0 = 9;
                                if (v1 == v0) {
                                    // 0x001ddf8c
                                    charge(ctx, 4);
                                    lw(v1, a0, 4);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_001ddfe0;
                                    }
                                    // 0x001ddf9c
                                    charge(ctx, 6);
                                    jal(ctx, 0x1DDF9Cu, gen::fn_datGetTime_0016ef30);
                                    v1 = v0 & 0xFF;
                                    v0 = 8;
                                    if (v1 != v0) {
                                        goto L_001ddfe0;
                                    }
                                    goto L_001ddfb4;
                                }
                            L_001ddfe0:
                                charge(ctx, 5);
                                lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(a0, v1, f4::scene::kMajor);
                                v0 = 14;
                                if (a0 == v0) {
                                    // 0x001ddff4
                                    charge(ctx, 4);
                                    lw(v1, v1, 4);
                                    v0 = 5;
                                    if (v1 != v0) {
                                        goto L_001de010;
                                    }
                                    // 0x001de004
                                    charge(ctx, 3);
                                    v0 = 0;
                                    // 0x001de610 (the shared epilogue, written out on this path)
                                    charge(ctx, 5);
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_001de010:
                                charge(ctx, 3);
                                v0 = 33;
                                if (a0 != v0) {
                                    // 0x001de048
                                    charge(ctx, 3);
                                    v0 = 7;
                                    if (a0 == v0) {
                                        // 0x001de054
                                        charge(ctx, 6);
                                        a0 = 3584;
                                        jal(ctx, 0x1DE058u, gen::fn_datGetFlag_0016f190);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            goto L_001de078;
                                        }
                                        // 0x001de06c
                                        charge(ctx, 3);
                                        v0 = 0;
                                        // 0x001de610 (the shared epilogue, written out on this path)
                                        charge(ctx, 5);
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001de078:
                                    charge(ctx, 5);
                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, v0, f4::scene::kMajor);
                                    v0 = 6;
                                    if (v1 == v0) {
                                        // 0x001de08c
                                        charge(ctx, 6);
                                        a0 = 3680;
                                        jal(ctx, 0x1DE090u, gen::fn_datGetFlag_0016f190);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            goto L_001de0d0;
                                        }
                                        // 0x001de0a4
                                        charge(ctx, 5);
                                        a0 = 3125;
                                        jal(ctx, 0x1DE0A8u, gen::fn_datGetFlag_0016f190);
                                        if (v0 == 0) {
                                            // 0x001de0c4
                                            charge(ctx, 3);
                                            v0 = 1;
                                        } else {
                                            // 0x001de0b8
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x001de610 (the shared epilogue, written out on this path)
                                        charge(ctx, 5);
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001de0d0:
                                    charge(ctx, 5);
                                    jal(ctx, 0x1DE0D0u, gen::fn_sub_1A01C0_001a01c0);
                                    v1 = 1;
                                    if (v0 != v1) {
                                        // 0x001de0e4
                                        charge(ctx, 5);
                                        lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v0, v1, f4::scene::kMajor);
                                        a0 = 21;
                                        if (v0 == a0) {
                                            // 0x001de0f8
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de108;
                                        }
                                    L_001de108:
                                        charge(ctx, 3);
                                        a0 = 22;
                                        if (v0 == a0) {
                                            // 0x001de114
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de124;
                                        }
                                    L_001de124:
                                        charge(ctx, 3);
                                        a0 = 22;
                                        if (v0 == a0) {
                                            // 0x001de130
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 51;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de140;
                                        }
                                    L_001de140:
                                        charge(ctx, 3);
                                        a0 = 23;
                                        if (v0 == a0) {
                                            // 0x001de14c
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de15c;
                                        }
                                    L_001de15c:
                                        charge(ctx, 3);
                                        a0 = 23;
                                        if (v0 == a0) {
                                            // 0x001de168
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 51;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de178;
                                        }
                                    L_001de178:
                                        charge(ctx, 3);
                                        a0 = 24;
                                        if (v0 == a0) {
                                            // 0x001de184
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de194;
                                        }
                                    L_001de194:
                                        charge(ctx, 3);
                                        a0 = 24;
                                        if (v0 == a0) {
                                            // 0x001de1a0
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 51;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de1b0;
                                        }
                                    L_001de1b0:
                                        charge(ctx, 3);
                                        a0 = 25;
                                        if (v0 == a0) {
                                            // 0x001de1bc
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de1cc;
                                        }
                                    L_001de1cc:
                                        charge(ctx, 3);
                                        a0 = 26;
                                        if (v0 == a0) {
                                            // 0x001de1d8
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de1e8;
                                        }
                                    L_001de1e8:
                                        charge(ctx, 3);
                                        a0 = 27;
                                        if (v0 == a0) {
                                            // 0x001de1f4
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de204;
                                        }
                                    L_001de204:
                                        charge(ctx, 3);
                                        a0 = 41;
                                        if (v0 == a0) {
                                            // 0x001de210
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de220;
                                        }
                                    L_001de220:
                                        charge(ctx, 3);
                                        a0 = 42;
                                        if (v0 == a0) {
                                            // 0x001de22c
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de23c;
                                        }
                                    L_001de23c:
                                        charge(ctx, 3);
                                        a0 = 43;
                                        if (v0 == a0) {
                                            // 0x001de248
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de258;
                                        }
                                    L_001de258:
                                        charge(ctx, 3);
                                        a0 = 44;
                                        if (v0 == a0) {
                                            // 0x001de264
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de274;
                                        }
                                    L_001de274:
                                        charge(ctx, 3);
                                        a0 = 45;
                                        if (v0 == a0) {
                                            // 0x001de280
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de290;
                                        }
                                    L_001de290:
                                        charge(ctx, 3);
                                        a0 = 46;
                                        if (v0 == a0) {
                                            // 0x001de29c
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de2ac;
                                        }
                                    L_001de2ac:
                                        charge(ctx, 3);
                                        a0 = 47;
                                        if (v0 == a0) {
                                            // 0x001de2b8
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 50;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de2c8;
                                        }
                                    L_001de2c8:
                                        charge(ctx, 3);
                                        a0 = 39;
                                        if (v0 == a0) {
                                            // 0x001de2d4
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 1;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de2e4;
                                        }
                                    L_001de2e4:
                                        charge(ctx, 3);
                                        a0 = 39;
                                        if (v0 == a0) {
                                            // 0x001de2f0
                                            charge(ctx, 4);
                                            lw(a1, v1, 4);
                                            a0 = 2;
                                            if (a1 == a0) {
                                                goto L_001de31c;
                                            }
                                            goto L_001de300;
                                        }
                                    L_001de300:
                                        charge(ctx, 3);
                                        a0 = 39;
                                        if (v0 == a0) {
                                            // 0x001de30c
                                            charge(ctx, 4);
                                            lw(v1, v1, 4);
                                            v0 = 3;
                                            if (v1 != v0) {
                                                goto L_001de350;
                                            }
                                            goto L_001de31c;
                                        }
                                    L_001de350:
                                        charge(ctx, 5);
                                        a0 = 3125;
                                        jal(ctx, 0x1DE354u, gen::fn_datGetFlag_0016f190);
                                        if (v0 == 0) {
                                            // 0x001de370
                                            charge(ctx, 3);
                                            v0 = 1;
                                        } else {
                                            // 0x001de364
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x001de610 (the shared epilogue, written out on this path)
                                        charge(ctx, 5);
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001de31c:
                                    charge(ctx, 7);
                                    a0 = dsll32(s0, 16);
                                    a0 = dsra32(a0, 16);
                                    jal(ctx, 0x1DE324u, gen::fn_sub_16C970_0016c970);
                                    v1 = 128;
                                    if (v0 != v1) {
                                        // 0x001de344
                                        charge(ctx, 3);
                                        v0 = 0;
                                    } else {
                                        // 0x001de338
                                        charge(ctx, 3);
                                        v0 = 1;
                                    }
                                } else {
                                    // 0x001de01c
                                    charge(ctx, 5);
                                    a0 = 3125;
                                    jal(ctx, 0x1DE020u, gen::fn_datGetFlag_0016f190);
                                    if (v0 == 0) {
                                        // 0x001de03c
                                        charge(ctx, 3);
                                        v0 = 1;
                                    } else {
                                        // 0x001de030
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                }
                            } else {
                                // 0x001dded4
                                charge(ctx, 5);
                                a0 = 3125;
                                jal(ctx, 0x1DDED8u, gen::fn_datGetFlag_0016f190);
                                if (v0 == 0) {
                                    // 0x001ddef4
                                    charge(ctx, 3);
                                    v0 = 1;
                                } else {
                                    // 0x001ddee8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            }
                        } else {
                            // 0x001dde58
                            charge(ctx, 2);
                            // 0x001de5e4
                            charge(ctx, 7);
                            a0 = dsll32(s0, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x1DE5ECu, gen::fn_sub_16C970_0016c970);
                            v1 = 128;
                            if (v0 != v1) {
                                // 0x001de60c
                                charge(ctx, 1);
                                v0 = 0;
                            } else {
                                // 0x001de600
                                charge(ctx, 3);
                                v0 = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x001de610 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DE630 sub_1DE630 [K_FldPc_GetWalkMode] -- 1804 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DE630(member) -> the walk animation set of party member `member` (1 slow, 2 / 3 normal; 0 for 6 outside
// 14/5): per member the same scene rules as sub_1DDE00 (14/5 and major 33 force 1; flag 3119 for member 5; majors
// 6 / 7 for member 2; the hero: 3, or 2 with flag 3125, in the town scenes; 3 in Tartarus-type scenes).
// Callers: the footstep supporter (sub_1DA020) and the virtual pad (sub_1E05B0).
void sub_1DE630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001de630
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    a3 = 6;
    if (a0 == a3) {
        // 0x001decf0
        charge(ctx, 5);
        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        lw(v1, a0, f4::scene::kMajor);
        v0 = 14;
        if (v1 == v0) {
            // 0x001ded04
            charge(ctx, 4);
            lw(v1, a0, 4);
            v0 = 5;
            if (v1 == v0) {
                // 0x001ded14
                charge(ctx, 3);
                s0 = 1;
            }
        }
    } else {
        // 0x001de64c
        charge(ctx, 3);
        v0 = 13;
        if (a0 == v0) {
            // 0x001decb4
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            v0 = 14;
            if (v1 == v0) {
                // 0x001decc8
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 5;
                if (v1 != v0) {
                    goto L_001dece4;
                }
                // 0x001decd8
                charge(ctx, 3);
                s0 = 1;
                // 0x001ded24 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                v0 = s0;
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_001dece4:
            charge(ctx, 3);
            s0 = 3;
        } else {
            // 0x001de658
            charge(ctx, 3);
            v0 = 10;
            if (a0 == v0) {
                // 0x001dec78
                charge(ctx, 5);
                lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                lw(v1, a0, f4::scene::kMajor);
                v0 = 14;
                if (v1 == v0) {
                    // 0x001dec8c
                    charge(ctx, 4);
                    lw(v1, a0, 4);
                    v0 = 5;
                    if (v1 != v0) {
                        goto L_001deca8;
                    }
                    // 0x001dec9c
                    charge(ctx, 3);
                    s0 = 1;
                    // 0x001ded24 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    v0 = s0;
                    ld(ra, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x20);
                    return;
                }
            L_001deca8:
                charge(ctx, 3);
                s0 = 3;
            } else {
                // 0x001de664
                charge(ctx, 3);
                a2 = 7;
                if (a0 == a2) {
                    // 0x001dec24
                    charge(ctx, 5);
                    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    lw(a0, v1, f4::scene::kMajor);
                    v0 = 14;
                    if (a0 == v0) {
                        // 0x001dec38
                        charge(ctx, 4);
                        lw(v1, v1, 4);
                        v0 = 5;
                        if (v1 != v0) {
                            goto L_001dec54;
                        }
                        // 0x001dec48
                        charge(ctx, 3);
                        s0 = 1;
                        // 0x001ded24 (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        v0 = s0;
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_001dec54:
                    charge(ctx, 3);
                    v0 = 33;
                    if (a0 != v0) {
                        // 0x001dec6c
                        charge(ctx, 3);
                        s0 = 3;
                    } else {
                        // 0x001dec60
                        charge(ctx, 3);
                        s0 = 1;
                    }
                } else {
                    // 0x001de670
                    charge(ctx, 3);
                    a1 = 5;
                    if (a0 == a1) {
                        // 0x001debb0
                        charge(ctx, 5);
                        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(v1, a0, f4::scene::kMajor);
                        v0 = 14;
                        if (v1 == v0) {
                            // 0x001debc4
                            charge(ctx, 3);
                            lw(v0, a0, 4);
                            if (v0 != a1) {
                                goto L_001debdc;
                            }
                            // 0x001debd0
                            charge(ctx, 3);
                            s0 = 1;
                            // 0x001ded24 (the shared epilogue, written out on this path)
                            charge(ctx, 6);
                            v0 = s0;
                            ld(ra, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_001debdc:
                        charge(ctx, 6);
                        a0 = 3119;
                        jal(ctx, 0x1DEBE0u, gen::fn_datGetFlag_0016f190);
                        s0 = 1;
                        if (v0 != s0) {
                            // 0x001debfc
                            charge(ctx, 5);
                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            lw(v1, v0, f4::scene::kMajor);
                            v0 = 33;
                            if (v1 != v0) {
                                // 0x001dec18
                                charge(ctx, 3);
                                s0 = 3;
                            } else {
                                // 0x001dec10
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x001debf4
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x001de67c
                        charge(ctx, 3);
                        v0 = 2;
                        if (a0 == v0) {
                            // 0x001deb5c
                            charge(ctx, 4);
                            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            lw(v1, a0, f4::scene::kMajor);
                            if (v1 != a3) {
                                // 0x001deb6c
                                charge(ctx, 2);
                                if (v1 == a2) {
                                    goto L_001deb74;
                                }
                                // 0x001deb80
                                charge(ctx, 3);
                                v0 = 14;
                                if (v1 == v0) {
                                    // 0x001deb8c
                                    charge(ctx, 3);
                                    lw(v0, a0, 4);
                                    if (v0 != a1) {
                                        goto L_001deba4;
                                    }
                                    // 0x001deb98
                                    charge(ctx, 3);
                                    s0 = 1;
                                    // 0x001ded24 (the shared epilogue, written out on this path)
                                    charge(ctx, 6);
                                    v0 = s0;
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_001deba4:
                                charge(ctx, 3);
                                s0 = 3;
                                // 0x001ded24 (the shared epilogue, written out on this path)
                                charge(ctx, 6);
                                v0 = s0;
                                ld(ra, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x20);
                                return;
                            }
                        L_001deb74:
                            charge(ctx, 3);
                            s0 = 1;
                        } else {
                            // 0x001de688
                            charge(ctx, 3);
                            v0 = 1;
                            if (a0 == v0) {
                                // 0x001de69c
                                charge(ctx, 5);
                                jal(ctx, 0x1DE69Cu, gen::fn_sub_17D800_0017d800);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x001de6b0
                                    charge(ctx, 5);
                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, v0, f4::scene::kMajor);
                                    v0 = 4;
                                    if (v1 != v0) {
                                        // 0x001de6c4
                                        charge(ctx, 3);
                                        v0 = 5;
                                        if (v1 != v0) {
                                            goto L_001de6f4;
                                        }
                                        goto L_001de6d0;
                                    }
                                L_001de6d0:
                                    charge(ctx, 6);
                                    s0 = 3;
                                    a0 = 3125;
                                    jal(ctx, 0x1DE6D8u, gen::fn_datGetFlag_0016f190);
                                    if (v0 != 0) {
                                        // 0x001de6e8
                                        charge(ctx, 3);
                                        s0 = addiu(s0, -1);
                                    }
                                    // 0x001ded24 (the shared epilogue, written out on this path)
                                    charge(ctx, 6);
                                    v0 = s0;
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_001de6f4:
                                charge(ctx, 5);
                                jal(ctx, 0x1DE6F4u, gen::fn_sub_1A0310_001a0310);
                                v1 = 1;
                                if (v0 != v1) {
                                    // 0x001de72c
                                    charge(ctx, 5);
                                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, a0, f4::scene::kMajor);
                                    v0 = 7;
                                    if (v1 == v0) {
                                        // 0x001de740
                                        charge(ctx, 4);
                                        lw(v1, a0, 4);
                                        v0 = 6;
                                        if (v1 != v0) {
                                            goto L_001de768;
                                        }
                                        // 0x001de750
                                        charge(ctx, 6);
                                        jal(ctx, 0x1DE750u, gen::fn_datGetTime_0016ef30);
                                        v1 = v0 & 0xFF;
                                        v0 = 8;
                                        if (v1 != v0) {
                                            goto L_001de768;
                                        }
                                    L_001de7e0:
                                        charge(ctx, 6);
                                        s0 = 3;
                                        a0 = 3125;
                                        jal(ctx, 0x1DE7E8u, gen::fn_datGetFlag_0016f190);
                                        if (v0 != 0) {
                                            // 0x001de7f8
                                            charge(ctx, 3);
                                            s0 = addiu(s0, -1);
                                        }
                                        // 0x001ded24 (the shared epilogue, written out on this path)
                                        charge(ctx, 6);
                                        v0 = s0;
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001de768:
                                    charge(ctx, 5);
                                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, a0, f4::scene::kMajor);
                                    v0 = 8;
                                    if (v1 == v0) {
                                        // 0x001de77c
                                        charge(ctx, 4);
                                        lw(v1, a0, 4);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            goto L_001de7a4;
                                        }
                                        // 0x001de78c
                                        charge(ctx, 6);
                                        jal(ctx, 0x1DE78Cu, gen::fn_datGetTime_0016ef30);
                                        v1 = v0 & 0xFF;
                                        v0 = 8;
                                        if (v1 == v0) {
                                            goto L_001de7e0;
                                        }
                                        goto L_001de7a4;
                                    }
                                L_001de7a4:
                                    charge(ctx, 5);
                                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, a0, f4::scene::kMajor);
                                    v0 = 9;
                                    if (v1 == v0) {
                                        // 0x001de7b8
                                        charge(ctx, 4);
                                        lw(v1, a0, 4);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            goto L_001de804;
                                        }
                                        // 0x001de7c8
                                        charge(ctx, 6);
                                        jal(ctx, 0x1DE7C8u, gen::fn_datGetTime_0016ef30);
                                        v1 = v0 & 0xFF;
                                        v0 = 8;
                                        if (v1 != v0) {
                                            goto L_001de804;
                                        }
                                        goto L_001de7e0;
                                    }
                                L_001de804:
                                    charge(ctx, 5);
                                    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(a0, v1, f4::scene::kMajor);
                                    v0 = 14;
                                    if (a0 == v0) {
                                        // 0x001de818
                                        charge(ctx, 4);
                                        lw(v1, v1, 4);
                                        v0 = 5;
                                        if (v1 != v0) {
                                            goto L_001de834;
                                        }
                                        // 0x001de828
                                        charge(ctx, 3);
                                        s0 = 1;
                                        // 0x001ded24 (the shared epilogue, written out on this path)
                                        charge(ctx, 6);
                                        v0 = s0;
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001de834:
                                    charge(ctx, 3);
                                    v0 = 33;
                                    if (a0 != v0) {
                                        // 0x001de864
                                        charge(ctx, 3);
                                        v0 = 7;
                                        if (a0 == v0) {
                                            // 0x001de870
                                            charge(ctx, 6);
                                            a0 = 3584;
                                            jal(ctx, 0x1DE874u, gen::fn_datGetFlag_0016f190);
                                            s0 = 1;
                                            if (v0 != s0) {
                                                goto L_001de890;
                                            }
                                            // 0x001de888
                                            charge(ctx, 2);
                                            // 0x001ded24 (the shared epilogue, written out on this path)
                                            charge(ctx, 6);
                                            v0 = s0;
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_001de890:
                                        charge(ctx, 5);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v1, v0, f4::scene::kMajor);
                                        v0 = 6;
                                        if (v1 == v0) {
                                            // 0x001de8a4
                                            charge(ctx, 6);
                                            a0 = 3680;
                                            jal(ctx, 0x1DE8A8u, gen::fn_datGetFlag_0016f190);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                goto L_001de8e0;
                                            }
                                            // 0x001de8bc
                                            charge(ctx, 6);
                                            s0 = 3;
                                            a0 = 3125;
                                            jal(ctx, 0x1DE8C4u, gen::fn_datGetFlag_0016f190);
                                            if (v0 != 0) {
                                                // 0x001de8d4
                                                charge(ctx, 3);
                                                s0 = addiu(s0, -1);
                                            }
                                            // 0x001ded24 (the shared epilogue, written out on this path)
                                            charge(ctx, 6);
                                            v0 = s0;
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_001de8e0:
                                        charge(ctx, 5);
                                        jal(ctx, 0x1DE8E0u, gen::fn_sub_1A01C0_001a01c0);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x001de8f4
                                            charge(ctx, 5);
                                            lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                            lw(v0, v1, f4::scene::kMajor);
                                            a0 = 21;
                                            if (v0 == a0) {
                                                // 0x001de908
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de918;
                                            }
                                        L_001de918:
                                            charge(ctx, 3);
                                            a0 = 22;
                                            if (v0 == a0) {
                                                // 0x001de924
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de934;
                                            }
                                        L_001de934:
                                            charge(ctx, 3);
                                            a0 = 22;
                                            if (v0 == a0) {
                                                // 0x001de940
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 51;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de950;
                                            }
                                        L_001de950:
                                            charge(ctx, 3);
                                            a0 = 23;
                                            if (v0 == a0) {
                                                // 0x001de95c
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de96c;
                                            }
                                        L_001de96c:
                                            charge(ctx, 3);
                                            a0 = 23;
                                            if (v0 == a0) {
                                                // 0x001de978
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 51;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de988;
                                            }
                                        L_001de988:
                                            charge(ctx, 3);
                                            a0 = 24;
                                            if (v0 == a0) {
                                                // 0x001de994
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de9a4;
                                            }
                                        L_001de9a4:
                                            charge(ctx, 3);
                                            a0 = 24;
                                            if (v0 == a0) {
                                                // 0x001de9b0
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 51;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de9c0;
                                            }
                                        L_001de9c0:
                                            charge(ctx, 3);
                                            a0 = 25;
                                            if (v0 == a0) {
                                                // 0x001de9cc
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de9dc;
                                            }
                                        L_001de9dc:
                                            charge(ctx, 3);
                                            a0 = 26;
                                            if (v0 == a0) {
                                                // 0x001de9e8
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001de9f8;
                                            }
                                        L_001de9f8:
                                            charge(ctx, 3);
                                            a0 = 27;
                                            if (v0 == a0) {
                                                // 0x001dea04
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001dea14;
                                            }
                                        L_001dea14:
                                            charge(ctx, 3);
                                            a0 = 41;
                                            if (v0 == a0) {
                                                // 0x001dea20
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001dea30;
                                            }
                                        L_001dea30:
                                            charge(ctx, 3);
                                            a0 = 42;
                                            if (v0 == a0) {
                                                // 0x001dea3c
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001dea4c;
                                            }
                                        L_001dea4c:
                                            charge(ctx, 3);
                                            a0 = 43;
                                            if (v0 == a0) {
                                                // 0x001dea58
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001dea68;
                                            }
                                        L_001dea68:
                                            charge(ctx, 3);
                                            a0 = 44;
                                            if (v0 == a0) {
                                                // 0x001dea74
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001dea84;
                                            }
                                        L_001dea84:
                                            charge(ctx, 3);
                                            a0 = 45;
                                            if (v0 == a0) {
                                                // 0x001dea90
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001deaa0;
                                            }
                                        L_001deaa0:
                                            charge(ctx, 3);
                                            a0 = 46;
                                            if (v0 == a0) {
                                                // 0x001deaac
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001deabc;
                                            }
                                        L_001deabc:
                                            charge(ctx, 3);
                                            a0 = 47;
                                            if (v0 == a0) {
                                                // 0x001deac8
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001dead8;
                                            }
                                        L_001dead8:
                                            charge(ctx, 3);
                                            a0 = 39;
                                            if (v0 == a0) {
                                                // 0x001deae4
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 1;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001deaf4;
                                            }
                                        L_001deaf4:
                                            charge(ctx, 3);
                                            a0 = 39;
                                            if (v0 == a0) {
                                                // 0x001deb00
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 2;
                                                if (a1 == a0) {
                                                    goto L_001deb2c;
                                                }
                                                goto L_001deb10;
                                            }
                                        L_001deb10:
                                            charge(ctx, 3);
                                            a0 = 39;
                                            if (v0 == a0) {
                                                // 0x001deb1c
                                                charge(ctx, 4);
                                                lw(v1, v1, 4);
                                                v0 = 3;
                                                if (v1 != v0) {
                                                    goto L_001deb38;
                                                }
                                                goto L_001deb2c;
                                            }
                                        L_001deb38:
                                            charge(ctx, 6);
                                            s0 = 3;
                                            a0 = 3125;
                                            jal(ctx, 0x1DEB40u, gen::fn_datGetFlag_0016f190);
                                            if (v0 != 0) {
                                                // 0x001deb50
                                                charge(ctx, 3);
                                                s0 = addiu(s0, -1);
                                            }
                                            // 0x001ded24 (the shared epilogue, written out on this path)
                                            charge(ctx, 6);
                                            v0 = s0;
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_001deb2c:
                                        charge(ctx, 3);
                                        s0 = 3;
                                    } else {
                                        // 0x001de840
                                        charge(ctx, 6);
                                        s0 = 3;
                                        a0 = 3125;
                                        jal(ctx, 0x1DE848u, gen::fn_datGetFlag_0016f190);
                                        if (v0 != 0) {
                                            // 0x001de858
                                            charge(ctx, 3);
                                            s0 = addiu(s0, -1);
                                        }
                                    }
                                } else {
                                    // 0x001de708
                                    charge(ctx, 6);
                                    s0 = 3;
                                    a0 = 3125;
                                    jal(ctx, 0x1DE710u, gen::fn_datGetFlag_0016f190);
                                    if (v0 != 0) {
                                        // 0x001de720
                                        charge(ctx, 3);
                                        s0 = addiu(s0, -1);
                                    }
                                }
                            } else {
                                // 0x001de694
                                charge(ctx, 2);
                                // 0x001ded20
                                charge(ctx, 1);
                                s0 = 3;
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x001ded24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DED40 sub_1DED40 [K_FldPc_GetRunMode] -- 1808 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1DED40(member) -> the run animation set (1..5), the same rules as sub_1DE630 with the town values 5 / 4 for the
// hero and 2 for member 2 in majors 6 / 7 and member 5 with flag 3119.
void sub_1DED40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ded40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    a3 = 6;
    if (a0 == a3) {
        // 0x001df404
        charge(ctx, 5);
        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        lw(v1, a0, f4::scene::kMajor);
        v0 = 14;
        if (v1 == v0) {
            // 0x001df418
            charge(ctx, 4);
            lw(v1, a0, 4);
            v0 = 5;
            if (v1 == v0) {
                // 0x001df428
                charge(ctx, 3);
                s0 = 1;
            }
        }
    } else {
        // 0x001ded5c
        charge(ctx, 3);
        v0 = 13;
        if (a0 == v0) {
            // 0x001df3c8
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            v0 = 14;
            if (v1 == v0) {
                // 0x001df3dc
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 5;
                if (v1 != v0) {
                    goto L_001df3f8;
                }
                // 0x001df3ec
                charge(ctx, 3);
                s0 = 1;
                // 0x001df438 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                v0 = s0;
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_001df3f8:
            charge(ctx, 3);
            s0 = 3;
        } else {
            // 0x001ded68
            charge(ctx, 3);
            v0 = 10;
            if (a0 == v0) {
                // 0x001df38c
                charge(ctx, 5);
                lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                lw(v1, a0, f4::scene::kMajor);
                v0 = 14;
                if (v1 == v0) {
                    // 0x001df3a0
                    charge(ctx, 4);
                    lw(v1, a0, 4);
                    v0 = 5;
                    if (v1 != v0) {
                        goto L_001df3bc;
                    }
                    // 0x001df3b0
                    charge(ctx, 3);
                    s0 = 1;
                    // 0x001df438 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    v0 = s0;
                    ld(ra, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x20);
                    return;
                }
            L_001df3bc:
                charge(ctx, 3);
                s0 = 3;
            } else {
                // 0x001ded74
                charge(ctx, 3);
                a2 = 7;
                if (a0 == a2) {
                    // 0x001df338
                    charge(ctx, 5);
                    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    lw(a0, v1, f4::scene::kMajor);
                    v0 = 14;
                    if (a0 == v0) {
                        // 0x001df34c
                        charge(ctx, 4);
                        lw(v1, v1, 4);
                        v0 = 5;
                        if (v1 != v0) {
                            goto L_001df368;
                        }
                        // 0x001df35c
                        charge(ctx, 3);
                        s0 = 1;
                        // 0x001df438 (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        v0 = s0;
                        ld(ra, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_001df368:
                    charge(ctx, 3);
                    v0 = 33;
                    if (a0 != v0) {
                        // 0x001df380
                        charge(ctx, 3);
                        s0 = 3;
                    } else {
                        // 0x001df374
                        charge(ctx, 3);
                        s0 = 1;
                    }
                } else {
                    // 0x001ded80
                    charge(ctx, 3);
                    a1 = 5;
                    if (a0 == a1) {
                        // 0x001df2c0
                        charge(ctx, 5);
                        lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(v1, a0, f4::scene::kMajor);
                        v0 = 14;
                        if (v1 == v0) {
                            // 0x001df2d4
                            charge(ctx, 3);
                            lw(v0, a0, 4);
                            if (v0 != a1) {
                                goto L_001df2ec;
                            }
                            // 0x001df2e0
                            charge(ctx, 3);
                            s0 = 1;
                            // 0x001df438 (the shared epilogue, written out on this path)
                            charge(ctx, 6);
                            v0 = s0;
                            ld(ra, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_001df2ec:
                        charge(ctx, 6);
                        a0 = 3119;
                        jal(ctx, 0x1DF2F0u, gen::fn_datGetFlag_0016f190);
                        s0 = 1;
                        if (v0 != s0) {
                            // 0x001df310
                            charge(ctx, 5);
                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            lw(v1, v0, f4::scene::kMajor);
                            v0 = 33;
                            if (v1 != v0) {
                                // 0x001df32c
                                charge(ctx, 3);
                                s0 = 3;
                            } else {
                                // 0x001df324
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x001df304
                            charge(ctx, 3);
                            s0 = 2;
                        }
                    } else {
                        // 0x001ded8c
                        charge(ctx, 3);
                        v0 = 2;
                        if (a0 == v0) {
                            // 0x001df26c
                            charge(ctx, 4);
                            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            lw(v1, a0, f4::scene::kMajor);
                            if (v1 != a3) {
                                // 0x001df27c
                                charge(ctx, 2);
                                if (v1 == a2) {
                                    goto L_001df284;
                                }
                                // 0x001df290
                                charge(ctx, 3);
                                v0 = 14;
                                if (v1 == v0) {
                                    // 0x001df29c
                                    charge(ctx, 3);
                                    lw(v0, a0, 4);
                                    if (v0 != a1) {
                                        goto L_001df2b4;
                                    }
                                    // 0x001df2a8
                                    charge(ctx, 3);
                                    s0 = 1;
                                    // 0x001df438 (the shared epilogue, written out on this path)
                                    charge(ctx, 6);
                                    v0 = s0;
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_001df2b4:
                                charge(ctx, 3);
                                s0 = 3;
                                // 0x001df438 (the shared epilogue, written out on this path)
                                charge(ctx, 6);
                                v0 = s0;
                                ld(ra, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x20);
                                return;
                            }
                        L_001df284:
                            charge(ctx, 3);
                            s0 = 2;
                        } else {
                            // 0x001ded98
                            charge(ctx, 3);
                            v0 = 1;
                            if (a0 == v0) {
                                // 0x001dedac
                                charge(ctx, 5);
                                jal(ctx, 0x1DEDACu, gen::fn_sub_17D800_0017d800);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x001dedc0
                                    charge(ctx, 5);
                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, v0, f4::scene::kMajor);
                                    v0 = 4;
                                    if (v1 != v0) {
                                        // 0x001dedd4
                                        charge(ctx, 3);
                                        v0 = 5;
                                        if (v1 != v0) {
                                            goto L_001dee04;
                                        }
                                        goto L_001dede0;
                                    }
                                L_001dede0:
                                    charge(ctx, 6);
                                    s0 = 5;
                                    a0 = 3125;
                                    jal(ctx, 0x1DEDE8u, gen::fn_datGetFlag_0016f190);
                                    if (v0 != 0) {
                                        // 0x001dedf8
                                        charge(ctx, 3);
                                        s0 = addiu(s0, -1);
                                    }
                                    // 0x001df438 (the shared epilogue, written out on this path)
                                    charge(ctx, 6);
                                    v0 = s0;
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_001dee04:
                                charge(ctx, 5);
                                jal(ctx, 0x1DEE04u, gen::fn_sub_1A0310_001a0310);
                                v1 = 1;
                                if (v0 != v1) {
                                    // 0x001dee3c
                                    charge(ctx, 5);
                                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, a0, f4::scene::kMajor);
                                    v0 = 7;
                                    if (v1 == v0) {
                                        // 0x001dee50
                                        charge(ctx, 4);
                                        lw(v1, a0, 4);
                                        v0 = 6;
                                        if (v1 != v0) {
                                            goto L_001dee78;
                                        }
                                        // 0x001dee60
                                        charge(ctx, 6);
                                        jal(ctx, 0x1DEE60u, gen::fn_datGetTime_0016ef30);
                                        v1 = v0 & 0xFF;
                                        v0 = 8;
                                        if (v1 != v0) {
                                            goto L_001dee78;
                                        }
                                    L_001deef0:
                                        charge(ctx, 6);
                                        s0 = 5;
                                        a0 = 3125;
                                        jal(ctx, 0x1DEEF8u, gen::fn_datGetFlag_0016f190);
                                        if (v0 != 0) {
                                            // 0x001def08
                                            charge(ctx, 3);
                                            s0 = addiu(s0, -1);
                                        }
                                        // 0x001df438 (the shared epilogue, written out on this path)
                                        charge(ctx, 6);
                                        v0 = s0;
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001dee78:
                                    charge(ctx, 5);
                                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, a0, f4::scene::kMajor);
                                    v0 = 8;
                                    if (v1 == v0) {
                                        // 0x001dee8c
                                        charge(ctx, 4);
                                        lw(v1, a0, 4);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            goto L_001deeb4;
                                        }
                                        // 0x001dee9c
                                        charge(ctx, 6);
                                        jal(ctx, 0x1DEE9Cu, gen::fn_datGetTime_0016ef30);
                                        v1 = v0 & 0xFF;
                                        v0 = 8;
                                        if (v1 == v0) {
                                            goto L_001deef0;
                                        }
                                        goto L_001deeb4;
                                    }
                                L_001deeb4:
                                    charge(ctx, 5);
                                    lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, a0, f4::scene::kMajor);
                                    v0 = 9;
                                    if (v1 == v0) {
                                        // 0x001deec8
                                        charge(ctx, 4);
                                        lw(v1, a0, 4);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            goto L_001def14;
                                        }
                                        // 0x001deed8
                                        charge(ctx, 6);
                                        jal(ctx, 0x1DEED8u, gen::fn_datGetTime_0016ef30);
                                        v1 = v0 & 0xFF;
                                        v0 = 8;
                                        if (v1 != v0) {
                                            goto L_001def14;
                                        }
                                        goto L_001deef0;
                                    }
                                L_001def14:
                                    charge(ctx, 5);
                                    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(a0, v1, f4::scene::kMajor);
                                    v0 = 14;
                                    if (a0 == v0) {
                                        // 0x001def28
                                        charge(ctx, 4);
                                        lw(v1, v1, 4);
                                        v0 = 5;
                                        if (v1 != v0) {
                                            goto L_001def44;
                                        }
                                        // 0x001def38
                                        charge(ctx, 3);
                                        s0 = 1;
                                        // 0x001df438 (the shared epilogue, written out on this path)
                                        charge(ctx, 6);
                                        v0 = s0;
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_001def44:
                                    charge(ctx, 3);
                                    v0 = 33;
                                    if (a0 != v0) {
                                        // 0x001def74
                                        charge(ctx, 3);
                                        v0 = 7;
                                        if (a0 == v0) {
                                            // 0x001def80
                                            charge(ctx, 6);
                                            a0 = 3584;
                                            jal(ctx, 0x1DEF84u, gen::fn_datGetFlag_0016f190);
                                            s0 = 1;
                                            if (v0 != s0) {
                                                goto L_001defa0;
                                            }
                                            // 0x001def98
                                            charge(ctx, 2);
                                            // 0x001df438 (the shared epilogue, written out on this path)
                                            charge(ctx, 6);
                                            v0 = s0;
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_001defa0:
                                        charge(ctx, 5);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v1, v0, f4::scene::kMajor);
                                        v0 = 6;
                                        if (v1 == v0) {
                                            // 0x001defb4
                                            charge(ctx, 6);
                                            a0 = 3680;
                                            jal(ctx, 0x1DEFB8u, gen::fn_datGetFlag_0016f190);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                goto L_001deff0;
                                            }
                                            // 0x001defcc
                                            charge(ctx, 6);
                                            s0 = 5;
                                            a0 = 3125;
                                            jal(ctx, 0x1DEFD4u, gen::fn_datGetFlag_0016f190);
                                            if (v0 != 0) {
                                                // 0x001defe4
                                                charge(ctx, 3);
                                                s0 = addiu(s0, -1);
                                            }
                                            // 0x001df438 (the shared epilogue, written out on this path)
                                            charge(ctx, 6);
                                            v0 = s0;
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_001deff0:
                                        charge(ctx, 5);
                                        jal(ctx, 0x1DEFF0u, gen::fn_sub_1A01C0_001a01c0);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x001df004
                                            charge(ctx, 5);
                                            lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                            lw(v0, v1, f4::scene::kMajor);
                                            a0 = 21;
                                            if (v0 == a0) {
                                                // 0x001df018
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df028;
                                            }
                                        L_001df028:
                                            charge(ctx, 3);
                                            a0 = 22;
                                            if (v0 == a0) {
                                                // 0x001df034
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df044;
                                            }
                                        L_001df044:
                                            charge(ctx, 3);
                                            a0 = 22;
                                            if (v0 == a0) {
                                                // 0x001df050
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 51;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df060;
                                            }
                                        L_001df060:
                                            charge(ctx, 3);
                                            a0 = 23;
                                            if (v0 == a0) {
                                                // 0x001df06c
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df07c;
                                            }
                                        L_001df07c:
                                            charge(ctx, 3);
                                            a0 = 23;
                                            if (v0 == a0) {
                                                // 0x001df088
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 51;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df098;
                                            }
                                        L_001df098:
                                            charge(ctx, 3);
                                            a0 = 24;
                                            if (v0 == a0) {
                                                // 0x001df0a4
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df0b4;
                                            }
                                        L_001df0b4:
                                            charge(ctx, 3);
                                            a0 = 24;
                                            if (v0 == a0) {
                                                // 0x001df0c0
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 51;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df0d0;
                                            }
                                        L_001df0d0:
                                            charge(ctx, 3);
                                            a0 = 25;
                                            if (v0 == a0) {
                                                // 0x001df0dc
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df0ec;
                                            }
                                        L_001df0ec:
                                            charge(ctx, 3);
                                            a0 = 26;
                                            if (v0 == a0) {
                                                // 0x001df0f8
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df108;
                                            }
                                        L_001df108:
                                            charge(ctx, 3);
                                            a0 = 27;
                                            if (v0 == a0) {
                                                // 0x001df114
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df124;
                                            }
                                        L_001df124:
                                            charge(ctx, 3);
                                            a0 = 41;
                                            if (v0 == a0) {
                                                // 0x001df130
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df140;
                                            }
                                        L_001df140:
                                            charge(ctx, 3);
                                            a0 = 42;
                                            if (v0 == a0) {
                                                // 0x001df14c
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df15c;
                                            }
                                        L_001df15c:
                                            charge(ctx, 3);
                                            a0 = 43;
                                            if (v0 == a0) {
                                                // 0x001df168
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df178;
                                            }
                                        L_001df178:
                                            charge(ctx, 3);
                                            a0 = 44;
                                            if (v0 == a0) {
                                                // 0x001df184
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df194;
                                            }
                                        L_001df194:
                                            charge(ctx, 3);
                                            a0 = 45;
                                            if (v0 == a0) {
                                                // 0x001df1a0
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df1b0;
                                            }
                                        L_001df1b0:
                                            charge(ctx, 3);
                                            a0 = 46;
                                            if (v0 == a0) {
                                                // 0x001df1bc
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df1cc;
                                            }
                                        L_001df1cc:
                                            charge(ctx, 3);
                                            a0 = 47;
                                            if (v0 == a0) {
                                                // 0x001df1d8
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 50;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df1e8;
                                            }
                                        L_001df1e8:
                                            charge(ctx, 3);
                                            a0 = 39;
                                            if (v0 == a0) {
                                                // 0x001df1f4
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 1;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df204;
                                            }
                                        L_001df204:
                                            charge(ctx, 3);
                                            a0 = 39;
                                            if (v0 == a0) {
                                                // 0x001df210
                                                charge(ctx, 4);
                                                lw(a1, v1, 4);
                                                a0 = 2;
                                                if (a1 == a0) {
                                                    goto L_001df23c;
                                                }
                                                goto L_001df220;
                                            }
                                        L_001df220:
                                            charge(ctx, 3);
                                            a0 = 39;
                                            if (v0 == a0) {
                                                // 0x001df22c
                                                charge(ctx, 4);
                                                lw(v1, v1, 4);
                                                v0 = 3;
                                                if (v1 != v0) {
                                                    goto L_001df248;
                                                }
                                                goto L_001df23c;
                                            }
                                        L_001df248:
                                            charge(ctx, 6);
                                            s0 = 5;
                                            a0 = 3125;
                                            jal(ctx, 0x1DF250u, gen::fn_datGetFlag_0016f190);
                                            if (v0 != 0) {
                                                // 0x001df260
                                                charge(ctx, 3);
                                                s0 = addiu(s0, -1);
                                            }
                                            // 0x001df438 (the shared epilogue, written out on this path)
                                            charge(ctx, 6);
                                            v0 = s0;
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_001df23c:
                                        charge(ctx, 3);
                                        s0 = 3;
                                    } else {
                                        // 0x001def50
                                        charge(ctx, 6);
                                        s0 = 3;
                                        a0 = 3125;
                                        jal(ctx, 0x1DEF58u, gen::fn_datGetFlag_0016f190);
                                        if (v0 != 0) {
                                            // 0x001def68
                                            charge(ctx, 3);
                                            s0 = addiu(s0, -1);
                                        }
                                    }
                                } else {
                                    // 0x001dee18
                                    charge(ctx, 6);
                                    s0 = 5;
                                    a0 = 3125;
                                    jal(ctx, 0x1DEE20u, gen::fn_datGetFlag_0016f190);
                                    if (v0 != 0) {
                                        // 0x001dee30
                                        charge(ctx, 3);
                                        s0 = addiu(s0, -1);
                                    }
                                }
                            } else {
                                // 0x001deda4
                                charge(ctx, 2);
                                // 0x001df434
                                charge(ctx, 1);
                                s0 = 3;
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x001df438 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001DF450 sub_1DF450 [K_FldPc_PickIdleAnim] -- 1564 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1DF450(member) -> the idle animation: sub_1DDE00(member) for members other than the hero; for the hero in the
// town scenes (and field 14 at time 6 on 11/18, 11/19) a random one of 6..8 (RpRandom % 3 + 6), in Tartarus-type
// scenes 15.
void sub_1DF450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001df450
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x1DF464u, gen::fn_sub_1DDE00_001dde00);
    s0 = v0;
    v0 = 1;
    if (s1 == v0) {
        // 0x001df484
        charge(ctx, 5);
        jal(ctx, 0x1DF484u, gen::fn_sub_17D800_0017d800);
        v1 = 1;
        if (v0 == v1) {
            // 0x001df498
            charge(ctx, 5);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = 4;
            if (v1 != v0) {
                // 0x001df4ac
                charge(ctx, 3);
                v0 = 5;
                if (v1 != v0) {
                    goto L_001df4d8;
                }
                goto L_001df4b8;
            }
        L_001df4b8:
            charge(ctx, 8);
            jal(ctx, 0x1DF4B8u, gen::fn_sub_488F30_00488f30);
            v1 = 3;
            divu(v0, v1);
            mfhi(v0);
            s0 = addiu(v0, 6);
            // 0x001dfa50 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            v0 = s0;
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_001df4d8:
        charge(ctx, 5);
        jal(ctx, 0x1DF4D8u, gen::fn_sub_1A0310_001a0310);
        v1 = 1;
        if (v0 != v1) {
            // 0x001df50c
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            v0 = 7;
            if (v1 == v0) {
                // 0x001df520
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 6;
                if (v1 != v0) {
                    goto L_001df548;
                }
                // 0x001df530
                charge(ctx, 6);
                jal(ctx, 0x1DF530u, gen::fn_datGetTime_0016ef30);
                v1 = v0 & 0xFF;
                v0 = 8;
                if (v1 != v0) {
                    goto L_001df548;
                }
            L_001df5c0:
                charge(ctx, 8);
                jal(ctx, 0x1DF5C0u, gen::fn_sub_488F30_00488f30);
                v1 = 3;
                divu(v0, v1);
                mfhi(v0);
                s0 = addiu(v0, 6);
                // 0x001dfa50 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                v0 = s0;
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_001df548:
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            v0 = 8;
            if (v1 == v0) {
                // 0x001df55c
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 1;
                if (v1 != v0) {
                    goto L_001df584;
                }
                // 0x001df56c
                charge(ctx, 6);
                jal(ctx, 0x1DF56Cu, gen::fn_datGetTime_0016ef30);
                v1 = v0 & 0xFF;
                v0 = 8;
                if (v1 == v0) {
                    goto L_001df5c0;
                }
                goto L_001df584;
            }
        L_001df584:
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            v0 = 9;
            if (v1 == v0) {
                // 0x001df598
                charge(ctx, 4);
                lw(v1, a0, 4);
                v0 = 1;
                if (v1 != v0) {
                    goto L_001df5e0;
                }
                // 0x001df5a8
                charge(ctx, 6);
                jal(ctx, 0x1DF5A8u, gen::fn_datGetTime_0016ef30);
                v1 = v0 & 0xFF;
                v0 = 8;
                if (v1 != v0) {
                    goto L_001df5e0;
                }
                goto L_001df5c0;
            }
        L_001df5e0:
            charge(ctx, 5);
            lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(a0, v1, f4::scene::kMajor);
            v0 = 14;
            if (a0 == v0) {
                // 0x001df5f4
                charge(ctx, 4);
                lw(v1, v1, 4);
                v0 = 5;
                if (v1 != v0) {
                    goto L_001df604;
                }
                // 0x001dfa50 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                v0 = s0;
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_001df604:
            charge(ctx, 3);
            v0 = 14;
            if (a0 == v0) {
                // 0x001df610
                charge(ctx, 6);
                jal(ctx, 0x1DF610u, gen::fn_datGetTime_0016ef30);
                v1 = v0 & 0xFF;
                v0 = 6;
                if (v1 != v0) {
                    goto L_001df698;
                }
                // 0x001df628
                charge(ctx, 5);
                jal(ctx, 0x1DF628u, gen::fn_clndGetCurrentMonth_0017d920);
                v1 = 11;
                if (v0 == v1) {
                    // 0x001df63c
                    charge(ctx, 5);
                    jal(ctx, 0x1DF63Cu, gen::fn_clndGetCurrentDay_0017da40);
                    v1 = 18;
                    if (v0 != v1) {
                        goto L_001df650;
                    }
                L_001df678:
                    charge(ctx, 8);
                    jal(ctx, 0x1DF678u, gen::fn_sub_488F30_00488f30);
                    v1 = 3;
                    divu(v0, v1);
                    mfhi(v0);
                    s0 = addiu(v0, 6);
                    // 0x001dfa50 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    v0 = s0;
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            L_001df650:
                charge(ctx, 5);
                jal(ctx, 0x1DF650u, gen::fn_clndGetCurrentMonth_0017d920);
                v1 = 11;
                if (v0 != v1) {
                    goto L_001df698;
                }
                // 0x001df664
                charge(ctx, 5);
                jal(ctx, 0x1DF664u, gen::fn_clndGetCurrentDay_0017da40);
                v1 = 19;
                if (v0 != v1) {
                    goto L_001df698;
                }
                goto L_001df678;
            }
        L_001df698:
            charge(ctx, 5);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = 33;
            if (v1 != v0) {
                // 0x001df6ac
                charge(ctx, 3);
                v0 = 7;
                if (v1 == v0) {
                    // 0x001df6b8
                    charge(ctx, 6);
                    a0 = 3584;
                    jal(ctx, 0x1DF6BCu, gen::fn_datGetFlag_0016f190);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_001df6d0;
                    }
                    // 0x001dfa50 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    v0 = s0;
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            L_001df6d0:
                charge(ctx, 5);
                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                lw(v1, v0, f4::scene::kMajor);
                v0 = 6;
                if (v1 == v0) {
                    // 0x001df6e4
                    charge(ctx, 6);
                    a0 = 3680;
                    jal(ctx, 0x1DF6E8u, gen::fn_datGetFlag_0016f190);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_001df71c;
                    }
                    // 0x001df6fc
                    charge(ctx, 8);
                    jal(ctx, 0x1DF6FCu, gen::fn_sub_488F30_00488f30);
                    v1 = 3;
                    divu(v0, v1);
                    mfhi(v0);
                    s0 = addiu(v0, 6);
                    // 0x001dfa50 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    v0 = s0;
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            L_001df71c:
                charge(ctx, 5);
                jal(ctx, 0x1DF71Cu, gen::fn_sub_1A01C0_001a01c0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001df730
                    charge(ctx, 5);
                    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    lw(v0, v1, f4::scene::kMajor);
                    a0 = 21;
                    if (v0 == a0) {
                        // 0x001df744
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df754;
                    }
                L_001df754:
                    charge(ctx, 3);
                    a0 = 22;
                    if (v0 == a0) {
                        // 0x001df760
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df770;
                    }
                L_001df770:
                    charge(ctx, 3);
                    a0 = 22;
                    if (v0 == a0) {
                        // 0x001df77c
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 51;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df78c;
                    }
                L_001df78c:
                    charge(ctx, 3);
                    a0 = 23;
                    if (v0 == a0) {
                        // 0x001df798
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df7a8;
                    }
                L_001df7a8:
                    charge(ctx, 3);
                    a0 = 23;
                    if (v0 == a0) {
                        // 0x001df7b4
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 51;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df7c4;
                    }
                L_001df7c4:
                    charge(ctx, 3);
                    a0 = 24;
                    if (v0 == a0) {
                        // 0x001df7d0
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df7e0;
                    }
                L_001df7e0:
                    charge(ctx, 3);
                    a0 = 24;
                    if (v0 == a0) {
                        // 0x001df7ec
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 51;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df7fc;
                    }
                L_001df7fc:
                    charge(ctx, 3);
                    a0 = 25;
                    if (v0 == a0) {
                        // 0x001df808
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df818;
                    }
                L_001df818:
                    charge(ctx, 3);
                    a0 = 26;
                    if (v0 == a0) {
                        // 0x001df824
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df834;
                    }
                L_001df834:
                    charge(ctx, 3);
                    a0 = 27;
                    if (v0 == a0) {
                        // 0x001df840
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df850;
                    }
                L_001df850:
                    charge(ctx, 3);
                    a0 = 41;
                    if (v0 == a0) {
                        // 0x001df85c
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df86c;
                    }
                L_001df86c:
                    charge(ctx, 3);
                    a0 = 42;
                    if (v0 == a0) {
                        // 0x001df878
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df888;
                    }
                L_001df888:
                    charge(ctx, 3);
                    a0 = 43;
                    if (v0 == a0) {
                        // 0x001df894
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df8a4;
                    }
                L_001df8a4:
                    charge(ctx, 3);
                    a0 = 44;
                    if (v0 == a0) {
                        // 0x001df8b0
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df8c0;
                    }
                L_001df8c0:
                    charge(ctx, 3);
                    a0 = 45;
                    if (v0 == a0) {
                        // 0x001df8cc
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df8dc;
                    }
                L_001df8dc:
                    charge(ctx, 3);
                    a0 = 46;
                    if (v0 == a0) {
                        // 0x001df8e8
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df8f8;
                    }
                L_001df8f8:
                    charge(ctx, 3);
                    a0 = 47;
                    if (v0 == a0) {
                        // 0x001df904
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df914;
                    }
                L_001df914:
                    charge(ctx, 3);
                    a0 = 41;
                    if (v0 == a0) {
                        // 0x001df920
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df930;
                    }
                L_001df930:
                    charge(ctx, 3);
                    a0 = 42;
                    if (v0 == a0) {
                        // 0x001df93c
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df94c;
                    }
                L_001df94c:
                    charge(ctx, 3);
                    a0 = 43;
                    if (v0 == a0) {
                        // 0x001df958
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df968;
                    }
                L_001df968:
                    charge(ctx, 3);
                    a0 = 44;
                    if (v0 == a0) {
                        // 0x001df974
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df984;
                    }
                L_001df984:
                    charge(ctx, 3);
                    a0 = 45;
                    if (v0 == a0) {
                        // 0x001df990
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df9a0;
                    }
                L_001df9a0:
                    charge(ctx, 3);
                    a0 = 46;
                    if (v0 == a0) {
                        // 0x001df9ac
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df9bc;
                    }
                L_001df9bc:
                    charge(ctx, 3);
                    a0 = 47;
                    if (v0 == a0) {
                        // 0x001df9c8
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 50;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df9d8;
                    }
                L_001df9d8:
                    charge(ctx, 3);
                    a0 = 39;
                    if (v0 == a0) {
                        // 0x001df9e4
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 1;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001df9f4;
                    }
                L_001df9f4:
                    charge(ctx, 3);
                    a0 = 39;
                    if (v0 == a0) {
                        // 0x001dfa00
                        charge(ctx, 4);
                        lw(a1, v1, 4);
                        a0 = 2;
                        if (a1 == a0) {
                            goto L_001dfa2c;
                        }
                        goto L_001dfa10;
                    }
                L_001dfa10:
                    charge(ctx, 3);
                    a0 = 39;
                    if (v0 == a0) {
                        // 0x001dfa1c
                        charge(ctx, 4);
                        lw(v1, v1, 4);
                        v0 = 3;
                        if (v1 != v0) {
                            goto L_001dfa38;
                        }
                        goto L_001dfa2c;
                    }
                L_001dfa38:
                    charge(ctx, 6);
                    jal(ctx, 0x1DFA38u, gen::fn_sub_488F30_00488f30);
                    v1 = 3;
                    divu(v0, v1);
                    mfhi(v0);
                    s0 = addiu(v0, 6);
                    // 0x001dfa50 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    v0 = s0;
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            L_001dfa2c:
                charge(ctx, 3);
                s0 = 15;
            }
        } else {
            // 0x001df4ec
            charge(ctx, 8);
            jal(ctx, 0x1DF4ECu, gen::fn_sub_488F30_00488f30);
            v1 = 3;
            divu(v0, v1);
            mfhi(v0);
            s0 = addiu(v0, 6);
        }
    } else {
        // 0x001df47c
        charge(ctx, 2);
    }
    // 0x001dfa50 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001DFA70 sub_1DFA70 [K_FreeCamera_Update] -- 2668 bytes; frame 0x100: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_1DFA70(task) -> 0, or -1 to be destroyed: the field editor's FREE CAMERA MODE (work: +80 the camera, +16
// the saved frame): state 0 saves the camera frame matrix; state 1 moves the camera frame with the sticks (yaw about
// world up, pitch about the frame's right axis, dolly along the look axis by 0x7CB110 per frame) and the shoulder
// buttons (up / down 10), the d-pad / buttons reset the pitch; with circle (pad 0x40) it prints the frame matrix and
// its Euler angles ("%f %f %f"); triangle (0x20) -> 2; state 2 -> -1. Debug only (the "field editor").
void sub_1DFA70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x001dfa70
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a0, f4::kTaskWork);
    lw(v0, s0, 80);
    lw(s4, v0, 4);
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 == v0) {
        // 0x001e0494
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001dfabc
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x001dfb1c
            charge(ctx, 6);
            s3 = 0;
            s2 = addiu(sp, 0xD0);
            v1 = addiu(sp, 0xC0);
            v0 = 12;
            if (v1 != 0) {
                for (;;) {
                    // 0x001dfb34
                    charge(ctx, 7);
                    sb(zero, v1, 0);
                    v1 = addiu(v1, 1);
                    v0 = addiu(v0, -1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x001dfb50
            charge(ctx, 5);
            mtc1(zero, f20);
            v0 = 0x7E0000;
            lbu(v0, v0, 2398);  // 0x7E095E
            if (i64(v0) < 0) {
                // 0x001dfb78
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001dfb64
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001dfb94
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f2, f1, f0);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f2, f0);
            if (!cond(ctx)) {
                // 0x001dfbbc
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f2, f0);
                if (!cond(ctx)) {
                    goto L_001dfbd4;
                }
                goto L_001dfbf8;
            }
        L_001dfbd4:
            charge(ctx, 9);
            mtc1(zero, f1);
            sw(zero, s2, 0);
            v0 = 0x3F800000;
            sw(v0, s2, 4);
            sw(zero, s2, 8);
            lwc1(f0, gp, -31848);  // 0x7CB088
            adda_s(f1, f20);
            msub_s(f20, f0, f2);
            s3 = 1;
        L_001dfbf8:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2399);  // 0x7E095F
            if (i64(v0) < 0) {
                // 0x001dfc1c
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001dfc08
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001dfc38
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f2, f1, f0);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f2, f0);
            if (!cond(ctx)) {
                // 0x001dfc60
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f2, f0);
                if (!cond(ctx)) {
                    goto L_001dfc78;
                }
                goto L_001dfc94;
            }
        L_001dfc78:
            charge(ctx, 7);
            s2 = addiu(s4, 16);
            lwc1(f1, gp, -31848);  // 0x7CB088
            mtc1(zero, f0);
            adda_s(f0, f20);
            msub_s(f20, f1, f2);
            s3 = 1;
        L_001dfc94:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2401);  // 0x7E0961
            if (i64(v0) < 0) {
                // 0x001dfcb8
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001dfca4
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001dfcd4
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f21, f1, f0);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f21, f0);
            if (!cond(ctx)) {
                // 0x001dfcfc
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f21, f0);
                if (!cond(ctx)) {
                    goto L_001dfd14;
                }
                goto L_001dfd6c;
            }
        L_001dfd14:
            charge(ctx, 22);
            a0 = addiu(sp, 0xC0);
            lwc1(f2, s4, 48);
            lwc1(f1, s4, 52);
            lwc1(f0, s4, 56);
            swc1(f2, sp, 0xC0);
            swc1(f1, sp, 0xC4);
            swc1(f0, sp, 0xC8);
            a1 = a0;
            jal(ctx, 0x1DFD34u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f0, gp, -31712);  // 0x7CB110
            mul_s(f1, f0, f21);
            lwc1(f0, sp, 0xC0);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0xC0);
            lwc1(f0, sp, 0xC4);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0xC4);
            lwc1(f0, sp, 0xC8);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0xC8);
            s3 = 1;
        L_001dfd6c:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2400);  // 0x7E0960
            if (i64(v0) < 0) {
                // 0x001dfd90
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001dfd7c
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001dfdac
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f21, f1, f0);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f21, f0);
            if (!cond(ctx)) {
                // 0x001dfdd4
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f21, f0);
                if (!cond(ctx)) {
                    goto L_001dfdec;
                }
                // 0x001dfe4c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, 2380);  // 0x7E094C
                v0 = v1 & 0x6;
                if (v0 == 0) {
                    // 0x001dfe84
                    charge(ctx, 3);
                    v0 = v1 & 0x9;
                    if (v0 == 0) {
                        // 0x001dfeb4
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v1, v0, 2382);  // gPadFlags
                        v0 = v1 & 0x1000;
                        if (v0 == 0) {
                            // 0x001dff64
                            charge(ctx, 3);
                            v0 = v1 & 0x4000;
                            if (v0 == 0) {
                                // 0x001e0010
                                charge(ctx, 3);
                                v0 = v1 & 0x8000;
                                if (v0 == 0) {
                                    // 0x001e00bc
                                    charge(ctx, 3);
                                    v0 = v1 & 0x2000;
                                    if (v0 == 0) {
                                        // 0x001e0168
                                        charge(ctx, 3);
                                        v0 = v1 & 0x20;
                                        if (v0 != 0) {
                                            // 0x001e0174
                                            charge(ctx, 3);
                                            lw(v0, s0, 0);
                                            v0 = addiu(v0, 1);
                                            sw(v0, s0, 0);
                                        }
                                    } else {
                                        // 0x001e00c8
                                        charge(ctx, 40);
                                        sw(zero, s2, 0);
                                        v0 = 0x3F800000;
                                        sw(v0, s2, 4);
                                        sw(zero, s2, 8);
                                        lwc1(f2, s4, 64);
                                        lwc1(f1, s4, 68);
                                        lwc1(f0, s4, 72);
                                        swc1(f2, sp, 0xF0);
                                        swc1(f1, sp, 0xF4);
                                        swc1(f0, sp, 0xF8);
                                        v0 = lui(0xBF80);
                                        mtc1(v0, f1);
                                        lwc1(f0, sp, 0xF0);
                                        mul_s(f0, f1, f0);
                                        swc1(f0, sp, 0xE0);
                                        lwc1(f0, sp, 0xF4);
                                        mul_s(f0, f1, f0);
                                        swc1(f0, sp, 0xE4);
                                        lwc1(f0, sp, 0xF8);
                                        mul_s(f0, f1, f0);
                                        swc1(f0, sp, 0xE8);
                                        a0 = s4;
                                        a1 = addiu(sp, 0xE0);
                                        a2 = 2;
                                        jal(ctx, 0x1E0128u, gen::fn_sub_4CB750_004cb750);
                                        v0 = 0x43870000;
                                        mtc1(v0, f12);
                                        a0 = s4;
                                        a1 = s2;
                                        a2 = 0;
                                        jal(ctx, 0x1E0144u, gen::fn_sub_4CB890_004cb890);
                                        a0 = s4;
                                        a1 = addiu(sp, 0xF0);
                                        a2 = 2;
                                        jal(ctx, 0x1E0158u, gen::fn_sub_4CB750_004cb750);
                                    }
                                } else {
                                    // 0x001e001c
                                    charge(ctx, 40);
                                    sw(zero, s2, 0);
                                    v0 = 0x3F800000;
                                    sw(v0, s2, 4);
                                    sw(zero, s2, 8);
                                    lwc1(f2, s4, 64);
                                    lwc1(f1, s4, 68);
                                    lwc1(f0, s4, 72);
                                    swc1(f2, sp, 0xF0);
                                    swc1(f1, sp, 0xF4);
                                    swc1(f0, sp, 0xF8);
                                    v0 = lui(0xBF80);
                                    mtc1(v0, f1);
                                    lwc1(f0, sp, 0xF0);
                                    mul_s(f0, f1, f0);
                                    swc1(f0, sp, 0xE0);
                                    lwc1(f0, sp, 0xF4);
                                    mul_s(f0, f1, f0);
                                    swc1(f0, sp, 0xE4);
                                    lwc1(f0, sp, 0xF8);
                                    mul_s(f0, f1, f0);
                                    swc1(f0, sp, 0xE8);
                                    a0 = s4;
                                    a1 = addiu(sp, 0xE0);
                                    a2 = 2;
                                    jal(ctx, 0x1E007Cu, gen::fn_sub_4CB750_004cb750);
                                    v0 = 0x42B40000;
                                    mtc1(v0, f12);
                                    a0 = s4;
                                    a1 = s2;
                                    a2 = 0;
                                    jal(ctx, 0x1E0098u, gen::fn_sub_4CB890_004cb890);
                                    a0 = s4;
                                    a1 = addiu(sp, 0xF0);
                                    a2 = 2;
                                    jal(ctx, 0x1E00ACu, gen::fn_sub_4CB750_004cb750);
                                }
                            } else {
                                // 0x001dff70
                                charge(ctx, 40);
                                sw(zero, s2, 0);
                                v0 = 0x3F800000;
                                sw(v0, s2, 4);
                                sw(zero, s2, 8);
                                lwc1(f2, s4, 64);
                                lwc1(f1, s4, 68);
                                lwc1(f0, s4, 72);
                                swc1(f2, sp, 0xF0);
                                swc1(f1, sp, 0xF4);
                                swc1(f0, sp, 0xF8);
                                v0 = lui(0xBF80);
                                mtc1(v0, f1);
                                lwc1(f0, sp, 0xF0);
                                mul_s(f0, f1, f0);
                                swc1(f0, sp, 0xE0);
                                lwc1(f0, sp, 0xF4);
                                mul_s(f0, f1, f0);
                                swc1(f0, sp, 0xE4);
                                lwc1(f0, sp, 0xF8);
                                mul_s(f0, f1, f0);
                                swc1(f0, sp, 0xE8);
                                a0 = s4;
                                a1 = addiu(sp, 0xE0);
                                a2 = 2;
                                jal(ctx, 0x1DFFD0u, gen::fn_sub_4CB750_004cb750);
                                v0 = 0x43340000;
                                mtc1(v0, f12);
                                a0 = s4;
                                a1 = s2;
                                a2 = 0;
                                jal(ctx, 0x1DFFECu, gen::fn_sub_4CB890_004cb890);
                                a0 = s4;
                                a1 = addiu(sp, 0xF0);
                                a2 = 2;
                                jal(ctx, 0x1E0000u, gen::fn_sub_4CB750_004cb750);
                            }
                        } else {
                            // 0x001dfec8
                            charge(ctx, 39);
                            sw(zero, s2, 0);
                            v0 = 0x3F800000;
                            sw(v0, s2, 4);
                            sw(zero, s2, 8);
                            lwc1(f2, s4, 64);
                            lwc1(f1, s4, 68);
                            lwc1(f0, s4, 72);
                            swc1(f2, sp, 0xF0);
                            swc1(f1, sp, 0xF4);
                            swc1(f0, sp, 0xF8);
                            v0 = lui(0xBF80);
                            mtc1(v0, f1);
                            lwc1(f0, sp, 0xF0);
                            mul_s(f0, f1, f0);
                            swc1(f0, sp, 0xE0);
                            lwc1(f0, sp, 0xF4);
                            mul_s(f0, f1, f0);
                            swc1(f0, sp, 0xE4);
                            lwc1(f0, sp, 0xF8);
                            mul_s(f0, f1, f0);
                            swc1(f0, sp, 0xE8);
                            a0 = s4;
                            a1 = addiu(sp, 0xE0);
                            a2 = 2;
                            jal(ctx, 0x1DFF28u, gen::fn_sub_4CB750_004cb750);
                            mtc1(zero, f12);
                            a0 = s4;
                            a1 = s2;
                            a2 = 0;
                            jal(ctx, 0x1DFF40u, gen::fn_sub_4CB890_004cb890);
                            a0 = s4;
                            a1 = addiu(sp, 0xF0);
                            a2 = 2;
                            jal(ctx, 0x1DFF54u, gen::fn_sub_4CB750_004cb750);
                        }
                    } else {
                        // 0x001dfe90
                        charge(ctx, 9);
                        lwc1(f1, sp, 0xC4);
                        v0 = 0x41200000;
                        mtc1(v0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, sp, 0xC4);
                        s3 = 1;
                    }
                } else {
                    // 0x001dfe60
                    charge(ctx, 9);
                    lwc1(f1, sp, 0xC4);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xC4);
                    s3 = 1;
                }
                goto L_001e0180;
            }
        L_001dfdec:
            charge(ctx, 24);
            a0 = addiu(sp, 0xC0);
            lwc1(f2, s4, 16);
            lwc1(f1, s4, 20);
            lwc1(f0, s4, 24);
            swc1(f2, sp, 0xC0);
            swc1(f1, sp, 0xC4);
            swc1(f0, sp, 0xC8);
            a1 = a0;
            jal(ctx, 0x1DFE0Cu, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f0, gp, -31712);  // 0x7CB110
            mul_s(f1, f0, f21);
            lwc1(f0, sp, 0xC0);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0xC0);
            lwc1(f0, sp, 0xC4);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0xC4);
            lwc1(f0, sp, 0xC8);
            mul_s(f0, f0, f1);
            swc1(f0, sp, 0xC8);
            s3 = 1;
        L_001e0180:
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 != 0) {
                // 0x001e0194
                charge(ctx, 81);
                jal(ctx, 0x1E0194u, gen::fn_sub_198590_00198590);
                lw(s1, v0, 4);
                lwc1(f12, s1, 16);
                jal(ctx, 0x1E01A4u, gen::fn_fptodp_00530da0);
                s0 = v0;
                lwc1(f12, s1, 20);
                jal(ctx, 0x1E01B4u, gen::fn_fptodp_00530da0);
                s5 = v0;
                lwc1(f12, s1, 24);
                jal(ctx, 0x1E01C4u, gen::fn_fptodp_00530da0);
                a0 = 0x680000;
                a0 = addiu(a0, 15696);  // "%f %f %f\n"
                a1 = s0;
                a2 = s5;
                a3 = v0;
                jal(ctx, 0x1E01E0u, gen::fn_printf_005225a8);
                lwc1(f12, s1, 32);
                jal(ctx, 0x1E01ECu, gen::fn_fptodp_00530da0);
                s0 = v0;
                lwc1(f12, s1, 36);
                jal(ctx, 0x1E01FCu, gen::fn_fptodp_00530da0);
                s5 = v0;
                lwc1(f12, s1, 40);
                jal(ctx, 0x1E020Cu, gen::fn_fptodp_00530da0);
                a0 = 0x680000;
                a0 = addiu(a0, 15696);  // "%f %f %f\n"
                a1 = s0;
                a2 = s5;
                a3 = v0;
                jal(ctx, 0x1E0228u, gen::fn_printf_005225a8);
                lwc1(f12, s1, 48);
                jal(ctx, 0x1E0234u, gen::fn_fptodp_00530da0);
                s0 = v0;
                lwc1(f12, s1, 52);
                jal(ctx, 0x1E0244u, gen::fn_fptodp_00530da0);
                s5 = v0;
                lwc1(f12, s1, 56);
                jal(ctx, 0x1E0254u, gen::fn_fptodp_00530da0);
                a0 = 0x680000;
                a0 = addiu(a0, 15696);  // "%f %f %f\n"
                a1 = s0;
                a2 = s5;
                a3 = v0;
                jal(ctx, 0x1E0270u, gen::fn_printf_005225a8);
                lwc1(f12, s1, 64);
                jal(ctx, 0x1E027Cu, gen::fn_fptodp_00530da0);
                s0 = v0;
                lwc1(f12, s1, 68);
                jal(ctx, 0x1E028Cu, gen::fn_fptodp_00530da0);
                s5 = v0;
                lwc1(f12, s1, 72);
                jal(ctx, 0x1E029Cu, gen::fn_fptodp_00530da0);
                a0 = 0x680000;
                a0 = addiu(a0, 15696);  // "%f %f %f\n"
                a1 = s0;
                a2 = s5;
                a3 = v0;
                jal(ctx, 0x1E02B8u, gen::fn_printf_005225a8);
                a0 = addiu(gp, -27168);  // "\n"
                jal(ctx, 0x1E02C4u, gen::fn_printf_005225a8);
                a2 = addiu(s1, 16);
                a1 = addiu(sp, 0x80);
                a0 = 8;
                for (;;) {
                    // 0x001e02d8
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x001e02fc
                charge(ctx, 36);
                a0 = addiu(sp, 0x80);
                a1 = a0;
                jal(ctx, 0x1E0304u, gen::fn_sub_4C2FB0_004c2fb0);
                s0 = addiu(sp, 0x90);
                lwc1(f12, s0, 8);
                lwc1(f13, s0, 4);
                jal(ctx, 0x1E0318u, gen::fn_atan2f_0052ea18);
                mov_s(f23, f0);
                lwc1(f12, s0, 0);
                jal(ctx, 0x1E0328u, gen::fn_asinf_0052ea00);
                neg_s(f21, f0);
                mov_s(f12, f21);
                jal(ctx, 0x1E0338u, gen::fn_cosf_0052e6d8);
                lwc1(f1, sp, 0xA0);
                div_s(f12, f1, f0);
                jal(ctx, 0x1E0358u, gen::fn_asinf_0052ea00);
                lwc1(f12, sp, 0x88);
                lwc1(f13, sp, 0x80);
                jal(ctx, 0x1E0368u, gen::fn_atan2f_0052ea18);
                mov_s(f22, f0);
                lwc1(f1, sp, 0x80);
                mtc1(zero, f0);
                c_le_s(f1, f0);
                if (cond(ctx)) {
                    // 0x001e038c
                    charge(ctx, 2);
                    lwc1(f0, gp, -32184);  // 0x7CAF38
                    sub_s(f23, f0, f23);
                }
                // 0x001e0394
                charge(ctx, 21);
                lwc1(f0, gp, -31708);  // 0x7CB114
                mul_s(f12, f23, f0);
                mul_s(f22, f22, f0);
                mul_s(f21, f21, f0);
                jal(ctx, 0x1E03A4u, gen::fn_fptodp_00530da0);
                s1 = v0;
                mov_s(f12, f22);
                jal(ctx, 0x1E03B4u, gen::fn_fptodp_00530da0);
                s0 = v0;
                mov_s(f12, f21);
                jal(ctx, 0x1E03C4u, gen::fn_fptodp_00530da0);
                a0 = 0x680000;
                a0 = addiu(a0, 15696);  // "%f %f %f\n"
                a1 = s1;
                a2 = s0;
                a3 = v0;
                jal(ctx, 0x1E03E0u, gen::fn_printf_005225a8);
            }
            // 0x001e03e8
            charge(ctx, 3);
            v0 = 1;
            if (s3 == v0) {
                // 0x001e03f4
                charge(ctx, 40);
                lwc1(f2, s4, 64);
                lwc1(f1, s4, 68);
                lwc1(f0, s4, 72);
                swc1(f2, sp, 0xF0);
                swc1(f1, sp, 0xF4);
                swc1(f0, sp, 0xF8);
                v0 = lui(0xBF80);
                mtc1(v0, f1);
                lwc1(f0, sp, 0xF0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE0);
                lwc1(f0, sp, 0xF4);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE4);
                lwc1(f0, sp, 0xF8);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE8);
                a0 = s4;
                a1 = addiu(sp, 0xE0);
                a2 = 2;
                jal(ctx, 0x1E0444u, gen::fn_sub_4CB750_004cb750);
                a0 = s4;
                a1 = s2;
                mov_s(f12, f20);
                a2 = 2;
                jal(ctx, 0x1E045Cu, gen::fn_sub_4CB890_004cb890);
                a0 = s4;
                a1 = addiu(sp, 0xC0);
                a2 = 2;
                jal(ctx, 0x1E0470u, gen::fn_sub_4CB750_004cb750);
                a0 = s4;
                a1 = addiu(sp, 0xF0);
                a2 = 2;
                jal(ctx, 0x1E0484u, gen::fn_sub_4CB750_004cb750);
            }
        } else {
            // 0x001dfac8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x001dfad8
                charge(ctx, 3);
                a2 = addiu(s4, 16);
                a1 = addiu(s0, 16);
                a0 = 8;
                for (;;) {
                    // 0x001dfae4
                    charge(ctx, 9);
                    lw(v1, a2, 0);
                    lw(v0, a2, 4);
                    a2 = addiu(a2, 8);
                    a0 = addiu(a0, -1);
                    sw(v1, a1, 0);
                    sw(v0, a1, 4);
                    a1 = addiu(a1, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x001dfb08
                charge(ctx, 5);
                lw(v0, s0, 0);
                v0 = addiu(v0, 1);
                sw(v0, s0, 0);
            } else {
                // 0x001dfad0
                charge(ctx, 2);
            }
        }
        // 0x001e04a0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001e04a4 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x001E1850 sub_1E1850 [K_FieldEditor_Update] -- 2732 bytes; frame 0xB0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E1850(task) -> 0, or -1 to be destroyed: the original's "field editor" (sub_1E2370; created only when the scene
// has a resource manager and an id): a menu (sub_1A3B10 / sub_1A3DC0 with the 11 items of 0x683E10) whose picks
// start a sub-task in work +4 and a title: 0 FREE CAMERA MODE (sub_1E0510), 2 NPC (create, sub_1E4B40), 3 NPC LIST
// (sub_1E5850), 4 POS (create, sub_1E6030), 5 POS LIST (sub_1E6A70), 7 / 10 a yes / no box, 8 SAVEFILE =
// fMMM_NNN_SSS.FBN with the set SSS (work +20, from the scene +20) chosen with the d-pad (+-1, +-10, wrapping at
// 256); state 7 writes the FBN (sub_1E2BD0) and reports success or "failed..". Confirm with circle (0x40), back with
// triangle (0x20). Debug only.
void sub_1E1850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e1850
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, f4::kTaskWork);
    lw(a1, s0, 0);
    at = sltiu(a1, 9);
    if (at != 0) {
        // 0x001e1878
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 28000);  // &0x7B6D60
        v0 = sll(a1, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1E1894u:  // table[0]
            // 0x001e1894
            charge(ctx, 24);
            a1 = 32;
            a2 = a1;
            a3 = 2;
            jal(ctx, 0x1E18A0u, gen::fn_sub_1A3B10_001a3b10);
            sw(v0, s0, 12);
            a0 = v0;
            a1 = 0x680000;
            a1 = addiu(a1, 15888);  // &0x683E10
            a2 = 11;
            jal(ctx, 0x1E18BCu, gen::fn_sub_1A3DC0_001a3dc0);
            lw(a0, s0, 12);
            a1 = 1;
            jal(ctx, 0x1E18CCu, gen::fn_sub_1A3BF0_001a3bf0);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lh(v0, v0, f4::scene::kNpcSet);
            sw(v0, s0, 20);
            lw(v0, s0, 0);
            v0 = addiu(v0, 1);
            sw(v0, s0, 0);
        L_001e22e0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1E18F4u:  // table[1]
            // 0x001e18f4
            charge(ctx, 4);
            v0 = addiu(a1, 1);
            sw(v0, s0, 0);
            goto L_001e22e0;
        case 0x1E1904u:  // table[2]
            // 0x001e1904
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e1d28
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e1d34
                    charge(ctx, 26);
                    a1 = 300;
                    a2 = 220;
                    a3 = 2;
                    jal(ctx, 0x1E1D40u, gen::fn_sub_1A3B10_001a3b10);
                    sw(v0, s0, 16);
                    a0 = v0;
                    a1 = addiu(gp, -27120);  // "NO"
                    jal(ctx, 0x1E1D54u, gen::fn_sub_1A3F20_001a3f20);
                    lw(a0, s0, 16);
                    a1 = addiu(gp, -27116);  // "YES"
                    jal(ctx, 0x1E1D64u, gen::fn_sub_1A3F20_001a3f20);
                    lw(a0, s0, 16);
                    a1 = 1;
                    jal(ctx, 0x1E1D74u, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s0, 12);
                    a1 = 0;
                    jal(ctx, 0x1E1D84u, gen::fn_sub_1A3BF0_001a3bf0);
                    v0 = 5;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001e1918
                charge(ctx, 6);
                lw(a0, s0, 12);
                jal(ctx, 0x1E191Cu, gen::fn_sub_1A4510_001a4510);
                at = sltiu(v0, 11);
                if (at != 0) {
                    // 0x001e1930
                    charge(ctx, 7);
                    v1 = 0x7B0000;
                    v1 = addiu(v1, 27952);  // &0x7B6D30
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x1E194Cu:  // table[0]
                        // 0x001e194c
                        charge(ctx, 35);
                        jal(ctx, 0x1E194Cu, gen::fn_sub_198590_00198590);
                        a0 = s1;
                        a1 = v0;
                        jal(ctx, 0x1E195Cu, gen::fn_sub_1E0510_001e0510);
                        sw(v0, s0, 4);
                        a0 = s1;
                        a1 = 442;
                        a2 = 56;
                        a3 = 2;
                        jal(ctx, 0x1E1978u, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 8);
                        a0 = v0;
                        a1 = 1;
                        jal(ctx, 0x1E198Cu, gen::fn_sub_1A3BE0_001a3be0);
                        lw(a0, s0, 8);
                        a1 = 0x680000;
                        a1 = addiu(a1, 16240);  // "FREE CAMERA MODE"
                        jal(ctx, 0x1E19A0u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 8);
                        a1 = 1;
                        jal(ctx, 0x1E19B0u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E19C0u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 3;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E19D8u:  // table[2]
                        // 0x001e19d8
                        charge(ctx, 31);
                        a0 = s1;
                        jal(ctx, 0x1E19DCu, gen::fn_sub_1E4B40_001e4b40);
                        sw(v0, s0, 4);
                        a0 = s1;
                        a1 = 598;
                        a2 = 56;
                        a3 = 2;
                        jal(ctx, 0x1E19F8u, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 8);
                        a0 = v0;
                        a1 = 1;
                        jal(ctx, 0x1E1A0Cu, gen::fn_sub_1A3BE0_001a3be0);
                        lw(a0, s0, 8);
                        a1 = addiu(gp, -27128);  // "NPC"
                        jal(ctx, 0x1E1A1Cu, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 8);
                        a1 = 1;
                        jal(ctx, 0x1E1A2Cu, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1A3Cu, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 3;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E1A54u:  // table[3]
                        // 0x001e1a54
                        charge(ctx, 32);
                        a0 = s1;
                        jal(ctx, 0x1E1A58u, gen::fn_sub_1E5850_001e5850);
                        sw(v0, s0, 4);
                        a0 = s1;
                        a1 = 538;
                        a2 = 56;
                        a3 = 2;
                        jal(ctx, 0x1E1A74u, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 8);
                        a0 = v0;
                        a1 = 1;
                        jal(ctx, 0x1E1A88u, gen::fn_sub_1A3BE0_001a3be0);
                        lw(a0, s0, 8);
                        a1 = 0x680000;
                        a1 = addiu(a1, 16264);  // "NPC LIST"
                        jal(ctx, 0x1E1A9Cu, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 8);
                        a1 = 1;
                        jal(ctx, 0x1E1AACu, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1ABCu, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 3;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E1AD4u:  // table[4]
                        // 0x001e1ad4
                        charge(ctx, 31);
                        a0 = s1;
                        jal(ctx, 0x1E1AD8u, gen::fn_sub_1E6030_001e6030);
                        sw(v0, s0, 4);
                        a0 = s1;
                        a1 = 598;
                        a2 = 56;
                        a3 = 2;
                        jal(ctx, 0x1E1AF4u, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 8);
                        a0 = v0;
                        a1 = 1;
                        jal(ctx, 0x1E1B08u, gen::fn_sub_1A3BE0_001a3be0);
                        lw(a0, s0, 8);
                        a1 = addiu(gp, -27124);  // "POS"
                        jal(ctx, 0x1E1B18u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 8);
                        a1 = 1;
                        jal(ctx, 0x1E1B28u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1B38u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 3;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E1B50u:  // table[5]
                        // 0x001e1b50
                        charge(ctx, 32);
                        a0 = s1;
                        jal(ctx, 0x1E1B54u, gen::fn_sub_1E6A70_001e6a70);
                        sw(v0, s0, 4);
                        a0 = s1;
                        a1 = 538;
                        a2 = 56;
                        a3 = 2;
                        jal(ctx, 0x1E1B70u, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 8);
                        a0 = v0;
                        a1 = 1;
                        jal(ctx, 0x1E1B84u, gen::fn_sub_1A3BE0_001a3be0);
                        lw(a0, s0, 8);
                        a1 = 0x680000;
                        a1 = addiu(a1, 16280);  // "POS LIST"
                        jal(ctx, 0x1E1B98u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 8);
                        a1 = 1;
                        jal(ctx, 0x1E1BA8u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1BB8u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 3;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E1BD0u:  // table[7]
                        // 0x001e1bd0
                        charge(ctx, 27);
                        a0 = s1;
                        a1 = 300;
                        a2 = 220;
                        a3 = 2;
                        jal(ctx, 0x1E1BE0u, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 16);
                        a0 = v0;
                        a1 = addiu(gp, -27120);  // "NO"
                        jal(ctx, 0x1E1BF4u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 16);
                        a1 = addiu(gp, -27116);  // "YES"
                        jal(ctx, 0x1E1C04u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 16);
                        a1 = 1;
                        jal(ctx, 0x1E1C14u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1C24u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 4;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E1C3Cu:  // table[8]
                        // 0x001e1c3c
                        charge(ctx, 32);
                        a0 = s1;
                        a1 = 64;
                        a2 = a1;
                        a3 = 2;
                        jal(ctx, 0x1E1C4Cu, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 16);
                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        a0 = addiu(sp, 0x30);
                        a1 = 0x680000;
                        a1 = addiu(a1, 16304);  // "SAVEFILE = f%03d_%03d_%03d.FBN"
                        lw(a2, v0, f4::scene::kMajor);
                        lw(a3, v0, f4::scene::kMinor);
                        lw(t0, s0, 20);
                        jal(ctx, 0x1E1C74u, gen::fn_sprintf_00523ac8);
                        lw(a0, s0, 16);
                        a1 = addiu(sp, 0x30);
                        jal(ctx, 0x1E1C84u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 16);
                        a1 = 1;
                        jal(ctx, 0x1E1C94u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1CA4u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 6;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E1CBCu:  // table[10]
                        // 0x001e1cbc
                        charge(ctx, 27);
                        a0 = s1;
                        a1 = 300;
                        a2 = 220;
                        a3 = 2;
                        jal(ctx, 0x1E1CCCu, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s0, 16);
                        a0 = v0;
                        a1 = addiu(gp, -27120);  // "NO"
                        jal(ctx, 0x1E1CE0u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 16);
                        a1 = addiu(gp, -27116);  // "YES"
                        jal(ctx, 0x1E1CF0u, gen::fn_sub_1A3F20_001a3f20);
                        lw(a0, s0, 16);
                        a1 = 1;
                        jal(ctx, 0x1E1D00u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 12);
                        a1 = 0;
                        jal(ctx, 0x1E1D10u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 5;
                        sw(v0, s0, 0);
                        break;
                    case 0x1E22E0u:  // table[1, 6, 9]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
            }
            goto L_001e22e0;
        case 0x1E1D9Cu:  // table[3]
            // 0x001e1d9c
            charge(ctx, 6);
            lw(a0, s0, 4);
            jal(ctx, 0x1E1DA0u, gen::fn_kwlnTaskExists_00195460);
            a1 = 1;
            if (v0 != a1) {
                // 0x001e1db4
                charge(ctx, 6);
                lw(a0, s0, 12);
                jal(ctx, 0x1E1DB8u, gen::fn_sub_1A3BF0_001a3bf0);
                lw(a0, s0, 8);
                if (a0 != 0) {
                    // 0x001e1dcc
                    charge(ctx, 3);
                    jal(ctx, 0x1E1DCCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    sw(zero, s0, 8);
                }
                // 0x001e1dd8
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_001e22e0;
        case 0x1E1DE8u:  // table[4]
            // 0x001e1de8
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e1e78
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e1e84
                    charge(ctx, 11);
                    lw(a0, s0, 12);
                    a1 = 1;
                    jal(ctx, 0x1E1E8Cu, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s0, 16);
                    jal(ctx, 0x1E1E98u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001e1dfc
                charge(ctx, 6);
                lw(a0, s0, 16);
                jal(ctx, 0x1E1E00u, gen::fn_sub_1A4510_001a4510);
                a0 = 1;
                if (v0 == a0) {
                    // 0x001e1e24
                    charge(ctx, 10);
                    jal(ctx, 0x1E1E24u, gen::fn_sub_1E2930_001e2930);
                    a0 = 1;
                    jal(ctx, 0x1E1E30u, gen::fn_sub_1E2B10_001e2b10);
                    a0 = addiu(gp, -19000);  // &0x7CE2B8
                    a1 = 0;
                    a2 = 8;
                    jal(ctx, 0x1E1E44u, gen::fn_memset_00521408);
                } else {
                    // 0x001e1e14
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x001e1e1c
                        charge(ctx, 2);
                    }
                }
                // 0x001e1e4c
                charge(ctx, 11);
                lw(a0, s0, 12);
                a1 = 1;
                jal(ctx, 0x1E1E54u, gen::fn_sub_1A3BF0_001a3bf0);
                lw(a0, s0, 16);
                jal(ctx, 0x1E1E60u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_001e22e0;
        case 0x1E1EB0u:  // table[5]
            // 0x001e1eb0
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e1f24
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e1f30
                    charge(ctx, 11);
                    lw(a0, s0, 12);
                    a1 = 1;
                    jal(ctx, 0x1E1F38u, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s0, 16);
                    jal(ctx, 0x1E1F44u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001e1ec4
                charge(ctx, 6);
                lw(a0, s0, 16);
                jal(ctx, 0x1E1EC8u, gen::fn_sub_1A4510_001a4510);
                a1 = 1;
                if (v0 == a1) {
                    // 0x001e1f14
                    charge(ctx, 4);
                    v0 = 8;
                    sw(v0, s0, 0);
                } else {
                    // 0x001e1edc
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001e1eec
                        charge(ctx, 10);
                        lw(a0, s0, 12);
                        jal(ctx, 0x1E1EF0u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(a0, s0, 16);
                        jal(ctx, 0x1E1EFCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        v0 = 2;
                        sw(v0, s0, 0);
                    } else {
                        // 0x001e1ee4
                        charge(ctx, 2);
                    }
                }
            }
            goto L_001e22e0;
        case 0x1E1F5Cu:  // table[6]
            // 0x001e1f5c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2386);  // 0x7E0952
            v0 = v1 & 0x9000;
            if (v0 == 0) {
                // 0x001e1fd8
                charge(ctx, 3);
                v0 = v1 & 0x6000;
                if (v0 == 0) {
                    // 0x001e204c
                    charge(ctx, 3);
                    v0 = v1 & 0xA;
                    if (v0 == 0) {
                        // 0x001e20c0
                        charge(ctx, 3);
                        v0 = v1 & 0x5;
                        if (v0 != 0) {
                            // 0x001e20cc
                            charge(ctx, 5);
                            lw(v0, s0, 20);
                            v0 = addiu(v0, -10);
                            sw(v0, s0, 20);
                            if (i64(v0) < 0) {
                                // 0x001e20e0
                                charge(ctx, 2);
                                v0 = 255;
                                sw(v0, s0, 20);
                            }
                            // 0x001e20e8
                            charge(ctx, 17);
                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            a0 = addiu(sp, 0x30);
                            a1 = 0x680000;
                            a1 = addiu(a1, 16304);  // "SAVEFILE = f%03d_%03d_%03d.FBN"
                            lw(a2, v0, f4::scene::kMajor);
                            lw(a3, v0, f4::scene::kMinor);
                            lw(t0, s0, 20);
                            jal(ctx, 0x1E2104u, gen::fn_sprintf_00523ac8);
                            lw(a0, s0, 16);
                            a1 = 0;
                            jal(ctx, 0x1E2114u, gen::fn_sub_1A4010_001a4010);
                            a0 = v0;
                            a1 = addiu(sp, 0x30);
                            jal(ctx, 0x1E2124u, gen::fn_strcpy_00524270);
                        }
                    } else {
                        // 0x001e2058
                        charge(ctx, 6);
                        lw(v0, s0, 20);
                        v0 = addiu(v0, 10);
                        sw(v0, s0, 20);
                        at = slti(v0, 256);
                        if (at == 0) {
                            // 0x001e2070
                            charge(ctx, 1);
                            sw(zero, s0, 20);
                        }
                        // 0x001e2074
                        charge(ctx, 19);
                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        a0 = addiu(sp, 0x30);
                        a1 = 0x680000;
                        a1 = addiu(a1, 16304);  // "SAVEFILE = f%03d_%03d_%03d.FBN"
                        lw(a2, v0, f4::scene::kMajor);
                        lw(a3, v0, f4::scene::kMinor);
                        lw(t0, s0, 20);
                        jal(ctx, 0x1E2090u, gen::fn_sprintf_00523ac8);
                        lw(a0, s0, 16);
                        a1 = 0;
                        jal(ctx, 0x1E20A0u, gen::fn_sub_1A4010_001a4010);
                        a0 = v0;
                        a1 = addiu(sp, 0x30);
                        jal(ctx, 0x1E20B0u, gen::fn_strcpy_00524270);
                    }
                } else {
                    // 0x001e1fe4
                    charge(ctx, 5);
                    lw(v0, s0, 20);
                    v0 = addiu(v0, -1);
                    sw(v0, s0, 20);
                    if (i64(v0) < 0) {
                        // 0x001e1ff8
                        charge(ctx, 2);
                        v0 = 255;
                        sw(v0, s0, 20);
                    }
                    // 0x001e2000
                    charge(ctx, 19);
                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    a0 = addiu(sp, 0x30);
                    a1 = 0x680000;
                    a1 = addiu(a1, 16304);  // "SAVEFILE = f%03d_%03d_%03d.FBN"
                    lw(a2, v0, f4::scene::kMajor);
                    lw(a3, v0, f4::scene::kMinor);
                    lw(t0, s0, 20);
                    jal(ctx, 0x1E201Cu, gen::fn_sprintf_00523ac8);
                    lw(a0, s0, 16);
                    a1 = 0;
                    jal(ctx, 0x1E202Cu, gen::fn_sub_1A4010_001a4010);
                    a0 = v0;
                    a1 = addiu(sp, 0x30);
                    jal(ctx, 0x1E203Cu, gen::fn_strcpy_00524270);
                }
            } else {
                // 0x001e1f70
                charge(ctx, 6);
                lw(v0, s0, 20);
                v0 = addiu(v0, 1);
                sw(v0, s0, 20);
                at = slti(v0, 256);
                if (at == 0) {
                    // 0x001e1f88
                    charge(ctx, 1);
                    sw(zero, s0, 20);
                }
                // 0x001e1f8c
                charge(ctx, 19);
                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                a0 = addiu(sp, 0x30);
                a1 = 0x680000;
                a1 = addiu(a1, 16304);  // "SAVEFILE = f%03d_%03d_%03d.FBN"
                lw(a2, v0, f4::scene::kMajor);
                lw(a3, v0, f4::scene::kMinor);
                lw(t0, s0, 20);
                jal(ctx, 0x1E1FA8u, gen::fn_sprintf_00523ac8);
                lw(a0, s0, 16);
                a1 = 0;
                jal(ctx, 0x1E1FB8u, gen::fn_sub_1A4010_001a4010);
                a0 = v0;
                a1 = addiu(sp, 0x30);
                jal(ctx, 0x1E1FC8u, gen::fn_strcpy_00524270);
            }
            // 0x001e212c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e21a8
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e21b4
                    charge(ctx, 11);
                    lw(a0, s0, 12);
                    a1 = 1;
                    jal(ctx, 0x1E21BCu, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s0, 16);
                    jal(ctx, 0x1E21C8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001e2140
                charge(ctx, 26);
                lw(a0, s0, 16);
                jal(ctx, 0x1E2144u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                a0 = s1;
                a1 = 300;
                a2 = 220;
                a3 = 2;
                jal(ctx, 0x1E215Cu, gen::fn_sub_1A3B10_001a3b10);
                sw(v0, s0, 16);
                a0 = v0;
                a1 = addiu(gp, -27120);  // "NO"
                jal(ctx, 0x1E2170u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s0, 16);
                a1 = addiu(gp, -27116);  // "YES"
                jal(ctx, 0x1E2180u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s0, 16);
                a1 = 1;
                jal(ctx, 0x1E2190u, gen::fn_sub_1A3BF0_001a3bf0);
                v0 = 7;
                sw(v0, s0, 0);
            }
            goto L_001e22e0;
        case 0x1E21E0u:  // table[7]
            // 0x001e21e0
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e229c
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e22a8
                    charge(ctx, 11);
                    lw(a0, s0, 12);
                    a1 = 1;
                    jal(ctx, 0x1E22B0u, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s0, 16);
                    jal(ctx, 0x1E22BCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001e21f4
                charge(ctx, 6);
                lw(a0, s0, 16);
                jal(ctx, 0x1E21F8u, gen::fn_sub_1A4510_001a4510);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001e221c
                    charge(ctx, 6);
                    lh(a0, s0, 20);
                    jal(ctx, 0x1E2220u, gen::fn_sub_1E2BD0_001e2bd0);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x001e2254
                        charge(ctx, 7);
                        a0 = s1;
                        a1 = 0;
                        a2 = 400;
                        a3 = 0x680000;
                        a3 = addiu(a3, 16336);  // "failed.."
                        jal(ctx, 0x1E2268u, gen::fn_sub_1A1540_001a1540);
                    } else {
                        // 0x001e2234
                        charge(ctx, 8);
                        a0 = s1;
                        a1 = 0;
                        a2 = 400;
                        a3 = addiu(gp, -27112);  // "saved.."
                        jal(ctx, 0x1E2244u, gen::fn_sub_1A1540_001a1540);
                    }
                } else {
                    // 0x001e220c
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x001e2214
                        charge(ctx, 2);
                    }
                }
                // 0x001e2270
                charge(ctx, 11);
                lw(a0, s0, 12);
                a1 = 1;
                jal(ctx, 0x1E2278u, gen::fn_sub_1A3BF0_001a3bf0);
                lw(a0, s0, 16);
                jal(ctx, 0x1E2284u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_001e22e0;
        case 0x1E22D4u:  // table[8]
            // 0x001e22d4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001e22e4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xB0);
        return;
    }
    goto L_001e22e0;
}

// 0x001E2300 sub_1E2300 [K_FieldEditor_Destroy] -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E2300(task): drops the editor's NPC and position records (sub_1E2930(0), sub_1E2B10(0), the list heads
// 0x7CE2B8 / 0x7CE2BC cleared) and frees the work.
void sub_1E2300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2300
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x1E2314u, gen::fn_sub_1E2930_001e2930);
    a0 = 0;
    jal(ctx, 0x1E2320u, gen::fn_sub_1E2B10_001e2b10);
    a0 = addiu(gp, -19000);  // &0x7CE2B8
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x1E2334u, gen::fn_memset_00521408);
    lw(a0, s0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E2348u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E2370 sub_1E2370 [K_FieldEditor_CreateTask] -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E2370(parent) -> the "field editor" task (24-byte work) after snapshotting the scene's NPCs and positions
// (sub_1E2430), or 0 when the scene has no resource manager (+8) or no id. Caller: the event debug menu sub_36D5F0.
void sub_1E2370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2370
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // the parent task
    lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
    lw(v0, v1, f4::scene::kResMgr);
    bool scene = false;
    if (v0 != 0) {
        // 0x001e2390: a scene with a resource manager and an id
        charge(ctx, 4);
        lw(v1, v1, f4::scene::kMajor);
        v0 = si(-1);
        scene = v1 != v0;
    }
    if (!scene) {
        // 0x001e23a0: no editor
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x001e23ac: the 24-byte work (RwCalloc through the slot 0x960184)
        charge(ctx, 9);
        a0 = 1;
        a1 = 24;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x1E23C0u, v0.u());
        if (v0 != 0) {
            // 0x001e23dc
            charge(ctx, 15);
            a0 = s0;
            a1 = 10;
            a2 = 0x680000;
            a2 = addiu(a2, 16352);  // "field editor"
            a3 = 0x1E0000;
            a3 = addiu(a3, 6224);  // &sub_1E1850
            t0 = 0x1E0000;
            t0 = addiu(t0, 8960);  // &sub_1E2300
            t1 = v0;
            jal(ctx, 0x1E2400u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
            s0 = v0;
            jal(ctx, 0x1E240Cu, gen::fn_sub_1E2430_001e2430);  // snapshot the scene's NPCs and positions
            v0 = s0;
        } else {
            // 0x001e23d0
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001e2418 (the shared epilogue)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E2430 sub_1E2430 [K_FieldEditor_SnapshotScene] -- 984 bytes; frame 0x90: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1E2430(): copies the scene's NPCs (type 3 resources) into 112-byte FBN NPC records (sub_1E2850): +0 the model,
// +8 the resource id, +4 / +6 the model's ids (model +212 / +214), +12 the collision radius (the controller +488,
// K_FldFrame_CtlGetSphereCollisRadius), +11 bit 0 = resource +40 bit 31, +10 = resource +480, +16 = +484, +97 = +482,
// +32 the model matrix (64 bytes), +96 / +100 from the resource's +496 task (sub_19C300 / sub_19C490); and the
// positions (type 8) into 96-byte records (sub_1E2A20) with a marker task (sub_1A4CD0) whose frame is built from the
// three axes 0x683FF0.. and the resource's position, the frame matrix at +16.
void sub_1E2430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001e2430
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    a0 = 3;
    jal(ctx, 0x1E244Cu, gen::fn_sub_3B5D50_003b5d50);
    s2 = v0;
    a0 = 8;
    jal(ctx, 0x1E245Cu, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    for (;;) {
        // 0x001e255c
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e2470
        charge(ctx, 22);
        jal(ctx, 0x1E2470u, gen::fn_sub_1E2850_001e2850);
        s0 = v0;
        lw(v1, s2, 296);
        sw(v1, v0, 0);
        lhu(v1, s2, 0);
        sh(v1, v0, 8);
        lw(v1, s2, 296);
        lhu(v1, v1, 212);
        sh(v1, v0, 4);
        lw(v1, s2, 296);
        lhu(v1, v1, 214);
        sh(v1, v0, 6);
        lw(a0, s2, 488);
        jal(ctx, 0x1E24A8u, gen::fn_K_FldFrame_CtlGetSphereCollisRadius_001ad8b0);
        swc1(f0, s0, 12);
        lw(v1, s2, 40);
        v0 = lui(0x8000);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x001e24dc
            charge(ctx, 3);
            lbu(v0, s0, 11);
            v0 = v0 & 0xFE;
            sb(v0, s0, 11);
        } else {
            // 0x001e24c8
            charge(ctx, 5);
            lbu(v0, s0, 11);
            v0 = v0 | 0x1;
            sb(v0, s0, 11);
        }
        // 0x001e24e8
        charge(ctx, 11);
        lhu(v0, s2, 480);
        sb(v0, s0, 10);
        lw(v0, s2, 484);
        sw(v0, s0, 16);
        lbu(v0, s2, 482);
        sb(v0, s0, 97);
        lw(a0, s2, 296);
        jal(ctx, 0x1E2504u, gen::fn_sub_318B60_00318b60);
        a2 = addiu(s0, 32);
        a1 = 8;
        for (;;) {
            // 0x001e2514
            charge(ctx, 9);
            lw(a0, v0, 0);
            lw(v1, v0, 4);
            v0 = addiu(v0, 8);
            a1 = addiu(a1, -1);
            sw(a0, a2, 0);
            sw(v1, a2, 4);
            a2 = addiu(a2, 8);
            if (i64(a1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x001e2538
        charge(ctx, 9);
        lw(a0, s2, 496);
        jal(ctx, 0x1E253Cu, gen::fn_sub_19C300_0019c300);
        sb(v0, s0, 96);
        lw(a0, s2, 496);
        jal(ctx, 0x1E254Cu, gen::fn_sub_19C490_0019c490);
        swc1(f0, s0, 100);
        lw(s2, s2, 248);
    }
    // 0x001e2564
    charge(ctx, 2);
    for (;;) {
        // 0x001e27e0
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e256c
        charge(ctx, 147);
        jal(ctx, 0x1E256Cu, gen::fn_sub_1E2A20_001e2a20);
        s0 = v0;
        v1 = 0x680000;
        ld(a0, v1, 16368);  // 0x683FF0
        v1 = 0x680000;
        lwc1(f0, v1, 16376);  // 0x683FF8
        sd(a0, sp, 0x80);
        swc1(f0, sp, 0x88);
        v1 = 0x680000;
        ld(a0, v1, 16384);  // 0x684000
        v1 = 0x680000;
        lwc1(f0, v1, 16392);  // 0x684008
        sd(a0, sp, 0x70);
        swc1(f0, sp, 0x78);
        v1 = 0x680000;
        ld(a0, v1, 16400);  // 0x684010
        v1 = 0x680000;
        lwc1(f0, v1, 16408);  // 0x684018
        sd(a0, sp, 0x60);
        swc1(f0, sp, 0x68);
        lhu(v1, s1, 0);
        sh(v1, v0, 80);
        a0 = 0;
        jal(ctx, 0x1E25CCu, gen::fn_sub_1A4CD0_001a4cd0);
        sw(v0, s0, 0);
        v1 = 0x3F800000;
        mtc1(v1, f20);
        a0 = v0;
        jal(ctx, 0x1E25E4u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 40);
        lw(a0, s0, 0);
        jal(ctx, 0x1E25F4u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 20);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2604u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 0);
        mtc1(zero, f20);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2618u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 16);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2628u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 8);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2638u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 4);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2648u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 36);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2658u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 32);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2668u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 24);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2678u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 56);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2688u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 52);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2698u, gen::fn_sub_1A4E50_001a4e50);
        swc1(f20, v0, 48);
        lw(a0, s0, 0);
        jal(ctx, 0x1E26A8u, gen::fn_sub_1A4E50_001a4e50);
        lw(v1, v0, 12);
        v0 = 0x20000;
        v0 = v0 | 0x3;
        s2 = v1 | v0;
        lw(a0, s0, 0);
        jal(ctx, 0x1E26C4u, gen::fn_sub_1A4E50_001a4e50);
        sw(s2, v0, 12);
        lw(a0, s0, 0);
        jal(ctx, 0x1E26D4u, gen::fn_sub_1A4E50_001a4e50);
        a0 = v0;
        a1 = addiu(sp, 0x80);
        lwc1(f12, s1, 16);
        a2 = 2;
        jal(ctx, 0x1E26ECu, gen::fn_sub_4C31B0_004c31b0);
        lw(a0, s0, 0);
        jal(ctx, 0x1E26F8u, gen::fn_sub_1A4E50_001a4e50);
        a0 = v0;
        a1 = addiu(sp, 0x70);
        lwc1(f12, s1, 20);
        a2 = 2;
        jal(ctx, 0x1E2710u, gen::fn_sub_4C31B0_004c31b0);
        lw(a0, s0, 0);
        jal(ctx, 0x1E271Cu, gen::fn_sub_1A4E50_001a4e50);
        a0 = v0;
        a1 = addiu(sp, 0x60);
        lwc1(f12, s1, 24);
        a2 = 2;
        jal(ctx, 0x1E2734u, gen::fn_sub_4C31B0_004c31b0);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2740u, gen::fn_sub_1A4E50_001a4e50);
        lwc1(f2, s1, 4);
        lwc1(f1, s1, 8);
        lwc1(f0, s1, 12);
        swc1(f2, v0, 48);
        swc1(f1, v0, 52);
        swc1(f0, v0, 56);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x1E2764u, gen::fn_sub_4C2CC0_004c2cc0);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2770u, gen::fn_sub_1A4E50_001a4e50);
        a0 = v0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x1E2780u, gen::fn_sub_4C2D20_004c2d20);
        lw(a0, s0, 0);
        jal(ctx, 0x1E278Cu, gen::fn_sub_1A4E50_001a4e50);
        a0 = v0;
        jal(ctx, 0x1E2798u, gen::fn_sub_4C2F10_004c2f10);
        lw(a0, s0, 0);
        jal(ctx, 0x1E27A4u, gen::fn_sub_1A4E50_001a4e50);
        a2 = addiu(s0, 16);
        a1 = 8;
        a3 = v0;
        for (;;) {
            // 0x001e27b8
            charge(ctx, 9);
            lw(a0, a3, 0);
            lw(v1, a3, 4);
            a3 = addiu(a3, 8);
            a1 = addiu(a1, -1);
            sw(a0, a2, 0);
            sw(v1, a2, 4);
            a2 = addiu(a2, 8);
            if (i64(a1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x001e27dc
        charge(ctx, 1);
        lw(s1, s1, 248);
    }
    // 0x001e27e8
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001E2850 sub_1E2850 [K_FieldEditor_NewNpcRecord] -- 80 bytes; frame 0x10: ra sp+0x0
// sub_1E2850() -> a new 112-byte NPC record pushed on the editor's NPC list 0x7CE2B8 (+104 prev, +108 next).
void sub_1E2850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2850
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 112;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1E286Cu, v0.u());
    lw(v1, gp, -19000);  // 0x7CE2B8
    if (v1 != 0) {
        // 0x001e2880
        charge(ctx, 1);
        sw(v0, v1, 104);
    }
    // 0x001e2884 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, gp, -19000);  // 0x7CE2B8
    sw(v1, v0, 108);
    sw(v0, gp, -19000);  // 0x7CE2B8
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E28A0 sub_1E28A0 [K_FieldEditor_FreeNpcRecord] -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E28A0(record, alsoResource): unlinks and frees an NPC record; with alsoResource the scene resource (+8) is
// destroyed too (sub_3B7090).
void sub_1E28A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e28a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 1;
    if (a1 == v0) {
        // 0x001e28bc
        charge(ctx, 3);
        lhu(a0, s0, 8);
        jal(ctx, 0x1E28C0u, gen::fn_sub_3B7090_003b7090);
    }
    // 0x001e28c8
    charge(ctx, 3);
    lw(v1, s0, 104);
    if (v1 == 0) {
        // 0x001e28e4
        charge(ctx, 2);
        lw(v0, s0, 108);
        sw(v0, gp, -19000);  // 0x7CE2B8
    } else {
        // 0x001e28d4
        charge(ctx, 4);
        lw(v0, s0, 108);
        sw(v0, v1, 108);
    }
    // 0x001e28ec
    charge(ctx, 3);
    lw(v1, s0, 108);
    if (v1 != 0) {
        // 0x001e28f8
        charge(ctx, 2);
        lw(v0, s0, 104);
        sw(v0, v1, 104);
    }
    // 0x001e2900
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E290Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E2930 sub_1E2930 [K_FieldEditor_FreeNpcRecords] -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E2930(alsoResources): frees every record of the NPC list (sub_1E28A0 inlined).
void sub_1E2930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2930
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, gp, -19000);  // 0x7CE2B8
    for (;;) {
        // 0x001e29b8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e2950
        charge(ctx, 3);
        v0 = 1;
        if (s1 == v0) {
            // 0x001e295c
            charge(ctx, 3);
            lhu(a0, s0, 8);
            jal(ctx, 0x1E2960u, gen::fn_sub_3B7090_003b7090);
        }
        // 0x001e2968
        charge(ctx, 3);
        lw(v1, s0, 104);
        if (v1 == 0) {
            // 0x001e2984
            charge(ctx, 2);
            lw(v0, s0, 108);
            sw(v0, gp, -19000);  // 0x7CE2B8
        } else {
            // 0x001e2974
            charge(ctx, 4);
            lw(v0, s0, 108);
            sw(v0, v1, 108);
        }
        // 0x001e298c
        charge(ctx, 3);
        lw(v1, s0, 108);
        if (v1 != 0) {
            // 0x001e2998
            charge(ctx, 2);
            lw(v0, s0, 104);
            sw(v0, v1, 104);
        }
        // 0x001e29a0
        charge(ctx, 6);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1E29ACu, v0.u());
        lw(s0, s0, 108);
    }
    // 0x001e29c0
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001E2A20 sub_1E2A20 [K_FieldEditor_NewPosRecord] -- 80 bytes; frame 0x10: ra sp+0x0
// sub_1E2A20() -> a new 96-byte position record pushed on the list 0x7CE2BC (+84 prev, +88 next).
void sub_1E2A20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2a20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 96;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1E2A3Cu, v0.u());
    lw(v1, gp, -18996);  // 0x7CE2BC
    if (v1 != 0) {
        // 0x001e2a50
        charge(ctx, 1);
        sw(v0, v1, 84);
    }
    // 0x001e2a54 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, gp, -18996);  // 0x7CE2BC
    sw(v1, v0, 88);
    sw(v0, gp, -18996);  // 0x7CE2BC
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E2A70 sub_1E2A70 [K_FieldEditor_FreePosRecord] -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E2A70(record, alsoResource): destroys the record's marker task (+0), optionally the scene resource (+80),
// unlinks and frees it.
void sub_1E2A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2a70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 1;
    if (a1 == v0) {
        // 0x001e2a8c
        charge(ctx, 3);
        lhu(a0, s0, 80);
        jal(ctx, 0x1E2A90u, gen::fn_sub_3B7090_003b7090);
    }
    // 0x001e2a98
    charge(ctx, 6);
    lw(a0, s0, 0);
    jal(ctx, 0x1E2A9Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    lw(v1, s0, 84);
    if (v1 == 0) {
        // 0x001e2ac0
        charge(ctx, 2);
        lw(v0, s0, 88);
        sw(v0, gp, -18996);  // 0x7CE2BC
    } else {
        // 0x001e2ab0
        charge(ctx, 4);
        lw(v0, s0, 88);
        sw(v0, v1, 88);
    }
    // 0x001e2ac8
    charge(ctx, 3);
    lw(v1, s0, 88);
    if (v1 != 0) {
        // 0x001e2ad4
        charge(ctx, 2);
        lw(v0, s0, 84);
        sw(v0, v1, 84);
    }
    // 0x001e2adc
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E2AE8u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E2B10 sub_1E2B10 [K_FieldEditor_FreePosRecords] -- 180 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E2B10(alsoResources): frees every record of the position list.
void sub_1E2B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2b10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, gp, -18996);  // 0x7CE2BC
    for (;;) {
        // 0x001e2ba4
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e2b30
        charge(ctx, 3);
        v0 = 1;
        if (s1 == v0) {
            // 0x001e2b3c
            charge(ctx, 3);
            lhu(a0, s0, 80);
            jal(ctx, 0x1E2B40u, gen::fn_sub_3B7090_003b7090);
        }
        // 0x001e2b48
        charge(ctx, 6);
        lw(a0, s0, 0);
        jal(ctx, 0x1E2B4Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        lw(v1, s0, 84);
        if (v1 == 0) {
            // 0x001e2b70
            charge(ctx, 2);
            lw(v0, s0, 88);
            sw(v0, gp, -18996);  // 0x7CE2BC
        } else {
            // 0x001e2b60
            charge(ctx, 4);
            lw(v0, s0, 88);
            sw(v0, v1, 88);
        }
        // 0x001e2b78
        charge(ctx, 3);
        lw(v1, s0, 88);
        if (v1 != 0) {
            // 0x001e2b84
            charge(ctx, 2);
            lw(v0, s0, 84);
            sw(v0, v1, 84);
        }
        // 0x001e2b8c
        charge(ctx, 6);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1E2B98u, v0.u());
        lw(s0, s0, 88);
    }
    // 0x001e2bac
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001E2BD0 sub_1E2BD0 [K_FieldEditor_WriteFbn] -- 460 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E2BD0() -> 1 when the FBN image was built: unless a schedule NPC was placed (0x7CE2C0) or there is no scene:
// counts both lists, allocates 24 + 112 n + 96 p bytes, writes the FBN header {0x12345678, 0x00010001, n, 112, p, 96}
// and the records in list order, then frees the image again (the retail build has no file write here; the debug
// build presumably wrote it to the host). The layout every FBN file on the disc has (field4.h fbn).
void sub_1E2BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2bd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x1E2BE4u, gen::fn_sub_1E1840_001e1840);
    lw(s0, v0, 0);
    jal(ctx, 0x1E2BF0u, gen::fn_sub_1E1840_001e1840);
    lw(a0, v0, 4);
    lw(v1, gp, -18992);  // 0x7CE2C0
    v0 = 1;
    if (v1 != v0) {
        // 0x001e2c18
        charge(ctx, 5);
        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        lw(v1, v0, f4::scene::kMajor);
        v0 = si(-1);
        if (v1 != v0) {
            // 0x001e2c38
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001e2c4c
                charge(ctx, 5);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e2c44
                charge(ctx, 2);
                lw(s0, s0, 108);
                s1 = addiu(s1, 1);
            }
            // 0x001e2c60
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x001e2c74
                charge(ctx, 5);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e2c6c
                charge(ctx, 2);
                lw(a0, a0, 88);
                s0 = addiu(s0, 1);
            }
            // 0x001e2c88
            charge(ctx, 33);
            v0 = sll(s1, 3);
            v0 = subu(v0, s1);
            v0 = sll(v0, 4);
            v1 = addiu(v0, 24);
            v0 = sll(s0, 1);
            v0 = addu(v0, s0);
            v0 = sll(v0, 5);
            a1 = addu(v1, v0);
            a0 = 1;
            a2 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 388);  // 0x960184
            jalr(ctx, 0x1E2CB8u, v0.u());
            s2 = v0;
            v1 = 0x12340000;
            v1 = v1 | 0x5678;
            sw(v1, v0, 0);
            v1 = 0x10000;
            v1 = v1 | 0x1;
            sw(v1, v0, 4);
            sw(s1, v0, 8);
            v1 = 112;
            sw(v1, v0, 12);
            sw(s0, v0, 16);
            v1 = 96;
            sw(v1, v0, 20);
            s1 = addiu(s2, 24);
            jal(ctx, 0x1E2CF8u, gen::fn_sub_1E1840_001e1840);
            lw(s0, v0, 0);
            for (;;) {
                // 0x001e2d28
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e2d0c
                charge(ctx, 7);
                a0 = s1;
                a1 = s0;
                a2 = 112;
                jal(ctx, 0x1E2D18u, gen::fn_memcpy_00521250);
                s1 = addiu(s1, 112);
                lw(s0, s0, 108);
            }
            // 0x001e2d30
            charge(ctx, 5);
            jal(ctx, 0x1E2D30u, gen::fn_sub_1E1840_001e1840);
            lw(s0, v0, 4);
            for (;;) {
                // 0x001e2d60
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e2d44
                charge(ctx, 7);
                a0 = s1;
                a1 = s0;
                a2 = 96;
                jal(ctx, 0x1E2D50u, gen::fn_memcpy_00521250);
                s1 = addiu(s1, 96);
                lw(s0, s0, 88);
            }
            // 0x001e2d68
            charge(ctx, 6);
            a0 = s2;
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1E2D74u, v0.u());
            v0 = 1;
        } else {
            // 0x001e2c2c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001e2c0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e2d80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001E2DA0 sub_1E2DA0 [K_Fldrc_RequestFbn] -- 172 bytes; frame 0xC0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E2DA0(major, minor, set) -> the request of "field/data/fMMM_NNN_SSS.FBN" (NPC placement), 1 when the .pac is
// resident (the file then comes from it), 0 when it does not exist.
void sub_1E2DA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e2da0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    jal(ctx, 0x1E2DC0u, gen::fn_sub_1B0910_001b0910);
    if (v0 != 0) {
        // 0x001e2e2c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x001e2dd0
        charge(ctx, 14);
        a2 = s2 & 0xFFFF;
        a3 = s1 & 0xFFFF;
        t0 = dsll32(s0, 16);
        t0 = dsra32(t0, 16);
        a0 = addiu(sp, 0x40);
        a1 = 0x680000;
        a1 = addiu(a1, 16416);  // "field/data/f%03d_%03d_%03d.FBN"
        jal(ctx, 0x1E2DECu, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x1E2DF8u, gen::fn_H_Cdvd_FileExists_001008b0);
        if (v0 != 0) {
            // 0x001e2e14
            charge(ctx, 6);
            a0 = addiu(sp, 0x40);
            a1 = 0;
            jal(ctx, 0x1E2E1Cu, gen::fn_H_Cdvd_Request_00100d80);
        } else {
            // 0x001e2e08
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001e2e30 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x001E2E50 sub_1E2E50 [K_Fldrc_TryLoadFbn] -- 2800 bytes; frame 0xF0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E2E50(request, &data, major, minor, set) -> 1 when the FBN header is read (0 while loading; 1 at once for no
// file): from the .pac cache ("field/pack/fMMM_NNN_SSS.FBN", *data = the cached file) or the loaded request. The NPC
// slots: sField +4288 count, +4292 model handles, +4296 36-byte slots; per NPC record a model request
// (sub_316E00(major, minor)) -- {4, 0xFFFF} placeholders only in the schedule mode (0x7CE200 == 1, sub_316B40) --,
// slot +8 = the record index. Outside that mode the placeholders are filled from today's NPC schedule (sub_1B83F0 ->
// its list sub_1B85A0: entries whose flag +16 is -1 or clear, matched by resource id 0xC00 | (id & 0x3FF), model
// +2 / +4 -> slot kind 1, +4 = the entry) and from the social-link NPC lists (sub_1B8D60 / sub_1B8DB0: model +100 /
// +102 -> slot kind 2, +16 = the list index); 0x7CE2C0 = 1 when any schedule NPC was placed. Then the position records
// become type-8 scene resources at their matrices (sub_3B5E90, sub_3B78B0).
void sub_1E2E50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x001e2e50
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    sw(zero, gp, -18992);  // 0x7CE2C0
    if (s4 != 0) {
        // 0x001e2ea4
        charge(ctx, 5);
        sw(zero, s3, 0);
        jal(ctx, 0x1E2EA8u, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001e33cc
            charge(ctx, 16);
            a2 = s2 & 0xFFFF;
            a3 = s1 & 0xFFFF;
            t0 = dsll32(s0, 16);
            t0 = dsra32(t0, 16);
            a0 = addiu(sp, 0x90);
            a1 = 0x680000;
            a1 = addiu(a1, 16480);  // "field/pack/f%03d_%03d_%03d.FBN"
            jal(ctx, 0x1E33E8u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x90);
            a1 = addiu(sp, 0xEC);
            jal(ctx, 0x1E33F8u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s4 = v0;
            if (s4 != 0) {
                // 0x001e340c
                charge(ctx, 36);
                sw(s4, s3, 0);
                lw(s0, s4, 8);
                jal(ctx, 0x1E3414u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcCount);
                s0 = 0x960000;
                s0 = addiu(s0, 388);  // &0x960184
                lw(v0, s4, 8);
                a1 = sll(v0, 2);
                a0 = 1;
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x1E343Cu, v0.u());
                s1 = v0;
                jal(ctx, 0x1E3448u, gen::fn_K_Field_Get_001b9120);
                sw(s1, v0, f4::fld::kNpcModels);
                lw(v1, s4, 8);
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                a1 = sll(v0, 2);
                a0 = 1;
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x1E3470u, v0.u());
                s0 = v0;
                jal(ctx, 0x1E347Cu, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcSlots);
                s2 = addiu(s4, 24);
                s0 = 0;
                s3 = 0;
                for (;;) {
                    // 0x001e3584
                    charge(ctx, 4);
                    lw(v0, s4, 8);
                    v0 = sltu(s0, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e349c
                    charge(ctx, 4);
                    lhu(v1, s2, 4);
                    a0 = 4;
                    if (v1 == a0) {
                        // 0x001e34ac
                        charge(ctx, 4);
                        lhu(v0, s2, 6);
                        a1 = 0xFFFF;
                        if (v0 != a1) {
                            goto L_001e3528;
                        }
                        // 0x001e34bc
                        charge(ctx, 4);
                        lw(v1, gp, -19184);  // 0x7CE200
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x001e34cc
                            charge(ctx, 23);
                            a2 = 0x680000;
                            a2 = addiu(a2, 16448);  // "field/editor.RMD"
                            a3 = 0;
                            jal(ctx, 0x1E34D8u, gen::fn_sub_316B40_00316b40);
                            s1 = v0;
                            jal(ctx, 0x1E34E4u, gen::fn_K_Field_Get_001b9120);
                            v1 = sll(s3, 2);
                            lw(v0, v0, f4::fld::kNpcModels);
                            v0 = addu(v0, v1);
                            sw(s1, v0, 0);
                            jal(ctx, 0x1E34FCu, gen::fn_K_Field_Get_001b9120);
                            v1 = sll(s3, 3);
                            v1 = addu(v1, s3);
                            v1 = sll(v1, 2);
                            lw(v0, v0, f4::fld::kNpcSlots);
                            v0 = addu(v0, v1);
                            sw(s0, v0, 8);
                            s3 = addiu(s3, 1);
                        }
                        goto L_001e357c;
                    }
                L_001e3528:
                    charge(ctx, 21);
                    a0 = v1;
                    lhu(a1, s2, 6);
                    a2 = 0;
                    jal(ctx, 0x1E3534u, gen::fn_sub_316E00_00316e00);
                    s1 = v0;
                    jal(ctx, 0x1E3540u, gen::fn_K_Field_Get_001b9120);
                    v1 = sll(s3, 2);
                    lw(v0, v0, f4::fld::kNpcModels);
                    v0 = addu(v0, v1);
                    sw(s1, v0, 0);
                    jal(ctx, 0x1E3558u, gen::fn_K_Field_Get_001b9120);
                    v1 = sll(s3, 3);
                    v1 = addu(v1, s3);
                    v1 = sll(v1, 2);
                    lw(v0, v0, f4::fld::kNpcSlots);
                    v0 = addu(v0, v1);
                    sw(s0, v0, 8);
                    s3 = addiu(s3, 1);
                L_001e357c:
                    charge(ctx, 2);
                    s0 = addiu(s0, 1);
                    s2 = addiu(s2, 112);
                }
                // 0x001e3594
                charge(ctx, 3);
                lw(v0, gp, -19184);  // 0x7CE200
                if (v0 == 0) {
                    // 0x001e35a0
                    charge(ctx, 4);
                    jal(ctx, 0x1E35A0u, gen::fn_sub_1B83F0_001b83f0);
                    if (v0 != 0) {
                        // 0x001e35b0
                        charge(ctx, 7);
                        lw(a0, v0, 12);
                        jal(ctx, 0x1E35B4u, gen::fn_sub_1B85A0_001b85a0);
                        s0 = v0;
                        s6 = 0;
                        for (;;) {
                            // 0x001e3704
                            charge(ctx, 4);
                            lhu(v1, s0, 0);
                            v0 = 0xFFFF;
                            if (v1 == v0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001e35cc
                            charge(ctx, 4);
                            lw(a0, s0, 16);
                            v0 = si(-1);
                            if (a0 != v0) {
                                // 0x001e35dc
                                charge(ctx, 5);
                                jal(ctx, 0x1E35DCu, gen::fn_datGetFlag_0016f190);
                                v1 = 1;
                                if (v0 != v1) {
                                    goto L_001e35f0;
                                }
                                goto L_001e36fc;
                            }
                        L_001e35f0:
                            charge(ctx, 7);
                            a3 = addiu(s4, 24);
                            s1 = 0;
                            lw(a2, s4, 8);
                            a0 = 0xFFFF;
                            a1 = 4;
                            for (;;) {
                                // 0x001e36f0
                                charge(ctx, 3);
                                v0 = sltu(s1, a2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001e360c
                                charge(ctx, 3);
                                lhu(v0, a3, 4);
                                if (v0 == a1) {
                                    // 0x001e3618
                                    charge(ctx, 3);
                                    lhu(v0, a3, 6);
                                    if (v0 != a0) {
                                        goto L_001e36e8;
                                    }
                                    // 0x001e3624
                                    charge(ctx, 7);
                                    lhu(v1, a3, 8);
                                    lhu(v0, s0, 0);
                                    v0 = v0 & 0x3FF;
                                    v0 = v0 | 0xC00;
                                    v0 = v0 & 0xFFFF;
                                    if (v1 != v0) {
                                        goto L_001e36e8;
                                    }
                                    goto L_001e3640_64;
                                }
                            L_001e36e8:
                                charge(ctx, 2);
                                s1 = addiu(s1, 1);
                                a3 = addiu(a3, 112);
                            }
                        L_001e36fc:
                            charge(ctx, 2);
                            s6 = addiu(s6, 1);
                            s0 = addiu(s0, 32);
                        }
                    }
                    // 0x001e3714
                    charge(ctx, 3);
                    s1 = 0;
                    for (;;) {
                        // 0x001e3868
                        charge(ctx, 4);
                        lw(v0, gp, -19116);  // 0x7CE244
                        v0 = sltu(s1, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001e3720
                        charge(ctx, 9);
                        a0 = s1;
                        jal(ctx, 0x1E3724u, gen::fn_sub_1B8D60_001b8d60);
                        a0 = v0;
                        jal(ctx, 0x1E3730u, gen::fn_sub_1B8DB0_001b8db0);
                        s0 = v0;
                        if (s0 != 0) {
                            // 0x001e3744
                            charge(ctx, 7);
                            a3 = addiu(s4, 24);
                            s5 = 0;
                            lw(a2, s4, 8);
                            a0 = 0xFFFF;
                            a1 = 4;
                            for (;;) {
                                // 0x001e3858
                                charge(ctx, 3);
                                v0 = sltu(s5, a2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001e3760
                                charge(ctx, 3);
                                lhu(v0, a3, 4);
                                if (v0 == a1) {
                                    // 0x001e376c
                                    charge(ctx, 3);
                                    lhu(v0, a3, 6);
                                    if (v0 != a0) {
                                        goto L_001e3850;
                                    }
                                    // 0x001e3778
                                    charge(ctx, 7);
                                    lhu(v1, a3, 8);
                                    lhu(v0, s0, 0);
                                    v0 = v0 & 0x3FF;
                                    v0 = v0 | 0xC00;
                                    v0 = v0 & 0xFFFF;
                                    if (v1 != v0) {
                                        goto L_001e3850;
                                    }
                                    goto L_001e3794_77;
                                }
                            L_001e3850:
                                charge(ctx, 2);
                                s5 = addiu(s5, 1);
                                a3 = addiu(a3, 112);
                            }
                        }
                    L_001e3864:
                        charge(ctx, 1);
                        s1 = addiu(s1, 1);
                    }
                    // 0x001e3878
                    charge(ctx, 3);
                    jal(ctx, 0x1E3878u, gen::fn_K_Field_Get_001b9120);
                    sw(s3, v0, f4::fld::kNpcCount);
                }
                // 0x001e3884
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x001e38f0
                    charge(ctx, 4);
                    lw(v0, s4, 16);
                    v0 = sltu(s0, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e3890
                    charge(ctx, 24);
                    lhu(v0, s2, 80);
                    a0 = v0 & 0x3FF;
                    jal(ctx, 0x1E3898u, gen::fn_sub_3B5E90_003b5e90);
                    s1 = v0 & 0xFFFF;
                    a0 = addiu(s2, 16);
                    jal(ctx, 0x1E38A8u, gen::fn_sub_1A5B30_001a5b30);
                    swc1(f0, sp, 0xD0);
                    a0 = addiu(s2, 16);
                    jal(ctx, 0x1E38B8u, gen::fn_sub_1A5AA0_001a5aa0);
                    swc1(f0, sp, 0xD4);
                    a0 = addiu(s2, 16);
                    jal(ctx, 0x1E38C8u, gen::fn_sub_1A5BC0_001a5bc0);
                    swc1(f0, sp, 0xD8);
                    a0 = s1;
                    a1 = addiu(s2, 64);
                    a2 = addiu(sp, 0xD0);
                    jal(ctx, 0x1E38E0u, gen::fn_sub_3B78B0_003b78b0);
                    s0 = addiu(s0, 1);
                    s2 = addiu(s2, 96);
                }
            }
            // 0x001e3900
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001e2eb8
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x1E2EBCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001e390c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001e2ecc
                charge(ctx, 36);
                lw(s1, s4, 272);
                lw(s0, s1, 8);
                jal(ctx, 0x1E2ED4u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcCount);
                s0 = 0x960000;
                s0 = addiu(s0, 388);  // &0x960184
                lw(v0, s1, 8);
                a1 = sll(v0, 2);
                a0 = 1;
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x1E2EFCu, v0.u());
                s2 = v0;
                jal(ctx, 0x1E2F08u, gen::fn_K_Field_Get_001b9120);
                sw(s2, v0, f4::fld::kNpcModels);
                lw(v1, s1, 8);
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                a1 = sll(v0, 2);
                a0 = 1;
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x1E2F30u, v0.u());
                s0 = v0;
                jal(ctx, 0x1E2F3Cu, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcSlots);
                s3 = addiu(s1, 24);
                s0 = 0;
                s4 = 0;
                for (;;) {
                    // 0x001e3044
                    charge(ctx, 4);
                    lw(v0, s1, 8);
                    v0 = sltu(s0, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e2f5c
                    charge(ctx, 4);
                    lhu(v1, s3, 4);
                    a0 = 4;
                    if (v1 == a0) {
                        // 0x001e2f6c
                        charge(ctx, 4);
                        lhu(v0, s3, 6);
                        a1 = 0xFFFF;
                        if (v0 != a1) {
                            goto L_001e2fe8;
                        }
                        // 0x001e2f7c
                        charge(ctx, 4);
                        lw(v1, gp, -19184);  // 0x7CE200
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x001e2f8c
                            charge(ctx, 23);
                            a2 = 0x680000;
                            a2 = addiu(a2, 16448);  // "field/editor.RMD"
                            a3 = 0;
                            jal(ctx, 0x1E2F98u, gen::fn_sub_316B40_00316b40);
                            s2 = v0;
                            jal(ctx, 0x1E2FA4u, gen::fn_K_Field_Get_001b9120);
                            v1 = sll(s4, 2);
                            lw(v0, v0, f4::fld::kNpcModels);
                            v0 = addu(v0, v1);
                            sw(s2, v0, 0);
                            jal(ctx, 0x1E2FBCu, gen::fn_K_Field_Get_001b9120);
                            v1 = sll(s4, 3);
                            v1 = addu(v1, s4);
                            v1 = sll(v1, 2);
                            lw(v0, v0, f4::fld::kNpcSlots);
                            v0 = addu(v0, v1);
                            sw(s0, v0, 8);
                            s4 = addiu(s4, 1);
                        }
                        goto L_001e303c;
                    }
                L_001e2fe8:
                    charge(ctx, 21);
                    a0 = v1;
                    lhu(a1, s3, 6);
                    a2 = 0;
                    jal(ctx, 0x1E2FF4u, gen::fn_sub_316E00_00316e00);
                    s2 = v0;
                    jal(ctx, 0x1E3000u, gen::fn_K_Field_Get_001b9120);
                    v1 = sll(s4, 2);
                    lw(v0, v0, f4::fld::kNpcModels);
                    v0 = addu(v0, v1);
                    sw(s2, v0, 0);
                    jal(ctx, 0x1E3018u, gen::fn_K_Field_Get_001b9120);
                    v1 = sll(s4, 3);
                    v1 = addu(v1, s4);
                    v1 = sll(v1, 2);
                    lw(v0, v0, f4::fld::kNpcSlots);
                    v0 = addu(v0, v1);
                    sw(s0, v0, 8);
                    s4 = addiu(s4, 1);
                L_001e303c:
                    charge(ctx, 2);
                    s0 = addiu(s0, 1);
                    s3 = addiu(s3, 112);
                }
                // 0x001e3054
                charge(ctx, 3);
                lw(v0, gp, -19184);  // 0x7CE200
                if (v0 == 0) {
                    // 0x001e3060
                    charge(ctx, 4);
                    jal(ctx, 0x1E3060u, gen::fn_sub_1B83F0_001b83f0);
                    if (v0 != 0) {
                        // 0x001e3070
                        charge(ctx, 7);
                        lw(a0, v0, 12);
                        jal(ctx, 0x1E3074u, gen::fn_sub_1B85A0_001b85a0);
                        s0 = v0;
                        s6 = 0;
                        for (;;) {
                            // 0x001e31c4
                            charge(ctx, 4);
                            lhu(v1, s0, 0);
                            v0 = 0xFFFF;
                            if (v1 == v0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001e308c
                            charge(ctx, 4);
                            lw(a0, s0, 16);
                            v0 = si(-1);
                            if (a0 != v0) {
                                // 0x001e309c
                                charge(ctx, 5);
                                jal(ctx, 0x1E309Cu, gen::fn_datGetFlag_0016f190);
                                v1 = 1;
                                if (v0 != v1) {
                                    goto L_001e30b0;
                                }
                                goto L_001e31bc;
                            }
                        L_001e30b0:
                            charge(ctx, 7);
                            a3 = addiu(s1, 24);
                            s2 = 0;
                            lw(a2, s1, 8);
                            a0 = 0xFFFF;
                            a1 = 4;
                            for (;;) {
                                // 0x001e31b0
                                charge(ctx, 3);
                                v0 = sltu(s2, a2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001e30cc
                                charge(ctx, 3);
                                lhu(v0, a3, 4);
                                if (v0 == a1) {
                                    // 0x001e30d8
                                    charge(ctx, 3);
                                    lhu(v0, a3, 6);
                                    if (v0 != a0) {
                                        goto L_001e31a8;
                                    }
                                    // 0x001e30e4
                                    charge(ctx, 7);
                                    lhu(v1, a3, 8);
                                    lhu(v0, s0, 0);
                                    v0 = v0 & 0x3FF;
                                    v0 = v0 | 0xC00;
                                    v0 = v0 & 0xFFFF;
                                    if (v1 != v0) {
                                        goto L_001e31a8;
                                    }
                                    goto L_001e3100_21;
                                }
                            L_001e31a8:
                                charge(ctx, 2);
                                s2 = addiu(s2, 1);
                                a3 = addiu(a3, 112);
                            }
                        L_001e31bc:
                            charge(ctx, 2);
                            s6 = addiu(s6, 1);
                            s0 = addiu(s0, 32);
                        }
                    }
                    // 0x001e31d4
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x001e3328
                        charge(ctx, 4);
                        lw(v0, gp, -19116);  // 0x7CE244
                        v0 = sltu(s2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001e31e0
                        charge(ctx, 9);
                        a0 = s2;
                        jal(ctx, 0x1E31E4u, gen::fn_sub_1B8D60_001b8d60);
                        a0 = v0;
                        jal(ctx, 0x1E31F0u, gen::fn_sub_1B8DB0_001b8db0);
                        s0 = v0;
                        if (s0 != 0) {
                            // 0x001e3204
                            charge(ctx, 7);
                            a3 = addiu(s1, 24);
                            s5 = 0;
                            lw(a2, s1, 8);
                            a0 = 0xFFFF;
                            a1 = 4;
                            for (;;) {
                                // 0x001e3318
                                charge(ctx, 3);
                                v0 = sltu(s5, a2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001e3220
                                charge(ctx, 3);
                                lhu(v0, a3, 4);
                                if (v0 == a1) {
                                    // 0x001e322c
                                    charge(ctx, 3);
                                    lhu(v0, a3, 6);
                                    if (v0 != a0) {
                                        goto L_001e3310;
                                    }
                                    // 0x001e3238
                                    charge(ctx, 7);
                                    lhu(v1, a3, 8);
                                    lhu(v0, s0, 0);
                                    v0 = v0 & 0x3FF;
                                    v0 = v0 | 0xC00;
                                    v0 = v0 & 0xFFFF;
                                    if (v1 != v0) {
                                        goto L_001e3310;
                                    }
                                    goto L_001e3254_34;
                                }
                            L_001e3310:
                                charge(ctx, 2);
                                s5 = addiu(s5, 1);
                                a3 = addiu(a3, 112);
                            }
                        }
                    L_001e3324:
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x001e3338
                    charge(ctx, 3);
                    jal(ctx, 0x1E3338u, gen::fn_K_Field_Get_001b9120);
                    sw(s4, v0, f4::fld::kNpcCount);
                }
                // 0x001e3344
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x001e33b0
                    charge(ctx, 4);
                    lw(v0, s1, 16);
                    v0 = sltu(s0, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e3350
                    charge(ctx, 24);
                    lhu(v0, s3, 80);
                    a0 = v0 & 0x3FF;
                    jal(ctx, 0x1E3358u, gen::fn_sub_3B5E90_003b5e90);
                    s2 = v0 & 0xFFFF;
                    a0 = addiu(s3, 16);
                    jal(ctx, 0x1E3368u, gen::fn_sub_1A5B30_001a5b30);
                    swc1(f0, sp, 0xE0);
                    a0 = addiu(s3, 16);
                    jal(ctx, 0x1E3378u, gen::fn_sub_1A5AA0_001a5aa0);
                    swc1(f0, sp, 0xE4);
                    a0 = addiu(s3, 16);
                    jal(ctx, 0x1E3388u, gen::fn_sub_1A5BC0_001a5bc0);
                    swc1(f0, sp, 0xE8);
                    a0 = s2;
                    a1 = addiu(s3, 64);
                    a2 = addiu(sp, 0xE0);
                    jal(ctx, 0x1E33A0u, gen::fn_sub_3B78B0_003b78b0);
                    s0 = addiu(s0, 1);
                    s3 = addiu(s3, 96);
                }
                // 0x001e33c0
                charge(ctx, 3);
                v0 = 1;
            }
        }
    } else {
        // 0x001e2e98
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001e3910 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xF0);
    return;
L_001e3100_21:
    charge(ctx, 3);
    lhu(v0, s0, 2);
    if (v0 == 0) {
        // 0x001e310c
        charge(ctx, 3);
        lhu(v0, s0, 4);
        if (v0 != 0) {
            goto L_001e3118;
        }
        goto L_001e31bc;
    }
L_001e3118:
    charge(ctx, 36);
    v0 = 1;
    sw(v0, gp, -18992);  // 0x7CE2C0
    lhu(a0, s0, 2);
    lhu(a1, s0, 4);
    a2 = 0;
    jal(ctx, 0x1E312Cu, gen::fn_sub_316E00_00316e00);
    s5 = v0;
    jal(ctx, 0x1E3138u, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s4, 2);
    lw(v0, v0, f4::fld::kNpcModels);
    v0 = addu(v0, v1);
    sw(s5, v0, 0);
    v0 = sll(s4, 3);
    v0 = addu(v0, s4);
    s5 = sll(v0, 2);
    s7 = 1;
    jal(ctx, 0x1E3160u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s5);
    sw(s7, v0, 0);
    jal(ctx, 0x1E3174u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s5);
    sw(s0, v0, 4);
    jal(ctx, 0x1E3188u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s5);
    sw(s2, v0, 8);
    s4 = addiu(s4, 1);
    goto L_001e31bc;
L_001e3254_34:
    charge(ctx, 3);
    lhu(v0, s0, 100);
    if (v0 == 0) {
        // 0x001e3260
        charge(ctx, 3);
        lhu(v0, s0, 102);
        if (v0 != 0) {
            goto L_001e326c;
        }
        goto L_001e3324;
    }
L_001e326c:
    charge(ctx, 41);
    v0 = 1;
    sw(v0, gp, -18992);  // 0x7CE2C0
    lhu(a0, s0, 100);
    lhu(a1, s0, 102);
    a2 = 0;
    jal(ctx, 0x1E3280u, gen::fn_sub_316E00_00316e00);
    s6 = v0;
    jal(ctx, 0x1E328Cu, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s4, 2);
    lw(v0, v0, f4::fld::kNpcModels);
    v0 = addu(v0, v1);
    sw(s6, v0, 0);
    v0 = sll(s4, 3);
    v0 = addu(v0, s4);
    s6 = sll(v0, 2);
    s7 = 2;
    jal(ctx, 0x1E32B4u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s7, v0, 0);
    jal(ctx, 0x1E32C8u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s0, v0, 4);
    jal(ctx, 0x1E32DCu, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s5, v0, 8);
    jal(ctx, 0x1E32F0u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s2, v0, 16);
    s4 = addiu(s4, 1);
    goto L_001e3324;
L_001e3640_64:
    charge(ctx, 3);
    lhu(v0, s0, 2);
    if (v0 == 0) {
        // 0x001e364c
        charge(ctx, 3);
        lhu(v0, s0, 4);
        if (v0 != 0) {
            goto L_001e3658;
        }
        goto L_001e36fc;
    }
L_001e3658:
    charge(ctx, 36);
    v0 = 1;
    sw(v0, gp, -18992);  // 0x7CE2C0
    lhu(a0, s0, 2);
    lhu(a1, s0, 4);
    a2 = 0;
    jal(ctx, 0x1E366Cu, gen::fn_sub_316E00_00316e00);
    s5 = v0;
    jal(ctx, 0x1E3678u, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s3, 2);
    lw(v0, v0, f4::fld::kNpcModels);
    v0 = addu(v0, v1);
    sw(s5, v0, 0);
    v0 = sll(s3, 3);
    v0 = addu(v0, s3);
    s5 = sll(v0, 2);
    s7 = 1;
    jal(ctx, 0x1E36A0u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s5);
    sw(s7, v0, 0);
    jal(ctx, 0x1E36B4u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s5);
    sw(s0, v0, 4);
    jal(ctx, 0x1E36C8u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s5);
    sw(s1, v0, 8);
    s3 = addiu(s3, 1);
    goto L_001e36fc;
L_001e3794_77:
    charge(ctx, 3);
    lhu(v0, s0, 100);
    if (v0 == 0) {
        // 0x001e37a0
        charge(ctx, 3);
        lhu(v0, s0, 102);
        if (v0 != 0) {
            goto L_001e37ac;
        }
        goto L_001e3864;
    }
L_001e37ac:
    charge(ctx, 41);
    v0 = 1;
    sw(v0, gp, -18992);  // 0x7CE2C0
    lhu(a0, s0, 100);
    lhu(a1, s0, 102);
    a2 = 0;
    jal(ctx, 0x1E37C0u, gen::fn_sub_316E00_00316e00);
    s6 = v0;
    jal(ctx, 0x1E37CCu, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s3, 2);
    lw(v0, v0, f4::fld::kNpcModels);
    v0 = addu(v0, v1);
    sw(s6, v0, 0);
    v0 = sll(s3, 3);
    v0 = addu(v0, s3);
    s6 = sll(v0, 2);
    s7 = 2;
    jal(ctx, 0x1E37F4u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s7, v0, 0);
    jal(ctx, 0x1E3808u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s0, v0, 4);
    jal(ctx, 0x1E381Cu, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s5, v0, 8);
    jal(ctx, 0x1E3830u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcSlots);
    v0 = addu(v0, s6);
    sw(s1, v0, 16);
    s3 = addiu(s3, 1);
    goto L_001e3864;
}

// 0x001E3940 sub_1E3940 [K_Fldrc_PlaceFbnNpcs] -- 1476 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E3940(request, data) -> 1 when the FBN's NPCs are placed (0 while their models load; 1 at once for no file):
// waits for every slot's model and the base model (sub_1B7E30); per slot the NPC record (data + 24 + size * slot
// +8): a type-3 scene resource with id & 0x3FF, kind +96 (v1.1+, else 3) and the model (sub_3B6270), drawn
// (sub_1A0DC0), the model matrix = the record's, the resource placed at the matrix (sub_3B78B0), the collision radius
// (record +12) set on its controller (+488), the shadow (+496) set, a shadow model cloned from the base model scaled
// by +12 (+492), +40 bit 31 = record +11 bit 0, +480 / +484 / +482 from the record; kind 1 (schedule): +504 the
// entry, its scale +20 and pose +6; kind 2 (social link): +508 the entry, pose +104 and, with a link id +116 != 255,
// a field icon (sub_1DD460) showing 2 (flag 2304 + id) / 1 (flag 2368 + id) / 3; the slot blocks freed (sub_1B8CF0).
// Then the slot arrays are freed, "CAUTION!! READ OLD VER FBN DATA" for v1.0 files, and the request destroyed.
void sub_1E3940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x001e3940
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
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
    s7 = a0;
    s4 = a1;
    if (s7 != 0) {
        // 0x001e3988
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x001e39cc
            charge(ctx, 6);
            jal(ctx, 0x1E39CCu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kNpcCount);
            v0 = sltu(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001e3994
            charge(ctx, 10);
            jal(ctx, 0x1E3994u, gen::fn_K_Field_Get_001b9120);
            v1 = sll(s0, 2);
            lw(v0, v0, f4::fld::kNpcModels);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x1E39ACu, gen::fn_sub_316F70_00316f70);
            if (v0 == 0) {
                goto L_001e39bc_4;
            }
            // 0x001e39c8
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x001e39e4
        charge(ctx, 4);
        jal(ctx, 0x1E39E4u, gen::fn_sub_1B7E30_001b7e30);
        if (v0 != 0) {
            // 0x001e3a00
            charge(ctx, 4);
            jal(ctx, 0x1E3A00u, gen::fn_sub_1B0910_001b0910);
            if (v0 == 0) {
                // 0x001e3a10
                charge(ctx, 3);
                lw(s4, s7, 272);
                goto L_001e3a38;
            }
            // 0x001e3a1c
            charge(ctx, 2);
            if (s4 == 0) {
                // 0x001e3a2c
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x001e3a24
                charge(ctx, 2);
            L_001e3a38:
                charge(ctx, 4);
                fp = addiu(s4, 0x18);
                s3 = 0;
                for (;;) {
                    // 0x001e3e14
                    charge(ctx, 6);
                    jal(ctx, 0x1E3E14u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kNpcCount);
                    v0 = sltu(s3, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e3a48
                    charge(ctx, 24);
                    s0 = 3;
                    v0 = 0x680000;
                    ld(v1, v0, 16512);  // 0x684080
                    v0 = 0x680000;
                    lwc1(f0, v0, 16520);  // 0x684088
                    sd(v1, sp, 0xC0);
                    swc1(f0, sp, 0xC8);
                    v0 = sll(s3, 3);
                    v0 = addu(v0, s3);
                    s2 = sll(v0, 2);
                    jal(ctx, 0x1E3A70u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kNpcSlots);
                    v0 = addu(v0, s2);
                    lw(v1, v0, 8);
                    lw(v0, s4, 12);
                    mult(v0, v0, v1);
                    s1 = addu(fp, v0);
                    lw(v0, s4, 4);
                    at = 0x10000;
                    at = at | 0x1;
                    at = sltu(v0, at);
                    if (at == 0) {
                        // 0x001e3aa8
                        charge(ctx, 1);
                        lbu(s0, s1, 96);
                    }
                    // 0x001e3aac
                    charge(ctx, 29);
                    s6 = sll(s3, 2);
                    jal(ctx, 0x1E3AB0u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kNpcModels);
                    v1 = addu(v0, s6);
                    lhu(v0, s1, 8);
                    a0 = v0 & 0x3FF;
                    a1 = s0 & 0xFF;
                    lw(a2, v1, 0);
                    jal(ctx, 0x1E3AD0u, gen::fn_sub_3B6270_003b6270);
                    s5 = v0 & 0xFFFF;
                    a0 = s5;
                    a1 = 1;
                    jal(ctx, 0x1E3AE4u, gen::fn_sub_1A0DC0_001a0dc0);
                    a0 = s5;
                    jal(ctx, 0x1E3AF0u, gen::fn_sub_3B5D10_003b5d10);
                    s0 = v0;
                    jal(ctx, 0x1E3AFCu, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kNpcModels);
                    v0 = addu(v0, s6);
                    lw(a0, v0, 0);
                    jal(ctx, 0x1E3B10u, gen::fn_sub_318B60_00318b60);
                    a2 = addiu(s1, 32);
                    a1 = 8;
                    for (;;) {
                        // 0x001e3b20
                        charge(ctx, 9);
                        lw(a0, a2, 0);
                        lw(v1, a2, 4);
                        a2 = addiu(a2, 8);
                        a1 = addiu(a1, -1);
                        sw(a0, v0, 0);
                        sw(v1, v0, 4);
                        v0 = addiu(v0, 8);
                        if (i64(a1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x001e3b44
                    charge(ctx, 66);
                    a0 = addiu(s1, 32);
                    jal(ctx, 0x1E3B48u, gen::fn_sub_1A5B30_001a5b30);
                    swc1(f0, sp, 0xD0);
                    a0 = addiu(s1, 32);
                    jal(ctx, 0x1E3B58u, gen::fn_sub_1A5AA0_001a5aa0);
                    swc1(f0, sp, 0xD4);
                    a0 = addiu(s1, 32);
                    jal(ctx, 0x1E3B68u, gen::fn_sub_1A5BC0_001a5bc0);
                    swc1(f0, sp, 0xD8);
                    a0 = s5;
                    a1 = addiu(s1, 80);
                    a2 = addiu(sp, 0xD0);
                    jal(ctx, 0x1E3B80u, gen::fn_sub_3B78B0_003b78b0);
                    jal(ctx, 0x1E3B88u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kNpcModels);
                    v0 = addu(v0, s6);
                    lw(a0, v0, 0);
                    jal(ctx, 0x1E3B9Cu, gen::fn_sub_318B60_00318b60);
                    a0 = v0;
                    jal(ctx, 0x1E3BA8u, gen::fn_sub_4C2F10_004c2f10);
                    lw(a0, s0, 488);
                    lwc1(f12, s1, 12);
                    jal(ctx, 0x1E3BB8u, gen::fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0);
                    lw(a0, s0, 496);
                    lwc1(f12, s1, 100);
                    jal(ctx, 0x1E3BC8u, gen::fn_sub_19C320_0019c320);
                    lwc1(f0, s1, 12);
                    swc1(f0, sp, 0xB0);
                    swc1(f0, sp, 0xB4);
                    swc1(f0, sp, 0xB8);
                    lw(a0, gp, -19156);  // 0x7CE21C
                    jal(ctx, 0x1E3BE4u, gen::fn_sub_317450_00317450);
                    sw(v0, s0, 492);
                    a0 = v0;
                    a1 = addiu(sp, 0xC0);
                    lwc1(f12, sp, 0xD4);
                    a2 = 2;
                    jal(ctx, 0x1E3C00u, gen::fn_sub_318A50_00318a50);
                    lw(a0, s0, 492);
                    a1 = addiu(sp, 0xB0);
                    a2 = 2;
                    jal(ctx, 0x1E3C14u, gen::fn_sub_318A90_00318a90);
                    lw(a0, s0, 492);
                    a1 = addiu(s1, 80);
                    a2 = 2;
                    jal(ctx, 0x1E3C28u, gen::fn_sub_318A30_00318a30);
                    lw(a0, s0, 492);
                    jal(ctx, 0x1E3C34u, gen::fn_sub_317730_00317730);
                    lbu(v0, s1, 11);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x001e3c64
                        charge(ctx, 4);
                        lw(v0, s0, 40);
                        v0 = dsll32(v0, 1);
                        v0 = dsrl32(v0, 1);
                        sw(v0, s0, 40);
                    } else {
                        // 0x001e3c4c
                        charge(ctx, 6);
                        lw(v1, s0, 40);
                        v0 = lui(0x8000);
                        v0 = v1 | v0;
                        sw(v0, s0, 40);
                    }
                    // 0x001e3c74
                    charge(ctx, 15);
                    lbu(v0, s1, 10);
                    sh(v0, s0, 480);
                    lw(v0, s1, 16);
                    sw(v0, s0, 484);
                    lbu(v0, s1, 97);
                    sb(v0, s0, 482);
                    jal(ctx, 0x1E3C8Cu, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kNpcSlots);
                    v0 = addu(v0, s2);
                    lw(v1, v0, 0);
                    sw(v1, s0, 500);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x001e3d28
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x001e3d34
                            charge(ctx, 18);
                            jal(ctx, 0x1E3D34u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kNpcSlots);
                            v0 = addu(v0, s2);
                            lw(v0, v0, 4);
                            sw(v0, s0, 508);
                            lh(a2, v0, 104);
                            lw(a0, s0, 296);
                            a1 = 0;
                            a3 = 8;
                            t0 = 1;
                            jal(ctx, 0x1E3D60u, gen::fn_sub_3182D0_003182d0);
                            lw(v0, s0, 508);
                            lw(v1, v0, 116);
                            v0 = 255;
                            if (v1 != v0) {
                                // 0x001e3d7c
                                charge(ctx, 6);
                                s1 = 3;
                                a0 = addiu(v1, 2304);
                                jal(ctx, 0x1E3D84u, gen::fn_datGetFlag_0016f190);
                                if (v0 == 0) {
                                    // 0x001e3da0
                                    charge(ctx, 7);
                                    lw(v0, s0, 508);
                                    lw(v0, v0, 116);
                                    a0 = addiu(v0, 2368);
                                    jal(ctx, 0x1E3DACu, gen::fn_datGetFlag_0016f190);
                                    if (v0 != 0) {
                                        // 0x001e3dbc
                                        charge(ctx, 1);
                                        s1 = 1;
                                    }
                                } else {
                                    // 0x001e3d94
                                    charge(ctx, 3);
                                    s1 = 2;
                                }
                                // 0x001e3dc0
                                charge(ctx, 14);
                                lw(a0, s0, 488);
                                a1 = s1;
                                a2 = 4184;
                                jal(ctx, 0x1E3DCCu, gen::fn_sub_1DD460_001dd460);
                                sw(v0, s0, 528);
                                a0 = v0;
                                lw(a1, s0, 296);
                                jal(ctx, 0x1E3DE0u, gen::fn_sub_1DD5F0_001dd5f0);
                                lw(a0, s0, 528);
                                a1 = 1;
                                jal(ctx, 0x1E3DF0u, gen::fn_sub_1DD5E0_001dd5e0);
                            }
                            // 0x001e3df8
                            charge(ctx, 6);
                            jal(ctx, 0x1E3DF8u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kNpcSlots);
                            a0 = addu(v0, s2);
                            jal(ctx, 0x1E3E08u, gen::fn_sub_1B8CF0_001b8cf0);
                        }
                    } else {
                        // 0x001e3cb0
                        charge(ctx, 12);
                        jal(ctx, 0x1E3CB0u, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kNpcSlots);
                        v0 = addu(v0, s2);
                        lw(v0, v0, 4);
                        sw(v0, s0, 504);
                        lwc1(f1, v0, 20);
                        mtc1(zero, f0);
                        c_eq_s(f0, f1);
                        if (!cond(ctx)) {
                            // 0x001e3ce0
                            charge(ctx, 8);
                            swc1(f1, sp, 0xA8);
                            swc1(f1, sp, 0xA4);
                            swc1(f1, sp, 0xA0);
                            lw(a0, s0, 296);
                            a1 = addiu(sp, 0xA0);
                            a2 = 1;
                            jal(ctx, 0x1E3CF8u, gen::fn_sub_318A90_00318a90);
                        }
                        // 0x001e3d00
                        charge(ctx, 10);
                        lw(v0, s0, 504);
                        lh(a2, v0, 6);
                        lw(a0, s0, 296);
                        a1 = 0;
                        a3 = 8;
                        t0 = 1;
                        jal(ctx, 0x1E3D18u, gen::fn_sub_3182D0_003182d0);
                    }
                    // 0x001e3e10
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x001e3e2c
                charge(ctx, 20);
                s0 = 0x960000;
                s0 = addiu(s0, 380);  // &0x96017C
                jal(ctx, 0x1E3E34u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kNpcModels);
                lw(v0, s0, 0);  // 0x96017C
                jalr(ctx, 0x1E3E44u, v0.u());
                jal(ctx, 0x1E3E4Cu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kNpcSlots);
                lw(v0, s0, 0);  // 0x96017C
                jalr(ctx, 0x1E3E5Cu, v0.u());
                lw(v0, s4, 4);
                at = 0x10000;
                at = at | 0x1;
                at = sltu(v0, at);
                if (at != 0) {
                    // 0x001e3e7c
                    charge(ctx, 7);
                    a0 = 0;
                    a1 = 0;
                    a2 = 388;
                    a3 = 0x680000;
                    a3 = addiu(a3, 16528);  // "CAUTION!! READ OLD VER FBN DATA"
                    jal(ctx, 0x1E3E90u, gen::fn_sub_1A1540_001a1540);
                }
                // 0x001e3e98
                charge(ctx, 10);
                jal(ctx, 0x1E3E98u, gen::fn_K_Field_Get_001b9120);
                sw(zero, v0, f4::fld::kNpcCount);
                jal(ctx, 0x1E3EA4u, gen::fn_K_Field_Get_001b9120);
                sw(zero, v0, f4::fld::kNpcModels);
                jal(ctx, 0x1E3EB0u, gen::fn_sub_1B0910_001b0910);
                if (v0 == 0) {
                    // 0x001e3ec0
                    charge(ctx, 3);
                    a0 = s7;
                    jal(ctx, 0x1E3EC4u, gen::fn_H_Cdvd_Destroy_00100ec0);
                }
                // 0x001e3ecc
                charge(ctx, 1);
                v0 = 1;
            }
        } else {
            // 0x001e39f4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001e397c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001e3ed0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
    return;
L_001e39bc_4:
    charge(ctx, 3);
    v0 = 0;
    // 0x001e3ed0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
}

// 0x001E3F10 sub_1E3F10 [K_FieldEditor_CreateNpcUpdate] -- 3072 bytes; frame 0x120: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E3F10(task) -> 0, or -1 to be destroyed: the editor's "create Npc" mode (48-byte work: +4 the menu, +16 / +18
// the model ids, +20 the resource id, +22 the controller byte, +23 the flags, +24 the radius, +28 +484, +32 the
// kind, +33 +97, +36 the shadow size, +40 the model, +44 the controller): STATIC (a model by major / minor from the
// 8-field form 0x684120) or VIRTUAL (the placeholder "field/editor.RMD" {4, 0xFFFF}, radius 30, kind 3, shadow 60);
// "already exist resource ID" when the id is taken (sub_1E2810); state 4 creates the resource 1000 units in front of
// the camera; state 5 drives it with the sticks like the player (K_FldFrame_CtlMoveInDir, the rotate sub_1ADFF0, up /
// down 10, R3 snaps to the ground sub_1AE0D0) and circle stores it as a new NPC record (sub_1E2850), triangle
// deletes it; triangle in the menus -> 6 (-1).
void sub_1E3F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001e3f10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s2, a0, f4::kTaskWork);
    lw(v0, s2, 0);
    at = sltiu(v0, 7);
    if (at != 0) {
        // 0x001e3f3c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 28048);  // &0x7B6D90
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1E3F58u:  // table[0]
            // 0x001e3f58
            charge(ctx, 23);
            a1 = 290;
            a2 = 220;
            a3 = 2;
            jal(ctx, 0x1E3F64u, gen::fn_sub_1A3B10_001a3b10);
            sw(v0, s2, 4);
            a0 = v0;
            a1 = addiu(gp, -27096);  // "STATIC"
            jal(ctx, 0x1E3F78u, gen::fn_sub_1A3F20_001a3f20);
            lw(a0, s2, 4);
            a1 = addiu(gp, -27088);  // "VIRTUAL"
            jal(ctx, 0x1E3F88u, gen::fn_sub_1A3F20_001a3f20);
            lw(a0, s2, 4);
            a1 = 1;
            jal(ctx, 0x1E3F98u, gen::fn_sub_1A3BF0_001a3bf0);
            lw(v0, s2, 0);
            v0 = addiu(v0, 1);
            sw(v0, s2, 0);
        L_001e4af0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1E3FB4u:  // table[1]
            // 0x001e3fb4
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e40b0
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e40bc
                    charge(ctx, 4);
                    v0 = 6;
                    sw(v0, s2, 0);
                }
            } else {
                // 0x001e3fc8
                charge(ctx, 6);
                lw(a0, s2, 4);
                jal(ctx, 0x1E3FCCu, gen::fn_sub_1A4510_001a4510);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001e4050
                    charge(ctx, 24);
                    lw(a0, s2, 4);
                    jal(ctx, 0x1E4054u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    a0 = s1;
                    a1 = 32;
                    a2 = a1;
                    a3 = 2;
                    jal(ctx, 0x1E406Cu, gen::fn_sub_1A3B10_001a3b10);
                    sw(v0, s2, 4);
                    a0 = v0;
                    a1 = 0x680000;
                    a1 = addiu(a1, 16928);  // &0x684220
                    a2 = 2;
                    jal(ctx, 0x1E4088u, gen::fn_sub_1A3DC0_001a3dc0);
                    lw(a0, s2, 4);
                    a1 = 1;
                    jal(ctx, 0x1E4098u, gen::fn_sub_1A3BF0_001a3bf0);
                    v0 = 3;
                    sw(v0, s2, 0);
                } else {
                    // 0x001e3fe0
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001e3ff0
                        charge(ctx, 24);
                        lw(a0, s2, 4);
                        jal(ctx, 0x1E3FF4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        a0 = s1;
                        a1 = 32;
                        a2 = a1;
                        a3 = 2;
                        jal(ctx, 0x1E400Cu, gen::fn_sub_1A3B10_001a3b10);
                        sw(v0, s2, 4);
                        a0 = v0;
                        a1 = 0x680000;
                        a1 = addiu(a1, 16672);  // &0x684120
                        a2 = 8;
                        jal(ctx, 0x1E4028u, gen::fn_sub_1A3DC0_001a3dc0);
                        lw(a0, s2, 4);
                        a1 = 1;
                        jal(ctx, 0x1E4038u, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 2;
                        sw(v0, s2, 0);
                    } else {
                        // 0x001e3fe8
                        charge(ctx, 2);
                    }
                }
            }
            goto L_001e4af0;
        case 0x1E40CCu:  // table[2]
            // 0x001e40cc
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e4244
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e4250
                    charge(ctx, 4);
                    v0 = 6;
                    sw(v0, s2, 0);
                }
            } else {
                // 0x001e40e0
                charge(ctx, 6);
                lw(a0, s2, 4);
                jal(ctx, 0x1E40E4u, gen::fn_sub_1A4510_001a4510);
                v1 = 7;
                if (v0 == v1) {
                    // 0x001e4100
                    charge(ctx, 46);
                    lw(a0, s2, 4);
                    a1 = 0;
                    jal(ctx, 0x1E4108u, gen::fn_sub_1A41B0_001a41b0);
                    lhu(s0, v0, 0);
                    lw(a0, s2, 4);
                    a1 = 1;
                    jal(ctx, 0x1E411Cu, gen::fn_sub_1A41B0_001a41b0);
                    lw(v0, v0, 0);
                    sh(v0, s2, 16);
                    lw(a0, s2, 4);
                    a1 = 2;
                    jal(ctx, 0x1E4134u, gen::fn_sub_1A41B0_001a41b0);
                    lw(v0, v0, 0);
                    sh(v0, s2, 18);
                    lw(a0, s2, 4);
                    a1 = 4;
                    jal(ctx, 0x1E414Cu, gen::fn_sub_1A41B0_001a41b0);
                    lwc1(f0, v0, 0);
                    cvt_s_w(f0, f0);
                    swc1(f0, s2, 24);
                    lw(a0, s2, 4);
                    a1 = 5;
                    jal(ctx, 0x1E4168u, gen::fn_sub_1A41B0_001a41b0);
                    lw(v0, v0, 0);
                    sb(v0, s2, 32);
                    lw(a0, s2, 4);
                    a1 = 6;
                    jal(ctx, 0x1E4180u, gen::fn_sub_1A41B0_001a41b0);
                    lwc1(f0, v0, 0);
                    cvt_s_w(f0, f0);
                    swc1(f0, s2, 36);
                    sb(zero, s2, 33);
                    lw(a0, s2, 4);
                    a1 = 3;
                    jal(ctx, 0x1E41A0u, gen::fn_sub_1A41B0_001a41b0);
                    lw(v1, v0, 0);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x001e41cc
                        charge(ctx, 3);
                        lbu(v0, s2, 23);
                        v0 = v0 & 0xFE;
                        sb(v0, s2, 23);
                    } else {
                        // 0x001e41b8
                        charge(ctx, 5);
                        lbu(v0, s2, 23);
                        v0 = v0 | 0x1;
                        sb(v0, s2, 23);
                    }
                    // 0x001e41d8
                    charge(ctx, 8);
                    v0 = s0 & 0xFFFF;
                    v0 = v0 & 0x3FF;
                    v0 = v0 | 0xC00;
                    a0 = v0 & 0xFFFF;
                    jal(ctx, 0x1E41E8u, gen::fn_sub_1E2810_001e2810);
                    if (v0 == 0) {
                        // 0x001e421c
                        charge(ctx, 10);
                        lhu(a0, s2, 16);
                        lhu(a1, s2, 18);
                        a2 = 0;
                        jal(ctx, 0x1E4228u, gen::fn_sub_316E00_00316e00);
                        sw(v0, s2, 40);
                        v0 = 4;
                        sw(v0, s2, 0);
                    } else {
                        // 0x001e41f8
                        charge(ctx, 9);
                        a0 = s1;
                        a1 = 0;
                        a2 = 180;
                        a3 = 0x680000;
                        a3 = addiu(a3, 17008);  // "already exist resource ID"
                        jal(ctx, 0x1E420Cu, gen::fn_sub_1A1540_001a1540);
                    }
                } else {
                    // 0x001e40f8
                    charge(ctx, 2);
                }
            }
            goto L_001e4af0;
        case 0x1E4260u:  // table[3]
            // 0x001e4260
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e4348
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e4354
                    charge(ctx, 4);
                    v0 = 6;
                    sw(v0, s2, 0);
                }
            } else {
                // 0x001e4274
                charge(ctx, 6);
                lw(a0, s2, 4);
                jal(ctx, 0x1E4278u, gen::fn_sub_1A4510_001a4510);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001e4294
                    charge(ctx, 24);
                    lw(a0, s2, 4);
                    a1 = 0;
                    jal(ctx, 0x1E429Cu, gen::fn_sub_1A41B0_001a41b0);
                    lhu(v1, v0, 0);
                    v0 = 4;
                    sh(v0, s2, 16);
                    v0 = 0xFFFF;
                    sh(v0, s2, 18);
                    v0 = 0x41F00000;
                    sw(v0, s2, 24);
                    v0 = 3;
                    sb(v0, s2, 32);
                    v0 = 0x42700000;
                    sw(v0, s2, 36);
                    v0 = 1;
                    sb(v0, s2, 33);
                    v0 = v1 & 0x3FF;
                    v0 = v0 | 0xC00;
                    a0 = v0 & 0xFFFF;
                    jal(ctx, 0x1E42E4u, gen::fn_sub_1E2810_001e2810);
                    if (v0 == 0) {
                        // 0x001e4318
                        charge(ctx, 12);
                        a0 = 4;
                        a1 = 0xFFFF;
                        a2 = 0x680000;
                        a2 = addiu(a2, 17040);  // "field/editor.RMD"
                        a3 = 0;
                        jal(ctx, 0x1E432Cu, gen::fn_sub_316B40_00316b40);
                        sw(v0, s2, 40);
                        v0 = 4;
                        sw(v0, s2, 0);
                    } else {
                        // 0x001e42f4
                        charge(ctx, 9);
                        a0 = s1;
                        a1 = 0;
                        a2 = 180;
                        a3 = 0x680000;
                        a3 = addiu(a3, 17008);  // "already exist resource ID"
                        jal(ctx, 0x1E4308u, gen::fn_sub_1A1540_001a1540);
                    }
                } else {
                    // 0x001e428c
                    charge(ctx, 2);
                }
            }
            goto L_001e4af0;
        case 0x1E4364u:  // table[4]
            // 0x001e4364
            charge(ctx, 10);
            lw(a0, s2, 4);
            a1 = 0;
            jal(ctx, 0x1E436Cu, gen::fn_sub_1A41B0_001a41b0);
            lhu(s0, v0, 0);
            lw(a0, s2, 40);
            jal(ctx, 0x1E437Cu, gen::fn_sub_316F70_00316f70);
            if (v0 != 0) {
                // 0x001e438c
                charge(ctx, 75);
                lbu(a1, s2, 32);
                a0 = s0;
                lw(a2, s2, 40);
                jal(ctx, 0x1E4398u, gen::fn_sub_3B6270_003b6270);
                sh(v0, s2, 20);
                lhu(a0, s2, 20);
                a1 = 1;
                jal(ctx, 0x1E43ACu, gen::fn_sub_1A0DC0_001a0dc0);
                lhu(a0, s2, 20);
                jal(ctx, 0x1E43B8u, gen::fn_sub_3B5D10_003b5d10);
                lw(a0, v0, 488);
                sw(a0, s2, 44);
                lwc1(f12, s2, 24);
                jal(ctx, 0x1E43CCu, gen::fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0);
                lw(a0, s2, 44);
                a1 = lui(0x8000);
                jal(ctx, 0x1E43DCu, gen::fn_sub_1AD870_001ad870);
                lw(a0, s2, 4);
                jal(ctx, 0x1E43E8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                jal(ctx, 0x1E43F0u, gen::fn_sub_198590_00198590);
                lw(a0, v0, 4);
                jal(ctx, 0x1E43FCu, gen::fn_sub_4CB2F0_004cb2f0);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x110);
                swc1(f1, sp, 0x114);
                swc1(f0, sp, 0x118);
                a0 = addiu(sp, 0x100);
                lwc1(f2, v0, 32);
                lwc1(f1, v0, 36);
                lwc1(f0, v0, 40);
                swc1(f2, sp, 0x100);
                swc1(f1, sp, 0x104);
                swc1(f0, sp, 0x108);
                a1 = a0;
                jal(ctx, 0x1E443Cu, gen::fn_sub_4C69F0_004c69f0);
                v0 = 0x447A0000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x100);
                mul_s(f3, f0, f1);
                swc1(f3, sp, 0x100);
                lwc1(f0, sp, 0x104);
                mul_s(f2, f0, f1);
                swc1(f2, sp, 0x104);
                lwc1(f0, sp, 0x108);
                mul_s(f1, f0, f1);
                swc1(f1, sp, 0x108);
                lwc1(f0, sp, 0x110);
                add_s(f0, f0, f3);
                swc1(f0, sp, 0x110);
                lwc1(f0, sp, 0x114);
                add_s(f0, f0, f2);
                swc1(f0, sp, 0x114);
                lwc1(f0, sp, 0x118);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x118);
                lw(a0, s2, 44);
                a1 = addiu(sp, 0x110);
                jal(ctx, 0x1E449Cu, gen::fn_sub_1ADC20_001adc20);
                lw(v0, s2, 0);
                v0 = addiu(v0, 1);
                sw(v0, s2, 0);
            }
            goto L_001e4af0;
        case 0x1E44B8u:  // table[5]
            // 0x001e44b8
            charge(ctx, 4);
            v1 = addiu(sp, 0xE0);
            v0 = 12;
            if (v1 != 0) {
                for (;;) {
                    // 0x001e44c8
                    charge(ctx, 7);
                    sb(zero, v1, 0);
                    v1 = addiu(v1, 1);
                    v0 = addiu(v0, -1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x001e44e4
            charge(ctx, 18);
            v0 = 0x680000;
            ld(v1, v0, 16992);  // 0x684260
            v0 = 0x680000;
            lwc1(f0, v0, 17000);  // 0x684268
            sd(v1, sp, 0xD0);
            swc1(f0, sp, 0xD8);
            jal(ctx, 0x1E44FCu, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            jal(ctx, 0x1E4508u, gen::fn_sub_4CB2F0_004cb2f0);
            a0 = v0;
            jal(ctx, 0x1E4514u, gen::fn_sub_1A5AA0_001a5aa0);
            v0 = 0x7E0000;
            lbu(v0, v0, 2399);  // 0x7E095F
            if (i64(v0) < 0) {
                // 0x001e4540
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e452c
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e455c
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0xE8);
            v0 = 0x7E0000;
            lhu(a0, v0, 2380);  // 0x7E094C
            v0 = a0 & 0x1000;
            if (v0 != 0) {
                // 0x001e4584
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0xE8);
            }
            // 0x001e458c
            charge(ctx, 3);
            v0 = a0 & 0x4000;
            if (v0 != 0) {
                // 0x001e4598
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0xE8);
            }
            // 0x001e45a0
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2398);  // 0x7E095E
            if (i64(v0) < 0) {
                // 0x001e45c4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e45b0
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e45e0
            charge(ctx, 8);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0xE0);
            v0 = a0 & 0x8000;
            if (v0 != 0) {
                // 0x001e4600
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0xE0);
            }
            // 0x001e4608
            charge(ctx, 3);
            v0 = a0 & 0x2000;
            if (v0 != 0) {
                // 0x001e4614
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0xE0);
            }
            // 0x001e461c
            charge(ctx, 7);
            lwc1(f1, sp, 0xE8);
            v0 = lui(0xC240);
            mtc1(v0, f3);
            c_lt_s(f1, f3);
            if (!cond(ctx)) {
                // 0x001e4638
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f2);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e466c;
                }
                // 0x001e4650
                charge(ctx, 4);
                lwc1(f1, sp, 0xE0);
                c_lt_s(f1, f3);
                if (cond(ctx)) {
                    goto L_001e466c;
                }
                // 0x001e4660
                charge(ctx, 3);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e466c;
                }
                goto L_001e47ac;
            }
        L_001e466c:
            charge(ctx, 49);
            v0 = 0x3F800000;
            sw(v0, sp, 0x68);
            sw(v0, sp, 0x54);
            sw(v0, sp, 0x40);
            sw(zero, sp, 0x50);
            sw(zero, sp, 0x48);
            sw(zero, sp, 0x44);
            sw(zero, sp, 0x64);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x58);
            sw(zero, sp, 0x78);
            sw(zero, sp, 0x74);
            sw(zero, sp, 0x70);
            lw(v1, sp, 0x4C);
            v0 = 0x20000;
            v0 = v0 | 0x3;
            v0 = v1 | v0;
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x40);
            a1 = addiu(sp, 0xD0);
            mov_s(f12, f0);
            a2 = 1;
            jal(ctx, 0x1E46C4u, gen::fn_sub_4C31B0_004c31b0);
            a0 = addiu(sp, 0xF0);
            a1 = addiu(sp, 0xE0);
            jal(ctx, 0x1E46D4u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f0, sp, 0xF0);
            neg_s(f0, f0);
            swc1(f0, sp, 0xF0);
            lwc1(f0, sp, 0xF4);
            neg_s(f0, f0);
            swc1(f0, sp, 0xF4);
            lwc1(f0, sp, 0xF8);
            neg_s(f0, f0);
            swc1(f0, sp, 0xF8);
            a0 = addiu(sp, 0xF0);
            a1 = a0;
            a2 = addiu(sp, 0x40);
            jal(ctx, 0x1E470Cu, gen::fn_sub_4C6BE0_004c6be0);
            lwc1(f1, sp, 0xE0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e4730
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE0);
            }
            // 0x001e4744
            charge(ctx, 7);
            lwc1(f1, sp, 0xE8);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e4760
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE8);
            }
            // 0x001e4774
            charge(ctx, 14);
            lwc1(f1, sp, 0xE0);
            lwc1(f0, sp, 0xE8);
            add_s(f1, f1, f0);
            lwc1(f0, gp, -31704);  // 0x7CB118
            mul_s(f1, f0, f1);
            v0 = 0x40000000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            lw(a0, s2, 44);
            a1 = addiu(sp, 0xF0);
            jal(ctx, 0x1E47A4u, gen::fn_K_FldFrame_CtlMoveInDir_001addf0);
        L_001e47ac:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2400);  // 0x7E0960
            if (i64(v0) < 0) {
                // 0x001e47d0
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001e47bc
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001e47ec
            charge(ctx, 11);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, sp, 0xE0);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x001e4818
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    goto L_001e4830;
                }
                goto L_001e4848;
            }
        L_001e4830:
            charge(ctx, 6);
            lwc1(f0, gp, -31700);  // 0x7CB11C
            mul_s(f12, f0, f1);
            lw(a0, s2, 44);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x1E4840u, gen::fn_sub_1ADFF0_001adff0);
        L_001e4848:
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2380);  // 0x7E094C
            v0 = v1 & 0x6;
            if (v0 == 0) {
                // 0x001e48b4
                charge(ctx, 3);
                v0 = v1 & 0x9;
                if (v0 == 0) {
                    // 0x001e4918
                    charge(ctx, 3);
                    v0 = v1 & 0x80;
                    if (v0 == 0) {
                        // 0x001e4938
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v1, v0, 2382);  // gPadFlags
                        v0 = v1 & 0x20;
                        if (v0 == 0) {
                            // 0x001e4964
                            charge(ctx, 3);
                            v0 = v1 & 0x40;
                            if (v0 != 0) {
                                // 0x001e4970
                                charge(ctx, 28);
                                jal(ctx, 0x1E4970u, gen::fn_sub_1E2850_001e2850);
                                s1 = v0;
                                lhu(a0, s2, 20);
                                jal(ctx, 0x1E4980u, gen::fn_sub_3B5D10_003b5d10);
                                s0 = v0;
                                lw(v1, s2, 40);
                                sw(v1, s1, 0);
                                lhu(v1, s2, 20);
                                sh(v1, s1, 8);
                                lhu(v1, s2, 16);
                                sh(v1, s1, 4);
                                lhu(v1, s2, 18);
                                sh(v1, s1, 6);
                                lwc1(f0, s2, 24);
                                swc1(f0, s1, 12);
                                lbu(v1, s2, 22);
                                sb(v1, s1, 10);
                                sh(v1, v0, 480);
                                lbu(v0, s2, 23);
                                sb(v0, s1, 11);
                                lbu(v0, s2, 33);
                                sb(v0, s1, 97);
                                lbu(v0, s1, 11);
                                v0 = v0 & 0x1;
                                if (v0 == 0) {
                                    // 0x001e49f8
                                    charge(ctx, 4);
                                    lw(v0, s0, 40);
                                    v0 = dsll32(v0, 1);
                                    v0 = dsrl32(v0, 1);
                                    sw(v0, s0, 40);
                                } else {
                                    // 0x001e49e0
                                    charge(ctx, 6);
                                    lw(v1, s0, 40);
                                    v0 = lui(0x8000);
                                    v0 = v1 | v0;
                                    sw(v0, s0, 40);
                                }
                                // 0x001e4a08
                                charge(ctx, 8);
                                lw(v0, s2, 28);
                                sw(v0, s1, 16);
                                sw(v0, s0, 484);
                                lw(a0, s2, 40);
                                jal(ctx, 0x1E4A18u, gen::fn_sub_318B60_00318b60);
                                a2 = addiu(s1, 32);
                                a1 = 8;
                                for (;;) {
                                    // 0x001e4a28
                                    charge(ctx, 9);
                                    lw(a0, v0, 0);
                                    lw(v1, v0, 4);
                                    v0 = addiu(v0, 8);
                                    a1 = addiu(a1, -1);
                                    sw(a0, a2, 0);
                                    sw(v1, a2, 4);
                                    a2 = addiu(a2, 8);
                                    if (i64(a1) <= 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x001e4a4c
                                charge(ctx, 38);
                                lbu(v0, s2, 32);
                                sb(v0, s1, 96);
                                lwc1(f0, s2, 36);
                                swc1(f0, s1, 100);
                                lw(a0, s0, 496);
                                lwc1(f12, s2, 36);
                                jal(ctx, 0x1E4A64u, gen::fn_sub_19C320_0019c320);
                                a0 = addiu(s1, 32);
                                jal(ctx, 0x1E4A70u, gen::fn_sub_1A5B30_001a5b30);
                                swc1(f0, sp, 0xA0);
                                a0 = addiu(s1, 32);
                                jal(ctx, 0x1E4A80u, gen::fn_sub_1A5AA0_001a5aa0);
                                swc1(f0, sp, 0xA4);
                                a0 = addiu(s1, 32);
                                jal(ctx, 0x1E4A90u, gen::fn_sub_1A5BC0_001a5bc0);
                                swc1(f0, sp, 0xA8);
                                lhu(a0, s1, 8);
                                a1 = addiu(s1, 80);
                                a2 = addiu(sp, 0xA0);
                                jal(ctx, 0x1E4AA8u, gen::fn_sub_3B78B0_003b78b0);
                                lw(a0, s2, 44);
                                a1 = lui(0x8000);
                                jal(ctx, 0x1E4AB8u, gen::fn_sub_1AD890_001ad890);
                                lw(a0, s1, 0);
                                jal(ctx, 0x1E4AC4u, gen::fn_sub_318B60_00318b60);
                                a0 = v0;
                                jal(ctx, 0x1E4AD0u, gen::fn_sub_4C2F10_004c2f10);
                                sw(zero, s2, 0);
                            }
                        } else {
                            // 0x001e494c
                            charge(ctx, 6);
                            lhu(a0, s2, 20);
                            jal(ctx, 0x1E4950u, gen::fn_sub_3B7090_003b7090);
                            sw(zero, s2, 0);
                        }
                    } else {
                        // 0x001e4924
                        charge(ctx, 5);
                        lw(a0, s2, 44);
                        jal(ctx, 0x1E4928u, gen::fn_sub_1AE0D0_001ae0d0);
                    }
                } else {
                    // 0x001e48c0
                    charge(ctx, 22);
                    a0 = addiu(sp, 0x80);
                    lw(a1, s2, 44);
                    jal(ctx, 0x1E48C8u, gen::fn_sub_1AD940_001ad940);
                    a1 = addiu(sp, 0xB0);
                    lwc1(f2, sp, 0x80);
                    lwc1(f1, sp, 0x84);
                    lwc1(f0, sp, 0x88);
                    swc1(f2, sp, 0xB0);
                    swc1(f1, sp, 0xB4);
                    swc1(f0, sp, 0xB8);
                    lwc1(f1, sp, 0xB4);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xB4);
                    lw(a0, s2, 44);
                    jal(ctx, 0x1E4908u, gen::fn_sub_1ADC20_001adc20);
                }
            } else {
                // 0x001e485c
                charge(ctx, 22);
                a0 = addiu(sp, 0x90);
                lw(a1, s2, 44);
                jal(ctx, 0x1E4864u, gen::fn_sub_1AD940_001ad940);
                a1 = addiu(sp, 0xC0);
                lwc1(f2, sp, 0x90);
                lwc1(f1, sp, 0x94);
                lwc1(f0, sp, 0x98);
                swc1(f2, sp, 0xC0);
                swc1(f1, sp, 0xC4);
                swc1(f0, sp, 0xC8);
                lwc1(f1, sp, 0xC4);
                v0 = 0x41200000;
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xC4);
                lw(a0, s2, 44);
                jal(ctx, 0x1E48A4u, gen::fn_sub_1ADC20_001adc20);
            }
            goto L_001e4af0;
        case 0x1E4AE4u:  // table[6]
            // 0x001e4ae4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001e4af4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x120);
        return;
    }
    goto L_001e4af0;
}

// 0x001E4B10 sub_1E4B10 [K_FieldEditor_CreateNpcDestroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1E4B10(task): frees the "create Npc" work.
void sub_1E4B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e4b10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E4B24u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E4B40 sub_1E4B40 [K_FieldEditor_CreateNpcTask] -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E4B40(parent) -> the "create Npc" task (48-byte work, priority 4207).
void sub_1E4B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e4b40
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 48;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1E4B64u, v0.u());
    if (v0 != 0) {
        // 0x001e4b80
        charge(ctx, 11);
        a0 = s0;
        a1 = 4207;
        a2 = 0x680000;
        a2 = addiu(a2, 17064);  // "create Npc"
        a3 = 0x1E0000;
        a3 = addiu(a3, 16144);  // &sub_1E3F10
        t0 = 0x1E0000;
        t0 = addiu(t0, 19216);  // &sub_1E4B10
        t1 = v0;
        jal(ctx, 0x1E4BA4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    } else {
        // 0x001e4b74
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e4bac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E4BC0 sub_1E4BC0 [K_FieldEditor_NpcListUpdate] -- 3168 bytes; frame 0x180: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E4BC0(task) -> 0, or -1 to be destroyed: the editor's "Npc list": a menu of the NPC records ("ResID=%04d
// Major=%d Minor=%03d"), then MOVE NPC (drive it like sub_1E3F10 state 5; circle writes the new matrix / radius back
// into the record and the resource) or DELETE NPC (with a NO / YES box; sub_1E28A0(record, 1)).
void sub_1E4BC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001e4bc0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s2, a0, f4::kTaskWork);
    lw(a0, s2, 0);
    at = sltiu(a0, 7);
    if (at != 0) {
        // 0x001e4bec
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 28080);  // &0x7B6DB0
        v0 = sll(a0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1E4C08u:  // table[0]
            // 0x001e4c08
            charge(ctx, 13);
            jal(ctx, 0x1E4C08u, gen::fn_sub_1E1840_001e1840);
            lw(s0, v0, 0);
            sw(zero, s2, 12);
            a0 = s1;
            a1 = 32;
            a2 = a1;
            a3 = 2;
            jal(ctx, 0x1E4C28u, gen::fn_sub_1A3B10_001a3b10);
            sw(v0, s2, 4);
            for (;;) {
                // 0x001e4c94
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e4c3c
                charge(ctx, 22);
                lhu(v0, s0, 8);
                a2 = v0 & 0x3FF;
                lhu(a3, s0, 4);
                lhu(t0, s0, 6);
                a0 = addiu(sp, 0x80);
                a1 = 0x680000;
                a1 = addiu(a1, 17104);  // "ResID=%04d Major=%d Minor=%03d"
                jal(ctx, 0x1E4C58u, gen::fn_sprintf_00523ac8);
                lw(a0, s2, 4);
                a1 = addiu(sp, 0x80);
                jal(ctx, 0x1E4C68u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s2, 4);
                a1 = v0;
                jal(ctx, 0x1E4C78u, gen::fn_sub_1A41B0_001a41b0);
                sw(s0, v0, 0);
                lw(v0, s2, 12);
                v0 = addiu(v0, 1);
                sw(v0, s2, 12);
                lw(s0, s0, 108);
            }
            // 0x001e4c9c
            charge(ctx, 3);
            lw(v0, s2, 12);
            if (v0 != 0) {
                // 0x001e4cc4
                charge(ctx, 9);
                lw(a0, s2, 4);
                a1 = 1;
                jal(ctx, 0x1E4CCCu, gen::fn_sub_1A3BF0_001a3bf0);
                lw(v0, s2, 0);
                v0 = addiu(v0, 1);
                sw(v0, s2, 0);
            } else {
                // 0x001e4ca8
                charge(ctx, 7);
                lw(a0, s2, 4);
                jal(ctx, 0x1E4CACu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                v0 = 6;
                sw(v0, s2, 0);
            }
        L_001e5800:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1E4CE8u:  // table[1]
            // 0x001e4ce8
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x001e4d28
                charge(ctx, 4);
                lw(v0, s2, 12);
                v0 = slt(s0, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e4cf4
                charge(ctx, 13);
                lw(a0, s2, 4);
                a1 = s0;
                jal(ctx, 0x1E4CFCu, gen::fn_sub_1A41B0_001a41b0);
                lw(v0, v0, 0);
                lhu(a0, v0, 8);
                jal(ctx, 0x1E4D0Cu, gen::fn_sub_3B5D10_003b5d10);
                lw(a0, v0, 488);
                a1 = lui(0x8000);
                jal(ctx, 0x1E4D1Cu, gen::fn_sub_1AD890_001ad890);
                s0 = addiu(s0, 1);
            }
            // 0x001e4d38
            charge(ctx, 20);
            lw(a0, s2, 4);
            jal(ctx, 0x1E4D3Cu, gen::fn_sub_1A4510_001a4510);
            lw(a0, s2, 4);
            a1 = v0;
            jal(ctx, 0x1E4D4Cu, gen::fn_sub_1A41B0_001a41b0);
            lw(s0, v0, 0);
            lhu(a0, s0, 8);
            jal(ctx, 0x1E4D5Cu, gen::fn_sub_3B5D10_003b5d10);
            lw(a0, v0, 488);
            a1 = lui(0x8000);
            jal(ctx, 0x1E4D6Cu, gen::fn_sub_1AD870_001ad870);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e4f9c
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e4fa8
                    charge(ctx, 7);
                    lw(a0, s2, 4);
                    jal(ctx, 0x1E4FACu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    v0 = 6;
                    sw(v0, s2, 0);
                }
            } else {
                // 0x001e4d88
                charge(ctx, 36);
                lw(a0, s2, 4);
                jal(ctx, 0x1E4D8Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                lw(v0, s0, 0);
                sw(v0, s2, 40);
                lhu(v0, s0, 8);
                sh(v0, s2, 20);
                lhu(v0, s0, 4);
                sh(v0, s2, 16);
                lhu(v0, s0, 6);
                sh(v0, s2, 18);
                lwc1(f0, s0, 12);
                swc1(f0, s2, 24);
                lbu(v0, s0, 11);
                sb(v0, s2, 23);
                lbu(v0, s0, 10);
                sb(v0, s2, 22);
                lw(v0, s0, 16);
                sw(v0, s2, 28);
                lbu(v0, s0, 96);
                sb(v0, s2, 32);
                lwc1(f0, s0, 100);
                swc1(f0, s2, 36);
                lhu(a0, s2, 20);
                jal(ctx, 0x1E4DE8u, gen::fn_sub_3B5D10_003b5d10);
                s0 = v0;
                lw(a0, v0, 488);
                sw(a0, s2, 44);
                a1 = lui(0x8000);
                jal(ctx, 0x1E4E00u, gen::fn_sub_1AD870_001ad870);
                lbu(v0, s2, 23);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x001e4e30
                    charge(ctx, 4);
                    lw(v0, s0, 40);
                    v0 = dsll32(v0, 1);
                    v0 = dsrl32(v0, 1);
                    sw(v0, s0, 40);
                } else {
                    // 0x001e4e18
                    charge(ctx, 6);
                    lw(v1, s0, 40);
                    v0 = lui(0x8000);
                    v0 = v1 | v0;
                    sw(v0, s0, 40);
                }
                // 0x001e4e40
                charge(ctx, 39);
                a0 = s1;
                a1 = 32;
                a2 = a1;
                a3 = 2;
                jal(ctx, 0x1E4E50u, gen::fn_sub_1A3B10_001a3b10);
                sw(v0, s2, 4);
                a0 = v0;
                a1 = 0x680000;
                a1 = addiu(a1, 16672);  // &0x684120
                a2 = 8;
                jal(ctx, 0x1E4E6Cu, gen::fn_sub_1A3DC0_001a3dc0);
                lwc1(f0, s2, 24);
                cvt_w_s(f0, f0);
                mfc1(s0, f0);
                lw(a0, s2, 4);
                a1 = 4;
                jal(ctx, 0x1E4E88u, gen::fn_sub_1A41B0_001a41b0);
                sw(s0, v0, 0);
                lbu(s0, s2, 32);
                lw(a0, s2, 4);
                a1 = 5;
                jal(ctx, 0x1E4EA0u, gen::fn_sub_1A41B0_001a41b0);
                sw(s0, v0, 0);
                lwc1(f0, s2, 36);
                cvt_w_s(f0, f0);
                mfc1(s0, f0);
                lw(a0, s2, 4);
                a1 = 6;
                jal(ctx, 0x1E4EC0u, gen::fn_sub_1A41B0_001a41b0);
                sw(s0, v0, 0);
                lbu(v0, s2, 23);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x001e4efc
                    charge(ctx, 5);
                    lw(a0, s2, 4);
                    a1 = 3;
                    jal(ctx, 0x1E4F04u, gen::fn_sub_1A41B0_001a41b0);
                    sw(zero, v0, 0);
                } else {
                    // 0x001e4edc
                    charge(ctx, 8);
                    s0 = 1;
                    lw(a0, s2, 4);
                    a1 = 3;
                    jal(ctx, 0x1E4EE8u, gen::fn_sub_1A41B0_001a41b0);
                    sw(s0, v0, 0);
                }
                // 0x001e4f10
                charge(ctx, 35);
                lw(a0, s2, 4);
                a1 = 1;
                jal(ctx, 0x1E4F18u, gen::fn_sub_1A4380_001a4380);
                lw(a0, s2, 4);
                a1 = 2;
                jal(ctx, 0x1E4F28u, gen::fn_sub_1A4380_001a4380);
                lw(a0, s2, 4);
                a1 = 0;
                jal(ctx, 0x1E4F38u, gen::fn_sub_1A4380_001a4380);
                lw(a0, s2, 4);
                a1 = 7;
                jal(ctx, 0x1E4F48u, gen::fn_sub_1A4380_001a4380);
                lw(a0, s2, 4);
                a1 = 0x680000;
                a1 = addiu(a1, 17136);  // "MOVE NPC"
                jal(ctx, 0x1E4F5Cu, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s2, 4);
                a1 = 0x680000;
                a1 = addiu(a1, 17152);  // "DELETE NPC"
                jal(ctx, 0x1E4F70u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s2, 4);
                a1 = 1;
                jal(ctx, 0x1E4F80u, gen::fn_sub_1A3BF0_001a3bf0);
                lw(v0, s2, 0);
                v0 = addiu(v0, 1);
                sw(v0, s2, 0);
            }
            goto L_001e5800;
        case 0x1E4FC4u:  // table[2]
            // 0x001e4fc4
            charge(ctx, 4);
            v0 = addiu(a0, 1);
            sw(v0, s2, 0);
            goto L_001e5800;
        case 0x1E4FD4u:  // table[3]
            // 0x001e4fd4
            charge(ctx, 32);
            lw(a0, s2, 4);
            a1 = 4;
            jal(ctx, 0x1E4FDCu, gen::fn_sub_1A41B0_001a41b0);
            lwc1(f0, v0, 0);
            cvt_s_w(f0, f0);
            swc1(f0, s2, 24);
            lw(a0, s2, 44);
            lwc1(f12, s2, 24);
            jal(ctx, 0x1E4FF8u, gen::fn_K_FldFrame_CtlSetSphereCollisRadius_001ad8c0);
            lw(a0, s2, 4);
            a1 = 5;
            jal(ctx, 0x1E5008u, gen::fn_sub_1A41B0_001a41b0);
            lw(v0, v0, 0);
            sb(v0, s2, 32);
            lw(a0, s2, 4);
            a1 = 6;
            jal(ctx, 0x1E5020u, gen::fn_sub_1A41B0_001a41b0);
            lwc1(f0, v0, 0);
            cvt_s_w(f0, f0);
            swc1(f0, s2, 36);
            lw(a0, s2, 4);
            a1 = 3;
            jal(ctx, 0x1E503Cu, gen::fn_sub_1A41B0_001a41b0);
            lw(v1, v0, 0);
            v0 = 1;
            if (v1 != v0) {
                // 0x001e5068
                charge(ctx, 3);
                lbu(v0, s2, 23);
                v0 = v0 & 0xFE;
                sb(v0, s2, 23);
            } else {
                // 0x001e5054
                charge(ctx, 5);
                lbu(v0, s2, 23);
                v0 = v0 | 0x1;
                sb(v0, s2, 23);
            }
            // 0x001e5074
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 != 0) {
                // 0x001e5088
                charge(ctx, 6);
                lw(a0, s2, 4);
                jal(ctx, 0x1E508Cu, gen::fn_sub_1A4510_001a4510);
                v1 = 9;
                if (v0 == v1) {
                    // 0x001e50d8
                    charge(ctx, 25);
                    a0 = s1;
                    a1 = 300;
                    a2 = 220;
                    a3 = 2;
                    jal(ctx, 0x1E50E8u, gen::fn_sub_1A3B10_001a3b10);
                    sw(v0, s2, 8);
                    a0 = v0;
                    a1 = addiu(gp, -27080);  // "NO"
                    jal(ctx, 0x1E50FCu, gen::fn_sub_1A3F20_001a3f20);
                    lw(a0, s2, 8);
                    a1 = addiu(gp, -27076);  // "YES"
                    jal(ctx, 0x1E510Cu, gen::fn_sub_1A3F20_001a3f20);
                    lw(a0, s2, 8);
                    a1 = 1;
                    jal(ctx, 0x1E511Cu, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s2, 4);
                    a1 = 0;
                    jal(ctx, 0x1E512Cu, gen::fn_sub_1A3BF0_001a3bf0);
                    v0 = 5;
                    sw(v0, s2, 0);
                } else {
                    // 0x001e50a0
                    charge(ctx, 3);
                    v1 = 8;
                    if (v0 == v1) {
                        // 0x001e50b4
                        charge(ctx, 9);
                        lw(a0, s2, 4);
                        a1 = 0;
                        jal(ctx, 0x1E50BCu, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(v0, s2, 0);
                        v0 = addiu(v0, 1);
                        sw(v0, s2, 0);
                    } else {
                        // 0x001e50ac
                        charge(ctx, 2);
                    }
                }
            }
            // 0x001e513c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x20;
            if (v0 != 0) {
                // 0x001e5150
                charge(ctx, 13);
                lhu(a0, s2, 20);
                jal(ctx, 0x1E5154u, gen::fn_sub_1E2810_001e2810);
                s1 = v0;
                lhu(a0, s2, 20);
                jal(ctx, 0x1E5164u, gen::fn_sub_3B5D10_003b5d10);
                s0 = v0;
                lw(a0, s2, 40);
                jal(ctx, 0x1E5174u, gen::fn_sub_318B60_00318b60);
                a2 = addiu(s1, 32);
                a1 = 8;
                for (;;) {
                    // 0x001e5184
                    charge(ctx, 9);
                    lw(a0, v0, 0);
                    lw(v1, v0, 4);
                    v0 = addiu(v0, 8);
                    a1 = addiu(a1, -1);
                    sw(a0, a2, 0);
                    sw(v1, a2, 4);
                    a2 = addiu(a2, 8);
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x001e51a8
                charge(ctx, 8);
                lwc1(f0, s2, 24);
                swc1(f0, s1, 12);
                lbu(v0, s2, 23);
                sb(v0, s1, 11);
                lbu(v0, s1, 11);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x001e51e0
                    charge(ctx, 4);
                    lw(v0, s0, 40);
                    v0 = dsll32(v0, 1);
                    v0 = dsrl32(v0, 1);
                    sw(v0, s0, 40);
                } else {
                    // 0x001e51c8
                    charge(ctx, 6);
                    lw(v1, s0, 40);
                    v0 = lui(0x8000);
                    v0 = v1 | v0;
                    sw(v0, s0, 40);
                }
                // 0x001e51f0
                charge(ctx, 46);
                lbu(v0, s2, 22);
                sb(v0, s1, 10);
                sh(v0, s0, 480);
                lw(v0, s2, 28);
                sw(v0, s1, 16);
                sw(v0, s0, 484);
                lhu(a0, s1, 8);
                a1 = addiu(s1, 80);
                a2 = addiu(sp, 0x170);
                jal(ctx, 0x1E5214u, gen::fn_sub_3B78B0_003b78b0);
                lbu(v0, s2, 32);
                sb(v0, s1, 96);
                lwc1(f0, s2, 36);
                swc1(f0, s1, 100);
                lw(a0, s0, 496);
                lwc1(f12, s2, 36);
                jal(ctx, 0x1E5234u, gen::fn_sub_19C320_0019c320);
                a0 = addiu(s1, 32);
                jal(ctx, 0x1E5240u, gen::fn_sub_1A5B30_001a5b30);
                swc1(f0, sp, 0x170);
                a0 = addiu(s1, 32);
                jal(ctx, 0x1E5250u, gen::fn_sub_1A5AA0_001a5aa0);
                swc1(f0, sp, 0x174);
                a0 = addiu(s1, 32);
                jal(ctx, 0x1E5260u, gen::fn_sub_1A5BC0_001a5bc0);
                swc1(f0, sp, 0x178);
                lhu(a0, s1, 8);
                a1 = addiu(s1, 80);
                a2 = addiu(sp, 0x170);
                jal(ctx, 0x1E5278u, gen::fn_sub_3B78B0_003b78b0);
                lw(a0, s2, 4);
                jal(ctx, 0x1E5284u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                lw(a0, s2, 44);
                a1 = lui(0x8000);
                jal(ctx, 0x1E5294u, gen::fn_sub_1AD890_001ad890);
                sw(zero, s2, 0);
            }
            goto L_001e5800;
        case 0x1E52A8u:  // table[4]
            // 0x001e52a8
            charge(ctx, 4);
            v1 = addiu(sp, 0x150);
            v0 = 12;
            if (v1 != 0) {
                for (;;) {
                    // 0x001e52b8
                    charge(ctx, 7);
                    sb(zero, v1, 0);
                    v1 = addiu(v1, 1);
                    v0 = addiu(v0, -1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x001e52d4
            charge(ctx, 18);
            v0 = 0x680000;
            ld(v1, v0, 17080);  // 0x6842B8
            v0 = 0x680000;
            lwc1(f0, v0, 17088);  // 0x6842C0
            sd(v1, sp, 0x140);
            swc1(f0, sp, 0x148);
            jal(ctx, 0x1E52ECu, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            jal(ctx, 0x1E52F8u, gen::fn_sub_4CB2F0_004cb2f0);
            a0 = v0;
            jal(ctx, 0x1E5304u, gen::fn_sub_1A5AA0_001a5aa0);
            v0 = 0x7E0000;
            lbu(v0, v0, 2399);  // 0x7E095F
            if (i64(v0) < 0) {
                // 0x001e5330
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e531c
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e534c
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0x158);
            v0 = 0x7E0000;
            lhu(a0, v0, 2380);  // 0x7E094C
            v0 = a0 & 0x1000;
            if (v0 != 0) {
                // 0x001e5374
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0x158);
            }
            // 0x001e537c
            charge(ctx, 3);
            v0 = a0 & 0x4000;
            if (v0 != 0) {
                // 0x001e5388
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0x158);
            }
            // 0x001e5390
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2398);  // 0x7E095E
            if (i64(v0) < 0) {
                // 0x001e53b4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e53a0
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e53d0
            charge(ctx, 8);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0x150);
            v0 = a0 & 0x8000;
            if (v0 != 0) {
                // 0x001e53f0
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0x150);
            }
            // 0x001e53f8
            charge(ctx, 3);
            v0 = a0 & 0x2000;
            if (v0 != 0) {
                // 0x001e5404
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0x150);
            }
            // 0x001e540c
            charge(ctx, 7);
            lwc1(f1, sp, 0x158);
            v0 = lui(0xC240);
            mtc1(v0, f3);
            c_lt_s(f1, f3);
            if (!cond(ctx)) {
                // 0x001e5428
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f2);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e545c;
                }
                // 0x001e5440
                charge(ctx, 4);
                lwc1(f1, sp, 0x150);
                c_lt_s(f1, f3);
                if (cond(ctx)) {
                    goto L_001e545c;
                }
                // 0x001e5450
                charge(ctx, 3);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e545c;
                }
                goto L_001e559c;
            }
        L_001e545c:
            charge(ctx, 49);
            v0 = 0x3F800000;
            sw(v0, sp, 0x68);
            sw(v0, sp, 0x54);
            sw(v0, sp, 0x40);
            sw(zero, sp, 0x50);
            sw(zero, sp, 0x48);
            sw(zero, sp, 0x44);
            sw(zero, sp, 0x64);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x58);
            sw(zero, sp, 0x78);
            sw(zero, sp, 0x74);
            sw(zero, sp, 0x70);
            lw(v1, sp, 0x4C);
            v0 = 0x20000;
            v0 = v0 | 0x3;
            v0 = v1 | v0;
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x40);
            a1 = addiu(sp, 0x140);
            mov_s(f12, f0);
            a2 = 1;
            jal(ctx, 0x1E54B4u, gen::fn_sub_4C31B0_004c31b0);
            a0 = addiu(sp, 0x160);
            a1 = addiu(sp, 0x150);
            jal(ctx, 0x1E54C4u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f0, sp, 0x160);
            neg_s(f0, f0);
            swc1(f0, sp, 0x160);
            lwc1(f0, sp, 0x164);
            neg_s(f0, f0);
            swc1(f0, sp, 0x164);
            lwc1(f0, sp, 0x168);
            neg_s(f0, f0);
            swc1(f0, sp, 0x168);
            a0 = addiu(sp, 0x160);
            a1 = a0;
            a2 = addiu(sp, 0x40);
            jal(ctx, 0x1E54FCu, gen::fn_sub_4C6BE0_004c6be0);
            lwc1(f1, sp, 0x150);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e5520
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0x150);
            }
            // 0x001e5534
            charge(ctx, 7);
            lwc1(f1, sp, 0x158);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e5550
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0x158);
            }
            // 0x001e5564
            charge(ctx, 14);
            lwc1(f1, sp, 0x150);
            lwc1(f0, sp, 0x158);
            add_s(f1, f1, f0);
            lwc1(f0, gp, -31704);  // 0x7CB118
            mul_s(f1, f0, f1);
            v0 = 0x40000000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            lw(a0, s2, 44);
            a1 = addiu(sp, 0x160);
            jal(ctx, 0x1E5594u, gen::fn_K_FldFrame_CtlMoveInDir_001addf0);
        L_001e559c:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2400);  // 0x7E0960
            if (i64(v0) < 0) {
                // 0x001e55c0
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001e55ac
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001e55dc
            charge(ctx, 11);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, sp, 0x150);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x001e5608
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    goto L_001e5620;
                }
                goto L_001e5638;
            }
        L_001e5620:
            charge(ctx, 6);
            lwc1(f0, gp, -31700);  // 0x7CB11C
            mul_s(f12, f0, f1);
            lw(a0, s2, 44);
            a1 = addiu(sp, 0x140);
            jal(ctx, 0x1E5630u, gen::fn_sub_1ADFF0_001adff0);
        L_001e5638:
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2380);  // 0x7E094C
            v0 = v1 & 0x6;
            if (v0 == 0) {
                // 0x001e56a4
                charge(ctx, 3);
                v0 = v1 & 0x9;
                if (v0 == 0) {
                    // 0x001e5708
                    charge(ctx, 3);
                    v0 = v1 & 0x80;
                    if (v0 == 0) {
                        // 0x001e5728
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, 2382);  // gPadFlags
                        v0 = v0 & 0x60;
                        if (v0 != 0) {
                            // 0x001e573c
                            charge(ctx, 8);
                            lw(a0, s2, 4);
                            a1 = 1;
                            jal(ctx, 0x1E5744u, gen::fn_sub_1A3BF0_001a3bf0);
                            v0 = 3;
                            sw(v0, s2, 0);
                        }
                    } else {
                        // 0x001e5714
                        charge(ctx, 5);
                        lw(a0, s2, 44);
                        jal(ctx, 0x1E5718u, gen::fn_sub_1AE0D0_001ae0d0);
                    }
                } else {
                    // 0x001e56b0
                    charge(ctx, 22);
                    a0 = addiu(sp, 0x100);
                    lw(a1, s2, 44);
                    jal(ctx, 0x1E56B8u, gen::fn_sub_1AD940_001ad940);
                    a1 = addiu(sp, 0x120);
                    lwc1(f2, sp, 0x100);
                    lwc1(f1, sp, 0x104);
                    lwc1(f0, sp, 0x108);
                    swc1(f2, sp, 0x120);
                    swc1(f1, sp, 0x124);
                    swc1(f0, sp, 0x128);
                    lwc1(f1, sp, 0x124);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x124);
                    lw(a0, s2, 44);
                    jal(ctx, 0x1E56F8u, gen::fn_sub_1ADC20_001adc20);
                }
            } else {
                // 0x001e564c
                charge(ctx, 22);
                a0 = addiu(sp, 0x110);
                lw(a1, s2, 44);
                jal(ctx, 0x1E5654u, gen::fn_sub_1AD940_001ad940);
                a1 = addiu(sp, 0x130);
                lwc1(f2, sp, 0x110);
                lwc1(f1, sp, 0x114);
                lwc1(f0, sp, 0x118);
                swc1(f2, sp, 0x130);
                swc1(f1, sp, 0x134);
                swc1(f0, sp, 0x138);
                lwc1(f1, sp, 0x134);
                v0 = 0x41200000;
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x134);
                lw(a0, s2, 44);
                jal(ctx, 0x1E5694u, gen::fn_sub_1ADC20_001adc20);
            }
            goto L_001e5800;
        case 0x1E575Cu:  // table[5]
            // 0x001e575c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 != 0) {
                // 0x001e5770
                charge(ctx, 6);
                lw(a0, s2, 8);
                jal(ctx, 0x1E5774u, gen::fn_sub_1A4510_001a4510);
                a1 = 1;
                if (v0 == a1) {
                    // 0x001e57b4
                    charge(ctx, 11);
                    lhu(a0, s2, 20);
                    jal(ctx, 0x1E57B8u, gen::fn_sub_1E2810_001e2810);
                    a0 = v0;
                    a1 = 1;
                    jal(ctx, 0x1E57C8u, gen::fn_sub_1E28A0_001e28a0);
                    lw(a0, s2, 4);
                    jal(ctx, 0x1E57D4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    sw(zero, s2, 0);
                } else {
                    // 0x001e5788
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001e5798
                        charge(ctx, 7);
                        lw(a0, s2, 4);
                        jal(ctx, 0x1E579Cu, gen::fn_sub_1A3BF0_001a3bf0);
                        v0 = 3;
                        sw(v0, s2, 0);
                    } else {
                        // 0x001e5790
                        charge(ctx, 2);
                    }
                }
                // 0x001e57e0
                charge(ctx, 5);
                lw(a0, s2, 8);
                jal(ctx, 0x1E57E4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            }
            goto L_001e5800;
        case 0x1E57F4u:  // table[6]
            // 0x001e57f4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001e5804 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x180);
        return;
    }
    goto L_001e5800;
}

// 0x001E5820 sub_1E5820 [K_FieldEditor_NpcListDestroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1E5820(task): frees the "create Npc list" work.
void sub_1E5820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e5820
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E5834u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E5850 sub_1E5850 [K_FieldEditor_NpcListTask] -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E5850(parent) -> the "create Npc list" task (work size and priority as sub_1E4B40).
void sub_1E5850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e5850
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 48;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1E5874u, v0.u());
    if (v0 != 0) {
        // 0x001e5890
        charge(ctx, 11);
        a0 = s0;
        a1 = 4207;
        a2 = 0x680000;
        a2 = addiu(a2, 17168);  // "create Npc list"
        a3 = 0x1E0000;
        a3 = addiu(a3, 19392);  // &sub_1E4BC0
        t0 = 0x1E0000;
        t0 = addiu(t0, 22560);  // &sub_1E5820
        t1 = v0;
        jal(ctx, 0x1E58B4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    } else {
        // 0x001e5884
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e58bc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E58D0 sub_1E58D0 [K_FieldEditor_CreatePosUpdate] -- 1828 bytes; frame 0x100: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E58D0(task) -> 0, or -1 to be destroyed: the editor's "create Pos" mode: a resource id from the form 0x684330
// ("already exist resource ID" when taken, sub_1E29E0), a type-8 position resource with a marker task (sub_1A4CD0)
// placed in front of the camera, moved with the sticks (frame translation / rotation sub_1A4ED0.. sub_1A5000) and
// stored as a new 96-byte position record (sub_1E2A20) with circle.
void sub_1E58D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001e58d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s1, a0, f4::kTaskWork);
    lw(v1, s1, 0);
    a1 = 3;
    if (v1 == a1) {
        // 0x001e5fc8
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001e58fc
        charge(ctx, 3);
        a3 = 2;
        if (v1 == a3) {
            // 0x001e5a60
            charge(ctx, 4);
            v1 = addiu(sp, 0xE0);
            v0 = 12;
            if (v1 != 0) {
                for (;;) {
                    // 0x001e5a70
                    charge(ctx, 7);
                    sb(zero, v1, 0);
                    v1 = addiu(v1, 1);
                    v0 = addiu(v0, -1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x001e5a8c
            charge(ctx, 18);
            v0 = 0x680000;
            ld(v1, v0, 17264);  // 0x684370
            v0 = 0x680000;
            lwc1(f0, v0, 17272);  // 0x684378
            sd(v1, sp, 0xD0);
            swc1(f0, sp, 0xD8);
            jal(ctx, 0x1E5AA4u, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            jal(ctx, 0x1E5AB0u, gen::fn_sub_4CB2F0_004cb2f0);
            a0 = v0;
            jal(ctx, 0x1E5ABCu, gen::fn_sub_1A5AA0_001a5aa0);
            v0 = 0x7E0000;
            lbu(v0, v0, 2399);  // 0x7E095F
            if (i64(v0) < 0) {
                // 0x001e5ae8
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e5ad4
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e5b04
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0xE8);
            v0 = 0x7E0000;
            lhu(a0, v0, 2380);  // 0x7E094C
            v0 = a0 & 0x1000;
            if (v0 != 0) {
                // 0x001e5b2c
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0xE8);
            }
            // 0x001e5b34
            charge(ctx, 3);
            v0 = a0 & 0x4000;
            if (v0 != 0) {
                // 0x001e5b40
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0xE8);
            }
            // 0x001e5b48
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2398);  // 0x7E095E
            if (i64(v0) < 0) {
                // 0x001e5b6c
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e5b58
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e5b88
            charge(ctx, 8);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0xE0);
            v0 = a0 & 0x8000;
            if (v0 != 0) {
                // 0x001e5ba8
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0xE0);
            }
            // 0x001e5bb0
            charge(ctx, 3);
            v0 = a0 & 0x2000;
            if (v0 != 0) {
                // 0x001e5bbc
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0xE0);
            }
            // 0x001e5bc4
            charge(ctx, 7);
            lwc1(f1, sp, 0xE8);
            v0 = lui(0xC240);
            mtc1(v0, f3);
            c_lt_s(f1, f3);
            if (!cond(ctx)) {
                // 0x001e5be0
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f2);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e5c14;
                }
                // 0x001e5bf8
                charge(ctx, 4);
                lwc1(f1, sp, 0xE0);
                c_lt_s(f1, f3);
                if (cond(ctx)) {
                    goto L_001e5c14;
                }
                // 0x001e5c08
                charge(ctx, 3);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e5c14;
                }
                goto L_001e5d54;
            }
        L_001e5c14:
            charge(ctx, 49);
            v0 = 0x3F800000;
            sw(v0, sp, 0x68);
            sw(v0, sp, 0x54);
            sw(v0, sp, 0x40);
            sw(zero, sp, 0x50);
            sw(zero, sp, 0x48);
            sw(zero, sp, 0x44);
            sw(zero, sp, 0x64);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x58);
            sw(zero, sp, 0x78);
            sw(zero, sp, 0x74);
            sw(zero, sp, 0x70);
            lw(v1, sp, 0x4C);
            v0 = 0x20000;
            v0 = v0 | 0x3;
            v0 = v1 | v0;
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x40);
            a1 = addiu(sp, 0xD0);
            mov_s(f12, f0);
            a2 = 1;
            jal(ctx, 0x1E5C6Cu, gen::fn_sub_4C31B0_004c31b0);
            a0 = addiu(sp, 0xF0);
            a1 = addiu(sp, 0xE0);
            jal(ctx, 0x1E5C7Cu, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f0, sp, 0xF0);
            neg_s(f0, f0);
            swc1(f0, sp, 0xF0);
            lwc1(f0, sp, 0xF4);
            neg_s(f0, f0);
            swc1(f0, sp, 0xF4);
            lwc1(f0, sp, 0xF8);
            neg_s(f0, f0);
            swc1(f0, sp, 0xF8);
            a0 = addiu(sp, 0xF0);
            a1 = a0;
            a2 = addiu(sp, 0x40);
            jal(ctx, 0x1E5CB4u, gen::fn_sub_4C6BE0_004c6be0);
            lwc1(f1, sp, 0xE0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e5cd8
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE0);
            }
            // 0x001e5cec
            charge(ctx, 7);
            lwc1(f1, sp, 0xE8);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e5d08
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0xE8);
            }
            // 0x001e5d1c
            charge(ctx, 14);
            lwc1(f1, sp, 0xE0);
            lwc1(f0, sp, 0xE8);
            add_s(f1, f1, f0);
            lwc1(f0, gp, -31704);  // 0x7CB118
            mul_s(f1, f0, f1);
            v0 = 0x40000000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            lw(a0, s1, 20);
            a1 = addiu(sp, 0xF0);
            jal(ctx, 0x1E5D4Cu, gen::fn_sub_1A4ED0_001a4ed0);
        L_001e5d54:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2400);  // 0x7E0960
            if (i64(v0) < 0) {
                // 0x001e5d78
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001e5d64
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001e5d94
            charge(ctx, 11);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, sp, 0xE0);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x001e5dc0
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    goto L_001e5dd8;
                }
                goto L_001e5df0;
            }
        L_001e5dd8:
            charge(ctx, 6);
            lwc1(f0, gp, -31700);  // 0x7CB11C
            mul_s(f12, f0, f1);
            lw(a0, s1, 20);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x1E5DE8u, gen::fn_sub_1A4F40_001a4f40);
        L_001e5df0:
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2380);  // 0x7E094C
            v0 = v1 & 0x6;
            if (v0 == 0) {
                // 0x001e5e5c
                charge(ctx, 3);
                v0 = v1 & 0x9;
                if (v0 == 0) {
                    // 0x001e5ec0
                    charge(ctx, 3);
                    v0 = v1 & 0x80;
                    if (v0 == 0) {
                        // 0x001e5ee0
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v1, v0, 2382);  // gPadFlags
                        v0 = v1 & 0x20;
                        if (v0 == 0) {
                            // 0x001e5f18
                            charge(ctx, 3);
                            v0 = v1 & 0x40;
                            if (v0 != 0) {
                                // 0x001e5f24
                                charge(ctx, 12);
                                jal(ctx, 0x1E5F24u, gen::fn_sub_1E2A20_001e2a20);
                                s0 = v0;
                                lhu(v1, s1, 16);
                                sh(v1, v0, 80);
                                lw(v1, s1, 20);
                                sw(v1, v0, 0);
                                lw(a0, s1, 20);
                                jal(ctx, 0x1E5F44u, gen::fn_sub_1A4E50_001a4e50);
                                a2 = addiu(s0, 16);
                                a1 = 8;
                                for (;;) {
                                    // 0x001e5f54
                                    charge(ctx, 9);
                                    lw(a0, v0, 0);
                                    lw(v1, v0, 4);
                                    v0 = addiu(v0, 8);
                                    a1 = addiu(a1, -1);
                                    sw(a0, a2, 0);
                                    sw(v1, a2, 4);
                                    a2 = addiu(a2, 8);
                                    if (i64(a1) <= 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x001e5f78
                                charge(ctx, 20);
                                a0 = addiu(s0, 16);
                                jal(ctx, 0x1E5F7Cu, gen::fn_sub_1A5B30_001a5b30);
                                swc1(f0, sp, 0xA0);
                                a0 = addiu(s0, 16);
                                jal(ctx, 0x1E5F8Cu, gen::fn_sub_1A5AA0_001a5aa0);
                                swc1(f0, sp, 0xA4);
                                a0 = addiu(s0, 16);
                                jal(ctx, 0x1E5F9Cu, gen::fn_sub_1A5BC0_001a5bc0);
                                swc1(f0, sp, 0xA8);
                                lhu(a0, s0, 80);
                                a1 = addiu(s0, 64);
                                a2 = addiu(sp, 0xA0);
                                jal(ctx, 0x1E5FB4u, gen::fn_sub_3B78B0_003b78b0);
                                sw(zero, s1, 0);
                            }
                        } else {
                            // 0x001e5ef4
                            charge(ctx, 9);
                            lhu(a0, s1, 16);
                            jal(ctx, 0x1E5EF8u, gen::fn_sub_3B7090_003b7090);
                            lw(a0, s1, 20);
                            jal(ctx, 0x1E5F04u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                            sw(zero, s1, 0);
                        }
                    } else {
                        // 0x001e5ecc
                        charge(ctx, 5);
                        lw(a0, s1, 20);
                        jal(ctx, 0x1E5ED0u, gen::fn_sub_1A5000_001a5000);
                    }
                } else {
                    // 0x001e5e68
                    charge(ctx, 22);
                    a0 = addiu(sp, 0x80);
                    lw(a1, s1, 20);
                    jal(ctx, 0x1E5E70u, gen::fn_sub_1A4DF0_001a4df0);
                    a1 = addiu(sp, 0xB0);
                    lwc1(f2, sp, 0x80);
                    lwc1(f1, sp, 0x84);
                    lwc1(f0, sp, 0x88);
                    swc1(f2, sp, 0xB0);
                    swc1(f1, sp, 0xB4);
                    swc1(f0, sp, 0xB8);
                    lwc1(f1, sp, 0xB4);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xB4);
                    lw(a0, s1, 20);
                    jal(ctx, 0x1E5EB0u, gen::fn_sub_1A4E60_001a4e60);
                }
            } else {
                // 0x001e5e04
                charge(ctx, 22);
                a0 = addiu(sp, 0x90);
                lw(a1, s1, 20);
                jal(ctx, 0x1E5E0Cu, gen::fn_sub_1A4DF0_001a4df0);
                a1 = addiu(sp, 0xC0);
                lwc1(f2, sp, 0x90);
                lwc1(f1, sp, 0x94);
                lwc1(f0, sp, 0x98);
                swc1(f2, sp, 0xC0);
                swc1(f1, sp, 0xC4);
                swc1(f0, sp, 0xC8);
                lwc1(f1, sp, 0xC4);
                v0 = 0x41200000;
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xC4);
                lw(a0, s1, 20);
                jal(ctx, 0x1E5E4Cu, gen::fn_sub_1A4E60_001a4e60);
            }
        } else {
            // 0x001e5908
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x001e5974
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, 2382);  // gPadFlags
                v0 = v1 & 0x40;
                if (v0 == 0) {
                    // 0x001e5a48
                    charge(ctx, 3);
                    v0 = v1 & 0x20;
                    if (v0 != 0) {
                        // 0x001e5a54
                        charge(ctx, 3);
                        sw(a1, s1, 0);
                    }
                } else {
                    // 0x001e5988
                    charge(ctx, 6);
                    lw(a0, s1, 4);
                    jal(ctx, 0x1E598Cu, gen::fn_sub_1A4510_001a4510);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001e59a8
                        charge(ctx, 12);
                        lw(a0, s1, 4);
                        a1 = 0;
                        jal(ctx, 0x1E59B0u, gen::fn_sub_1A41B0_001a41b0);
                        lhu(s2, v0, 0);
                        v0 = s2 & 0x3FF;
                        v0 = v0 | 0x2000;
                        a0 = v0 & 0xFFFF;
                        jal(ctx, 0x1E59C8u, gen::fn_sub_1E29E0_001e29e0);
                        if (v0 == 0) {
                            // 0x001e59fc
                            charge(ctx, 19);
                            a0 = s2;
                            jal(ctx, 0x1E5A00u, gen::fn_sub_3B5E90_003b5e90);
                            sh(v0, s1, 16);
                            lhu(a0, s1, 16);
                            jal(ctx, 0x1E5A10u, gen::fn_sub_3B5D10_003b5d10);
                            a0 = 0;
                            jal(ctx, 0x1E5A1Cu, gen::fn_sub_1A4CD0_001a4cd0);
                            sw(v0, s1, 20);
                            lw(a0, s1, 4);
                            jal(ctx, 0x1E5A2Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                            lw(v0, s1, 0);
                            v0 = addiu(v0, 1);
                            sw(v0, s1, 0);
                        } else {
                            // 0x001e59d8
                            charge(ctx, 9);
                            a0 = s0;
                            a1 = 0;
                            a2 = 180;
                            a3 = 0x680000;
                            a3 = addiu(a3, 17280);  // "already exist resource ID"
                            jal(ctx, 0x1E59ECu, gen::fn_sub_1A1540_001a1540);
                        }
                    } else {
                        // 0x001e59a0
                        charge(ctx, 2);
                    }
                }
            } else {
                // 0x001e5914
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x001e5924
                    charge(ctx, 20);
                    a1 = 32;
                    a2 = a1;
                    jal(ctx, 0x1E592Cu, gen::fn_sub_1A3B10_001a3b10);
                    sw(v0, s1, 4);
                    a0 = v0;
                    a1 = 0x680000;
                    a1 = addiu(a1, 17200);  // &0x684330
                    a2 = 2;
                    jal(ctx, 0x1E5948u, gen::fn_sub_1A3DC0_001a3dc0);
                    lw(a0, s1, 4);
                    a1 = 1;
                    jal(ctx, 0x1E5958u, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(v0, s1, 0);
                    v0 = addiu(v0, 1);
                    sw(v0, s1, 0);
                } else {
                    // 0x001e591c
                    charge(ctx, 2);
                }
            }
        }
        // 0x001e5fd4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001e5fd8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x001E6000 sub_1E6000 [K_FieldEditor_CreatePosDestroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1E6000(task): frees the "create Pos" work.
void sub_1E6000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e6000
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E6014u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E6030 sub_1E6030 [K_FieldEditor_CreatePosTask] -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E6030(parent) -> the "create Pos" task.
void sub_1E6030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e6030
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 24;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1E6054u, v0.u());
    if (v0 != 0) {
        // 0x001e6070
        charge(ctx, 11);
        a0 = s0;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, 17312);  // "create Pos"
        a3 = 0x1E0000;
        a3 = addiu(a3, 22736);  // &sub_1E58D0
        t0 = 0x1E0000;
        t0 = addiu(t0, 24576);  // &sub_1E6000
        t1 = v0;
        jal(ctx, 0x1E6094u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    } else {
        // 0x001e6064
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e609c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E60B0 sub_1E60B0 [K_FieldEditor_PosListUpdate] -- 2436 bytes; frame 0x190: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E60B0(task) -> 0, or -1 to be destroyed: the editor's position list ("ResID=%04d"): MOVE POS / DELETE POS as
// sub_1E4BC0 for the 96-byte records (sub_1E2A70(record, 1)).
void sub_1E60B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001e60b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, f4::kTaskWork);
    lw(a0, s1, 0);
    at = sltiu(a0, 7);
    if (at != 0) {
        // 0x001e60e0
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 28112);  // &0x7B6DD0
        v0 = sll(a0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1E60FCu:  // table[0]
            // 0x001e60fc
            charge(ctx, 13);
            jal(ctx, 0x1E60FCu, gen::fn_sub_1E1840_001e1840);
            lw(s0, v0, 4);
            sw(zero, s1, 12);
            a0 = s2;
            a1 = 32;
            a2 = a1;
            a3 = 2;
            jal(ctx, 0x1E611Cu, gen::fn_sub_1A3B10_001a3b10);
            sw(v0, s1, 4);
            for (;;) {
                // 0x001e6180
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e6130
                charge(ctx, 20);
                lhu(v0, s0, 80);
                a2 = v0 & 0x3FF;
                a0 = addiu(sp, 0x90);
                a1 = 0x680000;
                a1 = addiu(a1, 17344);  // "ResID=%04d"
                jal(ctx, 0x1E6144u, gen::fn_sprintf_00523ac8);
                lw(a0, s1, 4);
                a1 = addiu(sp, 0x90);
                jal(ctx, 0x1E6154u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s1, 4);
                a1 = v0;
                jal(ctx, 0x1E6164u, gen::fn_sub_1A41B0_001a41b0);
                sw(s0, v0, 0);
                lw(v0, s1, 12);
                v0 = addiu(v0, 1);
                sw(v0, s1, 12);
                lw(s0, s0, 88);
            }
            // 0x001e6188
            charge(ctx, 3);
            lw(v0, s1, 12);
            if (v0 != 0) {
                // 0x001e61b0
                charge(ctx, 9);
                lw(a0, s1, 4);
                a1 = 1;
                jal(ctx, 0x1E61B8u, gen::fn_sub_1A3BF0_001a3bf0);
                lw(v0, s1, 0);
                v0 = addiu(v0, 1);
                sw(v0, s1, 0);
            } else {
                // 0x001e6194
                charge(ctx, 7);
                lw(a0, s1, 4);
                jal(ctx, 0x1E6198u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                v0 = 6;
                sw(v0, s1, 0);
            }
        L_001e6a10:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1E61D4u:  // table[1]
            // 0x001e61d4
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x001e6214
                charge(ctx, 4);
                lw(v0, s1, 12);
                v0 = slt(s0, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e61e0
                charge(ctx, 13);
                lw(a0, s1, 4);
                a1 = s0;
                jal(ctx, 0x1E61E8u, gen::fn_sub_1A41B0_001a41b0);
                lw(s3, v0, 0);
                lhu(a0, s3, 80);
                jal(ctx, 0x1E61F8u, gen::fn_sub_3B5D10_003b5d10);
                lw(a0, s3, 0);
                a1 = addiu(gp, -27064);  // &0x7CC338
                jal(ctx, 0x1E6208u, gen::fn_sub_1A4DC0_001a4dc0);
                s0 = addiu(s0, 1);
            }
            // 0x001e6224
            charge(ctx, 20);
            lw(a0, s1, 4);
            jal(ctx, 0x1E6228u, gen::fn_sub_1A4510_001a4510);
            lw(a0, s1, 4);
            a1 = v0;
            jal(ctx, 0x1E6238u, gen::fn_sub_1A41B0_001a41b0);
            lw(s0, v0, 0);
            lhu(a0, s0, 80);
            jal(ctx, 0x1E6248u, gen::fn_sub_3B5D10_003b5d10);
            lw(a0, s0, 0);
            a1 = addiu(gp, -27060);  // &0x7CC33C
            jal(ctx, 0x1E6258u, gen::fn_sub_1A4DC0_001a4dc0);
            v0 = 0x7E0000;
            lhu(v1, v0, 2382);  // gPadFlags
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x001e6304
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 != 0) {
                    // 0x001e6310
                    charge(ctx, 7);
                    lw(a0, s1, 4);
                    jal(ctx, 0x1E6314u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    v0 = 6;
                    sw(v0, s1, 0);
                }
            } else {
                // 0x001e6274
                charge(ctx, 36);
                lw(a0, s1, 4);
                jal(ctx, 0x1E6278u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                lw(v0, s0, 0);
                sw(v0, s1, 20);
                lhu(v0, s0, 80);
                sh(v0, s1, 16);
                lhu(a0, s1, 16);
                jal(ctx, 0x1E6294u, gen::fn_sub_3B5D10_003b5d10);
                a0 = s2;
                a1 = 32;
                a2 = a1;
                a3 = 2;
                jal(ctx, 0x1E62ACu, gen::fn_sub_1A3B10_001a3b10);
                sw(v0, s1, 4);
                a0 = v0;
                a1 = 0x680000;
                a1 = addiu(a1, 17360);  // "MOVE POS"
                jal(ctx, 0x1E62C4u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s1, 4);
                a1 = 0x680000;
                a1 = addiu(a1, 17376);  // "DELETE POS"
                jal(ctx, 0x1E62D8u, gen::fn_sub_1A3F20_001a3f20);
                lw(a0, s1, 4);
                a1 = 1;
                jal(ctx, 0x1E62E8u, gen::fn_sub_1A3BF0_001a3bf0);
                lw(v0, s1, 0);
                v0 = addiu(v0, 1);
                sw(v0, s1, 0);
            }
            goto L_001e6a10;
        case 0x1E632Cu:  // table[2]
            // 0x001e632c
            charge(ctx, 4);
            v0 = addiu(a0, 1);
            sw(v0, s1, 0);
            goto L_001e6a10;
        case 0x1E633Cu:  // table[3]
            // 0x001e633c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 != 0) {
                // 0x001e6350
                charge(ctx, 6);
                lw(a0, s1, 4);
                jal(ctx, 0x1E6354u, gen::fn_sub_1A4510_001a4510);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001e639c
                    charge(ctx, 25);
                    a0 = s2;
                    a1 = 300;
                    a2 = 220;
                    a3 = 2;
                    jal(ctx, 0x1E63ACu, gen::fn_sub_1A3B10_001a3b10);
                    sw(v0, s1, 8);
                    a0 = v0;
                    a1 = addiu(gp, -27056);  // "NO"
                    jal(ctx, 0x1E63C0u, gen::fn_sub_1A3F20_001a3f20);
                    lw(a0, s1, 8);
                    a1 = addiu(gp, -27052);  // "YES"
                    jal(ctx, 0x1E63D0u, gen::fn_sub_1A3F20_001a3f20);
                    lw(a0, s1, 8);
                    a1 = 1;
                    jal(ctx, 0x1E63E0u, gen::fn_sub_1A3BF0_001a3bf0);
                    lw(a0, s1, 4);
                    a1 = 0;
                    jal(ctx, 0x1E63F0u, gen::fn_sub_1A3BF0_001a3bf0);
                    v0 = 5;
                    sw(v0, s1, 0);
                } else {
                    // 0x001e6368
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001e6378
                        charge(ctx, 9);
                        lw(a0, s1, 4);
                        a1 = 0;
                        jal(ctx, 0x1E6380u, gen::fn_sub_1A3BF0_001a3bf0);
                        lw(v0, s1, 0);
                        v0 = addiu(v0, 1);
                        sw(v0, s1, 0);
                    } else {
                        // 0x001e6370
                        charge(ctx, 2);
                    }
                }
            }
            // 0x001e6400
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x20;
            if (v0 != 0) {
                // 0x001e6414
                charge(ctx, 6);
                lw(a0, s1, 4);
                jal(ctx, 0x1E6418u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                sw(zero, s1, 0);
            }
            goto L_001e6a10;
        case 0x1E642Cu:  // table[4]
            // 0x001e642c
            charge(ctx, 4);
            v1 = addiu(sp, 0x170);
            v0 = 12;
            if (v1 != 0) {
                for (;;) {
                    // 0x001e643c
                    charge(ctx, 7);
                    sb(zero, v1, 0);
                    v1 = addiu(v1, 1);
                    v0 = addiu(v0, -1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x001e6458
            charge(ctx, 18);
            v0 = 0x680000;
            ld(v1, v0, 17328);  // 0x6843B0
            v0 = 0x680000;
            lwc1(f0, v0, 17336);  // 0x6843B8
            sd(v1, sp, 0x160);
            swc1(f0, sp, 0x168);
            jal(ctx, 0x1E6470u, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            jal(ctx, 0x1E647Cu, gen::fn_sub_4CB2F0_004cb2f0);
            a0 = v0;
            jal(ctx, 0x1E6488u, gen::fn_sub_1A5AA0_001a5aa0);
            v0 = 0x7E0000;
            lbu(v0, v0, 2399);  // 0x7E095F
            if (i64(v0) < 0) {
                // 0x001e64b4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e64a0
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e64d0
            charge(ctx, 10);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0x178);
            v0 = 0x7E0000;
            lhu(a0, v0, 2380);  // 0x7E094C
            v0 = a0 & 0x1000;
            if (v0 != 0) {
                // 0x001e64f8
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0x178);
            }
            // 0x001e6500
            charge(ctx, 3);
            v0 = a0 & 0x4000;
            if (v0 != 0) {
                // 0x001e650c
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0x178);
            }
            // 0x001e6514
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2398);  // 0x7E095E
            if (i64(v0) < 0) {
                // 0x001e6538
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f1);
                cvt_s_w(f2, f1);
                add_s(f2, f2, f2);
            } else {
                // 0x001e6524
                charge(ctx, 5);
                mtc1(v0, f1);
                cvt_s_w(f2, f1);
            }
            // 0x001e6554
            charge(ctx, 8);
            v0 = 0x43000000;
            mtc1(v0, f1);
            sub_s(f1, f2, f1);
            swc1(f1, sp, 0x170);
            v0 = a0 & 0x8000;
            if (v0 != 0) {
                // 0x001e6574
                charge(ctx, 2);
                v0 = lui(0xC300);
                sw(v0, sp, 0x170);
            }
            // 0x001e657c
            charge(ctx, 3);
            v0 = a0 & 0x2000;
            if (v0 != 0) {
                // 0x001e6588
                charge(ctx, 2);
                v0 = 0x43000000;
                sw(v0, sp, 0x170);
            }
            // 0x001e6590
            charge(ctx, 7);
            lwc1(f1, sp, 0x178);
            v0 = lui(0xC240);
            mtc1(v0, f3);
            c_lt_s(f1, f3);
            if (!cond(ctx)) {
                // 0x001e65ac
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f2);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e65e0;
                }
                // 0x001e65c4
                charge(ctx, 4);
                lwc1(f1, sp, 0x170);
                c_lt_s(f1, f3);
                if (cond(ctx)) {
                    goto L_001e65e0;
                }
                // 0x001e65d4
                charge(ctx, 3);
                c_le_s(f1, f2);
                if (!cond(ctx)) {
                    goto L_001e65e0;
                }
                goto L_001e6720;
            }
        L_001e65e0:
            charge(ctx, 49);
            v0 = 0x3F800000;
            sw(v0, sp, 0x78);
            sw(v0, sp, 0x64);
            sw(v0, sp, 0x50);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x58);
            sw(zero, sp, 0x54);
            sw(zero, sp, 0x74);
            sw(zero, sp, 0x70);
            sw(zero, sp, 0x68);
            sw(zero, sp, 0x88);
            sw(zero, sp, 0x84);
            sw(zero, sp, 0x80);
            lw(v1, sp, 0x5C);
            v0 = 0x20000;
            v0 = v0 | 0x3;
            v0 = v1 | v0;
            sw(v0, sp, 0x5C);
            a0 = addiu(sp, 0x50);
            a1 = addiu(sp, 0x160);
            mov_s(f12, f0);
            a2 = 1;
            jal(ctx, 0x1E6638u, gen::fn_sub_4C31B0_004c31b0);
            a0 = addiu(sp, 0x180);
            a1 = addiu(sp, 0x170);
            jal(ctx, 0x1E6648u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f0, sp, 0x180);
            neg_s(f0, f0);
            swc1(f0, sp, 0x180);
            lwc1(f0, sp, 0x184);
            neg_s(f0, f0);
            swc1(f0, sp, 0x184);
            lwc1(f0, sp, 0x188);
            neg_s(f0, f0);
            swc1(f0, sp, 0x188);
            a0 = addiu(sp, 0x180);
            a1 = a0;
            a2 = addiu(sp, 0x50);
            jal(ctx, 0x1E6680u, gen::fn_sub_4C6BE0_004c6be0);
            lwc1(f1, sp, 0x170);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e66a4
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0x170);
            }
            // 0x001e66b8
            charge(ctx, 7);
            lwc1(f1, sp, 0x178);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x001e66d4
                charge(ctx, 5);
                v0 = lui(0xBF80);
                mtc1(v0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, sp, 0x178);
            }
            // 0x001e66e8
            charge(ctx, 14);
            lwc1(f1, sp, 0x170);
            lwc1(f0, sp, 0x178);
            add_s(f1, f1, f0);
            lwc1(f0, gp, -31704);  // 0x7CB118
            mul_s(f1, f0, f1);
            v0 = 0x40000000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            lw(a0, s1, 20);
            a1 = addiu(sp, 0x180);
            jal(ctx, 0x1E6718u, gen::fn_sub_1A4ED0_001a4ed0);
        L_001e6720:
            charge(ctx, 4);
            v0 = 0x7E0000;
            lbu(v0, v0, 2400);  // 0x7E0960
            if (i64(v0) < 0) {
                // 0x001e6744
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001e6730
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001e6760
            charge(ctx, 11);
            v0 = 0x43000000;
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, sp, 0x170);
            v0 = lui(0xC240);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x001e678c
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    goto L_001e67a4;
                }
                goto L_001e67bc;
            }
        L_001e67a4:
            charge(ctx, 6);
            lwc1(f0, gp, -31700);  // 0x7CB11C
            mul_s(f12, f0, f1);
            lw(a0, s1, 20);
            a1 = addiu(sp, 0x160);
            jal(ctx, 0x1E67B4u, gen::fn_sub_1A4F40_001a4f40);
        L_001e67bc:
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, 2380);  // 0x7E094C
            v0 = v1 & 0x6;
            if (v0 == 0) {
                // 0x001e6828
                charge(ctx, 3);
                v0 = v1 & 0x9;
                if (v0 == 0) {
                    // 0x001e688c
                    charge(ctx, 3);
                    v0 = v1 & 0x80;
                    if (v0 == 0) {
                        // 0x001e68ac
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, 2382);  // gPadFlags
                        v0 = v0 & 0x60;
                        if (v0 != 0) {
                            // 0x001e68c0
                            charge(ctx, 9);
                            lhu(a0, s1, 16);
                            jal(ctx, 0x1E68C4u, gen::fn_sub_1E29E0_001e29e0);
                            s0 = v0;
                            lw(a0, s1, 20);
                            jal(ctx, 0x1E68D4u, gen::fn_sub_1A4E50_001a4e50);
                            a2 = addiu(s0, 16);
                            a1 = 8;
                            for (;;) {
                                // 0x001e68e4
                                charge(ctx, 9);
                                lw(a0, v0, 0);
                                lw(v1, v0, 4);
                                v0 = addiu(v0, 8);
                                a1 = addiu(a1, -1);
                                sw(a0, a2, 0);
                                sw(v1, a2, 4);
                                a2 = addiu(a2, 8);
                                if (i64(a1) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x001e6908
                            charge(ctx, 25);
                            a0 = addiu(s0, 16);
                            jal(ctx, 0x1E690Cu, gen::fn_sub_1A5B30_001a5b30);
                            swc1(f0, sp, 0x130);
                            a0 = addiu(s0, 16);
                            jal(ctx, 0x1E691Cu, gen::fn_sub_1A5AA0_001a5aa0);
                            swc1(f0, sp, 0x134);
                            a0 = addiu(s0, 16);
                            jal(ctx, 0x1E692Cu, gen::fn_sub_1A5BC0_001a5bc0);
                            swc1(f0, sp, 0x138);
                            lhu(a0, s0, 80);
                            a1 = addiu(s0, 64);
                            a2 = addiu(sp, 0x130);
                            jal(ctx, 0x1E6944u, gen::fn_sub_3B78B0_003b78b0);
                            lw(a0, s1, 4);
                            a1 = 1;
                            jal(ctx, 0x1E6954u, gen::fn_sub_1A3BF0_001a3bf0);
                            v0 = 3;
                            sw(v0, s1, 0);
                        }
                    } else {
                        // 0x001e6898
                        charge(ctx, 5);
                        lw(a0, s1, 20);
                        jal(ctx, 0x1E689Cu, gen::fn_sub_1A5000_001a5000);
                    }
                } else {
                    // 0x001e6834
                    charge(ctx, 22);
                    a0 = addiu(sp, 0x110);
                    lw(a1, s1, 20);
                    jal(ctx, 0x1E683Cu, gen::fn_sub_1A4DF0_001a4df0);
                    a1 = addiu(sp, 0x140);
                    lwc1(f2, sp, 0x110);
                    lwc1(f1, sp, 0x114);
                    lwc1(f0, sp, 0x118);
                    swc1(f2, sp, 0x140);
                    swc1(f1, sp, 0x144);
                    swc1(f0, sp, 0x148);
                    lwc1(f1, sp, 0x144);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x144);
                    lw(a0, s1, 20);
                    jal(ctx, 0x1E687Cu, gen::fn_sub_1A4E60_001a4e60);
                }
            } else {
                // 0x001e67d0
                charge(ctx, 22);
                a0 = addiu(sp, 0x120);
                lw(a1, s1, 20);
                jal(ctx, 0x1E67D8u, gen::fn_sub_1A4DF0_001a4df0);
                a1 = addiu(sp, 0x150);
                lwc1(f2, sp, 0x120);
                lwc1(f1, sp, 0x124);
                lwc1(f0, sp, 0x128);
                swc1(f2, sp, 0x150);
                swc1(f1, sp, 0x154);
                swc1(f0, sp, 0x158);
                lwc1(f1, sp, 0x154);
                v0 = 0x41200000;
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x154);
                lw(a0, s1, 20);
                jal(ctx, 0x1E6818u, gen::fn_sub_1A4E60_001a4e60);
            }
            goto L_001e6a10;
        case 0x1E696Cu:  // table[5]
            // 0x001e696c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 != 0) {
                // 0x001e6980
                charge(ctx, 6);
                lw(a0, s1, 8);
                jal(ctx, 0x1E6984u, gen::fn_sub_1A4510_001a4510);
                a1 = 1;
                if (v0 == a1) {
                    // 0x001e69c4
                    charge(ctx, 11);
                    sw(zero, s1, 0);
                    lhu(a0, s1, 16);
                    jal(ctx, 0x1E69CCu, gen::fn_sub_1E29E0_001e29e0);
                    a0 = v0;
                    a1 = 1;
                    jal(ctx, 0x1E69DCu, gen::fn_sub_1E2A70_001e2a70);
                    lw(a0, s1, 4);
                    jal(ctx, 0x1E69E8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                } else {
                    // 0x001e6998
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001e69a8
                        charge(ctx, 7);
                        v0 = 3;
                        sw(v0, s1, 0);
                        lw(a0, s1, 4);
                        jal(ctx, 0x1E69B4u, gen::fn_sub_1A3BF0_001a3bf0);
                    } else {
                        // 0x001e69a0
                        charge(ctx, 2);
                    }
                }
                // 0x001e69f0
                charge(ctx, 5);
                lw(a0, s1, 8);
                jal(ctx, 0x1E69F4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            }
            goto L_001e6a10;
        case 0x1E6A04u:  // table[6]
            // 0x001e6a04
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001e6a14 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x190);
        return;
    }
    goto L_001e6a10;
}

// 0x001E6A40 sub_1E6A40 [K_FieldEditor_PosListDestroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1E6A40(task): frees the position-list work.
void sub_1E6A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e6a40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E6A54u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E6A70 sub_1E6A70 [K_FieldEditor_PosListTask] -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E6A70(parent) -> the position-list task (its name string is "create Npc list" too).
void sub_1E6A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e6a70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 24;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1E6A94u, v0.u());
    if (v0 != 0) {
        // 0x001e6ab0
        charge(ctx, 11);
        a0 = s0;
        a1 = 4207;
        a2 = 0x680000;
        a2 = addiu(a2, 17392);  // "create Npc list"
        a3 = 0x1E0000;
        a3 = addiu(a3, 24752);  // &sub_1E60B0
        t0 = 0x1E0000;
        t0 = addiu(t0, 27200);  // &sub_1E6A40
        t1 = v0;
        jal(ctx, 0x1E6AD4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
    } else {
        // 0x001e6aa4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e6adc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E6AF0 sub_1E6AF0 [K_Hit_MakeQuad] -- 436 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_1E6AF0(out[4], center, $f12 width, $f13 depth): the four corners of a width x depth quad in the xz plane
// centred on the origin ((-w/2, 0, -d/2), (w/2, 0, -d/2), (-w/2, 0, d/2), (w/2, 0, d/2)), turned by the angle in
// $f14 about the axis 0x684400 (an RwMatrix, RwV3dTransformPoints) and moved to center. Callers: the block builder
// sub_1BB300 and the scene hit creators sub_3B6870 / sub_3B69A0.
void sub_1E6AF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001e6af0
    enter(ctx, 79);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    mov_s(f22, f12);
    mov_s(f21, f13);
    mov_s(f20, f14);
    jal(ctx, 0x1E6B24u, gen::fn_sub_4C38C0_004c38c0);
    s0 = v0;
    a1 = addiu(sp, 0x50);
    v1 = 0x680000;
    ld(a0, v1, 17408);  // 0x684400
    v1 = 0x680000;
    lwc1(f0, v1, 17416);  // 0x684408
    sd(a0, sp, 0x50);
    swc1(f0, sp, 0x58);
    neg_s(f0, f22);
    v1 = 0x40000000;
    mtc1(v1, f3);
    div_s(f2, f0, f3);
    swc1(f2, s2, 0);
    sw(zero, s2, 4);
    neg_s(f0, f21);
    div_s(f0, f0, f3);
    swc1(f0, s2, 8);
    div_s(f1, f22, f3);
    swc1(f1, s2, 12);
    sw(zero, s2, 16);
    swc1(f0, s2, 20);
    swc1(f2, s2, 24);
    sw(zero, s2, 28);
    div_s(f0, f21, f3);
    swc1(f0, s2, 32);
    swc1(f1, s2, 36);
    sw(zero, s2, 40);
    swc1(f0, s2, 44);
    v1 = 0x3F800000;
    sw(v1, v0, 40);
    sw(v1, v0, 20);
    sw(v1, v0, 0);
    sw(zero, v0, 16);
    sw(zero, v0, 8);
    sw(zero, v0, 4);
    sw(zero, v0, 36);
    sw(zero, v0, 32);
    sw(zero, v0, 24);
    sw(zero, v0, 56);
    sw(zero, v0, 52);
    sw(zero, v0, 48);
    lw(a0, v0, 12);
    v1 = 0x20000;
    v1 = v1 | 0x3;
    v1 = a0 | v1;
    sw(v1, v0, 12);
    a0 = s0;
    mov_s(f12, f20);
    a2 = 2;
    jal(ctx, 0x1E6BF4u, gen::fn_sub_4C31B0_004c31b0);
    a0 = s2;
    a1 = s2;
    a2 = 4;
    a3 = s0;
    jal(ctx, 0x1E6C0Cu, gen::fn_sub_4C6C20_004c6c20);
    a0 = s0;
    jal(ctx, 0x1E6C18u, gen::fn_sub_4C3880_004c3880);
    a0 = 0;
    for (;;) {
        // 0x001e6c70
        charge(ctx, 3);
        v1 = slti(a0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e6c2c
        charge(ctx, 17);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(s2, v1);
        lwc1(f1, v1, 0);
        lwc1(f0, s1, 0);
        add_s(f0, f1, f0);
        swc1(f0, v1, 0);
        lwc1(f1, s1, 4);
        lwc1(f0, v1, 4);
        add_s(f0, f0, f1);
        swc1(f0, v1, 4);
        lwc1(f1, s1, 8);
        lwc1(f0, v1, 8);
        add_s(f0, f0, f1);
        swc1(f0, v1, 8);
        a0 = addiu(a0, 1);
    }
    // 0x001e6c7c
    charge(ctx, 10);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001E6CB0 sub_1E6CB0 [K_Fldrc_RequestHbn] -- 152 bytes; frame 0xB0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E6CB0(major, minor) -> the request of "field/data/fMMM_NNN.HBN" (the field's hit data), 1 with the .pac, 0 when
// it does not exist.
void sub_1E6CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e6cb0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x1E6CC8u, gen::fn_sub_1B0910_001b0910);
    if (v0 != 0) {
        // 0x001e6d2c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x001e6cd8
        charge(ctx, 12);
        a2 = s1 & 0xFFFF;
        a3 = s0 & 0xFFFF;
        a0 = addiu(sp, 0x30);
        a1 = 0x680000;
        a1 = addiu(a1, 17424);  // "field/data/f%03d_%03d.HBN"
        jal(ctx, 0x1E6CECu, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x30);
        jal(ctx, 0x1E6CF8u, gen::fn_H_Cdvd_FileExists_001008b0);
        if (v0 != 0) {
            // 0x001e6d14
            charge(ctx, 6);
            a0 = addiu(sp, 0x30);
            a1 = 0;
            jal(ctx, 0x1E6D1Cu, gen::fn_H_Cdvd_Request_00100d80);
        } else {
            // 0x001e6d08
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001e6d30 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x001E6D50 sub_1E6D50 [K_Fldrc_TryLoadHbn] -- 328 bytes; frame 0xA0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E6D50(request, &data, major, minor) -> 1 when the HBN is copied to a heap block *data (from the .pac
// "field/pack/fMMM_NNN.HBN" or the loaded request; 1 at once for no request).
void sub_1E6D50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e6d50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = a1;
    s2 = a2;
    s1 = a3;
    if (s3 != 0) {
        // 0x001e6d8c
        charge(ctx, 4);
        jal(ctx, 0x1E6D8Cu, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001e6dfc
            charge(ctx, 14);
            a2 = s2 & 0xFFFF;
            a3 = s1 & 0xFFFF;
            a0 = addiu(sp, 0x50);
            a1 = 0x680000;
            a1 = addiu(a1, 17456);  // "field/pack/f%03d_%03d.HBN"
            jal(ctx, 0x1E6E10u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x50);
            a1 = addiu(sp, 0x9C);
            jal(ctx, 0x1E6E20u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s1 = v0;
            if (s1 != 0) {
                // 0x001e6e34
                charge(ctx, 13);
                lw(a1, sp, 0x9C);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1E6E48u, v0.u());
                sw(v0, s0, 0);
                lw(a2, sp, 0x9C);
                a0 = v0;
                a1 = s1;
                jal(ctx, 0x1E6E60u, gen::fn_memcpy_00521250);
            }
            // 0x001e6e68
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001e6d9c
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x1E6DA0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001e6e74
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001e6db0
                charge(ctx, 19);
                lw(a1, s3, 280);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1E6DC4u, v0.u());
                sw(v0, s0, 0);
                lw(a2, s3, 280);
                a0 = v0;
                lw(a1, s3, 272);
                jal(ctx, 0x1E6DDCu, gen::fn_memcpy_00521250);
                a0 = s3;
                jal(ctx, 0x1E6DE8u, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            }
        }
    } else {
        // 0x001e6d80
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001e6e78 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001E6EA0 sub_1E6EA0 [K_Fldrc_CreateHbnHits] -- 856 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E6EA0(hbn): creates the scene's hit resources from an HBN (+4 version 0x10000..0x10003, the section start by
// version: +40 / +48 / +56 / +72; counts +8 / +16 / +24 / +32 / +40 / +48 / +56 / +64): 32-byte hit quads (type 13,
// sub_3B6870; not on random floors, whose blocks carry their own), 20-byte type-14 points (sub_3B6AD0), and outside
// random floors the enemy (15), treasure (16), v1.1 type-17, v1.2 32-byte type-21 records (sub_3B69A0, id 0x5400 |
// n +332 = the record's +2) and v1.3 exits (18, sub_3B6DD0) / type-19 points (sub_3B6E90). "CAUTION!! READ OLD VER
// HIT DATA" below v1.3.
void sub_1E6EA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x001e6ea0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    if (s2 != 0) {
        // 0x001e6ec4
        charge(ctx, 4);
        lw(a0, s2, 4);
        v1 = 0x10000;
        if (a0 != v1) {
            // 0x001e6ee0
            charge(ctx, 3);
            v0 = v1 | 0x1;
            if (a0 != v0) {
                // 0x001e6ef8
                charge(ctx, 3);
                v0 = v1 | 0x2;
                if (a0 != v0) {
                    // 0x001e6f10
                    charge(ctx, 1);
                    s1 = addiu(s2, 72);
                } else {
                    // 0x001e6f04
                    charge(ctx, 3);
                    s1 = addiu(s2, 56);
                }
            } else {
                // 0x001e6eec
                charge(ctx, 3);
                s1 = addiu(s2, 48);
            }
        } else {
            // 0x001e6ed4
            charge(ctx, 3);
            s1 = addiu(s2, 40);
        }
        // 0x001e6f14
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x001e6f60
            charge(ctx, 4);
            lw(v0, s2, 8);
            v0 = sltu(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001e6f20
            charge(ctx, 4);
            jal(ctx, 0x1E6F20u, gen::fn_K_Scene_IsRandomFloor_001a0250);
            if (v0 == 0) {
                // 0x001e6f30
                charge(ctx, 10);
                lhu(v0, s1, 0);
                a0 = v0 & 0x3FF;
                a1 = addiu(s1, 8);
                lwc1(f12, s1, 20);
                lwc1(f13, s1, 24);
                lwc1(f14, s1, 28);
                lwr(a2, s1, 4);
                lwl(a2, s1, 7);
                jal(ctx, 0x1E6F50u, gen::fn_sub_3B6870_003b6870);
            }
            // 0x001e6f58
            charge(ctx, 2);
            s0 = addiu(s0, 1);
            s1 = addiu(s1, 32);
        }
        // 0x001e6f70
        charge(ctx, 4);
        s0 = s1;
        s3 = 0;
        for (;;) {
            // 0x001e6fa0
            charge(ctx, 4);
            lw(v0, s2, 16);
            v0 = sltu(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001e6f80
            charge(ctx, 8);
            lhu(v0, s0, 0);
            a0 = v0 & 0x3FF;
            a1 = addiu(s0, 4);
            lwc1(f12, s0, 16);
            jal(ctx, 0x1E6F90u, gen::fn_sub_3B6AD0_003b6ad0);
            s3 = addiu(s3, 1);
            s0 = addiu(s0, 20);
        }
        // 0x001e6fb0
        charge(ctx, 4);
        jal(ctx, 0x1E6FB0u, gen::fn_K_Scene_IsRandomFloor_001a0250);
        if (v0 == 0) {
            // 0x001e6fc0
            charge(ctx, 3);
            s3 = 0;
            for (;;) {
                // 0x001e6fec
                charge(ctx, 4);
                lw(v1, s2, 24);
                v1 = sltu(s3, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e6fcc
                charge(ctx, 8);
                lhu(v0, s0, 0);
                a0 = v0 & 0x3FF;
                a1 = addiu(s0, 4);
                lwc1(f12, s0, 16);
                jal(ctx, 0x1E6FDCu, gen::fn_sub_3B6B90_003b6b90);
                s3 = addiu(s3, 1);
                s0 = addiu(s0, 20);
            }
            // 0x001e6ffc
            charge(ctx, 3);
            s3 = 0;
            for (;;) {
                // 0x001e7028
                charge(ctx, 4);
                lw(v1, s2, 32);
                v1 = sltu(s3, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e7008
                charge(ctx, 8);
                lhu(v0, s0, 0);
                a0 = v0 & 0x3FF;
                a1 = addiu(s0, 4);
                lwc1(f12, s0, 16);
                jal(ctx, 0x1E7018u, gen::fn_sub_3B6C50_003b6c50);
                s3 = addiu(s3, 1);
                s0 = addiu(s0, 20);
            }
            // 0x001e7038
            charge(ctx, 6);
            lw(v1, s2, 4);
            at = 0x10000;
            at = at | 0x1;
            at = sltu(v1, at);
            if (at == 0) {
                // 0x001e7050
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x001e707c
                    charge(ctx, 4);
                    lw(v1, s2, 40);
                    v1 = sltu(s3, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e705c
                    charge(ctx, 8);
                    lhu(v0, s0, 0);
                    a0 = v0 & 0x3FF;
                    a1 = addiu(s0, 4);
                    lwc1(f12, s0, 16);
                    jal(ctx, 0x1E706Cu, gen::fn_sub_3B6D10_003b6d10);
                    s3 = addiu(s3, 1);
                    s0 = addiu(s0, 20);
                }
            }
            // 0x001e708c
            charge(ctx, 6);
            lw(v1, s2, 4);
            at = 0x10000;
            at = at | 0x2;
            at = sltu(v1, at);
            if (at == 0) {
                // 0x001e70a4
                charge(ctx, 4);
                s1 = s0;
                s0 = 0;
                for (;;) {
                    // 0x001e7104
                    charge(ctx, 4);
                    lw(v1, s2, 48);
                    v1 = sltu(s0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e70b4
                    charge(ctx, 20);
                    lhu(v0, s1, 0);
                    a0 = v0 & 0x3FF;
                    a1 = addiu(s1, 8);
                    lwc1(f12, s1, 20);
                    lwc1(f13, s1, 24);
                    lwc1(f14, s1, 28);
                    lwr(a2, s1, 4);
                    lwl(a2, s1, 7);
                    jal(ctx, 0x1E70D4u, gen::fn_sub_3B69A0_003b69a0);
                    lhu(v0, s1, 0);
                    v0 = v0 & 0x3FF;
                    v0 = v0 | 0x5400;
                    a0 = v0 & 0xFFFF;
                    jal(ctx, 0x1E70ECu, gen::fn_sub_3B5D10_003b5d10);
                    lhu(v1, s1, 2);
                    sw(v1, v0, 332);
                    s0 = addiu(s0, 1);
                    s1 = addiu(s1, 32);
                }
            }
            // 0x001e7114
            charge(ctx, 6);
            lw(v1, s2, 4);
            at = 0x10000;
            at = at | 0x3;
            at = sltu(v1, at);
            if (at == 0) {
                // 0x001e712c
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x001e7158
                    charge(ctx, 4);
                    lw(v1, s2, 56);
                    v1 = sltu(s0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e7138
                    charge(ctx, 8);
                    lhu(v0, s1, 0);
                    a0 = v0 & 0x3FF;
                    a1 = addiu(s1, 4);
                    lwc1(f12, s1, 16);
                    jal(ctx, 0x1E7148u, gen::fn_sub_3B6DD0_003b6dd0);
                    s0 = addiu(s0, 1);
                    s1 = addiu(s1, 20);
                }
                // 0x001e7168
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x001e7194
                    charge(ctx, 4);
                    lw(v1, s2, 64);
                    v1 = sltu(s0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e7174
                    charge(ctx, 8);
                    lhu(v0, s1, 0);
                    a0 = v0 & 0x3FF;
                    a1 = addiu(s1, 4);
                    lwc1(f12, s1, 16);
                    jal(ctx, 0x1E7184u, gen::fn_sub_3B6E90_003b6e90);
                    s0 = addiu(s0, 1);
                    s1 = addiu(s1, 20);
                }
            }
        }
        // 0x001e71a4
        charge(ctx, 6);
        lw(v1, s2, 4);
        at = 0x10000;
        at = at | 0x3;
        at = sltu(v1, at);
        if (at != 0) {
            // 0x001e71bc
            charge(ctx, 7);
            a0 = 0;
            a1 = 0;
            a2 = 388;
            a3 = 0x680000;
            a3 = addiu(a3, 17488);  // "CAUTION!! READ OLD VER HIT DATA"
            jal(ctx, 0x1E71D0u, gen::fn_sub_1A1540_001a1540);
        }
    }
    // 0x001e71d8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001E7200 sub_1E7200 [K_Fldrc_RequestFieldScriptFile] -- 136 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E7200(major) -> the request of "field/script/fMMM.bf" (the field's BF script), 1 with the .pac, 0 if absent.
void sub_1E7200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7200
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1E7210u, gen::fn_sub_1B0910_001b0910);
    if (v0 != 0) {
        // 0x001e7270
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x001e7220
        charge(ctx, 11);
        a2 = s0 & 0xFFFF;
        a0 = addiu(sp, 0x20);
        a1 = 0x680000;
        a1 = addiu(a1, 17520);  // "field/script/f%03d.bf"
        jal(ctx, 0x1E7230u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x20);
        jal(ctx, 0x1E723Cu, gen::fn_H_Cdvd_FileExists_001008b0);
        if (v0 != 0) {
            // 0x001e7258
            charge(ctx, 6);
            a0 = addiu(sp, 0x20);
            a1 = 0;
            jal(ctx, 0x1E7260u, gen::fn_H_Cdvd_Request_00100d80);
        } else {
            // 0x001e724c
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001e7274 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001E7290 sub_1E7290 [K_Fldrc_TryLoadFieldScript] -- 372 bytes; frame 0x80: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E7290(request, major) -> 1 when the field script is copied to the heap: sField +4168 the block, +4172 its size
// (from the .pac "field/pack/fMMM.bf" or the loaded request; 1 at once for no request).
void sub_1E7290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7290
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 != 0) {
        // 0x001e72bc
        charge(ctx, 4);
        jal(ctx, 0x1E72BCu, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001e7350
            charge(ctx, 13);
            a2 = s0 & 0xFFFF;
            a0 = addiu(sp, 0x30);
            a1 = 0x680000;
            a1 = addiu(a1, 17552);  // "field/pack/f%03d.bf"
            jal(ctx, 0x1E7360u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x30);
            a1 = addiu(sp, 0x7C);
            jal(ctx, 0x1E7370u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s1 = v0;
            if (s1 != 0) {
                // 0x001e7384
                charge(ctx, 22);
                lw(a1, sp, 0x7C);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1E7398u, v0.u());
                s0 = v0;
                jal(ctx, 0x1E73A4u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kFieldScript);
                lw(s0, sp, 0x7C);
                jal(ctx, 0x1E73B4u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kFieldScriptSize);
                jal(ctx, 0x1E73C0u, gen::fn_K_Field_Get_001b9120);
                lw(a2, sp, 0x7C);
                lw(a0, v0, f4::fld::kFieldScript);
                a1 = s1;
                jal(ctx, 0x1E73D4u, gen::fn_memcpy_00521250);
            }
            // 0x001e73dc
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001e72cc
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x1E72D0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001e73e8
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001e72e0
                charge(ctx, 28);
                lw(a1, s1, 280);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1E72F4u, v0.u());
                s0 = v0;
                jal(ctx, 0x1E7300u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kFieldScript);
                lw(s0, s1, 280);
                jal(ctx, 0x1E7310u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kFieldScriptSize);
                jal(ctx, 0x1E731Cu, gen::fn_K_Field_Get_001b9120);
                lw(a2, s1, 280);
                lw(a0, v0, f4::fld::kFieldScript);
                lw(a1, s1, 272);
                jal(ctx, 0x1E7330u, gen::fn_memcpy_00521250);
                a0 = s1;
                jal(ctx, 0x1E733Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            }
        }
    } else {
        // 0x001e72b0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001e73ec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001E7410 sub_1E7410 [K_Fldrc_FreeFieldScript] -- 84 bytes; frame 0x10: ra sp+0x0
// sub_1E7410(): frees the field script copy (sField +4168).
void sub_1E7410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7410
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1E7418u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kFieldScript);
    if (v1 != 0) {
        // 0x001e742c
        charge(ctx, 10);
        jal(ctx, 0x1E742Cu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kFieldScript);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1E7440u, v0.u());
        jal(ctx, 0x1E7448u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kFieldScript);
    }
    // 0x001e7454 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E7470 sub_1E7470 [K_Fldrc_RequestMapFile] -- 100 bytes; frame 0x90: ra sp+0x0
// sub_1E7470(major, minor) -> the request of "field/map/fMMM_NNN.MAP" (a fixed floor's grid), 0 when absent.
void sub_1E7470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7470
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x0);
    a2 = a0 & 0xFFFF;
    a3 = a1 & 0xFFFF;
    a0 = addiu(sp, 0x10);
    a1 = 0x680000;
    a1 = addiu(a1, 17584);  // "field/map/f%03d_%03d.MAP"
    jal(ctx, 0x1E748Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x1E7498u, gen::fn_H_Cdvd_FileExists_001008b0);
    if (v0 != 0) {
        // 0x001e74b4
        charge(ctx, 4);
        a0 = addiu(sp, 0x10);
        a1 = 0;
        jal(ctx, 0x1E74BCu, gen::fn_H_Cdvd_Request_00100d80);
    } else {
        // 0x001e74a8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e74c4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001E74E0 sub_1E74E0 [K_Fldrc_IsMapFileLoaded] -- 56 bytes; frame 0x10: ra sp+0x0
// sub_1E74E0(request) -> 1 when there is no request or it has loaded.
void sub_1E74E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e74e0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x001e74fc
        charge(ctx, 3);
        jal(ctx, 0x1E74FCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        v0 = sltu(0, v0);
    } else {
        // 0x001e74f0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001e7508 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E7520 sub_1E7520 [K_Fldrc_FreeMapFile] -- 32 bytes; frame 0x10: ra sp+0x0
// sub_1E7520(request): H_Cdvd_Destroy(request).
void sub_1E7520(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7520
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1E7528u, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001E7540 sub_1E7540 [K_HiResShot_WriteTile] -- 108 bytes; frame 0x60: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E7540(raster, x, y) -> raster: the tile callback of the high-resolution screenshot: writes the raster as
// "hst:image%d_%d_%d.bmp" (shot number 0x7CE2C4, tile x / y) through sub_4BAD50 and prints the result. Debug only.
void sub_1E7540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7540
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a3 = a1;
    t0 = a2;
    a0 = addiu(sp, 0x20);
    a1 = 0x680000;
    a1 = addiu(a1, 17616);  // "hst:image%d_%d_%d.bmp"
    lw(a2, gp, -18988);  // 0x7CE2C4
    jal(ctx, 0x1E7568u, gen::fn_sprintf_00523ac8);
    sw(zero, gp, -19896);  // 0x7CDF38
    a0 = s0;
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x1E757Cu, gen::fn_sub_4BAD50_004bad50);
    a0 = addiu(gp, -27048);  // "0x%x\n"
    a1 = v0;
    jal(ctx, 0x1E758Cu, gen::fn_printf_005225a8);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001E75B0 sub_1E75B0 [K_HiResShot_RenderTile] -- 356 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E75B0(camera) -> camera: the render callback of the high-resolution screenshot: copies the tile camera's
// view window, offsets and frustum into the main camera and runs one task frame with the band B tasks disabled
// (kwlnTaskSetBandBEnabled(0), kwlnTaskMain, (1)). Debug only.
void sub_1E75B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001e75b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(gp, -27040);  // "%d %d\n"
    jal(ctx, 0x1E75C4u, gen::fn_printf_005225a8);
    jal(ctx, 0x1E75CCu, gen::fn_sub_198590_00198590);
    a2 = addiu(s0, 32);
    a1 = addiu(v0, 32);
    a0 = 8;
    for (;;) {
        // 0x001e75e0
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e7604
    charge(ctx, 17);
    jal(ctx, 0x1E7604u, gen::fn_sub_198590_00198590);
    lwc1(f1, s0, 104);
    lwc1(f0, s0, 108);
    swc1(f1, v0, 104);
    swc1(f0, v0, 108);
    jal(ctx, 0x1E761Cu, gen::fn_sub_198590_00198590);
    lwc1(f1, s0, 120);
    lwc1(f0, s0, 124);
    swc1(f1, v0, 120);
    swc1(f0, v0, 124);
    jal(ctx, 0x1E7634u, gen::fn_sub_198590_00198590);
    a2 = addiu(s0, 148);
    a1 = addiu(v0, 148);
    a0 = 15;
    for (;;) {
        // 0x001e7648
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e766c
    charge(ctx, 5);
    jal(ctx, 0x1E766Cu, gen::fn_sub_198590_00198590);
    a2 = addiu(s0, 268);
    a1 = addiu(v0, 268);
    a0 = 3;
    for (;;) {
        // 0x001e7680
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e76a4
    charge(ctx, 5);
    jal(ctx, 0x1E76A4u, gen::fn_sub_198590_00198590);
    a2 = addiu(s0, 292);
    a1 = addiu(v0, 292);
    a0 = 12;
    for (;;) {
        // 0x001e76b8
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e76dc
    charge(ctx, 14);
    a0 = 0;
    jal(ctx, 0x1E76E0u, gen::fn_kwlnTaskSetBandBEnabled_00195770);
    jal(ctx, 0x1E76E8u, gen::fn_kwlnTaskMain_001949e0);
    a0 = 1;
    jal(ctx, 0x1E76F4u, gen::fn_kwlnTaskSetBandBEnabled_00195770);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E7720 sub_1E7720 [K_HiResShot_Take] -- 408 bytes; frame 0x1A0: ra sp+0x0
// sub_1E7720(task): takes a 1280 x 896 screenshot in 640 x 448 tiles (sub_4BF540 with sub_1E75B0 / sub_1E7540),
// saving and restoring the main camera's 400 bytes around it; shot number 0x7CE2C4 + 1. From kwlnUpdate (debug).
void sub_1E7720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001e7720
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1E7728u, gen::fn_sub_198590_00198590);
    a1 = addiu(sp, 0x10);
    a0 = 25;
    for (;;) {
        // 0x001e7738
        charge(ctx, 7);
        lq(v1, v0, 0);
        v0 = addiu(v0, 16);
        a0 = addiu(a0, -1);
        sq(v1, a1, 0);
        a1 = addiu(a1, 16);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e7754
    charge(ctx, 19);
    jal(ctx, 0x1E7754u, gen::fn_sub_198590_00198590);
    a0 = v0;
    a1 = 1280;
    a2 = 896;
    a3 = 640;
    t0 = 448;
    t1 = 0x1E0000;
    t1 = addiu(t1, 30128);  // &sub_1E75B0
    t2 = 0x1E0000;
    t2 = addiu(t2, 30016);  // &sub_1E7540
    t3 = 0;
    jal(ctx, 0x1E7784u, gen::fn_sub_4BF540_004bf540);
    jal(ctx, 0x1E778Cu, gen::fn_sub_198590_00198590);
    a2 = addiu(sp, 0x30);
    a1 = addiu(v0, 32);
    a0 = 8;
    for (;;) {
        // 0x001e77a0
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e77c4
    charge(ctx, 17);
    jal(ctx, 0x1E77C4u, gen::fn_sub_198590_00198590);
    lwc1(f1, sp, 0x78);
    lwc1(f0, sp, 0x7C);
    swc1(f1, v0, 104);
    swc1(f0, v0, 108);
    jal(ctx, 0x1E77DCu, gen::fn_sub_198590_00198590);
    lwc1(f1, sp, 0x88);
    lwc1(f0, sp, 0x8C);
    swc1(f1, v0, 120);
    swc1(f0, v0, 124);
    jal(ctx, 0x1E77F4u, gen::fn_sub_198590_00198590);
    a2 = addiu(sp, 0xA4);
    a1 = addiu(v0, 148);
    a0 = 15;
    for (;;) {
        // 0x001e7808
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e782c
    charge(ctx, 5);
    jal(ctx, 0x1E782Cu, gen::fn_sub_198590_00198590);
    a2 = addiu(sp, 0x11C);
    a1 = addiu(v0, 268);
    a0 = 3;
    for (;;) {
        // 0x001e7840
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e7864
    charge(ctx, 5);
    jal(ctx, 0x1E7864u, gen::fn_sub_198590_00198590);
    a3 = addiu(sp, 0x134);
    a2 = addiu(v0, 292);
    a1 = 12;
    for (;;) {
        // 0x001e7878
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001e789c
    charge(ctx, 7);
    lw(v1, gp, -18988);  // 0x7CE2C4
    v1 = addiu(v1, 1);
    sw(v1, gp, -18988);  // 0x7CE2C4
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x001E78C0 sub_1E78C0 [K_Im3d_CreateQuadClump] -- 416 bytes; frame 0x90: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1E78C0(n, texture) -> an RpAtomic of n camera-facing quads (sub_493710: 4 n vertices, 2 n triangles with the
// index pattern 0x6844E8) with a bounding sphere at the middle of the near / far planes, in the main camera's world
// (sub_492D10). Callers: the debug-draw tasks sub_1A1550 / sub_1A2A80.
void sub_1E78C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x001e78c0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s5 = a0;
    a2 = a1;
    a0 = sll(s5, 2);
    a1 = sll(s5, 1);
    jal(ctx, 0x1E78F4u, gen::fn_sub_493710_00493710);
    s4 = v0;
    lw(s3, v0, 44);
    s2 = 0;
    s1 = 0;
    for (;;) {
        // 0x001e7980
        charge(ctx, 3);
        v0 = slt(s1, s5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e7914
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x001e796c
            charge(ctx, 3);
            v0 = slti(s0, 6);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001e7920
            charge(ctx, 19);
            v1 = sll(s0, 1);
            v0 = 0x680000;
            v0 = addiu(v0, 17640);  // &0x6844E8
            v1 = addu(v0, v1);
            lhu(v0, v1, 0);
            v0 = addu(s2, v0);
            a2 = v0 & 0xFFFF;
            lhu(v0, v1, 2);
            v0 = addu(s2, v0);
            a3 = v0 & 0xFFFF;
            lhu(v0, v1, 4);
            v0 = addu(s2, v0);
            t0 = v0 & 0xFFFF;
            a0 = s4;
            a1 = s3;
            jal(ctx, 0x1E795Cu, gen::fn_sub_493210_00493210);
            s3 = addiu(s3, 8);
            s0 = addiu(s0, 3);
        }
        // 0x001e7978
        charge(ctx, 2);
        s2 = addiu(s2, 4);
        s1 = addiu(s1, 1);
    }
    // 0x001e798c
    charge(ctx, 53);
    lw(s0, s4, 92);
    sw(zero, sp, 0x80);
    sw(zero, sp, 0x84);
    jal(ctx, 0x1E7998u, gen::fn_sub_198590_00198590);
    lwc1(f20, v0, 128);
    jal(ctx, 0x1E79A4u, gen::fn_sub_198590_00198590);
    lwc1(f0, v0, 132);
    add_s(f1, f20, f0);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    sw(zero, sp, 0x8C);
    lwc1(f3, sp, 0x80);
    lwc1(f2, sp, 0x84);
    lwc1(f1, sp, 0x88);
    lwc1(f0, sp, 0x8C);
    swc1(f3, s0, 4);
    swc1(f2, s0, 8);
    swc1(f1, s0, 12);
    swc1(f0, s0, 16);
    jal(ctx, 0x1E79ECu, gen::fn_sub_491880_00491880);
    s0 = v0;
    a0 = s0;
    a1 = s4;
    a2 = 0;
    jal(ctx, 0x1E7A04u, gen::fn_sub_4919B0_004919b0);
    a0 = s4;
    jal(ctx, 0x1E7A10u, gen::fn_sub_493B60_00493b60);
    jal(ctx, 0x1E7A18u, gen::fn_sub_198590_00198590);
    a0 = s0;
    lw(a1, v0, 4);
    jal(ctx, 0x1E7A28u, gen::fn_sub_492D10_00492d10);
    v0 = s0;
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001E7A60 sub_1E7A60 [K_Im3d_DestroyQuadClump] -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E7A60(atomic): removes the atomic from the world (sub_492D10(.., 0)) and destroys it (sub_491A80).
void sub_1E7A60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7a60
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    jal(ctx, 0x1E7A74u, gen::fn_sub_492D10_00492d10);
    a0 = s0;
    jal(ctx, 0x1E7A80u, gen::fn_sub_491A80_00491a80);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E7AA0 sub_1E7AA0 [K_Im3d_SetQuadUv] -- 104 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E7AA0(atomic, i, uv): sets the texture coordinates of quad i (geometry +44 + 16 i + 8; sub_493230 twice).
void sub_1E7AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7aa0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    lw(a0, a0, 24);
    v1 = sll(a1, 4);
    lw(v0, a0, 44);
    a1 = addu(v0, v1);
    s0 = addiu(a1, 8);
    jal(ctx, 0x1E7AD0u, gen::fn_sub_493230_00493230);
    lw(a0, s2, 24);
    a1 = s0;
    a2 = s1;
    jal(ctx, 0x1E7AE4u, gen::fn_sub_493230_00493230);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001E7B10 sub_1E7B10 [K_Im3d_ScreenToCameraQuad] -- 272 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_1E7B10(quad[4], $f12 depth): turns four screen-space corners into camera space at the given depth from the
// view window (camera +104.., the raster size sub_4CA5B0 / sub_4CA560).
void sub_1E7B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001e7b10
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f22, f12);
    jal(ctx, 0x1E7B34u, gen::fn_sub_198590_00198590);
    s1 = addiu(v0, 104);
    jal(ctx, 0x1E7B40u, gen::fn_sub_198590_00198590);
    lwc1(f0, s1, 0);
    mul_s(f0, f0, f22);
    v0 = 0x40000000;
    mtc1(v0, f1);
    mul_s(f21, f1, f0);
    lwc1(f0, s1, 4);
    mul_s(f0, f0, f22);
    mul_s(f20, f1, f0);
    jal(ctx, 0x1E7B6Cu, gen::fn_sub_4CA5B0_004ca5b0);
    a0 = addiu(sp, 0x40);
    a1 = v0;
    jal(ctx, 0x1E7B7Cu, gen::fn_sub_4CA560_004ca560);
    a0 = 0;
    v1 = 0x3F000000;
    mtc1(v1, f2);
    for (;;) {
        // 0x001e7bf0
        charge(ctx, 3);
        v1 = sltiu(a0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e7b98
        charge(ctx, 22);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(s0, v1);
        lwc1(f0, v1, 0);
        neg_s(f1, f0);
        lwc1(f0, sp, 0x40);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        add_s(f0, f2, f0);
        mul_s(f0, f21, f0);
        swc1(f0, v1, 0);
        lwc1(f0, v1, 4);
        neg_s(f1, f0);
        lwc1(f0, sp, 0x44);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        add_s(f0, f2, f0);
        mul_s(f0, f20, f0);
        swc1(f0, v1, 4);
        swc1(f22, v1, 8);
        a0 = addiu(a0, 1);
    }
    // 0x001e7bfc
    charge(ctx, 9);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001E7C20 sub_1E7C20 [K_Im3d_GetNearFarDepth] -- 188 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// sub_1E7C20() -> 0xFFFF: the depth helper of the debug quads ($f0 = a value between the camera's near +128 and far
// +132 planes through ACC).
void sub_1E7C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x001e7c20
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1E7C34u, gen::fn_sub_198590_00198590);
    lwc1(f20, v0, 128);
    jal(ctx, 0x1E7C40u, gen::fn_sub_198590_00198590);
    lwc1(f3, v0, 132);
    v0 = 0xFFFF;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    neg_s(f2, f0);
    if (i64(s0) < 0) {
        // 0x001e7c7c
        charge(ctx, 7);
        v1 = srl(s0, 1);
        v0 = s0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x001e7c68
        charge(ctx, 5);
        mtc1(s0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x001e7c98 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    v0 = 0xFFFF;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    sub_s(f1, f1, f0);
    sub_s(f0, f3, f20);
    mula_s(f2, f3);
    msub_s(f1, f1, f0);
    mul_s(f0, f2, f20);
    mul_s(f0, f3, f0);
    div_s(f0, f0, f1);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001E7CE0 sub_1E7CE0 [K_AfterImage_Create] -- 244 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E7CE0(points, segments) -> an after-image trail record (eff_after.c): one block of 36 + 24 points + 12
// (points + 1) + 36 (segments + 1) bytes (RwMalloc 0x960178): +4 / +8 / +12 the three arrays, +16 a frame
// (sub_4C38C0), +24 points, +20 segments, +32..+35 = 0xFF, flags +0 = 3.
void sub_1E7CE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7ce0
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    v0 = sll(s4, 1);
    v0 = addu(v0, s4);
    s1 = sll(v0, 3);
    v1 = addiu(s4, 1);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    s0 = sll(v0, 2);
    v1 = addiu(s3, 1);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, s1);
    a0 = addu(v0, s0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x1E7D44u, v0.u());
    s2 = v0;
    v1 = addiu(s2, 36);
    sw(v1, v0, 4);
    v1 = addu(v1, s1);
    sw(v1, v0, 8);
    v1 = addu(v1, s0);
    sw(v1, v0, 12);
    jal(ctx, 0x1E7D68u, gen::fn_sub_4C38C0_004c38c0);
    sw(v0, s2, 16);
    sw(zero, s2, 0);
    sw(zero, s2, 28);
    sw(s4, s2, 24);
    sw(s3, s2, 20);
    v0 = 255;
    sb(v0, s2, 32);
    sb(v0, s2, 33);
    sb(v0, s2, 34);
    sb(v0, s2, 35);
    lw(v0, s2, 0);
    v0 = v0 | 0x1;
    sw(v0, s2, 0);
    v0 = v0 | 0x2;
    sw(v0, s2, 0);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001E7DE0 sub_1E7DE0 [K_AfterImage_Destroy] -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E7DE0(trail): destroys its frame (sub_4C3880) and frees it.
void sub_1E7DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e7de0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 16);
    jal(ctx, 0x1E7DF4u, gen::fn_sub_4C3880_004c3880);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1E7E08u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001E7E30 sub_1E7E30 [K_AfterImage_SegmentLength] -- 344 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1E7E30(trail, i) -> $f0: the length of trail segment i -> i + 1 (sub_1E8330 maps the ring index): the
// distances between the two edge point arrays (+16 / +20) added and scaled by the trail record's +44 through ACC.
void sub_1E7E30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    // 0x001e7e30
    enter(ctx, 86);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    jal(ctx, 0x1E7E50u, gen::fn_sub_1E8330_001e8330);
    s0 = v0;
    a1 = addiu(s1, 1);
    a0 = s2;
    jal(ctx, 0x1E7E64u, gen::fn_sub_1E8330_001e8330);
    mtc1(zero, f20);
    v1 = sll(s0, 1);
    v1 = addu(v1, s0);
    s1 = sll(v1, 2);
    lw(a0, s2, 16);
    v1 = sll(v0, 1);
    v0 = addu(v1, v0);
    s0 = sll(v0, 2);
    v0 = addu(a0, s0);
    lwc1(f1, v0, 0);
    v0 = addu(a0, s1);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    v1 = addiu(a0, 4);
    v0 = addu(v1, s0);
    lwc1(f1, v0, 0);
    v0 = addu(v1, s1);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x54);
    v1 = addiu(a0, 8);
    v0 = addu(v1, s0);
    lwc1(f1, v0, 0);
    v0 = addu(v1, s1);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x1E7EE0u, gen::fn_sub_4C6AC0_004c6ac0);
    add_s(f20, f20, f0);
    lw(a0, s2, 20);
    v0 = addu(a0, s0);
    lwc1(f1, v0, 0);
    v0 = addu(a0, s1);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    v1 = addiu(a0, 4);
    v0 = addu(v1, s0);
    lwc1(f1, v0, 0);
    v0 = addu(v1, s1);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x54);
    v1 = addiu(a0, 8);
    v0 = addu(v1, s0);
    lwc1(f1, v0, 0);
    v0 = addu(v1, s1);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x1E7F44u, gen::fn_sub_4C6AC0_004c6ac0);
    add_s(f2, f20, f0);
    mtc1(zero, f1);
    lw(v0, s2, 0);
    lw(v0, v0, 0);
    lwc1(f0, v0, 44);
    adda_s(f1, f1);
    madd_s(f0, f2, f0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001E7F90 sub_1E7F90 [K_AfterImage_LocateAlong] -- 928 bytes; frame 0xC0: ra sp+0x90, s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_1E7F90(trail, &segment, &t, $f12 distance): finds the segment containing the given distance along the trail
// (summing sub_1E7E30's lengths) and the fraction t inside it; K_Assert eff_after.c 129 for an empty segment; 0 / 0.0
// for a trail without length.
void sub_1E7F90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x001e7f90
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    mov_s(f24, f12);
    s1 = a1;
    s6 = a2;
    mtc1(zero, f21);
    s0 = 0;
    for (;;) {
        // 0x001e8000
        charge(ctx, 5);
        lw(v1, s2, 8);
        v1 = addiu(v1, -1);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001e7fe8
        charge(ctx, 6);
        a0 = s2;
        a1 = s0;
        jal(ctx, 0x1E7FF0u, gen::fn_sub_1E7E30_001e7e30);
        add_s(f21, f21, f0);
        s0 = addiu(s0, 1);
    }
    // 0x001e8014
    charge(ctx, 5);
    mtc1(zero, f0);
    c_le_s(f21, f0);
    if (!cond(ctx)) {
        // 0x001e8038
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x001e8170
            charge(ctx, 5);
            lw(v1, s2, 8);
            v1 = addiu(v1, -1);
            v1 = slt(s0, v1);
            if (v1 != 0) {
                backedge(ctx);
                // 0x001e8044
                charge(ctx, 4);
                mtc1(zero, f22);
                s5 = 0;
                for (;;) {
                    // 0x001e8150
                    charge(ctx, 4);
                    a0 = addiu(s0, 1);
                    v1 = slt(s5, a0);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001e8054
                    charge(ctx, 63);
                    a0 = s2;
                    a1 = s5;
                    jal(ctx, 0x1E805Cu, gen::fn_sub_1E8330_001e8330);
                    s3 = v0;
                    a1 = addiu(s5, 1);
                    a0 = s2;
                    jal(ctx, 0x1E8070u, gen::fn_sub_1E8330_001e8330);
                    mtc1(zero, f20);
                    lw(a0, s2, 16);
                    v1 = sll(s3, 1);
                    v1 = addu(v1, s3);
                    s4 = sll(v1, 2);
                    v1 = sll(v0, 1);
                    v0 = addu(v1, v0);
                    s3 = sll(v0, 2);
                    v1 = addu(a0, s3);
                    lwc1(f1, v1, 0);
                    v0 = addu(a0, s4);
                    lwc1(f0, v0, 0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB0);
                    lwc1(f1, v1, 4);
                    lwc1(f0, v0, 4);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB4);
                    lwc1(f1, v1, 8);
                    lwc1(f0, v0, 8);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB8);
                    a0 = addiu(sp, 0xB0);
                    jal(ctx, 0x1E80D4u, gen::fn_sub_4C6AC0_004c6ac0);
                    add_s(f20, f20, f0);
                    lw(v0, s2, 20);
                    v1 = addu(v0, s3);
                    lwc1(f1, v1, 0);
                    v0 = addu(v0, s4);
                    lwc1(f0, v0, 0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB0);
                    lwc1(f1, v1, 4);
                    lwc1(f0, v0, 4);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB4);
                    lwc1(f1, v1, 8);
                    lwc1(f0, v0, 8);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB8);
                    a0 = addiu(sp, 0xB0);
                    jal(ctx, 0x1E8120u, gen::fn_sub_4C6AC0_004c6ac0);
                    add_s(f2, f20, f0);
                    mtc1(zero, f1);
                    lw(v1, s2, 0);
                    lw(v1, v1, 0);
                    lwc1(f0, v1, 44);
                    adda_s(f1, f1);
                    madd_s(f0, f2, f0);
                    div_s(f0, f0, f21);
                    add_s(f22, f22, f0);
                    s5 = addiu(s5, 1);
                }
                // 0x001e8160
                charge(ctx, 3);
                c_lt_s(f24, f22);
                if (!cond(ctx)) {
                    // 0x001e816c
                    charge(ctx, 1);
                    s0 = a0;
                    continue;
                }
            }
            break;
        }
        // 0x001e8184
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x001e8198
            charge(ctx, 4);
            mtc1(zero, f23);
            s5 = 0;
            for (;;) {
                // 0x001e82a4
                charge(ctx, 3);
                v1 = slt(s5, s0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001e81a8
                charge(ctx, 63);
                a0 = s2;
                a1 = s5;
                jal(ctx, 0x1E81B0u, gen::fn_sub_1E8330_001e8330);
                s3 = v0;
                a1 = addiu(s5, 1);
                a0 = s2;
                jal(ctx, 0x1E81C4u, gen::fn_sub_1E8330_001e8330);
                mtc1(zero, f20);
                lw(a0, s2, 16);
                v1 = sll(s3, 1);
                v1 = addu(v1, s3);
                s4 = sll(v1, 2);
                v1 = sll(v0, 1);
                v0 = addu(v1, v0);
                s3 = sll(v0, 2);
                v1 = addu(a0, s3);
                lwc1(f1, v1, 0);
                v0 = addu(a0, s4);
                lwc1(f0, v0, 0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xA0);
                lwc1(f1, v1, 4);
                lwc1(f0, v0, 4);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xA4);
                lwc1(f1, v1, 8);
                lwc1(f0, v0, 8);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xA8);
                a0 = addiu(sp, 0xA0);
                jal(ctx, 0x1E8228u, gen::fn_sub_4C6AC0_004c6ac0);
                add_s(f20, f20, f0);
                lw(v0, s2, 20);
                v1 = addu(v0, s3);
                lwc1(f1, v1, 0);
                v0 = addu(v0, s4);
                lwc1(f0, v0, 0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xA0);
                lwc1(f1, v1, 4);
                lwc1(f0, v0, 4);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xA4);
                lwc1(f1, v1, 8);
                lwc1(f0, v0, 8);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xA8);
                a0 = addiu(sp, 0xA0);
                jal(ctx, 0x1E8274u, gen::fn_sub_4C6AC0_004c6ac0);
                add_s(f2, f20, f0);
                mtc1(zero, f1);
                lw(v1, s2, 0);
                lw(v1, v1, 0);
                lwc1(f0, v1, 44);
                adda_s(f1, f1);
                madd_s(f0, f2, f0);
                div_s(f0, f0, f21);
                add_s(f23, f23, f0);
                s5 = addiu(s5, 1);
            }
        } else {
            // 0x001e818c
            charge(ctx, 3);
            mtc1(zero, f23);
        }
        // 0x001e82b0
        charge(ctx, 7);
        sw(s0, s1, 0);
        sub_s(f20, f22, f23);
        mtc1(zero, f0);
        c_le_s(f20, f0);
        if (cond(ctx)) {
            // 0x001e82cc
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 17656);  // "eff_after.c"
            a1 = 129;
            jal(ctx, 0x1E82D8u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001e82e0
        charge(ctx, 4);
        sub_s(f0, f24, f23);
        div_s(f0, f0, f20);
        swc1(f0, s6, 0);
    } else {
        // 0x001e8028
        charge(ctx, 4);
        sw(zero, s1, 0);
        swc1(f0, s6, 0);
    }
    // 0x001e82f0 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    ld(ra, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

}  // namespace p3fes::game
